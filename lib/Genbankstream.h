// Genbankstream.h
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


#ifndef _mccore_Genbankstream_h_
#define _mccore_Genbankstream_h_

#include <iostream>
#include <fstream>
#include <vector>

#include "zstream.h"

using namespace std;


namespace mccore
{
  /**
   * @short Base class for input of Genbank formated streams
   */
  class iGenbankstream : public istream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    iGenbankstream () : istream (0) { }

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
   */
  class ifGenbankstream : public iGenbankstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;

  public:

    /**
     * Initializes the object.
     */
    ifGenbankstream ()
    : iGenbankstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    ifGenbankstream (const char *name, ios_base::openmode mode = ios_base::in)
    : iGenbankstream (),
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
   * @short Implementation of Genbank input in compressed files.
   */
  class izfGenbankstream : public iGenbankstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;

  public:

    /**
     * Initializes the stream.
     */
    izfGenbankstream ()
    : iGenbankstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    izfGenbankstream (const char *name, ios_base::openmode mode = ios_base::in)
    : iGenbankstream (),
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
}

#endif
