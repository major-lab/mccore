//                              -*- Mode: C++ -*- 
// Relation.h
// Copyright � 2003-06 Laboratoire de Biologie Informatique et Th�orique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003
// $Revision: 1.30 $
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
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "Algo.h"
#include "Exception.h"
#include "HBond.h"
#include "HomogeneousTransfo.h"
#include "ResId.h"
#include "Residue.h"
#include "Vector3D.h"

using namespace std;



namespace mccore
{
  class PropertyType;
  class iBinstream;
  class oBinstream;

  

  /**
   * HBondFlow
   */
  struct HBondFlow
  {
    HBond hbond;
    float flow;

    HBondFlow () { }
    virtual ~HBondFlow () { }
    HBondFlow (const HBond &hbond, float flow) : hbond (hbond), flow (flow) { }
    bool operator< (const HBondFlow& other) const { return flow < other.flow; }

    virtual ostream& write (ostream &os) const;
    
    virtual iBinstream& read (iBinstream &is, const map< ResId, const Residue* > &resMap);

    virtual oBinstream& write (oBinstream &os) const;
  };

  /**
   * @short A relation between two residues.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Relation.h,v 1.30 2007-01-09 00:02:22 larosem Exp $
   */
  class Relation
  {
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
     * The four-bits annotation type: msb<-[adjacent][stacking][pairing][backbone]->lsb
     */
    unsigned char type_aspb;
    
    /**
     * The collection of hbond.  Empty if not a pairing.
     */
    vector< HBondFlow > hbonds;

    /**
     * The pairing flow sum, on other cases 0.
     */
    float sum_flow;

    /**
     * Collection of pairing faces.
     */
    vector< pair< const PropertyType*, const PropertyType* > > pairedFaces;


    // STATIC MEMBERS -------------------------------------------------------


  public:
    
    /**
     * The adjacent type mask (1000).
     */
    static const unsigned char adjacent_mask = 8;

    /**
     * The stacking type mask (0100).
     */
    static const unsigned char stacking_mask = 4;

    /**
     * The pairing type mask (0010).
     */
    static const unsigned char pairing_mask = 2;

    /**
     * The backbone hydrogen bond type mask (0001).
     */
    static const unsigned char bhbond_mask = 1;

  protected:

    static vector< pair< Vector3D, const PropertyType* > > faces_A;
    static vector< pair< Vector3D, const PropertyType* > > faces_C;
    static vector< pair< Vector3D, const PropertyType* > > faces_G;
    static vector< pair< Vector3D, const PropertyType* > > faces_U;
    static vector< pair< Vector3D, const PropertyType* > > faces_T;

    static bool face_init;

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
     * Initializes a symbolic Relation object. It should stay constant
     * or else behavior is undeterminded.
     */
    Relation (const Residue* res1, 
	      const Residue* res2,
	      const PropertyType* face1,
	      const PropertyType* face2,
	      const set< const PropertyType* >& props);

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
     * Creates a new symbolic Relation object. It should stay constant
     * or else behavior is undeterminded. ASPB bitfield is adjusted
     * according to input (backbone not yet handled).
     * @param res1 First residue.
     * @param res2 Second residue.
     * @param face1 Contact face on first residue if paired.
     * @param face2 Contact face on second residue if paired.
     * @param props Property labels. 
     * @return New object.
     */
    static Relation* createSymbolic (const Residue* res1, 
				     const Residue* res2,
				     const PropertyType* face1,
				     const PropertyType* face2,
				     const set< const PropertyType* >& props);
    
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
      return this->type_aspb;
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
     * Gets the pairing faces vector.
     * @return the collection of pairing faces.
     */
    const vector< pair< const PropertyType*, const PropertyType* > >& getPairedFaces () const { return pairedFaces; }

    /**
     * Replaces the Residue pointers with those coming from the set.  It
     * is used by the GraphModel class to do a deep copy without doing a full
     * re-annotation.
     * @param resSet a set of Residue pointers.
     * @exception NoSuchElementException is thrown when ref or res is not found
     * in resSet.
     */
    void reassignResiduePointers (const Residue* target_ref, const Residue* target_res);
    void reassignResiduePointers (const set< const Residue*, less_deref< Residue > > &resSet);
  private:
    void _reassignResiduePointers (const Residue* target_ref, const Residue* target_res);
  public:

    // METHODS --------------------------------------------------------------

    /**
     * Check if a label or its children is in the annotation.
     * @param t The property type label to find.
     * @return true only if the label or its children is in the annotation.
     */
    bool is (const PropertyType* t) const;

    /**
     * Check if a label is in the annotation (not its children).
     * @param t The property type label to find.
     * @return true only if the label is in the annotation.
     */
    bool has (const PropertyType* t) const;

    /**
     * Tells is the annotated relation is from the adjacent family.
     * @return true only if the annotated relation is from the adjacent family.
     */
    bool isAdjacent () const { return 0 != (type_aspb & Relation::adjacent_mask); }

    /**
     * Tells is the annotated relation is from the stacking family.
     * Return true only if the annotated relation is from the stacking family.
     */
    bool isStacking () const { return 0 != (type_aspb & Relation::stacking_mask); }

    /**
     * Tells is the annotated relation is from the pairing family.
     * @return true only if the annotated relation is from the pairing family.
     */
    bool isPairing () const { return 0 != (type_aspb & Relation::pairing_mask); }
    
   /**
     * Tells is the annotated relation is from the hbond family.
     * @return true only if the annotated relation is from the hydrogen bond
     * family.
     */
    bool isBHbond () const { return 0 != (type_aspb & Relation::bhbond_mask); }

    /**
     * Parse an annotation mask string into a bitmask. The string is
     * composed by the concatenation of characters A, S, P or B
     * (case-insensitive):
     * 
     *   A  annotate adjacency (phosphodiester linkage)
     *   S  annotate base stacking
     *   P  annotate base pairing
     *   B  annotate hydrogen-bonding with backbone
     *
     * Throws an @ref IntLibException for any other character.
     *
     * @param mask_str The annotation mask string.
     * @return The parsed annotation bitmask.
     * @exception IntLibException
     */
    static unsigned char parseAnnotationMask (const string& mask_str);

    /**
     * Resets the relation's annotation data and set it up from two new residues.
     * @param rA The new origin.
     * @param rB The new destination.
     */
    void reset (const Residue* org, const Residue* dest);
    
    /** 
     * Describes the interaction.
     * @param asbp Bit mask controlling annotation tasks: adjacency, 
     *        stacking, pairing and pairing with backbone (default: all).
     * @return true if there is indeed a relation between the bases.
     */
    bool annotate (unsigned char aspb = adjacent_mask|pairing_mask|stacking_mask|bhbond_mask);
    
    /**
     * Tests for adjacency relation.
     */
    void areAdjacent ();

    /**
     * Tests for backbone hydrogen bonded relation.
     */
    void areBHBonded ();

    /**
     * Test for pairing relation.
     */
    void arePaired ();

    /**
     * Tests for stacking relation.
     */
    void areStacked ();

  private:

    /**
     * Adds the pairing labels into the Relation.
     */
    void addPairingLabels ();

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
    static set< const PropertyType* > areBHBonded (const Residue *ra, const Residue *rb);
    

    // PRIVATE METHODS ------------------------------------------------------

  protected:
    
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
    static const PropertyType* translatePairing (const Residue *ra, const Residue *rb, const PropertyType *bpo, list< HBondFlow > &hbf, float total_flow, unsigned int size_hint);

    // I/O  -----------------------------------------------------------------

  public:

    /**
     * Ouputs the relation to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& write (ostream &os) const;

    /**
     * Reads the relation from a binary stream.
     * @param is the binary input stream.
     * @param resMap the models residue mapping to their ResId.
     * @return the binary input stream.
     * @exception NoSuchElementException is thrown when ref or res is not found
     * within resMap.
     */
    virtual iBinstream& read (iBinstream &is, const map< ResId, const Residue* > &resMap);
    
    /**
     * Writes the relation to a binary stream.
     * @param os the binary output stream.
     * @return the binary output stream.
     */
    virtual oBinstream& write (oBinstream &os) const;
    
  };

}



namespace std
{

  /**
   * Ouputs the HBondFlow to the stream.
   * @param os the output stream.
   * @param hbf the HBondFlow.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::HBondFlow &hbf);
  
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
