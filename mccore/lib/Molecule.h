//                              -*- Mode: C++ -*- 
// Molecule.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose
// Created On       : Mon Jul  7 15:59:36 2003
// $Revision: 1.4.2.2 $
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


#ifndef _mccore_Molecule_h_
#define _mccore_Molecule_h_

#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;


namespace mccore
{
  class AbstractModel;
  class ResidueFactoryMethod;
  class iPdbstream;
  class oPdbstream;
  class iBinstream;
  class oBinstream;
  
  /**
   * @short Container for a collection of Models.
   *
   * This is a collection of mccore Models in a simple STL list.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Molecule.h,v 1.4.2.2 2004-12-25 02:42:24 larosem Exp $
   */
  class Molecule
  {
  public:
    
    typedef unsigned int size_type;

  protected:
    
    /**
     * Container for Models.
     */
    list< AbstractModel* > models;

    /**
     * Properties for the molecule class.
     */
    map< string, string > properties;
    
    /**
     * Factory method for creating new residues within new models.
     */
    ResidueFactoryMethod *residueFM;
    
  public:
    
    // ITERATORS -----------------------------------------------------------------

    /**
     * @short Iterator class for Molecule.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class molecule_iterator : public list< AbstractModel* >::iterator
    {
    public:

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the iterator.
       */
      molecule_iterator () : list< AbstractModel* >::iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      molecule_iterator (const list< AbstractModel* >::iterator &lIt)
	: list< AbstractModel* >::iterator (lIt)
      { }

      // OPERATORS ------------------------------------------------------------

      /**
       * Defines a difference operator for Molecule iterators.
       * @param right the right iterator value in the difference.
       * @return the distance between the iterators.
       */
      unsigned int operator- (const molecule_iterator &right) const;
    
      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      AbstractModel& operator* () const
      { 
	return *list< AbstractModel* >::iterator::operator* (); 
      }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      AbstractModel* operator-> () const { return &(operator* ()); }
    };
  
    /**
     * @short Const iterator class for Molecule.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class molecule_const_iterator : public list< AbstractModel* >::const_iterator
    {
    public:

      /**
       * Initializes the const iterator.
       */
      molecule_const_iterator () : list< AbstractModel* >::const_iterator () { }
    
      /**
       * Initializes the iterator with the list iterator.
       * @param lIt the list iterator.
       */
      molecule_const_iterator (const list< AbstractModel* >::const_iterator &lIt)
	: list< AbstractModel* >::const_iterator (lIt)
      { }

      /**
       * Initializes the iterator with a non const molecule_iterator.
       * @param it the molecule iterator.
       */
      molecule_const_iterator (const molecule_iterator& it)
	: list< AbstractModel* >::const_iterator (it)
      { }

      // OPERATORS ------------------------------------------------------------
      
      /**
       * Defines a difference operator for Molecule const_iterators.
       * @param right the right iterator value in the difference.
       * @return the distance between the iterators.
       */
      unsigned int operator- (const molecule_const_iterator &right) const;

      /**
       * Redefines the access operator* to get the dereferenced residue.
       * @return the referenced residue.
       */
      const AbstractModel& operator* () const
      { return *list< AbstractModel* >::const_iterator::operator* (); }

      /**
       * Redefines the access operator-> to get the dereferenced residue.
       * @return the pointed residue.
       */
      const AbstractModel* operator-> () const { return &(operator* ()); }
    };

  public:

    typedef molecule_iterator iterator;
    typedef molecule_const_iterator const_iterator;
      
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     * @param fm the residue factory methods that will instanciate new residues (default is @ref ExtendedResidueFM).
     */
    Molecule (const ResidueFactoryMethod *fm = 0);
    
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    Molecule (const Molecule &right);
    
    /**
     * Clones the molecule.
     * @return a copy of the molecule.
     */
    virtual Molecule* clone () const { return new Molecule (*this); }
    
    /**
     * Destroys the object.
     */
    virtual ~Molecule ();
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    Molecule& operator= (const Molecule &right);

    /**
     * Gets the model reference at nth position.
     * @param nth the position of the reference to get.
     * @return the nth reference.
     */
    AbstractModel& operator[] (size_type nth);

    /**
     * Gets the model const_reference at nth position.
     * @param nth the position of the const_reference to get.
     * @return the nth const_reference.
     */
    const AbstractModel& operator[] (size_type nth) const;
    
    // ACCESS ---------------------------------------------------------------
    
    /**
     * Gets the property value of the key. Throws an @ref IntLibException
     * if key isn't found.
     * @param key the key.
     * @return the value of the key.
     * @throws IntLibException
     */
    const char* getProperty (const char *key) const;
    
    /**
     * Sets the key value pair.
     * @param key the key.
     * @param value the value.
     */
    void setProperty (const string &key, const string &value);
    
    /**
     * Gets the property map.
     * @return the property map.
     */
    const map< string, string >& getProperties () const
    {
      return this->properties;
    }

   /**
     * Gets the residue factory method.
     * @return the residue factory method.
     */
    const ResidueFactoryMethod* getResidueFM () const
    {
      return this->residueFM;
    }
  
    /**
     * Sets the residue factory method.
     * @param fm the new factory method to use (default is @ref ExtendedResidueFM).
     */
    void setResidueFM (const ResidueFactoryMethod *fm = 0);

    /**
     * Gets the iterator pointing to the beginning of the molecule.
     * @return the iterator.
     */
    iterator begin ()
    {
      return iterator (models.begin ());
    }

    /**
     * Gets the iterator pointing to the end of the molecule.
     * @return the iterator.
     */
    iterator end ()
    {
      return iterator (models.end ());
    }

    /**
     * Gets the const iterator pointing to the beginning of the molecule.
     * @return the iterator.
     */
    const_iterator begin () const
    {
      return const_iterator (models.begin ());
    }

    /**
     * Gets the const iterator pointing to the end of the molecule.
     * @return the iterator.
     */
    const_iterator end () const
    {
      return const_iterator (models.end());
    }
    
    // METHODS --------------------------------------------------------------

    /**
     * Inserts a model at the end.
     * @param model the model to insert.
     * @return the position where the residue was inserted.
     */
    iterator insert (const AbstractModel& model)
    {
      return this->models.insert (models.end (), model.clone ());
    }
    
    /**
     * Inserts the model range before pos.  It calls the list<> method.
     * @param pos the iterator where the model will be placed.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     */
    template <class InputIterator>
    void insert(InputIterator f, InputIterator l)
    {
      while (f != l)
	{
	  this->insert (*f);
	  ++f;
	}
    }

    /**
     * Erases a model from the molecule.
     * @param pos the position to erase.
     * @return an iterator on the next model.
     */ 
    iterator erase (iterator pos) 
    {
      return this->models.erase (pos);
    }
    
    /**
     * Returns the number of models present in the molecule.
     * @return a number of models.
     */
    size_type size () const
    {
      return this->models.size ();
    }

    /**
     * Tells if there is no model in the molecule.
     * @return whether the molecule is empty.
     */
    bool empty () const
    {
      return this->models.empty ();
    }

    /**
     * Removes all of the models from the molecule.  
     */
    virtual void clear();
    
    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the molecule to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    ostream& write (ostream &os) const;

    /**
     * Writes the molecule to a pdb output stream.
     * @param ops the pdb data stream.
     * @return the consumed pdb stream.
     */
    oPdbstream& write (oPdbstream &ops) const;

    /**
     * Reads the molecule from a pdb input stream.
     * @param ips the pdb data stream.
     * @return the consumed pdb stream.
     */
    iPdbstream& read (iPdbstream &ips);
  
    /**
     * Writes the molecule to a binary output stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    oBinstream& write (oBinstream &obs) const;

    /**
     * Reads the molecule from a binary input stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    iBinstream& read (iBinstream &ibs);
    
  };
  
  // NON-MEMBER FUNCTION -------------------------------------------------------
  
  /**
   * Outputs the molecule to an output stream.
   * @param obs the output stream.
   * @param obj the molecule to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const Molecule &obj);
  
  /**
   * Inputs the molecule from a pdb stream.
   * @param ips the input pdb stream.
   * @param obj the molecule where to put the molecules.
   * @return the input pdb stream.
   */
  iPdbstream& operator>> (iPdbstream &ips, Molecule &obj);
  
  /**
   * Outputs the molecule to a pdb stream.
   * @param ops the output pdb stream.
   * @param obj the molecule to output.
   * @return the output pdb stream.
   */
  oPdbstream& operator<< (oPdbstream &ops, const Molecule &obj);

}

#endif
