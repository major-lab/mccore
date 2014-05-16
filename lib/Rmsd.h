// Rmsd.h
// Copyright © 2003-06, 2014 Laboratoire de Biologie Informatique et Theorique
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


#ifndef _mccore_Rmsd_h_
#define _mccore_Rmsd_h_

#include "Vector3D.h"
#include "HomogeneousTransfo.h"


namespace mccore
{
  /**
   * A class that encloses RMSD computation as well as optimal
   * superimposition of groups of points.
   * Computation is based on the algorithm by Kabsch, 1976.
   */
  class Rmsd
  {

  private:

    /**
     */
    static int jacobi (double *a, int n, double *d, double *v);


    /**
     */
    static void jacobiRotate (double *a, int i, int j, int k, int l, int n,
                              double s, double tau);


  public:

    /**
     * Calculates the rmsd between two collection of atoms without performing an
     * alignment.  The atom number and types in the collections must match.
     * @param begin_a a begin iterator on the first collection of atoms.
     * @param end_a a end iterator on the first collection of atoms.
     * @param begin_b a begin iterator on the second collection of atoms.
     * @param end_b a end iterator on the second collection of atoms.
     * @return the rmsd value.
     */
    template< class T >
    static float rmsd (T begin_a, T end_a,
                       T begin_b, T end_b)
    {
      float result = 0;
      int count = 0;
      T cii, cij;

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij) 
        {
          result += cii->squareDistance (*cij);
          count++;
        }
      return (float) sqrt (result / (float)count);
    }

    /**
     * Creates a HomogeneousTransfo that moves a to b, that is, if you want
     * to superimpose two structure, a must be transformed by t.
     * @param begin_a a begin iterator on the first collection of atoms.
     * @param end_a a end iterator on the first collection of atoms.
     * @param begin_b a begin iterator on the second collection of atoms.
     * @param end_b a end iterator on the second collection of atoms.     
     * @param t the transfo that expresses a motion from a to b.
     * @return the rmsd value.
     */
    template< class T >
    static float rmsd (T begin_a, T end_a, 
                       T begin_b, T end_b,
                       HomogeneousTransfo &t)
    {
      Vector3D center_a (0, 0, 0);
      Vector3D center_b (0, 0, 0);
      double r[3 * 3];
      double e0;
      int i, j, k;
      int count = 0;
      T cii, cij;

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij)
        {
          center_a += *cii;
          center_b += *cij;
          count++;
        }
 
      center_a /= count;
      center_b /= count;

      // R computation
      memset (r, 0, sizeof (double) * 3 * 3);

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij)
        {
          r[0*3+0] += ((*cij).getX () - center_b.getX ()) * ((*cii).getX () - center_a.getX ());
          r[0*3+1] += ((*cij).getX () - center_b.getX ()) * ((*cii).getY () - center_a.getY ());
          r[0*3+2] += ((*cij).getX () - center_b.getX ()) * ((*cii).getZ () - center_a.getZ ());
          r[1*3+0] += ((*cij).getY () - center_b.getY ()) * ((*cii).getX () - center_a.getX ());
          r[1*3+1] += ((*cij).getY () - center_b.getY ()) * ((*cii).getY () - center_a.getY ());
          r[1*3+2] += ((*cij).getY () - center_b.getY ()) * ((*cii).getZ () - center_a.getZ ());
          r[2*3+0] += ((*cij).getZ () - center_b.getZ ()) * ((*cii).getX () - center_a.getX ());
          r[2*3+1] += ((*cij).getZ () - center_b.getZ ()) * ((*cii).getY () - center_a.getY ());
          r[2*3+2] += ((*cij).getZ () - center_b.getZ ()) * ((*cii).getZ () - center_a.getZ ());
        }

      // E0 computation
      e0 = 0;

      for (cii = begin_a, cij = begin_b;
           cii != end_a && cij != end_b;
           ++cii, ++cij)
        {
          e0 += (pow((*cii).getX() - center_a.getX(), 2)
               + pow((*cii).getY() - center_a.getY(), 2)
               + pow((*cii).getZ() - center_a.getZ(), 2)
               + pow((*cij).getX() - center_b.getX(), 2)
               + pow((*cij).getY() - center_b.getY(), 2)
               + pow((*cij).getZ() - center_b.getZ(), 2));
        }
      e0 /= 2;

      // RR Computation
      double rr[3 * 3];
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          rr[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            rr[i*3+j] += r[k*3+i] * r[k*3+j];
          }
        }
      }

      // Diagonalization
      double mu[3];
      double a[3*3];
      double b[3*3];

      jacobi (rr, 3, mu, a);

      // Sort of eigenvalues and eigenvectors
      for (i = 0; i < 2; ++i)
      {
        for (j = i + 1; j < 3; ++j)
        {
          if (mu[i] < mu[j])
          {
            swap (mu[i], mu[j]);
            swap (a[0*3+i], a[0*3+j]);
            swap (a[1*3+i], a[1*3+j]);
            swap (a[2*3+i], a[2*3+j]);
          }
        }
      }

      a[0*3+2] = a[1*3+0] * a[2*3+1] - a[2*3+0] * a[1*3+1];
      a[1*3+2] = a[2*3+0] * a[0*3+1] - a[0*3+0] * a[2*3+1];
      a[2*3+2] = a[0*3+0] * a[1*3+1] - a[1*3+0] * a[0*3+1];

      // Construction of b
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          b[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            b[i*3+j] += r[i*3+k] * a[k*3+j];
          }
        }
      }

      // Normalization of b
      double l[2];
      l[0] = l[1] = 0;
      for (i = 0; i < 3; ++i)
      {
        l[0] += pow (b[i*3+0], 2);
        l[1] += pow (b[i*3+1], 2);
      }

      l[0] = sqrt(l[0]);
      l[1] = sqrt(l[1]);
      for (i = 0; i < 3; ++i)
      {
        b[i*3+0] /= l[0];
        b[i*3+1] /= l[1];
      }

      double right_b3[3];
      double sigma_3;
      right_b3[0] = b[1*3+0] * b[2*3+1] - b[2*3+0] * b[1*3+1];
      right_b3[1] = b[2*3+0] * b[0*3+1] - b[0*3+0] * b[2*3+1];
      right_b3[2] = b[0*3+0] * b[1*3+1] - b[1*3+0] * b[0*3+1];

      sigma_3 = b[0*3+2] * right_b3[0] + b[1*3+2] * right_b3[1] + b[2*3+2] * right_b3[2];
      if (sigma_3 < 0)
      {
        sigma_3 = -1;
      }
      else
      {
        sigma_3 = 1;
      }

      b[0*3+2] = right_b3[0];
      b[1*3+2] = right_b3[1];
      b[2*3+2] = right_b3[2];

      double result = 2 * (e0 - sqrt(mu[0]) - sqrt(mu[1]) - sigma_3 * sqrt(mu[2])) / count;

      if (result < 0)
      {
        result = 0;
      }
      result = sqrt(result);

      // Construction of U
      double u[3*3];
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          u[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            u[i*3+j] += b[i*3+k] * a[j*3+k];
          }
        }
      }

      HomogeneousTransfo rot ((float) u[0*3+0], (float) u[0*3+1], (float) u[0*3+2], (float) 0,
                              (float) u[1*3+0], (float) u[1*3+1], (float) u[1*3+2], (float) 0,
                              (float) u[2*3+0], (float) u[2*3+1], (float) u[2*3+2], (float) 0);

      t = HomogeneousTransfo().translate(center_b) 
        * rot 
        * HomogeneousTransfo().translate(-center_a);

      return (float) result;
    }


    /**
     * Creates a HomogeneousTransfo that moves a to b, that is, if you
     * want to superimpose two structure, a must be transformed by t.
     * This method is for those concerned with speed and do not want
     * to copy ther atoms in a vector before passing them to this function.
     * @param begin_a a begin iterator on the first collection of atoms.
     * @param end_a a end iterator on the first collection of atoms.
     * @param begin_b a begin iterator on the second collection of atoms.
     * @param end_b a end iterator on the second collection of atoms.     
     * @param t the transfo that expresses a motion from a to b.
     * @return the rmsd value.
     */
    template< class T >
    static float rmsdWithDereference (T begin_a, T end_a,
                                      T begin_b, T end_b,
                                      HomogeneousTransfo &t)
    {
      Vector3D center_a (0, 0, 0);
      Vector3D center_b (0, 0, 0);
      double r[3 * 3];
      double e0;
      int i, j, k;
      int count = 0;
      T cii, cij;

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij)
        {
          center_a += **cii;
          center_b += **cij;
          count++;
        }

      center_a /= count;
      center_b /= count;

      // R computation
      memset (r, 0, sizeof (double) * 3 * 3);

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij)
         {
          r[0*3+0] += ((**cij).getX () - center_b.getX ()) * ((**cii).getX () - center_a.getX ());
          r[0*3+1] += ((**cij).getX () - center_b.getX ()) * ((**cii).getY () - center_a.getY ());
          r[0*3+2] += ((**cij).getX () - center_b.getX ()) * ((**cii).getZ () - center_a.getZ ());
          r[1*3+0] += ((**cij).getY () - center_b.getY ()) * ((**cii).getX () - center_a.getX ());
          r[1*3+1] += ((**cij).getY () - center_b.getY ()) * ((**cii).getY () - center_a.getY ());
          r[1*3+2] += ((**cij).getY () - center_b.getY ()) * ((**cii).getZ () - center_a.getZ ());
          r[2*3+0] += ((**cij).getZ () - center_b.getZ ()) * ((**cii).getX () - center_a.getX ());
          r[2*3+1] += ((**cij).getZ () - center_b.getZ ()) * ((**cii).getY () - center_a.getY ());
          r[2*3+2] += ((**cij).getZ () - center_b.getZ ()) * ((**cii).getZ () - center_a.getZ ());
        }

      // E0 computation
      e0 = 0;

      for (cii = begin_a, cij = begin_b; 
           cii != end_a && cij != end_b; 
           ++cii, ++cij)
        {
          e0 += (pow((**cii).getX() - center_a.getX(), 2)
               + pow((**cii).getY() - center_a.getY(), 2)
               + pow((**cii).getZ() - center_a.getZ(), 2)
               + pow((**cij).getX() - center_b.getX(), 2)
               + pow((**cij).getY() - center_b.getY(), 2)
               + pow((**cij).getZ() - center_b.getZ(), 2));
        }
      e0 /= 2;

      // RR Computation
      double rr[3 * 3];
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          rr[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            rr[i*3+j] += r[k*3+i] * r[k*3+j];
          }
        }
      }

      // Diagonalization
      double mu[3];
      double a[3*3];
      double b[3*3];

      jacobi (rr, 3, mu, a);

      // Sort of eigenvalues and eigenvectors
      for (i = 0; i < 2; ++i)
      {
        for (j = i + 1; j < 3; ++j)
        {
          if (mu[i] < mu[j])
          {
            swap (mu[i], mu[j]);
            swap (a[0*3+i], a[0*3+j]);
            swap (a[1*3+i], a[1*3+j]);
            swap (a[2*3+i], a[2*3+j]);
          }
        }
      }

      a[0*3+2] = a[1*3+0] * a[2*3+1] - a[2*3+0] * a[1*3+1];
      a[1*3+2] = a[2*3+0] * a[0*3+1] - a[0*3+0] * a[2*3+1];
      a[2*3+2] = a[0*3+0] * a[1*3+1] - a[1*3+0] * a[0*3+1];

      // Construction of b
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          b[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            b[i*3+j] += r[i*3+k] * a[k*3+j];
          }
        }
      }

      // Normalization of b
      double l[2];
      l[0] = l[1] = 0;
      for (i = 0; i < 3; ++i)
      {
        l[0] += pow (b[i*3+0], 2);
        l[1] += pow (b[i*3+1], 2);
      }

      l[0] = sqrt(l[0]);
      l[1] = sqrt(l[1]);
      for (i = 0; i < 3; ++i)
      {
        b[i*3+0] /= l[0];
        b[i*3+1] /= l[1];
      }

      double right_b3[3];
      double sigma_3;
      right_b3[0] = b[1*3+0] * b[2*3+1] - b[2*3+0] * b[1*3+1];
      right_b3[1] = b[2*3+0] * b[0*3+1] - b[0*3+0] * b[2*3+1];
      right_b3[2] = b[0*3+0] * b[1*3+1] - b[1*3+0] * b[0*3+1];

      sigma_3 = b[0*3+2] * right_b3[0] + b[1*3+2] * right_b3[1] + b[2*3+2] * right_b3[2];
      if (sigma_3 < 0)
      {
        sigma_3 = -1;
      }
      else 
      {
        sigma_3 = 1;
      }

      b[0*3+2] = right_b3[0];
      b[1*3+2] = right_b3[1];
      b[2*3+2] = right_b3[2];

      double result = 2 * (e0 - sqrt(mu[0]) - sqrt(mu[1]) - sigma_3 * sqrt(mu[2])) / count;

      if (result < 0)
      {
        result = 0;
      }
      result = sqrt(result);

      // Construction of U
      double u[3*3];
      for (i = 0; i < 3; ++i)
      {
        for (j = 0; j < 3; ++j)
        {
          u[i*3+j] = 0;
          for (k = 0; k < 3; ++k)
          {
            u[i*3+j] += b[i*3+k] * a[j*3+k];
          }
        }
      }

      HomogeneousTransfo rot ((float) u[0*3+0], (float) u[0*3+1], (float) u[0*3+2], 0,
                              (float) u[1*3+0], (float) u[1*3+1], (float) u[1*3+2], 0,
                              (float) u[2*3+0], (float) u[2*3+1], (float) u[2*3+2], 0);

      t = HomogeneousTransfo().translate(center_b) 
      * rot 
      * HomogeneousTransfo().translate(-center_a);

      return (float) result;
    }

  };

}

#endif