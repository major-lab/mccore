//                              -*- Mode: C++ -*- 
// zfBinstream.h
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created on       : jeu 22 jui 1999 18:24:14 EDT
// Last Modified By : Martin Larose
// Last Modified On : Mon Jan 22 15:20:19 2001
// Update Count     : 2
// Status           : Ok.
// 


#ifndef _zfBinstream_h_
#define _zfBinstream_h_


#include <zlib.h>

#include "Binstream.h"
#include "zfstreambase.h"



/**
 * @short Compressed input binary stream.
 *
 * I/O general classes using the GNU zip compression system.  These streams
 * adds the compression on the normal binary streams.  The input stream can
 * read an uncompressed file.  When creating a output stream the programmer
 * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
 * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
 * of compression level 0 is not recommended: the data is not compressed but
 * a gzip dependent header an footer is added to the file.  It is preferable
 * to use the fBinstream classes for uncompressed output binary streams.
 * For further details see @ref iBinstream and @ref zfstreambase.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class izfBinstream : public zfstreambase, public iBinstream
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  izfBinstream () : zfstreambase (), iBinstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  izfBinstream (int fd) : zfstreambase (fd), iBinstream () { }
  
  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  izfBinstream(const char *name, int mode = ios::in, int prot = 0664)
    : zfstreambase(name, mode, Z_BEST_SPEED, prot), iBinstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int mode=ios::in, int prot = 0664)
  {
    zfstreambase::open (name, mode, Z_BEST_SPEED, prot);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void close () { iBinstream::close (); zfstreambase::close (); }
  
  // I/O ------------------------------------------------------------------
};



/**
 * @short Compressed output binary stream.
 *
 * I/O general classes using the GNU zip compression system.  These streams
 * adds the compression on the normal binary streams.  The input stream can
 * read an uncompressed file.  When creating a output stream the programmer
 * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
 * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
 * of compression level 0 is not recommended: the data is not compressed but
 * a gzip dependent header an footer is added to the file.  It is preferable
 * to use the fBinstream classes for uncompressed output binary streams.
 * For further details see @ref oBinstream and @ref zfstreambase.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class ozfBinstream : public zfstreambase, public oBinstream
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  ozfBinstream () : zfstreambase (), oBinstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  ozfBinstream (int fd) : zfstreambase (fd), oBinstream () { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::out).
   * @param prot the protection (default 0644).
   */
  ozfBinstream (const char *name, int level = Z_BEST_SPEED,
		int mode = ios::out, int prot = 0664)
    : zfstreambase (name, mode, level, prot), oBinstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::out).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int level = Z_BEST_SPEED,
	     int mode = ios::out, int prot = 0664)
  {
    zfstreambase::open (name, mode, level, prot);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { oBinstream::close (); zfstreambase::close (); }

  // I/O ------------------------------------------------------------------
};



/**
 * @short General compressed binary stream.
 *
 * I/O general classes using the GNU zip compression system.  These streams
 * adds the compression on the normal binary streams.  The input stream can
 * read an uncompressed file.  When creating a output stream the programmer
 * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
 * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
 * of compression level 0 is not recommended: the data is not compressed but
 * a gzip dependent header an footer is added to the file.  It is preferable
 * to use the fBinstream classes for uncompressed output binary streams.
 * For further details see @ref Binstream and @ref zfstreambase.
 *
 * @author Martin Larose <larosem@IRO.UMontreal.CA>
 */
class zfBinstream : public zfstreambase, public Binstream
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  zfBinstream () : zfstreambase (), Binstream () { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  zfBinstream (int fd) : zfstreambase (fd), Binstream () { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  zfBinstream (const char *name, int level = Z_BEST_SPEED,
	       int mode = ios::in, int prot = 0664)
    : zfstreambase (name, mode, level, prot), Binstream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  void open (const char *name, int level = Z_BEST_SPEED,
	     int mode = ios::in, int prot = 0664)
  {
    zfstreambase::open (name, mode, level, prot);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  void close () { Binstream::close (); zfstreambase::close (); }

  // I/O ------------------------------------------------------------------
};

#endif
