//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000-05 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// $Revision: 1.21 $
// $Id: Binstream.cc,v 1.21 2005-01-05 01:42:45 larosem Exp $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstring>
#include <string>
#if defined (__FreeBSD__)
#include <sys/param.h>
#else
#include <netinet/in.h>
#endif

#include "Binstream.h"



namespace mccore
{
  
  iBinstream&
  iBinstream::operator>> (char &c)
  {
    short int ns;
    iBinstream::read ((char*)&ns, sizeof (short int));
    c = (char)ntohs (ns);
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (char *str)
  {
    short int length;
    
    *this >> length;
    iBinstream::read ((char*)str, sizeof (char) * length);
    str[length] = '\0';
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (char **str)
  {
    short int length;
    
    *this >> length;
    *str = new char[length + 1];
    iBinstream::read ((char*)*str, sizeof (char) * length);
    (*str)[length] = '\0';
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (string &str)
  {
    short int length;
    char *buffer;
    
    *this >> length;
    buffer = new char[length + 1];
    iBinstream::read (buffer, sizeof (char) * length);
    buffer[length] = '\0';
    str = buffer;
    delete[] buffer;
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (short int &n)
  {
    short int ns;
    
    iBinstream::read ((char*) &ns, sizeof (short int));
    n = ntohs (ns);
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (int &n)
  {
    int nl;
    
    iBinstream::read ((char*)&nl, sizeof (int));
    n = (int)ntohl (nl);
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (long int &n)
  {
    long int nl;
    
    iBinstream::read ((char*)&nl, sizeof (long int));
    n = (long int)ntohl (nl);
    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (float &x)
  {
    long int nl;
    long int hl;
    
    iBinstream::read ((char*)&nl, sizeof (long int));
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
    
    oBinstream::write ((char*)&ns, sizeof (short int));
    return *this;
  }
  
  
  oBinstream&
  oBinstream::operator<< (const char *str)
  {
    short int length = strlen (str);
    *this << length;
    oBinstream::write ((char*)str, sizeof (char) * length);
    return *this;
  }
  
  
  oBinstream&
  oBinstream::operator<< (const string &str)
  {
    unsigned int length;

    length = str.size ();
    *this << length;
    oBinstream::write (str.data (), sizeof (char) * length);
    return *this;
  }

  
  oBinstream&
  oBinstream::operator<< (short int n)
  {
    short int ns = htons (n);
    
    oBinstream::write ((char*)&ns, sizeof (short int));
    return *this;
  }
  
  
  oBinstream&
  oBinstream::operator<< (int n)
  {
    int nl = htonl (n);
    
    oBinstream::write ((char*)&nl, sizeof (int));
    return *this;
  }
  
  
  oBinstream&
  oBinstream::operator<< (long int n)
  {
    long int nl = htonl (n);
    
    oBinstream::write ((char*)&nl, sizeof (long int));
    return *this;
  }
  
  
  oBinstream&
  oBinstream::operator<< (float x)
  {
    long int nl = htonl (*((long int*)&x));
    
    oBinstream::write ((char*)&nl, sizeof (long int));
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
  
}
