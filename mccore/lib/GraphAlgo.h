//                              -*- Mode: C++ -*- 
// GraphAlgo.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 16:47:26 2003
// Last Modified By : Martin Larose
// Last Modified On : Tue Apr  6 17:21:12 2004
// Update Count     : 53
// Status           : Unknown.
// 

#ifndef _GraphAlgo_h_
#define _GraphAlgo_h_

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <vector>

#include "AbstractGraph.h"
#include "Messagestream.h"
#include "Path.h"

using namespace std;

#define MAXFLOAT numeric_limits< float > ().max ()



namespace mccore {


//   template< class value_type >
//   class lessPath
//   {
//   public:
//     bool operator () (const Path< int, value_type> &l, const Path< int, value_type> &r) const
//     {
//       return (l < r
// 	      || (l.getValue () == r.getValue ()
// 		  && ((const list< int >&) l) < ((const list< int >&) r)));
//     }
//   };
  
  
  
  /**
   * @short Algorithms on graphs.  
   * 
   * They use the Fast Interface defined in the Graph objects.
   * Consequently, they are to be called with node ids instead of
   * actual nodes.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: GraphAlgo.h,v 1.4 2004-04-06 21:08:34 larosem Exp $
   */
  class GraphAlgo 
  {
   
  public:

    
    /**
     * Algorithm for determining the shortest path between two nodes
     * in a directed graph.
     * @param graph a graph.
     * @param source the start node id of the path.
     * @param dest the end node id of the path. 
     * @return a Path of object that represents the path.
     */
    template< class node_type, 
	      class edge_type,
	      class node_comparator > 
    static Path< int, float > 
    shortestPath(AbstractGraph< node_type, edge_type, node_comparator > &graph,
		 int source, int dest)
    {
      vector< Path< int, float > > paths;     
      shortestPath (graph, source, paths);
      return paths[dest];
    }




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
    template< class node_type, 
	      class edge_type,
	      class node_comparator,
	      class value_type >
    static void 
    shortestPath (AbstractGraph< node_type, edge_type, node_comparator > &graph,
		  int source,
		  vector< Path< int, value_type > > &paths)
    {
      const value_type MAXVALUE = numeric_limits< value_type >::max ();
      unsigned int w;
      unsigned int graphsize;
      vector< unsigned int > C;
      
      graphsize = graph.size ();
      paths.clear ();
      paths.resize (graphsize);
      
      // Initialize ---
      for  (w = 0; w < graphsize; ++w)
	{
	  value_type value;
	  
	  if  (w == (unsigned int) source)
	    value = 0;
	  else
	    {
	      C.push_back (w);
	      if  (graph.internalAreConnected (source, w))
		{
		  value = graph.internalGetWeight (source, w);
		  paths[w].push_back (source); 
		  paths[w].push_back (w);
		}
	      else
		value = MAXVALUE;
	    }
	  paths[w].setValue (value);
	}
      
      while (! C.empty ())
	{
	  vector< unsigned int >::iterator min_iter;
	  vector< unsigned int >::iterator k;
	  value_type min_value;
	  unsigned int min_index;

	  min_iter = C.begin ();
	  min_value = paths[*min_iter].getValue ();
	  
	  for  (k = C.begin (); k != C.end (); ++k)
	    {
	      if  (paths[*k].getValue () < min_value)
		{
		  min_value = paths[*k].getValue ();
		  min_iter = k;
		}
	    }
	  w = *min_iter;
	  C.erase (min_iter);
	  
	  if  (min_value == MAXVALUE)
	    break; // in case there is no better element...
	  
	  for (k = C.begin (); C.end () != k; ++k)
	    {
	      value_type new_val;
	      unsigned int v;

	      v = *k;
	      if (graph.internalAreConnected (w, v)
		  && paths[v].getValue () > (new_val = min_value + graph.internalGetWeight (w, v)))
		{
		  paths[v] = paths[w];
		  paths[v].push_back (v);
		  paths[v].setValue (new_val);
		}
	    }
	}
    }


    
    /**
     * Prim's algorithm for the minimum spanning tree.
     * @param graph an undirected graph
     * @param edge_nodes a vector of pairs of node ids.
     * @return a vector of edges representing a spanning tree of the graph.
     */
    template< class node_type, 
	      class edge_type,
	      class node_comparator >
    static void 
    minimumSpanningTree (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph,
			 vector< pair< int, int > > &edge_nodes) 
    {
      typedef float value_type;
      value_type MAXVALUE = MAXFLOAT;
      
      vector< int > nearest (graph.size (), -1);
      vector< value_type > mindist (graph.size (), MAXVALUE);
      int i, j;
      
      // Initialize
      for (i=1; i<(int)graph.size (); ++i) {
	nearest[i] = 0;
	mindist[i] = graph.internalAreConnected (i, 0) ? graph.internalGetWeight (i, 0) : MAXVALUE;
      }
      edge_nodes.clear ();
  
    // Execute
      for (i=0; i<(int)graph.size ()-1; ++i) {
	value_type min = MAXVALUE;
	int k = -1;
	for (j=1; j<(int)graph.size (); ++j) {
	  if (mindist[j] >= 0 && mindist[j]<min) {
	    min = mindist[j];
	    k = j;
	  }
	}
	
	// This is a test to see if we stay in the same connected component
	if (k!=-1) 
	  {  
	    edge_nodes.push_back (make_pair (nearest[k], k));	    
	    mindist[k] = -1;
	    
	    for (j=1; j<(int)graph.size (); ++j) {
	      value_type val = 
		graph.internalAreConnected (j, k) ? 
		graph.internalGetWeight (j, k) : 
		MAXVALUE;
	      if (val < mindist[j]) {
		mindist[j] = val;
		nearest[j] = k;
	      }
	    }
	  }
      }
    }
    


    /**
     * Horton's algorithm for the minimum cycle basis.
     * @param graph an UndirectedAbstractGraph.
     * @param searchType (0 = minimum cycle basis, 1 = union of minimum cycle basis, 2 = minimum cycles)
     * @return cycles.
     */
    template< class node_type,
	      class edge_type,
	      class node_comparator,
	      class value_type >
    static vector< Path< int, value_type > > 
    cycleBaseHorton (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, int searchType = 0)
    {
      vector< Path< int, value_type > > bag;
      typename vector< Path< int, value_type > >::iterator p;
      int i;
      typename vector< vector< Path< int, value_type > > >::iterator ii;
      const map< int, pair< int, int > > &edgesCoordinates = graph.getInternalEdgeCoordinateMap ();
      map< int, pair< int, int > >::const_iterator ecIt;
//       set< Path< int, value_type >, lessPath< value_type > > uniquePaths;
      set< Path< int, value_type > > uniquePaths;
      
      for (i = 0; i < graph.size (); ++i)
	{
	  vector< Path< int, value_type > > tmp;
	  
	  shortestPath (graph, i, tmp);
	  for (ecIt = edgesCoordinates.begin (); edgesCoordinates.end () != ecIt; ++ecIt)
	    {
	      int j;
	      int k;
	      
	      j = ecIt->second.first;
	      k = ecIt->second.second;
	      // if P(v,x) ^ P(v,y) = {v}
	      if (++(tmp[j].begin ()) != ++(tmp[k].begin ()))
		{
		  Path< int, value_type > Pvx = tmp[j];
		  Path< int, value_type > Pvy = tmp[k];
		  Path< int, value_type > Pvxp = Pvx; 
		  Path< int, value_type > Pvyp = Pvy; 
		  Path< int, value_type > inter;
		  
		  std::sort (Pvxp.begin (), Pvxp.end ());
		  std::sort (Pvyp.begin (), Pvyp.end ());
		  set_intersection (Pvxp.begin (), Pvxp.end (),
				    Pvyp.begin (), Pvyp.end (),
				    inserter (inter, inter.begin ()));
		  
		  if (inter.size () == 1 && inter.front () == i)
		    {
		      Path< int, value_type > C = Pvx;
		      
		      C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
		      C.pop_back ();
		      C.setValue (Pvx.getValue () + Pvy.getValue () + 1);

		      Path< int, value_type > key = C;
		      std::sort (key.begin (), key.end ());
		      if (uniquePaths.end () == uniquePaths.find (key))
			{
			  uniquePaths.insert (key);
			  bag.push_back (C);
			}
		    }
		}
	    }
	}
      
      sort (bag.begin (), bag.end ());
      
      gOut (3) << "Found " << bag.size () << " potential cycles before elimination" << endl;
      
      if (searchType == 2)
	{
	  nonSimpleCycleElimination (graph, bag);
	}
      else
	{
	  bag = gaussianElimination (graph, bag, searchType);
	}
      
      gOut (3) << "Found " << bag.size () << " cycles." << endl;
      
      return bag;
    }
  

    /**
     * Eliminates the non simple cycles from the set of enumerated cycles.
     * @param graph an UndirectedAbstractGraph.
     * @param bag a vector of cycles.
     * @return a vector of minimum cycles cycles.
     */
    template< class node_type, 
	      class edge_type,
	      class node_comparator,
	      class value_type >
    static void
    nonSimpleCycleElimination (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, vector< Path< int, value_type > > &bag)
    {
      typename vector< Path< int, value_type > >::iterator bagIt;

      for (bagIt = bag.begin (); bag.end () != bagIt; )
	{
	  Path< int, value_type > &path = *bagIt;
	  typename Path< int, value_type >::iterator pathIt;
	  unsigned int edgeCount;
	  const unsigned int cycleSize = path.size ();
	  typename Path< int, value_type >::iterator pathIt2;

	  edgeCount = 0;
	  for (pathIt = path.begin (); path.end () != pathIt; ++pathIt)
	    {
	      for (++pathIt2 = pathIt; path.end () != pathIt2; ++pathIt2)
		{
		  if (graph.internalAreConnected (*pathIt, *pathIt2))
		    {
		      if (cycleSize < ++edgeCount)
			break;
		    }
		}
	      if (path.end () != pathIt2)
		break;
	    }
	  if (path.end () != pathIt2)
	    bagIt = bag.erase (bagIt);
	  else
	    ++bagIt;
	}
    }
    
  
    /**
     * Uses the Gaussian Elimination algorithm to find non linearly
     * dependant cycles from the set of enumerated cycles.
     * @param graph an UndirectedAbstractGraph.
     * @param bag a vector of cycles.
     * @param minBasisUnion whether or not we want a single basis (true for union)
     * @return a linearly independant vector of cycles.
     */
    template< class node_type, 
	      class edge_type,
	      class node_comparator,
	      class value_type >
    static vector< Path< int, value_type > >
    gaussianElimination (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph,
			 vector< Path< int, value_type > >& bag, bool minBasisUnion)
    {
      typedef typename vector< Path< int, value_type > >::iterator vpiterator;
    
      if (bag.size () == 0) return bag;
    
      vector< bool* > matrix;
      vector< bool* >::iterator n;

      int i, j;
      vector< Path< int, value_type > > newbag;
      vpiterator p, q;

      vector< vpiterator > marked;
      marked.clear ();

      bool* row = new bool[graph.edgeSize ()];    

      for (p=bag.begin (); p!=bag.end (); ++p) {
	memset (row, false, graph.edgeSize () * sizeof (bool));
      
	// Let's see if *p is linearly independent to the content of newbag 
	//       cout << "Treating " << *p << endl;
      
	typename Path< int, value_type >::iterator r, s;
	for (r=p->begin (), s=r, ++s; r!=p->end (); ++r, ++s) {
	  if (s==p->end ()) row[graph.internalGetEdge(*r, *p->begin ())] = true;
	  else row[graph.internalGetEdge(*r, *s)] = true;
	}
                 
	bool inserted = false;

	for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
	  // 	cout << "row " << flush;
	  // 	for (j=0; j<edgeSize (); ++j) { cout << row[j] << " "; } 
	  // 	cout << endl << "nj  " << flush; 
	  // 	for (j=0; j<edgeSize (); ++j) { cout << (*n)[j] << " "; } cout << endl;
	
	  j=0;
	  while (j<(int)graph.edgeSize () && row[j] == false && (*n)[j] == false) ++j;
	  if (j == (int)graph.edgeSize ()) continue;
	
	  if (row[j] == true && (*n)[j] == false) {
	    // 	  cout << "Marking " << *p << endl;
	    marked.push_back (p);
	    inserted = true;
	    break;
	  }
	
	  if (row[j] == true && (*n)[j] == true) {
	    //Reduce the current
	    for (i=0; i<(int)graph.edgeSize (); ++i) {
	      row[i] = (row[i] + (*n)[i])%2;
	    }
	    continue;
	  }
	}
      
	if (!inserted) {
	  for (j=0; j<(int)graph.edgeSize (); ++j) {
	    if (row[j] == true) break;
	  }
	  if (j!=(int)graph.edgeSize ()) {
	    // 	  cout << "Marking " << *p << endl;
	    marked.push_back (p);
	  } else {
	    // 	  cout << "Rejecting " << *p << endl;
	  }
	}
    
	//Let's see if we should try to insert the marked...
	if (p+1==bag.end () || (p+1)->size () > p->size ()) {
	  // 	cout << endl << "Inserting marked cycles (" << marked.size () << ")" << endl << endl;

	  for (i=0; i<(int)marked.size (); ++i) {
	    bool* row2 = new bool[graph.edgeSize ()];	  
	    memset (row2, false, graph.edgeSize () * sizeof (bool));
	  
	    typename Path< int, value_type >::iterator r, s;
	    for (r=marked[i]->begin (), s=r, ++s; r!=marked[i]->end (); ++r, ++s) {
	      if (s==marked[i]->end ()) row2[graph.internalGetEdge(*r, *marked[i]->begin ())] = true;
	      else row2[graph.internalGetEdge (*r, *s)] = true;
	    }
	    inserted = false;	
	    for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
	      j=0;    
	      while (j<(int)graph.edgeSize () && row2[j] == false && (*n)[j] == false) ++j;
	      if (j == (int)graph.edgeSize ()) continue;
	    
	      if (row2[j] == true && (*n)[j] == false) {
		// 	      cout << "Inserting " << *marked[i] << endl;
		matrix.insert (n, row2);
		newbag.insert (q, *marked[i]);
		inserted = true;
		break;
	      }
	    
	      if (row2[j] == true && (*n)[j] == true) {
		//Reduce the current
		for (int k=0; k<(int)graph.edgeSize (); ++k) {
		  row2[k] = (row2[k] + (*n)[k])%2;
		}
		continue;
	      }
	    }
	  
	    if (!inserted) {
	      if (minBasisUnion) {
		//  	      cout << "Accepting " << *marked[i] << endl;
		matrix.push_back (row2);
		newbag.push_back (*marked[i]);
	      } else {	    
		for (j=0; j<(int)graph.edgeSize (); ++j) {
		  if (row2[j] == true) break;
		}
		if (j!=(int)graph.edgeSize ()) {
		  //  		cout << "Accepting " << *marked[i] << endl;
		  matrix.push_back (row2);
		  newbag.push_back (*marked[i]);
		} else {
		  //  		cout << "Rejecting " << *marked[i] << endl;
		  delete[] row2;
		}
	      }
	    }
	  }
	  marked.clear ();
	  // 	cout << "done" << endl;
	}      
      }

      for (n=matrix.begin (); n!=matrix.end (); ++n) {
	delete[] *n;
      }

      delete[] row;

      return newbag;
    }

  };
}

#endif
