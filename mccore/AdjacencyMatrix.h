//                              -*- Mode: C++ -*- 
// AdjacencyMatrix.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Wed Aug 13 18:24:14 2003
// $Revision: 1.3 $
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


#ifndef _mccore_AdjacencyMatrix_h_
#define _mccore_AdjacencyMatrix_h_

#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

namespace mccore {

  
  /**
   * Abstract base clas for an adjacency matrix.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   * @version $Id: AdjacencyMatrix.h,v 1.3 2005-01-03 22:49:13 larosem Exp $
   */
  class AdjacencyMatrix 
  {

    // LIFECYCLE ---------------------------------------------------------------

    AdjacencyMatrix (const AdjacencyMatrix& other) {}
    AdjacencyMatrix& operator= (const AdjacencyMatrix &other) { return *this; }
    
  public:   

    AdjacencyMatrix () {}
    virtual ~AdjacencyMatrix () {}

    // ACCESS ------------------------------------------------------------------

    virtual int get (int o, int p) const = 0;
    virtual int& elem (int o, int p) = 0;

    // METHODS -----------------------------------------------------------------

    //    virtual list< int > erase (int n) = 0;

    virtual int connect (int o, int p, int e) = 0;
    virtual int disconnect (int o, int p) = 0;


    virtual void resize (int size) = 0;
    virtual int size () const = 0;
    virtual void clear () = 0;

    virtual list< int > neighbors (int n) const = 0;

    bool contains (int n) const {
      return n<size ();
    }

    bool areConnected (int o, int p) const {
      return get (o, p) != -1;
    }

    // I/O ---------------------------------------------------------------------

    virtual ostream& output (ostream& os) const
    {
      for (int i=0; i!=size (); ++i) {
	os << i << " : "; 
	for (int j=0; j!=size (); ++j) {
	  if (get (i, j) == -1) os << "- ";
	  else os << get (i, j) << " ";
	}
	os << endl;
      }
      return os;
    }
  };



  /**
   * Implementation of an adjacency matrix using an array.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   */
  class ArrayMatrix : public AdjacencyMatrix 
  {
    int *array;
    int msize;

    // LIFECYCLE ---------------------------------------------------------------

  public:

    ArrayMatrix () {
      array = new int[0];
      msize = 0;
    }

    virtual ~ArrayMatrix () { delete[] array; }

    // ACCESS ------------------------------------------------------------------

    int get (int o, int p) const {
      return array[o*msize + p]; 
    }

    int& elem (int o, int p) { 
      return array[o*msize + p]; 
    }
    
    // METHODS -----------------------------------------------------------------

    //    list< int > erase (int n) { return list< int> (); }

    int connect (int o, int p, int e) {
      if (o>=size() || p>=size()) resize (max (o+1, p+1));
      
      elem (o, p) = e;
      return e;
    }

    int disconnect (int o, int p) { 
      int e = elem (o, p);
      elem (o, p) = -1;

      for (int i=0; i<size ()*size (); ++i) {
	if (array[i] > e) array[i]--;
      }      

      return 0; 
    }

    void resize (int s) {
      if (s <= size ()) return;
      delete[] array;
      msize = s;
      array = new int[size ()*size ()];
      for (int i=0; i<size ()*size (); ++i) array[i] = -1;
    }

    int size () const { return msize; }

    void clear () { 
      delete[] array; 
      array = new int[0]; 
      msize = 0;
    }

    list< int > neighbors (int n) const {
      list< int > l;
      for (int i=0; i<size (); ++i) 
	if (get (n, i) != -1) l.push_back (i);
      return l;
    }
  };





  /**
   * Implementation of an adjacency matrix using a map of maps.
   *
   * @author Patrick Gendron (gendrop@iro.umontreal.ca)
   */
  class MapMatrix : public AdjacencyMatrix 
  {
  public:
    map< int, map< int, int > > array;
    
    // LIFECYCLE ---------------------------------------------------------------

  public:
    
    MapMatrix () {}
    
    virtual ~MapMatrix () { array.clear (); }


    // ACCESS ------------------------------------------------------------------

    int get (int o, int p) const {
      map< int, map< int, int > >::const_iterator row;
      map< int, int >::const_iterator col;
      if ((row = array.find (o)) == array.end ()) return -1;
      if ((col = row->second.find (p)) == row->second.end ()) return -1;
      return col->second;
    }

    int& elem (int o, int p) { 
      return array[o][p];
    }   

    // METHODS -----------------------------------------------------------------

//     list< int > erase (int n) { 
//       list< int > l;
//       map< int, map< int, int > >::iterator i;
//       map< int, int >::iterator j;

//       i = array.find (n);
      
//       for (j=i->second.begin (); j!=i->second.end (); ++j) {
// 	l.push_back (j->second);
//       }
//       array.erase (i);

//       for (i=array.begin (); i!=array.end (); ++i) {
// 	for (j=i->second.begin (); j!=i->second.end (); ++j) {
// 	  if (j->first == n) {
// 	    l.push_back (j->second);
// 	  }
// 	}
// 	i->second.erase (n);
//       }

//       return l; 
//     }

    int connect (int o, int p, int e) {
      if (o>=size() || p>=size()) resize (max (o+1, p+1));
      
      elem (o, p) = e;
      return e; 
    }
    
    int disconnect (int o, int p) { 
      int e = elem (o, p);
      elem (o, p) = -1;

      map< int, map< int, int > >::iterator i;
      map< int, int >::iterator j;

      for (i=array.begin (); i!=array.end (); ++i) {
	for (j=i->second.begin (); j!=i->second.end (); ++j) {
	  if (j->second > e) j->second--;
	}
      }

      return e; 
    }

    void resize (int s) {
      int current_size = size ();

      if (s <= current_size) return;

      while (s-->current_size) {
	array[s] = map< int, int > ();
      }
    }

    int size () const { return array.size (); }

    void clear () { array.clear (); }

    list< int > neighbors (int n) const {
      list< int > l;
      map< int, map< int, int > >::const_iterator i;
      map< int, int >::const_iterator j;

      i = array.find (n);
      for (j=i->second.begin (); j!=i->second.end (); ++j) {
	l.push_back (j->first);
      }
      return l;
    }

  };

}


#endif
