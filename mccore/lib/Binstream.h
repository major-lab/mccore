//                         -*- Mode: C++ -*-
// Binstream.h
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@IRO.UMontreal.CA>
// Created On       : jeu 24 jun 1999 18:11:41 EDT
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:23 2000
// Update count     : 0
// Status           : Ok.
//


#ifndef _Binstream_h_
#define _Binstream_h_

#include <iostream.h>



/**
 * @short Input binary stream for database and cache input.
 *
 * I/O binary stream basically used for the MCSYM database and cache.  These
 * classes are defined to provide binary read and write on basic types with
 * the operators << and >> and to give the opportunity to create ways to
 * save user defined objets in binary format.  Basic types uses read and
 * write methods from istream and ostream.  Each new class that needs to be
 * saved in binary format must define operators << and >> on iBinstream and
 * oBinstream in their class implementation.
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
  iBinstream () { }

  // OPERATORS ------------------------------------------------------------
  
  /**
   * Inputs character from binary stream.  It is not handled by the
   * template, it is not needed to be translated to host endian.
   * @param c the character to output.
   * @return itself.
   */
  iBinstream& operator>> (char &c);

  /**
   * Inputs unsigned character from binary stream.  It is not handled by the
   * template, it is not needed to be translated to host endian.
   * @param c the character to output.
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
  iBinstream& operator>> (char* str);
  
  /**
   * Inputs known size unsigned strings from the binary stream.  To use with
   * care, the size of the input must be less than the size of the character
   * string given as parameter.
   * @param str the string to put the characters in.
   * @return itself.
   */
  iBinstream& operator>> (unsigned char* str)
  { return operator>> ((char*)str); }
  
  /**
   * Inputs unknown size strings from the binary stream.  This operator read
   * an integer from the stream representing the string size, allocate a
   * space to read in the string.
   * @param str the string address where the new string will placed.
   * @return itself.
   */
  iBinstream& operator>> (char** str);

  /**
   * Inputs unknown size unsigned strings from the binary stream.  This
   * operator read an integer from the stream representing the string size,
   * allocate a space to read in the string.
   * @param str the string address where the new string will placed.
   * @return itself.
   */
  iBinstream& operator>> (unsigned char** str)
  { return operator>> ((char**)str); }

  /**
   * Inputs integers from the binary stream.  Reads the integer with read
   * and converts it with ntohl.
   * @param n the integer to read.
   * @return itself.
   */
  iBinstream& operator>> (int &n);

  /**
   * Inputs unsigned integers from the binary stream.  Reads the integer
   * with read and converts it with ntohl.
   * @param n the integer to read.
   * @return itself.
   */
  iBinstream& operator>> (unsigned int &n) { return operator>> ((int&)n); }

  /**
   * Inputs floats from the binary stream.  Reads the float with read
   * and converts it with ntohl.
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
  void close () { }
  
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
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class oBinstream : public ostream
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.  Nothing to be done.
   */
  oBinstream () { }

  // OPERATORS ------------------------------------------------------------
  
  /**
   * Outputs characters.  Is not needed to be translated to network endian.
   * @param c the character to output.
   * @return itself.
   */
  oBinstream& operator<< (char c);
  
  /**
   * Outputs unsigned characters.  It is not needed to be translated to
   * network endian.
   * @param c the character to output.
   * @return itself.
   */
  oBinstream& operator<< (unsigned char c) { return operator<< ((char)c); }
  
  /**
   * Outputs strings.
   * @param str the string to output.
   * @return itself.
   */
  oBinstream& operator<< (const char* str);

  /**
   * Outputs unsigned strings.
   * @param str the string to output.
   * @return itself.
   */
  oBinstream& operator<< (const unsigned char* str)
  { return operator<< ((const char*)str); }

  /**
   * Outputs integers to binary stream.  We convert the integer to network
   * endian before writing it.
   * @param n the integer to ouput.
   * @return itself.
   */
  oBinstream& operator<< (int n);

  /**
   * Outputs unsigned integers to binary stream.  We convert the integer to
   * network endian before writing it.
   * @param n the integer to ouput.
   * @return itself.
   */
  oBinstream& operator<< (unsigned int n) { return operator<< ((int)n); }

  /**
   * Outputs floats to binary stream.  We convert the float to network
   * endian before writing it. 
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
  void close () { }
  
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
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class Binstream : public iBinstream, public oBinstream
{
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the stream.  Nothing to be done.
   */
  Binstream () { }

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
  void close () { }
  
  // I/O ------------------------------------------------------------------
};

#endif
