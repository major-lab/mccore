//                              -*- Mode: C++ -*- 
// stlio.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Apr  9 13:38:51 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Apr 10 11:05:47 2003
// Update Count     : 5
// Status           : Unknown.
// 

#ifndef _stlio_h_
#define _stlio_h_

#include <set>
#include <vector>
#include <list>
#include <map>

template< class T >
ostream& operator<< (ostream &os, const set< T > &t)
{
  copy (t.begin (), t.end (), ostream_iterator< T > (cout, " "));
  return os;
}

template< class T >
ostream& operator<< (ostream &os, const vector< T > &t)
{
  copy (t.begin (), t.end (), ostream_iterator< T > (cout, " "));
  return os;
}

template< class T >
ostream& operator<< (ostream &os, const list< T > &t)
{
  copy (t.begin (), t.end (), ostream_iterator< T > (cout, " "));
  return os;
}

template< class T, class S >
ostream& operator<< (ostream &os, const map< T, S > &t)
{
  for (map< T, S >::const_iterator i=t.begin(); i!=t.end (); ++i)
    {
      os << "(" << i->first << "=" << i->second << ") ";
    }
  return os;
}

template< class T, class S >
ostream& operator<< (ostream &os, const pair< T, S > &t)
{
  os << "(" << t.first << ", " << t.second << ") ";
  return os;
}


#endif
