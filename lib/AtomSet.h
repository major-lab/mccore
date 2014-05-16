// AtomSet.h
// Copyright © 2003-05, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal.
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


#ifndef _mccore_AtomSet_h_
#define _mccore_AtomSet_h_

#include <iostream>
#include <set>

#include "Atom.h"
#include "AtomType.h"

namespace mccore {

  class AtomType;
  class iBinstream;
  class oBinstream;

  /**
   * @short Base unary function for the atomset.
   *
   * Abstract class for filtering atom sets.  These classes are used in the
   * residues iterators.
   */
  class AtomSet
  {
  protected:

    static const int ATOMSET_ALL;
    static const int ATOMSET_NOT;
    static const int ATOMSET_AND;
    static const int ATOMSET_OR;
    static const int ATOMSET_SIDECHAIN;
    static const int ATOMSET_BACKBONE;
    static const int ATOMSET_PHOSPHATE;
    static const int ATOMSET_PSE;
    static const int ATOMSET_HYDROGEN;
    static const int ATOMSET_LP;
    static const int ATOMSET_ATOM;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSet (const AtomSet &other) {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const = 0;

    /**
     * Destroys the object.
     */
    virtual ~AtomSet () {}

    /**
     * Create a new AtomSet based on a string representation. Throws an exception if
     * representation is unknown.
     * @param str string representation.
     * @return a newly created AtomSet.
     * @exception IntLibException.
     */
    static AtomSet* create (const char* str);

    // OPERATORS ------------------------------------------------------------

  protected:

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSet& operator= (const AtomSet &other) { return *this; }

  public:

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const = 0;

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const = 0;

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const = 0;

    /**
     * Inputs the atom from the binary stream.
     * @param ibs the input binary stream.
     * @param atom the atom to fill.
     * @return the input binary stream used.
     */
    friend iBinstream& operator>> (iBinstream &ibs, AtomSet *&as);

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const = 0;
  };



  /**
   * @short All atom set unary function.
   *
   * No atoms are filtered.
   */
  class AtomSetAll : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetAll () : AtomSet () { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAll (const AtomSetAll &other) : AtomSet (other) { }

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const { return (AtomSet*) new AtomSetAll (*this); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetAll () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetAll& operator= (const AtomSetAll &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return true; }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_NOT; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };


  /**
   * @short Not operator over atomset function objects.
   */
  class AtomSetNot : public AtomSet
  {
    /**
     * The atomset function object.
     */
    AtomSet *op;

  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

  private:

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetNot () : AtomSet () { }

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetNot (AtomSet *x) : AtomSet (), op(x) { }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetNot (const AtomSetNot &other) 
      : AtomSet (other), op (other.op->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const { return (AtomSet*) new AtomSetNot (*this); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetNot () { delete op; }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetNot& operator= (const AtomSetNot &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return ! op->operator() (atom); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_NOT; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short And operator over atomset function objects.
   */
  class AtomSetAnd : public AtomSet
  {
    /**
     * The left atomset function object.
     */
    AtomSet *op1;

    /**
     * The right atomset function object.
     */
    AtomSet *op2;  

  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

  private:

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetAnd () : AtomSet () {}

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetAnd (AtomSet *x, AtomSet *y) 
      : AtomSet (), op1(x), op2(y) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAnd (const AtomSetAnd &other) 
    : AtomSet (other), op1 (other.op1->clone ()), op2 (other.op2->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const { return (AtomSet*) new AtomSetAnd (*this); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetAnd ()
    {
      delete op1;
      delete op2;
    }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetAnd& operator= (const AtomSetAnd &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return op1->operator() (atom) && op2->operator() (atom); }

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_AND; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };



  /**
   * @short Or operator over atomset function objects.
   */
  class AtomSetOr : public AtomSet
  {
    /**
     * The left atomset function object.
     */
    AtomSet *op1;

    /**
     * The right atomset function object.
     */
    AtomSet *op2;  

  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

  private:

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetOr () : AtomSet () { }

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetOr (AtomSet *x, AtomSet *y) 
    : AtomSet (), op1(x), op2(y) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetOr (const AtomSetOr &other) 
    : AtomSet (other), op1 (other.op1->clone ()), op2 (other.op2->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const { return (AtomSet*) new AtomSetOr (*this); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetOr ()
    {
      delete op1;
      delete op2;
    }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetOr& operator= (const AtomSetOr &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return op1->operator() (atom) || op2->operator() (atom); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_OR; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };


  /**
   * @short Base atom set unary function.
   *
   * Filters the atoms that are located on the side chain.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetSideChain : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetSideChain () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetSideChain (const AtomSetSideChain &other) 
    : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetSideChain (); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetSideChain () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetSideChain& operator= (const AtomSetSideChain &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isSideChain (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_SIDECHAIN; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };


  /**
   * @short Backbone atom set unary function.
   *
   * Filters the atoms that are located on the backbone.
   */
  class AtomSetBackbone : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetBackbone () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetBackbone (const AtomSetBackbone &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetBackbone (); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetBackbone () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetBackbone& operator= (const AtomSetBackbone &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isBackbone (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_BACKBONE; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };


  /**
   * @short Phosphate atom set unary function.
   *
   * Filters the atoms that are located on the phosphate.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class AtomSetPhosphate : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetPhosphate () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetPhosphate (const AtomSetPhosphate &other) 
    : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetPhosphate (); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetPhosphate () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetPhosphate& operator= (const AtomSetPhosphate &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isPhosphate (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_PHOSPHATE; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };


  /**
   * @short PSE operator over atomset function objects.
   *
   * Filters the atoms that are pseudo atoms (pivots).
   */
  class AtomSetPSE : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetPSE () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetPSE (const AtomSetPSE &other) 
    : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetPSE (); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetPSE () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetPSE& operator= (const AtomSetPSE &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isPseudo (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_PSE; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short LP operator over atomset function objects.
   *
   * Filters the atoms that are LonePairs.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetLP : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetLP () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetLP (const AtomSetLP &other) 
    : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetLP (); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetLP () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetLP& operator= (const AtomSetLP &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isLonePair (); }

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_LP; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short Hydrogen operator over atomset function objects.
   */
  class AtomSetHydrogen : public AtomSet
  {
  public:

    static const char* representation;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetHydrogen () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetHydrogen (const AtomSetHydrogen &other) 
    : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetHydrogen (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetHydrogen () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetHydrogen& operator= (const AtomSetHydrogen &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isHydrogen (); }

    // METHODS --------------------------------------------------------------

  protected:

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_HYDROGEN; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short Atom operator over atomset function objects.
   */
  class AtomSetAtom : public AtomSet
  {
    /**
     * The AtomType.
     */
    const AtomType *type;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetAtom () : AtomSet () {}

  public:

    /**
     * Initializes the object.
     * @param anAtomType the AtomType.
     */
    AtomSetAtom(const AtomType *anAtomType)
    {
      type = anAtomType;
    }

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAtom (const AtomSetAtom &other) 
    : AtomSet (other),
    type (other.type)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const { return (AtomSet*) new AtomSetAtom (*this); }

    /**
     * Destroys the object.
     */
    virtual ~AtomSetAtom () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    AtomSetAtom& operator= (const AtomSetAtom &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType () == type; }


    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual int getSetNumber() const { return AtomSet::ATOMSET_ATOM; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };

}



namespace std
{

  /**
   * Ouputs the set to the stream.
   * @param os the output stream.
   * @param as the atomset.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::AtomSet &as);

}

#endif
