//                              -*- Mode: C++ -*- 
// PropertyType.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:17:11 2003
// $Revision: 1.7 $
// $Id: PropertyType.cc,v 1.7 2004-06-25 14:40:20 thibaup Exp $
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
#include "CException.h"
#include "Binstream.h"



namespace mccore {

  // STATIC MEMBERS ------------------------------------------------------------

  PropertyTypeStore PropertyType::ptstore;
  PropertyType* PropertyType::pTheo;
  PropertyType* PropertyType::pPairing;
  PropertyType* PropertyType::pStack;
  PropertyType* PropertyType::pCis;
  PropertyType* PropertyType::pTrans;
  PropertyType* PropertyType::pReverse;
  PropertyType* PropertyType::pAdjacent;
  PropertyType* PropertyType::pType_A;
  PropertyType* PropertyType::pType_B;
  PropertyType* PropertyType::pHelix;
  PropertyType* PropertyType::pC1p_endo;
  PropertyType* PropertyType::pC1p_exo;
  PropertyType* PropertyType::pC2p_endo;
  PropertyType* PropertyType::pC2p_exo;
  PropertyType* PropertyType::pC3p_endo;
  PropertyType* PropertyType::pC3p_exo;
  PropertyType* PropertyType::pC4p_endo;
  PropertyType* PropertyType::pC4p_exo;
  PropertyType* PropertyType::pO4p_endo;
  PropertyType* PropertyType::pO4p_exo;
  PropertyType* PropertyType::pAnti;
  PropertyType* PropertyType::pSyn;
  PropertyType* PropertyType::pDIR_5p;
  PropertyType* PropertyType::pDIR_3p;
  PropertyType* PropertyType::pDIR_ANY;
  //     static PropertyType* pDIR_SH;
  //     static PropertyType* pDIR_HS;
  PropertyType* PropertyType::pSaenger;
  PropertyType* PropertyType::pWC;
  PropertyType* PropertyType::pWobble;
  PropertyType* PropertyType::pI;
  PropertyType* PropertyType::pII;
  PropertyType* PropertyType::pIII;
  PropertyType* PropertyType::pIV;
  PropertyType* PropertyType::pV;
  PropertyType* PropertyType::pVI;
  PropertyType* PropertyType::pVII;
  PropertyType* PropertyType::pVIII;
  PropertyType* PropertyType::pIX;
  PropertyType* PropertyType::pX;
  PropertyType* PropertyType::pXI;
  PropertyType* PropertyType::pXII;
  PropertyType* PropertyType::pXIII;
  PropertyType* PropertyType::pXIV;
  PropertyType* PropertyType::pXV;
  PropertyType* PropertyType::pXVI;
  PropertyType* PropertyType::pXVII;
  PropertyType* PropertyType::pXVIII;
  PropertyType* PropertyType::pXIX;
  PropertyType* PropertyType::pXX;
  PropertyType* PropertyType::pXXI;
  PropertyType* PropertyType::pXXII;
  PropertyType* PropertyType::pXXIII;
  PropertyType* PropertyType::pXXIV;
  PropertyType* PropertyType::pXXV;
  PropertyType* PropertyType::pXXVI;
  PropertyType* PropertyType::pXXVII;
  PropertyType* PropertyType::pXXVIII;
  PropertyType* PropertyType::pOneHbond;
  PropertyType* PropertyType::p29;
  PropertyType* PropertyType::p30;
  PropertyType* PropertyType::p31;
  PropertyType* PropertyType::p32;
  PropertyType* PropertyType::p33;
  PropertyType* PropertyType::p34;
  PropertyType* PropertyType::p35;
  PropertyType* PropertyType::p36;
  PropertyType* PropertyType::p37;
  PropertyType* PropertyType::p38;
  PropertyType* PropertyType::p39;
  PropertyType* PropertyType::p40;
  PropertyType* PropertyType::p41;
  PropertyType* PropertyType::p42;
  PropertyType* PropertyType::p43;
  PropertyType* PropertyType::p44;
  PropertyType* PropertyType::p45;
  PropertyType* PropertyType::p46;
  PropertyType* PropertyType::p47;
  PropertyType* PropertyType::p48;
  PropertyType* PropertyType::p49;
  PropertyType* PropertyType::p50;
  PropertyType* PropertyType::p51;
  PropertyType* PropertyType::p52;
  PropertyType* PropertyType::p53;
  PropertyType* PropertyType::p54;
  PropertyType* PropertyType::p55;
  PropertyType* PropertyType::p56;
  PropertyType* PropertyType::p57;
  PropertyType* PropertyType::p58;
  PropertyType* PropertyType::p59;
  PropertyType* PropertyType::p60;
  PropertyType* PropertyType::p61;
  PropertyType* PropertyType::p62;
  PropertyType* PropertyType::p63;
  PropertyType* PropertyType::p64;
  PropertyType* PropertyType::p65;
  PropertyType* PropertyType::p66;
  PropertyType* PropertyType::p67;
  PropertyType* PropertyType::p68;
  PropertyType* PropertyType::p69;
  PropertyType* PropertyType::p70;
  PropertyType* PropertyType::p71;
  PropertyType* PropertyType::p72;
  PropertyType* PropertyType::p73;
  PropertyType* PropertyType::p74;
  PropertyType* PropertyType::p75;
  PropertyType* PropertyType::p76;
  PropertyType* PropertyType::p77;
  PropertyType* PropertyType::p78;
  PropertyType* PropertyType::p79;
  PropertyType* PropertyType::p80;
  PropertyType* PropertyType::p81;
  PropertyType* PropertyType::p82;
  PropertyType* PropertyType::p83;
  PropertyType* PropertyType::p84;
  PropertyType* PropertyType::p85;
  PropertyType* PropertyType::p86;
  PropertyType* PropertyType::p87;
  PropertyType* PropertyType::p88;
  PropertyType* PropertyType::p89;
  PropertyType* PropertyType::p90;
  PropertyType* PropertyType::p91;
  PropertyType* PropertyType::p92;
  PropertyType* PropertyType::p93;
  PropertyType* PropertyType::p94;
  PropertyType* PropertyType::p95;
  PropertyType* PropertyType::p96;
  PropertyType* PropertyType::p97;
  PropertyType* PropertyType::p98;
  PropertyType* PropertyType::p99;
  PropertyType* PropertyType::p100;
  PropertyType* PropertyType::p101;
  PropertyType* PropertyType::p102;
  PropertyType* PropertyType::p103;
  PropertyType* PropertyType::p104;
  PropertyType* PropertyType::p105;
  PropertyType* PropertyType::p106;
  PropertyType* PropertyType::p108;
  PropertyType* PropertyType::p109;
  PropertyType* PropertyType::p110;
  PropertyType* PropertyType::p111;
  PropertyType* PropertyType::p112;
  PropertyType* PropertyType::p113;
  PropertyType* PropertyType::p114;
  PropertyType* PropertyType::p115;
  PropertyType* PropertyType::p116;
  PropertyType* PropertyType::p117;
  PropertyType* PropertyType::p118;
  PropertyType* PropertyType::p119;
  PropertyType* PropertyType::p120;
  PropertyType* PropertyType::p121;
  PropertyType* PropertyType::p122;
  PropertyType* PropertyType::p123;
  PropertyType* PropertyType::p124;
  PropertyType* PropertyType::p125;
  PropertyType* PropertyType::p126;
  PropertyType* PropertyType::p127;
  PropertyType* PropertyType::p128;
  PropertyType* PropertyType::p129;
  PropertyType* PropertyType::p130;
  PropertyType* PropertyType::p131;
  PropertyType* PropertyType::p132;
  PropertyType* PropertyType::p133;
  PropertyType* PropertyType::p134;
  PropertyType* PropertyType::p135;
  PropertyType* PropertyType::p136;
  PropertyType* PropertyType::p137;
  //     static PropertyType* pwct;
  //     static PropertyType* pconnect;
  //     static PropertyType* pwobblet;
  //     static PropertyType* pnon_adjacent;
  //     static PropertyType* pstrong;
  //     static PropertyType* pweak;
  //     static PropertyType* pnostack;
  PropertyType* PropertyType::pW;
  PropertyType* PropertyType::pS;
  PropertyType* PropertyType::pH;
  PropertyType* PropertyType::pWs;
  PropertyType* PropertyType::pWw;
  PropertyType* PropertyType::pWh;
  PropertyType* PropertyType::pSw;
  PropertyType* PropertyType::pSs;
  PropertyType* PropertyType::pHw;
  PropertyType* PropertyType::pHh;
  PropertyType* PropertyType::pC8;
  PropertyType* PropertyType::pBs;
  PropertyType* PropertyType::pBh;
  
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
    if (!t) out << "null";
    else t->output (out);
    return out;
  }

  
  CException&
  operator<< (CException& ex, const PropertyType &t)
  {
    return ex << (const char*)t;
  }

  
  CException&
  operator<< (CException& ex, const PropertyType *t)
  {
    return t == 0 ? (ex << "null") : (ex << (const char*)*t);
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const PropertyType *t)
  {
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
