//                              -*- Mode: C++ -*- 
// PropertyTypeStore.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:42:25 2003
// $Revision: 1.15 $
// $Id: PropertyTypeStore.cc,v 1.15 2005-11-17 19:26:38 thibaup Exp $
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

#include "PropertyTypeStore.h"



namespace mccore
{

  PropertyTypeStore::PropertyTypeStore () 
  {
    string str;

    PropertyType::pNull = *this->repository.insert (new Null ((str = ""))).first;
    PropertyType::pUnknown = *this->repository.insert (new Unknown ((str = "unknown"))).first;

    PropertyType::pAdjacent = *this->repository.insert (new Adjacent ((str = "adjacent"))).first;
    PropertyType::pAdjacent5p = *this->repository.insert (new Adjacent5p ((str = "adjacent_5p"))).first;
    PropertyType::pAdjacent3p = *this->repository.insert (new Adjacent3p ((str = "adjacent_3p"))).first;

    PropertyType::pStack = *this->repository.insert (new Stack ((str = "stack"))).first;
    PropertyType::pUpward = *this->repository.insert (new Upward ((str = "upward"))).first;
    PropertyType::pDownward = *this->repository.insert (new Downward ((str = "downward"))).first;
    PropertyType::pInward = *this->repository.insert (new Inward ((str = "inward"))).first;
    PropertyType::pOutward = *this->repository.insert (new Outward ((str = "outward"))).first;
    
    PropertyType::pPairing = *this->repository.insert (new Pairing ((str = "pairing"))).first;
    PropertyType::pParallel = *this->repository.insert (new Parallel ((str = "parallel"))).first;
    PropertyType::pAntiparallel = *this->repository.insert (new Antiparallel ((str = "antiparallel"))).first;
    PropertyType::pCis = *this->repository.insert (new Cis ((str = "cis"))).first;
    PropertyType::pTrans = *this->repository.insert (new Trans ((str = "trans"))).first;

    PropertyType::pType_A = *this->repository.insert (new Type_A ((str = "type_A"))).first;
    PropertyType::pType_B = *this->repository.insert (new Type_B ((str = "type_B"))).first;
    PropertyType::pHelix = *this->repository.insert (new Helix ((str = "helix"))).first;
    PropertyType::pC1p_endo = *this->repository.insert (new C1p_endo ((str = "C1p_endo"))).first;
    PropertyType::pC1p_exo = *this->repository.insert (new C1p_exo ((str = "C1p_exo"))).first;
    PropertyType::pC2p_endo = *this->repository.insert (new C2p_endo ((str = "C2p_endo"))).first;
    PropertyType::pC2p_exo = *this->repository.insert (new C2p_exo ((str = "C2p_exo"))).first;
    PropertyType::pC3p_endo = *this->repository.insert (new C3p_endo ((str = "C3p_endo"))).first;
    PropertyType::pC3p_exo = *this->repository.insert (new C3p_exo ((str = "C3p_exo"))).first;
    PropertyType::pC4p_endo = *this->repository.insert (new C4p_endo ((str = "C4p_endo"))).first;
    PropertyType::pC4p_exo = *this->repository.insert (new C4p_exo ((str = "C4p_exo"))).first;
    PropertyType::pO4p_endo = *this->repository.insert (new O4p_endo ((str = "O4p_endo"))).first;
    PropertyType::pO4p_exo = *this->repository.insert (new O4p_exo ((str = "O4p_exo"))).first;
    PropertyType::pAnti = *this->repository.insert (new Anti ((str = "anti"))).first;
    PropertyType::pSyn = *this->repository.insert (new Syn ((str = "syn"))).first;
    PropertyType::pSaenger = *this->repository.insert (new Saenger ((str = "saenger"))).first;
    PropertyType::pWC = *this->repository.insert (new WC ((str = "wc"))).first;
    PropertyType::pWobble = *this->repository.insert (new Wobble ((str = "wobble"))).first;
    PropertyType::pI = *this->repository.insert (new PI ((str = "I"))).first;
    PropertyType::pII = *this->repository.insert (new PII ((str = "II"))).first;
    PropertyType::pIII = *this->repository.insert (new PIII ((str = "III"))).first;
    PropertyType::pIV = *this->repository.insert (new PIV ((str = "IV"))).first;
    PropertyType::pV = *this->repository.insert (new PV ((str = "V"))).first;
    PropertyType::pVI = *this->repository.insert (new PVI ((str = "VI"))).first;
    PropertyType::pVII = *this->repository.insert (new PVII ((str = "VII"))).first;
    PropertyType::pVIII = *this->repository.insert (new PVIII ((str = "VIII"))).first;
    PropertyType::pIX = *this->repository.insert (new PIX ((str = "IX"))).first;
    PropertyType::pX = *this->repository.insert (new PX ((str = "X"))).first;
    PropertyType::pXI = *this->repository.insert (new PXI ((str = "XI"))).first;
    PropertyType::pXII = *this->repository.insert (new PXII ((str = "XII"))).first;
    PropertyType::pXIII = *this->repository.insert (new PXIII ((str = "XIII"))).first;
    PropertyType::pXIV = *this->repository.insert (new PXIV ((str = "XIV"))).first;
    PropertyType::pXV = *this->repository.insert (new PXV ((str = "XV"))).first;
    PropertyType::pXVI = *this->repository.insert (new PXVI ((str = "XVI"))).first;
    PropertyType::pXVII = *this->repository.insert (new PXVII ((str = "XVII"))).first;
    PropertyType::pXVIII = *this->repository.insert (new PXVIII ((str = "XVIII"))).first;
    PropertyType::pXIX = *this->repository.insert (new PXIX ((str = "XIX"))).first;
    PropertyType::pXX = *this->repository.insert (new PXX ((str = "XX"))).first;
    PropertyType::pXXI = *this->repository.insert (new PXXI ((str = "XXI"))).first;
    PropertyType::pXXII = *this->repository.insert (new PXXII ((str = "XXII"))).first;
    PropertyType::pXXIII = *this->repository.insert (new PXXIII ((str = "XXIII"))).first;
    PropertyType::pXXIV = *this->repository.insert (new PXXIV ((str = "XXIV"))).first;
    PropertyType::pXXV = *this->repository.insert (new PXXV ((str = "XXV"))).first;
    PropertyType::pXXVI = *this->repository.insert (new PXXVI ((str = "XXVI"))).first;
    PropertyType::pXXVII = *this->repository.insert (new PXXVII ((str = "XXVII"))).first;
    PropertyType::pXXVIII = *this->repository.insert (new PXXVIII ((str = "XXVIII"))).first;
    PropertyType::pOneHbond = *this->repository.insert (new OneHbond ((str = "one_hbond"))).first;
    PropertyType::p29 = *this->repository.insert (new P29 ((str = "29"))).first;
    PropertyType::p30 = *this->repository.insert (new P30 ((str = "30"))).first;
    PropertyType::p31 = *this->repository.insert (new P31 ((str = "31"))).first;
    PropertyType::p32 = *this->repository.insert (new P32 ((str = "32"))).first;
    PropertyType::p33 = *this->repository.insert (new P33 ((str = "33"))).first;
    PropertyType::p34 = *this->repository.insert (new P34 ((str = "34"))).first;
    PropertyType::p35 = *this->repository.insert (new P35 ((str = "35"))).first;
    PropertyType::p36 = *this->repository.insert (new P36 ((str = "36"))).first;
    PropertyType::p37 = *this->repository.insert (new P37 ((str = "37"))).first;
    PropertyType::p38 = *this->repository.insert (new P38 ((str = "38"))).first;
    PropertyType::p39 = *this->repository.insert (new P39 ((str = "39"))).first;
    PropertyType::p40 = *this->repository.insert (new P40 ((str = "40"))).first;
    PropertyType::p41 = *this->repository.insert (new P41 ((str = "41"))).first;
    PropertyType::p42 = *this->repository.insert (new P42 ((str = "42"))).first;
    PropertyType::p43 = *this->repository.insert (new P43 ((str = "43"))).first;
    PropertyType::p44 = *this->repository.insert (new P44 ((str = "44"))).first;
    PropertyType::p45 = *this->repository.insert (new P45 ((str = "45"))).first;
    PropertyType::p46 = *this->repository.insert (new P46 ((str = "46"))).first;
    PropertyType::p47 = *this->repository.insert (new P47 ((str = "47"))).first;
    PropertyType::p48 = *this->repository.insert (new P48 ((str = "48"))).first;
    PropertyType::p49 = *this->repository.insert (new P49 ((str = "49"))).first;
    PropertyType::p50 = *this->repository.insert (new P50 ((str = "50"))).first;
    PropertyType::p51 = *this->repository.insert (new P51 ((str = "51"))).first;
    PropertyType::p52 = *this->repository.insert (new P52 ((str = "52"))).first;
    PropertyType::p53 = *this->repository.insert (new P53 ((str = "53"))).first;
    PropertyType::p54 = *this->repository.insert (new P54 ((str = "54"))).first;
    PropertyType::p55 = *this->repository.insert (new P55 ((str = "55"))).first;
    PropertyType::p56 = *this->repository.insert (new P56 ((str = "56"))).first;
    PropertyType::p57 = *this->repository.insert (new P57 ((str = "57"))).first;
    PropertyType::p58 = *this->repository.insert (new P58 ((str = "58"))).first;
    PropertyType::p59 = *this->repository.insert (new P59 ((str = "59"))).first;
    PropertyType::p60 = *this->repository.insert (new P60 ((str = "60"))).first;
    PropertyType::p61 = *this->repository.insert (new P61 ((str = "61"))).first;
    PropertyType::p62 = *this->repository.insert (new P62 ((str = "62"))).first;
    PropertyType::p63 = *this->repository.insert (new P63 ((str = "63"))).first;
    PropertyType::p64 = *this->repository.insert (new P64 ((str = "64"))).first;
    PropertyType::p65 = *this->repository.insert (new P65 ((str = "65"))).first;
    PropertyType::p66 = *this->repository.insert (new P66 ((str = "66"))).first;
    PropertyType::p67 = *this->repository.insert (new P67 ((str = "67"))).first;
    PropertyType::p68 = *this->repository.insert (new P68 ((str = "68"))).first;
    PropertyType::p69 = *this->repository.insert (new P69 ((str = "69"))).first;
    PropertyType::p70 = *this->repository.insert (new P70 ((str = "70"))).first;
    PropertyType::p71 = *this->repository.insert (new P71 ((str = "71"))).first;
    PropertyType::p72 = *this->repository.insert (new P72 ((str = "72"))).first;
    PropertyType::p73 = *this->repository.insert (new P73 ((str = "73"))).first;
    PropertyType::p74 = *this->repository.insert (new P74 ((str = "74"))).first;
    PropertyType::p75 = *this->repository.insert (new P75 ((str = "75"))).first;
    PropertyType::p76 = *this->repository.insert (new P76 ((str = "76"))).first;
    PropertyType::p77 = *this->repository.insert (new P77 ((str = "77"))).first;
    PropertyType::p78 = *this->repository.insert (new P78 ((str = "78"))).first;
    PropertyType::p79 = *this->repository.insert (new P79 ((str = "79"))).first;
    PropertyType::p80 = *this->repository.insert (new P80 ((str = "80"))).first;
    PropertyType::p81 = *this->repository.insert (new P81 ((str = "81"))).first;
    PropertyType::p82 = *this->repository.insert (new P82 ((str = "82"))).first;
    PropertyType::p83 = *this->repository.insert (new P83 ((str = "83"))).first;
    PropertyType::p84 = *this->repository.insert (new P84 ((str = "84"))).first;
    PropertyType::p85 = *this->repository.insert (new P85 ((str = "85"))).first;
    PropertyType::p86 = *this->repository.insert (new P86 ((str = "86"))).first;
    PropertyType::p87 = *this->repository.insert (new P87 ((str = "87"))).first;
    PropertyType::p88 = *this->repository.insert (new P88 ((str = "88"))).first;
    PropertyType::p89 = *this->repository.insert (new P89 ((str = "89"))).first;
    PropertyType::p90 = *this->repository.insert (new P90 ((str = "90"))).first;
    PropertyType::p91 = *this->repository.insert (new P91 ((str = "91"))).first;
    PropertyType::p92 = *this->repository.insert (new P92 ((str = "92"))).first;
    PropertyType::p93 = *this->repository.insert (new P93 ((str = "93"))).first;
    PropertyType::p94 = *this->repository.insert (new P94 ((str = "94"))).first;
    PropertyType::p95 = *this->repository.insert (new P95 ((str = "95"))).first;
    PropertyType::p96 = *this->repository.insert (new P96 ((str = "96"))).first;
    PropertyType::p97 = *this->repository.insert (new P97 ((str = "97"))).first;
    PropertyType::p98 = *this->repository.insert (new P98 ((str = "98"))).first;
    PropertyType::p99 = *this->repository.insert (new P99 ((str = "99"))).first;
    PropertyType::p100 = *this->repository.insert (new P100 ((str = "100"))).first;
    PropertyType::p101 = *this->repository.insert (new P101 ((str = "101"))).first;
    PropertyType::p102 = *this->repository.insert (new P102 ((str = "102"))).first;
    PropertyType::p103 = *this->repository.insert (new P103 ((str = "103"))).first;
    PropertyType::p104 = *this->repository.insert (new P104 ((str = "104"))).first;
    PropertyType::p105 = *this->repository.insert (new P105 ((str = "105"))).first;
    PropertyType::p106 = *this->repository.insert (new P106 ((str = "106"))).first;
    PropertyType::p108 = *this->repository.insert (new P108 ((str = "108"))).first;
    PropertyType::p109 = *this->repository.insert (new P109 ((str = "109"))).first;
    PropertyType::p110 = *this->repository.insert (new P110 ((str = "110"))).first;
    PropertyType::p111 = *this->repository.insert (new P111 ((str = "111"))).first;
    PropertyType::p112 = *this->repository.insert (new P112 ((str = "112"))).first;
    PropertyType::p113 = *this->repository.insert (new P113 ((str = "113"))).first;
    PropertyType::p114 = *this->repository.insert (new P114 ((str = "114"))).first;
    PropertyType::p115 = *this->repository.insert (new P115 ((str = "115"))).first;
    PropertyType::p116 = *this->repository.insert (new P116 ((str = "116"))).first;
    PropertyType::p117 = *this->repository.insert (new P117 ((str = "117"))).first;
    PropertyType::p118 = *this->repository.insert (new P118 ((str = "118"))).first;
    PropertyType::p119 = *this->repository.insert (new P119 ((str = "119"))).first;
    PropertyType::p120 = *this->repository.insert (new P120 ((str = "120"))).first;
    PropertyType::p121 = *this->repository.insert (new P121 ((str = "121"))).first;
    PropertyType::p122 = *this->repository.insert (new P122 ((str = "122"))).first;
    PropertyType::p123 = *this->repository.insert (new P123 ((str = "123"))).first;
    PropertyType::p124 = *this->repository.insert (new P124 ((str = "124"))).first;
    PropertyType::p125 = *this->repository.insert (new P125 ((str = "125"))).first;
    PropertyType::p126 = *this->repository.insert (new P126 ((str = "126"))).first;
    PropertyType::p127 = *this->repository.insert (new P127 ((str = "127"))).first;
    PropertyType::p128 = *this->repository.insert (new P128 ((str = "128"))).first;
    PropertyType::p129 = *this->repository.insert (new P129 ((str = "129"))).first;
    PropertyType::p130 = *this->repository.insert (new P130 ((str = "130"))).first;
    PropertyType::p131 = *this->repository.insert (new P131 ((str = "131"))).first;
    PropertyType::p132 = *this->repository.insert (new P132 ((str = "132"))).first;
    PropertyType::p133 = *this->repository.insert (new P133 ((str = "133"))).first;
    PropertyType::p134 = *this->repository.insert (new P134 ((str = "134"))).first;
    PropertyType::p135 = *this->repository.insert (new P135 ((str = "135"))).first;
    PropertyType::p136 = *this->repository.insert (new P136 ((str = "136"))).first;
    PropertyType::p137 = *this->repository.insert (new P137 ((str = "137"))).first;
    PropertyType::pW = *this->repository.insert (new PW ((str = "W"))).first;
    PropertyType::pS = *this->repository.insert (new PS ((str = "S"))).first;
    PropertyType::pH = *this->repository.insert (new PH ((str = "H"))).first;
    PropertyType::pWs = *this->repository.insert (new PWs ((str = "Ws"))).first;
    PropertyType::pWw = *this->repository.insert (new PWw ((str = "Ww"))).first;
    PropertyType::pWh = *this->repository.insert (new PWh ((str = "Wh"))).first;
    PropertyType::pSw = *this->repository.insert (new PSw ((str = "Sw"))).first;
    PropertyType::pSs = *this->repository.insert (new PSs ((str = "Ss"))).first;
    PropertyType::pHw = *this->repository.insert (new PHw ((str = "Hw"))).first;
    PropertyType::pHh = *this->repository.insert (new PHh ((str = "Hh"))).first;
    PropertyType::pC8 = *this->repository.insert (new PC8 ((str = "C8"))).first;
    PropertyType::pBs = *this->repository.insert (new PBs ((str = "Bs"))).first;
    PropertyType::pBh = *this->repository.insert (new PBh ((str = "Bh"))).first;
    PropertyType::pPhosphate = *repository.insert (new PPhosphate ((str = "O2P"))).first;
    PropertyType::pRibose = *repository.insert (new PRibose ((str = "O2'"))).first;

    PropertyType::pAlpha_L_Lyxofuranoside = *this->repository.insert (new Alpha_L_Lyxofuranoside ((str = "alpha-L-lyxofuranoside"))).first;
    PropertyType::pBeta_L_Lyxofuranoside = *this->repository.insert (new Beta_L_Lyxofuranoside ((str = "beta-L-lyxofuranoside"))).first;
    PropertyType::pAlpha_D_Lyxofuranoside = *this->repository.insert (new Alpha_D_Lyxofuranoside ((str = "alpha-D-lyxofuranoside"))).first;
    PropertyType::pBeta_D_Lyxofuranoside = *this->repository.insert (new Beta_D_Lyxofuranoside ((str = "beta-D-lyxofuranoside"))).first;
    PropertyType::pAlpha_L_Ribofuranoside = *this->repository.insert (new Alpha_L_Ribofuranoside ((str = "alpha-L-ribofuranoside"))).first;
    PropertyType::pBeta_L_Ribofuranoside = *this->repository.insert (new Beta_L_Ribofuranoside ((str = "beta-L-ribofuranoside"))).first;
    PropertyType::pAlpha_D_Ribofuranoside = *this->repository.insert (new Alpha_D_Ribofuranoside ((str = "alpha-D-ribofuranoside"))).first;
    PropertyType::pBeta_D_Ribofuranoside = *this->repository.insert (new Beta_D_Ribofuranoside ((str = "beta-D-ribofuranoside"))).first;
    PropertyType::pAlpha_L_Arabinofuranoside = *this->repository.insert (new Alpha_L_Arabinofuranoside ((str = "alpha-L-arabinofuranoside"))).first;
    PropertyType::pBeta_L_Arabinofuranoside = *this->repository.insert (new Beta_L_Arabinofuranoside ((str = "beta-L-arabinofuranoside"))).first;
    PropertyType::pAlpha_D_Arabinofuranoside = *this->repository.insert (new Alpha_D_Arabinofuranoside ((str = "alpha-D-arabinofuranoside"))).first;
    PropertyType::pBeta_D_Arabinofuranoside = *this->repository.insert (new Beta_D_Arabinofuranoside ((str = "beta-D-arabinofuranoside"))).first;
    PropertyType::pAlpha_L_Xylofuranoside = *this->repository.insert (new Alpha_L_Xylofuranoside ((str = "alpha-L-xylofuranoside"))).first;
    PropertyType::pBeta_L_Xylofuranoside = *this->repository.insert (new Beta_L_Xylofuranoside ((str = "beta-L-xylofuranoside"))).first;
    PropertyType::pAlpha_D_Xylofuranoside = *this->repository.insert (new Alpha_D_Xylofuranoside ((str = "alpha-D-xylofuranoside"))).first;
    PropertyType::pBeta_D_Xylofuranoside = *this->repository.insert (new Beta_D_Xylofuranoside ((str = "beta-D-xylofuranoside"))).first;

    PropertyType::pTheo = *this->repository.insert (new Theo ((str = "theo"))).first;
  }


  PropertyTypeStore::~PropertyTypeStore () 
  {
    set< PropertyType*, PropertyType::less_deref >::iterator it;
    for (it = this->repository.begin (); it != this->repository.end (); ++it)
      delete *it;
  }  


  const PropertyType* 
  PropertyTypeStore::get (const string& key) 
  {
    string key2 = key;
    string::iterator sit;

    PropertyType* ptype = new Unknown (key2);    
    pair< set< PropertyType*, PropertyType::less_deref >::iterator, bool > inserted =
      this->repository.insert (ptype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete ptype;
      ptype = *inserted.first;
    }

    return ptype;
  }

}
