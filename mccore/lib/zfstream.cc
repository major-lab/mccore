//                              -*- Mode: C++ -*- 
// zfstream.cc
// Copyright © 2002-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Mon Jan 28 16:58:09 2002
// $Revision: 1.1.4.2 $
// $Id: zfstream.cc,v 1.1.4.2 2003-12-17 19:22:17 larosem Exp $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>

#include "zfstream.h"



zfstreambuf::zfstreambuf ()
  : opened (0)
{
  // Set output buffer pointers
  setp (buffer, buffer + (buf_size+putback_size-1));
  // Set input buffer pointers
  setg (buffer + putback_size,
	buffer + putback_size,
	buffer + putback_size);
}


zfstreambuf::~zfstreambuf ()
{
  close ();
}


zfstreambuf* 
zfstreambuf::open (const char* name, int mode, int level)
{
  char nmode[5];
  char fmode[5];

  if (is_open ()) return 0;
  
  _mode = mode;
  
  if ((_mode & ios::ate) || (_mode & ios::app)
      || ((_mode & ios::in) && (_mode & ios::out)))
    return 0;

  char* nmodeptr = nmode;
  if (_mode & ios::in)
    *nmodeptr++ = 'r';
  else if (_mode & ios::out)
    *nmodeptr++ = 'w';
  *nmodeptr++ = 'b';
  *nmodeptr = '\0';
	    
  sprintf (fmode, "%s%d", nmode, level);
  file = gzopen (name, fmode);

  if (file) opened = 1;

  return file ? this : 0;
}


zfstreambuf* 
zfstreambuf::close ()
{
  if (is_open ()) {
    sync ();
    opened = 0;
    if (gzclose (file) == Z_OK)
      return 0;
  }
  return this;
}


int     
zfstreambuf::overflow (int c)
{
  if (!(_mode & ios::out) || !opened)
    return EOF;
 
  int todo = pptr () - pbase ();
  int done;

  if (c != EOF) {
    *pptr () = c;
    ++todo;
    pbump (1);
  }

  // What happens if gzwrite doesn't write all the buffer?  Call sys_write instead?
  if ((done = gzwrite (file, pbase (), todo))) {
    //setp (pbase (), epptr ());
    pbump (-done);
    return (0);
  } else {
    return EOF;
  }
}


int     
zfstreambuf::underflow ()
{
  if (gptr () && (gptr () < egptr ()))
    return *gptr ();
  
  if (!(_mode & ios::in) || !opened)
    return EOF;

  int num_pb;
  num_pb = gptr () - eback ();
  if (num_pb > putback_size) {
    num_pb = putback_size;
  }
  
  memcpy (buffer + (putback_size - num_pb), 
	  gptr () - num_pb, num_pb);

  int num;
  num = gzread (file, buffer+putback_size, buf_size);
  
  if (num <= 0) {
    return EOF;
  }

  setg (buffer+(putback_size-num_pb), 
	buffer+putback_size,          
	buffer+putback_size+num);     
  
  // cast in unsigned char * necessary since *gptr () might be
  // equal to -1 == EOF when cast as a int.
  return *(unsigned char *)gptr();
}


int     
zfstreambuf::sync ()
{
  if (pptr() && pptr() > pbase()) {    
    // c will be the number of chars left to output...
    int c = overflow ();
    if (c == EOF)
      return -1;
  }
  return 0;
}




// zfstreambase::zfstreambase(const char* name, int mode = ios::in, int level)
// {
//   init (&buf);
//   open (name, mode, level);
// }


// zfstreambase::~zfstreambase()
// {
//   close();
// }


void 
zfstreambase::open (const char* name, int mode, int level)
{
  clear ();
  if (!buf.open (name, mode, level))
    setstate (ios::badbit);
}


void 
zfstreambase::close ()
{
  if (buf.is_open ())
    if (!buf.close ())
      setstate (ios::badbit);
}

