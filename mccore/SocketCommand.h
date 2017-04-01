//                              -*- Mode: C++ -*- 
// SocketCommand.h
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Aug 16 16:21:12 2001
// $Revision: 1.6 $
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


#ifndef _mccore_SocketCommand_h_
#define _mccore_SocketCommand_h_



namespace mccore
{
  /**
   * @short Abstract class for socket commands.
   * 
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: SocketCommand.h,v 1.6 2005-01-26 15:11:44 thibaup Exp $
   */
  class SocketCommand 
  {
  public:

    typedef int com_type;

    static const com_type NONE               =  0;

    static const com_type SEND_CHAR          =  1;
    static const com_type SEND_COM_TYPE      =  2;
    static const com_type SEND_FLOAT         =  3;
    static const com_type SEND_STRING        =  4;
    static const com_type SEND_POCOM_TYPE3D  =  5;
    static const com_type SEND_ATOM          =  6;
    static const com_type SEND_TRANSFO       =  7;
    static const com_type SEND_RESIDUE       =  8;
    static const com_type SEND_MODEL         =  9;
    static const com_type SEND_MOLECULE      = 10;

    static const com_type FETCH_CHAR         = 51;
    static const com_type FETCH_COM_TYPE     = 52;
    static const com_type FETCH_FLOAT        = 53;
    static const com_type FETCH_STRING       = 54;
    static const com_type FETCH_POCOM_TYPE3D = 55;
    static const com_type FETCH_ATOM         = 56;
    static const com_type FETCH_TRANSFO      = 57;
    static const com_type FETCH_RESIDUE      = 58;
    static const com_type FETCH_MODEL        = 59;
    static const com_type FETCH_MOLECULE     = 60;
  
    // LIFECYCLE ------------------------------------------------------------

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------
  };

}

#endif
