//                              -*- Mode: C++ -*- 
// ArrayGraph.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 17:25:17 2003
// $Revision: 1.3 $
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


#ifndef _ArrayGraph_h_
#define _ArrayGraph_h_

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <assert.h>

#include "AbstractGraph.h"
#include "GraphAlgo.h"
#include "Path.h"

using namespace std;

namespace mccore {

  /**
   * Implementation of directed graphs that uses arrays for faster
   * access to nodes and edges.
   *
   * This implementation should not be used as a container for the
   * object of the graph (although it will work) but rather an
   * addition to the real object container, meaning that no
   * optimisation is done to prevent recopying large objects.  You
   * should insert references to object by passing the correct node
   * comparator if needed.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: ArrayGraph.h,v 1.3 2004-09-02 20:52:19 larosem Exp $
   */
  template< class node_type, 
	    class edge_type = bool,
	    class node_comparator = less< node_type > >
  class ArrayGraph : public virtual AbstractGraph< node_type, edge_type, node_comparator >
  {

    // MEMBERS -----------------------------------------------------------------

  protected:

    /**
     * Mapping from the internal id to the node.
     */
    vector< node_type > nodes;

    /**
     * The actual edges.
     */
    vector< edge_type > edges; 

    /**
     * The adjacency matrix.
     */
    int* graph;

    /**
     * The edge coordinate map.
     */
    map< int, pair< int, int > > edgeCoordinates;

    /**
     * Node weights.
     */
    vector< float > nodeWeights;
       
    /**
     * Edge weights.
     */
    vector< float > edgeWeights;


    // TYPEDEFS ----------------------------------------------------------------
        
    /**
     * The size type of the container.
     */
    typedef unsigned int size_type;


    // LIFECYCLE ---------------------------------------------------------------
        
  public:
    
    /**
     * Initializes the object.
     */
    ArrayGraph (int size_hint = 0)
      : AbstractGraph< node_type, edge_type, node_comparator > ()
    {
      graph = new int[0];
    }
    
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    ArrayGraph (const AbstractGraph< node_type, edge_type, node_comparator > &other) 
      : AbstractGraph< node_type, edge_type, node_comparator > (other)
    {
      typename ArrayGraph::const_iterator i, j;
      
      resize (other.size ());
      
      for (i=other.begin (); i!=other.end (); ++i) {
      	insert (*i);
      }
      
      for (i=other.begin (); i!=other.end (); ++i) {
      	for (j=other.begin (); j!=other.end (); ++j) {	
      	  if (other.areConnected (*i, *j)) {
      	    connect (*i, *j, other.getEdge (*i, *j), other.getWeight (*i, *j));
      	  }
      	}
      }
    }
    
    
    /**
     * Destroys the object.
     */
    virtual ~ArrayGraph () {
      clear ();
      delete[] graph;
    }


    // OPERATORS ---------------------------------------------------------------

  public:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    ArrayGraph& operator= (const AbstractGraph< node_type, edge_type, node_comparator > &other) {
      if (this != &other) {
	clear ();
	
	resize (other.size ());

	typename ArrayGraph::const_iterator i, j;
	
	for (i=other.begin (); i!=other.end (); ++i) {
	  insert (*i);
	}
	
	for (i=other.begin (); i!=other.end (); ++i) {
	  for (j=other.begin (); j!=other.end (); ++j) {	
	    if (other.areConnected (*i, *j)) {
	      connect (*i, *j, other.getEdge (*i, *j), other.getWeight (*i, *j));
	    }
	  }
	}
      }
      return *this;
    }

    
    // ACCESS ------------------------------------------------------------------

  public:
    
    /**
     * Sets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual void setWeight (const node_type& n, float w)
    {
      nodeWeights[mapping[n]] = w;
    }


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& n) const
    {
      return nodeWeights[mapping.find (n)->second];
    }


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& o, const node_type& p) const
    {
      return edgeWeights[graph[index(mapping.find (o)->second, 
				     mapping.find (p)->second)]];
    }
    
    
    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const edge_type& getEdge (const node_type& o, const node_type& p) const
    {
      const edge_type& e = edges[graph[index(mapping.find (o)->second, 
					     mapping.find (p)->second)]];
      return e;
    }
    

    virtual void setEdgeWeight (const node_type& o, const node_type& p, float w)
    {
      edgeWeights[graph[index(mapping.find (o)->second, 
			      mapping.find (p)->second)]] = w;
    }
      

    // PRIVATE METHODS ---------------------------------------------------------

  protected:
    
    int index (int o, int p) const { return o*size () + p; }

    void resize (int s) { // TO COMPLETE: Add resize to lower sizes...
      if (s<size ()) return;
      int* tmp = graph;
      graph = new int[s*s];
      for (int i=0; i<s*s; ++i) graph[i] = -1;

      int os = s-1;
      for (int i=0; i<os; ++i) {
	int* toto = graph;
	memcpy (graph+i*s, tmp+i*os, os*sizeof(int));
      }
      
      delete[] tmp;
    }


    // METHODS -----------------------------------------------------------------

  public:

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const node_type &n, float weight = 1) 
    {
      if (contains (n))	return false;
      
      mapping[n] = nodes.size ();
      nodes.push_back (n);
      nodeWeights.push_back (weight);
     
      resize (size ());
      
      return true;
    }
    

    /**
     * Erase a node from the graph.
     * @param n the node to remove.
     * @return the number of nodes that were erased.
     */ 
    virtual size_type erase (const node_type &n) {
      cerr << "Undefined method (erase)" << endl;
      return 0;
    }


    /**
     * Determines if the node is in the graph
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    bool contains (const node_type &n) const {
      return (mapping.find (n) != mapping.end ());
    }


    /**
     * Get the number of elements in this graph.
     * @return the number of elements in the graph.
     */
    int size () const {
      return nodes.size ();
    }

      
    /**
     * Get the number of edges in this graph.
     * @return the number of edges in the graph.
     */
    int edgeSize () const {
      return edges.size ();
    }

    
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains 0 nodes.
     */
    bool empty () const {
      return (size () == 0);
    }


    /**
     * Removes all of the elements from the graph.  
     */
    virtual void clear() {
      nodes.clear ();
      edges.clear ();
      nodeWeights.clear ();
      edgeWeights.clear ();
      delete[] graph;
      graph = new int[0];
    }


    /**
     * Connect two nodes of the graph by a directed edge.
     * @param o a node.
     * @param p another node.
     * @param e the edge.
     * @param w the weight of this edge (default=1).
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const node_type &o, const node_type &p, 
			  const edge_type &e = edge_type(), float w = 1) 
    {
      if (!contains (o) || !contains (p))
	return false;

      edges.push_back (e);
      edgeWeights.push_back (w);
      
      graph[index (mapping[o], mapping[p])] = edges.size ()-1;
      edgeCoordinates.insert (make_pair (edges.size () - 1, make_pair (mapping[o], mapping[p])));
      return true;
    }
    

    /**
     * Disconnect two nodes of the graph.
     * @param o a node.
     * @param p another node.
     * @return true if the nodes were disconnected.
     */
    virtual bool disconnect (const node_type &o, const node_type &p) 
    {
      if (!contains (o)
	  || !contains (p)
	  || !areConnected (o, p))
	return false;
      
      int e = graph[index (mapping[o], mapping[p])];
      map< int, pair< int, int > >::iterator eIt;
      map< int, pair< int, int > >::iterator eIt2;
      
      graph[index (mapping[o], mapping[p])] = -1;
      
      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);

      for (int i=0; i<size ()*size (); ++i) {
	if (graph[i] > e) graph[i]--;
      }
      eIt = edgeCoordinates.find (e);
      eIt2 = eIt++;
      edgeCoordinates.erase (eIt2);
      while (edgeCoordinates.end () != eIt)
	{
	  edgeCoordinates.insert (make_pair (eIt->first - 1, eIt->second));
	  eIt2 = eIt++;
	  edgeCoordinates.erase (eIt2);
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
      return (graph[index (mapping.find (o)->second,
			   mapping.find (p)->second)] != -1);
    }
    

    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< node_type > getNeighbors (const node_type& o) const {
      list< node_type > l;

      int oi = mapping.find(o)->second;
      for (int i=0; i<size (); ++i) {
	if (internalAreConnected (oi, i)) l.push_back (nodes[i]);
      }
      
      return l;
    }

    
    /**
     * Algorithm for determining the shortest path between two nodes
     * in a directed graph.
     * @param source the start node of the path.
     * @param dest the end node of the path. 
     * @return a Path of object that represents the path.
     */
    Path< node_type, float > 
    shortestPath (const node_type& o, const node_type& p)
    {
      Path< int, float >::iterator i;
      Path< int, float > apath;
      Path< node_type, float > realpath;

      apath = GraphAlgo::shortestPath (*this, mapping.find (o)->second, mapping.find (p)->second);
      
      for (i=apath.begin (); i!=apath.end (); ++i) {
	realpath.push_back (nodes[*i]);
      }
      realpath.setValue (apath.getValue ());
      return realpath;
    }


    // FAST INTERFACE ----------------------------------------------------------
  
  public:  // TODO Encapsulate TODO
   

    /**
     * Gets a node given its id.
     * @param n the node id.
     * @return the node.
     */
    virtual const node_type& internalGetNode (int n) const 
    {
      return nodes[n];
    }


    /**
     * Sets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual void internalSetWeight (int n, float w)
    {
      nodeWeights[n] = w;
    }


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float internalGetWeight (int n) const 
    {
      return nodeWeights[n];
    }


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float internalGetWeight (int o, int p) const 
    {
      return edgeWeights[graph[index(o, p)]];
    }


    /**
     * Gets the edge give its id.
     * @param n the edge id.
     * @return the edge.
     */
    virtual const edge_type& internalGetEdge (int n) const {
      const edge_type& e = edges[n];
      return e;
    }

      /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual int internalGetEdge (int o, int p) const {
      return graph[index(o, p)];
    }
    
    
    /**
     * Determines if the node is in the graph
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    virtual bool internalContains (int n) const {
      return (n>0 && n<size ());
    }


    /**
     * Returns true if there exists an edge between o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool internalAreConnected (int o, int p) const 
    {
      return graph[index(o,p)] != -1;
    }


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetNeighbors (int o) const
    {
      list< int > l;
      for (int i=0; i<size (); ++i) 
	if (graph[index (o, i)] != -1) l.push_back (i);
      return l;
    }

    
    /**
     * Gets the edge coordinates map.
     * @return a map of edge id has key and nodes id pair.
     */
    virtual const map< int, pair< int, int > >& getInternalEdgeCoordinateMap () const
    {
      return edgeCoordinates;
    }

    
    // I/O ---------------------------------------------------------------------    
    
  public:
    
    virtual
    ostream& output (ostream& os) const
    {
      typename ArrayGraph::const_iterator ki, kj;
      typename vector< node_type >::const_iterator i;
      typename vector< edge_type >::const_iterator j;
      
      os << "Nodes:" << endl;
      for (i=nodes.begin (); i!=nodes.end (); ++i) {
	os << i-nodes.begin () << " : " << *i << " (" 
	   << nodeWeights[i-nodes.begin ()] << ")" << endl;
      }
      os << "Edges:" << endl;
      for (j=edges.begin (); j!=edges.end (); ++j) {
	os << j-edges.begin () << " : " << *j << " (" 
	   << edgeWeights[j-edges.begin ()] << ")" << endl;
      }
      os << "Adjacency (size = " << size () << ")" << endl;
      
      //       for (ki=begin (); ki!=end (); ++ki) {      
      // 	os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
      // 	for (kj=begin (); kj!=end (); ++kj) {
      // 	  if (areConnected (*ki, *kj)) 
      // 	    os << *kj << "(" << getEdge (*ki, *kj) << ") ";
      // 	}
      // 	os << endl;
      //       }
      
      for (int i = 0; i != size (); ++i)
	{
	  os << i << " : "; 
	  for (int j=0; j!=size (); ++j)
	    {
	      if (graph[index (i, j)] == -1) os << "- ";
	      else os << graph[index (i, j)] << " ";
	    }
	  os << endl;
	}
      return os;
    }
  };
}

#endif
