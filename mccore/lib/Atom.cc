//                              -*- Mode: C++ -*- 
// Atom.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:00:09 2003
// $Revision: 1.9.4.1 $
// $Id: Atom.cc,v 1.9.4.1 2004-12-25 02:39:06 larosem Exp $
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

#include "Atom.h"
#include "AtomType.h"
#include "Binstream.h"
#include "Pdbstream.h"



namespace mccore {


  // LIFECYCLE ------------------------------------------------------------
  
  
  Atom::Atom ()
    : Vector3D (),
      type (AtomType::aNull)
  {
  }
  
  
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
  {
  }
  
  
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
  Atom::getColor () const 
  {
    return this->type->getColor ();
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
  


  iPdbstream& 
  operator>> (iPdbstream &ips, Atom &at)
  {
    ips.read (at);
    return ips;
  }



  oPdbstream&
  operator<< (oPdbstream &ops, const Atom &at)
  {
    ops.write (at);
    return ops;
  }

}
