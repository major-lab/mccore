//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal
// Author           : Martin Larose
// Created On       : Fri Dec 10 00:05:15 2004
// $Revision: 1.23.4.4 $
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

#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using namespace std;



namespace mccore
{
  
  /**
   * Exception for Graph access.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   */
  class NoSuchElementException : public exception
  {
    
  public:

    NoSuchElementException () { }
    ~NoSuchElementException () { }
  };


  /**
   * Abstract class for the graph classes.  Removing vertices or edges are
   * costly.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.23.4.4 2004-12-13 04:34:22 larosem Exp $
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
    typedef typename vector::size_type size_type;
    typedef typename size_type label;
    typedef typename map< EndVertices, Graph::label > EV2ELabel;
    
  private:

    typedef typename map< const V*, Graph::label, deref< Vertex_Comparator > > V2VLabel;
    
  protected:
    
    /**
     * Comparator used in the vertex to vertex label mapping.
     *
     * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
     */
    template< class Vertex_Comparator >
    class less_deref : public binary_function< V*, V*, bool >
    {
      
    public:
      
      less_deref () { }
      bool operator() (const V *left, const V *right)
      {
	return Vertex_Comparator ().operator() (*left, *right);
      }
    };

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
      Graph::label head;

      /**
       * The tail vertex label.
       */
      Graph::label tail;

      // LIFECYCLE ------------------------------------------------------------
      
      /**
       * Initializes the object;
       */
      EndVertices () { }

    protected:
      
      /**
       * Initializes the object with head and tail vertices labels.
       * @param head the head label.
       * @param tail the tail label.
       */
      EndVertices (Graph::label head, Graph::label tail)
	: head (head), tail (tail)
      { }

      /**
       * Initializes the object with right's content.
       * @param right the endvertices to copy.
       */
      EndVertices (const EndVertices &right)
	: head (right.head), tail (right.tail)
      { }

    public:

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
      V& getHeadVertex () throw (NoSuchElementException)
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
      const V& getHeadVertex () const throw (NoSuchElementException)
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
      V& getTailVertex () throw (NoSuchElementException)
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
      const V& getTailVertex () const throw (NoSuchElementException)
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
      Graph::label getHeadLabel () const { return head; }

      /**
       * Gets the tail label.
       * @return the tail label.
       */
      Graph::label getTailLabel () const { return tail; }

      // METHODS --------------------------------------------------------------
      
      // I/O  -----------------------------------------------------------------

    };

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
    virtual Graph* clone () const = 0;

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
	  Graph::label l;

	  vertices = right.vertices;
	  vertexWeights = right.vertexWeights;
	  edges = right.edges;
	  edgeWeights = right.edgeWeights;
	  v2vlabel.clear;
	  for (l = 0; l < vertices.size (); ++l)
	    {
	      v2vlabel.insert (make_pair (&vertices[l], l));
	    }
	  ev2elabel = right.ev2elabel;
	}
      return *this;
    }
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the vertex weight.
     * @param v the vertex.
     * @return the vertex weight.
     * @exception NoSuchElementException if the graph does not contain the
     * vertex.
     */
    VW& getVertexWeight (const V &v) throw (NoSuchElementException)
    {
      V2VLabel::const_iterator it;

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
    const VW& getVertexWeight (const V &v) const throw (NoSuchElementException)
    {
      V2VLabel::const_iterator it;

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
    void setVertexWeight (const V &v, VW &w) throw (NoSuchElementException)
    {
      V2VLabel::const_iterator it;
      
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
    E& getEdge (const V &h, const V &t) throw (NoSuchElementException)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;
      EV2ELabel::const_iterator ite;

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
    const E& getEdge (const V &h, const V &t) const throw (NoSuchElementException)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;
      EV2ELabel::const_iterator ite;

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
    EW& getEdgeWeight (const V &h, const V &t) throw (NoSuchElementException)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;
      EV2ELabel::const_iterator ite;

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
    const EW& getEdgeWeight (const V &h, const V &t) const throw (NoSuchElementException)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;
      EV2ELabel::const_iterator ite;

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
    void setEdgeWeight (const V &h, const V &t, EW &w) throw (NoSuchElementException)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;
      EV2ELabel::const_iterator ite;

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
    Graph::label getVertexLabel (const V &v) const throw (NoSuchElementException)
    {
      V2VLabel::const_iterator it;

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
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;

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
    list< V > getNeighbors (const V &v)
    {
      list< V > res;
      V2VLabel::const_iterator it;

      if (v2vlabel.end () != (it = v2vlabel.find (&v)))
	{
	  set< Graph::label > nLabels;
	  set< Graph::label >::iterator sit;
	  EV2ELabel::const_iterator evit;
	  Graph::label l;

	  l = it->second;
	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      if (evit->first.getHeadLabel () == l)
		{
		  nLabels.insert (evit->first.getTailLabel ());
		}
	      else if (evit->first.getTailLabel () == l)
		{
		  nLabels.insert (evit->first.getHeadLabel ());
		}
	    }
	  for (sit = nLabels.begin (); nLabels.end () != sit; ++sit)
	    {
	      res.push_back (vertices[*sit]);
	    }
	}
      return res;
    }	  

    /**
     * Gets a vertex given its label.
     * @param l the vertex label.
     * @return the vertex.
     * @exception NoSuchElementException if the graph does not contain the
     * label.
     */
    V& internalGetVertex (Graph::label l) throw (NoSuchElementException)
    {
      if (vertices.size <= l)
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
    const V& internalGetVertex (Graph::label l) const throw (NoSuchElementException)
    {
      if (vertices.size <= l)
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
    VW& internalGetVertexWeight (Graph::label l) throw (NoSuchElementException)
    {
      if (vertexWeights.size <= l)
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
    const VW& internalGetVertexWeight (Graph::label l) const throw (NoSuchElementException)
    {
      if (vertexWeights.size <= l)
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
    void internalSetVertexWeight (Graph::label l, VW &w) throw (NoSuchElementException)
    {
      if (vertexWeights.size <= l)
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
    E& internalGetEdge (Graph::label l) throw (NoSuchElementException)
    {
      if (edges.size <= l)
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
    const E& internalGetEdge (Graph::label l) const throw (NoSuchElementException)
    {
      if (edges.size <= l)
	{
	  throw NoSuchElementException ();
	}
      return edges[l];
    }
    
    /**
     * Gets the edge label between endvertices labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge label.
     * @exception NoSuchElementException if the graph does not contain the
     * labels or the vertices are not connected.
     */
    Graph::label internalGetEdgeLabel (Graph::label h, Graph::label t) const throw (NoSuchElementException)
    {
      EV2ELabel::iterator evit;
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
    EW& internalGetEdgeWeight (Graph::label h, Graph::label t) throw (NoSuchElementException)
    {
      EV2ELabel::iterator evit;
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
    const EW& internalGetEdgeWeight (Graph::label h, Graph::label t) const throw (NoSuchElementException)
    {
      EV2ELabel::iterator evit;
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
    EW& internalGetEdgeWeight (Graph::label l) throw (NoSuchElementException)
    {
      if (edgeWeights.size <= l)
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
    const EW& internalGetEdgeWeight (Graph::label l) const throw (NoSuchElementException)
    {
      if (edgeWeights.size <= l)
	{
	  throw NoSuchElementException ();
	}
      return edgeWeights[l];
    }

    /**
     * Determines if the vertex label is in the graph.
     * @param l the vertex label to find.
     * @return whether the label is within the range of vertices.
     */
    bool internalContains (Graph::label l) const
    {
      return vertices.size () > l;
    }

    /**
     * Returns true if there exists an edge between vertex labels h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return true if there exists an edge between vertices h and t.
     */
    bool internalAreConnected (Graph::label h, Graph::label t) const
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
     * Returns a increasing label list of the neighbors of the given vertex
     * label.  An empty list is returned if the label has no neighbor or if
     * it is not contained in the graph.
     * @param l the vertex label.
     * @return the list of neighbors.
     */
    list< Graph::label > internalGetNeighbors (Graph::label l) const
    {
      list< Graph::label > res;
      V2VLabel::const_iterator it;

      if (vertices.size () > v)
	{
	  set< Graph::label > nLabels;
	  EV2ELabel::const_iterator evit;

	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      if (evit->first.getHeadLabel () == l)
		{
		  nLabels.insert (evit->first.getTailLabel ());
		}
	      else if (evit->first.getTailLabel () == l)
		{
		  nLabels.insert (evit->first.getHeadLabel ());
		}
	    }
	  res.insert (res.end (), nLabels.begin (), nLabels.end ());
	}
      return res;
    }	  

    /**
     * Gets the iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    Graph::iterator begin () { return vertices.begin (); }

    /**
     * Gets the iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    Graph::iterator end () { return vertices.end (); }

    /**
     * Gets the const_iterator pointing to the beginning of the graph vertices.
     * @return the iterator.
     */
    Graph::const_iterator begin () const { return vertices.begin (); }

    /**
     * Gets the const_iterator pointing to the end of the graph vertices.
     * @return the iterator.
     */
    Graph::const_iterator end () const { return vertices.end (); }

    // METHODS --------------------------------------------------------------

    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &v) = 0;
    
    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @param w the vertex weight.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const V &v, VW &w) = 0;
    
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
    virtual Graph::iterator erase (const V &v) = 0;

    /**
     * Finds a vertex in the graph.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    Graph::iterator find (const V &v)
    {
      V2VLabel::const_iterator it;

      return (v2vlabel.end () == (it = v2vlabel.find (&v))
	      ? vertices.end ()
	      : vertices.begin () + it->second);
    }

    /**
     * Finds a vertex in the graph.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    Graph::const_iterator find (const V &v) const
    {
      V2VLabel::const_iterator it;

      return (v2vlabel.end () == (it = v2vlabel.find (&v))
	      ? vertices.end ()
	      : vertices.begin () + it->second);
    }

    /**
     * Gets the number of vertices in this graph.
     * @return the number of vertices in the graph.
     */
    Graph::size_type size () const { return vertices.size (); }
    
    /**
     * Gets the number of edges in this graph.
     * @return the number of edges in the graph.
     */
    Graph::size_type edgeSize () const { return edges.size (); }
    
    /**
     * Determines if the graph is empty.
     * @return true if the graph contains no vertex.
     */
    bool empty () const { return vertices.empty () }
    
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
    
    /**
     * Connects two vertices of the graph with an edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, E &e) = 0;
    
    /**
     * Connects two vertices of the graph with an edge and weight.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &o, const V &p, E &e, W &w) = 0;
    
    /**
     * Disconnects two vertices of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
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
