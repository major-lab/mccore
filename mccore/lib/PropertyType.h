//                              -*- Mode: C++ -*- 
// PropertyType.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:17:11 2003
// $Revision: 1.1 $
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



#ifndef _PropertyType_h_
#define _PropertyType_h_

#include <iostream>

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  class PropertyTypeStore;

  /**
   * @short Property types.
   *
   * General property types.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>
   * @version $Id: PropertyType.h,v 1.1 2003-04-11 01:34:35 gendrop Exp $
   */
class PropertyType
{
  /**
   * Container for string to type associations.
   */
  static PropertyTypeStore ptstore;
  
  /**
   * The type.
   */
  char* type;

protected:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  PropertyType ();

  /**
   * Initializes the object.
   * @param t the string representation of the type.
   * @param p the set of properties for this type.
   */
  PropertyType (const char* t);
    
  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  PropertyType (const PropertyType &other);

  /**
   * Destroys the object.
   */
  virtual ~PropertyType ();

  /**
   * PropertyTypeStore is a friend since the destructor is private.
   */
  friend class PropertyTypeStore;
  
public:
  
  // FUNCTION OBJECTS --------------------------------------------------------
  
  /**
   * @short less comparator for Atomtypes.
   */
  struct less
  {
    /**
     * Tests whether the first  propertytype is less than the second. 
     * @param s1 the first string.
     * @param s2 the second string.
     * @return the result of the test.
     */
    bool operator() (const PropertyType* t1, const PropertyType* t2) const
    { return *t1 < *t2; }
  };
  
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Indicates whether some other propertytype is "equal to" this one.
   * @param obj the reference object with which to compare.
   * @param true if this object is the same as the obj argument;
   * false otherwise.
   */
  bool operator== (const PropertyType &other) const
  { return strcmp (type, other.type) == 0; }
  
  /**
   * Indicates whether some other property is "not equal to" this one.
   * @param obj the reference object with which to compare.
   * @param true if this object is the same as the obj argument;
   * false otherwise.
   */
  bool operator!= (const PropertyType &other) const 
  { return ! operator== (other); }
  
  /**
   * Imposes a total ordering on the PropertyType objects.
   * @param obj the property type to compare.
   * @return true if this property type is less than the other.
   */
  bool operator< (const PropertyType &other) const
  { return strcmp (type, other.type) < 0; }
  

  // METHODS --------------------------------------------------------------

  /**
   * Converts the property type into a string.
   * @return the string.
   */
  virtual operator const char* () const { return type; }
  
  /**
   * Identifies the type of property stored in a string.
   * @param s the string.
   * @return a property type for the string.
   */
  static PropertyType* parseType (const char* t);

 
  // I/O  -----------------------------------------------------------------

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
  
  /**
   * Global theo type.
   */
  static PropertyType* pTheo;
  
  /**
   * Global pairing type.
   */
  static PropertyType* pPairing;
  
  /**
   * Global pairing type.
   */
  static PropertyType* pStack;

  /**
   * Global cis type.
   */
  static PropertyType* pCis;

  /**
   * Global trans type.
   */
  static PropertyType* pTrans;

  /**
   * Global reverse type.
   */
  static PropertyType* pReverse;
    
  /**
   * Global adjacent type.
   */
  static PropertyType* pAdjacent;
    
  /**
   * Global type_A type.
   */
  static PropertyType* pType_A;

  /**
   * Global type_B type.
   */
  static PropertyType* pType_B;

  /**
   * Global helix type.
   */
  static PropertyType* pHelix;
  
  /**
   * Global C1p_endo type.
   */
  static PropertyType* pC1p_endo;

  /**
   * Global C1p_exo type.
   */
  static PropertyType* pC1p_exo;

  /**
   * Global C2p_endo type.
   */
  static PropertyType* pC2p_endo;

  /**
   * Global C2p_exo type.
   */
  static PropertyType* pC2p_exo;

  /**
   * Global C3p_endo type.
   */
  static PropertyType* pC3p_endo;

  /**
   * Global C3p_exo type.
   */
  static PropertyType* pC3p_exo;

  /**
   * Global C4p_endo type.
   */
  static PropertyType* pC4p_endo;

  /**
   * Global C4p_exo type.
   */
  static PropertyType* pC4p_exo;

  /**
   * Global O4p_endo type.
   */
  static PropertyType* pO4p_endo;

  /**
   * Global O4p_exo type.
   */
  static PropertyType* pO4p_exo;

  /**
   * Global anti type.
   */
  static PropertyType* pAnti;

  /**
   * Global syn type.
   */
  static PropertyType* pSyn;

  /**
   * Global DIR_5p type.
   */
  static PropertyType* pDIR_5p;

  /**
   * Global DIR_3p type.
   */
  static PropertyType* pDIR_3p;

  /**
   * Global DIR_ANY type.
   */
  static PropertyType* pDIR_ANY;

  //     /**
  //      * Global DIR_SH type.
  //      */
  //     static PropertyType* pDIR_SH;

  //     /**
  //      * Global DIR_HS type.
  //      */
  //     static PropertyType* pDIR_HS;

  /**
   * Global saenger type.
   */
  static PropertyType* pSaenger;

  /**
   * Global wc type.
   */
  static PropertyType* pWC;

  /**
   * Global wobble type.
   */
  static PropertyType* pWobble;

  /**
   * Global I type.
   */
  static PropertyType* pI;

  /**
   * Global II type.
   */
  static PropertyType* pII;

  /**
   * Global III type.
   */
  static PropertyType* pIII;

  /**
   * Global IV type.
   */
  static PropertyType* pIV;

  /**
   * Global V type.
   */
  static PropertyType* pV;

  /**
   * Global VI type.
   */
  static PropertyType* pVI;

  /**
   * Global VII type.
   */
  static PropertyType* pVII;

  /**
   * Global VIII type.
   */
  static PropertyType* pVIII;

  /**
   * Global IX type.
   */
  static PropertyType* pIX;

  /**
   * Global X type.
   */
  static PropertyType* pX;

  /**
   * Global XI type.
   */
  static PropertyType* pXI;

  /**
   * Global XII type.
   */
  static PropertyType* pXII;

  /**
   * Global XIII type.
   */
  static PropertyType* pXIII;

  /**
   * Global XIV type.
   */
  static PropertyType* pXIV;

  /**
   * Global XV type.
   */
  static PropertyType* pXV;

  /**
   * Global XVI type.
   */
  static PropertyType* pXVI;

  /**
   * Global XVII type.
   */
  static PropertyType* pXVII;

  /**
   * Global XVIII type.
   */
  static PropertyType* pXVIII;

  /**
   * Global XIX type.
   */
  static PropertyType* pXIX;

  /**
   * Global XX type.
   */
  static PropertyType* pXX;

  /**
   * Global XXI type.
   */
  static PropertyType* pXXI;

  /**
   * Global XXII type.
   */
  static PropertyType* pXXII;

  /**
   * Global XXIII type.
   */
  static PropertyType* pXXIII;

  /**
   * Global XXIV type.
   */
  static PropertyType* pXXIV;

  /**
   * Global XXV type.
   */
  static PropertyType* pXXV;

  /**
   * Global XXVI type.
   */
  static PropertyType* pXXVI;

  /**
   * Global XXVII type.
   */
  static PropertyType* pXXVII;

  /**
   * Global XXVIII type.
   */
  static PropertyType* pXXVIII;

  /**
   * Global OneHbond type.
   */
  static PropertyType* pOneHbond;

  /**
   * Global 29 type.
   */
  static PropertyType* p29;

  /**
   * Global 30 type.
   */
  static PropertyType* p30;

  /**
   * Global 31 type.
   */
  static PropertyType* p31;

  /**
   * Global 32 type.
   */
  static PropertyType* p32;

  /**
   * Global 33 type.
   */
  static PropertyType* p33;

  /**
   * Global 34 type.
   */
  static PropertyType* p34;

  /**
   * Global 35 type.
   */
  static PropertyType* p35;

  /**
   * Global 36 type.
   */
  static PropertyType* p36;

  /**
   * Global 37 type.
   */
  static PropertyType* p37;

  /**
   * Global 38 type.
   */
  static PropertyType* p38;

  /**
   * Global 39 type.
   */
  static PropertyType* p39;

  /**
   * Global 40 type.
   */
  static PropertyType* p40;

  /**
   * Global 41 type.
   */
  static PropertyType* p41;

  /**
   * Global 42 type.
   */
  static PropertyType* p42;

  /**
   * Global 43 type.
   */
  static PropertyType* p43;

  /**
   * Global 44 type.
   */
  static PropertyType* p44;

  /**
   * Global 45 type.
   */
  static PropertyType* p45;

  /**
   * Global 46 type.
   */
  static PropertyType* p46;

  /**
   * Global 47 type.
   */
  static PropertyType* p47;

  /**
   * Global 48 type.
   */
  static PropertyType* p48;

  /**
   * Global 49 type.
   */
  static PropertyType* p49;

  /**
   * Global 50 type.
   */
  static PropertyType* p50;

  /**
   * Global 51 type.
   */
  static PropertyType* p51;

  /**
   * Global 52 type.
   */
  static PropertyType* p52;

  /**
   * Global 53 type.
   */
  static PropertyType* p53;

  /**
   * Global 54 type.
   */
  static PropertyType* p54;

  /**
   * Global 55 type.
   */
  static PropertyType* p55;

  /**
   * Global 56 type.
   */
  static PropertyType* p56;

  /**
   * Global 57 type.
   */
  static PropertyType* p57;

  /**
   * Global 58 type.
   */
  static PropertyType* p58;

  /**
   * Global 59 type.
   */
  static PropertyType* p59;

  /**
   * Global 60 type.
   */
  static PropertyType* p60;

  /**
   * Global 61 type.
   */
  static PropertyType* p61;

  /**
   * Global 62 type.
   */
  static PropertyType* p62;

  /**
   * Global 63 type.
   */
  static PropertyType* p63;

  /**
   * Global 64 type.
   */
  static PropertyType* p64;

  /**
   * Global 65 type.
   */
  static PropertyType* p65;

  /**
   * Global 66 type.
   */
  static PropertyType* p66;

  /**
   * Global 67 type.
   */
  static PropertyType* p67;

  /**
   * Global 68 type.
   */
  static PropertyType* p68;

  /**
   * Global 69 type.
   */
  static PropertyType* p69;

  /**
   * Global 70 type.
   */
  static PropertyType* p70;

  /**
   * Global 71 type.
   */
  static PropertyType* p71;

  /**
   * Global 72 type.
   */
  static PropertyType* p72;

  /**
   * Global 73 type.
   */
  static PropertyType* p73;

  /**
   * Global 74 type.
   */
  static PropertyType* p74;

  /**
   * Global 75 type.
   */
  static PropertyType* p75;

  /**
   * Global 76 type.
   */
  static PropertyType* p76;

  /**
   * Global 77 type.
   */
  static PropertyType* p77;

  /**
   * Global 78 type.
   */
  static PropertyType* p78;

  /**
   * Global 79 type.
   */
  static PropertyType* p79;

  /**
   * Global 80 type.
   */
  static PropertyType* p80;

  /**
   * Global 81 type.
   */
  static PropertyType* p81;

  /**
   * Global 82 type.
   */
  static PropertyType* p82;

  /**
   * Global 83 type.
   */
  static PropertyType* p83;

  /**
   * Global 84 type.
   */
  static PropertyType* p84;

  /**
   * Global 85 type.
   */
  static PropertyType* p85;

  /**
   * Global 86 type.
   */
  static PropertyType* p86;

  /**
   * Global 87 type.
   */
  static PropertyType* p87;

  /**
   * Global 88 type.
   */
  static PropertyType* p88;

  /**
   * Global 89 type.
   */
  static PropertyType* p89;

  /**
   * Global 90 type.
   */
  static PropertyType* p90;

  /**
   * Global 91 type.
   */
  static PropertyType* p91;

  /**
   * Global 92 type.
   */
  static PropertyType* p92;

  /**
   * Global 93 type.
   */
  static PropertyType* p93;

  /**
   * Global 94 type.
   */
  static PropertyType* p94;

  /**
   * Global 95 type.
   */
  static PropertyType* p95;

  /**
   * Global 96 type.
   */
  static PropertyType* p96;

  /**
   * Global 97 type.
   */
  static PropertyType* p97;

  /**
   * Global 98 type.
   */
  static PropertyType* p98;

  /**
   * Global 99 type.
   */
  static PropertyType* p99;

  /**
   * Global 100 type.
   */
  static PropertyType* p100;

  /**
   * Global 101 type.
   */
  static PropertyType* p101;

  /**
   * Global 102 type.
   */
  static PropertyType* p102;

  /**
   * Global 103 type.
   */
  static PropertyType* p103;

  /**
   * Global 104 type.
   */
  static PropertyType* p104;

  /**
   * Global 105 type.
   */
  static PropertyType* p105;

  /**
   * Global 106 type.
   */
  static PropertyType* p106;

  /**
   * Global 108 type.
   */
  static PropertyType* p108;

  /**
   * Global 109 type.
   */
  static PropertyType* p109;

  /**
   * Global 110 type.
   */
  static PropertyType* p110;

  /**
   * Global 111 type.
   */
  static PropertyType* p111;

  /**
   * Global 112 type.
   */
  static PropertyType* p112;

  /**
   * Global 113 type.
   */
  static PropertyType* p113;

  /**
   * Global 114 type.
   */
  static PropertyType* p114;

  /**
   * Global 115 type.
   */
  static PropertyType* p115;

  /**
   * Global 116 type.
   */
  static PropertyType* p116;

  /**
   * Global 117 type.
   */
  static PropertyType* p117;

  /**
   * Global 118 type.
   */
  static PropertyType* p118;

  /**
   * Global 119 type.
   */
  static PropertyType* p119;

  /**
   * Global 120 type.
   */
  static PropertyType* p120;

  /**
   * Global 121 type.
   */
  static PropertyType* p121;

  /**
   * Global 122 type.
   */
  static PropertyType* p122;

  /**
   * Global 123 type.
   */
  static PropertyType* p123;

  /**
   * Global 124 type.
   */
  static PropertyType* p124;

  /**
   * Global 125 type.
   */
  static PropertyType* p125;

  /**
   * Global 126 type.
   */
  static PropertyType* p126;

  /**
   * Global 127 type.
   */
  static PropertyType* p127;

  /**
   * Global 128 type.
   */
  static PropertyType* p128;

  /**
   * Global 129 type.
   */
  static PropertyType* p129;

  /**
   * Global 130 type.
   */
  static PropertyType* p130;

  /**
   * Global 131 type.
   */
  static PropertyType* p131;

  /**
   * Global 132 type.
   */
  static PropertyType* p132;

  /**
   * Global 133 type.
   */
  static PropertyType* p133;

  /**
   * Global 134 type.
   */
  static PropertyType* p134;

  /**
   * Global 135 type.
   */
  static PropertyType* p135;

  /**
   * Global 136 type.
   */
  static PropertyType* p136;

  /**
   * Global 137 type.
   */
  static PropertyType* p137;

  //     /**
  //      * Global wct type.
  //      */
  //     static PropertyType* pwct;

  //     /**
  //      * Global connect type.
  //      */
  //     static PropertyType* pconnect;

  //     /**
  //      * Global wobblet type.
  //      */
  //     static PropertyType* pwobblet;

  //     /**
  //      * Global non_adjacent type.
  //      */
  //     static PropertyType* pnon_adjacent;

  //     /**
  //      * Global strong type.
  //      */
  //     static PropertyType* pstrong;

  //     /**
  //      * Global weak type.
  //      */
  //     static PropertyType* pweak;

  //     /**
  //      * Global nostack type.
  //      */
  //     static PropertyType* pnostack;

  /**
   * Global W type.
   */
  static PropertyType* pW;

  /**
   * Global S type.
   */
  static PropertyType* pS;

  /**
   * Global H type.
   */
  static PropertyType* pH;

  /**
   * Global B type.
   */
  static PropertyType* pB;

  /**
   * Global Ws type.
   */
  static PropertyType* pWs;

  /**
   * Global Ww type.
   */
  static PropertyType* pWw;

  /**
   * Global Wh type.
   */
  static PropertyType* pWh;

  /**
   * Global Sw type.
   */
  static PropertyType* pSw;

  /**
   * Global Ss type.
   */
  static PropertyType* pSs;

  /**
   * Global Hw type.
   */
  static PropertyType* pHw;

  /**
   * Global Hh type.
   */
  static PropertyType* pHh;

  /**
   * Global C8 type.
   */
  static PropertyType* pC8;

  /**
   * Global Bs type.
   */
  static PropertyType* pBs;

  /**
   * Global Bh type.
   */
  static PropertyType* pBh;

};

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const PropertyType &t);

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const PropertyType *t);

  /**
   * Inputs the atom type.  The integer type is read and the type object is
   * assigned to the pointer.
   * @param ibs the input binary stream.
   * @param t the atom type pointer to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &in, const PropertyType *&t);
  
  /**
   * Outputs the atom type through a binary stream.  The type is dumped as an
   * integer.
   * @param obs the binary output stream.
   * @param t the type to dump.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &out, const PropertyType *t);



}

#endif
