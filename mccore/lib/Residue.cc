//                              -*- Mode: C++ -*- 
// Residue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
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

#include "Residue.h"


namespace mccore {
  
  // LIFECYCLE -----------------------------------------------------------------

  Residue::Residue () 
    : BasicResidue (), placed (true)
  {      
  }


  Residue::Residue (const ResidueType *t, const ResId &i) 
    : BasicResidue (t, i) , placed (true)
  {
  } 
  

  Residue::Residue (const Residue &other)
    : BasicResidue (other)
  {
    vector< Atom* >::const_iterator cit;
    
    for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
      atomLocal.push_back ((*cit)->clone ());

    tfo = other.tfo;
    placed = other.placed;
  }


  BasicResidue* 
  Residue::clone () const 
  { 
    return new Residue (*this); 
  }
  
  
  Residue::~Residue () 
  {
    clear ();
  }


  // OPERATORS -----------------------------------------------------------------


  Residue& 
  Residue::operator= (const Residue &other)
  {
    vector< Atom* >::const_iterator cit;

    if (this != &other) {
      clear ();
      BasicResidue::operator= (other);

      for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
	atomLocal.push_back ((*cit)->clone ());
      tfo = other.tfo;
      placed = other.placed;
    }
    return *this;
  }


  // ACCESS --------------------------------------------------------------------


  Residue::iterator 
  Residue::begin (AtomSet *atomset) 
  {
    return iterator (this, atomIndex.begin (), atomset);
  }
  
  
  Residue::iterator 
  Residue::end () 
  {
    return iterator (this, atomIndex.end ()); 
  }
  

  Residue::const_iterator 
  Residue::begin (AtomSet *atomset) const 
  {
    return const_iterator (this, atomIndex.begin (), atomset);
  }


  Residue::const_iterator 
  Residue::end () const 
  {
    return const_iterator (this, atomIndex.end ()); 
  }
  
  
  Residue::iterator 
  Residue::find (const AtomType *k) 
  {
    AtomMap::iterator it = atomIndex.find (k);
    if (it == atomIndex.end ())
      return end ();
    else
      return iterator (this, it);
  }


  Residue::const_iterator 
  Residue::find (const AtomType *k) const
  {
    AtomMap::const_iterator cit = atomIndex.find (k);
    if (cit == atomIndex.end ())
      return end ();
    else
      return const_iterator (this, cit);
  }

  
  bool 
  Residue::contains (const AtomType *k) const 
  { 
    return find (k) != end (); 
  }
  

  // METHODS -------------------------------------------------------------------


  const HomogeneousTransfo&
  Residue::getReferential (HomogeneousTransfo *t) const
  {
    return tfo; 
  }


  void 
  Residue::setReferential (const HomogeneousTransfo& m) 
  { 
    tfo = m; 
    displace ();
  }
  

  const Residue& 
  Residue::transform (const HomogeneousTransfo &aTransfo) 
  {
    setReferential (aTransfo * getReferential());
    return *this;
  }


  void 
  Residue::insert (const Atom &atom)
  {    
    AtomMap::iterator it;
    it = atomIndex.find (atom.getType ());
    int pos = size ();

    if (it==atomIndex.end ()) {
      atomIndex[atom.getType ()] = pos;
      atomLocal.push_back (atom.clone ());
      atomGlobal.push_back (atom.clone ());
      it = atomIndex.find (atom.getType ());
    } else {
      *atomLocal[it->second] = atom;
    }

    // Transform the atom to the origin
    if (!tfo.isIdentity ()) {
      (*atomLocal[it->second]).transform (tfo.invert ());
    }
  }


  Atom& 
  Residue::get (size_type pos) const
  {
    assert (pos < atomGlobal.size ());
    place ();
    return *atomGlobal[pos];
  }


  Residue::iterator 
  Residue::erase (const AtomType *type)
  {
    AtomMap::iterator i = atomIndex.find (type);
    
    if (i!=atomIndex.end ()) {
      vector< Atom* >::const_iterator cit;
      const AtomType* next;
      size_type index;
      
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


  Residue::iterator 
  Residue::erase (const iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  Residue::iterator 
  Residue::erase (const const_iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  int 
  Residue::size () const 
  { 
    return atomIndex.size (); 
  }


  bool 
  Residue::empty () const 
  { 
    return size () == 0; 
  }


  void 
  Residue::clear() {
    BasicResidue::clear ();
    vector< Atom* >::iterator it;
    for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
      delete *it;
    atomLocal.clear ();
    tfo.setIdentity ();
  }


  // PRIVATE METHODS------------------------------------------------------------

  void Residue::place () const
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
  
  void Residue::displace () const
  {
    placed=false;
    place ();
  }


  void Residue::finalize ()
  {
    unsigned int i;
    Vector3D *pivot[3];
    Vector3D *v1, *v2, *v3;

    // Some checks...
    if (type == 0 || empty ()) return;
    
    /* Compute the location of the pseudo atoms. */
    if (((v1 = get (AtomType::aN9)) != 0 
	 && (v2 = get (AtomType::aC8)) != 0 
	 && (v3 = get (AtomType::aC4)) != 0)
	|| ((v1 = get (AtomType::aN1)) != 0 
	    && (v2 = get (AtomType::aC6)) != 0 
	    && (v3 = get (AtomType::aC2)) != 0)) {
      Vector3D a, b, y, z;
      
      a = (*v2-*v1).normalize();
      b = (*v3-*v1).normalize();
      y = *v1 + (a + b).normalize();
      z = *v1 + (b.cross(a)).normalize();
      
      insert (Atom (y, AtomType::aPSY));
      insert (Atom (z, AtomType::aPSZ));

    } else if (type->isAminoAcid ()) {
      if ((v1 = get (AtomType::aCA)) != 0 &&
	  (v2 = get (AtomType::aN)) != 0 &&
	  (v3 = get (AtomType::aC)) != 0) {
	Vector3D a, b, z;
	a = (*v2 - *v1).normalize();
	b = (*v3 - *v1).normalize();
	z = *v1 + (b.cross(a)).normalize();
	
	insert (Atom(z, AtomType::aPSAZ));
      } else {
	cerr << "Residue " << getResId () << "-" << getType()
	  << " is missing one or more critical atoms." << endl;		
      }	
    }
    
    /* Set the pivots */
    if ((get (AtomType::aN9) != 0 || get (AtomType::aN1) != 0) 
	&& get (AtomType::aPSY) != 0
	&& get (AtomType::aPSZ) != 0) {
      pivot[0] = get (AtomType::aN9) != 0 ? get (AtomType::aN9) : get (AtomType::aN1);
      pivot[1] = get (AtomType::aPSY);
      pivot[2] = get (AtomType::aPSZ);	   
    } else if (type->isAminoAcid ()) {
      pivot[0] = get (AtomType::aCA);
      pivot[1] = get (AtomType::aN);
      pivot[2] = get (AtomType::aPSAZ);
    } else if (type->isPhosphate ()) {
      pivot[0] = get (AtomType::aP);
      pivot[1] = get (AtomType::aO3p);
      pivot[2] = get (AtomType::aO5p);      
    } else if (size() >= 3) {
      pivot[0] = (Atom*) atomGlobal[0];
      pivot[1] = (Atom*) atomGlobal[1];
      pivot[2] = (Atom*) atomGlobal[2];
    } else {
      pivot[0] = 0;
      pivot[1] = 0;
      pivot[2] = 0;
      //cerr << "Warning, residue has less than 3 atoms: " << getType () << endl;
    }
    
    /* Align the residue to the origin. */
    if (pivot[0] != 0 && pivot[1] != 0 && pivot[2] != 0) {
      tfo = HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);
      HomogeneousTransfo inv = tfo.invert ();
      
      for (i=0; i<atomLocal.size (); ++i) {
	*atomLocal[i] = *atomGlobal[i];
	atomLocal[i]->transform (inv);
      }
    }	
  }


  Atom* 
  Residue::get (const AtomType* type) const 
  {
    place ();
    AtomMap::const_iterator it = atomIndex.find (type);
    if (it == atomIndex.end ())
      return 0;
    else
      return atomGlobal[it->second];
  }

  // I/O -----------------------------------------------------------------------


  ostream&
  Residue::output (ostream &os) const 
  {
    place ();
    os << resId << type;
//     os << endl << tfo;
//     AtomMap::const_iterator cit;
//     os << "\n\tLocal coordinates\t\tGlobal coordinates";
//     for (cit=atomIndex.begin (); cit!=atomIndex.end (); ++cit) {
//       os << "\n\t" << *(atomLocal[cit->second]) << "\t" << *(atomGlobal[cit->second]) << flush;
//     }
    return os;
  }
  
}
