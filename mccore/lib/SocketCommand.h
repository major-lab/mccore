//                              -*- Mode: C++ -*- 
// SocketCommand.h
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Aug 16 16:21:12 2001
// $Revision: 1.4 $
// $Id: SocketCommand.h,v 1.4 2003-12-23 14:58:09 larosem Exp $
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


#ifndef _SocketCommand_h_
#define _SocketCommand_h_



/**
 * @short Abstract class for socket commands.
 * 
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class SocketCommand 
{
public:

  static const int NONE         = 0;
  static const int SEND_CHAR    = 1;
  static const int SEND_INT     = 2;
  static const int SEND_FLOAT   = 3;
  static const int SEND_STRING  = 4;
  static const int SEND_POINT3D = 5;
  static const int SEND_ATOM    = 6;
  static const int SEND_TRANSFO = 7;
  static const int SEND_RESIDUE = 8;
  static const int SEND_MODEL   = 9;
  static const int FETCH_CHAR    = 51;
  static const int FETCH_INT     = 52;
  static const int FETCH_FLOAT   = 53;
  static const int FETCH_STRING  = 54;
  static const int FETCH_POINT3D = 55;
  static const int FETCH_ATOM    = 56;
  static const int FETCH_TRANSFO = 57;
  static const int FETCH_RESIDUE = 58;
  static const int FETCH_MODEL   = 59;
  
  // LIFECYCLE ------------------------------------------------------------

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------
};

#endif
