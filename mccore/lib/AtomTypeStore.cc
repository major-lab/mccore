//                              -*- Mode: C++ -*- 
// AtomTypeStore.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 13:56:50 2003
// $Revision: 1.3 $

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "AtomTypeStore.h"
#include "Residue.h"

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

  const AtomType* 
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


  // TYPES ---------------------------------------------------------------------

  float
  AtomTypeStore::AC1p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();
    
    if (r == ResidueType::rRA)      return 0.0394;
    else if (r == ResidueType::rDA) return 0.0431;
    else if (r == ResidueType::rRC) return 0.0066;
    else if (r == ResidueType::rDC) return -0.0116;
    else if (r == ResidueType::rRG) return 0.0191;
    else if (r == ResidueType::rDG) return 0.0358;
    else if (r == ResidueType::rRU) return 0.0674;
    else if (r == ResidueType::rDT) return 0.0680;
    else                  return 0;
  }

  
  float
  AtomTypeStore::AC2p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isRNA ())
      return 0.0670;
    else if (res->getType ()->isDNA ())
      return -0.0854;
    else
      return 0;
  }
  

  float
  AtomTypeStore::AC3p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isRNA ())
      return 0.2022;
    else if (res->getType ()->isDNA ())
      return 0.0713;
    else
      return 0;
  }


  float
  AtomTypeStore::AC4p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isRNA ())
      return 0.1065;
    else if (res->getType ()->isDNA ())
      return 0.1629;
    else
      return 0;
  }

  float
  AtomTypeStore::AC5p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isRNA ())
      return 0.0558;
    else if (res->getType ()->isDNA ())
      return -0.0069;
    else
      return 0;
  }

  float
  AtomTypeStore::AH1p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();
  
    if (r == ResidueType::rDA) return 0.1838;
    else if (r == ResidueType::rRA) return 0.2007;
    else if (r == ResidueType::rDC) return 0.1963;
    else if (r == ResidueType::rRC) return 0.2029;
    else if (r == ResidueType::rDG) return 0.1746;
    else if (r == ResidueType::rRG) return 0.2006;
    else if (r == ResidueType::rDT) return 0.1804;
    else if (r == ResidueType::rRU) return 0.1824;
    else return 0;
  }


  float
  AtomTypeStore::AH2p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.0718;
    else if (res->getType ()->isRNA ())
      return 0.0972;
    else
      return 0;
  }

  float
  AtomTypeStore::AH3p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.0985;
    else if (res->getType ()->isRNA ())
      return 0.0615;
    else
      return 0;
  }

  float
  AtomTypeStore::AH4p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.1176;
    else if (res->getType ()->isRNA ())
      return 0.1174;
    else
      return 0;
  }


  float
  AtomTypeStore::AH5p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.0754;
    else if (res->getType ()->isRNA ())
      return 0.0679;
    else
      return 0;
  }



  float
  AtomTypeStore::AO1P::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return -0.7761;
    else if (res->getType ()->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2p::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isRNA ())
      return -0.6139;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2P::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return -0.7761;
    else if (res->getType ()->isRNA ())
      return -0.7760;
    else
      return 0;
  }





  float
  AtomTypeStore::AO3p::getVDWR (const Residue *res) const
  {
    return res->find (AtomType::aH3T) != res->end () ? 1.7210 : 1.6837;
  }



  float
  AtomTypeStore::AO3p::getAmberEpsilon (const Residue *res) const
  {
    return res->find (AtomType::aH3T) != res->end () ? 0.2104 : 0.1700;
  }
  
  
  
  float
  AtomTypeStore::AO3p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();
    
    if (res->find (AtomType::aH3T) == res->end ())
      {
	if (r->isDNA ())
	  return -0.5232;
	else if (r->isRNA ())
	  return -0.5246;
      }
    else
      {
	if (r->isDNA ())
	  return -0.6549;
	else if (r->isRNA ())
	  return -0.6541;
      }
    return 0;
  }


  float
  AtomTypeStore::AO3P::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return -0.7761;
    else if (res->getType ()->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO4p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();
  
    if (r->isDNA ())
      return -0.3691;
    else if (r->isRNA ())
      return -0.3548;
    else
      return 0;
  }



  float
  AtomTypeStore::AO5p::getVDWR (const Residue *res) const
  {
    return res->find (AtomType::aH5T) != res->end () ? 1.7210 : 1.6837;
  }



  float
  AtomTypeStore::AO5p::getAmberEpsilon (const Residue *res) const
  {
    return res->find (AtomType::aH5T) != res->end () ? 0.2104 : 0.1700;
  }



  float
  AtomTypeStore::AO5p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (res->find (AtomType::aH5T) != res->end ())
      {
	if (r->isDNA ())
	  return -0.6318;
	else if (r->isRNA ())
	  return -0.6223;
      }
    else
      {
	if (r->isDNA ())
	  return -0.4954;
	else if (r->isRNA ())
	  return -0.4989;
      }
    return 0;
  }



  float
  AtomTypeStore::AP::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      return 1.1659;
    else if (r->isRNA ())
      return 1.1662;
    return 0;
  }


  float
  AtomTypeStore::A1H2p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      return 0.0718;
    else if (r->isRNA ())
      return 0.0972;
    return 0;
  }


  float
  AtomTypeStore::A1H5p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }

  float
  AtomTypeStore::A2H2p::getAmberCharge (const Residue *res) const
  {
    return 0.0718;
  }


  float
  AtomTypeStore::A2H5p::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }


  float
  AtomTypeStore::AHO2p::getAmberCharge (const Residue *res) const
  {
    return 0.4186;
  }


  float
  AtomTypeStore::AC2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.5716;
	else if (r->isT ())
	  return 0.5677;
	else if (r->isG ())
	  return 0.7432;
	else if (r->isC ())
	  return 0.7959;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.5875;
	else if (r->isU ())
	  return 0.4687;
	else if (r->isG ())
	  return 0.7657;
	else if (r->isC ())
	  return 0.7538;
      }
    return 0;
  }

  float
  AtomTypeStore::AC4::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.3800;
	else if (r->isT ())
	  return 0.5194;
	else if (r->isG ())
	  return 0.1814;
	else if (r->isC ())
	  return 0.8439;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.3053;
	else if (r->isC ())
	  return 0.8185;
	else if (r->isG ())
	  return 0.1222;
	else if (r->isU ())
	  return 0.5952;
      }
    return 0;
  }

  float
  AtomTypeStore::AC5::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.0725;
	else if (r->isT ())
	  return 0.0025;
	else if (r->isG ())
	  return 0.1991;
	else if (r->isC ())
	  return -0.5222;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.0515;
	else if (r->isC ())
	  return -0.5215;
	else if (r->isG ())
	  return  0.1744;
	else if (r->isU ())
	  return -0.3635;
      }
    return 0;
  }


  float
  AtomTypeStore::AC6::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.6897;
	else if (r->isT ())
	  return -0.2209;
	else if (r->isG ())
	  return 0.4918;
	else if (r->isC ())
	  return -0.0183;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.7009;
	else if (r->isC ())
	  return 0.0053;
	else if (r->isG ())
	  return 0.4770;
	else if (r->isU ())
	  return -0.1126;
      }
    return 0;
  }

  float
  AtomTypeStore::AC8::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1607;
	else if (r->isG ())
	  return 0.0736;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.2006;
	else if (r->isG ())
	  return 0.1374;
      }
    return 0;
  }
  float
  AtomTypeStore::AH1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDG)
      return 0.3520;
    else if (res->getType () == ResidueType::rRG)
      return 0.3424;
    return 0;
  }



  float
  AtomTypeStore::AH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDA)
      return 0.0598;
    else if (res->getType () == ResidueType::rRA)
      return 0.0473;
    return 0;
  }


  float
  AtomTypeStore::AH3::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDT)
      return 0.3420;
    else if (res->getType () == ResidueType::rRU)
      return 0.3154;
    return 0;
  }



  float
  AtomTypeStore::AH5::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rDC)
      return 0.1863;
    else if (r == ResidueType::rRC)
      return 0.1928;
    else if (r == ResidueType::rRU)
      return 0.1811;
    return 0;
  }


  float
  AtomTypeStore::AH6::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isT ())
	  return 0.2607;
	else if (r->isC ())
	  return 0.2293;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return 0.1958;
	else if (r->isU ())
	  return 0.2188;
      }
    return 0;
  }
  float
  AtomTypeStore::AH8::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1877;
	else if (r->isG ())
	  return 0.1997;
      }
    else if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1553;
	else if (r->isG ())
	  return 0.1640;
      }
    return 0;
  }


  float
  AtomTypeStore::AN1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7624;
	else if (r->isT ())
	  return -0.0239;
	else if (r->isG ())
	  return -0.5053;
	else if (r->isC ())
	  return -0.0339;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.7615;
	else if (r->isC ())
	  return -0.0484;
	else if (r->isG ())
	  return -0.4787;
	else if (r->isU ())
	  return 0.0418;
      }
    return 0;
  }


  float
  AtomTypeStore::AN2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDG)
      return -0.9230;
    else if (res->getType () == ResidueType::rRG)
      return -0.9672;
    return 0;
  }


  float
  AtomTypeStore::AN3::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7417;
	else if (r->isT ())
	  return -0.4340;
	else if (r->isG ())
	  return -0.6636;
	else if (r->isC ())
	  return -0.7748;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6997;
	else if (r->isC ())
	  return -0.7584;
	else if (r->isG ())
	  return -0.6323;
	else if (r->isU ())
	  return -0.3549;
      }
    return 0;
  }


  float
  AtomTypeStore::AN4::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDC)
      return -0.9773;
    else if (res->getType () == ResidueType::rRC)
      return -0.9530;
    return 0;
  }

  float
  AtomTypeStore::AN6::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDA)
      return -0.9123;
    else if (res->getType () == ResidueType::rRA)
      return -0.9019;
    return 0;
  }

  float
  AtomTypeStore::AN7::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.6175;
	else if (r->isG ())
	  return -0.5725;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6073;
	else if (r->isG ())
	  return -0.5709;
      }
    return 0;
  }

  float
  AtomTypeStore::AN9::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.0268;
	else if (r->isG ())
	  return 0.0577;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.0251;
	else if (r->isG ())
	  return  0.0492;
      }
    return 0;
  }


  float
  AtomTypeStore::AO2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r->isDNA ())
      {
	if (r->isT ())
	  return -0.5881;
	else if (r->isC ())
	  return -0.6548;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return -0.6252;
	else if (r->isU ())
	  return -0.5477;
      }
    return 0;
  }


  float
  AtomTypeStore::AO4::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDT)
      return -0.5563;
    else if (res->getType () == ResidueType::rRU)
      return -0.5761;
    return 0;
  }


  float
  AtomTypeStore::AO6::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDG)
      return -0.5699;
    else if (res->getType () == ResidueType::rRG)
      return -0.5597;
    return 0;
  }

  float
  AtomTypeStore::A1H2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDG)
      return 0.4235;
    else if (res->getType () == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A1H4::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDC)
      return 0.4314;
    else if (res->getType () == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A1H5M::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A1H6::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDA)
      return 0.4167;
    else if (res->getType () == ResidueType::rRA)
      return 0.4115;
    return 0;
  }

  float
  AtomTypeStore::A2H2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDG)
      return 0.4235;
    else if (res->getType () == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A2H4::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDC)
      return 0.4314;
    else if (res->getType () == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A2H5M::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A2H6::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDA)
      return 0.4167;
    else if (res->getType () == ResidueType::rRA)
      return 0.4115;
    return 0;
  }


  float
  AtomTypeStore::A3H5M::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rDT)
      return 0.0770;
    return 0;
  }



  float
  AtomTypeStore::AH3T::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.4396;
    else if (res->getType ()->isRNA ())
      return 0.4376;
    return 0;
  }

  float
  AtomTypeStore::AH5T::getAmberCharge (const Residue *res) const
  {
    if (res->getType ()->isDNA ())
      return 0.4422;
    else if (res->getType ()->isRNA ())
      return 0.4295;
    return 0;
  }


  float
  AtomTypeStore::AC::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR       
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN       
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE       
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.59730;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.73410;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.53660;
    else if (r == ResidueType::rPRO)
      return 0.58960;
    return 0;
  }


  float
  AtomTypeStore::ACA::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA)
      return 0.03370;
    else if (r == ResidueType::rGLY)
      return -0.02520;
    else if (r == ResidueType::rSER)
      return -0.02490;
    else if (r == ResidueType::rTHR)
      return -0.03890;
    else if (r == ResidueType::rLEU)
      return -0.05180;
    else if (r == ResidueType::rILE)
      return -0.05970;
    else if (r == ResidueType::rVAL)
      return -0.08750;
    else if (r == ResidueType::rASN)
      return 0.01430;
    else if (r == ResidueType::rGLN)
      return -0.00310;
    else if (r == ResidueType::rARG)
      return -0.26370;
    else if (r == ResidueType::rHIS)
      return 0.01880;
    else if (r == ResidueType::rTRP)
      return -0.02750;
    else if (r == ResidueType::rPHE)
      return -0.00240;
    else if (r == ResidueType::rTYR)
      return -0.00140;
    else if (r == ResidueType::rGLU)
      return 0.03970;
    else if (r == ResidueType::rASP)
      return 0.03810;
    else if (r == ResidueType::rLYS)
      return -0.24000;
    else if (r == ResidueType::rPRO)
      return -0.02660;
    else if (r == ResidueType::rCYS)
      return 0.02130;
    else if (r == ResidueType::rMET)
      return -0.02370;
    return 0;
  }


  float
  AtomTypeStore::ACB::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA)
      return -0.18250;
    else if (r == ResidueType::rSER)
      return 0.21170;
    else if (r == ResidueType::rTHR)
      return 0.36540;
    else if (r == ResidueType::rLEU)
      return -0.11020;
    else if (r == ResidueType::rILE)
      return 0.13030;
    else if (r == ResidueType::rVAL)
      return 0.29850;
    else if (r == ResidueType::rASN)
      return -0.20410;
    else if (r == ResidueType::rGLN)
      return -0.00360;
    else if (r == ResidueType::rARG)
      return -0.00070;
    else if (r == ResidueType::rHIS)
      return -0.04620;
    else if (r == ResidueType::rTRP)
      return -0.00500;
    else if (r == ResidueType::rPHE)
      return -0.03430;
    else if (r == ResidueType::rTYR)
      return -0.01520;
    else if (r == ResidueType::rGLU)
      return 0.05600;
    else if (r == ResidueType::rASP)
      return -0.03030;
    else if (r == ResidueType::rLYS)
      return -0.00940;
    else if (r == ResidueType::rPRO)
      return -0.00700;
    else if (r == ResidueType::rCYS)
      return -0.12310;
    else if (r == ResidueType::rMET)
      return 0.03420;
    return 0;
  }


  float
  AtomTypeStore::ACD::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
  
    return type == ResidueType::rGLN || type == ResidueType::rGLU ? 0.0860 : 0.1094;
  }



  float
  AtomTypeStore::ACD::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rGLN)
      return 0.69510;
    else if (r == ResidueType::rARG)
      return 0.04860;
    else if (r == ResidueType::rGLU)
      return 0.80540;
    else if (r == ResidueType::rLYS)
      return -0.04790;
    else if (r == ResidueType::rPRO)
      return 0.01920;
    return 0;
  }

  float
  AtomTypeStore::ACD1::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
  
    return (type == ResidueType::rPHE
	    || type == ResidueType::rTYR
	    || type == ResidueType::rTRP
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return -0.41210;
    else if (r == ResidueType::rILE)
      return -0.06600;
    else if (r == ResidueType::rTRP)
      return -0.16380;
    else if (r == ResidueType::rPHE)
      return -0.12560;
    else if (r == ResidueType::rTYR)
      return -0.19060;
    return 0;
  }


  float
  AtomTypeStore::ACD2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return -0.41210;
    else if (r == ResidueType::rHIS)
      return 0.12920;
    else if (r == ResidueType::rTRP)
      return 0.12430;
    else if (r == ResidueType::rPHE)
      return -0.12560;
    else if (r == ResidueType::rTYR)
      return -0.19060;
    return 0;
  }


  float
  AtomTypeStore::ACE::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLYS)
      return -0.01430;
    else if (r == ResidueType::rMET)
      return -0.05360;
    return 0;
  }

  float
  AtomTypeStore::ACE1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rHIS)
      return 0.20570;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }



  float
  AtomTypeStore::ACE2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTRP)
      return 0.13800;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }


  float
  AtomTypeStore::ACE3::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return -0.23870;
    return 0;
  }


  float
  AtomTypeStore::ACG::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
  
    return ((type == ResidueType::rASN || type == ResidueType::rHIS || type == ResidueType::rTRP
	     || type == ResidueType::rPHE || type == ResidueType::rTYR || type == ResidueType::rASP)
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACG::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.35310;
    else if (r == ResidueType::rASN)
      return 0.71300;
    else if (r == ResidueType::rGLN)
      return -0.06450;
    else if (r == ResidueType::rARG)
      return 0.03900;
    else if (r == ResidueType::rHIS)
      return -0.02660;
    else if (r == ResidueType::rTRP)
      return -0.14150;
    else if (r == ResidueType::rPHE)
      return 0.01180;
    else if (r == ResidueType::rTYR)
      return -0.00110;
    else if (r == ResidueType::rGLU)
      return 0.01360;
    else if (r == ResidueType::rASP)
      return 0.79940;
    else if (r == ResidueType::rLYS)
      return 0.01870;
    else if (r == ResidueType::rPRO)
      return 0.01890;
    else if (r == ResidueType::rMET)
      return 0.00180;
    return 0;
  }



  float
  AtomTypeStore::ACG1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rILE)
      return -0.04300;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACG2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTHR)
      return -0.24380;
    else if (r == ResidueType::rILE)
      return -0.32040;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return -0.11340;
    return 0;
  }


  float
  AtomTypeStore::ACZ::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rARG)
      return 0.80760;
    else if (r == ResidueType::rPHE)
      return -0.10720;
    else if (r == ResidueType::rTYR)
      return 0.32260;
    return 0;
  }


  float
  AtomTypeStore::ACZ2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return -0.26010;
    return 0;
  }


  float
  AtomTypeStore::ACZ3::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return -0.19720;
    return 0;
  }


  float
  AtomTypeStore::AH::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.27190;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.27470;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.29360;
    return 0;
  }


  float
  AtomTypeStore::AHA::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA)
      return 0.08230;
    else if (r == ResidueType::rSER)
      return 0.08430;
    else if (r == ResidueType::rTHR)
      return 0.10070;
    else if (r == ResidueType::rLEU)
      return 0.09220;
    else if (r == ResidueType::rILE)
      return 0.08690;
    else if (r == ResidueType::rVAL)
      return 0.09690;
    else if (r == ResidueType::rASN)
      return 0.10480;
    else if (r == ResidueType::rGLN)
      return 0.08500;
    else if (r == ResidueType::rARG)
      return 0.15600;
    else if (r == ResidueType::rHIS)
      return 0.08810;
    else if (r == ResidueType::rTRP)
      return 0.11230;
    else if (r == ResidueType::rPHE)
      return 0.09780;
    else if (r == ResidueType::rTYR)
      return 0.08760;
    else if (r == ResidueType::rGLU)
      return 0.11050;
    else if (r == ResidueType::rASP || r == ResidueType::rMET)
      return 0.08800;
    else if (r == ResidueType::rLYS)
      return 0.14260;
    else if (r == ResidueType::rPRO)
      return 0.06410;
    else if (r == ResidueType::rCYS)
      return 0.11240;
    return 0;
  }


  float
  AtomTypeStore::AHA1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHA2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHB::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTHR)
      return 0.00430;
    else if (r == ResidueType::rILE)
      return 0.01870;
    else if (r == ResidueType::rVAL)
      return -0.02970;
    return 0;
  }

  float
  AtomTypeStore::AHB1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rALA)
      return 0.06030;
    return 0;
  }



  float
  AtomTypeStore::AHB2::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
  
    return (type == ResidueType::rSER || type == ResidueType::rCYS) ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA)
      return 0.06030;
    else if (r == ResidueType::rSER)
      return 0.03520;
    else if (r == ResidueType::rLEU)
      return 0.04570;
    else if (r == ResidueType::rASN)
      return 0.07970;
    else if (r == ResidueType::rGLN)
      return 0.01710;
    else if (r == ResidueType::rARG)
      return 0.03270;
    else if (r == ResidueType::rHIS)
      return 0.04020;
    else if (r == ResidueType::rTRP)
      return 0.03390;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950;
    else if (r == ResidueType::rGLU)
      return -0.01730;
    else if (r == ResidueType::rASP)
      return -0.01220;
    else if (r == ResidueType::rLYS)
      return 0.03620;
    else if (r == ResidueType::rPRO)
      return 0.02530;
    else if (r == ResidueType::rCYS)
      return 0.11120;
    else if (r == ResidueType::rMET)
      return 0.02410;
    return 0;
  }

  float
  AtomTypeStore::AHB3::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
  
    return type == ResidueType::rSER || type == ResidueType::rCYS ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB3::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA)
      return 0.06030;
    else if (r == ResidueType::rSER)
      return 0.03520;
    else if (r == ResidueType::rLEU)
      return 0.04570;
    else if (r == ResidueType::rASN)
      return 0.07970;
    else if (r == ResidueType::rGLN)
      return 0.01710;
    else if (r == ResidueType::rARG)
      return 0.03270;
    else if (r == ResidueType::rHIS)
      return 0.04020;
    else if (r == ResidueType::rTRP)
      return 0.03390;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950;
    else if (r == ResidueType::rGLU)
      return -0.01730;
    else if (r == ResidueType::rASP)
      return -0.01220;
    else if (r == ResidueType::rLYS)
      return 0.03620;
    else if (r == ResidueType::rPRO)
      return 0.02530;
    else if (r == ResidueType::rCYS)
      return 0.11120;
    else if (r == ResidueType::rMET)
      return 0.02410;
    return 0;
  }

  float
  AtomTypeStore::AHD1::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rHIS)
      return 0.6000;
    else if (type == ResidueType::rTRP)
      return 1.4090;
    else
      return 1.4590;
  }



  float
  AtomTypeStore::AHD1::getAmberEpsilon (const Residue *res) const
  {
    return res->getType () == ResidueType::rHIS ? 0.0157 : 0.0150;
  }



  float
  AtomTypeStore::AHD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rHIS)
      return 0.36490;
    else if (r == ResidueType::rTRP)
      return 0.20620;
    else if (r == ResidueType::rPHE)
      return 0.13300;
    else if (r == ResidueType::rTYR)
      return 0.16990;
    return 0;
  }


  float
  AtomTypeStore::AHD2::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rARG || type == ResidueType::rPRO)
      return 1.3870; // H1
    else if (type == ResidueType::rHIS)
      return 1.4090; // H4
    else if (type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 1.4590; // HA
    else if (type == ResidueType::rLYS)
      return 1.4870; // HC
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rARG || type == ResidueType::rPRO || type == ResidueType::rLYS)
      return 0.0157; // H1 HC
    else if (type == ResidueType::rHIS || type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 0.0150; // H4 HA
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rARG)
      return 0.06870;
    else if (r == ResidueType::rHIS)
      return 0.11470;
    else if (r == ResidueType::rPHE)
      return 0.13300;
    else if (r == ResidueType::rTYR)
      return 0.16990;
    else if (r == ResidueType::rLYS)
      return 0.06210;
    else if (r == ResidueType::rPRO)
      return 0.03910;
    return 0;
  }

  float
  AtomTypeStore::AHE::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return 0.34560;
    return 0;
  }



  float
  AtomTypeStore::AHE1::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rHIS)
      return 1.3590; // H5
    else if (type == ResidueType::rTRP)
      return 0.6000; // H
    else if (type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 1.4590; // HA
    else if (type == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rHIS || type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 0.0150; // H5 HA
    else if (type == ResidueType::rTRP || type == ResidueType::rMET)
      return 0.0157; // H H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rHIS)
      return 0.13920;
    else if (r == ResidueType::rTRP)
      return 0.34120;
    else if (r == ResidueType::rPHE)
      return 0.14300;
    else if (r == ResidueType::rTYR)
      return 0.16560;
    else if (r == ResidueType::rMET)
      return 0.06940;
    return 0;
  }

  float
  AtomTypeStore::AHE2::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rHIS)
      return 0.6000; // H
    else if (type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 1.4590; // HA
    else if (type == ResidueType::rLYS)
      return 1.1000; // HP
    else if (type == ResidueType::rMET)
      return 1.3870; // H1
    else if (type == ResidueType::rGLU)
      return 0.0000;
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rHIS || type == ResidueType::rLYS || type == ResidueType::rMET)
      return 0.0157; // H HP H1
    else if (type == ResidueType::rPHE || type == ResidueType::rTYR)
      return 0.0150; // HA
    else if (type == ResidueType::rGLU)
      return 0.0000; // HO
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rPHE)
      return 0.14300;
    else if (r == ResidueType::rTYR)
      return 0.16560;
    else if (r == ResidueType::rLYS)
      return 0.11350;
    else if (r == ResidueType::rMET)
      return 0.06840;
    return 0;
  }


  float
  AtomTypeStore::AHE3::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rTRP)
      return 1.4590; // HA
    else if (type == ResidueType::rLYS)
      return 1.1000; // HP
    else if (type == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rLYS || type == ResidueType::rMET)
      return 0.0157; // HP H1
    else if (type == ResidueType::rTRP)
      return 0.0150; // HA
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTRP)
      return 0.17000;
    else if (r == ResidueType::rLYS)
      return 0.11350;
    else if (r == ResidueType::rMET)
      return 0.06840;
    return 0;
  }


  float
  AtomTypeStore::AHG::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rSER)
      return 0.42750;
    else if (r == ResidueType::rLEU)
      return -0.03610;
    else if (r == ResidueType::rCYS)
      return 0.19330;
    return 0;
  }


  float
  AtomTypeStore::AHG1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTHR)
      return 0.41020;
    return 0;
  }


  float
  AtomTypeStore::AHG2::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rGLN || type == ResidueType::rARG || type == ResidueType::rGLU || type == ResidueType::rLYS
	|| type == ResidueType::rPRO)
      return 1.4870; // HC
    else if (type == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHG2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rGLN)
      return 0.03520;
    else if (r == ResidueType::rARG)
      return 0.02850;
    else if (r == ResidueType::rGLU)
      return -0.04250;
    else if (r == ResidueType::rLYS)
      return 0.01030;
    else if (r == ResidueType::rPRO)
      return 0.02130;
    else if (r == ResidueType::rMET)
      return 0.04400;
    return 0;
  }

  float
  AtomTypeStore::AHH::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTYR)
      return 0.39920;
    return 0;
  }


  float
  AtomTypeStore::AHH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return 0.14170;
    return 0;
  }


  float
  AtomTypeStore::AHZ::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rPHE)
      return 0.12970;
    return 0;
  }


  float
  AtomTypeStore::AHZ1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rTRP)
      return 1.4590; // HA
    else if (type == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rTRP)
      return 0.0150; // HA
    else if (type == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return 0.15720;
    else if (res->getType ()== ResidueType::rLYS)
      return 0.34000;
    return 0;
  }

  float
  AtomTypeStore::AHZ3::getVDWR (const Residue *res) const
  {
    const ResidueType *type = res->getType ();
    
    if (type == ResidueType::rTRP)
      return 1.4590; // HA
    else if (type == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberEpsilon (const Residue *res) const
  {
    const ResidueType *type = res->getType ();

    if (type == ResidueType::rTRP)
      return 0.0150; // HA
    else if (type == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return 0.14470;
    else if (res->getType () == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }


  float
  AtomTypeStore::AN::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.41570;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.34790;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.51630;
    else if (r == ResidueType::rPRO)
      return -0.25480;
    return 0;
  }


  float
  AtomTypeStore::AND1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rHIS)
      return -0.38110;
    return 0;
  }


  float
  AtomTypeStore::AND2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rASN)
      return -0.91910;
    return 0;
  }


  float
  AtomTypeStore::ANE::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return -0.52950;
    return 0;
  }


  float
  AtomTypeStore::ANE1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTRP)
      return -0.34180;
    return 0;
  }


  float
  AtomTypeStore::ANE2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rGLN)
      return -0.94070;
    else if (r == ResidueType::rHIS)
      return -0.57270;
    return 0;
  }

  float
  AtomTypeStore::ANH1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANZ::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rLYS)
      return -0.38540;
    return 0;
  }


  float
  AtomTypeStore::AO::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.56790;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.58940;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.58190;
    else if (r == ResidueType::rPRO)
      return -0.57480;
    return 0;
  }

  float
  AtomTypeStore::AOD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rASN)
      return -0.59310;
    else if (r == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOD2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOE1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rGLN)
      return -0.60860;
    else if (r == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOE2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOG::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rSER)
      return -0.65460;
    return 0;
  }

  float
  AtomTypeStore::AOG1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTHR)
      return -0.67610;
    return 0;
  }


  float
  AtomTypeStore::AOH::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rTYR)
      return -0.55790;
    return 0;
  }

  float
  AtomTypeStore::ASD::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rMET)
      return -0.27370;
    return 0;
  }


  float
  AtomTypeStore::ASG::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rCYS)
      return -0.31190;
    return 0;
  }


  float
  AtomTypeStore::A1HD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A1HD2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A1HE2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A1HG1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HG2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HH1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A1HH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A2HD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A2HD2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A2HE2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A2HG1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A2HG2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A2HH1::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A2HH2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A3HD1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }



  float
  AtomTypeStore::A3HD2::getAmberCharge (const Residue *res) const
  {
    if (res->getType () == ResidueType::rLEU)
      return 0.10000;
    return 0;
  }


  float
  AtomTypeStore::A3HG1::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A3HG2::getAmberCharge (const Residue *res) const
  {
    const ResidueType *r = res->getType ();

    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


}
