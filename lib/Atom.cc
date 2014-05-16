// Atom.cc
// Copyright © 2003-05, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal.
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


#include <config.h>

#include "Atom.h"
#include "Binstream.h"
#include "Pdbstream.h"

namespace mccore
{


  bool Atom::operator== (const Atom &other) const
  {
    return *type == *other.getType (); 
  }


  bool Atom::operator!= (const Atom &other) const 
  {
    return ! operator== (other); 
  }


  bool Atom::operator< (const Atom &other) const
  {
    return *type < *other.type; 
  }

  Vector3D Atom::getColor () const 
  {
    return this->type->getColor ();
  }

  iBinstream& operator>> (iBinstream &ibs, Atom &atom)
  {
    const AtomType *type;
    ibs >> (Vector3D&)atom;
    ibs >> type;
    atom.setType (type);
    return ibs;
  }

  oBinstream& operator<< (oBinstream &obs, const Atom &atom)
  {
    return obs << (const Vector3D&) atom << atom.getType ();
  }

  iPdbstream&  operator>> (iPdbstream &ips, Atom &at)
  {
    ips.read (at);
    return ips;
  }

  oPdbstream& operator<< (oPdbstream &ops, const Atom &at)
  {
    ops.write (at);
    return ops;
  }

}


namespace std
{

  ostream& operator<< (ostream &os, const mccore::Atom &atom)
  {
    return os << (const mccore::Vector3D&) atom
              << ' ' << *atom.getType ();
  }

}
