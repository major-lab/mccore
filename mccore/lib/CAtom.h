//                              -*- Mode: C++ -*- 
// CAtom.h
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Nov  9 10:44:49 2000
// Update Count     : 2
// Status           : Ok.
// 


#ifndef _CAtom_h_
#define _CAtom_h_


#include <function.h>

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
 * Derived from CPoint3D, this class adds the type and a serial number to
 * the point.
 *
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
   * Destructs the object.  The atom count is decreased.
   */
  virtual ~CAtom () { count--; }
  
  // OPERATORS -----------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const CAtom& operator= (const CAtom &right);

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
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct AtomSet : public unary_function< const CAtom&, bool >
{
  /**
   * Tests wheter the atom is within the set.
   * @param atom the atom.
   * @return false.
   */
  typedef CAtom argument_type;
  virtual bool operator() (const CAtom &atom) const { return false; }
  virtual AtomSet* clone () const { return new AtomSet (); }
};



class atomset_and : public AtomSet
{
protected:
  AtomSet *op1;
  AtomSet *op2;
public:
  atomset_and (AtomSet *x, AtomSet *y) : op1(x), op2(y) {}
  virtual ~atomset_and () { delete op1; delete op2; }
  virtual atomset_and& operator= (const atomset_and &right)
  {
    if (this != &right)
      {
	AtomSet::operator= (right);
	delete op1;
	delete op2;
	op1 = right.op1->clone ();
	op2 = right.op2->clone ();
      }
    return *this;
  }
  virtual bool operator() (const CAtom& x) const
  { return (*op1) (x) && (*op2) (x); }
  virtual atomset_and* clone () const
  { return new atomset_and (op1->clone (), op2->clone ()); }
};



/**
 * @short All atom set unary function.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct all_atom_set : public AtomSet
{
  /**
   * Tests wheter the atom is within the set.
   * @param atom the atom.
   * @return true.
   */
  virtual bool operator() (const CAtom &atom) const { return true; }
  virtual all_atom_set* clone () const { return new all_atom_set (); }
};



/**
 * @short Base atom set unary function.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct base_atom_set : public AtomSet
{
  /**
   * Tests wheter the atom is part of the base.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return atom.GetType ()->is_SideChain (); }
  virtual base_atom_set* clone () const { return new base_atom_set (); }
};



/**
 * @short Backbone atom set unary function.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct backbone_atom_set : public AtomSet
{
  /**
   * Tests wheter the atom is part of the backbone.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return atom.GetType ()->is_Backbone (); }
  virtual backbone_atom_set* clone () const { return new backbone_atom_set (); }
};



/**
 * @short Pse atom set unary function.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct pse_atom_set : public AtomSet
{
  /**
   * Tests wheter the atom is C1p.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return (atom.GetType ()->is_C1p () || atom.GetType ()->is_PSY ()
	    || atom.GetType ()->is_PSZ ()); }
  virtual pse_atom_set* clone () const { return new pse_atom_set (); }
};



/**
 * @short No hydrogen option unary function.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct no_hydrogen_opt : public AtomSet
{
  /**
   * Tests wheter the atom is an hydrogen.
   * @param atom the atom.
   * @return the truth value.
   */
  virtual bool operator() (const CAtom &atom) const
  { return ! atom.GetType ()->is_Hydrogen (); }
  virtual no_hydrogen_opt* clone () const { return new no_hydrogen_opt (); }
};




/**
 * @short All atoms exept psedo and lone pair unary function.
 *
 * Tells whether the atom is part of the set.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
struct no_pse_lp_atom_set : public AtomSet
{
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
  virtual no_pse_lp_atom_set* clone () const
  { return new no_pse_lp_atom_set (); }
};

#endif
