//                              -*- Mode: C++ -*- 
// RnamlWriter.cc
// Copyright � 2003 Laboratoire de Biologie Informatique et Th�orique
//                  Universit� de Montr�al.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.2 $
// $Id: RnamlWriter.cc,v 1.2 2003-12-23 14:57:49 larosem Exp $
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
#include <stdio.h>
#include <string>
#include <string.h>
// #include <sstream>
#include <errno.h>

#include "Atom.h"
#include "AtomType.h"
#include "Messagestream.h"
#include "Model.h"
#include "Molecule.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueType.h"
#include "RnamlWriter.h"

#include "xmlcpg/Atom.h"
#include "xmlcpg/Base.h"
#include "xmlcpg/FileOutputStream.h"
#include "xmlcpg/GZIPOutputStream.h"
#include "xmlcpg/Marshaller.h"
#include "xmlcpg/Model.h"
#include "xmlcpg/Molecule.h"
#include "xmlcpg/PrintStream.h"
#include "xmlcpg/Rnaml.h"
#include "xmlcpg/Structure.h"



namespace mccore {

  
  RnamlWriter::RnamlWriter (const char *name, bool zipped)
    : ps (0)
  {
    if (0 != name)
      {
	rnaml::OutputStream *os;

	if (zipped)
	  name = string (name).append (".gz").c_str ();
	os = new rnaml::FileOutputStream (name);
	if (0 == os)
	  gOut (2) << "File " << name << ": " << strerror (errno) << endl;
	else if (os->getError ())
	  {
	    gOut (2) << "File " << name << ": " << os->getErrorString () << endl;
	    delete os;
	  }
	else
	  {
	    if (zipped)
	      os = new rnaml::GZIPOutputStream ((rnaml::FileOutputStream*) os);
	    ps = new rnaml::PrintStream (os);
	  }
      }
  }
  
  
  
  RnamlWriter::~RnamlWriter ()
  {
    if (0 != ps)
      delete ps;
  }
  
  
  
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
    const char *type;
    const ResId &id = residue.getResId ();
    
    base = new rnaml::Base ();
    if (' ' != id.getChainId ())
      {
	string chainId;
	
	chainId = id.getChainId ();
	base->setStrand (chainId.c_str ());
      }
    base->setPosition (id.getResNo ());
    type = residue.getType ()->toString ();
    base->setBaseType (type);
    if (' ' != id.getInsertionCode ())
      {
	string insertionCode;
	
	insertionCode = id.getInsertionCode ();
	base->setInsertion (insertionCode.c_str ()[0]);
      }
    for (it = residue.begin (new AtomSetNot (new AtomSetOr (new AtomSetPSE (), new AtomSetLP ()))); residue.end () != it; ++it)
      base->addAtom (RnamlWriter::toRnaml (*it));
    return base;
  }
  
  
  
  rnaml::Model*
  RnamlWriter::toRnaml (const Model &model)
  {
    rnaml::Model *m;
    Model::const_iterator cit;
    
    m = new rnaml::Model ();
    for (cit = model.begin (); model.end () != cit; ++cit)
      m->addBase (RnamlWriter::toRnaml (*cit));
    return m;
  }
  
  
  
  rnaml::Molecule*
  RnamlWriter::toRnaml (const Molecule &molecule)
  {
    rnaml::Molecule *m;
    const char *property;
    
    m = new rnaml::Molecule ();
    property = molecule.getProperty ("id");
    if (0 != property)
      m->setId (property);
    property = molecule.getProperty ("type");
    if (0 != property)
      m->setType (property);
    property = molecule.getProperty ("comment");
    if (0 != property)
      m->setComment (property);
    property = molecule.getProperty ("reference-ids");
    if (0 != property)
      m->addReferenceId (property);
    property = molecule.getProperty ("analysis-ids");
    if (0 != property)
      m->addAnalysisId (property);
    property = molecule.getProperty ("database-ids");
    if (0 != property)
      m->addDatabaseId (property);
    if (! molecule.empty ())
      {
	rnaml::Structure *s;
	Molecule::const_iterator cit;
	int i;
	
	i = 0;
	s = new rnaml::Structure ();
	for (cit = molecule.begin (); molecule.end () != cit; ++cit)
	  {
	    rnaml::Model *model;
	    // 	  ostringstream oss;
	    char *id;
	    
	    model = RnamlWriter::toRnaml (**cit);
	    // 	  oss << (string) "model" << ++i;
	    // 	  model->setId (oss.str ().c_str ());
	    id = new char[256];
	    sprintf (id, "model%d", ++i);
	    model->setId (id);
	    s->addModel (model);
	  }
	m->setStructure (s);
      }
    return m;
  }
  
  
  
  void
  RnamlWriter::close ()
  {
    if (0 != ps)
      ps->close ();
  }
  
  
  
  void
  RnamlWriter::write (const Molecule &molecule)
  {
    if (0 != ps)
      {
	rnaml::Molecule *m;
	rnaml::Rnaml rnaml ("1.1");
	rnaml::Marshaller marshaller;
	
	m = toRnaml (molecule);
	m->setId ("molecule1");
	rnaml.addChild (m);
	marshaller.setValidating (true);
	marshaller.setFormatted (true);
	marshaller.marshall (rnaml, *ps);
      }
  }
}
