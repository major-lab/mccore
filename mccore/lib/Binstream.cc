//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000, 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// Last Modified By : Martin Larose
// Last Modified On : Mon Jan 22 16:53:40 2001
// Update Count     : 4
// Status           : Ok.
// 



#include <string.h>

#include "Binstream.h"



#ifdef WORDS_BIGENDIAN

#define MASK_0 0xff000000L
#define MASK_1 0x00ff0000L
#define MASK_2 0x0000ff00L
#define MASK_3 0x000000ffL

void
swap_endian (long *x)
{
  long oldl = *x;
  
  *x = (((oldl & MASK_3) << 24) | ((oldl & MASK_2) << 8)
	| ((oldl & MASK_1) >> 8) | ((oldl & MASK_0) >> 24));
}
#endif



iBinstream&
iBinstream::operator>> (char &c)
{
  this->read (&c, sizeof (char));
  return *this;
}



iBinstream&
iBinstream::operator>> (char *str)
{
  size_t tmpInt;

  *this >> tmpInt;
  this->read (str, sizeof (char) * (tmpInt + 1));
  return *this;
}



iBinstream&
iBinstream::operator>> (char **str)
{
  size_t tmpInt;

  *this >> tmpInt;
  *str = new char[tmpInt + 1];
  this->read (*str, sizeof (char) * (tmpInt + 1));
  return *this;
}



iBinstream&
iBinstream::operator>> (int &n)
{
  this->read ((char*) &n, sizeof (int));
#ifdef WORDS_BIGENDIAN
  swap_endian ((long*)&n);
#endif
  return *this;
}



iBinstream&
iBinstream::operator>> (float &x)
{
  this->read ((char*)&x, sizeof (float));
#ifdef WORDS_BIGENDIAN
  swap_endian ((long*)&x);
#endif
  return *this;
}



iBinstream&
iBinstream::operator>> (istream& (*func)(istream&))
{
  (*func)(*this);
  return *this;
}



iBinstream&
iBinstream::operator>> (ios& (*func)(ios&))
{
  (*func)(*this);
  return *this;
}



oBinstream&
oBinstream::operator<< (char c)
{
  this->write (&c, sizeof (char));
  return *this;
}



oBinstream&
oBinstream::operator<< (const char *str)
{
  size_t tmpInt = strlen (str);

  *this << tmpInt;
  this->write (str, sizeof (char) * (tmpInt + 1));
  return *this;
}



oBinstream&
oBinstream::operator<< (int n)
{
  int tmp = n;

#ifdef WORDS_BIGENDIAN
  swap_endian ((long*)&tmp);
#endif
  this->write ((char*)&tmp, sizeof (int));
  return *this;
}



oBinstream&
oBinstream::operator<< (float x)
{
  float tmp = x;  
  
#ifdef WORDS_BIGENDIAN
  swap_endian ((long*)&tmp);
#endif
  this->write ((char*)&tmp, sizeof (float));
  return *this;
}



oBinstream&
oBinstream::operator<< (ios& (*func)(ios&))
{
  (*func)(*this);
  return *this;
}



oBinstream&
oBinstream::operator<< (ostream& (*func)(ostream&))
{
  (*func)(*this);
  return *this;
}
