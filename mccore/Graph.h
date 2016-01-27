//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Martin Larose
// Created On       : Fri Dec 10 00:05:15 2004
// $Revision: 1.30 $
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

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>

#include "Algo.h"
#include "Exception.h"
// #include "Path.h"

using namespace std;



namespace mccore
{
  /**
   * Abstract class for the graph classes.  Removing vertices or edges are
   * costly.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.30 2007-01-08 23:39:39 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class Graph
  {
    
  public:

    typedef typename vector< V >::iterator iterator;
    typedef typename vector< V >::const_iterator const_iterator;
    typedef typename vector< V >::size_type size_type;
    typedef typename vector< V >::size_type label;
    typedef typename vector< E >::iterator edge_iterator;
    typedef typename vector< E >::const_iterator edge_const_iterator;
    typedef typename vector< E >::size_type edge_size_type;
    typedef typename vector< E >::size_type edge_label;
    
  public:
    
    /**
     * Stores the endvertices labels.
     *
     * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
     */
    class EndVertices
    {
      /**
       * The head vertex label.
       */
      label head;

      /**
       * The tail vertex label.
       */
      label tail;

      // LIFECYCLE ------------------------------------------------------------
      
      /**
       * Initializes the object;
       */
      EndVertices () { }

    public:

      /**
       * Initializes the object with head and tail vertices labels.
       * @param head the head label.
       * @param tail the tail label.
       */
      EndVertices (label head, label tail)
	: head (head), tail (tail)
      { }

      /**
       * Initializes the object with right's content.
       * @param right the endvertices to copy.
       */
      EndVertices (const EndVertices &right)
	: head (right.head), tail (right.tail)
      { }

      /**
       * Destroys the object.
       */
      ~EndVertices () { }

      // OPERATORS ------------------------------------------------------------

    protected:

      /**
       * Assigns the endvertices with the right's content.
       * @param right the endvertices to copy.
       * @return this.
       */
      EndVertices& operator= (const EndVertices &right)
      {
	if (this != &right)
	  {
	    head = right.head;
	    tail = right.tail;
	  }
	return *this;
      }

    public:
      
      /**
       * Tests whether this equals right.
       * @param right the endvertices to compare.
       * @return true if the endvertices labels are equal.
       */
      bool operator== (const EndVertices &right) const
      {
	return head == right.head && tail == right.tail;
      }

      /**
       * Tests whether this differs from right.
       * @param right the endvertices to compare.
       * @return true if the endvertices labels differs.
       */
      bool operator!= (const EndVertices &right) const
      {
	return ! operator== (right);
      }

      /**
       * Tests whether this is less than right.
       * @param right the endvertices to compare.
       * @return true if this is less than right.
       */
      bool operator< (const EndVertices &right) const
      {
	return (head < right.head
		|| (head == right.head
		    && tail < right.tail));
      }

      // ACCESS ---------------------------------------------------------------
      
      /**
       * Gets the head vertex.
       * @return the head vertex.
       * @exception NoSuchElementException if the head label is outside the
       * vertex container.
       */
      V& getHeadVertex ()
      {
	if (vertices.size () <= head)
	  {
	    throw NoSuchElementException ();
	  }
	return vertices[head];
      }

      /**
       * Gets the head vertex.
       * @return the head vertex.
       * @exception NoSuchElementException if the head label is outside the
       * vertex container.
       */
      const V& getHeadVertex () const
      {
	if (vertices.size () <= head)
	  {
	    throw NoSuchElementException ();
	  }
	return vertices[head];
      }

      /**
       * Gets the tail vertex.
       * @return the tail vertex.
       * @exception NoSuchElementException if the tail label is outside the
       * vertex container.
       */
      V& getTailVertex ()
      {
	if (vertices.size () <= tail)
	  {
	    throw NoSuchElementException ();
	  }
	return vertices[tail];
      }

      /**
       * Gets the tail vertex.
       * @return the tail vertex.
       * @exception NoSuchElementException if the tail label is outside the
       * vertex container.
       */
      const V& getTailVertex () const
      {
	if (vertices.size () <= tail)
	  {
	    throw NoSuchElementException ();
	  }
	return vertices[tail];
      }

      /**
       * Gets the head label.
       * @return the head label.
       */
      label getHeadLabel () const { return head; }

      /**
       * Gets the tail label.
       * @return the tail label.
       */
      label getTailLabel () const { return tail; }

      // METHODS --------------------------------------------------------------
      
      // I/O  -----------------------------------------------------------------

    };

  protected:

    typedef map< EndVertices, label > EV2ELabel;
    typedef map< const V*, label, less_deref< V, Vertex_Comparator > > V2VLabel;
    
    /**
     * The vertex collection.
     */
    vector< V > vertices;

    /**
     * The vertex weight collection.
     */
    vector< VW > vertexWeights;

    /**
     * The edge collection.
     */
    vector< E > edges;

    /**
     * The edge weight collection.
     */
    vector< EW > edgeWeights;

    /**
     * The map between the vertices and their label.
     */
    V2VLabel v2vlabel;

    /**
     * The map between the endvertices and the associated edge label.
     */
    EV2ELabel ev2elabel;
    
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
    virtual Graph< V, E, VW, EW, Vertex_Comparator >* cloneGraph () const = 0;

    /**
     * Destroys the object.
     */
    virtual ~Graph () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    Graph& operator= (const Graph &right)
    {
      if (this != &right)
	{
	  label l;

	  vertices = right.vertices;
	  vertexWeights = right.vertexWeights;
	  edges = right.edges;
	  edgeWeights = right.edgeWeights;
	  v2vlabel.clear ();
	  for (l = 0; l < vertices.size (); ++l)
	    {
	      v2vlabel.insert (make_pair (&vertices[l], l));
	    }
	  ev2elabel = right.ev2elabel;
	}
      return *this;
    }

    /**
     * Tests whether the graphs are equals.
     * @param right a graph to compare with this.
     * @return whether the graphs are equals.
     */
    bool operator== (const Graph< V, E, VW, EW, Vertex_Comparator > &right) const
    {
      return (this == &right
	      || (vertices == right.vertices
		  && vertexWeights == right.vertexWeights
		  && edges == right.edges
		  && edgeWeights == right.edgeWeights
		  && ev2elabel == right.ev2elabel));
    }
    
    /**
     * Tests whether the graphs differs.
     * @param right a graph to compare with this.
     * @return whether the graphs differs.
     */
    bool operator!= (const Graph< V, E, VW, EW, Vertex_Comparator > &right) const
    {
      return ! operator== (right);
    }
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the vertex weight.
     * @param v the vertex.
     * @return the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertex.
     */
    VW& getVertexWeight (const V &v)
    {
      typename V2VLabel::const_iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  throw NoSuchElementException ();
	}
      return vertexWeights[it->second];
    }
      
    /**
     * Gets the vertex weight.
     * @param v the vertex.
     * @return the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertex.
     */
    const VW& getVertexWeight (const V &v) const
    {
      typename V2VLabel::const_iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  throw NoSuchElementException ();
	}
      return vertexWeights[it->second];
    }
    
    /**
     * Sets the vertex weight.
     * @param v the vertex.
     * @param w the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertex.
     */
    void setVertexWeight (const V &v, const VW &w)
    {
      typename V2VLabel::const_iterator it;
      
      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  throw NoSuchElementException ();
	}
      vertexWeights[it->second] = w;
    }
      
    /**
     * Gets the edge that exists between vertices h and t.
     * @param h the head of the edge.
     * @param t the tail of the edge.
     * @return the edge.
     * @exception NoSuchElementException if the graph does not contain the
     * vertices or the edge.
     */
    E& getEdge (const V &h, const V &t)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      typename EV2ELabel::const_iterator ite;

      if (v2vlabel.end () == (ith = v2vlabel.find (&h))
	  || v2vlabel.end () == (itt = v2vlabel.find (&t)))
	{
	  throw NoSuchElementException ();
	}
      EndVertices ev (ith->second, itt->second);
      if (ev2elabel.end () == (ite = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edges[ite->second];
    }

    /**
     * Gets the edge between vertices h and t.
     * @param h the head of the edge.
     * @param t the tail of the edge.
     * @return the edge.
     * @exception NoSuchElementException if the graph does not contain the
     * vertices or the edge.
     */
    const E& getEdge (const V &h, const V &t) const
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      typename EV2ELabel::const_iterator ite;

      if (v2vlabel.end () == (ith = v2vlabel.find (&h))
	  || v2vlabel.end () == (itt = v2vlabel.find (&t)))
	{
	  throw NoSuchElementException ();
	}
      EndVertices ev (ith->second, itt->second);
      if (ev2elabel.end () == (ite = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edges[ite->second];
    }

    /**
     * Gets the edge weight between vertices h and t.
     * @param h the head of the edge.
     * @param t the tail of the edge.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertices or the edge.
     */
    EW& getEdgeWeight (const V &h, const V &t)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      typename EV2ELabel::const_iterator ite;

      if (v2vlabel.end () == (ith = v2vlabel.find (&h))
	  || v2vlabel.end () == (itt = v2vlabel.find (&t)))
	{
	  throw NoSuchElementException ();
	}
      EndVertices ev (ith->second, itt->second);
      if (ev2elabel.end () == (ite = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[ite->second];
    }
    
    /**
     * Gets the edge weight between vertices h and t.
     * @param h the head of the edge.
     * @param t the tail of the edge.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertices or the edge.
     */
    const EW& getEdgeWeight (const V &h, const V &t) const
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      typename EV2ELabel::const_iterator ite;

      if (v2vlabel.end () == (ith = v2vlabel.find (&h))
	  || v2vlabel.end () == (itt = v2vlabel.find (&t)))
	{
	  throw NoSuchElementException ();
	}
      EndVertices ev (ith->second, itt->second);
      if (ev2elabel.end () == (ite = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[ite->second];
    }
    
    /**
     * Sets the edge weight betwee endvertices h and t.
     * @param h the head vertex.
     * @param t the tail vertex.
     * @param w the new weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertices or the edge.
     */
    void setEdgeWeight (const V &h, const V &t, const EW &w)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      typename EV2ELabel::const_iterator ite;

      if (v2vlabel.end () == (ith = v2vlabel.find (&h))
	  || v2vlabel.end () == (itt = v2vlabel.find (&t)))
	{
	  throw NoSuchElementException ();
	}
      EndVertices ev (ith->second, itt->second);
      if (ev2elabel.end () == (ite = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      edgeWeights[ite->second] = w;
    }
    
    /**
     * Gets the vertex label.
     * @param v the vertex.
     * @return the vertex label.
     * @exception NoSuchElementException if the graph does not contain the
     * vertex.
     */
    label getVertexLabel (const V &v) const
    {
      typename V2VLabel::const_iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  throw NoSuchElementException ();
	}
      return it->second;
    }
    
    /**
     * Determines if the graph contains the vertex v.
     * @param v the vertex to find.
     * @return true if the vertex v is in the graph.
     */
    bool contains (const V &v) const
    {
      return v2vlabel.end () != v2vlabel.find (&v);
    }

    /**
     * Returns true if there exists an edge between vertices h and t.
     * @param h an extremity of the edge.
     * @param t an extremity of the edge.
     * @return true if there exists an edge between vertices h and t.
     */
    bool areConnected (const V &h, const V &t) const
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;

      if (v2vlabel.end () != (ith = v2vlabel.find (&h))
	  && v2vlabel.end () != (itt = v2vlabel.find (&t)))
	{
	  EndVertices ev (ith->second, itt->second);

	  return ev2elabel.end () != ev2elabel.find (ev);
	}
      return false;
    }      
    
    /**
     * Returns the neighbors of the given vertex sorted over their label. An
     * empty list is returned if the vertex has no neighbors or if the graph
     * does not contain the vertex.
     * @param v a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual list< V > neighborhood (const V &v) = 0;
    
    /**
     * Returns a increasing label list of the neighbors of the given vertex
     * label.  An empty list is returned if the label has no neighbor or if
     * it is not contained in the graph.
     * @param l the vertex label.
     * @return the list of neighbors.
     */
    virtual list< label > internalNeighborhood (label l) const = 0;
    
    /**
     * Gets a vertex given its label.
     * @param l the vertex label.
     * @return the vertex.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    V& internalGetVertex (label l)
    {
      if (vertices.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return vertices[l];
    }

    /**
     * Gets a vertex given its label.
     * @param l the vertex label.
     * @return the vertex.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    const V& internalGetVertex (label l) const
    {
      if (vertices.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return vertices[l];
    }

    /**
     * Gets the vertex label weight.
     * @param l the vertex label.
     * @return the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    VW& internalGetVertexWeight (label l)
    {
      if (vertexWeights.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return vertexWeights[l];
    }

    /**
     * Gets the vertex label weight.
     * @param l the vertex label.
     * @return the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    const VW& internalGetVertexWeight (label l) const
    {
      if (vertexWeights.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return vertexWeights[l];
    }
    
    /**
     * Sets the vertex label weight.
     * @param l the vertex label.
     * @param w the new vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    void internalSetVertexWeight (label l, const VW &w)
    {
      if (vertexWeights.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      vertexWeights[l] = w;
    }
    
    /**
     * Gets the edge given its label.
     * @param l the edge label.
     * @return the edge.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    E& internalGetEdge (edge_label l)
    {
      if (edges.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return edges[l];
    }
    
    /**
     * Gets the edge given its label.
     * @param l the edge label.
     * @return the edge.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    const E& internalGetEdge (edge_label l) const
    {
      if (edges.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return edges[l];
    }
    
    /**
     * Gets the edge given its endvertices label.
     * @param h the endvertices head label.
     * @param t the endvertices tail label.
     * @return the edge.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    const E& internalGetEdge (label h, label t) const
    {
      typename EV2ELabel::const_iterator evit;
      EndVertices ev (h, t);
      
      if (vertices.size () <= h
	  || vertices.size () <= t
	  || ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edges[evit->second];
    }
    
    /**
     * Gets the edge label between endvertices labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge label.
     * @exception NoSuchElementException if the graph does not contain the
     * labels or the vertices are not connected.
     */
    edge_label internalGetEdgeLabel (label h, label t) const
    {
      typename EV2ELabel::const_iterator evit;
      EndVertices ev (h, t);
      
      if (vertices.size () <= h
	  || vertices.size () <= t
	  || ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return evit->second;
    }
    
    /**
     * Gets the edge weight between endvertices labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * labels or the vertices are not connected.
     */
    EW& internalGetEdgeWeight (label h, label t)
    {
      typename EV2ELabel::iterator evit;
      EndVertices ev (h, t);
      
      if (vertices.size () <= h
	  || vertices.size () <= t
	  || ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[evit->second];
    }
    
    /**
     * Gets the edge weight between endvertices labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * labels or the vertices are not connected.
     */
    const EW& internalGetEdgeWeight (label h, label t) const
    {
      typename EV2ELabel::const_iterator evit;
      EndVertices ev (h, t);
      
      if (vertices.size () <= h
	  || vertices.size () <= t
	  || ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[evit->second];
    }
    
    /**
     * Gets the edge weight given the edge label.
     * @param l the edge label.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    EW& internalGetEdgeWeight (edge_label l)
    {
      if (edgeWeights.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[l];
    }

    /**
     * Gets the edge weight given the edge label.
     * @param l the edge label.
     * @return the edge weight.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    const EW& internalGetEdgeWeight (edge_label l) const
    {
      if (edgeWeights.size () <= l)
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[l];
    }

    /**
     * Sets the edge weight between endvertices labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @param w the new weight.
     * @exception NoSuchElementException if the graph does not contain the
     * labels or the vertices are not connected.
     */
    void internalSetEdgeWeight (label h, label t, const EW w)
    {
      typename EV2ELabel::iterator evit;
      EndVertices ev (h, t);
      
      if (vertices.size () <= h
	  || vertices.size () <= t
	  || ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  throw NoSuchElementException ();
	}
      edgeWeights[evit->second] = w;
    }
    
    /**
     * Determines if the vertex label is in the graph.
     * @param l the vertex label to find.
     * @return whether the label is within the range of vertices.
     */
    bool internalContains (label l) const
    {
      return vertices.size () > l;
    }

    /**
     * Returns true if there exists an edge between vertex labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return true if there exists an edge between vertices h and t.
     */
    bool internalAreConnected (label h, label t) const
    {
      if (vertices.size () > h
	  && vertices.size () > t)
	{
	  EndVertices ev (h, t);

	  return ev2elabel.end () != ev2elabel.find (ev);
	}
      return false;
    }
    
    /**
     * Gets the iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    iterator begin () { return vertices.begin (); }

    /**
     * Gets the iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    iterator end () { return vertices.end (); }

    /**
     * Gets the const_iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    const_iterator begin () const { return vertices.begin (); }

    /**
     * Gets the const_iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    const_iterator end () const { return vertices.end (); }

    /**
     * Gets the iterator pointing to the beginning of the graph edges.
     * @return the iterator.
     */
    edge_iterator edge_begin () { return edges.begin (); }

    /**
     * Gets the iterator pointing to the end of the graph edges.
     * @return the iterator.
     */
    edge_iterator edge_end () { return edges.end (); }

    /**
     * Gets the const_iterator pointing to the beginning of the graph edges.
     * @return the iterator.
     */
    edge_const_iterator edge_begin () const { return edges.begin (); }

    /**
     * Gets the const_iterator pointing to the end of the graph edges.
     * @return the iterator.
     */
    edge_const_iterator edge_end () const { return edges.end (); }

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Rebuilds the vertex to vertex lable map.
     */
    void rebuildV2VLabel ()
    {
      typename vector< V >::iterator it;
      
      v2vlabel.clear ();
      for (it = vertices.begin (); vertices.end () != it; ++it)
	{
	  v2vlabel.insert (make_pair (&*it, it - vertices.begin ()));
	}
    }

  public:
    
    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &v)
    {
      typename V2VLabel::iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  vertices.push_back (v);
	  vertexWeights.resize (vertexWeights.size () + 1);
	  rebuildV2VLabel ();
	  return true;
	}
      return false;
    }
    
    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @param w the vertex weight.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &v, const VW &w)
    {
      typename V2VLabel::iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  vertices.push_back (v);
	  vertexWeights.push_back (w);
	  rebuildV2VLabel ();
	  return true;
	}
      return false;
    }
    
    /**
     * Inserts a vertex range.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     */
    template <class InputIterator>
    void insertRange (InputIterator f, InputIterator l)
    {
      for (; l != f; ++f)
	{
	  if (vertices.end () == std::find (vertices.begin (), vertices.end (), *f))
	    {
	      vertices.push_back (*f);
	    }
	}
      vertexWeights.resize (vertices.size ());
      rebuildV2VLabel ();
    }

  protected:

    /**
     * Erase a vertex label from the graph.  If an edge is connected to this
     * vertex label it is also removed.  No check is made on label validity.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element.
     */
    virtual iterator uncheckedInternalErase (label l) = 0;

  public:
    
    /**
     * Erase a vertex from the graph.  If an edge is connected to this
     * vertex it is also removed.
     * @param v the vertex to remove.
     * @return an iterator over the next vertex element.
     */
    iterator erase (const V &v)
    {
      typename V2VLabel::iterator it;
      
      return (v2vlabel.end () != (it = v2vlabel.find (&v))
	      ? uncheckedInternalErase (it->second)
	      : vertices.end ());
    }
    
    /**
     * Erase a vertex label from the graph.  If an edge is connected to this
     * vertex label it is also removed.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element.
     */
    iterator internalErase (label l)
    {
      return (vertices.size () > l
	      ? uncheckedInternalErase (l)
	      : vertices.end ());
    }
    
    /**
     * Finds a vertex in the graph.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    iterator find (const V &v)
    {
      typename V2VLabel::const_iterator it;

      return (v2vlabel.end () == (it = v2vlabel.find (&v))
	      ? vertices.end ()
	      : vertices.begin () + it->second);
    }

    /**
     * Finds a vertex in the graph.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    const_iterator find (const V &v) const
    {
      typename V2VLabel::const_iterator it;

      return (v2vlabel.end () == (it = v2vlabel.find (&v))
	      ? vertices.end ()
	      : vertices.begin () + it->second);
    }

    /**
     * Gets the number of vertices in this graph.
     * @return the number of vertices in the graph.
     */
    size_type size () const { return vertices.size (); }
    
    /**
     * Gets the number of edges in this graph.
     * @return the number of edges in the graph.
     */
    edge_size_type edgeSize () const { return edges.size (); }
    
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains no vertex.
     */
    bool empty () const { return vertices.empty (); }
    
    /**
     * Removes all graph elements.
     */
    void clear ()
    {
      vertices.clear ();
      vertexWeights.clear ();
      edges.clear ();
      edgeWeights.clear ();
      v2vlabel.clear ();
      ev2elabel.clear ();
    }

  protected:

    /**
     * Connects two vertices labels of the graph with an edge.  No check are
     * made on vertex labels validity.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, const E &e) = 0;
    
    /**
     * Connects two vertices of the graph with an edge and weight.  No check
     * are made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, const E &e, const EW &w) = 0;
    
  public:
    
    /**
     * Connects two vertices of the graph with an edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, const E &e)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;

      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? uncheckedInternalConnect (ith->second, itt->second, e)
	      : false);
    }      
    
    /**
     * Connects two vertices of the graph with an edge and weight.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, const E &e, const EW &w)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;
      
      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? uncheckedInternalConnect (ith->second, itt->second, e, w)
	      : false);
    }
    
    /**
     * Connects two vertices labels of the graph with an edge.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool internalConnect (label h, label t, const E &e)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? uncheckedInternalConnect (h, t, e)
	      : false);
    }
    
    /**
     * Connects two vertices labels of the graph with an edge and weight.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool internalConnect (label h, label t, const E &e, const EW &w)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? uncheckedInternalConnect (h, t, e, w)
	      : false);
    }

  protected:

    /**
     * Disconnects two endvertices labels of the graph.  No check are
     * made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool uncheckedInternalDisconnect (label h, label t) = 0;
    
  public:
    
    /**
     * Disconnects two endvertices of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    bool disconnect (const V &t, const V &h)
    {
      typename V2VLabel::const_iterator ith;
      typename V2VLabel::const_iterator itt;

      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? uncheckedInternalDisconnect (ith->second, itt->second)
	      : false);
    }
    
    /**
     * Disconnects two endvertices labels of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    bool internalDisconnect (label h, label t)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? uncheckedInternalDisconnect (h, t)
	      : false);
    }
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual ostream& write (ostream& os) const
    {
      typename vector< V >::const_iterator vit;
      typename vector< VW >::const_iterator vwit;
      typename vector< E >::const_iterator eit;
      typename vector< EW >::const_iterator ewit;
      typename EV2ELabel::const_iterator evit;
      label counter;
      label linecounter;

      os << "[Vertices]" << endl;
      for (vit = vertices.begin (), vwit = vertexWeights.begin (), counter = 0; vertices.end () != vit; ++vit, ++vwit, ++counter)
	{
	  os << setw (5) << counter << "  " << *vit << "  " << *vwit << endl;
	}
      os << "[Edges]" << endl;
      for (eit = edges.begin (), ewit = edgeWeights.begin (), counter = 0; edges.end () != eit; ++eit, ++ewit, ++counter)
	{
	  os << setw (5) << counter << "  " << *eit << "  " << *ewit << endl;
	}
      os << "[Adjacency matrix]" << endl;
      os << "     ";
      for (counter = 0; vertices.size () > counter; ++counter)
	{
	  os << setw (5) << counter;
	}
      linecounter = 0;
      if (! empty ())
	{
	  os << endl << setw (5) << linecounter;
	}
      for (counter = 0, evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit, ++counter)
	{
	  label evline;
	  label evcolumn;

	  evline = evit->first.getHeadLabel ();
	  evcolumn = evit->first.getTailLabel ();
	  while (linecounter < evline)
	    {
	      while (vertices.size () > counter)
		{
		  os << setw (5) << '.';
		  ++counter;
		}
	      counter = 0;
	      ++linecounter;
	      os << endl << setw (5) << linecounter;
	    }
	  while (counter < evcolumn)
	    {
	      os << setw (5) << '.';
	      ++counter;
	    }
	  os << setw (5) << evit->second;
	}
      while (linecounter < vertices.size ())
	{
	  while (counter < vertices.size ())
	    {
	      os << setw (5) << '.';
	      ++counter;
	    }
	  counter = 0;
	  ++linecounter;
	  if (linecounter < vertices.size ())
	    {
	      os << endl << setw (5) << linecounter;
	    }
	}
      os << endl;      
      return os;
    }
    
  };

}



namespace std
{

  /**
   * Writes the graph into the output stream.  It calls the graph virtual
   * method write.
   * @param os the output stream.
   * @param obj the graph.
   * @return the output stream.
   */
  template < class V, class E, class VW, class EW, class VC >
  ostream& operator<< (ostream &os, const mccore::Graph< V, E, VW, EW, VC > &obj)
  {
    return obj.write (os);
  }
  
}

#endif
