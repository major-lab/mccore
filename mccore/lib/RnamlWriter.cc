//                              -*- Mode: C++ -*- 
// RnamlWriter.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.1.2.1 $
// $Id: RnamlWriter.cc,v 1.1.2.1 2003-07-15 14:10:45 larosem Exp $
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
#include <string>
#include <sstream>

#include "Atom.h"
#include "AtomSet.h"
#include "Model.h"
#include "Molecule.h"
#include "Residue.h"
#include "RnamlWriter.h"

#include "xmlcpg/Atom.h"
#include "xmlcpg/Base.h"
#include "xmlcpg/Model.h"
#include "xmlcpg/Molecule.h"
#include "xmlcpg/Rnaml.h"

extern "C" {
#include "xmlcpg/xmlcpg.h"
#include "xmlcpg/validator.h"
}

using namespace rnaml;



namespace mccore
{
  rnaml::Atom*
  RnamlWriter::toRnaml (const mccore::Atom &atom)
  {
    rnaml::Atom *a;

    a = new rnaml::Atom ();
    a->setAtomType ((const char*) *atom.getType ());
    a->setCoordinates (atom.getX (), atom.getY (), atom.getZ ());
    return a;
  }


  
  rnaml::Base*
  RnamlWriter::toRnaml (const Residue &residue)
  {
    rnaml::Base *base;
    Residue::const_iterator it;

    base = new rnaml::Base ();
    if (' ' != residue.getResId ().getChainId ())
      {
	string chainId;

	chainId = residue.getResId ().getChainId ();
	base->setStrand (chainId.c_str ());
      }
    base->setPosition (residue.getResId ().getResNo ());
    base->setBaseType ((const char*) *residue.getType ());
    if (' ' != residue.getResId ().getChainId ())
      {
	string insertionCode;

	insertionCode = residue.getResId ().getChainId ();
// 	base->setInsertion (insertionCode.c_str ());
      }
    for (it = residue.begin (new AtomSetNot (new AtomSetPSE ())); residue.end () != it; ++it)
      base->addAtom (RnamlWriter::toRnaml (*it));
    return base;
  }


  
  rnaml::Model*
  RnamlWriter::toRnaml (const mccore::Model &model)
  {
    rnaml::Model *m;
    mccore::Model::const_iterator cit;

    m = new rnaml::Model ();
    for (cit = model.begin (); model.end () != cit; ++cit)
      {
	rnaml::Base *base;

	base = RnamlWriter::toRnaml (*cit);
	m->addBase (base);
      }
    return m;
  }
  

  
  rnaml::Molecule*
  RnamlWriter::toRnaml (const mccore::Molecule &molecule)
  {
    rnaml::Molecule *m;
    mccore::Molecule::const_iterator cit;
    int i;
    
    m = new rnaml::Molecule ();
    i = 0;
    for (cit = molecule.begin (); molecule.end () != cit; ++cit)
      {
	rnaml::Model *model;
	ostringstream oss;
	
	model = RnamlWriter::toRnaml (**cit);
	oss << (string) "model" << ++i;
	model->setId (oss.str ().c_str ());
	m->addModel (model);
      }
    return m;
  }
  
  
  
  void
  RnamlWriter::write (const mccore::Atom &atom)
  {
    rnaml::Atom *a;
    xmlcpgElement *element;

    a = RnamlWriter::toRnaml (atom);
    element = a->toXML ();
    xmlcpgprettyPrint (of, (xmlcpgObject*) element, 0);
    delete a;
    xmlcpgdelete ((xmlcpgObject*) element);
  }
  

  
  void
  RnamlWriter::write (const Residue &residue)
  {
    rnaml::Base *base;
    xmlcpgElement *element;

    base = RnamlWriter::toRnaml (residue);
    element = base->toXML ();
    xmlcpgprettyPrint (of, (xmlcpgObject*) element, 0);
    delete base;
    xmlcpgdelete ((xmlcpgObject*) element);
  }
  

  
  void
  RnamlWriter::write (const mccore::Model &model)
  {
    rnaml::Model *m;
    xmlcpgElement *element;

    m = RnamlWriter::toRnaml (model);
    element = m->toXML ();
    xmlcpgprettyPrint (of, (xmlcpgObject*) element, 0);
    delete m;
    xmlcpgdelete ((xmlcpgObject*) element);
  }
  
  
  
  void
  RnamlWriter::write (const mccore::Molecule &molecule)
  {
    rnaml::Molecule *m;
    xmlcpgElement *element;

    m = RnamlWriter::toRnaml (molecule);
    element = m->toXML ();
    xmlcpgprettyPrint (of, (xmlcpgObject*) element, 0);
    delete m;
    xmlcpgdelete ((xmlcpgObject*) element);
  }


  
  void
  RnamlWriter::writeDocument (const mccore::Molecule &molecule)
  {
    rnaml::Molecule *m;
    rnaml::Rnaml rnaml ("1.1");
    xmlcpgObject *document;

    m = toRnaml (molecule);
    m->setId ("molecule1");
    rnaml.addChild (m);
    document = (xmlcpgObject*) rnaml.toXMLDocument ();
    xmlcpgprettyPrint (of, document, 0);
    xmlcpgdelete (document);
  }


  
  void
  RnamlWriter::write (const rnaml::Rnaml &rnaml)
  {
    xmlcpgObject *document;

    document = (xmlcpgObject*) rnaml.toXMLDocument ();
    xmlcpgprettyPrint (of, document, 0);
    xmlcpgdelete (document);
  }
}
