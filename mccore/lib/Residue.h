//                              -*- Mode: C++ -*- 
// Residue.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar 14 16:44:35 2003
// $Revision: 1.20 $
// $Id: Residue.h,v 1.20 2004-06-25 14:46:47 thibaup Exp $
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


namespace mccore
{

  class PropertyType;
  class ResidueFactoryMethod;
  class CException;
  class iBinstream;
  class iPdbstream;
  class oBinstream;
  class oPdbstream;

  
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
   * @version $Id: Residue.h,v 1.20 2004-06-25 14:46:47 thibaup Exp $
   */
  class Residue
  {
    friend class ExtendedResidue;

  public:
    
    /**
     * The size type of the abstract residue container.
     */
    typedef unsigned int size_type;
    
    /**
     * Definition of the sorted mapping.
     */
    typedef map< const AtomType*, size_type, AtomType::less > AtomMap;
    
  protected:

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

    /**
     * Ribose's atom aliases used in the theoretical building method.
     */
    Atom *rib_C1p, *rib_C2p, *rib_C3p, *rib_C4p, *rib_C5p, *rib_O2p, *rib_O3p, *rib_O4p, *rib_O5p, *rib_P;

    /**
     * Flag asserting ribose's atoms pointer validity. Any methods modifying the atoms' container should raise this flag.
     */
    bool rib_dirty_ref;

    /**
     * Flag asserting ribose's building validity.
     */
    bool rib_built_valid;

    /**
     * Ribose building counter.
     */
    unsigned int rib_built_count;

    /**
     * Constants used in hydrogens and lone pairs insertion. 
     */
    static const float C_H_DIST_CYC;  
    static const float C_H_DIST;      
    static const float N_H_DIST;      
    static const float O_H_DIST;
    static const float O_LP_DIST;
    static const float N_LP_DIST;
    static const float TAN19;         
    static const float TAN54;
    static const float TAN60;         
    static const float TAN70;         
    static const float TAN30;
    
    /**
     * Constants for the ribose theoretical building by estimation.
     */
    static const float s_cosf_amplitude, s_cosf_vshift, s_cosf_phase, s_cosf_2xphase;

    /**
     * Respectively two times and four times the value of PI.
     */
    static const float s_2xpi, s_4xpi;
    
  public:
    
    /**
     * Default parameter values for the ribose theoretical building by optimization.
     */
    static float s_rib_minshift, s_rib_mindrop, s_rib_shiftrate;
    

  protected:

    // PRIVATE METHODS ------------------------------------------------------

    /**
     * Gets the atom at a position given by an index.  This is used by
     * the iterators.  It is private since no atom pointers should be
     * used outside the residue; these pointers are not guaranteed to be valid.
     * @param pos the position of the atom in the atom vector;
     * @return the atom.
     */
    Atom& _get (size_type pos) const;

  public:

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
      
   
      
      // LIFECYCLE ------------------------------------------------------------

    public:
      
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
      pointer operator-> () const { return &(res->_get (pos->second)); }
      
      /**
       * Dereferences the iterator.
       * @return an atom reference.
       */
      reference operator* () const { return res->_get (pos->second); }
  
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

      
      // METHODS -----------------------------------------------------------------

      
      /**
       * Overwrites currently pointed atom's coordinates in local referential
       * @param coord The atom's new coordinates.
       */
      void setLocal (const Vector3D& coord) { res->_insert_local (coord, pos); }
      
    };
    friend class Residue::ResidueIterator;


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

      // LIFECYCLE ------------------------------------------------------------

    public:
      
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
      pointer operator-> () const { return &(res->_get (pos->second)); }
    
      /**
       * Dereferences the iterator.
       * @return an atom reference.
       */
      reference operator* () const { return res->_get (pos->second); }
    
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
    
    friend class Residue::ResidueConstIterator;

     
  public:

    typedef ResidueIterator iterator;
    typedef ResidueConstIterator const_iterator;
    
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
     * Sets all atoms according to standard coordinates as defined by
     * G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.
     * Handled types are nitrogen bases (nucleic acid types), phosphates and riboses.
     * @exception CIntLibException is thrown if type isn't handled.
     */
    void setTheoretical ();

    /**
     * Sets all atoms according to standard coordinates as defined by
     * G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.
     * A full nucleic acid residue is created.
     * @exception CIntLibException is thrown if type isn't handled.
     */
    void setFullTheoretical ();
				 
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Residue& operator= (const Residue &other);
    
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

    /**
     * Verifies last ribose theoretical building's validity. An invalid ribose
     * should be ignored.
     * @return The ribose theoretical building's validity.
     */
    bool validateRiboseBuilding () const;

    /**
     * Gets the ribose theoretical building iteration count.
     * @return The ribose theoretical building iteration count.
     */
    unsigned int getRiboseBuiltCount () const;
    
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
     * Adds the HO3' hydrogen. Mandatory if the residue ends a strand.
     */
    void addHO3p ();

    /**
     * Adds the lone pairs to the residue.
     */
    virtual void addLonePairs ();

    /**
     * Calls removeOptionals, addHydrogens and addLonePairs.
     */
    void setupHLP ();
    
    /**
     * Determines the pucker pseudorotation (rho) of the NucleicAcid backbone.
     * @return The pseudorotation value (rad).
     * @exception CLibException thrown if type isn't a nucleic acid.
     */
    virtual float getRho () const;
    
    /**
     * Determines the pucker mode of the NucleicAcid backbone.
     * @return The property type label.
     */
    virtual const PropertyType* getPucker () const;

    /**
     * Determines the glycosyl torsion (chi) of the NucleicAcid backbone.
     * @return The glycosyl torsion value (rad).
     * @exception CLibException thrown if type isn't a nucleic acid.
     */
    virtual float getChi () const;
    
    /**
     * Determines the glycosidic angle classification.
     * @return The property type label.
     */
    virtual const PropertyType* getGlycosyl () const;
    
    /**
     * Finalizes the residue. Computes the referential's pseudo-atoms.
     * @exception CLibException is thrown if a needed atom is missing.
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

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base.
     * The ribose's conformation is parameterized by symbolic types, while
     * its 5' branch is optionnaly parameterized by gamma and beta torsion values. 
     * @param pucker Pucker conformation type.
     * @param glycosyl Glycosyl torsion type.
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     */
    void buildRibose (const PropertyType* pucker, const PropertyType* glycosyl,
		      bool build5p, bool build3p);

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base.
     * The ribose's conformation is parameterized by the pseudorotation (rho) and the glycosyl torsion (chi), while
     * its 5' branch is optionnaly parameterized by gamma and beta torsions. 
     * @param pucker Pucker pseudorotation (rad).
     * @param glycosyl Glycosyl torsion (rad).
     * @param gamma Gamma torsion (rad).
     * @param beta Beta torsion (rad).
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     */
    void buildRibose (float rho, float chi,
		      float gamma, float beta,
		      bool build5p, bool build3p);

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base that fits the global
     * position of two adjacent phosphates (toward 5' and 3'). The optimal value for rho
     * and chi are estimated in constant time using 3' phosphate position (which is therefore
     * mandatory). Fitting is quantified by the rms deviation for the implicit C5'-O5'
     * and C3'-O3' bond lengths. Only the 5' phosphate can be ommited (set to NULL) resulting
     * in the unconstrained building of the corresponding ribose branch. No conformation
     * restriction is allowed with this building method.
     *
     * @param po4_5p Phosphate residue toward 5' (set it to NULL for an unconstrained branch).
     * @param po4_3p Phosphate residue toward 3' (mandatory!)
     * @return Rms deviation for the implicit C5'-O5' and C3'-O3' bond lengths (Angstroms).
     * @exception CLibException is thrown if 3' phosphate is unspecified.
     */
    float buildRiboseByEstimation (const Residue* po4_5p, const Residue* po4_3p);

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base that fits the global
     * position of two adjacent phosphates (toward 5' and 3'). A constant step cyclic
     * coordinates method solves the optimization problem in the 2D torsion space created
     * by rho and chi. Both pucker and glycosyl types can be forced, otherwise
     * the best geometrical fit is favored. Fitting is quantified by the rms deviation for
     * the implicit C5'-O5' and C3'-O3' bond lengths. Any of the two phosphates can be ommited
     * (set to NULL) resulting in the unconstrained building of the corresponding ribose branch.
     * Default optimization paramaters are used.
     *
     * @param po4_5p Phosphate residue toward 5' (set it to NULL for an unconstrained branch).
     * @param po4_3p Phosphate residue toward 3' (set it to NULL for an unconstrained branch).
     * @param pucker Optional pucker type restriction.
     * @param glycosyl Optional glycosyl torsion type restriction.
     * @return Rms deviation for the implicit C5'-O5' and C3'-O3' bond lengths (Angstroms).
     * @exception CLibException is thrown if both phosphates are unspecified.
     */
    float buildRiboseByCCM2D (const Residue* po4_5p,
			      const Residue* po4_3p,
			      const PropertyType* pucker = 0,
			      const PropertyType* glycosyl = 0);
    
    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base that fits the global
     * position of two adjacent phosphates (toward 5' and 3'). A constant step cyclic
     * coordinates method solves the optimization problem in the 2D torsion space created
     * by rho and chi. Both pucker and glycosyl types can be forced, otherwise
     * the best geometrical fit is favored. Fitting is quantified by the rms deviation for
     * the implicit C5'-O5' and C3'-O3' bond lengths. Any of the two phosphates can be ommited
     * (set to NULL) resulting in the unconstrained building of the corresponding ribose branch.
     * Optimization paramaters are specified.
     *
     * @param po4_5p Phosphate residue toward 5' (set it to NULL for an unconstrained branch).
     * @param po4_3p Phosphate residue toward 3' (set it to NULL for an unconstrained branch).
     * @param minshift Torsion shift threshold during optimization (rad).
     * @param mindrop Displacement threshold in the optimization's objective function.
     * @param shiftrate Torsion shift reduction rate during optimization (assumed < 1).
     * @param pucker Optional pucker type restriction.
     * @param glycosyl Optional glycosyl torsion type restriction.
     * @return Rms deviation for the implicit C5'-O5' and C3'-O3' bond lengths (Angstroms).
     * @exception CLibException is thrown if both phosphates are unspecified.
     */
    float buildRiboseByCCM2D (const Residue* po4_5p,
			      const Residue* po4_3p,
			      float minshift,
			      float mindrop,
			      float shiftrate,
			      const PropertyType* pucker = 0,
			      const PropertyType* glycosyl = 0);

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base that fits the global
     * position of two adjacent phosphates (toward 5' and 3'). A constant step cyclic
     * coordinates method solves the optimization problem in the 4D torsion space created
     * by rho, chi, gamma and beta. Both pucker and glycosyl types can be forced, otherwise
     * the best geometrical fit is favored. Fitting is quantified by the rms deviation for
     * the implicit C5'-O5' and C3'-O3' bond lengths. Any of the two phosphates can be ommited
     * (set to NULL) resulting in the unconstrained building of the corresponding ribose branch.
     * Default optimization paramaters are used.
     *
     * @param po4_5p Phosphate residue toward 5' (set it to NULL for an unconstrained branch).
     * @param po4_3p Phosphate residue toward 3' (set it to NULL for an unconstrained branch).
     * @param pucker Optional pucker type restriction.
     * @param glycosyl Optional glycosyl torsion type restriction.
     * @return Rms deviation for the implicit C5'-O5' and C3'-O3' bond lengths (Angstroms).
     * @exception CLibException is thrown if both phosphates are unspecified.
     */
    float buildRiboseByCCM4D (const Residue* po4_5p,
			      const Residue* po4_3p,
			      const PropertyType* pucker = 0,
			      const PropertyType* glycosyl = 0);

    /**
     * Builds a theoretical ribose onto a nucleic acid's nitrogen base that fits the global
     * position of two adjacent phosphates (toward 5' and 3'). A constant step cyclic
     * coordinates method solves the optimization problem in the 4D torsion space created
     * by rho, chi, gamma and beta. Both pucker and glycosyl types can be forced, otherwise
     * the best geometrical fit is favored. Fitting is quantified by the rms deviation for
     * the implicit C5'-O5' and C3'-O3' bond lengths. Any of the two phosphates can be ommited
     * (set to NULL) resulting in the unconstrained building of the corresponding ribose branch.
     * Optimization paramaters are specified.
     *
     * @param po4_5p Phosphate residue toward 5' (set it to NULL for an unconstrained branch).
     * @param po4_3p Phosphate residue toward 3' (set it to NULL for an unconstrained branch).
     * @param minshift Torsion shift threshold during optimization (rad).
     * @param mindrop Displacement threshold in the optimization's objective function.
     * @param shiftrate Torsion shift reduction rate during optimization (assumed < 1).
     * @param pucker Optional pucker type restriction.
     * @param glycosyl Optional glycosyl torsion type restriction.
     * @return Rms deviation for the implicit C5'-O5' and C3'-O3' bond lengths (Angstroms).
     * @exception CLibException is thrown if both phosphates are unspecified.
     */
    float buildRiboseByCCM4D (const Residue* po4_5p,
			      const Residue* po4_3p,
			      float minshift,
			      float mindrop,
			      float shiftrate,
			      const PropertyType* pucker = 0,
			      const PropertyType* glycosyl = 0);
    
    /**
     * Creates and returns a new phosphate typed residue with its O5'-P bond aligned onto
     * reference residue's  O5'-P bond.
     * @param reference Residue onto which phosphate should be aligned.
     * @param fm Residue factory method used to create phosphate (default: creates ExtendedResidue)
     * @return Newly created phosphate residue. The object is dynamically created, therefore caller has ownership on memory (caller should delete it...).
     * @exception CLibException is thrown if reference is missing the needed atoms.
     */
    static Residue* createPhosphate5p (const Residue& reference,
				       const ResidueFactoryMethod* fm = 0);

    /**
     * Gets the pucker type associated with the specified pseudorotation (rho) value.
     * @param rho The pseudorotation (rho) value (rad).
     * @return The associated pucker type.
     */
    static const PropertyType* getPuckerType (float rho);

    /**
     * Gets the glycosyl torsion type associated with the specified glycosyl torsion (chi) value.
     * @param chi The glycosyl torsion (chi) value (rad).
     * @return The associated glycosyl torsion type.
     */
    static const PropertyType* getGlycosylType (float chi);

    /**
     * Gets the range of pseudorotation (rho) values associated with the specified pucker type.
     * @param pucker The pucker type.
     * @return The minimal or maximal pseudorotation (rho) value (rad).
     * @exception CLibException is thrown if pucker type is unknown.
     */
    static float getMinRho (const PropertyType* pucker);
    static float getMaxRho (const PropertyType* pucker);

    /**
     * Gets the range of glycosyl torsion (chi) values associated with the specified glycosyl torsion type.
     * @param pucker The pucker type.
     * @return The minimal or maximal glycosyl torsion (chi) value (rad).
     * @exception CLibException is thrown if glycosyl torsion type is unknown.
     */
    static float getMinChi (const PropertyType* glycosyl);
    static float getMaxChi (const PropertyType* glycosyl);
    
    
  protected:

    // PRIVATE METHODS ------------------------------------------------------

    /**
     * Gets the atom of given type.  It is private since no atom
     * pointers should be used outside the residue; these pointers are
     * not guaranteed to be valid.
     * @param type the atom type.
     * @return the atom (null pointer if atom is missing).
     */
    Atom* _get (const AtomType* type) const;

    /**
     * Gets the atom of given type.  It is private since no atom
     * pointers should be used outside the residue; these pointers are
     * not guaranteed to be valid.
     * @param type the atom type.
     * @return the atom.
     * @exception CLibException is thrown if atom is missing.
     */
    Atom* _safe_get (const AtomType* type) const;

    /**
     * Fetches the atom specified by its type. If the atom is missing, a new
     * atom of the given type is created and placed at the global origin.
     * Internal method used for ribose building.
     * @param aType The atom type.
     * @return A pointer to the atom in the internal container.
     */
    virtual Atom* _get_or_create (const AtomType *aType);

    /**
     * Overwrites an atom's coordinates in local referential. The overwritten
     * atom is pointed by an AtomMap iterator.
     * @param coord The atom's new coordinates.
     * @param posit The AtomMap iterator.
     */
    virtual void _insert_local (const Vector3D& coord, AtomMap::iterator posit);

    /**
     * Compute the residue's referential transfo.
     * @return The residue's referential transfo.
     * @exception CLibException is thrown if an atom is missing or type isn't handled.
     */
    HomogeneousTransfo _compute_referential () const;
    
    /**
     * Adds backbone's hydrogens only if they aren't already in the residue.
     */
    void _add_ribose_hydrogens ();
    
    /**
     * Preprocesses ribose building. Setups atom pointers if needed. Fetches, copies
     * and align in the residue's referential the anchor atoms from the phosphates.
     * Internal method used for ribose building.
     * @param po4_5p Phosphate residue toward 5'.
     * @param po4_3p Phosphate residue toward 3'.
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     * @param o5p Atom to receive O5' aligned copy from 5' phosphate.
     * @param o3p Atom to receive O3' aligned copy from 3' phosphate.
     * @param referential Transfo to receive a copy of the residue's referential.
     * @exception CLibException is thrown if residue type is not of the nucleic acid family or if anchor atoms are missing in the phosphates.
     */
    void _build_ribose_preprocess (const Residue* po4_5p, const Residue* po4_3p,
				   bool build5p, bool build3p,
				   Atom& o5p, Atom& o3p,
				   HomogeneousTransfo& referential);

    /**
     * Builds ribose atom-wise according to the given torsion parameters. Uses idealized
     * geometries as defined by G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     */
    void _build_ribose (float rho, float chi, float gamma, float beta,
			bool build5p, bool build3p);

    /**
     * Builds ribose atom-wise according to the given torsion parameters. Uses idealized
     * geometries as defined by G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * Construction method apply explicit transformation (slower than premultiplying, but kept for maintenance)
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     */
    void _build_ribose_explicitly (float rho, float chi, float gamma, float beta,
				   bool build5p, bool build3p);

    /**
     * Transforms ribose's atoms directly.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * @param tfo Transfo applied.
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).
     */
    void _transform_ribose (const HomogeneousTransfo& tfo,
			    bool build5p, bool build3p);
    
    /**
     * Computes the sum of the implicit C5'-O5' and C3'-O3' squared bond lengths.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * @param o5p Anchoring O5' atom.
     * @param o3p Anchoring O3' atom.
     * @param build5p If true then C5'-O5' length is assumed perfect.
     * @param build3p If true then C3'-O3' length is assumed perfect.
     * @return The squared bond lengths sum (Angstroms*Angstroms).
     */
    float _evaluate_ribose (const Atom& o5p, const Atom& o3p,
			    bool build5p, bool build3p) const;

    /**
     * Postprocesses ribose building. Places ribose's atoms back in global referential.
     * Internal method used for ribose building. Assumes that the ribose's atom pointers are set!
     * @param referential Residue's saved referential.
     * @param build5p Flag to enable 5' branch construction (O5' and P atoms).
     * @param build3p Flag to enable 3' branch construction (O3' atom).    
     */
    virtual void _build_ribose_postprocess (const HomogeneousTransfo& referential,
					    bool build5p, bool build3p);
    
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
   * Ouputs the residue to the exception stream.
   * @param ex the exception stream.
   * @param r the residue.
   * @return the used exception stream.
   */
  CException& operator<< (CException& ex, const Residue &r);
  
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

  /**
   * Inputs the residue from the pdb stream.
   * @param ibs the input pdb stream.
   * @param res the residue to fill.
   * @return the input pdb stream used.
   */
  iPdbstream& operator>> (iPdbstream &ibs, Residue &res);
  
  
  /**
   * Outputs the Residue to the pdb stream.
   * @param obs the output pdb stream.
   * @param res the Residue.
   * @return the output pdb stream used.
   */
  oPdbstream& operator<< (oPdbstream &obs, const Residue &res);
}
  
#endif
