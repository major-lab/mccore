//                              -*- Mode: C++ -*- 
// PropertyTypeStore.cc
// Copyright � 2003 Laboratoire de Biologie Informatique et Th�orique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:42:25 2003
// $Revision: 1.1 $


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <set>
#include <string>

#include "PropertyTypeStore.h"
#include "PropertyType.h"

namespace mccore {


  // LIFECYCLE -----------------------------------------------------------------

  PropertyTypeStore::PropertyTypeStore () 
  {
    stringType["theo"] = PropertyType::pTheo = new Theo ("theo");
    stringType["pairing"] = PropertyType::pPairing = new Pairing ("pairing");
    stringType["cis"] = PropertyType::pCis = new Cis ("cis");
    stringType["trans"] = PropertyType::pTrans = new Trans ("trans");
    stringType["stack"] = PropertyType::pStack = new Stack ("stack");
    stringType["reverse"] = PropertyType::pReverse = new Reverse ("reverse");
    stringType["adjacent"] = PropertyType::pAdjacent = new Adjacent ("adjacent");
    stringType["type_a"] = PropertyType::pType_A = new Type_A ("type_A");
    stringType["type_b"] = PropertyType::pType_B = new Type_B ("type_B");
    stringType["helix"] = PropertyType::pHelix = new Helix ("helix");
    stringType["c1p_endo"] = PropertyType::pC1p_endo = new C1p_endo ("C1p_endo");
    stringType["c1p_exo"] = PropertyType::pC1p_exo = new C1p_exo ("C1p_exo");
    stringType["c2p_endo"] = PropertyType::pC2p_endo = new C2p_endo ("C2p_endo");
    stringType["c2p_exo"] = PropertyType::pC2p_exo = new C2p_exo ("C2p_exo");
    stringType["c3p_endo"] = PropertyType::pC3p_endo = new C3p_endo ("C3p_endo");
    stringType["c3p_exo"] = PropertyType::pC3p_exo = new C3p_exo ("C3p_exo");
    stringType["c4p_endo"] = PropertyType::pC4p_endo = new C4p_endo ("C4p_endo");
    stringType["c4p_exo"] = PropertyType::pC4p_exo = new C4p_exo ("C4p_exo");
    stringType["o4p_endo"] = PropertyType::pO4p_endo = new O4p_endo ("O4p_endo");
    stringType["o4p_exo"] = PropertyType::pO4p_exo = new O4p_exo ("O4p_exo");
    stringType["anti"] = PropertyType::pAnti = new Anti ("anti");
    stringType["syn"] = PropertyType::pSyn = new Syn ("syn");
    stringType["dir_5p"] = PropertyType::pDIR_5p = new DIR_5p ("DIR_5p");
    stringType["dir_3p"] = PropertyType::pDIR_3p = new DIR_3p ("DIR_3p");
    stringType["dir_any"] = PropertyType::pDIR_ANY = new DIR_ANY ("DIR_ANY");
    // 	stringType.put ("dir_sh", pDIR_SH = new PropertyType.DIR_SH ("DIR_SH"));
    // 	stringType.put ("dir_hs", pDIR_HS = new PropertyType.DIR_HS ("DIR_HS"));
    stringType["saenger"] = PropertyType::pSaenger = new Saenger ("saenger");
    stringType["wc"] = PropertyType::pWC = new WC ("wc");
    stringType["wobble"] = PropertyType::pWobble = new Wobble ("wobble");
    stringType["i"] = PropertyType::pI = new PI ("I");
    stringType["ii"] = PropertyType::pII = new PII ("II");
    stringType["iii"] = PropertyType::pIII = new PIII ("III");
    stringType["iv"] = PropertyType::pIV = new PIV ("IV");
    stringType["v"] = PropertyType::pV = new PV ("V");
    stringType["vi"] = PropertyType::pVI = new PVI ("VI");
    stringType["vii"] = PropertyType::pVII = new PVII ("VII");
    stringType["viii"] = PropertyType::pVIII = new PVIII ("VIII");
    stringType["ix"] = PropertyType::pIX = new PIX ("IX");
    stringType["x"] = PropertyType::pX = new PX ("X");
    stringType["xi"] = PropertyType::pXI = new PXI ("XI");
    stringType["xii"] = PropertyType::pXII = new PXII ("XII");
    stringType["xiii"] = PropertyType::pXIII = new PXIII ("XIII");
    stringType["xiv"] = PropertyType::pXIV = new PXIV ("XIV");
    stringType["xv"] = PropertyType::pXV = new PXV ("XV");
    stringType["xvi"] = PropertyType::pXVI = new PXVI ("XVI");
    stringType["xvii"] = PropertyType::pXVII = new PXVII ("XVII");
    stringType["xviii"] = PropertyType::pXVIII = new PXVIII ("XVIII");
    stringType["xix"] = PropertyType::pXIX = new PXIX ("XIX");
    stringType["xx"] = PropertyType::pXX = new PXX ("XX");
    stringType["xxi"] = PropertyType::pXXI = new PXXI ("XXI");
    stringType["xxii"] = PropertyType::pXXII = new PXXII ("XXII");
    stringType["xxiii"] = PropertyType::pXXIII = new PXXIII ("XXIII");
    stringType["xxiv"] = PropertyType::pXXIV = new PXXIV ("XXIV");
    stringType["xxv"] = PropertyType::pXXV = new PXXV ("XXV");
    stringType["xxvi"] = PropertyType::pXXVI = new PXXVI ("XXVI");
    stringType["xxvii"] = PropertyType::pXXVII = new PXXVII ("XXVII");
    stringType["xxviii"] = PropertyType::pXXVIII = new PXXVIII ("XXVIII");
    stringType["one_hbond"] = PropertyType::pOneHbond = new OneHbond ("one_hbond");
    stringType["29"] = PropertyType::p29 = new P29 ("29");
    stringType["30"] = PropertyType::p30 = new P30 ("30");
    stringType["31"] = PropertyType::p31 = new P31 ("31");
    stringType["32"] = PropertyType::p32 = new P32 ("32");
    stringType["33"] = PropertyType::p33 = new P33 ("33");
    stringType["34"] = PropertyType::p34 = new P34 ("34");
    stringType["35"] = PropertyType::p35 = new P35 ("35");
    stringType["36"] = PropertyType::p36 = new P36 ("36");
    stringType["37"] = PropertyType::p37 = new P37 ("37");
    stringType["38"] = PropertyType::p38 = new P38 ("38");
    stringType["39"] = PropertyType::p39 = new P39 ("39");
    stringType["40"] = PropertyType::p40 = new P40 ("40");
    stringType["41"] = PropertyType::p41 = new P41 ("41");
    stringType["42"] = PropertyType::p42 = new P42 ("42");
    stringType["43"] = PropertyType::p43 = new P43 ("43");
    stringType["44"] = PropertyType::p44 = new P44 ("44");
    stringType["45"] = PropertyType::p45 = new P45 ("45");
    stringType["46"] = PropertyType::p46 = new P46 ("46");
    stringType["47"] = PropertyType::p47 = new P47 ("47");
    stringType["48"] = PropertyType::p48 = new P48 ("48");
    stringType["49"] = PropertyType::p49 = new P49 ("49");
    stringType["50"] = PropertyType::p50 = new P50 ("50");
    stringType["51"] = PropertyType::p51 = new P51 ("51");
    stringType["52"] = PropertyType::p52 = new P52 ("52");
    stringType["53"] = PropertyType::p53 = new P53 ("53");
    stringType["54"] = PropertyType::p54 = new P54 ("54");
    stringType["55"] = PropertyType::p55 = new P55 ("55");
    stringType["56"] = PropertyType::p56 = new P56 ("56");
    stringType["57"] = PropertyType::p57 = new P57 ("57");
    stringType["58"] = PropertyType::p58 = new P58 ("58");
    stringType["59"] = PropertyType::p59 = new P59 ("59");
    stringType["60"] = PropertyType::p60 = new P60 ("60");
    stringType["61"] = PropertyType::p61 = new P61 ("61");
    stringType["62"] = PropertyType::p62 = new P62 ("62");
    stringType["63"] = PropertyType::p63 = new P63 ("63");
    stringType["64"] = PropertyType::p64 = new P64 ("64");
    stringType["65"] = PropertyType::p65 = new P65 ("65");
    stringType["66"] = PropertyType::p66 = new P66 ("66");
    stringType["67"] = PropertyType::p67 = new P67 ("67");
    stringType["68"] = PropertyType::p68 = new P68 ("68");
    stringType["69"] = PropertyType::p69 = new P69 ("69");
    stringType["70"] = PropertyType::p70 = new P70 ("70");
    stringType["71"] = PropertyType::p71 = new P71 ("71");
    stringType["72"] = PropertyType::p72 = new P72 ("72");
    stringType["73"] = PropertyType::p73 = new P73 ("73");
    stringType["74"] = PropertyType::p74 = new P74 ("74");
    stringType["75"] = PropertyType::p75 = new P75 ("75");
    stringType["76"] = PropertyType::p76 = new P76 ("76");
    stringType["77"] = PropertyType::p77 = new P77 ("77");
    stringType["78"] = PropertyType::p78 = new P78 ("78");
    stringType["79"] = PropertyType::p79 = new P79 ("79");
    stringType["80"] = PropertyType::p80 = new P80 ("80");
    stringType["81"] = PropertyType::p81 = new P81 ("81");
    stringType["82"] = PropertyType::p82 = new P82 ("82");
    stringType["83"] = PropertyType::p83 = new P83 ("83");
    stringType["84"] = PropertyType::p84 = new P84 ("84");
    stringType["85"] = PropertyType::p85 = new P85 ("85");
    stringType["86"] = PropertyType::p86 = new P86 ("86");
    stringType["87"] = PropertyType::p87 = new P87 ("87");
    stringType["88"] = PropertyType::p88 = new P88 ("88");
    stringType["89"] = PropertyType::p89 = new P89 ("89");
    stringType["90"] = PropertyType::p90 = new P90 ("90");
    stringType["91"] = PropertyType::p91 = new P91 ("91");
    stringType["92"] = PropertyType::p92 = new P92 ("92");
    stringType["93"] = PropertyType::p93 = new P93 ("93");
    stringType["94"] = PropertyType::p94 = new P94 ("94");
    stringType["95"] = PropertyType::p95 = new P95 ("95");
    stringType["96"] = PropertyType::p96 = new P96 ("96");
    stringType["97"] = PropertyType::p97 = new P97 ("97");
    stringType["98"] = PropertyType::p98 = new P98 ("98");
    stringType["99"] = PropertyType::p99 = new P99 ("99");
    stringType["100"] = PropertyType::p100 = new P100 ("100");
    stringType["101"] = PropertyType::p101 = new P101 ("101");
    stringType["102"] = PropertyType::p102 = new P102 ("102");
    stringType["103"] = PropertyType::p103 = new P103 ("103");
    stringType["104"] = PropertyType::p104 = new P104 ("104");
    stringType["105"] = PropertyType::p105 = new P105 ("105");
    stringType["106"] = PropertyType::p106 = new P106 ("106");
    stringType["108"] = PropertyType::p108 = new P108 ("108");
    stringType["109"] = PropertyType::p109 = new P109 ("109");
    stringType["110"] = PropertyType::p110 = new P110 ("110");
    stringType["111"] = PropertyType::p111 = new P111 ("111");
    stringType["112"] = PropertyType::p112 = new P112 ("112");
    stringType["113"] = PropertyType::p113 = new P113 ("113");
    stringType["114"] = PropertyType::p114 = new P114 ("114");
    stringType["115"] = PropertyType::p115 = new P115 ("115");
    stringType["116"] = PropertyType::p116 = new P116 ("116");
    stringType["117"] = PropertyType::p117 = new P117 ("117");
    stringType["118"] = PropertyType::p118 = new P118 ("118");
    stringType["119"] = PropertyType::p119 = new P119 ("119");
    stringType["120"] = PropertyType::p120 = new P120 ("120");
    stringType["121"] = PropertyType::p121 = new P121 ("121");
    stringType["122"] = PropertyType::p122 = new P122 ("122");
    stringType["123"] = PropertyType::p123 = new P123 ("123");
    stringType["124"] = PropertyType::p124 = new P124 ("124");
    stringType["125"] = PropertyType::p125 = new P125 ("125");
    stringType["126"] = PropertyType::p126 = new P126 ("126");
    stringType["127"] = PropertyType::p127 = new P127 ("127");
    stringType["128"] = PropertyType::p128 = new P128 ("128");
    stringType["129"] = PropertyType::p129 = new P129 ("129");
    stringType["130"] = PropertyType::p130 = new P130 ("130");
    stringType["131"] = PropertyType::p131 = new P131 ("131");
    stringType["132"] = PropertyType::p132 = new P132 ("132");
    stringType["133"] = PropertyType::p133 = new P133 ("133");
    stringType["134"] = PropertyType::p134 = new P134 ("134");
    stringType["135"] = PropertyType::p135 = new P135 ("135");
    stringType["136"] = PropertyType::p136 = new P136 ("136");
    stringType["137"] = PropertyType::p137 = new P137 ("137");
    // 	stringType.put ("wct", pwct = new PropertyType.wct ("wct"));
    //     public static PropertyType pconnect;
    //     public static PropertyType pwobblet;
    //     public static PropertyType pnon_adjacent;
    //     public static PropertyType pstrong;
    //     public static PropertyType pweak;
    //     public static PropertyType pnostack;
    stringType["w"] = PropertyType::pW = new PW ("W");
    stringType["s"] = PropertyType::pS = new PS ("S");
    stringType["h"] = PropertyType::pH = new PH ("H");
    stringType["b"] = PropertyType::pB = new PB ("B");
    stringType["ws"] = PropertyType::pWs = new PWs ("Ws");
    stringType["ww"] = PropertyType::pWw = new PWw ("Ww");
    stringType["wh"] = PropertyType::pWh = new PWh ("Wh");
    stringType["sw"] = PropertyType::pSw = new PSw ("Sw");
    stringType["ss"] = PropertyType::pSs = new PSs ("Ss");
    stringType["hw"] = PropertyType::pHw = new PHw ("Hw");
    stringType["hh"] = PropertyType::pHh = new PHh ("Hh");
    stringType["c8"] = PropertyType::pC8 = new PC8 ("C8");
    stringType["bs"] = PropertyType::pBs = new PBs ("Bs");
    stringType["bh"] = PropertyType::pBh = new PBh ("Bh");    
  }

  PropertyTypeStore::~PropertyTypeStore () 
  {
    set< PropertyType* > bag;
    map< const char*, PropertyType*, less_string >::iterator i;
    for (i=stringType.begin (); i!=stringType.end (); ++i) {
      bag.insert (i->second);
    }
    set< PropertyType* >::iterator j;
    for (j=bag.begin (); j!=bag.end (); ++j) {
      delete *j;
    }
  }  


  // METHODS -------------------------------------------------------------------

  PropertyType* 
  PropertyTypeStore::get (const char* s) 
  {
    PropertyType* t = 0;
    char* str = new char[strlen (s) + 1];
    strcpy (str, s);

    for (char* i=str; *i; ++i) {
      if (*i == '\'') *i = '*';
      *i = tolower (*i);
    }
    
    if (stringType.find (str) != stringType.end ()) {
      t = stringType[str];
    } else {
      t = new PropertyType (str);
      stringType[*t] = t;
    }
    delete[] str;
    return t;
  }
}