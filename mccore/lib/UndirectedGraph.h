//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:30:26 2003
// $Revision: 1.8 $
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later vertypename sion.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef _UndirectedGraph_h_
#define _UndirectedGraph_h_

#include <iostream>
#include <map>
#include <algorithm>

#include "AdjacencyMatrix.h"
#include "Path.h"
#include "Graph.h"


namespace mccore {

/**
 * @short A templated undirected graph class.  It is implemented using
 * the directed graph base class and by using a triangular matrix and
 * a node ordering determined by the node_comparator function object.
 *
 * @author Patrick Gendron (gendrop@iro.umontreal.ca)
 * @version $Id: UndirectedGraph.h,v 1.8 2003-10-16 21:57:10 gendrop Exp $
 */
template< class node_type, 
	  class edge_type = bool, 
	  class matrix_type = MapMatrix,
	  class node_comparator = less< node_type > >
class UndirectedGraph : public Graph< node_type, edge_type, matrix_type, node_comparator >
{
  

  // LIFECYCLE ------------------------------------------------------------


public:

  /**
   * Initializes the object.
   */
  UndirectedGraph (int size_hint = 0) 
    : Graph< node_type, edge_type, matrix_type, node_comparator > (size_hint) {}


  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  UndirectedGraph (const UndirectedGraph &other) 
    : Graph< node_type, edge_type, matrix_type, node_comparator > (other) {}


  /**
   * Destroys the object.
   */
  virtual ~UndirectedGraph () {
    clear ();
  }


  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  virtual UndirectedGraph& operator= (const UndirectedGraph &other) {
    if (this != &other) {
      Graph< node_type, edge_type, matrix_type, node_comparator >::operator= (other);      
    }
    return *this;
  }


  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  
  /**
   * Connect two nodes of the graph by a directed edge.
   * @param o a node.
   * @param p another node.
   * @param w the weight of this edge (default=1).
   * @return true if the connect operation succeeded.
   */
  virtual bool connect (const node_type &o, const node_type &p, 
			const edge_type &e = edge_type(), float w = 1) 
  {
    if (!contains (o) || !contains (p)) return false;
    
    edges.push_back (e);
    edgeWeights.push_back (w);

    graph.connect (mapping[o], mapping[p], edges.size ()-1);
    graph.connect (mapping[p], mapping[o], edges.size ()-1);
    
    return true;
  }

  /**
   * Disconnect two nodes of the graph.
   * @param o a node.
   * @param p another node.
   * @return true if the nodes were disconnected.
   */
  virtual bool disconnect (const node_type &o, const node_type &p) 
  {
    if (!contains (o) || !contains (p)) return false;
    if (!areConnected (o, p)) return false;
    
    int e = graph.elem (mapping[o], mapping[p]);
    graph.disconnect (mapping[o], mapping[p]);

    graph.elem (mapping[p], mapping[o]) = -1;

    edges.erase (edges.begin () + e);
    edgeWeights.erase (edgeWeights.begin () + e);
    return true;
  }
  

  /**
   * Prim's algorithm for the minimum spanning tree.
   * @return a vector of edges representing a spanning tree of this graph.
   */
  vector< pair< node_type, node_type > > minimumSpanningTree () 
  {
    typedef float value_type;
    value_type MAXVALUE = MAXFLOAT;

    vector< int > nearest (size (), -1);
    vector< value_type > mindist (size (), MAXVALUE);
    vector< pair< node_type, node_type > > edgeNodes;
    int i, j;

    // Initialize
    for (i=1; i<(int)size (); ++i) {
      nearest[i] = 0;
      mindist[i] = internalGetWeight (i, 0);
    }
    
    // Execute
    for (i=0; i<(int)size ()-1; ++i) {
      value_type min = MAXVALUE;
      int k = -1;
      for (j=1; j<(int)size (); ++j) {
	if (mindist[j] >= 0 && mindist[j]<min) {
	  min = mindist[j];
	  k = j;
	}
      }

      // This is a test to see if we stay in the same connected component
      if (k!=-1) 
	{  
	  edgeNodes.push_back (make_pair (nodes[nearest[k]], nodes[k]));
	  
	  mindist[k] = -1;
	  
	  for (j=1; j<(int)size (); ++j) {
	    value_type val = internalAreConnected (j, k) ? internalGetWeight (j, k) : MAXVALUE;
	    if (val < mindist[j]) {
	      mindist[j] = val;
	    nearest[j] = k;
	    }
	  }
	}
    }
    
    return edgeNodes;
  }


  /**
   * Horton's algorithm for the minimum cycle basis.
   */
  vector< Path< node_type, float > > cycleBase () { return cycleBaseHorton (0); }
  vector< Path< node_type, float > > cycleBaseUnion () { return cycleBaseHorton (1); }
  vector< Path< node_type, float > > minimumCycles () { return cycleBaseHorton (2); }
  
  
private:

  
  vector< Path< node_type, float > > cycleBaseHorton (int searchType = 0)
  {
    vector< Path< node_type, float > > realbag;

    vector< Path< int, float > > bag;
    vector< Path< int, float > >::iterator p;
    int i, j;

    vector< vector< Path< int, float > > > paths;
    vector< vector< Path< int, float > > >::iterator ii;

    for (i=0; i<size (); ++i) {
      vector< Path< int, float > > tmp;
      internalShortestPath (i, tmp);
      paths.push_back (tmp);
    }
    
    
    for (i=0; i<size (); ++i) {
//       cout << "Step: " << i << endl;
      
      for (j=0; j!=size (); ++j) {
	list< int > ln = internalGetNeighbors (j);
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
      bag = nonSimpleCycleElimination (bag);
    else
      bag = gaussianElimination (bag, searchType);    

    Path< int, float >::iterator pi;
    for (p=bag.begin (); p!=bag.end (); ++p) {
      Path< node_type, float > aPath;
      for (pi=p->begin (); pi!=p->end (); ++pi) {
 	aPath.push_back (nodes[*pi]);
      }
      aPath.setValue (p->getValue ());
      realbag.push_back (aPath);      
    }

    return realbag;
  }
  

  vector< Path< int, float > >
  nonSimpleCycleElimination (vector< Path< int, float > >& bag)
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
	      internalAreConnected (*i, *j))
	    break;
	}
	if (j!=p->end ()) break;
      }
      if (i==p->end ())
	newbag.push_back (*p);
    }
    return newbag;
  }

  
  vector< Path< int, float > >
  gaussianElimination (vector< Path< int, float > >& bag, bool minBasisUnion)
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

    bool* row = new bool[edges.size ()];    

    for (p=bag.begin (); p!=bag.end (); ++p) {
      memset (row, false, edges.size () * sizeof (bool));
      
      // Let's see if *p is linearly independent to the content of newbag 
//       cout << "Treating " << *p << endl;
      
      Path< int, float >::iterator r, s;
      for (r=p->begin (), s=r, ++s; r!=p->end (); ++r, ++s) {
	if (s==p->end ()) row[internalGetEdge(*r, *p->begin ())] = true;
	else row[internalGetEdge(*r, *s)] = true;
      }
                 
      bool inserted = false;

      for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
// 	cout << "row " << flush;
// 	for (j=0; j<edges.size (); ++j) { cout << row[j] << " "; } 
// 	cout << endl << "nj  " << flush; 
// 	for (j=0; j<edges.size (); ++j) { cout << (*n)[j] << " "; } cout << endl;
	
	j=0;
	while (j<(int)edges.size () && row[j] == false && (*n)[j] == false) ++j;
	if (j == (int)edges.size ()) continue;
	
	if (row[j] == true && (*n)[j] == false) {
// 	  cout << "Marking " << *p << endl;
	  marked.push_back (p);
	  inserted = true;
	  break;
	}
	
	if (row[j] == true && (*n)[j] == true) {
	  //Reduce the current
	  for (i=0; i<(int)edges.size (); ++i) {
	    row[i] = (row[i] + (*n)[i])%2;
	  }
	  continue;
	}
      }
      
      if (!inserted) {
	for (j=0; j<(int)edges.size (); ++j) {
	  if (row[j] == true) break;
	}
	if (j!=(int)edges.size ()) {
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
	  bool* row2 = new bool[edges.size ()];	  
	  memset (row2, false, edges.size () * sizeof (bool));
	  
	  Path< int, float >::iterator r, s;
	  for (r=marked[i]->begin (), s=r, ++s; r!=marked[i]->end (); ++r, ++s) {
	    if (s==marked[i]->end ()) row2[internalGetEdge(*r, *marked[i]->begin ())] = true;
	    else row2[internalGetEdge (*r, *s)] = true;
	  }
	  inserted = false;	
	  for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
	    j=0;    
	    while (j<(int)edges.size () && row2[j] == false && (*n)[j] == false) ++j;
	    if (j == (int)edges.size ()) continue;
	    
	    if (row2[j] == true && (*n)[j] == false) {
// 	      cout << "Inserting " << *marked[i] << endl;
	      matrix.insert (n, row2);
	      newbag.insert (q, *marked[i]);
	      inserted = true;
	      break;
	    }
	    
	    if (row2[j] == true && (*n)[j] == true) {
	      //Reduce the current
	      for (int k=0; k<(int)edges.size (); ++k) {
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
	      for (j=0; j<(int)edges.size (); ++j) {
		if (row2[j] == true) break;
	      }
	      if (j!=(int)edges.size ()) {
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


  
  

  // I/O  -----------------------------------------------------------------


public:


//   virtual ostream& output (ostream& os) const
//   {
//     typename UndirectedGraph::const_iterator ki, kj;
//     typename vector< node_type >::const_iterator i;
//     typename vector< edge_type >::const_iterator j;

//     os << "Nodes:" << endl;
//     for (i=nodes.begin (); i!=nodes.end (); ++i) {
//       os << i-nodes.begin () << " : " << *i << " " << mapping.find (*i)->second << endl;
//     }
//     os << "Edges:" << endl;
//     for (j=edges.begin (); j!=edges.end (); ++j) {
//       os << j-edges.begin () << " : " << *j << " (" 
// 	 << edgeWeights[j-edges.begin ()] << ")" << endl;
//     }
    
//     os << "Adjacency:" << endl;
//     for (ki=begin (); ki!=end (); ++ki) {      
//       os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
//       for (kj=begin (); kj!=end (); ++kj) {
//     	if (areConnected (*ki, *kj)) 
// 	  os << *kj << "(" << getEdge (*ki, *kj) << ") ";
//       }
//       os << endl;
//     }
    
//     os << graph << endl;
    
//     return os;
//   }

};

}

#endif
