//                              -*- Mode: C++ -*- 
// stlio.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Apr  9 13:38:51 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Mon Jun  9 16:18:34 2003
// Update Count     : 20
// Status           : Unknown.
// 

#ifndef _stlio_h_
#define _stlio_h_

#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <map>

using namespace std;

template< typename T, typename S >
ostream& operator<< (ostream &os, const pair< T, S > &t)
{
  os << "(" << t.first << ", " << t.second << ") ";
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
ostream& operator<< (ostream &os, const vector< T > &t)
{
  typename vector< T >::const_iterator i;
  
  for (i=t.begin(); i!=t.end (); ++i)
    {
      os << *i << " ";
    }
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

#endif
