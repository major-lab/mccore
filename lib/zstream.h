// zstream.h
// Copyright © 2004, 2014 Laboratoire de Biologie Informatique et Theorique
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


#ifndef _mccore_zstream_h_
#define _mccore_zstream_h_

#include <iostream>
#include <zlib.h>

using namespace std;


namespace mccore
{

  /**
   * @short Implementation of compressed file buffer.
   *
   * This implementation of buffer suits for compressed streams.
   */
  class zstreambuf : public streambuf
  {
    /**
     * The compressed file pointer used in gzread, gzwrite, etc.
     */
    gzFile file;

    /**
     * The size of the input/output buffer. 
     */
    static const int buf_size = 1024;

    /**
     * The size of the putback region.
     */ 
    static const int putback_size = 4;

    char buffer [buf_size+putback_size];

    /**
     * Indicate if the file is opened.
     */ 
    bool opened;

    /**
     * The open mode of the gzFile.
     */ 
    int _mode;

  public:

    zstreambuf ();

    ~zstreambuf();

    /**
     * Opens the compressed file buffer.
     * @param name the name of the file.
     * @param mode the open mode requested.
     * @param level the compression level (default Z_BEST_SPEED).
     * @return itself if the operation went successfull, 0 otherwise.
     */
    zstreambuf* open (const char* name, int mode, int level = Z_BEST_SPEED);

    /**
     * Closes the zipped files.  The buffer is first synched so that the
     * buffer is flushed to disk.
     * @return 0 if the operation is successfull, itself otherwise.
     */
    zstreambuf* close ();

    /**
     * Returns the state of the buffer.
     */
    bool is_open () { return opened; }

    /**
     * Takes care of overflow in write methods.  This is the main output method
     * in GCC 2.95, GCC3.0 and sgi CC.
     * @param c the character to put in the buffer.
     * @return 0 for success, -1 if EOF is reached.
     */
    virtual int overflow (int c = EOF);

    /**
     * Takes care of underflow in read methods.  This is the main input method
     * in GCC 2.95, GCC3.0 and sgi CC.
     * @return the upstream character.
     */
    virtual int underflow ();

    /**
     * Takes care of synchronizing the file by flushing the output buffer
     * when endl or flush are called
     * @return 0 if the sync succeeded, -1 if EOF is reached.
     */
    virtual int sync ();

  };


  /**
   * @short Simple compressed input stream.
   *
   * This is a simple stream that reads a compressed gzip file.
   */
  class izfstream : public istream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;

  public:

    /**
     * Initializes the stream.
     */
    izfstream () : istream (0), buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     */
    izfstream (const char *name, int mode = ios::in) : istream (0), buf ()
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
    void open (const char* name, int mode = ios::in)
    {
      if (! buf.open (name, mode | ios::in))
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
   * @short Simple compressed output stream.
   *
   * This is a simple stream that writes to a compressed gzip file.
   */
  class ozfstream : public ostream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;

  public:

    /**
     * Initializes the stream.
     */
    ozfstream () : ostream (0), buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with filename.
     * @param name the file name.
     * @param mode the file mode.
     * @param level the compression level (default Z_BEST_SPEED).
     */
    ozfstream (const char* name, int mode = ios::out, int level = Z_BEST_SPEED) : ostream (0), buf ()
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
    void open (const char* name, int mode = ios::out | ios::trunc, int level = Z_BEST_SPEED)
    {
      if (! buf.open (name, mode | ios::out, level))
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
