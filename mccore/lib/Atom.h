//                              -*- Mode: C++ -*- 
// Atom.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:00:09 2003
// $Revision: 1.3 $
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


#ifndef _Atom_h_
#define _Atom_h_

#include <iostream>

#include "Vector3D.h"

using namespace std;

class iBinstream;
class oBinstream;

namespace mccore {

  class AtomType;

  /**
   * @short Derived from Vector3D, this class adds the type of the atom.
   *
   * Derived from Vector3D, this class adds the type of the atom.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: Atom.h,v 1.3 2003-07-11 21:27:00 gendrop Exp $
   */
  class Atom : public Vector3D
  {
    /**
     * The type of the atom.
     */
    const AtomType *type;
    
    // LIFECYCLE ------------------------------------------------------------

  public:

    /**
     * Initializes the object.
     */
    Atom ();

    /**
     * Initializes the atom with coordinates and a type.
     * @param x the x coordinate.
     * @param y the y coordinate.
     * @param z the z coordinate.
     * @param aType the atom type.
     */
    Atom (float x, float y, float z, const AtomType *aType);
    
    /**
     * Initializes the atom with a point and a type.
     * @param aPoint the coordinates
     * @param aType the atom type.
     */
    Atom (Vector3D aPoint, const AtomType *aType);

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Atom (const Atom &other);
    
    /**
     * Clones the atom.
     * @return a copy of itself.
     */
    virtual Atom* clone () const;

    /**
     * Destroys the object.
     */
    virtual ~Atom () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    Atom& operator= (const Atom &other);

    /**
     * Indicates whether some other atom is "equal to" this one.
     * @param other the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const Atom &other) const;

    /**
     * Indicates whether some other atom is "not equal to" this one.
     * @param other the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator!= (const Atom &other) const;

    /**
     * Imposes a total ordering on the Atom objects.  They are sorted
     * by AtomType.
     * @param other the atom to compare.
     * @return true if this atom is less than the other.
     */
    bool operator< (const Atom &other) const;


    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the atom type.
     * @return the atom type.
     */
    const AtomType* getType () const {
      return type;
    }
    
    /**
     * Sets the atom type.
     * @param type the new atom type.
     */
    void setType (const AtomType *t) {
      type = t;
    }
    
    /**
     * Sets every field of the atom.
     * @param x the x coordinate.
     * @param y the y coordinate.
     * @param z the z coordinate.
     * @param type the atom type.
     * @param loc the atom alternate location id (default = ' ').
     */
    void setAll (float x, float y, float z, const AtomType *t) {
      set (x, y, z);
      type = t;
    }

    // METHODS --------------------------------------------------------------

    /**
     * Returns the color of the given atom as a Vector3D in RGB space.
     * @return the atom color.
     */
    Vector3D color () const;    
    

    // I/O  -----------------------------------------------------------------

  };

  /**
   * Ouputs the atom to the stream.
   * @param os the output stream.
   * @param atom the atom.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const Atom &atom);
  
  /**
   * Inputs the atom from the binary stream.
   * @param ibs the input binary stream.
   * @param atom the atom to fill.
   * @return the input binary stream used.
   */
  iBinstream& operator>> (iBinstream &ibs, Atom &atom);


  /**
   * Outputs the atom to the binary stream.
   * @param obs the output binary stream.
   * @param atom the atom.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &obs, const Atom &atom);

}

#endif
