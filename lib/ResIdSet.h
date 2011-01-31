//                              -*- Mode: C++ -*- 
// ResIdSet.h
// Copyright © 2000-04, 06 Laboratoire de Biologie Informatique et Théorique,
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Oct 26 10:24:02 2000
// $Revision: 1.7 $
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


#ifndef _mccore_ResIdSet_h_
#define _mccore_ResIdSet_h_

#include <set>

#include "ResId.h"
#include "Messagestream.h"
#include "Exception.h"



namespace mccore
{
  class iBinstream;
  class oBinstream;
  
  
  
  /**
   * @short Set of sorted ResId
   * 
   * This class represents the idea of a range of residue id.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   */
  class ResIdSet : public set< ResId >
  {
  public:
    typedef ResId     value_type;
    typedef ResId&    reference;
    typedef ResId*    pointer;
    
  private:  
    /**
     * The index over the set.
     */
    iterator mIndex;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    ResIdSet () : set< ResId > (), mIndex (begin ()) { }
    
    /**
     * Initializes the object with the right's content.
     * @param right the object to copy.
     */
    ResIdSet (const ResIdSet &right)
      : set< ResId > (right), mIndex (right.mIndex) { }
    
    /**
     * Initializes the object with a range of residue id.  See the
     * _parse_and_insert method.
     * @param str the string containing the range.
     */
    ResIdSet (const char *str) { _parse_and_insert (str); }
    
    /**
     * Initializes the object with a residue number and a chain id.
     * @param resno the residue number.
     * @param chainid the chain id (default = ' ').
     */
    ResIdSet (int resno, char chainid = ' ');
    
    /**
     * Destructs the object.
     */
    ~ResIdSet () { }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the object with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    ResIdSet& operator= (const ResIdSet &right);
    
    /**
     * Pre-increases the index.
     * @return itself.
     */
    ResIdSet& operator++ ();
    
    /**
     * Post-increases the index.
     * @param ign ignored parameter.
     * @return a copy of the object.
     */
    ResIdSet operator++ (int ign);
    
    // ACCESS ---------------------------------------------------------------
    
    /**
     * Gets the chain id pointed by the index.
     * @return the chain id.
     */
    char getChainId () const;
    
    /**
     * Gets the residue number pointed by the index.
     * @return the residue number.
     */
    int getResNo () const;
    
    // METHODS --------------------------------------------------------------
    
  private:
    /**
     * Parses and inserts a string describing a range of residue number and
     * chain id.  It's format is:
     * <pre>
     *   multiple range :: <range>
     *                   | <multiple range>,<range>
     *
     *   range          :: <chain id><res no>
     *                   | <chain id><res no n>-<chain id><res no m>
     *     where n < m.
     * </pre>
     * It throws an exception if the range format is invalid.
     * @param str the string to parse.
     * @exception IntLibException.
     */
    void _parse_and_insert (const char *str);
  public:
    
    /**
     * Inserts a range of residue number and chain id in the set via the
     * string defined in _parse_and_insert.
     * @param str the string description of the range.
     * @exception IntLibException
     */
    void insert (const char *str)
    {
      _parse_and_insert (str); 
    }
    
    /**
     * Inserts a residue number and chain id in the set.
     * @param resno the residue number.
     * @param chainid the chain id (default = ' ').
     */
    void insert (int resno, char chainid = ' ');
    
    /**
     * Inserts a ResId in the range.
     * @param resid the residue id to insert.
     */
    void insert (const ResId &resid) { set< ResId >::insert (resid); }
    
    /**
     * Inserts a range of ResId in the object.
     * @param __first the iterator to the first element to insert.
     * @param __last the iterator to the last element to insert.
     */
    template<class _InputIterator>
    void insert (_InputIterator __first, _InputIterator __last)
    { set< ResId >::insert (__first, __last); }
    
    /**
     * Inserts a residue id into the object using a position as a hint to
     * where it will be inserted.
     * @param __pos the position.
     * @param resid the residue id to insert.
     * @return the iterator over the inserted element.
     */
    iterator insert (iterator __pos, const value_type &resid)
    { return set< ResId >::insert (__pos, resid); }
    
    /**
     * Resets the internal iterator to the beginning of the set.
     */
    void reset () { mIndex = begin (); }
    
    // I/O  -----------------------------------------------------------------
    
  };
  
  /**
   * Inputs the residue id set from a binary stream.
   * @param ibs the input binary stream.
   * @param obj the residue id set where to put the residue ids.
   * @return the input binary stream.
   */
  iBinstream& operator>> (iBinstream &ibs, ResIdSet &obj);
  
  /**
   * Outputs the residue id set to a binary stream.
   * @param obs the output binary stream.
   * @param obj the residue id set to output.
   * @return the output binary stream.
   */
  oBinstream& operator<< (oBinstream &obs, const ResIdSet &obj);
  
}


namespace std
{

  /**
   * Outputs the set to an output stream.
   * @param os the output stream.
   * @param residset the set to display.
   * @return the output stream.
   */
  ostream& operator<< (ostream &os, const mccore::ResIdSet &residset);
  
}

#endif
