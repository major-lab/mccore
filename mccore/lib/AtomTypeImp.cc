//                              -*- Mode: C++ -*-
// AtomTypeImp.cc
// Copyright © 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Oct 25 11:27:33 2001
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

#include <ctype.h>
#include <map>
#include <stdlib.h>
#include <string.h>

#include "AbstractResidue.h"
#include "AtomTypeImp.h"
#include "Binstream.h"
#include "CException.h"
#include "McCore.h"
#include "ResidueType.h"

#define T_ATOM_BIN           1
#define AT_NUCLEICACID_BIN   2
#define AT_AMINOACID_BIN     3
#define AT_BACKBONE_BIN      4
#define AT_SIDECHAIN_BIN     5
#define AT_CARBON_BIN        6
#define AT_HYDROGEN_BIN      7
#define AT_NITROGEN_BIN      8
#define AT_PHOSPHATE_BIN     9
#define AT_OXYGEN_BIN       10
#define AT_SULFUR_BIN       11
#define AT_LONEPAIR_BIN     12
#define AT_PSEUDO_BIN       13
#define AT_C1p_BIN          14
#define AT_C2p_BIN          15
#define AT_C3p_BIN          16
#define AT_C4p_BIN          17
#define AT_C5p_BIN          18
#define AT_H1p_BIN          19
#define AT_H2p_BIN          20
#define AT_H3p_BIN          21
#define AT_H4p_BIN          22
#define AT_H5p_BIN          23
#define AT_O1P_BIN          24
#define AT_O2p_BIN          25
#define AT_O2P_BIN          26
#define AT_O3p_BIN          27
#define AT_O3P_BIN          28
#define AT_O4p_BIN          29
#define AT_O5p_BIN          30
#define AT_P_BIN            31
#define AT_1H2p_BIN         32
#define AT_1H5p_BIN         33
#define AT_2H2p_BIN         34
#define AT_2H5p_BIN         35
#define AT_HO2p_BIN         36
#define AT_HO3p_BIN         37
#define AT_C2_BIN           38
#define AT_C4_BIN           39
#define AT_C5_BIN           40
#define AT_C5M_BIN          41
#define AT_C6_BIN           42
#define AT_C8_BIN           43
#define AT_H1_BIN           44
#define AT_H2_BIN           45
#define AT_H3_BIN           46
#define AT_H5_BIN           47
#define AT_H6_BIN           48
#define AT_H7_BIN           49
#define AT_H8_BIN           50
#define AT_N1_BIN           51
#define AT_N2_BIN           52
#define AT_N3_BIN           53
#define AT_N4_BIN           54
#define AT_N6_BIN           55
#define AT_N7_BIN           56
#define AT_N9_BIN           57
#define AT_O2_BIN           58
#define AT_O4_BIN           59
#define AT_O6_BIN           60
#define AT_1H2_BIN          61
#define AT_1H4_BIN          62
#define AT_1H5M_BIN         63
#define AT_1H6_BIN          64
#define AT_2H2_BIN          65
#define AT_2H4_BIN          66
#define AT_2H5M_BIN         67
#define AT_2H6_BIN          68
#define AT_3H5M_BIN         69
#define AT_PSY_BIN          70
#define AT_PSZ_BIN          71
#define AT_LP1_BIN          72
#define AT_LP3_BIN          73
#define AT_LP7_BIN          74
#define AT_1LP2_BIN         75
#define AT_1LP4_BIN         76
#define AT_1LP6_BIN         77
#define AT_2LP2_BIN         78
#define AT_2LP4_BIN         79
#define AT_2LP6_BIN         80
#define AT_H3T_BIN          81
#define AT_MISC_BIN         82
#define AT_C_BIN            83
#define AT_CA_BIN           84
#define AT_CB_BIN           85
#define AT_CD_BIN           86
#define AT_CD1_BIN          87
#define AT_CD2_BIN          88
#define AT_CE_BIN           89
#define AT_CE1_BIN          90
#define AT_CE2_BIN          91
#define AT_CE3_BIN          92
#define AT_CG_BIN           93
#define AT_CG1_BIN          94
#define AT_CG2_BIN          95
#define AT_CH2_BIN          96
#define AT_CZ_BIN           97
#define AT_CZ2_BIN          98
#define AT_CZ3_BIN          99
#define AT_H_BIN           100
#define AT_HA_BIN          101
#define AT_HA1_BIN         102
#define AT_HA2_BIN         103
#define AT_HB_BIN          104
#define AT_HB1_BIN         105
#define AT_HB2_BIN         106
#define AT_HB3_BIN         107
#define AT_HD1_BIN         108
#define AT_HD2_BIN         109
#define AT_HE_BIN          110
#define AT_HE1_BIN         111
#define AT_HE2_BIN         112
#define AT_HE3_BIN         113
#define AT_HG_BIN          114
#define AT_HG1_BIN         115
#define AT_HG2_BIN         116
#define AT_HH_BIN          117
#define AT_HH2_BIN         118
#define AT_HXT_BIN         122
#define AT_HZ_BIN          123
#define AT_HZ1_BIN         124
#define AT_HZ2_BIN         125
#define AT_HZ3_BIN         126
#define AT_N_BIN           127
#define AT_ND1_BIN         128
#define AT_ND2_BIN         129
#define AT_NE_BIN          130
#define AT_NE1_BIN         131
#define AT_NE2_BIN         132
#define AT_NH1_BIN         133
#define AT_NH2_BIN         134
#define AT_NZ_BIN          135
#define AT_O_BIN           136
#define AT_OD1_BIN         137
#define AT_OD2_BIN         138
#define AT_OE1_BIN         139
#define AT_OE2_BIN         140
#define AT_OG_BIN          141
#define AT_OG1_BIN         142
#define AT_OH_BIN          143
#define AT_OXT_BIN         144
#define AT_SD_BIN          145
#define AT_SG_BIN          146
#define AT_1HD1_BIN        147
#define AT_1HD2_BIN        148
#define AT_1HE2_BIN        149
#define AT_1HG1_BIN        150
#define AT_1HG2_BIN        151
#define AT_1HH1_BIN        152
#define AT_1HH2_BIN        153
#define AT_2HD1_BIN        154
#define AT_2HD2_BIN        155
#define AT_2HE2_BIN        156
#define AT_2HG1_BIN        157
#define AT_2HG2_BIN        158
#define AT_2HH1_BIN        159
#define AT_2HH2_BIN        160
#define AT_3HD1_BIN        161
#define AT_3HD2_BIN        162
#define AT_3HG1_BIN        163
#define AT_3HG2_BIN        164
#define AT_MAGNESIUM_BIN   165
#define AT_MG_BIN          166
#define AT_1H_BIN          167
#define AT_2H_BIN          168
#define AT_3H_BIN          169
#define AT_H5T_BIN         170
#define AT_PSAZ_BIN        171

using namespace std;



void
t_Atom::Binoutput (oBinstream &obs) const
{
  obs << char (T_ATOM_BIN);
}



oBinstream&
operator<< (oBinstream &obs, const t_Atom *t)
{
  t->Binoutput (obs);
  return obs;
}



iBinstream&
operator>> (iBinstream &ibs, t_Atom *&t)
{
  int id;
  char buf[256];
  char buf2[8];
  map< const char *, t_Atom*, less_string >::iterator pos;
  
  ibs >> id;
  switch (id)
    {
    case AT_NUCLEICACID_BIN:
      t = a_NucleicAcid;
      break;
    case AT_AMINOACID_BIN:
      t = a_AminoAcid;
      break;
    case AT_BACKBONE_BIN:
      t = a_Backbone;
      break;
    case AT_SIDECHAIN_BIN:
      t = a_SideChain;
      break;
    case AT_CARBON_BIN:
      t = a_Carbon;
      break;
    case AT_HYDROGEN_BIN:
      t = a_Hydrogen;
      break;
    case AT_NITROGEN_BIN:
      t = a_Nitrogen;
      break;
    case AT_PHOSPHATE_BIN:
      t = a_Phosphate;
      break;
    case AT_OXYGEN_BIN:
      t = a_Oxygen;
      break;
    case AT_SULFUR_BIN:
      t = a_Sulfur;
      break;
    case AT_LONEPAIR_BIN:
      t = a_LonePair;
      break;
    case AT_PSEUDO_BIN:
      t = a_Pseudo;
      break;
    case AT_C1p_BIN:
      t = a_C1p;
      break;
    case AT_C2p_BIN:
      t = a_C2p;
      break;
    case AT_C3p_BIN:
      t = a_C3p;
      break;
    case AT_C4p_BIN:
      t = a_C4p;
      break;
    case AT_C5p_BIN:
      t = a_C5p;
      break;
    case AT_H1p_BIN:
      t = a_H1p;
      break;
    case AT_H2p_BIN:
      t = a_H2p;
      break;
    case AT_H3p_BIN:
      t = a_H3p;
      break;
    case AT_H4p_BIN:
      t = a_H4p;
      break;
    case AT_H5p_BIN:
      t = a_H5p;
      break;
    case AT_O1P_BIN:
      t = a_O1P;
      break;
    case AT_O2p_BIN:
      t = a_O2p;
      break;
    case AT_O2P_BIN:
      t = a_O2P;
      break;
    case AT_O3p_BIN:
      t = a_O3p;
      break;
    case AT_O3P_BIN:
      t = a_O3P;
      break;
    case AT_O4p_BIN:
      t = a_O4p;
      break;
    case AT_O5p_BIN:
      t = a_O5p;
      break;
    case AT_P_BIN:
      t = a_P;
      break;
    case AT_1H2p_BIN:
      t = a_1H2p;
      break;
    case AT_1H5p_BIN:
      t = a_1H5p;
      break;
    case AT_2H2p_BIN:
      t = a_2H2p;
      break;
    case AT_2H5p_BIN:
      t = a_2H5p;
      break;
    case AT_HO2p_BIN:
      t = a_HO2p;
      break;
    case AT_HO3p_BIN:
      t = a_HO3p;
      break;
    case AT_C2_BIN:
      t = a_C2;
      break;
    case AT_C4_BIN:
      t = a_C4;
      break;
    case AT_C5_BIN:
      t = a_C5;
      break;
    case AT_C5M_BIN:
      t = a_C5M;
      break;
    case AT_C6_BIN:
      t = a_C6;
      break;
    case AT_C8_BIN:
      t = a_C8;
      break;
    case AT_H1_BIN:
      t = a_H1;
      break;
    case AT_H2_BIN:
      t = a_H2;
      break;
    case AT_H3_BIN:
      t = a_H3;
      break;
    case AT_H5_BIN:
      t = a_H5;
      break;
    case AT_H6_BIN:
      t = a_H6;
      break;
    case AT_H7_BIN:
      t = a_H7;
      break;
    case AT_H8_BIN:
      t = a_H8;
      break;
    case AT_N1_BIN:
      t = a_N1;
      break;
    case AT_N2_BIN:
      t = a_N2;
      break;
    case AT_N3_BIN:
      t = a_N3;
      break;
    case AT_N4_BIN:
      t = a_N4;
      break;
    case AT_N6_BIN:
      t = a_N6;
      break;
    case AT_N7_BIN:
      t = a_N7;
      break;
    case AT_N9_BIN:
      t = a_N9;
      break;
    case AT_O2_BIN:
      t = a_O2;
      break;
    case AT_O4_BIN:
      t = a_O4;
      break;
    case AT_O6_BIN:
      t = a_O6;
      break;
    case AT_1H2_BIN:
      t = a_1H2;
      break;
    case AT_1H4_BIN:
      t = a_1H4;
      break;
    case AT_1H5M_BIN:
      t = a_1H5M;
      break;
    case AT_1H6_BIN:
      t = a_1H6;
      break;
    case AT_2H2_BIN:
      t = a_2H2;
      break;
    case AT_2H4_BIN:
      t = a_2H4;
      break;
    case AT_2H5M_BIN:
      t = a_2H5M;
      break;
    case AT_2H6_BIN:
      t = a_2H6;
      break;
    case AT_3H5M_BIN:
      t = a_3H5M;
      break;
    case AT_PSY_BIN:
      t = a_PSY;
      break;
    case AT_PSZ_BIN:
      t = a_PSZ;
      break;
    case AT_LP1_BIN:
      t = a_LP1;
      break;
    case AT_LP3_BIN:
      t = a_LP3;
      break;
    case AT_LP7_BIN:
      t = a_LP7;
      break;
    case AT_1LP2_BIN:
      t = a_1LP2;
      break;
    case AT_1LP4_BIN:
      t = a_1LP4;
      break;
    case AT_1LP6_BIN:
      t = a_1LP6;
      break;
    case AT_2LP2_BIN:
      t = a_2LP2;
      break;
    case AT_2LP4_BIN:
      t = a_2LP4;
      break;
    case AT_2LP6_BIN:
      t = a_2LP6;
      break;
    case AT_H3T_BIN:
      t = a_H3T;
      break;
    case AT_MISC_BIN:
      ibs >> buf >> buf2;
      pos = gMiscAtomString.find (buf);
      if (pos == gMiscAtomString.end ())
	t = new at_Misc (buf, buf2);
      else
	t = pos->second;
      break;
    case AT_C_BIN:
      t = a_C;
      break;
    case AT_CA_BIN:
      t = a_CA;
      break;
    case AT_CB_BIN:
      t = a_CB;
      break;
    case AT_CD_BIN:
      t = a_CD;
      break;
    case AT_CD1_BIN:
      t = a_CD1;
      break;
    case AT_CD2_BIN:
      t = a_CD2;
      break;
    case AT_CE_BIN:
      t = a_CE;
      break;
    case AT_CE1_BIN:
      t = a_CE1;
      break;
    case AT_CE2_BIN:
      t = a_CE2;
      break;
    case AT_CE3_BIN:
      t = a_CE3;
      break;
    case AT_CG_BIN:
      t = a_CG;
      break;
    case AT_CG1_BIN:
      t = a_CG1;
      break;
    case AT_CG2_BIN:
      t = a_CG2;
      break;
    case AT_CH2_BIN:
      t = a_CH2;
      break;
    case AT_CZ_BIN:
      t = a_CZ;
      break;
    case AT_CZ2_BIN:
      t = a_CZ2;
      break;
    case AT_CZ3_BIN:
      t = a_CZ3;
      break;
    case AT_H_BIN:
      t = a_H;
      break;
    case AT_HA_BIN:
      t = a_HA;
      break;
    case AT_HA1_BIN:
      t = a_HA1;
      break;
    case AT_HA2_BIN:
      t = a_HA2;
      break;
    case AT_HB_BIN:
      t = a_HB;
      break;
    case AT_HB1_BIN:
      t = a_HB1;
      break;
    case AT_HB2_BIN:
      t = a_HB2;
      break;
    case AT_HB3_BIN:
      t = a_HB3;
      break;
    case AT_HD1_BIN:
      t = a_HD1;
      break;
    case AT_HD2_BIN:
      t = a_HD2;
      break;
    case AT_HE_BIN:
      t = a_HE;
      break;
    case AT_HE1_BIN:
      t = a_HE1;
      break;
    case AT_HE2_BIN:
      t = a_HE2;
      break;
    case AT_HE3_BIN:
      t = a_HE3;
      break;
    case AT_HG_BIN:
      t = a_HG;
      break;
    case AT_HG1_BIN:
      t = a_HG1;
      break;
    case AT_HG2_BIN:
      t = a_HG2;
      break;
    case AT_HH_BIN:
      t = a_HH;
      break;
    case AT_HH2_BIN:
      t = a_HH2;
      break;
    case AT_HXT_BIN:
      t = a_HXT;
      break;
    case AT_HZ_BIN:
      t = a_HZ;
      break;
    case AT_HZ1_BIN:
      t = a_HZ1;
      break;
    case AT_HZ2_BIN:
      t = a_HZ2;
      break;
    case AT_HZ3_BIN:
      t = a_HZ3;
      break;
    case AT_N_BIN:
      t = a_N;
      break;
    case AT_ND1_BIN:
      t = a_ND1;
      break;
    case AT_ND2_BIN:
      t = a_ND2;
      break;
    case AT_NE_BIN:
      t = a_NE;
      break;
    case AT_NE1_BIN:
      t = a_NE1;
      break;
    case AT_NE2_BIN:
      t = a_NE2;
      break;
    case AT_NH1_BIN:
      t = a_NH1;
      break;
    case AT_NH2_BIN:
      t = a_NH2;
      break;
    case AT_NZ_BIN:
      t = a_NZ;
      break;
    case AT_O_BIN:
      t = a_O;
      break;
    case AT_OD1_BIN:
      t = a_OD1;
      break;
    case AT_OD2_BIN:
      t = a_OD2;
      break;
    case AT_OE1_BIN:
      t = a_OE1;
      break;
    case AT_OE2_BIN:
      t = a_OE2;
      break;
    case AT_OG_BIN:
      t = a_OG;
      break;
    case AT_OG1_BIN:
      t = a_OG1;
      break;
    case AT_OH_BIN:
      t = a_OH;
      break;
    case AT_OXT_BIN:
      t = a_OXT;
      break;
    case AT_SD_BIN:
      t = a_SD;
      break;
    case AT_SG_BIN:
      t = a_SG;
      break;
    case AT_1HD1_BIN:
      t = a_1HD1;
      break;
    case AT_1HD2_BIN:
      t = a_1HD2;
      break;
    case AT_1HE2_BIN:
      t = a_1HE2;
      break;
    case AT_1HG1_BIN:
      t = a_1HG1;
      break;
    case AT_1HG2_BIN:
      t = a_1HG2;
      break;
    case AT_1HH1_BIN:
      t = a_1HH1;
      break;
    case AT_1HH2_BIN:
      t = a_1HH2;
      break;
    case AT_2HD1_BIN:
      t = a_2HD1;
      break;
    case AT_2HD2_BIN:
      t = a_2HD2;
      break;
    case AT_2HE2_BIN:
      t = a_2HE2;
      break;
    case AT_2HG1_BIN:
      t = a_2HG1;
      break;
    case AT_2HG2_BIN:
      t = a_2HG2;
      break;
    case AT_2HH1_BIN:
      t = a_2HH1;
      break;
    case AT_2HH2_BIN:
      t = a_2HH2;
      break;
    case AT_3HD1_BIN:
      t = a_3HD1;
      break;
    case AT_3HD2_BIN:
      t = a_3HD2;
      break;
    case AT_3HG1_BIN:
      t = a_3HG1;
      break;
    case AT_3HG2_BIN:
      t = a_3HG2;
      break;
    case AT_MAGNESIUM_BIN:
      t = a_Magnesium;
      break;
    case AT_MG_BIN:
      t = a_MG;
      break;
    case AT_1H_BIN:
      t = a_1H;
      break;
    case AT_2H_BIN:
      t = a_2H;
      break;
    case AT_3H_BIN:
      t = a_3H;
      break;
    case AT_H5T_BIN:
      t = a_H5T;
      break;
    case AT_PSAZ_BIN:
      t = a_PSAZ;
      break;
    default:
      t = 0;
    }
  return ibs;
}



char
at_Misc::GetFirstAlpha () const
{
  const char *p = mName;
  
  while (*p)
    {
      if (isalpha (*p))
	return *p;
      ++p;
    }
  return 0;
}



at_Misc::at_Misc (const char *sn, const char *n)
{
  strcpy (mSName, sn);
  strcpy (mName, n);
  gMiscAtomString[mSName] = this;
}



at_Misc::at_Misc (const at_Misc &right)
{
  strcpy (mSName, right.mSName);
  strcpy (mName, right.mName);
}



const at_Misc&
at_Misc::operator= (const at_Misc &right)
{
  if (this != &right)
    {
      t_Atom::operator= (right);
      strcpy (mSName, right.mSName);
      strcpy (mName, right.mName);
    }
  return *this;
}



void
at_Misc::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_MISC_BIN << mSName << mName;
}



const at_NucleicAcid&
at_NucleicAcid::operator= (const at_NucleicAcid &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}

      
void
at_NucleicAcid::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NUCLEICACID_BIN;
}



const at_AminoAcid&
at_AminoAcid::operator= (const at_AminoAcid &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_AminoAcid::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_AMINOACID_BIN;
}



const at_Backbone&
at_Backbone::operator= (const at_Backbone &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}


      
void
at_Backbone::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_BACKBONE_BIN;
}



const at_SideChain&
at_SideChain::operator= (const at_SideChain &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_SideChain::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_SIDECHAIN_BIN;
}



const at_Carbon&
at_Carbon::operator= (const at_Carbon &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Carbon::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CARBON_BIN;
}



const at_Hydrogen&
at_Hydrogen::operator= (const at_Hydrogen &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Hydrogen::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HYDROGEN_BIN;
}



const at_Nitrogen&
at_Nitrogen::operator= (const at_Nitrogen &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Nitrogen::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NITROGEN_BIN;
}



const at_Phosphate&
at_Phosphate::operator= (const at_Phosphate &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Phosphate::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_PHOSPHATE_BIN;
}



const at_Oxygen&
at_Oxygen::operator= (const at_Oxygen &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Oxygen::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OXYGEN_BIN;
}



const at_Sulfur&
at_Sulfur::operator= (const at_Sulfur &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Sulfur::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_SULFUR_BIN;
}



const at_Magnesium&
at_Magnesium::operator= (const at_Magnesium &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Magnesium::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_MAGNESIUM_BIN;
}



const at_LonePair&
at_LonePair::operator= (const at_LonePair &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_LonePair::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_LONEPAIR_BIN;
}



const at_Pseudo&
at_Pseudo::operator= (const at_Pseudo &right)
{
  if (this != &right)
    t_Atom::operator= (right);
  return *this;
}



void
at_Pseudo::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_PSEUDO_BIN;
}



const at_C1p&
at_C1p::operator= (const at_C1p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_C1p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C2p () || type->is_O4p () || type->is_H1p ()
	  || (res->is_Purine () && type->is_N9 ())
	  || (res->is_Pyrimidine () && type->is_N1 ()));
}



float
at_C1p::getAmberCharge (const AbstractResidue *res) const
{
  const t_Residue *r = res->GetType ();
  
  if (r->is_rA ())      return 0.0394;
  else if (r->is_dA ()) return 0.0431;
  else if (r->is_rC ()) return 0.0066;
  else if (r->is_dC ()) return -0.0116;
  else if (r->is_rG ()) return 0.0191;
  else if (r->is_dG ()) return 0.0358;
  else if (r->is_rU ()) return 0.0674;
  else if (r->is_dT ()) return 0.0680;
  else                  return 0;
}



void
at_C1p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C1p_BIN;
}



const at_C2p&
at_C2p::operator= (const at_C2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_C2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C1p () || type->is_O2p () || type->is_C3p ()
	  || type->is_H2p () || type->is_1H2p () || type->is_2H2p ());
}



float
at_C2p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_RNA ())
    return 0.0670;
  else if (res->GetType ()->is_DNA ())
    return -0.0854;
  else
    return 0;
}



void
at_C2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C2p_BIN;
}



const at_C3p&
at_C3p::operator= (const at_C3p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_C3p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C2p () || type->is_O3p () || type->is_C4p ()
	  || type->is_H3p ());
}



float
at_C3p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_RNA ())
    return 0.2022;
  else if (res->GetType ()->is_DNA ())
    return 0.0713;
  else
    return 0;
}



void
at_C3p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C3p_BIN;
}



const at_C4p&
at_C4p::operator= (const at_C4p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_C4p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_O4p () || type->is_C3p () || type->is_C5p ()
	  || type->is_H4p ());
}



float
at_C4p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_RNA ())
    return 0.1065;
  else if (res->GetType ()->is_DNA ())
    return 0.1629;
  else
    return 0;
}



void
at_C4p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C4p_BIN;
}



const at_C5p&
at_C5p::operator= (const at_C5p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_C5p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C4p () || type->is_O5p () || type->is_1H5p ()
	  || type->is_2H5p ());
}



float
at_C5p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_RNA ())
    return 0.0558;
  else if (res->GetType ()->is_DNA ())
    return -0.0069;
  else
    return 0;
}



void
at_C5p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C5p_BIN;
}



const at_H1p&
at_H1p::operator= (const at_H1p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H1p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C1p ();
}



float
at_H1p::getAmberCharge (const AbstractResidue *res) const
{
  const t_Residue *r = res->GetType ();
  
  if (r->is_dA ())
    return 0.1838;
  else if (r->is_rA ())
    return 0.2007;
  else if (r->is_dC ())
    return 0.1963;
  else if (r->is_rC ())
    return 0.2029;
  else if (r->is_dG ())
    return 0.1746;
  else if (r->is_rG ())
    return 0.2006;
  else if (r->is_dT ())
    return 0.1804;
  else if (r->is_rU ())
    return 0.1824;
  else
    return 0;
}



void
at_H1p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H1p_BIN;
}



const at_H2p&
at_H2p::operator= (const at_H2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C2p ();
}



float
at_H2p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.0718;
  else if (res->GetType ()->is_RNA ())
    return 0.0972;
  else
    return 0;
}



void
at_H2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H2p_BIN;
}



const at_H3p&
at_H3p::operator= (const at_H3p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H3p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C3p ();
}



float
at_H3p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.0985;
  else if (res->GetType ()->is_RNA ())
    return 0.0615;
  else
    return 0;
}



void
at_H3p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H3p_BIN;
}



const at_H4p&
at_H4p::operator= (const at_H4p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H4p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C4p ();
}



float
at_H4p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.1176;
  else if (res->GetType ()->is_RNA ())
    return 0.1174;
  else
    return 0;
}



void
at_H4p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H4p_BIN;
}



const at_H5p&
at_H5p::operator= (const at_H5p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H5p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O5p ();
}



float
at_H5p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.0754;
  else if (res->GetType ()->is_RNA ())
    return 0.0679;
  else
    return 0;
}



void
at_H5p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H5p_BIN;
}



const at_O1P&
at_O1P::operator= (const at_O1P &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O1P::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_P ();
}



float
at_O1P::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return -0.7761;
  else if (res->GetType ()->is_RNA ())
    return -0.7760;
  else
    return 0;
}



void
at_O1P::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O1P_BIN;
}



const at_O2p&
at_O2p::operator= (const at_O2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C2p () || type->is_HO2p ();
}



float
at_O2p::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_RNA ())
    return -0.6139;
  else
    return 0;
}



void
at_O2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O2p_BIN;
}



const at_O2P&
at_O2P::operator= (const at_O2P &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O2P::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_P ();
}



float
at_O2P::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return -0.7761;
  else if (res->GetType ()->is_RNA ())
    return -0.7760;
  else
    return 0;
}



void
at_O2P::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O2P_BIN;
}



const at_O3p&
at_O3p::operator= (const at_O3p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O3p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C3p () || type->is_HO3p () || type->is_H3T ()
	  || (type->is_P () && res->is_Phosphate ()));
}



float
at_O3p::getVDWR (const AbstractResidue *res) const
{
  return res->find (a_H3T) != res->end () ? 1.7210 : 1.6837;
}



float
at_O3p::getAmberEpsilon (const AbstractResidue *res) const
{
  return res->find (a_H3T) != res->end () ? 0.2104 : 0.1700;
}



float
at_O3p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();
  
  if (res->find (a_H3T) == res->end ())
    {
      if (r->is_DNA ())
	return -0.5232;
      else if (r->is_RNA ())
	return -0.5246;
    }
  else
    {
      if (r->is_DNA ())
	return -0.6549;
      else if (r->is_RNA ())
	return -0.6541;
    }
  return 0;
}



void
at_O3p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O3p_BIN;
}



const at_O3P&
at_O3P::operator= (const at_O3P &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O3P::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_P ();
}



float
at_O3P::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return -0.7761;
  else if (res->GetType ()->is_RNA ())
    return -0.7760;
  else
    return 0;
}



void
at_O3P::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O3P_BIN;
}



const at_O4p&
at_O4p::operator= (const at_O4p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O4p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C1p () || type->is_C4p ();
}



float
at_O4p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();
  
  if (r->is_DNA ())
    return -0.3691;
  else if (r->is_RNA ())
    return -0.3548;
  else
    return 0;
}



void
at_O4p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O4p_BIN;
}



const at_O5p&
at_O5p::operator= (const at_O5p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O5p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5p () || type->is_P () || type->is_H5T ();
}



float
at_O5p::getVDWR (const AbstractResidue *res) const
{
  return res->find (a_H5T) != res->end () ? 1.7210 : 1.6837;
}



float
at_O5p::getAmberEpsilon (const AbstractResidue *res) const
{
  return res->find (a_H5T) != res->end () ? 0.2104 : 0.1700;
}



float
at_O5p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (res->find (a_H5T) != res->end ())
    {
      if (r->is_DNA ())
	return -0.6318;
      else if (r->is_RNA ())
	return -0.6223;
    }
  else
    {
      if (r->is_DNA ())
	return -0.4954;
      else if (r->is_RNA ())
	return -0.4989;
    }
  return 0;
}



void
at_O5p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O5p_BIN;
}



const at_P&
at_P::operator= (const at_P &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Phosphate::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_P::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_O1P () || type->is_O2P () || type->is_O5p ()
	  || (type->is_O3p () && res->is_Phosphate ()));
}



float
at_P::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    return 1.1659;
  else if (r->is_RNA ())
    return 1.1662;
  return 0;
}



void
at_P::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_P_BIN;
}



const at_1H2p&
at_1H2p::operator= (const at_1H2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_1H2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C2p ();
}



float
at_1H2p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    return 0.0718;
  else if (r->is_RNA ())
    return 0.0972;
  return 0;
}



void
at_1H2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H2p_BIN;
}



const at_1H5p&
at_1H5p::operator= (const at_1H5p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_1H5p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5p ();
}



float
at_1H5p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    return 0.0754;
  else if (r->is_RNA ())
    return 0.0679;
  return 0;
}



void
at_1H5p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H5p_BIN;
}



const at_2H2p&
at_2H2p::operator= (const at_2H2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_2H2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C2p ();
}



float
at_2H2p::getAmberCharge (const AbstractResidue *res) const
{
  return 0.0718;
}



void
at_2H2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H2p_BIN;
}



const at_2H5p&
at_2H5p::operator= (const at_2H5p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_2H5p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5p ();
}



float
at_2H5p::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    return 0.0754;
  else if (r->is_RNA ())
    return 0.0679;
  return 0;
}



void
at_2H5p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H5p_BIN;
}



const at_HO2p&
at_HO2p::operator= (const at_HO2p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_HO2p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O2p ();
}



float
at_HO2p::getAmberCharge (const AbstractResidue *res) const
{
  return 0.4186;
}



void
at_HO2p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HO2p_BIN;
}



const at_HO3p&
at_HO3p::operator= (const at_HO3p &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_HO3p::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O3p ();
}



void
at_HO3p::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HO3p_BIN;
}



const at_C2&
at_C2::operator= (const at_C2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_N1 () || type->is_N3 () || type->is_O2 ()
	  || type->is_N2 () || type->is_H2 ());
}



float
at_C2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.5716;
      else if (r->is_T ())
	return 0.5677;
      else if (r->is_G ())
	return 0.7432;
      else if (r->is_C ())
	return 0.7959;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return 0.5875;
      else if (r->is_U ())
	return 0.4687;
      else if (r->is_G ())
	return 0.7657;
      else if (r->is_C ())
	return 0.7538;
    }
  return 0;
}



void
at_C2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C2_BIN;
}



const at_C4&
at_C4::operator= (const at_C4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_N3 () || type->is_N4 () || type->is_C5 () 
	  || type->is_O4 () || type->is_N9 ());
}



float
at_C4::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.3800;
      else if (r->is_T ())
	return 0.5194;
      else if (r->is_G ())
	return 0.1814;
      else if (r->is_C ())
	return 0.8439;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return 0.3053;
      else if (r->is_C ())
	return 0.8185;
      else if (r->is_G ())
	return 0.1222;
      else if (r->is_U ())
	return 0.5952;
    }
  return 0;
}



void
at_C4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C4_BIN;
}



const at_C5&
at_C5::operator= (const at_C5 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C5::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C4 () || type->is_C6 () || type->is_H5 () 
	  || type->is_N7 () || type->is_C5M ());
}



float
at_C5::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.0725;
      else if (r->is_T ())
	return 0.0025;
      else if (r->is_G ())
	return 0.1991;
      else if (r->is_C ())
	return -0.5222;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return  0.0515;
      else if (r->is_C ())
	return -0.5215;
      else if (r->is_G ())
	return  0.1744;
      else if (r->is_U ())
	return -0.3635;
    }
  return 0;
}



void
at_C5::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C5_BIN;
}



const at_C5M&
at_C5M::operator= (const at_C5M &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C5M::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C5 () || type->is_1H5M () || type->is_2H5M ()
	  || type->is_3H5M ());
}



void
at_C5M::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C5M_BIN;
}



const at_C6&
at_C6::operator= (const at_C6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C5 () || type->is_N1 () || type->is_H6 ()
	  || type->is_O6 () || type->is_N6 ());
}



float
at_C6::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.6897;
      else if (r->is_T ())
	return -0.2209;
      else if (r->is_G ())
	return 0.4918;
      else if (r->is_C ())
	return -0.0183;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return  0.7009;
      else if (r->is_C ())
	return 0.0053;
      else if (r->is_G ())
	return 0.4770;
      else if (r->is_U ())
	return -0.1126;
    }
  return 0;
}



void
at_C6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C6_BIN;
}



const at_C8&
at_C8::operator= (const at_C8 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_C8::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N7 () || type->is_H8 () || type->is_N9 ();
}



float
at_C8::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.1607;
      else if (r->is_G ())
	return 0.0736;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return 0.2006;
      else if (r->is_G ())
	return 0.1374;
    }
  return 0;
}



void
at_C8::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C8_BIN;
}



const at_H1&
at_H1::operator= (const at_H1 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N1 ();
}



float
at_H1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dG ())
    return 0.3520;
  else if (res->GetType ()->is_rG ())
    return 0.3424;
  return 0;
}



void
at_H1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H1_BIN;
}



const at_H2&
at_H2::operator= (const at_H2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O2 () || type->is_C2 ();
}



float
at_H2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dA ())
    return 0.0598;
  else if (res->GetType ()->is_rA ())
    return 0.0473;
  return 0;
}



void
at_H2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H2_BIN;
}



const at_H3&
at_H3::operator= (const at_H3 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N3 ();
}



float
at_H3::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_T ())
    return 0.3420;
  else if (res->GetType ()->is_U ())
    return 0.3154;
  return 0;
}



void
at_H3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H3_BIN;
}



const at_H5&
at_H5::operator= (const at_H5 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H5::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5 ();
}



float
at_H5::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_dC ())
    return 0.1863;
  else if (r->is_rC ())
    return 0.1928;
  else if (r->is_rU ())
    return 0.1811;
  return 0;
}



void
at_H5::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H5_BIN;
}



const at_H6&
at_H6::operator= (const at_H6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C6 ();
}



float
at_H6::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_T ())
	return 0.2607;
      else if (r->is_C ())
	return 0.2293;
    }
  else if (r->is_RNA ())
    {
      if (r->is_C ())
	return 0.1958;
      else if (r->is_U ())
	return 0.2188;
    }
  return 0;
}



void
at_H6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H6_BIN;
}



const at_H7&
at_H7::operator= (const at_H7 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H7::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N7 ();
}



void
at_H7::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H7_BIN;
}



const at_H8&
at_H8::operator= (const at_H8 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_H8::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C8 ();
}



float
at_H8::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.1877;
      else if (r->is_G ())
	return 0.1997;
    }
  else if (r->is_DNA ())
    {
      if (r->is_A ())
	return 0.1553;
      else if (r->is_G ())
	return 0.1640;
    }
  return 0;
}



void
at_H8::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H8_BIN;
}



const at_N1&
at_N1::operator= (const at_N1 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C6 () || type->is_C2 () || type->is_H1 () || type->is_LP1 ()
	  || (type->is_C1p () && res->is_Pyrimidine ()));
}



float
at_N1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return -0.7624;
      else if (r->is_T ())
	return -0.0239;
      else if (r->is_G ())
	return -0.5053;
      else if (r->is_C ())
	return -0.0339;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return -0.7615;
      else if (r->is_C ())
	return -0.0484;
      else if (r->is_G ())
	return -0.4787;
      else if (r->is_U ())
	return 0.0418;
    }
  return 0;
}



void
at_N1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N1_BIN;
}



const at_N2&
at_N2::operator= (const at_N2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C2 () || type->is_1H2 () || type->is_2H2 ();
}



float
at_N2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dG ())
    return -0.9230;
  else if (res->GetType ()->is_rG ())
    return -0.9672;
  return 0;
}



void
at_N2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N2_BIN;
}



const at_N3&
at_N3::operator= (const at_N3 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C2 () || type->is_C4 () || type->is_H3 ()
	  || type->is_LP3 ());
}



float
at_N3::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_A ())
	return -0.7417;
      else if (r->is_T ())
	return -0.4340;
      else if (r->is_G ())
	return -0.6636;
      else if (r->is_C ())
	return -0.7748;
    }
  else if (r->is_RNA ())
    {
      if (r->is_A ())
	return -0.6997;
      else if (r->is_C ())
	return -0.7584;
      else if (r->is_G ())
	return -0.6323;
      else if (r->is_U ())
	return -0.3549;
    }
  return 0;
}



void
at_N3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N3_BIN;
}



const at_N4&
at_N4::operator= (const at_N4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C4 () || type->is_1H4 () || type->is_2H4 ();
}



float
at_N4::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dC ())
    return -0.9773;
  else if (res->GetType ()->is_rC ())
    return -0.9530;
  return 0;
}



void
at_N4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N4_BIN;
}



const at_N6&
at_N6::operator= (const at_N6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C6 () || type->is_2H6 () || type->is_1H6 ();
}



float
at_N6::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dA ())
    return -0.9123;
  else if (res->GetType ()->is_rA ())
    return -0.9019;
  return 0;
}



void
at_N6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N6_BIN;
}



const at_N7&
at_N7::operator= (const at_N7 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N7::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C5 () || type->is_C8 () || type->is_H7 ()
	  || type->is_LP7 ());
}



float
at_N7::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_dA ())
	return -0.6175;
      else if (r->is_dG ())
	return -0.5725;
    }
  else if (r->is_RNA ())
    {
      if (r->is_rA ())
	return -0.6073;
      else if (r->is_rG ())
	return -0.5709;
    }
  return 0;
}



void
at_N7::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N7_BIN;
}



const at_N9&
at_N9::operator= (const at_N9 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_N9::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C1p () || type->is_C8 () || type->is_C4 ();
}



float
at_N9::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_dA ())
	return -0.0268;
      else if (r->is_dG ())
	return 0.0577;
    }
  else if (r->is_RNA ())
    {
      if (r->is_rA ())
	return -0.0251;
      else if (r->is_rG ())
	return  0.0492;
    }
  return 0;
}



void
at_N9::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N9_BIN;
}



const at_O2&
at_O2::operator= (const at_O2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_O2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C2 () || type->is_H2 () || type->is_1LP2 ()
	  || type->is_2LP2 ());
}



float
at_O2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_DNA ())
    {
      if (r->is_dT ())
	return -0.5881;
      else if (r->is_dC ())
	return -0.6548;
    }
  else if (r->is_RNA ())
    {
      if (r->is_rC ())
	return -0.6252;
      else if (r->is_rU ())
	return -0.5477;
    }
  return 0;
}



void
at_O2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O2_BIN;
}



const at_O4&
at_O4::operator= (const at_O4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_O4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C4 () || type->is_1LP4 () || type->is_2LP4 ();
}



float
at_O4::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dT ())
    return -0.5563;
  else if (res->GetType ()->is_rU ())
    return -0.5761;
  return 0;
}



void
at_O4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O4_BIN;
}



const at_O6&
at_O6::operator= (const at_O6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_O6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C6 () || type->is_1LP6 () || type->is_2LP6 ();
}



float
at_O6::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dG ())
    return -0.5699;
  else if (res->GetType ()->is_rG ())
    return -0.5597;
  return 0;
}



void
at_O6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O6_BIN;
}



const at_1H2&
at_1H2::operator= (const at_1H2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1H2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N2 ();
}



float
at_1H2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dG ())
    return 0.4235;
  else if (res->GetType ()->is_rG ())
    return 0.4364;
  return 0;
}



void
at_1H2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H2_BIN;
}



const at_1H4&
at_1H4::operator= (const at_1H4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1H4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N4 ();
}



float
at_1H4::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dC ())
    return 0.4314;
  else if (res->GetType ()->is_rC ())
    return 0.4234;
  return 0;
}



void
at_1H4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H4_BIN;
}



const at_1H5M&
at_1H5M::operator= (const at_1H5M &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1H5M::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5M ();
}



float
at_1H5M::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dT ())
    return 0.0770;
  return 0;
}



void
at_1H5M::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H5M_BIN;
}



const at_1H6&
at_1H6::operator= (const at_1H6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1H6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N6 ();
}



float
at_1H6::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dA ())
    return 0.4167;
  else if (res->GetType ()->is_rA ())
    return 0.4115;
  return 0;
}



void
at_1H6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H6_BIN;
}



const at_2H2&
at_2H2::operator= (const at_2H2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2H2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N2 ();
}



float
at_2H2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dG ())
    return 0.4235;
  else if (res->GetType ()->is_rG ())
    return 0.4364;
  return 0;
}



void
at_2H2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H2_BIN;
}



const at_2H4&
at_2H4::operator= (const at_2H4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2H4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N4 ();
}



float
at_2H4::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dC ())
    return 0.4314;
  else if (res->GetType ()->is_rC ())
    return 0.4234;
  return 0;
}



void
at_2H4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H4_BIN;
}



const at_2H5M&
at_2H5M::operator= (const at_2H5M &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2H5M::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5M ();
}



float
at_2H5M::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dT ())
    return 0.0770;
  return 0;
}



void
at_2H5M::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H5M_BIN;
}



const at_2H6&
at_2H6::operator= (const at_2H6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2H6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N6 ();
}



float
at_2H6::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dA ())
    return 0.4167;
  else if (res->GetType ()->is_rA ())
    return 0.4115;
  return 0;
}



void
at_2H6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H6_BIN;
}



const at_3H5M&
at_3H5M::operator= (const at_3H5M &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_3H5M::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C5M ();
}



float
at_3H5M::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_dT ())
    return 0.0770;
  return 0;
}



void
at_3H5M::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3H5M_BIN;
}



const at_PSY&
at_PSY::operator= (const at_PSY &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Pseudo::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_PSY::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return false;
}



void
at_PSY::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_PSY_BIN;
}



const at_PSZ&
at_PSZ::operator= (const at_PSZ &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Pseudo::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_PSZ::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return false;
}



void
at_PSZ::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_PSZ_BIN;
}



const at_LP1&
at_LP1::operator= (const at_LP1 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_LP1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N1 ();
}



void
at_LP1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_LP1_BIN;
}



const at_LP3&
at_LP3::operator= (const at_LP3 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_LP3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N3 ();
}



void
at_LP3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_LP3_BIN;
}



const at_LP7&
at_LP7::operator= (const at_LP7 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_LP7::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N7 ();
}



void
at_LP7::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_LP7_BIN;
}



const at_1LP2&
at_1LP2::operator= (const at_1LP2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1LP2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O2 ();
}



void
at_1LP2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1LP2_BIN;
}



const at_1LP4&
at_1LP4::operator= (const at_1LP4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1LP4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O4 ();
}



void
at_1LP4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1LP4_BIN;
}



const at_1LP6&
at_1LP6::operator= (const at_1LP6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1LP6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O6 ();
}



void
at_1LP6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1LP6_BIN;
}



const at_2LP2&
at_2LP2::operator= (const at_2LP2 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2LP2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O2 ();
}



void
at_2LP2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2LP2_BIN;
}



const at_2LP4&
at_2LP4::operator= (const at_2LP4 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2LP4::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O4 ();
}



void
at_2LP4::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2LP4_BIN;
}



const at_2LP6&
at_2LP6::operator= (const at_2LP6 &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_LonePair::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2LP6::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O6 ();
}



void
at_2LP6::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2LP6_BIN;
}



const at_H3T&
at_H3T::operator= (const at_H3T &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H3T::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O3p ();
}



float
at_H3T::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.4396;
  else if (res->GetType ()->is_RNA ())
    return 0.4376;
  return 0;
}



void
at_H3T::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H3T_BIN;
}



const at_H5T&
at_H5T::operator= (const at_H5T &right)
{
  if (this != &right)
    {
      at_NucleicAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H5T::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O5p ();
}



float
at_H5T::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_DNA ())
    return 0.4422;
  else if (res->GetType ()->is_RNA ())
    return 0.4295;
  return 0;
}



void
at_H5T::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H5T_BIN;
}



const at_C&
at_C::operator= (const at_C &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}


bool
at_C::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_O () || type->is_CA () || type->is_OXT ();
}



float
at_C::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA () || r->is_GLY () || r->is_SER () || r->is_THR ()
      || r->is_LEU () || r->is_ILE () || r->is_VAL () || r->is_ASN ()
      || r->is_GLN () || r->is_HIS () || r->is_TRP () || r->is_PHE ()
      || r->is_TYR () || r->is_CYS () || r->is_MET ())
    return 0.59730;
  else if (r->is_ARG () || r->is_LYS ())
    return 0.73410;
  else if (r->is_GLU () || r->is_ASP ())
    return 0.53660;
  else if (r->is_PRO ())
    return 0.58960;
  return 0;
}



void
at_C::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_C_BIN;
}



const at_CA&
at_CA::operator= (const at_CA &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_CA::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_C () || type->is_N () || type->is_CB ()
	  || type->is_HA () || type->is_HA1 () || type->is_HA2 ());
}



float
at_CA::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA ())
    return 0.03370;
  else if (r->is_GLY ())
    return -0.02520;
  else if (r->is_SER ())
    return -0.02490;
  else if (r->is_THR ())
    return -0.03890;
  else if (r->is_LEU ())
    return -0.05180;
  else if (r->is_ILE ())
    return -0.05970;
  else if (r->is_VAL ())
    return -0.08750;
  else if (r->is_ASN ())
    return 0.01430;
  else if (r->is_GLN ())
    return -0.00310;
  else if (r->is_ARG ())
    return -0.26370;
  else if (r->is_HIS ())
    return 0.01880;
  else if (r->is_TRP ())
    return -0.02750;
  else if (r->is_PHE ())
    return -0.00240;
  else if (r->is_TYR ())
    return -0.00140;
  else if (r->is_GLU ())
    return 0.03970;
  else if (r->is_ASP ())
    return 0.03810;
  else if (r->is_LYS ())
    return -0.24000;
  else if (r->is_PRO ())
    return -0.02660;
  else if (r->is_CYS ())
    return 0.02130;
  else if (r->is_MET ())
    return -0.02370;
  return 0;
}



void
at_CA::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CA_BIN;
}



const at_CB&
at_CB::operator= (const at_CB &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CB::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CA () || type->is_HB1 () || type->is_HB2 ()
	  || type->is_HB3 () || type->is_CG () || type->is_SG ()
	  || type->is_CG1 () || type->is_CG2 () || type->is_HB ()
	  || type->is_OG () || type->is_OG1 ());
}



float
at_CB::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA ())
    return -0.18250;
  else if (r->is_SER ())
    return 0.21170;
  else if (r->is_THR ())
    return 0.36540;
  else if (r->is_LEU ())
    return -0.11020;
  else if (r->is_ILE ())
    return 0.13030;
  else if (r->is_VAL ())
    return 0.29850;
  else if (r->is_ASN ())
    return -0.20410;
  else if (r->is_GLN ())
    return -0.00360;
  else if (r->is_ARG ())
    return -0.00070;
  else if (r->is_HIS ())
    return -0.04620;
  else if (r->is_TRP ())
    return -0.00500;
  else if (r->is_PHE ())
    return -0.03430;
  else if (r->is_TYR ())
    return -0.01520;
  else if (r->is_GLU ())
    return 0.05600;
  else if (r->is_ASP ())
    return -0.03030;
  else if (r->is_LYS ())
    return -0.00940;
  else if (r->is_PRO ())
    return -0.00700;
  else if (r->is_CYS ())
    return -0.12310;
  else if (r->is_MET ())
    return 0.03420;
  return 0;
}



void
at_CB::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CB_BIN;
}



const at_CD&
at_CD::operator= (const at_CD &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}


bool
at_CD::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CG () || type->is_NE () || type->is_HD1 ()
	  || type->is_HD2 () || type->is_OE1 () || type->is_NE2 ()
	  || type->is_OE2 () || type->is_CE ()
	  || (res->is_PRO () && type->is_N ()));
}



float
at_CD::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();
  
  return type->is_GLN () || type->is_GLU () ? 0.0860 : 0.1094;
}



float
at_CD::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_GLN ())
    return 0.69510;
  else if (r->is_ARG ())
    return 0.04860;
  else if (r->is_GLU ())
    return 0.80540;
  else if (r->is_LYS ())
    return -0.04790;
  else if (r->is_PRO ())
    return 0.01920;
  return 0;
}



void
at_CD::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CD_BIN;
}



const at_CD1&
at_CD1::operator= (const at_CD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}


bool
at_CD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CG1 () || type->is_1HD1 () || type->is_2HD1 ()
	  || type->is_3HD1 () || type->is_CG () || type->is_CE1 ()
	  || type->is_HD1 () || type->is_NE1 ());
}



float
at_CD1::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();
  
  return (type->is_PHE () || type->is_TYR () || type->is_TRP ()
	  ? 0.0860 : 0.1094);
}



float
at_CD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return -0.41210;
  else if (r->is_ILE ())
    return -0.06600;
  else if (r->is_TRP ())
    return -0.16380;
  else if (r->is_PHE ())
    return -0.12560;
  else if (r->is_TYR ())
    return -0.19060;
  return 0;
}



void
at_CD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CD1_BIN;
}



const at_CD2&
at_CD2::operator= (const at_CD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}


bool
at_CD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CG () || type->is_NE2 () || type->is_HD2 ()
	  || type->is_1HD2 () || type->is_2HD2 () || type->is_3HD2 ()
	  || type->is_CE2 () || type->is_CE3 ());
}


float
at_CD2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return -0.41210;
  else if (r->is_HIS ())
    return 0.12920;
  else if (r->is_TRP ())
    return 0.12430;
  else if (r->is_PHE ())
    return -0.12560;
  else if (r->is_TYR ())
    return -0.19060;
  return 0;
}



void
at_CD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CD2_BIN;
}



const at_CE&
at_CE::operator= (const at_CE &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CE::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CD () || type->is_NZ () || type->is_HE1 ()
	  || type->is_HE2 () || type->is_SD () || type->is_HE3 ());
}



float
at_CE::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LYS ())
    return -0.01430;
  else if (r->is_MET ())
    return -0.05360;
  return 0;
}



void
at_CE::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CE_BIN;
}



const at_CE1&
at_CE1::operator= (const at_CE1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CE1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_ND1 () || type->is_NE2 () || type->is_HE1 ()
	  || type->is_CD1 () || type->is_CZ ());
}



float
at_CE1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_HIS ())
    return 0.20570;
  else if (r->is_PHE ())
    return -0.17040;
  else if (r->is_TYR ())
    return -0.23410;
  return 0;
}



void
at_CE1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CE1_BIN;
}



const at_CE2&
at_CE2::operator= (const at_CE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CD2 () || type->is_CZ () || type->is_HE2 ()
	  || type->is_NE1 () || type->is_CZ2 ());
}



float
at_CE2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_TRP ())
    return 0.13800;
  else if (r->is_PHE ())
    return -0.17040;
  else if (r->is_TYR ())
    return -0.23410;
  return 0;
}



void
at_CE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CE2_BIN;
}



const at_CE3&
at_CE3::operator= (const at_CE3 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CE3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD2 () || type->is_CZ3 () || type->is_HE3 ();
}



float
at_CE3::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return -0.23870;
  return 0;
}



void
at_CE3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CE3_BIN;
}



const at_CG&
at_CG::operator= (const at_CG &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CG::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CB () || type->is_CD () || type->is_HG1 ()
	  || type->is_HG2 () || type->is_OD1 () || type->is_ND2 ()
	  || type->is_OD2 () || type->is_ND1 () || type->is_CD1 ()
	  || type->is_CD2 () || type->is_HG () || type->is_SD ());
}



float
at_CG::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();
  
  return ((type->is_ASN () || type->is_HIS () || type->is_TRP ()
	   || type->is_PHE () || type->is_TYR () || type->is_ASP ())
	  ? 0.0860 : 0.1094);
}



float
at_CG::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.35310;
  else if (r->is_ASN ())
    return 0.71300;
  else if (r->is_GLN ())
    return -0.06450;
  else if (r->is_ARG ())
    return 0.03900;
  else if (r->is_HIS ())
    return -0.02660;
  else if (r->is_TRP ())
    return -0.14150;
  else if (r->is_PHE ())
    return 0.01180;
  else if (r->is_TYR ())
    return -0.00110;
  else if (r->is_GLU ())
    return 0.01360;
  else if (r->is_ASP ())
    return 0.79940;
  else if (r->is_LYS ())
    return 0.01870;
  else if (r->is_PRO ())
    return 0.01890;
  else if (r->is_MET ())
    return 0.00180;
  return 0;
}



void
at_CG::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CG_BIN;
}



const at_CG1&
at_CG1::operator= (const at_CG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CB () || type->is_CD1 () || type->is_1HG1 ()
	  || type->is_2HG1 () || type->is_3HG1 ());
}



float
at_CG1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ILE ())
    return -0.04300;
  else if (r->is_VAL ())
    return -0.31920;
  return 0;
}



void
at_CG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CG1_BIN;
}



const at_CG2&
at_CG2::operator= (const at_CG2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CG2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CB () || type->is_1HG2 () || type->is_2HG2 ()
	  || type->is_3HG2 ());
}



float
at_CG2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_THR ())
    return -0.24380;
  else if (r->is_ILE ())
    return -0.32040;
  else if (r->is_VAL ())
    return -0.31920;
  return 0;
}



void
at_CG2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CG2_BIN;
}



const at_CH2&
at_CH2::operator= (const at_CH2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CH2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CZ2 () || type->is_CZ3 () || type->is_HH2 ();
}



float
at_CH2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return -0.11340;
  return 0;
}



void
at_CH2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CH2_BIN;
}



const at_CZ&
at_CZ::operator= (const at_CZ &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CZ::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_NE () || type->is_NH1 () || type->is_NH2 ()
	  || type->is_CE1 () || type->is_CE2 () || type->is_HZ ()
	  || type->is_OH ());
}



float
at_CZ::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ARG ())
    return 0.80760;
  else if (r->is_PHE ())
    return -0.10720;
  else if (r->is_TYR ())
    return 0.32260;
  return 0;
}



void
at_CZ::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CZ_BIN;
}



const at_CZ2&
at_CZ2::operator= (const at_CZ2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CZ2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE2 () || type->is_CH2 () || type->is_HZ2 ();
}



float
at_CZ2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return -0.26010;
  return 0;
}



void
at_CZ2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CZ2_BIN;
}



const at_CZ3&
at_CZ3::operator= (const at_CZ3 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Carbon::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_CZ3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE3 () || type->is_CH2 () || type->is_HZ3 ();
}



float
at_CZ3::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return -0.19720;
  return 0;
}



void
at_CZ3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_CZ3_BIN;
}



const at_H&
at_H::operator= (const at_H &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_H::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N ();
}



float
at_H::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA () || r->is_GLY () || r->is_SER () || r->is_THR ()
      || r->is_LEU () || r->is_ILE () || r->is_VAL () || r->is_ASN ()
      || r->is_GLN () || r->is_HIS () || r->is_TRP () || r->is_PHE ()
      || r->is_TYR () || r->is_CYS () || r->is_MET ())
    return 0.27190;
  else if (r->is_ARG () || r->is_LYS ())
    return 0.27470;
  else if (r->is_GLU () || r->is_ASP ())
    return 0.29360;
  return 0;
}



void
at_H::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_H_BIN;
}



const at_1H&
at_1H::operator= (const at_1H &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_1H::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N ();
}



void
at_1H::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1H_BIN;
}



const at_2H&
at_2H::operator= (const at_2H &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_2H::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N ();
}



void
at_2H::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2H_BIN;
}



const at_3H&
at_3H::operator= (const at_3H &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_3H::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_N ();
}



void
at_3H::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3H_BIN;
}



const at_HA&
at_HA::operator= (const at_HA &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HA::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CA ();
}



float
at_HA::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA ())
    return 0.08230;
  else if (r->is_SER ())
    return 0.08430;
  else if (r->is_THR ())
    return 0.10070;
  else if (r->is_LEU ())
    return 0.09220;
  else if (r->is_ILE ())
    return 0.08690;
  else if (r->is_VAL ())
    return 0.09690;
  else if (r->is_ASN ())
    return 0.10480;
  else if (r->is_GLN ())
    return 0.08500;
  else if (r->is_ARG ())
    return 0.15600;
  else if (r->is_HIS ())
    return 0.08810;
  else if (r->is_TRP ())
    return 0.11230;
  else if (r->is_PHE ())
    return 0.09780;
  else if (r->is_TYR ())
    return 0.08760;
  else if (r->is_GLU ())
    return 0.11050;
  else if (r->is_ASP () || r->is_MET ())
    return 0.08800;
  else if (r->is_LYS ())
    return 0.14260;
  else if (r->is_PRO ())
    return 0.06410;
  else if (r->is_CYS ())
    return 0.11240;
  return 0;
}



void
at_HA::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HA_BIN;
}



const at_HA1&
at_HA1::operator= (const at_HA1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HA1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CA ();
}



float
at_HA1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_GLY ())
    return 0.06980;
  return 0;
}



void
at_HA1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HA1_BIN;
}



const at_HA2&
at_HA2::operator= (const at_HA2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HA2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CA ();
}



float
at_HA2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_GLY ())
    return 0.06980;
  return 0;
}



void
at_HA2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HA2_BIN;
}



const at_HB&
at_HB::operator= (const at_HB &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HB::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB ();
}



float
at_HB::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_THR ())
    return 0.00430;
  else if (r->is_ILE ())
    return 0.01870;
  else if (r->is_VAL ())
    return -0.02970;
  return 0;
}



void
at_HB::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HB_BIN;
}



const at_HB1&
at_HB1::operator= (const at_HB1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HB1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB ();
}



float
at_HB1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ALA ())
    return 0.06030;
  return 0;
}



void
at_HB1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HB1_BIN;
}



const at_HB2&
at_HB2::operator= (const at_HB2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HB2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB ();
}



float
at_HB2::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();
  
  return type->is_SER () || type->is_CYS () ? 1.3870 : 1.4870;
}



float
at_HB2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA ())
    return 0.06030;
  else if (r->is_SER ())
    return 0.03520;
  else if (r->is_LEU ())
    return 0.04570;
  else if (r->is_ASN ())
    return 0.07970;
  else if (r->is_GLN ())
    return 0.01710;
  else if (r->is_ARG ())
    return 0.03270;
  else if (r->is_HIS ())
    return 0.04020;
  else if (r->is_TRP ())
    return 0.03390;
  else if (r->is_PHE () || r->is_TYR ())
    return 0.02950;
  else if (r->is_GLU ())
    return -0.01730;
  else if (r->is_ASP ())
    return -0.01220;
  else if (r->is_LYS ())
    return 0.03620;
  else if (r->is_PRO ())
    return 0.02530;
  else if (r->is_CYS ())
    return 0.11120;
  else if (r->is_MET ())
    return 0.02410;
  return 0;
}



void
at_HB2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HB2_BIN;
}



const at_HB3&
at_HB3::operator= (const at_HB3 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HB3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB ();
}



float
at_HB3::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();
  
  return type->is_SER () || type->is_CYS () ? 1.3870 : 1.4870;
}



float
at_HB3::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA ())
    return 0.06030;
  else if (r->is_SER ())
    return 0.03520;
  else if (r->is_LEU ())
    return 0.04570;
  else if (r->is_ASN ())
    return 0.07970;
  else if (r->is_GLN ())
    return 0.01710;
  else if (r->is_ARG ())
    return 0.03270;
  else if (r->is_HIS ())
    return 0.04020;
  else if (r->is_TRP ())
    return 0.03390;
  else if (r->is_PHE () || r->is_TYR ())
    return 0.02950;
  else if (r->is_GLU ())
    return -0.01730;
  else if (r->is_ASP ())
    return -0.01220;
  else if (r->is_LYS ())
    return 0.03620;
  else if (r->is_PRO ())
    return 0.02530;
  else if (r->is_CYS ())
    return 0.11120;
  else if (r->is_MET ())
    return 0.02410;
  return 0;
}



void
at_HB3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HB3_BIN;
}



const at_HD1&
at_HD1::operator= (const at_HD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD () || type->is_ND1 () || type->is_CD1 ();
}



float
at_HD1::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_HIS ())
    return 0.6000;
  else if (type->is_TRP ())
    return 1.4090;
  else
    return 1.4590;
}



float
at_HD1::getAmberEpsilon (const AbstractResidue *res) const
{
  return res->GetType ()->is_HIS () ? 0.0157 : 0.0150;
}



float
at_HD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_HIS ())
    return 0.36490;
  else if (r->is_TRP ())
    return 0.20620;
  else if (r->is_PHE ())
    return 0.13300;
  else if (r->is_TYR ())
    return 0.16990;
  return 0;
}



void
at_HD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HD1_BIN;
}



const at_HD2&
at_HD2::operator= (const at_HD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD () || type->is_CD2 ();
}



float
at_HD2::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_ARG () || type->is_PRO ())
    return 1.3870; // H1
  else if (type->is_HIS ())
    return 1.4090; // H4
  else if (type->is_PHE () || type->is_TYR ())
    return 1.4590; // HA
  else if (type->is_LYS ())
    return 1.4870; // HC
  else
    return 0.0000; // HO
}



float
at_HD2::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_ARG () || type->is_PRO () || type->is_LYS ())
    return 0.0157; // H1 HC
  else if (type->is_HIS () || type->is_PHE () || type->is_TYR ())
    return 0.0150; // H4 HA
  else
    return 0.0000; // HO
}



float
at_HD2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ARG ())
    return 0.06870;
  else if (r->is_HIS ())
    return 0.11470;
  else if (r->is_PHE ())
    return 0.13300;
  else if (r->is_TYR ())
    return 0.16990;
  else if (r->is_LYS ())
    return 0.06210;
  else if (r->is_PRO ())
    return 0.03910;
  return 0;
}



void
at_HD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HD2_BIN;
}



const at_HE&
at_HE::operator= (const at_HE &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HE::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NE ();
}



float
at_HE::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return 0.34560;
  return 0;
}



void
at_HE::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HE_BIN;
}



const at_HE1&
at_HE1::operator= (const at_HE1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HE1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE1 () || type->is_CE () || type->is_NE1 ();
}


float
at_HE1::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_HIS ())
    return 1.3590; // H5
  else if (type->is_TRP ())
    return 0.6000; // H
  else if (type->is_PHE () || type->is_TYR ())
    return 1.4590; // HA
  else if (type->is_MET ())
    return 1.3870; // H1
  return 0;
}



float
at_HE1::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_HIS () || type->is_PHE () || type->is_TYR ())
    return 0.0150; // H5 HA
  else if (type->is_TRP () || type->is_MET ())
    return 0.0157; // H H1
  return 0;
}



float
at_HE1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_HIS ())
    return 0.13920;
  else if (r->is_TRP ())
    return 0.34120;
  else if (r->is_PHE ())
    return 0.14300;
  else if (r->is_TYR ())
    return 0.16560;
  else if (r->is_MET ())
    return 0.06940;
  return 0;
}



void
at_HE1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HE1_BIN;
}



const at_HE2&
at_HE2::operator= (const at_HE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE () || type->is_CE2 () || type->is_NE2 ();
}



float
at_HE2::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_HIS ())
    return 0.6000; // H
  else if (type->is_PHE () || type->is_TYR ())
    return 1.4590; // HA
  else if (type->is_LYS ())
    return 1.1000; // HP
  else if (type->is_MET ())
    return 1.3870; // H1
  else if (type->is_GLU ())
    return 0.0000;
  return 0;
}



float
at_HE2::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_HIS () || type->is_LYS () || type->is_MET ())
    return 0.0157; // H HP H1
  else if (type->is_PHE () || type->is_TYR ())
    return 0.0150; // HA
  else if (type->is_GLU ())
    return 0.0000; // HO
  return 0;
}



float
at_HE2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_PHE ())
    return 0.14300;
  else if (r->is_TYR ())
    return 0.16560;
  else if (r->is_LYS ())
    return 0.11350;
  else if (r->is_MET ())
    return 0.06840;
  return 0;
}



void
at_HE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HE2_BIN;
}



const at_HE3&
at_HE3::operator= (const at_HE3 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HE3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE () || type->is_CE3 ();
}



float
at_HE3::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_TRP ())
    return 1.4590; // HA
  else if (type->is_LYS ())
    return 1.1000; // HP
  else if (type->is_MET ())
    return 1.3870; // H1
  return 0;
}



float
at_HE3::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_LYS () || type->is_MET ())
    return 0.0157; // HP H1
  else if (type->is_TRP ())
    return 0.0150; // HA
  return 0;
}



float
at_HE3::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_TRP ())
    return 0.17000;
  else if (r->is_LYS ())
    return 0.11350;
  else if (r->is_MET ())
    return 0.06840;
  return 0;
}



void
at_HE3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HE3_BIN;
}



const at_HG&
at_HG::operator= (const at_HG &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HG::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_SG () || type->is_CG () || type->is_OG ();
}



float
at_HG::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_SER ())
    return 0.42750;
  else if (r->is_LEU ())
    return -0.03610;
  else if (r->is_CYS ())
    return 0.19330;
  return 0;
}



void
at_HG::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HG_BIN;
}



const at_HG1&
at_HG1::operator= (const at_HG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG () || type->is_OG1 ();
}



float
at_HG1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_THR ())
    return 0.41020;
  return 0;
}



void
at_HG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HG1_BIN;
}



const at_HG2&
at_HG2::operator= (const at_HG2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HG2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG ();
}



float
at_HG2::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_GLN () || type->is_ARG () || type->is_GLU () || type->is_LYS ()
      || type->is_PRO ())
    return 1.4870; // HC
  else if (type->is_MET ())
    return 1.3870; // H1
  return 0;
}



float
at_HG2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_GLN ())
    return 0.03520;
  else if (r->is_ARG ())
    return 0.02850;
  else if (r->is_GLU ())
    return -0.04250;
  else if (r->is_LYS ())
    return 0.01030;
  else if (r->is_PRO ())
    return 0.02130;
  else if (r->is_MET ())
    return 0.04400;
  return 0;
}



void
at_HG2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HG2_BIN;
}



const at_HH&
at_HH::operator= (const at_HH &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HH::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_OH ();
}



float
at_HH::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TYR ())
    return 0.39920;
  return 0;
}



void
at_HH::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HH_BIN;
}



const at_HH2&
at_HH2::operator= (const at_HH2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HH2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CH2 ();
}



float
at_HH2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return 0.14170;
  return 0;
}



void
at_HH2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HH2_BIN;
}



const at_HXT&
at_HXT::operator= (const at_HXT &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_HXT::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_OXT ();
}



void
at_HXT::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HXT_BIN;
}



const at_HZ&
at_HZ::operator= (const at_HZ &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HZ::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CZ ();
}



float
at_HZ::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_PHE ())
    return 0.12970;
  return 0;
}



void
at_HZ::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HZ_BIN;
}



const at_HZ1&
at_HZ1::operator= (const at_HZ1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HZ1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NZ ();
}



float
at_HZ1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_LYS ())
    return 0.34000;
  return 0;
}



void
at_HZ1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HZ1_BIN;
}



const at_HZ2&
at_HZ2::operator= (const at_HZ2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HZ2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NZ () || type->is_CZ2 ();
}



float
at_HZ2::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_TRP ())
    return 1.4590; // HA
  else if (type->is_LYS ())
    return 0.6000; // H
  return 0;
}



float
at_HZ2::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_TRP ())
    return 0.0150; // HA
  else if (type->is_LYS ())
    return 0.0157; // H
  return 0;
}



float
at_HZ2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return 0.15720;
  else if (res->GetType ()->is_LYS ())
    return 0.34000;
  return 0;
}



void
at_HZ2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HZ2_BIN;
}



const at_HZ3&
at_HZ3::operator= (const at_HZ3 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_HZ3::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NZ () || type->is_CZ3 ();
}



float
at_HZ3::getVDWR (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_TRP ())
    return 1.4590; // HA
  else if (type->is_LYS ())
    return 0.6000; // H
  return 0;
}



float
at_HZ3::getAmberEpsilon (const AbstractResidue *res) const
{
  t_Residue *type = res->GetType ();

  if (type->is_TRP ())
    return 0.0150; // HA
  else if (type->is_LYS ())
    return 0.0157; // H
  return 0;
}



float
at_HZ3::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return 0.14470;
  else if (res->GetType ()->is_LYS ())
    return 0.34000;
  return 0;
}



void
at_HZ3::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_HZ3_BIN;
}



const at_N&
at_N::operator= (const at_N &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_N::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CA () || (res->is_PRO () && type->is_CD ())
	  || type->is_H () || type->is_1H () || type->is_2H ()
	  || type->is_3H ());
}



float
at_N::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA () || r->is_GLY () || r->is_SER () || r->is_THR ()
      || r->is_LEU () || r->is_ILE () || r->is_VAL () || r->is_ASN ()
      || r->is_GLN () || r->is_HIS () || r->is_TRP () || r->is_PHE ()
      || r->is_TYR () || r->is_CYS () || r->is_MET ())
    return -0.41570;
  else if (r->is_ARG () || r->is_LYS ())
    return -0.34790;
  else if (r->is_GLU () || r->is_ASP ())
    return -0.51630;
  else if (r->is_PRO ())
    return -0.25480;
  return 0;
}



void
at_N::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_N_BIN;
}



const at_ND1&
at_ND1::operator= (const at_ND1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_ND1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG () || type->is_CE1 () || type->is_HD1 ();
}



float
at_ND1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_HIS ())
    return -0.38110;
  return 0;
}



void
at_ND1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_ND1_BIN;
}



const at_ND2&
at_ND2::operator= (const at_ND2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_ND2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG () || type->is_1HD2 () || type->is_2HD2 ();
}



float
at_ND2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ASN ())
    return -0.91910;
  return 0;
}



void
at_ND2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_ND2_BIN;
}



const at_NE&
at_NE::operator= (const at_NE &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NE::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD () || type->is_CZ () || type->is_HE ();
}



float
at_NE::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return -0.52950;
  return 0;
}



void
at_NE::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NE_BIN;
}



const at_NE1&
at_NE1::operator= (const at_NE1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NE1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD1 () || type->is_CE2 () || type->is_HE1 ();
}



float
at_NE1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TRP ())
    return -0.34180;
  return 0;
}



void
at_NE1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NE1_BIN;
}



const at_NE2&
at_NE2::operator= (const at_NE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CD () || type->is_HE2 () || type->is_1HE2 ()
	  || type->is_2HE2 () || type->is_CD2 () || type->is_CE1 ());
}



float
at_NE2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_GLN ())
    return -0.94070;
  else if (r->is_HIS ())
    return -0.57270;
  return 0;
}



void
at_NE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NE2_BIN;
}



const at_NH1&
at_NH1::operator= (const at_NH1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NH1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CZ () || type->is_1HH1 () || type->is_2HH1 ();
}



float
at_NH1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return -0.86270;
  return 0;
}



void
at_NH1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NH1_BIN;
}



const at_NH2&
at_NH2::operator= (const at_NH2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NH2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CZ () || type->is_1HH2 () || type->is_2HH2 ();
}



float
at_NH2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return -0.86270;
  return 0;
}



void
at_NH2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NH2_BIN;
}



const at_NZ&
at_NZ::operator= (const at_NZ &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Nitrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_NZ::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return (type->is_CE () || type->is_HZ1 () || type->is_HZ2 ()
	  || type->is_HZ3 ());
}



float
at_NZ::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_LYS ())
    return -0.38540;
  return 0;
}



void
at_NZ::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_NZ_BIN;
}



const at_O&
at_O::operator= (const at_O &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_O::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C ();
}



float
at_O::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ALA () || r->is_GLY () || r->is_SER () || r->is_THR ()
      || r->is_LEU () || r->is_ILE () || r->is_VAL () || r->is_ASN ()
      || r->is_GLN () || r->is_HIS () || r->is_TRP () || r->is_PHE ()
      || r->is_TYR () || r->is_CYS () || r->is_MET ())
    return -0.56790;
  else if (r->is_ARG () || r->is_LYS ())
    return -0.58940;
  else if (r->is_GLU () || r->is_ASP ())
    return -0.58190;
  else if (r->is_PRO ())
    return -0.57480;
  return 0;
}



void
at_O::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_O_BIN;
}



const at_OD1&
at_OD1::operator= (const at_OD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG ();
}



float
at_OD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ASN ())
    return -0.59310;
  else if (r->is_ASP ())
    return -0.80140;
  return 0;
}



void
at_OD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OD1_BIN;
}



const at_OD2&
at_OD2::operator= (const at_OD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG ();
}



float
at_OD2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ASP ())
    return -0.80140;
  return 0;
}



void
at_OD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OD2_BIN;
}



const at_OE1&
at_OE1::operator= (const at_OE1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OE1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD ();
}



float
at_OE1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_GLN ())
    return -0.60860;
  else if (r->is_GLU ())
    return -0.81880;
  return 0;
}



void
at_OE1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OE1_BIN;
}



const at_OE2&
at_OE2::operator= (const at_OE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD ();
}



float
at_OE2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_GLU ())
    return -0.81880;
  return 0;
}



void
at_OE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OE2_BIN;
}



const at_OG&
at_OG::operator= (const at_OG &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OG::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB () || type->is_HG ();
}



float
at_OG::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_SER ())
    return -0.65460;
  return 0;
}



void
at_OG::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OG_BIN;
}



const at_OG1&
at_OG1::operator= (const at_OG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB () || type->is_HG1 ();
}



float
at_OG1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_THR ())
    return -0.67610;
  return 0;
}



void
at_OG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OG1_BIN;
}



const at_OH&
at_OH::operator= (const at_OH &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_OH::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CZ () || type->is_HH ();
}



float
at_OH::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_TYR ())
    return -0.55790;
  return 0;
}



void
at_OH::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OH_BIN;
}



const at_OXT&
at_OXT::operator= (const at_OXT &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Oxygen::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_OXT::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_C () || type->is_HXT ();
}



void
at_OXT::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_OXT_BIN;
}



const at_SD&
at_SD::operator= (const at_SD &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Sulfur::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_SD::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CE () || type->is_CG ();
}



float
at_SD::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_MET ())
    return -0.27370;
  return 0;
}



void
at_SD::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_SD_BIN;
}



const at_SG&
at_SG::operator= (const at_SG &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Sulfur::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_SG::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CB () || type->is_HG ();
}



float
at_SG::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_CYS ())
    return -0.31190;
  return 0;
}



void
at_SG::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_SG_BIN;
}



const at_1HD1&
at_1HD1::operator= (const at_1HD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD1 ();
}



float
at_1HD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.10000;
  else if (r->is_ILE ())
    return 0.01860;
  return 0;
}



void
at_1HD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HD1_BIN;
}



const at_1HD2&
at_1HD2::operator= (const at_1HD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_ND2 () || type->is_CD2 ();
}



float
at_1HD2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.10000;
  else if (r->is_ASN ())
    return 0.41960;
  return 0;
}



void
at_1HD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HD2_BIN;
}



const at_1HE2&
at_1HE2::operator= (const at_1HE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NE2 ();
}



float
at_1HE2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_GLN ())
    return 0.42510;
  return 0;
}



void
at_1HE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HE2_BIN;
}



const at_1HG1&
at_1HG1::operator= (const at_1HG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG1 ();
}



float
at_1HG1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_1HG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HG1_BIN;
}



const at_1HG2&
at_1HG2::operator= (const at_1HG2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HG2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG2 ();
}



float
at_1HG2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_THR ())
    return 0.06420;
  else if (r->is_ILE ())
    return 0.08820;
  else if (r->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_1HG2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HG2_BIN;
}



const at_1HH1&
at_1HH1::operator= (const at_1HH1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HH1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NH1 ();
}



float
at_1HH1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return 0.44780;
  return 0;
}



void
at_1HH1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HH1_BIN;
}



const at_1HH2&
at_1HH2::operator= (const at_1HH2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_1HH2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NH2 ();
}



float
at_1HH2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return 0.44780;
  return 0;
}



void
at_1HH2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_1HH2_BIN;
}



const at_2HD1&
at_2HD1::operator= (const at_2HD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD1 ();
}



float
at_2HD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.10000;
  else if (r->is_ILE ())
    return 0.01860;
  return 0;
}



void
at_2HD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HD1_BIN;
}



const at_2HD2&
at_2HD2::operator= (const at_2HD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_ND2 () || type->is_CD2 ();
}



float
at_2HD2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.10000;
  else if (r->is_ASN ())
    return 0.41960;
  return 0;
}



void
at_2HD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HD2_BIN;
}



const at_2HE2&
at_2HE2::operator= (const at_2HE2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HE2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NE2 ();
}



float
at_2HE2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_GLN ())
    return 0.42510;
  return 0;
}



void
at_2HE2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HE2_BIN;
}



const at_2HG1&
at_2HG1::operator= (const at_2HG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG1 ();
}



float
at_2HG1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ILE ())
    return 0.02360;
  else if (r->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_2HG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HG1_BIN;
}



const at_2HG2&
at_2HG2::operator= (const at_2HG2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HG2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG2 ();
}



float
at_2HG2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_THR ())
    return 0.06420;
  else if (r->is_ILE ())
    return 0.08820;
  else if (r->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_2HG2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HG2_BIN;
}



const at_2HH1&
at_2HH1::operator= (const at_2HH1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HH1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NH1 ();
}



float
at_2HH1::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return 0.44780;
  return 0;
}



void
at_2HH1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HH1_BIN;
}



const at_2HH2&
at_2HH2::operator= (const at_2HH2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_2HH2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_NH2 ();
}



float
at_2HH2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_ARG ())
    return 0.44780;
  return 0;
}



void
at_2HH2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_2HH2_BIN;
}



const at_3HD1&
at_3HD1::operator= (const at_3HD1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_3HD1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD1 ();
}



float
at_3HD1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_LEU ())
    return 0.10000;
  else if (r->is_ILE ())
    return 0.01860;
  return 0;
}



void
at_3HD1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3HD1_BIN;
}



const at_3HD2&
at_3HD2::operator= (const at_3HD2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_3HD2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CD2 ();
}



float
at_3HD2::getAmberCharge (const AbstractResidue *res) const
{
  if (res->GetType ()->is_LEU ())
    return 0.10000;
  return 0;
}



void
at_3HD2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3HD2_BIN;
}



const at_3HG1&
at_3HG1::operator= (const at_3HG1 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_3HG1::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG1 ();
}



float
at_3HG1::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_ILE ())
    return 0.02360;
  else if (r->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_3HG1::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3HG1_BIN;
}



const at_3HG2&
at_3HG2::operator= (const at_3HG2 &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Hydrogen::operator= (right);
      at_SideChain::operator= (right);
    }
  return *this;
}



bool
at_3HG2::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return type->is_CG2 ();
}



float
at_3HG2::getAmberCharge (const AbstractResidue *res) const
{
  t_Residue *r = res->GetType ();

  if (r->is_THR ())
    return 0.06420;
  else if (r->is_ILE ())
    return 0.08820;
  else if (r->is_VAL ())
    return 0.07910;
  return 0;
}



void
at_3HG2::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_3HG2_BIN;
}



const at_MG&
at_MG::operator= (const at_MG &right)
{
  if (this != &right)
    at_Magnesium::operator= (right);
  return *this;
}



void
at_MG::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_MG_BIN;
}



const at_PSAZ&
at_PSAZ::operator= (const at_PSAZ &right)
{
  if (this != &right)
    {
      at_AminoAcid::operator= (right);
      at_Pseudo::operator= (right);
      at_Backbone::operator= (right);
    }
  return *this;
}



bool
at_PSAZ::is_connected (const t_Atom *type, const t_Residue *res) const
{
  return false;
}



void
at_PSAZ::Binoutput (oBinstream &obs) const
{
  obs << (int) AT_PSAZ_BIN;
}
