//                              -*- Mode: C++ -*- 
// OrientedGraph.cc
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 17 15:20:36 2004
// $Revision: 1.2.4.1 $
// $Id: OrientedGraph.cc,v 1.2.4.1 2006-03-24 18:42:40 larosem Exp $
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
#include <list>
#include <vector>

#include "Messagestream.h"
#include "OrientedGraph.h"
#include "stlio.h"

using namespace mccore;
using namespace std;



int
main (int argc, char *argv[])
{
  typedef OrientedGraph< int, int, int, float > OGraph;
  OGraph graph;
  OGraph::iterator it;
  OGraph::const_iterator cit;
  OGraph::vweight_iterator vwit;
  OGraph::vweight_const_iterator vwcit;
  OGraph::edge_iterator eit;
  OGraph::edge_const_iterator ecit;
  OGraph::eweight_iterator ewit;
  OGraph::eweight_const_iterator ewcit;
  int v1;
  int v2;
  int v3;
  float v4;
  OGraph::label i1;
  OGraph::label i2;
  OGraph::edge_label e1;
  OGraph *clone;
  vector< int > c;
  list< int > vertices;
  list< OGraph::label > labels;
	    
  // New graph
  gOut (0) << "Empty oriented graph"
	   << endl << graph << endl;

  // Add a few nodes
  graph.insert (1);
  graph.insert (123);
  graph.insert (1);
  graph.insert (3, 1000);
  graph.insert (4, 1001);
  graph.insert (5, 1002);
  graph.connect (3, 1, 50, 2000);
  graph.connect (4, 5, 51, 2001);
  graph.connect (5, 5, 52, 2002);
  graph.connect (5, 4, 53, 2003);
  gOut (0) << "Initial state" << endl << graph << endl;
  
  // Testing copy constructor.
  OGraph other (graph);
  gOut (0) << "Copy constructor" << endl;
  gOut (0) << other << endl;

  // Testing clone
  gOut (0) << "Cloning graph" << endl;
  clone = (OGraph*) graph.cloneGraph ();
  gOut (0) << *clone << endl;

  // Testing operator==
  gOut (0) << "operator== on copy constructed graph with return value "
	   << flush;
  gOut (0) << (graph == other)
	   << endl << graph << endl;

  gOut (0) << "operator== on cloned graph with return value "
	   << flush;
  gOut (0) << (graph == *clone)
	   << endl << graph << endl;
  delete clone;

  // Testing operator=
  other = graph;
  gOut (0) << "operator== on assigned graph with return value "
	   << flush;
  gOut (0) << (graph == other)
	   << endl << graph << endl;
  
  // Testing operator!=
  gOut (0) << "operator!= on assigned graph with return value "
	   << flush;
  gOut (0) << (graph != other)
	   << endl << graph << endl;
  
  // Adding an int Collection.
  gOut (0) << "insert (2, 124, 124) " << flush;
  c.push_back (2);
  c.push_back (124);
  c.push_back (124);
  graph.insertRange (c.begin (), c.end ());
  gOut (0) << endl << graph << endl;
	
  // Testing insert with weight
  v1 = 125;
  v2 = 1000;
  gOut (0) << "insert (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.insert (v1, v2)
	   << endl << graph << endl;

  const OGraph constGraph (graph);

  // Testing find
  v1 = graph.size ();
  gOut (0) << "find (" << v1 << ") with return value "
	   << flush;
  it = graph.find (v1);
  if (graph.end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 5;
  gOut (0) << "find (" << v1 << ") with return value "
	   << flush;
  it = graph.find (v1);
  if (graph.end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = constGraph.size ();
  gOut (0) << "find (" << v1 << ") on const graph with return value "
	   << flush;
  cit = constGraph.find (v1);
  if (constGraph.end () != cit)
    {
      gOut (0) << *cit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  v1 = 5;
  gOut (0) << "find (" << v1 << ") on const graph with return value "
	   << flush;
  cit = constGraph.find (v1);
  if (graph.end () != cit)
    {
      gOut (0) << *cit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  // Testing findWeight
  v1 = 125;
  gOut (0) << "findWeight (" << v1 << ") with return value "
	   << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () == vwit)
    {
      gOut (0) << "not found";
    }
  else
    {
      gOut (0) << *vwit;
    }
  gOut (0) << endl << graph << endl;

  v1 = 43233;
  gOut (0) << "findWeight (" << v1 << ") with return value " << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () == vwit)
    {
      gOut (0) << "not found";
    }
  else
    {
      gOut (0) << *vwit;
    }
  gOut (0) << endl << graph << endl;

  v1 = 43233;
  gOut (0) << "findWeight (" << v1 << ") on const graph with return value "
	   << flush;
  vwcit = constGraph.findWeight (v1);
  if (constGraph.vweight_end () == vwcit)
    {
      gOut (0) << "not found";
    }
  else
    {
      gOut (0) << *vwcit;
    }
  gOut (0) << endl << constGraph << endl;
  
  v1 = 125;
  gOut (0) << "findWeight (" << v1 << ") on graph with return value "
	   << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () == vwit)
    {
      gOut (0) << "not found";
    }
  else
    {
      gOut (0) << *vwit;
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 125;
  gOut (0) << "findWeight (" << v1 << ") on const graph with return value "
	   << flush;
  vwcit = constGraph.findWeight (v1);
  if (constGraph.vweight_end () == vwcit)
    {
      gOut (0) << "not found";
    }
  else
    {
      gOut (0) << *vwcit;
    }
  gOut (0) << endl << constGraph << endl;
  
  // Testing set findWeight
  v1 = 125;
  v2 = 1001;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ") " << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v2;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 43233;
  v2 = 1006;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ") " << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v2;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 125;
  v2 = 1006;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ")" << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v2;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = graph.size ();
  v2 = 1007;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ") " << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v2;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 43233;
  v2 = 1007;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ") " << flush;
  vwit = graph.findWeight (v1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v2;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  // Testing find
  v1 = 123;
  v2 = 123;
  gOut (0) << "find (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  eit = graph.find (v1, v2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 202;
  v2 = 200;
  gOut (0) << "find (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  eit = graph.find (v1, v2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 3;
  v2 = 1;
  gOut (0) << "find (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  eit = graph.find (v1, v2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 4;
  v2 = 5;
  gOut (0) << "find (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  eit = graph.find (v1, v2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 5;
  v2 = 5;
  gOut (0) << "find (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  eit = graph.find (v1, v2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 5;
  v2 = 5;
  gOut (0) << "find (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.find (v1, v2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  v1 = 5;
  v2 = 4;
  gOut (0) << "find (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.find (v1, v2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  v1 = 124;
  v2 = 1;
  gOut (0) << "find (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.find (v1, v2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  // Testing findWeight
  v1 = 123;
  v2 = 123;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 202;
  v2 = 200;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 5;
  v2 = 4;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  v1 = 123;
  v2 = 123;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.findWeight (v1, v2);
  if (constGraph.eweight_end () != ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  v1 = 202;
  v2 = 200;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.findWeight (v1, v2);
  if (constGraph.eweight_end () != ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  v1 = 5;
  v2 = 4;
  gOut (0) << "findWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.findWeight (v1, v2);
  if (constGraph.eweight_end () != ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  // Testing set findWeight
  v1 = 123;
  v2 = 123;
  v4 = 5.1;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 123;
  v2 = 1;
  v4 = 5.2;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 4;
  v2 = 5;
  v4 = 5.3;
  gOut (0) << "set findWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.findWeight (v1, v2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  // Testing getVertexLabel
  v1 = 43233;
  gOut (0) << "getVertexLabel (" << v1 << ") with return value " << flush;
  i1 = graph.getVertexLabel (v1);
  if (graph.size () > i1)
    {
      gOut (0) << i1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  v1 = 124;
  gOut (0) << "getVertexLabel (" << v1 << ") with return value " << flush;
  i1 = graph.getVertexLabel (v1);
  if (graph.size () > i1)
    {
      gOut (0) << i1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  // Testing areConnected
  v1 = 231553;
  v2 = 125;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;

  v1 = 125;
  v2 = 231553;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;

  v1 = 1;
  v2 = 125;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;
  
  v1 = 125;
  v2 = 1;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;

  v1 = 5;
  v2 = 5;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;

  v1 = 5;
  v2 = 4;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;

  v1 = 4;
  v2 = 5;
  gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.areConnected (v1, v2)
	   << endl << graph << endl;
  
  v1 = 124;
  v2 = 5;
  v3 = 2000;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  v1 = 5;
  v2 = 2;
  v3 = 2000;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
  
  // Testing neighborhood
  v1 = 1200;
  gOut (0) << "neighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.neighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;
  
  v1 = 201;
  gOut (0) << "neighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.neighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  v1 = 5;
  gOut (0) << "neighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.neighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;
  
  v1 = 202;
  gOut (0) << "neighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.neighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  // Testing neighborhood Index (int)
  i1 = graph.size ();
  gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	   << flush;
  labels = graph.internalNeighborhood (i1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  i1 = 324324;
  gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	   << flush;
  labels = graph.internalNeighborhood (i1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  i1 = 6;
  gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	   << flush;
  labels = graph.internalNeighborhood (i1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  i1 = 4;
  gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	   << flush;
  labels = graph.internalNeighborhood (i1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;
  
  i1 = 7;
  gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	   << flush;
  labels = graph.internalNeighborhood (i1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;
  
  // Testing inNeighborhood
  v1 = 12432;
  gOut (0) << "inNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.inNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  v1 = 5;
  gOut (0) << "inNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.inNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  v1 = 4;
  gOut (0) << "inNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.inNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  // Testing outNeighborhood
  v1 = 12432;
  gOut (0) << "outNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.outNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  v1 = 5;
  gOut (0) << "outNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.outNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  v1 = 4;
  gOut (0) << "outNeighborhood (" << v1 << ") with return value "
	   << flush;
  vertices = graph.outNeighborhood (v1);
  vertices.sort ();
  gOut (0) << vertices
	   << endl << graph << endl;

  // Testing internalInNeighborhood
  v1 = 12432;
  gOut (0) << "internalInNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalInNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  v1 = 5;
  gOut (0) << "internalInNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalInNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  v1 = 4;
  gOut (0) << "internalInNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalInNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  // Testing internalOutNeighborhood
  v1 = 12432;
  gOut (0) << "internalOutNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalOutNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  v1 = 5;
  gOut (0) << "internalOutNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalOutNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;

  v1 = 4;
  gOut (0) << "internalOutNeighborhood (" << v1 << ") with return value "
	   << flush;
  labels = graph.internalOutNeighborhood (v1);
  labels.sort ();
  gOut (0) << labels
	   << endl << graph << endl;
  
  // Testing internalFind
  i1 = graph.size ();
  gOut (0) << "internalFind (" << i1 << ") with return value "
	   << flush;
  it = graph.internalFind (i1);
  if (graph.end () != it)
    {
      gOut << *it;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 324324;
  gOut (0) << "internalFind (" << i1 << ") with return value "
	   << flush;
  it = graph.internalFind (i1);
  if (graph.end () != it)
    {
      gOut << *it;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 4;
  gOut (0) << "internalFind (" << i1 << ") with return value "
	   << flush;
  it = graph.internalFind (i1);
  if (graph.end () != it)
    {
      gOut << *it;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = graph.size ();
  gOut (0) << "internalFind (" << i1 << ") on const graph with return value "
	   << flush;
  cit = constGraph.internalFind (i1);
  if (constGraph.end () != cit)
    {
      gOut << *cit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 324324;
  gOut (0) << "internalFind (" << i1 << ") on const graph with return value "
	   << flush;
  cit = constGraph.internalFind (i1);
  if (constGraph.end () != cit)
    {
      gOut << *cit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 4;
  gOut (0) << "internalFind (" << i1 << ") on const graph with return value "
	   << flush;
  cit = constGraph.internalFind (i1);
  if (constGraph.end () != cit)
    {
      gOut << *cit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  // Testing internalFindWeight
  i1 = graph.size ();
  gOut (0) << "internalFindWeight (" << i1 << ") with return value "
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      gOut << *vwit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  i1 = 43233;
  gOut (0) << "internalFindWeight (" << i1 << ") with return value "
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      gOut << *vwit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 6;
  gOut (0) << "internalFindWeight (" << i1 << ") with return value "
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      gOut << *vwit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = constGraph.size ();
  gOut (0) << "internalFindWeight (" << i1 << ") on const graph with return value "
	   << flush;
  vwcit = constGraph.internalFindWeight (i1);
  if (constGraph.vweight_end () != vwcit)
    {
      gOut << *vwcit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 43233;
  gOut (0) << "internalFindWeight (" << i1 << ") on const graph with return value "
	   << flush;
  vwcit = constGraph.internalFindWeight (i1);
  if (constGraph.vweight_end () != vwcit)
    {
      gOut << *vwcit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 6;
  gOut (0) << "internalFindWeight (" << i1 << ") on const graph with return value "
	   << flush;
  vwcit = constGraph.internalFindWeight (i1);
  if (constGraph.vweight_end () != vwcit)
    {
      gOut << *vwcit;
    }
  else
    {
      gOut << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  // Testing set internalFindWeight
  i1 = 6;
  v1 = 1007;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << v1 << ")"
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v1;
    }
  else
    {
      gOut << " not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = graph.size ();
  v1 = 1008;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << v1 << ")"
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v1;
    }
  else
    {
      gOut << " not found";
    }
  gOut (0) << endl << graph << endl;
  
  i1 = 0;
  v1 = 1009;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << v1 << ")"
	   << flush;
  vwit = graph.internalFindWeight (i1);
  if (graph.vweight_end () != vwit)
    {
      *vwit = v1;
    }
  else
    {
      gOut << " not found";
    }
  gOut (0) << endl << graph << endl;

  // Testing internalFind
  i1 = graph.size ();
  i2 = 8; 
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  eit = graph.internalFind (i1, i2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 2;
  i2 = 8; 
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  eit = graph.internalFind (i1, i2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  i1 = 2;
  i2 = 0;
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  eit = graph.internalFind (i1, i2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 4;
  i2 = 5;
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  eit = graph.internalFind (i1, i2);
  if (graph.edge_end () != eit)
    {
      gOut (0) << *eit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  i1 = constGraph.size ();
  i2 = 8; 
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.internalFind (i1, i2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  i1 = 2;
  i2 = 8; 
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.internalFind (i1, i2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 2;
  i2 = 0;
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.internalFind (i1, i2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 6;
  i2 = 4;
  gOut (0) << "internalFind (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ecit = constGraph.internalFind (i1, i2);
  if (constGraph.edge_end () != ecit)
    {
      gOut (0) << *ecit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  // Testing internalGetEdgeLabel
  i1 = graph.size ();
  i2 = 8; 
  gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  e1 = graph.internalGetEdgeLabel (i1, i2);
  if (graph.edgeSize () > e1)
    {
      gOut (0) << e1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 2;
  i2 = 8; 
  gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  e1 = graph.internalGetEdgeLabel (i1, i2);
  if (graph.edgeSize () > e1)
    {
      gOut (0) << e1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 3;
  i2 = 4;
  gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  e1 = graph.internalGetEdgeLabel (i1, i2);
  if (graph.edgeSize () > e1)
    {
      gOut (0) << e1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  e1 = graph.internalGetEdgeLabel (i1, i2);
  if (graph.edgeSize () > e1)
    {
      gOut (0) << e1;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  // Testing internalFindWeight
  i1 = graph.size ();
  i2 = 8;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 2;
  i2 = 8;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 4;
  i2 = 3;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = constGraph.size ();
  i2 = 8;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindWeight (i1, i2);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 2;
  i2 = 8;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindWeight (i1, i2);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 4;
  i2 = 3;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindWeight (i1, i2);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  i1 = 7;
  i2 = 7;
  gOut (0) << "internalFindWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindWeight (i1, i2);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  e1 = graph.edgeSize ();
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") with return value "
	   << flush;
  ewit = graph.internalFindEdgeWeight (e1);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  e1 = 0;
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") with return value "
	   << flush;
  ewit = graph.internalFindEdgeWeight (e1);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  e1 = 5;
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") with return value "
	   << flush;
  ewit = graph.internalFindEdgeWeight (e1);
  if (graph.eweight_end () > ewit)
    {
      gOut (0) << *ewit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  e1 = constGraph.size ();
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindEdgeWeight (e1);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  e1 = 0;
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindEdgeWeight (e1);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;

  e1 = 5;
  gOut (0) << "internalFindEdgeWeight (" << e1 << ") on const graph with return value "
	   << flush;
  ewcit = constGraph.internalFindEdgeWeight (e1);
  if (constGraph.eweight_end () > ewcit)
    {
      gOut (0) << *ewcit;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << constGraph << endl;
  
  // Testing set internalFindWeight
  i1 = graph.size ();
  i2 = 8;
  v4 = 5.6;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 2;
  i2 = 3;
  v4 = 5.7;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;

  i1 = 4;
  i2 = 4;
  v4 = 5.8;
  gOut (0) << "set internalFindWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	   << flush;
  ewit = graph.internalFindWeight (i1, i2);
  if (graph.eweight_end () != ewit)
    {
      *ewit = v4;
    }
  else
    {
      gOut (0) << "not found";
    }
  gOut (0) << endl << graph << endl;
  
  // Testing internalContains
  i1 = graph.size ();
  gOut (0) << "internalContains (" << i1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalContains (i1)
	   << endl << graph << endl;

  i1 = 234;
  gOut (0) << "internalContains (" << i1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalContains (i1)
	   << endl << graph << endl;

  i1 = 5;
  gOut (0) << "internalContains (" << i1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalContains (i1)
	   << endl << graph << endl;

  // Testing internalAreConnected
  i1 = graph.size ();
  i2 = 7;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 7;
  i2 = graph.size ();
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 1;
  i2 = 2144321;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 2;
  i2 = 4;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 4;
  i2 = 2;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 5;
  i2 = 0;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalAreConnected (i1, i2)
	   << endl << graph << endl;

  // Iterators
  gOut (0) << "Iteration on iterator with return value"
	   << flush;
  for (it = graph.begin (); graph.end () != it; ++it)
    {
      gOut (0) << " " << *it;
    }
  gOut (0) << endl << graph << endl;
  gOut (0) << "Iteration on const_iterator with return value"
	   << flush;
  for (cit = constGraph.begin (); constGraph.end () != cit; ++cit)
    {
      gOut (0) << " " << *cit;
    }
  gOut (0) << endl << constGraph << endl;

  gOut (0) << "Iteration on edge_iterator with return value"
	   << flush;
  for (eit = graph.edge_begin (); graph.edge_end () != eit; ++eit)
    {
      gOut (0) << " " << *eit;
    }
  gOut (0) << endl << graph << endl;
  gOut (0) << "Iteration on edge_const_iterator with return value"
	   << flush;
  for (ecit = constGraph.edge_begin (); constGraph.edge_end () != ecit; ++ecit)
    {
      gOut (0) << " " << *ecit;
    }
  gOut (0) << endl << constGraph << endl;

  gOut (0) << "Iteration on vweight_iterator with return value"
	   << flush;
  for (vwit = graph.vweight_begin (); graph.vweight_end () != vwit; ++vwit)
    {
      gOut (0) << " " << *vwit;
    }
  gOut (0) << endl << graph << endl;
  gOut (0) << "Iteration on vweight_const_iterator with return value"
	   << flush;
  for (vwcit = constGraph.vweight_begin (); constGraph.vweight_end () != vwcit; ++vwcit)
    {
      gOut (0) << " " << *vwcit;
    }
  gOut (0) << endl << constGraph << endl;

  gOut (0) << "Iteration on eweight_iterator with return value"
	   << flush;
  for (ewit = graph.eweight_begin (); graph.eweight_end () != ewit; ++ewit)
    {
      gOut (0) << " " << *ewit;
    }
  gOut (0) << endl << graph << endl;
  gOut (0) << "Iteration on eweight_const_iterator with return value"
	   << flush;
  for (ewcit = constGraph.eweight_begin (); constGraph.eweight_end () != ewcit; ++ewcit)
    {
      gOut (0) << " " << *ewcit;
    }
  gOut (0) << endl << constGraph << endl;

  // Testing erase
  clone = (OGraph*) graph.cloneGraph ();
  v1 = 125;
  gOut (0) << "erase (" << v1 << ") with return value "
	   << flush;
  it = clone->erase (v1);
  if (clone->end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "end ()";
    }
  gOut (0) << endl << *clone << endl << graph << endl;

  v1 = 3;
  gOut (0) << "erase (" << v1 << ") with return value "
	   << flush;
  it = clone->erase (v1);
  if (clone->end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "end ()";
    }
  gOut (0) << endl << *clone << endl << graph << endl;

  // Testing internalErase
  i1 = 1;
  gOut (0) << "internalErase (" << i1 << ") with return value "
	   << flush;
  it = clone->internalErase (i1);
  if (clone->end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "end ()";
    }
  gOut (0) << endl << *clone << endl << graph << endl;

  i1 = 2;
  gOut (0) << "internalErase (" << i1 << ") with return value "
	   << flush;
  it = clone->internalErase (i1);
  if (clone->end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "end ()";
    }
  gOut (0) << endl << *clone << endl << graph << endl;

  i1 = 321532432;
  gOut (0) << "internalErase (" << i1 << ") with return value "
	   << flush;
  it = clone->internalErase (i1);
  if (clone->end () != it)
    {
      gOut (0) << *it;
    }
  else
    {
      gOut (0) << "end ()";
    }
  gOut (0) << endl << *clone << endl << graph << endl;

  // Testing size
  gOut (0) << "size () with return value "
	   << flush;
  gOut (0) << graph.size ()
	   << endl << graph << endl;

  // Testing edgeSize
  gOut (0) << "edgeSize () with return value "
	   << flush;
  gOut (0) << graph.edgeSize ()
	   << endl << graph << endl;

  // Testing empty 
  gOut (0) << "empty () with return value "
	   << flush;
  gOut (0) << graph.empty ()
	   << endl << graph << endl;

  // Testing clear
  gOut (0) << "clear () " << flush;
  clone->clear ();
  gOut (0) << endl << *clone << endl;
  
  // Testing empty 
  gOut (0) << "empty () with return value "
	   << flush;
  gOut (0) << clone->empty ()
	   << endl << *clone << endl;
  
  // Testing connect
  v1 = 1;
  v2 = 5;
  v3 = 2000;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  v1 = 5;
  v2 = 1;
  v3 = 2001;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
  
  v1 = 125;
  v2 = 2;
  v3 = 2002;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  v1 = 1;
  v2 = 200;
  v3 = 2003;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  v1 = 2;
  v2 = 125;
  v3 = 2004;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  v1 = 1;
  v2 = 123;
  v3 = 2005;
  gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	   << flush;
  gOut (0) << graph.connect (v1, v2, v3)
	   << endl << graph << endl;

  // Testing internalConnect
  i1 = graph.size ();
  i2 = 7;
  v1 = 2006;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;

  i1 = 7;
  i2 = graph.size ();
  v1 = 2006;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  v1 = 2007;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;

  i1 = 1;
  i2 = 7;
  v1 = 2008;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;

  // Testing internalConnect
  i1 = graph.size ();
  i2 = 7;
  v1 = 2004;
  v4 = 5.7;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;

  i1 = 7;
  i2 = graph.size ();
  v1 = 2004;
  v4 = 5.7;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  v1 = 2004;
  v4 = 5.7;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;

  i1 = 2;
  i2 = 4;
  v1 = 2005;
  v4 = 5.8;
  gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	   << flush;
  gOut (0) << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;

  // Testing disconnect
  v1 = 200;
  v2 = 202;
  gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.disconnect (v1, v2)
	   << endl << graph << endl;

  v1 = 200;
  v2 = 200;
  gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.disconnect (v1, v2)
	   << endl << graph << endl;

  v1 = 1;
  v2 = 123;
  gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.disconnect (v1, v2)
	   << endl << graph << endl;

  v1 = 1;
  v2 = 123;
  gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	   << flush;
  gOut (0) << graph.disconnect (v1, v2)
	   << endl << graph << endl;

  // Testing internalDisconnect
  i1 = graph.size ();
  i2 = 8;
  gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalDisconnect (i1, i2)
	   << endl << graph << endl;

  i1 = 4;
  i2 = 3;
  gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalDisconnect (i1, i2)
	   << endl << graph << endl;

  i1 = 2;
  i2 = 4;
  gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalDisconnect (i1, i2)
	   << endl << graph << endl;

  i1 = 7;
  i2 = 7;
  gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	   << flush;
  gOut (0) << graph.internalDisconnect (i1, i2)
	   << endl << graph << endl;

  delete clone;
  return EXIT_SUCCESS;
}
