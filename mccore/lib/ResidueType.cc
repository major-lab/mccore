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

#include "ResidueType.h"
#include "ResidueTypeStore.h"
#include "Binstream.h"
#include "Exception.h"


namespace mccore
{

  ResidueTypeStore* ResidueType::rtstore = new ResidueTypeStore ();

  ResidueType* ResidueType::rNull = 0;
  ResidueType* ResidueType::rUnknown = 0;
  
  ResidueType* ResidueType::rNucleicAcid = 0;
  ResidueType* ResidueType::rAminoAcid = 0;
  
  ResidueType* ResidueType::rRNA = 0;
  ResidueType* ResidueType::rDNA = 0;
  
  ResidueType* ResidueType::rPhosphate = 0;
  
  ResidueType* ResidueType::rRRibose = 0;
  ResidueType* ResidueType::rRRibose5 = 0;
  ResidueType* ResidueType::rRRibose3 = 0;
  ResidueType* ResidueType::rRRibose53 = 0;
  ResidueType* ResidueType::rDRibose = 0;
  ResidueType* ResidueType::rDRibose5 = 0;
  ResidueType* ResidueType::rDRibose3 = 0;
  ResidueType* ResidueType::rDRibose53 = 0;
  
  ResidueType* ResidueType::rPurine = 0;
  ResidueType* ResidueType::rPyrimidine = 0;
  ResidueType* ResidueType::rRPurine = 0;
  ResidueType* ResidueType::rRPyrimidine = 0;
  ResidueType* ResidueType::rDPurine = 0;
  ResidueType* ResidueType::rDPyrimidine = 0;
  
  ResidueType* ResidueType::rW = 0;
  ResidueType* ResidueType::rS = 0;
  ResidueType* ResidueType::rM = 0;
  ResidueType* ResidueType::rK = 0;
  ResidueType* ResidueType::rB = 0;
  ResidueType* ResidueType::rD = 0;
  ResidueType* ResidueType::rH = 0;
  ResidueType* ResidueType::rV = 0;
  
  ResidueType* ResidueType::rRW = 0;
  ResidueType* ResidueType::rRS = 0;
  ResidueType* ResidueType::rRM = 0;
  ResidueType* ResidueType::rRK = 0;
  ResidueType* ResidueType::rRB = 0;
  ResidueType* ResidueType::rRD = 0;
  ResidueType* ResidueType::rRH = 0;
  ResidueType* ResidueType::rRV = 0;
  
  ResidueType* ResidueType::rDW = 0;
  ResidueType* ResidueType::rDS = 0;
  ResidueType* ResidueType::rDM = 0;
  ResidueType* ResidueType::rDK = 0;
  ResidueType* ResidueType::rDB = 0;
  ResidueType* ResidueType::rDD = 0;
  ResidueType* ResidueType::rDH = 0;
  ResidueType* ResidueType::rDV = 0;
  
  ResidueType* ResidueType::rA = 0;
  ResidueType* ResidueType::rC = 0;
  ResidueType* ResidueType::rG = 0;
  ResidueType* ResidueType::rU = 0;
  ResidueType* ResidueType::rT = 0;
  ResidueType* ResidueType::rRA = 0;
  ResidueType* ResidueType::rRC = 0;
  ResidueType* ResidueType::rRG = 0;
  ResidueType* ResidueType::rRU = 0;
  ResidueType* ResidueType::rDA = 0;
  ResidueType* ResidueType::rDC = 0;
  ResidueType* ResidueType::rDG = 0;
  ResidueType* ResidueType::rDT = 0;
  
  ResidueType* ResidueType::rALA = 0;
  ResidueType* ResidueType::rARG = 0;
  ResidueType* ResidueType::rASN = 0;
  ResidueType* ResidueType::rASP = 0;
  ResidueType* ResidueType::rCYS = 0;
  ResidueType* ResidueType::rGLN = 0;
  ResidueType* ResidueType::rGLU = 0;
  ResidueType* ResidueType::rGLY = 0;
  ResidueType* ResidueType::rHIS = 0;
  ResidueType* ResidueType::rILE = 0;
  ResidueType* ResidueType::rLEU = 0;
  ResidueType* ResidueType::rLYS = 0;
  ResidueType* ResidueType::rMET = 0;
  ResidueType* ResidueType::rPHE = 0;
  ResidueType* ResidueType::rPRO = 0;
  ResidueType* ResidueType::rSER = 0;
  ResidueType* ResidueType::rTHR = 0;
  ResidueType* ResidueType::rTRP = 0;
  ResidueType* ResidueType::rTYR = 0;
  ResidueType* ResidueType::rVAL = 0;
  ResidueType* ResidueType::rASX = 0;
  ResidueType* ResidueType::rGLX = 0;


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


  ostream &
  operator<< (ostream &out, const ResidueType &t)
  {
    return t.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const ResidueType *t)
  {
    return (0 == t ? ResidueType::rNull : t)->output (out);
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
