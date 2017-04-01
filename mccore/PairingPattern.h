//                              -*- Mode: C++ -*- 
// PairingPattern.h
// Copyright © 2001-06 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Thu May 31 08:17:56 2001
// $Revision: 1.10 $
// $Id: PairingPattern.h,v 1.10 2006-05-02 20:54:08 larosem Exp $
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


#ifndef _mccore_PairingPattern_h_
#define _mccore_PairingPattern_h_

#include <iostream>
#include <list>
#include <vector>

#include "HBond.h"
#include "Relation.h"

using namespace std;



namespace mccore
{
  class AtomType;
  class PropertyType;
  class Residue;
  class ResidueType;

  /**
   * @short Patterns for MC-Sym's ancient pairing system.
   *
   * This class implements the correspondence between a pattern of flow as 
   * described by a vector of HBondFlow* and the arabic/roman numeral used to
   * identify the pairing.
   *
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: PairingPattern.h,v 1.10 2006-05-02 20:54:08 larosem Exp $
   */
  class PairingPattern
    {
      /**
       * The Saenger/Gautheret pairing type.
       */
      const PropertyType *name;

      /**
       * The type of residues involved in the pattern description.
       */
      const ResidueType *typeA;
      const ResidueType *typeB;

      /**
       * The parallel/antiparallel base orientation.
       */
      const PropertyType *baseOrientation;

    public:
      
      class Description
      {
      public:

	/**
	 * Indicates if the bond should be ignored.
	 */
	bool ignored;
	
	HBond hbond;

	/**
	 * Initializes the description.
	 */
	Description (bool i, HBond &h) : ignored (i), hbond (h) { }

	Description (const Description &other)
	  : ignored (other.ignored), hbond (other.hbond) { }

	~Description () { }

	Description& operator= (const Description &other)
	{
	  if (this != &other)
	    {
	      ignored = other.ignored;
	      hbond = other.hbond;
	    }
	  return *this;
	}
      };

    private:

      /**
       * The descriptions from type A to type B.
       */
      vector< Description > AtoB;

      /**
       * The descriptions from type B to type A.
       */
      vector< Description > BtoA;
      

      /**
       * The number of non ignored descriptions.
       */
      unsigned int msize;
      
      /**
       * The patterns.
       */
      static list< PairingPattern > patterns;

      /**
       *
       */
      static bool isInit;

      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object.
       */
      PairingPattern () : name (0), typeA (0), typeB (0), baseOrientation (0), msize (0) { }

    public:

      /**
       * Initializes the object for a particular pattern.
       * @param id the MC-Sym pairing id.
       * @param type_a the type of one residue.
       * @param type_b the type of another residue.
       */
      PairingPattern (const PropertyType *id, const ResidueType *type_a, const ResidueType *type_b, const PropertyType *ori)
	: name (id), typeA (type_a), typeB (type_b), baseOrientation (ori), msize (0)
      { }

      /**
       * Initializes the object with the other's content.
       * @param other, the object to copy.
       */
      PairingPattern (const PairingPattern &other)
	: name (other.name),
	  typeA (other.typeA),
	  typeB (other.typeB),
	  baseOrientation (other.baseOrientation),
	  AtoB (other.AtoB),
	  BtoA (other.BtoA),
	  msize (other.msize)
      { }

      /**
       * Destroys the object.
       */
      ~PairingPattern () { }

      // OPERATORS ------------------------------------------------------------

    private:
      
      /**
       * Assigns the object with the other's content.
       * @param other, the object to copy.
       * @return itself.
       */
      const PairingPattern &operator= (const PairingPattern &other);

      // ACCESS ---------------------------------------------------------------

    public:

      /**
       * Gets the MC-Sym property type.
       * @return the type
       */
      const PropertyType* getName () const { return name; }

      /**
       * Gets the type of residue in start position.
       * @return the residue type.
       */
      const ResidueType* getTypeA () const { return typeA; }

      /**
       * Gets the type of residue in end position.
       * @return the residue type.
       */
      const ResidueType* getTypeB () const { return typeB; }

      /**
       * Gets the AtoB descriptions of a pattern.
       * @return the descriptions of the pattern.
       */
      vector< Description >& getAtoB () { return AtoB; }
      
      /**
       * Gets the BtoA descriptions of a pattern.
       * @return the descriptions of the pattern.
       */
      vector< Description >& getBtoA () { return BtoA; }
      
      /**
       * Gets all pairing patterns.
       * @return the list of the pairing patterns.
       */
      static const list< PairingPattern >& patternList ()
      {
	if (!isInit)
	  {
	    init ();
	    isInit = true;
	  }
	return patterns;
      }

      /**
       * Gets the size of the Pattern witch is the number of descriptions.
       * @return the size of the Description collection.
       */
      unsigned int size () const { return msize; }

      // METHODS --------------------------------------------------------------

      /**
       * Add an H-Bond to the Description desc.
       * @param desc the collection of Description.
       * @param donor the donor atom type.
       * @param hydro the hydrogen type.
       * @param acceptor the acceptor atom type.
       * @param loneair the lonepair implicated.
       * @param ignore wether this shouldn't be in the pairing.
       */
      void addBond (vector< Description > &desc, const AtomType *donor, const AtomType *hydro, const AtomType *acceptor, const AtomType *lonepair, bool ignore = false);

      /**
       * Tests if all Descriptions from desc are matched in the HBondFlow list.
       * @param hbf the HBondFlow list.
       * @param desc the Description collection.
       * @param rA the donor residue.
       * @param direction the desc direction (only for printing purpose).
       * @return if the hbf matches the desc collection.
       */
      bool match (list< HBondFlow > &hbf, const vector< Description > &desc, const Residue *rA, char direction) const;
      
      /**
       * Evaluates the possibility of the flow pattern to match the
       * current HBond pairing pattern.
       * @param bpori base pair orientation (para or anti).
       * @return the property type or 0 if there is no match.
       */
      const PropertyType* evaluate (const Residue *ra, const Residue *rb, const PropertyType *bpori, list< HBondFlow > &hbf) const;

      /**
       * Initializes the Global vector of pairing patterns
       */
      static void init ();
         
      /**
       * Ouputs the pairing pattern to the stream.
       * @param os the output stream.
       * @return the used output stream.
       */
      ostream& output (ostream &os) const;

    };

}



namespace std
{
  
  /**
   * Outputs the pairing pattern to an output stream.
   * @param obs the output stream.
   * @param obj the model to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const mccore::PairingPattern &pat);

}

#endif
