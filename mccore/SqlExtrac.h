//                              -*- Mode: C++ -*- 
// SqlExtrac.h
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


#ifndef _mccore_SqlExtrac_h_
#define _mccore_SqlExtrac_h_

#include <vector>
#include <mysql++.hh>

using namespace std;



namespace mccore
{
  class Atom;
  class ResidueFactoryMethod;
  class Residue;
  class Model;
  class Molecule;


  
  /**
   * @author Anita Boisgontier (<a href="boisgona@iro.umontreal.ca">boisgona@iro.umontreal.ca</a>)
   * @version $Id: SqlExtrac.h,v 1.2 2005-01-03 23:08:01 larosem Exp $
   */
  class sqlExtrac
  {
    
  private:

    const char *name;
    ResidueFactoryMethod *residueFM;
    Connection con;
    sqlExtrac() {}
    
  public:
    
    sqlExtrac (const char *name) : name (name), con (use_exceptions) { }

    virtual ~sqlExtrac () { }
    
  private:
    
    Model* toExtrac (int num_Mod);

  public:

    Molecule* read ();
  };
}

#endif
