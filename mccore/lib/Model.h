//                              -*- Mode: C++ -*- 
// Model.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Oct 25 11:20:57 2001
// Update Count     : 2
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


#ifndef _Model_h_
#define _Model_h_

#include <list.h>

#include "AbstractResidue.h"

class ResidueFactoryMethod;
class iPdbstream;
class oPdbstream;
class iBinstream;
class oBinstream;



/**
 * @short Container for residues.
 *
 * This object is the container for abstract residues.  It is an unsorted list
 * of residues.  Random access is simulated with sequential access.  This class
 * should be the replacement for nearly all Residue*.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class Model : public list< AbstractResidue* >
{
  /**
   * Factory method for creating new residues.
   */
  ResidueFactoryMethod *residueFM;
  
protected:

  /**
   * @short Iterator class for Model.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class model_iterator : public list< AbstractResidue* >::iterator
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the iterator.
     */
    model_iterator () : list< AbstractResidue* >::iterator () { }
    
    /**
     * Initializes the iterator with the list iterator.
     * @param lIt the list iterator.
     */
    model_iterator (list< AbstractResidue*>::iterator lIt)
      : list< AbstractResidue* >::iterator (lIt)
    { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the iterator to the right's contents.
     * @param right the iterator to copy.
     * @return itself.
     */
    model_iterator& operator= (const model_iterator &right);

    /**
     * Tests the equality between iterators.
     * @param right the iterator to test.
     * @return the result of the test.
     */
    bool operator== (const model_iterator &right) const
    { return list< AbstractResidue* >::iterator::operator== (right); }
     
    /**
     * Tests the inequality between iterators.
     * @param right the iterator to test.
     * @return the result of the test.
     */
    bool operator!= (const model_iterator &right) const
    { return !operator== (right); }
     
    /**
     * Redefines the access operator* to get the dereferenced residue.
     * @return the referenced residue.
     */
    AbstractResidue& operator* () const
    { return *list< AbstractResidue* >::iterator::operator* (); }

    /**
     * Redefines the access operator-> to get the dereferenced residue.
     * @return the pointed residue.
     */
    AbstractResidue* operator-> () const { return &(operator* ()); }
  };
  
  /**
   * @short Const iterator class for Model.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class model_const_iterator : public list< AbstractResidue* >::const_iterator
  {
  public:

    /**
     * Initializes the const iterator.
     */
    model_const_iterator () : list< AbstractResidue* >::const_iterator () { }
    
    /**
     * Initializes the iterator with the list iterator.
     * @param lIt the list iterator.
     */
    model_const_iterator (list< AbstractResidue*>::const_iterator lIt)
      : list< AbstractResidue* >::const_iterator (lIt)
    { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the iterator to the right's contents.
     * @param right the iterator to copy.
     * @return itself.
     */
    model_const_iterator& operator= (const model_const_iterator &right);

    /**
     * Tests the equality between iterators.
     * @param right the iterator to test.
     * @return the result of the test.
     */
    bool operator== (const model_const_iterator &right) const
    { return list< AbstractResidue* >::const_iterator::operator== (right); }
     
    /**
     * Tests the inequality between iterators.
     * @param right the iterator to test.
     * @return the result of the test.
     */
    bool operator!= (const model_const_iterator &right) const
    { return !operator== (right); }
     
    /**
     * Redefines the access operator* to get the dereferenced residue.
     * @return the referenced residue.
     */
    const AbstractResidue& operator* () const
    { return *list< AbstractResidue* >::const_iterator::operator* (); }

    /**
     * Redefines the access operator-> to get the dereferenced residue.
     * @return the pointed residue.
     */
    const AbstractResidue* operator-> () const { return &(operator* ()); }
  };
  
public:

  typedef model_iterator iterator;
  typedef model_const_iterator const_iterator;
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   * @param fm the residue factory methods that will instanciate new residues.
   */
  Model (ResidueFactoryMethod *fm = 0);

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  Model (const Model &right);

  /**
   * Clones the model.
   * @return a copy of the model.
   */
  virtual Model* clone () const { return new Model (*this); }

  /**
   * Destroys the object.
   */
  virtual ~Model ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  Model& operator= (const Model &right);

  /**
   * Gets the model reference at nth position.
   * @param nth the position of the reference to get.
   * @return the nth reference.
   */
  AbstractResidue& operator[] (size_type nth);

  /**
   * Gets the model const_reference at nth position.
   * @param nth the position of the const_reference to get.
   * @return the nth const_reference.
   */
  const AbstractResidue& operator[] (size_type nth) const;

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the residue factory method.
   * @return the residue factory method.
   */
  const ResidueFactoryMethod* getResidueFM () const { return residueFM; }
  
  /**
   * Sets the residue factory method.
   * @param fm the new factory method to use.
   */
  void setResidueFM (ResidueFactoryMethod *fm);
  
  /**
   * Gets the iterator pointing to the beginning of the model.
   * @return the iterator.
   */
  iterator begin () { return iterator (list< AbstractResidue* >::begin ()); }

  /**
   * Gets the const iterator pointing to the beginning of the model.
   * @return the iterator.
   */
  const_iterator begin () const
  { return const_iterator (list< AbstractResidue* >::begin ()); }

  /**
   * Gets the iterator pointing to the end of the model.
   * @return the iterator.
   */
  iterator end () { return iterator (list< AbstractResidue* >::end ()); }

  /**
   * Gets the const iterator pointing to the end of the model.
   * @return the iterator.
   */
  const_iterator end () const
  { return const_iterator (list< AbstractResidue* >::end()); }

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  AbstractResidue::iterator find (const char *str);

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  AbstractResidue::const_iterator find (const char *str) const;

  /**
   * Finds a residue given it's residue id.  Returns an iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a Model iterator.
   */
  iterator find (const CResId &id);

  /**
   * Finds a residue given it's residue id.  Returns a Model iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a Model iterator.
   */
  const_iterator find (const CResId &id) const;

  // METHODS --------------------------------------------------------------

  /**
   * Validates residues contained in the model.  The validated residues (amino
   * acid and nucleic acid) are retained, the others deleted.
   */
  void validate ();

  /**
   * Removes the optional atoms within the residues.
   */
  void removeOptionals ();

  /**
   * Removes the amino acids from the model.
   */
  void removeAminoAcid ();

  /**
   * Removes the nucleic acids from the model.
   */
  void removeNucleicAcid ();

  /**
   * Removes every residue that is not an amino acid.
   */
  void keepAminoAcid ();

  /**
   * Removes every residue that is not a nucleic acid.
   */
  void keepNucleicAcid ();

  // I/O  -----------------------------------------------------------------

  /**
   * Reads the model from a data input stream.
   * @param ibs the input data stream.
   * @return the new model generated by the read.
   */
  static Model* read (iBinstream &ibs);

  /**
   * Reads the model from a pdb input stream.
   * @param ibs the input pdb stream.
   * @return the new model generated by the read.
   */
  static Model* read (iPdbstream &ips);

  /**
   * Writes the model to a data output stream.
   * @param obs the output data stream.
   * @return the consumed data stream.
   */
  virtual oBinstream& write (oBinstream &obs) const;

  /**
   * Writes the model to a pdb output stream.
   * @param obs the pdb data stream.
   * @return the consumed pdb stream.
   */
  virtual oPdbstream& write (oPdbstream &obs) const;
};



/**
 * Test the partial order (Residue order) between model iterators.
 * @param left the left operand.
 * @param right the right operand.
 * @return wheter the residue pointed by left is less than right.
 */
bool operator< (const Model::iterator &left, const Model::iterator &right);



/**
 * Inputs the model from a pdb stream.
 * @param ips the input pdb stream.
 * @param obj the model where to put the residues.
 * @return the input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, Model &obj);



/**
 * Outputs the model to a pdb stream.  PDB headers are not printed but
 * termination between residue chains are made.
 * @param ops the output pdb stream.
 * @param obj the model to output.
 * @return the output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const Model &obj);



/**
 * Inputs the model from a binary stream.
 * @param ibs the input binary stream.
 * @param obj the model where to put the residues.
 * @return the input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, Model &obj);



/**
 * Outputs the model to a binary stream.
 * @param obs the output binary stream.
 * @param obj the model to output.
 * @return the output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const Model &obj);

#endif
