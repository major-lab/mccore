//                       -*- Mode: C++ -*-
// fPdbstream.h
// Copyright � 1999, 2000-03 Laboratoire de Biologie Informatique et Th�orique.
//                           Universit� de Montr�al.
// Author           : Martin Larose <larosem@iro.umontreal.ca>.
// Created On       : 
// Last Modified By : Patrick Gendron
// Last Modified On : Tue Mar 18 19:34:01 2003
// Update Count     : 9
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


#ifndef _fPdbstream_h_
#define _fPdbstream_h_

#include <iostream>
#include <fstream>

#include "fstreambase.h"
#include "Pdbstream.h"


namespace mccore {

/**
 * @short Input pdb file stream.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class ifPdbstream : public iPdbstream, public fstreambase
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  ifPdbstream () : iPdbstream (fstreambase::rdbuf ()) { }

  /**
   * Initializes the stream with a file name and optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   */
  ifPdbstream (const char *name, int mode = ios::in)
    : iPdbstream (fstreambase::rdbuf ()), fstreambase (name, mode) { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the file stream with a file name and optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   */
  void open (const char *name, int mode=ios::in)
    { fstreambase::open (name, mode); iPdbstream::open (); }

  /**
   * Closes the stream.
   */
  virtual void close () { iPdbstream::close (); fstreambase::close (); }

  // I/O -----------------------------------------------------------
};



/**
 * @short Output pdb file stream.
 *
 * This stream can be used as a regular file stream (ofstream).  The output
 * is formatted for pdb files.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class ofPdbstream : public oPdbstream, public fstreambase
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  ofPdbstream () : oPdbstream (fstreambase::rdbuf ()) { }

  /**
   * Initializes the stream with a file name and an optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   */
  ofPdbstream (const char *name, int mode = ios::out)
    : oPdbstream (fstreambase::rdbuf ()), fstreambase (name, mode) { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the stream with a file name and an optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   */
  void open (const char *name, int mode = ios::out)
    { fstreambase::open (name, mode); oPdbstream::open (); }

  /**
   * Closes the stream.
   */
  virtual void close () { oPdbstream::close (); fstreambase::close (); }

  // I/O -----------------------------------------------------------
};

}

#endif
