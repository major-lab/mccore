//                              -*- Mode: C++ -*- 
// PropertyType.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:17:11 2003
// $Revision: 1.14 $
// $Id: PropertyType.cc,v 1.14 2005-01-07 17:09:38 thibaup Exp $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "PropertyType.h"
#include "PropertyTypeStore.h"
#include "Exception.h"
#include "Binstream.h"



namespace mccore
{

  // STATIC MEMBERS ------------------------------------------------------------

  PropertyTypeStore PropertyType::ptstore;

  const PropertyType* PropertyType::pNull = 0;
  const PropertyType* PropertyType::pUnknown = 0;
  const PropertyType* PropertyType::pTheo = 0;

  const PropertyType* PropertyType::pAdjacent = 0;
  const PropertyType* PropertyType::pAdjacent5p = 0;
  const PropertyType* PropertyType::pAdjacent3p = 0;
  
  const PropertyType* PropertyType::pStack = 0;
  const PropertyType* PropertyType::pStraightUpward = 0;
  const PropertyType* PropertyType::pStraightDownward = 0;
  const PropertyType* PropertyType::pReverseUpward = 0;
  const PropertyType* PropertyType::pReverseDownward = 0;

  const PropertyType* PropertyType::pPairing = 0;
  const PropertyType* PropertyType::pCis = 0;
  const PropertyType* PropertyType::pTrans = 0;
  const PropertyType* PropertyType::pStraight = 0;
  const PropertyType* PropertyType::pReverse = 0;

  const PropertyType* PropertyType::pType_A = 0;
  const PropertyType* PropertyType::pType_B = 0;
  const PropertyType* PropertyType::pHelix = 0;
  const PropertyType* PropertyType::pC1p_endo = 0;
  const PropertyType* PropertyType::pC1p_exo = 0;
  const PropertyType* PropertyType::pC2p_endo = 0;
  const PropertyType* PropertyType::pC2p_exo = 0;
  const PropertyType* PropertyType::pC3p_endo = 0;
  const PropertyType* PropertyType::pC3p_exo = 0;
  const PropertyType* PropertyType::pC4p_endo = 0;
  const PropertyType* PropertyType::pC4p_exo = 0;
  const PropertyType* PropertyType::pO4p_endo = 0;
  const PropertyType* PropertyType::pO4p_exo = 0;
  const PropertyType* PropertyType::pAnti = 0;
  const PropertyType* PropertyType::pSyn = 0;

  const PropertyType* PropertyType::pSaenger = 0;
  const PropertyType* PropertyType::pWC = 0;
  const PropertyType* PropertyType::pWobble = 0;
  const PropertyType* PropertyType::pI = 0;
  const PropertyType* PropertyType::pII = 0;
  const PropertyType* PropertyType::pIII = 0;
  const PropertyType* PropertyType::pIV = 0;
  const PropertyType* PropertyType::pV = 0;
  const PropertyType* PropertyType::pVI = 0;
  const PropertyType* PropertyType::pVII = 0;
  const PropertyType* PropertyType::pVIII = 0;
  const PropertyType* PropertyType::pIX = 0;
  const PropertyType* PropertyType::pX = 0;
  const PropertyType* PropertyType::pXI = 0;
  const PropertyType* PropertyType::pXII = 0;
  const PropertyType* PropertyType::pXIII = 0;
  const PropertyType* PropertyType::pXIV = 0;
  const PropertyType* PropertyType::pXV = 0;
  const PropertyType* PropertyType::pXVI = 0;
  const PropertyType* PropertyType::pXVII = 0;
  const PropertyType* PropertyType::pXVIII = 0;
  const PropertyType* PropertyType::pXIX = 0;
  const PropertyType* PropertyType::pXX = 0;
  const PropertyType* PropertyType::pXXI = 0;
  const PropertyType* PropertyType::pXXII = 0;
  const PropertyType* PropertyType::pXXIII = 0;
  const PropertyType* PropertyType::pXXIV = 0;
  const PropertyType* PropertyType::pXXV = 0;
  const PropertyType* PropertyType::pXXVI = 0;
  const PropertyType* PropertyType::pXXVII = 0;
  const PropertyType* PropertyType::pXXVIII = 0;
  const PropertyType* PropertyType::pOneHbond = 0;
  const PropertyType* PropertyType::p29 = 0;
  const PropertyType* PropertyType::p30 = 0;
  const PropertyType* PropertyType::p31 = 0;
  const PropertyType* PropertyType::p32 = 0;
  const PropertyType* PropertyType::p33 = 0;
  const PropertyType* PropertyType::p34 = 0;
  const PropertyType* PropertyType::p35 = 0;
  const PropertyType* PropertyType::p36 = 0;
  const PropertyType* PropertyType::p37 = 0;
  const PropertyType* PropertyType::p38 = 0;
  const PropertyType* PropertyType::p39 = 0;
  const PropertyType* PropertyType::p40 = 0;
  const PropertyType* PropertyType::p41 = 0;
  const PropertyType* PropertyType::p42 = 0;
  const PropertyType* PropertyType::p43 = 0;
  const PropertyType* PropertyType::p44 = 0;
  const PropertyType* PropertyType::p45 = 0;
  const PropertyType* PropertyType::p46 = 0;
  const PropertyType* PropertyType::p47 = 0;
  const PropertyType* PropertyType::p48 = 0;
  const PropertyType* PropertyType::p49 = 0;
  const PropertyType* PropertyType::p50 = 0;
  const PropertyType* PropertyType::p51 = 0;
  const PropertyType* PropertyType::p52 = 0;
  const PropertyType* PropertyType::p53 = 0;
  const PropertyType* PropertyType::p54 = 0;
  const PropertyType* PropertyType::p55 = 0;
  const PropertyType* PropertyType::p56 = 0;
  const PropertyType* PropertyType::p57 = 0;
  const PropertyType* PropertyType::p58 = 0;
  const PropertyType* PropertyType::p59 = 0;
  const PropertyType* PropertyType::p60 = 0;
  const PropertyType* PropertyType::p61 = 0;
  const PropertyType* PropertyType::p62 = 0;
  const PropertyType* PropertyType::p63 = 0;
  const PropertyType* PropertyType::p64 = 0;
  const PropertyType* PropertyType::p65 = 0;
  const PropertyType* PropertyType::p66 = 0;
  const PropertyType* PropertyType::p67 = 0;
  const PropertyType* PropertyType::p68 = 0;
  const PropertyType* PropertyType::p69 = 0;
  const PropertyType* PropertyType::p70 = 0;
  const PropertyType* PropertyType::p71 = 0;
  const PropertyType* PropertyType::p72 = 0;
  const PropertyType* PropertyType::p73 = 0;
  const PropertyType* PropertyType::p74 = 0;
  const PropertyType* PropertyType::p75 = 0;
  const PropertyType* PropertyType::p76 = 0;
  const PropertyType* PropertyType::p77 = 0;
  const PropertyType* PropertyType::p78 = 0;
  const PropertyType* PropertyType::p79 = 0;
  const PropertyType* PropertyType::p80 = 0;
  const PropertyType* PropertyType::p81 = 0;
  const PropertyType* PropertyType::p82 = 0;
  const PropertyType* PropertyType::p83 = 0;
  const PropertyType* PropertyType::p84 = 0;
  const PropertyType* PropertyType::p85 = 0;
  const PropertyType* PropertyType::p86 = 0;
  const PropertyType* PropertyType::p87 = 0;
  const PropertyType* PropertyType::p88 = 0;
  const PropertyType* PropertyType::p89 = 0;
  const PropertyType* PropertyType::p90 = 0;
  const PropertyType* PropertyType::p91 = 0;
  const PropertyType* PropertyType::p92 = 0;
  const PropertyType* PropertyType::p93 = 0;
  const PropertyType* PropertyType::p94 = 0;
  const PropertyType* PropertyType::p95 = 0;
  const PropertyType* PropertyType::p96 = 0;
  const PropertyType* PropertyType::p97 = 0;
  const PropertyType* PropertyType::p98 = 0;
  const PropertyType* PropertyType::p99 = 0;
  const PropertyType* PropertyType::p100 = 0;
  const PropertyType* PropertyType::p101 = 0;
  const PropertyType* PropertyType::p102 = 0;
  const PropertyType* PropertyType::p103 = 0;
  const PropertyType* PropertyType::p104 = 0;
  const PropertyType* PropertyType::p105 = 0;
  const PropertyType* PropertyType::p106 = 0;
  const PropertyType* PropertyType::p108 = 0;
  const PropertyType* PropertyType::p109 = 0;
  const PropertyType* PropertyType::p110 = 0;
  const PropertyType* PropertyType::p111 = 0;
  const PropertyType* PropertyType::p112 = 0;
  const PropertyType* PropertyType::p113 = 0;
  const PropertyType* PropertyType::p114 = 0;
  const PropertyType* PropertyType::p115 = 0;
  const PropertyType* PropertyType::p116 = 0;
  const PropertyType* PropertyType::p117 = 0;
  const PropertyType* PropertyType::p118 = 0;
  const PropertyType* PropertyType::p119 = 0;
  const PropertyType* PropertyType::p120 = 0;
  const PropertyType* PropertyType::p121 = 0;
  const PropertyType* PropertyType::p122 = 0;
  const PropertyType* PropertyType::p123 = 0;
  const PropertyType* PropertyType::p124 = 0;
  const PropertyType* PropertyType::p125 = 0;
  const PropertyType* PropertyType::p126 = 0;
  const PropertyType* PropertyType::p127 = 0;
  const PropertyType* PropertyType::p128 = 0;
  const PropertyType* PropertyType::p129 = 0;
  const PropertyType* PropertyType::p130 = 0;
  const PropertyType* PropertyType::p131 = 0;
  const PropertyType* PropertyType::p132 = 0;
  const PropertyType* PropertyType::p133 = 0;
  const PropertyType* PropertyType::p134 = 0;
  const PropertyType* PropertyType::p135 = 0;
  const PropertyType* PropertyType::p136 = 0;
  const PropertyType* PropertyType::p137 = 0;
  const PropertyType* PropertyType::pW = 0;
  const PropertyType* PropertyType::pS = 0;
  const PropertyType* PropertyType::pH = 0;
  const PropertyType* PropertyType::pWs = 0;
  const PropertyType* PropertyType::pWw = 0;
  const PropertyType* PropertyType::pWh = 0;
  const PropertyType* PropertyType::pSw = 0;
  const PropertyType* PropertyType::pSs = 0;
  const PropertyType* PropertyType::pHw = 0;
  const PropertyType* PropertyType::pHh = 0;
  const PropertyType* PropertyType::pC8 = 0;
  const PropertyType* PropertyType::pBs = 0;
  const PropertyType* PropertyType::pBh = 0;

  
  // LIFECYCLE -----------------------------------------------------------------

  PropertyType::PropertyType () 
  {
    
  }


  PropertyType::PropertyType (const string& ks)
    : key (ks)
  {
    
  }
  

  PropertyType::PropertyType (const PropertyType &other)
  {
    FatalIntLibException ex ("", __FILE__, __LINE__);
    ex << "Use of copy constructor for class PropertyType is prohibited.";
    throw ex;
  }


  PropertyType::~PropertyType () 
  {
    
  }
 
 
  // METHODS -------------------------------------------------------------------

  
  const PropertyType* 
  PropertyType::parseType (const char* str) 
  {
    string ks (str);
    return ptstore.get (ks);
  }

  
  const PropertyType* 
  PropertyType::parseType (const string& str) 
  {
    return ptstore.get (str);
  }

  
  const PropertyType*
  PropertyType::invert (const PropertyType* t)
  {
    if (PropertyType::pStraightUpward == t) return PropertyType::pStraightDownward;
    if (PropertyType::pStraightDownward == t) return PropertyType::pStraightUpward;

    if (PropertyType::pAdjacent5p == t) return PropertyType::pAdjacent3p;
    if (PropertyType::pAdjacent3p == t) return PropertyType::pAdjacent5p;

    return t;
  }

  
  // I/O -----------------------------------------------------------------------


  ostream &
  PropertyType::output (ostream &out) const
  {
    return out << key.c_str ();
  }
  

  oBinstream &
  PropertyType::output (oBinstream &out) const
  {
    return out << key.c_str ();
  }


  Exception&
  operator<< (Exception& ex, const PropertyType &t)
  {
    return ex << (const char*)t;
  }

  
  Exception&
  operator<< (Exception& ex, const PropertyType *t)
  {
    return ex << (const char*)*(t == 0 ? PropertyType::pNull : t);
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const PropertyType *t)
  {
    if (0 == t)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Cannot write null-pointed property type to binstream: use PropertyType::pNull";
      throw ex;
    }
    return t->output (obs);
  }
 

  iBinstream&
  operator>> (iBinstream &ibs, const PropertyType *&t)
  {
    char* str;
    ibs >> &str;
    t = PropertyType::parseType (str);
    delete[] str;
    return ibs;
  }

}


namespace std
{

  ostream &
  operator<< (ostream &out, const mccore::PropertyType &t)
  {
    return t.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const mccore::PropertyType *t)
  {
    return (t == 0 ? mccore::PropertyType::pNull : t)->output (out);
  }

}
