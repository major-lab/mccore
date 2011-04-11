//                              -*- Mode: C++ -*- 
// ResId.cc
// Copyright � 2003-06 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:45:21 2003
// $Revision: 1.11 $
// $Id: ResId.cc,v 1.11 2007-01-09 00:03:22 larosem Exp $
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

// cmake generated defines
#include <config.h>

#include <string.h>
#include <sstream>

#include "ResId.h"
#include "Binstream.h"
#include "Exception.h"



#ifndef HAVE_STRSEP
static char*
strsep (char **stringp, const char *delim)
{
  char *return_val = *stringp;
  char *to;

  if (*stringp == 0)
    return 0;

  to = strpbrk (*stringp, delim);

  if (to)
    *to++ = '\0';
  
  *stringp = to;

  return return_val;
}
#endif



namespace mccore
{
  
  ResId::ResId (const char *str)
    : chain (' '), no (-1), iCode (' ')
  {
    char *strCopy = strdup (str);
    char *base = strCopy;
    char *token;
    unsigned int i;
    
    if (strCopy[0] == '\'')
      {
	if (strlen (strCopy) < 4 || strCopy[2] != '\'')
	  {
	    delete[] base;
	    FatalLibException exc ("Malformed residue id ");
	    exc << strCopy;
	    throw exc;
	  }
	chain = strCopy[1];
	strCopy += 3;
      }
    else if (isalpha (strCopy[0]))
      chain = *strCopy++;
    
    token = strsep (&strCopy, ".");
    
    if (strlen (token) < 1)
      {
	delete[] base;
	FatalLibException exc ("Malformed residue number in residue id ");
	exc << '\'' << chain << '\'' << token;
	if (strCopy && strlen (strCopy) > 0)
	  exc << '.' << strCopy;
	throw exc;
      }
    for (i = 0; i < strlen (token); ++i)
      if (!isdigit (token[i]))
	{
	  delete[] base;
	  FatalLibException exc ("Residue number is non numeric in residue id ");
	  exc << '\'' << chain << '\'' << token;
	  if (strCopy && strlen (strCopy) > 0)
	    exc << '.' << strCopy;
	  throw exc;
	}
    no = atoi (token);
    if (strCopy)
      {
	if (strlen (strCopy) != 1)
	  {
	    delete[] base;
	    FatalLibException exc ("Malformed insertion code in residue id ");
	    exc << '\'' << chain << '\'' << no << "." << strCopy;
	    throw exc;
	  }
	iCode = strCopy[0];
      }
    delete[] base;
  }
  
  
  ResId&
  ResId::operator= (const ResId &other)
  {
    if (this != &other)
      {
	chain = other.chain;
	no = other.no;
	iCode = other.iCode;
      }
    return *this;
  }
  
  
  ostream&
  ResId::write (ostream &os) const
  {
    ostringstream oss;

    if (chain == ' ')
      {
	oss << no;
      }
    else if (! isalpha (chain))
      {
	oss << '\'' << chain << '\'' << no;
      }
    else
      {
	oss << chain << no;
      }
    
    if (iCode != ' ')
      {
	oss << '.' << iCode;
      }
    
    return os << oss.str ();
  }

    
  Exception&
  operator<< (Exception &ex, const ResId& obj)
  {
    if (obj.getChainId () == ' ') ex << obj.getResNo ();
    else if (! isalpha (obj.getChainId ())) 
      ex << '\'' << obj.getChainId () << '\'' << obj.getResNo ();
    else ex << obj.getChainId () << obj.getResNo ();
    
    if (obj.getInsertionCode () != ' ') ex << '.' << obj.getInsertionCode ();
    
    return ex;
  }
  
  
  iBinstream&
  operator>> (iBinstream &ibs, ResId &obj)
  {
    int resno = 0;
    char chainid = 0;
    char ic = 0;
    
    ibs >> resno >> chainid >> ic;
    obj.setResNo (resno);
    obj.setChainId (chainid);
    obj.setInsertionCode (ic);
    return ibs;
  }


  oBinstream&
  operator<< (oBinstream &obs, const ResId &obj)
  {
    return obs << obj.getResNo () << obj.getChainId ()
	       << obj.getInsertionCode ();
  }

}



namespace std
{

  ostream&
  operator<< (ostream &os, const mccore::ResId &obj)
  {
    return obj.write (os);
  }
  

  ostream&
  operator<< (ostream &os, const mccore::ResId *obj)
  {
    return obj->write (os);
  }
  
}  
