//                              -*- Mode: C++ -*- 
// Model.h
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// $Revision: 1.27 $
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


#ifndef _mccore_Model_h_
#define _mccore_Model_h_

#include <iostream>
#include <vector>

#include "AbstractModel.h"
#include "Exception.h"

using namespace std;



namespace mccore
{
  class ResId;
  class Residue; 
  class ResidueFactoryMethod;
  class iBinstream;
  class iPdbstream;
  class oBinstream;



  /**
   * @short Container for residues.
   *
   * This object is the container for residues.  This class should be the
   * replacement for nearly all Residue containers.
   *
   * NOTES:
   *
   * - The container contains pointers to residues but dereferenced
   *   iterators yields object.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Model.h,v 1.27 2005-12-09 18:28:51 larosem Exp $
   */
  class Model : public AbstractModel
  {
    /**
     * Container for Residues.
     */
    vector< Residue* > residues;

    // LIFECYCLE ------------------------------------------------------------

  public:

    /**
     * Initializes the object.
     * @param fm the residue factory methods that will instanciate new residues (default is @ref ExtendedResidueFM).
     */
    Model (const ResidueFactoryMethod *fm = 0) : AbstractModel (fm) { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     * @param fm the residues factory methods that will instanciate new residues (default is @ref ExtendedResidueFM).
     */
    Model (const AbstractModel &right, const ResidueFactoryMethod *fm = 0);

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     * @param fm the residues factory methods that will instanciate new residues (default is @ref ExtendedResidueFM).
     */
    Model (const Model &right, const ResidueFactoryMethod *fm = 0);

    /**
     * Clones the model.
     * @return a copy of the model.
     */
    virtual AbstractModel* clone () const
    {
      return new Model (*this);
    }

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
    Model& operator= (const AbstractModel &right);

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
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual Residue& operator[] (size_type nth);

    /**
     * Gets the model const_reference at nth position.
     * @param nth the position of the const_reference to get.
     * @return the nth const_reference.
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual const Residue& operator[] (size_type nth) const;

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual iterator begin () { return iterator (residues.begin ()); }

    /**
     * Gets the iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual iterator end () { return iterator (residues.end ()); }

    /**
     * Gets the const iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual const_iterator begin () const
    { return const_iterator (residues.begin ()); }

    /**
     * Gets the const iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual const_iterator end () const
    { return const_iterator (residues.end()); }

    // METHODS -------------------------------------------------------------

    /**
     * Inserts a residue at the end.  It calls the vector<> method.
     * @param res the residue to insert.
     * @return the position where the residue was inserted.
     */
    virtual iterator insert (const Residue &res);

    /**
     * Erases a residue from the model.
     * @param pos the position to erase.
     * @return an iterator on the next residue.
     */ 
    virtual iterator erase (iterator pos);
    
    /**
     * Sorts the model according to the Residue::operator<
     */ 
    virtual void sort ();
    
    /**
     * Returns the number of residues present in the model.
     * @return a number of residues.
     */
    virtual size_type size () const { return residues.size (); }

    /**
     * Tells if there is no residue in the model.
     * @return whether the model is empty.
     */
    virtual bool empty () const { return residues.empty (); }

    /**
     * Removes all of the residues from the model.  
     */
    virtual void clear ();

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the model to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Reads the model from a pdb input stream.
     * @param ips the pdb data stream.
     * @return the consumed pdb stream.
     */
    virtual iPdbstream& input (iPdbstream &ips);
  
    /**
     * Writes the model to a binary output stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;

    /**
     * Reads the model from a binary input stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual iBinstream& input (iBinstream &ibs);

  };
}

#endif
