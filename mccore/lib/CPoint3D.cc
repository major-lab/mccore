//                           -*- Mode: C++ -*-
// CPoint3D.cc
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Sep 20 12:45:00 2001
// Update Count     : 13
// Status           : Ok.
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

#include <iostream.h>
#include <stdio.h>
#include <math.h>

#include "Binstream.h"
#include "CException.h"
#include "CPoint3D.h"
#include "CTransfo.h"
#include "McCore.h"

#ifndef HAVE_ACOSF
#define   acosf      acos
#endif

#ifndef HAVE_SQRTF
#define   sqrtf      sqrt
#endif



const CPoint3D&
CPoint3D::operator= (const CPoint3D &right)
{
  if (&right != this)
    {
      mX = right.mX;
      mY = right.mY;
      mZ = right.mZ;
    }
  return *this;
}



CPoint3D 
CPoint3D::operator- (const CPoint3D &right) const
{
  return CPoint3D (mX - right.mX, mY - right.mY, mZ - right.mZ);
}



const CPoint3D&
CPoint3D::operator-= (const CPoint3D &right)
{
  mX -= right.mX; 
  mY -= right.mY;
  mZ -= right.mZ;
  return *this;
}



CPoint3D 
CPoint3D::operator+ (const CPoint3D &right) const
{
  return CPoint3D (mX + right.mX, mY + right.mY, mZ + right.mZ);
}



const CPoint3D&
CPoint3D::operator+= (const CPoint3D &right)
{
  mX += right.mX; 
  mY += right.mY;
  mZ += right.mZ;
  return *this;
}



float 
CPoint3D::operator* (const CPoint3D &right) const
{
  return mX * right.mX + mY * right.mY + mZ * right.mZ;
}



CPoint3D 
CPoint3D::operator* (float right) const
{
  return CPoint3D (mX * right, mY * right, mZ * right);
}



const CPoint3D&
CPoint3D::operator*= (float right)
{
  mX *= right; 
  mY *= right;
  mZ *= right;
  return *this;
}



CPoint3D 
CPoint3D::operator/ (float right) const
{
  return CPoint3D (mX / right, mY / right, mZ / right);
}



const CPoint3D&
CPoint3D::operator/= (float right)
{
  mX /= right; 
  mY /= right;
  mZ /= right;
  return *this;
}



float 
CPoint3D::operator| (const CPoint3D &right) const
{
  return sqrtf ((mX - right.mX) * (mX - right.mX)
		+ (mY - right.mY) * (mY - right.mY)
		+ (mZ - right.mZ) * (mZ - right.mZ));
}



float 
CPoint3D::operator|| (const CPoint3D &right) const
{
  return ((mX - right.mX) * (mX - right.mX)
	  + (mY - right.mY) * (mY - right.mY)
	  + (mZ - right.mZ) * (mZ - right.mZ));
}



CPoint3D 
CPoint3D::operator- () const
{ 
  return CPoint3D (-mX, -mY, -mZ);
}



float&
CPoint3D::operator[] (unsigned int k)
{
  if (k < 3)
    switch (k)
      {
      case 0:
	return mX;
      case 1:
	return mY;
      case 2:
	return mZ;
      }

  CFatalIntLibException exc ("Invalid point index", __FILE__, __LINE__);
  
  exc << k;
  throw exc;
}



const float&
CPoint3D::operator[] (unsigned int k) const
{
  if (k < 3)
    switch (k)
      {
      case 0:
	return mX;
      case 1:
	return mY;
      case 2:
	return mZ;
      }
  
  CFatalIntLibException exc ("Invalid point index", __FILE__, __LINE__);
  
  exc << k;
  throw exc;
}



const CPoint3D&
CPoint3D::SetXYZ (float nX, float nY, float nZ)
{
  mX = nX;
  mY = nY;
  mZ = nZ;
  return *this;
}



CPoint3D&
CPoint3D::Normalize ()
{
  float n = sqrt (mX * mX + mY * mY + mZ * mZ);
  mX /= n;
  mY /= n;
  mZ /= n;
  return *this;
}



float 
CPoint3D::Length () const 
{
  return sqrtf (mX * mX + mY * mY + mZ * mZ);
}



float 
CPoint3D::Angle (const CPoint3D &A, const CPoint3D &C) const
{
  CPoint3D u (A - *this);
  CPoint3D v (C - *this);
  float len = u.Length () * v.Length ();

  return len == 0 ? 0 : acosf (u * v / len);
}



float
CPoint3D::TorsionAngle (const CPoint3D &A, const CPoint3D &C,
			const CPoint3D &D) const
{
  CPoint3D B_C_Vect (C - *this);
  CPoint3D B_A_Vect (A - *this);
  CPoint3D C_D_Vect (D - C);
  CPoint3D ProjVect;
  float ProjLength, CosTheta;

  ProjLength = (B_A_Vect * B_C_Vect) / (B_C_Vect * B_C_Vect);
  ProjVect = B_C_Vect * ProjLength;
  B_A_Vect -= ProjVect;

  // B_A_Vect is now the projection of original vector B_A_Vect in the plane
  // perpendicular to vector B_C_Vect.
  
  ProjLength = (C_D_Vect * B_C_Vect) / (B_C_Vect * B_C_Vect);
  ProjVect = B_C_Vect * ProjLength;
  C_D_Vect -= ProjVect;

  // C_D_Vect is now the projection of original vector C_D_Vect in the plane
  // perpendicular to vector B_C_Vect.
  
  CosTheta = (B_A_Vect * C_D_Vect) / (B_A_Vect.Length () * C_D_Vect.Length ());

  if (CosTheta > 1)
    return 0;
  else if (CosTheta < -1)
    return M_PI;
  else
    return acosf (CosTheta);
}



float
CPoint3D::TorsionAngleDir (const CPoint3D &A, const CPoint3D &C,
			   const CPoint3D &D) const
{
  CPoint3D B_C_Vect (C - *this);
  CPoint3D B_A_Vect (A - *this);
  CPoint3D C_D_Vect (D - C);
  CPoint3D ProjVect;
  float ProjLength, CosTheta;
  float AngleDirection; 

  ProjLength = (B_A_Vect * B_C_Vect) / (B_C_Vect * B_C_Vect);
  ProjVect = B_C_Vect * ProjLength;
  B_A_Vect -= ProjVect;

  // B_A_Vect is now the projection of original vector B_A_Vect in the plane
  // perpendicular to vector B_C_Vect.

  ProjLength = (C_D_Vect * B_C_Vect) / (B_C_Vect * B_C_Vect);
  ProjVect = B_C_Vect * ProjLength;
  C_D_Vect -= ProjVect;

  // C_D_Vect is now the projection of original vector C_D_Vect in the plane
  // perpendicular to vector B_C_Vect.

  CosTheta = (B_A_Vect * C_D_Vect) / (B_A_Vect.Length () * C_D_Vect.Length ());

  AngleDirection = B_A_Vect.Cross (C_D_Vect) * B_C_Vect;

  if (CosTheta > 1)
    return 0;
  else if (CosTheta < -1)
    return M_PI;
  else if (AngleDirection >= 0)
    return acosf (CosTheta);
  else
    return -acosf (CosTheta);
}



CPoint3D
CPoint3D::Cross (const CPoint3D &right) const
{
  return CPoint3D (mY * right.GetZ () - mZ * right.GetY (),
		   mZ * right.GetX () - mX * right.GetZ (),
		   mX * right.GetY () - mY * right.GetX ());
}



CPoint3D&
CPoint3D::Transform (const CTransfo &tfo)
{
  float tmpX = mX;
  float tmpY = mY;
  float tmpZ = mZ;

  mX = (tfo.GetElement (0,0) * tmpX
	+ tfo.GetElement (0,1) * tmpY
	+ tfo.GetElement (0,2) * tmpZ
	+ tfo.GetElement (0,3));
  mY = (tfo.GetElement (1,0) * tmpX
	+ tfo.GetElement (1,1) * tmpY
	+ tfo.GetElement (1,2) * tmpZ
	+ tfo.GetElement (1,3));
  mZ = (tfo.GetElement (2,0) * tmpX
	+ tfo.GetElement (2,1) * tmpY
	+ tfo.GetElement (2,2) * tmpZ
	+ tfo.GetElement (2,3));
  return *this;
}



istream&
operator>> (istream &is, CPoint3D &p)
{
  float tmp1, tmp2, tmp3;

  is >> tmp1 >> tmp2 >> tmp3;
  p.SetXYZ (tmp1, tmp2, tmp3);
  return is;
}



ostream&
operator<< (ostream &os, const CPoint3D &p)
{
  char line[81];

  sprintf (line, "%10.3f %10.3f %10.3f", p.GetX (), p.GetY (), p.GetZ ());
  return os << line;
}



iBinstream& 
operator>> (iBinstream &ibs, CPoint3D &p)
{
  float tmpx, tmpy, tmpz;
  
  ibs >> tmpx >> tmpy >> tmpz;
  p.SetXYZ (tmpx, tmpy, tmpz);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CPoint3D &p)
{
  return obs << p.GetX () << p.GetY () << p.GetZ ();
}
