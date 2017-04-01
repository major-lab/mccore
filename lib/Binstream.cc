//                              -*- mode: C++ -*- 
// Binstream.cc
// Copyright © 1999, 2000-05 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@orage.IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:18:52 EDT
// $Revision: 1.27 $
// $Id: Binstream.cc,v 1.27 2006-01-23 22:06:25 larosem Exp $
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




#include "Binstream.h"

#include <string>
#ifdef _MSC_VER
#include <WinSock2.h>
#endif
#include <zlib.h>

namespace mccore
{

  /**
   * 32b float to integer type punning
   */
  union f2i_32
  {
    float fv;
    int iv;
  };

  /**
   * 64b float to integer type punning
   */
  union f2i_64
  {
    double fv;
    long long int iv;
  };

  // -- class iBinstream

  iBinstream&
  iBinstream::operator>> (char& c)
  {
//     this->read (&c, 1);
//     return *this;


    mccore::bin_i16 data16;

    this->read16 (data16);

    if (sizeof (c) != 1 && (data16 < BS_MIN16 || data16 > BS_MAX16))
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "overflow while reading 16b integer value into a " 
	 << sizeof (c) * 8 << "b character variable.";
      throw ex;
    }

    c = (char)data16;

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (unsigned char& c)
  {
//     this->read ((char*)&c, 1);
//     return *this;

    mccore::bin_ui16 data16;

    this->read16 (data16);

    if (sizeof (c) != 1 && data16 > BS_UMAX16)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "overflow while reading 16b unsigned integer value into a " 
	 << sizeof (c) * 8 << "b unsigned character variable.";
      throw ex;
    }

    c = (unsigned char)data16;

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (signed char& c)
  {
//     this->read ((char*)&c, 1);
//     return *this;


    *this >> (char&)c;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (short& s)
  {
    return this->read16 (s);
  }

  iBinstream&
  iBinstream::operator>> (unsigned short& s)
  {
    return this->read16 (s);
  }
  

  iBinstream&
  iBinstream::operator>> (int& i)
  {
    return this->read32 (i);
  }


  iBinstream&
  iBinstream::operator>> (unsigned int& i)
  {
    return this->read32 (i);
  }


  iBinstream&
  iBinstream::operator>> (long& li)
  {
    long long lli;
    this->read64 (lli);

    if (sizeof (li) != 8 && (lli < BS_MIN32 || lli > BS_MAX32))
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "overflow while reading 64b signed integer value into a" 
	 << sizeof (li) * 8 << " long variable.";
      throw ex;
    }

    li = static_cast<long>(lli);

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (unsigned long& li)
  {
    unsigned long long lli;
    this->read64 (lli);

    if (sizeof (li) != 8 && lli > BS_UMAX32)
    {
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "overflow while reading 64b unsigned integer value into a" 
	 << sizeof (li) * 8 << " unsigned long variable.";
      throw ex;
    }

    li = static_cast<unsigned long>(lli);

    return *this;
  }
  
  
  iBinstream&
  iBinstream::operator>> (long long& lli)
  {
    return this->read64 (lli);
  }


  iBinstream&
  iBinstream::operator>> (unsigned long long& lli)
  {
    return this->read64 (lli);
  }


  iBinstream&
  iBinstream::operator>> (float& f)
  {
    f2i_32 fi;
    this->read32 (fi.iv);
    f = fi.fv;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (double& d)
  {
    f2i_64 fi;
    this->read64 (fi.iv);
    d = fi.fv;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (char** cstr)
  {
    mccore::bin_ui64 len = 0;

    *this >> len;
    *cstr = new char[len + 1];
    this->read (*cstr, sizeof (char)*len);
    (*cstr)[len] = '\0';

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (unsigned char** cstr)
  {
    *this >> (char**)cstr;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (signed char** cstr)
  {
    *this >> (char**)cstr;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (char* cstr)
  {
    mccore::bin_ui64 len = 0;

    *this >> len;
    this->read (cstr, sizeof (char)*len);
    cstr[len] = '\0';

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (unsigned char* cstr)
  {
    *this >> (char*)cstr;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (signed char* cstr)
  {
    *this >> (char*)cstr;
    return *this;
  }


  iBinstream&
  iBinstream::operator>> (string& str)
  {
    mccore::bin_ui64 len = 0;
    char* cstr;

    *this >> len;
    cstr = new char[len + 1];
    this->read (cstr, sizeof (char)*len);
    cstr[len] = '\0';
    str = cstr;
    delete [] cstr;

    return *this;
  }


  iBinstream&
  iBinstream::operator>> (bool& b)
  {
    char c = 0;
    
    *this >> c;

    switch (c)
    {
    case 'F': b = false; break;
    case 'T': b = true; break;
    default:
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "corrupted bool data in input binary stream";
	throw ex;
      }
    }

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

  uint16_t 
  iBinstream::netToHostFormat(uint16_t& data)
  {
	  return ntohs(data);

  }
  uint32_t
  iBinstream::netToHostFormat(uint32_t& data)
  {
	  return ntohl(data);
  }
  

  // -- class oBinstream


  oBinstream&
  oBinstream::operator<< (char c)
  {
    this->write16 ((mccore::bin_i16)c);
    return *this;
  }


  oBinstream&
  oBinstream::operator<< (unsigned char c)
  {
    this->write16 ((mccore::bin_ui16)c);
    return *this;
  }


  oBinstream&
  oBinstream::operator<< (signed char c)
  {
    this->write16 ((mccore::bin_i16)c);
    return *this;
  }


  oBinstream&
  oBinstream::operator<< (short s)
  {
    return this->write16 (s);
  }


  oBinstream&
  oBinstream::operator<< (unsigned short s)
  {
    return this->write16 (s);
  }


  oBinstream&
  oBinstream::operator<< (int i)
  {
    return this->write32 (i);
  }

  oBinstream&
  oBinstream::operator<< (unsigned int i)
  {
    return this->write32 (i);
  }


  oBinstream&
  oBinstream::operator<< (long li)
  {
    return this->write64 ((long long)li);
  }


  oBinstream&
  oBinstream::operator<< (unsigned long li)
  {
    return this->write64 ((unsigned long long)li);
  }
  

  oBinstream&
  oBinstream::operator<< (long long lli)
  {
    return this->write64 (lli);
  }


  oBinstream&
  oBinstream::operator<< (unsigned long long lli)
  {
    return this->write64 (lli);
  }
  

  oBinstream&
  oBinstream::operator<< (float f)
  {
    f2i_32 fi;
    fi.fv = f;
    return this->write32 (fi.iv);
  }


  oBinstream&
  oBinstream::operator<< (double d)
  {
    f2i_64 fi;
    fi.fv = d;
    return this->write64 (fi.iv);
  }


  oBinstream&
  oBinstream::operator<< (const char* str)
  {
    mccore::bin_ui64 len = strlen (str);

    *this << len; 
    this->write (str, sizeof (char)*len);

    return *this;
  }
  

  oBinstream&
  oBinstream::operator<< (const unsigned char* str)
  {
    *this << (const char*)str;
    return *this;
  }


  oBinstream&
  oBinstream::operator<< (const signed char* str)
  {
    *this << (const char*)str;
    return *this;
  }


  oBinstream&
  oBinstream::operator<< (const string& str)
  {
    mccore::bin_ui64 len = str.size ();

    *this << len; 
    this->write (str.data (), sizeof (char)*len);

    return *this;
  }


  oBinstream&
  oBinstream::operator<< (bool b)
  {
    return *this << (char)(b ? 'T' : 'F');
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

  uint16_t oBinstream::hostToNetFormat(uint16_t& data)
  {
	  return htons(data);
  }
  
  uint32_t oBinstream::hostToNetFormat(uint32_t& data)
  {
	  return htonl(data);
  }

  
}
