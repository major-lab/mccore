//                              -*- Mode: C++ -*- 
// RiboseOptimizer5D.cc
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


#include "Exception.h"
#include "RiboseOptimizer5D.h"


namespace mccore
{
  
  float RiboseOptimizer5D::s_min_shift = 0.1;
  float RiboseOptimizer5D::s_min_drop = 0.00001;
  float RiboseOptimizer5D::s_shift_rate = 0.5;


  RiboseOptimizer5D::RiboseOptimizer5D (Residue::const_iterator c24,
					Residue::const_iterator n19,
					Residue::const_iterator c1p,
					Residue::const_iterator o5p,
					Residue::const_iterator p5p,
					Residue::const_iterator o3p,
					Residue::const_iterator p3p,
					char quality)
    : RiboseBuilder (quality),
      anc_C24_it (c24),
      anc_N19_it (n19),
      anc_C1p_it (c1p),
      anc_O5p_it (o5p),
      anc_P5p_it (p5p),
      anc_O3p_it (o3p),
      anc_P3p_it (p3p),
      min_shift (s_min_shift), 
      min_drop (s_min_drop),
      shift_rate (s_shift_rate)
  {
    check_O5p = check_O3p = true;
    iterators_checkup ();
    init ();
  }


  RiboseOptimizer5D::RiboseOptimizer5D (Residue::const_iterator c24,
					Residue::const_iterator n19,
					Residue::const_iterator c1p,
					Residue::const_iterator p,
					Residue::const_iterator o,
					bool cst_at_O5p,
					char quality)				
    : RiboseBuilder (quality),
      anc_C24_it (c24),
      anc_N19_it (n19),
      anc_C1p_it (c1p),
      min_shift (s_min_shift), // 0.005 deg
      min_drop (s_min_drop),
      shift_rate (s_shift_rate)
  {

    if (cst_at_O5p)
      {
	anc_P5p_it = p;
	anc_O5p_it = o;
	check_O5p = true;
	check_O3p = false;
      }
    else
      {
	anc_P3p_it = p;
	anc_O3p_it = o;
	check_O5p = false;
	check_O3p = true;
      }

    iterators_checkup ();
    init ();
  }


  RiboseOptimizer5D::RiboseOptimizer5D (Residue* base,
					Residue* p5p,
					Residue* p3p,
					char quality)
    : RiboseBuilder (quality),
      min_shift (s_min_shift), 
      min_drop (s_min_drop),
      shift_rate (s_shift_rate)
  {
    if (!base)
      throw IntLibException ("Need a base to create ribose optimizer");
  
    if (!(p5p || p3p))
      throw IntLibException ("Need at least one phosphate to create ribose optimizer");

    if (p5p)
      {
	if ((anc_P5p_it = p5p->find (AtomType::aP)) == p5p->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aP << " not found in linked 5' phosphate.";
	  }
	if ((anc_O5p_it = p5p->find (AtomType::aO5p)) == p5p->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aO5p << " not found in linked 5' phosphate.";
	  }
	check_O5p = true;
      }
    else
      check_O5p = false;
  
    if (p3p)
      {
	if ((anc_P3p_it = p3p->find (AtomType::aP)) == p3p->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aP << " not found in linked 3' phosphate.";
	  }
	if ((anc_O3p_it = p3p->find (AtomType::aO3p)) == p3p->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aO3p << " not found in linked 3' phosphate.";
	  }
	check_O3p = true;
      }
    else
      check_O3p = false;
  
    if (base->getType ()->isPurine ())
      {
	if ((anc_N19_it = base->find (AtomType::aN9)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aN9 << " not found in linked base.";
	  }
	if ((anc_C1p_it = base->find (AtomType::aC1p)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC1p << " not found in linked base.";
	  }
	if ((anc_C24_it = base->find (AtomType::aC4)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC4 << " not found in linked base.";
	  }
      }
    else if (base->getType ()->isPyrimidine ())
      {
	if ((anc_N19_it = base->find (AtomType::aN1)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aN1 << " not found in linked base.";
	  }
	if ((anc_C1p_it = base->find (AtomType::aC1p)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC1p << " not found in linked base.";
	  }
	if ((anc_C24_it = base->find (AtomType::aC2)) == base->end ())
	  {
	    IntLibException ex ("Cannot build ribose: ");
	    throw ex << (const char*)*AtomType::aC2 << " not found in linked base.";
	  }
      }
    else
      {
	IntLibException ex ("Cannot build ribose linked to base type \"");
	throw ex << (const char*)*base->getType () << "\".";
      }

    iterators_checkup ();
    init ();
  }


  RiboseOptimizer5D::RiboseOptimizer5D (const RiboseOptimizer5D &right)
    : RiboseBuilder (right),
      anc_C24_it (right.anc_C24_it),
      anc_N19_it (right.anc_N19_it),
      anc_C1p_it (right.anc_C1p_it),
      anc_O5p_it (right.anc_O5p_it),
      anc_P5p_it (right.anc_P5p_it),
      anc_O3p_it (right.anc_O3p_it),
      anc_P3p_it (right.anc_P3p_it),
      min_shift (right.min_shift),
      min_drop (right.min_drop),
      shift_rate (right.shift_rate)
  {
    iterators_checkup ();
    init ();
  }


  RiboseOptimizer5D&
  RiboseOptimizer5D::operator= (const RiboseOptimizer5D &right)
  {
    if (this != &right)
      {
	RiboseBuilder::operator= (right);
	anc_C24_it = right.anc_C24_it;
	anc_N19_it = right.anc_N19_it;
	anc_C1p_it = right.anc_C1p_it;
	anc_O5p_it = right.anc_O5p_it;
	anc_P5p_it = right.anc_P5p_it;
	anc_O3p_it = right.anc_O3p_it;
	anc_P3p_it = right.anc_P3p_it;
	min_shift = right.min_shift;
	min_drop = right.min_drop;
	shift_rate = right.shift_rate;
	iterators_checkup ();
	init ();
      }
    return *this;
  }


  void
  RiboseOptimizer5D::init ()
  {
    alignment =
      HomogeneousTransfo::align (*anc_N19_it, *anc_C1p_it, *anc_C24_it) * rz90;

    HomogeneousTransfo tmp (alignment.invert ());
    
    if (check_O5p)
      {
	anc_O5p = *anc_O5p_it;
	anc_P5p = *anc_P5p_it;
	anc_O5p.transform (tmp);
	anc_P5p.transform (tmp);
      }
    if (check_O3p)
      {
	anc_O3p = *anc_O3p_it;
	anc_P3p = *anc_P3p_it;
	anc_O3p.transform (tmp);
	anc_P3p.transform (tmp);
      }

  }
  

  float
  RiboseOptimizer5D::build ()
  {
    ribose.reset ();
    ++built_count;
  
    buildFuranose ();
    build5p ();
    build3p ();
  
    return (*qfct) ();
  }


  float
  RiboseOptimizer5D::solve ()
  {
    int i;
    float x[5], new_x[5];
    float eval_x, eval_new_x, shift = 3.14159;
    bool not_shifted;
  
    new_x[0] = x[0] = 0.523599;
    new_x[1] = x[1] = 1.0472;
    new_x[2] = x[2] = 3.14159;
    new_x[3] = x[3] = 3.14159;
    new_x[4] = x[4] = 3.14159;

    built_count = 0;
    eval_x = eval (x);

    while (shift > min_shift)
      {
	not_shifted = true;

	for (i = 0; i < 5; ++i)
	  {
	    new_x[i] = x[i] + shift;
	    eval_new_x = eval (new_x);
	    if (eval_new_x < eval_x - min_drop)
	      {
		x[i] = new_x[i];
		eval_x = eval_new_x;
		not_shifted = false;
	      }
	    else
	      {
		new_x[i] = x[i] - shift;
		eval_new_x = eval (new_x);
		if (eval_new_x < eval_x - min_drop)
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
	  shift *= shift_rate;
      }

    return eval (x);
  }


  float
  RiboseOptimizer5D::eval (float* p)
  {
    chi = p[0];
    rho = p[1];
    gamma = p[2];
    beta = p[3];
    epsilon = p[4];
    return build ();
  }


  float
  RiboseOptimizer5D::evaluate_ptp () const
  {
    float v = 0;
    if (check_O5p)
      v += ribose.P5p.squareDistance (anc_P5p) + ribose.O5p.squareDistance (anc_O5p);
    if (check_O3p)
      v += ribose.P3p.squareDistance (anc_P3p) + ribose.O3p.squareDistance (anc_O3p);
    return v;
  }


  float
  RiboseOptimizer5D::evaluate_bond () const
  {
    float v = 0;
    if (check_O5p)
      v += ribose.C5p.distance (anc_O5p);
    else
      v += 1.440;
    if (check_O3p)
      v += ribose.C3p.distance (anc_O3p);
    else
      v += 1.431;
    return v;
  }


  void
  RiboseOptimizer5D::iterators_checkup () const
  {
    if (!((anc_C24_it->getType () == AtomType::aC2 && anc_N19_it->getType () == AtomType::aN1) ||
	  (anc_C24_it->getType () == AtomType::aC4 && anc_N19_it->getType () == AtomType::aN9)))
      throw IntLibException ("mismatched anchor atom iterator for base atoms (C2,N1) or (C4,N9)");  
    if (anc_C1p_it->getType () != AtomType::aC1p)
      throw IntLibException ("mismatched anchor atom iterator for C1'");
    if (check_O5p && anc_O5p_it->getType () != AtomType::aO5p)
      throw IntLibException ("mismatched anchor atom iterator for O5'");
    if (check_O5p && anc_P5p_it->getType () != AtomType::aP)
      throw IntLibException ("mismatched anchor atom iterator for P(5')");
    if (check_O3p && anc_O3p_it->getType () != AtomType::aO3p)
      throw IntLibException ("mismatched anchor atom iterator for O3'");
    if (check_O3p && anc_P3p_it->getType () != AtomType::aP)
      throw IntLibException ("mismatched anchor atom iterator for P(3')");
  }


}
