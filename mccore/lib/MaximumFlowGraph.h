//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.10.4.3 $
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


#ifndef _mccore_MaximumFlowGraph_h_
#define _mccore_MaximumFlowGraph_h_

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <list>

#include "Messagestream.h"
#include "OrientedGraph.h"
#include "stlio.h"



namespace mccore
{
  
  /**
   * Maximum flow in a directed graph.  The edges must implements the method:
   * <pre>
   *      float getValue ()
   * </pre>
   * for flow calculation.
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: MaximumFlowGraph.h,v 1.10.4.3 2004-12-16 17:08:39 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class Vertex_Comparator = less< V > >	    
  class MaximumFlowGraph : public OrientedGraph< V, E, VW, float, Vertex_Comparator >
  {  
    
  public:
    
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::size_type size_type;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::label label;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::iterator iterator;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::const_iterator const_iterator;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::V2VLabel V2VLabel;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::EV2ELabel EV2ELabel;
    typedef typename OrientedGraph< V, E, VW, float, Vertex_Comparator >::EndVertices EndVertices;

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    MaximumFlowGraph ()
      : OrientedGraph< V, E, VW, float, Vertex_Comparator > ()
    { }
    
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    MaximumFlowGraph (const MaximumFlowGraph &right)
      : OrientedGraph< V, E, VW, float, Vertex_Comparator > (right)
    { }
  
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph< V, E, VW, float, Vertex_Comparator >* cloneGraph () const
    {
      return new MaximumFlowGraph< V, E, VW, Vertex_Comparator> (*this);
    }

    /**
     * Destroys the object.
     */
    virtual ~MaximumFlowGraph () { }
  
    // OPERATORS ---------------------------------------------------------------

    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    MaximumFlowGraph& operator= (const MaximumFlowGraph &right)
    {
      if (this != &right)
	{
	  OrientedGraph< V, E, VW, float, Vertex_Comparator >::operator= (right);
	}
      return *this;
    }
    
  public:
    
    // ACCESS ------------------------------------------------------------------
  
    // METHODS -----------------------------------------------------------------

  private:

    /**
     * Connects two vertices of the graph with an edge.  Private method to
     * ensure that the in-edge and weights are given.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, E &e) { return false; }

  public:
    
    /**
     * Connects two vertices of the graph with an edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the edge weight.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, E &e, float w)
    {
      return OrientedGraph< V, E, VW, float, Vertex_Comparator >::connect (h, t, e, w);
    }

  private:
    
    /**
     * Connects two vertices labels of the graph with an edge.  Private
     * method to ensure that the in-edge and its weight are given.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool internalConnect (label h, label t, E &e)
    {
      return false;
    }      
    
  public:
    
    /**
     * Pre Flow Push algorithm for solving the Maximum Flow problem.
     * Adapted by Sebastien to minimize each individual flow and avoid
     * "extreme" solutions.  In the context of H-bond patterns, this
     * favors bifurcated geometries, if possible, by separating the
     * flow on the two possible H-bonds of the bifurcation.
     * @param source the source of the graph.
     * @param sink the sink of the graph.
     */
    void preFlowPush (const V &source, const V &sink)
    {
      if (contains (source) && contains (sink))
	{
	  label sourceid;
	  label sinkid;
	  vector< int > labels;
	  vector< float > excess;
	  list< label > q;
	  int distance;
	  list< label > active;
	  list< label > neighborhood;
	  typename list< label >:: iterator it;

	  sourceid = getVertexLabel (source);
	  sinkid = getVertexLabel (sink);
      
	  // Compute the initial distance labels
	  labels.insert (labels.end (), size (), numeric_limits< int >::max ());
	  excess.insert (excess.end (), size (), 0);
	  
	  distance = 0;
	  q.push_back (sourceid);
	  labels[sourceid] = distance;

	  gOut (5) << "Labels " << labels << endl;
	  
	  while (! q.empty ())
	    {
	      list < label > tmp;

	      distance = labels[q.front ()] + 1;
	      neighborhood = internalOutNeighborhood (q.front ());
	      tmp = internalInNeighborhood (q.front ());
	      neighborhood.insert (neighborhood.end (), tmp.begin (), tmp.end ());
	      for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
		{
		  if (labels[*it] > distance)
		    {
		      labels[*it] = distance;
		      q.push_back (*it);
		    }
		}
	      q.pop_front ();
	    }

	  gOut (5) << "Labels " << labels << endl;

	  // Flood from the source
	  neighborhood = internalOutNeighborhood (sourceid);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      internalSetEdgeWeight (sourceid, *it, internalGetEdge (sourceid, *it).getValue ());
	      excess[*it] = internalGetEdgeWeight (sourceid, *it);
	      excess[sourceid] -= excess[*it];
	      active.push_back (*it);
	    }
	  
	  gOut (5) << "Active " << active << endl;
	  gOut (5) << "Excess " << excess << endl;
	  
	  while (! active.empty ())
	    {
	      pushRelabel (active, excess, labels, sourceid, sinkid);
	      if (0 == excess[active.front ()])
		{
		  active.pop_front ();
		}
	    }
	}
    }
    
  private:
    
    /**
     * Push-Relabel part of the Pre Flow Push algorithm.
     * @param active the active list of labels.
     * @param excess the excess collection for each labels.
     * @param labels the distance collection for each labels.
     * @param source the source vertex label.
     * @param sink the sink vertex label.
     */
    void pushRelabel (list< label > &active, vector< float > &excess, vector< int > &labels, label source, label sink)
    {
      label front;

      front = active.front ();
      gOut (5) << "Relabeling [" << front << "]" << endl;
      
      if (0 < excess[front])
	{
	  list< label > neighborhood;
	  typename list< label >::iterator it;
	  vector< float > cap;
	  float eq;

	  neighborhood = internalOutNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && internalGetEdgeWeight (front, *it) < internalGetEdge (front, *it).getValue ())
		{
		  cap.push_back (internalGetEdge (front, *it).getValue ()
				 - internalGetEdgeWeight (front, *it));
		}
	    }
	  eq = equilibrateFlow (cap, excess[front]);
	  
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && internalGetEdgeWeight (front, *it) < internalGetEdge (front, *it).getValue ())
		{
		  float push_delta;

		  push_delta = min (eq, internalGetEdge (front, *it).getValue () - internalGetEdgeWeight (front, *it));
		  
		  gOut (5) << "Pushing " << push_delta << " from " << front
			   << " to " << *it << endl;
		  
		  internalSetEdgeWeight (front, *it, internalGetEdgeWeight (front, *it) + push_delta);
		  excess[front] -= push_delta;
		  if (fabs (excess[front]) < 1e-5)
		    {
		      excess[front] = 0;
		    }
		  if (*it != source && *it != sink)
		    {
		      gOut (5) << "         AddingA " << *it << endl;
		      active.push_back (*it);
		    }
		  excess[*it] += push_delta;
		}
	    }
	}
      
      if (0 < excess[front])
	{
	  list< label > neighborhood;
	  typename list< label >::iterator it;
	  vector< float > cap;
	  float eq;

	  neighborhood = internalInNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && 0 < internalGetEdgeWeight (*it, front))
		{
		  cap.push_back (internalGetEdgeWeight (*it, front));
		}
	    }
	  eq = equilibrateFlow (cap, excess[front]);
	  
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && 0 < internalGetEdgeWeight (*it, front))
		{
		  float push_delta;

		  push_delta = min (eq, internalGetEdgeWeight (*it, front));
		  
		  gOut (5) << "Pushing back " << push_delta << " from " << front
			   << " to " << *it << endl;
		  
		  internalSetEdgeWeight (*it, front, internalGetEdgeWeight (*it, front) - push_delta);
		  excess[front] -= push_delta;
		  if (fabs (excess[front]) < 1e-5)
		    {
		      excess[front] = 0;
		    }
		  if (*it != source && *it != sink)
		    {
		      gOut (5) << "         AddingB " << *it << endl;
		      active.push_back (*it);
		    }
		  excess[*it] += push_delta;
		}
	    }
	}
      
      if (0 < excess[front])
	{
	  list< label > neighborhood;
	  typename list< label >::iterator it;
	  int max_dist;

	  gOut (5) << "Residual" << endl;
	  max_dist = -2 * size ();
	  neighborhood = internalOutNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (0 < internalGetEdge (front, *it).getValue () - internalGetEdgeWeight (front, *it)
		  && labels[*it] > max_dist)
		{
		  max_dist = labels[*it];
		  gOut (5) << "  max_dist forward residual = " 
			   << internalGetEdgeWeight (front, *it) - internalGetEdgeWeight (front, *it)
			   << endl;
		}
	    }

	  neighborhood = internalInNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (0 < internalGetEdgeWeight (*it, front)
		  && labels[*it] > max_dist)
		{
		  max_dist = labels[*it];
		  gOut (5) << "  max_dist back residual = " 
			   << internalGetEdgeWeight (*it, front) << endl;
		}
	    }

	  gOut (5) << "Relabel[" << front << "] from " 
		   << labels[front] << " to " << (max_dist - 1)
		   << " (excess = " << excess[front] << ")" << endl;
	  
	  labels[front] = max_dist - 1;
	}
    }
    
    /**
     * Reequilibrate flows in the graph.
     */
    float equilibrateFlow (vector< float > &capacities, float excess) 
    {
      unsigned int i;
      
      sort (capacities.begin (), capacities.end ());
      for (i = 0; i < capacities.size (); ++i)
	{
	  if (capacities[i] < (excess / (capacities.size () - i)))
	    {
	      excess -= capacities[i];
	    }
	  else
	    {
	      break;
	    }
	}
      if (i == capacities.size ())
	{
	  // The capacity of the donor/acceptor is not exceeded, so give
	  // everything
	  return 1;
	}
      return excess / (capacities.size () - i);
    }
    
    // I/O ---------------------------------------------------------------------
    
  public:
    
    virtual ostream& write (ostream& os) const
    {
      return os << "[MaximumFlowGraph]" << endl
		<< Graph< V, E, VW, float, Vertex_Comparator >::write (os);
    }
    
  };

}

#endif
