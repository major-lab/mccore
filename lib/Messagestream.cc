//                              -*- Mode: C++ -*- 
// Messagestream.cc
// Copyright � 2003-04 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al.
// Author           : Patrick Gendron
// Created On       : Wed Jul  9 11:25:19 2003
// $Revision: 1.4 $
// $Id: Messagestream.cc,v 1.4 2005-01-03 22:56:14 larosem Exp $
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


// cmake generated defines
#include <config.h>

#include "Messagestream.h"



namespace mccore
{
  
  oMessagestream gOut (cout, 2);

  oMessagestream gErr (cerr, 2);

}
