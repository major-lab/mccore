//                         -*- Mode: C++ -*-
// Binstream.h
// Copyright © 1999, 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:11:41 EDT
// $Revision: 1.14 $
// $Id: Binstream.h,v 1.14 2004-01-09 21:15:13 larosem Exp $
//
//  This file is part of mccore.
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


#ifndef _Binstream_h_
#define _Binstream_h_

#include <iostream>
#include <fstream>
#include <zlib.h>

#include "zstream.h"

using namespace std;



namespace mccore {
  /**
   * @short Input binary stream for database and cache input.
   *
   * I/O binary stream.  These classes are defined to provide binary
   * read and write on basic types with the operators << and >> and to
   * give the opportunity to create ways to save user defined objets in
   * binary format.  Basic types uses read and write methods from
   * istream and ostream.  Each new class that needs to be saved in
   * binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca> 
   */
  class iBinstream : public istream
  {
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.  Nothing to be done.
     */
    iBinstream () : istream (0) { }
    
    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    iBinstream (streambuf *sb) : istream (sb) { }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Inputs character from binary stream.
     * @param c the character to input.
     * @return itself.
     */
    iBinstream& operator>> (char &c);
    
    /**
     * Inputs unsigned character from binary stream.
     * @param c the character to intput.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char &c) { return operator>> ((char&)c); }
    
    /**
     * Inputs known size strings from the binary stream.  To use with care,
     * the size of the input must be less than the size of the character
     * string given as parameter.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (char *str);
    
    /**
     * Inputs known size unsigned strings from the binary stream.  To use with
     * care, the size of the input must be less than the size of the character
     * string given as parameter.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char *str)
    { return operator>> ((char*)str); }
    
    /**
     * Inputs unknown size strings from the binary stream.  This operator read
     * an integer from the stream representing the string size, allocate a
     * space to read in the string.
     * @param str the string address where the new string will placed.
     * @return itself.
     */
    iBinstream& operator>> (char **str);
    
    /**
     * Inputs unknown size unsigned strings from the binary stream.  This
     * operator read an integer from the stream representing the string size,
     * allocate a space to read in the string.
     * @param str the string address where the new string will placed.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char **str)
    { return operator>> ((char**)str); }
    
    /**
     * Inputs booleans from the binary stream.
     * @param b the boolean to read.
     * @return itself.
     */
    iBinstream& operator>> (bool &b) { return operator>> ((char&)b); }
    
    /**
     * Inputs short integers from the binary stream.
     * @param n the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (short int &n);
    
    /**
     * Inputs integers from the binary stream.
     * @param n the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (int &n);
    
    /**
     * Inputs unsigned integers from the binary stream.
     * @param n the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned int &n) { return operator>> ((int&)n); }
    
    /**
     * Inputs long integers from the binary stream.
     * @param n the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (long int &n);
    
    /**
     * Inputs unsigned long integers from the binary stream.
     * @param n the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned long int &n) { return operator>> ((long int&)n); }
    
    /**
     * Inputs floats from the binary stream.
     * @param x the float to read.
     * @return itself.
     */
    iBinstream& operator>> (float &x);
    
    /**
     * Inputs ios manipulation functions.
     * @param f is the ios manip fuction.
     * @return itself.
     */
    iBinstream& operator>> (ios& (*f)(ios&));
    
    /**
     * Inputs istream manipulation functions.
     * @param f is the istream manip function.
     * @return itself.
     */
    iBinstream& operator>> (istream& (*f)(istream&));
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
    /**
     * Opens the stream.
     */
    void open () { }
    
    /**
     * Closes the stream.
     */
    virtual void close () { }
    
    // I/O ------------------------------------------------------------------
  };
  
  
  
  /**
   * @short Output binary stream for database and cache output.
   *
   * I/O binary stream basically used for the MCSYM database and cache.  These
   * classes are defined to provide binary read and write on basic types with
   * the operators << and >> and to give the opportunity to create ways to
   * save user defined objets in binary format.  Basic types uses read and
   * write methods from istream and ostream.  Each new class that needs to be
   * saved in binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class oBinstream : public ostream
  {
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.  Nothing to be done.
     */
    oBinstream () : ostream (0) { }
    
    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    oBinstream (streambuf *sb) : ostream (sb) { }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Outputs characters (htons is used since Java uses 16 bit long chars
     * and we cannot suppose that chars have 8 bit...)
     * @param c the character to output.
     * @return itself.
     */
    oBinstream& operator<< (char c);
    
    /**
     * Outputs unsigned characters.
     * @param c the character to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned char c) { return operator<< ((char)c); }
    
    /**
     * Outputs strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const char *str);
    
    /**
     * Outputs unsigned strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const unsigned char *str)
    { 
      return operator<< ((const char*)str); 
    }
    
    /**
     * Outputs booleans to binary stream.
     * @param b the boolean to ouput.
     * @return itself.
     */
    oBinstream& operator<< (bool b) { return operator<< ((char)b); }
    
    /**
     * Outputs short integers to binary stream.
     * @param n the integer to ouput.
     * @return itself.
     */
    oBinstream& operator<< (short int n);
    
    /**
     * Outputs integers to binary stream.
     * @param n the integer to ouput.
     * @return itself.
     */
    oBinstream& operator<< (int n);
    
    /**
     * Outputs unsigned integers to binary stream.
     * @param n the integer to ouput.
     * @return itself.
     */
    oBinstream& operator<< (unsigned int n) { return operator<< ((int)n); }
    
    /**
     * Outputs long integers to binary stream.
     * @param n the integer to ouput.
     * @return itself.
     */
    oBinstream& operator<< (long int n);
    
    /**
     * Outputs unsigned integers to binary stream.
     * @param n the integer to ouput.
     * @return itself.
     */
    oBinstream& operator<< (unsigned long int n) { return operator<< ((long int)n); }
    
    /**
     * Outputs floats to binary stream.
     * @param x the float to ouput.
     * @return itself.
     */
    oBinstream& operator<< (float x);
    
    /**
     * Manipulates ios output.
     * @param func is the ios manip fuction.
     * @return itself.
     */
    oBinstream& operator<< (ios& (*func)(ios&));
    
    /**
     * Manipulates ostream output.
     * @param func is the ostream manip function.
     * @return itself.
     */
    oBinstream& operator<< (ostream& (*func)(ostream&));
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
    /**
     * Opens the stream.
     */
    void open () { }
    
    /**
     * Closes the stream.
     */
    virtual void close () { }
    
    // I/O ------------------------------------------------------------------
  };
  
  
  
  /**
   * @short General binary stream for database and cache I/O.
   *
   * I/O binary stream basically used for the MCSYM database and cache.  These
   * classes are defined to provide binary read and write on basic types with
   * the operators << and >> and to give the opportunity to create ways to
   * save user defined objets in binary format.  Basic types uses read and
   * write methods from istream and ostream.  Each new class that needs to be
   * saved in binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class Binstream : public iBinstream, public oBinstream
  {
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    Binstream () : iBinstream (), oBinstream () { }
    
    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    Binstream (streambuf *sb) : iBinstream (sb), oBinstream (sb) { }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
    /**
     * Opens the stream.
     */
    void open () { }
    
    /**
     * Closes the stream.
     */
    virtual void close () { }
    
    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Input binary file streams.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class ifBinstream : public iBinstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the objet.
     */
    ifBinstream ()
      : iBinstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    ifBinstream (const char *name, ios_base::openmode mode = ios_base::in)
      : iBinstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
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
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode))
	this->setstate (ios::failbit);
      iBinstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      iBinstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O ------------------------------------------------------------------
  };
  
  
  /**
   * @short Output binary file stream.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class ofBinstream : public oBinstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    ofBinstream ()
      : oBinstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out).
     */
    ofBinstream (const char *name, ios_base::openmode mode = ios_base::out)
      : oBinstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
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
     * Opens the stream with file name and optional mode and protection.
     * @param name the path and file name to open.
     * @param mode the open mode (default = ios_base::out).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc)
    {
      if (! buf.open (name, mode | ios_base::out))
	this->setstate (ios::failbit);
      oBinstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      oBinstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O ------------------------------------------------------------------
  };
  
  
  /**
   * @short General binary file stream.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class fBinstream : public Binstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    fBinstream ()
      : Binstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in | ios_base::out).
     */
    fBinstream (const char *name, ios_base::openmode mode = ios_base::in | ios_base::out)
      : Binstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
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
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in | ios_base::out).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in | ios_base::out)
    {
      if (! buf.open (name, mode))
	this->setstate (ios::failbit);
      Binstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    virtual void close ()
    {
      Binstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Compressed input binary stream.
   *
   * I/O general classes using the GNU zip compression system.  These streams
   * adds the compression on the normal binary streams.  The input stream can
   * read an uncompressed file.  When creating a output stream the programmer
   * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
   * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
   * of compression level 0 is not recommended: the data is not compressed but
   * a gzip dependent header an footer is added to the file.  It is preferable
   * to use the fBinstream classes for uncompressed output binary streams.
   * For further details see @ref iBinstream and @ref zfstreambase.  Note that
   * the compression level is not used in input streams.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class izfBinstream : public iBinstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    izfBinstream ()
      : iBinstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    izfBinstream(const char *name, ios_base::openmode mode = ios_base::in)
      : iBinstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
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
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
	this->setstate (ios::failbit);
      iBinstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      iBinstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O ------------------------------------------------------------------
  };
  
  
  /**
   * @short Compressed output binary stream.
   *
   * I/O general classes using the GNU zip compression system.  These streams
   * adds the compression on the normal binary streams.  The input stream can
   * read an uncompressed file.  When creating a output stream the programmer
   * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
   * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
   * of compression level 0 is not recommended: the data is not compressed but
   * a gzip dependent header an footer is added to the file.  It is preferable
   * to use the fBinstream classes for uncompressed output binary streams.
   * For further details see @ref oBinstream and @ref zfstreambase.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class ozfBinstream : public oBinstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    ozfBinstream ()
      : oBinstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out).
     * @param level the compression level for output.
     */
    ozfBinstream (const char *name, ios_base::openmode mode = ios_base::out, int level = Z_BEST_SPEED)
      : oBinstream (),
	buf()
    {
      this->init (&buf);
      this->open (name, mode, level);
    }
    
    // OPERATORS ------------------------------------------------------------
    
    // ACCESS ---------------------------------------------------------------
    
    // METHODS --------------------------------------------------------------
    
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
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out | ios_base::trunc).
     * @param level the compression level for output (default Z_BEST_SPEED).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc, int level = Z_BEST_SPEED)
    {
      if (! buf.open (name, mode | ios_base::out, level))
	this->setstate (ios::failbit);
      oBinstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      oBinstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O ------------------------------------------------------------------
  };
}
  
#endif
