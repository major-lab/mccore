//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// Last Modified By : Martin Larose
// Last Modified On : Mon Oct  1 14:35:45 2001
// Update Count     : 13
// Status           : Ok.
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

#include <string.h>
#if defined (__FreeBSD__)
#include <sys/param.h>
#else
#include <netinet/in.h>
#endif

#include "Binstream.h"


iBinstream&
iBinstream::operator>> (char &c)
{
  short int ns;
  this->read ((char*)&ns, sizeof (short int));
  c = (char)ntohs (ns);
  return *this;
}



iBinstream&
iBinstream::operator>> (char *str)
{
  short int length;

  *this >> length;
  this->read ((char*)str, sizeof (char) * length);
  str[length] = '\0';
  return *this;
}



iBinstream&
iBinstream::operator>> (char **str)
{
  short int length;

  *this >> length;
  *str = new char[length + 1];
  this->read ((char*)*str, sizeof (char) * length);
  (*str)[length] = '\0';
  return *this;
}



iBinstream&
iBinstream::operator>> (short int &n)
{
  short int ns;

  this->read ((char*) &ns, sizeof (short int));
  n = ntohs (ns);
  return *this;
}



iBinstream&
iBinstream::operator>> (int &n)
{
  int nl;

  this->read ((char*)&nl, sizeof (int));
  n = (int)ntohl (nl);
  return *this;
}



iBinstream&
iBinstream::operator>> (long int &n)
{
  long int nl;

  this->read ((char*)&nl, sizeof (long int));
  n = (long int)ntohl (nl);
  return *this;
}



iBinstream&
iBinstream::operator>> (float &x)
{
  int nl;
  int hl;

  this->read ((char*)&nl, sizeof (int));
  hl = ntohl (nl);
  x = *((float*)&hl);
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
  short int ns = htons (c);

  this->write ((char*)&ns, sizeof (short int));
  return *this;
}



oBinstream&
oBinstream::operator<< (const char *str)
{
  short int length = strlen (str);

  *this << length;
  this->write ((char*)str, sizeof (char) * length);
  return *this;
}



oBinstream&
oBinstream::operator<< (short int n)
{
  short int ns = htons (n);
  
  this->write ((char*)&ns, sizeof (short int));
  return *this;
}



oBinstream&
oBinstream::operator<< (int n)
{
  int nl = htonl (n);

  this->write ((char*)&nl, sizeof (int));
  return *this;
}



oBinstream&
oBinstream::operator<< (long int n)
{
  long int nl = htonl (n);

  this->write ((char*)&nl, sizeof (long int));
  return *this;
}



oBinstream&
oBinstream::operator<< (float x)
{
  int nl = htonl (*((int*)&x));

  this->write ((char*)&nl, sizeof (int));
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
