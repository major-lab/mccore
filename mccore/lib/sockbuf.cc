//                              -*- Mode: C++ -*- 
// sockbuf.cc
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:34 2001
// Last Modified By : Martin Larose
// Last Modified On : Mon Oct  1 14:15:59 2001
// Update Count     : 11
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

#include <errno.h>
#include <iostream.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#include "CException.h"
#include "sockbuf.h"

#if defined(__sgi) || defined (__sun)
#include <strings.h>
#endif



#ifndef HAVE_ISFDTYPE
int
isfdtype (int fd, int fdtype)
{
  struct stat buf;

  if (fstat (fd, &buf) < 0)
    return -1;
  if ((int)(buf.st_mode & S_IFMT) == fdtype)
    return 1;
  else
    return 0;
}
#endif



sockbuf::sockbuf ()
  : streambuf ()
{
  // Creating socket ---
  if ((socket_id = ::socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      CFatalSocketException exc ("socket creation failed", __FILE__, __LINE__);

      exc << ": " << strerror (errno);
      throw exc;
    }
}


sockbuf* 
sockbuf::open (const char* host, int port)
{
  sockaddr_in sin;
  hostent *hp;

  // Getting host info ---
  hp = gethostbyname (host);

  if (hp == NULL)
    {
      CSocketException exc ("unknown host: ");

      exc << host;
      throw exc;
    }

  // Setting server parameters ---
  bzero ((char*)&sin, sizeof (sin));
  bcopy (hp->h_addr, (char*)&sin.sin_addr, hp->h_length);
  sin.sin_family = hp->h_addrtype;
  sin.sin_port = htons (port);
  
  if (::connect (socket_id, (sockaddr*)&sin, sizeof (sin)) < 0)
    {
      CConnectionException exc ("connection to ");
      
      exc << host << " via port #" << port
	  << " failed:\n\t" << strerror (errno);
      throw exc;
    }

  return this;
}


sockbuf*
sockbuf::close ()
{
  return sys_close () ? this : 0;
}



bool
sockbuf::is_open () const
{
  return isfdtype (socket_id, S_IFSOCK) > 0;
}



streamsize
sockbuf::sys_read (char* buf, streamsize size)
{
  int nleft;
  int nread;
  char* ptr;
  
  ptr = buf;
  nleft = size;

  while (nleft > 0)
    {
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
      signal (SIGPIPE, SIG_IGN);
      if ((nread = ::recv (socket_id, ptr, nleft, 0)) < 0)
#else
      if ((nread = ::recv (socket_id, ptr, nleft, MSG_NOSIGNAL)) < 0)
#endif
	{
	  if (errno == EINTR)	
	    nread = 0;
	  else
	    {
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
	      signal (SIGPIPE, SIG_DFL);
#endif
	      return -1;
	    }
	}
      else if (nread == 0)
	break;
      nleft -= nread;
      ptr += nread;
    }
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
  signal (SIGPIPE, SIG_DFL);
#endif
  return (size - nleft);
}



streamsize 
sockbuf::sys_write (const char *buf, streamsize size)
{
  int nleft;
  int nsent;
  const char* ptr;

  ptr = buf;
  nleft = size;
  while (nleft > 0)
    {
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
      signal (SIGPIPE, SIG_IGN);
      if ((nsent = ::send (socket_id, ptr, nleft, 0)) < 0)
#else
      if ((nsent = ::send (socket_id, ptr, nleft, MSG_NOSIGNAL)) < 0)
#endif
	{
	  if (errno == EINTR)
	    nsent = 0;
	  else
	    {
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
	      signal (SIGPIPE, SIG_DFL);
#endif
	      return -1;
	    }
	}
      nleft -= nsent;
      ptr += nsent;
    }
#if defined (__sgi) || defined (__sun) || defined (__FreeBSD__)
  signal (SIGPIPE, SIG_DFL);
#endif
  return size;
}



int
sockbuf::sys_close ()
{
  overflow (EOF);

  if (::shutdown (socket_id, SHUT_RDWR) == -1 && errno != ENOTCONN)
    {
      CFatalSocketException exc ("socket shutdown failed",
				 __FILE__, __LINE__);
      
      exc << ": " << strerror (errno);
      throw exc;
    }
  
  if (::close (socket_id) == -1)
    {
      CFatalSocketException exc ("socket closing failed",
				 __FILE__, __LINE__);
      
      exc << ": " << strerror (errno);
      throw exc;
    }
  return true;
}



streamsize
sockbuf::xsgetn (char* s, streamsize n)
{
  // More things to do if the read is incomplete
  streamsize r = sys_read (s, n);
  
  if (r != n)
    {
      CSocketException exc ("Warning: incomplete read (");
      
      exc << r << "/" << n << " bytes):\n\t" << strerror (errno);
      throw exc;
    }
  return r;
}



streamsize
sockbuf::xsputn (const char* s, streamsize n)
{
  // More things to do if the write is incomplete
  streamsize w = sys_write (s, n);

  if (w !=n )
    {
      CSocketException exc ("Warning: incomplete write (");
      
      exc << w << "/" << n << " bytes):\n\t" << strerror (errno);
      throw exc;
    }
  return w;
}
