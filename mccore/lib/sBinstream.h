//                              -*- Mode: C++ -*- 
// sBinstream.h
// Copyright © 2001, 2002 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:41 2001
// Last Modified By : Patrick Gendron
// Last Modified On : Mon Feb 25 11:37:09 2002
// Update Count     : 4
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

#ifndef _sBinstream_h_
#define _sBinstream_h_

#include "sockstream.h"
#include "Binstream.h"

typedef Sockstream sBinstream;
typedef iSockstream isBinstream;
typedef oSockstream osBinstream;

#endif
