//                              -*- Mode: C++ -*- 
// UndirectedArrayGraph.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:30:26 2003
// $Revision: 1.3 $
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



#ifndef _UndirectedArrayGraph_h_
#define _UndirectedArrayGraph_h_

#include <iostream>
#include <map>
#include <algorithm>

#include "AbstractGraph.h"
#include "ArrayGraph.h"
#include "GraphAlgo.h"
#include "Messagestream.h"
#include "Path.h"



namespace mccore {

  /**
   * @short A templated undirected graph class.  It is implemented using
   * the directed graph base class and by using a triangular matrix and
   * a node ordering determined by the node_comparator function object.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: UndirectedArrayGraph.h,v 1.3 2004-09-02 20:52:37 larosem Exp $
   */
  template< class node_type, 
	    class edge_type = bool, 
	    class node_comparator = less< node_type > >
  class UndirectedArrayGraph : public virtual ArrayGraph< node_type, edge_type, node_comparator >,
			       public virtual UndirectedAbstractGraph< node_type, edge_type, node_comparator >
  {
    
    // TO COMPLETE: Use a symetric triangular array instead of a square.
  

    // LIFECYCLE ------------------------------------------------------------

  public:

    /**
     * Initializes the object.
     */
    UndirectedArrayGraph (int size_hint = 0) 
      : ArrayGraph< node_type, edge_type, node_comparator > (size_hint) 
    {}


    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    UndirectedArrayGraph (const UndirectedArrayGraph &other) 
      : ArrayGraph< node_type, edge_type, node_comparator > (other) {}


    /**
     * Destroys the object.
     */
    virtual ~UndirectedArrayGraph () {
      clear ();
    }


    // OPERATORS ------------------------------------------------------------

  public:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    UndirectedArrayGraph& 
    operator= (const AbstractGraph< node_type, edge_type, node_comparator > &other) {
      if (this != &other) {
	ArrayGraph< node_type, edge_type, node_comparator >::operator= (other);
      }
      return *this;
    }


    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

  public:

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

      graph[index (mapping[o], mapping[p])] = edges.size ()-1;
      graph[index (mapping[p], mapping[o])] = edges.size ()-1;
      edgeCoordinates.insert (make_pair (edges.size () - 1, make_pair (mapping[o], mapping[p])));
    
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
      if (!contains (o)
	  || !contains (p)
	  || !areConnected (o, p))
	return false;
    
      int e = graph[index (mapping[o], mapping[p])];
      map< int, pair< int, int > >::iterator eIt;
      map< int, pair< int, int > >::iterator eIt2;

      graph[index (mapping[o], mapping[p])] = -1;
      graph[index (mapping[p], mapping[o])] = -1;

      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);

      for (int i=0; i<size ()*size (); ++i) {
	if (graph[i] > e) graph[i]--;
      }
      
      eIt = edgeCoordinates.find (e);
      eIt2 = eIt++;
      edgeCoordinates.erase (eIt2);
      while (edgeCoordinates.end () != eIt)
	{
	  edgeCoordinates.insert (make_pair (eIt->first - 1, eIt->second));
	  eIt2 = eIt++;
	  edgeCoordinates.erase (eIt2);
	}
      return true;
    }
  
 
    /**
     * Prim's algorithm for the minimum spanning tree.
     * @return a vector of edges representing a spanning tree of the graph.
     */
    vector< pair< node_type, node_type > > 
    minimumSpanningTree () 
    {
      vector< pair< int, int > > aedges;
      vector< pair< int, int > >::iterator i;
      vector< pair< node_type, node_type > > realedges;

      GraphAlgo::minimumSpanningTree (*this, aedges);

      for (i=aedges.begin (); i!=aedges.end (); ++i) {
	realedges.push_back (make_pair (nodes[i->first],
					nodes[i->second]));
      }
      return realedges;
    }
    
    
    /**
     * Computes a minimum cycle basis for this graph.
     */
    template< class value_type >
    vector< Path< node_type, value_type > > cycleBase ()
    {
      vector< Path< unsigned int, int > > paths;
      vector< Path< unsigned int, int > >::iterator p;
      vector< Path< node_type, value_type > > realpaths;
      
      paths = GraphAlgo::cycleBaseHorton< node_type, edge_type, node_comparator > (*this);
      for (p = paths.begin (); p != paths.end (); ++p)
	{
	  Path< unsigned int, int >::iterator pi;
	  realpaths.push_back (Path< node_type, value_type > ());
	  Path< node_type, value_type > &path = realpaths.back ();
	  
	  for (pi = p->begin (); pi != p->end (); ++pi)
	    path.push_back (nodes[*pi]);
	  path.setValue (p->getValue ());
	}
      return realpaths;
    }

    /**
     * Computes the union of the minimum cycle basis for this graph.
     */
    template< class value_type >
    vector< Path< node_type, value_type > > cycleBaseUnion ()
    {
      vector< Path< unsigned int, int > > paths;
      vector< Path< unsigned int, int > >::iterator p;
      vector< Path< node_type, value_type > > realpaths;
      vector< AbstractGraph< unsigned int, bool, less< unsigned int > >* > digraphs;
      vector< AbstractGraph< unsigned int, bool, less< unsigned int> >* >::iterator diit;
      typename UndirectedArrayGraph< node_type, edge_type, node_comparator>::iterator it;

      for (it = begin (); end () != it; ++it)
	digraphs.push_back (new ArrayGraph< unsigned int, bool, less< unsigned int > > ());
      paths = GraphAlgo::unionMinimumCycleBases< node_type, edge_type, node_comparator > (*this, digraphs);
      
      for (p = paths.begin (); p != paths.end (); ++p)
	{
	  realpaths.push_back (Path< node_type, value_type > ());
	  Path< node_type, value_type > &path = realpaths.back ();
	  Path< unsigned int, int >::iterator pi;
	  
	  for (pi = p->begin (); pi != p->end (); ++pi)
	    path.push_back (nodes[*pi]);
	  path.setValue (p->getValue ());
	}
      for (diit = digraphs.begin (); digraphs.end () != diit; ++diit)
	{
	  gOut (4) << **diit << " ";
	  delete *diit;
	}
      return realpaths;
    }

//     /**
//      * Computes the union of all the minimum cycles for this graph.
//      */
//     template< class value_type >
//     vector< Path< node_type, value_type > > minimumCycles () { 

//       vector< Path< int, value_type > > paths;
//       typename vector< Path< int, value_type > >::iterator p;
//       typename Path< int, value_type >::iterator pi;
//       vector< Path< node_type, value_type > > realpaths;

//       paths = GraphAlgo::cycleBaseHorton< node_type, edge_type, node_comparator, value_type > (*this, 2);
      
//       for (p=paths.begin (); p!=paths.end (); ++p) {
//       	Path< node_type, value_type > aPath;
//       	for (pi=p->begin (); pi!=p->end (); ++pi) {
//       	  aPath.push_back (nodes[*pi]);
//       	}
//       	aPath.setValue (p->getValue ());
//       	realpaths.push_back (aPath);      
//       }
      
//       return realpaths;
//       gOut (2) << "Not implemented." << endl;
//       exit (1);
//     }

    // I/O  -----------------------------------------------------------------

  public:


    virtual ostream& output (ostream& os) const
    {
//       typename UndirectedArrayGraph::const_iterator ki, kj;
//       typename vector< node_type >::const_iterator i;
//       typename vector< edge_type >::const_iterator j;

//       os << "Nodes:" << endl;
//       for (i=nodes.begin (); i!=nodes.end (); ++i) {
// 	os << i-nodes.begin () << " : " << *i << " " << mapping.find (*i)->second << endl;
//       }
//       os << "Edges:" << endl;
//       for (j=edges.begin (); j!=edges.end (); ++j) {
// 	os << j-edges.begin () << " : " << *j << " (" 
// 	   << edgeWeights[j-edges.begin ()] << ")" << endl;
//       }
    
//       os << "Adjacency:" << endl;
//       for (ki=begin (); ki!=end (); ++ki) {      
// 	os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
// 	for (kj=begin (); kj!=end (); ++kj) {
// 	  if (areConnected (*ki, *kj)) 
// 	    os << *kj << "(" << getEdge (*ki, *kj) << ") ";
// 	}
// 	os << endl;
//       }

      int i, j;
      for (i=0; i<size (); ++i) {
	for (j=0; j<size (); ++j) {
	  if (internalAreConnected (i, j))
	    os << "x ";
	  else
	    os << "- ";
	}
	os << endl;
      }    

      return os;
    }
  };
}

#endif
