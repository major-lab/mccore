//                              -*- Mode: C++ -*- 
// ServerSocket.cc
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:56 2001
// Last Modified By : Martin Larose
// Last Modified On : Mon Oct  1 13:10:48 2001
// Update Count     : 7
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ServerSocket.h"

#include <errno.h>
#include <iostream.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#include "CException.h"

#if defined(__sgi) || defined (__sun)
#include <strings.h>

typedef int socklen_t;
#endif



ServerSocket::ServerSocket (int thePort)
  : port (thePort)
{
  sockaddr_in sin;

  // Creating socket ---
  if ((socket_id = ::socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    CFatalSocketException exc ("socket creation failed", __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }

  // Binding a name to the socket ---
  bzero (&sin, sizeof (sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons (port);

  if (::bind (socket_id, (sockaddr*)&sin, sizeof (sin)) < 0) {
    CFatalSocketException exc ("socket binding failed", __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }

  if (listen (socket_id, MAX_QUEUE_LEN) < 0) {
    CFatalSocketException exc ("socket listening failed", __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }

}

ServerSocket::~ServerSocket ()
{
}


sBinstream*
ServerSocket::accept ()
{
  sockaddr_in client;
  socklen_t clientlen;
  int cid;
  sBinstream* stream;

  if ((cid = ::accept (socket_id, (sockaddr*)&client, 
		       (socklen_t*)&clientlen)) < 0) {
    CFatalSocketException exc ("socket connection accepting failed",
			       __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }

  stream = new sBinstream (cid);

  return stream;
}

void
ServerSocket::close ()
{

  /*
  if (::shutdown (socket_id, SHUT_RDWR) == -1 && errno != ENOTCONN) {
    CFatalSocketException exc ("socket shutdown failed",
			       __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }
  */

  if (::close (socket_id) == -1) {
    CFatalSocketException exc ("socket closing failed",
			       __FILE__, __LINE__);
    exc << ": " << strerror (errno);
    throw exc;
  }
}
