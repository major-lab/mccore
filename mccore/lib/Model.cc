//                              -*- Mode: C++ -*- 
// Model.cc
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// $Revision: 1.26 $
// $Id: Model.cc,v 1.26 2004-12-10 00:30:09 larosem Exp $
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

#include <algorithm>
#include <cstring>

#include "Binstream.h"
#include "Messagestream.h"
#include "ExtendedResidue.h"
#include "Model.h"
#include "Pdbstream.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"



namespace mccore
{
  
  bool
  less_deref (Residue* const &x, Residue* const &y)
  {
    return *x < *y;
  }

  
  Model::Model (const Model &right)
    : AbstractModel (right)
  {
    const_iterator cit;
    
    for (cit = right.begin (); cit != right.end (); ++cit)
      this->insert (*cit);
  }


  Model::~Model ()
  {
    vector< Residue* >::iterator it;
    
    for (it = this->residues.begin (); it != this->residues.end (); ++it) 
      delete *it;      
  }


  Model&
  Model::operator= (const Model &right)
  {
    if (this != &right)
      {
	const_iterator cit;

	AbstractModel::operator= (right);
	this->clear ();	
	for (cit = right.begin (); cit != right.end (); ++cit)
	  this->insert (*cit);
      }
    return *this;
  }
  
  
  Residue&
  Model::operator[] (size_type nth)
  {
    return nth > size () ? *end () : *residues[nth];
  }



  const Residue&
  Model::operator[] (size_type nth) const
  {
    return nth > size () ? *end () : *residues[nth];
  }


  Model::iterator 
  Model::insert (const Residue &res)
  { 
    return (Model::iterator) residues.insert (residues.end (), res.clone ());
  }
  
  
  void
  Model::sort ()
  {
    std::sort (residues.begin (), residues.end (), &less_deref);
  }
  
  
  void 
  Model::clear()
  {
    vector< Residue* >::iterator it;
    
    for (it = residues.begin (); it != residues.end (); ++it) 
      delete *it;      
    residues.clear ();    
  }
  
  
  ostream& 
  Model::output (ostream &os) const
  {
    const_iterator cit;
    
    os << "MODEL (size=" << flush << residues.size() << ") :" << flush;
    for (cit = begin (); cit != end (); ++cit)
      os << cit->getResId ()  << " ";
    return os;
  }
  
  
  iPdbstream& 
  Model::input (iPdbstream &ips)
  {
    clear ();
    int currNb = ips.getModelNb ();
    
    while (! (ips.eof ()) && currNb == ips.getModelNb () )
      {
	Residue *res = getResidueFM ()->createResidue ();
	
	ips >> *res;
	
 	if (res->size () != 0) {
	  // Optimized insertion that bypasses the copy: 
 	  residues.push_back (res); 
	} else
	  delete res;
      }    
    return ips;
  }
  
  
  oBinstream& 
  Model::output (oBinstream &obs) const
  {
    const_iterator cit;
    
    obs << size ();
    for (cit = begin (); cit != end (); ++cit)
      obs << *cit;
    return obs;
  }
  
  
  iBinstream& 
  Model::input (iBinstream &ibs)
  {
    clear ();
    
    Model::size_type sz;
    
    ibs >> sz;
    for (; sz > 0; --sz)
      {
	Residue *res = getResidueFM ()->createResidue ();
	
	ibs >> *res;
	// Optimized insertion that bypasses the copy: 
	residues.push_back (res); 
      }
    return ibs;
  }
}
