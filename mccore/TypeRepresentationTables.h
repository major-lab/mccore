//                              -*- Mode: C++ -*- 
// TypeRepresentationTables.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct  1 13:34:36 2004
// $Revision: 1.4 $
// $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
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


#ifndef _mccore_TypeRepresentationTables_h_
#define _mccore_TypeRepresentationTables_h_

#include <map>
#include <string>
#include <utility>

using namespace std;



namespace mccore
{
  class AtomType;
  class ResidueType;
  
  /**
   * The AtomTypeParseTable maps a string representation and an AtomType.
   * It is used to get the correct AtomType depending of the reading
   * context.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
   */
  template < typename T >
  class TypeRepresentationTables
  {
  public:

    static const unsigned int PDB = 0;
    static const unsigned int AMBER = 1;

    /**
     * The parse table.
     */
    mutable map< string, const T* > typeTable;

    /**
     * The representation table.
     */
    mutable map< const T*, string > representationTable;
    
    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the objet.
     */
    TypeRepresentationTables () { }

  public:

    /**
     * Destroys the object.
     */
    virtual ~TypeRepresentationTables () { }

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    // METHODS -------------------------------------------------------------

    /**
     * Gets the type T from the string depending of the context.
     * @param str the string reprensentation of the type T.
     * @return the type T.
     */
    const T* parseType (const string &str) const
    {
      pair< typename map< string, const T* >::iterator, bool > inserted;

      inserted = typeTable.insert (std::pair< string, const T*> (str, 0));
      if (inserted.second)
	{
	  const T *type;
	  pair< const T*, string > p;

	  type = T::parseType (str);
	  inserted.first->second = type;
	  p = std::pair< const T*, string > (type, str);
	  representationTable.insert (p);
	}
      return inserted.first->second;
    }

    /**
     * Gets the context representation string from a type T.
     * @param t the type T.
     * @return the string representation.
     */
    const char* toString (const T *t) const
    {
      typename map< const T* , string >::const_iterator cit;
      
      cit = representationTable.find (t);
      if (representationTable.end () == cit)
	{
	  return (const char*) *t;
	}
      else
	{
	  return cit->second.c_str ();
	}
    }      

    // I/O -----------------------------------------------------------------
  };


  /**
   * The AmberAtomTypeRepresentationTable maps a string representation in Amber
   * context and an AtomType.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
   */
  class AmberAtomTypeRepresentationTable : public TypeRepresentationTables< AtomType >
  {
  public:

    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the table with the Amber atom type representation.
     */
    AmberAtomTypeRepresentationTable ();

    /**
     * Destroys the table.
     */
    virtual ~AmberAtomTypeRepresentationTable () { }

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    // METHODS -------------------------------------------------------------

    // I/O -----------------------------------------------------------------
  };

  
  /**
   * The PdbAtomTypeRepresentationTable maps a string representation in pdb
   * context and an AtomType.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
   */
  class PdbAtomTypeRepresentationTable : public TypeRepresentationTables< AtomType >
  {
  public:

    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the table with the Amber atom type representation.
     */
    PdbAtomTypeRepresentationTable ();

    /**
     * Destroys the table.
     */
    virtual ~PdbAtomTypeRepresentationTable () { }

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    // METHODS -------------------------------------------------------------

    // I/O -----------------------------------------------------------------
  };


  /**
   * The AmberResidueTypeRepresentationTable maps a string representation in Amber
   * context and an ResidueType.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
   */
  class AmberResidueTypeRepresentationTable : public TypeRepresentationTables< ResidueType >
  {
  public:

    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the table with the Amber atom type representation.
     */
    AmberResidueTypeRepresentationTable ();

    /**
     * Destroys the table.
     */
    virtual ~AmberResidueTypeRepresentationTable () { }

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    // METHODS -------------------------------------------------------------

    // I/O -----------------------------------------------------------------
  };

  
  /**
   * The PdbResidueTypeRepresentationTable maps a string representation in pdb
   * context and an ResidueType.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: TypeRepresentationTables.h,v 1.4 2005-08-05 16:01:19 larosem Exp $
   */
  class PdbResidueTypeRepresentationTable : public TypeRepresentationTables< ResidueType >
  {
  public:

    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the table with the Amber atom type representation.
     */
    PdbResidueTypeRepresentationTable ();

    /**
     * Destroys the table.
     */
    virtual ~PdbResidueTypeRepresentationTable () { }

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    // METHODS -------------------------------------------------------------

    // I/O -----------------------------------------------------------------
  };
}
    
#endif
