//                              -*- Mode: C++ -*- 
// DirectedGraph.cc
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:34:31 2001
// Update Count     : 1
// Status           : Unknown.
// 


#include "DirectedGraph.h"


// LIFECYCLE ------------------------------------------------------------


DirectedGraph::DirectedGraph ()
  : mLastEdge (0)
{}


DirectedGraph::DirectedGraph (const DirectedGraph &other)
  : mAdj (other.mAdj), mReverse (other.mReverse), mLastEdge (other.mLastEdge)
{}


DirectedGraph::~DirectedGraph (void)
{}


// OPERATORS ------------------------------------------------------------


DirectedGraph &DirectedGraph::operator= (const DirectedGraph &other)
{
  if (this != &other) { 
    mAdj = other.mAdj;
    mReverse = other.mReverse;
    mLastEdge = other.mLastEdge;
  }
  return *this;
}


// ACCESS ---------------------------------------------------------------


// METHODS --------------------------------------------------------------


// I/O  -----------------------------------------------------------------


//  ostream &operator<< (ostream &os, const DirectedGraph &obj)
//  {
//    return obj.output (os);
//  }


//  istream &operator>> (istream &is, DirectedGraph &obj)
//  {
//    return obj.input (is);
//  }


