//                              -*- Mode: C++ -*- 
// SocketCommand.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Aug 16 16:21:12 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 16 19:15:33 2001
// Update Count     : 2
// Status           : Unknown.
// 


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
