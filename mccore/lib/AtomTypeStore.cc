//                              -*- Mode: C++ -*- 
// AtomTypeStore.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 13:56:50 2003
// $Revision: 1.1 $

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "AtomTypeStore.h"

namespace mccore {

  // LIFECYCLE -----------------------------------------------------------------

  AtomTypeStore::AtomTypeStore () 
  {
    AtomType *t;

    stringType["C1*"] = AtomType::aC1p = new AC1p ("C1*");   
    stringType["C2*"] = AtomType::aC2p = new AC2p ("C2*");
    stringType["C3*"] = AtomType::aC3p = new AC3p ("C3*");
    stringType["C4*"] = AtomType::aC4p = new AC4p ("C4*");
    stringType["C5*"] = AtomType::aC5p = new AC5p ("C5*");
    stringType["H1*"] = AtomType::aH1p = new AH1p ("H1*");
    stringType["H2*"] = AtomType::aH2p = new AH2p ("H2*");
    stringType["H3*"] = AtomType::aH3p = new AH3p ("H3*");
    stringType["H4*"] = AtomType::aH4p = new AH4p ("H4*");
    stringType["H5*"] = AtomType::aH5p = new AH5p ("H5*");
    stringType["1H2*"] = t = AtomType::a1H2p = new A1H2p ("1H2*"); stringType["H2*1"] = t; 
    stringType["1H5*"] = t = AtomType::a1H5p = new A1H5p ("1H5*"); stringType["H5*1"] = t; 
    stringType["2H2*"] = AtomType::a2H2p = new A2H2p ("2H2*");
    stringType["2H5*"] = t = AtomType::a2H5p = new A2H5p ("2H5*"); stringType["H5**"] = t;  stringType["H5*2"] = t;  
    stringType["HO2*"] = t = AtomType::aHO2p = new AHO2p ("HO2*"); stringType["H2**"] = t;  stringType["HO*2"] = t;  stringType["2HO*"] = t;
    stringType["HO3*"] = t = AtomType::aHO3p = new AHO3p ("HO3*"); stringType["HO*3"] = t; 
    stringType["O1P"] = AtomType::aO1P = new AO1P ("O1P");
    stringType["O2*"] = AtomType::aO2p = new AO2p ("O2*");
    stringType["O2P"] = AtomType::aO2P = new AO2P ("O2P");
    stringType["O3*"] = t = AtomType::aO3p = new AO3p ("O3*"); stringType["O3T"] = t; 
    stringType["O3P"] = AtomType::aO3P = new AO3P ("O3P");
    stringType["O4*"] = AtomType::aO4p = new AO4p ("O4*");
    stringType["O5*"] = t = AtomType::aO5p = new AO5p ("O5*"); stringType["O5T"] = t; 
    stringType["P"] = AtomType::aP = new AP ("P");
    stringType["C2"] = AtomType::aC2 = new AC2 ("C2");
    stringType["C4"] = AtomType::aC4 = new AC4 ("C4");
    stringType["C5"] = AtomType::aC5 = new AC5 ("C5");
    stringType["C5M"] = t = AtomType::aC5M = new AC5M ("C5M"); stringType["C7"] = t; stringType["C5A"] = t; 
    stringType["C6"] = AtomType::aC6 = new AC6 ("C6");
    stringType["C8"] = AtomType::aC8 = new AC8 ("C8");
    stringType["H1"] = AtomType::aH1 = new AH1 ("H1");
    stringType["H2"] = AtomType::aH2 = new AH2 ("H2");
    stringType["H3"] = AtomType::aH3 = new AH3 ("H3");
    stringType["H5"] = AtomType::aH5 = new AH5 ("H5");
    stringType["H6"] = AtomType::aH6 = new AH6 ("H6");
    stringType["H7"] = AtomType::aH7 = new AH7 ("H7");
    stringType["H8"] = AtomType::aH8 = new AH8 ("H8");
    stringType["1H2"] = t = AtomType::a1H2 = new A1H2 ("1H2"); stringType["H21"] = t; 
    stringType["1H4"] = t = AtomType::a1H4 = new A1H4 ("1H4"); stringType["H41"] = t; 
    stringType["1H5M"] = t = AtomType::a1H5M = new A1H5M ("1H5M"); stringType["H71"] = t; stringType["1H5A"] = t; 
    stringType["1H6"] = t = AtomType::a1H6 = new A1H6 ("1H6"); stringType["H61"] = t; 
    stringType["2H2"] = t = AtomType::a2H2 = new A2H2 ("2H2"); stringType["H22"] = t; 
    stringType["2H4"] = t = AtomType::a2H4 = new A2H4 ("2H4"); stringType["H42"] = t; 
    stringType["2H5M"] = t = AtomType::a2H5M = new A2H5M ("2H5M"); stringType["H72"] = t; stringType["2H5A"] = t; 
    stringType["2H6"] = t = AtomType::a2H6 = new A2H6 ("2H6"); stringType["H62"] = t; 
    stringType["3H5M"] = t = AtomType::a3H5M = new A3H5M ("3H5M"); stringType["H73"] = t; stringType["3H5A"] = t; 
    stringType["N1"] = AtomType::aN1 = new AN1 ("N1");
    stringType["N2"] = AtomType::aN2 = new AN2 ("N2");
    stringType["N3"] = AtomType::aN3 = new AN3 ("N3");
    stringType["N4"] = AtomType::aN4 = new AN4 ("N4");
    stringType["N6"] = AtomType::aN6 = new AN6 ("N6");
    stringType["N7"] = AtomType::aN7 = new AN7 ("N7");
    stringType["N9"] = AtomType::aN9 = new AN9 ("N9");
    stringType["O2"] = AtomType::aO2 = new AO2 ("O2");
    stringType["O4"] = AtomType::aO4 = new AO4 ("O4");
    stringType["O6"] = AtomType::aO6 = new AO6 ("O6");
    stringType["2LP6"] = AtomType::a2LP6 = new A2LP6 ("2LP6");
    stringType["1LP6"] = AtomType::a1LP6 = new A1LP6 ("1LP6");
    stringType["LP7"] = AtomType::aLP7 = new ALP7 ("LP7");
    stringType["LP3"] = AtomType::aLP3 = new ALP3 ("LP3");
    stringType["LP1"] = AtomType::aLP1 = new ALP1 ("LP1");
    stringType["2LP2"] = AtomType::a2LP2 = new A2LP2 ("2LP2");
    stringType["1LP2"] = AtomType::a1LP2 = new A1LP2 ("1LP2");
    stringType["2LP4"] = AtomType::a2LP4 = new A2LP4 ("2LP4");
    stringType["1LP4"] = AtomType::a1LP4 = new A1LP4 ("1LP4");
    stringType["PSY"] = AtomType::aPSY = new APSY ("PSY");
    stringType["PSZ"] = AtomType::aPSZ = new APSZ ("PSZ");
    stringType["H3T"] = AtomType::aH3T = new AH3T ("H3T");
    stringType["H5T"] = AtomType::aH5T = new AH5T ("H5T");
    stringType["C"] = AtomType::aC = new AC ("C");
    stringType["CA"] = AtomType::aCA = new ACA ("CA");
    stringType["CB"] = AtomType::aCB = new ACB ("CB");
    stringType["CD"] = AtomType::aCD = new ACD ("CD");
    stringType["CD1"] = AtomType::aCD1 = new ACD1 ("CD1");
    stringType["CD2"] = AtomType::aCD2 = new ACD2 ("CD2");
    stringType["CE"] = AtomType::aCE = new ACE ("CE");
    stringType["CE1"] = AtomType::aCE1 = new ACE1 ("CE1");
    stringType["CE2"] = AtomType::aCE2 = new ACE2 ("CE2");
    stringType["CE3"] = AtomType::aCE3 = new ACE3 ("CE3");
    stringType["CG"] = AtomType::aCG = new ACG ("CG");
    stringType["CG1"] = AtomType::aCG1 = new ACG1 ("CG1");
    stringType["CG2"] = AtomType::aCG2 = new ACG2 ("CG2");
    stringType["CH2"] = AtomType::aCH2 = new ACH2 ("CH2");
    stringType["CZ"] = AtomType::aCZ = new ACZ ("CZ");
    stringType["CZ2"] = AtomType::aCZ2 = new ACZ2 ("CZ2");
    stringType["CZ3"] = AtomType::aCZ3 = new ACZ3 ("CZ3");
    stringType["H"] = AtomType::aH = new AH ("H");
    stringType["1H"] = t = AtomType::a1H = new A1H ("1H"); stringType["HN1"] = t; 
    stringType["2H"] = t = AtomType::a2H = new A2H ("2H"); stringType["HN2"] = t; 
    stringType["3H"] = t = AtomType::a3H = new A3H ("3H"); stringType["HN3"] = t; 
    stringType["HA"] = AtomType::aHA = new AHA ("HA");
    stringType["1HA"] = AtomType::aHA1 = new AHA1 ("1HA");
    stringType["2HA"] = AtomType::aHA2 = new AHA2 ("2HA");
    stringType["HB"] = AtomType::aHB = new AHB ("HB");
    stringType["1HB"] = AtomType::aHB1 = new AHB1 ("1HB");
    stringType["2HB"] = AtomType::aHB2 = new AHB2 ("2HB");
    stringType["3HB"] = AtomType::aHB3 = new AHB3 ("3HB");
    stringType["1HD"] = t = AtomType::aHD1 = new AHD1 ("HD1"); stringType["HD1"] = t; 
    stringType["2HD"] = t = AtomType::aHD2 = new AHD2 ("HD2"); stringType["HD2"] = t; 
    stringType["HE"] = AtomType::aHE = new AHE ("HE");
    stringType["1HE"] = t = AtomType::aHE1 = new AHE1 ("HE1"); stringType["HE1"] = t; 
    stringType["2HE"] = t = AtomType::aHE2 = new AHE2 ("HE2"); stringType["HE2"] = t;
    stringType["3HE"] = t = AtomType::aHE3 = new AHE3 ("HE3"); stringType["HE3"] = t;
    stringType["HG"] = AtomType::aHG = new AHG ("HG");
    stringType["1HG"] = t = AtomType::aHG1 = new AHG1 ("HG1"); stringType["HG1"] = t; 
    stringType["2HG"] = t = AtomType::aHG2 = new AHG2 ("HG2"); stringType["HG2"] = t; 
    stringType["HH"] = AtomType::aHH = new AHH ("HH");
    stringType["HH2"] = AtomType::aHH2 = new AHH2 ("HH2");
    stringType["HXT"] = AtomType::aHXT = new AHXT ("HXT");
    stringType["HZ"] = AtomType::aHZ = new AHZ ("HZ");
    stringType["1HZ"] = t = AtomType::aHZ1 = new AHZ1 ("HZ1"); stringType["HZ1"] = t; 
    stringType["2HZ"] = t = AtomType::aHZ2 = new AHZ2 ("HZ2"); stringType["HZ2"] = t; 
    stringType["3HZ"] = t = AtomType::aHZ3 = new AHZ3 ("HZ3"); stringType["HZ3"] = t; 
    stringType["N"] = AtomType::aN = new AN ("N");
    stringType["ND1"] = AtomType::aND1 = new AND1 ("ND1");
    stringType["ND2"] = AtomType::aND2 = new AND2 ("ND2");
    stringType["NE"] = AtomType::aNE = new ANE ("NE");
    stringType["NE1"] = AtomType::aNE1 = new ANE1 ("NE1");
    stringType["NE2"] = AtomType::aNE2 = new ANE2 ("NE2");
    stringType["NH1"] = AtomType::aNH1 = new ANH1 ("NH1");
    stringType["NH2"] = AtomType::aNH2 = new ANH2 ("NH2");
    stringType["NZ"] = AtomType::aNZ = new ANZ ("NZ");
    stringType["O"] = AtomType::aO = new AO ("O");
    stringType["OD1"] = AtomType::aOD1 = new AOD1 ("OD1");
    stringType["OD2"] = AtomType::aOD2 = new AOD2 ("OD2");
    stringType["OE1"] = AtomType::aOE1 = new AOE1 ("OE1");
    stringType["OE2"] = AtomType::aOE2 = new AOE2 ("OE2");
    stringType["OG"] = AtomType::aOG = new AOG ("OG");
    stringType["OG1"] = AtomType::aOG1 = new AOG1 ("OG1");
    stringType["OH"] = AtomType::aOH = new AOH ("OH");
    stringType["OXT"] = AtomType::aOXT = new AOXT ("OXT");
    stringType["SD"] = AtomType::aSD = new ASD ("SD");
    stringType["SG"] = AtomType::aSG = new ASG ("SG");
    stringType["1HD1"] = AtomType::a1HD1 = new A1HD1 ("1HD1");
    stringType["1HD2"] = AtomType::a1HD2 = new A1HD2 ("1HD2");
    stringType["1HE2"] = AtomType::a1HE2 = new A1HE2 ("1HE2");
    stringType["1HG1"] = AtomType::a1HG1 = new A1HG1 ("1HG1");
    stringType["1HG2"] = AtomType::a1HG2 = new A1HG2 ("1HG2");
    stringType["1HH1"] = AtomType::a1HH1 = new A1HH1 ("1HH1");
    stringType["1HH2"] = AtomType::a1HH2 = new A1HH2 ("1HH2");
    stringType["2HD1"] = AtomType::a2HD1 = new A2HD1 ("2HD1");
    stringType["2HD2"] = AtomType::a2HD2 = new A2HD2 ("2HD2");
    stringType["2HE2"] = AtomType::a2HE2 = new A2HE2 ("2HE2");
    stringType["2HG1"] = AtomType::a2HG1 = new A2HG1 ("2HG1");
    stringType["2HG2"] = AtomType::a2HG2 = new A2HG2 ("2HG2");
    stringType["2HH1"] = AtomType::a2HH1 = new A2HH1 ("2HH1");
    stringType["2HH2"] = AtomType::a2HH2 = new A2HH2 ("2HH2");
    stringType["3HD1"] = AtomType::a3HD1 = new A3HD1 ("3HD1");
    stringType["3HD2"] = AtomType::a3HD2 = new A3HD2 ("3HD2");
    stringType["3HG1"] = AtomType::a3HG1 = new A3HG1 ("3HG1");
    stringType["3HG2"] = AtomType::a3HG2 = new A3HG2 ("3HG2");
    stringType["MG"] = AtomType::aMG = new AMG ("MG");
    stringType["PSAZ"] = AtomType::aPSAZ = new APSAZ ("PSAZ");
  }

  
  AtomTypeStore::~AtomTypeStore () 
  {
    set< AtomType* > bag;
    map< const char*, AtomType*, less_string >::iterator i;
    for (i=stringType.begin (); i!=stringType.end (); ++i) {
      bag.insert (i->second);
    }
    set< AtomType* >::iterator j;
    for (j=bag.begin (); j!=bag.end (); ++j) {
      delete *j;
    }
  }

  
  // METHODS -------------------------------------------------------------------

  AtomType* 
  AtomTypeStore::get (const char* s) 
  {
    AtomType* t = 0;
    char* str = new char[strlen (s) + 1];
    strcpy (str, s);

    for (char* i=str; *i; ++i) {
      if (*i == '\'') *i = '*';
      *i = toupper (*i);
    }
    
    if (stringType.find (str) != stringType.end ()) {
      t = stringType[str];
    } else {
      t = new AtomType (str);
      stringType[*t] = t;
    }
    delete[] str;
    return t;
  }
}
