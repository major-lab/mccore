//                              -*- Mode: C++ -*- 
// PairingPattern.h
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Thu May 31 08:17:56 2001
// $Revision: 1.6 $
// $Id: PairingPattern.h,v 1.6 2004-09-19 03:37:26 larosem Exp $
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


#ifndef _PairingPattern_h_
#define _PairingPattern_h_

#include <iostream>
#include <list>
#include <vector>

#include "AtomType.h"
#include "ResidueType.h"
#include "PropertyType.h"
#include "HBond.h"
#include "Relation.h"
#include "Residue.h"

using namespace std;



namespace mccore {

  /**
   * @short Patterns for MC-Sym's ancient pairing system.
   *
   * This class implements the correspondence between a pattern of flow as 
   * described by a vector of HBondFlow* and the arabic/roman numeral used to
   * identify the pairing.
   *
   * @author Patrick Gendron
   */
  class PairingPattern
    {
      /**
       * The MC-Sym Id.
       */
      const PropertyType* name;

      /**
       * The type of residues involved in the pattern description.
       */
      const ResidueType* typeA;
      const ResidueType* typeB;

    public:
      
      class Description
      {
      public:

	/**
	 * Indicates if the bond should be ignored.
	 */
	bool ignored;
	
	/**
	 * The description. '>' indicates a bond from A to B, '<' indicates a
	 * bond from B to A.
	 */
	char direction;
	
	HBond hbond;

	/**
	 * Initializes the description.
	 */
	Description (bool i, char d, HBond &h)
	  : ignored (i), direction (d), hbond (h) { }

	Description (const Description &other)
	  : ignored (other.ignored), direction (other.direction), hbond (other.hbond)
	{ }

	~Description () { }

	Description& operator= (const Description &other)
	{
	  if (this != &other)
	    {
	      ignored = other.ignored;
	      direction = other.direction;
	      hbond = other.hbond;
	    }
	  return *this;
	}
      };

    private:

      vector< Description > descriptions;

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
      PairingPattern ();

    public:

      /**
       * Initializes the object for a particular pattern.
       * @param id the MC-Sym pairing id.
       * @param type_a the type of one residue.
       * @param type_b the type of another residue.
       */
      PairingPattern (const PropertyType* id, const ResidueType* type_a, const ResidueType* type_b);

      /**
       * Initializes the object with the other's content.
       * @param other, the object to copy.
       */
      PairingPattern (const PairingPattern &other);

      /**
       * Destructs the object.

      */
      ~PairingPattern (void);

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
       * Gets the descriptions of a pattern.
       * @return the descriptions of the pattern.
       */
      const vector< Description >& getDescriptions () const { return descriptions; }

      /**
       * Gets all pairing patterns.
       * @return the list of the pairing patterns.
       */
      static list< PairingPattern >& patternList ()
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
       * Add an H-Bond to the pattern.
       * @param dir the direction (based on the ordering given in the constructor).
       * @param donor the donor atom type.
       * @param hydro the hydrogen type.
       * @param acceptor the acceptor atom type.
       * @param loneair the lonepair implicated.
       * @param ignore wether this shouldn't be in the pairing.
       */
      void addBond (char dir, const AtomType *donor, const AtomType *hydro, 
		    const AtomType *acceptor, const AtomType *lonepair, bool ignore=false);
  
     
      /**
       * Evaluates the possibility of the flow pattern to match the
       * current HBond pairing pattern.  
       * @param pattern the description of the flow pattern in a BasePair.
       * @return the property type or 0 if there is no match.
       */
      const PropertyType* 
      evaluate (const Residue* ra, const Residue *rb, list< HBondFlow > &hbf) const;

      /**
       * Write Amber description.
       * @param the output stream.
       */
//       void amberOutput (ostream& out, CResId &id_a, CResId &id_b,
// 			t_Residue *ta, t_Residue *tb);

      
      // STATIC FUNCTIONS -----------------------------------------------------
      
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

  // NON-MEMBER FUNCTION -------------------------------------------------------


  /**
   * Outputs the pairing pattern to an output stream.
   * @param obs the output stream.
   * @param obj the model to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const PairingPattern &pat);


  /**
   * Outputs the pairing pattern to an output stream.
   * @param obs the output stream.
   * @param obj the Description to output.
   * @return the output stream.
   */
  ostream& operator<< (ostream &obs, const PairingPattern::Description &desc);

}

#endif
