//                              -*- Mode: C++ -*- 
// Algo.cc
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Sebastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : Wed Feb 14 15:45:51 2001
// Last Modified By : Martin Larose
// Last Modified On : Wed Aug 29 14:30:49 2001
// Update Count     : 9
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include "Algo.h"



void
Algo_Inst ()
{
  vector< CResidue > vec;
  vector< pair< vector< CResidue >::iterator, vector< CResidue >::iterator > >
    res = Algo::ExtractContact_AABB (vec.begin (), vec.end (), 5.0);

  cout << res.size () << endl;
}
