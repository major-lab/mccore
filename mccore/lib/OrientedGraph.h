//                              -*- Mode: C++ -*- 
// OrientedGraph.h
// Copyright � 2001-05 Laboratoire de Biologie Informatique et Th�orique.
//                     Universit� de Montr�al.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// $Revision: 1.3 $
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


#ifndef _mccore_OrientedGraph_h_
#define _mccore_OrientedGraph_h_

#include <functional>
#include <list>
#include <utility>
#include <vector>

#include "Graph.h"
#include "Path.h"

using namespace std;



namespace mccore
{
  /**
   * Directed graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: OrientedGraph.h,v 1.3 2005-02-01 22:13:33 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class OrientedGraph : public Graph< V, E, VW, EW, Vertex_Comparator >
  {

  public:

    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::size_type size_type;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::label label;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::iterator iterator;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::const_iterator const_iterator;

  protected:
    
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::V2VLabel V2VLabel;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::EV2ELabel EV2ELabel;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::EndVertices EndVertices;

  public:
    
    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    OrientedGraph () : Graph< V, E, VW, EW, Vertex_Comparator > () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    OrientedGraph (const OrientedGraph &right)
      : Graph< V, E, VW, EW, Vertex_Comparator > (right) { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph< V, E, VW, EW, Vertex_Comparator >* cloneGraph () const
    {
      return new OrientedGraph< V, E, VW, EW, Vertex_Comparator> (*this);
    }

    /**
     * Destroys the object.
     */
    virtual ~OrientedGraph () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    OrientedGraph& operator= (const OrientedGraph &right)
    {
      if (this != &right)
	{
	  Graph< V, E, VW, EW, Vertex_Comparator>::operator= (right);
	}
      return *this;
    }	  

    /**
     * Tests whether the graphs are equals.
     * @param right a graph to compare with this.
     * @return whether the graphs are equals.
     */
    bool operator== (const OrientedGraph &right) const
    {
      return (this == &right
	      || Graph< V, E, VW, EW, Vertex_Comparator>::operator== (right));
    }
    
    /**
     * Tests whether the graphs differs.
     * @param right a graph to compare with this.
     * @return whether the graphs differs.
     */
    bool operator!= (const OrientedGraph &right) const
    {
      return ! operator== (right);
    }
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Returns the in-neighbors of the given vertex. An empty list is
     * returned if the vertex has no neighbors or if the graph does not
     * contain the vertex.
     * @param v a vertex in the graph.
     * @return the list of in-neighbors.
     */
    virtual list< V > inNeighborhood (const V &v)
    {
      list< V > res;
      typename V2VLabel::const_iterator it;

      if (v2vlabel.end () != (it = v2vlabel.find (&v)))
	{
	  typename EV2ELabel::const_iterator evit;
	  label l;

	  l = it->second;
	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      if (evit->first.getTailLabel () == l)
		{
		  res.push_back (vertices[evit->first.getHeadLabel ()]);
		}
	    }
	}
      return res;
    }	  

    /**
     * Returns the out-neighbors of the given vertex. An empty list is
     * returned if the vertex has no neighbors or if the graph does not
     * contain the vertex.
     * @param v a vertex in the graph.
     * @return the list of out-neighbors.
     */
    virtual list< V > outNeighborhood (const V &v)
    {
      list< V > res;
      typename V2VLabel::const_iterator it;

      if (v2vlabel.end () != (it = v2vlabel.find (&v)))
	{
	  typename EV2ELabel::const_iterator evit;
	  label l;

	  l = it->second;
	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit && evit->first.getHeadLabel () <= l; ++evit)
	    {
	      if (evit->first.getHeadLabel () == l)
		{
		  res.push_back (vertices[evit->first.getTailLabel ()]);
		}
	    }
	}
      return res;
    }	  

    /**
     * Returns a label list of the in-neighbors of the given vertex label.
     * An empty list is returned if the label has no in-neighbor or if it is
     * not contained in the graph.
     * @param l the vertex label.
     * @return the list of in-neighbors.
     */
    virtual list< label > internalInNeighborhood (label l) const 
    {
      list< label > res;

      if (vertices.size () > l)
	{
	  typename EV2ELabel::const_iterator evit;

	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      if (evit->first.getTailLabel () == l)
		{
		  res.push_back (evit->first.getHeadLabel ());
		}
	    }
	}
      return res;
    }	  
    
    /**
     * Returns a label list of the neighbors of the given vertex label.  An
     * empty list is returned if the label has no neighbor or if it is not
     * contained in the graph.
     * @param l the vertex label.
     * @return the list of out-neighbors.
     */
    virtual list< label > internalOutNeighborhood (label l) const
    {
      list< label > res;

      if (vertices.size () > l)
	{
	  typename EV2ELabel::const_iterator evit;

	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit && evit->first.getHeadLabel () <= l; ++evit)
	    {
	      if (evit->first.getHeadLabel () == l)
		{
		  res.push_back (evit->first.getTailLabel ());
		}
	    }
	}
      return res;
    }	  

    /**
     * Returns the neighbors of the given vertex sorted over their label. An
     * empty list is returned if the vertex has no neighbors or if the graph
     * does not contain the vertex.  It is a alias for outNeighborhood.
     * @param v a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual list< V > neighborhood (const V &v)
    {
      return outNeighborhood (v);
    }
    
    /**
     * Returns a increasing label list of the out-neighbors of the given vertex
     * label.  An empty list is returned if the label has no neighbor or if
     * it is not contained in the graph.  It is an alias for
     * internalOutNeighborhood.
     * @param l the vertex label.
     * @return the list of out-neighbors.
     */
    virtual list< label > internalNeighborhood (label l) const
    {
      return internalOutNeighborhood (l);
    }
    
    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Erase a vertex label from the graph.  If an edge is connected to this
     * vertex label it is also removed.  No check is made on label validity.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element.
     */
    virtual iterator uncheckedInternalErase (label l)
    {
      list< label > outNeighbors = internalOutNeighborhood (l);
      list< label > inNeighbors = internalInNeighborhood (l);
      typename list< label >::iterator lit;
      iterator res;
      typename EV2ELabel::iterator evit;
      EV2ELabel newEV2;
      
      for (lit = outNeighbors.begin (); outNeighbors.end () != lit; ++lit)
	{
	  uncheckedInternalDisconnect (l, *lit);
	}
      for (lit = inNeighbors.begin (); inNeighbors.end () != lit; ++lit)
	{
	  uncheckedInternalDisconnect (*lit, l);
	}
      res = vertices.erase (vertices.begin () + l);
      vertexWeights.erase (vertexWeights.begin () + l);
      rebuildV2VLabel ();
	  
      for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	{
	  label h;
	  label t;
	  
	  h = evit->first.getHeadLabel ();
	  t = evit->first.getTailLabel ();
	  if (h > l)
	    {
	      --h;
	    }
	  if (t > l)
	    {
	      --t;
	    }
	  
	  EndVertices ev (h, t);
	  newEV2.insert (make_pair (ev, evit->second));
	}
      ev2elabel = newEV2;
      return res;
    }

    /**
     * Connects two vertices labels of the graph with an edge.  No check are
     * made on vertex labels validity.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, const E &e)
    {
      EndVertices ev (h, t);
      typename EV2ELabel::const_iterator evit;
      
      if (ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  ev2elabel.insert (make_pair (ev, edges.size ()));
	  edges.push_back (e);
	  edgeWeights.resize (edgeWeights.size () + 1);
	  return true;
	}
      return false;
    }

    /**
     * Connects two vertices of the graph with an edge and weight.  No check
     * are made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, const E &e, const EW &w)
    {
      EndVertices ev (h, t);
      typename EV2ELabel::const_iterator evit;
      
      if (ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  ev2elabel.insert (make_pair (ev, edges.size ()));
	  edges.push_back (e);
	  edgeWeights.push_back (w);
	  return true;
	}
      return false;
    }
    
    /**
     * Disconnects two endvertices labels of the graph.  No check are
     * made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool uncheckedInternalDisconnect (label h, label t)
    {
      EndVertices ev (h, t);
      typename EV2ELabel::iterator evit;
      
      if (ev2elabel.end () != (evit = ev2elabel.find (ev)))
	{
	  label l;
	  
	  l = evit->second;
	  edges.erase (edges.begin () + l);
	  edgeWeights.erase (edgeWeights.begin () + l);
	  ev2elabel.erase (evit);
	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      if (evit->second > l)
		{
		  --evit->second;
		}
	    }
	  return true;
	}
      return false;
    }      

  public:
    
    /**
     * Finds the all the paths from the label q to the root.  Must be a non
     * cyclic graph.  edge weights must implement operator+.
     * @param Dr the oriented graph (with no cycles).
     * @param q the starting label.
     * @return a collection of Paths from q to the root in Dr.
     */
    vector< Path< V, EW > > breadthFirstPaths (label q) const
    {
      vector< Path< V, EW> > result;
      list< Path< label, EW > > lst (1, Path< label, EW > ());
      Path< label, EW > &tmp = lst.front ();
      
      tmp.push_back (q);
      tmp.setValue (0);
      while (! lst.empty ())
	{
	  Path< label, unsigned int > &front = lst.front ();
	  label endNode;
	  list< label > neighbors;
	  typename list< label >::iterator neighborsIt;

	  endNode = front.back ();
	  neighbors = internalOutNeighborhood (endNode);
	  neighborsIt = neighbors.begin ();
	  if (neighbors.end () == neighborsIt)
	    {
	      typename Path< label, EW >::reverse_iterator rIt;

	      result.push_back (Path< V, EW > ());
	      Path< V, EW > &tmp = result.back ();
	      
	      for (rIt = front.rbegin (); front.rend () != rIt; ++rIt)
		{
		  tmp.push_back (internalGetVertex (*rIt));
		}
	      tmp.setValue (front.getValue ());
	    }
	  else
	    {
	      for (; neighbors.end () != neighborsIt; ++neighborsIt)
		{
		  lst.push_back (front);
		  Path< label, EW > &tmp = lst.back ();

		  tmp.push_back (*neighborsIt);
		  tmp.setValue (tmp.getValue () + internalGetEdgeWeight (endNode, *neighborsIt));
		}
	    }
	  lst.pop_front ();
	}
      return result;
    }

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual ostream& write (ostream& os) const
    {
      os << "[OrientedGraph]" << endl;
      return Graph< V, E, VW, EW, Vertex_Comparator >::write (os);
    }
    
  };

}

#endif
