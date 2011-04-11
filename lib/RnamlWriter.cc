//                              -*- Mode: C++ -*- 
// RnamlWriter.cc
// Copyright � 2003-06 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.17 $
// $Id: RnamlWriter.cc,v 1.17 2006-05-03 21:11:04 larosem Exp $
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

// cmake generated defines
#include <config.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <sstream>

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

#include "rnamlc++/Atom.h"
#include "rnamlc++/Base.h"
#include "rnamlc++/BaseId.h"
#include "rnamlc++/BaseId3p.h"
#include "rnamlc++/BaseId5p.h"
#include "rnamlc++/BasePair.h"
#include "rnamlc++/BaseStack.h"
#include "rnamlc++/FileOutputStream.h"
#include "rnamlc++/GZIPOutputStream.h"
#include "rnamlc++/Marshaller.h"
#include "rnamlc++/Model.h"
#include "rnamlc++/ModelId.h"
#include "rnamlc++/Molecule.h"
#include "rnamlc++/MoleculeId.h"
#include "rnamlc++/PrintStream.h"
#include "rnamlc++/Rnaml.h"
#include "rnamlc++/Segment.h"
#include "rnamlc++/SeqAnnotation.h"
#include "rnamlc++/Sequence.h"
#include "rnamlc++/StrAnnotation.h"
#include "rnamlc++/Structure.h"



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
    string type;
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
    type = residue.getType ()->toString ();
    if (residue.getType ()->isRNA ()
	|| residue.getType ()->isDNA ())
      {
	type = type.substr (2, type.size () - 2);
      }
    base->setBaseType (type.c_str ());
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
		if (rel.is (PropertyType::pUpward))
		  {
		    stack->setComment ((const char*) *PropertyType::pUpward);
		  }
		else if (rel.is (PropertyType::pDownward))
		  {
		    stack->setComment ((const char*) *PropertyType::pDownward);
		  }
		else if (rel.is (PropertyType::pInward))
		  {
		    stack->setComment ((const char*) *PropertyType::pInward);
		  }
		else if (rel.is (PropertyType::pOutward))
		  {
		    stack->setComment ((const char*) *PropertyType::pOutward);
		  }
		annotation->addChild (stack);
	      }
	    if (rel.isPairing ())
	      {
		const set< const PropertyType* > &labels = rel.getLabels ();
		set< const PropertyType* >::const_iterator labelsIt;
		rnaml::BasePair *bPair = new rnaml::BasePair ();
		rnaml::BaseId5p *bId5p = new rnaml::BaseId5p ();
		rnaml::BaseId3p *bId3p = new rnaml::BaseId3p ();
		string comment;

		bId5p->setBaseId (RnamlWriter::toBaseId (0, 0, rel.getRef ()->getResId ()));
		bPair->setBaseId5p (bId5p);
		bId3p->setBaseId (RnamlWriter::toBaseId (0, 0, rel.getRes ()->getResId ()));
		bPair->setBaseId3p (bId3p);
		bPair->setEdge5p (rel.getRefFace ()->toString ().c_str ());
		bPair->setEdge3p (rel.getResFace ()->toString ().c_str ());
		bPair->setBondOrientation ((rel.is (PropertyType::pCis)
					   ? PropertyType::pCis
					   : PropertyType::pTrans)->toString ().c_str ());
		bPair->setStrandOrientation ((rel.is (PropertyType::pParallel)
					      ? PropertyType::pParallel
					      : PropertyType::pAntiparallel)->toString ().c_str ());
// 		bPair->setStrandOrientation ((rel.is (PropertyType::pStraight)
// 					      ? "parallel"
// 					      : "anti-parallel"));
		for (labelsIt = labels.begin (); labels.end () != labelsIt; ++labelsIt)
		  {
		    const PropertyType *type = *labelsIt;
		    
		    if (type->isPairing ()
			&& type != PropertyType::pPairing)
		      {
			if (! comment.empty ())
			  {
			    comment += " ";
			  }
			comment += type->toString ();
		      }
		  }
		if (! comment.empty ())
		  {
		    bPair->setComment (comment.c_str ());
		  }
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
  

  void
  RnamlWriter::buildStrands (vector< vector< const Residue* > > &sequences, const GraphModel &graph)
  {
    list< GraphModel::edge_const_iterator > unsorted;
    GraphModel::edge_const_iterator edgeIt;

    sequences.clear ();
    for (edgeIt = graph.edge_begin (); graph.edge_end () != edgeIt; ++edgeIt)
      {
	if ((*edgeIt)->is (PropertyType::pAdjacent5p))
	  {
	    unsorted.push_back (edgeIt);
	  }
      }
    while (! unsorted.empty ())
      {
	GraphModel::edge_const_iterator sj;
	list< GraphModel::edge_const_iterator > sorted;
	list< GraphModel::edge_const_iterator >::iterator it;

	sj = unsorted.front ();
	unsorted.pop_front ();
	sorted.push_back (sj);
	for (it = unsorted.begin (); unsorted.end () != it;)
	  {
	    if ((**it)->getRes ()->getResId () == (*sj)->getRef ()->getResId ())
	      {
		sj = *it;
		sorted.push_front (sj);
		unsorted.erase (it);
		it = unsorted.begin ();
	      }
	    else
	      {
		++it;
	      }
	  }
	sj = sorted.back ();
	for (it = unsorted.begin (); unsorted.end () != it;)
	  {
	    if ((**it)->getRef ()->getResId () == (*sj)->getRes ()->getResId ())
	      {
		sj = *it;;
		sorted.push_back (sj);
		unsorted.erase (it);
		it = unsorted.begin ();
	      }
	    else
	      {
		++it;
	      }
	  }
	sequences.push_back (vector< const Residue* > ());
	vector< const Residue* > &seq = sequences.back ();

	it = sorted.begin ();
	seq.push_back ((**it)->getRef ());
	while (sorted.end () != it)
	  {
	    seq.push_back ((**it)->getRes ());
	    ++it;
	  }
      }

    // Verify that the sequences have the same chain id and have consecutive
    // residue number.
    vector< vector< const Residue* > >::iterator seqIt;

    for (seqIt = sequences.begin (); sequences.end () != seqIt; ++seqIt)
      {
	vector< const Residue* > &resVec = *seqIt;
	vector< const Residue* >::iterator resVecIt;
	char chain;
	int number;

	resVecIt = resVec.begin ();
	chain = (*resVecIt)->getResId ().getChainId ();
	number = (*resVecIt)->getResId ().getResNo ();
	++resVecIt;
	while (resVec.end () != resVecIt)
	  {
	    if ((*resVecIt)->getResId ().getChainId () != chain
		|| (*resVecIt)->getResId ().getResNo () != number + 1)
	      {
		vector < const Residue* > rest;
		
		if (++resVec.begin () == resVecIt)
		  {
		    rest.insert (rest.end (), resVecIt, resVec.end ());
		    resVec.erase (++resVecIt, resVec.end ());
		  }
		else
		  {
		    rest.insert (rest.end (), resVecIt - 1, resVec.end ());
		    resVec.erase (resVecIt, resVec.end ());
		  }		
		++seqIt;
		if (1 < rest.size ())
		  {
		    seqIt = --sequences.insert (seqIt, rest);
		  }
		break;
	      }
	    else
	      {
		number += 1;
		++resVecIt;
	      }
	  }
      }
  }


  rnaml::Sequence*
  RnamlWriter::toSequence (const vector< const Residue* > &seq)
  {
    rnaml::Sequence *sequence;
    string chain;

    sequence = new rnaml::Sequence ();
    chain = seq.front ()->getResId ().getChainId ();
    sequence->setStrand (chain.c_str ());
    sequence->setLength (seq.size ());
    sequence->setCircular (false);
    sequence->setSeqAnnotation (RnamlWriter::toSeqAnnotation (seq));
    return sequence;
  }


  rnaml::SeqAnnotation*
  RnamlWriter::toSeqAnnotation (const vector< const Residue* > &seq)
  {
    rnaml::SeqAnnotation *seqA;

    seqA = new rnaml::SeqAnnotation ();
    seqA->addChild (RnamlWriter::toSegment (seq));
    return seqA;
  }


  rnaml::Segment*
  RnamlWriter::toSegment (const vector< const Residue* > &seq)
  {
    rnaml::Segment *segment;
    rnaml::BaseId5p *bId5p;
    rnaml::BaseId3p *bId3p;

    segment = new rnaml::Segment ();
    bId5p = new rnaml::BaseId5p ();
    bId3p = new rnaml::BaseId3p ();
    bId5p->setBaseId (RnamlWriter::toBaseId (0, 0, seq.front ()->getResId ()));
    bId3p->setBaseId (RnamlWriter::toBaseId (0, 0, seq.back ()->getResId ()));
    segment->setBaseId5p (bId5p);
    segment->setEnd (bId3p);
    return segment;
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
	Molecule::const_iterator molIt;
	unsigned int moleculeIndex;
	const GraphModel *gModel;
	
	for (molIt = molecule.begin (), moleculeIndex = 1;
	     molecule.end () != molIt;
	     ++molIt, ++moleculeIndex)
	  {
	    rnaml::Molecule *m;
	    rnaml::Structure *s;
	    rnaml::Model *model;
	    ostringstream oss;
	    ostringstream oss2;
	
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
	    
	    if (0 != (gModel = dynamic_cast< const GraphModel* > (&*molIt)))
	      {
		vector< vector< const Residue* > > sequences;
		vector< vector< const Residue* > >::iterator seqIt;
		
		RnamlWriter::buildStrands (sequences, *gModel);
		for (seqIt = sequences.begin (); sequences.end () != seqIt; ++seqIt)
		  {
		    m->addSequence (RnamlWriter::toSequence (*seqIt));
		  }
	      }
	    s = new rnaml::Structure ();
	    model = RnamlWriter::toRnaml (*molIt);
	    model->setId ("model1");
	    s->addModel (model);
	    m->setStructure (s);
	    oss.str ("");	    
	    oss << "molecule" << moleculeIndex;
	    m->setId (oss.str ().c_str ());
	    rnaml.addChild (m);
	  }
	marshaller.setValidating (true);
	marshaller.setFormatted (true);
	marshaller.marshall (rnaml, *ps);
      }
  }
}
