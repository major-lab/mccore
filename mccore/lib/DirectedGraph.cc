//                              -*- Mode: C++ -*- 
// DirectedGraph.cc
// Copyright © 2001, 2003 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu May 10 14:49:18 2001
// Last Modified By : Patrick Gendron
// Last Modified On : Wed Jan 15 13:39:43 2003
// Update Count     : 11
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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

ostream& DirectedGraph::output (ostream& os) const
{
  os << "----" << endl;;
  map< int, int >::const_iterator k;
  for (int i=0; i<mAdj.size (); ++i) {
    for (int j=0; j<mAdj.size (); ++j) {
      if ((k=mAdj[i].find (j)) != mAdj[i].end ())
	os << k->second << " ";
      else
	os << "-" << " ";					   
    }
    os << endl;
  }
  os << "----" << endl;
   for (int i=0; i<mReverse.size (); ++i) {
    for (int j=0; j<mReverse.size (); ++j) {
      if ((k=mReverse[i].find (j)) != mReverse[i].end ())
	os << k->second << " ";
      else
	os << "-" << " ";					   
    }
    os << endl;
  }
  return os;
}

 ostream &operator<< (ostream &os, const DirectedGraph &obj)
 {
   return obj.output (os);
 }


//  istream &operator>> (istream &is, DirectedGraph &obj)
//  {
//    return obj.input (is);
//  }


