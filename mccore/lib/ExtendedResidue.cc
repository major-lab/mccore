//                              -*- Mode: C++ -*- 
// ExtendedResidue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.20 $
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
  
  
  ExtendedResidue::iterator 
  ExtendedResidue::find (const AtomType *k) 
  {
    AtomMap::iterator it = atomIndex.find (k);
    if (it == atomIndex.end ())
      return end ();
    else
      return iterator (this, it);
  }


  ExtendedResidue::const_iterator 
  ExtendedResidue::find (const AtomType *k) const
  {
    AtomMap::const_iterator cit = atomIndex.find (k);
    if (cit == atomIndex.end ())
      return end ();
    else
      return const_iterator (this, cit);
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
  
 //  void ExtendedResidue::finalize ()
//   {
//     unsigned int i;
//     Vector3D *pivot[3];
//     Vector3D *v1, *v2, *v3;

//     if (!type || empty ()) return;

//     if (!getType ()->isPhosphate ()) {
 
//       /* Compute the location of the pseudo atoms. */
//       if (((v1 = _get (AtomType::aN9)) != 0 
// 	   && (v2 = _get (AtomType::aC8)) != 0 
// 	   && (v3 = _get (AtomType::aC4)) != 0)
// 	  || ((v1 = _get (AtomType::aN1)) != 0 
// 	      && (v2 = _get (AtomType::aC6)) != 0 
// 	      && (v3 = _get (AtomType::aC2)) != 0)) {
// 	Vector3D a, b, y, z;
      
// 	a = (*v2-*v1).normalize();
// 	b = (*v3-*v1).normalize();
// 	y = *v1 + (a + b).normalize();
// 	z = *v1 + (b.cross(a)).normalize();
      
// 	insert (Atom (y, AtomType::aPSY));
// 	insert (Atom (z, AtomType::aPSZ));

//       } else if (type->isAminoAcid ()) {
// 	if ((v1 = _get (AtomType::aCA)) != 0 &&
// 	    (v2 = _get (AtomType::aN)) != 0 &&
// 	    (v3 = _get (AtomType::aC)) != 0) {
// 	  Vector3D a, b, z;
// 	  a = (*v2 - *v1).normalize();
// 	  b = (*v3 - *v1).normalize();
// 	  z = *v1 + (b.cross(a)).normalize();
	
// 	  insert (Atom(z, AtomType::aPSAZ));
// 	} else {
// 	  gOut (4) << "Residue " << getResId () << "-" << *getType ()
// 		   << " is missing one or more critical atoms." << endl;	
// 	}	
//       }

//     }
    
//     /* Set the pivots */
//     if ((_get (AtomType::aN9) != 0 || _get (AtomType::aN1) != 0) 
// 	&& _get (AtomType::aPSY) != 0
// 	&& _get (AtomType::aPSZ) != 0) {
//       pivot[0] = _get (AtomType::aN9) != 0 ? _get (AtomType::aN9) : _get (AtomType::aN1);
//       pivot[1] = _get (AtomType::aPSY);
//       pivot[2] = _get (AtomType::aPSZ);	   
//     } else if (type->isAminoAcid ()) {
//       pivot[0] = _get (AtomType::aCA);
//       pivot[1] = _get (AtomType::aN);
//       pivot[2] = _get (AtomType::aPSAZ);
//     } else if (type->isPhosphate ()) {
//       pivot[0] = _get (AtomType::aP);
//       pivot[1] = _get (AtomType::aO3p);
//       pivot[2] = _get (AtomType::aO5p);      
//     } else if (size() >= 3) {
//       pivot[0] = (Atom*) atomGlobal[0];
//       pivot[1] = (Atom*) atomGlobal[1];
//       pivot[2] = (Atom*) atomGlobal[2];
//     } else {
//       pivot[0] = 0;
//       pivot[1] = 0;
//       pivot[2] = 0;
//       gOut (4) << "Residue " << *getType () << " " << getResId () 
// 	       << " has less than 3 atoms and cannot be moved: " << endl;
//     }
    
//     /* Align the residue to the origin. */
//     if (pivot[0] != 0 && pivot[1] != 0 && pivot[2] != 0) {
//       tfo = HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);
//       HomogeneousTransfo inv = tfo.invert ();
      
//       for (i=0; i<atomLocal.size (); ++i) {
// 	*atomLocal[i] = *atomGlobal[i];
// 	atomLocal[i]->transform (inv);
//       }
//     }	
//   }


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
