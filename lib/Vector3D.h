// Vector3D.h
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


#ifndef _mccore_Vector3D_h_
#define _mccore_Vector3D_h_

#include <iostream>
#include <math.h>

using namespace std;



namespace mccore 
{
  class HomogeneousTransfo;
  class iBinstream;
  class oBinstream;


  /**
   * @short A Vector in 3D space.
   *
   * The 3D vector class represents simultaneously a location 
   * in space (a point) as well as a displacement.
   */
  class Vector3D
  {
  public:
    /**
     * The x coordinate.
     */
    float x;

    /**
     * The y coordinate.
     */
    float y;

    /**
     * The z coordinate.
     */
    float z;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Vector3D () : x (0), y (0), z (0) { }

    /**
     * Initializes the object.
     * @param xp the x coordinate.
     * @param yp the y coordinate.
     * @param zp the z coordinate.
     */
    Vector3D (float xp, float yp, float zp) : x (xp), y (yp), z (zp) { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Vector3D (const Vector3D &other) : x (other.x), y (other.y), z (other.z) { }

    /**
     * Destroys the object.
     */
    virtual ~Vector3D () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Vector3D& operator= (const Vector3D &other)
    {
      if (this != &other)
      {
        x = other.x;
        y = other.y;
        z = other.z;
      }
      return *this;
    }

    /**
     * Indicates whether some other object is "equal to" this one.
     * @param other the reference object with which to compare.
     * @return true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const Vector3D &other) const
    {
      return (x == other.x && y == other.y && z == other.z);
    }

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the x coordinate.
     * @return the x coordinate.
     */
    float getX () const { return x; }

    /**
     * Gets the y coordinate.
     * @return the y coordinate.
     */
    float getY () const { return y; }

    /**
     * Gets the z coordinate.
     * @return the z coordinate.
     */
    float getZ () const { return z; }

    /**
     * Sets the x coordinate.
     * @param xp the new x coordinate.
     */
    void setX (float xp) { x = xp; }

    /**
     * Sets the y coordinate.
     * @param nY the new y coordinate.
     */
    void setY (float yp) { y = yp; }

    /**
     * Sets the z coordinate.
     * @param nZ the new z coordinate.
     */
    void setZ(float zp) { z = zp; }

    /**
     * Sets the coordinates.
     * @param xp x coordinate.
     * @param yp y coordinate.
     * @param zp z coordinate.
     */
    void set(float xp, float yp, float zp)
    {
      x = xp;
      y = yp;
      z = zp;
    }

    // METHODS --------------------------------------------------------------

    /**
     * Normalizes the vector.
     * @return a new normalized vector.
     */
    Vector3D normalize() const
    {
      float l = length();
      return Vector3D (x / l, y / l, z / l);
    }
 
    /**
     * Calculates the distance between the vector and the origin.
     * @return the length of the vector.
     */
    float length() const 
    {
      return (float) sqrt (squareLength());
    }

    /**
     * Calculates the square distance between the vector and the origin.
     * @return the square length of the vector.
     */
    float squareLength () const 
    {
      return (x*x + y*y + z*z);
    }

    /**
     * Negates the coordinates.
     * @param v the vector.
     * @return a new vector.
     */
    Vector3D operator- () const
    {
      return Vector3D(-x, -y, -z);
    }

    /**
     * Substracts and assigns the coordinates.
     * @param v the vector.
     * @return itself.
     */
    const Vector3D& operator-= (const Vector3D &v)
    {
      x -= v.x; 
      y -= v.y;
      z -= v.z;
      return *this;
    }

    /**
     * Adds and assigns the coordinates.
     * @param v the vector.
     * @return itself.
     */
    const Vector3D& operator+= (const Vector3D &v)
    {
      x += v.x; 
      y += v.y;
      z += v.z;
      return *this;
    }

    /**
     * Calculates the cross product between two vectors.
     * @param aVector the aVector vectors.
     * @return a new vector.
     */
    Vector3D cross (const Vector3D &v) const 
    {
      return Vector3D(y * v.z - z * v.y,
                      z * v.x - x * v.z,
                      x * v.y - y * v.x);
    }

    /**
     * Calculates the dot-product over the vectors.
     * @param v the vector.
     * @return the dot product.
     */
    float dot (const Vector3D &v) const 
    {
      return x * v.x + y * v.y + z * v.z;
    }

    /**
     * Calculates and assigns the scalar multiplication.
     * @param value the scalar.
     * @return a new vector.
     */
    const Vector3D& operator*= (float value) 
    {
      x *= value; 
      y *= value;
      z *= value;
      return *this;
    }

    /**
     * Calculates and assigns the scalar quotient.
     * @param value the scalar.
     * @return a new vector.
     */
    const Vector3D& operator/= (float value) 
    {
      x /= value; 
      y /= value;
      z /= value;
      return *this;
    }

    /**
     * Calculates the distance between two points.
     * @param aVector the point.
     * @return the distance.
     */
    float distance (const Vector3D &aVector) const 
    {
      return (float)sqrt(squareDistance(aVector));
    }

    /**
     * Calculates the squared distance between two points.
     * @param aVector the point.
     * @return the squared distance.
     */
    float squareDistance (const Vector3D &aVector) const 
    {
      return (float) ((x - aVector.x) * (x - aVector.x)
                    + (y - aVector.y) * (y - aVector.y)
                    + (z - aVector.z) * (z - aVector.z));
    }

    /**
     * Calculates the angle between vectors a, the object and c.
     * The returned angle is expressed in radian.
     * @param a the first vector.
     * @param c the third vector.
     * @return the angle expressed in radian.
     */
    float angle (const Vector3D &a, const Vector3D &c) const;

    /**
     * Calculates the torsion angle around bond b-c with a sign to indicate the
     * direction.  The returned angle is expressed in radian in the range [-180,180].
     * @param a the first vector.
     * @param c the third vector.
     * @param d the fourth vector
     * @return the signed torsion angle expressed in radian.
     */
    float torsionAngle (const Vector3D &a, const Vector3D &c, const Vector3D &d) const;

    /**
     * Modifies the vector by the transformation.
     * @param tfo the tranfo.
     * @return itself.
     */
    virtual Vector3D& transform (const HomogeneousTransfo &tfo);

    // I/O  -----------------------------------------------------------------

    /**
     * Outputs to a stream.
     * @param out the output stream.
     * @return the output stream used.
     */
    ostream &output (ostream &out) const;

  };

  /**
   * Inputs the point from a binary stream.
   * @param is the input binary stream.
   * @param p the point.
   * @return the input stream used.
   */
  iBinstream& operator>> (iBinstream &ibs, Vector3D &p);

  /**
   * Outputs the point to a binary stream.
   * @param obs the output binary stream.
   * @param p the point.
   * @return the output stream used.
   */
  oBinstream& operator<< (oBinstream &obs, const Vector3D &p);


  /**
   * Subtract the coordinates.
   * @param v the vector.
   * @return a new vector.
   */
  const Vector3D operator- (const Vector3D &v, const Vector3D &w);

  /**
   * Adds the coordinates.
   * @param v the vector.
   * @return a new vector.
   */
  const Vector3D operator+ (const Vector3D &v, const Vector3D &w);

  /**
   * Calculates the dot-product over the vectors.
   * @param v the vector.
   * @return the dot product.
   */
  float operator* (const Vector3D &v, const Vector3D &w);

  /**
   * Calculates the scalar multiplication.
   * @param value the scalar.
   * @return a new vector.
   */
  const Vector3D operator* (const Vector3D &v, float value);

  /**
   * Calculates the scalar multiplication.
   * @param value the scalar.
   * @return a new vector.
   */
  const Vector3D operator* (float value, const Vector3D &v);

  /**
   * Calculates the scalar quotient.
   * @param value the scalar.
   * @return a new vector.
   */
  const Vector3D operator/ (const Vector3D &v, float value);

}



namespace std
{

  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::Vector3D &v);

}

#endif
