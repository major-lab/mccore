//                              -*- Mode: C++ -*- 
// CResId.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 23 15:09:47 2001
// Update Count     : 8
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
{
  if (str[0] == '\'')
    {
      if (strlen (str) < 4 || str[2] != '\'')
	{
	  gOut (3) << "Malformed residue id " << str << endl;
	  chain = ' ';
	  no = -1;
	  return;
	}
      chain = str[1];
      str += 3;
    }
  else if (isalpha (str[0]))
    chain = *str++;
  else
    chain = ' ';
  no = atoi (str);
}



CResId&
CResId::operator= (const CResId &right)
{
  if (this != &right)
    {
      no = right.no;
      chain = right.chain;
    }
  return *this;
}



CResId::operator const char* () const
{
  if (chain == ' ')
    sprintf (mRep, "%d", no);
  else
    sprintf (mRep, "%c%d", chain, no);
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
  char chainid;

  ibs >> resno >> chainid;
  obj.SetResNo (resno);
  obj.SetChainId (chainid);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CResId &obj)
{
  return obs << obj.GetResNo () << obj.GetChainId ();
}
