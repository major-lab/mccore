//                              -*- Mode: C++ -*- 
// zfstream.h
// Copyright © 2002-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Mon Jan 28 16:13:00 2002
// $Revision: 1.5.8.3 $
// $Id: zfstream.h,v 1.5.8.3 2003-12-05 19:59:45 larosem Exp $
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


#ifndef _zfstream_h_
#define _zfstream_h_

#include <iostream>
#include <zlib.h>

using namespace std;



/**
 * @short Implementation of compressed file buffer.
 *
 * This implementation of buffer suits for compressed file streams.  
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class zfstreambuf : public streambuf
{
  /**
   * The compressed file pointer used in gzread, gzwrite, etc.
   */
  gzFile file;

  /**
   * The size of the input/output buffer. 
   */
  static const int buf_size = 1024;

  /**
   * The size of the putback region.
   */ 
  static const int putback_size = 4;

  /**
   * The buffer.
   */ 
  char buffer [buf_size+putback_size];
  
  /**
   * Indicate if the file is opened.
   */ 
  bool opened;
  
  /**
   * The open mode of the gzFile.
   */ 
  int _mode;

public:

  /**
   * Initializes the object.
   */
  zfstreambuf ();
  
  /**
   * Destroys the object.
   */
  ~zfstreambuf();

  /**
   * Opens the compressed file buffer.
   * @param name the name of the file.
   * @param mode the open mode requested.
   * @param level the compression level (default Z_BEST_SPEED).
   * @return itself if the operation went successfull, 0 otherwise.
   */
  zfstreambuf* open(const char* name, int mode, int level = Z_BEST_SPEED);
  
  /**
   * Closes the zipped files.  The buffer is first synched so that the
   * buffer is flushed to disk.
   * @return 0 if the operation is successfull, itself otherwise.
   */
  zfstreambuf* close();

  /**
   * Returns the state of the buffer.
   */
  bool is_open() { return opened; }

  /**
   * Takes care of overflow in write methods.  This is the main output method
   * in GCC 2.95, GCC3.0 and sgi CC.
   * @param c the character to put in the buffer.
   * @return 0 for success, -1 if EOF is reached.
   */
  virtual int overflow (int c = EOF);

  /**
   * Takes care of underflow in read methods.  This is the main input method
   * in GCC 2.95, GCC3.0 and sgi CC.
   * @return the upstream character.
   */
  virtual int underflow ();

  /**
   * Takes care of synchronizing the file by flushing the output buffer
   * when endl or flush are called
   * @return 0 if the sync succeeded, -1 if EOF is reached.
   */
  virtual int sync (); 
};



/**
 * @short Implementation of a base class for compressed file i/o streams.
 *
 * You can use this buffer like fstreambase.
 * Crucial note: ANY Class that derives from zfstreambase must
 * initialize the zfstreambase parent last because stream state is
 * determined at that time!
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class zfstreambase : virtual public ios 
{
protected:

  /**
   * The compressed stream buffer.
   */
  mutable zfstreambuf buf;
  
public:
  
  /**
   * Initializes the stream.
   */
  zfstreambase () { init(rdbuf ()); }

  /**
   * Initializes the stream with a filename.
   * @param name the file name.
   * @param mode the file mode.
   * @param level the compression level (default Z_BEST_SPEED).
   */
  zfstreambase (const char* name, int mode, int level = Z_BEST_SPEED);

  /**
   * Destroys the stream by calling close on it.
   */
  ~zfstreambase();

  /**
   * Opens the stream with a file name.
   * @param name the file name.
   * @param mode the file mode.
   * @param level the compression level (default Z_BEST_SPEED).
   */
  void open (const char* name, int mode, int level = Z_BEST_SPEED);

  /**
   * Closes the stream.
   */
  void close ();

  /**
   * Tests if the stream is open.
   */
  bool is_open () const { return rdbuf ()->is_open (); }

  /**
   * Tests if the stream is open.
   */
  operator bool () { return is_open (); }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfstreambuf* rdbuf() const { return &buf; }
};


/**
 * @short Simple compressed input stream.
 *
 * This is a simple stream that reads a compressed gzip file.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class izfstream : public zfstreambase, public istream
{
  
 public:
  
  /**
   * Initializes the stream.
   */
  izfstream ()
    : zfstreambase (),
      istream (this->rdbuf ())
  { } 

  /**
   * Initializes the stream with filename.
   * @param name the file name.
   * @param mode the file mode.
   */
  izfstream (const char* name, int mode = ios::in)
    : zfstreambase (name, mode),
      istream (this->rdbuf ())
  { }
  
  /**
   * Opens the stream with file name.
   * @param name the file name.
   * @param mode the file mode.
   */
  void open (const char* name, int mode = ios::in)
  {
    zfstreambase::open (name, mode);
  }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfstreambuf* rdbuf () { return zfstreambase::rdbuf (); }
};



/**
 * @short Simple compressed output stream.
 *
 * This is a simple stream that writes to a compressed gzip file.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class ozfstream : public zfstreambase, public ostream
{
  
 public:

  /**
   * Initializes the stream.
   */
  ozfstream ()
    : zfstreambase (),
      ostream (this->rdbuf ())
  { }

  /**
   * Initializes the stream with filename.
   * @param name the file name.
   * @param mode the file mode.
   */
  ozfstream (const char* name, int mode = ios::out)
    : zfstreambase (name, mode),
      ostream (this->rdbuf ())
  { }

  /**
   * Opens the stream with file name.
   * @param name the file name.
   * @param mode the file mode.
   */
  void open (const char* name, int mode = ios::out)
  {
    zfstreambase::open (name, mode);
  }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfstreambuf* rdbuf () { return zfstreambase::rdbuf (); }
};

#endif
