//                              -*- Mode: C++ -*- 
// TypeRepresentationTables.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct  1 14:45:13 2004
// $Revision: 1.4 $
// $Id: TypeRepresentationTables.cc,v 1.4 2004-12-09 19:53:34 thibaup Exp $
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

#include "AtomType.h"
#include "ResidueType.h"
#include "TypeRepresentationTables.h"



namespace mccore
{
  
  AmberAtomTypeRepresentationTable::AmberAtomTypeRepresentationTable ()
  {
    typeTable[""] = AtomType::aNull;
    typeTable["C"] = AtomType::aC;
    typeTable["H"] = AtomType::aH;
    typeTable["N"] = AtomType::aN;
    typeTable["P"] = AtomType::aP;
    typeTable["O"] = AtomType::aO;
    typeTable["MG"] = AtomType::aMG;
    typeTable["C1'"] = AtomType::aC1p;
    typeTable["C2'"] = AtomType::aC2p;
    typeTable["C3'"] = AtomType::aC3p;
    typeTable["C4'"] = AtomType::aC4p;
    typeTable["C5'"] = AtomType::aC5p;
    typeTable["H1'"] = AtomType::aH1p;
    typeTable["H2'"] = AtomType::aH2p;
    typeTable["H3'"] = AtomType::aH3p;
    typeTable["H4'"] = AtomType::aH4p;
    typeTable["H5'"] = AtomType::aH5p;
    typeTable["O1P"] = AtomType::aO1P;
    typeTable["O2'"] = AtomType::aO2p;
    typeTable["O2P"] = AtomType::aO2P;
    typeTable["O3'"] = AtomType::aO3p;
    typeTable["O3P"] = AtomType::aO3P;
    typeTable["O4'"] = AtomType::aO4p;
    typeTable["O5'"] = AtomType::aO5p;
    typeTable["H2'1"] = AtomType::a1H2p;
    typeTable["H5'1"] = AtomType::a1H5p;
    typeTable["H2'2"] = AtomType::a2H2p;
    typeTable["H5'2"] = AtomType::a2H5p;
    typeTable["HO'2"] = AtomType::aHO2p;
    typeTable["HO'3"] = AtomType::aHO3p;
    typeTable["C2"] = AtomType::aC2;
    typeTable["C4"] = AtomType::aC4;
    typeTable["C5"] = AtomType::aC5;
    typeTable["C7"] = AtomType::aC5M;
    typeTable["C6"] = AtomType::aC6;
    typeTable["C8"] = AtomType::aC8;
    typeTable["H1"] = AtomType::aH1;
    typeTable["H2"] = AtomType::aH2;
    typeTable["H3"] = AtomType::aH3;
    typeTable["H5"] = AtomType::aH5;
    typeTable["H6"] = AtomType::aH6;
    typeTable["H7"] = AtomType::aH7;
    typeTable["H8"] = AtomType::aH8;
    typeTable["N1"] = AtomType::aN1;
    typeTable["N2"] = AtomType::aN2;
    typeTable["N3"] = AtomType::aN3;
    typeTable["N4"] = AtomType::aN4;
    typeTable["N6"] = AtomType::aN6;
    typeTable["N7"] = AtomType::aN7;
    typeTable["N9"] = AtomType::aN9;
    typeTable["O2"] = AtomType::aO2;
    typeTable["O4"] = AtomType::aO4;
    typeTable["O6"] = AtomType::aO6;
    typeTable["H21"] = AtomType::a1H2;
    typeTable["H41"] = AtomType::a1H4;
    typeTable["H71"] = AtomType::a1H5M;
    typeTable["H61"] = AtomType::a1H6;
    typeTable["H22"] = AtomType::a2H2;
    typeTable["H42"] = AtomType::a2H4;
    typeTable["H72"] = AtomType::a2H5M;
    typeTable["H62"] = AtomType::a2H6;
    typeTable["H73"] = AtomType::a3H5M;
    typeTable["PSX"] = AtomType::aPSX;
    typeTable["PSY"] = AtomType::aPSY;
    typeTable["PSZ"] = AtomType::aPSZ;
    typeTable["LP1"] = AtomType::aLP1;
    typeTable["LP3"] = AtomType::aLP3;
    typeTable["LP7"] = AtomType::aLP7;
    typeTable["1LP2"] = AtomType::a1LP2;
    typeTable["1LP4"] = AtomType::a1LP4;
    typeTable["1LP6"] = AtomType::a1LP6;
    typeTable["2LP2"] = AtomType::a2LP2;
    typeTable["2LP4"] = AtomType::a2LP4;
    typeTable["2LP6"] = AtomType::a2LP6;
    typeTable["H3T"] = AtomType::aH3T;
    typeTable["H5T"] = AtomType::aH5T;
    typeTable["CA"] = AtomType::aCA;
    typeTable["CB"] = AtomType::aCB;
    typeTable["CD"] = AtomType::aCD;
    typeTable["CD1"] = AtomType::aCD1;
    typeTable["CD2"] = AtomType::aCD2;
    typeTable["CE"] = AtomType::aCE;
    typeTable["CE1"] = AtomType::aCE1;
    typeTable["CE2"] = AtomType::aCE2;
    typeTable["CE3"] = AtomType::aCE3;
    typeTable["CG"] = AtomType::aCG;
    typeTable["CG1"] = AtomType::aCG1;
    typeTable["CG2"] = AtomType::aCG2;
    typeTable["CH2"] = AtomType::aCH2;
    typeTable["CZ"] = AtomType::aCZ;
    typeTable["CZ2"] = AtomType::aCZ2;
    typeTable["CZ3"] = AtomType::aCZ3;
    typeTable["1H"] = AtomType::a1H;
    typeTable["2H"] = AtomType::a2H;
    typeTable["3H"] = AtomType::a3H;
    typeTable["HA"] = AtomType::aHA;
    typeTable["HA2"] = AtomType::aHA1;
    typeTable["HA3"] = AtomType::aHA2;
    typeTable["HB"] = AtomType::aHB;
    typeTable["HB1"] = AtomType::aHB1;
    typeTable["HB2"] = AtomType::aHB2;
    typeTable["HB3"] = AtomType::aHB3;
    typeTable["HD1"] = AtomType::aHD1;
    typeTable["HD2"] = AtomType::aHD2;
    typeTable["HE"] = AtomType::aHE;
    typeTable["HE1"] = AtomType::aHE1;
    typeTable["HE2"] = AtomType::aHE2;
    typeTable["HE3"] = AtomType::aHE3;
    typeTable["HG"] = AtomType::aHG;
    typeTable["HG1"] = AtomType::aHG1;
    typeTable["HG2"] = AtomType::aHG2;
    typeTable["HH"] = AtomType::aHH;
    typeTable["HH2"] = AtomType::aHH2;
    typeTable["HXT"] = AtomType::aHXT;
    typeTable["HZ"] = AtomType::aHZ;
    typeTable["HZ1"] = AtomType::aHZ1;
    typeTable["HZ2"] = AtomType::aHZ2;
    typeTable["HZ3"] = AtomType::aHZ3;
    typeTable["ND1"] = AtomType::aND1;
    typeTable["ND2"] = AtomType::aND2;
    typeTable["NE"] = AtomType::aNE;
    typeTable["NE1"] = AtomType::aNE1;
    typeTable["NE2"] = AtomType::aNE2;
    typeTable["NH1"] = AtomType::aNH1;
    typeTable["NH2"] = AtomType::aNH2;
    typeTable["NZ"] = AtomType::aNZ;
    typeTable["OD1"] = AtomType::aOD1;
    typeTable["OD2"] = AtomType::aOD2;
    typeTable["OE1"] = AtomType::aOE1;
    typeTable["OE2"] = AtomType::aOE2;
    typeTable["OG"] = AtomType::aOG;
    typeTable["OG1"] = AtomType::aOG1;
    typeTable["OH"] = AtomType::aOH;
    typeTable["OXT"] = AtomType::aOXT;
    typeTable["SD"] = AtomType::aSD;
    typeTable["SG"] = AtomType::aSG;
    typeTable["HD11"] = AtomType::a1HD1;
    typeTable["HD21"] = AtomType::a1HD2;
    typeTable["HE21"] = AtomType::a1HE2;
    typeTable["HG11"] = AtomType::a1HG1;
    typeTable["HG21"] = AtomType::a1HG2;
    typeTable["HH11"] = AtomType::a1HH1;
    typeTable["HH21"] = AtomType::a1HH2;
    typeTable["HD12"] = AtomType::a2HD1;
    typeTable["HD22"] = AtomType::a2HD2;
    typeTable["HE22"] = AtomType::a2HE2;
    typeTable["HG12"] = AtomType::a2HG1;
    typeTable["HG22"] = AtomType::a2HG2;
    typeTable["HH12"] = AtomType::a2HH1;
    typeTable["HH22"] = AtomType::a2HH2;
    typeTable["HD13"] = AtomType::a3HD1;
    typeTable["HD23"] = AtomType::a3HD2;
    typeTable["HG13"] = AtomType::a3HG1;
    typeTable["HG23"] = AtomType::a3HG2;
    typeTable["PSAZ"] = AtomType::aPSAZ;

    representationTable[AtomType::aNull] = "";
    representationTable[AtomType::aC] = "C";
    representationTable[AtomType::aH] = "H";
    representationTable[AtomType::aN] = "N";
    representationTable[AtomType::aP] = "P";
    representationTable[AtomType::aO] = "O";
    representationTable[AtomType::aMG] = "MG";
    representationTable[AtomType::aC1p] = "C1'";
    representationTable[AtomType::aC2p] = "C2'";
    representationTable[AtomType::aC3p] = "C3'";
    representationTable[AtomType::aC4p] = "C4'";
    representationTable[AtomType::aC5p] = "C5'";
    representationTable[AtomType::aH1p] = "H1'";
    representationTable[AtomType::aH2p] = "H2'";
    representationTable[AtomType::aH3p] = "H3'";
    representationTable[AtomType::aH4p] = "H4'";
    representationTable[AtomType::aH5p] = "H5'";
    representationTable[AtomType::aO1P] = "O1P";
    representationTable[AtomType::aO2p] = "O2'";
    representationTable[AtomType::aO2P] = "O2P";
    representationTable[AtomType::aO3p] = "O3'";
    representationTable[AtomType::aO3P] = "O3P";
    representationTable[AtomType::aO4p] = "O4'";
    representationTable[AtomType::aO5p] = "O5'";
    representationTable[AtomType::a1H2p] = "H2'1";
    representationTable[AtomType::a1H5p] = "H5'1";
    representationTable[AtomType::a2H2p] = "H2'2";
    representationTable[AtomType::a2H5p] = "H5'2";
    representationTable[AtomType::aHO2p] = "HO'2";
    representationTable[AtomType::aHO3p] = "HO'3";
    representationTable[AtomType::aC2] = "C2";
    representationTable[AtomType::aC4] = "C4";
    representationTable[AtomType::aC5] = "C5";
    representationTable[AtomType::aC5M] = "C7";
    representationTable[AtomType::aC6] = "C6";
    representationTable[AtomType::aC8] = "C8";
    representationTable[AtomType::aH1] = "H1";
    representationTable[AtomType::aH2] = "H2";
    representationTable[AtomType::aH3] = "H3";
    representationTable[AtomType::aH5] = "H5";
    representationTable[AtomType::aH6] = "H6";
    representationTable[AtomType::aH7] = "H7";
    representationTable[AtomType::aH8] = "H8";
    representationTable[AtomType::aN1] = "N1";
    representationTable[AtomType::aN2] = "N2";
    representationTable[AtomType::aN3] = "N3";
    representationTable[AtomType::aN4] = "N4";
    representationTable[AtomType::aN6] = "N6";
    representationTable[AtomType::aN7] = "N7";
    representationTable[AtomType::aN9] = "N9";
    representationTable[AtomType::aO2] = "O2";
    representationTable[AtomType::aO4] = "O4";
    representationTable[AtomType::aO6] = "O6";
    representationTable[AtomType::a1H2] = "H21";
    representationTable[AtomType::a1H4] = "H41";
    representationTable[AtomType::a1H5M] = "H71";
    representationTable[AtomType::a1H6] = "H61";
    representationTable[AtomType::a2H2] = "H22";
    representationTable[AtomType::a2H4] = "H42";
    representationTable[AtomType::a2H5M] = "H72";
    representationTable[AtomType::a2H6] = "H62";
    representationTable[AtomType::a3H5M] = "H73";
    representationTable[AtomType::aPSX] = "PSX";
    representationTable[AtomType::aPSY] = "PSY";
    representationTable[AtomType::aPSZ] = "PSZ";
    representationTable[AtomType::aLP1] = "LP1";
    representationTable[AtomType::aLP3] = "LP3";
    representationTable[AtomType::aLP7] = "LP7";
    representationTable[AtomType::a1LP2] = "1LP2";
    representationTable[AtomType::a1LP4] = "1LP4";
    representationTable[AtomType::a1LP6] = "1LP6";
    representationTable[AtomType::a2LP2] = "2LP2";
    representationTable[AtomType::a2LP4] = "2LP4";
    representationTable[AtomType::a2LP6] = "2LP6";
    representationTable[AtomType::aH3T] = "H3T";
    representationTable[AtomType::aH5T] = "H5T";
    representationTable[AtomType::aCA] = "CA";
    representationTable[AtomType::aCB] = "CB";
    representationTable[AtomType::aCD] = "CD";
    representationTable[AtomType::aCD1] = "CD1";
    representationTable[AtomType::aCD2] = "CD2";
    representationTable[AtomType::aCE] = "CE";
    representationTable[AtomType::aCE1] = "CE1";
    representationTable[AtomType::aCE2] = "CE2";
    representationTable[AtomType::aCE3] = "CE3";
    representationTable[AtomType::aCG] = "CG";
    representationTable[AtomType::aCG1] = "CG1";
    representationTable[AtomType::aCG2] = "CG2";
    representationTable[AtomType::aCH2] = "CH2";
    representationTable[AtomType::aCZ] = "CZ";
    representationTable[AtomType::aCZ2] = "CZ2";
    representationTable[AtomType::aCZ3] = "CZ3";
    representationTable[AtomType::a1H] = "1H";
    representationTable[AtomType::a2H] = "2H";
    representationTable[AtomType::a3H] = "3H";
    representationTable[AtomType::aHA] = "HA";
    representationTable[AtomType::aHA1] = "HA2";
    representationTable[AtomType::aHA2] = "HA3";
    representationTable[AtomType::aHB] = "HB";
    representationTable[AtomType::aHB1] = "HB1";
    representationTable[AtomType::aHB2] = "HB2";
    representationTable[AtomType::aHB3] = "HB3";
    representationTable[AtomType::aHD1] = "HD1";
    representationTable[AtomType::aHD2] = "HD2";
    representationTable[AtomType::aHE] = "HE";
    representationTable[AtomType::aHE1] = "HE1";
    representationTable[AtomType::aHE2] = "HE2";
    representationTable[AtomType::aHE3] = "HE3";
    representationTable[AtomType::aHG] = "HG";
    representationTable[AtomType::aHG1] = "HG1";
    representationTable[AtomType::aHG2] = "HG2";
    representationTable[AtomType::aHH] = "HH";
    representationTable[AtomType::aHH2] = "HH2";
    representationTable[AtomType::aHXT] = "HXT";
    representationTable[AtomType::aHZ] = "HZ";
    representationTable[AtomType::aHZ1] = "HZ1";
    representationTable[AtomType::aHZ2] = "HZ2";
    representationTable[AtomType::aHZ3] = "HZ3";
    representationTable[AtomType::aND1] = "ND1";
    representationTable[AtomType::aND2] = "ND2";
    representationTable[AtomType::aNE] = "NE";
    representationTable[AtomType::aNE1] = "NE1";
    representationTable[AtomType::aNE2] = "NE2";
    representationTable[AtomType::aNH1] = "NH1";
    representationTable[AtomType::aNH2] = "NH2";
    representationTable[AtomType::aNZ] = "NZ";
    representationTable[AtomType::aOD1] = "OD1";
    representationTable[AtomType::aOD2] = "OD2";
    representationTable[AtomType::aOE1] = "OE1";
    representationTable[AtomType::aOE2] = "OE2";
    representationTable[AtomType::aOG] = "OG";
    representationTable[AtomType::aOG1] = "OG1";
    representationTable[AtomType::aOH] = "OH";
    representationTable[AtomType::aOXT] = "OXT";
    representationTable[AtomType::aSD] = "SD";
    representationTable[AtomType::aSG] = "SG";
    representationTable[AtomType::a1HD1] = "HD11";
    representationTable[AtomType::a1HD2] = "HD21";
    representationTable[AtomType::a1HE2] = "HE21";
    representationTable[AtomType::a1HG1] = "HG11";
    representationTable[AtomType::a1HG2] = "HG21";
    representationTable[AtomType::a1HH1] = "HH11";
    representationTable[AtomType::a1HH2] = "HH21";
    representationTable[AtomType::a2HD1] = "HD12";
    representationTable[AtomType::a2HD2] = "HD22";
    representationTable[AtomType::a2HE2] = "HE22";
    representationTable[AtomType::a2HG1] = "HG12";
    representationTable[AtomType::a2HG2] = "HG22";
    representationTable[AtomType::a2HH1] = "HH12";
    representationTable[AtomType::a2HH2] = "HH22";
    representationTable[AtomType::a3HD1] = "HD13";
    representationTable[AtomType::a3HD2] = "HD23";
    representationTable[AtomType::a3HG1] = "HG13";
    representationTable[AtomType::a3HG2] = "HG23";
    representationTable[AtomType::aPSAZ] = "PSAZ";
  }


  PdbAtomTypeRepresentationTable::PdbAtomTypeRepresentationTable ()
  {
    typeTable[""] = AtomType::aNull;
    typeTable["C1*"] = AtomType::aC1p;
    typeTable["C2*"] = AtomType::aC2p;
    typeTable["C3*"] = AtomType::aC3p;
    typeTable["C4*"] = AtomType::aC4p;
    typeTable["C5*"] = AtomType::aC5p;
    typeTable["H1*"] = AtomType::aH1p;
    typeTable["H2*"] = AtomType::aH2p;
    typeTable["H3*"] = AtomType::aH3p;
    typeTable["H4*"] = AtomType::aH4p;
    typeTable["H5*"] = AtomType::aH5p;
    typeTable["1H2*"] = AtomType::a1H2p;
    typeTable["H2*1"] = AtomType::a1H2p;
    typeTable["1H5*"] = AtomType::a1H5p;
    typeTable["H5*1"] = AtomType::a1H5p;
    typeTable["2H2*"] = AtomType::a2H2p;
    typeTable["2H5*"] = AtomType::a2H5p;
    typeTable["H5**"] = AtomType::a2H5p;
    typeTable["H5*2"] = AtomType::a2H5p;
    typeTable["HO2*"] = AtomType::aHO2p;
    typeTable["H2**"] = AtomType::aHO2p;
    typeTable["HO*2"] = AtomType::aHO2p;
    typeTable["2HO*"] = AtomType::aHO2p;
    typeTable["HO3*"] = AtomType::aHO3p;
    typeTable["HO*3"] = AtomType::aHO3p;
    typeTable["O1P"] = AtomType::aO1P;
    typeTable["O2*"] = AtomType::aO2p;
    typeTable["O2P"] = AtomType::aO2P;
    typeTable["O3*"] = AtomType::aO3p;
    typeTable["O3T"] = AtomType::aO3p;
    typeTable["O3P"] = AtomType::aO3P;
    typeTable["O4*"] = AtomType::aO4p;
    typeTable["O5*"] = AtomType::aO5p;
    typeTable["O5T"] = AtomType::aO5p;
    typeTable["P"] = AtomType::aP;
    typeTable["C2"] = AtomType::aC2;
    typeTable["C4"] = AtomType::aC4;
    typeTable["C5"] = AtomType::aC5;
    typeTable["C5M"] = AtomType::aC5M;
    typeTable["C5A"] = AtomType::aC5M;
    typeTable["C6"] = AtomType::aC6;
    typeTable["C8"] = AtomType::aC8;
    typeTable["H1"] = AtomType::aH1;
    typeTable["H2"] = AtomType::aH2;
    typeTable["H3"] = AtomType::aH3;
    typeTable["H5"] = AtomType::aH5;
    typeTable["H6"] = AtomType::aH6;
    typeTable["H7"] = AtomType::aH7;
    typeTable["H8"] = AtomType::aH8;
    typeTable["1H2"] = AtomType::a1H2;
    typeTable["1H4"] = AtomType::a1H4;
    typeTable["1H5M"] = AtomType::a1H5M;
    typeTable["1H5A"] = AtomType::a1H5M;
    typeTable["1H6"] = AtomType::a1H6;
    typeTable["2H2"] = AtomType::a2H2;
    typeTable["2H4"] = AtomType::a2H4;
    typeTable["2H5M"] = AtomType::a2H5M;
    typeTable["2H5A"] = AtomType::a2H5M;
    typeTable["2H6"] = AtomType::a2H6;
    typeTable["3H5M"] = AtomType::a3H5M;
    typeTable["3H5A"] = AtomType::a3H5M;
    typeTable["N1"] = AtomType::aN1;
    typeTable["N2"] = AtomType::aN2;
    typeTable["N3"] = AtomType::aN3;
    typeTable["N4"] = AtomType::aN4;
    typeTable["N6"] = AtomType::aN6;
    typeTable["N7"] = AtomType::aN7;
    typeTable["N9"] = AtomType::aN9;
    typeTable["O2"] = AtomType::aO2;
    typeTable["O4"] = AtomType::aO4;
    typeTable["O6"] = AtomType::aO6;
    typeTable["2LP6"] = AtomType::a2LP6;
    typeTable["1LP6"] = AtomType::a1LP6;
    typeTable["LP7"] = AtomType::aLP7;
    typeTable["LP3"] = AtomType::aLP3;
    typeTable["LP1"] = AtomType::aLP1;
    typeTable["2LP2"] = AtomType::a2LP2;
    typeTable["1LP2"] = AtomType::a1LP2;
    typeTable["2LP4"] = AtomType::a2LP4;
    typeTable["1LP4"] = AtomType::a1LP4;
    typeTable["PSX"] = AtomType::aPSX;
    typeTable["PSY"] = AtomType::aPSY;
    typeTable["PSZ"] = AtomType::aPSZ;
    typeTable["H3T"] = AtomType::aH3T;
    typeTable["H5T"] = AtomType::aH5T;
    typeTable["C"] = AtomType::aC;
    typeTable["CA"] = AtomType::aCA;
    typeTable["CB"] = AtomType::aCB;
    typeTable["CD"] = AtomType::aCD;
    typeTable["CD1"] = AtomType::aCD1;
    typeTable["CD2"] = AtomType::aCD2;
    typeTable["CE"] = AtomType::aCE;
    typeTable["CE1"] = AtomType::aCE1;
    typeTable["CE2"] = AtomType::aCE2;
    typeTable["CE3"] = AtomType::aCE3;
    typeTable["CG"] = AtomType::aCG;
    typeTable["CG1"] = AtomType::aCG1;
    typeTable["CG2"] = AtomType::aCG2;
    typeTable["CH2"] = AtomType::aCH2;
    typeTable["CZ"] = AtomType::aCZ;
    typeTable["CZ2"] = AtomType::aCZ2;
    typeTable["CZ3"] = AtomType::aCZ3;
    typeTable["H"] = AtomType::aH;
    typeTable["1H"] = AtomType::a1H;
    typeTable["HN1"] = AtomType::a1H;
    typeTable["2H"] = AtomType::a2H;
    typeTable["HN2"] = AtomType::a2H;
    typeTable["3H"] = AtomType::a3H;
    typeTable["HN3"] = AtomType::a3H;
    typeTable["HA"] = AtomType::aHA;
    typeTable["1HA"] = AtomType::aHA1;
    typeTable["2HA"] = AtomType::aHA2;
    typeTable["HB"] = AtomType::aHB;
    typeTable["1HB"] = AtomType::aHB1;
    typeTable["2HB"] = AtomType::aHB2;
    typeTable["3HB"] = AtomType::aHB3;
    typeTable["1HD"] = AtomType::aHD1;
    typeTable["2HD"] = AtomType::aHD2;
    typeTable["HE"] = AtomType::aHE;
    typeTable["1HE"] = AtomType::aHE1;
    typeTable["2HE"] = AtomType::aHE2;
    typeTable["3HE"] = AtomType::aHE3;
    typeTable["HG"] = AtomType::aHG;
    typeTable["1HG"] = AtomType::aHG1;
    typeTable["2HG"] = AtomType::aHG2;
    typeTable["HH"] = AtomType::aHH;
    typeTable["HH2"] = AtomType::aHH2;
    typeTable["HXT"] = AtomType::aHXT;
    typeTable["HZ"] = AtomType::aHZ;
    typeTable["1HZ"] = AtomType::aHZ1;
    typeTable["2HZ"] = AtomType::aHZ2;
    typeTable["3HZ"] = AtomType::aHZ3;
    typeTable["N"] = AtomType::aN;
    typeTable["ND1"] = AtomType::aND1;
    typeTable["ND2"] = AtomType::aND2;
    typeTable["NE"] = AtomType::aNE;
    typeTable["NE1"] = AtomType::aNE1;
    typeTable["NE2"] = AtomType::aNE2;
    typeTable["NH1"] = AtomType::aNH1;
    typeTable["NH2"] = AtomType::aNH2;
    typeTable["NZ"] = AtomType::aNZ;
    typeTable["O"] = AtomType::aO;
    typeTable["OD1"] = AtomType::aOD1;
    typeTable["OD2"] = AtomType::aOD2;
    typeTable["OE1"] = AtomType::aOE1;
    typeTable["OE2"] = AtomType::aOE2;
    typeTable["OG"] = AtomType::aOG;
    typeTable["OG1"] = AtomType::aOG1;
    typeTable["OH"] = AtomType::aOH;
    typeTable["OXT"] = AtomType::aOXT;
    typeTable["SD"] = AtomType::aSD;
    typeTable["SG"] = AtomType::aSG;
    typeTable["1HD1"] = AtomType::a1HD1;
    typeTable["1HD2"] = AtomType::a1HD2;
    typeTable["1HE2"] = AtomType::a1HE2;
    typeTable["1HG1"] = AtomType::a1HG1;
    typeTable["1HG2"] = AtomType::a1HG2;
    typeTable["1HH1"] = AtomType::a1HH1;
    typeTable["1HH2"] = AtomType::a1HH2;
    typeTable["2HD1"] = AtomType::a2HD1;
    typeTable["2HD2"] = AtomType::a2HD2;
    typeTable["2HE2"] = AtomType::a2HE2;
    typeTable["2HG1"] = AtomType::a2HG1;
    typeTable["2HG2"] = AtomType::a2HG2;
    typeTable["2HH1"] = AtomType::a2HH1;
    typeTable["2HH2"] = AtomType::a2HH2;
    typeTable["3HD1"] = AtomType::a3HD1;
    typeTable["3HD2"] = AtomType::a3HD2;
    typeTable["3HG1"] = AtomType::a3HG1;
    typeTable["3HG2"] = AtomType::a3HG2;
    typeTable["MG"] = AtomType::aMG;
    typeTable["PSAZ"] = AtomType::aPSAZ;

    representationTable[AtomType::aNull] = "";
    representationTable[AtomType::aC1p] = "C1*";
    representationTable[AtomType::aC2p] = "C2*";
    representationTable[AtomType::aC3p] = "C3*";
    representationTable[AtomType::aC4p] = "C4*";
    representationTable[AtomType::aC5p] = "C5*";
    representationTable[AtomType::aH1p] = "H1*";
    representationTable[AtomType::aH2p] = "H2*";
    representationTable[AtomType::aH3p] = "H3*";
    representationTable[AtomType::aH4p] = "H4*";
    representationTable[AtomType::aH5p] = "H5*";
    representationTable[AtomType::a1H2p] = "1H2*";
    representationTable[AtomType::a1H5p] = "1H5*";
    representationTable[AtomType::a2H2p] = "2H2*";
    representationTable[AtomType::a2H5p] = "2H5*";
    representationTable[AtomType::aHO2p] = "HO2*";
    representationTable[AtomType::aHO3p] = "HO3*";
    representationTable[AtomType::aO1P] = "O1P";
    representationTable[AtomType::aO2p] = "O2*";
    representationTable[AtomType::aO2P] = "O2P";
    representationTable[AtomType::aO3p] = "O3*";
    representationTable[AtomType::aO3P] = "O3P";
    representationTable[AtomType::aO4p] = "O4*";
    representationTable[AtomType::aO5p] = "O5*";
    representationTable[AtomType::aP] = "P";
    representationTable[AtomType::aC2] = "C2";
    representationTable[AtomType::aC4] = "C4";
    representationTable[AtomType::aC5] = "C5";
    representationTable[AtomType::aC5M] = "C5M";
    representationTable[AtomType::aC6] = "C6";
    representationTable[AtomType::aC8] = "C8";
    representationTable[AtomType::aH1] = "H1";
    representationTable[AtomType::aH2] = "H2";
    representationTable[AtomType::aH3] = "H3";
    representationTable[AtomType::aH5] = "H5";
    representationTable[AtomType::aH6] = "H6";
    representationTable[AtomType::aH7] = "H7";
    representationTable[AtomType::aH8] = "H8";
    representationTable[AtomType::a1H2] = "1H2";
    representationTable[AtomType::a1H4] = "1H4";
    representationTable[AtomType::a1H5M] = "1H5M";
    representationTable[AtomType::a1H6] = "1H6";
    representationTable[AtomType::a2H2] = "2H2";
    representationTable[AtomType::a2H4] = "2H4";
    representationTable[AtomType::a2H5M] = "2H5M";
    representationTable[AtomType::a2H6] = "2H6";
    representationTable[AtomType::a3H5M] = "3H5M";
    representationTable[AtomType::aN1] = "N1";
    representationTable[AtomType::aN2] = "N2";
    representationTable[AtomType::aN3] = "N3";
    representationTable[AtomType::aN4] = "N4";
    representationTable[AtomType::aN6] = "N6";
    representationTable[AtomType::aN7] = "N7";
    representationTable[AtomType::aN9] = "N9";
    representationTable[AtomType::aO2] = "O2";
    representationTable[AtomType::aO4] = "O4";
    representationTable[AtomType::aO6] = "O6";
    representationTable[AtomType::a2LP6] = "2LP6";
    representationTable[AtomType::a1LP6] = "1LP6";
    representationTable[AtomType::aLP7] = "LP7";
    representationTable[AtomType::aLP3] = "LP3";
    representationTable[AtomType::aLP1] = "LP1";
    representationTable[AtomType::a2LP2] = "2LP2";
    representationTable[AtomType::a1LP2] = "1LP2";
    representationTable[AtomType::a2LP4] = "2LP4";
    representationTable[AtomType::a1LP4] = "1LP4";
    representationTable[AtomType::aPSX] = "PSX";
    representationTable[AtomType::aPSY] = "PSY";
    representationTable[AtomType::aPSZ] = "PSZ";
    representationTable[AtomType::aH3T] = "H3T";
    representationTable[AtomType::aH5T] = "H5T";
    representationTable[AtomType::aC] = "C";
    representationTable[AtomType::aCA] = "CA";
    representationTable[AtomType::aCB] = "CB";
    representationTable[AtomType::aCD] = "CD";
    representationTable[AtomType::aCD1] = "CD1";
    representationTable[AtomType::aCD2] = "CD2";
    representationTable[AtomType::aCE] = "CE";
    representationTable[AtomType::aCE1] = "CE1";
    representationTable[AtomType::aCE2] = "CE2";
    representationTable[AtomType::aCE3] = "CE3";
    representationTable[AtomType::aCG] = "CG";
    representationTable[AtomType::aCG1] = "CG1";
    representationTable[AtomType::aCG2] = "CG2";
    representationTable[AtomType::aCH2] = "CH2";
    representationTable[AtomType::aCZ] = "CZ";
    representationTable[AtomType::aCZ2] = "CZ2";
    representationTable[AtomType::aCZ3] = "CZ3";
    representationTable[AtomType::aH] = "H";
    representationTable[AtomType::a1H] = "1H";
    representationTable[AtomType::a2H] = "2H";
    representationTable[AtomType::a3H] = "3H";
    representationTable[AtomType::aHA] = "HA";
    representationTable[AtomType::aHA1] = "1HA";
    representationTable[AtomType::aHA2] = "2HA";
    representationTable[AtomType::aHB] = "HB";
    representationTable[AtomType::aHB1] = "1HB";
    representationTable[AtomType::aHB2] = "2HB";
    representationTable[AtomType::aHB3] = "3HB";
    representationTable[AtomType::aHD1] = "1HD";
    representationTable[AtomType::aHD2] = "2HD";
    representationTable[AtomType::aHE] = "HE";
    representationTable[AtomType::aHE1] = "1HE";
    representationTable[AtomType::aHE2] = "2HE";
    representationTable[AtomType::aHE3] = "3HE";
    representationTable[AtomType::aHG] = "HG";
    representationTable[AtomType::aHG1] = "1HG";
    representationTable[AtomType::aHG2] = "2HG";
    representationTable[AtomType::aHH] = "HH";
    representationTable[AtomType::aHH2] = "HH2";
    representationTable[AtomType::aHXT] = "HXT";
    representationTable[AtomType::aHZ] = "HZ";
    representationTable[AtomType::aHZ1] = "1HZ";
    representationTable[AtomType::aHZ2] = "2HZ";
    representationTable[AtomType::aHZ3] = "3HZ";
    representationTable[AtomType::aN] = "N";
    representationTable[AtomType::aND1] = "ND1";
    representationTable[AtomType::aND2] = "ND2";
    representationTable[AtomType::aNE] = "NE";
    representationTable[AtomType::aNE1] = "NE1";
    representationTable[AtomType::aNE2] = "NE2";
    representationTable[AtomType::aNH1] = "NH1";
    representationTable[AtomType::aNH2] = "NH2";
    representationTable[AtomType::aNZ] = "NZ";
    representationTable[AtomType::aO] = "O";
    representationTable[AtomType::aOD1] = "OD1";
    representationTable[AtomType::aOD2] = "OD2";
    representationTable[AtomType::aOE1] = "OE1";
    representationTable[AtomType::aOE2] = "OE2";
    representationTable[AtomType::aOG] = "OG";
    representationTable[AtomType::aOG1] = "OG1";
    representationTable[AtomType::aOH] = "OH";
    representationTable[AtomType::aOXT] = "OXT";
    representationTable[AtomType::aSD] = "SD";
    representationTable[AtomType::aSG] = "SG";
    representationTable[AtomType::a1HD1] = "1HD1";
    representationTable[AtomType::a1HD2] = "1HD2";
    representationTable[AtomType::a1HE2] = "1HE2";
    representationTable[AtomType::a1HG1] = "1HG1";
    representationTable[AtomType::a1HG2] = "1HG2";
    representationTable[AtomType::a1HH1] = "1HH1";
    representationTable[AtomType::a1HH2] = "1HH2";
    representationTable[AtomType::a2HD1] = "2HD1";
    representationTable[AtomType::a2HD2] = "2HD2";
    representationTable[AtomType::a2HE2] = "2HE2";
    representationTable[AtomType::a2HG1] = "2HG1";
    representationTable[AtomType::a2HG2] = "2HG2";
    representationTable[AtomType::a2HH1] = "2HH1";
    representationTable[AtomType::a2HH2] = "2HH2";
    representationTable[AtomType::a3HD1] = "3HD1";
    representationTable[AtomType::a3HD2] = "3HD2";
    representationTable[AtomType::a3HG1] = "3HG1";
    representationTable[AtomType::a3HG2] = "3HG2";
    representationTable[AtomType::aMG] = "MG";
    representationTable[AtomType::aPSAZ] = "PSAZ";
  }


  AmberResidueTypeRepresentationTable::AmberResidueTypeRepresentationTable ()
  {
    typeTable["RA"] = ResidueType::rRA;
    typeTable["RA5"] = ResidueType::rRA;
    typeTable["RA3"] = ResidueType::rRA;
    typeTable["DA"] = ResidueType::rDA;
    typeTable["DA5"] = ResidueType::rDA;
    typeTable["DA3"] = ResidueType::rDA;
    typeTable["RC"] = ResidueType::rRC;
    typeTable["RC5"] = ResidueType::rRC;
    typeTable["RC3"] = ResidueType::rRC;
    typeTable["DC"] = ResidueType::rDC;
    typeTable["DC5"] = ResidueType::rDC;
    typeTable["DC3"] = ResidueType::rDC;
    typeTable["RG"] = ResidueType::rRG;
    typeTable["RG5"] = ResidueType::rRG;
    typeTable["RG3"] = ResidueType::rRG;
    typeTable["DG"] = ResidueType::rDG;
    typeTable["DG5"] = ResidueType::rDG;
    typeTable["DG3"] = ResidueType::rDG;
    typeTable["RU"] = ResidueType::rRU;
    typeTable["RU5"] = ResidueType::rRU;
    typeTable["RU3"] = ResidueType::rRU;
    typeTable["DT"] = ResidueType::rDT;
    typeTable["DT5"] = ResidueType::rDT;
    typeTable["DT3"] = ResidueType::rDT;
    typeTable["ALA"] = ResidueType::rALA;
    typeTable["PA"] = ResidueType::rALA;
    typeTable["ARG"] = ResidueType::rARG;
    typeTable["PR"] = ResidueType::rARG;
    typeTable["ASN"] = ResidueType::rASN;
    typeTable["PN"] = ResidueType::rASN;
    typeTable["ASP"] = ResidueType::rASP;
    typeTable["PD"] = ResidueType::rASP;
    typeTable["CYS"] = ResidueType::rCYS;
    typeTable["PC"] = ResidueType::rCYS;
    typeTable["GLN"] = ResidueType::rGLN;
    typeTable["PQ"] = ResidueType::rGLN;
    typeTable["GLU"] = ResidueType::rGLU;
    typeTable["PE"] = ResidueType::rGLU;
    typeTable["GLY"] = ResidueType::rGLY;
    typeTable["PG"] = ResidueType::rGLY;
    typeTable["HIS"] = ResidueType::rHIS;
    typeTable["PH"] = ResidueType::rHIS;
    typeTable["ILE"] = ResidueType::rILE;
    typeTable["PI"] = ResidueType::rILE;
    typeTable["LEU"] = ResidueType::rLEU;
    typeTable["PL"] = ResidueType::rLEU;
    typeTable["LYS"] = ResidueType::rLYS;
    typeTable["PK"] = ResidueType::rLYS;
    typeTable["MET"] = ResidueType::rMET;
    typeTable["PM"] = ResidueType::rMET;
    typeTable["PHE"] = ResidueType::rPHE;
    typeTable["PF"] = ResidueType::rPHE;
    typeTable["PRO"] = ResidueType::rPRO;
    typeTable["PP"] = ResidueType::rPRO;
    typeTable["SER"] = ResidueType::rSER;
    typeTable["PS"] = ResidueType::rSER;
    typeTable["THR"] = ResidueType::rTHR;
    typeTable["PT"] = ResidueType::rTHR;
    typeTable["TRP"] = ResidueType::rTRP;
    typeTable["PW"] = ResidueType::rTRP;
    typeTable["TYR"] = ResidueType::rTYR;
    typeTable["PY"] = ResidueType::rTYR;
    typeTable["VAL"] = ResidueType::rVAL;
    typeTable["PV"] = ResidueType::rVAL;

    representationTable[ResidueType::rRA] = "RA ";
    representationTable[ResidueType::parseType ("RRA5")] = "RA5";
    representationTable[ResidueType::parseType ("RRA3")] = "RA3";
    representationTable[ResidueType::rDA] = "DA ";
    representationTable[ResidueType::parseType ("DDA5")] = "DA5";
    representationTable[ResidueType::parseType ("DDA3")] = "DA3";
    representationTable[ResidueType::rRC] = "RC ";
    representationTable[ResidueType::parseType ("RRC5")] = "RC5";
    representationTable[ResidueType::parseType ("RRC3")] = "RC3";
    representationTable[ResidueType::rDC] = "DC ";
    representationTable[ResidueType::parseType ("DDC5")] = "DC5";
    representationTable[ResidueType::parseType ("DDC3")] = "DC3";
    representationTable[ResidueType::rRG] = "RG ";
    representationTable[ResidueType::parseType ("RRG5")] = "RG5";
    representationTable[ResidueType::parseType ("RRG3")] = "RG3";
    representationTable[ResidueType::rDG] = "DG ";
    representationTable[ResidueType::parseType ("DDG5")] = "DG5";
    representationTable[ResidueType::parseType ("DDG3")] = "DG3";
    representationTable[ResidueType::rRU] = "RU ";
    representationTable[ResidueType::parseType ("RRU5")] = "RU5";
    representationTable[ResidueType::parseType ("RRU33")] = "RU3";
    representationTable[ResidueType::rDT] = "DT ";
    representationTable[ResidueType::parseType ("DDT5")] = "DT5";
    representationTable[ResidueType::parseType ("DDT3")] = "DT3";
    representationTable[ResidueType::rALA] = "ALA";
    representationTable[ResidueType::rARG] = "ARG";
    representationTable[ResidueType::rASN] = "ASN";
    representationTable[ResidueType::rASP] = "ASP";
    representationTable[ResidueType::rCYS] = "CYS";
    representationTable[ResidueType::rGLN] = "GLN";
    representationTable[ResidueType::rGLU] = "GLU";
    representationTable[ResidueType::rGLY] = "GLY";
    representationTable[ResidueType::rHIS] = "HIS";
    representationTable[ResidueType::rILE] = "ILE";
    representationTable[ResidueType::rLEU] = "LEU";
    representationTable[ResidueType::rLYS] = "LYS";
    representationTable[ResidueType::rMET] = "MET";
    representationTable[ResidueType::rPHE] = "PHE";
    representationTable[ResidueType::rPRO] = "PRO";
    representationTable[ResidueType::rSER] = "SER";
    representationTable[ResidueType::rTHR] = "THR";
    representationTable[ResidueType::rTRP] = "TRP";
    representationTable[ResidueType::rTYR] = "TYR";
    representationTable[ResidueType::rVAL] = "VAL";
  }


  PdbResidueTypeRepresentationTable::PdbResidueTypeRepresentationTable ()
  {
    typeTable["A"] = ResidueType::rRA;
    typeTable["ADE"] = ResidueType::rRA;
    typeTable["C"] = ResidueType::rRC;
    typeTable["CYT"] = ResidueType::rRC;
    typeTable["G"] = ResidueType::rRG;
    typeTable["GUA"] = ResidueType::rRG;
    typeTable["U"] = ResidueType::rRU;
    typeTable["URI"] = ResidueType::rRU;
    typeTable["URA"] = ResidueType::rRU;
    typeTable["T"] = ResidueType::rDT;
    typeTable["TYM"] = ResidueType::rDT;
    typeTable["ALA"] = ResidueType::rALA;
    typeTable["PA"] = ResidueType::rALA;
    typeTable["ARG"] = ResidueType::rARG;
    typeTable["PR"] = ResidueType::rARG;
    typeTable["ASN"] = ResidueType::rASN;
    typeTable["PN"] = ResidueType::rASN;
    typeTable["ASP"] = ResidueType::rASP;
    typeTable["PD"] = ResidueType::rASP;
    typeTable["CYS"] = ResidueType::rCYS;
    typeTable["PC"] = ResidueType::rCYS;
    typeTable["GLN"] = ResidueType::rGLN;
    typeTable["PQ"] = ResidueType::rGLN;
    typeTable["GLU"] = ResidueType::rGLU;
    typeTable["PE"] = ResidueType::rGLU;
    typeTable["GLY"] = ResidueType::rGLY;
    typeTable["PG"] = ResidueType::rGLY;
    typeTable["HIS"] = ResidueType::rHIS;
    typeTable["PH"] = ResidueType::rHIS;
    typeTable["ILE"] = ResidueType::rILE;
    typeTable["PI"] = ResidueType::rILE;
    typeTable["LEU"] = ResidueType::rLEU;
    typeTable["PL"] = ResidueType::rLEU;
    typeTable["LYS"] = ResidueType::rLYS;
    typeTable["PK"] = ResidueType::rLYS;
    typeTable["MET"] = ResidueType::rMET;
    typeTable["PM"] = ResidueType::rMET;
    typeTable["PHE"] = ResidueType::rPHE;
    typeTable["PF"] = ResidueType::rPHE;
    typeTable["PRO"] = ResidueType::rPRO;
    typeTable["PP"] = ResidueType::rPRO;
    typeTable["SER"] = ResidueType::rSER;
    typeTable["PS"] = ResidueType::rSER;
    typeTable["THR"] = ResidueType::rTHR;
    typeTable["PT"] = ResidueType::rTHR;
    typeTable["TRP"] = ResidueType::rTRP;
    typeTable["PW"] = ResidueType::rTRP;
    typeTable["TYR"] = ResidueType::rTYR;
    typeTable["PY"] = ResidueType::rTYR;
    typeTable["VAL"] = ResidueType::rVAL;
    typeTable["PV"] = ResidueType::rVAL;

    representationTable[ResidueType::rRA] = "A";
    representationTable[ResidueType::rDA] = "A";
    representationTable[ResidueType::rRC] = "C";
    representationTable[ResidueType::rDC] = "C";
    representationTable[ResidueType::rRG] = "G";
    representationTable[ResidueType::rDG] = "G";
    representationTable[ResidueType::rRU] = "U";
    representationTable[ResidueType::rDT] = "T";
    representationTable[ResidueType::rALA] = "ALA";
    representationTable[ResidueType::rARG] = "ARG";
    representationTable[ResidueType::rASN] = "ASN";
    representationTable[ResidueType::rASP] = "ASP";
    representationTable[ResidueType::rCYS] = "CYS";
    representationTable[ResidueType::rGLN] = "GLN";
    representationTable[ResidueType::rGLU] = "GLU";
    representationTable[ResidueType::rGLY] = "GLY";
    representationTable[ResidueType::rHIS] = "HIS";
    representationTable[ResidueType::rILE] = "ILE";
    representationTable[ResidueType::rLEU] = "LEU";
    representationTable[ResidueType::rLYS] = "LYS";
    representationTable[ResidueType::rMET] = "MET";
    representationTable[ResidueType::rPHE] = "PHE";
    representationTable[ResidueType::rPRO] = "PRO";
    representationTable[ResidueType::rSER] = "SER";
    representationTable[ResidueType::rTHR] = "THR";
    representationTable[ResidueType::rTRP] = "TRP";
    representationTable[ResidueType::rTYR] = "TYR";
    representationTable[ResidueType::rVAL] = "VAL";
  }
}
