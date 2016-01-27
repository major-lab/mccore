//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.cc
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// $Revision: 1.27 $
// $Id: HomogeneousTransfo.cc,v 1.27 2006-10-11 17:55:56 thibaup Exp $
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


// cmake generated defines
#include <config.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#else
#include <cmath>
#endif

#include <iomanip>

#include "Binstream.h"
#include "HomogeneousTransfo.h"


namespace mccore 
{

  const float HomogeneousTransfo::alpha_square = 6.927424f;

#define sgn( x ) ( ( ( x ) >= 0.0f ) ? +1 : -1 )

  inline int min3( float x, float y, float z )
  {
    if( ( x >= y ) && ( x >= z ) )
      return 0;
    if( ( y >= x ) && ( y >= z ) )
      return 1;
    return 2;
  }

  
  float
  HomogeneousTransfo::elementAt (unsigned i, unsigned j) const throw (ArrayIndexOutOfBoundsException)
  {
    // emulate random access ...
    switch (i)
    {
    case 0:
      switch (j)
      {
      case 0: return this->m00; break;
      case 1: return this->m01; break;
      case 2: return this->m02; break;
      case 3: return this->m03; break;
      }
      break;
    case 1:
      switch (j)
      {
      case 0: return this->m10; break;
      case 1: return this->m11; break;
      case 2: return this->m12; break;
      case 3: return this->m13; break;
      }
      break;
    case 2:
      switch (j)
      {
      case 0: return this->m20; break;
      case 1: return this->m21; break;
      case 2: return this->m22; break;
      case 3: return this->m23; break;
      }
      break;
    case 3:
      switch (j)
      {
      case 0: return 0.0f; break;
      case 1: return 0.0f; break;
      case 2: return 0.0f; break;
      case 3: return 1.0f; break;
      }
      break;
    }

    ArrayIndexOutOfBoundsException ex ("", __FILE__, __LINE__);
    ex << "index [" << i << ',' << j << "] out of 4X4 matrix bounds.";
    throw ex;

    return 0.0f;
  }


  HomogeneousTransfo 
  HomogeneousTransfo::getRotation () const 
  {
    return HomogeneousTransfo (m00, m01, m02, 0.0f,
		   m10, m11, m12, 0.0f,
		   m20, m21, m22, 0.0f);
  }
  
  
  pair< Vector3D, float >
  HomogeneousTransfo::getRotationVector () const
  {
    float a = m12 - m21;
    float b = m20 - m02;
    float c = m01 - m10;
    float diag = m00 + m11 + m22 - 1;
    float theta;
    
    theta = atan2( sqrt( a*a + b*b + c*c ), diag );
    
    
    // Robot manipulators : mathematics, programming, and control :
    //   the computer control of robot manipulators
    // Paul, Richard P.
    // Cambridge, Mass. : MIT Press, c1981.
    // pp 29-34
    //
    //HomogeneousTransfo mRot  // = Rot(y,90) * Rot(z,90)
    // ( 0, 0, 1, 0,
    //   1, 0, 0, 0,
    //   0, 1, 0, 0 );
    // theta = 120o  axe = ( 1/sqrt(3), 1/sqrt(3), 1/sqrt(3) )
    
    float Kx = 0.0f;
    float Ky = 0.0f;
    float Kz = 0.0f;
    if (theta >= M_PI/2.0f)
    {
      float cost = cos (theta);
      float vers = 1 - cost;
      Kx = sgn (a) * sqrt ((m00 - cost) / vers);
      Ky = sgn (b) * sqrt ((m11 - cost) / vers);
      Kz = sgn (c) * sqrt ((m22 - cost) / vers);
	
      float denom;
      switch (min3 (Kx, Ky, Kz))
      {
      case 0:
	denom = 2 * Kx * vers;
	Ky =  (m01 + m10) / denom;
	Kz =  (m20 + m02) / denom;
	break;
	    
      case 1:
	denom = 2 * Ky * vers;
	Kx =  (m01 + m10) / denom;
	Kz =  (m12 + m21) / denom;
	break;
	    
      default:
	denom = 2 * Kz * vers;
	Kx =  (m20 + m02) / denom;
	Ky =  (m12 + m21) / denom;
	break;
      }
    }
    else
      if (theta > 0.0f)
      {
	float denom = 2.0f * sin (theta);
	Kx = a / denom;
	Ky = b / denom;
	Kz = c / denom;
      }
    
    Vector3D v (Kx, Ky, Kz);
    if (v.length() > 0.0f)
      v.normalize();
    
    return make_pair (v, theta);
  }


  Vector3D
  HomogeneousTransfo::getTranslationVector () const 
  {
    return Vector3D (m03, m13, m23);
  }
  

  HomogeneousTransfo 
  HomogeneousTransfo::getTranslation () const 
  {
    return HomogeneousTransfo (1, 0, 0, m03,
		   0, 1, 0, m13,
		   0, 0, 1, m23);
  }
  
  
  HomogeneousTransfo 
  HomogeneousTransfo::rotation (const Vector3D &axis, float theta) 
  {
    float cosTh;
    float sinTh;
    float versTh;
    float x;
    float y;
    float z;
    
    Vector3D naxis = axis.normalize ();
    
    cosTh = (float) cos (theta);
    sinTh = (float) sin (theta);
    versTh = 1 - cosTh;
    x = naxis.getX ();
    y = naxis.getY ();
    z = naxis.getZ ();

    return HomogeneousTransfo (x * x * versTh + cosTh,
		   x * y * versTh - z * sinTh,
		   x * z * versTh + y * sinTh,
		   0.0f,
		   x * y * versTh + z * sinTh,
		   y * y * versTh + cosTh,
		   y * z * versTh - x * sinTh,
		   0.0f,
		   x * z * versTh - y * sinTh,
		   y * z * versTh + x * sinTh,
		   z * z * versTh + cosTh,
		   0.0f);
  }

  
  HomogeneousTransfo 
  HomogeneousTransfo::rotationX (float theta)
  {
    float a = (float)sin (theta);
    float b = (float)cos (theta);
    return HomogeneousTransfo (1, 0, 0, 0,
		   0, b, -a, 0,
		   0 , a, b, 0);
  }

  
  HomogeneousTransfo 
  HomogeneousTransfo::rotationY (float theta)
  {
    float a = (float) sin (theta);
    float b = (float) cos (theta);
    return HomogeneousTransfo (b, 0, a, 0,
		   0, 1, 0, 0,
		   -a, 0, b, 0);
  }


  HomogeneousTransfo 
  HomogeneousTransfo::rotationZ (float theta)
  {
    float a = (float) sin (theta);
    float b = (float) cos (theta);
    return HomogeneousTransfo (b,-a, 0, 0,
		   a, b, 0, 0,
		   0, 0, 1, 0);
  }

  
  HomogeneousTransfo 
  HomogeneousTransfo::rotate (const Vector3D &axis, float theta) const 
  {
    return (*this * HomogeneousTransfo::rotation (axis, theta));
  }


  HomogeneousTransfo
  HomogeneousTransfo::rotateX (float theta) const
  {
    return (*this * HomogeneousTransfo::rotationX (theta));
  }


  HomogeneousTransfo
  HomogeneousTransfo::rotateY (float theta) const
  {
    return (*this * HomogeneousTransfo::rotationY (theta));
  }


  HomogeneousTransfo
  HomogeneousTransfo::rotateZ (float theta) const
  {
    return (*this * HomogeneousTransfo::rotationZ (theta));
  }

  
  HomogeneousTransfo 
  HomogeneousTransfo::translation (const Vector3D &t) 
  {
    return HomogeneousTransfo::translation (t.getX (), t.getY (), t.getZ ());
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translation (float x, float y, float z) 
  {
    return HomogeneousTransfo(1, 0, 0, x,
		  0, 1, 0, y,
		  0, 0, 1, z);
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translate (const Vector3D &t) const 
  {
    return (*this * HomogeneousTransfo::translation (t));
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translate (float x, float y, float z) const 
  {
    return (*this *HomogeneousTransfo::translation (x, y, z));
  }
  
  
//   float 
//   HomogeneousTransfo::strength () const 
//   {
//     float a = m21 - m12;
//     float b = m02 - m20;
//     float c = m10 - m01;

//     float theta_rad = atan2f (sqrtf (a*a + b*b + c*c), m00 + m11 + m22 - 1.0f);

//     return sqrtf (m03*m03 + m13*m13 + m23*m23 + gc_alpha_square * theta_rad * theta_rad);
//   }


  float 
  HomogeneousTransfo::strength (float& tvalue2, float& rvalue2) const 
  {
    float a = m21 - m12;
    float b = m02 - m20;
    float c = m10 - m01;

    float theta_rad = atan2f (sqrtf (a*a + b*b + c*c), m00 + m11 + m22 - 1.0f);

    return sqrtf ((tvalue2 = m03*m03 + m13*m13 + m23*m23) + 
		  (rvalue2 = HomogeneousTransfo::alpha_square * theta_rad * theta_rad));
  }

  
  float
  HomogeneousTransfo::squareDistance (const HomogeneousTransfo &m) const
  {
    float val;

    val = distance (m);
    return val * val;
  }

  
  double
  HomogeneousTransfo::euclidianRMSD (const HomogeneousTransfo& t) const
  {
    return sqrt ((pow (m01 - t.m01, 2.0) +
		  pow (m02 - t.m02, 2.0) +
		  pow (m03 - t.m03, 2.0) +
		  pow (m11 - t.m11, 2.0) +
		  pow (m12 - t.m12, 2.0) +
		  pow (m13 - t.m13, 2.0) +
		  pow (m21 - t.m21, 2.0) +
		  pow (m22 - t.m22, 2.0) +
		  pow (m23 - t.m23, 2.0)) / 12.0);
  }


  ostream&
  HomogeneousTransfo::write (ostream& os) const 
  {
    int w = 16, p = 11;

    os.setf (ios::right, ios::adjustfield);
    os.setf (ios::fixed, ios::floatfield);
    os.precision (p);
    os << "| " << setw (w) << m00 << " "  // 11
	<< setw (w) << m01 << " " 
	<< setw (w) << m02 << " " 
	<< setw (w) << m03 << " |" << endl;
    os << "| " << setw (w) << m10 << " " 
	<< setw (w) << m11 << " " 
	<< setw (w) << m12 << " " 
	<< setw (w) << m13 << " |" << endl;
    os << "| " << setw (w) << m20 << " " 
	<< setw (w) << m21 << " " 
	<< setw (w) << m22 << " " 
	<< setw (w) << m23 << " |" << endl;
    os << "| " << setw (w) << 0.0f << " " 
	<< setw (w) << 0.0f << " " 
	<< setw (w) << 0.0f << " " 
	<< setw (w) << 1.0f << " |" << endl;  

    return os;
  }
  

  oBinstream&
  HomogeneousTransfo::write (oBinstream& obs) const
  {
//     return obs << m00 << m01 << m02 << m03 
// 	       << m10 << m11 << m12 << m13 
// 	       << m20 << m21 << m22 << m23;
    // temporary backward compatibility
    return obs << m00 << m10 << m20 << 0.0f
	       << m01 << m11 << m21 << 0.0f
	       << m02 << m12 << m22 << 0.0f
	       << m03 << m13 << m23 << 1.0f; 
  }


  iBinstream&
  HomogeneousTransfo::read (iBinstream& ibs)
  {
    // temporary backward compatibility
    float ign;
    ibs >> m00 >> m10 >> m20 >> ign
	>> m01 >> m11 >> m21 >> ign
	>> m02 >> m12 >> m22 >> ign
	>> m03 >> m13 >> m23 >> ign; 
    return ibs; 

//     return ibs >> m00 >> m01 >> m02 >> m03 
// 	       >> m10 >> m11 >> m12 >> m13 
// 	       >> m20 >> m21 >> m22 >> m23;    
  }
  

  oBinstream&
  operator<< (oBinstream& obs, const HomogeneousTransfo& obj)
  {
    return obj.write (obs);
  }
  

  iBinstream&
  operator>> (iBinstream& ibs, HomogeneousTransfo& obj)
  {
    return obj.read (ibs);
  }
  
}

namespace std
{
  ostream&
  operator<< (ostream& os, const mccore::HomogeneousTransfo& obj)
  {
    return obj.write (os);
  }
}
