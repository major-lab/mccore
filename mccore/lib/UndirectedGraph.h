//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 10 19:09:13 2004
// $Revision: 1.12.2.10 $
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
#include <limits>
#include <list>
#include <utility>
#include <vector>

#include "Graph.h"

using namespace std;



namespace mccore
{
  /**
   * Undirected graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: UndirectedGraph.h,v 1.12.2.10 2004-12-27 01:54:55 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class UndirectedGraph : public Graph< V, E, VW, EW, Vertex_Comparator>
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
    UndirectedGraph () : Graph< V, E, VW, EW, Vertex_Comparator > () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    UndirectedGraph (const UndirectedGraph &right)
      : Graph< V, E, VW, EW, Vertex_Comparator > (right) { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph< V, E, VW, EW, Vertex_Comparator >* cloneGraph () const
    {
      return new UndirectedGraph< V, E, VW, EW, Vertex_Comparator> (*this);
    }

    /**
     * Destroys the object.
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
	  Graph< V, E, VW, EW, Vertex_Comparator>::operator= (right);
	}
      return *this;
    }	  

    /**
     * Tests whether the graphs are equals.
     * @param right a graph to compare with this.
     * @return whether the graphs are equals.
     */
    bool operator== (const UndirectedGraph &right) const
    {
      return (this == &right
	      || Graph< V, E, VW, EW, Vertex_Comparator>::operator== (right));
    }
    
    /**
     * Tests whether the graphs differs.
     * @param right a graph to compare with this.
     * @return whether the graphs differs.
     */
    bool operator!= (const UndirectedGraph &right) const
    {
      return ! operator== (right);
    }
    
    // ACCESS ---------------------------------------------------------------

    /**
     * Returns the neighbors of the given vertex. An empty list is returned
     * if the vertex has no neighbors or if the graph does not contain the
     * vertex.
     * @param v a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual list< V > neighborhood (const V &v)
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
     * Returns a label list of the out-neighbors of the given vertex label.
     * An empty list is returned if the label has no neighbor or if it is
     * not contained in the graph.
     * @param l the vertex label.
     * @return the list of out-neighbors.
     */
    virtual list< label > internalNeighborhood (label l) const
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
      list< label > neighbors = internalNeighborhood (l);
      typename list< label >::iterator lit;
      typename EV2ELabel::iterator evit;
      EV2ELabel newEV2;
      typename vector< V >::iterator res;
      
      for (lit = neighbors.begin (); neighbors.end () != lit; ++lit)
	{
	  uncheckedInternalDisconnect (l, *lit);
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
     * Connects two vertices labels of the graph with an edge.  Two
     * endvertices are added, pointing to the same edge.  No check are
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
	  if (h != t)
	    {
	      EndVertices ev2 (t, h);
	      
	      ev2elabel.insert (make_pair (ev2, edges.size ()));
	    }
	  edges.push_back (e);
	  edgeWeights.resize (edgeWeights.size () + 1);
	  return true;
	}
      return false;
    }

    /**
     * Connects two vertices of the graph with an edge and weight.  Two
     * endvertices are added, pointing to the same edge.  No check are
     * made on vertex labels validity.
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
	  if (h != t)
	    {
	      EndVertices ev2 (t, h);
	      
	      ev2elabel.insert (make_pair (ev2, edges.size ()));
	    }
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
	  EndVertices ev2 (t, h);
	  label l;
	  
	  l = evit->second;
	  edges.erase (edges.begin () + l);
	  edgeWeights.erase (edgeWeights.begin () + l);
	  ev2elabel.erase (evit);
	  if (ev2elabel.end () != (evit = ev2elabel.find (ev2)))
	    {
	      ev2elabel.erase (evit);
	    }
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

    /**
     * Prim's algorithm for the minimum spanning tree.
     * @param graph an undirected graph
     * @param edge_nodes a vector of pairs of node ids.
     * @return a vector of edges representing a spanning tree of the graph.
     */
    static void minimumSpanningTree (const UndirectedGraph< V, E, VW, EW, Vertex_Comparator > &graph, vector< pair< label, label > > &edge_nodes) 
    {
      vector< label > nearest (graph.size (), 0);
      vector< float > mindist (graph.size (), numeric_limits< float >::max ());
      unsigned int i;
      unsigned int j;

      if (! graph.empty ())
	{
	  // Initialize
	  for (i = 1; i < graph.size (); ++i)
	    {
	      if (graph.internalAreConnected (i, 0))
		{
		  mindist[i] = graph.internalGetEdgeWeight (i, 0);
		}
	    }
	  edge_nodes.clear ();
  
	  // Execute
	  for (i = 0; i < graph.size () - 1; ++i)
	    {
	      float min = numeric_limits< float >::max ();
	      label k = numeric_limits< unsigned int >::max ();
	  
	      for (j = 1; j < graph.size (); ++j)
		{
		  if (mindist[j] >= 0 && mindist[j] < min)
		    {
		      min = mindist[j];
		      k = j;
		    }
		}
	
	      // This is a test to see if we stay in the same connected
	      // component
	      if (k != numeric_limits< unsigned int >::max ())
		{
		  edge_nodes.push_back (make_pair (nearest[k], k));
		  mindist[k] = numeric_limits< unsigned int >::max ();
	    
		  for (j = 1; j < graph.size (); ++j)
		    {
		      float val = (graph.internalAreConnected (j, k)
				   ? graph.internalGetEdgeWeight (j, k)
				   : numeric_limits< float >::max ());
		    if (val < mindist[j])
		      {
			mindist[j] = val;
			nearest[j] = k;
		      }
		    }
		}
	    }
	}
    }

  public:
    
    /**
     * Prim's algorithm for the minimum spanning tree.
     * @return a vector of edges representing a spanning tree of the graph.
     */
    vector< pair< V, V > > minimumSpanningTree () const
    {
      vector< pair< label, label > > aedges;
      typename vector< pair< label, label > >::iterator i;
      vector< pair< V, V > > realedges;

      UndirectedGraph::minimumSpanningTree (*this, aedges);
      for (i = aedges.begin (); aedges.end () != i; ++i)
	{
	  realedges.push_back (make_pair (vertices[i->first], vertices[i->second]));
	}
      return realedges;
    }
    
    // I/O  -----------------------------------------------------------------

  public:
    
    /**
     * Writes the object to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual ostream& write (ostream& os) const
    {
      os << "[UndirectedGraph]" << endl;
      return Graph< V, E, VW, EW, Vertex_Comparator >::write (os);
    }
    
  };

}

#endif
