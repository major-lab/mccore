//                              -*- Mode: C++ -*- 
// sBinstream.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:41 2001
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:04:37 2001
// Update Count     : 1
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



#ifndef _sBinstream_h_
#define _sBinstream_h_

#include "sockbuf.h"
#include "Binstream.h"


/**
 * @short Implementation of an input Socket stream
 *
 * This is an implementation of a communication socket for input only
 * using the ipv4 protocol and with blodking read methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
*/
class isBinstream : public iBinstream
{
  mutable sockbuf buf;

public:

  /**
   * Initializes the stream.
   */
  isBinstream () : iBinstream () { init (rdbuf ()); }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  isBinstream (const char* host, int port)
    : iBinstream () { 
    init (rdbuf ());
    rdbuf()->open (host, port);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  isBinstream (int s) : iBinstream (), buf (s) { 
    init (rdbuf ());
//      rdbuf ()->attach (s);
  }

  /**
   * Destructor.
   */
  virtual ~isBinstream () { }
  
  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    clear ();
    rdbuf ()->open (host, port);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () {
    iBinstream::close ();
    rdbuf ()->close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockbuf* rdbuf () { return &buf; }
};




/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for output only
 * using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class osBinstream : public oBinstream
{
  mutable sockbuf buf;

public:

  /**
   * Initializes the stream.
   */
  osBinstream () : oBinstream () { init (rdbuf ()); }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  osBinstream (const char* host, int port)
    :  oBinstream () { 
    init (rdbuf ());
    rdbuf()->open (host, port);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  osBinstream (int s) : oBinstream (), buf (s) { 
    init (rdbuf ());
//      rdbuf ()->attach (s);
  }

  /**
   * Destructor.
   */
  virtual ~osBinstream () { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    clear ();
    rdbuf ()->open (host, port);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () {
    oBinstream::close ();
    rdbuf ()->close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockbuf* rdbuf () { return &buf; }
};



/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for input and
 * output using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
*/
class sBinstream : public Binstream
{
  mutable sockbuf buf;  

public:

  /**
   * Initializes the stream.
   */
  sBinstream () : Binstream () { init (rdbuf ()); }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  sBinstream (const char* host, int port)
    : Binstream () { 
    init (rdbuf ());
    rdbuf()->open (host, port);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  sBinstream (int s) : Binstream (), buf (s) { 
    init (rdbuf ());
  }

  /**
   * Destructor.
   */
  virtual ~sBinstream () { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port) {
    clear ();
    rdbuf ()->open (host, port);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () {
    Binstream::close ();
    rdbuf ()->close ();
  }

  /**
   * Gets the buffer.
   * @return the socket buffer object.
   */
  sockbuf* rdbuf () { return &buf; }
};

#endif
