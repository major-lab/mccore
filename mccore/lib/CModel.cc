//                              -*- Mode: C++ -*- 
// CModel.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Dec  4 15:38:53 2000
// Update Count     : 3
// Status           : Unknown.
// 


#include <string.h>

#include "CModel.h"

#include "Pdbstream.h"



CModel&
CModel::operator= (const CModel &right)
{
  if (this != &right)
    {
      vector< CResidue >::operator= (right);
    }
  return *this;
}



CModel
CModel::Validate () const
{
  const_iterator it = begin ();
  CModel model;

  for (it = begin (); it != end (); ++it)
    {
      CResidue res = it->Validate ();
      
      if (res.GetType () != 0)
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



iPdbstream&
operator>> (iPdbstream &ips, CModel &obj)
{
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
