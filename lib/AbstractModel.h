//                              -*- Mode: C++ -*- 
// AbstractModel.h
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 16:12:42 2004
// $Revision: 1.8 $
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


#ifndef _mccore_AbstractModel_h_
#define _mccore_AbstractModel_h_

#include <iostream>
#include <vector>

#include "Exception.h"

using namespace std;



namespace mccore
{
  class ResId;
  class Residue; 
  class ResidueType; 
  class ResidueFactoryMethod;
  class iBinstream;
  class iPdbstream;
  class oBinstream;
  class oPdbstream;



  /**
   * Abstract class for Models.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: AbstractModel.h,v 1.8 2006-02-24 15:38:07 larosem Exp $
   */
  class AbstractModel
  {
    
  public:
    
    typedef vector< Residue* >::size_type size_type;

  protected:

    /**
     * Factory method for creating new residues.
     */
    ResidueFactoryMethod *residueFM;

  public:

    // ITERATORS --------------------------------------------------------------

    /**
     * @short Iterator class for AbstractModel.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class model_iterator : public vector< Residue* >::iterator
    {
    public:

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the iterator.
       */
      model_iterator () : vector< Residue* >::iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      model_iterator (const vector< Residue* >::iterator &lIt)
	: vector< Residue* >::iterator (lIt)
      { }

      // OPERATORS ------------------------------------------------------------

      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      Residue& operator* () const
      { 
	return *vector< Residue* >::iterator::operator* (); 
      }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      Residue* operator-> () const { return &(operator* ()); }
    };
  
    /**
     * @short Const iterator class for AbstractModel.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class model_const_iterator : public vector< Residue* >::const_iterator
    {
    public:

      /**
       * Initializes the const iterator.
       */
      model_const_iterator () : vector< Residue* >::const_iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      model_const_iterator (const vector< Residue* >::const_iterator &lIt)
	: vector< Residue* >::const_iterator (lIt)
      { }

      /**
       * Initializes the iterator with a non const model_iterator.
       * @param it the model iterator.
       */
      model_const_iterator (const model_iterator& it)
	: vector< Residue* >::const_iterator (it)
      { }

      // OPERATORS ------------------------------------------------------------
      
      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      const Residue& operator* () const
      { return *vector< Residue* >::const_iterator::operator* (); }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      const Residue* operator-> () const { return &(operator* ()); }
    };

  public:

    typedef model_iterator iterator;
    typedef model_const_iterator const_iterator;
  
    // LIFECYCLE ------------------------------------------------------------

  private:

    /**
     * Initializes the object.
     */
    AbstractModel () { }

  protected:
    
    /**
     * Initializes the object.
     * @param fm the residue factory methods that will instanciate new
     * residues (default is @ref ExtendedResidueFM).
     */
    AbstractModel (const ResidueFactoryMethod *fm);

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    AbstractModel (const AbstractModel &right);

  public:
    
    /**
     * Clones the model.
     * @return a copy of the model.
     */
    virtual AbstractModel* clone () const = 0;

    /**
     * Destroys the object.
     */
    virtual ~AbstractModel ();

    // OPERATORS ------------------------------------------------------------

  protected:
    
    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    AbstractModel& operator= (const AbstractModel &right);

  public:

    /**
     * Gets the model reference at nth position.
     * @param nth the position of the reference to get.
     * @return the nth reference.
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual Residue& operator[] (size_type nth) = 0;

    /**
     * Gets the model const_reference at nth position.
     * @param nth the position of the const_reference to get.
     * @return the nth const_reference.
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual const Residue& operator[] (size_type nth) const = 0;

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
    void setResidueFM (const ResidueFactoryMethod *fm = 0);
  
    /**
     * Gets the iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual iterator begin () = 0;

    /**
     * Gets the iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual iterator end () = 0;

    /**
     * Gets the const iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual const_iterator begin () const = 0;

    /**
     * Gets the const iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual const_iterator end () const = 0;

    /**
     * Gets the first element of the model or end if the model is empty.
     * @return the first element of the model or end if the model is empty.
     */
    Residue& front () { return *begin (); }
    
    /**
     * Gets the first element of the model or end if the model is empty.
     * @return the first element of the model or end if the model is empty.
     */
    const Residue& front () const { return *begin (); }

    /**
     * Gets the last element of the model or end if the model is empty.
     * @return the last element of the model or end if the model is empty.
     */
    Residue& back () { return *((iterator) --end ()); }

    /**
     * Gets the last element of the model or end if the model is empty.
     * @return the last element of the model or end if the model is empty.
     */
    const Residue& back () const { return *((const_iterator) --end ()); }

    // METHODS -------------------------------------------------------------

    /**
     * Inserts a residue at the end.  It calls the vector<> method.
     * @param res the residue to insert.
     * @return the position where the residue was inserted.
     */
    virtual iterator insert (const Residue &res) = 0;

    /**
     * Inserts the residue range before pos.  It calls the vector<> method.
     * @param pos the iterator where the residue will be placed.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     */
    template <class InputIterator>
    void insert (InputIterator f, InputIterator l)
    {
      while (f != l)
	{
	  insert (*f);
	  ++f;
	}
    }

    /**
     * Erases a residue from the model.
     * @param pos the position to erase.
     * @return an iterator on the next residue.
     */ 
    virtual iterator erase (iterator pos) = 0;
    
    /**
     * Finds a residue given it's residue id.  Returns an iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     */
    iterator find (const ResId &id);

    /**
     * Finds a residue given it's residue id.  Returns a AbstractModel iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     */
    const_iterator find (const ResId &id) const;

    /**
     * Finds a residue given it's residue id.  Returns an iterator
     * pointing to the residue or throws an exception if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     * @exception NoSuchElementException
     */
    iterator safeFind (const ResId &id);

    /**
     * Finds a residue given it's residue id.  Returns a AbstractModel iterator
     * pointing to the residue or throws an exception if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     * @exception NoSuchElementException
     */
    const_iterator safeFind (const ResId &id) const;
    
    /**
     * Sorts the model according to the Residue::operator<
     */ 
    virtual void sort () = 0;
    
    /**
     * Returns the number of residues present in the model.
     * @return a number of residues.
     */
    virtual size_type size () const = 0;

    /**
     * Tells if there is no residue in the model.
     * @return whether the model is empty.
     */
    virtual bool empty () const = 0;

    /**
     * Removes all of the residues from the model.  
     */
    virtual void clear () = 0;

    /**
     * Validates residues contained in the model.  The validated residues (amino
     * acid and nucleic acid) are retained, the others deleted.
     */
    void validate ();

    /**
     * Adds hydrogens and lone pairs to each nucleic acid residue. The
     * terminal HO3' is not added by this method.
     * @param overwrite Flag used to force the placing of an atom even if
     * it's already there (default: true)
     */
    void addHLP (bool overwrite = true);
    
    /**
     * Removes the optional atoms within the residues.
     */
    virtual void removeOptionals ();

    /**
     * Removes the amino acids from the model.
     */
    virtual void removeAminoAcid ();    

    /**
     * Removes the nucleic acids from the model.
     */
    virtual void removeNucleicAcid ();

    /**
     * Removes the water from the model.
     */
    virtual void removeWater ();

    /**
     * Removes every residue that is not an amino acid.
     */
    virtual void keepAminoAcid ();

    /**
     * Removes every residue that is not a nucleic acid.
     */
    virtual void keepNucleicAcid ();

    /**
     * Removes every residue that is not RNA.
     */
    virtual void keepRNA ();

    /**
     * Removes every residue that is not DNA.
     */
    virtual void keepDNA ();

    /**
     * Removes every residue that is not of the specified type family.
     * @param rtype type family.
     */
    virtual void keep (const ResidueType* rtype);

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the model to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const = 0;

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
    virtual iPdbstream& input (iPdbstream &ips) = 0;
  
    /**
     * Writes the model to a binary output stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual oBinstream& output (oBinstream &obs) const = 0;

    /**
     * Reads the model from a binary input stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual iBinstream& input (iBinstream &ibs) = 0;

  };

  /**
   * Inputs the model from a pdb stream.
   * @param ips the input pdb stream.
   * @param obj the model where to put the residues.
   * @return the input pdb stream.
   */
  iPdbstream& operator>> (iPdbstream &ips, AbstractModel &obj);

  /**
   * Outputs the model to a pdb stream.  Termination between residue
   * chains are made.
   * @param ops the output pdb stream.
   * @param obj the model to output.
   * @return the output pdb stream.
   */
  oPdbstream& operator<< (oPdbstream &ops, const AbstractModel &obj);

  /**
   * Inputs the model from a binary stream.
   * @param ibs the input binary stream.
   * @param obj the model where to put the residues.
   * @return the input binary stream.
   */
  iBinstream& operator>> (iBinstream &ibs, AbstractModel &obj);

  /**
   * Outputs the model to a binary stream.
   * @param obs the output binary stream.
   * @param obj the model to output.
   * @return the output binary stream.
   */
  oBinstream& operator<< (oBinstream &obs, const AbstractModel &obj);

  /**
   * Test the partial order (Residue order) between model iterators.
   * @param left the left operand.
   * @param right the right operand.
   * @return wheter the residue pointed by left is less than right.
   */
  bool operator< (const AbstractModel::iterator &left, const AbstractModel::iterator &right);

  /**
   * Test the partial order (Residue order) between model const_iterators.
   * @param left the left operand.
   * @param right the right operand.
   * @return wheter the residue pointed by left is less than right.
   */
  bool operator< (const AbstractModel::const_iterator &left, const AbstractModel::const_iterator &right);

}



namespace std
{
  
  /**
   * Outputs the model to an output stream.
   * @param obs the output stream.
   * @param obj the model to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const mccore::AbstractModel &obj);

}

#endif
