//                              -*- Mode: C++ -*- 
// PropertyType.h
// Copyright � 2003-07 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:17:11 2003
// $Revision: 1.20 $
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


#ifndef _mccore_PropertyType_h_
#define _mccore_PropertyType_h_

#include <iostream>
#include <string>

using namespace std;



namespace mccore
{

  class PropertyTypeStore;
  class Exception;
  class iBinstream;
  class oBinstream;
  
  /**
   * @short Property types.
   *
   * General property types.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>
   * @version $Id: PropertyType.h,v 1.20 2007-01-09 01:07:10 larosem Exp $
   */
  class PropertyType
  {
    /**
     * Container for string to type associations.
     */
    static PropertyTypeStore ptstore;

  protected:
    
    /**
     * The type key string.
     */
    string key;
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    PropertyType ();
    
    /**
     * Initializes the object.
     * @param ks the string representation of the type key.
     */
    PropertyType (const string& ks);
    
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
      bool operator() (const PropertyType* t1, const PropertyType* t2) const
      {
	return
	  *(0 == t1 ? PropertyType::pNull : t1) <
	  *(0 == t2 ? PropertyType::pNull : t2);
      }
    };
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Indicates whether some other propertytype is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const PropertyType &other) const
    {
      return this->key == other.key;
    }
      
    
    /**
     * Indicates whether some other property is "not equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const PropertyType &other) const
    {
      return ! operator== (other);
    }
    
    /**
     * Imposes a total ordering on the PropertyType objects.
     * @param obj the property type to compare.
     * @return true if this property type is less than the other.
     */
    bool operator< (const PropertyType &other) const
    {
      return this->key < other.key;
    }
    bool operator<= (const PropertyType &other) const
    {
      return this->key < other.key || this->key == other.key;
    }
    bool operator> (const PropertyType &other) const
    {
      return !this->operator<= (other);
    }
    bool operator>= (const PropertyType &other) const
    {
      return !this->operator< (other);
    }

    /**
     * Converts the property type into a string.
     * @return the string.
     */
    virtual operator const char* () const
    {
      return this->key.c_str ();
    }
    
    // METHODS --------------------------------------------------------------

    /**
     * Converts the residuetype into a stl string.
     * @return the string.
     */
    virtual const string& toString () const
    {
      return this->key;
    }
    
    /**
     * Identifies the type of property stored in a string.
     * @param str the c string.
     * @return a property type for the string.
     */
    static const PropertyType* parseType (const char *str);

    /**
     * Identifies the type of property stored in a string.
     * @param str the stl string.
     * @return a property type for the string.
     */
    static const PropertyType* parseType (const string &str);

    /**
     * Gets the property corresponding to the inverted relation.
     * @param t The property type for a relation.
     * @return The property type corresponding to the inverted relation.
     */
    static const PropertyType* invert (const PropertyType *t);
    
    /**
     * Tests whether the type this is same as or derived from t.
     * @param t the base type class.
     * @return true if this is same as or derived from t.
     */
    virtual bool is (const PropertyType *t) const
    {
      return t->describe (this);
    }
    
    /**
     * Tests whether the type t is a PropertyType or derived class.
     * @param the type to test.
     * @return the truth value of the test.
     */
    virtual bool describe (const PropertyType *t) const
    {
      return dynamic_cast< const PropertyType* > (t);
    }
    
    /**
     * isNull?
     */
    virtual bool isNull () const
    {
      return false;
    }

    /**
     * isUnknown?
     */
    virtual bool isUnknown () const
    {
      return false;
    }

    /**
     * isAdjacent?
     */
    virtual bool isAdjacent () const
    {
      return false;
    }

    /**
     * isStack?
     */
    virtual bool isStack () const
    {
      return false;
    }

    /**
     * is up?
     */
    virtual bool isUp () const
    {
      return false;
    }

    /**
     * is down?
     */
    virtual bool isDown () const
    {
      return false;
    }
    /**
     * is straight?
     */
    virtual bool isStraight () const
    {
      return false;
    }

    /**
     * is reverse?
     */
    virtual bool isReverse () const
    {
      return false;
    }

    /**
     * isPairing?
     */
    virtual bool isPairing () const
    {
      return false;
    }

    /**
     * is backbone h-bond?
     */
    virtual bool isBHbond () const
    {
      return false;
    }

    /**
     * isFace?
     */
    virtual bool isFace () const
    {
      return false;
    }

    /**
     * isH?
     */
    virtual bool isH () const
    {
      return false;
    }

    /**
     * isS?
     */
    virtual bool isS () const
    {
      return false;
    }

    /**
     * isW?
     */
    virtual bool isW () const
    {
      return false;
    }

    /**
     * isSaenger?
     */
    virtual bool isSaenger () const
    {
      return false;
    }

    /**
     * isWC?
     */
    virtual bool isWC () const
    {
      return false;
    }

    /**
     * isWobble?
     */
    virtual bool isWobble () const
    {
      return false;
    }

    /**
     * isOneHbond?
     */
    virtual bool isOneHbond () const
    {
      return false;
    }

    /**
     * isPuckeringMode?
     */
    virtual bool isPuckeringMode () const
    {
      return false;
    }

    /**
     * isRiboseOrientation?
     */
    virtual bool isRiboseOrientation () const
    {
      return false;
    }

    
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
     * Global null type.
     */
    static const PropertyType* pNull;

    /**
     * Global unknown type.
     */
    static const PropertyType* pUnknown;
    
    /**
     * Global Hydrogen Bond type.
     */
    static const PropertyType* pHbond;
    
    /**
     * Global theo type.
     */
    static const PropertyType* pTheo;
    
    /**
     * Global stack type.
     */
    static const PropertyType* pStack;

    /**
     * Global upward type.
     */
    static const PropertyType* pUpward;

    /**
     * Global downward type.
     */
    static const PropertyType* pDownward;

    /**
     * Global inward type.
     */
    static const PropertyType* pInward;

    /**
     * Global outward type.
     */
    static const PropertyType* pOutward;
    
    /**
     * Global pairing type.
     */
    static const PropertyType* pPairing;

    /**
     * Global backbone Hydrogen Bond type.
     */
    static const PropertyType* pBHbond;
    
    /**
     * Global parallel type.
     */
    static const PropertyType* pParallel;

    /**
     * Global antiparallel type.
     */
    static const PropertyType* pAntiparallel;

    /**
     * Global cis type.
     */
    static const PropertyType* pCis;
    
    /**
     * Global trans type.
     */
    static const PropertyType* pTrans;
    
    /**
     * Global adjacent type.
     */
    static const PropertyType* pAdjacent;

    /**
     * Global 5' adjacent type.
     */
    static const PropertyType* pAdjacent5p;

    /**
     * Global 3' adjacent type.
     */
    static const PropertyType* pAdjacent3p;
    
    /**
     * Global type_A type.
     */
    static const PropertyType* pType_A;
    
    /**
     * Global type_B type.
     */
    static const PropertyType* pType_B;
    
    /**
     * Global helix type.
     */
    static const PropertyType* pHelix;
    
    /**
     * Global C1p_endo type.
     */
    static const PropertyType* pC1p_endo;
    
    /**
     * Global C1p_exo type.
     */
    static const PropertyType* pC1p_exo;
    
    /**
     * Global C2p_endo type.
     */
    static const PropertyType* pC2p_endo;
    
    /**
     * Global C2p_exo type.
     */
    static const PropertyType* pC2p_exo;
    
    /**
     * Global C3p_endo type.
     */
    static const PropertyType* pC3p_endo;
    
    /**
     * Global C3p_exo type.
     */
    static const PropertyType* pC3p_exo;
    
    /**
     * Global C4p_endo type.
     */
    static const PropertyType* pC4p_endo;
    
    /**
     * Global C4p_exo type.
     */
    static const PropertyType* pC4p_exo;
    
    /**
     * Global O4p_endo type.
     */
    static const PropertyType* pO4p_endo;
    
    /**
     * Global O4p_exo type.
     */
    static const PropertyType* pO4p_exo;
    
    /**
     * Global anti type.
     */
    static const PropertyType* pAnti;
    
    /**
     * Global syn type.
     */
    static const PropertyType* pSyn;
    
    /**
     * Global saenger type.
     */
    static const PropertyType* pSaenger;
    
    /**
     * Global wc type.
     */
    static const PropertyType* pWC;
    
    /**
     * Global wobble type.
     */
    static const PropertyType* pWobble;
    
    /**
     * Global I type.
     */
    static const PropertyType* pI;
    
    /**
     * Global II type.
     */
    static const PropertyType* pII;
    
    /**
     * Global III type.
     */
    static const PropertyType* pIII;
    
    /**
     * Global IV type.
     */
    static const PropertyType* pIV;
    
    /**
     * Global V type.
     */
    static const PropertyType* pV;
    
    /**
     * Global VI type.
     */
    static const PropertyType* pVI;
    
    /**
     * Global VII type.
     */
    static const PropertyType* pVII;
    
    /**
     * Global VIII type.
     */
    static const PropertyType* pVIII;
    
    /**
     * Global IX type.
     */
    static const PropertyType* pIX;
    
    /**
     * Global X type.
     */
    static const PropertyType* pX;
    
    /**
     * Global XI type.
     */
    static const PropertyType* pXI;
    
    /**
     * Global XII type.
     */
    static const PropertyType* pXII;
    
    /**
     * Global XIII type.
     */
    static const PropertyType* pXIII;
    
    /**
     * Global XIV type.
     */
    static const PropertyType* pXIV;
    
    /**
     * Global XV type.
     */
    static const PropertyType* pXV;
    
    /**
     * Global XVI type.
     */
    static const PropertyType* pXVI;
    
    /**
     * Global XVII type.
     */
    static const PropertyType* pXVII;
    
    /**
     * Global XVIII type.
     */
    static const PropertyType* pXVIII;
    
    /**
     * Global XIX type.
     */
    static const PropertyType* pXIX;
    
    /**
     * Global XX type.
     */
    static const PropertyType* pXX;
    
    /**
     * Global XXI type.
     */
    static const PropertyType* pXXI;
    
    /**
     * Global XXII type.
     */
    static const PropertyType* pXXII;
    
    /**
     * Global XXIII type.
     */
    static const PropertyType* pXXIII;
    
    /**
     * Global XXIV type.
     */
    static const PropertyType* pXXIV;
    
    /**
     * Global XXV type.
     */
    static const PropertyType* pXXV;
    
    /**
     * Global XXVI type.
     */
    static const PropertyType* pXXVI;
    
    /**
     * Global XXVII type.
     */
    static const PropertyType* pXXVII;
    
    /**
     * Global XXVIII type.
     */
    static const PropertyType* pXXVIII;
    
    /**
     * Global OneHbond type.
     */
    static const PropertyType* pOneHbond;
    
    /**
     * Global 29 type.
     */
    static const PropertyType* p29;
    
    /**
     * Global 30 type.
     */
    static const PropertyType* p30;
    
    /**
     * Global 31 type.
     */
    static const PropertyType* p31;
    
    /**
     * Global 32 type.
     */
    static const PropertyType* p32;
    
    /**
     * Global 33 type.
     */
    static const PropertyType* p33;
    
    /**
     * Global 34 type.
     */
    static const PropertyType* p34;
    
    /**
     * Global 35 type.
     */
    static const PropertyType* p35;
    
    /**
     * Global 36 type.
     */
    static const PropertyType* p36;
    
    /**
     * Global 37 type.
     */
    static const PropertyType* p37;
    
    /**
     * Global 38 type.
     */
    static const PropertyType* p38;
    
    /**
     * Global 39 type.
     */
    static const PropertyType* p39;
    
    /**
     * Global 40 type.
     */
    static const PropertyType* p40;
    
    /**
     * Global 41 type.
     */
    static const PropertyType* p41;
    
    /**
     * Global 42 type.
     */
    static const PropertyType* p42;
    
    /**
     * Global 43 type.
     */
    static const PropertyType* p43;
    
    /**
     * Global 44 type.
     */
    static const PropertyType* p44;
    
    /**
     * Global 45 type.
     */
    static const PropertyType* p45;
    
    /**
     * Global 46 type.
     */
    static const PropertyType* p46;
    
    /**
     * Global 47 type.
     */
    static const PropertyType* p47;
    
    /**
     * Global 48 type.
     */
    static const PropertyType* p48;
    
    /**
     * Global 49 type.
     */
    static const PropertyType* p49;
    
    /**
     * Global 50 type.
     */
    static const PropertyType* p50;
    
    /**
     * Global 51 type.
     */
    static const PropertyType* p51;
    
    /**
     * Global 52 type.
     */
    static const PropertyType* p52;
    
    /**
     * Global 53 type.
     */
    static const PropertyType* p53;
    
    /**
     * Global 54 type.
     */
    static const PropertyType* p54;
    
    /**
     * Global 55 type.
     */
    static const PropertyType* p55;
    
    /**
     * Global 56 type.
     */
    static const PropertyType* p56;
    
    /**
     * Global 57 type.
     */
    static const PropertyType* p57;
    
    /**
     * Global 58 type.
     */
    static const PropertyType* p58;
    
    /**
     * Global 59 type.
     */
    static const PropertyType* p59;
    
    /**
     * Global 60 type.
     */
    static const PropertyType* p60;
    
    /**
     * Global 61 type.
     */
    static const PropertyType* p61;
    
    /**
     * Global 62 type.
     */
    static const PropertyType* p62;
    
    /**
     * Global 63 type.
     */
    static const PropertyType* p63;
    
    /**
     * Global 64 type.
     */
    static const PropertyType* p64;
    
    /**
     * Global 65 type.
     */
    static const PropertyType* p65;
    
    /**
     * Global 66 type.
     */
    static const PropertyType* p66;
    
    /**
     * Global 67 type.
     */
    static const PropertyType* p67;
    
    /**
     * Global 68 type.
     */
    static const PropertyType* p68;
    
    /**
     * Global 69 type.
     */
    static const PropertyType* p69;
    
    /**
     * Global 70 type.
     */
    static const PropertyType* p70;
    
    /**
     * Global 71 type.
     */
    static const PropertyType* p71;
    
    /**
     * Global 72 type.
     */
    static const PropertyType* p72;
    
    /**
     * Global 73 type.
     */
    static const PropertyType* p73;
    
    /**
     * Global 74 type.
     */
    static const PropertyType* p74;
    
    /**
     * Global 75 type.
     */
    static const PropertyType* p75;
    
    /**
     * Global 76 type.
     */
    static const PropertyType* p76;
    
    /**
     * Global 77 type.
     */
    static const PropertyType* p77;
    
    /**
     * Global 78 type.
     */
    static const PropertyType* p78;
    
    /**
     * Global 79 type.
     */
    static const PropertyType* p79;
    
    /**
     * Global 80 type.
     */
    static const PropertyType* p80;
    
    /**
     * Global 81 type.
     */
    static const PropertyType* p81;
    
    /**
     * Global 82 type.
     */
    static const PropertyType* p82;
    
    /**
     * Global 83 type.
     */
    static const PropertyType* p83;
    
    /**
     * Global 84 type.
     */
    static const PropertyType* p84;
    
    /**
     * Global 85 type.
     */
    static const PropertyType* p85;
    
    /**
     * Global 86 type.
     */
    static const PropertyType* p86;
    
    /**
     * Global 87 type.
     */
    static const PropertyType* p87;
    
    /**
     * Global 88 type.
     */
    static const PropertyType* p88;
    
    /**
     * Global 89 type.
     */
    static const PropertyType* p89;
    
    /**
     * Global 90 type.
     */
    static const PropertyType* p90;
    
    /**
     * Global 91 type.
     */
    static const PropertyType* p91;
    
    /**
     * Global 92 type.
     */
    static const PropertyType* p92;
    
    /**
     * Global 93 type.
     */
    static const PropertyType* p93;
    
    /**
     * Global 94 type.
     */
    static const PropertyType* p94;
    
    /**
     * Global 95 type.
     */
    static const PropertyType* p95;
    
    /**
     * Global 96 type.
     */
    static const PropertyType* p96;
    
    /**
     * Global 97 type.
     */
    static const PropertyType* p97;
    
    /**
     * Global 98 type.
     */
    static const PropertyType* p98;
    
    /**
     * Global 99 type.
     */
    static const PropertyType* p99;
    
    /**
     * Global 100 type.
     */
    static const PropertyType* p100;
    
    /**
     * Global 101 type.
     */
    static const PropertyType* p101;
    
    /**
     * Global 102 type.
     */
    static const PropertyType* p102;
    
    /**
     * Global 103 type.
     */
    static const PropertyType* p103;
    
    /**
     * Global 104 type.
     */
    static const PropertyType* p104;
    
    /**
     * Global 105 type.
     */
    static const PropertyType* p105;
    
    /**
     * Global 106 type.
     */
    static const PropertyType* p106;
    
    /**
     * Global 108 type.
     */
    static const PropertyType* p108;
    
    /**
     * Global 109 type.
     */
    static const PropertyType* p109;
    
    /**
     * Global 110 type.
     */
    static const PropertyType* p110;
    
    /**
     * Global 111 type.
     */
    static const PropertyType* p111;
    
    /**
     * Global 112 type.
     */
    static const PropertyType* p112;
    
    /**
     * Global 113 type.
     */
    static const PropertyType* p113;
    
    /**
     * Global 114 type.
     */
    static const PropertyType* p114;
    
    /**
     * Global 115 type.
     */
    static const PropertyType* p115;
    
    /**
     * Global 116 type.
     */
    static const PropertyType* p116;
    
    /**
     * Global 117 type.
     */
    static const PropertyType* p117;
    
    /**
     * Global 118 type.
     */
    static const PropertyType* p118;
    
    /**
     * Global 119 type.
     */
    static const PropertyType* p119;
    
    /**
     * Global 120 type.
     */
    static const PropertyType* p120;
    
    /**
     * Global 121 type.
     */
    static const PropertyType* p121;
    
    /**
     * Global 122 type.
     */
    static const PropertyType* p122;
    
    /**
     * Global 123 type.
     */
    static const PropertyType* p123;
    
    /**
     * Global 124 type.
     */
    static const PropertyType* p124;
    
    /**
     * Global 125 type.
     */
    static const PropertyType* p125;
    
    /**
     * Global 126 type.
     */
    static const PropertyType* p126;
    
    /**
     * Global 127 type.
     */
    static const PropertyType* p127;
    
    /**
     * Global 128 type.
     */
    static const PropertyType* p128;
    
    /**
     * Global 129 type.
     */
    static const PropertyType* p129;
    
    /**
     * Global 130 type.
     */
    static const PropertyType* p130;
    
    /**
     * Global 131 type.
     */
    static const PropertyType* p131;
    
    /**
     * Global 132 type.
     */
    static const PropertyType* p132;
    
    /**
     * Global 133 type.
     */
    static const PropertyType* p133;
    
    /**
     * Global 134 type.
     */
    static const PropertyType* p134;
    
    /**
     * Global 135 type.
     */
    static const PropertyType* p135;
    
    /**
     * Global 136 type.
     */
    static const PropertyType* p136;
    
    /**
     * Global 137 type.
     */
    static const PropertyType* p137;
    
    /**
     * Global W type.
     */
    static const PropertyType* pW;
    
    /**
     * Global S type.
     */
    static const PropertyType* pS;
    
    /**
     * Global H type.
     */
    static const PropertyType* pH;
    
    /**
     * Global Ws type.
     */
    static const PropertyType* pWs;
    
    /**
     * Global Ww type.
     */
    static const PropertyType* pWw;
    
    /**
     * Global Wh type.
     */
    static const PropertyType* pWh;
    
    /**
     * Global Sw type.
     */
    static const PropertyType* pSw;
    
    /**
     * Global Ss type.
     */
    static const PropertyType* pSs;
    
    /**
     * Global Hw type.
     */
    static const PropertyType* pHw;
    
    /**
     * Global Hh type.
     */
    static const PropertyType* pHh;
    
    /**
     * Global C8 type.
     */
    static const PropertyType* pC8;
    
    /**
     * Global Bs type.
     */
    static const PropertyType* pBs;
    
    /**
     * Global Bh type.
     */
    static const PropertyType* pBh;

    /**
     * Global Phosphate face type.
     */
    static const PropertyType *pPhosphate;

    /**
     * Global Ribose face type.
     */
    static const PropertyType *pRibose;
    
    /**
     * Global Alpha-L-Lyxo type.
     */
    static const PropertyType* pAlpha_L_Lyxofuranoside;

    /**
     * Global Beta-L-Lyxo type.
     */
    static const PropertyType* pBeta_L_Lyxofuranoside;

    /**
     * Global Alpha-D-Lyxo type.
     */
    static const PropertyType* pAlpha_D_Lyxofuranoside;

    /**
     * Global Beta-D-Lyxo type.
     */
    static const PropertyType* pBeta_D_Lyxofuranoside;

    /**
     * Global Alpha-L-Ribo type.
     */
    static const PropertyType* pAlpha_L_Ribofuranoside;

    /**
     * Global Beta-L-Ribo type.
     */
    static const PropertyType* pBeta_L_Ribofuranoside;

    /**
     * Global Alpha-D-Ribo type.
     */
    static const PropertyType* pAlpha_D_Ribofuranoside;

    /**
     * Global Beta-D-Ribo type.
     */
    static const PropertyType* pBeta_D_Ribofuranoside;

    /**
     * Global Alpha-L-Arabino type.
     */
    static const PropertyType* pAlpha_L_Arabinofuranoside;

    /**
     * Global Beta-L-Arabino type.
     */
    static const PropertyType* pBeta_L_Arabinofuranoside;

    /**
     * Global Alpha-D-Arabino type.
     */
    static const PropertyType* pAlpha_D_Arabinofuranoside;

    /**
     * Global Beta-D-Arabino type.
     */
    static const PropertyType* pBeta_D_Arabinofuranoside;

    /**
     * Global Alpha-L-Xylo type.
     */
    static const PropertyType* pAlpha_L_Xylofuranoside;

    /**
     * Global Beta-L-Xylo type.
     */
    static const PropertyType* pBeta_L_Xylofuranoside;

    /**
     * Global Alpha-D-Xylo type.
     */
    static const PropertyType* pAlpha_D_Xylofuranoside;

    /**
     * Global Beta-D-Xylo type.
     */
    static const PropertyType* pBeta_D_Xylofuranoside;

  };
  
  /**
   * Outputs to an exception stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception& ex, const PropertyType &t);

  /**
   * Outputs to an exception  stream.
   * @param out the exception stream.
   * @return the exception stream used.
   */
  Exception& operator<< (Exception& ex, const PropertyType *t);
  
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
   * @exception FatalIntLibException thrown if type is null pointed.
   */
  oBinstream& operator<< (oBinstream &out, const PropertyType *t);

}


namespace std
{

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::PropertyType &t);
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::PropertyType *t);
  
}

#endif
