//                              -*- Mode: C++ -*- 
// McCore.h
// Copyright © 2000-02 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Philippe Thibault
// Last Modified On : Tue Jun 25 10:01:19 2002
// Update Count     : 16
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


#ifndef _McCore_h_
#define _McCore_h_


#include <map.h>
#include <set.h>
#include <vector.h>
#include <function.h>
#include <string.h>

#include "AbstractResidue.h"

class t_Atom;
class t_Residue;
class Messagestream;
class CPoint3D;
class CAtom;
class CTransfo;


/**
 * @short less comparator for strings.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
struct less_string
{
  /**
   * Tests whether the first string is lexicographically less than the
   * second one.
   * @param s1 the first string.
   * @param s2 the second string.
   * @return the result of the test.
   */
  bool operator() (const char* s1, const char* s2) const
  { return strcmp (s1, s2) < 0; }
};



/**
 * @short less comparator that first dereferences the objects.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
template <class T>
struct less_deref
{
  /**
   * Tests whether the object pointed to are ordered.
   * @param x the pointer to the first object.
   * @param y the pointer to the second object.
   * @return the thruth value.
   */
  bool operator()(const T& x, const T& y) const { 
    return (x && y && *x < *y); 
  }
};



/**
 * Atomic bond fixed length (A).
 */
extern map< t_Atom*, map < t_Atom*, float > > gAtomicBond;



/**
 * Map of the Miscellaneous Atom ordered by their name.
 */
extern map< const char *, t_Atom*, less_string > gMiscAtomString;



/**
 * Map of the Miscellaneous Residue ordered by their name.
 */
extern map< const char *, t_Residue*, less_string > gMiscResidueString;



/**
 * Global nucleic acid atom type.
 */
extern t_Atom *a_NucleicAcid;



/**
 * Global protein atom type.
 */
extern t_Atom *a_AminoAcid;


/**
 * Global backbone atom type.
 */
extern t_Atom *a_Backbone;



/**
 * Global side chain atom type.
 */
extern t_Atom *a_SideChain;



/**
 * Global carbon atom type.
 */
extern t_Atom *a_Carbon;



/**
 * Global hydrogen atom type.
 */
extern t_Atom *a_Hydrogen;



/**
 * Global nitrogen atom type.
 */
extern t_Atom *a_Nitrogen;



/**
 * Global phosphate atom type.
 */
extern t_Atom *a_Phosphate;



/**
 * Global oxygen atom type.
 */
extern t_Atom *a_Oxygen;



/**
 * Global sulfur atom type.
 */
extern t_Atom *a_Sulfur;



/**
 * Global magnesium atom type.
 */
extern t_Atom *a_Magnesium;



/**
 * Global lone pair atom type.
 */
extern t_Atom *a_LonePair;



/**
 * Global pseudo atom type.
 */
extern t_Atom *a_Pseudo;



/**
 * Global C1p atom type.
 */
extern t_Atom *a_C1p;



/**
 * Global C2p atom type.
 */
extern t_Atom *a_C2p;



/**
 * Global C3p atom type.
 */
extern t_Atom *a_C3p;



/**
 * Global C4p atom type.
 */
extern t_Atom *a_C4p;



/**
 * Global C5p atom type.
 */
extern t_Atom *a_C5p;



/**
 * Global H1p atom type.
 */
extern t_Atom *a_H1p;



/**
 * Global H2p atom type.
 */
extern t_Atom *a_H2p;



/**
 * Global H3p atom type.
 */
extern t_Atom *a_H3p;



/**
 * Global H4p atom type.
 */
extern t_Atom *a_H4p;



/**
 * Global H5p atom type.
 */
extern t_Atom *a_H5p;



/**
 * Global O1P atom type.
 */
extern t_Atom *a_O1P;



/**
 * Global O2p atom type.
 */
extern t_Atom *a_O2p;



/**
 * Global O2P atom type.
 */
extern t_Atom *a_O2P;



/**
 * Global O3p atom type.
 */
extern t_Atom *a_O3p;



/**
 * Global O3P atom type.
 */
extern t_Atom *a_O3P;



/**
 * Global O4p atom type.
 */
extern t_Atom *a_O4p;



/**
 * Global O5p atom type.
 */
extern t_Atom *a_O5p;



/**
 * Global P atom type.
 */
extern t_Atom *a_P;



/**
 * Global 1H2p atom type.
 */
extern t_Atom *a_1H2p;



/**
 * Global 1H5p atom type.
 */
extern t_Atom *a_1H5p;



/**
 * Global 2H2p atom type.
 */
extern t_Atom *a_2H2p;



/**
 * Global 2H5p atom type.
 */
extern t_Atom *a_2H5p;



/**
 * Global HO2p atom type.
 */
extern t_Atom *a_HO2p;



/**
 * Global HO3p atom type.
 */
extern t_Atom *a_HO3p;



/**
 * Global C2 atom type.
 */
extern t_Atom *a_C2;



/**
 * Global C4 atom type.
 */
extern t_Atom *a_C4;



/**
 * Global C5 atom type.
 */
extern t_Atom *a_C5;



/**
 * Global C5M atom type.
 */
extern t_Atom *a_C5M;



/**
 * Global C6 atom type.
 */
extern t_Atom *a_C6;



/**
 * Global C8 atom type.
 */
extern t_Atom *a_C8;



/**
 * Global H1 atom type.
 */
extern t_Atom *a_H1;



/**
 * Global H2 atom type.
 */
extern t_Atom *a_H2;



/**
 * Global H3 atom type.
 */
extern t_Atom *a_H3;



/**
 * Global H5 atom type.
 */
extern t_Atom *a_H5;



/**
 * Global H6 atom type.
 */
extern t_Atom *a_H6;



/**
 * Global H7 atom type.
 */
extern t_Atom *a_H7;



/**
 * Global H8 atom type.
 */
extern t_Atom *a_H8;



/**
 * Global N1 atom type.
 */
extern t_Atom *a_N1;



/**
 * Global N2 atom type.
 */
extern t_Atom *a_N2;



/**
 * Global N3 atom type.
 */
extern t_Atom *a_N3;



/**
 * Global N4 atom type.
 */
extern t_Atom *a_N4;



/**
 * Global N6 atom type.
 */
extern t_Atom *a_N6;



/**
 * Global N7 atom type.
 */
extern t_Atom *a_N7;



/**
 * Global N9 atom type.
 */
extern t_Atom *a_N9;



/**
 * Global O2 atom type.
 */
extern t_Atom *a_O2;



/**
 * Global O4 atom type.
 */
extern t_Atom *a_O4;



/**
 * Global O6 atom type.
 */
extern t_Atom *a_O6;



/**
 * Global 1H2 atom type.
 */
extern t_Atom *a_1H2;



/**
 * Global 1H4 atom type.
 */
extern t_Atom *a_1H4;



/**
 * Global 1H5M atom type.
 */
extern t_Atom *a_1H5M;



/**
 * Global 1H6 atom type.
 */
extern t_Atom *a_1H6;



/**
 * Global 2H2 atom type.
 */
extern t_Atom *a_2H2;



/**
 * Global 2H4 atom type.
 */
extern t_Atom *a_2H4;



/**
 * Global 2H5M atom type.
 */
extern t_Atom *a_2H5M;



/**
 * Global 2H6 atom type.
 */
extern t_Atom *a_2H6;



/**
 * Global 3H5M atom type.
 */
extern t_Atom *a_3H5M;



/**
 * Global PSY atom type.
 */
extern t_Atom *a_PSY;



/**
 * Global PSZ atom type.
 */
extern t_Atom *a_PSZ;



/**
 * Global LP1 atom type.
 */
extern t_Atom *a_LP1;



/**
 * Global LP3 atom type.
 */
extern t_Atom *a_LP3;



/**
 * Global LP7 atom type.
 */
extern t_Atom *a_LP7;



/**
 * Global 1LP2 atom type.
 */
extern t_Atom *a_1LP2;



/**
 * Global 1LP4 atom type.
 */
extern t_Atom *a_1LP4;



/**
 * Global 1LP6 atom type.
 */
extern t_Atom *a_1LP6;



/**
 * Global 2LP2 atom type.
 */
extern t_Atom *a_2LP2;



/**
 * Global 2LP4 atom type.
 */
extern t_Atom *a_2LP4;



/**
 * Global 2LP6 atom type.
 */
extern t_Atom *a_2LP6;



/**
 * Global H3T atom type.
 */
extern t_Atom *a_H3T;



/**
 * Global H5T atom type.
 */
extern t_Atom *a_H5T;



/**
 * Global C atom type.
 */
extern t_Atom *a_C;



/**
 * Global CA atom type.
 */
extern t_Atom *a_CA;



/**
 * Global CB atom type.
 */
extern t_Atom *a_CB;



/**
 * Global CD atom type.
 */
extern t_Atom *a_CD;



/**
 * Global CD1 atom type.
 */
extern t_Atom *a_CD1;



/**
 * Global CD2 atom type.
 */
extern t_Atom *a_CD2;



/**
 * Global CE atom type.
 */
extern t_Atom *a_CE;



/**
 * Global CE1 atom type.
 */
extern t_Atom *a_CE1;



/**
 * Global CE2 atom type.
 */
extern t_Atom *a_CE2;



/**
 * Global CE3 atom type.
 */
extern t_Atom *a_CE3;



/**
 * Global CG atom type.
 */
extern t_Atom *a_CG;



/**
 * Global CG1 atom type.
 */
extern t_Atom *a_CG1;



/**
 * Global CG2 atom type.
 */
extern t_Atom *a_CG2;



/**
 * Global CH2 atom type.
 */
extern t_Atom *a_CH2;



/**
 * Global CZ atom type.
 */
extern t_Atom *a_CZ;



/**
 * Global CZ2 atom type.
 */
extern t_Atom *a_CZ2;



/**
 * Global CZ3 atom type.
 */
extern t_Atom *a_CZ3;



/**
 * Global H atom type.
 */
extern t_Atom *a_H;



/**
 * Global 1H atom type.
 */
extern t_Atom *a_1H;



/**
 * Global 2H atom type.
 */
extern t_Atom *a_2H;



/**
 * Global 3H atom type.
 */
extern t_Atom *a_3H;



/**
 * Global HA atom type.
 */
extern t_Atom *a_HA;



/**
 * Global HA1 atom type.
 */
extern t_Atom *a_HA1;



/**
 * Global HA2 atom type.
 */
extern t_Atom *a_HA2;



/**
 * Global HB atom type.
 */
extern t_Atom *a_HB;



/**
 * Global HB1 atom type.
 */
extern t_Atom *a_HB1;



/**
 * Global HB2 atom type.
 */
extern t_Atom *a_HB2;



/**
 * Global HB3 atom type.
 */
extern t_Atom *a_HB3;



/**
 * Global HD1 atom type.
 */
extern t_Atom *a_HD1;



/**
 * Global HD2 atom type.
 */
extern t_Atom *a_HD2;



/**
 * Global HE atom type.
 */
extern t_Atom *a_HE;



/**
 * Global HE1 atom type.
 */
extern t_Atom *a_HE1;



/**
 * Global HE2 atom type.
 */
extern t_Atom *a_HE2;



/**
 * Global HE3 atom type.
 */
extern t_Atom *a_HE3;



/**
 * Global HG atom type.
 */
extern t_Atom *a_HG;



/**
 * Global HG1 atom type.
 */
extern t_Atom *a_HG1;



/**
 * Global HG2 atom type.
 */
extern t_Atom *a_HG2;



/**
 * Global HH atom type.
 */
extern t_Atom *a_HH;



/**
 * Global HH2 atom type.
 */
extern t_Atom *a_HH2;



/**
 * Global HXT atom type.
 */
extern t_Atom *a_HXT;



/**
 * Global HZ atom type.
 */
extern t_Atom *a_HZ;



/**
 * Global HZ1 atom type.
 */
extern t_Atom *a_HZ1;



/**
 * Global HZ2 atom type.
 */
extern t_Atom *a_HZ2;



/**
 * Global HZ3 atom type.
 */
extern t_Atom *a_HZ3;



/**
 * Global N atom type.
 */
extern t_Atom *a_N;



/**
 * Global ND1 atom type.
 */
extern t_Atom *a_ND1;



/**
 * Global ND2 atom type.
 */
extern t_Atom *a_ND2;



/**
 * Global NE atom type.
 */
extern t_Atom *a_NE;



/**
 * Global NE1 atom type.
 */
extern t_Atom *a_NE1;



/**
 * Global NE2 atom type.
 */
extern t_Atom *a_NE2;



/**
 * Global NH1 atom type.
 */
extern t_Atom *a_NH1;



/**
 * Global NH2 atom type.
 */
extern t_Atom *a_NH2;



/**
 * Global NZ atom type.
 */
extern t_Atom *a_NZ;



/**
 * Global O atom type.
 */
extern t_Atom *a_O;



/**
 * Global OD1 atom type.
 */
extern t_Atom *a_OD1;



/**
 * Global OD2 atom type.
 */
extern t_Atom *a_OD2;



/**
 * Global OE1 atom type.
 */
extern t_Atom *a_OE1;



/**
 * Global OE2 atom type.
 */
extern t_Atom *a_OE2;



/**
 * Global OG atom type.
 */
extern t_Atom *a_OG;



/**
 * Global OG1 atom type.
 */
extern t_Atom *a_OG1;



/**
 * Global OH atom type.
 */
extern t_Atom *a_OH;



/**
 * Global OXT atom type.
 */
extern t_Atom *a_OXT;



/**
 * Global SD atom type.
 */
extern t_Atom *a_SD;



/**
 * Global SG atom type.
 */
extern t_Atom *a_SG;



/**
 * Global 1HD1 atom type.
 */
extern t_Atom *a_1HD1;



/**
 * Global 1HD2 atom type.
 */
extern t_Atom *a_1HD2;



/**
 * Global 1HE2 atom type.
 */
extern t_Atom *a_1HE2;



/**
 * Global 1HG1 atom type.
 */
extern t_Atom *a_1HG1;



/**
 * Global 1HG2 atom type.
 */
extern t_Atom *a_1HG2;



/**
 * Global 1HH1 atom type.
 */
extern t_Atom *a_1HH1;



/**
 * Global 1HH2 atom type.
 */
extern t_Atom *a_1HH2;



/**
 * Global 2HD1 atom type.
 */
extern t_Atom *a_2HD1;



/**
 * Global 2HD2 atom type.
 */
extern t_Atom *a_2HD2;



/**
 * Global 2HE2 atom type.
 */
extern t_Atom *a_2HE2;



/**
 * Global 2HG1 atom type.
 */
extern t_Atom *a_2HG1;



/**
 * Global 2HG2 atom type.
 */
extern t_Atom *a_2HG2;



/**
 * Global 2HH1 atom type.
 */
extern t_Atom *a_2HH1;



/**
 * Global 2HH2 atom type.
 */
extern t_Atom *a_2HH2;



/**
 * Global 3HD1 atom type.
 */
extern t_Atom *a_3HD1;



/**
 * Global 3HD2 atom type.
 */
extern t_Atom *a_3HD2;



/**
 * Global 3HG1 atom type.
 */
extern t_Atom *a_3HG1;



/**
 * Global 3HG2 atom type.
 */
extern t_Atom *a_3HG2;



/**
 * Global magnesium atom type.
 */
extern t_Atom *a_MG;



/**
 * Global amino acid pseudo atom type.
 */
extern t_Atom *a_PSAZ;



/**
 * Global nucleic acid residue type.
 */
extern t_Residue *r_NucleicAcid;



/**
 * Global amino acid residue type.
 */
extern t_Residue *r_AminoAcid;



/**
 * Global phosphate residue type.
 */
extern t_Residue *r_Phosphate;



/**
 * Global purine residue type.
 */
extern t_Residue *r_Purine;



/**
 * Global pyrimidine residue type.
 */
extern t_Residue *r_Pyrimidine;



/**
 * Global DNA residue type.
 */
extern t_Residue *r_DNA;



/**
 * Global RNA residue type.
 */
extern t_Residue *r_RNA;



/**
 * Global A residue type.
 */
extern t_Residue *r_A;



/**
 * Global C residue type.
 */
extern t_Residue *r_C;



/**
 * Global G residue type.
 */
extern t_Residue *r_G;



/**
 * Global U residue type.
 */
extern t_Residue *r_U;



/**
 * Global T residue type.
 */
extern t_Residue *r_T;



/**
 * Global rA residue type.
 */
extern t_Residue *r_rA;



/**
 * Global rC residue type.
 */
extern t_Residue *r_rC;



/**
 * Global rG residue type.
 */
extern t_Residue *r_rG;



/**
 * Global rU residue type.
 */
extern t_Residue *r_rU;



/**
 * Global dA residue type.
 */
extern t_Residue *r_dA;



/**
 * Global dC residue type.
 */
extern t_Residue *r_dC;



/**
 * Global dG residue type.
 */
extern t_Residue *r_dG;



/**
 * Global dT residue type.
 */
extern t_Residue *r_dT;



/**
 * Global alanine residue type.
 */
extern t_Residue *r_ALA;



/**
 * Global arginine residue type.
 */
extern t_Residue *r_ARG;



/**
 * Global asparagine residue type.
 */
extern t_Residue *r_ASN;



/**
 * Global asparticacid residue type.
 */
extern t_Residue *r_ASP;



/**
 * Global cysteine residue type.
 */
extern t_Residue *r_CYS;



/**
 * Global glutamine residue type.
 */
extern t_Residue *r_GLN;



/**
 * Global glutamicacid residue type.
 */
extern t_Residue *r_GLU;



/**
 * Global glycine residue type.
 */
extern t_Residue *r_GLY;



/**
 * Global histidine residue type.
 */
extern t_Residue *r_HIS;



/**
 * Global isoleucine residue type.
 */
extern t_Residue *r_ILE;



/**
 * Global leucine residue type.
 */
extern t_Residue *r_LEU;



/**
 * Global lysine residue type.
 */
extern t_Residue *r_LYS;



/**
 * Global methionine residue type.
 */
extern t_Residue *r_MET;



/**
 * Global phenylalanine residue type.
 */
extern t_Residue *r_PHE;



/**
 * Global proline residue type.
 */
extern t_Residue *r_PRO;



/**
 * Global serine residue type.
 */
extern t_Residue *r_SER;



/**
 * Global threonine residue type.
 */
extern t_Residue *r_THR;



/**
 * Global tryptophan residue type.
 */
extern t_Residue *r_TRP;



/**
 * Global tyrosine residue type.
 */
extern t_Residue *r_TYR;



/**
 * Global valine residue type.
 */
extern t_Residue *r_VAL;



/**
 * Set of obligatory atoms types in a dA.
 */
extern set< t_Atom* > gdAOblAtomSet;



/**
 * Set of obligatory atoms types in a rA.
 */
extern set< t_Atom* > grAOblAtomSet;



/**
 * Set of obligatory atoms types in a dC.
 */
extern set< t_Atom* > gdCOblAtomSet;



/**
 * Set of obligatory atoms types in a rC.
 */
extern set< t_Atom* > grCOblAtomSet;



/**
 * Set of obligatory atoms types in a dG.
 */
extern set< t_Atom* > gdGOblAtomSet;



/**
 * Set of obligatory atoms types in a rG.
 */
extern set< t_Atom* > grGOblAtomSet;



/**
 * Set of obligatory atoms types in a dT.
 */
extern set< t_Atom* > gdTOblAtomSet;



/**
 * Set of obligatory atoms types in a rU.
 */
extern set< t_Atom* > grUOblAtomSet;



/**
 * Set of obligatory atoms types in a ALA.
 */
extern set< t_Atom* > gALAOblAtomSet;



/**
 * Set of obligatory atoms types in a ARG.
 */
extern set< t_Atom* > gARGOblAtomSet;



/**
 * Set of obligatory atoms types in a ASN.
 */
extern set< t_Atom* > gASNOblAtomSet;



/**
 * Set of obligatory atoms types in a ASP.
 */
extern set< t_Atom* > gASPOblAtomSet;



/**
 * Set of obligatory atoms types in a CYS.
 */
extern set< t_Atom* > gCYSOblAtomSet;



/**
 * Set of obligatory atoms types in a GLN.
 */
extern set< t_Atom* > gGLNOblAtomSet;



/**
 * Set of obligatory atoms types in a GLU.
 */
extern set< t_Atom* > gGLUOblAtomSet;



/**
 * Set of obligatory atoms types in a GLY.
 */
extern set< t_Atom* > gGLYOblAtomSet;



/**
 * Set of obligatory atoms types in a HIS.
 */
extern set< t_Atom* > gHISOblAtomSet;



/**
 * Set of obligatory atoms types in a ILE.
 */
extern set< t_Atom* > gILEOblAtomSet;



/**
 * Set of obligatory atoms types in a LEU.
 */
extern set< t_Atom* > gLEUOblAtomSet;



/**
 * Set of obligatory atoms types in a LYS.
 */
extern set< t_Atom* > gLYSOblAtomSet;



/**
 * Set of obligatory atoms types in a MET.
 */
extern set< t_Atom* > gMETOblAtomSet;



/**
 * Set of obligatory atoms types in a PHE.
 */
extern set< t_Atom* > gPHEOblAtomSet;



/**
 * Set of obligatory atoms types in a PRO.
 */
extern set< t_Atom* > gPROOblAtomSet;



/**
 * Set of obligatory atoms types in a SER.
 */
extern set< t_Atom* > gSEROblAtomSet;



/**
 * Set of obligatory atoms types in a THR.
 */
extern set< t_Atom* > gTHROblAtomSet;



/**
 * Set of obligatory atoms types in a TRP.
 */
extern set< t_Atom* > gTRPOblAtomSet;



/**
 * Set of obligatory atoms types in a TYR.
 */
extern set< t_Atom* > gTYROblAtomSet;



/**
 * Set of obligatory atoms types in a VAL.
 */
extern set< t_Atom* > gVALOblAtomSet;



/**
 * Set of optional atoms types in a dA.
 */
extern set< t_Atom* > gdAOptAtomSet;



/**
 * Set of optional atoms types in a rA.
 */
extern set< t_Atom* > grAOptAtomSet;



/**
 * Set of optional atoms types in a dC.
 */
extern set< t_Atom* > gdCOptAtomSet;



/**
 * Set of optional atoms types in a rC.
 */
extern set< t_Atom* > grCOptAtomSet;



/**
 * Set of optional atoms types in a dG.
 */
extern set< t_Atom* > gdGOptAtomSet;



/**
 * Set of optional atoms types in a rG.
 */
extern set< t_Atom* > grGOptAtomSet;



/**
 * Set of optional atoms types in a dT.
 */
extern set< t_Atom* > gdTOptAtomSet;



/**
 * Set of optional atoms types in a rU.
 */
extern set< t_Atom* > grUOptAtomSet;



/**
 * Set of optional atoms types in a ALA.
 */
extern set< t_Atom* > gALAOptAtomSet;



/**
 * Set of optional atoms types in a ARG.
 */
extern set< t_Atom* > gARGOptAtomSet;



/**
 * Set of optional atoms types in a ASN.
 */
extern set< t_Atom* > gASNOptAtomSet;



/**
 * Set of optional atoms types in a ASP.
 */
extern set< t_Atom* > gASPOptAtomSet;



/**
 * Set of optional atoms types in a CYS.
 */
extern set< t_Atom* > gCYSOptAtomSet;



/**
 * Set of optional atoms types in a GLN.
 */
extern set< t_Atom* > gGLNOptAtomSet;



/**
 * Set of optional atoms types in a GLU.
 */
extern set< t_Atom* > gGLUOptAtomSet;



/**
 * Set of optional atoms types in a GLY.
 */
extern set< t_Atom* > gGLYOptAtomSet;



/**
 * Set of optional atoms types in a HIS.
 */
extern set< t_Atom* > gHISOptAtomSet;



/**
 * Set of optional atoms types in a ILE.
 */
extern set< t_Atom* > gILEOptAtomSet;



/**
 * Set of optional atoms types in a LEU.
 */
extern set< t_Atom* > gLEUOptAtomSet;



/**
 * Set of optional atoms types in a LYS.
 */
extern set< t_Atom* > gLYSOptAtomSet;



/**
 * Set of optional atoms types in a MET.
 */
extern set< t_Atom* > gMETOptAtomSet;



/**
 * Set of optional atoms types in a PHE.
 */
extern set< t_Atom* > gPHEOptAtomSet;



/**
 * Set of optional atoms types in a PRO.
 */
extern set< t_Atom* > gPROOptAtomSet;



/**
 * Set of optional atoms types in a SER.
 */
extern set< t_Atom* > gSEROptAtomSet;



/**
 * Set of optional atoms types in a THR.
 */
extern set< t_Atom* > gTHROptAtomSet;



/**
 * Set of optional atoms types in a TRP.
 */
extern set< t_Atom* > gTRPOptAtomSet;



/**
 * Set of optional atoms types in a TYR.
 */
extern set< t_Atom* > gTYROptAtomSet;



/**
 * Set of optional atoms types in a VAL.
 */
extern set< t_Atom* > gVALOptAtomSet;



/**
 * Global message system.
 */
extern Messagestream &gOut;



/**
 * Calculates the minimum of it's 2 arguments.
 * @param x the first float.
 * @param y the second float.
 * @return the minimum value.
 */
float minf (float x, float y);



/**
 * Calculates the absolute value of it's argument.
 * @param x the float.
 * @return the absolute value.
 */
float absf (float x);



/**
 * Tests whether the argument is near 0.
 * @param x the double to test.
 * @return the truth value.
 */
bool equal0 (double x);



/**
 * Calculates the arctan of it's parameters.
 * @param x the first double.
 * @param y the second double.
 * @return the arctan of 2 doubles.
 */
double arctan2 (double x, double y);



/**
 * Transforms an angle in degree to radian.
 * @param d the angle in degree.
 * @return the angle in radian.
 */
float DegToRadian (float d);



/**
 * Transforms an angle in radian to degree.
 * @param r the angle in radian.
 * @return the angle in degrees.
 */
float RadToDegree (float r);



/**
 * Calculates the rmsd between the vectors of atoms without performing an
 * alignment.
 * @param mgr1 the first vector of atoms.
 * @param mgr2 the second vector of atoms.
 * @return the rmsd value.
 */
float rmsd (const vector< AbstractResidue::iterator > &mgr1,
	    const vector< AbstractResidue::iterator > &mgr2);



/**
 * Calculates the rmsd between the atoms in the iterator range 
 * without performing an alignment.
 *@param begin_a a start iterator on the first atom container
 *@param end_a an end iterator on the first atom container
 *@param begin_b a start iterator on the second atom container
 *@param end_b an end iterator on the second atom container
 *@return the rmsd value.
 */
float rmsd (const AbstractResidue::iterator &begin_a,
	    const AbstractResidue::iterator &end_a,
	    const AbstractResidue::iterator &begin_b,
	    const AbstractResidue::iterator &end_b);



/**
 * Calculates the rmsd between the atoms in the const_iterator range 
 * without performing an alignment.
 *@param begin_a a start iterator on the first atom container
 *@param end_a an end iterator on the first atom container
 *@param begin_b a start iterator on the second atom container
 *@param end_b an end iterator on the second atom container
 *@return the rmsd value.
 */
float rmsd (const AbstractResidue::const_iterator &begin_a,
	    const AbstractResidue::const_iterator &end_a,
	    const AbstractResidue::const_iterator &begin_b,
	    const AbstractResidue::const_iterator &end_b);



/**
 * Creates a CTransfo that moves x to y, that is, if you want
 * to superimpose to structure, x must be transformed by tfo.
 * @param x the first vector of atoms.
 * @param y the second vector of atoms.
 * @param t the transfo created (default = 0).
 * @return the rmsd value.
 */
template< class T >
float rmsd_with_align (T x_begin, T x_end, 
		       T y_begin, T y_end,
		       CTransfo *t = 0) {
  // Extracting translations
  CPoint3D center_a (0, 0, 0);
  CPoint3D center_b (0, 0, 0);
  int count = 0;
  T cii, cij;
  double r[3 * 3];
  int i, j;
  double e0 = 0;

  for (cii = x_begin, cij = y_begin; cii != x_end && cij != y_end; ++cii, ++cij)
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
  
  for (cii = x_begin, cij = y_begin; cii != x_end && cij != y_end; ++cii, ++cij)
    {
      r[0*3+0] += ((*cij)->GetX () - center_b.GetX ()) * ((*cii)->GetX () - center_a.GetX ());
      r[0*3+1] += ((*cij)->GetX () - center_b.GetX ()) * ((*cii)->GetY () - center_a.GetY ());
      r[0*3+2] += ((*cij)->GetX () - center_b.GetX ()) * ((*cii)->GetZ () - center_a.GetZ ());
      r[1*3+0] += ((*cij)->GetY () - center_b.GetY ()) * ((*cii)->GetX () - center_a.GetX ());
      r[1*3+1] += ((*cij)->GetY () - center_b.GetY ()) * ((*cii)->GetY () - center_a.GetY ());
      r[1*3+2] += ((*cij)->GetY () - center_b.GetY ()) * ((*cii)->GetZ () - center_a.GetZ ());
      r[2*3+0] += ((*cij)->GetZ () - center_b.GetZ ()) * ((*cii)->GetX () - center_a.GetX ());
      r[2*3+1] += ((*cij)->GetZ () - center_b.GetZ ()) * ((*cii)->GetY () - center_a.GetY ());
      r[2*3+2] += ((*cij)->GetZ () - center_b.GetZ ()) * ((*cii)->GetZ () - center_a.GetZ ());
    }
  
  // Calcul de E0
  
  for (cii = x_begin, cij = y_begin; cii != x_end && cij != y_end; ++cii, ++cij)
    {
      e0 += (((*cii)->GetX () - center_a.GetX ()) * ((*cii)->GetX () - center_a.GetX ()) +
	     ((*cii)->GetY () - center_a.GetY ()) * ((*cii)->GetY () - center_a.GetY ()) +
	     ((*cii)->GetZ () - center_a.GetZ ()) * ((*cii)->GetZ () - center_a.GetZ ()) +
	     ((*cij)->GetX () - center_b.GetX ()) * ((*cij)->GetX () - center_b.GetX ()) +
	     ((*cij)->GetY () - center_b.GetY ()) * ((*cij)->GetY () - center_b.GetY ()) +
	     ((*cij)->GetZ () - center_b.GetZ ()) * ((*cij)->GetZ () - center_b.GetZ ()));
    }
  e0 /= 2;

  return __rmsd_with_align_aux (center_a, center_b, r, e0, count, t);
}



float __rmsd_with_align_aux (CPoint3D &center_a, CPoint3D &center_b, 
			     double *r, double e0, int n, CTransfo *t = 0);


/**
 */
void
jacobi_rotate (double *a, int i, int j, int k, int l, int n, double s,
	       double tau);



/**
 */
void jacobi (double *a, int n, double *d, double *v, int *nrot);



/**
 * Initializes the mccore library.  This method must called at the beginning
 * of the application.
 */
void McCoreInit ();



/**
 * Displays to cout the version information.
 */
void McCore_version ();



#ifndef HAVE_STRSEP
/**
 * Separates the string in tokens.  It re-implements the bogus strsep from
 * stdlib.
 * @param stringp the pointer towards the string to tokenize.
 * @param delim the token delimiter.
 * @return the token read.
 */
char* strsep (char **stringp, const char *delim);
#endif



/**
 * Gets the current time and writes it to string format "%Y/%m/%d".
 * @param str the string where is written the time.
 * @return the date string.
 */
char* get_current_time (char *str);

#endif
