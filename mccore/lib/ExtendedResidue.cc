//                              -*- Mode: C++ -*- 
// ExtendedResidue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.21 $
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
      atomLocal.push_back ((*cit)->clone ());

    tfo = other.tfo;
    placed = other.placed;
  }


  Residue* 
  ExtendedResidue::clone () const 
  { 
    return new ExtendedResidue (*this); 
  }
  
  
  ExtendedResidue::~ExtendedResidue () 
  {
    vector< Atom* >::iterator it;
    for (it = atomLocal.begin (); it != atomLocal.end (); ++it) {
      delete *it;
    }
    atomLocal.clear ();
    tfo.setIdentity ();
  }


  // OPERATORS -----------------------------------------------------------------


  ExtendedResidue& 
  ExtendedResidue::operator= (const ExtendedResidue &other)
  {
    vector< Atom* >::const_iterator cit;

    if (this != &other) {
      clear ();
      Residue::operator= (other);

      for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
	atomLocal.push_back ((*cit)->clone ());
      tfo = other.tfo;
      placed = other.placed;
    }
    return *this;
  }


  // ACCESS --------------------------------------------------------------------


  ExtendedResidue::iterator 
  ExtendedResidue::begin (AtomSet *atomset) 
  {
    return iterator (this, atomIndex.begin (), atomset);
  }
  
  
  ExtendedResidue::iterator 
  ExtendedResidue::end () 
  {
    return iterator (this, atomIndex.end ()); 
  }
  

  ExtendedResidue::const_iterator 
  ExtendedResidue::begin (AtomSet *atomset) const 
  {
    return const_iterator (this, atomIndex.begin (), atomset);
  }


  ExtendedResidue::const_iterator 
  ExtendedResidue::end () const 
  {
    return const_iterator (this, atomIndex.end ()); 
  }
  
  
  bool 
  ExtendedResidue::contains (const AtomType *k) const 
  { 
    return find (k) != end (); 
  }
  

  // METHODS -------------------------------------------------------------------


  const HomogeneousTransfo
  ExtendedResidue::getReferential () const
  {
    return tfo; 
  }


  void 
  ExtendedResidue::setReferential (const HomogeneousTransfo& m) 
  { 
    tfo = m; 
    displace ();
  }
  

  void
  ExtendedResidue::transform (const HomogeneousTransfo &aTransfo) 
  {
    setReferential (aTransfo * getReferential());
  }


  void 
  ExtendedResidue::insert (const Atom &atom)
  {
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (atom.getType (), pos));

    if (inserted.second)
      {
	atomLocal.push_back (atom.clone ());
	atomGlobal.push_back (atom.clone ());
	rib_dirty_ref = true;
      }
    else
      {
	*atomLocal[inserted.first->second] = atom;
	*atomGlobal[inserted.first->second] = atom;
      }

    if (!tfo.isIdentity ())
      (*atomLocal[inserted.first->second]).transform (tfo.invert ());
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const AtomType *aType)
  {
    AtomMap::iterator i = atomIndex.find (aType);
    
    if (i!=atomIndex.end ()) {
      vector< Atom* >::const_iterator cit;
      const AtomType* next;
      size_type index;

      rib_dirty_ref = true;
      
      delete atomGlobal[i->second];
      atomGlobal.erase (atomGlobal.begin () + i->second);
      delete atomLocal[i->second];
      atomLocal.erase (atomLocal.begin () + i->second);

      next = ++i == atomIndex.end () ? 0 : i->first;
      atomIndex.clear ();
      for (cit = atomLocal.begin (), index = 0;
	   cit != atomLocal.end ();
	   ++cit, ++index)
	atomIndex[(*cit)->getType ()] = index;
      
      return find (next);
    } 
    return end ();
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const const_iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  int 
  ExtendedResidue::size () const 
  { 
    return atomIndex.size (); 
  }


  bool 
  ExtendedResidue::empty () const 
  { 
    return size () == 0; 
  }


  void 
  ExtendedResidue::clear()
  {
    Residue::clear ();
    vector< Atom* >::iterator it;
    for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
      delete *it;
    atomLocal.clear ();
    tfo.setIdentity ();
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
	for (i=0; i<atomLocal.size (); ++i) {
	  *atomGlobal[i] = *(other.atomGlobal[i]);
	  *atomLocal[i] = *(other.atomGlobal[i]);
	  atomLocal[i]->transform (tfoi);
	}
	
      } 
    }
  }

  // PRIVATE METHODS------------------------------------------------------------

  Atom*
  ExtendedResidue::_get_or_create (const AtomType *aType)
  {
    // ribose pointers to local container!
    
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
      {
	atomLocal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	rib_dirty_ref = true;
	return atomLocal[pos];
      }
    else
      {
	return atomLocal[inserted.first->second];
      }
  }

  
  void
  ExtendedResidue::_insert_local (const Vector3D& coord, AtomMap::iterator posit)
  {
    atomLocal[posit->second]->set (coord.getX (), coord.getY (), coord.getZ ());
    atomGlobal[posit->second]->set (coord.getX (), coord.getY (), coord.getZ ());
    atomGlobal[posit->second]->transform (tfo);
  }

  
  void
  ExtendedResidue::place () const
  {
    if (!isPlaced ()) {

      vector< Atom* >::const_iterator cit;
      vector< Atom* >::iterator it;
    
      for (cit = atomLocal.begin (), it = atomGlobal.begin ();
	   cit != atomLocal.end ();
	   ++cit, ++it)
	{
	  **it = **cit;
	  (*it)->transform (tfo);
	}      
      placed = true;
    }
  }
  
  void ExtendedResidue::displace () const
  {
    placed=false;
    place ();
  }

  void
  ExtendedResidue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
					      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential

    // TODO: place only ribose atoms...
    displace (); // -> place all atoms :(
    _add_ribose_hydrogens ();
  }
  
  // I/O -----------------------------------------------------------------------


  ostream&
  ExtendedResidue::output (ostream &os) const 
  {    
//     os << &resId << endl;
    os << resId << type;
//     os << endl << tfo;
//     os << endl;
//     AtomMap::const_iterator cit;
//     os << "\n\tLocal coordinates\t\tGlobal coordinates";
//     for (cit=atomIndex.begin (); cit!=atomIndex.end (); ++cit) {
//       os << "\n\t" 
// 	 << atomLocal[cit->second] << " " << *(atomLocal[cit->second]) << " \t " 
// 	 << atomGlobal[cit->second] << " " << *(atomGlobal[cit->second]) 
// 	 << ((!isPlaced ())?" [invalid]":"") << flush;
//     }
    return os;
  }
  
}
