//                              -*- Mode: C++ -*- 
// zfstreambase.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Mar 10 15:36:48 2000
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:15:42 2000
// Update Count     : 3
// Status           : Unknown.
// 



#include <stdio.h>
#include <unistd.h>

#include "zfstreambase.h"

#if defined(__GNUC__)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream.h>
#include <libio.h>
#elif defined(__sgi)
typedef ssize_t          _IO_ssize_t;
typedef size_t           _IO_size_t;
#include <errno.h>
#ifndef __set_errno
#define __set_errno(Val) errno = (Val)
#endif
#endif



#if defined(__sgi) && !defined(__GNUC__)
//  int
//  zfilebuf::_switch_to_get_mode ()
//  {
//    if (pptr () > pbase ())
//      if (overflow (EOF) == EOF)
//        return EOF;

//    setg (base (), pptr (), (pptr () > egptr ()) ? pptr () : egptr ());
//    setp (gptr (), gptr ());
//    return 0;
//  }



int
zfilebuf::_do_write (const char *data, size_t to_do)
{
  size_t count;
  
  if (to_do == 0)
    return 0;
  count = sys_write (data, to_do);
  setg (base (), base (), base ());
  setp (base (), base ());
  return count != to_do ? EOF : 0;
}
#endif



zfilebuf::~zfilebuf ()
{
  if (zf)
    {
      gzclose (zf);
      zf = 0;
    }
}



zfilebuf*
zfilebuf::open (const char *filename, _openmode mode, int level, int prot)
{
  char nmode[5];
  char fmode[5];
  int fd;

  if (is_open ())
    return 0;

  filebuf *fileb = filebuf::open (filename, mode, prot);
  
  if (! fileb || (fd = fileb->fd ()) < 0)
    return 0;

  char* nmodeptr = nmode;
  if (mode & ios::in)
    {
      *nmodeptr++ = 'r';
    }
  else if (mode & ios::out)
    *nmodeptr++ = 'w';
  *nmodeptr++ = 'b';
  *nmodeptr = '\0';
	    
  sprintf (fmode, "%s%d", nmode, level);
  zf = gzdopen (dup (fd), fmode);
  return zf ? this : 0;
}



zfilebuf*
zfilebuf::close ()
{
#if defined(__sgi) && !defined(__GNUC__)
  overflow (EOF);
  gzclose (zf);
  zf = 0;
#endif
  return (zfilebuf*)filebuf::close ();
}



#if defined(__GNUC__)

streamsize
zfilebuf::sys_read (char* buf, streamsize size)
{
  return (streamsize)gzread (zf, buf, size);
}



streampos
zfilebuf::sys_seek (streamoff off, _seek_dir dir)
{
  return gzseek (zf, off, dir);
}



streamsize
zfilebuf::sys_write (const char *data, streamsize n)
{
  _IO_ssize_t to_do = n;

  while (to_do > 0)
    {
      _IO_ssize_t count = gzwrite (zf, (voidp)data, to_do);
      if (count == 0)
	{
	  _flags |= _IO_ERR_SEEN;
	  break;
        }
      to_do -= count;
      data = data + count;
    }
  n -= to_do;
  if (_offset >= 0)
    _offset += n;
  return (streamsize)n;
}



int
zfilebuf::sys_stat (void *s)
{
  return filebuf::sys_stat (s);
}



int
zfilebuf::sys_close ()
{
  int close_status = 0;
  
  if (zf)
    {
      close_status = gzclose (zf);
      zf = 0;
    }
  if (close_status == Z_OK)
    return filebuf::sys_close ();
  else
    return close_status;
}



#elif defined(__sgi)
streamsize
zfilebuf::sys_write (const char *data, streamsize n)
{
  _IO_ssize_t to_do = n;

  while (to_do > 0)
    {
      _IO_ssize_t count = gzwrite (zf, (voidp)data, to_do);
      if (count == 0)
	break;
      to_do -= count;
      data = data + count;
    }
  n -= to_do;
  return (streamsize)n;
}



int
zfilebuf::underflow ()
{
  ssize_t count;

  if (gptr () < egptr ())
    return *(unsigned char *) gptr ();

  if (base () == 0)
    allocate ();

//    _switch_to_get_mode ();

  setg (base (), base (), base ());
  setp (base (), base ());

  count = gzread (zf, base (), ebuf () - base ());

  if (count <= 0)
    {
      if (count == 0)
	opened |= ios::eofbit;
      else
	{
	  opened |= ios::failbit;
	  count = 0;
	}
    }

  setg (eback (), gptr (), egptr () + count);
  if (count == 0)
    return EOF;
  return *(unsigned char *) gptr ();
}



int
zfilebuf::overflow (int ch)
{
  /* Allocate a buffer if needed. */
  if (pbase () == 0)
    {
      allocate ();
      setg (base (), base (), base ());
      setp (base (), base ());
    }
  if (ch == EOF)
    return _do_write (pbase (), pptr () - pbase ());
	
  if (pptr () == ebuf ()) /* Buffer is really full */
    if (_do_write (pbase (), pptr () - pbase ()) == EOF)
      return EOF;

  char *_ptr = pptr ();
  *_ptr = ch;
  pbump (1);

  if (ch == '\n')
    if (_do_write (pbase (), pptr () - pbase ()) == EOF)
      return EOF;
  return (unsigned char) ch;
}



int
zfilebuf::xsputn (const char *data, int n)
{
  const char *s = data;
  int to_do = n;
  int must_flush = 0;
  int count;

  if (n <= 0)
    return 0;

  count = ebuf () - pptr ();
  if (count >= n)
    {
      register const char *p;
      for (p = s + n; p > s; )
	{
	  if (*--p == '\n')
	    {
	      count = p - s + 1;
              must_flush = 1;
	      break;
	    }
	}
    }
  /* Then fill the buffer. */
  if (count > 0)
    {
      if (count > to_do)
	count = to_do;
      if (count > 20)
	{
	  memcpy (pptr (), s, count);
	  s += count;
	}
      else
	{
	  char *p = pptr ();
	  int i = count;
	  while (--i >= 0)
	    *p++ = *s++;
	}
      pbump (count);
      to_do -= count;
    }
  if (to_do + must_flush > 0)
    {
      int block_size, dont_write;

      if (overflow (EOF) == EOF)
	return n - to_do;

      block_size = ebuf () - base ();
      dont_write = block_size >= 128 ? to_do % block_size : 0;

      count = to_do - dont_write;
      if (_do_write (s, count) == EOF)
	return n - to_do;
      to_do = dont_write;

      /* Now write out the remainder.  Normally, this will fit in the
	 buffer, but it's somewhat messier for line-buffered files,
	 so we let _IO_default_xsputn handle the general case. */
      if (dont_write)
	{
	  char *p = pptr () + count;
	  int i;
	  
	  for (i = dont_write; --i >= 0; )
	    *p++ = *s++;
	  pbump (dont_write);
	  to_do -= dont_write;
        }
    }
  return n - to_do;
}



streambuf*
zfilebuf::setbuf(char* p, int len)
{
  if (streambuf::setbuf (p, len) == 0)
    return 0;

  setp (base (), base ());
  setg (base (), base (), base ());
  
  return (streambuf*)this;
}
#endif



zfstreambase::zfstreambase ()
{
  init (rdbuf ());
}



zfstreambase::zfstreambase (const char *name, int mode, int level, int prot)
{
  init (rdbuf ());
  if (!rdbuf()->open (name, mode, level, prot))
    setstate(ios::badbit);
}



zfstreambase::zfstreambase (int fd)
{
  init (rdbuf ());
  rdbuf ()->attach (fd);
}



void
zfstreambase::open (const char *name, int mode, int level, int prot)
{
  clear ();
  if (!rdbuf ()->open (name, mode, level, prot))
    setstate(ios::badbit);
}


void
zfstreambase::attach (int fd)
{
  if (!rdbuf ()->attach (fd))
    setstate(ios::failbit);
}



void
zfstreambase::close ()
{
  if (!rdbuf ()->close ())
    setstate(ios::failbit);
}
