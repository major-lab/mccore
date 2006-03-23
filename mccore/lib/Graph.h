//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2006 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Martin Larose
// Created On       : Mon Mar 6 00:05:15 2006
// $Revision: 1.27.2.1 $
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

#include <iomanip>
#include <iostream>
#include <functional>
#include <ext/hash_map>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "Algo.h"
// #include "Path.h"

using namespace __gnu_cxx;


namespace mccore
{
  /**
   * Abstract class for the graph classes.  Removing vertices or edges is
   * costly.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.27.2.1 2006-03-23 01:35:35 larosem Exp $
   */
  template< typename V, typename E, typename VW = float, typename EW = float,
	    typename Vertex_Comparator = std::less< V > >
  class Graph
  {
    
  public:

    typedef V                     vertex;
    typedef typename std::vector< vertex >::iterator iterator;
    typedef typename std::vector< vertex >::const_iterator const_iterator;
    typedef typename std::vector< vertex >::size_type size_type;
    typedef typename std::vector< vertex >::size_type label;
    typedef VW                    vertex_weight;
    typedef typename std::vector< vertex_weight >::iterator vweight_iterator;
    typedef typename std::vector< vertex_weight >::const_iterator vweight_const_iterator;
    typedef typename std::vector< vertex_weight >::size_type vweight_size_type;
    typedef typename std::vector< vertex_weight >::size_type vweight_label;
    typedef E                     edge;
    typedef typename std::vector< edge >::iterator edge_iterator;
    typedef typename std::vector< edge >::const_iterator edge_const_iterator;
    typedef typename std::vector< edge >::size_type edge_size_type;
    typedef typename std::vector< edge >::size_type edge_label;
    typedef EW                    edge_weight;
    typedef typename std::vector< edge_weight >::iterator eweight_iterator;
    typedef typename std::vector< edge_weight >::const_iterator eweight_const_iterator;
    typedef typename std::vector< edge_weight >::size_type eweight_size_type;
    typedef typename std::vector< edge_weight >::size_type eweight_label;

  protected:
    
    typedef std::map< const vertex*, label, less_deref< vertex, Vertex_Comparator > > V2VLabel;
    typedef hash_map< label, edge_label > InnerMap;
    typedef hash_map< label, InnerMap > EV2ELabel;
    
    /**
     * The vertex collection.
     */
    std::vector< vertex > vertices;

    /**
     * The vertex weight collection.
     */
    std::vector< vertex_weight > vertexWeights;

    /**
     * The edge collection.
     */
    std::vector< edge > edges;

    /**
     * The edge weight collection.
     */
    std::vector< edge_weight > edgeWeights;

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
    virtual Graph* cloneGraph () const = 0;
//     virtual Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator >* cloneGraph () const = 0;

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
    bool operator== (const Graph &right) const
//     bool operator== (const Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator > &right) const
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
    bool operator!= (const Graph &right) const
//     bool operator!= (const Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator > &right) const
    {
      return ! operator== (right);
    }
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the vertex label.
     * @param v the vertex.
     * @return the vertex label or Graph.size () if the vertex is not in
     * the graph.
     */
    label getVertexLabel (const vertex &v) const
    {
      typename V2VLabel::const_iterator result;
      
      return ((result = v2vlabel.find (&v)) != v2vlabel.end ()
	      ? result->second
	      : size ());
    }
    
    /**
     * Gets the edge label whose endvertices are h and t.
     * @param v the vertex.
     * @return the edge label or edge_size () if no edge connects h and t.
     */
    edge_label getEdgeLabel (const vertex &h, const vertex &t) const
    {
      return internalGetEdgeLabel (getVertexLabel (h), getVertexLabel (t));
    }
    
    /**
     * Determines if the graph contains the vertex v.
     * @param v the vertex to find.
     * @return true if the vertex v is in the graph.
     */
    bool contains (const vertex &v) const
    {
      return end () != find (v);
    }

    /**
     * Returns true if there exists an edge between vertices h and t.
     * @param h an extremity of the edge.
     * @param t an extremity of the edge.
     * @return true if there exists an edge between vertices h and t.
     */
    bool areConnected (const vertex &h, const vertex &t) const
    {
      return edgeSize () > getEdgeLabel (h, t);
    }      
    
    /**
     * Returns the neighbors of the given vertex. An empty list is returned
     * if the vertex has no neighbors or if the graph does not contain the
     * vertex. Vertex order is unsorted and may change on graph modification.
     * @param v a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual std::list< vertex > neighborhood (const vertex &v)
    {
      std::list< vertex > res;
      typename EV2ELabel::const_iterator evit;
      
      if (((typename EV2ELabel::const_iterator) ev2elabel.end ()) != (evit = ev2elabel.find (getVertexLabel (v))))
	{
	  const InnerMap &im = evit->second;
	  typename InnerMap::const_iterator imit;

	  for (imit = im.begin (); im.end () != imit; ++imit)
	    {
	      res.push_back (*internalFind (imit->first));
	    }
	}
      return res;
    }	  

    /**
     * Returns a label list of the out-neighbors of the given vertex label.
     * An empty list is returned if the label has no neighbor or if it is
     * not contained in the graph. Labels order is unsorted and may change
     * on graph modification.
     * @param l the vertex label.
     * @return the list of connected labels to l.
     */
    virtual list< label > internalNeighborhood (label l) const
    {
      list< label > res;
      typename EV2ELabel::const_iterator evit;
      
      if (((typename EV2ELabel::const_iterator) ev2elabel.end ()) != (evit = ev2elabel.find (l)))
	{
	  const InnerMap &im = evit->second;
	  typename InnerMap::const_iterator imit;

	  for (imit = im.begin (); im.end () != imit; ++imit)
	    {
	      res.push_back (imit->first);
	    }
	}
      return res;
    }	  

    /**
     * Finds a vertex whose label is l or end () if the graph does not
     * contain this label.
     * @param l the vertex label.
     * @return the vertex.
     */
    iterator internalFind (label l)
    {
      return (size () > l ? vertices.begin () + l : end ());
    }

    /**
     * Finds a vertex whose label is l or end () if the graph does not
     * contain this label.
     * @param l the vertex label.
     * @return the vertex.
     */
    const_iterator internalFind (label l) const
    {
      return (size () > l ? vertices.begin () + l : end ());
    }

    /**
     * Finds a vertex weight whose label is l or end () if the graph does not
     * contain this label.
     * @param l the vertex label.
     * @return the vertex weight.
     */
    vweight_iterator internalFindWeight (label l)
    {
      return (size () > l ? vertexWeights.begin () + l : vweight_end ());
    }

    /**
     * Finds a vertex weight whose label is l or end () if the graph does not
     * contain this label.
     * @param l the vertex label.
     * @return the vertex weight.
     */
    vweight_const_iterator internalFindWeight (label l) const
    {
      return (size () > l ? vertexWeights.begin () + l : vweight_end ());
    }
    
    /**
     * Gets the edge label between endvertices labels h and t. 
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge label or graph.edge_size () if no edges exists between
     * h and t.
     */
    edge_label internalGetEdgeLabel (label h, label t) const
    {
      typename EV2ELabel::const_iterator headIt;

      if (((typename EV2ELabel::const_iterator) ev2elabel.end ()) != (headIt = ev2elabel.find (h)))
	{
	  const InnerMap &im = headIt->second;
	  typename InnerMap::const_iterator tailIt;

	  if (im.end () != (tailIt = im.find (t)))
	    {
	      return tailIt->second;
	    }
	}
      return edges.size ();
    }
    
    /**
     * Finds an edge whose endlabels are h and t or edge_end () if no edge
     * connects h and t.
     * @param h the endvertices head label.
     * @param t the endvertices tail label.
     * @return the edge.
     */
    edge_iterator internalFindEdge (label h, label t)
    {
      return edges.begin () + internalGetEdgeLabel (h, t);
    }
    
    /**
     * Finds an edge whose endlabels are h and t or edge_end () if no edge
     * connects h and t.
     * @param h the endvertices head label.
     * @param t the endvertices tail label.
     * @return the edge.
     */
    edge_const_iterator internalFindEdge (label h, label t) const
    {
      return edges.begin () + internalGetEdgeLabel (h, t);
    }
    
    /**
     * Finds an edge whose label is l or edge_end () if the graph does not
     * contain this label.
     * @param l the edge label.
     * @return the edge.
     */
    edge_iterator internalFindEdge (edge_label l)
    {
      return (edgeSize () > l ? edges.begin () + l : edge_end ());
    }
    
    /**
     * Finds an edge whose label is l or edge_end () if the graph does not
     * contain this label.
     * @param l the edge label.
     * @return the edge.
     */
    edge_const_iterator internalFindEdge (edge_label l) const
    {
      return (edgeSize () > l ? edges.begin () + l : edge_end ());
    }

    /**
     * Finds an edge weight whose endlabels are h and t or eweight_end () if
     * no edge connects h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge weight.
     */
    eweight_iterator internalFindEdgeWeight (label h, label t)
    {
      return edgeWeights.begin () + internalGetEdgeLabel (h, t);
    }
    
    /**
     * Finds an edge weight whose endlabels are h and t or eweight_end () if
     * no edge connects h and t.
     * @param h the head label of the edge.
     * @param t the tail label of the edge.
     * @return the edge weight.
     */
    eweight_const_iterator internalFindEdgeWeight (label h, label t) const
    {
      return edgeWeights.begin () + internalGetEdgeLabel (h, t);
    }
    
    /**
     * Finds an edge weight whose edge label is l or eweight_end () if the
     * graph does not contain this label.
     * @param l the edge label.
     * @return the edge weight.
     */
    eweight_iterator internalFindEdgeWeight (edge_label l)
    {
      return (edgeSize () > l ? edgeWeights.begin () + l : eweight_end ());
    }

    /**
     * Finds an edge weight whose edge label is l or eweight_end () if the
     * graph does not contain this label.
     * @param l the edge label.
     * @return the edge weight.
     */
    eweight_const_iterator internalFindEdgeWeight (edge_label l) const
    {
      return (edgeSize () > l ? edgeWeights.begin () + l : eweight_end ());
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
      return edges.size () != internalGetEdgeLabel (h, t);
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
     * Gets the iterator pointing to the beginning of the graph vertex weights.
     * @return the iterator.
     */
    vweight_iterator vweight_begin () { return vertexWeights.begin (); }

    /**
     * Gets the iterator pointing to the end of the graph vertex weights.
     * @return the iterator.
     */
    vweight_iterator vweight_end () { return vertexWeights.end (); }

    /**
     * Gets the const_iterator pointing to the beginning of the graph vertex
     * weights.
     * @return the iterator.
     */
    vweight_const_iterator vweight_begin () const { return vertexWeights.begin (); }

    /**
     * Gets the const_iterator pointing to the end of the graph vertex
     * weights.
     * @return the iterator.
     */
    vweight_const_iterator vweight_end () const { return vertexWeights.end (); }

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

    /**
     * Gets the iterator pointing to the beginning of the graph edge weights.
     * @return the iterator.
     */
    eweight_iterator eweight_begin () { return edgeWeights.begin (); }

    /**
     * Gets the iterator pointing to the end of the graph edge weights.
     * @return the iterator.
     */
    eweight_iterator eweight_end () { return edgeWeights.end (); }

    /**
     * Gets the const_iterator pointing to the beginning of the graph edge
     * weights.
     * @return the iterator.
     */
    eweight_const_iterator eweight_begin () const { return edgeWeights.begin (); }

    /**
     * Gets the const_iterator pointing to the end of the graph edge weights.
     * @return the iterator.
     */
    eweight_const_iterator eweight_end () const { return edgeWeights.end (); }

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Rebuilds the vertex to vertex label map.
     */
    void rebuildV2VLabel ()
    {
      typename std::vector< vertex >::iterator it;
      
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
    virtual bool insert (const vertex &v)
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
    virtual bool insert (const vertex &v, const vertex_weight &w)
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
    template <typename InputIterator>
    void insertRange (InputIterator f, InputIterator l)
    {
      for (; l != f; ++f)
	{
	  insert (*f);
	}
    }

  protected:
    
    /**
     * Rebuilds the mapping between vertices and edges when some were
     * deleted.  If a label inside the mapping vectors is equal to the
     * vector size, it means that this label has been deleted.
     * @param vertexmapping the mapping between the old and the new vertices.
     * @param edgemapping the mapping between the old and the new edges.
     */
    void rebuildEV2ELabel (const std::vector< label > &vertexmapping, const std::vector< edge_label > &edgemapping)
    {
      label sz = vertexmapping.size ();
      edge_label esz = edgemapping.size ();
      EV2ELabel newMap;
      typename EV2ELabel::iterator eit;

      for (eit = ev2elabel.begin (); ((typename EV2ELabel::iterator) ev2elabel.end ()) != eit; ++eit)
	{
	  label h;
	  
	  if (sz != (h = vertexmapping[eit->first]))
	    {
	      const InnerMap &im = eit->second;
	      typename InnerMap::const_iterator imit;
	      InnerMap newInner;

	      for (imit = im.begin (); im.end () != imit; ++imit)
		{
		  label t;
		  edge_label e;
	      
		  if (sz != (t = vertexmapping[imit->first])
		      && esz != (e = edgemapping[imit->second]))
		    {
		      newInner[t] = e;
		    }
		}
	      if (! newInner.empty ())
		{
		  newMap[h] = newInner;
		}
	    }
	}
      ev2elabel = newMap;
    }

    /**
     * Builds the set of edges to delete according to the given vertex set.
     * @param labelset the set of labels to delete.
     * @param edgelabelset the set of edge labels that will have to be deleted.
     */
    virtual void edgestodelete (const std::set< label > &labelset, std::set< edge_label > &edgelabelset) const
    {
      typename std::set< label >::const_iterator lsit;
      typename EV2ELabel::const_iterator ev2elit;

      edgelabelset.clear ();
      for (lsit = labelset.begin (); labelset.end () != lsit; ++lsit)
	{
	  if (((typename EV2ELabel::const_iterator) ev2elabel.end ()) != (ev2elit = ev2elabel.find (*lsit)))
	    {
	      const InnerMap &im = ev2elit->second;
	      typename InnerMap::const_iterator imit;

	      for (imit = im.begin (); im.end () != imit; ++imit)
		{
		  edgelabelset.insert (imit->second);
		}
	    }
	}
      for (ev2elit = ev2elabel.begin (); ((typename EV2ELabel::const_iterator) ev2elabel.end ()) != ev2elit; ++ev2elit)
	{
	  label h = ev2elit->first;

	  if (labelset.end () == labelset.find (h))
	    {
	      const InnerMap &im = ev2elit->second;
	      typename InnerMap::const_iterator imit;

	      for (imit = im.begin (); im.end () != imit; ++imit)
		{
		  if (labelset.end () != labelset.find (imit->first))
		    {
		      edgelabelset.insert (imit->second);
		    }
		}
	    }
	}
    }
        
    /**
     * Erases a set of vertices and edges whose labels are in labelset and
     * edgelabelset respectively.
     * @param labelset the vertex labels to remove.
     */
    void internalErase (const std::set< label > &labelset, const std::set< edge_label > &edgelabelset)
    {
      size_type sz = size ();
      edge_size_type esz = edgeSize ();
      std::vector< label > vertexmapping (sz);
      std::vector< edge_label > edgemapping (esz);
      
      if (! labelset.empty ())
	{
	  label count;
	  label ocount;
	  iterator vit;
	  vweight_iterator vwit;
	  typename std::set< label >::const_iterator lsit;

	  // Remove vertex and build vertex mapping vector.
	  for (count = 0, ocount = 0, vit = begin (), vwit = vweight_begin (), lsit = labelset.begin ();
	       labelset.end () != lsit;
	       ++ocount)
	    {
	      if (ocount < *lsit)
		{
		  vertexmapping[ocount] = count;
		  ++count;
		  ++vit;
		  ++vwit;
		}
	      else
		{
		  vertexmapping[ocount] = sz;
		  vit = vertices.erase (vit);
		  vwit = vertexWeights.erase (vwit);
		  ++lsit;
		}
	    }
	  while (sz > ocount)
	    {
	      vertexmapping[ocount] = count;
	      ++count;
	      ++ocount;
	    }
	  rebuildV2VLabel ();
	}
      else
	{
	  label label;

	  for (label = 0; sz > label; ++label)
	    {
	      vertexmapping[label] = label;
	    }
	}
	  
      // Remove edges and build edge mapping vector.
      if (! edgelabelset.empty ())
	{
	  edge_label ecount;
	  edge_label oecount;
	  edge_iterator eit;
	  eweight_iterator ewit;
	  typename std::set< edge_label >::const_iterator elsit;

	  for (ecount = 0, oecount = 0, eit = edge_begin (), ewit = eweight_begin (), elsit = edgelabelset.begin ();
	       edgelabelset.end () != elsit;
	       ++oecount)
	    {
	      if (oecount < *elsit)
		{
		  // increase everybody except edgelabelset iterator
		  edgemapping[oecount] = ecount;
		  ++ecount;
		  ++eit;
		  ++ewit;
		}
	      else
		{
		  // found an edge to delete
		  edgemapping[oecount] = esz;
		  eit = edges.erase (eit);
		  ewit = edgeWeights.erase (ewit);
		  ++elsit;
		}
	    }
	  while (esz > oecount)
	    {
	      edgemapping[oecount] = ecount;
	      ++ecount;
	      ++oecount;
	    }
	}
      else
	{
	  edge_label elabel;

	  for (elabel = 0; esz > elabel; ++elabel)
	    {
	      edgemapping[elabel] = elabel;
	    }
	}
      rebuildEV2ELabel (vertexmapping, edgemapping);
    }
    
    /**
     * Erases a set of vertices whose labels are in labelset.  If an edge is
     * connected to these vertex labels they are also removed.
     * @param labelset the vertex labels to remove.
     */
    void internalErase (const std::set< label > &labelset)
    {
      std::set< edge_label > edgelabelset;

      // Build the set of edges to delete.
      edgestodelete (labelset, edgelabelset);
      internalErase (labelset, edgelabelset);
    }

  public:
    
    /**
     * Erases a vertex whose label is l.  If an edge is connected to this
     * vertex label it is also removed.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element or end () if the
     * vertex was not found.
     */
    iterator internalErase (label l)
    {
      if (size () > l)
	{
	  std::set< label > labelset;

	  labelset.insert (l);
	  internalErase (labelset);
	  return begin () + l;
	}
      else
	{
	  return end ();
	}
    }      
    
    /**
     * Erase a vertex from the graph.  If an edge is connected to this
     * vertex it is also removed.
     * @param v the vertex to remove.
     * @return an iterator over the next vertex element or end () if the
     * vertex was not found.
     */
    iterator erase (const vertex &v)
    {
      return internalErase (getVertexLabel (v));
    }
    
    /**
     * Finds a vertex whose key is v.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    iterator find (const vertex &v)
    {
      return vertices.begin () + getVertexLabel (v);
    }

    /**
     * Finds a vertex whose key is v.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on end () if not found.
     */
    const_iterator find (const vertex &v) const
    {
      return vertices.begin () + getVertexLabel (v);
    }

    /**
     * Finds a vertex weight whose key is v.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on vweight_end () if v is
     * not found.
     */
    vweight_iterator findWeight (const vertex &v)
    {
      return vertexWeights.begin () + getVertexLabel (v);
    }

    /**
     * Finds a vertex weight whose key is v.
     * @param v the vertex to find.
     * @return an iterator on the found vertex or on vweight_end () if v is
     * not found.
     */
    vweight_const_iterator findWeight (const vertex &v) const
    {
      return vertexWeights.begin () + getVertexLabel (v);
    }

    /**
     * Finds an edge whose endvertices are h and t.
     * @param h the head vertex.
     * @param t the tail vertex.
     * @return an iterator on the found edge or on edge_end () if not found.
     */
    edge_iterator find (const vertex &h, const vertex &t)
    {
      return edges.begin () + getEdgeLabel (h, t);
    }

    /**
     * Finds an edge whose endvertices are h and t.
     * @param h the head vertex.
     * @param t the tail vertex.
     * @return an iterator on the found edge or on edge_end () if not found.
     */
    edge_const_iterator find (const vertex &h, const vertex &t) const
    {
      return edges.begin () + getEdgeLabel (h, t);
    }

    /**
     * Finds an edge weight whose endvertices are h and t.
     * @param h the head vertex.
     * @param t the tail vertex.
     * @return an iterator on the found edge weight or on eweight_end () if
     * not found.
     */
    eweight_iterator findWeight (const vertex &h, const vertex &t)
    {
      return edgeWeights.begin () + getEdgeLabel (h, t);
    }

    /**
     * Finds an edge weight whose endvertices are h and t.
     * @param h the head vertex.
     * @param t the tail vertex.
     * @return an iterator on the found edge weight or on eweight_end () if
     * not found.
     */
    eweight_const_iterator findWeight (const vertex &h, const vertex &t) const
    {
      return edgeWeights.begin () + getEdgeLabel (h, t);
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

    /**
     * Connects two vertices labels of the graph with an edge.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded or false if the
     * labels were already connected.
     */
    virtual bool internalConnect (label h, label t, const edge &e)
    {
      if (size () > h
	  && size () > t
	  && edgeSize () == internalGetEdgeLabel (h, t))
	{
	  InnerMap im;
	  edge_label el;
	  std::pair< typename EV2ELabel::iterator, bool > inserted;
	  
	  im[t] = el = edgeSize ();
	  edges.push_back (e);
	  edgeWeights.resize (edgeWeights.size () + 1);
	  inserted = ev2elabel.insert (std::make_pair (h, im));
	  if (! inserted.second)
	    {
	      inserted.first->second[t] = el;
	    }
	  return true;
	}
      else
	{
	  return false;
	}
    }
    
    /**
     * Connects two vertices labels of the graph with an edge and weight.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool internalConnect (label h, label t, const edge &e, const edge_weight &w)
    {
      if (size () > h
	  && size () > t
	  && edgeSize () == internalGetEdgeLabel (h, t))
	{
	  InnerMap im;
	  edge_label el;
	  std::pair< typename EV2ELabel::iterator, bool > inserted;

	  im[t] = el = edgeSize ();
	  edges.push_back (e);
	  edgeWeights.push_back (w);
	  inserted = ev2elabel.insert (std::make_pair (h, im));
	  if (! inserted.second)
	    {
	      inserted.first->second[t] = el;
	    }
	  return true;
	}
      else
	{
	  return false;
	}
    }
    
    /**
     * Connects two vertices of the graph with an edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    bool connect (const vertex &h, const vertex &t, const edge &e)
    {
      return internalConnect (getVertexLabel (h), getVertexLabel (t), e);
    }      
    
    /**
     * Connects two vertices of the graph with an edge and weight.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    bool connect (const vertex &h, const vertex &t, const edge &e, const edge_weight &w)
    {
      return internalConnect (getVertexLabel (h), getVertexLabel (t), e, w);
    }
    
    /**
     * Disconnects two endvertices labels of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool internalDisconnect (label h, label t)
    {
      edge_label e;
      
      if (edgeSize () > (e = internalGetEdgeLabel (h, t)))
	{
	  std::set< label > labelset;
	  std::set< edge_label > edgelabelset;

	  edgelabelset.insert (e);
	  internalErase (labelset, edgelabelset);
	  return true;
	}
      else
	{
	  return false;
	}
    }
    
    /**
     * Disconnects two endvertices of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    bool disconnect (const vertex &h, const vertex &t)
    {
      return internalDisconnect (getVertexLabel (h), getVertexLabel (t));
    }
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the graph to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual std::ostream& write (std::ostream& os) const
    {
      typename std::vector< vertex >::const_iterator vit;
      typename std::vector< vertex_weight >::const_iterator vwit;
      typename std::vector< edge >::const_iterator eit;
      typename std::vector< edge_weight >::const_iterator ewit;
      typename EV2ELabel::const_iterator evit;
      label rowcounter;
      label linecounter;
      label sz = size ();
      edge_label esz = edgeSize ();

      os << "[Vertices]" << std::endl;
      for (vit = vertices.begin (), vwit = vertexWeights.begin (), rowcounter = 0; vertices.end () != vit; ++vit, ++vwit, ++rowcounter)
	{
	  os << std::setw (5) << rowcounter << "  " << *vit << "  " << *vwit << std::endl;
	}
      os << "[Edges]" << std::endl;
      for (eit = edges.begin (), ewit = edgeWeights.begin (), rowcounter = 0; edges.end () != eit; ++eit, ++ewit, ++rowcounter)
	{
	  os << std::setw (5) << rowcounter << "  " << *eit << "  " << *ewit << std::endl;
	}
      os << "[Adjacency matrix]" << std::endl;
      os << "     ";
      for (rowcounter = 0; vertices.size () > rowcounter; ++rowcounter)
	{
	  os << std::setw (5) << rowcounter;
	}
      for (linecounter = 0; sz > linecounter; ++linecounter)
	{
	  os << std::endl << std::setw (5) << linecounter;
	  for (rowcounter = 0; sz > rowcounter; ++rowcounter)
	    {
	      edge_label edge;
	      
	      if (esz == (edge = internalGetEdgeLabel (linecounter, rowcounter)))
		{
		  os << std::setw (5) << '.';
		}
	      else
		{
		  os << std::setw (5) << edge;
		}
	    }
	}
      os << std::endl;      
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
  template < typename vertex, typename edge, typename vertex_weight, typename edge_weight, typename VC >
  ostream& operator<< (ostream &os, const mccore::Graph< vertex, edge, vertex_weight, edge_weight, VC > &obj)
  {
    return obj.write (os);
  }
  
}

#endif
