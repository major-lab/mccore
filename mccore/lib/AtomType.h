//                              -*- Mode: C++ -*- 
// AtomType.h
// Copyright © 2000-01, 03 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
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


#ifndef _AtomType_h_
#define _AtomType_h_

#include <iostream>
#include <typeinfo>
#include <set>

#include "Vector3D.h"


using namespace std;

class iBinstream;
class oBinstream;

namespace mccore { 

  class Residue;
  class AtomTypeStore;

  

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
   * @version $Id: AtomType.h,v 1.17 2003-10-03 22:40:55 larosem Exp $ 
   */
  class AtomType 
  {
    /**
     * Container for string to type associations.
     */
    static AtomTypeStore atstore;
    
    /**
     * The type.
     */
    char* type;

  protected: 

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    AtomType ();

    /**
     * Initializes the object.
     * @param t the string representation of the type.
     * @param p the set of properties for this type.
     */
    AtomType (const char* t);
    
    /**
     * (Disallow copy constructor) Initializes the object with another atom type.
     * @param other another type.
     */
    AtomType (const AtomType &other);

    /**
     * Destroys the object.
     */
    virtual ~AtomType ();
    
    /**
     * AtomTypeStore is a friend since the destructor is private.
     */
    friend class AtomTypeStore;

  public:

    // FUNCTION OBJECTS --------------------------------------------------------

    /**
     * @short less comparator for Atomtypes.
     */
    struct less
    {
      /**
       * Tests whether the first atomtype is less than the second. 
       * @param s1 the first string.
       * @param s2 the second string.
       * @return the result of the test.
       */
      bool operator() (const AtomType* t1, const AtomType* t2) const
      { return *t1 < *t2; }
    };
    
    // OPERATORS ---------------------------------------------------------------

    /**
     * Indicates whether some other atomtype is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const AtomType &other) const
    { return strcmp (type, other.type) == 0; }

    /**
     * Indicates whether some other atom is "not equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const AtomType &other) const 
    { return ! operator== (other); }

    /**
     * Imposes a total ordering on the AtomType objects.
     * @param obj the atom type to compare.
     * @return true if this atom type is less than the other.
     */
    bool operator< (const AtomType &other) const
    { return strcmp (type, other.type) < 0; }

    // METHODS -----------------------------------------------------------------
    
    /**
     * Converts the atomtype into a string.
     * @return the string.
     */
    virtual operator const char* () const { return type; }
        
    /**
     * Identifies the type of atom stored in a string.
     * @param s the string.
     * @return an atom type for the string.
     */
    static const AtomType* parseType (const char* t);

    
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
     * is Hydrogen?
     */
    virtual bool isHydrogen () const {
      return (getFirstLetter () == 'H');
    }

    /** 
     * is Carbon?
     */
    virtual bool isCarbon () const {
      return (getFirstLetter () == 'C');
    }
    
    /** 
     * is Nitrogen?
     */
    virtual bool isNitrogen () const {
      return (getFirstLetter () == 'N');
    }
    
    /** 
     * is Phosphate?
     */
    virtual bool isPhosphate () const {
      return (getFirstLetter () == 'P' && !isPseudo ());
    }
    
    /** 
     * is Oxygen?
     */
    virtual bool isOxygen () const {
      return (getFirstLetter () == 'O');
    }

    /** 
     * is Sulfur?
     */
    virtual bool isSulfur () const {
      return (getFirstLetter () == 'S');
    }
    
    /** 
     * is Lone pair?
     */
    virtual bool isLonePair () const {
      return (getFirstLetter () == 'L');
    }
    
    /** 
     * is Magnesium?
     */
    virtual bool isMagnesium () const {
      return (getFirstLetter () == 'M');
    }
    
    /** 
     * is Pseudo?
     */
    virtual bool isPseudo () const {
      return (strlen (type) > 1 && type[0] == 'P' && type[1] == 'S');
    }
    
    /**
     * is Backbone?
     */
    virtual bool isBackbone () const {
      return false;
    }

    /**
     * is Side Chain?
     */
    virtual bool isSideChain () const {
      return false;
    }

    /**
     * is Unknown?  
     */
    virtual bool isUnknown () const {
      return (typeid (*this) == typeid (AtomType));
    }
        
    /**
     * Gets the Van Der Waals radius value for the atom.
     * @param res the residue that contains the atom.
     * @return the Van Der Waals radius value.
     */
    virtual float getVDWR (const Residue *res) const { return 0; }
    
    /**
     * Gets the Amber epsilon value for the atom.
     * @param res the residue that contains the atom.
     * @return the Amber epsilon value.
     */
    virtual float getAmberEpsilon (const Residue *res) const { return 0; }
    
    /**
     * Gets the Amber charge value for the atom in the given residue type.
     * @param res the residue type.
     * @return the Amber charge.
     */
    virtual float getAmberCharge (const Residue *res) const { return 0; }

    /**
     * Gets the color of the atom type.
     * @param type the atom type.
     * @return the Vector3D color in RGB format.
     */
    static Vector3D getColor (const AtomType *type);
    
  private:

    // PRIVATE METHODS ---------------------------------------------------------
    
    /**
     * Identifies the first letter in the type.
     * @return the letter.
     */
    char getFirstLetter () const;
 
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

    static AtomType* aC1p;
    static AtomType* aC2p;
    static AtomType* aC3p;
    static AtomType* aC4p;
    static AtomType* aC5p;
    static AtomType* aH1p;
    static AtomType* aH2p;
    static AtomType* aH3p;
    static AtomType* aH4p;
    static AtomType* aH5p;
    static AtomType* aO1P;
    static AtomType* aO2p;
    static AtomType* aO2P;
    static AtomType* aO3p;
    static AtomType* aO3P;
    static AtomType* aO4p;
    static AtomType* aO5p;
    static AtomType* aP;
    static AtomType* a1H2p;
    static AtomType* a1H5p;
    static AtomType* a2H2p;
    static AtomType* a2H5p;
    static AtomType* aHO2p;
    static AtomType* aHO3p;
    static AtomType* aC2;
    static AtomType* aC4;
    static AtomType* aC5;
    static AtomType* aC5M;
    static AtomType* aC6;
    static AtomType* aC8;
    static AtomType* aH1;
    static AtomType* aH2;
    static AtomType* aH3;
    static AtomType* aH5;
    static AtomType* aH6;
    static AtomType* aH7;
    static AtomType* aH8;
    static AtomType* aN1;
    static AtomType* aN2;
    static AtomType* aN3;
    static AtomType* aN4;
    static AtomType* aN6;
    static AtomType* aN7;
    static AtomType* aN9;
    static AtomType* aO2;
    static AtomType* aO4;
    static AtomType* aO6;
    static AtomType* a1H2;
    static AtomType* a1H4;
    static AtomType* a1H5M;
    static AtomType* a1H6;
    static AtomType* a2H2;
    static AtomType* a2H4;
    static AtomType* a2H5M;
    static AtomType* a2H6;
    static AtomType* a3H5M;
    static AtomType* aPSY;
    static AtomType* aPSZ;
    static AtomType* aLP1;
    static AtomType* aLP3;
    static AtomType* aLP7;
    static AtomType* a1LP2;
    static AtomType* a1LP4;
    static AtomType* a1LP6;
    static AtomType* a2LP2;
    static AtomType* a2LP4;
    static AtomType* a2LP6;
    static AtomType* aH3T;
    static AtomType* aH5T;
    static AtomType* aC;
    static AtomType* aCA;
    static AtomType* aCB;
    static AtomType* aCD;
    static AtomType* aCD1;
    static AtomType* aCD2;
    static AtomType* aCE;
    static AtomType* aCE1;
    static AtomType* aCE2;
    static AtomType* aCE3;
    static AtomType* aCG;
    static AtomType* aCG1;
    static AtomType* aCG2;
    static AtomType* aCH2;
    static AtomType* aCZ;
    static AtomType* aCZ2;
    static AtomType* aCZ3;
    static AtomType* aH;
    static AtomType* a1H;
    static AtomType* a2H;
    static AtomType* a3H;
    static AtomType* aHA;
    static AtomType* aHA1;
    static AtomType* aHA2;
    static AtomType* aHB;
    static AtomType* aHB1;
    static AtomType* aHB2;
    static AtomType* aHB3;
    static AtomType* aHD1;
    static AtomType* aHD2;
    static AtomType* aHE;
    static AtomType* aHE1;
    static AtomType* aHE2;
    static AtomType* aHE3;
    static AtomType* aHG;
    static AtomType* aHG1;
    static AtomType* aHG2;
    static AtomType* aHH;
    static AtomType* aHH2;
    static AtomType* aHXT;
    static AtomType* aHZ;
    static AtomType* aHZ1;
    static AtomType* aHZ2;
    static AtomType* aHZ3;
    static AtomType* aN;
    static AtomType* aND1;
    static AtomType* aND2;
    static AtomType* aNE;
    static AtomType* aNE1;
    static AtomType* aNE2;
    static AtomType* aNH1;
    static AtomType* aNH2;
    static AtomType* aNZ;
    static AtomType* aO;
    static AtomType* aOD1;
    static AtomType* aOD2;
    static AtomType* aOE1;
    static AtomType* aOE2;
    static AtomType* aOG;
    static AtomType* aOG1;
    static AtomType* aOH;
    static AtomType* aOXT;
    static AtomType* aSD;
    static AtomType* aSG;
    static AtomType* a1HD1;
    static AtomType* a1HD2;
    static AtomType* a1HE2;
    static AtomType* a1HG1;
    static AtomType* a1HG2;
    static AtomType* a1HH1;
    static AtomType* a1HH2;
    static AtomType* a2HD1;
    static AtomType* a2HD2;
    static AtomType* a2HE2;
    static AtomType* a2HG1;
    static AtomType* a2HG2;
    static AtomType* a2HH1;
    static AtomType* a2HH2;
    static AtomType* a3HD1;
    static AtomType* a3HD2;
    static AtomType* a3HG1;
    static AtomType* a3HG2;
    static AtomType* aMG;
    static AtomType* aPSAZ;
  };
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const AtomType &a);

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const AtomType *a);

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
   */
  oBinstream& operator<< (oBinstream &out, const AtomType *t);
  
}

#endif
