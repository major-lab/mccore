//                              -*- Mode: C++ -*- 
// fstreambase.h
// Copyright © 2002-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Fri Jan 25 15:17:28 2002
// $Revision: 1.1.4.1 $
// $Id: fstreambase.h,v 1.1.4.1 2003-12-10 14:20:24 larosem Exp $
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


#ifndef _fstreambase_h_
#define _fstreambase_h_

#include <fstream>

using namespace std;



// We want to keep the version that's implemented in the libstdc++ 
// when available...
#ifndef HAVE_FSTREAMBASE
#include <iostream>



/**
 * @short Implementation of base class for file i/o streams.
 *
 * This is an implementation of fstreambase for systems that do not
 * implement it.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class fstreambase : virtual public ios 
{
protected:

  /**
   * The stream buffer.
   */
  mutable filebuf buf;

public:

  /**
   * Initializes the stream.
   */
  fstreambase () { init (&buf); }

  /**
   * Initializes the stream with a filename.
   * @param name the file name.
   * @param mode the file mode.
   */
  fstreambase (const char* name, int mode) {
    init (&buf);
    open (name, mode);
  }

  /**
   * Destroys the stream by calling close on it.
   */
  ~fstreambase ()
  {
    close ();
  }

  /**
   * Opens the stream with a file name.
   * @param name the file name.
   * @param mode the file mode.
   */
  void open (const char* name, int mode)
  {
    clear ();
    if (!buf.open (name, (ios::openmode)mode))
      clear (ios::badbit);
  }

  /**
   * Closes the stream.
   */
  void close ()
  {
    if (buf.is_open ())
      if (!buf.close ())
	clear (ios::badbit);
  }

  /**
   * Tests if the stream is open.
   */
  operator bool () { return good (); }

  /**
   * Gets the buffer.
   * @return the file buffer object.
   */
  filebuf* rdbuf () const { return &buf; }
};

#endif
#endif
