//                              -*- Mode: C++ -*- 
// AtomType.cc
// Copyright © 2003-07 Laboratoire de Biologie Informatique et Théorique
//                     Univesité de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 15:00:09 2003
// $Revision: 1.23 $
// $Id: AtomType.cc,v 1.23 2007-01-14 18:21:02 larosem Exp $
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

#include "AtomType.h"
#include "AtomTypeStore.h"
#include "Exception.h"
#include "Binstream.h"



namespace mccore
{
  std::unique_ptr<AtomTypeStore> AtomType::atstore(new AtomTypeStore());
  const AtomType* AtomType::aNull = 0;
  const AtomType* AtomType::aUnknown = 0;
  const AtomType* AtomType::aC1p = 0;
  const AtomType* AtomType::aC2p = 0;
  const AtomType* AtomType::aC3p = 0;
  const AtomType* AtomType::aC4p = 0;
  const AtomType* AtomType::aC5p = 0;
  const AtomType* AtomType::aH1p = 0;
  const AtomType* AtomType::aH2p = 0;
  const AtomType* AtomType::aH3p = 0;
  const AtomType* AtomType::aH4p = 0;
  const AtomType* AtomType::aH5p = 0;
  const AtomType* AtomType::aO1P = 0;
  const AtomType* AtomType::aO2p = 0;
  const AtomType* AtomType::aO2P = 0;
  const AtomType* AtomType::aO3p = 0;
  const AtomType* AtomType::aO3P = 0;
  const AtomType* AtomType::aO4p = 0;
  const AtomType* AtomType::aO5p = 0;
  const AtomType* AtomType::aP = 0;
  const AtomType* AtomType::a1H2p = 0;
  const AtomType* AtomType::a1H5p = 0;
  const AtomType* AtomType::a2H2p = 0;
  const AtomType* AtomType::a2H5p = 0;
  const AtomType* AtomType::aHO2p = 0;
  const AtomType* AtomType::aHO3p = 0;
  const AtomType* AtomType::aC2 = 0;
  const AtomType* AtomType::aC4 = 0;
  const AtomType* AtomType::aC5 = 0;
  const AtomType* AtomType::aC5M = 0;
  const AtomType* AtomType::aC6 = 0;
  const AtomType* AtomType::aC8 = 0;
  const AtomType* AtomType::aH1 = 0;
  const AtomType* AtomType::aH2 = 0;
  const AtomType* AtomType::aH3 = 0;
  const AtomType* AtomType::aH5 = 0;
  const AtomType* AtomType::aH6 = 0;
  const AtomType* AtomType::aH7 = 0;
  const AtomType* AtomType::aH8 = 0;
  const AtomType* AtomType::aN1 = 0;
  const AtomType* AtomType::aN2 = 0;
  const AtomType* AtomType::aN3 = 0;
  const AtomType* AtomType::aN4 = 0;
  const AtomType* AtomType::aN6 = 0;
  const AtomType* AtomType::aN7 = 0;
  const AtomType* AtomType::aN9 = 0;
  const AtomType* AtomType::aO2 = 0;
  const AtomType* AtomType::aO4 = 0;
  const AtomType* AtomType::aO6 = 0;
  const AtomType* AtomType::a1H2 = 0;
  const AtomType* AtomType::a1H4 = 0;
  const AtomType* AtomType::a1H5M = 0;
  const AtomType* AtomType::a1H6 = 0;
  const AtomType* AtomType::a2H2 = 0;
  const AtomType* AtomType::a2H4 = 0;
  const AtomType* AtomType::a2H5M = 0;
  const AtomType* AtomType::a2H6 = 0;
  const AtomType* AtomType::a3H5M = 0;
  const AtomType* AtomType::aPSX = 0;
  const AtomType* AtomType::aPSY = 0;
  const AtomType* AtomType::aPSZ = 0;
  const AtomType* AtomType::aPSO = 0;
  const AtomType* AtomType::aLP1 = 0;
  const AtomType* AtomType::aLP3 = 0;
  const AtomType* AtomType::aLP7 = 0;
  const AtomType* AtomType::a1LP2 = 0;
  const AtomType* AtomType::a1LP4 = 0;
  const AtomType* AtomType::a1LP6 = 0;
  const AtomType* AtomType::a2LP2 = 0;
  const AtomType* AtomType::a2LP4 = 0;
  const AtomType* AtomType::a2LP6 = 0;
  const AtomType* AtomType::aH3T = 0;
  const AtomType* AtomType::aH5T = 0;
  const AtomType* AtomType::aC = 0;
  const AtomType* AtomType::aCA = 0;
  const AtomType* AtomType::aCB = 0;
  const AtomType* AtomType::aCD = 0;
  const AtomType* AtomType::aCD1 = 0;
  const AtomType* AtomType::aCD2 = 0;
  const AtomType* AtomType::aCE = 0;
  const AtomType* AtomType::aCE1 = 0;
  const AtomType* AtomType::aCE2 = 0;
  const AtomType* AtomType::aCE3 = 0;
  const AtomType* AtomType::aCG = 0;
  const AtomType* AtomType::aCG1 = 0;
  const AtomType* AtomType::aCG2 = 0;
  const AtomType* AtomType::aCH2 = 0;
  const AtomType* AtomType::aCZ = 0;
  const AtomType* AtomType::aCZ2 = 0;
  const AtomType* AtomType::aCZ3 = 0;
  const AtomType* AtomType::aH = 0;
  const AtomType* AtomType::a1H = 0;
  const AtomType* AtomType::a2H = 0;
  const AtomType* AtomType::a3H = 0;
  const AtomType* AtomType::aHA = 0;
  const AtomType* AtomType::aHA1 = 0;
  const AtomType* AtomType::aHA2 = 0;
  const AtomType* AtomType::aHB = 0;
  const AtomType* AtomType::aHB1 = 0;
  const AtomType* AtomType::aHB2 = 0;
  const AtomType* AtomType::aHB3 = 0;
  const AtomType* AtomType::aHD1 = 0;
  const AtomType* AtomType::aHD2 = 0;
  const AtomType* AtomType::aHE = 0;
  const AtomType* AtomType::aHE1 = 0;
  const AtomType* AtomType::aHE2 = 0;
  const AtomType* AtomType::aHE3 = 0;
  const AtomType* AtomType::aHG = 0;
  const AtomType* AtomType::aHG1 = 0;
  const AtomType* AtomType::aHG2 = 0;
  const AtomType* AtomType::aHH = 0;
  const AtomType* AtomType::aHH2 = 0;
  const AtomType* AtomType::aHXT = 0;
  const AtomType* AtomType::aHZ = 0;
  const AtomType* AtomType::aHZ1 = 0;
  const AtomType* AtomType::aHZ2 = 0;
  const AtomType* AtomType::aHZ3 = 0;
  const AtomType* AtomType::aN = 0;
  const AtomType* AtomType::aND1 = 0;
  const AtomType* AtomType::aND2 = 0;
  const AtomType* AtomType::aNE = 0;
  const AtomType* AtomType::aNE1 = 0;
  const AtomType* AtomType::aNE2 = 0;
  const AtomType* AtomType::aNH1 = 0;
  const AtomType* AtomType::aNH2 = 0;
  const AtomType* AtomType::aNZ = 0;
  const AtomType* AtomType::aO = 0;
  const AtomType* AtomType::aOD1 = 0;
  const AtomType* AtomType::aOD2 = 0;
  const AtomType* AtomType::aOE1 = 0;
  const AtomType* AtomType::aOE2 = 0;
  const AtomType* AtomType::aOG = 0;
  const AtomType* AtomType::aOG1 = 0;
  const AtomType* AtomType::aOH = 0;
  const AtomType* AtomType::aOXT = 0;
  const AtomType* AtomType::aSD = 0;
  const AtomType* AtomType::aSG = 0;
  const AtomType* AtomType::a1HD1 = 0;
  const AtomType* AtomType::a1HD2 = 0;
  const AtomType* AtomType::a1HE2 = 0;
  const AtomType* AtomType::a1HG1 = 0;
  const AtomType* AtomType::a1HG2 = 0;
  const AtomType* AtomType::a1HH1 = 0;
  const AtomType* AtomType::a1HH2 = 0;
  const AtomType* AtomType::a2HD1 = 0;
  const AtomType* AtomType::a2HD2 = 0;
  const AtomType* AtomType::a2HE2 = 0;
  const AtomType* AtomType::a2HG1 = 0;
  const AtomType* AtomType::a2HG2 = 0;
  const AtomType* AtomType::a2HH1 = 0;
  const AtomType* AtomType::a2HH2 = 0;
  const AtomType* AtomType::a3HD1 = 0;
  const AtomType* AtomType::a3HD2 = 0;
  const AtomType* AtomType::a3HG1 = 0;
  const AtomType* AtomType::a3HG2 = 0;
  const AtomType* AtomType::aMG = 0;
  const AtomType* AtomType::aPSAZ = 0;

    // New AtomType (some are invalid type names due to their notation in
    // the components.cif.gz file
    //
  const AtomType* AtomType::a1HM1 = 0;
  const AtomType* AtomType::a1HN6 = 0;
  const AtomType* AtomType::a2HM1 = 0;
  const AtomType* AtomType::a2HN6 = 0;
  const AtomType* AtomType::a3HM1 = 0;
  const AtomType* AtomType::aCM1 = 0;

  
  AtomType::AtomType (const AtomType &other)
  {
    FatalIntLibException ex ("", __FILE__, __LINE__);
    ex << "Use of copy constructor for class AtomType is prohibited.";
    throw ex;
  }


  const AtomType* 
  AtomType::parseType (const char* str) 
  {
    string sk (str);
    return atstore->get (sk);
  }


  const AtomType* 
  AtomType::parseType (const string& str)  
  {
    return atstore->get (str);
  }

  void AtomType::AddMapping(const std::string& key, const AtomType* apType)
  {
	  atstore->addMapping(key, apType);
  }

  
  // I/O -----------------------------------------------------------------------

  ostream &
  AtomType::output (ostream &out) const
  {
    return out << key;
  }
  

  oBinstream &
  AtomType::output (oBinstream &out) const
  {
    return out << key;
  }


  Exception&
  operator<< (Exception& ex, const AtomType &t)
  {
    return ex << (const char*)t;
  }

  
  Exception&
  operator<< (Exception& ex, const AtomType *t)
  {
    return ex << (const char*)*(0 == t ? AtomType::aNull : t);
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const AtomType *t)
  {
    if (0 == t)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Cannot write null-pointed atom type to binstream: use AtomType::aNull";
      throw ex;
    }
    return t->output (obs);
  }
 

  iBinstream&
  operator>> (iBinstream &ibs, const AtomType *&t)
  {
    char* str;
    ibs >> &str;
    t = AtomType::parseType (str);
    delete[] str;
    return ibs;
  }

}



namespace std
{

  ostream &
  operator<< (ostream &out, const mccore::AtomType &a)
  {
    return a.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const mccore::AtomType* a)
  {
    return (0 == a ? mccore::AtomType::aNull : a)->output (out);
  }

}
