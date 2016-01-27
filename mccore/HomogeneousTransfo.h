//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.h
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// $Revision: 1.24 $
// $Id: HomogeneousTransfo.h,v 1.24 2006-10-11 17:55:56 thibaup Exp $
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


#ifndef _mccore_HomogeneousTransfo_h_
#define _mccore_HomogeneousTransfo_h_

#include <iostream>

#include "Vector3D.h"
#include "Exception.h"

using namespace std;

namespace mccore
{

  class iBinstream;
  class oBinstream;
  
  /**
   * @short Rigid body linear transformation matrix in homogeneous coordinates.
   *
   * The 4X4 matrix is encoded using 12 float variables for the first
   * three rows. The last {0,0,0,1} row is implicit.
   *
   * Binary stream I/O is backward compatible (for now...). 
   *
   */
  class HomogeneousTransfo
  {
    /**
     * The transfo matrix elements (first three rows).
     */
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23;
   
    /**
     * The squared scale ratio between angle and distance (Ang^2 / rad^2)
     */ 
    static const float alpha_square; // 2.632^2
 
  public:
   
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the trasnformation as identity.
     */
    HomogeneousTransfo ()
      : m00 (1.0f), m01 (0.0f), m02 (0.0f), m03 (0.0f),
	m10 (0.0f), m11 (1.0f), m12 (0.0f), m13 (0.0f),
	m20 (0.0f), m21 (0.0f), m22 (1.0f), m23 (0.0f)
    { }

    /**
     * Initializes the transfo.
     * @param n00 the float at position [0,0].
     * @param n01 the float at position [0,1].
     * @param n02 the float at position [0,2].
     * @param n03 the float at position [0,3].
     * @param n10 the float at position [1,0].
     * @param n11 the float at position [1,1].
     * @param n12 the float at position [1,2].
     * @param n13 the float at position [1,3].
     * @param n20 the float at position [2,0].
     * @param n21 the float at position [2,1].
     * @param n22 the float at position [2,2].
     * @param n23 the float at position [2,3].
     * @param n30 the float at position [3,0].
     * @param n31 the float at position [3,1].
     * @param n32 the float at position [3,2].
     * @param n33 the float at position [3,3].
     */
    HomogeneousTransfo(float n00, float n01, float n02, float n03,
		       float n10, float n11, float n12, float n13,
		       float n20, float n21, float n22, float n23)
      : m00 (n00), m01 (n01), m02 (n02), m03 (n03), 
	m10 (n10), m11 (n11), m12 (n12), m13 (n13), 
	m20 (n20), m21 (n21), m22 (n22), m23 (n23)
    { }
    
    
    /**
     * Initializes the object with the other's content.
     * @param t the object to copy.
     */
    HomogeneousTransfo (const HomogeneousTransfo& t)
      : m00 (t.m00), m01 (t.m01), m02 (t.m02), m03 (t.m03), 
	m10 (t.m10), m11 (t.m11), m12 (t.m12), m13 (t.m13), 
	m20 (t.m20), m21 (t.m21), m22 (t.m22), m23 (t.m23)
    { }
    
    /**
     * Destroys the object.
     */
    ~HomogeneousTransfo () { }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the object with the other's content.
     * @param t the object to copy.
     * @return itself.
     */
    HomogeneousTransfo& operator= (const HomogeneousTransfo& t)
    {
      m00 = t.m00; m01 = t.m01; m02 = t.m02; m03 = t.m03;
      m10 = t.m10; m11 = t.m11; m12 = t.m12; m13 = t.m13;
      m20 = t.m20; m21 = t.m21; m22 = t.m22; m23 = t.m23;
      return *this;
    }
    
    // ACCESS ---------------------------------------------------------------
    
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
     * @return itself.
     */
    HomogeneousTransfo& set(float n00, float n01, float n02, float n03,
			    float n10, float n11, float n12, float n13,
			    float n20, float n21, float n22, float n23)
    {
      m00 = n00; m01 = n01; m02 = n02; m03 = n03;
      m10 = n10; m11 = n11; m12 = n12; m13 = n13;
      m20 = n20; m21 = n21; m22 = n22; m23 = n23;
      return *this;
    }
    
    /**
     * Sets the matrix to identity.
     */
    void setIdentity()
    {
      m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m23 = 0.0f;
      m00 = m11 = m22 = 1.0f;
    }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Calculates the matrix multiplication.
     * @param right the right matrix.
     * @return the resulting matrix.
     */
    HomogeneousTransfo operator* (const HomogeneousTransfo& t) const
    {
      return HomogeneousTransfo (      m00*t.m00 + m01*t.m10 + m02*t.m20,
				       m00*t.m01 + m01*t.m11 + m02*t.m21,
				       m00*t.m02 + m01*t.m12 + m02*t.m22,
				       m03 + m00*t.m03 + m01*t.m13 + m02*t.m23,

				       m10*t.m00 + m11*t.m10 + m12*t.m20,
				       m10*t.m01 + m11*t.m11 + m12*t.m21,
				       m10*t.m02 + m11*t.m12 + m12*t.m22,
				       m13 + m10*t.m03 + m11*t.m13 + m12*t.m23,

				       m20*t.m00 + m21*t.m10 + m22*t.m20,
				       m20*t.m01 + m21*t.m11 + m22*t.m21,
				       m20*t.m02 + m21*t.m12 + m22*t.m22,
				       m23 + m20*t.m03 + m21*t.m13 + m22*t.m23);
    }
    
    /**
     * Calculates and assign the matrix multiplication.
     * @param right the right matrix.
     * @return the resulting matrix.
     */
    HomogeneousTransfo& operator*= (const HomogeneousTransfo& t)
    {
      m00 =       m00*t.m00 + m01*t.m10 + m02*t.m20;
      m01 =       m00*t.m01 + m01*t.m11 + m02*t.m21;
      m02 =       m00*t.m02 + m01*t.m12 + m02*t.m22;
      m03 = m03 + m00*t.m03 + m01*t.m13 + m02*t.m23;

      m10 =       m10*t.m00 + m11*t.m10 + m12*t.m20;
      m11 =       m10*t.m01 + m11*t.m11 + m12*t.m21;
      m12 =       m10*t.m02 + m11*t.m12 + m12*t.m22;
      m13 = m13 + m10*t.m03 + m11*t.m13 + m12*t.m23;

      m20 =       m20*t.m00 + m21*t.m10 + m22*t.m20;
      m21 =       m20*t.m01 + m21*t.m11 + m22*t.m21;
      m22 =       m20*t.m02 + m21*t.m12 + m22*t.m22;
      m23 = m23 + m20*t.m03 + m21*t.m13 + m22*t.m23;

      return *this;
    }
    
    /**
     * Applies the transfo to the given point.
     * @param v the original point.
     * @return the transformed point.
     */
    Vector3D operator* (const Vector3D &v) const
    {
      return Vector3D (m00*v.getX () + m01*v.getY () + m02*v.getZ () + m03,  
		       m10*v.getX () + m11*v.getY () + m12*v.getZ () + m13, 
		       m20*v.getX () + m21*v.getY () + m22*v.getZ () + m23);
    }
    
    // METHODS --------------------------------------------------------------    

    /**
     * Gets the element of row i column j. Throws an ArrayIndexOutOfBoundsException
     * if (i,j) not in {0,1,2,3}X{0,1,2,3}.
     * @param i the row number in {0,1,2,3}.
     * @param j the column number in {0,1,2,3}.
     * @return the element[i,j].
     * @throws ArrayIndexOutOfBoundsException
     */
    float elementAt (unsigned i, unsigned j) const;

    /**
     * Gets a transfo containing the rotation part of this transfo.
     * @return the transfo.
     */
    HomogeneousTransfo getRotation () const;
    
    /**
     * Gets the vector of rotation and amplitude of this transfo.
     * @return a pair.
     */
    pair< Vector3D, float > getRotationVector () const;
    
    /**
     * Gets a transfo containing the rotation part of this transfo.
     * @return the transfo.
     */
    HomogeneousTransfo getTranslation () const;
    
    /**
     * Gets the translation vector from the homogeneous matrix.
     * @return the translation vector.
     */
    Vector3D getTranslationVector () const;
    
    /**
     * Calculates the homogeneous rotation matrix by a given angle
     * about a given axis.
     * @param axis the Vector3D representing the rotation axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new HomogeneousTransfo with the given rotation.
     */
    static HomogeneousTransfo rotation (const Vector3D &axis, float theta);

    /**
     * Calculates the homogeneous rotation matrix by a given angle
     * about the X axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new HomogeneousTransfo with the given rotation.
     */
    static HomogeneousTransfo rotationX (float theta);

    /**
     * Calculates the homogeneous rotation matrix by a given angle
     * about the Y axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new HomogeneousTransfo with the given rotation.
     */
    static HomogeneousTransfo rotationY (float theta);

    /**
     * Calculates the homogeneous rotation matrix by a given angle
     * about the Z axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new HomogeneousTransfo with the given rotation.
     */
    static HomogeneousTransfo rotationZ (float theta);
    
    /**
     * Rotates the current HomogeneousTransfo given an angle about a given axis.
     * @param axis the vector representing normalised rotation axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new rotated HomogeneousTransfo.
     */
    HomogeneousTransfo rotate (const Vector3D &axis, float theta) const;
    
    /**
     * Rotates this transfo by a given angle about the X axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new rotated HomogeneousTransfo.
     */
    HomogeneousTransfo rotateX (float theta) const;

    /**
     * Rotates this transfo by a given angle about the Y axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new rotated HomogeneousTransfo.
     */
    HomogeneousTransfo rotateY (float theta) const;

    /**
     * Rotates this transfo by a given angle about the Z axis.
     * @param theta the angle to rotate by (in radians).
     * @return the new rotated HomogeneousTransfo.
     */
    HomogeneousTransfo rotateZ (float theta) const;
    
    /**
     * Translates the homogeneous translation matrix by a given vector.
     * @param t the vector representing normalised translation.
     * @return the new HomogeneousTransfo with the given translation.
     */
    static HomogeneousTransfo translation (const Vector3D &t);

    /**
     * Translates the homogeneous translation matrix by a given
     * vector specified by its 3D components.
     * @param x X axis component.
     * @param y Y axis component.
     * @param z Z axis component.
     * @return the new HomogeneousTransfo with the given translation.
     */
    static HomogeneousTransfo translation (float x, float y, float z);
    
    /**
     * Translates the homogeneous matrix given a translation vector.
     * @param t the translation vector.
     * @return the new HomogeneousTransfo with the given translation.
     */
    HomogeneousTransfo translate (const Vector3D &t) const;
    
    /**
     * Translates the matrix
     * @param x the amplitude of translation in the x direction.
     * @param y the amplitude of translation in the y direction.
     * @param z the amplitude of translation in the z direction.
     * @return this.
     */
    HomogeneousTransfo translate (float x, float y, float z) const;

    
    /**
     * Returns this matrix's inverse using the general method. This is the default invert method.
     * More floating-point operations than unstable version, but apparently 
     * not slower using compiler optimization (prove me wrong!).
     * Stable numerical error, but not more precise than unstable version as a one-shot.
     * @return the inverted matrix.
     */
    HomogeneousTransfo invert () const
    {
      float det = m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 + m00*m11*m22 - m02*m11*m20;      
      return HomogeneousTransfo 
	((m11*m22 - m12*m21) / det,
	 (m02*m21 - m01*m22) / det,
	 (m01*m12 - m02*m11) / det,
	 (m03*m12*m21 - m02*m13*m21 - m03*m11*m22 + m01*m13*m22 + m02*m11*m23 - m01*m12*m23) / det,
	 
	 (m12*m20 - m10*m22) / det,
	 (m00*m22 - m02*m20) / det,
	 (m02*m10 - m00*m12) / det,
	 (m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 + m00*m12*m23 - m03*m12*m20) / det,
		
	 (m10*m21 - m11*m20) / det,
	 (m01*m20 - m00*m21) / det,
	 (m00*m11 - m01*m10) / det,
	 (m03*m11*m20 - m01*m13*m20 - m03*m10*m21 + m00*m13*m21 + m01*m10*m23 - m00*m11*m23) / det);
    }
    

    /**
     * Returns this matrix's inverse assuming that we have a rigid body transfo.
     * Unstable numerical error (after 22 iterations!).
     * @return the inverted matrix.
     */
    HomogeneousTransfo invert_unstable () const
    {
      return HomogeneousTransfo (m00, m10, m20, -m03*m00 - m13*m10 - m23*m20,
				 m01, m11, m21, -m03*m01 - m13*m11 - m23*m21,
				 m02, m12, m22, -m03*m02 - m13*m12 - m23*m22);
    }


    /**
     * Computes the strength of this transfo, which is relative to both
     * the translation and rotation components.
     * @return the strength (Angstroms).
     */
    float strength () const
    {
      float a = m21 - m12;
      float b = m02 - m20;
      float c = m10 - m01;
      float theta_rad = atan2f (sqrtf (a*a + b*b + c*c), m00 + m11 + m22 - 1.0f);
      return sqrtf (m03*m03 + m13*m13 + m23*m23 + alpha_square * theta_rad * theta_rad);
    }

    /**
     * Same as strength() method, but provides access to the metric components.
     * @param tvalue2 placeholder for translation component (Angstrom^2).
     * @param rvalue2 placeholder for rotation component (Angstrom^2).
     * @return the strength (Angstroms).
     */
    float strength (float& tvalue2, float& rvalue2) const;

    /**
     * M: m -> m'
     * N: n -> n'
     * Computes the strength of the transfo that represents n' in m''s
     * referential when m and n are both aligned to the global referential
     * (This transfo is M^-1 * N).
     * @param m the transfo to compare to.
     * @return the computed distance (Angstroms).
     */
    float distance (const HomogeneousTransfo &m) const
    {
      return (this->invert () * m).strength ();
    }

    /**
     * Computes the squared distance between two transfo.  For more details,
     * see a discussion of the metric used in P. Gendron, S. Lemieuxs
     * and F. Major (2001) Quantitative analysis of nucleic acid
     * three-dimensional structures, J. Mol. Biol. 308(5):919-936
     * @param m the other transfo.
     * @return the computed distance.
     */
    float squareDistance (const HomogeneousTransfo &m) const;

    /**
     * Same as distance() method, but using unstable invert() method.
     * @param m the transfo to compare to.
     * @return the computed distance (Angstroms).
     */
    float distance_unstable (const HomogeneousTransfo &m) const
    {
      return (this->invert_unstable () * m).strength ();
    }

    /**
     * Computes the euclidian RMSD between this transfo and another transfo, viewing
     * matrices has 12D vectors (ignoring last row).
     * @param t the transfo to compare to.
     * @return the computed euclidian distance (Angstroms).
     */
    double euclidianRMSD (const HomogeneousTransfo& t) const;

    /**
     * Computes the homogeneous transformation matrix that represents the
     * coordinate frame aligned onto three arbitrary points P1, P2 and P3
     * in such a manner that P1 is the frame's origin, P2 is on the Y axis 
     * and P3 is on the YZ plane.
     * @param p1 point P1.
     * @param p2 point P2.
     * @param p3 point P3.
     * @return the coordinate frame.
     */
    static HomogeneousTransfo align (const Vector3D &p1, const Vector3D &p2, const Vector3D &p3)
    {
      Vector3D v = (p2 - p1).normalize ();
      Vector3D u = ((p2 - p1).cross(p3 - p1)).normalize ();
      return HomogeneousTransfo::frame (u, v, (u.cross (v)).normalize (), p1);
    }

    /**
     * Computes the homogeneous transformation matrix that represents the
     * coordinate frame <u,v,w> with origin at O in the standard Euclidian
     * reference frame. Assumes that <u,v,w> is an orthonormal basis of R^3.
     * @param u normal vector u both orthogonal to v and w.
     * @param v normal vector v both orthogonal to u and w.
     * @param w normal vector w both orthogonal to u and v.
     * @param o point O, the frame's origin.
     * @return the coordinate frame.
     */
    static HomogeneousTransfo frame (const Vector3D& u, const Vector3D& v, const Vector3D& w, const Vector3D& o)
    {
      return HomogeneousTransfo (u.getX (), v.getX (), w.getX (), o.getX (),
				 u.getY (), v.getY (), w.getY (), o.getY (),
				 u.getZ (), v.getZ (), w.getZ (), o.getZ ());
    }

    // I/O  -----------------------------------------------------------------
    
    /**
     * Outputs to a stream.
     * @param os the output stream.
     * @return the written stream.
     */
    ostream& write (ostream& os) const;

    /**
     * Outputs to a binary stream.
     * @param obs the output stream.
     * @return the written stream.
     */
    oBinstream& write (oBinstream& obs) const;

    /**
     * Set transfo from a binary stream.
     * @param ibs the input stream.
     * @return the read stream.
     */
    iBinstream& read (iBinstream& ibs);
  };
  
  /**
   * Reads a tranfo from the input binary stream.
   * @param ibs the input binary stream.
   * @param obj the transfo to fill.
   * @return the used input binary stream.
   */
  iBinstream& operator>> (iBinstream& ibs, HomogeneousTransfo& obj);
  
  /**
   * Writes the transfo to the output binary stream.
   * @param obs the output binary stream.
   * @param obj the transfo to write.
   * @return the used output binary stream.
   */
  oBinstream& operator<< (oBinstream& obs, const HomogeneousTransfo& obj);

}



namespace std
{
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream& operator<< (ostream& os, const mccore::HomogeneousTransfo& obj);
  
}

#endif
