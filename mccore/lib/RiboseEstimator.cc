//                              -*- Mode: C++ -*- 
// RiboseEstimator.cc
// Author           : Philippe Thibault <thibaup@iro.umontreal.ca>
// Created On       : Mon Sep 29 14:58:39 2003
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

#include <values.h>

#include "Residue.h"
#include "CException.h"
#include "RiboseEstimator.h"


namespace mccore
{
  
  float RiboseEstimator::s_cosf_amplitude = 1.3305;
  float RiboseEstimator::s_cosf_vshift = 2.0778;
  float RiboseEstimator::s_cosf_phase = 0.3041;
  float RiboseEstimator::s_cosf_2xphase = 2.0 * RiboseEstimator::s_cosf_phase;

  float RiboseEstimator::two_pi = 2.0 * M_PI;
  float RiboseEstimator::four_pi = 4.0 * M_PI;


  RiboseEstimator::RiboseEstimator (Residue::const_iterator c24,
				    Residue::const_iterator n19,
				    Residue::const_iterator c1p,
				    Residue::const_iterator o5p,
				    Residue::const_iterator o3p,
				    char quality)
    : RiboseBuilder (quality),
      anc_C24_it (c24),
      anc_N19_it (n19),
      anc_C1p_it (c1p),
      anc_O5p_it (o5p),
      anc_O3p_it (o3p),
      solved_ok (true)
  {
    check_O5p = check_O3p = true;
    iterators_checkup ();
    init ();
  }


  RiboseEstimator::RiboseEstimator (Residue::const_iterator c24,
				    Residue::const_iterator n19,
				    Residue::const_iterator c1p,
				    Residue::const_iterator o3p,
				    char quality)
    : RiboseBuilder (quality),
      anc_C24_it (c24),
      anc_N19_it (n19),
      anc_C1p_it (c1p),
      anc_O3p_it (o3p),
      solved_ok (true)
  {
    check_O5p = false;
    check_O3p = true;
    iterators_checkup ();
    init ();
  }


  RiboseEstimator::RiboseEstimator (Residue* base,
				    Residue* p5p,
				    Residue* p3p,
				    char quality)
    : RiboseBuilder (quality),
      solved_ok (true)
  {
    if (!base)
      throw CIntLibException ("Need a base to create ribose estimator");
  
    if (!(p5p || p3p))
      throw CIntLibException ("Need at least one phosphate to create ribose estimator");
    else if (!p3p)
      throw CIntLibException ("phosphate 3' is mandatory to create ribose estimator");
  
    if (p5p)
      {
	if ((anc_O5p_it = p5p->find (AtomType::aO5p)) == p5p->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aO5p << " not found in linked 5' phosphate.";
	  }
	check_O5p = true;
      }
    else
      check_O5p = false;

    if ((anc_O3p_it = p3p->find (AtomType::aO3p)) == p3p->end ())
      {
	CIntLibException ex ("Cannot build ribose: ");
	throw ex << (const char*)*AtomType::aO3p << " not found in linked 3' phosphate.";
      }
    check_O3p = true;


    if (base->getType ()->isPurine ())
      {
	if ((anc_N19_it = base->find (AtomType::aN9)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aN9 << " not found in linked base.";
	  }
	if ((anc_C1p_it = base->find (AtomType::aC1p)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC1p << " not found in linked base.";
	  }
	if ((anc_C24_it = base->find (AtomType::aC4)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC4 << " not found in linked base.";
	  }
      }
    else if (base->getType ()->isPyrimidine ())
      {
	if ((anc_N19_it = base->find (AtomType::aN1)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aN1 << " not found in linked base.";
	  }
	if ((anc_C1p_it = base->find (AtomType::aC1p)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC1p << " not found in linked base.";
	  }
	if ((anc_C24_it = base->find (AtomType::aC2)) == base->end ())
	  {
	    CIntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC2 << " not found in linked base.";
	  }
      }
    else
      {
	CIntLibException ex ("Cannot build ribose linked to base type \"");
	throw ex << (const char*)*base->getType () << "\".";
      }

    iterators_checkup ();
    init ();
  }


  RiboseEstimator::RiboseEstimator (const RiboseEstimator &right)
    : RiboseBuilder (right),
      anc_C24_it (right.anc_C24_it),
      anc_N19_it (right.anc_N19_it),
      anc_C1p_it (right.anc_C1p_it),
      anc_O5p_it (right.anc_O5p_it),
      anc_O3p_it (right.anc_O3p_it),
      solved_ok (right.solved_ok)
  {
    iterators_checkup ();
    init ();
  }


  RiboseEstimator&
  RiboseEstimator::operator= (const RiboseEstimator &right)
  {
    if (this != &right)
      {
	RiboseBuilder::operator= (right);
	anc_C24_it = right.anc_C24_it;
	anc_N19_it = right.anc_N19_it;
	anc_C1p_it = right.anc_C1p_it;
	anc_O5p_it = right.anc_O5p_it;
	anc_O3p_it = right.anc_O3p_it;
	solved_ok = right.solved_ok;
	iterators_checkup ();
	init ();
      }
    return *this;
  }


  void
  RiboseEstimator::init ()
  {
    alignment =
      HomogeneousTransfo::align (*anc_N19_it, *anc_C1p_it, *anc_C24_it) * rz90;

    HomogeneousTransfo tmp (alignment.invert ());
    
    if (check_O5p)
      {
	anc_O5p = *anc_O5p_it;
	anc_O5p.transform (tmp);
      }
    if (check_O3p)
      {
	anc_O3p = *anc_O3p_it;
	anc_O3p.transform (tmp);
      }

  }
  

  float
  RiboseEstimator::build ()
  {
    ribose.reset ();
    ++built_count;
  
    buildFuranose ();
    build5p ();
    build3p ();
  
    return (*qfct) ();
  }


  float
  RiboseEstimator::solve ()
  {
    float erho1, erho2;
    float y, z, yz_len;
    float anchor_xrot, built_xrot, xrot1, xrot2;
    float value1 = 0, value2 = 0;

    HomogeneousTransfo rotation1, rotation2;
    _Ribose ribose1;

    solved_ok = true;
    built_count = 0;
  
    y = anc_O3p.getY ();
    z = anc_O3p.getZ ();
    yz_len = sqrt (y*y + z*z);

    // rho estimation

    erho1 = (yz_len - s_cosf_vshift) / s_cosf_amplitude;

    // +/- 0.2 tolerance on cos amplitude
    if (erho1 < -1.2 || erho1 > 1.2)
      {
	solved_ok = false;
	return MAXFLOAT;
      }
    if (erho1 < -1)
      erho1 = -1;
    else if (erho1 > 1)
      erho1 = 1;

    erho1 = acos (erho1) - s_cosf_phase;

    // get mirror rho
  
    if  (erho1 > 0)
      erho2 = two_pi - 2 * s_cosf_phase - erho1;
    else
      {
	erho1 = two_pi + erho1;
	erho2 = four_pi - s_cosf_phase - erho1;
      }
  
  
    // chi estimation 

    // X rotation to anchor O3'
  
    y = anc_O3p.getY ();
    z = anc_O3p.getZ ();
    yz_len = sqrt (y*y + z*z);

    anchor_xrot =
      y == 0 ?
      (z == 0 ? 0 : acos (z / yz_len)) :
      (y < 0 ? acos (z / yz_len) : two_pi - acos (z / yz_len));
  
    // build with first rho
  
    rho = erho1;
    chi = 0;
    build ();
  
    // X rotation to built O3' with first rho
  
    y = ribose.O3p.getY ();
    z = ribose.O3p.getZ ();
    yz_len = sqrt (y*y + z*z);

    built_xrot =
      y == 0 ?
      (z == 0 ? 0 : acos (z / yz_len)) :
      (y < 0 ? acos (z / yz_len) : two_pi - acos (z / yz_len));

    // compute estimated chi and apply X rotation

    xrot1 =
      built_xrot < anchor_xrot ?
      anchor_xrot - built_xrot :
      two_pi + anchor_xrot - built_xrot;
  
    ribose.transform (rotation1.rotate (xrot1, 0.0, 0.0));
    value1 = (*qfct) ();

    // save this ribose

    ribose1 = ribose;
  
    // build with second rho

    rho = erho2;
    chi = 0;
    build ();

    // X rotation to built O3' with first rho
  
    y = ribose.O3p.getY ();
    z = ribose.O3p.getZ ();
    yz_len = sqrt (y*y + z*z);

    built_xrot =
      y == 0 ?
      (z == 0 ? 0 : acos (z / yz_len)) :
      (y < 0 ? acos (z / yz_len) : two_pi - acos (z / yz_len));

    // compute estimated chi and apply X rotation

    xrot2 =
      built_xrot < anchor_xrot ?
      anchor_xrot - built_xrot :
      two_pi + anchor_xrot - built_xrot;
  
    ribose.transform (rotation2.rotate (xrot2, 0.0, 0.0));
    value2 = (*qfct) ();

    if (value1 < value2)
      {
	// set as first rho: retrieve old ribose.

	ribose = ribose1;
	rho = erho1;
	chi = xrot1;

	return value1;
      }

    // set as second rho: keep current ribose.

    chi = xrot2;

    return value2;
  }



  float
  RiboseEstimator::evaluate_ptp () const
  {
    float v = 0;
    if (check_O5p)
      v += ribose.O5p.squareDistance (anc_O5p);
    v += ribose.O3p.squareDistance (anc_O3p);
    return v;
  }


  float
  RiboseEstimator::evaluate_bond () const
  {
    float v = 0;
    if (check_O5p)
      v += fabs (ribose.C5p.squareDistance (anc_O5p) - 2.0736);
    v += fabs (ribose.C3p.squareDistance (anc_O3p) - 2.047761);
    return v;
  }


  void
  RiboseEstimator::iterators_checkup () const
  {
    if (!((anc_C24_it->getType () == AtomType::aC2 && anc_N19_it->getType () == AtomType::aN1) ||
	  (anc_C24_it->getType () == AtomType::aC4 && anc_N19_it->getType () == AtomType::aN9)))
      throw CIntLibException ("mismatched anchor atom iterator for base atoms (C2,N1) or (C4,N9)");  
    if (anc_C1p_it->getType () != AtomType::aC1p)
      throw CIntLibException ("mismatched anchor atom iterator for C1'");
    if (check_O5p && anc_O5p_it->getType () != AtomType::aO5p)
      throw CIntLibException ("mismatched anchor atom iterator for O5'");
    if (check_O3p && anc_O3p_it->getType () != AtomType::aO3p)
      throw CIntLibException ("mismatched anchor atom iterator for O3'");
  }

}
