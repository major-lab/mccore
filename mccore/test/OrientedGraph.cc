//                              -*- Mode: C++ -*- 
// OrientedGraph.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 17 15:20:36 2004
// $Revision: 1.1.2.1 $
// $Id: OrientedGraph.cc,v 1.1.2.1 2004-12-21 19:47:46 larosem Exp $
// 


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <list>
#include <vector>

#include "mccore/Messagestream.h"
#include "mccore/OrientedGraph.h"
#include "mccore/stlio.h"

using namespace mccore;
using namespace std;



int
main (int argc, char *argv[])
{
  typedef OrientedGraph< int, int, int, float > OGraph;
  OGraph graph;
  OGraph::iterator it;
  OGraph::const_iterator cit;
  bool retval1;
  bool retval2;
  bool retval3;
  bool retval4;
  int v1;
  int v2;
  int v3;
  float v4;
  OGraph::label i1;
  OGraph::label i2;
  OGraph *clone;
  vector< int > c;
	    
  // New graph
  gOut (0) << "Empty oriented graph"
	   << endl << graph << endl;

  // Add a few nodes
  retval1 = graph.insert (1);
  retval2 = graph.insert (123);
  retval3 = graph.insert (1);
  gOut (0) << "Adding vertices 1, 123 and 1" << endl;
  gOut (0) << "   with return values " << retval1 << " " << retval2 << " " << retval3 << endl;
  gOut (0) << graph << endl;

  gOut (0) << "Adding vertices 3, 4, 5 with weights 1000, 1001, 1002" << endl;
  retval1 = graph.insert (3, 1000);
  retval2 = graph.insert (4, 1001);
  retval3 = graph.insert (5, 1002);
  gOut (0) << "   with return values " << retval1 << " " << retval2 << " " << retval3 << endl;
  gOut (0) << graph << endl;

  gOut (0) << "Adding edges (3, 1, 50, 2000), (4, 5, 51, 2001), (5, 5, 52, 2002), (5, 4, 53, 2003)" << endl;
  retval1 = graph.connect (3, 1, 50, 2000);
  retval2 = graph.connect (4, 5, 51, 2001);
  retval3 = graph.connect (5, 5, 52, 2002);
  retval4 = graph.connect (5, 4, 53, 2003);
  gOut (0) << "   with return values " << retval1 << " " << retval2 << " " << retval3 << " " << retval4 << endl;
  gOut (0) << graph << endl;
  
  // Testing copy constructor.
  OGraph other (graph);
  gOut (0) << "Copy constructor" << endl;
  gOut (0) << other << endl;

  // Testing clone
  gOut (0) << "Cloning graph" << endl;
  clone = (OGraph*) graph.cloneGraph ();
  gOut (0) << *clone << endl;

  // Testing operator==
  gOut (0) << "Testing operator== on copy constructed graph" << endl
	   << "    with return value " << (graph == other) << endl;
  gOut (0) << "Testing operator== on cloned graph" << endl
	   << "    with return value " << (graph == *clone) << endl;

  delete clone;

  // Testing operator=
  other = graph;
  gOut (0) << "Testing operator== on assigned graph" << endl
	   << "    with return value " << (graph == other) << endl;
  
  // Adding an int Collection.
  gOut (0) << "Adding an range of vertices 2, 124 and 124" << endl;

  c.push_back (2);
  c.push_back (124);
  c.push_back (124);
  graph.insertRange (c.begin (), c.end ());
  gOut (0) << graph << endl;
	
  // Testing insert with weight
  gOut (0) << "Adding 125 with weight 1000" << endl;
  retval1 = graph.insert (125, 1000);
  gOut (0) << "     with return value " << retval1 << endl;
  gOut (0) << graph << endl;

  // Testing getVertexWeight
  const OGraph constGraph (graph);
  
  gOut (0) << "Getting vertex weight (125, 1000)" << endl;
  gOut (0) << "     with return value " << graph.getVertexWeight (125) << endl;
  try
    {
      v1 = 43233;
      gOut (0) << "Getting vertex weight (43233)" << endl
	       << "     with return value " << flush
	       << graph.getVertexWeight (v1) << endl;
      gOut (0) << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 43233;
      gOut (0) << "Getting vertex weight (43233) on const graph" << endl
	       << "     with return value " << flush
	       << constGraph.getVertexWeight (v1)
	       << endl;
      gOut (0) << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  v1 = 125;
  gOut (0) << "Getting vertex weight (" << v1 << ")" << endl
	   << "     with return value " << graph.getVertexWeight (v1)
	   << endl;
  gOut (0) << graph << endl;
  gOut (0) << "Getting vertex weight (125, 1000) on const graph" << endl;
  gOut (0) << "     with return value " << constGraph.getVertexWeight (125)
	   << endl;

  // Testing setVertexWeight
  v1 = 125;
  v2 = 1001;
  gOut (0) << "Setting vertex weight (" << v1 << ", " << v2 << ")" << endl;
  graph.setVertexWeight (125, 1001);
  gOut (0) << graph << endl;
  try
    {
      v1 = 43233;
      v2 = 1006;
      gOut (0) << "Setting vertex weight (" << v1 << ", " << v2 << ") " << flush;
      graph.setVertexWeight (v1, v2);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  v1 = 125;
  v2 = 1006;
      gOut (0) << "Setting vertex weight (" << v1 << ", " << v2 << ")" << endl;
      graph.setVertexWeight (v1, v2);
      gOut (0) << graph << endl;
  try
    {
      v1 = graph.size ();
      v2 = 1007;
      gOut (0) << "Setting vertex weight (" << v1 << ", " << v2 << ") " << flush;
      graph.setVertexWeight (v1, v2);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 43233;
      v2 = 1007;
      gOut (0) << "Setting vertex weight (" << v1 << ", " << v2 << ") " << flush;
      graph.setVertexWeight (v1, v2);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing getEdge
  try
    {
      v1 = 123;
      v2 = 123;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdge (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 202;
      v2 = 200;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdge (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 3;
      v2 = 1;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdge (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 4;
      v2 = 5;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdge (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 5;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdge (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 5;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdge (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 4;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdge (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 124;
      v2 = 1;
      gOut (0) << "Getting edge (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdge (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing getEdgeWeight
  try
    {
      v1 = 123;
      v2 = 123;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdgeWeight (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 202;
      v2 = 200;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getEdgeWeight (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 4;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdgeWeight (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 123;
      v2 = 123;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdgeWeight (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 202;
      v2 = 200;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdgeWeight (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 4;
      gOut (0) << "Getting edge weight (" << v1 << ", " << v2 << ") on const graph" << endl
	       << "     with return value " << flush;
      gOut (0) << constGraph.getEdgeWeight (v1, v2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing setEdgeWeight
  try
    {
      v1 = 123;
      v2 = 123;
      v4 = 5.1;
      gOut (0) << "Setting edge weight (" << v1 << ", " << v2 << ", " << v4 << ") " << flush;
      graph.setEdgeWeight (v1, v2, v4);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 123;
      v2 = 1;
      v4 = 5.2;
      gOut (0) << "Setting edge weight (" << v1 << ", " << v2 << ", " << v4 << ") " << flush;
      graph.setEdgeWeight (v1, v2, v4);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 4;
      v2 = 5;
      v4 = 5.3;
      gOut (0) << "Setting edge weight (" << v1 << ", " << v2 << ", " << v4 << ") " << flush;
      graph.setEdgeWeight (v1, v2, v4);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing getVertexLabel
  try
    {
      v1 = 43233;
      gOut (0) << "Getting vertex label (" << v1 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getVertexLabel (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 124;
      gOut (0) << "Getting vertex label (" << v1 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.getVertexLabel (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing areConnected
  try
    {
      v1 = 231553;
      v2 = 125;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      v2 = 231553;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 1;
      v2 = 125;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      v2 = 1;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 5;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 4;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 4;
      v2 = 5;
      gOut (0) << "Are connected (" << v1 << ", " << v2 << ")" << endl
	       << "     with return value " << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing neighborhood
  v1 = 1200;
  gOut (0) << "Getting neighborhood (" << v1 << ")" << endl
	   << "     with return value " << graph.neighborhood (v1)
	   << endl << graph << endl;
  v1 = 201;
  gOut (0) << "Getting neighborhood (" << v1 << ")" << endl
	   << "     with return value " << graph.neighborhood (v1)
	   << endl << graph << endl;
  v1 = 5;
  gOut (0) << "Getting neighborhood (" << v1 << ")" << endl
	   << "     with return value " << graph.neighborhood (v1)
	   << endl << graph << endl;
  v1 = 202;
  gOut (0) << "Getting neighborhood (" << v1 << ")" << endl
	   << "     with return value " << graph.neighborhood (v1)
	   << endl << graph << endl;

  // Testing neighborhood Index (int)
  i1 = graph.size ();
  gOut (0) << "Getting internalNeighborhood (" << i1 << ")" << endl
	   << "     with return value " << graph.internalNeighborhood (i1)
	   << endl << graph << endl;
  i1 = 324324;
  gOut (0) << "Getting internalNeighborhood (" << i1 << ")" << endl
	   << "     with return value " << graph.internalNeighborhood (i1)
	   << endl << graph << endl;
  i1 = 6;
  gOut (0) << "Getting internalNeighborhood (" << i1 << ")" << endl
	   << "     with return value " << graph.internalNeighborhood (i1)
	   << endl << graph << endl;
  i1 = 4;
  gOut (0) << "Getting internalNeighborhood (" << i1 << ")" << endl
	   << "     with return value " << graph.internalNeighborhood (i1)
	   << endl << graph << endl;
  i1 = 7;
  gOut (0) << "Getting internalNeighborhood (" << i1 << ")" << endl
	   << "     with return value " << graph.internalNeighborhood (i1)
	   << endl << graph << endl;

  // Testing internalGetVertex
  try
    {
      i1 = graph.size ();
      gOut (0) << "Getting vertex from label (" << i1 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.internalGetVertex (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 324324;
      gOut (0) << "Getting vertex from label (" << i1 << ")" << endl
	       << "     with return value " << flush;
      gOut (0) << graph.internalGetVertex (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      gOut (0) << "Getting vertex from label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetVertex (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = graph.size ();
      gOut (0) << "Getting vertex from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertex (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 324324;
      gOut (0) << "Getting vertex from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertex (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      gOut (0) << "Getting vertex from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertex (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalGetVertexWeight
  try
    {
      i1 = graph.size ();
      gOut (0) << "Getting vertex weight from label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 43233;
      gOut (0) << "Getting vertex weight from label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      gOut (0) << "Getting vertex weight from label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      gOut (0) << "Getting vertex weight from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertexWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 43233;
      gOut (0) << "Getting vertex weight from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertexWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      gOut (0) << "Getting vertex weight from label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetVertexWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalSetVertexWeight
  try
    {
      i1 = 6;
      v1 = 1007;
      gOut (0) << "Setting vertex weight from label (" << i1 << ", " << v1 << ")" << endl;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = graph.size ();
      v1 = 1008;
      gOut (0) << "Setting vertex weight from label (" << i1 << ", " << v1 << ")" << endl;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      v1 = 1009;
      gOut (0) << "Setting vertex weight from label (" << i1 << ", " << v1 << ")" << endl;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << "     with return value " << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalGetEdge
  try
    {
      i1 = graph.size ();
      i2 = 8; 
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8; 
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      i2 = 8; 
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ") on const graph"
	       << "     with return value " << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8; 
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ") on const graph"
	       << "     with return value " << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ") on const graph"
	       << "     with return value " << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Getting edge of endvertices (" << i1 << ", " << i2 << ") on const graph"
	       << "     with return value " << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalGetEdgeLabel
  try
    {
      i1 = graph.size ();
      i2 = 8; 
      gOut (0) << "Getting edge label of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8; 
      gOut (0) << "Getting edge label of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Getting edge label of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Getting edge label of endvertices (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalGetEdgeWeight
  try
    {
      i1 = graph.size ();
      i2 = 8;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      i2 = 8;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Getting edge weight of endvertices (" << i1 << ", " << i2 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalGetEdgeWeight
  try
    {
      i1 = graph.size ();
      gOut (0) << "Getting edge weight of edge label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      gOut (0) << "Getting edge weight of edge label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "Getting edge weight of edge label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      gOut (0) << "Getting edge weight of edge label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      gOut (0) << "Getting edge weight of edge label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "Getting edge weight of edge label (" << i1 << ") on const graph" << endl
	       << "     with return value " << constGraph.internalGetEdgeWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Testing internalSetEdgeWeight
  try
    {
      i1 = graph.size ();
      i2 = 8;
      v4 = 5.6;
      gOut (0) << "Setting edge weight of edge endvertices labels (" << i1 << ", " << i2 << ", " << v4 << ")" << endl;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 8;
      i2 = graph.size ();
      v4 = 5.7;
      gOut (0) << "Setting edge weight of edge endvertices labels (" << i1 << ", " << i2 << ", " << v4 << ")" << endl;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 8;
      i2 = 4;
      v4 = 5.8;
      gOut (0) << "Setting edge weight of edge endvertices labels (" << i1 << ", " << i2 << ", " << v4 << ")" << endl;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << "     with return value " << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalContains
  try
    {
      i1 = graph.size ();
      gOut (0) << "Contains vertex label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalContains (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 234;
      gOut (0) << "Contains vertex label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalContains (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "Contains vertex label (" << i1 << ")" << endl
	       << "     with return value " << graph.internalContains (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalAreConnected
  try
    {
      i1 = graph.size ();
      i2 = 7;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = graph.size ();
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 1;
      i2 = 2144321;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 2;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      i2 = 0;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Vertices labels are connected (" << i1 << ", " << i2 << ")" << endl
	       << "     with return value " << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  gOut (0) << "Testing iterator " << endl;
  for (it = graph.begin (); graph.end () != it; ++it)
    {
      gOut (0) << *it << " ";
    }
  gOut (0) << endl << graph << endl;
  gOut (0) << "Testing const_iterator " << endl;
  for (cit = constGraph.begin (); constGraph.end () != cit; ++cit)
    {
      gOut (0) << *cit << " ";
    }
  gOut (0) << endl << constGraph << endl;

  // Testing erase
  clone = (OGraph*) graph.cloneGraph ();
  try
    {
      v1 = 125;
      gOut (0) << "Erasing (" << v1 << ")" << endl
	       << "     with return value " << *(clone->erase (v1))
	       << endl << *clone
	       << endl << graph;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 321532432;
      gOut (0) << "Erasing (" << v1 << ")" << endl
	       << "     with return value " << *(clone->erase (v1))
	       << endl << *clone
	       << endl << graph;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalErase
  try
    {
      i1 = 1;
      gOut (0) << "Erasing vertex label (" << i1 << ")" << endl
	       << "     with return value " << *(clone->internalErase (i1))
	       << endl << *clone
	       << endl << graph;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 321532432;
      gOut (0) << "Erasing vertex label (" << i1 << ")" << endl
	       << "     with return value " << *(clone->internalErase (i1))
	       << endl << *clone
	       << endl << graph;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing find
  try
    {
      v1 = graph.size ();
      gOut (0) << "Finding vertex (" << v1 << ")" << endl
	       << "     with return value " << *(graph.find (v1))
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      gOut (0) << "Finding vertex (" << v1 << ")" << endl
	       << "     with return value " << *(graph.find (v1))
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = constGraph.size ();
      gOut (0) << "Finding vertex (" << v1 << ")" << endl
	       << "     with return value " << *(constGraph.find (v1))
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      gOut (0) << "Finding vertex (" << v1 << ")" << endl
	       << "     with return value " << *(constGraph.find (v1))
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing size
  gOut (0) << "Size of vertices"
	   << "     with return value " << graph.size ()
	   << endl << graph << endl;

  // Testing edgeSize
  gOut (0) << "Size of edges"
	   << "     with return value " << graph.edgeSize ()
	   << endl << graph << endl;

  // Testing empty 
  gOut (0) << "empty"
	   << "     with return value " << graph.empty ()
	   << endl << graph << endl;

  // Testing clear
  gOut (0) << "clear" << endl
	   << "     with return value ";
  clone->clear ();
  gOut (0) << endl << *clone << endl;
  
  // Testing empty 
  gOut (0) << "empty"
	   << "     with return value " << clone->empty ()
	   << endl << *clone << endl;

  // Testing connect
  try
    {
      v1 = 1;
      v2 = 5;
      v3 = 2000;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 1;
      v3 = 2001;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      v2 = 2;
      v3 = 2002;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 1;
      v2 = 200;
      v3 = 2003;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 2;
      v2 = 125;
      v3 = 2004;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 1;
      v2 = 123;
      v3 = 2005;
      gOut (0) << "Connecting vertices (" << v1 << ", " << v2 << ", " << v3 << ")" << endl
	   << "     with return value " << graph.connect (v1, v2, v3)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalConnect
  try
    {
      i1 = graph.size ();
      i2 = 7;
      v1 = 2006;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ")" << endl
	   << "     with return value " << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = graph.size ();
      v1 = 2006;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ")" << endl
	   << "     with return value " << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      v1 = 2007;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ")" << endl
	   << "     with return value " << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 1;
      i2 = 7;
      v1 = 2008;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ")" << endl
	   << "     with return value " << graph.internalConnect (i1, i2, v1)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalConnect
  try
    {
      i1 = graph.size ();
      i2 = 7;
      v1 = 2004;
      v4 = 5.7;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ")" << endl
	       << "     with return value " << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = graph.size ();
      v1 = 2004;
      v4 = 5.7;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ")" << endl
	       << "     with return value " << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      v1 = 2004;
      v4 = 5.7;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ")" << endl
	       << "     with return value " << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      v1 = 2005;
      v4 = 5.8;
      gOut (0) << "Connecting vertices labels (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ")" << endl
	       << "     with return value " << graph.internalConnect (i1, i2, v1, v4)
	   << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing disconnect
  try
    {
      v1 = 200;
      v2 = 202;
      gOut (0) << "Disconnecting (" << v1 << ", " << v2 << ")"
	       << "     with return value " << graph.disconnect (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 200;
      v2 = 200;
      gOut (0) << "Disconnecting (" << v1 << ", " << v2 << ")"
	       << "     with return value " << graph.disconnect (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 1;
      v2 = 123;
      gOut (0) << "Disconnecting (" << v1 << ", " << v2 << ")"
	       << "     with return value " << graph.disconnect (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 1;
      v2 = 123;
      gOut (0) << "Disconnecting (" << v1 << ", " << v2 << ")"
	       << "     with return value " << graph.disconnect (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalDisconnect
  try
    {
      i1 = graph.size ();
      i2 = 8;
      gOut (0) << "Disconnecting labels (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 8;
      gOut (0) << "Disconnecting labels (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 4;
      gOut (0) << "Disconnecting labels (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 7;
      gOut (0) << "Disconnecting labels (" << i1 << ", " << i2 << ")"
	       << "     with return value " << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
	
  return EXIT_SUCCESS;
}
