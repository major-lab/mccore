//                              -*- Mode: C++ -*- 
// ExtendedResidue.h
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.15 $
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


#ifndef _mccore_ExtendedResidue_h_
#define _mccore_ExtendedResidue_h_

#include <iostream>
#include <vector>
#include <map>

#include "Atom.h"
#include "HomogeneousTransfo.h"
#include "Residue.h"

using namespace std;



namespace mccore
{
  class ResId;
  class ResidueType;

  
  /**
   * @short A residue.
   *
   * This residue is a container for Atom.  We define a set of
   * operators and methods that looks like the STL vector:
   * comparators, iterators, insert and erase methods.  Atom traversal
   * using iterators is garantied to follow a partial order defined by
   * the atom types.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ExtendedResidue.h,v 1.15 2005-01-26 20:42:46 larosem Exp $
   */
  class ExtendedResidue : public Residue
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

    /**
     * Gets the atom at a position given by an index.  This is used by
     * the iterators.  It is protected since no atom pointers should be
     * used outside the residue; these pointers are not guaranteed to be valid.
     * @param pos the position of the atom in the atom vector;
     * @return the atom.
     */
    virtual Atom& _get (size_type pos) const;

  public:

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    ExtendedResidue () : Residue (), placed (true) { }

    /**
     * Initializes the residue with a type and id.
     * @param t the residue type.
     * @param i the residue id.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i)
      : Residue (t, i), placed (true)
    { }
    
    /**
     * Initializes the residue with type, atom container and id.
     * @param type the residue type.
     * @param i the residue id.
     * @param vec the atom container.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i, vector< Atom > &vec)
      : Residue (t, i, vec), placed (true)
    { }
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    ExtendedResidue (const ExtendedResidue &other);

    /**
     * Clones the residue.
     * @return the copy of the object.
     */
    virtual Residue* clone () const { return new ExtendedResidue (*this); }
    
    /**
     * Initializes the objet with the other's content.
     * @param other the objet to copy.
     */
    virtual ~ExtendedResidue ();
    
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    ExtendedResidue& operator= (const ExtendedResidue &other);

    // ACCESS ---------------------------------------------------------------
 
    // METHODS -----------------------------------------------------------------

    /**
     * Gets the homogeneous matrix representing the local referential.
     * @param t a homogeneous matrix that will be filled if non null.
     * @return the referential.
     */
    virtual const HomogeneousTransfo getReferential () const { return tfo; }

    /**
     * Sets the homogeneous matrix representing the local referential.
     * @param m the new referential.
     */
    virtual void setReferential (const HomogeneousTransfo& m)
    {
      tfo = m;
//       _displace ();
      placed = false;
    }
    
    /**
     * Inserts an atom in the residue.  It crushes the existing atom if it
     * exists.  
     * @param atom the atom to insert.
     */
    virtual void insert (const Atom &atom);
    
    /**
     * Erases the atom at position pos.
     * @param rit the residue iterator wrapping the atom position.
     * @return the iterator to the atom that follows the one that was erased.
     */
    virtual iterator erase (const iterator& rit);

    /**
     * Removes all of the atoms from the residue.  
     */
    virtual void clear ();

    /**
     * Initializes all the internals of the residue.  It aligns the
     * residue to the origin of the global coordinate and stores the
     * transformation internally.
     */
    virtual void finalize ();

    /**
     * @deprecated
     * DEPRECATED
     * Copies the atom of other into *this without verification.  It
     * is implied that both residues ar of the same type and contain
     * the same atoms.
     *
     * Warning: Both residues must respect the same atom insertion order or else
     * the destination residue will be corrupted!
     *
     * @param other the residue from which to copy atom locations.
     */
    virtual void atomCopy (const Residue& other); 

    // PRIVATE METHODS ------------------------------------------------------

  protected:
    
    /**
     * @internal
     * Fetches the atom specified by its type. If the atom is missing, a new
     * atom of the given type is created and placed at the global origin.
     * Internal method used for ribose building.
     * @param aType The atom type.
     * @return A pointer to the atom in the internal container.
     */
    virtual Atom* _get_or_create (const AtomType *aType);
    
    /**
     * @internal
     * Postprocesses ribose building. Places ribose's atoms back in global referential.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * @param referential Residue's saved referential.
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).    
     */
    virtual void _build_ribose_postprocess (const HomogeneousTransfo& referential,
					    bool build5p, bool build3p);
    
    /**
     * Updates the atom containers so that the residue is placed in space.
     */
    void _place () const;

//     /**
//      * @internal
//      * Updates the atom containers so that the residue is placed in space, if needed.
//      */
//     void _displace () const;

//   public:
    
    // I/O  -----------------------------------------------------------------
    
  };

}

#endif
