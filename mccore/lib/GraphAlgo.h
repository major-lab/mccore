//                              -*- Mode: C++ -*- 
// GraphAlgo.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 16:47:26 2003
// Last Modified By : Martin Larose
// Last Modified On : Fri Apr  2 14:11:17 2004
// Update Count     : 52
// Status           : Unknown.
// 

#ifndef _GraphAlgo_h_
#define _GraphAlgo_h_


#include <assert.h>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

#include "AbstractGraph.h"
#include "Path.h"

using namespace std;

#define MAXFLOAT numeric_limits< float > ().max ()



namespace mccore {

  /**
   * @short Algorithms on graphs.  
   * 
   * They use the Fast Interface defined in the Graph objects.
   * Consequently, they are to be called with node ids instead of
   * actual nodes.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: GraphAlgo.h,v 1.3 2004-04-02 18:59:20 larosem Exp $
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
    template< class node_type, class edge_type, class node_comparator >
    static vector< Path< int, float > > 
    cycleBaseHorton (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, int searchType = 0)
    {
      vector< Path< int, float > > bag;
      vector< Path< int, float > >::iterator p;
      int i, j;
      vector< vector< Path< int, float > > >::iterator ii;
      
      for (i=0; i<graph.size (); ++i) {
	vector< Path< int, float > > tmp;
	
	shortestPath (graph, i, tmp);
	for (j=0; j!=graph.size (); ++j)
	  {
	    list< int > ln = graph.internalGetNeighbors (j);
	    list< int >::iterator k;
	    
	    for (k=ln.begin (); k!=ln.end (); ++k)
	      {
		// if P(v,x) ^ P(v,y) = {v}
		Path< int, float > Pvx = tmp[j];
		Path< int, float > Pvy = tmp[*k];
		Path< int, float > Pvxp = Pvx; 
		Path< int, float > Pvyp = Pvy; 
		Path< int, float > inter;
		
		Pvxp.sort ();
		Pvyp.sort ();
		set_intersection (Pvxp.begin (), Pvxp.end (),
				  Pvyp.begin (), Pvyp.end (),
				  inserter (inter, inter.begin ()));
		
		// 	  cout << "Inter = " << inter << endl;
		
		if (inter.size () == 1 && inter.front () == i)
		  {
		    Path< int, float > C = Pvx;
		    
		    C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
		    C.pop_back ();
		    C.setValue (Pvx.getValue () + Pvy.getValue () + 1);
		    
		    for (p=bag.begin (); p!=bag.end (); ++p)
		      {
			if (*p == C)
			  {  // Redundancy test
			    break;
			  }
		      }
		    if (p==bag.end ())
		      {
			bag.push_back (C);
			// 	      cout << "Inserting " << C << endl;
		      }
		  }
	      }	  
	  }
      }
    
      sort (bag.begin (), bag.end ());
      
      cout << "Found " << bag.size () << " potential cycles before elimination" << endl;
      
      if (searchType == 2)
	// 	bag = nonSimpleCycleElimination (graph, bag);
	nonSimpleCycleElimination (graph, bag);
      else
	bag = gaussianElimination (graph, bag, searchType);    
      
      cout << "Found " << bag.size () << " cycles." << endl;
      
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
	      class node_comparator >
//     static vector< Path< int, float > >
    static void
    nonSimpleCycleElimination (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph, vector< Path< int, float > > &bag)
    {
//       vector< Path< int, float > > newbag;
      vector< Path< int, float > >::iterator p;
      Path< int, float >::iterator i;
      Path< int, float >::iterator j;
      Path< int, float >::iterator k;
      Path< int, float >::iterator l;
      Path< int, float >::iterator m;
    
      for (p = bag.begin (); bag.end () != p;)
	{
	  for (i = p->begin (); i != p->end (); ++i)
	    {
	      for (j = p->begin (); j != p->end (); ++j)
		{
		  k = l = j;
		  m = i;
		  if (j != i
		      && (++k) != i
		      && (--l) != i
		      && ! (i == p->begin () && k == p->end ())
		      && ! (j == p->begin () && (++m) == p->end ())
		      && graph.internalAreConnected (*i, *j))
		    break;
		}
	      if (j != p->end ())
		break;
	    }
// 	  if (i == p->end ())
// 	    newbag.push_back (*p);

	  // too slow, should consider using a list
	  if (p->end () == i)
	    ++p;
	  else
	    p = bag.erase (p);
	}
//       return newbag;
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
	      class node_comparator >
    static vector< Path< int, float > >
    gaussianElimination (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph,
			 vector< Path< int, float > >& bag, bool minBasisUnion)
    {
      typedef vector< Path< int, float > >::iterator vpiterator;
    
      if (bag.size () == 0) return bag;
    
      vector< bool* > matrix;
      vector< bool* >::iterator n;

      int i, j;
      vector< Path< int, float > > newbag;
      vpiterator p, q;

      vector< vpiterator > marked;
      marked.clear ();

      bool* row = new bool[graph.edgeSize ()];    

      for (p=bag.begin (); p!=bag.end (); ++p) {
	memset (row, false, graph.edgeSize () * sizeof (bool));
      
	// Let's see if *p is linearly independent to the content of newbag 
	//       cout << "Treating " << *p << endl;
      
	Path< int, float >::iterator r, s;
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
	  
	    Path< int, float >::iterator r, s;
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
