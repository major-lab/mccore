//                              -*- Mode: C++ -*- 
// SqlReader.h
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


#ifndef _mccore_SqlReader_h_
#define _mccore_SqlReader_h_

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
   * @version $Id: SqlReader.h,v 1.2 2005-01-03 23:08:26 larosem Exp $
   */
  class RnasqlReader
  {
    
  private:

    const char *name;
    ResidueFactoryMethod *residueFM;
    Connection con;
    RnasqlReader() {}
    
  public:
    
    RnasqlReader (const char *name, ResidueFactoryMethod *fm = 0);
    virtual ~RnasqlReader ();
    
  private:
    
    //mccore::Atom* toMccoreAt (int num_At, int id_AtomType);
    //Residue* toMccoreRes (int num_Res, int id_ResidueType);
    Model* toMccoreMod (int num_Mod);
    //Molecule* toMccoreO (string sm);

  public:

    Molecule* read ();
  };
}

#endif
