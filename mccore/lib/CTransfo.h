//                              -*- Mode: C++ -*- 
// CTransfo.h
// Copyright © 1999, 2000-02 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Patrick Gendron <gendrop@IRO.UMontreal.CA>
// Created On       : Fri Oct  1 18:22:41 1999
// Last Modified By : Patrick Gendron
// Last Modified On : Wed Nov 13 16:49:44 2002
// Update Count     : 9
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


#ifndef _CTransfo_h_
#define _CTransfo_h_

#include <iostream.h>

#include <vector.h>
#include <pair.h>

class CAtom;
class CPoint3D;
class CResidue;
class iBinstream;
class oBinstream;



/**
 * @short
 *
 * All angles are in radians...
 * <pre>
 * | m0  m1  m2  m3   |      | n00  n01  n02  n03 |
 * | m4  m5  m6  m7   |  ==  | n10  n11  n12  n13 |
 * | m8  m9  m10 m11  |      | n20  n21  n22  n23 |

 * Example:
 *
 * To align res2 on res1:
 * res2 = (const CTransfo&) res1;
 * </pre>
 *
 * @author Patrick Gendron <gendrop@IRO.UMontreal.CA>
 */
class CTransfo
{
  /**
   * The tranfo matrix.
   */
  float m[12];

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the transfo to the identity.
   */
  CTransfo ();

  /**
   * Initializes the transfo.
   * @param n00 the float at position 00.
   * @param n01 the float at position 01.
   * @param n02 the float at position 02.
   * @param n03 the float at position 03.
   * @param n10 the float at position 10.
   * @param n11 the float at position 11.
   * @param n12 the float at position 12.
   * @param n13 the float at position 13.
   * @param n20 the float at position 20.
   * @param n21 the float at position 21.
   * @param n22 the float at position 22.
   * @param n23 the float at position 23.
   */
  CTransfo (float n00, float n01, float n02, float n03,
	    float n10, float n11, float n12, float n13,
	    float n20, float n21, float n22, float n23);

  /**
   * Initializes the transfo with the right's content.
   * @param right the object to copy.
   */
  CTransfo (const CTransfo &right);

  /**
   * Destructs the transfo.
   */
  ~CTransfo () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  CTransfo& operator= (const CTransfo &right);

  /**
   * Calculates the matrix multiplication.
   * @param right the right matrix.
   * @return the resulting matrix.
   */
  CTransfo operator* (const CTransfo &right) const;

  /**
   * Calculates and assigns the matrix multiplication (Premultiplies).
   * @param right the right matrix.
   * @return itself.
   */
  CTransfo& operator*= (const CTransfo &right);

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the element of row i column j.
   * @param i the row number.
   * @param j the column number.
   * @return the element[i,j].
   */
  float GetElement (int i,int j) const { return m[i * 4 + j]; }

  /**
   * Sets the element of row i, column j.
   * @param i the row number.
   * @param j the column number.
   * @param x the new value.
   */
  void SetElement (int i, int j, float x) { m[i * 4 + j] = x; }

  /**
   * Gets the element at position i.
   * @param i the position.
   * @return the element at position i.
   */
  float GetElement (int i) const { return m[i]; }

  /**
   * Sets the element at position i.
   * @param i the position.
   * @param x the new value.
   */
  void SetElement (int i, float x) { m[i] = x; }

  /**
   * Sets all elements.
   * @param n00 the value at position [0,0].
   * @param n01 the value at position [0,1].
   * @param n02 the value at position [0,2].
   * @param n03 the value at position [0,3].
   * @param n10 the value at position [1,0].
   * @param n11 the value at position [1,1].
   * @param n12 the value at position [1,2].
   * @param n13 the value at position [1,3].
   * @param n20 the value at position [2,0].
   * @param n21 the value at position [2,1].
   * @param n22 the value at position [2,2].
   * @param n23 the value at position [2,3].
   */
  void SetAll (float n00, float n01, float n02, float n03,
	       float n10, float n11, float n12, float n13,
	       float n20, float n21, float n22, float n23);

  /**
   * Sets the matrix to identity.
   */
  void SetIdentity ();

  /**
   * Determines if the matrix is set to identity.
   */
  bool isIdentity ();

  // METHODS --------------------------------------------------------------


  /**
   * Calculates the homogeneous rotation matrix by a given angle
   * about a given axis.
   * @param axis the CPoint3D representing normalised rotation axis.
   * @param theta the angle to rotate by (in radians).
   * @return itself.
   */
  CTransfo& SetRotation (const CPoint3D &axis, float theta);

  /**
   * Calculates and assigns the homogeneous translation matrix by a given
   * vector.
   * @param t the vector representing normalised translation.
   * @return itself.
   */
  CTransfo& SetTranslation (const CPoint3D &t);

  /**
   * Gets the translation vector from the homogeneous matrix.
   * @return the translation vector.
   */
  CPoint3D GetTranslation () const;

  /**
   * Gets the pair rotation axis, rotation angle from an homogeneous
   * matrix.
   * @return the pair rotation axis (vector), rotation angle (in radians).
   */
  pair< CPoint3D, float > GetRotation () const;

  /**
   * Sets and returns the homogeneous matrix to it's inverse.
   * @return the inverse of the matrix.
   */
  CTransfo& Inverse ();

  /**
   * Calculates the distance from the homogeneous matrix to origin.  The
   * rotation factor is also included.
   * @return the distance.
   */
  float Strength () const;

  /**
   * Applies the rotation given an angle about a given axis.
   * @param axis the vector representing normalised rotation axis.
   * @param theta the angle to rotate by (in radians).
   * @returns itself.
   */
  CTransfo& Rotate (const CPoint3D &axis, float theta);

  /**
   * Applies a rotation to the homogeneous matrix given three rotation
   * angles.
   * @param theta_x the x rotation angle (in radians).
   * @param theta_y the y rotation angle (in radians).
   * @param theta_z the z rotation angle (in radians).
   * @returns itself.
   */
  CTransfo& Rotate (float theta_x, float theta_y, float theta_z);

  /**
   * Applies a translation to the homogeneous matrix given a translation
   * vector.
   * @param t the translation vector.
   * @return itself.
   */
  CTransfo& Translate (const CPoint3D &t);

  /**
   * Composes the current transfo with the inverse of the one needed to
   * align the Cpoints p1, p2, p3 with the Euclidian reference frame centered
   * at (0,0,0).  Throws an exception if any vector is null.
   * @param p1 the first vector.
   * @param p2 the second vector.
   * @param p3 the third vector.
   * @exception CFatalIntLibException.
   * @return itself.
   */
  CTransfo& Align (const CPoint3D *p1, const CPoint3D *p2, const CPoint3D *p3);
  
  /**
   * ** DEPRECATED *****
   * Finds the transfo that expresses the coordinate system of r2 as seen
   * from the reference frame r1 when called on an identity transfo.
   * Otherwise, premultiply the transfo from r1 to r2 to *this.  Throw an
   * exception if any vector is null.
   * @param p1 the first vector.
   * @param p2 the second vector.
   * @param p3 the third vector.
   * @param p4 the fourth vector.
   * @param p5 the fifth vector.
   * @param p6 the sixth vector.
   * @exception CFatalIntLibException.
   * @return itself.
   */
  CTransfo& Referentiel (const CPoint3D *p1, const CPoint3D *p2,
			 const CPoint3D *p3, const CPoint3D *p4,
			 const CPoint3D *p5, const CPoint3D *p6);

  // PRIVATE METHODS ------------------------------------------------------

private:

  bool determineIdentity ();

  // I/O  -----------------------------------------------------------------
};



/**
 * Displays the transfo to human readable form.
 * @param os the output stream.
 * @param obj the transfo to display.
 * @return the used output stream.
 */
ostream& operator<< (ostream &out, const CTransfo &obj);



/**
 * Reads a tranfo from the input binary stream.
 * @param ibs the input binary stream.
 * @param obj the transfo to fill.
 * @return the used input binary stream.
 */
iBinstream& operator>> (iBinstream& ibs, CTransfo &obj);



/**
 * Writes the transfo to the output binary stream.
 * @param obs the output binary stream.
 * @param obj the transfo to write.
 * @return the used output binary stream.
 */
oBinstream& operator<< (oBinstream& obs, const CTransfo &obj);

#endif
