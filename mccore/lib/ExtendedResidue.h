//                              -*- Mode: C++ -*- 
// ExtendedResidue.h
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.1 $
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


#ifndef _ExtendedResidue_h_
#define _ExtendedResidue_h_

#include <iostream>
#include <vector>
#include <map>

#include "Residue.h"
#include "ResId.h"
#include "Atom.h"
#include "HomogeneousTransfo.h"
#include "ResidueType.h"

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  /**
   * @short A residue.
   *
   * This residue is a container for Atom.  We define a set of
   * operators and methods that looks like the STL vector:
   * comparators, iterators, insert and erase methods.  Atom traversal
   * using iterators is garantied to follow a partial order defined by
   * the atom types.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: ExtendedResidue.h,v 1.1 2003-06-03 14:20:59 gendrop Exp $
   */
  class ExtendedResidue : public virtual Residue
  {
    /**
     * The container for atoms expressed in the local referential.
     * atomLocal is kept null until we need to transform the residue.
     * This way, most of the time a residue will be quite "slim".
     */
    vector< Atom* > atomLocal;

    /**
     * The transfo that express the location of the local referential
     * in terms of global referential coordinates.
     */
    HomogeneousTransfo tfo;

    /**
     * Indicates if the residue is placed in space, i.e. if atomGlobal
     * contains atoms from atomLocal transformed according to the tfo.
     */
    mutable bool placed;

  public:

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    ExtendedResidue ();

    /**
     * Initializes the residue with a type and id.
     * @param t the residue type.
     * @param i the residue id.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i); 
    
    /**
     * Initializes the residue with type, atom container and id.
     * @param type the residue type.
     * @param i the residue id.
     * @param vec the atom container.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i, vector< Atom > &vec);
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    ExtendedResidue (const ExtendedResidue &other);

    /**
     * Clones the residue.
     * @return the copy of the object.
     */
    virtual Residue* clone () const; 
    
    /**
     * Initializes the objet with the other's content.
     * @param other the objet to copy.
     */
    ~ExtendedResidue ();
    
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual ExtendedResidue& operator= (const ExtendedResidue &other);

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the iterator begin.
     * @param atomset the atom filter.
     * @return the iterator over the first element.
     */
    virtual iterator begin (AtomSet *atomset = 0);
    
    /**
     * Gets the end iterator.
     * @return the iterator past the last element.
     */
    virtual iterator end ();

    /**
     * Gets the const_iterator begin.
     * @param atomset the atom filter.
     * @return the const_iterator over the first element.
     */
    virtual const_iterator begin (AtomSet *atomset = 0) const;
    
    /**
     * Gets the end const_iterator.
     * @return the const_iterator past the last element.
     */
    virtual const_iterator end () const;

    /**
     * Finds an element whose key is k.
     * @param k the atom type key.
     * @return the iterator to the element or end () if it is not found.
     */
    virtual iterator find (const AtomType *k);
    
    /**
     * Finds an element whose key is k.
     * @param k the atom type key.
     * @return the iterator to the element or end () if it is not found.
     */
    virtual const_iterator find (const AtomType *k) const;
    
    /**
     * Check if an element with key k exists in this residue.
     * @param k the atom type key.
     * @return the presence of an element with key k.
     */
    virtual bool contains (const AtomType *k) const;
    
    // METHODS -----------------------------------------------------------------

    /**
     * Gets the homogeneous matrix representing the local referential.
     * @param t a homogeneous matrix that will be filled if non null.
     * @return the referential.
     */
    virtual const HomogeneousTransfo& getReferential (HomogeneousTransfo *t = 0) const; 

    /**
     * Sets the homogeneous matrix representing the local referential.
     * @param m the new referential.
     */
    void setReferential (const HomogeneousTransfo& m);
    
    /**
     * Applies a tfo over each atoms.  Only the internal transfo is modified.
     * @param aTransfo the transfo to apply.
     * @return itself.
     */
    const ExtendedResidue& transform (const HomogeneousTransfo &aTransfo);
    
    /**
     * Inserts an atom in the residue.  It crushes the existing atom if it
     * exists.  
     * @param atom the atom to insert.
     */
    virtual void insert (const Atom &atom);

    /**
     * Erases an atom from the residue.
     * @param type the atom type to remove.
     * @return the iterator to the atom that follows the one that was erased.
     */
    virtual iterator erase (const AtomType *type);
    
    /**
     * Erases the atom at position pos.
     * @param pos the atom position.
     * @return the iterator to the atom that follows the one that was erased.
     */
    iterator erase (const iterator pos);

    /**
     * Erases the atom at position pos.
     * @param pos the atom position.
     * @return the iterator to the atom that follows the one that was erased.
     */
    iterator erase (const const_iterator pos);

    /**
     * Returns the number of atoms in the residue.
     * @return the number of residues.
     */
    virtual int size () const;
  
    /**
     * Tells if there is no atoms in the residue.
     * @return whether the residue is empty.
     */
    virtual bool empty () const;

    /**
     * Removes all of the atoms from the residue.  
     */
    virtual void clear();


    // PRIVATE METHODS ------------------------------------------------------

    /**
     *  Initializes all the internals of the residue.  It aligns the
     *  residue to the origin of the global coordinate and stores the
     *  transformation internally.  
     */
    void finalize ();

  protected:
    
    /**
     * Gets the atom at a position given by an index.  This is used by the iterators.
     * @param pos the position of the atom in the atom vector;
     * @return the atom.
     */
    virtual Atom& get (size_type pos) const;
    
    /**
     * Gets the atom of given type.  
     * @param type the atom type.
     * @return the atom.
     */
    virtual Atom* get (const AtomType* type) const;
    
    /**
     *  Updates the atom containers so that the residue is placed in space.
     */
    void place () const;
    
    void displace () const;

    bool isPlaced () const { return (placed == true); }


  public:
    
    // I/O  -----------------------------------------------------------------
    
    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
    
    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    //    oBinstream& output (oBinstream &obs) const;

  };

  
//   /**
//    * Ouputs the residue to the stream.
//    * @param os the output stream.
//    * @param as the atomset.
//    * @return the used output stream.
//    */
//   ostream& operator<< (ostream &os, const ExtendedResidue &r);
  
//   /**
//    * Inputs the atom from the binary stream.
//    * @param ibs the input binary stream.
//    * @param atom the atom to fill.
//    * @return the input binary stream used.
//    */
//   iBinstream& operator>> (iBinstream &ibs, Atom &atom);


//   /**
//    * Outputs the atom to the binary stream.
//    * @param obs the output binary stream.
//    * @param atom the atom.
//    * @return the output binary stream used.
//    */
//   oBinstream& operator<< (oBinstream &obs, const ExtendedResidue &atom);
 

}

#endif
