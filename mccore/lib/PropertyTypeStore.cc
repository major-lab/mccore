//                              -*- Mode: C++ -*- 
// PropertyTypeStore.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:42:25 2003
// $Revision: 1.12 $
// $Id: PropertyTypeStore.cc,v 1.12 2005-01-07 17:09:59 thibaup Exp $
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
    PropertyType::pNull = *this->repository.insert (new Null (string (""))).first;
    PropertyType::pUnknown = *this->repository.insert (new Unknown (string ("unknown"))).first;

    PropertyType::pStack = *this->repository.insert (new Stack (string ("stack"))).first;
    PropertyType::pStraightUpward = *this->repository.insert (new StraightUpward (string ("straight_upward"))).first;
    PropertyType::pStraightDownward = *this->repository.insert (new StraightDownward (string ("straight_downward"))).first;
    PropertyType::pReverseUpward = *this->repository.insert (new ReverseUpward (string ("reverse_upward"))).first;
    PropertyType::pReverseDownward = *this->repository.insert (new ReverseDownward (string ("reverse_downward"))).first;
    
    PropertyType::pAdjacent = *this->repository.insert (new Adjacent (string ("adjacent"))).first;
    PropertyType::pAdjacent5p = *this->repository.insert (new Adjacent5p (string ("adjacent_5p"))).first;
    PropertyType::pAdjacent3p = *this->repository.insert (new Adjacent3p (string ("adjacent_3p"))).first;
    
    PropertyType::pTheo = *this->repository.insert (new Theo (string ("theo"))).first;
    PropertyType::pPairing = *this->repository.insert (new Pairing (string ("pairing"))).first;
    PropertyType::pCis = *this->repository.insert (new Cis (string ("cis"))).first;
    PropertyType::pTrans = *this->repository.insert (new Trans (string ("trans"))).first;
    PropertyType::pStraight = *this->repository.insert (new Straight (string ("straight"))).first;
    PropertyType::pReverse = *this->repository.insert (new Reverse (string ("reverse"))).first;

    PropertyType::pType_A = *this->repository.insert (new Type_A (string ("type_A"))).first;
    PropertyType::pType_B = *this->repository.insert (new Type_B (string ("type_B"))).first;
    PropertyType::pHelix = *this->repository.insert (new Helix (string ("helix"))).first;
    PropertyType::pC1p_endo = *this->repository.insert (new C1p_endo (string ("C1p_endo"))).first;
    PropertyType::pC1p_exo = *this->repository.insert (new C1p_exo (string ("C1p_exo"))).first;
    PropertyType::pC2p_endo = *this->repository.insert (new C2p_endo (string ("C2p_endo"))).first;
    PropertyType::pC2p_exo = *this->repository.insert (new C2p_exo (string ("C2p_exo"))).first;
    PropertyType::pC3p_endo = *this->repository.insert (new C3p_endo (string ("C3p_endo"))).first;
    PropertyType::pC3p_exo = *this->repository.insert (new C3p_exo (string ("C3p_exo"))).first;
    PropertyType::pC4p_endo = *this->repository.insert (new C4p_endo (string ("C4p_endo"))).first;
    PropertyType::pC4p_exo = *this->repository.insert (new C4p_exo (string ("C4p_exo"))).first;
    PropertyType::pO4p_endo = *this->repository.insert (new O4p_endo (string ("O4p_endo"))).first;
    PropertyType::pO4p_exo = *this->repository.insert (new O4p_exo (string ("O4p_exo"))).first;
    PropertyType::pAnti = *this->repository.insert (new Anti (string ("anti"))).first;
    PropertyType::pSyn = *this->repository.insert (new Syn (string ("syn"))).first;
    PropertyType::pSaenger = *this->repository.insert (new Saenger (string ("saenger"))).first;
    PropertyType::pWC = *this->repository.insert (new WC (string ("wc"))).first;
    PropertyType::pWobble = *this->repository.insert (new Wobble (string ("wobble"))).first;
    PropertyType::pI = *this->repository.insert (new PI (string ("I"))).first;
    PropertyType::pII = *this->repository.insert (new PII (string ("II"))).first;
    PropertyType::pIII = *this->repository.insert (new PIII (string ("III"))).first;
    PropertyType::pIV = *this->repository.insert (new PIV (string ("IV"))).first;
    PropertyType::pV = *this->repository.insert (new PV (string ("V"))).first;
    PropertyType::pVI = *this->repository.insert (new PVI (string ("VI"))).first;
    PropertyType::pVII = *this->repository.insert (new PVII (string ("VII"))).first;
    PropertyType::pVIII = *this->repository.insert (new PVIII (string ("VIII"))).first;
    PropertyType::pIX = *this->repository.insert (new PIX (string ("IX"))).first;
    PropertyType::pX = *this->repository.insert (new PX (string ("X"))).first;
    PropertyType::pXI = *this->repository.insert (new PXI (string ("XI"))).first;
    PropertyType::pXII = *this->repository.insert (new PXII (string ("XII"))).first;
    PropertyType::pXIII = *this->repository.insert (new PXIII (string ("XIII"))).first;
    PropertyType::pXIV = *this->repository.insert (new PXIV (string ("XIV"))).first;
    PropertyType::pXV = *this->repository.insert (new PXV (string ("XV"))).first;
    PropertyType::pXVI = *this->repository.insert (new PXVI (string ("XVI"))).first;
    PropertyType::pXVII = *this->repository.insert (new PXVII (string ("XVII"))).first;
    PropertyType::pXVIII = *this->repository.insert (new PXVIII (string ("XVIII"))).first;
    PropertyType::pXIX = *this->repository.insert (new PXIX (string ("XIX"))).first;
    PropertyType::pXX = *this->repository.insert (new PXX (string ("XX"))).first;
    PropertyType::pXXI = *this->repository.insert (new PXXI (string ("XXI"))).first;
    PropertyType::pXXII = *this->repository.insert (new PXXII (string ("XXII"))).first;
    PropertyType::pXXIII = *this->repository.insert (new PXXIII (string ("XXIII"))).first;
    PropertyType::pXXIV = *this->repository.insert (new PXXIV (string ("XXIV"))).first;
    PropertyType::pXXV = *this->repository.insert (new PXXV (string ("XXV"))).first;
    PropertyType::pXXVI = *this->repository.insert (new PXXVI (string ("XXVI"))).first;
    PropertyType::pXXVII = *this->repository.insert (new PXXVII (string ("XXVII"))).first;
    PropertyType::pXXVIII = *this->repository.insert (new PXXVIII (string ("XXVIII"))).first;
    PropertyType::pOneHbond = *this->repository.insert (new OneHbond (string ("one_hbond"))).first;
    PropertyType::p29 = *this->repository.insert (new P29 (string ("29"))).first;
    PropertyType::p30 = *this->repository.insert (new P30 (string ("30"))).first;
    PropertyType::p31 = *this->repository.insert (new P31 (string ("31"))).first;
    PropertyType::p32 = *this->repository.insert (new P32 (string ("32"))).first;
    PropertyType::p33 = *this->repository.insert (new P33 (string ("33"))).first;
    PropertyType::p34 = *this->repository.insert (new P34 (string ("34"))).first;
    PropertyType::p35 = *this->repository.insert (new P35 (string ("35"))).first;
    PropertyType::p36 = *this->repository.insert (new P36 (string ("36"))).first;
    PropertyType::p37 = *this->repository.insert (new P37 (string ("37"))).first;
    PropertyType::p38 = *this->repository.insert (new P38 (string ("38"))).first;
    PropertyType::p39 = *this->repository.insert (new P39 (string ("39"))).first;
    PropertyType::p40 = *this->repository.insert (new P40 (string ("40"))).first;
    PropertyType::p41 = *this->repository.insert (new P41 (string ("41"))).first;
    PropertyType::p42 = *this->repository.insert (new P42 (string ("42"))).first;
    PropertyType::p43 = *this->repository.insert (new P43 (string ("43"))).first;
    PropertyType::p44 = *this->repository.insert (new P44 (string ("44"))).first;
    PropertyType::p45 = *this->repository.insert (new P45 (string ("45"))).first;
    PropertyType::p46 = *this->repository.insert (new P46 (string ("46"))).first;
    PropertyType::p47 = *this->repository.insert (new P47 (string ("47"))).first;
    PropertyType::p48 = *this->repository.insert (new P48 (string ("48"))).first;
    PropertyType::p49 = *this->repository.insert (new P49 (string ("49"))).first;
    PropertyType::p50 = *this->repository.insert (new P50 (string ("50"))).first;
    PropertyType::p51 = *this->repository.insert (new P51 (string ("51"))).first;
    PropertyType::p52 = *this->repository.insert (new P52 (string ("52"))).first;
    PropertyType::p53 = *this->repository.insert (new P53 (string ("53"))).first;
    PropertyType::p54 = *this->repository.insert (new P54 (string ("54"))).first;
    PropertyType::p55 = *this->repository.insert (new P55 (string ("55"))).first;
    PropertyType::p56 = *this->repository.insert (new P56 (string ("56"))).first;
    PropertyType::p57 = *this->repository.insert (new P57 (string ("57"))).first;
    PropertyType::p58 = *this->repository.insert (new P58 (string ("58"))).first;
    PropertyType::p59 = *this->repository.insert (new P59 (string ("59"))).first;
    PropertyType::p60 = *this->repository.insert (new P60 (string ("60"))).first;
    PropertyType::p61 = *this->repository.insert (new P61 (string ("61"))).first;
    PropertyType::p62 = *this->repository.insert (new P62 (string ("62"))).first;
    PropertyType::p63 = *this->repository.insert (new P63 (string ("63"))).first;
    PropertyType::p64 = *this->repository.insert (new P64 (string ("64"))).first;
    PropertyType::p65 = *this->repository.insert (new P65 (string ("65"))).first;
    PropertyType::p66 = *this->repository.insert (new P66 (string ("66"))).first;
    PropertyType::p67 = *this->repository.insert (new P67 (string ("67"))).first;
    PropertyType::p68 = *this->repository.insert (new P68 (string ("68"))).first;
    PropertyType::p69 = *this->repository.insert (new P69 (string ("69"))).first;
    PropertyType::p70 = *this->repository.insert (new P70 (string ("70"))).first;
    PropertyType::p71 = *this->repository.insert (new P71 (string ("71"))).first;
    PropertyType::p72 = *this->repository.insert (new P72 (string ("72"))).first;
    PropertyType::p73 = *this->repository.insert (new P73 (string ("73"))).first;
    PropertyType::p74 = *this->repository.insert (new P74 (string ("74"))).first;
    PropertyType::p75 = *this->repository.insert (new P75 (string ("75"))).first;
    PropertyType::p76 = *this->repository.insert (new P76 (string ("76"))).first;
    PropertyType::p77 = *this->repository.insert (new P77 (string ("77"))).first;
    PropertyType::p78 = *this->repository.insert (new P78 (string ("78"))).first;
    PropertyType::p79 = *this->repository.insert (new P79 (string ("79"))).first;
    PropertyType::p80 = *this->repository.insert (new P80 (string ("80"))).first;
    PropertyType::p81 = *this->repository.insert (new P81 (string ("81"))).first;
    PropertyType::p82 = *this->repository.insert (new P82 (string ("82"))).first;
    PropertyType::p83 = *this->repository.insert (new P83 (string ("83"))).first;
    PropertyType::p84 = *this->repository.insert (new P84 (string ("84"))).first;
    PropertyType::p85 = *this->repository.insert (new P85 (string ("85"))).first;
    PropertyType::p86 = *this->repository.insert (new P86 (string ("86"))).first;
    PropertyType::p87 = *this->repository.insert (new P87 (string ("87"))).first;
    PropertyType::p88 = *this->repository.insert (new P88 (string ("88"))).first;
    PropertyType::p89 = *this->repository.insert (new P89 (string ("89"))).first;
    PropertyType::p90 = *this->repository.insert (new P90 (string ("90"))).first;
    PropertyType::p91 = *this->repository.insert (new P91 (string ("91"))).first;
    PropertyType::p92 = *this->repository.insert (new P92 (string ("92"))).first;
    PropertyType::p93 = *this->repository.insert (new P93 (string ("93"))).first;
    PropertyType::p94 = *this->repository.insert (new P94 (string ("94"))).first;
    PropertyType::p95 = *this->repository.insert (new P95 (string ("95"))).first;
    PropertyType::p96 = *this->repository.insert (new P96 (string ("96"))).first;
    PropertyType::p97 = *this->repository.insert (new P97 (string ("97"))).first;
    PropertyType::p98 = *this->repository.insert (new P98 (string ("98"))).first;
    PropertyType::p99 = *this->repository.insert (new P99 (string ("99"))).first;
    PropertyType::p100 = *this->repository.insert (new P100 (string ("100"))).first;
    PropertyType::p101 = *this->repository.insert (new P101 (string ("101"))).first;
    PropertyType::p102 = *this->repository.insert (new P102 (string ("102"))).first;
    PropertyType::p103 = *this->repository.insert (new P103 (string ("103"))).first;
    PropertyType::p104 = *this->repository.insert (new P104 (string ("104"))).first;
    PropertyType::p105 = *this->repository.insert (new P105 (string ("105"))).first;
    PropertyType::p106 = *this->repository.insert (new P106 (string ("106"))).first;
    PropertyType::p108 = *this->repository.insert (new P108 (string ("108"))).first;
    PropertyType::p109 = *this->repository.insert (new P109 (string ("109"))).first;
    PropertyType::p110 = *this->repository.insert (new P110 (string ("110"))).first;
    PropertyType::p111 = *this->repository.insert (new P111 (string ("111"))).first;
    PropertyType::p112 = *this->repository.insert (new P112 (string ("112"))).first;
    PropertyType::p113 = *this->repository.insert (new P113 (string ("113"))).first;
    PropertyType::p114 = *this->repository.insert (new P114 (string ("114"))).first;
    PropertyType::p115 = *this->repository.insert (new P115 (string ("115"))).first;
    PropertyType::p116 = *this->repository.insert (new P116 (string ("116"))).first;
    PropertyType::p117 = *this->repository.insert (new P117 (string ("117"))).first;
    PropertyType::p118 = *this->repository.insert (new P118 (string ("118"))).first;
    PropertyType::p119 = *this->repository.insert (new P119 (string ("119"))).first;
    PropertyType::p120 = *this->repository.insert (new P120 (string ("120"))).first;
    PropertyType::p121 = *this->repository.insert (new P121 (string ("121"))).first;
    PropertyType::p122 = *this->repository.insert (new P122 (string ("122"))).first;
    PropertyType::p123 = *this->repository.insert (new P123 (string ("123"))).first;
    PropertyType::p124 = *this->repository.insert (new P124 (string ("124"))).first;
    PropertyType::p125 = *this->repository.insert (new P125 (string ("125"))).first;
    PropertyType::p126 = *this->repository.insert (new P126 (string ("126"))).first;
    PropertyType::p127 = *this->repository.insert (new P127 (string ("127"))).first;
    PropertyType::p128 = *this->repository.insert (new P128 (string ("128"))).first;
    PropertyType::p129 = *this->repository.insert (new P129 (string ("129"))).first;
    PropertyType::p130 = *this->repository.insert (new P130 (string ("130"))).first;
    PropertyType::p131 = *this->repository.insert (new P131 (string ("131"))).first;
    PropertyType::p132 = *this->repository.insert (new P132 (string ("132"))).first;
    PropertyType::p133 = *this->repository.insert (new P133 (string ("133"))).first;
    PropertyType::p134 = *this->repository.insert (new P134 (string ("134"))).first;
    PropertyType::p135 = *this->repository.insert (new P135 (string ("135"))).first;
    PropertyType::p136 = *this->repository.insert (new P136 (string ("136"))).first;
    PropertyType::p137 = *this->repository.insert (new P137 (string ("137"))).first;
    PropertyType::pW = *this->repository.insert (new PW (string ("W"))).first;
    PropertyType::pS = *this->repository.insert (new PS (string ("S"))).first;
    PropertyType::pH = *this->repository.insert (new PH (string ("H"))).first;
    PropertyType::pWs = *this->repository.insert (new PWs (string ("Ws"))).first;
    PropertyType::pWw = *this->repository.insert (new PWw (string ("Ww"))).first;
    PropertyType::pWh = *this->repository.insert (new PWh (string ("Wh"))).first;
    PropertyType::pSw = *this->repository.insert (new PSw (string ("Sw"))).first;
    PropertyType::pSs = *this->repository.insert (new PSs (string ("Ss"))).first;
    PropertyType::pHw = *this->repository.insert (new PHw (string ("Hw"))).first;
    PropertyType::pHh = *this->repository.insert (new PHh (string ("Hh"))).first;
    PropertyType::pC8 = *this->repository.insert (new PC8 (string ("C8"))).first;
    PropertyType::pBs = *this->repository.insert (new PBs (string ("Bs"))).first;
    PropertyType::pBh = *this->repository.insert (new PBh (string ("Bh"))).first;
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
