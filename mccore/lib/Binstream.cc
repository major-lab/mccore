//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:22 2000
// Update Count     : 3
// Status           : Ok.
// 



#include <netinet/in.h>
#include <string.h>

#include "Binstream.h"



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
  int tmp;
  
  this->read ((char*) &tmp, sizeof (int));
  n = ntohl ((long)tmp);
  return *this;
}



iBinstream&
iBinstream::operator>> (float &x)
{
  int tmp;
  
  this->read ((char*)&tmp, sizeof (float));
  tmp = ntohl (tmp);
  x = *(float*)&tmp;
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
  int tmp = htonl (n);

  this->write ((char*)&tmp, sizeof (int));
  return *this;
}



oBinstream&
oBinstream::operator<< (float x)
{
  int tmp = htonl (*(int*)&x);  
  
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
