//                              -*- Mode: C++ -*- 
// RnamlWriter.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Thu Jul 10 14:43:57 2003
// $Revision: 1.2.2.1 $
// $Id: RnamlWriter.h,v 1.2.2.1 2004-12-10 03:45:38 larosem Exp $
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

namespace rnaml
{
  class Atom;
  class Base;
  class Model;
  class Molecule;
  class PrintStream;
  class Rnaml;
}



namespace mccore {
  
  class Atom;
  class AbstractModel;
  class Molecule;
  class Residue;
  
  
  
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
     * The print stream.
     */
    rnaml::PrintStream *ps;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the writer with a file name.
     * @param name the file name.
     * @param zipped whether the ouput file must be zipped; default false.
     */
    RnamlWriter (const char *name, bool zipped = false);
    
    /**
     * Initializes the object.
     * @param ps the print stream.
     */
    RnamlWriter (rnaml::PrintStream *ps) : ps (ps) { }
    
    /**
     * Destroys the object.
     */
    virtual ~RnamlWriter ();
    
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
     * Transforms a mccore AbstractModel to a rnaml Model.
     * @param model the mccore AbstractModel.
     * @return the rnaml Model.
     */
    static rnaml::Model* toRnaml (const AbstractModel &model);
    
    /**
     * Transforms a mccore Molecule to a rnaml Molecule.
     * @param molecule the mccore Molecule.
     * @return the rnaml Molecule.
     */
    static rnaml::Molecule* toRnaml (const Molecule &molecule);
    
    /**
     * Close the stream. Once a stream has been closed, further write ()
     * invocations will do nothing. Closing a previously-closed stream,
     * however, has no effect.
     */
    void close ();
    
    // I/O  -----------------------------------------------------------------
    
    /**
     * Writes the molecule wrapped in a rnaml document.
     * @param molecule the Molecule to write.
     */
    void write (const Molecule &molecule);
    
  };
}

#endif
