//                              -*- Mode: C++ -*- 
// PropertyType.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:17:11 2003
// $Revision: 1.9 $
// $Id: PropertyType.cc,v 1.9 2004-08-17 18:26:13 thibaup Exp $
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



namespace mccore {

  // STATIC MEMBERS ------------------------------------------------------------

  PropertyTypeStore PropertyType::ptstore;
  PropertyType* PropertyType::pNull = 0;
  PropertyType* PropertyType::pTheo = 0;
  PropertyType* PropertyType::pPairing = 0;
  PropertyType* PropertyType::pStack = 0;
  PropertyType* PropertyType::pCis = 0;
  PropertyType* PropertyType::pTrans = 0;
  PropertyType* PropertyType::pReverse = 0;
  PropertyType* PropertyType::pAdjacent = 0;
  PropertyType* PropertyType::pType_A = 0;
  PropertyType* PropertyType::pType_B = 0;
  PropertyType* PropertyType::pHelix = 0;
  PropertyType* PropertyType::pC1p_endo = 0;
  PropertyType* PropertyType::pC1p_exo = 0;
  PropertyType* PropertyType::pC2p_endo = 0;
  PropertyType* PropertyType::pC2p_exo = 0;
  PropertyType* PropertyType::pC3p_endo = 0;
  PropertyType* PropertyType::pC3p_exo = 0;
  PropertyType* PropertyType::pC4p_endo = 0;
  PropertyType* PropertyType::pC4p_exo = 0;
  PropertyType* PropertyType::pO4p_endo = 0;
  PropertyType* PropertyType::pO4p_exo = 0;
  PropertyType* PropertyType::pAnti = 0;
  PropertyType* PropertyType::pSyn = 0;
  PropertyType* PropertyType::pDIR_5p = 0;
  PropertyType* PropertyType::pDIR_3p = 0;
  PropertyType* PropertyType::pDIR_ANY = 0;
  //     static PropertyType* pDIR_SH = 0;
  //     static PropertyType* pDIR_HS = 0;
  PropertyType* PropertyType::pSaenger = 0;
  PropertyType* PropertyType::pWC = 0;
  PropertyType* PropertyType::pWobble = 0;
  PropertyType* PropertyType::pI = 0;
  PropertyType* PropertyType::pII = 0;
  PropertyType* PropertyType::pIII = 0;
  PropertyType* PropertyType::pIV = 0;
  PropertyType* PropertyType::pV = 0;
  PropertyType* PropertyType::pVI = 0;
  PropertyType* PropertyType::pVII = 0;
  PropertyType* PropertyType::pVIII = 0;
  PropertyType* PropertyType::pIX = 0;
  PropertyType* PropertyType::pX = 0;
  PropertyType* PropertyType::pXI = 0;
  PropertyType* PropertyType::pXII = 0;
  PropertyType* PropertyType::pXIII = 0;
  PropertyType* PropertyType::pXIV = 0;
  PropertyType* PropertyType::pXV = 0;
  PropertyType* PropertyType::pXVI = 0;
  PropertyType* PropertyType::pXVII = 0;
  PropertyType* PropertyType::pXVIII = 0;
  PropertyType* PropertyType::pXIX = 0;
  PropertyType* PropertyType::pXX = 0;
  PropertyType* PropertyType::pXXI = 0;
  PropertyType* PropertyType::pXXII = 0;
  PropertyType* PropertyType::pXXIII = 0;
  PropertyType* PropertyType::pXXIV = 0;
  PropertyType* PropertyType::pXXV = 0;
  PropertyType* PropertyType::pXXVI = 0;
  PropertyType* PropertyType::pXXVII = 0;
  PropertyType* PropertyType::pXXVIII = 0;
  PropertyType* PropertyType::pOneHbond = 0;
  PropertyType* PropertyType::p29 = 0;
  PropertyType* PropertyType::p30 = 0;
  PropertyType* PropertyType::p31 = 0;
  PropertyType* PropertyType::p32 = 0;
  PropertyType* PropertyType::p33 = 0;
  PropertyType* PropertyType::p34 = 0;
  PropertyType* PropertyType::p35 = 0;
  PropertyType* PropertyType::p36 = 0;
  PropertyType* PropertyType::p37 = 0;
  PropertyType* PropertyType::p38 = 0;
  PropertyType* PropertyType::p39 = 0;
  PropertyType* PropertyType::p40 = 0;
  PropertyType* PropertyType::p41 = 0;
  PropertyType* PropertyType::p42 = 0;
  PropertyType* PropertyType::p43 = 0;
  PropertyType* PropertyType::p44 = 0;
  PropertyType* PropertyType::p45 = 0;
  PropertyType* PropertyType::p46 = 0;
  PropertyType* PropertyType::p47 = 0;
  PropertyType* PropertyType::p48 = 0;
  PropertyType* PropertyType::p49 = 0;
  PropertyType* PropertyType::p50 = 0;
  PropertyType* PropertyType::p51 = 0;
  PropertyType* PropertyType::p52 = 0;
  PropertyType* PropertyType::p53 = 0;
  PropertyType* PropertyType::p54 = 0;
  PropertyType* PropertyType::p55 = 0;
  PropertyType* PropertyType::p56 = 0;
  PropertyType* PropertyType::p57 = 0;
  PropertyType* PropertyType::p58 = 0;
  PropertyType* PropertyType::p59 = 0;
  PropertyType* PropertyType::p60 = 0;
  PropertyType* PropertyType::p61 = 0;
  PropertyType* PropertyType::p62 = 0;
  PropertyType* PropertyType::p63 = 0;
  PropertyType* PropertyType::p64 = 0;
  PropertyType* PropertyType::p65 = 0;
  PropertyType* PropertyType::p66 = 0;
  PropertyType* PropertyType::p67 = 0;
  PropertyType* PropertyType::p68 = 0;
  PropertyType* PropertyType::p69 = 0;
  PropertyType* PropertyType::p70 = 0;
  PropertyType* PropertyType::p71 = 0;
  PropertyType* PropertyType::p72 = 0;
  PropertyType* PropertyType::p73 = 0;
  PropertyType* PropertyType::p74 = 0;
  PropertyType* PropertyType::p75 = 0;
  PropertyType* PropertyType::p76 = 0;
  PropertyType* PropertyType::p77 = 0;
  PropertyType* PropertyType::p78 = 0;
  PropertyType* PropertyType::p79 = 0;
  PropertyType* PropertyType::p80 = 0;
  PropertyType* PropertyType::p81 = 0;
  PropertyType* PropertyType::p82 = 0;
  PropertyType* PropertyType::p83 = 0;
  PropertyType* PropertyType::p84 = 0;
  PropertyType* PropertyType::p85 = 0;
  PropertyType* PropertyType::p86 = 0;
  PropertyType* PropertyType::p87 = 0;
  PropertyType* PropertyType::p88 = 0;
  PropertyType* PropertyType::p89 = 0;
  PropertyType* PropertyType::p90 = 0;
  PropertyType* PropertyType::p91 = 0;
  PropertyType* PropertyType::p92 = 0;
  PropertyType* PropertyType::p93 = 0;
  PropertyType* PropertyType::p94 = 0;
  PropertyType* PropertyType::p95 = 0;
  PropertyType* PropertyType::p96 = 0;
  PropertyType* PropertyType::p97 = 0;
  PropertyType* PropertyType::p98 = 0;
  PropertyType* PropertyType::p99 = 0;
  PropertyType* PropertyType::p100 = 0;
  PropertyType* PropertyType::p101 = 0;
  PropertyType* PropertyType::p102 = 0;
  PropertyType* PropertyType::p103 = 0;
  PropertyType* PropertyType::p104 = 0;
  PropertyType* PropertyType::p105 = 0;
  PropertyType* PropertyType::p106 = 0;
  PropertyType* PropertyType::p108 = 0;
  PropertyType* PropertyType::p109 = 0;
  PropertyType* PropertyType::p110 = 0;
  PropertyType* PropertyType::p111 = 0;
  PropertyType* PropertyType::p112 = 0;
  PropertyType* PropertyType::p113 = 0;
  PropertyType* PropertyType::p114 = 0;
  PropertyType* PropertyType::p115 = 0;
  PropertyType* PropertyType::p116 = 0;
  PropertyType* PropertyType::p117 = 0;
  PropertyType* PropertyType::p118 = 0;
  PropertyType* PropertyType::p119 = 0;
  PropertyType* PropertyType::p120 = 0;
  PropertyType* PropertyType::p121 = 0;
  PropertyType* PropertyType::p122 = 0;
  PropertyType* PropertyType::p123 = 0;
  PropertyType* PropertyType::p124 = 0;
  PropertyType* PropertyType::p125 = 0;
  PropertyType* PropertyType::p126 = 0;
  PropertyType* PropertyType::p127 = 0;
  PropertyType* PropertyType::p128 = 0;
  PropertyType* PropertyType::p129 = 0;
  PropertyType* PropertyType::p130 = 0;
  PropertyType* PropertyType::p131 = 0;
  PropertyType* PropertyType::p132 = 0;
  PropertyType* PropertyType::p133 = 0;
  PropertyType* PropertyType::p134 = 0;
  PropertyType* PropertyType::p135 = 0;
  PropertyType* PropertyType::p136 = 0;
  PropertyType* PropertyType::p137 = 0;
  //     static PropertyType* pwct = 0;
  //     static PropertyType* pconnect = 0;
  //     static PropertyType* pwobblet = 0;
  //     static PropertyType* pnon_adjacent = 0;
  //     static PropertyType* pstrong = 0;
  //     static PropertyType* pweak = 0;
  //     static PropertyType* pnostack = 0;
  PropertyType* PropertyType::pW = 0;
  PropertyType* PropertyType::pS = 0;
  PropertyType* PropertyType::pH = 0;
  PropertyType* PropertyType::pWs = 0;
  PropertyType* PropertyType::pWw = 0;
  PropertyType* PropertyType::pWh = 0;
  PropertyType* PropertyType::pSw = 0;
  PropertyType* PropertyType::pSs = 0;
  PropertyType* PropertyType::pHw = 0;
  PropertyType* PropertyType::pHh = 0;
  PropertyType* PropertyType::pC8 = 0;
  PropertyType* PropertyType::pBs = 0;
  PropertyType* PropertyType::pBh = 0;
  
  // LIFECYCLE -----------------------------------------------------------------

  PropertyType::PropertyType () 
    : type (0) 
  {
  }


  PropertyType::PropertyType (const char* t) 
  {
    type = new char[strlen (t) + 1];
    strcpy (type, t);
  }
  

  PropertyType::PropertyType (const PropertyType &other)
  {
  }


  PropertyType::~PropertyType () 
  {
    if (type) delete[] type;
  }
 
 
  // METHODS -------------------------------------------------------------------


  const PropertyType* 
  PropertyType::parseType (const char* s) 
  {
    return ptstore.get (s);
  }

  
  // I/O -----------------------------------------------------------------------


  ostream &
  PropertyType::output (ostream &out) const
  {
    return out << type;
  }
  

  oBinstream &
  PropertyType::output (oBinstream &out) const
  {
    return out << type;
  }


  ostream &
  operator<< (ostream &out, const PropertyType &t)
  {
    return t.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const PropertyType *t)
  {
    return (t == 0 ? PropertyType::pNull : t)->output (out);
  }

  
  Exception&
  operator<< (Exception& ex, const PropertyType &t)
  {
    return ex << (const char*)t;
  }

  
  Exception&
  operator<< (Exception& ex, const PropertyType *t)
  {
    return ex << (const char*)(t == 0 ? PropertyType::pNull : t);
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const PropertyType *t)
  {
    return (t == 0 ? PropertyType::pNull : t)->output (obs);
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
