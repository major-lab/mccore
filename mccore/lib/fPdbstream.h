//                       -*- Mode: C++ -*-
// fPdbstream.h
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>.
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:35:06 2001
// Update Count     : 6
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

#include <fstream.h>

#include "Pdbstream.h"



/**
 * @short Input pdb file stream.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class ifPdbstream : public fstreambase, public iPdbstream
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  ifPdbstream () : fstreambase (), iPdbstream () { }

  /**
   * Initializes the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  ifPdbstream (int fd) : fstreambase (fd), iPdbstream () { }

  /**
   * Initializes the stream with a file name and optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   * @param prot the protection flag (default = 0664).
   */
  ifPdbstream (const char *name, int mode = ios::in, int prot = 0664)
    : fstreambase (name, mode, prot), iPdbstream () { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the file stream with a file name and optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   * @param prot the protection flag (default = 0664).
   */
  void open (const char *name, int mode=ios::in, int prot=0664)
    { fstreambase::open (name, mode, prot); iPdbstream::open (); }

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
class ofPdbstream : public fstreambase, public oPdbstream
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  ofPdbstream () : fstreambase (), oPdbstream () { }

  /**
   * Initializes the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  ofPdbstream(int fd)
    : fstreambase (fd), oPdbstream () { }

  /**
   * Initializes the stream with a file name and an optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param prot the protection flag (default = 0664).
   */
  ofPdbstream (const char *name, int mode = ios::out, int prot = 0664)
    : fstreambase (name, mode, prot), oPdbstream () { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the stream with a file name and an optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param prot the protection flag (default = 0664).
   */
  void open (const char *name, int mode = ios::out, int prot = 0664)
    { fstreambase::open (name, mode, prot); oPdbstream::open (); }

  /**
   * Closes the stream.
   */
  virtual void close () { oPdbstream::close (); fstreambase::close (); }

  // I/O -----------------------------------------------------------
};

#endif
