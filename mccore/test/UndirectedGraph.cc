//                              -*- Mode: C++ -*- 
// UndirectedGraph.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Dec 22 16:39:23 2004
// $Revision: 1.1.2.3 $
// $Id: UndirectedGraph.cc,v 1.1.2.3 2004-12-27 01:55:38 larosem Exp $
// 


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <list>
#include <vector>

#include "Messagestream.h"
#include "UndirectedGraph.h"
#include "stlio.h"

using namespace mccore;
using namespace std;



int
main (int argc, char *argv[])
{
  typedef UndirectedGraph< int, int, int, float > OGraph;
  OGraph graph;
  OGraph::iterator it;
  OGraph::const_iterator cit;
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
  try
    {
      gOut (0) << "operator== on copy constructed graph with return value "
	       << flush;
      gOut (0) << (graph == other)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }  
  try
    {
      gOut (0) << "operator== on cloned graph with return value "
	       << flush;
      gOut (0) << (graph == *clone)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  delete clone;

  // Testing operator=
  try
    {
      other = graph;
      gOut (0) << "operator== on assigned graph with return value "
	       << flush;
      gOut (0) << (graph == other)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
      
  
  // Testing operator!=
  try
    {
      gOut (0) << "operator!= on assigned graph with return value "
	       << flush;
      gOut (0) << (graph != other)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Adding an int Collection.
  try
    {
      gOut (0) << "insert (2, 124, 124) " << flush;
      c.push_back (2);
      c.push_back (124);
      c.push_back (124);
      graph.insertRange (c.begin (), c.end ());
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
	
  // Testing insert with weight
  try
    {
      v1 = 125;
      v2 = 1000;
      gOut (0) << "insert (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.insert (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing getVertexWeight
  const OGraph constGraph (graph);
  try
    {
      v1 = 125;
      gOut (0) << "getVertexWeight (" << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.getVertexWeight (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 43233;
      gOut (0) << "getVertexWeight (" << v1 << ") with return value " << flush;
      gOut (0) << graph.getVertexWeight (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 43233;
      gOut (0) << "getVertexWeight (" << v1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.getVertexWeight (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      gOut (0) << "getVertexWeight (" << v1 << ") on const graph with return value "
	       << flush;
      gOut (0) << graph.getVertexWeight (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      gOut (0) << "getVertexWeight (" << v1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.getVertexWeight (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing setVertexWeight
  try
    {
      v1 = 125;
      v2 = 1001;
      gOut (0) << "setVertexWeight (" << v1 << ", " << v2 << ") " << flush;
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
      v2 = 1006;
      gOut (0) << "setVertexWeight (" << v1 << ", " << v2 << ") " << flush;
      graph.setVertexWeight (v1, v2);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 125;
      v2 = 1006;
      gOut (0) << "setVertexWeight (" << v1 << ", " << v2 << ")" << flush;
      graph.setVertexWeight (v1, v2);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = graph.size ();
      v2 = 1007;
      gOut (0) << "setVertexWeight (" << v1 << ", " << v2 << ") " << flush;
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
      gOut (0) << "setVertexWeight (" << v1 << ", " << v2 << ") " << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "getEdge (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") with return value "
	       << flush;
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
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.getEdgeWeight (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 123;
      v2 = 123;
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "getEdgeWeight (" << v1 << ", " << v2 << ") on const graph with return value "
	       << flush;
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
      gOut (0) << "setEdgeWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	       << flush;
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
      gOut (0) << "setEdgeWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	       << flush;
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
      gOut (0) << "setEdgeWeight (" << v1 << ", " << v2 << ", " << v4 << ") "
	       << flush;
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
      gOut (0) << "getVertexLabel (" << v1 << ") with return value " << flush;
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
      gOut (0) << "getVertexLabel (" << v1 << ") with return value " << flush;
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
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
      gOut (0) << "areConnected (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.areConnected (v1, v2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  try
    {
      v1 = 124;
      v2 = 5;
      v3 = 2000;
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      v2 = 2;
      v3 = 2000;
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Testing neighborhood
  try
    {
      v1 = 1200;
      gOut (0) << "neighborhood (" << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.neighborhood (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 201;
      gOut (0) << "neighborhood (" << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.neighborhood (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      gOut (0) << "neighborhood (" << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.neighborhood (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 202;
      gOut (0) << "neighborhood (" << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.neighborhood (v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing neighborhood Index (int)
  try
    {
      i1 = graph.size ();
      gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalNeighborhood (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 324324;
      gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalNeighborhood (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalNeighborhood (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalNeighborhood (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      gOut (0) << "internalNeighborhood (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalNeighborhood (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Testing internalGetVertex
  try
    {
      i1 = graph.size ();
      gOut (0) << "internalGetVertex (" << i1 << ") with return value "
	       << flush;
      gOut (0) << flush;
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
      gOut (0) << "internalGetVertex (" << i1 << ") with return value "
	       << flush;
      gOut (0) << flush;
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
      gOut (0) << "internalGetVertex (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetVertex (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = graph.size ();
      gOut (0) << "internalGetVertex (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertex (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 324324;
      gOut (0) << "internalGetVertex (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertex (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      gOut (0) << "internalGetVertex (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertex (i1)
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
      gOut (0) << "internalGetVertexWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 43233;
      gOut (0) << "internalGetVertexWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      gOut (0) << "internalGetVertexWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetVertexWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      gOut (0) << "internalGetVertexWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertexWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 43233;
      gOut (0) << "internalGetVertexWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertexWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      gOut (0) << "internalGetVertexWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetVertexWeight (i1)
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
      gOut (0) << "internalSetVertexWeight (" << i1 << ", " << v1 << ") "
	       << flush;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = graph.size ();
      v1 = 1008;
      gOut (0) << "internalSetVertexWeight (" << i1 << ", " << v1 << ") "
	       << flush;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      v1 = 1009;
      gOut (0) << "internalSetVertexWeight (" << i1 << ", " << v1 << ") "
	       << flush;
      graph.internalSetVertexWeight (i1, v1);
      gOut (0) << endl << graph << endl;
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
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdge (i1, i2)
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
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 0;
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdge (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 5;
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdge (i1, i2)
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
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdge (i1, i2)
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
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 0;
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdge (i1, i2)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 6;
      i2 = 4;
      gOut (0) << "internalGetEdge (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdge (i1, i2)
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
      gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 2;
      i2 = 0; 
      gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeLabel (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      i2 = 2;
      gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeLabel (i1, i2)
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
      gOut (0) << "internalGetEdgeLabel (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeLabel (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 6;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 4;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ", " << i2 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1, i2)
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
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalGetEdgeWeight (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = constGraph.size ();
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 0;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1)
	       << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "internalGetEdgeWeight (" << i1 << ") on const graph with return value "
	       << flush;
      gOut (0) << constGraph.internalGetEdgeWeight (i1)
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
      gOut (0) << "internalSetEdgeWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	       << flush;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 3;
      v4 = 5.7;
      gOut (0) << "internalSetEdgeWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	       << flush;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << endl << graph << endl;
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
      gOut (0) << "internalSetEdgeWeight (" << i1 << ", " << i2 << ", " << v4 << ") "
	       << flush;
      graph.internalSetEdgeWeight (i1, i2, v4);
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalContains
  try
    {
      i1 = graph.size ();
      gOut (0) << "internalContains (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalContains (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 234;
      gOut (0) << "internalContains (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalContains (i1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 5;
      gOut (0) << "internalContains (" << i1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalContains (i1)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
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
      gOut (0) << "internalAreConnected (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalAreConnected (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Iterators
  try
    {
      it = graph.begin ();
      gOut (0) << "Iteration on iterator with return value"
	       << flush;
      for (it = graph.begin (); graph.end () != it; ++it)
	{
	  gOut (0) << " " << *it;
	}
      gOut (0) << endl << graph << endl;
      cit = constGraph.begin ();
      gOut (0) << "Iteration on const_iterator with return value"
	       << flush;
      for (cit = constGraph.begin (); constGraph.end () != cit; ++cit)
	{
	  gOut (0) << " " << *cit;
	}
      gOut (0) << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing erase
  clone = (OGraph*) graph.cloneGraph ();
  try
    {
      v1 = 125;
      gOut (0) << "erase (" << v1 << ") with return value "
	       << flush;
      it = clone->erase (v1);
      if (clone->end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << *clone << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 321532432;
      gOut (0) << "erase (" << v1 << ") with return value "
	       << flush;
      it = clone->erase (v1);
      if (clone->end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << *clone << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing internalErase
  try
    {
      i1 = 1;
      gOut (0) << "internalErase (" << i1 << ") with return value "
	       << flush;
      it = clone->internalErase (i1);
      if (clone->end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << *clone << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 321532432;
      gOut (0) << "internalErase (" << i1 << ") with return value "
	       << flush;
      it = clone->internalErase (i1);
      if (clone->end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << *clone << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing find
  try
    {
      v1 = graph.size ();
      gOut (0) << "find (" << v1 << ") with return value "
	       << flush;
      it = graph.find (v1);
      if (graph.end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      gOut (0) << "find (" << v1 << ") with return value "
	       << flush;
      it = graph.find (v1);
      if (graph.end () == it)
	gOut (0) << "end ()";
      else
	gOut (0) << *it;
      gOut (0) << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = constGraph.size ();
      gOut (0) << "find (" << v1 << ") on const graph with return value "
	       << flush;
      cit = constGraph.find (v1);
      if (constGraph.end () == cit)
	gOut (0) << "end ()";
      else
	gOut (0) << *cit;
      gOut (0) << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      v1 = 5;
      gOut (0) << "find (" << v1 << ") on const graph with return value "
	       << flush;
      cit = constGraph.find (v1);
      if (constGraph.end () == cit)
	gOut (0) << "end ()";
      else
	gOut (0) << *cit;
      gOut (0) << endl << constGraph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }

  // Testing size
  try
    {
      gOut (0) << "size () with return value "
	       << flush;
      gOut (0) << graph.size ()
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << graph << endl;
    }

  // Testing edgeSize
  try
    {
      gOut (0) << "edgeSize () with return value "
	       << flush;
      gOut (0) << graph.edgeSize ()
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << graph << endl;
    }

  // Testing empty 
  try
    {
      gOut (0) << "empty () with return value "
	       << flush;
      gOut (0) << graph.empty ()
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << graph << endl;
    }

  // Testing clear
  try
    {
      gOut (0) << "clear () " << flush;
      clone->clear ();
      gOut (0) << endl << *clone << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Testing empty 
  try
    {
      gOut (0) << "empty () with return value "
	       << flush;
      gOut (0) << clone->empty ()
	       << endl << *clone << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  
  // Testing connect
  try
    {
      v1 = 1;
      v2 = 5;
      v3 = 2000;
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "connect (" << v1 << ", " << v2 << ", " << v3 << ") with return value "
	       << flush;
      gOut (0) << graph.connect (v1, v2, v3)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 7;
      i2 = 6;
      v1 = 2007;
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1, v4)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1, v4)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1, v4)
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
      gOut (0) << "internalConnect (" << i1 << ", " << i2 << ", " << v1 << ", " << v4 << ") with return value "
	       << flush;
      gOut (0) << graph.internalConnect (i1, i2, v1, v4)
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
      gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.disconnect (v1, v2)
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
      gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.disconnect (v1, v2)
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
      gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
	       << flush;
      gOut (0) << graph.disconnect (v1, v2)
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
      gOut (0) << "disconnect (" << v1 << ", " << v2 << ") with return value "
      << flush;
      gOut (0) << graph.disconnect (v1, v2)
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
      gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
  try
    {
      i1 = 4;
      i2 = 3;
      gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalDisconnect (i1, i2)
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
      gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalDisconnect (i1, i2)
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
      gOut (0) << "internalDisconnect (" << i1 << ", " << i2 << ") with return value "
	       << flush;
      gOut (0) << graph.internalDisconnect (i1, i2)
	       << endl << graph << endl;
    }
  catch (NoSuchElementException &e)
    {
      gOut (0) << e << endl;
    }
	
  return EXIT_SUCCESS;
}
