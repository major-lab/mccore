//                              -*- Mode: C++ -*- 
// sockbuf.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:26 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Sep 20 12:48:01 2001
// Update Count     : 6
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


#ifndef _sockbuf_h_
#define _sockbuf_h_

#include <iostream.h>

#if defined (__sgi) && !defined(__GNUC__)
typedef size_t streamsize;
#endif



/**
 * @short Implementation of a socket trivial buffer
 *
 * This buffer does not buffer anything, it reads and writes immediatly 
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class sockbuf : public streambuf
{
public:
  int socket_id;

  char hostname[256];

public:

  /**
   * Initializes the socket buffer.
   */
  sockbuf ();
  
  /**
   * Initializes the socket buffer with a socket.
   * @param s a socket created by accept(2) or socket(2).
   */
  sockbuf (int s) : streambuf (), socket_id (s) {}

  /**
   * Destructor.
   */
  virtual ~sockbuf () { }

  
/**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   * @return itself if the operation went successfull, 0 otherwise.
   */
  virtual sockbuf* open (const char* host, int port);

  /**
   * Closes the stream.
   */
  virtual sockbuf* close ();
  
  /**
   * Tests if the stream is open.
   */
  bool is_open () const;

  /**
   * Socket read method.
   * @param buf the bytes to read
   * @param size the number of bytes to read
   * return the number of bytes read (-1 on error)
   */
  virtual streamsize sys_read (char* buf, streamsize size);

  /**
   * Socket write method.
   * @param buf the bytes to write
   * @param len the number of bytes to write
   * @param flags the flags passed to send(2)
   * return the number of bytes written (-1 on error)
   */ 
  virtual streamsize sys_write (const char *buf, streamsize size);

  /**
   * Closes the stream.
   * @return 0 on success.
   */
  virtual int sys_close ();

  int GetSocketId () { return socket_id; } 

protected:

  /**
   * Stream input method.
   */
  virtual streamsize xsgetn (char* s, streamsize n);    

  /**
   * Stream output method.
   * 
   */
  virtual streamsize xsputn (const char* s, streamsize n);

};



/**
 * @short Wrapper for the socket trivial buffer.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class socketstreambase : virtual public ios
{
  /**
   * The socket buffer.
   */
  mutable sockbuf buf;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.
   */
  socketstreambase () { init (rdbuf ()); }

  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  socketstreambase (const char *host, int port)
  {
    init (rdbuf ());
    if (!rdbuf ()->open (host, port))
      setstate (ios::badbit);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  socketstreambase (int s) : buf (s) { init (rdbuf ()); }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    clear ();
    if (!rdbuf ()->open (host, port))
      setstate (ios::badbit);
  }

  /**
   * Closes the stream.
   */
  void  close ()
  {
    if (!rdbuf ()->close ())
      setstate (ios::failbit);
  }

  /**
   * Tests if the stream is open.
   */
  int is_open () const { return rdbuf ()->is_open (); }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockbuf* rdbuf () const { return &buf; }

  // I/O ------------------------------------------------------------------
};

#endif
