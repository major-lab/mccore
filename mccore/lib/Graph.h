//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Tue Mar 25 10:40:26 2003
// $Revision: 1.8 $
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

#include "Path.h"

namespace mccore {

    /**
   * @short A templated directed graph class.  Graphs are always weighted using floats!
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.8 2003-04-03 21:43:32 gendrop Exp $
   */
  template< class node_type, 
	    class edge_type = int, 
	    class node_comparator = less< node_type > >
  class Graph
  {
  public:
  
    /**
     * The size type of the abstract residue container.
     */
    typedef unsigned int size_type;

    /**
     * Forward declaration of iterators classes.
     */
    class graph_iterator;
    typedef graph_iterator iterator;
    class graph_const_iterator;
    typedef graph_const_iterator const_iterator;
  
  protected:

    /**
     * The type of a mapping node/edge.
     */
    typedef map< node_type, edge_type, node_comparator > adjacency_type;

    /**
     * The type of a mapping node/node/edge.
     */
    typedef map< node_type, adjacency_type, node_comparator > graph_type;

    /**
     * A type for pairs of nodes.
     */
    typedef pair< node_type, node_type > node_pair;

    /**
     * The graph implemented as a map of map, that is an adjacency
     * matrix but where empty cells do not take space in memory.
     */
    graph_type graph;

    /**
     * Node weights.
     */
    map< node_type, float, node_comparator > node_weights;

    /**
     * Edge weights.
     */
    map< node_type, map< node_type, float, node_comparator >, node_comparator > edge_weights;

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
    Graph (const Graph &other) {
      graph = other.graph;
      node_weights = other.node_weights;
      edge_weights = other.edge_weights;
    }

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
	graph = other.graph;
	node_weights = other.node_weights;
	edge_weights = other.edge_weights;
      }
      return *this;
    }

    // ACCESS ---------------------------------------------------------------

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
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    float getWeight (const node_type& n) {
      assert (contains (n));
      return node_weights[n];
    }

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

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return an iterator on the node that was inserted.
     */
    virtual iterator insert (const node_type &n, float weight = 1) {
      graph[n] = adjacency_type ();
      node_weights[n] = weight;
      iterator p = graph.find (n);
      return p;
    }

    /**
     * Erase a node from the graph.
     * @param n the node to remove.
     * @return the number of nodes that were erased.
     */ 
    virtual size_type erase (const node_type &n) {
      if (!contains (n)) return 0;
   
      graph.erase (n);
      node_weights.erase (n);
      
      graph_type::iterator i;    
      for (i=graph.begin (); i!=graph.end (); ++i) {
	i->second.erase (n);
      }
    }

    /**
     * Finds a node in the graph.
     * @param n the node to find.
     * @return an iterator on the node found or on end () if not found.
     */
    iterator find (const node_type &n) {
      return graph.find (n);
    }
  
    /**
     * Finds a node in the graph.
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    const_iterator find (const node_type &n) const {
      return graph.find (n);
    }
  
    /**
     * Determines if the 
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    bool contains (const node_type &n) const {
      return (graph.find (n) != graph.end ());
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
      node_weights.clear ();
      edge_weights.clear ();
    }

    // GRAPH RELATED METHODS ------------------------------------------------

    /**
     * Connect two nodes of the graph by a directed edge.
     * @param o a node.
     * @param p another node.
     * @param w the weight of this edge (default=1).
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const node_type &o, const node_type &p, const edge_type &e, float w = 1) {
      if (!contains (o) || !contains (p)) return false;
    
      graph[o][p] = e;
      edge_weights[o][p] = w;

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

      graph.find (o)->second.erase (p);
      edge_weights.find (o)->second.erase (p);

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
    
      return graph.find (o)->second.find (p) != graph.find (o)->second.end ();
    }


    /**
     * Dijkstra's algorithm for the shortest path in a directed graph.
     * NOTE: value_type must be a float since we still use gcc-2.95.3
     * and we can't know the MAX_VALUE of types at runtime.  and it
     * doesn't implement numeric_limits<T> 
     * @param source the source node of the paths.
     * @return a map of nodes with their paths from the source.
     */
    map< node_type, Path< node_type, float > >
    shortestPath (const node_type &source) 
    {
      typedef float value_type;
      value_type MAXVALUE = MAXFLOAT;

      if (!contains (source)) return map< node_type, Path< node_type, value_type > > ();
      
      map< const node_type*, vector< const node_type* > > p;  // path description
      map< const node_type*, value_type > v;                  // value of paths in p
      vector< const node_type* > c;                           // node set
      const_iterator i;
      int j, k;
      
      // Initialize.
      for (i=begin (); i!=end (); ++i) {
      	if (!node_comparator() (source, *i) && !node_comparator() (*i, source)) {
      	  v[&*i] = value_type ();
      	  p[&*i] = vector< const node_type* > ();
      	} else {
      	  c.push_back (&*i);
      	  if (areConnected (source, *i)) {
      	    v[&*i] = getWeight (source, *i);
      	    p[&*i] = vector< const node_type* > ();
      	    p[&*i].push_back (&source);
      	    p[&*i].push_back (&*i);
      	  } else {
      	    v[&*i] = MAXVALUE;
      	    p[&*i] = vector< const node_type* > ();
      	  }	
	}
      }

//       {
// 	map< const node_type*, vector< const node_type* > >::iterator it;
// 	map< const node_type*, value_type >::iterator jt;
// 	vector< const node_type* >::iterator kt; 
      
// 	cout << "p =  (" << endl;
// 	for  (it=p.begin (), jt=v.begin (); it!=p.end () && jt!= v.end (); ++it, ++jt) {
// 	  cout << *(it->first) << "=[";
// 	  for (kt=it->second.begin (); kt!=it->second.end (); ++kt) {
// 	    cout << **kt << " ";
// 	  }
// 	  cout << "] " << jt->second << endl;
// 	} 
// 	cout << ")" << endl;

// 	cout << "c = ";
// 	for (kt=c.begin (); kt!=c.end (); ++kt) {
// 	  cout << **kt << " ";
// 	}
// 	cout << endl;
//       }

      // Execute ---
      for (j=0; j<size ()-2; ++j) {
	// Find an element of c that minimizes the current path weight.
	int minId = 0;
	value_type minVal = v[c[minId]];
	for (k=0; k<c.size (); ++k) {
	  value_type currVal = v[c[k]];
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
	for (k=0; k<c.size (); ++k) {
	  value_type oldVal = v[c[k]];
	  value_type newVal;
	  const node_type* kp = c[k];
	  if (areConnected (*minNode, *kp))
	    newVal = minVal + getWeight (*minNode, *kp);
	  else
	    newVal = MAXVALUE;

	  if (oldVal > newVal) {
	    p[kp] = p[minNode];
	    p[kp].push_back (kp);
	    v[kp] = newVal;
	  }
	}
      }

      // Recreate the resulting map.
      map< node_type, Path< node_type, value_type > > paths;      
      {
	map< const node_type*, vector< const node_type* > >::iterator it;
	map< const node_type*, value_type >::iterator jt;
	vector< const node_type* >::iterator kt; 

	for  (it=p.begin (), jt=v.begin (); it!=p.end () && jt!= v.end (); ++it, ++jt) {
	  if (it->second.size () > 0) {
	    Path< node_type, value_type > aPath;
	    for (kt=it->second.begin (); kt!=it->second.end (); ++kt) {
	      aPath.push_back (**kt);
	    }
	    aPath.setValue (jt->second);
	    paths[*(it->first)] = aPath;
	  }
	}
      } 
      
      return paths;
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
      
      map< node_type, Path< node_type, value_type > > paths;
      paths = shortestPath (source);
      if (paths.find (dest) != paths.end ()) 
	return paths[dest];
      return Path< node_type, value_type >();
    }



    // I/O -----------------------------------------------------------------------


    virtual ostream& output (ostream& os) const
    {
      graph_type::const_iterator i;
      adjacency_type::const_iterator j;

      for (i=graph.begin (); i!=graph.end (); ++i) {
	cout << i->first << " : ";
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  cout << j->first << "(" << j->second << ") ";
	}
	cout << endl;
      }

      //const_iterator i, j;
      //     for (i=begin (); i!=end (); ++i) {
      //       os << *i << /*" " << val[&*i] << */endl;
      //     }

      //     for (i=begin (); i!=end (); ++i) {

      //       os << *i << " ";

      //       for (j=begin (); j!=end (); ++j) {
      // 	if (areConnected (*i, *j)) os << "x ";
      // 	else os << "- ";
      //       }
      //       os << endl;
      //     }

      return os;
    }
  
    friend ostream &operator<< (ostream &out, const Graph &g)
    {
      return g.output (out);
    }

  protected:
    

    // ITERATORS ------------------------------------------------------------

    class graph_iterator : public graph_type::iterator
    {      
    public:

      graph_iterator () : graph_type::iterator () { }

      graph_iterator (const graph_type::iterator &it) 
	: graph_type::iterator (it)
      { }
    
      const node_type& operator* () const 
      {
	return graph_type::iterator::operator* ().first;
      }

      const node_type* operator-> () const 
      { 
	return &(operator* ()); 
      }
    };


    class graph_const_iterator : public graph_type::const_iterator
    {
    public:

      graph_const_iterator () : graph_type::const_iterator () { }

      graph_const_iterator (const graph_type::const_iterator &it) 
	: graph_type::const_iterator (it)
      { }
    
      graph_const_iterator (const graph_type::iterator &it) 
	: graph_type::const_iterator (it)
      { }

      const node_type& operator* () const 
      {
	return graph_type::const_iterator::operator* ().first;
      }

      const node_type* operator-> () const 
      { 
	return &(operator* ()); 
      }
    };

  };  


  
}

#endif
