//                              -*- Mode: C++ -*- 
// SymmetricalMatrix.cc
// Copyright © 2003-03 Laboratoire de Biologie Informatique et Théorique
// Author           : Philippe Thibault
// Created On       : Wed Oct 16 09:28:54 2002
// $Revision: 1.4.4.1 $
// $Id: SymmetricalMatrix.cc,v 1.4.4.1 2003-12-10 14:20:10 larosem Exp $
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


#ifndef __SymmetricalMatrix_cc_
#define __SymmetricalMatrix_cc_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>

#include "Binstream.h"
#include "CException.h"



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
    matrix[i] = right.matrix[i];
}


template< class Type >
SymmetricalMatrix< Type >*
SymmetricalMatrix< Type >::clone () const
{
  return new SymmetricalMatrix< Type > (*this);
}


template< class Type >
SymmetricalMatrix< Type >::~SymmetricalMatrix ()
{
  if (cleanup)
    for (int i = 0; i < oneSize; ++i)
      (*cleanup) (matrix[i]); 
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
	for (int i = 0; i < oneSize; ++i)
	  (*cleanup) (matrix[i]);
      delete[] matrix;
      matrix = new Type[oneSize];
      for (int i = 0; i < oneSize; ++i)
	matrix[i] = right.matrix[i];
    }
  return *this;
}


template< class Type >
Type&
SymmetricalMatrix< Type >::operator[] (int i) const
{
  if (i < 0 || i >= oneSize)
    {
      CFatalIntLibException ex ("1x", __FILE__, __LINE__);
      ex << oneSize << " matrix index " << i << "  out of bounds.";
      throw ex;
    }
  return matrix[i];
}


template< class Type >
void
SymmetricalMatrix< Type >::clear ()
{
  if (cleanup)
    for (int i = 0; i < oneSize; ++i)
      (*cleanup) (matrix[i]);
  delete[] matrix;
  oneSize = 0;
  twoSize = 0;
}


template< class Type >
Type&
SymmetricalMatrix< Type >::getij (int i, int j) const
{
  if (i == j || i >= twoSize || j >= twoSize)
    {
      CFatalIntLibException ex ("", __FILE__, __LINE__);
      ex << twoSize << 'x' << twoSize << " matrix indexes (" 
	 << i << ',' << j << ") out of bounds.";
      throw ex;
    }
  return i < j ? 
   matrix[(int)(i*twoSize - 0.5*i*(i + 3) + j - 1)] : 
   matrix[(int)(j*twoSize - 0.5*j*(j + 3) + i - 1)];
}


template< class Type >
void
SymmetricalMatrix< Type >::setij (int i, int j, const Type& data)
{
  if (i == j || i >= twoSize || j >= twoSize)
    {
      CFatalIntLibException ex ("", __FILE__, __LINE__);
      ex << twoSize << 'x' << twoSize << " matrix indexes (" 
	 << i << ',' << j << ") out of bounds.";
      throw ex;
    }
  if (i < j)
    matrix[(int)(i*twoSize - 0.5*i*(i + 3) + j - 1)] = data;
  else
    matrix[(int)(j*twoSize - 0.5*j*(j + 3) + i - 1)] = data;
}


template< class Type >
iBinstream&
SymmetricalMatrix< Type >::read (iBinstream &ibs)
{
  delete[] matrix;
  ibs >> oneSize >> twoSize;
  matrix = new Type[oneSize];
  for (int i = 0; i < oneSize; ++i)
    ibs >> matrix[i];
  return ibs;
}


template< class Type >
oBinstream&
SymmetricalMatrix< Type >::write (oBinstream& obs) const
{
  obs << oneSize << twoSize;
  for (int i = 0; i < oneSize; ++i)
    obs << matrix[i];
  return obs;
}

#endif
