//                              -*- Mode: C++ -*- 
// Relation.h
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003
// $Revision: 1.17 $
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


#ifndef _mccore_Relation_h_
#define _mccore_Relation_h_

#include <iostream>
#include <list>
#include <set>
#include <utility>
#include <vector>

#include "Algo.h"
#include "Exception.h"
#include "HBond.h"
#include "HomogeneousTransfo.h"
#include "Residue.h"
#include "Vector3D.h"

using namespace std;



namespace mccore
{
  class PropertyType;

  

  /**
   * HBondFlow
   */
  struct HBondFlow
  {
    HBond hbond;
    float flow;

    HBondFlow () { }
    HBondFlow (const HBond &hbond, float flow) : hbond (hbond), flow (flow) { }
    bool operator< (const HBondFlow& other) const { return flow < other.flow; }
  };
  

  /**
   * @short A relation between two residues.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Relation.h,v 1.17 2005-01-10 16:47:13 thibaup Exp $
   */
  class Relation
  {
    static const float PAIRING_CUTOFF = 0.8f;
    static const float TWO_BONDS_CUTOFF = 1.5f;
    static const float THREE_BONDS_CUTOFF = 2.1f;

  protected:
    
    /**
     * The residue location at the origin of this relation.
     */
    const Residue *ref;

    /**
     * The residue location at the destination of this relation.
     */
    const Residue *res;

    /**
     * The homogeneous matrix that expresses the transformation from the ref
     * to the res.
     */
    HomogeneousTransfo tfo;

    /**
     * The homogeneous matrix that expresses the transformation from
     * the reference residue to the phosphate residue.
     */
    HomogeneousTransfo po4_tfo;
    
    /**
     * A property for the interacting face of the ref.
     */
    const PropertyType *refFace;
    
    /**
     * A property for the interacting face of the res.
     */
    const PropertyType *resFace;
    
    /**
     * General properties of the interaction.
     */
    set< const PropertyType* > labels;

    /**
     * The three-bits annotation type: msb<-[adjacent][stacking][pairing]->lsb
     */
    unsigned char type_asp;
    
    /**
     * The collection of hbond.  Empty if not a pairing.
     */
    vector< HBondFlow > hbonds;

    /**
     * The pairing flow sum, on other cases 0.
     */
    float sum_flow;


    // STATIC MEMBERS -------------------------------------------------------


  public:
    
    /**
     * The adjacent type mask (100).
     */
    static const unsigned char adjacent_mask;

    /**
     * The stacking type mask (010).
     */
    static const unsigned char stacking_mask;

    /**
     * The pairing type mask (001).
     */
    static const unsigned char pairing_mask;

  protected:

    static vector< pair< Vector3D, const PropertyType* > > faces_A;
    static vector< pair< Vector3D, const PropertyType* > > faces_C;
    static vector< pair< Vector3D, const PropertyType* > > faces_G;
    static vector< pair< Vector3D, const PropertyType* > > faces_U;
    static vector< pair< Vector3D, const PropertyType* > > faces_T;

    static bool face_init;

    /**
     * The O3'-P squared bond length cutoff between adjacent nucleotides (Angstroms square).
     */
    static float adjacency_distance_cutoff_square;
    
    /**
     * The nitrogen base center squared distance cutoff for a stacking (Angstroms square).
     */
    static float stack_distance_cutoff_square;

    /**
     * The nitrogen base plane tilt cutoff for a stacking (radian).
     */
    static float stack_tilt_cutoff;

    /**
     * The nitrogen base plane overlap cutoff for a stacking (radian).
     */
    static float stack_overlap_cutoff;

  public:
    
    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Relation ();

    /**
     * Initializes the object. The relation keeps only pointers to the
     * original residues.
     * @param rA the residue location of origin of the relation.
     * @param rB the residue location of destination of the relation.
     */
    Relation (const Residue *rA, const Residue *rB);

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Relation (const Relation &other);

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Relation* clone () const { return new Relation (*this); }
    
    /**
     * Destroys the object.
     */
    virtual ~Relation () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Relation& operator= (const Relation &other);

    // ACCESS ---------------------------------------------------------------

    /**
     * Returns the origin residue location of the relation.
     */
    const Residue* getRef () const { return ref; }

    /**
     * Returns the destination residue location of the relation.
     */
    const Residue* getRes () const { return res; }
    
    /**
     * Returns the face interacting in the relation, if any.
     */
    const PropertyType* getRefFace () const { return refFace; }

    /**
     * Returns the face interacting in the relation, if any.
     */
    const PropertyType* getResFace () const { return resFace; }

    /**
     * Returns the properties of the relation.
     */
    const set< const PropertyType* >& getLabels () const { return labels; }

    /**
     * Gets the annotation type bits.
     * @return The annotation type bits.
     */
    unsigned char getAnnotationType () const
    {
      return this->type_asp;
    }
    
    /**
     * Returns the transformation between the residues of the relation.
     */
    const HomogeneousTransfo& getTransfo () const { return tfo; }

    /**
     * Returns the transformation between the phosphate and the reference
     * residue of the relation.
     */
    const HomogeneousTransfo& getPhosphateTransfo () const { return po4_tfo; }

    /**
     * Gets the hbonds flow collection.  Empty in case of a non pairing
     * relation.
     * @return the HBondFlow vector.
     */
    const vector< HBondFlow >& getHBondFlows () const { return hbonds; }

    /**
     * Gets the pairing flow sum.  0 in case of a non pairing relation.
     * @return the flow sum.
     */
    float getFlowSum () const { return sum_flow; }

    /**
     * Replaces the Residue pointers with those coming from the set.  It
     * is used by the GraphModel class to do a deep copy without doing a full
     * re-annotation.
     * @param resSet a set of Residue pointers.
     * @exception NoSuchElementException is thrown when ref or res is not found
     * in resSet.
     */
    void reassignResiduePointers (const set< const Residue*, less_deref< Residue > > &resSet) throw (NoSuchElementException);

    // METHODS --------------------------------------------------------------

    /**
     * Check if a label or its children is in the annotation.
     * @param t The property type label to find.
     * @return True only if the label or its children is in the annotation.
     */
    bool is (const PropertyType* t) const;

    /**
     * Check if a label is in the annotation (not its children).
     * @param t The property type label to find.
     * @return True only if the label is in the annotation.
     */
    bool has (const PropertyType* t) const;

    /**
     * Tells is the annotated relation is from the adjacent family.
     * Return True only if the annotated relation is from the adjacent family.
     */
    bool isAdjacent () const;

    /**
     * Tells is the annotated relation is from the stacking family.
     * Return True only if the annotated relation is from the stacking family.
     */
    bool isStacking () const;

    /**
     * Tells is the annotated relation is from the pairing family.
     * Return True only if the annotated relation is from the pairing family.
     */
    bool isPairing () const;

    /**
     * Resets the relation's annotation data and set it up from two new residues.
     * @param rA The new origin.
     * @param rB The new destination.
     */
    void reset (const Residue* org, const Residue* dest);
    
    /** 
     * Describes the interaction.
     * @return true if there is indeed a relation between the bases.
     */
    bool annotate ();

  protected:
    
    /**
     * Tests for adjacency relation.
     */
    void areAdjacent ();

  private:

    /**
     * Adds the pairing labels into the Relation.
     */
    void addPairingLabels ();

  protected:
    
    /**
     * Tests for h-bonded relation.
     */
    void areHBonded ();

    /**
     * Test for pairing relation.
     */
    void arePaired ();

    /**
     * Tests for stacking relation.
     */
    void areStacked ();

    /**
     * DEPRECATED
     * Tests for stacking relation.
     */
    void areStacked_old ();

  public:

    /**
     * Inverts this relation.
     * @return itself.
     */
    Relation& invert ();
    
    /**
     * Determines if there are properties in the relation.
     * @return true if there is no property in the relation.
     */
    bool empty () const { return labels.empty (); }
    
    // STATIC METHODS -------------------------------------------------------
    
    /**
     * Determines if the given residues are adjacent in sequence based
     * on the position of their atoms.
     * @param ra a residue.
     * @param rb another residue.
     * @return a set of properties describing the adjacency state.
     */
    static set< const PropertyType* > areAdjacent (const Residue *ra, const Residue *rb);
    
    /**
     * Determines if the given residues are stacked in space based
     * on the position of their rings.
     * @param ra a residue.
     * @param rb another residue.
     * @return a set of properties describing the stacked state.
     */
    static set< const PropertyType* > 
    areStacked (const Residue* ra, const Residue *rb);

    /**
     * DEPRECATED
     * Determines if the given residues are stacked in space based
     * on the position of their rings.
     * @param ra a residue.
     * @param rb another residue.
     * @return a set of properties describing the stacked state.
     */
    static set< const PropertyType* > 
    areStacked_old (const Residue* ra, const Residue *rb);
    
    /**
     * Determines if the given residues are paired in space based on
     * the formation of hydrogen bonds.  This method is used for the
     * base pairing of nucleic acids based the parameters derived in:
     * S. Lemieux and F. Major, RNA canonical and non-canonical base
     * pairing types: a recognition method and complete
     * repertoire. NAR, 30(19): 4250-4263, 2002.
     * @param ra a residue.
     * @param ra another residue.
     * @param pta the resulting interacting face of a.
     * @param ptb the resulting interacting face of b.
     * @return a Vector containing a Set of keywords describing the paired state,
     *          the face of ra and the face of rb interacting in the pairing.
     */
    static set< const PropertyType* > arePaired (const Residue *ra, const Residue *rb, const PropertyType *pta, const PropertyType *ptb);

    /**
     * [Experimental] Determines if there is at least one H-HBond
     * possible between the two residues, regardless of the position
     * of the donors and acceptors.
     */
    static set< const PropertyType* > areHBonded (const Residue *ra, const Residue *rb);
    

    // PRIVATE METHODS ------------------------------------------------------

  protected:
    
    /**
     * DEPRECATED
     */
    static Vector3D pyrimidineNormal (const Residue *r);

    /**
     * DEPRECATED
     */
    static Vector3D imidazolNormal (const Residue *r);

    /**
     * Calculates the pyrimidine ring's geometrical center from a nucleic acid residue.
     * @param res The residue.
     * @return The ring center.
     * @exception NoSuchAtomException
     */
    static Vector3D _pyrimidine_ring_center (const Residue& res);

    /**
     * Calculates the imidazole ring's geometrical center from a nucleic acid residue.
     * @param res The residue.
     * @return The ring center.
     * @exception NoSuchAtomException
     */
    static Vector3D _imidazole_ring_center (const Residue& res);

    /**
     * Calculates the pyrimidine ring's normal vector from a nucleic acid residue using
     * the Cremer and Pople method.
     * Cremer D., Pople J.A., J. Am. Chem. Soc. 1975, 97, 1354-1358
     * @param res The residue.
     * @param center The ring center.
     * @return The normal vector (normalized).
     * @exception NoSuchAtomException
     */
    static Vector3D _pyrimidine_ring_normal (const Residue& res, const Vector3D& center);

    /**
     * Calculates the imidazole ring's normal vector from a nucleic acid residue using
     * the Cremer and Pople method.
     * Cremer D., Pople J.A., J. Am. Chem. Soc. 1975, 97, 1354-1358
     * @param res The residue.
     * @param center The ring center.
     * @return The normal vector (normalized).
     * @exception NoSuchAtomException
     */
    static Vector3D _imidazole_ring_normal (const Residue& res, const Vector3D& center);

    /**
     * Check if two nitrogen base rings are stacking on each other. Three criteria are to be
     * satisfied: the rings' center distance, the rings' plane tilt angle and horizontal overlapping. 
     * @param centerA The first ring's center.
     * @param normalA The first ring's normal.
     * @param centerB The second ring's center.
     * @param normalB The second ring's normal.
     * @return The stacking annotation as a pair of property types (both set to Null when not stacked)
     */
    const PropertyType*
    _ring_stacking (const Vector3D& centerA, const Vector3D& normalA,
		    const Vector3D& centerB, const Vector3D& normalB);
    
    /**
     * 
     */
    static const PropertyType* getFace (const Residue *r, const Vector3D &p);

    /**
     * 
     */
    static void init ();

    /**
     * 
     */
    static const PropertyType* translatePairing (const Residue *ra, const Residue *rb, list< HBondFlow > &hbf, float total_flow, unsigned int size_hint);

    // I/O  -----------------------------------------------------------------

  public:

    /**
     * Ouputs the relation to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& write (ostream &os) const;
    
  };

}



namespace std
{
  
  /**
   * Ouputs the relation to the stream.
   * @param os the output stream.
   * @param r the relation.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::Relation &r);

  /**
   * Ouputs the relation to the stream.
   * @param os the output stream.
   * @param r the relation.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::Relation *r);

}

#endif
