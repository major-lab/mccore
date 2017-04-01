//                              -*- Mode: C++ -*- 
// ResidueTopology.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Mar 21 15:30:27 2003
// $Revision: 1.4 $
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


#ifndef _mccore_ResidueTopology_h_
#define _mccore_ResidueTopology_h_

#include <iostream>
#include <set>

#include "AtomType.h"
#include "UndirectedGraph.h"



namespace mccore
{
  class ResidueType;


  
  /**
   * The topology of known residues including obligatory and optionnal atoms.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: ResidueTopology.h,v 1.4 2006-01-26 21:22:19 thibaup Exp $
   */
  class ResidueTopology
  {

    static map< const ResidueType*, UndirectedGraph< const AtomType*, pair< const AtomType*, const AtomType* > > > topologies;
    
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ResidueTopology ();

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    ResidueTopology (const ResidueTopology &other);

    /**
     * Destroys the object.
     */
    ~ResidueTopology () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the standard topology corresponding to the residue type.
     * @param type the ResidueType.
     * @return the topology or null if the type is non-standard.
     */
    static const UndirectedGraph< const AtomType*, pair< const AtomType*, const AtomType* > >* get (const ResidueType* type);

    /**
     * Returns obligatory atom sets for the given type. 
     */
    static set< const AtomType* > getOblSet (const ResidueType* type);
  
    // METHODS --------------------------------------------------------------

  private:

    static bool init (const ResidueType* type);

    // I/O  -----------------------------------------------------------------

  };

}

namespace std
{
  /**
   * Outputs a pair of atom types. It is necessary because of class Graph output,
   * but this ain't really nice ... 
   * @param os The ouput stream.
   * @param ap The pair of atom types.
   * @return The written stream.
   */
  ostream& operator<< (ostream& os, const pair< const mccore::AtomType*, const mccore::AtomType* >& ap);
}

#endif
