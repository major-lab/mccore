//                        -*- Mode: C++ -*-
// fBinstream.h
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:20:58 EDT
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:15:30 2000
// Update count     : 0
// Status           : Ok.
//


#ifndef _fBinstream_h_
#define _fBinstream_h_

#include <fstream.h>

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
class ifBinstream : public fstreambase, public iBinstream
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  ifBinstream () : fstreambase (), iBinstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  ifBinstream (int fd) : fstreambase (fd), iBinstream () { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  ifBinstream (const char *name, int mode=ios::in, int prot=0644)
    : fstreambase (name, mode, prot), iBinstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int mode=ios::in, int prot=0644)
    {
      fstreambase::open (name, mode, prot);
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
  ofBinstream () : fstreambase (), oBinstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  ofBinstream (int fd) : fstreambase (fd), oBinstream () { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::out).
   * @param prot the protection (default 0644).
   */
  ofBinstream (const char *name, int mode = ios::out, int prot = 0644)
    : fstreambase (name, mode, prot), oBinstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and optional mode and protection.
   * @param name the path and file name to open.
   * @param mode the open mode (default = ios::out).
   * @param prot the protection (default = 0644).
   */
  void open (const char *name, int mode = ios::out, int prot = 0644)
  {
    fstreambase::open (name, mode, prot);
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
  fBinstream () : fstreambase (), Binstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  fBinstream (int fd) : fstreambase (fd), Binstream () { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  fBinstream (const char *name, int mode = ios::in, int prot = 0664)
    : fstreambase(name, mode, prot), Binstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int mode = ios::in, int prot = 0664)
  {
    fstreambase::open (name, mode, prot);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  void close () { Binstream::close (); fstreambase::close (); }

  // I/O ------------------------------------------------------------------
};

#endif
