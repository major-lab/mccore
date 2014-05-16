// Rmsd.cc
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

#include <config.h>

#include "Rmsd.h"



namespace mccore
{

  int Rmsd::jacobi (double *a, int n, double *d, double *v)
  {
    int ip, iq, j;
    double *b;
    double *z;
    int nrot;

    // Initializing to the identity matrix
    for (int ip = 0; ip < n; ++ip)
    {
      for (int iq = 0; iq < n; ++iq)
      {
        v[ip*n+iq] = (ip == iq) ? 1 : 0;
      }
    }

    // Initialize b and d to the diagonal of a
    b = new double[n];
    z = new double[n];
    for (int ip = 0; ip < n; ++ip)
    {
      b[ip] = d[ip] = a[ip*n+ip];
      z[ip] = 0;
    }

    nrot = 0;
    for (int it = 0; it < 50; ++it)
    {
      double tresh;
      double theta;
      double tau;
      double t;
      double s;
      double h;
      double g;
      double c;
      double sm;

      sm = 0;
      for (ip = 0; ip < n-1; ++ip)
      {
        for (iq = ip+1; iq < n; ++iq)
        {
          sm += fabs (a[ip*n+iq]);
        }
      }

      if (sm == 0)
      {
        delete[] z;
        delete[] b;
        return nrot;
      }

      if (it < 3)
      {
        tresh = 0.2 * sm / (n * n);
      }
      else 
      {
        tresh = 0;
      }

      for (ip = 0; ip < n - 1; ++ip)
      {
        for (iq = ip + 1; iq < n; ++iq)
        {
          g = (double)100 * fabs(a[ip*n+iq]);
          if (it > 3
              && (double)fabs(d[ip]) + g == (double)fabs(d[ip])
              && (double)fabs(d[iq]) + g == (double)fabs(d[iq])) 
          {
            a[ip*n+iq] = (double)0;
          }
          else
          {
            if (fabs(a[ip*n+iq]) > tresh)
            {
              h = d[iq] - d[ip];
              if ((double)fabs(h) + g == (double)fabs(h))
              { 
                t = (a[ip*n+iq]) / h;
              }
              else 
              {
                theta = (double)0.5 * h / (a[ip*n+iq]);
                t = (double)1.0 / (fabs(theta) + sqrt((double)1.0 + theta * theta));
                if (theta < 0.0)
                {
                  t = -t;
                }
              }
              c = (double)1.0 / sqrt((double)1.0 + t * t);
              s = t * c;
              tau = s / ((double)1.0 + c);
              h = t * a[ip*n+iq];
              z[ip] -= h;
              z[iq] += h;
              d[ip] -= h;
              d[iq] += h;
              a[ip*n+iq] = 0.0;
              for (j = 0; j <= ip - 1; ++j)
              {
                Rmsd::jacobiRotate(a, j, ip, j, iq, n, s, tau);
              }
              for (j = ip+1; j <= iq-1; ++j)
              {
                Rmsd::jacobiRotate(a, ip, j, j, iq, n, s, tau);
              }
              for (j = iq+1; j < n; ++j)
              {
                Rmsd::jacobiRotate(a, ip, j, iq, j, n, s, tau);
              }
              for (j = 0; j < n; ++j)
              {
                Rmsd::jacobiRotate(v, j, ip, j, iq, n, s, tau);
              }
              ++nrot;
            }
          }
        }
      }

      for (ip = 0; ip < n; ++ip)
      {
        b[ip] += z[ip];

        // this assumes that all d[i] >= 0 (?)
        d[ip] = b[ip] < 0.0 ? 0.0 : b[ip];
        z[ip] = 0;
      }
    }
    delete[] z;
    delete[] b;
    return nrot;
  }


  void Rmsd::jacobiRotate (double *a, int i, int j, int k, int l, int n,
                           double s, double tau)
  {
    double g;
    double h;

    g = a[i * n + j];
    h = a[k * n + l];
    a[i * n + j] = g - s * (h + g * tau);
    a[k * n + l] = h + s * (g - h * tau);
  }

}
