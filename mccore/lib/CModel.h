//                              -*- Mode: C++ -*- 
// CModel.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon May 28 14:31:45 2001
// Update Count     : 7
// Status           : Unknown.
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


#ifndef _CModel_h_
#define _CModel_h_


#include <list.h>

#include "CResidue.h"


class iPdbstream;
class oPdbstream;
class iBinstream;
class oBinstream;



/**
 * @short Container for residues.
 * 
 * This object is the container for residues.  It is an unsorted list of
 * residues.  Random access is simulated with sequential access.  This class
 * should be the replacement for nearly all CResidue*.
 *
 * @author Martin Larose
 */
class CModel : public list< CResidue >
{
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  CModel () : list< CResidue > () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CModel (const CModel &right) : list< CResidue > (right) { }

  /**
   * Destructs the object.
   */
  ~CModel () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  CModel& operator= (const CModel &right);

  /**
   * Gets the model reference at nth position.
   * @param nth the position of the reference to get.
   * @return the nth reference.
   */
  reference operator[] (unsigned int nth);

  /**
   * Gets the model const_reference at nth position.
   * @param nth the position of the const_reference to get.
   * @return the nth const_reference.
   */
  const_reference operator[] (unsigned int nth) const;

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Creates a new model with validated residues.
   * @return the new model.
   */
  CModel Validate () const;

  /**
   * Creates a new model with all the optional atoms removed.
   * @return the new model.
   */
  CModel RemoveOptionals () const;

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  CResidue::iterator find (const char *str);

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  CResidue::const_iterator find (const char *str) const;

  /**
   * Finds a residue given it's residue id.  Returns a CModel iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a CModel iterator.
   */
  CModel::iterator find (const CResId &id);

  /**
   * Finds a residue given it's residue id.  Returns a CModel iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a CModel iterator.
   */
  CModel::const_iterator find (const CResId &id) const;

  // I/O  -----------------------------------------------------------------
};



/**
 * Test the partial order (CResidue order) between model iterators.
 * @param left the left operand.
 * @param right the right operand.
 * @return wheter the residue pointed by left is less than right.
 */
bool operator< (const CModel::iterator &left, const CModel::iterator &right);



/**
 * Inputs the model from a pdb stream.
 * @param ips the input pdb stream.
 * @param obj the model where to put the residues.
 * @return the input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, CModel &obj);



/**
 * Outputs the model to a pdb stream.  PDB headers are not printed but
 * termination between residue chains are made.
 * @param ops the output pdb stream.
 * @param obj the model to output.
 * @return the output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const CModel &obj);



/**
 * Inputs the model from a binary stream.
 * @param ibs the input binary stream.
 * @param obj the model where to put the residues.
 * @return the input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, CModel &obj);



/**
 * Outputs the model to a binary stream.
 * @param obs the output binary stream.
 * @param obj the model to output.
 * @return the output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const CModel &obj);

#endif
