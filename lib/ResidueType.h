//                              -*- Mode: C++ -*- 
// ResidueType.h
// Copyright © 2000-07 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.36 $
// $Id: ResidueType.h,v 1.36 2007-01-14 18:21:12 larosem Exp $
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


#ifndef _mccore_ResidueType_h_
#define _mccore_ResidueType_h_

#include <memory>
#include <iostream>
#include <string>

using namespace std;



namespace mccore
{ 
  class Exception;
  class ResidueTypeStore;
  class iBinstream;
  class oBinstream;
  
  
  
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
   * @version $Id: ResidueType.h,v 1.36 2007-01-14 18:21:12 larosem Exp $
   */
  class ResidueType
  {    
    /**
     * Container for string to type associations.
     */
	  static std::unique_ptr<ResidueTypeStore> rtstore;

    /**
     * The type key string.
     */
    string key;

    /**
     * The type long definition.
     */
    string definition;

  protected: 

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    ResidueType () { }

    /**
     * Initializes the object.
     * @param ks the string representation of the type key.
     * @param ds the long string representation of the type definition.
     */
    ResidueType (const string& ks, const string& ls)
      : key (ks), definition (ls) { }

    /**
     * (Disallow copy constructor) Initializes the object with another
     * residue type.
     * @param other another type.
     */
    ResidueType (const ResidueType &t);

    /**
     * Destroys the object.
     */
    virtual ~ResidueType () { }
    
    /**
     * ResidueTypeStore is a friend since the destructor is private.
     */
    friend class ResidueTypeStore;

  public:
    
    /**
     * @short less comparator on derefenced type pointers
     */
    struct less_deref
    {
      /**
       * Tests whether the first type is less than the second. 
       * @param s1 the first type.
       * @param s2 the second type.
       * @return the result of the test.
       */
      bool operator() (const ResidueType *t1, const ResidueType *t2) const
      {
	return
	  *(0 == t1 ? ResidueType::rNull : t1) <
	  *(0 == t2 ? ResidueType::rNull : t2);
      }
    };
    
    // OPERATORS ---------------------------------------------------------------
    
    /**
     * Indicates whether some other residuetype is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const ResidueType &other) const
    { return key == other.key; }

    /**
     * Indicates whether some other residue is "not equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const ResidueType &other) const 
    {
      return ! operator== (other);
    }

    /**
     * Imposes a total ordering on the ResidueType objects.
     * @param obj the residue type to compare.
     * @return true if this residue type is less than the other.
     */
    bool operator< (const ResidueType &other) const
    {
      return key < other.key;
    }

    bool operator<= (const ResidueType &other) const
    {
      return key < other.key || key == other.key;
    }

    bool operator> (const ResidueType &other) const
    {
      return !operator<= (other);
    }

    bool operator>= (const ResidueType &other) const
    {
      return !operator< (other);
    }

    /**
     * Converts the residuetype into a string.
     * @return the string.
     */
    virtual operator const char* () const
    {
      return key.c_str ();
    }
 
    // METHODS -----------------------------------------------------------------
    
    /**
     * Converts the residuetype into a stl string.
     * @return the string.
     */
    virtual const string& toString () const
    {
      return key;
    }

    /**
     * Converts the residuetype into a long stl  string.
     * @return the string.
     */
    virtual const string& toLongString () const
    {
      return definition;
    }

    /**
     * Identifies the type of residue stored in a string.
     * @param str the c string.
     * @return a residue type for the string.
     */
    static const ResidueType* parseType (const char *str);

    /**
     * Identifies the type of residue stored in a string.
     * @param str the stl string.
     * @return a residue type for the string.
     */
    static const ResidueType* parseType (const string &str);

    /**
     * Invalidates the residue type.  
     * @return a new ResidueType with the current strings as content.
     */
    const ResidueType* invalidate () const;
    
    /**
     * General is method for use when both objects to compare are of
     * unknown type.
     */
    virtual bool is (const ResidueType *t) const
    {
      return t->describe (this);
    }

    /**
     * Tests whether the type t is a ResidueType or derived class.
     * @param the type to test.
     * @return the truth value of the test.
     */
    virtual bool describe (const ResidueType *t) const
    {
      return dynamic_cast< const ResidueType* > (t);
    }

    /**
     * is Null?
     */
    virtual bool isNull () const {
      return false;
    }
    
    /**
     * is Unknown?
     */
    virtual bool isUnknown () const {
      return false;
    }
    
    /**
     * is Amber representation?
     */
    virtual bool isAmber () const {
      return false;
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
     * is Phosphate?
     */
    virtual bool isPhosphate () const {
        return false;
    }

    /**
     * is Ribose?
     */
    virtual bool isRibose () const {
        return false;
    }

    /**
     * is Ribose5?
     */
    virtual bool isRibose5 () const {
        return false;
    }

    /**
     * is Ribose3?
     */
    virtual bool isRibose3 () const {
        return false;
    }

    /**
     * is Ribose53?
     */
    virtual bool isRibose53 () const {
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
    virtual bool isA () const {	
	return false;
    }

    /**
     * Tests wheter the residue type is a C.
     * @return true if the residue type is a C.
     */
    virtual bool isC () const {
	return false;
    }

    /**
     * Tests wheter the residue type is a G.
     * @return true if the residue type is a G.
     */
    virtual bool isG () const {
	return false;
    }

    /**
     * Tests wheter the residue type is a U.
     * @return true if the residue type is a G.
     */
    virtual bool isU () const {
	return false;
    }

    /**
     * Tests wheter the residue type is a T.
     * @return true if the residue type is a T.
     */
    virtual bool isT () const {
	return false;
    }

    /**
     * Finds the least general type for the given residue types.
     * @param aResType1 a residue type.
     * @param aResType2 a residue type.
     * @return the least general type for the given residue types.
     */
    static const ResidueType* generalizeBase (const ResidueType *aResType1, const ResidueType *aResType2);


  public:

    
    // I/O ---------------------------------------------------------------------


    /**
     * Outputs to a stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    ostream& output (ostream &out) const;


    /**
     * Outputs to a binary stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    oBinstream& output (oBinstream &out) const;


  public:


    // TYPE POINTERS -----------------------------------------------------------

    static const ResidueType *rResidue;
    static const ResidueType *rNull;
    static const ResidueType *rUnknown;

    static const ResidueType *rNucleicAcid;
    static const ResidueType *rAminoAcid;

    static const ResidueType *rRNA;
    static const ResidueType *rDNA;

    static const ResidueType *rPhosphate;
    static const ResidueType *rRPhosphate;
    static const ResidueType *rDPhosphate;

    static const ResidueType *rRibose;
    static const ResidueType *rRRibose;
    static const ResidueType *rRRibose5;
    static const ResidueType *rRRibose3;
    static const ResidueType *rRRibose53;
    static const ResidueType *rDRibose;
    static const ResidueType *rDRibose5;
    static const ResidueType *rDRibose3;
    static const ResidueType *rDRibose53;
    
    static const ResidueType *rPurine; // (R = A || G)
    static const ResidueType *rPyrimidine; // (Y = C || U)
    static const ResidueType *rRPurine;
    static const ResidueType *rRPyrimidine;
    static const ResidueType *rDPurine;
    static const ResidueType *rDPyrimidine;

    static const ResidueType *rW; // (A || U)
    static const ResidueType *rS; // (C || G)
    static const ResidueType *rM; // (A || C)
    static const ResidueType *rK; // (G || U)
    static const ResidueType *rB; // (C || G || U || S || Y || K)
    static const ResidueType *rD; // (A || G || U || R || W || K)
    static const ResidueType *rH; // (A || C || U || M || W || Y)
    static const ResidueType *rV; // (A || C || G || M || R || S)

    static const ResidueType *rRW;
    static const ResidueType *rRS;
    static const ResidueType *rRM;
    static const ResidueType *rRK;
    static const ResidueType *rRB;
    static const ResidueType *rRD;
    static const ResidueType *rRH;
    static const ResidueType *rRV;

    static const ResidueType *rDW;
    static const ResidueType *rDS;
    static const ResidueType *rDM;
    static const ResidueType *rDK;
    static const ResidueType *rDB;
    static const ResidueType *rDD;
    static const ResidueType *rDH;
    static const ResidueType *rDV;

    static const ResidueType *rA;
    static const ResidueType *rC;
    static const ResidueType *rG;
    static const ResidueType *rI;
    static const ResidueType *rU;
    static const ResidueType *rT;

    static const ResidueType *rRA;
    static const ResidueType *rRC;
    static const ResidueType *rRG;
    static const ResidueType *rRI;
    static const ResidueType *rRU;
    static const ResidueType *rDA;
    static const ResidueType *rDC;
    static const ResidueType *rDG;
    static const ResidueType *rDI;
    static const ResidueType *rDT;

    static const ResidueType *rALA;
    static const ResidueType *rARG;
    static const ResidueType *rASN;
    static const ResidueType *rASP;
    static const ResidueType *rCYS;
    static const ResidueType *rGLN;
    static const ResidueType *rGLU;
    static const ResidueType *rGLY;
    static const ResidueType *rHIS;
    static const ResidueType *rILE;
    static const ResidueType *rLEU;
    static const ResidueType *rLYS;
    static const ResidueType *rMET;
    static const ResidueType *rPHE;
    static const ResidueType *rPRO;
    static const ResidueType *rSER;
    static const ResidueType *rTHR;
    static const ResidueType *rTRP;
    static const ResidueType *rTYR;
    static const ResidueType *rVAL;
    static const ResidueType *rASX; // (ASN | ASP)
    static const ResidueType *rGLX; // (GLN | GLU)

    // New types.
    //
    static const ResidueType *r1MA;
    static const ResidueType *rR1MA;
    static const ResidueType *rD1MA;
    static const ResidueType *r5MU;
    static const ResidueType *rR5MU;
    static const ResidueType *rD5MU;
    static const ResidueType *rPSU;
    static const ResidueType *rRPSU;
    static const ResidueType *rDPSU;
  };

  /**
   * Outputs to an exception stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception &ex, const ResidueType &t);

  /**
   * Outputs to an exception  stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception &ex, const ResidueType *t);
  
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
   * @exception FatalIntLibException thrown if type is null pointed.
   */
  oBinstream& operator<< (oBinstream &out, const ResidueType *t);
  
}



namespace std
{
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream& operator<< (ostream &out, const mccore::ResidueType &t);

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream& operator<< (ostream &out, const mccore::ResidueType *t);

}

#endif
