//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// $Revision: 1.16 $
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
#include <utility>

#include "Vector3D.h"

using namespace std;



namespace mccore
{

  class iBinstream;
  class oBinstream;
  
  
  
  /**
   * Homogeneous transformation matrices.  The internal representation
   * matches the one of the OpenGL library.
   *
   * <pre>
   * m = matrix
   * | m0  m4  m8  m12  |      | n00  n01  n02  n03 |
   * | m1  m5  m9  m13  |  ==  | n10  n11  n12  n13 |
   * | m2  m6  m10 m14  |      | n20  n21  n22  n23 |
   * | m3  m7  m11 m15  |      | n30  n31  n32  n33 |
   * </pre>
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: HomogeneousTransfo.h,v 1.16 2005-01-11 19:39:39 thibaup Exp $
   */
  class HomogeneousTransfo
  {
    /**
     * The tranfo matrix.
     */
    float *matrix;
    

  public:

    /**
     * The 4x4 identity matrix.
     */
    static const HomogeneousTransfo identity;

    /**
     * The squared scale ratio between angle and distance (Ang^2 / rad^2)
     */
    static const float alpha_square;
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     */
    HomogeneousTransfo ();
    
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
		       float n20, float n21, float n22, float n23,
		       float n30 = 0, float n31 = 0, float n32 = 0, float n33 = 1);
    
    /**
     * Creates a transfo with an openGL matrix.
     * @param openGLMatrix the array of values in openGL format.
     */
    HomogeneousTransfo (const float* openGLMatrix);
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    HomogeneousTransfo (const HomogeneousTransfo &other);
    
    /**
     * Destroys the object.
     */
    virtual ~HomogeneousTransfo ();
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    HomogeneousTransfo& operator= (const HomogeneousTransfo &other);
    
    // ACCESS ---------------------------------------------------------------
    
    /**
     * Returns an openGL matrix.
     * @return an array of values corresponding to the open GL matrix.
     */
    float* toOpenGL() {
      return matrix;
    }
    
    /**
     * Gets the element at position i.
     * @param i the position.
     * @return the element at position i.
     */
    float elementAt(int i) const {
      return matrix[i];
    }
    
    /**
     * Sets the element at position i.
     * @param x the new value.
     * @param i the position.
     */
    void setElementAt(float x, int i) {
      matrix[i] = x;
    }
    
    /**
     * Gets the element of row i column j.
     * @param i the row number.
     * @param j the column number.
     * @return the element[i,j].
     */
    float elementAt(int i,int j) const {
      return matrix[i + j * 4];
    }
    
    /**
     * Sets the element of row i, column j.
     * @param x the new value.
     * @param i the row number.
     * @param j the column number.
     */
    void setElementAt(float x, int i, int j) {
      matrix[i + j * 4] = x;
    }
    
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
    void set(float n00, float n01, float n02, float n03,
	     float n10, float n11, float n12, float n13,
	     float n20, float n21, float n22, float n23,
	     float n30 = 0, float n31 = 0, float n32 = 0, float n33 = 1);
    
    /**
     * Sets the matrix to identity.
     */
    void setIdentity();
    
    /**
     * Determines if the matrix is set to identity.
     * @return if the HomogeneousTransfo is set to identity.
     */
    bool isIdentity();
    
    // METHODS --------------------------------------------------------------
    
    /**
     * Calculates the matrix multiplication.
     * @param right the right matrix.
     * @return the resulting matrix.
     */
    HomogeneousTransfo operator* (const HomogeneousTransfo &right) const;
    
    /**
     * Calculates and assign the matrix multiplication.
     * @param right the right matrix.
     * @return the resulting matrix.
     */
    HomogeneousTransfo& operator*= (const HomogeneousTransfo &right);
    
    /**
     * Applies the transfo to the given point.
     * @param v the original point.
     * @return the transformed point.
     */
    Vector3D operator* (const Vector3D &v) const;
    
    
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
     * Returns the homogeneous matrix to it's inverse.
     * @return the new HomogeneousTransfo inverse.
     */
    HomogeneousTransfo invert () const;
    
    /**
     * [DEPRECATED]
     * Calculates the distance from the homogeneous matrix to origin.  The
     * rotation factor is also included.
     * @return the distance.
     */
    float strength_old () const;

    /**
     * Computes the strength of this transfo, which is relative to both
     * the translation and rotation components.
     * @return the strength (Angstroms).
     */
    float strength (float* tvalue = 0, float* rvalue = 0) const;

    /**
     * Computes the rms of <i,j,k> moved by this transfo from the global referential.
     * @return the rmsd (Angstroms).
     */
    float rmsd () const;
    
    /**
     * [DEPRECATED]
     * Computes the distance between two transfo.  For more details,
     * see a discussion of the metric used in P. Gendron, S. Lemieuxs
     * and F. Major (2001) Quantitative analysis of nucleic acid
     * three-dimensional structures, J. Mol. Biol. 308(5):919-936
     * @param m the other transfo.
     * @return the computed distance.
     */
    float distance_old (const HomogeneousTransfo &m) const;

    /**
     * M: m -> m'
     * N: n -> n'
     * Computes the strength of the transfo that represents n' in m''s
     * referential when m and n are both aligned to the global referential
     * (This transfo is M^-1 * N).
     * @param m the transfo to compare to.
     * @return the computed distance (Angstroms).
     */
    float distance (const HomogeneousTransfo &m, float* tvalue = 0, float* rvalue = 0) const;

    /**
     * M: m -> m'
     * N: n -> n'
     * Computes the rmsd of the transfo that represents n' in m''s
     * referential when m and n are both aligned to the global referential
     * (This transfo is M^-1 * N).
     * @param m the transfo to compare to.
     * @return the computed rmsd (Angstroms).
     */
    float rmsd (const HomogeneousTransfo &m) const;
    
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
     * Computes the homogeneous transformation matrix that represents the
     * coordinate frame aligned onto three arbitrary points P1, P2 and P3
     * in such a manner that P1 is the frame's origin, P2 is on the Y axis 
     * and P3 is on the YZ plane.
     * @param p1 point P1.
     * @param p2 point P2.
     * @param p3 point P3.
     * @return the coordinate frame.
     */
    static HomogeneousTransfo align (const Vector3D &p1, const Vector3D &p2, const Vector3D &p3);
    
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
    static HomogeneousTransfo frame (const Vector3D& u, const Vector3D& v, const Vector3D& w, const Vector3D& o);

    // I/O  -----------------------------------------------------------------
    
    /**
     * Outputs to a stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    ostream &output (ostream &out) const;
    
  };
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const HomogeneousTransfo &h);
  
  /**
   * Reads a tranfo from the input binary stream.
   * @param ibs the input binary stream.
   * @param obj the transfo to fill.
   * @return the used input binary stream.
   */
  iBinstream& operator>> (iBinstream& ibs, HomogeneousTransfo &obj);
  
  
  
  /**
   * Writes the transfo to the output binary stream.
   * @param obs the output binary stream.
   * @param obj the transfo to write.
   * @return the used output binary stream.
   */
  oBinstream& operator<< (oBinstream& obs, const HomogeneousTransfo &obj);
  
  
}

#endif
