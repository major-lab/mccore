//                              -*- Mode: C++ -*- 
// Messagestream.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Wed Jul  9 11:25:19 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Wed Jul  9 11:44:34 2003
// Update Count     : 6
// Status           : Unknown.
// 

#include "Messagestream.h"

oMessagestream out (cerr, 2);
Messagestream &gOut = out;
