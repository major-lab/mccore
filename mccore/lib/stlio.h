//                              -*- Mode: C++ -*- 
// stlio.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Apr  9 13:38:51 2003
// $Revision: 1.9 $
// $Id: stlio.h,v 1.9 2005-01-03 23:08:43 larosem Exp $
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


#ifndef _mccore_stlio_h_
#define _mccore_stlio_h_

#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <map>



namespace std
{
  template< typename T, typename S >
  ostream& operator<< (ostream &os, const pair< T, S > &t)
  {
    os << "(" << t.first << ", " << t.second << ") ";
    return os;
  }

  template< typename T, typename S >
  ostream& operator<< (ostream &os, const pair< T*, S* > &t)
  {
    os << "(" << *(t.first) << ", " << *(t.second) << ") ";
    return os;
  }

  template< typename T >
  ostream& operator<< (ostream &os, const set< T > &t)
  {
    typename set< T >::const_iterator i;

    for (i=t.begin(); i!=t.end (); ++i)
      {
	os << *i << " ";
      }
    return os;
  }

  template< typename T >
  ostream& operator<< (ostream &os, const set< T* > &t)
  {
    typename set< T* >::const_iterator i;
    
    for (i = t.begin (); i != t.end (); ++i)
      os << **i << " ";
    return os;
  }

  template< typename T >
  ostream& operator<< (ostream &os, const vector< T > &t)
  {
    typename vector< T >::const_iterator i;
    
    os << "[";
    for (i=t.begin(); i!=t.end (); ++i)
      {
	if (i!=t.begin ()) os << " ";
	os << *i;
      }
    os << "]";
    return os;
  }

  template< typename T >
  ostream& operator<< (ostream &os, const vector< T* > &t)
  {
    typename vector< T* >::const_iterator i;
    
    os << "[";
    for (i = t.begin (); i != t.end (); ++i) {
      if (i!=t.begin ()) os << " ";
      os << **i << " ";
    }
    os << "]";
    return os;
  }

  template< typename T >
  ostream& operator<< (ostream &os, const list< T > &t)
  {
    typename list< T >::const_iterator i;
    
    for (i=t.begin(); i!=t.end (); ++i)
      {
	os << *i << " ";
      }
    return os;
  }
  
  template< typename T >
  ostream& operator<< (ostream &os, const list< T* > &t)
  {
    typename list< T* >::const_iterator i;
    
    for (i = t.begin (); i != t.end (); ++i)
      os << **i << " ";
    return os;
  }
  
  template< typename T, typename S >
  ostream& operator<< (ostream &os, const map< T, S > &t)
  {
    typename map< T, S >::const_iterator i;
    for (i=t.begin(); i!=t.end (); ++i)
      {
	os << "(" << i->first << "=" << i->second << ") ";
      }
    return os;
  }

  template< typename T, typename S >
  ostream& operator<< (ostream &os, const map< T, S* > &t)
  {
    typename map< T, S* >::const_iterator i;
    
    for (i = t.begin (); i != t.end (); ++i)
      os << "(" << i->first << "=" << *(i->second) << ") ";
    return os;
  }

  template< typename T, typename S >
  ostream& operator<< (ostream &os, const map< T*, S > &t)
  {
    typename map< T*, S >::const_iterator i;
    
    for (i = t.begin (); i != t.end (); ++i)
      os << "(" << *(i->first) << "=" << i->second << ") ";
    return os;
  }

  template< typename T, typename S >
  ostream& operator<< (ostream &os, const map< T*, S* > &t)
  {
    typename map< T*, S* >::const_iterator i;
    
    for (i = t.begin (); i != t.end (); ++i)
      os << "(" << *(i->first) << "=" << *(i->second) << ") ";
    return os;
  }

  template< typename T >
  class Print : public unary_function< T, void >
  {
    ostream &os;

  public:

    Print (ostream &os) : os (os) { }

    void operator() (T &obj)
    {
      os << obj;
    }
  };

  template< typename T >
  class PrintLn : public unary_function< T, void >
  {
    ostream &os;

  public:

    PrintLn (ostream &os) : os (os) { }

    void operator() (T &obj)
    {
      os << obj << endl;
    }
  };
}

#endif
