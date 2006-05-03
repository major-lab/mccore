//                              -*- Mode: C++ -*- 
// RnamlReader.cc
// Copyright Å© 2003-06 Laboratoire de Biologie Informatique et ThÅÈorique
//                     UniversitÅÈ de MontrÅÈal.
// Author           : Martin Larose
// Created On       : Tue Jul 15 12:56:11 2003
// $Revision: 1.9.2.2 $
// $Id: RnamlReader.cc,v 1.9.2.2 2006-05-03 21:04:37 larosem Exp $
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

#include <string.h>
#include <errno.h>

#include "AbstractModel.h"
#include "Atom.h"
#include "AtomType.h"
#include "GraphModel.h"
#include "Messagestream.h"
#include "ModelFactoryMethod.h"
#include "Molecule.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"
#include "ResidueType.h"
#include "RnamlReader.h"

#include "rnamlc++/Atom.h"
#include "rnamlc++/Base.h"
#include "rnamlc++/FileInputStream.h"
#include "rnamlc++/GZIPInputStream.h"
#include "rnamlc++/InputStream.h"
#include "rnamlc++/Model.h"
#include "rnamlc++/Molecule.h"
#include "rnamlc++/Object.h"
#include "rnamlc++/Rnaml.h"
#include "rnamlc++/Structure.h"
#include "rnamlc++/Unmarshaller.h"



namespace mccore
{
  
  RnamlReader::RnamlReader (const char *name, const ModelFactoryMethod *fm)
    : is (0),
      rnaml (0)
  {
    if (0 != name)
      {
	is = (rnaml::InputStream*) new rnaml::FileInputStream (name);
	if (0 == is)
	  gOut (2) << "File " << name << " " << strerror (errno) << endl;
	else if (is->getError ())
	  {
	    gOut (2) << "File " << name << " " << is->getErrorString () << endl;
	    delete is;
	    is = 0;
	  }
	else
	  is = (rnaml::InputStream*) new rnaml::GZIPInputStream ((rnaml::FileInputStream*) is);
      }

    if (0 == fm)
    {
      ExtendedResidueFM rfm;
      this->modelFM = new GraphModelFM (&rfm);
    }
    else
      this->modelFM = fm->clone ();
  }
  
  
  RnamlReader::RnamlReader (rnaml::InputStream *is, const ModelFactoryMethod *fm)
    : is (is),
      rnaml (0)
  {
    if (0 == fm)
    {
      ExtendedResidueFM rfm;
      this->modelFM = new GraphModelFM (&rfm);
    }
    else
      this->modelFM = fm->clone ();
  }
  
  
  RnamlReader::~RnamlReader ()
  {
    if (0 != is)
      delete is;
    delete this->modelFM;
    if (0 != rnaml)
      delete rnaml;
  }
  
  
  mccore::Atom*
  RnamlReader::toMccore (const rnaml::Atom &atom)
  {
    mccore::Atom *a;
    char *type;
    
    a = new mccore::Atom ();
    type = new char[strlen (atom.getAtomType ()) + 1];
    strcpy (type, atom.getAtomType ());
    a->set (atom.getX (), atom.getY (), atom.getZ (), AtomType::parseType (type));
    return a;
  }
  
  
  Residue*
  RnamlReader::toMccore (const rnaml::Base &base)
  {
    Residue *r;
    ResId id;
    const char *str;
    int c;
    const vector< rnaml::Atom* > &atoms = ((rnaml::Base&) base).getAtoms ();
    vector< rnaml::Atom* >::const_iterator cit;

    r = this->modelFM->createResidue ();
    str = base.getStrand ();
    if (0 != str)
      id.setChainId (str[0]);
    id.setResNo (base.getPosition ());
    c = base.getInsertion ();
    if ((char) EOF != c)
      id.setInsertionCode (c);
    r->setResId (id);
    r->setType (ResidueType::parseType (base.getBaseType ()));
    for (cit = atoms.begin (); atoms.end () != cit; ++cit)
      {
	mccore::Atom *a;
	
	a = toMccore (**cit);
	r->insert (*a);
	delete a;
      }
    r->finalize ();
    return r;
  }
  
  
  AbstractModel*
  RnamlReader::toMccore (const rnaml::Model &model)
  {
    AbstractModel *m;
    const vector< rnaml::Base* > &bases = ((rnaml::Model&) model).getBases ();
    vector< rnaml::Base* >::const_iterator cit;
    
    m = this->modelFM->createModel ();
    for (cit = bases.begin (); bases.end () != cit; ++cit)
      {
	Residue *r;

	r = toMccore (**cit);
	m->insert (*r);
	delete r;
      }
    return m;
  }
  
  
  Molecule*
  RnamlReader::toMccore (const rnaml::Molecule &molecule)
  {
    Molecule *m;
    const char *str;
    rnaml::Structure *structure;
    
    m = new Molecule (this->modelFM);
    m->setProperty ("id", molecule.getId ());
    m->setProperty ("type", molecule.getType ());
    str = molecule.getComment ();
    if (0 != str)
      m->setProperty ("comment", str);
    str = molecule.getReferenceIdsString ();
    if (0 != str)
      m->setProperty ("reference-ids", str);
    str = molecule.getAnalysisIdsString ();
    if (0 != str)
      m->setProperty ("analysis-ids", str);
    str = molecule.getDatabaseIdsString ();
    if (0 != str)
      m->setProperty ("database-ids", str);
    
    structure = molecule.getStructure ();
    if (0 != structure)
      {
	const vector< rnaml::Model* > &models = structure->getModels ();
	vector< rnaml::Model* >::const_iterator cit;
	
	for (cit = models.begin (); models.end () != cit; ++cit)
	{
	  AbstractModel* mdl = toMccore (**cit);
	  m->insert (*mdl);
	  delete mdl;
	}
      }
    return m;
  }
  
  
  void
  RnamlReader::close ()
  {
    if (0 != is)
      is->close ();
  }
  

  Molecule*
  RnamlReader::read ()
  {
    Molecule *molecule;
    
    molecule = 0;
    if (0 != is && 0 == rnaml)
      {
	rnaml::Unmarshaller um;
	
	um.setValidating (true);
	rnaml = um.unmarshall (*is);
	if (0 != rnaml)
	  children = rnaml->getChildren ();
	it = children.begin ();
      }
    while (it != children.end ())
      {
	rnaml::Molecule *obj;
	
	if (0 != (obj = dynamic_cast< rnaml::Molecule* > (*(it++))))
	  {
	    molecule = toMccore (*obj);
	    break;
	  }
      }
    return molecule;
  }
  
}
