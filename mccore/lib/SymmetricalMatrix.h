//                              -*- Mode: C++ -*- 
// SymmetricalMatrix.h
// Copyright © 2003-03 Laboratoire de Biologie Informatique et Théorique
// Author           : Philippe Thibault
// Created On       : Wed Oct 16 09:28:54 2002
// $Revision: 1.4 $
// $Id: SymmetricalMatrix.h,v 1.4 2003-12-23 14:58:09 larosem Exp $
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


#ifndef _SymmetricalMatrix_h_
#define _SymmetricalMatrix_h_

#include <utility>

namespace mccore {
  class iBinstream;
  class oBinstream;
}

using namespace mccore;



/**
 * @short Implementation for a nxn symetrical matrix.
 * 
 * Implements a nxn symetrical matrix where (i,j) = (j,i) 
 * for each i,j in [0,n[, i != j. The diagonal is not defined.
 *
 * @author Philippe Thibault
 */
template< class Type >
class SymmetricalMatrix 
{

  /**
   * The one-dimensional emulated nxn matrix.
   */
  Type* matrix;

  /**
   * Size of the one-dimensional matrix.
   */
  int oneSize;

  /**
   * Size of the emulated nxn matrix
   */
  int twoSize;

  /**
   * User-defined data cleanup method.
   */
  void (*cleanup) (Type&);

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  SymmetricalMatrix (int n = 1, void (*cf) (Type&) = NULL);

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  SymmetricalMatrix (const SymmetricalMatrix &right);

  /**
   * Clones the object.
   * @return a copy of itself.
   */
  SymmetricalMatrix* clone () const;

  /**
   * Destructs the object.
   */
  ~SymmetricalMatrix ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  SymmetricalMatrix& operator= (const SymmetricalMatrix &right);

  /**
   * Access the one-dimensional matrix ith data.
   * @param i the index.
   * @return the ith data.
   */
  Type& operator[] (int i) const;

  /**
   * Access the two-dimensional matrix data at (i,j).
   * @param i the row index.
   * @param j the column index.
   * @return the data at (i,j).
   */
  Type& operator[] (std::pair< int, int > ij) const { return getij (ij.first, ij.second); }

  /**
   * Access the two-dimensional matrix data at (i,j).
   * @param i the row index.
   * @param j the column index.
   * @return the data at (i,j).
   */
  Type& operator[] (int ij[2]) const { return getij (ij[0], ij[1]); }

  Type& operator() (int i, int j) const { return getij (i, j); }

  // ACCESS ---------------------------------------------------------------

  /**
   * Return the data stored at index (i,j).
   * @param i ith row.
   * @param j jth column.
   * @return the data indexed. 
   */
  Type& getij (int i, int j) const;

  /**
   * Store data at index (i,j).
   * @param i ith row.
   * @param j jth column.
   * @param data the data to store. 
   */
  void setij (int i, int j, const Type& data);

  int size (int d = 2) { return d == 2 ? twoSize : oneSize; } 

  // METHODS --------------------------------------------------------------

  void clear ();

  // I/O  -----------------------------------------------------------------

  /**
   * Initialize from a binary stream.
   * @param ibs the input binstream.
   * @return the read binstream. 
   */ 
  iBinstream& read (iBinstream &ibs);

  /**
   * Dump to a binary stream.
   * @param obs the output binstream.
   * @return the written binstream.
   */
  oBinstream& write (oBinstream& obs) const;
};

/**
 * Initialize object from a binary stream.
 * @param ibs the input binstream.
 * @param obj the object read.
 * @return the read binstream. 
 */ 
template< class Type >
iBinstream& operator>> (iBinstream &ibs, SymmetricalMatrix< Type > &obj)
{ return obj.read (ibs); }

/**
 * Dump object to a binary stream.
 * @param obs the output binstream.
 * @param obj the object to dump.
 * @return the written binstream.
 */
template< class Type >
oBinstream& operator<< (oBinstream &obs, const SymmetricalMatrix< Type > &obj)
{ return obj.write (obs); }


#include "SymmetricalMatrix.cc"

#endif
