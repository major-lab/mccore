//                              -*- Mode: C++ -*- 
// RiboseEstimator.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Philippe Thibault <thibaup@iro.umontreal.ca> 
// Created On       : Mon Sep 29 14:59:19 2003
// $Revision: 1.3 $
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


#ifndef __RiboseEstimator_h_
#define __RiboseEstimator_h_


#include "RiboseBuilder.h"


namespace mccore
{
  
  /**
   * @short Builds a theoretical ribose between a RNA base and two phosphates.
   * 
   * Builds a theoretical ribose between a RNA base and two phosphates,
   * toward 5' and 3' branches. Uses a estimation of the pseudoration angle and
   * glycosyl torsion to minimize the distance between the reference based on
   * 3' phosphate position. Therefore O3' phosphate is mandatory.
   *
   * @author Philippe Thibault
   */
  class RiboseEstimator : public RiboseBuilder
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
     * Iterator to O3' anchor atoms.
     */
    Residue::const_iterator anc_O3p_it;

    /**
     * Placed O5' anchor atoms.
     */
    Vector3D anc_O5p;
  
    /**
     * Placed O5' anchor atoms.
     */
    Vector3D anc_O3p;

    /**
     * Flag acknowledging last built theoretical validity.
     * An invalid ribose should be discarded.
     */
    bool solved_ok;
  
    /**
     * Estimator's cosine function amplitude.
     */
    static float s_cosf_amplitude;

    /**
     * Estimator's cosine function vertical shift.
     */
    static float s_cosf_vshift;

    /**
     * Estimator's cosine function phase angle (rad).
     */
    static float s_cosf_phase;

    /**
     * Estimator's cosine function phase angle double value (rad).
     */
    static float s_cosf_2xphase;
  
    /**
     * Equivalent of 2 times the value of pi (rad).
     */
    static float two_pi;

    /**
     * Equivalent of 4 times the value of pi (rad).
     */
    static float four_pi;

    // LIFECYCLE ------------------------------------------------------------

  
    /**
     * Initializes the object. Should never be used.
     */
    RiboseEstimator () { }
  
  public:

    /**
     * Initializes object taking its reference atoms from the specifed residue
     * iterators. Ribose is fully constrained between 5' and 3'.
     * @param c24 residue iterator to pyrimidine's C2 or purine's C4 in achor base.
     * @param n19 residue iterator to pyrimidine's N1 or purine's N9 in achor base.
     * @param c1p residue iterator to C1' in achor base.
     * @param o5p Residue iterator to O5' atom in 5' anchor branch.
     * @param o3p Residue iterator to O3' atom in 3' anchor branch.
     * @param quality Id for quality function to be used. 
     */
    RiboseEstimator (Residue::const_iterator c24,
		     Residue::const_iterator n19,
		     Residue::const_iterator c1p,
		     Residue::const_iterator o5p,
		     Residue::const_iterator o3p,
		     char quality = QFCT_BOND);

    /**
     * Initializes object taking its reference atoms from the specifed residue
     * iterators. Ribose is half-constrained, the unspecfied branch is built
     * unconstrained. Here 03' is mandatory, so only the 5' branch can be built
     * unconstrained.
     * @param c24 residue iterator to pyrimidine's C2 or purine's C4 in achor base.
     * @param n19 residue iterator to pyrimidine's N1 or purine's N9 in achor base.
     * @param c1p residue iterator to C1' in achor base.
     * @param o3p Residue iterator to linked O3' atom in constrained anchor branch.
     * @param quality Id for quality function to be used.  
     */
    RiboseEstimator (Residue::const_iterator c24,
		     Residue::const_iterator n19,
		     Residue::const_iterator c1p,
		     Residue::const_iterator o3p,
		     char quality = QFCT_BOND);

    /**
     * Initializes object taking its reference atoms from the specifed residues.
     * Use only if base and phosphate are separate residues.
     * 5' phosphate residue must contain both P and O5' linked from C5' toward 5',
     * as 3' phosphate residue must contain both P and O3' linked from C3'
     * toward 3'.
     * @param base RNA base to which ribose should be build.
     * @param p5p phosphate residue toward 5', anchoring ribose. A null value
     *            indicates that 5' anchor branch should be built unconstrained.
     * @param p3p phosphate residue toward 3', anchoring ribose. A null value
     *            indicates that 3' anchor branch should be built unconstrained.
     * @param quality Id for quality function to be used.    
     */
    RiboseEstimator (Residue* base,
		     Residue* p5p,
		     Residue* p3p,
		     char quality = QFCT_BOND);

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    RiboseEstimator (const RiboseEstimator &right);

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual RiboseBuilder* clone () const { return new RiboseEstimator (*this); }

    /**
     * Destructs the object.
     */
    virtual ~RiboseEstimator () { }
  
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content and reinit.
     * @param right the object to copy.
     * @return itself.
     */
    RiboseEstimator& operator= (const RiboseEstimator &right);
  
    // ACCESS ---------------------------------------------------------------

    /**
     * Acknowledges last building theoretical validity.
     * @return true only if last building was theoreticaly valid.
     */
    bool solvedOk () const { return solved_ok; }
  
    // METHODS --------------------------------------------------------------

    /**
     * Estimation pre-processing : calculate building referential.
     */
    virtual void init ();

    /**
     * Build ribose's atoms according to current torsions value and
     * building referential.  
     @return Built ribose quality.
     */
    virtual float build ();
  
    /**
     * Find parameters for ribose best fit according to anchors, and build it;
     * @return Best fitted ribose quality.
     */
    virtual float solve ();

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

  protected:
  
    /**
     * Maintenance routine to verify anchor residues' iterator validity.
     */
    virtual void iterators_checkup () const;
  
  
  };

}

#endif
