//                              -*- Mode: C++ -*- 
// GraphAlgo.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Dec  5 16:47:26 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Fri Jan  9 15:08:31 2004
// Update Count     : 50
// Status           : Unknown.
// 

#ifndef _GraphAlgo_h_
#define _GraphAlgo_h_


#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

#include "AbstractGraph.h"
#include "Path.h"

using namespace std;

#ifndef HAVE_NUMERIC_LIMITS
#include <values.h>
#else
#define MAXFLOAT numeric_limits< float > ().max ()
#define MAXINT numeric_limits< int > ().max ()
#endif


namespace mccore {

  /**
   * @short Algorithms on graphs.  
   * 
   * They use the Fast Interface defined in the Graph objects.
   * Consequently, they are to be called with node ids instead of
   * actual nodes.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: GraphAlgo.h,v 1.1 2004-01-09 20:09:44 gendrop Exp $
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
     * NOTE: value_type must be a float since we still use gcc-2.95.3
     * and we can't know the MAX_VALUE of types at runtime.  and it
     * doesn't implement numeric_limits<T> 
     * @param graph a graph.
     * @param source the source node id of the paths.
     * @return a map of nodes with their paths from the source.
     */
    template< class node_type, 
	      class edge_type,
	      class node_comparator >
    static void 
    shortestPath (AbstractGraph< node_type, edge_type, node_comparator > &graph,
		  int source, vector< Path< int, float > > &paths)
    {      
      typedef float value_type;
      value_type MAXVALUE = MAXFLOAT;  

      int i;
      int graphsize = graph.size ();
      paths.clear ();
      paths.resize (graphsize);                     // path description  
      vector< int > C;                              // node set
      vector< int >::iterator k;
      
      // Initialize ---
      for  (i=0; i<graphsize; i++) {
	if  (i == source) { 
	  paths[i].setValue (0);
	} else { 
	  C.push_back (i);
	  if  (graph.internalAreConnected(source, i)) {
	    paths[i].setValue (graph.internalGetWeight (source, i));	 
	    paths[i].push_back (source); 
	    paths[i].push_back (i);
	  } else {
	    paths[i].setValue (MAXVALUE);
	  }
	}
      }
    
      for  (i=0; i<graphsize-2; i++) {
	vector< int >::iterator min_iter = C.begin();
	value_type min_value = paths[*min_iter].getValue (); // in C
	int min_index;
	
	for  (k=C.begin(); k!=C.end(); k++) {
	  if  (paths[*k].getValue () < min_value) {
	    min_value = paths[*k].getValue ();
	    min_iter = k;
	  } 
	}
	min_index = *min_iter;
	C.erase (min_iter);
	
	if  (min_value == MAXVALUE) break; // in case there is no better element...
	
	for (k=C.begin(); k!=C.end(); k++) {
	  value_type old_val = paths[*k].getValue ();
	  value_type new_val;
	  if (graph.internalAreConnected (min_index, *k))
	    new_val = min_value + graph.internalGetWeight (min_index, *k);
	  else 
	    new_val = MAXVALUE;
	  if  (old_val > new_val) {
	    paths[*k] = paths[ min_index ];
	    paths[*k].push_back (*k);
	    paths[*k].setValue (new_val);
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
	      class node_comparator >
    static vector< Path< int, float > > 
    cycleBaseHorton (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph,
		     int searchType = 0)
    {
      vector< Path< int, float > > bag;
      vector< Path< int, float > >::iterator p;
      int i, j;
      
      vector< vector< Path< int, float > > > paths;
      vector< vector< Path< int, float > > >::iterator ii;
      
      for (i=0; i<graph.size (); ++i) {
	vector< Path< int, float > > tmp;
	shortestPath (graph, i, tmp);
	paths.push_back (tmp);
      }
        
      for (i=0; i<graph.size (); ++i) {
	//       cout << "Step: " << i << endl;
      
	for (j=0; j!=graph.size (); ++j) {
	  list< int > ln = graph.internalGetNeighbors (j);
	  list< int >::iterator k;
	  for (k=ln.begin (); k!=ln.end (); ++k) {
	  
	    // 	  cout << "Step: " << i << " (" << j << " " << *k << ")" << endl;
	  
	    Path< int, float > Pvx = paths[i][j];	  
	    Path< int, float > Pvy = paths[i][*k];

	    // if P(v,x) ^ P(v,y) = {v}
	  
	    Path< int, float > Pvxp = Pvx; 
	    Pvxp.sort ();
	    Path< int, float > Pvyp = Pvy; 
	    Pvyp.sort ();
	  
	    Path< int, float > inter;
	    set_intersection (Pvxp.begin (), Pvxp.end (),
			      Pvyp.begin (), Pvyp.end (),
			      inserter (inter, inter.begin ()));

	    // 	  cout << "Inter = " << inter << endl;

	    if (inter.size () == 1 && inter.front () == i) {
	      Path< int, float > C = Pvx;
	      C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
	      C.pop_back ();
	      C.setValue (Pvx.getValue () + Pvy.getValue () + 1);
	    
	      for (p=bag.begin (); p!=bag.end (); ++p) {
		if (*p == C) {  // Redundancy test
		  break;
		}
	      }
	      if (p==bag.end ()) {
		bag.push_back (C);
		// 	      cout << "Inserting " << C << endl;
	      }
	    }
	  }	  
	}
      }
    
      sort (bag.begin (), bag.end ());

      cout << "Found " << bag.size () << " potential cycles before the Gaussian elimination" << endl;

      if (searchType == 2)
	bag = nonSimpleCycleElimination (graph, bag);
      else
	bag = gaussianElimination (graph, bag, searchType);    
      
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
    static vector< Path< int, float > >
    nonSimpleCycleElimination (UndirectedAbstractGraph< node_type, edge_type, node_comparator > &graph,
			       vector< Path< int, float > >& bag)
    {
      vector< Path< int, float > > newbag;
      vector< Path< int, float > >::iterator p;
      Path< int, float >::iterator i, j, k, l, m;

    
      for (p=bag.begin (); p!=bag.end (); ++p) {
	for (i=p->begin (); i!=p->end (); ++i) {
	  for (j=p->begin (); j!=p->end (); ++j) {
	    k = l = j;
	    m = i;
	    if (j!=i && (++k)!=i && (--l)!=i && 
		!(i==p->begin () && k==p->end ()) &&
		!(j==p->begin () && (++m)==p->end ()) &&
		graph.internalAreConnected (*i, *j))
	      break;
	  }
	  if (j!=p->end ()) break;
	}
	if (i==p->end ())
	  newbag.push_back (*p);
      }
      return newbag;
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
