//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.1 $
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
#include <values.h>

#include "stlio.h"

#include "Graph.h"

namespace mccore {


  /**
   * Maximum flow in a bi-directed graph... The preFlowPush algo has
   * only been tested when nodes are int.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: MaximumFlowGraph.h,v 1.1 2003-04-11 01:37:03 gendrop Exp $
   */
  template < class node_type,
	     class edge_type = bool, 
	     class node_comparator = less< node_type > >
  class MaximumFlowGraph : public Graph< node_type, edge_type, node_comparator >
  {
    /**
     * The graph of reverse edges implemented as a Map of Map, that is
     * an adjacency matrix but where empty cells do not take space in
     * memory.
     */
    graph_type reverseGraph;

    /**
     * The flow on edges.  The capacity will be given by the
     * edgeWeights Map inherited from Graph< int >.
     */
    edge_adapter edgeFlows;

    bool verbose;

    // LIFECYCLE ---------------------------------------------------------------

  public:
  
    /**
     * Initializes the object.
     */
    MaximumFlowGraph () : Graph< node_type, edge_type, node_comparator > () {
      verbose = false;
    }
  
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    MaximumFlowGraph (const MaximumFlowGraph &other) 
      : Graph< node_type, edge_type, node_comparator > (other)
    {
      reverseGraph = other.reverseGraph;
      edgeFlows = other.edgeFlows;
      verbose = false;
    }
  
    /**
     * Destroys the object.
     */
    virtual ~MaximumFlowGraph () {
      clear ();
    }
  
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual MaximumFlowGraph& operator= (const MaximumFlowGraph &other) {
      if (this != &other) {
	Graph< node_type, edge_type, node_comparator >::operator= (other);
	reverseGraph = other.reverseGraph;
	edgeFlows = other.edgeFlows;
      }
      return *this;
    }

    // ACCESS ------------------------------------------------------------------

    /**
     * Gets the weight of this edge.
     * @param o the origin node.
     * @param p the destination node.
     * @return the weight.
     */
    float getWeight (const node_type& o, const node_type& p) const
    {
      assert (areConnected (o, p));
      return edgeWeights.find(o)->second.find (p)->second;
    }
  
    /**
     * Sets the flow of an edge.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @param val the value.
     */
    void setFlow (const node_type& o, const node_type& p, float val) 
    {
      if (!contains (o) || !contains (p)) return;    
      edgeFlows[o][p] = val;
    }
  
    /**
     * Returns the flow of the desired edge
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the weight or 0 if the edge is not in the graph.
     */
    float getFlow (const node_type& o, const node_type& p) const 
    {
      assert (areConnected (o, p));
      if (!contains (o) || !contains (p)) return 0; 
      else return edgeFlows.find(o)->second.find (p)->second;
    }
  
  
    // METHODS -----------------------------------------------------------------

    /**
     * Inserts a node in the graph.
     * @param n the node to insert.
     * @param w the weight of this node (default=1)
     * @return an iterator on the node that was inserted.
     */
    virtual iterator insert (const node_type &n, float weight = 1) 
    {
      if (contains (n)) return graph.find (n);

      graph[n] = adjacency_type ();
      reverseGraph[n] = adjacency_type ();
      nodeWeights[n] = weight;
      iterator p = graph.find (n);
      return p;
    }
  
    /**
     * Erase a node from the graph.
     * @param n the node to remove.
     * @return the number of nodes that were erased.
     */ 
    virtual size_type erase (const node_type &n) 
    {
      if (!contains (n)) return 0;
    
      graph.erase (n);
      reverseGraph.erase (n);
      nodeWeights.erase (n);
    
      graph_type::iterator i;    
      for (i=graph.begin (); i!=graph.end (); ++i) {
	i->second.erase (n);
      }
      for (i=reverseGraph.begin (); i!=reverseGraph.end (); ++i) {
	i->second.erase (n);
      }
      return 1;
    }
  
  
    // GRAPH RELATED METHODS ---------------------------------------------------
  
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
    
      graph[o][p] = e;
      reverseGraph[p][o] = e;
      edgeWeights[o][p] = w;
      setFlow (o, p, 0);

      return true;
    }
  
    /**
     * Returns true if there exists an edge between o to p or p and o.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return true if there exists an edge between o and p.
     */
    bool areConnected (const node_type& o, const node_type& p) const {
      if (!contains (o) || !contains (p)) return false;
      return (graph.find (o)->second.find (p) != graph.find (o)->second.end ());
    }
  
    /**
     * Returns the reverse neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    list< node_type > getReverseNeighbors (const node_type& o) const {
      list< node_type > n;
      if (!contains (o)) return n;
    
      const adjacency_type &at = reverseGraph.find (o)->second;
      for (adjacency_type::const_iterator i=at.begin (); i!=at.end (); ++i) {
	n.push_back (i->first);
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
           
      iterator i;
      adjacency_type::iterator j;

      // Compute the initial distance labels
      map< const node_type, int > label;
      map< const node_type, float > excess;
      
      for (i=begin (); i!=end (); ++i) {
	label[*i] = MAXINT;
	excess[*i] = 0;
      }

      list< node_type > q;
      q.push_back (source);
      int distance = 0;
      label[source] = distance;

      if (verbose) cout << label << endl;

      while (q.size () > 0) {
	distance = label[q.front ()] + 1;
	for (j=graph[q.front ()].begin (); j!=graph[q.front ()].end (); ++j) {  
	  // Uses directly the graph instead of getNeighbors() for efficency.
	  if (label[j->first] > distance) {
	    label[j->first] = distance;
	    q.push_back (j->first);
	  }
	}
	for (j=reverseGraph[q.front ()].begin (); j!=reverseGraph[q.front ()].end (); ++j) {
	  if (label[j->first] > distance) {
	    label[j->first] = distance;
	    q.push_back (j->first);
	  }
	}
	q.pop_front ();
      }

      if (verbose) cout << label << endl;

      // Flood from the source      
      list< node_type > active;
      for (j=graph[source].begin (); j!=graph[source].end (); ++j) {
	setFlow (source, j->first, getWeight (source, j->first));
	excess[j->first] = getFlow (source, j->first);
	excess[source] = excess[source] - getFlow (source, j->first);
	active.push_back (j->first);
      }

      if (verbose) cout << active << endl;
      if (verbose) cout << excess << endl;

      while (active.size () > 0) {
	pushRelabel (active.front (), active, excess, label, source, sink);
	if (excess[active.front ()] == 0) active.pop_front ();
      }
    }

    // PRIVATE METHODS ---------------------------------------------------------

  private:

    void pushRelabel (const node_type& node, 
		      list< node_type >& active, 
		      map< const node_type, float >& excess, 
		      map< const node_type, int >& label, 
		      const node_type& source, const node_type& sink)
    {
      adjacency_type::iterator i;

      if (verbose) cout << "Relabeling [" << node << "]" << endl;

      if (excess[node] > 0) {
	vector< float > cap;
	for (i=graph[node].begin (); i!=graph[node].end (); ++i) {
	  if (label[i->first] > label[node] &&
	      getFlow (node,i->first) < getWeight (node, i->first))
	    cap.push_back (getWeight (node, i->first)-getFlow (node, i->first));
	}
	float eq = equilibrateFlow (cap, excess[node]);

	for (i=graph[node].begin (); i!=graph[node].end (); ++i) {
	  if (label[i->first] > label[node] &&
	      getFlow (node, i->first) < getWeight (node, i->first)) {
	    float push_delta = min(eq, getWeight (node, i->first)-getFlow (node, i->first));

	    if (verbose) cout << "Pushing " << push_delta << " from " << node << " to " << i->first << endl;

	    setFlow (node, i->first, getFlow (node, i->first) + push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (!equals (i->first, source) &&
		!equals (i->first, sink)) {
	      if (verbose) cout << "         AddingA " << i->first << endl;
	      active.push_back (i->first);
	    }
	    excess[i->first] += push_delta;
	  }
	}
      }

      if (excess[node] > 0) {
	vector< float > cap;
	for (i=reverseGraph[node].begin (); i!=reverseGraph[node].end (); ++i) {
	  if (label[i->first] > label[node] &&
	      getFlow (i->first, node) > 0)
	    cap.push_back (getFlow (i->first, node));	 
	}
	float eq = equilibrateFlow (cap, excess[node]);
	
	for (i=reverseGraph[node].begin (); i!=reverseGraph[node].end (); ++i) {
	  if (label[i->first] > label[node] &&
	      getFlow (i->first, node) > 0) {
	    float push_delta = min(eq, getFlow (i->first, node));

	    if (verbose) cout << "Pushing back " << push_delta << " from " << node << " to " << i->first << endl;
	  
	    setFlow (i->first, node, getFlow (i->first, node) - push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (!equals (i->first, source) &&
		!equals (i->first, sink)) {
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

	for (i=graph[node].begin (); i!=graph[node].end (); ++i) {
	  if (getWeight (node, i->first) - getFlow (node, i->first) > 0) {
	    if (label[i->first] > max_dist) {
	      max_dist = label[i->first];
	      if (verbose) cout << "  max_dist forward residual = " 
		   << getWeight (node, i->first) - getFlow (node, i->first)
		   << endl;
	    }
	  }
	}
	
	for (i=reverseGraph[node].begin (); i!=reverseGraph[node].end (); ++i) {
	  if (getFlow (i->first, node) > 0) {
	    if (label[i->first] > max_dist) {
	      max_dist = label[i->first];
	      if (verbose) cout << "  max_dist back residual = " 
		   << getFlow (i->first, node)
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
    
   
    // I/O ---------------------------------------------------------------------

  public:

    virtual ostream& output (ostream& os) const
    {
      graph_type::const_iterator i;
      adjacency_type::const_iterator j;

      os << "Forward Graph" << endl;
      for (i=graph.begin (); i!=graph.end (); ++i) {
	cout << "node      " << i->first << " : ";
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  cout << j->first << "(" << j->second << ") ";
	}
	cout << endl;
	cout << "capacity  " << i->first << " : ";
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  cout << j->first << "=" << getWeight (i->first, j->first) << " ";
	}
	cout << endl;
	cout << "flow      " << i->first << " : ";
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  cout << j->first << "=" << getFlow (i->first, j->first) << " ";
	}
	cout << endl;
      }
//       os << "Reverse Graph" << endl;
//       for (i=reverseGraph.begin (); i!=reverseGraph.end (); ++i) {
// 	cout << i->first << " : ";
// 	for (j=i->second.begin (); j!=i->second.end (); ++j) {
// 	  cout << j->first << "(" << j->second << ") ";
// 	}
// 	cout << endl;
//       }
      return os;
    }
  };

}

#endif
