//                              -*- Mode: C++ -*-
// zfPdbstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : ven 23 jui 1999 13:54:45 EDT
// Last Modified By : Patrick Gendron
// Last Modified On : Mon Mar 24 17:20:12 2003
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


#ifndef _zfPdbstream_h_
#define _zfPdbstream_h_


#include "fstreambase.h"
#include "zfstream.h"
#include "Pdbstream.h"


namespace mccore {

/**
 * @short Compressed input pdb file stream.
 *
 * This stream can be used the same way as the ifPdbstream except that it
 * can read compressed files.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class izfPdbstream : public iPdbstream, public zfstreambase
{

public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the objet.
   */
  izfPdbstream () : iPdbstream (zfstreambase::rdbuf ()) { }

  /**
   * Initializes the objet with a file name and optional mode and
   * protection.  The zfstreambase is open with Z_BEST_SPEED compression
   * flag.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   */
  izfPdbstream (const char *name, int mode = ios::in)
    : iPdbstream (zfstreambase::rdbuf ()), 
      zfstreambase (name, mode) { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the file stream with a file name and optional mode and
   * protection.  The zfstreambase is open with Z_BEST_SPEED compression
   * flag.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   */
  void open (const char *name, int mode = ios::in)
  {
    zfstreambase::open (name, mode);
    iPdbstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { iPdbstream::close (); zfstreambase::close (); }

  // I/O -----------------------------------------------------------
};



/**
 * @short Output compressed pdb file stream.
 *
 * This stream can be used the same way as the ofPdbstream except that it
 * produces compressed pdb files.  The compression level is defaulted to
 * Z_BEST_SPEED but it can be modified on constructor and open operations.
 * Please do not use Z_NO_COMPRESSION (level 0): it produces a gzip header
 * and footer to the file (witch is often not desired).
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class ozfPdbstream : public oPdbstream, public zfstreambase
{

public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the pdb file stream.
   */
  ozfPdbstream () : oPdbstream (zfstreambase::rdbuf()) { }

  /**
   * Initializes the pdb file stream with a file name and optional mode,
   * compression level and protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param level the compression level (default = Z_BEST_SPEED).
   */
  ozfPdbstream (const char *name, int mode = ios::out,
		int level = Z_BEST_SPEED)
    : oPdbstream (zfstreambase::rdbuf()),
      zfstreambase (name, mode, level) { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the pdb file stream with a file name and optional mode,
   * compression level and protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param level the compression level (default = Z_BEST_SPEED).
   */
  void open (const char *name, int mode = ios::out,
	     int level = Z_BEST_SPEED)
  {
    zfstreambase::open (name, mode, level);
    oPdbstream::open ();
  }

  /**
   * Closes the compressed pdb file stream.
   */
  virtual void close () { oPdbstream::close (); zfstreambase::close (); }

  // I/O -----------------------------------------------------------
};

}

#endif
