//                              -*- Mode: C++ -*- 
// AtomTypeStore.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 12:30:39 2003
// $Revision: 1.3 $
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

#ifndef _AtomTypeStore_h_
#define _AtomTypeStore_h_

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include <string>

#include "AtomType.h"

using namespace std;

namespace mccore { 

  /**
   * @short Repository of atomtypes.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: AtomTypeStore.h,v 1.3 2003-07-11 21:27:13 gendrop Exp $
   */
  class AtomTypeStore
  {
    /**
     * @short less comparator for strings.
     */
    struct less_string
    {
      /**
       * Tests whether the first string is lexicographically less than the
       * second one.
       * @param s1 the first string.
       * @param s2 the second string.
       * @return the result of the test.
       */
      bool operator() (const char* s1, const char* s2) const
      { return strcmp (s1, s2) < 0; }
    };
    
    /**
     * Container for string to type associations.
     */
    map< const char*, AtomType*, less_string > stringType;

  public:

    // LIFECYCLE ---------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomTypeStore ();
    
    /**
     * Destroys the object.  No deletion is done on the char* since it
     * is no known it is a string constant or an allocated string.
     * This is not too bad since types should live for as long as the
     * program runs.  (Note that we could use the C++ string class but
     * this increases compilation time by a factor 3).  NEWS: The get
     * function now uses the string found in the type as key to the
     * map and there are thus no more memory leaks.
     */
    ~AtomTypeStore ();

    // METHODS -----------------------------------------------------------------
    
    /**
     * Gets the atomtype represented by the string if one exists.
     * @return the matching atom type or a new one if none existed.
     */
    const AtomType* get (const char* s);

  private:
    
    // TYPES -------------------------------------------------------------------

    /**
     * Private abstract class for amino acid atoms.
     */
    class AminoAcid : public virtual AtomType {
    public:      
      AminoAcid () {}
      AminoAcid (const char* t) : AtomType (t) {}

      virtual bool isAminoAcid () const { return true; }
    };
    
    /**
     * Private abstract class for nucleic acid atoms.
     */
    class NucleicAcid : public virtual AtomType {
    public:
      NucleicAcid () {}
      NucleicAcid (const char* t) : AtomType (t) {}

      virtual bool isNucleicAcid () const { return true; }
    };

    /**
     * Private abstract class for backbone atoms.
     */
    class Backbone : public virtual AtomType {
    public:
      Backbone () {}
      Backbone (const char* t) : AtomType (t) {}

      virtual bool isBackbone () const { return true; }
    };

    /**
     * Private abstract class for sidechain atoms.
     */
    class SideChain : public virtual AtomType {
    public:
      SideChain () {}
      SideChain (const char* t) : AtomType (t) {}

      virtual bool isSideChain () const { return true; }
    };

    /**
     * Private abstract class for carbon atoms.
     */
    class Carbon : public virtual AtomType {
    public:
      Carbon () {}
      Carbon (const char* t) : AtomType (t) {}

      virtual bool isCarbon () const { return true; }
    };

    /**
     * Private abstract class for hydrogen atoms.
     */
    class Hydrogen : public virtual AtomType {
    public:
      Hydrogen () {}
      Hydrogen (const char* t) : AtomType (t) {}

      virtual bool isHydrogen () const { return true; }
    };

    /**
     * Private abstract class for lonepair atoms.
     */
    class LonePair : public virtual AtomType {
    public:
      LonePair () {}
      LonePair (const char* t) : AtomType (t) {}

      virtual bool isLonePair () const { return true; }
    };

    /**
     * Private abstract class for magnesium atoms.
     */
    class Magnesium : public virtual AtomType {
    public:
      Magnesium () {}
      Magnesium (const char* t) : AtomType (t) {}

      virtual bool isMagnesium () const { return true; }
    };

    /**
     * Private abstract class for nitrogen atoms.
     */
    class Nitrogen : public virtual AtomType {
    public:
      Nitrogen () {}
      Nitrogen (const char* t) : AtomType (t) {}

      virtual bool isNitrogen () const { return true; }
    };

    /**
     * Private abstract class for oxygen atoms.
     */
    class Oxygen : public virtual AtomType {
    public:
      Oxygen () {}
      Oxygen (const char* t) : AtomType (t) {}

      virtual bool isOxygen () const { return true; }
    };

    /**
     * Private abstract class for phosphate atoms.
     */
    class Phosphate : public virtual AtomType {
    public:
      Phosphate () {}
      Phosphate (const char* t) : AtomType (t) {}

      virtual bool isPhosphate () const { return true; }
    };

    /**
     * Private abstract class for pseudo atoms.
     */
    class Pseudo : public virtual AtomType {
    public:
      Pseudo () {}
      Pseudo (const char* t) : AtomType (t) {}

      virtual bool isPseudo () const { return true; }
    };

    /**
     * Private abstract class for sulfur atoms.
     */
    class Sulfur : public virtual AtomType {
    public:
      Sulfur () {}
      Sulfur (const char* t) : AtomType (t) {}

      virtual bool isSulfur () const { return true; }
    };

    /**
     * Global C1p atom type class.
     */
    class AC1p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC1p () {}
      AC1p (const char* t) : AtomType (t) {}
    };

    /**
     * Global C2p atom type class.
     */
    class AC2p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC2p () {}
      AC2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C3p atom type class.
     */
    class AC3p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC3p () {}
      AC3p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C4p atom type class.
     */
    class AC4p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC4p () {}
      AC4p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C5p atom type class.
     */
    class AC5p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC5p () {}
      AC5p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H1p atom type class.
     */
    class AH1p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH1p () {}
      AH1p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H2p atom type class.
     */
    class AH2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH2p () {}
      AH2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H3p atom type class.
     */
    class AH3p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH3p () {}
      AH3p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H4p atom type class.
     */
    class AH4p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH4p () {}
      AH4p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H5p atom type class.
     */
    class AH5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH5p () {}
      AH5p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O1P atom type class.
     */
    class AO1P : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO1P () {}
      AO1P (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O2p atom type class.
     */
    class AO2p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO2p () {}
      AO2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O2P atom type class.
     */
    class AO2P : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO2P () {}
      AO2P (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O3p atom type class.
     */
    class AO3p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO3p () {}
      AO3p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O3P atom type class.
     */
    class AO3P : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO3P () {}
      AO3P (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O4p atom type class.
     */
    class AO4p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO4p () {}
      AO4p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O5p atom type class.
     */
    class AO5p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO5p () {}
      AO5p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global P atom type class.
     */
    class AP : public virtual NucleicAcid, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AP () {}
      AP (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H2p atom type class.
     */
    class A1H2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H2p () {}
      A1H2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H5p atom type class.
     */
    class A1H5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H5p () {}
      A1H5p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H2p atom type class.
     */
    class A2H2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H2p () {}
      A2H2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H5p atom type class.
     */
    class A2H5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H5p () {}
      A2H5p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HO2p atom type class.
     */
    class AHO2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHO2p () {}
      AHO2p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HO3p atom type class.
     */
    class AHO3p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHO3p () {}
      AHO3p (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C2 atom type class.
     */
    class AC2 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC2 () {}
      AC2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C4 atom type class.
     */
    class AC4 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC4 () {}
      AC4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C5 atom type class.
     */
    class AC5 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC5 () {}
      AC5 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C5M atom type class.
     */
    class AC5M : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC5M () {}
      AC5M (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C6 atom type class.
     */
    class AC6 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC6 () {}
      AC6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C8 atom type class.
     */
    class AC8 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC8 () {}
      AC8 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H1 atom type class.
     */
    class AH1 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH1 () {}
      AH1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H2 atom type class.
     */
    class AH2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH2 () {}
      AH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H3 atom type class.
     */
    class AH3 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH3 () {}
      AH3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H5 atom type class.
     */
    class AH5 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH5 () {}
      AH5 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H6 atom type class.
     */
    class AH6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH6 () {}
      AH6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H7 atom type class.
     */
    class AH7 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH7 () {}
      AH7 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H8 atom type class.
     */
    class AH8 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH8 () {}
      AH8 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N1 atom type class.
     */
    class AN1 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN1 () {}
      AN1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N2 atom type class.
     */
    class AN2 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN2 () {}
      AN2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N3 atom type class.
     */
    class AN3 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN3 () {}
      AN3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N4 atom type class.
     */
    class AN4 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN4 () {}
      AN4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N6 atom type class.
     */
    class AN6 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN6 () {}
      AN6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N7 atom type class.
     */
    class AN7 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN7 () {}
      AN7 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N9 atom type class.
     */
    class AN9 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN9 () {}
      AN9 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O2 atom type class.
     */
    class AO2 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO2 () {}
      AO2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O4 atom type class.
     */
    class AO4 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO4 () {}
      AO4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O6 atom type class.
     */
    class AO6 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO6 () {}
      AO6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H2 atom type class.
     */
    class A1H2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H2 () {}
      A1H2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H4 atom type class.
     */
    class A1H4 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H4 () {}
      A1H4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H5M atom type class.
     */
    class A1H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H5M () {}
      A1H5M (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H6 atom type class.
     */
    class A1H6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H6 () {}
      A1H6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H2 atom type class.
     */
    class A2H2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H2 () {}
      A2H2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H4 atom type class.
     */
    class A2H4 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H4 () {}
      A2H4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H5M atom type class.
     */
    class A2H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H5M () {}
      A2H5M (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H6 atom type class.
     */
    class A2H6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H6 () {}
      A2H6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3H5M atom type class.
     */
    class A3H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3H5M () {}
      A3H5M (const char*  t) : AtomType (t) {}
    };

    /**
     * Global PSY atom type class.
     */
    class APSY : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSY () {}
      APSY (const char*  t) : AtomType (t) {}
    };

    /**
     * Global PSZ atom type class.
     */
    class APSZ : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSZ () {}
      APSZ (const char*  t) : AtomType (t) {}
    };

    /**
     * Global LP1 atom type class.
     */
    class ALP1 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP1 () {}
      ALP1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global LP3 atom type class.
     */
    class ALP3 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP3 () {}
      ALP3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global LP7 atom type class.
     */
    class ALP7 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP7 () {}
      ALP7 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1LP2 atom type class.
     */
    class A1LP2 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP2 () {}
      A1LP2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1LP4 atom type class.
     */
    class A1LP4 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP4 () {}
      A1LP4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1LP6 atom type class.
     */
    class A1LP6 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP6 () {}
      A1LP6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2LP2 atom type class.
     */
    class A2LP2 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP2 () {}
      A2LP2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2LP4 atom type class.
     */
    class A2LP4 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP4 () {}
      A2LP4 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2LP6 atom type class.
     */
    class A2LP6 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP6 () {}
      A2LP6 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H3T atom type class.
     */
    class AH3T : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH3T () {}
      AH3T (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H5T atom type class.
     */
    class AH5T : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH5T () {}
      AH5T (const char*  t) : AtomType (t) {}
    };

    /**
     * Global C atom type class.
     */
    class AC : public virtual AminoAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC () {}
      AC (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CA atom type class.
     */
    class ACA : public virtual AminoAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      ACA () {}
      ACA (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CB atom type class.
     */
    class ACB : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACB () {}
      ACB (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CD atom type class.
     */
    class ACD : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD () {}
      ACD (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CD1 atom type class.
     */
    class ACD1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD1 () {}
      ACD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CD2 atom type class.
     */
    class ACD2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD2 () {}
      ACD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CE atom type class.
     */
    class ACE : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE () {}
      ACE (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CE1 atom type class.
     */
    class ACE1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE1 () {}
      ACE1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CE2 atom type class.
     */
    class ACE2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE2 () {}
      ACE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CE3 atom type class.
     */
    class ACE3 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE3 () {}
      ACE3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CG atom type class.
     */
    class ACG : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG () {}
      ACG (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CG1 atom type class.
     */
    class ACG1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG1 () {}
      ACG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CG2 atom type class.
     */
    class ACG2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG2 () {}
      ACG2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CH2 atom type class.
     */
    class ACH2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACH2 () {}
      ACH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CZ atom type class.
     */
    class ACZ : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ () {}
      ACZ (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CZ2 atom type class.
     */
    class ACZ2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ2 () {}
      ACZ2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global CZ3 atom type class.
     */
    class ACZ3 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ3 () {}
      ACZ3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global H atom type class.
     */
    class AH : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH () {}
      AH (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1H atom type class.
     */
    class A1H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H () {}
      A1H (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2H atom type class.
     */
    class A2H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H () {}
      A2H (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3H atom type class.
     */
    class A3H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A3H () {}
      A3H (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HA atom type class.
     */
    class AHA : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA () {}
      AHA (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HA1 atom type class.
     */
    class AHA1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA1 () {}
      AHA1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HA2 atom type class.
     */
    class AHA2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA2 () {}
      AHA2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HB atom type class.
     */
    class AHB : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB () {}
      AHB (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HB1 atom type class.
     */
    class AHB1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB1 () {}
      AHB1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HB2 atom type class.
     */
    class AHB2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB2 () {}
      AHB2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HB3 atom type class.
     */
    class AHB3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB3 () {}
      AHB3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HD1 atom type class.
     */
    class AHD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHD1 () {}
      AHD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HD2 atom type class.
     */
    class AHD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHD2 () {}
      AHD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HE atom type class.
     */
    class AHE : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE () {}
      AHE (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HE1 atom type class.
     */
    class AHE1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE1 () {}
      AHE1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HE2 atom type class.
     */
    class AHE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE2 () {}
      AHE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HE3 atom type class.
     */
    class AHE3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE3 () {}
      AHE3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HG atom type class.
     */
    class AHG : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG () {}
      AHG (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HG1 atom type class.
     */
    class AHG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG1 () {}
      AHG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HG2 atom type class.
     */
    class AHG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG2 () {}
      AHG2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HH atom type class.
     */
    class AHH : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHH () {}
      AHH (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HH2 atom type class.
     */
    class AHH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHH2 () {}
      AHH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HXT atom type class.
     */
    class AHXT : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHXT () {}
      AHXT (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HZ atom type class.
     */
    class AHZ : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ () {}
      AHZ (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HZ1 atom type class.
     */
    class AHZ1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ1 () {}
      AHZ1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HZ2 atom type class.
     */
    class AHZ2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ2 () {}
      AHZ2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global HZ3 atom type class.
     */
    class AHZ3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ3 () {}
      AHZ3 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global N atom type class.
     */
    class AN : public virtual AminoAcid, public virtual Nitrogen, public virtual Backbone
    { 
    public:
      AN () {}
      AN (const char*  t) : AtomType (t) {}
    };

    /**
     * Global ND1 atom type class.
     */
    class AND1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AND1 () {}
      AND1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global ND2 atom type class.
     */
    class AND2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AND2 () {}
      AND2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NE atom type class.
     */
    class ANE : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE () {}
      ANE (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NE1 atom type class.
     */
    class ANE1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE1 () {}
      ANE1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NE2 atom type class.
     */
    class ANE2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE2 () {}
      ANE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NH1 atom type class.
     */
    class ANH1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANH1 () {}
      ANH1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NH2 atom type class.
     */
    class ANH2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANH2 () {}
      ANH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global NZ atom type class.
     */
    class ANZ : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANZ () {}
      ANZ (const char*  t) : AtomType (t) {}
    };

    /**
     * Global O atom type class.
     */
    class AO : public virtual AminoAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO () {}
      AO (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OD1 atom type class.
     */
    class AOD1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOD1 () {}
      AOD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OD2 atom type class.
     */
    class AOD2 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOD2 () {}
      AOD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OE1 atom type class.
     */
    class AOE1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOE1 () {}
      AOE1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OE2 atom type class.
     */
    class AOE2 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOE2 () {}
      AOE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OG atom type class.
     */
    class AOG : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOG () {}
      AOG (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OG1 atom type class.
     */
    class AOG1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOG1 () {}
      AOG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OH atom type class.
     */
    class AOH : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOH () {}
      AOH (const char*  t) : AtomType (t) {}
    };

    /**
     * Global OXT atom type class.
     */
    class AOXT : public virtual AminoAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AOXT () {}
      AOXT (const char*  t) : AtomType (t) {}
    };

    /**
     * Global SD atom type class.
     */
    class ASD : public virtual AminoAcid, public virtual Sulfur, public virtual SideChain
    { 
    public:
      ASD () {}
      ASD (const char*  t) : AtomType (t) {}
    };

    /**
     * Global SG atom type class.
     */
    class ASG : public virtual AminoAcid, public virtual Sulfur, public virtual SideChain
    { 
    public:
      ASG () {}
      ASG (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HD1 atom type class.
     */
    class A1HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HD1 () {}
      A1HD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HD2 atom type class.
     */
    class A1HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HD2 () {}
      A1HD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HE2 atom type class.
     */
    class A1HE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HE2 () {}
      A1HE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HG1 atom type class.
     */
    class A1HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HG1 () {}
      A1HG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HG2 atom type class.
     */
    class A1HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HG2 () {}
      A1HG2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HH1 atom type class.
     */
    class A1HH1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HH1 () {}
      A1HH1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 1HH2 atom type class.
     */
    class A1HH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HH2 () {}
      A1HH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HD1 atom type class.
     */
    class A2HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HD1 () {}
      A2HD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HD2 atom type class.
     */
    class A2HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HD2 () {}
      A2HD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HE2 atom type class.
     */
    class A2HE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HE2 () {}
      A2HE2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HG1 atom type class.
     */
    class A2HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HG1 () {}
      A2HG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HG2 atom type class.
     */
    class A2HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HG2 () {}
      A2HG2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HH1 atom type class.
     */
    class A2HH1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HH1 () {}
      A2HH1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 2HH2 atom type class.
     */
    class A2HH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HH2 () {}
      A2HH2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3HD1 atom type class.
     */
    class A3HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HD1 () {}
      A3HD1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3HD2 atom type class.
     */
    class A3HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HD2 () {}
      A3HD2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3HG1 atom type class.
     */
    class A3HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HG1 () {}
      A3HG1 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global 3HG2 atom type class.
     */
    class A3HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HG2 () {}
      A3HG2 (const char*  t) : AtomType (t) {}
    };

    /**
     * Global magnesium atom type class.
     */
    class AMG : public virtual Magnesium
    { 
    public:
      AMG () {}
      AMG (const char*  t) : AtomType (t) {}
    };

    /**
     * Global amino acid pseudo atom type class.
     */
    class APSAZ : public virtual AminoAcid, public virtual Pseudo, public virtual Backbone
    { 
    public:
      APSAZ () {}
      APSAZ (const char*  t) : AtomType (t) {}
    };

  };  
}

#endif
