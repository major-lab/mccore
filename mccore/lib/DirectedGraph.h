//                              -*- Mode: C++ -*- 
// DirectedGraph.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 23 15:17:18 2001
// Update Count     : 2
// Status           : Unknown.
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
public:
  typedef map< int, int > neighbor;
  typedef map< int, int >::iterator neighbor_iterator;

private:
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
