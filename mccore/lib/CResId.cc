//                              -*- Mode: C++ -*- 
// CResId.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri Aug 24 17:35:48 2001
// Update Count     : 9
// Status           : Ok.
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Binstream.h"
#include "CMessageQueue.h"
#include "CResId.h"
#include "McCore.h"


  
CResId::CResId (const char *str)
  : no (-1),
    chain (' '),
    iCode (' '),
    mRep (0)
{
  char *strCopy = strdup (str);
  char *base = strCopy;
  char *token;
  unsigned int i;

  if (strCopy[0] == '\'')
    {
      if (strlen (strCopy) < 4 || strCopy[2] != '\'')
	{
	  gOut (2) << "Malformed residue id " << strCopy << endl;
	  delete[] base;
	  return;
	}
      chain = strCopy[1];
      strCopy += 3;
    }
  else if (isalpha (strCopy[0]))
    chain = *strCopy++;
  
  token = strsep (&strCopy, ".");

  if (strlen (token) > 4 || strlen (token) < 1)
    {
      gOut (2) << "Malformed residue number in residue id "
	       << '\'' << chain << '\'' << token;
      if (strlen (strCopy) > 0)
	gOut << '.' << strCopy;
      gOut << endl;
      delete[] base;
      return;
    }
  for (i = 0; i < strlen (token); ++i)
    if (!isdigit (token[i]))
      {
	gOut (2) << "Malformed residue number in residue id "
		 << '\'' << chain << '\'' << token;
	if (strlen (strCopy) > 0)
	  gOut << '.' << strCopy;
	gOut << endl;
	delete[] base;
	return;
      }
  no = atoi (token);
  if (strCopy)
    {
      if (strlen (strCopy) != 1)
	{
	  gOut (2) << "Malformed insertion code in residue id "
		   << (const char*)*this << "." << strCopy << endl;
	  delete[] base;
	  return;
	}
      iCode = strCopy[0];
    }
  delete[] base;
}



CResId&
CResId::operator= (const CResId &right)
{
  if (this != &right)
    {
      no = right.no;
      chain = right.chain;
      iCode = right.iCode;
      if (mRep)
	{
	  delete[] mRep;
	  mRep = 0;
	}
    }
  return *this;
}



CResId::operator const char* () const
{
  if (!mRep)
    {
      mRep = new char[11];

      if (chain == ' ')
	sprintf (mRep, "%d", no);
      else if (! isalpha (chain))
	sprintf (mRep, "'%c'%d", chain, no);
      else
	sprintf (mRep, "%c%d", chain, no);
      if (iCode != ' ')
	{
	  char ic[3];

	  sprintf (ic, ".%c", iCode);
	  strcat (mRep, ic);
	}
    }
  return mRep;
}



ostream&
operator<< (ostream &os, const CResId &obj)
{
  return os << obj.operator const char* ();
}



iBinstream&
operator>> (iBinstream &ibs, CResId &obj)
{
  int resno;
  char chainid, ic;

  ibs >> resno >> chainid >> ic;
  obj.SetResNo (resno);
  obj.SetChainId (chainid);
  obj.setInsertionCode (ic);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CResId &obj)
{
  return obs << obj.GetResNo () << obj.GetChainId ()
	     << obj.getInsertionCode ();
}
