//                              -*- Mode: C++ -*- 
// AtomType.h
// Copyright © 2000-07 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.37 $
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


#ifndef _mccore_AtomType_h_
#define _mccore_AtomType_h_


#include <iostream>
#include <memory>
#include <string>

#include "Vector3D.h"

using namespace std;



namespace mccore
{
  class AtomTypeStore;
  class ResidueType;
  class Exception;
  class iBinstream;
  class oBinstream;
  
  
  
  /**
   * @short Atom types.
   *
   * <br>
   * Implicit information:<br>
   *   - Mapping from string to actual type.<br>
   *   - The chemical nature of each type.<br>
   *   - The localization of each atom type (backbone or sidechain)<br>
   *   - The charge and van der Waals radius<br>
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>
   * @version $Id: AtomType.h,v 1.37 2007-01-14 18:21:02 larosem Exp $ 
   */
  class AtomType 
  {
    /**
     * Container for string to type associations.
     */
    static std::unique_ptr<AtomTypeStore> atstore;

    /**
     * The type key string.
     */
    string key;

  protected: 

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    AtomType () { }

    /**
     * Initializes the object.
     * @param ks the string representation of the type key.
     */
    AtomType (const string& ks) : key (ks) { }
    
    /**
     * (Disallow copy constructor) Initializes the object with another atom type.
     * @param other another type.
     */
    AtomType (const AtomType &other);

    /**
     * Destroys the object.
     */
    virtual ~AtomType () { }
    
    /**
     * AtomTypeStore is a friend since the destructor is private.
     */
    friend class AtomTypeStore;

  public:

    /**
     * @short less comparator on derefenced type pointers
     */
    struct less_deref
    {
      /**
       * Tests whether the first atomtype is less than the second. 
       * @param s1 the first string.
       * @param s2 the second string.
       * @return the result of the test.
       */
      bool operator() (const AtomType* t1, const AtomType* t2) const
      {
	return
	  *(0 == t1 ? AtomType::aNull : t1) <
	  *(0 == t2 ? AtomType::aNull : t2);
      }
    };
    
    // OPERATORS ---------------------------------------------------------------

    /**
     * Indicates whether some other atomtype is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const AtomType &other) const
    {
      return this->key == other.key;
    }

    /**
     * Indicates whether some other atom is "not equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const AtomType &other) const 
    {
      return ! operator== (other);
    }

    /**
     * Imposes a total ordering on the AtomType objects.
     * @param obj the atom type to compare.
     * @return true if this atom type is less than the other.
     */
    bool operator< (const AtomType &other) const
    {
      return this->key < other.key;
    }

    bool operator<= (const AtomType &other) const
    {
      return this->key < other.key || this->key == other.key;
    }

    bool operator> (const AtomType &other) const
    {
      return !this->operator<= (other);
    }

    bool operator>= (const AtomType &other) const
    {
      return !this->operator< (other);
    }

    /**
     * Converts the atomtype into a string.
     * @return the string.
     */
    virtual operator const char* () const
    {
      return this->key.c_str ();
    }
        
    // METHODS -----------------------------------------------------------------

    /**
     * Converts the residuetype into a stl string.
     * @return the string.
     */
    virtual const string& toString () const
    {
      return this->key;
    }
    
    /**
     * Identifies the type of atom stored in a string.
     * @param str the c string.
     * @return an atom type for the string.
     */
    static const AtomType* parseType (const char* str);

    /**
     * Identifies the type of atom stored in a string.
     * @param str the stl string.
     * @return an atom type for the string.
     */
    static const AtomType* parseType (const string& str);

    /**
     * General is method for use when both objects to compare are of
     * unknown type.
     */
    virtual bool is (const AtomType *t) const {
      return t->describe (this);
    }

    /**
     * Tests whether the type t is an AtomType or derived class.
     * @param the type to test.
     * @return the truth value of the test.
     */
    virtual bool describe (const AtomType *t) const {
      return dynamic_cast< const AtomType* > (t);
    }
    
    /**
     * is Null?
     */
    virtual bool isNull() const {
      return false;
    }
    
    /**
     * is Unknown?
     */
    virtual bool isUnknown() const {
      return false;
    }
       
    /** 
     * is NucleicAcid?
     */
    virtual bool isNucleicAcid () const {
      return false;
    }

    /** 
     * is AminoAcid?
     */
    virtual bool isAminoAcid () const {
      return false;
    }
    
    /**
     * is Backbone?
     */
    virtual bool isBackbone () const {
      return false;
    }

    /** 
     * is Phosphate?
     */
    virtual bool isPhosphate () const {
      return false;
    }
    
    
    /**
     * is Side Chain?
     */
    virtual bool isSideChain () const {
      return false;
    }
    
    /** 
     * is Hydrogen?
     */
    virtual bool isHydrogen () const {
      return false;
    }

    /** 
     * is Carbon?
     */
    virtual bool isCarbon () const {
      return false;
    }
    
    /** 
     * is Nitrogen?
     */
    virtual bool isNitrogen () const {
      return false;
    }
    
    /** 
     * is Phosphorus?
     */
    virtual bool isPhosphorus () const {
      return false;
    }
    
    /** 
     * is Oxygen?
     */
    virtual bool isOxygen () const {
      return false;
    }

    /** 
     * is Sulfur?
     */
    virtual bool isSulfur () const {
      return false;
    }
    
    /** 
     * is Lone pair?
     */
    virtual bool isLonePair () const {
      return false;
    }

    /** 
     * is Pseudo?
     */
    virtual bool isPseudo () const {
      return false;
    }
    
    /** 
     * is Magnesium?
     */
    virtual bool isMagnesium () const {
      return false;
    }
            
    /**
     * Gets the Van Der Waals radius value for the atom.
     * @param res the residue that contains the atom.
     * @return the Van Der Waals radius value.
     */
    virtual float getVDWR (const ResidueType *r) const { return 0; }
    
    /**
     * Gets the Amber epsilon value for the atom.
     * @param res the residue that contains the atom.
     * @return the Amber epsilon value.
     */
    virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
    
    /**
     * Gets the Amber charge value for the atom in the given residue type.
     * @param res the residue type.
     * @return the Amber charge.
     */
    virtual float getAmberCharge (const ResidueType *r) const { return 0; }

    /**
     * Gets the color of the atom type.
     * @param type the atom type.
     * @return the Vector3D color in RGB format.
     */
    virtual Vector3D getColor () const {
      return Vector3D (0.10, 0.10, 0.10);
    }
    
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
  
  
    /**
     * Add mapping for atom name to defined atom named. To support non standard 
     * atom naming.
     * @param key The alternate name of the atom.
     * @param apType The already defined AtomType to which to map the name.
     */
    static void AddMapping(const std::string& key, const AtomType* apType);

    // TYPE POINTERS -----------------------------------------------------------

    static const AtomType *aNull;
    static const AtomType *aUnknown;
    static const AtomType *aC1p;
    static const AtomType *aC2p;
    static const AtomType *aC3p;
    static const AtomType *aC4p;
    static const AtomType *aC5p;
    static const AtomType *aH1p;
    static const AtomType *aH2p;
    static const AtomType *aH3p;
    static const AtomType *aH4p;
    static const AtomType *aH5p;
    static const AtomType *aO1P;
    static const AtomType *aO2p;
    static const AtomType *aO2P;
    static const AtomType *aO3p;
    static const AtomType *aO3P;
    static const AtomType *aO4p;
    static const AtomType *aO5p;
    static const AtomType *aP;
    static const AtomType *a1H2p;
    static const AtomType *a1H5p;
    static const AtomType *a2H2p;
    static const AtomType *a2H5p;
    static const AtomType *aHO2p;
    static const AtomType *aHO3p;
    static const AtomType *aC2;
    static const AtomType *aC4;
    static const AtomType *aC5;
    static const AtomType *aC5M;
    static const AtomType *aC6;
    static const AtomType *aC8;
    static const AtomType *aH1;
    static const AtomType *aH2;
    static const AtomType *aH3;
    static const AtomType *aH5;
    static const AtomType *aH6;
    static const AtomType *aH7;
    static const AtomType *aH8;
    static const AtomType *aN1;
    static const AtomType *aN2;
    static const AtomType *aN3;
    static const AtomType *aN4;
    static const AtomType *aN6;
    static const AtomType *aN7;
    static const AtomType *aN9;
    static const AtomType *aO2;
    static const AtomType *aO4;
    static const AtomType *aO6;
    static const AtomType *a1H2;
    static const AtomType *a1H4;
    static const AtomType *a1H5M;
    static const AtomType *a1H6;
    static const AtomType *a2H2;
    static const AtomType *a2H4;
    static const AtomType *a2H5M;
    static const AtomType *a2H6;
    static const AtomType *a3H5M;
    static const AtomType *aPSX;
    static const AtomType *aPSY;
    static const AtomType *aPSZ;
    static const AtomType *aPSO;
    static const AtomType *aLP1;
    static const AtomType *aLP3;
    static const AtomType *aLP7;
    static const AtomType *a1LP2;
    static const AtomType *a1LP4;
    static const AtomType *a1LP6;
    static const AtomType *a2LP2;
    static const AtomType *a2LP4;
    static const AtomType *a2LP6;
    static const AtomType *aH3T;
    static const AtomType *aH5T;
    static const AtomType *aC;
    static const AtomType *aCA;
    static const AtomType *aCB;
    static const AtomType *aCD;
    static const AtomType *aCD1;
    static const AtomType *aCD2;
    static const AtomType *aCE;
    static const AtomType *aCE1;
    static const AtomType *aCE2;
    static const AtomType *aCE3;
    static const AtomType *aCG;
    static const AtomType *aCG1;
    static const AtomType *aCG2;
    static const AtomType *aCH2;
    static const AtomType *aCZ;
    static const AtomType *aCZ2;
    static const AtomType *aCZ3;
    static const AtomType *aH;
    static const AtomType *a1H;
    static const AtomType *a2H;
    static const AtomType *a3H;
    static const AtomType *aHA;
    static const AtomType *aHA1;
    static const AtomType *aHA2;
    static const AtomType *aHB;
    static const AtomType *aHB1;
    static const AtomType *aHB2;
    static const AtomType *aHB3;
    static const AtomType *aHD1;
    static const AtomType *aHD2;
    static const AtomType *aHE;
    static const AtomType *aHE1;
    static const AtomType *aHE2;
    static const AtomType *aHE3;
    static const AtomType *aHG;
    static const AtomType *aHG1;
    static const AtomType *aHG2;
    static const AtomType *aHH;
    static const AtomType *aHH2;
    static const AtomType *aHXT;
    static const AtomType *aHZ;
    static const AtomType *aHZ1;
    static const AtomType *aHZ2;
    static const AtomType *aHZ3;
    static const AtomType *aN;
    static const AtomType *aND1;
    static const AtomType *aND2;
    static const AtomType *aNE;
    static const AtomType *aNE1;
    static const AtomType *aNE2;
    static const AtomType *aNH1;
    static const AtomType *aNH2;
    static const AtomType *aNZ;
    static const AtomType *aO;
    static const AtomType *aOD1;
    static const AtomType *aOD2;
    static const AtomType *aOE1;
    static const AtomType *aOE2;
    static const AtomType *aOG;
    static const AtomType *aOG1;
    static const AtomType *aOH;
    static const AtomType *aOXT;
    static const AtomType *aSD;
    static const AtomType *aSG;
    static const AtomType *a1HD1;
    static const AtomType *a1HD2;
    static const AtomType *a1HE2;
    static const AtomType *a1HG1;
    static const AtomType *a1HG2;
    static const AtomType *a1HH1;
    static const AtomType *a1HH2;
    static const AtomType *a2HD1;
    static const AtomType *a2HD2;
    static const AtomType *a2HE2;
    static const AtomType *a2HG1;
    static const AtomType *a2HG2;
    static const AtomType *a2HH1;
    static const AtomType *a2HH2;
    static const AtomType *a3HD1;
    static const AtomType *a3HD2;
    static const AtomType *a3HG1;
    static const AtomType *a3HG2;
    static const AtomType *aMG;
    static const AtomType *aPSAZ;

    // New AtomType (some are invalid type names due to their notation in
    // the components.cif.gz file
    //
    static const AtomType *a1HM1;
    static const AtomType *a1HN6;
    static const AtomType *a2HM1;
    static const AtomType *a2HN6;
    static const AtomType *a3HM1;
    static const AtomType *aCM1;
  };
  
  /**
   * Outputs to an exception stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception& ex, const AtomType &t);

  /**
   * Outputs to an exception  stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception& ex, const AtomType *t);
  
  /**
   * Inputs the atom type.  The integer type is read and the type object is
   * assigned to the pointer.
   * @param ibs the input binary stream.
   * @param t the atom type pointer to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &in, const AtomType *&t);
  
  /**
   * Outputs the atom type through a binary stream.  The type is dumped as an
   * integer.
   * @param obs the binary output stream.
   * @param t the type to dump.
   * @return the output binary stream used.
   * @exception FatalIntLibException thrown if type is null pointed.
   */
  oBinstream& operator<< (oBinstream &out, const AtomType *t);
  
}



namespace std
{
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::AtomType &a);

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::AtomType *a);

}

#endif
