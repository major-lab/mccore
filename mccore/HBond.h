//                              -*- Mode: C++ -*- 
// HBond.h
// Copyright © 2000-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.9 $
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


#ifndef _mccore_HBond_h
#define _mccore_HBond_h

#include <iostream>
#include <map>
#include <set>

#include "Algo.h"
#include "Exception.h"
#include "ResId.h"

using namespace std;



namespace mccore
{
  class Atom;
  class AtomType;
  class Residue;
  class iBinstream;
  class oBinstream;

  /**
   * @short Hydrogen bonds.
   *
   * A class to represent hydrogen bonds.  Hydrogen bonds are a
   * specialization of the more general concept of a chemical bond
   * between any two atoms.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: HBond.h,v 1.9 2006-08-28 17:50:31 thibaup Exp $
   */
  class HBond
  {
    friend class Relation;

    /**
     * The donor atom type implicated in the bond.
     */
    const AtomType *donor;

    /**
     * The hydrogen type implicated in the bond (connected to the donor atom).
     */
    const AtomType *hydrogen;
      
    /**
     * The acceptor type implicated in the bond.
     */
    const AtomType *acceptor;
      
    /**
     * The lone pair type implicated in the bond (connected to the acceptor).
     */
    const AtomType *lonepair;

    /**
     * The value of the last evaluation.
     */
    float value;
      
    /**
     * The residue location on which we find the donor group
     */
    const Residue *resD;
      
    /**
     * The residue location on which we find the acceptor group
     */
    const Residue *resA;
      
    /**
     * Gaussian parameters for Pairing pattern detection. (see
     * S. Lemieux and F. Major (2002) RNA canonical and non-canonical
     * base pairing types: a recognition method and complete
     * repertoire, NAR 30(19):4250-4263.
     */
    static const int sNbGauss;
    static const float sProbH[7];
    static const float sWeight[7];
    static const float sMean[7][3];
    static const float sCovarInv[7][3][3];
    static const float sCovarDet[7];

  public:
      
    // LIFECYCLE -------------------------------------------------------------
      
    /**
     * Initializes the object.  Every pointer is set to 0.
     * @param val the initial value.
     */
    HBond (float val = 0);
      
    /**
     * Initializes the object.
     * @param d the donor atom type.
     * @param h the hydrogen type.
     * @param a the acceptor atom type.
     * @param l the lonepair implicated.
     */
    HBond (const AtomType *d, const AtomType *h, 
	   const AtomType *a, const AtomType *l);

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    HBond (const HBond &other);

    /**
     * Clones the HBond.
     * @return a copy of this.
     */
    virtual HBond* clone () const { return new HBond (*this); }

    /**
     * Destroys the object.  Nothing to do.
     */
    virtual ~HBond () { }
      
    // OPERATORS -------------------------------------------------------------
      
    /**
     * Assigns the other's content to the object.
     * @param other the object to copy.
     * @return itself.
     */
    const HBond& operator= (const HBond &other);
      
    /**
     * Tests the equality between two HBond objects.
     * @param other the object to test.
     * @return the truth value.
     */
    virtual bool operator== (const HBond &other) const;
      
    // ACCESS ----------------------------------------------------------------

    /**
     * Returns the donor atom.
     * @param r a residue into which to take the atom.  If none is
     * supplied and the HBond was evaluated on a pair of residues,
     * returns the atom from this donor.
     * @return the donor atom. 
     * @exception NullPointerException is thrown when the residue was assigned.
     */
    const Atom& getDonor () const;
    const Atom& getDonor (const Residue &r) const;

    /**
     * Gets the donor atom type.
     * @return the donor atom type.
     */
    const AtomType* getDonorType () const { return donor; }

    /**
     * Returns the hydrogen atom.
     * @param r a residue into which to take the atom.  If none is
     * supplied and the HBond was evaluated on a pair of residues,
     * returns the atom from this donor.
     * @return the hydrogen atom. 
     * @exception NullPointerException is thrown when the residue was assigned.
     */
    const Atom& getHydrogen () const;
    const Atom& getHydrogen (const Residue &r) const;

    /**
     * Gets the hydrogen atom type.
     * @return the hydrogen atom type.
     */
    const AtomType* getHydrogenType () const { return hydrogen; }

    /**
     * Returns the acceptor atom.
     * @param r a residue into which to take the atom.  If none is
     * supplied and the HBond was evaluated on a pair of residues,
     * returns the atom from this donor.
     * @return the acceptor atom. 
     * @exception NullPointerException is thrown when the residue was assigned.
     */
    const Atom& getAcceptor () const;
    const Atom& getAcceptor (const Residue &r) const;
      
    /**
     * Gets the acceptor atom type.
     * @return the acceptor atom type.
     */
    const AtomType* getAcceptorType () const { return acceptor; }

    /**
     * Returns the lonepair atom.
     * @param r a residue into which to take the atom.  If none is
     * supplied and the HBond was evaluated on a pair of residues,
     * returns the atom from this donor.
     * @return the lonepair atom.
     * @exception NullPointerException is thrown when the residue was assigned.
     */
    const Atom& getLonePair () const;
    const Atom& getLonePair (const Residue &r) const;
      
    /**
     * Gets the lonepair atom type.
     * @return the lonepair atom type.
     */
    const AtomType* getLonePairType () const { return lonepair; }

    /**
     * Returns the donor residue location, if one is set for this HBond.
     */
    const Residue* getDonorResidue () const { return resD; }

    /**
     * Returns the donor residue location, if one is set for this HBond.
     */
    const Residue* getAcceptorResidue () const { return resA; }

    /**
     * Gets the probability of forming h-bond.  Initially 0.
     * @return the probability of forming h-bond.
     */
    float getValue () const { return value; }

  private:
      
    /**
     * Replaces the Residue pointers with those coming from the set.  It
     * is used by the Relation class to do a deep copy without doing a full
     * re-annotation.
     * Throws a @ref NoSuchElementException if either resA or resD isn't found in target set.
     * @param resSet a set of Residue pointers.
     * @exception NoSuchElementException
     */
    void reassignResiduePointers (const set< const Residue*, less_deref < Residue > > &resSet);

  public:
      
    // METHODS ---------------------------------------------------------------

    /**
     * Evaluates the possibility that the given hydrogen bond forms
     * given the spatial coordinates of the residues (based on
     * Sebastien's observation that the Hydrogen-LP distance is a good
     * criteria).
     * @param ra the residue location that contains the donor atom.
     * @param rb the residue location that contains the acceptor atom.
     * @return a score between 0 and 1, where 0 is low probability and 1 is high probability.
     */
    float eval (const Residue *ra, const Residue *rb);

    /**
     * Evaluates the possibility that the given hydrogen bond forms
     * given the spatial coordinates of the residues (based on a
     * Gaussian mixture model which should be used only for RNA/DNA
     * base pairs).
     * @param ra the residue location that contains the donor atom.
     * @param rb the residue location that contains the acceptor atom.
     * @return a score between 0 and 1, where 0 is low probability and 1 is high probability.      
     */
    float evalStatistically (const Residue *ra, const Residue *rb);
      
    // I/O -------------------------------------------------------------------

    /**
     * Outputs the H-bond in human readable format.
     * @param os the output stream.
     * @param theBond the H-bond to display.
     * @return the used output stream.
     */
    ostream &output (ostream &os) const;

    /**
     * Reads the HBond from a binary stream.
     * @param is the binary input stream.
     * @param resMap the model's residue mapping to their ResId.
     * @exception NoSuchElementException is thrown when a residue is not found
     * within resMap.
     * @return the binary input stream.
     */
    virtual iBinstream& read (iBinstream &is, const map< ResId, const Residue* > &resMap);
    
    /**
     * Writes the HBond to a binary stream.
     * @param os the binary output stream.
     * @return the binary output stream.
     */
    virtual oBinstream& write (oBinstream &os) const;
    
  };

}



namespace std
{

  /**
   * Writes the HBond through the output stream.
   * @param os the output stream.
   * @param theBond the HBond to write.
   * @return the output stream.
   */
  ostream& operator<< (ostream &os, const mccore::HBond &theBond);

}

#endif
