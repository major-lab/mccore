//                              -*- Mode: C++ -*- 
// Exception.cc
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.1 $
// $Id: Exception.cc,v 1.1 2004-06-30 18:13:01 thibaup Exp $
//
// This file is part of mccore.
//
// mccore is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// mccore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with mccore; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>

#include "ResId.h"
#include "Exception.h"


namespace mccore
{

  
#ifdef HAVE_NUMERIC_LIMITS
  void terminate_func (void)
  {
    cerr << "An exception was thrown but not caught." << endl
	 << "Please send a bug report to 'bug-mcsym@iro.umontreal.ca'." << endl;
    exit(EXIT_FAILURE);
  }
#endif


  Exception::Exception ()
  { 
#ifdef HAVE_NUMERIC_LIMITS
    set_terminate(&terminate_func);
#endif

    mMessage = new char[1];
    mMessage[0] = '\0';
  }



  Exception::Exception (const char *message)
  {
#ifdef HAVE_NUMERIC_LIMITS
    set_terminate(&terminate_func);
#endif
    mMessage = new char[strlen (message) + 1];
    strcpy (mMessage, message);
  }



  Exception::Exception (const Exception &right)
  {
    mMessage = new char[strlen (right.mMessage) + 1];
    strcpy (mMessage, right.mMessage);
  }



  const Exception&
  Exception::operator= (const Exception &right)
  {
    if (this != &right)
      {
	delete[] mMessage;
	mMessage = new char[strlen (right.mMessage) + 1];
	strcpy (mMessage, right.mMessage);
      }
    return *this;
  }



  Exception&
  Exception::operator<< (const char *message)
  {
    char *tmp;

    tmp = new char[strlen (mMessage) + strlen (message) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, message);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (int integer)
  {
    char str[256];
    char *tmp;

    sprintf (str, "%d", integer);
    tmp = new char[strlen (mMessage) + strlen (str) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, str);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (unsigned int integer)
  {
    char str[256];
    char *tmp;

    sprintf (str, "%u", integer);
    tmp = new char[strlen (mMessage) + strlen (str) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, str);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (long int integer)
  {
    char str[256];
    char *tmp;

    sprintf (str, "%ld", integer);
    tmp = new char[strlen (mMessage) + strlen (str) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, str);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (unsigned long int integer)
  {
    char str[256];
    char *tmp;

    sprintf (str, "%lu", integer);
    tmp = new char[strlen (mMessage) + strlen (str) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, str);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (float float_val)
  {
    char str[256];
    char *tmp;

    sprintf (str, "%f", float_val);
    tmp = new char[strlen (mMessage) + strlen (str) + 1];
    strcpy (tmp, mMessage);
    strcat (tmp, str);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }



  Exception&
  Exception::operator<< (char theChar)
  {
    char a[2];
    char *tmp;

    a[0] = theChar;
    a[1] = '\0';
    tmp = new char[strlen (mMessage) + 2];
    strcpy (tmp, mMessage);
    strcat (tmp, a);
    delete[] mMessage;
    mMessage = tmp;
    return *this;
  }


  ostream& 
  Exception::output (ostream &os) const
  {
    return os << GetMessage ();
  }

  
  const InterruptException&
  InterruptException::operator= (const InterruptException &right)
  {
    if (this != &right)
      Exception::operator= (right);
    return *this;
  }	



  const LibException&
  LibException::operator= (const LibException &right)
  {
    if (this != &right)
      Exception::operator= (right);
    return *this;
  }



  const FatalLibException&
  FatalLibException::operator= (const FatalLibException &right)
  {
    if (this != &right)
      LibException::operator= (right);
    return *this;
  }



  IntLibException::IntLibException ()
    : Exception (), mLine (0)
  {
    mFile = new char[1];
    mFile[0] = '\0';
  }



  IntLibException::IntLibException (const char *theMessage,
				      const char *file, int line)
    : Exception (theMessage), mLine (line)
  {
    if (file)
      {
	mFile = new char[strlen (file) + 1];
	strcpy (mFile, file);
      }
    else
      {
	mFile = new char[1];
	mFile[0] = '\0';
      }
  }



  IntLibException::IntLibException (const IntLibException &right)
    : Exception (right), mLine (right.mLine)
  {
    mFile = new char[strlen (right.mFile) + 1];
    strcpy (mFile, right.mFile);
  }



  const IntLibException&
  IntLibException::operator= (const IntLibException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
	mFile = new char[strlen (right.mFile) + 1];
	strcpy (mFile, right.mFile);
	mLine = right.mLine;
      }
    return *this;
  }



  ostream& 
  IntLibException::output (ostream &os) const
  {
    os << GetFileName () << ":" << GetLine () << ": ";
    Exception::output (os);
    os << endl << endl
       << "Please send a bug report to 'bug-mcsym@iro.umontreal.ca'.";
    return os;
  }



  const FatalIntLibException&
  FatalIntLibException::operator= (const FatalIntLibException &right)
  {
    if (this != &right)
      IntLibException::operator= (right);
    return *this;
  }



  const SocketException&
  SocketException::operator= (const SocketException &right)
  {
    if (this != &right)
      Exception::operator= (right);
    return *this;
  }



  FatalSocketException::FatalSocketException ()
    : Exception (), mLine (0)
  {
    mFile = new char[1];
    mFile[0] = '\0';
  }



  FatalSocketException::FatalSocketException (const char *theMessage,
						const char *file, int line)
    : Exception (theMessage), mLine (line)
  {
    if (file)
      {
	mFile = new char[strlen (file) + 1];
	strcpy (mFile, file);
      }
    else
      {
	mFile = new char[1];
	mFile[0] = '\0';
      }
  }



  FatalSocketException::FatalSocketException (const FatalSocketException &right)
    : Exception (right), mLine (right.mLine)
  {
    mFile = new char[strlen (right.mFile) + 1];
    strcpy (mFile, right.mFile);
  }



  const FatalSocketException&
  FatalSocketException::operator= (const FatalSocketException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
	mFile = new char[strlen (right.mFile) + 1];
	strcpy (mFile, right.mFile);
	mLine = right.mLine;
      }
    return *this;
  }



  ostream& 
  FatalSocketException::output (ostream &os) const
  {
    os << GetFileName () << ":" << GetLine () << ": ";
    Exception::output (os);
    return os;
  }



  const ConnectionException&
  ConnectionException::operator= (const ConnectionException &right)
  {
    if (this != &right)
      SocketException::operator= (right);
    return *this;
  }	


}

namespace std
{
  ostream&
  operator<< (ostream &os, const mccore::Exception &exc)
  {
    return exc.output (os);
  }
}
