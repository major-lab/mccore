//                              -*- Mode: C++ -*- 
// CResIdSet.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Oct 26 10:24:02 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Dec  4 15:41:26 2000
// Update Count     : 4
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
	  
	  if (upper)
	    {
	      if (isalpha (lower[0]) && isalpha (upper[0])
		  && lower[0] == upper[0])
		{
		  char chain = lower[0];
		  int start = atoi (++lower); 
		  int end = atoi (++upper);
		  int i;
		  
		  for (i = start; i <= end; i++)
		    insert (i, chain);
		}
	      else if (isdigit (lower[0]) && isdigit (upper[0]))
		{
		  int start = atoi (lower); 
		  int end = atoi (upper);
		  int i;
		  
		  for (i = start; i <= end; i++)
		    insert (i);
		}
	      else
		throw CIntLibException ("Malformed residue id range",
					__FILE__, __LINE__);
	    }
	  else
	    insert (CResId (lower));
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


