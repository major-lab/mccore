//                              -*- Mode: C++ -*- 
// Path.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
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

using namespace std;

namespace mccore {

  /**
   * @short A path in a graph.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Path.h,v 1.4 2004-04-02 18:59:52 larosem Exp $
   */
  template< class node_type, class valuetype >
  class Path : public list< node_type >
  {    

    valuetype value;

  public:
   
    
    typedef typename list< node_type >::const_iterator const_iterator;
    typedef typename list< node_type >::iterator iterator;

 
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Path ()
      : list< node_type > (),
	value (valuetype ())
    { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Path (const Path &other)
      : list< node_type > (other),
	value (other.value)
    { }

    /**
     * Destroys the object.
     */
    ~Path () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Path& operator= (const Path &other)
    {
      if  (this != &other)
	{
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

    /**
     * Compares two paths to determine if they are equal.  They are
     * compared in both directions and are rotated, i.e. it is to be
     * used with cycles.
     */
    bool operator== (const Path &other) const
    {
      if (value == other.value
	  && size () == other.size ())
	{
	  if (empty ())
	    return true;
	  else
	    {
	      const Path &a = *this;
	      Path b = other;
	      int i;
	      
	      for (i = 0; i <(int) a.size (); ++i)
		{
		  if ((const list< node_type >&) a == (list< node_type >&) b)
		    return true;
		  b.rotate ();
		}
	      
	      b.reverse ();
	      
	      for (i = 0; i < (int) a.size (); ++i)
		{
		  if ((list< node_type >&) a == (list< node_type >&) b)
		    return true;
		  b.rotate ();
		}
	    }
	}
      return false;
    }
      

    bool operator!= (const Path &other) const { return ! this->operator== (other); }
     
    // ACCESS ---------------------------------------------------------------

    void setValue (const valuetype &v) { value = v; }

    valuetype getValue (void) const { return value; }

    // METHODS --------------------------------------------------------------

    void rotate ()
    {
      this->push_back (this->front ());
      this->pop_front ();
    }
    
    // I/O  -----------------------------------------------------------------

    ostream &output (ostream &out) const {
      out << "[ " << flush;
      const_iterator i;
      for (i=begin (); i!=end (); ++i) {
	out << *i << " ";
      }
      out << "] " << value << flush;
      return out;
    }
    
    friend ostream &operator<< (ostream &out, const Path &path)
    {
      return path.output (out);
    }
  };

  template < class node_type, class valuetype >
  ostream &operator<< (ostream &out, const Path< node_type, valuetype > &path)
  {
    return path.output (out);
  }
}
  

#endif
