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


namespace mccore {

  // STATIC MEMBERS ------------------------------------------------------------

  ResidueTypeStore ResidueType::rtstore;
  ResidueType* ResidueType::rNucleicAcid;
  ResidueType* ResidueType::rAminoAcid;

  ResidueType* ResidueType::rRNA;
  ResidueType* ResidueType::rDNA;
  ResidueType* ResidueType::rPhosphate;
  ResidueType* ResidueType::rPurine;
  ResidueType* ResidueType::rPyrimidine;
  ResidueType* ResidueType::rRPurine;
  ResidueType* ResidueType::rRPyrimidine;
  ResidueType* ResidueType::rDPurine;
  ResidueType* ResidueType::rDPyrimidine;

  ResidueType* ResidueType::rW;
  ResidueType* ResidueType::rS;
  ResidueType* ResidueType::rM;
  ResidueType* ResidueType::rK;
  ResidueType* ResidueType::rB;
  ResidueType* ResidueType::rD;
  ResidueType* ResidueType::rH;
  ResidueType* ResidueType::rV;

  ResidueType* ResidueType::rRW;
  ResidueType* ResidueType::rRS;
  ResidueType* ResidueType::rRM;
  ResidueType* ResidueType::rRK;
  ResidueType* ResidueType::rRB;
  ResidueType* ResidueType::rRD;
  ResidueType* ResidueType::rRH;
  ResidueType* ResidueType::rRV;

  ResidueType* ResidueType::rDW;
  ResidueType* ResidueType::rDS;
  ResidueType* ResidueType::rDM;
  ResidueType* ResidueType::rDK;
  ResidueType* ResidueType::rDB;
  ResidueType* ResidueType::rDD;
  ResidueType* ResidueType::rDH;
  ResidueType* ResidueType::rDV;

  ResidueType* ResidueType::rA;
  ResidueType* ResidueType::rC;
  ResidueType* ResidueType::rG;
  ResidueType* ResidueType::rU;
  ResidueType* ResidueType::rT;
  ResidueType* ResidueType::rRA;
  ResidueType* ResidueType::rRC;
  ResidueType* ResidueType::rRG;
  ResidueType* ResidueType::rRU;
  ResidueType* ResidueType::rDA;
  ResidueType* ResidueType::rDC;
  ResidueType* ResidueType::rDG;
  ResidueType* ResidueType::rDT;

  ResidueType* ResidueType::rALA;
  ResidueType* ResidueType::rARG;
  ResidueType* ResidueType::rASN;
  ResidueType* ResidueType::rASP;
  ResidueType* ResidueType::rCYS;
  ResidueType* ResidueType::rGLN;
  ResidueType* ResidueType::rGLU;
  ResidueType* ResidueType::rGLY;
  ResidueType* ResidueType::rHIS;
  ResidueType* ResidueType::rILE;
  ResidueType* ResidueType::rLEU;
  ResidueType* ResidueType::rLYS;
  ResidueType* ResidueType::rMET;
  ResidueType* ResidueType::rPHE;
  ResidueType* ResidueType::rPRO;
  ResidueType* ResidueType::rSER;
  ResidueType* ResidueType::rTHR;
  ResidueType* ResidueType::rTRP;
  ResidueType* ResidueType::rTYR;
  ResidueType* ResidueType::rVAL;

  
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
    if (!t) out << "null";
    else t->output (out);
    return out;
  }


  oBinstream&
  operator<< (oBinstream &obs, const ResidueType *t)
  {
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
