//                              -*- Mode: C++ -*- 
// sBinstream.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:41 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 23 15:10:31 2001
// Update Count     : 3
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
class isBinstream : public socketstreambase, public iBinstream
{

public:

  /**
   * Initializes the stream.
   */
  isBinstream () : socketstreambase (), iBinstream () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  isBinstream (const char* host, int port)
    : socketstreambase (host, port), iBinstream () { }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  isBinstream (int s) : socketstreambase (s), iBinstream () { }

  /**
   * Destructor.
   */
  virtual ~isBinstream () { }
  
  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    socketstreambase::open (host, port);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close ()
  {
    iBinstream::close ();
    socketstreambase::close ();
  }
};



/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for output only
 * using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class osBinstream : public socketstreambase, public oBinstream
{

public:

  /**
   * Initializes the stream.
   */
  osBinstream () : socketstreambase (), oBinstream () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  osBinstream (const char* host, int port)
    :  socketstreambase (host, port), oBinstream () { }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  osBinstream (int s) : socketstreambase (s), oBinstream () { }

  /**
   * Destructor.
   */
  virtual ~osBinstream () { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    socketstreambase::open (host, port);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close ()
  {
    oBinstream::close ();
    socketstreambase::close ();
  }
};



/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for input and
 * output using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
*/
class sBinstream : public socketstreambase, public Binstream
{

public:

  /**
   * Initializes the stream.
   */
  sBinstream () : socketstreambase (), Binstream () { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  sBinstream (const char* host, int port)
    : socketstreambase (host, port), Binstream () { }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  sBinstream (int s) : socketstreambase (s), Binstream () { }

  /**
   * Destructor.
   */
  virtual ~sBinstream () { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    socketstreambase::open (host, port);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close ()
  {
    Binstream::close ();
    socketstreambase::close ();
  }
};

#endif
