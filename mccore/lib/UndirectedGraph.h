//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 10 19:09:13 2004
// $Revision: 1.12.2.1 $
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


#ifndef _mccore_UndirectedGraph_h_
#define _mccore_UndirectedGraph_h_

#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "Graph.h"

using namespace std;



namespace mccore
{
  /**
   * Undirected graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: UndirectedGraph.h,v 1.12.2.1 2004-12-11 01:35:13 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class UndirectedGraph : public Graph<V,E,VW,EW,Vertex_Comparator>
  {

  protected:
    
    /**
     * The vertex collection.
     */
    vector< V > vertices;

    /**
     * The vertex weight collection.
     */
    vector< VW > vertexWeights;

    /**
     * The EdgeEntry collection.
     */
    vector< Graph::EdgeEntry< E, EW > > edges;

    /**
     * The map between a vertex and its index.
     */
    map< V, size_type > vertex2ind;
    
    /**
     * The map between a vertex id and a map of vertex id to edge entry index.
     */
    map< size_type, map< size_type, typename vector< Graph::EdgeEntry< E, EW > >::size_type > > internalGraph;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    UndirectedGraph () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    UndirectedGraph (const UndirectedGraph &right)
      : vertices (right.vertices),
	vertexWeights (right.vertexWeights),
	edges (right.edges),
	vertex2ind (right.vertex2ind),
	internalGraph (right.internalGraph)
    { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph* clone () const
    {
      return new UndirectedGraph<V,VW,E,EW,Vertex_Comparator> (*this);
    }

    /**
     * Destructs the object.
     */
    virtual ~UndirectedGraph () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    UndirectedGraph& operator= (const UndirectedGraph &right)
    {
      if (this != &right)
	{
	  vertices = right.vertices;
	  vertexWeights = right.vertexWeights;
	  edges = right.edges;
	  vertex2ind = right.vertex2ind;
	  internalGraph = right.internalGraph;
	}
      return *this;
    }	  

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the vertex weight.
     * @param n the vertex.
     * @return the vertex weight.
     */
    virtual VW& getVertexWeight (const V &n) throw (NoSuchElementException)
    {
      map<

    /**
     * Gets the vertex weight.
     * @param n the vertex.
     * @return the vertex weight.
     */
    virtual const VW& getVertexWeight (const V &n) const = 0;

    /**
     * Sets the vertex weight.
     * @param n the vertex.
     * @param w the vertex weight.
     */
    virtual void setVertexWeight (const V &n, const VW &w) = 0;

    /**
     * Gets the edge that exists between vertices o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual E& getEdge (const V &o, const V &p) = 0;

    /**
     * Gets the edge that exists between vertices o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
    virtual const E& getEdge (const V &o, const V &p) const = 0;

    /**
     * Gets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @return the edge weight.
     */
    virtual EW& getWeight (const V &o, const V &p) = 0;
    
    /**
     * Gets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @return the edge weight.
     */
    virtual const EW& getWeight (const V &o, const V &p) const = 0;

    /**
     * Sets the edge weight.
     * @param o the origin vertex.
     * @param p the destination vertex.
     * @param w the new weight.
     */
    virtual void setEdgeWeight (const V &o, const V &p, const EW &w) = 0;

    /**
     * Gets the id of the vertex.
     * @param v the vertex.
     * @return the vertex id.
     */
    virtual size_type getVertexIndex (const V &v) const = 0;
    
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
    virtual V& internalGetVertex (size_type idx) = 0;

    /**
     * Gets a vertex given its id.
     * @param idx the vertex id.
     * @return the vertex.
     */
    virtual const V& internalGetVertex (size_type idx) const = 0;

    /**
     * Gets the vertex index weight.
     * @param idx the vertex index.
     * @return the vertex weight.
     */
    virtual VW& internalGetVertexWeight (size_type idx) = 0;

    /**
     * Gets the vertex index weight.
     * @param idx the vertex index.
     * @return the vertex weight.
     */
    virtual const VW& internalGetVertexWeight (size_type idx) const = 0;

    /**
     * Sets the vertex index weight.
     * @param idx the vertex index.
     * @param w the new vertex weight.
     */
    virtual void internalSetVertexWeight (size_type idx, const VW &w) = 0;

    /**
     * Gets the edge given its index.
     * @param idx the edge index.
     * @return the edge.
     */
    virtual E& internalGetEdge (size_type idx) = 0;

    /**
     * Gets the edge given its index.
     * @param idx the edge index.
     * @return the edge.
     */
    virtual const E& internalGetEdge (size_type idx) const = 0;

    /**
     * Gets the edge index that exists between vertices indexes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge index.
     */
    virtual size_type internalGetEdgeIndex (size_type o, size_type p) const = 0;
    
    /**
     * Gets the edge weight.
     * @param o the origin vertex index.
     * @param p the destination vertex index.
     * @return the edge weight.
     */
    virtual EW& internalGetEdgeWeight (size_type o, size_type p) = 0;

    /**
     * Gets the edge weight.
     * @param o the origin vertex index.
     * @param p the destination vertex index.
     * @return the edge weight.
     */
    virtual const EW& internalGetEdgeWeight (size_type o, size_type p) const = 0;

    /**
     * Gets the edge weight given the edge index.
     * @param idx the edge index.
     * @return the edge weight.
     */
    virtual EW& internalGetEdgeWeight (size_type idx) = 0;

    /**
     * Gets the edge weight given the edge index.
     * @param idx the edge index.
     * @return the edge weight.
     */
    virtual const EW& internalGetEdgeWeight (size_type idx) const = 0;

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

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os The stream.
     * @return The written stream.
     */
    ostream& write (ostream& os) const;

  };

}

namespace std
{
  ostream& operator<< (ostream &os, const mccore::UndirectedGraph& obj);
}

#endif
