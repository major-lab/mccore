//                              -*- Mode: C++ -*- 
// CTransfo.cc
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron <gendrop@IRO.UMontreal.CA>
// Created On       : Fri Oct  1 18:22:41 1999
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:03:40 2001
// Update Count     : 7
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


#include <iostream.h>
#include <iomanip.h>
#include <math.h>

#include "CTransfo.h"

#include "McCore.h"
#include "Binstream.h"
#include "CException.h"
#include "CPoint3D.h"
#include "CResidue.h"



CTransfo::CTransfo ()
{
  SetIdentity ();
}



CTransfo::CTransfo (float n00, float n01, float n02, float n03,
		    float n10, float n11, float n12, float n13,
		    float n20, float n21, float n22, float n23)
{
  m[0] = n00;  m[1] = n01;  m[ 2] = n02;  m[ 3] = n03;
  m[4] = n10;  m[5] = n11;  m[ 6] = n12;  m[ 7] = n13;
  m[8] = n20;  m[9] = n21;  m[10] = n22;  m[11] = n23;
}



CTransfo::CTransfo (const CTransfo &right)
{
  m[0] = right.m[0]; m[1] = right.m[1]; m[2] = right.m[2];
  m[3] = right.m[3]; m[4] = right.m[4]; m[5] = right.m[5];
  m[6] = right.m[6]; m[7] = right.m[7]; m[8] = right.m[8];
  m[9] = right.m[9]; m[10] = right.m[10]; m[11] = right.m[11];
}



CTransfo&
CTransfo::operator= (const CTransfo &right)
{
  if (this != &right)
    {
      m[0] = right.m[0]; m[1] = right.m[1]; m[2] = right.m[2];
      m[3] = right.m[3]; m[4] = right.m[4]; m[5] = right.m[5];
      m[6] = right.m[6]; m[7] = right.m[7]; m[8] = right.m[8];
      m[9] = right.m[9]; m[10] = right.m[10]; m[11] = right.m[11];
    }
  return *this;
}



CTransfo
CTransfo::operator* (const CTransfo &right) const
{
  return CTransfo (m[0] * right.m[0] + m[1] * right.m[4] + m[2] * right.m[8],
		   m[0] * right.m[1] + m[1] * right.m[5] + m[2] * right.m[9],
		   m[0] * right.m[2] + m[1] * right.m[6] + m[2] * right.m[10],
		   m[0] * right.m[3] + m[1] * right.m[7] + m[2] * right.m[11]
		   + m[3],
		   
		   m[4] * right.m[0] + m[5] * right.m[4] + m[6] * right.m[8],
		   m[4] * right.m[1] + m[5] * right.m[5] + m[6] * right.m[9],
		   m[4] * right.m[2] + m[5] * right.m[6] + m[6] * right.m[10],
		   m[4] * right.m[3] + m[5] * right.m[7] + m[6] * right.m[11]
		   + m[7],
		   
		   m[8] * right.m[0] + m[9] * right.m[4] + m[10] * right.m[8],
		   m[8] * right.m[1] + m[9] * right.m[5] + m[10] * right.m[9],
		   m[8] * right.m[2] + m[9] * right.m[6] + m[10] * right.m[10],
		   m[8] * right.m[3] + m[9] * right.m[7] + m[10] * right.m[11]
		   + m[11]);
}



CTransfo&
CTransfo::operator*= (const CTransfo &right)
{
  float m0 = m[0], m1 = m[1], m2 = m[2], m3 = m[3];
  float m4 = m[4], m5 = m[5], m6 = m[6], m7 = m[7];
  float m8 = m[8], m9 = m[9], m10 = m[10], m11 = m[11];

  m[0] = m0 * right.m[0] + m1 * right.m[4] + m2 * right.m[8];
  m[1] = m0 * right.m[1] + m1 * right.m[5] + m2 * right.m[9];
  m[2] = m0 * right.m[2] + m1 * right.m[6] + m2 * right.m[10];
  m[3] = m0 * right.m[3] + m1 * right.m[7] + m2 * right.m[11] + m3;

  m[4] = m4 * right.m[0] + m5 * right.m[4] + m6 * right.m[8];
  m[5] = m4 * right.m[1] + m5 * right.m[5] + m6 * right.m[9];
  m[6] = m4 * right.m[2] + m5 * right.m[6] + m6 * right.m[10];
  m[7] = m4 * right.m[3] + m5 * right.m[7] + m6 * right.m[11] + m7;

  m[8] = m8 * right.m[0] + m9 * right.m[4] + m10 * right.m[8];
  m[9] = m8 * right.m[1] + m9 * right.m[5] + m10 * right.m[9];
  m[10] = m8 * right.m[2] + m9 * right.m[6] + m10 * right.m[10];
  m[11] = m8 * right.m[3] + m9 * right.m[7] + m10 * right.m[11] + m11;

  return *this;
}



void
CTransfo::SetAll (float n00, float n01, float n02, float n03,
		  float n10, float n11, float n12, float n13,
		  float n20, float n21, float n22, float n23)
{
  m[0] = n00;  m[1] = n01;  m[ 2] = n02;  m[ 3] = n03;
  m[4] = n10;  m[5] = n11;  m[ 6] = n12;  m[ 7] = n13;
  m[8] = n20;  m[9] = n21;  m[10] = n22;  m[11] = n23;
}



void
CTransfo::SetIdentity ()
{
  m[0] = 1.0;  m[1] = 0.0;  m[ 2] = 0.0;  m[ 3] = 0.0;
  m[4] = 0.0;  m[5] = 1.0;  m[ 6] = 0.0;  m[ 7] = 0.0;
  m[8] = 0.0;  m[9] = 0.0;  m[10] = 1.0;  m[11] = 0.0;
}



bool
CTransfo::isIdentity ()
{
  return (m[0] == 1 && m[1] == 0 && m[ 2] == 0 && m[ 3] == 0 &&
	  m[4] == 0 && m[5] == 1 && m[ 6] == 0 && m[ 7] == 0 &&
	  m[8] == 0 && m[9] == 0 && m[10] == 1 && m[11] == 0);
}



CTransfo&
CTransfo::SetRotation (const CPoint3D &axis, float theta)
{
  float cos_th = cos (theta);
  float sin_th = sin (theta);
  float vers_th = 1 - cos_th;
  float x = axis.GetX ();
  float y = axis.GetY ();
  float z = axis.GetZ ();

  SetAll (x * x * vers_th + cos_th,
	  x * y * vers_th - z * sin_th,
	  x * z * vers_th + y * sin_th,
	  0,
	  x * y * vers_th + z * sin_th,
	  y * y * vers_th + cos_th,
	  y * z * vers_th - x * sin_th,
	  0,
	  x * z * vers_th - y * sin_th,
	  y * z * vers_th + x * sin_th,
	  z * z * vers_th + cos_th,
	  0);
  return *this;
}



CTransfo&
CTransfo::SetTranslation (const CPoint3D &t)
{
  SetAll (1, 0, 0, t.GetX (), 0, 1, 0, t.GetY (), 0, 0, 1, t.GetZ ());
  return *this;
}



CPoint3D 
CTransfo::GetTranslation () const
{
  return CPoint3D (m[3], m[7], m[11]);
}



pair< CPoint3D, float >
CTransfo::GetRotation () const
{
  CPoint3D v (0, 0, 0);  // Still to be done: axis of rotation...

  float a = m[9] - m[6];
  float b = m[2] - m[8];
  float c = m[4] - m[1];
  float diag = m[0] + m[5] + m[10] - 1;
  float theta;

  a *= a;
  b *= b;
  c *= c;
  theta = atan2 (sqrt (a + b + c), diag);
  
  return make_pair (v, theta);
}



CTransfo&
CTransfo::Inverse ()
{
  float m0 = m[0], m1 = m[1], m2 = m[2], m3 = m[3];
  float m4 = m[4], m5 = m[5], m6 = m[6], m7 = m[7];
  float m8 = m[8], m9 = m[9], m10 = m[10], m11 = m[11];
  
  m[3]  = - (m3 * m0 + m7 * m4 + m11 * m8);
  m[7]  = - (m3 * m1 + m7 * m5 + m11 * m9);
  m[11] = - (m3 * m2 + m7 * m6 + m11 * m10);
  m[1] = m4;  m[4] = m1;
  m[2] = m8;  m[8] = m2;
  m[6] = m9;  m[9] = m6;

  return *this;
}



float 
CTransfo::Strength () const
{
  CPoint3D trans (m[3], m[7], m[11]);
  float rot = RadToDegree (GetRotation ().second);

  return sqrt (trans.Length () * trans.Length () + rot * rot / 900);
}



CTransfo&
CTransfo::Rotate (const CPoint3D &axis, float theta)
{
  CTransfo theRot;
  
  theRot.SetRotation (axis, theta);

  return *this *= theRot;
}



CTransfo&
CTransfo::Rotate (float theta_x, float theta_y, float theta_z)
{
  float a, b;

  if (theta_x != 0.0)
    {
      a = sin (theta_x);
      b = cos (theta_x);
      *this *= CTransfo(1, 0, 0, 0, 0, b, -a, 0, 0, a, b, 0);
    }
  if (theta_y != 0.0)
    {
      a = sin (theta_y);
      b = cos (theta_y);
      *this *= CTransfo (b, 0, a, 0, 0, 1, 0, 0, -a, 0, b, 0 );
    }
  if (theta_z != 0.0)
    {
      a = sin (theta_z);
    b = cos (theta_z);
    *this *= CTransfo (b,-a, 0, 0, a, b, 0, 0, 0, 0, 1, 0);
    }
  return *this;
}



CTransfo&
CTransfo::Translate (const CPoint3D &t)
{
  CTransfo theTrans;
  
  theTrans.SetTranslation (t);
  return *this *= theTrans;
}



CTransfo&
CTransfo::Align (const CPoint3D *p1, const CPoint3D *p2, const CPoint3D *p3)
{
  if (p1 == 0 || p2 == 0 || p3 == 0)
    throw CFatalIntLibException ("Pivot(s) not set.", __FILE__, __LINE__);

  // p1 is placed at the origin
  // p2 is placed along the y axis
  // p3 is placed in the y-z plane.
  CPoint3D Ry = *p2 - *p1;  
  Ry = Ry / Ry.Length ();
  CPoint3D Rx = (*p2 - *p1).Cross ((*p3 - *p1));
  Rx = Rx/Rx.Length ();
  CPoint3D Rz = Rx.Cross (Ry);

  CTransfo rot (Rx.GetX (), Rx.GetY (), Rx.GetZ (), 0,
		Ry.GetX (), Ry.GetY (), Ry.GetZ (), 0,
		Rz.GetX (), Rz.GetY (), Rz.GetZ (), 0);
  
  CTransfo trans (1, 0, 0, -p1->GetX (),
		  0, 1, 0, -p1->GetY (),
		  0, 0, 1, -p1->GetZ ());
  
  CTransfo tot = (rot * trans).Inverse ();
  return *this = tot * (*this);
}



CTransfo&
CTransfo::Referentiel (const CPoint3D *p1, const CPoint3D *p2,
		       const CPoint3D *p3, const CPoint3D *p4,
		       const CPoint3D *p5, const CPoint3D *p6)
{
  if (p1 == 0 || p2 == 0 || p3 == 0
      || p4 == 0 || p5 == 0 || p6 == 0)
    throw CFatalIntLibException ("Pivot(s) not set.", __FILE__, __LINE__);

  CTransfo m1, m2;   
  CPoint3D p4p, p5p, p6p;

  m1.Align (p1, p2, p3).Inverse ();

  p4p = *p4;
  p4p.Transform (m1);
  p5p = *p5;
  p5p.Transform (m1);
  p6p = *p6;
  p6p.Transform (m1);
  
  m2.Align (&p4p, &p5p, &p6p);
  
  return *this *= m2;
}



ostream&
operator<< (ostream &os, const CTransfo &obj)
{
  os.precision (8);
  os.setf (ios::right);
  os.setf (ios::showpoint);
  os.setf (ios::fixed);
  os.setf (ios::internal);
  return os << "| " << setw (12) << obj.GetElement (0)
	    << "  " << setw (12) << obj.GetElement (1)
	    << "  " << setw (12) << obj.GetElement (2)
	    << "  " << setw (12) << obj.GetElement (3)
	    << " |\n"
	    << "| " << setw (12) << obj.GetElement (4)
	    << "  " << setw (12) << obj.GetElement (5)
	    << "  " << setw (12) << obj.GetElement (6)
	    << "  " << setw (12) << obj.GetElement (7)
	    << " |\n"
	    << "| " << setw (12) << obj.GetElement (8)
	    << "  " << setw (12) << obj.GetElement (9)
	    << "  " << setw (12) << obj.GetElement (10)
	    << "  " << setw (12) << obj.GetElement (11)
	    << " |\n"
	    << "| " << setw (12) << 0.0 << "  " << setw (12) << 0.0
	    << "  " << setw (12) << 0.0 << "  " << setw (12) << 1.0
	    << " |";
}



iBinstream&
operator>> (iBinstream &ibs, CTransfo &obj)
{
  int i;
  
  for (i = 0; i < 12; ++i)
    {
      float x;
      
      ibs >> x;
      obj.SetElement (i, x);
    }
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CTransfo &obj)
{
  int i;
  
  for (i = 0; i < 12; ++i)
    obs << obj.GetElement (i);
  return obs;
}
