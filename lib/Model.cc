//                              -*- Mode: C++ -*- 
// Model.cc
// Copyright � 2001-05 Laboratoire de Biologie Informatique et Th�orique.
//                     Universit� de Montr�al.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// $Revision: 1.35 $
// $Id: Model.cc,v 1.35 2005-12-09 18:28:51 larosem Exp $
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


// cmake generated defines
#include <config.h>

#include <algorithm>

#include "Algo.h"
#include "Binstream.h"
#include "Messagestream.h"
#include "ExtendedResidue.h"
#include "Model.h"
#include "Pdbstream.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"



namespace mccore
{
  
  Model::Model (const AbstractModel &right, const ResidueFactoryMethod *fm)
    : AbstractModel (fm)
  {
    AbstractModel::insert (right.begin (), right.end ());
  }


  Model::Model (const Model &right, const ResidueFactoryMethod *fm)
    : AbstractModel (fm)
  {
    const_iterator cit;

    for (cit = right.begin (); right.end () != cit; ++cit)
      {
	residues.push_back (cit->clone ());
      }
  }
  
  
  Model::~Model ()
  {
    vector< Residue* >::iterator it;
    
    for (it = residues.begin (); it != residues.end (); ++it)
      {
	delete *it;
      }
  }


  Model&
  Model::operator= (const AbstractModel &right)
  {
    if (this != &right)
      {
	vector< Residue* >::iterator it;
	
	for (it = residues.begin (); it != residues.end (); ++it)
	  {
	    delete *it;
	  }
	residues.clear ();
	AbstractModel::operator= (right);
	AbstractModel::insert (right.begin (), right.end ());
      }
    return *this;
  }
  
  
  Model&
  Model::operator= (const Model &right)
  {
    if (this != &right)
      {
	vector< Residue* >::iterator it;
	
	for (it = residues.begin (); it != residues.end (); ++it)
	  {
	    delete *it;
	  }
	residues.clear ();
	AbstractModel::operator= (right);
	AbstractModel::insert (right.begin (), right.end ());
      }
    return *this;
  }
  
  
  Residue&
  Model::operator[] (size_type nth)
  {
    if (nth < size ())
      {
	return *residues[nth];
      }
    throw ArrayIndexOutOfBoundsException ("", __FILE__, __LINE__);
  }



  const Residue&
  Model::operator[] (size_type nth) const
  {
    if (nth < size ())
      {
	return *residues[nth];
      }
    throw ArrayIndexOutOfBoundsException ("", __FILE__, __LINE__);
  }


  Model::iterator 
  Model::insert (const Residue &res)
  {
    iterator found;

    if (end () == (found = find (res.getResId ())))
    {
      found = this->residues.insert (this->residues.end (), this->residueFM->createResidue (res));
    }
    else
    {
      gErr (4) << "Warning: model's residue " << *found << " was overwritten by " << res << endl;
      *found = res;
    }

    return found;
  }
  
  
  Model::iterator
  Model::erase (iterator pos)
  {
    delete &*pos;
    return iterator (residues.erase (pos));
  }
  
    
  void
  Model::sort ()
  {
    std::sort (residues.begin (), residues.end (), less_deref< Residue > ());
  }
  
  
  void 
  Model::clear ()
  {
    vector< Residue* >::iterator it;
    
    for (it = residues.begin (); it != residues.end (); ++it)
      {
	delete *it;
      }
    residues.clear ();    
  }
  
  
  ostream& 
  Model::output (ostream &os) const
  {
    const_iterator cit;
    
    os << "MODEL (size=" << flush << size () << ") :" << flush;
    for (cit = begin (); cit != end (); ++cit)
      {
	os << cit->getResId ()  << " ";
      }
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
	
 	if (res->size () != 0)
	  {
	    // Optimized insertion that bypasses the copy: 
	    residues.push_back (res); 
	  }
	else
	  {
	    delete res;
	  }
      }    
    return ips;
  }
  
  
  oBinstream& 
  Model::output (oBinstream &obs) const
  {
    const_iterator cit;
    
    obs << (mccore::bin_ui64)size ();
    for (cit = begin (); cit != end (); ++cit)
      {
	obs << *cit;
      }
    return obs;
  }
  
  
  iBinstream& 
  Model::input (iBinstream &ibs)
  {
    mccore::bin_ui64 sz = 0;
    Residue *res;

    clear ();

    for (ibs >> sz; sz > 0; --sz)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)sz << " to go.";
	throw ex;
      }     

      res = getResidueFM ()->createResidue ();
      ibs >> *res;
      // Optimized insertion that bypasses the copy: 
      residues.push_back (res); 
    }
    return ibs;
  }
  
}
