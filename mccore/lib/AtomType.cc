//                              -*- Mode: C++ -*- 
// AtomType.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 15:00:09 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "AtomType.h"
#include "AtomTypeStore.h"
#include "Binstream.h"

namespace mccore {

  // STATIC MEMBERS ------------------------------------------------------------

  AtomTypeStore AtomType::atstore;
  AtomType* AtomType::aC1p;
  AtomType* AtomType::aC2p;
  AtomType* AtomType::aC3p;
  AtomType* AtomType::aC4p;
  AtomType* AtomType::aC5p;
  AtomType* AtomType::aH1p;
  AtomType* AtomType::aH2p;
  AtomType* AtomType::aH3p;
  AtomType* AtomType::aH4p;
  AtomType* AtomType::aH5p;
  AtomType* AtomType::aO1P;
  AtomType* AtomType::aO2p;
  AtomType* AtomType::aO2P;
  AtomType* AtomType::aO3p;
  AtomType* AtomType::aO3P;
  AtomType* AtomType::aO4p;
  AtomType* AtomType::aO5p;
  AtomType* AtomType::aP;
  AtomType* AtomType::a1H2p;
  AtomType* AtomType::a1H5p;
  AtomType* AtomType::a2H2p;
  AtomType* AtomType::a2H5p;
  AtomType* AtomType::aHO2p;
  AtomType* AtomType::aHO3p;
  AtomType* AtomType::aC2;
  AtomType* AtomType::aC4;
  AtomType* AtomType::aC5;
  AtomType* AtomType::aC5M;
  AtomType* AtomType::aC6;
  AtomType* AtomType::aC8;
  AtomType* AtomType::aH1;
  AtomType* AtomType::aH2;
  AtomType* AtomType::aH3;
  AtomType* AtomType::aH5;
  AtomType* AtomType::aH6;
  AtomType* AtomType::aH7;
  AtomType* AtomType::aH8;
  AtomType* AtomType::aN1;
  AtomType* AtomType::aN2;
  AtomType* AtomType::aN3;
  AtomType* AtomType::aN4;
  AtomType* AtomType::aN6;
  AtomType* AtomType::aN7;
  AtomType* AtomType::aN9;
  AtomType* AtomType::aO2;
  AtomType* AtomType::aO4;
  AtomType* AtomType::aO6;
  AtomType* AtomType::a1H2;
  AtomType* AtomType::a1H4;
  AtomType* AtomType::a1H5M;
  AtomType* AtomType::a1H6;
  AtomType* AtomType::a2H2;
  AtomType* AtomType::a2H4;
  AtomType* AtomType::a2H5M;
  AtomType* AtomType::a2H6;
  AtomType* AtomType::a3H5M;
  AtomType* AtomType::aPSY;
  AtomType* AtomType::aPSZ;
  AtomType* AtomType::aLP1;
  AtomType* AtomType::aLP3;
  AtomType* AtomType::aLP7;
  AtomType* AtomType::a1LP2;
  AtomType* AtomType::a1LP4;
  AtomType* AtomType::a1LP6;
  AtomType* AtomType::a2LP2;
  AtomType* AtomType::a2LP4;
  AtomType* AtomType::a2LP6;
  AtomType* AtomType::aH3T;
  AtomType* AtomType::aH5T;
  AtomType* AtomType::aC;
  AtomType* AtomType::aCA;
  AtomType* AtomType::aCB;
  AtomType* AtomType::aCD;
  AtomType* AtomType::aCD1;
  AtomType* AtomType::aCD2;
  AtomType* AtomType::aCE;
  AtomType* AtomType::aCE1;
  AtomType* AtomType::aCE2;
  AtomType* AtomType::aCE3;
  AtomType* AtomType::aCG;
  AtomType* AtomType::aCG1;
  AtomType* AtomType::aCG2;
  AtomType* AtomType::aCH2;
  AtomType* AtomType::aCZ;
  AtomType* AtomType::aCZ2;
  AtomType* AtomType::aCZ3;
  AtomType* AtomType::aH;
  AtomType* AtomType::a1H;
  AtomType* AtomType::a2H;
  AtomType* AtomType::a3H;
  AtomType* AtomType::aHA;
  AtomType* AtomType::aHA1;
  AtomType* AtomType::aHA2;
  AtomType* AtomType::aHB;
  AtomType* AtomType::aHB1;
  AtomType* AtomType::aHB2;
  AtomType* AtomType::aHB3;
  AtomType* AtomType::aHD1;
  AtomType* AtomType::aHD2;
  AtomType* AtomType::aHE;
  AtomType* AtomType::aHE1;
  AtomType* AtomType::aHE2;
  AtomType* AtomType::aHE3;
  AtomType* AtomType::aHG;
  AtomType* AtomType::aHG1;
  AtomType* AtomType::aHG2;
  AtomType* AtomType::aHH;
  AtomType* AtomType::aHH2;
  AtomType* AtomType::aHXT;
  AtomType* AtomType::aHZ;
  AtomType* AtomType::aHZ1;
  AtomType* AtomType::aHZ2;
  AtomType* AtomType::aHZ3;
  AtomType* AtomType::aN;
  AtomType* AtomType::aND1;
  AtomType* AtomType::aND2;
  AtomType* AtomType::aNE;
  AtomType* AtomType::aNE1;
  AtomType* AtomType::aNE2;
  AtomType* AtomType::aNH1;
  AtomType* AtomType::aNH2;
  AtomType* AtomType::aNZ;
  AtomType* AtomType::aO;
  AtomType* AtomType::aOD1;
  AtomType* AtomType::aOD2;
  AtomType* AtomType::aOE1;
  AtomType* AtomType::aOE2;
  AtomType* AtomType::aOG;
  AtomType* AtomType::aOG1;
  AtomType* AtomType::aOH;
  AtomType* AtomType::aOXT;
  AtomType* AtomType::aSD;
  AtomType* AtomType::aSG;
  AtomType* AtomType::a1HD1;
  AtomType* AtomType::a1HD2;
  AtomType* AtomType::a1HE2;
  AtomType* AtomType::a1HG1;
  AtomType* AtomType::a1HG2;
  AtomType* AtomType::a1HH1;
  AtomType* AtomType::a1HH2;
  AtomType* AtomType::a2HD1;
  AtomType* AtomType::a2HD2;
  AtomType* AtomType::a2HE2;
  AtomType* AtomType::a2HG1;
  AtomType* AtomType::a2HG2;
  AtomType* AtomType::a2HH1;
  AtomType* AtomType::a2HH2;
  AtomType* AtomType::a3HD1;
  AtomType* AtomType::a3HD2;
  AtomType* AtomType::a3HG1;
  AtomType* AtomType::a3HG2;
  AtomType* AtomType::aMG;
  AtomType* AtomType::aPSAZ;

  
  // LIFECYCLE -----------------------------------------------------------------

  AtomType::AtomType () 
    : type (0) 
  {
  }


  AtomType::AtomType (const char* t) 
  {
    type = new char[strlen (t) + 1];
    strcpy (type, t);
  }
  

  AtomType::AtomType (const AtomType &other)
  {
  }


  AtomType::~AtomType () 
  {
    if (type) delete[] type;
  }
  

  // METHODS -------------------------------------------------------------------


  const AtomType* 
  AtomType::parseType (const char* s) 
  {
    return atstore.get (s);
  }

  
  Vector3D 
  AtomType::getColor (const AtomType *type)
  {
    if (type->isHydrogen ())       return Vector3D (1.00f, 1.00f, 1.00f);
    else if (type->isOxygen ())    return Vector3D (0.76f, 0.00f, 0.00f);
    else if (type->isNitrogen ())  return Vector3D (0.20f, 0.15f, 0.80f);
    else if (type->isPhosphorus ()) return Vector3D (0.82f, 0.53f, 0.00f);
    else if (type->isCarbon ())    return Vector3D (0.60f, 0.60f, 0.60f);
    else if (type->isSulfur ())    return Vector3D (0.80f, 0.80f, 0.00f);
    else if (type->isLonePair ())  return Vector3D (0.00f, 0.80f, 0.00f);
    else if (type->isMagnesium ()) return Vector3D (0.13f, 0.54f, 0.13f);
    else 
      return Vector3D (0.10f, 0.10f, 0.10f);
  }

  
  char 
  AtomType::getFirstLetter () const
  {
    const char *p = type;
    
    while (*p)
      {
	if (isalpha (*p))
	  return *p;
	++p;
      }
    return (char)0;
  }
  
  // I/O -----------------------------------------------------------------------

  ostream &
  AtomType::output (ostream &out) const
  {
    return out << type;
  }
  

  oBinstream &
  AtomType::output (oBinstream &out) const
  {
    return out << type;
  }


  ostream &
  operator<< (ostream &out, const AtomType &a)
  {
    return a.output (out);
  }
  

  ostream &
  operator<< (ostream &out, const AtomType *a)
  {
    if (!a) out << "null";
    else a->output (out);
    return out;
  }

  
  oBinstream&
  operator<< (oBinstream &obs, const AtomType *t)
  {
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
