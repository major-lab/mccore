//                              -*- Mode: C++ -*- 
// zfBinstream.h
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created on       : jeu 22 jui 1999 18:24:14 EDT
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:04:46 2001
// Update Count     : 3
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


#ifndef _zfBinstream_h_
#define _zfBinstream_h_


#include <zlib.h>

#include "Binstream.h"
#include "zfilebuf.h"



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
class izfBinstream : public iBinstream
{
  /**
   * The compressed stream buffer.
   */
  mutable zfilebuf buf;


public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  izfBinstream () : iBinstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  izfBinstream (int fd) : iBinstream () {
    init (rdbuf ());
    rdbuf ()->attach (fd);
  }
  
  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  izfBinstream(const char *name, int mode = ios::in, int prot = 0664)
    : iBinstream () { 
    init (rdbuf ());
    if (!rdbuf()->open (name, mode, Z_BEST_SPEED, prot))
      setstate(ios::badbit);
  }

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
    clear ();
    if (!rdbuf ()->open (name, mode, Z_BEST_SPEED, prot))
      setstate(ios::badbit);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void close () { 
    iBinstream::close (); 
    if (!rdbuf ()->close ())
      setstate(ios::failbit);
  }
  
  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfilebuf* rdbuf () { return &buf; }

  /**
   * Attaches the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  void attach (int fd) {
    if (!rdbuf ()->attach (fd))
      setstate(ios::failbit);
  }

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
class ozfBinstream : public oBinstream
{
  /**
   * The compressed stream buffer.
   */
  mutable zfilebuf buf;


public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  ozfBinstream () : oBinstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  ozfBinstream (int fd) : oBinstream () { 
    init (rdbuf ());
    rdbuf ()->attach (fd);
  }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::out).
   * @param prot the protection (default 0644).
   */
  ozfBinstream (const char *name, int level = Z_BEST_SPEED,
		int mode = ios::out, int prot = 0664)
    : oBinstream () { 
    init (rdbuf ());
    if (!rdbuf()->open (name, mode, level, prot))
      setstate(ios::badbit);
  }

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
    clear ();
    if (!rdbuf ()->open (name, mode, level, prot))
      setstate(ios::badbit);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  virtual void close () { 
    oBinstream::close ();  
    if (!rdbuf ()->close ())
      setstate(ios::failbit);
  }

    
  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfilebuf* rdbuf () { return &buf; }

  /**
   * Attaches the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  void attach (int fd) {
    if (!rdbuf ()->attach (fd))
      setstate(ios::failbit);
  }


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
class zfBinstream : public Binstream
{
  /**
   * The compressed stream buffer.
   */
  mutable zfilebuf buf;


public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  zfBinstream () : Binstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  zfBinstream (int fd) : Binstream () { 
    init (rdbuf ());
    rdbuf ()->attach (fd);
  }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  zfBinstream (const char *name, int level = Z_BEST_SPEED,
	       int mode = ios::in, int prot = 0664)
    : Binstream () { 
    init (rdbuf ());
    if (!rdbuf()->open (name, mode, level, prot))
      setstate(ios::badbit);
  }

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
    clear ();
    if (!rdbuf ()->open (name, mode, level, prot))
      setstate(ios::badbit);
    Binstream::open ();
  }
  
  /**
   * Closes the stream.
   */
  void close () { 
    Binstream::close ();
    if (!rdbuf ()->close ())
      setstate(ios::failbit);
  }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfilebuf* rdbuf () { return &buf; }

  /**
   * Attaches the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  void attach (int fd) {
    if (!rdbuf ()->attach (fd))
      setstate(ios::failbit);
  }

  // I/O ------------------------------------------------------------------
};

#endif
