// SymmetricalMatrix.h
// Copyright © 2003-04, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal
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


#ifndef _mccore_SymmetricalMatrix_h_
#define _mccore_SymmetricalMatrix_h_

#include <cmath>
#include <utility>

#include "Binstream.h"
#include "Exception.h"



namespace mccore
{
  /**
   * @short Implementation for a nxn symetrical matrix.
   * 
   * Implements a nxn symetrical matrix where (i,j) = (j,i) 
   * for each i,j in [0,n[, i != j. The diagonal is not defined.
   */
  template< class Type >
  class SymmetricalMatrix 
  {
    /**
     * The one-dimensional emulated n by n matrix.
     */
    Type* matrix;

    /**
     * Size of the one-dimensional matrix.
     */
    int oneSize;

    /**
     * Size of the emulated n by n matrix
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
     * Destroys the object.
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


    template< class Type >
    SymmetricalMatrix< Type >::SymmetricalMatrix (int n, void (*cf) (Type&))
      : twoSize (n),
        cleanup (cf)
    {
      oneSize = (int)((n / 2.0)*(n - 1));
      matrix = new Type[oneSize];
    }


    template< class Type >
    SymmetricalMatrix< Type >::SymmetricalMatrix (const SymmetricalMatrix< Type >& right)
      : oneSize (right.oneSize),
        twoSize (right.twoSize)
    {
      matrix = new Type[oneSize];
      for (int i = 0; i < oneSize; ++i)
      {
        matrix[i] = right.matrix[i];
      }
    }


    template< class Type >
    SymmetricalMatrix< Type >* SymmetricalMatrix< Type >::clone () const
    {
      return new SymmetricalMatrix< Type > (*this);
    }


    template< class Type >
    SymmetricalMatrix< Type >::~SymmetricalMatrix ()
    {
      if (cleanup)
      {
        for (int i = 0; i < oneSize; ++i)
        {
          (*cleanup) (matrix[i]);
        }
      }
      delete[] matrix;
    }


    template< class Type >
    SymmetricalMatrix< Type >& 
    SymmetricalMatrix< Type >::operator= (const SymmetricalMatrix< Type >& right)
    {
      if (this != &right)
      {
        oneSize = right.oneSize;
        twoSize = right.twoSize;
        if (cleanup)
        {
          for (int i = 0; i < oneSize; ++i)
          {
            (*cleanup) (matrix[i]);
          }
        }
        delete[] matrix;
        matrix = new Type[oneSize];
        for (int i = 0; i < oneSize; ++i)
        {
          matrix[i] = right.matrix[i];
        }
      }
      return *this;
    }


    template< class Type >
    Type& SymmetricalMatrix< Type >::operator[] (int i) const
    {
      if (i < 0 || i >= oneSize)
      {
        FatalIntLibException ex ("1x", __FILE__, __LINE__);
        ex << oneSize << " matrix index " << i << "  out of bounds.";
        throw ex;
      }
      return matrix[i];
    }


    template< class Type >
    void SymmetricalMatrix< Type >::clear ()
    {
      if (cleanup)
      {
        for (int i = 0; i < oneSize; ++i)
        {
          (*cleanup) (matrix[i]);
        }
      }
      delete[] matrix;
      oneSize = 0;
      twoSize = 0;
    }


    template< class Type >
    Type& SymmetricalMatrix< Type >::getij (int i, int j) const
    {
      if (i == j || i >= twoSize || j >= twoSize)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << twoSize << 'x' << twoSize << " matrix indexes (" 
        << i << ',' << j << ") out of bounds.";
        throw ex;
      }
      return i < j ?
             matrix[(int)(i*twoSize - 0.5*i*(i + 3) + j - 1)] : 
             matrix[(int)(j*twoSize - 0.5*j*(j + 3) + i - 1)];
    }


    template< class Type >
    void SymmetricalMatrix< Type >::setij (int i, int j, const Type& data)
    {
      if (i == j || i >= twoSize || j >= twoSize)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << twoSize << 'x' << twoSize << " matrix indexes (" 
        << i << ',' << j << ") out of bounds.";
        throw ex;
      }
      if (i < j)
      {
        matrix[(int)(i*twoSize - 0.5*i*(i + 3) + j - 1)] = data;
      }
      else
      {
        matrix[(int)(j*twoSize - 0.5*j*(j + 3) + i - 1)] = data;
      }
    }


    template< class Type >
    iBinstream& SymmetricalMatrix< Type >::read (iBinstream &ibs)
    {
      delete[] matrix;
      ibs >> oneSize >> twoSize;
      matrix = new Type[oneSize];
      for (int i = 0; i < oneSize; ++i)
      {
        ibs >> matrix[i];
      }
      return ibs;
    }

    template< class Type >
    oBinstream& SymmetricalMatrix< Type >::write (oBinstream& obs) const
    {
      obs << oneSize << twoSize;
      for (int i = 0; i < oneSize; ++i)
      {
        obs << matrix[i];
      }
      return obs;
    }

  };

  /**
   * Initialize object from a binary stream.
   * @param ibs the input binstream.
   * @param obj the object read.
   * @return the read binstream.
   */
  template< class Type >
  iBinstream& operator>> (iBinstream &ibs, SymmetricalMatrix< Type > &obj)
  {
    return obj.read (ibs);
  }

  /**
   * Dump object to a binary stream.
   * @param obs the output binstream.
   * @param obj the object to dump.
   * @return the written binstream.
   */
  template< class Type >
  oBinstream& operator<< (oBinstream &obs, const SymmetricalMatrix< Type > &obj)
  {
    return obj.write (obs);
  }

}

#endif
