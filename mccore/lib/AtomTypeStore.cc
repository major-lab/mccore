//                              -*- Mode: C++ -*- 
// AtomTypeStore.cc
// Copyright © 2003-07 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 13:56:50 2003
// $Revision: 1.19 $
// $Id: AtomTypeStore.cc,v 1.19 2007-01-14 18:21:02 larosem Exp $
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


#include "AtomTypeStore.h"
#include "ResidueType.h"
#include "Messagestream.h"


namespace mccore
{

  // LIFECYCLE -----------------------------------------------------------------

  AtomTypeStore::AtomTypeStore () 
  {
    string str;

    AtomType::aNull = *repository.insert (new Null ((str = ""))).first;
    AtomType::aUnknown = *repository.insert (new Unknown ((str = "UNK"))).first;
    AtomType::aC1p = *repository.insert (new AC1p ((str = "C1*"))).first;
    AtomType::aC2p = *repository.insert (new AC2p ((str = "C2*"))).first;
    AtomType::aC3p = *repository.insert (new AC3p ((str = "C3*"))).first;
    AtomType::aC4p = *repository.insert (new AC4p ((str = "C4*"))).first;
    AtomType::aC5p = *repository.insert (new AC5p ((str = "C5*"))).first;
    AtomType::aH1p = *repository.insert (new AH1p ((str = "H1*"))).first;
    AtomType::aH2p = *repository.insert (new AH2p ((str = "H2*"))).first;
    AtomType::aH3p = *repository.insert (new AH3p ((str = "H3*"))).first;
    AtomType::aH4p = *repository.insert (new AH4p ((str = "H4*"))).first;
    AtomType::aH5p = *repository.insert (new AH5p ((str = "H5*"))).first;
    AtomType::aO1P = *repository.insert (new AO1P ((str = "O1P"))).first;
    AtomType::aO2p = *repository.insert (new AO2p ((str = "O2*"))).first;
    AtomType::aO2P = *repository.insert (new AO2P ((str = "O2P"))).first;
    AtomType::aO3p = *repository.insert (new AO3p ((str = "O3*"))).first;
    AtomType::aO3P = *repository.insert (new AO3P ((str = "O3P"))).first;
    AtomType::aO4p = *repository.insert (new AO4p ((str = "O4*"))).first;
    AtomType::aO5p = *repository.insert (new AO5p ((str = "O5*"))).first;
    AtomType::aP = *repository.insert (new AP ((str = "P"))).first;
    AtomType::a1H2p = *repository.insert (new A1H2p ((str = "1H2*"))).first;
    AtomType::a1H5p = *repository.insert (new A1H5p ((str = "1H5*"))).first;
    AtomType::a2H2p = *repository.insert (new A2H2p ((str = "2H2*"))).first;
    AtomType::a2H5p = *repository.insert (new A2H5p ((str = "2H5*"))).first;
    AtomType::aHO2p = *repository.insert (new AHO2p ((str = "HO2*"))).first;
    AtomType::aHO3p = *repository.insert (new AHO3p ((str = "HO3*"))).first;
    AtomType::aC2 = *repository.insert (new AC2 ((str = "C2"))).first;
    AtomType::aC4 = *repository.insert (new AC4 ((str = "C4"))).first;
    AtomType::aC5 = *repository.insert (new AC5 ((str = "C5"))).first;
    AtomType::aC5M = *repository.insert (new AC5M ((str = "C5M"))).first;
    AtomType::aC6 = *repository.insert (new AC6 ((str = "C6"))).first;
    AtomType::aC8 = *repository.insert (new AC8 ((str = "C8"))).first;
    AtomType::aH1 = *repository.insert (new AH1 ((str = "H1"))).first;
    AtomType::aH2 = *repository.insert (new AH2 ((str = "H2"))).first;
    AtomType::aH3 = *repository.insert (new AH3 ((str = "H3"))).first;
    AtomType::aH5 = *repository.insert (new AH5 ((str = "H5"))).first;
    AtomType::aH6 = *repository.insert (new AH6 ((str = "H6"))).first;
    AtomType::aH7 = *repository.insert (new AH7 ((str = "H7"))).first;
    AtomType::aH8 = *repository.insert (new AH8 ((str = "H8"))).first;
    AtomType::aN1 = *repository.insert (new AN1 ((str = "N1"))).first;
    AtomType::aN2 = *repository.insert (new AN2 ((str = "N2"))).first;
    AtomType::aN3 = *repository.insert (new AN3 ((str = "N3"))).first;
    AtomType::aN4 = *repository.insert (new AN4 ((str = "N4"))).first;
    AtomType::aN6 = *repository.insert (new AN6 ((str = "N6"))).first;
    AtomType::aN7 = *repository.insert (new AN7 ((str = "N7"))).first;
    AtomType::aN9 = *repository.insert (new AN9 ((str = "N9"))).first;
    AtomType::aO2 = *repository.insert (new AO2 ((str = "O2"))).first;
    AtomType::aO4 = *repository.insert (new AO4 ((str = "O4"))).first;
    AtomType::aO6 = *repository.insert (new AO6 ((str = "O6"))).first;
    AtomType::a1H2 = *repository.insert (new A1H2 ((str = "1H2"))).first;
    AtomType::a1H4 = *repository.insert (new A1H4 ((str = "1H4"))).first;
    AtomType::a1H5M = *repository.insert (new A1H5M ((str = "1H5M"))).first;
    AtomType::a1H6 = *repository.insert (new A1H6 ((str = "1H6"))).first;
    AtomType::a2H2 = *repository.insert (new A2H2 ((str = "2H2"))).first;
    AtomType::a2H4 = *repository.insert (new A2H4 ((str = "2H4"))).first;
    AtomType::a2H5M = *repository.insert (new A2H5M ((str = "2H5M"))).first;
    AtomType::a2H6 = *repository.insert (new A2H6 ((str = "2H6"))).first;
    AtomType::a3H5M = *repository.insert (new A3H5M ((str = "3H5M"))).first;
    AtomType::aPSX = *repository.insert (new APSX ((str = "PSX"))).first;
    AtomType::aPSY = *repository.insert (new APSY ((str = "PSY"))).first;
    AtomType::aPSZ = *repository.insert (new APSZ ((str = "PSZ"))).first;
    AtomType::aPSO = *repository.insert (new APSO ((str = "PSO"))).first;
    AtomType::aLP1 = *repository.insert (new ALP1 ((str = "LP1"))).first;
    AtomType::aLP3 = *repository.insert (new ALP3 ((str = "LP3"))).first;
    AtomType::aLP7 = *repository.insert (new ALP7 ((str = "LP7"))).first;
    AtomType::a1LP2 = *repository.insert (new A1LP2 ((str = "1LP2"))).first;
    AtomType::a1LP4 = *repository.insert (new A1LP4 ((str = "1LP4"))).first;
    AtomType::a1LP6 = *repository.insert (new A1LP6 ((str = "1LP6"))).first;
    AtomType::a2LP2 = *repository.insert (new A2LP2 ((str = "2LP2"))).first;
    AtomType::a2LP4 = *repository.insert (new A2LP4 ((str = "2LP4"))).first;
    AtomType::a2LP6 = *repository.insert (new A2LP6 ((str = "2LP6"))).first;
    AtomType::aH3T = *repository.insert (new AH3T ((str = "H3T"))).first;
    AtomType::aH5T = *repository.insert (new AH5T ((str = "H5T"))).first;
    AtomType::aC = *repository.insert (new AC ((str = "C"))).first;
    AtomType::aCA = *repository.insert (new ACA ((str = "CA"))).first;
    AtomType::aCB = *repository.insert (new ACB ((str = "CB"))).first;
    AtomType::aCD = *repository.insert (new ACD ((str = "CD"))).first;
    AtomType::aCD1 = *repository.insert (new ACD1 ((str = "CD1"))).first;
    AtomType::aCD2 = *repository.insert (new ACD2 ((str = "CD2"))).first;
    AtomType::aCE = *repository.insert (new ACE ((str = "CE"))).first;
    AtomType::aCE1 = *repository.insert (new ACE1 ((str = "CE1"))).first;
    AtomType::aCE2 = *repository.insert (new ACE2 ((str = "CE2"))).first;
    AtomType::aCE3 = *repository.insert (new ACE3 ((str = "CE3"))).first;
    AtomType::aCG = *repository.insert (new ACG ((str = "CG"))).first;
    AtomType::aCG1 = *repository.insert (new ACG1 ((str = "CG1"))).first;
    AtomType::aCG2 = *repository.insert (new ACG2 ((str = "CG2"))).first;
    AtomType::aCH2 = *repository.insert (new ACH2 ((str = "CH2"))).first;
    AtomType::aCZ = *repository.insert (new ACZ ((str = "CZ"))).first;
    AtomType::aCZ2 = *repository.insert (new ACZ2 ((str = "CZ2"))).first;
    AtomType::aCZ3 = *repository.insert (new ACZ3 ((str = "CZ3"))).first;
    AtomType::aH = *repository.insert (new AH ((str = "H"))).first;
    AtomType::a1H = *repository.insert (new A1H ((str = "1H"))).first;
    AtomType::a2H = *repository.insert (new A2H ((str = "2H"))).first;
    AtomType::a3H = *repository.insert (new A3H ((str = "3H"))).first;
    AtomType::aHA = *repository.insert (new AHA ((str = "HA"))).first;
    AtomType::aHA1 = *repository.insert (new AHA1 ((str = "HA1"))).first;
    AtomType::aHA2 = *repository.insert (new AHA2 ((str = "HA2"))).first;
    AtomType::aHB = *repository.insert (new AHB ((str = "HB"))).first;
    AtomType::aHB1 = *repository.insert (new AHB1 ((str = "HB1"))).first;
    AtomType::aHB2 = *repository.insert (new AHB2 ((str = "HB2"))).first;
    AtomType::aHB3 = *repository.insert (new AHB3 ((str = "HB3"))).first;
    AtomType::aHD1 = *repository.insert (new AHD1 ((str = "HD1"))).first;
    AtomType::aHD2 = *repository.insert (new AHD2 ((str = "HD2"))).first;
    AtomType::aHE = *repository.insert (new AHE ((str = "HE"))).first;
    AtomType::aHE1 = *repository.insert (new AHE1 ((str = "HE1"))).first;
    AtomType::aHE2 = *repository.insert (new AHE2 ((str = "HE2"))).first;
    AtomType::aHE3 = *repository.insert (new AHE3 ((str = "HE3"))).first;
    AtomType::aHG = *repository.insert (new AHG ((str = "HG"))).first;
    AtomType::aHG1 = *repository.insert (new AHG1 ((str = "HG1"))).first;
    AtomType::aHG2 = *repository.insert (new AHG2 ((str = "HG2"))).first;
    AtomType::aHH = *repository.insert (new AHH ((str = "HH"))).first;
    AtomType::aHH2 = *repository.insert (new AHH2 ((str = "HH2"))).first;
    AtomType::aHXT = *repository.insert (new AHXT ((str = "HXT"))).first;
    AtomType::aHZ = *repository.insert (new AHZ ((str = "HZ"))).first;
    AtomType::aHZ1 = *repository.insert (new AHZ1 ((str = "HZ1"))).first;
    AtomType::aHZ2 = *repository.insert (new AHZ2 ((str = "HZ2"))).first;
    AtomType::aHZ3 = *repository.insert (new AHZ3 ((str = "HZ3"))).first;
    AtomType::aN = *repository.insert (new AN ((str = "N"))).first;
    AtomType::aND1 = *repository.insert (new AND1 ((str = "ND1"))).first;
    AtomType::aND2 = *repository.insert (new AND2 ((str = "ND2"))).first;
    AtomType::aNE = *repository.insert (new ANE ((str = "NE"))).first;
    AtomType::aNE1 = *repository.insert (new ANE1 ((str = "NE1"))).first;
    AtomType::aNE2 = *repository.insert (new ANE2 ((str = "NE2"))).first;
    AtomType::aNH1 = *repository.insert (new ANH1 ((str = "NH1"))).first;
    AtomType::aNH2 = *repository.insert (new ANH2 ((str = "NH2"))).first;
    AtomType::aNZ = *repository.insert (new ANZ ((str = "NZ"))).first;
    AtomType::aO = *repository.insert (new AO ((str = "O"))).first;
    AtomType::aOD1 = *repository.insert (new AOD1 ((str = "OD1"))).first;
    AtomType::aOD2 = *repository.insert (new AOD2 ((str = "OD2"))).first;
    AtomType::aOE1 = *repository.insert (new AOE1 ((str = "OE1"))).first;
    AtomType::aOE2 = *repository.insert (new AOE2 ((str = "OE2"))).first;
    AtomType::aOG = *repository.insert (new AOG ((str = "OG"))).first;
    AtomType::aOG1 = *repository.insert (new AOG1 ((str = "OG1"))).first;
    AtomType::aOH = *repository.insert (new AOH ((str = "OH"))).first;
    AtomType::aOXT = *repository.insert (new AOXT ((str = "OXT"))).first;
    AtomType::aSD = *repository.insert (new ASD ((str = "SD"))).first;
    AtomType::aSG = *repository.insert (new ASG ((str = "SG"))).first;
    AtomType::a1HD1 = *repository.insert (new A1HD1 ((str = "1HD1"))).first;
    AtomType::a1HD2 = *repository.insert (new A1HD2 ((str = "1HD2"))).first;
    AtomType::a1HE2 = *repository.insert (new A1HE2 ((str = "1HE2"))).first;
    AtomType::a1HG1 = *repository.insert (new A1HG1 ((str = "1HG1"))).first;
    AtomType::a1HG2 = *repository.insert (new A1HG2 ((str = "1HG2"))).first;
    AtomType::a1HH1 = *repository.insert (new A1HH1 ((str = "1HH1"))).first;
    AtomType::a1HH2 = *repository.insert (new A1HH2 ((str = "1HH2"))).first;
    AtomType::a2HD1 = *repository.insert (new A2HD1 ((str = "2HD1"))).first;
    AtomType::a2HD2 = *repository.insert (new A2HD2 ((str = "2HD2"))).first;
    AtomType::a2HE2 = *repository.insert (new A2HE2 ((str = "2HE2"))).first;
    AtomType::a2HG1 = *repository.insert (new A2HG1 ((str = "2HG1"))).first;
    AtomType::a2HG2 = *repository.insert (new A2HG2 ((str = "2HG2"))).first;
    AtomType::a2HH1 = *repository.insert (new A2HH1 ((str = "2HH1"))).first;
    AtomType::a2HH2 = *repository.insert (new A2HH2 ((str = "2HH2"))).first;
    AtomType::a3HD1 = *repository.insert (new A3HD1 ((str = "3HD1"))).first;
    AtomType::a3HD2 = *repository.insert (new A3HD2 ((str = "3HD2"))).first;
    AtomType::a3HG1 = *repository.insert (new A3HG1 ((str = "3HG1"))).first;
    AtomType::a3HG2 = *repository.insert (new A3HG2 ((str = "3HG2"))).first;
    AtomType::aMG = *repository.insert (new AMG ((str = "MG"))).first;
    AtomType::aPSAZ = *repository.insert (new APSAZ ((str = "PSAZ"))).first;

    // New AtomType (some are invalid type names due to their notation in
    // the components.cif.gz file
    //
//     AtomType::a"C10 = *repository.insert (new A"C10 ((str = ""C10"))).first;
//     AtomType::a"C11 = *repository.insert (new A"C11 ((str = ""C11"))).first;
//     AtomType::a"C12 = *repository.insert (new A"C12 ((str = ""C12"))).first;
//     AtomType::a"C13 = *repository.insert (new A"C13 ((str = ""C13"))).first;
//     AtomType::a"C14 = *repository.insert (new A"C14 ((str = ""C14"))).first;
//     AtomType::a"C15 = *repository.insert (new A"C15 ((str = ""C15"))).first;
//     AtomType::a"C16 = *repository.insert (new A"C16 ((str = ""C16"))).first;
//     AtomType::a"C17 = *repository.insert (new A"C17 ((str = ""C17"))).first;
//     AtomType::a"C18 = *repository.insert (new A"C18 ((str = ""C18"))).first;
//     AtomType::a"C19 = *repository.insert (new A"C19 ((str = ""C19"))).first;
//     AtomType::a"C20 = *repository.insert (new A"C20 ((str = ""C20"))).first;
//     AtomType::a"HO4 = *repository.insert (new A"HO4 ((str = ""HO4"))).first;
//     AtomType::a*1H = *repository.insert (new A*1H ((str = "*1H"))).first;
//     AtomType::a*2H = *repository.insert (new A*2H ((str = "*2H"))).first;
//     AtomType::a*3H = *repository.insert (new A*3H ((str = "*3H"))).first;
//     AtomType::a*C = *repository.insert (new A*C ((str = "*C"))).first;
//     AtomType::a*C1 = *repository.insert (new A*C1 ((str = "*C1"))).first;
//     AtomType::a*C1* = *repository.insert (new A*C1* ((str = "*C1*"))).first;
//     AtomType::a*C10 = *repository.insert (new A*C10 ((str = "*C10"))).first;
//     AtomType::a*C11 = *repository.insert (new A*C11 ((str = "*C11"))).first;
//     AtomType::a*C12 = *repository.insert (new A*C12 ((str = "*C12"))).first;
//     AtomType::a*C13 = *repository.insert (new A*C13 ((str = "*C13"))).first;
//     AtomType::a*C14 = *repository.insert (new A*C14 ((str = "*C14"))).first;
//     AtomType::a*C15 = *repository.insert (new A*C15 ((str = "*C15"))).first;
//     AtomType::a*C16 = *repository.insert (new A*C16 ((str = "*C16"))).first;
//     AtomType::a*C17 = *repository.insert (new A*C17 ((str = "*C17"))).first;
//     AtomType::a*C18 = *repository.insert (new A*C18 ((str = "*C18"))).first;
//     AtomType::a*C19 = *repository.insert (new A*C19 ((str = "*C19"))).first;
//     AtomType::a*C2 = *repository.insert (new A*C2 ((str = "*C2"))).first;
//     AtomType::a*C2* = *repository.insert (new A*C2* ((str = "*C2*"))).first;
//     AtomType::a*C20 = *repository.insert (new A*C20 ((str = "*C20"))).first;
//     AtomType::a*C21 = *repository.insert (new A*C21 ((str = "*C21"))).first;
//     AtomType::a*C22 = *repository.insert (new A*C22 ((str = "*C22"))).first;
//     AtomType::a*C23 = *repository.insert (new A*C23 ((str = "*C23"))).first;
//     AtomType::a*C24 = *repository.insert (new A*C24 ((str = "*C24"))).first;
//     AtomType::a*C25 = *repository.insert (new A*C25 ((str = "*C25"))).first;
//     AtomType::a*C26 = *repository.insert (new A*C26 ((str = "*C26"))).first;
//     AtomType::a*C3 = *repository.insert (new A*C3 ((str = "*C3"))).first;
//     AtomType::a*C3* = *repository.insert (new A*C3* ((str = "*C3*"))).first;
//     AtomType::a*C4 = *repository.insert (new A*C4 ((str = "*C4"))).first;
//     AtomType::a*C4* = *repository.insert (new A*C4* ((str = "*C4*"))).first;
//     AtomType::a*C5 = *repository.insert (new A*C5 ((str = "*C5"))).first;
//     AtomType::a*C5* = *repository.insert (new A*C5* ((str = "*C5*"))).first;
//     AtomType::a*C6 = *repository.insert (new A*C6 ((str = "*C6"))).first;
//     AtomType::a*C6* = *repository.insert (new A*C6* ((str = "*C6*"))).first;
//     AtomType::a*C7 = *repository.insert (new A*C7 ((str = "*C7"))).first;
//     AtomType::a*C7* = *repository.insert (new A*C7* ((str = "*C7*"))).first;
//     AtomType::a*C8 = *repository.insert (new A*C8 ((str = "*C8"))).first;
//     AtomType::a*C8* = *repository.insert (new A*C8* ((str = "*C8*"))).first;
//     AtomType::a*C9 = *repository.insert (new A*C9 ((str = "*C9"))).first;
//     AtomType::a*C9A = *repository.insert (new A*C9A ((str = "*C9A"))).first;
//     AtomType::a*C9B = *repository.insert (new A*C9B ((str = "*C9B"))).first;
//     AtomType::a*CD1 = *repository.insert (new A*CD1 ((str = "*CD1"))).first;
//     AtomType::a*CD2 = *repository.insert (new A*CD2 ((str = "*CD2"))).first;
//     AtomType::a*CD3 = *repository.insert (new A*CD3 ((str = "*CD3"))).first;
//     AtomType::a*CD7 = *repository.insert (new A*CD7 ((str = "*CD7"))).first;
//     AtomType::a*CD8 = *repository.insert (new A*CD8 ((str = "*CD8"))).first;
//     AtomType::a*CE1 = *repository.insert (new A*CE1 ((str = "*CE1"))).first;
//     AtomType::a*CE2 = *repository.insert (new A*CE2 ((str = "*CE2"))).first;
//     AtomType::a*CE3 = *repository.insert (new A*CE3 ((str = "*CE3"))).first;
//     AtomType::a*CE4 = *repository.insert (new A*CE4 ((str = "*CE4"))).first;
//     AtomType::a*CP1 = *repository.insert (new A*CP1 ((str = "*CP1"))).first;
//     AtomType::a*CP2 = *repository.insert (new A*CP2 ((str = "*CP2"))).first;
//     AtomType::a*CP3 = *repository.insert (new A*CP3 ((str = "*CP3"))).first;
//     AtomType::a*CP4 = *repository.insert (new A*CP4 ((str = "*CP4"))).first;
//     AtomType::a*CP5 = *repository.insert (new A*CP5 ((str = "*CP5"))).first;
//     AtomType::a*CP6 = *repository.insert (new A*CP6 ((str = "*CP6"))).first;
//     AtomType::a*H = *repository.insert (new A*H ((str = "*H"))).first;
//     AtomType::a*H1 = *repository.insert (new A*H1 ((str = "*H1"))).first;
//     AtomType::a*H1* = *repository.insert (new A*H1* ((str = "*H1*"))).first;
//     AtomType::a*H10 = *repository.insert (new A*H10 ((str = "*H10"))).first;
//     AtomType::a*H11 = *repository.insert (new A*H11 ((str = "*H11"))).first;
//     AtomType::a*H12 = *repository.insert (new A*H12 ((str = "*H12"))).first;
//     AtomType::a*H14 = *repository.insert (new A*H14 ((str = "*H14"))).first;
//     AtomType::a*H15 = *repository.insert (new A*H15 ((str = "*H15"))).first;
//     AtomType::a*H17 = *repository.insert (new A*H17 ((str = "*H17"))).first;
//     AtomType::a*H18 = *repository.insert (new A*H18 ((str = "*H18"))).first;
//     AtomType::a*H19 = *repository.insert (new A*H19 ((str = "*H19"))).first;
//     AtomType::a*H1A = *repository.insert (new A*H1A ((str = "*H1A"))).first;
//     AtomType::a*H1G = *repository.insert (new A*H1G ((str = "*H1G"))).first;
//     AtomType::a*H1U = *repository.insert (new A*H1U ((str = "*H1U"))).first;
//     AtomType::a*H2 = *repository.insert (new A*H2 ((str = "*H2"))).first;
//     AtomType::a*H25 = *repository.insert (new A*H25 ((str = "*H25"))).first;
//     AtomType::a*H2A = *repository.insert (new A*H2A ((str = "*H2A"))).first;
//     AtomType::a*H2G = *repository.insert (new A*H2G ((str = "*H2G"))).first;
//     AtomType::a*H2U = *repository.insert (new A*H2U ((str = "*H2U"))).first;
//     AtomType::a*H3 = *repository.insert (new A*H3 ((str = "*H3"))).first;
//     AtomType::a*H3* = *repository.insert (new A*H3* ((str = "*H3*"))).first;
//     AtomType::a*H3A = *repository.insert (new A*H3A ((str = "*H3A"))).first;
//     AtomType::a*H3G = *repository.insert (new A*H3G ((str = "*H3G"))).first;
//     AtomType::a*H3U = *repository.insert (new A*H3U ((str = "*H3U"))).first;
//     AtomType::a*H4* = *repository.insert (new A*H4* ((str = "*H4*"))).first;
//     AtomType::a*H4A = *repository.insert (new A*H4A ((str = "*H4A"))).first;
//     AtomType::a*H4G = *repository.insert (new A*H4G ((str = "*H4G"))).first;
//     AtomType::a*H4U = *repository.insert (new A*H4U ((str = "*H4U"))).first;
//     AtomType::a*H5 = *repository.insert (new A*H5 ((str = "*H5"))).first;
//     AtomType::a*H5* = *repository.insert (new A*H5* ((str = "*H5*"))).first;
//     AtomType::a*H6 = *repository.insert (new A*H6 ((str = "*H6"))).first;
//     AtomType::a*H7 = *repository.insert (new A*H7 ((str = "*H7"))).first;
//     AtomType::a*H8 = *repository.insert (new A*H8 ((str = "*H8"))).first;
//     AtomType::a*H9 = *repository.insert (new A*H9 ((str = "*H9"))).first;
//     AtomType::a*H9A = *repository.insert (new A*H9A ((str = "*H9A"))).first;
//     AtomType::a*H9B = *repository.insert (new A*H9B ((str = "*H9B"))).first;
//     AtomType::a*HC2 = *repository.insert (new A*HC2 ((str = "*HC2"))).first;
//     AtomType::a*HC3 = *repository.insert (new A*HC3 ((str = "*HC3"))).first;
//     AtomType::a*HC6 = *repository.insert (new A*HC6 ((str = "*HC6"))).first;
//     AtomType::a*HD1 = *repository.insert (new A*HD1 ((str = "*HD1"))).first;
//     AtomType::a*HN1 = *repository.insert (new A*HN1 ((str = "*HN1"))).first;
//     AtomType::a*HN2 = *repository.insert (new A*HN2 ((str = "*HN2"))).first;
//     AtomType::a*HN3 = *repository.insert (new A*HN3 ((str = "*HN3"))).first;
//     AtomType::a*HN4 = *repository.insert (new A*HN4 ((str = "*HN4"))).first;
//     AtomType::a*HN7 = *repository.insert (new A*HN7 ((str = "*HN7"))).first;
//     AtomType::a*HN8 = *repository.insert (new A*HN8 ((str = "*HN8"))).first;
//     AtomType::a*HO1 = *repository.insert (new A*HO1 ((str = "*HO1"))).first;
//     AtomType::a*HO4 = *repository.insert (new A*HO4 ((str = "*HO4"))).first;
//     AtomType::a*HO5 = *repository.insert (new A*HO5 ((str = "*HO5"))).first;
//     AtomType::a*HO6 = *repository.insert (new A*HO6 ((str = "*HO6"))).first;
//     AtomType::a*HO7 = *repository.insert (new A*HO7 ((str = "*HO7"))).first;
//     AtomType::a*HO8 = *repository.insert (new A*HO8 ((str = "*HO8"))).first;
//     AtomType::a*HP2 = *repository.insert (new A*HP2 ((str = "*HP2"))).first;
//     AtomType::a*HP3 = *repository.insert (new A*HP3 ((str = "*HP3"))).first;
//     AtomType::a*HP4 = *repository.insert (new A*HP4 ((str = "*HP4"))).first;
//     AtomType::a*HP5 = *repository.insert (new A*HP5 ((str = "*HP5"))).first;
//     AtomType::a*HP6 = *repository.insert (new A*HP6 ((str = "*HP6"))).first;
//     AtomType::a*HS3 = *repository.insert (new A*HS3 ((str = "*HS3"))).first;
//     AtomType::a*N = *repository.insert (new A*N ((str = "*N"))).first;
//     AtomType::a*N1 = *repository.insert (new A*N1 ((str = "*N1"))).first;
//     AtomType::a*N10 = *repository.insert (new A*N10 ((str = "*N10"))).first;
//     AtomType::a*N13 = *repository.insert (new A*N13 ((str = "*N13"))).first;
//     AtomType::a*N19 = *repository.insert (new A*N19 ((str = "*N19"))).first;
//     AtomType::a*N20 = *repository.insert (new A*N20 ((str = "*N20"))).first;
//     AtomType::a*N24 = *repository.insert (new A*N24 ((str = "*N24"))).first;
//     AtomType::a*N27 = *repository.insert (new A*N27 ((str = "*N27"))).first;
//     AtomType::a*N3* = *repository.insert (new A*N3* ((str = "*N3*"))).first;
//     AtomType::a*N4* = *repository.insert (new A*N4* ((str = "*N4*"))).first;
//     AtomType::a*N8 = *repository.insert (new A*N8 ((str = "*N8"))).first;
//     AtomType::a*N9 = *repository.insert (new A*N9 ((str = "*N9"))).first;
//     AtomType::a*ND1 = *repository.insert (new A*ND1 ((str = "*ND1"))).first;
//     AtomType::a*ND2 = *repository.insert (new A*ND2 ((str = "*ND2"))).first;
//     AtomType::a*O = *repository.insert (new A*O ((str = "*O"))).first;
//     AtomType::a*O10 = *repository.insert (new A*O10 ((str = "*O10"))).first;
//     AtomType::a*O12 = *repository.insert (new A*O12 ((str = "*O12"))).first;
//     AtomType::a*O13 = *repository.insert (new A*O13 ((str = "*O13"))).first;
//     AtomType::a*O17 = *repository.insert (new A*O17 ((str = "*O17"))).first;
//     AtomType::a*O18 = *repository.insert (new A*O18 ((str = "*O18"))).first;
//     AtomType::a*O19 = *repository.insert (new A*O19 ((str = "*O19"))).first;
//     AtomType::a*O1A = *repository.insert (new A*O1A ((str = "*O1A"))).first;
//     AtomType::a*O1B = *repository.insert (new A*O1B ((str = "*O1B"))).first;
//     AtomType::a*O21 = *repository.insert (new A*O21 ((str = "*O21"))).first;
//     AtomType::a*O3* = *repository.insert (new A*O3* ((str = "*O3*"))).first;
//     AtomType::a*O4 = *repository.insert (new A*O4 ((str = "*O4"))).first;
//     AtomType::a*O4* = *repository.insert (new A*O4* ((str = "*O4*"))).first;
//     AtomType::a*O5* = *repository.insert (new A*O5* ((str = "*O5*"))).first;
//     AtomType::a*O6 = *repository.insert (new A*O6 ((str = "*O6"))).first;
//     AtomType::a*O7A = *repository.insert (new A*O7A ((str = "*O7A"))).first;
//     AtomType::a*O7B = *repository.insert (new A*O7B ((str = "*O7B"))).first;
//     AtomType::a*O8 = *repository.insert (new A*O8 ((str = "*O8"))).first;
//     AtomType::a*OD1 = *repository.insert (new A*OD1 ((str = "*OD1"))).first;
//     AtomType::a0 = *repository.insert (new A0 ((str = "0"))).first;
//     AtomType::a0CT1 = *repository.insert (new A0CT1 ((str = "0CT1"))).first;
//     AtomType::a0H1 = *repository.insert (new A0H1 ((str = "0H1"))).first;
//     AtomType::a0HO1 = *repository.insert (new A0HO1 ((str = "0HO1"))).first;
//     AtomType::a0HO2 = *repository.insert (new A0HO2 ((str = "0HO2"))).first;
//     AtomType::a0HO7 = *repository.insert (new A0HO7 ((str = "0HO7"))).first;
//     AtomType::a0HPA = *repository.insert (new A0HPA ((str = "0HPA"))).first;
//     AtomType::a0HT1 = *repository.insert (new A0HT1 ((str = "0HT1"))).first;
//     AtomType::a10H = *repository.insert (new A10H ((str = "10H"))).first;
//     AtomType::a10OH = *repository.insert (new A10OH ((str = "10OH"))).first;
//     AtomType::a11HO = *repository.insert (new A11HO ((str = "11HO"))).first;
//     AtomType::a17HS = *repository.insert (new A17HS ((str = "17HS"))).first;
//     AtomType::a1BH = *repository.insert (new A1BH ((str = "1BH"))).first;
//     AtomType::a1C = *repository.insert (new A1C ((str = "1C"))).first;
//     AtomType::a1C0 = *repository.insert (new A1C0 ((str = "1C0"))).first;
//     AtomType::a1C1 = *repository.insert (new A1C1 ((str = "1C1"))).first;
//     AtomType::a1C10 = *repository.insert (new A1C10 ((str = "1C10"))).first;
//     AtomType::a1C11 = *repository.insert (new A1C11 ((str = "1C11"))).first;
//     AtomType::a1C12 = *repository.insert (new A1C12 ((str = "1C12"))).first;
//     AtomType::a1C13 = *repository.insert (new A1C13 ((str = "1C13"))).first;
//     AtomType::a1C2 = *repository.insert (new A1C2 ((str = "1C2"))).first;
//     AtomType::a1C22 = *repository.insert (new A1C22 ((str = "1C22"))).first;
//     AtomType::a1C3 = *repository.insert (new A1C3 ((str = "1C3"))).first;
//     AtomType::a1C4 = *repository.insert (new A1C4 ((str = "1C4"))).first;
//     AtomType::a1C5 = *repository.insert (new A1C5 ((str = "1C5"))).first;
//     AtomType::a1C6 = *repository.insert (new A1C6 ((str = "1C6"))).first;
//     AtomType::a1C6A = *repository.insert (new A1C6A ((str = "1C6A"))).first;
//     AtomType::a1C6B = *repository.insert (new A1C6B ((str = "1C6B"))).first;
//     AtomType::a1C7 = *repository.insert (new A1C7 ((str = "1C7"))).first;
//     AtomType::a1C8 = *repository.insert (new A1C8 ((str = "1C8"))).first;
//     AtomType::a1C9 = *repository.insert (new A1C9 ((str = "1C9"))).first;
//     AtomType::a1CA = *repository.insert (new A1CA ((str = "1CA"))).first;
//     AtomType::a1CB = *repository.insert (new A1CB ((str = "1CB"))).first;
//     AtomType::a1CD = *repository.insert (new A1CD ((str = "1CD"))).first;
//     AtomType::a1CD1 = *repository.insert (new A1CD1 ((str = "1CD1"))).first;
//     AtomType::a1CD2 = *repository.insert (new A1CD2 ((str = "1CD2"))).first;
//     AtomType::a1CD3 = *repository.insert (new A1CD3 ((str = "1CD3"))).first;
//     AtomType::a1CD4 = *repository.insert (new A1CD4 ((str = "1CD4"))).first;
//     AtomType::a1CD6 = *repository.insert (new A1CD6 ((str = "1CD6"))).first;
//     AtomType::a1CE1 = *repository.insert (new A1CE1 ((str = "1CE1"))).first;
//     AtomType::a1CE2 = *repository.insert (new A1CE2 ((str = "1CE2"))).first;
//     AtomType::a1CE3 = *repository.insert (new A1CE3 ((str = "1CE3"))).first;
//     AtomType::a1CE4 = *repository.insert (new A1CE4 ((str = "1CE4"))).first;
//     AtomType::a1CE6 = *repository.insert (new A1CE6 ((str = "1CE6"))).first;
//     AtomType::a1CEM = *repository.insert (new A1CEM ((str = "1CEM"))).first;
//     AtomType::a1CG = *repository.insert (new A1CG ((str = "1CG"))).first;
//     AtomType::a1CG2 = *repository.insert (new A1CG2 ((str = "1CG2"))).first;
//     AtomType::a1CG5 = *repository.insert (new A1CG5 ((str = "1CG5"))).first;
//     AtomType::a1CH3 = *repository.insert (new A1CH3 ((str = "1CH3"))).first;
//     AtomType::a1CZ = *repository.insert (new A1CZ ((str = "1CZ"))).first;
//     AtomType::a1D = *repository.insert (new A1D ((str = "1D"))).first;
//     AtomType::a1D10 = *repository.insert (new A1D10 ((str = "1D10"))).first;
//     AtomType::a1D14 = *repository.insert (new A1D14 ((str = "1D14"))).first;
//     AtomType::a1D2 = *repository.insert (new A1D2 ((str = "1D2"))).first;
//     AtomType::a1D3 = *repository.insert (new A1D3 ((str = "1D3"))).first;
//     AtomType::a1H = *repository.insert (new A1H ((str = "1H"))).first;
//     AtomType::a1H" = *repository.insert (new A1H" ((str = "1H""))).first;
//     AtomType::a1H* = *repository.insert (new A1H* ((str = "1H*"))).first;
//     AtomType::a1H** = *repository.insert (new A1H** ((str = "1H**"))).first;
//     AtomType::a1H*0 = *repository.insert (new A1H*0 ((str = "1H*0"))).first;
//     AtomType::a1H*1 = *repository.insert (new A1H*1 ((str = "1H*1"))).first;
//     AtomType::a1H*2 = *repository.insert (new A1H*2 ((str = "1H*2"))).first;
//     AtomType::a1H*3 = *repository.insert (new A1H*3 ((str = "1H*3"))).first;
//     AtomType::a1H*4 = *repository.insert (new A1H*4 ((str = "1H*4"))).first;
//     AtomType::a1H*5 = *repository.insert (new A1H*5 ((str = "1H*5"))).first;
//     AtomType::a1H*7 = *repository.insert (new A1H*7 ((str = "1H*7"))).first;
//     AtomType::a1H*8 = *repository.insert (new A1H*8 ((str = "1H*8"))).first;
//     AtomType::a1H*A = *repository.insert (new A1H*A ((str = "1H*A"))).first;
//     AtomType::a1H*C = *repository.insert (new A1H*C ((str = "1H*C"))).first;
//     AtomType::a1H0 = *repository.insert (new A1H0 ((str = "1H0"))).first;
//     AtomType::a1H0* = *repository.insert (new A1H0* ((str = "1H0*"))).first;
//     AtomType::a1H01 = *repository.insert (new A1H01 ((str = "1H01"))).first;
//     AtomType::a1H02 = *repository.insert (new A1H02 ((str = "1H02"))).first;
//     AtomType::a1H03 = *repository.insert (new A1H03 ((str = "1H03"))).first;
//     AtomType::a1H04 = *repository.insert (new A1H04 ((str = "1H04"))).first;
//     AtomType::a1H05 = *repository.insert (new A1H05 ((str = "1H05"))).first;
//     AtomType::a1H06 = *repository.insert (new A1H06 ((str = "1H06"))).first;
//     AtomType::a1H07 = *repository.insert (new A1H07 ((str = "1H07"))).first;
//     AtomType::a1H08 = *repository.insert (new A1H08 ((str = "1H08"))).first;
//     AtomType::a1H09 = *repository.insert (new A1H09 ((str = "1H09"))).first;
//     AtomType::a1H0A = *repository.insert (new A1H0A ((str = "1H0A"))).first;
//     AtomType::a1H0B = *repository.insert (new A1H0B ((str = "1H0B"))).first;
//     AtomType::a1H0C = *repository.insert (new A1H0C ((str = "1H0C"))).first;
//     AtomType::a1H0E = *repository.insert (new A1H0E ((str = "1H0E"))).first;
//     AtomType::a1H0I = *repository.insert (new A1H0I ((str = "1H0I"))).first;
//     AtomType::a1H0J = *repository.insert (new A1H0J ((str = "1H0J"))).first;
//     AtomType::a1H0K = *repository.insert (new A1H0K ((str = "1H0K"))).first;
//     AtomType::a1H0N = *repository.insert (new A1H0N ((str = "1H0N"))).first;
//     AtomType::a1H0P = *repository.insert (new A1H0P ((str = "1H0P"))).first;
//     AtomType::a1H0Q = *repository.insert (new A1H0Q ((str = "1H0Q"))).first;
//     AtomType::a1H0R = *repository.insert (new A1H0R ((str = "1H0R"))).first;
//     AtomType::a1H0S = *repository.insert (new A1H0S ((str = "1H0S"))).first;
//     AtomType::a1H0T = *repository.insert (new A1H0T ((str = "1H0T"))).first;
//     AtomType::a1H0X = *repository.insert (new A1H0X ((str = "1H0X"))).first;
//     AtomType::a1H1 = *repository.insert (new A1H1 ((str = "1H1"))).first;
//     AtomType::a1H1" = *repository.insert (new A1H1" ((str = "1H1""))).first;
//     AtomType::a1H1* = *repository.insert (new A1H1* ((str = "1H1*"))).first;
//     AtomType::a1H10 = *repository.insert (new A1H10 ((str = "1H10"))).first;
//     AtomType::a1H10A = *repository.insert (new A1H10A ((str = "1H10A"))).first;
//     AtomType::a1H10B = *repository.insert (new A1H10B ((str = "1H10B"))).first;
//     AtomType::a1H11 = *repository.insert (new A1H11 ((str = "1H11"))).first;
//     AtomType::a1H11A = *repository.insert (new A1H11A ((str = "1H11A"))).first;
//     AtomType::a1H11B = *repository.insert (new A1H11B ((str = "1H11B"))).first;
//     AtomType::a1H12 = *repository.insert (new A1H12 ((str = "1H12"))).first;
//     AtomType::a1H12A = *repository.insert (new A1H12A ((str = "1H12A"))).first;
//     AtomType::a1H12B = *repository.insert (new A1H12B ((str = "1H12B"))).first;
//     AtomType::a1H13 = *repository.insert (new A1H13 ((str = "1H13"))).first;
//     AtomType::a1H13A = *repository.insert (new A1H13A ((str = "1H13A"))).first;
//     AtomType::a1H13B = *repository.insert (new A1H13B ((str = "1H13B"))).first;
//     AtomType::a1H14 = *repository.insert (new A1H14 ((str = "1H14"))).first;
//     AtomType::a1H14A = *repository.insert (new A1H14A ((str = "1H14A"))).first;
//     AtomType::a1H14B = *repository.insert (new A1H14B ((str = "1H14B"))).first;
//     AtomType::a1H15 = *repository.insert (new A1H15 ((str = "1H15"))).first;
//     AtomType::a1H15* = *repository.insert (new A1H15* ((str = "1H15*"))).first;
//     AtomType::a1H15B = *repository.insert (new A1H15B ((str = "1H15B"))).first;
//     AtomType::a1H16 = *repository.insert (new A1H16 ((str = "1H16"))).first;
//     AtomType::a1H16B = *repository.insert (new A1H16B ((str = "1H16B"))).first;
//     AtomType::a1H17 = *repository.insert (new A1H17 ((str = "1H17"))).first;
//     AtomType::a1H18 = *repository.insert (new A1H18 ((str = "1H18"))).first;
//     AtomType::a1H19 = *repository.insert (new A1H19 ((str = "1H19"))).first;
//     AtomType::a1H1A = *repository.insert (new A1H1A ((str = "1H1A"))).first;
//     AtomType::a1H1B = *repository.insert (new A1H1B ((str = "1H1B"))).first;
//     AtomType::a1H1C = *repository.insert (new A1H1C ((str = "1H1C"))).first;
//     AtomType::a1H1D = *repository.insert (new A1H1D ((str = "1H1D"))).first;
//     AtomType::a1H1E = *repository.insert (new A1H1E ((str = "1H1E"))).first;
//     AtomType::a1H1F = *repository.insert (new A1H1F ((str = "1H1F"))).first;
//     AtomType::a1H1G = *repository.insert (new A1H1G ((str = "1H1G"))).first;
//     AtomType::a1H1H = *repository.insert (new A1H1H ((str = "1H1H"))).first;
//     AtomType::a1H1I = *repository.insert (new A1H1I ((str = "1H1I"))).first;
//     AtomType::a1H1J = *repository.insert (new A1H1J ((str = "1H1J"))).first;
//     AtomType::a1H1K = *repository.insert (new A1H1K ((str = "1H1K"))).first;
//     AtomType::a1H1L = *repository.insert (new A1H1L ((str = "1H1L"))).first;
//     AtomType::a1H1M = *repository.insert (new A1H1M ((str = "1H1M"))).first;
//     AtomType::a1H1N = *repository.insert (new A1H1N ((str = "1H1N"))).first;
//     AtomType::a1H1O = *repository.insert (new A1H1O ((str = "1H1O"))).first;
//     AtomType::a1H1P = *repository.insert (new A1H1P ((str = "1H1P"))).first;
//     AtomType::a1H1Q = *repository.insert (new A1H1Q ((str = "1H1Q"))).first;
//     AtomType::a1H1R = *repository.insert (new A1H1R ((str = "1H1R"))).first;
//     AtomType::a1H1S = *repository.insert (new A1H1S ((str = "1H1S"))).first;
//     AtomType::a1H1T = *repository.insert (new A1H1T ((str = "1H1T"))).first;
//     AtomType::a1H1V = *repository.insert (new A1H1V ((str = "1H1V"))).first;
//     AtomType::a1H1X = *repository.insert (new A1H1X ((str = "1H1X"))).first;
//     AtomType::a1H1Y = *repository.insert (new A1H1Y ((str = "1H1Y"))).first;
//     AtomType::a1H2 = *repository.insert (new A1H2 ((str = "1H2"))).first;
//     AtomType::a1H2" = *repository.insert (new A1H2" ((str = "1H2""))).first;
//     AtomType::a1H2* = *repository.insert (new A1H2* ((str = "1H2*"))).first;
//     AtomType::a1H20 = *repository.insert (new A1H20 ((str = "1H20"))).first;
//     AtomType::a1H21 = *repository.insert (new A1H21 ((str = "1H21"))).first;
//     AtomType::a1H22 = *repository.insert (new A1H22 ((str = "1H22"))).first;
//     AtomType::a1H23 = *repository.insert (new A1H23 ((str = "1H23"))).first;
//     AtomType::a1H24 = *repository.insert (new A1H24 ((str = "1H24"))).first;
//     AtomType::a1H25 = *repository.insert (new A1H25 ((str = "1H25"))).first;
//     AtomType::a1H25* = *repository.insert (new A1H25* ((str = "1H25*"))).first;
//     AtomType::a1H26 = *repository.insert (new A1H26 ((str = "1H26"))).first;
//     AtomType::a1H27 = *repository.insert (new A1H27 ((str = "1H27"))).first;
//     AtomType::a1H28 = *repository.insert (new A1H28 ((str = "1H28"))).first;
//     AtomType::a1H29 = *repository.insert (new A1H29 ((str = "1H29"))).first;
//     AtomType::a1H2A = *repository.insert (new A1H2A ((str = "1H2A"))).first;
//     AtomType::a1H2B = *repository.insert (new A1H2B ((str = "1H2B"))).first;
//     AtomType::a1H2C = *repository.insert (new A1H2C ((str = "1H2C"))).first;
//     AtomType::a1H2D = *repository.insert (new A1H2D ((str = "1H2D"))).first;
//     AtomType::a1H2E = *repository.insert (new A1H2E ((str = "1H2E"))).first;
//     AtomType::a1H2F = *repository.insert (new A1H2F ((str = "1H2F"))).first;
//     AtomType::a1H2G = *repository.insert (new A1H2G ((str = "1H2G"))).first;
//     AtomType::a1H2H = *repository.insert (new A1H2H ((str = "1H2H"))).first;
//     AtomType::a1H2I = *repository.insert (new A1H2I ((str = "1H2I"))).first;
//     AtomType::a1H2J = *repository.insert (new A1H2J ((str = "1H2J"))).first;
//     AtomType::a1H2K = *repository.insert (new A1H2K ((str = "1H2K"))).first;
//     AtomType::a1H2L = *repository.insert (new A1H2L ((str = "1H2L"))).first;
//     AtomType::a1H2M = *repository.insert (new A1H2M ((str = "1H2M"))).first;
//     AtomType::a1H2N = *repository.insert (new A1H2N ((str = "1H2N"))).first;
//     AtomType::a1H2O = *repository.insert (new A1H2O ((str = "1H2O"))).first;
//     AtomType::a1H2P = *repository.insert (new A1H2P ((str = "1H2P"))).first;
//     AtomType::a1H2R = *repository.insert (new A1H2R ((str = "1H2R"))).first;
//     AtomType::a1H2S = *repository.insert (new A1H2S ((str = "1H2S"))).first;
//     AtomType::a1H2T = *repository.insert (new A1H2T ((str = "1H2T"))).first;
//     AtomType::a1H2V = *repository.insert (new A1H2V ((str = "1H2V"))).first;
//     AtomType::a1H2X = *repository.insert (new A1H2X ((str = "1H2X"))).first;
//     AtomType::a1H2Y = *repository.insert (new A1H2Y ((str = "1H2Y"))).first;
//     AtomType::a1H2Z = *repository.insert (new A1H2Z ((str = "1H2Z"))).first;
//     AtomType::a1H3 = *repository.insert (new A1H3 ((str = "1H3"))).first;
//     AtomType::a1H3" = *repository.insert (new A1H3" ((str = "1H3""))).first;
//     AtomType::a1H3* = *repository.insert (new A1H3* ((str = "1H3*"))).first;
//     AtomType::a1H30 = *repository.insert (new A1H30 ((str = "1H30"))).first;
//     AtomType::a1H31 = *repository.insert (new A1H31 ((str = "1H31"))).first;
//     AtomType::a1H32 = *repository.insert (new A1H32 ((str = "1H32"))).first;
//     AtomType::a1H33 = *repository.insert (new A1H33 ((str = "1H33"))).first;
//     AtomType::a1H34 = *repository.insert (new A1H34 ((str = "1H34"))).first;
//     AtomType::a1H35 = *repository.insert (new A1H35 ((str = "1H35"))).first;
//     AtomType::a1H36 = *repository.insert (new A1H36 ((str = "1H36"))).first;
//     AtomType::a1H37 = *repository.insert (new A1H37 ((str = "1H37"))).first;
//     AtomType::a1H38 = *repository.insert (new A1H38 ((str = "1H38"))).first;
//     AtomType::a1H39 = *repository.insert (new A1H39 ((str = "1H39"))).first;
//     AtomType::a1H3A = *repository.insert (new A1H3A ((str = "1H3A"))).first;
//     AtomType::a1H3B = *repository.insert (new A1H3B ((str = "1H3B"))).first;
//     AtomType::a1H3C = *repository.insert (new A1H3C ((str = "1H3C"))).first;
//     AtomType::a1H3D = *repository.insert (new A1H3D ((str = "1H3D"))).first;
//     AtomType::a1H3E = *repository.insert (new A1H3E ((str = "1H3E"))).first;
//     AtomType::a1H3F = *repository.insert (new A1H3F ((str = "1H3F"))).first;
//     AtomType::a1H3G = *repository.insert (new A1H3G ((str = "1H3G"))).first;
//     AtomType::a1H3H = *repository.insert (new A1H3H ((str = "1H3H"))).first;
//     AtomType::a1H3I = *repository.insert (new A1H3I ((str = "1H3I"))).first;
//     AtomType::a1H3J = *repository.insert (new A1H3J ((str = "1H3J"))).first;
//     AtomType::a1H3K = *repository.insert (new A1H3K ((str = "1H3K"))).first;
//     AtomType::a1H3L = *repository.insert (new A1H3L ((str = "1H3L"))).first;
//     AtomType::a1H3M = *repository.insert (new A1H3M ((str = "1H3M"))).first;
//     AtomType::a1H3N = *repository.insert (new A1H3N ((str = "1H3N"))).first;
//     AtomType::a1H3O = *repository.insert (new A1H3O ((str = "1H3O"))).first;
//     AtomType::a1H3P = *repository.insert (new A1H3P ((str = "1H3P"))).first;
//     AtomType::a1H3R = *repository.insert (new A1H3R ((str = "1H3R"))).first;
//     AtomType::a1H3S = *repository.insert (new A1H3S ((str = "1H3S"))).first;
//     AtomType::a1H3T = *repository.insert (new A1H3T ((str = "1H3T"))).first;
//     AtomType::a1H3U = *repository.insert (new A1H3U ((str = "1H3U"))).first;
//     AtomType::a1H3X = *repository.insert (new A1H3X ((str = "1H3X"))).first;
//     AtomType::a1H4 = *repository.insert (new A1H4 ((str = "1H4"))).first;
//     AtomType::a1H4" = *repository.insert (new A1H4" ((str = "1H4""))).first;
//     AtomType::a1H4* = *repository.insert (new A1H4* ((str = "1H4*"))).first;
//     AtomType::a1H40 = *repository.insert (new A1H40 ((str = "1H40"))).first;
//     AtomType::a1H41 = *repository.insert (new A1H41 ((str = "1H41"))).first;
//     AtomType::a1H42 = *repository.insert (new A1H42 ((str = "1H42"))).first;
//     AtomType::a1H43 = *repository.insert (new A1H43 ((str = "1H43"))).first;
//     AtomType::a1H44 = *repository.insert (new A1H44 ((str = "1H44"))).first;
//     AtomType::a1H45 = *repository.insert (new A1H45 ((str = "1H45"))).first;
//     AtomType::a1H46 = *repository.insert (new A1H46 ((str = "1H46"))).first;
//     AtomType::a1H47 = *repository.insert (new A1H47 ((str = "1H47"))).first;
//     AtomType::a1H48 = *repository.insert (new A1H48 ((str = "1H48"))).first;
//     AtomType::a1H49 = *repository.insert (new A1H49 ((str = "1H49"))).first;
//     AtomType::a1H4A = *repository.insert (new A1H4A ((str = "1H4A"))).first;
//     AtomType::a1H4B = *repository.insert (new A1H4B ((str = "1H4B"))).first;
//     AtomType::a1H4C = *repository.insert (new A1H4C ((str = "1H4C"))).first;
//     AtomType::a1H4D = *repository.insert (new A1H4D ((str = "1H4D"))).first;
//     AtomType::a1H4E = *repository.insert (new A1H4E ((str = "1H4E"))).first;
//     AtomType::a1H4F = *repository.insert (new A1H4F ((str = "1H4F"))).first;
//     AtomType::a1H4G = *repository.insert (new A1H4G ((str = "1H4G"))).first;
//     AtomType::a1H4H = *repository.insert (new A1H4H ((str = "1H4H"))).first;
//     AtomType::a1H4I = *repository.insert (new A1H4I ((str = "1H4I"))).first;
//     AtomType::a1H4J = *repository.insert (new A1H4J ((str = "1H4J"))).first;
//     AtomType::a1H4M = *repository.insert (new A1H4M ((str = "1H4M"))).first;
//     AtomType::a1H4N = *repository.insert (new A1H4N ((str = "1H4N"))).first;
//     AtomType::a1H4O = *repository.insert (new A1H4O ((str = "1H4O"))).first;
//     AtomType::a1H4P = *repository.insert (new A1H4P ((str = "1H4P"))).first;
//     AtomType::a1H4R = *repository.insert (new A1H4R ((str = "1H4R"))).first;
//     AtomType::a1H4S = *repository.insert (new A1H4S ((str = "1H4S"))).first;
//     AtomType::a1H4T = *repository.insert (new A1H4T ((str = "1H4T"))).first;
//     AtomType::a1H4X = *repository.insert (new A1H4X ((str = "1H4X"))).first;
//     AtomType::a1H5 = *repository.insert (new A1H5 ((str = "1H5"))).first;
//     AtomType::a1H5" = *repository.insert (new A1H5" ((str = "1H5""))).first;
//     AtomType::a1H50 = *repository.insert (new A1H50 ((str = "1H50"))).first;
//     AtomType::a1H51 = *repository.insert (new A1H51 ((str = "1H51"))).first;
//     AtomType::a1H52 = *repository.insert (new A1H52 ((str = "1H52"))).first;
//     AtomType::a1H53 = *repository.insert (new A1H53 ((str = "1H53"))).first;
//     AtomType::a1H54 = *repository.insert (new A1H54 ((str = "1H54"))).first;
//     AtomType::a1H55 = *repository.insert (new A1H55 ((str = "1H55"))).first;
//     AtomType::a1H56 = *repository.insert (new A1H56 ((str = "1H56"))).first;
//     AtomType::a1H57 = *repository.insert (new A1H57 ((str = "1H57"))).first;
//     AtomType::a1H58 = *repository.insert (new A1H58 ((str = "1H58"))).first;
//     AtomType::a1H59 = *repository.insert (new A1H59 ((str = "1H59"))).first;
//     AtomType::a1H5B = *repository.insert (new A1H5B ((str = "1H5B"))).first;
//     AtomType::a1H5C = *repository.insert (new A1H5C ((str = "1H5C"))).first;
//     AtomType::a1H5D = *repository.insert (new A1H5D ((str = "1H5D"))).first;
//     AtomType::a1H5E = *repository.insert (new A1H5E ((str = "1H5E"))).first;
//     AtomType::a1H5F = *repository.insert (new A1H5F ((str = "1H5F"))).first;
//     AtomType::a1H5G = *repository.insert (new A1H5G ((str = "1H5G"))).first;
//     AtomType::a1H5J = *repository.insert (new A1H5J ((str = "1H5J"))).first;
//     AtomType::a1H5M = *repository.insert (new A1H5M ((str = "1H5M"))).first;
//     AtomType::a1H5N = *repository.insert (new A1H5N ((str = "1H5N"))).first;
//     AtomType::a1H5P = *repository.insert (new A1H5P ((str = "1H5P"))).first;
//     AtomType::a1H5R = *repository.insert (new A1H5R ((str = "1H5R"))).first;
//     AtomType::a1H5S = *repository.insert (new A1H5S ((str = "1H5S"))).first;
//     AtomType::a1H5T = *repository.insert (new A1H5T ((str = "1H5T"))).first;
//     AtomType::a1H5U = *repository.insert (new A1H5U ((str = "1H5U"))).first;
//     AtomType::a1H5X = *repository.insert (new A1H5X ((str = "1H5X"))).first;
//     AtomType::a1H6 = *repository.insert (new A1H6 ((str = "1H6"))).first;
//     AtomType::a1H6" = *repository.insert (new A1H6" ((str = "1H6""))).first;
//     AtomType::a1H6* = *repository.insert (new A1H6* ((str = "1H6*"))).first;
//     AtomType::a1H60 = *repository.insert (new A1H60 ((str = "1H60"))).first;
//     AtomType::a1H61 = *repository.insert (new A1H61 ((str = "1H61"))).first;
//     AtomType::a1H62 = *repository.insert (new A1H62 ((str = "1H62"))).first;
//     AtomType::a1H63 = *repository.insert (new A1H63 ((str = "1H63"))).first;
//     AtomType::a1H64 = *repository.insert (new A1H64 ((str = "1H64"))).first;
//     AtomType::a1H65 = *repository.insert (new A1H65 ((str = "1H65"))).first;
//     AtomType::a1H66 = *repository.insert (new A1H66 ((str = "1H66"))).first;
//     AtomType::a1H67 = *repository.insert (new A1H67 ((str = "1H67"))).first;
//     AtomType::a1H68 = *repository.insert (new A1H68 ((str = "1H68"))).first;
//     AtomType::a1H69 = *repository.insert (new A1H69 ((str = "1H69"))).first;
//     AtomType::a1H6A = *repository.insert (new A1H6A ((str = "1H6A"))).first;
//     AtomType::a1H6B = *repository.insert (new A1H6B ((str = "1H6B"))).first;
//     AtomType::a1H6C = *repository.insert (new A1H6C ((str = "1H6C"))).first;
//     AtomType::a1H6D = *repository.insert (new A1H6D ((str = "1H6D"))).first;
//     AtomType::a1H6E = *repository.insert (new A1H6E ((str = "1H6E"))).first;
//     AtomType::a1H6F = *repository.insert (new A1H6F ((str = "1H6F"))).first;
//     AtomType::a1H6G = *repository.insert (new A1H6G ((str = "1H6G"))).first;
//     AtomType::a1H6H = *repository.insert (new A1H6H ((str = "1H6H"))).first;
//     AtomType::a1H6I = *repository.insert (new A1H6I ((str = "1H6I"))).first;
//     AtomType::a1H6J = *repository.insert (new A1H6J ((str = "1H6J"))).first;
//     AtomType::a1H6K = *repository.insert (new A1H6K ((str = "1H6K"))).first;
//     AtomType::a1H6L = *repository.insert (new A1H6L ((str = "1H6L"))).first;
//     AtomType::a1H6M = *repository.insert (new A1H6M ((str = "1H6M"))).first;
//     AtomType::a1H6N = *repository.insert (new A1H6N ((str = "1H6N"))).first;
//     AtomType::a1H6O = *repository.insert (new A1H6O ((str = "1H6O"))).first;
//     AtomType::a1H6P = *repository.insert (new A1H6P ((str = "1H6P"))).first;
//     AtomType::a1H6R = *repository.insert (new A1H6R ((str = "1H6R"))).first;
//     AtomType::a1H6S = *repository.insert (new A1H6S ((str = "1H6S"))).first;
//     AtomType::a1H6T = *repository.insert (new A1H6T ((str = "1H6T"))).first;
//     AtomType::a1H6W = *repository.insert (new A1H6W ((str = "1H6W"))).first;
//     AtomType::a1H6X = *repository.insert (new A1H6X ((str = "1H6X"))).first;
//     AtomType::a1H6Y = *repository.insert (new A1H6Y ((str = "1H6Y"))).first;
//     AtomType::a1H6Z = *repository.insert (new A1H6Z ((str = "1H6Z"))).first;
//     AtomType::a1H7 = *repository.insert (new A1H7 ((str = "1H7"))).first;
//     AtomType::a1H7" = *repository.insert (new A1H7" ((str = "1H7""))).first;
//     AtomType::a1H7* = *repository.insert (new A1H7* ((str = "1H7*"))).first;
//     AtomType::a1H70 = *repository.insert (new A1H70 ((str = "1H70"))).first;
//     AtomType::a1H71 = *repository.insert (new A1H71 ((str = "1H71"))).first;
//     AtomType::a1H72 = *repository.insert (new A1H72 ((str = "1H72"))).first;
//     AtomType::a1H73 = *repository.insert (new A1H73 ((str = "1H73"))).first;
//     AtomType::a1H74 = *repository.insert (new A1H74 ((str = "1H74"))).first;
//     AtomType::a1H75 = *repository.insert (new A1H75 ((str = "1H75"))).first;
//     AtomType::a1H76 = *repository.insert (new A1H76 ((str = "1H76"))).first;
//     AtomType::a1H77 = *repository.insert (new A1H77 ((str = "1H77"))).first;
//     AtomType::a1H78 = *repository.insert (new A1H78 ((str = "1H78"))).first;
//     AtomType::a1H79 = *repository.insert (new A1H79 ((str = "1H79"))).first;
//     AtomType::a1H7A = *repository.insert (new A1H7A ((str = "1H7A"))).first;
//     AtomType::a1H7B = *repository.insert (new A1H7B ((str = "1H7B"))).first;
//     AtomType::a1H7C = *repository.insert (new A1H7C ((str = "1H7C"))).first;
//     AtomType::a1H7D = *repository.insert (new A1H7D ((str = "1H7D"))).first;
//     AtomType::a1H7E = *repository.insert (new A1H7E ((str = "1H7E"))).first;
//     AtomType::a1H7F = *repository.insert (new A1H7F ((str = "1H7F"))).first;
//     AtomType::a1H7H = *repository.insert (new A1H7H ((str = "1H7H"))).first;
//     AtomType::a1H7I = *repository.insert (new A1H7I ((str = "1H7I"))).first;
//     AtomType::a1H7J = *repository.insert (new A1H7J ((str = "1H7J"))).first;
//     AtomType::a1H7K = *repository.insert (new A1H7K ((str = "1H7K"))).first;
//     AtomType::a1H7M = *repository.insert (new A1H7M ((str = "1H7M"))).first;
//     AtomType::a1H7N = *repository.insert (new A1H7N ((str = "1H7N"))).first;
//     AtomType::a1H7P = *repository.insert (new A1H7P ((str = "1H7P"))).first;
//     AtomType::a1H7R = *repository.insert (new A1H7R ((str = "1H7R"))).first;
//     AtomType::a1H7S = *repository.insert (new A1H7S ((str = "1H7S"))).first;
//     AtomType::a1H7T = *repository.insert (new A1H7T ((str = "1H7T"))).first;
//     AtomType::a1H7X = *repository.insert (new A1H7X ((str = "1H7X"))).first;
//     AtomType::a1H7Z = *repository.insert (new A1H7Z ((str = "1H7Z"))).first;
//     AtomType::a1H8 = *repository.insert (new A1H8 ((str = "1H8"))).first;
//     AtomType::a1H8" = *repository.insert (new A1H8" ((str = "1H8""))).first;
//     AtomType::a1H8* = *repository.insert (new A1H8* ((str = "1H8*"))).first;
//     AtomType::a1H80 = *repository.insert (new A1H80 ((str = "1H80"))).first;
//     AtomType::a1H81 = *repository.insert (new A1H81 ((str = "1H81"))).first;
//     AtomType::a1H82 = *repository.insert (new A1H82 ((str = "1H82"))).first;
//     AtomType::a1H83 = *repository.insert (new A1H83 ((str = "1H83"))).first;
//     AtomType::a1H84 = *repository.insert (new A1H84 ((str = "1H84"))).first;
//     AtomType::a1H85 = *repository.insert (new A1H85 ((str = "1H85"))).first;
//     AtomType::a1H86 = *repository.insert (new A1H86 ((str = "1H86"))).first;
//     AtomType::a1H87 = *repository.insert (new A1H87 ((str = "1H87"))).first;
//     AtomType::a1H88 = *repository.insert (new A1H88 ((str = "1H88"))).first;
//     AtomType::a1H89 = *repository.insert (new A1H89 ((str = "1H89"))).first;
//     AtomType::a1H8A = *repository.insert (new A1H8A ((str = "1H8A"))).first;
//     AtomType::a1H8B = *repository.insert (new A1H8B ((str = "1H8B"))).first;
//     AtomType::a1H8C = *repository.insert (new A1H8C ((str = "1H8C"))).first;
//     AtomType::a1H8D = *repository.insert (new A1H8D ((str = "1H8D"))).first;
//     AtomType::a1H8E = *repository.insert (new A1H8E ((str = "1H8E"))).first;
//     AtomType::a1H8F = *repository.insert (new A1H8F ((str = "1H8F"))).first;
//     AtomType::a1H8I = *repository.insert (new A1H8I ((str = "1H8I"))).first;
//     AtomType::a1H8J = *repository.insert (new A1H8J ((str = "1H8J"))).first;
//     AtomType::a1H8K = *repository.insert (new A1H8K ((str = "1H8K"))).first;
//     AtomType::a1H8M = *repository.insert (new A1H8M ((str = "1H8M"))).first;
//     AtomType::a1H8N = *repository.insert (new A1H8N ((str = "1H8N"))).first;
//     AtomType::a1H8S = *repository.insert (new A1H8S ((str = "1H8S"))).first;
//     AtomType::a1H8X = *repository.insert (new A1H8X ((str = "1H8X"))).first;
//     AtomType::a1H9 = *repository.insert (new A1H9 ((str = "1H9"))).first;
//     AtomType::a1H9" = *repository.insert (new A1H9" ((str = "1H9""))).first;
//     AtomType::a1H9* = *repository.insert (new A1H9* ((str = "1H9*"))).first;
//     AtomType::a1H90 = *repository.insert (new A1H90 ((str = "1H90"))).first;
//     AtomType::a1H91 = *repository.insert (new A1H91 ((str = "1H91"))).first;
//     AtomType::a1H92 = *repository.insert (new A1H92 ((str = "1H92"))).first;
//     AtomType::a1H93 = *repository.insert (new A1H93 ((str = "1H93"))).first;
//     AtomType::a1H94 = *repository.insert (new A1H94 ((str = "1H94"))).first;
//     AtomType::a1H95 = *repository.insert (new A1H95 ((str = "1H95"))).first;
//     AtomType::a1H96 = *repository.insert (new A1H96 ((str = "1H96"))).first;
//     AtomType::a1H97 = *repository.insert (new A1H97 ((str = "1H97"))).first;
//     AtomType::a1H98 = *repository.insert (new A1H98 ((str = "1H98"))).first;
//     AtomType::a1H99 = *repository.insert (new A1H99 ((str = "1H99"))).first;
//     AtomType::a1H9A = *repository.insert (new A1H9A ((str = "1H9A"))).first;
//     AtomType::a1H9B = *repository.insert (new A1H9B ((str = "1H9B"))).first;
//     AtomType::a1H9C = *repository.insert (new A1H9C ((str = "1H9C"))).first;
//     AtomType::a1H9D = *repository.insert (new A1H9D ((str = "1H9D"))).first;
//     AtomType::a1H9E = *repository.insert (new A1H9E ((str = "1H9E"))).first;
//     AtomType::a1H9F = *repository.insert (new A1H9F ((str = "1H9F"))).first;
//     AtomType::a1H9J = *repository.insert (new A1H9J ((str = "1H9J"))).first;
//     AtomType::a1H9K = *repository.insert (new A1H9K ((str = "1H9K"))).first;
//     AtomType::a1H9M = *repository.insert (new A1H9M ((str = "1H9M"))).first;
//     AtomType::a1H9N = *repository.insert (new A1H9N ((str = "1H9N"))).first;
//     AtomType::a1H9O = *repository.insert (new A1H9O ((str = "1H9O"))).first;
//     AtomType::a1H9S = *repository.insert (new A1H9S ((str = "1H9S"))).first;
//     AtomType::a1H9X = *repository.insert (new A1H9X ((str = "1H9X"))).first;
//     AtomType::a1HA" = *repository.insert (new A1HA" ((str = "1HA""))).first;
//     AtomType::a1HA* = *repository.insert (new A1HA* ((str = "1HA*"))).first;
//     AtomType::a1HA1 = *repository.insert (new A1HA1 ((str = "1HA1"))).first;
//     AtomType::a1HA2 = *repository.insert (new A1HA2 ((str = "1HA2"))).first;
//     AtomType::a1HA3 = *repository.insert (new A1HA3 ((str = "1HA3"))).first;
//     AtomType::a1HA4 = *repository.insert (new A1HA4 ((str = "1HA4"))).first;
//     AtomType::a1HA5 = *repository.insert (new A1HA5 ((str = "1HA5"))).first;
//     AtomType::a1HA6 = *repository.insert (new A1HA6 ((str = "1HA6"))).first;
//     AtomType::a1HA7 = *repository.insert (new A1HA7 ((str = "1HA7"))).first;
//     AtomType::a1HA8 = *repository.insert (new A1HA8 ((str = "1HA8"))).first;
//     AtomType::a1HA9 = *repository.insert (new A1HA9 ((str = "1HA9"))).first;
//     AtomType::a1HAA = *repository.insert (new A1HAA ((str = "1HAA"))).first;
//     AtomType::a1HAB = *repository.insert (new A1HAB ((str = "1HAB"))).first;
//     AtomType::a1HAC = *repository.insert (new A1HAC ((str = "1HAC"))).first;
//     AtomType::a1HAD = *repository.insert (new A1HAD ((str = "1HAD"))).first;
//     AtomType::a1HAE = *repository.insert (new A1HAE ((str = "1HAE"))).first;
//     AtomType::a1HAF = *repository.insert (new A1HAF ((str = "1HAF"))).first;
//     AtomType::a1HAG = *repository.insert (new A1HAG ((str = "1HAG"))).first;
//     AtomType::a1HAH = *repository.insert (new A1HAH ((str = "1HAH"))).first;
//     AtomType::a1HAI = *repository.insert (new A1HAI ((str = "1HAI"))).first;
//     AtomType::a1HAJ = *repository.insert (new A1HAJ ((str = "1HAJ"))).first;
//     AtomType::a1HAK = *repository.insert (new A1HAK ((str = "1HAK"))).first;
//     AtomType::a1HAL = *repository.insert (new A1HAL ((str = "1HAL"))).first;
//     AtomType::a1HAM = *repository.insert (new A1HAM ((str = "1HAM"))).first;
//     AtomType::a1HAN = *repository.insert (new A1HAN ((str = "1HAN"))).first;
//     AtomType::a1HAO = *repository.insert (new A1HAO ((str = "1HAO"))).first;
//     AtomType::a1HAP = *repository.insert (new A1HAP ((str = "1HAP"))).first;
//     AtomType::a1HAQ = *repository.insert (new A1HAQ ((str = "1HAQ"))).first;
//     AtomType::a1HAR = *repository.insert (new A1HAR ((str = "1HAR"))).first;
//     AtomType::a1HAS = *repository.insert (new A1HAS ((str = "1HAS"))).first;
//     AtomType::a1HAT = *repository.insert (new A1HAT ((str = "1HAT"))).first;
//     AtomType::a1HAU = *repository.insert (new A1HAU ((str = "1HAU"))).first;
//     AtomType::a1HAV = *repository.insert (new A1HAV ((str = "1HAV"))).first;
//     AtomType::a1HAW = *repository.insert (new A1HAW ((str = "1HAW"))).first;
//     AtomType::a1HAX = *repository.insert (new A1HAX ((str = "1HAX"))).first;
//     AtomType::a1HAY = *repository.insert (new A1HAY ((str = "1HAY"))).first;
//     AtomType::a1HAZ = *repository.insert (new A1HAZ ((str = "1HAZ"))).first;
//     AtomType::a1HB" = *repository.insert (new A1HB" ((str = "1HB""))).first;
//     AtomType::a1HB* = *repository.insert (new A1HB* ((str = "1HB*"))).first;
//     AtomType::a1HB0 = *repository.insert (new A1HB0 ((str = "1HB0"))).first;
//     AtomType::a1HB1 = *repository.insert (new A1HB1 ((str = "1HB1"))).first;
//     AtomType::a1HB2 = *repository.insert (new A1HB2 ((str = "1HB2"))).first;
//     AtomType::a1HB3 = *repository.insert (new A1HB3 ((str = "1HB3"))).first;
//     AtomType::a1HB4 = *repository.insert (new A1HB4 ((str = "1HB4"))).first;
//     AtomType::a1HB5 = *repository.insert (new A1HB5 ((str = "1HB5"))).first;
//     AtomType::a1HB6 = *repository.insert (new A1HB6 ((str = "1HB6"))).first;
//     AtomType::a1HB7 = *repository.insert (new A1HB7 ((str = "1HB7"))).first;
//     AtomType::a1HB8 = *repository.insert (new A1HB8 ((str = "1HB8"))).first;
//     AtomType::a1HB9 = *repository.insert (new A1HB9 ((str = "1HB9"))).first;
//     AtomType::a1HBA = *repository.insert (new A1HBA ((str = "1HBA"))).first;
//     AtomType::a1HBB = *repository.insert (new A1HBB ((str = "1HBB"))).first;
//     AtomType::a1HBC = *repository.insert (new A1HBC ((str = "1HBC"))).first;
//     AtomType::a1HBD = *repository.insert (new A1HBD ((str = "1HBD"))).first;
//     AtomType::a1HBE = *repository.insert (new A1HBE ((str = "1HBE"))).first;
//     AtomType::a1HBF = *repository.insert (new A1HBF ((str = "1HBF"))).first;
//     AtomType::a1HBG = *repository.insert (new A1HBG ((str = "1HBG"))).first;
//     AtomType::a1HBH = *repository.insert (new A1HBH ((str = "1HBH"))).first;
//     AtomType::a1HBI = *repository.insert (new A1HBI ((str = "1HBI"))).first;
//     AtomType::a1HBJ = *repository.insert (new A1HBJ ((str = "1HBJ"))).first;
//     AtomType::a1HBK = *repository.insert (new A1HBK ((str = "1HBK"))).first;
//     AtomType::a1HBL = *repository.insert (new A1HBL ((str = "1HBL"))).first;
//     AtomType::a1HBM = *repository.insert (new A1HBM ((str = "1HBM"))).first;
//     AtomType::a1HBN = *repository.insert (new A1HBN ((str = "1HBN"))).first;
//     AtomType::a1HBO = *repository.insert (new A1HBO ((str = "1HBO"))).first;
//     AtomType::a1HBP = *repository.insert (new A1HBP ((str = "1HBP"))).first;
//     AtomType::a1HBQ = *repository.insert (new A1HBQ ((str = "1HBQ"))).first;
//     AtomType::a1HBR = *repository.insert (new A1HBR ((str = "1HBR"))).first;
//     AtomType::a1HBS = *repository.insert (new A1HBS ((str = "1HBS"))).first;
//     AtomType::a1HBT = *repository.insert (new A1HBT ((str = "1HBT"))).first;
//     AtomType::a1HBU = *repository.insert (new A1HBU ((str = "1HBU"))).first;
//     AtomType::a1HBV = *repository.insert (new A1HBV ((str = "1HBV"))).first;
//     AtomType::a1HBW = *repository.insert (new A1HBW ((str = "1HBW"))).first;
//     AtomType::a1HBX = *repository.insert (new A1HBX ((str = "1HBX"))).first;
//     AtomType::a1HBY = *repository.insert (new A1HBY ((str = "1HBY"))).first;
//     AtomType::a1HBZ = *repository.insert (new A1HBZ ((str = "1HBZ"))).first;
//     AtomType::a1HC = *repository.insert (new A1HC ((str = "1HC"))).first;
//     AtomType::a1HC" = *repository.insert (new A1HC" ((str = "1HC""))).first;
//     AtomType::a1HC* = *repository.insert (new A1HC* ((str = "1HC*"))).first;
//     AtomType::a1HC0 = *repository.insert (new A1HC0 ((str = "1HC0"))).first;
//     AtomType::a1HC1 = *repository.insert (new A1HC1 ((str = "1HC1"))).first;
//     AtomType::a1HC2 = *repository.insert (new A1HC2 ((str = "1HC2"))).first;
//     AtomType::a1HC3 = *repository.insert (new A1HC3 ((str = "1HC3"))).first;
//     AtomType::a1HC4 = *repository.insert (new A1HC4 ((str = "1HC4"))).first;
//     AtomType::a1HC5 = *repository.insert (new A1HC5 ((str = "1HC5"))).first;
//     AtomType::a1HC6 = *repository.insert (new A1HC6 ((str = "1HC6"))).first;
//     AtomType::a1HC7 = *repository.insert (new A1HC7 ((str = "1HC7"))).first;
//     AtomType::a1HC8 = *repository.insert (new A1HC8 ((str = "1HC8"))).first;
//     AtomType::a1HC9 = *repository.insert (new A1HC9 ((str = "1HC9"))).first;
//     AtomType::a1HCA = *repository.insert (new A1HCA ((str = "1HCA"))).first;
//     AtomType::a1HCB = *repository.insert (new A1HCB ((str = "1HCB"))).first;
//     AtomType::a1HCC = *repository.insert (new A1HCC ((str = "1HCC"))).first;
//     AtomType::a1HCD = *repository.insert (new A1HCD ((str = "1HCD"))).first;
//     AtomType::a1HCE = *repository.insert (new A1HCE ((str = "1HCE"))).first;
//     AtomType::a1HCF = *repository.insert (new A1HCF ((str = "1HCF"))).first;
//     AtomType::a1HCG = *repository.insert (new A1HCG ((str = "1HCG"))).first;
//     AtomType::a1HCH = *repository.insert (new A1HCH ((str = "1HCH"))).first;
//     AtomType::a1HCI = *repository.insert (new A1HCI ((str = "1HCI"))).first;
//     AtomType::a1HCJ = *repository.insert (new A1HCJ ((str = "1HCJ"))).first;
//     AtomType::a1HCK = *repository.insert (new A1HCK ((str = "1HCK"))).first;
//     AtomType::a1HCL = *repository.insert (new A1HCL ((str = "1HCL"))).first;
//     AtomType::a1HCM = *repository.insert (new A1HCM ((str = "1HCM"))).first;
//     AtomType::a1HCN = *repository.insert (new A1HCN ((str = "1HCN"))).first;
//     AtomType::a1HCO = *repository.insert (new A1HCO ((str = "1HCO"))).first;
//     AtomType::a1HCP = *repository.insert (new A1HCP ((str = "1HCP"))).first;
//     AtomType::a1HCQ = *repository.insert (new A1HCQ ((str = "1HCQ"))).first;
//     AtomType::a1HCR = *repository.insert (new A1HCR ((str = "1HCR"))).first;
//     AtomType::a1HCS = *repository.insert (new A1HCS ((str = "1HCS"))).first;
//     AtomType::a1HCT = *repository.insert (new A1HCT ((str = "1HCT"))).first;
//     AtomType::a1HCU = *repository.insert (new A1HCU ((str = "1HCU"))).first;
//     AtomType::a1HCV = *repository.insert (new A1HCV ((str = "1HCV"))).first;
//     AtomType::a1HCW = *repository.insert (new A1HCW ((str = "1HCW"))).first;
//     AtomType::a1HCX = *repository.insert (new A1HCX ((str = "1HCX"))).first;
//     AtomType::a1HCZ = *repository.insert (new A1HCZ ((str = "1HCZ"))).first;
//     AtomType::a1HD" = *repository.insert (new A1HD" ((str = "1HD""))).first;
//     AtomType::a1HD* = *repository.insert (new A1HD* ((str = "1HD*"))).first;
//     AtomType::a1HD0 = *repository.insert (new A1HD0 ((str = "1HD0"))).first;
//     AtomType::a1HD1 = *repository.insert (new A1HD1 ((str = "1HD1"))).first;
//     AtomType::a1HD2 = *repository.insert (new A1HD2 ((str = "1HD2"))).first;
//     AtomType::a1HD3 = *repository.insert (new A1HD3 ((str = "1HD3"))).first;
//     AtomType::a1HD4 = *repository.insert (new A1HD4 ((str = "1HD4"))).first;
//     AtomType::a1HD5 = *repository.insert (new A1HD5 ((str = "1HD5"))).first;
//     AtomType::a1HD6 = *repository.insert (new A1HD6 ((str = "1HD6"))).first;
//     AtomType::a1HD7 = *repository.insert (new A1HD7 ((str = "1HD7"))).first;
//     AtomType::a1HD8 = *repository.insert (new A1HD8 ((str = "1HD8"))).first;
//     AtomType::a1HD9 = *repository.insert (new A1HD9 ((str = "1HD9"))).first;
//     AtomType::a1HDA = *repository.insert (new A1HDA ((str = "1HDA"))).first;
//     AtomType::a1HDB = *repository.insert (new A1HDB ((str = "1HDB"))).first;
//     AtomType::a1HDC = *repository.insert (new A1HDC ((str = "1HDC"))).first;
//     AtomType::a1HDD = *repository.insert (new A1HDD ((str = "1HDD"))).first;
//     AtomType::a1HDI = *repository.insert (new A1HDI ((str = "1HDI"))).first;
//     AtomType::a1HDK = *repository.insert (new A1HDK ((str = "1HDK"))).first;
//     AtomType::a1HDL = *repository.insert (new A1HDL ((str = "1HDL"))).first;
//     AtomType::a1HDM = *repository.insert (new A1HDM ((str = "1HDM"))).first;
//     AtomType::a1HDN = *repository.insert (new A1HDN ((str = "1HDN"))).first;
//     AtomType::a1HDO = *repository.insert (new A1HDO ((str = "1HDO"))).first;
//     AtomType::a1HDP = *repository.insert (new A1HDP ((str = "1HDP"))).first;
//     AtomType::a1HDY = *repository.insert (new A1HDY ((str = "1HDY"))).first;
//     AtomType::a1HE" = *repository.insert (new A1HE" ((str = "1HE""))).first;
//     AtomType::a1HE* = *repository.insert (new A1HE* ((str = "1HE*"))).first;
//     AtomType::a1HE0 = *repository.insert (new A1HE0 ((str = "1HE0"))).first;
//     AtomType::a1HE1 = *repository.insert (new A1HE1 ((str = "1HE1"))).first;
//     AtomType::a1HE2 = *repository.insert (new A1HE2 ((str = "1HE2"))).first;
//     AtomType::a1HE3 = *repository.insert (new A1HE3 ((str = "1HE3"))).first;
//     AtomType::a1HE4 = *repository.insert (new A1HE4 ((str = "1HE4"))).first;
//     AtomType::a1HE6 = *repository.insert (new A1HE6 ((str = "1HE6"))).first;
//     AtomType::a1HE7 = *repository.insert (new A1HE7 ((str = "1HE7"))).first;
//     AtomType::a1HEA = *repository.insert (new A1HEA ((str = "1HEA"))).first;
//     AtomType::a1HEC = *repository.insert (new A1HEC ((str = "1HEC"))).first;
//     AtomType::a1HED = *repository.insert (new A1HED ((str = "1HED"))).first;
//     AtomType::a1HEI = *repository.insert (new A1HEI ((str = "1HEI"))).first;
//     AtomType::a1HEK = *repository.insert (new A1HEK ((str = "1HEK"))).first;
//     AtomType::a1HEM = *repository.insert (new A1HEM ((str = "1HEM"))).first;
//     AtomType::a1HEO = *repository.insert (new A1HEO ((str = "1HEO"))).first;
//     AtomType::a1HEP = *repository.insert (new A1HEP ((str = "1HEP"))).first;
//     AtomType::a1HEY = *repository.insert (new A1HEY ((str = "1HEY"))).first;
//     AtomType::a1HF = *repository.insert (new A1HF ((str = "1HF"))).first;
//     AtomType::a1HF" = *repository.insert (new A1HF" ((str = "1HF""))).first;
//     AtomType::a1HF* = *repository.insert (new A1HF* ((str = "1HF*"))).first;
//     AtomType::a1HF1 = *repository.insert (new A1HF1 ((str = "1HF1"))).first;
//     AtomType::a1HF2 = *repository.insert (new A1HF2 ((str = "1HF2"))).first;
//     AtomType::a1HFI = *repository.insert (new A1HFI ((str = "1HFI"))).first;
//     AtomType::a1HFM = *repository.insert (new A1HFM ((str = "1HFM"))).first;
//     AtomType::a1HG" = *repository.insert (new A1HG" ((str = "1HG""))).first;
//     AtomType::a1HG* = *repository.insert (new A1HG* ((str = "1HG*"))).first;
//     AtomType::a1HG1 = *repository.insert (new A1HG1 ((str = "1HG1"))).first;
//     AtomType::a1HG2 = *repository.insert (new A1HG2 ((str = "1HG2"))).first;
//     AtomType::a1HG3 = *repository.insert (new A1HG3 ((str = "1HG3"))).first;
//     AtomType::a1HG4 = *repository.insert (new A1HG4 ((str = "1HG4"))).first;
//     AtomType::a1HG5 = *repository.insert (new A1HG5 ((str = "1HG5"))).first;
//     AtomType::a1HG6 = *repository.insert (new A1HG6 ((str = "1HG6"))).first;
//     AtomType::a1HG7 = *repository.insert (new A1HG7 ((str = "1HG7"))).first;
//     AtomType::a1HG8 = *repository.insert (new A1HG8 ((str = "1HG8"))).first;
//     AtomType::a1HGA = *repository.insert (new A1HGA ((str = "1HGA"))).first;
//     AtomType::a1HGB = *repository.insert (new A1HGB ((str = "1HGB"))).first;
//     AtomType::a1HGC = *repository.insert (new A1HGC ((str = "1HGC"))).first;
//     AtomType::a1HGI = *repository.insert (new A1HGI ((str = "1HGI"))).first;
//     AtomType::a1HGK = *repository.insert (new A1HGK ((str = "1HGK"))).first;
//     AtomType::a1HGO = *repository.insert (new A1HGO ((str = "1HGO"))).first;
//     AtomType::a1HGP = *repository.insert (new A1HGP ((str = "1HGP"))).first;
//     AtomType::a1HGS = *repository.insert (new A1HGS ((str = "1HGS"))).first;
//     AtomType::a1HGT = *repository.insert (new A1HGT ((str = "1HGT"))).first;
//     AtomType::a1HH = *repository.insert (new A1HH ((str = "1HH"))).first;
//     AtomType::a1HH" = *repository.insert (new A1HH" ((str = "1HH""))).first;
//     AtomType::a1HH* = *repository.insert (new A1HH* ((str = "1HH*"))).first;
//     AtomType::a1HH1 = *repository.insert (new A1HH1 ((str = "1HH1"))).first;
//     AtomType::a1HH2 = *repository.insert (new A1HH2 ((str = "1HH2"))).first;
//     AtomType::a1HH3 = *repository.insert (new A1HH3 ((str = "1HH3"))).first;
//     AtomType::a1HH4 = *repository.insert (new A1HH4 ((str = "1HH4"))).first;
//     AtomType::a1HH5 = *repository.insert (new A1HH5 ((str = "1HH5"))).first;
//     AtomType::a1HH6 = *repository.insert (new A1HH6 ((str = "1HH6"))).first;
//     AtomType::a1HHA = *repository.insert (new A1HHA ((str = "1HHA"))).first;
//     AtomType::a1HHB = *repository.insert (new A1HHB ((str = "1HHB"))).first;
//     AtomType::a1HHC = *repository.insert (new A1HHC ((str = "1HHC"))).first;
//     AtomType::a1HHD = *repository.insert (new A1HHD ((str = "1HHD"))).first;
//     AtomType::a1HHR = *repository.insert (new A1HHR ((str = "1HHR"))).first;
//     AtomType::a1HHY = *repository.insert (new A1HHY ((str = "1HHY"))).first;
//     AtomType::a1HI = *repository.insert (new A1HI ((str = "1HI"))).first;
//     AtomType::a1HI" = *repository.insert (new A1HI" ((str = "1HI""))).first;
//     AtomType::a1HI* = *repository.insert (new A1HI* ((str = "1HI*"))).first;
//     AtomType::a1HI1 = *repository.insert (new A1HI1 ((str = "1HI1"))).first;
//     AtomType::a1HI2 = *repository.insert (new A1HI2 ((str = "1HI2"))).first;
//     AtomType::a1HI3 = *repository.insert (new A1HI3 ((str = "1HI3"))).first;
//     AtomType::a1HIB = *repository.insert (new A1HIB ((str = "1HIB"))).first;
//     AtomType::a1HIF = *repository.insert (new A1HIF ((str = "1HIF"))).first;
//     AtomType::a1HJ = *repository.insert (new A1HJ ((str = "1HJ"))).first;
//     AtomType::a1HJ" = *repository.insert (new A1HJ" ((str = "1HJ""))).first;
//     AtomType::a1HJ* = *repository.insert (new A1HJ* ((str = "1HJ*"))).first;
//     AtomType::a1HJ1 = *repository.insert (new A1HJ1 ((str = "1HJ1"))).first;
//     AtomType::a1HJ2 = *repository.insert (new A1HJ2 ((str = "1HJ2"))).first;
//     AtomType::a1HJ6 = *repository.insert (new A1HJ6 ((str = "1HJ6"))).first;
//     AtomType::a1HJC = *repository.insert (new A1HJC ((str = "1HJC"))).first;
//     AtomType::a1HK = *repository.insert (new A1HK ((str = "1HK"))).first;
//     AtomType::a1HK* = *repository.insert (new A1HK* ((str = "1HK*"))).first;
//     AtomType::a1HK1 = *repository.insert (new A1HK1 ((str = "1HK1"))).first;
//     AtomType::a1HK2 = *repository.insert (new A1HK2 ((str = "1HK2"))).first;
//     AtomType::a1HK3 = *repository.insert (new A1HK3 ((str = "1HK3"))).first;
//     AtomType::a1HK4 = *repository.insert (new A1HK4 ((str = "1HK4"))).first;
//     AtomType::a1HK5 = *repository.insert (new A1HK5 ((str = "1HK5"))).first;
//     AtomType::a1HK6 = *repository.insert (new A1HK6 ((str = "1HK6"))).first;
//     AtomType::a1HKC = *repository.insert (new A1HKC ((str = "1HKC"))).first;
//     AtomType::a1HKY = *repository.insert (new A1HKY ((str = "1HKY"))).first;
//     AtomType::a1HL = *repository.insert (new A1HL ((str = "1HL"))).first;
//     AtomType::a1HL* = *repository.insert (new A1HL* ((str = "1HL*"))).first;
//     AtomType::a1HL1 = *repository.insert (new A1HL1 ((str = "1HL1"))).first;
//     AtomType::a1HL2 = *repository.insert (new A1HL2 ((str = "1HL2"))).first;
//     AtomType::a1HL3 = *repository.insert (new A1HL3 ((str = "1HL3"))).first;
//     AtomType::a1HL4 = *repository.insert (new A1HL4 ((str = "1HL4"))).first;
//     AtomType::a1HL5 = *repository.insert (new A1HL5 ((str = "1HL5"))).first;
//     AtomType::a1HL6 = *repository.insert (new A1HL6 ((str = "1HL6"))).first;
//     AtomType::a1HL7 = *repository.insert (new A1HL7 ((str = "1HL7"))).first;
//     AtomType::a1HL8 = *repository.insert (new A1HL8 ((str = "1HL8"))).first;
//     AtomType::a1HL9 = *repository.insert (new A1HL9 ((str = "1HL9"))).first;
//     AtomType::a1HLB = *repository.insert (new A1HLB ((str = "1HLB"))).first;
//     AtomType::a1HM = *repository.insert (new A1HM ((str = "1HM"))).first;
//     AtomType::a1HM" = *repository.insert (new A1HM" ((str = "1HM""))).first;
//     AtomType::a1HM* = *repository.insert (new A1HM* ((str = "1HM*"))).first;
//     AtomType::a1HM0 = *repository.insert (new A1HM0 ((str = "1HM0"))).first;
    AtomType::a1HM1 = *repository.insert (new A1HM1 ((str = "1HM1"))).first;
//     AtomType::a1HM2 = *repository.insert (new A1HM2 ((str = "1HM2"))).first;
//     AtomType::a1HM3 = *repository.insert (new A1HM3 ((str = "1HM3"))).first;
//     AtomType::a1HM4 = *repository.insert (new A1HM4 ((str = "1HM4"))).first;
//     AtomType::a1HM5 = *repository.insert (new A1HM5 ((str = "1HM5"))).first;
//     AtomType::a1HM6 = *repository.insert (new A1HM6 ((str = "1HM6"))).first;
//     AtomType::a1HM7 = *repository.insert (new A1HM7 ((str = "1HM7"))).first;
//     AtomType::a1HM8 = *repository.insert (new A1HM8 ((str = "1HM8"))).first;
//     AtomType::a1HM9 = *repository.insert (new A1HM9 ((str = "1HM9"))).first;
//     AtomType::a1HMA = *repository.insert (new A1HMA ((str = "1HMA"))).first;
//     AtomType::a1HMB = *repository.insert (new A1HMB ((str = "1HMB"))).first;
//     AtomType::a1HMC = *repository.insert (new A1HMC ((str = "1HMC"))).first;
//     AtomType::a1HMD = *repository.insert (new A1HMD ((str = "1HMD"))).first;
//     AtomType::a1HME = *repository.insert (new A1HME ((str = "1HME"))).first;
//     AtomType::a1HMF = *repository.insert (new A1HMF ((str = "1HMF"))).first;
//     AtomType::a1HMK = *repository.insert (new A1HMK ((str = "1HMK"))).first;
//     AtomType::a1HMP = *repository.insert (new A1HMP ((str = "1HMP"))).first;
//     AtomType::a1HMZ = *repository.insert (new A1HMZ ((str = "1HMZ"))).first;
//     AtomType::a1HN = *repository.insert (new A1HN ((str = "1HN"))).first;
//     AtomType::a1HN* = *repository.insert (new A1HN* ((str = "1HN*"))).first;
//     AtomType::a1HN0 = *repository.insert (new A1HN0 ((str = "1HN0"))).first;
//     AtomType::a1HN1 = *repository.insert (new A1HN1 ((str = "1HN1"))).first;
//     AtomType::a1HN2 = *repository.insert (new A1HN2 ((str = "1HN2"))).first;
//     AtomType::a1HN3 = *repository.insert (new A1HN3 ((str = "1HN3"))).first;
//     AtomType::a1HN4 = *repository.insert (new A1HN4 ((str = "1HN4"))).first;
//     AtomType::a1HN5 = *repository.insert (new A1HN5 ((str = "1HN5"))).first;
    AtomType::a1HN6 = *repository.insert (new A1HN6 ((str = "1HN6"))).first;
//     AtomType::a1HN7 = *repository.insert (new A1HN7 ((str = "1HN7"))).first;
//     AtomType::a1HN8 = *repository.insert (new A1HN8 ((str = "1HN8"))).first;
//     AtomType::a1HN9 = *repository.insert (new A1HN9 ((str = "1HN9"))).first;
//     AtomType::a1HNA = *repository.insert (new A1HNA ((str = "1HNA"))).first;
//     AtomType::a1HNB = *repository.insert (new A1HNB ((str = "1HNB"))).first;
//     AtomType::a1HNC = *repository.insert (new A1HNC ((str = "1HNC"))).first;
//     AtomType::a1HND = *repository.insert (new A1HND ((str = "1HND"))).first;
//     AtomType::a1HNE = *repository.insert (new A1HNE ((str = "1HNE"))).first;
//     AtomType::a1HNF = *repository.insert (new A1HNF ((str = "1HNF"))).first;
//     AtomType::a1HNG = *repository.insert (new A1HNG ((str = "1HNG"))).first;
//     AtomType::a1HNH = *repository.insert (new A1HNH ((str = "1HNH"))).first;
//     AtomType::a1HNI = *repository.insert (new A1HNI ((str = "1HNI"))).first;
//     AtomType::a1HNK = *repository.insert (new A1HNK ((str = "1HNK"))).first;
//     AtomType::a1HNL = *repository.insert (new A1HNL ((str = "1HNL"))).first;
//     AtomType::a1HNM = *repository.insert (new A1HNM ((str = "1HNM"))).first;
//     AtomType::a1HNO = *repository.insert (new A1HNO ((str = "1HNO"))).first;
//     AtomType::a1HNP = *repository.insert (new A1HNP ((str = "1HNP"))).first;
//     AtomType::a1HNQ = *repository.insert (new A1HNQ ((str = "1HNQ"))).first;
//     AtomType::a1HNS = *repository.insert (new A1HNS ((str = "1HNS"))).first;
//     AtomType::a1HNT = *repository.insert (new A1HNT ((str = "1HNT"))).first;
//     AtomType::a1HNV = *repository.insert (new A1HNV ((str = "1HNV"))).first;
//     AtomType::a1HNX = *repository.insert (new A1HNX ((str = "1HNX"))).first;
//     AtomType::a1HNZ = *repository.insert (new A1HNZ ((str = "1HNZ"))).first;
//     AtomType::a1HO = *repository.insert (new A1HO ((str = "1HO"))).first;
//     AtomType::a1HO" = *repository.insert (new A1HO" ((str = "1HO""))).first;
//     AtomType::a1HO* = *repository.insert (new A1HO* ((str = "1HO*"))).first;
//     AtomType::a1HO0 = *repository.insert (new A1HO0 ((str = "1HO0"))).first;
//     AtomType::a1HO1 = *repository.insert (new A1HO1 ((str = "1HO1"))).first;
//     AtomType::a1HO2 = *repository.insert (new A1HO2 ((str = "1HO2"))).first;
//     AtomType::a1HO3 = *repository.insert (new A1HO3 ((str = "1HO3"))).first;
//     AtomType::a1HO4 = *repository.insert (new A1HO4 ((str = "1HO4"))).first;
//     AtomType::a1HO5 = *repository.insert (new A1HO5 ((str = "1HO5"))).first;
//     AtomType::a1HO6 = *repository.insert (new A1HO6 ((str = "1HO6"))).first;
//     AtomType::a1HO7 = *repository.insert (new A1HO7 ((str = "1HO7"))).first;
//     AtomType::a1HO8 = *repository.insert (new A1HO8 ((str = "1HO8"))).first;
//     AtomType::a1HO9 = *repository.insert (new A1HO9 ((str = "1HO9"))).first;
//     AtomType::a1HOA = *repository.insert (new A1HOA ((str = "1HOA"))).first;
//     AtomType::a1HOB = *repository.insert (new A1HOB ((str = "1HOB"))).first;
//     AtomType::a1HOC = *repository.insert (new A1HOC ((str = "1HOC"))).first;
//     AtomType::a1HOD = *repository.insert (new A1HOD ((str = "1HOD"))).first;
//     AtomType::a1HOE = *repository.insert (new A1HOE ((str = "1HOE"))).first;
//     AtomType::a1HOG = *repository.insert (new A1HOG ((str = "1HOG"))).first;
//     AtomType::a1HOH = *repository.insert (new A1HOH ((str = "1HOH"))).first;
//     AtomType::a1HOP = *repository.insert (new A1HOP ((str = "1HOP"))).first;
//     AtomType::a1HOR = *repository.insert (new A1HOR ((str = "1HOR"))).first;
//     AtomType::a1HOS = *repository.insert (new A1HOS ((str = "1HOS"))).first;
//     AtomType::a1HOT = *repository.insert (new A1HOT ((str = "1HOT"))).first;
//     AtomType::a1HOV = *repository.insert (new A1HOV ((str = "1HOV"))).first;
//     AtomType::a1HOX = *repository.insert (new A1HOX ((str = "1HOX"))).first;
//     AtomType::a1HP = *repository.insert (new A1HP ((str = "1HP"))).first;
//     AtomType::a1HP1 = *repository.insert (new A1HP1 ((str = "1HP1"))).first;
//     AtomType::a1HP2 = *repository.insert (new A1HP2 ((str = "1HP2"))).first;
//     AtomType::a1HP3 = *repository.insert (new A1HP3 ((str = "1HP3"))).first;
//     AtomType::a1HP4 = *repository.insert (new A1HP4 ((str = "1HP4"))).first;
//     AtomType::a1HP5 = *repository.insert (new A1HP5 ((str = "1HP5"))).first;
//     AtomType::a1HP6 = *repository.insert (new A1HP6 ((str = "1HP6"))).first;
//     AtomType::a1HP7 = *repository.insert (new A1HP7 ((str = "1HP7"))).first;
//     AtomType::a1HP8 = *repository.insert (new A1HP8 ((str = "1HP8"))).first;
//     AtomType::a1HP9 = *repository.insert (new A1HP9 ((str = "1HP9"))).first;
//     AtomType::a1HPA = *repository.insert (new A1HPA ((str = "1HPA"))).first;
//     AtomType::a1HPB = *repository.insert (new A1HPB ((str = "1HPB"))).first;
//     AtomType::a1HPC = *repository.insert (new A1HPC ((str = "1HPC"))).first;
//     AtomType::a1HPD = *repository.insert (new A1HPD ((str = "1HPD"))).first;
//     AtomType::a1HPE = *repository.insert (new A1HPE ((str = "1HPE"))).first;
//     AtomType::a1HPS = *repository.insert (new A1HPS ((str = "1HPS"))).first;
//     AtomType::a1HQ = *repository.insert (new A1HQ ((str = "1HQ"))).first;
//     AtomType::a1HQ1 = *repository.insert (new A1HQ1 ((str = "1HQ1"))).first;
//     AtomType::a1HQ2 = *repository.insert (new A1HQ2 ((str = "1HQ2"))).first;
//     AtomType::a1HQ6 = *repository.insert (new A1HQ6 ((str = "1HQ6"))).first;
//     AtomType::a1HQ7 = *repository.insert (new A1HQ7 ((str = "1HQ7"))).first;
//     AtomType::a1HQB = *repository.insert (new A1HQB ((str = "1HQB"))).first;
//     AtomType::a1HR = *repository.insert (new A1HR ((str = "1HR"))).first;
//     AtomType::a1HR* = *repository.insert (new A1HR* ((str = "1HR*"))).first;
//     AtomType::a1HR1 = *repository.insert (new A1HR1 ((str = "1HR1"))).first;
//     AtomType::a1HR2 = *repository.insert (new A1HR2 ((str = "1HR2"))).first;
//     AtomType::a1HR3 = *repository.insert (new A1HR3 ((str = "1HR3"))).first;
//     AtomType::a1HR4 = *repository.insert (new A1HR4 ((str = "1HR4"))).first;
//     AtomType::a1HR5 = *repository.insert (new A1HR5 ((str = "1HR5"))).first;
//     AtomType::a1HR6 = *repository.insert (new A1HR6 ((str = "1HR6"))).first;
//     AtomType::a1HR7 = *repository.insert (new A1HR7 ((str = "1HR7"))).first;
//     AtomType::a1HR8 = *repository.insert (new A1HR8 ((str = "1HR8"))).first;
//     AtomType::a1HR9 = *repository.insert (new A1HR9 ((str = "1HR9"))).first;
//     AtomType::a1HS = *repository.insert (new A1HS ((str = "1HS"))).first;
//     AtomType::a1HS1 = *repository.insert (new A1HS1 ((str = "1HS1"))).first;
//     AtomType::a1HS2 = *repository.insert (new A1HS2 ((str = "1HS2"))).first;
//     AtomType::a1HS3 = *repository.insert (new A1HS3 ((str = "1HS3"))).first;
//     AtomType::a1HS4 = *repository.insert (new A1HS4 ((str = "1HS4"))).first;
//     AtomType::a1HS5 = *repository.insert (new A1HS5 ((str = "1HS5"))).first;
//     AtomType::a1HS6 = *repository.insert (new A1HS6 ((str = "1HS6"))).first;
//     AtomType::a1HSS = *repository.insert (new A1HSS ((str = "1HSS"))).first;
//     AtomType::a1HT = *repository.insert (new A1HT ((str = "1HT"))).first;
//     AtomType::a1HT" = *repository.insert (new A1HT" ((str = "1HT""))).first;
//     AtomType::a1HT* = *repository.insert (new A1HT* ((str = "1HT*"))).first;
//     AtomType::a1HT0 = *repository.insert (new A1HT0 ((str = "1HT0"))).first;
//     AtomType::a1HT1 = *repository.insert (new A1HT1 ((str = "1HT1"))).first;
//     AtomType::a1HT2 = *repository.insert (new A1HT2 ((str = "1HT2"))).first;
//     AtomType::a1HT3 = *repository.insert (new A1HT3 ((str = "1HT3"))).first;
//     AtomType::a1HT4 = *repository.insert (new A1HT4 ((str = "1HT4"))).first;
//     AtomType::a1HT5 = *repository.insert (new A1HT5 ((str = "1HT5"))).first;
//     AtomType::a1HT6 = *repository.insert (new A1HT6 ((str = "1HT6"))).first;
//     AtomType::a1HTC = *repository.insert (new A1HTC ((str = "1HTC"))).first;
//     AtomType::a1HU = *repository.insert (new A1HU ((str = "1HU"))).first;
//     AtomType::a1HU2 = *repository.insert (new A1HU2 ((str = "1HU2"))).first;
//     AtomType::a1HU5 = *repository.insert (new A1HU5 ((str = "1HU5"))).first;
//     AtomType::a1HV = *repository.insert (new A1HV ((str = "1HV"))).first;
//     AtomType::a1HV1 = *repository.insert (new A1HV1 ((str = "1HV1"))).first;
//     AtomType::a1HV2 = *repository.insert (new A1HV2 ((str = "1HV2"))).first;
//     AtomType::a1HV3 = *repository.insert (new A1HV3 ((str = "1HV3"))).first;
//     AtomType::a1HV4 = *repository.insert (new A1HV4 ((str = "1HV4"))).first;
//     AtomType::a1HV6 = *repository.insert (new A1HV6 ((str = "1HV6"))).first;
//     AtomType::a1HV8 = *repository.insert (new A1HV8 ((str = "1HV8"))).first;
//     AtomType::a1HV9 = *repository.insert (new A1HV9 ((str = "1HV9"))).first;
//     AtomType::a1HVA = *repository.insert (new A1HVA ((str = "1HVA"))).first;
//     AtomType::a1HVB = *repository.insert (new A1HVB ((str = "1HVB"))).first;
//     AtomType::a1HW = *repository.insert (new A1HW ((str = "1HW"))).first;
//     AtomType::a1HW6 = *repository.insert (new A1HW6 ((str = "1HW6"))).first;
//     AtomType::a1HX = *repository.insert (new A1HX ((str = "1HX"))).first;
//     AtomType::a1HX* = *repository.insert (new A1HX* ((str = "1HX*"))).first;
//     AtomType::a1HX0 = *repository.insert (new A1HX0 ((str = "1HX0"))).first;
//     AtomType::a1HX1 = *repository.insert (new A1HX1 ((str = "1HX1"))).first;
//     AtomType::a1HX2 = *repository.insert (new A1HX2 ((str = "1HX2"))).first;
//     AtomType::a1HX3 = *repository.insert (new A1HX3 ((str = "1HX3"))).first;
//     AtomType::a1HX4 = *repository.insert (new A1HX4 ((str = "1HX4"))).first;
//     AtomType::a1HX5 = *repository.insert (new A1HX5 ((str = "1HX5"))).first;
//     AtomType::a1HX6 = *repository.insert (new A1HX6 ((str = "1HX6"))).first;
//     AtomType::a1HX7 = *repository.insert (new A1HX7 ((str = "1HX7"))).first;
//     AtomType::a1HX8 = *repository.insert (new A1HX8 ((str = "1HX8"))).first;
//     AtomType::a1HX9 = *repository.insert (new A1HX9 ((str = "1HX9"))).first;
//     AtomType::a1HXA = *repository.insert (new A1HXA ((str = "1HXA"))).first;
//     AtomType::a1HXB = *repository.insert (new A1HXB ((str = "1HXB"))).first;
//     AtomType::a1HXD = *repository.insert (new A1HXD ((str = "1HXD"))).first;
//     AtomType::a1HXE = *repository.insert (new A1HXE ((str = "1HXE"))).first;
//     AtomType::a1HXG = *repository.insert (new A1HXG ((str = "1HXG"))).first;
//     AtomType::a1HXT = *repository.insert (new A1HXT ((str = "1HXT"))).first;
//     AtomType::a1HY1 = *repository.insert (new A1HY1 ((str = "1HY1"))).first;
//     AtomType::a1HY2 = *repository.insert (new A1HY2 ((str = "1HY2"))).first;
//     AtomType::a1HY3 = *repository.insert (new A1HY3 ((str = "1HY3"))).first;
//     AtomType::a1HY4 = *repository.insert (new A1HY4 ((str = "1HY4"))).first;
//     AtomType::a1HY6 = *repository.insert (new A1HY6 ((str = "1HY6"))).first;
//     AtomType::a1HY7 = *repository.insert (new A1HY7 ((str = "1HY7"))).first;
//     AtomType::a1HZ* = *repository.insert (new A1HZ* ((str = "1HZ*"))).first;
//     AtomType::a1HZ1 = *repository.insert (new A1HZ1 ((str = "1HZ1"))).first;
//     AtomType::a1HZ2 = *repository.insert (new A1HZ2 ((str = "1HZ2"))).first;
//     AtomType::a1HZ3 = *repository.insert (new A1HZ3 ((str = "1HZ3"))).first;
//     AtomType::a1HZ4 = *repository.insert (new A1HZ4 ((str = "1HZ4"))).first;
//     AtomType::a1HZ5 = *repository.insert (new A1HZ5 ((str = "1HZ5"))).first;
//     AtomType::a1HZ6 = *repository.insert (new A1HZ6 ((str = "1HZ6"))).first;
//     AtomType::a1HZ7 = *repository.insert (new A1HZ7 ((str = "1HZ7"))).first;
//     AtomType::a1HZ8 = *repository.insert (new A1HZ8 ((str = "1HZ8"))).first;
//     AtomType::a1HZ9 = *repository.insert (new A1HZ9 ((str = "1HZ9"))).first;
//     AtomType::a1HZA = *repository.insert (new A1HZA ((str = "1HZA"))).first;
//     AtomType::a1HZN = *repository.insert (new A1HZN ((str = "1HZN"))).first;
//     AtomType::a1HZY = *repository.insert (new A1HZY ((str = "1HZY"))).first;
//     AtomType::a1H_2 = *repository.insert (new A1H_2 ((str = "1H_2"))).first;
//     AtomType::a1N = *repository.insert (new A1N ((str = "1N"))).first;
//     AtomType::a1N10 = *repository.insert (new A1N10 ((str = "1N10"))).first;
//     AtomType::a1N2 = *repository.insert (new A1N2 ((str = "1N2"))).first;
//     AtomType::a1ND1 = *repository.insert (new A1ND1 ((str = "1ND1"))).first;
//     AtomType::a1NE2 = *repository.insert (new A1NE2 ((str = "1NE2"))).first;
//     AtomType::a1NH = *repository.insert (new A1NH ((str = "1NH"))).first;
//     AtomType::a1NH* = *repository.insert (new A1NH* ((str = "1NH*"))).first;
//     AtomType::a1NH1 = *repository.insert (new A1NH1 ((str = "1NH1"))).first;
//     AtomType::a1NH3 = *repository.insert (new A1NH3 ((str = "1NH3"))).first;
//     AtomType::a1NH4 = *repository.insert (new A1NH4 ((str = "1NH4"))).first;
//     AtomType::a1NHO = *repository.insert (new A1NHO ((str = "1NHO"))).first;
//     AtomType::a1O = *repository.insert (new A1O ((str = "1O"))).first;
//     AtomType::a1O0* = *repository.insert (new A1O0* ((str = "1O0*"))).first;
//     AtomType::a1O1 = *repository.insert (new A1O1 ((str = "1O1"))).first;
//     AtomType::a1O2" = *repository.insert (new A1O2" ((str = "1O2""))).first;
//     AtomType::a1O2* = *repository.insert (new A1O2* ((str = "1O2*"))).first;
//     AtomType::a1O21 = *repository.insert (new A1O21 ((str = "1O21"))).first;
//     AtomType::a1O22 = *repository.insert (new A1O22 ((str = "1O22"))).first;
//     AtomType::a1O3 = *repository.insert (new A1O3 ((str = "1O3"))).first;
//     AtomType::a1O4* = *repository.insert (new A1O4* ((str = "1O4*"))).first;
//     AtomType::a1O7 = *repository.insert (new A1O7 ((str = "1O7"))).first;
//     AtomType::a1OCT = *repository.insert (new A1OCT ((str = "1OCT"))).first;
//     AtomType::a1OE1 = *repository.insert (new A1OE1 ((str = "1OE1"))).first;
//     AtomType::a1OH = *repository.insert (new A1OH ((str = "1OH"))).first;
//     AtomType::a1OM6 = *repository.insert (new A1OM6 ((str = "1OM6"))).first;
//     AtomType::a1OP = *repository.insert (new A1OP ((str = "1OP"))).first;
//     AtomType::a1OP* = *repository.insert (new A1OP* ((str = "1OP*"))).first;
//     AtomType::a1OP3 = *repository.insert (new A1OP3 ((str = "1OP3"))).first;
//     AtomType::a1OP5 = *repository.insert (new A1OP5 ((str = "1OP5"))).first;
//     AtomType::a1OXT = *repository.insert (new A1OXT ((str = "1OXT"))).first;
//     AtomType::a2BH = *repository.insert (new A2BH ((str = "2BH"))).first;
//     AtomType::a2C = *repository.insert (new A2C ((str = "2C"))).first;
//     AtomType::a2C0 = *repository.insert (new A2C0 ((str = "2C0"))).first;
//     AtomType::a2C1 = *repository.insert (new A2C1 ((str = "2C1"))).first;
//     AtomType::a2C11 = *repository.insert (new A2C11 ((str = "2C11"))).first;
//     AtomType::a2C12 = *repository.insert (new A2C12 ((str = "2C12"))).first;
//     AtomType::a2C13 = *repository.insert (new A2C13 ((str = "2C13"))).first;
//     AtomType::a2C2 = *repository.insert (new A2C2 ((str = "2C2"))).first;
//     AtomType::a2C3 = *repository.insert (new A2C3 ((str = "2C3"))).first;
//     AtomType::a2C4 = *repository.insert (new A2C4 ((str = "2C4"))).first;
//     AtomType::a2C5 = *repository.insert (new A2C5 ((str = "2C5"))).first;
//     AtomType::a2C6 = *repository.insert (new A2C6 ((str = "2C6"))).first;
//     AtomType::a2C6A = *repository.insert (new A2C6A ((str = "2C6A"))).first;
//     AtomType::a2C6B = *repository.insert (new A2C6B ((str = "2C6B"))).first;
//     AtomType::a2C7 = *repository.insert (new A2C7 ((str = "2C7"))).first;
//     AtomType::a2C8 = *repository.insert (new A2C8 ((str = "2C8"))).first;
//     AtomType::a2C9 = *repository.insert (new A2C9 ((str = "2C9"))).first;
//     AtomType::a2CA = *repository.insert (new A2CA ((str = "2CA"))).first;
//     AtomType::a2CB = *repository.insert (new A2CB ((str = "2CB"))).first;
//     AtomType::a2CD = *repository.insert (new A2CD ((str = "2CD"))).first;
//     AtomType::a2CD1 = *repository.insert (new A2CD1 ((str = "2CD1"))).first;
//     AtomType::a2CD2 = *repository.insert (new A2CD2 ((str = "2CD2"))).first;
//     AtomType::a2CD3 = *repository.insert (new A2CD3 ((str = "2CD3"))).first;
//     AtomType::a2CD4 = *repository.insert (new A2CD4 ((str = "2CD4"))).first;
//     AtomType::a2CD6 = *repository.insert (new A2CD6 ((str = "2CD6"))).first;
//     AtomType::a2CE1 = *repository.insert (new A2CE1 ((str = "2CE1"))).first;
//     AtomType::a2CE2 = *repository.insert (new A2CE2 ((str = "2CE2"))).first;
//     AtomType::a2CE3 = *repository.insert (new A2CE3 ((str = "2CE3"))).first;
//     AtomType::a2CE4 = *repository.insert (new A2CE4 ((str = "2CE4"))).first;
//     AtomType::a2CE6 = *repository.insert (new A2CE6 ((str = "2CE6"))).first;
//     AtomType::a2CEG = *repository.insert (new A2CEG ((str = "2CEG"))).first;
//     AtomType::a2CG = *repository.insert (new A2CG ((str = "2CG"))).first;
//     AtomType::a2CG2 = *repository.insert (new A2CG2 ((str = "2CG2"))).first;
//     AtomType::a2CG5 = *repository.insert (new A2CG5 ((str = "2CG5"))).first;
//     AtomType::a2CH3 = *repository.insert (new A2CH3 ((str = "2CH3"))).first;
//     AtomType::a2CL1 = *repository.insert (new A2CL1 ((str = "2CL1"))).first;
//     AtomType::a2CZ = *repository.insert (new A2CZ ((str = "2CZ"))).first;
//     AtomType::a2D = *repository.insert (new A2D ((str = "2D"))).first;
//     AtomType::a2D10 = *repository.insert (new A2D10 ((str = "2D10"))).first;
//     AtomType::a2D14 = *repository.insert (new A2D14 ((str = "2D14"))).first;
//     AtomType::a2D2 = *repository.insert (new A2D2 ((str = "2D2"))).first;
//     AtomType::a2D3 = *repository.insert (new A2D3 ((str = "2D3"))).first;
//     AtomType::a2H = *repository.insert (new A2H ((str = "2H"))).first;
//     AtomType::a2H" = *repository.insert (new A2H" ((str = "2H""))).first;
//     AtomType::a2H* = *repository.insert (new A2H* ((str = "2H*"))).first;
//     AtomType::a2H** = *repository.insert (new A2H** ((str = "2H**"))).first;
//     AtomType::a2H*0 = *repository.insert (new A2H*0 ((str = "2H*0"))).first;
//     AtomType::a2H*1 = *repository.insert (new A2H*1 ((str = "2H*1"))).first;
//     AtomType::a2H*2 = *repository.insert (new A2H*2 ((str = "2H*2"))).first;
//     AtomType::a2H*3 = *repository.insert (new A2H*3 ((str = "2H*3"))).first;
//     AtomType::a2H*4 = *repository.insert (new A2H*4 ((str = "2H*4"))).first;
//     AtomType::a2H*5 = *repository.insert (new A2H*5 ((str = "2H*5"))).first;
//     AtomType::a2H*7 = *repository.insert (new A2H*7 ((str = "2H*7"))).first;
//     AtomType::a2H*8 = *repository.insert (new A2H*8 ((str = "2H*8"))).first;
//     AtomType::a2H*A = *repository.insert (new A2H*A ((str = "2H*A"))).first;
//     AtomType::a2H*C = *repository.insert (new A2H*C ((str = "2H*C"))).first;
//     AtomType::a2H0 = *repository.insert (new A2H0 ((str = "2H0"))).first;
//     AtomType::a2H0* = *repository.insert (new A2H0* ((str = "2H0*"))).first;
//     AtomType::a2H01 = *repository.insert (new A2H01 ((str = "2H01"))).first;
//     AtomType::a2H02 = *repository.insert (new A2H02 ((str = "2H02"))).first;
//     AtomType::a2H03 = *repository.insert (new A2H03 ((str = "2H03"))).first;
//     AtomType::a2H04 = *repository.insert (new A2H04 ((str = "2H04"))).first;
//     AtomType::a2H05 = *repository.insert (new A2H05 ((str = "2H05"))).first;
//     AtomType::a2H06 = *repository.insert (new A2H06 ((str = "2H06"))).first;
//     AtomType::a2H07 = *repository.insert (new A2H07 ((str = "2H07"))).first;
//     AtomType::a2H08 = *repository.insert (new A2H08 ((str = "2H08"))).first;
//     AtomType::a2H09 = *repository.insert (new A2H09 ((str = "2H09"))).first;
//     AtomType::a2H0A = *repository.insert (new A2H0A ((str = "2H0A"))).first;
//     AtomType::a2H0B = *repository.insert (new A2H0B ((str = "2H0B"))).first;
//     AtomType::a2H0C = *repository.insert (new A2H0C ((str = "2H0C"))).first;
//     AtomType::a2H0E = *repository.insert (new A2H0E ((str = "2H0E"))).first;
//     AtomType::a2H0I = *repository.insert (new A2H0I ((str = "2H0I"))).first;
//     AtomType::a2H0J = *repository.insert (new A2H0J ((str = "2H0J"))).first;
//     AtomType::a2H0K = *repository.insert (new A2H0K ((str = "2H0K"))).first;
//     AtomType::a2H0N = *repository.insert (new A2H0N ((str = "2H0N"))).first;
//     AtomType::a2H0P = *repository.insert (new A2H0P ((str = "2H0P"))).first;
//     AtomType::a2H0Q = *repository.insert (new A2H0Q ((str = "2H0Q"))).first;
//     AtomType::a2H0R = *repository.insert (new A2H0R ((str = "2H0R"))).first;
//     AtomType::a2H0S = *repository.insert (new A2H0S ((str = "2H0S"))).first;
//     AtomType::a2H0T = *repository.insert (new A2H0T ((str = "2H0T"))).first;
//     AtomType::a2H0X = *repository.insert (new A2H0X ((str = "2H0X"))).first;
//     AtomType::a2H1 = *repository.insert (new A2H1 ((str = "2H1"))).first;
//     AtomType::a2H1" = *repository.insert (new A2H1" ((str = "2H1""))).first;
//     AtomType::a2H1* = *repository.insert (new A2H1* ((str = "2H1*"))).first;
//     AtomType::a2H10 = *repository.insert (new A2H10 ((str = "2H10"))).first;
//     AtomType::a2H10A = *repository.insert (new A2H10A ((str = "2H10A"))).first;
//     AtomType::a2H10B = *repository.insert (new A2H10B ((str = "2H10B"))).first;
//     AtomType::a2H11 = *repository.insert (new A2H11 ((str = "2H11"))).first;
//     AtomType::a2H11A = *repository.insert (new A2H11A ((str = "2H11A"))).first;
//     AtomType::a2H11B = *repository.insert (new A2H11B ((str = "2H11B"))).first;
//     AtomType::a2H12 = *repository.insert (new A2H12 ((str = "2H12"))).first;
//     AtomType::a2H12A = *repository.insert (new A2H12A ((str = "2H12A"))).first;
//     AtomType::a2H12B = *repository.insert (new A2H12B ((str = "2H12B"))).first;
//     AtomType::a2H13 = *repository.insert (new A2H13 ((str = "2H13"))).first;
//     AtomType::a2H13A = *repository.insert (new A2H13A ((str = "2H13A"))).first;
//     AtomType::a2H13B = *repository.insert (new A2H13B ((str = "2H13B"))).first;
//     AtomType::a2H14 = *repository.insert (new A2H14 ((str = "2H14"))).first;
//     AtomType::a2H14A = *repository.insert (new A2H14A ((str = "2H14A"))).first;
//     AtomType::a2H14B = *repository.insert (new A2H14B ((str = "2H14B"))).first;
//     AtomType::a2H15 = *repository.insert (new A2H15 ((str = "2H15"))).first;
//     AtomType::a2H15* = *repository.insert (new A2H15* ((str = "2H15*"))).first;
//     AtomType::a2H15B = *repository.insert (new A2H15B ((str = "2H15B"))).first;
//     AtomType::a2H16 = *repository.insert (new A2H16 ((str = "2H16"))).first;
//     AtomType::a2H16B = *repository.insert (new A2H16B ((str = "2H16B"))).first;
//     AtomType::a2H17 = *repository.insert (new A2H17 ((str = "2H17"))).first;
//     AtomType::a2H18 = *repository.insert (new A2H18 ((str = "2H18"))).first;
//     AtomType::a2H19 = *repository.insert (new A2H19 ((str = "2H19"))).first;
//     AtomType::a2H1A = *repository.insert (new A2H1A ((str = "2H1A"))).first;
//     AtomType::a2H1B = *repository.insert (new A2H1B ((str = "2H1B"))).first;
//     AtomType::a2H1C = *repository.insert (new A2H1C ((str = "2H1C"))).first;
//     AtomType::a2H1D = *repository.insert (new A2H1D ((str = "2H1D"))).first;
//     AtomType::a2H1E = *repository.insert (new A2H1E ((str = "2H1E"))).first;
//     AtomType::a2H1F = *repository.insert (new A2H1F ((str = "2H1F"))).first;
//     AtomType::a2H1G = *repository.insert (new A2H1G ((str = "2H1G"))).first;
//     AtomType::a2H1H = *repository.insert (new A2H1H ((str = "2H1H"))).first;
//     AtomType::a2H1I = *repository.insert (new A2H1I ((str = "2H1I"))).first;
//     AtomType::a2H1L = *repository.insert (new A2H1L ((str = "2H1L"))).first;
//     AtomType::a2H1M = *repository.insert (new A2H1M ((str = "2H1M"))).first;
//     AtomType::a2H1N = *repository.insert (new A2H1N ((str = "2H1N"))).first;
//     AtomType::a2H1P = *repository.insert (new A2H1P ((str = "2H1P"))).first;
//     AtomType::a2H1R = *repository.insert (new A2H1R ((str = "2H1R"))).first;
//     AtomType::a2H1S = *repository.insert (new A2H1S ((str = "2H1S"))).first;
//     AtomType::a2H1T = *repository.insert (new A2H1T ((str = "2H1T"))).first;
//     AtomType::a2H1V = *repository.insert (new A2H1V ((str = "2H1V"))).first;
//     AtomType::a2H1X = *repository.insert (new A2H1X ((str = "2H1X"))).first;
//     AtomType::a2H1Y = *repository.insert (new A2H1Y ((str = "2H1Y"))).first;
//     AtomType::a2H2 = *repository.insert (new A2H2 ((str = "2H2"))).first;
//     AtomType::a2H2" = *repository.insert (new A2H2" ((str = "2H2""))).first;
//     AtomType::a2H2* = *repository.insert (new A2H2* ((str = "2H2*"))).first;
//     AtomType::a2H20 = *repository.insert (new A2H20 ((str = "2H20"))).first;
//     AtomType::a2H21 = *repository.insert (new A2H21 ((str = "2H21"))).first;
//     AtomType::a2H22 = *repository.insert (new A2H22 ((str = "2H22"))).first;
//     AtomType::a2H23 = *repository.insert (new A2H23 ((str = "2H23"))).first;
//     AtomType::a2H24 = *repository.insert (new A2H24 ((str = "2H24"))).first;
//     AtomType::a2H25 = *repository.insert (new A2H25 ((str = "2H25"))).first;
//     AtomType::a2H25* = *repository.insert (new A2H25* ((str = "2H25*"))).first;
//     AtomType::a2H26 = *repository.insert (new A2H26 ((str = "2H26"))).first;
//     AtomType::a2H27 = *repository.insert (new A2H27 ((str = "2H27"))).first;
//     AtomType::a2H28 = *repository.insert (new A2H28 ((str = "2H28"))).first;
//     AtomType::a2H29 = *repository.insert (new A2H29 ((str = "2H29"))).first;
//     AtomType::a2H2A = *repository.insert (new A2H2A ((str = "2H2A"))).first;
//     AtomType::a2H2B = *repository.insert (new A2H2B ((str = "2H2B"))).first;
//     AtomType::a2H2C = *repository.insert (new A2H2C ((str = "2H2C"))).first;
//     AtomType::a2H2D = *repository.insert (new A2H2D ((str = "2H2D"))).first;
//     AtomType::a2H2E = *repository.insert (new A2H2E ((str = "2H2E"))).first;
//     AtomType::a2H2F = *repository.insert (new A2H2F ((str = "2H2F"))).first;
//     AtomType::a2H2G = *repository.insert (new A2H2G ((str = "2H2G"))).first;
//     AtomType::a2H2H = *repository.insert (new A2H2H ((str = "2H2H"))).first;
//     AtomType::a2H2I = *repository.insert (new A2H2I ((str = "2H2I"))).first;
//     AtomType::a2H2J = *repository.insert (new A2H2J ((str = "2H2J"))).first;
//     AtomType::a2H2L = *repository.insert (new A2H2L ((str = "2H2L"))).first;
//     AtomType::a2H2M = *repository.insert (new A2H2M ((str = "2H2M"))).first;
//     AtomType::a2H2N = *repository.insert (new A2H2N ((str = "2H2N"))).first;
//     AtomType::a2H2O = *repository.insert (new A2H2O ((str = "2H2O"))).first;
//     AtomType::a2H2P = *repository.insert (new A2H2P ((str = "2H2P"))).first;
//     AtomType::a2H2R = *repository.insert (new A2H2R ((str = "2H2R"))).first;
//     AtomType::a2H2S = *repository.insert (new A2H2S ((str = "2H2S"))).first;
//     AtomType::a2H2T = *repository.insert (new A2H2T ((str = "2H2T"))).first;
//     AtomType::a2H2V = *repository.insert (new A2H2V ((str = "2H2V"))).first;
//     AtomType::a2H2X = *repository.insert (new A2H2X ((str = "2H2X"))).first;
//     AtomType::a2H2Y = *repository.insert (new A2H2Y ((str = "2H2Y"))).first;
//     AtomType::a2H2Z = *repository.insert (new A2H2Z ((str = "2H2Z"))).first;
//     AtomType::a2H3 = *repository.insert (new A2H3 ((str = "2H3"))).first;
//     AtomType::a2H3" = *repository.insert (new A2H3" ((str = "2H3""))).first;
//     AtomType::a2H3* = *repository.insert (new A2H3* ((str = "2H3*"))).first;
//     AtomType::a2H30 = *repository.insert (new A2H30 ((str = "2H30"))).first;
//     AtomType::a2H31 = *repository.insert (new A2H31 ((str = "2H31"))).first;
//     AtomType::a2H32 = *repository.insert (new A2H32 ((str = "2H32"))).first;
//     AtomType::a2H33 = *repository.insert (new A2H33 ((str = "2H33"))).first;
//     AtomType::a2H34 = *repository.insert (new A2H34 ((str = "2H34"))).first;
//     AtomType::a2H35 = *repository.insert (new A2H35 ((str = "2H35"))).first;
//     AtomType::a2H36 = *repository.insert (new A2H36 ((str = "2H36"))).first;
//     AtomType::a2H37 = *repository.insert (new A2H37 ((str = "2H37"))).first;
//     AtomType::a2H38 = *repository.insert (new A2H38 ((str = "2H38"))).first;
//     AtomType::a2H39 = *repository.insert (new A2H39 ((str = "2H39"))).first;
//     AtomType::a2H3A = *repository.insert (new A2H3A ((str = "2H3A"))).first;
//     AtomType::a2H3B = *repository.insert (new A2H3B ((str = "2H3B"))).first;
//     AtomType::a2H3C = *repository.insert (new A2H3C ((str = "2H3C"))).first;
//     AtomType::a2H3D = *repository.insert (new A2H3D ((str = "2H3D"))).first;
//     AtomType::a2H3E = *repository.insert (new A2H3E ((str = "2H3E"))).first;
//     AtomType::a2H3F = *repository.insert (new A2H3F ((str = "2H3F"))).first;
//     AtomType::a2H3G = *repository.insert (new A2H3G ((str = "2H3G"))).first;
//     AtomType::a2H3H = *repository.insert (new A2H3H ((str = "2H3H"))).first;
//     AtomType::a2H3I = *repository.insert (new A2H3I ((str = "2H3I"))).first;
//     AtomType::a2H3L = *repository.insert (new A2H3L ((str = "2H3L"))).first;
//     AtomType::a2H3M = *repository.insert (new A2H3M ((str = "2H3M"))).first;
//     AtomType::a2H3N = *repository.insert (new A2H3N ((str = "2H3N"))).first;
//     AtomType::a2H3O = *repository.insert (new A2H3O ((str = "2H3O"))).first;
//     AtomType::a2H3P = *repository.insert (new A2H3P ((str = "2H3P"))).first;
//     AtomType::a2H3R = *repository.insert (new A2H3R ((str = "2H3R"))).first;
//     AtomType::a2H3S = *repository.insert (new A2H3S ((str = "2H3S"))).first;
//     AtomType::a2H3T = *repository.insert (new A2H3T ((str = "2H3T"))).first;
//     AtomType::a2H3U = *repository.insert (new A2H3U ((str = "2H3U"))).first;
//     AtomType::a2H3X = *repository.insert (new A2H3X ((str = "2H3X"))).first;
//     AtomType::a2H4 = *repository.insert (new A2H4 ((str = "2H4"))).first;
//     AtomType::a2H4" = *repository.insert (new A2H4" ((str = "2H4""))).first;
//     AtomType::a2H4* = *repository.insert (new A2H4* ((str = "2H4*"))).first;
//     AtomType::a2H40 = *repository.insert (new A2H40 ((str = "2H40"))).first;
//     AtomType::a2H41 = *repository.insert (new A2H41 ((str = "2H41"))).first;
//     AtomType::a2H42 = *repository.insert (new A2H42 ((str = "2H42"))).first;
//     AtomType::a2H43 = *repository.insert (new A2H43 ((str = "2H43"))).first;
//     AtomType::a2H44 = *repository.insert (new A2H44 ((str = "2H44"))).first;
//     AtomType::a2H45 = *repository.insert (new A2H45 ((str = "2H45"))).first;
//     AtomType::a2H46 = *repository.insert (new A2H46 ((str = "2H46"))).first;
//     AtomType::a2H47 = *repository.insert (new A2H47 ((str = "2H47"))).first;
//     AtomType::a2H48 = *repository.insert (new A2H48 ((str = "2H48"))).first;
//     AtomType::a2H49 = *repository.insert (new A2H49 ((str = "2H49"))).first;
//     AtomType::a2H4A = *repository.insert (new A2H4A ((str = "2H4A"))).first;
//     AtomType::a2H4B = *repository.insert (new A2H4B ((str = "2H4B"))).first;
//     AtomType::a2H4C = *repository.insert (new A2H4C ((str = "2H4C"))).first;
//     AtomType::a2H4D = *repository.insert (new A2H4D ((str = "2H4D"))).first;
//     AtomType::a2H4E = *repository.insert (new A2H4E ((str = "2H4E"))).first;
//     AtomType::a2H4F = *repository.insert (new A2H4F ((str = "2H4F"))).first;
//     AtomType::a2H4G = *repository.insert (new A2H4G ((str = "2H4G"))).first;
//     AtomType::a2H4H = *repository.insert (new A2H4H ((str = "2H4H"))).first;
//     AtomType::a2H4I = *repository.insert (new A2H4I ((str = "2H4I"))).first;
//     AtomType::a2H4J = *repository.insert (new A2H4J ((str = "2H4J"))).first;
//     AtomType::a2H4M = *repository.insert (new A2H4M ((str = "2H4M"))).first;
//     AtomType::a2H4N = *repository.insert (new A2H4N ((str = "2H4N"))).first;
//     AtomType::a2H4P = *repository.insert (new A2H4P ((str = "2H4P"))).first;
//     AtomType::a2H4R = *repository.insert (new A2H4R ((str = "2H4R"))).first;
//     AtomType::a2H4S = *repository.insert (new A2H4S ((str = "2H4S"))).first;
//     AtomType::a2H4T = *repository.insert (new A2H4T ((str = "2H4T"))).first;
//     AtomType::a2H4X = *repository.insert (new A2H4X ((str = "2H4X"))).first;
//     AtomType::a2H5 = *repository.insert (new A2H5 ((str = "2H5"))).first;
//     AtomType::a2H5" = *repository.insert (new A2H5" ((str = "2H5""))).first;
//     AtomType::a2H50 = *repository.insert (new A2H50 ((str = "2H50"))).first;
//     AtomType::a2H51 = *repository.insert (new A2H51 ((str = "2H51"))).first;
//     AtomType::a2H52 = *repository.insert (new A2H52 ((str = "2H52"))).first;
//     AtomType::a2H53 = *repository.insert (new A2H53 ((str = "2H53"))).first;
//     AtomType::a2H54 = *repository.insert (new A2H54 ((str = "2H54"))).first;
//     AtomType::a2H55 = *repository.insert (new A2H55 ((str = "2H55"))).first;
//     AtomType::a2H56 = *repository.insert (new A2H56 ((str = "2H56"))).first;
//     AtomType::a2H57 = *repository.insert (new A2H57 ((str = "2H57"))).first;
//     AtomType::a2H58 = *repository.insert (new A2H58 ((str = "2H58"))).first;
//     AtomType::a2H59 = *repository.insert (new A2H59 ((str = "2H59"))).first;
//     AtomType::a2H5B = *repository.insert (new A2H5B ((str = "2H5B"))).first;
//     AtomType::a2H5C = *repository.insert (new A2H5C ((str = "2H5C"))).first;
//     AtomType::a2H5D = *repository.insert (new A2H5D ((str = "2H5D"))).first;
//     AtomType::a2H5E = *repository.insert (new A2H5E ((str = "2H5E"))).first;
//     AtomType::a2H5F = *repository.insert (new A2H5F ((str = "2H5F"))).first;
//     AtomType::a2H5G = *repository.insert (new A2H5G ((str = "2H5G"))).first;
//     AtomType::a2H5J = *repository.insert (new A2H5J ((str = "2H5J"))).first;
//     AtomType::a2H5M = *repository.insert (new A2H5M ((str = "2H5M"))).first;
//     AtomType::a2H5N = *repository.insert (new A2H5N ((str = "2H5N"))).first;
//     AtomType::a2H5P = *repository.insert (new A2H5P ((str = "2H5P"))).first;
//     AtomType::a2H5R = *repository.insert (new A2H5R ((str = "2H5R"))).first;
//     AtomType::a2H5S = *repository.insert (new A2H5S ((str = "2H5S"))).first;
//     AtomType::a2H5T = *repository.insert (new A2H5T ((str = "2H5T"))).first;
//     AtomType::a2H5U = *repository.insert (new A2H5U ((str = "2H5U"))).first;
//     AtomType::a2H5X = *repository.insert (new A2H5X ((str = "2H5X"))).first;
//     AtomType::a2H6 = *repository.insert (new A2H6 ((str = "2H6"))).first;
//     AtomType::a2H6" = *repository.insert (new A2H6" ((str = "2H6""))).first;
//     AtomType::a2H6* = *repository.insert (new A2H6* ((str = "2H6*"))).first;
//     AtomType::a2H60 = *repository.insert (new A2H60 ((str = "2H60"))).first;
//     AtomType::a2H61 = *repository.insert (new A2H61 ((str = "2H61"))).first;
//     AtomType::a2H62 = *repository.insert (new A2H62 ((str = "2H62"))).first;
//     AtomType::a2H63 = *repository.insert (new A2H63 ((str = "2H63"))).first;
//     AtomType::a2H64 = *repository.insert (new A2H64 ((str = "2H64"))).first;
//     AtomType::a2H65 = *repository.insert (new A2H65 ((str = "2H65"))).first;
//     AtomType::a2H66 = *repository.insert (new A2H66 ((str = "2H66"))).first;
//     AtomType::a2H67 = *repository.insert (new A2H67 ((str = "2H67"))).first;
//     AtomType::a2H68 = *repository.insert (new A2H68 ((str = "2H68"))).first;
//     AtomType::a2H69 = *repository.insert (new A2H69 ((str = "2H69"))).first;
//     AtomType::a2H6A = *repository.insert (new A2H6A ((str = "2H6A"))).first;
//     AtomType::a2H6B = *repository.insert (new A2H6B ((str = "2H6B"))).first;
//     AtomType::a2H6C = *repository.insert (new A2H6C ((str = "2H6C"))).first;
//     AtomType::a2H6D = *repository.insert (new A2H6D ((str = "2H6D"))).first;
//     AtomType::a2H6E = *repository.insert (new A2H6E ((str = "2H6E"))).first;
//     AtomType::a2H6F = *repository.insert (new A2H6F ((str = "2H6F"))).first;
//     AtomType::a2H6G = *repository.insert (new A2H6G ((str = "2H6G"))).first;
//     AtomType::a2H6H = *repository.insert (new A2H6H ((str = "2H6H"))).first;
//     AtomType::a2H6I = *repository.insert (new A2H6I ((str = "2H6I"))).first;
//     AtomType::a2H6J = *repository.insert (new A2H6J ((str = "2H6J"))).first;
//     AtomType::a2H6K = *repository.insert (new A2H6K ((str = "2H6K"))).first;
//     AtomType::a2H6L = *repository.insert (new A2H6L ((str = "2H6L"))).first;
//     AtomType::a2H6M = *repository.insert (new A2H6M ((str = "2H6M"))).first;
//     AtomType::a2H6N = *repository.insert (new A2H6N ((str = "2H6N"))).first;
//     AtomType::a2H6P = *repository.insert (new A2H6P ((str = "2H6P"))).first;
//     AtomType::a2H6R = *repository.insert (new A2H6R ((str = "2H6R"))).first;
//     AtomType::a2H6S = *repository.insert (new A2H6S ((str = "2H6S"))).first;
//     AtomType::a2H6T = *repository.insert (new A2H6T ((str = "2H6T"))).first;
//     AtomType::a2H6W = *repository.insert (new A2H6W ((str = "2H6W"))).first;
//     AtomType::a2H6X = *repository.insert (new A2H6X ((str = "2H6X"))).first;
//     AtomType::a2H6Y = *repository.insert (new A2H6Y ((str = "2H6Y"))).first;
//     AtomType::a2H6Z = *repository.insert (new A2H6Z ((str = "2H6Z"))).first;
//     AtomType::a2H7 = *repository.insert (new A2H7 ((str = "2H7"))).first;
//     AtomType::a2H7" = *repository.insert (new A2H7" ((str = "2H7""))).first;
//     AtomType::a2H7* = *repository.insert (new A2H7* ((str = "2H7*"))).first;
//     AtomType::a2H70 = *repository.insert (new A2H70 ((str = "2H70"))).first;
//     AtomType::a2H71 = *repository.insert (new A2H71 ((str = "2H71"))).first;
//     AtomType::a2H72 = *repository.insert (new A2H72 ((str = "2H72"))).first;
//     AtomType::a2H73 = *repository.insert (new A2H73 ((str = "2H73"))).first;
//     AtomType::a2H74 = *repository.insert (new A2H74 ((str = "2H74"))).first;
//     AtomType::a2H75 = *repository.insert (new A2H75 ((str = "2H75"))).first;
//     AtomType::a2H76 = *repository.insert (new A2H76 ((str = "2H76"))).first;
//     AtomType::a2H77 = *repository.insert (new A2H77 ((str = "2H77"))).first;
//     AtomType::a2H78 = *repository.insert (new A2H78 ((str = "2H78"))).first;
//     AtomType::a2H79 = *repository.insert (new A2H79 ((str = "2H79"))).first;
//     AtomType::a2H7A = *repository.insert (new A2H7A ((str = "2H7A"))).first;
//     AtomType::a2H7B = *repository.insert (new A2H7B ((str = "2H7B"))).first;
//     AtomType::a2H7C = *repository.insert (new A2H7C ((str = "2H7C"))).first;
//     AtomType::a2H7D = *repository.insert (new A2H7D ((str = "2H7D"))).first;
//     AtomType::a2H7E = *repository.insert (new A2H7E ((str = "2H7E"))).first;
//     AtomType::a2H7F = *repository.insert (new A2H7F ((str = "2H7F"))).first;
//     AtomType::a2H7H = *repository.insert (new A2H7H ((str = "2H7H"))).first;
//     AtomType::a2H7I = *repository.insert (new A2H7I ((str = "2H7I"))).first;
//     AtomType::a2H7J = *repository.insert (new A2H7J ((str = "2H7J"))).first;
//     AtomType::a2H7M = *repository.insert (new A2H7M ((str = "2H7M"))).first;
//     AtomType::a2H7N = *repository.insert (new A2H7N ((str = "2H7N"))).first;
//     AtomType::a2H7P = *repository.insert (new A2H7P ((str = "2H7P"))).first;
//     AtomType::a2H7R = *repository.insert (new A2H7R ((str = "2H7R"))).first;
//     AtomType::a2H7S = *repository.insert (new A2H7S ((str = "2H7S"))).first;
//     AtomType::a2H7T = *repository.insert (new A2H7T ((str = "2H7T"))).first;
//     AtomType::a2H7Z = *repository.insert (new A2H7Z ((str = "2H7Z"))).first;
//     AtomType::a2H8 = *repository.insert (new A2H8 ((str = "2H8"))).first;
//     AtomType::a2H8" = *repository.insert (new A2H8" ((str = "2H8""))).first;
//     AtomType::a2H8* = *repository.insert (new A2H8* ((str = "2H8*"))).first;
//     AtomType::a2H80 = *repository.insert (new A2H80 ((str = "2H80"))).first;
//     AtomType::a2H81 = *repository.insert (new A2H81 ((str = "2H81"))).first;
//     AtomType::a2H82 = *repository.insert (new A2H82 ((str = "2H82"))).first;
//     AtomType::a2H83 = *repository.insert (new A2H83 ((str = "2H83"))).first;
//     AtomType::a2H84 = *repository.insert (new A2H84 ((str = "2H84"))).first;
//     AtomType::a2H85 = *repository.insert (new A2H85 ((str = "2H85"))).first;
//     AtomType::a2H86 = *repository.insert (new A2H86 ((str = "2H86"))).first;
//     AtomType::a2H87 = *repository.insert (new A2H87 ((str = "2H87"))).first;
//     AtomType::a2H88 = *repository.insert (new A2H88 ((str = "2H88"))).first;
//     AtomType::a2H89 = *repository.insert (new A2H89 ((str = "2H89"))).first;
//     AtomType::a2H8A = *repository.insert (new A2H8A ((str = "2H8A"))).first;
//     AtomType::a2H8B = *repository.insert (new A2H8B ((str = "2H8B"))).first;
//     AtomType::a2H8C = *repository.insert (new A2H8C ((str = "2H8C"))).first;
//     AtomType::a2H8D = *repository.insert (new A2H8D ((str = "2H8D"))).first;
//     AtomType::a2H8E = *repository.insert (new A2H8E ((str = "2H8E"))).first;
//     AtomType::a2H8F = *repository.insert (new A2H8F ((str = "2H8F"))).first;
//     AtomType::a2H8I = *repository.insert (new A2H8I ((str = "2H8I"))).first;
//     AtomType::a2H8J = *repository.insert (new A2H8J ((str = "2H8J"))).first;
//     AtomType::a2H8M = *repository.insert (new A2H8M ((str = "2H8M"))).first;
//     AtomType::a2H8N = *repository.insert (new A2H8N ((str = "2H8N"))).first;
//     AtomType::a2H8S = *repository.insert (new A2H8S ((str = "2H8S"))).first;
//     AtomType::a2H9 = *repository.insert (new A2H9 ((str = "2H9"))).first;
//     AtomType::a2H9" = *repository.insert (new A2H9" ((str = "2H9""))).first;
//     AtomType::a2H9* = *repository.insert (new A2H9* ((str = "2H9*"))).first;
//     AtomType::a2H90 = *repository.insert (new A2H90 ((str = "2H90"))).first;
//     AtomType::a2H91 = *repository.insert (new A2H91 ((str = "2H91"))).first;
//     AtomType::a2H92 = *repository.insert (new A2H92 ((str = "2H92"))).first;
//     AtomType::a2H93 = *repository.insert (new A2H93 ((str = "2H93"))).first;
//     AtomType::a2H94 = *repository.insert (new A2H94 ((str = "2H94"))).first;
//     AtomType::a2H95 = *repository.insert (new A2H95 ((str = "2H95"))).first;
//     AtomType::a2H96 = *repository.insert (new A2H96 ((str = "2H96"))).first;
//     AtomType::a2H97 = *repository.insert (new A2H97 ((str = "2H97"))).first;
//     AtomType::a2H98 = *repository.insert (new A2H98 ((str = "2H98"))).first;
//     AtomType::a2H99 = *repository.insert (new A2H99 ((str = "2H99"))).first;
//     AtomType::a2H9A = *repository.insert (new A2H9A ((str = "2H9A"))).first;
//     AtomType::a2H9B = *repository.insert (new A2H9B ((str = "2H9B"))).first;
//     AtomType::a2H9C = *repository.insert (new A2H9C ((str = "2H9C"))).first;
//     AtomType::a2H9D = *repository.insert (new A2H9D ((str = "2H9D"))).first;
//     AtomType::a2H9E = *repository.insert (new A2H9E ((str = "2H9E"))).first;
//     AtomType::a2H9F = *repository.insert (new A2H9F ((str = "2H9F"))).first;
//     AtomType::a2H9J = *repository.insert (new A2H9J ((str = "2H9J"))).first;
//     AtomType::a2H9M = *repository.insert (new A2H9M ((str = "2H9M"))).first;
//     AtomType::a2H9N = *repository.insert (new A2H9N ((str = "2H9N"))).first;
//     AtomType::a2H9S = *repository.insert (new A2H9S ((str = "2H9S"))).first;
//     AtomType::a2HA" = *repository.insert (new A2HA" ((str = "2HA""))).first;
//     AtomType::a2HA* = *repository.insert (new A2HA* ((str = "2HA*"))).first;
//     AtomType::a2HA1 = *repository.insert (new A2HA1 ((str = "2HA1"))).first;
//     AtomType::a2HA2 = *repository.insert (new A2HA2 ((str = "2HA2"))).first;
//     AtomType::a2HA3 = *repository.insert (new A2HA3 ((str = "2HA3"))).first;
//     AtomType::a2HA4 = *repository.insert (new A2HA4 ((str = "2HA4"))).first;
//     AtomType::a2HA5 = *repository.insert (new A2HA5 ((str = "2HA5"))).first;
//     AtomType::a2HA6 = *repository.insert (new A2HA6 ((str = "2HA6"))).first;
//     AtomType::a2HA7 = *repository.insert (new A2HA7 ((str = "2HA7"))).first;
//     AtomType::a2HA8 = *repository.insert (new A2HA8 ((str = "2HA8"))).first;
//     AtomType::a2HA9 = *repository.insert (new A2HA9 ((str = "2HA9"))).first;
//     AtomType::a2HAA = *repository.insert (new A2HAA ((str = "2HAA"))).first;
//     AtomType::a2HAB = *repository.insert (new A2HAB ((str = "2HAB"))).first;
//     AtomType::a2HAC = *repository.insert (new A2HAC ((str = "2HAC"))).first;
//     AtomType::a2HAD = *repository.insert (new A2HAD ((str = "2HAD"))).first;
//     AtomType::a2HAE = *repository.insert (new A2HAE ((str = "2HAE"))).first;
//     AtomType::a2HAF = *repository.insert (new A2HAF ((str = "2HAF"))).first;
//     AtomType::a2HAG = *repository.insert (new A2HAG ((str = "2HAG"))).first;
//     AtomType::a2HAH = *repository.insert (new A2HAH ((str = "2HAH"))).first;
//     AtomType::a2HAI = *repository.insert (new A2HAI ((str = "2HAI"))).first;
//     AtomType::a2HAJ = *repository.insert (new A2HAJ ((str = "2HAJ"))).first;
//     AtomType::a2HAK = *repository.insert (new A2HAK ((str = "2HAK"))).first;
//     AtomType::a2HAL = *repository.insert (new A2HAL ((str = "2HAL"))).first;
//     AtomType::a2HAM = *repository.insert (new A2HAM ((str = "2HAM"))).first;
//     AtomType::a2HAN = *repository.insert (new A2HAN ((str = "2HAN"))).first;
//     AtomType::a2HAO = *repository.insert (new A2HAO ((str = "2HAO"))).first;
//     AtomType::a2HAP = *repository.insert (new A2HAP ((str = "2HAP"))).first;
//     AtomType::a2HAQ = *repository.insert (new A2HAQ ((str = "2HAQ"))).first;
//     AtomType::a2HAR = *repository.insert (new A2HAR ((str = "2HAR"))).first;
//     AtomType::a2HAS = *repository.insert (new A2HAS ((str = "2HAS"))).first;
//     AtomType::a2HAT = *repository.insert (new A2HAT ((str = "2HAT"))).first;
//     AtomType::a2HAU = *repository.insert (new A2HAU ((str = "2HAU"))).first;
//     AtomType::a2HAV = *repository.insert (new A2HAV ((str = "2HAV"))).first;
//     AtomType::a2HAW = *repository.insert (new A2HAW ((str = "2HAW"))).first;
//     AtomType::a2HAX = *repository.insert (new A2HAX ((str = "2HAX"))).first;
//     AtomType::a2HAY = *repository.insert (new A2HAY ((str = "2HAY"))).first;
//     AtomType::a2HAZ = *repository.insert (new A2HAZ ((str = "2HAZ"))).first;
//     AtomType::a2HB" = *repository.insert (new A2HB" ((str = "2HB""))).first;
//     AtomType::a2HB* = *repository.insert (new A2HB* ((str = "2HB*"))).first;
//     AtomType::a2HB0 = *repository.insert (new A2HB0 ((str = "2HB0"))).first;
//     AtomType::a2HB1 = *repository.insert (new A2HB1 ((str = "2HB1"))).first;
//     AtomType::a2HB2 = *repository.insert (new A2HB2 ((str = "2HB2"))).first;
//     AtomType::a2HB3 = *repository.insert (new A2HB3 ((str = "2HB3"))).first;
//     AtomType::a2HB4 = *repository.insert (new A2HB4 ((str = "2HB4"))).first;
//     AtomType::a2HB5 = *repository.insert (new A2HB5 ((str = "2HB5"))).first;
//     AtomType::a2HB6 = *repository.insert (new A2HB6 ((str = "2HB6"))).first;
//     AtomType::a2HB7 = *repository.insert (new A2HB7 ((str = "2HB7"))).first;
//     AtomType::a2HB8 = *repository.insert (new A2HB8 ((str = "2HB8"))).first;
//     AtomType::a2HB9 = *repository.insert (new A2HB9 ((str = "2HB9"))).first;
//     AtomType::a2HBA = *repository.insert (new A2HBA ((str = "2HBA"))).first;
//     AtomType::a2HBB = *repository.insert (new A2HBB ((str = "2HBB"))).first;
//     AtomType::a2HBC = *repository.insert (new A2HBC ((str = "2HBC"))).first;
//     AtomType::a2HBD = *repository.insert (new A2HBD ((str = "2HBD"))).first;
//     AtomType::a2HBE = *repository.insert (new A2HBE ((str = "2HBE"))).first;
//     AtomType::a2HBF = *repository.insert (new A2HBF ((str = "2HBF"))).first;
//     AtomType::a2HBG = *repository.insert (new A2HBG ((str = "2HBG"))).first;
//     AtomType::a2HBH = *repository.insert (new A2HBH ((str = "2HBH"))).first;
//     AtomType::a2HBI = *repository.insert (new A2HBI ((str = "2HBI"))).first;
//     AtomType::a2HBJ = *repository.insert (new A2HBJ ((str = "2HBJ"))).first;
//     AtomType::a2HBK = *repository.insert (new A2HBK ((str = "2HBK"))).first;
//     AtomType::a2HBL = *repository.insert (new A2HBL ((str = "2HBL"))).first;
//     AtomType::a2HBM = *repository.insert (new A2HBM ((str = "2HBM"))).first;
//     AtomType::a2HBN = *repository.insert (new A2HBN ((str = "2HBN"))).first;
//     AtomType::a2HBO = *repository.insert (new A2HBO ((str = "2HBO"))).first;
//     AtomType::a2HBP = *repository.insert (new A2HBP ((str = "2HBP"))).first;
//     AtomType::a2HBQ = *repository.insert (new A2HBQ ((str = "2HBQ"))).first;
//     AtomType::a2HBR = *repository.insert (new A2HBR ((str = "2HBR"))).first;
//     AtomType::a2HBS = *repository.insert (new A2HBS ((str = "2HBS"))).first;
//     AtomType::a2HBT = *repository.insert (new A2HBT ((str = "2HBT"))).first;
//     AtomType::a2HBU = *repository.insert (new A2HBU ((str = "2HBU"))).first;
//     AtomType::a2HBV = *repository.insert (new A2HBV ((str = "2HBV"))).first;
//     AtomType::a2HBW = *repository.insert (new A2HBW ((str = "2HBW"))).first;
//     AtomType::a2HBX = *repository.insert (new A2HBX ((str = "2HBX"))).first;
//     AtomType::a2HBY = *repository.insert (new A2HBY ((str = "2HBY"))).first;
//     AtomType::a2HBZ = *repository.insert (new A2HBZ ((str = "2HBZ"))).first;
//     AtomType::a2HC = *repository.insert (new A2HC ((str = "2HC"))).first;
//     AtomType::a2HC" = *repository.insert (new A2HC" ((str = "2HC""))).first;
//     AtomType::a2HC* = *repository.insert (new A2HC* ((str = "2HC*"))).first;
//     AtomType::a2HC0 = *repository.insert (new A2HC0 ((str = "2HC0"))).first;
//     AtomType::a2HC1 = *repository.insert (new A2HC1 ((str = "2HC1"))).first;
//     AtomType::a2HC2 = *repository.insert (new A2HC2 ((str = "2HC2"))).first;
//     AtomType::a2HC3 = *repository.insert (new A2HC3 ((str = "2HC3"))).first;
//     AtomType::a2HC4 = *repository.insert (new A2HC4 ((str = "2HC4"))).first;
//     AtomType::a2HC5 = *repository.insert (new A2HC5 ((str = "2HC5"))).first;
//     AtomType::a2HC6 = *repository.insert (new A2HC6 ((str = "2HC6"))).first;
//     AtomType::a2HC7 = *repository.insert (new A2HC7 ((str = "2HC7"))).first;
//     AtomType::a2HC8 = *repository.insert (new A2HC8 ((str = "2HC8"))).first;
//     AtomType::a2HC9 = *repository.insert (new A2HC9 ((str = "2HC9"))).first;
//     AtomType::a2HCA = *repository.insert (new A2HCA ((str = "2HCA"))).first;
//     AtomType::a2HCB = *repository.insert (new A2HCB ((str = "2HCB"))).first;
//     AtomType::a2HCC = *repository.insert (new A2HCC ((str = "2HCC"))).first;
//     AtomType::a2HCD = *repository.insert (new A2HCD ((str = "2HCD"))).first;
//     AtomType::a2HCE = *repository.insert (new A2HCE ((str = "2HCE"))).first;
//     AtomType::a2HCF = *repository.insert (new A2HCF ((str = "2HCF"))).first;
//     AtomType::a2HCG = *repository.insert (new A2HCG ((str = "2HCG"))).first;
//     AtomType::a2HCH = *repository.insert (new A2HCH ((str = "2HCH"))).first;
//     AtomType::a2HCI = *repository.insert (new A2HCI ((str = "2HCI"))).first;
//     AtomType::a2HCJ = *repository.insert (new A2HCJ ((str = "2HCJ"))).first;
//     AtomType::a2HCK = *repository.insert (new A2HCK ((str = "2HCK"))).first;
//     AtomType::a2HCL = *repository.insert (new A2HCL ((str = "2HCL"))).first;
//     AtomType::a2HCM = *repository.insert (new A2HCM ((str = "2HCM"))).first;
//     AtomType::a2HCN = *repository.insert (new A2HCN ((str = "2HCN"))).first;
//     AtomType::a2HCO = *repository.insert (new A2HCO ((str = "2HCO"))).first;
//     AtomType::a2HCP = *repository.insert (new A2HCP ((str = "2HCP"))).first;
//     AtomType::a2HCQ = *repository.insert (new A2HCQ ((str = "2HCQ"))).first;
//     AtomType::a2HCR = *repository.insert (new A2HCR ((str = "2HCR"))).first;
//     AtomType::a2HCS = *repository.insert (new A2HCS ((str = "2HCS"))).first;
//     AtomType::a2HCT = *repository.insert (new A2HCT ((str = "2HCT"))).first;
//     AtomType::a2HCU = *repository.insert (new A2HCU ((str = "2HCU"))).first;
//     AtomType::a2HCV = *repository.insert (new A2HCV ((str = "2HCV"))).first;
//     AtomType::a2HCW = *repository.insert (new A2HCW ((str = "2HCW"))).first;
//     AtomType::a2HCX = *repository.insert (new A2HCX ((str = "2HCX"))).first;
//     AtomType::a2HCZ = *repository.insert (new A2HCZ ((str = "2HCZ"))).first;
//     AtomType::a2HD" = *repository.insert (new A2HD" ((str = "2HD""))).first;
//     AtomType::a2HD* = *repository.insert (new A2HD* ((str = "2HD*"))).first;
//     AtomType::a2HD0 = *repository.insert (new A2HD0 ((str = "2HD0"))).first;
//     AtomType::a2HD1 = *repository.insert (new A2HD1 ((str = "2HD1"))).first;
//     AtomType::a2HD2 = *repository.insert (new A2HD2 ((str = "2HD2"))).first;
//     AtomType::a2HD3 = *repository.insert (new A2HD3 ((str = "2HD3"))).first;
//     AtomType::a2HD4 = *repository.insert (new A2HD4 ((str = "2HD4"))).first;
//     AtomType::a2HD5 = *repository.insert (new A2HD5 ((str = "2HD5"))).first;
//     AtomType::a2HD6 = *repository.insert (new A2HD6 ((str = "2HD6"))).first;
//     AtomType::a2HD7 = *repository.insert (new A2HD7 ((str = "2HD7"))).first;
//     AtomType::a2HD8 = *repository.insert (new A2HD8 ((str = "2HD8"))).first;
//     AtomType::a2HD9 = *repository.insert (new A2HD9 ((str = "2HD9"))).first;
//     AtomType::a2HDA = *repository.insert (new A2HDA ((str = "2HDA"))).first;
//     AtomType::a2HDB = *repository.insert (new A2HDB ((str = "2HDB"))).first;
//     AtomType::a2HDC = *repository.insert (new A2HDC ((str = "2HDC"))).first;
//     AtomType::a2HDD = *repository.insert (new A2HDD ((str = "2HDD"))).first;
//     AtomType::a2HDI = *repository.insert (new A2HDI ((str = "2HDI"))).first;
//     AtomType::a2HDK = *repository.insert (new A2HDK ((str = "2HDK"))).first;
//     AtomType::a2HDL = *repository.insert (new A2HDL ((str = "2HDL"))).first;
//     AtomType::a2HDM = *repository.insert (new A2HDM ((str = "2HDM"))).first;
//     AtomType::a2HDN = *repository.insert (new A2HDN ((str = "2HDN"))).first;
//     AtomType::a2HDO = *repository.insert (new A2HDO ((str = "2HDO"))).first;
//     AtomType::a2HDP = *repository.insert (new A2HDP ((str = "2HDP"))).first;
//     AtomType::a2HDY = *repository.insert (new A2HDY ((str = "2HDY"))).first;
//     AtomType::a2HE" = *repository.insert (new A2HE" ((str = "2HE""))).first;
//     AtomType::a2HE* = *repository.insert (new A2HE* ((str = "2HE*"))).first;
//     AtomType::a2HE0 = *repository.insert (new A2HE0 ((str = "2HE0"))).first;
//     AtomType::a2HE1 = *repository.insert (new A2HE1 ((str = "2HE1"))).first;
//     AtomType::a2HE2 = *repository.insert (new A2HE2 ((str = "2HE2"))).first;
//     AtomType::a2HE3 = *repository.insert (new A2HE3 ((str = "2HE3"))).first;
//     AtomType::a2HE4 = *repository.insert (new A2HE4 ((str = "2HE4"))).first;
//     AtomType::a2HE6 = *repository.insert (new A2HE6 ((str = "2HE6"))).first;
//     AtomType::a2HE7 = *repository.insert (new A2HE7 ((str = "2HE7"))).first;
//     AtomType::a2HEA = *repository.insert (new A2HEA ((str = "2HEA"))).first;
//     AtomType::a2HEC = *repository.insert (new A2HEC ((str = "2HEC"))).first;
//     AtomType::a2HED = *repository.insert (new A2HED ((str = "2HED"))).first;
//     AtomType::a2HEI = *repository.insert (new A2HEI ((str = "2HEI"))).first;
//     AtomType::a2HEK = *repository.insert (new A2HEK ((str = "2HEK"))).first;
//     AtomType::a2HEM = *repository.insert (new A2HEM ((str = "2HEM"))).first;
//     AtomType::a2HEO = *repository.insert (new A2HEO ((str = "2HEO"))).first;
//     AtomType::a2HEP = *repository.insert (new A2HEP ((str = "2HEP"))).first;
//     AtomType::a2HEY = *repository.insert (new A2HEY ((str = "2HEY"))).first;
//     AtomType::a2HF = *repository.insert (new A2HF ((str = "2HF"))).first;
//     AtomType::a2HF" = *repository.insert (new A2HF" ((str = "2HF""))).first;
//     AtomType::a2HF* = *repository.insert (new A2HF* ((str = "2HF*"))).first;
//     AtomType::a2HF1 = *repository.insert (new A2HF1 ((str = "2HF1"))).first;
//     AtomType::a2HF2 = *repository.insert (new A2HF2 ((str = "2HF2"))).first;
//     AtomType::a2HFI = *repository.insert (new A2HFI ((str = "2HFI"))).first;
//     AtomType::a2HFM = *repository.insert (new A2HFM ((str = "2HFM"))).first;
//     AtomType::a2HG" = *repository.insert (new A2HG" ((str = "2HG""))).first;
//     AtomType::a2HG* = *repository.insert (new A2HG* ((str = "2HG*"))).first;
//     AtomType::a2HG1 = *repository.insert (new A2HG1 ((str = "2HG1"))).first;
//     AtomType::a2HG2 = *repository.insert (new A2HG2 ((str = "2HG2"))).first;
//     AtomType::a2HG3 = *repository.insert (new A2HG3 ((str = "2HG3"))).first;
//     AtomType::a2HG4 = *repository.insert (new A2HG4 ((str = "2HG4"))).first;
//     AtomType::a2HG5 = *repository.insert (new A2HG5 ((str = "2HG5"))).first;
//     AtomType::a2HG6 = *repository.insert (new A2HG6 ((str = "2HG6"))).first;
//     AtomType::a2HG7 = *repository.insert (new A2HG7 ((str = "2HG7"))).first;
//     AtomType::a2HG8 = *repository.insert (new A2HG8 ((str = "2HG8"))).first;
//     AtomType::a2HGA = *repository.insert (new A2HGA ((str = "2HGA"))).first;
//     AtomType::a2HGB = *repository.insert (new A2HGB ((str = "2HGB"))).first;
//     AtomType::a2HGC = *repository.insert (new A2HGC ((str = "2HGC"))).first;
//     AtomType::a2HGI = *repository.insert (new A2HGI ((str = "2HGI"))).first;
//     AtomType::a2HGK = *repository.insert (new A2HGK ((str = "2HGK"))).first;
//     AtomType::a2HGO = *repository.insert (new A2HGO ((str = "2HGO"))).first;
//     AtomType::a2HGP = *repository.insert (new A2HGP ((str = "2HGP"))).first;
//     AtomType::a2HGS = *repository.insert (new A2HGS ((str = "2HGS"))).first;
//     AtomType::a2HGT = *repository.insert (new A2HGT ((str = "2HGT"))).first;
//     AtomType::a2HH = *repository.insert (new A2HH ((str = "2HH"))).first;
//     AtomType::a2HH" = *repository.insert (new A2HH" ((str = "2HH""))).first;
//     AtomType::a2HH* = *repository.insert (new A2HH* ((str = "2HH*"))).first;
//     AtomType::a2HH1 = *repository.insert (new A2HH1 ((str = "2HH1"))).first;
//     AtomType::a2HH2 = *repository.insert (new A2HH2 ((str = "2HH2"))).first;
//     AtomType::a2HH3 = *repository.insert (new A2HH3 ((str = "2HH3"))).first;
//     AtomType::a2HH4 = *repository.insert (new A2HH4 ((str = "2HH4"))).first;
//     AtomType::a2HH5 = *repository.insert (new A2HH5 ((str = "2HH5"))).first;
//     AtomType::a2HH6 = *repository.insert (new A2HH6 ((str = "2HH6"))).first;
//     AtomType::a2HHA = *repository.insert (new A2HHA ((str = "2HHA"))).first;
//     AtomType::a2HHB = *repository.insert (new A2HHB ((str = "2HHB"))).first;
//     AtomType::a2HHC = *repository.insert (new A2HHC ((str = "2HHC"))).first;
//     AtomType::a2HHD = *repository.insert (new A2HHD ((str = "2HHD"))).first;
//     AtomType::a2HHR = *repository.insert (new A2HHR ((str = "2HHR"))).first;
//     AtomType::a2HHY = *repository.insert (new A2HHY ((str = "2HHY"))).first;
//     AtomType::a2HI = *repository.insert (new A2HI ((str = "2HI"))).first;
//     AtomType::a2HI" = *repository.insert (new A2HI" ((str = "2HI""))).first;
//     AtomType::a2HI* = *repository.insert (new A2HI* ((str = "2HI*"))).first;
//     AtomType::a2HI1 = *repository.insert (new A2HI1 ((str = "2HI1"))).first;
//     AtomType::a2HI2 = *repository.insert (new A2HI2 ((str = "2HI2"))).first;
//     AtomType::a2HI3 = *repository.insert (new A2HI3 ((str = "2HI3"))).first;
//     AtomType::a2HIB = *repository.insert (new A2HIB ((str = "2HIB"))).first;
//     AtomType::a2HIF = *repository.insert (new A2HIF ((str = "2HIF"))).first;
//     AtomType::a2HJ = *repository.insert (new A2HJ ((str = "2HJ"))).first;
//     AtomType::a2HJ" = *repository.insert (new A2HJ" ((str = "2HJ""))).first;
//     AtomType::a2HJ* = *repository.insert (new A2HJ* ((str = "2HJ*"))).first;
//     AtomType::a2HJ1 = *repository.insert (new A2HJ1 ((str = "2HJ1"))).first;
//     AtomType::a2HJ2 = *repository.insert (new A2HJ2 ((str = "2HJ2"))).first;
//     AtomType::a2HJ6 = *repository.insert (new A2HJ6 ((str = "2HJ6"))).first;
//     AtomType::a2HJC = *repository.insert (new A2HJC ((str = "2HJC"))).first;
//     AtomType::a2HK = *repository.insert (new A2HK ((str = "2HK"))).first;
//     AtomType::a2HK* = *repository.insert (new A2HK* ((str = "2HK*"))).first;
//     AtomType::a2HK1 = *repository.insert (new A2HK1 ((str = "2HK1"))).first;
//     AtomType::a2HK2 = *repository.insert (new A2HK2 ((str = "2HK2"))).first;
//     AtomType::a2HK3 = *repository.insert (new A2HK3 ((str = "2HK3"))).first;
//     AtomType::a2HK4 = *repository.insert (new A2HK4 ((str = "2HK4"))).first;
//     AtomType::a2HK5 = *repository.insert (new A2HK5 ((str = "2HK5"))).first;
//     AtomType::a2HK6 = *repository.insert (new A2HK6 ((str = "2HK6"))).first;
//     AtomType::a2HKC = *repository.insert (new A2HKC ((str = "2HKC"))).first;
//     AtomType::a2HKY = *repository.insert (new A2HKY ((str = "2HKY"))).first;
//     AtomType::a2HL = *repository.insert (new A2HL ((str = "2HL"))).first;
//     AtomType::a2HL* = *repository.insert (new A2HL* ((str = "2HL*"))).first;
//     AtomType::a2HL1 = *repository.insert (new A2HL1 ((str = "2HL1"))).first;
//     AtomType::a2HL2 = *repository.insert (new A2HL2 ((str = "2HL2"))).first;
//     AtomType::a2HL3 = *repository.insert (new A2HL3 ((str = "2HL3"))).first;
//     AtomType::a2HL4 = *repository.insert (new A2HL4 ((str = "2HL4"))).first;
//     AtomType::a2HL5 = *repository.insert (new A2HL5 ((str = "2HL5"))).first;
//     AtomType::a2HL6 = *repository.insert (new A2HL6 ((str = "2HL6"))).first;
//     AtomType::a2HL7 = *repository.insert (new A2HL7 ((str = "2HL7"))).first;
//     AtomType::a2HL8 = *repository.insert (new A2HL8 ((str = "2HL8"))).first;
//     AtomType::a2HL9 = *repository.insert (new A2HL9 ((str = "2HL9"))).first;
//     AtomType::a2HLB = *repository.insert (new A2HLB ((str = "2HLB"))).first;
//     AtomType::a2HM = *repository.insert (new A2HM ((str = "2HM"))).first;
//     AtomType::a2HM" = *repository.insert (new A2HM" ((str = "2HM""))).first;
//     AtomType::a2HM* = *repository.insert (new A2HM* ((str = "2HM*"))).first;
//     AtomType::a2HM0 = *repository.insert (new A2HM0 ((str = "2HM0"))).first;
    AtomType::a2HM1 = *repository.insert (new A2HM1 ((str = "2HM1"))).first;
//     AtomType::a2HM2 = *repository.insert (new A2HM2 ((str = "2HM2"))).first;
//     AtomType::a2HM3 = *repository.insert (new A2HM3 ((str = "2HM3"))).first;
//     AtomType::a2HM4 = *repository.insert (new A2HM4 ((str = "2HM4"))).first;
//     AtomType::a2HM5 = *repository.insert (new A2HM5 ((str = "2HM5"))).first;
//     AtomType::a2HM6 = *repository.insert (new A2HM6 ((str = "2HM6"))).first;
//     AtomType::a2HM7 = *repository.insert (new A2HM7 ((str = "2HM7"))).first;
//     AtomType::a2HM8 = *repository.insert (new A2HM8 ((str = "2HM8"))).first;
//     AtomType::a2HM9 = *repository.insert (new A2HM9 ((str = "2HM9"))).first;
//     AtomType::a2HMA = *repository.insert (new A2HMA ((str = "2HMA"))).first;
//     AtomType::a2HMB = *repository.insert (new A2HMB ((str = "2HMB"))).first;
//     AtomType::a2HMC = *repository.insert (new A2HMC ((str = "2HMC"))).first;
//     AtomType::a2HMD = *repository.insert (new A2HMD ((str = "2HMD"))).first;
//     AtomType::a2HME = *repository.insert (new A2HME ((str = "2HME"))).first;
//     AtomType::a2HMF = *repository.insert (new A2HMF ((str = "2HMF"))).first;
//     AtomType::a2HMK = *repository.insert (new A2HMK ((str = "2HMK"))).first;
//     AtomType::a2HMP = *repository.insert (new A2HMP ((str = "2HMP"))).first;
//     AtomType::a2HMZ = *repository.insert (new A2HMZ ((str = "2HMZ"))).first;
//     AtomType::a2HN = *repository.insert (new A2HN ((str = "2HN"))).first;
//     AtomType::a2HN* = *repository.insert (new A2HN* ((str = "2HN*"))).first;
//     AtomType::a2HN0 = *repository.insert (new A2HN0 ((str = "2HN0"))).first;
//     AtomType::a2HN1 = *repository.insert (new A2HN1 ((str = "2HN1"))).first;
//     AtomType::a2HN2 = *repository.insert (new A2HN2 ((str = "2HN2"))).first;
//     AtomType::a2HN3 = *repository.insert (new A2HN3 ((str = "2HN3"))).first;
//     AtomType::a2HN4 = *repository.insert (new A2HN4 ((str = "2HN4"))).first;
//     AtomType::a2HN5 = *repository.insert (new A2HN5 ((str = "2HN5"))).first;
    AtomType::a2HN6 = *repository.insert (new A2HN6 ((str = "2HN6"))).first;
//     AtomType::a2HN7 = *repository.insert (new A2HN7 ((str = "2HN7"))).first;
//     AtomType::a2HN8 = *repository.insert (new A2HN8 ((str = "2HN8"))).first;
//     AtomType::a2HN9 = *repository.insert (new A2HN9 ((str = "2HN9"))).first;
//     AtomType::a2HNA = *repository.insert (new A2HNA ((str = "2HNA"))).first;
//     AtomType::a2HNB = *repository.insert (new A2HNB ((str = "2HNB"))).first;
//     AtomType::a2HNC = *repository.insert (new A2HNC ((str = "2HNC"))).first;
//     AtomType::a2HND = *repository.insert (new A2HND ((str = "2HND"))).first;
//     AtomType::a2HNE = *repository.insert (new A2HNE ((str = "2HNE"))).first;
//     AtomType::a2HNF = *repository.insert (new A2HNF ((str = "2HNF"))).first;
//     AtomType::a2HNG = *repository.insert (new A2HNG ((str = "2HNG"))).first;
//     AtomType::a2HNH = *repository.insert (new A2HNH ((str = "2HNH"))).first;
//     AtomType::a2HNI = *repository.insert (new A2HNI ((str = "2HNI"))).first;
//     AtomType::a2HNK = *repository.insert (new A2HNK ((str = "2HNK"))).first;
//     AtomType::a2HNL = *repository.insert (new A2HNL ((str = "2HNL"))).first;
//     AtomType::a2HNM = *repository.insert (new A2HNM ((str = "2HNM"))).first;
//     AtomType::a2HNO = *repository.insert (new A2HNO ((str = "2HNO"))).first;
//     AtomType::a2HNP = *repository.insert (new A2HNP ((str = "2HNP"))).first;
//     AtomType::a2HNQ = *repository.insert (new A2HNQ ((str = "2HNQ"))).first;
//     AtomType::a2HNS = *repository.insert (new A2HNS ((str = "2HNS"))).first;
//     AtomType::a2HNT = *repository.insert (new A2HNT ((str = "2HNT"))).first;
//     AtomType::a2HNV = *repository.insert (new A2HNV ((str = "2HNV"))).first;
//     AtomType::a2HNX = *repository.insert (new A2HNX ((str = "2HNX"))).first;
//     AtomType::a2HNZ = *repository.insert (new A2HNZ ((str = "2HNZ"))).first;
//     AtomType::a2HO = *repository.insert (new A2HO ((str = "2HO"))).first;
//     AtomType::a2HO* = *repository.insert (new A2HO* ((str = "2HO*"))).first;
//     AtomType::a2HO0 = *repository.insert (new A2HO0 ((str = "2HO0"))).first;
//     AtomType::a2HO1 = *repository.insert (new A2HO1 ((str = "2HO1"))).first;
//     AtomType::a2HO2 = *repository.insert (new A2HO2 ((str = "2HO2"))).first;
//     AtomType::a2HO3 = *repository.insert (new A2HO3 ((str = "2HO3"))).first;
//     AtomType::a2HO4 = *repository.insert (new A2HO4 ((str = "2HO4"))).first;
//     AtomType::a2HO5 = *repository.insert (new A2HO5 ((str = "2HO5"))).first;
//     AtomType::a2HO6 = *repository.insert (new A2HO6 ((str = "2HO6"))).first;
//     AtomType::a2HO7 = *repository.insert (new A2HO7 ((str = "2HO7"))).first;
//     AtomType::a2HO8 = *repository.insert (new A2HO8 ((str = "2HO8"))).first;
//     AtomType::a2HO9 = *repository.insert (new A2HO9 ((str = "2HO9"))).first;
//     AtomType::a2HOA = *repository.insert (new A2HOA ((str = "2HOA"))).first;
//     AtomType::a2HOB = *repository.insert (new A2HOB ((str = "2HOB"))).first;
//     AtomType::a2HOC = *repository.insert (new A2HOC ((str = "2HOC"))).first;
//     AtomType::a2HOD = *repository.insert (new A2HOD ((str = "2HOD"))).first;
//     AtomType::a2HOE = *repository.insert (new A2HOE ((str = "2HOE"))).first;
//     AtomType::a2HOG = *repository.insert (new A2HOG ((str = "2HOG"))).first;
//     AtomType::a2HOJ = *repository.insert (new A2HOJ ((str = "2HOJ"))).first;
//     AtomType::a2HON = *repository.insert (new A2HON ((str = "2HON"))).first;
//     AtomType::a2HOR = *repository.insert (new A2HOR ((str = "2HOR"))).first;
//     AtomType::a2HOS = *repository.insert (new A2HOS ((str = "2HOS"))).first;
//     AtomType::a2HOW = *repository.insert (new A2HOW ((str = "2HOW"))).first;
//     AtomType::a2HOX = *repository.insert (new A2HOX ((str = "2HOX"))).first;
//     AtomType::a2HP = *repository.insert (new A2HP ((str = "2HP"))).first;
//     AtomType::a2HP1 = *repository.insert (new A2HP1 ((str = "2HP1"))).first;
//     AtomType::a2HP2 = *repository.insert (new A2HP2 ((str = "2HP2"))).first;
//     AtomType::a2HP3 = *repository.insert (new A2HP3 ((str = "2HP3"))).first;
//     AtomType::a2HP4 = *repository.insert (new A2HP4 ((str = "2HP4"))).first;
//     AtomType::a2HP5 = *repository.insert (new A2HP5 ((str = "2HP5"))).first;
//     AtomType::a2HP6 = *repository.insert (new A2HP6 ((str = "2HP6"))).first;
//     AtomType::a2HP7 = *repository.insert (new A2HP7 ((str = "2HP7"))).first;
//     AtomType::a2HP8 = *repository.insert (new A2HP8 ((str = "2HP8"))).first;
//     AtomType::a2HP9 = *repository.insert (new A2HP9 ((str = "2HP9"))).first;
//     AtomType::a2HPA = *repository.insert (new A2HPA ((str = "2HPA"))).first;
//     AtomType::a2HPB = *repository.insert (new A2HPB ((str = "2HPB"))).first;
//     AtomType::a2HPC = *repository.insert (new A2HPC ((str = "2HPC"))).first;
//     AtomType::a2HPD = *repository.insert (new A2HPD ((str = "2HPD"))).first;
//     AtomType::a2HPE = *repository.insert (new A2HPE ((str = "2HPE"))).first;
//     AtomType::a2HPS = *repository.insert (new A2HPS ((str = "2HPS"))).first;
//     AtomType::a2HQ = *repository.insert (new A2HQ ((str = "2HQ"))).first;
//     AtomType::a2HQ1 = *repository.insert (new A2HQ1 ((str = "2HQ1"))).first;
//     AtomType::a2HQ2 = *repository.insert (new A2HQ2 ((str = "2HQ2"))).first;
//     AtomType::a2HQ6 = *repository.insert (new A2HQ6 ((str = "2HQ6"))).first;
//     AtomType::a2HQ7 = *repository.insert (new A2HQ7 ((str = "2HQ7"))).first;
//     AtomType::a2HQB = *repository.insert (new A2HQB ((str = "2HQB"))).first;
//     AtomType::a2HR = *repository.insert (new A2HR ((str = "2HR"))).first;
//     AtomType::a2HR* = *repository.insert (new A2HR* ((str = "2HR*"))).first;
//     AtomType::a2HR1 = *repository.insert (new A2HR1 ((str = "2HR1"))).first;
//     AtomType::a2HR2 = *repository.insert (new A2HR2 ((str = "2HR2"))).first;
//     AtomType::a2HR3 = *repository.insert (new A2HR3 ((str = "2HR3"))).first;
//     AtomType::a2HR4 = *repository.insert (new A2HR4 ((str = "2HR4"))).first;
//     AtomType::a2HR5 = *repository.insert (new A2HR5 ((str = "2HR5"))).first;
//     AtomType::a2HR6 = *repository.insert (new A2HR6 ((str = "2HR6"))).first;
//     AtomType::a2HR7 = *repository.insert (new A2HR7 ((str = "2HR7"))).first;
//     AtomType::a2HR8 = *repository.insert (new A2HR8 ((str = "2HR8"))).first;
//     AtomType::a2HR9 = *repository.insert (new A2HR9 ((str = "2HR9"))).first;
//     AtomType::a2HS = *repository.insert (new A2HS ((str = "2HS"))).first;
//     AtomType::a2HS1 = *repository.insert (new A2HS1 ((str = "2HS1"))).first;
//     AtomType::a2HS2 = *repository.insert (new A2HS2 ((str = "2HS2"))).first;
//     AtomType::a2HS3 = *repository.insert (new A2HS3 ((str = "2HS3"))).first;
//     AtomType::a2HS4 = *repository.insert (new A2HS4 ((str = "2HS4"))).first;
//     AtomType::a2HS5 = *repository.insert (new A2HS5 ((str = "2HS5"))).first;
//     AtomType::a2HS6 = *repository.insert (new A2HS6 ((str = "2HS6"))).first;
//     AtomType::a2HSG = *repository.insert (new A2HSG ((str = "2HSG"))).first;
//     AtomType::a2HSP = *repository.insert (new A2HSP ((str = "2HSP"))).first;
//     AtomType::a2HSS = *repository.insert (new A2HSS ((str = "2HSS"))).first;
//     AtomType::a2HT = *repository.insert (new A2HT ((str = "2HT"))).first;
//     AtomType::a2HT" = *repository.insert (new A2HT" ((str = "2HT""))).first;
//     AtomType::a2HT* = *repository.insert (new A2HT* ((str = "2HT*"))).first;
//     AtomType::a2HT0 = *repository.insert (new A2HT0 ((str = "2HT0"))).first;
//     AtomType::a2HT1 = *repository.insert (new A2HT1 ((str = "2HT1"))).first;
//     AtomType::a2HT2 = *repository.insert (new A2HT2 ((str = "2HT2"))).first;
//     AtomType::a2HT3 = *repository.insert (new A2HT3 ((str = "2HT3"))).first;
//     AtomType::a2HT4 = *repository.insert (new A2HT4 ((str = "2HT4"))).first;
//     AtomType::a2HT5 = *repository.insert (new A2HT5 ((str = "2HT5"))).first;
//     AtomType::a2HT6 = *repository.insert (new A2HT6 ((str = "2HT6"))).first;
//     AtomType::a2HTC = *repository.insert (new A2HTC ((str = "2HTC"))).first;
//     AtomType::a2HU = *repository.insert (new A2HU ((str = "2HU"))).first;
//     AtomType::a2HU2 = *repository.insert (new A2HU2 ((str = "2HU2"))).first;
//     AtomType::a2HU5 = *repository.insert (new A2HU5 ((str = "2HU5"))).first;
//     AtomType::a2HV = *repository.insert (new A2HV ((str = "2HV"))).first;
//     AtomType::a2HV1 = *repository.insert (new A2HV1 ((str = "2HV1"))).first;
//     AtomType::a2HV2 = *repository.insert (new A2HV2 ((str = "2HV2"))).first;
//     AtomType::a2HV3 = *repository.insert (new A2HV3 ((str = "2HV3"))).first;
//     AtomType::a2HV4 = *repository.insert (new A2HV4 ((str = "2HV4"))).first;
//     AtomType::a2HV6 = *repository.insert (new A2HV6 ((str = "2HV6"))).first;
//     AtomType::a2HV8 = *repository.insert (new A2HV8 ((str = "2HV8"))).first;
//     AtomType::a2HV9 = *repository.insert (new A2HV9 ((str = "2HV9"))).first;
//     AtomType::a2HW = *repository.insert (new A2HW ((str = "2HW"))).first;
//     AtomType::a2HW6 = *repository.insert (new A2HW6 ((str = "2HW6"))).first;
//     AtomType::a2HX = *repository.insert (new A2HX ((str = "2HX"))).first;
//     AtomType::a2HX* = *repository.insert (new A2HX* ((str = "2HX*"))).first;
//     AtomType::a2HX0 = *repository.insert (new A2HX0 ((str = "2HX0"))).first;
//     AtomType::a2HX1 = *repository.insert (new A2HX1 ((str = "2HX1"))).first;
//     AtomType::a2HX2 = *repository.insert (new A2HX2 ((str = "2HX2"))).first;
//     AtomType::a2HX3 = *repository.insert (new A2HX3 ((str = "2HX3"))).first;
//     AtomType::a2HX4 = *repository.insert (new A2HX4 ((str = "2HX4"))).first;
//     AtomType::a2HX5 = *repository.insert (new A2HX5 ((str = "2HX5"))).first;
//     AtomType::a2HX6 = *repository.insert (new A2HX6 ((str = "2HX6"))).first;
//     AtomType::a2HX7 = *repository.insert (new A2HX7 ((str = "2HX7"))).first;
//     AtomType::a2HX8 = *repository.insert (new A2HX8 ((str = "2HX8"))).first;
//     AtomType::a2HX9 = *repository.insert (new A2HX9 ((str = "2HX9"))).first;
//     AtomType::a2HXA = *repository.insert (new A2HXA ((str = "2HXA"))).first;
//     AtomType::a2HXB = *repository.insert (new A2HXB ((str = "2HXB"))).first;
//     AtomType::a2HXD = *repository.insert (new A2HXD ((str = "2HXD"))).first;
//     AtomType::a2HXE = *repository.insert (new A2HXE ((str = "2HXE"))).first;
//     AtomType::a2HXG = *repository.insert (new A2HXG ((str = "2HXG"))).first;
//     AtomType::a2HXT = *repository.insert (new A2HXT ((str = "2HXT"))).first;
//     AtomType::a2HY1 = *repository.insert (new A2HY1 ((str = "2HY1"))).first;
//     AtomType::a2HY2 = *repository.insert (new A2HY2 ((str = "2HY2"))).first;
//     AtomType::a2HY3 = *repository.insert (new A2HY3 ((str = "2HY3"))).first;
//     AtomType::a2HY4 = *repository.insert (new A2HY4 ((str = "2HY4"))).first;
//     AtomType::a2HY6 = *repository.insert (new A2HY6 ((str = "2HY6"))).first;
//     AtomType::a2HY7 = *repository.insert (new A2HY7 ((str = "2HY7"))).first;
//     AtomType::a2HZ* = *repository.insert (new A2HZ* ((str = "2HZ*"))).first;
//     AtomType::a2HZ1 = *repository.insert (new A2HZ1 ((str = "2HZ1"))).first;
//     AtomType::a2HZ2 = *repository.insert (new A2HZ2 ((str = "2HZ2"))).first;
//     AtomType::a2HZ3 = *repository.insert (new A2HZ3 ((str = "2HZ3"))).first;
//     AtomType::a2HZ4 = *repository.insert (new A2HZ4 ((str = "2HZ4"))).first;
//     AtomType::a2HZ5 = *repository.insert (new A2HZ5 ((str = "2HZ5"))).first;
//     AtomType::a2HZ6 = *repository.insert (new A2HZ6 ((str = "2HZ6"))).first;
//     AtomType::a2HZ7 = *repository.insert (new A2HZ7 ((str = "2HZ7"))).first;
//     AtomType::a2HZ8 = *repository.insert (new A2HZ8 ((str = "2HZ8"))).first;
//     AtomType::a2HZ9 = *repository.insert (new A2HZ9 ((str = "2HZ9"))).first;
//     AtomType::a2HZA = *repository.insert (new A2HZA ((str = "2HZA"))).first;
//     AtomType::a2HZH = *repository.insert (new A2HZH ((str = "2HZH"))).first;
//     AtomType::a2HZN = *repository.insert (new A2HZN ((str = "2HZN"))).first;
//     AtomType::a2HZY = *repository.insert (new A2HZY ((str = "2HZY"))).first;
//     AtomType::a2H_2 = *repository.insert (new A2H_2 ((str = "2H_2"))).first;
//     AtomType::a2N = *repository.insert (new A2N ((str = "2N"))).first;
//     AtomType::a2N10 = *repository.insert (new A2N10 ((str = "2N10"))).first;
//     AtomType::a2N3 = *repository.insert (new A2N3 ((str = "2N3"))).first;
//     AtomType::a2N7 = *repository.insert (new A2N7 ((str = "2N7"))).first;
//     AtomType::a2ND1 = *repository.insert (new A2ND1 ((str = "2ND1"))).first;
//     AtomType::a2NE2 = *repository.insert (new A2NE2 ((str = "2NE2"))).first;
//     AtomType::a2NH = *repository.insert (new A2NH ((str = "2NH"))).first;
//     AtomType::a2NH* = *repository.insert (new A2NH* ((str = "2NH*"))).first;
//     AtomType::a2NH1 = *repository.insert (new A2NH1 ((str = "2NH1"))).first;
//     AtomType::a2NH4 = *repository.insert (new A2NH4 ((str = "2NH4"))).first;
//     AtomType::a2O = *repository.insert (new A2O ((str = "2O"))).first;
//     AtomType::a2O1 = *repository.insert (new A2O1 ((str = "2O1"))).first;
//     AtomType::a2O2 = *repository.insert (new A2O2 ((str = "2O2"))).first;
//     AtomType::a2O2* = *repository.insert (new A2O2* ((str = "2O2*"))).first;
//     AtomType::a2O21 = *repository.insert (new A2O21 ((str = "2O21"))).first;
//     AtomType::a2O22 = *repository.insert (new A2O22 ((str = "2O22"))).first;
//     AtomType::a2O3 = *repository.insert (new A2O3 ((str = "2O3"))).first;
//     AtomType::a2O4 = *repository.insert (new A2O4 ((str = "2O4"))).first;
//     AtomType::a2O4* = *repository.insert (new A2O4* ((str = "2O4*"))).first;
//     AtomType::a2O7 = *repository.insert (new A2O7 ((str = "2O7"))).first;
//     AtomType::a2OE1 = *repository.insert (new A2OE1 ((str = "2OE1"))).first;
//     AtomType::a2OH = *repository.insert (new A2OH ((str = "2OH"))).first;
//     AtomType::a2OP = *repository.insert (new A2OP ((str = "2OP"))).first;
//     AtomType::a2OP* = *repository.insert (new A2OP* ((str = "2OP*"))).first;
//     AtomType::a2OP3 = *repository.insert (new A2OP3 ((str = "2OP3"))).first;
//     AtomType::a2OP5 = *repository.insert (new A2OP5 ((str = "2OP5"))).first;
//     AtomType::a2OXT = *repository.insert (new A2OXT ((str = "2OXT"))).first;
//     AtomType::a31HO = *repository.insert (new A31HO ((str = "31HO"))).first;
//     AtomType::a33HO = *repository.insert (new A33HO ((str = "33HO"))).first;
//     AtomType::a3C = *repository.insert (new A3C ((str = "3C"))).first;
//     AtomType::a3C1 = *repository.insert (new A3C1 ((str = "3C1"))).first;
//     AtomType::a3C10 = *repository.insert (new A3C10 ((str = "3C10"))).first;
//     AtomType::a3C11 = *repository.insert (new A3C11 ((str = "3C11"))).first;
//     AtomType::a3C12 = *repository.insert (new A3C12 ((str = "3C12"))).first;
//     AtomType::a3C13 = *repository.insert (new A3C13 ((str = "3C13"))).first;
//     AtomType::a3C3 = *repository.insert (new A3C3 ((str = "3C3"))).first;
//     AtomType::a3C4 = *repository.insert (new A3C4 ((str = "3C4"))).first;
//     AtomType::a3C5 = *repository.insert (new A3C5 ((str = "3C5"))).first;
//     AtomType::a3C6 = *repository.insert (new A3C6 ((str = "3C6"))).first;
//     AtomType::a3C6A = *repository.insert (new A3C6A ((str = "3C6A"))).first;
//     AtomType::a3C6B = *repository.insert (new A3C6B ((str = "3C6B"))).first;
//     AtomType::a3C7 = *repository.insert (new A3C7 ((str = "3C7"))).first;
//     AtomType::a3C8 = *repository.insert (new A3C8 ((str = "3C8"))).first;
//     AtomType::a3C9 = *repository.insert (new A3C9 ((str = "3C9"))).first;
//     AtomType::a3CA = *repository.insert (new A3CA ((str = "3CA"))).first;
//     AtomType::a3CB = *repository.insert (new A3CB ((str = "3CB"))).first;
//     AtomType::a3CD = *repository.insert (new A3CD ((str = "3CD"))).first;
//     AtomType::a3CD2 = *repository.insert (new A3CD2 ((str = "3CD2"))).first;
//     AtomType::a3CE1 = *repository.insert (new A3CE1 ((str = "3CE1"))).first;
//     AtomType::a3CEG = *repository.insert (new A3CEG ((str = "3CEG"))).first;
//     AtomType::a3CG = *repository.insert (new A3CG ((str = "3CG"))).first;
//     AtomType::a3CG1 = *repository.insert (new A3CG1 ((str = "3CG1"))).first;
//     AtomType::a3CG2 = *repository.insert (new A3CG2 ((str = "3CG2"))).first;
//     AtomType::a3CH3 = *repository.insert (new A3CH3 ((str = "3CH3"))).first;
//     AtomType::a3CH5 = *repository.insert (new A3CH5 ((str = "3CH5"))).first;
//     AtomType::a3CL3 = *repository.insert (new A3CL3 ((str = "3CL3"))).first;
//     AtomType::a3D = *repository.insert (new A3D ((str = "3D"))).first;
//     AtomType::a3D14 = *repository.insert (new A3D14 ((str = "3D14"))).first;
//     AtomType::a3H = *repository.insert (new A3H ((str = "3H"))).first;
//     AtomType::a3H* = *repository.insert (new A3H* ((str = "3H*"))).first;
//     AtomType::a3H** = *repository.insert (new A3H** ((str = "3H**"))).first;
//     AtomType::a3H*7 = *repository.insert (new A3H*7 ((str = "3H*7"))).first;
//     AtomType::a3H*8 = *repository.insert (new A3H*8 ((str = "3H*8"))).first;
//     AtomType::a3H*A = *repository.insert (new A3H*A ((str = "3H*A"))).first;
//     AtomType::a3H0 = *repository.insert (new A3H0 ((str = "3H0"))).first;
//     AtomType::a3H01 = *repository.insert (new A3H01 ((str = "3H01"))).first;
//     AtomType::a3H02 = *repository.insert (new A3H02 ((str = "3H02"))).first;
//     AtomType::a3H03 = *repository.insert (new A3H03 ((str = "3H03"))).first;
//     AtomType::a3H04 = *repository.insert (new A3H04 ((str = "3H04"))).first;
//     AtomType::a3H05 = *repository.insert (new A3H05 ((str = "3H05"))).first;
//     AtomType::a3H06 = *repository.insert (new A3H06 ((str = "3H06"))).first;
//     AtomType::a3H07 = *repository.insert (new A3H07 ((str = "3H07"))).first;
//     AtomType::a3H08 = *repository.insert (new A3H08 ((str = "3H08"))).first;
//     AtomType::a3H09 = *repository.insert (new A3H09 ((str = "3H09"))).first;
//     AtomType::a3H0A = *repository.insert (new A3H0A ((str = "3H0A"))).first;
//     AtomType::a3H0B = *repository.insert (new A3H0B ((str = "3H0B"))).first;
//     AtomType::a3H0C = *repository.insert (new A3H0C ((str = "3H0C"))).first;
//     AtomType::a3H0K = *repository.insert (new A3H0K ((str = "3H0K"))).first;
//     AtomType::a3H0Q = *repository.insert (new A3H0Q ((str = "3H0Q"))).first;
//     AtomType::a3H1 = *repository.insert (new A3H1 ((str = "3H1"))).first;
//     AtomType::a3H1" = *repository.insert (new A3H1" ((str = "3H1""))).first;
//     AtomType::a3H1* = *repository.insert (new A3H1* ((str = "3H1*"))).first;
//     AtomType::a3H10 = *repository.insert (new A3H10 ((str = "3H10"))).first;
//     AtomType::a3H11 = *repository.insert (new A3H11 ((str = "3H11"))).first;
//     AtomType::a3H12 = *repository.insert (new A3H12 ((str = "3H12"))).first;
//     AtomType::a3H13 = *repository.insert (new A3H13 ((str = "3H13"))).first;
//     AtomType::a3H13A = *repository.insert (new A3H13A ((str = "3H13A"))).first;
//     AtomType::a3H14 = *repository.insert (new A3H14 ((str = "3H14"))).first;
//     AtomType::a3H15 = *repository.insert (new A3H15 ((str = "3H15"))).first;
//     AtomType::a3H16 = *repository.insert (new A3H16 ((str = "3H16"))).first;
//     AtomType::a3H16B = *repository.insert (new A3H16B ((str = "3H16B"))).first;
//     AtomType::a3H17 = *repository.insert (new A3H17 ((str = "3H17"))).first;
//     AtomType::a3H18 = *repository.insert (new A3H18 ((str = "3H18"))).first;
//     AtomType::a3H19 = *repository.insert (new A3H19 ((str = "3H19"))).first;
//     AtomType::a3H1A = *repository.insert (new A3H1A ((str = "3H1A"))).first;
//     AtomType::a3H1B = *repository.insert (new A3H1B ((str = "3H1B"))).first;
//     AtomType::a3H1C = *repository.insert (new A3H1C ((str = "3H1C"))).first;
//     AtomType::a3H1D = *repository.insert (new A3H1D ((str = "3H1D"))).first;
//     AtomType::a3H1E = *repository.insert (new A3H1E ((str = "3H1E"))).first;
//     AtomType::a3H1F = *repository.insert (new A3H1F ((str = "3H1F"))).first;
//     AtomType::a3H1L = *repository.insert (new A3H1L ((str = "3H1L"))).first;
//     AtomType::a3H1M = *repository.insert (new A3H1M ((str = "3H1M"))).first;
//     AtomType::a3H1N = *repository.insert (new A3H1N ((str = "3H1N"))).first;
//     AtomType::a3H1P = *repository.insert (new A3H1P ((str = "3H1P"))).first;
//     AtomType::a3H1V = *repository.insert (new A3H1V ((str = "3H1V"))).first;
//     AtomType::a3H1X = *repository.insert (new A3H1X ((str = "3H1X"))).first;
//     AtomType::a3H1Y = *repository.insert (new A3H1Y ((str = "3H1Y"))).first;
//     AtomType::a3H2 = *repository.insert (new A3H2 ((str = "3H2"))).first;
//     AtomType::a3H2" = *repository.insert (new A3H2" ((str = "3H2""))).first;
//     AtomType::a3H2* = *repository.insert (new A3H2* ((str = "3H2*"))).first;
//     AtomType::a3H20 = *repository.insert (new A3H20 ((str = "3H20"))).first;
//     AtomType::a3H21 = *repository.insert (new A3H21 ((str = "3H21"))).first;
//     AtomType::a3H22 = *repository.insert (new A3H22 ((str = "3H22"))).first;
//     AtomType::a3H23 = *repository.insert (new A3H23 ((str = "3H23"))).first;
//     AtomType::a3H24 = *repository.insert (new A3H24 ((str = "3H24"))).first;
//     AtomType::a3H25 = *repository.insert (new A3H25 ((str = "3H25"))).first;
//     AtomType::a3H26 = *repository.insert (new A3H26 ((str = "3H26"))).first;
//     AtomType::a3H27 = *repository.insert (new A3H27 ((str = "3H27"))).first;
//     AtomType::a3H28 = *repository.insert (new A3H28 ((str = "3H28"))).first;
//     AtomType::a3H29 = *repository.insert (new A3H29 ((str = "3H29"))).first;
//     AtomType::a3H2A = *repository.insert (new A3H2A ((str = "3H2A"))).first;
//     AtomType::a3H2B = *repository.insert (new A3H2B ((str = "3H2B"))).first;
//     AtomType::a3H2C = *repository.insert (new A3H2C ((str = "3H2C"))).first;
//     AtomType::a3H2G = *repository.insert (new A3H2G ((str = "3H2G"))).first;
//     AtomType::a3H2H = *repository.insert (new A3H2H ((str = "3H2H"))).first;
//     AtomType::a3H2I = *repository.insert (new A3H2I ((str = "3H2I"))).first;
//     AtomType::a3H2M = *repository.insert (new A3H2M ((str = "3H2M"))).first;
//     AtomType::a3H2N = *repository.insert (new A3H2N ((str = "3H2N"))).first;
//     AtomType::a3H2P = *repository.insert (new A3H2P ((str = "3H2P"))).first;
//     AtomType::a3H2V = *repository.insert (new A3H2V ((str = "3H2V"))).first;
//     AtomType::a3H2Y = *repository.insert (new A3H2Y ((str = "3H2Y"))).first;
//     AtomType::a3H2Z = *repository.insert (new A3H2Z ((str = "3H2Z"))).first;
//     AtomType::a3H3 = *repository.insert (new A3H3 ((str = "3H3"))).first;
//     AtomType::a3H3" = *repository.insert (new A3H3" ((str = "3H3""))).first;
//     AtomType::a3H3* = *repository.insert (new A3H3* ((str = "3H3*"))).first;
//     AtomType::a3H30 = *repository.insert (new A3H30 ((str = "3H30"))).first;
//     AtomType::a3H31 = *repository.insert (new A3H31 ((str = "3H31"))).first;
//     AtomType::a3H32 = *repository.insert (new A3H32 ((str = "3H32"))).first;
//     AtomType::a3H33 = *repository.insert (new A3H33 ((str = "3H33"))).first;
//     AtomType::a3H34 = *repository.insert (new A3H34 ((str = "3H34"))).first;
//     AtomType::a3H35 = *repository.insert (new A3H35 ((str = "3H35"))).first;
//     AtomType::a3H36 = *repository.insert (new A3H36 ((str = "3H36"))).first;
//     AtomType::a3H37 = *repository.insert (new A3H37 ((str = "3H37"))).first;
//     AtomType::a3H38 = *repository.insert (new A3H38 ((str = "3H38"))).first;
//     AtomType::a3H39 = *repository.insert (new A3H39 ((str = "3H39"))).first;
//     AtomType::a3H3A = *repository.insert (new A3H3A ((str = "3H3A"))).first;
//     AtomType::a3H3B = *repository.insert (new A3H3B ((str = "3H3B"))).first;
//     AtomType::a3H3C = *repository.insert (new A3H3C ((str = "3H3C"))).first;
//     AtomType::a3H3D = *repository.insert (new A3H3D ((str = "3H3D"))).first;
//     AtomType::a3H3E = *repository.insert (new A3H3E ((str = "3H3E"))).first;
//     AtomType::a3H3F = *repository.insert (new A3H3F ((str = "3H3F"))).first;
//     AtomType::a3H3G = *repository.insert (new A3H3G ((str = "3H3G"))).first;
//     AtomType::a3H3I = *repository.insert (new A3H3I ((str = "3H3I"))).first;
//     AtomType::a3H3M = *repository.insert (new A3H3M ((str = "3H3M"))).first;
//     AtomType::a3H3N = *repository.insert (new A3H3N ((str = "3H3N"))).first;
//     AtomType::a3H3P = *repository.insert (new A3H3P ((str = "3H3P"))).first;
//     AtomType::a3H3T = *repository.insert (new A3H3T ((str = "3H3T"))).first;
//     AtomType::a3H3U = *repository.insert (new A3H3U ((str = "3H3U"))).first;
//     AtomType::a3H4 = *repository.insert (new A3H4 ((str = "3H4"))).first;
//     AtomType::a3H4" = *repository.insert (new A3H4" ((str = "3H4""))).first;
//     AtomType::a3H4* = *repository.insert (new A3H4* ((str = "3H4*"))).first;
//     AtomType::a3H40 = *repository.insert (new A3H40 ((str = "3H40"))).first;
//     AtomType::a3H41 = *repository.insert (new A3H41 ((str = "3H41"))).first;
//     AtomType::a3H42 = *repository.insert (new A3H42 ((str = "3H42"))).first;
//     AtomType::a3H43 = *repository.insert (new A3H43 ((str = "3H43"))).first;
//     AtomType::a3H44 = *repository.insert (new A3H44 ((str = "3H44"))).first;
//     AtomType::a3H45 = *repository.insert (new A3H45 ((str = "3H45"))).first;
//     AtomType::a3H46 = *repository.insert (new A3H46 ((str = "3H46"))).first;
//     AtomType::a3H47 = *repository.insert (new A3H47 ((str = "3H47"))).first;
//     AtomType::a3H48 = *repository.insert (new A3H48 ((str = "3H48"))).first;
//     AtomType::a3H49 = *repository.insert (new A3H49 ((str = "3H49"))).first;
//     AtomType::a3H4A = *repository.insert (new A3H4A ((str = "3H4A"))).first;
//     AtomType::a3H4B = *repository.insert (new A3H4B ((str = "3H4B"))).first;
//     AtomType::a3H4C = *repository.insert (new A3H4C ((str = "3H4C"))).first;
//     AtomType::a3H4E = *repository.insert (new A3H4E ((str = "3H4E"))).first;
//     AtomType::a3H4I = *repository.insert (new A3H4I ((str = "3H4I"))).first;
//     AtomType::a3H4M = *repository.insert (new A3H4M ((str = "3H4M"))).first;
//     AtomType::a3H4T = *repository.insert (new A3H4T ((str = "3H4T"))).first;
//     AtomType::a3H5 = *repository.insert (new A3H5 ((str = "3H5"))).first;
//     AtomType::a3H5" = *repository.insert (new A3H5" ((str = "3H5""))).first;
//     AtomType::a3H5* = *repository.insert (new A3H5* ((str = "3H5*"))).first;
//     AtomType::a3H50 = *repository.insert (new A3H50 ((str = "3H50"))).first;
//     AtomType::a3H51 = *repository.insert (new A3H51 ((str = "3H51"))).first;
//     AtomType::a3H52 = *repository.insert (new A3H52 ((str = "3H52"))).first;
//     AtomType::a3H53 = *repository.insert (new A3H53 ((str = "3H53"))).first;
//     AtomType::a3H54 = *repository.insert (new A3H54 ((str = "3H54"))).first;
//     AtomType::a3H55 = *repository.insert (new A3H55 ((str = "3H55"))).first;
//     AtomType::a3H56 = *repository.insert (new A3H56 ((str = "3H56"))).first;
//     AtomType::a3H57 = *repository.insert (new A3H57 ((str = "3H57"))).first;
//     AtomType::a3H58 = *repository.insert (new A3H58 ((str = "3H58"))).first;
//     AtomType::a3H59 = *repository.insert (new A3H59 ((str = "3H59"))).first;
//     AtomType::a3H5B = *repository.insert (new A3H5B ((str = "3H5B"))).first;
//     AtomType::a3H5C = *repository.insert (new A3H5C ((str = "3H5C"))).first;
//     AtomType::a3H5M = *repository.insert (new A3H5M ((str = "3H5M"))).first;
//     AtomType::a3H5N = *repository.insert (new A3H5N ((str = "3H5N"))).first;
//     AtomType::a3H5P = *repository.insert (new A3H5P ((str = "3H5P"))).first;
//     AtomType::a3H5S = *repository.insert (new A3H5S ((str = "3H5S"))).first;
//     AtomType::a3H5X = *repository.insert (new A3H5X ((str = "3H5X"))).first;
//     AtomType::a3H6 = *repository.insert (new A3H6 ((str = "3H6"))).first;
//     AtomType::a3H6" = *repository.insert (new A3H6" ((str = "3H6""))).first;
//     AtomType::a3H6* = *repository.insert (new A3H6* ((str = "3H6*"))).first;
//     AtomType::a3H60 = *repository.insert (new A3H60 ((str = "3H60"))).first;
//     AtomType::a3H61 = *repository.insert (new A3H61 ((str = "3H61"))).first;
//     AtomType::a3H62 = *repository.insert (new A3H62 ((str = "3H62"))).first;
//     AtomType::a3H63 = *repository.insert (new A3H63 ((str = "3H63"))).first;
//     AtomType::a3H64 = *repository.insert (new A3H64 ((str = "3H64"))).first;
//     AtomType::a3H65 = *repository.insert (new A3H65 ((str = "3H65"))).first;
//     AtomType::a3H66 = *repository.insert (new A3H66 ((str = "3H66"))).first;
//     AtomType::a3H67 = *repository.insert (new A3H67 ((str = "3H67"))).first;
//     AtomType::a3H68 = *repository.insert (new A3H68 ((str = "3H68"))).first;
//     AtomType::a3H69 = *repository.insert (new A3H69 ((str = "3H69"))).first;
//     AtomType::a3H6A = *repository.insert (new A3H6A ((str = "3H6A"))).first;
//     AtomType::a3H6B = *repository.insert (new A3H6B ((str = "3H6B"))).first;
//     AtomType::a3H6C = *repository.insert (new A3H6C ((str = "3H6C"))).first;
//     AtomType::a3H6D = *repository.insert (new A3H6D ((str = "3H6D"))).first;
//     AtomType::a3H6E = *repository.insert (new A3H6E ((str = "3H6E"))).first;
//     AtomType::a3H6G = *repository.insert (new A3H6G ((str = "3H6G"))).first;
//     AtomType::a3H6J = *repository.insert (new A3H6J ((str = "3H6J"))).first;
//     AtomType::a3H6L = *repository.insert (new A3H6L ((str = "3H6L"))).first;
//     AtomType::a3H6M = *repository.insert (new A3H6M ((str = "3H6M"))).first;
//     AtomType::a3H6X = *repository.insert (new A3H6X ((str = "3H6X"))).first;
//     AtomType::a3H6Y = *repository.insert (new A3H6Y ((str = "3H6Y"))).first;
//     AtomType::a3H6Z = *repository.insert (new A3H6Z ((str = "3H6Z"))).first;
//     AtomType::a3H7 = *repository.insert (new A3H7 ((str = "3H7"))).first;
//     AtomType::a3H7* = *repository.insert (new A3H7* ((str = "3H7*"))).first;
//     AtomType::a3H71 = *repository.insert (new A3H71 ((str = "3H71"))).first;
//     AtomType::a3H72 = *repository.insert (new A3H72 ((str = "3H72"))).first;
//     AtomType::a3H73 = *repository.insert (new A3H73 ((str = "3H73"))).first;
//     AtomType::a3H74 = *repository.insert (new A3H74 ((str = "3H74"))).first;
//     AtomType::a3H75 = *repository.insert (new A3H75 ((str = "3H75"))).first;
//     AtomType::a3H76 = *repository.insert (new A3H76 ((str = "3H76"))).first;
//     AtomType::a3H77 = *repository.insert (new A3H77 ((str = "3H77"))).first;
//     AtomType::a3H78 = *repository.insert (new A3H78 ((str = "3H78"))).first;
//     AtomType::a3H79 = *repository.insert (new A3H79 ((str = "3H79"))).first;
//     AtomType::a3H7A = *repository.insert (new A3H7A ((str = "3H7A"))).first;
//     AtomType::a3H7B = *repository.insert (new A3H7B ((str = "3H7B"))).first;
//     AtomType::a3H7C = *repository.insert (new A3H7C ((str = "3H7C"))).first;
//     AtomType::a3H7D = *repository.insert (new A3H7D ((str = "3H7D"))).first;
//     AtomType::a3H7M = *repository.insert (new A3H7M ((str = "3H7M"))).first;
//     AtomType::a3H7R = *repository.insert (new A3H7R ((str = "3H7R"))).first;
//     AtomType::a3H7T = *repository.insert (new A3H7T ((str = "3H7T"))).first;
//     AtomType::a3H8 = *repository.insert (new A3H8 ((str = "3H8"))).first;
//     AtomType::a3H8* = *repository.insert (new A3H8* ((str = "3H8*"))).first;
//     AtomType::a3H80 = *repository.insert (new A3H80 ((str = "3H80"))).first;
//     AtomType::a3H81 = *repository.insert (new A3H81 ((str = "3H81"))).first;
//     AtomType::a3H82 = *repository.insert (new A3H82 ((str = "3H82"))).first;
//     AtomType::a3H83 = *repository.insert (new A3H83 ((str = "3H83"))).first;
//     AtomType::a3H84 = *repository.insert (new A3H84 ((str = "3H84"))).first;
//     AtomType::a3H86 = *repository.insert (new A3H86 ((str = "3H86"))).first;
//     AtomType::a3H87 = *repository.insert (new A3H87 ((str = "3H87"))).first;
//     AtomType::a3H88 = *repository.insert (new A3H88 ((str = "3H88"))).first;
//     AtomType::a3H89 = *repository.insert (new A3H89 ((str = "3H89"))).first;
//     AtomType::a3H8A = *repository.insert (new A3H8A ((str = "3H8A"))).first;
//     AtomType::a3H8B = *repository.insert (new A3H8B ((str = "3H8B"))).first;
//     AtomType::a3H8C = *repository.insert (new A3H8C ((str = "3H8C"))).first;
//     AtomType::a3H8E = *repository.insert (new A3H8E ((str = "3H8E"))).first;
//     AtomType::a3H8M = *repository.insert (new A3H8M ((str = "3H8M"))).first;
//     AtomType::a3H8N = *repository.insert (new A3H8N ((str = "3H8N"))).first;
//     AtomType::a3H8S = *repository.insert (new A3H8S ((str = "3H8S"))).first;
//     AtomType::a3H9 = *repository.insert (new A3H9 ((str = "3H9"))).first;
//     AtomType::a3H9* = *repository.insert (new A3H9* ((str = "3H9*"))).first;
//     AtomType::a3H90 = *repository.insert (new A3H90 ((str = "3H90"))).first;
//     AtomType::a3H91 = *repository.insert (new A3H91 ((str = "3H91"))).first;
//     AtomType::a3H92 = *repository.insert (new A3H92 ((str = "3H92"))).first;
//     AtomType::a3H93 = *repository.insert (new A3H93 ((str = "3H93"))).first;
//     AtomType::a3H94 = *repository.insert (new A3H94 ((str = "3H94"))).first;
//     AtomType::a3H95 = *repository.insert (new A3H95 ((str = "3H95"))).first;
//     AtomType::a3H96 = *repository.insert (new A3H96 ((str = "3H96"))).first;
//     AtomType::a3H97 = *repository.insert (new A3H97 ((str = "3H97"))).first;
//     AtomType::a3H98 = *repository.insert (new A3H98 ((str = "3H98"))).first;
//     AtomType::a3H99 = *repository.insert (new A3H99 ((str = "3H99"))).first;
//     AtomType::a3H9A = *repository.insert (new A3H9A ((str = "3H9A"))).first;
//     AtomType::a3H9B = *repository.insert (new A3H9B ((str = "3H9B"))).first;
//     AtomType::a3H9C = *repository.insert (new A3H9C ((str = "3H9C"))).first;
//     AtomType::a3H9M = *repository.insert (new A3H9M ((str = "3H9M"))).first;
//     AtomType::a3H9N = *repository.insert (new A3H9N ((str = "3H9N"))).first;
//     AtomType::a3HA = *repository.insert (new A3HA ((str = "3HA"))).first;
//     AtomType::a3HA* = *repository.insert (new A3HA* ((str = "3HA*"))).first;
//     AtomType::a3HA1 = *repository.insert (new A3HA1 ((str = "3HA1"))).first;
//     AtomType::a3HA2 = *repository.insert (new A3HA2 ((str = "3HA2"))).first;
//     AtomType::a3HA3 = *repository.insert (new A3HA3 ((str = "3HA3"))).first;
//     AtomType::a3HA4 = *repository.insert (new A3HA4 ((str = "3HA4"))).first;
//     AtomType::a3HA5 = *repository.insert (new A3HA5 ((str = "3HA5"))).first;
//     AtomType::a3HA6 = *repository.insert (new A3HA6 ((str = "3HA6"))).first;
//     AtomType::a3HA7 = *repository.insert (new A3HA7 ((str = "3HA7"))).first;
//     AtomType::a3HA9 = *repository.insert (new A3HA9 ((str = "3HA9"))).first;
//     AtomType::a3HAA = *repository.insert (new A3HAA ((str = "3HAA"))).first;
//     AtomType::a3HAB = *repository.insert (new A3HAB ((str = "3HAB"))).first;
//     AtomType::a3HAC = *repository.insert (new A3HAC ((str = "3HAC"))).first;
//     AtomType::a3HAD = *repository.insert (new A3HAD ((str = "3HAD"))).first;
//     AtomType::a3HAE = *repository.insert (new A3HAE ((str = "3HAE"))).first;
//     AtomType::a3HAF = *repository.insert (new A3HAF ((str = "3HAF"))).first;
//     AtomType::a3HAG = *repository.insert (new A3HAG ((str = "3HAG"))).first;
//     AtomType::a3HAH = *repository.insert (new A3HAH ((str = "3HAH"))).first;
//     AtomType::a3HAI = *repository.insert (new A3HAI ((str = "3HAI"))).first;
//     AtomType::a3HAJ = *repository.insert (new A3HAJ ((str = "3HAJ"))).first;
//     AtomType::a3HAK = *repository.insert (new A3HAK ((str = "3HAK"))).first;
//     AtomType::a3HAL = *repository.insert (new A3HAL ((str = "3HAL"))).first;
//     AtomType::a3HAM = *repository.insert (new A3HAM ((str = "3HAM"))).first;
//     AtomType::a3HAN = *repository.insert (new A3HAN ((str = "3HAN"))).first;
//     AtomType::a3HAO = *repository.insert (new A3HAO ((str = "3HAO"))).first;
//     AtomType::a3HAP = *repository.insert (new A3HAP ((str = "3HAP"))).first;
//     AtomType::a3HAQ = *repository.insert (new A3HAQ ((str = "3HAQ"))).first;
//     AtomType::a3HAR = *repository.insert (new A3HAR ((str = "3HAR"))).first;
//     AtomType::a3HAS = *repository.insert (new A3HAS ((str = "3HAS"))).first;
//     AtomType::a3HAT = *repository.insert (new A3HAT ((str = "3HAT"))).first;
//     AtomType::a3HAU = *repository.insert (new A3HAU ((str = "3HAU"))).first;
//     AtomType::a3HAW = *repository.insert (new A3HAW ((str = "3HAW"))).first;
//     AtomType::a3HAX = *repository.insert (new A3HAX ((str = "3HAX"))).first;
//     AtomType::a3HAY = *repository.insert (new A3HAY ((str = "3HAY"))).first;
//     AtomType::a3HAZ = *repository.insert (new A3HAZ ((str = "3HAZ"))).first;
//     AtomType::a3HB* = *repository.insert (new A3HB* ((str = "3HB*"))).first;
//     AtomType::a3HB0 = *repository.insert (new A3HB0 ((str = "3HB0"))).first;
//     AtomType::a3HB1 = *repository.insert (new A3HB1 ((str = "3HB1"))).first;
//     AtomType::a3HB2 = *repository.insert (new A3HB2 ((str = "3HB2"))).first;
//     AtomType::a3HB3 = *repository.insert (new A3HB3 ((str = "3HB3"))).first;
//     AtomType::a3HB6 = *repository.insert (new A3HB6 ((str = "3HB6"))).first;
//     AtomType::a3HB7 = *repository.insert (new A3HB7 ((str = "3HB7"))).first;
//     AtomType::a3HB8 = *repository.insert (new A3HB8 ((str = "3HB8"))).first;
//     AtomType::a3HBA = *repository.insert (new A3HBA ((str = "3HBA"))).first;
//     AtomType::a3HBB = *repository.insert (new A3HBB ((str = "3HBB"))).first;
//     AtomType::a3HBC = *repository.insert (new A3HBC ((str = "3HBC"))).first;
//     AtomType::a3HBD = *repository.insert (new A3HBD ((str = "3HBD"))).first;
//     AtomType::a3HBE = *repository.insert (new A3HBE ((str = "3HBE"))).first;
//     AtomType::a3HBF = *repository.insert (new A3HBF ((str = "3HBF"))).first;
//     AtomType::a3HBG = *repository.insert (new A3HBG ((str = "3HBG"))).first;
//     AtomType::a3HBI = *repository.insert (new A3HBI ((str = "3HBI"))).first;
//     AtomType::a3HBJ = *repository.insert (new A3HBJ ((str = "3HBJ"))).first;
//     AtomType::a3HBL = *repository.insert (new A3HBL ((str = "3HBL"))).first;
//     AtomType::a3HBM = *repository.insert (new A3HBM ((str = "3HBM"))).first;
//     AtomType::a3HBO = *repository.insert (new A3HBO ((str = "3HBO"))).first;
//     AtomType::a3HBP = *repository.insert (new A3HBP ((str = "3HBP"))).first;
//     AtomType::a3HBT = *repository.insert (new A3HBT ((str = "3HBT"))).first;
//     AtomType::a3HBW = *repository.insert (new A3HBW ((str = "3HBW"))).first;
//     AtomType::a3HBX = *repository.insert (new A3HBX ((str = "3HBX"))).first;
//     AtomType::a3HBY = *repository.insert (new A3HBY ((str = "3HBY"))).first;
//     AtomType::a3HBZ = *repository.insert (new A3HBZ ((str = "3HBZ"))).first;
//     AtomType::a3HC = *repository.insert (new A3HC ((str = "3HC"))).first;
//     AtomType::a3HC" = *repository.insert (new A3HC" ((str = "3HC""))).first;
//     AtomType::a3HC* = *repository.insert (new A3HC* ((str = "3HC*"))).first;
//     AtomType::a3HC0 = *repository.insert (new A3HC0 ((str = "3HC0"))).first;
//     AtomType::a3HC1 = *repository.insert (new A3HC1 ((str = "3HC1"))).first;
//     AtomType::a3HC2 = *repository.insert (new A3HC2 ((str = "3HC2"))).first;
//     AtomType::a3HC3 = *repository.insert (new A3HC3 ((str = "3HC3"))).first;
//     AtomType::a3HC4 = *repository.insert (new A3HC4 ((str = "3HC4"))).first;
//     AtomType::a3HC5 = *repository.insert (new A3HC5 ((str = "3HC5"))).first;
//     AtomType::a3HC6 = *repository.insert (new A3HC6 ((str = "3HC6"))).first;
//     AtomType::a3HC7 = *repository.insert (new A3HC7 ((str = "3HC7"))).first;
//     AtomType::a3HC8 = *repository.insert (new A3HC8 ((str = "3HC8"))).first;
//     AtomType::a3HC9 = *repository.insert (new A3HC9 ((str = "3HC9"))).first;
//     AtomType::a3HCA = *repository.insert (new A3HCA ((str = "3HCA"))).first;
//     AtomType::a3HCB = *repository.insert (new A3HCB ((str = "3HCB"))).first;
//     AtomType::a3HCC = *repository.insert (new A3HCC ((str = "3HCC"))).first;
//     AtomType::a3HCD = *repository.insert (new A3HCD ((str = "3HCD"))).first;
//     AtomType::a3HCE = *repository.insert (new A3HCE ((str = "3HCE"))).first;
//     AtomType::a3HCH = *repository.insert (new A3HCH ((str = "3HCH"))).first;
//     AtomType::a3HCI = *repository.insert (new A3HCI ((str = "3HCI"))).first;
//     AtomType::a3HCM = *repository.insert (new A3HCM ((str = "3HCM"))).first;
//     AtomType::a3HCN = *repository.insert (new A3HCN ((str = "3HCN"))).first;
//     AtomType::a3HCO = *repository.insert (new A3HCO ((str = "3HCO"))).first;
//     AtomType::a3HCP = *repository.insert (new A3HCP ((str = "3HCP"))).first;
//     AtomType::a3HCS = *repository.insert (new A3HCS ((str = "3HCS"))).first;
//     AtomType::a3HCT = *repository.insert (new A3HCT ((str = "3HCT"))).first;
//     AtomType::a3HCV = *repository.insert (new A3HCV ((str = "3HCV"))).first;
//     AtomType::a3HCX = *repository.insert (new A3HCX ((str = "3HCX"))).first;
//     AtomType::a3HD = *repository.insert (new A3HD ((str = "3HD"))).first;
//     AtomType::a3HD* = *repository.insert (new A3HD* ((str = "3HD*"))).first;
//     AtomType::a3HD0 = *repository.insert (new A3HD0 ((str = "3HD0"))).first;
//     AtomType::a3HD1 = *repository.insert (new A3HD1 ((str = "3HD1"))).first;
//     AtomType::a3HD2 = *repository.insert (new A3HD2 ((str = "3HD2"))).first;
//     AtomType::a3HD3 = *repository.insert (new A3HD3 ((str = "3HD3"))).first;
//     AtomType::a3HD4 = *repository.insert (new A3HD4 ((str = "3HD4"))).first;
//     AtomType::a3HD5 = *repository.insert (new A3HD5 ((str = "3HD5"))).first;
//     AtomType::a3HD6 = *repository.insert (new A3HD6 ((str = "3HD6"))).first;
//     AtomType::a3HD7 = *repository.insert (new A3HD7 ((str = "3HD7"))).first;
//     AtomType::a3HD8 = *repository.insert (new A3HD8 ((str = "3HD8"))).first;
//     AtomType::a3HD9 = *repository.insert (new A3HD9 ((str = "3HD9"))).first;
//     AtomType::a3HDA = *repository.insert (new A3HDA ((str = "3HDA"))).first;
//     AtomType::a3HDB = *repository.insert (new A3HDB ((str = "3HDB"))).first;
//     AtomType::a3HDL = *repository.insert (new A3HDL ((str = "3HDL"))).first;
//     AtomType::a3HDM = *repository.insert (new A3HDM ((str = "3HDM"))).first;
//     AtomType::a3HE" = *repository.insert (new A3HE" ((str = "3HE""))).first;
//     AtomType::a3HE* = *repository.insert (new A3HE* ((str = "3HE*"))).first;
//     AtomType::a3HE1 = *repository.insert (new A3HE1 ((str = "3HE1"))).first;
//     AtomType::a3HE2 = *repository.insert (new A3HE2 ((str = "3HE2"))).first;
//     AtomType::a3HE3 = *repository.insert (new A3HE3 ((str = "3HE3"))).first;
//     AtomType::a3HE4 = *repository.insert (new A3HE4 ((str = "3HE4"))).first;
//     AtomType::a3HEA = *repository.insert (new A3HEA ((str = "3HEA"))).first;
//     AtomType::a3HEC = *repository.insert (new A3HEC ((str = "3HEC"))).first;
//     AtomType::a3HED = *repository.insert (new A3HED ((str = "3HED"))).first;
//     AtomType::a3HEI = *repository.insert (new A3HEI ((str = "3HEI"))).first;
//     AtomType::a3HEM = *repository.insert (new A3HEM ((str = "3HEM"))).first;
//     AtomType::a3HEP = *repository.insert (new A3HEP ((str = "3HEP"))).first;
//     AtomType::a3HF = *repository.insert (new A3HF ((str = "3HF"))).first;
//     AtomType::a3HF* = *repository.insert (new A3HF* ((str = "3HF*"))).first;
//     AtomType::a3HF1 = *repository.insert (new A3HF1 ((str = "3HF1"))).first;
//     AtomType::a3HFM = *repository.insert (new A3HFM ((str = "3HFM"))).first;
//     AtomType::a3HG = *repository.insert (new A3HG ((str = "3HG"))).first;
//     AtomType::a3HG* = *repository.insert (new A3HG* ((str = "3HG*"))).first;
//     AtomType::a3HG1 = *repository.insert (new A3HG1 ((str = "3HG1"))).first;
//     AtomType::a3HG2 = *repository.insert (new A3HG2 ((str = "3HG2"))).first;
//     AtomType::a3HG3 = *repository.insert (new A3HG3 ((str = "3HG3"))).first;
//     AtomType::a3HG4 = *repository.insert (new A3HG4 ((str = "3HG4"))).first;
//     AtomType::a3HG5 = *repository.insert (new A3HG5 ((str = "3HG5"))).first;
//     AtomType::a3HG6 = *repository.insert (new A3HG6 ((str = "3HG6"))).first;
//     AtomType::a3HG7 = *repository.insert (new A3HG7 ((str = "3HG7"))).first;
//     AtomType::a3HG8 = *repository.insert (new A3HG8 ((str = "3HG8"))).first;
//     AtomType::a3HGB = *repository.insert (new A3HGB ((str = "3HGB"))).first;
//     AtomType::a3HGC = *repository.insert (new A3HGC ((str = "3HGC"))).first;
//     AtomType::a3HGT = *repository.insert (new A3HGT ((str = "3HGT"))).first;
//     AtomType::a3HH = *repository.insert (new A3HH ((str = "3HH"))).first;
//     AtomType::a3HH1 = *repository.insert (new A3HH1 ((str = "3HH1"))).first;
//     AtomType::a3HH2 = *repository.insert (new A3HH2 ((str = "3HH2"))).first;
//     AtomType::a3HH3 = *repository.insert (new A3HH3 ((str = "3HH3"))).first;
//     AtomType::a3HH6 = *repository.insert (new A3HH6 ((str = "3HH6"))).first;
//     AtomType::a3HHR = *repository.insert (new A3HHR ((str = "3HHR"))).first;
//     AtomType::a3HI = *repository.insert (new A3HI ((str = "3HI"))).first;
//     AtomType::a3HI* = *repository.insert (new A3HI* ((str = "3HI*"))).first;
//     AtomType::a3HI1 = *repository.insert (new A3HI1 ((str = "3HI1"))).first;
//     AtomType::a3HI2 = *repository.insert (new A3HI2 ((str = "3HI2"))).first;
//     AtomType::a3HI3 = *repository.insert (new A3HI3 ((str = "3HI3"))).first;
//     AtomType::a3HIB = *repository.insert (new A3HIB ((str = "3HIB"))).first;
//     AtomType::a3HIF = *repository.insert (new A3HIF ((str = "3HIF"))).first;
//     AtomType::a3HJ = *repository.insert (new A3HJ ((str = "3HJ"))).first;
//     AtomType::a3HJ" = *repository.insert (new A3HJ" ((str = "3HJ""))).first;
//     AtomType::a3HJ* = *repository.insert (new A3HJ* ((str = "3HJ*"))).first;
//     AtomType::a3HK = *repository.insert (new A3HK ((str = "3HK"))).first;
//     AtomType::a3HK* = *repository.insert (new A3HK* ((str = "3HK*"))).first;
//     AtomType::a3HK1 = *repository.insert (new A3HK1 ((str = "3HK1"))).first;
//     AtomType::a3HK2 = *repository.insert (new A3HK2 ((str = "3HK2"))).first;
//     AtomType::a3HK5 = *repository.insert (new A3HK5 ((str = "3HK5"))).first;
//     AtomType::a3HK6 = *repository.insert (new A3HK6 ((str = "3HK6"))).first;
//     AtomType::a3HL = *repository.insert (new A3HL ((str = "3HL"))).first;
//     AtomType::a3HL1 = *repository.insert (new A3HL1 ((str = "3HL1"))).first;
//     AtomType::a3HL2 = *repository.insert (new A3HL2 ((str = "3HL2"))).first;
//     AtomType::a3HL5 = *repository.insert (new A3HL5 ((str = "3HL5"))).first;
//     AtomType::a3HL6 = *repository.insert (new A3HL6 ((str = "3HL6"))).first;
//     AtomType::a3HL7 = *repository.insert (new A3HL7 ((str = "3HL7"))).first;
//     AtomType::a3HLB = *repository.insert (new A3HLB ((str = "3HLB"))).first;
//     AtomType::a3HM = *repository.insert (new A3HM ((str = "3HM"))).first;
//     AtomType::a3HM" = *repository.insert (new A3HM" ((str = "3HM""))).first;
//     AtomType::a3HM* = *repository.insert (new A3HM* ((str = "3HM*"))).first;
//     AtomType::a3HM0 = *repository.insert (new A3HM0 ((str = "3HM0"))).first;
    AtomType::a3HM1 = *repository.insert (new A3HM1 ((str = "3HM1"))).first;
//     AtomType::a3HM2 = *repository.insert (new A3HM2 ((str = "3HM2"))).first;
//     AtomType::a3HM3 = *repository.insert (new A3HM3 ((str = "3HM3"))).first;
//     AtomType::a3HM4 = *repository.insert (new A3HM4 ((str = "3HM4"))).first;
//     AtomType::a3HM5 = *repository.insert (new A3HM5 ((str = "3HM5"))).first;
//     AtomType::a3HM6 = *repository.insert (new A3HM6 ((str = "3HM6"))).first;
//     AtomType::a3HM7 = *repository.insert (new A3HM7 ((str = "3HM7"))).first;
//     AtomType::a3HM8 = *repository.insert (new A3HM8 ((str = "3HM8"))).first;
//     AtomType::a3HM9 = *repository.insert (new A3HM9 ((str = "3HM9"))).first;
//     AtomType::a3HMA = *repository.insert (new A3HMA ((str = "3HMA"))).first;
//     AtomType::a3HMB = *repository.insert (new A3HMB ((str = "3HMB"))).first;
//     AtomType::a3HMC = *repository.insert (new A3HMC ((str = "3HMC"))).first;
//     AtomType::a3HMD = *repository.insert (new A3HMD ((str = "3HMD"))).first;
//     AtomType::a3HME = *repository.insert (new A3HME ((str = "3HME"))).first;
//     AtomType::a3HMF = *repository.insert (new A3HMF ((str = "3HMF"))).first;
//     AtomType::a3HMK = *repository.insert (new A3HMK ((str = "3HMK"))).first;
//     AtomType::a3HMP = *repository.insert (new A3HMP ((str = "3HMP"))).first;
//     AtomType::a3HMZ = *repository.insert (new A3HMZ ((str = "3HMZ"))).first;
//     AtomType::a3HN = *repository.insert (new A3HN ((str = "3HN"))).first;
//     AtomType::a3HN* = *repository.insert (new A3HN* ((str = "3HN*"))).first;
//     AtomType::a3HN1 = *repository.insert (new A3HN1 ((str = "3HN1"))).first;
//     AtomType::a3HN2 = *repository.insert (new A3HN2 ((str = "3HN2"))).first;
//     AtomType::a3HN3 = *repository.insert (new A3HN3 ((str = "3HN3"))).first;
//     AtomType::a3HN4 = *repository.insert (new A3HN4 ((str = "3HN4"))).first;
//     AtomType::a3HN5 = *repository.insert (new A3HN5 ((str = "3HN5"))).first;
//     AtomType::a3HN6 = *repository.insert (new A3HN6 ((str = "3HN6"))).first;
//     AtomType::a3HN7 = *repository.insert (new A3HN7 ((str = "3HN7"))).first;
//     AtomType::a3HN8 = *repository.insert (new A3HN8 ((str = "3HN8"))).first;
//     AtomType::a3HN9 = *repository.insert (new A3HN9 ((str = "3HN9"))).first;
//     AtomType::a3HNA = *repository.insert (new A3HNA ((str = "3HNA"))).first;
//     AtomType::a3HNB = *repository.insert (new A3HNB ((str = "3HNB"))).first;
//     AtomType::a3HNC = *repository.insert (new A3HNC ((str = "3HNC"))).first;
//     AtomType::a3HNE = *repository.insert (new A3HNE ((str = "3HNE"))).first;
//     AtomType::a3HNG = *repository.insert (new A3HNG ((str = "3HNG"))).first;
//     AtomType::a3HNP = *repository.insert (new A3HNP ((str = "3HNP"))).first;
//     AtomType::a3HNS = *repository.insert (new A3HNS ((str = "3HNS"))).first;
//     AtomType::a3HNZ = *repository.insert (new A3HNZ ((str = "3HNZ"))).first;
//     AtomType::a3HO = *repository.insert (new A3HO ((str = "3HO"))).first;
//     AtomType::a3HO* = *repository.insert (new A3HO* ((str = "3HO*"))).first;
//     AtomType::a3HO1 = *repository.insert (new A3HO1 ((str = "3HO1"))).first;
//     AtomType::a3HO2 = *repository.insert (new A3HO2 ((str = "3HO2"))).first;
//     AtomType::a3HO3 = *repository.insert (new A3HO3 ((str = "3HO3"))).first;
//     AtomType::a3HO4 = *repository.insert (new A3HO4 ((str = "3HO4"))).first;
//     AtomType::a3HO5 = *repository.insert (new A3HO5 ((str = "3HO5"))).first;
//     AtomType::a3HO6 = *repository.insert (new A3HO6 ((str = "3HO6"))).first;
//     AtomType::a3HOA = *repository.insert (new A3HOA ((str = "3HOA"))).first;
//     AtomType::a3HOB = *repository.insert (new A3HOB ((str = "3HOB"))).first;
//     AtomType::a3HOC = *repository.insert (new A3HOC ((str = "3HOC"))).first;
//     AtomType::a3HOD = *repository.insert (new A3HOD ((str = "3HOD"))).first;
//     AtomType::a3HOE = *repository.insert (new A3HOE ((str = "3HOE"))).first;
//     AtomType::a3HOG = *repository.insert (new A3HOG ((str = "3HOG"))).first;
//     AtomType::a3HOJ = *repository.insert (new A3HOJ ((str = "3HOJ"))).first;
//     AtomType::a3HOM = *repository.insert (new A3HOM ((str = "3HOM"))).first;
//     AtomType::a3HOR = *repository.insert (new A3HOR ((str = "3HOR"))).first;
//     AtomType::a3HOS = *repository.insert (new A3HOS ((str = "3HOS"))).first;
//     AtomType::a3HOU = *repository.insert (new A3HOU ((str = "3HOU"))).first;
//     AtomType::a3HOV = *repository.insert (new A3HOV ((str = "3HOV"))).first;
//     AtomType::a3HOW = *repository.insert (new A3HOW ((str = "3HOW"))).first;
//     AtomType::a3HOX = *repository.insert (new A3HOX ((str = "3HOX"))).first;
//     AtomType::a3HOY = *repository.insert (new A3HOY ((str = "3HOY"))).first;
//     AtomType::a3HOZ = *repository.insert (new A3HOZ ((str = "3HOZ"))).first;
//     AtomType::a3HP = *repository.insert (new A3HP ((str = "3HP"))).first;
//     AtomType::a3HP1 = *repository.insert (new A3HP1 ((str = "3HP1"))).first;
//     AtomType::a3HP3 = *repository.insert (new A3HP3 ((str = "3HP3"))).first;
//     AtomType::a3HP4 = *repository.insert (new A3HP4 ((str = "3HP4"))).first;
//     AtomType::a3HP5 = *repository.insert (new A3HP5 ((str = "3HP5"))).first;
//     AtomType::a3HP7 = *repository.insert (new A3HP7 ((str = "3HP7"))).first;
//     AtomType::a3HP8 = *repository.insert (new A3HP8 ((str = "3HP8"))).first;
//     AtomType::a3HP9 = *repository.insert (new A3HP9 ((str = "3HP9"))).first;
//     AtomType::a3HPA = *repository.insert (new A3HPA ((str = "3HPA"))).first;
//     AtomType::a3HPB = *repository.insert (new A3HPB ((str = "3HPB"))).first;
//     AtomType::a3HPD = *repository.insert (new A3HPD ((str = "3HPD"))).first;
//     AtomType::a3HPE = *repository.insert (new A3HPE ((str = "3HPE"))).first;
//     AtomType::a3HQ = *repository.insert (new A3HQ ((str = "3HQ"))).first;
//     AtomType::a3HQ1 = *repository.insert (new A3HQ1 ((str = "3HQ1"))).first;
//     AtomType::a3HQ2 = *repository.insert (new A3HQ2 ((str = "3HQ2"))).first;
//     AtomType::a3HR = *repository.insert (new A3HR ((str = "3HR"))).first;
//     AtomType::a3HR* = *repository.insert (new A3HR* ((str = "3HR*"))).first;
//     AtomType::a3HS = *repository.insert (new A3HS ((str = "3HS"))).first;
//     AtomType::a3HS1 = *repository.insert (new A3HS1 ((str = "3HS1"))).first;
//     AtomType::a3HS2 = *repository.insert (new A3HS2 ((str = "3HS2"))).first;
//     AtomType::a3HS3 = *repository.insert (new A3HS3 ((str = "3HS3"))).first;
//     AtomType::a3HS4 = *repository.insert (new A3HS4 ((str = "3HS4"))).first;
//     AtomType::a3HS5 = *repository.insert (new A3HS5 ((str = "3HS5"))).first;
//     AtomType::a3HS6 = *repository.insert (new A3HS6 ((str = "3HS6"))).first;
//     AtomType::a3HSG = *repository.insert (new A3HSG ((str = "3HSG"))).first;
//     AtomType::a3HSP = *repository.insert (new A3HSP ((str = "3HSP"))).first;
//     AtomType::a3HT = *repository.insert (new A3HT ((str = "3HT"))).first;
//     AtomType::a3HT* = *repository.insert (new A3HT* ((str = "3HT*"))).first;
//     AtomType::a3HT2 = *repository.insert (new A3HT2 ((str = "3HT2"))).first;
//     AtomType::a3HT3 = *repository.insert (new A3HT3 ((str = "3HT3"))).first;
//     AtomType::a3HT4 = *repository.insert (new A3HT4 ((str = "3HT4"))).first;
//     AtomType::a3HT5 = *repository.insert (new A3HT5 ((str = "3HT5"))).first;
//     AtomType::a3HV = *repository.insert (new A3HV ((str = "3HV"))).first;
//     AtomType::a3HV1 = *repository.insert (new A3HV1 ((str = "3HV1"))).first;
//     AtomType::a3HV2 = *repository.insert (new A3HV2 ((str = "3HV2"))).first;
//     AtomType::a3HV3 = *repository.insert (new A3HV3 ((str = "3HV3"))).first;
//     AtomType::a3HV4 = *repository.insert (new A3HV4 ((str = "3HV4"))).first;
//     AtomType::a3HV6 = *repository.insert (new A3HV6 ((str = "3HV6"))).first;
//     AtomType::a3HV8 = *repository.insert (new A3HV8 ((str = "3HV8"))).first;
//     AtomType::a3HV9 = *repository.insert (new A3HV9 ((str = "3HV9"))).first;
//     AtomType::a3HX = *repository.insert (new A3HX ((str = "3HX"))).first;
//     AtomType::a3HX8 = *repository.insert (new A3HX8 ((str = "3HX8"))).first;
//     AtomType::a3HXT = *repository.insert (new A3HXT ((str = "3HXT"))).first;
//     AtomType::a3HY1 = *repository.insert (new A3HY1 ((str = "3HY1"))).first;
//     AtomType::a3HY4 = *repository.insert (new A3HY4 ((str = "3HY4"))).first;
//     AtomType::a3HY6 = *repository.insert (new A3HY6 ((str = "3HY6"))).first;
//     AtomType::a3HZ1 = *repository.insert (new A3HZ1 ((str = "3HZ1"))).first;
//     AtomType::a3HZ2 = *repository.insert (new A3HZ2 ((str = "3HZ2"))).first;
//     AtomType::a3HZ3 = *repository.insert (new A3HZ3 ((str = "3HZ3"))).first;
//     AtomType::a3HZ6 = *repository.insert (new A3HZ6 ((str = "3HZ6"))).first;
//     AtomType::a3HZ7 = *repository.insert (new A3HZ7 ((str = "3HZ7"))).first;
//     AtomType::a3HZ8 = *repository.insert (new A3HZ8 ((str = "3HZ8"))).first;
//     AtomType::a3HZA = *repository.insert (new A3HZA ((str = "3HZA"))).first;
//     AtomType::a3HZH = *repository.insert (new A3HZH ((str = "3HZH"))).first;
//     AtomType::a3N = *repository.insert (new A3N ((str = "3N"))).first;
//     AtomType::a3N10 = *repository.insert (new A3N10 ((str = "3N10"))).first;
//     AtomType::a3N2 = *repository.insert (new A3N2 ((str = "3N2"))).first;
//     AtomType::a3ND1 = *repository.insert (new A3ND1 ((str = "3ND1"))).first;
//     AtomType::a3NE2 = *repository.insert (new A3NE2 ((str = "3NE2"))).first;
//     AtomType::a3O = *repository.insert (new A3O ((str = "3O"))).first;
//     AtomType::a3O1 = *repository.insert (new A3O1 ((str = "3O1"))).first;
//     AtomType::a3O2 = *repository.insert (new A3O2 ((str = "3O2"))).first;
//     AtomType::a3O3 = *repository.insert (new A3O3 ((str = "3O3"))).first;
//     AtomType::a3O4 = *repository.insert (new A3O4 ((str = "3O4"))).first;
//     AtomType::a3OE1 = *repository.insert (new A3OE1 ((str = "3OE1"))).first;
//     AtomType::a3OE2 = *repository.insert (new A3OE2 ((str = "3OE2"))).first;
//     AtomType::a3OP = *repository.insert (new A3OP ((str = "3OP"))).first;
//     AtomType::a3OP* = *repository.insert (new A3OP* ((str = "3OP*"))).first;
//     AtomType::a3OP3 = *repository.insert (new A3OP3 ((str = "3OP3"))).first;
//     AtomType::a3OP5 = *repository.insert (new A3OP5 ((str = "3OP5"))).first;
//     AtomType::a3OXT = *repository.insert (new A3OXT ((str = "3OXT"))).first;
//     AtomType::a3P = *repository.insert (new A3P ((str = "3P"))).first;
//     AtomType::a4C = *repository.insert (new A4C ((str = "4C"))).first;
//     AtomType::a4C11 = *repository.insert (new A4C11 ((str = "4C11"))).first;
//     AtomType::a4C12 = *repository.insert (new A4C12 ((str = "4C12"))).first;
//     AtomType::a4C13 = *repository.insert (new A4C13 ((str = "4C13"))).first;
//     AtomType::a4C7 = *repository.insert (new A4C7 ((str = "4C7"))).first;
//     AtomType::a4C8 = *repository.insert (new A4C8 ((str = "4C8"))).first;
//     AtomType::a4C9 = *repository.insert (new A4C9 ((str = "4C9"))).first;
//     AtomType::a4CA = *repository.insert (new A4CA ((str = "4CA"))).first;
//     AtomType::a4CB = *repository.insert (new A4CB ((str = "4CB"))).first;
//     AtomType::a4CD = *repository.insert (new A4CD ((str = "4CD"))).first;
//     AtomType::a4CD1 = *repository.insert (new A4CD1 ((str = "4CD1"))).first;
//     AtomType::a4CD2 = *repository.insert (new A4CD2 ((str = "4CD2"))).first;
//     AtomType::a4CE1 = *repository.insert (new A4CE1 ((str = "4CE1"))).first;
//     AtomType::a4CE2 = *repository.insert (new A4CE2 ((str = "4CE2"))).first;
//     AtomType::a4CG = *repository.insert (new A4CG ((str = "4CG"))).first;
//     AtomType::a4CL1 = *repository.insert (new A4CL1 ((str = "4CL1"))).first;
//     AtomType::a4CZ = *repository.insert (new A4CZ ((str = "4CZ"))).first;
//     AtomType::a4D = *repository.insert (new A4D ((str = "4D"))).first;
//     AtomType::a4H = *repository.insert (new A4H ((str = "4H"))).first;
//     AtomType::a4H* = *repository.insert (new A4H* ((str = "4H*"))).first;
//     AtomType::a4H*A = *repository.insert (new A4H*A ((str = "4H*A"))).first;
//     AtomType::a4H1 = *repository.insert (new A4H1 ((str = "4H1"))).first;
//     AtomType::a4H18 = *repository.insert (new A4H18 ((str = "4H18"))).first;
//     AtomType::a4H19 = *repository.insert (new A4H19 ((str = "4H19"))).first;
//     AtomType::a4H1N = *repository.insert (new A4H1N ((str = "4H1N"))).first;
//     AtomType::a4H2 = *repository.insert (new A4H2 ((str = "4H2"))).first;
//     AtomType::a4H20 = *repository.insert (new A4H20 ((str = "4H20"))).first;
//     AtomType::a4H22 = *repository.insert (new A4H22 ((str = "4H22"))).first;
//     AtomType::a4H23 = *repository.insert (new A4H23 ((str = "4H23"))).first;
//     AtomType::a4H25 = *repository.insert (new A4H25 ((str = "4H25"))).first;
//     AtomType::a4H26 = *repository.insert (new A4H26 ((str = "4H26"))).first;
//     AtomType::a4H27 = *repository.insert (new A4H27 ((str = "4H27"))).first;
//     AtomType::a4H3 = *repository.insert (new A4H3 ((str = "4H3"))).first;
//     AtomType::a4H4 = *repository.insert (new A4H4 ((str = "4H4"))).first;
//     AtomType::a4H5 = *repository.insert (new A4H5 ((str = "4H5"))).first;
//     AtomType::a4H6 = *repository.insert (new A4H6 ((str = "4H6"))).first;
//     AtomType::a4H81 = *repository.insert (new A4H81 ((str = "4H81"))).first;
//     AtomType::a4H82 = *repository.insert (new A4H82 ((str = "4H82"))).first;
//     AtomType::a4H83 = *repository.insert (new A4H83 ((str = "4H83"))).first;
//     AtomType::a4HA = *repository.insert (new A4HA ((str = "4HA"))).first;
//     AtomType::a4HB1 = *repository.insert (new A4HB1 ((str = "4HB1"))).first;
//     AtomType::a4HB2 = *repository.insert (new A4HB2 ((str = "4HB2"))).first;
//     AtomType::a4HC = *repository.insert (new A4HC ((str = "4HC"))).first;
//     AtomType::a4HC" = *repository.insert (new A4HC" ((str = "4HC""))).first;
//     AtomType::a4HC* = *repository.insert (new A4HC* ((str = "4HC*"))).first;
//     AtomType::a4HC0 = *repository.insert (new A4HC0 ((str = "4HC0"))).first;
//     AtomType::a4HC1 = *repository.insert (new A4HC1 ((str = "4HC1"))).first;
//     AtomType::a4HC2 = *repository.insert (new A4HC2 ((str = "4HC2"))).first;
//     AtomType::a4HC4 = *repository.insert (new A4HC4 ((str = "4HC4"))).first;
//     AtomType::a4HC8 = *repository.insert (new A4HC8 ((str = "4HC8"))).first;
//     AtomType::a4HC9 = *repository.insert (new A4HC9 ((str = "4HC9"))).first;
//     AtomType::a4HCA = *repository.insert (new A4HCA ((str = "4HCA"))).first;
//     AtomType::a4HCN = *repository.insert (new A4HCN ((str = "4HCN"))).first;
//     AtomType::a4HD1 = *repository.insert (new A4HD1 ((str = "4HD1"))).first;
//     AtomType::a4HD2 = *repository.insert (new A4HD2 ((str = "4HD2"))).first;
//     AtomType::a4HE1 = *repository.insert (new A4HE1 ((str = "4HE1"))).first;
//     AtomType::a4HE2 = *repository.insert (new A4HE2 ((str = "4HE2"))).first;
//     AtomType::a4HG = *repository.insert (new A4HG ((str = "4HG"))).first;
//     AtomType::a4HG1 = *repository.insert (new A4HG1 ((str = "4HG1"))).first;
//     AtomType::a4HG2 = *repository.insert (new A4HG2 ((str = "4HG2"))).first;
//     AtomType::a4HG5 = *repository.insert (new A4HG5 ((str = "4HG5"))).first;
//     AtomType::a4HN = *repository.insert (new A4HN ((str = "4HN"))).first;
//     AtomType::a4HN* = *repository.insert (new A4HN* ((str = "4HN*"))).first;
//     AtomType::a4HN3 = *repository.insert (new A4HN3 ((str = "4HN3"))).first;
//     AtomType::a4HNA = *repository.insert (new A4HNA ((str = "4HNA"))).first;
//     AtomType::a4HNP = *repository.insert (new A4HNP ((str = "4HNP"))).first;
//     AtomType::a4HO = *repository.insert (new A4HO ((str = "4HO"))).first;
//     AtomType::a4HO* = *repository.insert (new A4HO* ((str = "4HO*"))).first;
//     AtomType::a4HO1 = *repository.insert (new A4HO1 ((str = "4HO1"))).first;
//     AtomType::a4HO2 = *repository.insert (new A4HO2 ((str = "4HO2"))).first;
//     AtomType::a4HO3 = *repository.insert (new A4HO3 ((str = "4HO3"))).first;
//     AtomType::a4HO4 = *repository.insert (new A4HO4 ((str = "4HO4"))).first;
//     AtomType::a4HO6 = *repository.insert (new A4HO6 ((str = "4HO6"))).first;
//     AtomType::a4HOA = *repository.insert (new A4HOA ((str = "4HOA"))).first;
//     AtomType::a4HOB = *repository.insert (new A4HOB ((str = "4HOB"))).first;
//     AtomType::a4HOC = *repository.insert (new A4HOC ((str = "4HOC"))).first;
//     AtomType::a4HOD = *repository.insert (new A4HOD ((str = "4HOD"))).first;
//     AtomType::a4HOE = *repository.insert (new A4HOE ((str = "4HOE"))).first;
//     AtomType::a4HOG = *repository.insert (new A4HOG ((str = "4HOG"))).first;
//     AtomType::a4HOL = *repository.insert (new A4HOL ((str = "4HOL"))).first;
//     AtomType::a4HOP = *repository.insert (new A4HOP ((str = "4HOP"))).first;
//     AtomType::a4HOS = *repository.insert (new A4HOS ((str = "4HOS"))).first;
//     AtomType::a4HOX = *repository.insert (new A4HOX ((str = "4HOX"))).first;
//     AtomType::a4HOZ = *repository.insert (new A4HOZ ((str = "4HOZ"))).first;
//     AtomType::a4HR = *repository.insert (new A4HR ((str = "4HR"))).first;
//     AtomType::a4HR* = *repository.insert (new A4HR* ((str = "4HR*"))).first;
//     AtomType::a4HXT = *repository.insert (new A4HXT ((str = "4HXT"))).first;
//     AtomType::a4HZ = *repository.insert (new A4HZ ((str = "4HZ"))).first;
//     AtomType::a4N = *repository.insert (new A4N ((str = "4N"))).first;
//     AtomType::a4N10 = *repository.insert (new A4N10 ((str = "4N10"))).first;
//     AtomType::a4ND1 = *repository.insert (new A4ND1 ((str = "4ND1"))).first;
//     AtomType::a4NE2 = *repository.insert (new A4NE2 ((str = "4NE2"))).first;
//     AtomType::a4O = *repository.insert (new A4O ((str = "4O"))).first;
//     AtomType::a4O1 = *repository.insert (new A4O1 ((str = "4O1"))).first;
//     AtomType::a4O2 = *repository.insert (new A4O2 ((str = "4O2"))).first;
//     AtomType::a4O3 = *repository.insert (new A4O3 ((str = "4O3"))).first;
//     AtomType::a4O4 = *repository.insert (new A4O4 ((str = "4O4"))).first;
//     AtomType::a4OE1 = *repository.insert (new A4OE1 ((str = "4OE1"))).first;
//     AtomType::a4OXT = *repository.insert (new A4OXT ((str = "4OXT"))).first;
//     AtomType::a5C = *repository.insert (new A5C ((str = "5C"))).first;
//     AtomType::a5CA = *repository.insert (new A5CA ((str = "5CA"))).first;
//     AtomType::a5CB = *repository.insert (new A5CB ((str = "5CB"))).first;
//     AtomType::a5CD = *repository.insert (new A5CD ((str = "5CD"))).first;
//     AtomType::a5CFK = *repository.insert (new A5CFK ((str = "5CFK"))).first;
//     AtomType::a5CG = *repository.insert (new A5CG ((str = "5CG"))).first;
//     AtomType::a5CH3 = *repository.insert (new A5CH3 ((str = "5CH3"))).first;
//     AtomType::a5H = *repository.insert (new A5H ((str = "5H"))).first;
//     AtomType::a5H*U = *repository.insert (new A5H*U ((str = "5H*U"))).first;
//     AtomType::a5H1 = *repository.insert (new A5H1 ((str = "5H1"))).first;
//     AtomType::a5H18 = *repository.insert (new A5H18 ((str = "5H18"))).first;
//     AtomType::a5H1N = *repository.insert (new A5H1N ((str = "5H1N"))).first;
//     AtomType::a5H2 = *repository.insert (new A5H2 ((str = "5H2"))).first;
//     AtomType::a5HA = *repository.insert (new A5HA ((str = "5HA"))).first;
//     AtomType::a5HB1 = *repository.insert (new A5HB1 ((str = "5HB1"))).first;
//     AtomType::a5HB2 = *repository.insert (new A5HB2 ((str = "5HB2"))).first;
//     AtomType::a5HC = *repository.insert (new A5HC ((str = "5HC"))).first;
//     AtomType::a5HC" = *repository.insert (new A5HC" ((str = "5HC""))).first;
//     AtomType::a5HC* = *repository.insert (new A5HC* ((str = "5HC*"))).first;
//     AtomType::a5HC1 = *repository.insert (new A5HC1 ((str = "5HC1"))).first;
//     AtomType::a5HC5 = *repository.insert (new A5HC5 ((str = "5HC5"))).first;
//     AtomType::a5HC8 = *repository.insert (new A5HC8 ((str = "5HC8"))).first;
//     AtomType::a5HCA = *repository.insert (new A5HCA ((str = "5HCA"))).first;
//     AtomType::a5HCN = *repository.insert (new A5HCN ((str = "5HCN"))).first;
//     AtomType::a5HE2 = *repository.insert (new A5HE2 ((str = "5HE2"))).first;
//     AtomType::a5HG1 = *repository.insert (new A5HG1 ((str = "5HG1"))).first;
//     AtomType::a5HG2 = *repository.insert (new A5HG2 ((str = "5HG2"))).first;
//     AtomType::a5HG5 = *repository.insert (new A5HG5 ((str = "5HG5"))).first;
//     AtomType::a5HN = *repository.insert (new A5HN ((str = "5HN"))).first;
//     AtomType::a5HN* = *repository.insert (new A5HN* ((str = "5HN*"))).first;
//     AtomType::a5HN4 = *repository.insert (new A5HN4 ((str = "5HN4"))).first;
//     AtomType::a5HN5 = *repository.insert (new A5HN5 ((str = "5HN5"))).first;
//     AtomType::a5HO = *repository.insert (new A5HO ((str = "5HO"))).first;
//     AtomType::a5HO* = *repository.insert (new A5HO* ((str = "5HO*"))).first;
//     AtomType::a5HO1 = *repository.insert (new A5HO1 ((str = "5HO1"))).first;
//     AtomType::a5HO2 = *repository.insert (new A5HO2 ((str = "5HO2"))).first;
//     AtomType::a5HO3 = *repository.insert (new A5HO3 ((str = "5HO3"))).first;
//     AtomType::a5HO4 = *repository.insert (new A5HO4 ((str = "5HO4"))).first;
//     AtomType::a5HO6 = *repository.insert (new A5HO6 ((str = "5HO6"))).first;
//     AtomType::a5HOA = *repository.insert (new A5HOA ((str = "5HOA"))).first;
//     AtomType::a5HOH = *repository.insert (new A5HOH ((str = "5HOH"))).first;
//     AtomType::a5HOP = *repository.insert (new A5HOP ((str = "5HOP"))).first;
//     AtomType::a5HOS = *repository.insert (new A5HOS ((str = "5HOS"))).first;
//     AtomType::a5HOU = *repository.insert (new A5HOU ((str = "5HOU"))).first;
//     AtomType::a5HXT = *repository.insert (new A5HXT ((str = "5HXT"))).first;
//     AtomType::a5N = *repository.insert (new A5N ((str = "5N"))).first;
//     AtomType::a5O = *repository.insert (new A5O ((str = "5O"))).first;
//     AtomType::a5O1 = *repository.insert (new A5O1 ((str = "5O1"))).first;
//     AtomType::a5O2 = *repository.insert (new A5O2 ((str = "5O2"))).first;
//     AtomType::a5O3 = *repository.insert (new A5O3 ((str = "5O3"))).first;
//     AtomType::a5O4 = *repository.insert (new A5O4 ((str = "5O4"))).first;
//     AtomType::a5OE1 = *repository.insert (new A5OE1 ((str = "5OE1"))).first;
//     AtomType::a5OE2 = *repository.insert (new A5OE2 ((str = "5OE2"))).first;
//     AtomType::a5OXT = *repository.insert (new A5OXT ((str = "5OXT"))).first;
//     AtomType::a6CKF = *repository.insert (new A6CKF ((str = "6CKF"))).first;
//     AtomType::a6CL1 = *repository.insert (new A6CL1 ((str = "6CL1"))).first;
//     AtomType::a6H = *repository.insert (new A6H ((str = "6H"))).first;
//     AtomType::a6H0 = *repository.insert (new A6H0 ((str = "6H0"))).first;
//     AtomType::a6H1 = *repository.insert (new A6H1 ((str = "6H1"))).first;
//     AtomType::a6H18 = *repository.insert (new A6H18 ((str = "6H18"))).first;
//     AtomType::a6HC = *repository.insert (new A6HC ((str = "6HC"))).first;
//     AtomType::a6HC" = *repository.insert (new A6HC" ((str = "6HC""))).first;
//     AtomType::a6HC1 = *repository.insert (new A6HC1 ((str = "6HC1"))).first;
//     AtomType::a6HC2 = *repository.insert (new A6HC2 ((str = "6HC2"))).first;
//     AtomType::a6HC3 = *repository.insert (new A6HC3 ((str = "6HC3"))).first;
//     AtomType::a6HC4 = *repository.insert (new A6HC4 ((str = "6HC4"))).first;
//     AtomType::a6HC9 = *repository.insert (new A6HC9 ((str = "6HC9"))).first;
//     AtomType::a6HCA = *repository.insert (new A6HCA ((str = "6HCA"))).first;
//     AtomType::a6HCN = *repository.insert (new A6HCN ((str = "6HCN"))).first;
//     AtomType::a6HG2 = *repository.insert (new A6HG2 ((str = "6HG2"))).first;
//     AtomType::a6HG5 = *repository.insert (new A6HG5 ((str = "6HG5"))).first;
//     AtomType::a6HN* = *repository.insert (new A6HN* ((str = "6HN*"))).first;
//     AtomType::a6HN8 = *repository.insert (new A6HN8 ((str = "6HN8"))).first;
//     AtomType::a6HNS = *repository.insert (new A6HNS ((str = "6HNS"))).first;
//     AtomType::a6HNT = *repository.insert (new A6HNT ((str = "6HNT"))).first;
//     AtomType::a6HO = *repository.insert (new A6HO ((str = "6HO"))).first;
//     AtomType::a6HO* = *repository.insert (new A6HO* ((str = "6HO*"))).first;
//     AtomType::a6HO1 = *repository.insert (new A6HO1 ((str = "6HO1"))).first;
//     AtomType::a6HO2 = *repository.insert (new A6HO2 ((str = "6HO2"))).first;
//     AtomType::a6HO3 = *repository.insert (new A6HO3 ((str = "6HO3"))).first;
//     AtomType::a6HO4 = *repository.insert (new A6HO4 ((str = "6HO4"))).first;
//     AtomType::a6HO6 = *repository.insert (new A6HO6 ((str = "6HO6"))).first;
//     AtomType::a6HOA = *repository.insert (new A6HOA ((str = "6HOA"))).first;
//     AtomType::a6HOB = *repository.insert (new A6HOB ((str = "6HOB"))).first;
//     AtomType::a6HOC = *repository.insert (new A6HOC ((str = "6HOC"))).first;
//     AtomType::a6HOD = *repository.insert (new A6HOD ((str = "6HOD"))).first;
//     AtomType::a6HOG = *repository.insert (new A6HOG ((str = "6HOG"))).first;
//     AtomType::a6HOP = *repository.insert (new A6HOP ((str = "6HOP"))).first;
//     AtomType::a6HOS = *repository.insert (new A6HOS ((str = "6HOS"))).first;
//     AtomType::a6O1 = *repository.insert (new A6O1 ((str = "6O1"))).first;
//     AtomType::a6O2 = *repository.insert (new A6O2 ((str = "6O2"))).first;
//     AtomType::a6O3 = *repository.insert (new A6O3 ((str = "6O3"))).first;
//     AtomType::a6O4 = *repository.insert (new A6O4 ((str = "6O4"))).first;
//     AtomType::a6OS = *repository.insert (new A6OS ((str = "6OS"))).first;
//     AtomType::a7H = *repository.insert (new A7H ((str = "7H"))).first;
//     AtomType::a7H2 = *repository.insert (new A7H2 ((str = "7H2"))).first;
//     AtomType::a7HC = *repository.insert (new A7HC ((str = "7HC"))).first;
//     AtomType::a7HC4 = *repository.insert (new A7HC4 ((str = "7HC4"))).first;
//     AtomType::a7HC6 = *repository.insert (new A7HC6 ((str = "7HC6"))).first;
//     AtomType::a7HCA = *repository.insert (new A7HCA ((str = "7HCA"))).first;
//     AtomType::a7HN = *repository.insert (new A7HN ((str = "7HN"))).first;
//     AtomType::a7HN7 = *repository.insert (new A7HN7 ((str = "7HN7"))).first;
//     AtomType::a7HO = *repository.insert (new A7HO ((str = "7HO"))).first;
//     AtomType::a7HO* = *repository.insert (new A7HO* ((str = "7HO*"))).first;
//     AtomType::a7HO1 = *repository.insert (new A7HO1 ((str = "7HO1"))).first;
//     AtomType::a7HO2 = *repository.insert (new A7HO2 ((str = "7HO2"))).first;
//     AtomType::a7HO3 = *repository.insert (new A7HO3 ((str = "7HO3"))).first;
//     AtomType::a7HO6 = *repository.insert (new A7HO6 ((str = "7HO6"))).first;
//     AtomType::a7HO7 = *repository.insert (new A7HO7 ((str = "7HO7"))).first;
//     AtomType::a7HO8 = *repository.insert (new A7HO8 ((str = "7HO8"))).first;
//     AtomType::a7HO9 = *repository.insert (new A7HO9 ((str = "7HO9"))).first;
//     AtomType::a7HOB = *repository.insert (new A7HOB ((str = "7HOB"))).first;
//     AtomType::a7HOM = *repository.insert (new A7HOM ((str = "7HOM"))).first;
//     AtomType::a7HON = *repository.insert (new A7HON ((str = "7HON"))).first;
//     AtomType::a7HOP = *repository.insert (new A7HOP ((str = "7HOP"))).first;
//     AtomType::a7HOR = *repository.insert (new A7HOR ((str = "7HOR"))).first;
//     AtomType::a8CL2 = *repository.insert (new A8CL2 ((str = "8CL2"))).first;
//     AtomType::a8H = *repository.insert (new A8H ((str = "8H"))).first;
//     AtomType::a8H1 = *repository.insert (new A8H1 ((str = "8H1"))).first;
//     AtomType::a8H2 = *repository.insert (new A8H2 ((str = "8H2"))).first;
//     AtomType::a8HC = *repository.insert (new A8HC ((str = "8HC"))).first;
//     AtomType::a8HCA = *repository.insert (new A8HCA ((str = "8HCA"))).first;
//     AtomType::a8HN = *repository.insert (new A8HN ((str = "8HN"))).first;
//     AtomType::a8HO = *repository.insert (new A8HO ((str = "8HO"))).first;
//     AtomType::a8HO* = *repository.insert (new A8HO* ((str = "8HO*"))).first;
//     AtomType::a8HO0 = *repository.insert (new A8HO0 ((str = "8HO0"))).first;
//     AtomType::a8HO1 = *repository.insert (new A8HO1 ((str = "8HO1"))).first;
//     AtomType::a8HOA = *repository.insert (new A8HOA ((str = "8HOA"))).first;
//     AtomType::a8HOB = *repository.insert (new A8HOB ((str = "8HOB"))).first;
//     AtomType::a8HOP = *repository.insert (new A8HOP ((str = "8HOP"))).first;
//     AtomType::a8HOR = *repository.insert (new A8HOR ((str = "8HOR"))).first;
//     AtomType::a9H = *repository.insert (new A9H ((str = "9H"))).first;
//     AtomType::a9H1 = *repository.insert (new A9H1 ((str = "9H1"))).first;
//     AtomType::a9H2 = *repository.insert (new A9H2 ((str = "9H2"))).first;
//     AtomType::a9H3 = *repository.insert (new A9H3 ((str = "9H3"))).first;
//     AtomType::a9HC = *repository.insert (new A9HC ((str = "9HC"))).first;
//     AtomType::a9HN = *repository.insert (new A9HN ((str = "9HN"))).first;
//     AtomType::a9HN1 = *repository.insert (new A9HN1 ((str = "9HN1"))).first;
//     AtomType::a9HNC = *repository.insert (new A9HNC ((str = "9HNC"))).first;
//     AtomType::a9HO" = *repository.insert (new A9HO" ((str = "9HO""))).first;
//     AtomType::a9HO* = *repository.insert (new A9HO* ((str = "9HO*"))).first;
//     AtomType::a9HOA = *repository.insert (new A9HOA ((str = "9HOA"))).first;
//     AtomType::a9HOB = *repository.insert (new A9HOB ((str = "9HOB"))).first;
//     AtomType::aAC1 = *repository.insert (new AAC1 ((str = "AC1"))).first;
//     AtomType::aAC1* = *repository.insert (new AAC1* ((str = "AC1*"))).first;
//     AtomType::aAC10 = *repository.insert (new AAC10 ((str = "AC10"))).first;
//     AtomType::aAC11 = *repository.insert (new AAC11 ((str = "AC11"))).first;
//     AtomType::aAC12 = *repository.insert (new AAC12 ((str = "AC12"))).first;
//     AtomType::aAC13 = *repository.insert (new AAC13 ((str = "AC13"))).first;
//     AtomType::aAC14 = *repository.insert (new AAC14 ((str = "AC14"))).first;
//     AtomType::aAC15 = *repository.insert (new AAC15 ((str = "AC15"))).first;
//     AtomType::aAC16 = *repository.insert (new AAC16 ((str = "AC16"))).first;
//     AtomType::aAC17 = *repository.insert (new AAC17 ((str = "AC17"))).first;
//     AtomType::aAC18 = *repository.insert (new AAC18 ((str = "AC18"))).first;
//     AtomType::aAC2 = *repository.insert (new AAC2 ((str = "AC2"))).first;
//     AtomType::aAC2* = *repository.insert (new AAC2* ((str = "AC2*"))).first;
//     AtomType::aAC3 = *repository.insert (new AAC3 ((str = "AC3"))).first;
//     AtomType::aAC3* = *repository.insert (new AAC3* ((str = "AC3*"))).first;
//     AtomType::aAC4 = *repository.insert (new AAC4 ((str = "AC4"))).first;
//     AtomType::aAC4* = *repository.insert (new AAC4* ((str = "AC4*"))).first;
//     AtomType::aAC4A = *repository.insert (new AAC4A ((str = "AC4A"))).first;
//     AtomType::aAC4B = *repository.insert (new AAC4B ((str = "AC4B"))).first;
//     AtomType::aAC5 = *repository.insert (new AAC5 ((str = "AC5"))).first;
//     AtomType::aAC5* = *repository.insert (new AAC5* ((str = "AC5*"))).first;
//     AtomType::aAC6 = *repository.insert (new AAC6 ((str = "AC6"))).first;
//     AtomType::aAC7 = *repository.insert (new AAC7 ((str = "AC7"))).first;
//     AtomType::aAC8 = *repository.insert (new AAC8 ((str = "AC8"))).first;
//     AtomType::aAC8A = *repository.insert (new AAC8A ((str = "AC8A"))).first;
//     AtomType::aAC8B = *repository.insert (new AAC8B ((str = "AC8B"))).first;
//     AtomType::aAC9 = *repository.insert (new AAC9 ((str = "AC9"))).first;
//     AtomType::aAD1 = *repository.insert (new AAD1 ((str = "AD1"))).first;
//     AtomType::aAD2 = *repository.insert (new AAD2 ((str = "AD2"))).first;
//     AtomType::aAE1 = *repository.insert (new AAE1 ((str = "AE1"))).first;
//     AtomType::aAE2 = *repository.insert (new AAE2 ((str = "AE2"))).first;
//     AtomType::aAH1 = *repository.insert (new AAH1 ((str = "AH1"))).first;
//     AtomType::aAH1* = *repository.insert (new AAH1* ((str = "AH1*"))).first;
//     AtomType::aAH10 = *repository.insert (new AAH10 ((str = "AH10"))).first;
//     AtomType::aAH12 = *repository.insert (new AAH12 ((str = "AH12"))).first;
//     AtomType::aAH15 = *repository.insert (new AAH15 ((str = "AH15"))).first;
//     AtomType::aAH16 = *repository.insert (new AAH16 ((str = "AH16"))).first;
//     AtomType::aAH2 = *repository.insert (new AAH2 ((str = "AH2"))).first;
//     AtomType::aAH2* = *repository.insert (new AAH2* ((str = "AH2*"))).first;
//     AtomType::aAH21 = *repository.insert (new AAH21 ((str = "AH21"))).first;
//     AtomType::aAH22 = *repository.insert (new AAH22 ((str = "AH22"))).first;
//     AtomType::aAH3 = *repository.insert (new AAH3 ((str = "AH3"))).first;
//     AtomType::aAH3* = *repository.insert (new AAH3* ((str = "AH3*"))).first;
//     AtomType::aAH4 = *repository.insert (new AAH4 ((str = "AH4"))).first;
//     AtomType::aAH4* = *repository.insert (new AAH4* ((str = "AH4*"))).first;
//     AtomType::aAH5 = *repository.insert (new AAH5 ((str = "AH5"))).first;
//     AtomType::aAH51 = *repository.insert (new AAH51 ((str = "AH51"))).first;
//     AtomType::aAH52 = *repository.insert (new AAH52 ((str = "AH52"))).first;
//     AtomType::aAH6 = *repository.insert (new AAH6 ((str = "AH6"))).first;
//     AtomType::aAH61 = *repository.insert (new AAH61 ((str = "AH61"))).first;
//     AtomType::aAH62 = *repository.insert (new AAH62 ((str = "AH62"))).first;
//     AtomType::aAH7 = *repository.insert (new AAH7 ((str = "AH7"))).first;
//     AtomType::aAH8 = *repository.insert (new AAH8 ((str = "AH8"))).first;
//     AtomType::aAH81 = *repository.insert (new AAH81 ((str = "AH81"))).first;
//     AtomType::aAH82 = *repository.insert (new AAH82 ((str = "AH82"))).first;
//     AtomType::aAH83 = *repository.insert (new AAH83 ((str = "AH83"))).first;
//     AtomType::aAH9 = *repository.insert (new AAH9 ((str = "AH9"))).first;
//     AtomType::aAHC = *repository.insert (new AAHC ((str = "AHC"))).first;
//     AtomType::aAHN2 = *repository.insert (new AAHN2 ((str = "AHN2"))).first;
//     AtomType::aAHO1 = *repository.insert (new AAHO1 ((str = "AHO1"))).first;
//     AtomType::aAHO2 = *repository.insert (new AAHO2 ((str = "AHO2"))).first;
//     AtomType::aAHO3 = *repository.insert (new AAHO3 ((str = "AHO3"))).first;
//     AtomType::aAHO4 = *repository.insert (new AAHO4 ((str = "AHO4"))).first;
//     AtomType::aAHO5 = *repository.insert (new AAHO5 ((str = "AHO5"))).first;
//     AtomType::aAHO6 = *repository.insert (new AAHO6 ((str = "AHO6"))).first;
//     AtomType::aAHO7 = *repository.insert (new AAHO7 ((str = "AHO7"))).first;
//     AtomType::aAHO8 = *repository.insert (new AAHO8 ((str = "AHO8"))).first;
//     AtomType::aAHS4 = *repository.insert (new AAHS4 ((str = "AHS4"))).first;
//     AtomType::aAL = *repository.insert (new AAL ((str = "AL"))).first;
//     AtomType::aAN1 = *repository.insert (new AAN1 ((str = "AN1"))).first;
//     AtomType::aAN10 = *repository.insert (new AAN10 ((str = "AN10"))).first;
//     AtomType::aAN2 = *repository.insert (new AAN2 ((str = "AN2"))).first;
//     AtomType::aAN3 = *repository.insert (new AAN3 ((str = "AN3"))).first;
//     AtomType::aAN6 = *repository.insert (new AAN6 ((str = "AN6"))).first;
//     AtomType::aAN7 = *repository.insert (new AAN7 ((str = "AN7"))).first;
//     AtomType::aAN9 = *repository.insert (new AAN9 ((str = "AN9"))).first;
//     AtomType::aAO1 = *repository.insert (new AAO1 ((str = "AO1"))).first;
//     AtomType::aAO1P = *repository.insert (new AAO1P ((str = "AO1P"))).first;
//     AtomType::aAO2 = *repository.insert (new AAO2 ((str = "AO2"))).first;
//     AtomType::aAO2* = *repository.insert (new AAO2* ((str = "AO2*"))).first;
//     AtomType::aAO2P = *repository.insert (new AAO2P ((str = "AO2P"))).first;
//     AtomType::aAO3 = *repository.insert (new AAO3 ((str = "AO3"))).first;
//     AtomType::aAO3* = *repository.insert (new AAO3* ((str = "AO3*"))).first;
//     AtomType::aAO4 = *repository.insert (new AAO4 ((str = "AO4"))).first;
//     AtomType::aAO4* = *repository.insert (new AAO4* ((str = "AO4*"))).first;
//     AtomType::aAO5 = *repository.insert (new AAO5 ((str = "AO5"))).first;
//     AtomType::aAO5* = *repository.insert (new AAO5* ((str = "AO5*"))).first;
//     AtomType::aAO6 = *repository.insert (new AAO6 ((str = "AO6"))).first;
//     AtomType::aAO7 = *repository.insert (new AAO7 ((str = "AO7"))).first;
//     AtomType::aAO7* = *repository.insert (new AAO7* ((str = "AO7*"))).first;
//     AtomType::aAO8 = *repository.insert (new AAO8 ((str = "AO8"))).first;
//     AtomType::aAO8* = *repository.insert (new AAO8* ((str = "AO8*"))).first;
//     AtomType::aAO9 = *repository.insert (new AAO9 ((str = "AO9"))).first;
//     AtomType::aAO9* = *repository.insert (new AAO9* ((str = "AO9*"))).first;
//     AtomType::aAOP1 = *repository.insert (new AAOP1 ((str = "AOP1"))).first;
//     AtomType::aAOP2 = *repository.insert (new AAOP2 ((str = "AOP2"))).first;
//     AtomType::aAOP3 = *repository.insert (new AAOP3 ((str = "AOP3"))).first;
//     AtomType::aAP = *repository.insert (new AAP ((str = "AP"))).first;
//     AtomType::aAP1 = *repository.insert (new AAP1 ((str = "AP1"))).first;
//     AtomType::aAP2 = *repository.insert (new AAP2 ((str = "AP2"))).first;
//     AtomType::aAP2* = *repository.insert (new AAP2* ((str = "AP2*"))).first;
//     AtomType::aAP3* = *repository.insert (new AAP3* ((str = "AP3*"))).first;
//     AtomType::aAS = *repository.insert (new AAS ((str = "AS"))).first;
//     AtomType::aAS1 = *repository.insert (new AAS1 ((str = "AS1"))).first;
//     AtomType::aAU = *repository.insert (new AAU ((str = "AU"))).first;
//     AtomType::aB = *repository.insert (new AB ((str = "B"))).first;
//     AtomType::aB07 = *repository.insert (new AB07 ((str = "B07"))).first;
//     AtomType::aB1 = *repository.insert (new AB1 ((str = "B1"))).first;
//     AtomType::aB10 = *repository.insert (new AB10 ((str = "B10"))).first;
//     AtomType::aB11 = *repository.insert (new AB11 ((str = "B11"))).first;
//     AtomType::aB12 = *repository.insert (new AB12 ((str = "B12"))).first;
//     AtomType::aB1A = *repository.insert (new AB1A ((str = "B1A"))).first;
//     AtomType::aB2 = *repository.insert (new AB2 ((str = "B2"))).first;
//     AtomType::aB24 = *repository.insert (new AB24 ((str = "B24"))).first;
//     AtomType::aB25 = *repository.insert (new AB25 ((str = "B25"))).first;
//     AtomType::aB26 = *repository.insert (new AB26 ((str = "B26"))).first;
//     AtomType::aB27 = *repository.insert (new AB27 ((str = "B27"))).first;
//     AtomType::aB28 = *repository.insert (new AB28 ((str = "B28"))).first;
//     AtomType::aB29 = *repository.insert (new AB29 ((str = "B29"))).first;
//     AtomType::aB30 = *repository.insert (new AB30 ((str = "B30"))).first;
//     AtomType::aB31 = *repository.insert (new AB31 ((str = "B31"))).first;
//     AtomType::aB32 = *repository.insert (new AB32 ((str = "B32"))).first;
//     AtomType::aB4 = *repository.insert (new AB4 ((str = "B4"))).first;
//     AtomType::aB5 = *repository.insert (new AB5 ((str = "B5"))).first;
//     AtomType::aB6 = *repository.insert (new AB6 ((str = "B6"))).first;
//     AtomType::aB7 = *repository.insert (new AB7 ((str = "B7"))).first;
//     AtomType::aB8 = *repository.insert (new AB8 ((str = "B8"))).first;
//     AtomType::aB9 = *repository.insert (new AB9 ((str = "B9"))).first;
//     AtomType::aBC = *repository.insert (new ABC ((str = "BC"))).first;
//     AtomType::aBC1 = *repository.insert (new ABC1 ((str = "BC1"))).first;
//     AtomType::aBC1* = *repository.insert (new ABC1* ((str = "BC1*"))).first;
//     AtomType::aBC10 = *repository.insert (new ABC10 ((str = "BC10"))).first;
//     AtomType::aBC11 = *repository.insert (new ABC11 ((str = "BC11"))).first;
//     AtomType::aBC12 = *repository.insert (new ABC12 ((str = "BC12"))).first;
//     AtomType::aBC13 = *repository.insert (new ABC13 ((str = "BC13"))).first;
//     AtomType::aBC14 = *repository.insert (new ABC14 ((str = "BC14"))).first;
//     AtomType::aBC15 = *repository.insert (new ABC15 ((str = "BC15"))).first;
//     AtomType::aBC16 = *repository.insert (new ABC16 ((str = "BC16"))).first;
//     AtomType::aBC17 = *repository.insert (new ABC17 ((str = "BC17"))).first;
//     AtomType::aBC18 = *repository.insert (new ABC18 ((str = "BC18"))).first;
//     AtomType::aBC2 = *repository.insert (new ABC2 ((str = "BC2"))).first;
//     AtomType::aBC2* = *repository.insert (new ABC2* ((str = "BC2*"))).first;
//     AtomType::aBC3 = *repository.insert (new ABC3 ((str = "BC3"))).first;
//     AtomType::aBC3* = *repository.insert (new ABC3* ((str = "BC3*"))).first;
//     AtomType::aBC4 = *repository.insert (new ABC4 ((str = "BC4"))).first;
//     AtomType::aBC4* = *repository.insert (new ABC4* ((str = "BC4*"))).first;
//     AtomType::aBC5 = *repository.insert (new ABC5 ((str = "BC5"))).first;
//     AtomType::aBC5* = *repository.insert (new ABC5* ((str = "BC5*"))).first;
//     AtomType::aBC6 = *repository.insert (new ABC6 ((str = "BC6"))).first;
//     AtomType::aBC7 = *repository.insert (new ABC7 ((str = "BC7"))).first;
//     AtomType::aBC8 = *repository.insert (new ABC8 ((str = "BC8"))).first;
//     AtomType::aBC9 = *repository.insert (new ABC9 ((str = "BC9"))).first;
//     AtomType::aBD = *repository.insert (new ABD ((str = "BD"))).first;
//     AtomType::aBE = *repository.insert (new ABE ((str = "BE"))).first;
//     AtomType::aBH1 = *repository.insert (new ABH1 ((str = "BH1"))).first;
//     AtomType::aBH1* = *repository.insert (new ABH1* ((str = "BH1*"))).first;
//     AtomType::aBH12 = *repository.insert (new ABH12 ((str = "BH12"))).first;
//     AtomType::aBH15 = *repository.insert (new ABH15 ((str = "BH15"))).first;
//     AtomType::aBH16 = *repository.insert (new ABH16 ((str = "BH16"))).first;
//     AtomType::aBH2 = *repository.insert (new ABH2 ((str = "BH2"))).first;
//     AtomType::aBH2* = *repository.insert (new ABH2* ((str = "BH2*"))).first;
//     AtomType::aBH21 = *repository.insert (new ABH21 ((str = "BH21"))).first;
//     AtomType::aBH22 = *repository.insert (new ABH22 ((str = "BH22"))).first;
//     AtomType::aBH3 = *repository.insert (new ABH3 ((str = "BH3"))).first;
//     AtomType::aBH3* = *repository.insert (new ABH3* ((str = "BH3*"))).first;
//     AtomType::aBH4 = *repository.insert (new ABH4 ((str = "BH4"))).first;
//     AtomType::aBH4* = *repository.insert (new ABH4* ((str = "BH4*"))).first;
//     AtomType::aBH5 = *repository.insert (new ABH5 ((str = "BH5"))).first;
//     AtomType::aBH51 = *repository.insert (new ABH51 ((str = "BH51"))).first;
//     AtomType::aBH52 = *repository.insert (new ABH52 ((str = "BH52"))).first;
//     AtomType::aBH6 = *repository.insert (new ABH6 ((str = "BH6"))).first;
//     AtomType::aBH61 = *repository.insert (new ABH61 ((str = "BH61"))).first;
//     AtomType::aBH62 = *repository.insert (new ABH62 ((str = "BH62"))).first;
//     AtomType::aBH7 = *repository.insert (new ABH7 ((str = "BH7"))).first;
//     AtomType::aBH8 = *repository.insert (new ABH8 ((str = "BH8"))).first;
//     AtomType::aBH81 = *repository.insert (new ABH81 ((str = "BH81"))).first;
//     AtomType::aBH82 = *repository.insert (new ABH82 ((str = "BH82"))).first;
//     AtomType::aBH83 = *repository.insert (new ABH83 ((str = "BH83"))).first;
//     AtomType::aBH9 = *repository.insert (new ABH9 ((str = "BH9"))).first;
//     AtomType::aBHC = *repository.insert (new ABHC ((str = "BHC"))).first;
//     AtomType::aBHN2 = *repository.insert (new ABHN2 ((str = "BHN2"))).first;
//     AtomType::aBHO1 = *repository.insert (new ABHO1 ((str = "BHO1"))).first;
//     AtomType::aBHO2 = *repository.insert (new ABHO2 ((str = "BHO2"))).first;
//     AtomType::aBHO3 = *repository.insert (new ABHO3 ((str = "BHO3"))).first;
//     AtomType::aBHO4 = *repository.insert (new ABHO4 ((str = "BHO4"))).first;
//     AtomType::aBHO6 = *repository.insert (new ABHO6 ((str = "BHO6"))).first;
//     AtomType::aBHOC = *repository.insert (new ABHOC ((str = "BHOC"))).first;
//     AtomType::aBN1 = *repository.insert (new ABN1 ((str = "BN1"))).first;
//     AtomType::aBN10 = *repository.insert (new ABN10 ((str = "BN10"))).first;
//     AtomType::aBN2 = *repository.insert (new ABN2 ((str = "BN2"))).first;
//     AtomType::aBN3 = *repository.insert (new ABN3 ((str = "BN3"))).first;
//     AtomType::aBN6 = *repository.insert (new ABN6 ((str = "BN6"))).first;
//     AtomType::aBN7 = *repository.insert (new ABN7 ((str = "BN7"))).first;
//     AtomType::aBN9 = *repository.insert (new ABN9 ((str = "BN9"))).first;
//     AtomType::aBO1 = *repository.insert (new ABO1 ((str = "BO1"))).first;
//     AtomType::aBO2 = *repository.insert (new ABO2 ((str = "BO2"))).first;
//     AtomType::aBO2* = *repository.insert (new ABO2* ((str = "BO2*"))).first;
//     AtomType::aBO3 = *repository.insert (new ABO3 ((str = "BO3"))).first;
//     AtomType::aBO3* = *repository.insert (new ABO3* ((str = "BO3*"))).first;
//     AtomType::aBO4 = *repository.insert (new ABO4 ((str = "BO4"))).first;
//     AtomType::aBO4* = *repository.insert (new ABO4* ((str = "BO4*"))).first;
//     AtomType::aBO5 = *repository.insert (new ABO5 ((str = "BO5"))).first;
//     AtomType::aBO5* = *repository.insert (new ABO5* ((str = "BO5*"))).first;
//     AtomType::aBO6 = *repository.insert (new ABO6 ((str = "BO6"))).first;
//     AtomType::aBO7 = *repository.insert (new ABO7 ((str = "BO7"))).first;
//     AtomType::aBR = *repository.insert (new ABR ((str = "BR"))).first;
//     AtomType::aBR1 = *repository.insert (new ABR1 ((str = "BR1"))).first;
//     AtomType::aBR10 = *repository.insert (new ABR10 ((str = "BR10"))).first;
//     AtomType::aBR11 = *repository.insert (new ABR11 ((str = "BR11"))).first;
//     AtomType::aBR12 = *repository.insert (new ABR12 ((str = "BR12"))).first;
//     AtomType::aBR13 = *repository.insert (new ABR13 ((str = "BR13"))).first;
//     AtomType::aBR17 = *repository.insert (new ABR17 ((str = "BR17"))).first;
//     AtomType::aBR19 = *repository.insert (new ABR19 ((str = "BR19"))).first;
//     AtomType::aBR2 = *repository.insert (new ABR2 ((str = "BR2"))).first;
//     AtomType::aBR21 = *repository.insert (new ABR21 ((str = "BR21"))).first;
//     AtomType::aBR22 = *repository.insert (new ABR22 ((str = "BR22"))).first;
//     AtomType::aBR23 = *repository.insert (new ABR23 ((str = "BR23"))).first;
//     AtomType::aBR24 = *repository.insert (new ABR24 ((str = "BR24"))).first;
//     AtomType::aBR25 = *repository.insert (new ABR25 ((str = "BR25"))).first;
//     AtomType::aBR26 = *repository.insert (new ABR26 ((str = "BR26"))).first;
//     AtomType::aBR27 = *repository.insert (new ABR27 ((str = "BR27"))).first;
//     AtomType::aBR28 = *repository.insert (new ABR28 ((str = "BR28"))).first;
//     AtomType::aBR29 = *repository.insert (new ABR29 ((str = "BR29"))).first;
//     AtomType::aBR3 = *repository.insert (new ABR3 ((str = "BR3"))).first;
//     AtomType::aBR36 = *repository.insert (new ABR36 ((str = "BR36"))).first;
//     AtomType::aBR37 = *repository.insert (new ABR37 ((str = "BR37"))).first;
//     AtomType::aBR38 = *repository.insert (new ABR38 ((str = "BR38"))).first;
//     AtomType::aBR4 = *repository.insert (new ABR4 ((str = "BR4"))).first;
//     AtomType::aBR4* = *repository.insert (new ABR4* ((str = "BR4*"))).first;
//     AtomType::aBR41 = *repository.insert (new ABR41 ((str = "BR41"))).first;
//     AtomType::aBR43 = *repository.insert (new ABR43 ((str = "BR43"))).first;
//     AtomType::aBR5 = *repository.insert (new ABR5 ((str = "BR5"))).first;
//     AtomType::aBR5* = *repository.insert (new ABR5* ((str = "BR5*"))).first;
//     AtomType::aBR53 = *repository.insert (new ABR53 ((str = "BR53"))).first;
//     AtomType::aBR6 = *repository.insert (new ABR6 ((str = "BR6"))).first;
//     AtomType::aBR7 = *repository.insert (new ABR7 ((str = "BR7"))).first;
//     AtomType::aBR8 = *repository.insert (new ABR8 ((str = "BR8"))).first;
//     AtomType::aBR9 = *repository.insert (new ABR9 ((str = "BR9"))).first;
//     AtomType::aBRA = *repository.insert (new ABRA ((str = "BRA"))).first;
//     AtomType::aBRA2 = *repository.insert (new ABRA2 ((str = "BRA2"))).first;
//     AtomType::aBRAH = *repository.insert (new ABRAH ((str = "BRAH"))).first;
//     AtomType::aBRAI = *repository.insert (new ABRAI ((str = "BRAI"))).first;
//     AtomType::aBRB = *repository.insert (new ABRB ((str = "BRB"))).first;
//     AtomType::aBRC = *repository.insert (new ABRC ((str = "BRC"))).first;
//     AtomType::aC = *repository.insert (new AC ((str = "C"))).first;
//     AtomType::aC" = *repository.insert (new AC" ((str = "C""))).first;
//     AtomType::aC* = *repository.insert (new AC* ((str = "C*"))).first;
//     AtomType::aC*0 = *repository.insert (new AC*0 ((str = "C*0"))).first;
//     AtomType::aC*1 = *repository.insert (new AC*1 ((str = "C*1"))).first;
//     AtomType::aC*10 = *repository.insert (new AC*10 ((str = "C*10"))).first;
//     AtomType::aC*11 = *repository.insert (new AC*11 ((str = "C*11"))).first;
//     AtomType::aC*12 = *repository.insert (new AC*12 ((str = "C*12"))).first;
//     AtomType::aC*2 = *repository.insert (new AC*2 ((str = "C*2"))).first;
//     AtomType::aC*3 = *repository.insert (new AC*3 ((str = "C*3"))).first;
//     AtomType::aC*4 = *repository.insert (new AC*4 ((str = "C*4"))).first;
//     AtomType::aC*5 = *repository.insert (new AC*5 ((str = "C*5"))).first;
//     AtomType::aC*6 = *repository.insert (new AC*6 ((str = "C*6"))).first;
//     AtomType::aC*7 = *repository.insert (new AC*7 ((str = "C*7"))).first;
//     AtomType::aC*7A = *repository.insert (new AC*7A ((str = "C*7A"))).first;
//     AtomType::aC*8 = *repository.insert (new AC*8 ((str = "C*8"))).first;
//     AtomType::aC*9 = *repository.insert (new AC*9 ((str = "C*9"))).first;
//     AtomType::aC0 = *repository.insert (new AC0 ((str = "C0"))).first;
//     AtomType::aC0* = *repository.insert (new AC0* ((str = "C0*"))).first;
//     AtomType::aC01 = *repository.insert (new AC01 ((str = "C01"))).first;
//     AtomType::aC02 = *repository.insert (new AC02 ((str = "C02"))).first;
//     AtomType::aC03 = *repository.insert (new AC03 ((str = "C03"))).first;
//     AtomType::aC04 = *repository.insert (new AC04 ((str = "C04"))).first;
//     AtomType::aC05 = *repository.insert (new AC05 ((str = "C05"))).first;
//     AtomType::aC06 = *repository.insert (new AC06 ((str = "C06"))).first;
//     AtomType::aC07 = *repository.insert (new AC07 ((str = "C07"))).first;
//     AtomType::aC08 = *repository.insert (new AC08 ((str = "C08"))).first;
//     AtomType::aC09 = *repository.insert (new AC09 ((str = "C09"))).first;
//     AtomType::aC0A = *repository.insert (new AC0A ((str = "C0A"))).first;
//     AtomType::aC0B = *repository.insert (new AC0B ((str = "C0B"))).first;
//     AtomType::aC0C = *repository.insert (new AC0C ((str = "C0C"))).first;
//     AtomType::aC0D = *repository.insert (new AC0D ((str = "C0D"))).first;
//     AtomType::aC0E = *repository.insert (new AC0E ((str = "C0E"))).first;
//     AtomType::aC0F = *repository.insert (new AC0F ((str = "C0F"))).first;
//     AtomType::aC0G = *repository.insert (new AC0G ((str = "C0G"))).first;
//     AtomType::aC0I = *repository.insert (new AC0I ((str = "C0I"))).first;
//     AtomType::aC0J = *repository.insert (new AC0J ((str = "C0J"))).first;
//     AtomType::aC0K = *repository.insert (new AC0K ((str = "C0K"))).first;
//     AtomType::aC0L = *repository.insert (new AC0L ((str = "C0L"))).first;
//     AtomType::aC0N = *repository.insert (new AC0N ((str = "C0N"))).first;
//     AtomType::aC0P = *repository.insert (new AC0P ((str = "C0P"))).first;
//     AtomType::aC0Q = *repository.insert (new AC0Q ((str = "C0Q"))).first;
//     AtomType::aC0R = *repository.insert (new AC0R ((str = "C0R"))).first;
//     AtomType::aC0S = *repository.insert (new AC0S ((str = "C0S"))).first;
//     AtomType::aC0T = *repository.insert (new AC0T ((str = "C0T"))).first;
//     AtomType::aC0X = *repository.insert (new AC0X ((str = "C0X"))).first;
//     AtomType::aC1 = *repository.insert (new AC1 ((str = "C1"))).first;
//     AtomType::aC1" = *repository.insert (new AC1" ((str = "C1""))).first;
//     AtomType::aC1* = *repository.insert (new AC1* ((str = "C1*"))).first;
//     AtomType::aC1** = *repository.insert (new AC1** ((str = "C1**"))).first;
//     AtomType::aC1*A = *repository.insert (new AC1*A ((str = "C1*A"))).first;
//     AtomType::aC1*B = *repository.insert (new AC1*B ((str = "C1*B"))).first;
//     AtomType::aC1*G = *repository.insert (new AC1*G ((str = "C1*G"))).first;
//     AtomType::aC1*N = *repository.insert (new AC1*N ((str = "C1*N"))).first;
//     AtomType::aC1*U = *repository.insert (new AC1*U ((str = "C1*U"))).first;
//     AtomType::aC1, = *repository.insert (new AC1, ((str = "C1,"))).first;
//     AtomType::aC10 = *repository.insert (new AC10 ((str = "C10"))).first;
//     AtomType::aC10* = *repository.insert (new AC10* ((str = "C10*"))).first;
//     AtomType::aC102 = *repository.insert (new AC102 ((str = "C102"))).first;
//     AtomType::aC10A = *repository.insert (new AC10A ((str = "C10A"))).first;
//     AtomType::aC10B = *repository.insert (new AC10B ((str = "C10B"))).first;
//     AtomType::aC10P = *repository.insert (new AC10P ((str = "C10P"))).first;
//     AtomType::aC11 = *repository.insert (new AC11 ((str = "C11"))).first;
//     AtomType::aC11* = *repository.insert (new AC11* ((str = "C11*"))).first;
//     AtomType::aC110 = *repository.insert (new AC110 ((str = "C110"))).first;
//     AtomType::aC11A = *repository.insert (new AC11A ((str = "C11A"))).first;
//     AtomType::aC11B = *repository.insert (new AC11B ((str = "C11B"))).first;
//     AtomType::aC11P = *repository.insert (new AC11P ((str = "C11P"))).first;
//     AtomType::aC12 = *repository.insert (new AC12 ((str = "C12"))).first;
//     AtomType::aC12* = *repository.insert (new AC12* ((str = "C12*"))).first;
//     AtomType::aC12A = *repository.insert (new AC12A ((str = "C12A"))).first;
//     AtomType::aC12B = *repository.insert (new AC12B ((str = "C12B"))).first;
//     AtomType::aC12P = *repository.insert (new AC12P ((str = "C12P"))).first;
//     AtomType::aC13 = *repository.insert (new AC13 ((str = "C13"))).first;
//     AtomType::aC13* = *repository.insert (new AC13* ((str = "C13*"))).first;
//     AtomType::aC13A = *repository.insert (new AC13A ((str = "C13A"))).first;
//     AtomType::aC13B = *repository.insert (new AC13B ((str = "C13B"))).first;
//     AtomType::aC13P = *repository.insert (new AC13P ((str = "C13P"))).first;
//     AtomType::aC14 = *repository.insert (new AC14 ((str = "C14"))).first;
//     AtomType::aC14* = *repository.insert (new AC14* ((str = "C14*"))).first;
//     AtomType::aC14A = *repository.insert (new AC14A ((str = "C14A"))).first;
//     AtomType::aC14B = *repository.insert (new AC14B ((str = "C14B"))).first;
//     AtomType::aC14C = *repository.insert (new AC14C ((str = "C14C"))).first;
//     AtomType::aC14P = *repository.insert (new AC14P ((str = "C14P"))).first;
//     AtomType::aC15 = *repository.insert (new AC15 ((str = "C15"))).first;
//     AtomType::aC15* = *repository.insert (new AC15* ((str = "C15*"))).first;
//     AtomType::aC15B = *repository.insert (new AC15B ((str = "C15B"))).first;
//     AtomType::aC15P = *repository.insert (new AC15P ((str = "C15P"))).first;
//     AtomType::aC16 = *repository.insert (new AC16 ((str = "C16"))).first;
//     AtomType::aC16* = *repository.insert (new AC16* ((str = "C16*"))).first;
//     AtomType::aC16B = *repository.insert (new AC16B ((str = "C16B"))).first;
//     AtomType::aC16P = *repository.insert (new AC16P ((str = "C16P"))).first;
//     AtomType::aC17 = *repository.insert (new AC17 ((str = "C17"))).first;
//     AtomType::aC17* = *repository.insert (new AC17* ((str = "C17*"))).first;
//     AtomType::aC18 = *repository.insert (new AC18 ((str = "C18"))).first;
//     AtomType::aC18* = *repository.insert (new AC18* ((str = "C18*"))).first;
//     AtomType::aC19 = *repository.insert (new AC19 ((str = "C19"))).first;
//     AtomType::aC19* = *repository.insert (new AC19* ((str = "C19*"))).first;
//     AtomType::aC1A = *repository.insert (new AC1A ((str = "C1A"))).first;
//     AtomType::aC1B = *repository.insert (new AC1B ((str = "C1B"))).first;
//     AtomType::aC1C = *repository.insert (new AC1C ((str = "C1C"))).first;
//     AtomType::aC1D = *repository.insert (new AC1D ((str = "C1D"))).first;
//     AtomType::aC1E = *repository.insert (new AC1E ((str = "C1E"))).first;
//     AtomType::aC1F = *repository.insert (new AC1F ((str = "C1F"))).first;
//     AtomType::aC1G = *repository.insert (new AC1G ((str = "C1G"))).first;
//     AtomType::aC1H = *repository.insert (new AC1H ((str = "C1H"))).first;
//     AtomType::aC1I = *repository.insert (new AC1I ((str = "C1I"))).first;
//     AtomType::aC1J = *repository.insert (new AC1J ((str = "C1J"))).first;
//     AtomType::aC1K = *repository.insert (new AC1K ((str = "C1K"))).first;
//     AtomType::aC1L = *repository.insert (new AC1L ((str = "C1L"))).first;
//     AtomType::aC1M = *repository.insert (new AC1M ((str = "C1M"))).first;
//     AtomType::aC1N = *repository.insert (new AC1N ((str = "C1N"))).first;
//     AtomType::aC1O = *repository.insert (new AC1O ((str = "C1O"))).first;
//     AtomType::aC1P = *repository.insert (new AC1P ((str = "C1P"))).first;
//     AtomType::aC1Q = *repository.insert (new AC1Q ((str = "C1Q"))).first;
//     AtomType::aC1R = *repository.insert (new AC1R ((str = "C1R"))).first;
//     AtomType::aC1S = *repository.insert (new AC1S ((str = "C1S"))).first;
//     AtomType::aC1T = *repository.insert (new AC1T ((str = "C1T"))).first;
//     AtomType::aC1U = *repository.insert (new AC1U ((str = "C1U"))).first;
//     AtomType::aC1V = *repository.insert (new AC1V ((str = "C1V"))).first;
//     AtomType::aC1W = *repository.insert (new AC1W ((str = "C1W"))).first;
//     AtomType::aC1X = *repository.insert (new AC1X ((str = "C1X"))).first;
//     AtomType::aC1Y = *repository.insert (new AC1Y ((str = "C1Y"))).first;
//     AtomType::aC1Z = *repository.insert (new AC1Z ((str = "C1Z"))).first;
//     AtomType::aC2 = *repository.insert (new AC2 ((str = "C2"))).first;
//     AtomType::aC2" = *repository.insert (new AC2" ((str = "C2""))).first;
//     AtomType::aC2* = *repository.insert (new AC2* ((str = "C2*"))).first;
//     AtomType::aC2** = *repository.insert (new AC2** ((str = "C2**"))).first;
//     AtomType::aC2*A = *repository.insert (new AC2*A ((str = "C2*A"))).first;
//     AtomType::aC2*B = *repository.insert (new AC2*B ((str = "C2*B"))).first;
//     AtomType::aC2*G = *repository.insert (new AC2*G ((str = "C2*G"))).first;
//     AtomType::aC2*N = *repository.insert (new AC2*N ((str = "C2*N"))).first;
//     AtomType::aC2*U = *repository.insert (new AC2*U ((str = "C2*U"))).first;
//     AtomType::aC2, = *repository.insert (new AC2, ((str = "C2,"))).first;
//     AtomType::aC20 = *repository.insert (new AC20 ((str = "C20"))).first;
//     AtomType::aC20* = *repository.insert (new AC20* ((str = "C20*"))).first;
//     AtomType::aC21 = *repository.insert (new AC21 ((str = "C21"))).first;
//     AtomType::aC21* = *repository.insert (new AC21* ((str = "C21*"))).first;
//     AtomType::aC22 = *repository.insert (new AC22 ((str = "C22"))).first;
//     AtomType::aC22* = *repository.insert (new AC22* ((str = "C22*"))).first;
//     AtomType::aC23 = *repository.insert (new AC23 ((str = "C23"))).first;
//     AtomType::aC23* = *repository.insert (new AC23* ((str = "C23*"))).first;
//     AtomType::aC24 = *repository.insert (new AC24 ((str = "C24"))).first;
//     AtomType::aC24* = *repository.insert (new AC24* ((str = "C24*"))).first;
//     AtomType::aC25 = *repository.insert (new AC25 ((str = "C25"))).first;
//     AtomType::aC25* = *repository.insert (new AC25* ((str = "C25*"))).first;
//     AtomType::aC26 = *repository.insert (new AC26 ((str = "C26"))).first;
//     AtomType::aC26* = *repository.insert (new AC26* ((str = "C26*"))).first;
//     AtomType::aC27 = *repository.insert (new AC27 ((str = "C27"))).first;
//     AtomType::aC27* = *repository.insert (new AC27* ((str = "C27*"))).first;
//     AtomType::aC28 = *repository.insert (new AC28 ((str = "C28"))).first;
//     AtomType::aC29 = *repository.insert (new AC29 ((str = "C29"))).first;
//     AtomType::aC2A = *repository.insert (new AC2A ((str = "C2A"))).first;
//     AtomType::aC2A* = *repository.insert (new AC2A* ((str = "C2A*"))).first;
//     AtomType::aC2B = *repository.insert (new AC2B ((str = "C2B"))).first;
//     AtomType::aC2C = *repository.insert (new AC2C ((str = "C2C"))).first;
//     AtomType::aC2D = *repository.insert (new AC2D ((str = "C2D"))).first;
//     AtomType::aC2E = *repository.insert (new AC2E ((str = "C2E"))).first;
//     AtomType::aC2F = *repository.insert (new AC2F ((str = "C2F"))).first;
//     AtomType::aC2G = *repository.insert (new AC2G ((str = "C2G"))).first;
//     AtomType::aC2H = *repository.insert (new AC2H ((str = "C2H"))).first;
//     AtomType::aC2I = *repository.insert (new AC2I ((str = "C2I"))).first;
//     AtomType::aC2J = *repository.insert (new AC2J ((str = "C2J"))).first;
//     AtomType::aC2K = *repository.insert (new AC2K ((str = "C2K"))).first;
//     AtomType::aC2L = *repository.insert (new AC2L ((str = "C2L"))).first;
//     AtomType::aC2M = *repository.insert (new AC2M ((str = "C2M"))).first;
//     AtomType::aC2N = *repository.insert (new AC2N ((str = "C2N"))).first;
//     AtomType::aC2P = *repository.insert (new AC2P ((str = "C2P"))).first;
//     AtomType::aC2Q = *repository.insert (new AC2Q ((str = "C2Q"))).first;
//     AtomType::aC2R = *repository.insert (new AC2R ((str = "C2R"))).first;
//     AtomType::aC2S = *repository.insert (new AC2S ((str = "C2S"))).first;
//     AtomType::aC2T = *repository.insert (new AC2T ((str = "C2T"))).first;
//     AtomType::aC2U = *repository.insert (new AC2U ((str = "C2U"))).first;
//     AtomType::aC2V = *repository.insert (new AC2V ((str = "C2V"))).first;
//     AtomType::aC2W = *repository.insert (new AC2W ((str = "C2W"))).first;
//     AtomType::aC2X = *repository.insert (new AC2X ((str = "C2X"))).first;
//     AtomType::aC2Y = *repository.insert (new AC2Y ((str = "C2Y"))).first;
//     AtomType::aC2Z = *repository.insert (new AC2Z ((str = "C2Z"))).first;
//     AtomType::aC3 = *repository.insert (new AC3 ((str = "C3"))).first;
//     AtomType::aC3" = *repository.insert (new AC3" ((str = "C3""))).first;
//     AtomType::aC3* = *repository.insert (new AC3* ((str = "C3*"))).first;
//     AtomType::aC3** = *repository.insert (new AC3** ((str = "C3**"))).first;
//     AtomType::aC3*A = *repository.insert (new AC3*A ((str = "C3*A"))).first;
//     AtomType::aC3*B = *repository.insert (new AC3*B ((str = "C3*B"))).first;
//     AtomType::aC3*G = *repository.insert (new AC3*G ((str = "C3*G"))).first;
//     AtomType::aC3*N = *repository.insert (new AC3*N ((str = "C3*N"))).first;
//     AtomType::aC3*U = *repository.insert (new AC3*U ((str = "C3*U"))).first;
//     AtomType::aC3, = *repository.insert (new AC3, ((str = "C3,"))).first;
//     AtomType::aC30 = *repository.insert (new AC30 ((str = "C30"))).first;
//     AtomType::aC31 = *repository.insert (new AC31 ((str = "C31"))).first;
//     AtomType::aC31* = *repository.insert (new AC31* ((str = "C31*"))).first;
//     AtomType::aC32 = *repository.insert (new AC32 ((str = "C32"))).first;
//     AtomType::aC32* = *repository.insert (new AC32* ((str = "C32*"))).first;
//     AtomType::aC33 = *repository.insert (new AC33 ((str = "C33"))).first;
//     AtomType::aC34 = *repository.insert (new AC34 ((str = "C34"))).first;
//     AtomType::aC35 = *repository.insert (new AC35 ((str = "C35"))).first;
//     AtomType::aC36 = *repository.insert (new AC36 ((str = "C36"))).first;
//     AtomType::aC37 = *repository.insert (new AC37 ((str = "C37"))).first;
//     AtomType::aC38 = *repository.insert (new AC38 ((str = "C38"))).first;
//     AtomType::aC39 = *repository.insert (new AC39 ((str = "C39"))).first;
//     AtomType::aC3A = *repository.insert (new AC3A ((str = "C3A"))).first;
//     AtomType::aC3B = *repository.insert (new AC3B ((str = "C3B"))).first;
//     AtomType::aC3C = *repository.insert (new AC3C ((str = "C3C"))).first;
//     AtomType::aC3D = *repository.insert (new AC3D ((str = "C3D"))).first;
//     AtomType::aC3E = *repository.insert (new AC3E ((str = "C3E"))).first;
//     AtomType::aC3F = *repository.insert (new AC3F ((str = "C3F"))).first;
//     AtomType::aC3G = *repository.insert (new AC3G ((str = "C3G"))).first;
//     AtomType::aC3H = *repository.insert (new AC3H ((str = "C3H"))).first;
//     AtomType::aC3I = *repository.insert (new AC3I ((str = "C3I"))).first;
//     AtomType::aC3J = *repository.insert (new AC3J ((str = "C3J"))).first;
//     AtomType::aC3K = *repository.insert (new AC3K ((str = "C3K"))).first;
//     AtomType::aC3L = *repository.insert (new AC3L ((str = "C3L"))).first;
//     AtomType::aC3M = *repository.insert (new AC3M ((str = "C3M"))).first;
//     AtomType::aC3N = *repository.insert (new AC3N ((str = "C3N"))).first;
//     AtomType::aC3P = *repository.insert (new AC3P ((str = "C3P"))).first;
//     AtomType::aC3Q = *repository.insert (new AC3Q ((str = "C3Q"))).first;
//     AtomType::aC3R = *repository.insert (new AC3R ((str = "C3R"))).first;
//     AtomType::aC3S = *repository.insert (new AC3S ((str = "C3S"))).first;
//     AtomType::aC3T = *repository.insert (new AC3T ((str = "C3T"))).first;
//     AtomType::aC3U = *repository.insert (new AC3U ((str = "C3U"))).first;
//     AtomType::aC3W = *repository.insert (new AC3W ((str = "C3W"))).first;
//     AtomType::aC3X = *repository.insert (new AC3X ((str = "C3X"))).first;
//     AtomType::aC3Y = *repository.insert (new AC3Y ((str = "C3Y"))).first;
//     AtomType::aC3Z = *repository.insert (new AC3Z ((str = "C3Z"))).first;
//     AtomType::aC4 = *repository.insert (new AC4 ((str = "C4"))).first;
//     AtomType::aC4" = *repository.insert (new AC4" ((str = "C4""))).first;
//     AtomType::aC4* = *repository.insert (new AC4* ((str = "C4*"))).first;
//     AtomType::aC4** = *repository.insert (new AC4** ((str = "C4**"))).first;
//     AtomType::aC4*A = *repository.insert (new AC4*A ((str = "C4*A"))).first;
//     AtomType::aC4*B = *repository.insert (new AC4*B ((str = "C4*B"))).first;
//     AtomType::aC4*G = *repository.insert (new AC4*G ((str = "C4*G"))).first;
//     AtomType::aC4*N = *repository.insert (new AC4*N ((str = "C4*N"))).first;
//     AtomType::aC4*U = *repository.insert (new AC4*U ((str = "C4*U"))).first;
//     AtomType::aC4, = *repository.insert (new AC4, ((str = "C4,"))).first;
//     AtomType::aC40 = *repository.insert (new AC40 ((str = "C40"))).first;
//     AtomType::aC41 = *repository.insert (new AC41 ((str = "C41"))).first;
//     AtomType::aC42 = *repository.insert (new AC42 ((str = "C42"))).first;
//     AtomType::aC42* = *repository.insert (new AC42* ((str = "C42*"))).first;
//     AtomType::aC43 = *repository.insert (new AC43 ((str = "C43"))).first;
//     AtomType::aC43* = *repository.insert (new AC43* ((str = "C43*"))).first;
//     AtomType::aC44 = *repository.insert (new AC44 ((str = "C44"))).first;
//     AtomType::aC45 = *repository.insert (new AC45 ((str = "C45"))).first;
//     AtomType::aC46 = *repository.insert (new AC46 ((str = "C46"))).first;
//     AtomType::aC47 = *repository.insert (new AC47 ((str = "C47"))).first;
//     AtomType::aC48 = *repository.insert (new AC48 ((str = "C48"))).first;
//     AtomType::aC49 = *repository.insert (new AC49 ((str = "C49"))).first;
//     AtomType::aC4A = *repository.insert (new AC4A ((str = "C4A"))).first;
//     AtomType::aC4A* = *repository.insert (new AC4A* ((str = "C4A*"))).first;
//     AtomType::aC4B = *repository.insert (new AC4B ((str = "C4B"))).first;
//     AtomType::aC4C = *repository.insert (new AC4C ((str = "C4C"))).first;
//     AtomType::aC4D = *repository.insert (new AC4D ((str = "C4D"))).first;
//     AtomType::aC4E = *repository.insert (new AC4E ((str = "C4E"))).first;
//     AtomType::aC4F = *repository.insert (new AC4F ((str = "C4F"))).first;
//     AtomType::aC4G = *repository.insert (new AC4G ((str = "C4G"))).first;
//     AtomType::aC4H = *repository.insert (new AC4H ((str = "C4H"))).first;
//     AtomType::aC4I = *repository.insert (new AC4I ((str = "C4I"))).first;
//     AtomType::aC4J = *repository.insert (new AC4J ((str = "C4J"))).first;
//     AtomType::aC4K = *repository.insert (new AC4K ((str = "C4K"))).first;
//     AtomType::aC4L = *repository.insert (new AC4L ((str = "C4L"))).first;
//     AtomType::aC4M = *repository.insert (new AC4M ((str = "C4M"))).first;
//     AtomType::aC4N = *repository.insert (new AC4N ((str = "C4N"))).first;
//     AtomType::aC4P = *repository.insert (new AC4P ((str = "C4P"))).first;
//     AtomType::aC4Q = *repository.insert (new AC4Q ((str = "C4Q"))).first;
//     AtomType::aC4R = *repository.insert (new AC4R ((str = "C4R"))).first;
//     AtomType::aC4S = *repository.insert (new AC4S ((str = "C4S"))).first;
//     AtomType::aC4T = *repository.insert (new AC4T ((str = "C4T"))).first;
//     AtomType::aC4U = *repository.insert (new AC4U ((str = "C4U"))).first;
//     AtomType::aC4W = *repository.insert (new AC4W ((str = "C4W"))).first;
//     AtomType::aC4X = *repository.insert (new AC4X ((str = "C4X"))).first;
//     AtomType::aC4Y = *repository.insert (new AC4Y ((str = "C4Y"))).first;
//     AtomType::aC4Z = *repository.insert (new AC4Z ((str = "C4Z"))).first;
//     AtomType::aC5 = *repository.insert (new AC5 ((str = "C5"))).first;
//     AtomType::aC5" = *repository.insert (new AC5" ((str = "C5""))).first;
//     AtomType::aC5* = *repository.insert (new AC5* ((str = "C5*"))).first;
//     AtomType::aC5** = *repository.insert (new AC5** ((str = "C5**"))).first;
//     AtomType::aC5*A = *repository.insert (new AC5*A ((str = "C5*A"))).first;
//     AtomType::aC5*B = *repository.insert (new AC5*B ((str = "C5*B"))).first;
//     AtomType::aC5*G = *repository.insert (new AC5*G ((str = "C5*G"))).first;
//     AtomType::aC5*N = *repository.insert (new AC5*N ((str = "C5*N"))).first;
//     AtomType::aC5*U = *repository.insert (new AC5*U ((str = "C5*U"))).first;
//     AtomType::aC5, = *repository.insert (new AC5, ((str = "C5,"))).first;
//     AtomType::aC50 = *repository.insert (new AC50 ((str = "C50"))).first;
//     AtomType::aC51 = *repository.insert (new AC51 ((str = "C51"))).first;
//     AtomType::aC52 = *repository.insert (new AC52 ((str = "C52"))).first;
//     AtomType::aC53 = *repository.insert (new AC53 ((str = "C53"))).first;
//     AtomType::aC54 = *repository.insert (new AC54 ((str = "C54"))).first;
//     AtomType::aC55 = *repository.insert (new AC55 ((str = "C55"))).first;
//     AtomType::aC56 = *repository.insert (new AC56 ((str = "C56"))).first;
//     AtomType::aC57 = *repository.insert (new AC57 ((str = "C57"))).first;
//     AtomType::aC58 = *repository.insert (new AC58 ((str = "C58"))).first;
//     AtomType::aC59 = *repository.insert (new AC59 ((str = "C59"))).first;
//     AtomType::aC5A* = *repository.insert (new AC5A* ((str = "C5A*"))).first;
//     AtomType::aC5B = *repository.insert (new AC5B ((str = "C5B"))).first;
//     AtomType::aC5C = *repository.insert (new AC5C ((str = "C5C"))).first;
//     AtomType::aC5D = *repository.insert (new AC5D ((str = "C5D"))).first;
//     AtomType::aC5E = *repository.insert (new AC5E ((str = "C5E"))).first;
//     AtomType::aC5F = *repository.insert (new AC5F ((str = "C5F"))).first;
//     AtomType::aC5G = *repository.insert (new AC5G ((str = "C5G"))).first;
//     AtomType::aC5H = *repository.insert (new AC5H ((str = "C5H"))).first;
//     AtomType::aC5I = *repository.insert (new AC5I ((str = "C5I"))).first;
//     AtomType::aC5J = *repository.insert (new AC5J ((str = "C5J"))).first;
//     AtomType::aC5K = *repository.insert (new AC5K ((str = "C5K"))).first;
//     AtomType::aC5L = *repository.insert (new AC5L ((str = "C5L"))).first;
//     AtomType::aC5M = *repository.insert (new AC5M ((str = "C5M"))).first;
//     AtomType::aC5N = *repository.insert (new AC5N ((str = "C5N"))).first;
//     AtomType::aC5O = *repository.insert (new AC5O ((str = "C5O"))).first;
//     AtomType::aC5P = *repository.insert (new AC5P ((str = "C5P"))).first;
//     AtomType::aC5Q = *repository.insert (new AC5Q ((str = "C5Q"))).first;
//     AtomType::aC5R = *repository.insert (new AC5R ((str = "C5R"))).first;
//     AtomType::aC5S = *repository.insert (new AC5S ((str = "C5S"))).first;
//     AtomType::aC5T = *repository.insert (new AC5T ((str = "C5T"))).first;
//     AtomType::aC5U = *repository.insert (new AC5U ((str = "C5U"))).first;
//     AtomType::aC5W = *repository.insert (new AC5W ((str = "C5W"))).first;
//     AtomType::aC5X = *repository.insert (new AC5X ((str = "C5X"))).first;
//     AtomType::aC5Y = *repository.insert (new AC5Y ((str = "C5Y"))).first;
//     AtomType::aC5Z = *repository.insert (new AC5Z ((str = "C5Z"))).first;
//     AtomType::aC6 = *repository.insert (new AC6 ((str = "C6"))).first;
//     AtomType::aC6" = *repository.insert (new AC6" ((str = "C6""))).first;
//     AtomType::aC6* = *repository.insert (new AC6* ((str = "C6*"))).first;
//     AtomType::aC6** = *repository.insert (new AC6** ((str = "C6**"))).first;
//     AtomType::aC6*A = *repository.insert (new AC6*A ((str = "C6*A"))).first;
//     AtomType::aC6*B = *repository.insert (new AC6*B ((str = "C6*B"))).first;
//     AtomType::aC60 = *repository.insert (new AC60 ((str = "C60"))).first;
//     AtomType::aC61 = *repository.insert (new AC61 ((str = "C61"))).first;
//     AtomType::aC62 = *repository.insert (new AC62 ((str = "C62"))).first;
//     AtomType::aC63 = *repository.insert (new AC63 ((str = "C63"))).first;
//     AtomType::aC64 = *repository.insert (new AC64 ((str = "C64"))).first;
//     AtomType::aC65 = *repository.insert (new AC65 ((str = "C65"))).first;
//     AtomType::aC66 = *repository.insert (new AC66 ((str = "C66"))).first;
//     AtomType::aC67 = *repository.insert (new AC67 ((str = "C67"))).first;
//     AtomType::aC68 = *repository.insert (new AC68 ((str = "C68"))).first;
//     AtomType::aC69 = *repository.insert (new AC69 ((str = "C69"))).first;
//     AtomType::aC6A = *repository.insert (new AC6A ((str = "C6A"))).first;
//     AtomType::aC6B = *repository.insert (new AC6B ((str = "C6B"))).first;
//     AtomType::aC6C = *repository.insert (new AC6C ((str = "C6C"))).first;
//     AtomType::aC6D = *repository.insert (new AC6D ((str = "C6D"))).first;
//     AtomType::aC6E = *repository.insert (new AC6E ((str = "C6E"))).first;
//     AtomType::aC6F = *repository.insert (new AC6F ((str = "C6F"))).first;
//     AtomType::aC6G = *repository.insert (new AC6G ((str = "C6G"))).first;
//     AtomType::aC6H = *repository.insert (new AC6H ((str = "C6H"))).first;
//     AtomType::aC6I = *repository.insert (new AC6I ((str = "C6I"))).first;
//     AtomType::aC6J = *repository.insert (new AC6J ((str = "C6J"))).first;
//     AtomType::aC6K = *repository.insert (new AC6K ((str = "C6K"))).first;
//     AtomType::aC6L = *repository.insert (new AC6L ((str = "C6L"))).first;
//     AtomType::aC6M = *repository.insert (new AC6M ((str = "C6M"))).first;
//     AtomType::aC6N = *repository.insert (new AC6N ((str = "C6N"))).first;
//     AtomType::aC6P = *repository.insert (new AC6P ((str = "C6P"))).first;
//     AtomType::aC6R = *repository.insert (new AC6R ((str = "C6R"))).first;
//     AtomType::aC6S = *repository.insert (new AC6S ((str = "C6S"))).first;
//     AtomType::aC6T = *repository.insert (new AC6T ((str = "C6T"))).first;
//     AtomType::aC6U = *repository.insert (new AC6U ((str = "C6U"))).first;
//     AtomType::aC6W = *repository.insert (new AC6W ((str = "C6W"))).first;
//     AtomType::aC6X = *repository.insert (new AC6X ((str = "C6X"))).first;
//     AtomType::aC6Y = *repository.insert (new AC6Y ((str = "C6Y"))).first;
//     AtomType::aC6Z = *repository.insert (new AC6Z ((str = "C6Z"))).first;
//     AtomType::aC7 = *repository.insert (new AC7 ((str = "C7"))).first;
//     AtomType::aC7" = *repository.insert (new AC7" ((str = "C7""))).first;
//     AtomType::aC7* = *repository.insert (new AC7* ((str = "C7*"))).first;
//     AtomType::aC70 = *repository.insert (new AC70 ((str = "C70"))).first;
//     AtomType::aC71 = *repository.insert (new AC71 ((str = "C71"))).first;
//     AtomType::aC72 = *repository.insert (new AC72 ((str = "C72"))).first;
//     AtomType::aC73 = *repository.insert (new AC73 ((str = "C73"))).first;
//     AtomType::aC74 = *repository.insert (new AC74 ((str = "C74"))).first;
//     AtomType::aC75 = *repository.insert (new AC75 ((str = "C75"))).first;
//     AtomType::aC76 = *repository.insert (new AC76 ((str = "C76"))).first;
//     AtomType::aC77 = *repository.insert (new AC77 ((str = "C77"))).first;
//     AtomType::aC78 = *repository.insert (new AC78 ((str = "C78"))).first;
//     AtomType::aC79 = *repository.insert (new AC79 ((str = "C79"))).first;
//     AtomType::aC7A = *repository.insert (new AC7A ((str = "C7A"))).first;
//     AtomType::aC7B = *repository.insert (new AC7B ((str = "C7B"))).first;
//     AtomType::aC7C = *repository.insert (new AC7C ((str = "C7C"))).first;
//     AtomType::aC7D = *repository.insert (new AC7D ((str = "C7D"))).first;
//     AtomType::aC7E = *repository.insert (new AC7E ((str = "C7E"))).first;
//     AtomType::aC7F = *repository.insert (new AC7F ((str = "C7F"))).first;
//     AtomType::aC7H = *repository.insert (new AC7H ((str = "C7H"))).first;
//     AtomType::aC7I = *repository.insert (new AC7I ((str = "C7I"))).first;
//     AtomType::aC7J = *repository.insert (new AC7J ((str = "C7J"))).first;
//     AtomType::aC7K = *repository.insert (new AC7K ((str = "C7K"))).first;
//     AtomType::aC7M = *repository.insert (new AC7M ((str = "C7M"))).first;
//     AtomType::aC7MA = *repository.insert (new AC7MA ((str = "C7MA"))).first;
//     AtomType::aC7N = *repository.insert (new AC7N ((str = "C7N"))).first;
//     AtomType::aC7P = *repository.insert (new AC7P ((str = "C7P"))).first;
//     AtomType::aC7R = *repository.insert (new AC7R ((str = "C7R"))).first;
//     AtomType::aC7S = *repository.insert (new AC7S ((str = "C7S"))).first;
//     AtomType::aC7T = *repository.insert (new AC7T ((str = "C7T"))).first;
//     AtomType::aC7X = *repository.insert (new AC7X ((str = "C7X"))).first;
//     AtomType::aC7Z = *repository.insert (new AC7Z ((str = "C7Z"))).first;
//     AtomType::aC8 = *repository.insert (new AC8 ((str = "C8"))).first;
//     AtomType::aC8" = *repository.insert (new AC8" ((str = "C8""))).first;
//     AtomType::aC8* = *repository.insert (new AC8* ((str = "C8*"))).first;
//     AtomType::aC80 = *repository.insert (new AC80 ((str = "C80"))).first;
//     AtomType::aC81 = *repository.insert (new AC81 ((str = "C81"))).first;
//     AtomType::aC82 = *repository.insert (new AC82 ((str = "C82"))).first;
//     AtomType::aC83 = *repository.insert (new AC83 ((str = "C83"))).first;
//     AtomType::aC84 = *repository.insert (new AC84 ((str = "C84"))).first;
//     AtomType::aC85 = *repository.insert (new AC85 ((str = "C85"))).first;
//     AtomType::aC86 = *repository.insert (new AC86 ((str = "C86"))).first;
//     AtomType::aC87 = *repository.insert (new AC87 ((str = "C87"))).first;
//     AtomType::aC88 = *repository.insert (new AC88 ((str = "C88"))).first;
//     AtomType::aC89 = *repository.insert (new AC89 ((str = "C89"))).first;
//     AtomType::aC8A = *repository.insert (new AC8A ((str = "C8A"))).first;
//     AtomType::aC8A* = *repository.insert (new AC8A* ((str = "C8A*"))).first;
//     AtomType::aC8B = *repository.insert (new AC8B ((str = "C8B"))).first;
//     AtomType::aC8C = *repository.insert (new AC8C ((str = "C8C"))).first;
//     AtomType::aC8D = *repository.insert (new AC8D ((str = "C8D"))).first;
//     AtomType::aC8E = *repository.insert (new AC8E ((str = "C8E"))).first;
//     AtomType::aC8F = *repository.insert (new AC8F ((str = "C8F"))).first;
//     AtomType::aC8G = *repository.insert (new AC8G ((str = "C8G"))).first;
//     AtomType::aC8I = *repository.insert (new AC8I ((str = "C8I"))).first;
//     AtomType::aC8J = *repository.insert (new AC8J ((str = "C8J"))).first;
//     AtomType::aC8K = *repository.insert (new AC8K ((str = "C8K"))).first;
//     AtomType::aC8M = *repository.insert (new AC8M ((str = "C8M"))).first;
//     AtomType::aC8N = *repository.insert (new AC8N ((str = "C8N"))).first;
//     AtomType::aC8O = *repository.insert (new AC8O ((str = "C8O"))).first;
//     AtomType::aC8P = *repository.insert (new AC8P ((str = "C8P"))).first;
//     AtomType::aC8R = *repository.insert (new AC8R ((str = "C8R"))).first;
//     AtomType::aC8S = *repository.insert (new AC8S ((str = "C8S"))).first;
//     AtomType::aC8X = *repository.insert (new AC8X ((str = "C8X"))).first;
//     AtomType::aC9 = *repository.insert (new AC9 ((str = "C9"))).first;
//     AtomType::aC9" = *repository.insert (new AC9" ((str = "C9""))).first;
//     AtomType::aC9* = *repository.insert (new AC9* ((str = "C9*"))).first;
//     AtomType::aC90 = *repository.insert (new AC90 ((str = "C90"))).first;
//     AtomType::aC91 = *repository.insert (new AC91 ((str = "C91"))).first;
//     AtomType::aC92 = *repository.insert (new AC92 ((str = "C92"))).first;
//     AtomType::aC93 = *repository.insert (new AC93 ((str = "C93"))).first;
//     AtomType::aC94 = *repository.insert (new AC94 ((str = "C94"))).first;
//     AtomType::aC95 = *repository.insert (new AC95 ((str = "C95"))).first;
//     AtomType::aC96 = *repository.insert (new AC96 ((str = "C96"))).first;
//     AtomType::aC97 = *repository.insert (new AC97 ((str = "C97"))).first;
//     AtomType::aC98 = *repository.insert (new AC98 ((str = "C98"))).first;
//     AtomType::aC99 = *repository.insert (new AC99 ((str = "C99"))).first;
//     AtomType::aC9A = *repository.insert (new AC9A ((str = "C9A"))).first;
//     AtomType::aC9A* = *repository.insert (new AC9A* ((str = "C9A*"))).first;
//     AtomType::aC9B = *repository.insert (new AC9B ((str = "C9B"))).first;
//     AtomType::aC9C = *repository.insert (new AC9C ((str = "C9C"))).first;
//     AtomType::aC9D = *repository.insert (new AC9D ((str = "C9D"))).first;
//     AtomType::aC9E = *repository.insert (new AC9E ((str = "C9E"))).first;
//     AtomType::aC9F = *repository.insert (new AC9F ((str = "C9F"))).first;
//     AtomType::aC9J = *repository.insert (new AC9J ((str = "C9J"))).first;
//     AtomType::aC9K = *repository.insert (new AC9K ((str = "C9K"))).first;
//     AtomType::aC9M = *repository.insert (new AC9M ((str = "C9M"))).first;
//     AtomType::aC9N = *repository.insert (new AC9N ((str = "C9N"))).first;
//     AtomType::aC9P = *repository.insert (new AC9P ((str = "C9P"))).first;
//     AtomType::aC9R = *repository.insert (new AC9R ((str = "C9R"))).first;
//     AtomType::aC9S = *repository.insert (new AC9S ((str = "C9S"))).first;
//     AtomType::aC9X = *repository.insert (new AC9X ((str = "C9X"))).first;
//     AtomType::aCA = *repository.insert (new ACA ((str = "CA"))).first;
//     AtomType::aCA" = *repository.insert (new ACA" ((str = "CA""))).first;
//     AtomType::aCA* = *repository.insert (new ACA* ((str = "CA*"))).first;
//     AtomType::aCA0 = *repository.insert (new ACA0 ((str = "CA0"))).first;
//     AtomType::aCA1 = *repository.insert (new ACA1 ((str = "CA1"))).first;
//     AtomType::aCA2 = *repository.insert (new ACA2 ((str = "CA2"))).first;
//     AtomType::aCA3 = *repository.insert (new ACA3 ((str = "CA3"))).first;
//     AtomType::aCA4 = *repository.insert (new ACA4 ((str = "CA4"))).first;
//     AtomType::aCA5 = *repository.insert (new ACA5 ((str = "CA5"))).first;
//     AtomType::aCA6 = *repository.insert (new ACA6 ((str = "CA6"))).first;
//     AtomType::aCA7 = *repository.insert (new ACA7 ((str = "CA7"))).first;
//     AtomType::aCA8 = *repository.insert (new ACA8 ((str = "CA8"))).first;
//     AtomType::aCA9 = *repository.insert (new ACA9 ((str = "CA9"))).first;
//     AtomType::aCAA = *repository.insert (new ACAA ((str = "CAA"))).first;
//     AtomType::aCAB = *repository.insert (new ACAB ((str = "CAB"))).first;
//     AtomType::aCAC = *repository.insert (new ACAC ((str = "CAC"))).first;
//     AtomType::aCAD = *repository.insert (new ACAD ((str = "CAD"))).first;
//     AtomType::aCAE = *repository.insert (new ACAE ((str = "CAE"))).first;
//     AtomType::aCAF = *repository.insert (new ACAF ((str = "CAF"))).first;
//     AtomType::aCAG = *repository.insert (new ACAG ((str = "CAG"))).first;
//     AtomType::aCAH = *repository.insert (new ACAH ((str = "CAH"))).first;
//     AtomType::aCAI = *repository.insert (new ACAI ((str = "CAI"))).first;
//     AtomType::aCAJ = *repository.insert (new ACAJ ((str = "CAJ"))).first;
//     AtomType::aCAK = *repository.insert (new ACAK ((str = "CAK"))).first;
//     AtomType::aCAL = *repository.insert (new ACAL ((str = "CAL"))).first;
//     AtomType::aCAM = *repository.insert (new ACAM ((str = "CAM"))).first;
//     AtomType::aCAN = *repository.insert (new ACAN ((str = "CAN"))).first;
//     AtomType::aCAO = *repository.insert (new ACAO ((str = "CAO"))).first;
//     AtomType::aCAP = *repository.insert (new ACAP ((str = "CAP"))).first;
//     AtomType::aCAQ = *repository.insert (new ACAQ ((str = "CAQ"))).first;
//     AtomType::aCAR = *repository.insert (new ACAR ((str = "CAR"))).first;
//     AtomType::aCAS = *repository.insert (new ACAS ((str = "CAS"))).first;
//     AtomType::aCAT = *repository.insert (new ACAT ((str = "CAT"))).first;
//     AtomType::aCAU = *repository.insert (new ACAU ((str = "CAU"))).first;
//     AtomType::aCAV = *repository.insert (new ACAV ((str = "CAV"))).first;
//     AtomType::aCAW = *repository.insert (new ACAW ((str = "CAW"))).first;
//     AtomType::aCAX = *repository.insert (new ACAX ((str = "CAX"))).first;
//     AtomType::aCAY = *repository.insert (new ACAY ((str = "CAY"))).first;
//     AtomType::aCAZ = *repository.insert (new ACAZ ((str = "CAZ"))).first;
//     AtomType::aCB = *repository.insert (new ACB ((str = "CB"))).first;
//     AtomType::aCB* = *repository.insert (new ACB* ((str = "CB*"))).first;
//     AtomType::aCB0 = *repository.insert (new ACB0 ((str = "CB0"))).first;
//     AtomType::aCB1 = *repository.insert (new ACB1 ((str = "CB1"))).first;
//     AtomType::aCB2 = *repository.insert (new ACB2 ((str = "CB2"))).first;
//     AtomType::aCB3 = *repository.insert (new ACB3 ((str = "CB3"))).first;
//     AtomType::aCB4 = *repository.insert (new ACB4 ((str = "CB4"))).first;
//     AtomType::aCB5 = *repository.insert (new ACB5 ((str = "CB5"))).first;
//     AtomType::aCB6 = *repository.insert (new ACB6 ((str = "CB6"))).first;
//     AtomType::aCB7 = *repository.insert (new ACB7 ((str = "CB7"))).first;
//     AtomType::aCB8 = *repository.insert (new ACB8 ((str = "CB8"))).first;
//     AtomType::aCB9 = *repository.insert (new ACB9 ((str = "CB9"))).first;
//     AtomType::aCBA = *repository.insert (new ACBA ((str = "CBA"))).first;
//     AtomType::aCBB = *repository.insert (new ACBB ((str = "CBB"))).first;
//     AtomType::aCBC = *repository.insert (new ACBC ((str = "CBC"))).first;
//     AtomType::aCBD = *repository.insert (new ACBD ((str = "CBD"))).first;
//     AtomType::aCBE = *repository.insert (new ACBE ((str = "CBE"))).first;
//     AtomType::aCBF = *repository.insert (new ACBF ((str = "CBF"))).first;
//     AtomType::aCBG = *repository.insert (new ACBG ((str = "CBG"))).first;
//     AtomType::aCBH = *repository.insert (new ACBH ((str = "CBH"))).first;
//     AtomType::aCBI = *repository.insert (new ACBI ((str = "CBI"))).first;
//     AtomType::aCBJ = *repository.insert (new ACBJ ((str = "CBJ"))).first;
//     AtomType::aCBK = *repository.insert (new ACBK ((str = "CBK"))).first;
//     AtomType::aCBL = *repository.insert (new ACBL ((str = "CBL"))).first;
//     AtomType::aCBM = *repository.insert (new ACBM ((str = "CBM"))).first;
//     AtomType::aCBN = *repository.insert (new ACBN ((str = "CBN"))).first;
//     AtomType::aCBO = *repository.insert (new ACBO ((str = "CBO"))).first;
//     AtomType::aCBP = *repository.insert (new ACBP ((str = "CBP"))).first;
//     AtomType::aCBQ = *repository.insert (new ACBQ ((str = "CBQ"))).first;
//     AtomType::aCBR = *repository.insert (new ACBR ((str = "CBR"))).first;
//     AtomType::aCBS = *repository.insert (new ACBS ((str = "CBS"))).first;
//     AtomType::aCBT = *repository.insert (new ACBT ((str = "CBT"))).first;
//     AtomType::aCBU = *repository.insert (new ACBU ((str = "CBU"))).first;
//     AtomType::aCBV = *repository.insert (new ACBV ((str = "CBV"))).first;
//     AtomType::aCBW = *repository.insert (new ACBW ((str = "CBW"))).first;
//     AtomType::aCBX = *repository.insert (new ACBX ((str = "CBX"))).first;
//     AtomType::aCBY = *repository.insert (new ACBY ((str = "CBY"))).first;
//     AtomType::aCBZ = *repository.insert (new ACBZ ((str = "CBZ"))).first;
//     AtomType::aCC = *repository.insert (new ACC ((str = "CC"))).first;
//     AtomType::aCC* = *repository.insert (new ACC* ((str = "CC*"))).first;
//     AtomType::aCC1 = *repository.insert (new ACC1 ((str = "CC1"))).first;
//     AtomType::aCC1* = *repository.insert (new ACC1* ((str = "CC1*"))).first;
//     AtomType::aCC2 = *repository.insert (new ACC2 ((str = "CC2"))).first;
//     AtomType::aCC2* = *repository.insert (new ACC2* ((str = "CC2*"))).first;
//     AtomType::aCC3 = *repository.insert (new ACC3 ((str = "CC3"))).first;
//     AtomType::aCC3* = *repository.insert (new ACC3* ((str = "CC3*"))).first;
//     AtomType::aCC4 = *repository.insert (new ACC4 ((str = "CC4"))).first;
//     AtomType::aCC4* = *repository.insert (new ACC4* ((str = "CC4*"))).first;
//     AtomType::aCC5 = *repository.insert (new ACC5 ((str = "CC5"))).first;
//     AtomType::aCC5* = *repository.insert (new ACC5* ((str = "CC5*"))).first;
//     AtomType::aCC6 = *repository.insert (new ACC6 ((str = "CC6"))).first;
//     AtomType::aCC7 = *repository.insert (new ACC7 ((str = "CC7"))).first;
//     AtomType::aCC8 = *repository.insert (new ACC8 ((str = "CC8"))).first;
//     AtomType::aCC9 = *repository.insert (new ACC9 ((str = "CC9"))).first;
//     AtomType::aCCA = *repository.insert (new ACCA ((str = "CCA"))).first;
//     AtomType::aCCB = *repository.insert (new ACCB ((str = "CCB"))).first;
//     AtomType::aCCC = *repository.insert (new ACCC ((str = "CCC"))).first;
//     AtomType::aCCD = *repository.insert (new ACCD ((str = "CCD"))).first;
//     AtomType::aCCE = *repository.insert (new ACCE ((str = "CCE"))).first;
//     AtomType::aCCF = *repository.insert (new ACCF ((str = "CCF"))).first;
//     AtomType::aCCG = *repository.insert (new ACCG ((str = "CCG"))).first;
//     AtomType::aCCH = *repository.insert (new ACCH ((str = "CCH"))).first;
//     AtomType::aCCI = *repository.insert (new ACCI ((str = "CCI"))).first;
//     AtomType::aCCJ = *repository.insert (new ACCJ ((str = "CCJ"))).first;
//     AtomType::aCCK = *repository.insert (new ACCK ((str = "CCK"))).first;
//     AtomType::aCCL = *repository.insert (new ACCL ((str = "CCL"))).first;
//     AtomType::aCCM = *repository.insert (new ACCM ((str = "CCM"))).first;
//     AtomType::aCCN = *repository.insert (new ACCN ((str = "CCN"))).first;
//     AtomType::aCCO = *repository.insert (new ACCO ((str = "CCO"))).first;
//     AtomType::aCCP = *repository.insert (new ACCP ((str = "CCP"))).first;
//     AtomType::aCCQ = *repository.insert (new ACCQ ((str = "CCQ"))).first;
//     AtomType::aCCR = *repository.insert (new ACCR ((str = "CCR"))).first;
//     AtomType::aCCS = *repository.insert (new ACCS ((str = "CCS"))).first;
//     AtomType::aCCT = *repository.insert (new ACCT ((str = "CCT"))).first;
//     AtomType::aCCU = *repository.insert (new ACCU ((str = "CCU"))).first;
//     AtomType::aCCV = *repository.insert (new ACCV ((str = "CCV"))).first;
//     AtomType::aCCW = *repository.insert (new ACCW ((str = "CCW"))).first;
//     AtomType::aCCX = *repository.insert (new ACCX ((str = "CCX"))).first;
//     AtomType::aCCY = *repository.insert (new ACCY ((str = "CCY"))).first;
//     AtomType::aCCZ = *repository.insert (new ACCZ ((str = "CCZ"))).first;
//     AtomType::aCD = *repository.insert (new ACD ((str = "CD"))).first;
//     AtomType::aCD* = *repository.insert (new ACD* ((str = "CD*"))).first;
//     AtomType::aCD0 = *repository.insert (new ACD0 ((str = "CD0"))).first;
//     AtomType::aCD1 = *repository.insert (new ACD1 ((str = "CD1"))).first;
//     AtomType::aCD1T = *repository.insert (new ACD1T ((str = "CD1T"))).first;
//     AtomType::aCD2 = *repository.insert (new ACD2 ((str = "CD2"))).first;
//     AtomType::aCD2T = *repository.insert (new ACD2T ((str = "CD2T"))).first;
//     AtomType::aCD3 = *repository.insert (new ACD3 ((str = "CD3"))).first;
//     AtomType::aCD31 = *repository.insert (new ACD31 ((str = "CD31"))).first;
//     AtomType::aCD32 = *repository.insert (new ACD32 ((str = "CD32"))).first;
//     AtomType::aCD4 = *repository.insert (new ACD4 ((str = "CD4"))).first;
//     AtomType::aCD5 = *repository.insert (new ACD5 ((str = "CD5"))).first;
//     AtomType::aCD6 = *repository.insert (new ACD6 ((str = "CD6"))).first;
//     AtomType::aCD7 = *repository.insert (new ACD7 ((str = "CD7"))).first;
//     AtomType::aCD8 = *repository.insert (new ACD8 ((str = "CD8"))).first;
//     AtomType::aCD9 = *repository.insert (new ACD9 ((str = "CD9"))).first;
//     AtomType::aCDA = *repository.insert (new ACDA ((str = "CDA"))).first;
//     AtomType::aCDB = *repository.insert (new ACDB ((str = "CDB"))).first;
//     AtomType::aCDC = *repository.insert (new ACDC ((str = "CDC"))).first;
//     AtomType::aCDD = *repository.insert (new ACDD ((str = "CDD"))).first;
//     AtomType::aCDE = *repository.insert (new ACDE ((str = "CDE"))).first;
//     AtomType::aCDF = *repository.insert (new ACDF ((str = "CDF"))).first;
//     AtomType::aCDG = *repository.insert (new ACDG ((str = "CDG"))).first;
//     AtomType::aCDH = *repository.insert (new ACDH ((str = "CDH"))).first;
//     AtomType::aCDI = *repository.insert (new ACDI ((str = "CDI"))).first;
//     AtomType::aCDJ = *repository.insert (new ACDJ ((str = "CDJ"))).first;
//     AtomType::aCDK = *repository.insert (new ACDK ((str = "CDK"))).first;
//     AtomType::aCDL = *repository.insert (new ACDL ((str = "CDL"))).first;
//     AtomType::aCDM = *repository.insert (new ACDM ((str = "CDM"))).first;
//     AtomType::aCDN = *repository.insert (new ACDN ((str = "CDN"))).first;
//     AtomType::aCDO = *repository.insert (new ACDO ((str = "CDO"))).first;
//     AtomType::aCDP = *repository.insert (new ACDP ((str = "CDP"))).first;
//     AtomType::aCDQ = *repository.insert (new ACDQ ((str = "CDQ"))).first;
//     AtomType::aCDY = *repository.insert (new ACDY ((str = "CDY"))).first;
//     AtomType::aCE = *repository.insert (new ACE ((str = "CE"))).first;
//     AtomType::aCE* = *repository.insert (new ACE* ((str = "CE*"))).first;
//     AtomType::aCE0 = *repository.insert (new ACE0 ((str = "CE0"))).first;
//     AtomType::aCE1 = *repository.insert (new ACE1 ((str = "CE1"))).first;
//     AtomType::aCE2 = *repository.insert (new ACE2 ((str = "CE2"))).first;
//     AtomType::aCE2T = *repository.insert (new ACE2T ((str = "CE2T"))).first;
//     AtomType::aCE3 = *repository.insert (new ACE3 ((str = "CE3"))).first;
//     AtomType::aCE31 = *repository.insert (new ACE31 ((str = "CE31"))).first;
//     AtomType::aCE32 = *repository.insert (new ACE32 ((str = "CE32"))).first;
//     AtomType::aCE3T = *repository.insert (new ACE3T ((str = "CE3T"))).first;
//     AtomType::aCE4 = *repository.insert (new ACE4 ((str = "CE4"))).first;
//     AtomType::aCE5 = *repository.insert (new ACE5 ((str = "CE5"))).first;
//     AtomType::aCE6 = *repository.insert (new ACE6 ((str = "CE6"))).first;
//     AtomType::aCE7 = *repository.insert (new ACE7 ((str = "CE7"))).first;
//     AtomType::aCEA = *repository.insert (new ACEA ((str = "CEA"))).first;
//     AtomType::aCEB = *repository.insert (new ACEB ((str = "CEB"))).first;
//     AtomType::aCEC = *repository.insert (new ACEC ((str = "CEC"))).first;
//     AtomType::aCED = *repository.insert (new ACED ((str = "CED"))).first;
//     AtomType::aCEF = *repository.insert (new ACEF ((str = "CEF"))).first;
//     AtomType::aCEI = *repository.insert (new ACEI ((str = "CEI"))).first;
//     AtomType::aCEK = *repository.insert (new ACEK ((str = "CEK"))).first;
//     AtomType::aCEM = *repository.insert (new ACEM ((str = "CEM"))).first;
//     AtomType::aCEP = *repository.insert (new ACEP ((str = "CEP"))).first;
//     AtomType::aCEY = *repository.insert (new ACEY ((str = "CEY"))).first;
//     AtomType::aCF = *repository.insert (new ACF ((str = "CF"))).first;
//     AtomType::aCF* = *repository.insert (new ACF* ((str = "CF*"))).first;
//     AtomType::aCF1 = *repository.insert (new ACF1 ((str = "CF1"))).first;
//     AtomType::aCF2 = *repository.insert (new ACF2 ((str = "CF2"))).first;
//     AtomType::aCF3* = *repository.insert (new ACF3* ((str = "CF3*"))).first;
//     AtomType::aCFF = *repository.insert (new ACFF ((str = "CFF"))).first;
//     AtomType::aCFI = *repository.insert (new ACFI ((str = "CFI"))).first;
//     AtomType::aCFM = *repository.insert (new ACFM ((str = "CFM"))).first;
//     AtomType::aCFM4 = *repository.insert (new ACFM4 ((str = "CFM4"))).first;
//     AtomType::aCFM7 = *repository.insert (new ACFM7 ((str = "CFM7"))).first;
//     AtomType::aCG = *repository.insert (new ACG ((str = "CG"))).first;
//     AtomType::aCG* = *repository.insert (new ACG* ((str = "CG*"))).first;
//     AtomType::aCG0 = *repository.insert (new ACG0 ((str = "CG0"))).first;
//     AtomType::aCG1 = *repository.insert (new ACG1 ((str = "CG1"))).first;
//     AtomType::aCG2 = *repository.insert (new ACG2 ((str = "CG2"))).first;
//     AtomType::aCG3 = *repository.insert (new ACG3 ((str = "CG3"))).first;
//     AtomType::aCG4 = *repository.insert (new ACG4 ((str = "CG4"))).first;
//     AtomType::aCG5 = *repository.insert (new ACG5 ((str = "CG5"))).first;
//     AtomType::aCG51 = *repository.insert (new ACG51 ((str = "CG51"))).first;
//     AtomType::aCG52 = *repository.insert (new ACG52 ((str = "CG52"))).first;
//     AtomType::aCG6 = *repository.insert (new ACG6 ((str = "CG6"))).first;
//     AtomType::aCG61 = *repository.insert (new ACG61 ((str = "CG61"))).first;
//     AtomType::aCG62 = *repository.insert (new ACG62 ((str = "CG62"))).first;
//     AtomType::aCG7 = *repository.insert (new ACG7 ((str = "CG7"))).first;
//     AtomType::aCG8 = *repository.insert (new ACG8 ((str = "CG8"))).first;
//     AtomType::aCGA = *repository.insert (new ACGA ((str = "CGA"))).first;
//     AtomType::aCGB = *repository.insert (new ACGB ((str = "CGB"))).first;
//     AtomType::aCGC = *repository.insert (new ACGC ((str = "CGC"))).first;
//     AtomType::aCGD = *repository.insert (new ACGD ((str = "CGD"))).first;
//     AtomType::aCGF = *repository.insert (new ACGF ((str = "CGF"))).first;
//     AtomType::aCGI = *repository.insert (new ACGI ((str = "CGI"))).first;
//     AtomType::aCGK = *repository.insert (new ACGK ((str = "CGK"))).first;
//     AtomType::aCGL = *repository.insert (new ACGL ((str = "CGL"))).first;
//     AtomType::aCGO = *repository.insert (new ACGO ((str = "CGO"))).first;
//     AtomType::aCGP = *repository.insert (new ACGP ((str = "CGP"))).first;
//     AtomType::aCGS = *repository.insert (new ACGS ((str = "CGS"))).first;
//     AtomType::aCGT = *repository.insert (new ACGT ((str = "CGT"))).first;
//     AtomType::aCGY = *repository.insert (new ACGY ((str = "CGY"))).first;
//     AtomType::aCH = *repository.insert (new ACH ((str = "CH"))).first;
//     AtomType::aCH* = *repository.insert (new ACH* ((str = "CH*"))).first;
//     AtomType::aCH01 = *repository.insert (new ACH01 ((str = "CH01"))).first;
//     AtomType::aCH02 = *repository.insert (new ACH02 ((str = "CH02"))).first;
//     AtomType::aCH04 = *repository.insert (new ACH04 ((str = "CH04"))).first;
//     AtomType::aCH05 = *repository.insert (new ACH05 ((str = "CH05"))).first;
//     AtomType::aCH1 = *repository.insert (new ACH1 ((str = "CH1"))).first;
//     AtomType::aCH1* = *repository.insert (new ACH1* ((str = "CH1*"))).first;
//     AtomType::aCH1, = *repository.insert (new ACH1, ((str = "CH1,"))).first;
//     AtomType::aCH10 = *repository.insert (new ACH10 ((str = "CH10"))).first;
//     AtomType::aCH11 = *repository.insert (new ACH11 ((str = "CH11"))).first;
//     AtomType::aCH12 = *repository.insert (new ACH12 ((str = "CH12"))).first;
//     AtomType::aCH13 = *repository.insert (new ACH13 ((str = "CH13"))).first;
//     AtomType::aCH14 = *repository.insert (new ACH14 ((str = "CH14"))).first;
//     AtomType::aCH15 = *repository.insert (new ACH15 ((str = "CH15"))).first;
//     AtomType::aCH16 = *repository.insert (new ACH16 ((str = "CH16"))).first;
//     AtomType::aCH17 = *repository.insert (new ACH17 ((str = "CH17"))).first;
//     AtomType::aCH18 = *repository.insert (new ACH18 ((str = "CH18"))).first;
//     AtomType::aCH19 = *repository.insert (new ACH19 ((str = "CH19"))).first;
//     AtomType::aCH1N = *repository.insert (new ACH1N ((str = "CH1N"))).first;
//     AtomType::aCH1R = *repository.insert (new ACH1R ((str = "CH1R"))).first;
//     AtomType::aCH1T = *repository.insert (new ACH1T ((str = "CH1T"))).first;
//     AtomType::aCH1X = *repository.insert (new ACH1X ((str = "CH1X"))).first;
//     AtomType::aCH2 = *repository.insert (new ACH2 ((str = "CH2"))).first;
//     AtomType::aCH2* = *repository.insert (new ACH2* ((str = "CH2*"))).first;
//     AtomType::aCH20 = *repository.insert (new ACH20 ((str = "CH20"))).first;
//     AtomType::aCH21 = *repository.insert (new ACH21 ((str = "CH21"))).first;
//     AtomType::aCH22 = *repository.insert (new ACH22 ((str = "CH22"))).first;
//     AtomType::aCH23 = *repository.insert (new ACH23 ((str = "CH23"))).first;
//     AtomType::aCH24 = *repository.insert (new ACH24 ((str = "CH24"))).first;
//     AtomType::aCH25 = *repository.insert (new ACH25 ((str = "CH25"))).first;
//     AtomType::aCH26 = *repository.insert (new ACH26 ((str = "CH26"))).first;
//     AtomType::aCH27 = *repository.insert (new ACH27 ((str = "CH27"))).first;
//     AtomType::aCH28 = *repository.insert (new ACH28 ((str = "CH28"))).first;
//     AtomType::aCH29 = *repository.insert (new ACH29 ((str = "CH29"))).first;
//     AtomType::aCH2A = *repository.insert (new ACH2A ((str = "CH2A"))).first;
//     AtomType::aCH2N = *repository.insert (new ACH2N ((str = "CH2N"))).first;
//     AtomType::aCH2R = *repository.insert (new ACH2R ((str = "CH2R"))).first;
//     AtomType::aCH2T = *repository.insert (new ACH2T ((str = "CH2T"))).first;
//     AtomType::aCH2X = *repository.insert (new ACH2X ((str = "CH2X"))).first;
//     AtomType::aCH3 = *repository.insert (new ACH3 ((str = "CH3"))).first;
//     AtomType::aCH3* = *repository.insert (new ACH3* ((str = "CH3*"))).first;
//     AtomType::aCH3, = *repository.insert (new ACH3, ((str = "CH3,"))).first;
//     AtomType::aCH30 = *repository.insert (new ACH30 ((str = "CH30"))).first;
//     AtomType::aCH31 = *repository.insert (new ACH31 ((str = "CH31"))).first;
//     AtomType::aCH32 = *repository.insert (new ACH32 ((str = "CH32"))).first;
//     AtomType::aCH3A = *repository.insert (new ACH3A ((str = "CH3A"))).first;
//     AtomType::aCH3I = *repository.insert (new ACH3I ((str = "CH3I"))).first;
//     AtomType::aCH3N = *repository.insert (new ACH3N ((str = "CH3N"))).first;
//     AtomType::aCH3R = *repository.insert (new ACH3R ((str = "CH3R"))).first;
//     AtomType::aCH3T = *repository.insert (new ACH3T ((str = "CH3T"))).first;
//     AtomType::aCH4 = *repository.insert (new ACH4 ((str = "CH4"))).first;
//     AtomType::aCH4* = *repository.insert (new ACH4* ((str = "CH4*"))).first;
//     AtomType::aCH4, = *repository.insert (new ACH4, ((str = "CH4,"))).first;
//     AtomType::aCH41 = *repository.insert (new ACH41 ((str = "CH41"))).first;
//     AtomType::aCH42 = *repository.insert (new ACH42 ((str = "CH42"))).first;
//     AtomType::aCH4A = *repository.insert (new ACH4A ((str = "CH4A"))).first;
//     AtomType::aCH4N = *repository.insert (new ACH4N ((str = "CH4N"))).first;
//     AtomType::aCH4R = *repository.insert (new ACH4R ((str = "CH4R"))).first;
//     AtomType::aCH4T = *repository.insert (new ACH4T ((str = "CH4T"))).first;
//     AtomType::aCH5 = *repository.insert (new ACH5 ((str = "CH5"))).first;
//     AtomType::aCH5* = *repository.insert (new ACH5* ((str = "CH5*"))).first;
//     AtomType::aCH51 = *repository.insert (new ACH51 ((str = "CH51"))).first;
//     AtomType::aCH52 = *repository.insert (new ACH52 ((str = "CH52"))).first;
//     AtomType::aCH5I = *repository.insert (new ACH5I ((str = "CH5I"))).first;
//     AtomType::aCH5N = *repository.insert (new ACH5N ((str = "CH5N"))).first;
//     AtomType::aCH5T = *repository.insert (new ACH5T ((str = "CH5T"))).first;
//     AtomType::aCH6 = *repository.insert (new ACH6 ((str = "CH6"))).first;
//     AtomType::aCH6* = *repository.insert (new ACH6* ((str = "CH6*"))).first;
//     AtomType::aCH61 = *repository.insert (new ACH61 ((str = "CH61"))).first;
//     AtomType::aCH6A = *repository.insert (new ACH6A ((str = "CH6A"))).first;
//     AtomType::aCH6N = *repository.insert (new ACH6N ((str = "CH6N"))).first;
//     AtomType::aCH8A = *repository.insert (new ACH8A ((str = "CH8A"))).first;
//     AtomType::aCHA = *repository.insert (new ACHA ((str = "CHA"))).first;
//     AtomType::aCHA* = *repository.insert (new ACHA* ((str = "CHA*"))).first;
//     AtomType::aCHA1 = *repository.insert (new ACHA1 ((str = "CHA1"))).first;
//     AtomType::aCHA2 = *repository.insert (new ACHA2 ((str = "CHA2"))).first;
//     AtomType::aCHB = *repository.insert (new ACHB ((str = "CHB"))).first;
//     AtomType::aCHBI = *repository.insert (new ACHBI ((str = "CHBI"))).first;
//     AtomType::aCHC = *repository.insert (new ACHC ((str = "CHC"))).first;
//     AtomType::aCHCE = *repository.insert (new ACHCE ((str = "CHCE"))).first;
//     AtomType::aCHD = *repository.insert (new ACHD ((str = "CHD"))).first;
//     AtomType::aCHD1 = *repository.insert (new ACHD1 ((str = "CHD1"))).first;
//     AtomType::aCHE3 = *repository.insert (new ACHE3 ((str = "CHE3"))).first;
//     AtomType::aCHF = *repository.insert (new ACHF ((str = "CHF"))).first;
//     AtomType::aCHGI = *repository.insert (new ACHGI ((str = "CHGI"))).first;
//     AtomType::aCHH2 = *repository.insert (new ACHH2 ((str = "CHH2"))).first;
//     AtomType::aCHO1 = *repository.insert (new ACHO1 ((str = "CHO1"))).first;
//     AtomType::aCHO2 = *repository.insert (new ACHO2 ((str = "CHO2"))).first;
//     AtomType::aCHO3 = *repository.insert (new ACHO3 ((str = "CHO3"))).first;
//     AtomType::aCHO5 = *repository.insert (new ACHO5 ((str = "CHO5"))).first;
//     AtomType::aCHO6 = *repository.insert (new ACHO6 ((str = "CHO6"))).first;
//     AtomType::aCHR = *repository.insert (new ACHR ((str = "CHR"))).first;
//     AtomType::aCHS1 = *repository.insert (new ACHS1 ((str = "CHS1"))).first;
//     AtomType::aCHY = *repository.insert (new ACHY ((str = "CHY"))).first;
//     AtomType::aCHZ2 = *repository.insert (new ACHZ2 ((str = "CHZ2"))).first;
//     AtomType::aCHZ3 = *repository.insert (new ACHZ3 ((str = "CHZ3"))).first;
//     AtomType::aCI = *repository.insert (new ACI ((str = "CI"))).first;
//     AtomType::aCI* = *repository.insert (new ACI* ((str = "CI*"))).first;
//     AtomType::aCI1 = *repository.insert (new ACI1 ((str = "CI1"))).first;
//     AtomType::aCI2 = *repository.insert (new ACI2 ((str = "CI2"))).first;
//     AtomType::aCI3 = *repository.insert (new ACI3 ((str = "CI3"))).first;
//     AtomType::aCI4 = *repository.insert (new ACI4 ((str = "CI4"))).first;
//     AtomType::aCI5 = *repository.insert (new ACI5 ((str = "CI5"))).first;
//     AtomType::aCI6 = *repository.insert (new ACI6 ((str = "CI6"))).first;
//     AtomType::aCIB = *repository.insert (new ACIB ((str = "CIB"))).first;
//     AtomType::aCIF = *repository.insert (new ACIF ((str = "CIF"))).first;
//     AtomType::aCJ = *repository.insert (new ACJ ((str = "CJ"))).first;
//     AtomType::aCJ* = *repository.insert (new ACJ* ((str = "CJ*"))).first;
//     AtomType::aCJ1 = *repository.insert (new ACJ1 ((str = "CJ1"))).first;
//     AtomType::aCJ2 = *repository.insert (new ACJ2 ((str = "CJ2"))).first;
//     AtomType::aCJ3 = *repository.insert (new ACJ3 ((str = "CJ3"))).first;
//     AtomType::aCJ4 = *repository.insert (new ACJ4 ((str = "CJ4"))).first;
//     AtomType::aCJ5 = *repository.insert (new ACJ5 ((str = "CJ5"))).first;
//     AtomType::aCJ6 = *repository.insert (new ACJ6 ((str = "CJ6"))).first;
//     AtomType::aCK = *repository.insert (new ACK ((str = "CK"))).first;
//     AtomType::aCK* = *repository.insert (new ACK* ((str = "CK*"))).first;
//     AtomType::aCK1 = *repository.insert (new ACK1 ((str = "CK1"))).first;
//     AtomType::aCK10 = *repository.insert (new ACK10 ((str = "CK10"))).first;
//     AtomType::aCK11 = *repository.insert (new ACK11 ((str = "CK11"))).first;
//     AtomType::aCK12 = *repository.insert (new ACK12 ((str = "CK12"))).first;
//     AtomType::aCK2 = *repository.insert (new ACK2 ((str = "CK2"))).first;
//     AtomType::aCK3 = *repository.insert (new ACK3 ((str = "CK3"))).first;
//     AtomType::aCK4 = *repository.insert (new ACK4 ((str = "CK4"))).first;
//     AtomType::aCK5 = *repository.insert (new ACK5 ((str = "CK5"))).first;
//     AtomType::aCK6 = *repository.insert (new ACK6 ((str = "CK6"))).first;
//     AtomType::aCK7 = *repository.insert (new ACK7 ((str = "CK7"))).first;
//     AtomType::aCK8 = *repository.insert (new ACK8 ((str = "CK8"))).first;
//     AtomType::aCK9 = *repository.insert (new ACK9 ((str = "CK9"))).first;
//     AtomType::aCKY = *repository.insert (new ACKY ((str = "CKY"))).first;
//     AtomType::aCL = *repository.insert (new ACL ((str = "CL"))).first;
//     AtomType::aCL0 = *repository.insert (new ACL0 ((str = "CL0"))).first;
//     AtomType::aCL07 = *repository.insert (new ACL07 ((str = "CL07"))).first;
//     AtomType::aCL08 = *repository.insert (new ACL08 ((str = "CL08"))).first;
//     AtomType::aCL1 = *repository.insert (new ACL1 ((str = "CL1"))).first;
//     AtomType::aCL10 = *repository.insert (new ACL10 ((str = "CL10"))).first;
//     AtomType::aCL11 = *repository.insert (new ACL11 ((str = "CL11"))).first;
//     AtomType::aCL12 = *repository.insert (new ACL12 ((str = "CL12"))).first;
//     AtomType::aCL13 = *repository.insert (new ACL13 ((str = "CL13"))).first;
//     AtomType::aCL14 = *repository.insert (new ACL14 ((str = "CL14"))).first;
//     AtomType::aCL15 = *repository.insert (new ACL15 ((str = "CL15"))).first;
//     AtomType::aCL16 = *repository.insert (new ACL16 ((str = "CL16"))).first;
//     AtomType::aCL17 = *repository.insert (new ACL17 ((str = "CL17"))).first;
//     AtomType::aCL18 = *repository.insert (new ACL18 ((str = "CL18"))).first;
//     AtomType::aCL19 = *repository.insert (new ACL19 ((str = "CL19"))).first;
//     AtomType::aCL1A = *repository.insert (new ACL1A ((str = "CL1A"))).first;
//     AtomType::aCL1B = *repository.insert (new ACL1B ((str = "CL1B"))).first;
//     AtomType::aCL2 = *repository.insert (new ACL2 ((str = "CL2"))).first;
//     AtomType::aCL2* = *repository.insert (new ACL2* ((str = "CL2*"))).first;
//     AtomType::aCL20 = *repository.insert (new ACL20 ((str = "CL20"))).first;
//     AtomType::aCL21 = *repository.insert (new ACL21 ((str = "CL21"))).first;
//     AtomType::aCL22 = *repository.insert (new ACL22 ((str = "CL22"))).first;
//     AtomType::aCL23 = *repository.insert (new ACL23 ((str = "CL23"))).first;
//     AtomType::aCL24 = *repository.insert (new ACL24 ((str = "CL24"))).first;
//     AtomType::aCL25 = *repository.insert (new ACL25 ((str = "CL25"))).first;
//     AtomType::aCL26 = *repository.insert (new ACL26 ((str = "CL26"))).first;
//     AtomType::aCL27 = *repository.insert (new ACL27 ((str = "CL27"))).first;
//     AtomType::aCL28 = *repository.insert (new ACL28 ((str = "CL28"))).first;
//     AtomType::aCL29 = *repository.insert (new ACL29 ((str = "CL29"))).first;
//     AtomType::aCL2F = *repository.insert (new ACL2F ((str = "CL2F"))).first;
//     AtomType::aCL3 = *repository.insert (new ACL3 ((str = "CL3"))).first;
//     AtomType::aCL30 = *repository.insert (new ACL30 ((str = "CL30"))).first;
//     AtomType::aCL31 = *repository.insert (new ACL31 ((str = "CL31"))).first;
//     AtomType::aCL32 = *repository.insert (new ACL32 ((str = "CL32"))).first;
//     AtomType::aCL33 = *repository.insert (new ACL33 ((str = "CL33"))).first;
//     AtomType::aCL34 = *repository.insert (new ACL34 ((str = "CL34"))).first;
//     AtomType::aCL35 = *repository.insert (new ACL35 ((str = "CL35"))).first;
//     AtomType::aCL36 = *repository.insert (new ACL36 ((str = "CL36"))).first;
//     AtomType::aCL37 = *repository.insert (new ACL37 ((str = "CL37"))).first;
//     AtomType::aCL38 = *repository.insert (new ACL38 ((str = "CL38"))).first;
//     AtomType::aCL39 = *repository.insert (new ACL39 ((str = "CL39"))).first;
//     AtomType::aCL3D = *repository.insert (new ACL3D ((str = "CL3D"))).first;
//     AtomType::aCL3F = *repository.insert (new ACL3F ((str = "CL3F"))).first;
//     AtomType::aCL4 = *repository.insert (new ACL4 ((str = "CL4"))).first;
//     AtomType::aCL4* = *repository.insert (new ACL4* ((str = "CL4*"))).first;
//     AtomType::aCL40 = *repository.insert (new ACL40 ((str = "CL40"))).first;
//     AtomType::aCL41 = *repository.insert (new ACL41 ((str = "CL41"))).first;
//     AtomType::aCL43 = *repository.insert (new ACL43 ((str = "CL43"))).first;
//     AtomType::aCL45 = *repository.insert (new ACL45 ((str = "CL45"))).first;
//     AtomType::aCL46 = *repository.insert (new ACL46 ((str = "CL46"))).first;
//     AtomType::aCL5 = *repository.insert (new ACL5 ((str = "CL5"))).first;
//     AtomType::aCL5* = *repository.insert (new ACL5* ((str = "CL5*"))).first;
//     AtomType::aCL50 = *repository.insert (new ACL50 ((str = "CL50"))).first;
//     AtomType::aCL57 = *repository.insert (new ACL57 ((str = "CL57"))).first;
//     AtomType::aCL6 = *repository.insert (new ACL6 ((str = "CL6"))).first;
//     AtomType::aCL68 = *repository.insert (new ACL68 ((str = "CL68"))).first;
//     AtomType::aCL6A = *repository.insert (new ACL6A ((str = "CL6A"))).first;
//     AtomType::aCL7 = *repository.insert (new ACL7 ((str = "CL7"))).first;
//     AtomType::aCL7A = *repository.insert (new ACL7A ((str = "CL7A"))).first;
//     AtomType::aCL8 = *repository.insert (new ACL8 ((str = "CL8"))).first;
//     AtomType::aCL9 = *repository.insert (new ACL9 ((str = "CL9"))).first;
//     AtomType::aCLA = *repository.insert (new ACLA ((str = "CLA"))).first;
//     AtomType::aCLAD = *repository.insert (new ACLAD ((str = "CLAD"))).first;
//     AtomType::aCLAE = *repository.insert (new ACLAE ((str = "CLAE"))).first;
//     AtomType::aCLAF = *repository.insert (new ACLAF ((str = "CLAF"))).first;
//     AtomType::aCLAH = *repository.insert (new ACLAH ((str = "CLAH"))).first;
//     AtomType::aCLAR = *repository.insert (new ACLAR ((str = "CLAR"))).first;
//     AtomType::aCLB = *repository.insert (new ACLB ((str = "CLB"))).first;
//     AtomType::aCLC = *repository.insert (new ACLC ((str = "CLC"))).first;
//     AtomType::aCLL = *repository.insert (new ACLL ((str = "CLL"))).first;
//     AtomType::aCM = *repository.insert (new ACM ((str = "CM"))).first;
//     AtomType::aCM" = *repository.insert (new ACM" ((str = "CM""))).first;
//     AtomType::aCM* = *repository.insert (new ACM* ((str = "CM*"))).first;
//     AtomType::aCM0 = *repository.insert (new ACM0 ((str = "CM0"))).first;
    AtomType::aCM1 = *repository.insert (new ACM1 ((str = "CM1"))).first;
//     AtomType::aCM2 = *repository.insert (new ACM2 ((str = "CM2"))).first;
//     AtomType::aCM3 = *repository.insert (new ACM3 ((str = "CM3"))).first;
//     AtomType::aCM3* = *repository.insert (new ACM3* ((str = "CM3*"))).first;
//     AtomType::aCM4 = *repository.insert (new ACM4 ((str = "CM4"))).first;
//     AtomType::aCM5 = *repository.insert (new ACM5 ((str = "CM5"))).first;
//     AtomType::aCM6 = *repository.insert (new ACM6 ((str = "CM6"))).first;
//     AtomType::aCM7 = *repository.insert (new ACM7 ((str = "CM7"))).first;
//     AtomType::aCM8 = *repository.insert (new ACM8 ((str = "CM8"))).first;
//     AtomType::aCM9 = *repository.insert (new ACM9 ((str = "CM9"))).first;
//     AtomType::aCMA = *repository.insert (new ACMA ((str = "CMA"))).first;
//     AtomType::aCMB = *repository.insert (new ACMB ((str = "CMB"))).first;
//     AtomType::aCMC = *repository.insert (new ACMC ((str = "CMC"))).first;
//     AtomType::aCMD = *repository.insert (new ACMD ((str = "CMD"))).first;
//     AtomType::aCME = *repository.insert (new ACME ((str = "CME"))).first;
//     AtomType::aCMF = *repository.insert (new ACMF ((str = "CMF"))).first;
//     AtomType::aCMK = *repository.insert (new ACMK ((str = "CMK"))).first;
//     AtomType::aCMP = *repository.insert (new ACMP ((str = "CMP"))).first;
//     AtomType::aCMZ = *repository.insert (new ACMZ ((str = "CMZ"))).first;
//     AtomType::aCN = *repository.insert (new ACN ((str = "CN"))).first;
//     AtomType::aCN* = *repository.insert (new ACN* ((str = "CN*"))).first;
//     AtomType::aCN1 = *repository.insert (new ACN1 ((str = "CN1"))).first;
//     AtomType::aCN2 = *repository.insert (new ACN2 ((str = "CN2"))).first;
//     AtomType::aCN3 = *repository.insert (new ACN3 ((str = "CN3"))).first;
//     AtomType::aCN4 = *repository.insert (new ACN4 ((str = "CN4"))).first;
//     AtomType::aCN5 = *repository.insert (new ACN5 ((str = "CN5"))).first;
//     AtomType::aCN6 = *repository.insert (new ACN6 ((str = "CN6"))).first;
//     AtomType::aCN7 = *repository.insert (new ACN7 ((str = "CN7"))).first;
//     AtomType::aCN8 = *repository.insert (new ACN8 ((str = "CN8"))).first;
//     AtomType::aCN9 = *repository.insert (new ACN9 ((str = "CN9"))).first;
//     AtomType::aCNA = *repository.insert (new ACNA ((str = "CNA"))).first;
//     AtomType::aCNB = *repository.insert (new ACNB ((str = "CNB"))).first;
//     AtomType::aCNC = *repository.insert (new ACNC ((str = "CNC"))).first;
//     AtomType::aCND = *repository.insert (new ACND ((str = "CND"))).first;
//     AtomType::aCNE = *repository.insert (new ACNE ((str = "CNE"))).first;
//     AtomType::aCNF = *repository.insert (new ACNF ((str = "CNF"))).first;
//     AtomType::aCNM = *repository.insert (new ACNM ((str = "CNM"))).first;
//     AtomType::aCNV = *repository.insert (new ACNV ((str = "CNV"))).first;
//     AtomType::aCO = *repository.insert (new ACO ((str = "CO"))).first;
//     AtomType::aCO* = *repository.insert (new ACO* ((str = "CO*"))).first;
//     AtomType::aCO1 = *repository.insert (new ACO1 ((str = "CO1"))).first;
//     AtomType::aCO2 = *repository.insert (new ACO2 ((str = "CO2"))).first;
//     AtomType::aCO2* = *repository.insert (new ACO2* ((str = "CO2*"))).first;
//     AtomType::aCO3 = *repository.insert (new ACO3 ((str = "CO3"))).first;
//     AtomType::aCO3* = *repository.insert (new ACO3* ((str = "CO3*"))).first;
//     AtomType::aCO4 = *repository.insert (new ACO4 ((str = "CO4"))).first;
//     AtomType::aCO4* = *repository.insert (new ACO4* ((str = "CO4*"))).first;
//     AtomType::aCO5 = *repository.insert (new ACO5 ((str = "CO5"))).first;
//     AtomType::aCO5* = *repository.insert (new ACO5* ((str = "CO5*"))).first;
//     AtomType::aCO6 = *repository.insert (new ACO6 ((str = "CO6"))).first;
//     AtomType::aCO9 = *repository.insert (new ACO9 ((str = "CO9"))).first;
//     AtomType::aCOG = *repository.insert (new ACOG ((str = "COG"))).first;
//     AtomType::aCOH = *repository.insert (new ACOH ((str = "COH"))).first;
//     AtomType::aCOM = *repository.insert (new ACOM ((str = "COM"))).first;
//     AtomType::aCOO = *repository.insert (new ACOO ((str = "COO"))).first;
//     AtomType::aCP = *repository.insert (new ACP ((str = "CP"))).first;
//     AtomType::aCP1 = *repository.insert (new ACP1 ((str = "CP1"))).first;
//     AtomType::aCP2 = *repository.insert (new ACP2 ((str = "CP2"))).first;
//     AtomType::aCP3 = *repository.insert (new ACP3 ((str = "CP3"))).first;
//     AtomType::aCP4 = *repository.insert (new ACP4 ((str = "CP4"))).first;
//     AtomType::aCP5 = *repository.insert (new ACP5 ((str = "CP5"))).first;
//     AtomType::aCP6 = *repository.insert (new ACP6 ((str = "CP6"))).first;
//     AtomType::aCP7 = *repository.insert (new ACP7 ((str = "CP7"))).first;
//     AtomType::aCP8 = *repository.insert (new ACP8 ((str = "CP8"))).first;
//     AtomType::aCP9 = *repository.insert (new ACP9 ((str = "CP9"))).first;
//     AtomType::aCPA = *repository.insert (new ACPA ((str = "CPA"))).first;
//     AtomType::aCPB = *repository.insert (new ACPB ((str = "CPB"))).first;
//     AtomType::aCPC = *repository.insert (new ACPC ((str = "CPC"))).first;
//     AtomType::aCPD = *repository.insert (new ACPD ((str = "CPD"))).first;
//     AtomType::aCPE = *repository.insert (new ACPE ((str = "CPE"))).first;
//     AtomType::aCPF = *repository.insert (new ACPF ((str = "CPF"))).first;
//     AtomType::aCPG = *repository.insert (new ACPG ((str = "CPG"))).first;
//     AtomType::aCPH = *repository.insert (new ACPH ((str = "CPH"))).first;
//     AtomType::aCPI = *repository.insert (new ACPI ((str = "CPI"))).first;
//     AtomType::aCPK = *repository.insert (new ACPK ((str = "CPK"))).first;
//     AtomType::aCPM = *repository.insert (new ACPM ((str = "CPM"))).first;
//     AtomType::aCPO = *repository.insert (new ACPO ((str = "CPO"))).first;
//     AtomType::aCPP = *repository.insert (new ACPP ((str = "CPP"))).first;
//     AtomType::aCPQ = *repository.insert (new ACPQ ((str = "CPQ"))).first;
//     AtomType::aCPR = *repository.insert (new ACPR ((str = "CPR"))).first;
//     AtomType::aCPS = *repository.insert (new ACPS ((str = "CPS"))).first;
//     AtomType::aCPT = *repository.insert (new ACPT ((str = "CPT"))).first;
//     AtomType::aCQ = *repository.insert (new ACQ ((str = "CQ"))).first;
//     AtomType::aCQ1 = *repository.insert (new ACQ1 ((str = "CQ1"))).first;
//     AtomType::aCQ2 = *repository.insert (new ACQ2 ((str = "CQ2"))).first;
//     AtomType::aCQ3 = *repository.insert (new ACQ3 ((str = "CQ3"))).first;
//     AtomType::aCQ4 = *repository.insert (new ACQ4 ((str = "CQ4"))).first;
//     AtomType::aCQ5 = *repository.insert (new ACQ5 ((str = "CQ5"))).first;
//     AtomType::aCQ6 = *repository.insert (new ACQ6 ((str = "CQ6"))).first;
//     AtomType::aCQ7 = *repository.insert (new ACQ7 ((str = "CQ7"))).first;
//     AtomType::aCQA = *repository.insert (new ACQA ((str = "CQA"))).first;
//     AtomType::aCQB = *repository.insert (new ACQB ((str = "CQB"))).first;
//     AtomType::aCR = *repository.insert (new ACR ((str = "CR"))).first;
//     AtomType::aCR1 = *repository.insert (new ACR1 ((str = "CR1"))).first;
//     AtomType::aCR10 = *repository.insert (new ACR10 ((str = "CR10"))).first;
//     AtomType::aCR11 = *repository.insert (new ACR11 ((str = "CR11"))).first;
//     AtomType::aCR12 = *repository.insert (new ACR12 ((str = "CR12"))).first;
//     AtomType::aCR13 = *repository.insert (new ACR13 ((str = "CR13"))).first;
//     AtomType::aCR14 = *repository.insert (new ACR14 ((str = "CR14"))).first;
//     AtomType::aCR15 = *repository.insert (new ACR15 ((str = "CR15"))).first;
//     AtomType::aCR16 = *repository.insert (new ACR16 ((str = "CR16"))).first;
//     AtomType::aCR17 = *repository.insert (new ACR17 ((str = "CR17"))).first;
//     AtomType::aCR2 = *repository.insert (new ACR2 ((str = "CR2"))).first;
//     AtomType::aCR3 = *repository.insert (new ACR3 ((str = "CR3"))).first;
//     AtomType::aCR4 = *repository.insert (new ACR4 ((str = "CR4"))).first;
//     AtomType::aCR5 = *repository.insert (new ACR5 ((str = "CR5"))).first;
//     AtomType::aCR6 = *repository.insert (new ACR6 ((str = "CR6"))).first;
//     AtomType::aCR7 = *repository.insert (new ACR7 ((str = "CR7"))).first;
//     AtomType::aCR8 = *repository.insert (new ACR8 ((str = "CR8"))).first;
//     AtomType::aCR9 = *repository.insert (new ACR9 ((str = "CR9"))).first;
//     AtomType::aCS = *repository.insert (new ACS ((str = "CS"))).first;
//     AtomType::aCS1 = *repository.insert (new ACS1 ((str = "CS1"))).first;
//     AtomType::aCS2 = *repository.insert (new ACS2 ((str = "CS2"))).first;
//     AtomType::aCS3 = *repository.insert (new ACS3 ((str = "CS3"))).first;
//     AtomType::aCS4 = *repository.insert (new ACS4 ((str = "CS4"))).first;
//     AtomType::aCS5 = *repository.insert (new ACS5 ((str = "CS5"))).first;
//     AtomType::aCS6 = *repository.insert (new ACS6 ((str = "CS6"))).first;
//     AtomType::aCSA = *repository.insert (new ACSA ((str = "CSA"))).first;
//     AtomType::aCSD = *repository.insert (new ACSD ((str = "CSD"))).first;
//     AtomType::aCSS = *repository.insert (new ACSS ((str = "CSS"))).first;
//     AtomType::aCT = *repository.insert (new ACT ((str = "CT"))).first;
//     AtomType::aCT0 = *repository.insert (new ACT0 ((str = "CT0"))).first;
//     AtomType::aCT1 = *repository.insert (new ACT1 ((str = "CT1"))).first;
//     AtomType::aCT2 = *repository.insert (new ACT2 ((str = "CT2"))).first;
//     AtomType::aCT3 = *repository.insert (new ACT3 ((str = "CT3"))).first;
//     AtomType::aCT4 = *repository.insert (new ACT4 ((str = "CT4"))).first;
//     AtomType::aCT5 = *repository.insert (new ACT5 ((str = "CT5"))).first;
//     AtomType::aCT6 = *repository.insert (new ACT6 ((str = "CT6"))).first;
//     AtomType::aCT7 = *repository.insert (new ACT7 ((str = "CT7"))).first;
//     AtomType::aCT8 = *repository.insert (new ACT8 ((str = "CT8"))).first;
//     AtomType::aCT9 = *repository.insert (new ACT9 ((str = "CT9"))).first;
//     AtomType::aCU = *repository.insert (new ACU ((str = "CU"))).first;
//     AtomType::aCU1 = *repository.insert (new ACU1 ((str = "CU1"))).first;
//     AtomType::aCU2 = *repository.insert (new ACU2 ((str = "CU2"))).first;
//     AtomType::aCU3 = *repository.insert (new ACU3 ((str = "CU3"))).first;
//     AtomType::aCU4 = *repository.insert (new ACU4 ((str = "CU4"))).first;
//     AtomType::aCV = *repository.insert (new ACV ((str = "CV"))).first;
//     AtomType::aCV1 = *repository.insert (new ACV1 ((str = "CV1"))).first;
//     AtomType::aCV2 = *repository.insert (new ACV2 ((str = "CV2"))).first;
//     AtomType::aCV3 = *repository.insert (new ACV3 ((str = "CV3"))).first;
//     AtomType::aCV4 = *repository.insert (new ACV4 ((str = "CV4"))).first;
//     AtomType::aCV5 = *repository.insert (new ACV5 ((str = "CV5"))).first;
//     AtomType::aCV6 = *repository.insert (new ACV6 ((str = "CV6"))).first;
//     AtomType::aCV7 = *repository.insert (new ACV7 ((str = "CV7"))).first;
//     AtomType::aCV8 = *repository.insert (new ACV8 ((str = "CV8"))).first;
//     AtomType::aCV9 = *repository.insert (new ACV9 ((str = "CV9"))).first;
//     AtomType::aCVA = *repository.insert (new ACVA ((str = "CVA"))).first;
//     AtomType::aCVB = *repository.insert (new ACVB ((str = "CVB"))).first;
//     AtomType::aCW = *repository.insert (new ACW ((str = "CW"))).first;
//     AtomType::aCW1 = *repository.insert (new ACW1 ((str = "CW1"))).first;
//     AtomType::aCW2 = *repository.insert (new ACW2 ((str = "CW2"))).first;
//     AtomType::aCW3 = *repository.insert (new ACW3 ((str = "CW3"))).first;
//     AtomType::aCW4 = *repository.insert (new ACW4 ((str = "CW4"))).first;
//     AtomType::aCW5 = *repository.insert (new ACW5 ((str = "CW5"))).first;
//     AtomType::aCW6 = *repository.insert (new ACW6 ((str = "CW6"))).first;
//     AtomType::aCX = *repository.insert (new ACX ((str = "CX"))).first;
//     AtomType::aCX* = *repository.insert (new ACX* ((str = "CX*"))).first;
//     AtomType::aCX1 = *repository.insert (new ACX1 ((str = "CX1"))).first;
//     AtomType::aCX10 = *repository.insert (new ACX10 ((str = "CX10"))).first;
//     AtomType::aCX11 = *repository.insert (new ACX11 ((str = "CX11"))).first;
//     AtomType::aCX12 = *repository.insert (new ACX12 ((str = "CX12"))).first;
//     AtomType::aCX2 = *repository.insert (new ACX2 ((str = "CX2"))).first;
//     AtomType::aCX3 = *repository.insert (new ACX3 ((str = "CX3"))).first;
//     AtomType::aCX4 = *repository.insert (new ACX4 ((str = "CX4"))).first;
//     AtomType::aCX5 = *repository.insert (new ACX5 ((str = "CX5"))).first;
//     AtomType::aCX6 = *repository.insert (new ACX6 ((str = "CX6"))).first;
//     AtomType::aCX7 = *repository.insert (new ACX7 ((str = "CX7"))).first;
//     AtomType::aCX8 = *repository.insert (new ACX8 ((str = "CX8"))).first;
//     AtomType::aCX9 = *repository.insert (new ACX9 ((str = "CX9"))).first;
//     AtomType::aCXA = *repository.insert (new ACXA ((str = "CXA"))).first;
//     AtomType::aCXB = *repository.insert (new ACXB ((str = "CXB"))).first;
//     AtomType::aCXC = *repository.insert (new ACXC ((str = "CXC"))).first;
//     AtomType::aCXD = *repository.insert (new ACXD ((str = "CXD"))).first;
//     AtomType::aCXE = *repository.insert (new ACXE ((str = "CXE"))).first;
//     AtomType::aCXF = *repository.insert (new ACXF ((str = "CXF"))).first;
//     AtomType::aCXG = *repository.insert (new ACXG ((str = "CXG"))).first;
//     AtomType::aCXT = *repository.insert (new ACXT ((str = "CXT"))).first;
//     AtomType::aCY = *repository.insert (new ACY ((str = "CY"))).first;
//     AtomType::aCY1 = *repository.insert (new ACY1 ((str = "CY1"))).first;
//     AtomType::aCY2 = *repository.insert (new ACY2 ((str = "CY2"))).first;
//     AtomType::aCY3 = *repository.insert (new ACY3 ((str = "CY3"))).first;
//     AtomType::aCY4 = *repository.insert (new ACY4 ((str = "CY4"))).first;
//     AtomType::aCY5 = *repository.insert (new ACY5 ((str = "CY5"))).first;
//     AtomType::aCY6 = *repository.insert (new ACY6 ((str = "CY6"))).first;
//     AtomType::aCY7 = *repository.insert (new ACY7 ((str = "CY7"))).first;
//     AtomType::aCYH = *repository.insert (new ACYH ((str = "CYH"))).first;
//     AtomType::aCYT = *repository.insert (new ACYT ((str = "CYT"))).first;
//     AtomType::aCZ = *repository.insert (new ACZ ((str = "CZ"))).first;
//     AtomType::aCZ* = *repository.insert (new ACZ* ((str = "CZ*"))).first;
//     AtomType::aCZ1 = *repository.insert (new ACZ1 ((str = "CZ1"))).first;
//     AtomType::aCZ10 = *repository.insert (new ACZ10 ((str = "CZ10"))).first;
//     AtomType::aCZ11 = *repository.insert (new ACZ11 ((str = "CZ11"))).first;
//     AtomType::aCZ12 = *repository.insert (new ACZ12 ((str = "CZ12"))).first;
//     AtomType::aCZ13 = *repository.insert (new ACZ13 ((str = "CZ13"))).first;
//     AtomType::aCZ14 = *repository.insert (new ACZ14 ((str = "CZ14"))).first;
//     AtomType::aCZ15 = *repository.insert (new ACZ15 ((str = "CZ15"))).first;
//     AtomType::aCZ2 = *repository.insert (new ACZ2 ((str = "CZ2"))).first;
//     AtomType::aCZ2T = *repository.insert (new ACZ2T ((str = "CZ2T"))).first;
//     AtomType::aCZ3 = *repository.insert (new ACZ3 ((str = "CZ3"))).first;
//     AtomType::aCZ3T = *repository.insert (new ACZ3T ((str = "CZ3T"))).first;
//     AtomType::aCZ4 = *repository.insert (new ACZ4 ((str = "CZ4"))).first;
//     AtomType::aCZ5 = *repository.insert (new ACZ5 ((str = "CZ5"))).first;
//     AtomType::aCZ6 = *repository.insert (new ACZ6 ((str = "CZ6"))).first;
//     AtomType::aCZ7 = *repository.insert (new ACZ7 ((str = "CZ7"))).first;
//     AtomType::aCZ8 = *repository.insert (new ACZ8 ((str = "CZ8"))).first;
//     AtomType::aCZ9 = *repository.insert (new ACZ9 ((str = "CZ9"))).first;
//     AtomType::aCZA = *repository.insert (new ACZA ((str = "CZA"))).first;
//     AtomType::aCZH = *repository.insert (new ACZH ((str = "CZH"))).first;
//     AtomType::aCZY = *repository.insert (new ACZY ((str = "CZY"))).first;
//     AtomType::aC_1 = *repository.insert (new AC_1 ((str = "C_1"))).first;
//     AtomType::aC_2 = *repository.insert (new AC_2 ((str = "C_2"))).first;
//     AtomType::aC_3 = *repository.insert (new AC_3 ((str = "C_3"))).first;
//     AtomType::aC_4 = *repository.insert (new AC_4 ((str = "C_4"))).first;
//     AtomType::aC_5 = *repository.insert (new AC_5 ((str = "C_5"))).first;
//     AtomType::aC_6 = *repository.insert (new AC_6 ((str = "C_6"))).first;
//     AtomType::aC_7 = *repository.insert (new AC_7 ((str = "C_7"))).first;
//     AtomType::aC_8 = *repository.insert (new AC_8 ((str = "C_8"))).first;
//     AtomType::aC_9 = *repository.insert (new AC_9 ((str = "C_9"))).first;
//     AtomType::aD1A = *repository.insert (new AD1A ((str = "D1A"))).first;
//     AtomType::aD1B = *repository.insert (new AD1B ((str = "D1B"))).first;
//     AtomType::aD1C = *repository.insert (new AD1C ((str = "D1C"))).first;
//     AtomType::aD5A = *repository.insert (new AD5A ((str = "D5A"))).first;
//     AtomType::aD5B = *repository.insert (new AD5B ((str = "D5B"))).first;
//     AtomType::aDC1 = *repository.insert (new ADC1 ((str = "DC1"))).first;
//     AtomType::aDC2 = *repository.insert (new ADC2 ((str = "DC2"))).first;
//     AtomType::aDC3 = *repository.insert (new ADC3 ((str = "DC3"))).first;
//     AtomType::aDC4 = *repository.insert (new ADC4 ((str = "DC4"))).first;
//     AtomType::aDC5 = *repository.insert (new ADC5 ((str = "DC5"))).first;
//     AtomType::aDC6 = *repository.insert (new ADC6 ((str = "DC6"))).first;
//     AtomType::aDHO1 = *repository.insert (new ADHO1 ((str = "DHO1"))).first;
//     AtomType::aDHO2 = *repository.insert (new ADHO2 ((str = "DHO2"))).first;
//     AtomType::aDHO3 = *repository.insert (new ADHO3 ((str = "DHO3"))).first;
//     AtomType::aDHO4 = *repository.insert (new ADHO4 ((str = "DHO4"))).first;
//     AtomType::aDHO5 = *repository.insert (new ADHO5 ((str = "DHO5"))).first;
//     AtomType::aDHO6 = *repository.insert (new ADHO6 ((str = "DHO6"))).first;
//     AtomType::aDO2 = *repository.insert (new ADO2 ((str = "DO2"))).first;
//     AtomType::aDO3 = *repository.insert (new ADO3 ((str = "DO3"))).first;
//     AtomType::aDO4 = *repository.insert (new ADO4 ((str = "DO4"))).first;
//     AtomType::aDO5 = *repository.insert (new ADO5 ((str = "DO5"))).first;
//     AtomType::aDO6 = *repository.insert (new ADO6 ((str = "DO6"))).first;
//     AtomType::aEC1 = *repository.insert (new AEC1 ((str = "EC1"))).first;
//     AtomType::aEC2 = *repository.insert (new AEC2 ((str = "EC2"))).first;
//     AtomType::aEC3 = *repository.insert (new AEC3 ((str = "EC3"))).first;
//     AtomType::aEC4 = *repository.insert (new AEC4 ((str = "EC4"))).first;
//     AtomType::aEC5 = *repository.insert (new AEC5 ((str = "EC5"))).first;
//     AtomType::aEC6 = *repository.insert (new AEC6 ((str = "EC6"))).first;
//     AtomType::aEH2 = *repository.insert (new AEH2 ((str = "EH2"))).first;
//     AtomType::aEH23 = *repository.insert (new AEH23 ((str = "EH23"))).first;
//     AtomType::aEHN1 = *repository.insert (new AEHN1 ((str = "EHN1"))).first;
//     AtomType::aEHN2 = *repository.insert (new AEHN2 ((str = "EHN2"))).first;
//     AtomType::aEHO1 = *repository.insert (new AEHO1 ((str = "EHO1"))).first;
//     AtomType::aEHO2 = *repository.insert (new AEHO2 ((str = "EHO2"))).first;
//     AtomType::aEHO3 = *repository.insert (new AEHO3 ((str = "EHO3"))).first;
//     AtomType::aEHO4 = *repository.insert (new AEHO4 ((str = "EHO4"))).first;
//     AtomType::aEHO5 = *repository.insert (new AEHO5 ((str = "EHO5"))).first;
//     AtomType::aEHO6 = *repository.insert (new AEHO6 ((str = "EHO6"))).first;
//     AtomType::aEO1 = *repository.insert (new AEO1 ((str = "EO1"))).first;
//     AtomType::aEO2 = *repository.insert (new AEO2 ((str = "EO2"))).first;
//     AtomType::aEO3 = *repository.insert (new AEO3 ((str = "EO3"))).first;
//     AtomType::aEO4 = *repository.insert (new AEO4 ((str = "EO4"))).first;
//     AtomType::aEO5 = *repository.insert (new AEO5 ((str = "EO5"))).first;
//     AtomType::aEO6 = *repository.insert (new AEO6 ((str = "EO6"))).first;
//     AtomType::aF = *repository.insert (new AF ((str = "F"))).first;
//     AtomType::aF01 = *repository.insert (new AF01 ((str = "F01"))).first;
//     AtomType::aF02 = *repository.insert (new AF02 ((str = "F02"))).first;
//     AtomType::aF03 = *repository.insert (new AF03 ((str = "F03"))).first;
//     AtomType::aF08 = *repository.insert (new AF08 ((str = "F08"))).first;
//     AtomType::aF1 = *repository.insert (new AF1 ((str = "F1"))).first;
//     AtomType::aF1* = *repository.insert (new AF1* ((str = "F1*"))).first;
//     AtomType::aF10 = *repository.insert (new AF10 ((str = "F10"))).first;
//     AtomType::aF11 = *repository.insert (new AF11 ((str = "F11"))).first;
//     AtomType::aF12 = *repository.insert (new AF12 ((str = "F12"))).first;
//     AtomType::aF13 = *repository.insert (new AF13 ((str = "F13"))).first;
//     AtomType::aF14 = *repository.insert (new AF14 ((str = "F14"))).first;
//     AtomType::aF15 = *repository.insert (new AF15 ((str = "F15"))).first;
//     AtomType::aF16 = *repository.insert (new AF16 ((str = "F16"))).first;
//     AtomType::aF17 = *repository.insert (new AF17 ((str = "F17"))).first;
//     AtomType::aF18 = *repository.insert (new AF18 ((str = "F18"))).first;
//     AtomType::aF19 = *repository.insert (new AF19 ((str = "F19"))).first;
//     AtomType::aF1B = *repository.insert (new AF1B ((str = "F1B"))).first;
//     AtomType::aF1O = *repository.insert (new AF1O ((str = "F1O"))).first;
//     AtomType::aF1P = *repository.insert (new AF1P ((str = "F1P"))).first;
//     AtomType::aF1Q = *repository.insert (new AF1Q ((str = "F1Q"))).first;
//     AtomType::aF2 = *repository.insert (new AF2 ((str = "F2"))).first;
//     AtomType::aF2* = *repository.insert (new AF2* ((str = "F2*"))).first;
//     AtomType::aF2** = *repository.insert (new AF2** ((str = "F2**"))).first;
//     AtomType::aF20 = *repository.insert (new AF20 ((str = "F20"))).first;
//     AtomType::aF21 = *repository.insert (new AF21 ((str = "F21"))).first;
//     AtomType::aF22 = *repository.insert (new AF22 ((str = "F22"))).first;
//     AtomType::aF23 = *repository.insert (new AF23 ((str = "F23"))).first;
//     AtomType::aF24 = *repository.insert (new AF24 ((str = "F24"))).first;
//     AtomType::aF25 = *repository.insert (new AF25 ((str = "F25"))).first;
//     AtomType::aF26 = *repository.insert (new AF26 ((str = "F26"))).first;
//     AtomType::aF27 = *repository.insert (new AF27 ((str = "F27"))).first;
//     AtomType::aF28 = *repository.insert (new AF28 ((str = "F28"))).first;
//     AtomType::aF29 = *repository.insert (new AF29 ((str = "F29"))).first;
//     AtomType::aF2A = *repository.insert (new AF2A ((str = "F2A"))).first;
//     AtomType::aF2B = *repository.insert (new AF2B ((str = "F2B"))).first;
//     AtomType::aF2G = *repository.insert (new AF2G ((str = "F2G"))).first;
//     AtomType::aF3 = *repository.insert (new AF3 ((str = "F3"))).first;
//     AtomType::aF3* = *repository.insert (new AF3* ((str = "F3*"))).first;
//     AtomType::aF30 = *repository.insert (new AF30 ((str = "F30"))).first;
//     AtomType::aF31 = *repository.insert (new AF31 ((str = "F31"))).first;
//     AtomType::aF31* = *repository.insert (new AF31* ((str = "F31*"))).first;
//     AtomType::aF32 = *repository.insert (new AF32 ((str = "F32"))).first;
//     AtomType::aF32* = *repository.insert (new AF32* ((str = "F32*"))).first;
//     AtomType::aF33 = *repository.insert (new AF33 ((str = "F33"))).first;
//     AtomType::aF33* = *repository.insert (new AF33* ((str = "F33*"))).first;
//     AtomType::aF34 = *repository.insert (new AF34 ((str = "F34"))).first;
//     AtomType::aF35 = *repository.insert (new AF35 ((str = "F35"))).first;
//     AtomType::aF36 = *repository.insert (new AF36 ((str = "F36"))).first;
//     AtomType::aF37 = *repository.insert (new AF37 ((str = "F37"))).first;
//     AtomType::aF38 = *repository.insert (new AF38 ((str = "F38"))).first;
//     AtomType::aF39 = *repository.insert (new AF39 ((str = "F39"))).first;
//     AtomType::aF3A = *repository.insert (new AF3A ((str = "F3A"))).first;
//     AtomType::aF4 = *repository.insert (new AF4 ((str = "F4"))).first;
//     AtomType::aF4* = *repository.insert (new AF4* ((str = "F4*"))).first;
//     AtomType::aF40 = *repository.insert (new AF40 ((str = "F40"))).first;
//     AtomType::aF41 = *repository.insert (new AF41 ((str = "F41"))).first;
//     AtomType::aF42 = *repository.insert (new AF42 ((str = "F42"))).first;
//     AtomType::aF43 = *repository.insert (new AF43 ((str = "F43"))).first;
//     AtomType::aF44 = *repository.insert (new AF44 ((str = "F44"))).first;
//     AtomType::aF45 = *repository.insert (new AF45 ((str = "F45"))).first;
//     AtomType::aF46 = *repository.insert (new AF46 ((str = "F46"))).first;
//     AtomType::aF47 = *repository.insert (new AF47 ((str = "F47"))).first;
//     AtomType::aF48 = *repository.insert (new AF48 ((str = "F48"))).first;
//     AtomType::aF49 = *repository.insert (new AF49 ((str = "F49"))).first;
//     AtomType::aF5 = *repository.insert (new AF5 ((str = "F5"))).first;
//     AtomType::aF50 = *repository.insert (new AF50 ((str = "F50"))).first;
//     AtomType::aF51 = *repository.insert (new AF51 ((str = "F51"))).first;
//     AtomType::aF52 = *repository.insert (new AF52 ((str = "F52"))).first;
//     AtomType::aF53 = *repository.insert (new AF53 ((str = "F53"))).first;
//     AtomType::aF54 = *repository.insert (new AF54 ((str = "F54"))).first;
//     AtomType::aF56 = *repository.insert (new AF56 ((str = "F56"))).first;
//     AtomType::aF57 = *repository.insert (new AF57 ((str = "F57"))).first;
//     AtomType::aF58 = *repository.insert (new AF58 ((str = "F58"))).first;
//     AtomType::aF59 = *repository.insert (new AF59 ((str = "F59"))).first;
//     AtomType::aF6 = *repository.insert (new AF6 ((str = "F6"))).first;
//     AtomType::aF61 = *repository.insert (new AF61 ((str = "F61"))).first;
//     AtomType::aF66 = *repository.insert (new AF66 ((str = "F66"))).first;
//     AtomType::aF67 = *repository.insert (new AF67 ((str = "F67"))).first;
//     AtomType::aF7 = *repository.insert (new AF7 ((str = "F7"))).first;
//     AtomType::aF75 = *repository.insert (new AF75 ((str = "F75"))).first;
//     AtomType::aF76 = *repository.insert (new AF76 ((str = "F76"))).first;
//     AtomType::aF78 = *repository.insert (new AF78 ((str = "F78"))).first;
//     AtomType::aF79 = *repository.insert (new AF79 ((str = "F79"))).first;
//     AtomType::aF7A = *repository.insert (new AF7A ((str = "F7A"))).first;
//     AtomType::aF7B = *repository.insert (new AF7B ((str = "F7B"))).first;
//     AtomType::aF7C = *repository.insert (new AF7C ((str = "F7C"))).first;
//     AtomType::aF8 = *repository.insert (new AF8 ((str = "F8"))).first;
//     AtomType::aF80 = *repository.insert (new AF80 ((str = "F80"))).first;
//     AtomType::aF89 = *repository.insert (new AF89 ((str = "F89"))).first;
//     AtomType::aF8B = *repository.insert (new AF8B ((str = "F8B"))).first;
//     AtomType::aF9 = *repository.insert (new AF9 ((str = "F9"))).first;
//     AtomType::aF96 = *repository.insert (new AF96 ((str = "F96"))).first;
//     AtomType::aF9B = *repository.insert (new AF9B ((str = "F9B"))).first;
//     AtomType::aFA1 = *repository.insert (new AFA1 ((str = "FA1"))).first;
//     AtomType::aFAA = *repository.insert (new AFAA ((str = "FAA"))).first;
//     AtomType::aFAB = *repository.insert (new AFAB ((str = "FAB"))).first;
//     AtomType::aFAC = *repository.insert (new AFAC ((str = "FAC"))).first;
//     AtomType::aFAD = *repository.insert (new AFAD ((str = "FAD"))).first;
//     AtomType::aFAE = *repository.insert (new AFAE ((str = "FAE"))).first;
//     AtomType::aFAF = *repository.insert (new AFAF ((str = "FAF"))).first;
//     AtomType::aFAG = *repository.insert (new AFAG ((str = "FAG"))).first;
//     AtomType::aFAP = *repository.insert (new AFAP ((str = "FAP"))).first;
//     AtomType::aFAT = *repository.insert (new AFAT ((str = "FAT"))).first;
//     AtomType::aFAV = *repository.insert (new AFAV ((str = "FAV"))).first;
//     AtomType::aFAW = *repository.insert (new AFAW ((str = "FAW"))).first;
//     AtomType::aFAX = *repository.insert (new AFAX ((str = "FAX"))).first;
//     AtomType::aFB1 = *repository.insert (new AFB1 ((str = "FB1"))).first;
//     AtomType::aFB2 = *repository.insert (new AFB2 ((str = "FB2"))).first;
//     AtomType::aFB3 = *repository.insert (new AFB3 ((str = "FB3"))).first;
//     AtomType::aFB7 = *repository.insert (new AFB7 ((str = "FB7"))).first;
//     AtomType::aFBE = *repository.insert (new AFBE ((str = "FBE"))).first;
//     AtomType::aFBF = *repository.insert (new AFBF ((str = "FBF"))).first;
//     AtomType::aFBG = *repository.insert (new AFBG ((str = "FBG"))).first;
//     AtomType::aFC* = *repository.insert (new AFC* ((str = "FC*"))).first;
//     AtomType::aFD* = *repository.insert (new AFD* ((str = "FD*"))).first;
//     AtomType::aFD1 = *repository.insert (new AFD1 ((str = "FD1"))).first;
//     AtomType::aFD2 = *repository.insert (new AFD2 ((str = "FD2"))).first;
//     AtomType::aFD3 = *repository.insert (new AFD3 ((str = "FD3"))).first;
//     AtomType::aFE = *repository.insert (new AFE ((str = "FE"))).first;
//     AtomType::aFE* = *repository.insert (new AFE* ((str = "FE*"))).first;
//     AtomType::aFE1 = *repository.insert (new AFE1 ((str = "FE1"))).first;
//     AtomType::aFE2 = *repository.insert (new AFE2 ((str = "FE2"))).first;
//     AtomType::aFE3 = *repository.insert (new AFE3 ((str = "FE3"))).first;
//     AtomType::aFE4 = *repository.insert (new AFE4 ((str = "FE4"))).first;
//     AtomType::aFE5 = *repository.insert (new AFE5 ((str = "FE5"))).first;
//     AtomType::aFE6 = *repository.insert (new AFE6 ((str = "FE6"))).first;
//     AtomType::aFE7 = *repository.insert (new AFE7 ((str = "FE7"))).first;
//     AtomType::aFE8 = *repository.insert (new AFE8 ((str = "FE8"))).first;
//     AtomType::aFF* = *repository.insert (new AFF* ((str = "FF*"))).first;
//     AtomType::aFG1 = *repository.insert (new AFG1 ((str = "FG1"))).first;
//     AtomType::aFG2 = *repository.insert (new AFG2 ((str = "FG2"))).first;
//     AtomType::aFHO2 = *repository.insert (new AFHO2 ((str = "FHO2"))).first;
//     AtomType::aFHO3 = *repository.insert (new AFHO3 ((str = "FHO3"))).first;
//     AtomType::aFHO6 = *repository.insert (new AFHO6 ((str = "FHO6"))).first;
//     AtomType::aFL1 = *repository.insert (new AFL1 ((str = "FL1"))).first;
//     AtomType::aFL2 = *repository.insert (new AFL2 ((str = "FL2"))).first;
//     AtomType::aFZ = *repository.insert (new AFZ ((str = "FZ"))).first;
//     AtomType::aFZ1 = *repository.insert (new AFZ1 ((str = "FZ1"))).first;
//     AtomType::aFZ2 = *repository.insert (new AFZ2 ((str = "FZ2"))).first;
//     AtomType::aFZ3 = *repository.insert (new AFZ3 ((str = "FZ3"))).first;
//     AtomType::aGA = *repository.insert (new AGA ((str = "GA"))).first;
//     AtomType::aGC1 = *repository.insert (new AGC1 ((str = "GC1"))).first;
//     AtomType::aGC1* = *repository.insert (new AGC1* ((str = "GC1*"))).first;
//     AtomType::aGC2 = *repository.insert (new AGC2 ((str = "GC2"))).first;
//     AtomType::aGC2* = *repository.insert (new AGC2* ((str = "GC2*"))).first;
//     AtomType::aGC3 = *repository.insert (new AGC3 ((str = "GC3"))).first;
//     AtomType::aGC3* = *repository.insert (new AGC3* ((str = "GC3*"))).first;
//     AtomType::aGC4 = *repository.insert (new AGC4 ((str = "GC4"))).first;
//     AtomType::aGC4* = *repository.insert (new AGC4* ((str = "GC4*"))).first;
//     AtomType::aGC5 = *repository.insert (new AGC5 ((str = "GC5"))).first;
//     AtomType::aGC5* = *repository.insert (new AGC5* ((str = "GC5*"))).first;
//     AtomType::aGC6 = *repository.insert (new AGC6 ((str = "GC6"))).first;
//     AtomType::aGC8 = *repository.insert (new AGC8 ((str = "GC8"))).first;
//     AtomType::aGF2* = *repository.insert (new AGF2* ((str = "GF2*"))).first;
//     AtomType::aGH1 = *repository.insert (new AGH1 ((str = "GH1"))).first;
//     AtomType::aGH1* = *repository.insert (new AGH1* ((str = "GH1*"))).first;
//     AtomType::aGH2* = *repository.insert (new AGH2* ((str = "GH2*"))).first;
//     AtomType::aGH21 = *repository.insert (new AGH21 ((str = "GH21"))).first;
//     AtomType::aGH22 = *repository.insert (new AGH22 ((str = "GH22"))).first;
//     AtomType::aGH3* = *repository.insert (new AGH3* ((str = "GH3*"))).first;
//     AtomType::aGH4* = *repository.insert (new AGH4* ((str = "GH4*"))).first;
//     AtomType::aGH51 = *repository.insert (new AGH51 ((str = "GH51"))).first;
//     AtomType::aGH52 = *repository.insert (new AGH52 ((str = "GH52"))).first;
//     AtomType::aGH8 = *repository.insert (new AGH8 ((str = "GH8"))).first;
//     AtomType::aGHN1 = *repository.insert (new AGHN1 ((str = "GHN1"))).first;
//     AtomType::aGHN2 = *repository.insert (new AGHN2 ((str = "GHN2"))).first;
//     AtomType::aGHO2 = *repository.insert (new AGHO2 ((str = "GHO2"))).first;
//     AtomType::aGHO3 = *repository.insert (new AGHO3 ((str = "GHO3"))).first;
//     AtomType::aGHO4 = *repository.insert (new AGHO4 ((str = "GHO4"))).first;
//     AtomType::aGHO5 = *repository.insert (new AGHO5 ((str = "GHO5"))).first;
//     AtomType::aGN1 = *repository.insert (new AGN1 ((str = "GN1"))).first;
//     AtomType::aGN2 = *repository.insert (new AGN2 ((str = "GN2"))).first;
//     AtomType::aGN3 = *repository.insert (new AGN3 ((str = "GN3"))).first;
//     AtomType::aGN7 = *repository.insert (new AGN7 ((str = "GN7"))).first;
//     AtomType::aGN9 = *repository.insert (new AGN9 ((str = "GN9"))).first;
//     AtomType::aGO1 = *repository.insert (new AGO1 ((str = "GO1"))).first;
//     AtomType::aGO2 = *repository.insert (new AGO2 ((str = "GO2"))).first;
//     AtomType::aGO3 = *repository.insert (new AGO3 ((str = "GO3"))).first;
//     AtomType::aGO3* = *repository.insert (new AGO3* ((str = "GO3*"))).first;
//     AtomType::aGO4* = *repository.insert (new AGO4* ((str = "GO4*"))).first;
//     AtomType::aGO5* = *repository.insert (new AGO5* ((str = "GO5*"))).first;
//     AtomType::aGO6 = *repository.insert (new AGO6 ((str = "GO6"))).first;
//     AtomType::aH = *repository.insert (new AH ((str = "H"))).first;
//     AtomType::aH* = *repository.insert (new AH* ((str = "H*"))).first;
//     AtomType::aH*1 = *repository.insert (new AH*1 ((str = "H*1"))).first;
//     AtomType::aH*6 = *repository.insert (new AH*6 ((str = "H*6"))).first;
//     AtomType::aH*8 = *repository.insert (new AH*8 ((str = "H*8"))).first;
//     AtomType::aH0 = *repository.insert (new AH0 ((str = "H0"))).first;
//     AtomType::aH0* = *repository.insert (new AH0* ((str = "H0*"))).first;
//     AtomType::aH01 = *repository.insert (new AH01 ((str = "H01"))).first;
//     AtomType::aH02 = *repository.insert (new AH02 ((str = "H02"))).first;
//     AtomType::aH02A = *repository.insert (new AH02A ((str = "H02A"))).first;
//     AtomType::aH03 = *repository.insert (new AH03 ((str = "H03"))).first;
//     AtomType::aH03B = *repository.insert (new AH03B ((str = "H03B"))).first;
//     AtomType::aH04 = *repository.insert (new AH04 ((str = "H04"))).first;
//     AtomType::aH04C = *repository.insert (new AH04C ((str = "H04C"))).first;
//     AtomType::aH05 = *repository.insert (new AH05 ((str = "H05"))).first;
//     AtomType::aH06 = *repository.insert (new AH06 ((str = "H06"))).first;
//     AtomType::aH07 = *repository.insert (new AH07 ((str = "H07"))).first;
//     AtomType::aH08 = *repository.insert (new AH08 ((str = "H08"))).first;
//     AtomType::aH09 = *repository.insert (new AH09 ((str = "H09"))).first;
//     AtomType::aH0A = *repository.insert (new AH0A ((str = "H0A"))).first;
//     AtomType::aH0B = *repository.insert (new AH0B ((str = "H0B"))).first;
//     AtomType::aH0C = *repository.insert (new AH0C ((str = "H0C"))).first;
//     AtomType::aH0D = *repository.insert (new AH0D ((str = "H0D"))).first;
//     AtomType::aH0K1 = *repository.insert (new AH0K1 ((str = "H0K1"))).first;
//     AtomType::aH0P2 = *repository.insert (new AH0P2 ((str = "H0P2"))).first;
//     AtomType::aH0P3 = *repository.insert (new AH0P3 ((str = "H0P3"))).first;
//     AtomType::aH1 = *repository.insert (new AH1 ((str = "H1"))).first;
//     AtomType::aH1" = *repository.insert (new AH1" ((str = "H1""))).first;
//     AtomType::aH1* = *repository.insert (new AH1* ((str = "H1*"))).first;
//     AtomType::aH1*1 = *repository.insert (new AH1*1 ((str = "H1*1"))).first;
//     AtomType::aH1*2 = *repository.insert (new AH1*2 ((str = "H1*2"))).first;
//     AtomType::aH1*A = *repository.insert (new AH1*A ((str = "H1*A"))).first;
//     AtomType::aH1*U = *repository.insert (new AH1*U ((str = "H1*U"))).first;
//     AtomType::aH10 = *repository.insert (new AH10 ((str = "H10"))).first;
//     AtomType::aH10* = *repository.insert (new AH10* ((str = "H10*"))).first;
//     AtomType::aH100 = *repository.insert (new AH100 ((str = "H100"))).first;
//     AtomType::aH101 = *repository.insert (new AH101 ((str = "H101"))).first;
//     AtomType::aH102 = *repository.insert (new AH102 ((str = "H102"))).first;
//     AtomType::aH103 = *repository.insert (new AH103 ((str = "H103"))).first;
//     AtomType::aH104 = *repository.insert (new AH104 ((str = "H104"))).first;
//     AtomType::aH108 = *repository.insert (new AH108 ((str = "H108"))).first;
//     AtomType::aH10A = *repository.insert (new AH10A ((str = "H10A"))).first;
//     AtomType::aH10B = *repository.insert (new AH10B ((str = "H10B"))).first;
//     AtomType::aH10S = *repository.insert (new AH10S ((str = "H10S"))).first;
//     AtomType::aH11 = *repository.insert (new AH11 ((str = "H11"))).first;
//     AtomType::aH11* = *repository.insert (new AH11* ((str = "H11*"))).first;
//     AtomType::aH111 = *repository.insert (new AH111 ((str = "H111"))).first;
//     AtomType::aH112 = *repository.insert (new AH112 ((str = "H112"))).first;
//     AtomType::aH11A = *repository.insert (new AH11A ((str = "H11A"))).first;
//     AtomType::aH11D = *repository.insert (new AH11D ((str = "H11D"))).first;
//     AtomType::aH11P = *repository.insert (new AH11P ((str = "H11P"))).first;
//     AtomType::aH12 = *repository.insert (new AH12 ((str = "H12"))).first;
//     AtomType::aH12* = *repository.insert (new AH12* ((str = "H12*"))).first;
//     AtomType::aH120 = *repository.insert (new AH120 ((str = "H120"))).first;
//     AtomType::aH121 = *repository.insert (new AH121 ((str = "H121"))).first;
//     AtomType::aH122 = *repository.insert (new AH122 ((str = "H122"))).first;
//     AtomType::aH12A = *repository.insert (new AH12A ((str = "H12A"))).first;
//     AtomType::aH13 = *repository.insert (new AH13 ((str = "H13"))).first;
//     AtomType::aH13* = *repository.insert (new AH13* ((str = "H13*"))).first;
//     AtomType::aH131 = *repository.insert (new AH131 ((str = "H131"))).first;
//     AtomType::aH132 = *repository.insert (new AH132 ((str = "H132"))).first;
//     AtomType::aH133 = *repository.insert (new AH133 ((str = "H133"))).first;
//     AtomType::aH13A = *repository.insert (new AH13A ((str = "H13A"))).first;
//     AtomType::aH13D = *repository.insert (new AH13D ((str = "H13D"))).first;
//     AtomType::aH14 = *repository.insert (new AH14 ((str = "H14"))).first;
//     AtomType::aH14* = *repository.insert (new AH14* ((str = "H14*"))).first;
//     AtomType::aH141 = *repository.insert (new AH141 ((str = "H141"))).first;
//     AtomType::aH142 = *repository.insert (new AH142 ((str = "H142"))).first;
//     AtomType::aH14A = *repository.insert (new AH14A ((str = "H14A"))).first;
//     AtomType::aH14B = *repository.insert (new AH14B ((str = "H14B"))).first;
//     AtomType::aH15 = *repository.insert (new AH15 ((str = "H15"))).first;
//     AtomType::aH15* = *repository.insert (new AH15* ((str = "H15*"))).first;
//     AtomType::aH151 = *repository.insert (new AH151 ((str = "H151"))).first;
//     AtomType::aH152 = *repository.insert (new AH152 ((str = "H152"))).first;
//     AtomType::aH16 = *repository.insert (new AH16 ((str = "H16"))).first;
//     AtomType::aH161 = *repository.insert (new AH161 ((str = "H161"))).first;
//     AtomType::aH162 = *repository.insert (new AH162 ((str = "H162"))).first;
//     AtomType::aH17 = *repository.insert (new AH17 ((str = "H17"))).first;
//     AtomType::aH171 = *repository.insert (new AH171 ((str = "H171"))).first;
//     AtomType::aH172 = *repository.insert (new AH172 ((str = "H172"))).first;
//     AtomType::aH18 = *repository.insert (new AH18 ((str = "H18"))).first;
//     AtomType::aH181 = *repository.insert (new AH181 ((str = "H181"))).first;
//     AtomType::aH182 = *repository.insert (new AH182 ((str = "H182"))).first;
//     AtomType::aH19 = *repository.insert (new AH19 ((str = "H19"))).first;
//     AtomType::aH191 = *repository.insert (new AH191 ((str = "H191"))).first;
//     AtomType::aH192 = *repository.insert (new AH192 ((str = "H192"))).first;
//     AtomType::aH1A = *repository.insert (new AH1A ((str = "H1A"))).first;
//     AtomType::aH1AA = *repository.insert (new AH1AA ((str = "H1AA"))).first;
//     AtomType::aH1AB = *repository.insert (new AH1AB ((str = "H1AB"))).first;
//     AtomType::aH1AC = *repository.insert (new AH1AC ((str = "H1AC"))).first;
//     AtomType::aH1B = *repository.insert (new AH1B ((str = "H1B"))).first;
//     AtomType::aH1C = *repository.insert (new AH1C ((str = "H1C"))).first;
//     AtomType::aH1CA = *repository.insert (new AH1CA ((str = "H1CA"))).first;
//     AtomType::aH1CC = *repository.insert (new AH1CC ((str = "H1CC"))).first;
//     AtomType::aH1CE = *repository.insert (new AH1CE ((str = "H1CE"))).first;
//     AtomType::aH1D = *repository.insert (new AH1D ((str = "H1D"))).first;
//     AtomType::aH1E = *repository.insert (new AH1E ((str = "H1E"))).first;
//     AtomType::aH1F = *repository.insert (new AH1F ((str = "H1F"))).first;
//     AtomType::aH1G = *repository.insert (new AH1G ((str = "H1G"))).first;
//     AtomType::aH1H = *repository.insert (new AH1H ((str = "H1H"))).first;
//     AtomType::aH1I = *repository.insert (new AH1I ((str = "H1I"))).first;
//     AtomType::aH1J = *repository.insert (new AH1J ((str = "H1J"))).first;
//     AtomType::aH1K = *repository.insert (new AH1K ((str = "H1K"))).first;
//     AtomType::aH1L = *repository.insert (new AH1L ((str = "H1L"))).first;
//     AtomType::aH1M = *repository.insert (new AH1M ((str = "H1M"))).first;
//     AtomType::aH1N = *repository.insert (new AH1N ((str = "H1N"))).first;
//     AtomType::aH1N1 = *repository.insert (new AH1N1 ((str = "H1N1"))).first;
//     AtomType::aH1N2 = *repository.insert (new AH1N2 ((str = "H1N2"))).first;
//     AtomType::aH1NA = *repository.insert (new AH1NA ((str = "H1NA"))).first;
//     AtomType::aH1O = *repository.insert (new AH1O ((str = "H1O"))).first;
//     AtomType::aH1O2 = *repository.insert (new AH1O2 ((str = "H1O2"))).first;
//     AtomType::aH1O3 = *repository.insert (new AH1O3 ((str = "H1O3"))).first;
//     AtomType::aH1O4 = *repository.insert (new AH1O4 ((str = "H1O4"))).first;
//     AtomType::aH1O6 = *repository.insert (new AH1O6 ((str = "H1O6"))).first;
//     AtomType::aH1P = *repository.insert (new AH1P ((str = "H1P"))).first;
//     AtomType::aH1PA = *repository.insert (new AH1PA ((str = "H1PA"))).first;
//     AtomType::aH1Q = *repository.insert (new AH1Q ((str = "H1Q"))).first;
//     AtomType::aH1QA = *repository.insert (new AH1QA ((str = "H1QA"))).first;
//     AtomType::aH1R = *repository.insert (new AH1R ((str = "H1R"))).first;
//     AtomType::aH1S = *repository.insert (new AH1S ((str = "H1S"))).first;
//     AtomType::aH1T = *repository.insert (new AH1T ((str = "H1T"))).first;
//     AtomType::aH1U = *repository.insert (new AH1U ((str = "H1U"))).first;
//     AtomType::aH1UA = *repository.insert (new AH1UA ((str = "H1UA"))).first;
//     AtomType::aH1V = *repository.insert (new AH1V ((str = "H1V"))).first;
//     AtomType::aH1W = *repository.insert (new AH1W ((str = "H1W"))).first;
//     AtomType::aH1X = *repository.insert (new AH1X ((str = "H1X"))).first;
//     AtomType::aH1XA = *repository.insert (new AH1XA ((str = "H1XA"))).first;
//     AtomType::aH1Y = *repository.insert (new AH1Y ((str = "H1Y"))).first;
//     AtomType::aH1Z = *repository.insert (new AH1Z ((str = "H1Z"))).first;
//     AtomType::aH1ZA = *repository.insert (new AH1ZA ((str = "H1ZA"))).first;
//     AtomType::aH2 = *repository.insert (new AH2 ((str = "H2"))).first;
//     AtomType::aH2" = *repository.insert (new AH2" ((str = "H2""))).first;
//     AtomType::aH2* = *repository.insert (new AH2* ((str = "H2*"))).first;
//     AtomType::aH2** = *repository.insert (new AH2** ((str = "H2**"))).first;
//     AtomType::aH2*A = *repository.insert (new AH2*A ((str = "H2*A"))).first;
//     AtomType::aH20 = *repository.insert (new AH20 ((str = "H20"))).first;
//     AtomType::aH201 = *repository.insert (new AH201 ((str = "H201"))).first;
//     AtomType::aH202 = *repository.insert (new AH202 ((str = "H202"))).first;
//     AtomType::aH21 = *repository.insert (new AH21 ((str = "H21"))).first;
//     AtomType::aH21* = *repository.insert (new AH21* ((str = "H21*"))).first;
//     AtomType::aH211 = *repository.insert (new AH211 ((str = "H211"))).first;
//     AtomType::aH212 = *repository.insert (new AH212 ((str = "H212"))).first;
//     AtomType::aH21P = *repository.insert (new AH21P ((str = "H21P"))).first;
//     AtomType::aH22 = *repository.insert (new AH22 ((str = "H22"))).first;
//     AtomType::aH22* = *repository.insert (new AH22* ((str = "H22*"))).first;
//     AtomType::aH23 = *repository.insert (new AH23 ((str = "H23"))).first;
//     AtomType::aH23* = *repository.insert (new AH23* ((str = "H23*"))).first;
//     AtomType::aH231 = *repository.insert (new AH231 ((str = "H231"))).first;
//     AtomType::aH232 = *repository.insert (new AH232 ((str = "H232"))).first;
//     AtomType::aH24 = *repository.insert (new AH24 ((str = "H24"))).first;
//     AtomType::aH24* = *repository.insert (new AH24* ((str = "H24*"))).first;
//     AtomType::aH241 = *repository.insert (new AH241 ((str = "H241"))).first;
//     AtomType::aH242 = *repository.insert (new AH242 ((str = "H242"))).first;
//     AtomType::aH24A = *repository.insert (new AH24A ((str = "H24A"))).first;
//     AtomType::aH24B = *repository.insert (new AH24B ((str = "H24B"))).first;
//     AtomType::aH25 = *repository.insert (new AH25 ((str = "H25"))).first;
//     AtomType::aH25* = *repository.insert (new AH25* ((str = "H25*"))).first;
//     AtomType::aH26 = *repository.insert (new AH26 ((str = "H26"))).first;
//     AtomType::aH261 = *repository.insert (new AH261 ((str = "H261"))).first;
//     AtomType::aH262 = *repository.insert (new AH262 ((str = "H262"))).first;
//     AtomType::aH27 = *repository.insert (new AH27 ((str = "H27"))).first;
//     AtomType::aH271 = *repository.insert (new AH271 ((str = "H271"))).first;
//     AtomType::aH272 = *repository.insert (new AH272 ((str = "H272"))).first;
//     AtomType::aH28 = *repository.insert (new AH28 ((str = "H28"))).first;
//     AtomType::aH29 = *repository.insert (new AH29 ((str = "H29"))).first;
//     AtomType::aH291 = *repository.insert (new AH291 ((str = "H291"))).first;
//     AtomType::aH292 = *repository.insert (new AH292 ((str = "H292"))).first;
//     AtomType::aH2A = *repository.insert (new AH2A ((str = "H2A"))).first;
//     AtomType::aH2AA = *repository.insert (new AH2AA ((str = "H2AA"))).first;
//     AtomType::aH2B = *repository.insert (new AH2B ((str = "H2B"))).first;
//     AtomType::aH2C = *repository.insert (new AH2C ((str = "H2C"))).first;
//     AtomType::aH2CA = *repository.insert (new AH2CA ((str = "H2CA"))).first;
//     AtomType::aH2CC = *repository.insert (new AH2CC ((str = "H2CC"))).first;
//     AtomType::aH2CE = *repository.insert (new AH2CE ((str = "H2CE"))).first;
//     AtomType::aH2D = *repository.insert (new AH2D ((str = "H2D"))).first;
//     AtomType::aH2E = *repository.insert (new AH2E ((str = "H2E"))).first;
//     AtomType::aH2F = *repository.insert (new AH2F ((str = "H2F"))).first;
//     AtomType::aH2G = *repository.insert (new AH2G ((str = "H2G"))).first;
//     AtomType::aH2H = *repository.insert (new AH2H ((str = "H2H"))).first;
//     AtomType::aH2I = *repository.insert (new AH2I ((str = "H2I"))).first;
//     AtomType::aH2J = *repository.insert (new AH2J ((str = "H2J"))).first;
//     AtomType::aH2K = *repository.insert (new AH2K ((str = "H2K"))).first;
//     AtomType::aH2KA = *repository.insert (new AH2KA ((str = "H2KA"))).first;
//     AtomType::aH2L = *repository.insert (new AH2L ((str = "H2L"))).first;
//     AtomType::aH2M = *repository.insert (new AH2M ((str = "H2M"))).first;
//     AtomType::aH2M1 = *repository.insert (new AH2M1 ((str = "H2M1"))).first;
//     AtomType::aH2M2 = *repository.insert (new AH2M2 ((str = "H2M2"))).first;
//     AtomType::aH2M3 = *repository.insert (new AH2M3 ((str = "H2M3"))).first;
//     AtomType::aH2N = *repository.insert (new AH2N ((str = "H2N"))).first;
//     AtomType::aH2N1 = *repository.insert (new AH2N1 ((str = "H2N1"))).first;
//     AtomType::aH2N2 = *repository.insert (new AH2N2 ((str = "H2N2"))).first;
//     AtomType::aH2NA = *repository.insert (new AH2NA ((str = "H2NA"))).first;
//     AtomType::aH2NH = *repository.insert (new AH2NH ((str = "H2NH"))).first;
//     AtomType::aH2O = *repository.insert (new AH2O ((str = "H2O"))).first;
//     AtomType::aH2P = *repository.insert (new AH2P ((str = "H2P"))).first;
//     AtomType::aH2Q = *repository.insert (new AH2Q ((str = "H2Q"))).first;
//     AtomType::aH2QA = *repository.insert (new AH2QA ((str = "H2QA"))).first;
//     AtomType::aH2R = *repository.insert (new AH2R ((str = "H2R"))).first;
//     AtomType::aH2S = *repository.insert (new AH2S ((str = "H2S"))).first;
//     AtomType::aH2T = *repository.insert (new AH2T ((str = "H2T"))).first;
//     AtomType::aH2U = *repository.insert (new AH2U ((str = "H2U"))).first;
//     AtomType::aH2UA = *repository.insert (new AH2UA ((str = "H2UA"))).first;
//     AtomType::aH2W = *repository.insert (new AH2W ((str = "H2W"))).first;
//     AtomType::aH2X = *repository.insert (new AH2X ((str = "H2X"))).first;
//     AtomType::aH2Y = *repository.insert (new AH2Y ((str = "H2Y"))).first;
//     AtomType::aH2Z = *repository.insert (new AH2Z ((str = "H2Z"))).first;
//     AtomType::aH2ZA = *repository.insert (new AH2ZA ((str = "H2ZA"))).first;
//     AtomType::aH3 = *repository.insert (new AH3 ((str = "H3"))).first;
//     AtomType::aH3" = *repository.insert (new AH3" ((str = "H3""))).first;
//     AtomType::aH3* = *repository.insert (new AH3* ((str = "H3*"))).first;
//     AtomType::aH3** = *repository.insert (new AH3** ((str = "H3**"))).first;
//     AtomType::aH3*1 = *repository.insert (new AH3*1 ((str = "H3*1"))).first;
//     AtomType::aH3*2 = *repository.insert (new AH3*2 ((str = "H3*2"))).first;
//     AtomType::aH3*A = *repository.insert (new AH3*A ((str = "H3*A"))).first;
//     AtomType::aH3*U = *repository.insert (new AH3*U ((str = "H3*U"))).first;
//     AtomType::aH30 = *repository.insert (new AH30 ((str = "H30"))).first;
//     AtomType::aH301 = *repository.insert (new AH301 ((str = "H301"))).first;
//     AtomType::aH302 = *repository.insert (new AH302 ((str = "H302"))).first;
//     AtomType::aH30A = *repository.insert (new AH30A ((str = "H30A"))).first;
//     AtomType::aH30B = *repository.insert (new AH30B ((str = "H30B"))).first;
//     AtomType::aH30C = *repository.insert (new AH30C ((str = "H30C"))).first;
//     AtomType::aH31 = *repository.insert (new AH31 ((str = "H31"))).first;
//     AtomType::aH31* = *repository.insert (new AH31* ((str = "H31*"))).first;
//     AtomType::aH31A = *repository.insert (new AH31A ((str = "H31A"))).first;
//     AtomType::aH31B = *repository.insert (new AH31B ((str = "H31B"))).first;
//     AtomType::aH32 = *repository.insert (new AH32 ((str = "H32"))).first;
//     AtomType::aH32* = *repository.insert (new AH32* ((str = "H32*"))).first;
//     AtomType::aH321 = *repository.insert (new AH321 ((str = "H321"))).first;
//     AtomType::aH322 = *repository.insert (new AH322 ((str = "H322"))).first;
//     AtomType::aH32A = *repository.insert (new AH32A ((str = "H32A"))).first;
//     AtomType::aH32B = *repository.insert (new AH32B ((str = "H32B"))).first;
//     AtomType::aH33 = *repository.insert (new AH33 ((str = "H33"))).first;
//     AtomType::aH33* = *repository.insert (new AH33* ((str = "H33*"))).first;
//     AtomType::aH331 = *repository.insert (new AH331 ((str = "H331"))).first;
//     AtomType::aH332 = *repository.insert (new AH332 ((str = "H332"))).first;
//     AtomType::aH33A = *repository.insert (new AH33A ((str = "H33A"))).first;
//     AtomType::aH33B = *repository.insert (new AH33B ((str = "H33B"))).first;
//     AtomType::aH33C = *repository.insert (new AH33C ((str = "H33C"))).first;
//     AtomType::aH34 = *repository.insert (new AH34 ((str = "H34"))).first;
//     AtomType::aH34* = *repository.insert (new AH34* ((str = "H34*"))).first;
//     AtomType::aH35 = *repository.insert (new AH35 ((str = "H35"))).first;
//     AtomType::aH351 = *repository.insert (new AH351 ((str = "H351"))).first;
//     AtomType::aH352 = *repository.insert (new AH352 ((str = "H352"))).first;
//     AtomType::aH36 = *repository.insert (new AH36 ((str = "H36"))).first;
//     AtomType::aH361 = *repository.insert (new AH361 ((str = "H361"))).first;
//     AtomType::aH362 = *repository.insert (new AH362 ((str = "H362"))).first;
//     AtomType::aH37 = *repository.insert (new AH37 ((str = "H37"))).first;
//     AtomType::aH38 = *repository.insert (new AH38 ((str = "H38"))).first;
//     AtomType::aH381 = *repository.insert (new AH381 ((str = "H381"))).first;
//     AtomType::aH382 = *repository.insert (new AH382 ((str = "H382"))).first;
//     AtomType::aH39 = *repository.insert (new AH39 ((str = "H39"))).first;
//     AtomType::aH391 = *repository.insert (new AH391 ((str = "H391"))).first;
//     AtomType::aH392 = *repository.insert (new AH392 ((str = "H392"))).first;
//     AtomType::aH3A = *repository.insert (new AH3A ((str = "H3A"))).first;
//     AtomType::aH3B = *repository.insert (new AH3B ((str = "H3B"))).first;
//     AtomType::aH3C = *repository.insert (new AH3C ((str = "H3C"))).first;
//     AtomType::aH3CC = *repository.insert (new AH3CC ((str = "H3CC"))).first;
//     AtomType::aH3CE = *repository.insert (new AH3CE ((str = "H3CE"))).first;
//     AtomType::aH3D = *repository.insert (new AH3D ((str = "H3D"))).first;
//     AtomType::aH3E = *repository.insert (new AH3E ((str = "H3E"))).first;
//     AtomType::aH3F = *repository.insert (new AH3F ((str = "H3F"))).first;
//     AtomType::aH3G = *repository.insert (new AH3G ((str = "H3G"))).first;
//     AtomType::aH3H = *repository.insert (new AH3H ((str = "H3H"))).first;
//     AtomType::aH3I = *repository.insert (new AH3I ((str = "H3I"))).first;
//     AtomType::aH3J = *repository.insert (new AH3J ((str = "H3J"))).first;
//     AtomType::aH3K = *repository.insert (new AH3K ((str = "H3K"))).first;
//     AtomType::aH3L = *repository.insert (new AH3L ((str = "H3L"))).first;
//     AtomType::aH3M = *repository.insert (new AH3M ((str = "H3M"))).first;
//     AtomType::aH3N = *repository.insert (new AH3N ((str = "H3N"))).first;
//     AtomType::aH3O = *repository.insert (new AH3O ((str = "H3O"))).first;
//     AtomType::aH3P = *repository.insert (new AH3P ((str = "H3P"))).first;
//     AtomType::aH3Q = *repository.insert (new AH3Q ((str = "H3Q"))).first;
//     AtomType::aH3R = *repository.insert (new AH3R ((str = "H3R"))).first;
//     AtomType::aH3S = *repository.insert (new AH3S ((str = "H3S"))).first;
//     AtomType::aH3SA = *repository.insert (new AH3SA ((str = "H3SA"))).first;
//     AtomType::aH3T = *repository.insert (new AH3T ((str = "H3T"))).first;
//     AtomType::aH3U = *repository.insert (new AH3U ((str = "H3U"))).first;
//     AtomType::aH3V = *repository.insert (new AH3V ((str = "H3V"))).first;
//     AtomType::aH3W = *repository.insert (new AH3W ((str = "H3W"))).first;
//     AtomType::aH3X = *repository.insert (new AH3X ((str = "H3X"))).first;
//     AtomType::aH3Y = *repository.insert (new AH3Y ((str = "H3Y"))).first;
//     AtomType::aH3Z = *repository.insert (new AH3Z ((str = "H3Z"))).first;
//     AtomType::aH4 = *repository.insert (new AH4 ((str = "H4"))).first;
//     AtomType::aH4" = *repository.insert (new AH4" ((str = "H4""))).first;
//     AtomType::aH4* = *repository.insert (new AH4* ((str = "H4*"))).first;
//     AtomType::aH4** = *repository.insert (new AH4** ((str = "H4**"))).first;
//     AtomType::aH4*1 = *repository.insert (new AH4*1 ((str = "H4*1"))).first;
//     AtomType::aH4*2 = *repository.insert (new AH4*2 ((str = "H4*2"))).first;
//     AtomType::aH4*A = *repository.insert (new AH4*A ((str = "H4*A"))).first;
//     AtomType::aH4*U = *repository.insert (new AH4*U ((str = "H4*U"))).first;
//     AtomType::aH40 = *repository.insert (new AH40 ((str = "H40"))).first;
//     AtomType::aH40A = *repository.insert (new AH40A ((str = "H40A"))).first;
//     AtomType::aH40B = *repository.insert (new AH40B ((str = "H40B"))).first;
//     AtomType::aH40C = *repository.insert (new AH40C ((str = "H40C"))).first;
//     AtomType::aH41 = *repository.insert (new AH41 ((str = "H41"))).first;
//     AtomType::aH42 = *repository.insert (new AH42 ((str = "H42"))).first;
//     AtomType::aH42A = *repository.insert (new AH42A ((str = "H42A"))).first;
//     AtomType::aH42B = *repository.insert (new AH42B ((str = "H42B"))).first;
//     AtomType::aH43 = *repository.insert (new AH43 ((str = "H43"))).first;
//     AtomType::aH44 = *repository.insert (new AH44 ((str = "H44"))).first;
//     AtomType::aH44* = *repository.insert (new AH44* ((str = "H44*"))).first;
//     AtomType::aH45 = *repository.insert (new AH45 ((str = "H45"))).first;
//     AtomType::aH46 = *repository.insert (new AH46 ((str = "H46"))).first;
//     AtomType::aH47 = *repository.insert (new AH47 ((str = "H47"))).first;
//     AtomType::aH48 = *repository.insert (new AH48 ((str = "H48"))).first;
//     AtomType::aH49 = *repository.insert (new AH49 ((str = "H49"))).first;
//     AtomType::aH4A = *repository.insert (new AH4A ((str = "H4A"))).first;
//     AtomType::aH4B = *repository.insert (new AH4B ((str = "H4B"))).first;
//     AtomType::aH4C = *repository.insert (new AH4C ((str = "H4C"))).first;
//     AtomType::aH4CC = *repository.insert (new AH4CC ((str = "H4CC"))).first;
//     AtomType::aH4CE = *repository.insert (new AH4CE ((str = "H4CE"))).first;
//     AtomType::aH4D = *repository.insert (new AH4D ((str = "H4D"))).first;
//     AtomType::aH4E = *repository.insert (new AH4E ((str = "H4E"))).first;
//     AtomType::aH4F = *repository.insert (new AH4F ((str = "H4F"))).first;
//     AtomType::aH4G = *repository.insert (new AH4G ((str = "H4G"))).first;
//     AtomType::aH4H = *repository.insert (new AH4H ((str = "H4H"))).first;
//     AtomType::aH4I = *repository.insert (new AH4I ((str = "H4I"))).first;
//     AtomType::aH4J = *repository.insert (new AH4J ((str = "H4J"))).first;
//     AtomType::aH4K = *repository.insert (new AH4K ((str = "H4K"))).first;
//     AtomType::aH4L = *repository.insert (new AH4L ((str = "H4L"))).first;
//     AtomType::aH4M = *repository.insert (new AH4M ((str = "H4M"))).first;
//     AtomType::aH4N = *repository.insert (new AH4N ((str = "H4N"))).first;
//     AtomType::aH4O = *repository.insert (new AH4O ((str = "H4O"))).first;
//     AtomType::aH4P = *repository.insert (new AH4P ((str = "H4P"))).first;
//     AtomType::aH4Q = *repository.insert (new AH4Q ((str = "H4Q"))).first;
//     AtomType::aH4R = *repository.insert (new AH4R ((str = "H4R"))).first;
//     AtomType::aH4S = *repository.insert (new AH4S ((str = "H4S"))).first;
//     AtomType::aH4T = *repository.insert (new AH4T ((str = "H4T"))).first;
//     AtomType::aH4T* = *repository.insert (new AH4T* ((str = "H4T*"))).first;
//     AtomType::aH4U = *repository.insert (new AH4U ((str = "H4U"))).first;
//     AtomType::aH4V = *repository.insert (new AH4V ((str = "H4V"))).first;
//     AtomType::aH4W = *repository.insert (new AH4W ((str = "H4W"))).first;
//     AtomType::aH4X = *repository.insert (new AH4X ((str = "H4X"))).first;
//     AtomType::aH4Y = *repository.insert (new AH4Y ((str = "H4Y"))).first;
//     AtomType::aH4Z = *repository.insert (new AH4Z ((str = "H4Z"))).first;
//     AtomType::aH5 = *repository.insert (new AH5 ((str = "H5"))).first;
//     AtomType::aH5" = *repository.insert (new AH5" ((str = "H5""))).first;
//     AtomType::aH5* = *repository.insert (new AH5* ((str = "H5*"))).first;
//     AtomType::aH5** = *repository.insert (new AH5** ((str = "H5**"))).first;
//     AtomType::aH50 = *repository.insert (new AH50 ((str = "H50"))).first;
//     AtomType::aH51 = *repository.insert (new AH51 ((str = "H51"))).first;
//     AtomType::aH51* = *repository.insert (new AH51* ((str = "H51*"))).first;
//     AtomType::aH52 = *repository.insert (new AH52 ((str = "H52"))).first;
//     AtomType::aH52* = *repository.insert (new AH52* ((str = "H52*"))).first;
//     AtomType::aH53 = *repository.insert (new AH53 ((str = "H53"))).first;
//     AtomType::aH54 = *repository.insert (new AH54 ((str = "H54"))).first;
//     AtomType::aH55 = *repository.insert (new AH55 ((str = "H55"))).first;
//     AtomType::aH56 = *repository.insert (new AH56 ((str = "H56"))).first;
//     AtomType::aH57 = *repository.insert (new AH57 ((str = "H57"))).first;
//     AtomType::aH58 = *repository.insert (new AH58 ((str = "H58"))).first;
//     AtomType::aH59 = *repository.insert (new AH59 ((str = "H59"))).first;
//     AtomType::aH5A = *repository.insert (new AH5A ((str = "H5A"))).first;
//     AtomType::aH5B = *repository.insert (new AH5B ((str = "H5B"))).first;
//     AtomType::aH5C = *repository.insert (new AH5C ((str = "H5C"))).first;
//     AtomType::aH5CC = *repository.insert (new AH5CC ((str = "H5CC"))).first;
//     AtomType::aH5CE = *repository.insert (new AH5CE ((str = "H5CE"))).first;
//     AtomType::aH5D = *repository.insert (new AH5D ((str = "H5D"))).first;
//     AtomType::aH5E = *repository.insert (new AH5E ((str = "H5E"))).first;
//     AtomType::aH5F = *repository.insert (new AH5F ((str = "H5F"))).first;
//     AtomType::aH5G = *repository.insert (new AH5G ((str = "H5G"))).first;
//     AtomType::aH5H = *repository.insert (new AH5H ((str = "H5H"))).first;
//     AtomType::aH5I = *repository.insert (new AH5I ((str = "H5I"))).first;
//     AtomType::aH5J = *repository.insert (new AH5J ((str = "H5J"))).first;
//     AtomType::aH5K = *repository.insert (new AH5K ((str = "H5K"))).first;
//     AtomType::aH5L = *repository.insert (new AH5L ((str = "H5L"))).first;
//     AtomType::aH5M = *repository.insert (new AH5M ((str = "H5M"))).first;
//     AtomType::aH5N = *repository.insert (new AH5N ((str = "H5N"))).first;
//     AtomType::aH5O = *repository.insert (new AH5O ((str = "H5O"))).first;
//     AtomType::aH5P = *repository.insert (new AH5P ((str = "H5P"))).first;
//     AtomType::aH5R = *repository.insert (new AH5R ((str = "H5R"))).first;
//     AtomType::aH5S = *repository.insert (new AH5S ((str = "H5S"))).first;
//     AtomType::aH5T = *repository.insert (new AH5T ((str = "H5T"))).first;
//     AtomType::aH5U = *repository.insert (new AH5U ((str = "H5U"))).first;
//     AtomType::aH5W = *repository.insert (new AH5W ((str = "H5W"))).first;
//     AtomType::aH5X = *repository.insert (new AH5X ((str = "H5X"))).first;
//     AtomType::aH5Y = *repository.insert (new AH5Y ((str = "H5Y"))).first;
//     AtomType::aH5Z = *repository.insert (new AH5Z ((str = "H5Z"))).first;
//     AtomType::aH6 = *repository.insert (new AH6 ((str = "H6"))).first;
//     AtomType::aH6" = *repository.insert (new AH6" ((str = "H6""))).first;
//     AtomType::aH6* = *repository.insert (new AH6* ((str = "H6*"))).first;
//     AtomType::aH6** = *repository.insert (new AH6** ((str = "H6**"))).first;
//     AtomType::aH60 = *repository.insert (new AH60 ((str = "H60"))).first;
//     AtomType::aH61 = *repository.insert (new AH61 ((str = "H61"))).first;
//     AtomType::aH61A = *repository.insert (new AH61A ((str = "H61A"))).first;
//     AtomType::aH62 = *repository.insert (new AH62 ((str = "H62"))).first;
//     AtomType::aH62A = *repository.insert (new AH62A ((str = "H62A"))).first;
//     AtomType::aH63 = *repository.insert (new AH63 ((str = "H63"))).first;
//     AtomType::aH64 = *repository.insert (new AH64 ((str = "H64"))).first;
//     AtomType::aH65 = *repository.insert (new AH65 ((str = "H65"))).first;
//     AtomType::aH66 = *repository.insert (new AH66 ((str = "H66"))).first;
//     AtomType::aH67 = *repository.insert (new AH67 ((str = "H67"))).first;
//     AtomType::aH68 = *repository.insert (new AH68 ((str = "H68"))).first;
//     AtomType::aH69 = *repository.insert (new AH69 ((str = "H69"))).first;
//     AtomType::aH6A = *repository.insert (new AH6A ((str = "H6A"))).first;
//     AtomType::aH6B = *repository.insert (new AH6B ((str = "H6B"))).first;
//     AtomType::aH6C = *repository.insert (new AH6C ((str = "H6C"))).first;
//     AtomType::aH6CC = *repository.insert (new AH6CC ((str = "H6CC"))).first;
//     AtomType::aH6CE = *repository.insert (new AH6CE ((str = "H6CE"))).first;
//     AtomType::aH6D = *repository.insert (new AH6D ((str = "H6D"))).first;
//     AtomType::aH6E = *repository.insert (new AH6E ((str = "H6E"))).first;
//     AtomType::aH6F = *repository.insert (new AH6F ((str = "H6F"))).first;
//     AtomType::aH6G = *repository.insert (new AH6G ((str = "H6G"))).first;
//     AtomType::aH6H = *repository.insert (new AH6H ((str = "H6H"))).first;
//     AtomType::aH6N = *repository.insert (new AH6N ((str = "H6N"))).first;
//     AtomType::aH6O = *repository.insert (new AH6O ((str = "H6O"))).first;
//     AtomType::aH6P = *repository.insert (new AH6P ((str = "H6P"))).first;
//     AtomType::aH6R = *repository.insert (new AH6R ((str = "H6R"))).first;
//     AtomType::aH6S = *repository.insert (new AH6S ((str = "H6S"))).first;
//     AtomType::aH6T = *repository.insert (new AH6T ((str = "H6T"))).first;
//     AtomType::aH6U = *repository.insert (new AH6U ((str = "H6U"))).first;
//     AtomType::aH6X = *repository.insert (new AH6X ((str = "H6X"))).first;
//     AtomType::aH6Z = *repository.insert (new AH6Z ((str = "H6Z"))).first;
//     AtomType::aH7 = *repository.insert (new AH7 ((str = "H7"))).first;
//     AtomType::aH7" = *repository.insert (new AH7" ((str = "H7""))).first;
//     AtomType::aH7* = *repository.insert (new AH7* ((str = "H7*"))).first;
//     AtomType::aH70 = *repository.insert (new AH70 ((str = "H70"))).first;
//     AtomType::aH71 = *repository.insert (new AH71 ((str = "H71"))).first;
//     AtomType::aH72 = *repository.insert (new AH72 ((str = "H72"))).first;
//     AtomType::aH73 = *repository.insert (new AH73 ((str = "H73"))).first;
//     AtomType::aH74 = *repository.insert (new AH74 ((str = "H74"))).first;
//     AtomType::aH75 = *repository.insert (new AH75 ((str = "H75"))).first;
//     AtomType::aH76 = *repository.insert (new AH76 ((str = "H76"))).first;
//     AtomType::aH77 = *repository.insert (new AH77 ((str = "H77"))).first;
//     AtomType::aH78 = *repository.insert (new AH78 ((str = "H78"))).first;
//     AtomType::aH79 = *repository.insert (new AH79 ((str = "H79"))).first;
//     AtomType::aH7A = *repository.insert (new AH7A ((str = "H7A"))).first;
//     AtomType::aH7B = *repository.insert (new AH7B ((str = "H7B"))).first;
//     AtomType::aH7C = *repository.insert (new AH7C ((str = "H7C"))).first;
//     AtomType::aH7D = *repository.insert (new AH7D ((str = "H7D"))).first;
//     AtomType::aH7E = *repository.insert (new AH7E ((str = "H7E"))).first;
//     AtomType::aH7F = *repository.insert (new AH7F ((str = "H7F"))).first;
//     AtomType::aH7H = *repository.insert (new AH7H ((str = "H7H"))).first;
//     AtomType::aH7I = *repository.insert (new AH7I ((str = "H7I"))).first;
//     AtomType::aH7M1 = *repository.insert (new AH7M1 ((str = "H7M1"))).first;
//     AtomType::aH7M2 = *repository.insert (new AH7M2 ((str = "H7M2"))).first;
//     AtomType::aH7M3 = *repository.insert (new AH7M3 ((str = "H7M3"))).first;
//     AtomType::aH7N = *repository.insert (new AH7N ((str = "H7N"))).first;
//     AtomType::aH7P = *repository.insert (new AH7P ((str = "H7P"))).first;
//     AtomType::aH7R = *repository.insert (new AH7R ((str = "H7R"))).first;
//     AtomType::aH7X = *repository.insert (new AH7X ((str = "H7X"))).first;
//     AtomType::aH7Z = *repository.insert (new AH7Z ((str = "H7Z"))).first;
//     AtomType::aH8 = *repository.insert (new AH8 ((str = "H8"))).first;
//     AtomType::aH8" = *repository.insert (new AH8" ((str = "H8""))).first;
//     AtomType::aH8* = *repository.insert (new AH8* ((str = "H8*"))).first;
//     AtomType::aH8** = *repository.insert (new AH8** ((str = "H8**"))).first;
//     AtomType::aH80 = *repository.insert (new AH80 ((str = "H80"))).first;
//     AtomType::aH81 = *repository.insert (new AH81 ((str = "H81"))).first;
//     AtomType::aH82 = *repository.insert (new AH82 ((str = "H82"))).first;
//     AtomType::aH83 = *repository.insert (new AH83 ((str = "H83"))).first;
//     AtomType::aH84 = *repository.insert (new AH84 ((str = "H84"))).first;
//     AtomType::aH85 = *repository.insert (new AH85 ((str = "H85"))).first;
//     AtomType::aH86 = *repository.insert (new AH86 ((str = "H86"))).first;
//     AtomType::aH87 = *repository.insert (new AH87 ((str = "H87"))).first;
//     AtomType::aH88 = *repository.insert (new AH88 ((str = "H88"))).first;
//     AtomType::aH89 = *repository.insert (new AH89 ((str = "H89"))).first;
//     AtomType::aH8A = *repository.insert (new AH8A ((str = "H8A"))).first;
//     AtomType::aH8B = *repository.insert (new AH8B ((str = "H8B"))).first;
//     AtomType::aH8C = *repository.insert (new AH8C ((str = "H8C"))).first;
//     AtomType::aH8D = *repository.insert (new AH8D ((str = "H8D"))).first;
//     AtomType::aH8E = *repository.insert (new AH8E ((str = "H8E"))).first;
//     AtomType::aH8F = *repository.insert (new AH8F ((str = "H8F"))).first;
//     AtomType::aH8G = *repository.insert (new AH8G ((str = "H8G"))).first;
//     AtomType::aH8H = *repository.insert (new AH8H ((str = "H8H"))).first;
//     AtomType::aH8I = *repository.insert (new AH8I ((str = "H8I"))).first;
//     AtomType::aH8M = *repository.insert (new AH8M ((str = "H8M"))).first;
//     AtomType::aH8N = *repository.insert (new AH8N ((str = "H8N"))).first;
//     AtomType::aH8O = *repository.insert (new AH8O ((str = "H8O"))).first;
//     AtomType::aH8P = *repository.insert (new AH8P ((str = "H8P"))).first;
//     AtomType::aH8R = *repository.insert (new AH8R ((str = "H8R"))).first;
//     AtomType::aH8S = *repository.insert (new AH8S ((str = "H8S"))).first;
//     AtomType::aH8X = *repository.insert (new AH8X ((str = "H8X"))).first;
//     AtomType::aH9 = *repository.insert (new AH9 ((str = "H9"))).first;
//     AtomType::aH9" = *repository.insert (new AH9" ((str = "H9""))).first;
//     AtomType::aH9* = *repository.insert (new AH9* ((str = "H9*"))).first;
//     AtomType::aH90 = *repository.insert (new AH90 ((str = "H90"))).first;
//     AtomType::aH91 = *repository.insert (new AH91 ((str = "H91"))).first;
//     AtomType::aH91* = *repository.insert (new AH91* ((str = "H91*"))).first;
//     AtomType::aH92 = *repository.insert (new AH92 ((str = "H92"))).first;
//     AtomType::aH92* = *repository.insert (new AH92* ((str = "H92*"))).first;
//     AtomType::aH93 = *repository.insert (new AH93 ((str = "H93"))).first;
//     AtomType::aH93* = *repository.insert (new AH93* ((str = "H93*"))).first;
//     AtomType::aH94 = *repository.insert (new AH94 ((str = "H94"))).first;
//     AtomType::aH95 = *repository.insert (new AH95 ((str = "H95"))).first;
//     AtomType::aH96 = *repository.insert (new AH96 ((str = "H96"))).first;
//     AtomType::aH97 = *repository.insert (new AH97 ((str = "H97"))).first;
//     AtomType::aH99 = *repository.insert (new AH99 ((str = "H99"))).first;
//     AtomType::aH9A = *repository.insert (new AH9A ((str = "H9A"))).first;
//     AtomType::aH9B = *repository.insert (new AH9B ((str = "H9B"))).first;
//     AtomType::aH9C = *repository.insert (new AH9C ((str = "H9C"))).first;
//     AtomType::aH9D = *repository.insert (new AH9D ((str = "H9D"))).first;
//     AtomType::aH9R = *repository.insert (new AH9R ((str = "H9R"))).first;
//     AtomType::aHA = *repository.insert (new AHA ((str = "HA"))).first;
//     AtomType::aHA* = *repository.insert (new AHA* ((str = "HA*"))).first;
//     AtomType::aHA0 = *repository.insert (new AHA0 ((str = "HA0"))).first;
//     AtomType::aHA1 = *repository.insert (new AHA1 ((str = "HA1"))).first;
//     AtomType::aHA1* = *repository.insert (new AHA1* ((str = "HA1*"))).first;
//     AtomType::aHA2 = *repository.insert (new AHA2 ((str = "HA2"))).first;
//     AtomType::aHA2* = *repository.insert (new AHA2* ((str = "HA2*"))).first;
//     AtomType::aHA21 = *repository.insert (new AHA21 ((str = "HA21"))).first;
//     AtomType::aHA22 = *repository.insert (new AHA22 ((str = "HA22"))).first;
//     AtomType::aHA3 = *repository.insert (new AHA3 ((str = "HA3"))).first;
//     AtomType::aHA3* = *repository.insert (new AHA3* ((str = "HA3*"))).first;
//     AtomType::aHA4 = *repository.insert (new AHA4 ((str = "HA4"))).first;
//     AtomType::aHA5 = *repository.insert (new AHA5 ((str = "HA5"))).first;
//     AtomType::aHA6 = *repository.insert (new AHA6 ((str = "HA6"))).first;
//     AtomType::aHA7 = *repository.insert (new AHA7 ((str = "HA7"))).first;
//     AtomType::aHA8 = *repository.insert (new AHA8 ((str = "HA8"))).first;
//     AtomType::aHAA = *repository.insert (new AHAA ((str = "HAA"))).first;
//     AtomType::aHAB = *repository.insert (new AHAB ((str = "HAB"))).first;
//     AtomType::aHAC = *repository.insert (new AHAC ((str = "HAC"))).first;
//     AtomType::aHACF = *repository.insert (new AHACF ((str = "HACF"))).first;
//     AtomType::aHACG = *repository.insert (new AHACG ((str = "HACG"))).first;
//     AtomType::aHACR = *repository.insert (new AHACR ((str = "HACR"))).first;
//     AtomType::aHAD = *repository.insert (new AHAD ((str = "HAD"))).first;
//     AtomType::aHAE = *repository.insert (new AHAE ((str = "HAE"))).first;
//     AtomType::aHAF = *repository.insert (new AHAF ((str = "HAF"))).first;
//     AtomType::aHAG = *repository.insert (new AHAG ((str = "HAG"))).first;
//     AtomType::aHAH = *repository.insert (new AHAH ((str = "HAH"))).first;
//     AtomType::aHAI = *repository.insert (new AHAI ((str = "HAI"))).first;
//     AtomType::aHAJ = *repository.insert (new AHAJ ((str = "HAJ"))).first;
//     AtomType::aHAK = *repository.insert (new AHAK ((str = "HAK"))).first;
//     AtomType::aHAL = *repository.insert (new AHAL ((str = "HAL"))).first;
//     AtomType::aHAM = *repository.insert (new AHAM ((str = "HAM"))).first;
//     AtomType::aHAN = *repository.insert (new AHAN ((str = "HAN"))).first;
//     AtomType::aHAO = *repository.insert (new AHAO ((str = "HAO"))).first;
//     AtomType::aHAP = *repository.insert (new AHAP ((str = "HAP"))).first;
//     AtomType::aHAQ = *repository.insert (new AHAQ ((str = "HAQ"))).first;
//     AtomType::aHAR = *repository.insert (new AHAR ((str = "HAR"))).first;
//     AtomType::aHAS = *repository.insert (new AHAS ((str = "HAS"))).first;
//     AtomType::aHAT = *repository.insert (new AHAT ((str = "HAT"))).first;
//     AtomType::aHAU = *repository.insert (new AHAU ((str = "HAU"))).first;
//     AtomType::aHAV = *repository.insert (new AHAV ((str = "HAV"))).first;
//     AtomType::aHAW = *repository.insert (new AHAW ((str = "HAW"))).first;
//     AtomType::aHAX = *repository.insert (new AHAX ((str = "HAX"))).first;
//     AtomType::aHAY = *repository.insert (new AHAY ((str = "HAY"))).first;
//     AtomType::aHAZ = *repository.insert (new AHAZ ((str = "HAZ"))).first;
//     AtomType::aHB = *repository.insert (new AHB ((str = "HB"))).first;
//     AtomType::aHB* = *repository.insert (new AHB* ((str = "HB*"))).first;
//     AtomType::aHB0 = *repository.insert (new AHB0 ((str = "HB0"))).first;
//     AtomType::aHB1 = *repository.insert (new AHB1 ((str = "HB1"))).first;
//     AtomType::aHB1* = *repository.insert (new AHB1* ((str = "HB1*"))).first;
//     AtomType::aHB11 = *repository.insert (new AHB11 ((str = "HB11"))).first;
//     AtomType::aHB12 = *repository.insert (new AHB12 ((str = "HB12"))).first;
//     AtomType::aHB2 = *repository.insert (new AHB2 ((str = "HB2"))).first;
//     AtomType::aHB2* = *repository.insert (new AHB2* ((str = "HB2*"))).first;
//     AtomType::aHB3 = *repository.insert (new AHB3 ((str = "HB3"))).first;
//     AtomType::aHB4 = *repository.insert (new AHB4 ((str = "HB4"))).first;
//     AtomType::aHB41 = *repository.insert (new AHB41 ((str = "HB41"))).first;
//     AtomType::aHB42 = *repository.insert (new AHB42 ((str = "HB42"))).first;
//     AtomType::aHB5 = *repository.insert (new AHB5 ((str = "HB5"))).first;
//     AtomType::aHB6 = *repository.insert (new AHB6 ((str = "HB6"))).first;
//     AtomType::aHB7 = *repository.insert (new AHB7 ((str = "HB7"))).first;
//     AtomType::aHB8 = *repository.insert (new AHB8 ((str = "HB8"))).first;
//     AtomType::aHBA = *repository.insert (new AHBA ((str = "HBA"))).first;
//     AtomType::aHBB = *repository.insert (new AHBB ((str = "HBB"))).first;
//     AtomType::aHBC = *repository.insert (new AHBC ((str = "HBC"))).first;
//     AtomType::aHBCF = *repository.insert (new AHBCF ((str = "HBCF"))).first;
//     AtomType::aHBCG = *repository.insert (new AHBCG ((str = "HBCG"))).first;
//     AtomType::aHBCR = *repository.insert (new AHBCR ((str = "HBCR"))).first;
//     AtomType::aHBD = *repository.insert (new AHBD ((str = "HBD"))).first;
//     AtomType::aHBE = *repository.insert (new AHBE ((str = "HBE"))).first;
//     AtomType::aHBF = *repository.insert (new AHBF ((str = "HBF"))).first;
//     AtomType::aHBG = *repository.insert (new AHBG ((str = "HBG"))).first;
//     AtomType::aHBH = *repository.insert (new AHBH ((str = "HBH"))).first;
//     AtomType::aHBI = *repository.insert (new AHBI ((str = "HBI"))).first;
//     AtomType::aHBJ = *repository.insert (new AHBJ ((str = "HBJ"))).first;
//     AtomType::aHBK = *repository.insert (new AHBK ((str = "HBK"))).first;
//     AtomType::aHBL = *repository.insert (new AHBL ((str = "HBL"))).first;
//     AtomType::aHBM = *repository.insert (new AHBM ((str = "HBM"))).first;
//     AtomType::aHBN = *repository.insert (new AHBN ((str = "HBN"))).first;
//     AtomType::aHBO = *repository.insert (new AHBO ((str = "HBO"))).first;
//     AtomType::aHBP = *repository.insert (new AHBP ((str = "HBP"))).first;
//     AtomType::aHBQ = *repository.insert (new AHBQ ((str = "HBQ"))).first;
//     AtomType::aHBR = *repository.insert (new AHBR ((str = "HBR"))).first;
//     AtomType::aHBS = *repository.insert (new AHBS ((str = "HBS"))).first;
//     AtomType::aHBT = *repository.insert (new AHBT ((str = "HBT"))).first;
//     AtomType::aHBU = *repository.insert (new AHBU ((str = "HBU"))).first;
//     AtomType::aHBV = *repository.insert (new AHBV ((str = "HBV"))).first;
//     AtomType::aHBW = *repository.insert (new AHBW ((str = "HBW"))).first;
//     AtomType::aHBX = *repository.insert (new AHBX ((str = "HBX"))).first;
//     AtomType::aHBY = *repository.insert (new AHBY ((str = "HBY"))).first;
//     AtomType::aHBZ = *repository.insert (new AHBZ ((str = "HBZ"))).first;
//     AtomType::aHC = *repository.insert (new AHC ((str = "HC"))).first;
//     AtomType::aHC* = *repository.insert (new AHC* ((str = "HC*"))).first;
//     AtomType::aHC0 = *repository.insert (new AHC0 ((str = "HC0"))).first;
//     AtomType::aHC1 = *repository.insert (new AHC1 ((str = "HC1"))).first;
//     AtomType::aHC1* = *repository.insert (new AHC1* ((str = "HC1*"))).first;
//     AtomType::aHC10 = *repository.insert (new AHC10 ((str = "HC10"))).first;
//     AtomType::aHC11 = *repository.insert (new AHC11 ((str = "HC11"))).first;
//     AtomType::aHC12 = *repository.insert (new AHC12 ((str = "HC12"))).first;
//     AtomType::aHC13 = *repository.insert (new AHC13 ((str = "HC13"))).first;
//     AtomType::aHC14 = *repository.insert (new AHC14 ((str = "HC14"))).first;
//     AtomType::aHC15 = *repository.insert (new AHC15 ((str = "HC15"))).first;
//     AtomType::aHC16 = *repository.insert (new AHC16 ((str = "HC16"))).first;
//     AtomType::aHC17 = *repository.insert (new AHC17 ((str = "HC17"))).first;
//     AtomType::aHC18 = *repository.insert (new AHC18 ((str = "HC18"))).first;
//     AtomType::aHC19 = *repository.insert (new AHC19 ((str = "HC19"))).first;
//     AtomType::aHC1A = *repository.insert (new AHC1A ((str = "HC1A"))).first;
//     AtomType::aHC1B = *repository.insert (new AHC1B ((str = "HC1B"))).first;
//     AtomType::aHC1C = *repository.insert (new AHC1C ((str = "HC1C"))).first;
//     AtomType::aHC1F = *repository.insert (new AHC1F ((str = "HC1F"))).first;
//     AtomType::aHC1I = *repository.insert (new AHC1I ((str = "HC1I"))).first;
//     AtomType::aHC1J = *repository.insert (new AHC1J ((str = "HC1J"))).first;
//     AtomType::aHC1L = *repository.insert (new AHC1L ((str = "HC1L"))).first;
//     AtomType::aHC1M = *repository.insert (new AHC1M ((str = "HC1M"))).first;
//     AtomType::aHC1P = *repository.insert (new AHC1P ((str = "HC1P"))).first;
//     AtomType::aHC2 = *repository.insert (new AHC2 ((str = "HC2"))).first;
//     AtomType::aHC2* = *repository.insert (new AHC2* ((str = "HC2*"))).first;
//     AtomType::aHC20 = *repository.insert (new AHC20 ((str = "HC20"))).first;
//     AtomType::aHC21 = *repository.insert (new AHC21 ((str = "HC21"))).first;
//     AtomType::aHC22 = *repository.insert (new AHC22 ((str = "HC22"))).first;
//     AtomType::aHC23 = *repository.insert (new AHC23 ((str = "HC23"))).first;
//     AtomType::aHC24 = *repository.insert (new AHC24 ((str = "HC24"))).first;
//     AtomType::aHC25 = *repository.insert (new AHC25 ((str = "HC25"))).first;
//     AtomType::aHC26 = *repository.insert (new AHC26 ((str = "HC26"))).first;
//     AtomType::aHC27 = *repository.insert (new AHC27 ((str = "HC27"))).first;
//     AtomType::aHC28 = *repository.insert (new AHC28 ((str = "HC28"))).first;
//     AtomType::aHC29 = *repository.insert (new AHC29 ((str = "HC29"))).first;
//     AtomType::aHC2A = *repository.insert (new AHC2A ((str = "HC2A"))).first;
//     AtomType::aHC2B = *repository.insert (new AHC2B ((str = "HC2B"))).first;
//     AtomType::aHC2C = *repository.insert (new AHC2C ((str = "HC2C"))).first;
//     AtomType::aHC2P = *repository.insert (new AHC2P ((str = "HC2P"))).first;
//     AtomType::aHC2Q = *repository.insert (new AHC2Q ((str = "HC2Q"))).first;
//     AtomType::aHC2R = *repository.insert (new AHC2R ((str = "HC2R"))).first;
//     AtomType::aHC3 = *repository.insert (new AHC3 ((str = "HC3"))).first;
//     AtomType::aHC3* = *repository.insert (new AHC3* ((str = "HC3*"))).first;
//     AtomType::aHC30 = *repository.insert (new AHC30 ((str = "HC30"))).first;
//     AtomType::aHC31 = *repository.insert (new AHC31 ((str = "HC31"))).first;
//     AtomType::aHC32 = *repository.insert (new AHC32 ((str = "HC32"))).first;
//     AtomType::aHC33 = *repository.insert (new AHC33 ((str = "HC33"))).first;
//     AtomType::aHC34 = *repository.insert (new AHC34 ((str = "HC34"))).first;
//     AtomType::aHC35 = *repository.insert (new AHC35 ((str = "HC35"))).first;
//     AtomType::aHC36 = *repository.insert (new AHC36 ((str = "HC36"))).first;
//     AtomType::aHC37 = *repository.insert (new AHC37 ((str = "HC37"))).first;
//     AtomType::aHC38 = *repository.insert (new AHC38 ((str = "HC38"))).first;
//     AtomType::aHC39 = *repository.insert (new AHC39 ((str = "HC39"))).first;
//     AtomType::aHC3A = *repository.insert (new AHC3A ((str = "HC3A"))).first;
//     AtomType::aHC3B = *repository.insert (new AHC3B ((str = "HC3B"))).first;
//     AtomType::aHC3C = *repository.insert (new AHC3C ((str = "HC3C"))).first;
//     AtomType::aHC3J = *repository.insert (new AHC3J ((str = "HC3J"))).first;
//     AtomType::aHC3K = *repository.insert (new AHC3K ((str = "HC3K"))).first;
//     AtomType::aHC3L = *repository.insert (new AHC3L ((str = "HC3L"))).first;
//     AtomType::aHC3M = *repository.insert (new AHC3M ((str = "HC3M"))).first;
//     AtomType::aHC3N = *repository.insert (new AHC3N ((str = "HC3N"))).first;
//     AtomType::aHC3P = *repository.insert (new AHC3P ((str = "HC3P"))).first;
//     AtomType::aHC3Q = *repository.insert (new AHC3Q ((str = "HC3Q"))).first;
//     AtomType::aHC3R = *repository.insert (new AHC3R ((str = "HC3R"))).first;
//     AtomType::aHC4 = *repository.insert (new AHC4 ((str = "HC4"))).first;
//     AtomType::aHC4* = *repository.insert (new AHC4* ((str = "HC4*"))).first;
//     AtomType::aHC41 = *repository.insert (new AHC41 ((str = "HC41"))).first;
//     AtomType::aHC42 = *repository.insert (new AHC42 ((str = "HC42"))).first;
//     AtomType::aHC43 = *repository.insert (new AHC43 ((str = "HC43"))).first;
//     AtomType::aHC44 = *repository.insert (new AHC44 ((str = "HC44"))).first;
//     AtomType::aHC46 = *repository.insert (new AHC46 ((str = "HC46"))).first;
//     AtomType::aHC47 = *repository.insert (new AHC47 ((str = "HC47"))).first;
//     AtomType::aHC4A = *repository.insert (new AHC4A ((str = "HC4A"))).first;
//     AtomType::aHC4B = *repository.insert (new AHC4B ((str = "HC4B"))).first;
//     AtomType::aHC4C = *repository.insert (new AHC4C ((str = "HC4C"))).first;
//     AtomType::aHC4P = *repository.insert (new AHC4P ((str = "HC4P"))).first;
//     AtomType::aHC4Q = *repository.insert (new AHC4Q ((str = "HC4Q"))).first;
//     AtomType::aHC4R = *repository.insert (new AHC4R ((str = "HC4R"))).first;
//     AtomType::aHC5 = *repository.insert (new AHC5 ((str = "HC5"))).first;
//     AtomType::aHC5* = *repository.insert (new AHC5* ((str = "HC5*"))).first;
//     AtomType::aHC51 = *repository.insert (new AHC51 ((str = "HC51"))).first;
//     AtomType::aHC52 = *repository.insert (new AHC52 ((str = "HC52"))).first;
//     AtomType::aHC53 = *repository.insert (new AHC53 ((str = "HC53"))).first;
//     AtomType::aHC54 = *repository.insert (new AHC54 ((str = "HC54"))).first;
//     AtomType::aHC55 = *repository.insert (new AHC55 ((str = "HC55"))).first;
//     AtomType::aHC56 = *repository.insert (new AHC56 ((str = "HC56"))).first;
//     AtomType::aHC5A = *repository.insert (new AHC5A ((str = "HC5A"))).first;
//     AtomType::aHC5B = *repository.insert (new AHC5B ((str = "HC5B"))).first;
//     AtomType::aHC5C = *repository.insert (new AHC5C ((str = "HC5C"))).first;
//     AtomType::aHC5P = *repository.insert (new AHC5P ((str = "HC5P"))).first;
//     AtomType::aHC6 = *repository.insert (new AHC6 ((str = "HC6"))).first;
//     AtomType::aHC6* = *repository.insert (new AHC6* ((str = "HC6*"))).first;
//     AtomType::aHC63 = *repository.insert (new AHC63 ((str = "HC63"))).first;
//     AtomType::aHC64 = *repository.insert (new AHC64 ((str = "HC64"))).first;
//     AtomType::aHC65 = *repository.insert (new AHC65 ((str = "HC65"))).first;
//     AtomType::aHC66 = *repository.insert (new AHC66 ((str = "HC66"))).first;
//     AtomType::aHC6F = *repository.insert (new AHC6F ((str = "HC6F"))).first;
//     AtomType::aHC7 = *repository.insert (new AHC7 ((str = "HC7"))).first;
//     AtomType::aHC7B = *repository.insert (new AHC7B ((str = "HC7B"))).first;
//     AtomType::aHC8 = *repository.insert (new AHC8 ((str = "HC8"))).first;
//     AtomType::aHC8B = *repository.insert (new AHC8B ((str = "HC8B"))).first;
//     AtomType::aHC9 = *repository.insert (new AHC9 ((str = "HC9"))).first;
//     AtomType::aHC9F = *repository.insert (new AHC9F ((str = "HC9F"))).first;
//     AtomType::aHCA = *repository.insert (new AHCA ((str = "HCA"))).first;
//     AtomType::aHCA1 = *repository.insert (new AHCA1 ((str = "HCA1"))).first;
//     AtomType::aHCA2 = *repository.insert (new AHCA2 ((str = "HCA2"))).first;
//     AtomType::aHCA3 = *repository.insert (new AHCA3 ((str = "HCA3"))).first;
//     AtomType::aHCA4 = *repository.insert (new AHCA4 ((str = "HCA4"))).first;
//     AtomType::aHCA6 = *repository.insert (new AHCA6 ((str = "HCA6"))).first;
//     AtomType::aHCAM = *repository.insert (new AHCAM ((str = "HCAM"))).first;
//     AtomType::aHCB = *repository.insert (new AHCB ((str = "HCB"))).first;
//     AtomType::aHCB1 = *repository.insert (new AHCB1 ((str = "HCB1"))).first;
//     AtomType::aHCB2 = *repository.insert (new AHCB2 ((str = "HCB2"))).first;
//     AtomType::aHCB3 = *repository.insert (new AHCB3 ((str = "HCB3"))).first;
//     AtomType::aHCB4 = *repository.insert (new AHCB4 ((str = "HCB4"))).first;
//     AtomType::aHCB6 = *repository.insert (new AHCB6 ((str = "HCB6"))).first;
//     AtomType::aHCC = *repository.insert (new AHCC ((str = "HCC"))).first;
//     AtomType::aHCC5 = *repository.insert (new AHCC5 ((str = "HCC5"))).first;
//     AtomType::aHCD = *repository.insert (new AHCD ((str = "HCD"))).first;
//     AtomType::aHCD1 = *repository.insert (new AHCD1 ((str = "HCD1"))).first;
//     AtomType::aHCD2 = *repository.insert (new AHCD2 ((str = "HCD2"))).first;
//     AtomType::aHCE = *repository.insert (new AHCE ((str = "HCE"))).first;
//     AtomType::aHCE1 = *repository.insert (new AHCE1 ((str = "HCE1"))).first;
//     AtomType::aHCE2 = *repository.insert (new AHCE2 ((str = "HCE2"))).first;
//     AtomType::aHCF = *repository.insert (new AHCF ((str = "HCF"))).first;
//     AtomType::aHCG = *repository.insert (new AHCG ((str = "HCG"))).first;
//     AtomType::aHCH = *repository.insert (new AHCH ((str = "HCH"))).first;
//     AtomType::aHCI = *repository.insert (new AHCI ((str = "HCI"))).first;
//     AtomType::aHCJ = *repository.insert (new AHCJ ((str = "HCJ"))).first;
//     AtomType::aHCK = *repository.insert (new AHCK ((str = "HCK"))).first;
//     AtomType::aHCK1 = *repository.insert (new AHCK1 ((str = "HCK1"))).first;
//     AtomType::aHCK5 = *repository.insert (new AHCK5 ((str = "HCK5"))).first;
//     AtomType::aHCK6 = *repository.insert (new AHCK6 ((str = "HCK6"))).first;
//     AtomType::aHCK8 = *repository.insert (new AHCK8 ((str = "HCK8"))).first;
//     AtomType::aHCK9 = *repository.insert (new AHCK9 ((str = "HCK9"))).first;
//     AtomType::aHCL = *repository.insert (new AHCL ((str = "HCL"))).first;
//     AtomType::aHCM = *repository.insert (new AHCM ((str = "HCM"))).first;
//     AtomType::aHCN = *repository.insert (new AHCN ((str = "HCN"))).first;
//     AtomType::aHCN1 = *repository.insert (new AHCN1 ((str = "HCN1"))).first;
//     AtomType::aHCN2 = *repository.insert (new AHCN2 ((str = "HCN2"))).first;
//     AtomType::aHCN3 = *repository.insert (new AHCN3 ((str = "HCN3"))).first;
//     AtomType::aHCN4 = *repository.insert (new AHCN4 ((str = "HCN4"))).first;
//     AtomType::aHCP1 = *repository.insert (new AHCP1 ((str = "HCP1"))).first;
//     AtomType::aHCR = *repository.insert (new AHCR ((str = "HCR"))).first;
//     AtomType::aHCS = *repository.insert (new AHCS ((str = "HCS"))).first;
//     AtomType::aHCT = *repository.insert (new AHCT ((str = "HCT"))).first;
//     AtomType::aHCU = *repository.insert (new AHCU ((str = "HCU"))).first;
//     AtomType::aHCV2 = *repository.insert (new AHCV2 ((str = "HCV2"))).first;
//     AtomType::aHCV7 = *repository.insert (new AHCV7 ((str = "HCV7"))).first;
//     AtomType::aHCW = *repository.insert (new AHCW ((str = "HCW"))).first;
//     AtomType::aHCX = *repository.insert (new AHCX ((str = "HCX"))).first;
//     AtomType::aHCX1 = *repository.insert (new AHCX1 ((str = "HCX1"))).first;
//     AtomType::aHCX2 = *repository.insert (new AHCX2 ((str = "HCX2"))).first;
//     AtomType::aHCX3 = *repository.insert (new AHCX3 ((str = "HCX3"))).first;
//     AtomType::aHCX4 = *repository.insert (new AHCX4 ((str = "HCX4"))).first;
//     AtomType::aHCX5 = *repository.insert (new AHCX5 ((str = "HCX5"))).first;
//     AtomType::aHCY = *repository.insert (new AHCY ((str = "HCY"))).first;
//     AtomType::aHCZ = *repository.insert (new AHCZ ((str = "HCZ"))).first;
//     AtomType::aHD = *repository.insert (new AHD ((str = "HD"))).first;
//     AtomType::aHD* = *repository.insert (new AHD* ((str = "HD*"))).first;
//     AtomType::aHD1 = *repository.insert (new AHD1 ((str = "HD1"))).first;
//     AtomType::aHD1* = *repository.insert (new AHD1* ((str = "HD1*"))).first;
//     AtomType::aHD2 = *repository.insert (new AHD2 ((str = "HD2"))).first;
//     AtomType::aHD2* = *repository.insert (new AHD2* ((str = "HD2*"))).first;
//     AtomType::aHD3 = *repository.insert (new AHD3 ((str = "HD3"))).first;
//     AtomType::aHD4 = *repository.insert (new AHD4 ((str = "HD4"))).first;
//     AtomType::aHD5 = *repository.insert (new AHD5 ((str = "HD5"))).first;
//     AtomType::aHD6 = *repository.insert (new AHD6 ((str = "HD6"))).first;
//     AtomType::aHD8 = *repository.insert (new AHD8 ((str = "HD8"))).first;
//     AtomType::aHD9 = *repository.insert (new AHD9 ((str = "HD9"))).first;
//     AtomType::aHDA = *repository.insert (new AHDA ((str = "HDA"))).first;
//     AtomType::aHDA1 = *repository.insert (new AHDA1 ((str = "HDA1"))).first;
//     AtomType::aHDA2 = *repository.insert (new AHDA2 ((str = "HDA2"))).first;
//     AtomType::aHDB = *repository.insert (new AHDB ((str = "HDB"))).first;
//     AtomType::aHDB1 = *repository.insert (new AHDB1 ((str = "HDB1"))).first;
//     AtomType::aHDB2 = *repository.insert (new AHDB2 ((str = "HDB2"))).first;
//     AtomType::aHDC = *repository.insert (new AHDC ((str = "HDC"))).first;
//     AtomType::aHDC1 = *repository.insert (new AHDC1 ((str = "HDC1"))).first;
//     AtomType::aHDC2 = *repository.insert (new AHDC2 ((str = "HDC2"))).first;
//     AtomType::aHDD = *repository.insert (new AHDD ((str = "HDD"))).first;
//     AtomType::aHDD1 = *repository.insert (new AHDD1 ((str = "HDD1"))).first;
//     AtomType::aHDD2 = *repository.insert (new AHDD2 ((str = "HDD2"))).first;
//     AtomType::aHDE = *repository.insert (new AHDE ((str = "HDE"))).first;
//     AtomType::aHDE1 = *repository.insert (new AHDE1 ((str = "HDE1"))).first;
//     AtomType::aHDE2 = *repository.insert (new AHDE2 ((str = "HDE2"))).first;
//     AtomType::aHDF = *repository.insert (new AHDF ((str = "HDF"))).first;
//     AtomType::aHDF1 = *repository.insert (new AHDF1 ((str = "HDF1"))).first;
//     AtomType::aHDF2 = *repository.insert (new AHDF2 ((str = "HDF2"))).first;
//     AtomType::aHDG1 = *repository.insert (new AHDG1 ((str = "HDG1"))).first;
//     AtomType::aHDG2 = *repository.insert (new AHDG2 ((str = "HDG2"))).first;
//     AtomType::aHDH1 = *repository.insert (new AHDH1 ((str = "HDH1"))).first;
//     AtomType::aHDH2 = *repository.insert (new AHDH2 ((str = "HDH2"))).first;
//     AtomType::aHDI1 = *repository.insert (new AHDI1 ((str = "HDI1"))).first;
//     AtomType::aHDI2 = *repository.insert (new AHDI2 ((str = "HDI2"))).first;
//     AtomType::aHDJ1 = *repository.insert (new AHDJ1 ((str = "HDJ1"))).first;
//     AtomType::aHDJ2 = *repository.insert (new AHDJ2 ((str = "HDJ2"))).first;
//     AtomType::aHDK1 = *repository.insert (new AHDK1 ((str = "HDK1"))).first;
//     AtomType::aHDM = *repository.insert (new AHDM ((str = "HDM"))).first;
//     AtomType::aHDT = *repository.insert (new AHDT ((str = "HDT"))).first;
//     AtomType::aHE = *repository.insert (new AHE ((str = "HE"))).first;
//     AtomType::aHE* = *repository.insert (new AHE* ((str = "HE*"))).first;
//     AtomType::aHE1 = *repository.insert (new AHE1 ((str = "HE1"))).first;
//     AtomType::aHE2 = *repository.insert (new AHE2 ((str = "HE2"))).first;
//     AtomType::aHE2* = *repository.insert (new AHE2* ((str = "HE2*"))).first;
//     AtomType::aHE3 = *repository.insert (new AHE3 ((str = "HE3"))).first;
//     AtomType::aHE3* = *repository.insert (new AHE3* ((str = "HE3*"))).first;
//     AtomType::aHE4 = *repository.insert (new AHE4 ((str = "HE4"))).first;
//     AtomType::aHE4* = *repository.insert (new AHE4* ((str = "HE4*"))).first;
//     AtomType::aHE5 = *repository.insert (new AHE5 ((str = "HE5"))).first;
//     AtomType::aHE5* = *repository.insert (new AHE5* ((str = "HE5*"))).first;
//     AtomType::aHE6 = *repository.insert (new AHE6 ((str = "HE6"))).first;
//     AtomType::aHE6* = *repository.insert (new AHE6* ((str = "HE6*"))).first;
//     AtomType::aHEA = *repository.insert (new AHEA ((str = "HEA"))).first;
//     AtomType::aHEB = *repository.insert (new AHEB ((str = "HEB"))).first;
//     AtomType::aHEC = *repository.insert (new AHEC ((str = "HEC"))).first;
//     AtomType::aHEF = *repository.insert (new AHEF ((str = "HEF"))).first;
//     AtomType::aHF = *repository.insert (new AHF ((str = "HF"))).first;
//     AtomType::aHF1 = *repository.insert (new AHF1 ((str = "HF1"))).first;
//     AtomType::aHF2 = *repository.insert (new AHF2 ((str = "HF2"))).first;
//     AtomType::aHF2* = *repository.insert (new AHF2* ((str = "HF2*"))).first;
//     AtomType::aHF3* = *repository.insert (new AHF3* ((str = "HF3*"))).first;
//     AtomType::aHF5* = *repository.insert (new AHF5* ((str = "HF5*"))).first;
//     AtomType::aHF6* = *repository.insert (new AHF6* ((str = "HF6*"))).first;
//     AtomType::aHFA = *repository.insert (new AHFA ((str = "HFA"))).first;
//     AtomType::aHFB = *repository.insert (new AHFB ((str = "HFB"))).first;
//     AtomType::aHFC = *repository.insert (new AHFC ((str = "HFC"))).first;
//     AtomType::aHFD = *repository.insert (new AHFD ((str = "HFD"))).first;
//     AtomType::aHFE = *repository.insert (new AHFE ((str = "HFE"))).first;
//     AtomType::aHFF = *repository.insert (new AHFF ((str = "HFF"))).first;
//     AtomType::aHFM1 = *repository.insert (new AHFM1 ((str = "HFM1"))).first;
//     AtomType::aHFM2 = *repository.insert (new AHFM2 ((str = "HFM2"))).first;
//     AtomType::aHFM3 = *repository.insert (new AHFM3 ((str = "HFM3"))).first;
//     AtomType::aHG = *repository.insert (new AHG ((str = "HG"))).first;
//     AtomType::aHG* = *repository.insert (new AHG* ((str = "HG*"))).first;
//     AtomType::aHG1 = *repository.insert (new AHG1 ((str = "HG1"))).first;
//     AtomType::aHG1* = *repository.insert (new AHG1* ((str = "HG1*"))).first;
//     AtomType::aHG11 = *repository.insert (new AHG11 ((str = "HG11"))).first;
//     AtomType::aHG12 = *repository.insert (new AHG12 ((str = "HG12"))).first;
//     AtomType::aHG13 = *repository.insert (new AHG13 ((str = "HG13"))).first;
//     AtomType::aHG2 = *repository.insert (new AHG2 ((str = "HG2"))).first;
//     AtomType::aHG2* = *repository.insert (new AHG2* ((str = "HG2*"))).first;
//     AtomType::aHG21 = *repository.insert (new AHG21 ((str = "HG21"))).first;
//     AtomType::aHG22 = *repository.insert (new AHG22 ((str = "HG22"))).first;
//     AtomType::aHG23 = *repository.insert (new AHG23 ((str = "HG23"))).first;
//     AtomType::aHG3 = *repository.insert (new AHG3 ((str = "HG3"))).first;
//     AtomType::aHG4 = *repository.insert (new AHG4 ((str = "HG4"))).first;
//     AtomType::aHG5 = *repository.insert (new AHG5 ((str = "HG5"))).first;
//     AtomType::aHG6 = *repository.insert (new AHG6 ((str = "HG6"))).first;
//     AtomType::aHGA = *repository.insert (new AHGA ((str = "HGA"))).first;
//     AtomType::aHGB = *repository.insert (new AHGB ((str = "HGB"))).first;
//     AtomType::aHGC = *repository.insert (new AHGC ((str = "HGC"))).first;
//     AtomType::aHGF = *repository.insert (new AHGF ((str = "HGF"))).first;
//     AtomType::aHGI = *repository.insert (new AHGI ((str = "HGI"))).first;
//     AtomType::aHGL = *repository.insert (new AHGL ((str = "HGL"))).first;
//     AtomType::aHGM = *repository.insert (new AHGM ((str = "HGM"))).first;
//     AtomType::aHGT = *repository.insert (new AHGT ((str = "HGT"))).first;
//     AtomType::aHGY = *repository.insert (new AHGY ((str = "HGY"))).first;
//     AtomType::aHH = *repository.insert (new AHH ((str = "HH"))).first;
//     AtomType::aHH* = *repository.insert (new AHH* ((str = "HH*"))).first;
//     AtomType::aHH1 = *repository.insert (new AHH1 ((str = "HH1"))).first;
//     AtomType::aHH11 = *repository.insert (new AHH11 ((str = "HH11"))).first;
//     AtomType::aHH12 = *repository.insert (new AHH12 ((str = "HH12"))).first;
//     AtomType::aHH2 = *repository.insert (new AHH2 ((str = "HH2"))).first;
//     AtomType::aHH21 = *repository.insert (new AHH21 ((str = "HH21"))).first;
//     AtomType::aHH22 = *repository.insert (new AHH22 ((str = "HH22"))).first;
//     AtomType::aHH3 = *repository.insert (new AHH3 ((str = "HH3"))).first;
//     AtomType::aHHA = *repository.insert (new AHHA ((str = "HHA"))).first;
//     AtomType::aHHB = *repository.insert (new AHHB ((str = "HHB"))).first;
//     AtomType::aHHC = *repository.insert (new AHHC ((str = "HHC"))).first;
//     AtomType::aHHD = *repository.insert (new AHHD ((str = "HHD"))).first;
//     AtomType::aHHF = *repository.insert (new AHHF ((str = "HHF"))).first;
//     AtomType::aHHN = *repository.insert (new AHHN ((str = "HHN"))).first;
//     AtomType::aHHN1 = *repository.insert (new AHHN1 ((str = "HHN1"))).first;
//     AtomType::aHHN4 = *repository.insert (new AHHN4 ((str = "HHN4"))).first;
//     AtomType::aHHO2 = *repository.insert (new AHHO2 ((str = "HHO2"))).first;
//     AtomType::aHHO3 = *repository.insert (new AHHO3 ((str = "HHO3"))).first;
//     AtomType::aHHO6 = *repository.insert (new AHHO6 ((str = "HHO6"))).first;
//     AtomType::aHI = *repository.insert (new AHI ((str = "HI"))).first;
//     AtomType::aHI* = *repository.insert (new AHI* ((str = "HI*"))).first;
//     AtomType::aHI1 = *repository.insert (new AHI1 ((str = "HI1"))).first;
//     AtomType::aHI2 = *repository.insert (new AHI2 ((str = "HI2"))).first;
//     AtomType::aHI3 = *repository.insert (new AHI3 ((str = "HI3"))).first;
//     AtomType::aHI4 = *repository.insert (new AHI4 ((str = "HI4"))).first;
//     AtomType::aHI5 = *repository.insert (new AHI5 ((str = "HI5"))).first;
//     AtomType::aHI6 = *repository.insert (new AHI6 ((str = "HI6"))).first;
//     AtomType::aHJ = *repository.insert (new AHJ ((str = "HJ"))).first;
//     AtomType::aHJ* = *repository.insert (new AHJ* ((str = "HJ*"))).first;
//     AtomType::aHJ1 = *repository.insert (new AHJ1 ((str = "HJ1"))).first;
//     AtomType::aHJ2 = *repository.insert (new AHJ2 ((str = "HJ2"))).first;
//     AtomType::aHJ3 = *repository.insert (new AHJ3 ((str = "HJ3"))).first;
//     AtomType::aHJ4 = *repository.insert (new AHJ4 ((str = "HJ4"))).first;
//     AtomType::aHJ5 = *repository.insert (new AHJ5 ((str = "HJ5"))).first;
//     AtomType::aHJ6 = *repository.insert (new AHJ6 ((str = "HJ6"))).first;
//     AtomType::aHJA = *repository.insert (new AHJA ((str = "HJA"))).first;
//     AtomType::aHJB = *repository.insert (new AHJB ((str = "HJB"))).first;
//     AtomType::aHK = *repository.insert (new AHK ((str = "HK"))).first;
//     AtomType::aHK* = *repository.insert (new AHK* ((str = "HK*"))).first;
//     AtomType::aHK1 = *repository.insert (new AHK1 ((str = "HK1"))).first;
//     AtomType::aHK2 = *repository.insert (new AHK2 ((str = "HK2"))).first;
//     AtomType::aHKA = *repository.insert (new AHKA ((str = "HKA"))).first;
//     AtomType::aHKB = *repository.insert (new AHKB ((str = "HKB"))).first;
//     AtomType::aHL = *repository.insert (new AHL ((str = "HL"))).first;
//     AtomType::aHL1 = *repository.insert (new AHL1 ((str = "HL1"))).first;
//     AtomType::aHL2 = *repository.insert (new AHL2 ((str = "HL2"))).first;
//     AtomType::aHLA = *repository.insert (new AHLA ((str = "HLA"))).first;
//     AtomType::aHLB = *repository.insert (new AHLB ((str = "HLB"))).first;
//     AtomType::aHM = *repository.insert (new AHM ((str = "HM"))).first;
//     AtomType::aHM* = *repository.insert (new AHM* ((str = "HM*"))).first;
//     AtomType::aHM1 = *repository.insert (new AHM1 ((str = "HM1"))).first;
//     AtomType::aHM11 = *repository.insert (new AHM11 ((str = "HM11"))).first;
//     AtomType::aHM12 = *repository.insert (new AHM12 ((str = "HM12"))).first;
//     AtomType::aHM13 = *repository.insert (new AHM13 ((str = "HM13"))).first;
//     AtomType::aHM2 = *repository.insert (new AHM2 ((str = "HM2"))).first;
//     AtomType::aHM21 = *repository.insert (new AHM21 ((str = "HM21"))).first;
//     AtomType::aHM22 = *repository.insert (new AHM22 ((str = "HM22"))).first;
//     AtomType::aHM3 = *repository.insert (new AHM3 ((str = "HM3"))).first;
//     AtomType::aHM31 = *repository.insert (new AHM31 ((str = "HM31"))).first;
//     AtomType::aHM32 = *repository.insert (new AHM32 ((str = "HM32"))).first;
//     AtomType::aHM33 = *repository.insert (new AHM33 ((str = "HM33"))).first;
//     AtomType::aHM41 = *repository.insert (new AHM41 ((str = "HM41"))).first;
//     AtomType::aHM42 = *repository.insert (new AHM42 ((str = "HM42"))).first;
//     AtomType::aHM43 = *repository.insert (new AHM43 ((str = "HM43"))).first;
//     AtomType::aHM51 = *repository.insert (new AHM51 ((str = "HM51"))).first;
//     AtomType::aHM52 = *repository.insert (new AHM52 ((str = "HM52"))).first;
//     AtomType::aHM53 = *repository.insert (new AHM53 ((str = "HM53"))).first;
//     AtomType::aHM71 = *repository.insert (new AHM71 ((str = "HM71"))).first;
//     AtomType::aHM72 = *repository.insert (new AHM72 ((str = "HM72"))).first;
//     AtomType::aHM73 = *repository.insert (new AHM73 ((str = "HM73"))).first;
//     AtomType::aHM81 = *repository.insert (new AHM81 ((str = "HM81"))).first;
//     AtomType::aHM82 = *repository.insert (new AHM82 ((str = "HM82"))).first;
//     AtomType::aHM83 = *repository.insert (new AHM83 ((str = "HM83"))).first;
//     AtomType::aHMA = *repository.insert (new AHMA ((str = "HMA"))).first;
//     AtomType::aHMB = *repository.insert (new AHMB ((str = "HMB"))).first;
//     AtomType::aHMC = *repository.insert (new AHMC ((str = "HMC"))).first;
//     AtomType::aHMD = *repository.insert (new AHMD ((str = "HMD"))).first;
//     AtomType::aHME1 = *repository.insert (new AHME1 ((str = "HME1"))).first;
//     AtomType::aHME2 = *repository.insert (new AHME2 ((str = "HME2"))).first;
//     AtomType::aHME3 = *repository.insert (new AHME3 ((str = "HME3"))).first;
//     AtomType::aHN = *repository.insert (new AHN ((str = "HN"))).first;
//     AtomType::aHN" = *repository.insert (new AHN" ((str = "HN""))).first;
//     AtomType::aHN* = *repository.insert (new AHN* ((str = "HN*"))).first;
//     AtomType::aHN0 = *repository.insert (new AHN0 ((str = "HN0"))).first;
//     AtomType::aHN10 = *repository.insert (new AHN10 ((str = "HN10"))).first;
//     AtomType::aHN11 = *repository.insert (new AHN11 ((str = "HN11"))).first;
//     AtomType::aHN12 = *repository.insert (new AHN12 ((str = "HN12"))).first;
//     AtomType::aHN13 = *repository.insert (new AHN13 ((str = "HN13"))).first;
//     AtomType::aHN14 = *repository.insert (new AHN14 ((str = "HN14"))).first;
//     AtomType::aHN15 = *repository.insert (new AHN15 ((str = "HN15"))).first;
//     AtomType::aHN16 = *repository.insert (new AHN16 ((str = "HN16"))).first;
//     AtomType::aHN17 = *repository.insert (new AHN17 ((str = "HN17"))).first;
//     AtomType::aHN18 = *repository.insert (new AHN18 ((str = "HN18"))).first;
//     AtomType::aHN19 = *repository.insert (new AHN19 ((str = "HN19"))).first;
//     AtomType::aHN1A = *repository.insert (new AHN1A ((str = "HN1A"))).first;
//     AtomType::aHN1F = *repository.insert (new AHN1F ((str = "HN1F"))).first;
//     AtomType::aHN1J = *repository.insert (new AHN1J ((str = "HN1J"))).first;
//     AtomType::aHN2* = *repository.insert (new AHN2* ((str = "HN2*"))).first;
//     AtomType::aHN20 = *repository.insert (new AHN20 ((str = "HN20"))).first;
//     AtomType::aHN21 = *repository.insert (new AHN21 ((str = "HN21"))).first;
//     AtomType::aHN22 = *repository.insert (new AHN22 ((str = "HN22"))).first;
//     AtomType::aHN23 = *repository.insert (new AHN23 ((str = "HN23"))).first;
//     AtomType::aHN24 = *repository.insert (new AHN24 ((str = "HN24"))).first;
//     AtomType::aHN25 = *repository.insert (new AHN25 ((str = "HN25"))).first;
//     AtomType::aHN26 = *repository.insert (new AHN26 ((str = "HN26"))).first;
//     AtomType::aHN28 = *repository.insert (new AHN28 ((str = "HN28"))).first;
//     AtomType::aHN29 = *repository.insert (new AHN29 ((str = "HN29"))).first;
//     AtomType::aHN2A = *repository.insert (new AHN2A ((str = "HN2A"))).first;
//     AtomType::aHN2B = *repository.insert (new AHN2B ((str = "HN2B"))).first;
//     AtomType::aHN3* = *repository.insert (new AHN3* ((str = "HN3*"))).first;
//     AtomType::aHN30 = *repository.insert (new AHN30 ((str = "HN30"))).first;
//     AtomType::aHN31 = *repository.insert (new AHN31 ((str = "HN31"))).first;
//     AtomType::aHN32 = *repository.insert (new AHN32 ((str = "HN32"))).first;
//     AtomType::aHN34 = *repository.insert (new AHN34 ((str = "HN34"))).first;
//     AtomType::aHN35 = *repository.insert (new AHN35 ((str = "HN35"))).first;
//     AtomType::aHN36 = *repository.insert (new AHN36 ((str = "HN36"))).first;
//     AtomType::aHN37 = *repository.insert (new AHN37 ((str = "HN37"))).first;
//     AtomType::aHN3F = *repository.insert (new AHN3F ((str = "HN3F"))).first;
//     AtomType::aHN3G = *repository.insert (new AHN3G ((str = "HN3G"))).first;
//     AtomType::aHN3T = *repository.insert (new AHN3T ((str = "HN3T"))).first;
//     AtomType::aHN4 = *repository.insert (new AHN4 ((str = "HN4"))).first;
//     AtomType::aHN40 = *repository.insert (new AHN40 ((str = "HN40"))).first;
//     AtomType::aHN41 = *repository.insert (new AHN41 ((str = "HN41"))).first;
//     AtomType::aHN42 = *repository.insert (new AHN42 ((str = "HN42"))).first;
//     AtomType::aHN44 = *repository.insert (new AHN44 ((str = "HN44"))).first;
//     AtomType::aHN48 = *repository.insert (new AHN48 ((str = "HN48"))).first;
//     AtomType::aHN4A = *repository.insert (new AHN4A ((str = "HN4A"))).first;
//     AtomType::aHN4B = *repository.insert (new AHN4B ((str = "HN4B"))).first;
//     AtomType::aHN5 = *repository.insert (new AHN5 ((str = "HN5"))).first;
//     AtomType::aHN5* = *repository.insert (new AHN5* ((str = "HN5*"))).first;
//     AtomType::aHN50 = *repository.insert (new AHN50 ((str = "HN50"))).first;
//     AtomType::aHN51 = *repository.insert (new AHN51 ((str = "HN51"))).first;
//     AtomType::aHN52 = *repository.insert (new AHN52 ((str = "HN52"))).first;
//     AtomType::aHN59 = *repository.insert (new AHN59 ((str = "HN59"))).first;
//     AtomType::aHN5G = *repository.insert (new AHN5G ((str = "HN5G"))).first;
//     AtomType::aHN6 = *repository.insert (new AHN6 ((str = "HN6"))).first;
//     AtomType::aHN7 = *repository.insert (new AHN7 ((str = "HN7"))).first;
//     AtomType::aHN76 = *repository.insert (new AHN76 ((str = "HN76"))).first;
//     AtomType::aHN8 = *repository.insert (new AHN8 ((str = "HN8"))).first;
//     AtomType::aHN9 = *repository.insert (new AHN9 ((str = "HN9"))).first;
//     AtomType::aHN94 = *repository.insert (new AHN94 ((str = "HN94"))).first;
//     AtomType::aHNA = *repository.insert (new AHNA ((str = "HNA"))).first;
//     AtomType::aHNAC = *repository.insert (new AHNAC ((str = "HNAC"))).first;
//     AtomType::aHNAD = *repository.insert (new AHNAD ((str = "HNAD"))).first;
//     AtomType::aHNAE = *repository.insert (new AHNAE ((str = "HNAE"))).first;
//     AtomType::aHNAJ = *repository.insert (new AHNAJ ((str = "HNAJ"))).first;
//     AtomType::aHNAN = *repository.insert (new AHNAN ((str = "HNAN"))).first;
//     AtomType::aHNAP = *repository.insert (new AHNAP ((str = "HNAP"))).first;
//     AtomType::aHNAQ = *repository.insert (new AHNAQ ((str = "HNAQ"))).first;
//     AtomType::aHNAR = *repository.insert (new AHNAR ((str = "HNAR"))).first;
//     AtomType::aHNAS = *repository.insert (new AHNAS ((str = "HNAS"))).first;
//     AtomType::aHNAU = *repository.insert (new AHNAU ((str = "HNAU"))).first;
//     AtomType::aHNAY = *repository.insert (new AHNAY ((str = "HNAY"))).first;
//     AtomType::aHNAZ = *repository.insert (new AHNAZ ((str = "HNAZ"))).first;
//     AtomType::aHNB = *repository.insert (new AHNB ((str = "HNB"))).first;
//     AtomType::aHNBA = *repository.insert (new AHNBA ((str = "HNBA"))).first;
//     AtomType::aHNBB = *repository.insert (new AHNBB ((str = "HNBB"))).first;
//     AtomType::aHNBC = *repository.insert (new AHNBC ((str = "HNBC"))).first;
//     AtomType::aHNBD = *repository.insert (new AHNBD ((str = "HNBD"))).first;
//     AtomType::aHNBF = *repository.insert (new AHNBF ((str = "HNBF"))).first;
//     AtomType::aHNBJ = *repository.insert (new AHNBJ ((str = "HNBJ"))).first;
//     AtomType::aHNC = *repository.insert (new AHNC ((str = "HNC"))).first;
//     AtomType::aHNCE = *repository.insert (new AHNCE ((str = "HNCE"))).first;
//     AtomType::aHND = *repository.insert (new AHND ((str = "HND"))).first;
//     AtomType::aHND1 = *repository.insert (new AHND1 ((str = "HND1"))).first;
//     AtomType::aHND3 = *repository.insert (new AHND3 ((str = "HND3"))).first;
//     AtomType::aHNDC = *repository.insert (new AHNDC ((str = "HNDC"))).first;
//     AtomType::aHNE = *repository.insert (new AHNE ((str = "HNE"))).first;
//     AtomType::aHNE1 = *repository.insert (new AHNE1 ((str = "HNE1"))).first;
//     AtomType::aHNF = *repository.insert (new AHNF ((str = "HNF"))).first;
//     AtomType::aHNG = *repository.insert (new AHNG ((str = "HNG"))).first;
//     AtomType::aHNH = *repository.insert (new AHNH ((str = "HNH"))).first;
//     AtomType::aHNH1 = *repository.insert (new AHNH1 ((str = "HNH1"))).first;
//     AtomType::aHNH2 = *repository.insert (new AHNH2 ((str = "HNH2"))).first;
//     AtomType::aHNI = *repository.insert (new AHNI ((str = "HNI"))).first;
//     AtomType::aHNJ = *repository.insert (new AHNJ ((str = "HNJ"))).first;
//     AtomType::aHNK = *repository.insert (new AHNK ((str = "HNK"))).first;
//     AtomType::aHNL = *repository.insert (new AHNL ((str = "HNL"))).first;
//     AtomType::aHNM = *repository.insert (new AHNM ((str = "HNM"))).first;
//     AtomType::aHNM1 = *repository.insert (new AHNM1 ((str = "HNM1"))).first;
//     AtomType::aHNM2 = *repository.insert (new AHNM2 ((str = "HNM2"))).first;
//     AtomType::aHNM3 = *repository.insert (new AHNM3 ((str = "HNM3"))).first;
//     AtomType::aHNN = *repository.insert (new AHNN ((str = "HNN"))).first;
//     AtomType::aHNO = *repository.insert (new AHNO ((str = "HNO"))).first;
//     AtomType::aHNP = *repository.insert (new AHNP ((str = "HNP"))).first;
//     AtomType::aHNP1 = *repository.insert (new AHNP1 ((str = "HNP1"))).first;
//     AtomType::aHNP2 = *repository.insert (new AHNP2 ((str = "HNP2"))).first;
//     AtomType::aHNQ = *repository.insert (new AHNQ ((str = "HNQ"))).first;
//     AtomType::aHNR = *repository.insert (new AHNR ((str = "HNR"))).first;
//     AtomType::aHNS = *repository.insert (new AHNS ((str = "HNS"))).first;
//     AtomType::aHNT = *repository.insert (new AHNT ((str = "HNT"))).first;
//     AtomType::aHNV = *repository.insert (new AHNV ((str = "HNV"))).first;
//     AtomType::aHNW = *repository.insert (new AHNW ((str = "HNW"))).first;
//     AtomType::aHNX = *repository.insert (new AHNX ((str = "HNX"))).first;
//     AtomType::aHNY = *repository.insert (new AHNY ((str = "HNY"))).first;
//     AtomType::aHNZ = *repository.insert (new AHNZ ((str = "HNZ"))).first;
//     AtomType::aHO = *repository.insert (new AHO ((str = "HO"))).first;
//     AtomType::aHO" = *repository.insert (new AHO" ((str = "HO""))).first;
//     AtomType::aHO* = *repository.insert (new AHO* ((str = "HO*"))).first;
//     AtomType::aHO0 = *repository.insert (new AHO0 ((str = "HO0"))).first;
//     AtomType::aHO1 = *repository.insert (new AHO1 ((str = "HO1"))).first;
//     AtomType::aHO1* = *repository.insert (new AHO1* ((str = "HO1*"))).first;
//     AtomType::aHO10 = *repository.insert (new AHO10 ((str = "HO10"))).first;
//     AtomType::aHO11 = *repository.insert (new AHO11 ((str = "HO11"))).first;
//     AtomType::aHO12 = *repository.insert (new AHO12 ((str = "HO12"))).first;
//     AtomType::aHO13 = *repository.insert (new AHO13 ((str = "HO13"))).first;
//     AtomType::aHO14 = *repository.insert (new AHO14 ((str = "HO14"))).first;
//     AtomType::aHO15 = *repository.insert (new AHO15 ((str = "HO15"))).first;
//     AtomType::aHO16 = *repository.insert (new AHO16 ((str = "HO16"))).first;
//     AtomType::aHO17 = *repository.insert (new AHO17 ((str = "HO17"))).first;
//     AtomType::aHO18 = *repository.insert (new AHO18 ((str = "HO18"))).first;
//     AtomType::aHO19 = *repository.insert (new AHO19 ((str = "HO19"))).first;
//     AtomType::aHO1A = *repository.insert (new AHO1A ((str = "HO1A"))).first;
//     AtomType::aHO1B = *repository.insert (new AHO1B ((str = "HO1B"))).first;
//     AtomType::aHO1C = *repository.insert (new AHO1C ((str = "HO1C"))).first;
//     AtomType::aHO1G = *repository.insert (new AHO1G ((str = "HO1G"))).first;
//     AtomType::aHO1J = *repository.insert (new AHO1J ((str = "HO1J"))).first;
//     AtomType::aHO1L = *repository.insert (new AHO1L ((str = "HO1L"))).first;
//     AtomType::aHO1N = *repository.insert (new AHO1N ((str = "HO1N"))).first;
//     AtomType::aHO1O = *repository.insert (new AHO1O ((str = "HO1O"))).first;
//     AtomType::aHO1P = *repository.insert (new AHO1P ((str = "HO1P"))).first;
//     AtomType::aHO1X = *repository.insert (new AHO1X ((str = "HO1X"))).first;
//     AtomType::aHO2 = *repository.insert (new AHO2 ((str = "HO2"))).first;
//     AtomType::aHO20 = *repository.insert (new AHO20 ((str = "HO20"))).first;
//     AtomType::aHO21 = *repository.insert (new AHO21 ((str = "HO21"))).first;
//     AtomType::aHO22 = *repository.insert (new AHO22 ((str = "HO22"))).first;
//     AtomType::aHO23 = *repository.insert (new AHO23 ((str = "HO23"))).first;
//     AtomType::aHO24 = *repository.insert (new AHO24 ((str = "HO24"))).first;
//     AtomType::aHO25 = *repository.insert (new AHO25 ((str = "HO25"))).first;
//     AtomType::aHO26 = *repository.insert (new AHO26 ((str = "HO26"))).first;
//     AtomType::aHO27 = *repository.insert (new AHO27 ((str = "HO27"))).first;
//     AtomType::aHO28 = *repository.insert (new AHO28 ((str = "HO28"))).first;
//     AtomType::aHO29 = *repository.insert (new AHO29 ((str = "HO29"))).first;
//     AtomType::aHO2A = *repository.insert (new AHO2A ((str = "HO2A"))).first;
//     AtomType::aHO2B = *repository.insert (new AHO2B ((str = "HO2B"))).first;
//     AtomType::aHO2G = *repository.insert (new AHO2G ((str = "HO2G"))).first;
//     AtomType::aHO2H = *repository.insert (new AHO2H ((str = "HO2H"))).first;
//     AtomType::aHO2I = *repository.insert (new AHO2I ((str = "HO2I"))).first;
//     AtomType::aHO2J = *repository.insert (new AHO2J ((str = "HO2J"))).first;
//     AtomType::aHO2K = *repository.insert (new AHO2K ((str = "HO2K"))).first;
//     AtomType::aHO2L = *repository.insert (new AHO2L ((str = "HO2L"))).first;
//     AtomType::aHO2P = *repository.insert (new AHO2P ((str = "HO2P"))).first;
//     AtomType::aHO2Q = *repository.insert (new AHO2Q ((str = "HO2Q"))).first;
//     AtomType::aHO2R = *repository.insert (new AHO2R ((str = "HO2R"))).first;
//     AtomType::aHO2X = *repository.insert (new AHO2X ((str = "HO2X"))).first;
//     AtomType::aHO3 = *repository.insert (new AHO3 ((str = "HO3"))).first;
//     AtomType::aHO30 = *repository.insert (new AHO30 ((str = "HO30"))).first;
//     AtomType::aHO31 = *repository.insert (new AHO31 ((str = "HO31"))).first;
//     AtomType::aHO32 = *repository.insert (new AHO32 ((str = "HO32"))).first;
//     AtomType::aHO33 = *repository.insert (new AHO33 ((str = "HO33"))).first;
//     AtomType::aHO34 = *repository.insert (new AHO34 ((str = "HO34"))).first;
//     AtomType::aHO35 = *repository.insert (new AHO35 ((str = "HO35"))).first;
//     AtomType::aHO36 = *repository.insert (new AHO36 ((str = "HO36"))).first;
//     AtomType::aHO37 = *repository.insert (new AHO37 ((str = "HO37"))).first;
//     AtomType::aHO39 = *repository.insert (new AHO39 ((str = "HO39"))).first;
//     AtomType::aHO3A = *repository.insert (new AHO3A ((str = "HO3A"))).first;
//     AtomType::aHO3B = *repository.insert (new AHO3B ((str = "HO3B"))).first;
//     AtomType::aHO3C = *repository.insert (new AHO3C ((str = "HO3C"))).first;
//     AtomType::aHO3G = *repository.insert (new AHO3G ((str = "HO3G"))).first;
//     AtomType::aHO3H = *repository.insert (new AHO3H ((str = "HO3H"))).first;
//     AtomType::aHO3I = *repository.insert (new AHO3I ((str = "HO3I"))).first;
//     AtomType::aHO3J = *repository.insert (new AHO3J ((str = "HO3J"))).first;
//     AtomType::aHO3K = *repository.insert (new AHO3K ((str = "HO3K"))).first;
//     AtomType::aHO3L = *repository.insert (new AHO3L ((str = "HO3L"))).first;
//     AtomType::aHO3P = *repository.insert (new AHO3P ((str = "HO3P"))).first;
//     AtomType::aHO3Q = *repository.insert (new AHO3Q ((str = "HO3Q"))).first;
//     AtomType::aHO3R = *repository.insert (new AHO3R ((str = "HO3R"))).first;
//     AtomType::aHO3X = *repository.insert (new AHO3X ((str = "HO3X"))).first;
//     AtomType::aHO4 = *repository.insert (new AHO4 ((str = "HO4"))).first;
//     AtomType::aHO4* = *repository.insert (new AHO4* ((str = "HO4*"))).first;
//     AtomType::aHO40 = *repository.insert (new AHO40 ((str = "HO40"))).first;
//     AtomType::aHO41 = *repository.insert (new AHO41 ((str = "HO41"))).first;
//     AtomType::aHO42 = *repository.insert (new AHO42 ((str = "HO42"))).first;
//     AtomType::aHO43 = *repository.insert (new AHO43 ((str = "HO43"))).first;
//     AtomType::aHO44 = *repository.insert (new AHO44 ((str = "HO44"))).first;
//     AtomType::aHO45 = *repository.insert (new AHO45 ((str = "HO45"))).first;
//     AtomType::aHO46 = *repository.insert (new AHO46 ((str = "HO46"))).first;
//     AtomType::aHO47 = *repository.insert (new AHO47 ((str = "HO47"))).first;
//     AtomType::aHO48 = *repository.insert (new AHO48 ((str = "HO48"))).first;
//     AtomType::aHO49 = *repository.insert (new AHO49 ((str = "HO49"))).first;
//     AtomType::aHO4A = *repository.insert (new AHO4A ((str = "HO4A"))).first;
//     AtomType::aHO4B = *repository.insert (new AHO4B ((str = "HO4B"))).first;
//     AtomType::aHO4C = *repository.insert (new AHO4C ((str = "HO4C"))).first;
//     AtomType::aHO4P = *repository.insert (new AHO4P ((str = "HO4P"))).first;
//     AtomType::aHO4R = *repository.insert (new AHO4R ((str = "HO4R"))).first;
//     AtomType::aHO5 = *repository.insert (new AHO5 ((str = "HO5"))).first;
//     AtomType::aHO5* = *repository.insert (new AHO5* ((str = "HO5*"))).first;
//     AtomType::aHO52 = *repository.insert (new AHO52 ((str = "HO52"))).first;
//     AtomType::aHO57 = *repository.insert (new AHO57 ((str = "HO57"))).first;
//     AtomType::aHO58 = *repository.insert (new AHO58 ((str = "HO58"))).first;
//     AtomType::aHO59 = *repository.insert (new AHO59 ((str = "HO59"))).first;
//     AtomType::aHO5A = *repository.insert (new AHO5A ((str = "HO5A"))).first;
//     AtomType::aHO5B = *repository.insert (new AHO5B ((str = "HO5B"))).first;
//     AtomType::aHO5K = *repository.insert (new AHO5K ((str = "HO5K"))).first;
//     AtomType::aHO5P = *repository.insert (new AHO5P ((str = "HO5P"))).first;
//     AtomType::aHO6 = *repository.insert (new AHO6 ((str = "HO6"))).first;
//     AtomType::aHO6* = *repository.insert (new AHO6* ((str = "HO6*"))).first;
//     AtomType::aHO60 = *repository.insert (new AHO60 ((str = "HO60"))).first;
//     AtomType::aHO61 = *repository.insert (new AHO61 ((str = "HO61"))).first;
//     AtomType::aHO62 = *repository.insert (new AHO62 ((str = "HO62"))).first;
//     AtomType::aHO63 = *repository.insert (new AHO63 ((str = "HO63"))).first;
//     AtomType::aHO64 = *repository.insert (new AHO64 ((str = "HO64"))).first;
//     AtomType::aHO65 = *repository.insert (new AHO65 ((str = "HO65"))).first;
//     AtomType::aHO66 = *repository.insert (new AHO66 ((str = "HO66"))).first;
//     AtomType::aHO67 = *repository.insert (new AHO67 ((str = "HO67"))).first;
//     AtomType::aHO69 = *repository.insert (new AHO69 ((str = "HO69"))).first;
//     AtomType::aHO6A = *repository.insert (new AHO6A ((str = "HO6A"))).first;
//     AtomType::aHO6B = *repository.insert (new AHO6B ((str = "HO6B"))).first;
//     AtomType::aHO6G = *repository.insert (new AHO6G ((str = "HO6G"))).first;
//     AtomType::aHO6H = *repository.insert (new AHO6H ((str = "HO6H"))).first;
//     AtomType::aHO6I = *repository.insert (new AHO6I ((str = "HO6I"))).first;
//     AtomType::aHO6K = *repository.insert (new AHO6K ((str = "HO6K"))).first;
//     AtomType::aHO6L = *repository.insert (new AHO6L ((str = "HO6L"))).first;
//     AtomType::aHO6P = *repository.insert (new AHO6P ((str = "HO6P"))).first;
//     AtomType::aHO7 = *repository.insert (new AHO7 ((str = "HO7"))).first;
//     AtomType::aHO72 = *repository.insert (new AHO72 ((str = "HO72"))).first;
//     AtomType::aHO7P = *repository.insert (new AHO7P ((str = "HO7P"))).first;
//     AtomType::aHO7R = *repository.insert (new AHO7R ((str = "HO7R"))).first;
//     AtomType::aHO8 = *repository.insert (new AHO8 ((str = "HO8"))).first;
//     AtomType::aHO8R = *repository.insert (new AHO8R ((str = "HO8R"))).first;
//     AtomType::aHO9 = *repository.insert (new AHO9 ((str = "HO9"))).first;
//     AtomType::aHOA = *repository.insert (new AHOA ((str = "HOA"))).first;
//     AtomType::aHOA1 = *repository.insert (new AHOA1 ((str = "HOA1"))).first;
//     AtomType::aHOA2 = *repository.insert (new AHOA2 ((str = "HOA2"))).first;
//     AtomType::aHOAA = *repository.insert (new AHOAA ((str = "HOAA"))).first;
//     AtomType::aHOAC = *repository.insert (new AHOAC ((str = "HOAC"))).first;
//     AtomType::aHOAE = *repository.insert (new AHOAE ((str = "HOAE"))).first;
//     AtomType::aHOAF = *repository.insert (new AHOAF ((str = "HOAF"))).first;
//     AtomType::aHOAG = *repository.insert (new AHOAG ((str = "HOAG"))).first;
//     AtomType::aHOAH = *repository.insert (new AHOAH ((str = "HOAH"))).first;
//     AtomType::aHOAI = *repository.insert (new AHOAI ((str = "HOAI"))).first;
//     AtomType::aHOAK = *repository.insert (new AHOAK ((str = "HOAK"))).first;
//     AtomType::aHOAL = *repository.insert (new AHOAL ((str = "HOAL"))).first;
//     AtomType::aHOAS = *repository.insert (new AHOAS ((str = "HOAS"))).first;
//     AtomType::aHOB = *repository.insert (new AHOB ((str = "HOB"))).first;
//     AtomType::aHOBA = *repository.insert (new AHOBA ((str = "HOBA"))).first;
//     AtomType::aHOBN = *repository.insert (new AHOBN ((str = "HOBN"))).first;
//     AtomType::aHOBR = *repository.insert (new AHOBR ((str = "HOBR"))).first;
//     AtomType::aHOBT = *repository.insert (new AHOBT ((str = "HOBT"))).first;
//     AtomType::aHOBU = *repository.insert (new AHOBU ((str = "HOBU"))).first;
//     AtomType::aHOC = *repository.insert (new AHOC ((str = "HOC"))).first;
//     AtomType::aHOC1 = *repository.insert (new AHOC1 ((str = "HOC1"))).first;
//     AtomType::aHOC2 = *repository.insert (new AHOC2 ((str = "HOC2"))).first;
//     AtomType::aHOC3 = *repository.insert (new AHOC3 ((str = "HOC3"))).first;
//     AtomType::aHOC5 = *repository.insert (new AHOC5 ((str = "HOC5"))).first;
//     AtomType::aHOC9 = *repository.insert (new AHOC9 ((str = "HOC9"))).first;
//     AtomType::aHOCY = *repository.insert (new AHOCY ((str = "HOCY"))).first;
//     AtomType::aHOD = *repository.insert (new AHOD ((str = "HOD"))).first;
//     AtomType::aHOD2 = *repository.insert (new AHOD2 ((str = "HOD2"))).first;
//     AtomType::aHOE = *repository.insert (new AHOE ((str = "HOE"))).first;
//     AtomType::aHOE1 = *repository.insert (new AHOE1 ((str = "HOE1"))).first;
//     AtomType::aHOE2 = *repository.insert (new AHOE2 ((str = "HOE2"))).first;
//     AtomType::aHOF = *repository.insert (new AHOF ((str = "HOF"))).first;
//     AtomType::aHOF1 = *repository.insert (new AHOF1 ((str = "HOF1"))).first;
//     AtomType::aHOF2 = *repository.insert (new AHOF2 ((str = "HOF2"))).first;
//     AtomType::aHOF3 = *repository.insert (new AHOF3 ((str = "HOF3"))).first;
//     AtomType::aHOG = *repository.insert (new AHOG ((str = "HOG"))).first;
//     AtomType::aHOG1 = *repository.insert (new AHOG1 ((str = "HOG1"))).first;
//     AtomType::aHOH = *repository.insert (new AHOH ((str = "HOH"))).first;
//     AtomType::aHOH1 = *repository.insert (new AHOH1 ((str = "HOH1"))).first;
//     AtomType::aHOI2 = *repository.insert (new AHOI2 ((str = "HOI2"))).first;
//     AtomType::aHOJ = *repository.insert (new AHOJ ((str = "HOJ"))).first;
//     AtomType::aHOK2 = *repository.insert (new AHOK2 ((str = "HOK2"))).first;
//     AtomType::aHOL = *repository.insert (new AHOL ((str = "HOL"))).first;
//     AtomType::aHOM = *repository.insert (new AHOM ((str = "HOM"))).first;
//     AtomType::aHOM1 = *repository.insert (new AHOM1 ((str = "HOM1"))).first;
//     AtomType::aHOM2 = *repository.insert (new AHOM2 ((str = "HOM2"))).first;
//     AtomType::aHOM3 = *repository.insert (new AHOM3 ((str = "HOM3"))).first;
//     AtomType::aHOM7 = *repository.insert (new AHOM7 ((str = "HOM7"))).first;
//     AtomType::aHON = *repository.insert (new AHON ((str = "HON"))).first;
//     AtomType::aHOO = *repository.insert (new AHOO ((str = "HOO"))).first;
//     AtomType::aHOP = *repository.insert (new AHOP ((str = "HOP"))).first;
//     AtomType::aHOP1 = *repository.insert (new AHOP1 ((str = "HOP1"))).first;
//     AtomType::aHOP2 = *repository.insert (new AHOP2 ((str = "HOP2"))).first;
//     AtomType::aHOP3 = *repository.insert (new AHOP3 ((str = "HOP3"))).first;
//     AtomType::aHOQ = *repository.insert (new AHOQ ((str = "HOQ"))).first;
//     AtomType::aHOR = *repository.insert (new AHOR ((str = "HOR"))).first;
//     AtomType::aHOS = *repository.insert (new AHOS ((str = "HOS"))).first;
//     AtomType::aHOT = *repository.insert (new AHOT ((str = "HOT"))).first;
//     AtomType::aHOT1 = *repository.insert (new AHOT1 ((str = "HOT1"))).first;
//     AtomType::aHOU = *repository.insert (new AHOU ((str = "HOU"))).first;
//     AtomType::aHOV = *repository.insert (new AHOV ((str = "HOV"))).first;
//     AtomType::aHOW = *repository.insert (new AHOW ((str = "HOW"))).first;
//     AtomType::aHOX = *repository.insert (new AHOX ((str = "HOX"))).first;
//     AtomType::aHOX2 = *repository.insert (new AHOX2 ((str = "HOX2"))).first;
//     AtomType::aHOX3 = *repository.insert (new AHOX3 ((str = "HOX3"))).first;
//     AtomType::aHOX4 = *repository.insert (new AHOX4 ((str = "HOX4"))).first;
//     AtomType::aHOX6 = *repository.insert (new AHOX6 ((str = "HOX6"))).first;
//     AtomType::aHOXT = *repository.insert (new AHOXT ((str = "HOXT"))).first;
//     AtomType::aHOY = *repository.insert (new AHOY ((str = "HOY"))).first;
//     AtomType::aHOZ = *repository.insert (new AHOZ ((str = "HOZ"))).first;
//     AtomType::aHOZ1 = *repository.insert (new AHOZ1 ((str = "HOZ1"))).first;
//     AtomType::aHP = *repository.insert (new AHP ((str = "HP"))).first;
//     AtomType::aHP* = *repository.insert (new AHP* ((str = "HP*"))).first;
//     AtomType::aHP1 = *repository.insert (new AHP1 ((str = "HP1"))).first;
//     AtomType::aHP2 = *repository.insert (new AHP2 ((str = "HP2"))).first;
//     AtomType::aHP3 = *repository.insert (new AHP3 ((str = "HP3"))).first;
//     AtomType::aHP4 = *repository.insert (new AHP4 ((str = "HP4"))).first;
//     AtomType::aHP5 = *repository.insert (new AHP5 ((str = "HP5"))).first;
//     AtomType::aHP6 = *repository.insert (new AHP6 ((str = "HP6"))).first;
//     AtomType::aHP61 = *repository.insert (new AHP61 ((str = "HP61"))).first;
//     AtomType::aHP62 = *repository.insert (new AHP62 ((str = "HP62"))).first;
//     AtomType::aHP63 = *repository.insert (new AHP63 ((str = "HP63"))).first;
//     AtomType::aHP64 = *repository.insert (new AHP64 ((str = "HP64"))).first;
//     AtomType::aHP7 = *repository.insert (new AHP7 ((str = "HP7"))).first;
//     AtomType::aHP71 = *repository.insert (new AHP71 ((str = "HP71"))).first;
//     AtomType::aHP72 = *repository.insert (new AHP72 ((str = "HP72"))).first;
//     AtomType::aHP73 = *repository.insert (new AHP73 ((str = "HP73"))).first;
//     AtomType::aHP74 = *repository.insert (new AHP74 ((str = "HP74"))).first;
//     AtomType::aHP8 = *repository.insert (new AHP8 ((str = "HP8"))).first;
//     AtomType::aHPA = *repository.insert (new AHPA ((str = "HPA"))).first;
//     AtomType::aHPF = *repository.insert (new AHPF ((str = "HPF"))).first;
//     AtomType::aHPG = *repository.insert (new AHPG ((str = "HPG"))).first;
//     AtomType::aHPI = *repository.insert (new AHPI ((str = "HPI"))).first;
//     AtomType::aHPN = *repository.insert (new AHPN ((str = "HPN"))).first;
//     AtomType::aHPO = *repository.insert (new AHPO ((str = "HPO"))).first;
//     AtomType::aHPQ = *repository.insert (new AHPQ ((str = "HPQ"))).first;
//     AtomType::aHPR = *repository.insert (new AHPR ((str = "HPR"))).first;
//     AtomType::aHPT = *repository.insert (new AHPT ((str = "HPT"))).first;
//     AtomType::aHPX = *repository.insert (new AHPX ((str = "HPX"))).first;
//     AtomType::aHQ = *repository.insert (new AHQ ((str = "HQ"))).first;
//     AtomType::aHQ1 = *repository.insert (new AHQ1 ((str = "HQ1"))).first;
//     AtomType::aHQ2 = *repository.insert (new AHQ2 ((str = "HQ2"))).first;
//     AtomType::aHQ3 = *repository.insert (new AHQ3 ((str = "HQ3"))).first;
//     AtomType::aHQ4 = *repository.insert (new AHQ4 ((str = "HQ4"))).first;
//     AtomType::aHQ5 = *repository.insert (new AHQ5 ((str = "HQ5"))).first;
//     AtomType::aHQ6 = *repository.insert (new AHQ6 ((str = "HQ6"))).first;
//     AtomType::aHQ7 = *repository.insert (new AHQ7 ((str = "HQ7"))).first;
//     AtomType::aHQA = *repository.insert (new AHQA ((str = "HQA"))).first;
//     AtomType::aHR = *repository.insert (new AHR ((str = "HR"))).first;
//     AtomType::aHR1 = *repository.insert (new AHR1 ((str = "HR1"))).first;
//     AtomType::aHR2 = *repository.insert (new AHR2 ((str = "HR2"))).first;
//     AtomType::aHR3 = *repository.insert (new AHR3 ((str = "HR3"))).first;
//     AtomType::aHR4 = *repository.insert (new AHR4 ((str = "HR4"))).first;
//     AtomType::aHR5 = *repository.insert (new AHR5 ((str = "HR5"))).first;
//     AtomType::aHR6 = *repository.insert (new AHR6 ((str = "HR6"))).first;
//     AtomType::aHS = *repository.insert (new AHS ((str = "HS"))).first;
//     AtomType::aHS* = *repository.insert (new AHS* ((str = "HS*"))).first;
//     AtomType::aHS1 = *repository.insert (new AHS1 ((str = "HS1"))).first;
//     AtomType::aHS11 = *repository.insert (new AHS11 ((str = "HS11"))).first;
//     AtomType::aHS2 = *repository.insert (new AHS2 ((str = "HS2"))).first;
//     AtomType::aHS25 = *repository.insert (new AHS25 ((str = "HS25"))).first;
//     AtomType::aHS3 = *repository.insert (new AHS3 ((str = "HS3"))).first;
//     AtomType::aHS4 = *repository.insert (new AHS4 ((str = "HS4"))).first;
//     AtomType::aHS44 = *repository.insert (new AHS44 ((str = "HS44"))).first;
//     AtomType::aHS5 = *repository.insert (new AHS5 ((str = "HS5"))).first;
//     AtomType::aHS6 = *repository.insert (new AHS6 ((str = "HS6"))).first;
//     AtomType::aHS7 = *repository.insert (new AHS7 ((str = "HS7"))).first;
//     AtomType::aHS8 = *repository.insert (new AHS8 ((str = "HS8"))).first;
//     AtomType::aHSA1 = *repository.insert (new AHSA1 ((str = "HSA1"))).first;
//     AtomType::aHSA2 = *repository.insert (new AHSA2 ((str = "HSA2"))).first;
//     AtomType::aHSA3 = *repository.insert (new AHSA3 ((str = "HSA3"))).first;
//     AtomType::aHSAF = *repository.insert (new AHSAF ((str = "HSAF"))).first;
//     AtomType::aHSD = *repository.insert (new AHSD ((str = "HSD"))).first;
//     AtomType::aHSD1 = *repository.insert (new AHSD1 ((str = "HSD1"))).first;
//     AtomType::aHSD2 = *repository.insert (new AHSD2 ((str = "HSD2"))).first;
//     AtomType::aHSD3 = *repository.insert (new AHSD3 ((str = "HSD3"))).first;
//     AtomType::aHSE = *repository.insert (new AHSE ((str = "HSE"))).first;
//     AtomType::aHSG = *repository.insert (new AHSG ((str = "HSG"))).first;
//     AtomType::aHSM1 = *repository.insert (new AHSM1 ((str = "HSM1"))).first;
//     AtomType::aHSZ2 = *repository.insert (new AHSZ2 ((str = "HSZ2"))).first;
//     AtomType::aHT = *repository.insert (new AHT ((str = "HT"))).first;
//     AtomType::aHT1 = *repository.insert (new AHT1 ((str = "HT1"))).first;
//     AtomType::aHT11 = *repository.insert (new AHT11 ((str = "HT11"))).first;
//     AtomType::aHT12 = *repository.insert (new AHT12 ((str = "HT12"))).first;
//     AtomType::aHT13 = *repository.insert (new AHT13 ((str = "HT13"))).first;
//     AtomType::aHT2 = *repository.insert (new AHT2 ((str = "HT2"))).first;
//     AtomType::aHT21 = *repository.insert (new AHT21 ((str = "HT21"))).first;
//     AtomType::aHT22 = *repository.insert (new AHT22 ((str = "HT22"))).first;
//     AtomType::aHT23 = *repository.insert (new AHT23 ((str = "HT23"))).first;
//     AtomType::aHT3 = *repository.insert (new AHT3 ((str = "HT3"))).first;
//     AtomType::aHT31 = *repository.insert (new AHT31 ((str = "HT31"))).first;
//     AtomType::aHT32 = *repository.insert (new AHT32 ((str = "HT32"))).first;
//     AtomType::aHT33 = *repository.insert (new AHT33 ((str = "HT33"))).first;
//     AtomType::aHT4 = *repository.insert (new AHT4 ((str = "HT4"))).first;
//     AtomType::aHT5 = *repository.insert (new AHT5 ((str = "HT5"))).first;
//     AtomType::aHT6 = *repository.insert (new AHT6 ((str = "HT6"))).first;
//     AtomType::aHT7 = *repository.insert (new AHT7 ((str = "HT7"))).first;
//     AtomType::aHT8 = *repository.insert (new AHT8 ((str = "HT8"))).first;
//     AtomType::aHT9 = *repository.insert (new AHT9 ((str = "HT9"))).first;
//     AtomType::aHTA = *repository.insert (new AHTA ((str = "HTA"))).first;
//     AtomType::aHTP = *repository.insert (new AHTP ((str = "HTP"))).first;
//     AtomType::aHTT = *repository.insert (new AHTT ((str = "HTT"))).first;
//     AtomType::aHTV = *repository.insert (new AHTV ((str = "HTV"))).first;
//     AtomType::aHU = *repository.insert (new AHU ((str = "HU"))).first;
//     AtomType::aHU2 = *repository.insert (new AHU2 ((str = "HU2"))).first;
//     AtomType::aHV = *repository.insert (new AHV ((str = "HV"))).first;
//     AtomType::aHV1 = *repository.insert (new AHV1 ((str = "HV1"))).first;
//     AtomType::aHV2 = *repository.insert (new AHV2 ((str = "HV2"))).first;
//     AtomType::aHV2A = *repository.insert (new AHV2A ((str = "HV2A"))).first;
//     AtomType::aHV2C = *repository.insert (new AHV2C ((str = "HV2C"))).first;
//     AtomType::aHV2T = *repository.insert (new AHV2T ((str = "HV2T"))).first;
//     AtomType::aHV3 = *repository.insert (new AHV3 ((str = "HV3"))).first;
//     AtomType::aHV4 = *repository.insert (new AHV4 ((str = "HV4"))).first;
//     AtomType::aHV4A = *repository.insert (new AHV4A ((str = "HV4A"))).first;
//     AtomType::aHV4C = *repository.insert (new AHV4C ((str = "HV4C"))).first;
//     AtomType::aHV4T = *repository.insert (new AHV4T ((str = "HV4T"))).first;
//     AtomType::aHV5 = *repository.insert (new AHV5 ((str = "HV5"))).first;
//     AtomType::aHV6 = *repository.insert (new AHV6 ((str = "HV6"))).first;
//     AtomType::aHV7 = *repository.insert (new AHV7 ((str = "HV7"))).first;
//     AtomType::aHW = *repository.insert (new AHW ((str = "HW"))).first;
//     AtomType::aHW1 = *repository.insert (new AHW1 ((str = "HW1"))).first;
//     AtomType::aHW2 = *repository.insert (new AHW2 ((str = "HW2"))).first;
//     AtomType::aHW3 = *repository.insert (new AHW3 ((str = "HW3"))).first;
//     AtomType::aHW4 = *repository.insert (new AHW4 ((str = "HW4"))).first;
//     AtomType::aHW5 = *repository.insert (new AHW5 ((str = "HW5"))).first;
//     AtomType::aHW6 = *repository.insert (new AHW6 ((str = "HW6"))).first;
//     AtomType::aHX = *repository.insert (new AHX ((str = "HX"))).first;
//     AtomType::aHX1 = *repository.insert (new AHX1 ((str = "HX1"))).first;
//     AtomType::aHX10 = *repository.insert (new AHX10 ((str = "HX10"))).first;
//     AtomType::aHX11 = *repository.insert (new AHX11 ((str = "HX11"))).first;
//     AtomType::aHX12 = *repository.insert (new AHX12 ((str = "HX12"))).first;
//     AtomType::aHX2 = *repository.insert (new AHX2 ((str = "HX2"))).first;
//     AtomType::aHX3 = *repository.insert (new AHX3 ((str = "HX3"))).first;
//     AtomType::aHX4 = *repository.insert (new AHX4 ((str = "HX4"))).first;
//     AtomType::aHX5 = *repository.insert (new AHX5 ((str = "HX5"))).first;
//     AtomType::aHX6 = *repository.insert (new AHX6 ((str = "HX6"))).first;
//     AtomType::aHX7 = *repository.insert (new AHX7 ((str = "HX7"))).first;
//     AtomType::aHX8 = *repository.insert (new AHX8 ((str = "HX8"))).first;
//     AtomType::aHX9 = *repository.insert (new AHX9 ((str = "HX9"))).first;
//     AtomType::aHXB = *repository.insert (new AHXB ((str = "HXB"))).first;
//     AtomType::aHXC = *repository.insert (new AHXC ((str = "HXC"))).first;
//     AtomType::aHXD = *repository.insert (new AHXD ((str = "HXD"))).first;
//     AtomType::aHXE = *repository.insert (new AHXE ((str = "HXE"))).first;
//     AtomType::aHXF = *repository.insert (new AHXF ((str = "HXF"))).first;
//     AtomType::aHXT = *repository.insert (new AHXT ((str = "HXT"))).first;
//     AtomType::aHXU = *repository.insert (new AHXU ((str = "HXU"))).first;
//     AtomType::aHXV = *repository.insert (new AHXV ((str = "HXV"))).first;
//     AtomType::aHY = *repository.insert (new AHY ((str = "HY"))).first;
//     AtomType::aHY1 = *repository.insert (new AHY1 ((str = "HY1"))).first;
//     AtomType::aHY2 = *repository.insert (new AHY2 ((str = "HY2"))).first;
//     AtomType::aHY3 = *repository.insert (new AHY3 ((str = "HY3"))).first;
//     AtomType::aHY4 = *repository.insert (new AHY4 ((str = "HY4"))).first;
//     AtomType::aHY5 = *repository.insert (new AHY5 ((str = "HY5"))).first;
//     AtomType::aHY6 = *repository.insert (new AHY6 ((str = "HY6"))).first;
//     AtomType::aHY7 = *repository.insert (new AHY7 ((str = "HY7"))).first;
//     AtomType::aHZ = *repository.insert (new AHZ ((str = "HZ"))).first;
//     AtomType::aHZ* = *repository.insert (new AHZ* ((str = "HZ*"))).first;
//     AtomType::aHZ1 = *repository.insert (new AHZ1 ((str = "HZ1"))).first;
//     AtomType::aHZ2 = *repository.insert (new AHZ2 ((str = "HZ2"))).first;
//     AtomType::aHZ3 = *repository.insert (new AHZ3 ((str = "HZ3"))).first;
//     AtomType::aHZ4 = *repository.insert (new AHZ4 ((str = "HZ4"))).first;
//     AtomType::aHZ5 = *repository.insert (new AHZ5 ((str = "HZ5"))).first;
//     AtomType::aHZ6 = *repository.insert (new AHZ6 ((str = "HZ6"))).first;
//     AtomType::aHZ7 = *repository.insert (new AHZ7 ((str = "HZ7"))).first;
//     AtomType::aHZH1 = *repository.insert (new AHZH1 ((str = "HZH1"))).first;
//     AtomType::aHZH2 = *repository.insert (new AHZH2 ((str = "HZH2"))).first;
//     AtomType::aH_1 = *repository.insert (new AH_1 ((str = "H_1"))).first;
//     AtomType::aH_2 = *repository.insert (new AH_2 ((str = "H_2"))).first;
//     AtomType::aH_3 = *repository.insert (new AH_3 ((str = "H_3"))).first;
//     AtomType::aH_4 = *repository.insert (new AH_4 ((str = "H_4"))).first;
//     AtomType::aH_5 = *repository.insert (new AH_5 ((str = "H_5"))).first;
//     AtomType::aH_7 = *repository.insert (new AH_7 ((str = "H_7"))).first;
//     AtomType::aH_8 = *repository.insert (new AH_8 ((str = "H_8"))).first;
//     AtomType::aI = *repository.insert (new AI ((str = "I"))).first;
//     AtomType::aI1 = *repository.insert (new AI1 ((str = "I1"))).first;
//     AtomType::aI12 = *repository.insert (new AI12 ((str = "I12"))).first;
//     AtomType::aI13 = *repository.insert (new AI13 ((str = "I13"))).first;
//     AtomType::aI14 = *repository.insert (new AI14 ((str = "I14"))).first;
//     AtomType::aI19 = *repository.insert (new AI19 ((str = "I19"))).first;
//     AtomType::aI2 = *repository.insert (new AI2 ((str = "I2"))).first;
//     AtomType::aI2S = *repository.insert (new AI2S ((str = "I2S"))).first;
//     AtomType::aI3 = *repository.insert (new AI3 ((str = "I3"))).first;
//     AtomType::aI3* = *repository.insert (new AI3* ((str = "I3*"))).first;
//     AtomType::aI4 = *repository.insert (new AI4 ((str = "I4"))).first;
//     AtomType::aI4* = *repository.insert (new AI4* ((str = "I4*"))).first;
//     AtomType::aI5 = *repository.insert (new AI5 ((str = "I5"))).first;
//     AtomType::aI5* = *repository.insert (new AI5* ((str = "I5*"))).first;
//     AtomType::aI54 = *repository.insert (new AI54 ((str = "I54"))).first;
//     AtomType::aI6 = *repository.insert (new AI6 ((str = "I6"))).first;
//     AtomType::aI7 = *repository.insert (new AI7 ((str = "I7"))).first;
//     AtomType::aI8A = *repository.insert (new AI8A ((str = "I8A"))).first;
//     AtomType::aI9 = *repository.insert (new AI9 ((str = "I9"))).first;
//     AtomType::aIAE = *repository.insert (new AIAE ((str = "IAE"))).first;
//     AtomType::aIAS = *repository.insert (new AIAS ((str = "IAS"))).first;
//     AtomType::aIBI = *repository.insert (new AIBI ((str = "IBI"))).first;
//     AtomType::aIC1 = *repository.insert (new AIC1 ((str = "IC1"))).first;
//     AtomType::aIC2 = *repository.insert (new AIC2 ((str = "IC2"))).first;
//     AtomType::aIC3 = *repository.insert (new AIC3 ((str = "IC3"))).first;
//     AtomType::aIE = *repository.insert (new AIE ((str = "IE"))).first;
//     AtomType::aIF1 = *repository.insert (new AIF1 ((str = "IF1"))).first;
//     AtomType::aIF2 = *repository.insert (new AIF2 ((str = "IF2"))).first;
//     AtomType::aIF3 = *repository.insert (new AIF3 ((str = "IF3"))).first;
//     AtomType::aIHO1 = *repository.insert (new AIHO1 ((str = "IHO1"))).first;
//     AtomType::aIHO2 = *repository.insert (new AIHO2 ((str = "IHO2"))).first;
//     AtomType::aIHO3 = *repository.insert (new AIHO3 ((str = "IHO3"))).first;
//     AtomType::aIHO5 = *repository.insert (new AIHO5 ((str = "IHO5"))).first;
//     AtomType::aIHO6 = *repository.insert (new AIHO6 ((str = "IHO6"))).first;
//     AtomType::aIN1 = *repository.insert (new AIN1 ((str = "IN1"))).first;
//     AtomType::aIO1 = *repository.insert (new AIO1 ((str = "IO1"))).first;
//     AtomType::aIO2 = *repository.insert (new AIO2 ((str = "IO2"))).first;
//     AtomType::aIR = *repository.insert (new AIR ((str = "IR"))).first;
//     AtomType::aJHO2 = *repository.insert (new AJHO2 ((str = "JHO2"))).first;
//     AtomType::aJHO3 = *repository.insert (new AJHO3 ((str = "JHO3"))).first;
//     AtomType::aK = *repository.insert (new AK ((str = "K"))).first;
//     AtomType::aKHC1 = *repository.insert (new AKHC1 ((str = "KHC1"))).first;
//     AtomType::aKHC2 = *repository.insert (new AKHC2 ((str = "KHC2"))).first;
//     AtomType::aKHO2 = *repository.insert (new AKHO2 ((str = "KHO2"))).first;
//     AtomType::aKHO3 = *repository.insert (new AKHO3 ((str = "KHO3"))).first;
//     AtomType::aKHO6 = *repository.insert (new AKHO6 ((str = "KHO6"))).first;
//     AtomType::aLHO1 = *repository.insert (new ALHO1 ((str = "LHO1"))).first;
//     AtomType::aLHO2 = *repository.insert (new ALHO2 ((str = "LHO2"))).first;
//     AtomType::aLHO3 = *repository.insert (new ALHO3 ((str = "LHO3"))).first;
//     AtomType::aMG = *repository.insert (new AMG ((str = "MG"))).first;
//     AtomType::aMG1 = *repository.insert (new AMG1 ((str = "MG1"))).first;
//     AtomType::aMN = *repository.insert (new AMN ((str = "MN"))).first;
//     AtomType::aMN1 = *repository.insert (new AMN1 ((str = "MN1"))).first;
//     AtomType::aMN2 = *repository.insert (new AMN2 ((str = "MN2"))).first;
//     AtomType::aMN3 = *repository.insert (new AMN3 ((str = "MN3"))).first;
//     AtomType::aMN4 = *repository.insert (new AMN4 ((str = "MN4"))).first;
//     AtomType::aMO = *repository.insert (new AMO ((str = "MO"))).first;
//     AtomType::aMO1 = *repository.insert (new AMO1 ((str = "MO1"))).first;
//     AtomType::aMO2 = *repository.insert (new AMO2 ((str = "MO2"))).first;
//     AtomType::aMO3 = *repository.insert (new AMO3 ((str = "MO3"))).first;
//     AtomType::aMO4 = *repository.insert (new AMO4 ((str = "MO4"))).first;
//     AtomType::aMO5 = *repository.insert (new AMO5 ((str = "MO5"))).first;
//     AtomType::aMO6 = *repository.insert (new AMO6 ((str = "MO6"))).first;
//     AtomType::aMO7 = *repository.insert (new AMO7 ((str = "MO7"))).first;
//     AtomType::aMOM1 = *repository.insert (new AMOM1 ((str = "MOM1"))).first;
//     AtomType::aN = *repository.insert (new AN ((str = "N"))).first;
//     AtomType::aN" = *repository.insert (new AN" ((str = "N""))).first;
//     AtomType::aN* = *repository.insert (new AN* ((str = "N*"))).first;
//     AtomType::aN*0 = *repository.insert (new AN*0 ((str = "N*0"))).first;
//     AtomType::aN*1 = *repository.insert (new AN*1 ((str = "N*1"))).first;
//     AtomType::aN0 = *repository.insert (new AN0 ((str = "N0"))).first;
//     AtomType::aN0* = *repository.insert (new AN0* ((str = "N0*"))).first;
//     AtomType::aN01 = *repository.insert (new AN01 ((str = "N01"))).first;
//     AtomType::aN02 = *repository.insert (new AN02 ((str = "N02"))).first;
//     AtomType::aN03 = *repository.insert (new AN03 ((str = "N03"))).first;
//     AtomType::aN04 = *repository.insert (new AN04 ((str = "N04"))).first;
//     AtomType::aN05 = *repository.insert (new AN05 ((str = "N05"))).first;
//     AtomType::aN06 = *repository.insert (new AN06 ((str = "N06"))).first;
//     AtomType::aN07 = *repository.insert (new AN07 ((str = "N07"))).first;
//     AtomType::aN08 = *repository.insert (new AN08 ((str = "N08"))).first;
//     AtomType::aN09 = *repository.insert (new AN09 ((str = "N09"))).first;
//     AtomType::aN1 = *repository.insert (new AN1 ((str = "N1"))).first;
//     AtomType::aN1" = *repository.insert (new AN1" ((str = "N1""))).first;
//     AtomType::aN1* = *repository.insert (new AN1* ((str = "N1*"))).first;
//     AtomType::aN10 = *repository.insert (new AN10 ((str = "N10"))).first;
//     AtomType::aN10* = *repository.insert (new AN10* ((str = "N10*"))).first;
//     AtomType::aN108 = *repository.insert (new AN108 ((str = "N108"))).first;
//     AtomType::aN10A = *repository.insert (new AN10A ((str = "N10A"))).first;
//     AtomType::aN10S = *repository.insert (new AN10S ((str = "N10S"))).first;
//     AtomType::aN11 = *repository.insert (new AN11 ((str = "N11"))).first;
//     AtomType::aN12 = *repository.insert (new AN12 ((str = "N12"))).first;
//     AtomType::aN13 = *repository.insert (new AN13 ((str = "N13"))).first;
//     AtomType::aN14 = *repository.insert (new AN14 ((str = "N14"))).first;
//     AtomType::aN15 = *repository.insert (new AN15 ((str = "N15"))).first;
//     AtomType::aN16 = *repository.insert (new AN16 ((str = "N16"))).first;
//     AtomType::aN17 = *repository.insert (new AN17 ((str = "N17"))).first;
//     AtomType::aN18 = *repository.insert (new AN18 ((str = "N18"))).first;
//     AtomType::aN19 = *repository.insert (new AN19 ((str = "N19"))).first;
//     AtomType::aN1A = *repository.insert (new AN1A ((str = "N1A"))).first;
//     AtomType::aN1B = *repository.insert (new AN1B ((str = "N1B"))).first;
//     AtomType::aN1C = *repository.insert (new AN1C ((str = "N1C"))).first;
//     AtomType::aN1D = *repository.insert (new AN1D ((str = "N1D"))).first;
//     AtomType::aN1E = *repository.insert (new AN1E ((str = "N1E"))).first;
//     AtomType::aN1F = *repository.insert (new AN1F ((str = "N1F"))).first;
//     AtomType::aN1G = *repository.insert (new AN1G ((str = "N1G"))).first;
//     AtomType::aN1H = *repository.insert (new AN1H ((str = "N1H"))).first;
//     AtomType::aN1I = *repository.insert (new AN1I ((str = "N1I"))).first;
//     AtomType::aN1J = *repository.insert (new AN1J ((str = "N1J"))).first;
//     AtomType::aN1M = *repository.insert (new AN1M ((str = "N1M"))).first;
//     AtomType::aN1N = *repository.insert (new AN1N ((str = "N1N"))).first;
//     AtomType::aN1P = *repository.insert (new AN1P ((str = "N1P"))).first;
//     AtomType::aN1R = *repository.insert (new AN1R ((str = "N1R"))).first;
//     AtomType::aN1S = *repository.insert (new AN1S ((str = "N1S"))).first;
//     AtomType::aN1T = *repository.insert (new AN1T ((str = "N1T"))).first;
//     AtomType::aN1U = *repository.insert (new AN1U ((str = "N1U"))).first;
//     AtomType::aN1X = *repository.insert (new AN1X ((str = "N1X"))).first;
//     AtomType::aN2 = *repository.insert (new AN2 ((str = "N2"))).first;
//     AtomType::aN2* = *repository.insert (new AN2* ((str = "N2*"))).first;
//     AtomType::aN2** = *repository.insert (new AN2** ((str = "N2**"))).first;
//     AtomType::aN20 = *repository.insert (new AN20 ((str = "N20"))).first;
//     AtomType::aN21 = *repository.insert (new AN21 ((str = "N21"))).first;
//     AtomType::aN21* = *repository.insert (new AN21* ((str = "N21*"))).first;
//     AtomType::aN22 = *repository.insert (new AN22 ((str = "N22"))).first;
//     AtomType::aN23 = *repository.insert (new AN23 ((str = "N23"))).first;
//     AtomType::aN24 = *repository.insert (new AN24 ((str = "N24"))).first;
//     AtomType::aN25 = *repository.insert (new AN25 ((str = "N25"))).first;
//     AtomType::aN26 = *repository.insert (new AN26 ((str = "N26"))).first;
//     AtomType::aN27 = *repository.insert (new AN27 ((str = "N27"))).first;
//     AtomType::aN28 = *repository.insert (new AN28 ((str = "N28"))).first;
//     AtomType::aN29 = *repository.insert (new AN29 ((str = "N29"))).first;
//     AtomType::aN2A = *repository.insert (new AN2A ((str = "N2A"))).first;
//     AtomType::aN2B = *repository.insert (new AN2B ((str = "N2B"))).first;
//     AtomType::aN2C = *repository.insert (new AN2C ((str = "N2C"))).first;
//     AtomType::aN2D = *repository.insert (new AN2D ((str = "N2D"))).first;
//     AtomType::aN2F = *repository.insert (new AN2F ((str = "N2F"))).first;
//     AtomType::aN2G = *repository.insert (new AN2G ((str = "N2G"))).first;
//     AtomType::aN2H = *repository.insert (new AN2H ((str = "N2H"))).first;
//     AtomType::aN2I = *repository.insert (new AN2I ((str = "N2I"))).first;
//     AtomType::aN2T = *repository.insert (new AN2T ((str = "N2T"))).first;
//     AtomType::aN2X = *repository.insert (new AN2X ((str = "N2X"))).first;
//     AtomType::aN3 = *repository.insert (new AN3 ((str = "N3"))).first;
//     AtomType::aN3" = *repository.insert (new AN3" ((str = "N3""))).first;
//     AtomType::aN3* = *repository.insert (new AN3* ((str = "N3*"))).first;
//     AtomType::aN30 = *repository.insert (new AN30 ((str = "N30"))).first;
//     AtomType::aN31 = *repository.insert (new AN31 ((str = "N31"))).first;
//     AtomType::aN32 = *repository.insert (new AN32 ((str = "N32"))).first;
//     AtomType::aN33 = *repository.insert (new AN33 ((str = "N33"))).first;
//     AtomType::aN33* = *repository.insert (new AN33* ((str = "N33*"))).first;
//     AtomType::aN34 = *repository.insert (new AN34 ((str = "N34"))).first;
//     AtomType::aN35 = *repository.insert (new AN35 ((str = "N35"))).first;
//     AtomType::aN36 = *repository.insert (new AN36 ((str = "N36"))).first;
//     AtomType::aN37 = *repository.insert (new AN37 ((str = "N37"))).first;
//     AtomType::aN38 = *repository.insert (new AN38 ((str = "N38"))).first;
//     AtomType::aN39 = *repository.insert (new AN39 ((str = "N39"))).first;
//     AtomType::aN3A = *repository.insert (new AN3A ((str = "N3A"))).first;
//     AtomType::aN3B = *repository.insert (new AN3B ((str = "N3B"))).first;
//     AtomType::aN3C = *repository.insert (new AN3C ((str = "N3C"))).first;
//     AtomType::aN3F = *repository.insert (new AN3F ((str = "N3F"))).first;
//     AtomType::aN3G = *repository.insert (new AN3G ((str = "N3G"))).first;
//     AtomType::aN3H = *repository.insert (new AN3H ((str = "N3H"))).first;
//     AtomType::aN3P = *repository.insert (new AN3P ((str = "N3P"))).first;
//     AtomType::aN3R = *repository.insert (new AN3R ((str = "N3R"))).first;
//     AtomType::aN3S = *repository.insert (new AN3S ((str = "N3S"))).first;
//     AtomType::aN3T = *repository.insert (new AN3T ((str = "N3T"))).first;
//     AtomType::aN3U = *repository.insert (new AN3U ((str = "N3U"))).first;
//     AtomType::aN3X = *repository.insert (new AN3X ((str = "N3X"))).first;
//     AtomType::aN4 = *repository.insert (new AN4 ((str = "N4"))).first;
//     AtomType::aN4* = *repository.insert (new AN4* ((str = "N4*"))).first;
//     AtomType::aN40 = *repository.insert (new AN40 ((str = "N40"))).first;
//     AtomType::aN41 = *repository.insert (new AN41 ((str = "N41"))).first;
//     AtomType::aN42 = *repository.insert (new AN42 ((str = "N42"))).first;
//     AtomType::aN43 = *repository.insert (new AN43 ((str = "N43"))).first;
//     AtomType::aN44 = *repository.insert (new AN44 ((str = "N44"))).first;
//     AtomType::aN45 = *repository.insert (new AN45 ((str = "N45"))).first;
//     AtomType::aN46 = *repository.insert (new AN46 ((str = "N46"))).first;
//     AtomType::aN47 = *repository.insert (new AN47 ((str = "N47"))).first;
//     AtomType::aN48 = *repository.insert (new AN48 ((str = "N48"))).first;
//     AtomType::aN49 = *repository.insert (new AN49 ((str = "N49"))).first;
//     AtomType::aN4A = *repository.insert (new AN4A ((str = "N4A"))).first;
//     AtomType::aN4B = *repository.insert (new AN4B ((str = "N4B"))).first;
//     AtomType::aN4C = *repository.insert (new AN4C ((str = "N4C"))).first;
//     AtomType::aN4E = *repository.insert (new AN4E ((str = "N4E"))).first;
//     AtomType::aN4F = *repository.insert (new AN4F ((str = "N4F"))).first;
//     AtomType::aN4I = *repository.insert (new AN4I ((str = "N4I"))).first;
//     AtomType::aN4M = *repository.insert (new AN4M ((str = "N4M"))).first;
//     AtomType::aN4P = *repository.insert (new AN4P ((str = "N4P"))).first;
//     AtomType::aN4Y = *repository.insert (new AN4Y ((str = "N4Y"))).first;
//     AtomType::aN5 = *repository.insert (new AN5 ((str = "N5"))).first;
//     AtomType::aN5* = *repository.insert (new AN5* ((str = "N5*"))).first;
//     AtomType::aN5** = *repository.insert (new AN5** ((str = "N5**"))).first;
//     AtomType::aN50 = *repository.insert (new AN50 ((str = "N50"))).first;
//     AtomType::aN51 = *repository.insert (new AN51 ((str = "N51"))).first;
//     AtomType::aN52 = *repository.insert (new AN52 ((str = "N52"))).first;
//     AtomType::aN53 = *repository.insert (new AN53 ((str = "N53"))).first;
//     AtomType::aN54 = *repository.insert (new AN54 ((str = "N54"))).first;
//     AtomType::aN55 = *repository.insert (new AN55 ((str = "N55"))).first;
//     AtomType::aN56 = *repository.insert (new AN56 ((str = "N56"))).first;
//     AtomType::aN57 = *repository.insert (new AN57 ((str = "N57"))).first;
//     AtomType::aN58 = *repository.insert (new AN58 ((str = "N58"))).first;
//     AtomType::aN59 = *repository.insert (new AN59 ((str = "N59"))).first;
//     AtomType::aN5A = *repository.insert (new AN5A ((str = "N5A"))).first;
//     AtomType::aN5B = *repository.insert (new AN5B ((str = "N5B"))).first;
//     AtomType::aN5D = *repository.insert (new AN5D ((str = "N5D"))).first;
//     AtomType::aN5F = *repository.insert (new AN5F ((str = "N5F"))).first;
//     AtomType::aN5G = *repository.insert (new AN5G ((str = "N5G"))).first;
//     AtomType::aN5X = *repository.insert (new AN5X ((str = "N5X"))).first;
//     AtomType::aN6 = *repository.insert (new AN6 ((str = "N6"))).first;
//     AtomType::aN6* = *repository.insert (new AN6* ((str = "N6*"))).first;
//     AtomType::aN60 = *repository.insert (new AN60 ((str = "N60"))).first;
//     AtomType::aN61 = *repository.insert (new AN61 ((str = "N61"))).first;
//     AtomType::aN62 = *repository.insert (new AN62 ((str = "N62"))).first;
//     AtomType::aN63 = *repository.insert (new AN63 ((str = "N63"))).first;
//     AtomType::aN64 = *repository.insert (new AN64 ((str = "N64"))).first;
//     AtomType::aN65 = *repository.insert (new AN65 ((str = "N65"))).first;
//     AtomType::aN66 = *repository.insert (new AN66 ((str = "N66"))).first;
//     AtomType::aN67 = *repository.insert (new AN67 ((str = "N67"))).first;
//     AtomType::aN68 = *repository.insert (new AN68 ((str = "N68"))).first;
//     AtomType::aN69 = *repository.insert (new AN69 ((str = "N69"))).first;
//     AtomType::aN6A = *repository.insert (new AN6A ((str = "N6A"))).first;
//     AtomType::aN6B = *repository.insert (new AN6B ((str = "N6B"))).first;
//     AtomType::aN6C = *repository.insert (new AN6C ((str = "N6C"))).first;
//     AtomType::aN6F = *repository.insert (new AN6F ((str = "N6F"))).first;
//     AtomType::aN6G = *repository.insert (new AN6G ((str = "N6G"))).first;
//     AtomType::aN6M = *repository.insert (new AN6M ((str = "N6M"))).first;
//     AtomType::aN6R = *repository.insert (new AN6R ((str = "N6R"))).first;
//     AtomType::aN6S = *repository.insert (new AN6S ((str = "N6S"))).first;
//     AtomType::aN6X = *repository.insert (new AN6X ((str = "N6X"))).first;
//     AtomType::aN7 = *repository.insert (new AN7 ((str = "N7"))).first;
//     AtomType::aN7* = *repository.insert (new AN7* ((str = "N7*"))).first;
//     AtomType::aN70 = *repository.insert (new AN70 ((str = "N70"))).first;
//     AtomType::aN71 = *repository.insert (new AN71 ((str = "N71"))).first;
//     AtomType::aN72 = *repository.insert (new AN72 ((str = "N72"))).first;
//     AtomType::aN73 = *repository.insert (new AN73 ((str = "N73"))).first;
//     AtomType::aN74 = *repository.insert (new AN74 ((str = "N74"))).first;
//     AtomType::aN76 = *repository.insert (new AN76 ((str = "N76"))).first;
//     AtomType::aN77 = *repository.insert (new AN77 ((str = "N77"))).first;
//     AtomType::aN78 = *repository.insert (new AN78 ((str = "N78"))).first;
//     AtomType::aN79 = *repository.insert (new AN79 ((str = "N79"))).first;
//     AtomType::aN7A = *repository.insert (new AN7A ((str = "N7A"))).first;
//     AtomType::aN7B = *repository.insert (new AN7B ((str = "N7B"))).first;
//     AtomType::aN7C = *repository.insert (new AN7C ((str = "N7C"))).first;
//     AtomType::aN7G = *repository.insert (new AN7G ((str = "N7G"))).first;
//     AtomType::aN7M = *repository.insert (new AN7M ((str = "N7M"))).first;
//     AtomType::aN7N = *repository.insert (new AN7N ((str = "N7N"))).first;
//     AtomType::aN7R = *repository.insert (new AN7R ((str = "N7R"))).first;
//     AtomType::aN7X = *repository.insert (new AN7X ((str = "N7X"))).first;
//     AtomType::aN8 = *repository.insert (new AN8 ((str = "N8"))).first;
//     AtomType::aN8* = *repository.insert (new AN8* ((str = "N8*"))).first;
//     AtomType::aN80 = *repository.insert (new AN80 ((str = "N80"))).first;
//     AtomType::aN81 = *repository.insert (new AN81 ((str = "N81"))).first;
//     AtomType::aN83 = *repository.insert (new AN83 ((str = "N83"))).first;
//     AtomType::aN85 = *repository.insert (new AN85 ((str = "N85"))).first;
//     AtomType::aN86 = *repository.insert (new AN86 ((str = "N86"))).first;
//     AtomType::aN87 = *repository.insert (new AN87 ((str = "N87"))).first;
//     AtomType::aN88 = *repository.insert (new AN88 ((str = "N88"))).first;
//     AtomType::aN8A = *repository.insert (new AN8A ((str = "N8A"))).first;
//     AtomType::aN8B = *repository.insert (new AN8B ((str = "N8B"))).first;
//     AtomType::aN8C = *repository.insert (new AN8C ((str = "N8C"))).first;
//     AtomType::aN8M = *repository.insert (new AN8M ((str = "N8M"))).first;
//     AtomType::aN8P = *repository.insert (new AN8P ((str = "N8P"))).first;
//     AtomType::aN9 = *repository.insert (new AN9 ((str = "N9"))).first;
//     AtomType::aN9* = *repository.insert (new AN9* ((str = "N9*"))).first;
//     AtomType::aN90 = *repository.insert (new AN90 ((str = "N90"))).first;
//     AtomType::aN91 = *repository.insert (new AN91 ((str = "N91"))).first;
//     AtomType::aN92 = *repository.insert (new AN92 ((str = "N92"))).first;
//     AtomType::aN93 = *repository.insert (new AN93 ((str = "N93"))).first;
//     AtomType::aN94 = *repository.insert (new AN94 ((str = "N94"))).first;
//     AtomType::aN95 = *repository.insert (new AN95 ((str = "N95"))).first;
//     AtomType::aN96 = *repository.insert (new AN96 ((str = "N96"))).first;
//     AtomType::aN99 = *repository.insert (new AN99 ((str = "N99"))).first;
//     AtomType::aN9A = *repository.insert (new AN9A ((str = "N9A"))).first;
//     AtomType::aN9B = *repository.insert (new AN9B ((str = "N9B"))).first;
//     AtomType::aN9C = *repository.insert (new AN9C ((str = "N9C"))).first;
//     AtomType::aN9G = *repository.insert (new AN9G ((str = "N9G"))).first;
//     AtomType::aN9R = *repository.insert (new AN9R ((str = "N9R"))).first;
//     AtomType::aN9X = *repository.insert (new AN9X ((str = "N9X"))).first;
//     AtomType::aNA = *repository.insert (new ANA ((str = "NA"))).first;
//     AtomType::aNA* = *repository.insert (new ANA* ((str = "NA*"))).first;
//     AtomType::aNA1 = *repository.insert (new ANA1 ((str = "NA1"))).first;
//     AtomType::aNA2 = *repository.insert (new ANA2 ((str = "NA2"))).first;
//     AtomType::aNA3 = *repository.insert (new ANA3 ((str = "NA3"))).first;
//     AtomType::aNA4 = *repository.insert (new ANA4 ((str = "NA4"))).first;
//     AtomType::aNA5 = *repository.insert (new ANA5 ((str = "NA5"))).first;
//     AtomType::aNA7 = *repository.insert (new ANA7 ((str = "NA7"))).first;
//     AtomType::aNAA = *repository.insert (new ANAA ((str = "NAA"))).first;
//     AtomType::aNAB = *repository.insert (new ANAB ((str = "NAB"))).first;
//     AtomType::aNAC = *repository.insert (new ANAC ((str = "NAC"))).first;
//     AtomType::aNAD = *repository.insert (new ANAD ((str = "NAD"))).first;
//     AtomType::aNAE = *repository.insert (new ANAE ((str = "NAE"))).first;
//     AtomType::aNAF = *repository.insert (new ANAF ((str = "NAF"))).first;
//     AtomType::aNAG = *repository.insert (new ANAG ((str = "NAG"))).first;
//     AtomType::aNAH = *repository.insert (new ANAH ((str = "NAH"))).first;
//     AtomType::aNAI = *repository.insert (new ANAI ((str = "NAI"))).first;
//     AtomType::aNAJ = *repository.insert (new ANAJ ((str = "NAJ"))).first;
//     AtomType::aNAK = *repository.insert (new ANAK ((str = "NAK"))).first;
//     AtomType::aNAL = *repository.insert (new ANAL ((str = "NAL"))).first;
//     AtomType::aNAM = *repository.insert (new ANAM ((str = "NAM"))).first;
//     AtomType::aNAN = *repository.insert (new ANAN ((str = "NAN"))).first;
//     AtomType::aNAO = *repository.insert (new ANAO ((str = "NAO"))).first;
//     AtomType::aNAP = *repository.insert (new ANAP ((str = "NAP"))).first;
//     AtomType::aNAQ = *repository.insert (new ANAQ ((str = "NAQ"))).first;
//     AtomType::aNAR = *repository.insert (new ANAR ((str = "NAR"))).first;
//     AtomType::aNAS = *repository.insert (new ANAS ((str = "NAS"))).first;
//     AtomType::aNAT = *repository.insert (new ANAT ((str = "NAT"))).first;
//     AtomType::aNAU = *repository.insert (new ANAU ((str = "NAU"))).first;
//     AtomType::aNAV = *repository.insert (new ANAV ((str = "NAV"))).first;
//     AtomType::aNAW = *repository.insert (new ANAW ((str = "NAW"))).first;
//     AtomType::aNAX = *repository.insert (new ANAX ((str = "NAX"))).first;
//     AtomType::aNAY = *repository.insert (new ANAY ((str = "NAY"))).first;
//     AtomType::aNAZ = *repository.insert (new ANAZ ((str = "NAZ"))).first;
//     AtomType::aNB = *repository.insert (new ANB ((str = "NB"))).first;
//     AtomType::aNB* = *repository.insert (new ANB* ((str = "NB*"))).first;
//     AtomType::aNB1 = *repository.insert (new ANB1 ((str = "NB1"))).first;
//     AtomType::aNB2 = *repository.insert (new ANB2 ((str = "NB2"))).first;
//     AtomType::aNB4 = *repository.insert (new ANB4 ((str = "NB4"))).first;
//     AtomType::aNB5 = *repository.insert (new ANB5 ((str = "NB5"))).first;
//     AtomType::aNB7 = *repository.insert (new ANB7 ((str = "NB7"))).first;
//     AtomType::aNBA = *repository.insert (new ANBA ((str = "NBA"))).first;
//     AtomType::aNBB = *repository.insert (new ANBB ((str = "NBB"))).first;
//     AtomType::aNBC = *repository.insert (new ANBC ((str = "NBC"))).first;
//     AtomType::aNBD = *repository.insert (new ANBD ((str = "NBD"))).first;
//     AtomType::aNBE = *repository.insert (new ANBE ((str = "NBE"))).first;
//     AtomType::aNBF = *repository.insert (new ANBF ((str = "NBF"))).first;
//     AtomType::aNBG = *repository.insert (new ANBG ((str = "NBG"))).first;
//     AtomType::aNBH = *repository.insert (new ANBH ((str = "NBH"))).first;
//     AtomType::aNBI = *repository.insert (new ANBI ((str = "NBI"))).first;
//     AtomType::aNBJ = *repository.insert (new ANBJ ((str = "NBJ"))).first;
//     AtomType::aNBK = *repository.insert (new ANBK ((str = "NBK"))).first;
//     AtomType::aNBL = *repository.insert (new ANBL ((str = "NBL"))).first;
//     AtomType::aNBN = *repository.insert (new ANBN ((str = "NBN"))).first;
//     AtomType::aNBP = *repository.insert (new ANBP ((str = "NBP"))).first;
//     AtomType::aNBS = *repository.insert (new ANBS ((str = "NBS"))).first;
//     AtomType::aNBV = *repository.insert (new ANBV ((str = "NBV"))).first;
//     AtomType::aNBW = *repository.insert (new ANBW ((str = "NBW"))).first;
//     AtomType::aNBY = *repository.insert (new ANBY ((str = "NBY"))).first;
//     AtomType::aNBZ = *repository.insert (new ANBZ ((str = "NBZ"))).first;
//     AtomType::aNC = *repository.insert (new ANC ((str = "NC"))).first;
//     AtomType::aNC* = *repository.insert (new ANC* ((str = "NC*"))).first;
//     AtomType::aNC1 = *repository.insert (new ANC1 ((str = "NC1"))).first;
//     AtomType::aNC1* = *repository.insert (new ANC1* ((str = "NC1*"))).first;
//     AtomType::aNC2 = *repository.insert (new ANC2 ((str = "NC2"))).first;
//     AtomType::aNC2* = *repository.insert (new ANC2* ((str = "NC2*"))).first;
//     AtomType::aNC3 = *repository.insert (new ANC3 ((str = "NC3"))).first;
//     AtomType::aNC3* = *repository.insert (new ANC3* ((str = "NC3*"))).first;
//     AtomType::aNC4 = *repository.insert (new ANC4 ((str = "NC4"))).first;
//     AtomType::aNC4* = *repository.insert (new ANC4* ((str = "NC4*"))).first;
//     AtomType::aNC5 = *repository.insert (new ANC5 ((str = "NC5"))).first;
//     AtomType::aNC5* = *repository.insert (new ANC5* ((str = "NC5*"))).first;
//     AtomType::aNC6 = *repository.insert (new ANC6 ((str = "NC6"))).first;
//     AtomType::aNC7 = *repository.insert (new ANC7 ((str = "NC7"))).first;
//     AtomType::aNC8 = *repository.insert (new ANC8 ((str = "NC8"))).first;
//     AtomType::aNCA = *repository.insert (new ANCA ((str = "NCA"))).first;
//     AtomType::aNCB = *repository.insert (new ANCB ((str = "NCB"))).first;
//     AtomType::aNCE = *repository.insert (new ANCE ((str = "NCE"))).first;
//     AtomType::aNCG = *repository.insert (new ANCG ((str = "NCG"))).first;
//     AtomType::aNCL = *repository.insert (new ANCL ((str = "NCL"))).first;
//     AtomType::aND = *repository.insert (new AND ((str = "ND"))).first;
//     AtomType::aND* = *repository.insert (new AND* ((str = "ND*"))).first;
//     AtomType::aND1 = *repository.insert (new AND1 ((str = "ND1"))).first;
//     AtomType::aND2 = *repository.insert (new AND2 ((str = "ND2"))).first;
//     AtomType::aND3 = *repository.insert (new AND3 ((str = "ND3"))).first;
//     AtomType::aND4 = *repository.insert (new AND4 ((str = "ND4"))).first;
//     AtomType::aNDC = *repository.insert (new ANDC ((str = "NDC"))).first;
//     AtomType::aNE = *repository.insert (new ANE ((str = "NE"))).first;
//     AtomType::aNE* = *repository.insert (new ANE* ((str = "NE*"))).first;
//     AtomType::aNE1 = *repository.insert (new ANE1 ((str = "NE1"))).first;
//     AtomType::aNE1T = *repository.insert (new ANE1T ((str = "NE1T"))).first;
//     AtomType::aNE2 = *repository.insert (new ANE2 ((str = "NE2"))).first;
//     AtomType::aNE3 = *repository.insert (new ANE3 ((str = "NE3"))).first;
//     AtomType::aNEO = *repository.insert (new ANEO ((str = "NEO"))).first;
//     AtomType::aNF = *repository.insert (new ANF ((str = "NF"))).first;
//     AtomType::aNF* = *repository.insert (new ANF* ((str = "NF*"))).first;
//     AtomType::aNF1 = *repository.insert (new ANF1 ((str = "NF1"))).first;
//     AtomType::aNFE = *repository.insert (new ANFE ((str = "NFE"))).first;
//     AtomType::aNG = *repository.insert (new ANG ((str = "NG"))).first;
//     AtomType::aNG* = *repository.insert (new ANG* ((str = "NG*"))).first;
//     AtomType::aNG1 = *repository.insert (new ANG1 ((str = "NG1"))).first;
//     AtomType::aNG2 = *repository.insert (new ANG2 ((str = "NG2"))).first;
//     AtomType::aNG3 = *repository.insert (new ANG3 ((str = "NG3"))).first;
//     AtomType::aNGB = *repository.insert (new ANGB ((str = "NGB"))).first;
//     AtomType::aNH = *repository.insert (new ANH ((str = "NH"))).first;
//     AtomType::aNH09 = *repository.insert (new ANH09 ((str = "NH09"))).first;
//     AtomType::aNH1 = *repository.insert (new ANH1 ((str = "NH1"))).first;
//     AtomType::aNH1* = *repository.insert (new ANH1* ((str = "NH1*"))).first;
//     AtomType::aNH10 = *repository.insert (new ANH10 ((str = "NH10"))).first;
//     AtomType::aNH11 = *repository.insert (new ANH11 ((str = "NH11"))).first;
//     AtomType::aNH12 = *repository.insert (new ANH12 ((str = "NH12"))).first;
//     AtomType::aNH13 = *repository.insert (new ANH13 ((str = "NH13"))).first;
//     AtomType::aNH14 = *repository.insert (new ANH14 ((str = "NH14"))).first;
//     AtomType::aNH15 = *repository.insert (new ANH15 ((str = "NH15"))).first;
//     AtomType::aNH16 = *repository.insert (new ANH16 ((str = "NH16"))).first;
//     AtomType::aNH17 = *repository.insert (new ANH17 ((str = "NH17"))).first;
//     AtomType::aNH19 = *repository.insert (new ANH19 ((str = "NH19"))).first;
//     AtomType::aNH1B = *repository.insert (new ANH1B ((str = "NH1B"))).first;
//     AtomType::aNH2 = *repository.insert (new ANH2 ((str = "NH2"))).first;
//     AtomType::aNH2* = *repository.insert (new ANH2* ((str = "NH2*"))).first;
//     AtomType::aNH21 = *repository.insert (new ANH21 ((str = "NH21"))).first;
//     AtomType::aNH22 = *repository.insert (new ANH22 ((str = "NH22"))).first;
//     AtomType::aNH24 = *repository.insert (new ANH24 ((str = "NH24"))).first;
//     AtomType::aNH26 = *repository.insert (new ANH26 ((str = "NH26"))).first;
//     AtomType::aNH3 = *repository.insert (new ANH3 ((str = "NH3"))).first;
//     AtomType::aNH3* = *repository.insert (new ANH3* ((str = "NH3*"))).first;
//     AtomType::aNH30 = *repository.insert (new ANH30 ((str = "NH30"))).first;
//     AtomType::aNH31 = *repository.insert (new ANH31 ((str = "NH31"))).first;
//     AtomType::aNH33 = *repository.insert (new ANH33 ((str = "NH33"))).first;
//     AtomType::aNH36 = *repository.insert (new ANH36 ((str = "NH36"))).first;
//     AtomType::aNH37 = *repository.insert (new ANH37 ((str = "NH37"))).first;
//     AtomType::aNH4 = *repository.insert (new ANH4 ((str = "NH4"))).first;
//     AtomType::aNH4* = *repository.insert (new ANH4* ((str = "NH4*"))).first;
//     AtomType::aNH41 = *repository.insert (new ANH41 ((str = "NH41"))).first;
//     AtomType::aNH42 = *repository.insert (new ANH42 ((str = "NH42"))).first;
//     AtomType::aNH44 = *repository.insert (new ANH44 ((str = "NH44"))).first;
//     AtomType::aNH5 = *repository.insert (new ANH5 ((str = "NH5"))).first;
//     AtomType::aNH51 = *repository.insert (new ANH51 ((str = "NH51"))).first;
//     AtomType::aNH52 = *repository.insert (new ANH52 ((str = "NH52"))).first;
//     AtomType::aNH6 = *repository.insert (new ANH6 ((str = "NH6"))).first;
//     AtomType::aNH61 = *repository.insert (new ANH61 ((str = "NH61"))).first;
//     AtomType::aNH62 = *repository.insert (new ANH62 ((str = "NH62"))).first;
//     AtomType::aNH7 = *repository.insert (new ANH7 ((str = "NH7"))).first;
//     AtomType::aNH71 = *repository.insert (new ANH71 ((str = "NH71"))).first;
//     AtomType::aNH72 = *repository.insert (new ANH72 ((str = "NH72"))).first;
//     AtomType::aNH81 = *repository.insert (new ANH81 ((str = "NH81"))).first;
//     AtomType::aNH82 = *repository.insert (new ANH82 ((str = "NH82"))).first;
//     AtomType::aNH83 = *repository.insert (new ANH83 ((str = "NH83"))).first;
//     AtomType::aNHE1 = *repository.insert (new ANHE1 ((str = "NHE1"))).first;
//     AtomType::aNHO = *repository.insert (new ANHO ((str = "NHO"))).first;
//     AtomType::aNHO2 = *repository.insert (new ANHO2 ((str = "NHO2"))).first;
//     AtomType::aNHO3 = *repository.insert (new ANHO3 ((str = "NHO3"))).first;
//     AtomType::aNHO6 = *repository.insert (new ANHO6 ((str = "NHO6"))).first;
//     AtomType::aNHP2 = *repository.insert (new ANHP2 ((str = "NHP2"))).first;
//     AtomType::aNI = *repository.insert (new ANI ((str = "NI"))).first;
//     AtomType::aNI1 = *repository.insert (new ANI1 ((str = "NI1"))).first;
//     AtomType::aNI2 = *repository.insert (new ANI2 ((str = "NI2"))).first;
//     AtomType::aNJ = *repository.insert (new ANJ ((str = "NJ"))).first;
//     AtomType::aNJ1 = *repository.insert (new ANJ1 ((str = "NJ1"))).first;
//     AtomType::aNJ2 = *repository.insert (new ANJ2 ((str = "NJ2"))).first;
//     AtomType::aNK = *repository.insert (new ANK ((str = "NK"))).first;
//     AtomType::aNL = *repository.insert (new ANL ((str = "NL"))).first;
//     AtomType::aNL1 = *repository.insert (new ANL1 ((str = "NL1"))).first;
//     AtomType::aNL2 = *repository.insert (new ANL2 ((str = "NL2"))).first;
//     AtomType::aNM = *repository.insert (new ANM ((str = "NM"))).first;
//     AtomType::aNM1 = *repository.insert (new ANM1 ((str = "NM1"))).first;
//     AtomType::aNM2 = *repository.insert (new ANM2 ((str = "NM2"))).first;
//     AtomType::aNM3 = *repository.insert (new ANM3 ((str = "NM3"))).first;
//     AtomType::aNN = *repository.insert (new ANN ((str = "NN"))).first;
//     AtomType::aNN1 = *repository.insert (new ANN1 ((str = "NN1"))).first;
//     AtomType::aNN2 = *repository.insert (new ANN2 ((str = "NN2"))).first;
//     AtomType::aNN3 = *repository.insert (new ANN3 ((str = "NN3"))).first;
//     AtomType::aNN5 = *repository.insert (new ANN5 ((str = "NN5"))).first;
//     AtomType::aNN6 = *repository.insert (new ANN6 ((str = "NN6"))).first;
//     AtomType::aNN7 = *repository.insert (new ANN7 ((str = "NN7"))).first;
//     AtomType::aNNG = *repository.insert (new ANNG ((str = "NNG"))).first;
//     AtomType::aNO = *repository.insert (new ANO ((str = "NO"))).first;
//     AtomType::aNO1 = *repository.insert (new ANO1 ((str = "NO1"))).first;
//     AtomType::aNO1P = *repository.insert (new ANO1P ((str = "NO1P"))).first;
//     AtomType::aNO2 = *repository.insert (new ANO2 ((str = "NO2"))).first;
//     AtomType::aNO2* = *repository.insert (new ANO2* ((str = "NO2*"))).first;
//     AtomType::aNO2P = *repository.insert (new ANO2P ((str = "NO2P"))).first;
//     AtomType::aNO3* = *repository.insert (new ANO3* ((str = "NO3*"))).first;
//     AtomType::aNO4* = *repository.insert (new ANO4* ((str = "NO4*"))).first;
//     AtomType::aNO5 = *repository.insert (new ANO5 ((str = "NO5"))).first;
//     AtomType::aNO5* = *repository.insert (new ANO5* ((str = "NO5*"))).first;
//     AtomType::aNO6 = *repository.insert (new ANO6 ((str = "NO6"))).first;
//     AtomType::aNO7 = *repository.insert (new ANO7 ((str = "NO7"))).first;
//     AtomType::aNP = *repository.insert (new ANP ((str = "NP"))).first;
//     AtomType::aNP0 = *repository.insert (new ANP0 ((str = "NP0"))).first;
//     AtomType::aNP1 = *repository.insert (new ANP1 ((str = "NP1"))).first;
//     AtomType::aNP2 = *repository.insert (new ANP2 ((str = "NP2"))).first;
//     AtomType::aNP3 = *repository.insert (new ANP3 ((str = "NP3"))).first;
//     AtomType::aNP4 = *repository.insert (new ANP4 ((str = "NP4"))).first;
//     AtomType::aNP5 = *repository.insert (new ANP5 ((str = "NP5"))).first;
//     AtomType::aNP6 = *repository.insert (new ANP6 ((str = "NP6"))).first;
//     AtomType::aNP7 = *repository.insert (new ANP7 ((str = "NP7"))).first;
//     AtomType::aNP8 = *repository.insert (new ANP8 ((str = "NP8"))).first;
//     AtomType::aNPA = *repository.insert (new ANPA ((str = "NPA"))).first;
//     AtomType::aNPB = *repository.insert (new ANPB ((str = "NPB"))).first;
//     AtomType::aNPC = *repository.insert (new ANPC ((str = "NPC"))).first;
//     AtomType::aNPD = *repository.insert (new ANPD ((str = "NPD"))).first;
//     AtomType::aNPE = *repository.insert (new ANPE ((str = "NPE"))).first;
//     AtomType::aNPJ = *repository.insert (new ANPJ ((str = "NPJ"))).first;
//     AtomType::aNPL = *repository.insert (new ANPL ((str = "NPL"))).first;
//     AtomType::aNPN = *repository.insert (new ANPN ((str = "NPN"))).first;
//     AtomType::aNPS = *repository.insert (new ANPS ((str = "NPS"))).first;
//     AtomType::aNQ = *repository.insert (new ANQ ((str = "NQ"))).first;
//     AtomType::aNQ1 = *repository.insert (new ANQ1 ((str = "NQ1"))).first;
//     AtomType::aNQ2 = *repository.insert (new ANQ2 ((str = "NQ2"))).first;
//     AtomType::aNQ5 = *repository.insert (new ANQ5 ((str = "NQ5"))).first;
//     AtomType::aNR = *repository.insert (new ANR ((str = "NR"))).first;
//     AtomType::aNR1 = *repository.insert (new ANR1 ((str = "NR1"))).first;
//     AtomType::aNR2 = *repository.insert (new ANR2 ((str = "NR2"))).first;
//     AtomType::aNS = *repository.insert (new ANS ((str = "NS"))).first;
//     AtomType::aNS1 = *repository.insert (new ANS1 ((str = "NS1"))).first;
//     AtomType::aNS7 = *repository.insert (new ANS7 ((str = "NS7"))).first;
//     AtomType::aNSE1 = *repository.insert (new ANSE1 ((str = "NSE1"))).first;
//     AtomType::aNT = *repository.insert (new ANT ((str = "NT"))).first;
//     AtomType::aNT1 = *repository.insert (new ANT1 ((str = "NT1"))).first;
//     AtomType::aNT2 = *repository.insert (new ANT2 ((str = "NT2"))).first;
//     AtomType::aNT3 = *repository.insert (new ANT3 ((str = "NT3"))).first;
//     AtomType::aNT6 = *repository.insert (new ANT6 ((str = "NT6"))).first;
//     AtomType::aNV = *repository.insert (new ANV ((str = "NV"))).first;
//     AtomType::aNV2 = *repository.insert (new ANV2 ((str = "NV2"))).first;
//     AtomType::aNV4 = *repository.insert (new ANV4 ((str = "NV4"))).first;
//     AtomType::aNX = *repository.insert (new ANX ((str = "NX"))).first;
//     AtomType::aNX1 = *repository.insert (new ANX1 ((str = "NX1"))).first;
//     AtomType::aNX2 = *repository.insert (new ANX2 ((str = "NX2"))).first;
//     AtomType::aNX5 = *repository.insert (new ANX5 ((str = "NX5"))).first;
//     AtomType::aNX6 = *repository.insert (new ANX6 ((str = "NX6"))).first;
//     AtomType::aNXH = *repository.insert (new ANXH ((str = "NXH"))).first;
//     AtomType::aNXT = *repository.insert (new ANXT ((str = "NXT"))).first;
//     AtomType::aNY = *repository.insert (new ANY ((str = "NY"))).first;
//     AtomType::aNY4 = *repository.insert (new ANY4 ((str = "NY4"))).first;
//     AtomType::aNZ = *repository.insert (new ANZ ((str = "NZ"))).first;
//     AtomType::aNZ* = *repository.insert (new ANZ* ((str = "NZ*"))).first;
//     AtomType::aNZ1 = *repository.insert (new ANZ1 ((str = "NZ1"))).first;
//     AtomType::aNZ2 = *repository.insert (new ANZ2 ((str = "NZ2"))).first;
//     AtomType::aNZ3 = *repository.insert (new ANZ3 ((str = "NZ3"))).first;
//     AtomType::aNZ7 = *repository.insert (new ANZ7 ((str = "NZ7"))).first;
//     AtomType::aNZK = *repository.insert (new ANZK ((str = "NZK"))).first;
//     AtomType::aN_1 = *repository.insert (new AN_1 ((str = "N_1"))).first;
//     AtomType::aN_2 = *repository.insert (new AN_2 ((str = "N_2"))).first;
//     AtomType::aO = *repository.insert (new AO ((str = "O"))).first;
//     AtomType::aO" = *repository.insert (new AO" ((str = "O""))).first;
//     AtomType::aO* = *repository.insert (new AO* ((str = "O*"))).first;
//     AtomType::aO*12 = *repository.insert (new AO*12 ((str = "O*12"))).first;
//     AtomType::aO*2 = *repository.insert (new AO*2 ((str = "O*2"))).first;
//     AtomType::aO*4 = *repository.insert (new AO*4 ((str = "O*4"))).first;
//     AtomType::aO*7 = *repository.insert (new AO*7 ((str = "O*7"))).first;
//     AtomType::aO*F = *repository.insert (new AO*F ((str = "O*F"))).first;
//     AtomType::aO0 = *repository.insert (new AO0 ((str = "O0"))).first;
//     AtomType::aO00 = *repository.insert (new AO00 ((str = "O00"))).first;
//     AtomType::aO01 = *repository.insert (new AO01 ((str = "O01"))).first;
//     AtomType::aO02 = *repository.insert (new AO02 ((str = "O02"))).first;
//     AtomType::aO03 = *repository.insert (new AO03 ((str = "O03"))).first;
//     AtomType::aO04 = *repository.insert (new AO04 ((str = "O04"))).first;
//     AtomType::aO05 = *repository.insert (new AO05 ((str = "O05"))).first;
//     AtomType::aO06 = *repository.insert (new AO06 ((str = "O06"))).first;
//     AtomType::aO07 = *repository.insert (new AO07 ((str = "O07"))).first;
//     AtomType::aO08 = *repository.insert (new AO08 ((str = "O08"))).first;
//     AtomType::aO09 = *repository.insert (new AO09 ((str = "O09"))).first;
//     AtomType::aO0C = *repository.insert (new AO0C ((str = "O0C"))).first;
//     AtomType::aO0D = *repository.insert (new AO0D ((str = "O0D"))).first;
//     AtomType::aO0F = *repository.insert (new AO0F ((str = "O0F"))).first;
//     AtomType::aO0H = *repository.insert (new AO0H ((str = "O0H"))).first;
//     AtomType::aO0M = *repository.insert (new AO0M ((str = "O0M"))).first;
//     AtomType::aO0R = *repository.insert (new AO0R ((str = "O0R"))).first;
//     AtomType::aO1 = *repository.insert (new AO1 ((str = "O1"))).first;
//     AtomType::aO1" = *repository.insert (new AO1" ((str = "O1""))).first;
//     AtomType::aO1* = *repository.insert (new AO1* ((str = "O1*"))).first;
//     AtomType::aO10 = *repository.insert (new AO10 ((str = "O10"))).first;
//     AtomType::aO10* = *repository.insert (new AO10* ((str = "O10*"))).first;
//     AtomType::aO100 = *repository.insert (new AO100 ((str = "O100"))).first;
//     AtomType::aO105 = *repository.insert (new AO105 ((str = "O105"))).first;
//     AtomType::aO10A = *repository.insert (new AO10A ((str = "O10A"))).first;
//     AtomType::aO10P = *repository.insert (new AO10P ((str = "O10P"))).first;
//     AtomType::aO11 = *repository.insert (new AO11 ((str = "O11"))).first;
//     AtomType::aO118 = *repository.insert (new AO118 ((str = "O118"))).first;
//     AtomType::aO11A = *repository.insert (new AO11A ((str = "O11A"))).first;
//     AtomType::aO11B = *repository.insert (new AO11B ((str = "O11B"))).first;
//     AtomType::aO11D = *repository.insert (new AO11D ((str = "O11D"))).first;
//     AtomType::aO11P = *repository.insert (new AO11P ((str = "O11P"))).first;
//     AtomType::aO12 = *repository.insert (new AO12 ((str = "O12"))).first;
//     AtomType::aO12* = *repository.insert (new AO12* ((str = "O12*"))).first;
//     AtomType::aO12B = *repository.insert (new AO12B ((str = "O12B"))).first;
//     AtomType::aO12C = *repository.insert (new AO12C ((str = "O12C"))).first;
//     AtomType::aO12P = *repository.insert (new AO12P ((str = "O12P"))).first;
//     AtomType::aO13 = *repository.insert (new AO13 ((str = "O13"))).first;
//     AtomType::aO13* = *repository.insert (new AO13* ((str = "O13*"))).first;
//     AtomType::aO13A = *repository.insert (new AO13A ((str = "O13A"))).first;
//     AtomType::aO13B = *repository.insert (new AO13B ((str = "O13B"))).first;
//     AtomType::aO14 = *repository.insert (new AO14 ((str = "O14"))).first;
//     AtomType::aO14* = *repository.insert (new AO14* ((str = "O14*"))).first;
//     AtomType::aO15 = *repository.insert (new AO15 ((str = "O15"))).first;
//     AtomType::aO15* = *repository.insert (new AO15* ((str = "O15*"))).first;
//     AtomType::aO16 = *repository.insert (new AO16 ((str = "O16"))).first;
//     AtomType::aO17 = *repository.insert (new AO17 ((str = "O17"))).first;
//     AtomType::aO18 = *repository.insert (new AO18 ((str = "O18"))).first;
//     AtomType::aO19 = *repository.insert (new AO19 ((str = "O19"))).first;
//     AtomType::aO1A = *repository.insert (new AO1A ((str = "O1A"))).first;
//     AtomType::aO1B = *repository.insert (new AO1B ((str = "O1B"))).first;
//     AtomType::aO1C = *repository.insert (new AO1C ((str = "O1C"))).first;
//     AtomType::aO1D = *repository.insert (new AO1D ((str = "O1D"))).first;
//     AtomType::aO1E = *repository.insert (new AO1E ((str = "O1E"))).first;
//     AtomType::aO1F = *repository.insert (new AO1F ((str = "O1F"))).first;
//     AtomType::aO1G = *repository.insert (new AO1G ((str = "O1G"))).first;
//     AtomType::aO1H = *repository.insert (new AO1H ((str = "O1H"))).first;
//     AtomType::aO1I = *repository.insert (new AO1I ((str = "O1I"))).first;
//     AtomType::aO1J = *repository.insert (new AO1J ((str = "O1J"))).first;
//     AtomType::aO1K = *repository.insert (new AO1K ((str = "O1K"))).first;
//     AtomType::aO1L = *repository.insert (new AO1L ((str = "O1L"))).first;
//     AtomType::aO1M = *repository.insert (new AO1M ((str = "O1M"))).first;
//     AtomType::aO1N = *repository.insert (new AO1N ((str = "O1N"))).first;
//     AtomType::aO1P = *repository.insert (new AO1P ((str = "O1P"))).first;
//     AtomType::aO1P* = *repository.insert (new AO1P* ((str = "O1P*"))).first;
//     AtomType::aO1PA = *repository.insert (new AO1PA ((str = "O1PA"))).first;
//     AtomType::aO1PN = *repository.insert (new AO1PN ((str = "O1PN"))).first;
//     AtomType::aO1Q = *repository.insert (new AO1Q ((str = "O1Q"))).first;
//     AtomType::aO1R = *repository.insert (new AO1R ((str = "O1R"))).first;
//     AtomType::aO1S = *repository.insert (new AO1S ((str = "O1S"))).first;
//     AtomType::aO1S* = *repository.insert (new AO1S* ((str = "O1S*"))).first;
//     AtomType::aO1T = *repository.insert (new AO1T ((str = "O1T"))).first;
//     AtomType::aO1U = *repository.insert (new AO1U ((str = "O1U"))).first;
//     AtomType::aO1V = *repository.insert (new AO1V ((str = "O1V"))).first;
//     AtomType::aO1W = *repository.insert (new AO1W ((str = "O1W"))).first;
//     AtomType::aO1X = *repository.insert (new AO1X ((str = "O1X"))).first;
//     AtomType::aO1Y = *repository.insert (new AO1Y ((str = "O1Y"))).first;
//     AtomType::aO2 = *repository.insert (new AO2 ((str = "O2"))).first;
//     AtomType::aO2" = *repository.insert (new AO2" ((str = "O2""))).first;
//     AtomType::aO2* = *repository.insert (new AO2* ((str = "O2*"))).first;
//     AtomType::aO2** = *repository.insert (new AO2** ((str = "O2**"))).first;
//     AtomType::aO2*A = *repository.insert (new AO2*A ((str = "O2*A"))).first;
//     AtomType::aO2*B = *repository.insert (new AO2*B ((str = "O2*B"))).first;
//     AtomType::aO2*G = *repository.insert (new AO2*G ((str = "O2*G"))).first;
//     AtomType::aO2*N = *repository.insert (new AO2*N ((str = "O2*N"))).first;
//     AtomType::aO2*U = *repository.insert (new AO2*U ((str = "O2*U"))).first;
//     AtomType::aO20 = *repository.insert (new AO20 ((str = "O20"))).first;
//     AtomType::aO21 = *repository.insert (new AO21 ((str = "O21"))).first;
//     AtomType::aO21P = *repository.insert (new AO21P ((str = "O21P"))).first;
//     AtomType::aO22 = *repository.insert (new AO22 ((str = "O22"))).first;
//     AtomType::aO22* = *repository.insert (new AO22* ((str = "O22*"))).first;
//     AtomType::aO22P = *repository.insert (new AO22P ((str = "O22P"))).first;
//     AtomType::aO23 = *repository.insert (new AO23 ((str = "O23"))).first;
//     AtomType::aO23* = *repository.insert (new AO23* ((str = "O23*"))).first;
//     AtomType::aO24 = *repository.insert (new AO24 ((str = "O24"))).first;
//     AtomType::aO24* = *repository.insert (new AO24* ((str = "O24*"))).first;
//     AtomType::aO25 = *repository.insert (new AO25 ((str = "O25"))).first;
//     AtomType::aO25* = *repository.insert (new AO25* ((str = "O25*"))).first;
//     AtomType::aO26 = *repository.insert (new AO26 ((str = "O26"))).first;
//     AtomType::aO27 = *repository.insert (new AO27 ((str = "O27"))).first;
//     AtomType::aO28 = *repository.insert (new AO28 ((str = "O28"))).first;
//     AtomType::aO29 = *repository.insert (new AO29 ((str = "O29"))).first;
//     AtomType::aO2A = *repository.insert (new AO2A ((str = "O2A"))).first;
//     AtomType::aO2B = *repository.insert (new AO2B ((str = "O2B"))).first;
//     AtomType::aO2C = *repository.insert (new AO2C ((str = "O2C"))).first;
//     AtomType::aO2D = *repository.insert (new AO2D ((str = "O2D"))).first;
//     AtomType::aO2E = *repository.insert (new AO2E ((str = "O2E"))).first;
//     AtomType::aO2F = *repository.insert (new AO2F ((str = "O2F"))).first;
//     AtomType::aO2G = *repository.insert (new AO2G ((str = "O2G"))).first;
//     AtomType::aO2H = *repository.insert (new AO2H ((str = "O2H"))).first;
//     AtomType::aO2I = *repository.insert (new AO2I ((str = "O2I"))).first;
//     AtomType::aO2J = *repository.insert (new AO2J ((str = "O2J"))).first;
//     AtomType::aO2K = *repository.insert (new AO2K ((str = "O2K"))).first;
//     AtomType::aO2L = *repository.insert (new AO2L ((str = "O2L"))).first;
//     AtomType::aO2M = *repository.insert (new AO2M ((str = "O2M"))).first;
//     AtomType::aO2N = *repository.insert (new AO2N ((str = "O2N"))).first;
//     AtomType::aO2P = *repository.insert (new AO2P ((str = "O2P"))).first;
//     AtomType::aO2P* = *repository.insert (new AO2P* ((str = "O2P*"))).first;
//     AtomType::aO2PA = *repository.insert (new AO2PA ((str = "O2PA"))).first;
//     AtomType::aO2PN = *repository.insert (new AO2PN ((str = "O2PN"))).first;
//     AtomType::aO2Q = *repository.insert (new AO2Q ((str = "O2Q"))).first;
//     AtomType::aO2R = *repository.insert (new AO2R ((str = "O2R"))).first;
//     AtomType::aO2S = *repository.insert (new AO2S ((str = "O2S"))).first;
//     AtomType::aO2S* = *repository.insert (new AO2S* ((str = "O2S*"))).first;
//     AtomType::aO2T = *repository.insert (new AO2T ((str = "O2T"))).first;
//     AtomType::aO2U = *repository.insert (new AO2U ((str = "O2U"))).first;
//     AtomType::aO2V = *repository.insert (new AO2V ((str = "O2V"))).first;
//     AtomType::aO2W = *repository.insert (new AO2W ((str = "O2W"))).first;
//     AtomType::aO2X = *repository.insert (new AO2X ((str = "O2X"))).first;
//     AtomType::aO2Y = *repository.insert (new AO2Y ((str = "O2Y"))).first;
//     AtomType::aO2Z = *repository.insert (new AO2Z ((str = "O2Z"))).first;
//     AtomType::aO3 = *repository.insert (new AO3 ((str = "O3"))).first;
//     AtomType::aO3" = *repository.insert (new AO3" ((str = "O3""))).first;
//     AtomType::aO3* = *repository.insert (new AO3* ((str = "O3*"))).first;
//     AtomType::aO3*A = *repository.insert (new AO3*A ((str = "O3*A"))).first;
//     AtomType::aO3*B = *repository.insert (new AO3*B ((str = "O3*B"))).first;
//     AtomType::aO3*G = *repository.insert (new AO3*G ((str = "O3*G"))).first;
//     AtomType::aO3*N = *repository.insert (new AO3*N ((str = "O3*N"))).first;
//     AtomType::aO3*U = *repository.insert (new AO3*U ((str = "O3*U"))).first;
//     AtomType::aO3, = *repository.insert (new AO3, ((str = "O3,"))).first;
//     AtomType::aO30 = *repository.insert (new AO30 ((str = "O30"))).first;
//     AtomType::aO31 = *repository.insert (new AO31 ((str = "O31"))).first;
//     AtomType::aO32 = *repository.insert (new AO32 ((str = "O32"))).first;
//     AtomType::aO33 = *repository.insert (new AO33 ((str = "O33"))).first;
//     AtomType::aO33* = *repository.insert (new AO33* ((str = "O33*"))).first;
//     AtomType::aO34 = *repository.insert (new AO34 ((str = "O34"))).first;
//     AtomType::aO34* = *repository.insert (new AO34* ((str = "O34*"))).first;
//     AtomType::aO35 = *repository.insert (new AO35 ((str = "O35"))).first;
//     AtomType::aO36 = *repository.insert (new AO36 ((str = "O36"))).first;
//     AtomType::aO37 = *repository.insert (new AO37 ((str = "O37"))).first;
//     AtomType::aO38 = *repository.insert (new AO38 ((str = "O38"))).first;
//     AtomType::aO39 = *repository.insert (new AO39 ((str = "O39"))).first;
//     AtomType::aO3A = *repository.insert (new AO3A ((str = "O3A"))).first;
//     AtomType::aO3B = *repository.insert (new AO3B ((str = "O3B"))).first;
//     AtomType::aO3C = *repository.insert (new AO3C ((str = "O3C"))).first;
//     AtomType::aO3D = *repository.insert (new AO3D ((str = "O3D"))).first;
//     AtomType::aO3E = *repository.insert (new AO3E ((str = "O3E"))).first;
//     AtomType::aO3F = *repository.insert (new AO3F ((str = "O3F"))).first;
//     AtomType::aO3G = *repository.insert (new AO3G ((str = "O3G"))).first;
//     AtomType::aO3H = *repository.insert (new AO3H ((str = "O3H"))).first;
//     AtomType::aO3I = *repository.insert (new AO3I ((str = "O3I"))).first;
//     AtomType::aO3J = *repository.insert (new AO3J ((str = "O3J"))).first;
//     AtomType::aO3K = *repository.insert (new AO3K ((str = "O3K"))).first;
//     AtomType::aO3L = *repository.insert (new AO3L ((str = "O3L"))).first;
//     AtomType::aO3M = *repository.insert (new AO3M ((str = "O3M"))).first;
//     AtomType::aO3N = *repository.insert (new AO3N ((str = "O3N"))).first;
//     AtomType::aO3P = *repository.insert (new AO3P ((str = "O3P"))).first;
//     AtomType::aO3P* = *repository.insert (new AO3P* ((str = "O3P*"))).first;
//     AtomType::aO3Q = *repository.insert (new AO3Q ((str = "O3Q"))).first;
//     AtomType::aO3R = *repository.insert (new AO3R ((str = "O3R"))).first;
//     AtomType::aO3S = *repository.insert (new AO3S ((str = "O3S"))).first;
//     AtomType::aO3S* = *repository.insert (new AO3S* ((str = "O3S*"))).first;
//     AtomType::aO3U = *repository.insert (new AO3U ((str = "O3U"))).first;
//     AtomType::aO3V = *repository.insert (new AO3V ((str = "O3V"))).first;
//     AtomType::aO3W = *repository.insert (new AO3W ((str = "O3W"))).first;
//     AtomType::aO3X = *repository.insert (new AO3X ((str = "O3X"))).first;
//     AtomType::aO3Y = *repository.insert (new AO3Y ((str = "O3Y"))).first;
//     AtomType::aO3Z = *repository.insert (new AO3Z ((str = "O3Z"))).first;
//     AtomType::aO4 = *repository.insert (new AO4 ((str = "O4"))).first;
//     AtomType::aO4" = *repository.insert (new AO4" ((str = "O4""))).first;
//     AtomType::aO4* = *repository.insert (new AO4* ((str = "O4*"))).first;
//     AtomType::aO4*A = *repository.insert (new AO4*A ((str = "O4*A"))).first;
//     AtomType::aO4*B = *repository.insert (new AO4*B ((str = "O4*B"))).first;
//     AtomType::aO4*G = *repository.insert (new AO4*G ((str = "O4*G"))).first;
//     AtomType::aO4*N = *repository.insert (new AO4*N ((str = "O4*N"))).first;
//     AtomType::aO4*U = *repository.insert (new AO4*U ((str = "O4*U"))).first;
//     AtomType::aO4, = *repository.insert (new AO4, ((str = "O4,"))).first;
//     AtomType::aO40 = *repository.insert (new AO40 ((str = "O40"))).first;
//     AtomType::aO41 = *repository.insert (new AO41 ((str = "O41"))).first;
//     AtomType::aO42 = *repository.insert (new AO42 ((str = "O42"))).first;
//     AtomType::aO43 = *repository.insert (new AO43 ((str = "O43"))).first;
//     AtomType::aO44 = *repository.insert (new AO44 ((str = "O44"))).first;
//     AtomType::aO44* = *repository.insert (new AO44* ((str = "O44*"))).first;
//     AtomType::aO45 = *repository.insert (new AO45 ((str = "O45"))).first;
//     AtomType::aO45* = *repository.insert (new AO45* ((str = "O45*"))).first;
//     AtomType::aO46 = *repository.insert (new AO46 ((str = "O46"))).first;
//     AtomType::aO47 = *repository.insert (new AO47 ((str = "O47"))).first;
//     AtomType::aO48 = *repository.insert (new AO48 ((str = "O48"))).first;
//     AtomType::aO49 = *repository.insert (new AO49 ((str = "O49"))).first;
//     AtomType::aO4A = *repository.insert (new AO4A ((str = "O4A"))).first;
//     AtomType::aO4B = *repository.insert (new AO4B ((str = "O4B"))).first;
//     AtomType::aO4C = *repository.insert (new AO4C ((str = "O4C"))).first;
//     AtomType::aO4D = *repository.insert (new AO4D ((str = "O4D"))).first;
//     AtomType::aO4E = *repository.insert (new AO4E ((str = "O4E"))).first;
//     AtomType::aO4F = *repository.insert (new AO4F ((str = "O4F"))).first;
//     AtomType::aO4G = *repository.insert (new AO4G ((str = "O4G"))).first;
//     AtomType::aO4H = *repository.insert (new AO4H ((str = "O4H"))).first;
//     AtomType::aO4I = *repository.insert (new AO4I ((str = "O4I"))).first;
//     AtomType::aO4J = *repository.insert (new AO4J ((str = "O4J"))).first;
//     AtomType::aO4K = *repository.insert (new AO4K ((str = "O4K"))).first;
//     AtomType::aO4L = *repository.insert (new AO4L ((str = "O4L"))).first;
//     AtomType::aO4M = *repository.insert (new AO4M ((str = "O4M"))).first;
//     AtomType::aO4P = *repository.insert (new AO4P ((str = "O4P"))).first;
//     AtomType::aO4R = *repository.insert (new AO4R ((str = "O4R"))).first;
//     AtomType::aO4S = *repository.insert (new AO4S ((str = "O4S"))).first;
//     AtomType::aO4T = *repository.insert (new AO4T ((str = "O4T"))).first;
//     AtomType::aO4U = *repository.insert (new AO4U ((str = "O4U"))).first;
//     AtomType::aO4W = *repository.insert (new AO4W ((str = "O4W"))).first;
//     AtomType::aO4X = *repository.insert (new AO4X ((str = "O4X"))).first;
//     AtomType::aO4Y = *repository.insert (new AO4Y ((str = "O4Y"))).first;
//     AtomType::aO4Z = *repository.insert (new AO4Z ((str = "O4Z"))).first;
//     AtomType::aO5 = *repository.insert (new AO5 ((str = "O5"))).first;
//     AtomType::aO5" = *repository.insert (new AO5" ((str = "O5""))).first;
//     AtomType::aO5* = *repository.insert (new AO5* ((str = "O5*"))).first;
//     AtomType::aO5*A = *repository.insert (new AO5*A ((str = "O5*A"))).first;
//     AtomType::aO5*B = *repository.insert (new AO5*B ((str = "O5*B"))).first;
//     AtomType::aO5*G = *repository.insert (new AO5*G ((str = "O5*G"))).first;
//     AtomType::aO5*N = *repository.insert (new AO5*N ((str = "O5*N"))).first;
//     AtomType::aO5*U = *repository.insert (new AO5*U ((str = "O5*U"))).first;
//     AtomType::aO5, = *repository.insert (new AO5, ((str = "O5,"))).first;
//     AtomType::aO50 = *repository.insert (new AO50 ((str = "O50"))).first;
//     AtomType::aO51 = *repository.insert (new AO51 ((str = "O51"))).first;
//     AtomType::aO52 = *repository.insert (new AO52 ((str = "O52"))).first;
//     AtomType::aO53 = *repository.insert (new AO53 ((str = "O53"))).first;
//     AtomType::aO54 = *repository.insert (new AO54 ((str = "O54"))).first;
//     AtomType::aO55 = *repository.insert (new AO55 ((str = "O55"))).first;
//     AtomType::aO56 = *repository.insert (new AO56 ((str = "O56"))).first;
//     AtomType::aO57 = *repository.insert (new AO57 ((str = "O57"))).first;
//     AtomType::aO58 = *repository.insert (new AO58 ((str = "O58"))).first;
//     AtomType::aO59 = *repository.insert (new AO59 ((str = "O59"))).first;
//     AtomType::aO5A = *repository.insert (new AO5A ((str = "O5A"))).first;
//     AtomType::aO5B = *repository.insert (new AO5B ((str = "O5B"))).first;
//     AtomType::aO5C = *repository.insert (new AO5C ((str = "O5C"))).first;
//     AtomType::aO5D = *repository.insert (new AO5D ((str = "O5D"))).first;
//     AtomType::aO5E = *repository.insert (new AO5E ((str = "O5E"))).first;
//     AtomType::aO5F = *repository.insert (new AO5F ((str = "O5F"))).first;
//     AtomType::aO5G = *repository.insert (new AO5G ((str = "O5G"))).first;
//     AtomType::aO5H = *repository.insert (new AO5H ((str = "O5H"))).first;
//     AtomType::aO5I = *repository.insert (new AO5I ((str = "O5I"))).first;
//     AtomType::aO5J = *repository.insert (new AO5J ((str = "O5J"))).first;
//     AtomType::aO5K = *repository.insert (new AO5K ((str = "O5K"))).first;
//     AtomType::aO5L = *repository.insert (new AO5L ((str = "O5L"))).first;
//     AtomType::aO5M = *repository.insert (new AO5M ((str = "O5M"))).first;
//     AtomType::aO5P = *repository.insert (new AO5P ((str = "O5P"))).first;
//     AtomType::aO5Q = *repository.insert (new AO5Q ((str = "O5Q"))).first;
//     AtomType::aO5R = *repository.insert (new AO5R ((str = "O5R"))).first;
//     AtomType::aO5S = *repository.insert (new AO5S ((str = "O5S"))).first;
//     AtomType::aO5W = *repository.insert (new AO5W ((str = "O5W"))).first;
//     AtomType::aO5X = *repository.insert (new AO5X ((str = "O5X"))).first;
//     AtomType::aO5Y = *repository.insert (new AO5Y ((str = "O5Y"))).first;
//     AtomType::aO5Z = *repository.insert (new AO5Z ((str = "O5Z"))).first;
//     AtomType::aO6 = *repository.insert (new AO6 ((str = "O6"))).first;
//     AtomType::aO6" = *repository.insert (new AO6" ((str = "O6""))).first;
//     AtomType::aO6* = *repository.insert (new AO6* ((str = "O6*"))).first;
//     AtomType::aO6*1 = *repository.insert (new AO6*1 ((str = "O6*1"))).first;
//     AtomType::aO6*2 = *repository.insert (new AO6*2 ((str = "O6*2"))).first;
//     AtomType::aO60 = *repository.insert (new AO60 ((str = "O60"))).first;
//     AtomType::aO61 = *repository.insert (new AO61 ((str = "O61"))).first;
//     AtomType::aO62 = *repository.insert (new AO62 ((str = "O62"))).first;
//     AtomType::aO63 = *repository.insert (new AO63 ((str = "O63"))).first;
//     AtomType::aO64 = *repository.insert (new AO64 ((str = "O64"))).first;
//     AtomType::aO65 = *repository.insert (new AO65 ((str = "O65"))).first;
//     AtomType::aO66 = *repository.insert (new AO66 ((str = "O66"))).first;
//     AtomType::aO67 = *repository.insert (new AO67 ((str = "O67"))).first;
//     AtomType::aO68 = *repository.insert (new AO68 ((str = "O68"))).first;
//     AtomType::aO69 = *repository.insert (new AO69 ((str = "O69"))).first;
//     AtomType::aO6A = *repository.insert (new AO6A ((str = "O6A"))).first;
//     AtomType::aO6B = *repository.insert (new AO6B ((str = "O6B"))).first;
//     AtomType::aO6C = *repository.insert (new AO6C ((str = "O6C"))).first;
//     AtomType::aO6D = *repository.insert (new AO6D ((str = "O6D"))).first;
//     AtomType::aO6E = *repository.insert (new AO6E ((str = "O6E"))).first;
//     AtomType::aO6F = *repository.insert (new AO6F ((str = "O6F"))).first;
//     AtomType::aO6G = *repository.insert (new AO6G ((str = "O6G"))).first;
//     AtomType::aO6H = *repository.insert (new AO6H ((str = "O6H"))).first;
//     AtomType::aO6I = *repository.insert (new AO6I ((str = "O6I"))).first;
//     AtomType::aO6K = *repository.insert (new AO6K ((str = "O6K"))).first;
//     AtomType::aO6L = *repository.insert (new AO6L ((str = "O6L"))).first;
//     AtomType::aO6M = *repository.insert (new AO6M ((str = "O6M"))).first;
//     AtomType::aO6P = *repository.insert (new AO6P ((str = "O6P"))).first;
//     AtomType::aO6Q = *repository.insert (new AO6Q ((str = "O6Q"))).first;
//     AtomType::aO6R = *repository.insert (new AO6R ((str = "O6R"))).first;
//     AtomType::aO6S = *repository.insert (new AO6S ((str = "O6S"))).first;
//     AtomType::aO6T = *repository.insert (new AO6T ((str = "O6T"))).first;
//     AtomType::aO6X = *repository.insert (new AO6X ((str = "O6X"))).first;
//     AtomType::aO7 = *repository.insert (new AO7 ((str = "O7"))).first;
//     AtomType::aO7" = *repository.insert (new AO7" ((str = "O7""))).first;
//     AtomType::aO7* = *repository.insert (new AO7* ((str = "O7*"))).first;
//     AtomType::aO70 = *repository.insert (new AO70 ((str = "O70"))).first;
//     AtomType::aO71 = *repository.insert (new AO71 ((str = "O71"))).first;
//     AtomType::aO72 = *repository.insert (new AO72 ((str = "O72"))).first;
//     AtomType::aO73 = *repository.insert (new AO73 ((str = "O73"))).first;
//     AtomType::aO74 = *repository.insert (new AO74 ((str = "O74"))).first;
//     AtomType::aO75 = *repository.insert (new AO75 ((str = "O75"))).first;
//     AtomType::aO76 = *repository.insert (new AO76 ((str = "O76"))).first;
//     AtomType::aO77 = *repository.insert (new AO77 ((str = "O77"))).first;
//     AtomType::aO78 = *repository.insert (new AO78 ((str = "O78"))).first;
//     AtomType::aO79 = *repository.insert (new AO79 ((str = "O79"))).first;
//     AtomType::aO7A = *repository.insert (new AO7A ((str = "O7A"))).first;
//     AtomType::aO7B = *repository.insert (new AO7B ((str = "O7B"))).first;
//     AtomType::aO7C = *repository.insert (new AO7C ((str = "O7C"))).first;
//     AtomType::aO7D = *repository.insert (new AO7D ((str = "O7D"))).first;
//     AtomType::aO7F = *repository.insert (new AO7F ((str = "O7F"))).first;
//     AtomType::aO7G = *repository.insert (new AO7G ((str = "O7G"))).first;
//     AtomType::aO7H = *repository.insert (new AO7H ((str = "O7H"))).first;
//     AtomType::aO7M = *repository.insert (new AO7M ((str = "O7M"))).first;
//     AtomType::aO7N = *repository.insert (new AO7N ((str = "O7N"))).first;
//     AtomType::aO7P = *repository.insert (new AO7P ((str = "O7P"))).first;
//     AtomType::aO7R = *repository.insert (new AO7R ((str = "O7R"))).first;
//     AtomType::aO7Z = *repository.insert (new AO7Z ((str = "O7Z"))).first;
//     AtomType::aO8 = *repository.insert (new AO8 ((str = "O8"))).first;
//     AtomType::aO8" = *repository.insert (new AO8" ((str = "O8""))).first;
//     AtomType::aO8* = *repository.insert (new AO8* ((str = "O8*"))).first;
//     AtomType::aO80 = *repository.insert (new AO80 ((str = "O80"))).first;
//     AtomType::aO81 = *repository.insert (new AO81 ((str = "O81"))).first;
//     AtomType::aO82 = *repository.insert (new AO82 ((str = "O82"))).first;
//     AtomType::aO83 = *repository.insert (new AO83 ((str = "O83"))).first;
//     AtomType::aO84 = *repository.insert (new AO84 ((str = "O84"))).first;
//     AtomType::aO85 = *repository.insert (new AO85 ((str = "O85"))).first;
//     AtomType::aO86 = *repository.insert (new AO86 ((str = "O86"))).first;
//     AtomType::aO87 = *repository.insert (new AO87 ((str = "O87"))).first;
//     AtomType::aO88 = *repository.insert (new AO88 ((str = "O88"))).first;
//     AtomType::aO89 = *repository.insert (new AO89 ((str = "O89"))).first;
//     AtomType::aO8A = *repository.insert (new AO8A ((str = "O8A"))).first;
//     AtomType::aO8B = *repository.insert (new AO8B ((str = "O8B"))).first;
//     AtomType::aO8C = *repository.insert (new AO8C ((str = "O8C"))).first;
//     AtomType::aO8D = *repository.insert (new AO8D ((str = "O8D"))).first;
//     AtomType::aO8F = *repository.insert (new AO8F ((str = "O8F"))).first;
//     AtomType::aO8G = *repository.insert (new AO8G ((str = "O8G"))).first;
//     AtomType::aO8H = *repository.insert (new AO8H ((str = "O8H"))).first;
//     AtomType::aO8J = *repository.insert (new AO8J ((str = "O8J"))).first;
//     AtomType::aO8L = *repository.insert (new AO8L ((str = "O8L"))).first;
//     AtomType::aO8M = *repository.insert (new AO8M ((str = "O8M"))).first;
//     AtomType::aO8N = *repository.insert (new AO8N ((str = "O8N"))).first;
//     AtomType::aO8P = *repository.insert (new AO8P ((str = "O8P"))).first;
//     AtomType::aO8Q = *repository.insert (new AO8Q ((str = "O8Q"))).first;
//     AtomType::aO8R = *repository.insert (new AO8R ((str = "O8R"))).first;
//     AtomType::aO8S = *repository.insert (new AO8S ((str = "O8S"))).first;
//     AtomType::aO9 = *repository.insert (new AO9 ((str = "O9"))).first;
//     AtomType::aO9" = *repository.insert (new AO9" ((str = "O9""))).first;
//     AtomType::aO9* = *repository.insert (new AO9* ((str = "O9*"))).first;
//     AtomType::aO90 = *repository.insert (new AO90 ((str = "O90"))).first;
//     AtomType::aO91 = *repository.insert (new AO91 ((str = "O91"))).first;
//     AtomType::aO91A = *repository.insert (new AO91A ((str = "O91A"))).first;
//     AtomType::aO92 = *repository.insert (new AO92 ((str = "O92"))).first;
//     AtomType::aO92A = *repository.insert (new AO92A ((str = "O92A"))).first;
//     AtomType::aO93 = *repository.insert (new AO93 ((str = "O93"))).first;
//     AtomType::aO94 = *repository.insert (new AO94 ((str = "O94"))).first;
//     AtomType::aO95 = *repository.insert (new AO95 ((str = "O95"))).first;
//     AtomType::aO96 = *repository.insert (new AO96 ((str = "O96"))).first;
//     AtomType::aO97 = *repository.insert (new AO97 ((str = "O97"))).first;
//     AtomType::aO98 = *repository.insert (new AO98 ((str = "O98"))).first;
//     AtomType::aO99 = *repository.insert (new AO99 ((str = "O99"))).first;
//     AtomType::aO9A = *repository.insert (new AO9A ((str = "O9A"))).first;
//     AtomType::aO9B = *repository.insert (new AO9B ((str = "O9B"))).first;
//     AtomType::aO9C = *repository.insert (new AO9C ((str = "O9C"))).first;
//     AtomType::aO9P = *repository.insert (new AO9P ((str = "O9P"))).first;
//     AtomType::aO9R = *repository.insert (new AO9R ((str = "O9R"))).first;
//     AtomType::aOA = *repository.insert (new AOA ((str = "OA"))).first;
//     AtomType::aOA1 = *repository.insert (new AOA1 ((str = "OA1"))).first;
//     AtomType::aOA2 = *repository.insert (new AOA2 ((str = "OA2"))).first;
//     AtomType::aOA3 = *repository.insert (new AOA3 ((str = "OA3"))).first;
//     AtomType::aOA4 = *repository.insert (new AOA4 ((str = "OA4"))).first;
//     AtomType::aOA5 = *repository.insert (new AOA5 ((str = "OA5"))).first;
//     AtomType::aOA6 = *repository.insert (new AOA6 ((str = "OA6"))).first;
//     AtomType::aOA7 = *repository.insert (new AOA7 ((str = "OA7"))).first;
//     AtomType::aOA8 = *repository.insert (new AOA8 ((str = "OA8"))).first;
//     AtomType::aOA9 = *repository.insert (new AOA9 ((str = "OA9"))).first;
//     AtomType::aOAA = *repository.insert (new AOAA ((str = "OAA"))).first;
//     AtomType::aOAB = *repository.insert (new AOAB ((str = "OAB"))).first;
//     AtomType::aOAC = *repository.insert (new AOAC ((str = "OAC"))).first;
//     AtomType::aOAD = *repository.insert (new AOAD ((str = "OAD"))).first;
//     AtomType::aOAE = *repository.insert (new AOAE ((str = "OAE"))).first;
//     AtomType::aOAF = *repository.insert (new AOAF ((str = "OAF"))).first;
//     AtomType::aOAG = *repository.insert (new AOAG ((str = "OAG"))).first;
//     AtomType::aOAH = *repository.insert (new AOAH ((str = "OAH"))).first;
//     AtomType::aOAI = *repository.insert (new AOAI ((str = "OAI"))).first;
//     AtomType::aOAJ = *repository.insert (new AOAJ ((str = "OAJ"))).first;
//     AtomType::aOAK = *repository.insert (new AOAK ((str = "OAK"))).first;
//     AtomType::aOAL = *repository.insert (new AOAL ((str = "OAL"))).first;
//     AtomType::aOAM = *repository.insert (new AOAM ((str = "OAM"))).first;
//     AtomType::aOAN = *repository.insert (new AOAN ((str = "OAN"))).first;
//     AtomType::aOAO = *repository.insert (new AOAO ((str = "OAO"))).first;
//     AtomType::aOAP = *repository.insert (new AOAP ((str = "OAP"))).first;
//     AtomType::aOAQ = *repository.insert (new AOAQ ((str = "OAQ"))).first;
//     AtomType::aOAR = *repository.insert (new AOAR ((str = "OAR"))).first;
//     AtomType::aOAS = *repository.insert (new AOAS ((str = "OAS"))).first;
//     AtomType::aOAT = *repository.insert (new AOAT ((str = "OAT"))).first;
//     AtomType::aOAU = *repository.insert (new AOAU ((str = "OAU"))).first;
//     AtomType::aOAV = *repository.insert (new AOAV ((str = "OAV"))).first;
//     AtomType::aOAW = *repository.insert (new AOAW ((str = "OAW"))).first;
//     AtomType::aOAX = *repository.insert (new AOAX ((str = "OAX"))).first;
//     AtomType::aOAY = *repository.insert (new AOAY ((str = "OAY"))).first;
//     AtomType::aOAZ = *repository.insert (new AOAZ ((str = "OAZ"))).first;
//     AtomType::aOB = *repository.insert (new AOB ((str = "OB"))).first;
//     AtomType::aOB* = *repository.insert (new AOB* ((str = "OB*"))).first;
//     AtomType::aOB1 = *repository.insert (new AOB1 ((str = "OB1"))).first;
//     AtomType::aOB2 = *repository.insert (new AOB2 ((str = "OB2"))).first;
//     AtomType::aOB3 = *repository.insert (new AOB3 ((str = "OB3"))).first;
//     AtomType::aOB4 = *repository.insert (new AOB4 ((str = "OB4"))).first;
//     AtomType::aOB5 = *repository.insert (new AOB5 ((str = "OB5"))).first;
//     AtomType::aOB6 = *repository.insert (new AOB6 ((str = "OB6"))).first;
//     AtomType::aOB7 = *repository.insert (new AOB7 ((str = "OB7"))).first;
//     AtomType::aOB8 = *repository.insert (new AOB8 ((str = "OB8"))).first;
//     AtomType::aOB9 = *repository.insert (new AOB9 ((str = "OB9"))).first;
//     AtomType::aOBA = *repository.insert (new AOBA ((str = "OBA"))).first;
//     AtomType::aOBB = *repository.insert (new AOBB ((str = "OBB"))).first;
//     AtomType::aOBC = *repository.insert (new AOBC ((str = "OBC"))).first;
//     AtomType::aOBD = *repository.insert (new AOBD ((str = "OBD"))).first;
//     AtomType::aOBE = *repository.insert (new AOBE ((str = "OBE"))).first;
//     AtomType::aOBF = *repository.insert (new AOBF ((str = "OBF"))).first;
//     AtomType::aOBG = *repository.insert (new AOBG ((str = "OBG"))).first;
//     AtomType::aOBH = *repository.insert (new AOBH ((str = "OBH"))).first;
//     AtomType::aOBI = *repository.insert (new AOBI ((str = "OBI"))).first;
//     AtomType::aOBJ = *repository.insert (new AOBJ ((str = "OBJ"))).first;
//     AtomType::aOBK = *repository.insert (new AOBK ((str = "OBK"))).first;
//     AtomType::aOBL = *repository.insert (new AOBL ((str = "OBL"))).first;
//     AtomType::aOBM = *repository.insert (new AOBM ((str = "OBM"))).first;
//     AtomType::aOBN = *repository.insert (new AOBN ((str = "OBN"))).first;
//     AtomType::aOBO = *repository.insert (new AOBO ((str = "OBO"))).first;
//     AtomType::aOBP = *repository.insert (new AOBP ((str = "OBP"))).first;
//     AtomType::aOBQ = *repository.insert (new AOBQ ((str = "OBQ"))).first;
//     AtomType::aOBR = *repository.insert (new AOBR ((str = "OBR"))).first;
//     AtomType::aOBS = *repository.insert (new AOBS ((str = "OBS"))).first;
//     AtomType::aOBT = *repository.insert (new AOBT ((str = "OBT"))).first;
//     AtomType::aOBU = *repository.insert (new AOBU ((str = "OBU"))).first;
//     AtomType::aOBV = *repository.insert (new AOBV ((str = "OBV"))).first;
//     AtomType::aOBY = *repository.insert (new AOBY ((str = "OBY"))).first;
//     AtomType::aOC = *repository.insert (new AOC ((str = "OC"))).first;
//     AtomType::aOC* = *repository.insert (new AOC* ((str = "OC*"))).first;
//     AtomType::aOC1 = *repository.insert (new AOC1 ((str = "OC1"))).first;
//     AtomType::aOC2 = *repository.insert (new AOC2 ((str = "OC2"))).first;
//     AtomType::aOC3 = *repository.insert (new AOC3 ((str = "OC3"))).first;
//     AtomType::aOC4 = *repository.insert (new AOC4 ((str = "OC4"))).first;
//     AtomType::aOC5 = *repository.insert (new AOC5 ((str = "OC5"))).first;
//     AtomType::aOC6 = *repository.insert (new AOC6 ((str = "OC6"))).first;
//     AtomType::aOC7 = *repository.insert (new AOC7 ((str = "OC7"))).first;
//     AtomType::aOC8 = *repository.insert (new AOC8 ((str = "OC8"))).first;
//     AtomType::aOC9 = *repository.insert (new AOC9 ((str = "OC9"))).first;
//     AtomType::aOCA = *repository.insert (new AOCA ((str = "OCA"))).first;
//     AtomType::aOCB = *repository.insert (new AOCB ((str = "OCB"))).first;
//     AtomType::aOCC = *repository.insert (new AOCC ((str = "OCC"))).first;
//     AtomType::aOCD = *repository.insert (new AOCD ((str = "OCD"))).first;
//     AtomType::aOCE = *repository.insert (new AOCE ((str = "OCE"))).first;
//     AtomType::aOCF = *repository.insert (new AOCF ((str = "OCF"))).first;
//     AtomType::aOCG = *repository.insert (new AOCG ((str = "OCG"))).first;
//     AtomType::aOCH = *repository.insert (new AOCH ((str = "OCH"))).first;
//     AtomType::aOCJ = *repository.insert (new AOCJ ((str = "OCJ"))).first;
//     AtomType::aOCK = *repository.insert (new AOCK ((str = "OCK"))).first;
//     AtomType::aOCM = *repository.insert (new AOCM ((str = "OCM"))).first;
//     AtomType::aOCN = *repository.insert (new AOCN ((str = "OCN"))).first;
//     AtomType::aOCP = *repository.insert (new AOCP ((str = "OCP"))).first;
//     AtomType::aOCQ = *repository.insert (new AOCQ ((str = "OCQ"))).first;
//     AtomType::aOCR = *repository.insert (new AOCR ((str = "OCR"))).first;
//     AtomType::aOCS = *repository.insert (new AOCS ((str = "OCS"))).first;
//     AtomType::aOCT = *repository.insert (new AOCT ((str = "OCT"))).first;
//     AtomType::aOCV = *repository.insert (new AOCV ((str = "OCV"))).first;
//     AtomType::aOCW = *repository.insert (new AOCW ((str = "OCW"))).first;
//     AtomType::aOCX = *repository.insert (new AOCX ((str = "OCX"))).first;
//     AtomType::aOCY = *repository.insert (new AOCY ((str = "OCY"))).first;
//     AtomType::aOCZ = *repository.insert (new AOCZ ((str = "OCZ"))).first;
//     AtomType::aOD = *repository.insert (new AOD ((str = "OD"))).first;
//     AtomType::aOD* = *repository.insert (new AOD* ((str = "OD*"))).first;
//     AtomType::aOD1 = *repository.insert (new AOD1 ((str = "OD1"))).first;
//     AtomType::aOD2 = *repository.insert (new AOD2 ((str = "OD2"))).first;
//     AtomType::aOD3 = *repository.insert (new AOD3 ((str = "OD3"))).first;
//     AtomType::aOD4 = *repository.insert (new AOD4 ((str = "OD4"))).first;
//     AtomType::aOD5 = *repository.insert (new AOD5 ((str = "OD5"))).first;
//     AtomType::aOD6 = *repository.insert (new AOD6 ((str = "OD6"))).first;
//     AtomType::aOD7 = *repository.insert (new AOD7 ((str = "OD7"))).first;
//     AtomType::aODA = *repository.insert (new AODA ((str = "ODA"))).first;
//     AtomType::aODB = *repository.insert (new AODB ((str = "ODB"))).first;
//     AtomType::aODC = *repository.insert (new AODC ((str = "ODC"))).first;
//     AtomType::aODD = *repository.insert (new AODD ((str = "ODD"))).first;
//     AtomType::aODE = *repository.insert (new AODE ((str = "ODE"))).first;
//     AtomType::aODF = *repository.insert (new AODF ((str = "ODF"))).first;
//     AtomType::aODI = *repository.insert (new AODI ((str = "ODI"))).first;
//     AtomType::aODL = *repository.insert (new AODL ((str = "ODL"))).first;
//     AtomType::aODM = *repository.insert (new AODM ((str = "ODM"))).first;
//     AtomType::aODO = *repository.insert (new AODO ((str = "ODO"))).first;
//     AtomType::aODR = *repository.insert (new AODR ((str = "ODR"))).first;
//     AtomType::aOE = *repository.insert (new AOE ((str = "OE"))).first;
//     AtomType::aOE* = *repository.insert (new AOE* ((str = "OE*"))).first;
//     AtomType::aOE1 = *repository.insert (new AOE1 ((str = "OE1"))).first;
//     AtomType::aOE11 = *repository.insert (new AOE11 ((str = "OE11"))).first;
//     AtomType::aOE12 = *repository.insert (new AOE12 ((str = "OE12"))).first;
//     AtomType::aOE13 = *repository.insert (new AOE13 ((str = "OE13"))).first;
//     AtomType::aOE2 = *repository.insert (new AOE2 ((str = "OE2"))).first;
//     AtomType::aOE23 = *repository.insert (new AOE23 ((str = "OE23"))).first;
//     AtomType::aOE3 = *repository.insert (new AOE3 ((str = "OE3"))).first;
//     AtomType::aOE4 = *repository.insert (new AOE4 ((str = "OE4"))).first;
//     AtomType::aOE5 = *repository.insert (new AOE5 ((str = "OE5"))).first;
//     AtomType::aOE6 = *repository.insert (new AOE6 ((str = "OE6"))).first;
//     AtomType::aOE7 = *repository.insert (new AOE7 ((str = "OE7"))).first;
//     AtomType::aOE8 = *repository.insert (new AOE8 ((str = "OE8"))).first;
//     AtomType::aOEA = *repository.insert (new AOEA ((str = "OEA"))).first;
//     AtomType::aOEB = *repository.insert (new AOEB ((str = "OEB"))).first;
//     AtomType::aOEM = *repository.insert (new AOEM ((str = "OEM"))).first;
//     AtomType::aOET = *repository.insert (new AOET ((str = "OET"))).first;
//     AtomType::aOEZ = *repository.insert (new AOEZ ((str = "OEZ"))).first;
//     AtomType::aOF = *repository.insert (new AOF ((str = "OF"))).first;
//     AtomType::aOF* = *repository.insert (new AOF* ((str = "OF*"))).first;
//     AtomType::aOF1 = *repository.insert (new AOF1 ((str = "OF1"))).first;
//     AtomType::aOF2 = *repository.insert (new AOF2 ((str = "OF2"))).first;
//     AtomType::aOF3 = *repository.insert (new AOF3 ((str = "OF3"))).first;
//     AtomType::aOG = *repository.insert (new AOG ((str = "OG"))).first;
//     AtomType::aOG* = *repository.insert (new AOG* ((str = "OG*"))).first;
//     AtomType::aOG1 = *repository.insert (new AOG1 ((str = "OG1"))).first;
//     AtomType::aOG2 = *repository.insert (new AOG2 ((str = "OG2"))).first;
//     AtomType::aOG3 = *repository.insert (new AOG3 ((str = "OG3"))).first;
//     AtomType::aOG4 = *repository.insert (new AOG4 ((str = "OG4"))).first;
//     AtomType::aOG5 = *repository.insert (new AOG5 ((str = "OG5"))).first;
//     AtomType::aOG6 = *repository.insert (new AOG6 ((str = "OG6"))).first;
//     AtomType::aOGL = *repository.insert (new AOGL ((str = "OGL"))).first;
//     AtomType::aOGS = *repository.insert (new AOGS ((str = "OGS"))).first;
//     AtomType::aOGT = *repository.insert (new AOGT ((str = "OGT"))).first;
//     AtomType::aOH = *repository.insert (new AOH ((str = "OH"))).first;
//     AtomType::aOH*A = *repository.insert (new AOH*A ((str = "OH*A"))).first;
//     AtomType::aOH1 = *repository.insert (new AOH1 ((str = "OH1"))).first;
//     AtomType::aOH10 = *repository.insert (new AOH10 ((str = "OH10"))).first;
//     AtomType::aOH11 = *repository.insert (new AOH11 ((str = "OH11"))).first;
//     AtomType::aOH12 = *repository.insert (new AOH12 ((str = "OH12"))).first;
//     AtomType::aOH13 = *repository.insert (new AOH13 ((str = "OH13"))).first;
//     AtomType::aOH14 = *repository.insert (new AOH14 ((str = "OH14"))).first;
//     AtomType::aOH15 = *repository.insert (new AOH15 ((str = "OH15"))).first;
//     AtomType::aOH17 = *repository.insert (new AOH17 ((str = "OH17"))).first;
//     AtomType::aOH18 = *repository.insert (new AOH18 ((str = "OH18"))).first;
//     AtomType::aOH19 = *repository.insert (new AOH19 ((str = "OH19"))).first;
//     AtomType::aOH1A = *repository.insert (new AOH1A ((str = "OH1A"))).first;
//     AtomType::aOH1B = *repository.insert (new AOH1B ((str = "OH1B"))).first;
//     AtomType::aOH1C = *repository.insert (new AOH1C ((str = "OH1C"))).first;
//     AtomType::aOH1P = *repository.insert (new AOH1P ((str = "OH1P"))).first;
//     AtomType::aOH2 = *repository.insert (new AOH2 ((str = "OH2"))).first;
//     AtomType::aOH2* = *repository.insert (new AOH2* ((str = "OH2*"))).first;
//     AtomType::aOH22 = *repository.insert (new AOH22 ((str = "OH22"))).first;
//     AtomType::aOH23 = *repository.insert (new AOH23 ((str = "OH23"))).first;
//     AtomType::aOH27 = *repository.insert (new AOH27 ((str = "OH27"))).first;
//     AtomType::aOH2A = *repository.insert (new AOH2A ((str = "OH2A"))).first;
//     AtomType::aOH2B = *repository.insert (new AOH2B ((str = "OH2B"))).first;
//     AtomType::aOH2C = *repository.insert (new AOH2C ((str = "OH2C"))).first;
//     AtomType::aOH2P = *repository.insert (new AOH2P ((str = "OH2P"))).first;
//     AtomType::aOH2R = *repository.insert (new AOH2R ((str = "OH2R"))).first;
//     AtomType::aOH2S = *repository.insert (new AOH2S ((str = "OH2S"))).first;
//     AtomType::aOH2X = *repository.insert (new AOH2X ((str = "OH2X"))).first;
//     AtomType::aOH3 = *repository.insert (new AOH3 ((str = "OH3"))).first;
//     AtomType::aOH3* = *repository.insert (new AOH3* ((str = "OH3*"))).first;
//     AtomType::aOH3, = *repository.insert (new AOH3, ((str = "OH3,"))).first;
//     AtomType::aOH32 = *repository.insert (new AOH32 ((str = "OH32"))).first;
//     AtomType::aOH3A = *repository.insert (new AOH3A ((str = "OH3A"))).first;
//     AtomType::aOH3B = *repository.insert (new AOH3B ((str = "OH3B"))).first;
//     AtomType::aOH3N = *repository.insert (new AOH3N ((str = "OH3N"))).first;
//     AtomType::aOH3P = *repository.insert (new AOH3P ((str = "OH3P"))).first;
//     AtomType::aOH3R = *repository.insert (new AOH3R ((str = "OH3R"))).first;
//     AtomType::aOH4 = *repository.insert (new AOH4 ((str = "OH4"))).first;
//     AtomType::aOH4* = *repository.insert (new AOH4* ((str = "OH4*"))).first;
//     AtomType::aOH40 = *repository.insert (new AOH40 ((str = "OH40"))).first;
//     AtomType::aOH41 = *repository.insert (new AOH41 ((str = "OH41"))).first;
//     AtomType::aOH43 = *repository.insert (new AOH43 ((str = "OH43"))).first;
//     AtomType::aOH4A = *repository.insert (new AOH4A ((str = "OH4A"))).first;
//     AtomType::aOH4P = *repository.insert (new AOH4P ((str = "OH4P"))).first;
//     AtomType::aOH5 = *repository.insert (new AOH5 ((str = "OH5"))).first;
//     AtomType::aOH52 = *repository.insert (new AOH52 ((str = "OH52"))).first;
//     AtomType::aOH6 = *repository.insert (new AOH6 ((str = "OH6"))).first;
//     AtomType::aOH62 = *repository.insert (new AOH62 ((str = "OH62"))).first;
//     AtomType::aOH63 = *repository.insert (new AOH63 ((str = "OH63"))).first;
//     AtomType::aOH6A = *repository.insert (new AOH6A ((str = "OH6A"))).first;
//     AtomType::aOH6S = *repository.insert (new AOH6S ((str = "OH6S"))).first;
//     AtomType::aOH7 = *repository.insert (new AOH7 ((str = "OH7"))).first;
//     AtomType::aOH7A = *repository.insert (new AOH7A ((str = "OH7A"))).first;
//     AtomType::aOH7N = *repository.insert (new AOH7N ((str = "OH7N"))).first;
//     AtomType::aOH8 = *repository.insert (new AOH8 ((str = "OH8"))).first;
//     AtomType::aOH8A = *repository.insert (new AOH8A ((str = "OH8A"))).first;
//     AtomType::aOH9* = *repository.insert (new AOH9* ((str = "OH9*"))).first;
//     AtomType::aOH92 = *repository.insert (new AOH92 ((str = "OH92"))).first;
//     AtomType::aOHA1 = *repository.insert (new AOHA1 ((str = "OHA1"))).first;
//     AtomType::aOHA3 = *repository.insert (new AOHA3 ((str = "OHA3"))).first;
//     AtomType::aOHA7 = *repository.insert (new AOHA7 ((str = "OHA7"))).first;
//     AtomType::aOHB = *repository.insert (new AOHB ((str = "OHB"))).first;
//     AtomType::aOHB1 = *repository.insert (new AOHB1 ((str = "OHB1"))).first;
//     AtomType::aOHB2 = *repository.insert (new AOHB2 ((str = "OHB2"))).first;
//     AtomType::aOHB7 = *repository.insert (new AOHB7 ((str = "OHB7"))).first;
//     AtomType::aOHC2 = *repository.insert (new AOHC2 ((str = "OHC2"))).first;
//     AtomType::aOHD = *repository.insert (new AOHD ((str = "OHD"))).first;
//     AtomType::aOHD1 = *repository.insert (new AOHD1 ((str = "OHD1"))).first;
//     AtomType::aOHE2 = *repository.insert (new AOHE2 ((str = "OHE2"))).first;
//     AtomType::aOHG1 = *repository.insert (new AOHG1 ((str = "OHG1"))).first;
//     AtomType::aOHG2 = *repository.insert (new AOHG2 ((str = "OHG2"))).first;
//     AtomType::aOHN = *repository.insert (new AOHN ((str = "OHN"))).first;
//     AtomType::aOHP1 = *repository.insert (new AOHP1 ((str = "OHP1"))).first;
//     AtomType::aOHP3 = *repository.insert (new AOHP3 ((str = "OHP3"))).first;
//     AtomType::aOHP4 = *repository.insert (new AOHP4 ((str = "OHP4"))).first;
//     AtomType::aOHPA = *repository.insert (new AOHPA ((str = "OHPA"))).first;
//     AtomType::aOHPN = *repository.insert (new AOHPN ((str = "OHPN"))).first;
//     AtomType::aOHT1 = *repository.insert (new AOHT1 ((str = "OHT1"))).first;
//     AtomType::aOI = *repository.insert (new AOI ((str = "OI"))).first;
//     AtomType::aOI* = *repository.insert (new AOI* ((str = "OI*"))).first;
//     AtomType::aOI1 = *repository.insert (new AOI1 ((str = "OI1"))).first;
//     AtomType::aOI2 = *repository.insert (new AOI2 ((str = "OI2"))).first;
//     AtomType::aOI3 = *repository.insert (new AOI3 ((str = "OI3"))).first;
//     AtomType::aOI4 = *repository.insert (new AOI4 ((str = "OI4"))).first;
//     AtomType::aOI5 = *repository.insert (new AOI5 ((str = "OI5"))).first;
//     AtomType::aOI6 = *repository.insert (new AOI6 ((str = "OI6"))).first;
//     AtomType::aOJ1 = *repository.insert (new AOJ1 ((str = "OJ1"))).first;
//     AtomType::aOJ2 = *repository.insert (new AOJ2 ((str = "OJ2"))).first;
//     AtomType::aOJ3 = *repository.insert (new AOJ3 ((str = "OJ3"))).first;
//     AtomType::aOJ4 = *repository.insert (new AOJ4 ((str = "OJ4"))).first;
//     AtomType::aOJ5 = *repository.insert (new AOJ5 ((str = "OJ5"))).first;
//     AtomType::aOJ6 = *repository.insert (new AOJ6 ((str = "OJ6"))).first;
//     AtomType::aOK = *repository.insert (new AOK ((str = "OK"))).first;
//     AtomType::aOK1 = *repository.insert (new AOK1 ((str = "OK1"))).first;
//     AtomType::aOK2 = *repository.insert (new AOK2 ((str = "OK2"))).first;
//     AtomType::aOL = *repository.insert (new AOL ((str = "OL"))).first;
//     AtomType::aOL1 = *repository.insert (new AOL1 ((str = "OL1"))).first;
//     AtomType::aOL2 = *repository.insert (new AOL2 ((str = "OL2"))).first;
//     AtomType::aOL3 = *repository.insert (new AOL3 ((str = "OL3"))).first;
//     AtomType::aOL5 = *repository.insert (new AOL5 ((str = "OL5"))).first;
//     AtomType::aOM = *repository.insert (new AOM ((str = "OM"))).first;
//     AtomType::aOM1 = *repository.insert (new AOM1 ((str = "OM1"))).first;
//     AtomType::aOM2 = *repository.insert (new AOM2 ((str = "OM2"))).first;
//     AtomType::aOM3 = *repository.insert (new AOM3 ((str = "OM3"))).first;
//     AtomType::aOM4 = *repository.insert (new AOM4 ((str = "OM4"))).first;
//     AtomType::aOM6 = *repository.insert (new AOM6 ((str = "OM6"))).first;
//     AtomType::aOM7 = *repository.insert (new AOM7 ((str = "OM7"))).first;
//     AtomType::aOMA = *repository.insert (new AOMA ((str = "OMA"))).first;
//     AtomType::aOMB = *repository.insert (new AOMB ((str = "OMB"))).first;
//     AtomType::aOMC = *repository.insert (new AOMC ((str = "OMC"))).first;
//     AtomType::aOMD = *repository.insert (new AOMD ((str = "OMD"))).first;
//     AtomType::aON = *repository.insert (new AON ((str = "ON"))).first;
//     AtomType::aON1 = *repository.insert (new AON1 ((str = "ON1"))).first;
//     AtomType::aON2 = *repository.insert (new AON2 ((str = "ON2"))).first;
//     AtomType::aON3 = *repository.insert (new AON3 ((str = "ON3"))).first;
//     AtomType::aOND = *repository.insert (new AOND ((str = "OND"))).first;
//     AtomType::aOO = *repository.insert (new AOO ((str = "OO"))).first;
//     AtomType::aOP = *repository.insert (new AOP ((str = "OP"))).first;
//     AtomType::aOP1 = *repository.insert (new AOP1 ((str = "OP1"))).first;
//     AtomType::aOP2 = *repository.insert (new AOP2 ((str = "OP2"))).first;
//     AtomType::aOP3 = *repository.insert (new AOP3 ((str = "OP3"))).first;
//     AtomType::aOP4 = *repository.insert (new AOP4 ((str = "OP4"))).first;
//     AtomType::aOP5 = *repository.insert (new AOP5 ((str = "OP5"))).first;
//     AtomType::aOP6 = *repository.insert (new AOP6 ((str = "OP6"))).first;
//     AtomType::aOP7 = *repository.insert (new AOP7 ((str = "OP7"))).first;
//     AtomType::aOP8 = *repository.insert (new AOP8 ((str = "OP8"))).first;
//     AtomType::aOP9 = *repository.insert (new AOP9 ((str = "OP9"))).first;
//     AtomType::aOPA = *repository.insert (new AOPA ((str = "OPA"))).first;
//     AtomType::aOPA1 = *repository.insert (new AOPA1 ((str = "OPA1"))).first;
//     AtomType::aOPA2 = *repository.insert (new AOPA2 ((str = "OPA2"))).first;
//     AtomType::aOPA3 = *repository.insert (new AOPA3 ((str = "OPA3"))).first;
//     AtomType::aOPB = *repository.insert (new AOPB ((str = "OPB"))).first;
//     AtomType::aOPB1 = *repository.insert (new AOPB1 ((str = "OPB1"))).first;
//     AtomType::aOPB2 = *repository.insert (new AOPB2 ((str = "OPB2"))).first;
//     AtomType::aOPB3 = *repository.insert (new AOPB3 ((str = "OPB3"))).first;
//     AtomType::aOPC = *repository.insert (new AOPC ((str = "OPC"))).first;
//     AtomType::aOPC1 = *repository.insert (new AOPC1 ((str = "OPC1"))).first;
//     AtomType::aOPC2 = *repository.insert (new AOPC2 ((str = "OPC2"))).first;
//     AtomType::aOPC3 = *repository.insert (new AOPC3 ((str = "OPC3"))).first;
//     AtomType::aOPD = *repository.insert (new AOPD ((str = "OPD"))).first;
//     AtomType::aOPP = *repository.insert (new AOPP ((str = "OPP"))).first;
//     AtomType::aOPX = *repository.insert (new AOPX ((str = "OPX"))).first;
//     AtomType::aOQ = *repository.insert (new AOQ ((str = "OQ"))).first;
//     AtomType::aOQ1 = *repository.insert (new AOQ1 ((str = "OQ1"))).first;
//     AtomType::aOQ2 = *repository.insert (new AOQ2 ((str = "OQ2"))).first;
//     AtomType::aOQ3 = *repository.insert (new AOQ3 ((str = "OQ3"))).first;
//     AtomType::aOQ4 = *repository.insert (new AOQ4 ((str = "OQ4"))).first;
//     AtomType::aOQ5 = *repository.insert (new AOQ5 ((str = "OQ5"))).first;
//     AtomType::aOQ6 = *repository.insert (new AOQ6 ((str = "OQ6"))).first;
//     AtomType::aOQ7 = *repository.insert (new AOQ7 ((str = "OQ7"))).first;
//     AtomType::aOR = *repository.insert (new AOR ((str = "OR"))).first;
//     AtomType::aOR1 = *repository.insert (new AOR1 ((str = "OR1"))).first;
//     AtomType::aOR2 = *repository.insert (new AOR2 ((str = "OR2"))).first;
//     AtomType::aOR3 = *repository.insert (new AOR3 ((str = "OR3"))).first;
//     AtomType::aOR4 = *repository.insert (new AOR4 ((str = "OR4"))).first;
//     AtomType::aOR5 = *repository.insert (new AOR5 ((str = "OR5"))).first;
//     AtomType::aOR6 = *repository.insert (new AOR6 ((str = "OR6"))).first;
//     AtomType::aORA = *repository.insert (new AORA ((str = "ORA"))).first;
//     AtomType::aOS = *repository.insert (new AOS ((str = "OS"))).first;
//     AtomType::aOS1 = *repository.insert (new AOS1 ((str = "OS1"))).first;
//     AtomType::aOS2 = *repository.insert (new AOS2 ((str = "OS2"))).first;
//     AtomType::aOS3 = *repository.insert (new AOS3 ((str = "OS3"))).first;
//     AtomType::aOS4 = *repository.insert (new AOS4 ((str = "OS4"))).first;
//     AtomType::aOS5 = *repository.insert (new AOS5 ((str = "OS5"))).first;
//     AtomType::aOSA = *repository.insert (new AOSA ((str = "OSA"))).first;
//     AtomType::aOSB = *repository.insert (new AOSB ((str = "OSB"))).first;
//     AtomType::aOSC = *repository.insert (new AOSC ((str = "OSC"))).first;
//     AtomType::aOT = *repository.insert (new AOT ((str = "OT"))).first;
//     AtomType::aOT" = *repository.insert (new AOT" ((str = "OT""))).first;
//     AtomType::aOT1 = *repository.insert (new AOT1 ((str = "OT1"))).first;
//     AtomType::aOT2 = *repository.insert (new AOT2 ((str = "OT2"))).first;
//     AtomType::aOT3 = *repository.insert (new AOT3 ((str = "OT3"))).first;
//     AtomType::aOT4 = *repository.insert (new AOT4 ((str = "OT4"))).first;
//     AtomType::aOT7 = *repository.insert (new AOT7 ((str = "OT7"))).first;
//     AtomType::aOTP = *repository.insert (new AOTP ((str = "OTP"))).first;
//     AtomType::aOTT = *repository.insert (new AOTT ((str = "OTT"))).first;
//     AtomType::aOU = *repository.insert (new AOU ((str = "OU"))).first;
//     AtomType::aOU2 = *repository.insert (new AOU2 ((str = "OU2"))).first;
//     AtomType::aOV = *repository.insert (new AOV ((str = "OV"))).first;
//     AtomType::aOV1 = *repository.insert (new AOV1 ((str = "OV1"))).first;
//     AtomType::aOV2 = *repository.insert (new AOV2 ((str = "OV2"))).first;
//     AtomType::aOV3 = *repository.insert (new AOV3 ((str = "OV3"))).first;
//     AtomType::aOV4 = *repository.insert (new AOV4 ((str = "OV4"))).first;
//     AtomType::aOV5 = *repository.insert (new AOV5 ((str = "OV5"))).first;
//     AtomType::aOV6 = *repository.insert (new AOV6 ((str = "OV6"))).first;
//     AtomType::aOW = *repository.insert (new AOW ((str = "OW"))).first;
//     AtomType::aOW1 = *repository.insert (new AOW1 ((str = "OW1"))).first;
//     AtomType::aOW2 = *repository.insert (new AOW2 ((str = "OW2"))).first;
//     AtomType::aOW3 = *repository.insert (new AOW3 ((str = "OW3"))).first;
//     AtomType::aOW4 = *repository.insert (new AOW4 ((str = "OW4"))).first;
//     AtomType::aOW5 = *repository.insert (new AOW5 ((str = "OW5"))).first;
//     AtomType::aOW6 = *repository.insert (new AOW6 ((str = "OW6"))).first;
//     AtomType::aOX = *repository.insert (new AOX ((str = "OX"))).first;
//     AtomType::aOX1 = *repository.insert (new AOX1 ((str = "OX1"))).first;
//     AtomType::aOX2 = *repository.insert (new AOX2 ((str = "OX2"))).first;
//     AtomType::aOX3 = *repository.insert (new AOX3 ((str = "OX3"))).first;
//     AtomType::aOX4 = *repository.insert (new AOX4 ((str = "OX4"))).first;
//     AtomType::aOX5 = *repository.insert (new AOX5 ((str = "OX5"))).first;
//     AtomType::aOX6 = *repository.insert (new AOX6 ((str = "OX6"))).first;
//     AtomType::aOX7 = *repository.insert (new AOX7 ((str = "OX7"))).first;
//     AtomType::aOX8 = *repository.insert (new AOX8 ((str = "OX8"))).first;
//     AtomType::aOXA = *repository.insert (new AOXA ((str = "OXA"))).first;
//     AtomType::aOXB = *repository.insert (new AOXB ((str = "OXB"))).first;
//     AtomType::aOXC = *repository.insert (new AOXC ((str = "OXC"))).first;
//     AtomType::aOXD = *repository.insert (new AOXD ((str = "OXD"))).first;
//     AtomType::aOXH = *repository.insert (new AOXH ((str = "OXH"))).first;
//     AtomType::aOXT = *repository.insert (new AOXT ((str = "OXT"))).first;
//     AtomType::aOY = *repository.insert (new AOY ((str = "OY"))).first;
//     AtomType::aOY2 = *repository.insert (new AOY2 ((str = "OY2"))).first;
//     AtomType::aOY3 = *repository.insert (new AOY3 ((str = "OY3"))).first;
//     AtomType::aOY4 = *repository.insert (new AOY4 ((str = "OY4"))).first;
//     AtomType::aOY5 = *repository.insert (new AOY5 ((str = "OY5"))).first;
//     AtomType::aOY7 = *repository.insert (new AOY7 ((str = "OY7"))).first;
//     AtomType::aOYH = *repository.insert (new AOYH ((str = "OYH"))).first;
//     AtomType::aOZ = *repository.insert (new AOZ ((str = "OZ"))).first;
//     AtomType::aOZ1 = *repository.insert (new AOZ1 ((str = "OZ1"))).first;
//     AtomType::aOZ2 = *repository.insert (new AOZ2 ((str = "OZ2"))).first;
//     AtomType::aOZ3 = *repository.insert (new AOZ3 ((str = "OZ3"))).first;
//     AtomType::aOZ4 = *repository.insert (new AOZ4 ((str = "OZ4"))).first;
//     AtomType::aOZ5 = *repository.insert (new AOZ5 ((str = "OZ5"))).first;
//     AtomType::aOZA = *repository.insert (new AOZA ((str = "OZA"))).first;
//     AtomType::aO_1 = *repository.insert (new AO_1 ((str = "O_1"))).first;
//     AtomType::aP = *repository.insert (new AP ((str = "P"))).first;
//     AtomType::aP* = *repository.insert (new AP* ((str = "P*"))).first;
//     AtomType::aP1 = *repository.insert (new AP1 ((str = "P1"))).first;
//     AtomType::aP10 = *repository.insert (new AP10 ((str = "P10"))).first;
//     AtomType::aP11 = *repository.insert (new AP11 ((str = "P11"))).first;
//     AtomType::aP12 = *repository.insert (new AP12 ((str = "P12"))).first;
//     AtomType::aP13 = *repository.insert (new AP13 ((str = "P13"))).first;
//     AtomType::aP14 = *repository.insert (new AP14 ((str = "P14"))).first;
//     AtomType::aP15 = *repository.insert (new AP15 ((str = "P15"))).first;
//     AtomType::aP16 = *repository.insert (new AP16 ((str = "P16"))).first;
//     AtomType::aP17 = *repository.insert (new AP17 ((str = "P17"))).first;
//     AtomType::aP18 = *repository.insert (new AP18 ((str = "P18"))).first;
//     AtomType::aP19 = *repository.insert (new AP19 ((str = "P19"))).first;
//     AtomType::aP1A = *repository.insert (new AP1A ((str = "P1A"))).first;
//     AtomType::aP2 = *repository.insert (new AP2 ((str = "P2"))).first;
//     AtomType::aP2* = *repository.insert (new AP2* ((str = "P2*"))).first;
//     AtomType::aP20 = *repository.insert (new AP20 ((str = "P20"))).first;
//     AtomType::aP21 = *repository.insert (new AP21 ((str = "P21"))).first;
//     AtomType::aP23 = *repository.insert (new AP23 ((str = "P23"))).first;
//     AtomType::aP24 = *repository.insert (new AP24 ((str = "P24"))).first;
//     AtomType::aP25 = *repository.insert (new AP25 ((str = "P25"))).first;
//     AtomType::aP26 = *repository.insert (new AP26 ((str = "P26"))).first;
//     AtomType::aP28 = *repository.insert (new AP28 ((str = "P28"))).first;
//     AtomType::aP29 = *repository.insert (new AP29 ((str = "P29"))).first;
//     AtomType::aP2A = *repository.insert (new AP2A ((str = "P2A"))).first;
//     AtomType::aP3 = *repository.insert (new AP3 ((str = "P3"))).first;
//     AtomType::aP3* = *repository.insert (new AP3* ((str = "P3*"))).first;
//     AtomType::aP3*A = *repository.insert (new AP3*A ((str = "P3*A"))).first;
//     AtomType::aP31 = *repository.insert (new AP31 ((str = "P31"))).first;
//     AtomType::aP32 = *repository.insert (new AP32 ((str = "P32"))).first;
//     AtomType::aP33 = *repository.insert (new AP33 ((str = "P33"))).first;
//     AtomType::aP34 = *repository.insert (new AP34 ((str = "P34"))).first;
//     AtomType::aP35 = *repository.insert (new AP35 ((str = "P35"))).first;
//     AtomType::aP39 = *repository.insert (new AP39 ((str = "P39"))).first;
//     AtomType::aP3X = *repository.insert (new AP3X ((str = "P3X"))).first;
//     AtomType::aP4 = *repository.insert (new AP4 ((str = "P4"))).first;
//     AtomType::aP40 = *repository.insert (new AP40 ((str = "P40"))).first;
//     AtomType::aP44 = *repository.insert (new AP44 ((str = "P44"))).first;
//     AtomType::aP46 = *repository.insert (new AP46 ((str = "P46"))).first;
//     AtomType::aP48 = *repository.insert (new AP48 ((str = "P48"))).first;
//     AtomType::aP4A = *repository.insert (new AP4A ((str = "P4A"))).first;
//     AtomType::aP4B = *repository.insert (new AP4B ((str = "P4B"))).first;
//     AtomType::aP5 = *repository.insert (new AP5 ((str = "P5"))).first;
//     AtomType::aP5* = *repository.insert (new AP5* ((str = "P5*"))).first;
//     AtomType::aP55 = *repository.insert (new AP55 ((str = "P55"))).first;
//     AtomType::aP6 = *repository.insert (new AP6 ((str = "P6"))).first;
//     AtomType::aP60 = *repository.insert (new AP60 ((str = "P60"))).first;
//     AtomType::aP68 = *repository.insert (new AP68 ((str = "P68"))).first;
//     AtomType::aP69 = *repository.insert (new AP69 ((str = "P69"))).first;
//     AtomType::aP7 = *repository.insert (new AP7 ((str = "P7"))).first;
//     AtomType::aP7" = *repository.insert (new AP7" ((str = "P7""))).first;
//     AtomType::aP7* = *repository.insert (new AP7* ((str = "P7*"))).first;
//     AtomType::aP71 = *repository.insert (new AP71 ((str = "P71"))).first;
//     AtomType::aP79 = *repository.insert (new AP79 ((str = "P79"))).first;
//     AtomType::aP8 = *repository.insert (new AP8 ((str = "P8"))).first;
//     AtomType::aP9 = *repository.insert (new AP9 ((str = "P9"))).first;
//     AtomType::aPA = *repository.insert (new APA ((str = "PA"))).first;
//     AtomType::aPA1 = *repository.insert (new APA1 ((str = "PA1"))).first;
//     AtomType::aPAE = *repository.insert (new APAE ((str = "PAE"))).first;
//     AtomType::aPAJ = *repository.insert (new APAJ ((str = "PAJ"))).first;
//     AtomType::aPAP = *repository.insert (new APAP ((str = "PAP"))).first;
//     AtomType::aPAQ = *repository.insert (new APAQ ((str = "PAQ"))).first;
//     AtomType::aPAR = *repository.insert (new APAR ((str = "PAR"))).first;
//     AtomType::aPAT = *repository.insert (new APAT ((str = "PAT"))).first;
//     AtomType::aPAU = *repository.insert (new APAU ((str = "PAU"))).first;
//     AtomType::aPAV = *repository.insert (new APAV ((str = "PAV"))).first;
//     AtomType::aPAX = *repository.insert (new APAX ((str = "PAX"))).first;
//     AtomType::aPAY = *repository.insert (new APAY ((str = "PAY"))).first;
//     AtomType::aPAZ = *repository.insert (new APAZ ((str = "PAZ"))).first;
//     AtomType::aPB = *repository.insert (new APB ((str = "PB"))).first;
//     AtomType::aPB2 = *repository.insert (new APB2 ((str = "PB2"))).first;
//     AtomType::aPBK = *repository.insert (new APBK ((str = "PBK"))).first;
//     AtomType::aPBM = *repository.insert (new APBM ((str = "PBM"))).first;
//     AtomType::aPBW = *repository.insert (new APBW ((str = "PBW"))).first;
//     AtomType::aPC = *repository.insert (new APC ((str = "PC"))).first;
//     AtomType::aPC1 = *repository.insert (new APC1 ((str = "PC1"))).first;
//     AtomType::aPC10 = *repository.insert (new APC10 ((str = "PC10"))).first;
//     AtomType::aPC11 = *repository.insert (new APC11 ((str = "PC11"))).first;
//     AtomType::aPC12 = *repository.insert (new APC12 ((str = "PC12"))).first;
//     AtomType::aPC13 = *repository.insert (new APC13 ((str = "PC13"))).first;
//     AtomType::aPC14 = *repository.insert (new APC14 ((str = "PC14"))).first;
//     AtomType::aPC2 = *repository.insert (new APC2 ((str = "PC2"))).first;
//     AtomType::aPC3 = *repository.insert (new APC3 ((str = "PC3"))).first;
//     AtomType::aPC5 = *repository.insert (new APC5 ((str = "PC5"))).first;
//     AtomType::aPC6 = *repository.insert (new APC6 ((str = "PC6"))).first;
//     AtomType::aPC7 = *repository.insert (new APC7 ((str = "PC7"))).first;
//     AtomType::aPC9 = *repository.insert (new APC9 ((str = "PC9"))).first;
//     AtomType::aPCB = *repository.insert (new APCB ((str = "PCB"))).first;
//     AtomType::aPCC = *repository.insert (new APCC ((str = "PCC"))).first;
//     AtomType::aPCD = *repository.insert (new APCD ((str = "PCD"))).first;
//     AtomType::aPCE = *repository.insert (new APCE ((str = "PCE"))).first;
//     AtomType::aPCF = *repository.insert (new APCF ((str = "PCF"))).first;
//     AtomType::aPCG = *repository.insert (new APCG ((str = "PCG"))).first;
//     AtomType::aPD = *repository.insert (new APD ((str = "PD"))).first;
//     AtomType::aPDP = *repository.insert (new APDP ((str = "PDP"))).first;
//     AtomType::aPE = *repository.insert (new APE ((str = "PE"))).first;
//     AtomType::aPF = *repository.insert (new APF ((str = "PF"))).first;
//     AtomType::aPG = *repository.insert (new APG ((str = "PG"))).first;
//     AtomType::aPHO1 = *repository.insert (new APHO1 ((str = "PHO1"))).first;
//     AtomType::aPHO2 = *repository.insert (new APHO2 ((str = "PHO2"))).first;
//     AtomType::aPHO3 = *repository.insert (new APHO3 ((str = "PHO3"))).first;
//     AtomType::aPHO4 = *repository.insert (new APHO4 ((str = "PHO4"))).first;
//     AtomType::aPHO5 = *repository.insert (new APHO5 ((str = "PHO5"))).first;
//     AtomType::aPHO6 = *repository.insert (new APHO6 ((str = "PHO6"))).first;
//     AtomType::aPHO7 = *repository.insert (new APHO7 ((str = "PHO7"))).first;
//     AtomType::aPHO8 = *repository.insert (new APHO8 ((str = "PHO8"))).first;
//     AtomType::aPHS* = *repository.insert (new APHS* ((str = "PHS*"))).first;
//     AtomType::aPM = *repository.insert (new APM ((str = "PM"))).first;
//     AtomType::aPN = *repository.insert (new APN ((str = "PN"))).first;
//     AtomType::aPN4 = *repository.insert (new APN4 ((str = "PN4"))).first;
//     AtomType::aPN8 = *repository.insert (new APN8 ((str = "PN8"))).first;
//     AtomType::aPO1 = *repository.insert (new APO1 ((str = "PO1"))).first;
//     AtomType::aPO10 = *repository.insert (new APO10 ((str = "PO10"))).first;
//     AtomType::aPO5 = *repository.insert (new APO5 ((str = "PO5"))).first;
//     AtomType::aPO9 = *repository.insert (new APO9 ((str = "PO9"))).first;
//     AtomType::aPS* = *repository.insert (new APS* ((str = "PS*"))).first;
//     AtomType::aPS1 = *repository.insert (new APS1 ((str = "PS1"))).first;
//     AtomType::aPT = *repository.insert (new APT ((str = "PT"))).first;
//     AtomType::aPT1 = *repository.insert (new APT1 ((str = "PT1"))).first;
//     AtomType::aPT2 = *repository.insert (new APT2 ((str = "PT2"))).first;
//     AtomType::aRC1* = *repository.insert (new ARC1* ((str = "RC1*"))).first;
//     AtomType::aRC2* = *repository.insert (new ARC2* ((str = "RC2*"))).first;
//     AtomType::aRC3* = *repository.insert (new ARC3* ((str = "RC3*"))).first;
//     AtomType::aRC4* = *repository.insert (new ARC4* ((str = "RC4*"))).first;
//     AtomType::aRC5* = *repository.insert (new ARC5* ((str = "RC5*"))).first;
//     AtomType::aRC6* = *repository.insert (new ARC6* ((str = "RC6*"))).first;
//     AtomType::aRC7* = *repository.insert (new ARC7* ((str = "RC7*"))).first;
//     AtomType::aRE = *repository.insert (new ARE ((str = "RE"))).first;
//     AtomType::aRH = *repository.insert (new ARH ((str = "RH"))).first;
//     AtomType::aRO1* = *repository.insert (new ARO1* ((str = "RO1*"))).first;
//     AtomType::aRO2* = *repository.insert (new ARO2* ((str = "RO2*"))).first;
//     AtomType::aRO3* = *repository.insert (new ARO3* ((str = "RO3*"))).first;
//     AtomType::aRO4* = *repository.insert (new ARO4* ((str = "RO4*"))).first;
//     AtomType::aRO5* = *repository.insert (new ARO5* ((str = "RO5*"))).first;
//     AtomType::aRO6* = *repository.insert (new ARO6* ((str = "RO6*"))).first;
//     AtomType::aRU = *repository.insert (new ARU ((str = "RU"))).first;
//     AtomType::aRU1 = *repository.insert (new ARU1 ((str = "RU1"))).first;
//     AtomType::aRU18 = *repository.insert (new ARU18 ((str = "RU18"))).first;
//     AtomType::aS = *repository.insert (new AS ((str = "S"))).first;
//     AtomType::aS* = *repository.insert (new AS* ((str = "S*"))).first;
//     AtomType::aS0 = *repository.insert (new AS0 ((str = "S0"))).first;
//     AtomType::aS01 = *repository.insert (new AS01 ((str = "S01"))).first;
//     AtomType::aS02 = *repository.insert (new AS02 ((str = "S02"))).first;
//     AtomType::aS03 = *repository.insert (new AS03 ((str = "S03"))).first;
//     AtomType::aS04 = *repository.insert (new AS04 ((str = "S04"))).first;
//     AtomType::aS07 = *repository.insert (new AS07 ((str = "S07"))).first;
//     AtomType::aS08 = *repository.insert (new AS08 ((str = "S08"))).first;
//     AtomType::aS1 = *repository.insert (new AS1 ((str = "S1"))).first;
//     AtomType::aS1* = *repository.insert (new AS1* ((str = "S1*"))).first;
//     AtomType::aS10 = *repository.insert (new AS10 ((str = "S10"))).first;
//     AtomType::aS11 = *repository.insert (new AS11 ((str = "S11"))).first;
//     AtomType::aS12 = *repository.insert (new AS12 ((str = "S12"))).first;
//     AtomType::aS13 = *repository.insert (new AS13 ((str = "S13"))).first;
//     AtomType::aS14 = *repository.insert (new AS14 ((str = "S14"))).first;
//     AtomType::aS15 = *repository.insert (new AS15 ((str = "S15"))).first;
//     AtomType::aS16 = *repository.insert (new AS16 ((str = "S16"))).first;
//     AtomType::aS17 = *repository.insert (new AS17 ((str = "S17"))).first;
//     AtomType::aS18 = *repository.insert (new AS18 ((str = "S18"))).first;
//     AtomType::aS19 = *repository.insert (new AS19 ((str = "S19"))).first;
//     AtomType::aS1A = *repository.insert (new AS1A ((str = "S1A"))).first;
//     AtomType::aS1B = *repository.insert (new AS1B ((str = "S1B"))).first;
//     AtomType::aS1C = *repository.insert (new AS1C ((str = "S1C"))).first;
//     AtomType::aS1D = *repository.insert (new AS1D ((str = "S1D"))).first;
//     AtomType::aS1G = *repository.insert (new AS1G ((str = "S1G"))).first;
//     AtomType::aS1P = *repository.insert (new AS1P ((str = "S1P"))).first;
//     AtomType::aS1T = *repository.insert (new AS1T ((str = "S1T"))).first;
//     AtomType::aS2 = *repository.insert (new AS2 ((str = "S2"))).first;
//     AtomType::aS2* = *repository.insert (new AS2* ((str = "S2*"))).first;
//     AtomType::aS20 = *repository.insert (new AS20 ((str = "S20"))).first;
//     AtomType::aS21 = *repository.insert (new AS21 ((str = "S21"))).first;
//     AtomType::aS22 = *repository.insert (new AS22 ((str = "S22"))).first;
//     AtomType::aS23 = *repository.insert (new AS23 ((str = "S23"))).first;
//     AtomType::aS24 = *repository.insert (new AS24 ((str = "S24"))).first;
//     AtomType::aS25 = *repository.insert (new AS25 ((str = "S25"))).first;
//     AtomType::aS26 = *repository.insert (new AS26 ((str = "S26"))).first;
//     AtomType::aS27 = *repository.insert (new AS27 ((str = "S27"))).first;
//     AtomType::aS28 = *repository.insert (new AS28 ((str = "S28"))).first;
//     AtomType::aS29 = *repository.insert (new AS29 ((str = "S29"))).first;
//     AtomType::aS2A = *repository.insert (new AS2A ((str = "S2A"))).first;
//     AtomType::aS2B = *repository.insert (new AS2B ((str = "S2B"))).first;
//     AtomType::aS2G = *repository.insert (new AS2G ((str = "S2G"))).first;
//     AtomType::aS2P = *repository.insert (new AS2P ((str = "S2P"))).first;
//     AtomType::aS3 = *repository.insert (new AS3 ((str = "S3"))).first;
//     AtomType::aS3* = *repository.insert (new AS3* ((str = "S3*"))).first;
//     AtomType::aS30 = *repository.insert (new AS30 ((str = "S30"))).first;
//     AtomType::aS31 = *repository.insert (new AS31 ((str = "S31"))).first;
//     AtomType::aS32 = *repository.insert (new AS32 ((str = "S32"))).first;
//     AtomType::aS33 = *repository.insert (new AS33 ((str = "S33"))).first;
//     AtomType::aS34 = *repository.insert (new AS34 ((str = "S34"))).first;
//     AtomType::aS35 = *repository.insert (new AS35 ((str = "S35"))).first;
//     AtomType::aS36 = *repository.insert (new AS36 ((str = "S36"))).first;
//     AtomType::aS37 = *repository.insert (new AS37 ((str = "S37"))).first;
//     AtomType::aS38 = *repository.insert (new AS38 ((str = "S38"))).first;
//     AtomType::aS39 = *repository.insert (new AS39 ((str = "S39"))).first;
//     AtomType::aS3A = *repository.insert (new AS3A ((str = "S3A"))).first;
//     AtomType::aS3B = *repository.insert (new AS3B ((str = "S3B"))).first;
//     AtomType::aS3G = *repository.insert (new AS3G ((str = "S3G"))).first;
//     AtomType::aS3H = *repository.insert (new AS3H ((str = "S3H"))).first;
//     AtomType::aS3P = *repository.insert (new AS3P ((str = "S3P"))).first;
//     AtomType::aS4 = *repository.insert (new AS4 ((str = "S4"))).first;
//     AtomType::aS4* = *repository.insert (new AS4* ((str = "S4*"))).first;
//     AtomType::aS40 = *repository.insert (new AS40 ((str = "S40"))).first;
//     AtomType::aS41 = *repository.insert (new AS41 ((str = "S41"))).first;
//     AtomType::aS42 = *repository.insert (new AS42 ((str = "S42"))).first;
//     AtomType::aS43 = *repository.insert (new AS43 ((str = "S43"))).first;
//     AtomType::aS44 = *repository.insert (new AS44 ((str = "S44"))).first;
//     AtomType::aS45 = *repository.insert (new AS45 ((str = "S45"))).first;
//     AtomType::aS46 = *repository.insert (new AS46 ((str = "S46"))).first;
//     AtomType::aS47 = *repository.insert (new AS47 ((str = "S47"))).first;
//     AtomType::aS48 = *repository.insert (new AS48 ((str = "S48"))).first;
//     AtomType::aS49 = *repository.insert (new AS49 ((str = "S49"))).first;
//     AtomType::aS4A = *repository.insert (new AS4A ((str = "S4A"))).first;
//     AtomType::aS4B = *repository.insert (new AS4B ((str = "S4B"))).first;
//     AtomType::aS4C = *repository.insert (new AS4C ((str = "S4C"))).first;
//     AtomType::aS5 = *repository.insert (new AS5 ((str = "S5"))).first;
//     AtomType::aS5* = *repository.insert (new AS5* ((str = "S5*"))).first;
//     AtomType::aS50 = *repository.insert (new AS50 ((str = "S50"))).first;
//     AtomType::aS51 = *repository.insert (new AS51 ((str = "S51"))).first;
//     AtomType::aS52 = *repository.insert (new AS52 ((str = "S52"))).first;
//     AtomType::aS53 = *repository.insert (new AS53 ((str = "S53"))).first;
//     AtomType::aS54 = *repository.insert (new AS54 ((str = "S54"))).first;
//     AtomType::aS55 = *repository.insert (new AS55 ((str = "S55"))).first;
//     AtomType::aS58 = *repository.insert (new AS58 ((str = "S58"))).first;
//     AtomType::aS5A = *repository.insert (new AS5A ((str = "S5A"))).first;
//     AtomType::aS5B = *repository.insert (new AS5B ((str = "S5B"))).first;
//     AtomType::aS5H = *repository.insert (new AS5H ((str = "S5H"))).first;
//     AtomType::aS6 = *repository.insert (new AS6 ((str = "S6"))).first;
//     AtomType::aS61 = *repository.insert (new AS61 ((str = "S61"))).first;
//     AtomType::aS66 = *repository.insert (new AS66 ((str = "S66"))).first;
//     AtomType::aS69 = *repository.insert (new AS69 ((str = "S69"))).first;
//     AtomType::aS7 = *repository.insert (new AS7 ((str = "S7"))).first;
//     AtomType::aS7* = *repository.insert (new AS7* ((str = "S7*"))).first;
//     AtomType::aS70 = *repository.insert (new AS70 ((str = "S70"))).first;
//     AtomType::aS73 = *repository.insert (new AS73 ((str = "S73"))).first;
//     AtomType::aS74 = *repository.insert (new AS74 ((str = "S74"))).first;
//     AtomType::aS75 = *repository.insert (new AS75 ((str = "S75"))).first;
//     AtomType::aS79 = *repository.insert (new AS79 ((str = "S79"))).first;
//     AtomType::aS7E = *repository.insert (new AS7E ((str = "S7E"))).first;
//     AtomType::aS8 = *repository.insert (new AS8 ((str = "S8"))).first;
//     AtomType::aS8* = *repository.insert (new AS8* ((str = "S8*"))).first;
//     AtomType::aS81 = *repository.insert (new AS81 ((str = "S81"))).first;
//     AtomType::aS83 = *repository.insert (new AS83 ((str = "S83"))).first;
//     AtomType::aS85 = *repository.insert (new AS85 ((str = "S85"))).first;
//     AtomType::aS86 = *repository.insert (new AS86 ((str = "S86"))).first;
//     AtomType::aS88 = *repository.insert (new AS88 ((str = "S88"))).first;
//     AtomType::aS8E = *repository.insert (new AS8E ((str = "S8E"))).first;
//     AtomType::aS8K = *repository.insert (new AS8K ((str = "S8K"))).first;
//     AtomType::aS9 = *repository.insert (new AS9 ((str = "S9"))).first;
//     AtomType::aS9B = *repository.insert (new AS9B ((str = "S9B"))).first;
//     AtomType::aSA = *repository.insert (new ASA ((str = "SA"))).first;
//     AtomType::aSAD = *repository.insert (new ASAD ((str = "SAD"))).first;
//     AtomType::aSAE = *repository.insert (new ASAE ((str = "SAE"))).first;
//     AtomType::aSAF = *repository.insert (new ASAF ((str = "SAF"))).first;
//     AtomType::aSAG = *repository.insert (new ASAG ((str = "SAG"))).first;
//     AtomType::aSAH = *repository.insert (new ASAH ((str = "SAH"))).first;
//     AtomType::aSAJ = *repository.insert (new ASAJ ((str = "SAJ"))).first;
//     AtomType::aSAM = *repository.insert (new ASAM ((str = "SAM"))).first;
//     AtomType::aSAN = *repository.insert (new ASAN ((str = "SAN"))).first;
//     AtomType::aSAO = *repository.insert (new ASAO ((str = "SAO"))).first;
//     AtomType::aSAP = *repository.insert (new ASAP ((str = "SAP"))).first;
//     AtomType::aSAQ = *repository.insert (new ASAQ ((str = "SAQ"))).first;
//     AtomType::aSAR = *repository.insert (new ASAR ((str = "SAR"))).first;
//     AtomType::aSAU = *repository.insert (new ASAU ((str = "SAU"))).first;
//     AtomType::aSAX = *repository.insert (new ASAX ((str = "SAX"))).first;
//     AtomType::aSAY = *repository.insert (new ASAY ((str = "SAY"))).first;
//     AtomType::aSB = *repository.insert (new ASB ((str = "SB"))).first;
//     AtomType::aSB2 = *repository.insert (new ASB2 ((str = "SB2"))).first;
//     AtomType::aSBB = *repository.insert (new ASBB ((str = "SBB"))).first;
//     AtomType::aSBC = *repository.insert (new ASBC ((str = "SBC"))).first;
//     AtomType::aSBD = *repository.insert (new ASBD ((str = "SBD"))).first;
//     AtomType::aSBE = *repository.insert (new ASBE ((str = "SBE"))).first;
//     AtomType::aSBH = *repository.insert (new ASBH ((str = "SBH"))).first;
//     AtomType::aSBI = *repository.insert (new ASBI ((str = "SBI"))).first;
//     AtomType::aSC = *repository.insert (new ASC ((str = "SC"))).first;
//     AtomType::aSCC = *repository.insert (new ASCC ((str = "SCC"))).first;
//     AtomType::aSD = *repository.insert (new ASD ((str = "SD"))).first;
//     AtomType::aSD1 = *repository.insert (new ASD1 ((str = "SD1"))).first;
//     AtomType::aSDD = *repository.insert (new ASDD ((str = "SDD"))).first;
//     AtomType::aSDE = *repository.insert (new ASDE ((str = "SDE"))).first;
//     AtomType::aSDF = *repository.insert (new ASDF ((str = "SDF"))).first;
//     AtomType::aSDM = *repository.insert (new ASDM ((str = "SDM"))).first;
//     AtomType::aSE = *repository.insert (new ASE ((str = "SE"))).first;
//     AtomType::aSE1 = *repository.insert (new ASE1 ((str = "SE1"))).first;
//     AtomType::aSE2 = *repository.insert (new ASE2 ((str = "SE2"))).first;
//     AtomType::aSE2* = *repository.insert (new ASE2* ((str = "SE2*"))).first;
//     AtomType::aSE3 = *repository.insert (new ASE3 ((str = "SE3"))).first;
//     AtomType::aSE4 = *repository.insert (new ASE4 ((str = "SE4"))).first;
//     AtomType::aSEG = *repository.insert (new ASEG ((str = "SEG"))).first;
//     AtomType::aSEL = *repository.insert (new ASEL ((str = "SEL"))).first;
//     AtomType::aSG = *repository.insert (new ASG ((str = "SG"))).first;
//     AtomType::aSG* = *repository.insert (new ASG* ((str = "SG*"))).first;
//     AtomType::aSG1 = *repository.insert (new ASG1 ((str = "SG1"))).first;
//     AtomType::aSG2 = *repository.insert (new ASG2 ((str = "SG2"))).first;
//     AtomType::aSG5 = *repository.insert (new ASG5 ((str = "SG5"))).first;
//     AtomType::aSG6 = *repository.insert (new ASG6 ((str = "SG6"))).first;
//     AtomType::aSHO2 = *repository.insert (new ASHO2 ((str = "SHO2"))).first;
//     AtomType::aSHOG = *repository.insert (new ASHOG ((str = "SHOG"))).first;
//     AtomType::aSI = *repository.insert (new ASI ((str = "SI"))).first;
//     AtomType::aSI1 = *repository.insert (new ASI1 ((str = "SI1"))).first;
//     AtomType::aSI4 = *repository.insert (new ASI4 ((str = "SI4"))).first;
//     AtomType::aSI70 = *repository.insert (new ASI70 ((str = "SI70"))).first;
//     AtomType::aSK = *repository.insert (new ASK ((str = "SK"))).first;
//     AtomType::aSM1 = *repository.insert (new ASM1 ((str = "SM1"))).first;
//     AtomType::aSNN = *repository.insert (new ASNN ((str = "SNN"))).first;
//     AtomType::aSP = *repository.insert (new ASP ((str = "SP"))).first;
//     AtomType::aSR = *repository.insert (new ASR ((str = "SR"))).first;
//     AtomType::aSS = *repository.insert (new ASS ((str = "SS"))).first;
//     AtomType::aSUL = *repository.insert (new ASUL ((str = "SUL"))).first;
//     AtomType::aSW = *repository.insert (new ASW ((str = "SW"))).first;
//     AtomType::aSX1 = *repository.insert (new ASX1 ((str = "SX1"))).first;
//     AtomType::aSZ1 = *repository.insert (new ASZ1 ((str = "SZ1"))).first;
//     AtomType::aSZ2 = *repository.insert (new ASZ2 ((str = "SZ2"))).first;
//     AtomType::aS_1 = *repository.insert (new AS_1 ((str = "S_1"))).first;
//     AtomType::aS_2 = *repository.insert (new AS_2 ((str = "S_2"))).first;
//     AtomType::aTA1 = *repository.insert (new ATA1 ((str = "TA1"))).first;
//     AtomType::aTA2 = *repository.insert (new ATA2 ((str = "TA2"))).first;
//     AtomType::aTA3 = *repository.insert (new ATA3 ((str = "TA3"))).first;
//     AtomType::aTA4 = *repository.insert (new ATA4 ((str = "TA4"))).first;
//     AtomType::aTA5 = *repository.insert (new ATA5 ((str = "TA5"))).first;
//     AtomType::aTA6 = *repository.insert (new ATA6 ((str = "TA6"))).first;
//     AtomType::aTE3 = *repository.insert (new ATE3 ((str = "TE3"))).first;
//     AtomType::aTHO* = *repository.insert (new ATHO* ((str = "THO*"))).first;
//     AtomType::aU = *repository.insert (new AU ((str = "U"))).first;
//     AtomType::aUC1* = *repository.insert (new AUC1* ((str = "UC1*"))).first;
//     AtomType::aUC2 = *repository.insert (new AUC2 ((str = "UC2"))).first;
//     AtomType::aUC2* = *repository.insert (new AUC2* ((str = "UC2*"))).first;
//     AtomType::aUC3* = *repository.insert (new AUC3* ((str = "UC3*"))).first;
//     AtomType::aUC4 = *repository.insert (new AUC4 ((str = "UC4"))).first;
//     AtomType::aUC4* = *repository.insert (new AUC4* ((str = "UC4*"))).first;
//     AtomType::aUC5 = *repository.insert (new AUC5 ((str = "UC5"))).first;
//     AtomType::aUC5* = *repository.insert (new AUC5* ((str = "UC5*"))).first;
//     AtomType::aUC6 = *repository.insert (new AUC6 ((str = "UC6"))).first;
//     AtomType::aUH1* = *repository.insert (new AUH1* ((str = "UH1*"))).first;
//     AtomType::aUH2* = *repository.insert (new AUH2* ((str = "UH2*"))).first;
//     AtomType::aUH3 = *repository.insert (new AUH3 ((str = "UH3"))).first;
//     AtomType::aUH3* = *repository.insert (new AUH3* ((str = "UH3*"))).first;
//     AtomType::aUH4* = *repository.insert (new AUH4* ((str = "UH4*"))).first;
//     AtomType::aUH5 = *repository.insert (new AUH5 ((str = "UH5"))).first;
//     AtomType::aUH51 = *repository.insert (new AUH51 ((str = "UH51"))).first;
//     AtomType::aUH52 = *repository.insert (new AUH52 ((str = "UH52"))).first;
//     AtomType::aUH6 = *repository.insert (new AUH6 ((str = "UH6"))).first;
//     AtomType::aUHN3 = *repository.insert (new AUHN3 ((str = "UHN3"))).first;
//     AtomType::aUHO2 = *repository.insert (new AUHO2 ((str = "UHO2"))).first;
//     AtomType::aUHO3 = *repository.insert (new AUHO3 ((str = "UHO3"))).first;
//     AtomType::aUN1 = *repository.insert (new AUN1 ((str = "UN1"))).first;
//     AtomType::aUN3 = *repository.insert (new AUN3 ((str = "UN3"))).first;
//     AtomType::aUO1P = *repository.insert (new AUO1P ((str = "UO1P"))).first;
//     AtomType::aUO2 = *repository.insert (new AUO2 ((str = "UO2"))).first;
//     AtomType::aUO2* = *repository.insert (new AUO2* ((str = "UO2*"))).first;
//     AtomType::aUO2P = *repository.insert (new AUO2P ((str = "UO2P"))).first;
//     AtomType::aUO3* = *repository.insert (new AUO3* ((str = "UO3*"))).first;
//     AtomType::aUO3P = *repository.insert (new AUO3P ((str = "UO3P"))).first;
//     AtomType::aUO4 = *repository.insert (new AUO4 ((str = "UO4"))).first;
//     AtomType::aUO4* = *repository.insert (new AUO4* ((str = "UO4*"))).first;
//     AtomType::aUO5* = *repository.insert (new AUO5* ((str = "UO5*"))).first;
//     AtomType::aUP = *repository.insert (new AUP ((str = "UP"))).first;
//     AtomType::aV = *repository.insert (new AV ((str = "V"))).first;
//     AtomType::aV1 = *repository.insert (new AV1 ((str = "V1"))).first;
//     AtomType::aV10 = *repository.insert (new AV10 ((str = "V10"))).first;
//     AtomType::aV2 = *repository.insert (new AV2 ((str = "V2"))).first;
//     AtomType::aV3 = *repository.insert (new AV3 ((str = "V3"))).first;
//     AtomType::aV4 = *repository.insert (new AV4 ((str = "V4"))).first;
//     AtomType::aV5 = *repository.insert (new AV5 ((str = "V5"))).first;
//     AtomType::aV6 = *repository.insert (new AV6 ((str = "V6"))).first;
//     AtomType::aV7 = *repository.insert (new AV7 ((str = "V7"))).first;
//     AtomType::aV8 = *repository.insert (new AV8 ((str = "V8"))).first;
//     AtomType::aV9 = *repository.insert (new AV9 ((str = "V9"))).first;
//     AtomType::aW = *repository.insert (new AW ((str = "W"))).first;
//     AtomType::aW1 = *repository.insert (new AW1 ((str = "W1"))).first;
//     AtomType::aW10 = *repository.insert (new AW10 ((str = "W10"))).first;
//     AtomType::aW11 = *repository.insert (new AW11 ((str = "W11"))).first;
//     AtomType::aW12 = *repository.insert (new AW12 ((str = "W12"))).first;
//     AtomType::aW13 = *repository.insert (new AW13 ((str = "W13"))).first;
//     AtomType::aW14 = *repository.insert (new AW14 ((str = "W14"))).first;
//     AtomType::aW15 = *repository.insert (new AW15 ((str = "W15"))).first;
//     AtomType::aW16 = *repository.insert (new AW16 ((str = "W16"))).first;
//     AtomType::aW17 = *repository.insert (new AW17 ((str = "W17"))).first;
//     AtomType::aW18 = *repository.insert (new AW18 ((str = "W18"))).first;
//     AtomType::aW2 = *repository.insert (new AW2 ((str = "W2"))).first;
//     AtomType::aW3 = *repository.insert (new AW3 ((str = "W3"))).first;
//     AtomType::aW4 = *repository.insert (new AW4 ((str = "W4"))).first;
//     AtomType::aW5 = *repository.insert (new AW5 ((str = "W5"))).first;
//     AtomType::aW6 = *repository.insert (new AW6 ((str = "W6"))).first;
//     AtomType::aW7 = *repository.insert (new AW7 ((str = "W7"))).first;
//     AtomType::aW8 = *repository.insert (new AW8 ((str = "W8"))).first;
//     AtomType::aW9 = *repository.insert (new AW9 ((str = "W9"))).first;
//     AtomType::aWA = *repository.insert (new AWA ((str = "WA"))).first;
//     AtomType::aWB = *repository.insert (new AWB ((str = "WB"))).first;
//     AtomType::aXC1 = *repository.insert (new AXC1 ((str = "XC1"))).first;
//     AtomType::aXC10 = *repository.insert (new AXC10 ((str = "XC10"))).first;
//     AtomType::aXC11 = *repository.insert (new AXC11 ((str = "XC11"))).first;
//     AtomType::aXC12 = *repository.insert (new AXC12 ((str = "XC12"))).first;
//     AtomType::aXC13 = *repository.insert (new AXC13 ((str = "XC13"))).first;
//     AtomType::aXC14 = *repository.insert (new AXC14 ((str = "XC14"))).first;
//     AtomType::aXC15 = *repository.insert (new AXC15 ((str = "XC15"))).first;
//     AtomType::aXC16 = *repository.insert (new AXC16 ((str = "XC16"))).first;
//     AtomType::aXC17 = *repository.insert (new AXC17 ((str = "XC17"))).first;
//     AtomType::aXC18 = *repository.insert (new AXC18 ((str = "XC18"))).first;
//     AtomType::aXC19 = *repository.insert (new AXC19 ((str = "XC19"))).first;
//     AtomType::aXC20 = *repository.insert (new AXC20 ((str = "XC20"))).first;
//     AtomType::aXC22 = *repository.insert (new AXC22 ((str = "XC22"))).first;
//     AtomType::aXC23 = *repository.insert (new AXC23 ((str = "XC23"))).first;
//     AtomType::aXC24 = *repository.insert (new AXC24 ((str = "XC24"))).first;
//     AtomType::aXC25 = *repository.insert (new AXC25 ((str = "XC25"))).first;
//     AtomType::aXC26 = *repository.insert (new AXC26 ((str = "XC26"))).first;
//     AtomType::aXC3 = *repository.insert (new AXC3 ((str = "XC3"))).first;
//     AtomType::aXC4 = *repository.insert (new AXC4 ((str = "XC4"))).first;
//     AtomType::aXC5 = *repository.insert (new AXC5 ((str = "XC5"))).first;
//     AtomType::aXC6 = *repository.insert (new AXC6 ((str = "XC6"))).first;
//     AtomType::aXC8 = *repository.insert (new AXC8 ((str = "XC8"))).first;
//     AtomType::aXC9 = *repository.insert (new AXC9 ((str = "XC9"))).first;
//     AtomType::aXH1 = *repository.insert (new AXH1 ((str = "XH1"))).first;
//     AtomType::aXH11 = *repository.insert (new AXH11 ((str = "XH11"))).first;
//     AtomType::aXH24 = *repository.insert (new AXH24 ((str = "XH24"))).first;
//     AtomType::aXH3 = *repository.insert (new AXH3 ((str = "XH3"))).first;
//     AtomType::aXH4 = *repository.insert (new AXH4 ((str = "XH4"))).first;
//     AtomType::aXH5 = *repository.insert (new AXH5 ((str = "XH5"))).first;
//     AtomType::aXH6 = *repository.insert (new AXH6 ((str = "XH6"))).first;
//     AtomType::aXH8 = *repository.insert (new AXH8 ((str = "XH8"))).first;
//     AtomType::aXH9 = *repository.insert (new AXH9 ((str = "XH9"))).first;
//     AtomType::aXHN1 = *repository.insert (new AXHN1 ((str = "XHN1"))).first;
//     AtomType::aXHN2 = *repository.insert (new AXHN2 ((str = "XHN2"))).first;
//     AtomType::aXHN7 = *repository.insert (new AXHN7 ((str = "XHN7"))).first;
//     AtomType::aXHO2 = *repository.insert (new AXHO2 ((str = "XHO2"))).first;
//     AtomType::aXN2 = *repository.insert (new AXN2 ((str = "XN2"))).first;
//     AtomType::aXN21 = *repository.insert (new AXN21 ((str = "XN21"))).first;
//     AtomType::aXN7 = *repository.insert (new AXN7 ((str = "XN7"))).first;
//     AtomType::aXO10 = *repository.insert (new AXO10 ((str = "XO10"))).first;
//     AtomType::aY1 = *repository.insert (new AY1 ((str = "Y1"))).first;
//     AtomType::aZC2 = *repository.insert (new AZC2 ((str = "ZC2"))).first;
//     AtomType::aZC3 = *repository.insert (new AZC3 ((str = "ZC3"))).first;
//     AtomType::aZC4 = *repository.insert (new AZC4 ((str = "ZC4"))).first;
//     AtomType::aZC5 = *repository.insert (new AZC5 ((str = "ZC5"))).first;
//     AtomType::aZC6 = *repository.insert (new AZC6 ((str = "ZC6"))).first;
//     AtomType::aZC7 = *repository.insert (new AZC7 ((str = "ZC7"))).first;
//     AtomType::aZH2 = *repository.insert (new AZH2 ((str = "ZH2"))).first;
//     AtomType::aZH3 = *repository.insert (new AZH3 ((str = "ZH3"))).first;
//     AtomType::aZH5 = *repository.insert (new AZH5 ((str = "ZH5"))).first;
//     AtomType::aZH6 = *repository.insert (new AZH6 ((str = "ZH6"))).first;
//     AtomType::aZN = *repository.insert (new AZN ((str = "ZN"))).first;
//     AtomType::aZN1 = *repository.insert (new AZN1 ((str = "ZN1"))).first;
//     AtomType::aZO7 = *repository.insert (new AZO7 ((str = "ZO7"))).first;
//     AtomType::aZR1 = *repository.insert (new AZR1 ((str = "ZR1"))).first;
//     AtomType::aZR2 = *repository.insert (new AZR2 ((str = "ZR2"))).first;
//     AtomType::aZR3 = *repository.insert (new AZR3 ((str = "ZR3"))).first;
  }

  
  AtomTypeStore::~AtomTypeStore () 
  {
    set< AtomType*, AtomType::less_deref >::iterator it;
    for (it = repository.begin (); it != repository.end (); ++it)
      delete *it;
  }

  
  // METHODS -------------------------------------------------------------------

  const AtomType* 
  AtomTypeStore::get (const string& key) 
  {
    string key2 = key;
    string::iterator sit;

    for (sit = key2.begin (); sit != key2.end (); ++sit)
    {
      if ('\'' == *sit)
	*sit = '*';
      else
	*sit = toupper (*sit);
    }

    AtomType* atype = new Unknown (key2);    
    pair< set< AtomType*, AtomType::less_deref >::iterator, bool > inserted =
      repository.insert (atype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete atype;
      atype = *inserted.first;
    }
    else
      gOut (4) << endl << "... created unknown atom type \'" << atype << "\'" << endl;

    return atype;
  }


  // TYPES ---------------------------------------------------------------------

  float
  AtomTypeStore::AC1p::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rRA)      return 0.0394;
    else if (r == ResidueType::rDA) return 0.0431;
    else if (r == ResidueType::rRC) return 0.0066;
    else if (r == ResidueType::rDC) return -0.0116;
    else if (r == ResidueType::rRG) return 0.0191;
    else if (r == ResidueType::rDG) return 0.0358;
    else if (r == ResidueType::rRU) return 0.0674;
    else if (r == ResidueType::rDT) return 0.0680;
    else                  return 0;
  }

  
  float
  AtomTypeStore::AC2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0670;
    else if (r->isDNA ())
      return -0.0854;
    else
      return 0;
  }
  

  float
  AtomTypeStore::AC3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.2022;
    else if (r->isDNA ())
      return 0.0713;
    else
      return 0;
  }


  float
  AtomTypeStore::AC4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.1065;
    else if (r->isDNA ())
      return 0.1629;
    else
      return 0;
  }

  float
  AtomTypeStore::AC5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return 0.0558;
    else if (r->isDNA ())
      return -0.0069;
    else
      return 0;
  }

  float
  AtomTypeStore::AH1p::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA) return 0.1838;
    else if (r == ResidueType::rRA) return 0.2007;
    else if (r == ResidueType::rDC) return 0.1963;
    else if (r == ResidueType::rRC) return 0.2029;
    else if (r == ResidueType::rDG) return 0.1746;
    else if (r == ResidueType::rRG) return 0.2006;
    else if (r == ResidueType::rDT) return 0.1804;
    else if (r == ResidueType::rRU) return 0.1824;
    else return 0;
  }


  float
  AtomTypeStore::AH2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718;
    else if (r->isRNA ())
      return 0.0972;
    else
      return 0;
  }

  float
  AtomTypeStore::AH3p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0985;
    else if (r->isRNA ())
      return 0.0615;
    else
      return 0;
  }

  float
  AtomTypeStore::AH4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.1176;
    else if (r->isRNA ())
      return 0.1174;
    else
      return 0;
  }


  float
  AtomTypeStore::AH5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    else
      return 0;
  }



  float
  AtomTypeStore::AO1P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isRNA ())
      return -0.6139;
    else
      return 0;
  }


  float
  AtomTypeStore::AO2P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }





  float
  AtomTypeStore::AO3p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO3p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH3T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700;  // Assumes the residue is not terminal
  }
  
  
  
  float
  AtomTypeStore::AO3p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH3T) == res->end ())
//       {
    // *** Now assumes the residue is not terminal
    if (r->isDNA ())
      return -0.5232;
    else if (r->isRNA ())
      return -0.5246;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.6549;
// 	else if (r->isRNA ())
// 	  return -0.6541;
//       }
    return 0;
  }


  float
  AtomTypeStore::AO3P::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.7761;
    else if (r->isRNA ())
      return -0.7760;
    else
      return 0;
  }


  float
  AtomTypeStore::AO4p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return -0.3691;
    else if (r->isRNA ())
      return -0.3548;
    else
      return 0;
  }



  float
  AtomTypeStore::AO5p::getVDWR (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 1.7210 : 1.6837;
    return 1.6837;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberEpsilon (const ResidueType *r) const
  {
    //return res->find (AtomType::aH5T) != res->end () ? 0.2104 : 0.1700;
    return 0.1700;  // Assumes the residue is not terminal
  }



  float
  AtomTypeStore::AO5p::getAmberCharge (const ResidueType *r) const
  {
//     if (res->find (AtomType::aH5T) != res->end ())
//       {
    // Assumes the residue is not terminal
    if (r->isDNA ())
      return -0.6318;
    else if (r->isRNA ())
      return -0.6223;
//       }
//     else
//       {
// 	if (r->isDNA ())
// 	  return -0.4954;
// 	else if (r->isRNA ())
// 	  return -0.4989;
//       }
    return 0;
  }



  float
  AtomTypeStore::AP::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 1.1659;
    else if (r->isRNA ())
      return 1.1662;
    return 0;
  }


  float
  AtomTypeStore::A1H2p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0718;
    else if (r->isRNA ())
      return 0.0972;
    return 0;
  }


  float
  AtomTypeStore::A1H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }

  float
  AtomTypeStore::A2H2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.0718;
  }


  float
  AtomTypeStore::A2H5p::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.0754;
    else if (r->isRNA ())
      return 0.0679;
    return 0;
  }


  float
  AtomTypeStore::AHO2p::getAmberCharge (const ResidueType *r) const
  {
    return 0.4186;
  }


  float
  AtomTypeStore::AC2::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.5716;
	else if (r->isT ())
	  return 0.5677;
	else if (r->isG ())
	  return 0.7432;
	else if (r->isC ())
	  return 0.7959;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.5875;
	else if (r->isU ())
	  return 0.4687;
	else if (r->isG ())
	  return 0.7657;
	else if (r->isC ())
	  return 0.7538;
      }
    return 0;
  }

  float
  AtomTypeStore::AC4::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.3800;
	else if (r->isT ())
	  return 0.5194;
	else if (r->isG ())
	  return 0.1814;
	else if (r->isC ())
	  return 0.8439;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.3053;
	else if (r->isC ())
	  return 0.8185;
	else if (r->isG ())
	  return 0.1222;
	else if (r->isU ())
	  return 0.5952;
      }
    return 0;
  }

  float
  AtomTypeStore::AC5::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.0725;
	else if (r->isT ())
	  return 0.0025;
	else if (r->isG ())
	  return 0.1991;
	else if (r->isC ())
	  return -0.5222;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.0515;
	else if (r->isC ())
	  return -0.5215;
	else if (r->isG ())
	  return  0.1744;
	else if (r->isU ())
	  return -0.3635;
      }
    return 0;
  }


  float
  AtomTypeStore::AC6::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.6897;
	else if (r->isT ())
	  return -0.2209;
	else if (r->isG ())
	  return 0.4918;
	else if (r->isC ())
	  return -0.0183;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return  0.7009;
	else if (r->isC ())
	  return 0.0053;
	else if (r->isG ())
	  return 0.4770;
	else if (r->isU ())
	  return -0.1126;
      }
    return 0;
  }

  float
  AtomTypeStore::AC8::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1607;
	else if (r->isG ())
	  return 0.0736;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return 0.2006;
	else if (r->isG ())
	  return 0.1374;
      }
    return 0;
  }
  float
  AtomTypeStore::AH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.3520;
    else if (r == ResidueType::rRG)
      return 0.3424;
    return 0;
  }



  float
  AtomTypeStore::AH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.0598;
    else if (r == ResidueType::rRA)
      return 0.0473;
    return 0;
  }


  float
  AtomTypeStore::AH3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.3420;
    else if (r == ResidueType::rRU)
      return 0.3154;
    return 0;
  }



  float
  AtomTypeStore::AH5::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.1863;
    else if (r == ResidueType::rRC)
      return 0.1928;
    else if (r == ResidueType::rRU)
      return 0.1811;
    return 0;
  }


  float
  AtomTypeStore::AH6::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isT ())
	  return 0.2607;
	else if (r->isC ())
	  return 0.2293;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return 0.1958;
	else if (r->isU ())
	  return 0.2188;
      }
    return 0;
  }
  float
  AtomTypeStore::AH8::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1877;
	else if (r->isG ())
	  return 0.1997;
      }
    else if (r->isDNA ())
      {
	if (r->isA ())
	  return 0.1553;
	else if (r->isG ())
	  return 0.1640;
      }
    return 0;
  }


  float
  AtomTypeStore::AN1::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7624;
	else if (r->isT ())
	  return -0.0239;
	else if (r->isG ())
	  return -0.5053;
	else if (r->isC ())
	  return -0.0339;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.7615;
	else if (r->isC ())
	  return -0.0484;
	else if (r->isG ())
	  return -0.4787;
	else if (r->isU ())
	  return 0.0418;
      }
    return 0;
  }


  float
  AtomTypeStore::AN2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.9230;
    else if (r == ResidueType::rRG)
      return -0.9672;
    return 0;
  }


  float
  AtomTypeStore::AN3::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.7417;
	else if (r->isT ())
	  return -0.4340;
	else if (r->isG ())
	  return -0.6636;
	else if (r->isC ())
	  return -0.7748;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6997;
	else if (r->isC ())
	  return -0.7584;
	else if (r->isG ())
	  return -0.6323;
	else if (r->isU ())
	  return -0.3549;
      }
    return 0;
  }


  float
  AtomTypeStore::AN4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return -0.9773;
    else if (r == ResidueType::rRC)
      return -0.9530;
    return 0;
  }

  float
  AtomTypeStore::AN6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return -0.9123;
    else if (r == ResidueType::rRA)
      return -0.9019;
    return 0;
  }

  float
  AtomTypeStore::AN7::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.6175;
	else if (r->isG ())
	  return -0.5725;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.6073;
	else if (r->isG ())
	  return -0.5709;
      }
    return 0;
  }

  float
  AtomTypeStore::AN9::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isA ())
	  return -0.0268;
	else if (r->isG ())
	  return 0.0577;
      }
    else if (r->isRNA ())
      {
	if (r->isA ())
	  return -0.0251;
	else if (r->isG ())
	  return  0.0492;
      }
    return 0;
  }


  float
  AtomTypeStore::AO2::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      {
	if (r->isT ())
	  return -0.5881;
	else if (r->isC ())
	  return -0.6548;
      }
    else if (r->isRNA ())
      {
	if (r->isC ())
	  return -0.6252;
	else if (r->isU ())
	  return -0.5477;
      }
    return 0;
  }


  float
  AtomTypeStore::AO4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return -0.5563;
    else if (r == ResidueType::rRU)
      return -0.5761;
    return 0;
  }


  float
  AtomTypeStore::AO6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return -0.5699;
    else if (r == ResidueType::rRG)
      return -0.5597;
    return 0;
  }

  float
  AtomTypeStore::A1H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235;
    else if (r == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A1H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314;
    else if (r == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A1H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A1H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167;
    else if (r == ResidueType::rRA)
      return 0.4115;
    return 0;
  }

  float
  AtomTypeStore::A2H2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDG)
      return 0.4235;
    else if (r == ResidueType::rRG)
      return 0.4364;
    return 0;
  }


  float
  AtomTypeStore::A2H4::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDC)
      return 0.4314;
    else if (r == ResidueType::rRC)    
      return 0.4234;
    return 0;
  }


  float
  AtomTypeStore::A2H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }


  float
  AtomTypeStore::A2H6::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDA)
      return 0.4167;
    else if (r == ResidueType::rRA)
      return 0.4115;
    return 0;
  }


  float
  AtomTypeStore::A3H5M::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rDT)
      return 0.0770;
    return 0;
  }



  float
  AtomTypeStore::AH3T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4396;
    else if (r->isRNA ())
      return 0.4376;
    return 0;
  }

  float
  AtomTypeStore::AH5T::getAmberCharge (const ResidueType *r) const
  {
    if (r->isDNA ())
      return 0.4422;
    else if (r->isRNA ())
      return 0.4295;
    return 0;
  }


  float
  AtomTypeStore::AC::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR       
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN       
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE       
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.59730;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.73410;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.53660;
    else if (r == ResidueType::rPRO)
      return 0.58960;
    return 0;
  }


  float
  AtomTypeStore::ACA::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.03370;
    else if (r == ResidueType::rGLY)
      return -0.02520;
    else if (r == ResidueType::rSER)
      return -0.02490;
    else if (r == ResidueType::rTHR)
      return -0.03890;
    else if (r == ResidueType::rLEU)
      return -0.05180;
    else if (r == ResidueType::rILE)
      return -0.05970;
    else if (r == ResidueType::rVAL)
      return -0.08750;
    else if (r == ResidueType::rASN)
      return 0.01430;
    else if (r == ResidueType::rGLN)
      return -0.00310;
    else if (r == ResidueType::rARG)
      return -0.26370;
    else if (r == ResidueType::rHIS)
      return 0.01880;
    else if (r == ResidueType::rTRP)
      return -0.02750;
    else if (r == ResidueType::rPHE)
      return -0.00240;
    else if (r == ResidueType::rTYR)
      return -0.00140;
    else if (r == ResidueType::rGLU)
      return 0.03970;
    else if (r == ResidueType::rASP)
      return 0.03810;
    else if (r == ResidueType::rLYS)
      return -0.24000;
    else if (r == ResidueType::rPRO)
      return -0.02660;
    else if (r == ResidueType::rCYS)
      return 0.02130;
    else if (r == ResidueType::rMET)
      return -0.02370;
    return 0;
  }


  float
  AtomTypeStore::ACB::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return -0.18250;
    else if (r == ResidueType::rSER)
      return 0.21170;
    else if (r == ResidueType::rTHR)
      return 0.36540;
    else if (r == ResidueType::rLEU)
      return -0.11020;
    else if (r == ResidueType::rILE)
      return 0.13030;
    else if (r == ResidueType::rVAL)
      return 0.29850;
    else if (r == ResidueType::rASN)
      return -0.20410;
    else if (r == ResidueType::rGLN)
      return -0.00360;
    else if (r == ResidueType::rARG)
      return -0.00070;
    else if (r == ResidueType::rHIS)
      return -0.04620;
    else if (r == ResidueType::rTRP)
      return -0.00500;
    else if (r == ResidueType::rPHE)
      return -0.03430;
    else if (r == ResidueType::rTYR)
      return -0.01520;
    else if (r == ResidueType::rGLU)
      return 0.05600;
    else if (r == ResidueType::rASP)
      return -0.03030;
    else if (r == ResidueType::rLYS)
      return -0.00940;
    else if (r == ResidueType::rPRO)
      return -0.00700;
    else if (r == ResidueType::rCYS)
      return -0.12310;
    else if (r == ResidueType::rMET)
      return 0.03420;
    return 0;
  }


  float
  AtomTypeStore::ACD::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rGLN || t == ResidueType::rGLU ? 0.0860 : 0.1094;
  }



  float
  AtomTypeStore::ACD::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.69510;
    else if (r == ResidueType::rARG)
      return 0.04860;
    else if (r == ResidueType::rGLU)
      return 0.80540;
    else if (r == ResidueType::rLYS)
      return -0.04790;
    else if (r == ResidueType::rPRO)
      return 0.01920;
    return 0;
  }

  float
  AtomTypeStore::ACD1::getAmberEpsilon (const ResidueType *r) const
  {
    return (r == ResidueType::rPHE
	    || r == ResidueType::rTYR
	    || r == ResidueType::rTRP
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return -0.41210;
    else if (r == ResidueType::rILE)
      return -0.06600;
    else if (r == ResidueType::rTRP)
      return -0.16380;
    else if (r == ResidueType::rPHE)
      return -0.12560;
    else if (r == ResidueType::rTYR)
      return -0.19060;
    return 0;
  }


  float
  AtomTypeStore::ACD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return -0.41210;
    else if (r == ResidueType::rHIS)
      return 0.12920;
    else if (r == ResidueType::rTRP)
      return 0.12430;
    else if (r == ResidueType::rPHE)
      return -0.12560;
    else if (r == ResidueType::rTYR)
      return -0.19060;
    return 0;
  }


  float
  AtomTypeStore::ACE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.01430;
    else if (r == ResidueType::rMET)
      return -0.05360;
    return 0;
  }

  float
  AtomTypeStore::ACE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.20570;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }



  float
  AtomTypeStore::ACE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.13800;
    else if (r == ResidueType::rPHE)
      return -0.17040;
    else if (r == ResidueType::rTYR)
      return -0.23410;
    return 0;
  }


  float
  AtomTypeStore::ACE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.23870;
    return 0;
  }


  float
  AtomTypeStore::ACG::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return ((t == ResidueType::rASN || t == ResidueType::rHIS || t == ResidueType::rTRP
	     || t == ResidueType::rPHE || t == ResidueType::rTYR || t == ResidueType::rASP)
	    ? 0.0860 : 0.1094);
  }



  float
  AtomTypeStore::ACG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.35310;
    else if (r == ResidueType::rASN)
      return 0.71300;
    else if (r == ResidueType::rGLN)
      return -0.06450;
    else if (r == ResidueType::rARG)
      return 0.03900;
    else if (r == ResidueType::rHIS)
      return -0.02660;
    else if (r == ResidueType::rTRP)
      return -0.14150;
    else if (r == ResidueType::rPHE)
      return 0.01180;
    else if (r == ResidueType::rTYR)
      return -0.00110;
    else if (r == ResidueType::rGLU)
      return 0.01360;
    else if (r == ResidueType::rASP)
      return 0.79940;
    else if (r == ResidueType::rLYS)
      return 0.01870;
    else if (r == ResidueType::rPRO)
      return 0.01890;
    else if (r == ResidueType::rMET)
      return 0.00180;
    return 0;
  }



  float
  AtomTypeStore::ACG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return -0.04300;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.24380;
    else if (r == ResidueType::rILE)
      return -0.32040;
    else if (r == ResidueType::rVAL)
      return -0.31920;
    return 0;
  }


  float
  AtomTypeStore::ACH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.11340;
    return 0;
  }


  float
  AtomTypeStore::ACZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.80760;
    else if (r == ResidueType::rPHE)
      return -0.10720;
    else if (r == ResidueType::rTYR)
      return 0.32260;
    return 0;
  }


  float
  AtomTypeStore::ACZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.26010;
    return 0;
  }


  float
  AtomTypeStore::ACZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.19720;
    return 0;
  }


  float
  AtomTypeStore::AH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return 0.27190;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return 0.27470;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return 0.29360;
    return 0;
  }


  float
  AtomTypeStore::AHA::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.08230;
    else if (r == ResidueType::rSER)
      return 0.08430;
    else if (r == ResidueType::rTHR)
      return 0.10070;
    else if (r == ResidueType::rLEU)
      return 0.09220;
    else if (r == ResidueType::rILE)
      return 0.08690;
    else if (r == ResidueType::rVAL)
      return 0.09690;
    else if (r == ResidueType::rASN)
      return 0.10480;
    else if (r == ResidueType::rGLN)
      return 0.08500;
    else if (r == ResidueType::rARG)
      return 0.15600;
    else if (r == ResidueType::rHIS)
      return 0.08810;
    else if (r == ResidueType::rTRP)
      return 0.11230;
    else if (r == ResidueType::rPHE)
      return 0.09780;
    else if (r == ResidueType::rTYR)
      return 0.08760;
    else if (r == ResidueType::rGLU)
      return 0.11050;
    else if (r == ResidueType::rASP || r == ResidueType::rMET)
      return 0.08800;
    else if (r == ResidueType::rLYS)
      return 0.14260;
    else if (r == ResidueType::rPRO)
      return 0.06410;
    else if (r == ResidueType::rCYS)
      return 0.11240;
    return 0;
  }


  float
  AtomTypeStore::AHA1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHA2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLY)
      return 0.06980;
    return 0;
  }


  float
  AtomTypeStore::AHB::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.00430;
    else if (r == ResidueType::rILE)
      return 0.01870;
    else if (r == ResidueType::rVAL)
      return -0.02970;
    return 0;
  }

  float
  AtomTypeStore::AHB1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030;
    return 0;
  }



  float
  AtomTypeStore::AHB2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return (t == ResidueType::rSER || t == ResidueType::rCYS) ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030;
    else if (r == ResidueType::rSER)
      return 0.03520;
    else if (r == ResidueType::rLEU)
      return 0.04570;
    else if (r == ResidueType::rASN)
      return 0.07970;
    else if (r == ResidueType::rGLN)
      return 0.01710;
    else if (r == ResidueType::rARG)
      return 0.03270;
    else if (r == ResidueType::rHIS)
      return 0.04020;
    else if (r == ResidueType::rTRP)
      return 0.03390;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950;
    else if (r == ResidueType::rGLU)
      return -0.01730;
    else if (r == ResidueType::rASP)
      return -0.01220;
    else if (r == ResidueType::rLYS)
      return 0.03620;
    else if (r == ResidueType::rPRO)
      return 0.02530;
    else if (r == ResidueType::rCYS)
      return 0.11120;
    else if (r == ResidueType::rMET)
      return 0.02410;
    return 0;
  }

  float
  AtomTypeStore::AHB3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
  
    return t == ResidueType::rSER || t == ResidueType::rCYS ? 1.3870 : 1.4870;
  }



  float
  AtomTypeStore::AHB3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA)
      return 0.06030;
    else if (r == ResidueType::rSER)
      return 0.03520;
    else if (r == ResidueType::rLEU)
      return 0.04570;
    else if (r == ResidueType::rASN)
      return 0.07970;
    else if (r == ResidueType::rGLN)
      return 0.01710;
    else if (r == ResidueType::rARG)
      return 0.03270;
    else if (r == ResidueType::rHIS)
      return 0.04020;
    else if (r == ResidueType::rTRP)
      return 0.03390;
    else if (r == ResidueType::rPHE || r == ResidueType::rTYR)
      return 0.02950;
    else if (r == ResidueType::rGLU)
      return -0.01730;
    else if (r == ResidueType::rASP)
      return -0.01220;
    else if (r == ResidueType::rLYS)
      return 0.03620;
    else if (r == ResidueType::rPRO)
      return 0.02530;
    else if (r == ResidueType::rCYS)
      return 0.11120;
    else if (r == ResidueType::rMET)
      return 0.02410;
    return 0;
  }

  float
  AtomTypeStore::AHD1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000;
    else if (t == ResidueType::rTRP)
      return 1.4090;
    else
      return 1.4590;
  }



  float
  AtomTypeStore::AHD1::getAmberEpsilon (const ResidueType *r) const
  {
    return r == ResidueType::rHIS ? 0.0157 : 0.0150;
  }



  float
  AtomTypeStore::AHD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.36490;
    else if (r == ResidueType::rTRP)
      return 0.20620;
    else if (r == ResidueType::rPHE)
      return 0.13300;
    else if (r == ResidueType::rTYR)
      return 0.16990;
    return 0;
  }


  float
  AtomTypeStore::AHD2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO)
      return 1.3870; // H1
    else if (t == ResidueType::rHIS)
      return 1.4090; // H4
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.4870; // HC
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rARG || t == ResidueType::rPRO || t == ResidueType::rLYS)
      return 0.0157; // H1 HC
    else if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // H4 HA
    else
      return 0.0000; // HO
  }



  float
  AtomTypeStore::AHD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.06870;
    else if (r == ResidueType::rHIS)
      return 0.11470;
    else if (r == ResidueType::rPHE)
      return 0.13300;
    else if (r == ResidueType::rTYR)
      return 0.16990;
    else if (r == ResidueType::rLYS)
      return 0.06210;
    else if (r == ResidueType::rPRO)
      return 0.03910;
    return 0;
  }

  float
  AtomTypeStore::AHE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.34560;
    return 0;
  }



  float
  AtomTypeStore::AHE1::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 1.3590; // H5
    else if (t == ResidueType::rTRP)
      return 0.6000; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // H5 HA
    else if (t == ResidueType::rTRP || t == ResidueType::rMET)
      return 0.0157; // H H1
    return 0;
  }



  float
  AtomTypeStore::AHE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return 0.13920;
    else if (r == ResidueType::rTRP)
      return 0.34120;
    else if (r == ResidueType::rPHE)
      return 0.14300;
    else if (r == ResidueType::rTYR)
      return 0.16560;
    else if (r == ResidueType::rMET)
      return 0.06940;
    return 0;
  }

  float
  AtomTypeStore::AHE2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS)
      return 0.6000; // H
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000; // HP
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    else if (t == ResidueType::rGLU)
      return 0.0000;
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rHIS || t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157; // H HP H1
    else if (t == ResidueType::rPHE || t == ResidueType::rTYR)
      return 0.0150; // HA
    else if (t == ResidueType::rGLU)
      return 0.0000; // HO
    return 0;
  }



  float
  AtomTypeStore::AHE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rPHE)
      return 0.14300;
    else if (r == ResidueType::rTYR)
      return 0.16560;
    else if (r == ResidueType::rLYS)
      return 0.11350;
    else if (r == ResidueType::rMET)
      return 0.06840;
    return 0;
  }


  float
  AtomTypeStore::AHE3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 1.1000; // HP
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rLYS || t == ResidueType::rMET)
      return 0.0157; // HP H1
    else if (t == ResidueType::rTRP)
      return 0.0150; // HA
    return 0;
  }



  float
  AtomTypeStore::AHE3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.17000;
    else if (r == ResidueType::rLYS)
      return 0.11350;
    else if (r == ResidueType::rMET)
      return 0.06840;
    return 0;
  }


  float
  AtomTypeStore::AHG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return 0.42750;
    else if (r == ResidueType::rLEU)
      return -0.03610;
    else if (r == ResidueType::rCYS)
      return 0.19330;
    return 0;
  }


  float
  AtomTypeStore::AHG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.41020;
    return 0;
  }


  float
  AtomTypeStore::AHG2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rGLN || t == ResidueType::rARG || t == ResidueType::rGLU || t == ResidueType::rLYS
	|| t == ResidueType::rPRO)
      return 1.4870; // HC
    else if (t == ResidueType::rMET)
      return 1.3870; // H1
    return 0;
  }



  float
  AtomTypeStore::AHG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.03520;
    else if (r == ResidueType::rARG)
      return 0.02850;
    else if (r == ResidueType::rGLU)
      return -0.04250;
    else if (r == ResidueType::rLYS)
      return 0.01030;
    else if (r == ResidueType::rPRO)
      return 0.02130;
    else if (r == ResidueType::rMET)
      return 0.04400;
    return 0;
  }

  float
  AtomTypeStore::AHH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return 0.39920;
    return 0;
  }


  float
  AtomTypeStore::AHH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14170;
    return 0;
  }


  float
  AtomTypeStore::AHZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rPHE)
      return 0.12970;
    return 0;
  }


  float
  AtomTypeStore::AHZ1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.15720;
    else if (r== ResidueType::rLYS)
      return 0.34000;
    return 0;
  }

  float
  AtomTypeStore::AHZ3::getVDWR (const ResidueType *r) const
  {
    const ResidueType *t = r;
    
    if (t == ResidueType::rTRP)
      return 1.4590; // HA
    else if (t == ResidueType::rLYS)
      return 0.6000; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberEpsilon (const ResidueType *r) const
  {
    const ResidueType *t = r;

    if (t == ResidueType::rTRP)
      return 0.0150; // HA
    else if (t == ResidueType::rLYS)
      return 0.0157; // H
    return 0;
  }



  float
  AtomTypeStore::AHZ3::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return 0.14470;
    else if (r == ResidueType::rLYS)
      return 0.34000;
    return 0;
  }


  float
  AtomTypeStore::AN::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.41570;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.34790;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.51630;
    else if (r == ResidueType::rPRO)
      return -0.25480;
    return 0;
  }


  float
  AtomTypeStore::AND1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rHIS)
      return -0.38110;
    return 0;
  }


  float
  AtomTypeStore::AND2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.91910;
    return 0;
  }


  float
  AtomTypeStore::ANE::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.52950;
    return 0;
  }


  float
  AtomTypeStore::ANE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTRP)
      return -0.34180;
    return 0;
  }


  float
  AtomTypeStore::ANE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.94070;
    else if (r == ResidueType::rHIS)
      return -0.57270;
    return 0;
  }

  float
  AtomTypeStore::ANH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return -0.86270;
    return 0;
  }


  float
  AtomTypeStore::ANZ::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLYS)
      return -0.38540;
    return 0;
  }


  float
  AtomTypeStore::AO::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rALA || r == ResidueType::rGLY || r == ResidueType::rSER || r == ResidueType::rTHR
	|| r == ResidueType::rLEU || r == ResidueType::rILE || r == ResidueType::rVAL || r == ResidueType::rASN
	|| r == ResidueType::rGLN || r == ResidueType::rHIS || r == ResidueType::rTRP || r == ResidueType::rPHE
	|| r == ResidueType::rTYR || r == ResidueType::rCYS || r == ResidueType::rMET)
      return -0.56790;
    else if (r == ResidueType::rARG || r == ResidueType::rLYS)
      return -0.58940;
    else if (r == ResidueType::rGLU || r == ResidueType::rASP)
      return -0.58190;
    else if (r == ResidueType::rPRO)
      return -0.57480;
    return 0;
  }

  float
  AtomTypeStore::AOD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASN)
      return -0.59310;
    else if (r == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rASP)
      return -0.80140;
    return 0;
  }


  float
  AtomTypeStore::AOE1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return -0.60860;
    else if (r == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLU)
      return -0.81880;
    return 0;
  }


  float
  AtomTypeStore::AOG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rSER)
      return -0.65460;
    return 0;
  }

  float
  AtomTypeStore::AOG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return -0.67610;
    return 0;
  }


  float
  AtomTypeStore::AOH::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTYR)
      return -0.55790;
    return 0;
  }

  float
  AtomTypeStore::ASD::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rMET)
      return -0.27370;
    return 0;
  }


  float
  AtomTypeStore::ASG::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rCYS)
      return -0.31190;
    return 0;
  }


  float
  AtomTypeStore::A1HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A1HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A1HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A1HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A1HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A1HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A2HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }


  float
  AtomTypeStore::A2HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rASN)
      return 0.41960;
    return 0;
  }


  float
  AtomTypeStore::A2HE2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rGLN)
      return 0.42510;
    return 0;
  }


  float
  AtomTypeStore::A2HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A2HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


  float
  AtomTypeStore::A2HH1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }


  float
  AtomTypeStore::A2HH2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rARG)
      return 0.44780;
    return 0;
  }

  float
  AtomTypeStore::A3HD1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    else if (r == ResidueType::rILE)
      return 0.01860;
    return 0;
  }



  float
  AtomTypeStore::A3HD2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rLEU)
      return 0.10000;
    return 0;
  }


  float
  AtomTypeStore::A3HG1::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rILE)
      return 0.02360;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }

  float
  AtomTypeStore::A3HG2::getAmberCharge (const ResidueType *r) const
  {
    if (r == ResidueType::rTHR)
      return 0.06420;
    else if (r == ResidueType::rILE)
      return 0.08820;
    else if (r == ResidueType::rVAL)
      return 0.07910;
    return 0;
  }


}
