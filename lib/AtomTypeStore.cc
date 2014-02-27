//                              -*- Mode: C++ -*- 
// AtomTypeStore.cc
// Copyright @ 2003-07 Laboratoire de Biologie Informatique et Th�orique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 13:56:50 2003
// $Revision: 1.19 $
// $Id: AtomTypeStore.cc,v 1.19 2007-01-14 18:21:02 larosem Exp $
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


// cmake generated defines
#include <config.h>

#include "AtomTypeStore.h"
#include "ResidueType.h"
#include "Messagestream.h"

#include <cassert>


namespace mccore
{

  // LIFECYCLE -----------------------------------------------------------------

  AtomTypeStore::AtomTypeStore () 
  {
    string str;

    AtomType::aNull = *repository.insert (new Null ((str = ""))).first;
    AtomType::aUnknown = *repository.insert (new Unknown ((str = "UNK"))).first;
    AtomType::aC1p = *repository.insert (new AC1p ((str = "C1*"))).first;
    AtomType::aC2p = *repository.insert (new AC2p ((str = "C2*"))).first;
    AtomType::aC3p = *repository.insert (new AC3p ((str = "C3*"))).first;
    AtomType::aC4p = *repository.insert (new AC4p ((str = "C4*"))).first;
    AtomType::aC5p = *repository.insert (new AC5p ((str = "C5*"))).first;
    AtomType::aH1p = *repository.insert (new AH1p ((str = "H1*"))).first;
    AtomType::aH2p = *repository.insert (new AH2p ((str = "H2*"))).first;
    AtomType::aH3p = *repository.insert (new AH3p ((str = "H3*"))).first;
    AtomType::aH4p = *repository.insert (new AH4p ((str = "H4*"))).first;
    AtomType::aH5p = *repository.insert (new AH5p ((str = "H5*"))).first;
    AtomType::aO1P = *repository.insert (new AO1P ((str = "O1P"))).first;
    AtomType::aO2p = *repository.insert (new AO2p ((str = "O2*"))).first;
    AtomType::aO2P = *repository.insert (new AO2P ((str = "O2P"))).first;
    AtomType::aO3p = *repository.insert (new AO3p ((str = "O3*"))).first;
    AtomType::aO3P = *repository.insert (new AO3P ((str = "O3P"))).first;
    AtomType::aO4p = *repository.insert (new AO4p ((str = "O4*"))).first;
    AtomType::aO5p = *repository.insert (new AO5p ((str = "O5*"))).first;
    AtomType::aP = *repository.insert (new AP ((str = "P"))).first;
    AtomType::a1H2p = *repository.insert (new A1H2p ((str = "1H2*"))).first;
    AtomType::a1H5p = *repository.insert (new A1H5p ((str = "1H5*"))).first;
    AtomType::a2H2p = *repository.insert (new A2H2p ((str = "2H2*"))).first;
    AtomType::a2H5p = *repository.insert (new A2H5p ((str = "2H5*"))).first;
    AtomType::aHO2p = *repository.insert (new AHO2p ((str = "HO2*"))).first;
    AtomType::aHO3p = *repository.insert (new AHO3p ((str = "HO3*"))).first;
    AtomType::aC2 = *repository.insert (new AC2 ((str = "C2"))).first;
    AtomType::aC4 = *repository.insert (new AC4 ((str = "C4"))).first;
    AtomType::aC5 = *repository.insert (new AC5 ((str = "C5"))).first;
    AtomType::aC5M = *repository.insert (new AC5M ((str = "C5M"))).first;
    AtomType::aC6 = *repository.insert (new AC6 ((str = "C6"))).first;
    AtomType::aC8 = *repository.insert (new AC8 ((str = "C8"))).first;
    AtomType::aH1 = *repository.insert (new AH1 ((str = "H1"))).first;
    AtomType::aH2 = *repository.insert (new AH2 ((str = "H2"))).first;
    AtomType::aH3 = *repository.insert (new AH3 ((str = "H3"))).first;
    AtomType::aH5 = *repository.insert (new AH5 ((str = "H5"))).first;
    AtomType::aH6 = *repository.insert (new AH6 ((str = "H6"))).first;
    AtomType::aH7 = *repository.insert (new AH7 ((str = "H7"))).first;
    AtomType::aH8 = *repository.insert (new AH8 ((str = "H8"))).first;
    AtomType::aN1 = *repository.insert (new AN1 ((str = "N1"))).first;
    AtomType::aN2 = *repository.insert (new AN2 ((str = "N2"))).first;
    AtomType::aN3 = *repository.insert (new AN3 ((str = "N3"))).first;
    AtomType::aN4 = *repository.insert (new AN4 ((str = "N4"))).first;
    AtomType::aN6 = *repository.insert (new AN6 ((str = "N6"))).first;
    AtomType::aN7 = *repository.insert (new AN7 ((str = "N7"))).first;
    AtomType::aN9 = *repository.insert (new AN9 ((str = "N9"))).first;
    AtomType::aO2 = *repository.insert (new AO2 ((str = "O2"))).first;
    AtomType::aO4 = *repository.insert (new AO4 ((str = "O4"))).first;
    AtomType::aO6 = *repository.insert (new AO6 ((str = "O6"))).first;
    AtomType::a1H2 = *repository.insert (new A1H2 ((str = "1H2"))).first;
    AtomType::a1H4 = *repository.insert (new A1H4 ((str = "1H4"))).first;
    AtomType::a1H5M = *repository.insert (new A1H5M ((str = "1H5M"))).first;
    AtomType::a1H6 = *repository.insert (new A1H6 ((str = "1H6"))).first;
    AtomType::a2H2 = *repository.insert (new A2H2 ((str = "2H2"))).first;
    AtomType::a2H4 = *repository.insert (new A2H4 ((str = "2H4"))).first;
    AtomType::a2H5M = *repository.insert (new A2H5M ((str = "2H5M"))).first;
    AtomType::a2H6 = *repository.insert (new A2H6 ((str = "2H6"))).first;
    AtomType::a3H5M = *repository.insert (new A3H5M ((str = "3H5M"))).first;
    AtomType::aPSX = *repository.insert (new APSX ((str = "PSX"))).first;
    AtomType::aPSY = *repository.insert (new APSY ((str = "PSY"))).first;
    AtomType::aPSZ = *repository.insert (new APSZ ((str = "PSZ"))).first;
    AtomType::aPSO = *repository.insert (new APSO ((str = "PSO"))).first;
    AtomType::aLP1 = *repository.insert (new ALP1 ((str = "LP1"))).first;
    AtomType::aLP3 = *repository.insert (new ALP3 ((str = "LP3"))).first;
    AtomType::aLP7 = *repository.insert (new ALP7 ((str = "LP7"))).first;
    AtomType::a1LP2 = *repository.insert (new A1LP2 ((str = "1LP2"))).first;
    AtomType::a1LP4 = *repository.insert (new A1LP4 ((str = "1LP4"))).first;
    AtomType::a1LP6 = *repository.insert (new A1LP6 ((str = "1LP6"))).first;
    AtomType::a2LP2 = *repository.insert (new A2LP2 ((str = "2LP2"))).first;
    AtomType::a2LP4 = *repository.insert (new A2LP4 ((str = "2LP4"))).first;
    AtomType::a2LP6 = *repository.insert (new A2LP6 ((str = "2LP6"))).first;
    AtomType::aH3T = *repository.insert (new AH3T ((str = "H3T"))).first;
    AtomType::aH5T = *repository.insert (new AH5T ((str = "H5T"))).first;
    AtomType::aC = *repository.insert (new AC ((str = "C"))).first;
    AtomType::aCA = *repository.insert (new ACA ((str = "CA"))).first;
    AtomType::aCB = *repository.insert (new ACB ((str = "CB"))).first;
    AtomType::aCD = *repository.insert (new ACD ((str = "CD"))).first;
    AtomType::aCD1 = *repository.insert (new ACD1 ((str = "CD1"))).first;
    AtomType::aCD2 = *repository.insert (new ACD2 ((str = "CD2"))).first;
    AtomType::aCE = *repository.insert (new ACE ((str = "CE"))).first;
    AtomType::aCE1 = *repository.insert (new ACE1 ((str = "CE1"))).first;
    AtomType::aCE2 = *repository.insert (new ACE2 ((str = "CE2"))).first;
    AtomType::aCE3 = *repository.insert (new ACE3 ((str = "CE3"))).first;
    AtomType::aCG = *repository.insert (new ACG ((str = "CG"))).first;
    AtomType::aCG1 = *repository.insert (new ACG1 ((str = "CG1"))).first;
    AtomType::aCG2 = *repository.insert (new ACG2 ((str = "CG2"))).first;
    AtomType::aCH2 = *repository.insert (new ACH2 ((str = "CH2"))).first;
    AtomType::aCZ = *repository.insert (new ACZ ((str = "CZ"))).first;
    AtomType::aCZ2 = *repository.insert (new ACZ2 ((str = "CZ2"))).first;
    AtomType::aCZ3 = *repository.insert (new ACZ3 ((str = "CZ3"))).first;
    AtomType::aH = *repository.insert (new AH ((str = "H"))).first;
    AtomType::a1H = *repository.insert (new A1H ((str = "1H"))).first;
    AtomType::a2H = *repository.insert (new A2H ((str = "2H"))).first;
    AtomType::a3H = *repository.insert (new A3H ((str = "3H"))).first;
    AtomType::aHA = *repository.insert (new AHA ((str = "HA"))).first;
    AtomType::aHA1 = *repository.insert (new AHA1 ((str = "HA1"))).first;
    AtomType::aHA2 = *repository.insert (new AHA2 ((str = "HA2"))).first;
    AtomType::aHB = *repository.insert (new AHB ((str = "HB"))).first;
    AtomType::aHB1 = *repository.insert (new AHB1 ((str = "HB1"))).first;
    AtomType::aHB2 = *repository.insert (new AHB2 ((str = "HB2"))).first;
    AtomType::aHB3 = *repository.insert (new AHB3 ((str = "HB3"))).first;
    AtomType::aHD1 = *repository.insert (new AHD1 ((str = "HD1"))).first;
    AtomType::aHD2 = *repository.insert (new AHD2 ((str = "HD2"))).first;
    AtomType::aHE = *repository.insert (new AHE ((str = "HE"))).first;
    AtomType::aHE1 = *repository.insert (new AHE1 ((str = "HE1"))).first;
    AtomType::aHE2 = *repository.insert (new AHE2 ((str = "HE2"))).first;
    AtomType::aHE3 = *repository.insert (new AHE3 ((str = "HE3"))).first;
    AtomType::aHG = *repository.insert (new AHG ((str = "HG"))).first;
    AtomType::aHG1 = *repository.insert (new AHG1 ((str = "HG1"))).first;
    AtomType::aHG2 = *repository.insert (new AHG2 ((str = "HG2"))).first;
    AtomType::aHH = *repository.insert (new AHH ((str = "HH"))).first;
    AtomType::aHH2 = *repository.insert (new AHH2 ((str = "HH2"))).first;
    AtomType::aHXT = *repository.insert (new AHXT ((str = "HXT"))).first;
    AtomType::aHZ = *repository.insert (new AHZ ((str = "HZ"))).first;
    AtomType::aHZ1 = *repository.insert (new AHZ1 ((str = "HZ1"))).first;
    AtomType::aHZ2 = *repository.insert (new AHZ2 ((str = "HZ2"))).first;
    AtomType::aHZ3 = *repository.insert (new AHZ3 ((str = "HZ3"))).first;
    AtomType::aN = *repository.insert (new AN ((str = "N"))).first;
    AtomType::aND1 = *repository.insert (new AND1 ((str = "ND1"))).first;
    AtomType::aND2 = *repository.insert (new AND2 ((str = "ND2"))).first;
    AtomType::aNE = *repository.insert (new ANE ((str = "NE"))).first;
    AtomType::aNE1 = *repository.insert (new ANE1 ((str = "NE1"))).first;
    AtomType::aNE2 = *repository.insert (new ANE2 ((str = "NE2"))).first;
    AtomType::aNH1 = *repository.insert (new ANH1 ((str = "NH1"))).first;
    AtomType::aNH2 = *repository.insert (new ANH2 ((str = "NH2"))).first;
    AtomType::aNZ = *repository.insert (new ANZ ((str = "NZ"))).first;
    AtomType::aO = *repository.insert (new AO ((str = "O"))).first;
    AtomType::aOD1 = *repository.insert (new AOD1 ((str = "OD1"))).first;
    AtomType::aOD2 = *repository.insert (new AOD2 ((str = "OD2"))).first;
    AtomType::aOE1 = *repository.insert (new AOE1 ((str = "OE1"))).first;
    AtomType::aOE2 = *repository.insert (new AOE2 ((str = "OE2"))).first;
    AtomType::aOG = *repository.insert (new AOG ((str = "OG"))).first;
    AtomType::aOG1 = *repository.insert (new AOG1 ((str = "OG1"))).first;
    AtomType::aOH = *repository.insert (new AOH ((str = "OH"))).first;
    AtomType::aOXT = *repository.insert (new AOXT ((str = "OXT"))).first;
    AtomType::aSD = *repository.insert (new ASD ((str = "SD"))).first;
    AtomType::aSG = *repository.insert (new ASG ((str = "SG"))).first;
    AtomType::a1HD1 = *repository.insert (new A1HD1 ((str = "1HD1"))).first;
    AtomType::a1HD2 = *repository.insert (new A1HD2 ((str = "1HD2"))).first;
    AtomType::a1HE2 = *repository.insert (new A1HE2 ((str = "1HE2"))).first;
    AtomType::a1HG1 = *repository.insert (new A1HG1 ((str = "1HG1"))).first;
    AtomType::a1HG2 = *repository.insert (new A1HG2 ((str = "1HG2"))).first;
    AtomType::a1HH1 = *repository.insert (new A1HH1 ((str = "1HH1"))).first;
    AtomType::a1HH2 = *repository.insert (new A1HH2 ((str = "1HH2"))).first;
    AtomType::a2HD1 = *repository.insert (new A2HD1 ((str = "2HD1"))).first;
    AtomType::a2HD2 = *repository.insert (new A2HD2 ((str = "2HD2"))).first;
    AtomType::a2HE2 = *repository.insert (new A2HE2 ((str = "2HE2"))).first;
    AtomType::a2HG1 = *repository.insert (new A2HG1 ((str = "2HG1"))).first;
    AtomType::a2HG2 = *repository.insert (new A2HG2 ((str = "2HG2"))).first;
    AtomType::a2HH1 = *repository.insert (new A2HH1 ((str = "2HH1"))).first;
    AtomType::a2HH2 = *repository.insert (new A2HH2 ((str = "2HH2"))).first;
    AtomType::a3HD1 = *repository.insert (new A3HD1 ((str = "3HD1"))).first;
    AtomType::a3HD2 = *repository.insert (new A3HD2 ((str = "3HD2"))).first;
    AtomType::a3HG1 = *repository.insert (new A3HG1 ((str = "3HG1"))).first;
    AtomType::a3HG2 = *repository.insert (new A3HG2 ((str = "3HG2"))).first;
    AtomType::aMG = *repository.insert (new AMG ((str = "MG"))).first;
    AtomType::aPSAZ = *repository.insert (new APSAZ ((str = "PSAZ"))).first;

    // New AtomType (some are invalid type names due to their notation in
    // the components.cif.gz file
    //
    AtomType::a1HM1 = *repository.insert (new A1HM1 ((str = "1HM1"))).first;
    AtomType::a1HN6 = *repository.insert (new A1HN6 ((str = "1HN6"))).first;
    AtomType::a2HM1 = *repository.insert (new A2HM1 ((str = "2HM1"))).first;
    AtomType::a2HN6 = *repository.insert (new A2HN6 ((str = "2HN6"))).first;
    AtomType::a3HM1 = *repository.insert (new A3HM1 ((str = "3HM1"))).first;
    AtomType::aCM1 = *repository.insert (new ACM1 ((str = "CM1"))).first;
  }

  
  AtomTypeStore::~AtomTypeStore () 
  {
	  mapping.clear();
    set< AtomType*, AtomType::less_deref >::iterator it;
    for (it = repository.begin (); it != repository.end (); ++it)
    {
      delete *it;
    }
  }

  
  // METHODS -------------------------------------------------------------------

  const AtomType* 
  AtomTypeStore::get (const string& key) 
  {
	  const AtomType* atype = 0;
    string key2 = key;
    string::iterator sit;

    for (sit = key2.begin (); sit != key2.end (); ++sit)
    {
      if ('\'' == *sit)
	*sit = '*';
      else
	*sit = toupper (*sit);
    }

    AtomType* aNewType = new Unknown (key2);
    set< AtomType*, AtomType::less_deref >::iterator itFind = repository.find(aNewType);

    if (itFind != repository.end()) // no unique insertion => key exists
    {
      delete aNewType;
      atype = *itFind;
    }
    else
    {
    	// Look into the mapping for equivalence
    	std::map<std::string, const AtomType*>::const_iterator itMap;
    	itMap = mapping.find(key);
    	if(itMap != mapping.end())
    	{
    		delete aNewType;
    		atype = itMap->second;
    	}else
    	{
    		pair< set< AtomType*, AtomType::less_deref >::iterator, bool > inserted;
    		inserted = repository.insert (aNewType);
    		assert(inserted.second);
    		atype = aNewType;
    		gOut (4) << endl << "... created unknown atom type \'" << atype << "\'" << endl;
    	}
    }

    return atype;
  }

  void AtomTypeStore::addMapping(const string& key, const AtomType* apType)
  {
	  mapping[key] = apType;
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
