//                              -*- Mode: C++ -*- 
// HomogeneousTransfo.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar  7 14:10:00 2003
// $Revision: 1.1 $


#ifndef _HomogeneousTransfo_h_
#define _HomogeneousTransfo_h_

#include <iostream>

#include "Vector3D.h"

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore
{

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
 * @version $Id: HomogeneousTransfo.h,v 1.1 2003-04-03 21:55:55 gendrop Exp $
 */
class HomogeneousTransfo
{
  /**
   * The tranfo matrix.
   */
  float *matrix;
  

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  HomogeneousTransfo () { 
    matrix = new float[16];
    setIdentity (); 
  }

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
		     float n30, float n31, float n32, float n33) {
    matrix = new float[16];
    set(n00, n01, n02, n03, 
	n10, n11, n12, n13, 
	n20, n21, n22, n23,
	n30, n31, n32, n33);
  }
  
  /**
   * Creates a transfo with an openGL matrix.
   * @param openGLMatrix the array of values in openGL format.
   */
  HomogeneousTransfo (const float* openGLMatrix) {
    matrix = new float[16];
    memcpy (matrix, openGLMatrix, 16*sizeof (float));
  }
  
  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  HomogeneousTransfo (const HomogeneousTransfo &other) {
    matrix = new float[16];
    memcpy (matrix, other.matrix, 16*sizeof (float));
  }
  
  /**
   * Destroys the object.
   */
  virtual ~HomogeneousTransfo () {
    delete matrix;
  }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  virtual HomogeneousTransfo& operator= (const HomogeneousTransfo &other);

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
	   float n30, float n31, float n32, float n33) {
    matrix[ 0] = n00; matrix[ 4] = n01; matrix[ 8] = n02; matrix[12] = n03;
    matrix[ 1] = n10; matrix[ 5] = n11; matrix[ 9] = n12; matrix[13] = n13;
    matrix[ 2] = n20; matrix[ 6] = n21; matrix[10] = n22; matrix[14] = n23;
    matrix[ 3] = n30; matrix[ 7] = n31; matrix[11] = n32; matrix[15] = n33;
  }
  
  /**
   * Sets the matrix to identity.
   */
  void setIdentity() {
    set (1.0f, 0.0f, 0.0f, 0.0f, 
	 0.0f, 1.0f, 0.0f, 0.0f, 
	 0.0f, 0.0f, 1.0f, 0.0f, 
	 0.0f, 0.0f, 0.0f, 1.0f);
  }
  
  /**
   * Determines if the matrix is set to identity.
   * @return if the HomogeneousTransfo is set to identity.
   */
  bool isIdentity() {
    return (matrix[0] == 1 && matrix[ 4] == 0 && matrix[ 8] == 0 && matrix[12] == 0
	    && matrix[1] == 0 && matrix[ 5] == 1 && matrix[ 9] == 0 && matrix[13] == 0
	    && matrix[2] == 0 && matrix[ 6] == 0 && matrix[10] == 1 && matrix[14] == 0
	    && matrix[3] == 0 && matrix[ 7] == 0 && matrix[11] == 0 && matrix[15] == 1);
  }
  
  // METHODS --------------------------------------------------------------

  /**
   * Calculates the matrix multiplication.
   * @param right the right matrix.
   * @return the resulting matrix.
   */
  HomogeneousTransfo operator* (const HomogeneousTransfo &right) const {
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

  /**
   * Calculates and assign the matrix multiplication.
   * @param right the right matrix.
   * @return the resulting matrix.
   */
  HomogeneousTransfo& operator*= (const HomogeneousTransfo &right) {
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

  /**
   * Applies the transfo to the given point.
   * @param v the original point.
   * @return the transformed point.
   */
  inline Vector3D operator* (const Vector3D &v) const {
    return Vector3D(matrix[0]*v.getX () + matrix[4]*v.getY () + matrix[8]*v.getZ () + matrix[12],  
		    matrix[1]*v.getX () + matrix[5]*v.getY () + matrix[9]*v.getZ () + matrix[13], 
		    matrix[2]*v.getX () + matrix[6]*v.getY () + matrix[10]*v.getZ () + matrix[14]);
  }
  
  
  /**
   * Gets a transfo containing the rotation part of this transfo.
   * @return the transfo.
   */
  HomogeneousTransfo getRotation () {
    return HomogeneousTransfo (matrix[0], matrix[4], matrix[8],  0,
			       matrix[1], matrix[5], matrix[9],  0,
			       matrix[2], matrix[6], matrix[10], 0,
			       0, 0, 0, 1);
  }
  
  /**
   * Gets the translation vector from the homogeneous matrix.
   * @return the translation vector.
   */
  HomogeneousTransfo getTranslation () {
    return HomogeneousTransfo (1, 0, 0, matrix[12],
			       0, 1, 0, matrix[13],
			       0, 0, 1, matrix[14],
			       0, 0, 0, 1);
  }
  

  /**
   * Calculates the homogeneous rotation matrix by a given angle
   * about a given axis.
   * @param axis the Vector3D representing normalised rotation axis.
   * @param theta the angle to rotate by (in radians).
   * @return the new HomogeneousTransfo with the given rotation.
   */
  static HomogeneousTransfo rotation (const Vector3D &axis, float theta) {
	float cosTh;
	float sinTh;
	float versTh;
	float x;
	float y;
	float z;

	cosTh = (float) cos (theta);
	sinTh = (float) sin (theta);
	versTh = 1 - cosTh;
	x = axis.getX ();
	y = axis.getY ();
	z = axis.getZ ();
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

  /**
   * Rotates the current HomogeneousTransfo given an angle about a given axis.
   * @param axis the vector representing normalised rotation axis.
   * @param theta the angle to rotate by (in radians).
   * @return the new rotated HomogeneousTransfo.
   */
  HomogeneousTransfo rotate (const Vector3D &axis, float theta) const {
    return (*this * HomogeneousTransfo::rotation (axis, theta));
  }
  
  /**
   * Calculates the rotation of the homogeneous matrix given three
   * rotation angles.
   * @param theta_x the x rotation angle (in radians).
   * @param theta_y the y rotation angle (in radians).
   * @param theta_z the z rotation angle (in radians).
   * @return the new HomogeneousTransfo.
   */
  HomogeneousTransfo rotate(float theta_x, float theta_y, float theta_z) const {
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
  
  /**
   * Translates the homogeneous translation matrix by a given
   * vector.
   * @param t the vector representing normalised translation.
   * @return the new HomogeneousTransfo with the given translation.
   */
  static HomogeneousTransfo translation (const Vector3D &t) {
    return HomogeneousTransfo(1, 0, 0, t.getX (),
			      0, 1, 0, t.getY (),
			      0, 0, 1, t.getZ (),
			      0, 0, 0, 1);
  }

  /**
   * Translates the homogeneous matrix given a translation vector.
   * @param t the translation vector.
   * @return the new HomogeneousTransfo with the given translation.
   */
  HomogeneousTransfo translate (const Vector3D &t) const {
    return (*this * HomogeneousTransfo::translation(t));
  }
  
  /**
   * Translates the matrix
   * @param x the amplitude of translation in the x direction.
   * @param y the amplitude of translation in the y direction.
   * @param z the amplitude of translation in the z direction.
   * @return this.
   */
  HomogeneousTransfo translate (float x, float y, float z) const {
    return (*this * HomogeneousTransfo(1, 0, 0, x,
				       0, 1, 0, y,
				       0, 0, 1, z,
				       0, 0, 0, 1));
  }
  
  /**
   * Returns the homogeneous matrix to it's inverse.
   * @return the new HomogeneousTransfo inverse.
   */
  HomogeneousTransfo invert () const {
    if ((matrix[3] + matrix[7] + matrix[11]) != 0.0)
      cerr << "HTM containing scale cannot be inverted." << endl;
    return HomogeneousTransfo (matrix[0], matrix[1], matrix[2], 
			       -(matrix[12]*matrix[0] + matrix[13]*matrix[1] + matrix[14]*matrix[2]),
			       matrix[4], matrix[5], matrix[6], 
			       -(matrix[12]*matrix[4] + matrix[13]*matrix[5] + matrix[14]*matrix[6]),
			       matrix[8], matrix[9], matrix[10], 
			       -(matrix[12]*matrix[8] + matrix[13]*matrix[9] + matrix[14]*matrix[10]),
			       matrix[3], matrix[7], matrix[11], 
			       matrix[15]);
  }
  
  /**
   * Calculates the distance from the homogeneous matrix to origin.  The
   * rotation factor is also included.
   * @return the distance.
   */
  float strength () const {
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
    
  
  /**
   * Computes the distance between two transfo.  For more details,
   * see a discussion of the metric used in P. Gendron, S. Lemieuxs
   * and F. Major (2001) Quantitative analysis of nucleic acid
   * three-dimensional structures, J. Mol. Biol. 308(5):919-936
   * @param m the other transfo.
   * @return the computed distance.
   */
  float distance (const HomogeneousTransfo &m) const {
    HomogeneousTransfo a = *this;
    HomogeneousTransfo bi = m;
    bi = bi.invert ();
    
    HomogeneousTransfo a_bi = a * bi;
    HomogeneousTransfo bi_a = bi * a;
    return (a_bi.strength () + bi_a.strength ()) / 2;
  }


  /**
   * Returns the transfo needed to align the points p1, p2, p3 with
   * the Euclidian reference frame centered at (0,0,0).
   * @param p1 the first vector.
   * @param p2 the second vector.
   * @param p3 the third vector.
   * @return the new aligned HomogeneousTransfo.
   */
  static HomogeneousTransfo align (const Vector3D &p1, const Vector3D &p2, const Vector3D &p3) {
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
