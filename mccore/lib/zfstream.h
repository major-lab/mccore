//                              -*- Mode: C++ -*- 
// zfstream.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca
// Created On       : Fri May 11 17:58:03 2001
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:35:22 2001
// Update Count     : 2
// Status           : Unknown.
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


#ifndef _zfstream_h_
#define _zfstream_h_


#include <iostream.h>

#include "zfilebuf.h"



/**
 * @short Compressed input file stream.
 *
 * These streams behaves like regular fstream except that we are able to
 * sets it's compression ratio on open operation.  It uses zlib.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class izfstream : public istream
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
  izfstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  izfstream (int fd) { 
    init (rdbuf ());
    rdbuf ()->attach (fd);
  }
  
  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   * @param prot the protection (default 0644).
   */
  izfstream(const char *name, int mode = ios::in, int prot = 0664) { 
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
  void open(const char *name, int mode=ios::in, int prot = 0664) { 
    clear ();
    if (!rdbuf ()->open (name, mode, Z_BEST_SPEED, prot))
      setstate(ios::badbit);
  }

  /**
   * Closes the stream.  It calls zfstreambase close () method to empty the
   * buffer and put the compression trailer at the end of the file.
   */
  void close () {
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
 * @short Compressed output file stream.
 *
 * These streams behaves like regular fstream except that we are able to
 * sets it's compression ratio on open operation.  It uses zlib.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class ozfstream : public ostream
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
  ozfstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  ozfstream (int fd) { 
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
  ozfstream (const char *name, int level = Z_BEST_SPEED,
	     int mode = ios::out, int prot = 0664) { 
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
	     int mode = ios::out, int prot = 0664) { 
    clear ();
    if (!rdbuf ()->open (name, mode, level, prot))
      setstate(ios::badbit);
  }
  
  /**
   * Closes the stream.  It calls zfstreambase close () method to empty the
   * buffer and put the compression trailer at the end of the file.
   */
  void close () { 
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
 * @short General compressed file stream.
 *
 * These streams behaves like regular fstream except that we are able to
 * sets it's compression ratio on open operation.  It uses zlib.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class zfstream : public iostream
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
  zfstream () { init (rdbuf ()); }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the input file descriptor.
   */
  zfstream (int fd) { 
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
  zfstream (const char *name, int level = Z_BEST_SPEED,
	    int mode = ios::in, int prot = 0664) {
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
	     int mode = ios::in, int prot = 0664) { 
    clear ();
    if (!rdbuf ()->open (name, mode, level, prot))
      setstate(ios::badbit);
  }

  /**
   * Closes the stream.  It calls zfstreambase close () method to empty the
   * buffer and put the compression trailer at the end of the file.
   */
  void close () { 
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
