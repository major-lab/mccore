//                              -*- Mode: C++ -*- 
// Vector3D.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar  5 15:05:43 2003
// $Revision: 1.1 $
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
#include "Vector3D.h"
#include "HomogeneousTransfo.h"

namespace mccore {


  // LIFECYCLE -----------------------------------------------------------------


  Vector3D::Vector3D () 
    : x (0), y (0), z (0) 
  {
  }


  Vector3D::Vector3D (float xp, float yp, float zp)
    : x (xp), y (yp), z (zp) 
  {
  }


  Vector3D::Vector3D (const Vector3D &other) 
    : x (other.x), y (other.y), z (other.z) 
  {
  }
  

  Vector3D::~Vector3D () 
  {
  }

  
  // OPERATORS -----------------------------------------------------------------
  

  Vector3D& 
  Vector3D::operator= (const Vector3D &other)
  {
    if (this != &other)
      {
	x = other.x;
	y = other.y;
	z = other.z;
      }
    return *this;
  }
  
  
  bool 
  Vector3D::operator== (const Vector3D &other) const
  {
    return (x == other.x && y == other.y && z == other.z);
  }


  
  // METHODS -------------------------------------------------------------------


  Vector3D 
  Vector3D::normalize() const 
  {
    float l = length();
    return Vector3D (x / l, y / l, z / l);
  }
  

  float
  Vector3D::length() const 
  {
    return (float) sqrt (squareLength());
  }


  float 
  Vector3D::squareLength () const 
  {
    return (x*x + y*y + z*z);
  }

  Vector3D 
  Vector3D::operator- () const
  {
    return Vector3D(-x, -y, -z);
  }
  
  
  const Vector3D& 
  Vector3D::operator-= (const Vector3D &v)
  {
    x -= v.x; 
    y -= v.y;
    z -= v.z;
    return *this;
  }
  

  const Vector3D& 
  Vector3D::operator+= (const Vector3D &v)
  {
    x += v.x; 
    y += v.y;
    z += v.z;
    return *this;
  }


  Vector3D 
  Vector3D::cross (const Vector3D &v) const 
  {
    return Vector3D(y * v.z - z * v.y,
		    z * v.x - x * v.z,
		    x * v.y - y * v.x);
  }


  float 
  Vector3D::dot (const Vector3D &v) const 
  {
    return x * v.x + y * v.y + z * v.z;
  }


  const Vector3D& 
  Vector3D::operator*= (float value) 
  {
    x *= value; 
    y *= value;
    z *= value;
    return *this;
  }


  const Vector3D& 
  Vector3D::operator/= (float value) 
  {
    x /= value; 
    y /= value;
    z /= value;
    return *this;
  }


  float 
  Vector3D::distance (const Vector3D &aVector) const 
  {
    return (float)sqrt(squareDistance(aVector));
  }


  float 
  Vector3D::squareDistance (const Vector3D &aVector) const 
  {
    return (float) ((x - aVector.x) * (x - aVector.x)
		    + (y - aVector.y) * (y - aVector.y)
		    + (z - aVector.z) * (z - aVector.z));
  }


  float 
  Vector3D::angle(const Vector3D &a, const Vector3D &c) const
  {
    Vector3D u;
    Vector3D v;
    float len;
    
    u = a - *this;
    v = c - *this;
    len = u.length() * v.length();
    return len == 0 ? 0 : (float) acosf (u.dot(v) / len);
  }
  
  
  float 
  Vector3D::torsionAngle(const Vector3D &a, const Vector3D &c, const Vector3D &d) const
  {
    Vector3D bcVect;
    Vector3D baVect;
    Vector3D cdVect;
    Vector3D projVect;
    float projLength;
    float cosTheta;
    float angleDirection;
    
    bcVect = c - *this;
    baVect = a - *this;
    cdVect = d - c;
    projLength = baVect.dot(bcVect) / bcVect.dot(bcVect);
    projVect = bcVect * projLength;
    baVect -= projVect;
    
    // baVect is now the projection of original vector baVect in
    // the plane perpendicular to vector bcVect.
    
    projLength = cdVect.dot(bcVect) / bcVect.dot(bcVect);
    projVect = bcVect * projLength;
    cdVect -= projVect;
    
    // cdVect is now the projection of original vector cdVect in
    // the plane perpendicular to vector bcVect.
    
    cosTheta = baVect.dot(cdVect) / (baVect.length() * cdVect.length());
    
    if (cosTheta > 1) {
      return 0;
    } else if (cosTheta < -1) {
      return (float) M_PI;
    }
    
    angleDirection = baVect.cross(cdVect).dot(bcVect);
    return (float) ((angleDirection >= 0)
		    ? acosf(cosTheta)
		    : -acosf(cosTheta));
  }
  
  
  Vector3D& 
  Vector3D::transform (const HomogeneousTransfo &tfo)
  {
    *this = tfo * *this;
    return *this;
  }
  
  
  // I/O  -----------------------------------------------------------------
  
  
  ostream &
  Vector3D::output (ostream &out) const 
  {
    out.setf (ios::right, ios::adjustfield);
    out.setf (ios::fixed, ios::floatfield);
    out.precision (3);
    out << "(" << setw (8) << getX ()
	<< setw (8) << getY ()
	<< setw (8) << getZ ()
	<< " )";
    return out;
  }
  

  ostream &
  operator<< (ostream &out, const Vector3D &v)
  {
    return v.output (out);
  }
  
  
  iBinstream& 
  operator>> (iBinstream &ibs, Vector3D &p)
  {
    float tmpx, tmpy, tmpz;
    
    ibs >> tmpx >> tmpy >> tmpz;
    p.set (tmpx, tmpy, tmpz);
    return ibs;
  }
  
  
  
  oBinstream&
  operator<< (oBinstream &obs, const Vector3D &p)
  {
    return obs << p.getX () << p.getY () << p.getZ ();
  }
  

  const Vector3D
  operator- (const Vector3D &v, const Vector3D &w) 
  {
    Vector3D result = v;
    return result -= w;
  }
  
  
  const Vector3D 
  operator+ (const Vector3D &v, const Vector3D &w) 
  {    
    Vector3D result = v;
    return result += w;
  }


  const float 
  operator* (const Vector3D &v, const Vector3D &w) 
  {
    return v.dot (w);
  }
  

  const Vector3D 
  operator* (const Vector3D &v, float value) 
  {
    Vector3D result = v;
    return result *= value;
  }


  const Vector3D 
  operator* (float value, const Vector3D &v) 
  {
    Vector3D result = v;
    return result *= value;
  }


  const Vector3D 
  operator/ (const Vector3D &v, float value) 
  {
    Vector3D result = v;
    return result /= value;
  }


}
