//                              -*- Mode: C++ -*- 
// Atom.h
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:00:09 2003
// $Revision: 1.8 $
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


#ifndef _mccore_Atom_h_
#define _mccore_Atom_h_

#include <iostream>

#include "Vector3D.h"

using namespace std;



namespace mccore
{
  class AtomType;
  class iBinstream;
  class iPdbstream;
  class oBinstream;
  class oPdbstream;

  

  /**
   * @short Derived from Vector3D, this class adds the type of the atom.
   *
   * Derived from Vector3D, this class adds the type of the atom.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: Atom.h,v 1.8 2005-01-05 01:41:45 larosem Exp $
   */
  class Atom : public Vector3D
  {
    /**
     * The type of the atom.
     */
    const AtomType *type;
    
    /**
     * The serial number for use in PDB output.
     */
    mutable int serialNo;

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
     * @param ax the x coordinate.
     * @param ay the y coordinate.
     * @param az the z coordinate.
     * @param type the atom type.
     * @param loc the atom alternate location id (default = ' ').
     */
    void setAll (float ax, float ay, float az, const AtomType *t) {
      set (ax, ay, az);
      type = t;
    }

    /**
     * Sets the serial number of atoms in PDB files.
     */
    void setSerialNo (int serial) const { serialNo = serial; }

    /**
     * Sets the serial number of the atom when dumped in a PDB file.
     */
    int getSerialNo () const { return serialNo; }

    // METHODS --------------------------------------------------------------

    /**
     * Returns the color of the given atom as a Vector3D in RGB space.
     * @return the atom color.
     */
    Vector3D getColor () const;    
    

    // I/O  -----------------------------------------------------------------

  };

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

  /**
   * Reads an atom from the stream.
   * @param at the atom to read.
   * @return the Pdbstream.
   */
  iPdbstream& operator>> (iPdbstream &ips, Atom &at);
    
  /**
   * Writes an atom to the pdb stream.
   * @param at the atom to write.
   * @return the output pdb stream used.
   */
  oPdbstream& operator<< (oPdbstream &ops, const Atom& at);

}



namespace std
{
  
  /**
   * Ouputs the atom to the stream.
   * @param os the output stream.
   * @param atom the atom.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::Atom &atom);
  
}

#endif
