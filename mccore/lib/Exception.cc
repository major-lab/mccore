//                              -*- Mode: C++ -*- 
// Exception.cc
// Copyright © 1999, 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.3.2.5 $
// $Id: Exception.cc,v 1.3.2.5 2004-12-27 01:34:57 larosem Exp $
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

#include <sstream>

#include "Exception.h"



namespace mccore
{

  Exception&
  Exception::operator= (const Exception &right)
  {
    if (this != &right)
      {
	mMessage = right.mMessage;
      }
    return *this;
  }



  Exception&
  Exception::operator<< (const char *message)
  {
    mMessage += message;
    return *this;
  }


  Exception&
  Exception::operator<< (const string &message)
  {
    mMessage += message;
    return *this;
  }
  

  Exception&
  Exception::operator<< (int integer)
  {
    ostringstream oss;

    oss << integer;
    mMessage += oss.str ();
    return *this;
  }



  Exception&
  Exception::operator<< (unsigned int integer)
  {
    ostringstream oss;

    oss << integer;
    mMessage += oss.str ();
    return *this;
  }



  Exception&
  Exception::operator<< (long int integer)
  {
    ostringstream oss;

    oss << integer;
    mMessage += oss.str ();
    return *this;
  }



  Exception&
  Exception::operator<< (unsigned long int integer)
  {
    ostringstream oss;

    oss << integer;
    mMessage += oss.str ();
    return *this;
  }



  Exception&
  Exception::operator<< (float float_val)
  {
    ostringstream oss;

    oss << float_val;
    mMessage += oss.str ();
    return *this;
  }



  Exception&
  Exception::operator<< (char theChar)
  {
    ostringstream oss;

    oss << theChar;
    mMessage += oss.str ();
    return *this;
  }


  InterruptException&
  InterruptException::operator= (const InterruptException &right)
  {
    if (this != &right)
      Exception::operator= (right);
    return *this;
  }	


  NoSuchElementException&
  NoSuchElementException::operator= (const NoSuchElementException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
      }
    return *this;
  }

  
  LibException&
  LibException::operator= (const LibException &right)
  {
    if (this != &right)
      Exception::operator= (right);
    return *this;
  }


  FatalLibException&
  FatalLibException::operator= (const FatalLibException &right)
  {
    if (this != &right)
      LibException::operator= (right);
    return *this;
  }


  IntLibException&
  IntLibException::operator= (const IntLibException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
	mFile = right.mFile;
	mLine = right.mLine;
      }
    return *this;
  }


  ostream& 
  IntLibException::output (ostream &os) const
  {
    os << getFileName () << ":" << getLine () << ": ";
    Exception::output (os);
    return os << endl;
  }

  
  NoSuchAtomException&
  NoSuchAtomException::operator= (const NoSuchAtomException &right)
  {
    if (this != &right)
      {
	IntLibException::operator= (right);
      }
    return *this;
  }


  NullPointerException&
  NullPointerException::operator= (const NullPointerException &right)
  {
    if (this != &right)
      {
	IntLibException::operator= (right);
      }
    return *this;
  }


  ArrayIndexOutOfBoundsException&
  ArrayIndexOutOfBoundsException::operator= (const ArrayIndexOutOfBoundsException &right)
  {
    if (this != &right)
      {
	IntLibException::operator= (right);
      }
    return *this;
  }
  
	
  FatalIntLibException&
  FatalIntLibException::operator= (const FatalIntLibException &right)
  {
    if (this != &right)
      {
	IntLibException::operator= (right);
      }
    return *this;
  }


  SocketException&
  SocketException::operator= (const SocketException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
      }
    return *this;
  }


  FatalSocketException&
  FatalSocketException::operator= (const FatalSocketException &right)
  {
    if (this != &right)
      {
	Exception::operator= (right);
	mFile = right.mFile;
	mLine = right.mLine;
      }
    return *this;
  }


  ostream& 
  FatalSocketException::output (ostream &os) const
  {
    os << getFileName () << ":" << getLine () << ": ";
    Exception::output (os);
    return os;
  }


  ConnectionException&
  ConnectionException::operator= (const ConnectionException &right)
  {
    if (this != &right)
      {
	SocketException::operator= (right);
      }
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
