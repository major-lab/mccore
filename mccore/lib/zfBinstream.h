//                              -*- Mode: C++ -*- 
// zfBinstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created on       : jeu 22 jui 1999 18:24:14 EDT
// $Revision: 1.7.4.2 $
// $Id: zfBinstream.h,v 1.7.4.2 2003-12-17 19:22:10 larosem Exp $
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


#ifndef _zfBinstream_h_
#define _zfBinstream_h_

#include <iostream>
#include <zlib.h>

#include "Binstream.h"
#include "zfstream.h"

using namespace std;



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
 * For further details see @ref iBinstream and @ref zfstreambase.  Note that
 * the compression level is not used in input streams.
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
  izfBinstream ()
    : zfstreambase (),
      iBinstream (zfstreambase::rdbuf ())
  { }
  
  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param mode the open mode (default ios::in).
   */
  izfBinstream(const char *name, int mode = ios::in)
    : zfstreambase (),
      iBinstream (zfstreambase::rdbuf ())
  {
    open (name, mode);
  }

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
    zfstreambase::open (name, mode);
    iBinstream::open ();
  }
  
  /**
   * Closes the stream.
   */
  virtual void close () { iBinstream::close (); zfstreambase::close (); }
  
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
  ozfBinstream ()
    : zfstreambase (),
      oBinstream (zfstreambase::rdbuf ())
  { }

  /**
   * Initializes the stream with file name and parameters.
   * @param name the path and file name to open.
   * @param level the compression level for output.
   * @param mode the open mode (default ios::out).
   */
  ozfBinstream (const char *name, int level = Z_BEST_SPEED, int mode = ios::out)
    : zfstreambase (),
      oBinstream (zfstreambase::rdbuf())
  {
    open (name, level, mode);
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
  void open (const char *name, int level = Z_BEST_SPEED, int mode = ios::out)
  {
    zfstreambase::open (name, mode, level);
    oBinstream::open ();
  }
  
  /**
   * Closes the stream.
   */
  virtual void close () { oBinstream::close (); zfstreambase::close (); }
  
  // I/O ------------------------------------------------------------------
};

#endif
