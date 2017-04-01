//                              -*- Mode: C++ -*- 
// Messagestream.h
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Sep  5 17:06:24 2001
// $Revision: 1.13 $
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


#ifndef _mccore_Messagestream_h_
#define _mccore_Messagestream_h_


#include <iostream>

using namespace std;



namespace mccore
{
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
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Messagestream.h,v 1.13 2005-09-30 19:19:59 thibaup Exp $
   */
  class Messagestream : public ostream
  {
  
  protected:
  
    /**
     * The verbose level of the Messagestream object.
     */
    unsigned int verboseLevel;

    /**
     * Alias to the associated streambuf object.
     */
    streambuf* buf_alias;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Messagestream () 
      : ostream (cout.rdbuf ()), 
	verboseLevel (2), 
	buf_alias (cout.rdbuf ()) 
    { }

    /**
     * Initializes the message system with verbose levels.
     * @param buf the streambuf of the output stream.
     * @param level the verbose level.
     */
    Messagestream (streambuf *buf, unsigned int level)
      : ostream (buf), 
	verboseLevel (level), 
	buf_alias (buf) 
    { }

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
      this->rdbuf (level > this->verboseLevel ? 0 : this->buf_alias);
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
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Messagestream.h,v 1.13 2005-09-30 19:19:59 thibaup Exp $
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
      : Messagestream (os.rdbuf (), level) { }
  
    /**
     * Destructs the object.
     */
    virtual ~oMessagestream () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------
  };
  
  /**
   * Output stream.
   */
  extern oMessagestream gOut;

  /**
   * Error stream.
   */
  extern oMessagestream gErr;

}

#endif
