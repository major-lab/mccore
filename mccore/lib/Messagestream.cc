//                              -*- Mode: C++ -*- 
// Messagestream.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Jul  9 11:25:19 2003
// $Revision: 1.3 $
// $Id: Messagestream.cc,v 1.3 2003-12-23 14:50:08 larosem Exp $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Messagestream.h"



oMessagestream out (cout, 2);
Messagestream &gOut = out;

oMessagestream err (cerr, 2);
Messagestream &gErr = err;
