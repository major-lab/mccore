//                              -*- Mode: C++ -*- 
// RnamlWriter.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.9 $
// $Id: RnamlWriter.cc,v 1.9 2005-03-22 01:10:25 larosem Exp $
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

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#include "AbstractModel.h"
#include "Atom.h"
#include "AtomType.h"
#include "GraphModel.h"
#include "Messagestream.h"
#include "Model.h"
#include "Molecule.h"
#include "PropertyType.h"
#include "Relation.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueType.h"
#include "RnamlWriter.h"

#include "xmlcpg/Atom.h"
#include "xmlcpg/Base.h"
#include "xmlcpg/BaseId.h"
#include "xmlcpg/BaseId3p.h"
#include "xmlcpg/BaseId5p.h"
#include "xmlcpg/BasePair.h"
#include "xmlcpg/BaseStack.h"
#include "xmlcpg/FileOutputStream.h"
#include "xmlcpg/GZIPOutputStream.h"
#include "xmlcpg/Marshaller.h"
#include "xmlcpg/Model.h"
#include "xmlcpg/ModelId.h"
#include "xmlcpg/Molecule.h"
#include "xmlcpg/MoleculeId.h"
#include "xmlcpg/PrintStream.h"
#include "xmlcpg/Rnaml.h"
#include "xmlcpg/StrAnnotation.h"
#include "xmlcpg/Structure.h"



namespace mccore
{
  
  RnamlWriter::RnamlWriter (const char *name, bool zipped)
    : ps (0)
  {
    if (0 != name)
      {
	string filename;
	rnaml::OutputStream *os;

	filename = string (name);
	if (zipped)
	  filename = filename.append (".gz");
	os = new rnaml::FileOutputStream (filename.c_str());
	if (0 == os)
	  gOut (2) << "File " << filename << ": " << strerror (errno) << endl;
	else if (os->getError ())
	  {
	    gOut (2) << "File " << filename << ": " << os->getErrorString () << endl;
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


  rnaml::BaseId*
  RnamlWriter::toBaseId (rnaml::MoleculeId *molId, rnaml::ModelId *mId, const ResId &id)
  {
    rnaml::BaseId *bId;

    bId = new rnaml::BaseId ();
    if (0 != molId)
      {
	bId->setMoleculeId (molId);
      }
    if (0 != mId)
      {
	bId->setModelId (mId);
      }
    if (' ' != id.getChainId ())
      {
	string str;

	str += id.getChainId ();
	bId->setStrand (str.c_str ());
      }
    bId->setPosition (id.getResNo ());
    return bId;
  }
  
  
  rnaml::Base*
  RnamlWriter::toRnaml (const Residue &residue)
  {
    rnaml::Base *base;
    Residue::const_iterator it;
    const char *type;
    const ResId &id = residue.getResId ();
    AtomSetNot filter (new AtomSetOr (new AtomSetPSE (), new AtomSetLP ()));
    
    base = new rnaml::Base ();
    if (' ' != id.getChainId ())
      {
	string chainId;
	
	chainId = id.getChainId ();
	base->setStrand (chainId.c_str ());
      }
    base->setPosition (id.getResNo ());
    type = (const char*) *residue.getType ();
    base->setBaseType (type);
    if (' ' != id.getInsertionCode ())
      {
	string insertionCode;
	
	insertionCode = id.getInsertionCode ();
	base->setInsertion (insertionCode.c_str ()[0]);
      }
    for (it = residue.begin (filter); residue.end () != it; ++it)
      base->addAtom (RnamlWriter::toRnaml (*it));
    return base;
  }


  rnaml::StrAnnotation*
  RnamlWriter::strAnnotate (const GraphModel &model)
  {
    rnaml::StrAnnotation *annotation;
    GraphModel::edge_const_iterator ecit;

    annotation = new rnaml::StrAnnotation ();
    for (ecit = model.edge_begin (); model.edge_end () != ecit; ++ecit)
      {
	const Relation &rel = **ecit;

	if (rel.getRef ()->getResId () < rel.getRes ()->getResId ())
	  {
	    if (rel.isStacking ())
	      {
		rnaml::BaseStack *stack = new rnaml::BaseStack ();

		stack->setBaseId1 (RnamlWriter::toBaseId (0, 0, rel.getRef ()->getResId ()));
		stack->setBaseId2 (RnamlWriter::toBaseId (0, 0, rel.getRes ()->getResId ()));
		if (rel.is (PropertyType::pStraightUpward))
		  {
		    stack->setComment ((const char*) *PropertyType::pStraightUpward);
		  }
		else if (rel.is (PropertyType::pStraightDownward))
		  {
		    stack->setComment ((const char*) *PropertyType::pStraightDownward);
		  }
		else if (rel.is (PropertyType::pReverseUpward))
		  {
		    stack->setComment ((const char*) *PropertyType::pReverseUpward);
		  }
		else if (rel.is (PropertyType::pReverseDownward))
		  {
		    stack->setComment ((const char*) *PropertyType::pReverseDownward);
		  }
		annotation->addChild (stack);
	      }
	    if (rel.isPairing ())
	      {
		rnaml::BasePair *bPair = new rnaml::BasePair ();
		rnaml::BaseId5p *bId5p = new rnaml::BaseId5p ();
		rnaml::BaseId3p *bId3p = new rnaml::BaseId3p ();

		bId5p->setBaseId (RnamlWriter::toBaseId (0, 0, rel.getRef ()->getResId ()));
		bPair->setBaseId5p (bId5p);
		bId3p->setBaseId (RnamlWriter::toBaseId (0, 0, rel.getRes ()->getResId ()));
		bPair->setBaseId3p (bId3p);
		bPair->setEdge5p (rel.getRefFace ()->toString ().c_str ());
		bPair->setEdge3p (rel.getResFace ()->toString ().c_str ());
		bPair->setBondOrientation ((rel.is (PropertyType::pCis)
					   ? PropertyType::pCis
					   : PropertyType::pTrans)->toString ().c_str ());
// 		bPair->setStrandOrientation ((rel.is (PropertyType::pParallel)
// 					     ? PropertyType::pParallel
// 					     : PropertyType::pAntiParallel)->toString ().c_str ());
		annotation->addChild (bPair);
	      }
	  }
      }
    return annotation;
  }
  
  
  rnaml::Model*
  RnamlWriter::toRnaml (const AbstractModel &model)
  {
    rnaml::Model *m;
    AbstractModel::const_iterator cit;
    const GraphModel *gModel;
    
    m = new rnaml::Model ();
    for (cit = model.begin (); model.end () != cit; ++cit)
      {
	m->addBase (RnamlWriter::toRnaml (*cit));
      }
    if (0 != (gModel = dynamic_cast< const GraphModel* > (&model)))
      {
	m->setStrAnnotation (RnamlWriter::strAnnotate (*gModel));
      }
    return m;
  }
  
  
  rnaml::Molecule*
  RnamlWriter::toRnaml (const Molecule &molecule)
  {
    rnaml::Molecule *m;
    
    m = new rnaml::Molecule ();
    try
      {
	const string &property = molecule.getProperty ("id");

	m->setId (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    try
      {
	const string &property = molecule.getProperty ("type");
	
	m->setType (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    try
      {
	const string &property = molecule.getProperty ("comment");
	
	m->setComment (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    try
      {
	const string &property = molecule.getProperty ("reference-ids");
	
	m->addReferenceId (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    try
      {
	const string &property = molecule.getProperty ("analysis-ids");
	
	m->addAnalysisId (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    try
      {
	const string &property = molecule.getProperty ("database-ids");
	
	m->addDatabaseId (property.c_str ());
      }
    catch (NoSuchElementException &e) { }
    
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
	    
	    model = RnamlWriter::toRnaml (*cit);
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
	rnaml::Rnaml rnaml ("1.1");
	rnaml::Marshaller marshaller;

	if (! molecule.empty ())
	  {
	    rnaml::Molecule *m;
	    
	    m = toRnaml (molecule);
	    m->setId ("molecule1");
	    rnaml.addChild (m);
	  }
	marshaller.setValidating (true);
	marshaller.setFormatted (true);
	marshaller.marshall (rnaml, *ps);
      }
  }
}
