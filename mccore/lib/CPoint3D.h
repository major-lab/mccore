//                              -*- Mode: C++ -*- 
// CPoint3D.h
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Jan 23 15:01:48 2001
// Update Count     : 7
// Status           : Ok.
// 


#ifndef _CPoint3D_h_
#define _CPoint3D_h_


class CTransfo;
class istream;
class ostream;
class iBinstream;
class oBinstream;



/**
 * @short Tri-dimentional coordinates and operations.
 *
 * Class defining the operations on tri-dimentional objects.  It is used as
 * a base class for CAtom.
 *
 * The sum, the multiplication and the quotient are supported as well as an
 * euclidian distance evaluation between two CPoint3D objects.  A few angle
 * methods are given.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CPoint3D
{
  /**
   * The x coordinate.
   */
  float mX;

  /**
   * The y coordinate.
   */
  float mY;

  /**
   * The z coordinate.
   */
  float mZ;

public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  CPoint3D () : mX (0.0), mY (0.0), mZ (0.0) { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CPoint3D (const CPoint3D &right)
    : mX (right.mX), mY (right.mY), mZ (right.mZ) { }

  /**
   * Initializes the object with the coordinates.
   * @param nX the x coordinate.
   * @param nY the y coordinate.
   * @param nZ the z coordinate.
   */
  CPoint3D (float nX, float nY, float nZ) : mX (nX), mY (nY), mZ (nZ) { }

  /**
   * Destructs the object.
   */
  virtual ~CPoint3D () { }

  // OPERATORS -----------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const CPoint3D& operator= (const CPoint3D &right);

  /**
   * Substract the coordinates.
   * @param right the right point.
   * @return a new point.
   */
  CPoint3D operator- (const CPoint3D &right) const;

  /**
   * Substracts and assigns the coordinates.
   * @param right the right point.
   * @return itself.
   */
  const CPoint3D& operator-= (const CPoint3D &right);
  
  /**
   * Adds the coordinates.
   * @param right the right point.
   * @return a new point.
   */
  CPoint3D operator+ (const CPoint3D &right) const;

  /**
   * Adds and assigns the coordinates.
   * @param right the right point.
   * @return itself.
   */
  const CPoint3D& operator+= (const CPoint3D &right);

  /**
   * Calculates the dot-product over the points.
   * @param right the right point.
   * @return the dot product.
   */
  float operator* (const CPoint3D &right) const;

  /**
   * Calculates the scalar multiplication.
   * @param right the scalar.
   * @return a new point.
   */
  CPoint3D operator* (float right) const;

  /**
   * Calculates and assigns the scalar multiplication.
   * @param right the scalar.
   * @return itself.
   */
  const CPoint3D& operator*= (float right);

  /**
   * Calculates the scalar quotient.
   * @param right the scalar.
   * @return a new point.
   */
  CPoint3D operator/ (float right) const;
  
  /**
   * Calculates and assigns the scalar quotient.
   * @param right the scalar.
   * @return itself.
   */
  const CPoint3D& operator/= (float right);
  
  /**
   * Calculates the distance between two points.
   * @param right the right point.
   * @return the distance.
   */
  float operator| (const CPoint3D &right) const;

  /**
   * Calculates the squared distance between two points.
   * @param right the right point.
   * @return the squared distance.
   */
  float operator|| (const CPoint3D &right) const;

  /**
   * Negates the coordinates.
   * @return a new point.
   */
  CPoint3D operator- () const;

  // ACCESS --------------------------------------------------------

  /**
   * Sets the coordinates.
   * @param nX the x coordinate.
   * @param nY the y coordinate.
   * @param nZ the z coordinate.
   * @return itself.
   */
  const CPoint3D& SetXYZ (float nX, float nY, float nZ);

  /**
   * Gets the x coordinate.
   * @return the x coordinate.
   */
  float &Get (int index) { 
    switch (index) {
    case 0: return mX;
    case 1: return mY;
    case 2: return mZ;
    }
    return mX;
  }

  /**
   * Gets the x coordinate.
   * @return the x coordinate.
   */
  float GetX () const { return mX; }

  /**
   * Gets the y coordinate.
   * @return the y coordinate.
   */
  float GetY () const { return mY; }

  /**
   * Gets the z coordinate.
   * @return the z coordinate.
   */
  float GetZ () const { return mZ; }

  /**
   * Sets the x coordinate.
   * @param nX the new x coordinate.
   */
  void SetX (float nX) { mX = nX; }

  /**
   * Sets the y coordinate.
   * @param nY the new y coordinate.
   */
  void SetY (float nY) { mY = nY; }

  /**
   * Sets the z coordinate.
   * @param nZ the new z coordinate.
   */
  void SetZ (float nZ) { mZ = nZ; }

  // METHODS -------------------------------------------------------
  
  /**
   * Normalizes the point.
   * @return itself.
   */
  CPoint3D& Normalize ();

  /**
   * Calculates the distance between the point and the origin.
   * @return the distance.
   */
  float Length () const;

  /**
   * Calculates the angle between points A, the object and C.  The returned
   * angle is expressed in radian.
   * @param A the first point.
   * @param C the third point.
   * @return the angle expressed in radian.
   */
  float Angle (const CPoint3D &A, const CPoint3D &C) const;

  /**
   * Calculates the torsion angle around bond B-C.  The returned angle
   * is expressed in radian.
   * @param A the first point.
   * @param C the third point.
   * @param D the fourth point
   * @return the unsigned torsion angle expressed in radian.
   */
  float TorsionAngle (const CPoint3D &A, const CPoint3D &C,
		      const CPoint3D &D) const;

  /**
   * Calculates the torsion angle around bond B-C with a sign to indicate the
   * direction.  The returned angle is expressed in radian.
   * @param A the first point.
   * @param C the third point.
   * @param D the fourth point
   * @return the signed torsion angle expressed in radian.
   */
  float TorsionAngleDir (const CPoint3D &A, const CPoint3D &C,
			 const CPoint3D &D) const;

  /**
   * Calculates the cross product between two points.
   * @param right the right point.
   * @return a new point.
   */
  CPoint3D Cross (const CPoint3D &right) const;

  /**
   * Applies the tranfo over the point.
   * @param tfo the tranfo.
   * @return itself.
   */
  CPoint3D& Transform (const CTransfo &tfo);
  
  // I/O -------------------------------------------------------------
};



/**
 * Inputs the point from a stream.
 * @param is the input stream.
 * @param p the point.
 * @return the input stream used.
 */
istream& operator>> (istream &is, CPoint3D &p);



/**
 * Outputs the point to a stream.
 * @param os the output stream.
 * @param p the point.
 * @return the output stream used.
 */
ostream& operator<< (ostream &os, const CPoint3D &p);



/**
 * Inputs the point from a binary stream.
 * @param is the input binary stream.
 * @param p the point.
 * @return the input stream used.
 */
iBinstream& operator>> (iBinstream &ibs, CPoint3D &p);



/**
 * Outputs the point to a binary stream.
 * @param obs the output binary stream.
 * @param p the point.
 * @return the output stream used.
 */
oBinstream& operator<< (oBinstream &obs, const CPoint3D &p);

#endif
