//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2004-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Dec 10 19:09:13 2004
// $Revision: 1.15 $
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

#include "Graph.h"
#include "OrientedGraph.h"
#include "Path.h"

using namespace std;



namespace mccore
{
  /**
   * Undirected graph implementation.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: UndirectedGraph.h,v 1.15 2005-02-01 22:13:33 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class EW = float,
	    class Vertex_Comparator = less< V > >	    
  class UndirectedGraph : public Graph< V, E, VW, EW, Vertex_Comparator>
  {
    static const int MAXVALUE = numeric_limits< int >::max ();
    static const unsigned int MAXUIVALUE = numeric_limits< unsigned int >::max ();

  public:

    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::size_type size_type;
    typedef typename Graph< V, E, VW, EW, Vertex_Comparator >::edge_size_type edge_size_type;
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
    template< class Compare >
    void sptDijkstraTiernan (label source, vector< Path< label, unsigned int > > &paths, const Compare &comparator = less< label > ())
    {
      label w;
      size_type graphsize;
      vector< label > C;
      
      graphsize = size ();
      paths.clear ();
      paths.resize (graphsize);
      
      // Initialize ---
      for  (w = 0; w < graphsize; ++w)
	{
	  int value;
	  
	  paths[w].push_back (source);
	  if  (w == source)
	    {
	      value = MAXUIVALUE;
	    }
	  else
	    {
	      if (internalAreConnected (source, w))
		{
		  value = internalGetEdgeWeight (source, w);
		  paths[w].push_back (w);
		}
	      else
		{
		  value = MAXUIVALUE;
		}
	      C.push_back (w);
	    }
	  paths[w].setValue (value);
	}
      
      while (! C.empty ())
	{
	  typename vector< label >::iterator min_iter;
	  typename vector< label >::iterator k;
	  int min_value;
	  label min_index;
	  
	  min_iter = C.begin ();
	  min_value = paths[*min_iter].getValue ();
	  
	  for  (k = C.begin (); k != C.end (); ++k)
	    if  (paths[*k].getValue () < min_value)
	      {
		min_value = paths[*k].getValue ();
		min_iter = k;
	      }
	  w = *min_iter;
	  C.erase (min_iter);
	  
	  // Break if the elements remaining in C are not connected to the
	  // source.
	  if  (min_value == MAXUIVALUE)
	    {
	      break;
	    }
	  
	  for (k = C.begin (); C.end () != k; ++k)
	    {
	      int new_val;
	      unsigned int v;
	      
	      v = *k;
	      if (comparator (source, w)
		  && internalAreConnected (w, v)
		  && (paths[v].getValue () > (new_val = min_value + internalGetEdgeWeight (w, v))))
	        {
		  paths[v] = paths[w];
		  paths[v].push_back (v);
		  paths[v].setValue (new_val);
		}
	    }
	}
    }
    
    /**
     * Uses the Gaussian Elimination algorithm to find non linearly
     * dependant cycles from the set of enumerated cycles.
     * @param graph an UndirectedAbstractGraph.
     * @param bag a vector of cycles.
     * @return a linearly independant vector of cycles.
     */
    vector< mccore::Path< label, int > > gaussianElimination (vector< mccore::Path< label, int > >& bag)
    {
      typedef typename vector< mccore::Path< label, int > >::iterator vpiterator;
      
      if (bag.empty ())
	{
	  return bag;
	}
      
      vector< bool* > matrix;
      vector< bool* >::iterator n;
      label i;
      label j;
      vector< mccore::Path< label, int > > newbag;
      vpiterator p, q;
      size_type edgeSize;
      vector< vpiterator > marked;
      bool *row;
      
      edgeSize = edgeSize ();
      row = new bool[edgeSize];    
      for (p = bag.begin (); p != bag.end (); ++p)
	{
	  typename mccore::Path< label, int >::iterator r;
	  typename mccore::Path< label, int >::iterator s;
	  bool inserted;
	  
	  for (i = 0; i < edgeSize; ++i)
	    row[i] = false;
	  
	  // Let's see if *p is linearly independent to the content of newbag 
	  //       cout << "Treating " << *p << endl;
	  
	  s = p->begin ();
	  row[internalGetEdgeLabel (p->back (), *s)] = true;
	  for (r = s++; p->end () != s; ++r, ++s)
	    {
	      row[internalGetEdgeLabel (*r, *s)] = true;
	    }
	  
	  inserted = false;
	  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
	    {
	      j = 0;
	      while (j < edgeSize && row[j] == false && (*n)[j] == false)
		{
		  ++j;
		}
	      if (j == edgeSize)
		{
		  continue;
		}
	      
	      if (row[j] == true && (*n)[j] == false)
		{
		  gOut (4) << "Marking " << *p << endl;
		  marked.push_back (p);
		  inserted = true;
		  break;
		}
	      
	      if (row[j] == true && (*n)[j] == true)
		{
		  //Reduce the current
		  for (i = 0; i < edgeSize; ++i)
		    {
		      row[i] ^= (*n)[i];
		    }
		  continue;
		}
	    }
	  
	  if (! inserted)
	    {
	      for (j = 0; j < edgeSize; ++j)
		{
		  if (true == row[j])
		    {
		      gOut (4) << "Rejecting " << *p << endl;
		      break;
		    }
		}
	      if (j != edgeSize)
		{
		  gOut (4) << "Marking " << *p << endl;
		  marked.push_back (p);
		}
	    }
	  
	  // Let's see if we should try to insert the marked...
	  if (p + 1 == bag.end () || (p + 1)->size () > p->size ())
	    {
	      gOut (4) << endl << "Inserting marked cycles (" << marked.size ()
		       << ")" << endl << endl;
	      
	      for (i = 0; i < marked.size (); ++i)
		{
		  typename mccore::Path< label, int >::iterator r;
		  typename mccore::Path< label, int >::iterator s;
		  bool *row2;
		  unsigned int k;
		  
		  row2 = new bool[edgeSize];	  
		  for (k = 0; k < edgeSize; ++k)
		    {
		      row2[k] = false;
		    }		  
		  s = marked[i]->begin ();
		  row2[internalGetEdgeLabel (marked[i]->back (), *s)] = true;
		  for (r = s++; marked[i]->end () != s; ++r, ++s)
		    {
		      row2[graph.internalGetEdge (*r, *s)] = true;
		    }		  
		  inserted = false;	
		  for (n = matrix.begin (), q = newbag.begin (); q != newbag.end (); ++n, ++q)
		    {
		      j = 0;    
		      while (j < edgeSize && row2[j] == false && (*n)[j] == false)
			{
			  ++j;
			}
		      if (j == edgeSize)
			{
			  continue;
			}
		      
		      if (row2[j] == true && (*n)[j] == false)
			{
			  gOut (4) << "Inserting " << *marked[i] << " " << *row2 << endl;
			  matrix.insert (n, row2);
			  newbag.insert (q, *marked[i]);
			  inserted = true;
			  break;
			}
		      
		      if (row2[j] == true && (*n)[j] == true)
			{
			  //Reduce the current
  			  for (k = 0; k < edgeSize; ++k)
			    {
			      row2[k] ^= (*n)[k];
			    }
			  continue;
			}
		    }
		  
		  if (! inserted)
		    {
		      for (j = 0; j < edgeSize; ++j)
			{
			  if (row2[j] == true)
			    {
			      break;
			    }
			}
		      if (j != edgeSize)
			{
			  gOut (4) << "Accepting " << *marked[i] << endl;
			  matrix.push_back (row2);
			  newbag.push_back (*marked[i]);
			}
		      else
			{
			  gOut (4) << "Rejecting " << *marked[i] << endl;
			  delete[] row2;
			}
		    }
		}
	      marked.clear ();
	      gOut (4) << "done" << endl;
	    }
	}
      
      for (n = matrix.begin (); n != matrix.end (); ++n)
	{
	  delete[] *n;
	}
      delete[] row;
      return newbag;
    }

    /**
     * Horton's algorithm for the minimum cycle basis.  It returns a vector
     * of Paths (cycles where the first and last vertices are connected) in
     * the graph internal numerotation.
     * @return the minimum cycle basis for this.
     */
    vector< mccore::Path< label, int > > cycleBaseHorton () const
    {
      vector< mccore::Path< label, int > > bag;
      typename vector< Path< label, int > >::iterator p;
      label i;
      
      for (i = 0; i < size (); ++i)
	{
	  vector< Path< label, int > > tmp;
	  typename EV2ELabel::const_iterator ecIt;

	  sptDijkstraTiernan (i, tmp, less< label > ());
	  for (ecIt = ev2elabel.begin (); ev2elabel.end () != ecIt; ++ecIt)
	    {
	      label j;
	      label k;
	      
	      j = ecIt->first.getHeadLabel ();
	      k = ecIt->first.getTailLabel ();
	      if (j < k
		  && MAXVALUE != tmp[j].getValue ()
		  && MAXVALUE != tmp[k].getValue ()
		  && *++(tmp[j].begin ()) != *++(tmp[k].begin ()))
		{
		  Path< label, int > Pvx = tmp[j];
		  Path< label, int > Pvy = tmp[k];
		  Path< label, int > Pvxp = Pvx; 
		  Path< label, int > Pvyp = Pvy; 
		  Path< label, int > inter;
		  
		  std::sort (Pvxp.begin (), Pvxp.end ());
		  std::sort (Pvyp.begin (), Pvyp.end ());
		  set_intersection (Pvxp.begin (), Pvxp.end (),
				    Pvyp.begin (), Pvyp.end (),
				    inserter (inter, inter.begin ()));
		  
		  if (inter.size () == 1 && inter.front () == i)
		    {
		      mccore::Path< label, int > C = Pvx;
		      
		      C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
		      C.pop_back ();
		      C.setValue (Pvx.getValue () + Pvy.getValue () + internalGetEdgeWeight (ecIt->second));
		      bag.push_back (C);
		    }
		}
	    }
	}
      
      sort (bag.begin (), bag.end ());
      gOut (3) << "Found " << bag.size () << " potential cycles before elimination" << endl;
      bag = gaussianElimination (bag);
      sort (bag.begin (), bag.end ());
      gOut (3) << "Found " << bag.size () << " cycles." << endl;
      return bag;
    }

  private:
    
    /**
     * Adds a Path in the digraph Dr.
     * @param p the Path to add.
     * @param Dr the digraph.
     */
    void addPath (Path< label, EW > &sp, OrientedGraph< label, bool, VW, EW > &Dr) const
    {
      typename Path< label, EW >::reverse_iterator fit;
      typename Path< label, EW >::reverse_iterator lit;
      
      fit = p.rbegin ();
      Dr.insert (*fit);
      for (lit = fit++; p.rend () != fit; ++fit, ++lit)
	{
	  Dr.insert (*fit);
	  if (! Dr.areConnected (*lit, *fit))
	    {
	      Dr.connect (*lit, *fit, internalGetEdgeWeight (*lit, *fit));
	    }
	}
    }

    pair< bool, vector< vector< bool > >::iterator > gElimination (vector< bool > &candidate, vector< vector< bool > > &matrix)
    {
      vector< vector< bool > >::iterator row;
      vector< bool >::iterator cIt;

      for (row = matrix.begin (); matrix.end () != row; ++row)
	{
	  vector< bool >::const_iterator mIt;

	  for (cIt = candidate.begin (), mIt = row->begin ();
	       candidate.end () != cIt && false == *cIt && false == *mIt;
	       ++cIt, ++mIt);
	  if (candidate.end () == cIt)
	    {
	      continue;
	    }
	  if (true == *cIt && false == *mIt)
	    {
	      return make_pair (false, row);
	    }
	  if (true == *cIt && true == *mIt)
	    {
	      // Reduce candidate
	      for (cIt = candidate.begin (), mIt = row->begin (); candidate.end () != cIt; ++cIt, ++mIt)
		{
		  *cIt = *cIt xor *mIt;
		}
	      continue;
	    }
	}
      return make_pair (candidate.end () == find (candidate.begin (), candidate.end (), true), matrix.end ());
    }

    /**
     */
    vector< Path< unsigned int, int > > BElimination (vector< Path< unsigned int, int > >& bag) const
    {
      if (bag.empty ())
	return bag;
      
      vector< vector< bool > > BLess;
      vector< vector< bool > > B;
      vector< Path< label, int > > newbag;
      typename vector< Path< label, int > >::iterator p;
      edge_size_type edgeSize;
      label pathSize = 0;
      vector< bool > candidate2;

      edgeSize = edgeSize ();
      
      for (p = bag.begin (); p != bag.end (); ++p)
	{
	  typename Path< label, int >::iterator r;
	  typename Path< label, int >::iterator s;
	  vector< bool > candidate (edgeSize, false);

	  if (p->size () != pathSize)
	    {
	      BLess = B;
	      pathSize = p->size ();
	    }
	  
	  s = p->begin ();
	  candidate[internalGetEdge (p->back (), *s)] = true;
	  for (r = s++; p->end () != s; ++r, ++s)
	    {
	      candidate[internalGetEdge (*r, *s)] = true;
	    }
	  candidate2 = candidate;

	  if (! gElimination (candidate, BLess).first)
	    {
	      pair< bool, vector< vector< bool > >::iterator > res = gElimination (candidate2, B);

	      newbag.push_back (*p);
	      if (! res.first)
		{
		  B.insert (res.second, candidate2);
		}
	    }
	}
      return newbag;
    }
    
  protected:
    
    /**
     * Vismara's union of minimum cycle bases algorithm.  It returns a
     * vector of Path (cycles where the first and last vertices are
     * connected) in graph numerotation.  We should be able to cast the edge
     * weights to unsigned int.
     * @return a vector of Path.
     */
    vector< mccore::Path< label, unsigned int > > internalUnionMinimumCycleBases () const
    {
      label r;
      vector< Path< label, unsigned int > > prototypes;
      typename vector< Path< label, unsigned int > >::iterator protIt;
      vector< Path< label, unsigned int > > CR;
      typename vector< Path< label, unsigned int > >::iterator it;
      vector< OrientedGraph< label, bool, bool, unsigned int > > D (size ());

      for (r = 0; size () > r; ++r)
	{
	  vector< Path< label, unsigned int > > spt;
	  label y;
	  OrientedGraph< label, bool, bool, unsigned int > &Dr = D[r];
	  
	  sptDijkstraTiernan (r, spt, greater< unsigned int > ());
	  for (y = 0; size () > y && y < r; ++y)
	    {
	      Path< label, int > &py = spt[y];
	      vector< label > S;
	      list< label > neighbors;
	      typename list< label >::iterator z;
	      typename vector< label >::iterator p;
	      typename vector< label >::iterator q;
	      
	      neighbors = internalNeighborhood (y);
	      for (z = neighbors.begin (); neighbors.end () != z; ++z)
		{
		  if (*z < r)
		    {
		      Path< label, int > &pz = spt[*z];
		      
		      if (MAXVALUE != py.getValue ()
			  && MAXVALUE != pz.getValue ())
			{
			  if (pz.getValue () + internalGetWeight (y, *z) == py.getValue ())
			    {
			      addSP (py, Dr);
			      addSP (pz, Dr);
			      Dr.connect (y, *z, internalGetVertexWeight (y, *z));
			      S.push_back (*z);
			    }
			  else if (pz.getValue () != py.getValue () + internalGetVertexWeight (y, *z) && *z < y)
			    {
			      set< label > sy;
			      set< label > sz;
			      vector< label > inter;
			      
			      sy.insert (py.begin (), py.end ());
			      sz.insert (pz.begin (), pz.end ());
			      set_intersection (sy.begin (), sy.end (),
						sz.begin (), sz.end (),
						inserter (inter, inter.begin ()));
			      
			      if (1 == inter.size () && inter.front () == r)
				{
				  prototypes.push_back (py);
				  Path< label, int > &cycle = prototypes.back ();
				  
				  addSP (py, Dr);
				  addSP (pz, Dr);
				  cycle.setP (cycle.size () - 1);
				  cycle.setQ (cycle.size ());
				  cycle.insert (cycle.end (), pz.rbegin (), pz.rend () - 1);
				  cycle.setValue (cycle.getValue () + pz.getValue () + 1);
				  gOut (4) << cycle << " r = " << cycle.getR ()
					   << " p = " << cycle.getP ()
					   << " q = " << cycle.getQ () << endl;
				}
			    }
			}
		    }
		}
	      for (p = S.begin (); S.end () != p; ++p)
		for (q = S.begin (); S.end () != q; ++q)
		  {
		    if (p != q)
		      {
			Path< label, int > &pp = spt[*p];
			Path< label, int > &pq = spt[*q];
			set< label > sp;
			set< label > sq;
			vector< label > inter;

			sp.insert (pp.begin (), pp.end ());
			sq.insert (pq.begin (), pq.end ());
			set_intersection (sp.begin (), sp.end (),
					  sq.begin (), sq.end (),
					  inserter (inter, inter.begin ()));
			
			if (1 == inter.size () && inter.front () == r)
			  {
			    if (*p < *q)
			      {
				prototypes.push_back (pp);
				Path< label, int > &cycle = prototypes.back ();

				cycle.setP (cycle.size () - 1);
				cycle.setQ (cycle.size () + 1);
				cycle.push_back (y);
				cycle.insert (cycle.end (), pq.rbegin (), pq.rend () - 1);
				cycle.setValue (cycle.getValue () + pq.getValue () + 2);
				gOut (4) << cycle << " r = " << cycle.getR ()
					 << " p = " << cycle.getP ()
					 << " y = " << cycle.getY ()
					 << " q = " << cycle.getQ () << endl;
			      }
			  }
		      }
		  }
	    }
	}
      sort (prototypes.begin (), prototypes.end ());
      gOut (3) << "Found " << prototypes.size () << " potential prototypes before elimination" << endl;
      gOut (4) << prototypes << endl;
      prototypes = BElimination (prototypes);
      gOut (3) << "Found " << prototypes.size () << " prototypes" << endl;
      gOut (4) << prototypes << endl;
      
      // Enumeration of CR.
      for (protIt = prototypes.begin (); prototypes.end () != protIt; ++protIt)
	{
	  Path< label, int > &prototype = *protIt;
	  label p;
	  label q;
	  vector< Path< label, int > > pPaths;
	  vector< Path< label, int > > qPaths;
	  typename vector< Path< label, int > >::iterator pPathIterator;
	  typename vector< Path< label, int > >::iterator qPathIterator;

	  r = prototype.getR ();
	  p = prototype.getP ();
	  q = prototype.getQ ();
	  pPaths = breadthFirstPaths (*D[r], p);
	  qPaths = breadthFirstPaths (*D[r], q);
	  
	  for (pPathIterator = pPaths.begin (); pPaths.end () != pPathIterator; ++pPathIterator)
	    {
	      for (qPathIterator = qPaths.begin (); qPaths.end () != qPathIterator; ++qPathIterator)
		{
		  CR.push_back (*pPathIterator);
		  Path< label, int > &cycle = CR.back ();
		
		  if (0 == prototype.size () % 2)
		    {
		      unsigned int y;

		      y = prototype.getY ();
		      cycle.push_back (y);
		      cycle.setValue (cycle.getValue ()
				      + internalGetVertexWeight (p, y)
				      + internalGetVertexWeight (y, q));
		    }
		  else
		    {
		      cycle.setValue (cycle.getValue () + internalGetVertexWeight (p, q));
		    }
		  cycle.insert (cycle.end (), qPathIterator->rbegin (), qPathIterator->rend () - 1);
		  cycle.setValue (cycle.getValue () + qPathIterator->getValue ());
		}
	    }
	}
      gOut (3) << "Found " << CR.size () << " cycles" << endl;
      return CR;
    }
    
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
