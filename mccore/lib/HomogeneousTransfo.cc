//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// $Revision: 1.6 $
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




#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>

#include "Binstream.h"
#include "HomogeneousTransfo.h"
#include "CException.h"

namespace mccore 
{

#define sgn( x ) ( ( ( x ) >= 0.0 ) ? +1 : -1 )

  inline int min3( float x, float y, float z )
  {
    if( ( x >= y ) && ( x >= z ) )
      return 0;
    if( ( y >= x ) && ( y >= z ) )
      return 1;
    return 2;
  }
  

  // LIFECYCLE ------------------------------------------------------------

  HomogeneousTransfo::HomogeneousTransfo () 
  { 
    matrix = new float[16];
    setIdentity (); 
  }
  

  HomogeneousTransfo::HomogeneousTransfo(float n00, float n01, float n02, float n03,
					 float n10, float n11, float n12, float n13,
					 float n20, float n21, float n22, float n23,
					 float n30, float n31, float n32, float n33) 
  {
    matrix = new float[16];
    set(n00, n01, n02, n03, 
	n10, n11, n12, n13, 
	n20, n21, n22, n23,
	n30, n31, n32, n33);
  }


  HomogeneousTransfo::HomogeneousTransfo (const float* openGLMatrix) 
  {
    matrix = new float[16];
    memcpy (matrix, openGLMatrix, 16*sizeof (float));
  }
  
  
  HomogeneousTransfo::HomogeneousTransfo (const HomogeneousTransfo &other) 
  {
    matrix = new float[16];
    memcpy (matrix, other.matrix, 16*sizeof (float));
  }


  HomogeneousTransfo::~HomogeneousTransfo () 
  {
    delete matrix;
  }


  // OPERATORS ------------------------------------------------------------


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
  

   // ACCESS ---------------------------------------------------------------


  void HomogeneousTransfo::set(float n00, float n01, float n02, float n03,
			       float n10, float n11, float n12, float n13,
			       float n20, float n21, float n22, float n23,
			       float n30, float n31, float n32, float n33) {
    matrix[ 0] = n00; matrix[ 4] = n01; matrix[ 8] = n02; matrix[12] = n03;
    matrix[ 1] = n10; matrix[ 5] = n11; matrix[ 9] = n12; matrix[13] = n13;
    matrix[ 2] = n20; matrix[ 6] = n21; matrix[10] = n22; matrix[14] = n23;
    matrix[ 3] = n30; matrix[ 7] = n31; matrix[11] = n32; matrix[15] = n33;
  }
  

  void HomogeneousTransfo::setIdentity() {
    set (1.0f, 0.0f, 0.0f, 0.0f, 
	 0.0f, 1.0f, 0.0f, 0.0f, 
	 0.0f, 0.0f, 1.0f, 0.0f, 
	 0.0f, 0.0f, 0.0f, 1.0f);
  }
  
  
  bool HomogeneousTransfo::isIdentity() {
    return (matrix[0] == 1 && matrix[ 4] == 0 && matrix[ 8] == 0 && matrix[12] == 0
	    && matrix[1] == 0 && matrix[ 5] == 1 && matrix[ 9] == 0 && matrix[13] == 0
	    && matrix[2] == 0 && matrix[ 6] == 0 && matrix[10] == 1 && matrix[14] == 0
	    && matrix[3] == 0 && matrix[ 7] == 0 && matrix[11] == 0 && matrix[15] == 1);
  }


  // METHODS --------------------------------------------------------------

  
  HomogeneousTransfo 
  HomogeneousTransfo::operator* (const HomogeneousTransfo &right) const 
  {
    return HomogeneousTransfo 
      (matrix[0] * right.matrix[0] + matrix[4] * right.matrix[1] + matrix[8] * right.matrix[2] + matrix[12] * right.matrix[3],
       matrix[0] * right.matrix[4] + matrix[4] * right.matrix[5] + matrix[8] * right.matrix[6] + matrix[12] * right.matrix[7],
       matrix[0] * right.matrix[8] + matrix[4] * right.matrix[9] + matrix[8] * right.matrix[10] + matrix[12] * right.matrix[11],
       matrix[0] * right.matrix[12] + matrix[4] * right.matrix[13] + matrix[8] * right.matrix[14] + matrix[12] * right.matrix[15],
       
       matrix[1] * right.matrix[0] + matrix[5] * right.matrix[1] + matrix[9] * right.matrix[2] + matrix[13] * right.matrix[3],
       matrix[1] * right.matrix[4] + matrix[5] * right.matrix[5] + matrix[9] * right.matrix[6] + matrix[13] * right.matrix[7],
       matrix[1] * right.matrix[8] + matrix[5] * right.matrix[9] + matrix[9] * right.matrix[10] + matrix[13] * right.matrix[11],
       matrix[1] * right.matrix[12] + matrix[5] * right.matrix[13] + matrix[9] * right.matrix[14] + matrix[13] * right.matrix[15],
       
       matrix[2] * right.matrix[0] + matrix[6] * right.matrix[1] + matrix[10] * right.matrix[2] + matrix[14] * right.matrix[3],
       matrix[2] * right.matrix[4] + matrix[6] * right.matrix[5] + matrix[10] * right.matrix[6] + matrix[14] * right.matrix[7],
       matrix[2] * right.matrix[8] + matrix[6] * right.matrix[9] + matrix[10] * right.matrix[10] + matrix[14] * right.matrix[11],
       matrix[2] * right.matrix[12] + matrix[6] * right.matrix[13] + matrix[10] * right.matrix[14] + matrix[14] * right.matrix[15],
       
       matrix[3] * right.matrix[0] + matrix[7] * right.matrix[1] + matrix[11] * right.matrix[2] + matrix[15] * right.matrix[3],
       matrix[3] * right.matrix[4] + matrix[7] * right.matrix[5] + matrix[11] * right.matrix[6] + matrix[15] * right.matrix[7],
       matrix[3] * right.matrix[8] + matrix[7] * right.matrix[9] + matrix[11] * right.matrix[10] + matrix[15] * right.matrix[11],
       matrix[3] * right.matrix[12] + matrix[7] * right.matrix[13] + matrix[11] * right.matrix[14] + matrix[15] * right.matrix[15]);	     
  }


  HomogeneousTransfo& 
  HomogeneousTransfo::operator*= (const HomogeneousTransfo &right) 
  {
    set (matrix[0] * right.matrix[0] + matrix[4] * right.matrix[1] + matrix[8] * right.matrix[2] + matrix[12] * right.matrix[3],
	 matrix[0] * right.matrix[4] + matrix[4] * right.matrix[5] + matrix[8] * right.matrix[6] + matrix[12] * right.matrix[7],
	 matrix[0] * right.matrix[8] + matrix[4] * right.matrix[9] + matrix[8] * right.matrix[10] + matrix[12] * right.matrix[11],
	 matrix[0] * right.matrix[12] + matrix[4] * right.matrix[13] + matrix[8] * right.matrix[14] + matrix[12] * right.matrix[15],
	 
	 matrix[1] * right.matrix[0] + matrix[5] * right.matrix[1] + matrix[9] * right.matrix[2] + matrix[13] * right.matrix[3],
	 matrix[1] * right.matrix[4] + matrix[5] * right.matrix[5] + matrix[9] * right.matrix[6] + matrix[13] * right.matrix[7],
	 matrix[1] * right.matrix[8] + matrix[5] * right.matrix[9] + matrix[9] * right.matrix[10] + matrix[13] * right.matrix[11],
	 matrix[1] * right.matrix[12] + matrix[5] * right.matrix[13] + matrix[9] * right.matrix[14] + matrix[13] * right.matrix[15],
	 
	 matrix[2] * right.matrix[0] + matrix[6] * right.matrix[1] + matrix[10] * right.matrix[2] + matrix[14] * right.matrix[3],
	 matrix[2] * right.matrix[4] + matrix[6] * right.matrix[5] + matrix[10] * right.matrix[6] + matrix[14] * right.matrix[7],
	 matrix[2] * right.matrix[8] + matrix[6] * right.matrix[9] + matrix[10] * right.matrix[10] + matrix[14] * right.matrix[11],
	 matrix[2] * right.matrix[12] + matrix[6] * right.matrix[13] + matrix[10] * right.matrix[14] + matrix[14] * right.matrix[15],
	 
	 matrix[3] * right.matrix[0] + matrix[7] * right.matrix[1] + matrix[11] * right.matrix[2] + matrix[15] * right.matrix[3],
	 matrix[3] * right.matrix[4] + matrix[7] * right.matrix[5] + matrix[11] * right.matrix[6] + matrix[15] * right.matrix[7],
	 matrix[3] * right.matrix[8] + matrix[7] * right.matrix[9] + matrix[11] * right.matrix[10] + matrix[15] * right.matrix[11],
	 matrix[3] * right.matrix[12] + matrix[7] * right.matrix[13] + matrix[11] * right.matrix[14] + matrix[15] * right.matrix[15]);
    return *this;
  }


  Vector3D 
  HomogeneousTransfo::operator* (const Vector3D &v) const 
  {
    return Vector3D(matrix[0]*v.getX () + matrix[4]*v.getY () + matrix[8]*v.getZ () + matrix[12],  
		    matrix[1]*v.getX () + matrix[5]*v.getY () + matrix[9]*v.getZ () + matrix[13], 
		    matrix[2]*v.getX () + matrix[6]*v.getY () + matrix[10]*v.getZ () + matrix[14]);
  }


  HomogeneousTransfo 
  HomogeneousTransfo::getRotation () const 
  {
    return HomogeneousTransfo (matrix[0], matrix[4], matrix[8],  0,
			       matrix[1], matrix[5], matrix[9],  0,
			       matrix[2], matrix[6], matrix[10], 0,
			       0, 0, 0, 1);
  }
  
  



  pair< Vector3D, float >
  HomogeneousTransfo::getRotationVector () const
  {
    float a = matrix[9] - matrix[6];
    float b = matrix[2] - matrix[8];
    float c = matrix[4] - matrix[1];
    float diag = matrix[0] + matrix[5] + matrix[10] - 1;
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
    
    float Kx = 0.0;
    float Ky = 0.0;
    float Kz = 0.0;
    if (theta >= M_PI/2.0)
      {
	float cost = cos (theta);
	float vers = 1 - cost;
	Kx = sgn (a) * sqrt ((matrix[ 0] - cost) / vers);
	Ky = sgn (b) * sqrt ((matrix[ 5] - cost) / vers);
	Kz = sgn (c) * sqrt ((matrix[10] - cost) / vers);
	
	float denom;
	switch (min3 (Kx, Ky, Kz))
	  {
	  case 0:
	    denom = 2 * Kx * vers;
	    Ky =  (matrix[4] + matrix[1]) / denom;
	    Kz =  (matrix[2] + matrix[8]) / denom;
	    break;
	    
	  case 1:
	    denom = 2 * Ky * vers;
	    Kx =  (matrix[4] + matrix[1]) / denom;
	    Kz =  (matrix[9] + matrix[6]) / denom;
	    break;
	    
	  default:
	    denom = 2 * Kz * vers;
	    Kx =  (matrix[2] + matrix[8]) / denom;
	    Ky =  (matrix[9] + matrix[6]) / denom;
	    break;
	  }
      }
    else
      if (theta > 0.0)
	{
	  float denom = 2.0 * sin (theta);
	  Kx = a / denom;
	  Ky = b / denom;
	  Kz = c / denom;
	}
    
    Vector3D v (Kx, Ky, Kz);
    if (v.length() > 0.0)
      v.normalize();
    
    return make_pair (v, theta);
  }




  Vector3D
  HomogeneousTransfo::getTranslationVector () const 
  {
    return Vector3D (matrix[12], matrix[13], matrix[14]);
  }
  

  HomogeneousTransfo 
  HomogeneousTransfo::getTranslation () const 
  {
    return HomogeneousTransfo (1, 0, 0, matrix[12],
			       0, 1, 0, matrix[13],
			       0, 0, 1, matrix[14],
			       0, 0, 0, 1);
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
			       0,
			       x * y * versTh + z * sinTh,
			       y * y * versTh + cosTh,
			       y * z * versTh - x * sinTh,
			       0,
			       x * z * versTh - y * sinTh,
			       y * z * versTh + x * sinTh,
			       z * z * versTh + cosTh,
			       0,
			       0, 0, 0, 1);
  }
  
  
  HomogeneousTransfo 
  HomogeneousTransfo::rotate (const Vector3D &axis, float theta) const 
  {
    return (*this * HomogeneousTransfo::rotation (axis, theta));
  }


  HomogeneousTransfo 
  HomogeneousTransfo::rotate(float theta_x, float theta_y, float theta_z) const 
  {
    float a, b;
    HomogeneousTransfo copy = *this;
    
    if (0 != theta_x) {
      a = (float) sin(theta_x);
      b = (float) cos(theta_x);
      copy = copy * HomogeneousTransfo(1, 0, 0, 0,
				       0, b, -a, 0,
				       0, a, b, 0,
				       0, 0, 0, 1);
    }
    if (0 != theta_y) {
      a = (float) sin(theta_y);
      b = (float) cos(theta_y);
      copy = copy * HomogeneousTransfo (b, 0, a, 0,
					0, 1, 0, 0,
					-a, 0, b, 0,
					0, 0, 0, 1);
    }
    if (0 != theta_z) {
      a = (float) sin(theta_z);
      b = (float) cos(theta_z);
      copy = copy * HomogeneousTransfo (b,-a, 0, 0,
					a, b, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
    }
    return copy;
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translation (const Vector3D &t) 
  {
    return HomogeneousTransfo(1, 0, 0, t.getX (),
			      0, 1, 0, t.getY (),
			      0, 0, 1, t.getZ (),
			      0, 0, 0, 1);
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translate (const Vector3D &t) const 
  {
    return (*this * HomogeneousTransfo::translation(t));
  }


  HomogeneousTransfo 
  HomogeneousTransfo::translate (float x, float y, float z) const 
  {
    return (*this * HomogeneousTransfo(1, 0, 0, x,
				       0, 1, 0, y,
				       0, 0, 1, z,
				       0, 0, 0, 1));
  }
  

  HomogeneousTransfo 
  HomogeneousTransfo::invert () const 
  {
    if ((matrix[3] + matrix[7] + matrix[11]) != 0.0)
      throw CFatalIntLibException ("HomogeneousTransfo containing scale cannot be inverted.", __FILE__, __LINE__);

    return HomogeneousTransfo (matrix[0], matrix[1], matrix[2], 
			       -(matrix[12]*matrix[0] + matrix[13]*matrix[1] + matrix[14]*matrix[2]),
			       matrix[4], matrix[5], matrix[6], 
			       -(matrix[12]*matrix[4] + matrix[13]*matrix[5] + matrix[14]*matrix[6]),
			       matrix[8], matrix[9], matrix[10], 
			       -(matrix[12]*matrix[8] + matrix[13]*matrix[9] + matrix[14]*matrix[10]),
			       matrix[3], matrix[7], matrix[11], 
			       matrix[15]);
  }


  float 
  HomogeneousTransfo::strength () const 
  {
    Vector3D trans (matrix[12], matrix[13], matrix[14]);
    
    float a = matrix[6] - matrix[9];
    float b = matrix[8] - matrix[2];
    float c = matrix[1] - matrix[4];
    float diag = matrix[0] + matrix[5] + matrix[10] - 1;
    float theta;
    
    a *= a;
    b *= b;
    c *= c;
    theta = (float) atan2 (sqrt (a + b + c), diag) * 180 / (float) M_PI;	
    return (float) sqrt (trans.length () * trans.length () + theta * theta / 900);
  }
  
  
  float 
  HomogeneousTransfo::distance (const HomogeneousTransfo &m) const 
  {
    HomogeneousTransfo a = *this;
    HomogeneousTransfo bi = m;
    bi = bi.invert ();
    
    HomogeneousTransfo a_bi = a * bi;
    HomogeneousTransfo bi_a = bi * a;
    return (a_bi.strength () + bi_a.strength ()) / 2;
  }
  
  
  HomogeneousTransfo 
  HomogeneousTransfo::align (const Vector3D &p1, const Vector3D &p2, const Vector3D &p3) 
  {
    Vector3D ry;
    Vector3D rx;
    Vector3D rz;
    HomogeneousTransfo rot;
    HomogeneousTransfo trans;
    
    // p1 is placed at the origin
    // p2 is placed along the y axis
    // p3 is placed in the y-z plane.
    ry = p2 - p1;
    ry = ry.normalize();
    rx = (p2 - p1).cross(p3 - p1);
    rx = rx.normalize();
    rz = rx.cross(ry);
    
    rot.set (rx.getX (), rx.getY (), rx.getZ (), 0,
	     ry.getX (), ry.getY (), ry.getZ (), 0,
	     rz.getX (), rz.getY (), rz.getZ (), 0,
	     0, 0, 0, 1);
	
    trans.set (1, 0, 0, -p1.getX (),
	       0, 1, 0, -p1.getY (),
	       0, 0, 1, -p1.getZ (),
	       0, 0, 0, 1);
    
    return (rot * trans).invert ();
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
