//                              -*- Mode: C++ -*- 
// GraphModel.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal
// Author           : Martin Larose
// Created On       : Wed Dec 29 00:44:53 2004
// $Revision: 1.1.2.2 $
// $Id: GraphModel.cc,v 1.1.2.2 2004-12-29 21:18:52 larosem Exp $
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

#include <iostream>

#include "GraphModel.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "stlio.h"

using namespace mccore;
using namespace std;



int
main (int argc, char *argv[])
{
  izfPdbstream ifs;
  GraphModel model;

  ifs.open ("1L8V.pdb.gz");
  ifs >> model;
  ifs.close ();

//   gOut (0) << model << endl;
  model.removeWater ();
  model.addHLP ();
  model.annotate ();
  gOut (0) << model << endl;
  return EXIT_SUCCESS;
}
  
  
    
