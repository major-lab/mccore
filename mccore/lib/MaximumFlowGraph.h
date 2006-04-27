//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.12.4.2 $
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

#include "OrientedGraph.h"
#include "stlio.h"
#include "Messagestream.h"

using namespace std;



namespace mccore
{
  /**
   * Maximum flow is an oriented graph.  The edges must implements the
   * method:
   * <pre>
   *      float getValue ()
   * </pre>
   * for flow calculation.
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: MaximumFlowGraph.h,v 1.12.4.2 2006-04-27 15:49:37 larosem Exp $
   */
  template< typename V,
	    typename E,
	    typename VW = float,
	    typename Vertex_Comparator = less< V > >	    
  class MaximumFlowGraph : public OrientedGraph< V, E, VW, float, Vertex_Comparator >
  {

  public:

    typedef V vertex;
    typedef E edge;
    typedef VW vertex_weight;
    typedef float edge_weight;

  protected:

    typedef OrientedGraph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator > super;
    
  public:
    
    typedef typename super::iterator iterator;
    typedef typename super::const_iterator const_iterator;
    typedef typename super::size_type size_type;
    typedef typename super::label label;
    typedef typename super::vweight_iterator vweight_iterator;
    typedef typename super::vweight_const_iterator vweight_const_iterator;
    typedef typename super::vweight_size_type vweight_size_type;
    typedef typename super::vweight_label vweight_label;
    typedef typename super::edge_iterator edge_iterator;
    typedef typename super::edge_const_iterator edge_const_iterator;
    typedef typename super::edge_size_type edge_size_type;
    typedef typename super::edge_label edge_label;
    typedef typename super::eweight_iterator eweight_iterator;
    typedef typename super::eweight_const_iterator eweight_const_iterator;
    typedef typename super::eweight_size_type eweight_size_type;
    typedef typename super::eweight_label eweight_label;

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    MaximumFlowGraph () : super () { }
    
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    MaximumFlowGraph (const MaximumFlowGraph &right)
      : super (right) { }
  
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator >* cloneGraph () const
    {
      return new MaximumFlowGraph< vertex, edge, vertex_weight, Vertex_Comparator> (*this);
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
	  super::operator= (right);
	}
      return *this;
    }
    
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
    virtual bool connect (const vertex &h, const vertex &t, const edge &e) { return false; }

  public:
    
    /**
     * Connects two vertices of the graph with an edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the edge weight.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const vertex &h, const vertex &t, const edge &e, const edge_weight w)
    {
      return super::connect (h, t, e, w);
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
    virtual bool internalConnect (label h, label t, const edge &e)
    {
      return false;
    }      
    
  public:
    
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
      return super::internalConnect (h, t, e, w);
    }

    /**
     * Pre Flow Push algorithm for solving the Maximum Flow problem.
     * Adapted by Sebastien to minimize each individual flow and avoid
     * "extreme" solutions.  In the context of H-bond patterns, this
     * favors bifurcated geometries, if possible, by separating the
     * flow on the two possible H-bonds of the bifurcation.
     * @param source the source of the graph.
     * @param sink the sink of the graph.
     */
    void preFlowPush (const vertex &source, const vertex &sink)
    {
      if (contains (source) && contains (sink))
	{
	  label sourceid;
	  label sinkid;
	  std::vector< int > labels;
	  std::vector< float > excess;
	  std::list< label > q;
	  int distance;
	  std::list< label > active;
	  std::list< label > neighborhood;
	  typename std::list< label >::iterator it;

	  sourceid = getVertexLabel (source);
	  sinkid = getVertexLabel (sink);
      
	  // Compute the initial distance labels
	  labels.insert (labels.end (), this->size (), std::numeric_limits< int >::max ());
	  excess.insert (excess.end (), this->size (), 0);
	  
	  distance = 0;
	  q.push_back (sourceid);
	  labels[sourceid] = distance;

	  gOut (5) << "Labels " << labels << endl;
	  
	  while (! q.empty ())
	    {
	      std::list < label > tmp;

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
	      excess[*it] = *internalFindWeight (sourceid, *it) = internalFind (sourceid, *it)->getValue ();
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
    void pushRelabel (std::list< label > &active, std::vector< float > &excess, std::vector< int > &labels, label source, label sink)
    {
      label front;

      front = active.front ();
      gOut (5) << "Relabeling [" << front << "]" << endl;
      
      if (0 < excess[front])
	{
	  std::list< label > neighborhood;
	  typename std::list< label >::iterator it;
	  std::vector< float > cap;
	  float eq;

	  neighborhood = internalOutNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && *internalFindWeight (front, *it) < internalFind (front, *it)->getValue ())
		{
		  cap.push_back (internalFind (front, *it)->getValue ()
				 - *internalFindWeight (front, *it));
		}
	    }
	  eq = equilibrateFlow (cap, excess[front]);
	  
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && *internalFindWeight (front, *it) < internalFind (front, *it)->getValue ())
		{
		  float push_delta;

		  push_delta = min (eq, internalFind (front, *it)->getValue () - *internalFindWeight (front, *it));
		  
		  gOut (5) << "Pushing " << push_delta << " from " << front
			   << " to " << *it << endl;

		  *internalFindWeight (front, *it) += push_delta;
		  excess[front] -= push_delta;
		  if (std::fabs (excess[front]) < 1e-5)
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
	  std::list< label > neighborhood;
	  typename std::list< label >::iterator it;
	  std::vector< float > cap;
	  float eq;

	  neighborhood = internalInNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && 0 < *internalFindWeight (*it, front))
		{
		  cap.push_back (*internalFindWeight (*it, front));
		}
	    }
	  eq = equilibrateFlow (cap, excess[front]);
	  
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (labels[*it] > labels[front]
		  && 0 < *internalFindWeight (*it, front))
		{
		  float push_delta;

		  push_delta = min (eq, *internalFindWeight (*it, front));
		  
		  gOut (5) << "Pushing back " << push_delta << " from " << front
			   << " to " << *it << endl;
		  
		  *internalFindWeight (*it, front) -= push_delta;
		  excess[front] -= push_delta;
		  if (std::fabs (excess[front]) < 1e-5)
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
	  std::list< label > neighborhood;
	  typename std::list< label >::iterator it;
	  int max_dist;

	  gOut (5) << "Residual" << endl;
	  max_dist = -2 * this->size ();
	  neighborhood = internalOutNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (0 < internalFind (front, *it)->getValue () - *internalFindWeight (front, *it)
		  && labels[*it] > max_dist)
		{
		  max_dist = labels[*it];
		  gOut (5) << "  max_dist forward residual = " 
			   << internalFind (front, *it)->getValue () - *internalFindWeight (front, *it)
			   << endl;
		}
	    }

	  neighborhood = internalInNeighborhood (front);
	  for (it = neighborhood.begin (); neighborhood.end () != it; ++it)
	    {
	      if (0 < *internalFindWeight (*it, front)
		  && labels[*it] > max_dist)
		{
		  max_dist = labels[*it];
		  gOut (5) << "  max_dist back residual = " 
			   << *internalFindWeight (*it, front) << endl;
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
    float equilibrateFlow (std::vector< float > &capacities, float excess) 
    {
      unsigned int i;
      
      std::sort (capacities.begin (), capacities.end ());
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
      os << "[MaximumFlowGraph]" << endl;
      Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator >::write (os);
      return os;
    }
    
  };

}



namespace std
{

  /**
   * Writes the maximum flow graph into the output stream.  It calls the
   * graph virtual method write.
   * @param os the output stream.
   * @param obj the graph.
   * @return the output stream.
   */
  template < typename V, typename E, typename VW, typename VC >
  ostream& operator<< (ostream &os, const mccore::MaximumFlowGraph< V, E, VW, VC > &obj)
  {
    return obj.write (os);
  }
  
}

#endif
