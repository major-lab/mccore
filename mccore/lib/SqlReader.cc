//                              -*- Mode: C++ -*- 
// SqlReader.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Anita Boisgontier
// Created On       : 
// $Revision: 1.1.2.1 $
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

#include <cstring>
#include <cerrno>
#include <string>

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



namespace mccore
{

  RnasqlReader::RnasqlReader (const char *name, ResidueFactoryMethod *fm)
  : name(name), residueFM (fm), con(use_exceptions)
  {
    if (0 == fm) residueFM = new ExtendedResidueFM ();
  }

  
  RnasqlReader::~RnasqlReader ()
  {
    delete residueFM;
  }

  
  Molecule*
  RnasqlReader::read()
  {
    con.connect("database", "alpaga", "mccore", "mccoreweb");
    Molecule *molecule;
    molecule= new Molecule();
    int num_Mol=0;

    Query queryMol = con.query();
    queryMol << "SELECT Molecule.id as num_M, keyH, valueH FROM Molecule LEFT JOIN MoleculeHeader ON Molecule.id=MoleculeHeader.id_Molecule WHERE Molecule.nom=\"" << name << "\"";  
//cout << "QueryMol: " << queryMol.preview() << endl;
    Result resMol = queryMol.store();
    Result::iterator imol;
    for (imol = resMol.begin(); imol != resMol.end(); imol++)
    {
      Row rowMol = *imol;
      string key;
      string value;

      key = rowMol["keyH"];
      value = rowMol["valueH"];
      molecule->setProperty (key, value);
      num_Mol = rowMol["num_M"];
    }

    Query queryMod = con.query();
    queryMod << "SELECT id FROM Model WHERE id_Molecule=\"" << num_Mol << "\"";
//cout << "QueryMod: " << queryMod.preview() << endl;
    Result resMod = queryMod.store();
    Result::iterator imod;
    for (imod = resMod.begin(); imod != resMod.end(); imod++)
    {
      Row rowMod = *imod;
      AbstractModel *model;

      model = toMccoreMod(rowMod["id"]);
      molecule->insert (*model);
      delete model;
    }
    return molecule;
  }


  Model*
  RnasqlReader::toMccoreMod (int num_Mod)
  {
    Model *m;
    m = new Model ();

      Query queryRes = con.query();
      queryRes << "SELECT Residue.id as id, chain, number, insertion, type FROM Residue LEFT JOIN ResId ON ResId.id=Residue.id_ResId LEFT JOIN ResidueType ON ResidueType.id=Residue.id_ResidueType WHERE id_Model=\"" << num_Mod << "\"";
//cout << "QueryRes: " << queryRes.preview() << endl << endl;
      Result resRes = queryRes.store();
      Result::iterator ires;
      for (ires = resRes.begin(); ires != resRes.end(); ires++)
      {
        Residue *r;
        Row rowRes = *ires;
        ResId id;
	string type;
        int no;

        r = residueFM->createResidue ();
        id.setChainId (rowRes["chain"]);
        no = rowRes["number"];
        id.setResNo (no);
        id.setInsertionCode (rowRes["insertion"]);
        r->setResId (id);
        type = rowRes["type"];
        r->setType (ResidueType::parseType (type));

        Query queryAt = con.query();
        queryAt << "SELECT Atom.id as id, x,y,z,type FROM Atom LEFT JOIN Vector3D ON Atom.id_Vector3D=Vector3D.id LEFT JOIN AtomType ON Atom.id_AtomType=AtomType.id WHERE Atom.id_Residue=\"" << rowRes["id"] << "\"";
//cout << "QueryAt: " << queryAt.preview() << endl;
        Result resAt = queryAt.store();
        Result::iterator iat;
        for (iat = resAt.begin(); iat != resAt.end(); iat++)
        {
          mccore::Atom *a;
          a = new mccore::Atom ();
          Row rowAt = *iat;
	  
          type = rowAt["type"];
          a->setAll (rowAt["x"], rowAt["y"], rowAt["z"], AtomType::parseType (type)); 
          r->insert (*a);
          delete a;
        }
        r->finalize ();
        m->insert (*r);
        delete r;
      }
    return m;
  }
/*
  Residue*
  RnasqlReader::toMccoreRes (int id_Res, int id_ResidueType)
  {
    Residue *r;
    ResId id;
    char *type;
    const char *str;
    int no, ic;

    r = residueFM->createResidue ();
    Query queryResId = con.query();
    queryResId << "SELECT * from ResId where id=\"" << id_Res << "\"";
    Result resResId = queryResId.store();
    Row rowResId = resResId[0];
    str=rowResId["chain"].c_str();
    id.setChainId (str[0]);
    no=rowResId["number"];
    id.setResNo (no);
    ic=rowResId["insertion"];
    id.setInsertionCode (ic);
    r->setResId (id);

    Query queryRT = con.query();
    queryRT << "SELECT type from ResidueType where id=\"" << id_ResidueType << "\"";
    Result resRT = queryRT.store();
    Row rowRT = resRT[0];
    type = new char[strlen (rowRT["type"]) + 1];
    strcpy (type, rowRT["type"]);
    r->setType (ResidueType::parseType (type));

    Query queryAt = con.query();
    queryAt << "SELECT Atom.id as id, x,y,z,type FROM Atom LEFT JOIN Vector3D ON Atom.id_Vector3D=Vector3D.id LEFT JOIN AtomType ON Atom.id_AtomType=AtomType.id WHERE Atom.id_Residue=\"" << id_Res << "\"";
    //queryAt << "SELECT * FROM Atom WHERE id_Residue=\"" << id_Res << "\"";
    Result resAt = queryAt.store();
    Result::iterator iat;
    for (iat = resAt.begin(); iat != resAt.end(); iat++)
    {
      mccore::Atom *a;
      a = new mccore::Atom ();
      Row rowAt = *iat;
      type = new char[strlen (rowAt["type"]) + 1];
      //a = toMccoreAt (rowAt["id"], rowAt["id_AtomType"]);
      strcpy (type, rowAt["type"]);
      a->setAll (rowAt["x"], rowAt["y"], rowAt["z"], AtomType::parseType (type)); 
      r->insert (*a);
      delete a;
    }
    r->finalize ();
    return r;
  }

  mccore::Atom*
  RnasqlReader::toMccoreAt (int num_At, int id_AtomType)
  {
    mccore::Atom *a;
    char *type;
    
    a = new mccore::Atom ();
    Query queryAT = con.query();
    queryAT << "SELECT type from AtomType where id=\"" << id_AtomType << "\"";
    Result resAT = queryAT.store();
    Row rowAT = resAT[0];
    type = new char[strlen (rowAT["type"]) + 1];
    strcpy (type, rowAT["type"]);

    Query queryV = con.query();
    queryV << "SELECT * from Vector3D where id=\"" << num_At << "\"";
    Result resV = queryV.store();
    Row rowV = resV[0];
    a->setAll (rowV["x"], rowV["y"], rowV["z"], AtomType::parseType (type));
    return a;
  }
*/
}
