//                        -*- Mode: C++ -*-
// fBinstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:20:58 EDT
// $Revision
// $Id: fBinstream.h,v 1.5.4.1 2003-12-10 14:20:19 larosem Exp $
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


#ifndef _fBinstream_h_
#define _fBinstream_h_

#include <iostream>

#include "Binstream.h"
#include "fstreambase.h"

using namespace std;



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
class ifBinstream : public fstreambase, public iBinstream
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  ifBinstream ()
    : fstreambase (),
      iBinstream (fstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   */
  ifBinstream (const char *name, int mode=ios::in)
    : fstreambase (name, mode),
      iBinstream (fstreambase::rdbuf ())
  { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   */
  void open (const char *name, int mode=ios::in)
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
class ofBinstream : public fstreambase, public oBinstream
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  ofBinstream ()
    : fstreambase (),
      oBinstream (fstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::out).
   */
  ofBinstream (const char *name, int mode = ios::out)
    : fstreambase (name, mode),
      oBinstream (fstreambase::rdbuf ())
  { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and optional mode and protection.
   * @param name the path and file name to open.
   * @param mode the open mode (default = ios::out).
   */
  void open (const char *name, int mode = ios::out)
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
class fBinstream : public fstreambase, public Binstream
{
  
 public:
  
  // LIFECYCLE ------------------------------------------------------------
  
  /**
   * Initializes the stream.
   */
  fBinstream ()
    : fstreambase (),
      Binstream (fstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  fBinstream (const char *name, int mode = ios::in)
    : fstreambase (name, mode),
      Binstream (fstreambase::rdbuf ())
  { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int mode = ios::in)
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
