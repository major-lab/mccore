//                              -*- Mode: C++ -*- 
// CModel.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:02:58 2001
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


#include <string.h>

#include "CModel.h"

#include "Binstream.h"
#include "Pdbstream.h"
#include "ResidueType.h"
#ifndef HAVE_STRSEP
#include "McCore.h"
#endif


CModel&
CModel::operator= (const CModel &right)
{
  if (this != &right)
    {
      list< CResidue >::operator= (right);
    }
  return *this;
}



CModel::reference
CModel::operator[] (size_type nth)
{
  if (nth > size ())
    return *(end ());
  else
    {
      iterator it;
      
      for (it = begin (); nth > 0; --nth, ++it);
      return *it;
    }
}



CModel::const_reference
CModel::operator[] (size_type nth) const
{
  if (nth > size ())
    return *(end ());
  else
    {
      const_iterator cit;
      
      for (cit = begin (); nth > 0; --nth, ++cit);
      return *cit;
    }
}



CModel
CModel::Validate () const
{
  const_iterator it = begin ();
  CModel model;

  for (it = begin (); it != end (); ++it)
    {
      CResidue res = it->Validate ();
      
      if (res.GetType ()->is_NucleicAcid ())
	model.push_back (res);
    }
  return model;
}



CModel
CModel::RemoveOptionals () const
{
  const_iterator it;
  CModel model;

  for (it = begin (); it != end (); ++it)
    model.push_back (it->RemoveOptionals ());
  return model;
}



CModel
CModel::SortAtoms () const
{
  const_iterator cit;
  CModel model;

  for (cit = begin (); cit != end (); ++cit)
    model.push_back (cit->sort ());
  return model;
}



CResidue::iterator
CModel::find (const char *str)
{
  char *s = new char[strlen (str) + 1];
  char *p = s;
  char *argum;
  vector< char* > tok;
  CModel::iterator mit;
  CResidue::iterator it;
  
  strcpy (s, str);
  argum = strsep (&p, ":");
  while (argum)
    {
      if (strlen (argum) > 0) 
	tok.push_back (argum);
      argum = strsep (&p, ":");
    }

  if (tok.size () == 2
      && (mit = find (CResId (tok[0]))) != end ()
      && (it = mit->find (iPdbstream::GetAtomType (tok[1]))) != mit->end ())
    return it;
  else
    return CResidue::iterator ();
}



CResidue::const_iterator
CModel::find (const char *str) const
{
  char *s = new char[strlen (str) + 1];
  char *p = s;
  char *argum;
  vector< char* > tok;
  CModel::const_iterator mit;
  CResidue::const_iterator it;
  
  strcpy (s, str);
  argum = strsep (&p, ":");
  while (argum)
    {
      if (strlen (argum) > 0) 
	tok.push_back (argum);
      argum = strsep (&p, ":");
    }

  if (tok.size () == 2
      && (mit = find (CResId (tok[0]))) != end ()
      && (it = mit->find (iPdbstream::GetAtomType (tok[1]))) != mit->end ())
    return it;
  else
    return CResidue::const_iterator ();
}



CModel::iterator
CModel::find (const CResId &id)
{
  iterator it;

  for (it = begin (); it != end (); ++it)
    if (id == *it)
      break;
  return it;
}



CModel::const_iterator
CModel::find (const CResId &id) const
{
  const_iterator it;

  for (it = begin (); it != end (); ++it)
    if (id == *it)
      break;
  return it;
}



bool
operator< (const CModel::iterator &left, const CModel::iterator &right)
{
  return *left < *right;
}



iPdbstream&
operator>> (iPdbstream &ips, CModel &obj)
{
  obj.clear ();
  while (! (ips.eof () || ips.eop ()))
    {
      CResidue res;

      ips >> res;
      if (res.size () != 0)
	obj.push_back (res);
      if (ips.eom ())
	break;
    }
  return ips;
}



oPdbstream&
operator<< (oPdbstream &ops, const CModel &obj)
{
  CModel::const_iterator cit;

  if ((cit = obj.begin ()) != obj.end ())
    {
      char last_chain_id = cit->GetChainId ();
      
      for (; cit != obj.end (); ++cit)
	{
	  if (cit->GetChainId () != last_chain_id)
	    {
	      ops.TER ();
	      last_chain_id = cit->GetChainId ();
	    }
	  ops << *cit;
	}
      ops.TER ();
    }
  return ops;
}



iBinstream&
operator>> (iBinstream &ibs, CModel &obj)
{
  CModel::size_type sz;

  obj.clear ();
  ibs >> sz;
  for (; sz > 0; --sz)
    {
      obj.push_back (CResidue ());
      CResidue &tmp = obj.back ();

      ibs >> tmp;
    }
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CModel &obj)
{
  CModel::const_iterator cit;
  
  obs << obj.size ();
  for (cit = obj.begin (); cit != obj.end (); ++cit)
    obs << *cit;
  return obs;
}
