//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Apr 30 16:04:32 2003
// $Revision: 1.14 $
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
#include <list>
#include <vector>
#include <set>

#include <values.h>
#include <assert.h>

#include "Path.h"

namespace mccore {

  /**
   * @short A templated directed graph class.  Graphs are always weighted using floats!
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: Graph.h,v 1.14 2003-07-09 21:49:30 gendrop Exp $
   */
  template< class node_type, 
	    class edge_type = bool, 
	    class node_comparator = less< node_type > >
  class Graph
  {

  protected:

    /**
     * Comparison class that dereferences objects stored in the graph.
     */
    class comparator {
    public:
      bool operator() (const node_type* o, const node_type* p) const {
	return node_comparator() (*o, *p);
      }
    };

    // TYPEDEFS ----------------------------------------------------------------

    /**
     * The size type of the abstract residue container.
     */
    typedef unsigned int size_type;

    /**
     * The type of a mapping node/edge.
     */
    typedef map< const node_type*, const edge_type*, comparator > adjacency_type;
    
    /**
     * The type of a mapping node/node/edge.
     */
    typedef map< const node_type*, adjacency_type, comparator > graph_type;

    /**
     * A node to value associative container.
     */
    typedef map< const node_type*, float, comparator > node_adapter;

    /**
     * A node to node to value associative container.
     */
    typedef map< const node_type*, node_adapter, comparator > edge_adapter;
        
    
    // MEMBERS -----------------------------------------------------------------


    /**
     * The graph implemented as a map of map, that is an adjacency
     * matrix but where empty cells do not take space in memory.
     */
    graph_type graph;


    /**
     * The actual nodes.
     */
    set< node_type > nodes;


    /**
     * The actual edges.
     */
    list< edge_type > edges;


    /**
     * Node weights.
     */
    node_adapter nodeWeights;


    /**
     * Edge weights.
     */
    edge_adapter edgeWeights;

    
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
    Graph () {}


    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Graph (const Graph &other) {
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

  public:


    /**
     * Destroys the object.
     */
    virtual ~Graph () {
      clear ();
    }

    
    // OPERATORS ------------------------------------------------------------


    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual Graph& operator= (const Graph &other) {
      if (this != &other) {
	clear ();

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


    // ACCESS ---------------------------------------------------------------


  public:


    /**
     * Gets the iterator pointing to the beginning of the graph.
     * @return the iterator.
     */
    iterator begin () { return iterator (graph.begin ()); }


    /**
     * Gets the iterator pointing to the end of the graph.
     * @return the iterator.
     */
    iterator end () { return iterator (graph.end ()); }


    /**
     * Gets the const_iterator pointing to the beginning of the graph.
     * @return the iterator.
     */
    const_iterator begin () const { return const_iterator (graph.begin ()); }


    /**
     * Gets the const_iterator pointing to the end of the graph.
     * @return the iterator.
     */
    const_iterator end () const { return const_iterator (graph.end ()); }


    /**
     * Sets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual void setWeight (const node_type& n, float w)
    {
      assert (contains (n));
      nodeWeights.find (nodeToPtr (n))->second = w;
    }


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& n) const 
    {
      assert (contains (n));
      return nodeWeights.find (nodeToPtr (n))->second;
    }


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& o, const node_type& p) const 
    {
      assert (areConnected (o, p));
      return edgeWeights.find(nodeToPtr (o))->second.find (nodeToPtr (p))->second;
    }


    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const edge_type& getEdge (const node_type& o, const node_type& p) const {
      assert (areConnected (o, p));
      return *graph.find(nodeToPtr (o))->second.find (nodeToPtr (p))->second;
    }


  protected:


    const node_type* nodeToPtr (const node_type &n) const 
    {
      return &*nodes.find (n);
    }


    bool equals (const node_type& o, const node_type& p) {
      return !node_comparator () (o, p) && !node_comparator () (p, o);
    }


    // METHODS --------------------------------------------------------------


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
      
      const node_type* np = &*nodes.insert (n).first;

      graph[np] = adjacency_type ();
      nodeWeights[np] = weight;
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
      if (!contains (n)) return 0;
   
      const node_type* np = &*nodes.insert (n).first;

      graph.erase (np);
      nodeWeights.erase (np);
      
      typename graph_type::iterator i;    
      for (i=graph.begin (); i!=graph.end (); ++i) {
	i->second.erase (np);
      }

      nodes.erase (*np);

      return 1;
    }


    /**
     * Finds a node in the graph.
     * @param n the node to find.
     * @return an iterator on the node found or on end () if not found.
     */
    iterator find (const node_type &n) {
      return graph.find (nodeToPtr (n));
    }
  

    /**
     * Finds a node in the graph.
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    const_iterator find (const node_type &n) const {
      return graph.find (nodeToPtr (n));
    }

  
    /**
     * Determines if the 
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    bool contains (const node_type &n) const {
      return (nodes.find (n) != nodes.end ());
    }


    /**
     * Get the number of elements in this graph.
     * @return the number of elements in the graph.
     */
    int size () const {
      return graph.size ();
    }

  
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains 0 nodes.
     */
    bool empty () const {
      return (graph.size () == 0);
    }
  

    /**
     * Removes all of the elements from the graph.  
     */
    virtual void clear() {
      graph.clear ();
      nodeWeights.clear ();
      edgeWeights.clear ();
      nodes.clear ();
      edges.clear ();
    }


    // GRAPH RELATED METHODS ------------------------------------------------


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
      const edge_type* ep = &edges.back ();

      graph[nodeToPtr (o)][nodeToPtr (p)] = ep;
      edgeWeights[nodeToPtr (o)][nodeToPtr (p)] = w;

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

      const edge_type* ep = graph[nodeToPtr (o)][nodeToPtr (p)];

      graph.find (nodeToPtr (o))->second.erase (nodeToPtr (p));
      edgeWeights.find (nodeToPtr (o))->second.erase (nodeToPtr (p));

      typename list< edge_type >::iterator i;
      for (i=edges.begin (); i!=edges.end (); ++i) {
	if (&*i == ep) break;
      }
      if (i!=edges.end ())
	edges.erase (i);
      
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
      if (!contains (o) || !contains (p)) return false;
    
      return graph.find (nodeToPtr (o))->second.find (nodeToPtr (p)) != 
	graph.find (nodeToPtr (o))->second.end ();
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

      const adjacency_type &at = graph.find (nodeToPtr (o))->second;
      typename adjacency_type::const_iterator i;

      for (i=at.begin (); i!=at.end (); ++i) {
	n.push_back (*i->first);
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
      
      map< const node_type*, Path< const node_type*, value_type > > paths;
      paths = shortestPath (source);

      map< node_type, Path< node_type, value_type > > realpaths;      

      typename map< const node_type*, Path< const node_type*, value_type > >::iterator it;
      typename Path< const node_type*, value_type >::iterator kt; 
      
      for  (it=paths.begin (); it!=paths.end (); ++it) {
	if (it->second.size () > 0) {
	  Path< node_type, value_type > aPath;
	  for (kt=it->second.begin (); kt!=it->second.end (); ++kt) {
	    aPath.push_back (**kt);
	  }
	  aPath.setValue (it->second.getValue ());
	  realpaths[*(it->first)] = aPath;
	}
      }
      
      if (realpaths.find (dest) != realpaths.end ()) 
	return realpaths[dest];
      
      // Recreate the resulting map.
      
      return Path< node_type, value_type >();
    }

    // PRIVATE METHODS -----------------------------------------------------------

  protected:

    /**
     * Dijkstra's algorithm for the shortest path in a directed graph.
     * NOTE: value_type must be a float since we still use gcc-2.95.3
     * and we can't know the MAX_VALUE of types at runtime.  and it
     * doesn't implement numeric_limits<T> 
     * @param source the source node of the paths.
     * @return a map of nodes with their paths from the source.
     */
    map< const node_type*, Path< const node_type*, float > >
    shortestPath (const node_type &source) 
    {
      typedef float value_type;
      value_type MAXVALUE = MAXFLOAT;

      if (!contains (source)) 
	return map< const node_type*, Path< const node_type*, value_type > > ();
      
      map< const node_type*, Path< const node_type*, value_type > > p;  // path description
      vector< const node_type* > c;                                     // node set
      typename graph_type::const_iterator i;
      int j, k;
      
      // Initialize.
      for (i=graph.begin (); i!=graph.end (); ++i) {
      	if (equals (source, *i->first)) {
      	  p[i->first] = Path< const node_type*, value_type > ();
      	} else {
      	  c.push_back (i->first);
      	  if (areConnected (source, *i->first)) {
      	    p[i->first] = Path< const node_type*, value_type > ();
      	    p[i->first].setValue (getWeight (source, *i->first));
      	    p[i->first].push_back (nodeToPtr (source));
      	    p[i->first].push_back (i->first);
      	  } else {
      	    p[i->first] = Path< const node_type*, value_type > ();
      	    p[i->first].setValue (MAXVALUE);
      	  }	
	}
      }

//       {
// 	map< const node_type*, Path< const node_type*, value_type > >::iterator it;
// 	Path< const node_type*, value_type >::iterator kt; 
// 	vector< const node_type* >::iterator jt; 

// 	cout << "p =  (" << endl;
// 	for  (it=p.begin (); it!=p.end (); ++it) {
// 	  cout << *(it->first) << "=[";
// 	  for (kt=it->second.begin (); kt!=it->second.end (); ++kt) {
// 	    cout << **kt << " ";
// 	  }
// 	  cout << "] " << it->second.getValue () << endl;
// 	} 
// 	cout << ")" << endl;

// 	cout << "c = ";
// 	for (jt=c.begin (); jt!=c.end (); ++jt) {
// 	  cout << **jt << " ";
// 	}
// 	cout << endl;
//       }

      // Execute ---
      for (j=0; j<size ()-2; ++j) {
	// Find an element of c that minimizes the current path weight.
	int minId = 0;
	value_type minVal = p[c[minId]].getValue ();
	for (k=0; k<(int)c.size (); ++k) {
	  value_type currVal = p[c[k]].getValue ();
	  if (currVal < minVal) {
	    minVal = currVal;
	    minId = k;
	  }
	}	
	
	// Break if nothing was found.
	if (minVal == MAXVALUE) break;
	
	// Remove this element from the node set.
	const node_type* minNode = c[minId];
	c.erase (c.begin ()+minId);

	// Update paths.
	for (k=0; k<(int)c.size (); ++k) {
	  value_type oldVal = p[c[k]].getValue ();
	  value_type newVal;
	  const node_type* kp = c[k];
	  if (areConnected (*minNode, *kp))
	    newVal = minVal + getWeight (*minNode, *kp);
	  else
	    newVal = MAXVALUE;

	  if (oldVal > newVal) {
	    p[kp] = p[minNode];
	    p[kp].push_back (kp);
	    p[kp].setValue (newVal);
	  }
	}
      }
      
      return p;
    }


    // I/O -----------------------------------------------------------------------


  public:


    virtual ostream& output (ostream& os) const
    {
      typename graph_type::const_iterator i;
      typename adjacency_type::const_iterator j;

      for (i=graph.begin (); i!=graph.end (); ++i) {
	cout << *i->first << " : ";
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  cout << *j->first << " "; // << "(" << *j->second << ") ";
	}
	cout << endl;
      }

      return os;
    }
  

  protected:
    

    // ITERATORS ------------------------------------------------------------

    typedef typename graph_type::iterator gtiterator;
    typedef typename graph_type::const_iterator gtciterator;
    
    class graph_iterator : public gtiterator
    {      
    public:

      graph_iterator () : gtiterator () { }
      
      graph_iterator (const gtiterator &it) 
	: gtiterator (it)
      { }
      
      const node_type& operator* () const 
      {
	return *gtiterator::operator* ().first;
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
	return *gtciterator::operator* ().first;
      }

      const node_type* operator-> () const 
      { 
	return &(operator* ()); 
      }
    };


  };

  
  template< class node_type, 
	    class edge_type, 
	    class node_comparator >
  ostream &operator<< (ostream &out, const Graph< node_type, edge_type, node_comparator> &g)
  {
    return g.output (out);
  }  

}

#endif
