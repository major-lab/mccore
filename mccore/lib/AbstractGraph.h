//                              -*- Mode: C++ -*- 
// AbstractGraph.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 16:47:20 2003
// $Revision: 1.2.2.1 $
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


#ifndef _AbstractGraph_h_
#define _AbstractGraph_h_


#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <assert.h>

#include "Path.h"

using namespace std;

namespace mccore {

  /**
   * Abstract base class for graphs.  This implementation should not
   * be used as a container for the object of the graph (although it
   * will work) but rather an addition to the real object container,
   * meaning that no optimisation is done to prevent recopying large
   * objects.  You should insert references to object by passing the
   * correct node comparator if needed.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: AbstractGraph.h,v 1.2.2.1 2004-12-10 03:44:45 larosem Exp $
   */
  template< class node_type, 
	    class edge_type = bool,
	    class node_comparator = less< node_type > >
  class AbstractGraph
  {

    friend class GraphAlgo;


    // MEMBERS -----------------------------------------------------------------

  protected:

    /**
     * Mapping from the node to its internal id.
     */
    map< node_type, int, node_comparator > mapping;
    

    // TYPEDEFS ----------------------------------------------------------------
        
    /**
     * The size type of the container.
     */
    typedef unsigned int size_type;


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
    AbstractGraph () {}

    /**
     * Destroys the object.
     */
    virtual ~AbstractGraph () {}


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
    virtual void setWeight (const node_type& n, float w) = 0;


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& n) const = 0;


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float getWeight (const node_type& o, const node_type& p) const = 0;
    
    
    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const edge_type& getEdge (const node_type& o, const node_type& p) const = 0;

    virtual void setEdgeWeight (const node_type& o, const node_type& p, float w) = 0;

    // METHODS -----------------------------------------------------------------

  public:

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const node_type &n, float weight = 1) = 0;
    
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
    virtual bool contains (const node_type &n) const = 0;


    /**
     * Get the number of elements in this graph.
     * @return the number of elements in the graph.
     */
    virtual size_type size () const = 0;


    /**
     * Get the number of edges in this graph.
     * @return the number of edges in the graph.
     */
    virtual int edgeSize () const = 0;
    
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains 0 nodes.
     */
    virtual bool empty () const = 0;


    /**
     * Removes all of the elements from the graph.  
     */
    virtual void clear() = 0;


    /**
     * Connect two nodes of the graph by a directed edge.
     * @param o a node.
     * @param p another node.
     * @param e the edge.
     * @param w the weight of this edge (default=1).
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const node_type &o, const node_type &p, 
			  const edge_type &e = edge_type(), float w = 1) = 0;
    

    /**
     * Disconnect two nodes of the graph.
     * @param o a node.
     * @param p another node.
     * @return true if the nodes were disconnected.
     */
    virtual bool disconnect (const node_type &o, const node_type &p) = 0;


    /**
     * Returns true if there exists an edge between o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool areConnected (const node_type &o, const node_type &p) const = 0;


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< node_type > getNeighbors (const node_type& o) const = 0;


    // FAST INTERFACE ----------------------------------------------------------

  public: // TODO Encapsulate TODO

    
    /**
     * Gets a node given its id.
     * @param n the node id.
     * @return the node.
     */
    virtual const node_type& internalGetNode (int n) const = 0;

    /**
     * Gets the id of the node.
     * @param node the node.
     * @return the node id.
     */
    virtual int getInternalNodeId (const node_type &node) const
    {
      typename map< node_type, int, node_comparator >::const_iterator res;

      if (mapping.end () == (res = mapping.find (node)))
	return -1;
      else
	return res->second;
    }
    

    /**
     * Sets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual void internalSetWeight (int n, float w) = 0;


    /**
     * Gets the weight of this node.
     * @param n the node.
     * @return the weight.
     */
    virtual float internalGetWeight (int n) const = 0;


    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    virtual float internalGetWeight (int o, int p) const = 0;


    /**
     * Gets the edge give its id.
     * @param n the edge id.
     * @return the edge.
     */
    virtual const edge_type& internalGetEdge (int n) const = 0;


    /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual int internalGetEdge (int o, int p) const = 0;

    
    /**
     * Determines if the node is in the graph
     * @param n the node to find.
     * @return a const_iterator on the node found or on end () if not found.
     */
    virtual bool internalContains (int n) const = 0;


    /**
     * Returns true if there exists an edge between o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool internalAreConnected (int o, int p) const = 0;


    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetNeighbors (int o) const = 0;

    
    /**
     * Gets the edge coordinates map.
     * @return a map of edge id has key and nodes id pair.
     */
    virtual const map< int, pair< int, int > >& getInternalEdgeCoordinateMap () const = 0;


    // I/O ---------------------------------------------------------------------    
    
  public:
    
    virtual ostream& output (ostream& os) const
    {
      os << "Graph" << endl;
      return os;
    }

   
    // ITERATORS ------------------------------------------------------------
    
  protected:

    
    typedef typename map< node_type, int, node_comparator >::iterator gtiterator;
    typedef typename map< node_type, int, node_comparator >::const_iterator gtciterator;
    
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
	    class node_comparator >
  ostream &operator<< (ostream &out, const AbstractGraph< node_type, edge_type, node_comparator> &g)
  {    
    return g.output (out);
  }  





  /**
   * Abstract base class for Undirected graphs. 
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: AbstractGraph.h,v 1.2.2.1 2004-12-10 03:44:45 larosem Exp $
   */
  template< class node_type, 
	    class edge_type = bool,
	    class node_comparator = less< node_type > >
  class UndirectedAbstractGraph : public virtual AbstractGraph< node_type, edge_type, node_comparator >
  {

    // LIFECYCLE ---------------------------------------------------------------

  public:
    
    /**
     * Initializes the object.
     */
    UndirectedAbstractGraph () {}
    
    /**
     * Destroys the object.
     */
    virtual ~UndirectedAbstractGraph () {}



  };

}
#endif
