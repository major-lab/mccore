//                              -*- Mode: C++ -*- 
// CResIdSet.h
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Oct 26 10:24:02 2000
// Last Modified By : Martin Larose
// Last Modified On : Thu Nov  9 10:45:08 2000
// Update Count     : 2
// Status           : Unknown.
// 


#ifndef _CResIdSet_h_
#define _CResIdSet_h_


#include <set.h>

#include "CResId.h"

class ostream;



/**
 * @short Set of sorted CResId
 * 
 * Long Description
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CResIdSet : public set< CResId >
{
  typedef CResId     value_type;
  typedef CResId&    reference;
  typedef CResId*    pointer;
  
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

ostream& operator<< (ostream &os, const CResIdSet &residset);

#endif
