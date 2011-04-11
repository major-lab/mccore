//                              -*- Mode: C++ -*- 
// ServerSocket.cc
// Copyright � 2001-05 Laboratoire de Biologie Informatique et Th�orique.
//                     Universit� de Montr�al.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:56 2001
// $Revision: 1.20 $
// $Id: ServerSocket.cc,v 1.20 2005-06-07 22:15:41 larosem Exp $
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

// cmake generated defines
#include <config.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
}

#if defined(__sgi) || defined (__sun)
#include <strings.h>
#endif

#if defined (__sgi) || defined (__sun__)
typedef int socklen_t;
#endif

#include "Binstream.h"
#include "ServerSocket.h"



namespace mccore
{
  
  ServerSocket::ServerSocket (int thePort)
    : port (thePort)
  {
    sockaddr_in sin;
    
    // Creating socket ---
    if ((socket_id = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
      //      FatalSocketException exc ("socket creation failed", __FILE__, __LINE__);
      //      exc << ": " << strerror (errno);
      //      throw exc;
    }
    
    // Binding a name to the socket ---
    bzero (&sin, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (port);
    
    if (bind (socket_id, (sockaddr*) &sin, (socklen_t) sizeof (sin)) < 0) {
      //      FatalSocketException exc ("socket binding failed", __FILE__, __LINE__);
      //      exc << ": " << strerror (errno);
      //      throw exc;
    }
    
    if (listen (socket_id, MAX_QUEUE_LEN) < 0) {
      //      FatalSocketException exc ("socket listening failed", __FILE__, __LINE__);
      //      exc << ": " << strerror (errno);
      //      throw exc;
    }
    
  }

  
  sBinstream*
  ServerSocket::accept ()
  {
    sockaddr_in client;
    socklen_t clientlen;
    int cid;
    sBinstream* stream;
    
    if ((cid = ::accept (socket_id, (sockaddr*) &client, (socklen_t*) &clientlen)) < 0) {
      //      FatalSocketException exc ("socket connection accepting failed",
      //  			       __FILE__, __LINE__);
      //      exc << ": " << strerror (errno);
      //      throw exc;
    }
    
    stream = new sBinstream (cid);
    
    return stream;
  }

  
  void
  ServerSocket::close ()
  {
    
    /*
      if (shutdown (socket_id, SHUT_RDWR) == -1 && errno != ENOTCONN) {
      FatalSocketException exc ("socket shutdown failed",
      __FILE__, __LINE__);
      exc << ": " << strerror (errno);
      throw exc;
      }
    */
    
    if (::close (socket_id) == -1) {
      //      FatalSocketException exc ("socket closing failed",
      //  			       __FILE__, __LINE__);
      //      exc << ": " << strerror (errno);
      //      throw exc;
    }
  }
}
