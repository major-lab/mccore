//                              -*- Mode: C++ -*- 
// McCore.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Wed Aug 29 11:49:33 2001
// Update Count     : 14
// Status           : Ok.
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

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/param.h>

#include "McCore.h"

#include "AtomTypeImp.h"
#include "CAtom.h"
#include "CMessageQueue.h"
#include "CResidue.h"
#include "CTransfo.h"
#include "ResidueTypeImp.h"
#include "CException.h"


map< const char *, t_Atom*, less_string > gMiscAtomString;
map< const char *, t_Residue*, less_string > gMiscResidueString;


t_Atom *a_NucleicAcid = 0;
t_Atom *a_AminoAcid = 0;
t_Atom *a_Backbone = 0;
t_Atom *a_SideChain = 0;
t_Atom *a_Carbon = 0;
t_Atom *a_Hydrogen = 0;
t_Atom *a_Nitrogen = 0;
t_Atom *a_Phosphate = 0;
t_Atom *a_Oxygen = 0;
t_Atom *a_Sulfur = 0;
t_Atom *a_Magnesium = 0;
t_Atom *a_LonePair = 0;
t_Atom *a_Pseudo = 0;
t_Atom *a_C1p = 0;
t_Atom *a_C2p = 0;
t_Atom *a_C3p = 0;
t_Atom *a_C4p = 0;
t_Atom *a_C5p = 0;
t_Atom *a_H1p = 0;
t_Atom *a_H2p = 0;
t_Atom *a_H3p = 0;
t_Atom *a_H4p = 0;
t_Atom *a_H5p = 0;
t_Atom *a_O1P = 0;
t_Atom *a_O2p = 0;
t_Atom *a_O2P = 0;
t_Atom *a_O3p = 0;
t_Atom *a_O3P = 0;
t_Atom *a_O4p = 0;
t_Atom *a_O5p = 0;
t_Atom *a_P = 0;
t_Atom *a_1H2p = 0;
t_Atom *a_1H5p = 0;
t_Atom *a_2H2p = 0;
t_Atom *a_2H5p = 0;
t_Atom *a_HO2p = 0;
t_Atom *a_HO3p = 0;
t_Atom *a_C2 = 0;
t_Atom *a_C4 = 0;
t_Atom *a_C5 = 0;
t_Atom *a_C5M = 0;
t_Atom *a_C6 = 0;
t_Atom *a_C8 = 0;
t_Atom *a_H1 = 0;
t_Atom *a_H2 = 0;
t_Atom *a_H3 = 0;
t_Atom *a_H5 = 0;
t_Atom *a_H6 = 0;
t_Atom *a_H7 = 0;
t_Atom *a_H8 = 0;
t_Atom *a_N1 = 0;
t_Atom *a_N2 = 0;
t_Atom *a_N3 = 0;
t_Atom *a_N4 = 0;
t_Atom *a_N6 = 0;
t_Atom *a_N7 = 0;
t_Atom *a_N9 = 0;
t_Atom *a_O2 = 0;
t_Atom *a_O4 = 0;
t_Atom *a_O6 = 0;
t_Atom *a_1H2 = 0;
t_Atom *a_1H4 = 0;
t_Atom *a_1H5M = 0;
t_Atom *a_1H6 = 0;
t_Atom *a_2H2 = 0;
t_Atom *a_2H4 = 0;
t_Atom *a_2H5M = 0;
t_Atom *a_2H6 = 0;
t_Atom *a_3H5M = 0;
t_Atom *a_PSY = 0;
t_Atom *a_PSZ = 0;
t_Atom *a_2LP6 = 0;
t_Atom *a_1LP6 = 0;
t_Atom *a_LP7 = 0;
t_Atom *a_LP3 = 0;
t_Atom *a_LP1 = 0;
t_Atom *a_2LP2 = 0;
t_Atom *a_1LP2 = 0;
t_Atom *a_2LP4 = 0;
t_Atom *a_1LP4 = 0;
t_Atom *a_H3T = 0;
t_Atom *a_H5T = 0;
t_Atom *a_C = 0;
t_Atom *a_CA = 0;
t_Atom *a_CB = 0;
t_Atom *a_CD = 0;
t_Atom *a_CD1 = 0;
t_Atom *a_CD2 = 0;
t_Atom *a_CE = 0;
t_Atom *a_CE1 = 0;
t_Atom *a_CE2 = 0;
t_Atom *a_CE3 = 0;
t_Atom *a_CG = 0;
t_Atom *a_CG1 = 0;
t_Atom *a_CG2 = 0;
t_Atom *a_CH2 = 0;
t_Atom *a_CZ = 0;
t_Atom *a_CZ2 = 0;
t_Atom *a_CZ3 = 0;
t_Atom *a_H = 0;
t_Atom *a_1H = 0;
t_Atom *a_2H = 0;
t_Atom *a_3H = 0;
t_Atom *a_HA = 0;
t_Atom *a_HA1 = 0;
t_Atom *a_HA2 = 0;
t_Atom *a_HB = 0;
t_Atom *a_HB1 = 0;
t_Atom *a_HB2 = 0;
t_Atom *a_HB3 = 0;
t_Atom *a_HD1 = 0;
t_Atom *a_HD2 = 0;
t_Atom *a_HE = 0;
t_Atom *a_HE1 = 0;
t_Atom *a_HE2 = 0;
t_Atom *a_HE3 = 0;
t_Atom *a_HG = 0;
t_Atom *a_HG1 = 0;
t_Atom *a_HG2 = 0;
t_Atom *a_HH = 0;
t_Atom *a_HH2 = 0;
t_Atom *a_HXT = 0;
t_Atom *a_HZ = 0;
t_Atom *a_HZ1 = 0;
t_Atom *a_HZ2 = 0;
t_Atom *a_HZ3 = 0;
t_Atom *a_N = 0;
t_Atom *a_ND1 = 0;
t_Atom *a_ND2 = 0;
t_Atom *a_NE = 0;
t_Atom *a_NE1 = 0;
t_Atom *a_NE2 = 0;
t_Atom *a_NH1 = 0;
t_Atom *a_NH2 = 0;
t_Atom *a_NZ = 0;
t_Atom *a_O = 0;
t_Atom *a_OD1 = 0;
t_Atom *a_OD2 = 0;
t_Atom *a_OE1 = 0;
t_Atom *a_OE2 = 0;
t_Atom *a_OG = 0;
t_Atom *a_OG1 = 0;
t_Atom *a_OH = 0;
t_Atom *a_OXT = 0;
t_Atom *a_SD = 0;
t_Atom *a_SG = 0;
t_Atom *a_1HD1 = 0;
t_Atom *a_1HD2 = 0;
t_Atom *a_1HE2 = 0;
t_Atom *a_1HG1 = 0;
t_Atom *a_1HG2 = 0;
t_Atom *a_1HH1 = 0;
t_Atom *a_1HH2 = 0;
t_Atom *a_2HD1 = 0;
t_Atom *a_2HD2 = 0;
t_Atom *a_2HE2 = 0;
t_Atom *a_2HG1 = 0;
t_Atom *a_2HG2 = 0;
t_Atom *a_2HH1 = 0;
t_Atom *a_2HH2 = 0;
t_Atom *a_3HD1 = 0;
t_Atom *a_3HD2 = 0;
t_Atom *a_3HG1 = 0;
t_Atom *a_3HG2 = 0;
t_Atom *a_MG = 0;
t_Atom *a_PSAZ = 0;



t_Residue *r_NucleicAcid = 0;
t_Residue *r_AminoAcid = 0;
t_Residue *r_Phosphate = 0;
t_Residue *r_Purine = 0;
t_Residue *r_Pyrimidine = 0;
t_Residue *r_DNA = 0;
t_Residue *r_RNA = 0;
t_Residue *r_A = 0;
t_Residue *r_C = 0;
t_Residue *r_G = 0;
t_Residue *r_U = 0;
t_Residue *r_T = 0;
t_Residue *r_rA = 0;
t_Residue *r_rC = 0;
t_Residue *r_rG = 0;
t_Residue *r_rU = 0;
t_Residue *r_dA = 0;
t_Residue *r_dC = 0;
t_Residue *r_dG = 0;
t_Residue *r_dT = 0;
t_Residue *r_ALA = 0;
t_Residue *r_ARG = 0;
t_Residue *r_ASN = 0;
t_Residue *r_ASP = 0;
t_Residue *r_CYS = 0;
t_Residue *r_GLN = 0;
t_Residue *r_GLU = 0;
t_Residue *r_GLY = 0;
t_Residue *r_HIS = 0;
t_Residue *r_ILE = 0;
t_Residue *r_LEU = 0;
t_Residue *r_LYS = 0;
t_Residue *r_MET = 0;
t_Residue *r_PHE = 0;
t_Residue *r_PRO = 0;
t_Residue *r_SER = 0;
t_Residue *r_THR = 0;
t_Residue *r_TRP = 0;
t_Residue *r_TYR = 0;
t_Residue *r_VAL = 0;



set< t_Atom* > gdAOblAtomSet;
set< t_Atom* > grAOblAtomSet;
set< t_Atom* > gdCOblAtomSet;
set< t_Atom* > grCOblAtomSet;
set< t_Atom* > gdGOblAtomSet;
set< t_Atom* > grGOblAtomSet;
set< t_Atom* > gdTOblAtomSet;
set< t_Atom* > grUOblAtomSet;
set< t_Atom* > gALAOblAtomSet;
set< t_Atom* > gARGOblAtomSet;
set< t_Atom* > gASNOblAtomSet;
set< t_Atom* > gASPOblAtomSet;
set< t_Atom* > gCYSOblAtomSet;
set< t_Atom* > gGLNOblAtomSet;
set< t_Atom* > gGLUOblAtomSet;
set< t_Atom* > gGLYOblAtomSet;
set< t_Atom* > gHISOblAtomSet;
set< t_Atom* > gILEOblAtomSet;
set< t_Atom* > gLEUOblAtomSet;
set< t_Atom* > gLYSOblAtomSet;
set< t_Atom* > gMETOblAtomSet;
set< t_Atom* > gPHEOblAtomSet;
set< t_Atom* > gPROOblAtomSet;
set< t_Atom* > gSEROblAtomSet;
set< t_Atom* > gTHROblAtomSet;
set< t_Atom* > gTRPOblAtomSet;
set< t_Atom* > gTYROblAtomSet;
set< t_Atom* > gVALOblAtomSet;



set< t_Atom* > gdAOptAtomSet;
set< t_Atom* > grAOptAtomSet;
set< t_Atom* > gdCOptAtomSet;
set< t_Atom* > grCOptAtomSet;
set< t_Atom* > gdGOptAtomSet;
set< t_Atom* > grGOptAtomSet;
set< t_Atom* > gdTOptAtomSet;
set< t_Atom* > grUOptAtomSet;
set< t_Atom* > gALAOptAtomSet;
set< t_Atom* > gARGOptAtomSet;
set< t_Atom* > gASNOptAtomSet;
set< t_Atom* > gASPOptAtomSet;
set< t_Atom* > gCYSOptAtomSet;
set< t_Atom* > gGLNOptAtomSet;
set< t_Atom* > gGLUOptAtomSet;
set< t_Atom* > gGLYOptAtomSet;
set< t_Atom* > gHISOptAtomSet;
set< t_Atom* > gILEOptAtomSet;
set< t_Atom* > gLEUOptAtomSet;
set< t_Atom* > gLYSOptAtomSet;
set< t_Atom* > gMETOptAtomSet;
set< t_Atom* > gPHEOptAtomSet;
set< t_Atom* > gPROOptAtomSet;
set< t_Atom* > gSEROptAtomSet;
set< t_Atom* > gTHROptAtomSet;
set< t_Atom* > gTRPOptAtomSet;
set< t_Atom* > gTYROptAtomSet;
set< t_Atom* > gVALOptAtomSet;



CMessageQueue gOut (cerr, 2);



void
SetOblAtomSets ()
{
  t_Atom** dA[23] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_C8,  &a_N1,  &a_N3,
		      &a_N6,  &a_N7,  &a_N9,  &a_O1P, &a_O2P, &a_O3p,
		      &a_O4p, &a_O5p, &a_P,   &a_PSY, &a_PSZ };
  t_Atom** rA[24] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_C8,  &a_N1,  &a_N3,
		      &a_N6,  &a_N7,  &a_N9,  &a_O1P, &a_O2P, &a_O2p,
		      &a_O3p, &a_O4p, &a_O5p, &a_P,   &a_PSY, &a_PSZ };
  t_Atom** dC[21] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_N1,  &a_N3,  &a_N4,
		      &a_O1P, &a_O2,  &a_O2P, &a_O3p, &a_O4p, &a_O5p,
		      &a_P,   &a_PSY, &a_PSZ };
  t_Atom** rC[22] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_N1,  &a_N3,  &a_N4,
		      &a_O1P, &a_O2,  &a_O2P, &a_O2p, &a_O3p, &a_O4p,
		      &a_O5p, &a_P,   &a_PSY, &a_PSZ };
  t_Atom** dG[24] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_C8,  &a_N1,  &a_N2,
		      &a_N3,  &a_N7,  &a_N9,  &a_O1P, &a_O2P, &a_O3p,
		      &a_O4p, &a_O5p, &a_O6,  &a_P,   &a_PSY, &a_PSZ };
  t_Atom** rG[25] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_C8,  &a_N1,  &a_N2,
		      &a_N3,  &a_N7,  &a_N9,  &a_O1P, &a_O2p, &a_O2P,
		      &a_O3p, &a_O4p, &a_O5p, &a_O6,  &a_P,   &a_PSY,
		      &a_PSZ };
  t_Atom** dT[22] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C5M, &a_C6,  &a_N1,  &a_N3,
		      &a_O1P, &a_O2,  &a_O2P, &a_O3p, &a_O4,  &a_O4p,
		      &a_O5p, &a_P,   &a_PSY, &a_PSZ };
  t_Atom** rU[22] = { &a_C1p, &a_C2,  &a_C2p, &a_C3p, &a_C4,  &a_C4p,
		      &a_C5,  &a_C5p, &a_C6,  &a_N1,  &a_N3,  &a_O1P,
		      &a_O2,  &a_O2p, &a_O2P, &a_O3p, &a_O4,  &a_O4p,
		      &a_O5p, &a_P,   &a_PSY, &a_PSZ };
  t_Atom** ALA[5]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB};
  t_Atom** ARG[11] = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD,   &a_NE,   &a_CZ,   &a_NH1,  &a_NH2 };
  t_Atom** ASN[8]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_OD1,  &a_ND2 };
  t_Atom** ASP[8]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_OD1,  &a_OD2 };
  t_Atom** CYS[6]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_SG };
  t_Atom** GLN[9]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD,   &a_OE1,  &a_NE2 };
  t_Atom** GLU[9]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD,   &a_OE1,  &a_OE2 };
  t_Atom** GLY[4]  = { &a_N,    &a_C,    &a_O,    &a_CA };
  t_Atom** HIS[10] = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_ND1,  &a_CD2,  &a_CE1,  &a_NE2 };
  t_Atom** ILE[8]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG1,
		       &a_CG2,  &a_CD1 };
  t_Atom** LEU[8]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD1,  &a_CD2 };
  t_Atom** LYS[9]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD,   &a_CE,   &a_NZ };
  t_Atom** MET[8]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_SD,   &a_CE };
  t_Atom** PHE[11] = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD1,  &a_CD2,  &a_CE1,  &a_CE2,  &a_CZ };
  t_Atom** PRO[7]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD };
  t_Atom** SER[6]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_OG };
  t_Atom** THR[7]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_OG1,
		       &a_CG2 };
  t_Atom** TRP[14] = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD1,  &a_CD2,  &a_NE1,  &a_CE2,  &a_CE3,  &a_CZ2,
		       &a_CZ3,  &a_CH2 };
  t_Atom** TYR[12] = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG,
		       &a_CD1,  &a_CD2,  &a_CE1,  &a_CE2,  &a_CZ,   &a_OH };
  t_Atom** VAL[7]  = { &a_N,    &a_C,    &a_O,    &a_CA,   &a_CB,   &a_CG1,
		       &a_CG2 };
  t_Atom** odA[17] = { &a_H2,   &a_H8,   &a_1H6,  &a_2H6,  &a_LP1,  &a_LP3,
		       &a_LP7,  &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,  &a_1H5p,
		       &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** orA[17] = { &a_H2,   &a_H8,   &a_1H6,  &a_2H6,  &a_LP1,  &a_LP3,
		       &a_LP7,  &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,  &a_1H5p,
		       &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p, };
  t_Atom** odC[17] = { &a_H5,   &a_H6,   &a_1H4,  &a_2H4,  &a_LP3,  &a_1LP2,
		       &a_2LP2, &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,  &a_1H5p,
		       &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** orC[17] = { &a_H5,   &a_H6,   &a_1H4,  &a_2H4,  &a_LP3,  &a_1LP2,
		       &a_2LP2, &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,  &a_1H5p,
		       &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** odG[18] = { &a_H1,   &a_H8,   &a_1H2,  &a_2H2,  &a_LP3,  &a_LP7,
		       &a_1LP6, &a_2LP6, &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,
		       &a_1H5p, &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** orG[18] = { &a_H1,   &a_H8,   &a_1H2,  &a_2H2,  &a_LP3,  &a_LP7,
		       &a_1LP6, &a_2LP6, &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,
		       &a_1H5p, &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** odT[19] = { &a_1LP2, &a_2LP2, &a_1LP4, &a_2LP4, &a_H3,   &a_H6,
		       &a_1H5M, &a_2H5M, &a_3H5M, &a_H1p,  &a_H2p,  &a_H3p,
		       &a_H4p,  &a_1H5p, &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p,
		       &a_H5p };
  t_Atom** orU[17] = { &a_H3,   &a_H5,   &a_H6,   &a_1LP2, &a_2LP2, &a_1LP4,
		       &a_2LP4, &a_H1p,  &a_H2p,  &a_H3p,  &a_H4p,  &a_1H5p,
		       &a_2H5p, &a_HO2p, &a_HO3p, &a_1H2p, &a_H5p };
  t_Atom** oALA[6]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HB3 };
  t_Atom** oARG[14] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,
			&a_HG2,  &a_HD1,  &a_HD2,  &a_HE,   &a_1HH1, &a_2HH1,
			&a_1HH2, &a_2HH2 };
  t_Atom** oASN[7]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_1HD2,
			&a_2HD2 };
  t_Atom** oASP[5]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2 };
  t_Atom** oCYS[6]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG };
  t_Atom** oGLN[9]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,
			&a_HG2,  &a_1HE2, &a_2HE2 };
  t_Atom** oGLU[7]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,
			&a_HG2 };
  t_Atom** oGLY[4]  = { &a_H1,   &a_H2,   &a_HA1,  &a_HA2 };
  t_Atom** oHIS[8]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HD1,
			&a_HD2,  &a_HE1 };
  t_Atom** oILE[12] = { &a_H1,   &a_H2,   &a_HA,   &a_HB,   &a_1HG1, &a_2HG1,
			&a_1HG2, &a_2HG2, &a_3HG2, &a_1HD1, &a_2HD1, &a_3HD1 };
  t_Atom** oLEU[12] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG,
			&a_1HD1, &a_2HD1, &a_3HD1, &a_1HD2, &a_2HD2, &a_3HD2 };
  t_Atom** oLYS[14] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,
			&a_HG2,  &a_HD1,  &a_HD2,  &a_HE1,  &a_HE2,  &a_HZ1,
			&a_HZ2,  &a_HZ3 };
  t_Atom** oMET[10] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,
			&a_HG2,  &a_HE1,  &a_HE2,  &a_HE3 };
  t_Atom** oPHE[10] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HD1,
			&a_HD2,  &a_HE1,  &a_HE2,  &a_HZ };
  t_Atom** oPRO[8]  = { &a_H,    &a_HA,   &a_HB1,  &a_HB2,  &a_HG1,  &a_HG2,
			&a_HD1,  &a_HD2 };
  t_Atom** oSER[6]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HG };
  t_Atom** oTHR[8]  = { &a_H1,   &a_H2,   &a_HA,   &a_HB,   &a_HG1,  &a_1HG2,
			&a_2HG2, &a_3HG2 };
  t_Atom** oTRP[11] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HD1,
			&a_HE1,  &a_HE3,  &a_HZ2,  &a_HZ3,  &a_HH2 };
  t_Atom** oTYR[10] = { &a_H1,   &a_H2,   &a_HA,   &a_HB1,  &a_HB2,  &a_HD1,
			&a_HD2,  &a_HE1,  &a_HE2,  &a_HH };
  t_Atom** oVAL[10] = { &a_H1,   &a_H2,   &a_HA,   &a_HB,   &a_1HG1, &a_2HG1,
			&a_3HG1, &a_1HG2, &a_2HG2, &a_3HG2 };
  int i;

  for (i = 0; i < 23; ++i)
    gdAOblAtomSet.insert (*(dA[i]));
  for (i = 0; i < 24; ++i)
    grAOblAtomSet.insert (*(rA[i]));
  for (i = 0; i < 21; ++i)
    gdCOblAtomSet.insert (*(dC[i]));
  for (i = 0; i < 22; ++i)
    grCOblAtomSet.insert (*(rC[i]));
  for (i = 0; i < 24; ++i)
    gdGOblAtomSet.insert (*(dG[i]));
  for (i = 0; i < 25; ++i)
    grGOblAtomSet.insert (*(rG[i]));
  for (i = 0; i < 22; ++i)
    gdTOblAtomSet.insert (*(dT[i]));
  for (i = 0; i < 22; ++i)
    grUOblAtomSet.insert (*(rU[i]));
  for (i = 0; i < 5; ++i)
    gALAOblAtomSet.insert (*(ALA[i]));
  for (i = 0; i < 11; ++i)
    gARGOblAtomSet.insert (*(ARG[i]));
  for (i = 0; i < 8; ++i)
    gASNOblAtomSet.insert (*(ASN[i]));
  for (i = 0; i < 8; ++i)
    gASPOblAtomSet.insert (*(ASP[i]));
  for (i = 0; i < 6; ++i)
    gCYSOblAtomSet.insert (*(CYS[i]));
  for (i = 0; i < 9; ++i)
    gGLNOblAtomSet.insert (*(GLN[i]));
  for (i = 0; i < 9; ++i)
    gGLUOblAtomSet.insert (*(GLU[i]));
  for (i = 0; i < 4; ++i)
    gGLYOblAtomSet.insert (*(GLY[i]));
  for (i = 0; i < 10; ++i)
    gHISOblAtomSet.insert (*(HIS[i]));
  for (i = 0; i < 8; ++i)
    gILEOblAtomSet.insert (*(ILE[i]));
  for (i = 0; i < 8; ++i)
    gLEUOblAtomSet.insert (*(LEU[i]));
  for (i = 0; i < 9; ++i)
    gLYSOblAtomSet.insert (*(LYS[i]));
  for (i = 0; i < 8; ++i)
    gMETOblAtomSet.insert (*(MET[i]));
  for (i = 0; i < 11; ++i)
    gPHEOblAtomSet.insert (*(PHE[i]));
  for (i = 0; i < 7; ++i)
    gPROOblAtomSet.insert (*(PRO[i]));
  for (i = 0; i < 6; ++i)
    gSEROblAtomSet.insert (*(SER[i]));
  for (i = 0; i < 7; ++i)
    gTHROblAtomSet.insert (*(THR[i]));
  for (i = 0; i < 14; ++i)
    gTRPOblAtomSet.insert (*(TRP[i]));
  for (i = 0; i < 12; ++i)
    gTYROblAtomSet.insert (*(TYR[i]));
  for (i = 0; i < 7; ++i)
    gVALOblAtomSet.insert (*(VAL[i]));

  for (i = 0; i < 17; ++i)
    gdAOptAtomSet.insert (*(odA[i]));
  for (i = 0; i < 17; ++i)
    grAOptAtomSet.insert (*(orA[i]));
  for (i = 0; i < 17; ++i)
    gdCOptAtomSet.insert (*(odC[i]));
  for (i = 0; i < 17; ++i)
    grCOptAtomSet.insert (*(orC[i]));
  for (i = 0; i < 18; ++i)
    gdGOptAtomSet.insert (*(odG[i]));
  for (i = 0; i < 18; ++i)
    grGOptAtomSet.insert (*(orG[i]));
  for (i = 0; i < 19; ++i)
    gdTOptAtomSet.insert (*(odT[i]));
  for (i = 0; i < 17; ++i)
    grUOptAtomSet.insert (*(orU[i]));
  for (i = 0; i < 6; ++i)
    gALAOptAtomSet.insert (*(oALA[i]));
  for (i = 0; i < 14; ++i)
    gARGOptAtomSet.insert (*(oARG[i]));
  for (i = 0; i < 7; ++i)
    gASNOptAtomSet.insert (*(oASN[i]));
  for (i = 0; i < 5; ++i)
    gASPOptAtomSet.insert (*(oASP[i]));
  for (i = 0; i < 6; ++i)
    gCYSOptAtomSet.insert (*(oCYS[i]));
  for (i = 0; i < 9; ++i)
    gGLNOptAtomSet.insert (*(oGLN[i]));
  for (i = 0; i < 7; ++i)
    gGLUOptAtomSet.insert (*(oGLU[i]));
  for (i = 0; i < 4; ++i)
    gGLYOptAtomSet.insert (*(oGLY[i]));
  for (i = 0; i < 8; ++i)
    gHISOptAtomSet.insert (*(oHIS[i]));
  for (i = 0; i < 12; ++i)
    gILEOptAtomSet.insert (*(oILE[i]));
  for (i = 0; i < 12; ++i)
    gLEUOptAtomSet.insert (*(oLEU[i]));
  for (i = 0; i < 14; ++i)
    gLYSOptAtomSet.insert (*(oLYS[i]));
  for (i = 0; i < 10; ++i)
    gMETOptAtomSet.insert (*(oMET[i]));
  for (i = 0; i < 10; ++i)
    gPHEOptAtomSet.insert (*(oPHE[i]));
  for (i = 0; i < 8; ++i)
    gPROOptAtomSet.insert (*(oPRO[i]));
  for (i = 0; i < 6; ++i)
    gSEROptAtomSet.insert (*(oSER[i]));
  for (i = 0; i < 8; ++i)
    gTHROptAtomSet.insert (*(oTHR[i]));
  for (i = 0; i < 11; ++i)
    gTRPOptAtomSet.insert (*(oTRP[i]));
  for (i = 0; i < 10; ++i)
    gTYROptAtomSet.insert (*(oTYR[i]));
  for (i = 0; i < 10; ++i)
    gVALOptAtomSet.insert (*(oVAL[i]));
}



float
minf (float x, float y)
{
  return x < y ? x : y;
}



float
absf (float x)
{
  return x > 0 ? x : -x;
}



bool
equal0 (double x)
{
  return x + (1e-10) >= 0 && x - (1e-10) <= 0;
}




double
arctan2 (double x, double y)
{
  bool xe0 = equal0 (x);
  bool ye0 = equal0 (y);
  bool xg0 = x > 0;
  bool xl0 = x < 0;
  bool yl0 = y < 0;
  bool yg0 = y > 0;
  
  if (xe0 && ye0)
    return 0;
  if (xg0 && ye0)
    return M_PI_2;
  if (xl0 && ye0)
    return -M_PI_2;
  if (xg0 && yg0)
    return atan (x / y);
  if (xe0 && yg0)
    return 0;
  if (xe0 && yl0)
    return -M_PI;
  if (xg0 && yl0)
    return M_PI - atan (x / -y);
  if (xl0 && yl0)
    return -M_PI + atan (-x / -y);
  if (xl0)
    return -atan (-x / y);
  return 1;
}



float
DegToRadian (float d)
{
  return d * M_PI / 180;
}



float
RadToDegree (float r)
{
  return r * 180 / M_PI;
}



float 
rmsd (const vector< CResidue::iterator > &mgr1,
      const vector< CResidue::iterator > &mgr2)
{
  float rmsd = 0;
  vector< CResidue::iterator >::const_iterator i, j;
  
  for (i = mgr1.begin (), j = mgr2.begin (); i != mgr1.end (); i++, j++)
    rmsd += **i || **j;
  return sqrt (rmsd / (float)mgr1.size ());
}



float 
rmsd (const CResidue::iterator &begin_a, const CResidue::iterator &end_a,
      const CResidue::iterator &begin_b, const CResidue::iterator &end_b)
{
  float rmsd = 0.0;
  int count = 0;
  CResidue::iterator i,j;
  
  for (i=begin_a, j=begin_b; (i!=end_a || j!=end_b); ++i, ++j) {
    if (i->GetType () != j->GetType ())
      throw CFatalIntLibException ("Mismatch atom in rmsd computation.", 
				   __FILE__, __LINE__);
    rmsd += *i || *j;
    count ++;
  }
  
  if (i!=end_a || j!=end_b)
    throw CFatalIntLibException ("One residue is missing some atoms", 
				 __FILE__, __LINE__);
    
  return sqrt (rmsd / (float)count);
}



float 
rmsd (const CResidue::const_iterator &begin_a, const CResidue::const_iterator &end_a,
      const CResidue::const_iterator &begin_b, const CResidue::const_iterator &end_b)
{
  float rmsd = 0.0;
  int count = 0;
  CResidue::const_iterator i,j;
  
  for (i=begin_a, j=begin_b; (i!=end_a || j!=end_b); ++i, ++j) {
    if (i->GetType () != j->GetType ())
      throw CFatalIntLibException ("Mismatch atom in rmsd computation.", 
				   __FILE__, __LINE__);
    rmsd += *i || *j;
    count ++;
  }
  
  if (i!=end_a || j!=end_b)
    throw CFatalIntLibException ("One residue is missing some atoms", 
				 __FILE__, __LINE__);

  return sqrt (rmsd / (float)count);
}




float 
__rmsd_with_align_aux (CPoint3D &center_a, CPoint3D &center_b, 
		       double *r, double e0, int n, CTransfo *t)
{
  // Removing translations
  int i, j, k;
  double rr[3 * 3];

  // Calcul de RR

  for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
      {
	rr[i*3+j] = 0;
	for (k = 0; k < 3; ++k)
	  rr[i*3+j] += r[k*3+i] * r[k*3+j];
      }

  // Diagonalization

  double mu[3];
  double a[3*3];
  double b[3*3];
  int nrot;

  jacobi (rr, 3, mu, a, &nrot);

  // Tri des eigenvalues et eigenvectors

  for (i = 0; i < 2; ++i)
    for (j = i + 1; j < 3; ++j)
      if (mu[i] < mu[j])
	{
	  swap (mu[i], mu[j]);
	  swap (a[0*3+i], a[0*3+j]);
	  swap (a[1*3+i], a[1*3+j]);
	  swap (a[2*3+i], a[2*3+j]);
	}

//    for (int i = 0; i < 3; ++i)
//      cout << "mu[" << i << "] = " << mu[i] << endl;

  // a_3 = a_1 x a_2

  a[0*3+2] = a[1*3+0] * a[2*3+1] - a[2*3+0] * a[1*3+1];
  a[1*3+2] = a[2*3+0] * a[0*3+1] - a[0*3+0] * a[2*3+1];
  a[2*3+2] = a[0*3+0] * a[1*3+1] - a[1*3+0] * a[0*3+1];

  // Construction de b

  for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
      {
	b[i*3+j] = 0;
	for (k = 0; k < 3; ++k)
	  b[i*3+j] += r[i*3+k] * a[k*3+j];
      }
  
  // Normalization de b
  
  double l[2] = {0, 0};
  for (i = 0; i < 3; ++i) {
    l[0] += b[i*3+0] * b[i*3+0];
    l[1] += b[i*3+1] * b[i*3+1];
  }
  l[0] = sqrt (l[0]);
  l[1] = sqrt (l[1]);
  for (i = 0; i < 3; ++i) {
    b[i*3+0] /= l[0];
    b[i*3+1] /= l[1];
  }
  
  // b_3 = b_1 x b_2

  double right_b3[3];
  double sigma_3;

  right_b3[0] = b[1*3+0] * b[2*3+1] - b[2*3+0] * b[1*3+1];
  right_b3[1] = b[2*3+0] * b[0*3+1] - b[0*3+0] * b[2*3+1];
  right_b3[2] = b[0*3+0] * b[1*3+1] - b[1*3+0] * b[0*3+1];

  sigma_3 = (b[0*3+2] * right_b3[0] +
	     b[1*3+2] * right_b3[1] +
	     b[2*3+2] * right_b3[2]);
  if (sigma_3 < 0)
    sigma_3 = -1;
  else
    sigma_3 = +1;

  b[0*3+2] = right_b3[0];
  b[1*3+2] = right_b3[1];
  b[2*3+2] = right_b3[2];
  
  double rmsd = 2 * (e0 - sqrt (mu[0]) - sqrt (mu[1]) - sigma_3 * sqrt (mu[2])) / n;
  if (rmsd < 0)
    rmsd = 0;
  rmsd = sqrt (rmsd);

  // Construction de U

  double u[3*3];
  for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
      {
	u[i*3+j] = 0;
	for (k = 0; k < 3; ++k)
	  u[i*3+j] += b[i*3+k] * a[j*3+k];
      }
  
  CTransfo rot (u[0*3+0], u[0*3+1], u[0*3+2], 0,
		u[1*3+0], u[1*3+1], u[1*3+2], 0,
		u[2*3+0], u[2*3+1], u[2*3+2], 0);

  *t = (CTransfo ().SetTranslation (center_b) * rot *
        CTransfo ().SetTranslation (-center_a));

  return rmsd;
}



void
jacobi_rotate (double *a, int i, int j, int k, int l, int n, double s,
	       double tau)
{
  double g = a[i * n + j];
  double h = a[k * n + l];
  
  a[i * n + j] = g - s * (h + g * tau);
  a[k * n + l] = h + s * (g - h * tau);
}



void
jacobi (double *a, int n, double *d, double *v, int *nrot)
{
  int it, j, ip, iq;
  double tresh, theta, tau, t, sm, s, h, g, c;
  double *b = new double[n];
  double *z = new double[n];
  
  // Initializing to the identity matrix
  for (ip = 0; ip < n; ++ip)
    for (iq = 0; iq < n; ++iq)
      v[ip*n+iq] = (ip==iq)?1:0;

  // Initialize b and d to the diagonal of a
  for (ip = 0; ip < n; ++ip)
    {
      b[ip] = d[ip] = a[ip*n+ip];
      z[ip] = 0;
    }

  *nrot = 0;
  
  for (it = 0; it < 50; ++it)
    {
      sm = 0;
      for (ip = 0; ip < n-1; ++ip)
	for (iq = ip+1; iq < n; ++iq)
	  sm += fabs (a[ip*n+iq]);
      if (sm == 0)
	{
	  delete[] z;
	  delete[] b;
	  return;
	}
      
      if (it < 3)
	tresh = 0.2 * sm / (n*n);
      else
	tresh = 0;
      for (ip = 0; ip < n-1; ++ip)
	{
	  for (iq = ip+1; iq < n; ++iq)
	    {
	      g = (double)100 * fabs (a[ip*n+iq]);
	      if (it > 3 && (double)(fabs (d[ip])+g) == (double)(fabs (d[ip]))
		  && (double)(fabs (d[iq])+g) == (double)(fabs (d[iq])))
		a[ip*n+iq] = (double)0;
	      else 
		if (fabs (a[ip*n+iq]) > tresh)
		  {
		    h = d[iq] - d[ip];
		    if ((double)(fabs (h)+g) == (double)(fabs (h)))
		      t = (a[ip*n+iq]) / h;
		    else
		      {
			theta = (double)0.5 * h / (a[ip*n+iq]);
			t = (double)1.0 / (fabs (theta) + sqrt ((double)1.0 + theta*theta));
			if (theta < 0.0) t = -t;
		      }
		    c = (double)1.0 / sqrt ((double)1.0 + t*t);
		    s = t * c;
		    tau = s / ((double)1.0 + c);
		    h = t * a[ip*n+iq];
		    z[ip] -= h;
		    z[iq] += h;
		    d[ip] -= h;
		    d[iq] += h;
		    a[ip*n+iq] = 0.0;
		    for (j = 0; j <= ip-1; ++j)
		      jacobi_rotate(a, j, ip, j, iq, n, s, tau);
		    for (j = ip+1; j <= iq-1; ++j)
		      jacobi_rotate(a, ip, j, j, iq, n, s, tau);
		    for (j = iq+1; j < n; ++j)
		      jacobi_rotate(a, ip, j, iq, j, n, s, tau);
		    for (j = 0; j < n; ++j)
		      jacobi_rotate(v, j, ip, j, iq, n, s, tau);
		    ++(*nrot);
		  }
	    }
	}
      for (ip = 0; ip < n; ++ip)
	{
	  b[ip] += z[ip];
	  d[ip] = b[ip];
	  z[ip] = 0.0;
	}
    }
}



void
McCoreInit ()
{
  // Initializing atom globals ---------------------------------------

  a_NucleicAcid = new at_NucleicAcid;
  a_AminoAcid = new at_AminoAcid;
  a_Backbone = new at_Backbone;
  a_SideChain = new at_SideChain;
  a_Carbon = new at_Carbon;
  a_Hydrogen = new at_Hydrogen;
  a_Nitrogen = new at_Nitrogen;
  a_Phosphate = new at_Phosphate;
  a_Oxygen = new at_Oxygen;
  a_Sulfur = new at_Sulfur;
  a_Magnesium = new at_Magnesium;
  a_LonePair = new at_LonePair;
  a_Pseudo = new at_Pseudo;
  a_C1p = new at_C1p;
  a_C2p = new at_C2p;
  a_C3p = new at_C3p;
  a_C4p = new at_C4p;
  a_C5p = new at_C5p;
  a_H1p = new at_H1p;
  a_H2p = new at_H2p;
  a_H3p = new at_H3p;
  a_H4p = new at_H4p;
  a_H5p = new at_H5p;
  a_O1P = new at_O1P;
  a_O2p = new at_O2p;
  a_O2P = new at_O2P;
  a_O3p = new at_O3p;
  a_O3P = new at_O3P;
  a_O4p = new at_O4p;
  a_O5p = new at_O5p;
  a_P = new at_P;
  a_1H2p = new at_1H2p;
  a_1H5p = new at_1H5p;
  a_2H2p = new at_2H2p;
  a_2H5p = new at_2H5p;
  a_HO2p = new at_HO2p;
  a_HO3p = new at_HO3p;
  a_C2 = new at_C2;
  a_C4 = new at_C4;
  a_C5 = new at_C5;
  a_C5M = new at_C5M;
  a_C6 = new at_C6;
  a_C8 = new at_C8;
  a_H1 = new at_H1;
  a_H2 = new at_H2;
  a_H3 = new at_H3;
  a_H5 = new at_H5;
  a_H6 = new at_H6;
  a_H7 = new at_H7;
  a_H8 = new at_H8;
  a_N1 = new at_N1;
  a_N2 = new at_N2;
  a_N3 = new at_N3;
  a_N4 = new at_N4;
  a_N6 = new at_N6;
  a_N7 = new at_N7;
  a_N9 = new at_N9;
  a_O2 = new at_O2;
  a_O4 = new at_O4;
  a_O6 = new at_O6;
  a_1H2 = new at_1H2;
  a_1H4 = new at_1H4;
  a_1H5M = new at_1H5M;
  a_1H6 = new at_1H6;
  a_2H2 = new at_2H2;
  a_2H4 = new at_2H4;
  a_2H5M = new at_2H5M;
  a_2H6 = new at_2H6;
  a_3H5M = new at_3H5M;
  a_PSY = new at_PSY;
  a_PSZ = new at_PSZ;
  a_2LP6 = new at_2LP6;
  a_1LP6 = new at_1LP6;
  a_LP7 = new at_LP7;
  a_LP3 = new at_LP3;
  a_LP1 = new at_LP1;
  a_2LP2 = new at_2LP2;
  a_1LP2 = new at_1LP2;
  a_2LP4 = new at_2LP4;
  a_1LP4 = new at_1LP4;
  a_H3T = new at_H3T;
  a_H5T = new at_H5T;
  a_C = new at_C;
  a_CA = new at_CA;
  a_CB = new at_CB;
  a_CD = new at_CD;
  a_CD1 = new at_CD1;
  a_CD2 = new at_CD2;
  a_CE = new at_CE;
  a_CE1 = new at_CE1;
  a_CE2 = new at_CE2;
  a_CE3 = new at_CE3;
  a_CG = new at_CG;
  a_CG1 = new at_CG1;
  a_CG2 = new at_CG2;
  a_CH2 = new at_CH2;
  a_CZ = new at_CZ;
  a_CZ2 = new at_CZ2;
  a_CZ3 = new at_CZ3;
  a_H = new at_H;
  a_1H = new at_1H;
  a_2H = new at_2H;
  a_3H = new at_3H;
  a_HA = new at_HA;
  a_HA1 = new at_HA1;
  a_HA2 = new at_HA2;
  a_HB = new at_HB;
  a_HB1 = new at_HB1;
  a_HB2 = new at_HB2;
  a_HB3 = new at_HB3;
  a_HD1 = new at_HD1;
  a_HD2 = new at_HD2;
  a_HE = new at_HE;
  a_HE1 = new at_HE1;
  a_HE2 = new at_HE2;
  a_HE3 = new at_HE3;
  a_HG = new at_HG;
  a_HG1 = new at_HG1;
  a_HG2 = new at_HG2;
  a_HH = new at_HH;
  a_HH2 = new at_HH2;
  a_HXT = new at_HXT;
  a_HZ = new at_HZ;
  a_HZ1 = new at_HZ1;
  a_HZ2 = new at_HZ2;
  a_HZ3 = new at_HZ3;
  a_N = new at_N;
  a_ND1 = new at_ND1;
  a_ND2 = new at_ND2;
  a_NE = new at_NE;
  a_NE1 = new at_NE1;
  a_NE2 = new at_NE2;
  a_NH1 = new at_NH1;
  a_NH2 = new at_NH2;
  a_NZ = new at_NZ;
  a_O = new at_O;
  a_OD1 = new at_OD1;
  a_OD2 = new at_OD2;
  a_OE1 = new at_OE1;
  a_OE2 = new at_OE2;
  a_OG = new at_OG;
  a_OG1 = new at_OG1;
  a_OH = new at_OH;
  a_OXT = new at_OXT;
  a_SD = new at_SD;
  a_SG = new at_SG;
  a_1HD1 = new at_1HD1;
  a_1HD2 = new at_1HD2;
  a_1HE2 = new at_1HE2;
  a_1HG1 = new at_1HG1;
  a_1HG2 = new at_1HG2;
  a_1HH1 = new at_1HH1;
  a_1HH2 = new at_1HH2;
  a_2HD1 = new at_2HD1;
  a_2HD2 = new at_2HD2;
  a_2HE2 = new at_2HE2;
  a_2HG1 = new at_2HG1;
  a_2HG2 = new at_2HG2;
  a_2HH1 = new at_2HH1;
  a_2HH2 = new at_2HH2;
  a_3HD1 = new at_3HD1;
  a_3HD2 = new at_3HD2;
  a_3HG1 = new at_3HG1;
  a_3HG2 = new at_3HG2;
  a_MG = new at_MG;
  a_PSAZ = new at_PSAZ;

  // Initializing residue globals ------------------------------------

  r_NucleicAcid = new rt_NucleicAcid;
  r_AminoAcid = new rt_AminoAcid;
  r_Phosphate = new rt_Phosphate;
  r_Purine = new rt_Purine;
  r_Pyrimidine = new rt_Pyrimidine;
  r_DNA = new rt_DNA;
  r_RNA = new rt_RNA;
  r_A = new rt_A;
  r_C = new rt_C;
  r_G = new rt_G;
  r_U = new rt_U;
  r_T = new rt_T;
  r_rA = new rt_rA;
  r_rC = new rt_rC;
  r_rG = new rt_rG;
  r_rU = new rt_rU;
  r_dA = new rt_dA;
  r_dC = new rt_dC;
  r_dG = new rt_dG;
  r_dT = new rt_dT;
  r_ALA = new rt_ALA;
  r_ARG = new rt_ARG;
  r_ASN = new rt_ASN;
  r_ASP = new rt_ASP;
  r_CYS = new rt_CYS;
  r_GLN = new rt_GLN;
  r_GLU = new rt_GLU;
  r_GLY = new rt_GLY;
  r_HIS = new rt_HIS;
  r_ILE = new rt_ILE;
  r_LEU = new rt_LEU;
  r_LYS = new rt_LYS;
  r_MET = new rt_MET;
  r_PHE = new rt_PHE;
  r_PRO = new rt_PRO;
  r_SER = new rt_SER;
  r_THR = new rt_THR;
  r_TRP = new rt_TRP;
  r_TYR = new rt_TYR;
  r_VAL = new rt_VAL;

  // Initializing obligatory atom sets -------------------------------

  SetOblAtomSets ();
}



void
McCore_version ()
{
  cout << PACKAGE << " " << VERSION << endl
       << "Copyright © 2001 Université de Montréal" << endl
       << "www-lbit.iro.umontreal.ca" << endl;
}



#ifndef HAVE_STRSEP
char*
strsep (char **stringp, const char *delim)
{
  char *return_val = *stringp;
  char *to;

  if (*stringp == 0)
    return 0;

  to = strpbrk (*stringp, delim);

  if (to)
    *to++ = '\0';
  
  *stringp = to;

  return return_val;
}
#endif



char*
get_current_time (char *str)
{
  time_t tp;
  
  time (&tp);
  strftime (str, 16, "%Y/%m/%d", localtime (&tp));
  return str;
}
