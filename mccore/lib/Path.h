//                              -*- Mode: C++ -*- 
// Path.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:31:52 2003
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


#ifndef _Path_h_
#define _Path_h_

#include <iostream>
#include <list>

namespace mccore {

  /**
   * @short A path in a graph.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Path.h,v 1.2 2003-04-11 01:34:28 gendrop Exp $
   */
  template< class node_type, class valuetype >
  class Path : public list< node_type >
  {

    valuetype value;

  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Path () : list< node_type >(), value (valuetype ()) { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Path (const Path &other) : list< node_type > (other) { value = other.value; }

    /**
     * Destroys the object.
     */
    ~Path () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Path& operator= (const Path &other)
    {
      if  (this != &other) {
	list< node_type >::operator= (other);
	value = other.value;
      } 
      return *this;
    }

    /**
     * Determines if this path is shorter that the other.
     * @param other another path.
     * @return true if this path is shorter.
     */
    bool operator< (const Path &other) const {
      return  (size () < other.size ());
    }
    
    // ACCESS ---------------------------------------------------------------

    void setValue (valuetype &v) { value = v; }

    valuetype getValue (void) const { return value; }

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------

    ostream &output (ostream &out) const {
      out << "[ " << flush;
      copy (begin (), end (), ostream_iterator< node_type > (out, " "));
      out << "] " << value << flush;
      return out;
    }
    
    friend ostream &operator<< (ostream &out, const Path &path)
    {
      return path.output (out);
    }
  };

}
  

#endif
