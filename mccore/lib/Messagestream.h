//                              -*- Mode: C++ -*- 
// Messagestream.h
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Sep  5 17:06:24 2001
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Oct 16 17:55:20 2003
// Update Count     : 19
// Status           : Unknown.
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


#ifndef _Messagestream_h_
#define _Messagestream_h_


#include <iostream>

using namespace std;

class Messagestream;


extern Messagestream &gOut;


/**
 * @short Interface for output messages.
 *
 * Levels of verbose range from 0 to MAXINT, 0 being the most crucial.
 * When setting the verbose level to x, only messages of priority
 * inferior or equal to x will be printed.
 * 
 * 0 : Program output
 * 1 : Program errors
 * 2 : Library errors
 * 3 : verbose
 * 4 : very verbose
 * 5 : debug
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class Messagestream : public ostream
{
  
protected:
  
  /**
   * The verbose level of the Messagestream object.
   */
  unsigned int verboseLevel;

  /**
   * The verbose level of the last entered message.
   */
  unsigned int currentVerboseLevel;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  Messagestream () 
    : ostream (cout.rdbuf ()), verboseLevel (2), currentVerboseLevel (2) { }

  /**
   * Initializes the message system with verbose levels.
   * @param buf the streambuf of the output stream.
   * @param level the verbose level.
   * @param clevel the level of messages.
   */
  Messagestream (streambuf *buf, unsigned int level, unsigned int clevel)
    : ostream (buf), verboseLevel (level), currentVerboseLevel (clevel) { }

  /**
   * Destructs the object.
   */
  virtual ~Messagestream () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Changes the verbose level of the future entered messages.
   * @param level the new current verbose level.
   * @return itself.
   */
  Messagestream& operator() (unsigned int level)
  {
    currentVerboseLevel = level;
    return *this;
  }

  /**
   * Writes a character to the Message stream.
   * @param c the character to write.
   * @return itself.
   */
  Messagestream& operator<< (char c)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << c;
    return *this;
  }

  /**
   * Writes a unsigned char to the Message stream.
   * @param c the unsigned char to write.
   * @return itself.
   */
  Messagestream& operator<< (unsigned char c) { return operator<< ((char)c); }

  /**
   * Writes a signed char to the Message stream.
   * @param c the signed char to write.
   * @return itself.
   */
  Messagestream& operator<< (signed char c) { return operator<< ((char)c); }

  /**
   * Writes a string to the Message stream.
   * @param s the string to write.
   * @return itself.
   */
  Messagestream& operator<< (const char *s)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << s;
    return *this;
  }

  /**
   * Writes an unsigned string to the Message stream.
   * @param s the unsigned string to write.
   * @return itself.
   */
  Messagestream& operator<< (const unsigned char *s)
  { return operator<< ((const char*)s); }

  /**
   * Writes a signed string to the Message stream.
   * @param s the signed string to write.
   * @return itself.
   */
  Messagestream& operator<< (const signed char *s)
  { return operator<< ((const char*)s); }

  /**
   * Writes an integer to the Message stream.
   * @param n the integer to write.
   * @return itself.
   */
  Messagestream& operator<< (int n)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << n;
    return *this;
  }

  /**
   * Writes an unsigned integer to the Message stream.
   * @param n the unsigned integer to write.
   * @return itself.
   */
  Messagestream& operator<< (unsigned int n)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << n;
    return *this;
  }

  /**
   * Writes a long integer to the Message stream.
   * @param n the long integer to write.
   * @return itself.
   */
  Messagestream& operator<< (long n)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << n;
    return *this;
  }

  /**
   * Writes an unsigned long integer to the Message stream.
   * @param n the unsigned long integer to write.
   * @return itself.
   */
  Messagestream& operator<<(unsigned long n)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << n;
    return *this;
  }

  /**
   * Writes a double real to the Message stream.
   * @param n the double real to write.
   * @return itself.
   */
  Messagestream& operator<< (double n)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << n;
    return *this;
  }

  /**
   * Writes a float to the Message stream.
   * @param n the float to write.
   * @return itself.
   */
  Messagestream& operator<< (float n) { return operator<< ((double)n); }

  /**
   * Writes a long double to the Message stream.
   * @param n the long double to write.
   * @return itself.
   */
  Messagestream& operator<< (long double n) { return operator<< ((double)n); }

  /**
   * Writes an object to the Message stream.
   * @param n the long double to write.
   * @return itself.
   */
  template< class _Object >
  Messagestream& operator<< (const _Object &obj)
  {
    if (currentVerboseLevel <= verboseLevel)
      *(ostream*)this << obj;
    return *this;
  }
  
  /**
   * Modifies the Message stream.
   * @param func the ios manipulator function.
   * @return itself.
   */
  Messagestream& operator<< (ios& (*func)(ios&))
  {
    if (currentVerboseLevel <= verboseLevel)
      (*func)(*(ostream*)this);
    return *this;
  }

  /**
   * Modifies the Message stream.
   * @param func the ostream manipulator function.
   * @return itself.
   */
  Messagestream& operator<< (ostream& (*func)(ostream&))
  {
    if (currentVerboseLevel <= verboseLevel)
      (*func)(*(ostream*)this);
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  /**
   * Sets the verbose level of the message queue.
   * @param level the new verbose level.
   */
  void setVerboseLevel (unsigned int level) { verboseLevel = level; }

  unsigned int getVerboseLevel () { return verboseLevel; }

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------
};




/**
 * @short Text implementation of Messages.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class oMessagestream : public Messagestream
{

protected:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.  It must not be used.
   */
  oMessagestream () { }

public:

  /**
   * Initializes the message system with a ostream and an initial verbose
   * level.
   * @param os the output stream.
   * @param level the initial verbose level.
   */
  oMessagestream (ostream &os, unsigned int level)
    : Messagestream (os.rdbuf (), level, level) { }
  
  /**
   * Destructs the object.
   */
  virtual ~oMessagestream () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------
};


#endif
