//                              -*- Mode: C++ -*- 
// GraphAlgo.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 16:47:26 2003
// $Revision: 1.6 $
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


#ifndef _mccore_GraphAlgo_h_
#define _mccore_GraphAlgo_h_

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "UndirectedGraph.h"
#include "Messagestream.h"
#include "Path.h"
#include "stlio.h"

using namespace std;



namespace mccore
{
    
  /**
   * Algorithms on graphs.  
   * 
   * They use the Fast Interface defined in the Graph objects.
   * Consequently, they are to be called with node ids instead of
   * actual nodes.
   *
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: GraphAlgo.h,v 1.6 2005-01-03 22:54:17 larosem Exp $
   */
  class GraphAlgo 
  {
   
  public:

    template< class node_type, class value_type >
    class Path : public mccore::Path< node_type, value_type >
    {
      /**
       * The index of p in Path.
       */
      unsigned int p;
      
      /**
       * The index of q in Path.
       */
      unsigned int q;

    public:
      
      // LIFECYCLE ------------------------------------------------------------
      
      /**
       * Initializes the object.
       */
      Path () : mccore::Path< node_type, value_type > () { }
      
      /**
       * Initializes the object with the other's content.
       * @param other the object to copy.
       */
      Path (const Path &other)
	: mccore::Path< node_type, value_type > (other),
	  p (other.p),
	  q (other.q)
      { }
      
      /**
       * Destroys the object.
       */
      virtual ~Path () { }

      // OPERATORS ------------------------------------------------------------
      
      /**
       * Assigns the object with the other's content.
       * @param other the object to copy.
       * @return itself.
       */
      Path& operator= (const Path &other)
      {
	if  (this != &other)
	  {
	    mccore::Path< node_type, value_type>::operator= (other);
	    p = other.p;
	    q = other.q;
	  }
	return *this;
      }

      // ACCESS ---------------------------------------------------------------

      /**
       * Gets the value of r in the path.
       * @return the value of r.
       */
      const node_type& getR () const { return front (); }
      
      /**
       * Gets the value of p in the path.
       * @return the value at the p index.
       */
      const node_type& getP () const { return (*this)[p]; }
      
      /**
       * Gets the r to p Path.
       * @return the r to p Path.
       */
      Path< node_type, typename Path::value_type > getRP () const
      {
	return Path< node_type, value_type > (begin (), begin () + p);
      }
      
      /**
       * Sets the p index.
       * @param p the p index.
       */
      void setP (unsigned int p) { this->p = p; }
      
      /**
       * Gets y value.
       * @param path the Path.
       */
      const node_type& getY () const { return operator[] (p + 1); }
      
      /**
       * Gets the r to q Path.
       * @return the r to q Path.
       */
      Path< node_type, typename Path::value_type> getRQ () const
      {
	return Path< node_type, value_type > (rbegin (), rbegin () + q);
      }
      
      /**
       * Gets the value of q in the path.
       * @return the value at the q index.
       */
      const node_type& getQ () const { return (*this)[q]; }
      
      /**
       * Sets the q index.
       * @param q the q index.
       */
      void setQ (unsigned int q) { this->q = q; }
      
    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------

      virtual ostream &output (ostream &out) const {
	mccore::Path< node_type, value_type >::output (out)
	  << " r = " << getR ()
	  << " p = " << getP ()
	  << " q = " << getQ ();
	if (0 == size () % 2)
	  out << " y = " << getY ();
	return out;
      }
	  
    };
  
//     /**
//      * Algorithm for determining the shortest path between two nodes
//      * in a directed graph.
//      * @param graph a graph.
//      * @param source the start node id of the path.
//      * @param dest the end node id of the path. 
//      * @return a Path of object that represents the path.
//      */
//     template< class node_type, 
// 	      class edge_type,
// 	      class node_comparator > 
//     static Path< node_type, float > 
//     shortestPath(AbstractGraph< node_type, edge_type, node_comparator > &graph,
// 		 node_type source, unsigned int dest)
//     {
//       vector< Path< node_type, float > > paths;     
//       shortestPath (graph, source, paths);
//       return paths[dest];
//     }

    /**
     * Dijkstra's algorithm for the shortest path in a directed graph.
     * <pre>
     * NODE v, w;
     * SET V, S;             both V and S are SETS
     * int Dist[MAX][MAX];   distance from node v to w
     * int D[MAX];           current distance from the root
     * int P[MAX];           backward path towards root
     * 
     * S = {ROOT}; 
     * for (all other nodes w in V-S) {
     *   D[w] = Dist[ROOT][w];
     *   P[w] = ROOT;
     * }
     * while (S is not yet V) {
     *   choose node w in V-S such that D[w] is minimum;
     *   S = S union {w};
     *   for (each node v in V-S)
     *     if (D[v] > D[w] + Dist[w][v]) {
     *       D[v] = D[w] + Dist[w][v];
     *       P[v] = w;
     *     }
     * }
     * </pre>
     * @param graph a graph.
     * @param source the source node id of the paths.
     * @param paths a collection of Path to fill with the SPT.
     */
//     template< class node_type, 
// 	      class edge_type,
// 	      class node_comparator,
// 	      class value_type >
//     static void 
//     shortestPath (AbstractGraph< node_type, edge_type, node_comparator > &graph, node_type source, vector< Path< node_type, value_type > > &paths)
//     {
//       const value_type MAXVALUE = numeric_limits< value_type >::max ();
//       unsigned int w;
//       unsigned int graphsize;
//       vector< unsigned int > C;
      
//       graphsize = graph.size ();
//       paths.clear ();
//       paths.resize (graphsize);
      
//       // Initialize ---
//       for  (w = 0; w < graphsize; ++w)
// 	{
// 	  value_type value;
	  
// 	  paths[w].push_back (source);
// 	  if  (w == (unsigned int) source)
// 	    {
// 	      value = 0;
// 	    }
// 	  else
// 	    {
// 	      if (graph.internalAreConnected (source, w))
// 		{
// 		  value = graph.internalGetWeight (source, w);
// 		  paths[w].push_back (w);
// 		}
// 	      else
// 		value = MAXVALUE;
// 	      C.push_back (w);
// 	    }
// 	  paths[w].setValue (value);
// 	}
      
//       while (! C.empty ())
// 	{
// 	  vector< unsigned int >::iterator min_iter;
// 	  vector< unsigned int >::iterator k;
// 	  value_type min_value;
// 	  unsigned int min_index;

// 	  min_iter = C.begin ();
// 	  min_value = paths[*min_iter].getValue ();
	  
// 	  for  (k = C.begin (); k != C.end (); ++k)
// 	    {
// 	      if  (paths[*k].getValue () < min_value)
// 		{
// 		  min_value = paths[*k].getValue ();
// 		  min_iter = k;
// 		}
// 	    }
// 	  w = *min_iter;
// 	  C.erase (min_iter);
	  
// 	  // Break if the elements remaining in C are not connected to the
// 	  // source.
// 	  if  (min_value == MAXVALUE)
// 	    break;
	  
// 	  for (k = C.begin (); C.end () != k; ++k)
// 	    {
// 	      value_type new_val;
// 	      unsigned int v;

// 	      v = *k;
// 	      if (graph.internalAreConnected (w, v)
// 		  && paths[v].getValue () > (new_val = min_value + graph.internalGetWeight (w, v)))
// 		{
// 		  paths[v] = paths[w];
// 		  paths[v].push_back (v);
// 		  paths[v].setValue (new_val);
// 		}
// 	    }
// 	}
//     }
    
    /**
     * Dijkstra's algorithm for the shortest path in a directed graph.  The
     * SPT is optimized for graphs with non-negative edge weights.  A path
     * P(x,y) is pruned if there is a z in P(x,y) so that z < x.  The path's
     * value is reset to the max value of the Path's value type.  The source
     * (x) is at the beginning of the path.
     * <pre>
     * NODE v, w;
     * SET V, S;             both V and S are SETS
     * int Dist[MAX][MAX];   distance from node v to w
     * int D[MAX];           current distance from the root
     * int P[MAX];           backward path towards root
     * 
     * S = {ROOT}; 
     * for (all other nodes w in V-S) {
     *   if (areConnected (ROOT, w) and ROOT < w) {
     *     D[w] = Dist[ROOT][w];
     *     P[w] = ROOT;
     * }
     * while (S is not yet V) {
     *   choose node w in V-S such that D[w] is minimum;
     *   S = S union {w};
     *   for (each node v in V-S)
     *     if (D[v] > D[w] + Dist[w][v] and areConnected (w, v) and ROOT < v) {
     *       D[v] = D[w] + Dist[w][v];
     *       P[v] = w;
     *     }
     * }
     * </pre>
     * @param graph a graph.
     * @param source the source node id of the paths.
     * @param paths a collection of Path to fill with the SPT.
     */
//     template< class node_type, 
// 	      class edge_type,
// 	      class node_comparator,
// 	      class Compare >
//     static void sptDijkstraTiernan (const AbstractGraph< node_type, edge_type, node_comparator > &graph, unsigned int source, vector< Path< unsigned int, int > > &paths, const Compare &comparator = less< unsigned int > ())
//     {
//       const int MAXVALUE = numeric_limits< int >::max ();
//       unsigned int w;
//       unsigned int graphsize;
//       vector< unsigned int > C;
      
//       graphsize = graph.size ();
//       paths.clear ();
//       paths.resize (graphsize);
      
//       // Initialize ---
//       for  (w = 0; w < graphsize; ++w)
// 	{
// 	  int value;
	  
// 	  paths[w].push_back (source);
// 	  if  (w == source)
// 	    {
// 	      value = MAXVALUE;
// 	    }
// 	  else
// 	    {
// 	      if (graph.internalAreConnected (source, w))
// 		{
// 		  value = (int) graph.internalGetWeight (source, w);
// 		  paths[w].push_back (w);
// 		}
// 	      else
// 		value = MAXVALUE;
// 	      C.push_back (w);
// 	    }
// 	  paths[w].setValue (value);
// 	}
      
//       while (! C.empty ())
// 	{
// 	  vector< unsigned int >::iterator min_iter;
// 	  vector< unsigned int >::iterator k;
// 	  int min_value;
// 	  unsigned int min_index;
	  
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
// 	  if  (min_value == MAXVALUE)
// 	    break;
	  
// 	  for (k = C.begin (); C.end () != k; ++k)
// 	    {
// 	      int new_val;
// 	      unsigned int v;
	      
// 	      v = *k;
// 	      if (comparator (source, w)
// 		  && graph.internalAreConnected (w, v)
// 		  && (paths[v].getValue () > (new_val = min_value + (int) graph.internalGetWeight (w, v))))
// 	        {
// 		  paths[v] = paths[w];
// 		  paths[v].push_back (v);
// 		  paths[v].setValue (new_val);
// 		}
// 	    }
// 	}
//     }
    
    /**
     * Horton's algorithm for the minimum cycle basis.  It returns a vector
     * of Paths (cycles where the first and last vertices are connected) in
     * the graph internal numerotation.
     * @param graph an UndirectedAbstractGraph.
     * @return the minimum cycle basis for graph.
     */
//     template< class node_type,
// 	      class edge_type,
// 	      class node_comparator >
//     static vector< mccore::Path< unsigned int, int > > 
//     cycleBaseHorton (const UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph)
//     {
//       vector< mccore::Path< unsigned int, int > > bag;
//       vector< Path< unsigned int, int > >::iterator p;
//       unsigned int i;
//       vector< vector< Path< unsigned int, int > > >::iterator ii;
//       const map< int, pair< int, int > > &edgesCoordinates = graph.getInternalEdgeCoordinateMap ();
//       map< int, pair< int, int > >::const_iterator ecIt;
//       const int MAXVALUE = numeric_limits< int >::max ();
      
//       for (i = 0; i < (unsigned int) graph.size (); ++i)
// 	{
// 	  vector< Path< unsigned int, int > > tmp;
	  
// 	  sptDijkstraTiernan (graph, i, tmp, less< unsigned int > ());
// 	  for (ecIt = edgesCoordinates.begin (); edgesCoordinates.end () != ecIt; ++ecIt)
// 	    {
// 	      int j;
// 	      int k;
	      
// 	      j = ecIt->second.first;
// 	      k = ecIt->second.second;
// 	      if (MAXVALUE != tmp[j].getValue ()
// 		  && MAXVALUE != tmp[k].getValue ()
// 		  && *++(tmp[j].begin ()) != *++(tmp[k].begin ()))
// 		{
// 		  Path< unsigned int, int > Pvx = tmp[j];
// 		  Path< unsigned int, int > Pvy = tmp[k];
// 		  Path< unsigned int, int > Pvxp = Pvx; 
// 		  Path< unsigned int, int > Pvyp = Pvy; 
// 		  Path< unsigned int, int > inter;
		  
// 		  std::sort (Pvxp.begin (), Pvxp.end ());
// 		  std::sort (Pvyp.begin (), Pvyp.end ());
// 		  set_intersection (Pvxp.begin (), Pvxp.end (),
// 				    Pvyp.begin (), Pvyp.end (),
// 				    inserter (inter, inter.begin ()));
		  
// 		  if (inter.size () == 1 && inter.front () == i)
// 		    {
// 		      mccore::Path< unsigned int, int > C = Pvx;
		      
// 		      C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
// 		      C.pop_back ();
// 		      C.setValue (Pvx.getValue () + Pvy.getValue () + (int) graph.internalGetWeight (j, k));
// 		      bag.push_back (C);
// 		    }
// 		}
// 	    }
// 	}
      
//       sort (bag.begin (), bag.end ());
//       gOut (3) << "Found " << bag.size () << " potential cycles before elimination" << endl;
//       bag = gaussianElimination (graph, bag);
//       sort (bag.begin (), bag.end ());
//       gOut (3) << "Found " << bag.size () << " cycles." << endl;
//       return bag;
//     }
    
    /**
     * Adds a Path in the digraph Dr.
     * @param sp the Path to add.
     * @param graph the studied graph.
     * @param Dr the digraph.
     */
//     template< class node_type,
// 	      class edge_type,
// 	      class node_comparator >
//     static void addSP (Path< unsigned int, int > &sp, const UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, AbstractGraph< unsigned int, bool, less< unsigned int > > &Dr)
//     {
//       Path< unsigned int, int >::reverse_iterator fit;
//       Path< unsigned int, int >::reverse_iterator lit;
      
//       fit = sp.rbegin ();
//       Dr.insert (*fit);
//       for (lit = fit++; sp.rend () != fit; ++fit, ++lit)
// 	{
// 	  Dr.insert (*fit);
// 	  if (! Dr.areConnected (*lit, *fit))
// 	    Dr.connect (*lit, *fit, graph.internalGetWeight (*lit, *fit));
// 	}
//     }
    
//     template< class node_type,
// 	      class edge_type,
// 	      class node_comparator >
//     static vector< Path< unsigned int, int > >
//     breadthFirstPaths (const AbstractGraph< unsigned int, bool, less< unsigned int > > &Dr, const UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, unsigned int q)
//     {
//       vector< Path< unsigned int, int> > result;
//       list< Path< unsigned int, int> > lst (1, Path< unsigned int, int> ());
//       Path< unsigned int, int > &tmp = lst.front ();
      
//       tmp.push_back (q);
//       tmp.setValue (0);
//       while (! lst.empty ())
// 	{
// 	  Path< unsigned int, int > &front = lst.front ();
// 	  unsigned int endNode;
// 	  list< unsigned int > neighbors;
// 	  list< unsigned int >::iterator neighborsIt;

// 	  endNode = front.back ();
// 	  neighbors = Dr.getNeighbors (endNode);
// 	  neighborsIt = neighbors.begin ();
// 	  if (neighbors.end () == neighborsIt)
// 	    {
// 	      reverse (front.begin (), front.end ());
// 	      result.push_back (front);
// 	    }
// 	  else
// 	    {
// 	      for (; neighbors.end () != neighborsIt; ++neighborsIt)
// 		{
// 		  lst.push_back (front);
// 		  Path< unsigned int, int > &tmp = lst.back ();

// 		  tmp.push_back (*neighborsIt);
// 		  tmp.setValue (tmp.getValue () + 1);
// 		}
// 	    }
// 	  lst.pop_front ();
// 	}
//       return result;
//     }
      
    /**
     * Vismara's union of minimum cycle bases algorithm.  It returns a
     * vector of Path (cycles where the first and last vertices are
     * connected) in graph numerotation.
     * @param graph the UndirectedAbstractGraph input graph.
     * @param D a vector of digraphs witch has the same size as graph, it
     * contains the shortest paths digraph from a vertice to the source (it
     * is a turnaround due to GraphAlgo-AbstractGraph dependencies).
     * @return a vector of Path.
     */
//     template< class node_type,
// 	      class edge_type,
// 	      class node_comparator >
//     static vector< mccore::Path< unsigned int, int > >
//     unionMinimumCycleBases (const UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, vector< AbstractGraph< unsigned int, bool >* > &D)
//     {
//       const int MAXVALUE = numeric_limits< int >::max ();
//       unsigned int r;
//       vector< Path< unsigned int, int > > prototypes;
//       vector< Path< unsigned int, int > >::iterator protIt;
//       vector< mccore::Path< unsigned int, int > > CR;
//       vector< Path< unsigned int, int > >::iterator it;
      
//       for (r = 0; (unsigned int) graph.size () > r; ++r)
// 	{
// 	  vector< Path< unsigned int, int > > spt;
// 	  unsigned int y;
// 	  AbstractGraph< unsigned int, bool > &Dr = *D[r];
	  
// 	  sptDijkstraTiernan (graph, r, spt, greater< unsigned int > ());
// 	  for (y = 0; (unsigned int) graph.size () > y && y < r; ++y)
// 	    {
// 	      Path< unsigned int, int > &py = spt[y];
// 	      vector< unsigned int > S;
// 	      list< int > neighbors;
// 	      list< int >::iterator z;
// 	      vector< unsigned int >::iterator p;
// 	      vector< unsigned int >::iterator q;
	      
// 	      neighbors = graph.internalGetNeighbors (y);
// 	      for (z = neighbors.begin (); neighbors.end () != z; ++z)
// 		{
// 		  if ((unsigned int) *z < r)
// 		    {
// 		      Path< unsigned int, int > &pz = spt[*z];
		      
// 		      if (MAXVALUE != py.getValue ()
// 			  && MAXVALUE != pz.getValue ())
// 			{
// 			  if (pz.getValue () + (int) graph.internalGetWeight (y, *z) == py.getValue ())
// 			    {
// 			      GraphAlgo::addSP (py, graph, Dr);
// 			      GraphAlgo::addSP (pz, graph, Dr);
// 			      Dr.connect (y, *z, (int) graph.internalGetWeight (y, *z));
// 			      S.push_back (*z);
// 			    }
// 			  else if (pz.getValue () != py.getValue () + (int) graph.internalGetWeight (y, *z) && (unsigned int) *z < y)
// 			    {
// 			      set< unsigned int > sy;
// 			      set< unsigned int > sz;
// 			      vector< unsigned int > inter;
			      
// 			      sy.insert (py.begin (), py.end ());
// 			      sz.insert (pz.begin (), pz.end ());
// 			      set_intersection (sy.begin (), sy.end (),
// 						sz.begin (), sz.end (),
// 						inserter (inter, inter.begin ()));
			      
// 			      if (1 == inter.size () && inter.front () == r)
// 				{
// 				  prototypes.push_back (py);
// 				  Path< unsigned int, int > &cycle = prototypes.back ();
				  
// 				  GraphAlgo::addSP (py, graph, Dr);
// 				  GraphAlgo::addSP (pz, graph, Dr);
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
// 			Path< unsigned int, int > &pp = spt[*p];
// 			Path< unsigned int, int > &pq = spt[*q];
// 			set< unsigned int > sp;
// 			set< unsigned int > sq;
// 			vector< unsigned int > inter;

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
// 				Path< unsigned int, int > &cycle = prototypes.back ();

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
//       sort (prototypes.begin (), prototypes.end ());
//       gOut (3) << "Found " << prototypes.size () << " potential prototypes before elimination" << endl;
//       gOut (4) << prototypes << endl;
//       prototypes = BElimination (graph, prototypes);
//       gOut (3) << "Found " << prototypes.size () << " prototypes" << endl;
//       gOut (4) << prototypes << endl;
      
//       // Enumeration of CR.
//       for (protIt = prototypes.begin (); prototypes.end () != protIt; ++protIt)
// 	{
// 	  Path< unsigned int, int > &prototype = *protIt;
// 	  unsigned int p;
// 	  unsigned int q;
// 	  vector< Path< unsigned int, int > > pPaths;
// 	  vector< Path< unsigned int, int > > qPaths;
// 	  vector< Path< unsigned int, int > >::iterator pPathIterator;
// 	  vector< Path< unsigned int, int > >::iterator qPathIterator;

// 	  r = prototype.getR ();
// 	  p = prototype.getP ();
// 	  q = prototype.getQ ();
// 	  pPaths = GraphAlgo::breadthFirstPaths (*D[r], graph, p);
// 	  qPaths = GraphAlgo::breadthFirstPaths (*D[r], graph, q);
	  
// 	  for (pPathIterator = pPaths.begin (); pPaths.end () != pPathIterator; ++pPathIterator)
// 	    for (qPathIterator = qPaths.begin (); qPaths.end () != qPathIterator; ++qPathIterator)
// 	      {
// 		CR.push_back (*pPathIterator);
// 		mccore::Path< unsigned int, int > &cycle = CR.back ();
		
// 		if (0 == prototype.size () % 2)
// 		  {
// 		    unsigned int y;

// 		    y = prototype.getY ();
// 		    cycle.push_back (y);
// 		    cycle.setValue (cycle.getValue () + (int) graph.internalGetWeight (p, y) + (int) graph.internalGetWeight (y, q));
// 		  }
// 		else
// 		  cycle.setValue (cycle.getValue () + (int) graph.internalGetWeight (p, q));
// 		cycle.insert (cycle.end (), qPathIterator->rbegin (), qPathIterator->rend () - 1);
// 		cycle.setValue (cycle.getValue () + qPathIterator->getValue ());
// 	      }
// 	}
//       gOut (3) << "Found " << CR.size () << " cycles" << endl;
//       return CR;
//     }
    
//     /**
//      * Uses the Gaussian Elimination algorithm to find non linearly
//      * dependant cycles from the set of enumerated cycles.
//      * @param graph an UndirectedAbstractGraph.
//      * @param bag a vector of cycles.
//      * @return a linearly independant vector of cycles.
//      */
//     template< class node_type, 
// 	      class edge_type,
// 	      class node_comparator >
//     static vector< mccore::Path< unsigned int, int > >
//     gaussianElimination (const AbstractGraph< node_type, edge_type, node_comparator > &graph, vector< mccore::Path< unsigned int, int > >& bag)
//     {
//       typedef vector< mccore::Path< unsigned int, int > >::iterator vpiterator;
      
//       if (bag.empty ())
// 	return bag;
      
//       vector< bool* > matrix;
//       vector< bool* >::iterator n;
      
//       unsigned int i;
//       unsigned int j;
//       vector< mccore::Path< unsigned int, int > > newbag;
//       vpiterator p, q;
//       unsigned int edgeSize;
      
//       vector< vpiterator > marked;
      
//       edgeSize = graph.edgeSize ();

//       bool* row = new bool[edgeSize];    

//       for (p = bag.begin (); p != bag.end (); ++p)
// 	{
// 	  mccore::Path< unsigned int, int >::iterator r;
// 	  mccore::Path< unsigned int, int >::iterator s;
// 	  bool inserted;
	  
// 	  for (i = 0; i < edgeSize; ++i)
// 	    row[i] = false;
	  
// 	  // Let's see if *p is linearly independent to the content of newbag 
// 	  //       cout << "Treating " << *p << endl;
	  
// 	  s = p->begin ();
// 	  row[graph.internalGetEdge (p->back (), *s)] = true;
// 	  for (r = s++; p->end () != s; ++r, ++s)
// 	    row[graph.internalGetEdge (*r, *s)] = true;
	  
// 	  inserted = false;
// 	  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
// 	    {
// 	      j = 0;
// 	      while (j < edgeSize && row[j] == false && (*n)[j] == false)
// 		++j;
// 	      if (j == edgeSize)
// 		continue;
	      
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
// 		  for (i = 0; i < edgeSize; ++i)
// 		    row[i] ^= (*n)[i];
// 		  continue;
// 		}
// 	    }
	  
// 	  if (!inserted)
// 	    {
// 	      for (j = 0; j < edgeSize; ++j)
// 		if (true == row[j])
// 		  {
// 		    gOut (4) << "Rejecting " << *p << endl;
// 		    break;
// 		  }
// 	      if (j != edgeSize)
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
// 		  mccore::Path< unsigned int, int >::iterator r;
// 		  mccore::Path< unsigned int, int >::iterator s;
// 		  bool* row2;
// 		  unsigned int k;
		  
// 		  row2 = new bool[edgeSize];	  
// 		  for (k = 0; k < edgeSize; ++k)
// 		    row2[k] = false;
		  
// 		  s = marked[i]->begin ();
// 		  row2[graph.internalGetEdge (marked[i]->back (), *s)] = true;
// 		  for (r = s++; marked[i]->end () != s; ++r, ++s)
// 		    row2[graph.internalGetEdge (*r, *s)] = true;
		  
// 		  inserted = false;	
// 		  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
// 		    {
// 		      j = 0;    
// 		      while (j < edgeSize && row2[j] == false && (*n)[j] == false)
// 			++j;
// 		      if (j == edgeSize)
// 			continue;
		      
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
//   			  for (k = 0; k < edgeSize; ++k)
// 			    row2[k] ^= (*n)[k];
// 			  continue;
// 			}
// 		    }
		  
// 		  if (!inserted)
// 		    {
// 		      for (j = 0; j < edgeSize; ++j)
// 			if (row2[j] == true)
// 			  break;
// 		      if (j != edgeSize)
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
// 	delete[] *n;
//       delete[] row;
//       return newbag;
//     }

//     static pair< bool, vector< vector< bool > >::iterator > gElimination (vector< bool > &candidate, vector< vector< bool > > &matrix)
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
// 	    continue;
// 	  if (true == *cIt && false == *mIt)
// 	    return make_pair (false, row) ;
// 	  if (true == *cIt && true == *mIt)
// 	    {
// 	      // Reduce candidate
// 	      for (cIt = candidate.begin (), mIt = row->begin (); candidate.end () != cIt; ++cIt, ++mIt)
// 		*cIt = *cIt xor *mIt;
// 	      continue;
// 	    }
// 	}
//       return make_pair (candidate.end () == find (candidate.begin (), candidate.end (), true), matrix.end ());
//     }

//     template< class node_type, 
// 	      class edge_type,
// 	      class node_comparator >
//     static vector< Path< unsigned int, int > >
//     BElimination (const AbstractGraph< node_type, edge_type, node_comparator > &graph, vector< Path< unsigned int, int > >& bag)
//     {
//       if (bag.empty ())
// 	return bag;
      
//       vector< vector< bool > > BLess;
//       vector< vector< bool > > B;
//       vector< Path< unsigned int, int > > newbag;
//       vector< Path< unsigned int, int > >::iterator p;
//       unsigned int edgeSize;
//       unsigned int pathSize = 0;
//       vector< bool > candidate2;

//       edgeSize = graph.edgeSize ();
      
//       for (p = bag.begin (); p != bag.end (); ++p)
// 	{
// 	  Path< unsigned int, int >::iterator r;
// 	  Path< unsigned int, int >::iterator s;
// 	  vector< bool > candidate (edgeSize, false);

// 	  if (p->size () != pathSize)
// 	    {
// 	      BLess = B;
// 	      pathSize = p->size ();
// 	    }
	  
// 	  s = p->begin ();
// 	  candidate[graph.internalGetEdge (p->back (), *s)] = true;
// 	  for (r = s++; p->end () != s; ++r, ++s)
// 	    candidate[graph.internalGetEdge (*r, *s)] = true;
// 	  candidate2 = candidate;

// 	  if (! GraphAlgo::gElimination (candidate, BLess).first)
// 	    {
// 	      pair< bool, vector< vector< bool > >::iterator > res = GraphAlgo::gElimination (candidate2, B);

// 	      newbag.push_back (*p);
// 	      if (! res.first)
// 		B.insert (res.second, candidate2);
// 	    }
// 	}
//       return newbag;
//     }
  };
}

#endif
