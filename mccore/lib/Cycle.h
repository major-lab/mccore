//                              -*- Mode: C++ -*- 
// Cycle.h
// Copyright © 2005-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Feb  2 15:34:32 2005
// $Revision: 1.3 $
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


#ifndef _mccore_Cycle_h_
#define _mccore_Cycle_h_

#include <iostream>

#include "Path.h"

using namespace std;



namespace mccore
{
  template< class V,
	    class W >
  class Cycle : public Path< V, W >
  {
    /**
     * The index of p in the cycle.
     */
    unsigned int p;
      
    /**
     * The index of q in the cycle.
     */
    unsigned int q;

  public:
      
    // LIFECYCLE ------------------------------------------------------------
      
    /**
     * Initializes the object.
     */
    Cycle () { }
      
    /**
     * Initializes the object with the other's content.
     * @param right the Path to copy.
     */
    Cycle (const Path< V, W > &right)
      : Path< V, W > (right),
	p (0),
	q (0)
    { }

    /**
     * Initializes the object with the other's content.
     * @param right the Cycle to copy.
     */
    Cycle (const Cycle &right)
      : Path< V, W > (right),
	p (right.p),
	q (right.q)
    { }

    /**
     * Clones the Cycle in a new object.
     * @return a copy of this.
     */
    virtual Path< V, W >* clone () const { return new Cycle (*this); }
      
    /**
     * Destroys the object.
     */
    virtual ~Cycle () { }

    // OPERATORS ------------------------------------------------------------
      
    /**
     * Assigns the object with the other's content.
     * @param right the Cycle to copy.
     * @return itself.
     */
    Cycle& operator= (const Cycle &right)
    {
      if  (this != &right)
	{
	  Path< V, W>::operator= (right);
	  p = right.p;
	  q = right.q;
	}
      return *this;
    }

    /**
     * Determines if this cycle is shorter that the other.
     * @param other another path.
     * @return true if this path is shorter.
     */
    bool operator< (const Cycle &right) const
    {
      return Path< V, W >::operator< (right);
    }
      
    /**
     * Compares two cycles to determine if they are equal.  They are
     * compared in both directions and are rotated, i.e. it is to be
     * used with cycles.
     */
    bool operator== (const Cycle &right) const
    {
      return (Path< V, W >::operator== (right) && p == right.p && q == right.q);
    }

    /**
     * Compares two cycles to determine if they differs.
     * @param right the Cycle to compare with this.
     * @return whether the cycles differs.
     */
    bool operator!= (const Cycle &right) const { return ! operator== (right); }

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the value of r in the cycle.
     * @return the value of r.
     */
    const V& getR () const { return this->front (); }
      
    /**
     * Gets the value of p in the cycle.
     * @return the value at the p index.
     */
    const V& getP () const { return this->operator[] (p); }
      
    /**
     * Gets the r to p Path.
     * @return the r to p Path.
     */
    Path< V, W > getRP () const
    {
      return Path< V, W > (this->begin (), this->begin () + p);
    }
      
    /**
     * Sets the p index.
     * @param p the p index.
     */
    void setP (unsigned int p) { this->p = p; }
      
    /**
     * Gets y value.
     * @return the value at y index.
     */
    const V& getY () const { return this->operator[] (p + 1); }
      
    /**
     * Gets the r to q Path.
     * @return the r to q Path.
     */
    Path< V, W > getRQ () const
    {
      return Path< V, W > (this->rbegin (), this->rbegin () + q);
    }
      
    /**
     * Gets the value of q in the Cycle.
     * @return the value at q index.
     */
    const V& getQ () const { return this->operator[] (q); }
      
    /**
     * Sets the q index.
     * @param q the q index.
     */
    void setQ (unsigned int q) { this->q = q; }
      
    // METHODS --------------------------------------------------------------
      
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the Cycle to the output stream os.
     * @param os the output stream.
     * @return the output stream.
     */
    virtual ostream &write (ostream &os) const
    {
      Path< V, W >::write (os) << " r = " << getR ()
			       << " p = " << getP ()
			       << " q = " << getQ ();
      if (0 == this->size () % 2)
	{
	  os << " y = " << getY ();
	}
      return os;
    }
      
  };
}



namespace std
{

  /**
   * Writes the cycle to the output stream.
   * @param os the output stream.
   * @param cycle the Cycle to write.
   * @return the output stream.
   */
  template < class V, class W >
  ostream& operator<< (ostream &os, const mccore::Cycle< V, W > &cycle)
  {
    return cycle.write (os);
  }
  
}
  
#endif
