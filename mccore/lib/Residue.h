//                              -*- Mode: C++ -*- 
// Residue.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// Last Modified By : Martin Larose
// Last Modified On : Mon Nov  5 11:39:15 2001
// Update Count     : 3
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


#ifndef _Residue_h_
#define _Residue_h_

#include <vector.h>
#include <map.h>

#include "AbstractResidue.h"
#include "CAtom.h"

class iBinstream;
class oBinstream;
class iPdbstream;
class oPdbstream;
class t_Atom;
class t_Residue;



/**
 * @short Residue implementation that uses atom pointers.
 *
 * The residue is a container object of CAtom pointers.  It follows exactly
 * the CResidue class.  The atoms are positioned in a global referential
 * space and are only placed in local referential space when the first
 * residue iterator is dereferenced.  It is necessary to manipulates residue
 * iterator instead of atom pointers since the atom address is unstable when
 * it is placed.  Every methods that modifies the contents of the atom array
 * are functional, i.e. a new residue is created, modified and returned.
 * This way existing iterators over the residue are not dandling.  Atom
 * traversal using iterators is garantied to follow a partial order defined
 * by the atom types.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class Residue : public AbstractResidue
{

public:

//    typedef vector< CAtom* >::size_type size_type;
  typedef map< const t_Atom*, size_type > ResMap;

private:
  
  /**
   * The atom container in global referential.
   */
  vector< CAtom* > mAtomRef;

  /**
   * The associative container between atom types and atom position in
   * mAtomRef and mAtomRes.
   */
  ResMap mAtomIndex;

  /**
   * The atom container in local referential.
   */

  mutable vector< CAtom* > mAtomRes;

  /**
   * The flag indicating whether the atoms are placed.
   */
  mutable bool isPlaced;

  /**
   * The flag indicating whether the transfo is the identity.
   */
  bool isIdentity;

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the residue.  Increases the global count.
   */
  Residue () : AbstractResidue (), isPlaced (false), isIdentity (true)
  { }

  /**
   * Initializes the residue with type, atom container and id.
   * @param type the residue type.
   * @param vec the atom container.
   * @param nId the residue id.
   */
  Residue (t_Residue *type, vector< CAtom > &vec, const CResId &nId);

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  Residue (const Residue &right);

  /**
   * Clones the residue.
   * @return a copy of the residue.
   */
  virtual AbstractResidue* clone () const { return new Residue (*this); }
  
  /**
   * Destroys the object.
   */
  virtual ~Residue ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  Residue& operator= (const Residue &right);

  /**
   * Assigns the transfo.  Only the internal transfo is modified.
   * @param tfo the new transfo.
   */
  virtual AbstractResidue& operator= (const CTransfo &tfo);

  /**
   * Returns a reference to the atom associated with the type.  The returned
   * atom is not garanteed to stay valid.
   * @param type the atom type.
   * @return the reference to the atom in the local referential.
   */
  virtual CAtom& operator[] (t_Atom *type);

  /**
   * Returns a const pointer to the atom associated with the type.  The
   * returned atom is not garanteed to be valid after operations over the
   * residue.
   * @param type the atom type.
   * @return the const pointer to the atom in the global or local referential.
   */
  virtual const CAtom& operator[] (const t_Atom *type) const;

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the iterator begin.
   * @return the iterator over the first element.
   */
  virtual iterator begin (AtomSet *atomset = 0)
  { return iterator (this, 0, atomset); }

  /**
   * Gets the end iterator.
   * @return the iterator past the last element.
   */
  virtual iterator end ()
  { return iterator (this, mAtomRef.size ()); }

  /**
   * Gets the begin const_iterator.
   * @return the const_iterator over the first element.
   */
  virtual const_iterator begin (AtomSet *atomset = 0) const
  { return const_iterator (this, 0, atomset); }

  /**
   * Gets the end const_iterator.
   * @return the const_iterator past the last element.
   */
  virtual const_iterator end () const
  { return const_iterator (this, mAtomRef.size ()); }

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  virtual iterator find (const t_Atom *k);

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  virtual const_iterator find (const t_Atom *k) const;

  // METHODS --------------------------------------------------------------

protected:

  /**
   * Initializes the residue when it is created.
   */
  void init ();

  /**
   * Gets the atom in local referential at index pos.  The atoms are
   * tranformed on need.
   * @param pos the index of the atom.
   * @return the atom in local referential.
   */
  virtual CAtom& place (size_type pos) const
  {
    if (! isPlaced)
      placeIt ();
    return *mAtomRes[pos];
  }

  /**
   * Transforms and returns the atom in local referential.
   */
  void placeIt () const;

  /**
   * Gets the atom of type t in global referential.
   * @param t the atom type.
   * @return the atom or 0 if it is not found.
   */
  virtual const CAtom* ref (t_Atom *t) const;

  /**
   * Gets the atom reference in global referential.
   * @param pos the index of the atom to get.
   * @return the atom pointer at position pos.
   */
  virtual const CAtom& ref (size_type pos) const { return *mAtomRef[pos]; }

  /**
   * Gets the atom of type t in global referential if the tranfo is the
   * identity, the placed atom otherwise.
   * @param t the atom type.
   * @return the atom or 0 if it is not found.
   */
  virtual const CAtom* res (t_Atom *t) const;

  /**
   * Gets the atom reference in the sorted position pos.
   * @param pos the index of the atom to get.
   * @return the atom at position pos.
   */
  virtual const CAtom& res (size_type pos) const
  { return isIdentity ? *mAtomRef[pos] : place (pos); }

public:

  /**
   * Gets the number of atoms contained in the residue.
   * @return the size of the residue.
   */
  virtual unsigned int size () const { return mAtomRef.size (); }

  /**
   * Tells if there is no atoms in the residue.
   * @return whether the residue is empty.
   */
  virtual bool empty () const { return mAtomRef.empty (); }

  /**
   * Inserts an atom in the residue.  It crushes the existing atom if it
   * exists.  The index and the local referential containers are adjusted.
   * @param atom the atom to insert.
   */
  virtual void insert (const CAtom &atom);

  /**
   * Erases an atom from the residue, adjusting all containers and maps.
   * @param type the atom type to remove.
   */
  virtual iterator erase (t_Atom *type);
  
  /**
   * Erases a range of atoms from the residue, adjusting all containers and
   * maps.
   * @param start the iterator of the first atom to erase.
   * @param finish the iterator of the last atom to erase.
   */
  template<class _InputIterator>
  iterator
  erase (const _InputIterator &start, const _InputIterator &finish)
  {
    vector< CAtom* >::const_iterator cit;
    vector< CAtom* >::iterator it;
    size_type index;
    _InputIterator ciit;
    
    for (ciit = start; ciit != finish; ++ciit)
      {
	ResMap::iterator it = mAtomIndex.find (*ciit);
	
	if (it != mAtomIndex.end ())
	  {
	    delete mAtomRef[it->second];
	    next = mAtomRef.erase (mAtomRef.begin () + it->second);
	    delete mAtomRes.back ();
	    mAtomRes.pop_back ();
	  }
      }
    mAtomIndex.clear ();
    for (cit = mAtomRef.begin (), index = 0;
	 cit != mAtomRef.end ();
	 ++cit, ++index)
      mAtomIndex[(*cit)->GetType ()] = index;
    mAtomRes.reserve (index);
    isPlaced = false;
    if (next != mAtomRef.end ())
      return find ((*next)->GetType ());
    else
      return end ();
  }
  
  /**
   * Copies the atoms from the right residue.  This function preserves the
   * validity of iterators on the original residue.  Only spatial positions
   * of atoms are modified.
   * @param right the residue to copy.
   */
  virtual void AtomCopy (const AbstractResidue &right);
  
  /**
   * Creates a new residue with the atoms specified in the variable argument
   * list.  The list must be terminated by a (char*) null pointer.
   * @param at the first atom type.
   * @return the new residue.
   */
  virtual AbstractResidue* select (t_Atom *at ...) const;
  
  /**
   * Applies a tfo over each atoms.  Only the internal transfo is modified.
   * @param theTfo the transfo to apply.
   * @return itself.
   */
  virtual AbstractResidue& Transform (const CTransfo &theTfo);

  /**
   * Aligns the residue.  Sets the transfo to the identity.
   */
  virtual void Align ();

  // I/O  -----------------------------------------------------------------

  /**
   * Reads the residue from the data input stream.
   * @param ibs the data input stream.
   * @return the consumed data stream.
   */
  virtual iBinstream& read (iBinstream &ibs);
  
  /**
   * Writes the residue to a data output stream.
   * @param obs the data output stream.
   * @return the output stream.
   */
  virtual oBinstream& write (oBinstream &obs) const;

  /**
   * Reads the residue from the pdb input stream.
   * @param ibs the pdb input stream.
   * @return the consumed pdb stream.
   */
  virtual iPdbstream& read (iPdbstream &ibs);
  
  /**
   * Writes the residue to a pdb output stream.
   * @param obs the pdb output stream.
   * @return the output stream.
   */
  virtual oPdbstream& write (oPdbstream &obs) const;

  /**
   * Writes the residue to a text output stream.
   * @param obs the text output stream.
   * @return the output stream.
   */
  virtual ostream& write (ostream &os) const;

};

#endif
