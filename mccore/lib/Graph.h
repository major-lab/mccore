//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Mon Feb 18 16:07:09 2002
// $Revision: 1.7.8.2 $
// $Id: Graph.h,v 1.7.8.2 2003-11-26 17:00:05 larosem Exp $
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


#ifndef _Graph_h_
#define _Graph_h_

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "mccore/Binstream.h"

#define nodeid int
#define edgeid int

using namespace std;



/**
 * @short A class for a path in a graph.
 *
 * @author Patrick Gendron
 */
class Path : public vector< int >
{
  int mValue;
  
public:
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  Path () : vector< int >() { mValue = 0; }

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  Path (const Path &other) : vector< int> (other) { mValue = other.mValue; }

  /**
   * Destroys the object.
   */
  ~Path () {}

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  Path& operator= (const Path &other)
  {
    if  (this != &other) {
      vector< int >::operator= (other);
      mValue = other.mValue;
    } 
    return *this;
  }

  bool operator< (const Path &path) const { // used in sort
    return  (size () < path.size ());
  }

  bool operator== (const Path &other) const {
    Path a = *this;
    Path b = other;
    int i, j;
    
    bool success = false;
    
    if (a.size () != b.size ()) return false;
    
    for (i=0; i<(int)a.size (); ++i) {
      for (j=0; j<(int)a.size (); ++j) {
	if (a[j]!=b[j]) break;
      }
      if (j==(int)a.size ()) { success = true; break; }
      b.rotate ();
    }
    
    if (!success) {
      reverse (b.begin (), b.end ());
      
      for (i=0; i<(int)a.size (); ++i) {
	for (j=0; j<(int)a.size (); ++j) {
	  if (a[j]!=b[j]) break;
	}
	if (j==(int)a.size ()) { success = true; break; }
	b.rotate ();
      }
      
    }
    if (!success) return false;
    
    return true;
  }

  // ACCESS ---------------------------------------------------------------

  void setValue (int value) { mValue = value; }
  int getValue (void) const { return mValue; }
  
  // METHODS --------------------------------------------------------------

  void rotate ()
  {
    int tmp = (*this)[0];
    for (int i=0;i<(int)size ()-1; ++i)
      {
	(*this)[i] = (*this)[i+1];
      }
    (*this)[size ()-1]=tmp;
  }

  // I/O  -----------------------------------------------------------------

  ostream &output (ostream &out) const {
    out << "[ " << flush;
    for  (int i=0; i<(int)size(); i++) 
      out << (*this)[i] << " ";
    out << "] = " << mValue << flush;
    return out;
  }
  
  oBinstream &output (oBinstream &out) const {
    out << mValue;
    out << size();
    for  (int i=0; i<(int)size(); i++) 
      out << (*this)[i];
    return out;
  }
  
  iBinstream &input (iBinstream &ibn) {
    int size;
    ibn >> mValue;
    ibn >> size;
    for  (int i=0; i<size; i++) {
      int x;
      ibn >> x;
      push_back (x);
    }
    return ibn;
  }
  
  friend ostream &operator<< (ostream &out, const Path &path)
  {
    return path.output (out);
  }

  friend oBinstream &operator<< (oBinstream &out, const Path &path)
  {
    return path.output (out);
  }

  friend iBinstream &operator>> (iBinstream &ibn, Path &path)
  {
    return path.input (ibn);
  }
};


/**
 * @short A class for a graph.
 *
 * Class implementing the graph ADT with a adjacency lists implementation
 * and making it possible to treat oriented/non-oriented/semi-oriented graphs.
 *
 * @author Patrick Gendron
 */
template< class Node, class Edge >
class Graph : public map< int, map< int, int > >
{
public:

  typedef map< int, int > adjlist;    // Adjacency List
  typedef map< int, adjlist > adjgraph;  // Adjacency Graph  

protected:

  vector< Node > mNodes;
  vector< int > mNodeValues;

  // A mark on a node indicates that it is active in the graph. 
  vector< bool > mNodeMarks;

  vector< Edge > mEdges;
  vector< int >  mEdgeValues;
  vector< pair< int, int > > mEdgeNodes;

  // A mark on an edge indicates that it is active in the graph. 
  vector< bool > mEdgeMarks;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  Graph () {}

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  Graph (const Graph &other);

  /**
   * Destroys the object.
   */
  ~Graph ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  Graph& operator= (const Graph &other);
  
  /**
   * Returns the Node it position id in the graph
   * @param id the id of the node in the graph
   * @return the Node corresponding to the id.
   */
  const Node& operator() (int id) {
    assert (id>=0 && id<size ());
    return getNode (id);
  }
  
  // ACCESS ---------------------------------------------------------------

  size_t size () const { return mNodes.size (); }

  // Node related functions -----------------------------------------------

  const vector< Node > &getNodes (void) const { return mNodes; }
  vector< Node > &getNodes (void) { return mNodes; }
  
  const Node &getNode (int index) const;
  Node &getNode (int index);
  
  int getNodeValue (int index) const;
  void setNodeValue (int index, int v);
  
  int getNodeIndex (const Node &n) const;
  
  const adjlist& getNeighborIds (int id) const
  {
    static const adjlist empty;
    
    adjgraph::const_iterator i = find (id);
    if (i!=end ()) {
      return i->second;
    } 
    return empty;
  }
  
  // Edges related functions -----------------------------------------------

  const vector< Edge > &getEdges (void) const { return mEdges; }
  vector< Edge > &getEdges (void) { return mEdges; }

  const vector< pair< int, int > > &getEdgeNodes (void) const { return mEdgeNodes; }

  const Edge &getEdge (int index) const;
  Edge &getEdge (int index);

  const Edge &getEdge (int a, int b) const;
  Edge &getEdge (int a, int b); // a=origin, b=destination

  const pair< int, int > getNodes (const Edge &e) const;

  int getEdgeValue (int index) const;
  void setEdgeValue (int index, int v);

  int getEdgeIndex (const Edge &e) const; 
  int getEdgeIndex (int a, int b) const; // a=origin, b=destination

  // Check if there is a directed edge between a and b
  // Returns false even if there is a directed edge between b and a
  bool isConnected (int a, int b) const; // a=origin, b=destination
  
  // Building methods ------------------------------------------------------

  int addNode (const Node &n, const int v = 0);

  int addEdgeById (int a, int b, const Edge &e, 
		   bool oriented = true, const int v = 0);
  
  int addEdge (const Node &a, const Node &b, const Edge &e, 
	       bool oriented = true, const int v = 0);
    
  // Algorithms on the graph ----------------------------------------------

  void markNode (int index);
  void unmarkNode (int index);
  bool isMarked (int index) { return mNodeMarks[ index ]; }

  // (Un)Marks edge from a to b.  If the edge (b,a) exists, it is not modified
  void markEdge (int a, int b);
  void unmarkEdge (int a, int b);

  // Dijkstra's algorithm
  vector< Path > shortest_path (int root) const;
  Path shortest_path (int a, int b) const;

  // Prim's algorithm
  vector< Edge > minimum_spanning_tree (void) const;

  // Horton's algorithm 
  vector< Path > cycle_base () { return cycle_base_horton (); }
  vector< Path > cycle_base_union () { return cycle_base_horton (true); }
  private: vector< Path > cycle_base_horton (bool minimum_basis_union = false);
  private: vector< Path > gaussian_elimination (vector< Path > &bag, bool minimum_basis_union);

  // Seb's algorithm.
  // TODO: CODE THIS ALGO...  FROM ~lemieuxs/prog/analysis/UnGraph.h

  // I/O  -----------------------------------------------------------------
public:

  ostream &output (ostream &out) const;

  iBinstream& input (iBinstream& ibs);
  oBinstream& output (oBinstream& obs) const;

};

template< class Node, class Edge >
ostream &operator<< (ostream &out, const Graph< Node, Edge > &gr)
{
  return gr.output (out);
}

template< class Node, class Edge >
iBinstream &operator>> (iBinstream ibs, Graph< Node, Edge > &gr)
{
  return gr.input (ibs);
}

template< class Node, class Edge >
oBinstream &operator<< (oBinstream &obs, const Graph< Node, Edge > &gr)
{
  return gr.output (obs);
}

#include "Graph.cc"

#endif
