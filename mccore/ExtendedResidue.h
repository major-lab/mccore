//                              -*- Mode: C++ -*- 
// ExtendedResidue.h
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.21 $
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
   * *** Warning ***
   *
   * Virtual assignation is optimised by assessing that this class is a
   * leaf in the class hierarchy. If a class extends this one, virtual 
   * assignation may induce slicing. 
   *          
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ExtendedResidue.h,v 1.21 2005-12-09 18:46:29 thibaup Exp $
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
    HomogeneousTransfo referential;

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
    ExtendedResidue ()
      : Residue (), placed (true)
    { 
    }

    /**
     * Initializes the residue with a type and id.
     * @param t the residue type.
     * @param i the residue id.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i)
      : Residue (t, i), placed (true)
    { 
    }
    
    /**
     * Initializes the residue with type, atom container and id.
     * @param type the residue type.
     * @param i the residue id.
     * @param vec the atom container.
     */
    ExtendedResidue (const ResidueType *t, const ResId &i, vector< Atom > &vec);
    
    /**
     * Initializes this object's content with another's.
     * @param exres the other object from which to copy content.
     */
    ExtendedResidue (const ExtendedResidue& exres);

    /**
     * Initializes this object's content with another's by resolving
     * its polymorphic type.
     * @param res the polymorphic object from which to copy content.
     */
    ExtendedResidue (const Residue& res);

    /**
     * Clones the residue.
     * @return the copy of the object.
     */
    virtual Residue* clone () const 
    { 
      return new ExtendedResidue (*this); 
    }
    
    /**
     * Initializes the objet with the other's content.
     * @param other the objet to copy.
     */
    virtual ~ExtendedResidue ();

    // VIRTUAL ASSIGNATION --------------------------------------------------

    /**
     * Assigns this object's content with another's by resolving
     * its polymorphic type.
     * @param res the polymorphic object from which to copy content.
     * @return *this;
     */
    virtual Residue& assign (const Residue& res)
    {
      return this->assignNV (res);
    }

    /**
     * Assigns this object's content with another's by resolving
     * its polymorphic type (non-virtual version). 
     * @param res the polymorphic object from which to copy content.
     */
    ExtendedResidue& assignNV (const Residue& res);
    
  protected:

    /**
     * @internal
     * Assigns this object's content with another's.
     * @param res the other object from which to copy content.
     */
    void _assign (const ExtendedResidue& res);

  public:

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns this object's content with another's. Kept for compatibility reason.
     * @param exres the other object from which to copy content.
     * @return itself.
     */
    ExtendedResidue& operator= (const ExtendedResidue& exres);

    /**
     * Assigns this object's content with another's by resolving its polymorphic 
     * type. Kept for compatibility reason.
     * @param res the polymorphic object from which to copy content.
     * @return itself.
     */
    ExtendedResidue& operator= (const Residue& res)
    {
      return this->assignNV (res);
    }

    // ACCESS ---------------------------------------------------------------
 
    // METHODS -----------------------------------------------------------------

    /**
     * Gets the homogeneous matrix representing the local referential.
     * @param t a homogeneous matrix that will be filled if non null.
     * @return the referential.
     */
    virtual const HomogeneousTransfo getReferential () const
    { 
      return this->referential; 
    }

    /**
     * Sets the homogeneous matrix representing the local referential.
     * @param m the new referential.
     */
    virtual void setReferential (const HomogeneousTransfo& m);
    
    /**
     * Applies a tfo over each atoms. The new referential is updated.
     * @param m the transfo to apply.
     */
    virtual void transform (const HomogeneousTransfo& m);

    /**
     * Computes global atoms coordinates in the current referential.
     */
    virtual void place () const
    {
      this->_place ();
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

    // INTERNAL METHODS ------------------------------------------------------

  protected:
    
    /**
     * @internal
     * Gets the atom at a position given by an index.  This is used by
     * the iterators.  It is protected since no atom pointers should be
     * used outside the residue; these pointers are not guaranteed to be valid.
     * @param pos the position of the atom in the atom vector;
     * @return the atom.
     */
    virtual Atom& _get (size_type pos) const;

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

  public:
    
    // I/O  -----------------------------------------------------------------
    
    /**
     * Displays debugging information to the output stream.
     * param os the output stream.
     * @return the written output stream.
     */
    virtual ostream& display (ostream &os) const;

  protected:

    /**
     * @internal
     * Displays debugging information to the output stream (class specific).
     * param os the output stream.
     * @return the written output stream.
     */
    ostream& _display (ostream &os) const;

  public:

  };

}

#endif
