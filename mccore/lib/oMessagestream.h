//                              -*- Mode: C++ -*- 
// oMessagestream.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Sep  5 18:11:06 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Sep 20 12:46:09 2001
// Update Count     : 3
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


#ifndef _oMessagestream_h_
#define _oMessagestream_h_


#include "Messagestream.h"



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
