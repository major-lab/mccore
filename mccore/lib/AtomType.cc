//                              -*- Mode: C++ -*-
// AtomType.cc
// Copyright © 2000, 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Mon Jan 22 15:08:14 2001
// Update Count     : 3
// Status           : Ok.
// 


#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AtomType.h"

#include "McCore.h"
#include "ResidueType.h"
#include "CException.h"
#include "Binstream.h"


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



float
t_Atom::get_charge (const t_Residue *res) const
{
  CFatalLibException exc ("No charge for ");

  exc << *this;
  throw exc;
}



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
  unsigned char id;
  char buf[256];
  char buf2[8];
  map< const char *, t_Atom*, less_string >::iterator pos;
  
  ibs >> id;
  switch (int (id))
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
  obs << (unsigned char) AT_MISC_BIN << mSName << mName;
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
  obs << (unsigned char) AT_NUCLEICACID_BIN;
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
  obs << (unsigned char) AT_AMINOACID_BIN;
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
  obs << (unsigned char) AT_BACKBONE_BIN;
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
  obs << (unsigned char) AT_SIDECHAIN_BIN;
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
  obs << (unsigned char) AT_CARBON_BIN;
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
  obs << (unsigned char) AT_HYDROGEN_BIN;
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
  obs << (unsigned char) AT_NITROGEN_BIN;
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
  obs << (unsigned char) AT_PHOSPHATE_BIN;
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
  obs << (unsigned char) AT_OXYGEN_BIN;
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
  obs << (unsigned char) AT_SULFUR_BIN;
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
  obs << (unsigned char) AT_MAGNESIUM_BIN;
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
  obs << (unsigned char) AT_LONEPAIR_BIN;
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
  obs << (unsigned char) AT_PSEUDO_BIN;
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
at_C1p::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.0394;
  else if (r->is_C ()) return 0.0066;
  else if (r->is_G ()) return 0.0191;
  else if (r->is_U ()) return 0.0674;
  return 0;
}



void
at_C1p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C1p_BIN;
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



void
at_C2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C2p_BIN;
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



void
at_C3p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C3p_BIN;
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



void
at_C4p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C4p_BIN;
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



void
at_C5p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C5p_BIN;
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



void
at_H1p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H1p_BIN;
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



void
at_H2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H2p_BIN;
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



void
at_H3p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H3p_BIN;
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



void
at_H4p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H4p_BIN;
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



void
at_H5p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H5p_BIN;
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



void
at_O1P::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O1P_BIN;
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



void
at_O2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O2p_BIN;
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



void
at_O2P::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O2P_BIN;
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



void
at_O3p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O3p_BIN;
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



void
at_O3P::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O3P_BIN;
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



void
at_O4p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O4p_BIN;
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



void
at_O5p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O5p_BIN;
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



void
at_P::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_P_BIN;
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



void
at_1H2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H2p_BIN;
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



void
at_1H5p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H5p_BIN;
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



void
at_2H2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H2p_BIN;
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



void
at_2H5p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H5p_BIN;
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



void
at_HO2p::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HO2p_BIN;
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
  obs << (unsigned char) AT_HO3p_BIN;
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
at_C2::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.5875;
  else if (r->is_C ()) return 0.7538;
  else if (r->is_G ()) return 0.7657;
  else if (r->is_U ()) return 0.4687;
  return 0;
}



void
at_C2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C2_BIN;
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
at_C4::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.3053;
  else if (r->is_C ()) return 0.8185;
  else if (r->is_G ()) return 0.1222;
  else if (r->is_U ()) return 0.5952;
  return 0;
}



void
at_C4::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C4_BIN;
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
at_C5::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return  0.0515;
  else if (r->is_C ()) return -0.5215;
  else if (r->is_G ()) return  0.1744;
  else if (r->is_U ()) return -0.3635;
  return 0;
}



void
at_C5::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C5_BIN;
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
  obs << (unsigned char) AT_C5M_BIN;
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
at_C6::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return  0.7009;
  else if (r->is_C ()) return  0.0053;
  else if (r->is_G ()) return  0.4770;
  else if (r->is_U ()) return -0.1126;
  return 0;
}



void
at_C6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C6_BIN;
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
at_C8::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.2006;
  else if (r->is_G ()) return 0.1374;
  return 0;
}



void
at_C8::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C8_BIN;
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
at_H1::get_charge (const t_Residue *r) const
{
  if (r->is_G ()) return 0.3424;
  return 0;
}



void
at_H1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H1_BIN;
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
at_H2::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.0473;
  return 0;
}



void
at_H2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H2_BIN;
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
at_H3::get_charge (const t_Residue *r) const
{
  if (r->is_U ())      return 0.3154;
  return 0;
}



void
at_H3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H3_BIN;
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
at_H5::get_charge (const t_Residue *r) const
{
  if (r->is_C ())      return 0.1928;
  else if (r->is_U ()) return 0.1811;
  return 0;
}



void
at_H5::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H5_BIN;
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
at_H6::get_charge (const t_Residue *r) const
{
  if (r->is_C ())      return 0.1958;
  else if (r->is_U ()) return 0.2188;
  return 0;
}



void
at_H6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H6_BIN;
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
  obs << (unsigned char) AT_H7_BIN;
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
at_H8::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return 0.1553;
  else if (r->is_G ()) return 0.1640;
  return 0;
}



void
at_H8::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H8_BIN;
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
at_N1::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return -0.7615;
  else if (r->is_C ()) return -0.0484;
  else if (r->is_G ()) return -0.4787;
  else if (r->is_U ()) return  0.0418;
  return 0;
}



void
at_N1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N1_BIN;
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
at_N2::get_charge (const t_Residue *r) const
{
  if (r->is_G ()) return -0.9672;
  return 0;
}



void
at_N2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N2_BIN;
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
at_N3::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return -0.6997;
  else if (r->is_C ()) return -0.7584;
  else if (r->is_G ()) return -0.6323;
  else if (r->is_U ()) return -0.3549;
  return 0;
}



void
at_N3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N3_BIN;
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
at_N4::get_charge (const t_Residue *r) const
{
  if (r->is_C ()) return -0.9530;
  return 0;
}



void
at_N4::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N4_BIN;
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
at_N6::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return -0.9019;
  return 0;
}



void
at_N6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N6_BIN;
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
at_N7::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return -0.6073;
  else if (r->is_G ()) return -0.5709;
  return 0;
}



void
at_N7::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N7_BIN;
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
at_N9::get_charge (const t_Residue *r) const
{
  if (r->is_A ())      return -0.0251;
  else if (r->is_G ()) return  0.0492;
  return 0;
}



void
at_N9::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N9_BIN;
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
at_O2::get_charge (const t_Residue *r) const
{
  if (r->is_C ())      return -0.6252;
  else if (r->is_U ()) return -0.5477;
  return 0;
}



void
at_O2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O2_BIN;
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
at_O4::get_charge (const t_Residue *r) const
{
  if (r->is_U ()) return -0.5761;
  return 0;
}



void
at_O4::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O4_BIN;
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
at_O6::get_charge (const t_Residue *r) const
{
  if (r->is_G ()) return -0.5597;
  return 0;
}



void
at_O6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O6_BIN;
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
at_1H2::get_charge (const t_Residue *r) const
{
  if (r->is_G ()) return 0.4364;
  return 0;
}



void
at_1H2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H2_BIN;
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
at_1H4::get_charge (const t_Residue *r) const
{
  if (r->is_C ()) return 0.4234;
  return 0;
}



void
at_1H4::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H4_BIN;
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



void
at_1H5M::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H5M_BIN;
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
at_1H6::get_charge (const t_Residue *r) const
{
  if (r->is_A ()) return 0.4115;
  return 0;
}



void
at_1H6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1H6_BIN;
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
at_2H2::get_charge (const t_Residue *r) const
{
  if (r->is_G ()) return 0.4364;
  return 0;
}



void
at_2H2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H2_BIN;
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
at_2H4::get_charge (const t_Residue *r) const
{
  if (r->is_C ()) return 0.4234;
  return 0;
}



void
at_2H4::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H4_BIN;
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



void
at_2H5M::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H5M_BIN;
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
at_2H6::get_charge (const t_Residue *r) const
{
  if (r->is_A ()) return 0.4115;
  return 0;
}



void
at_2H6::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2H6_BIN;
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



void
at_3H5M::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_3H5M_BIN;
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
  obs << (unsigned char) AT_PSY_BIN;
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
  obs << (unsigned char) AT_PSZ_BIN;
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
  obs << (unsigned char) AT_LP1_BIN;
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
  obs << (unsigned char) AT_LP3_BIN;
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
  obs << (unsigned char) AT_LP7_BIN;
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
  obs << (unsigned char) AT_1LP2_BIN;
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
  obs << (unsigned char) AT_1LP4_BIN;
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
  obs << (unsigned char) AT_1LP6_BIN;
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
  obs << (unsigned char) AT_2LP2_BIN;
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
  obs << (unsigned char) AT_2LP4_BIN;
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
  obs << (unsigned char) AT_2LP6_BIN;
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



void
at_H3T::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H3T_BIN;
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



void
at_H5T::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H5T_BIN;
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


void
at_C::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_C_BIN;
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


void
at_CA::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CA_BIN;
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


void
at_CB::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CB_BIN;
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


void
at_CD::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CD_BIN;
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


void
at_CD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CD1_BIN;
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


void
at_CD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CD2_BIN;
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


void
at_CE::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CE_BIN;
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


void
at_CE1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CE1_BIN;
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


void
at_CE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CE2_BIN;
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


void
at_CE3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CE3_BIN;
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


void
at_CG::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CG_BIN;
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


void
at_CG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CG1_BIN;
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


void
at_CG2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CG2_BIN;
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


void
at_CH2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CH2_BIN;
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


void
at_CZ::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CZ_BIN;
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


void
at_CZ2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CZ2_BIN;
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


void
at_CZ3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_CZ3_BIN;
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


void
at_H::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_H_BIN;
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
  obs << (unsigned char) AT_1H_BIN;
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
  obs << (unsigned char) AT_2H_BIN;
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
  obs << (unsigned char) AT_3H_BIN;
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


void
at_HA::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HA_BIN;
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


void
at_HA1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HA1_BIN;
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


void
at_HA2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HA2_BIN;
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


void
at_HB::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HB_BIN;
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


void
at_HB1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HB1_BIN;
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


void
at_HB2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HB2_BIN;
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


void
at_HB3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HB3_BIN;
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


void
at_HD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HD1_BIN;
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


void
at_HD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HD2_BIN;
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


void
at_HE::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HE_BIN;
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


void
at_HE1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HE1_BIN;
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
  return type->is_CE () || type->is_CE2 ();
}


void
at_HE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HE2_BIN;
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


void
at_HE3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HE3_BIN;
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


void
at_HG::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HG_BIN;
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


void
at_HG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HG1_BIN;
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


void
at_HG2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HG2_BIN;
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


void
at_HH::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HH_BIN;
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



void
at_HH2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HH2_BIN;
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
  obs << (unsigned char) AT_HXT_BIN;
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



void
at_HZ::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HZ_BIN;
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



void
at_HZ1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HZ1_BIN;
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



void
at_HZ2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HZ2_BIN;
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



void
at_HZ3::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_HZ3_BIN;
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



void
at_N::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_N_BIN;
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



void
at_ND1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_ND1_BIN;
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



void
at_ND2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_ND2_BIN;
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



void
at_NE::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NE_BIN;
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



void
at_NE1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NE1_BIN;
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



void
at_NE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NE2_BIN;
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



void
at_NH1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NH1_BIN;
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



void
at_NH2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NH2_BIN;
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



void
at_NZ::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_NZ_BIN;
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



void
at_O::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_O_BIN;
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



void
at_OD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OD1_BIN;
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



void
at_OD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OD2_BIN;
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



void
at_OE1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OE1_BIN;
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



void
at_OE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OE2_BIN;
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



void
at_OG::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OG_BIN;
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



void
at_OG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OG1_BIN;
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



void
at_OH::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_OH_BIN;
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
  obs << (unsigned char) AT_OXT_BIN;
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



void
at_SD::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_SD_BIN;
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



void
at_SG::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_SG_BIN;
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



void
at_1HD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HD1_BIN;
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



void
at_1HD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HD2_BIN;
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



void
at_1HE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HE2_BIN;
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



void
at_1HG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HG1_BIN;
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



void
at_1HG2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HG2_BIN;
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



void
at_1HH1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HH1_BIN;
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



void
at_1HH2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_1HH2_BIN;
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



void
at_2HD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HD1_BIN;
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



void
at_2HD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HD2_BIN;
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



void
at_2HE2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HE2_BIN;
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



void
at_2HG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HG1_BIN;
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



void
at_2HG2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HG2_BIN;
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



void
at_2HH1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HH1_BIN;
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



void
at_2HH2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_2HH2_BIN;
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



void
at_3HD1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_3HD1_BIN;
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



void
at_3HD2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_3HD2_BIN;
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



void
at_3HG1::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_3HG1_BIN;
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



void
at_3HG2::Binoutput (oBinstream &obs) const
{
  obs << (unsigned char) AT_3HG2_BIN;
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
  obs << (unsigned char) AT_MG_BIN;
}
