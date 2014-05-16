// zstream.cc
// Copyright © 2004, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal
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

#include <config.h>

#include <cstdio>
#include <cstring>

#include "zstream.h"


namespace mccore
{

  zstreambuf::zstreambuf () : opened (false)
  {
    // Set output buffer pointers
    setp (buffer, buffer + (buf_size+putback_size-1));
    // Set input buffer pointers
    setg (buffer + putback_size,
          buffer + putback_size,
          buffer + putback_size);
  }


  zstreambuf::~zstreambuf ()
  {
    close ();
  }


  zstreambuf* zstreambuf::open (const char* name, int mode, int level)
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

    if (file)
      opened = true;

    return file ? this : 0;
  }


  zstreambuf* zstreambuf::close ()
  {
    if (is_open ())
    {
      sync ();
      opened = false;
      if (gzclose (file) == Z_OK)
        return 0;
    }
    return this;
  }


  int zstreambuf::overflow (int c)
  {
    if (!(_mode & ios::out) || !opened)
      return EOF;

    int todo = pptr () - pbase ();
    int done;

    if (c != EOF)
    {
      *pptr () = c;
      ++todo;
      pbump (1);
    }

    // What happens if gzwrite doesn't write all the buffer?  Call sys_write instead?
    if ((done = gzwrite (file, pbase (), todo)))
    {
      //setp (pbase (), epptr ());
      pbump (-done);
      return (0);
    } 
    else 
    {
      return EOF;
    }
  }


  int zstreambuf::underflow ()
  {
    if (gptr () && (gptr () < egptr ()))
      return *gptr ();

    if (!(_mode & ios::in) || !opened)
      return EOF;

    int num_pb;
    num_pb = gptr () - eback ();
    if (num_pb > putback_size)
    {
      num_pb = putback_size;
    }
 
    memcpy (buffer + (putback_size - num_pb), 
            gptr () - num_pb, num_pb);

    int num;
    num = gzread (file, buffer+putback_size, buf_size);

    if (num <= 0)
    {
      return EOF;
    }

    setg (buffer+(putback_size-num_pb),
          buffer+putback_size,
          buffer+putback_size+num);

    // cast in unsigned char * necessary since *gptr () might be
    // equal to -1 == EOF when cast as a int.
    return *(unsigned char *)gptr();
  }


  int zstreambuf::sync ()
  {
    if (pptr() && pptr() > pbase())
    {
      // c will be the number of chars left to output...
      int c = overflow ();
      if (c == EOF)
        return -1;
    }
    return 0;
  }

}
