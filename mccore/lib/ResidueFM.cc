//                              -*- Mode: C++ -*- 
// ResidueFM.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct 12 14:46:02 2001
// $Revision: 1.1.8.1 $
// $Id: ResidueFM.cc,v 1.1.8.1 2003-12-10 14:19:04 larosem Exp $
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

#include "CResId.h"
#include "Residue.h"
#include "ResidueFM.h"
#include "ResidueType.h"



AbstractResidue*
ResidueFM::createResidue () const
{
  return new Residue ();
}



AbstractResidue*
ResidueFM::createResidue (t_Residue *type, const vector< CAtom > &vec, const CResId &nId) const
{
  return new Residue (type, vec, nId);
}
