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

namespace mccore {

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
