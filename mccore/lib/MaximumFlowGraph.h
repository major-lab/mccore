//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.6 $
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

#include "AdjacencyMatrix.h"
#include "Graph.h"

namespace mccore {


  /**
   * Maximum flow in a bi-directed graph... The preFlowPush algo has
   * only been tested when nodes are int.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: MaximumFlowGraph.h,v 1.6 2003-12-23 14:48:25 larosem Exp $
   */
  template < class node_type,
	     class edge_type = bool, 
	     class matrix_type = MapMatrix,
	     class node_comparator = less< node_type > >
  class MaximumFlowGraph : public Graph< node_type, edge_type, matrix_type, node_comparator >
  {  

    // MEMBERS -----------------------------------------------------------------


    /**
     * The graph of reverse edges implemented as a Map of Map, that is
     * an adjacency matrix but where empty cells do not take space in
     * memory.
     */
    matrix_type reverseGraph;


    /**
     * The flow on edges.  The capacity will be given by the
     * edgeWeights Map inherited from Graph< int >.
     */
    vector< float > edgeFlows;

    bool verbose;


    // PUBLIC TYPEDEFS ---------------------------------------------------------


  public:


    /**
     * iterator
     */
    typedef typename Graph< node_type, edge_type, matrix_type, node_comparator >::iterator iterator;
    
    /**
     * const iterator
     */
    typedef typename Graph< node_type, edge_type, matrix_type, node_comparator >::const_iterator const_iterator;


    // LIFECYCLE ---------------------------------------------------------------

  public:
  
    /**
     * Initializes the object.
     */
    MaximumFlowGraph (int size_hint = 0) 
      : Graph< node_type, edge_type, matrix_type, node_comparator > (size_hint) {
      verbose = false;
    }
  
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    MaximumFlowGraph (const MaximumFlowGraph &other) 
      : Graph< node_type, edge_type, matrix_type, node_comparator > (other)
    {}
  
    /**
     * Destroys the object.
     */
    virtual ~MaximumFlowGraph () {
      clear ();
    }
  
    // OPERATORS ---------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    MaximumFlowGraph& operator= (const MaximumFlowGraph &other) {
      if (this != &other) {
	Graph< node_type, edge_type, matrix_type, node_comparator >::operator= (other);
 	edgeFlows = other.edgeFlows;
      }
      return *this;
    }

    // ACCESS ------------------------------------------------------------------
  
    /**
     * Sets the flow of an edge.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @param val the value.
     */
    void setFlow (const node_type& o, const node_type& p, float val) 
    {
      assert (contains (o));
      assert (contains (p));
      assert (areConnected (o, p));
      edgeFlows[graph.get (mapping.find (o)->second, mapping.find (p)->second)] = val;
    }
  
    /**
     * Returns the flow of the desired edge
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the weight or 0 if the edge is not in the graph.
     */
    float getFlow (const node_type& o, const node_type& p) const 
    {
      assert (contains (o));
      assert (contains (p));
      assert (areConnected (o, p));
      return edgeFlows[graph.get (mapping.find (o)->second, mapping.find (p)->second)];
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
      if (contains (n)) return find (n);

      mapping[n] = nodes.size ();
      nodes.push_back (n);
      nodeWeights.push_back (weight);

      graph.resize (size ());
      reverseGraph.resize (size ());

      iterator p = find (n);
      return p;
    }
  
//     /**
//      * Erase a node from the graph.
//      * @param n the node to remove.
//      * @return the number of nodes that were erased.
//      */ 
//     virtual size_type erase (const node_type &n) 
//     {
//       if (!contains (n)) return 0;
    
//       const node_type* np = &*nodes.insert (n).first;

//       graph.erase (np);
//       reverseGraph.erase (np);
//       nodeWeights.erase (np);
    
//       typename graph_type::iterator i;    
//       for (i=graph.begin (); i!=graph.end (); ++i) {
// 	i->second.erase (np);
//       }
//       for (i=reverseGraph.begin (); i!=reverseGraph.end (); ++i) {
// 	i->second.erase (np);
//       }

//       nodes.erase (*np);

//       return 1;
//     }
  
  
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

      graph.connect (mapping[o], mapping[p], edges.size ()-1);
      reverseGraph.connect (mapping[p], mapping[o], edges.size ()-1);

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
      reverseGraph.disconnect (mapping[p], mapping[o]);

      edges.erase (edges.begin () + e);
      edgeWeights.erase (edgeWeights.begin () + e);
      edgeFlows.erase (edgeWeights.begin () + e);

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
      if (!contains (o)) return n;
      
      list< int > l = internalGetReverse (mapping.find (o)->second);
      list< int >::iterator i;
      
      for (i=l.begin (); i!=l.end (); ++i) {
	n.push_back (nodes[*i]);
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
      list< int > neigh;
      list< int >::iterator j;
      
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
	neigh = internalGetNeighbors (q.front ());
	for (j=neigh.begin (); j!=neigh.end (); ++j) {  
	  if (label[*j] > distance) {
	    label[*j] = distance;
	    q.push_back (*j);
	  }
	}
	neigh = internalGetReverseNeighbors (q.front ());
	for (j=neigh.begin (); j!=neigh.end (); ++j) {
	  if (label[*j] > distance) {
	    label[*j] = distance;
	    q.push_back (*j);
	  }
	}
	q.pop_front ();
      }

//       if (verbose) cout << label << endl;

      // Flood from the source      
      list< int > active;
      neigh = internalGetNeighbors (sourceid);
      for (j=neigh.begin (); j!=neigh.end (); ++j) {
	internalSetFlow (sourceid, *j, internalGetWeight (sourceid, *j));
	excess[*j] = internalGetFlow (sourceid, *j);
	excess[sourceid] = excess[sourceid] - internalGetFlow (sourceid, *j);
	active.push_back (*j);
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
    
    void internalPushRelabel (int node, list< int >& active, vector< float >& excess, 
			      vector< int >& label, int source, int sink)
    {
      list< int > neigh;
      list< int >::iterator i;

      if (verbose) cout << "Relabeling [" << node << "]" << endl;
      
      if (excess[node] > 0) {
	vector< float > cap;
	neigh = internalGetNeighbors (node);
	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (label[*i] > label[node] &&
	      internalGetFlow (node, *i) < internalGetWeight (node, *i))
	    cap.push_back (internalGetWeight (node, *i) - internalGetFlow (node, *i));
	}
	float eq = equilibrateFlow (cap, excess[node]);

	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (label[*i] > label[node] &&
	      internalGetFlow (node, *i) < internalGetWeight (node, *i)) {
	    float push_delta = min(eq, internalGetWeight (node, *i)-internalGetFlow (node, *i));

	    if (verbose) cout << "Pushing " << push_delta << " from " << node << " to " << *i << endl;

	    internalSetFlow (node, *i, internalGetFlow (node, *i) + push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (*i != source && *i != sink) {
	      if (verbose) cout << "         AddingA " << *i << endl;
	      active.push_back (*i);
	    }
	    excess[*i] += push_delta;
	  }
	}
      }

      if (excess[node] > 0) {
	vector< float > cap;
	neigh = internalGetReverseNeighbors (node);
	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (label[*i] > label[node] &&
	      internalGetFlow (*i, node) > 0)
	    cap.push_back (internalGetFlow (*i, node));	 
	}
	float eq = equilibrateFlow (cap, excess[node]);
	
	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (label[*i] > label[node] &&
	      internalGetFlow (*i, node) > 0) {
	    float push_delta = min(eq, internalGetFlow (*i, node));

	    if (verbose) cout << "Pushing back " << push_delta << " from " << node << " to " << *i << endl;
	  
	    internalSetFlow (*i, node, internalGetFlow (*i, node) - push_delta);
	    excess[node] = excess[node] - push_delta;
	    if (fabs (excess[node]) < 1e-5) excess[node] = 0;
	    if (*i != source && *i != sink) {
	      if (verbose) cout << "         AddingB " << *i << endl;
	      active.push_back (*i);
	    }
	    excess[*i] += push_delta;
	  }
	}
      }
    
      if (excess[node] > 0) {
	if (verbose) cout << "Residual" << endl;

	int max_dist = -2 * size ();

	neigh = internalGetNeighbors (node);
	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (internalGetWeight (node, *i) - internalGetFlow (node, *i) > 0) {
	    if (label[*i] > max_dist) {
	      max_dist = label[*i];
	      if (verbose) cout << "  max_dist forward residual = " 
				<< internalGetWeight (node, *i) - internalGetFlow (node, *i)
				<< endl;
	    }
	  }
	}
	
	neigh = internalGetReverseNeighbors (node);
	for (i=neigh.begin (); i!=neigh.end (); ++i) {
	  if (internalGetFlow (*i, node) > 0) {
	    if (label[*i] > max_dist) {
	      max_dist = label[*i];
	      if (verbose) cout << "  max_dist back residual = " 
				<< internalGetFlow (*i, node)
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
    

    /**
     * Sets the flow of an edge.
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @param val the value.
     */
    void internalSetFlow (int o, int p, float val) 
    {
      assert (graph.contains (o));
      assert (graph.contains (p));
      assert (graph.areConnected (o, p));
      edgeFlows[graph.get (o, p)] = val;
    }
  
    /**
     * Returns the flow of the desired edge
     * @param o an extremity of the edge.
     * @param p an extremity of the edge.
     * @return the weight or 0 if the edge is not in the graph.
     */
    float internalGetFlow (const node_type& o, const node_type& p) const 
    {
      assert (graph.contains (o));
      assert (graph.contains (p));
      assert (graph.areConnected (o, p));
      return edgeFlows[graph.get (o, p)];
    }
  
    /**
     * Returns the reverse neighbors of the given node.
     * @param o a node in the graph.
     * @return the list of neighbors.
     */
    virtual list< int > internalGetReverseNeighbors (int o) const
    {
      if (!reverseGraph.contains (o)) return list< int >();
      return reverseGraph.neighbors (o);
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
      
      graph.output (os);
      os << endl;
      reverseGraph.output (os);
      

      return os;
    }
  };

}

#endif
