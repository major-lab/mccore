//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.9 $
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


#ifndef _MaximumFlowGraph_h_
#define _MaximumFlowGraph_h_

#include <iostream>
#include <map>
#include <list>
#include <algorithm>

#include "Graph.h"

namespace mccore {


  /**
   * Maximum flow in a bi-directed graph... The preFlowPush algo has
   * only been tested when nodes are int.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: MaximumFlowGraph.h,v 1.9 2004-01-09 21:47:36 gendrop Exp $
   */
  template < class node_type,
	     class edge_type = bool, 
	     class node_comparator = less< node_type > >
  class MaximumFlowGraph : public Graph< node_type, edge_type, node_comparator >
  {  

    // MEMBERS -----------------------------------------------------------------

  protected:

    /**
     * The graph of reverse edges implemented as a Map of Map, that is
     * an adjacency matrix but where empty cells do not take space in
     * memory.
     */
    map< int, map< int, int > > reverseGraph;


    /**
     * The flow on edges.  The capacity will be given by the
     * edgeWeights Map inherited from Graph< int >.
     */
    vector< float > edgeFlows;

    bool verbose;


    // LIFECYCLE ---------------------------------------------------------------

  public:
  
    /**
     * Initializes the object.
     */
    MaximumFlowGraph () 
      : Graph< node_type, edge_type, node_comparator > () 
    {
      verbose = false;
    }
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    MaximumFlowGraph (const AbstractGraph< node_type, edge_type, node_comparator > &other) 
      : Graph< node_type, edge_type, node_comparator > (other)
    {
      verbose = false;
    }
  
    /**
     * Destroys the object.
     */
    virtual ~MaximumFlowGraph () {
      clear ();
    }
  
    // OPERATORS ---------------------------------------------------------------

  public:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    MaximumFlowGraph& operator= (const MaximumFlowGraph &other) {
      if (this != &other) {
	Graph< node_type, edge_type, node_comparator >::operator= (other);
 	edgeFlows = other.edgeFlows;
      }
      return *this;
    }

    // ACCESS ------------------------------------------------------------------
  
  public:

    /**
     * Sets the flow of an edge.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @param val the value.
     */
    void setFlow (const node_type& o, const node_type& p, float val) 
    {
      edgeFlows[graph.find (mapping.find (o)->second)->second.find (mapping.find (p)->second)->second] = val;
    }
    
    /**
     * Returns the flow of the desired edge
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the weight or 0 if the edge is not in the graph.
     */
    float getFlow (const node_type& o, const node_type& p) const 
    {
      return edgeFlows[graph.find (mapping.find (o)->second)->second.find (mapping.find (p)->second)->second];
    }
  
  
    // METHODS -----------------------------------------------------------------

  public:

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const node_type &n, float weight = 1) 
    {
      if (contains (n)) return false;

      mapping[n] = nodes.size ();
      nodes.push_back (n);
      nodeWeights.push_back (weight);
      
      graph[mapping[n]] = map< int, int > ();
      reverseGraph[mapping[n]] = map< int, int > ();

      return true;
    }
  
  
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
      edgeFlows.push_back (0);

      graph[mapping[o]][mapping[p]] = edges.size ()-1;
      reverseGraph[mapping[p]][mapping[o]] = edges.size ()-1;

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
      reverseGraph.find (mapping[p])->second.erase (mapping[o]);
      
      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);
      edgeFlows.erase (edgeWeights.begin () + e);
      
      map< int, map< int, int > >::iterator i;
      map< int, int >::iterator j;
      
      for (i=graph.begin (); i!=graph.end (); ++i) {
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  if (j->second > e) j->second--;
	}
      }
      
      for (i=reverseGraph.begin (); i!=reverseGraph.end (); ++i) {
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  if (j->second > e) j->second--;
	}
      }     
      return true;
    }


    /**
     * Returns the reverse neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    list< node_type > getReverseNeighbors (const node_type& o) const 
    {
      list< node_type > n;
      map< int, int >::const_iterator col;
      
      int i = mapping.find (o)->second;
      
      for (col=reverseGraph.find (i)->second.begin (); 
	   col!=reverseGraph.find (i)->second.end (); ++col) {
	l.push_back (nodes[col->first]);
      }
      
      return n;
    }

    /**
     * Pre Flow Push algorithm for solving the Maximum Flow problem.
     * Adapted by Sebastien to minimize each individual flow and avoid
     * "extreme" solutions.  In the context of H-bond patterns, this
     * favors bifurcated geometries, if possible, by separating the
     * flow on the two possible H-bonds of the bifurcation.
     * @param source the source of the graph.
     * @param sink the sink of the graph.
     */
    void preFlowPush (const node_type& source, const node_type& sink)
    {
      if (!contains (source) || !contains (sink)) return;
     
      int sourceid = mapping.find (source)->second;
      int sinkid = mapping.find (sink)->second;
 
      int i;
      map< int, int >::const_iterator j;
      
      // Compute the initial distance labels
      vector< int > label;
      vector< float > excess;
      
      for (i=0; i<size (); ++i) {
	label.push_back (MAXINT);
	excess.push_back (0);
      }

      list< int > q;
      q.push_back (sourceid);
      int distance = 0;
      label[sourceid] = distance;

//       if (verbose) cout << label << endl;

      while (q.size () > 0) {
	distance = label[q.front ()] + 1;
	for (j=getNeighborsMap (q.front ()).begin (); j!=getNeighborsMap (q.front ()).end (); ++j) {  
	  if (label[j->first] > distance) {
	    label[j->first] = distance;
	    q.push_back (j->first);
	  }
	}
	for (j=getReverseNeighborsMap (q.front ()).begin (); 
	     j!=getReverseNeighborsMap (q.front ()).end (); ++j) {
	  if (label[j->first] > distance) {
	    label[j->first] = distance;
	    q.push_back (j->first);
	  }
	}
	q.pop_front ();
      }

//       if (verbose) cout << label << endl;

      // Flood from the source      
      list< int > active;
      for (j=getNeighborsMap (sourceid).begin (); 
	   j!=getNeighborsMap (sourceid).end (); ++j) {
	internalSetFlow (sourceid, j->first, internalGetWeight (sourceid, j->first));
	excess[j->first] = internalGetFlow (sourceid, j->first);
	excess[sourceid] = excess[sourceid] - internalGetFlow (sourceid, j->first);
	active.push_back (j->first);
      }

//       if (verbose) cout << active << endl;
//       if (verbose) cout << excess << endl;

      while (active.size () > 0) {
	internalPushRelabel (active.front (), active, excess, label, sourceid, sinkid);
	if (excess[active.front ()] == 0) active.pop_front ();
      }
    }
    
    // PRIVATE METHODS ---------------------------------------------------------
    
  private:
    
    /**
     * Push-Relabel part of the Pre Flow Push algorithm.
     */
    void internalPushRelabel (int node, list< int >& active, vector< float >& excess, 
			      vector< int >& label, int source, int sink)
    {
      map< int, int >::const_iterator i;

      if (verbose) cout << "Relabeling [" << node << "]" << endl;
      
      if (excess[node] > 0) {
	vector< float > cap;
	for (i=getNeighborsMap (node).begin (); i!=getNeighborsMap (node).end (); ++i) {
	  if (label[i->first] > label[node] &&
	      internalGetFlow (node, i->first) < internalGetWeight (node, i->first))
	    cap.push_back (internalGetWeight (node, i->first) - internalGetFlow (node, i->first));
	}
	float eq = equilibrateFlow (cap, excess[node]);

	for (i=getNeighborsMap (node).begin (); i!=getNeighborsMap (node).end (); ++i) {
	  if (label[i->first] > label[node] &&
	      internalGetFlow (node, i->first) < internalGetWeight (node, i->first)) {
	    float push_delta = min(eq, internalGetWeight (node, i->first)-internalGetFlow (node, i->first));

	    if (verbose) cout << "Pushing " << push_delta << " from " << node << " to " << i->first << endl;

	    internalSetFlow (node, i->first, internalGetFlow (node, i->first) + push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (i->first != source && i->first != sink) {
	      if (verbose) cout << "         AddingA " << i->first << endl;
	      active.push_back (i->first);
	    }
	    excess[i->first] += push_delta;
	  }
	}
      }

      if (excess[node] > 0) {
	vector< float > cap;
	for (i=getReverseNeighborsMap (node).begin (); i!=getReverseNeighborsMap (node).end (); ++i) {
	  if (label[i->first] > label[node] &&
	      internalGetFlow (i->first, node) > 0)
	    cap.push_back (internalGetFlow (i->first, node));	 
	}
	float eq = equilibrateFlow (cap, excess[node]);
	
	for (i=getReverseNeighborsMap (node).begin (); i!=getReverseNeighborsMap (node).end (); ++i) {
	  if (label[i->first] > label[node] &&
	      internalGetFlow (i->first, node) > 0) {
	    float push_delta = min(eq, internalGetFlow (i->first, node));

	    if (verbose) cout << "Pushing back " << push_delta << " from " << node << " to " << i->first << endl;
	  
	    internalSetFlow (i->first, node, internalGetFlow (i->first, node) - push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (i->first != source && i->first != sink) {
	      if (verbose) cout << "         AddingB " << i->first << endl;
	      active.push_back (i->first);
	    }
	    excess[i->first] += push_delta;
	  }
	}
      }
    
      if (excess[node] > 0) {
	if (verbose) cout << "Residual" << endl;

	int max_dist = -2 * size ();

	for (i=getNeighborsMap (node).begin (); i!=getNeighborsMap (node).end (); ++i) {
	  if (internalGetWeight (node, i->first) - internalGetFlow (node, i->first) > 0) {
	    if (label[i->first] > max_dist) {
	      max_dist = label[i->first];
	      if (verbose) cout << "  max_dist forward residual = " 
				<< internalGetWeight (node, i->first) - internalGetFlow (node, i->first)
				<< endl;
	    }
	  }
	}
	
	for (i=getReverseNeighborsMap (node).begin (); i!=getReverseNeighborsMap (node).end (); ++i) {
	  if (internalGetFlow (i->first, node) > 0) {
	    if (label[i->first] > max_dist) {
	      max_dist = label[i->first];
	      if (verbose) cout << "  max_dist back residual = " 
				<< internalGetFlow (i->first, node)
				<< endl;
	    }
	  }
	}

	if (verbose) cout << "Relabel[" << node << "] from " 
			  << label[node] << " to " << (max_dist - 1)
			  << " (excess = " << excess[node] << ")" << endl;
	
	label[node] = max_dist - 1;
      }
    }
    
    
    /**
     * Reequilibrate flows in the graph.
     */
    float equilibrateFlow (vector< float > capacities, float excess) 
    {
      unsigned int i;
      sort (capacities.begin (), capacities.end ());
      for (i = 0; i < capacities.size (); ++i)
	if (capacities[i] < (excess / (capacities.size () - i))) excess -= capacities[i];
	else break;
      if (i == capacities.size ()) {
	// The capacity of the donor/acceptor is not exceeded, so give everything
	return 1;
      }
      return (excess / (capacities.size () - i));
    }
    

    /**
     * Sets the flow of an edge.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @param val the value.
     */
    void internalSetFlow (int o, int p, float val) 
    {
      edgeFlows[graph[o][p]] = val;
    }
  
    /**
     * Returns the flow of the desired edge
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the weight or 0 if the edge is not in the graph.
     */
    float internalGetFlow (const node_type& o, const node_type& p) const 
    {
      return edgeFlows[graph.find (o)->second.find (p)->second];
    }
  
    /**
     * Returns the reverse neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetReverseNeighbors (int o) const
    {
      list< int > l;
      //if (reverseGraph.find (o) == reverseGraph.end ()) return l;

      map< int, int >::const_iterator col;

      for (col=reverseGraph.find (o)->second.begin (); 
	   col!=reverseGraph.find (o)->second.end (); ++col) {
	l.push_back (col->first);
      }

      return l;
    }


    // CUSTOM INTERFACE --------------------------------------------------------

  protected:

    /**
     * Returns the neighbors of the given node in the form of a map of
     * neighbors/edge ids..
     * @param o a node in the graph.
     * @return the map of neighbors with the associated edge.
     */
    const map< int, int >& getReverseNeighborsMap (int o) const {
      static const map< int, int > empty;
      
      map< int, map< int, int > >::const_iterator i = reverseGraph.find (o);
      if (i!=graph.end ()) {
	return i->second;
      } 
      return empty;
    }
    

    
    // I/O ---------------------------------------------------------------------

  public:

    virtual ostream& output (ostream& os) const
    {
      typename MaximumFlowGraph::const_iterator ki, kj;
      typename vector< node_type >::const_iterator i;
      typename vector< edge_type >::const_iterator j;
 
      os << "Nodes:" << endl;
      for (i=nodes.begin (); i!=nodes.end (); ++i) {
	os << i-nodes.begin () << " : " << *i << " (" 
	   << nodeWeights[i-nodes.begin ()] << ")" << endl;
      }
      os << "Edges:" << endl;
      for (j=edges.begin (); j!=edges.end (); ++j) {
	os << j-edges.begin () << " : " << *j << " (" 
	   << edgeFlows[j-edges.begin ()] << "/"
	   << edgeWeights[j-edges.begin ()] << ")" << endl;
      }
      os << "Adjacency:" << endl;
      for (ki=begin (); ki!=end (); ++ki) {      
	os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
	for (kj=begin (); kj!=end (); ++kj) {
	  if (areConnected (*ki, *kj)) 
	    os << *kj << "(" << getEdge (*ki, *kj) << ") ";
	}
	os << endl;
      }
      
      os << "Reverse Adjacency: " << endl;
      for (ki=begin (); ki!=end (); ++ki) {      
	os << *ki << "(" << getWeight (*ki) << ")" << " : ";      
	for (kj=begin (); kj!=end (); ++kj) {
	  if (areConnected (*kj, *ki)) 
	    os << *kj << "(" << getEdge (*kj, *ki) << ") ";
	}
	os << endl;
      }

      return os;
    }
  };

}

#endif
