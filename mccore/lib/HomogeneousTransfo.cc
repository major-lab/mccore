//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Mar 20 19:48:28 2003
// Update Count     : 18
// Status           : Unknown.
// 



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>

#include "Binstream.h"
#include "HomogeneousTransfo.h"

namespace mccore 
{

HomogeneousTransfo& 
HomogeneousTransfo::operator= (const HomogeneousTransfo &other)
{
  if (this != &other)
    {
      if (!matrix) matrix = new float[16];
      memcpy (matrix, other.matrix, 16*sizeof (float));
    }
  return *this;
}


// I/O  -----------------------------------------------------------------


ostream &
HomogeneousTransfo::output (ostream &out) const 
{
  out.setf (ios::right, ios::adjustfield);
  out.setf (ios::fixed, ios::floatfield);
  out.precision (3);
  out << "| " << setw (8) << matrix[0] << " " 
      << setw (8) << matrix[4] << " " 
      << setw (8) << matrix[8] << " " 
      << setw (8) << matrix[12] << " |" << endl;
  out << "| " << setw (8) << matrix[1] << " " 
      << setw (8) << matrix[5] << " " 
      << setw (8) << matrix[9] << " " 
      << setw (8) << matrix[13] << " |" << endl;
  out << "| " << setw (8) << matrix[2] << " " 
      << setw (8) << matrix[6] << " " 
      << setw (8) << matrix[10] << " " 
      << setw (8) << matrix[14] << " |" << endl;
 out << "| " << setw (8) << matrix[3] << " " 
      << setw (8) << matrix[7] << " " 
      << setw (8) << matrix[11] << " " 
      << setw (8) << matrix[15] << " |" << endl;  
  return out;
}


ostream &
operator<< (ostream &out, const HomogeneousTransfo &v)
{
  return v.output (out);
}


iBinstream&
operator>> (iBinstream &ibs, HomogeneousTransfo &obj)
{
  int i;

  for (i = 0; i < 16; ++i)
    {
      float x;

      ibs >> x;
      obj.setElementAt (x, i);
    }
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const HomogeneousTransfo &obj)
{
  int i;
  
  for (i = 0; i < 16; ++i)
    obs << obj.elementAt (i);
  return obs;
}

}
