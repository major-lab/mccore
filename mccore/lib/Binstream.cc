//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// Last Modified By : Martin Larose
// Last Modified On : Fri Apr 20 17:05:41 2001
// Update Count     : 6
// Status           : Ok.
// 



#include <string.h>
#include <netinet/in.h>

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
<<<<<<< Binstream.cc
  short int length;

  *this >> length;
  this->read ((char*)str, sizeof (char) * length);
  str[length] = '\0';
=======
  short int length;
  *this >> length;
  this->read ((char*)str, sizeof (char) * length);
  str[length] = '\0';
>>>>>>> 1.4
  return *this;
}



iBinstream&
iBinstream::operator>> (char **str)
{
<<<<<<< Binstream.cc
  short int length;

  *this >> length;
  *str = new char[length + 1];
  this->read ((char*)*str, sizeof (char) * length);
  str[length] = '\0';
  return *this;
}

=======
  short int length;
  *this >> length;
  *str = new char[length + 1];
  this->read (*str, sizeof (char) * length);
  (*str)[length] = '\0';
  return *this;
}

>>>>>>> 1.4

<<<<<<< Binstream.cc

iBinstream&
iBinstream::operator>> (short int &n)
{
  int ns;
  this->read ((char*) &ns, sizeof (short int));

  n = ntohs (ns);
=======

iBinstream&
iBinstream::operator>> (short int &n)
{
  int ns;
  this->read ((char*) &ns, sizeof (short int));
  n = ntohs (ns);
>>>>>>> 1.4
  return *this;
}



iBinstream&
iBinstream::operator>> (int &n)
{
  int nl;
  this->read ((char*) &nl, sizeof (int));
  n = (int)ntohl (nl);
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
<<<<<<< Binstream.cc
  short int ns = htons (c);
  this->write ((char*)&ns, sizeof (short int));

=======
  short int ns = htons (c);
  this->write ((char*)&ns, sizeof (short int));
>>>>>>> 1.4
  return *this;
}



oBinstream&
oBinstream::operator<< (const char *str)
{
<<<<<<< Binstream.cc
  short int length = strlen (str);

  *this << length;
  this->write ((char*)str, sizeof (char) * length);
  return *this;
}
=======
  short int length = strlen (str);
  *this << length;
  this->write ((char*)str, sizeof (char) * length);
  return *this;
}
>>>>>>> 1.4

<<<<<<< Binstream.cc


oBinstream&
oBinstream::operator<< (short int n)
{
  short int ns = htons (n);
  
  this->write ((char*)&ns, sizeof (short int));
=======


oBinstream&
oBinstream::operator<< (short int n)
{
  short int ns = htons (n);
  this->write ((char*)&ns, sizeof (short int));
>>>>>>> 1.4
  return *this;
}



oBinstream&
oBinstream::operator<< (int n)
{
<<<<<<< Binstream.cc
  int nl = htonl (n);

  this->write ((char*)&nl, sizeof (int));
=======
  int nl = htonl (n);
  this->write ((char*)&nl, sizeof (int));
>>>>>>> 1.4
  return *this;
}



oBinstream&
oBinstream::operator<< (float x)
{
<<<<<<< Binstream.cc
  int nl = htonl (*((int*)&x));
  
  this->write ((char*)&nl, sizeof (int));
=======
  int nl = htonl (*((int*)&x));
  this->write ((char*)&nl, sizeof (int));
>>>>>>> 1.4
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
