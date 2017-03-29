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

#include <algorithm>
#include <iterator>

#include "AtomTypeStore.h"
#include "ResidueType.h"
#include "Messagestream.h"

#ifdef _MSC_VER
// Disable some warnings for visual C
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced formal parameter
#endif

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

	  std::string key2;
	  std::transform(key.begin(), key.end(), std::back_inserter(key2), [](const char elem)
	  {
		  return ('\'' == elem) ? '*' : toupper(elem);
	  });

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
    if (r == ResidueType::rRA)      return 0.0394f;
    else if (r == ResidueType::rDA) return 0.0431f;
    else if (r == ResidueType::rRC) return 0.0066f;
    else if (r == ResidueType::rDC) return -0.0116f;
    else if (r == ResidueType::rRG) return 0.0191f;
    else if (r == ResidueType::rDG) return 0.0358f;
    else if (r == ResidueType::rRU) return 0.0674f;
    else if (r == ResidueType::rDT) return 0.0680f;
    else                  return 0.f;
  }

  
  float
  AtomTypeStore::AC2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0670f;
    else if (r->isDNA ())
      return -0.0854f;
    else
      return 0.f;
  }
  

  float
  AtomTypeStore::AC3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.2022f;
    else if (r->isDNA ())
      return 0.0713f;
    else
      return 0.f;
  }


  float
  AtomTypeStore::AC4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.1065f;
    else if (r->isDNA ())
      return 0.1629f;
    else
      return 0.f;
  }

  float
  AtomTypeStore::AC5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0558f;
    else if (r->isDNA ())
      return -0.0069f;
    else
      return 0.f;
  }

  float
  AtomTypeStore::AH1p::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA) return 0.1838f;
    else if (r == ResidueType::rRA) return 0.2007f;
    else if (r == ResidueType::rDC) return 0.1963f;
    else if (r == ResidueType::rRC) return 0.2029f;
    else if (r == ResidueType::rDG) return 0.1746f;
    else if (r == ResidueType::rRG) return 0.2006f;
    else if (r == ResidueType::rDT) return 0.1804f;
    else if (r == ResidueType::rRU) return 0.1824f;
    else return 0.f;
  }


  float
  AtomTypeStore::AH2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718f;
    else if (r->isRNA ())
      return 0.0972f;
    else
      return 0.f;
  }

  float
  AtomTypeStore::AH3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0985f;
    else if (r->isRNA ())
      return 0.0615f;
    else
      return 0.f;
  }

  float
  AtomTypeStore::AH4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.1176f;
    else if (r->isRNA ())
      return 0.1174f;
    else
      return 0.f;
  }


  float
  AtomTypeStore::AH5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754f;
    else if (r->isRNA ())
      return 0.0679f;
    else
      return 0.f;
  }



  float
  AtomTypeStore::AO1P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761f;
    else if (r->isRNA ())
      return -0.7760f;
    else
      return 0.f;
  }


  float
  AtomTypeStore::AO2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return -0.6139f;
    else
      return 0.f;
  }


  float
  AtomTypeStore::AO2P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761f;
    else if (r->isRNA ())
      return -0.7760f;
    else
      return 0.f;
  }





  float
  AtomTypeStore::AO3p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837f;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO3p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700f;  // Assumes the residue is not terminal
  }
  
  
  
  float
  AtomTypeStore::AO3p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH3T) == res->end ())
//       {
    // *** Now assumes the residue is not terminal
    if (r->isDNA ())
      return -0.5232f;
    else if (r->isRNA ())
      return -0.5246f;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.6549;
// 	else if (r->isRNA ())
// 	  return -0.6541;
//       }
    return 0.f;
  }


  float
  AtomTypeStore::AO3P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761f;
    else if (r->isRNA ())
      return -0.7760f;
    else
      return 0.f;
  }


  float
  AtomTypeStore::AO4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.3691f;
    else if (r->isRNA ())
      return -0.3548f;
    else
      return 0.f;
  }



  float
  AtomTypeStore::AO5p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837f;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700f;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH5T) != res->end ())
//       {
    // Assumes the residue is not terminal
    if (r->isDNA ())
      return -0.6318f;
    else if (r->isRNA ())
      return -0.6223f;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.4954;
// 	else if (r->isRNA ())
// 	  return -0.4989;
//       }
    return 0.f;
  }



  float
  AtomTypeStore::AP::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 1.1659f;
    else if (r->isRNA ())
      return 1.1662f;
    return 0.f;
  }


  float
  AtomTypeStore::A1H2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718f;
    else if (r->isRNA ())
      return 0.0972f;
    return 0.f;
  }


  float
  AtomTypeStore::A1H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754f;
    else if (r->isRNA ())
      return 0.0679f;
    return 0.f;
  }

  float
  AtomTypeStore::A2H2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.0718f;
  }


  float
  AtomTypeStore::A2H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754f;
    else if (r->isRNA ())
      return 0.0679f;
    return 0.f;
  }


  float
  AtomTypeStore::AHO2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.4186f;
  }


  float
  AtomTypeStore::AC2::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.5716f;
	else if (r->isT ())
	  return 0.5677f;
	else if (r->isG ())
	  return 0.7432f;
	else if (r->isC ())
	  return 0.7959f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.5875f;
	else if (r->isU ())
	  return 0.4687f;
	else if (r->isG ())
	  return 0.7657f;
	else if (r->isC ())
	  return 0.7538f;
      }
    return 0.f;
  }

  float
  AtomTypeStore::AC4::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.3800f;
	else if (r->isT ())
	  return 0.5194f;
	else if (r->isG ())
	  return 0.1814f;
	else if (r->isC ())
	  return 0.8439f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.3053f;
	else if (r->isC ())
	  return 0.8185f;
	else if (r->isG ())
	  return 0.1222f;
	else if (r->isU ())
	  return 0.5952f;
      }
    return 0.f;
  }

  float
  AtomTypeStore::AC5::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.0725f;
	else if (r->isT ())
	  return 0.0025f;
	else if (r->isG ())
	  return 0.1991f;
	else if (r->isC ())
	  return -0.5222f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.0515f;
	else if (r->isC ())
	  return -0.5215f;
	else if (r->isG ())
	  return  0.1744f;
	else if (r->isU ())
	  return -0.3635f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AC6::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.6897f;
	else if (r->isT ())
	  return -0.2209f;
	else if (r->isG ())
	  return 0.4918f;
	else if (r->isC ())
	  return -0.0183f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.7009f;
	else if (r->isC ())
	  return 0.0053f;
	else if (r->isG ())
	  return 0.4770f;
	else if (r->isU ())
	  return -0.1126f;
      }
    return 0.f;
  }

  float
  AtomTypeStore::AC8::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1607f;
	else if (r->isG ())
	  return 0.0736f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.2006f;
	else if (r->isG ())
	  return 0.1374f;
      }
    return 0.f;
  }
  float
  AtomTypeStore::AH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.3520f;
    else if (r == ResidueType::rRG)
      return 0.3424f;
    return 0.f;
  }



  float
  AtomTypeStore::AH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.0598f;
    else if (r == ResidueType::rRA)
      return 0.0473f;
    return 0.f;
  }


  float
  AtomTypeStore::AH3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.3420f;
    else if (r == ResidueType::rRU)
      return 0.3154f;
    return 0.f;
  }



  float
  AtomTypeStore::AH5::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.1863f;
    else if (r == ResidueType::rRC)
      return 0.1928f;
    else if (r == ResidueType::rRU)
      return 0.1811f;
    return 0.f;
  }


  float
  AtomTypeStore::AH6::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isT ())
	  return 0.2607f;
	else if (r->isC ())
	  return 0.2293f;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return 0.1958f;
	else if (r->isU ())
	  return 0.2188f;
      }
    return 0.f;
  }
  float
  AtomTypeStore::AH8::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1877f;
	else if (r->isG ())
	  return 0.1997f;
      }
    else if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1553f;
	else if (r->isG ())
	  return 0.1640f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AN1::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7624f;
	else if (r->isT ())
	  return -0.0239f;
	else if (r->isG ())
	  return -0.5053f;
	else if (r->isC ())
	  return -0.0339f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.7615f;
	else if (r->isC ())
	  return -0.0484f;
	else if (r->isG ())
	  return -0.4787f;
	else if (r->isU ())
	  return 0.0418f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AN2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.9230f;
    else if (r == ResidueType::rRG)
      return -0.9672f;
    return 0.f;
  }


  float
  AtomTypeStore::AN3::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7417f;
	else if (r->isT ())
	  return -0.4340f;
	else if (r->isG ())
	  return -0.6636f;
	else if (r->isC ())
	  return -0.7748f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6997f;
	else if (r->isC ())
	  return -0.7584f;
	else if (r->isG ())
	  return -0.6323f;
	else if (r->isU ())
	  return -0.3549f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AN4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return -0.9773f;
    else if (r == ResidueType::rRC)
      return -0.9530f;
    return 0.f;
  }

  float
  AtomTypeStore::AN6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return -0.9123f;
    else if (r == ResidueType::rRA)
      return -0.9019f;
    return 0.f;
  }

  float
  AtomTypeStore::AN7::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.6175f;
	else if (r->isG ())
	  return -0.5725f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6073f;
	else if (r->isG ())
	  return -0.5709f;
      }
    return 0.f;
  }

  float
  AtomTypeStore::AN9::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.0268f;
	else if (r->isG ())
	  return 0.0577f;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.0251f;
	else if (r->isG ())
	  return  0.0492f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AO2::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isT ())
	  return -0.5881f;
	else if (r->isC ())
	  return -0.6548f;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return -0.6252f;
	else if (r->isU ())
	  return -0.5477f;
      }
    return 0.f;
  }


  float
  AtomTypeStore::AO4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return -0.5563f;
    else if (r == ResidueType::rRU)
      return -0.5761f;
    return 0.f;
  }


  float
  AtomTypeStore::AO6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.5699f;
    else if (r == ResidueType::rRG)
      return -0.5597f;
    return 0.f;
  }

  float
  AtomTypeStore::A1H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235f;
    else if (r == ResidueType::rRG)
      return 0.4364f;
    return 0.f;
  }


  float
  AtomTypeStore::A1H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314f;
    else if (r == ResidueType::rRC)    
      return 0.4234f;
    return 0.f;
  }


  float
  AtomTypeStore::A1H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770f;
    return 0.f;
  }


  float
  AtomTypeStore::A1H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167f;
    else if (r == ResidueType::rRA)
      return 0.4115f;
    return 0.f;
  }

  float
  AtomTypeStore::A2H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235f;
    else if (r == ResidueType::rRG)
      return 0.4364f;
    return 0.f;
  }


  float
  AtomTypeStore::A2H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314f;
    else if (r == ResidueType::rRC)    
      return 0.4234f;
    return 0.f;
  }


  float
  AtomTypeStore::A2H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770f;
    return 0.f;
  }


  float
  AtomTypeStore::A2H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167f;
    else if (r == ResidueType::rRA)
      return 0.4115f;
    return 0.f;
  }


  float
  AtomTypeStore::A3H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770f;
    return 0.f;
  }



  float
  AtomTypeStore::AH3T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4396f;
    else if (r->isRNA ())
      return 0.4376f;
    return 0.f;
  }

  float
  AtomTypeStore::AH5T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4422f;
    else if (r->isRNA ())
      return 0.4295f;
    return 0.f;
  }


  float
  AtomTypeStore::AC::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR       
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN       
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE       
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.59730f;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.73410f;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.53660f;
    else if (r == ResidueType::rPRO)
      return 0.58960f;
    return 0.f;
  }


  float
  AtomTypeStore::ACA::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.03370f;
    else if (r == ResidueType::rGLY)
      return -0.02520f;
    else if (r == ResidueType::rSER)
      return -0.02490f;
    else if (r == ResidueType::rTHR)
      return -0.03890f;
    else if (r == ResidueType::rLEU)
      return -0.05180f;
    else if (r == ResidueType::rILE)
      return -0.05970f;
    else if (r == ResidueType::rVAL)
      return -0.08750f;
    else if (r == ResidueType::rASN)
      return 0.01430f;
    else if (r == ResidueType::rGLN)
      return -0.00310f;
    else if (r == ResidueType::rARG)
      return -0.26370f;
    else if (r == ResidueType::rHIS)
      return 0.01880f;
    else if (r == ResidueType::rTRP)
      return -0.02750f;
    else if (r == ResidueType::rPHE)
      return -0.00240f;
    else if (r == ResidueType::rTYR)
      return -0.00140f;
    else if (r == ResidueType::rGLU)
      return 0.03970f;
    else if (r == ResidueType::rASP)
      return 0.03810f;
    else if (r == ResidueType::rLYS)
      return -0.24000f;
    else if (r == ResidueType::rPRO)
      return -0.02660f;
    else if (r == ResidueType::rCYS)
      return 0.02130f;
    else if (r == ResidueType::rMET)
      return -0.02370f;
    return 0.f;
  }


  float
  AtomTypeStore::ACB::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return -0.18250f;
    else if (r == ResidueType::rSER)
      return 0.21170f;
    else if (r == ResidueType::rTHR)
      return 0.36540f;
    else if (r == ResidueType::rLEU)
      return -0.11020f;
    else if (r == ResidueType::rILE)
      return 0.13030f;
    else if (r == ResidueType::rVAL)
      return 0.29850f;
    else if (r == ResidueType::rASN)
      return -0.20410f;
    else if (r == ResidueType::rGLN)
      return -0.00360f;
    else if (r == ResidueType::rARG)
      return -0.00070f;
    else if (r == ResidueType::rHIS)
      return -0.04620f;
    else if (r == ResidueType::rTRP)
      return -0.00500f;
    else if (r == ResidueType::rPHE)
      return -0.03430f;
    else if (r == ResidueType::rTYR)
      return -0.01520f;
    else if (r == ResidueType::rGLU)
      return 0.05600f;
    else if (r == ResidueType::rASP)
      return -0.03030f;
    else if (r == ResidueType::rLYS)
      return -0.00940f;
    else if (r == ResidueType::rPRO)
      return -0.00700f;
    else if (r == ResidueType::rCYS)
      return -0.12310f;
    else if (r == ResidueType::rMET)
      return 0.03420f;
    return 0.f;
  }


  float
  AtomTypeStore::ACD::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rGLN || t == ResidueType::rGLU ? 0.0860f : 0.1094f;
  }



  float
  AtomTypeStore::ACD::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.69510f;
    else if (r == ResidueType::rARG)
      return 0.04860f;
    else if (r == ResidueType::rGLU)
      return 0.80540f;
    else if (r == ResidueType::rLYS)
      return -0.04790f;
    else if (r == ResidueType::rPRO)
      return 0.01920f;
    return 0.f;
  }

  float
  AtomTypeStore::ACD1::getAmberEpsilon (const ResidueType *r) const
  {
    return (r == ResidueType::rPHE
	    || r == ResidueType::rTYR
	    || r == ResidueType::rTRP
	    ? 0.0860f : 0.1094f);
  }



  float
  AtomTypeStore::ACD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return -0.41210f;
    else if (r == ResidueType::rILE)
      return -0.06600f;
    else if (r == ResidueType::rTRP)
      return -0.16380f;
    else if (r == ResidueType::rPHE)
      return -0.12560f;
    else if (r == ResidueType::rTYR)
      return -0.19060f;
    return 0.f;
  }


  float
  AtomTypeStore::ACD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return -0.41210f;
    else if (r == ResidueType::rHIS)
      return 0.12920f;
    else if (r == ResidueType::rTRP)
      return 0.12430f;
    else if (r == ResidueType::rPHE)
      return -0.12560f;
    else if (r == ResidueType::rTYR)
      return -0.19060f;
    return 0.f;
  }


  float
  AtomTypeStore::ACE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.01430f;
    else if (r == ResidueType::rMET)
      return -0.05360f;
    return 0.f;
  }

  float
  AtomTypeStore::ACE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.20570f;
    else if (r == ResidueType::rPHE)
      return -0.17040f;
    else if (r == ResidueType::rTYR)
      return -0.23410f;
    return 0.f;
  }



  float
  AtomTypeStore::ACE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.13800f;
    else if (r == ResidueType::rPHE)
      return -0.17040f;
    else if (r == ResidueType::rTYR)
      return -0.23410f;
    return 0.f;
  }


  float
  AtomTypeStore::ACE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.23870f;
    return 0.f;
  }


  float
  AtomTypeStore::ACG::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return ((t == ResidueType::rASN || t == ResidueType::rHIS || t == ResidueType::rTRP
	     || t == ResidueType::rPHE || t == ResidueType::rTYR || t == ResidueType::rASP)
	    ? 0.0860f : 0.1094f);
  }



  float
  AtomTypeStore::ACG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.35310f;
    else if (r == ResidueType::rASN)
      return 0.71300f;
    else if (r == ResidueType::rGLN)
      return -0.06450f;
    else if (r == ResidueType::rARG)
      return 0.03900f;
    else if (r == ResidueType::rHIS)
      return -0.02660f;
    else if (r == ResidueType::rTRP)
      return -0.14150f;
    else if (r == ResidueType::rPHE)
      return 0.01180f;
    else if (r == ResidueType::rTYR)
      return -0.00110f;
    else if (r == ResidueType::rGLU)
      return 0.01360f;
    else if (r == ResidueType::rASP)
      return 0.79940f;
    else if (r == ResidueType::rLYS)
      return 0.01870f;
    else if (r == ResidueType::rPRO)
      return 0.01890f;
    else if (r == ResidueType::rMET)
      return 0.00180f;
    return 0.f;
  }



  float
  AtomTypeStore::ACG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return -0.04300f;
    else if (r == ResidueType::rVAL)
      return -0.31920f;
    return 0.f;
  }


  float
  AtomTypeStore::ACG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.24380f;
    else if (r == ResidueType::rILE)
      return -0.32040f;
    else if (r == ResidueType::rVAL)
      return -0.31920f;
    return 0.f;
  }


  float
  AtomTypeStore::ACH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.11340f;
    return 0.f;
  }


  float
  AtomTypeStore::ACZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.80760f;
    else if (r == ResidueType::rPHE)
      return -0.10720f;
    else if (r == ResidueType::rTYR)
      return 0.32260f;
    return 0.f;
  }


  float
  AtomTypeStore::ACZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.26010f;
    return 0.f;
  }


  float
  AtomTypeStore::ACZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.19720f;
    return 0.f;
  }


  float
  AtomTypeStore::AH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.27190f;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.27470f;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.29360f;
    return 0.f;
  }


  float
  AtomTypeStore::AHA::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.08230f;
    else if (r == ResidueType::rSER)
      return 0.08430f;
    else if (r == ResidueType::rTHR)
      return 0.10070f;
    else if (r == ResidueType::rLEU)
      return 0.09220f;
    else if (r == ResidueType::rILE)
      return 0.08690f;
    else if (r == ResidueType::rVAL)
      return 0.09690f;
    else if (r == ResidueType::rASN)
      return 0.10480f;
    else if (r == ResidueType::rGLN)
      return 0.08500f;
    else if (r == ResidueType::rARG)
      return 0.15600f;
    else if (r == ResidueType::rHIS)
      return 0.08810f;
    else if (r == ResidueType::rTRP)
      return 0.11230f;
    else if (r == ResidueType::rPHE)
      return 0.09780f;
    else if (r == ResidueType::rTYR)
      return 0.08760f;
    else if (r == ResidueType::rGLU)
      return 0.11050f;
    else if (r == ResidueType::rASP || r == ResidueType::rMET)
      return 0.08800f;
    else if (r == ResidueType::rLYS)
      return 0.14260f;
    else if (r == ResidueType::rPRO)
      return 0.06410f;
    else if (r == ResidueType::rCYS)
      return 0.11240f;
    return 0.f;
  }


  float
  AtomTypeStore::AHA1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980f;
    return 0.f;
  }


  float
  AtomTypeStore::AHA2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980f;
    return 0.f;
  }


  float
  AtomTypeStore::AHB::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.00430f;
    else if (r == ResidueType::rILE)
      return 0.01870f;
    else if (r == ResidueType::rVAL)
      return -0.02970f;
    return 0.f;
  }

  float
  AtomTypeStore::AHB1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030f;
    return 0.f;
  }



  float
  AtomTypeStore::AHB2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return (t == ResidueType::rSER || t == ResidueType::rCYS) ? 1.3870f : 1.4870f;
  }



  float
  AtomTypeStore::AHB2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030f;
    else if (r == ResidueType::rSER)
      return 0.03520f;
    else if (r == ResidueType::rLEU)
      return 0.04570f;
    else if (r == ResidueType::rASN)
      return 0.07970f;
    else if (r == ResidueType::rGLN)
      return 0.01710f;
    else if (r == ResidueType::rARG)
      return 0.03270f;
    else if (r == ResidueType::rHIS)
      return 0.04020f;
    else if (r == ResidueType::rTRP)
      return 0.03390f;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950f;
    else if (r == ResidueType::rGLU)
      return -0.01730f;
    else if (r == ResidueType::rASP)
      return -0.01220f;
    else if (r == ResidueType::rLYS)
      return 0.03620f;
    else if (r == ResidueType::rPRO)
      return 0.02530f;
    else if (r == ResidueType::rCYS)
      return 0.11120f;
    else if (r == ResidueType::rMET)
      return 0.02410f;
    return 0.f;
  }

  float
  AtomTypeStore::AHB3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rSER || t == ResidueType::rCYS ? 1.3870f : 1.4870f;
  }



  float
  AtomTypeStore::AHB3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030f;
    else if (r == ResidueType::rSER)
      return 0.03520f;
    else if (r == ResidueType::rLEU)
      return 0.04570f;
    else if (r == ResidueType::rASN)
      return 0.07970f;
    else if (r == ResidueType::rGLN)
      return 0.01710f;
    else if (r == ResidueType::rARG)
      return 0.03270f;
    else if (r == ResidueType::rHIS)
      return 0.04020f;
    else if (r == ResidueType::rTRP)
      return 0.03390f;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950f;
    else if (r == ResidueType::rGLU)
      return -0.01730f;
    else if (r == ResidueType::rASP)
      return -0.01220f;
    else if (r == ResidueType::rLYS)
      return 0.03620f;
    else if (r == ResidueType::rPRO)
      return 0.02530f;
    else if (r == ResidueType::rCYS)
      return 0.11120f;
    else if (r == ResidueType::rMET)
      return 0.02410f;
    return 0.f;
  }

  float
  AtomTypeStore::AHD1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000f;
    else if (t == ResidueType::rTRP)
      return 1.4090f;
    else
      return 1.4590f;
  }



  float
  AtomTypeStore::AHD1::getAmberEpsilon (const ResidueType *r) const
  {
    return r == ResidueType::rHIS ? 0.0157f : 0.0150f;
  }



  float
  AtomTypeStore::AHD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.36490f;
    else if (r == ResidueType::rTRP)
      return 0.20620f;
    else if (r == ResidueType::rPHE)
      return 0.13300f;
    else if (r == ResidueType::rTYR)
      return 0.16990f;
    return 0.f;
  }


  float
  AtomTypeStore::AHD2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO)
      return 1.3870f; // H1
    else if (t == ResidueType::rHIS)
      return 1.4090f; // H4
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590f; // HA
    else if (t == ResidueType::rLYS)
      return 1.4870f; // HC
    else
      return 0.0000f; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO || t == ResidueType::rLYS)
      return 0.0157f; // H1 HC
    else if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150f; // H4 HA
    else
      return 0.0000f; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.06870f;
    else if (r == ResidueType::rHIS)
      return 0.11470f;
    else if (r == ResidueType::rPHE)
      return 0.13300f;
    else if (r == ResidueType::rTYR)
      return 0.16990f;
    else if (r == ResidueType::rLYS)
      return 0.06210f;
    else if (r == ResidueType::rPRO)
      return 0.03910f;
    return 0.f;
  }

  float
  AtomTypeStore::AHE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.34560f;
    return 0.f;
  }



  float
  AtomTypeStore::AHE1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 1.3590f; // H5
    else if (t == ResidueType::rTRP)
      return 0.6000f; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590f; // HA
    else if (t == ResidueType::rMET)
      return 1.3870f; // H1
    return 0.f;
  }



  float
  AtomTypeStore::AHE1::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150f; // H5 HA
    else if (t == ResidueType::rTRP || t == ResidueType::rMET)
      return 0.0157f; // H H1
    return 0.f;
  }



  float
  AtomTypeStore::AHE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.13920f;
    else if (r == ResidueType::rTRP)
      return 0.34120f;
    else if (r == ResidueType::rPHE)
      return 0.14300f;
    else if (r == ResidueType::rTYR)
      return 0.16560f;
    else if (r == ResidueType::rMET)
      return 0.06940f;
    return 0.f;
  }

  float
  AtomTypeStore::AHE2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000f; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590f; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000f; // HP
    else if (t == ResidueType::rMET)
      return 1.3870f; // H1
    else if (t == ResidueType::rGLU)
      return 0.0000f;
    return 0.f;
  }



  float
  AtomTypeStore::AHE2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157f; // H HP H1
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150f; // HA
    else if (t == ResidueType::rGLU)
      return 0.0000f; // HO
    return 0.f;
  }



  float
  AtomTypeStore::AHE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rPHE)
      return 0.14300f;
    else if (r == ResidueType::rTYR)
      return 0.16560f;
    else if (r == ResidueType::rLYS)
      return 0.11350f;
    else if (r == ResidueType::rMET)
      return 0.06840f;
    return 0.f;
  }


  float
  AtomTypeStore::AHE3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590f; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000f; // HP
    else if (t == ResidueType::rMET)
      return 1.3870f; // H1
    return 0.f;
  }



  float
  AtomTypeStore::AHE3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157f; // HP H1
    else if (t == ResidueType::rTRP)
      return 0.0150f; // HA
    return 0.f;
  }



  float
  AtomTypeStore::AHE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.17000f;
    else if (r == ResidueType::rLYS)
      return 0.11350f;
    else if (r == ResidueType::rMET)
      return 0.06840f;
    return 0.f;
  }


  float
  AtomTypeStore::AHG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return 0.42750f;
    else if (r == ResidueType::rLEU)
      return -0.03610f;
    else if (r == ResidueType::rCYS)
      return 0.19330f;
    return 0.f;
  }


  float
  AtomTypeStore::AHG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.41020f;
    return 0.f;
  }


  float
  AtomTypeStore::AHG2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rGLN || t == ResidueType::rARG || t == ResidueType::rGLU || t == ResidueType::rLYS
	|| t == ResidueType::rPRO)
      return 1.4870f; // HC
    else if (t == ResidueType::rMET)
      return 1.3870f; // H1
    return 0.f;
  }



  float
  AtomTypeStore::AHG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.03520f;
    else if (r == ResidueType::rARG)
      return 0.02850f;
    else if (r == ResidueType::rGLU)
      return -0.04250f;
    else if (r == ResidueType::rLYS)
      return 0.01030f;
    else if (r == ResidueType::rPRO)
      return 0.02130f;
    else if (r == ResidueType::rMET)
      return 0.04400f;
    return 0.f;
  }

  float
  AtomTypeStore::AHH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return 0.39920f;
    return 0.f;
  }


  float
  AtomTypeStore::AHH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14170f;
    return 0.f;
  }


  float
  AtomTypeStore::AHZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rPHE)
      return 0.12970f;
    return 0.f;
  }


  float
  AtomTypeStore::AHZ1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return 0.34000f;
    return 0.f;
  }



  float
  AtomTypeStore::AHZ2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590f; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000f; // H
    return 0.f;
  }



  float
  AtomTypeStore::AHZ2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150f; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157f; // H
    return 0.f;
  }



  float
  AtomTypeStore::AHZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.15720f;
    else if (r== ResidueType::rLYS)
      return 0.34000f;
    return 0.f;
  }

  float
  AtomTypeStore::AHZ3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
    
    if (t == ResidueType::rTRP)
      return 1.4590f; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000f; // H
    return 0.f;
  }



  float
  AtomTypeStore::AHZ3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150f; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157f; // H
    return 0.f;
  }



  float
  AtomTypeStore::AHZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14470f;
    else if (r == ResidueType::rLYS)
      return 0.34000f;
    return 0.f;
  }


  float
  AtomTypeStore::AN::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.41570f;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.34790f;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.51630f;
    else if (r == ResidueType::rPRO)
      return -0.25480f;
    return 0.f;
  }


  float
  AtomTypeStore::AND1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return -0.38110f;
    return 0.f;
  }


  float
  AtomTypeStore::AND2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.91910f;
    return 0.f;
  }


  float
  AtomTypeStore::ANE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.52950f;
    return 0.f;
  }


  float
  AtomTypeStore::ANE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.34180f;
    return 0.f;
  }


  float
  AtomTypeStore::ANE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.94070f;
    else if (r == ResidueType::rHIS)
      return -0.57270f;
    return 0.f;
  }

  float
  AtomTypeStore::ANH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270f;
    return 0.f;
  }


  float
  AtomTypeStore::ANH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270f;
    return 0.f;
  }


  float
  AtomTypeStore::ANZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.38540f;
    return 0.f;
  }


  float
  AtomTypeStore::AO::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.56790f;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.58940f;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.58190f;
    else if (r == ResidueType::rPRO)
      return -0.57480f;
    return 0.f;
  }

  float
  AtomTypeStore::AOD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.59310f;
    else if (r == ResidueType::rASP)
      return -0.80140f;
    return 0.f;
  }


  float
  AtomTypeStore::AOD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASP)
      return -0.80140f;
    return 0.f;
  }


  float
  AtomTypeStore::AOE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.60860f;
    else if (r == ResidueType::rGLU)
      return -0.81880f;
    return 0.f;
  }


  float
  AtomTypeStore::AOE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLU)
      return -0.81880f;
    return 0.f;
  }


  float
  AtomTypeStore::AOG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return -0.65460f;
    return 0.f;
  }

  float
  AtomTypeStore::AOG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.67610f;
    return 0.f;
  }


  float
  AtomTypeStore::AOH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return -0.55790f;
    return 0.f;
  }

  float
  AtomTypeStore::ASD::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rMET)
      return -0.27370f;
    return 0.f;
  }


  float
  AtomTypeStore::ASG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rCYS)
      return -0.31190f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    else if (r == ResidueType::rILE)
      return 0.01860f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    else if (r == ResidueType::rASN)
      return 0.41960f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420f;
    else if (r == ResidueType::rILE)
      return 0.08820f;
    else if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780f;
    return 0.f;
  }


  float
  AtomTypeStore::A1HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780f;
    return 0.f;
  }

  float
  AtomTypeStore::A2HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    else if (r == ResidueType::rILE)
      return 0.01860f;
    return 0.f;
  }


  float
  AtomTypeStore::A2HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    else if (r == ResidueType::rASN)
      return 0.41960f;
    return 0.f;
  }


  float
  AtomTypeStore::A2HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510f;
    return 0.f;
  }


  float
  AtomTypeStore::A2HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360f;
    else if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }

  float
  AtomTypeStore::A2HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420f;
    else if (r == ResidueType::rILE)
      return 0.08820f;
    else if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }


  float
  AtomTypeStore::A2HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780f;
    return 0.f;
  }


  float
  AtomTypeStore::A2HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780f;
    return 0.f;
  }

  float
  AtomTypeStore::A3HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    else if (r == ResidueType::rILE)
      return 0.01860f;
    return 0.f;
  }



  float
  AtomTypeStore::A3HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000f;
    return 0.f;
  }


  float
  AtomTypeStore::A3HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360f;
    else if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }

  float
  AtomTypeStore::A3HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420f;
    else if (r == ResidueType::rILE)
      return 0.08820f;
    else if (r == ResidueType::rVAL)
      return 0.07910f;
    return 0.f;
  }


}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
