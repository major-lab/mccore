//                              -*- Mode: C++ -*- 
// zfilebuf.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Mar 10 15:24:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:04:55 2001
// Update Count     : 4
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


#ifndef _zfilebuf_h_
#define _zfilebuf_h_


#if defined(__GNUC__)
#include <streambuf.h>
#include <fstream.h>

typedef ios::openmode _openmode;

#elif defined(__sgi)
#include <fstream.h>

typedef size_t streamsize;
typedef ios::seek_dir _seek_dir;
typedef int _openmode;
#endif

#include <zlib.h>



/**
 * @short Implementation of compressed file buffer.
 *
 * This implementation of buffer suits for compressed file streams.  
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class zfilebuf : public filebuf
{
  /**
   * The compressed file pointer used in gzread, gzwrite, etc.
   */
  gzFile zf;

#if defined(__sgi) && !defined(__GNUC__)
//    int _switch_to_get_mode ();
  /**
   * Writes data to the file in sgi compilation mode.
   * @param data the characters to write.
   * @param to_do how many characters to write.
   * @return the number of characters actually written.
   */
  int _do_write (const char *data, size_t to_do);
#endif
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  zfilebuf () : filebuf (), zf (0) { }

  /**
   * Initializes the objet with a file descriptor.
   * @param fd the file descriptor.
   */
  zfilebuf (int fd) : filebuf (fd), zf (0) { }

  /**
   * Initializes the objet with a file descriptor using a predefined
   * buffer. 
   * @param fd the file descriptor.
   * @param p the buffer used.
   * @param len the length of the buffer.
   */
  zfilebuf (int fd, char *p, int len) : filebuf (fd, p, len), zf (0) { }
  virtual ~zfilebuf ();

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the compressed file descriptor.
   * @param filename the name of the file.
   * @param mode the open mode requested.
   * @param level the compression level (default Z_BEST_SPEED).
   * @param prot the file mode (default 0664).
   * @return itself if the operation went successfull, 0 otherwise.
   */
  zfilebuf* open (const char *filename, _openmode mode,
		  int level = Z_BEST_SPEED, int prot = 0664);
  
  /**
   * Closes the zipped files.  In linux, the filebuf close method calls the
   * virtual method sys_close (defined later) witch do a gzclose on the
   * gzFile.  The filebuf close method must be called first, it purges the
   * buffer before closing the file descriptor.  With IRIX this method is
   * not used, so we get sure that we empties the buffer with overflow (EOF)
   * before closing the gzFile.
   * @return 0 if the operation is successfull, itself otherwise.
   */
  zfilebuf* close ();

#if defined(__GNUC__)
  /**
   * Reads the file in the buffer.  When using the GNU compiler we only have
   * to define the sys_read, sys_seek, sys_write, sys_stat and sys_close.
   * The rest of the methods are portable and uses these.
   * @param buf where to put the character read.
   * @param size the number of characters to read.
   * @return the number of characters actually read.
   */
  virtual streamsize sys_read (char* buf, streamsize size);

  /**
   * Seeks in the file.
   * @param off the offset to reach.
   * @param dir from witch position (start, current, end of file) the seek
   * is done.
   * @return the new stream position.
   */
  virtual streampos sys_seek (streamoff off, _seek_dir dir);

  /**
   * Writes in the compressed file buffer.
   * @param data the characters to write.
   * @param n the size of the string.
   * @return the number of characters written.
   */
  virtual streamsize sys_write (const char *data, streamsize n);

  /**
   * Gives informations about the current stream.
   * @param s the struct stat to fill.
   * @return 0 on success.
   */
  virtual int sys_stat (void *s);

  /**
   * Closes the stream.
   * @return 0 on success.
   */
  virtual int sys_close ();
  
#elif defined(__sgi)
  /**
   * Writes in the data in the buffer.
   * @param data the characters to write.
   * @param n the size of the string.
   * @return the number of characters written.
   */ 
  virtual streamsize sys_write (const char *data, streamsize n);

  /**
   * Takes care of underflow in read and write sgi methods.  It is meant for
   * internal use only.
   * @return the upstream character.
   */
  virtual int underflow ();

  /**
   * Takes care of overflow in write sgi methods.  It is meant for
   * internal use only.
   * @return the downstream character.
   */
  virtual int overflow (int ch = EOF);

  /**
   * Writes the data to the buffer.
   * @param data the characters to write.
   * @param n the number of characters to write.
   * @return the number of characters written.
   */
  virtual int xsputn (const char *data, int n);

  /**
   * Sets the internal buffer to an external one.
   * @param p the buffer.
   * @param len the size of the buffer.
   * @return the stream buffer.
   */
  virtual streambuf* setbuf (char *p, int len);

  // I/O ------------------------------------------------------------------
#endif
};



/**
 * @short Implementation of the wrapper over the compressed file buffer.
 *
 * You can use this buffer like fstreambase.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class zfstreambase : virtual public ios
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
  zfstreambase ();

  /**
   * Initializes the stream with filename.
   * @param name the file name.
   * @param mode the file mode.
   * @param level the compression level (default Z_BEST_SPEED).
   * @param prot the protection mode (default 0644).
   */
  zfstreambase (const char *name, int mode, int level = Z_BEST_SPEED,
		int prot = 0644);

  /**
   * Initializes the stream with the file descriptor.
   * @param fd the file descriptor.
   */
  zfstreambase (int fd);

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Opens the stream with file name.
   * @param name the file name.
   * @param mode the file mode.
   * @param level the compression level (default Z_BEST_SPEED).
   * @param prot the protection mode (default 0644).
   */
  void open (const char *name, int mode, int level = Z_BEST_SPEED,
	     int prot = 0644);

  /**
   * Attaches the stream with a file descriptor.
   * @param fd the file descriptor.
   */
  void attach (int fd);

  /**
   * Closes the stream.
   */
  void close ();

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  zfilebuf* rdbuf () { return &buf; }

  // I/O ------------------------------------------------------------------
};

#endif
