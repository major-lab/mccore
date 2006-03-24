//                              -*- Mode: C++ -*- 
// GraphModel.cc
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 19:34:11 2004
// $Revision: 1.16.2.1.2.1 $
// $Id: GraphModel.cc,v 1.16.2.1.2.1 2006-03-24 18:37:29 larosem Exp $
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

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "Binstream.h"
#include "Exception.h"
#include "GraphModel.h"
#include "Messagestream.h"
#include "ModelFactoryMethod.h"
#include "Molecule.h"
#include "Pdbstream.h"
#include "Relation.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"
#include "ResidueType.h"
#include "ResId.h"



namespace mccore
{

  /**
   * Base unary function used in keep.
   */
  class keepTemplate : public unary_function< ResidueType, bool >
  {
  public:
    virtual ~keepTemplate () { }
    virtual bool operator() (const ResidueType &value) const { return false; }
  };

  
  /**
   * Unary negate function.
   */
  template < class VC >
  class negate : public keepTemplate
  {
  public:
    virtual bool operator() (const ResidueType &value) const
    {
      return ! VC () (value);
    }
    
  };


  class isAminoAcid : public keepTemplate
  {
  public:
    virtual bool operator() (const ResidueType &value) const
    {
      return value.isAminoAcid ();
    }
  };


  class isNucleicAcid : public keepTemplate
  {
  public:
    virtual bool operator() (const ResidueType &value) const
    {
      return value.isNucleicAcid ();
    }
  };


  class isRNA : public keepTemplate
  {
  public:
    virtual bool operator() (const ResidueType &value) const
    {
      return value.isRNA ();
    }
  };


  class isDNA : public keepTemplate
  {
  public:
    virtual bool operator() (const ResidueType &value) const
    {
      return value.isDNA ();
    }
  };


  GraphModel::GraphModel (const AbstractModel &right, const ResidueFactoryMethod *fm)
    : AbstractModel (fm),
      annotated (false)
  {
    const GraphModel *model;

    if (0 == (model = dynamic_cast< const GraphModel* > (&right)))
      {
	AbstractModel::insert (right.begin (), right.end ());
      }
    else
      {
	annotated = model->annotated;
	deepCopy (*model);
      }
  }
  

  GraphModel::GraphModel (const GraphModel &right, const ResidueFactoryMethod *fm)
    : AbstractModel (fm),
      annotated (right.annotated)
  {
    deepCopy (right);
  }

  
  GraphModel::~GraphModel ()
  {
    vector< vertex >::iterator resIt;
    vector< edge >::iterator relIt;

    for (relIt = edges.begin (); edges.end () != relIt; ++relIt)
      {
	delete *relIt;
      }
    for (resIt = vertices.begin (); vertices.end () != resIt; ++resIt)
      {
	delete *resIt;
      }
  }


  void
  GraphModel::deepCopy (const GraphModel &right)
  {
    vector< vertex >::const_iterator resIt;
    vector< edge >::const_iterator relIt;
    set< const Residue*, less_deref< Residue > > resSet;

    for (resIt = right.vertices.begin (); right.vertices.end () != resIt; ++resIt)
      {
	vertex res = (*resIt)->clone ();
	
	graphsuper::insert (res, 0);
	resSet.insert (res);	
      }
    for (relIt = right.edges.begin (); right.edges.end () != relIt; ++relIt)
      {
	Relation *rel;

	rel = (*relIt)->clone ();
	rel->reassignResiduePointers (resSet);
	graphsuper::connect ((const vertex) rel->getRef (), (const vertex) rel->getRes (), rel, 0);
      }
  }
  
  
  GraphModel&
  GraphModel::operator= (const AbstractModel &right)
  {
    if (this != &right)
      {
	const GraphModel *model;
	
	if (0 == (model = dynamic_cast< const GraphModel* > (&right)))
	  {
	    clear ();
	    AbstractModel::operator= (right);
	    annotated = false;
	    AbstractModel::insert (right.begin (), right.end ());
	  }
	else
	  {
	    return operator= (*model);
	  }
      }
    return *this;
  }
    

  GraphModel&
  GraphModel::operator= (const GraphModel &right)
  {
    if (this != &right)
      {
	clear ();
	AbstractModel::operator= (right);
	annotated = right.annotated;
	deepCopy (right);
      }
    return *this;
  }
    

  GraphModel::iterator
  GraphModel::insert (const Residue &res, int w)
  {
    iterator found;
    vertex r;

    if (end () != (found = find (res.getResId ())))
      {
	erase (found);
      }
    r = residueFM->createResidue (res);
    graphsuper::insert (r, w);
    annotated = false;
    return graphsuper::find (r);
  }

  
  GraphModel::iterator
  GraphModel::erase (AbstractModel::iterator pos) 
  {
    vertex res = &*pos;
    iterator ret (graphsuper::erase (&*pos));

    delete res;
    return ret;
  }

  
  void
  GraphModel::sort ()
  {
    if (! empty ())
      {
	vector< vertex > sortedv = vertices;
	vector< int > newWeights (size ());
	vector< label > vmapping (size ());
	vector< edge_label > emapping (edgeSize ());
	vector< vertex >::const_iterator vit;
	edge_label ecount;
	edge_label esz = edgeSize ();

	std::sort (sortedv.begin (), sortedv.end (), less_deref< Residue > ());
	for (vit = sortedv.begin (); sortedv.end () != vit; ++vit)
	  {
	    label olabel = getVertexLabel (*vit);
	    label nlabel = vit - sortedv.begin ();
	    
	    vmapping[olabel] = nlabel;
	    newWeights[nlabel] = *internalFindWeight (olabel);
	  }
	for (ecount = 0; esz > ecount; ++ecount)
	  {
	    emapping[ecount] = ecount;
	  }
	vertices = sortedv;
	vertexWeights = newWeights;
	rebuildV2VLabel ();
	rebuildEV2ELabel (vmapping, emapping);
      }
  }
  
    
  void
  GraphModel::removeAminoAcid ()
  {
    negate< isAminoAcid > fn;
    
    keep (fn);
  }


  void
  GraphModel::removeNucleicAcid ()
  {
    negate< isNucleicAcid > fn;
    
    keep (fn);
  }


  void
  GraphModel::keepAminoAcid ()
  {
    keep (isAminoAcid ());
  }


  void
  GraphModel::keepNucleicAcid ()
  {
    keep (isNucleicAcid ());
  }


  void
  GraphModel::keepRNA ()
  {
    keep (isRNA ());
  }


  void
  GraphModel::keepDNA ()
  {
    keep (isDNA ());
  }


  void
  GraphModel::keep (const keepTemplate &is)
  {
    iterator cit;
    set< label > labelset;
      
    for (cit = begin (); end () != cit; ++cit)
      {
	if (is (*cit->getType ()))
	  {
	    labelset.insert (getVertexLabel (&*cit));
	  }
      }
    if (! labelset.empty ())
      {
	set< label >::iterator it;
	set< edge_label > edgelabelset;
	set< edge_label >::iterator eit;

	edgestodelete (labelset, edgelabelset);
	for (it = labelset.begin (); labelset.end () != it; ++it)
	  {
	    delete *internalFind (*it);
	  }
	for (eit = edgelabelset.begin (); edgelabelset.end () != eit; ++eit)
	  {
	    delete *internalFindEdge (*eit);
	  }
	internalErase (labelset, edgelabelset);
      }
  }

  
  void
  GraphModel::clear ()
  {
    graphsuper::iterator vIt;
    edge_iterator eIt;
    
    for (vIt = graphsuper::begin (); graphsuper::end () != vIt; ++vIt)
      {
	delete *vIt;
      }
    for (eIt = edge_begin (); edge_end () != eIt; ++eIt)
      {
	delete *eIt;
      }
    graphsuper::clear ();
    annotated = false;
  }


  void
  GraphModel::annotate (bool backbone)
  {
    if (! annotated)
      {
	vector< edge >::iterator eIt;
	vector< pair< AbstractModel::iterator, AbstractModel::iterator > > contacts;
	vector< pair< AbstractModel::iterator, AbstractModel::iterator > >::iterator l;

	for (eIt = edges.begin (); edges.end () != eIt; ++eIt)
	  {
	    delete *eIt;
	  }
	edges.clear ();
	ev2elabel.clear ();
	edgeWeights.clear ();

	removeWater ();
	addHLP ();
	
	contacts = Algo::extractContacts (begin (), end (), 5.0);
	gErr (3) << "Found " << contacts.size () << " possible contacts " << endl;
  
	for (l = contacts.begin (); contacts.end () != l; ++l)
	  {
	    vertex i = &*l->first;
	    vertex j = &*l->second;
	    edge rel = new Relation (i, j);

	    if (rel->annotate (backbone))
	      {
		edge inv;

		inv = rel->clone ();
		inv->invert ();
		connect (i, j, rel, 0);
		connect (j, i, inv, 0);
	      }
	    else
	      {
		delete rel;
	      }
	  }
	annotated = true;
      }
  }


//   void
//   GraphModel::fillMoleculeWithCycles (Molecule &molecule, const vector< Path< label, unsigned int > > &cycles) const
//   {
//     vector< Path< label, unsigned int > >::const_iterator cit;
//     set< const vertex, less_deref< Residue > > resCopies;

//     for (cit = cycles.begin (); cycles.end () != cit; ++cit)
//       {
// 	const Path< label, unsigned int > &cycle = *cit;
// 	Path< label, unsigned int >::const_iterator pit;
// 	GraphModel gm;
// 	AbstractModel::iterator mit;
// 	Residue *ref;
// 	label refl;

// 	molecule.insert (gm);
// 	GraphModel &model = (GraphModel&) molecule.back ();

// 	refl = cycle.back ();
// 	ref = &*(mit = model.insert (*internalGetVertex (refl), internalGetVertexWeight (refl)));
// 	resCopies.insert (ref);
// 	for (pit = cycle.begin (); cycle.end () != pit; ++pit)
// 	  {
// 	    label resl;
// 	    Residue *res;
// 	    Relation *rel;
	    
// 	    resl = *pit;
// 	    res = &*(mit = model.insert (*internalGetVertex (resl), internalGetVertexWeight (resl)));
// 	    rel = internalGetEdge (refl, resl)->clone ();
// 	    rel->reassignResiduePointers (resCopies);
// 	    model.connect (ref, res, rel, internalGetEdgeWeight (refl, resl));
// 	    refl = resl;
// 	    ref = res;
// 	  }
//       }
//   }
  

//   void
//   GraphModel::minimumCycleBasis (Molecule &molecule)
//   {
//     vector< Path< label, unsigned int > > cycles;
//     GraphModelFM gFM;
    
//     molecule.clear ();
//     molecule.setModelFM (&gFM);
//     annotate ();
//     internalMinimumCycleBasis (cycles);
//     fillMoleculeWithCycles (molecule, cycles);
//   }

  
//   void
//   GraphModel::unionMinimumCycleBases (Molecule &molecule)
//   {
//     vector< Path< label, unsigned int > > cycles;
//     GraphModelFM gFM;

//     molecule.clear ();
//     molecule.setModelFM (&gFM);
//     annotate ();
//     internalUnionMinimumCycleBases (cycles);
//     fillMoleculeWithCycles (molecule, cycles);
//   }

  
  ostream&
  GraphModel::output (ostream &os) const
  {
    const_iterator vit;
    vweight_const_iterator vwit;
    edge_label elabel;
    label rowcounter;
    label linecounter;
    label sz = size ();
    edge_label esz = edgeSize ();

    os << "[GraphModel]" << endl
       << "[Vertices]" << endl;
    for (vit = begin (), vwit = vweight_begin (), rowcounter = 0; end () != vit; ++vit, ++vwit, ++rowcounter)
      {
	os << setw (5) << rowcounter << "  " << *vit << "  " << *vwit << endl;
      }
    
    os << "[Edges]" << endl;
    for (elabel = 0; esz > elabel; ++elabel)
      {
	os << setw (5) << elabel << "  " << **internalFindEdge (elabel) << "  " << *internalFindEdgeWeight (elabel) << endl;
      }

    os << "[Adjacency matrix]" << endl;
    os << "     ";
    for (rowcounter = 0; sz > rowcounter; ++rowcounter)
      {
	os << setw (5) << rowcounter;
      }
    for (linecounter = 0; sz > linecounter; ++linecounter)
      {
	os << endl << setw (5) << linecounter;
	for (rowcounter = 0; sz > rowcounter; ++rowcounter)
	  {
	    edge_label edge;
	      
	    if (esz == (edge = internalGetEdgeLabel (linecounter, rowcounter)))
	      {
		os << setw (5) << '.';
	      }
	    else
	      {
		os << setw (5) << edge;
	      }
	  }
      }
    os << endl;      
    return os;
  }

  
  iPdbstream&
  GraphModel::input (iPdbstream &ips)
  {
    int currNb;

    clear ();
    if (! ips)
      {
	return ips;
      }
    currNb = ips.getModelNb ();
    while (! ips.eof () && currNb == ips.getModelNb ())
      {
	vertex res = getResidueFM ()->createResidue ();
	
	ips >> *res;
 	if (0 != res->size ())
	  {
	    graphsuper::insert (res, 0); 
	  }
	else
	  {
	    delete res;
	  }
      }    
    return ips;
  }
  

  iBinstream&
  GraphModel::input (iBinstream &is)
  {
    unsigned long long sz;
    map< ResId, const Residue* > resMap;

    clear ();
    is >> sz;
    for (; sz > 0; --sz)
      {
	vertex res;
	long long value;

	res = getResidueFM ()->createResidue ();
	is >> *res >> value;
	resMap.insert (make_pair (res->getResId (), res));
	graphsuper::insert (res, value);
      }
    is >> sz;
    for (; 0 < sz; --sz)
      {
	unsigned long long from;
	unsigned long long to;
	Relation *rel;
	unsigned long long value;

	is >> from >> to;
	rel = new Relation ();
	try
	  {
	    rel->read (is, resMap);
	  }
	catch (NoSuchElementException &e)
	  {
	    gErr (0) << e;
	  }
	is >> value;
	internalConnect (from, to, rel, value);
      }
    return is >> annotated;
  }
  
  
  oBinstream&
  GraphModel::output (oBinstream &os) const
  {
    unsigned long long sz = size ();
    unsigned long long esz = edgeSize ();
    label lbl;
    edge_label elabel;

    os << sz;
    for (lbl = 0; lbl < sz; ++lbl)
      {
	os << **internalFind (lbl)
	   << (long long) *internalFindWeight (lbl);
      }
    // In order to keep the binaries and graphs similar, the edges are saved
    // in their label order.
    os << esz;
    for (elabel = 0; esz > elabel; ++elabel)
      {
	const Relation &rel = **internalFindEdge (elabel);
	
	os << (unsigned long long) this->getVertexLabel ((const vertex) rel.getRef ())
	   << (unsigned long long) getVertexLabel ((const vertex) rel.getRes ());
	rel.write (os);
	os << (long long) *internalFindEdgeWeight (elabel);
      }
    return os << annotated;
  }

  
  iBinstream&
  operator>> (iBinstream &is, GraphModel &model)
  {
    return model.input (is);
  }


  oBinstream&
  operator<< (oBinstream &os, const GraphModel &model)
  {
    return model.output (os);
  }
  
}
