//                              -*- Mode: C++ -*- 
// Graph.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal
// Author           : Martin Larose
// Created On       : Fri Dec 10 00:05:15 2004
// $Revision: 1.23.4.2 $
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


#ifndef _mccore_Graph_h_
#define _mccore_Graph_h_

#include <iostream>

using namespace std;



namespace mccore
{
  /**
   * Abstract class for the graph classes.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Graph.h,v 1.23.4.2 2004-12-10 05:15:52 larosem Exp $
   */
  template< class N,
	    class NW,
	    class E,
	    class EW,
	    class Node_Comparator = less< N > >	    
  class Graph
  {
    
  protected:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Graph () { }

  public:
    
    /**
     * Clones the object.
     * @return a copy of the object.
     */
    virtual Graph* clone () const = 0;

    /**
     * Destructs the object.
     */
    virtual ~Graph () { }

    // OPERATORS ------------------------------------------------------------

  protected:
    
    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    Graph& operator= (const Graph& right) { return *this; }
    

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os The stream.
     * @return The written stream.
     */
    ostream& write (ostream& os) const;

  };

}

namespace std
{
  ostream& operator<< (ostream &os, const mccore::Graph& obj);
}

#endif
