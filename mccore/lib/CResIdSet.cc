//                              -*- Mode: C++ -*- 
// CResIdSet.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Oct 26 10:24:02 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri Feb  9 16:08:24 2001
// Update Count     : 5
// Status           : Unknown.
// 


#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "CResIdSet.h"

#include "McCore.h"
#include "CException.h"



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
      token = strsep (&str_copy, ",");
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
	  token = strsep (&str_copy, ",");
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


