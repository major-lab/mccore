//                              -*- Mode: C++ -*- 
// ResidueType.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:32:49 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ResidueType.h"
#include "ResidueTypeStore.h"
#include "Binstream.h"
#include "Exception.h"


namespace mccore
{

  // STATIC MEMBERS ------------------------------------------------------------

  ResidueTypeStore ResidueType::rtstore;

  ResidueType* ResidueType::rNull = 0;
  
  ResidueType* ResidueType::rNucleicAcid = 0;
  ResidueType* ResidueType::rAminoAcid = 0;

  ResidueType* ResidueType::rRNA = 0;
  ResidueType* ResidueType::rDNA = 0;
  ResidueType* ResidueType::rPhosphate = 0;
  ResidueType* ResidueType::rRRibose = 0;
  ResidueType* ResidueType::rDRibose = 0;
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

  
  // LIFECYCLE -----------------------------------------------------------------


  ResidueType::ResidueType () 
    : type (0), longtype (0) 
  {
  }


  ResidueType::ResidueType (const char* t, const char* lt) 
  {
    type = new char[strlen (t) + 1];
    strcpy (type, t);
    longtype = new char[strlen (lt) + 1];
    strcpy (longtype, lt);
  }

  ResidueType::ResidueType (const ResidueType &t) 
  {
  }
  
  ResidueType::~ResidueType () 
  {
    if (type) delete[] type;
    if (longtype) delete[] longtype;
  }
 

  // METHODS -------------------------------------------------------------------


  const ResidueType* 
  ResidueType::parseType (const char* s) 
  {
    return rtstore.get (s);
  }

  const ResidueType* 
  ResidueType::invalidate () const
  {
    return ResidueType::rtstore.getInvalid (longtype);
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
    return out << longtype;
  }
  

  oBinstream &
  ResidueType::output (oBinstream &out) const
  {
    return out << longtype;
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
    return ex << t.toLongString ();
  }

  
  Exception&
  operator<< (Exception& ex, const ResidueType *t)
  {
    return ex << (0 == t ? ResidueType::rNull : t)->toLongString ();
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const ResidueType *t)
  {
    if (0 == t)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Cannot write null-pointed residue type to binstream: use ResidueType::rNull";
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
