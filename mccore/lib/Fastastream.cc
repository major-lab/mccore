//                              -*- Mode: C++ -*- 
// Fastastream.cc
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Thu Jan 17 12:53:27 2002
// $Revision: 1.3.6.1 $
// $Id: Fastastream.cc,v 1.3.6.1 2004-12-25 02:40:34 larosem Exp $
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

#include <ctype.h>
#include <iostream>
#include <vector>

#include "Fastastream.h"



namespace mccore
{

  char*
  iFastastream::getDescription ()
  {
    char* buf = new char[512];
    char* ptr;
    char c;
  
    // Find comment line
    c = peek ();
    while (!eof () && c != '>') {
      ignore ();
      c = peek ();
    }

    if (eof ()) { cerr << "[fastastream] nothing to read" << endl; return 0; }
  
    ignore (); // ignore '>'
    c = peek ();
    ptr = buf;
    while (!eof () && c != '\n' && !iscntrl (c)) {
      *ptr = c; ptr++;
      ignore ();
      c = peek ();
    }
    *ptr = '\0';

    ignore (); // ignore end-of-line

    return buf;
  }


  vector< char >
  iFastastream::getSequence ()
  {
    vector< char > seq;
    char c;

    c = peek ();
    while (!eof () && c != '>') {
      if (isgraph (c))
	seq.push_back (c);
      ignore ();
      c = peek ();
    }

    return seq;
  }



  void 
  oFastastream::putDescription (const char* desc)
  {
    put ('>');
    *this << desc << endl;
  }


  void
  oFastastream::putSequence (const vector< char >& seq)
  {
    vector< char >::const_iterator i;
    int j;

    for (i=seq.begin (), j=0; i!=seq.end (); ++i, ++j) {
      if (j!=0 && j%80 == 0) *this << endl;
      *this << *i;
    }

    *this << endl;
  }

}
