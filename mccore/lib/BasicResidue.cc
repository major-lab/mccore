//                              -*- Mode: C++ -*- 
// BasicResidue.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar 14 16:44:35 2003
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

#include <algorithm>

#include "BasicResidue.h"
#include "ResidueTopology.h"
#include "ResId.h"
#include "Binstream.h"
#include "PropertyType.h"

namespace mccore {


  // LIFECYCLE -----------------------------------------------------------------


  BasicResidue::BasicResidue ()
    : type (0)
  {
  }


  BasicResidue::BasicResidue (const ResidueType *t, const ResId &i)
    : type (t), resId (i) 
  {
  }


  BasicResidue::BasicResidue (const BasicResidue &other)
  {
    vector< Atom* >::const_iterator cit;
    type = other.type;
    resId = other.resId;
    
    for (cit = other.atomGlobal.begin (); cit != other.atomGlobal.end (); ++cit)
      atomGlobal.push_back ((*cit)->clone ());
    
    atomIndex = other.atomIndex;
  }

  
  BasicResidue* 
  BasicResidue::clone () const 
  { 
    return new BasicResidue (*this); 
  }
  

  BasicResidue::~BasicResidue () 
  {
    clear ();
  }


  bool 
  BasicResidue::setIdeal ()
  {
    if (!type->isNucleicAcid ()) return false;

    clear ();

    if (type == ResidueType::rRA || type == ResidueType::rDA) {
      insert (Atom (0.213f, 0.660f, 1.287f, AtomType::aN9));
      insert (Atom (0.250f, 2.016f, 1.509f, AtomType::aC4));
      insert (Atom (0.016f, 2.995f, 0.619f, AtomType::aN3));
      insert (Atom (0.142f, 4.189f, 1.194f, AtomType::aC2));
      insert (Atom (0.451f, 4.493f, 2.459f, AtomType::aN1));
      insert (Atom (0.681f, 3.485f, 3.329f, AtomType::aC6));
      insert (Atom (0.990f, 3.787f, 4.592f, AtomType::aN6));
      insert (Atom (0.579f, 2.170f, 2.844f, AtomType::aC5));
      insert (Atom (0.747f, 0.934f, 3.454f, AtomType::aN7));
      insert (Atom (0.520f, 0.074f, 2.491f, AtomType::aC8));
      insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));
    } else if (type == ResidueType::rRC || type == ResidueType::rDC) {
      insert (Atom (0.212f, 0.668f, 1.294f, AtomType::aN1)); 
      insert (Atom (0.193f, -0.043f, 2.462f, AtomType::aC6));
      insert (Atom (0.374f, 2.055f, 1.315f, AtomType::aC2)); 
      insert (Atom (0.388f, 2.673f, 0.240f, AtomType::aO2)); 
      insert (Atom (0.511f, 2.687f, 2.504f, AtomType::aN3)); 
      insert (Atom (0.491f, 1.984f, 3.638f, AtomType::aC4)); 
      insert (Atom (0.631f, 2.649f, 4.788f, AtomType::aN4)); 
      insert (Atom (0.328f, 0.569f, 3.645f, AtomType::aC5)); 
      insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));
    } else if (type == ResidueType::rRG || type == ResidueType::rDG) {
      insert (Atom (0.214f, 0.659f, 1.283f, AtomType::aN9)); 
      insert (Atom (0.254f, 2.014f, 1.509f, AtomType::aC4)); 
      insert (Atom (0.034f, 2.979f, 0.591f, AtomType::aN3)); 
      insert (Atom (0.142f, 4.190f, 1.110f, AtomType::aC2)); 
      insert (Atom (-0.047f, 5.269f, 0.336f, AtomType::aN2)); 
      insert (Atom (0.444f, 4.437f, 2.427f, AtomType::aN1)); 
      insert (Atom (0.676f, 3.459f, 3.389f, AtomType::aC6)); 
      insert (Atom (0.941f, 3.789f, 4.552f, AtomType::aO6)); 
      insert (Atom (0.562f, 2.154f, 2.846f, AtomType::aC5)); 
      insert (Atom (0.712f, 0.912f, 3.448f, AtomType::aN7)); 
      insert (Atom (0.498f, 0.057f, 2.485f, AtomType::aC8)); 
      insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));
    } else if (type == ResidueType::rRU) {
      insert (Atom (0.212f, 0.676f, 1.281f, AtomType::aN1)); 
      insert (Atom (0.195f, -0.023f, 2.466f, AtomType::aC6));
      insert (Atom (0.370f, 2.048f, 1.265f, AtomType::aC2)); 
      insert (Atom (0.390f, 2.698f, 0.235f, AtomType::aO2)); 
      insert (Atom (0.505f, 2.629f, 2.502f, AtomType::aN3)); 
      insert (Atom (0.497f, 1.990f, 3.725f, AtomType::aC4)); 
      insert (Atom (0.629f, 2.653f, 4.755f, AtomType::aO4)); 
      insert (Atom (0.329f, 0.571f, 3.657f, AtomType::aC5)); 
      insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));
    } else if (type == ResidueType::rDT) {
      insert (Atom (0.214f, 0.668f, 1.296f, AtomType::aN1)); 
      insert (Atom (0.171f, -0.052f, 2.470f, AtomType::aC6)); 
      insert (Atom (0.374f, 2.035f, 1.303f, AtomType::aC2)); 
      insert (Atom (0.416f, 2.705f, 0.284f, AtomType::aO2)); 
      insert (Atom (0.483f, 2.592f, 2.553f, AtomType::aN3)); 
      insert (Atom (0.449f, 1.933f, 3.767f, AtomType::aC4)); 
      insert (Atom (0.560f, 2.568f, 4.812f, AtomType::aO4)); 
      insert (Atom (0.279f, 0.500f, 3.685f, AtomType::aC5)); 
      insert (Atom (0.231f, -0.299f, 4.949f, AtomType::aC5M)); 
      insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));	    
    } else {
      return false;
    }

    if (type->isRNA ()) {
      insert (Atom ( 4.691f,  0.327f, -2.444f, AtomType::aP));
      insert (Atom ( 5.034f,  1.678f, -1.932f, AtomType::aO1P));
      insert (Atom ( 4.718f,  0.068f, -3.906f, AtomType::aO2P));
      insert (Atom ( 3.246f, -0.057f, -1.895f, AtomType::aO5p));
      insert (Atom ( 2.957f, -1.393f, -1.443f, AtomType::aC5p));
      insert (Atom ( 1.509f, -1.478f, -1.022f, AtomType::aC4p));
      insert (Atom ( 1.286f, -0.587f,  0.103f, AtomType::aO4p));
      insert (Atom ( 0.000f,  0.000f,  0.000f, AtomType::aC1p));
      insert (Atom (-0.694f, -0.627f, -1.210f, AtomType::aC2p));
      insert (Atom (-1.474f, -1.731f, -0.795f, AtomType::aO2p));
      insert (Atom ( 0.499f, -1.031f, -2.067f, AtomType::aC3p));
      insert (Atom ( 0.178f, -2.084f, -2.981f, AtomType::aO3p));
    } else if (type->isDNA ()) {
      insert (Atom (  0.224f,  -4.365f,   2.383f, AtomType::aP));
      insert (Atom (  1.336f,  -3.982f,   3.290f, AtomType::aO1P));
      insert (Atom (  0.278f,  -5.664f,   1.666f, AtomType::aO2P));
      insert (Atom (  0.042f,  -3.205f,   1.307f, AtomType::aO5p));
      insert (Atom (  1.149f,  -0.891f,  -0.438f, AtomType::aC2p));
      insert (Atom ( -1.014f,  -3.256f,   0.347f, AtomType::aC5p));
      insert (Atom ( -0.913f,  -2.083f,  -0.600f, AtomType::aC4p));
      insert (Atom ( -1.127f,  -0.853f,   0.133f, AtomType::aO4p));
      insert (Atom (  0.000f,   0.000f,   0.000f, AtomType::aC1p));
      insert (Atom (  0.445f,  -1.932f,  -1.287f, AtomType::aC3p));
      insert (Atom (  0.272f,  -1.450f,  -2.624f, AtomType::aO3p));	    
    } else {
      return false;
    }

    finalize ();
    addHydrogens();
    addLonePairs();

    return true;    
  }


  // OPERATORS -----------------------------------------------------------------


  BasicResidue& 
  BasicResidue::operator= (const BasicResidue &other)
  {
    vector< Atom* >::const_iterator cit;

    if (this != &other) {
      type = other.type;
      resId = other.resId;
      clear ();
      for (cit = other.atomGlobal.begin (); cit != other.atomGlobal.end (); ++cit)
	atomGlobal.push_back ((*cit)->clone ());
    }
    return *this;
  }

  
  bool 
  BasicResidue::operator== (const BasicResidue &other) const
  { 
    return resId == other.resId 
      && *type == *other.getType (); 
  }
  

  bool 
  BasicResidue::operator!= (const BasicResidue &other) const 
  { 
    return ! operator== (other); 
  }
  
  
  bool 
  BasicResidue::operator< (const BasicResidue &other) const
  { 
    return resId < other.resId; 
  }


  // ACCESS --------------------------------------------------------------------


  const ResId& 
  BasicResidue::getResId () const 
  { 
    return resId; 
  }


  void 
  BasicResidue::setResId (const ResId& id) 
  { 
    resId = id; 
  }


  const ResidueType* 
  BasicResidue::getType() const 
  { 
    return type; 
  }


  void 
  BasicResidue::setType (const ResidueType* t) 
  { 
    type = t; 
  }

  
  BasicResidue::iterator 
  BasicResidue::begin (AtomSet *atomset) 
  {
    return iterator (this, atomIndex.begin (), atomset);
  }
  
  
  BasicResidue::iterator 
  BasicResidue::end () 
  {
    return iterator (this, atomIndex.end ()); 
  }
  

  BasicResidue::const_iterator 
  BasicResidue::begin (AtomSet *atomset) const 
  {
    return const_iterator (this, atomIndex.begin (), atomset);
  }


  BasicResidue::const_iterator 
  BasicResidue::end () const 
  {
    return const_iterator (this, atomIndex.end ()); 
  }
  
  
  BasicResidue::iterator 
  BasicResidue::find (const AtomType *k) 
  {
    AtomMap::iterator it = atomIndex.find (k);
    if (it == atomIndex.end ())
      return end ();
    else
      return iterator (this, it);
  }


  BasicResidue::const_iterator 
  BasicResidue::find (const AtomType *k) const
  {
    AtomMap::const_iterator cit = atomIndex.find (k);
    if (cit == atomIndex.end ())
      return end ();
    else
      return const_iterator (this, cit);
  }

  
  bool 
  BasicResidue::contains (const AtomType *k) const 
  { 
    return find (k) != end (); 
  }
  

  // METHODS -------------------------------------------------------------------


  const HomogeneousTransfo&
  BasicResidue::getReferential (HomogeneousTransfo *t) const
  {
    Vector3D *pivot[3];
    assert (t!=0);

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
    } else if (size() >= 3) {
      pivot[0] = (Atom*) atomGlobal[0];
      pivot[1] = (Atom*) atomGlobal[1];
      pivot[2] = (Atom*) atomGlobal[2];
    } else {
      pivot[0] = 0;
      pivot[1] = 0;
      pivot[2] = 0;
      cerr << "Warning, residue has less than 3 atoms: " << getType () << endl;
    }

    if (pivot[0] != 0 && pivot[1] != 0 && pivot[2] != 0) {
      *t = HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);
    }
    return *t; 
  }


  void 
  BasicResidue::setReferential (const HomogeneousTransfo& m) 
  {
    Vector3D *pivot[3];
    HomogeneousTransfo curr;

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
    } else if (size() >= 3) {
      pivot[0] = (Atom*) atomGlobal[0];
      pivot[1] = (Atom*) atomGlobal[1];
      pivot[2] = (Atom*) atomGlobal[2];
    } else {
      pivot[0] = 0;
      pivot[1] = 0;
      pivot[2] = 0;
      cerr << "Warning, residue has less than 3 atoms: " << getType () << endl;
    }
    curr = HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);

    /* Align the residue to the origin and transform. */
    unsigned int i;
    HomogeneousTransfo inv = curr.invert ();
    inv = m * inv;
    for (i=0; i<atomGlobal.size (); ++i) {
      atomGlobal[i]->transform (inv);
    }
  }


  void 
  BasicResidue::insert (const Atom &atom)
  {    
    AtomMap::iterator it;
    it = atomIndex.find (atom.getType ());
    int pos = size ();

    if (it==atomIndex.end ()) {
      atomIndex[atom.getType ()] = pos;
      atomGlobal.push_back (atom.clone ());
    } else {
      *atomGlobal[it->second] = atom;
    }
  }


  BasicResidue::iterator 
  BasicResidue::erase (const AtomType *type)
  {
    AtomMap::iterator i = atomIndex.find (type);
    
    if (i!=atomIndex.end ()) {
      vector< Atom* >::const_iterator cit;
      const AtomType* next;
      size_type index;
      
      delete atomGlobal[i->second];
      atomGlobal.erase (atomGlobal.begin () + i->second);
      next = ++i == atomIndex.end () ? 0 : i->first;
      atomIndex.clear ();
      for (cit = atomGlobal.begin (), index = 0;
	   cit != atomGlobal.end ();
	   ++cit, ++index)
	atomIndex[(*cit)->getType ()] = index;
      return find (next);
    } 
    return end ();
  }


  BasicResidue::iterator 
  BasicResidue::erase (const iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  BasicResidue::iterator 
  BasicResidue::erase (const const_iterator pos)
  { 
    return erase (pos->getType ()); 
  }


  int 
  BasicResidue::size () const 
  { 
    return atomIndex.size (); 
  }


  bool 
  BasicResidue::empty () const 
  { 
    return size () == 0; 
  }


  void 
  BasicResidue::clear() 
  {
    vector< Atom* >::iterator it;
    for (it = atomGlobal.begin (); it != atomGlobal.end (); ++it)
      delete *it;
    atomGlobal.clear ();
    atomIndex.clear();
  }


  void BasicResidue::validate () 
  {
    if (!type->isNucleicAcid () && !type->isAminoAcid ()) return;
    
    if (getType ()->isNucleicAcid ()) {
      removeOptionals ();
      addHydrogens ();
      addLonePairs ();
    }

    set< const AtomType* > actset;
    set< const AtomType* > diffset;    
    set< const AtomType* > oblset = ResidueTopology::getOblSet (type);
    AtomMap::iterator i;
    
    for (i=atomIndex.begin (); i!=atomIndex.end (); ++i) {
      actset.insert (i->first);
    }
    
    set_difference (oblset.begin (), oblset.end (),
 		    actset.begin (), actset.end (),
		    inserter (diffset, diffset.begin ()));
    
    if (!diffset.empty ()) {
      type = type->invalidate ();
    } else {
      // Add here the removal of non obligatory or optional atoms.
    }     
  }
  

  void BasicResidue::removeOptionals () 
  {
    if (!type->isNucleicAcid () && !type->isAminoAcid ()) return;    
    set< const AtomType* > oblset = ResidueTopology::getOblSet (type);
    iterator i;
    const AtomType* t;

    i = begin ();
    while (i != end ()) {
      t = i->getType ();
      if (oblset.find (t) == oblset.end ()) i = erase (i);
      else ++i;
    }
  }

  // PRIVATE METHODS------------------------------------------------------------


  void 
  BasicResidue::finalize ()
  {
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
  }
  
  
  Atom& 
  BasicResidue::get (size_type pos) const 
  {
    assert (pos < atomGlobal.size ());
    return *atomGlobal[pos];
  }


  Atom* 
  BasicResidue::get (const AtomType* type) const 
  {
    AtomMap::const_iterator it = atomIndex.find (type);
    if (it == atomIndex.end ())
      return 0;
    else
      return atomGlobal[it->second];
  }
  
  void BasicResidue::addHydrogens () 
  {
    // Parameters taken for AMBER all_nuc94.in
    static const float C_H_DIST_CYC = 1.08f;    // C-H distance for aromatic C
    static const float C_H_DIST = 1.09f;    // C-H distance for SP3 C
    static const float N_H_DIST = 1.01f;    // N-H distance for NH2 confo
    //    static const float N_H_DIST_CYC = 1.00f;
    static const float O_H_DIST = 0.96f;
    
    static const float TAN19 = 0.354f;      // O2' H 
    static const float TAN54 = 1.376f;
    static const float TAN60 = 1.7320508f;  // For NH2-like conformations
    static const float TAN70 = 2.7474774f;  // For CH3-like conformations
    static const float TAN30 = 0.57735027f;
 
    Vector3D x, y, z, up, a, b;

    if (type->isA ()) 
	{
	    Vector3D h2;
	    Vector3D h8;
	    Vector3D h61;
	    Vector3D h62;
	    
	    if (0 == get(AtomType::aC2) || 0 == get(AtomType::aN1)
		|| 0 == get(AtomType::aN3) || 0 == get(AtomType::aC8)
		|| 0 == get(AtomType::aN7) || 0 == get(AtomType::aN9)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aC5)
		|| 0 == get(AtomType::aN6) || 0 == get(AtomType::aC4)) {
		cerr << "A Residue " << getResId () << "-" << getType()
		     << " is missing one or more critical atoms." << endl;
		type = type->invalidate ();
		return;
	    }
	    
	    // H2
	    x = (*get (AtomType::aC2) - *get (AtomType::aN1)).normalize ();
	    y = (*get (AtomType::aC2) - *get (AtomType::aN3)).normalize ();
	    z = (x + y).normalize ();
	    h2 = *get (AtomType::aC2) + z * C_H_DIST_CYC;
	    
	    x = (*get (AtomType::aC8) - *get (AtomType::aN7)).normalize ();
	    y = (*get (AtomType::aC8) - *get (AtomType::aN9)).normalize ();
	    z = (x + y).normalize ();
	    h8 = *get (AtomType::aC8) + z * C_H_DIST_CYC;
	    
	    x = (*get (AtomType::aC6) - *get (AtomType::aN1)).normalize ();
	    y = (*get (AtomType::aC6) - *get (AtomType::aC5)).normalize ();
	    z = (*get (AtomType::aN6) - *get (AtomType::aC6)).normalize ();  // axe N6-C6     
	    up = x.cross (y).normalize ();
	    a = (z + up.cross (z).normalize () * TAN60).normalize ();
	    b = (z + z.cross (up).normalize () * TAN60).normalize ();	    
	    h61 = *get (AtomType::aN6) + a * N_H_DIST;
	    h62 = *get (AtomType::aN6) + b * N_H_DIST;
	    
	    insert (Atom (h2, AtomType::aH2));
	    insert (Atom (h8, AtomType::aH8));
	    insert (Atom (h61, AtomType::a1H6));
	    insert (Atom (h62, AtomType::a2H6));
	}
    else if (type->isG ()) 
	{
	    Vector3D h1;
	    Vector3D h8;
	    Vector3D h21;
	    Vector3D h22;
	    
	    if (0 == get(AtomType::aN1) || 0 == get(AtomType::aC2)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aC8)
		|| 0 == get(AtomType::aN7) || 0 == get(AtomType::aN9)
		|| 0 == get(AtomType::aN3) || 0 == get(AtomType::aN2)
		|| 0 == get(AtomType::aC4) || 0 == get(AtomType::aC5)
		|| 0 == get(AtomType::aO6)) {
		cerr << "G Residue " << getResId () << "-" << getType()
		     << " is missing one or more critical atoms." << endl;
		type = type->invalidate ();
		return;
	    }
	    
	    // H1
	    x = (*get (AtomType::aN1) - *get (AtomType::aC2)).normalize ();
	    y = (*get (AtomType::aN1) - *get (AtomType::aC6)).normalize ();
	    z = (x + y).normalize ();
	    h1 = *get (AtomType::aN1) + z * N_H_DIST;
	    
	    // H8
	    x = (*get (AtomType::aC8) - *get (AtomType::aN7)).normalize ();
	    y = (*get (AtomType::aC8) - *get (AtomType::aN9)).normalize ();
	    z = (x + y).normalize ();
	    h8 = *get (AtomType::aC8) + z * C_H_DIST_CYC;
	    
	    // 1H2 and 2H2
	    x = (*get (AtomType::aC2) - *get (AtomType::aN1)).normalize ();
	    y = (*get (AtomType::aC2) - *get (AtomType::aN3)).normalize ();
	    z = (*get (AtomType::aN2) - *get (AtomType::aC2)).normalize ();  // axe N2-C2	    
	    up = x.cross (y).normalize ();
	    a = (z + up.cross (z).normalize () * TAN60).normalize ();
	    b = (z + z.cross (up).normalize () * TAN60).normalize ();	    
	    h21 = *get (AtomType::aN2) + b * N_H_DIST;
	    h22 = *get (AtomType::aN2) + a * N_H_DIST;
	    
	    insert (Atom (h1, AtomType::aH1));
	    insert (Atom (h8, AtomType::aH8));
	    insert (Atom (h21, AtomType::a1H2));
	    insert (Atom (h22, AtomType::a2H2));	    
	}
    else if (type->isC ())
	{
	    Vector3D h5;
	    Vector3D h6;
	    Vector3D h41;
	    Vector3D h42;
	    
	    if (0 == get(AtomType::aC5) || 0 == get(AtomType::aC4)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aN1)
 		|| 0 == get(AtomType::aN3) || 0 == get(AtomType::aN4)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aC5)
		|| 0 == get(AtomType::aC2) || 0 == get(AtomType::aO2)) {
		cerr << "C Residue " << getResId () << "-" << getType()
		     << " is missing one or more critical atoms." << endl;
		type = type->invalidate ();
		return;
	    }

	    // H5
	    x = (*get (AtomType::aC5) - *get (AtomType::aC4)).normalize ();
	    y = (*get (AtomType::aC5) - *get (AtomType::aC6)).normalize ();
	    z = (x + y).normalize ();
	    h5 = *get (AtomType::aC5) + z * C_H_DIST; // Exceptionnal distance!
	          
	    // H6
	    x = (*get (AtomType::aC6) - *get (AtomType::aC5)).normalize ();
	    y = (*get (AtomType::aC6) - *get (AtomType::aN1)).normalize ();
	    z = (x + y).normalize ();
	    h6 = *get (AtomType::aC6) + z * C_H_DIST_CYC;
	    
	    // 1H4 and 2H4
	    x = (*get (AtomType::aC4) - *get (AtomType::aN3)).normalize ();
	    y = (*get (AtomType::aC4) - *get (AtomType::aC5)).normalize ();
	    z = (*get (AtomType::aN4) - *get (AtomType::aC4)).normalize ();	    
	    up = x.cross (y).normalize ();
	    a = (z + up.cross (z).normalize () * TAN60).normalize ();
	    b = (z + z.cross (up).normalize () * TAN60).normalize ();	    
	    h41 = *get (AtomType::aN4) + b * N_H_DIST;
	    h42 = *get (AtomType::aN4) + a * N_H_DIST;

	    insert (Atom (h5, AtomType::aH5));
	    insert (Atom (h6, AtomType::aH6));
	    insert (Atom (h41, AtomType::a1H4));
	    insert (Atom (h42, AtomType::a2H4));
	}
    else if (type->isU ()) 
	{
	    Vector3D h3;
	    Vector3D h5;
	    Vector3D h6;
	    
	    if (0 == get(AtomType::aN3) || 0 == get(AtomType::aC2)
		|| 0 == get(AtomType::aC4) || 0 == get(AtomType::aC5)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aN1)
		|| 0 == get(AtomType::aO2) || 0 == get(AtomType::aO4)) {
		cerr << "U Residue " << getResId () << "-" << getType()
		     << " is missing one or more critical atoms." << endl;
		type = type->invalidate ();
  		return;
  	    }

	    // H3
	    x = (*get (AtomType::aN3) - *get (AtomType::aC2)).normalize ();
	    y = (*get (AtomType::aN3) - *get (AtomType::aC4)).normalize ();
	    z = (x + y).normalize ();
	    h3 = *get (AtomType::aN3) + z * C_H_DIST; // Exceptionnal distance!
	    
	    
	    // H5
	    x = (*get (AtomType::aC5) - *get (AtomType::aC4)).normalize ();
	    y = (*get (AtomType::aC5) - *get (AtomType::aC6)).normalize ();
	    z = (x + y).normalize ();
	    h5 = *get (AtomType::aC5) + z * C_H_DIST; // Exceptionnal distance!	    
	    
	    // H6
	    x = (*get (AtomType::aC6) - *get (AtomType::aC5)).normalize ();
	    y = (*get (AtomType::aC6) - *get (AtomType::aN1)).normalize ();
	    z = (x + y).normalize ();
	    h6 = *get (AtomType::aC6) + z * C_H_DIST_CYC;

	    insert (Atom (h3, AtomType::aH3));
	    insert (Atom (h5, AtomType::aH5));
	    insert (Atom (h6, AtomType::aH6));

	}
    else if (type->isT ())
	{
	    Vector3D h3;
	    Vector3D h6, h51m, h52m, h53m;
	    
	    if (0 == get(AtomType::aN3) || 0 == get(AtomType::aC2)
		|| 0 == get(AtomType::aC4) || 0 == get(AtomType::aC5)
		|| 0 == get(AtomType::aC6) || 0 == get(AtomType::aN1)
		|| 0 == get(AtomType::aO2) || 0 == get(AtomType::aO4)) {
		cerr << "T Residue " << getResId () << "-" << getType()
		     << " is missing one or more critical atoms." << endl;
		type = type->invalidate ();
  		return;
  	    }

	    // H3
	    x = (*get (AtomType::aN3) - *get (AtomType::aC2)).normalize ();
	    y = (*get (AtomType::aN3) - *get (AtomType::aC4)).normalize ();
	    z = (x + y).normalize ();
	    h3 = *get (AtomType::aN3) + z * C_H_DIST; // Exceptionnal distance!	    
	    
	    // H6
	    x = (*get (AtomType::aC6) - *get (AtomType::aC5)).normalize ();
	    y = (*get (AtomType::aC6) - *get (AtomType::aN1)).normalize ();
	    z = (x + y).normalize ();
	    h6 = *get (AtomType::aC6) + z * C_H_DIST_CYC;
	    
	    // 1H5M, 2H5M, 3H5M (arbitrarily placed)	    
	    x = (*get (AtomType::aC5M) - *get (AtomType::aC5)).normalize ();
	    y = (*get (AtomType::aC5) - *get (AtomType::aC4)).normalize ();
	    up = x.cross (y).normalize ();
	    z = x.cross (up);
	    
	    h51m = *get (AtomType::aC5M) + (x + z * TAN70).normalize () * C_H_DIST;
	    
	    a = (up - z*TAN30).normalize ();
	    h52m = *get (AtomType::aC5M) + (x + a * TAN70).normalize () * C_H_DIST;
	    
	    b = (-up - z*TAN30).normalize ();
	    h53m = *get (AtomType::aC5M) + (x + b * TAN70).normalize () * C_H_DIST;

	    insert (Atom (h3, AtomType::aH3));
	    insert (Atom (h6, AtomType::aH6));
	    insert (Atom (h51m, AtomType::a1H5M));
	    insert (Atom (h52m, AtomType::a2H5M));
	    insert (Atom (h53m, AtomType::a3H5M));
	}

    if (type->isNucleicAcid ()) 
	{
	    const Vector3D *r1;
	    const Vector3D *r2;
	    const Vector3D *r3;
	    const Vector3D *r4;
	    
	    //  H1p
	    if (!contains (AtomType::aH1p)) {
		r1 = get (AtomType::aC1p);
		r2 = get (AtomType::aC2p);
		r3 = (type->isPurine ()) ? get (AtomType::aN9) : get (AtomType::aN1);
		r4 = get (AtomType::aO4p);
		if (0 != r1 && 0 != r2 && 0 != r3 && 0 != r4) {
		    Vector3D h1p;
		    
		    x = (*r1 - *r2).normalize ();
		    y = (*r1 - *r3).normalize ();
		    z = (*r1 - *r4).normalize ();
		    
		    h1p = *r1 + (x + y + z).normalize () * C_H_DIST;
		    insert (Atom (h1p, AtomType::aH1p));
		}
	    }
	    
	    //  H3p
	    if (!contains (AtomType::aH3p)) {
		r1 = get (AtomType::aC3p);
		r2 = get (AtomType::aC2p);
		r3 = get (AtomType::aO3p);
		r4 = get (AtomType::aC4p);
		if (0 != r1 && 0 != r2 && 0 != r3 && 0 != r4) {
		    Vector3D h3p;
		    
		    x = (*r1 - *r2).normalize ();
		    y = (*r1 - *r3).normalize ();
		    z = (*r1 - *r4).normalize ();
		    		    
		    h3p = *r1 + (x + y + z).normalize () * C_H_DIST;
		    insert (Atom (h3p, AtomType::aH3p));
		}
	    }

	    //  H4p
	    if (!contains (AtomType::aH4p)) {
		r1 = get (AtomType::aC4p);
		r2 = get (AtomType::aC3p);
		r3 = get (AtomType::aO4p);
		r4 = get (AtomType::aC5p);
		if (0 != r1 && 0 != r2 && 0 != r3 && 0 != r4) {
		    Vector3D h4p;
		    
		    x = (*r1 - *r2).normalize ();
		    y = (*r1 - *r3).normalize ();
		    z = (*r1 - *r4).normalize ();
	  
		    h4p = *r1 + (x + y + z).normalize () * C_H_DIST;
		    insert (Atom (h4p, AtomType::aH4p));
		}
	    }
	    
	    
	    //  1H5p  2H5p
	    if (!contains (AtomType::a1H5p) || !contains (AtomType::a1H5p)) {
		r1 = get (AtomType::aC5p);
		r2 = get (AtomType::aC4p);
		r3 = get (AtomType::aO5p);
		if (0 != r1 && 0 != r2 && 0 != r3) {
		    Vector3D h51p;
		    Vector3D h52p;
		    
		    x = (*r1 - *r2).normalize ();
		    y = (*r1 - *r3).normalize ();
		    z = (x + y).normalize ();
		    up = x.cross (y).normalize ();

		    h51p = *r1 + (up * TAN54 + z).normalize () * C_H_DIST;
		    h52p = *r1 + (-up * TAN54 + z).normalize () * C_H_DIST;
		    insert (Atom (h51p, AtomType::a1H5p));
		    insert (Atom (h52p, AtomType::a2H5p));
		}
	    }
	    
	    // HO3p  // optional
	    if (!contains (AtomType::aHO3p)) {
		r1 = get (AtomType::aO3p);
		r2 = get (AtomType::aC3p);
		r3 = get (AtomType::aC4p);
		
		if (0 != r1 && 0 != r2 && 0 != r3) {
		    Vector3D hO3p;
		    
		    x = (*r2 - *r3).normalize ();
		    y = (*r1 - *r2).normalize ();
		    z = x.cross (y).cross (y).normalize ();
		    
		    hO3p = *r1 + (y*TAN19+z).normalize () * O_H_DIST;
		    insert (Atom (hO3p, AtomType::aHO3p));
		}
	    }
	    
	    if (contains (AtomType::aO2p)) {
		//  H2p
		if (!contains (AtomType::aH2p)) {
		    r1 = get (AtomType::aC2p);
		    r2 = get (AtomType::aC1p);
		    r3 = get (AtomType::aC3p);
		    r4 = get (AtomType::aO2p);
		    if (0 != r1 && 0 != r2 && 0 != r3 && 0 != r4) {
			Vector3D h2p;
			
			x = (*r1 - *r2).normalize ();
			y = (*r1 - *r3).normalize ();
			z = (*r1 - *r4).normalize ();
			
			h2p = *r1 + (x + y + z).normalize () * C_H_DIST;
			insert (Atom (h2p, AtomType::aH2p));
		    }
		}
		
		// HO2p
		if (!contains (AtomType::aHO2p)) {
		    r1 = get (AtomType::aO2p);
		    r2 = get (AtomType::aC2p);
		    r3 = get (AtomType::aC1p);
		    if (0 != r1 && 0 != r2 && 0 != r3) {
			Vector3D hO2p;
			
			x = (*r2 - *r3).normalize ();
			y = (*r1 - *r2).normalize ();
			z = x.cross (y).cross (y).normalize ();			
			hO2p = *r1 + (y * TAN19 - z).normalize () * O_H_DIST;
			insert (Atom (hO2p, AtomType::aHO2p));
		    }
		}
	    } else {
		// 1H2p 2H2p
		if (!contains (AtomType::a1H2p) || !contains (AtomType::a2H2p)) {
		    r1 = get (AtomType::aC2p);
		    r2 = get (AtomType::aC1p);
		    r3 = get (AtomType::aC3p);
		    if (0 != r1 && 0 != r2 && 0 != r3) {
			Vector3D h21p;
			Vector3D h22p;
			
			x = (*r1 - *r2).normalize ();
			y = (*r1 - *r3).normalize ();
			z = (x + y).normalize ();
			up = x.cross (y).normalize ();
			
			h21p = *r1 + (up * TAN54 + z).normalize () * C_H_DIST;
			h22p = *r1 + (-up * TAN54 + z).normalize () * C_H_DIST;
			insert (Atom (h21p, AtomType::a1H2p));
			insert (Atom (h22p, AtomType::a2H2p));
		    }
		}
	    }	  	    
	}    
  }

  
  void 
  BasicResidue::addLonePairs () 
  {
    static const float O_LP_DIST = 1.00f;
    static const float N_LP_DIST = 1.00f;
    static const float TAN60 = 1.7320508f;

    Vector3D x, y, z, up, a, b;
    
    if (type->isA ()) 
      {	
	if (0 == get (AtomType::aC2) || 0 == get (AtomType::aN1)
	    || 0 == get (AtomType::aN3) || 0 == get (AtomType::aC8)
	    || 0 == get (AtomType::aN7) || 0 == get (AtomType::aN9)
	    || 0 == get (AtomType::aC6) || 0 == get (AtomType::aC5)
	    || 0 == get (AtomType::aN6) || 0 == get (AtomType::aC4)) {
	  cerr << "A Residue " << getResId () << "-" << getType()
	       << " is missing one or more critical atoms." << endl;
	  type = type->invalidate();
	  return;
	}
      
	Vector3D lp1;
	Vector3D lp3;
	Vector3D lp7;
	
	// LP1
	x = (*get (AtomType::aN1) - *get (AtomType::aC2)).normalize ();
	y = (*get (AtomType::aN1) - *get (AtomType::aC6)).normalize ();
	z = (x + y).normalize ();
	lp1 = *get (AtomType::aN1) + z * N_LP_DIST;
	
	// LP3
	x = (*get (AtomType::aN3) - *get (AtomType::aC2)).normalize ();
	y = (*get (AtomType::aN3) - *get (AtomType::aC4)).normalize ();
	z = (x + y).normalize ();
	lp3 =*get (AtomType::aN3) + z * N_LP_DIST;
      
	// LP7
	x = (*get (AtomType::aN7) - *get (AtomType::aC5)).normalize ();
	y = (*get (AtomType::aN7) - *get (AtomType::aC8)).normalize ();
	z = (x + y).normalize ();
	lp7 = *get (AtomType::aN7) + z * N_LP_DIST;
	
	insert (Atom (lp1, AtomType::aLP1));
	insert (Atom (lp3, AtomType::aLP3));
	insert (Atom (lp7, AtomType::aLP7));
      } 
    else if (type->isG ()) 
      {	
	if (0 == get (AtomType::aN1) || 0 == get (AtomType::aC2)
	    || 0 == get (AtomType::aC6) || 0 == get (AtomType::aC8)
	    || 0 == get (AtomType::aN7) || 0 == get (AtomType::aN9)
	    || 0 == get (AtomType::aN3) || 0 == get (AtomType::aN2)
	    || 0 == get (AtomType::aC4) || 0 == get (AtomType::aC5)
	    || 0 == get (AtomType::aO6)) {
	  cerr << "G Residue " << getResId () << "-" << getType()
	       << " is missing one or more critical atoms." << endl;
	  type = type->invalidate();	      
	  return;
	}
	
	Vector3D lp3;
	Vector3D lp7;
	Vector3D lp61;
	Vector3D lp62;
	
	// LP3
	x = (*get (AtomType::aN3) - *get (AtomType::aC2)).normalize ();
	y = (*get (AtomType::aN3) - *get (AtomType::aC4)).normalize ();
	z = (x + y).normalize ();
	lp3 = *get (AtomType::aN3) + z * N_LP_DIST;
	
	// LP7
	x = (*get (AtomType::aN7) - *get (AtomType::aC5)).normalize ();
	y = (*get (AtomType::aN7) - *get (AtomType::aC8)).normalize ();
	z = (x + y).normalize ();
	lp7 = *get (AtomType::aN7) + z * N_LP_DIST;
	
	// 1LP6 and 2LP6
	x = (*get (AtomType::aC6) - *get (AtomType::aN1)).normalize ();
	y = (*get (AtomType::aC6) - *get (AtomType::aC5)).normalize ();
	z = (*get (AtomType::aO6) - *get (AtomType::aC6)).normalize ();
	
	up = x.cross (y).normalize ();
	a = (z + up.cross (z).normalize () * TAN60).normalize ();
	b = (z + z.cross (up).normalize () * TAN60).normalize ();	
	lp61 = *get (AtomType::aO6) + b * O_LP_DIST;
	lp62 = *get (AtomType::aO6) + a * O_LP_DIST;
	
	insert (Atom (lp3, AtomType::aLP3));
	insert (Atom (lp7, AtomType::aLP7));
	insert (Atom (lp61, AtomType::a1LP6));
	insert (Atom (lp62, AtomType::a2LP6));
      } 
    else if (type->isC ()) 
      {
	if (0 == get (AtomType::aC5) || 0 == get (AtomType::aC4)
	    || 0 == get (AtomType::aC6) || 0 == get (AtomType::aN1)
	    || 0 == get (AtomType::aN3) || 0 == get (AtomType::aN4)
	    || 0 == get (AtomType::aC6) || 0 == get (AtomType::aC5)
	    || 0 == get (AtomType::aC2) || 0 == get (AtomType::aO2)) {
	  cerr << "C Residue " << getResId () << "-" << getType()
	       << " is missing one or more critical atoms." << endl;
	  type = type->invalidate();	      
	  return;
	}
	
	Vector3D lp3;
	Vector3D lp21;
	Vector3D lp22;
	
	// LP3
	x = (*get (AtomType::aN3) - *get (AtomType::aC2)).normalize ();
	y = (*get (AtomType::aN3) - *get (AtomType::aC4)).normalize ();
	z = (x + y).normalize ();
	lp3 = *get (AtomType::aN3) + z * N_LP_DIST;
	
	// 1LP2 and 2LP2
	x = (*get (AtomType::aC2) - *get (AtomType::aN1)).normalize ();
	y = (*get (AtomType::aC2) - *get (AtomType::aN3)).normalize ();
	z = (*get (AtomType::aO2) - *get (AtomType::aC2)).normalize ();
	
	up = x.cross (y).normalize ();
	a = (z + up.cross (z).normalize () * TAN60).normalize ();
	b = (z + z.cross (up).normalize () * TAN60).normalize ();
	
	lp21 = *get (AtomType::aO2) + a * O_LP_DIST;
	lp22 = *get (AtomType::aO2) + b * O_LP_DIST;
	
	insert (Atom (lp3, AtomType::aLP3));
	insert (Atom (lp21, AtomType::a1LP2));
	insert (Atom (lp22, AtomType::a2LP2));
      } 
    else if (type->isU () || type->isT ()) 
      {	    
	if (0 == get (AtomType::aN3) || 0 == get (AtomType::aC2)
	    || 0 == get (AtomType::aC4) || 0 == get (AtomType::aC5)
	    || 0 == get (AtomType::aC6) || 0 == get (AtomType::aN1)
	    || 0 == get (AtomType::aO2) || 0 == get (AtomType::aO4)) {
	  cerr << "U Residue " << getResId () << "-" << getType()
	       << " is missing one or more critical atoms." << endl;
	  type = type->invalidate();	      
	  return;
	}
	
	Vector3D lp21;
	Vector3D lp22;
	Vector3D lp41;
	Vector3D lp42;
	
	// 1LP2 and 2LP2
	x = (*get (AtomType::aC2) - *get (AtomType::aN1)).normalize ();
	y = (*get (AtomType::aC2) - *get (AtomType::aN3)).normalize ();
	z = (*get (AtomType::aO2) - *get (AtomType::aC2)).normalize ();
	up = x.cross (y).normalize ();
	a = (z + up.cross (z).normalize () * TAN60).normalize ();
	b = (z + z.cross (up).normalize () * TAN60).normalize ();
	lp21 = *get (AtomType::aO2) + a * O_LP_DIST;
	lp22 = *get (AtomType::aO2) + b * O_LP_DIST;
	
	// 1LP4 and 2LP4
	x = (*get (AtomType::aC4) - *get (AtomType::aN3)).normalize ();
	y = (*get (AtomType::aC4) - *get (AtomType::aC5)).normalize ();
	z = (*get (AtomType::aO4) - *get (AtomType::aC4)).normalize ();	
	up = x.cross (y).normalize ();
	a = (z + up.cross (z).normalize () * TAN60).normalize ();
	b = (z + z.cross (up).normalize () * TAN60).normalize ();
	
	lp41 = *get (AtomType::aO4) + b * O_LP_DIST;
	lp42 = *get (AtomType::aO4) + a * O_LP_DIST;
      
	insert (Atom (lp21, AtomType::a1LP2));
	insert (Atom (lp22, AtomType::a2LP2));
	insert (Atom (lp41, AtomType::a1LP4));
	insert (Atom (lp42, AtomType::a2LP4));
      }      
  }
  

  const PropertyType* 
  BasicResidue::getPucker ()
  {
    if (!getType ()->isNucleicAcid ()) return 0;

    double nu0, nu1, nu2, nu3, nu4;
    double P;
    
    // Evaluation of the pucker mode
    
    nu0 = get (AtomType::aO4p)->torsionAngle (*get (AtomType::aC4p),
					      *get (AtomType::aC1p),
					      *get (AtomType::aC2p));
    nu1 = get (AtomType::aC1p)->torsionAngle (*get (AtomType::aO4p),
					      *get (AtomType::aC2p),
					      *get (AtomType::aC3p));
    nu2 = get (AtomType::aC2p)->torsionAngle (*get (AtomType::aC1p),
					      *get (AtomType::aC3p),
					      *get (AtomType::aC4p));    
    nu3 = get (AtomType::aC3p)->torsionAngle (*get (AtomType::aC2p),
					      *get (AtomType::aC4p),
					      *get (AtomType::aO4p));    
    nu4 = get (AtomType::aC4p)->torsionAngle (*get (AtomType::aC3p),
					      *get (AtomType::aO4p),
					      *get (AtomType::aC1p));
    
    P = atan2 (nu4+nu1-nu3-nu0, nu2*3.07768354 );
    
    if  (P > 0)
      P = P * 180 / M_PI;
    else
      P = 360 + P * 180 / M_PI;
    
    if (((P >= 0) &&  (P < 36)) ||  (P == 360))
      return PropertyType::pC3p_endo;
    else if ((P >= 36) &&  (P < 72))
      return PropertyType::pC4p_exo;
    else if ((P >= 72) &&  (P < 108))
      return PropertyType::pO4p_endo;
    else if ((P >= 108) &&  (P < 144))
      return PropertyType::pC1p_exo;
    else if ((P >= 144) &&  (P < 180)) 
      return PropertyType::pC2p_endo;
    else if ((P >= 180) &&  (P < 216))
      return PropertyType::pC3p_exo;
    else if ((P >= 216) &&  (P < 252)) 
      return PropertyType::pC4p_endo;
    else if ((P >= 252) &&  (P < 288))
      return PropertyType::pO4p_exo;
    else if ((P >= 288) &&  (P < 324))
      return PropertyType::pC1p_endo;
    else 
      return PropertyType::pC2p_exo;   
  }
  
  const PropertyType* 
  BasicResidue::getGlycosyl ()
  {
    if (!getType ()->isNucleicAcid ()) return 0;
    
    double chi;
    
    if  (getType ()->isPurine ())
      chi = get (AtomType::aC1p)->torsionAngle (*get (AtomType::aO4p),
						 *get (AtomType::aN9),
						*get (AtomType::aC4));
    else 
      chi = get (AtomType::aC1p)->torsionAngle (*get (AtomType::aO4p),
						*get (AtomType::aN1),
						*get (AtomType::aC2));
    
    if  ((chi >= -10 && chi <= -M_PI/2)
	 || (chi > M_PI/2 && chi <= 10))
      return PropertyType::pAnti;
    else if  ((chi > -M_PI/2 && chi <= 0)
	      || (chi > 0 && chi <= M_PI/2))
      return PropertyType::pSyn;
    return 0;
  }

  
  // I/O -----------------------------------------------------------------------


  ostream&
  BasicResidue::output (ostream &os) const 
  {
    os << resId << type;
//     AtomMap::const_iterator cit;
//     for (cit=atomIndex.begin (); cit!=atomIndex.end (); ++cit) {
//       os << endl << *(atomGlobal[cit->second]);
//     }
    return os;
  }
  
  
  iBinstream& 
  BasicResidue::input (iBinstream &ibs)
  {
    clear ();

    int i, s;
    Atom a;

    ibs >> type;
    ibs >> resId;
    ibs >> s;
    
    for (i=0; i<s; ++i) {
      ibs >> a;
      insert (a);
    }

    // Finalize
    finalize ();
    
    return ibs;
  }


  oBinstream& 
  BasicResidue::output (oBinstream &obs) const
  {
    const_iterator cit;

    obs << type;
    obs << resId;
    obs << size ();

    for (cit = begin (); cit != end (); ++cit) {
      obs << *cit;
    }
    return obs;
  }


  ostream&
  operator<< (ostream &os, const BasicResidue &r)
  {
    return r.output (os);
  }

  ostream&
  operator<< (ostream &os, const BasicResidue *r)
  {
    return r->output (os);
  }

  iBinstream& operator>> (iBinstream &ibs, BasicResidue &res)
  {
    return res.input (ibs);
  }


  oBinstream& operator<< (oBinstream &obs, const BasicResidue &res)
  {
    return res.output (obs);
  }


  // ITERATORS -----------------------------------------------------------------


  BasicResidue::ResidueIterator::ResidueIterator ()
    : res (0),
      filter (new AtomSetAll ())
  {
  }
  


  BasicResidue::ResidueIterator::ResidueIterator (BasicResidue *r,
						  AtomMap::iterator p,
						  AtomSet *f)
    : res (r),
      pos (p),
      filter (f)
  {
    AtomMap::iterator last = res->atomIndex.end ();

    if (filter == 0)
      filter = new AtomSetAll ();
    while (pos != last && ! (*filter) (res->get (pos->second)))
      ++pos;
  }
  


  BasicResidue::ResidueIterator::ResidueIterator (const ResidueIterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  {
  }



  BasicResidue::ResidueIterator::~ResidueIterator ()
  {
    delete filter;
  }
  


  BasicResidue::ResidueIterator&
  BasicResidue::ResidueIterator::operator= (const ResidueIterator &right)
  {
    if (this != &right)
      {
	res = right.res;
	pos = right.pos;
	delete filter;
	filter = right.filter->clone ();
      }
    return *this;
  }



  BasicResidue::ResidueIterator&
  BasicResidue::ResidueIterator::operator+= (difference_type k)
  {
    AtomMap::iterator last = res->atomIndex.end ();

    while (k > 0 && pos != last)
      if (++pos != last && (*filter) (res->get (pos->second)))
	--k;
    return *this;
  }


  
  BasicResidue::iterator&
  BasicResidue::ResidueIterator::operator++ ()
  {
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return *this;
  }



  BasicResidue::iterator
  BasicResidue::ResidueIterator::operator++ (int ign)
  {
    ResidueIterator ret = *this;
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return ret;
  }



  BasicResidue::ResidueConstIterator::ResidueConstIterator ()
    : res (0),
      filter (new AtomSetAll ())
  { }



  BasicResidue::ResidueConstIterator::ResidueConstIterator (const BasicResidue *r,
							    AtomMap::const_iterator p,
							    AtomSet *f)
    : res (r),
      pos (p),
      filter (f)
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    if (filter == 0)
      filter = new AtomSetAll ();
    while (pos != last && ! (*filter) (res->get (pos->second)))
      ++pos;
  }



  BasicResidue::ResidueConstIterator::ResidueConstIterator (const BasicResidue::const_iterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  { }



  BasicResidue::ResidueConstIterator::ResidueConstIterator (const BasicResidue::iterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  { }



  BasicResidue::ResidueConstIterator::~ResidueConstIterator ()
  {
    delete filter;
  }



  BasicResidue::const_iterator&
  BasicResidue::ResidueConstIterator::operator= (const BasicResidue::const_iterator &right)
  {
    if (this != &right)
      {
	res = right.res;
	pos = right.pos;
	delete filter;
	filter = right.filter->clone ();
      }
    return *this;
  }



  BasicResidue::const_iterator&
  BasicResidue::ResidueConstIterator::operator= (const BasicResidue::iterator &right)
  {
    res = right.res;
    pos = right.pos;
    delete filter;
    filter = right.filter->clone ();
    return *this;
  }



  BasicResidue::const_iterator&
  BasicResidue::ResidueConstIterator::operator+= (difference_type k)
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (k > 0 && pos != last)
      if (++pos != last && (*filter) (res->get (pos->second)))
	--k;
    return *this;
  }



  BasicResidue::const_iterator&
  BasicResidue::ResidueConstIterator::operator++ ()
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return *this;
  }



  BasicResidue::const_iterator
  BasicResidue::ResidueConstIterator::operator++ (int ign)
  {
    ResidueConstIterator ret = *this;
    AtomMap::const_iterator last = res->atomIndex.end ();
  
    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return ret;
  }


}
