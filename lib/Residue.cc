//                              -*- Mode: C++ -*-
// Residue.cc
// Copyright � 2003-07 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al
// Author           : Patrick Gendron
// Created On       : Fri Mar 14 16:44:35 2003
// $Revision: 1.88 $
// $Id: Residue.cc,v 1.88 2007-01-14 18:21:04 larosem Exp $
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
#include <cmath>
#include <set>

#include "Binstream.h"
#include "Pdbstream.h"
#include "PropertyType.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueTopology.h"
#include "ResidueType.h"
#include "ResidueFactoryMethod.h"
#include "Rmsd.h"
#include "Messagestream.h"

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

#define RAD(deg) (deg * M_PI / 180.0)
#define DEG(rad) (rad * 180.0 / M_PI)



namespace mccore
{
  // GLOBAL CONSTANT ---------------------------------------------------------

  /**
   * Constants used in hydrogens and lone pairs positioning.
   * Parameters taken for AMBER all_nuc94.in
   */
  const float C_H_DIST_CYC = 1.08;     // C-H distance for aromatic C
  const float C_H_DIST     = 1.09;     // C-H distance for SP3 C
  const float N_H_DIST     = 1.01;     // N-H distance for NH2 confo
  const float O_H_DIST     = 0.96;
  const float O_LP_DIST    = 1.00;
  const float N_LP_DIST    = 1.00;
  const float TAN19        = 0.3443276;  // O2' H
  const float TAN30        = 0.57735027;
  const float TAN54        = 1.3763819;
  const float TAN60        = 1.7320508;  // For NH2-like conformations
  const float TAN70        = 2.7474774;  // For CH3-like conformations
  const float TAN71        = 2.9042109;

  const float gc_2xpi = 6.283185482025146484375;

  /**
   * Pseudorotation estimation parameters
   */
  const float gc_cosf_amplitude = 1.3305;
  const float gc_cosf_vshift    = 2.0778;
  const float gc_cosf_phase     = 0.3041;
  const float gc_cosf_2xphase   = 0.6082;

  // STATIC MEMBER -----------------------------------------------------------

  float Residue::s_rib_minshift  = 0.1;
  float Residue::s_rib_mindrop   = 0.00001;
  float Residue::s_rib_shiftrate = 0.5;

  // LIFECYCLE ---------------------------------------------------------------

  Residue::Residue ()
    : rib_C1p (0), rib_C2p (0), rib_C3p (0), rib_C4p (0), rib_C5p (0), rib_O2p (0),
      rib_O3p (0), rib_O4p (0), rib_O5p (0), rib_O1P (0), rib_O2P (0), rib_P (0),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    this->setType (0);
  }


  Residue::Residue (const ResidueType *t, const ResId &i)
    : resId (i),
      rib_C1p (0), rib_C2p (0), rib_C3p (0), rib_C4p (0), rib_C5p (0), rib_O2p (0),
      rib_O3p (0), rib_O4p (0), rib_O5p (0), rib_O1P (0), rib_O2P (0), rib_P (0),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    this->setType (t);
  }


  Residue::Residue (const ResidueType *t, const ResId &i, const vector< Atom > &vec)
    : resId (i),
      rib_C1p (0), rib_C2p (0), rib_C3p (0), rib_C4p (0), rib_C5p (0), rib_O2p (0),
      rib_O3p (0), rib_O4p (0), rib_O5p (0), rib_O1P (0), rib_O2P (0), rib_P (0),
      rib_dirty_ref (true),
      rib_built_valid (false),
      rib_built_count (0)
  {
    vector< Atom >::const_iterator it;

    this->setType (t);

    for (it = vec.begin (); it != vec.end (); ++it)
      this->insert (*it);
  }


  Residue::Residue (const Residue& res)
    : type (res.type),
      resId (res.resId),
      atomIndex (res.atomIndex),
      rib_C1p (0), rib_C2p (0), rib_C3p (0), rib_C4p (0), rib_C5p (0), rib_O2p (0),
      rib_O3p (0), rib_O4p (0), rib_O5p (0), rib_O1P (0), rib_O2P (0), rib_P (0),
      rib_dirty_ref (true),
      rib_built_valid (res.rib_built_valid),
      rib_built_count (res.rib_built_count)
  {
    vector< Atom* >::iterator cit;

    res.place (); // places globals if "res" is an ExtendedResidue
    this->atomGlobal = res.atomGlobal;

    // harden atoms
    for (cit = this->atomGlobal.begin (); cit != this->atomGlobal.end (); ++cit)
      *cit = (*cit)->clone ();
  }


  Residue::~Residue ()
  {
    vector< Atom* >::iterator it;

    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      delete *it;
  }

  // VIRTUAL ASSIGNATION --------------------------------------------------

  Residue&
  Residue::assign (const Residue& res)
  {
    if (this != &res)
      this->_assign (res);
    return *this;
  }


  void
  Residue::_assign (const Residue& res)
  {
    vector< Atom* >::iterator it;
    vector< Atom* >::const_iterator cit;

    this->type = res.type;
    this->resId = res.resId;
    this->atomIndex = res.atomIndex;

    // -- deep copy for atomGlobal
    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      delete *it;
    this->atomGlobal = res.atomGlobal;
    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      *it = (*it)->clone ();

    // -- ribose pointers are reset, but building validity is kept from
    //    copied object.
    //    This means that the ribose atoms can have correct
    //    positions, but any building from this point will need to fetch
    //    the atom pointers from this object.
    this->rib_C1p = this->rib_C2p = this->rib_C3p = this->rib_C4p = this->rib_C5p = this->rib_O2p = this->rib_O3p = this->rib_O4p = this->rib_O5p = this->rib_O1P = this->rib_O2P = this->rib_P = 0;
    this->rib_dirty_ref = true;
    this->rib_built_valid = res.rib_built_valid;
    this->rib_built_count = res.rib_built_count;
  }

  // OPERATORS ------------------------------------------------------------

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

  // ACCESS ------------------------------------------------------------------

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
    type = t == 0 ? ResidueType::rNull : t;
  }

  Residue::iterator
  Residue::begin ()
  {
    iterator it (this, atomIndex.begin ());
    return it;
  }

  Residue::iterator
  Residue::begin (const AtomSet& atomset)
  {
    iterator it (this, atomIndex.begin (), atomset);
    return it;
  }


  Residue::iterator
  Residue::end ()
  {
    iterator it (this, atomIndex.end ());
    return it;
  }


  Residue::const_iterator
  Residue::begin () const
  {
    const_iterator it (this, atomIndex.begin ());
    return it;
  }


  Residue::const_iterator
  Residue::begin (const AtomSet& atomset) const
  {
    const_iterator it (this, atomIndex.begin (), atomset);
    return it;
  }


  Residue::const_iterator
  Residue::end () const
  {
    const_iterator it (this, atomIndex.end ());
    return it;
  }


  Residue::iterator
  Residue::find (const AtomType *k)
  {
    AtomMap::iterator it = atomIndex.find (k);

    if (it == atomIndex.end ())
      return end ();
    else
    {
      iterator nit (this, it);
      return nit;
    }
  }


  Residue::const_iterator
  Residue::find (const AtomType *k) const
  {
    AtomMap::const_iterator cit = atomIndex.find (k);

    if (cit == atomIndex.end ())
      return end ();
    else
    {
      const_iterator it (this, cit);
      return it;
    }
  }


  Residue::iterator
  Residue::safeFind (const AtomType *k)
  {
    AtomMap::iterator mit = atomIndex.find (k);

    if (mit == atomIndex.end ())
    {
      NoSuchAtomException ex ("", __FILE__, __LINE__);
      ex << "residue " << *this << " is missing atom " << k;
      throw ex;
    }

    iterator it (this, mit);
    return it;
  }


  Residue::const_iterator
  Residue::safeFind (const AtomType *k) const
  {
    AtomMap::const_iterator cit = atomIndex.find (k);

    if (cit == atomIndex.end ())
    {
      NoSuchAtomException ex ("", __FILE__, __LINE__);
      ex << "residue " << *this << " is missing atom " << k;
      throw ex;
    }

    const_iterator it (this, cit);
    return it;
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

  // METHODS -----------------------------------------------------------------

  const HomogeneousTransfo
  Residue::getReferential () const
  {
    // needed to patch numerical instability
    //this->_set_pseudos ();

    return this->_compute_referential ();
  }


  void
  Residue::setReferential (const HomogeneousTransfo& m)
  {
    // needed to patch numerical instability
    this->_set_pseudos ();

    vector< Atom* >::iterator it;
    HomogeneousTransfo t  = m * this->_compute_referential ().invert ();

    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      (*it)->transform (t);
  }


  void
  Residue::transform (const HomogeneousTransfo& m)
  {
    vector< Atom* >::iterator it;

    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      (*it)->transform (m);
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
    }
    else
    {
      *atomGlobal[inserted.first->second] = atom;
    }
  }


  Residue::iterator
  Residue::erase (const AtomType *atype)
  {
    return erase (find (atype));
  }


  Residue::iterator
  Residue::erase (const iterator& rit)
  {
    if (this->end () != rit)
    {
      vector< Atom* >::iterator avit;
      vector< Atom* >::const_iterator cavit;
      AtomMap::iterator next_position;
      const AtomType* atype = 0;
      size_type index = 0;

      // -- invalidate ribose pointers
      this->rib_dirty_ref = true;

      // -- get type for the following atom.
      iterator nrit = rit + 1;
      if (this->end () != nrit)
	atype = nrit.pos->first;

      // -- delete the indexed atom
      avit = this->atomGlobal.begin () + rit.pos->second;
      delete *avit;
      this->atomGlobal.erase (avit);

      // -- recreate the atom index
      this->atomIndex.clear ();
      for (cavit = this->atomGlobal.begin (); cavit != this->atomGlobal.end (); ++cavit)
	this->atomIndex.insert (make_pair ((*cavit)->getType (), index++));

      if (atype)
      {
	// -- retrieve the appropriate iterator following the deletion point.
	if (this->atomIndex.end () == (next_position = this->atomIndex.find (atype)))
	{
	  FatalIntLibException ex ("", __FILE__, __LINE__);
	  ex << "failed to erase atom " << rit.pos->first << " from " << *this;
	  throw ex;
	}
	iterator next_rit (this, next_position, *rit.filter);
	return next_rit;
      }
    }
    return this->end ();
  }


  Residue::size_type
  Residue::size () const
  {
    return atomIndex.size ();
  }


  bool
  Residue::empty () const
  {
    return atomIndex.empty ();
  }


  void
  Residue::clear ()
  {
    vector< Atom* >::iterator it;

    for (it = this->atomGlobal.begin (); it != this->atomGlobal.end (); ++it)
      delete *it;

    this->atomGlobal.clear ();
    this->atomIndex.clear();

    this->rib_C1p = this->rib_C2p = this->rib_C3p = this->rib_C4p = this->rib_C5p = this->rib_O2p = this->rib_O3p = this->rib_O4p = this->rib_O5p = this->rib_O1P = this->rib_O2P = this->rib_P = 0;
    this->rib_dirty_ref = true;
    this->rib_built_valid = false;
  }


  void
  Residue::setTheoretical (bool base_with_C1p)
  {
    this->clear ();
    Atom atom;

    if (this->type->isA ())
    {
      this->insert (atom.set ( 0.213f,  0.660f,  1.287f, AtomType::aN9));
      this->insert (atom.set ( 0.250f,  2.016f,  1.509f, AtomType::aC4));
      this->insert (atom.set ( 0.016f,  2.995f,  0.619f, AtomType::aN3));
      this->insert (atom.set ( 0.142f,  4.189f,  1.194f, AtomType::aC2));
      this->insert (atom.set ( 0.451f,  4.493f,  2.459f, AtomType::aN1));
      this->insert (atom.set ( 0.681f,  3.485f,  3.329f, AtomType::aC6));
      this->insert (atom.set ( 0.990f,  3.787f,  4.592f, AtomType::aN6));
      this->insert (atom.set ( 0.579f,  2.170f,  2.844f, AtomType::aC5));
      this->insert (atom.set ( 0.747f,  0.934f,  3.454f, AtomType::aN7));
      this->insert (atom.set ( 0.520f,  0.074f,  2.491f, AtomType::aC8));

      if (base_with_C1p)
	this->insert (atom.set (-0.093f, -0.004f,  0.018f, AtomType::aC1p));

      this->insert (atom.set ( -0.0303076f, 5.03468f, 0.54474f, AtomType::aH2));
      this->insert (atom.set ( 1.04802f, 4.75317f, 4.88051f, AtomType::a1H6));
      this->insert (atom.set ( 1.16578f, 3.04933f, 5.25911f, AtomType::a2H6));
      this->insert (atom.set ( 0.569712f, -0.995716f, 2.63113f, AtomType::aH8));
      this->insert (atom.set ( 0.510616f, 5.44634f, 2.75495f, AtomType::aLP1));
      this->insert (atom.set ( -0.219929f, 2.84729f, -0.341479f, AtomType::aLP3));
      this->insert (atom.set ( 0.985635f, 0.744068f, 4.40635f, AtomType::aLP7));
    }
    else if (this->type->isC ())
    {
      this->insert (atom.set ( 0.212f,  0.668f,  1.294f, AtomType::aN1));
      this->insert (atom.set ( 0.193f, -0.043f,  2.462f, AtomType::aC6));
      this->insert (atom.set ( 0.374f,  2.055f,  1.315f, AtomType::aC2));
      this->insert (atom.set ( 0.388f,  2.673f,  0.240f, AtomType::aO2));
      this->insert (atom.set ( 0.511f,  2.687f,  2.504f, AtomType::aN3));
      this->insert (atom.set ( 0.491f,  1.984f,  3.638f, AtomType::aC4));
      this->insert (atom.set ( 0.631f,  2.649f,  4.788f, AtomType::aN4));
      this->insert (atom.set ( 0.328f,  0.569f,  3.645f, AtomType::aC5));

      if (base_with_C1p)
	this->insert (atom.set (0.064f, -0.006f,  0.002f, AtomType::aC1p));

      this->insert (atom.set ( 0.620979f, 2.14851f, 5.66522f, AtomType::a1H4));
      this->insert (atom.set ( 0.746876f, 3.6523f, 4.78031f, AtomType::a2H4));
      this->insert (atom.set ( 0.313722f, 0.00583071f, 4.57813f, AtomType::aH5));
      this->insert (atom.set ( 0.0671006f, -1.11515f, 2.42957f, AtomType::aH6));
      this->insert (atom.set ( 0.284334f, 2.178f, -0.622688f, AtomType::a1LP2));
      this->insert (atom.set ( 0.502955f, 3.66636f, 0.235793f, AtomType::a2LP2));
      this->insert (atom.set ( 0.627097f, 3.67983f, 2.53261f, AtomType::aLP3));
    }
    else if (this->type->isG ())
    {
      this->insert (atom.set ( 0.214f,  0.659f,  1.283f, AtomType::aN9));
      this->insert (atom.set ( 0.254f,  2.014f,  1.509f, AtomType::aC4));
      this->insert (atom.set ( 0.034f,  2.979f,  0.591f, AtomType::aN3));
      this->insert (atom.set ( 0.142f,  4.190f,  1.110f, AtomType::aC2));
      this->insert (atom.set (-0.047f,  5.269f,  0.336f, AtomType::aN2));
      this->insert (atom.set ( 0.444f,  4.437f,  2.427f, AtomType::aN1));
      this->insert (atom.set ( 0.676f,  3.459f,  3.389f, AtomType::aC6));
      this->insert (atom.set ( 0.941f,  3.789f,  4.552f, AtomType::aO6));
      this->insert (atom.set ( 0.562f,  2.154f,  2.846f, AtomType::aC5));
      this->insert (atom.set ( 0.712f,  0.912f,  3.448f, AtomType::aN7));
      this->insert (atom.set ( 0.498f,  0.057f,  2.485f, AtomType::aC8));

      if (base_with_C1p)
	this->insert (atom.set (-0.075f, -0.005f,  0.009f, AtomType::aC1p));

      this->insert (atom.set ( 0.502066f, 5.40203f, 2.7193f, AtomType::aH1));
      this->insert (atom.set ( -0.271768f, 5.15574f, -0.642136f, AtomType::a1H2));
      this->insert (atom.set ( 0.0354486f, 6.19476f, 0.731306f, AtomType::a2H2));
      this->insert (atom.set ( 0.539896f, -1.01379f, 2.61934f, AtomType::aH8));
      this->insert (atom.set ( -0.184759f, 2.79908f, -0.368048f, AtomType::aLP3));
      this->insert (atom.set ( 0.988664f, 4.75695f, 4.79856f, AtomType::a2LP6));
      this->insert (atom.set ( 1.10746f, 3.08769f, 5.24515f, AtomType::a1LP6));
      this->insert (atom.set ( 0.933818f, 0.716543f, 4.4033f, AtomType::aLP7));
    }
    else if (this->type->isU ())
    {
      this->insert (atom.set ( 0.212f,  0.676f,  1.281f, AtomType::aN1));
      this->insert (atom.set ( 0.195f, -0.023f,  2.466f, AtomType::aC6));
      this->insert (atom.set ( 0.370f,  2.048f,  1.265f, AtomType::aC2));
      this->insert (atom.set ( 0.390f,  2.698f,  0.235f, AtomType::aO2));
      this->insert (atom.set ( 0.505f,  2.629f,  2.502f, AtomType::aN3));
      this->insert (atom.set ( 0.497f,  1.990f,  3.725f, AtomType::aC4));
      this->insert (atom.set ( 0.629f,  2.653f,  4.755f, AtomType::aO4));
      this->insert (atom.set ( 0.329f,  0.571f,  3.657f, AtomType::aC5));

      if (base_with_C1p)
	this->insert (atom.set (0.063f, -0.008f, -0.006f, AtomType::aC1p));

      this->insert (atom.set ( 0.632158f, 3.71141f, 2.51965f, AtomType::aH3));
      this->insert (atom.set ( 0.310285f, -0.0229714f, 4.57076f, AtomType::aH5));
      this->insert (atom.set ( 0.0682911f, -1.09504f, 2.43321f, AtomType::aH6));
      this->insert (atom.set ( 0.289004f, 2.23923f, -0.647795f, AtomType::a1LP2));
      this->insert (atom.set ( 0.507414f, 3.69039f, 0.272225f, AtomType::a2LP2));
      this->insert (atom.set ( 0.624348f, 2.19893f, 5.64595f, AtomType::a1LP4));
      this->insert (atom.set ( 0.740793f, 3.64521f, 4.70007f, AtomType::a2LP4));
    }
    else if (this->type->isT ())
    {
      this->insert (atom.set ( 0.214f,  0.668f,  1.296f, AtomType::aN1));
      this->insert (atom.set ( 0.171f, -0.052f,  2.470f, AtomType::aC6));
      this->insert (atom.set ( 0.374f,  2.035f,  1.303f, AtomType::aC2));
      this->insert (atom.set ( 0.416f,  2.705f,  0.284f, AtomType::aO2));
      this->insert (atom.set ( 0.483f,  2.592f,  2.553f, AtomType::aN3));
      this->insert (atom.set ( 0.449f,  1.933f,  3.767f, AtomType::aC4));
      this->insert (atom.set ( 0.560f,  2.568f,  4.812f, AtomType::aO4));
      this->insert (atom.set ( 0.279f,  0.500f,  3.685f, AtomType::aC5));
      this->insert (atom.set ( 0.231f, -0.299f,  4.949f, AtomType::aC5M));

      if (base_with_C1p)
	this->insert (atom.set (0.000f,  0.000f,  0.000f, AtomType::aC1p));


      this->insert (atom.set ( 0.610471f, 3.67381f, 2.59215f, AtomType::aH3));
      this->insert (atom.set ( 0.338584f, 0.359726f, 5.81075f, AtomType::a1H5M));
      this->insert (atom.set ( 1.03978f, -1.02966f, 4.95911f, AtomType::a2H5M));
      this->insert (atom.set ( -0.72125f, -0.824345f, 5.02202f, AtomType::a3H5M));
      this->insert (atom.set ( 0.0428929f, -1.12249f, 2.40652f, AtomType::aH6));
      this->insert (atom.set ( 0.332737f, 2.2627f, -0.608996f, AtomType::a1LP2));
      this->insert (atom.set ( 0.533682f, 3.69636f, 0.341925f, AtomType::a2LP2));
      this->insert (atom.set ( 0.535573f, 2.09218f, 5.69121f, AtomType::a1LP4));
      this->insert (atom.set ( 0.67483f, 3.56099f, 4.78389f, AtomType::a2LP4));
    }
    else if (this->type->isPhosphate ())
    {
      this->insert (atom.set ( 4.691f,  0.327f, -2.444f, AtomType::aP));
      this->insert (atom.set ( 5.034f,  1.678f, -1.932f, AtomType::aO1P));
      this->insert (atom.set ( 4.718f,  0.068f, -3.906f, AtomType::aO2P));
      this->insert (atom.set ( 3.246f, -0.057f, -1.895f, AtomType::aO5p));
      this->insert (atom.set ( 5.662f, -0.712f, -1.734f, AtomType::aO3p));
    }
    else if (this->type->isRibose ())
    {
      this->insert (atom.set ( 0.000f,  0.000f,  0.000f, AtomType::aC1p));
      this->insert (atom.set (-0.694f, -0.627f, -1.210f, AtomType::aC2p));
      this->insert (atom.set ( 0.499f, -1.031f, -2.067f, AtomType::aC3p));
      this->insert (atom.set ( 1.509f, -1.478f, -1.022f, AtomType::aC4p));
      this->insert (atom.set ( 2.957f, -1.393f, -1.443f, AtomType::aC5p));
      this->insert (atom.set ( 1.286f, -0.587f,  0.103f, AtomType::aO4p));

      this->insert (atom.set ( -0.608679f, -0.1782100f,  0.886482f, AtomType::aH1p));
      this->insert (atom.set ( -1.391530f,  0.0203483f, -1.741500f, AtomType::aH2p));
      this->insert (atom.set (  0.859627f, -0.2273900f, -2.709070f, AtomType::aH3p));
      this->insert (atom.set (  1.354260f, -2.5362900f, -0.811835f, AtomType::aH4p));
      this->insert (atom.set (  3.151990f, -2.1054000f, -2.244600f, AtomType::a1H5p));
      this->insert (atom.set (  3.602570f, -1.6472600f, -0.602352f, AtomType::a2H5p));

      if (this->type->isRNA ())
      {
	this->insert (atom.set (-1.474f, -1.731f, -0.795f, AtomType::aO2p));
	this->insert (atom.set ( -1.90769f, -2.12145f, -1.55727f, AtomType::aHO2p));
      }

      if (this->type->isRibose5 () || this->type->isRibose53 ())
      {
	this->insert (atom.set ( 4.691f,  0.327f, -2.444f, AtomType::aP));
	this->insert (atom.set ( 5.034f,  1.678f, -1.932f, AtomType::aO1P));
	this->insert (atom.set ( 4.718f,  0.068f, -3.906f, AtomType::aO2P));
	this->insert (atom.set ( 3.246f, -0.057f, -1.895f, AtomType::aO5p));
      }

      if (this->type->isRibose3 () || this->type->isRibose53 ())
	this->insert (atom.set ( 0.178f, -2.084f, -2.981f, AtomType::aO3p));
    }
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "cannot create a theoretical residue for " << *this;
      throw ex;
    }

    this->finalize ();

    const HomogeneousTransfo identity;
    this->setReferential (identity);
  }


  void
  Residue::setFullTheoretical ()
  {
    if (this->type->isNucleicAcid ())
      this->setTheoretical ();
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "cannot create a full theoretical residue for " << *this;
      throw ex;
    }

    // create a C3' endo anti ribose
    this->buildRibose (PropertyType::pC3p_endo, PropertyType::pAnti, true, true);
  }


  void
  Residue::validate ()
  {
    gOut (6) << "Validating residue " << *this << " ..." << endl;

    if (!type)
    {
      gOut (6) << "\tCannot validate an untyped residue" << endl;
      return;
    }

    if (!(type->isNucleicAcid () || type->isAminoAcid ()))
    {
      gOut (6) << "\tCannot validate unhandled residue type: " << type << endl;
      return;
    }

    /*
      O3' and O3P mismatches
      - if both O3P and O3' are present -> remove O3P atom
      - if O3P is present but O3' isn't -> rename O3P atom type to O3'
    */
    Atom* O3_P = this->_get (AtomType::aO3P);
    if (0 != O3_P)
    {
      if (0 == this->_get (AtomType::aO3p))
      {
	O3_P->setType (AtomType::aO3p);
	this->insert (*O3_P);
	this->erase (AtomType::aO3P);
	gOut (4) << "\tRenamed O3P to O3' in residue " << *this << endl;
      }
      else
      {
	this->erase (AtomType::aO3P);
	gOut (4) << "\tRemoved O3P in residue " << *this << endl;
      }
    }

    set< const AtomType* > actset;
    set< const AtomType* > diffset;
    set< const AtomType* > oblset = ResidueTopology::getOblSet (type);
    set< const AtomType* >::const_iterator ait;
    AtomMap::iterator i;

    for (i=atomIndex.begin (); i!=atomIndex.end (); ++i)
      actset.insert (i->first);

//     gOut (7) << "\t\thas\tneed" << endl;
//     set< const AtomType* >::const_iterator ait2;
//     ait = actset.begin ();
//     ait2 = oblset.begin ();
//   LOOP_BODY:
//     if (actset.end () ==  ait)
//     {
//       while (ait2 != oblset.end ())
// 	gOut (7) << "\t\t   \t" << *(ait2++) << endl;
//       goto LOOP_END;
//     }
//     if (oblset.end () ==  ait2)
//     {
//       while (ait != actset.end ())
// 	gOut (7) << "\t\t" << *(ait++) << endl;
//       goto LOOP_END;
//     }
//     if (*ait == *ait2)
//       gOut (7) << "\t\t" << *(ait++) << "\t" << *(ait2++) << endl;
//     else if (*ait < *ait2)
//       gOut (7) << "\t\t" << *(ait++) << endl;
//     else
//       gOut (7) << "\t\t   \t" << *(ait2++) << endl;
//     goto LOOP_BODY;
//   LOOP_END:

    set_difference (oblset.begin (), oblset.end (),
 		    actset.begin (), actset.end (),
		    inserter (diffset, diffset.begin ()));

    if (diffset.empty ())
    {
      // Add here the removal of non obligatory or optional atoms.

      set_difference (actset.begin (), actset.end (),
		      oblset.begin (), oblset.end (),
		      inserter (diffset, diffset.begin ()));
      gOut (6) << "\tResidue " << *this
	       << " has the following non-obligatory atoms: "
	       << endl << "\t\t";
      for (ait = diffset.begin (); diffset.end () != ait; ++ait)
	gOut (6) << *ait << ' ';
      gOut (6) << endl;
    }
    else
    {
      gOut (6) << "\tResidue " << *this
	       << " is invalidated because the following atoms are missing: "
	       << endl << "\t\t";
      for (ait = diffset.begin (); diffset.end () != ait; ++ait)
	gOut (6) << *ait << ' ';
      gOut (6) << endl;

      type = type->invalidate ();
    }

    gOut (6) << "Validated obligatory atoms and type is now "
	     << (type->isUnknown ()? "invalid": "valid") << endl;
  }

  bool Residue::isValid() const
  {
	  set< const AtomType* > actset;
	  set< const AtomType* > diffset;
	  set< const AtomType* > oblset = ResidueTopology::getOblSet (type);
	  set< const AtomType* >::const_iterator ait;
	  AtomMap::const_iterator i;

	  // Get the actual list of atoms
	  for (i=atomIndex.begin (); i!=atomIndex.end (); ++i)
	  {
		  actset.insert (i->first);
	  }

	  // Check if some obligatory atoms are missing
	  std::set_difference (oblset.begin (), oblset.end (),
			  actset.begin (), actset.end (),
	  		  inserter (diffset, diffset.begin ()));

	  return diffset.empty();
  }


  void
  Residue::removeOptionals ()
  {
    if (!type->isNucleicAcid () && !type->isAminoAcid ()) return;
    set< const AtomType* > oblset = ResidueTopology::getOblSet (type);
    iterator i;
    const AtomType* t;

    i = begin ();
    while (i != end ())
    {
      t = i->getType ();
      if (oblset.find (t) == oblset.end ())
	i = erase (i);
      else
	++i;
    }
  }


  void
  Residue::putH (const AtomType *a1, const AtomType *a, const AtomType *a2, const AtomType *h, float dist)
  {
    try
      {
	Vector3D z;
	Vector3D v;
	Atom atom;

	z = ((*_safe_get (a) - *_safe_get (a1)).normalize ()
	     + (*_safe_get (a) - *_safe_get (a2)).normalize ()).normalize ();
	v = *_safe_get (a) + z * dist;
	insert (atom.set (v, h));
      }
    catch (NoSuchAtomException& ex)
      {
	gOut (4) << "Failed to add hydrogen " << h << " in " << *this << ": "
		 << ex << endl;
      }
  }


  void
  Residue::putH6 (const AtomType *a1, const AtomType *a6, const AtomType *a5, const AtomType *an6, const AtomType *a1h6, const AtomType *a2h6)
  {
    try
      {
	Vector3D a;
	Vector3D b;
	Vector3D v;
	Vector3D x;
	Vector3D y;
	Vector3D z;
	Vector3D up;
	Atom atom;

	x = (*_safe_get (a6) - *_safe_get (a1)).normalize ();
	y = (*_safe_get (a6) - *_safe_get (a5)).normalize ();
	z = (*_safe_get (an6) - *_safe_get (a6)).normalize ();  // axe N6-C6
	up = x.cross (y).normalize ();

	a = (z + up.cross (z).normalize () * TAN60).normalize ();
	v = *_safe_get (an6) + a * N_H_DIST;
	insert (atom.set (v, a1h6));

	b = (z + z.cross (up).normalize () * TAN60).normalize ();
	v = *_safe_get (an6) + b * N_H_DIST;
	insert (atom.set (v, a2h6));
      }
    catch (NoSuchAtomException& ex)
      {
	gOut (4) << "Failed to add hydrogens " << a1h6 << " and "
		 << a2h6 << " in " << *this << ": " << ex << endl;
      }
  }


  void
  Residue::putMethylH (const AtomType *a1, const AtomType *a2, const AtomType *ac, const AtomType *a1h, const AtomType *a2h, const AtomType *a3h)
  {
    try // a1h, a2h and a3h are arbitrarily placed
      {
	Vector3D a;
	Vector3D b;
	Vector3D v;
	Vector3D x;
	Vector3D y;
	Vector3D z;
	Vector3D up;
	Atom atom;

	x = (*_safe_get (ac) - *_safe_get (a1)).normalize ();
	y = (*_safe_get (a1) - *_safe_get (a2)).normalize ();
	up = x.cross (y).normalize ();
	z = x.cross (up);

	v = *_safe_get (ac) + (x + z * TAN70).normalize () * C_H_DIST;
	insert (atom.set (v, a1h));

	a = (up - z * TAN30).normalize ();
	v = *_safe_get (ac) + (x + a * TAN70).normalize () * C_H_DIST;
	insert (atom.set (v, a2h));

	b = (-up - z * TAN30).normalize ();
	v = *_safe_get (ac) + (x + b * TAN70).normalize () * C_H_DIST;
	insert (atom.set (v, a3h));
      }
    catch (NoSuchAtomException& ex)
      {
	gOut (4) << "Failed to add hydrogens " << a1h << ", "
		 << a2h << " and " << a3h << " in "
		 << *this << ": " << ex << endl;
      }
  }


  void
  Residue::addHydrogens (bool overwrite)
  {
    Vector3D x, y, z, up, a, b, v;
    Atom atom;

    if (type->isA () || type->is (ResidueType::r1MA))
      {
	if (overwrite || 0 == _get (AtomType::aH2))
	  {
	    // H2
	    putH (AtomType::aN1, AtomType::aC2, AtomType::aN3, AtomType::aH2, C_H_DIST_CYC);
	  }
	if (overwrite || 0 == _get (AtomType::aH8))
	  {
	    // H8
	    putH (AtomType::aN7, AtomType::aC8, AtomType::aN9, AtomType::aH8, C_H_DIST_CYC);
	  }
	if (type->isA ())  // H61 and H62
	  {
	    if (overwrite || 0 == _get (AtomType::a1H6) || 0 == _get (AtomType::a2H6))
	      {
		putH6 (AtomType::aN1, AtomType::aC6, AtomType::aC5, AtomType::aN6, AtomType::a1H6, AtomType::a2H6);
	      }
	  }
	else // 1HN6 and 2HN6
	  {
	    if (overwrite || 0 == _get (AtomType::a1HN6) || 0 == _get (AtomType::a2HN6))
	      {
		putH6 (AtomType::aN1, AtomType::aC6, AtomType::aC5, AtomType::aN6, AtomType::a1HN6, AtomType::a2HN6);
	      }
	  }
      }
    else if (type->isG ())
      {
	if (overwrite || 0 == _get (AtomType::aH1))
	  {
	    // H1
	    putH (AtomType::aC2, AtomType::aN1, AtomType::aC6, AtomType::aH1, N_H_DIST);
	  }
	if (overwrite || 0 == _get (AtomType::aH8))
	  {
	    // H8
	    putH (AtomType::aN7, AtomType::aC8, AtomType::aN9, AtomType::aH8, C_H_DIST_CYC);
	  }
	if (overwrite || 0 == _get (AtomType::a1H2) || 0 == _get (AtomType::a2H2))
	  try // 1H2 and 2H2
	    {
	      x = (*_safe_get (AtomType::aC2) - *_safe_get (AtomType::aN1)).normalize ();
	      y = (*_safe_get (AtomType::aC2) - *_safe_get (AtomType::aN3)).normalize ();
	      z = (*_safe_get (AtomType::aN2) - *_safe_get (AtomType::aC2)).normalize ();  // axe N2-C2
	      up = x.cross (y).normalize ();

	      b = (z + z.cross (up).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aN2) + b * N_H_DIST;
	      insert (atom.set (v, AtomType::a1H2));

	      a = (z + up.cross (z).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aN2) + a * N_H_DIST;
	      insert (atom.set (v, AtomType::a2H2));
	    }
	  catch (NoSuchAtomException& ex)
	    {
	      gOut (4) << "Failed to add hydrogens " << AtomType::a1H2 << " and "
		       << AtomType::a2H2 << " in " << *this << ": " << ex << endl;
	    }
      }
    else if (type->isPyrimidine ())
      {
	if (overwrite || 0 == _get (AtomType::aH6))
	  {
	    // H6
	    putH (AtomType::aC5, AtomType::aC6, AtomType::aN1, AtomType::aH6, C_H_DIST_CYC);
	  }

	if (type->isC () || type->isU ())
	  {
	    if (overwrite || 0 == _get (AtomType::aH5))
	      {
		// H5
		putH (AtomType::aC4, AtomType::aC5, AtomType::aC6, AtomType::aH5, C_H_DIST);
	      }
	  }
	else if (type->is (ResidueType::rPSU))
	  {
	    if (overwrite || 0 == _get (AtomType::aH1))
	      {
		// H5
		putH (AtomType::aC6, AtomType::aN1, AtomType::aC2, AtomType::aH1, C_H_DIST);
	      }
	  }
	else // Methylated
	  {
	    if (overwrite || 0 == _get (AtomType::a1H5M)
		|| 0 == _get (AtomType::a2H5M)
		|| 0 == _get (AtomType::a3H5M))
	      {
		putMethylH (AtomType::aC5, AtomType::aC4, AtomType::aC5M, AtomType::a1H5M, AtomType::a2H5M, AtomType::a3H5M);
	      }
	  }
	if (type->isC ())
	  {
	    if (overwrite || 0 == _get (AtomType::a1H4) || 0 == _get (AtomType::a2H4))
	      try // 1H4 and 2H4
		{
		  x = (*_safe_get (AtomType::aC4) - *_safe_get (AtomType::aN3)).normalize ();
		  y = (*_safe_get (AtomType::aC4) - *_safe_get (AtomType::aC5)).normalize ();
		  z = (*_safe_get (AtomType::aN4) - *_safe_get (AtomType::aC4)).normalize ();
		  up = x.cross (y).normalize ();

		  b = (z + z.cross (up).normalize () * TAN60).normalize ();
		  v = *_safe_get (AtomType::aN4) + b * N_H_DIST;
		  insert (atom.set (v, AtomType::a1H4));

		  a = (z + up.cross (z).normalize () * TAN60).normalize ();
		  v = *_safe_get (AtomType::aN4) + a * N_H_DIST;
		  insert (atom.set (v, AtomType::a2H4));
		}
	      catch (NoSuchAtomException& ex)
		{
		  gOut (4) << "Failed to add hydrogens " << AtomType::a1H4 << " and "
			   << AtomType::a2H4 << " in " << *this << ": " << ex << endl;
		}
	  }
	else if (type->isU () || type->isT () || type->is (ResidueType::r5MU)
		 || type->is (ResidueType::rPSU))
	  {
	    if (overwrite || 0 == _get (AtomType::aH3))
	      {
		// H3
		putH (AtomType::aC2, AtomType::aN3, AtomType::aC4, AtomType::aH3, C_H_DIST);
	      }
	  }
      }
    if (type->is (ResidueType::r1MA)) // Add a methyl group on CM1
      {
	if (overwrite
	    || 0 == _get (AtomType::a1HM1)
	    || 0 == _get (AtomType::a2HM1)
	    || 0 == _get (AtomType::a3HM1))
	  {
	    putMethylH (AtomType::aN1, AtomType::aC2, AtomType::aCM1, AtomType::a1HM1, AtomType::a2HM1, AtomType::a3HM1);
	  }
      }
    _add_ribose_hydrogens (overwrite);
  }


  void
  Residue::_add_ribose_hydrogens (bool overwrite)
  {
    Vector3D x, y, z, up, v;
    Atom atom;

    const Vector3D *r1;
    const Vector3D *r2;
    const Vector3D *r3;
    const Vector3D *r4;

    if (overwrite || 0 == this->_get (AtomType::aH1p))
      {
	try
	  {
	    r1 = this->_safe_get (AtomType::aC1p);
	    r2 = this->_safe_get (AtomType::aC2p);
	    r3 = this->_safe_get (Residue::nitrogenType19 (this->type));
	    r4 = this->_safe_get (AtomType::aO4p);

	    x = (*r1 - *r2).normalize ();
	    y = (*r1 - *r3).normalize ();
	    z = (*r1 - *r4).normalize ();

	    v = *r1 + (x + y + z).normalize () * C_H_DIST;
	    this->insert (atom.set (v, AtomType::aH1p));
	  }
	catch (NoSuchAtomException& ex)
	  {
	    gOut (4) << "Failed to add hydrogen " << AtomType::aH1p << " in "
		     << *this << ": " << ex << endl;
	  }
	catch (TypeException& ex)
	  {
	    gOut (4) << "Failed to add hydrogen " << AtomType::aH1p << " in "
		     << *this << ": " << ex << endl;
	  }
      }

    if (overwrite || 0 == this->_get (AtomType::aH3p))
      {
	try
	  {
	    r1 = this->_safe_get (AtomType::aC3p);
	    r2 = this->_safe_get (AtomType::aC2p);
	    r3 = this->_safe_get (AtomType::aO3p);
	    r4 = this->_safe_get (AtomType::aC4p);

	    x = (*r1 - *r2).normalize ();
	    y = (*r1 - *r3).normalize ();
	    z = (*r1 - *r4).normalize ();

	    v = *r1 + (x + y + z).normalize () * C_H_DIST;
	    this->insert (atom.set (v, AtomType::aH3p));
	  }
	catch (NoSuchAtomException& ex)
	  {
	    gOut (4) << "Failed to add hydrogen " << AtomType::aH3p << " in "
		     << *this << ": " << ex << endl;
	  }
      }

    if (overwrite || 0 == this->_get (AtomType::aH4p))
      {
	try
	  {
	    r1 = this->_safe_get (AtomType::aC4p);
	    r2 = this->_safe_get (AtomType::aC3p);
	    r3 = this->_safe_get (AtomType::aO4p);
	    r4 = this->_safe_get (AtomType::aC5p);

	    x = (*r1 - *r2).normalize ();
	    y = (*r1 - *r3).normalize ();
	    z = (*r1 - *r4).normalize ();

	    v = *r1 + (x + y + z).normalize () * C_H_DIST;
	    this->insert (atom.set (v, AtomType::aH4p));
	  }
	catch (NoSuchAtomException& ex)
	  {
	    gOut (4) << "Failed to add hydrogen " << AtomType::aH4p << " in "
		     << *this << ": " << ex << endl;
	  }
      }

    if (overwrite || 0 == this->_get (AtomType::a1H5p) || 0 == this->_get (AtomType::a2H5p))
      {
	try
	  {
	    r1 = this->_safe_get (AtomType::aC5p);
	    r2 = this->_safe_get (AtomType::aC4p);
	    r3 = this->_safe_get (AtomType::aO5p);

	    x = (*r1 - *r2).normalize ();
	    y = (*r1 - *r3).normalize ();
	    z = (x + y).normalize ();
	    up = x.cross (y).normalize ();

	    v = *r1 + (up * TAN54 + z).normalize () * C_H_DIST;
	    this->insert (atom.set (v, AtomType::a1H5p));

	    v = *r1 + (-up * TAN54 + z).normalize () * C_H_DIST;
	    this->insert (atom.set (v, AtomType::a2H5p));
	  }
	catch (NoSuchAtomException& ex)
	  {
	    gOut (4) << "Failed to add hydrogens " << AtomType::a1H5p << " and "
		     << AtomType::a2H5p << " in " << *this << ": " << ex << endl;
	  }
      }

    // check for O2'
    //   yes -> RNA ribose: H2p and HO2p
    //   no  -> DNA ribose: 1H2p and 2H2p

    if (0 == this->_get (AtomType::aO2p))
      {
	if (overwrite || 0 == this->_get (AtomType::a1H2p) || 0 == this->_get (AtomType::a2H2p))
	  {
	    try
	      {
		r1 = this->_safe_get (AtomType::aC2p);
		r2 = this->_safe_get (AtomType::aC1p);
		r3 = this->_safe_get (AtomType::aC3p);

		x = (*r1 - *r2).normalize ();
		y = (*r1 - *r3).normalize ();
		z = (x + y).normalize ();
		up = x.cross (y).normalize ();

		v = *r1 + (up * TAN54 + z).normalize () * C_H_DIST;
		this->insert (atom.set (v, AtomType::a1H2p));

		v = *r1 + (-up * TAN54 + z).normalize () * C_H_DIST;
		this->insert (atom.set (v, AtomType::a2H2p));
	      }
	    catch (NoSuchAtomException& ex)
	      {
		gOut (4) << "Failed to add hydrogens " << AtomType::a1H2p << " and "
			 << AtomType::a2H2p << " in " << *this << ": " << ex << endl;
	      }
	  }
      }
    else
      {
	if (overwrite || 0 == this->_get (AtomType::aH2p))
	  {
	    try
	      {
		r1 = this->_safe_get (AtomType::aC2p);
		r2 = this->_safe_get (AtomType::aC1p);
		r3 = this->_safe_get (AtomType::aC3p);
		r4 = this->_safe_get (AtomType::aO2p);

		x = (*r1 - *r2).normalize ();
		y = (*r1 - *r3).normalize ();
		z = (*r1 - *r4).normalize ();

		v = *r1 + (x + y + z).normalize () * C_H_DIST;
		this->insert (atom.set (v, AtomType::aH2p));
	      }
	    catch (NoSuchAtomException& ex)
	      {
		gOut (4) << "Failed to add hydrogen " << AtomType::aH2p << " in "
			 << *this << ": " << ex << endl;
	      }
	  }
	if (overwrite || 0 == this->_get (AtomType::aHO2p))
	  {
	    try
	      {
		r1 = this->_safe_get (AtomType::aO2p);
		r2 = this->_safe_get (AtomType::aC2p);
		r3 = this->_safe_get (AtomType::aC1p);

		x = (*r2 - *r3).normalize ();
		y = (*r1 - *r2).normalize ();
		z = x.cross (y).cross (y).normalize ();

		v = *r1 + (y * TAN19 - z).normalize () * O_H_DIST;
		this->insert (atom.set (v, AtomType::aHO2p));
	      }
	    catch (NoSuchAtomException& ex)
	      {
		gOut (4) << "Failed to add hydrogen " << AtomType::aHO2p << " in "
			 << *this << ": " << ex << endl;
	      }
	  }
      }

  }


  void
  Residue::addHO3p (bool overwrite)
  {
    if (overwrite || 0 == this->_get (AtomType::aHO3p))
      {
	try
	  {
	    Atom atom;
	    const Vector3D *r1 = this->_safe_get (AtomType::aO3p);
	    const Vector3D *r2 = this->_safe_get (AtomType::aC3p);
	    const Vector3D *r3 = this->_safe_get (AtomType::aC4p);

	    Vector3D x = (*r2 - *r3).normalize ();
	    Vector3D y = (*r1 - *r2).normalize ();
	    Vector3D z = x.cross (y).cross (y).normalize ();

	    Vector3D v = *r1 + (y*TAN19+z).normalize () * O_H_DIST;
	    this->insert (atom.set (v, AtomType::aHO3p));
	  }
	catch (NoSuchAtomException& ex)
	  {
	    gOut (4) << "Failed to add hydrogen " << AtomType::aHO3p << " in "
		     << *this << ": " << ex << endl;
	  }
      }
  }


  void
  Residue::addLonePairs (bool overwrite)
  {
    Vector3D x, y, z, up, a, b, v;
    Atom atom;

    if (type->isPurine ())
      {
	if (type->isA () && (overwrite || 0 == _get (AtomType::aLP1)))
	  {
	    // LP1
	    putH (AtomType::aC2, AtomType::aN1, AtomType::aC6, AtomType::aLP1, N_LP_DIST);
	  }
	if (type->isG ()
	    && (overwrite
		|| 0 == _get (AtomType::a1LP6)
		|| 0 == _get (AtomType::a2LP6)))
	  try // 1LP6 and 2LP6
	    {
	      x = (*_safe_get (AtomType::aC6) - *_safe_get (AtomType::aN1)).normalize ();
	      y = (*_safe_get (AtomType::aC6) - *_safe_get (AtomType::aC5)).normalize ();
	      z = (*_safe_get (AtomType::aO6) - *_safe_get (AtomType::aC6)).normalize ();
	      up = x.cross (y).normalize ();

	      b = (z + z.cross (up).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aO6) + b * O_LP_DIST;
	      insert (atom.set (v, AtomType::a1LP6));

	      a = (z + up.cross (z).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aO6) + a * O_LP_DIST;
	      insert (atom.set (v, AtomType::a2LP6));
	    }
	  catch (NoSuchAtomException& ex)
	    {
	      gOut (4) << "Failed to add lone pairs " << AtomType::a1LP6 << " and "
		       << AtomType::a2LP6 << " in " << *this << ": " << ex << endl;
	    }
	if (overwrite || 0 == _get (AtomType::aLP3))
	  {
	    // LP3
	    putH (AtomType::aC2, AtomType::aN3, AtomType::aC4, AtomType::aLP3, N_LP_DIST);
	  }
	if (overwrite || 0 == _get (AtomType::aLP7))
	  {
	    // LP7
	    putH (AtomType::aC5, AtomType::aN7, AtomType::aC8, AtomType::aLP7, N_LP_DIST);
	  }
      }
    else if (type->isPyrimidine ())
      {
	if (overwrite || 0 == _get (AtomType::a1LP2) || 0 == _get (AtomType::a2LP2))
	  try // 1LP2 and 2LP2
	    {
	      x = (*_safe_get (AtomType::aC2) - *_safe_get (AtomType::aN1)).normalize ();
	      y = (*_safe_get (AtomType::aC2) - *_safe_get (AtomType::aN3)).normalize ();
	      z = (*_safe_get (AtomType::aO2) - *_safe_get (AtomType::aC2)).normalize ();
	      up = x.cross (y).normalize ();

	      a = (z + up.cross (z).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aO2) + a * O_LP_DIST;
	      insert (atom.set (v, AtomType::a1LP2));

	      b = (z + z.cross (up).normalize () * TAN60).normalize ();
	      v = *_safe_get (AtomType::aO2) + b * O_LP_DIST;
	      insert (atom.set (v, AtomType::a2LP2));
	    }
	  catch (NoSuchAtomException& ex)
	    {
	      gOut (4) << "Failed to add lone pairs " << AtomType::a1LP2 << " and "
		       << AtomType::a2LP2 << " in " << *this << ": " << ex << endl;
	    }
	if (type->isC ())
	  {
	    if (overwrite || 0 == _get (AtomType::aLP3))
	      try // LP3
		{
		  x = (*_safe_get (AtomType::aN3) - *_safe_get (AtomType::aC2)).normalize ();
		  y = (*_safe_get (AtomType::aN3) - *_safe_get (AtomType::aC4)).normalize ();
		  z = (x + y).normalize ();
		  v = *_safe_get (AtomType::aN3) + z * N_LP_DIST;
		  insert (atom.set (v, AtomType::aLP3));
		}
	      catch (NoSuchAtomException& ex)
		{
		  gOut (4) << "Failed to add lone pair " << AtomType::aLP3 << " in "
			   << *this << ": " << ex << endl;
		}
	  }
	else if (type->isU () || type->isT () || type->is (ResidueType::r5MU)
		 || type->is (ResidueType::rPSU))
	  {
	    if (overwrite || 0 == _get (AtomType::a1LP4) || 0 == _get (AtomType::a2LP4))
	      try // 1LP4 and 2LP4
		{
		  x = (*_safe_get (AtomType::aC4) - *_safe_get (AtomType::aN3)).normalize ();
		  y = (*_safe_get (AtomType::aC4) - *_safe_get (AtomType::aC5)).normalize ();
		  z = (*_safe_get (AtomType::aO4) - *_safe_get (AtomType::aC4)).normalize ();
		  up = x.cross (y).normalize ();

		  b = (z + z.cross (up).normalize () * TAN60).normalize ();
		  v = *_safe_get (AtomType::aO4) + b * O_LP_DIST;
		  insert (atom.set (v, AtomType::a1LP4));

		  a = (z + up.cross (z).normalize () * TAN60).normalize ();
		  v = *_safe_get (AtomType::aO4) + a * O_LP_DIST;
		  insert (atom.set (v, AtomType::a2LP4));
		}
	      catch (NoSuchAtomException& ex)
		{
		  gOut (4) << "Failed to add lone pairs " << AtomType::a1LP4 << " and "
			   << AtomType::a2LP4 << " in " << *this << ": " << ex << endl;
		}
	  }
      }
  }


  float
  Residue::getRho () const
  {
    Atom *c1p, *c2p, *c3p, *c4p, *o4p;

    try
      {
	c1p = this->_safe_get (AtomType::aC1p);
	c2p = this->_safe_get (AtomType::aC2p);
	c3p = this->_safe_get (AtomType::aC3p);
	c4p = this->_safe_get (AtomType::aC4p);
	o4p = this->_safe_get (AtomType::aO4p);
      }
    catch (Exception& iex)
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "cannot evaluate pseudorotation for " << *this <<  "\n\t"
	   << iex.what ();
	throw ex;
      }

    double theta3 = o4p->torsionAngle (*c4p, *c1p, *c2p); // nu0
    double theta4 = c1p->torsionAngle (*o4p, *c2p, *c3p); // nu1
    double theta0 = c2p->torsionAngle (*c1p, *c3p, *c4p); // nu2
    double theta1 = c3p->torsionAngle (*c2p, *c4p, *o4p); // nu3
    double theta2 = c4p->torsionAngle (*c3p, *o4p, *c1p); // nu4
    double rho = atan2 (theta2 + theta4 - theta1 - theta3, theta0 * 3.077684f);

    return rho > 0 ? rho : gc_2xpi + rho;
  }


  float
  Residue::getRho (float& theta0, float& theta1, float& theta2, float& theta3, float& theta4) const
  {
    Atom *c1p, *c2p, *c3p, *c4p, *o4p;

    try
      {
	c1p = this->_safe_get (AtomType::aC1p);
	c2p = this->_safe_get (AtomType::aC2p);
	c3p = this->_safe_get (AtomType::aC3p);
	c4p = this->_safe_get (AtomType::aC4p);
	o4p = this->_safe_get (AtomType::aO4p);
      }
    catch (Exception& iex)
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "cannot evaluate pseudorotation for " << *this <<  "\n\t"
	   << iex.what ();
	throw ex;
      }

    theta3 = o4p->torsionAngle (*c4p, *c1p, *c2p); // nu0
    theta4 = c1p->torsionAngle (*o4p, *c2p, *c3p); // nu1
    theta0 = c2p->torsionAngle (*c1p, *c3p, *c4p); // nu2
    theta1 = c3p->torsionAngle (*c2p, *c4p, *o4p); // nu3
    theta2 = c4p->torsionAngle (*c3p, *o4p, *c1p); // nu4
    float rho = atan2 (theta2 + theta4 - theta1 - theta3, theta0 * 3.077684f);

    return rho > 0 ? rho : gc_2xpi + rho;
  }


  const PropertyType*
  Residue::getPucker () const
  {
    float rho;
    try
      {
	rho = this->getRho ();
      }
    catch (IntLibException& ex)
      {
	gOut (3) << "Failed to compute pseudorotation: " << ex << endl;
	return PropertyType::pUnknown;
      }
    return Residue::getPuckerType (rho);
  }


  float
  Residue::getChi () const
  {
    Atom *c24, *n19, *c1p, *o4p;

    try
      {
	c24 = this->_safe_get (Residue::carbonType24 (this->type));
	n19 = this->_safe_get (Residue::nitrogenType19 (this->type));
	c1p = this->_safe_get (AtomType::aC1p);
	o4p = this->_safe_get (AtomType::aO4p);
      }
    catch (IntLibException& iex)
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "cannot evaluate glycosyl torsion for " << *this <<  "\n\t"
	   << iex.what ();
	throw ex;
      }

    return c1p->torsionAngle (*o4p, *n19, *c24);
  }


  const PropertyType*
  Residue::getGlycosyl () const
  {
    float chi;
    try
      {
	chi = this->getChi ();
      }
    catch (IntLibException& ex)
      {
	gOut (3) << "Failed to compute glycosyl torsion: " << ex << endl;
	return PropertyType::pUnknown;
      }
    return Residue::getGlycosylType (chi);
  }


  float
  Residue::getFuranoseAmplitude () const throw (IntLibException)
  {
    try
      {
	return
	  this->_safe_get (AtomType::aC2p)->torsionAngle (*this->_safe_get (AtomType::aC1p),
							  *this->_safe_get (AtomType::aC3p),
							  *this->_safe_get (AtomType::aC4p))
	  /
	  cos (this->getRho ());
      }
    catch (Exception& iex)
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "cannot evaluate pucker amplitude for " << *this <<  "\n\t"
	   << iex.what ();
	throw ex;
      }
  }


  const PropertyType*
  Residue::getFuranoseType () const throw (IntLibException, FatalIntLibException)
  {
    /*
      4 bits unsigned value:
                             [1] C5'                   N1(N9)
         __ O4'__                |                     |
        /        \     --->      C4'---C3'-[O4']-C2'---C1'    == 0011 (5) == beta-D-ribofuranoside
      C4'-C3'-C2'-C1'                  |         |
      b1  b2  b3  b0         [0]       O3'       O2'
    */

    unsigned short ftype = 0, b3m = 8, b2m = 4, b1m = 2, b0m = 1;
    const PropertyType* fname = PropertyType::pNull;

    try
    {
      Atom* c1p = this->_safe_get (AtomType::aC1p);
      Atom* c2p = this->_safe_get (AtomType::aC2p);
      Atom* c3p = this->_safe_get (AtomType::aC3p);
      Atom* c4p = this->_safe_get (AtomType::aC4p);
      Atom* o4p = this->_safe_get (AtomType::aO4p);
      Vector3D ext;

      // b0: N1(N9)
      ext = *this->_safe_get (Residue::nitrogenType19 (this->type));
      if (ext.transform (HomogeneousTransfo::align (*c1p, *c2p, *o4p).invert ()).getX () < 0.0)
	ftype |= b0m;

      // b1: C5'
      ext = *this->_safe_get (AtomType::aC5p);
      if (ext.transform (HomogeneousTransfo::align (*c4p, *o4p, *c3p).invert ()).getX () < 0.0)
	ftype |= b1m;

      // b2: O3'
      ext = *this->_safe_get (AtomType::aO3p);
      if (ext.transform (HomogeneousTransfo::align (*c3p, *c4p, *c2p).invert ()).getX () < 0.0)
	ftype |= b2m;

      // b3: O2' => only if exists
      try
      {
	ext = *this->_safe_get (AtomType::aO2p);
	if (ext.transform (HomogeneousTransfo::align (*c2p, *c3p, *c1p).invert ()).getX () < 0.0)
	  ftype |= b3m;
      }
      catch (NoSuchAtomException& ex)
      {
      }
    }
    catch (Exception& iex)
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "cannot evaluate furanose type for " << *this <<  "\n\t"
	 << iex.what ();
      throw ex;
    }

    switch (ftype)
    {
    case  0: fname = PropertyType::pAlpha_L_Lyxofuranoside; break;
    case  1: fname = PropertyType::pBeta_L_Lyxofuranoside; break;
    case  2: fname = PropertyType::pAlpha_D_Ribofuranoside; break;
    case  3: fname = PropertyType::pBeta_D_Ribofuranoside; break;
    case  4: fname = PropertyType::pAlpha_L_Arabinofuranoside; break;
    case  5: fname = PropertyType::pBeta_L_Arabinofuranoside; break;
    case  6: fname = PropertyType::pAlpha_D_Xylofuranoside; break;
    case  7: fname = PropertyType::pBeta_D_Xylofuranoside; break;
    case  8: fname = PropertyType::pAlpha_L_Xylofuranoside; break;
    case  9: fname = PropertyType::pBeta_L_Xylofuranoside; break;
    case 10: fname = PropertyType::pAlpha_D_Arabinofuranoside; break;
    case 11: fname = PropertyType::pBeta_D_Arabinofuranoside; break;
    case 12: fname = PropertyType::pAlpha_L_Ribofuranoside; break;
    case 13: fname = PropertyType::pBeta_L_Ribofuranoside; break;
    case 14: fname = PropertyType::pAlpha_D_Lyxofuranoside; break;
    case 15: fname = PropertyType::pBeta_D_Lyxofuranoside; break;

    default:
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "invalid furanose type id #" << ftype;
      throw ex;
    }

    return fname;
  }


  void
  Residue::finalize ()
  {
    this->_set_pseudos ();
  }


  float
  Residue::distance (const Residue &r) const
  {
    if (this->getType ()->isAminoAcid ())
    {
      float deltaPseudoPhi =
	this->safeFind (AtomType::aN)->torsionAngle (*this->safeFind (AtomType::aH),
						     *this->safeFind (AtomType::aCA),
						     *this->safeFind (AtomType::aC))
	- r.safeFind (AtomType::aN)->torsionAngle (*r.safeFind (AtomType::aH),
						   *r.safeFind (AtomType::aCA),
						   *r.safeFind (AtomType::aC));

      float deltaPseudoPsi =
	this->safeFind (AtomType::aCA)->torsionAngle (*this->safeFind (AtomType::aN),
						      *this->safeFind (AtomType::aC),
						      *this->safeFind (AtomType::aO))
	- r.safeFind (AtomType::aCA)->torsionAngle (*r.safeFind (AtomType::aN),
						    *r.safeFind (AtomType::aC),
						    *r.safeFind (AtomType::aO));

      return (min ((float) abs (deltaPseudoPhi), (float)(2 * M_PI - abs (deltaPseudoPhi)))
	      + min ((float) abs (deltaPseudoPsi), (float)(2 * M_PI - abs (deltaPseudoPsi))));
    }
    else if (this->getType ()->isNucleicAcid ())
    {
      // nucleic acid
      Residue *tmpRef = this->clone ();
      Residue *tmpRes = r.clone ();
      float result;

      tmpRes->setReferential (tmpRef->getReferential ());

      // This supposes that the atoms are in the same order in the two
      // residues, which is the case since we iterate on sorted residues
      // by definition of a residue iterator
      AtomSetAnd as (new AtomSetBackbone (),
		     new AtomSetNot (new AtomSetOr (new AtomSetHydrogen (),
						    new AtomSetAtom (AtomType::aO2p))));

      result = Rmsd::rmsd (tmpRef->begin (as), tmpRef->end (),
			   tmpRes->begin (as), tmpRes->end ());
      delete tmpRef;
      delete tmpRes;
      return result;
    }

    TypeException ex ("", __FILE__, __LINE__);
    ex << "Distance metric is not defined for residues "
       << this->getType () << " and " << r.getType ();
    throw ex;
  }


  float
  Residue::buildRibose (const PropertyType* pucker, const PropertyType* glycosyl,
			bool build5p, bool build3p)
  {
    return this->buildRibose (pucker, glycosyl, build5p, build3p, this->getReferential ());
  }


  float
  Residue::buildRibose (const PropertyType* pucker, const PropertyType* glycosyl,
			bool build5p, bool build3p,
			const HomogeneousTransfo& ref_override)
  {
    float p0 = Residue::getMinRho (pucker), p1 = Residue::getMaxRho (pucker);
    float g0 = Residue::getMinChi (glycosyl), g1 = Residue::getMaxChi (glycosyl);
    return this->buildRibose (p0 + (p1 - p0) / 2.0, g0 + (g1 - g0) / 2.0,
			      M_PI, M_PI,
			      build5p, build3p,
			      ref_override);
  }


  float
  Residue::buildRibose (float rho, float chi, float gamma, float beta,
			bool build5p, bool build3p,
			const HomogeneousTransfo& ref_override)
  {
    Atom a1, a2;

    this->_build_ribose_preprocess (0, 0,
				    build5p, build3p,
				    a1, a2,
				    ref_override);
    this->_build_ribose (rho, chi, gamma, beta, build5p, build3p);
    this->_build_ribose_postprocess (ref_override, build5p, build3p);
    this->rib_built_valid = true;

    return 0.0;
  }


  float
  Residue::buildRiboseByEstimation (const Residue* po4_5p, const Residue* po4_3p)
  {
    return this->buildRiboseByEstimation (po4_5p, po4_3p, this->getReferential ());
  }


  float
  Residue::buildRiboseByEstimation (const Residue* po4_5p, const Residue* po4_3p,
				    const HomogeneousTransfo& ref_override)
  {
    Atom anchor_O5p, anchor_O3p;
    bool build5p = po4_5p == 0;

    float def_gamma = M_PI;
    float def_beta = M_PI;
    float erho1, erho2;
    float x, z, xz_len;
    float anchor_yrot, built_yrot;
    float value1 = 0, value2 = 0, final_value;

    if (po4_3p == 0)
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "3' phosphate is mandatory to estimate ribose for " << *this;
      throw ex;
    }

    /** preprocessing **/

    this->_build_ribose_preprocess (po4_5p, po4_3p,
				    build5p, false,
				    anchor_O5p, anchor_O3p,
				    ref_override);
    this->rib_built_valid = true;
    this->rib_built_count = 0;

    // dummy O3'
    // O3' must be built for estimation but 3' branch is always constrained
    Atom dummy_O3p;
    this->rib_O3p = &dummy_O3p;


    /** pseudorotation estimation  **/

    // O3' XZ plane projection vector length
    x = anchor_O3p.getX ();
    z = anchor_O3p.getZ ();
    xz_len = sqrt (x*x + z*z);

    // rho estimation with respect to O3'
    omega = erho1 = (xz_len - gc_cosf_vshift) / gc_cosf_amplitude;

    // +/- 0.25 tolerance on cos amplitude
    if (erho1 < -1.25)
    {
      this->rib_built_valid = false;
      return numeric_limits< float >::max ();
    }
    else if (erho1 < -1.0)   // -1.25 <= omega < -1.0
      erho1 = -1.0;
    else if (erho1 > 1.25)
    {
      this->rib_built_valid = false;
      return numeric_limits< float >::max ();
    }
    else if (erho1 > 1.0)    // 1.00 <= omega < 1.25
      erho1 = 1.0;

//     if (erho1 < -1)
//       erho1 = -1.0;
//     else if (erho1 > 1)
//       erho1 = 1.0;

    erho1 = acos (erho1) - gc_cosf_phase;
    erho2 = gc_2xpi - 2 * gc_cosf_phase - erho1;


    /** glycosyl torsion estimation **/

    // Y rotation from X axis to anchored O3'
    anchor_yrot = z < 0 ? acos (x / xz_len) : gc_2xpi - acos (x / xz_len);

    // build with first rho. Must build O3'!
    this->_build_ribose (erho1, 0, def_gamma, def_beta, build5p, true);

    // Y rotation from X axis to built O3'
    x = this->rib_O3p->getX ();
    z = this->rib_O3p->getZ ();
    xz_len = sqrt (x*x + z*z);
    built_yrot = z < 0 ? acos (x / xz_len) : gc_2xpi - acos (x / xz_len);

    // compute estimated chi and apply Y rotation
    this->_transform_ribose (HomogeneousTransfo::rotationY (anchor_yrot - built_yrot), build5p, false);
    value1 = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, false);

    // back up this ribose
    Atom sO2p, sO5p, sO1P, sO2P, sP;
    Atom sC1p = *this->rib_C1p;
    Atom sC2p = *this->rib_C2p;
    Atom sC3p = *this->rib_C3p;
    Atom sC4p = *this->rib_C4p;
    Atom sC5p = *this->rib_C5p;
    if (this->rib_O2p)
      sO2p = *this->rib_O2p;
    Atom sO4p = *this->rib_O4p;
    if (build5p)
    {
      sO5p = *this->rib_O5p;
      sO1P = *this->rib_O1P;
      sO2P = *this->rib_O2P;
      sP = *this->rib_P;
    }

    // build with second rho. Must build O3'!
    this->_build_ribose (erho2, 0, def_gamma, def_beta, build5p, true);

    // Y rotation from X axis to built O3'
    x = this->rib_O3p->getX ();
    z = this->rib_O3p->getZ ();
    xz_len = sqrt (x*x + z*z);
    built_yrot = z < 0 ? acos (x / xz_len) : gc_2xpi - acos (x / xz_len);

    // compute estimated chi and apply Y rotation
    this->_transform_ribose (HomogeneousTransfo::rotationY (anchor_yrot - built_yrot), build5p, false);
    value2 = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, false);

    if (value1 < value2)
    {
      // set as first estimation: retrieve backup ribose.
      *this->rib_C1p = sC1p;
      *this->rib_C2p = sC2p;
      *this->rib_C3p = sC3p;
      *this->rib_C4p = sC4p;
      *this->rib_C5p = sC5p;
      if (this->rib_O2p)
	*this->rib_O2p = sO2p;
      *this->rib_O4p = sO4p;
      if (build5p)
      {
	*this->rib_O5p = sO5p;
	*this->rib_O1P = sO1P;
	*this->rib_O2P = sO2P;
	*this->rib_P = sP;
      }
      final_value = value1;
      this->estrho = 1;
    }
    else
    {
      // set as second estimation: keep current ribose.
      final_value = value2;
      this->estrho = 2;
    }

    this->_build_ribose_postprocess (ref_override, build5p, false);
    this->rib_O3p = 0;

    return final_value;
  }


  float
  Residue::buildRiboseByCCM (const Residue* po4_5p, const Residue* po4_3p,
			     const PropertyType* pucker, const PropertyType* glycosyl)
  {
    return this->buildRiboseByCCM
      (po4_5p, po4_3p,
       this->getReferential (),
       Residue::s_rib_minshift, Residue::s_rib_mindrop, Residue::s_rib_shiftrate,
       pucker, glycosyl);
  }


  float
  Residue::buildRiboseByCCM (const Residue* po4_5p, const Residue* po4_3p,
			     const HomogeneousTransfo& ref_override,
			     const PropertyType* pucker, const PropertyType* glycosyl)
  {
    return this->buildRiboseByCCM
      (po4_5p, po4_3p,
       ref_override,
       Residue::s_rib_minshift, Residue::s_rib_mindrop, Residue::s_rib_shiftrate,
       pucker, glycosyl);
  }


  float
  Residue::buildRiboseByCCM (const Residue* po4_5p, const Residue* po4_3p,
			     const HomogeneousTransfo& ref_override,
			     float minshift, float mindrop, float shiftrate,
			     const PropertyType* pucker, const PropertyType* glycosyl)
  {
    Atom anchor_O5p, anchor_O3p;
    bool build5p = po4_5p == 0;
    bool build3p = po4_3p == 0;

    if (build5p && build3p)
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "needs at least one phosphate to build ribose for " << *this;
      throw ex;
    }

    this->_build_ribose_preprocess (po4_5p, po4_3p,
				    build5p, build3p,
				    anchor_O5p, anchor_O3p,
				    ref_override);

    // [0] -> rho
    // [1] -> chi

    int i;
    float x[2], new_x[2];
    float p_min[2], p_max[2], p_range[2], p_shift[2];
    float eval_x, eval_new_x;
    float def_gamma = M_PI;
    float def_beta = M_PI;
    bool not_shifted;

    if (PropertyType::pNull == pucker || 0 == pucker)
    {
      p_min[0] = 0.0;
      p_max[0] = gc_2xpi;
    }
    else
    {
      p_min[0] = Residue::getMinRho (pucker);
      p_max[0] = Residue::getMaxRho (pucker);
    }

    if (PropertyType::pNull == glycosyl || 0 == glycosyl)
    {
      p_min[1] = 0.0;
      p_max[1] = gc_2xpi;
    }
    else
    {
      p_min[1] = Residue::getMinChi (glycosyl);
      p_max[1] = Residue::getMaxChi (glycosyl);
    }

    for (i = 0; i < 2; ++i)
    {
      p_range[i] = p_max[i] - p_min[i];
      p_shift[i] = 0.25 * p_range[i];
      new_x[i] = x[i] = p_min[i] + 0.5 * p_range[i];
    }

    rib_built_count = 0;
    this->_build_ribose (x[0], x[1], def_gamma, def_beta, build5p, build3p);
    eval_x = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    while (p_shift[0] > minshift || p_shift[1] > minshift)
    {
      not_shifted = true;

      for (i = 0; i < 2; ++i)
      {
	new_x[i] = x[i] + p_shift[i];
	if (new_x[i] > p_max[i])
	  new_x[i] = p_max[i];

	this->_build_ribose (new_x[0], new_x[1], def_gamma, def_beta, build5p, build3p);
	eval_new_x = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

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

	  this->_build_ribose (new_x[0], new_x[1], def_gamma, def_beta, build5p, build3p);
	  eval_new_x = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

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

    this->_build_ribose (x[0], x[1], def_gamma, def_beta, build5p, build3p);
    eval_x = this->_evaluate_ribose (anchor_O5p, anchor_O3p, build5p, build3p);

    this->_build_ribose_postprocess (ref_override, build5p, build3p);
    this->rib_built_valid = true;

    //return sqrt (eval_x / 2.0);
    return eval_x;
  }


  const AtomType*
  Residue::nitrogenType19 (const ResidueType* rtype)
  {
    if (rtype)
    {
      if (rtype->isPurine ())     return AtomType::aN9;
      if (rtype->is (ResidueType::rPSU)) return AtomType::aC5;
      if (rtype->isPyrimidine ()) return AtomType::aN1;
    }
    TypeException ex ("", __FILE__, __LINE__);
    ex << "No terminus nitrogen known for residue type \"" << rtype << "\".";
    throw ex;
    return 0;
  }


  const AtomType*
  Residue::carbonType24 (const ResidueType* rtype)
  {
    if (rtype)
    {
      if (rtype->isPurine ())     return AtomType::aC4;
      if (rtype->is (ResidueType::rPSU)) return AtomType::aC4;
      if (rtype->isPyrimidine ()) return AtomType::aC2;
    }
    TypeException ex ("", __FILE__, __LINE__);
    ex << "No terminus carbon known for residue type \"" << rtype << "\".";
    throw ex;
    return 0;
  }


  const AtomType*
  Residue::carbonType68 (const ResidueType* rtype)
  {
    if (rtype)
    {
      if (rtype->isPurine ())     return AtomType::aC8;
      if (rtype->isPyrimidine ()) return AtomType::aC6;
    }
    TypeException ex ("", __FILE__, __LINE__);
    ex << "No terminus carbon known for residue type \"" << rtype << "\".";
    throw ex;
    return 0;
  }


  const PropertyType*
  Residue::getPuckerType (float rho)
  {
    // adjust value between [0,360]
    while (rho < 0.0)
      rho += gc_2xpi;
    while (rho > gc_2xpi)
      rho -= gc_2xpi;

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
      chi += gc_2xpi;
    while (chi > RAD_270)
      chi -= gc_2xpi;

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
    {
      TypeException ex ("", __FILE__, __LINE__);
      ex << "unknown pucker type " << pucker;
      throw ex;
    }
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
    {
      TypeException ex ("", __FILE__, __LINE__);
      ex << "unknown pucker type " << pucker;
      throw ex;
    }
  }


  float
  Residue::getMinChi (const PropertyType* glycosyl)
  {
    if (glycosyl == PropertyType::pSyn)
      return -RAD_90;
    else if (glycosyl == PropertyType::pAnti)
      return RAD_90;
    else
    {
      TypeException ex ("", __FILE__, __LINE__);
      ex << "unknown glycosyl torsion type " << glycosyl;
      throw ex;
    }
  }


  float
  Residue::getMaxChi (const PropertyType* glycosyl)
  {
    if (glycosyl == PropertyType::pSyn)
      return RAD_90;
    else if (glycosyl == PropertyType::pAnti)
      return RAD_270;
    else
    {
      TypeException ex ("", __FILE__, __LINE__);
      ex << "unknown glycosyl torsion type " << glycosyl;
      throw ex;
    }
  }

  // INTERNAL METHODS ------------------------------------------------------

  Atom&
  Residue::_get (size_type pos) const
  {
    return *atomGlobal[pos];
  }

  Atom*
  Residue::_get (const AtomType* aType) const
  {
    AtomMap::const_iterator it = atomIndex.find (aType);
    if (it == atomIndex.end ())
      return 0;
    else
      return &_get (it->second);
  }


  Atom*
  Residue::_safe_get (const AtomType* aType) const
  {
    AtomMap::const_iterator it = atomIndex.find (aType);
    if (it == atomIndex.end ())
    {
      NoSuchAtomException ex ("", __FILE__, __LINE__);
      ex << "residue " << *this << " is missing atom " << aType;
      throw ex;
    }
    return &_get (it->second);
  }


  Atom*
  Residue::_get_or_create (const AtomType *aType)
  {
    size_type pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
    {
      atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
      rib_dirty_ref = true;
      return atomGlobal[pos];
    }
    else
    {
      return atomGlobal[inserted.first->second];
    }
  }


  void
  Residue::_set_pseudos ()
  {
    Vector3D *p1, *p2, *p3;
    Vector3D a, b, i, j, k;
    Atom atom;

    try
    {
      if (this->type->isNucleicAcid ())
      {
	// fetch needed atoms
	p1 = this->_safe_get (Residue::nitrogenType19 (this->type));
	p2 = this->_safe_get (Residue::carbonType68 (this->type));
	p3 = this->_safe_get (Residue::carbonType24 (this->type));

	// compute and insert pseudo-atoms
	a = *p2 - *p1;
	b = *p3 - *p1;
	j = (a + b).normalize ();
	k = (b.cross (a)).normalize ();
	i = (j.cross (k)).normalize ();
	this->insert (atom.set (*p1 + i, AtomType::aPSX));
	this->insert (atom.set (*p1 + j, AtomType::aPSY));
	this->insert (atom.set (*p1 + k, AtomType::aPSZ));
	this->insert (atom.set (*p1, AtomType::aPSO));
      }
      else if (this->type->isPhosphate ())
      {
	// no pseudo-atoms needed
      }
      else if (this->type->isRibose ())
      {
	// no pseudo-atoms needed
      }
      else if (this->type->isAminoAcid ())
      {
	// fetch needed atoms
	p1 = this->_safe_get (AtomType::aCA);
	p2 = this->_safe_get (AtomType::aN);
	p3 = this->_safe_get (AtomType::aC);

	// compute and insert pseudo-atoms
	a = (*p2 - *p1).normalize ();
	b = (*p3 - *p1).normalize ();
	k = *p1 + (b.cross (a)).normalize ();
	this->insert (atom.set (k, AtomType::aPSAZ));
      }
      else
      {
	gOut (4) << "Unknown pseudo-atoms for residue type " << *this << endl;
      }
    }
    catch (IntLibException& ex)
    {
      gOut (4) << "Unknown pseudo-atoms for residue "<< *this << ": " << ex << endl;
    }
  }


  HomogeneousTransfo
  Residue::_compute_referential () const
  {
    Vector3D *pivot[3];
    Vector3D *origin;
    HomogeneousTransfo I;

    try
    {
      // first try to handle a nucleic acid which already has its pseudo atoms
      // to form an orthonormal base.
      if (this->type->isNucleicAcid ())
      {
	origin = this->_safe_get (AtomType::aPSO);
	return HomogeneousTransfo::frame (*this->_safe_get (AtomType::aPSX) - *origin,
					  *this->_safe_get (AtomType::aPSY) - *origin,
					  *this->_safe_get (AtomType::aPSZ) - *origin,
	 				  *origin);
      }

      // fetch pivot atoms for other types with no pseudo atoms
      if (this->type->isPhosphate ())
      {
	pivot[0] = this->_safe_get (AtomType::aP);
	pivot[1] = this->_safe_get (AtomType::aO3p);
	pivot[2] = this->_safe_get (AtomType::aO5p);
      }
      else if (this->type->isRibose ())
      {
	pivot[0] = this->_safe_get (AtomType::aC1p);
	pivot[1] = this->_safe_get (AtomType::aC2p);
	pivot[2] = this->_safe_get (AtomType::aO4p);
      }
      else if (this->type->isAminoAcid ())
      {
	pivot[0] = this->_safe_get (AtomType::aCA);
	pivot[1] = this->_safe_get (AtomType::aN);
	pivot[2] = this->_safe_get (AtomType::aPSAZ);
      }
      else if (this->size () >= 3)
      {
	pivot[0] = (Atom*)this->atomGlobal[0];
	pivot[1] = (Atom*)this->atomGlobal[1];
	pivot[2] = (Atom*)this->atomGlobal[2];
	gOut (4) << "default referential with first three atoms for residue type " << *this << endl;
      }
      else
      {
	gOut (4) << "no referential for residue type " << *this << endl;
	return I;
      }
    }
    catch (NoSuchAtomException& ex)
    {
      gOut (4) << "no referential for residue " << *this << ": " << ex << endl;
      return I;
    }

    return HomogeneousTransfo::align (*pivot[0], *pivot[1], *pivot[2]);
  }


  void
  Residue::_build_ribose_preprocess (const Residue* po4_5p,
				     const Residue* po4_3p,
				     bool build5p,
				     bool build3p,
				     Atom& o5p,
				     Atom& o3p,
				     const HomogeneousTransfo& referential)
  {
    // set reference to ribose's atoms

    if (this->rib_dirty_ref ||
	(build5p && 0 == this->rib_O5p) ||
	(build3p && 0 == this->rib_O3p))
    {
      // check residue type (DNA doesn't have a O2')
      if (this->type->isRNA ())
	this->rib_O2p = _get_or_create (AtomType::aO2p);
      else if (this->type->isDNA ())
	this->rib_O2p = 0;
      else
      {
	TypeException ex ("", __FILE__, __LINE__);
	ex << "cannot build ribose on residue " << *this;
	throw ex;
      }

      this->rib_C1p = _get_or_create (AtomType::aC1p);
      this->rib_C2p = _get_or_create (AtomType::aC2p);
      this->rib_C3p = _get_or_create (AtomType::aC3p);
      this->rib_C4p = _get_or_create (AtomType::aC4p);
      this->rib_C5p = _get_or_create (AtomType::aC5p);
      this->rib_O4p = _get_or_create (AtomType::aO4p);

      if (build5p)
      {
	this->rib_O5p = _get_or_create (AtomType::aO5p);
	this->rib_P   = _get_or_create (AtomType::aP);
	this->rib_O1P   = _get_or_create (AtomType::aO1P);
	this->rib_O2P   = _get_or_create (AtomType::aO2P);
      }

      if (build3p)
	this->rib_O3p = _get_or_create (AtomType::aO3p);

      this->rib_dirty_ref = false;
    }

    // align anchor atoms

    HomogeneousTransfo inv = referential.invert ();

    if (po4_5p)
    {
      o5p = *po4_5p->_safe_get (AtomType::aO5p);
      o5p.transform (inv);
    }

    if (po4_3p)
    {
      o3p = *po4_3p->_safe_get (AtomType::aO3p);
      o3p.transform (inv);
    }

  }


  void
  Residue::_transform_ribose (const HomogeneousTransfo& tfo,
			      bool build5p, bool build3p)
  {
    this->rib_C1p->transform (tfo);
    this->rib_C2p->transform (tfo);
    this->rib_C3p->transform (tfo);
    this->rib_C4p->transform (tfo);
    this->rib_C5p->transform (tfo);
    if (this->rib_O2p)
      this->rib_O2p->transform (tfo);
    this->rib_O4p->transform (tfo);

    if (build5p)
    {
      this->rib_O5p->transform (tfo);
      this->rib_O1P->transform (tfo);
      this->rib_O2P->transform (tfo);
      this->rib_P->transform (tfo);
    }

    if (build3p)
      this->rib_O3p->transform (tfo);
  }


  void
  Residue::_build_ribose (float rho, float chi, float gamma, float beta,
			  bool build5p, bool build3p)
  {
    Vector3D zero (0.0, 0.0, 0.0);

    ++this->rib_built_count;

    // nu0 = 37.68 * cos (rho + 3 * 144)
    // nu0 = 37.68 * cos (rho + 4 * 144)
    float nu0 = 0.6576400621514634 * cos (rho + 7.5398223686155035);
    float nu1 = 0.6576400621514634 * cos (rho + 10.053096491487338);

    float cos_chi_0 = cos (chi);
    float cos_chi_1 = cos (2.067167966062084 - chi);  // 118.440 - chi
    float cos_nu0_1 = cos (2.1176952479073194 - nu0); // 121.335 - nu0
    float cos_nu1_1 = cos (2.1146409217163296 - nu1); // 121.160 - nu1
    float cos_nu1_2 = cos (4.2034160639181035 - nu1); // 240.838 - nu1

    float sin_chi_0 = sin (chi);
    float sin_chi_1 = sin (2.067167966062084 - chi);  // 118.440 - chi
    float sin_nu0_1 = sin (2.1176952479073194 - nu0); // 121.335 - nu0
    float sin_nu1_1 = sin (2.1146409217163296 - nu1); // 121.160 - nu1
    float sin_nu1_2 = sin (4.2034160639181035 - nu1); // 240.838 - nu1


    // C1' (only a translation is needed)
    HomogeneousTransfo tfo
      (1.0, 0.0, 0.0, 0.0,
       0.0, 1.0, 0.0, -1.465,
       0.0, 0.0, 1.0, 0.0);
       //0.0, 0.0, 0.0, 1.0);

    this->rib_C1p->set (zero);
    this->rib_C1p->transform (tfo);


    // O4' with respect to chi (from C1')
    tfo.set
      (0.3178011539917053*cos_chi_0,
       -0.9481573848900511*cos_chi_0,
       -sin_chi_0,
       1.3435390143892023*cos_chi_0,

       0.9481573848900511,
       0.3178011539917053,
       0.0,
       -1.9153242352062465,

       0.3178011539917053*sin_chi_0,
       -0.9481573848900511*sin_chi_0,
       cos_chi_0,
       1.3435390143892023*sin_chi_0);

       //0.0, 0.0 ,0.0 ,1.0);

    this->rib_O4p->set (zero);
    this->rib_O4p->transform (tfo);


    // C2' with respect to chi (from C1')
    tfo.set
      (0.37505965617503256*cos_chi_1,
       -0.9270006765422916*cos_chi_1,
       sin_chi_1,
       1.4173840344331636*cos_chi_1,

       0.9270006765422916,
       0.37505965617503256,
       0.0,
       -2.038466214291625,

       -0.37505965617503256*sin_chi_1,
       0.9270006765422916*sin_chi_1,
       cos_chi_1,
       -1.4173840344331636*sin_chi_1);

    //0.0, 0.0 ,0.0 ,1.0);

    this->rib_C2p->set (zero);
    this->rib_C2p->transform (tfo);


    // C3' with respect to nu1 (from C2')
    tfo.set
      (cos_chi_1*(-0.9085646439620313 + 0.07442844670182767*cos_nu1_2) - 0.1984442887322796*sin_chi_1*sin_nu1_2,
       cos_chi_1*(-0.18395798991077703 - 0.3676005332037575*cos_nu1_2) + 0.9801121692283693*sin_chi_1*sin_nu1_2,
       cos_nu1_2*sin_chi_1 + 0.37505965617503256*cos_chi_1*sin_nu1_2,
       cos_chi_1*(1.697552053067277 + 0.5598556120693227*cos_nu1_2) - 1.4927108337348063*sin_chi_1*sin_nu1_2,

       0.3676005332037575 + 0.18395798991077703*cos_nu1_2,
       0.07442844670182767 - 0.9085646439620313*cos_nu1_2,
       0.9270006765422916*sin_nu1_2,
       -2.1518207386185084 + 1.3837439527541735*cos_nu1_2,

       (0.9085646439620313 - 0.07442844670182767*cos_nu1_2)*sin_chi_1 - 0.1984442887322796*cos_chi_1*sin_nu1_2,
       (0.18395798991077703 + 0.3676005332037575*cos_nu1_2)*sin_chi_1 + 0.9801121692283693*cos_chi_1*sin_nu1_2,
       cos_chi_1*cos_nu1_2 - 0.37505965617503256*sin_chi_1*sin_nu1_2,
       (-1.697552053067277 - 0.5598556120693227*cos_nu1_2)*sin_chi_1 - 1.4927108337348063*cos_chi_1*sin_nu1_2);

    //       0.0, 0.0, 0.0, 1.0);

    this->rib_C3p->set (zero);
    this->rib_C3p->transform (tfo);

    if (this->rib_O2p)
    {
      // O2' with respect to nu1 (from C2')
      tfo.set
	(cos_chi_1*(-0.8723723497509978 + 0.12684981914014418*cos_nu1_1) - 0.3382123804884682*sin_chi_1*sin_nu1_1,
	 cos_chi_1*(-0.31352310552778895 - 0.3529573190546505*cos_nu1_1) + 0.9410698091450621*sin_chi_1*sin_nu1_1,
	 cos_nu1_1*sin_chi_1 + 0.37505965617503256*cos_chi_1*sin_nu1_1,
	 cos_chi_1*(1.8607057056494571 + 0.4990816491432758*cos_nu1_1) - 1.3306727101311178*sin_chi_1*sin_nu1_1,

	 0.3529573190546505 + 0.31352310552778895*cos_nu1_1,
	 0.12684981914014418 - 0.8723723497509978*cos_nu1_1,
	 0.9270006765422916*sin_nu1_1,
	 -2.217831858555789 + 1.2335345025479107*cos_nu1_1,

	 (0.8723723497509978 - 0.12684981914014418*cos_nu1_1)*sin_chi_1 - 0.3382123804884682*cos_chi_1*sin_nu1_1,
	 (0.31352310552778895 + 0.3529573190546505*cos_nu1_1)*sin_chi_1 + 0.9410698091450621*cos_chi_1*sin_nu1_1,
	 cos_chi_1*cos_nu1_1 - 0.37505965617503256*sin_chi_1*sin_nu1_1,
	 (-1.8607057056494571 - 0.4990816491432758*cos_nu1_1)*sin_chi_1 - 1.3306727101311178*cos_chi_1*sin_nu1_1);

      //	 0.0, 0.0, 0.0, 1.0);

      this->rib_O2p->set (zero);
      this->rib_O2p->transform (tfo);
    }


    // C4' with respect to nu0 (from O4')
    tfo.set
      (cos_chi_0*(-0.8926622497199935 + 0.10712926213198759*cos_nu0_1) + 0.3370952584230821*sin_chi_0*sin_nu0_1,
       cos_chi_0*(-0.3196193586852655 - 0.2992004255904651*cos_nu0_1) - 0.941470544812038*sin_chi_0*sin_nu0_1,
       -(cos_nu0_1*sin_chi_0) + 0.3178011539917053*cos_chi_0*sin_nu0_1,
       cos_chi_0*(1.8076263232002079 + 0.43443901795735534*cos_nu0_1) + 1.3670152310670791*sin_chi_0*sin_nu0_1,

       0.2992004255904651 + 0.3196193586852655*cos_nu0_1,
       0.10712926213198759 - 0.8926622497199935*cos_nu0_1,
       0.9481573848900511*sin_nu0_1,
       -2.0708759238218923 + 1.2961455865934306*cos_nu0_1,

       (-0.8926622497199935 + 0.10712926213198759*cos_nu0_1)*sin_chi_0 - 0.3370952584230821*cos_chi_0*sin_nu0_1,
       (-0.3196193586852655 - 0.2992004255904651*cos_nu0_1)*sin_chi_0 + 0.941470544812038*cos_chi_0*sin_nu0_1,
       cos_chi_0*cos_nu0_1 + 0.3178011539917053*sin_chi_0*sin_nu0_1,
       (1.8076263232002079 + 0.43443901795735534*cos_nu0_1)*sin_chi_0 - 1.3670152310670791*cos_chi_0*sin_nu0_1);

    //       0.0, 0.0, 0.0, 1.0);

    this->rib_C4p->set (zero);
    this->rib_C4p->transform (tfo);

    // C5' => align first for 5' branch
    HomogeneousTransfo branch5p =
      HomogeneousTransfo::align (*rib_C4p, *rib_C3p, *rib_O4p);

    tfo.set
      (0.3716846792351733,
       -0.7832599952069786,
       0.4983515617816504,
       1.1827225927625378,

       0.9034400745204099,
       0.4287143941490142,
       0.0,
       -0.6473587351650114,

       -0.21365048788243526,
       0.45023077211337686,
       0.8669750405114266,
       -0.6798484658911991);

    //       0.0, 0.0, 0.0, 1.0);

    this->rib_C5p->set (zero);
    this->rib_C5p->transform (branch5p * tfo);

    if (build5p)
    {
      // O5' from C5' according to gamma => align first for 5' branch
      float cos_gamma = cos (gamma);
      float sin_gamma = sin (gamma);

      tfo.set
	(-0.7387794924982604 + 0.12347144128320701*cos_gamma + 0.16554942680320905*sin_gamma,
	 -0.26019431499486884 - 0.35057710131382114*cos_gamma - 0.4700507062172538*sin_gamma,
	 0.4983515617816504*cos_gamma - 0.3716846792351733*sin_gamma,
	 1.5574024063551488 + 0.5048310258919024*cos_gamma + 0.6768730169528454*sin_gamma,

	 0.40436815932672815 + 0.3001174230360551*cos_gamma,
	 0.14241637361367576 - 0.8521346728303227*cos_gamma,
	 -0.9034400745204099*sin_gamma,
	 -0.8524383131687046 + 1.2270739288756647*cos_gamma,

	 0.42466264505328705 - 0.07097342221365434*cos_gamma + 0.28800395547318697*sin_gamma,
	 0.14956398648790234 + 0.2015175037352462*cos_gamma - 0.8177404493490513*sin_gamma,
	 0.8669750405114266*cos_gamma + 0.21365048788243526*sin_gamma,
	 -0.8952206064337784 - 0.29018520537875453*cos_gamma + 1.1775462470626339*sin_gamma);

      //	 0.0, 0.0, 0.0, 1.0);

      this->rib_O5p->set (zero);
      this->rib_O5p->transform (branch5p * tfo);

      // P5' from O5' according to beta => align first for 5' branch
      float cos_beta = cos (beta);
      float sin_beta = sin (beta);

      tfo.set
	(-0.22318427905141008 + cos_gamma*(-0.3007110190328383 + 0.25617779354834425*sin_beta) + cos_beta*(-0.379769854899928 + 0.06347053730720459*cos_gamma + 0.08510074038901261*sin_gamma) - 0.4031906999458186*sin_gamma - 0.1910646385491005*sin_beta*sin_gamma,
	 -0.13375297806012146 + cos_gamma*(-0.18021428078216548 - 0.427466042186876*sin_beta) + cos_beta*(0.6336955071998497 - 0.10590886509866484*cos_gamma - 0.14200167851160403*sin_gamma) - 0.24162972890879952*sin_gamma + 0.3188162553482103*sin_beta*sin_gamma,
	 cos_beta*(0.4983515617816504*cos_gamma - 0.3716846792351733*sin_gamma) + sin_beta*(0.7387794924982604 - 0.12347144128320701*cos_gamma - 0.16554942680320905*sin_gamma),
	 1.7704709004049224 + cos_gamma*(0.791912375177892 + 0.6809534052036935*sin_beta) + cos_beta*(-1.0094769429693606 + 0.1687128221021731*cos_gamma + 0.22620867386898522*sin_gamma) + 1.061789175104563*sin_gamma - 0.507874294769699*sin_beta*sin_gamma,

	 0.1221590705035631 - cos_gamma*0.7309270481720375 + cos_beta*(0.20786559285012113 + 0.15427546562496294*cos_gamma) - 0.4644136843202968*sin_beta*sin_gamma,
	 0.07320918635646471 - cos_gamma*0.4380401247490384 + cos_beta*(-0.3468508376613121 - 0.25742872472978484*cos_gamma) + 0.7749347702003643*sin_beta*sin_gamma,
	 -0.9034400745204099*cos_beta*sin_gamma + sin_beta*(-0.40436815932672815 - 0.3001174230360551*cos_gamma),
	 -0.9690605470345528 + cos_gamma*1.9248718476008828 + cos_beta*(0.5525333843944701 + 0.41008395849454726*cos_gamma) - 1.2344710889291803*sin_beta*sin_gamma,

	 0.12829000701654686 + cos_gamma*(0.17285365665378855 + 0.44566882091364896*sin_beta) + cos_beta*(0.21829798029171227 - 0.036483912357508086*cos_gamma + 0.14804853341393348*sin_gamma) - 0.7014250585864771*sin_gamma + 0.10982710755550963*sin_beta*sin_gamma,
	 0.07688341923879162 + cos_gamma*(0.10359014283752652 - 0.7436565221493238*sin_beta) + cos_beta*(-0.36425863600498654 + 0.06087816357124541*cos_gamma - 0.24703827663377365*sin_gamma) - 0.42035976221392257*sin_gamma - 0.18326084529542347*sin_beta*sin_gamma,
	 sin_beta*(-0.42466264505328705 + 0.07097342221365434*cos_gamma - 0.28800395547318697*sin_gamma) + cos_beta*(0.8669750405114266*cos_gamma + 0.21365048788243526*sin_gamma),
	 -1.0176958932811735 + cos_gamma*(-0.45520430291893427 + 1.1846448397838727*sin_beta) + cos_beta*(0.5802640071559435 - 0.09697891456899393*cos_gamma + 0.3935319746776014*sin_gamma) + 1.8471793482694125*sin_gamma + 0.2919345265556096*sin_beta*sin_gamma);

      //	 0.0, 0.0, 0.0, 1.0);

      this->rib_P->set (zero);
      this->rib_P->transform (branch5p * tfo);

      // O1P and O2P position from P (arbitrary rotation)
      rib_O1P->set (zero);
      rib_O1P->transform
	( branch5p *
	  tfo *
	  HomogeneousTransfo::rotationZ (RAD(72.1)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.486, 0.0)) );

      rib_O2P->set (zero);
      rib_O2P->transform
	( branch5p *
	  tfo *
	  HomogeneousTransfo::rotationY (RAD(-119.47)) *
	  HomogeneousTransfo::rotationZ (RAD(71.5)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.483, 0.0)) );
    }

    if (build3p)
    { // O3' => align first for 3' branch
      HomogeneousTransfo branch3p =
	HomogeneousTransfo::align (*rib_C3p, *rib_C4p, *rib_C2p);

      tfo.set
	(0.32094659913896034,
	 -0.8016121226249803,
	 0.5043919957352705,
	 1.147106947476347,

	 0.9283561384876282,
	 0.3716919156133742,
	 0.0,
	 -0.5318911312427386,

	 -0.18747842711489557,
	 0.46825540544486394,
	 0.8634747909685556,
	 -0.6700734851916004);

      //	 0.0, 0.0, 0.0, 1.0);

      this->rib_O3p->set (zero);
      this->rib_O3p->transform (branch3p * tfo);
    }
  }


  void
  Residue::_build_ribose_explicitly (float rho, float chi, float gamma, float beta,
				     bool build5p, bool build3p)
  {
    Vector3D zero (0.0, 0.0, 0.0);

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
    rib_C1p->set (zero);
    rib_C1p->transform (c1p);

    // O4' with respect to chi (from C1')
    o4p =
      c1p *
      HomogeneousTransfo::rotationY (-chi) *
      HomogeneousTransfo::rotationZ (RAD(71.47)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.417, 0.0));
    rib_O4p->set (zero);
    rib_O4p->transform (o4p);



    // C2' with respect to chi (from C1')
    c2p =
      c1p *
      HomogeneousTransfo::rotationY (RAD(118.44) - chi) *
      HomogeneousTransfo::rotationZ (RAD(67.972)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.529, 0.0));
    rib_C2p->set (zero);
    rib_C2p->transform (c2p);

    // C3' with respect to nu1 (from C2')
    rib_C3p->set (zero);
    rib_C3p->transform
      ( c2p *
        HomogeneousTransfo::rotationY (RAD(240.838) - nu1) *
        HomogeneousTransfo::rotationZ (RAD(78.554)) *
        HomogeneousTransfo::translation (Vector3D (0.0, -1.523, 0.0)) );

    if (rib_O2p)
    {
      // O2' with respect to nu1 (from C2')
      rib_O2p->set (zero);
      rib_O2p->transform
	( c2p *
	  HomogeneousTransfo::rotationY (RAD(121.160) - nu1) *
	  HomogeneousTransfo::rotationZ (RAD(70.232)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.414, 0.0)) );
    }

    // C4' with respect to nu0 (from O4')
    rib_C4p->set (zero);
    rib_C4p->transform
      ( o4p *
        HomogeneousTransfo::rotationY (RAD(121.335) - nu0) *
        HomogeneousTransfo::rotationZ (RAD(70.3)) *
        HomogeneousTransfo::translation (Vector3D (0.0, -1.452, 0.0)) );

    // C5' aligned on furanose for 5' branch
    branch5p =
      HomogeneousTransfo::align (*rib_C4p, *rib_C3p, *rib_O4p);
    c5p =
      HomogeneousTransfo::rotationY (RAD(29.891)) *
      HomogeneousTransfo::rotationZ (RAD(64.614)) *
      HomogeneousTransfo::translation (Vector3D (0.0, -1.510, 0.0));
    rib_C5p->set (zero);
    rib_C5p->transform (branch5p * c5p);

    if (build5p)
    {
      // O5' from C5' according to gamma (aligned on furanose for 5' branch)
      HomogeneousTransfo o5p =
	c5p *
	HomogeneousTransfo::rotationY (-gamma) *
	HomogeneousTransfo::rotationZ (RAD(70.598)) *
	HomogeneousTransfo::translation (Vector3D (0.0, -1.440, 0.0));
      rib_O5p->set (zero);
      rib_O5p->transform (branch5p * o5p);

      // P from O5' according to beta (aligned on furanose for 5' branch)
      HomogeneousTransfo p =
	o5p *
	HomogeneousTransfo::rotationY (-beta) *
	HomogeneousTransfo::rotationZ (RAD(59.066)) *
	HomogeneousTransfo::translation (Vector3D (0.0, -1.593, 0.0));
      rib_P->set (zero);
      rib_P->transform (branch5p * p);

      // O1P and O2P position from P (arbitrary rotation)
      rib_O1P->set (zero);
      rib_O1P->transform
	( branch5p *
	  p *
	  HomogeneousTransfo::rotationZ (RAD(72.1)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.486, 0.0)) );

      rib_O2P->set (zero);
      rib_O2P->transform
	( branch5p *
	  p *
	  HomogeneousTransfo::rotationY (RAD(-119.47)) *
	  HomogeneousTransfo::rotationZ (RAD(71.5)) *
	  HomogeneousTransfo::translation (Vector3D (0.0, -1.483, 0.0)) );

    }

    if (build3p)
    {
      // O3' aligned on furanose for 3' branch
      rib_O3p->set (zero);
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
    float e5p = build5p ? 0.0 : this->rib_C5p->distance (o5p) - 1.440;
    float e3p = build3p ? 0.0 : this->rib_C3p->distance (o3p) - 1.431;
    return sqrt ((e5p*e5p + e3p*e3p) / 2.0);
  }

  void
  Residue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
				      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential
    this->_transform_ribose (referential, build5p, build3p);
    this->_add_ribose_hydrogens (true);
  }

  // I/O  --------------------------------------------------------------------

  ostream&
  Residue::output (ostream &os) const
  {
    os << this->resId << this->type;
    //     AtomMap::const_iterator cit;
    //     for (cit=atomIndex.begin (); cit!=atomIndex.end (); ++cit) {
    //       os << endl << *(atomGlobal[cit->second]);
    //     }
    return os;
  }



  ostream&
  Residue::display (ostream& os) const
  {
    return this->_display (os << "### Residue status ###" << endl) << "### end ###" << endl;
  }


  ostream&
  Residue::_display (ostream& os) const
  {
    AtomMap::const_iterator mit;
    vector< Atom* >::const_iterator ait;

    os << "# ID:" << this->resId << endl
       << "# type: " << this->type << endl
       << "# dirty backbone?: " << this->rib_dirty_ref << endl
       << "# valid backbone?: " << this->rib_built_valid << endl
       << "# backbone count:  " << this->rib_built_count << endl
       << "# atoms mapping: " << this->atomIndex.size () << " entries" << endl;

    for (mit = this->atomIndex.begin (); mit != atomIndex.end (); ++mit)
      os << "\t[" << mit->first << "]\t" << mit->second << endl;

    os << "# global atoms: " << this->atomGlobal.size () << " entries" << endl;

    for (ait = this->atomGlobal.begin (); ait != atomGlobal.end (); ++ait)
    {
      os << "\t";
      os.width (3);
      os.setf (ios::right);
      os << (ait - this->atomGlobal.begin ()) << ": " << **ait << endl;
    }

    return os;
  }

  iBinstream&
  Residue::input (iBinstream &ibs)
  {
    mccore::bin_ui64 qty = 0;
    Atom a;

    clear ();
    ibs >> type >> resId >> qty;

    for (; qty > 0; --qty)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

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

    obs << type << resId << (mccore::bin_ui64)size ();

    for (cit = begin (); cit != end (); ++cit)
      {
	obs << *cit;
      }
    return obs;
  }


  Exception&
  operator<< (Exception& ex, const Residue &r)
  {
    ex << '<' << r.getResId () << ':' << r.getType () << '>';
    return ex;
  }


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


  Residue::ResidueIterator::ResidueIterator ()
    : res (0),
      filter (new AtomSetAll ())
  { }


  Residue::ResidueIterator::ResidueIterator (Residue *r, AtomMap::iterator p)
    : res (r),
      pos (p),
      filter (new AtomSetAll ())
  {
    AtomMap::iterator last = res->atomIndex.end ();
    while (pos != last && ! (*filter) (res->_get (pos->second)))
      ++pos;
  }


  Residue::ResidueIterator::ResidueIterator (Residue *r,
					     AtomMap::iterator p,
					     const AtomSet& f)
    : res (r),
      pos (p),
      filter (f.clone ())
  {
    AtomMap::iterator last = res->atomIndex.end ();
    while (pos != last && ! (*filter) (res->_get (pos->second)))
      ++pos;
  }


  Residue::ResidueIterator::ResidueIterator (const ResidueIterator &right)
    : res (right.res),
      pos (right.pos),
      filter (right.filter->clone ())
  { }


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
      if (++pos != last && (*filter) (res->_get (pos->second)))
	--k;
    return *this;
  }


  Residue::iterator&
  Residue::ResidueIterator::operator++ ()
  {
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->_get (pos->second)))
	break;
    return *this;
  }


  Residue::iterator
  Residue::ResidueIterator::operator++ (int ign)
  {
    ResidueIterator ret = *this;
    AtomMap::iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->_get (pos->second)))
	break;
    return ret;
  }


  Residue::ResidueConstIterator::ResidueConstIterator ()
    : res (0),
      filter (new AtomSetAll ())
  { }


  Residue::ResidueConstIterator::ResidueConstIterator (const Residue *r,
						       AtomMap::const_iterator p,
						       const AtomSet& f)
    : res (r),
      pos (p),
      filter (f.clone ())
  {
    AtomMap::const_iterator last = res->atomIndex.end ();
    while (!(pos == last || (*filter) (res->_get (pos->second))))
      ++pos;
  }


  Residue::ResidueConstIterator::ResidueConstIterator (const Residue *r,
						       AtomMap::const_iterator p)
    : res (r),
      pos (p),
      filter (new AtomSetAll ())
  {
    AtomMap::const_iterator last = res->atomIndex.end ();
    while (pos != last && ! (*filter) (res->_get (pos->second)))
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
      if (++pos != last && (*filter) (res->_get (pos->second)))
	--k;
    return *this;
  }


  Residue::const_iterator&
  Residue::ResidueConstIterator::operator++ ()
  {
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->_get (pos->second)))
	break;
    return *this;
  }


  Residue::const_iterator
  Residue::ResidueConstIterator::operator++ (int ign)
  {
    ResidueConstIterator ret = *this;
    AtomMap::const_iterator last = res->atomIndex.end ();

    while (pos != last)
      if (++pos == last || (*filter) (res->_get (pos->second)))
	break;
    return ret;
  }

}



namespace std
{

  ostream&
  operator<< (ostream &os, const mccore::Residue &r)
  {
    return r.output (os);
  }

}
