//                              -*- Mode: C++ -*- 
// AtomTypeStore.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 13:56:50 2003
// $Revision: 1.12 $

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "AtomTypeStore.h"
#include "Residue.h"


namespace mccore
{

  // LIFECYCLE -----------------------------------------------------------------

  AtomTypeStore::AtomTypeStore () 
  {
    AtomType::aNull = *this->repository.insert (new Null (string (""))).first;
    AtomType::aUnknown = *this->repository.insert (new Unknown (string ("UNK"))).first;
    AtomType::aC1p = *this->repository.insert (new AC1p (string ("C1*"))).first;
    AtomType::aC2p = *this->repository.insert (new AC2p (string ("C2*"))).first;
    AtomType::aC3p = *this->repository.insert (new AC3p (string ("C3*"))).first;
    AtomType::aC4p = *this->repository.insert (new AC4p (string ("C4*"))).first;
    AtomType::aC5p = *this->repository.insert (new AC5p (string ("C5*"))).first;
    AtomType::aH1p = *this->repository.insert (new AH1p (string ("H1*"))).first;
    AtomType::aH2p = *this->repository.insert (new AH2p (string ("H2*"))).first;
    AtomType::aH3p = *this->repository.insert (new AH3p (string ("H3*"))).first;
    AtomType::aH4p = *this->repository.insert (new AH4p (string ("H4*"))).first;
    AtomType::aH5p = *this->repository.insert (new AH5p (string ("H5*"))).first;
    AtomType::aO1P = *this->repository.insert (new AO1P (string ("O1P"))).first;
    AtomType::aO2p = *this->repository.insert (new AO2p (string ("O2*"))).first;
    AtomType::aO2P = *this->repository.insert (new AO2P (string ("O2P"))).first;
    AtomType::aO3p = *this->repository.insert (new AO3p (string ("O3*"))).first;
    AtomType::aO3P = *this->repository.insert (new AO3P (string ("O3P"))).first;
    AtomType::aO4p = *this->repository.insert (new AO4p (string ("O4*"))).first;
    AtomType::aO5p = *this->repository.insert (new AO5p (string ("O5*"))).first;
    AtomType::aP = *this->repository.insert (new AP (string ("P"))).first;
    AtomType::a1H2p = *this->repository.insert (new A1H2p (string ("1H2*"))).first;
    AtomType::a1H5p = *this->repository.insert (new A1H5p (string ("1H5*"))).first;
    AtomType::a2H2p = *this->repository.insert (new A2H2p (string ("2H2*"))).first;
    AtomType::a2H5p = *this->repository.insert (new A2H5p (string ("2H5*"))).first;
    AtomType::aHO2p = *this->repository.insert (new AHO2p (string ("HO2*"))).first;
    AtomType::aHO3p = *this->repository.insert (new AHO3p (string ("HO3*"))).first;
    AtomType::aC2 = *this->repository.insert (new AC2 (string ("C2"))).first;
    AtomType::aC4 = *this->repository.insert (new AC4 (string ("C4"))).first;
    AtomType::aC5 = *this->repository.insert (new AC5 (string ("C5"))).first;
    AtomType::aC5M = *this->repository.insert (new AC5M (string ("C5M"))).first;
    AtomType::aC6 = *this->repository.insert (new AC6 (string ("C6"))).first;
    AtomType::aC8 = *this->repository.insert (new AC8 (string ("C8"))).first;
    AtomType::aH1 = *this->repository.insert (new AH1 (string ("H1"))).first;
    AtomType::aH2 = *this->repository.insert (new AH2 (string ("H2"))).first;
    AtomType::aH3 = *this->repository.insert (new AH3 (string ("H3"))).first;
    AtomType::aH5 = *this->repository.insert (new AH5 (string ("H5"))).first;
    AtomType::aH6 = *this->repository.insert (new AH6 (string ("H6"))).first;
    AtomType::aH7 = *this->repository.insert (new AH7 (string ("H7"))).first;
    AtomType::aH8 = *this->repository.insert (new AH8 (string ("H8"))).first;
    AtomType::aN1 = *this->repository.insert (new AN1 (string ("N1"))).first;
    AtomType::aN2 = *this->repository.insert (new AN2 (string ("N2"))).first;
    AtomType::aN3 = *this->repository.insert (new AN3 (string ("N3"))).first;
    AtomType::aN4 = *this->repository.insert (new AN4 (string ("N4"))).first;
    AtomType::aN6 = *this->repository.insert (new AN6 (string ("N6"))).first;
    AtomType::aN7 = *this->repository.insert (new AN7 (string ("N7"))).first;
    AtomType::aN9 = *this->repository.insert (new AN9 (string ("N9"))).first;
    AtomType::aO2 = *this->repository.insert (new AO2 (string ("O2"))).first;
    AtomType::aO4 = *this->repository.insert (new AO4 (string ("O4"))).first;
    AtomType::aO6 = *this->repository.insert (new AO6 (string ("O6"))).first;
    AtomType::a1H2 = *this->repository.insert (new A1H2 (string ("1H2"))).first;
    AtomType::a1H4 = *this->repository.insert (new A1H4 (string ("1H4"))).first;
    AtomType::a1H5M = *this->repository.insert (new A1H5M (string ("1H5M"))).first;
    AtomType::a1H6 = *this->repository.insert (new A1H6 (string ("1H6"))).first;
    AtomType::a2H2 = *this->repository.insert (new A2H2 (string ("2H2"))).first;
    AtomType::a2H4 = *this->repository.insert (new A2H4 (string ("2H4"))).first;
    AtomType::a2H5M = *this->repository.insert (new A2H5M (string ("2H5M"))).first;
    AtomType::a2H6 = *this->repository.insert (new A2H6 (string ("2H6"))).first;
    AtomType::a3H5M = *this->repository.insert (new A3H5M (string ("3H5M"))).first;
    AtomType::aPSX = *this->repository.insert (new APSX (string ("PSX"))).first;
    AtomType::aPSY = *this->repository.insert (new APSY (string ("PSY"))).first;
    AtomType::aPSZ = *this->repository.insert (new APSZ (string ("PSZ"))).first;
    AtomType::aLP1 = *this->repository.insert (new ALP1 (string ("LP1"))).first;
    AtomType::aLP3 = *this->repository.insert (new ALP3 (string ("LP3"))).first;
    AtomType::aLP7 = *this->repository.insert (new ALP7 (string ("LP7"))).first;
    AtomType::a1LP2 = *this->repository.insert (new A1LP2 (string ("1LP2"))).first;
    AtomType::a1LP4 = *this->repository.insert (new A1LP4 (string ("1LP4"))).first;
    AtomType::a1LP6 = *this->repository.insert (new A1LP6 (string ("1LP6"))).first;
    AtomType::a2LP2 = *this->repository.insert (new A2LP2 (string ("2LP2"))).first;
    AtomType::a2LP4 = *this->repository.insert (new A2LP4 (string ("2LP4"))).first;
    AtomType::a2LP6 = *this->repository.insert (new A2LP6 (string ("2LP6"))).first;
    AtomType::aH3T = *this->repository.insert (new AH3T (string ("H3T"))).first;
    AtomType::aH5T = *this->repository.insert (new AH5T (string ("H5T"))).first;
    AtomType::aC = *this->repository.insert (new AC (string ("C"))).first;
    AtomType::aCA = *this->repository.insert (new ACA (string ("CA"))).first;
    AtomType::aCB = *this->repository.insert (new ACB (string ("CB"))).first;
    AtomType::aCD = *this->repository.insert (new ACD (string ("CD"))).first;
    AtomType::aCD1 = *this->repository.insert (new ACD1 (string ("CD1"))).first;
    AtomType::aCD2 = *this->repository.insert (new ACD2 (string ("CD2"))).first;
    AtomType::aCE = *this->repository.insert (new ACE (string ("CE"))).first;
    AtomType::aCE1 = *this->repository.insert (new ACE1 (string ("CE1"))).first;
    AtomType::aCE2 = *this->repository.insert (new ACE2 (string ("CE2"))).first;
    AtomType::aCE3 = *this->repository.insert (new ACE3 (string ("CE3"))).first;
    AtomType::aCG = *this->repository.insert (new ACG (string ("CG"))).first;
    AtomType::aCG1 = *this->repository.insert (new ACG1 (string ("CG1"))).first;
    AtomType::aCG2 = *this->repository.insert (new ACG2 (string ("CG2"))).first;
    AtomType::aCH2 = *this->repository.insert (new ACH2 (string ("CH2"))).first;
    AtomType::aCZ = *this->repository.insert (new ACZ (string ("CZ"))).first;
    AtomType::aCZ2 = *this->repository.insert (new ACZ2 (string ("CZ2"))).first;
    AtomType::aCZ3 = *this->repository.insert (new ACZ3 (string ("CZ3"))).first;
    AtomType::aH = *this->repository.insert (new AH (string ("H"))).first;
    AtomType::a1H = *this->repository.insert (new A1H (string ("1H"))).first;
    AtomType::a2H = *this->repository.insert (new A2H (string ("2H"))).first;
    AtomType::a3H = *this->repository.insert (new A3H (string ("3H"))).first;
    AtomType::aHA = *this->repository.insert (new AHA (string ("HA"))).first;
    AtomType::aHA1 = *this->repository.insert (new AHA1 (string ("HA1"))).first;
    AtomType::aHA2 = *this->repository.insert (new AHA2 (string ("HA2"))).first;
    AtomType::aHB = *this->repository.insert (new AHB (string ("HB"))).first;
    AtomType::aHB1 = *this->repository.insert (new AHB1 (string ("HB1"))).first;
    AtomType::aHB2 = *this->repository.insert (new AHB2 (string ("HB2"))).first;
    AtomType::aHB3 = *this->repository.insert (new AHB3 (string ("HB3"))).first;
    AtomType::aHD1 = *this->repository.insert (new AHD1 (string ("HD1"))).first;
    AtomType::aHD2 = *this->repository.insert (new AHD2 (string ("HD2"))).first;
    AtomType::aHE = *this->repository.insert (new AHE (string ("HE"))).first;
    AtomType::aHE1 = *this->repository.insert (new AHE1 (string ("HE1"))).first;
    AtomType::aHE2 = *this->repository.insert (new AHE2 (string ("HE2"))).first;
    AtomType::aHE3 = *this->repository.insert (new AHE3 (string ("HE3"))).first;
    AtomType::aHG = *this->repository.insert (new AHG (string ("HG"))).first;
    AtomType::aHG1 = *this->repository.insert (new AHG1 (string ("HG1"))).first;
    AtomType::aHG2 = *this->repository.insert (new AHG2 (string ("HG2"))).first;
    AtomType::aHH = *this->repository.insert (new AHH (string ("HH"))).first;
    AtomType::aHH2 = *this->repository.insert (new AHH2 (string ("HH2"))).first;
    AtomType::aHXT = *this->repository.insert (new AHXT (string ("HXT"))).first;
    AtomType::aHZ = *this->repository.insert (new AHZ (string ("HZ"))).first;
    AtomType::aHZ1 = *this->repository.insert (new AHZ1 (string ("HZ1"))).first;
    AtomType::aHZ2 = *this->repository.insert (new AHZ2 (string ("HZ2"))).first;
    AtomType::aHZ3 = *this->repository.insert (new AHZ3 (string ("HZ3"))).first;
    AtomType::aN = *this->repository.insert (new AN (string ("N"))).first;
    AtomType::aND1 = *this->repository.insert (new AND1 (string ("ND1"))).first;
    AtomType::aND2 = *this->repository.insert (new AND2 (string ("ND2"))).first;
    AtomType::aNE = *this->repository.insert (new ANE (string ("NE"))).first;
    AtomType::aNE1 = *this->repository.insert (new ANE1 (string ("NE1"))).first;
    AtomType::aNE2 = *this->repository.insert (new ANE2 (string ("NE2"))).first;
    AtomType::aNH1 = *this->repository.insert (new ANH1 (string ("NH1"))).first;
    AtomType::aNH2 = *this->repository.insert (new ANH2 (string ("NH2"))).first;
    AtomType::aNZ = *this->repository.insert (new ANZ (string ("NZ"))).first;
    AtomType::aO = *this->repository.insert (new AO (string ("O"))).first;
    AtomType::aOD1 = *this->repository.insert (new AOD1 (string ("OD1"))).first;
    AtomType::aOD2 = *this->repository.insert (new AOD2 (string ("OD2"))).first;
    AtomType::aOE1 = *this->repository.insert (new AOE1 (string ("OE1"))).first;
    AtomType::aOE2 = *this->repository.insert (new AOE2 (string ("OE2"))).first;
    AtomType::aOG = *this->repository.insert (new AOG (string ("OG"))).first;
    AtomType::aOG1 = *this->repository.insert (new AOG1 (string ("OG1"))).first;
    AtomType::aOH = *this->repository.insert (new AOH (string ("OH"))).first;
    AtomType::aOXT = *this->repository.insert (new AOXT (string ("OXT"))).first;
    AtomType::aSD = *this->repository.insert (new ASD (string ("SD"))).first;
    AtomType::aSG = *this->repository.insert (new ASG (string ("SG"))).first;
    AtomType::a1HD1 = *this->repository.insert (new A1HD1 (string ("1HD1"))).first;
    AtomType::a1HD2 = *this->repository.insert (new A1HD2 (string ("1HD2"))).first;
    AtomType::a1HE2 = *this->repository.insert (new A1HE2 (string ("1HE2"))).first;
    AtomType::a1HG1 = *this->repository.insert (new A1HG1 (string ("1HG1"))).first;
    AtomType::a1HG2 = *this->repository.insert (new A1HG2 (string ("1HG2"))).first;
    AtomType::a1HH1 = *this->repository.insert (new A1HH1 (string ("1HH1"))).first;
    AtomType::a1HH2 = *this->repository.insert (new A1HH2 (string ("1HH2"))).first;
    AtomType::a2HD1 = *this->repository.insert (new A2HD1 (string ("2HD1"))).first;
    AtomType::a2HD2 = *this->repository.insert (new A2HD2 (string ("2HD2"))).first;
    AtomType::a2HE2 = *this->repository.insert (new A2HE2 (string ("2HE2"))).first;
    AtomType::a2HG1 = *this->repository.insert (new A2HG1 (string ("2HG1"))).first;
    AtomType::a2HG2 = *this->repository.insert (new A2HG2 (string ("2HG2"))).first;
    AtomType::a2HH1 = *this->repository.insert (new A2HH1 (string ("2HH1"))).first;
    AtomType::a2HH2 = *this->repository.insert (new A2HH2 (string ("2HH2"))).first;
    AtomType::a3HD1 = *this->repository.insert (new A3HD1 (string ("3HD1"))).first;
    AtomType::a3HD2 = *this->repository.insert (new A3HD2 (string ("3HD2"))).first;
    AtomType::a3HG1 = *this->repository.insert (new A3HG1 (string ("3HG1"))).first;
    AtomType::a3HG2 = *this->repository.insert (new A3HG2 (string ("3HG2"))).first;
    AtomType::aMG = *this->repository.insert (new AMG (string ("MG"))).first;
    AtomType::aPSAZ = *this->repository.insert (new APSAZ (string ("PSAZ"))).first;
  }

  
  AtomTypeStore::~AtomTypeStore () 
  {
    set< AtomType*, AtomType::less_deref >::iterator it;
    for (it = this->repository.begin (); it != this->repository.end (); ++it)
      delete *it;
  }

  
  // METHODS -------------------------------------------------------------------

  const AtomType* 
  AtomTypeStore::get (const string& key) 
  {
    string key2 = key;
    string::iterator sit;

    for (sit = key2.begin (); sit != key2.end (); ++sit)
    {
      if ('\'' == *sit)
	*sit = '*';
      else
	*sit = toupper (*sit);
    }

    AtomType* atype = new Unknown (key2);    
    pair< set< AtomType*, AtomType::less_deref >::iterator, bool > inserted =
      this->repository.insert (atype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete atype;
      atype = *inserted.first;
    }

    return atype;
  }


  // TYPES ---------------------------------------------------------------------

  float
  AtomTypeStore::AC1p::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AC2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0670;
    else if (r->isDNA ())
      return -0.0854;
    else
      return 0;
  }
  

  float
  AtomTypeStore::AC3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.2022;
    else if (r->isDNA ())
      return 0.0713;
    else
      return 0;
  }


  float
  AtomTypeStore::AC4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.1065;
    else if (r->isDNA ())
      return 0.1629;
    else
      return 0;
  }

  float
  AtomTypeStore::AC5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0558;
    else if (r->isDNA ())
      return -0.0069;
    else
      return 0;
  }

  float
  AtomTypeStore::AH1p::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AH2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718;
    else if (r->isRNA ())
      return 0.0972;
    else
      return 0;
  }

  float
  AtomTypeStore::AH3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0985;
    else if (r->isRNA ())
      return 0.0615;
    else
      return 0;
  }

  float
  AtomTypeStore::AH4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.1176;
    else if (r->isRNA ())
      return 0.1174;
    else
      return 0;
  }


  float
  AtomTypeStore::AH5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    else
      return 0;
  }



  float
  AtomTypeStore::AO1P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return -0.6139;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }





  float
  AtomTypeStore::AO3p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO3p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700;  // Assumes the residue is not terminal
  }
  
  
  
  float
  AtomTypeStore::AO3p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH3T) == res->end ())
//       {
    // *** Now assumes the residue is not terminal
    if (r->isDNA ())
      return -0.5232;
    else if (r->isRNA ())
      return -0.5246;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.6549;
// 	else if (r->isRNA ())
// 	  return -0.6541;
//       }
    return 0;
  }


  float
  AtomTypeStore::AO3P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.3691;
    else if (r->isRNA ())
      return -0.3548;
    else
      return 0;
  }



  float
  AtomTypeStore::AO5p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH5T) != res->end ())
//       {
    // Assumes the residue is not terminal
    if (r->isDNA ())
      return -0.6318;
    else if (r->isRNA ())
      return -0.6223;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.4954;
// 	else if (r->isRNA ())
// 	  return -0.4989;
//       }
    return 0;
  }



  float
  AtomTypeStore::AP::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 1.1659;
    else if (r->isRNA ())
      return 1.1662;
    return 0;
  }


  float
  AtomTypeStore::A1H2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718;
    else if (r->isRNA ())
      return 0.0972;
    return 0;
  }


  float
  AtomTypeStore::A1H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }

  float
  AtomTypeStore::A2H2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.0718;
  }


  float
  AtomTypeStore::A2H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }


  float
  AtomTypeStore::AHO2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.4186;
  }


  float
  AtomTypeStore::AC2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AC4::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AC5::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AC6::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AC8::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.3520;
    else if (r == ResidueType::rRG)
      return 0.3424;
    return 0;
  }



  float
  AtomTypeStore::AH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.0598;
    else if (r == ResidueType::rRA)
      return 0.0473;
    return 0;
  }


  float
  AtomTypeStore::AH3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.3420;
    else if (r == ResidueType::rRU)
      return 0.3154;
    return 0;
  }



  float
  AtomTypeStore::AH5::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.1863;
    else if (r == ResidueType::rRC)
      return 0.1928;
    else if (r == ResidueType::rRU)
      return 0.1811;
    return 0;
  }


  float
  AtomTypeStore::AH6::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AH8::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AN1::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AN2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.9230;
    else if (r == ResidueType::rRG)
      return -0.9672;
    return 0;
  }


  float
  AtomTypeStore::AN3::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AN4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return -0.9773;
    else if (r == ResidueType::rRC)
      return -0.9530;
    return 0;
  }

  float
  AtomTypeStore::AN6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return -0.9123;
    else if (r == ResidueType::rRA)
      return -0.9019;
    return 0;
  }

  float
  AtomTypeStore::AN7::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AN9::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AO2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AO4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return -0.5563;
    else if (r == ResidueType::rRU)
      return -0.5761;
    return 0;
  }


  float
  AtomTypeStore::AO6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.5699;
    else if (r == ResidueType::rRG)
      return -0.5597;
    return 0;
  }

  float
  AtomTypeStore::A1H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235;
    else if (r == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A1H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314;
    else if (r == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A1H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A1H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167;
    else if (r == ResidueType::rRA)
      return 0.4115;
    return 0;
  }

  float
  AtomTypeStore::A2H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235;
    else if (r == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A2H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314;
    else if (r == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A2H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A2H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167;
    else if (r == ResidueType::rRA)
      return 0.4115;
    return 0;
  }


  float
  AtomTypeStore::A3H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }



  float
  AtomTypeStore::AH3T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4396;
    else if (r->isRNA ())
      return 0.4376;
    return 0;
  }

  float
  AtomTypeStore::AH5T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4422;
    else if (r->isRNA ())
      return 0.4295;
    return 0;
  }


  float
  AtomTypeStore::AC::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACA::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACB::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACD::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rGLN || t == ResidueType::rGLU ? 0.0860 : 0.1094;
  }



  float
  AtomTypeStore::ACD::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACD1::getAmberEpsilon (const ResidueType *r) const
  {
    return (r == ResidueType::rPHE
	    || r == ResidueType::rTYR
	    || r == ResidueType::rTRP
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACD1::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACD2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.01430;
    else if (r == ResidueType::rMET)
      return -0.05360;
    return 0;
  }

  float
  AtomTypeStore::ACE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.20570;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }



  float
  AtomTypeStore::ACE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.13800;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }


  float
  AtomTypeStore::ACE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.23870;
    return 0;
  }


  float
  AtomTypeStore::ACG::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return ((t == ResidueType::rASN || t == ResidueType::rHIS || t == ResidueType::rTRP
	     || t == ResidueType::rPHE || t == ResidueType::rTYR || t == ResidueType::rASP)
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACG::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::ACG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return -0.04300;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.24380;
    else if (r == ResidueType::rILE)
      return -0.32040;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.11340;
    return 0;
  }


  float
  AtomTypeStore::ACZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.80760;
    else if (r == ResidueType::rPHE)
      return -0.10720;
    else if (r == ResidueType::rTYR)
      return 0.32260;
    return 0;
  }


  float
  AtomTypeStore::ACZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.26010;
    return 0;
  }


  float
  AtomTypeStore::ACZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.19720;
    return 0;
  }


  float
  AtomTypeStore::AH::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHA::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHA1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHA2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHB::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.00430;
    else if (r == ResidueType::rILE)
      return 0.01870;
    else if (r == ResidueType::rVAL)
      return -0.02970;
    return 0;
  }

  float
  AtomTypeStore::AHB1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030;
    return 0;
  }



  float
  AtomTypeStore::AHB2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return (t == ResidueType::rSER || t == ResidueType::rCYS) ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHB3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rSER || t == ResidueType::rCYS ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB3::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHD1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000;
    else if (t == ResidueType::rTRP)
      return 1.4090;
    else
      return 1.4590;
  }



  float
  AtomTypeStore::AHD1::getAmberEpsilon (const ResidueType *r) const
  {
    return r == ResidueType::rHIS ? 0.0157 : 0.0150;
  }



  float
  AtomTypeStore::AHD1::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHD2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO)
      return 1.3870; // H1
    else if (t == ResidueType::rHIS)
      return 1.4090; // H4
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.4870; // HC
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO || t == ResidueType::rLYS)
      return 0.0157; // H1 HC
    else if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // H4 HA
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.34560;
    return 0;
  }



  float
  AtomTypeStore::AHE1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 1.3590; // H5
    else if (t == ResidueType::rTRP)
      return 0.6000; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // H5 HA
    else if (t == ResidueType::rTRP || t == ResidueType::rMET)
      return 0.0157; // H H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHE2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000; // HP
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    else if (t == ResidueType::rGLU)
      return 0.0000;
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157; // H HP H1
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // HA
    else if (t == ResidueType::rGLU)
      return 0.0000; // HO
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHE3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000; // HP
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157; // HP H1
    else if (t == ResidueType::rTRP)
      return 0.0150; // HA
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.17000;
    else if (r == ResidueType::rLYS)
      return 0.11350;
    else if (r == ResidueType::rMET)
      return 0.06840;
    return 0;
  }


  float
  AtomTypeStore::AHG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return 0.42750;
    else if (r == ResidueType::rLEU)
      return -0.03610;
    else if (r == ResidueType::rCYS)
      return 0.19330;
    return 0;
  }


  float
  AtomTypeStore::AHG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.41020;
    return 0;
  }


  float
  AtomTypeStore::AHG2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rGLN || t == ResidueType::rARG || t == ResidueType::rGLU || t == ResidueType::rLYS
	|| t == ResidueType::rPRO)
      return 1.4870; // HC
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHG2::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AHH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return 0.39920;
    return 0;
  }


  float
  AtomTypeStore::AHH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14170;
    return 0;
  }


  float
  AtomTypeStore::AHZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rPHE)
      return 0.12970;
    return 0;
  }


  float
  AtomTypeStore::AHZ1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.15720;
    else if (r== ResidueType::rLYS)
      return 0.34000;
    return 0;
  }

  float
  AtomTypeStore::AHZ3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
    
    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14470;
    else if (r == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }


  float
  AtomTypeStore::AN::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AND1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return -0.38110;
    return 0;
  }


  float
  AtomTypeStore::AND2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.91910;
    return 0;
  }


  float
  AtomTypeStore::ANE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.52950;
    return 0;
  }


  float
  AtomTypeStore::ANE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.34180;
    return 0;
  }


  float
  AtomTypeStore::ANE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.94070;
    else if (r == ResidueType::rHIS)
      return -0.57270;
    return 0;
  }

  float
  AtomTypeStore::ANH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.38540;
    return 0;
  }


  float
  AtomTypeStore::AO::getAmberCharge (const ResidueType *r) const
  {
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
  AtomTypeStore::AOD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.59310;
    else if (r == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.60860;
    else if (r == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return -0.65460;
    return 0;
  }

  float
  AtomTypeStore::AOG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.67610;
    return 0;
  }


  float
  AtomTypeStore::AOH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return -0.55790;
    return 0;
  }

  float
  AtomTypeStore::ASD::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rMET)
      return -0.27370;
    return 0;
  }


  float
  AtomTypeStore::ASG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rCYS)
      return -0.31190;
    return 0;
  }


  float
  AtomTypeStore::A1HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A1HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A1HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A1HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A1HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A2HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A2HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A2HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A2HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A2HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A2HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A2HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A3HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }



  float
  AtomTypeStore::A3HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    return 0;
  }


  float
  AtomTypeStore::A3HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A3HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


}
