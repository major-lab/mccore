//                              -*- Mode: C++ -*- 
// Relation.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003
// $Revision: 1.2 $
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
#include <set>
#include <vector>

#include "HomogeneousTransfo.h"

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  class BasicResidue;
  class PropertyType;

  /**
   * @short A relation between two residues.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Relation.h,v 1.2 2003-05-13 18:19:51 gendrop Exp $
   */
  class Relation
  {
    /**
     * The residue at the origin of this relation.
     */
    const BasicResidue* ref;

    /**
     * The residue at the destination of this relation.
     */
    const BasicResidue* res;

    /**
     * The homogeneous matrix that expresses the transformation from the ref to the res.
     */
    HomogeneousTransfo tfo;

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
    Relation (const BasicResidue *rA, const BasicResidue *rB);

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Relation (const Relation &other);

    /**
     * Destroys the object.
     */
    ~Relation ();

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
    const BasicResidue* getRef () const { return ref; }

    /**
     * Returns the destination residue of the relation.
     */
    const BasicResidue* getRes () const { return res; }

    // METHODS --------------------------------------------------------------

    bool is (const PropertyType* t) const {
      return (labels.find (t) != labels.end ());
    }
    
    /** 
     * Describes the interaction.
     * @return true if there is indeed a relation between the bases.
     */
    bool annotate ();
        
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
    areAdjacent (const BasicResidue* ra, const BasicResidue *rb);
    
    /**
     * Determines if the given residues are stacked in space based
     * on the position of their rings.
     * @param ra a residue.
     * @param rb another residue.
     * @return a set of properties describing the stacked state.
     */
    static set< const PropertyType* > 
    areStacked (const BasicResidue* ra, const BasicResidue *rb);
    
    /**
     * Determines if the given residues are paired in space based
     * on the formation of hydrogen bonds.
     * @param ra a residue.
     * @param ra another residue.
     * @param pta the resulting interacting face of a.
     * @param ptb the resulting interacting face of b.
     * @return a Vector containing a Set of keywords describing the paired state,
     *          the face of ra and the face of rb interacting in the pairing.
     */
    static set< const PropertyType* > 
    arePaired (const BasicResidue* ra, const BasicResidue *rb, 
	       const PropertyType*& pta, const PropertyType*& pta);

    // PRIVATE METHODS ------------------------------------------------------

  private:
    
    /**
     *
     */
    static Vector3D pyrimidineNormal (const BasicResidue *r);

    /**
     *
     */
    static Vector3D imidazolNormal (const BasicResidue *r);

    /**
     * 
     */
    static const PropertyType* getFace (const BasicResidue *r, const Vector3D& p);

    /**
     * 
     */
    static void init ();

    // I/O  -----------------------------------------------------------------

  public:

    /**
     * Ouputs the relation to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    ostream& output (ostream &os) const;
    
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
  
  /**
   * Inputs the relation from the binary stream.
   * @param ibs the input binary stream.
   * @param res the relation to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &ibs, Relation &res);

  
  /**
   * Outputs the relation to the binary stream.
   * @param obs the output binary stream.
   * @param res the relation.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &obs, const Relation &res);

}

#endif
