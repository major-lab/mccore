//                              -*- Mode: C++ -*- 
// AbstractResidue.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct 12 18:21:13 2001
// Last Modified By : Martin Larose
// Last Modified On : Fri Nov 16 13:30:46 2001
// Update Count     : 5
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


#ifndef _AbstractResidue_h_
#define _AbstractResidue_h_


#include <map.h>

#include "CResId.h"
#include "CTransfo.h"

class AtomSet;
class CAtom;
class iBinstream;
class oBinstream;
class iPdbstream;
class oPdbstream;
class ostream;
class t_Atom;
class t_Residue;



/**
 * @short Abstract class for residues.
 *
 * This residue is a container for Atom.  We define a set of operators and
 * methods that looks like the STL vector: comparators, iterators, insert and
 * erase methods.  The atom container is not itself included in the class, it
 * might be interesting to use an other type of container (a map per example).
 * This choice is left to the implementation.  Atom traversal using iterators
 * is garantied to follow a partial order defined by the atom types.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class AbstractResidue
{
  
public:

  /**
   * The size type of the abstract residue container.
   */
  typedef unsigned int size_type;

protected:

  /**
   * Definition of the sorted mapping.
   */
  typedef map< const t_Atom*, size_type > ResMap;

public:
  
  /**
   * @short Iterators for residues.
   *
   * The iterator provides a generic way to access atoms in different
   * residue component types.  It looks like the forward iterator from STL.
   * It requires that the residue defines a size method and a bracket
   * ([AbstractResidue::size_type]) accessor.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class ResidueIterator
  {

  public:

    typedef random_access_iterator_tag iterator_category;
    typedef CAtom value_type;
    typedef ptrdiff_t difference_type;
    typedef CAtom* pointer;
    typedef CAtom& reference;

  private:

    /**
     * The pointer over the residue.
     */
    AbstractResidue *res;
    
    /**
     * The position of the iterator.  It is given by the ResMap iterator.
     */
    ResMap::iterator pos;
    
    /**
     * The filter function over the atom types.
     */
    AtomSet *filter;

  public:
    
    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the iterator.
     */
    ResidueIterator ();

    /**
     * Initializes the iterator.
     * @param r the residue owning the iterator.
     * @param p the position of the iterator.
     * @param f the filter function.
     */
    ResidueIterator (AbstractResidue *r, ResMap::iterator p, AtomSet *f = 0);

    /**
     * Initializes the iterator with the right's contents.
     * @param right the iterator to copy.
     */
    ResidueIterator (const ResidueIterator &right);
    
    /**
     * Destroys the iterator.
     */
    ~ResidueIterator ();

    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the iterator with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    ResidueIterator& operator= (const ResidueIterator &right);
    
    /**
     * Advances and assigns the iterator of k positions.
     * @param k the number of positions to advance.
     * @return itself.
     */
    ResidueIterator& operator+= (difference_type k);
    
    /**
     * Gets the atom pointed by the current iterator.
     * @return a pointer over the atom placed by the transfo.
     */
    pointer operator-> () const { return &(res->place (pos->second)); }
  
    /**
     * Dereferences the iterator.
     * @return an atom reference.
     */
    reference operator* () const { return res->place (pos->second); }
  
    /**
     * Pre-advances the iterator to the next atom.
     * @return the iterator over the next atom.
     */
    ResidueIterator& operator++ ();
    
    /**
     * Post-advances the iterator to the next atom.
     * @param ign ignored parameter.
     * @return the iterator over the current atom.
     */
    ResidueIterator operator++ (int ign);
    
    /**
     * Adds the iterator to a distance type k.  The result may points to the
     * end of the residue.
     * @param k the distance type.
     * @return a new iterator pointing to itself + k.
     */
    ResidueIterator operator+ (difference_type k) const
    {
      return ResidueIterator (*this) += k;
    }
    
    /**
     * Tests whether the iterators are equal.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator== (const ResidueIterator &right) const
    {
      return res == right.res && pos == right.pos;
    }
    
    /**
     * Tests whether the iterators are different.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator!= (const ResidueIterator &right) const
    {
      return !operator== (right);
    }
    
    /**
     * Tests whether the current iterator is less than the right.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator< (const ResidueIterator &right) const
    {
      return res == right.res && pos->first < right.pos->first;
    }
    
    /**
     * Casts the iterator to a residue.
     * @return the residue pointed by the iterator.
     */
    operator AbstractResidue* () { return res; }
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
    // I/O  -----------------------------------------------------------------
  };
  
  /**
   * @short Const iterators for residues.
   *
   * The const_iterator provides a generic way to access atoms in different
   * residue component types.  It looks like the forward iterator from STL.
   * It requires that the residue defines a size method and a bracket
   * ([AbstractResidue::size_type]) accessor.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class ResidueConstIterator
  {

  public:

    typedef random_access_iterator_tag iterator_category;
    typedef const CAtom value_type;
    typedef ptrdiff_t difference_type;
    typedef const CAtom* pointer;
    typedef const CAtom& reference;

  private:
    
    /**
     * The pointer over the residue.
     */
    const AbstractResidue *res;
    
    /**
     * The residue index where the const_residue_iterator points to.
     */
    ResMap::const_iterator pos;
    
    /**
     * The filter function over the atom types.
     */
    AtomSet *filter;

  public:

    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the iterator.
     */
    ResidueConstIterator ();
    
    /**
     * Initializes the iterator.
     * @param r the residue owning the iterator.
     * @param p the position of the iterator.
     * @param f the filter function.
     */
    ResidueConstIterator (const AbstractResidue *r,
			  ResMap::const_iterator p,
			  AtomSet *f = 0);

    /**
     * Initializes the ResidueConstIterator with the right's contents.
     * @param right the ResidueConstIterator to copy.
     */
    ResidueConstIterator (const ResidueConstIterator &right);
    
    /**
     * Destroys the object.
     */
    ~ResidueConstIterator ();
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the ResidueConstIterator with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    ResidueConstIterator& operator= (const ResidueConstIterator &right);
    
    /**
     * Advances and assigns the const_iterator of k positions.
     * @param k the number of positions to advance.
     * @return itself.
     */
    ResidueConstIterator& operator+= (difference_type k);
    
    /**
     * Gets the atom pointed by the current iterator.
     * @return the atom pointer.
     */
    pointer operator-> () const { return &(res->res (pos->second)); }
    
    /**
     * Dereferences the iterator.
     * @return an atom reference.
     */
    reference operator* () const { return res->res (pos->second); }
    
    /**
     * Pre-advances the iterator to the next atom.
     * @return the iterator over the next atom.
     */
    ResidueConstIterator& operator++ ();
    
    /**
     * Post-advances the iterator to the next atom.
     * @param ign ignored parameter.
     * @return the iterator over the current atom.
     */
    ResidueConstIterator operator++ (int ign);
    
    /**
     * Adds the const_iterator to a distance type k.  The result may points
     * to the end of the residue.
     * @param k the distance type.
     * @return a new iterator pointing to itself + k.
     */
    ResidueConstIterator operator+ (difference_type k) const
    {
      return ResidueConstIterator (*this) += k;
    }
    
    /**
     * Tests whether the iterators are equal.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator== (const ResidueConstIterator &right) const
    {
      return res == right.res && pos == right.pos;
    }
    
    /**
     * Tests whether the iterators are different.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator!= (const ResidueConstIterator &right) const
    {
      return !operator== (right);
    }
    
    /**
     * Tests whether the current iterator is less than the right.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator< (const ResidueConstIterator &right) const
    {
      return res == right.res && pos->first < right.pos->first;
    }
    
    /**
     * Casts the iterator to a residue.
     * @return the residue pointed by the iterator.
     */
    operator const AbstractResidue* () const { return res; }
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
    // I/O  -----------------------------------------------------------------
  };
  
  friend ResidueIterator;
  friend ResidueConstIterator;
  typedef ResidueIterator iterator;
  typedef ResidueConstIterator const_iterator;

protected:

  /**
   * The residue id.
   */
  CResId resId;
  
  /**
   * The residue type.
   */
  t_Residue *mType;

  /**
   * The tranfo for local referential.
   */
  CTransfo mTfo;

  /**
   * The associative container between atom types and atom position in
   * the atom container(s).
   */
  ResMap mAtomIndex;

public:

  /**
   * The global counter over the number of residues.
   */
  static int count;

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  AbstractResidue () : mType (0) { ++count; }
  
  /**
   * Initializes the object.
   * @param id the residue id.
   * @param type the residue type.
   */
  AbstractResidue (const CResId &id, t_Residue *type)
    : resId (id), mType (type)
  { ++count; } 
  
  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  AbstractResidue (const AbstractResidue &right)
    : resId (right.resId), mType (right.mType), mTfo (right.mTfo),
      mAtomIndex (right.mAtomIndex)
  { ++count; }


  /**
   * Clones the residue.
   * @return the copy of the object.
   */
  virtual AbstractResidue* clone () const = 0;
  
  /**
   * Destroys the object.
   */
  virtual ~AbstractResidue ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  AbstractResidue& operator= (const AbstractResidue &right);

  /**
   * Assigns the residue id.
   * @param id the new residue id.
   */
  AbstractResidue& operator= (const CResId &id)
  {
    resId = id;
    return *this;
  }

  /**
   * Assigns the transfo.
   * @param tfo the new transfo.
   */
  virtual AbstractResidue& operator= (const CTransfo &tfo) = 0;

  /**
   * Tests if the residues are equals.
   * @param right the right residue.
   * @return the truth value.
   */
  bool operator== (const AbstractResidue &right) const
  { return resId == right.resId && mType == right.mType; }

  /**
   * Tests whether the residues are different.
   * @param right the right residue.
   * @return the truth value.
   */
  bool operator!= (const AbstractResidue &right) const
  { return !operator== (right); }

  /**
   * Gives the order between 2 residues.
   * @param right the residue to compare.
   * @return wheter the left residue is less than the right one.
   */
  bool operator< (const AbstractResidue &right) const
  { return resId < right.resId; }
  
  /**
   * Returns a reference to the atom associated with the type.  The returned
   * atom is not garanteed to stay valid.
   * @param type the atom type.
   * @return the reference to the atom in the local referential.
   */
  virtual CAtom& operator[] (t_Atom *type) = 0;

  /**
   * Returns a const reference to the atom associated with the type.  The
   * returned atom is not garanteed to be valid after operations over the
   * residue.
   * @param type the atom type.
   * @return the reference to the atom in the global or local referential.
   */
  virtual const CAtom& operator[] (const t_Atom *type) const = 0;

  /**
   * Gets the const reference to the residue id.
   * @return the residue id reference.
   */
  operator const CResId& () const { return resId; }

  /**
   * Gets the const reference to the tranfo.
   * @return the transfo reference.
   */
  operator const CTransfo& () const { return mTfo; }

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the iterator begin.
   * @param atomset the atom filter.
   * @return the iterator over the first element.
   */
  virtual iterator begin (AtomSet *atomset = 0) = 0;

  /**
   * Gets the end iterator.
   * @return the iterator past the last element.
   */
  virtual iterator end () = 0;

  /**
   * Gets the begin const_iterator.
   * @param atomset the atom filter.
   * @return the const_iterator over the first element.
   */
  virtual const_iterator begin (AtomSet *atomset = 0) const = 0;

  /**
   * Gets the end const_iterator.
   * @return the const_iterator past the last element.
   */
  virtual const_iterator end () const = 0;

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  virtual iterator find (const t_Atom *k) = 0;

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  virtual const_iterator find (const t_Atom *k) const = 0;

  /**
   * Check if an element with key k exists.
   * @param k the atom type key.
   * @return the presence of an element with key k.
   */
  bool exists (const t_Atom *k) const { return find (k) != end (); }

  /**
   * Gets the residue type.
   * @return the residue type.
   */
  t_Residue* GetType () const { return mType; }

  /**
   * Sets the residue type.
   * @param type the new residue type.
   */
  void setType (t_Residue *type) { mType = type; }

  // METHODS --------------------------------------------------------------

protected:

  /**
   * Gets the atom in local referential at index pos.
   * @param pos the index of the atom.
   * @return the atom in local referential.
   */
  virtual CAtom& place (size_type pos) const = 0;
  
  /**
   * Gets the atom of type t in global referential.
   * @param t the atom type.
   * @return the atom or 0 if it is not found.
   */
  virtual const CAtom* ref (t_Atom *t) const = 0;

  /**
   * Gets the atom reference in global referential.
   * @param pos the index of the atom to get.
   * @return the atom reference at position pos.
   */
  virtual const CAtom& ref (size_type pos) const = 0;

  /**
   * Gets the atom of type t in local referential.
   * @param t the atom type.
   * @return the atom or 0 if it is not found.
   */
  virtual const CAtom* res (t_Atom *t) const = 0;

  /**
   * Gets the atom reference in local referential.
   * @param pos the index of the atom to get.
   * @return the atom reference at position pos.
   */
  virtual const CAtom& res (size_type pos) const = 0;

  /**
   * Adds the hydrogens to the residue.
   */
  void addHydrogens ();

  /**
   * Adds the lone pairs to the residue.
   */
  void addLP ();

public:
  
  /**
   * Gets the number of atoms contained in the residue.
   * @return the size of the residue.
   */
  virtual unsigned int size () const = 0;

  /**
   * Tells if there is no atoms in the residue.
   * @return whether the residue is empty.
   */
  virtual bool empty () const = 0;

  /**
   * Inserts an atom in the residue.  It crushes the existing atom if it
   * exists.
   * @param atom the atom to insert.
   */
  virtual void insert (const CAtom &atom) = 0;

  /**
   * Erases an atom from the residue.
   * @param type the atom type to remove.
   * @return the iterator to the atom that follows the one that was erased.
   */
  virtual iterator erase (t_Atom *type) = 0;

  /**
   * Erases the atom at position pos.
   * @param pos the atom position.
   * @return the iterator to the atom that follows the one that was erased.
   */
  template< class _Iterator >
  iterator erase (const _Iterator pos) { return erase (pos->GetType ()); }
    
  /**
   * Verifies wether all the obligatory atoms are in the residue and creates
   * a new residue where all atoms other than obligatory and optional are
   * removed.  If any test fails, the returned residue has no type.
   */
  void validate ();

  /**
   * Removes all optionnal atom from the residue.
   */
  void removeOptionals ();

  /**
   * Copies the atoms from the right residue.  This function preserves the
   * validity of iterators on the original residue.  Only spatial positions
   * of atoms are modified.
   * @param right the residue to copy.
   */
  virtual void AtomCopy (const AbstractResidue &right) = 0;
  
  /**
   * Creates a new residue with the atoms specified in the variable argument
   * list.  The list must be terminated by a (char*) null pointer.
   * @param at the first atom type.
   * @return the new residue.
   */
  virtual AbstractResidue* select (t_Atom *at ...) const = 0;
  
  /**
   * Applies a tfo over each atoms.  Only the internal transfo is modified.
   * @param theTfo the transfo to apply.
   * @return itself.
   */
  virtual AbstractResidue& Transform (const CTransfo &theTfo) = 0;

  /**
   * Aligns the residue.  Sets the transfo to the identity.
   */
  virtual void Align () = 0;

  // I/O  -----------------------------------------------------------------

  /**
   * Reads the residue from the data input stream.
   * @param ibs the data input stream.
   * @return the consumed data stream.
   */
  virtual iBinstream& read (iBinstream &ibs) = 0;
  
  /**
   * Writes the residue to a data output stream.
   * @param obs the data output stream.
   * @return the output stream.
   */
  virtual oBinstream& write (oBinstream &obs) const = 0;

  /**
   * Reads the residue from the pdb input stream.
   * @param ibs the pdb input stream.
   * @return the consumed pdb stream.
   */
  virtual iPdbstream& read (iPdbstream &ibs) = 0;
  
  /**
   * Writes the residue to a pdb output stream.
   * @param obs the pdb output stream.
   * @return the output stream.
   */
  virtual oPdbstream& write (oPdbstream &obs) const = 0;

  /**
   * Writes the residue to a text output stream.
   * @param obs the text output stream.
   * @return the output stream.
   */
  virtual ostream& write (ostream &os) const = 0;

};



/**
 * Inputs a residue from an input binary stream
 * @param ibs the input binary stream.
 * @param res the residue.
 * @return the used input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, AbstractResidue &res);



/**
 * Outputs the residue to the binary stream.
 * @param obs the output binary stream.
 * @param res the residue.
 * @return the used output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const AbstractResidue &res);



/**
 * Reads the residue from a pdb file.
 * @param ips the input pdb stream.
 * @param res the residue.
 * @return the used input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, AbstractResidue &res);



/**
 * Writes the residue to a pdb format file.
 * @param ops the ouput pdb stream.
 * @param the residue to output.
 * @return the used output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const AbstractResidue &res);



/**
 * Writes the residue in text format.
 * @param ops the ouput stream.
 * @param the residue to output.
 * @return the used output stream.
 */
ostream& operator<< (ostream &ops, const AbstractResidue &res);

#endif
