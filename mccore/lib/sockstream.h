//                              -*- Mode: C++ -*- 
// sockstream.h
// Copyright � 2002-04 Laboratoire de Biologie Informatique et Th�orique.
// Author           : Patrick Gendron
// Created On       : Thu Jan 31 15:21:36 2002
// $Revision: 1.1.4.3 $
// $Id: sockstream.h,v 1.1.4.3 2004-03-25 22:11:45 larosem Exp $
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


#ifndef _sockstream_h_
#define _sockstream_h_

#include <iostream>

#include "Binstream.h"

#if defined (__sgi)
typedef int streamsize;
#else
typedef std::streamsize streamsize;
#endif

using namespace std;



/**
 * @short Implementation of a socket stream buffer.
 *
 * This descendent of streambuf implements all the necessary methods
 * to communicate through a socket.  Note that this buffer does not
 * buffer anything, it reads and writes immediately.  Some implementations
 * of libstdc++ use xsgetn to read on the socket and others use underflow.
 * Both are included in this class.  xsgetn is probably faster since
 * underflow must read one byte at a time (reason for the size 1 buffer).  
 * This is necessary since a read interrupted by a SIGNAL would not empty
 * the read buffer and desynchronize the client and server...
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
 */
class sockstreambuf : public streambuf
{
protected:

  /**
   * The id of the socket (a file descriptor).
   */
  int socket_id;

  /**
   * The size of the input/output buffer. 
   */
  static const int buf_size = 1;

  /**
   * The size of the putback region.
   */ 
  static const int putback_size = 4;
  
  /**
   * The buffer (used only for input).
   */ 
  char buffer [buf_size+putback_size];
  
public:

  /**
   * Initializes the socket stream buffer.
   */
  sockstreambuf ();
  
  /**
   * Initializes the socket stream buffer with an existing (opened) socket.
   * @param s a socket created by accept(2) or socket(2).
   */
  sockstreambuf (int s);

  /**
   * Initializes the socket stream buffer and connect to the given host.
   * @param s a socket created by accept(2) or socket(2).
   */
  sockstreambuf (const char* host, int port);

  /**
   * Destructor.
   */
  ~sockstreambuf ();


  /**
   * Opens the stream with a connection to the given host.
   * @param host the server's host name.
   * @param port the port on which to call the host.
   * @return itself if the operation went successfull, 0 otherwise.
   */
  sockstreambuf* open (const char* host, int port);

  /**
   * Closes the stream.
   */
  sockstreambuf* close ();
  
  /**
   * Tests if the stream is open.
   * @return the result of the test
   */
  bool is_open () const;

  /**
   * Stream input method.
   * This is the function called to read on the socket.  
   * @param buf the bytes to read.
   * @param size the number of bytes to read.
   * @return the number of bytes read (-1 on error)
   */
  virtual streamsize xsgetn (char* s, streamsize n);    

  /**
   * Stream output method.
   * This is the function called to write on the socket.
   * @param buf the bytes to write.
   * @param size the number of bytes to write.
   * @return the number of bytes written (-1 on error)
   */
  virtual streamsize xsputn (const char* buf, streamsize size);

  /**
   * Stream input method.
   * This is the function called to read on the socket.
   * @return the number of bytes read (-1 on error).
   */
  virtual int underflow ();


private:

  /**
   * Socket read method.
   * @param buf the bytes to read.
   * @param size the number of bytes to read.
   * @return the number of bytes read (-1 on error).
   */
  virtual streamsize sys_read (char* buf, streamsize size);

  /**
   * Socket write method.
   * @param buf the bytes to write.
   * @param size the number of bytes to write.
   * @return the number of bytes written (-1 on error)
   */ 
  virtual streamsize sys_write (const char *buf, streamsize size);

  /**
   * Closes the stream.
   * @return 0 on success.
   */
  virtual int sys_close ();
};


/**
 * @short Implementation of a base class for socket streams.
 *
 * You can use this buffer like fstreambase.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class sockstreambase : virtual public ios
{
protected:

  /**
   * The socket stream buffer.
   */
  sockstreambuf buf;

public:

  /**
   * Initializes the stream.
   */
  sockstreambase () { init(&buf); }

 /**
   * Initializes the stream buffer with an existing (opened) socket.
   * @param s a socket created by accept(2) or socket(2).
   */
  sockstreambase (int s) : buf (s) { init (&buf); }

  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  sockstreambase (const char* host, int port)
  {
    init (&buf);
    open (host, port);
  }
  
  /**
   * Destructor.
   */
  ~sockstreambase () { close (); }

  /**
   * Opens the stream with a connection to the given host.
   * @param host the server's host name.
   * @param port the port on which to call the host.
   * @return itself if the operation went successfull, 0 otherwise.
   */
  void open (const char* host, int port)
  {
    clear ();
    if (!buf.open (host, port))
      setstate (ios::badbit);
  }

  /**
   * Closes the stream.
   */
  void close ()
  {
    if (buf.is_open ())
      if (!buf.close ())
	setstate (ios::badbit);
  }

  /**
   * Tests if the stream is open.
   */
  int is_open () { return buf.is_open (); }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  sockstreambuf* rdbuf() { return &buf; }
};

#endif
