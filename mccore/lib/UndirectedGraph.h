//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:30:26 2003
// $Revision: 1.1 $
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef _UndirectedGraph_h_
#define _UndirectedGraph_h_

#include <iostream>
#include <map>

#include "Graph.h"

namespace mccore {

/**
 * @short A templated undirected graph class.  It is implemented using
 * the directed graph base class and by using a triangular matrix and
 * a node ordering determined by the node_comparator function object.
 *
 * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
 * @version $Id: UndirectedGraph.h,v 1.1 2003-04-03 21:55:55 gendrop Exp $
 */
template< class node_type, 
	  class edge_type = int, 
	  class node_comparator = less< node_type > >
class UndirectedGraph : public Graph< node_type, edge_type, node_comparator >
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  UndirectedGraph () : Graph< node_type, edge_type, node_comparator > () {}

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  UndirectedGraph (const UndirectedGraph &other) : Graph< node_type, edge_type, node_comparator > (other) {}

  /**
   * Destroys the object.
   */
  virtual ~UndirectedGraph () {
    clear ();
  }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  virtual UndirectedGraph& operator= (const UndirectedGraph &other) {
    if (this != &other) {
      Graph< node_type, edge_type, node_comparator >::operator= (other);      
    }
    return *this;
  }


  // ACCESS ---------------------------------------------------------------

    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    float getWeight (const node_type& o, const node_type& p) {
      assert (areConnected (o, p));
      return edge_weights[o][p];
    }


  // METHODS --------------------------------------------------------------

  // GRAPH RELATED METHODS ------------------------------------------------
  
  /**
   * Connect two nodes of the graph by a directed edge.
   * @param o a node.
   * @param p another node.
   * @param w the weight of this edge (default=1).
   * @return true if the connect operation succeeded.
   */
  virtual bool connect (const node_type &o, const node_type &p, const edge_type &e, float w=1) {
    if (!contains (o) || !contains (p)) return false;
    
    if (node_comparator () (o, p)) {
      graph[o][p] = e;
      edge_weights[o][p] = w;
    } else {
      graph[p][o] = e;
      edge_weights[p][o] = w;
    }

    return true;
  }
  
  /**
   * Disconnect two nodes of the graph.
   * @param o a node.
   * @param p another node.
   * @return true if the nodes were disconnected.
   */
  virtual bool disconnect (const node_type &o, const node_type &p) {
    if (!contains (o) || !contains (p)) return false;
    
    if (node_comparator () (o, p)) {
      graph.find (o)->second.erase (p);
      edge_weights.find (o)->second.erase (p);
    } else {
      graph.find (p)->second.erase (o);
      edge_weights.find (p)->second.erase (o);
    }

    return true;
  }

  
  /**
   * Returns true if there exists an edge between o and p.
   * @param o an extremity of the edge.
   * @param p an extremity of the edge.
   * @return true if there exists an edge between o and p.
   */
  virtual bool areConnected (const node_type &o, const node_type &p) const {
    if (!contains (o) || !contains (p)) return false;
    
    return graph.find (o)->second.find (p) != graph.find (o)->second.end () ||
      graph.find (p)->second.find (o) != graph.find (p)->second.end ();
  }
  


  /**
   * Prim's algorithm for the minimum spanning tree.
   * @return a vector of edges representing a spanning tree of this graph.
   */
  vector< node_pair > minimumSpanningTree () {
    typedef float value_type;
    value_type MAXVALUE = MAXFLOAT;

    map< const node_type*, const node_type* > nearest;
    map< const node_type*, value_type > mindist;
    map< const node_type*, value_type >::iterator k;
    vector< node_pair > edges;
    const_iterator i;
    int j;

    // Initialize
    for (i=begin (); i!=end (); ++i) {
      if (&*i == &*begin ()) {
	nearest[&*i] = 0;
	mindist[&*i] = MAXVALUE;
      } else {
	nearest[&*i] = &*begin();
	mindist[&*i] = areConnected (*i, *begin()) ? getWeight (*i, *begin()) : MAXVALUE;
      }    
    }

    // Execute
    for (j=0; j<size ()-1; ++j) {
      value_type min = MAXVALUE;
      const node_type* minNode = 0;
      for (map< const node_type*, float >::iterator x=mindist.begin ();
	   x!= mindist.end (); ++x) {
	if (x->second >= 0 && x->second < min) {
	  min = x->second;
	  minNode = x->first;
	}
      }

      // This is a test to see if we stay in the same connected component
      if (minNode != 0) {
	edges.push_back (make_pair(*nearest[minNode], *minNode));

	mindist[&*minNode] = -1;

	for (k=mindist.begin (), ++k; k!=mindist.end (); ++k) {
	  const node_type* kp = k->first;
	  value_type v = areConnected (*kp, *minNode) ? getWeight (*kp, *minNode) : MAXVALUE;
	  if (v < k->second) {
	    mindist[&*kp] = v;
	    nearest[&*kp] = minNode;
	  }
	}
      }      
    }

    return edges;
  }

  // I/O  -----------------------------------------------------------------

};

}

#endif
