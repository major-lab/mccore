//                              -*- Mode: C++ -*- 
// Residue.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar 14 16:44:35 2003
// $Revision: 1.30 $
// $Id: Residue.cc,v 1.30 2004-05-14 15:01:27 thibaup Exp $
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
#include <assert.h>
#include <math.h>
#include <set>

#include "Binstream.h"
#include "CException.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "PropertyType.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueTopology.h"
#include "ResidueFactoryMethod.h"
#include "Rmsd.h"

#define RAD_36  0.6283185
#define RAD_72  1.2566371
#define RAD_90  1.5707963
#define RAD_108 1.8849556
#define RAD_144 2.5132741
#define RAD_180 3.1415927
#define RAD_216 3.7699112
#define RAD_252 4.3982297
#define RAD_270 4.7123890
#define RAD_288 5.0265482
#define RAD_324 5.6548668
#define RAD_360 6.2831853

#define RAD(deg) (deg * 180.0 / M_PI)
#define DEG(rad) (rad * M_PI / 180.0)

namespace mccore {

  const float Residue::s_cosf_amplitude = 1.3305;
  const float Residue::s_cosf_vshift = 2.0778;
  const float Residue::s_cosf_phase = 0.3041;
  const float Residue::s_cosf_2xphase = 2.0 * Residue::s_cosf_phase;

  const float Residue::s_2xpi = 2.0 * M_PI;
  const float Residue::s_4xpi = 4.0 * M_PI;

  float Residue::s_rib_minshift = 0.1;
  float Residue::s_rib_mindrop = 0.00001;
  float Residue::s_rib_shiftrate = 0.5;
  
  // LIFECYCLE ------------------------------------------------------------


  Residue::Residue ()
    : type (ResidueType::parseType ("undefined")),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    rib_C1p = rib_C2p = rib_C3p = rib_C4p = rib_C5p = rib_O2p = rib_O3p = rib_O4p = rib_O5p = rib_P = 0;
  }

  

  Residue::Residue (const ResidueType *t, const ResId &i)
    : type (t),
      resId (i),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    rib_C1p = rib_C2p = rib_C3p = rib_C4p = rib_C5p = rib_O2p = rib_O3p = rib_O4p = rib_O5p = rib_P = 0;
  }


  Residue::Residue (const ResidueType *t, const ResId &i, const vector< Atom > &vec)
    : type (t),
      resId (i),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    vector< Atom >::const_iterator j;
    for (j=vec.begin (); j!=vec.end (); ++j) {
      insert (*j);
    }

    rib_C1p = rib_C2p = rib_C3p = rib_C4p = rib_C5p = rib_O2p = rib_O3p = rib_O4p = rib_O5p = rib_P = 0;
  }


  Residue::Residue (const Residue &other)
  {
    vector< Atom* >::const_iterator cit;

    type = other.type;
    resId = other.resId;
    for (cit = other.atomGlobal.begin (); cit != other.atomGlobal.end (); ++cit) {
      Atom* cl = (*cit)->clone ();
      atomGlobal.push_back (cl);
    }    
    atomIndex = other.atomIndex;

    rib_C1p = rib_C2p = rib_C3p = rib_C4p = rib_C5p = rib_O2p = rib_O3p = rib_O4p = rib_O5p = rib_P = 0;
    rib_dirty_ref = true;
    rib_built_valid = other.rib_built_valid;
    rib_built_count = other.rib_built_count;
  }

  
  Residue* 
  Residue::clone () const 
  { 
    return new Residue (*this); 
  }
  

  Residue::~Residue () 
  {
    vector< Atom* >::iterator it;
    for (it = atomGlobal.begin (); it != atomGlobal.end (); ++it)
      delete *it;
    atomGlobal.clear ();
    atomIndex.clear();
  }


  bool 
  Residue::setIdeal (bool h_lp)
  {
    if (!(type->isNucleicAcid () || type->isPhosphate ()))
      return false;

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
      //insert (Atom (-0.094f, -0.005f, 0.017f, AtomType::aC1p));
    } else if (type == ResidueType::rRC || type == ResidueType::rDC) {
      insert (Atom (0.212f, 0.668f, 1.294f, AtomType::aN1)); 
      insert (Atom (0.193f, -0.043f, 2.462f, AtomType::aC6));
      insert (Atom (0.374f, 2.055f, 1.315f, AtomType::aC2)); 
      insert (Atom (0.388f, 2.673f, 0.240f, AtomType::aO2)); 
      insert (Atom (0.511f, 2.687f, 2.504f, AtomType::aN3)); 
      insert (Atom (0.491f, 1.984f, 3.638f, AtomType::aC4)); 
      insert (Atom (0.631f, 2.649f, 4.788f, AtomType::aN4)); 
      insert (Atom (0.328f, 0.569f, 3.645f, AtomType::aC5)); 
      //insert (Atom (0.064f, -0.006f, 0.002f, AtomType::aC1p));
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
      //insert (Atom (-0.075f, -0.005f, 0.009f, AtomType::aC1p));
    } else if (type == ResidueType::rRU) {
      insert (Atom (0.212f, 0.676f, 1.281f, AtomType::aN1)); 
      insert (Atom (0.195f, -0.023f, 2.466f, AtomType::aC6));
      insert (Atom (0.370f, 2.048f, 1.265f, AtomType::aC2)); 
      insert (Atom (0.390f, 2.698f, 0.235f, AtomType::aO2)); 
      insert (Atom (0.505f, 2.629f, 2.502f, AtomType::aN3)); 
      insert (Atom (0.497f, 1.990f, 3.725f, AtomType::aC4)); 
      insert (Atom (0.629f, 2.653f, 4.755f, AtomType::aO4)); 
      insert (Atom (0.329f, 0.571f, 3.657f, AtomType::aC5)); 
      //insert (Atom (0.063f, -0.008f, -0.006f, AtomType::aC1p));
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
      //insert (Atom (0.000f, 0.000f, 0.000f, AtomType::aC1p));	    
    } else if (type == ResidueType::rPhosphate) {
      insert (Atom ( 4.691f,  0.327f, -2.444f, AtomType::aP));
      insert (Atom ( 5.034f,  1.678f, -1.932f, AtomType::aO1P));
      insert (Atom ( 4.718f,  0.068f, -3.906f, AtomType::aO2P));
      insert (Atom ( 3.246f, -0.057f, -1.895f, AtomType::aO5p));
      insert (Atom ( 5.662f, -0.712f, -1.734f, AtomType::aO3p));
    }
    else {
      return false;
    }

    // These data are not valid and should be replaced...
//     if (type->isRNA ()) {
//       insert (Atom ( 4.691f,  0.327f, -2.444f, AtomType::aP));
//       insert (Atom ( 5.034f,  1.678f, -1.932f, AtomType::aO1P));
//       insert (Atom ( 4.718f,  0.068f, -3.906f, AtomType::aO2P));
//       insert (Atom ( 3.246f, -0.057f, -1.895f, AtomType::aO5p));
//       insert (Atom ( 2.957f, -1.393f, -1.443f, AtomType::aC5p));
//       insert (Atom ( 1.509f, -1.478f, -1.022f, AtomType::aC4p));
//       insert (Atom ( 1.286f, -0.587f,  0.103f, AtomType::aO4p));
//       insert (Atom ( 0.000f,  0.000f,  0.000f, AtomType::aC1p));
//       insert (Atom (-0.694f, -0.627f, -1.210f, AtomType::aC2p));
//       insert (Atom (-1.474f, -1.731f, -0.795f, AtomType::aO2p));
//       insert (Atom ( 0.499f, -1.031f, -2.067f, AtomType::aC3p));
//       insert (Atom ( 0.178f, -2.084f, -2.981f, AtomType::aO3p));
//     } else if (type->isDNA ()) {
//       insert (Atom (  0.224f,  -4.365f,   2.383f, AtomType::aP));
//       insert (Atom (  1.336f,  -3.982f,   3.290f, AtomType::aO1P));
//       insert (Atom (  0.278f,  -5.664f,   1.666f, AtomType::aO2P));
//       insert (Atom (  0.042f,  -3.205f,   1.307f, AtomType::aO5p));
//       insert (Atom (  1.149f,  -0.891f,  -0.438f, AtomType::aC2p));
//       insert (Atom ( -1.014f,  -3.256f,   0.347f, AtomType::aC5p));
//       insert (Atom ( -0.913f,  -2.083f,  -0.600f, AtomType::aC4p));
//       insert (Atom ( -1.127f,  -0.853f,   0.133f, AtomType::aO4p));
//       insert (Atom (  0.000f,   0.000f,   0.000f, AtomType::aC1p));
//       insert (Atom (  0.445f,  -1.932f,  -1.287f, AtomType::aC3p));
//       insert (Atom (  0.272f,  -1.450f,  -2.624f, AtomType::aO3p));	    
//     } else {
//       return false;
//     }

    finalize (h_lp);

    return true;    
  }


  // OPERATORS -----------------------------------------------------------------


  Residue& 
  Residue::operator= (const Residue &other)
  {
    vector< Atom* >::const_iterator cit;

    if (this != &other) {
      type = other.type;
      resId = other.resId;
      clear ();
      
      for (cit = other.atomGlobal.begin (); cit != other.atomGlobal.end (); ++cit)
	atomGlobal.push_back ((*cit)->clone ());

      rib_built_valid = other.rib_built_valid;
      rib_built_count = other.rib_built_count;
      atomIndex = other.atomIndex;
    }

    return *this;
  }

  
  bool 
  Residue::operator== (const Residue &other) const
  { 
    return resId == other.resId 
      && *type == *other.getType (); 
  }
  

  bool 
  Residue::operator!= (const Residue &other) const 
  { 
    return ! operator== (other); 
  }
  
  
  bool 
  Residue::operator< (const Residue &other) const
  { 
    return resId < other.resId; 
  }


  // ACCESS --------------------------------------------------------------------


  const ResId& 
  Residue::getResId () const 
  { 
    return resId; 
  }


  void 
  Residue::setResId (const ResId& id) 
  { 
    resId = id; 
  }


  const ResidueType* 
  Residue::getType() const 
  { 
    return type; 
  }


  void 
  Residue::setType (const ResidueType* t) 
  { 
    type = t; 
  }

  
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
  

  bool
  Residue::validateRiboseBuilding () const
  {
    return rib_built_valid;
  }

  
  unsigned int
  Residue::getRiboseBuiltCount () const
  {
    return rib_built_count;
  }

  
  // METHODS -------------------------------------------------------------------


  const HomogeneousTransfo
  Residue::getReferential () const
  {
    Vector3D *pivot[3];
    HomogeneousTransfo t;

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
      gOut (4) << "Residue " << *getType () << " " << getResId () 
	       << " has less than 3 atoms and cannot be moved: " << endl;
    }
    
    if (pivot[0] != 0 && pivot[1] != 0 && pivot[2] != 0) {
      t = HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);
    }
    return t; 
  }


  void 
  Residue::setReferential (const HomogeneousTransfo& m) 
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
      gOut (4) << "Residue " << *getType () << " " << getResId () 
	       << " has less than 3 atoms and cannot be moved: " << endl;
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
  Residue::insert (const Atom &atom)
  {
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (atom.getType (), pos));

    if (inserted.second)
      {
	atomGlobal.push_back (atom.clone ());
	rib_dirty_ref = true;
	rib_built_valid = false;
      }
    else
      {
	*atomGlobal[inserted.first->second] = atom;
      }

    
//     AtomMap::iterator it;
//     it = atomIndex.find (atom.getType ());
//     int pos = size ();

//     if (it == atomIndex.end ())
//       {
// 	atomIndex[atom.getType ()] = pos;
// 	atomGlobal.push_back (atom.clone ());
// 	rib_dirty_ref = true;
// 	rib_built_valid = false;
//       }
//     else
//       {
// 	*atomGlobal[it->second] = atom;
//       }
  }


  Residue::iterator 
  Residue::erase (const AtomType *aType)
  {
    AtomMap::iterator i = atomIndex.find (aType);
    
    if (i!=atomIndex.end ()) {
      vector< Atom* >::const_iterator cit;
      const AtomType* next;
      size_type index;

      rib_dirty_ref = true;
      rib_built_valid = false;
      
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
  Residue::clear() 
  {
    vector< Atom* >::iterator it;
    for (it = atomGlobal.begin (); it != atomGlobal.end (); ++it)
      delete *it;
    atomGlobal.clear ();
    atomIndex.clear();

    rib_C1p = rib_C2p = rib_C3p = rib_C4p = rib_C5p = rib_O2p = rib_O3p = rib_O4p = rib_O5p = rib_P = 0;
    rib_dirty_ref = true;
    rib_built_valid = false;
  }


  void Residue::validate () 
  {
    gOut (6) << "Validating " << resId << " " << *type << endl;

    if (!type) {
      gOut (6) << "Validate called on an empty residue" << endl;
      return;
    }

    if (!type->isNucleicAcid () && !type->isAminoAcid ()) {
      gOut (6) << "Validate called on a unknown residue: " << *type << endl;
      return;
    }
    
    gOut (6) << "Fixed atom content" << endl;

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

    gOut (6) << "Validated obligatory atoms and type is now " 
	     << (type->isUnknown ()? "invalid": "valid") << endl;
  }
  

  void Residue::removeOptionals () 
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


  void Residue::addHydrogens () 
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
	      gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	      gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	      gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	      gOut (2) << "Residue " << *getType () << " " << getResId ()
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
		|| 0 == get(AtomType::aO2) || 0 == get(AtomType::aO4)
		|| 0 == get(AtomType::aC5M)) {
	      gOut (2) << "Residue " << *getType () << " " << getResId ()
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
  Residue::addLonePairs () 
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
	  gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	  gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	  gOut (2) << "Residue " << *getType () << " " << getResId ()
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
	  gOut (2) << "Residue " << *getType () << " " << getResId ()
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

  float
  Residue::getRho () const
  {
    if (!getType ()->isNucleicAcid ())
      throw CLibException ("cannot evaluate pucker pseudorotation for residue type ")
	<< (const char*)*type;

    double nu0, nu1, nu2, nu3, nu4, rho;
    
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
    
    rho = atan2 (nu4+nu1-nu3-nu0, nu2*3.07768354 );

    return rho > 0 ? rho : s_2xpi + rho;
  }

  
  const PropertyType* 
  Residue::getPucker () const
  {
    return getPuckerType (getRho ());
  }


  float
  Residue::getChi () const
  {
    if (!getType ()->isNucleicAcid ())
      throw CLibException ("cannot evaluate glycosyl torsion for residue type ")
	<< (const char*)*type;

    float chi;
    
    if  (getType ()->isPurine ())
      chi = get (AtomType::aC1p)->torsionAngle (*get (AtomType::aO4p),
						 *get (AtomType::aN9),
						*get (AtomType::aC4));
    else 
      chi = get (AtomType::aC1p)->torsionAngle (*get (AtomType::aO4p),
						*get (AtomType::aN1),
						*get (AtomType::aC2));

    return chi;
  }

  
  const PropertyType* 
  Residue::getGlycosyl () const
  {
    return getGlycosylType (getChi ());
  }

  
  void 
  Residue::finalize (bool h_lp)
  {
    Vector3D *v1, *v2, *v3;

    if (!type || empty ()) return;

    // no pseudo atoms in phosphate residue, nothing to do!
    if (getType ()->isPhosphate ())
      return;
    
    if (getType ()->isNucleicAcid () && h_lp) {
      removeOptionals ();
      addHydrogens ();
      addLonePairs ();
    }

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
	gOut (2) << "Residue " << getResId () << "-" << *getType ()
		 << " is missing one or more critical atoms." << endl;		
      }	
    }    
  }


  float 
  Residue::distance (const Residue &r) const
  {
    if (getType ()->isAminoAcid ()) {
      float deltaPseudoPhi =
	find (AtomType::aN)->torsionAngle (*find (AtomType::aH),
					   *find (AtomType::aCA),
					   *find (AtomType::aC))
	- r.find (AtomType::aN)->torsionAngle (*r.find (AtomType::aH),
					       *r.find (AtomType::aCA),
					       *r.find (AtomType::aC));
      
      float deltaPseudoPsi =
	find (AtomType::aCA)->torsionAngle (*find (AtomType::aN),
					    *find (AtomType::aC),
					    *find (AtomType::aO))
	- r.find (AtomType::aCA)->torsionAngle (*r.find (AtomType::aN),
						*r.find (AtomType::aC),
						*r.find (AtomType::aO));
      
      return (min ((float) abs (deltaPseudoPhi), (float)(2 * M_PI - abs (deltaPseudoPhi)))
	      + min ((float) abs (deltaPseudoPsi), (float)(2 * M_PI - abs (deltaPseudoPsi))));
    } else if (getType ()->isNucleicAcid ()) {
      // nucleic acid
      Residue *tmpRef = clone ();
      Residue *tmpRes = r.clone ();
      AtomSet *as;
      float result;
      
      tmpRes->setReferential (tmpRef->getReferential ());

      // This supposes that the atoms are in the same order in the two 
      // residues, which is the case since we iterate on sorted residues 
      // by definition of a residue iterator
      as = new AtomSetAnd (new AtomSetBackbone (),
			   new AtomSetNot (new AtomSetOr (new AtomSetHydrogen (), 
							  new AtomSetAtom (AtomType::aO2p))));
      result = Rmsd::rmsd (tmpRef->begin (as->clone ()), 
			   tmpRef->end (),
			   tmpRes->begin (as),
			   tmpRes->end ());
      delete tmpRef;
      delete tmpRes;
      return result;
    }
    gOut (2) << "Distance metric is not defined for residues " 
	     << *getType () << " and " << *r.getType () << endl;
    return MAXFLOAT;
  }
  

  void Residue::atomCopy (const Residue& other) 
  {
    const Residue *resp = dynamic_cast< const Residue* > (&other);
    
    if (this != &other && resp) {
      if (type != resp->type) {
	CLibException exc ("Invalid residue type ");
	
	exc << *resp->type << ".";
	throw exc;
      }
      
      unsigned int i;
      for (i=0; i<atomGlobal.size (); ++i) {
	*atomGlobal[i] = *resp->atomGlobal[i];
      }
    }
  }

  
  void
  Residue::buildRibose (const PropertyType* pucker, const PropertyType* glycosyl,
			bool build5p, bool build3p)
  {
    float p0 = getMinRho (pucker), p1 = getMaxRho (pucker);
    float g0 = getMinChi (glycosyl), g1 = getMaxChi (glycosyl);
    buildRibose (p0 + (p1 - p0) / 2.0, g0 + (g1 - g0) / 2.0, 1, M_PI, build5p, build3p);
  }

  
  void
  Residue::buildRibose (float rho, float chi, float gamma, float beta,
			bool build5p, bool build3p)
  {
    HomogeneousTransfo tfo;
    Atom a1, a2;
    _build_ribose_preprocess (0, 0,
			      build5p, build3p,
			      a1, a2,
			      tfo);
    _build_ribose (rho, chi, gamma, beta, build5p, build3p);
    _build_ribose_postprocess (tfo, build5p, build3p);
    rib_built_valid = true;
  }

  
  float
  Residue::buildRiboseByCCM4D (const Residue* po4_5p,
			       const Residue* po4_3p,
			       const PropertyType* pucker,
			       const PropertyType* glycosyl)
  {
    return buildRiboseByCCM4D
      (po4_5p, po4_3p, s_rib_minshift, s_rib_mindrop, s_rib_shiftrate, pucker, glycosyl);
  }

  float
  Residue::buildRiboseByCCM4D (const Residue* po4_5p,
			       const Residue* po4_3p,
			       float minshift,
			       float mindrop,
			       float shiftrate,
			       const PropertyType* pucker,
			       const PropertyType* glycosyl)
  {
    HomogeneousTransfo tfo;
    Atom anchor_O5p, anchor_O3p;
    bool build5p = po4_5p == 0;
    bool build3p = po4_3p == 0;

    if (build5p && build3p)
      throw CLibException ("needs at least one phosphate to build ribose for ")
	<< resId;
    
    _build_ribose_preprocess (po4_5p, po4_3p,
			      build5p, build3p,
			      anchor_O5p, anchor_O3p,
			      tfo);
    
    // [0] -> rho
    // [1] -> chi
    // [3] -> gamma
    // [4] -> beta
    
    int i;
    float x[4], new_x[4];
    float p_min[4], p_max[4], p_range[4], p_shift[4];
    float eval_x, eval_new_x;
    bool not_shifted;

    if (pucker)
      {
	p_min[0] = getMinRho (pucker);
	p_max[0] = getMaxRho (pucker);
      }
    else
      {
	p_min[0] = 0.0;
	p_max[0] = s_2xpi;
      }

    if (glycosyl)
      {
	p_min[1] = getMinChi (pucker);
	p_max[1] = getMaxChi (pucker);
      }
    else
      {
	p_min[1] = 0.0;
	p_max[1] = s_2xpi;
      }
    
    p_min[2] = p_min[3] = 0.0;
    p_max[2] = p_max[3] = 360.0;

    for (i = 0; i < 4; ++i)
      {
	p_range[i] = p_max[i] - p_min[i];
	p_shift[i] = 0.25 * p_range[i];
	new_x[i] = x[i] = p_min[i] + 0.5 * p_range[i];
      }

    rib_built_count = 0;
    _build_ribose (x[0], x[1], x[2], x[3], build5p, build3p);
    eval_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    while (p_shift[0] > minshift ||
	   p_shift[1] > minshift ||
	   p_shift[2] > minshift ||
	   p_shift[3] > minshift)
      {
	not_shifted = true;

	for (i = 0; i < 4; ++i)
	  {
	    new_x[i] = x[i] + p_shift[i];
	    if (new_x[i] > p_max[i])
	      new_x[i] = p_max[i];

	    _build_ribose (x[0], x[1], x[2], x[3], build5p, build3p);
	    eval_new_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);
	    
	    if (eval_new_x < eval_x - mindrop)
	      {
		x[i] = new_x[i];
		eval_x = eval_new_x;
		not_shifted = false;
	      }
	    else
	      {
		new_x[i] = x[i] - p_shift[i];
		if (new_x[i] < p_min[i])
		  new_x[i] = p_min[i];

		_build_ribose (x[0], x[1], x[2], x[3], build5p, build3p);
		eval_new_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

		if (eval_new_x < eval_x - mindrop)
		  {
		    x[i] = new_x[i];
		    eval_x = eval_new_x;
		    not_shifted = false;
		  }
		else
		  new_x[i] = x[i];
	      }
	  }
	if (not_shifted)
	  {
	    for (i = 0; i < 4; ++i)
	      p_shift[i] *= shiftrate;
	  }
      }

    _build_ribose (x[0], x[1], x[2], x[3], build5p, build3p);
    eval_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    _build_ribose_postprocess (tfo, build5p, build3p);
    rib_built_valid = true;
    
    return sqrt (eval_x / 2.0);
  }

  
  float
  Residue::buildRiboseByCCM2D (const Residue* po4_5p,
			       const Residue* po4_3p,
			       const PropertyType* pucker,
			       const PropertyType* glycosyl)
  {
    return buildRiboseByCCM2D
      (po4_5p, po4_3p, s_rib_minshift, s_rib_mindrop, s_rib_shiftrate, pucker, glycosyl);
  }


  
  float
  Residue::buildRiboseByCCM2D (const Residue* po4_5p,
			       const Residue* po4_3p,
			       float minshift,
			       float mindrop,
			       float shiftrate,
			       const PropertyType* pucker,
			       const PropertyType* glycosyl)
  {
    HomogeneousTransfo tfo;
    Atom anchor_O5p, anchor_O3p;
    bool build5p = po4_5p == 0;
    bool build3p = po4_3p == 0;

    if (build5p && build3p)
      throw CLibException ("needs at least one phosphate to build ribose for ")
	<< resId;
    
    _build_ribose_preprocess (po4_5p, po4_3p,
			      build5p, build3p,
			      anchor_O5p, anchor_O3p,
			      tfo);

    // [0] -> rho
    // [1] -> chi
    
    int i;
    float x[2], new_x[2];
    float p_min[2], p_max[2], p_range[2], p_shift[2];
    float eval_x, eval_new_x;
    float def_gamma = RAD(55.0);
    float def_beta = M_PI;
    bool not_shifted;

    if (pucker)
      {
	p_min[0] = getMinRho (pucker);
	p_max[0] = getMaxRho (pucker);
      }
    else
      {
	p_min[0] = 0.0;
	p_max[0] = s_2xpi;
      }

    if (glycosyl)
      {
	p_min[1] = getMinChi (pucker);
	p_max[1] = getMaxChi (pucker);
      }
    else
      {
	p_min[1] = 0.0;
	p_max[1] = s_2xpi;
      }
    
    for (i = 0; i < 2; ++i)
      {
	p_range[i] = p_max[i] - p_min[i];
	p_shift[i] = 0.25 * p_range[i];
	new_x[i] = x[i] = p_min[i] + 0.5 * p_range[i];
      }
    
    rib_built_count = 0;
    _build_ribose (x[0], x[1], def_gamma, def_beta, build5p, build3p);
    eval_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    while (p_shift[0] > minshift || p_shift[1] > minshift)
      {
	not_shifted = true;

	for (i = 0; i < 2; ++i)
	  {
	    new_x[i] = x[i] + p_shift[i];
	    if (new_x[i] > p_max[i])
	      new_x[i] = p_max[i];

	    _build_ribose (new_x[0], new_x[1], def_gamma, def_beta, build5p, build3p);
	    eval_new_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);
	    
	    if (eval_new_x < eval_x - mindrop)
	      {
		x[i] = new_x[i];
		eval_x = eval_new_x;
		not_shifted = false;
	      }
	    else
	      {
		new_x[i] = x[i] - p_shift[i];
		if (new_x[i] < p_min[i])
		  new_x[i] = p_min[i];
		
		_build_ribose (new_x[0], new_x[1], def_gamma, def_beta, build5p, build3p);
		eval_new_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);		

		if (eval_new_x < eval_x - mindrop)
		  {
		    x[i] = new_x[i];
		    eval_x = eval_new_x;
		    not_shifted = false;
		  }
		else
		  new_x[i] = x[i];
	      }
	  }
	if (not_shifted)
	  {
	    p_shift[0] *= shiftrate;
	    p_shift[1] *= shiftrate;
	  }
      }

    _build_ribose (x[0], x[1], def_gamma, def_beta, build5p, build3p);
    eval_x = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    _build_ribose_postprocess (tfo, build5p, build3p);
    rib_built_valid = true;
    
    return sqrt (eval_x / 2.0);
  }

  
  float
  Residue::buildRiboseByEstimation (const Residue* po4_5p, const Residue* po4_3p)
  {
    HomogeneousTransfo tfo;
    Atom anchor_O5p, anchor_O3p;
    bool build5p = po4_5p == 0;

    float erho1, erho2;
    float x, z, xz_len;
    float anchor_yrot, built_yrot;
    float value1 = 0, value2 = 0, final_value;
    HomogeneousTransfo rotation;
    
    if (po4_3p == 0)
      throw CLibException ("3' phosphate is mandatory to estimate ribose for ")
	<< resId;

    
    /** preprocessing **/
    
    _build_ribose_preprocess (po4_5p, po4_3p,
			      build5p, false,
			      anchor_O5p, anchor_O3p,
			      tfo);
    rib_built_valid = true;
    rib_built_count = 0;
    
    // dummy O3'
    // O3' must be built for estimation but 3' branch is always constrained
    Atom dummy_O3p;
    rib_O3p = &dummy_O3p;

    
    /** pseudorotation estimation  **/
    
    // O3' YZ plane projection vector length
    x = anchor_O3p.getX ();
    z = anchor_O3p.getZ ();
    xz_len = sqrt (x*x + z*z);
   
    // rho estimation with respect to O3'
    erho1 = (xz_len - s_cosf_vshift) / s_cosf_amplitude;

    // +/- 0.2 tolerance on cos amplitude
    if (erho1 < -1.2 || erho1 > 1.2)
      {
	rib_built_valid = false;
	return MAXFLOAT;
      }
    if (erho1 < -1)
      erho1 = -1;
    else if (erho1 > 1)
      erho1 = 1;

    erho1 = acos (erho1) - s_cosf_phase;

    // get mirror rho
    if  (erho1 > 0)
      erho2 = s_2xpi - 2 * s_cosf_phase - erho1;
    else
      {
	erho1 = s_2xpi + erho1;
	erho2 = s_4xpi - s_cosf_phase - erho1;
      }
  
  
    /** glycosyl torsion estimation **/

    // Y rotation from X axis to anchored O3'
    x = anchor_O3p.getX ();
    z = anchor_O3p.getZ ();
    xz_len = sqrt (x*x + z*z);
    anchor_yrot = z < 0 ? acos (z / xz_len) : s_2xpi - acos (z / xz_len);
    
    // build with first rho. Must build O3'!
    _build_ribose (erho1, 0, 1, M_PI, build5p, true);
  
    // Y rotation from X axis to built O3'
    x = rib_O3p->getX ();
    z = rib_O3p->getZ ();
    xz_len = sqrt (x*x + z*z);
    built_yrot = z < 0 ? acos (z / xz_len) : s_2xpi - acos (z / xz_len);

    // compute estimated chi and apply Y rotation
    _transform_ribose (rotation.rotate (0.0, anchor_yrot - built_yrot, 0.0), build5p, false);
    value1 = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, false);

    // back up this ribose
    vector< Atom > saved_rib;
    saved_rib.push_back (*rib_C1p);
    saved_rib.push_back (*rib_C2p);
    saved_rib.push_back (*rib_C3p);
    saved_rib.push_back (*rib_C4p);
    saved_rib.push_back (*rib_C5p);
    if (rib_O2p)
      saved_rib.push_back (*rib_O2p);
    saved_rib.push_back (*rib_O4p);
    if (build5p)
      {
	saved_rib.push_back (*rib_O5p);
	saved_rib.push_back (*rib_P);
      }
    
    // build with second rho. Must build O3'!
    _build_ribose (erho2, 0, 1, M_PI, build5p, true);
    
    // Y rotation from X axis to built O3'
    x = rib_O3p->getX ();
    z = rib_O3p->getZ ();
    xz_len = sqrt (x*x + z*z);
    built_yrot = z < 0 ? acos (z / xz_len) : s_2xpi - acos (z / xz_len);
  
    // compute estimated chi and apply Y rotation
    _transform_ribose (rotation.rotate (0.0, anchor_yrot - built_yrot, 0.0), build5p, false);
    value2 = _evaluate_ribose (anchor_O5p, anchor_O3p, build5p, false);

    if (value1 < value2)
      {
	// set as first estimation: retrieve back upped ribose.
	int i = -1;
	*rib_C1p = saved_rib[++i];
	*rib_C2p = saved_rib[++i];
	*rib_C3p = saved_rib[++i];
	*rib_C4p = saved_rib[++i];
	*rib_C5p = saved_rib[++i];
	if (rib_O2p)
	  *rib_O2p = saved_rib[++i];
	*rib_O4p = saved_rib[++i];
	if (build5p)
	  {
	    *rib_O5p = saved_rib[++i];
	    *rib_P = saved_rib[++i];
	  }
	final_value = value1;
      }

    // set as second estimation: keep current ribose.
    final_value = value2;
    _build_ribose_postprocess (tfo, build5p, false);
    rib_O3p = 0;

    return sqrt (final_value / 2.0);
  }


  Residue*
  Residue::createPhosphate5p (const Residue& reference,
			      const ResidueFactoryMethod* fm)
  {
    Vector3D phos_v, oxy_v, u, v;
    Residue::const_iterator phos_it, oxy_it;
    
    Residue::const_iterator rib_phos_it = reference.find (AtomType::aP);
    Residue::const_iterator rib_oxy_it = reference.find (AtomType::aO5p);

    if (rib_phos_it == reference.end ())
      throw CLibException ("cannot create phosphate: residue ")
	<< reference.getResId () << " has no atom " << (const char*)*AtomType::aP;
    if (rib_oxy_it == reference.end ())
      throw CLibException ("cannot create phosphate: residue ")
	<< reference.getResId () << " has no atom " << (const char*)*AtomType::aO5p;
    
    Vector3D rib_phos_v (*rib_phos_it), rib_oxy_v (*rib_oxy_it);

    ExtendedResidueFM def_fm;
    if (fm == 0) fm = &def_fm;
    Residue* po4 = fm->createResidue ();
    
    po4->setType (ResidueType::rPhosphate);
    po4->setResId (ResId ("p0"));
    po4->setIdeal (false);
    po4->setReferential (HomogeneousTransfo ());
      
    phos_it = po4->find (AtomType::aP);
    oxy_it = po4->find (AtomType::aO5p);
    phos_v = *phos_it;
  
    po4->transform (HomogeneousTransfo::translation (rib_phos_v - phos_v));
    
    oxy_v = *oxy_it;

    u = oxy_v - rib_phos_v;
    v = rib_oxy_v - rib_phos_v;

    po4->transform
      (HomogeneousTransfo::translation (rib_phos_v) *
       
       HomogeneousTransfo::rotation
       ((u.cross (v)).normalize (), rib_phos_v.angle (oxy_v, rib_oxy_v)) *
       
       HomogeneousTransfo::translation (rib_phos_v * -1));

    return po4;
  }


  const PropertyType*
  Residue::getPuckerType (float rho)
  {
    // adjust value between [0,360]
    while (rho < 0.0)
      rho += s_2xpi;
    while (rho > s_2xpi)
      rho -= s_2xpi;

    if (rho < RAD_36)
      return PropertyType::pC3p_endo;
    else if (rho < RAD_72)
      return PropertyType::pC4p_exo;
    else if (rho < RAD_108)
      return PropertyType::pO4p_endo;
    else if (rho < RAD_144)
      return PropertyType::pC1p_exo;
    else if (rho < RAD_180)
      return PropertyType::pC2p_endo;
    else if (rho < RAD_216)
      return PropertyType::pC3p_exo;
    else if (rho < RAD_252)
      return PropertyType::pC4p_endo;
    else if (rho < RAD_288)
      return PropertyType::pO4p_exo;
    else if (rho < RAD_324)
      return PropertyType::pC1p_endo;
    else 
      return PropertyType::pC2p_exo;   
  }
  

  const PropertyType*
  Residue::getGlycosylType (float chi)
  {
    // adjust value between [-90,270]
    while (chi < -RAD_90)
      chi += s_2xpi;
    while (chi > RAD_270)
      chi -= s_2xpi;

    if (chi < RAD_90)
      return PropertyType::pSyn;
    else 
      return PropertyType::pAnti;
  }
  

  float
  Residue::getMinRho (const PropertyType* pucker)
  {
    if (pucker == PropertyType::pC3p_endo)
      return 0.0;
    else if (pucker == PropertyType::pC4p_exo)
      return RAD_36;
    else if (pucker == PropertyType::pO4p_endo)
      return RAD_72;
    else if (pucker == PropertyType::pC1p_exo)
      return RAD_108;
    else if (pucker == PropertyType::pC2p_endo)
      return RAD_144;
    else if (pucker == PropertyType::pC3p_exo)
      return RAD_180;
    else if (pucker == PropertyType::pC4p_endo)
      return RAD_216;
    else if (pucker == PropertyType::pO4p_exo)
      return RAD_252;
    else if (pucker == PropertyType::pC1p_endo)
      return RAD_288;
    else if (pucker == PropertyType::pC2p_exo)
      return RAD_324;
    else
      throw CLibException ("unknown pucker type ")
	<< (pucker ? (const char*)*pucker : "(null)");
  }

  
  float
  Residue::getMaxRho (const PropertyType* pucker)
  {
    if (pucker == PropertyType::pC3p_endo)
      return RAD_36;
    else if (pucker == PropertyType::pC4p_exo)
      return RAD_72;
    else if (pucker == PropertyType::pO4p_endo)
      return RAD_108;
    else if (pucker == PropertyType::pC1p_exo)
      return RAD_144;
    else if (pucker == PropertyType::pC2p_endo)
      return RAD_180;
    else if (pucker == PropertyType::pC3p_exo)
      return RAD_216;
    else if (pucker == PropertyType::pC4p_endo)
      return RAD_252;
    else if (pucker == PropertyType::pO4p_exo)
      return RAD_288;
    else if (pucker == PropertyType::pC1p_endo)
      return RAD_324;
    else if (pucker == PropertyType::pC2p_exo)
      return RAD_360;
    else
      throw CLibException ("unknown pucker type ")
	<< (pucker ? (const char*)*pucker : "(null)");
  }

  
  float
  Residue::getMinChi (const PropertyType* glycosyl)
  {
    if (glycosyl == PropertyType::pSyn)
      return -RAD_90;
    else if (glycosyl == PropertyType::pAnti)
      return RAD_90;
    else
      throw CLibException ("unknown glycosyl torsion type ")
	<< (glycosyl ? (const char*)*glycosyl : "(null)");
  }

  
  float
  Residue::getMaxChi (const PropertyType* glycosyl)
  {
    if (glycosyl == PropertyType::pSyn)
      return RAD_90;
    else if (glycosyl == PropertyType::pAnti)
      return RAD_270;
    else
      throw CLibException ("unknown glycosyl torsion type ")
	<< (glycosyl ? (const char*)*glycosyl : "(null)");
  }
    
  
  // PRIVATE METHODS -----------------------------------------------------------
  
  
  Atom& 
  Residue::get (size_type pos) const 
  {
    assert (pos < atomGlobal.size ());
    return *atomGlobal[pos];
  }


  Atom* 
  Residue::get (const AtomType* aType) const 
  {
    AtomMap::const_iterator it = atomIndex.find (aType);
    if (it == atomIndex.end ())
      return 0;
    else
      return atomGlobal[it->second];
  }

  Atom*
  Residue::_get_or_create (const AtomType *aType)
  {
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
      {
	atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	rib_dirty_ref = true;
	rib_built_valid = false;
	return atomGlobal[pos];
      }
    else
      {
	return atomGlobal[inserted.first->second];
      }
  }

  
  void
  Residue::_build_ribose_preprocess (const Residue* po4_5p,
				     const Residue* po4_3p,
				     bool build5p,
				     bool build3p,
				     Atom& o5p,
				     Atom& o3p,
				     HomogeneousTransfo& referential)
  {
    Atom* aptr;

    // set reference to ribose's atoms
    
    if (rib_dirty_ref)
      {
	// check residue type (DNA doesn't have a O2')
	if (type->isRNA ())
	  {
	    rib_O2p = _get_or_create (AtomType::aO2p);
	    rib_O2p->set (0.0, 0.0, 0.0);
	  }
	else if (type->isDNA ())
	  rib_O2p = 0;
	else
	  throw CLibException ("cannot build ribose on residue ")
	    << resId << " of type " << (const char*)*type;

	rib_C1p = _get_or_create (AtomType::aC1p);
	rib_C2p = _get_or_create (AtomType::aC2p);
	rib_C3p = _get_or_create (AtomType::aC3p);
	rib_C4p = _get_or_create (AtomType::aC4p);
	rib_C5p = _get_or_create (AtomType::aC5p);
	rib_O4p = _get_or_create (AtomType::aO4p);

	if (build5p)
	  {
	    rib_O5p = _get_or_create (AtomType::aO5p);
	    rib_P   = _get_or_create (AtomType::aP);
	  }
	
	if (build3p)
	  rib_O3p = _get_or_create (AtomType::aO3p);
	
	rib_dirty_ref = false;
      }

    // save referential and align anchor atoms
    
    referential = getReferential ();
    HomogeneousTransfo inv (referential.invert ());
    
    // fetch phosphates' anchor atoms
    
    if (po4_5p)
      {
	if ((aptr = po4_5p->get (AtomType::aO5p)) == 0)
	  throw CLibException ("missing ")
	    << (const char*)*AtomType::aO5p
	    << " in 5' phosphate residue " << po4_5p->resId
	    << " to build ribose for " << resId;
	o5p = *aptr;
	o5p.transform (inv);
      }
    
    if (po4_3p)
      {
	if ((aptr = po4_3p->get (AtomType::aO3p)) == 0)
	  throw CLibException ("missing ")
	    << (const char*)*AtomType::aO3p
	    << " in 3' phosphate residue " << po4_3p->resId
	    << " to build ribose for " << resId;
	o3p = *aptr;
	o3p.transform (inv);
      }

  }


  void
  Residue::_transform_ribose (const HomogeneousTransfo& tfo,
			      bool build5p, bool build3p)
  {
    rib_C1p->transform (tfo);
    rib_C2p->transform (tfo);
    rib_C3p->transform (tfo);
    rib_C4p->transform (tfo);
    rib_C5p->transform (tfo);
    if (rib_O2p)
      rib_O2p->transform (tfo);
    rib_O4p->transform (tfo);

    if (build5p)
      {
	rib_O5p->transform (tfo);
	rib_P->transform (tfo);
      }

    if (build3p)
      rib_O3p->transform (tfo);
  }

  
  void
  Residue::_build_ribose (float rho, float chi, float gamma, float beta,
			  bool build5p, bool build3p)
  {
    // use explicit method for now...
    _build_ribose_explicitly (rho, chi, gamma, beta, build5p, build3p);

    
    
    ++rib_built_count;
    
    // 0.6577118824501829 rad = 37.684115 deg
    // 2.5132741228718345 rad = 144 deg

    float nu0 = 0.6981317007977318 * cos (rho + 3*2.5132741228718345);
    float nu1 = 0.6981317007977318 * cos (rho + 4*2.5132741228718345);

    // building transfo 
    // uses idealized geometries as defined by
    // G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.

    // 1.0746515803304686  rad = 61.573  deg
    // 0.45770037903074895 rad = 26.2243 deg
    // 1.062835701294467   rad = 60.8960 deg
    // 1.024618226663547   rad = 58.7063 deg

    /*
    
    float sin_chi = sin (chi);
    float sin_chi_c2p = sin (chi + 1.0746515803304686);
    float sin_nu1_o2p = sin (nu1  + 0.45770037903074895);
    float sin_nu1_c3p = sin (nu1  - 1.062835701294467);
    float sin_nu0_c4p = sin (nu0  + 1.024618226663547);

    float cos_chi = cos (chi);
    float cos_chi_c2p = cos (chi + 1.0746515803304686);
    float cos_nu1_o2p = cos (nu1  + 0.45770037903074895);
    float cos_nu1_c3p = cos (nu1  - 1.062835701294467);
    float cos_nu0_c4p = cos (nu0  + 1.024618226663547);
  
    // C1' from Nt (N1 or N9)
    HomogeneousTransfo tfo
      (1,0,0,1.465,
       0,1,0,0,
       0,0,1,0);

    rib_C1p->set (0.0, 0.0, 0.0);
    rib_C1p->transform (tfo);

    // O4' from C1'
    tfo.set
      (0.3189593092980698,
       0,
       -0.9477684100095858,
       1.916965341275365,
	 
       -0.9477684100095858*sin_chi,cos_chi,
       -0.3189593092980698*sin_chi,
       -1.342987836983583*sin_chi,
	 
       0.9477684100095858*cos_chi,
       sin_chi,
       0.3189593092980698*cos_chi,
       1.342987836983583*cos_chi);

    rib_O4p->set (0.0, 0.0, 0.0);
    rib_O4p->transform (tfo);
      
    // C2' from C1'
    tfo.set
      (0.37505965617503256,
       0,
       0.9270006765422916,
       2.038466214291625,
	 
       0.9270006765422916*sin_chi_c2p,
       cos_chi_c2p,
       -0.37505965617503256*sin_chi_c2p,
       1.4173840344331636*sin_chi_c2p,
	 
       -0.9270006765422916*cos_chi_c2p,
       sin_chi_c2p,
       0.37505965617503256*cos_chi_c2p,
       -1.4173840344331636*cos_chi_c2p);

    rib_C2p->set (0.0, 0.0, 0.0);
    rib_C2p->transform (tfo);

    if (rib_O2p)
      {
	// O2' from C2'
	tfo.set
	  (0.37505965617503256,
	   0.9270006765422916*sin_nu1_o2p,
	   0.9270006765422916*cos_nu1_o2p,
	   2.2177447299432904 + 1.0391677584039087*cos_nu1_o2p - 0.6646594850808231*sin_nu1_o2p,
	
	   0.9270006765422916*sin_chi_c2p,
	   cos_chi_c2p*cos_nu1_o2p - 0.37505965617503256*sin_chi_c2p*sin_nu1_o2p,
	   -0.37505965617503256*cos_nu1_o2p*sin_chi_c2p - cos_chi_c2p*sin_nu1_o2p,
	   cos_chi_c2p*(-0.717*cos_nu1_o2p - 1.121*sin_nu1_o2p) + sin_chi_c2p*(1.860490357820379 - 0.4204418745722115*cos_nu1_o2p + 0.26891777347749835*sin_nu1_o2p),
	
	   -0.9270006765422916*cos_chi_c2p,cos_nu1_o2p*sin_chi_c2p + 0.37505965617503256*cos_chi_c2p*sin_nu1_o2p,
	   0.37505965617503256*cos_chi_c2p*cos_nu1_o2p - sin_chi_c2p*sin_nu1_o2p,
	   sin_chi_c2p*(-0.717*cos_nu1_o2p - 1.121*sin_nu1_o2p) + cos_chi_c2p*(-1.860490357820379 + 0.4204418745722115*cos_nu1_o2p - 0.26891777347749835*sin_nu1_o2p));

	rib_O2p->set (0.0, 0.0, 0.0);
	rib_O2p->transform (tfo);
      }
    
    // C3' from C2'
    tfo.set
      (0.07442844670182767 + 0.9085646439620313*cos_nu1_c3p,
       0.9270006765422916*sin_nu1_c3p,
       -0.3676005332037575 + 0.18395798991077703*cos_nu1_c3p,
       2.1518207386185084 + 1.3837439527541735*cos_nu1_c3p,

       (0.18395798991077703 - 0.3676005332037575*cos_nu1_c3p)*sin_chi_c2p - 0.9801121692283693*cos_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*cos_nu1_c3p - 0.37505965617503256*sin_chi_c2p*sin_nu1_c3p,
       (-0.9085646439620313 - 0.07442844670182767*cos_nu1_c3p)*sin_chi_c2p - 0.1984442887322796*cos_chi_c2p*sin_nu1_c3p,
       (1.697552053067277 - 0.5598556120693227*cos_nu1_c3p)*sin_chi_c2p - 1.4927108337348063*cos_chi_c2p*sin_nu1_c3p,
	
       cos_chi_c2p*(-0.18395798991077703 + 0.3676005332037575*cos_nu1_c3p) - 0.9801121692283693*sin_chi_c2p*sin_nu1_c3p,
       cos_nu1_c3p*sin_chi_c2p + 0.37505965617503256*cos_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*(0.9085646439620313 + 0.07442844670182767*cos_nu1_c3p) - 0.1984442887322796*sin_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*(-1.697552053067277 + 0.5598556120693227*cos_nu1_c3p) - 1.4927108337348063*sin_chi_c2p*sin_nu1_c3p);

    rib_C3p->set (0.0, 0.0, 0.0);
    rib_C3p->transform (tfo);
      
    // C4' from O4'
    tfo.set
      (0.10751967079428061 + 0.8922960413273637*cos_nu0_c4p,
       -0.9477684100095858*sin_nu0_c4p,
       0.3002907946977251 - 0.3194882370974149*cos_nu0_c4p,
       2.0730839032686603 + 1.2956138520073321*cos_nu0_c4p,

       (-0.3194882370974149 + 0.3002907946977251*cos_nu0_c4p)*sin_chi + 0.941470544812038*cos_chi*sin_nu0_c4p,
       cos_chi*cos_nu0_c4p - 0.3189593092980698*sin_chi*sin_nu0_c4p,
       (-0.8922960413273637 - 0.10751967079428061*cos_nu0_c4p)*sin_chi - 0.3370952584230821*cos_chi*sin_nu0_c4p,
       (-1.8068847572490294 + 0.43602223390109685*cos_nu0_c4p)*sin_chi + 1.3670152310670791*cos_chi*sin_nu0_c4p,

       cos_chi*(0.3194882370974149 - 0.3002907946977251*cos_nu0_c4p) + 0.941470544812038*sin_chi*sin_nu0_c4p,
       cos_nu0_c4p*sin_chi + 0.3189593092980698*cos_chi*sin_nu0_c4p,
       cos_chi*(0.8922960413273637 + 0.10751967079428061*cos_nu0_c4p) - 0.3370952584230821*sin_chi*sin_nu0_c4p,
       cos_chi*(1.8068847572490294 - 0.43602223390109685*cos_nu0_c4p) + 1.3670152310670791*sin_chi*sin_nu0_c4p);

    rib_C4p->set (0.0, 0.0, 0.0);
    rib_C4p->transform (tfo);

    */

    chi *= 180.0 / M_PI;
    nu0 *= 180.0 / M_PI;
    nu1 *= 180.0 / M_PI;

    HomogeneousTransfo tfo, c1p, c2p, o4p;
    
    // step 1 : C1'
    tfo = tfo.translate (0, -1.465, 0);
    rib_C1p->set (0.0, 0.0, 0.0);
    rib_C1p->transform (tfo);

    c1p = tfo;
    
    // step 2 : O4' with respect to chi (from C1')
    tfo = tfo.rotate (0.0, -chi * M_PI / 180.0, 0.0);
    tfo = tfo.rotate (0.0, 0.0, 71.47 * M_PI / 180.0);
    tfo = tfo.translate (0.0, -1.417, 0.0);
    rib_O4p->set (0.0, 0.0, 0.0);
    rib_O4p->transform (tfo);

    o4p = tfo;
      
    // step 2 : C2' with respect to chi (from C1')
    tfo = c1p;
    tfo = tfo.rotate (0.0 , (118.44 - chi) * M_PI / 180.0, 0.0);
    tfo = tfo.rotate (0.0, 0.0, 67.972 * M_PI / 180.0);
    tfo = tfo.translate (0.0, -1.529, 0.0);
    rib_C2p->set (0.0, 0.0, 0.0);
    rib_C2p->transform (tfo);

    c2p = tfo;
      
    // step 3 : C3' with respect to nu1 (from C2')
    //tfo.setIdentity ();
    tfo = tfo.rotate (0.0, (240.838 - nu1) * M_PI / 180.0, 0.0);
    tfo = tfo.rotate (0.0, 0.0, 78.554 * M_PI / 180.0);
    tfo = tfo.translate (0.0, -1.523, 0.0);
    rib_C3p->set (0.0, 0.0, 0.0);
    rib_C3p->transform (tfo);

    if (rib_O2p)
      {
	// step 3 : O2' with respect to nu1 (from C2')

	tfo = c2p;
	tfo = tfo.rotate (0.0, (121.160 - nu1) * M_PI / 180.0, 0.0);
	tfo = tfo.rotate (0.0, 0.0, 70.232 * M_PI / 180.0);
	tfo = tfo.translate (0.0, -1.414, 0.0);
	rib_O2p->set (0.0, 0.0, 0.0);
	rib_O2p->transform (tfo);
      }

    // step 4 : C4' with respect to nu0 (from O4')

    tfo = o4p;
    tfo = tfo.rotate (0.0, (121.335 - nu0) * M_PI / 180.0, 0.0);
    tfo = tfo.rotate (0.0, 0.0, 70.3 * M_PI / 180.0);
    tfo = tfo.translate (0.0, -1.452, 0.0);
    rib_C4p->set (0.0, 0.0, 0.0);
    rib_C4p->transform (tfo);

    // C5' => align first for 5' branch
    HomogeneousTransfo branch5p =
      HomogeneousTransfo::align (*rib_C4p, *rib_C3p, *rib_O4p);
  
//     tfo.set (0.4983470223041225,
// 	     -0.783262352599052,
// 	     -0.3716857979014169,
// 	     1.1827261524245685,
	     
// 	     0.,
// 	     0.4287143941490142,
// 	     -0.9034400745204099,
// 	     -0.6473587351650114,
	     
// 	     0.8669776498622179,
// 	     0.4502266709674608,
// 	     0.21364854174307712,
// 	     -0.6798422731608658);

    tfo.setIdentity ();
    tfo = tfo.rotate (0.0, 29.891 * M_PI / 180.0, 0.0);
    tfo = tfo.rotate (0.0, 0.0, 64.614 * M_PI / 180.0);
    tfo = tfo.translate (0.0, -1.510, 0.0);
    
    rib_C5p->set (0.0, 0.0, 0.0);
    rib_C5p->transform (branch5p * tfo);

    if (build5p)
      {	// O5' from C5' according to gamma => align first for 5' branch
// 	float cos_gamma = cos (gamma);
// 	float sin_gamma = sin (gamma);

// 	tfo.set
// 	  (0.4983470223041225*cos_gamma - 0.3716857979014169*sin_gamma,
// 	   -0.26019509810650415 - 0.3505781564521977*cos_gamma - 0.47004642453183026*sin_gamma,
// 	   0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma,
// 	   1.5574070936979345 + 0.5048325452911646*cos_gamma + 0.6768668513258356*sin_gamma,
	 
// 	   -0.9034400745204099*sin_gamma,
// 	   0.14241637361367576 - 0.8521346728303227*cos_gamma,
// 	   -0.40436815932672815 - 0.3001174230360551*cos_gamma,
// 	   -0.8524383131687046 + 1.2270739288756647*cos_gamma,
	 
// 	   0.8669776498622179*cos_gamma + 0.21364854174307712*sin_gamma,
// 	   0.14956262411160473 + 0.20151566811507393*cos_gamma - 0.8177429105175843*sin_gamma,
// 	   -0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma,
// 	   -0.8952124518815765 - 0.2901825620857065*cos_gamma + 1.1775497911453214*sin_gamma);

	tfo = tfo.rotate (0.0, -gamma, 0.0);
	tfo = tfo.rotate (0.0, 0.0, 70.598 * M_PI / 180.0);
	tfo = tfo.translate (0.0, -1.440, 0.0);
	
	rib_O5p->set (0.0, 0.0, 0.0);
	rib_O5p->transform (branch5p * tfo);
	
	// P5' from O5' according to beta => align first for 5' branch
// 	float cos_beta = cos (beta);
// 	float sin_beta = sin (beta);

// 	tfo.set
// 	  (cos_beta*(0.4983470223041225*cos_gamma - 0.3716857979014169*sin_gamma) + sin_beta*(0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma),
// 	   -0.26019509810650415 - 0.3505781564521977*cos_gamma - 0.47004642453183026*sin_gamma,
// 	   cos_beta*(0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma) + sin_beta*(-0.4983470223041225*cos_gamma + 0.3716857979014169*sin_gamma),
// 	   1.7704808595373507 + cos_gamma*(0.7919209976098692 + 0.680941371276353*sin_beta) + cos_beta*(-1.0094713367650046 + 0.1687118851431224*cos_gamma + 0.22620467626984803*sin_gamma) + (1.0617878683749513 - 0.5078714742524961*sin_beta)*sin_gamma,
	 
// 	   -0.9034400745204099*sin_gamma*cos_beta + sin_beta*(-0.40436815932672815 - 0.3001174230360551*cos_gamma),
// 	   0.14241637361367576 - 0.8521346728303227*cos_gamma,
// 	   cos_beta*(-0.40436815932672815 - 0.3001174230360551*cos_gamma) + 0.9034400745204099*sin_beta*sin_gamma,
// 	   -0.9690630815209436 + 1.9248870124564157*cos_gamma + cos_beta*(0.5525286529040414 + 0.4100804468364657*cos_gamma) - 1.2344605178246881*sin_beta*sin_gamma,
	 
// 	   sin_beta*(-0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma) + cos_beta*(0.8669776498622179*cos_gamma + 0.21364854174307712*sin_gamma),
// 	   0.14956262411160473 + 0.20151566811507393*cos_gamma - 0.8177429105175843*sin_gamma,
// 	   cos_beta*(-0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma) + sin_beta*(-0.8669776498622179*cos_gamma - 0.21364854174307712*sin_gamma),
// 	   -1.0176892847665697 + cos_gamma*(-0.45520374270514047 + 1.1846382607717347*sin_beta) + cos_beta*(0.5802537526292064 - 0.09697720074070179*cos_gamma + 0.3935297891688724*sin_gamma) + (1.847199460568171 + 0.2919293674377406*sin_beta)*sin_gamma);

	tfo = tfo.rotate (0.0, -beta, 0.0);
	tfo = tfo.rotate (0.0, 0.0, 59.066 * M_PI / 180.0);
	tfo = tfo.translate (0.0, -1.593, 0.0);
	
	rib_P->set (0.0, 0.0, 0.0);
	rib_P->transform (branch5p * tfo);
      }

    if (build3p)
      { // O3' => align first for 3' branch
	HomogeneousTransfo branch3p =
	  HomogeneousTransfo::align (*rib_C3p, *rib_C4p, *rib_C2p);
  
// 	tfo.set (0.5043859675317346,
// 		 -0.8016153916448716,
// 		 -0.3209479079774709,
// 		 1.1471116254438114,
	     
// 		 0.,
// 		 0.3716919156133742,
// 		 -0.9283561384876282,
// 		 -0.5318911312427386,
	 
// 		 0.8634783122679318,
// 		 0.46824980912510733,
// 		 0.18747618648037562,
// 		 -0.6700654768580286);

	tfo.setIdentity ();
	tfo = tfo.rotate (0.0, 30.291 * M_PI / 180.0, 0.0);
	tfo = tfo.rotate (0.0, 0.0, 68.18 * M_PI / 180.0);
	tfo = tfo.translate (0.0, -1.431, 0.0);

	rib_O3p->set (0.0, 0.0, 0.0);
	rib_O3p->transform (branch3p * tfo);
      }
  }

  
  void
  Residue::_build_ribose_explicitly (float rho, float chi, float gamma, float beta,
				     bool build5p, bool build3p)
  {
    ++rib_built_count;

    float nu0 = RAD(37.68) * cos (rho + 3 * RAD(144));
    float nu1 = RAD(37.68) * cos (rho + 4 * RAD(144));

    HomogeneousTransfo c1p, c2p, o4p, c5p, branch5p;

    // procedure from local referential:
    // fixed -Y translation for bond length
    // fixed +Z rotation for bond angle
    // variable Y rotation to respect torsion parameter (if any) 
    
    // C1' (only a translation is needed)
    c1p = HomogeneousTransfo::translation (Vector3D (0.0, -1.465, 0.0));
    rib_C1p->set (0.0, 0.0, 0.0);
    rib_C1p->transform (c1p);
    
    // O4' with respect to chi (from C1')
    o4p =
      HomogeneousTransfo::rotationY (-chi) *
      HomogeneousTransfo::rotationZ (RAD(71.47)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.417, 0.0)) *
      c1p;
    rib_O4p->set (0.0, 0.0, 0.0);
    rib_O4p->transform (o4p);
      
    // C2' with respect to chi (from C1')
    c2p =
      HomogeneousTransfo::rotationY (RAD(118.44) - chi) *
      HomogeneousTransfo::rotationZ (RAD(67.972)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.529, 0.0)) *
      c1p;
    rib_C2p->set (0.0, 0.0, 0.0);
    rib_C2p->transform (c2p);
      
    // C3' with respect to nu1 (from C2')
    rib_C3p->set (0.0, 0.0, 0.0);
    rib_C3p->transform
      (HomogeneousTransfo::rotationY (RAD(240.838) - nu1) *
       HomogeneousTransfo::rotationZ (RAD(78.554)) *
       HomogeneousTransfo::translation (Vector3D (0.0, -1.523, 0.0)) *
       c2p);

    if (rib_O2p)
      {
	// O2' with respect to nu1 (from C2')
	rib_O2p->set (0.0, 0.0, 0.0);
	rib_O2p->transform
	  (HomogeneousTransfo::rotationY (RAD(121.160) - nu1) *
	   HomogeneousTransfo::rotationZ (RAD(70.232)) *
	   HomogeneousTransfo::translation (Vector3D (0.0, -1.414, 0.0)) *
	   c2p);
      }

    // C4' with respect to nu0 (from O4')
    rib_C4p->set (0.0, 0.0, 0.0);
    rib_C4p->transform
      (HomogeneousTransfo::rotationY (RAD(121.335) - nu0) *
       HomogeneousTransfo::rotationZ (RAD(70.3)) *
       HomogeneousTransfo::translation (Vector3D (0.0, -1.452, 0.0)) *
       o4p);

    // C5' aligned on furanose for 5' branch
    branch5p =
      HomogeneousTransfo::align (*rib_C4p, *rib_C3p, *rib_O4p);
    c5p =
      HomogeneousTransfo::rotationY (RAD(29.891)) *
      HomogeneousTransfo::rotationZ (RAD(64.614)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.510, 0.0));
    rib_C5p->set (0.0, 0.0, 0.0);
    rib_C5p->transform (branch5p * c5p);

    if (build5p)
      {
	// O5' from C5' according to gamma (aligned on furanose for 5' branch)
	HomogeneousTransfo o5p =
	  HomogeneousTransfo::rotationY (-gamma) *
	  HomogeneousTransfo::rotationZ (RAD(70.598)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.440, 0.0)) *
	  c5p;
	rib_O5p->set (0.0, 0.0, 0.0);
	rib_O5p->transform (branch5p * o5p);

	// P from O5' according to beta (aligned on furanose for 5' branch)
	rib_P->set (0.0, 0.0, 0.0);
	rib_P->transform
	  (branch5p *
	   HomogeneousTransfo::rotationY (-beta) *
	   HomogeneousTransfo::rotationZ (RAD(59.066)) *
	   HomogeneousTransfo::translation (Vector3D (0.0, -1.593, 0.0)) *
	   o5p);
      }

    if (build3p)
      {
	// O3' aligned on furanose for 3' branch
	rib_O3p->set (0.0, 0.0, 0.0);
	rib_O3p->transform
	  (HomogeneousTransfo::align (*rib_C3p, *rib_C4p, *rib_C2p) *
	   HomogeneousTransfo::rotationY (RAD(30.291)) *
	   HomogeneousTransfo::rotationZ (RAD(68.18)) *
	   HomogeneousTransfo::translation (Vector3D (0.0, -1.431, 0.0)));
      }
  }

  
  float
  Residue::_evaluate_ribose (const Atom& o5p, const Atom& o3p,
			     bool build5p, bool build3p) const
  {
    return
      (build5p ? 2.0736 : rib_C5p->squareDistance (o5p)) +
      (build3p ? 2.047761 : rib_C3p->squareDistance (o3p));
  }
  
  void
  Residue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
				      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential
    _transform_ribose (referential, build5p, build3p);
  }
  
  // I/O -----------------------------------------------------------------------


  ostream&
  Residue::output (ostream &os) const 
  {
    os << resId << type;
//     AtomMap::const_iterator cit;
//     for (cit=atomIndex.begin (); cit!=atomIndex.end (); ++cit) {
//       os << endl << *(atomGlobal[cit->second]);
//     }
    return os;
  }
  
  
  iBinstream& 
  Residue::input (iBinstream &ibs)
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
  Residue::output (oBinstream &obs) const
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
  operator<< (ostream &os, const Residue &r)
  {
    return r.output (os);
  }

  // ostream&
//   operator<< (ostream &os, const Residue *r)
//   {
//     return r->output (os);
//   }

  iBinstream& operator>> (iBinstream &ibs, Residue &res)
  {
    return res.input (ibs);
  }


  oBinstream& operator<< (oBinstream &obs, const Residue &res)
  {
    return res.output (obs);
  }


  iPdbstream& 
  operator>> (iPdbstream &ips, Residue &res)
  {
    ips.read (res);
    return ips;
  }



  oPdbstream&
  operator<< (oPdbstream &ops, const Residue &res)
  {
    ops.write (res);
    return ops;
  }

  

  // ITERATORS -----------------------------------------------------------------


  Residue::ResidueIterator::ResidueIterator ()
    : res (0),
      filter (new AtomSetAll ())
  {
  }
  


  Residue::ResidueIterator::ResidueIterator (Residue *r,
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
  


  Residue::ResidueIterator::ResidueIterator (const ResidueIterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  {
  }



  Residue::ResidueIterator::~ResidueIterator ()
  {
    delete filter;
  }
  


  Residue::ResidueIterator&
  Residue::ResidueIterator::operator= (const ResidueIterator &right)
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



  Residue::ResidueIterator&
  Residue::ResidueIterator::operator+= (difference_type k)
  {
    AtomMap::iterator last = res->atomIndex.end ();

    while (k > 0 && pos != last)
      if (++pos != last && (*filter) (res->get (pos->second)))
	--k;
    return *this;
  }


  
  Residue::iterator&
  Residue::ResidueIterator::operator++ ()
  {
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return *this;
  }



  Residue::iterator
  Residue::ResidueIterator::operator++ (int ign)
  {
    ResidueIterator ret = *this;
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return ret;
  }



  Residue::ResidueConstIterator::ResidueConstIterator ()
    : res (0),
      filter (new AtomSetAll ())
  { }



  Residue::ResidueConstIterator::ResidueConstIterator (const Residue *r,
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



  Residue::ResidueConstIterator::ResidueConstIterator (const Residue::const_iterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  { }



  Residue::ResidueConstIterator::ResidueConstIterator (const Residue::iterator &right)
    : res (((ResidueConstIterator&) right).res),
      pos (((ResidueConstIterator&) right).pos),
      filter (((ResidueConstIterator&) right).filter->clone ())
  { }



  Residue::ResidueConstIterator::~ResidueConstIterator ()
  {
    delete filter;
  }



  Residue::const_iterator&
  Residue::ResidueConstIterator::operator= (const Residue::const_iterator &right)
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



  Residue::const_iterator&
  Residue::ResidueConstIterator::operator= (const Residue::iterator &right)
  {
    res = ((ResidueConstIterator&) right).res;
    pos = ((ResidueConstIterator&) right).pos;
    delete filter;
    filter = ((ResidueConstIterator&) right).filter->clone ();
    return *this;
  }



  Residue::const_iterator&
  Residue::ResidueConstIterator::operator+= (difference_type k)
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (k > 0 && pos != last)
      if (++pos != last && (*filter) (res->get (pos->second)))
	--k;
    return *this;
  }



  Residue::const_iterator&
  Residue::ResidueConstIterator::operator++ ()
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return *this;
  }



  Residue::const_iterator
  Residue::ResidueConstIterator::operator++ (int ign)
  {
    ResidueConstIterator ret = *this;
    AtomMap::const_iterator last = res->atomIndex.end ();
  
    while (pos != last)
      if (++pos == last || (*filter) (res->get (pos->second)))
	break;
    return ret;
  }


}
