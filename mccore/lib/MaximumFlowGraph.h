//                              -*- Mode: C++ -*- 
// MaximumFlowGraph.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Apr  7 18:28:55 2003
// $Revision: 1.10.4.1 $
// 
// This file is part of mccore.
// 
// mccore is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// mccore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with mccore; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _mccore_MaximumFlowGraph_h_
#define _mccore_MaximumFlowGraph_h_

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <list>

#include "OrientedGraph.h"



namespace mccore
{
  
  /**
   * Maximum flow in a directed graph but edges are made in both directions.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: MaximumFlowGraph.h,v 1.10.4.1 2004-12-14 02:51:42 larosem Exp $
   */
  template< class V,
	    class E,
	    class VW = float,
	    class Vertex_Comparator = less< V > >	    
  class MaximumFlowGraph : public OrientedGraph< V, E, VW, float, Vertex_Comparator >
  {  
    
  public:
    
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::size_type size_type;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::label label;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::iterator iterator;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::const_iterator const_iterator;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::V2VLabel V2VLabel;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::EV2ELabel EV2ELabel;
    typedef typename Graph< V, E, VW, float, Vertex_Comparator >::EndVertices EndVertices;

    // LIFECYCLE ---------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    MaximumFlowGraph ()
      : OrientedGraph< V, E, VW, float, Vertex_Comparator > ()
    { }
    
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    MaximumFlowGraph (const MaximumFlowGraph &right)
      : OrientedGraph< V, E, VW, float, Vertex_Comparator > (right)
    { }
  
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph< V, E, VW, float, Vertex_Comparator >* cloneGraph () const
    {
      return new MaximumFlowGraph< V, VW, E, float, Vertex_Comparator> (*this);
    }

    /**
     * Destroys the object.
     */
    virtual ~MaximumFlowGraph () { }
  
    // OPERATORS ---------------------------------------------------------------

    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    MaximumFlowGraph& operator= (const MaximumFlowGraph &right)
    {
      if (this != &right)
	{
	  OrientedGraph< V, E, VW, float, Vertex_Comparator >::operator= (right);
	}
      return *this;
    }
    
  public:
    
    // ACCESS ------------------------------------------------------------------
  
    // METHODS -----------------------------------------------------------------

  private:
    
    /**
     * Inserts a vertex in the graph.  Private method to ensure that a vertex
     * weigth is entered.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (V &v) { return false; }

    /**
     * Connects two vertices labels of the graph with an edge.  Two
     * endvertices are added, pointing to the same edge.  No check are
     * made on vertex labels validity.  Private method to ensure that an edge
     * weigth is entered.  Private method to ensure that a in-edge is given.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param e the edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, E &e)
    {
      return false;
    }

  protected:

    /**
     * Connects two vertices labels of the graph with an edge.  Two
     * endvertices are added, pointing to the same edge.  No check are
     * made on vertex labels validity.  Private method to ensure that an edge
     * weigth is entered.
     * @param h the head vertex label of the edge.
     * @param t the tail vertex label of the edge.
     * @param oe the out-edge.
     * @param ie the in-edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, E &oe, E &ie)
    {
      return uncheckedInternalConnect (h, t, e, 0);
    }

    /**
     * Connects two vertices of the graph with an edge and weight.  Two
     * endvertices are added, pointing to the same edge.  No check are
     * made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @param e the edge.
     * @param w the weight of this edge.
     * @return true if the connect operation succeeded.
     */
    virtual bool uncheckedInternalConnect (label h, label t, E &e, float w)
    {
      return (OrientedGraph::uncheckedInternalConnect (h, t, e, w)
	      && OrientedGraph::uncheckedInternalConnect (t, h, 0, 0));
    }
    
    /**
     * Disconnects two endvertices labels of the graph.  No check are
     * made on vertex labels validity.
     * @param h the head vertex of the edge.
     * @param t the tail vertex of the edge.
     * @return true if the vertices were disconnected.
     */
    virtual bool uncheckedInternalDisconnect (label h, label t)
    {
      return (OrientedGraph::uncheckedInternalDisconnect (h, t)
	      && OrientedGraph::uncheckedInternalDisconnect (t, h));
    }      

  public:
    
    /**
     * Pre Flow Push algorithm for solving the Maximum Flow problem.
     * Adapted by Sebastien to minimize each individual flow and avoid
     * "extreme" solutions.  In the context of H-bond patterns, this
     * favors bifurcated geometries, if possible, by separating the
     * flow on the two possible H-bonds of the bifurcation.
     * @param source the source of the graph.
     * @param sink the sink of the graph.
     */
    void preFlowPush (const label& source, const label& sink)
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
	label.push_back (numeric_limits<int>::max ());
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
    float internalGetFlow (const label& o, const label& p) const 
    {
      return edgeFlows[graph.find (o)->second.find (p)->second];
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
      typename vector< label >::const_iterator i;
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
