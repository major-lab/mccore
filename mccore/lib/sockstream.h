//                              -*- Mode: C++ -*- 
// sockstream.h
// Copyright © 2002-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Thu Jan 31 15:21:36 2002
// $Revision: 1.1.8.2 $
// $Id: sockstream.h,v 1.1.8.2 2003-11-26 17:01:06 larosem Exp $
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
  sockstreambase (int s) : buf (s) {
    init (rdbuf ());
  }

  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  sockstreambase (const char* host, int port) {  
    init (rdbuf ());
    if (!rdbuf ()->open (host, port))
      clear (rdstate () & ios::badbit);    
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
  void open (const char* host, int port);

  /**
   * Closes the stream.
   */
  void close ();

  /**
   * Tests if the stream is open.
   */
  int is_open () { return rdbuf ()->is_open (); }

  /**
   * Gets the buffer.
   * @return the compressed file buffer object.
   */
  sockstreambuf* rdbuf() { return &buf; }
};




/**
 * @short Implementation of an input Socket stream
 *
 * This is an implementation of a communication socket for input only
 * using the ipv4 protocol and with blocking read methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
*/
class iSockstream : public iBinstream, public sockstreambase
{
public:

  /**
   * Initializes the stream.
   */
  iSockstream () : iBinstream (rdbuf ()), sockstreambase () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  iSockstream (const char* host, int port)
    : iBinstream (rdbuf ()), sockstreambase (host, port) { }

  /**
   * Creates a socket stream from an existing (opened) socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  iSockstream (int s) : iBinstream (rdbuf ()), sockstreambase (s) { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    sockstreambase::open (host, port);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () {
    iBinstream::close ();
    sockstreambase::close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockstreambuf* rdbuf () { return sockstreambase::rdbuf (); }
};




/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for output only
 * using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class oSockstream : public oBinstream, public sockstreambase
{
public:

  /**
   * Initializes the stream.
   */
  oSockstream () : oBinstream (rdbuf ()), sockstreambase () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  oSockstream (const char* host, int port)
    : oBinstream (rdbuf ()), sockstreambase (host, port) { }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  oSockstream (int s) : oBinstream (rdbuf ()), sockstreambase (s) { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    sockstreambase::open (host, port);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () {
    oBinstream::close ();
    sockstreambase::close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockstreambuf* rdbuf () { return sockstreambase::rdbuf (); }
};



/**
 * @short Implementation of an output Socket stream
 *
 * <A long description>
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class Sockstream : public Binstream, public sockstreambase
{

public:

  /**
   * Initializes the stream.
   */
  Sockstream () : Binstream (rdbuf ()), sockstreambase () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  Sockstream (const char* host, int port)
    : Binstream (rdbuf ()), sockstreambase (host, port) { }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  Sockstream (int s) : Binstream (rdbuf ()), sockstreambase (s) { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    Binstream::open ();
    sockstreambase::open (host, port);
  }

  /**
   * Closes the stream.
   */
  void  close () {
    Binstream::close ();
    sockstreambase::close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockstreambuf* rdbuf () { return sockstreambase::rdbuf (); }
};

#endif
