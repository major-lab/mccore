//                              -*- Mode: C++ -*- 
// Genbankstream.h
// Copyright © 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Tue Feb 12 14:40:55 2002
//
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _Genbankstream_h_
#define _Genbankstream_h_

#include <iostream>

#include <fstream>
#include <vector>

#include "fstreambase.h"
#include "zfstream.h"

namespace mccore 
{
  /**
   * @short Base class for input of Genbank formated streams
   *
   * Long Description
   *
   * @author Patrick Gendron
   */
  class iGenbankstream : public istream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    iGenbankstream ()
      : istream (cin.rdbuf ()) {}
  
    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */ 
    iGenbankstream (streambuf *sb) : istream (sb) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Casts the fasta stream to a istream.
     * @return the istream.
     */
    operator istream* () { return dynamic_cast<istream*>(this); }

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Extracts the description line from a Genbank stream
     * @return a newly created string
     */
    char* getDescription ();

    /**
     * Extracts a sequence from a Genbank stream
     * @return a vector of char.
     */
    vector< char > getSequence ();
  };


  /**
   * @short Implementation of Genbank input in regular files.
   * 
   * @author Patrick Gendron 
   */
  class ifGenbankstream : public fstreambase, public iGenbankstream
  {
  public:

    /**
     * Initializes the object.
     */
    ifGenbankstream ()
      : fstreambase (),
	iGenbankstream (rdbuf ())
    { }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ifGenbankstream (const char *name, int mode = ios::in)
      : fstreambase (),
	iGenbankstream (rdbuf ())
    {
      open (name, mode);
    }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, int mode=ios::in)
    { fstreambase::open (name, mode); }

    /**
     * Gets the buffer.
     * @return the compressed file buffer object.
     */
    filebuf* rdbuf() { return fstreambase::rdbuf (); }
  };


  /**
   * @short Implementation of Genbank input in compressed files.
   * 
   * @author Patrick Gendron 
   */
  class izfGenbankstream : public zfstreambase, public iGenbankstream
  {
  public:

    /**
     * Initializes the stream.
     */
    izfGenbankstream ()
      : zfstreambase (),
	iGenbankstream (rdbuf ())
    { }
  
    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    izfGenbankstream (const char *name, int mode = ios::in)
      : zfstreambase (),
	iGenbankstream (rdbuf ())
    {
      open (name, mode);
    }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, int mode=ios::in)
    { zfstreambase::open (name, mode); }

    /**
     * Gets the buffer.
     * @return the compressed file buffer object.
     */
    zfstreambuf* rdbuf() { return zfstreambase::rdbuf(); }
  };

}

#endif
