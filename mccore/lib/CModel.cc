//                              -*- Mode: C++ -*- 
// CModel.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Thu Nov  9 10:44:51 2000
// Update Count     : 2
// Status           : Unknown.
// 


#include "algo.h"

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
