//                        -*- Mode: C++ -*-
// fBinstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:20:58 EDT
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 23 15:10:29 2001
// Update count     : 0
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


#ifndef _fBinstream_h_
#define _fBinstream_h_

#include <iostream>
#include <fstream>

#include "fstreambase.h"
#include "Binstream.h"


/**
 * @short Input binary file streams.
 *
 * Implementation of binary file streams, based on fstreambase and
 * Binstream.  These streams are used for binary dumps in files.  The
 * general layout is based on fstream while I/O operators comes from
 * Binstream.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class ifBinstream : public iBinstream, public fstreambase
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  ifBinstream () : iBinstream (fstreambase::rdbuf ()) { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   */
  ifBinstream (const char *name, int mode=std::ios::in)
    : iBinstream (fstreambase::rdbuf ()), fstreambase (name, mode) { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   */
  void open (const char *name, int mode=std::ios::in)
    {
      fstreambase::open (name, mode);
      iBinstream::open ();
    }

  /**
   * Closes the stream.
   */
  virtual void close () { iBinstream::close (); fstreambase::close (); }

  // I/O ------------------------------------------------------------------
};



/**
 * @short Output binary file stream.
 *
 * Implementation of binary file streams, based on fstreambase and
 * Binstream.  These streams are used for binary dumps in files.  The
 * general layout is based on fstream while I/O operators comes from
 * Binstream.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class ofBinstream : public oBinstream, public fstreambase
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  ofBinstream () : oBinstream (fstreambase::rdbuf ()) { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::out).
   */
  ofBinstream (const char *name, int mode = std::ios::out)
    : oBinstream (fstreambase::rdbuf ()), fstreambase (name, mode) { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and optional mode and protection.
   * @param name the path and file name to open.
   * @param mode the open mode (default = ios::out).
   */
  void open (const char *name, int mode = std::ios::out)
  {
    fstreambase::open (name, mode);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { oBinstream::close (); fstreambase::close (); }

  // I/O ------------------------------------------------------------------
};



/**
 * @short General binary file stream.
 *
 * Implementation of binary file streams, based on fstreambase and
 * Binstream.  These streams are used for binary dumps in files.  The
 * general layout is based on fstream while I/O operators comes from
 * Binstream.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class fBinstream : public Binstream, public fstreambase
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  fBinstream () : Binstream (fstreambase::rdbuf ()) { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  fBinstream (const char *name, int mode = std::ios::in)
    : Binstream (fstreambase::rdbuf ()), fstreambase(name, mode)  { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int mode = std::ios::in)
  {
    fstreambase::open (name, mode);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { Binstream::close (); fstreambase::close (); }

  // I/O ------------------------------------------------------------------
};

#endif
