//                              -*- Mode: C++ -*- 
// RiboseOptimizer5D.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Philippe Thibault <thibaup@iro.umontreal.ca> 
// Created On       : Mon Sep 29 14:59:19 2003
// $Revision: 1.2 $
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


#ifndef __RiboseOptimizer5D_h_
#define __RiboseOptimizer5D_h_


#include "RiboseBuilder.h"


namespace mccore
{

  /**
   * @short Builds a theoretical ribose between a RNA base and two phosphates.
   * 
   * Builds a theoretical ribose between a RNA base and two phosphates,
   * toward 5' and 3' branches. Uses a simplified cyclic coordinates method in
   * 5D torsion space < rho, chi, gamma, beta, epsilon >. Base must contains C1'.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class RiboseOptimizer5D : public RiboseBuilder
  {
  protected:
  
    /**
     * Iterator to pyrimidine's C2 or purine's C4 anchor atoms.
     */
    Residue::const_iterator anc_C24_it;

    /**
     * Iterator to pyrimidine's N1 or purine's N9 anchor atoms.
     */
    Residue::const_iterator anc_N19_it;

    /**
     * Iterator to C1' anchor atoms.
     */
    Residue::const_iterator anc_C1p_it;

    /**
     * Iterator to O5' anchor atoms.
     */
    Residue::const_iterator anc_O5p_it;

    /**
     * Iterator to 5' branch P anchor atoms.
     */
    Residue::const_iterator anc_P5p_it;

    /**
     * Iterator to O3' anchor atoms.
     */
    Residue::const_iterator anc_O3p_it;

    /**
     * Iterator to 3' branch P anchor atoms.
     */
    Residue::const_iterator anc_P3p_it;

    /**
     * Placed O5' anchor atoms.
     */
    Vector3D anc_O5p;
  
    /**
     * Placed 5' branch P anchor atoms.
     */
    Vector3D anc_P5p;
  
    /**
     * Placed O5' anchor atoms.
     */
    Vector3D anc_O3p;
  
    /**
     * Placed 3' branch P anchor atoms.
     */
    Vector3D anc_P3p;

    /**
     * Torsion shift threshold in optimization (rad). 
     */
    float min_shift;
  
    /**
     * Optimized function value threshold for a good shift.
     * 
     * IF  f(t') < f(t) - min_drop  THEN  t' is kept
     * 
     */
    float min_drop;

    /**
     * Torsion shift reduction rate in optimization (assumed < 1).
     */
    float shift_rate;

    /**
     * Initialization value for torsion shift threshold (rad).
     */
    static float s_min_shift;

    /**
     * Initialization value for function value threshold.
     */
    static float s_min_drop;

    /**
     * Initialization value for torsion shift reduction rate (assumed < 1).
     */
    static float s_shift_rate;

  
    // LIFECYCLE ------------------------------------------------------------

  
    /**
     * Initializes the object. Should never be used.
     */
    RiboseOptimizer5D () { }
  
  public:

    /**
     * Initializes object taking its reference atoms from the specifed residue
     * iterators. Ribose is fully constrained between 5' and 3'.
     * @param c24 residue iterator to pyrimidine's C2 or purine's C4 in achor base.
     * @param n19 residue iterator to pyrimidine's N1 or purine's N9 in achor base.
     * @param c1p residue iterator to C1' in achor base.
     * @param o5p residue iterator to O5' atom in 5' anchor branch.
     * @param p5p residue iterator to P atom in 5' anchor branch.
     * @param o3p residue iterator to O3' atom in 3' anchor branch.
     * @param p3p residue iterator to P atom in 3' anchor branch.
     * @param quality Id for quality function to be used.
     */
    RiboseOptimizer5D (Residue::const_iterator c24,
		       Residue::const_iterator n19,
		       Residue::const_iterator c1p,
		       Residue::const_iterator o5p,
		       Residue::const_iterator p5p,
		       Residue::const_iterator o3p,
		       Residue::const_iterator p3p,
		       char quality = QFCT_PTP);

    /**
     * Initializes object taking its reference atoms from the specifed residue
     * iterators. Ribose is half-constrained, the unspecfied branch is built
     * unconstrained.
     * @param c24 residue iterator to pyrimidine's C2 or purine's C4 in achor base.
     * @param n19 residue iterator to pyrimidine's N1 or purine's N9 in achor base.
     * @param c1p residue iterator to C1' in achor base.
     * @param p residue iterator to P atom in constrained anchor branch.
     * @param o residue iterator to linked O atom (O5' or O3') in constrained anchor branch.
     * @param cst_at_O5p flag attesting that the contrained branch is the 5' one (false for 3').
     * @param quality Id for quality function to be used.
     */
    RiboseOptimizer5D (Residue::const_iterator c24,
		       Residue::const_iterator n19,
		       Residue::const_iterator c1p,
		       Residue::const_iterator p,
		       Residue::const_iterator o,
		       bool cst_at_O5p,
		       char quality = QFCT_PTP);

    /**
     * Initializes object taking its reference atoms from the specifed residues.
     * Use only if base and phosphate are separate residues.
     * 5' phosphate residue must contains both P and O5' linked from C5' toward 5',
     * as 3' phosphate residue must contains both P and O3' linked from C3'
     * toward 3'.
     * @param base RNA base to which ribose should be build.
     * @param p5p phosphate residue toward 5', anchoring ribose. A null value
     *            indicates that 5' anchor branch should be built unconstrained.
     * @param p3p phosphate residue toward 3', anchoring ribose. A null value
     *            indicates that 3' anchor branch should be built unconstrained.
     * @param quality Id for quality function to be used.
     */
    RiboseOptimizer5D (Residue* base,
		       Residue* p5p,
		       Residue* p3p,
		       char quality = QFCT_PTP);

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    RiboseOptimizer5D (const RiboseOptimizer5D &right);

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual RiboseBuilder* clone () const { return new RiboseOptimizer5D (*this); }

    /**
     * Destructs the object.
     */
    virtual ~RiboseOptimizer5D () { }
  
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content and reinit.
     * @param right the object to copy.
     * @return itself.
     */
    RiboseOptimizer5D& operator= (const RiboseOptimizer5D &right);
  
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets torsion shift threshold (rad).
     * @return torsion shift threshold (rad).
     */
    float getMinimalShift () const { return min_shift; }

    /**
     * Gets function value threshold.
     * @return function value threshold.
     */
    float getMinimalDrop () const { return min_drop; }

    /**
     * Gets torsion shift reduction rate.
     * @return torsion shift reduction rate.
     */
    float getShiftRate () const { return shift_rate; }

    /**
     * Sets torsion shift threshold (rad).
     * @param ms new torsion shift threshold (rad).
     */
    void setMinimalShift (float ms) { min_shift = ms; }

    /**
     * Sets function value threshold.
     * @param md new function value threshold.
     */
    void setMinimalDrop (float md) { min_drop = md; }

    /**
     * Sets torsion shift reduction rate (assumed < 1).
     * @param sr new torsion shift reduction rate.
     */
    void setShiftRate (float sr) { shift_rate = sr; }

    /**
     * Modify torsion shift threshold initialization value.
     * @param ms new torsion shift threshold initialization value (rad).
     */
    static void defineMinimalShift (float ms) { s_min_shift = ms; }

    /**
     * Modify function value threshold initialization value.
     * @param md new function value threshold initialization value.
     */
    static void defineMinimalDrop (float md) { s_min_drop = md; }

    /**
     * Modify torsion shift reduction rate initialization value.
     * @param sr new torsion shift reduction rate initialization value.
     */
    static void defineShiftRate (float sr) { s_shift_rate = sr; }
  
  
    // METHODS --------------------------------------------------------------

    /**
     * Optimization pre-processing : calculate building referential.
     */
    virtual void init ();

    /**
     * Build ribose's atoms according to current torsions value and building referential.
     * @return Built ribose quality.
     */
    virtual float build ();
  
    /**
     * Finds parameters for ribose best fit according to anchors, and build it. Uses
     * a simplified cyclic coordinates method in 5D torsion space.
     * @return Best fitted ribose quality.
     */
    virtual float solve ();

  protected:

    /**
     * Builds ribose according to torsion value in p array in
     * < rho, chi, gamma, beta, epsilon > order, and returns quality.
     * @param p torsion value array < rho, chi, gamma, beta, epsilon >.
     * @return built ribose quality evaluation.
     */
    virtual float eval (float* p);

    /**
     * Maintenance routine to verify anchor residues' iterator validity.
     */
    virtual void iterators_checkup () const;
  
  public:

    /**
     * Evaluate currently built ribose according to the distance between built
     * and anchor atoms.
     * @return quality value (A^2)
     */
    virtual float evaluate_ptp () const;

    /**
     * Evaluate currently built ribose according to its implicit bond length.
     * @return quality value (A^2)
     */
    virtual float evaluate_bond () const;

  };

}

#endif
