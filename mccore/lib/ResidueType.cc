//                              -*- Mode: C++ -*- 
// ResidueType.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:32:49 2003
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

#include "Binstream.h"
#include "Exception.h"
#include "ResidueType.h"
#include "ResidueTypeStore.h"



namespace mccore
{

  ResidueTypeStore* ResidueType::rtstore = new ResidueTypeStore ();

  const ResidueType* ResidueType::rNull = 0;
  const ResidueType* ResidueType::rUnknown = 0;
  
  const ResidueType* ResidueType::rNucleicAcid = 0;
  const ResidueType* ResidueType::rAminoAcid = 0;
  
  const ResidueType* ResidueType::rRNA = 0;
  const ResidueType* ResidueType::rDNA = 0;
  
  const ResidueType* ResidueType::rPhosphate = 0;
  
  const ResidueType* ResidueType::rRRibose = 0;
  const ResidueType* ResidueType::rRRibose5 = 0;
  const ResidueType* ResidueType::rRRibose3 = 0;
  const ResidueType* ResidueType::rRRibose53 = 0;
  const ResidueType* ResidueType::rDRibose = 0;
  const ResidueType* ResidueType::rDRibose5 = 0;
  const ResidueType* ResidueType::rDRibose3 = 0;
  const ResidueType* ResidueType::rDRibose53 = 0;
  
  const ResidueType* ResidueType::rPurine = 0;
  const ResidueType* ResidueType::rPyrimidine = 0;
  const ResidueType* ResidueType::rRPurine = 0;
  const ResidueType* ResidueType::rRPyrimidine = 0;
  const ResidueType* ResidueType::rDPurine = 0;
  const ResidueType* ResidueType::rDPyrimidine = 0;
  
  const ResidueType* ResidueType::rW = 0;
  const ResidueType* ResidueType::rS = 0;
  const ResidueType* ResidueType::rM = 0;
  const ResidueType* ResidueType::rK = 0;
  const ResidueType* ResidueType::rB = 0;
  const ResidueType* ResidueType::rD = 0;
  const ResidueType* ResidueType::rH = 0;
  const ResidueType* ResidueType::rV = 0;
  
  const ResidueType* ResidueType::rRW = 0;
  const ResidueType* ResidueType::rRS = 0;
  const ResidueType* ResidueType::rRM = 0;
  const ResidueType* ResidueType::rRK = 0;
  const ResidueType* ResidueType::rRB = 0;
  const ResidueType* ResidueType::rRD = 0;
  const ResidueType* ResidueType::rRH = 0;
  const ResidueType* ResidueType::rRV = 0;
  
  const ResidueType* ResidueType::rDW = 0;
  const ResidueType* ResidueType::rDS = 0;
  const ResidueType* ResidueType::rDM = 0;
  const ResidueType* ResidueType::rDK = 0;
  const ResidueType* ResidueType::rDB = 0;
  const ResidueType* ResidueType::rDD = 0;
  const ResidueType* ResidueType::rDH = 0;
  const ResidueType* ResidueType::rDV = 0;
  
  const ResidueType* ResidueType::rA = 0;
  const ResidueType* ResidueType::rC = 0;
  const ResidueType* ResidueType::rG = 0;
  const ResidueType* ResidueType::rU = 0;
  const ResidueType* ResidueType::rT = 0;
  const ResidueType* ResidueType::rRA = 0;
  const ResidueType* ResidueType::rRC = 0;
  const ResidueType* ResidueType::rRG = 0;
  const ResidueType* ResidueType::rRU = 0;
  const ResidueType* ResidueType::rDA = 0;
  const ResidueType* ResidueType::rDC = 0;
  const ResidueType* ResidueType::rDG = 0;
  const ResidueType* ResidueType::rDT = 0;
  
  const ResidueType* ResidueType::rALA = 0;
  const ResidueType* ResidueType::rARG = 0;
  const ResidueType* ResidueType::rASN = 0;
  const ResidueType* ResidueType::rASP = 0;
  const ResidueType* ResidueType::rCYS = 0;
  const ResidueType* ResidueType::rGLN = 0;
  const ResidueType* ResidueType::rGLU = 0;
  const ResidueType* ResidueType::rGLY = 0;
  const ResidueType* ResidueType::rHIS = 0;
  const ResidueType* ResidueType::rILE = 0;
  const ResidueType* ResidueType::rLEU = 0;
  const ResidueType* ResidueType::rLYS = 0;
  const ResidueType* ResidueType::rMET = 0;
  const ResidueType* ResidueType::rPHE = 0;
  const ResidueType* ResidueType::rPRO = 0;
  const ResidueType* ResidueType::rSER = 0;
  const ResidueType* ResidueType::rTHR = 0;
  const ResidueType* ResidueType::rTRP = 0;
  const ResidueType* ResidueType::rTYR = 0;
  const ResidueType* ResidueType::rVAL = 0;
  const ResidueType* ResidueType::rASX = 0;
  const ResidueType* ResidueType::rGLX = 0;


  ResidueType::ResidueType (const ResidueType &t) 
  {
    FatalIntLibException ex ("", __FILE__, __LINE__);
    ex << "Use of copy constructor for class ResidueType is prohibited.";
    throw ex;
  }


  const ResidueType* 
  ResidueType::parseType (const char* str) 
  {
    return ResidueType::rtstore->get (string (str));
  }


  const ResidueType* 
  ResidueType::parseType (const string& str) 
  {
    return ResidueType::rtstore->get (str);
  }
  

  const ResidueType* 
  ResidueType::invalidate () const
  {
    return ResidueType::rtstore->getInvalid (this);
  }
  

  const ResidueType* 
  ResidueType::generalizeBase (const ResidueType *aResType1, const ResidueType *aResType2)
  {
    if (aResType1 == aResType2)
      return aResType1;
    
    if (aResType1->isRNA () && aResType2->isRNA ()) {
      if ((aResType1->isPurine() && aResType2->isPyrimidine())
	  || (aResType1->isPyrimidine() && aResType2->isPurine()))
	return rRNA;
      if (aResType1->isPurine() && aResType2->isPurine())
	return rRPurine;
      if (aResType1->isPyrimidine() && aResType2->isPyrimidine())
	return rRPyrimidine;
      return rRNA;
    }
    
    if (aResType1->isDNA () && aResType2->isDNA ()) {
      if ((aResType1->isPurine() && aResType2->isPyrimidine())
	  || (aResType1->isPyrimidine() && aResType2->isPurine()))
	return rDNA;
      if (aResType1->isPurine() && aResType2->isPurine())
	return rDPurine;
      if (aResType1->isPyrimidine() && aResType2->isPyrimidine())
	return rDPyrimidine;
      return rDNA;
    }
    
    if (aResType1->isNucleicAcid () && aResType2->isNucleicAcid ()) {
      if (aResType1->isA () && aResType2->isA ())
	return rA;
      if (aResType1->isC () && aResType2->isC ())
	return rC;
      if (aResType1->isG () && aResType2->isG ())
	return rG;
      if (aResType1->isU () && aResType2->isU ())
	return rU;
      if (aResType1->isT () && aResType2->isT ())
	return rT;
      if ((aResType1->isPurine() && aResType2->isPyrimidine())
	  || (aResType1->isPyrimidine() && aResType2->isPurine()))
	return rNucleicAcid;
      if (aResType1->isPurine() && aResType2->isPurine())
	return rPurine;
      if (aResType1->isPyrimidine() && aResType2->isPyrimidine())
	return rPyrimidine;
      return rNucleicAcid;
    }
    
    if (aResType1->isAminoAcid() && aResType2->isAminoAcid()) {
      return rAminoAcid;
    }
    
    return 0;
  }
  

  // I/O -----------------------------------------------------------------------


  ostream &
  ResidueType::output (ostream &out) const
  {
    return out << this->key.c_str ();
  }
  

  oBinstream &
  ResidueType::output (oBinstream &out) const
  {
    return out << this->key.c_str ();
  }


  Exception&
  operator<< (Exception& ex, const ResidueType &t)
  {
    return ex << (const char*)t;
  }

  
  Exception&
  operator<< (Exception& ex, const ResidueType *t)
  {
    return ex << (const char*)*(0 == t ? ResidueType::rNull : t);
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const ResidueType *t)
  {
    if (0 == t)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Cannot write null-pointed residue type to binstream: use PropertyType::rNull";
      throw ex;
    }
    return t->output (obs);
  }
 

  iBinstream&
  operator>> (iBinstream &ibs, const ResidueType *&t)
  {
    char* str;
    ibs >> &str;
    t = ResidueType::parseType (str);
    delete[] str;
    return ibs;
  }

}



namespace std
{
  
  ostream &
  operator<< (ostream &out, const mccore::ResidueType &t)
  {
    return t.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const mccore::ResidueType *t)
  {
    return (0 == t ? mccore::ResidueType::rNull : t)->output (out);
  }

}

