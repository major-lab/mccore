//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 10 19:09:13 2004
// $Revision: 1.12.2.3 $
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
   * @version $Id: UndirectedGraph.h,v 1.12.2.3 2004-12-13 07:13:35 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class UndirectedGraph : public Graph< V, E, VW, EW, Vertex_Comparator>
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    UndirectedGraph () : Graph () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    UndirectedGraph (const UndirectedGraph &right) : Graph (right) { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph* clone () const
    {
      return new UndirectedGraph< V, VW, E, EW, Vertex_Comparator> (*this);
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
	  Graph::operator= (right);
	}
      return *this;
    }	  

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Inserts a vertex in the graph.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (V &v)
    {
      V2VLabel::iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  vertices.push_back (v);
	  v2vlabel.insert (make_pair (&vertices.back (), vertices.size () - 1));
	  vertexWeights.resize (vertexWeights.size () + 1);
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
    virtual bool insert (V &v, VW &w)
    {
      V2VLabel::iterator it;

      if (v2vlabel.end () == (it = v2vlabel.find (&v)))
	{
	  vertices.push_back (v);
	  vertexWeights.push_back (w);
	  v2vlabel.insert (make_pair (&vertices.back (), vertices.size () - 1));
	  return true;
	}
      return false;
    }

  private:

    /**
     * Erase a vertex label from the graph.  If an edge is connected to this
     * vertex label it is also removed.  No check is made on label validity.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element.
     */
    Graph::iterator internalEraseNoCheck (Graph::label l)
    {
      list< Graph::label > neighbors = internalGetNeighbors (l);

      if (! neighbors.empty ())
	{
	  list< Graph::label > lit;
	  vector< V >::iterator vit;
	  EV2ELabel::iterator evit;
	  EV2ELabel newEV2;

	  for (lit = neighbors.begin (), neighbors.end () != lit; ++lit)
	    {
	      internalDisconnectNoCheck (l, *lit);
	    }
	  vertices.erase (vertices.begin () + l);
	  vertexWeights.erase (vertexWeights.begin () + l);
	  v2vlabel.clear ();
	  for (vit = vertices.begin (); vertices.end () != vit; ++vit)
	    {
	      v2vlabel.insert (make_pair (&*vit, vit - vertices.begin ()));
	    }
	  for (evit = ev2elabel.begin (); ev2elabel.end () != evit; ++evit)
	    {
	      Graph::label h;
	      Graph::label t;
	      
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
	  return true;
	}
      return false;
    }

  public:
    
    /**
     * Erase a vertex from the graph.  If an edge is connected to this
     * vertex it is also removed.
     * @param v the vertex to remove.
     * @return an iterator over the next vertex element.
     */
    virtual Graph::iterator erase (const V &v)
    {
      V2VLabel::iterator it;
      
      return (v2vlabel.end () != (it = v2vlabel.find (&v))
	      ? internalEraseNoCheck (it->second)
	      : false);
    }

    /**
     * Erase a vertex label from the graph.  If an edge is connected to this
     * vertex label it is also removed.
     * @param l the vertex label to remove.
     * @return an iterator over the next vertex element.
     */
    virtual Graph::iterator internalErase (Graph::label l)
    {
      return (vertices.size () > l
	      ? internalEraseNoCheck (l)
	      : false);
    }
    
  private:
    
    /**
     * Connects two vertices labels of the graph with an edge.  Two
     * endvertices are added, pointing to the same edge.  No check are
     * made on vertex labels validity.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    bool internalConnectNoCheck (Graph::label h, Graph::label t, E &e)
    {
      EndVertices ev (h, t);
      EV2ELabel::const_iterator evit;
      
      if (ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  EndVertices ev2 (t, h);
	  
	  ev2elabel.insert (make_pair (ev, edges.size ()));
	  ev2elabel.insert (make_pair (ev2, edges.size ()));
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
    bool internalConnectNoCheck (Graph::label h, Graph::label t, E &e, EW &w)
    {
      EndVertices ev (h, t);
      EV2ELabel::const_iterator evit;
      
      if (ev2elabel.end () == (evit = ev2elabel.find (ev)))
	{
	  EndVertices ev2 (t, h);
	  
	  ev2elabel.insert (make_pair (ev, edges.size ()));
	  ev2elabel.insert (make_pair (ev2, edges.size ()));
	  edges.push_back (e);
	  edgeWeights.push_back (w);
	  return true;
	}
      return false;
    }
    
  public:
    
    /**
     * Connects two vertices of the graph with an edge.  Two endvertices are
     * added, pointing to the same edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &h, const V &t, E &e)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;

      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? internalConnectNoCheck (ith->second, itt->second, e)
	      : false);
    }
    
    /**
     * Connects two vertices of the graph with an edge and weight.  Two
     * endvertices are added, pointing to the same edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool connect (const V &o, const V &p, E &e, W &w)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;

      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? internalConnectNoCheck (ith->second, itt->second, e, w)
	      : false);
    }

    /**
     * Connects two vertices labels of the graph with an edge.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool internalConnect (Graph::label h, Graph::label t, E &e)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? internalConnectNoCheck (h, t, e)
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
    virtual bool internalConnect (Graph::label h, Graph::label t, E &e, W &w)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? internalConnectNoCheck (h, t, e, w)
	      : false);
    }

  private:
    
    /**
     * Disconnects two endvertices labels of the graph.  No check are
     * made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    bool internalDisconnectNoCheck (Graph::label h, Graph::label t)
    {
      EndVertices ev (h, t);
      EV2ELabel::iterator evit;
      
      if (ev2elabel.end () != (evit = ev2elabel.find (ev)))
	{
	  EndVertices ev2 (t, h);
	  Graph::label l;
	  
	  l = evit->second;
	  edges.erase (edges.begin () + l);
	  edgeWeights.erase (edgeWeights.begin () + l);
	  ev2elabel.erase (evit);
	  ev2elabel.erase (ev2elabel.find (ev2));
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
     * Disconnects the edge between two endvertices.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool disconnect (const V &h, const V &t)
    {
      V2VLabel::const_iterator ith;
      V2VLabel::const_iterator itt;

      return (v2vlabel.end () != (ith = v2vlabel.find (&h))
	      && v2vlabel.end () != (itt = v2vlabel.find (&t))
	      ? internalDisconnectNoCheck (h, t)
	      : false);
    }

    /**
     * Disconnects two endvertices labels of the graph.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool internalDisconnect (Graph::label h, Graph::label t)
    {
      return (vertices.size () > h && vertices.size () > t
	      ? internalDisconnectNoCheck (h, t)
	      : false);
    }
    
    // I/O  -----------------------------------------------------------------

  };

}

#endif
