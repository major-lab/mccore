//                              -*- Mode: C++ -*- 
// ResidueType.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:26:33 2003
// $Revision: 1.17 $
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


#ifndef _ResidueType_h_
#define _ResidueType_h_

#include <iostream>
#include <typeinfo>

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore { 

  class ResidueTypeStore;
  
  /**
   * Residue types.<br>
   *
   * The type member is the one that should be used when creating pdb files.
   *
   * Implicit information: <br>
   *   - Mapping from string to actual type.<br>
   *   - The nature of a type (nucleic acid (pur/pyr) or amino acid)<br>
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: ResidueType.h,v 1.17 2003-09-26 21:17:22 gendrop Exp $
   */
  class ResidueType
  {    
    /**
     * Container for string to type associations.
     */
    static ResidueTypeStore rtstore;

    /**
     * The type.
     */
    char* type;

    /**
     * The long type.
     */
    char* longtype;

  protected: 

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    ResidueType ();

    /**
     * Initializes the object.
     * @param t the string representation of the type.
     * @param lt the long string representation of the type.
     */
    ResidueType (const char* t, const char* lt);

    /**
     * (Disallow copy constructor) Initializes the object with another residue type.
     * @param other another type.
     */
    ResidueType (const ResidueType &t);

    /**
     * Destroys the object.
     */
    virtual ~ResidueType ();
    
    /**
     * AtomTypeStore is a friend since the destructor is private.
     */
    friend class ResidueTypeStore;

  public:

    // FUNCTION OBJECTS --------------------------------------------------------

    /**
     * @short less comparator for Residuetypes.
     */
    struct less
    {
      /**
       * Tests whether the first atomtype is less than the second. 
       * @param s1 the first string.
       * @param s2 the second string.
       * @return the result of the test.
       */
      bool operator() (const ResidueType* t1, const ResidueType* t2) const
      { return *t1 < *t2; }
    };
    
    // OPERATORS ---------------------------------------------------------------
    
    /**
     * Indicates whether some other residuetype is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const ResidueType &other) const
    { return strcmp (type, other.type) == 0; }

    /**
     * Indicates whether some other residue is "not equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const ResidueType &other) const 
    { return ! operator== (other); }

    /**
     * Imposes a total ordering on the ResidueType objects.
     * @param obj the residue type to compare.
     * @return true if this residue type is less than the other.
     */
    bool operator< (const ResidueType &other) const
    { return strcmp (type, other.type) < 0; }

    // METHODS -----------------------------------------------------------------
    
    /**
     * Converts the residuetype into a string.
     * @return the string.
     */
    virtual operator const char* () const { return type; }
 
    /**
     * Converts the residuetype into a string.
     * @return the string.
     */
    virtual const char* toString () const { return type; }

    /**
     * Converts the residuetype into a long string.
     * @return the string.
     */
    virtual const char* toLongString () const { return longtype; }

    /**
     * Converts the residuetype into a PDB compliant string.
     * @return the string.
     */
    virtual const char* toPdbString () const {       
      return (isAminoAcid ()?longtype:type); 
    }

    /**
     * Identifies the type of residue stored in a string.
     * @param s the string.
     * @return a residue type for the string.
     */
    static const ResidueType* parseType (const char* t);

    /**
     * Invalidates the residue type.  
     * @return a new ResidueType with the current strings as content.
     */
    const ResidueType* invalidate () const;
    
    /**
     * General is method for use when both objects to compare are of
     * unknown type.
     */
    virtual bool is (const ResidueType *t) const {
      return t->describe (this);
    }

    /**
     * Tests whether the type t is a ResidueType or derived class.
     * @param the type to test.
     * @return the truth value of the test.
     */
    virtual bool describe (const ResidueType *t) const {
      return dynamic_cast< const ResidueType* >(t);
    }
    
    /** 
     * is Nucleic Acid?
     */
    virtual bool isNucleicAcid () const {
      return false;
    }

    /**
     * is RNA?
     */
    virtual bool isRNA () const {
	return false;
    }

    /**
     * is DNA?
     */
    virtual bool isDNA () const {
	return false;
    }

    /**
     * is Phosphate
     */
    virtual bool isPhosphate () const {
        return false;
    }
    
    /** 
     * is Amino Acid?
     */
    virtual bool isAminoAcid () const {
	return false;
    }

    /** 
     * is Purine?
     */
    virtual bool isPurine () const {
	return false;
    }

    /** 
     * is Pyrimidine?
     */
    virtual bool isPyrimidine () const {
	return false;
    }

    /**
     * Tests wheter the residue type is a A.
     * @return true if the residue type is a A.
     */
    virtual bool isA() const {	
	return false;
    }

    /**
     * Tests wheter the residue type is a C.
     * @return true if the residue type is a C.
     */
    virtual bool isC() const {
	return false;
    }

    /**
     * Tests wheter the residue type is a G.
     * @return true if the residue type is a G.
     */
    virtual bool isG() const {
	return false;
    }

    /**
     * Tests wheter the residue type is a U.
     * @return true if the residue type is a G.
     */
    virtual bool isU() const {
	return false;
    }

    /**
     * Tests wheter the residue type is a T.
     * @return true if the residue type is a T.
     */
    virtual bool isT() const {
	return false;
    }

    /**
     * Tests wheter the residue type is unknown (a miscelaneous residue)
     * @return true if the object is exactly a ResidueType
     */
    virtual bool isUnknown() const {
      return (typeid (*this) == typeid (ResidueType));
    }

    /**
     * Finds the least general type for the given residue types.
     * @param aResType1 a residue type.
     * @param aResType2 a residue type.
     * @return the least general type for the given residue types.
     */
    static const ResidueType* 
    generalizeBase (const ResidueType *aResType1, const ResidueType *aResType2);


  public:

    
    // I/O ---------------------------------------------------------------------


    /**
     * Outputs to a stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    ostream &output (ostream &out) const;


    /**
     * Outputs to a binary stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    oBinstream &output (oBinstream &out) const;


  public:


    // TYPE POINTERS -----------------------------------------------------------


    static ResidueType* rUnknown;
    static ResidueType* rNucleicAcid;
    static ResidueType* rAminoAcid;
    static ResidueType* rRNA;
    static ResidueType* rDNA;
    static ResidueType* rPhosphate;
    static ResidueType* rPurine; // (R = A || G)
    static ResidueType* rPyrimidine; // (Y = C || U)
    static ResidueType* rRPurine;
    static ResidueType* rRPyrimidine;
    static ResidueType* rDPurine;
    static ResidueType* rDPyrimidine;

    static ResidueType* rW; // (A || U)
    static ResidueType* rS; // (C || G)
    static ResidueType* rM; // (A || C)
    static ResidueType* rK; // (G || U)
    static ResidueType* rB; // (C || G || U || S || Y || K)
    static ResidueType* rD; // (A || G || U || R || W || K)
    static ResidueType* rH; // (A || C || U || M || W || Y)
    static ResidueType* rV; // (A || C || G || M || R || S)

    static ResidueType* rRW;
    static ResidueType* rRS;
    static ResidueType* rRM;
    static ResidueType* rRK;
    static ResidueType* rRB;
    static ResidueType* rRD;
    static ResidueType* rRH;
    static ResidueType* rRV;

    static ResidueType* rDW;
    static ResidueType* rDS;
    static ResidueType* rDM;
    static ResidueType* rDK;
    static ResidueType* rDB;
    static ResidueType* rDD;
    static ResidueType* rDH;
    static ResidueType* rDV;

    static ResidueType* rA;
    static ResidueType* rC;
    static ResidueType* rG;
    static ResidueType* rU;
    static ResidueType* rT;
    static ResidueType* rRA;
    static ResidueType* rRC;
    static ResidueType* rRG;
    static ResidueType* rRU;
    static ResidueType* rDA;
    static ResidueType* rDC;
    static ResidueType* rDG;
    static ResidueType* rDT;

    static ResidueType* rALA;
    static ResidueType* rARG;
    static ResidueType* rASN;
    static ResidueType* rASP;
    static ResidueType* rCYS;
    static ResidueType* rGLN;
    static ResidueType* rGLU;
    static ResidueType* rGLY;
    static ResidueType* rHIS;
    static ResidueType* rILE;
    static ResidueType* rLEU;
    static ResidueType* rLYS;
    static ResidueType* rMET;
    static ResidueType* rPHE;
    static ResidueType* rPRO;
    static ResidueType* rSER;
    static ResidueType* rTHR;
    static ResidueType* rTRP;
    static ResidueType* rTYR;
    static ResidueType* rVAL;
  };

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const ResidueType &t);

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const ResidueType *t);

  /**
   * Inputs the residue type.  The integer type is read and the type object is
   * assigned to the pointer.
   * @param ibs the input binary stream.
   * @param t the residue type pointer to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &in, const ResidueType *&t);
  
  /**
   * Outputs the residue type through a binary stream.  The type is dumped as an
   * integer.
   * @param obs the binary output stream.
   * @param t the type to dump.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &out, const ResidueType *t);
  
}

#endif
