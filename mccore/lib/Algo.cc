//                              -*- Mode: C++ -*- 
// Algo.cc
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sebastien Lemieux
// Created On       : Wed Feb 14 15:45:51 2001
// Last Modified By : Sebastien Lemieux
// Last Modified On : Wed Feb 14 15:55:50 2001
// Update Count     : 4
// Status           : Unknown.
// 

#include <iostream.h>
#include "Algo.h"

void Algo_Inst () {
  vector< CResidue > vec;
  vector< pair< vector< CResidue >::iterator, vector< CResidue >::iterator > >
    res = Algo::ExtractContact_AABB (vec.begin (), vec.end (), 5.0);
  cout << res.size () << endl;
}
