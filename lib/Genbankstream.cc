// Genbankstream.cc
// Copyright © 2002-04, 2014 Laboratoire de Biologie Informatique et Theorique.
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
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include <config.h>

#include <cstring>
#include <cctype>

#include "Genbankstream.h"

namespace mccore
{

  char* iGenbankstream::getDescription ()
  {
    char* buf = new char[512];

    *this >> buf;

    while (!eof () && strcmp (buf, "LOCUS") != 0)
    {
      *this >> buf;
    }
    *this >> buf;

    if (eof ()) { cerr << "[genbankstream] description nothing to read" << endl; return 0; }

    return buf;
  }

  vector< char > iGenbankstream::getSequence ()
  {
    char* buf = new char[512];
    vector< char > seq;

    *this >> buf;
    while (!eof ())
    {
      if (strcmp (buf, "ORIGIN") == 0)
      {
        *this >> buf;

        while (!eof () && strcmp (buf, "//") != 0)
        {
          if (!isdigit(buf[0]))
          {
            unsigned int i;
            for (i = 0; i < strlen (buf); ++i)
            {
              seq.push_back (toupper (buf[i]));
            }
          }
          *this >> buf;
        }
        break;
      }
      else
      {
        *this >> buf;
      }
    }

    char c;
    c = peek ();
    while (iscntrl (c) && !eof ()) { ignore (); c = peek (); }

    if (seq.size () == 0) { cerr << "[genbankstream] nothing to read" << endl; }

    return seq;
  }

}
