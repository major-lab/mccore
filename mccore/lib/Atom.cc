//                              -*- Mode: C++ -*- 
// Atom.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:00:09 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Atom.h"
#include "Binstream.h"
#include "AtomType.h"

namespace mccore {


  // LIFECYCLE ------------------------------------------------------------
  
  
  Atom::Atom () : type (0) 
  {}


  Atom::Atom (float x, float y, float z, const AtomType *aType) 
    : Vector3D (x, y, z), 
      type (aType) 
  {}


  Atom::Atom (Vector3D aPoint, const AtomType *aType)
    : Vector3D (aPoint.getX(), aPoint.getY(), aPoint.getZ()),
      type (aType) 
  {}
  

  Atom::Atom (const Atom &other) 
    : Vector3D (other),
      type (other.type) 
  {}
  

  Atom* 
  Atom::clone () const 
  { 
    return new Atom (*this); 
  }
  

  // OPERATORS ------------------------------------------------------------


  Atom& 
  Atom::operator= (const Atom &other)
  {
    if (&other != this) {
      Vector3D::operator= (other);
      type = other.type;
    }
    return *this;
  }


  bool 
  Atom::operator== (const Atom &other) const
  { 
    return *type == *other.getType (); 
  }
  
  
  bool 
  Atom::operator!= (const Atom &other) const 
  { 
    return ! operator== (other); 
  }
  
  bool 
  Atom::operator< (const Atom &other) const
  { 
    return *type < *other.type; 
  }
  

// METHODS --------------------------------------------------------------

  Vector3D 
  Atom::color () const 
  {
    if (type->isHydrogen ())       return Vector3D (1.00f, 1.00f, 1.00f);
    else if (type->isOxygen ())    return Vector3D (0.76f, 0.00f, 0.00f);
    else if (type->isNitrogen ())  return Vector3D (0.20f, 0.15f, 0.80f);
    else if (type->isPhosphate ()) return Vector3D (0.82f, 0.53f, 0.00f);
    else if (type->isCarbon ())    return Vector3D (0.60f, 0.60f, 0.60f);
    else if (type->isSulfur ())    return Vector3D (0.80f, 0.80f, 0.00f);
    else if (type->isLonePair ())  return Vector3D (0.00f, 0.80f, 0.00f);
    else if (type->isMagnesium ()) return Vector3D (0.13f, 0.54f, 0.13f);
    else 
      return Vector3D (0.10f, 0.10f, 0.10f);
  }
  
  // I/O -----------------------------------------------------------------------

  ostream&
  operator<< (ostream &os, const Atom& atom)
  {
  return os << (const Vector3D&) atom 
	    << ' ' << *atom.getType ();
}



iBinstream&
operator>> (iBinstream &ibs, Atom &atom)
{
  const AtomType *type;

  ibs >> (Vector3D&)atom;
  ibs >> type;
  
  atom.setType (type);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const Atom &atom)
{
  
  return obs << (const Vector3D&) atom << atom.getType ();
}

}
