//                              -*- Mode: C++ -*- 
// RiboseBuilder.h
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


#ifndef __RiboseBuilder_h_
#define __RiboseBuilder_h_


#include "Residue.h"
#include "ResidueFactoryMethod.h"


namespace mccore
{

  /**
   * @short Interface class. Builds a theoretical ribose between a RNA
   * base and its two adjacent phosphates.
   *
   * Interface class. Builds a theoretical ribose between a RNA base
   * and its two adjacent phosphates.  Building is addressed in
   * torsion space < rho, chi, gamma, beta, epsilon >
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class RiboseBuilder 
  {
  
  protected:

    /**
     * @short Simple container for ribose atoms.
     *
     * Simple container for ribose atoms.
     *
     * @author Philippe Thibault <thibaup@iro.umontreal.ca>
     */
    class _Ribose
    {
    public:

      /**
       * Ribose's atoms.
       */
      Atom C1p;
      Atom C2p;
      Atom C3p;
      Atom C4p;
      Atom C5p;
      Atom O2p;
      Atom O3p;
      Atom O4p;
      Atom O5p;
      Atom P5p;
      Atom P3p;

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object.
       */
      _Ribose ();

      /**
       * Initializes the object with the right's content.
       * @param right the object to copy.
       */
      _Ribose (const _Ribose& right);

      /**
       * Destructs the object.
       */
      ~_Ribose ();

      /**
       * Clones the object.
       * @return a copy of the object.
       */
      _Ribose* close () const { return new _Ribose (*this); }
    
      // OPERATORS ------------------------------------------------------------

      /**
       * Assigns the object with the right's content and reinit.
       * @param right the object to copy.
       * @return itself.
       */
      _Ribose& operator= (const _Ribose& right);
    
      // ACCESS ---------------------------------------------------------------
    
      // METHODS --------------------------------------------------------------

      /**
       * Resets ribose's atoms to origin.
       */
      void reset ();

      /**
       * Apply a transformation to each atoms.
       * @param tfo the tranasformation.
       */
      void transform (const HomogeneousTransfo& tfo);
    
      // I/O  -----------------------------------------------------------------
    };

    /**
     * @short Functor interface defining ribose quality function.
     *
     * Functor interface defining ribose quality function.
     *
     * @author Philippe Thibault <thibaup@iro.umontreal.ca>
     */  
    class _QualityFunctor
    {
    protected:

      /**
       * Builder object.
       */
      RiboseBuilder* builder;

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object. Should never be used.
       */
      _QualityFunctor () { }

    public:

      /**
       * Initializes the object.
       * @param b pointer to builder object.
       */
      _QualityFunctor (RiboseBuilder* b)
	: builder (b)
      { }

      /**
       * Initializes the object with the right's content.
       * @param right the object to copy.
       */
      _QualityFunctor (const _QualityFunctor& right) 
	: builder (right.builder)
      { }
    
      /**
       * Destructs the object.
       */
      virtual ~_QualityFunctor () { }

      /**
       * Clones the object.
       * @return a copy of the object.
       */
      virtual _QualityFunctor* clone () const = 0;
    
      // OPERATORS ------------------------------------------------------------

      /**
       * Assigns the object with the right's content and reinit.
       * @param right the object to copy.
       * @return itself.
       */
      virtual _QualityFunctor& operator= (const _QualityFunctor& right)
      { builder = right.builder; return *this; }

      /**
       * Calls builder's quality function.
       * @return the called quality function's return value.
       */
      virtual float operator() () const = 0;

      /**
       * Get builder's quality function name.
       * @return String representation for the builder's quality function.
       */
      virtual operator const char* () const = 0;
    
      // ACCESS ---------------------------------------------------------------
    
      // METHODS --------------------------------------------------------------
    
      // I/O  -----------------------------------------------------------------
    
    };

    /**
     * @short Functor implementation for point-to-point quality function.
     *
     * Functor implementation for point-to-point quality function. 
     *
     * @author Philippe Thibault <thibaup@iro.umontreal.ca>
     */  
    class _PointToPointQFct : public _QualityFunctor
    {
    protected:
    
      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object. Should never be used.
       */
      _PointToPointQFct () { }

    public:

      /**
       * Initializes the object.
       * @param b pointer to builder object.
       */
      _PointToPointQFct (RiboseBuilder* b)
	: _QualityFunctor (b)
      { }

      /**
       * Initializes the object with the right's content.
       * @param right the object to copy.
       */    
      _PointToPointQFct (const _PointToPointQFct& right) 
	: _QualityFunctor (right)
      { }

      /**
       * Destructs the object.
       */    
      virtual ~_PointToPointQFct () { }

      /**
       * Clones the object.
       * @return a copy of the object.
       */    
      virtual _QualityFunctor* clone () const { return new _PointToPointQFct (*this); }
    
      // OPERATORS ------------------------------------------------------------

      /**
       * Calls builder's point-to-point quality function.
       * @return the called quality function's return value.
       */
      virtual float operator() () const
      { return builder->evaluate_ptp (); }

      /**
       * Get builder's point-to-point quality function name.
       * @return String "point-to-point".
       */
      virtual operator const char* () const
      { return "point-to-point"; }
    
      // ACCESS ---------------------------------------------------------------
    
      // METHODS --------------------------------------------------------------
    
      // I/O  -----------------------------------------------------------------
    
    };

    /**
     * @short Functor implementation for bond length quality function.
     *
     * Functor implementation for bond length quality function. 
     *
     * @author Philippe Thibault <thibaup@iro.umontreal.ca>
     */  
    class _BondQFct : public _QualityFunctor
    {
    protected:
    
      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object. Should never be used.
       */    
      _BondQFct () { }

    public:

      /**
       * Initializes the object.
       * @param b pointer to builder object.
       */    
      _BondQFct (RiboseBuilder* b)
	: _QualityFunctor (b)
      { }

      /**
       * Initializes the object with the right's content.
       * @param right the object to copy.
       */        
      _BondQFct (const _BondQFct& right) 
	: _QualityFunctor (right)
      { }

      /**
       * Destructs the object.
       */  
      virtual ~_BondQFct () { }

      /**
       * Clones the object.
       * @return a copy of the object.
       */        
      virtual _QualityFunctor* clone () const { return new _BondQFct (*this); }
    
      // OPERATORS ------------------------------------------------------------

      /**
       * Calls builder's bond length quality function.
       * @return the called quality function's return value.
       */
      virtual float operator() () const
      { return builder->evaluate_bond (); }

      /**
       * Get builder's bond length quality function name.
       * @return String "bond".
       */
      virtual operator const char* () const
      { return "bond"; }
    
      // ACCESS --------------------------------------------------------------- 
    
      // METHODS --------------------------------------------------------------
    
      // I/O  -----------------------------------------------------------------

    };

    /**
     * Container for built atoms.
     */
    _Ribose ribose;

    /**
     * Defines quality function in use.
     */
    _QualityFunctor* qfct;

    /**
     * Flag acknowledging 5' branch constraint state.
     * 
     * true  : constrained
     *
     * false : free => built atoms P and O5p are inserted in resulting ribose.
     * 
     */
    bool check_O5p;
  
    /**
     * Flag acknowledging 3' branch constraint state.
     * 
     * true  : constrained
     *
     * false : free => built atom O3p is inserted in resulting ribose.
     * 
     */
    bool check_O3p;

    /**
     * Initial building referential.
     */
    HomogeneousTransfo alignment;

    /**
     * Pucker pseudorotation current value in radian.
     */
    float rho;

    /**
     * Glycosyl torsion current value in radian.
     */
    float chi;

    /**
     * Gamma torsion current value in radian.
     */
    float gamma;

    /**
     * Beta torsion current value in radian.
     */
    float beta;

    /**
     * Epsilon torsion current value in radian.
     */
    float epsilon;

    /**
     * Ribose built counter.
     */
    unsigned int built_count;

    /**
     * Homogeneous transformation matrix for z-axis 90 degree rotation.
     */
    static HomogeneousTransfo rz90;
    
  public:

    /**
     * Id for point-to-point quality function.
     */
    static const char QFCT_PTP;

    /**
     * Id for bond length quality function.
     */
    static const char QFCT_BOND;
  
    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     * @param quality quality function id.
     */
    RiboseBuilder (char quality = QFCT_BOND);
  
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    RiboseBuilder (const RiboseBuilder &right);
  
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual RiboseBuilder* clone () const = 0;

    /**
     * Destructs the object.
     */
    virtual ~RiboseBuilder ();
  
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content and reinit.
     * @param right the object to copy.
     * @return itself.
     */
    virtual RiboseBuilder& operator= (const RiboseBuilder &right);
  
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets current built count.
     * @return current built count.
     */
    virtual unsigned int get_count () const { return built_count; }

    /**
     * Gets current rho value in radian.
     * @return current rho value in radian
     */ 
    float get_rho () const { return rho; }

    /**
     * Sets current rho value in radian.
     * @param value new value for rho.
     */
    void set_rho (float value) { rho = value; }
  
    /**
     * Gets current chi value in radian.
     * @return current chi value in radian.
     */
    float get_chi () const { return chi; }

    /**
     * Sets current chi value in radian.
     * @param value new value for chi.
     */
    void set_chi (float value) { chi = value; }

    /**
     * Gets current gamma value in radian.
     * @return current gamma value in radian.
     */
    float get_gamma () const { return gamma; }

    /**
     * Sets current gamma value in radian.
     * @param value new value for gamma.
     */
    void set_gamma (float value) { gamma = value; }

    /**
     * Gets current beta value in radian.
     * @return current beta value in radian.
     */
    float get_beta () const { return beta; }

    /**
     * Sets current beta value in radian.
     * @param value new value for beta.
     */
    void set_beta (float value) { beta = value; }

    /**
     * Gets current epsilon value in radian.
     * @return current epsilon value in radian.
     */
    float get_epsilon () const { return epsilon; }

    /**
     * Sets current epsilon value in radian.
     * @param value new value for epsilon.
     */
    void set_epsilon (float value) { epsilon = value; }

    /**
     * Returns the branches constraint status
     *
     *  0: Fully constrained.
     *
     *  1: Constrained only toward 5'
     *
     * -1: Constrained only toward 3'
     *
     * @return branches constraint status.
     */
    virtual int status () const;

    /**
     * Acknowledges last building theoretical validity.
     * @return true only if last building was theoreticaly valid.
     */
    virtual bool solvedOk () const { return true; }
  
    // METHODS --------------------------------------------------------------

    /**
     * Building pre-processing : calculate initial building referential.
     */
    virtual void init () = 0;

    /**
     * Builds ribose's atoms according to current torsions value and building referential.
     * @return Built ribose quality.
     */
    virtual float build () = 0;

  protected:

    /**
     * Builds furanose cycle atoms according to current rho and chi.
     */
    virtual void buildFuranose ();

    /**
     * Builds C5', O5' and P5' atoms according to current gamma and beta.
     */
    virtual void build5p ();

    /**
     * Builds O3' and P3' atoms according to current epsilon.
     */
    virtual void build3p ();
  
  public:
  
    /**
     * Finds parameters for ribose best fit according to anchors, and builds it.
     * @return Best fitted ribose quality.
     */
    virtual float solve () = 0;

    /**
     * Evaluate currently built ribose according to the distance between built
     * and anchor atoms.
     * @return quality value (A^2)
     */
    virtual float evaluate_ptp () const = 0;

    /**
     * Evaluate currently built ribose according to its implicit bond length.
     * @return quality value (A^2)
     */
    virtual float evaluate_bond () const = 0;

    /**
     * Fill residue with currently built ribose atoms, overwritting any existing atom.
     * Ribose atoms are put into anchor referential, therefore residue must be the one
     * used in anchor specification (base and 5') to keep coherence.
     * Phosphate branch atoms are added only if that branch was unconstrained.
     * @param res Residue to be filled.
     */
    virtual void fillResidue (Residue& res) const;

    /**
     * Create a new phosphate-typed residue with its O5'-P bond aligned onto
     * 5' anchor phosphate O5'-P bond.
     * @return Newly created phosphate residue.
     */
    virtual Residue* createPhosphate5p (ResidueFactoryMethod* fm = 0) const;
  
    // I/O  -----------------------------------------------------------------
  };


}


#endif
