//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:30:26 2003
// $Revision: 1.5 $
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
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

#include "Graph.h"
#include "Path.h"

namespace mccore {

/**
 * @short A templated undirected graph class.  It is implemented using
 * the directed graph base class and by using a triangular matrix and
 * a node ordering determined by the node_comparator function object.
 *
 * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
 * @version $Id: UndirectedGraph.h,v 1.5 2003-07-08 20:01:44 gendrop Exp $
 */
template< class node_type, 
	  class edge_type = bool, 
	  class node_comparator = less< node_type > >
class UndirectedGraph : public Graph< node_type, edge_type, node_comparator >
{
  

  // LIFECYCLE ------------------------------------------------------------


public:

  /**
   * Initializes the object.
   */
  UndirectedGraph () : Graph< node_type, edge_type, node_comparator > () {}


  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  UndirectedGraph (const UndirectedGraph &other) 
    : Graph< node_type, edge_type, node_comparator > (other) {}


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
      Graph< node_type, edge_type, node_comparator >::operator= (other);      
    }
    return *this;
  }


  // ACCESS ---------------------------------------------------------------


  /**
   * Sets the weight of this node.
   * @param n the node.
   * @return the weight.
   */
  virtual void setWeight (const node_type& n, float w)
  {
    assert (contains (n));
    nodeWeights.find (nodeToPtr (n))->second = w;
  }
  
  
  /**
   * Gets the weight of this node.
   * @param n the node.
   * @return the weight.
   */
  virtual float getWeight (const node_type& n) const 
  {
    assert (contains (n));
    return nodeWeights.find (nodeToPtr (n))->second;
  }
  

  /**
   * Gets the weight of this edge.
   * @param o the origin node.
   * @param p the destination node.
   * @return the weight.
   */
  virtual float getWeight (const node_type& o, const node_type& p) const {
    assert (areConnected (o, p));
    if (node_comparator () (o, p)) {
      return edgeWeights.find(nodeToPtr (o))->second.find (nodeToPtr (p))->second;
    } else {
      return edgeWeights.find(nodeToPtr (p))->second.find (nodeToPtr (o))->second;
    }
  }
  

  /**
     * Gets the edge that exists between nodes o and p.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the edge.
     */
  virtual const edge_type& getEdge (const node_type& o, const node_type& p) const {
    assert (areConnected (o, p));
    if (node_comparator () (o, p)) {
      return *graph.find(nodeToPtr (o))->second.find (nodeToPtr (p))->second;
    } else {
      return *graph.find(nodeToPtr (p))->second.find (nodeToPtr (o))->second;
    }
  }


  // METHODS --------------------------------------------------------------

  
  
  // GRAPH RELATED METHODS ------------------------------------------------

  
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
    const edge_type* ep = &edges.back ();
    
    if (node_comparator () (o, p)) {
      graph[nodeToPtr (o)][nodeToPtr (p)] = ep;
      edgeWeights[nodeToPtr (o)][nodeToPtr (p)] = w;
    } else {
      graph[nodeToPtr (p)][nodeToPtr (o)] = ep;
      edgeWeights[nodeToPtr (p)][nodeToPtr (o)] = w;
    }
  
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

    const edge_type* ep = &getEdge (o, p);

    if (node_comparator () (o, p)) {
      graph.find (nodeToPtr (o))->second.erase (nodeToPtr (p));
      edgeWeights.find (nodeToPtr (o))->second.erase (nodeToPtr (p));
    } else {
      graph.find (nodeToPtr (p))->second.erase (nodeToPtr (o));
      edgeWeights.find (nodeToPtr (p))->second.erase (nodeToPtr (o));
    }

    typename list< edge_type >::iterator i;
    for (i=edges.begin (); i!=edges.end (); ++i) {
      if (&*i == ep) break;
    }
    if (i!=edges.end ())
      edges.erase (i);

    return true;
  }

  
  /**
   * Returns true if there exists an edge between o and p.
   * @param o an extremity of the edge.
   * @param p an extremity of the edge.
   * @return true if there exists an edge between o and p.
   */
  virtual bool areConnected (const node_type &o, const node_type &p) const 
  {
    if (!contains (o) || !contains (p)) return false;
    
    return (graph.find (nodeToPtr (o))->second.find (nodeToPtr (p)) != graph.find (nodeToPtr (o))->second.end () ||
	    graph.find (nodeToPtr (p))->second.find (nodeToPtr (o)) != graph.find (nodeToPtr (p))->second.end ());
  }
  
  
  /**
   * Returns the neighbors of the given node.
   * @param o a node in the graph.
   * @return the list of neighbors.
   */
  virtual list< node_type > getNeighbors (const node_type& o) const
  {
    list< node_type > n;

    typename UndirectedGraph::const_iterator i;

    if (!contains (o)) return n;
    
    for (i=begin (); i!=end (); ++i) {
      if (areConnected (o, *i))
	n.push_back (*i);
    }
    return n;
  }

  /**
   * Prim's algorithm for the minimum spanning tree.
   * @return a vector of edges representing a spanning tree of this graph.
   */
  vector< pair< node_type, node_type > > minimumSpanningTree () {
    typedef float value_type;
    value_type MAXVALUE = MAXFLOAT;

    map< const node_type*, const node_type* > nearest;
    map< const node_type*, value_type > mindist;
    typename map< const node_type*, value_type >::iterator k;
    vector< pair< node_type, node_type > > edgeNodes;
    typename UndirectedGraph::const_iterator i;
    int j;

    // Initialize
    for (i=begin (); i!=end (); ++i) {
      if (&*i == &*begin ()) {
	nearest[&*i] = 0;
	mindist[&*i] = MAXVALUE;
      } else {
	nearest[&*i] = &*begin();
	mindist[&*i] = areConnected (*i, *begin()) ? getWeight (*i, *begin()) : MAXVALUE;
      }    
    }

    // Execute
    for (j=0; j<size ()-1; ++j) {
      value_type min = MAXVALUE;
      const node_type* minNode = 0;
      typename map< const node_type*, float >::iterator x;
      for (x=mindist.begin (); x!= mindist.end (); ++x) {
	if (x->second >= 0 && x->second < min) {
	  min = x->second;
	  minNode = x->first;
	}
      }

      // This is a test to see if we stay in the same connected component
      if (minNode != 0) {
	edgeNodes.push_back (make_pair(*nearest[minNode], *minNode));

	mindist[&*minNode] = -1;

	for (k=mindist.begin (), ++k; k!=mindist.end (); ++k) {
	  const node_type* kp = k->first;
	  value_type v = areConnected (*kp, *minNode) ? getWeight (*kp, *minNode) : MAXVALUE;
	  if (v < k->second) {
	    mindist[&*kp] = v;
	    nearest[&*kp] = minNode;
	  }
	}
      }      
    }

    return edgeNodes;
  }


  /**
   * Horton's algorithm for the minimum cycle basis.
   */
  vector< Path< node_type, float > > cycleBase () { return cycleBaseHorton (); }
  vector< Path< node_type, float > > cycleBaseUnion () { return cycleBaseHorton (true); }

  
private:

  
  vector< Path< node_type, float > > cycleBaseHorton (bool minimum_basis_union = false)
  {
    vector< Path< node_type, float > > realbag;

    vector< Path< const node_type*, float > > bag;
    typename vector< Path< const node_type*, float > >::iterator p;

    typename graph_type::iterator i, j;
    typename adjacency_type::iterator k;

    map< const node_type*, map< const node_type*, Path< const node_type*, float > > > paths;
    typename map< const node_type*, Path< const node_type*, float > >::iterator ii;

    for (i=graph.begin (); i!=graph.end (); ++i) {
      paths[i->first] = shortestPath (*i->first);
      for (ii=paths[i->first].begin (); ii!=paths[i->first].end (); ++ii) {
// 	cout << *i->first << " " << *ii->first << " " << ii->second << endl; 
      }
    }

    for (i=graph.begin (); i!=graph.end (); ++i) {
      for (j=graph.begin (); j!=graph.end (); ++j) {
	for (k=j->second.begin (); k!=j->second.end (); ++k) {

	  //	  cout << "Step: " << i->first << " " << j->first << " " << k->first << endl;
	 
	  Path< const node_type*, float > Pvx = paths[i->first][j->first];	  
	  Path< const node_type*, float > Pvy = paths[i->first][k->first];

	  // if P(v,x) ^ P(v,y) = {v}
	  
	  Path< const node_type*, float > Pvxp = Pvx; 
	  Pvxp.sort ();
	  Path< const node_type*, float > Pvyp = Pvy; 
	  Pvyp.sort ();
	  
	  Path< const node_type*, float > inter;
	  set_intersection (Pvxp.begin (), Pvxp.end (),
			    Pvyp.begin (), Pvyp.end (),
			    inserter (inter, inter.begin ()));

	  //cout << "Inter = " << inter << endl;

	  if (inter.size () == 1 && inter.front () == i->first) {
	    Path< const node_type*, float > C = Pvx;
	    C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
	    C.pop_back ();
	    C.setValue (Pvx.getValue () + Pvy.getValue () + 1);
	    
	    for (p=bag.begin (); p!=bag.end (); ++p) {
	      if (*p == C) {
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

    bag = gaussianElimination (bag, minimum_basis_union);

    typename Path< const node_type*, float >::iterator pi;

    for (p=bag.begin (); p!=bag.end (); ++p) {
      Path< node_type, float > aPath;
      for (pi=p->begin (); pi!=p->end (); ++pi) {
	aPath.push_back (**pi);
      }
      aPath.setValue (p->getValue ());
      realbag.push_back (aPath);      
    }

    return realbag;
  }


  
  vector< Path< const node_type*, float > > 
  gaussianElimination (vector< Path< const node_type*, float > >& bag, bool minBasisUnion)
  {
    typedef typename vector< Path< const node_type*, float > >::iterator vpiterator;

    if (bag.size () == 0) return bag;
    
    vector< bool* > matrix;
    vector< bool* >::iterator n;

    int i, j;
    vector< Path< const node_type*, float > > newbag;
    vpiterator p, q;

    vector< vpiterator > marked;
    marked.clear ();


//     // Should be done otherwise...  We need an efficient way to get
//     // the index of an edge in the graph...

    int edgesize = 0;
    map< const edge_type*, int > edgeid; 
    typename list< edge_type >::const_iterator l;
    for (l=edges.begin (); l!=edges.end (); ++l) {
      edgeid[&*l] = edgesize++;
    }    
    
    for (p=bag.begin (); p!=bag.end (); ++p) {
      bool* row = new bool[edgesize];
      memset (row, false, edgesize * sizeof (bool));
      
//       cout << "Treating " << *p << endl;
      
      typename Path< const node_type*, float >::iterator r, s;
      for (r=p->begin (), s=r, ++s; r!=p->end (); ++r, ++s) {
	if (s==p->end ()) row[edgeid[&getEdge(**r, **p->begin ())]] = true;
	else row[edgeid[&getEdge(**r, **s)]] = true;
      }
                 
      bool inserted = false;

      for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
// 	for (j=0; j<edgesize; ++j) { cout << row[j] << " "; } 
// 	cout << "  ->  " << flush; 
// 	for (j=0; j<edgesize; ++j) { cout << (*n)[j] << " "; } cout << endl;
	
	j=0;
	while (j<edgesize && row[j] == false && (*n)[j] == false) ++j;
	if (j == edgesize) continue;
	
	if (row[j] == true && (*n)[j] == false) {
// 	  cout << "Marking " << *p << endl;
	  marked.push_back (p);
	  inserted = true;
	  break;
	}
	
	if (row[j] == true && (*n)[j] == true) {
	  //Reduce the current
	  for (i=0; i<edgesize; ++i) {
	    row[i] = (row[i] + (*n)[i])%2;
	  }
	  continue;
	}
      }
      
      if (!inserted) {
	for (j=0; j<edgesize; ++j) {
	  if (row[j] == true) break;
	}
	if (j!=edgesize) {
// 	  cout << "Marking " << *p << endl;
	  marked.push_back (p);
	} else {
// 	  cout << "Rejecting " << *p << endl;
	}
      }
      
      delete[] row;

      //Let's see if we should try to insert the marked...
      if (p+1==bag.end () || (p+1)->size () > p->size ()) {
// 	cout << "Inserting marked cycles" << endl;

	for (i=0; i<(int)marked.size (); ++i) {
	  bool* row = new bool[edgesize];
	  memset (row, false, edgesize * sizeof (bool));
	  
	  typename Path< const node_type*, float >::iterator r, s;
	  for (r=marked[i]->begin (), s=r, ++s; r!=marked[i]->end (); ++r, ++s) {
	    if (s==marked[i]->end ()) row[edgeid[&getEdge(**r, **marked[i]->begin ())]] = true;
	    else row[edgeid[&getEdge(**r, **s)]] = true;
	  }

// 	  cout << "Treating " << *marked[i] << endl;	
	  
	  inserted = false;
	
	  for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
	    j=0;    
	    while (j<edgesize && row[j] == false && (*n)[j] == false) ++j;
	    if (j == edgesize) continue;
	    
	    if (row[j] == true && (*n)[j] == false) {
// 	      cout << "Inserting " << *marked[i] << endl;
	      matrix.insert (n, row);
	      newbag.insert (q, *marked[i]);
	      inserted = true;
	      break;
	    }
	    
	    if (row[j] == true && (*n)[j] == true) {
	      //Reduce the current
	      for (int k=0; k<edgesize; ++k) {
		row[k] = (row[k] + (*n)[k])%2;
	      }
	      continue;
	    }
	  }
	  
	  if (!inserted) {
	    if (minBasisUnion) {
// 	      cout << "Accepting " << *marked[i] << endl;
	      matrix.push_back (row);
	      newbag.push_back (*marked[i]);
	    } else {	    
	      for (j=0; j<edgesize; ++j) {
		if (row[j] == true) break;
	      }
	      if (j!=edgesize) {
// 		cout << "Accepting " << *marked[i] << endl;
		matrix.push_back (row);
		newbag.push_back (*marked[i]);
	      } else {
// 		cout << "Rejecting " << *marked[i] << endl;
	      }
	    }	
	  }
	}
	marked.clear ();
      }      
    }
    
    return newbag;
  }
  

  // I/O  -----------------------------------------------------------------


public:


  virtual ostream& output (ostream& os) const
  {
    typename UndirectedGraph::const_iterator ki, kj;
    
    for (ki=begin (); ki!=end (); ++ki) {      
      os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
      for (kj=begin (); kj!=end (); ++kj) {
    	if (areConnected (*ki, *kj)) 
	  os << *kj << "(" << getEdge (*ki, *kj) << ") ";
      }
      os << endl;
    }
    
    for (ki=begin (); ki!=end (); ++ki) {     
      if (ki!=begin ()) os << endl;
      os << *ki << " ";      
      for (kj=begin (); kj!=end (); ++kj) {
    	if (areConnected (*ki, *kj)) os << "x ";
    	else os << "- ";	
      }
    }
    
    return os;
  }
};

}

#endif
