//                              -*- Mode: C++ -*- 
// McCore.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Nov  9 17:54:05 2000
// Update Count     : 4
// Status           : Ok.
// 


#include <math.h>
#include <time.h>

#include "McCore.h"

#include "AtomType.h"
#include "CAtom.h"
#include "CMessageQueue.h"
#include "CResidue.h"
#include "CTransfo.h"
#include "ResidueType.h"



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
t_Atom *a_HN1 = 0;
t_Atom *a_HN2 = 0;
t_Atom *a_HN3 = 0;
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



const unsigned int hbond_nbDon[5] = { 3, 1, 2, 2, 1 };
const unsigned int hbond_nbAcc[5] = { 4, 4, 3, 3, 4 };

const float hbond_angleH_ideal = 20.0;
const float hbond_angleH_var =   20.0;

const float hbond_angleL_ideal = 20.0;
const float hbond_angleL_var =   20.0;

const float hbond_dist_ideal = 3.10;
const float hbond_dist_var =   0.50;

t_Atom *hbond_don[5][3];
t_Atom *hbond_hyd[5][3];
t_Atom *hbond_acc[5][4];
t_Atom *hbond_lop[5][4];



set< t_Atom* > gdAOblAtomSet;
set< t_Atom* > grAOblAtomSet;
set< t_Atom* > gdCOblAtomSet;
set< t_Atom* > grCOblAtomSet;
set< t_Atom* > gdGOblAtomSet;
set< t_Atom* > grGOblAtomSet;
set< t_Atom* > gdTOblAtomSet;
set< t_Atom* > grUOblAtomSet;
set< t_Atom* > gdAOptAtomSet;
set< t_Atom* > grAOptAtomSet;
set< t_Atom* > gdCOptAtomSet;
set< t_Atom* > grCOptAtomSet;
set< t_Atom* > gdGOptAtomSet;
set< t_Atom* > grGOptAtomSet;
set< t_Atom* > gdTOptAtomSet;
set< t_Atom* > grUOptAtomSet;



CMessageQueue gOut (cout, 3);



void
SetBondsParam ()
{
  hbond_don[0][0] = a_N2;
  hbond_don[0][1] = a_N2;
  hbond_don[0][2] = a_N1;
  hbond_don[1][0] = a_N3;
  hbond_don[1][1] = 0;
  hbond_don[1][2] = 0;
  hbond_don[2][0] = a_N4;
  hbond_don[2][1] = a_N4;
  hbond_don[2][2] = 0;
  hbond_don[3][0] = a_N6;
  hbond_don[3][1] = a_N6;
  hbond_don[3][2] = 0;
  hbond_don[4][0] = a_N3;
  hbond_don[4][1] = 0;
  hbond_don[4][2] = 0;
  
  hbond_hyd[0][0] = a_1H2;
  hbond_hyd[0][1] = a_2H2;
  hbond_hyd[0][2] = a_H1;
  hbond_hyd[1][0] = a_H3;
  hbond_hyd[1][1] = 0;
  hbond_hyd[1][2] = 0;
  hbond_hyd[2][0] = a_1H4;
  hbond_hyd[2][1] = a_2H4;
  hbond_hyd[2][2] = 0;
  hbond_hyd[3][0] = a_1H6;
  hbond_hyd[3][1] = a_2H6;
  hbond_hyd[3][2] = 0;
  hbond_hyd[4][0] = a_H3;
  hbond_hyd[4][1] = 0;
  hbond_hyd[4][2] = 0;

  hbond_acc[0][0] = a_N3;
  hbond_acc[0][1] = a_N7;
  hbond_acc[0][2] = a_O6;
  hbond_acc[0][3] = a_O6;
  hbond_acc[1][0] = a_O2;
  hbond_acc[1][1] = a_O2;
  hbond_acc[1][2] = a_O4;
  hbond_acc[1][3] = a_O4;
  hbond_acc[2][0] = a_N3;
  hbond_acc[2][1] = a_O2;
  hbond_acc[2][2] = a_O2;
  hbond_acc[2][3] = 0;
  hbond_acc[3][0] = a_N1;
  hbond_acc[3][1] = a_N3;
  hbond_acc[3][2] = a_N7;
  hbond_acc[3][3] = 0;
  hbond_acc[4][0] = a_O2;
  hbond_acc[4][1] = a_O2;
  hbond_acc[4][2] = a_O4;
  hbond_acc[4][3] = a_O4;

  hbond_lop[0][0] = a_LP3;
  hbond_lop[0][1] = a_LP7;
  hbond_lop[0][2] = a_1LP6;
  hbond_lop[0][3] = a_2LP6;
  hbond_lop[1][0] = a_1LP2;
  hbond_lop[1][1] = a_2LP2;
  hbond_lop[1][2] = a_1LP4;
  hbond_lop[1][3] = a_2LP4;
  hbond_lop[2][0] = a_LP3;
  hbond_lop[2][1] = a_1LP2;
  hbond_lop[2][2] = a_2LP2;
  hbond_lop[2][3] = 0;
  hbond_lop[3][0] = a_LP1;
  hbond_lop[3][1] = a_LP3;
  hbond_lop[3][2] = a_LP7;
  hbond_lop[3][3] = 0;
  hbond_lop[4][0] = a_1LP2;
  hbond_lop[4][1] = a_2LP2;
  hbond_lop[4][2] = a_1LP4;
  hbond_lop[4][3] = a_2LP4;
}



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
rmsd (const vector< residue_iterator > &mgr1,
      const vector< residue_iterator > &mgr2)
{
  float rmsd = 0;
  vector< CResidue::iterator >::const_iterator i, j;
  
  for (i = mgr1.begin (), j = mgr2.begin (); i != mgr1.end (); i++, j++)
    rmsd += **i || **j;
  return sqrt (rmsd / (float)mgr1.size ());
}



float 
rmsd_with_align (const vector< residue_iterator > &x,
		 const vector< residue_iterator > &y, 
		 CTransfo *t)
{
  // Removing translations
  CPoint3D center_a (0, 0, 0);
  CPoint3D center_b (0, 0, 0);
  int count = 0;
  vector< CResidue::iterator >::const_iterator cii, cij;
  double r[3 * 3];
  int i, j, k;
  int n = x.size ();
  double e0 = 0;
  double rr[3 * 3];

  for (cii = x.begin (), cij = y.begin ();
       cii != x.end () && cij != y.end ();
       ++cii, ++cij)
    {
      center_a += **cii;
      center_b += **cij;
      count++;
    }

  center_a /= count;
  center_b /= count;

  // Calcul de R

  for (i = 0; i < 3; ++i)
    for (j = 0; j < 3; ++j)
      r[i * 3 + j] = 0;
  
  for (k = 0; k < n; ++k)
    {
      r[0*3+0] += (y[k]->GetX () - center_b.GetX ()) * (x[k]->GetX () - center_a.GetX ());
      r[0*3+1] += (y[k]->GetX () - center_b.GetX ()) * (x[k]->GetY () - center_a.GetY ());
      r[0*3+2] += (y[k]->GetX () - center_b.GetX ()) * (x[k]->GetZ () - center_a.GetZ ());
      r[1*3+0] += (y[k]->GetY () - center_b.GetY ()) * (x[k]->GetX () - center_a.GetX ());
      r[1*3+1] += (y[k]->GetY () - center_b.GetY ()) * (x[k]->GetY () - center_a.GetY ());
      r[1*3+2] += (y[k]->GetY () - center_b.GetY ()) * (x[k]->GetZ () - center_a.GetZ ());
      r[2*3+0] += (y[k]->GetZ () - center_b.GetZ ()) * (x[k]->GetX () - center_a.GetX ());
      r[2*3+1] += (y[k]->GetZ () - center_b.GetZ ()) * (x[k]->GetY () - center_a.GetY ());
      r[2*3+2] += (y[k]->GetZ () - center_b.GetZ ()) * (x[k]->GetZ () - center_a.GetZ ());
    }
  
  // Calcul de E0
  
  for (k = 0; k < n; ++k)
    {
      e0 += ((x[k]->GetX () - center_a.GetX ()) * (x[k]->GetX () - center_a.GetX ()) +
	     (x[k]->GetY () - center_a.GetY ()) * (x[k]->GetY () - center_a.GetY ()) +
	     (x[k]->GetZ () - center_a.GetZ ()) * (x[k]->GetZ () - center_a.GetZ ()) +
	     (y[k]->GetX () - center_b.GetX ()) * (y[k]->GetX () - center_b.GetX ()) +
	     (y[k]->GetY () - center_b.GetY ()) * (y[k]->GetY () - center_b.GetY ()) +
	     (y[k]->GetZ () - center_b.GetZ ()) * (y[k]->GetZ () - center_b.GetZ ()));
    }
  e0 /= 2;

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
  a_HN1 = new at_HN1;
  a_HN2 = new at_HN2;
  a_HN3 = new at_HN3;
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

  // Initializing hbond parameters -----------------------------------

  SetBondsParam ();

  // Initializing obligatory atom sets

  SetOblAtomSets ();
}



void
McCore_version ()
{
  cout << PACKAGE << " " << VERSION << endl;
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
