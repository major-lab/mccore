//                              -*- Mode: C++ -*- 
// sBinstream.h
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:41 2001
// $Revision: 1.8.4.2 $
// $Id: sBinstream.h,v 1.8.4.2 2004-03-25 22:11:27 larosem Exp $
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


#ifndef _sBinstream_h_
#define _sBinstream_h_

#include "sockstream.h"
#include "Binstream.h"



/**
 * @short Implementation of an input Socket stream
 *
 * This is an implementation of a communication socket for input only
 * using the ipv4 protocol and with blocking read methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
*/
class iSockstream : public sockstreambase, public iBinstream
{
  
 public:
  
  /**
   * Initializes the stream.
   */
  iSockstream ()
    : sockstreambase (),
      iBinstream (sockstreambase::rdbuf ())
  { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  iSockstream (const char* host, int port)
    : sockstreambase (),
      iBinstream (sockstreambase::rdbuf ())
  {
    open (host, port);
  }

  /**
   * Creates a socket stream from an existing (opened) socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  iSockstream (int s)
    : sockstreambase (s),
      iBinstream (sockstreambase::rdbuf ())
  { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    sockstreambase::open (host, port);
    iBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () { iBinstream::close (); sockstreambase::close (); }

};




/**
 * @short Implementation of an output Socket stream
 *
 * This is an implementation of a communication socket for output only
 * using the ipv4 protocol and with blodking write methods.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class oSockstream : public sockstreambase, public oBinstream
{
  
 public:
  
  /**
   * Initializes the stream.
   */
  oSockstream ()
    : sockstreambase (),
      oBinstream (sockstreambase::rdbuf ())
  { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  oSockstream (const char* host, int port)
    : sockstreambase (),
      oBinstream (sockstreambase::rdbuf ())
  {
    open (host, port);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  oSockstream (int s)
    : sockstreambase (s),
      oBinstream (sockstreambase::rdbuf ())
  { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    sockstreambase::open (host, port);
    oBinstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () { oBinstream::close (); sockstreambase::close (); }

};



/**
 * @short Implementation of an output Socket stream
 *
 * <A long description>
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class Sockstream : public sockstreambase, public Binstream
{
  
 public:
  
  /**
   * Initializes the stream.
   */
  Sockstream ()
    : sockstreambase (),
      Binstream (sockstreambase::rdbuf ())
  { }
  
  /**
   * Initializes the stream with a host name and port.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  Sockstream (const char* host, int port)
    : sockstreambase (),
      Binstream (sockstreambase::rdbuf ())
  {
    open (host, port);
  }

  /**
   * Creates a socket stream from an existing socket id
   * @param s a socket created by accept(2) or socket(2)
   */
  Sockstream (int s)
    : sockstreambase (s),
      Binstream (sockstreambase::rdbuf ())
  { }

  /**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   */
  void open (const char* host, int port)
  {
    sockstreambase::open (host, port);
    Binstream::open ();
  }

  /**
   * Closes the stream.
   */
  void  close () { Binstream::close (); sockstreambase::close (); }

};

typedef Sockstream sBinstream;
typedef iSockstream isBinstream;
typedef oSockstream osBinstream;

#endif
