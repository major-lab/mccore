//                              -*- Mode: C++ -*- 
// CAtom.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 22 11:05:26 2002
// Update Count     : 12
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


#ifndef _CAtom_h_
#define _CAtom_h_


#include <function.h>
#include <stdio.h>

#include "CPoint3D.h"
#include "AtomType.h"

class ostream;
class iBinstream;
class oBinstream;
class iPdbstream;
class oPdbstream;


/**
 * @short Atom implementation.
 *
 * Derived from CPoint3D, thisclass adds the type and a serial number to
 * the point.
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CAtom : public CPoint3D
{
  /**
   * The type of the atom.
   */
  t_Atom *mType;

  /**
   * Field AltLoc in PDB format.
   */
  char altLocId;

  /**
   * The serial number of the atom when it is dumped in a pdb file.
   */
  mutable unsigned int mAtomSerNo;
  
public:

  /**
   * Count of the total number of atom allocated.
   */
  static int count;

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the objet.
   */
  CAtom ();

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  CAtom (const CAtom &right);

  /**
   * Initializes the objet with the coordinates and atom type.
   * @param x the x coordinate.
   * @param y the y coordinate.
   * @param z the z coordinate.
   * @param type the atom type.
   */
  CAtom (float x, float y, float z, t_Atom *type);

  /**
   * Clones the atom.
   * @return a copy of itself.
   */
  virtual CAtom* clone () const { return new CAtom (*this); }
  
  /**
   * Destructs the object.  The atom count is decreased.
   */
  virtual ~CAtom () { count--; }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  CAtom& operator= (const CAtom &right);

  /**
   * Tests whether the atom is typed.
   * @return the thruth value.
   */
  operator bool () const { return mType != 0; }

  /**
   * Tests whether the atom is of the type t.
   * @param t the atom type.
   * @return the test result.
   */
  bool operator== (const t_Atom *t) const { return mType == t; }

  /**
   * Tests whether atoms are equals.  The discrimination is made over the
   * atom type.
   * @param right the right atom.
   * @return the result of the test.
   */
  bool operator== (const CAtom &right) const
  { return mType == right.GetType (); }

  /**
   * Tests whether atoms are not equals.  This is the negation of
   * operator==.
   * @param right the right atom.
   * @return the result of the test.
   */
  bool operator!= (const CAtom &right) const { return ! operator== (right); }

  /**
   * Tests whether the atoms is not of the type t.  This is the negation of
   * operator==.
   * @param type the atom type.
   * @return the result of the test.
   */
  bool operator!= (const t_Atom *type) const { return ! operator== (type); }

  /**
   * Tests whether the atom is less than the right one.  The order is based
   * over the type address.  The address over the same type is unique, so
   * the address can be used to order atoms in residues.
   * @param right the right atom.
   * @return the result of the test.
   */
  bool operator< (const CAtom &right) const
  { return mType < right.GetType (); }
  
  // METHODS -------------------------------------------------------

  /**
   * Gets the atom type.
   * @return the atom type.
   */
  t_Atom* GetType () const { return mType; }

  /**
   * Sets the atom type.
   * @param type the new atom type.
   */
  void SetType (t_Atom *type) { mType = type; }

  /**
   * Gets the atom serial number for pdb conect output.
   * @return the atom serial number.
   */
  unsigned int GetAtomSerNo () const { return mAtomSerNo; }

  /**
   * Sets the atom serial number for pdb conect output.  The field is
   * mutable.
   * @param k the serial number.
   */
  void SetAtomSerNo (unsigned int k) const { mAtomSerNo = k; }
  
  /**
   * Gets the atom alternate location id.
   * @return the alternate location id.
   */
  char GetAltLocId () const { return altLocId; }

  /**
   * Sets the atom alternate location id.
   * @param the new alternate location id.
   */
  void SetAltLocId (char id) { altLocId = id; }

  /**
   * Sets every field of the atom.
   * @param x the x coordinate.
   * @param y the y coordinate.
   * @param z the z coordinate.
   * @param type the atom type.
   * @param loc the atom alternate location id (default = ' ').
   */
  void SetAll (float x, float y, float z, t_Atom *type, char loc = ' ');

  // I/O ------------------------------------------------------------
};



/**
 * Ouputs the atom to the stream.
 * @param os the output stream.
 * @param atom the atom.
 * @return the used output stream.
 */
ostream& operator<< (ostream &os, const CAtom &atom);



/**
 * Inputs the atom from the binary stream.
 * @param ibs the input binary stream.
 * @param atom the atom to fill.
 * @return the input binary stream used.
 */
iBinstream& operator>> (iBinstream &ibs, CAtom &atom);



/**
 * Outputs the atom to the binary stream.
 * @param obs the output binary stream.
 * @param atom the atom.
 * @return the output binary stream used.
 */
oBinstream& operator<< (oBinstream &obs, const CAtom &atom);



/**
 * Reads an atom from a pdb file.
 * @param ips the input pdb stream.
 * @param atom the pointer to the new atom.
 * @return the used input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, CAtom &atom);



/**
 * Writes the atom to a pdb format file.
 * @param ops the output pdb stream.
 * @param atom the atom to write.
 * @return the used output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const CAtom &atom);



/**
 * @short Base unary function for the atomset.
 *
 * Abstract class for filtering atom sets.  These classes are used in the
 * residues iterators.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the objet.
   */
  AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  AtomSet (const AtomSet &right) { }

  /**
   * Destructs the object.
   */
  virtual ~AtomSet () { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  virtual AtomSet& operator= (const AtomSet &right) { return *this; }
  
  /**
   * Tests wheter the atom is within the set.
   * @param atom the atom.
   * @return wheter the atom is within the set.
   */
  virtual bool operator() (const CAtom &atom) const = 0;

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const = 0;

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const = 0;

  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const = 0;
};



/**
 * Inputs a function object from a binary stream.
 * @param ibs the input binary stream.
 * @param as the inputted function object.
 * @return the input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, AtomSet *&as);



/**
 * Outputs a function object through a binary stream.
 * @param obs the output binary stream.
 * @param as the function object to output.
 * @return the output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const AtomSet *as);



/**
 * @short And operator over atomset function objects.
 *
 * Function object that creates a and operation over two other functions.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class atomset_and : public AtomSet
{
  /**
   * The left atomset function object.
   */
  AtomSet *op1;

  /**
   * The right atomset function object.
   */
  AtomSet *op2;

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.  It must not be used.
   */
  atomset_and () : AtomSet () { }
  
  /**
   * A string used when using the const char* cast. 
   */
  mutable char *str;

public:

  /**
   * Initializes the object with two functions.
   * @param x the left function object.
   * @param y the right function object.
   */
  atomset_and (AtomSet *x, AtomSet *y) 
    : AtomSet (), op1(x), op2(y), str (0) { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  atomset_and (const atomset_and &right)
    : AtomSet (right), op1 (right.op1->clone ()), op2 (right.op2->clone ())
  { 
    if (str) delete[] str;
    str = 0;
  }

  /**
   * Destructs the operands.
   */
  virtual ~atomset_and () { 
    delete op1; delete op2; 
    if (str) delete[] str;
    str = 0;
  }

  // OPERATORS -----------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual atomset_and& operator= (const atomset_and &right);

  /**
   * Tests wheter the atom is within the set.
   * @param x the atom.
   * @return wheter the atom is within the set.
   */
  virtual bool operator() (const CAtom& x) const
  { return op1->operator() (x) && op2->operator() (x); }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const;

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const
  { return new atomset_and (op1->clone (), op2->clone ()); }

  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};



/**
 * @short All atom set unary function.
 *
 * No atoms are filtered.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class all_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  all_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  all_atom_set (const all_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests wheter the atom is within the set.
   * @param atom the atom.
   * @return true.
   */
  virtual bool operator() (const CAtom &atom) const { return true; }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "all"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new all_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};



/**
 * @short Base atom set unary function.
 *
 * Filters the atoms that are located on the side chain.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class base_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  base_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  base_atom_set (const base_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests wheter the atom is part of the base.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return atom.GetType ()->is_SideChain (); }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "base_only"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new base_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};



/**
 * @short Backbone atom set unary function.
 *
 * Filters the atoms that are located on the backbone.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class backbone_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  backbone_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  backbone_atom_set (const backbone_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests wheter the atom is part of the backbone.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return atom.GetType ()->is_Backbone (); }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "backbone_only"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new backbone_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};



/**
 * @short Pse atom set unary function.
 *
 * Filters the atoms that are pseudo atoms (pivots).
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class pse_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  pse_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  pse_atom_set (const pse_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests wheter the atom is C1p.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return (atom.GetType ()->is_C1p () || atom.GetType ()->is_PSY ()
	    || atom.GetType ()->is_PSZ ()); }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "pse_only"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new pse_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};



/**
 * @short No hydrogen option unary function.
 *
 * Filters out the hydrogen atoms.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class no_hydrogen_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  no_hydrogen_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  no_hydrogen_set (const no_hydrogen_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests wheter the atom is an hydrogen.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return ! atom.GetType ()->is_Hydrogen (); }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "no_hydrogen"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new no_hydrogen_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};




/**
 * @short All atoms exept psedo and lone pair unary function.
 *
 * Filters out pseudo or lone pair atoms.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class no_pse_lp_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  no_pse_lp_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  no_pse_lp_atom_set (const no_pse_lp_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests whether the atom is a pseudo or a lone pair atom.
   * @param atom the atom to test.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  {
    return ! (atom.GetType ()->is_Pseudo ()
	      || atom.GetType ()->is_LonePair ());
  }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "no_pse_lp"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new no_pse_lp_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};


/**
 * @short All atoms exept O2p unary function.
 *
 * Filters O2p atoms since this is the main difference between RNA and
 * DNA except for backbone hydrogens.
 *
 * @author Patrick Gendron <larosem@IRO.UMontreal.CA>
 */
class no_O2p_atom_set : public AtomSet
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the object.
   */
  no_O2p_atom_set () : AtomSet () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  no_O2p_atom_set (const no_O2p_atom_set& right) : AtomSet (right) { }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Tests whether the atom is a pseudo or a lone pair atom.
   * @param atom the atom to test.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  {
    return ! (atom.GetType ()->is_O2p ());
  }

  /**
   * Converts the function object to a character representation.
   * @return a constant char string.
   */
  virtual operator const char* () const { return "no_O2p"; }

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Copies the function object.
   * @return a copy of itself.
   */
  virtual AtomSet* clone () const { return new no_O2p_atom_set (); }
  
  // I/O -----------------------------------------------------------
  
  /**
   * Outputs the function object to a binary stream.
   * @param obs the output binary stream.
   */
  virtual void BinOutput (oBinstream& obs) const;
};

#endif
