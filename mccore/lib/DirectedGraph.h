//                              -*- Mode: C++ -*- 
// DirectedGraph.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:34:33 2001
// Update Count     : 1
// Status           : Unknown.
// 


#ifndef _DirectedGraph_h_
#define _DirectedGraph_h_

#include <vector.h>
#include <map.h>


/**
 * @short Directed graph implemented with adjacency lists.
 * 
 * Directed graph implemented with adjacency lists.  Lists of reverse edges
 * are kept for efficiency.  Nodes and edges have no content whatsoever.
 *
 * @author Patrick Gendron
 */
class DirectedGraph
{
  typedef map< int, int > neighbor;
  typedef map< int, int >::iterator neighbor_iterator;

  vector< neighbor > mAdj;
  vector< neighbor > mReverse;

  int mLastEdge;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  DirectedGraph ();

  /**
   * Initializes the object with the other's content.
   * @param other, the object to copy.
   */
  DirectedGraph (const DirectedGraph &other);

  /**
   * Destructs the object.

   */
  ~DirectedGraph ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other, the object to copy.
   * @return itself.
   */
  DirectedGraph &operator= (const DirectedGraph &other);

  // ACCESS ---------------------------------------------------------------
  
  /**
   * Size of the graph as a number of nodes
   * @return number of nodes
   */
  unsigned int size () const { return mAdj.size (); }

  /**
   * Integer id of the last node in the graph
   * @return number of nodes - 1
   */
  int last () const { return int (mAdj.size ()) - 1; }

  // METHODS --------------------------------------------------------------

  /**
   * Adds a node to the graph
   * @return the integer id of the created node
   */
  unsigned int addNode () {
    mAdj.push_back (neighbor ());
    mReverse.push_back (neighbor ());
    return (mAdj.size () - 1);
  }

  /**
   * Adds a directed edge between two nodes
   * @param index_a the source node
   * @param index_b the destination
   */
  void addEdge (int index_a, int index_b) {
    mAdj[index_a][index_b] = mLastEdge;
    mReverse[index_b][index_a] = -mLastEdge;
    ++mLastEdge;
  }

  /**
   * Neighbors of a node
   * @param the interesting node
   * @return the first neighbors accessible from that interesting node
   */
  neighbor &GetAdj (int index) { return mAdj[index]; }

  /**
   * Reverse neighbors of a node
   * @param the interesting node
   * @return the first neighbors accessible from that interesting node
   *         by following edges in their reverse direction
   */
  neighbor &GetReverse (int index) { return mReverse[index]; }
};

// I/O  -------------------------------------------------------------------

//  ostream &operator<< (ostream &os, const DirectedGraph &obj);
//  istream &operator>> (istream &is, DirectedGraph &obj);

#endif
