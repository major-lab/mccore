//                              -*- Mode: C++ -*- 
// CHBond.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:02:50 2001
// Update Count     : 2
// Status           : Ok.
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


#ifndef _CHBond_h
#define _CHBond_h


class CResidue;
class t_Atom;
class ostream;



/**
 * @short Describes the H-bond between to atoms.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CHBond
{
  /**
   * The left residue in the bond.
   */
  const CResidue *mResidueA;

  /**
   * The right residue in the bond.
   */
  const CResidue *mResidueB;

  /**
   * The donor atom type implicated in the bond.
   */
  t_Atom *mDonor;

  /**
   * The acceptor type implicated in the bond.
   */
  t_Atom *mAcceptor;

  /**
   * The hydrogen type implicated in the bond.
   */
  t_Atom *mHydro;

  /**
   * The lone pair type implicated in the bond.
   */
  t_Atom *mLonePair;

  /**
   * The penality associated with the bond.  It is calculated once and then
   * cached in this variable.  Initial value -1.
   */
  mutable float cache_penality;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.  Every pointer is set to 0 and the
   * cache_penalty is set to -1.
   */
  CHBond ();

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CHBond (const CHBond &right);

  /**
   * Initializes the object.
   * @param nResidueA the left residue.
   * @param nResidueB the right residue.
   * @param nDonor the donor atom type.
   * @param nHydro the hydrogen type.
   * @param nAcceptor the acceptor atom type.
   * @param nLonePair the lonepair implicated.
   */
  CHBond (const CResidue *nResidueA, const CResidue *nResidueB,
	  t_Atom *nDonor, t_Atom *nHydro, 
	  t_Atom *nAcceptor, t_Atom *nLonePair);

  /**
   * Destructs the object.  Nothing to do.
   */
  ~CHBond () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  const CHBond& operator= (const CHBond &right);

  /**
   * Calculates the penalty for the actual H-bond.  The result is cached
   * into cache_penalty.
   */
  operator float () const;
  
  // ACCESS ---------------------------------------------------------------

  /**
   * Sets the CHBond slots.
   * @param nResidueA the left residue.
   * @param nResidueB the right residue.
   * @param nDonor the donor atom type.
   * @param nHydro the hydrogen type.
   * @param nAcceptor the acceptor atom type.
   * @param nLonePair the lonepair implicated.
   */
  void SetHBond (const CResidue *nResidueA, const CResidue *nResidueB,
		 t_Atom *nDonor, t_Atom *nHydro,
		 t_Atom *nAcceptor, t_Atom *nLonePair);

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the H-bond in Amber restraint format.
   * @param os the output stream.
   */
  void DumpAmberRestraint (ostream &os);

  /**
   * Outputs the H-bond in human readable format.
   * @param os the output stream.
   * @param theBond the H-bond to display.
   * @return the used output stream.
   */
  friend ostream &operator<< (ostream &os, const CHBond &theBond);
};

#endif









