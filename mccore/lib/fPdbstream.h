//                       -*- Mode: C++ -*-
// fPdbstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>.
// Created On       : 
// $Revision: 1.4.4.1 $
// $Id: fPdbstream.h,v 1.4.4.1 2003-12-10 14:20:21 larosem Exp $
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


#ifndef _fPdbstream_h_
#define _fPdbstream_h_

#include <iostream>

#include "fstreambase.h"
#include "Pdbstream.h"

using namespace std;



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
  ifPdbstream ()
    : fstreambase (),
      iPdbstream (fstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with a file name and optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   */
  ifPdbstream (const char *name, int mode = ios::in)
    : fstreambase (name, mode),
      iPdbstream (fstreambase::rdbuf ())
  { }

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
  {
    fstreambase::open (name, mode);
    iPdbstream::open ();
  }

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
  ofPdbstream ()
    : fstreambase (),
      oPdbstream (fstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with a file name and an optional mode and
   * protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   */
  ofPdbstream (const char *name, int mode = ios::out)
    : fstreambase (name, mode),
      oPdbstream (fstreambase::rdbuf ())
  { }

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
  {
    fstreambase::open (name, mode);
    oPdbstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { oPdbstream::close (); fstreambase::close (); }

  // I/O -----------------------------------------------------------
};

#endif
