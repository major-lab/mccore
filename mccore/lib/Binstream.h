//                         -*- Mode: C++ -*-
// Binstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:11:41 EDT
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Mar 27 11:12:42 2003
// Update count     : 0
// Status           : Ok.
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


#ifndef _Binstream_h_
#define _Binstream_h_

#include <iostream>

using namespace std;

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
  iBinstream () : istream (cin.rdbuf ()) { }

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
  oBinstream () : ostream (cout.rdbuf ()) { }

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

#endif
