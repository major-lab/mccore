//                              -*- Mode: C++ -*- 
// ExtendedResidue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.24 $
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

#include "ExtendedResidue.h"
#include "Messagestream.h"
#include "Exception.h"
#include "stlio.h"

namespace mccore {
  
  // LIFECYCLE -----------------------------------------------------------------

  ExtendedResidue::ExtendedResidue () 
    : Residue (), placed (true)
  {

  }


  ExtendedResidue::ExtendedResidue (const ResidueType *t, const ResId &i) 
    : Residue (t, i) , placed (true)
  {

  } 
  
  ExtendedResidue::ExtendedResidue (const ResidueType *t, const ResId &i, vector< Atom > &vec)
    : Residue (t, i, vec) , placed (true)
  {

  }

  ExtendedResidue::ExtendedResidue (const ExtendedResidue &other)
    : Residue (other)
  {
    vector< Atom* >::const_iterator cit;
    
    for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
      this->atomLocal.push_back ((*cit)->clone ());

    this->tfo = other.tfo;
    this->placed = other.placed;
  }


  Residue* 
  ExtendedResidue::clone () const 
  { 
    return new ExtendedResidue (*this); 
  }
  
  
  ExtendedResidue::~ExtendedResidue () 
  {
    this->clear ();
  }


  // OPERATORS -----------------------------------------------------------------


  ExtendedResidue& 
  ExtendedResidue::operator= (const ExtendedResidue &other)
  {
    vector< Atom* >::const_iterator cit;

    if (this != &other)
    {
      this->clear ();
      this->Residue::operator= (other);

      for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
	this->atomLocal.push_back ((*cit)->clone ());
      this->tfo = other.tfo;
      this->placed = other.placed;
    }
    return *this;
  }


  // ACCESS --------------------------------------------------------------------

  
  
  // METHODS -------------------------------------------------------------------


  const HomogeneousTransfo
  ExtendedResidue::getReferential () const
  {
    return this->tfo; 
  }


  void 
  ExtendedResidue::setReferential (const HomogeneousTransfo& m) 
  { 
    this->tfo = m; 
    this->_displace ();
  }
  

  void 
  ExtendedResidue::insert (const Atom &atom)
  {
    int pos = this->size ();
    pair< AtomMap::iterator, bool > inserted =
      this->atomIndex.insert (make_pair (atom.getType (), pos));

    if (inserted.second)
      {
	this->atomLocal.push_back (atom.clone ());
	this->atomGlobal.push_back (atom.clone ());
	this->rib_dirty_ref = true;
      }
    else
      {
	*this->atomLocal[inserted.first->second] = atom;
	*this->atomGlobal[inserted.first->second] = atom;
      }

    if (!this->tfo.isIdentity ())
      (*this->atomLocal[inserted.first->second]).transform (this->tfo.invert ());
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const iterator& rit)
  { 
    if (this->end () != rit)
    {
      vector< Atom* >::iterator avit;
      vector< Atom* >::const_iterator cavit;
      const AtomType* next = 0;
      size_type index = 0;
      iterator next_rit = rit + 1;

      // invalidate ribose pointers
      this->rib_dirty_ref = true;
      
      // get next atom type before deletion
      if (this->end () != next_rit)
	next = next_rit.pos->first;
      
      // delete atom
      avit = this->atomGlobal.begin () + rit.pos->second;
      delete *avit;
      this->atomGlobal.erase (avit);
      avit = this->atomLocal.begin () + rit.pos->second;
      delete *avit;
      this->atomLocal.erase (avit);

      // fix atom map
      this->atomIndex.clear ();
      for (cavit = this->atomGlobal.begin (); cavit != this->atomGlobal.end (); ++cavit, ++index)
	this->atomIndex.insert (make_pair ((*cavit)->getType (), index));

      if (next)
      {
	// fetch iterator to saved atom type and set its filter.
	next_rit = this->find (next);
	delete next_rit.filter;
	next_rit.filter = rit.filter->clone ();
	return next_rit;
      }
    }
    return this->end ();  
  }


  void 
  ExtendedResidue::clear()
  {
    this->Residue::clear ();
    vector< Atom* >::iterator it;
    for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
      delete *it;
    this->atomLocal.clear ();
    this->tfo.setIdentity ();
  }

  
  void
  ExtendedResidue::finalize ()
  {
    // set pseudo-atoms
    this->Residue::finalize ();

    // set referential
    this->tfo = this->_compute_referential ();

    // set local atoms in referential's origin
    unsigned int i;
    HomogeneousTransfo inv (this->tfo.invert ());
    for (i = 0; i < this->atomLocal.size (); ++i)
      {
	*this->atomLocal[i] = *this->atomGlobal[i];
	this->atomLocal[i]->transform (inv);
      }
  }

  
  void ExtendedResidue::atomCopy (const Residue& other) 
  {


    const ExtendedResidue *resp = dynamic_cast< const ExtendedResidue* > (&other);

    if (this != &other && resp) {
      if (type != resp->getType ()) {
	LibException exc ("Invalid residue type ");
	
	exc << *resp->getType () << ".";
	throw exc;
      }
      
      unsigned int i;
      for (i=0; i<atomLocal.size (); ++i) {
	*atomLocal[i] = *resp->atomLocal[i];
	*atomGlobal[i] = *resp->atomGlobal[i];
      }

      placed = true;
      tfo = resp->tfo;      
    } else {
      if (this != &other) {
	if (type != other.getType ()) {
	  LibException exc ("Invalid residue type ");
	  
	  exc << *other.getType () << ".";
	  throw exc;
	}
	
	tfo = other.getReferential ();
	placed = true;

	HomogeneousTransfo tfoi = tfo.invert ();
	unsigned int i;
	for (i = 0; i < this->atomLocal.size (); ++i)
	{
	  *this->atomGlobal[i] = *(other.atomGlobal[i]);
	  *this->atomLocal[i] = *(other.atomGlobal[i]);
	  this->atomLocal[i]->transform (tfoi);
	}
	
      } 
    }
  }

  // PRIVATE METHODS------------------------------------------------------------

  Atom*
  ExtendedResidue::_get_or_create (const AtomType *aType)
  {
    // ribose pointers to local container!
    
    int pos = this->size ();
    pair< AtomMap::iterator, bool > inserted =
      this->atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
      {
	this->atomLocal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	this->atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	this->rib_dirty_ref = true;
	return atomLocal[pos];
      }
    else
      {
	return this->atomLocal[inserted.first->second];
      }
  }

  
  void
  ExtendedResidue::_place () const
  {
    if (false == this->placed)
    {
      vector< Atom* >::const_iterator cit;
      vector< Atom* >::iterator it;
    
      for (cit = this->atomLocal.begin (), it = this->atomGlobal.begin ();
	   cit != this->atomLocal.end ();
	   ++cit, ++it)
	{
	  **it = **cit;
	  (*it)->transform (tfo);
	}      
      this->placed = true;
    }
  }
  
  void ExtendedResidue::_displace () const
  {
    this->placed = false;
    this->_place ();
  }

  void
  ExtendedResidue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
					      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential

    // TODO: place only ribose atoms...
    this->_displace (); // -> place all atoms :(
    this->_add_ribose_hydrogens (true);
  }
  
  // I/O -----------------------------------------------------------------------
  
}
