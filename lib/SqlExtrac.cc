//                              -*- Mode: C++ -*- 
// SqlExtrac.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Anita Boisgontier
// Created On       : 
// $Revision: 1.2 $
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

#include <string.h>
#include <errno.h>

#include "Atom.h"
#include "AtomType.h"
#include "Messagestream.h"
#include "Model.h"
#include "Molecule.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"
#include "ResidueType.h"
#include "SqlReader.h"
#include "SqlExtrac.h"



namespace mccore
{

  Molecule*
  sqlExtrac::read ()
  {
    con.connect ("database", "alpaga", "mccore", "mccoreweb");
    Molecule *molecule;
    molecule= new Molecule ();

    return molecule;
  }

  Model*
  sqlExtrac::toExtrac (int num_Mod)
  {
    Model *m;
    m = new Model ();

    return m;
  }
}
