//                              -*- Mode: C++ -*- 
// Messagestream.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Jul  9 11:25:19 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Tue Oct 28 11:12:39 2003
// Update Count     : 10
// Status           : Unknown.
// 

#include "Messagestream.h"

oMessagestream out (cout, 2);
Messagestream &gOut = out;

oMessagestream err (cerr, 2);
Messagestream &gErr = err;
