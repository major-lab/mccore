//                              -*- Mode: C++ -*- 
// Graph.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal
// Author           : Martin Larose
// Created On       : Fri Dec 10 00:05:19 2004
// $Revision: 1.12.2.1 $
// $Id: Graph.cc,v 1.12.2.1 2004-12-10 05:15:48 larosem Exp $
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

#include "Graph.h"


namespace mccore
{

  ostream&
  Graph::write (ostream& os) const
  {
    return os;
  }
}

namespace std
{
  using namespace mccore;

  ostream&
  operator<< (ostream& os, const Graph& obj)
  {
    return obj.write (os);
  }
}
