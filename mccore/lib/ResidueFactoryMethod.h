//                              -*- Mode: C++ -*- 
// ResidueFactoryMethod.h
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct 12 14:31:19 2001
// $Revision: 1.1.12.1 $
// $Id: ResidueFactoryMethod.h,v 1.1.12.1 2003-11-26 17:00:15 larosem Exp $
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


#ifndef _ResidueFactoryMethod_h_
#define _ResidueFactoryMethod_h_

class AbstractResidue;



/**
 * @short Abstract class for residue factory methods.
 *
 * This class is used in Model to generate a given type of residue on input
 * methods.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class ResidueFactoryMethod
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  ResidueFactoryMethod () { }

  /**
   * Copies the object.
   */
  virtual ResidueFactoryMethod* clone () const = 0;
  
  /**
   * Destroys the object.
   */
  virtual ~ResidueFactoryMethod () { }

  // OPERATORS ------------------------------------------------------------

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------

  /**
   * Creates the residue.
   * @return the newly created empty residue.
   */
  virtual AbstractResidue* createResidue () const = 0;

};

#endif
