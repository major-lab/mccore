//                              -*- Mode: C++ -*- 
// CResIdSet.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Oct 26 10:24:02 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri Oct  5 16:56:52 2001
// Update Count     : 9
// Status           : Unknown.
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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Binstream.h"
#include "CException.h"
#include "CResIdSet.h"
#include "McCore.h"



CResIdSet::CResIdSet (int resno, char chainid)
  : mIndex (begin ())
{
  insert (resno, chainid);
}



CResIdSet&
CResIdSet::operator= (const CResIdSet &right)
{
  if (this != &right)
    {
      set< CResId >::operator= (right);
      mIndex = right.mIndex;
    }
  return *this;
}



CResIdSet&
CResIdSet::operator++ ()
{
  mIndex++;
  return *this;
}



CResIdSet
CResIdSet::operator++ (int ign)
{
  CResIdSet copy (*this);
  mIndex++;
  return copy;
}



char
CResIdSet::GetChainId () const
{
  return (*mIndex).GetChainId (); 
}



int
CResIdSet::GetResNo () const
{ 
  return (*mIndex).GetResNo ();
}



void
CResIdSet::_parse_and_insert (const char *str)
{
  if (str)
    {
      char* str_copy = new char[strlen (str) + 1];
      char* str_copy_ptr = str_copy;
      char* token = 0;
      char* lower = 0;
      char* upper = 0;
      
      strcpy (str_copy, str);
      token = strsep (&str_copy, ", ");
      while (token)
	{
	  lower = strsep (&token, "-");
	  upper = strsep (&token, "-");
	  
	  CResId low (lower);
	  insert (low);
	  if (upper)
	    {
	      CResId upp (upper);

	      if (low.GetChainId () == upp.GetChainId ()
		  && low.GetResNo () < upp.GetResNo ())
		{
		  char chain = low.GetChainId ();
		  int start = low.GetResNo () + 1;
		  int end = upp.GetResNo ();
		  
		  for (; start <= end; ++start)
		    insert (start, chain);
		}
	      else
		{
		  CIntLibException exc ("Malformed residue id range",
					__FILE__, __LINE__);

		  exc << str;
		  throw exc;
		}
	    }
	  token = strsep (&str_copy, ", ");
	}
      delete str_copy_ptr;
    }
}



void
CResIdSet::insert (int resno, char chainid)
{
  set< CResId >::insert (CResId (resno, chainid));
}



ostream&
operator<< (ostream &os, const CResIdSet &residset)
{
  CResIdSet::const_iterator cit1, cit2;

  cit1 = residset.begin ();
  if (cit1 != residset.end ())
    {
      bool inrange = false;
      for (cit2 = cit1, ++cit2; cit2 != residset.end (); ++cit1, ++cit2)
	{
	  if (cit2->GetChainId () == cit1->GetChainId ()
	      && cit2->GetResNo () == cit1->GetResNo () + 1)
	    {
	      if (!inrange)
		{
		  inrange = true;
		  os << *cit1 << '-';
		}
	    }
	  else
	    {
	      inrange = false;
	      os << *cit1 << ',';
	    }
	}
      os << *cit1;
    }
  return os;
}



iBinstream&
operator>> (iBinstream &ibs, CResIdSet &obj)
{
  CResIdSet::size_type sz;

  obj.clear ();
  ibs >> sz;
  for (; sz > 0; --sz)
    {
      CResId id;

      ibs >> id;
      obj.insert (obj.end (), id);
    }
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CResIdSet &obj)
{
  CResIdSet::const_iterator cit;
  
  obs << obj.size ();
  for (cit = obj.begin (); cit != obj.end (); ++cit)
    obs << *cit;
  return obs;
}
