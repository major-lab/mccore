//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 10 19:09:13 2004
// $Revision: 1.18.4.1 $
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

#include <algorithm>
#include <functional>
#include <limits>
#include <list>
#include <set>
#include <utility>
#include <vector>

#include "Cycle.h"
#include "Graph.h"
#include "OrientedGraph.h"
#include "Path.h"
#include "Messagestream.h"



namespace mccore
{
  /**
   * Undirected graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: UndirectedGraph.h,v 1.18.4.1 2006-03-24 18:41:35 larosem Exp $
   */
  template< typename V,
	    typename E,
	    typename VW = float,
	    typename EW = float,
	    typename Vertex_Comparator = less< V > >	    
  class UndirectedGraph : public Graph< V, E, VW, EW, Vertex_Comparator>
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
    UndirectedGraph () : super () { }

    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    UndirectedGraph (const UndirectedGraph &right)
      : super (right) { }

    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual super* cloneGraph () const
    {
      return (super*) new UndirectedGraph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator> (*this);
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
	  super::operator= (right);
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
      return (this == &right || super::operator== (right));
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

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Builds the set of edges to delete according to the given vertex set.
     * @param labelset the set of labels to delete.
     * @param edgelabelset the set of edge labels that will have to be deleted.
     */
    virtual void edgestodelete (const std::set< label > &labelset, std::set< edge_label > &edgelabelset) const
    {
      typename std::set< label >::const_iterator lsit;

      edgelabelset.clear ();
      for (lsit = labelset.begin (); labelset.end () != lsit; ++lsit)
	{
	  typename EV2ELabel::const_iterator evit;

	  if (((typename EV2ELabel::const_iterator) this->ev2elabel.end ()) != (evit = this->ev2elabel.find (*lsit)))
	    {
	      const InnerMap &im = evit->second;
	      typename InnerMap::const_iterator imit;

	      for (imit = im.begin (); im.end () != imit; ++imit)
		{
		  edgelabelset.insert (imit->second);
		}
	    }
	}
    }

  public:
    
    /**
     * Connects two vertices labels of the graph with an edge.  Two
     * endvertices are added, pointing to the same edge.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded or false if the
     * labels were already connected.
     */
    virtual bool internalConnect (label h, label t, const edge &e)
    {
      if (this->size () > h
	  && this->size () > t
	  && this->edgeSize () == internalGetEdgeLabel (h, t))
	{
	  InnerMap im;
	  InnerMap iminv;
	  edge_label el;
	  std::pair< typename EV2ELabel::iterator, bool > inserted;

	  im[t] = el = this->edgeSize ();
	  iminv[h] = el;
	  this->edgeWeights.resize (this->edgeSize () + 1);
	  this->edges.push_back (e);
	  inserted = this->ev2elabel.insert (std::make_pair (h, im));
	  if (! inserted.second)
	    {
	      inserted.first->second[t] = el;
	    }
	  inserted = this->ev2elabel.insert (std::make_pair (t, iminv));
	  if (! inserted.second)
	    {
	      inserted.first->second[h] = el;
	    }
	  return true;
	}
      else
	{
	  return false;
	}
    }

    /**
     * Connects two vertices of the graph with an edge and weight.  Two
     * endvertices are added, pointing to the same edge.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded or false if the
     * labels were already connected.
     */
    virtual bool internalConnect (label h, label t, const edge &e, const edge_weight &w)
    {
      if (this->size () > h
	  && this->size () > t
	  && this->edgeSize () == internalGetEdgeLabel (h, t))
	{
	  InnerMap im;
	  InnerMap iminv;
	  edge_label el;
	  std::pair< typename EV2ELabel::iterator, bool > inserted;

	  im[t] = el = this->edgeSize ();
	  iminv[h] = el;
	  this->edges.push_back (e);
	  this->edgeWeights.push_back (w);
	  inserted = this->ev2elabel.insert (std::make_pair (h, im));
	  if (! inserted.second)
	    {
	      inserted.first->second[t] = el;
	    }
	  inserted = this->ev2elabel.insert (std::make_pair (t, iminv));
	  if (! inserted.second)
	    {
	      inserted.first->second[h] = el;
	    }
	  return true;
	}
      else
	{
	  return false;
	}
    }
    
//     /**
//      * Prim's algorithm for the minimum spanning tree.
//      * @param graph an undirected graph
//      * @param edge_nodes a vector of pairs of node ids.
//      * @return a vector of edges representing a spanning tree of the graph.
//      */
//     static void minimumSpanningTree (const UndirectedGraph< vertex, edge, vertex_weight, edge_weight, Vertex_Comparator > &graph, vector< pair< label, label > > &edge_nodes) 
//     {
//       vector< label > nearest (graph.size (), 0);
//       vector< float > mindist (graph.size (), numeric_limits< float >::max ());
//       unsigned int i;
//       unsigned int j;

//       if (! graph.empty ())
// 	{
// 	  // Initialize
// 	  for (i = 1; i < graph.size (); ++i)
// 	    {
// 	      if (graph.internalAreConnected (i, 0))
// 		{
// 		  mindist[i] = graph.internalGetEdgeWeight (i, 0);
// 		}
// 	    }
// 	  edge_nodes.clear ();
  
// 	  // Execute
// 	  for (i = 0; i < graph.size () - 1; ++i)
// 	    {
// 	      float min = numeric_limits< float >::max ();
// 	      label k = numeric_limits< unsigned int >::max ();
	  
// 	      for (j = 1; j < graph.size (); ++j)
// 		{
// 		  if (mindist[j] >= 0 && mindist[j] < min)
// 		    {
// 		      min = mindist[j];
// 		      k = j;
// 		    }
// 		}
	
// 	      // This is a test to see if we stay in the same connected
// 	      // component
// 	      if (k != numeric_limits< unsigned int >::max ())
// 		{
// 		  edge_nodes.push_back (make_pair (nearest[k], k));
// 		  mindist[k] = numeric_limits< unsigned int >::max ();
	    
// 		  for (j = 1; j < graph.size (); ++j)
// 		    {
// 		      float val = (graph.internalAreConnected (j, k)
// 				   ? graph.internalGetEdgeWeight (j, k)
// 				   : numeric_limits< float >::max ());
// 		    if (val < mindist[j])
// 		      {
// 			mindist[j] = val;
// 			nearest[j] = k;
// 		      }
// 		    }
// 		}
// 	    }
// 	}
//     }

//   public:
    
//     /**
//      * Dijkstra's algorithm for the shortest path in a directed graph.  The
//      * SPT is optimized for graphs with non-negative edge weights.  A path
//      * P(x,y) is pruned if there is a z in P(x,y) so that z < x.  The path's
//      * value is reset to the max value of the Path's value type.  The source
//      * (x) is at the beginning of the path.
//      * <pre>
//      * NODE v, w;
//      * SET V, S;             both V and S are SETS
//      * int Dist[MAX][MAX];   distance from node v to w
//      * int D[MAX];           current distance from the root
//      * int P[MAX];           backward path towards root
//      * 
//      * S = {ROOT}; 
//      * for (all other nodes w in V-S) {
//      *   if (areConnected (ROOT, w) and ROOT < w) {
//      *     D[w] = Dist[ROOT][w];
//      *     P[w] = ROOT;
//      * }
//      * while (S is not yet V) {
//      *   choose node w in V-S such that D[w] is minimum;
//      *   S = S union {w};
//      *   for (each node v in V-S)
//      *     if (D[v] > D[w] + Dist[w][v] and areConnected (w, v) and ROOT < v) {
//      *       D[v] = D[w] + Dist[w][v];
//      *       P[v] = w;
//      *     }
//      * }
//      * </pre>
//      * @param source the source node id of the paths.
//      * @param paths a collection of Path to fill with the SPT.
//      */
//     template< typename Value, typename Compare >
//     void sptDijkstraTiernan (label source, vector< Path< label, Value > > &paths)
//     {
//       const Value MAXVAL = numeric_limits< Value >::max ();
//       label w;
//       size_type graphsize;
//       vector< label > C;
//       Compare comparator;
      
//       graphsize = this->size ();
//       paths.clear ();
//       paths.resize (graphsize);
      
//       // Initialize ---
//       for  (w = 0; w < graphsize; ++w)
// 	{
// 	  Value value;
	  
// 	  paths[w].push_back (source);
// 	  if  (w == source)
// 	    {
// 	      value = MAXVAL;
// 	    }
// 	  else
// 	    {
// 	      if (internalAreConnected (source, w))
// 		{
// 		  value = internalGetEdgeWeight (source, w);
// 		  paths[w].push_back (w);
// 		}
// 	      else
// 		{
// 		  value = MAXVAL;
// 		}
// 	      C.push_back (w);
// 	    }
// 	  paths[w].setValue (value);
// 	}
      
//       while (! C.empty ())
// 	{
// 	  typename vector< label >::iterator min_iter;
// 	  typename vector< label >::iterator k;
// 	  Value min_value;
	  
// 	  min_iter = C.begin ();
// 	  min_value = paths[*min_iter].getValue ();
	  
// 	  for  (k = C.begin (); k != C.end (); ++k)
// 	    if  (paths[*k].getValue () < min_value)
// 	      {
// 		min_value = paths[*k].getValue ();
// 		min_iter = k;
// 	      }
// 	  w = *min_iter;
// 	  C.erase (min_iter);
	  
// 	  // Break if the elements remaining in C are not connected to the
// 	  // source.
// 	  if  (min_value == MAXVAL)
// 	    {
// 	      break;
// 	    }
	  
// 	  for (k = C.begin (); C.end () != k; ++k)
// 	    {
// 	      Value new_val;
// 	      label v;
	      
// 	      v = *k;
// 	      if (comparator (source, w)
// 		  && internalAreConnected (w, v)
// 		  && (paths[v].getValue () > (new_val = min_value + internalGetEdgeWeight (w, v))))
// 	        {
// 		  paths[v] = paths[w];
// 		  paths[v].push_back (v);
// 		  paths[v].setValue (new_val);
// 		}
// 	    }
// 	}
//     }
    
//     /**
//      * Dijkstra's algorithm for the shortest path in a directed graph.  The
//      * SPT is optimized for graphs with non-negative edge weights.  A path
//      * P(x,y) is pruned if there is a z in P(x,y) so that z < x.  The path's
//      * value is reset to the max value of the Path's value type.  The source
//      * (x) is at the beginning of the path.  The value of the edge weights is
//      * fixed and given by value.
//      * <pre>
//      * NODE v, w;
//      * SET V, S;             both V and S are SETS
//      * int Dist[MAX][MAX];   distance from node v to w
//      * int D[MAX];           current distance from the root
//      * int P[MAX];           backward path towards root
//      * 
//      * S = {ROOT}; 
//      * for (all other nodes w in V-S) {
//      *   if (areConnected (ROOT, w) and ROOT < w) {
//      *     D[w] = Dist[ROOT][w];
//      *     P[w] = ROOT;
//      * }
//      * while (S is not yet V) {
//      *   choose node w in V-S such that D[w] is minimum;
//      *   S = S union {w};
//      *   for (each node v in V-S)
//      *     if (D[v] > D[w] + Dist[w][v] and areConnected (w, v) and ROOT < v) {
//      *       D[v] = D[w] + Dist[w][v];
//      *       P[v] = w;
//      *     }
//      * }
//      * </pre>
//      * @param source the source node id of the paths.
//      * @param paths a collection of Path to fill with the SPT.
//      * @param val the fixed value of edge weights.
//      * @param comparator the node comparator.
//      */
//     template< typename FW, typename Compare >
//     void sptDijkstraTiernanWithFixedValues (label source, vector< Path< label, FW > > &paths, const FW &val) const
//     {
//       const FW MAXVAL = numeric_limits< FW >::max ();
//       label w;
//       size_type graphsize;
//       vector< label > C;
// // <<<<<<< UndirectedGraph.h
// //       Compare comparator;
// // =======
//       const unsigned int MAXUIVALUE = numeric_limits< unsigned int >::max ();
// // >>>>>>> 1.16
      
//       graphsize = this->size ();
//       paths.clear ();
//       paths.resize (graphsize);
      
//       // Initialize ---
//       for  (w = 0; w < graphsize; ++w)
// 	{
// 	  int value;
	  
// 	  paths[w].push_back (source);
// 	  if  (w == source)
// 	    {
// 	      value = MAXVAL;
// 	    }
// 	  else
// 	    {
// 	      if (internalAreConnected (source, w))
// 		{
// 		  value = val;
// 		  paths[w].push_back (w);
// 		}
// 	      else
// 		{
// 		  value = MAXVAL;
// 		}
// 	      C.push_back (w);
// 	    }
// 	  paths[w].setValue (value);
// 	}
      
//       while (! C.empty ())
// 	{
// 	  typename vector< label >::iterator min_iter;
// 	  typename vector< label >::iterator k;
// 	  FW min_value;
	  
// 	  min_iter = C.begin ();
// 	  min_value = paths[*min_iter].getValue ();
	  
// 	  for  (k = C.begin (); k != C.end (); ++k)
// 	    if  (paths[*k].getValue () < min_value)
// 	      {
// 		min_value = paths[*k].getValue ();
// 		min_iter = k;
// 	      }
// 	  w = *min_iter;
// 	  C.erase (min_iter);
	  
// 	  // Break if the elements remaining in C are not connected to the
// 	  // source.
// 	  if  (min_value == MAXVAL)
// 	    {
// 	      break;
// 	    }
	  
// 	  for (k = C.begin (); C.end () != k; ++k)
// 	    {
// 	      FW new_val;
// 	      label v;
	      
// 	      v = *k;
// 	      if (comparator (source, w)
// 		  && internalAreConnected (w, v)
// 		  && paths[v].getValue () > (new_val = min_value + val))
// 	        {
// 		  paths[v] = paths[w];
// 		  paths[v].push_back (v);
// 		  paths[v].setValue (new_val);
// 		}
// 	    }
// 	}
//     }
    
//     /**
//      * Uses the Gaussian Elimination algorithm to find non linearly
//      * dependant cycles from the set of enumerated cycles.
//      * @param graph an UndirectedAbstractGraph.
//      * @param bag a vector of cycles.
//      * @return a linearly independant vector of cycles.
//      */
//     vector< Path< label, unsigned int > > gaussianElimination (vector< Path< label, unsigned int > >& bag) const
//     {
//       typedef typename vector< Path< label, unsigned int > >::iterator vpiterator;
      
//       if (bag.empty ())
// 	{
// 	  return bag;
// 	}
      
//       vector< bool* > matrix;
//       vector< bool* >::iterator n;
//       label i;
//       label j;
//       vector< mccore::Path< label, unsigned int > > newbag;
//       vpiterator p, q;
//       edge_size_type eSize;
//       vector< vpiterator > marked;
//       bool *row;
      
//       eSize = this->edgeSize ();
//       row = new bool[eSize];    
//       for (p = bag.begin (); p != bag.end (); ++p)
// 	{
// 	  typename mccore::Path< label, unsigned int >::iterator r;
// 	  typename mccore::Path< label, unsigned int >::iterator s;
// 	  bool inserted;
	  
// 	  for (i = 0; i < eSize; ++i)
// 	    {
// 	      row[i] = false;
// 	    }
	  
// 	  // Let's see if *p is linearly independent to the content of newbag 
// 	  //       cout << "Treating " << *p << endl;
	  
// 	  s = p->begin ();
// 	  row[internalGetEdgeLabel (p->back (), *s)] = true;
// 	  for (r = s++; p->end () != s; ++r, ++s)
// 	    {
// 	      row[internalGetEdgeLabel (*r, *s)] = true;
// 	    }
	  
// 	  inserted = false;
// 	  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
// 	    {
// 	      j = 0;
// 	      while (j < eSize && row[j] == false && (*n)[j] == false)
// 		{
// 		  ++j;
// 		}
// 	      if (j == eSize)
// 		{
// 		  continue;
// 		}
	      
// 	      if (row[j] == true && (*n)[j] == false)
// 		{
// 		  gOut (4) << "Marking " << *p << endl;
// 		  marked.push_back (p);
// 		  inserted = true;
// 		  break;
// 		}
	      
// 	      if (row[j] == true && (*n)[j] == true)
// 		{
// 		  //Reduce the current
// 		  for (i = 0; i < eSize; ++i)
// 		    {
// 		      row[i] ^= (*n)[i];
// 		    }
// 		  continue;
// 		}
// 	    }
	  
// 	  if (! inserted)
// 	    {
// 	      for (j = 0; j < eSize; ++j)
// 		{
// 		  if (true == row[j])
// 		    {
// 		      gOut (4) << "Rejecting " << *p << endl;
// 		      break;
// 		    }
// 		}
// 	      if (j != eSize)
// 		{
// 		  gOut (4) << "Marking " << *p << endl;
// 		  marked.push_back (p);
// 		}
// 	    }
	  
// 	  // Let's see if we should try to insert the marked...
// 	  if (p + 1 == bag.end () || (p + 1)->size () > p->size ())
// 	    {
// 	      gOut (4) << endl << "Inserting marked cycles (" << marked.size ()
// 		       << ")" << endl << endl;
	      
// 	      for (i = 0; i < marked.size (); ++i)
// 		{
// 		  typename Path< label, unsigned int >::iterator r;
// 		  typename Path< label, unsigned int >::iterator s;
// 		  bool *row2;
// 		  unsigned int k;
		  
// 		  row2 = new bool[eSize];	  
// 		  for (k = 0; k < eSize; ++k)
// 		    {
// 		      row2[k] = false;
// 		    }		  
// 		  s = marked[i]->begin ();
// 		  row2[internalGetEdgeLabel (marked[i]->back (), *s)] = true;
// 		  for (r = s++; marked[i]->end () != s; ++r, ++s)
// 		    {
// // <<<<<<< UndirectedGraph.h
// // 		      row2[internalGetEdgeLabel (*r, *s)] = true;
// // =======
// 		      row2[internalGetEdge (*r, *s)] = true;
// // >>>>>>> 1.16
// 		    }		  
// 		  inserted = false;	
// 		  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
// 		    {
// 		      j = 0;    
// 		      while (j < eSize && row2[j] == false && (*n)[j] == false)
// 			{
// 			  ++j;
// 			}
// 		      if (j == eSize)
// 			{
// 			  continue;
// 			}
		      
// 		      if (row2[j] == true && (*n)[j] == false)
// 			{
// 			  gOut (4) << "Inserting " << *marked[i] << " " << *row2 << endl;
// 			  matrix.insert (n, row2);
// 			  newbag.insert (q, *marked[i]);
// 			  inserted = true;
// 			  break;
// 			}
		      
// 		      if (row2[j] == true && (*n)[j] == true)
// 			{
// 			  //Reduce the current
//   			  for (k = 0; k < eSize; ++k)
// 			    {
// 			      row2[k] ^= (*n)[k];
// 			    }
// 			  continue;
// 			}
// 		    }
		  
// 		  if (! inserted)
// 		    {
// 		      for (j = 0; j < eSize; ++j)
// 			{
// 			  if (row2[j] == true)
// 			    {
// 			      break;
// 			    }
// 			}
// 		      if (j != eSize)
// 			{
// 			  gOut (4) << "Accepting " << *marked[i] << endl;
// 			  matrix.push_back (row2);
// 			  newbag.push_back (*marked[i]);
// 			}
// 		      else
// 			{
// 			  gOut (4) << "Rejecting " << *marked[i] << endl;
// 			  delete[] row2;
// 			}
// 		    }
// 		}
// 	      marked.clear ();
// 	      gOut (4) << "done" << endl;
// 	    }
// 	}
      
//       for (n = matrix.begin (); n != matrix.end (); ++n)
// 	{
// 	  delete[] *n;
// 	}
//       delete[] row;
//       return newbag;
//     }

//     /**
//      * Horton's algorithm for the minimum cycle basis.  It returns a vector
//      * of Paths (cycles where the first and last vertices are connected) in
//      * the graph internal numerotation.
//      * @param cycles the minimum cycle basis collection to fill.
//      */
//     void internalMinimumCycleBasis (vector< Path< label, unsigned int > > &cycles) const
//     {
//       const unsigned int MAXUIVALUE = numeric_limits< unsigned int >::max ();
//       typename vector< Path< label, unsigned int > >::iterator p;
//       label i;
// // <<<<<<< UndirectedGraph.h

// //       cycles.clear ();
// //       for (i = 0; i < size (); ++i)
// // =======
//       const int MAXVALUE = numeric_limits< int >::max ();
      
//       for (i = 0; i < this->size (); ++i)
// // >>>>>>> 1.16
// 	{
// 	  vector< Path< label, unsigned int > > tmp;
// 	  typename EV2ELabel::const_iterator ecIt;

// // <<<<<<< UndirectedGraph.h
// // 	  sptDijkstraTiernanWithFixedValues< unsigned int, less< label > > (i, tmp, 1);
// // 	  for (ecIt = ev2elabel.begin (); ev2elabel.end () != ecIt; ++ecIt)
// // =======
// 	  sptDijkstraTiernan (i, tmp, less< label > ());
// 	  for (ecIt = this->ev2elabel.begin (); this->ev2elabel.end () != ecIt; ++ecIt)
// // >>>>>>> 1.16
// 	    {
// 	      label j;
// 	      label k;
	      
// 	      j = ecIt->first.getHeadLabel ();
// 	      k = ecIt->first.getTailLabel ();
// 	      if (j < k
// 		  && MAXUIVALUE != tmp[j].getValue ()
// 		  && MAXUIVALUE != tmp[k].getValue ()
// 		  && *++(tmp[j].begin ()) != *++(tmp[k].begin ()))
// 		{
// 		  Path< label, unsigned int > Pvx = tmp[j];
// 		  Path< label, unsigned int > Pvy = tmp[k];
// 		  Path< label, unsigned int > Pvxp = Pvx; 
// 		  Path< label, unsigned int > Pvyp = Pvy; 
// 		  Path< label, unsigned int > inter;
		  
// 		  std::sort (Pvxp.begin (), Pvxp.end ());
// 		  std::sort (Pvyp.begin (), Pvyp.end ());
// 		  set_intersection (Pvxp.begin (), Pvxp.end (),
// 				    Pvyp.begin (), Pvyp.end (),
// 				    inserter (inter, inter.begin ()));
		  
// 		  if (inter.size () == 1 && inter.front () == i)
// 		    {
// 		      Path< label, unsigned int > C = Pvx;
		      
// 		      C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
// 		      C.pop_back ();
// 		      C.setValue (Pvx.getValue () + Pvy.getValue () + internalGetEdgeWeight (ecIt->second));
// 		      cycles.push_back (C);
// 		    }
// 		}
// 	    }
// 	}
      
//       std::sort (cycles.begin (), cycles.end ());
//       gOut (3) << "Found " << cycles.size () << " potential cycles before elimination" << endl;
//       cycles = gaussianElimination (cycles);
//       std::sort (cycles.begin (), cycles.end ());
//       gOut (3) << "Found " << cycles.size () << " cycles." << endl;
//     }

//   private:
    
//     /**
//      * Adds a Path in the digraph Dr.
//      * @param p the Path to add.
//      * @param Dr the digraph.
//      */
//     void addPath (Path< label, edge_weight > &sp, OrientedGraph< label, bool, vertex_weight, edge_weight > &Dr) const
//     {
//       typename Path< label, edge_weight >::reverse_iterator fit;
//       typename Path< label, edge_weight >::reverse_iterator lit;
      
//       fit = sp.rbegin ();
//       Dr.insert (*fit);
//       for (lit = fit++; sp.rend () != fit; ++fit, ++lit)
// 	{
// 	  Dr.insert (*fit);
// 	  if (! Dr.areConnected (*lit, *fit))
// 	    {
// 	      Dr.connect (*lit, *fit, internalGetEdgeWeight (*lit, *fit));
// 	    }
// 	}
//     }

//     pair< bool, vector< vector< bool > >::iterator > gElimination (vector< bool > &candidate, vector< vector< bool > > &matrix) const
//     {
//       vector< vector< bool > >::iterator row;
//       vector< bool >::iterator cIt;

//       for (row = matrix.begin (); matrix.end () != row; ++row)
// 	{
// 	  vector< bool >::const_iterator mIt;

// 	  for (cIt = candidate.begin (), mIt = row->begin ();
// 	       candidate.end () != cIt && false == *cIt && false == *mIt;
// 	       ++cIt, ++mIt);
// 	  if (candidate.end () == cIt)
// 	    {
// 	      continue;
// 	    }
// 	  if (true == *cIt && false == *mIt)
// 	    {
// 	      return make_pair (false, row);
// 	    }
// 	  if (true == *cIt && true == *mIt)
// 	    {
// 	      // Reduce candidate
// 	      for (cIt = candidate.begin (), mIt = row->begin (); candidate.end () != cIt; ++cIt, ++mIt)
// 		{
// 		  *cIt = *cIt xor *mIt;
// 		}
// 	      continue;
// 	    }
// 	}
//       return make_pair (candidate.end () == std::find (candidate.begin (), candidate.end (), true), matrix.end ());
//     }

//   protected:
    
//     /**
//      */
//     vector< Cycle< label, unsigned int > > BElimination (vector< Cycle< label, unsigned int > >& bag) const
//     {
//       if (bag.empty ())
// 	return bag;
      
//       vector< vector< bool > > BLess;
//       vector< vector< bool > > B;
//       vector< Cycle< label, unsigned int > > newbag;
//       typename vector< Cycle< label, unsigned int > >::iterator p;
//       edge_size_type eSize;
//       label pathSize = 0;
//       vector< bool > candidate2;

//       eSize = this->edgeSize ();
      
//       for (p = bag.begin (); p != bag.end (); ++p)
// 	{
// 	  typename Cycle< label, unsigned int >::iterator r;
// 	  typename Cycle< label, unsigned int >::iterator s;
// 	  vector< bool > candidate (eSize, false);

// 	  if (p->size () != pathSize)
// 	    {
// 	      BLess = B;
// 	      pathSize = p->size ();
// 	    }
	  
// 	  s = p->begin ();
// 	  candidate[internalGetEdgeLabel (p->back (), *s)] = true;
// 	  for (r = s++; p->end () != s; ++r, ++s)
// 	    {
// 	      candidate[internalGetEdgeLabel (*r, *s)] = true;
// 	    }
// 	  candidate2 = candidate;

// 	  if (! gElimination (candidate, BLess).first)
// 	    {
// 	      pair< bool, vector< vector< bool > >::iterator > res = gElimination (candidate2, B);

// 	      newbag.push_back (*p);
// 	      if (! res.first)
// 		{
// 		  B.insert (res.second, candidate2);
// 		}
// 	    }
// 	}
//       return newbag;
//     }
    
//     /**
//      * Vismara's union of minimum cycle bases algorithm.  It returns a
//      * vector of Path (cycles where the first and last vertices are
//      * connected) in graph numerotation.  We should be able to cast the edge
//      * weights to unsigned int.
//      * @param CR the minimum cycle basis collection to fill.
//      */
//     void internalUnionMinimumCycleBases (vector< Path< label, unsigned int > > &CR) const
//     {
//       const unsigned int MAXUIVALUE = numeric_limits< unsigned int >::max ();
//       label r;
// // <<<<<<< UndirectedGraph.h
// //       vector< Cycle< label, unsigned int > > prototypes;
// //       typename vector< Cycle< label, unsigned int > >::iterator protIt;
// //       vector< OrientedGraph< label, bool, bool, unsigned int > > D (size ());
// // =======
//       vector< Path< label, unsigned int > > prototypes;
//       typename vector< Path< label, unsigned int > >::iterator protIt;
// //       vector< Path< label, unsigned int > > CR;
//       typename vector< Path< label, unsigned int > >::iterator it;
//       vector< OrientedGraph< label, bool, bool, unsigned int > > D (this->size ());
//       const int MAXVALUE = numeric_limits< int >::max ();
// // >>>>>>> 1.16

// // <<<<<<< UndirectedGraph.h
// //       CR.clear ();
// //       for (r = 0; size () > r; ++r)
// // =======
//       for (r = 0; this->size () > r; ++r)
// // >>>>>>> 1.16
// 	{
// 	  vector< Path< label, unsigned int > > spt;
// 	  label y;
// 	  OrientedGraph< label, bool, bool, unsigned int > &Dr = D[r];
	  
// // <<<<<<< UndirectedGraph.h
// // 	  sptDijkstraTiernanWithFixedValues< unsigned int, greater< unsigned int > > (r, spt, 1);
// // 	  for (y = 0; size () > y && y < r; ++y)
// // =======
// 	  sptDijkstraTiernan (r, spt, greater< unsigned int > ());
// 	  for (y = 0; this->size () > y && y < r; ++y)
// // >>>>>>> 1.16
// 	    {
// 	      Path< label, unsigned int > &py = spt[y];
// 	      vector< label > S;
// 	      list< label > neighbors;
// 	      typename list< label >::iterator z;
// 	      typename vector< label >::iterator p;
// 	      typename vector< label >::iterator q;
	      
// 	      neighbors = internalNeighborhood (y);
// 	      for (z = neighbors.begin (); neighbors.end () != z; ++z)
// 		{
// 		  if (*z < r)
// 		    {
// 		      Path< label, unsigned int > &pz = spt[*z];
		      
// 		      if (MAXUIVALUE != py.getValue ()
// 			  && MAXUIVALUE != pz.getValue ())
// 			{
// 			  if (pz.getValue () + 1 == py.getValue ())
// 			    {
// 			      Dr.addReversePath (py, 1);
// 			      Dr.addReversePath (pz, 1);
// 			      Dr.connect (y, *z, 1);
// 			      S.push_back (*z);
// 			    }
// 			  else if (pz.getValue () != py.getValue () + 1 && *z < y)
// 			    {
// 			      set< label > sy;
// 			      set< label > sz;
// 			      vector< label > inter;
			      
// 			      sy.insert (py.begin (), py.end ());
// 			      sz.insert (pz.begin (), pz.end ());
// 			      set_intersection (sy.begin (), sy.end (),
// 						sz.begin (), sz.end (),
// 						inserter (inter, inter.begin ()));
			      
// 			      if (1 == inter.size () && inter.front () == r)
// 				{
// 				  prototypes.push_back (py);
// 				  Cycle< label, unsigned int > &cycle = prototypes.back ();
				  
// 				  Dr.addReversePath (py, 1);
// 				  Dr.addReversePath (pz, 1);
// 				  cycle.setP (cycle.size () - 1);
// 				  cycle.setQ (cycle.size ());
// 				  cycle.insert (cycle.end (), pz.rbegin (), pz.rend () - 1);
// 				  cycle.setValue (cycle.getValue () + pz.getValue () + 1);
// 				  gOut (4) << cycle << " r = " << cycle.getR ()
// 					   << " p = " << cycle.getP ()
// 					   << " q = " << cycle.getQ () << endl;
// 				}
// 			    }
// 			}
// 		    }
// 		}
// 	      for (p = S.begin (); S.end () != p; ++p)
// 		for (q = S.begin (); S.end () != q; ++q)
// 		  {
// 		    if (p != q)
// 		      {
// 			Path< label, unsigned int > &pp = spt[*p];
// 			Path< label, unsigned int > &pq = spt[*q];
// 			set< label > sp;
// 			set< label > sq;
// 			vector< label > inter;

// 			sp.insert (pp.begin (), pp.end ());
// 			sq.insert (pq.begin (), pq.end ());
// 			set_intersection (sp.begin (), sp.end (),
// 					  sq.begin (), sq.end (),
// 					  inserter (inter, inter.begin ()));
			
// 			if (1 == inter.size () && inter.front () == r)
// 			  {
// 			    if (*p < *q)
// 			      {
// 				prototypes.push_back (pp);
// 				Cycle< label, unsigned int > &cycle = prototypes.back ();

// 				cycle.setP (cycle.size () - 1);
// 				cycle.setQ (cycle.size () + 1);
// 				cycle.push_back (y);
// 				cycle.insert (cycle.end (), pq.rbegin (), pq.rend () - 1);
// 				cycle.setValue (cycle.getValue () + pq.getValue () + 2);
// 				gOut (4) << cycle << " r = " << cycle.getR ()
// 					 << " p = " << cycle.getP ()
// 					 << " y = " << cycle.getY ()
// 					 << " q = " << cycle.getQ () << endl;
// 			      }
// 			  }
// 		      }
// 		  }
// 	    }
// 	}
//       std::sort (prototypes.begin (), prototypes.end ());
//       gOut (3) << "Found " << prototypes.size ()
// 	       << " potential prototypes before elimination" << endl;
//       gOut (4) << prototypes << endl;
//       prototypes = BElimination (prototypes);
//       gOut (3) << "Found " << prototypes.size () << " prototypes" << endl;
//       gOut (4) << prototypes << endl;
      
//       // Enumeration of CR.
//       for (protIt = prototypes.begin (); prototypes.end () != protIt; ++protIt)
// 	{
// 	  Cycle< label, unsigned int > &prototype = *protIt;
// 	  label p;
// 	  label q;
// 	  vector< Path< label, unsigned int > > pPaths;
// 	  vector< Path< label, unsigned int > > qPaths;
// 	  typename vector< Path< label, unsigned int > >::iterator pPathIterator;
// 	  typename vector< Path< label, unsigned int > >::iterator qPathIterator;

// 	  r = prototype.getR ();
// 	  p = prototype.getP ();
// 	  q = prototype.getQ ();
// 	  pPaths = D[r].breadthFirstPaths (p);
// 	  qPaths = D[r].breadthFirstPaths (q);
	  
// 	  for (pPathIterator = pPaths.begin (); pPaths.end () != pPathIterator; ++pPathIterator)
// 	    {
// 	      for (qPathIterator = qPaths.begin (); qPaths.end () != qPathIterator; ++qPathIterator)
// 		{
// 		  CR.push_back (*pPathIterator);
// 		  Path< label, unsigned int > &cycle = CR.back ();
		
// 		  if (0 == prototype.size () % 2)
// 		    {
// 		      unsigned int y;

// 		      y = prototype.getY ();
// 		      cycle.push_back (y);
// 		      cycle.setValue (cycle.getValue () + 1 + 1);
// 		    }
// 		  else
// 		    {
// 		      cycle.setValue (cycle.getValue () + 1);
// 		    }
// 		  cycle.insert (cycle.end (), qPathIterator->rbegin (), qPathIterator->rend () - 1);
// 		  cycle.setValue (cycle.getValue () + qPathIterator->getValue ());
// 		}
// 	    }
// 	}
//       gOut (3) << "Found " << CR.size () << " cycles" << endl;
//     }
    
//     /**
//      * Prim's algorithm for the minimum spanning tree.
//      * @return a vector of edges representing a spanning tree of the graph.
//      */
//     vector< pair< vertex, vertex > > minimumSpanningTree () const
//     {
//       vector< pair< label, label > > aedges;
//       typename vector< pair< label, label > >::iterator i;
//       vector< pair< vertex, vertex > > realedges;

//       UndirectedGraph::minimumSpanningTree (*this, aedges);
//       for (i = aedges.begin (); aedges.end () != i; ++i)
// 	{
// 	  realedges.push_back (make_pair (this->vertices[i->first], this->vertices[i->second]));
// 	}
//       return realedges;
//     }
    
    // I/O  -----------------------------------------------------------------

  public:
    
    /**
     * Writes the object to a stream.
     * @param os the stream.
     * @return the stream.
     */
    virtual std::ostream& write (std::ostream& os) const
    {
      os << "[UndirectedGraph]" << std::endl;
      return super::write (os);
    }
    
  };

}

#endif
