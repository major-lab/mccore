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


  ResidueType* 
  ResidueType::parseType (const char* s) 
  {
    return rtstore.get (s);
  }


  // I/O -----------------------------------------------------------------------


  ostream &
  ResidueType::output (ostream &out) const
  {
    return out << type;
  }
  

  oBinstream &
  ResidueType::output (oBinstream &out) const
  {
    return out << type;
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
