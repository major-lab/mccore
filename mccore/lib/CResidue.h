//                              -*- Mode: C++ -*- 
// CResidue.h
// Copyright © 2000-02 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : Thu Sep 28 16:59:32 2000
// Last Modified By : Patrick Gendron
// Last Modified On : Fri Mar 15 14:11:33 2002
// Update Count     : 25
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


#ifndef _CResidue_h_
#define _CResidue_h_

#include <vector.h>

#include "AbstractResidue.h"
#include "CAtom.h"

class t_Atom;
class t_Residue;
class oPdbstream;
class iBinstream;
class oBinstream;
class ostream;



/**
 * @short Residue implementation.
 *
 * The residues contains an array of atoms (CAtoms).  The atoms are
 * positioned in a global referential space and are only placed in local
 * referential space when the first residue iterator is dereferenced.  It is
 * necessary to manipulates residue iterator instead of atom pointers since
 * the atom address is unstable when it is placed.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CResidue : public AbstractResidue
{
  
protected:
  
  typedef vector< CAtom >::size_type size_type;
  
private:
  
  /**
   * The atom container in global referential.
   */
  vector< CAtom > mAtomRef;

  /**
   * The atom container in local referential.
   */

  mutable vector< CAtom > mAtomRes;

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
  CResidue () : AbstractResidue (), isPlaced (false), isIdentity (true)
  { } 

  /**
   * Initializes the residue with type, atom container and id.
   * @param type the residue type.
   * @param vec the atom container.
   * @param nId the residue id.
   */
  CResidue (t_Residue *type, const vector< CAtom > &vec, const CResId &nId);

  /**
   * Initializes the residue with the right's content.
   * @param right the object to copy.
   */
  CResidue (const CResidue &right);

  /**
   * Clones the residue.
   * @return the copy of the object.
   */
  virtual AbstractResidue* clone () const { return new CResidue (*this); }
  
  /**
   * Destroys the object.
   */
  virtual ~CResidue () { }


  /**
   * Creates a residue containing the base atom coordinates of a
   * standard residue as defined by G.Parkinson et al., ACTA CRYST.D
   * (1996) v. 52, 57-64.
   */
  virtual void setIdeal ();


  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  CResidue& operator= (const CResidue &right);

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
   * Returns a const reference to the atom associated with the type.  The
   * returned atom is not garanteed to be valid after operations over the
   * residue.
   * @param type the atom type.
   * @return the reference to the atom in the global or local referential.
   */
  virtual const CAtom& operator[] (const t_Atom *type) const;

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the iterator begin.
   * @return the iterator over the first element.
   */
  virtual iterator begin (AtomSet *atomset = 0)
  { return iterator (this, mAtomIndex.begin (), atomset); }

  /**
   * Gets the end iterator.
   * @return the iterator past the last element.
   */
  virtual iterator end ()
  { return iterator (this, mAtomIndex.end ()); }

  /**
   * Gets the begin const_iterator.
   * @return the const_iterator over the first element.
   */
  const_iterator begin (AtomSet *atomset = 0) const
  { return const_iterator (this, mAtomIndex.begin (), atomset); }

  /**
   * Gets the end const_iterator.
   * @return the const_iterator past the last element.
   */
  const_iterator end () const
  { return const_iterator (this, mAtomIndex.end ()); }

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
    return mAtomRes[pos];
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
   * @return the atom reference at position pos.
   */
  virtual const CAtom& ref (size_type pos) const { return mAtomRef[pos]; }

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
   * @return the atom reference at position pos.
   */
  virtual const CAtom& res (size_type pos) const
  { return isIdentity ? mAtomRef[pos] : place (pos); }

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
  
protected:
  /**
   * Inserts an atom in the residue.  It crushes the existing atom if it
   * exists.  The index and the local referential containers are adjusted.
   * @param atom the atom to insert.
   */
  virtual void insert_local (const CAtom &atom);

public:
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
  void erase (const _InputIterator &start, const _InputIterator &finish)
  {
    vector< CAtom >::const_iterator cit;
    size_type index;
    _InputIterator ciit;
    
    for (ciit = start; ciit != finish; ++ciit)
      {
	vector< CAtom >::iterator it = ::find (mAtomRef.begin (),
					       mAtomRef.end (), *ciit);
	
	if (it != mAtomRef.end ())
	  mAtomRef.erase (it);
      }
    mAtomIndex.clear ();
    mAtomRes.clear ();
    for (cit = mAtomRef.begin (), index = 0;
	 cit != mAtomRef.end ();
	 ++cit, ++index)
      mAtomIndex[cit->GetType ()] = index;
    mAtomRes.reserve (index);
    mAtomRes.resize (index);
    isPlaced = false;
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
  virtual CResidue& Transform (const CTransfo &theTfo);

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


/**
 * Inputs a residue from an input binary stream
 * @param ibs the input binary stream.
 * @param res the residue.
 * @return the used input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, CResidue &res);



/**
 * Outputs the residue to the binary stream.
 * @param obs the output binary stream.
 * @param res the residue.
 * @return the used output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const CResidue &res);



/**
 * Reads the residue from a pdb file.
 * @param ips the input pdb stream.
 * @param res the residue.
 * @return the used input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, CResidue &res);



/**
 * Writes the residue to a pdb format file.
 * @param ops the ouput pdb stream.
 * @param the residue to output.
 * @return the used output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const CResidue &res);



/**
 * Writes the residue in text format.
 * @param ops the ouput stream.
 * @param the residue to output.
 * @return the used output stream.
 */
ostream& operator<< (ostream &ops, const CResidue &res);

#endif
