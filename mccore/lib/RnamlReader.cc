//                              -*- Mode: C++ -*- 
// RnamlReader.cc
// Copyright Å© 2003 Laboratoire de Biologie Informatique et ThÅÈorique
//                  UniversitÅÈ de MontrÅÈal.
// Author           : Martin Larose
// Created On       : Tue Jul 15 12:56:11 2003
// $Revision: 1.1.2.4 $
// $Id: RnamlReader.cc,v 1.1.2.4 2003-11-21 15:55:40 larosem Exp $
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

#include "AbstractResidue.h"
#include "CAtom.h"
#include "CResId.h"
#include "CResidueFM.h"
#include "McCore.h"
#include "Messagestream.h"
#include "Model.h"
#include "Molecule.h"
#include "Pdbstream.h"
#include "ResidueFactoryMethod.h"
#include "RnamlReader.h"

#include "xmlcpg/Atom.h"
#include "xmlcpg/Base.h"
#include "xmlcpg/FileInputStream.h"
#include "xmlcpg/GZIPInputStream.h"
#include "xmlcpg/InputStream.h"
#include "xmlcpg/Model.h"
#include "xmlcpg/Molecule.h"
#include "xmlcpg/Object.h"
#include "xmlcpg/Rnaml.h"
#include "xmlcpg/Structure.h"
#include "xmlcpg/Unmarshaller.h"



RnamlReader::RnamlReader (const char *name, ResidueFactoryMethod *fm)
  : is (0),
    residueFM (fm),
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
    residueFM = new CResidueFM ();
}


  
RnamlReader::RnamlReader (rnaml::InputStream *is, ResidueFactoryMethod *fm)
  : is (is),
    residueFM (fm),
    rnaml (0)
{
  if (0 == fm)
    residueFM = new CResidueFM ();
}


  
RnamlReader::~RnamlReader ()
{
  if (0 != is)
    delete is;
  delete residueFM;
  if (0 != rnaml)
    delete rnaml;
}



CAtom*
RnamlReader::toMccore (const rnaml::Atom &atom)
{
  CAtom *a;
  char *type;

  a = new CAtom ();
  type = strdup (atom.getAtomType ());
  a->SetAll (atom.getX (), atom.getY (), atom.getZ (), iPdbstream::GetAtomType (type));
  return a;
}



AbstractResidue*
RnamlReader::toMccore (const rnaml::Base &base)
{
  AbstractResidue *r;
  const char *str;
  char *type;
  int c;
  const vector< rnaml::Atom* > &atoms = ((rnaml::Base&) base).getAtoms ();
  vector< rnaml::Atom* >::const_iterator cit;

  r = residueFM->createResidue ();
  str = base.getStrand ();
  if (0 != str)
    ((CResId&) *r).SetChainId (str[0]);
  ((CResId&) *r).SetResNo (base.getPosition ());
  type = strdup (base.getBaseType ());
  r->setType (iPdbstream::GetResidueType (type));
  c = base.getInsertion ();
  if (EOF != c)
    ((CResId&) *r).setInsertionCode (c);
  for (cit = atoms.begin (); atoms.end () != cit; ++cit)
    {
      CAtom *a;

      a = toMccore (**cit);
      r->insert (*a);
      delete a;
    }
  return r;
}



Model*
RnamlReader::toMccore (const rnaml::Model &model)
{
  Model *m;
  const vector< rnaml::Base* > &bases = ((rnaml::Model&) model).getBases ();
  vector< rnaml::Base* >::const_iterator cit;

  m = new Model ();
  for (cit = bases.begin (); bases.end () != cit; ++cit)
    m->push_back (toMccore (**cit));
  return m;
}



Molecule*
RnamlReader::toMccore (const rnaml::Molecule &molecule)
{
  Molecule *m;
  const char *str;
  rnaml::Structure *structure;
  
  m = new Molecule ();
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
	m->push_back (toMccore (**cit));
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
