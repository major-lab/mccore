//                              -*- Mode: C++ -*- 
// CModel.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:49 2000
// Update Count     : 1
// Status           : Unknown.
// 


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
