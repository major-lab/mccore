//                              -*- Mode: C++ -*- 
// UndirectedGraph.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:30:26 2003
// $Revision: 1.10 $
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

#include "AbstractGraph.h"
#include "Graph.h"
#include "GraphAlgo.h"
#include "Path.h"



namespace mccore {

  /**
   * @short A templated undirected graph class.  It is implemented using
   * the directed graph base class and by using a triangular matrix and
   * a node ordering determined by the node_comparator function object.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: UndirectedGraph.h,v 1.10 2004-01-09 21:47:43 gendrop Exp $
   */
  template< class node_type, 
	    class edge_type = bool, 
	    class node_comparator = less< node_type > >
  class UndirectedGraph : public virtual Graph< node_type, edge_type, node_comparator >,
			  public virtual UndirectedAbstractGraph< node_type, edge_type, node_comparator >
  {
  
    // LIFECYCLE ------------------------------------------------------------

  public:

    /**
     * Initializes the object.
     */
    UndirectedGraph () 
      : Graph< node_type, edge_type, node_comparator > () {}


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

  public:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    UndirectedGraph& operator= (const UndirectedGraph &other) {    
      if (this != &other) {
	Graph< node_type, edge_type, node_comparator >::operator= (other);      
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

      graph[mapping[o]][mapping[p]] = edges.size ()-1;
      graph[mapping[p]][mapping[o]] = edges.size ()-1;

        
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
    
      int e = graph[mapping[o]][mapping[p]];
      graph.find (mapping[o])->second.erase (mapping[p]);
      graph.find (mapping[p])->second.erase (mapping[o]);

      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);

      map< int, map< int, int > >::iterator i;
      map< int, int >::iterator j;
    
      for (i=graph.begin (); i!=graph.end (); ++i) {
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  if (j->second > e) j->second--;
	}
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
    vector< Path< node_type, float > > cycleBase () { 

      vector< Path< int, float > > paths;
      vector< Path< int, float > >::iterator p;
      Path< int, float >::iterator pi;
      vector< Path< node_type, float > > realpaths;

      paths = GraphAlgo::cycleBaseHorton (*this, 0); 
      
      for (p=paths.begin (); p!=paths.end (); ++p) {
      	Path< node_type, float > aPath;
      	for (pi=p->begin (); pi!=p->end (); ++pi) {
      	  aPath.push_back (nodes[*pi]);
      	}
      	aPath.setValue (p->getValue ());
      	realpaths.push_back (aPath);      
      }
      
      return realpaths;
    }

    /**
     * Computes the union of the minimum cycle basis for this graph.
     */
    vector< Path< node_type, float > > cycleBaseUnion () { 

      vector< Path< int, float > > paths;
      vector< Path< int, float > >::iterator p;
      Path< int, float >::iterator pi;
      vector< Path< node_type, float > > realpaths;

      paths = GraphAlgo::cycleBaseHorton (*this, 1); 
      
      for (p=paths.begin (); p!=paths.end (); ++p) {
      	Path< node_type, float > aPath;
      	for (pi=p->begin (); pi!=p->end (); ++pi) {
      	  aPath.push_back (nodes[*pi]);
      	}
      	aPath.setValue (p->getValue ());
      	realpaths.push_back (aPath);      
      }
      
      return realpaths;
    }

    /**
     * Computes the union of all the minimum cycles for this graph.
     */
    vector< Path< node_type, float > > minimumCycles () { 

      vector< Path< int, float > > paths;
      vector< Path< int, float > >::iterator p;
      Path< int, float >::iterator pi;
      vector< Path< node_type, float > > realpaths;

      paths = GraphAlgo::cycleBaseHorton (*this, 2);
      
      for (p=paths.begin (); p!=paths.end (); ++p) {
      	Path< node_type, float > aPath;
      	for (pi=p->begin (); pi!=p->end (); ++pi) {
      	  aPath.push_back (nodes[*pi]);
      	}
      	aPath.setValue (p->getValue ());
      	realpaths.push_back (aPath);      
      }
      
      return realpaths;
    }


    // I/O  -----------------------------------------------------------------

  public:


//     virtual ostream& output (ostream& os) const
//     {
//       typename UndirectedGraph::const_iterator ki, kj;
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
    
//       return os;
//     }

  };

}

#endif
