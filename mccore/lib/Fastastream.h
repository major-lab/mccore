//                              -*- Mode: C++ -*- 
// Fastastream.h
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Thu Jan 17 12:53:27 2002
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


#ifndef _Fastastream_h_
#define _Fastastream_h_

#include <iostream>
#include <fstream>
#include <vector>

#include "fstreambase.h"
#include "zfstream.h"

namespace mccore 
{
  /**
   * @short Base class for input of Fasta formated streams 
   * 
   * The Fasta format implemented here allows only one line of comment
   * prior to each sequence sections:
   *  "> ID Description"
   *  "ACGUGACUCGAGCCCG"
   * 
   * @author Patrick Gendron 
   */
  class iFastastream : public istream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    iFastastream () 
      : istream (cin.rdbuf ()) {}

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */ 
    iFastastream (streambuf *sb) : istream (sb) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Casts the fasta stream to a istream.
     * @return the istream.
     */
    operator istream* () { return dynamic_cast<istream*>(this); }

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Extracts the description line from a FASTA stream
     * @return a newly created string
     */
    char* getDescription ();

    /**
     * Extracts a sequence from a FASTA stream
     * @return a vector of char.
     */
    vector< char > getSequence ();

    // I/O  -----------------------------------------------------------------

  };



  /**
   * @short Base class for output of Fasta formated streams.
   * 
   * The Fasta format implemented here allows only one line of comment
   * prior to each sequence sections:
   *  "> ID Description"
   *  "ACGUGACUCGAGCCCG"
   * 
   * @author Patrick Gendron 
   */
  class oFastastream : public ostream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    oFastastream () : ostream (cout.rdbuf ()) { }

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    oFastastream (streambuf* sb) : ostream (sb) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Casts the fasta stream to a ostream.
     * @return the ostream.
     */
    operator ostream* () { return dynamic_cast<ostream*>(this); }

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Puts a description line on the stream
     */
    void putDescription (const char* desc);

    /**
     * Puts a sequence on the stream
     */
    void putSequence (const vector< char > &v);

  };


  /**
   * @short Implementation of Fasta input in regular files.
   * 
   * @author Patrick Gendron 
   */
  class ifFastastream : public iFastastream, public fstreambase
  {
  public:

    /**
     * Initializes the object.
     */
    ifFastastream () : iFastastream (rdbuf ()) { }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ifFastastream (const char *name, int mode = ios::in)
      : iFastastream (rdbuf ()), fstreambase (name, mode) { }

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
   * @short Implementation of Fasta output in regular files.
   * 
   * @author Patrick Gendron 
   */
  class ofFastastream : public oFastastream, public fstreambase
  {
  public:

    /**
     * Initializes the object.
     */
    ofFastastream () : oFastastream (rdbuf ()) { }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ofFastastream (const char *name, int mode = ios::out)
      : oFastastream (rdbuf ()), fstreambase (name, mode) { }
  
    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, int mode=ios::out)
    { fstreambase::open (name, mode); }

    /**
     * Gets the buffer.
     * @return the compressed file buffer object.
     */
    filebuf* rdbuf () { return fstreambase::rdbuf (); }
  };


  /**
   * @short Implementation of Fasta input in compressed files.
   * 
   * @author Patrick Gendron 
   */
  class izfFastastream : public iFastastream, public zfstreambase
  {
  public:

    /**
     * Initializes the stream.
     */
    izfFastastream () : iFastastream (rdbuf ()) { }
  
    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    izfFastastream (const char *name, int mode = ios::in)
      : iFastastream (&buf), zfstreambase (name, mode) { }

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


  /**
   * @short Implementation of Fasta output in compressed files.
   * 
   * @author Patrick Gendron 
   */
  class ozfFastastream : public oFastastream, public zfstreambase
  {
  public:
    /**
     * Initializes the stream.
     */
    ozfFastastream () : oFastastream (rdbuf ()) { }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ozfFastastream (const char *name, int mode = ios::out)
      : oFastastream (&buf), zfstreambase (name, mode) { }
  
    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, int mode=ios::out)
    { zfstreambase::open (name, mode); }

    /**
     * Gets the buffer.
     * @return the compressed file buffer object.
     */
    zfstreambuf* rdbuf () { return zfstreambase::rdbuf(); }
  };

}


#endif







