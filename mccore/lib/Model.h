//                              -*- Mode: C++ -*- 
// Model.h
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// $Revision: 1.14 $
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

#include <list>

#include "Residue.h"

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  class ResidueFactoryMethod;
  class iPdbstream;
  class oPdbstream;


  /**
   * @short Container for residues using a simple list.
   *
   * This object is the container for residues.  It is an unsorted list
   * of residues.  Random access is simulated with sequential access.
   * This class should be the replacement for nearly all Residue containers.
   *
   * NOTES:
   *
   * - The container contains pointers to residues but dereferenced
   *   iterators yields object.
   *
   *  - Please do not change the STL container (see removeClash for
   * details).
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: Model.h,v 1.14 2003-09-26 21:16:34 gendrop Exp $
   */
  class Model
  {

  public:

    typedef unsigned int size_type;

  private:

    /**
     * Factory method for creating new residues.
     */
    ResidueFactoryMethod *residueFM;


    /**
     * Container for Residues.
     */
    list< Residue* > residues;

  public:

    class model_iterator;
    typedef model_iterator iterator;
    class model_const_iterator;
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
    Residue& operator[] (size_type nth);

    /**
     * Gets the model const_reference at nth position.
     * @param nth the position of the const_reference to get.
     * @return the nth const_reference.
     */
    const Residue& operator[] (size_type nth) const;

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
    iterator begin () { return iterator (residues.begin ()); }

    /**
     * Gets the iterator pointing to the end of the model.
     * @return the iterator.
     */
    iterator end () { return iterator (residues.end ()); }

    /**
     * Gets the const iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    const_iterator begin () const
    { return const_iterator (residues.begin ()); }

    /**
     * Gets the const iterator pointing to the end of the model.
     * @return the iterator.
     */
    const_iterator end () const
    { return const_iterator (residues.end()); }


    // METHODS -------------------------------------------------------------

    /**
     * Inserts a residue.  It calls the list<> method.
     * @param pos the iterator where the residue will be placed.
     * @param res the residue to insert.
     * @return the position where the residue was inserted.
     */
    iterator insert (const Residue &res);

    /**
     * Inserts the residue range before pos.  It calls the list<> method.
     * @param pos the iterator where the residue will be placed.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     * @return the position where the residue was inserted.
     */
    template <class InputIterator>
    void insert(InputIterator f, InputIterator l)
    {
      while (f != l)
	{
	  insert (*f);
	  ++f;
	}
    }

    /**
     * Erase a residue from the model.
     * @param 
     * @return an iterator on the next residue.
     */ 
    iterator erase (iterator &i) 
    {
      return residues.erase (i);
    }
    
    //   /**
    //    * Finds an atom given it's text representation of the form residue:atom.
    //    * Returns a empty iterator if it is not found.
    //    * @param str the text representation.
    //    * @return the residue iterator over the atom.
    //    */
    //   Residue::iterator find (const char *str);

    //   /**
    //    * Finds an atom given it's text representation of the form residue:atom.
    //    * Returns a empty iterator if it is not found.
    //    * @param str the text representation.
    //    * @return the residue iterator over the atom.
    //    */
    //   Residue::const_iterator find (const char *str) const;

    /**
     * Finds a residue given it's residue id.  Returns an iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a Model iterator.
     */
    iterator find (const ResId &id);

    /**
     * Finds a residue given it's residue id.  Returns a Model iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a Model iterator.
     */
    const_iterator find (const ResId &id) const;

    /**
     * Sorts the model according to the Residue::operator<
     */ 
    void sort ();

    /**
     * Returns the number of residues present in the model.
     * @return a number of residues.
     */
    size_type size () const;

    /**
     * Tells if there is no residue in the model.
     * @return whether the model is empty.
     */
    bool empty () const;

    /**
     * Removes all of the residues from the model.  
     */
    void clear();

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

    /**
     * Remove residues that clash (cutoff 1A, no H, no LP).  This method
     * will work only if model iterators are secure, i.e. are not
     * rendered invalid by deletion in the container.  At the time of
     * writing this, the Model uses a list.
     */
    //   void removeClashes ();

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the model to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    ostream& output (ostream &os) const;

    /**
     * Writes the model to a pdb output stream.
     * @param ops the pdb data stream.
     * @return the consumed pdb stream.
     */
    oPdbstream& output (oPdbstream &ops) const;

    /**
     * Reads the model from a pdb input stream.
     * @param ips the pdb data stream.
     * @return the consumed pdb stream.
     */
    iPdbstream& input (iPdbstream &ips);
  
    /**
     * Writes the model to a binary output stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    oBinstream& output (oBinstream &obs) const;

    /**
     * Reads the model from a binary input stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    iBinstream& input (iBinstream &ibs);

  protected:

  
    // ITERATORS -----------------------------------------------------------------

    /**
     * @short Iterator class for Model.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class model_iterator : public list< Residue* >::iterator
    {
    public:

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the iterator.
       */
      model_iterator () : list< Residue* >::iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      model_iterator (const list< Residue* >::iterator &lIt)
	: list< Residue* >::iterator (lIt)
      { }

      // OPERATORS ------------------------------------------------------------

      /**
       * Defines a difference operator for Model iterators.
       * @param right the right iterator value in the difference.
       * @return the distance between the iterators.
       */
      unsigned int operator- (const model_iterator &right) const;
    
      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      Residue& operator* () const
      { 
	return *list< Residue* >::iterator::operator* (); 
      }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      Residue* operator-> () const { return &(operator* ()); }
    };
  
    /**
     * @short Const iterator class for Model.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class model_const_iterator : public list< Residue* >::const_iterator
    {
    public:

      /**
       * Initializes the const iterator.
       */
      model_const_iterator () : list< Residue* >::const_iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      model_const_iterator (const list< Residue* >::const_iterator &lIt)
	: list< Residue* >::const_iterator (lIt)
      { }

      /**
       * Initializes the iterator with a non const model_iterator.
       * @param it the model iterator.
       */
      model_const_iterator (const model_iterator& it)
	: list< Residue* >::const_iterator (it)
      { }

      // OPERATORS ------------------------------------------------------------
      
      /**
       * Defines a difference operator for Model const_iterators.
       * @param right the right iterator value in the difference.
       * @return the distance between the iterators.
       */
      unsigned int operator- (const model_const_iterator &right) const;

      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      const Residue& operator* () const
      { return *list< Residue* >::const_iterator::operator* (); }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      const Residue* operator-> () const { return &(operator* ()); }
    };

  };


  // NON-MEMBER FUNCTION -------------------------------------------------------


  /**
   * Outputs the model to an output stream.
   * @param obs the output stream.
   * @param obj the model to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const Model &obj);



  /**
   * Inputs the model from a pdb stream.
   * @param ips the input pdb stream.
   * @param obj the model where to put the residues.
   * @return the input pdb stream.
   */
  iPdbstream& operator>> (iPdbstream &ips, Model &obj);



  /**
   * Outputs the model to a pdb stream.  Termination between residue
   * chains are made.
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



  /**
   * Test the partial order (Residue order) between model iterators.
   * @param left the left operand.
   * @param right the right operand.
   * @return wheter the residue pointed by left is less than right.
   */
  bool operator< (const Model::iterator &left, const Model::iterator &right);



  /**
   * Test the partial order (Residue order) between model const_iterators.
   * @param left the left operand.
   * @param right the right operand.
   * @return wheter the residue pointed by left is less than right.
   */
  bool operator< (const Model::const_iterator &left, const Model::const_iterator &right);

}

#endif
