//                              -*- Mode: C++ -*- 
// ResidueTopology.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Mar 21 15:30:27 2003
// $Revision: 1.1 $
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



#ifndef _ResidueTopology_h_
#define _ResidueTopology_h_

#include <iostream>
#include <set>

#include "AtomType.h"

namespace mccore {

  class ResidueType;

  /**
   * The topology of known residues including obligatory and optionnal atoms.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: ResidueTopology.h,v 1.1 2003-04-03 21:55:55 gendrop Exp $
   */
  class ResidueTopology
  {

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
    ~ResidueTopology ();

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    ResidueTopology& operator= (const ResidueTopology &other);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Returns obligatory atom sets for the given type. 
     */
    static set< const AtomType* > getOblSet (const ResidueType* type);
  

    // I/O  -----------------------------------------------------------------

  };

}

#endif
