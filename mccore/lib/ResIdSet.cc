//                              -*- Mode: C++ -*- 
// ResIdSet.cc
// Copyright © 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Oct 26 10:24:02 2000
// $Revision: 1.6.2.1 $
// $Id: ResIdSet.cc,v 1.6.2.1 2004-12-25 02:44:31 larosem Exp $
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

#include "Binstream.h"
#include "Exception.h"
#include "Messagestream.h"
#include "ResIdSet.h"



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
  
  ResIdSet::ResIdSet (int resno, char chainid)
    : mIndex (begin ())
  {
    insert (resno, chainid);
  }
  
  
  ResIdSet&
  ResIdSet::operator= (const ResIdSet &right)
  {
    if (this != &right)
      {
	set< ResId >::operator= (right);
	mIndex = right.mIndex;
      }
    return *this;
  }
  
  
  ResIdSet&
  ResIdSet::operator++ ()
  {
    mIndex++;
    return *this;
  }


  ResIdSet
  ResIdSet::operator++ (int ign)
  {
    ResIdSet copy (*this);
    mIndex++;
    return copy;
  }


  char
  ResIdSet::getChainId () const
  {
    return (*mIndex).getChainId (); 
  }


  int
  ResIdSet::getResNo () const
  { 
    return (*mIndex).getResNo ();
  }


  void
  ResIdSet::_parse_and_insert (const char *str)
  {
    if (str)
      {
	if (strlen (str) == 0) return;

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

	    ResId low (lower);
	    insert (low);
	    if (upper)
	      {
		ResId upp (upper);

		if (low.getChainId () == upp.getChainId ()
		    && low.getResNo () < upp.getResNo ())
		  {
		    char chain = low.getChainId ();
		    int start = low.getResNo () + 1;
		    int end = upp.getResNo ();
		  
		    for (; start <= end; ++start)
		      insert (start, chain);
		  }
		else
		  {
		    IntLibException exc ("Malformed residue id range", __FILE__, __LINE__);
		    throw exc;
		  }
	      }
	    token = strsep (&str_copy, ", ");
	  }
	delete str_copy_ptr;
      }
  }


  void
  ResIdSet::insert (int resno, char chainid)
  {
    set< ResId >::insert (ResId (chainid, resno));
  }


  iBinstream&
  operator>> (iBinstream &ibs, ResIdSet &obj)
  {
    ResIdSet::size_type sz;

    obj.clear ();
    ibs >> sz;
    for (; sz > 0; --sz)
      {
	ResId id;

	ibs >> id;
	obj.insert (obj.end (), id);
      }
    return ibs;
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const ResIdSet &obj)
  {
    ResIdSet::const_iterator cit;
  
    obs << obj.size ();
    for (cit = obj.begin (); cit != obj.end (); ++cit)
      obs << *cit;
    return obs;
  }

}



namespace std
{
  
  ostream&
  operator<< (ostream &os, const mccore::ResIdSet &residset)
  {
    mccore::ResIdSet::const_iterator cit1, cit2;
    
    cit1 = residset.begin ();
    if (cit1 != residset.end ())
      {
	bool inrange = false;
	for (cit2 = cit1, ++cit2; cit2 != residset.end (); ++cit1, ++cit2)
	  {
	    if (cit2->getChainId () == cit1->getChainId ()
		&& cit2->getResNo () == cit1->getResNo () + 1)
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

}  
