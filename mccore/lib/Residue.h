//                              -*- Mode: C++ -*- 
// Residue.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar 14 16:44:35 2003
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


#ifndef _Residue_h_
#define _Residue_h_

#include <iostream>
#include <vector>
#include <map>

#include "ResId.h"
#include "Atom.h"
#include "AtomType.h"
#include "AtomSet.h"
#include "ResidueType.h"
#include "HomogeneousTransfo.h"


using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  class PropertyType;

  /**
   * @short A basic residue.
   *
   * This residue is a container for Atom.  We define a set of
   * operators and methods that looks like the STL vector:
   * comparators, iterators, insert and erase methods.  Atom traversal
   * using iterators is garantied to follow a partial order defined by
   * the atom types.
   *
   * @author Patrick Gendron <gendrop@iro.umontreal.ca>
   * @version $Id: Residue.h,v 1.14 2003-10-28 16:11:44 gendrop Exp $
   */
  class Residue
  {
    friend class ExtendedResidue;

  public:
    
    /**
     * The size type of the abstract residue container.
     */
    typedef unsigned int size_type;
    
  protected:

    /**
     * Definition of the sorted mapping.
     */
    typedef map< const AtomType*, size_type, AtomType::less > AtomMap;
    
    /**
     * The residue type.
     */
    const ResidueType* type;

    /**
     * The residue id.
     */
    ResId resId;
  
    /**
     * The container for atoms expressed in the global referential.
     */
    mutable vector< Atom* > atomGlobal;

    /**
     * The associative array between atom types and atom container positions.
     */
    AtomMap atomIndex;  

    
  public:

    class ResidueIterator;
    friend class ResidueIterator;
    typedef ResidueIterator iterator;

    class ResidueConstIterator;
    friend class ResidueConstIterator;
    typedef ResidueConstIterator const_iterator;

    
  public:
    
    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Residue ();
    
    /**
     * Initializes the object.
     * @param t the residue type.
     * @param id the residue id.
     */
    Residue (const ResidueType *t, const ResId &i);
    
    /**
     * Initializes the residue with type, atom container and id.
     * @param type the residue type.
     * @param i the residue id.
     * @param vec the atom container.
     */
    Residue (const ResidueType *t, const ResId &i, const vector< Atom > &vec);

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Residue (const Residue &other);

    /**
     * Clones the residue.
     * @return the copy of the object.
     */
    virtual Residue* clone () const; 

    /**
     * Destroys the object.
     */
    virtual ~Residue ();

    /**
     * Creates a residue containing idealized coordinates of a
     * standard residue as defined by G.Parkinson et al., ACTA CRYST.D
     * (1996) v. 52, 57-64.
     * @param h_lp flag for hydrogens and lone pairs addition.
     * @return true if the operation was successful.
     */
    virtual bool setIdeal (bool h_lp = true);

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual Residue& operator= (const Residue &other);
    
    /**
     * Indicates whether some other residue is "equal to" this one.
     * @param other the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    virtual bool operator== (const Residue &other) const;
    
    /**
     * Indicates whether some other residue is "not equal to" this one.
     * @param other the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    virtual bool operator!= (const Residue &other) const;

    /**
     * Imposes a total ordering on the Atom objects.  They are sorted
     * by AtomType.
     * @param other the residue to compare.
     * @return true if this residue is less than the other.
     */
    virtual bool operator< (const Residue &other) const;


    // ACCESS ------------------------------------------------------------------

    /**
     * Gets the residue id.
     * @return the residue id.
     */
    const ResId& getResId () const;
  
    /**
     * Sets the residue id.
     * @param id the new residue id.
     */
    void setResId (const ResId& id);
  
    /**
     * Gets the residue type.
     * @return the residue type.
     */
    const ResidueType* getType() const;
    
    /**
     * Sets the residue type.
     * @param type the new residue type.
     */
    void setType (const ResidueType* t);
        
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
     * @param t a homogeneous matrix that will be filled and that must not be null.
     * @return the referential.
     */
    virtual const HomogeneousTransfo getReferential () const; 

    /**
     * Sets the homogeneous matrix representing the local referential.
     * @param m the new referential.
     */
    virtual void setReferential (const HomogeneousTransfo& m);
  
    /**
     * Applies a tfo over each atoms.
     * @param aTransfo the transfo to apply.
     * @return itself.
     */
    virtual void transform (const HomogeneousTransfo &aTransfo) {
      setReferential(aTransfo * getReferential());
    }

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
     * @return the number of atoms.
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

    /**
     * Verifies wether all the obligatory atoms are in the residue and
     * keeps only obligatory and optional atoms, stripping all
     * others.  If any test fails, the type is invalidated.
     */
    virtual void validate ();

    /**
     * Removes all optional atoms.
     */
    virtual void removeOptionals ();
    
    /**
     * Adds the hydrogens to the residue.  Hydrogens from the
     * sidechain will always be placed since their position is quite
     * stable and some PDB files have been found to contain weird
     * deviation in their positions.  Backbone hydrogens will only be
     * placed if they do not already exist.
     */
    virtual void addHydrogens ();

    /**
     * Adds the lone pairs to the residue.
     */
    virtual void addLonePairs ();
   
    /**
     * Determines the pucker mode of the NucleicAcid backbone.
     */
    virtual const PropertyType* getPucker ();

    /**
     * Determines the glycosidic angle classification.
     */
    virtual const PropertyType* getGlycosyl ();
    
    /**
     *  Initializes all the internals of the residue.  It aligns the
     *  residue to the origin of the global coordinate and stores the
     *  transformation internally.  
     */
    virtual void finalize ();

    /**
     * Computes the distance between two residues by first aligning
     * the residues and computing the RMSD on the backbone atoms.  For
     * more details, see a discussion of the metric used in
     * P. Gendron, S. Lemieuxs and F. Major (2001) Quantitative
     * analysis of nucleic acid three-dimensional structures,
     * J. Mol. Biol. 308(5):919-936 
     * @param m the other residue.
     * @return the computed distance.
     */
    float distance (const Residue &r) const;

    /**
     * Copies the atom of other into *this without verification.  It
     * is implied that both residues ar of the same type and contain
     * the same atoms.  
     * @param other the residue from which to copy atom locations.
     */
    virtual void atomCopy (const Residue& other); 

  protected:

    // PRIVATE METHODS ------------------------------------------------------

    /**
     * Gets the atom at a position given by an index.  This is used by
     * the iterators.  It is private since no atom pointers should be
     * used outside the residue; these pointers are not guaranteed to be valid.
     * @param pos the position of the atom in the atom vector;
     * @return the atom.
     */
    virtual Atom& get (size_type pos) const;

    /**
     * Gets the atom of given type.  It is private since no atom
     * pointers should be used outside the residue; these pointers are
     * not guaranteed to be valid.
     * @param type the atom type.
     * @return the atom.
     */
    virtual Atom* get (const AtomType* type) const;

  public:

    // I/O  --------------------------------------------------------------------

    /**
     * Ouputs the residue to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
    
    /**
     * Inputs the residue from the stream. All residues binary I/O
     * should be compatible for all inherited classes.
     * @param ibs the input stream.
     * @return the used output stream.
     */
    virtual iBinstream& input (iBinstream &ibs);

    /**
     * Ouputs the residue to the stream.  All residues binary I/O
     * should be compatible for all inherited classes.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;


  protected:
    
    // ITERATORS ---------------------------------------------------------------

    /**
     * @short Iterators for residues.
     *
     * The iterator provides a generic way to access atoms in different
     * residue component types.  It looks like the forward iterator from STL.
     * It requires that the residue defines a size method and a bracket
     * ([Residue::size_type]) accessor.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class ResidueIterator
    {
      friend class Residue::ResidueConstIterator;
      
    public:
      
      typedef random_access_iterator_tag iterator_category;
      typedef Atom value_type;
      typedef ptrdiff_t difference_type;
      typedef Atom* pointer;
      typedef Atom& reference;
      
    private:
      
      /**
       * The pointer over the residue.
       */
      Residue *res;
      
      /**
       * The position of the iterator.  It is given by the ResMap iterator.
       */
      AtomMap::iterator pos;
      
      /**
       * The filter function over the atom types.  Will be destroyed here.
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
      ResidueIterator (Residue *r, AtomMap::iterator p, AtomSet *f = 0);
      
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
      pointer operator-> () const { return &(res->get (pos->second)); }
      
      /**
       * Dereferences the iterator.
       * @return an atom reference.
       */
      reference operator* () const { return res->get (pos->second); }
  
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
	return (res < right.res ||
		res == right.res && pos->first < right.pos->first);
      }
      
      /**
       * Casts the iterator to a residue.
       * @return the residue pointed by the iterator.
       */
      operator Residue* () { return res; }
    };


    /**
     * @short Const iterators for residues.
     *
     * The const_iterator provides a generic way to access atoms in different
     * residue component types.  It looks like the forward iterator from STL.
     * It requires that the residue defines a size method and a bracket
     * ([Residue::size_type]) accessor.
     *
     * @author Martin Larose <larosem@iro.umontreal.ca>
     */
    class ResidueConstIterator
    {
      friend class Residue::ResidueIterator;

    public:

      typedef random_access_iterator_tag iterator_category;
      typedef const Atom value_type;
      typedef ptrdiff_t difference_type;
      typedef const Atom* pointer;
      typedef const Atom& reference;

    private:
    
      /**
       * The pointer over the residue.
       */
      const Residue *res;
    
      /**
       * The residue index where the const_residue_iterator points to.
       */
      AtomMap::const_iterator pos;
    
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
      ResidueConstIterator (const Residue *r,
			    AtomMap::const_iterator p,
			    AtomSet *f = 0);

      /**
       * Initializes the ResidueConstIterator with the right's contents.
       * @param right the ResidueConstIterator to copy.
       */
      ResidueConstIterator (const ResidueConstIterator &right);
    
    
      /**
       * Initializes the ResidueConstIterator with the right's contents. 
       * Adding constness is allowed.
       * @param right the ResidueConstIterator to copy.
       */
      ResidueConstIterator (const ResidueIterator &right);

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
       * Assigns the ResidueConstIterator with the right's content.
       * Adding constness is allowed.
       * @param right the object to copy.
       * @return itself.
       */
      ResidueConstIterator& operator= (const ResidueIterator &right);
    
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
      pointer operator-> () const { return &(res->get (pos->second)); }
    
      /**
       * Dereferences the iterator.
       * @return an atom reference.
       */
      reference operator* () const { return res->get (pos->second); }
    
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
	return (res < right.res ||
		res == right.res && pos->first < right.pos->first);
      }
    
      /**
       * Casts the iterator to a residue.
       * @return the residue pointed by the iterator.
       */
      operator const Residue* () const { return res; }
    
    };
    
  };

  // NON-MEMBER FUNCTIONS ------------------------------------------------------

  /**
   * Ouputs the residue to the stream.
   * @param os the output stream.
   * @param r the residue.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const Residue &r);

  /**
   * Ouputs the residue to the stream.
   * @param os the output stream.
   * @param r the residue.
   * @return the used output stream.
   */
  //ostream& operator<< (ostream &os, const Residue *r);
  
  /**
   * Inputs the residue from the binary stream.
   * @param ibs the input binary stream.
   * @param res the residue to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &ibs, Residue &res);

  
  /**
   * Outputs the Residue to the binary stream.
   * @param obs the output binary stream.
   * @param res the Residue.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &obs, const Residue &res);
  
}

#endif
