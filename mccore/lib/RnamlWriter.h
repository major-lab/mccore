//                              -*- Mode: C++ -*- 
// RnamlWriter.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.1.2.2 $
// $Id: RnamlWriter.h,v 1.1.2.2 2003-07-15 17:08:31 larosem Exp $
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


#ifndef _mccore_RnamlWriter_h_
#define _mccore_RnamlWriter_h_

#include <cstdio>

namespace rnaml
{
  class Atom;
  class Base;
  class Model;
  class Molecule;
  class Rnaml;
}



namespace mccore
{
  class Atom;
  class Residue;
  class Model;
  class Molecule;
  

  
  /**
   * @short Writer for mccore objects to rnaml.
   *
   * This class writes the mccore objects into a stream.  The objects are
   * transformed into rnamlObjects, then outputted to the stream.
   *
   * @author Martin Larose (<larosem@iro.umontreal.ca>).
   */
  class RnamlWriter
  {
    /**
     * The output stream.
     */
    FILE *of;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the object.
     * @param f the output stream.
     */
    RnamlWriter (FILE *f) : of (f) { }
    
    /**
     * Destroys the object.
     */
    virtual ~RnamlWriter () { }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------

    /**
     * Transforms a mccore Atom to a rnaml Atom.
     * @param atom the mccore Atom.
     * @return the rnaml Atom.
     */
    static rnaml::Atom* toRnaml (const mccore::Atom &atom);

    /**
     * Transforms a mccore Residue to a rnaml Base.
     * @param residue the mccore Residue.
     * @return the rnaml Base.
     */
    static rnaml::Base* toRnaml (const Residue &residue);

    /**
     * Transforms a mccore Model to a rnaml Model.
     * @param model the mccore Model.
     * @return the rnaml Model.
     */
    static rnaml::Model* toRnaml (const mccore::Model &model);

    /**
     * Transforms a mccore Molecule to a rnaml Molecule.
     * @param molecule the mccore Molecule.
     * @return the rnaml Molecule.
     */
    static rnaml::Molecule* toRnaml (const mccore::Molecule &molecule);
    
    // I/O  -----------------------------------------------------------------

    /**
     * Writes the atom in rnaml.
     * @param atom the Atom to write.
     */
    void write (const Atom &atom);

    /**
     * Writes the residue in rnaml.
     * @param residue the Residue to write.
     */
    void write (const Residue &residue);
    
    /**
     * Writes the model in rnaml.
     * @param model the Model to write.
     */
    void write (const Model &model);
    
    /**
     * Writes the molecule in rnaml.
     * @param molecule the Molecule to write.
     */
    void write (const Molecule &molecule);

    /**
     * Writes the molecule wrapped in a rnaml document.
     * @param molecule the Molecule to write.
     */
    void writeDocument (const mccore::Molecule &molecule);

    /**
     * Writes a rnaml object to the stream.
     * @param rnaml the Rnaml object to write.
     */
    void write (const rnaml::Rnaml &rnaml);

  };
}

#endif
