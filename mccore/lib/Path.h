//                              -*- Mode: C++ -*- 
// Path.h
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Mon Mar 24 21:31:52 2003
// $Revision: 1.12 $
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


#ifndef _mccore_Path_h_
#define _mccore_Path_h_

#include <iostream>
#include <vector>

using namespace std;



namespace mccore
{

  /**
   * A path in a graph.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Path.h,v 1.12 2006-08-02 18:01:22 larosem Exp $
   */
  template< class node_type, class valuetype >
  class Path : public vector< node_type >
  {    

    valuetype value;

  public:
   
    typedef typename vector< node_type >::size_type size_type;
    typedef typename vector< node_type >::const_iterator const_iterator;
    typedef typename vector< node_type >::iterator iterator;
 
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    Path () : value (valuetype ()) { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Path (const Path &other)
      : vector< node_type > (other),
	value (other.value)
    { }

    /**
     * Clones the Cycle in a new object.
     * @return a copy of this.
     */
    virtual Path< node_type, valuetype >* clone () const { return new Path (*this); }
      
    /**
     * Destroys the object.
     */
    virtual ~Path () { }

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
	  vector< node_type >::operator= (other);
	  value = other.value;
	}
      return *this;
    }

    /**
     * Determines if this path is shorter that the other.
     * @param other another path.
     * @return true if this path is shorter.
     */
    bool operator< (const Path &other) const
    {
      if (value < other.value
	  || (value == other.value
	      && size () < other.size ()))
	{
	  return true;
	}
      else if (value == other.value
	       && size () == other.size ())
	{
	  const_iterator cit;
	  const_iterator ocit;

	  for (cit = this->begin (), ocit = other.begin (); this->end () != cit; ++cit, ++ocit)
	    {
	      if (*cit >= *ocit)
		{
		  return false;
		}
	    }
	  return true;
	}
      else
	{
	  return false;
	}
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
	    {
	      return true;
	    }
	  else
	    {
	      const Path &a = *this;
	      Path b = other;
	      unsigned int i;
	      
	      for (i = a.size (); 0 != i; --i)
		{
		  if ((const vector< node_type >&) a == (vector< node_type >&) b)
		    {
		      return true;
		    }
		  b.rotate ();
		}
	      
	      b.reverse ();
	      
	      for (i = a.size (); 0 != i; --i)
		{
		  if ((vector< node_type >&) a == (vector< node_type >&) b)
		    {
		      return true;
		    }
		  b.rotate ();
		}
	    }
	}
      return false;
    }
      
    /**
     * Compares two paths to determine if they differs.  They are
     * compared in both directions and are rotated, i.e. it is to be
     * used with cycles.
     * @param other the Path to compare with this.
     * @return whether the Paths differs.
     */
    bool operator!= (const Path &other) const { return ! operator== (other); }
     
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the value of the Path.
     * @return the Path value.
     */
    valuetype getValue () const { return value; }

    /**
     * Sets the value of the Path.
     * @param the Path value.
     */
    void setValue (const valuetype &v) { value = v; }

    // METHODS --------------------------------------------------------------

    /**
     * Tells if the Path is empty.
     * @return true if there is no element in this.
     */
    bool empty () const { return vector< node_type >::empty (); }
    
    /**
     * Rotates the path.  It pushes the front element to the back of the Path.
     */
    void rotate ()
    {
      push_back (vector< node_type >::front ());
      vector< node_type >::pop_front ();
    }

    /**
     * Gets the size of the Path.
     * @return the size of the Path.
     */
    size_type size () const { return vector< node_type >::size (); }
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the Path to the output stream.
     * @param os the output stream.
     * @return the output stream.
     */
    virtual ostream& write (ostream &os) const
    {
      const_iterator i;

      os << "[ ";
      for (i = vector< node_type >::begin (); vector< node_type >::end () != i; ++i)
	{
	  os << *i << " ";
	}
      os << "] " << value << flush;
      return os;
    }
    
  };

}


namespace std
{

  /**
   * Writes the path to the output stream.
   * @param os the output stream.
   * @param path the Path to write.
   * @return the output stream.
   */
  template < class node_type, class valuetype >
  ostream& operator<< (ostream &os, const mccore::Path< node_type, valuetype > &path)
  {
    return path.write (os);
  }
  
}
  
#endif
