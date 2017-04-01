//                              -*- Mode: C++ -*- 
// Fastastream.h
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Thu Jan 17 12:53:27 2002
// $Revision: 1.6 $
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


#ifndef _mccore_Fastastream_h_
#define _mccore_Fastastream_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

#include "zstream.h"

using namespace std;



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
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: Fastastream.h,v 1.6 2005-01-03 22:53:33 larosem Exp $
   */
  class iFastastream : public istream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    iFastastream () : istream (0) { }

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
    oFastastream () : ostream (0) { }

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
  class ifFastastream : public iFastastream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:

    /**
     * Initializes the object.
     */
    ifFastastream ()
      : iFastastream (),
	buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ifFastastream (const char *name, ios_base::openmode mode = ios_base::in)
      : iFastastream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
	this->setstate (ios::failbit);
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
  };


  /**
   * @short Implementation of Fasta output in regular files.
   * 
   * @author Patrick Gendron 
   */
  class ofFastastream : public oFastastream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:

    /**
     * Initializes the object.
     */
    ofFastastream ()
      : oFastastream (),
	buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ofFastastream (const char *name, ios_base::openmode mode = ios_base::out)
      : oFastastream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
  
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc)
    {
      if (! buf.open (name, mode | ios_base::out))
	this->setstate (ios::failbit);
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
  };


  /**
   * @short Implementation of Fasta input in compressed files.
   * 
   * @author Patrick Gendron 
   */
  class izfFastastream : public iFastastream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:

    /**
     * Initializes the stream.
     */
    izfFastastream ()
      : iFastastream (),
	buf ()
    {
      this->init (&buf);
    }
  
    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    izfFastastream (const char *name, ios_base::openmode mode = ios_base::in)
      : iFastastream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
	this->setstate (ios::failbit);
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
  };


  /**
   * @short Implementation of Fasta output in compressed files.
   * 
   * @author Patrick Gendron 
   */
  class ozfFastastream : public oFastastream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:
    /**
     * Initializes the stream.
     */
    ozfFastastream ()
      : oFastastream (),
	buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     * @param level the compression level (default Z_BEST_SPEED).
     */
    ozfFastastream (const char *name, ios_base::openmode mode = ios_base::out, int level = Z_BEST_SPEED)
      : oFastastream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode, level);
    }
  
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name.
     * @param name the file name.
     * @param mode the file mode.
     * @param level the compression level (default Z_BEST_SPEED).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc, int level = Z_BEST_SPEED)
    {
      if (! buf.open (name, mode | ios_base::out, level))
	this->setstate (ios::failbit);
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
  };
}

#endif
