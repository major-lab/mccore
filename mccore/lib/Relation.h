//                              -*- Mode: C++ -*- 
// Relation.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003
// $Revision: 1.12 $
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


#ifndef _Relation_h_
#define _Relation_h_

#include <iostream>
#include <list>
#include <set>
#include <vector>

#include "HomogeneousTransfo.h"
#include "HBond.h"
#include "MaximumFlowGraph.h"

using namespace std;



namespace mccore {

  class Residue;
  class PropertyType;
  class iBinstream;
  class oBinstream;

  

  /**
   * HBondFlow
   */
  struct HBondFlow {
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
   * @version $Id: Relation.h,v 1.12 2004-08-17 18:30:10 thibaup Exp $
   */
  class Relation
  {

  protected:
    
    /**
     * The residue at the origin of this relation.
     */
    const Residue* ref;

    /**
     * The residue at the destination of this relation.
     */
    const Residue* res;

    /**
     * The homogeneous matrix that expresses the transformation from the ref to the res.
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
    const PropertyType* refFace;
    
    /**
     * A property for the interacting face of the res.
     */
    const PropertyType* resFace;
    
    /**
     * General properties of the interaction.
     */
    set< const PropertyType* > labels;

    /**
     * The collection of hbond.  Empty if not a pairing.
     */
    vector< HBondFlow > hbonds;

    /**
     * The pairing flow sum, on other cases 0.
     */
    float sum_flow;

    // STATIC MEMBERS -------------------------------------------------------

    static vector< pair< Vector3D, const PropertyType* > > faces_A;
    static vector< pair< Vector3D, const PropertyType* > > faces_C;
    static vector< pair< Vector3D, const PropertyType* > > faces_G;
    static vector< pair< Vector3D, const PropertyType* > > faces_U;
    static vector< pair< Vector3D, const PropertyType* > > faces_T;
    
    static bool isInit;
    
    // LIFECYCLE ------------------------------------------------------------

  public:

    /**
     * Initializes the object.
     */
    Relation ();

    /**
     * Initializes the object. The relation keeps only pointers to the original residues.
     * @param rA the residue of origin of the relation.
     * @param rB the residue of destination of the relation.
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
    virtual Relation* clone () const;
    
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
     * Returns the origin residue of the relation.
     */
    const Residue* getRef () const { return ref; }

    /**
     * Returns the destination residue of the relation.
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
     * Returns the transformation between the residues of the relation.
     */
    HomogeneousTransfo getTransfo () const { return tfo; }

    /**
     * Returns the transformation between the phosphate and the reference
     * residue of the relation.
     */
    HomogeneousTransfo getPhosphateTransfo () const { return po4_tfo; }

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

    // METHODS --------------------------------------------------------------

    bool is (const PropertyType* t) const {
      return (labels.find (t) != labels.end ());
    }
    
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

  public:
    
    /**
     * Inverts the relation.
     */
    Relation invert () const;
    
    /**
     * Determines if there are properties in the relation.
     * @return true if there is no property in the relation.
     */
    bool empty () { return labels.empty (); }

    // STATIC METHODS -------------------------------------------------------
    
    /**
     * Determines if the given residues are adjacent in sequence based
     * on the position of their atoms.
     * @param ra a residue.
     * @param rb another residue.
     * @return a set of properties describing the adjacency state.
     */
    static set< const PropertyType* > 
    areAdjacent (const Residue* ra, const Residue *rb);
    
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
    static set< const PropertyType* > 
    arePaired (const Residue* ra, const Residue *rb, 
	       const PropertyType*& pta, const PropertyType*& ptb);

    /**
     * [Experimental] Determines if there is at least one H-HBond
     * possible between the two residues, regardless of the position
     * of the donors and acceptors.
     */
    static set< const PropertyType* > 
    areHBonded (const Residue* ra, const Residue *rb);
    

    // PRIVATE METHODS ------------------------------------------------------

  protected:
    
    /**
     *
     */
    static Vector3D pyrimidineNormal (const Residue *r);

    /**
     *
     */
    static Vector3D imidazolNormal (const Residue *r);

    /**
     * 
     */
    static const PropertyType* getFace (const Residue *r, const Vector3D& p);

    /**
     * 
     */
    static void init ();

    /**
     * 
     */
    static const PropertyType* 
    translatePairing (const Residue* ra, const Residue *rb, 
		      list< HBondFlow > &hbf, float total_flow, int size_hint);

    // I/O  -----------------------------------------------------------------

  public:

    /**
     * Ouputs the relation to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& write (ostream &os) const;
    
//     /**
//      * Inputs the residue from the stream. Not virtual so that only
//      * the minimum data is transfered.
//      * @param ibs the input stream.
//      * @return the used output stream.
//      */
//     iBinstream& input (iBinstream &ibs);
    
//     /**
//      * Ouputs the residue to the stream.  Not virtual so that only the
//      * minimum data is transfered.
//      * @param os the output stream.
//      * @return the used output stream.
//      */
//     oBinstream& output (oBinstream &obs) const;
    
  };

  // NON_MEMBER FUNCTIONS ------------------------------------------------------

  /**
   * Ouputs the relation to the stream.
   * @param os the output stream.
   * @param r the relation.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const Relation &r);

  /**
   * Ouputs the relation to the stream.
   * @param os the output stream.
   * @param r the relation.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const Relation *r);
  
//   /**
//    * Inputs the relation from the binary stream.
//    * @param ibs the input binary stream.
//    * @param res the relation to fill.
//    * @return the input binary stream used.
//    */
//   iBinstream& operator>> (iBinstream &ibs, Relation &res);

  
//   /**
//    * Outputs the relation to the binary stream.
//    * @param obs the output binary stream.
//    * @param res the relation.
//    * @return the output binary stream used.
//    */
//   oBinstream& operator<< (oBinstream &obs, const Relation &res);

}

#endif
