//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Apr 30 16:04:32 2003
// $Revision: 1.17.2.1 $
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


#ifndef _Graph_h_
#define _Graph_h_


#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

#include "GraphAlgo.h"
#include "Path.h"

using namespace std;

#ifndef HAVE_NUMERIC_LIMITS
#include <values.h>
#else
#define MAXFLOAT numeric_limits< float > ().max ()
#define MAXINT numeric_limits< int > ().max ()
#endif


namespace mccore {

  /**
   * Implementation of directed graphs that uses maps for fast
   * neighbors access and low memory usage.
   *
   * This implementation is not a container for the object of the
   * graph but rather an addition to the real object container,
   * meaning that no optimisation is done to prevent recopying large
   * objects.  You should insert references to object by passing the
   * correct node comparator if needed.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: Graph.h,v 1.17.2.1 2003-12-17 16:34:17 gendrop Exp $
   */
  template< class node_type, 
	    class edge_type = bool,
	    class node_comparator = less< node_type > >
  class Graph : public virtual AbstractGraph< node_type, edge_type, node_comparator >
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
    map< int, map< int, int > > graph;

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
    Graph () 
      : AbstractGraph< node_type, edge_type, node_comparator > ()
    {}
    

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Graph (const AbstractGraph< node_type, edge_type, node_comparator > &other) 
      : AbstractGraph< node_type, edge_type, node_comparator > (other)
    {
      typename Graph::const_iterator i, j;

      graph.resize (other.size ());

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
    virtual ~Graph () {
      clear ();
    }


    // OPERATORS ---------------------------------------------------------------

  public:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Graph& operator= (const AbstractGraph< node_type, edge_type, node_comparator > &other) {
      if (this != &other) {
	clear ();
	
	typename Graph::const_iterator i, j;
	
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
      return edgeWeights[graph.find (mapping.find (o)->second)->second.find (mapping.find (p)->second)->second];
    }
    
    
    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const edge_type& getEdge (const node_type& o, const node_type& p) const {      
      const edge_type& e = edges[graph.find (mapping.find (o)->second)->second.find (mapping.find (p)->second)->second];
      return e;
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

      graph[mapping[n]] = map< int, int > ();

      return true;
    }

    
    /**
     * Inserts the residue range before pos.  It calls the list<> method.
     * @param pos the iterator where the residue will be placed.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     * @return the position where the residue was inserted.
     */
    template <class InputIterator>
    void insert(InputIterator f, InputIterator l)
    {
      while (f != l)
	{
	  insert (*f);
	  ++f;
	}
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
      graph.clear ();
      nodes.clear ();
      edges.clear ();
      nodeWeights.clear ();
      edgeWeights.clear ();
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
      if (!contains (o) || !contains (p)) return false;
    
      edges.push_back (e);
      edgeWeights.push_back (w);

      graph[mapping[o]][mapping[p]] = edges.size ()-1;

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
      if (!contains (o) || !contains (p)) return false;
      if (!areConnected (o, p)) return false;
      
      int e = graph[mapping[o]][mapping[p]];
      graph.find (mapping[o])->second.erase (mapping[p]);

      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);

      map< int, map< int, int > >::iterator i;
      map< int, int >::iterator j;

      for (i=graph.begin (); i!=graph.end (); ++i) {
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  if (j->second > e) j->second--;
	}
      }

      return true;
    }


    /**
     * Returns true if there exists an edge between o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool areConnected (const node_type &o, const node_type &p) const 
    {
      map< int, map< int, int > >::const_iterator row;
      map< int, int >::const_iterator col;
      if ((row = graph.find (mapping.find (o)->second)) == graph.end ()) return false;
      if ((col = row->second.find (mapping.find (p)->second)) == row->second.end ()) return false;
      return true;
    }


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< node_type > getNeighbors (const node_type& o) const
    {
      list< node_type > l;
      map< int, int >::const_iterator col;

      int i = mapping.find (o)->second;

      for (col=graph.find (i)->second.begin (); col!=graph.find (i)->second.end (); ++col) {
	l.push_back (nodes[col->first]);
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
    shortestPath (const node_type &source, const node_type &dest) 
    {
      Path< int, float >::iterator i;
      Path< int, float > apath;
      Path< node_type, float > realpath;

      apath = GraphAlgo::shortestPath (*this, mapping.find (source)->second, mapping.find (dest)->second);

      
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
      
      return edgeWeights[graph.find (o)->second.find (p)->second];
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
      return graph.find (o)->second.find (p)->second;
    }
    
    
    /**
     * Determines if the node is in the graph
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    bool internalContains (int n) const {
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
      map< int, map< int, int > >::const_iterator row;
      map< int, int >::const_iterator col;
      if ((row = graph.find (o)) == graph.end ()) return false;
      if ((col = row->second.find (p)) == row->second.end ()) return false;
      return true;
    }


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetNeighbors (int o) const
    {
      list< int > l;
      if (graph.find (o) == graph.end ()) return l;

      map< int, int >::const_iterator col;

      for (col=graph.find (o)->second.begin (); 
	   col!=graph.find (o)->second.end (); ++col) {
	l.push_back (col->first);
      }
      return l;
    }


    // CUSTOM INTERFACE --------------------------------------------------------

  public:  // TODO: Encapsulate TODO

    /**
     * Returns the neighbors of the given node in the form of a map of
     * neighbors/edge ids..
     * @param o a node in the graph.
     * @return the map of neighbors with the associated edge.
     */
    const map< int, int >& getNeighborsMap (int o) const {
      static const map< int, int > empty;
      
      map< int, map< int, int > >::const_iterator i = graph.find (o);
      if (i!=graph.end ()) {
	return i->second;
      } 
      return empty;
    }
    

    // I/O ---------------------------------------------------------------------
    
  public:
    
    virtual ostream& output (ostream& os) const
    {
      typename Graph::const_iterator ki, kj;
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

      for (ki=begin (); ki!=end (); ++ki) {      
	os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
	for (kj=begin (); kj!=end (); ++kj) {
	  if (areConnected (*ki, *kj)) 
	    os << *kj << "(" << getEdge (*ki, *kj) << ") ";
	}
	os << endl;
      }
      
      return os;
    }

    
  };
}


#endif
