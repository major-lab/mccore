//                              -*- Mode: C++ -*- 
// Molecule.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Mon Jul  7 15:59:35 2003
// $Revision: 1.1 $
// $Id: Molecule.cc,v 1.1 2003-07-08 21:12:49 larosem Exp $
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

#include <iostream>

#include "Model.h"
#include "Molecule.h"
#include "Pdbstream.h"
#include "stlio.h"

using namespace mccore;



Molecule::Molecule (const Molecule &right)
  : header (right.header)
{
  Molecule::const_iterator cit;

  for (cit = right.begin (); right.end () != cit; ++cit)
    push_back ((*cit)->clone ());
}



Molecule::~Molecule ()
{
  Molecule::iterator it;
  
  for (it = begin (); end () != it; ++it)
    delete (*it);
}



Molecule&
Molecule::operator= (const Molecule &right)
{
  if (&right != this)
    {
      Molecule::iterator it;
      Molecule::const_iterator cit;

      header = right.header;
      for (it = begin (); end () != it; ++it)
	delete (*it);
      clear ();
      for (cit = right.begin (); right.end () != cit; ++cit)
	push_back ((*cit)->clone ());
    }
  return *this;
}



ostream&
mccore::operator<< (ostream &obs, const Molecule &obj)
{
  return obs << "MOLECULE: " << endl << obj.getPdbFileHeader () << endl
	     << (const list< Model* >&) obj << endl;
}



iPdbstream&
mccore::operator>> (iPdbstream &ips, Molecule &obj)
{
  Molecule::iterator it;

  for (it = obj.begin (); obj.end () != it; ++it)
    delete (*it);
  obj.clear ();
  obj.setPdbFileHeader (ips.getHeader ());
  while (! ips.eof ())
    {
      Model *model;

      model = new Model ();
      ips >> *model;
      if (! model->empty ())
	obj.push_back (model);
    }
  return ips;
}



oPdbstream&
mccore::operator<< (oPdbstream &ops, const Molecule &obj)
{
  Molecule::const_iterator cit;
  bool modelHeaders;

  ops.setHeader (obj.getPdbFileHeader ());
  ops.writeHeader ();
  modelHeaders = 1 < obj.size ();
  for (cit = obj.begin (); obj.end () != cit; ++cit)
    {
      if (modelHeaders)
	ops.startModel ();
      ops << **cit;
      if (modelHeaders)
	ops.endModel ();
    }
  return ops;
}

