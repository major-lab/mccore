//                              -*- Mode: C++ -*- 
// OrientedGraph.h
// Copyright © 2001-06 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// $Revision: 1.7.2.1 $
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
#include <set>
#include <utility>
#include <vector>

#include "Graph.h"
// #include "Path.h"



namespace mccore
{
  /**
   * Directed graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: OrientedGraph.h,v 1.7.2.1 2006-03-23 01:35:54 larosem Exp $
   */
  template< typename V,
	    typename E,
	    typename VW = float,
	    typename EW = float,
	    typename Vertex_Comparator = std::less< V > >	    
  class OrientedGraph : public Graph< V, E, VW, EW, Vertex_Comparator >
  {
    
  public:

    typedef V vertex;
    typedef E edge;
    typedef VW vertex_weight;
    typedef EW edge_weight;

  protected:

    typedef Graph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator > super;
    
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

  protected:
    
    typedef typename super::V2VLabel V2VLabel;
    typedef typename super::InnerMap InnerMap;
    typedef typename super::EV2ELabel EV2ELabel;

  public:
    
    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    OrientedGraph () : super () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    OrientedGraph (const OrientedGraph &right)
      : super (right) { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual super* cloneGraph () const
    {
      return (super*) new OrientedGraph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator> (*this);
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
	  super::operator= (right);
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
      return (this == &right || super::operator== (right));
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
    virtual std::list< vertex > inNeighborhood (const vertex &v)
    {
      std::list< vertex > res;
      label t;

      if (this->size () != (t = getVertexLabel (v)))
	{
	  typename EV2ELabel::const_iterator cit;

	  for (cit = this->ev2elabel.begin (); ((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != cit; ++cit)
	    {
	      const InnerMap &im = cit->second;

	      if (im.end () != im.find (t))
		{
		  res.push_back (*internalFind (cit->first));
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
    virtual std::list< vertex > outNeighborhood (const vertex &v)
    {
      std::list< vertex > res;
      label h;

      if (this->size () != (h = getVertexLabel (v)))
	{
	  typename EV2ELabel::const_iterator cit;

	  if (((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != (cit = this->ev2elabel.find (h)))
	    {
	      const InnerMap &im = cit->second;
	      typename InnerMap::const_iterator imit;
	      
	      for (imit = im.begin (); im.end () != imit; ++imit)
		{
		  res.push_back (*internalFind (imit->first));
		}
	    }
	}
      return res;
    }	  

    /**
     * Returns a label list of the in-neighbors of the given vertex label.
     * An empty list is returned if the label has no in-neighbor or if it is
     * not contained in the graph.
     * @param t the vertex label.
     * @return the list of in-neighbors.
     */
    virtual std::list< label > internalInNeighborhood (label t) const 
    {
      std::list< label > res;

      if (this->size () > t)
	{
	  typename EV2ELabel::const_iterator cit;

	  for (cit = this->ev2elabel.begin (); ((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != cit; ++cit)
	    {
	      const InnerMap &im = cit->second;
	      typename InnerMap::const_iterator imit;

	      if (im.end () != (imit = im.find (t)))
		{
		  res.push_back (cit->first);
		}
	    }
	}
      return res;
    }
    
    /**
     * Returns a label list of the neighbors of the given vertex label.  An
     * empty list is returned if the label has no neighbor or if it is not
     * contained in the graph.
     * @param h the vertex label.
     * @return the list of out-neighbors.
     */
    virtual std::list< label > internalOutNeighborhood (label h) const
    {
      std::list< label > res;
      typename EV2ELabel::const_iterator cit;

      if (((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != (cit = this->ev2elabel.find (h)))
	{
	  const InnerMap &im = cit->second;
	  typename InnerMap::const_iterator imit;

	  for (imit = im.begin (); im.end () != imit; ++imit)
	    {
	      res.push_back (imit->first);
	    }
	}
      return res;
    }	  

    /**
     * Returns the in and out neighbors of the given vertex. An empty list
     * is returned if the vertex has no neighbors or if the graph does not
     * contain the vertex. Vertices order is unsorted and may change on
     * graph modification.
     * @param v a vertex in the graph.
     * @return the list of neighbors.
     */
    virtual std::list< vertex > neighborhood (const vertex &v)
    {
      std::list< vertex > res;
      label l;

      if (this->size () > (l = getVertexLabel (v)))
	{
	  std::set< label > labelset;
	  typename std::set< label >::const_iterator labelsetit;
	  typename EV2ELabel::const_iterator evit;

	  for (evit = this->ev2elabel.begin (); ((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != evit; ++evit)
	    {
	      const InnerMap &im = evit->second;
	      label head;

	      if ((head = evit->first) == l)
		{
		  typename InnerMap::const_iterator imit;

		  for (imit = im.begin (); im.end () != imit; ++imit)
		    {
		      labelset.insert (imit->first);
		    }
		}
	      else if (im.end () != im.find (l))
		{
		  labelset.insert (head);
		}
	    }
	  for (labelsetit = labelset.begin (); labelset.end () != labelsetit; ++labelsetit)
	    {
	      res.push_back (*internalFind (*labelsetit));
	    }
	}
      return res;		
    }
    
    /**
     * Returns the in and out neighbor labels of the given vertex. An empty list
     * is returned if the vertex has no neighbors or if the graph does not
     * contain the vertex. Labels order is unsorted and may change on graph
     * modification.
     * @param l the vertex label.
     * @return the list of neighbors.
     */
    virtual std::list< label > internalNeighborhood (label l) const
    {
      std::list< label > res;

      if (this->size () > l)
	{
	  std::set< label > labelset;
	  typename EV2ELabel::const_iterator evit;

	  for (evit = this->ev2elabel.begin (); ((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != evit; ++evit)
	    {
	      const InnerMap &im = evit->second;
	      label head;
	      
	      if ((head = evit->first) == l)
		{
		  typename InnerMap::const_iterator imit;

		  for (imit = im.begin (); im.end () != imit; ++imit)
		    {
		      labelset.insert (imit->first);
		    }
		}
	      else if (im.end () != im.find (l))
		{
		  labelset.insert (head);
		}
	    }
	  res.insert (res.end (), labelset.begin (), labelset.end ());
	}
      return res;
    }
    
    // METHODS --------------------------------------------------------------

//     /**
//      * Finds the all the paths from the label q to the root.  Must be a non
//      * cyclic graph.  edge weights must implement operator+.
//      * @param Dr the oriented graph (with no cycles).
//      * @param q the starting label.
//      * @return a collection of Paths from q to the root in Dr.
//      */
//     vector< Path< vertex, edge_weight > > breadthFirstPaths (label q) const
//     {
//       vector< Path< vertex, edge_weight> > result;
//       std::list< Path< label, edge_weight > > lst (1, Path< label, edge_weight > ());
//       Path< label, edge_weight > &tmp = lst.front ();
      
//       tmp.push_back (q);
//       tmp.setValue (0);
//       while (! lst.empty ())
// 	{
// 	  Path< label, unsigned int > &front = lst.front ();
// 	  label endNode;
// 	  std::list< label > neighbors;
// 	  typename std::list< label >::iterator neighborsIt;

// 	  endNode = front.back ();
// 	  neighbors = internalOutNeighborhood (endNode);
// 	  neighborsIt = neighbors.begin ();
// 	  if (neighbors.end () == neighborsIt)
// 	    {
// 	      typename Path< label, edge_weight >::reverse_iterator rIt;

// 	      result.push_back (Path< vertex, edge_weight > ());
// 	      Path< vertex, edge_weight > &tmp = result.back ();
	      
// 	      for (rIt = front.rbegin (); front.rend () != rIt; ++rIt)
// 		{
// 		  tmp.push_back (internalGetVertex (*rIt));
// 		}
// 	      tmp.setValue (front.getValue ());
// 	    }
// 	  else
// 	    {
// 	      for (; neighbors.end () != neighborsIt; ++neighborsIt)
// 		{
// 		  lst.push_back (front);
// 		  Path< label, edge_weight > &tmp = lst.back ();

// 		  tmp.push_back (*neighborsIt);
// 		  tmp.setValue (tmp.getValue () + internalGetEdgeWeight (endNode, *neighborsIt));
// 		}
// 	    }
// 	  lst.pop_front ();
// 	}
//       return result;
//     }

    /**
     * Adds the reverse path p to this OrientedGraph.  Edges weights are
     * constant with value val.
     * @param p the Path to add.
     * @param val the edge value.
     */
//     void addReversePath (Path< vertex, edge_weight > &p, const edge_weight &val)
//     {
//       typename Path< vertex, edge_weight >::reverse_iterator fit;
//       typename Path< vertex, edge_weight >::reverse_iterator lit;
      
//       fit = p.rbegin ();
//       if (! contains (*fit))
// 	{
// 	  insert (*fit);
// 	}
//       for (lit = fit++; p.rend () != fit; ++fit, ++lit)
// 	{
// 	  if (! contains (*fit))
// 	    {
// 	      insert (*fit);
// 	    }
// 	  if (! areConnected (*lit, *fit))
// 	    {
// 	      connect (*lit, *fit, val);
// 	    }
// 	}
//     }
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual std::ostream& write (std::ostream& os) const
    {
      os << "[OrientedGraph]" << std::endl;
      return super::write (os);
    }
    
  };

}

#endif
