//                       -*- Mode: C++ -*-
// fPdbstream.h
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>.
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:15:32 2000
// Update Count     : 4
// Status           : Ok.
//


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
