//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal
// Author           : Martin Larose
// Created On       : Fri Dec 10 00:05:15 2004
// $Revision: 1.23.4.3 $
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


#ifndef _mccore_Graph_h_
#define _mccore_Graph_h_

#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;



namespace mccore
{
  /**
   * Exception for 
   */
  
  /**
   * Abstract class for the graph classes.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.23.4.3 2004-12-11 01:35:07 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class Graph
  {
    
  protected:
    
    /**
     * Stores the edge object and its weight.
     *
     * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
     */
    class EdgeEntry<E,EW>
    {
      /**
       * The edge.
       */
      E edge;
      
      /**
       * The weight associated with the edge.
       */
      EW weight;

      /**
       * Initializes the object;
       */
      EdgeEntry() { }

    public:

      /**
       * Initializes the object.
       * @param edge the edge.
       * @param weight the weight.
       */
      EdgeEntry (const E &edge, const EW &weight)
	: edge (edge), weight (weight)
      { }

      /**
       * Destroys the object.
       */
      ~EdgeEntry () { }

      /**
       * Gets the edge.
       * @return the edge.
       */
      E& getEdge () { return edge; }

      /**
       * Gets the edge.
       * @return the edge.
       */
      const E& getEdge () const { return edge; }

      /**
       * Gets the weight.
       * @return the weight.
       */
      EW& getWeight () { return weight; }

      /**
       * Gets the weight.
       * @return the weight.
       */
      const EW& getWeight () const { return weight; }

      /**
       * Sets the weight.
       * @param w the weight.
       * @return the previous weight.
       */
      void setWeight (const EW &w) { weight = w; }
    };

  public:

    typedef typename vector< V >::iterator iterator;
    typedef typename vector< V >::const_iterator const_iterator;
    typedef typename vector< E >::iterator edgeIterator;
    typedef typename vector< E >::const_iterator const_edgeIterator;
    typedef typename vector< V >::size_type size_type;
    
  protected:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Graph () { }

  public:
    
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph* clone () const = 0;

    /**
     * Destructs the object.
     */
    virtual ~Graph () { }

    // OPERATORS ------------------------------------------------------------

  protected:
    
    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    Graph& operator= (const Graph &right) { return *this; }
    
  public:
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the vertex weight.
     * @param n the vertex.
     * @return the vertex weight.
     */
    virtual VW& getVertexWeight (const V &n) throw (NoSuchElementException) = 0;

    /**
     * Gets the vertex weight.
     * @param n the vertex.
     * @return the vertex weight.
     */
    virtual const VW& getVertexWeight (const V &n) const throw (NoSuchElementException) = 0;

    /**
     * Sets the vertex weight.
     * @param n the vertex.
     * @param w the vertex weight.
     */
    virtual void setVertexWeight (const V &n, const VW &w) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge that exists between vertices o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual E& getEdge (const V &o, const V &p) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge that exists between vertices o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const E& getEdge (const V &o, const V &p) const throw (NoSuchElementException) = 0;

    /**
     * Gets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @return the edge weight.
     */
    virtual EW& getEdgeWeight (const V &o, const V &p) throw (NoSuchElementException) = 0;
    
    /**
     * Gets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @return the edge weight.
     */
    virtual const EW& getEdgeWeight (const V &o, const V &p) const throw (NoSuchElementException) = 0;

    /**
     * Sets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @param w the new weight.
     */
    virtual void setEdgeWeight (const V &o, const V &p, const EW &w) throw (NoSuchElementException) = 0;

    /**
     * Gets the id of the vertex.
     * @param v the vertex.
     * @return the vertex id.
     */
    virtual size_type getVertexIndex (const V &v) const throw (NoSuchElementException) = 0;
    
    /**
     * Determines if the vertex is in the graph.
     * @param v the vertex to find.
     * @return wheter this graph containst the vertex v.
     */
    virtual bool contains (const V &v) const = 0;

    /**
     * Returns true if there exists an edge between vertices o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between vertices o and p.
     */
    virtual bool areConnected (const V &o, const V &p) const = 0;

    /**
     * Returns the neighbors of the given vertex.
     * @param o a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual list< V > getNeighbors (const V& o) const = 0;

    /**
     * Gets a vertex given its id.
     * @param idx the vertex id.
     * @return the vertex.
     */
    virtual V& internalGetVertex (size_type idx) throw (NoSuchElementException) = 0;

    /**
     * Gets a vertex given its id.
     * @param idx the vertex id.
     * @return the vertex.
     */
    virtual const V& internalGetVertex (size_type idx) throw (NoSuchElementException) const = 0;

    /**
     * Gets the vertex index weight.
     * @param idx the vertex index.
     * @return the vertex weight.
     */
    virtual VW& internalGetVertexWeight (size_type idx) throw (NoSuchElementException) = 0;

    /**
     * Gets the vertex index weight.
     * @param idx the vertex index.
     * @return the vertex weight.
     */
    virtual const VW& internalGetVertexWeight (size_type idx) throw (NoSuchElementException) const = 0;

    /**
     * Sets the vertex index weight.
     * @param idx the vertex index.
     * @param w the new vertex weight.
     */
    virtual void internalSetVertexWeight (size_type idx, const VW &w) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge given its index.
     * @param idx the edge index.
     * @return the edge.
     */
    virtual E& internalGetEdge (size_type idx) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge given its index.
     * @param idx the edge index.
     * @return the edge.
     */
    virtual const E& internalGetEdge (size_type idx) const throw (NoSuchElementException) = 0;

    /**
     * Gets the edge index that exists between vertices indexes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge index.
     */
    virtual size_type internalGetEdgeIndex (size_type o, size_type p) const throw (NoSuchElementException) = 0;
    
    /**
     * Gets the edge weight.
     * @param o the origin vertex index.
     * @param p the destination vertex index.
     * @return the edge weight.
     */
    virtual EW& internalGetEdgeWeight (size_type o, size_type p) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge weight.
     * @param o the origin vertex index.
     * @param p the destination vertex index.
     * @return the edge weight.
     */
    virtual const EW& internalGetEdgeWeight (size_type o, size_type p) const throw (NoSuchElementException) = 0;

    /**
     * Gets the edge weight given the edge index.
     * @param idx the edge index.
     * @return the edge weight.
     */
    virtual EW& internalGetEdgeWeight (size_type idx) throw (NoSuchElementException) = 0;

    /**
     * Gets the edge weight given the edge index.
     * @param idx the edge index.
     * @return the edge weight.
     */
    virtual const EW& internalGetEdgeWeight (size_type idx) const throw (NoSuchElementException) = 0;

    /**
     * Determines if the vertex index is in the graph.
     * @param idx the vertex index to find.
     * @return whether the index is within the range of vertices.
     */
    virtual bool internalContains (size_type idx) const = 0;

    /**
     * Returns true if there exists an edge between vertices indexes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    virtual bool internalAreConnected (size_type o, size_type p) const = 0;

    /**
     * Returns the neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< size_type > internalGetNeighbors (size_type o) const = 0;

    /**
     * Gets the iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    virtual iterator begin () = 0;

    /**
     * Gets the iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    virtual iterator end () = 0;

    /**
     * Gets the const_iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    virtual const_iterator begin () const = 0;

    /**
     * Gets the const_iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    virtual const_iterator end () const = 0;

    // METHODS --------------------------------------------------------------

    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &n) = 0;
    
    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @param w the vertex weight.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &n, const VW &w) = 0;
    
    /**
     * Inserts a vertex range.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     */
    template <class InputIterator>
    void insert (InputIterator f, InputIterator l)
    {
      while (f != l)
	{
	  insert (*f);
	  ++f;
	}
    }
    
    /**
     * Erase a vertex from the graph.  If an edge is connected to this
     * vertex it is also removed.
     * @param v the vertex to remove.
     * @return an iterator over the next vertex element.
     */
    virtual iterator erase (const V &v) = 0;

    /**
     * Finds a vertex in the graph.
     * @param  the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    iterator find (const V &n) = 0;

    /**
     * Finds a vertex in the graph.
     * @param  the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    const_iterator find (const V &n) const = 0;

    /**
     * Gets the number of vertices in this graph.
     * @return the number of vertices in the graph.
     */
    virtual size_type size () const = 0;

    /**
     * Gets the number of edges in this graph.
     * @return the number of edges in the graph.
     */
    virtual size_type edgeSize () const = 0;
    
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains no vertex.
     */
    virtual bool empty () const = 0;

    /**
     * Removes all graph elements.
     */
    virtual void clear () = 0;

    /**
     * Connects two vertices of the graph with an edge.
     * @param o a vertex.
     * @param p another vertex.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &o, const V &p, const E &e) = 0;
    
    /**
     * Connects two vertices of the graph with an edge and weight.
     * @param o a vertex.
     * @param p another vertex.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &o, const V &p, const E &e, const W  &w) = 0;
    
    /**
     * Disconnects two vertices of the graph.
     * @param o a vertex.
     * @param p another vertex.
     * @return true if the vertices were disconnected.
     */
    virtual bool disconnect (const V &o, const V &p) = 0;
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os The stream.
     * @return The written stream.
     */
    virtual ostream& write (ostream& os) const = 0;
    
  };

}

namespace std
{
  ostream& operator<< (ostream &os, const mccore::Graph& obj)
  {
    return obj.write (os);
  }
}

#endif
