//                              -*- Mode: C++ -*- 
// CResIdSet.h
// Copyright © 2000-03 Laboratoire de Biologie Informatique et Théorique,
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Oct 26 10:24:02 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri Oct  5 16:56:58 2001
// Update Count     : 6
// Status           : Ok.
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


#ifndef _CResIdSet_h_
#define _CResIdSet_h_

#include <iostream>
#include <set>

#include "CResId.h"

class iBinstream;
class oBinstream;

using namespace std;



/**
 * @short Set of sorted CResId
 * 
 * This class represents the idea of a range of residue id.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CResIdSet : public set< CResId >
{
public:
  typedef CResId     value_type;
  typedef CResId&    reference;
  typedef CResId*    pointer;

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
  CResIdSet () : set< CResId > (), mIndex (begin ()) { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CResIdSet (const CResIdSet &right)
    : set< CResId > (right), mIndex (right.mIndex) { }

  /**
   * Initializes the object with a range of residue id.  See the
   * _parse_and_insert method.
   * @param str the string containing the range.
   */
  CResIdSet (const char *str) { _parse_and_insert (str); }

  /**
   * Initializes the object with a residue number and a chain id.
   * @param resno the residue number.
   * @param chainid the chain id (default = ' ').
   */
  CResIdSet (int resno, char chainid = ' ');
  
  /**
   * Destructs the object.
   */
  ~CResIdSet () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  CResIdSet& operator= (const CResIdSet &right);

  /**
   * Pre-increases the index.
   * @return itself.
   */
  CResIdSet& operator++ ();

  /**
   * Post-increases the index.
   * @param ign ignored parameter.
   * @return a copy of the object.
   */
  CResIdSet operator++ (int ign);

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the chain id pointed by the index.
   * @return the chain id.
   */
  char GetChainId () const;

  /**
   * Gets the residue number pointed by the index.
   * @return the residue number.
   */
  int GetResNo () const;
  
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
   * @exception CIntLibException.
   */
  void _parse_and_insert (const char *str);
public:
  
  /**
   * Inserts a range of residue number and chain id in the set via the
   * string defined in _parse_and_insert.
   * @param str the string description of the range.
   */
  void insert (const char *str) { _parse_and_insert (str); }
  
  /**
   * Inserts a residue number and chain id in the set.
   * @param resno the residue number.
   * @param chainid the chain id (default = ' ').
   */
  void insert (int resno, char chainid = ' ');

  /**
   * Inserts a CResId in the range.
   * @param resid the residue id to insert.
   */
  void insert (const CResId &resid) { set< CResId >::insert (resid); }
  
  /**
   * Inserts a range of CResId in the object.
   * @param __first the iterator to the first element to insert.
   * @param __last the iterator to the last element to insert.
   */
  template<class _InputIterator>
  void insert (_InputIterator __first, _InputIterator __last)
  { set< CResId >::insert (__first, __last); }

  /**
   * Inserts a residue id into the object using a position as a hint to
   * where it will be inserted.
   * @param __pos the position.
   * @param resid the residue id to insert.
   * @return the iterator over the inserted element.
   */
  iterator insert (iterator __pos, const value_type &resid)
  { return set< CResId >::insert (__pos, resid); }
  
  /**
   * Resets the internal iterator to the beginning of the set.
   */
  void Reset () { mIndex = begin (); }
  
  // I/O  -----------------------------------------------------------------

};



/**
 * Outputs the set to an output stream.
 * @param os the output stream.
 * @param residset the set to display.
 * @return the output stream.
 */
ostream& operator<< (ostream &os, const CResIdSet &residset);

/**
 * Inputs the residue id set from a binary stream.
 * @param ibs the input binary stream.
 * @param obj the residue id set where to put the residue ids.
 * @return the input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, CResIdSet &obj);



/**
 * Outputs the residue id set to a binary stream.
 * @param obs the output binary stream.
 * @param obj the residue id set to output.
 * @return the output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const CResIdSet &obj);

#endif
