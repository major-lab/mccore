//                              -*- Mode: C++ -*-
// zfPdbstream.h
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : ven 23 jui 1999 13:54:45 EDT
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:15:38 2000
// Update Count     : 3
// Status           : Ok.
//


#ifndef _zfPdbstream_h_
#define _zfPdbstream_h_


#include "zfstreambase.h"
#include "Pdbstream.h"



/**
 * @short Compressed input pdb file stream.
 *
 * This stream can be used the same way as the ifPdbstream except that it
 * can read compressed files.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>.
 */
class izfPdbstream : public zfstreambase, public iPdbstream
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the objet.
   */
  izfPdbstream () : zfstreambase (), iPdbstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the file descriptor.
   */
  izfPdbstream (int fd) : zfstreambase (fd), iPdbstream () { }

  /**
   * Initializes the objet with a file name and optional mode and
   * protection.  The zfstreambase is open with Z_BEST_SPEED compression
   * flag.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   * @param prot the protection flag (default = 0664).
   */
  izfPdbstream (const char *name, int mode = ios::in, int prot = 0664)
    : zfstreambase (name, mode, Z_BEST_SPEED, prot), iPdbstream () { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the file stream with a file name and optional mode and
   * protection.  The zfstreambase is open with Z_BEST_SPEED compression
   * flag.
   * @param name the file name.
   * @param mode the ios mode (default = ios::in).
   * @param prot the protection flag (default = 0664).
   */
  void open (const char *name, int mode = ios::in, int prot = 0664)
  {
    zfstreambase::open (name, mode, Z_BEST_SPEED, prot);
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
class ozfPdbstream : public zfstreambase, public oPdbstream
{
public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the pdb file stream.
   */
  ozfPdbstream () : zfstreambase (), oPdbstream () { }

  /**
   * Initializes the pdb file stream with a file descriptor.
   * @param fd the file descriptor.
   */
  ozfPdbstream (int fd) : zfstreambase (fd), oPdbstream () { }

  /**
   * Initializes the pdb file stream with a file name and optional mode,
   * compression level and protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param level the compression level (default = Z_BEST_SPEED).
   * @param prot the protection flag (default = 0664).
   */
  ozfPdbstream (const char *name, int mode = ios::out,
		int level = Z_BEST_SPEED, int prot = 0664)
    : zfstreambase (name, mode, level, prot), oPdbstream () { }

  // OPERATORS -----------------------------------------------------

  // ACCESS --------------------------------------------------------

  // METHODS -------------------------------------------------------

  /**
   * Opens the pdb file stream with a file name and optional mode,
   * compression level and protection.
   * @param name the file name.
   * @param mode the ios mode (default = ios::out).
   * @param level the compression level (default = Z_BEST_SPEED).
   * @param prot the protection flag (default = 0664).
   */
  void open (const char *name, int mode = ios::out,
	     int level = Z_BEST_SPEED, int prot = 0664)
  {
    zfstreambase::open (name, mode, level, prot);
    oPdbstream::open ();
  }

  /**
   * Closes the compressed pdb file stream.
   */
  virtual void close () { oPdbstream::close (); zfstreambase::close (); }

  // I/O -----------------------------------------------------------
};

#endif
