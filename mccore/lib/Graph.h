//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Apr 30 16:04:32 2003
// $Revision: 1.16 $
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

#include "AdjacencyMatrix.h"
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
   * Abstract base class for graphs.  This implementation is not a
   * container for the object of the graph but rather an addition to
   * the real object container, meaning that no optimisation is done
   * to prevent recopying large objects.  You should insert references
   * to object by passing the correct node comparator if needed.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: Graph.h,v 1.16 2003-09-26 21:16:18 gendrop Exp $
   */
  template< class node_type, 
	    class edge_type = bool,
	    class matrix_type = MapMatrix,
	    class node_comparator = less< node_type > >
  class Graph
  {

  protected:

    // TYPEDEFS ----------------------------------------------------------------


    /**
     * The size type of the container.
     */
    typedef unsigned int size_type;

    
    // MEMBERS -----------------------------------------------------------------


    /**
     * Mapping from the node to its internal id.
     */
    map< node_type, int, node_comparator > mapping;

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
    matrix_type graph;

    /**
     * Node weights.
     */
    vector< float > nodeWeights;
    
    
    /**
     * Edge weights.
     */
    vector< float > edgeWeights;



    // PUBLIC TYPEDEFS ---------------------------------------------------------


  public:

    /**
     * Forward declaration of iterators classes.
     */
    class graph_iterator;
    typedef graph_iterator iterator;
    class graph_const_iterator;
    typedef graph_const_iterator const_iterator;

        
    // LIFECYCLE ---------------------------------------------------------------


  public:
    
    /**
     * Initializes the object.
     */
    Graph (int size_hint = 0) {
      graph.resize (size_hint);
    }
    

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Graph (const Graph &other) {
      const_iterator i, j;

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


    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual Graph& operator= (const Graph &other) {
      if (this != &other) {
	clear ();
	
	graph.resize (other.size ());

	const_iterator i, j;
	
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
     * Gets the iterator pointing to the beginning of the graph.
     * @return the iterator.
     */
    iterator begin () { return iterator (mapping.begin ()); }


    /**
     * Gets the iterator pointing to the end of the graph.
     * @return the iterator.
     */
    iterator end () { return iterator (mapping.end ()); }


    /**
     * Gets the const_iterator pointing to the beginning of the graph.
     * @return the iterator.
     */
    const_iterator begin () const { return const_iterator (mapping.begin ()); }


    /**
     * Gets the const_iterator pointing to the end of the graph.
     * @return the iterator.
     */
    const_iterator end () const { return const_iterator (mapping.end ()); }

    
    /**
     * Sets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual void setWeight (const node_type& n, float w)
    {
      assert (contains (n));
      internalSetWeight (mapping[n], w);
    }


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& n) const 
    {
      assert (contains (n));
      return internalGetWeight (mapping.find (n)->second);
    }


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& o, const node_type& p) const 
    {
      assert (contains (o));
      assert (contains (p));
      assert (areConnected (o, p));
      return internalGetWeight (mapping.find (o)->second, 
				mapping.find (p)->second);
    }
    
    
    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const edge_type getEdge (const node_type& o, const node_type& p) const {
      assert (contains (o));
      assert (contains (p));
      assert (areConnected (o, p));
      return edges[internalGetEdge (mapping.find (o)->second, 
				    mapping.find (p)->second)];
    }

    

    // METHODS -----------------------------------------------------------------

  public:

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return an iterator on the node that was inserted.
     */
    virtual iterator insert (const node_type &n, float weight = 1) 
    {
      if (contains (n))	return find (n);
      
      mapping[n] = nodes.size ();
      nodes.push_back (n);
      nodeWeights.push_back (weight);

      graph.resize (size ());

      iterator p = find (n);
      return p;     
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
     * Finds a node in the graph.
     * @param n the node to find.
     * @return an iterator on the node found or on end () if not found.
     */
    iterator find (const node_type &n) {
      return iterator (mapping.find (n));
    }


    /**
     * Finds a node in the graph.
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    const_iterator find (const node_type &n) const {
      return const_iterator (mapping.find (n));
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

      graph.connect (mapping[o], mapping[p], edges.size ()-1);

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
      
      int e = graph.elem (mapping[o], mapping[p]);
      graph.disconnect (mapping[o], mapping[p]);

      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);
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
      int oi, pi;
      oi = mapping.find(o)->second;
      pi = mapping.find(p)->second;
      return internalAreConnected (oi, pi);
    }


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< node_type > getNeighbors (const node_type& o) const
    {
      list< node_type > n;
      if (!contains (o)) return n;
      
      list< int > l = internalGetNeighbors (mapping.find (o)->second);
      list< int >::iterator i;

      for (i=l.begin (); i!=l.end (); ++i) {
	n.push_back (nodes[*i]);
      }

      return n;
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
      typedef float value_type;
      if (!contains (source) || !contains (dest)) return Path< node_type, value_type >();
      
      vector< Path< int, value_type > > paths;
      Path< int, value_type >::iterator kt; 

      internalShortestPath (mapping.find (source)->second, paths);
      
      Path< node_type, float > realpath;

      for (kt=paths[mapping.find (dest)->second].begin ();
	   kt!=paths[mapping.find (dest)->second].end (); ++kt) {
	realpath.push_back (nodes[*kt]);
      }
      realpath.setValue (paths[mapping.find (dest)->second].getValue ());
      return realpath;
    }

    
    // PROTECTED METHODS -------------------------------------------------------
  
  protected:
    
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
      return edgeWeights[graph.get (o, p)];
    }


    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual int internalGetEdge (int o, int p) const {
      return graph.get (o, p);
    }
    
    
    /**
     * Determines if the node is in the graph
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    bool internalContains (int n) const {
      return (graph.contains (n));
    }


    /**
     * Returns true if there exists an edge between o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool internalAreConnected (int o, int p) const 
    {
      return graph.areConnected (o, p);
    }


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetNeighbors (int o) const
    {
      return graph.neighbors (o);
    }

    
    /**
     * Dijkstra's algorithm for the shortest path in a directed graph.
     * NOTE: value_type must be a float since we still use gcc-2.95.3
     * and we can't know the MAX_VALUE of types at runtime.  and it
     * doesn't implement numeric_limits<T> 
     * @param source the source node of the paths.
     * @return a map of nodes with their paths from the source.
     */
    void internalShortestPath (int source, vector< Path< int, float > > &paths)
    {
      typedef float value_type;
      value_type MAXVALUE = MAXFLOAT;  

      int i;
      int graphsize = size ();
      paths.clear ();
      paths.resize (graphsize);                     // path description  
      vector< int > C;                              // node set
      vector< int >::iterator k;
      
      // Initialize ---
      for  (i=0; i<graphsize; i++) {
	if  (i == source) { 
	  paths[i].setValue (0);
	} else { 
	  C.push_back (i);
	  if  (internalAreConnected(source, i)) {
	    paths[i].setValue (internalGetWeight (source, i));	 
	    paths[i].push_back (source); 
	    paths[i].push_back (i);
	  } else {
	    paths[i].setValue (MAXVALUE);
	  }
	}
      }
    
      for  (i=0; i<graphsize-2; i++) {
	vector< int >::iterator min_iter = C.begin();
	value_type min_value = paths[*min_iter].getValue (); // in C
	int min_index;
	
	for  (k=C.begin(); k!=C.end(); k++) {
	  if  (paths[*k].getValue () < min_value) {
	    min_value = paths[*k].getValue ();
	    min_iter = k;
	  } 
	}
	min_index = *min_iter;
	C.erase (min_iter);
	
	if  (min_value == MAXVALUE) break; // in case there is no better element...
	
	for (k=C.begin(); k!=C.end(); k++) {
	  value_type old_val = paths[*k].getValue ();
	  value_type new_val;
	  if (internalAreConnected (min_index, *k))
	    new_val = min_value + internalGetWeight (min_index, *k);
	  else 
	    new_val = MAXVALUE;
	  if  (old_val > new_val) {
	    paths[*k] = paths[ min_index ];
	    paths[*k].push_back (*k);
	    paths[*k].setValue (new_val);
	  }
	}
      }
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
      
      graph.output (os);
      return os;
    }

    

    // ITERATORS ------------------------------------------------------------

    
protected:

    
    typedef typename map< node_type, int >::iterator gtiterator;
    typedef typename map< node_type, int >::const_iterator gtciterator;
    
    class graph_iterator : public gtiterator
    {      
    public:

      graph_iterator () : gtiterator () { }
      
      graph_iterator (const gtiterator &it) 
	: gtiterator (it)
      { }
      
      const node_type& operator* () const 
      {
	return gtiterator::operator* ().first;
      }
      
      const node_type* operator-> () const 
      { 
	return &(operator* ()); 
      }
    };


    class graph_const_iterator : public gtciterator
    {
    public:
      
      graph_const_iterator () : gtciterator () { }

      graph_const_iterator (const gtciterator &it) 
	: gtciterator (it)
      { }
    
      graph_const_iterator (const gtiterator &it) 
	: gtciterator (it)
      { }

      const node_type& operator* () const 
      {
	return gtciterator::operator* ().first;
      }

      const node_type* operator-> () const 
      { 
	return &(operator* ()); 
      }
    };

    
  };

  template< class node_type, 
	    class edge_type,
	    class matrix_type,
	    class node_comparator >
  ostream &operator<< (ostream &out, const Graph< node_type, edge_type, matrix_type, node_comparator> &g)
  {    
    return g.output (out);
  }  

}


#endif
