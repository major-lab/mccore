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
#include "Exception.h"
#include "Binstream.h"

namespace mccore {

  // STATIC MEMBERS ------------------------------------------------------------

  AtomTypeStore AtomType::atstore;
  AtomType* AtomType::aNull = 0;
  AtomType* AtomType::aC1p = 0;
  AtomType* AtomType::aC2p = 0;
  AtomType* AtomType::aC3p = 0;
  AtomType* AtomType::aC4p = 0;
  AtomType* AtomType::aC5p = 0;
  AtomType* AtomType::aH1p = 0;
  AtomType* AtomType::aH2p = 0;
  AtomType* AtomType::aH3p = 0;
  AtomType* AtomType::aH4p = 0;
  AtomType* AtomType::aH5p = 0;
  AtomType* AtomType::aO1P = 0;
  AtomType* AtomType::aO2p = 0;
  AtomType* AtomType::aO2P = 0;
  AtomType* AtomType::aO3p = 0;
  AtomType* AtomType::aO3P = 0;
  AtomType* AtomType::aO4p = 0;
  AtomType* AtomType::aO5p = 0;
  AtomType* AtomType::aP = 0;
  AtomType* AtomType::a1H2p = 0;
  AtomType* AtomType::a1H5p = 0;
  AtomType* AtomType::a2H2p = 0;
  AtomType* AtomType::a2H5p = 0;
  AtomType* AtomType::aHO2p = 0;
  AtomType* AtomType::aHO3p = 0;
  AtomType* AtomType::aC2 = 0;
  AtomType* AtomType::aC4 = 0;
  AtomType* AtomType::aC5 = 0;
  AtomType* AtomType::aC5M = 0;
  AtomType* AtomType::aC6 = 0;
  AtomType* AtomType::aC8 = 0;
  AtomType* AtomType::aH1 = 0;
  AtomType* AtomType::aH2 = 0;
  AtomType* AtomType::aH3 = 0;
  AtomType* AtomType::aH5 = 0;
  AtomType* AtomType::aH6 = 0;
  AtomType* AtomType::aH7 = 0;
  AtomType* AtomType::aH8 = 0;
  AtomType* AtomType::aN1 = 0;
  AtomType* AtomType::aN2 = 0;
  AtomType* AtomType::aN3 = 0;
  AtomType* AtomType::aN4 = 0;
  AtomType* AtomType::aN6 = 0;
  AtomType* AtomType::aN7 = 0;
  AtomType* AtomType::aN9 = 0;
  AtomType* AtomType::aO2 = 0;
  AtomType* AtomType::aO4 = 0;
  AtomType* AtomType::aO6 = 0;
  AtomType* AtomType::a1H2 = 0;
  AtomType* AtomType::a1H4 = 0;
  AtomType* AtomType::a1H5M = 0;
  AtomType* AtomType::a1H6 = 0;
  AtomType* AtomType::a2H2 = 0;
  AtomType* AtomType::a2H4 = 0;
  AtomType* AtomType::a2H5M = 0;
  AtomType* AtomType::a2H6 = 0;
  AtomType* AtomType::a3H5M = 0;
  AtomType* AtomType::aPSY = 0;
  AtomType* AtomType::aPSZ = 0;
  AtomType* AtomType::aLP1 = 0;
  AtomType* AtomType::aLP3 = 0;
  AtomType* AtomType::aLP7 = 0;
  AtomType* AtomType::a1LP2 = 0;
  AtomType* AtomType::a1LP4 = 0;
  AtomType* AtomType::a1LP6 = 0;
  AtomType* AtomType::a2LP2 = 0;
  AtomType* AtomType::a2LP4 = 0;
  AtomType* AtomType::a2LP6 = 0;
  AtomType* AtomType::aH3T = 0;
  AtomType* AtomType::aH5T = 0;
  AtomType* AtomType::aC = 0;
  AtomType* AtomType::aCA = 0;
  AtomType* AtomType::aCB = 0;
  AtomType* AtomType::aCD = 0;
  AtomType* AtomType::aCD1 = 0;
  AtomType* AtomType::aCD2 = 0;
  AtomType* AtomType::aCE = 0;
  AtomType* AtomType::aCE1 = 0;
  AtomType* AtomType::aCE2 = 0;
  AtomType* AtomType::aCE3 = 0;
  AtomType* AtomType::aCG = 0;
  AtomType* AtomType::aCG1 = 0;
  AtomType* AtomType::aCG2 = 0;
  AtomType* AtomType::aCH2 = 0;
  AtomType* AtomType::aCZ = 0;
  AtomType* AtomType::aCZ2 = 0;
  AtomType* AtomType::aCZ3 = 0;
  AtomType* AtomType::aH = 0;
  AtomType* AtomType::a1H = 0;
  AtomType* AtomType::a2H = 0;
  AtomType* AtomType::a3H = 0;
  AtomType* AtomType::aHA = 0;
  AtomType* AtomType::aHA1 = 0;
  AtomType* AtomType::aHA2 = 0;
  AtomType* AtomType::aHB = 0;
  AtomType* AtomType::aHB1 = 0;
  AtomType* AtomType::aHB2 = 0;
  AtomType* AtomType::aHB3 = 0;
  AtomType* AtomType::aHD1 = 0;
  AtomType* AtomType::aHD2 = 0;
  AtomType* AtomType::aHE = 0;
  AtomType* AtomType::aHE1 = 0;
  AtomType* AtomType::aHE2 = 0;
  AtomType* AtomType::aHE3 = 0;
  AtomType* AtomType::aHG = 0;
  AtomType* AtomType::aHG1 = 0;
  AtomType* AtomType::aHG2 = 0;
  AtomType* AtomType::aHH = 0;
  AtomType* AtomType::aHH2 = 0;
  AtomType* AtomType::aHXT = 0;
  AtomType* AtomType::aHZ = 0;
  AtomType* AtomType::aHZ1 = 0;
  AtomType* AtomType::aHZ2 = 0;
  AtomType* AtomType::aHZ3 = 0;
  AtomType* AtomType::aN = 0;
  AtomType* AtomType::aND1 = 0;
  AtomType* AtomType::aND2 = 0;
  AtomType* AtomType::aNE = 0;
  AtomType* AtomType::aNE1 = 0;
  AtomType* AtomType::aNE2 = 0;
  AtomType* AtomType::aNH1 = 0;
  AtomType* AtomType::aNH2 = 0;
  AtomType* AtomType::aNZ = 0;
  AtomType* AtomType::aO = 0;
  AtomType* AtomType::aOD1 = 0;
  AtomType* AtomType::aOD2 = 0;
  AtomType* AtomType::aOE1 = 0;
  AtomType* AtomType::aOE2 = 0;
  AtomType* AtomType::aOG = 0;
  AtomType* AtomType::aOG1 = 0;
  AtomType* AtomType::aOH = 0;
  AtomType* AtomType::aOXT = 0;
  AtomType* AtomType::aSD = 0;
  AtomType* AtomType::aSG = 0;
  AtomType* AtomType::a1HD1 = 0;
  AtomType* AtomType::a1HD2 = 0;
  AtomType* AtomType::a1HE2 = 0;
  AtomType* AtomType::a1HG1 = 0;
  AtomType* AtomType::a1HG2 = 0;
  AtomType* AtomType::a1HH1 = 0;
  AtomType* AtomType::a1HH2 = 0;
  AtomType* AtomType::a2HD1 = 0;
  AtomType* AtomType::a2HD2 = 0;
  AtomType* AtomType::a2HE2 = 0;
  AtomType* AtomType::a2HG1 = 0;
  AtomType* AtomType::a2HG2 = 0;
  AtomType* AtomType::a2HH1 = 0;
  AtomType* AtomType::a2HH2 = 0;
  AtomType* AtomType::a3HD1 = 0;
  AtomType* AtomType::a3HD2 = 0;
  AtomType* AtomType::a3HG1 = 0;
  AtomType* AtomType::a3HG2 = 0;
  AtomType* AtomType::aMG = 0;
  AtomType* AtomType::aPSAZ = 0;

  
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
    return (0 == a ? AtomType::aNull : a)->output (out);
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
