//                              -*- Mode: C++ -*- 
// ResidueTypeImp.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Mar  6 12:27:03 2001
// Last Modified By : Martin Larose
// Last Modified On : Wed Mar  7 13:47:51 2001
// Update Count     : 3
// Status           : Ok.
// 


#include <iostream.h>
#include <stdlib.h>

#include "Binstream.h"
#include "McCore.h"
#include "ResidueTypeImp.h"



#define T_RESIDUE_BIN          1
#define RT_NUCLEICACID_BIN     2
#define RT_AMINOACID_BIN       3 
#define RT_PHOSPHATE_BIN       4
#define RT_PURINE_BIN          5
#define RT_PYRIMIDINE_BIN      6
#define RT_DNA_BIN             7
#define RT_RNA_BIN             8
#define RT_A_BIN               9
#define RT_C_BIN              10
#define RT_G_BIN              11
#define RT_U_BIN              12
#define RT_T_BIN              13
#define RT_RA_BIN             14
#define RT_RC_BIN             15
#define RT_RG_BIN             16
#define RT_RU_BIN             17
#define RT_DA_BIN             18
#define RT_DC_BIN             19
#define RT_DG_BIN             20
#define RT_DT_BIN             21
#define RT_MISC_BIN           22
#define RT_ALA_BIN            23
#define RT_ARG_BIN            24
#define RT_ASN_BIN            25
#define RT_ASP_BIN            26
#define RT_CYS_BIN            27
#define RT_GLN_BIN            28
#define RT_GLU_BIN            29
#define RT_GLY_BIN            30
#define RT_HIS_BIN            31
#define RT_ILE_BIN            32
#define RT_LEU_BIN            33
#define RT_LYS_BIN            34
#define RT_MET_BIN            35
#define RT_PHE_BIN            36
#define RT_PRO_BIN            37
#define RT_SER_BIN            38
#define RT_THR_BIN            39
#define RT_TRP_BIN            40
#define RT_TYR_BIN            41
#define RT_VAL_BIN            42



void
t_Residue::Binoutput (oBinstream &obs) const
{
  obs << char (T_RESIDUE_BIN);
}



iBinstream&
operator>> (iBinstream &ibs, t_Residue *&t)
{
  char id;
  char buf[256];
  map< const char*, t_Residue*, less_string >::iterator pos;
  
  ibs >> id;
  switch (id)
    {
    case RT_NUCLEICACID_BIN:
      t = r_NucleicAcid;
      break;
    case RT_AMINOACID_BIN:
      t = r_AminoAcid;
      break;
    case RT_PHOSPHATE_BIN:
      t = r_Phosphate;
      break;
    case RT_PURINE_BIN:
      t = r_Purine;
      break;
    case RT_PYRIMIDINE_BIN:
      t = r_Pyrimidine;
      break;
    case RT_DNA_BIN:
      t = r_DNA;
      break;
    case RT_RNA_BIN:
      t = r_RNA;
      break;
    case RT_A_BIN:
      t = r_A;
      break;
    case RT_C_BIN:
      t = r_C;
      break;
    case RT_G_BIN:
      t = r_G;
      break;
    case RT_U_BIN:
      t = r_U;
      break;
    case RT_T_BIN:
      t = r_T;
      break;
    case RT_RA_BIN:
      t = r_rA;
      break;
    case RT_RC_BIN:
      t = r_rC;
      break;
    case RT_RG_BIN:
      t = r_rG;
      break;
    case RT_RU_BIN:
      t = r_rU;
      break;
    case RT_DA_BIN:
      t = r_dA;
      break;
    case RT_DC_BIN:
      t = r_dC;
      break;
    case RT_DG_BIN:
      t = r_dG;
      break;
    case RT_DT_BIN:
      t = r_dT;
      break;
    case RT_MISC_BIN: 
      ibs >> buf;
      if ((pos = gMiscResidueString.find (buf)) == gMiscResidueString.end ())
	t = new rt_Misc (buf);
      else
	t = pos->second;
      break;
    case RT_ALA_BIN:
      t = r_ALA;
      break;
    case RT_ARG_BIN:
      t = r_ARG;
      break;
    case RT_ASN_BIN:
      t = r_ASN;
      break;
    case RT_ASP_BIN:
      t = r_ASP;
      break;
    case RT_CYS_BIN:
      t = r_CYS;
      break;
    case RT_GLN_BIN:
      t = r_GLN;
      break;
    case RT_GLU_BIN:
      t = r_GLU;
      break;
    case RT_GLY_BIN:
      t = r_GLY;
      break;
    case RT_HIS_BIN:
      t = r_HIS;
      break;
    case RT_ILE_BIN:
      t = r_ILE;
      break;
    case RT_LEU_BIN:
      t = r_LEU;
      break;
    case RT_LYS_BIN:
      t = r_LYS;
      break;
    case RT_MET_BIN:
      t = r_MET;
      break;
    case RT_PHE_BIN:
      t = r_PHE;
      break;
    case RT_PRO_BIN:
      t = r_PRO;
      break;
    case RT_SER_BIN:
      t = r_SER;
      break;
    case RT_THR_BIN:
      t = r_THR;
      break;
    case RT_TRP_BIN:
      t = r_TRP;
      break;
    case RT_TYR_BIN:
      t = r_TYR;
      break;
    case RT_VAL_BIN:
      t = r_VAL;
      break;
    default:
      t = 0;
    } 
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const t_Residue *t)
{
  t->Binoutput (obs);
  return obs;
}



rt_Misc::rt_Misc (const char *name)
  : t_Residue ()
{
  strncpy (mName, name, 3);
  mName[3] = '\0';
  gMiscResidueString[mName] = this;
}



rt_Misc::rt_Misc (const rt_Misc &right)
  : t_Residue (right)
{
  strcpy (mName, right.mName);
}



const rt_Misc&
rt_Misc::operator= (const rt_Misc &right)
{
  if (this != &right)
    {
      t_Residue::operator= (right);
      strcpy (mName, right.mName);
    }
  return *this;
}



void
rt_Misc::Binoutput (oBinstream &obs) const
{
  obs << char (RT_MISC_BIN) << mName;
}



const rt_NucleicAcid&
rt_NucleicAcid::operator= (const rt_NucleicAcid &right)
{
  if (this != &right)
    t_Residue::operator= (right);
  return *this;
}



void
rt_NucleicAcid::Binoutput (oBinstream &obs) const
{
  obs << char (RT_NUCLEICACID_BIN);
}



const rt_AminoAcid&
rt_AminoAcid::operator= (const rt_AminoAcid &right)
{
  if (this != &right)
    t_Residue::operator= (right);
  return *this;
}



void
rt_AminoAcid::Binoutput (oBinstream &obs) const
{
  obs << char (RT_AMINOACID_BIN);
}



const rt_Phosphate&
rt_Phosphate::operator= (const rt_Phosphate &right)
{
  if (this != &right)
    rt_NucleicAcid::operator= (right);
  return *this;
}



void
rt_Phosphate::Binoutput (oBinstream &obs) const
{
  obs << char (RT_PHOSPHATE_BIN);
}



const rt_Purine&
rt_Purine::operator= (const rt_Purine &right)
{
  if (this != &right)
    rt_NucleicAcid::operator= (right);
  return *this;
}



void
rt_Purine::Binoutput (oBinstream &obs) const
{
  obs << char (RT_PURINE_BIN);
}



const rt_Pyrimidine&
rt_Pyrimidine::operator= (const rt_Pyrimidine &right)
{
  if (this != &right)
    rt_NucleicAcid::operator= (right);
  return *this;
}



void
rt_Pyrimidine::Binoutput (oBinstream &obs) const
{
  obs << char (RT_PYRIMIDINE_BIN);
}



const rt_DNA&
rt_DNA::operator= (const rt_DNA &right)
{
  if (this != &right)
    rt_NucleicAcid::operator= (right);
  return *this;
}



void
rt_DNA::Binoutput (oBinstream &obs) const
{
  obs << char (RT_DNA_BIN);
}



const rt_RNA&
rt_RNA::operator= (const rt_RNA &right)
{
  if (this != &right)
    rt_NucleicAcid::operator= (right);
  return *this;
}



void
rt_RNA::Binoutput (oBinstream &obs) const
{
  obs << char (RT_RNA_BIN);
}



const rt_A&
rt_A::operator= (const rt_A &right)
{
  if (this != &right)
    rt_Purine::operator= (right);
  return *this;
}



void
rt_A::Binoutput (oBinstream &obs) const
{
  obs << char (RT_A_BIN);
}



const rt_C&
rt_C::operator= (const rt_C &right)
{
  if (this != &right)
    rt_Pyrimidine::operator= (right);
  return *this;
}



void
rt_C::Binoutput (oBinstream &obs) const
{
  obs << char (RT_C_BIN);
}



const rt_G&
rt_G::operator= (const rt_G &right)
{
  if (this != &right)
    rt_Purine::operator= (right);
  return *this;
}



void
rt_G::Binoutput (oBinstream &obs) const
{
  obs << char (RT_G_BIN);
}



const rt_U&
rt_U::operator= (const rt_U &right)
{
  if (this != &right)
    rt_Pyrimidine::operator= (right);
  return *this;
}



void
rt_U::Binoutput (oBinstream &obs) const
{
  obs << char (RT_U_BIN);
}



const rt_T&
rt_T::operator= (const rt_T &right)
{
  if (this != &right)
    rt_Pyrimidine::operator= (right);
  return *this;
}



void
rt_T::Binoutput (oBinstream &obs) const
{
  obs << char (RT_T_BIN);
}



const rt_rA&
rt_rA::operator= (const rt_rA &right)
{
  if (this != &right)
    {
      rt_A::operator= (right);
      rt_RNA::operator= (right);
    }
  return *this;
}



void
rt_rA::Binoutput (oBinstream &obs) const
{
  obs << char (RT_RA_BIN);
}



const rt_rC&
rt_rC::operator= (const rt_rC &right)
{
  if (this != &right)
    {
      rt_C::operator= (right);
      rt_RNA::operator= (right);
    }
  return *this;
}



void
rt_rC::Binoutput (oBinstream &obs) const
{
  obs << char (RT_RC_BIN);
}



const rt_rG&
rt_rG::operator= (const rt_rG &right)
{
  if (this != &right)
    {
      rt_G::operator= (right);
      rt_RNA::operator= (right);
    }
  return *this;
}



void
rt_rG::Binoutput (oBinstream &obs) const
{
  obs << char (RT_RG_BIN);
}



const rt_rU&
rt_rU::operator= (const rt_rU &right)
{
  if (this != &right)
    {
      rt_U::operator= (right);
      rt_RNA::operator= (right);
    }
  return *this;
}



void
rt_rU::Binoutput (oBinstream &obs) const
{
  obs << char (RT_RU_BIN);
}



const rt_dA&
rt_dA::operator= (const rt_dA &right)
{
  if (this != &right)
    {
      rt_A::operator= (right);
      rt_DNA::operator= (right);
    }
  return *this;
}



void
rt_dA::Binoutput (oBinstream &obs) const
{
  obs << char (RT_DA_BIN);
}



const rt_dC&
rt_dC::operator= (const rt_dC &right)
{
  if (this != &right)
    {
      rt_C::operator= (right);
      rt_DNA::operator= (right);
    }
  return *this;
}



void
rt_dC::Binoutput (oBinstream &obs) const
{
  obs << char (RT_DC_BIN);
}



const rt_dG&
rt_dG::operator= (const rt_dG &right)
{
  if (this != &right)
    {
      rt_G::operator= (right);
      rt_DNA::operator= (right);
    }
  return *this;
}



void
rt_dG::Binoutput (oBinstream &obs) const
{
  obs << char (RT_DG_BIN);
}



const rt_dT&
rt_dT::operator= (const rt_dT &right)
{
  if (this != &right)
    {
      rt_T::operator= (right);
      rt_DNA::operator= (right);
    }
  return *this;
}



void
rt_dT::Binoutput (oBinstream &obs) const
{
  obs << char (RT_DT_BIN);
}



const rt_ALA&
rt_ALA::operator= (const rt_ALA &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_ALA::Binoutput (oBinstream &obs) const
{
  obs << char (RT_ALA_BIN);
}



const rt_ARG&
rt_ARG::operator= (const rt_ARG &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_ARG::Binoutput (oBinstream &obs) const
{
  obs << char (RT_ARG_BIN);
}



const rt_ASN&
rt_ASN::operator= (const rt_ASN &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_ASN::Binoutput (oBinstream &obs) const
{
  obs << char (RT_ASN_BIN);
}



const rt_ASP&
rt_ASP::operator= (const rt_ASP &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_ASP::Binoutput (oBinstream &obs) const
{
  obs << char (RT_ASP_BIN);
}



const rt_CYS&
rt_CYS::operator= (const rt_CYS &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_CYS::Binoutput (oBinstream &obs) const
{
  obs << char (RT_CYS_BIN);
}



const rt_GLN&
rt_GLN::operator= (const rt_GLN &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_GLN::Binoutput (oBinstream &obs) const
{
  obs << char (RT_GLN_BIN);
}



const rt_GLU&
rt_GLU::operator= (const rt_GLU &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_GLU::Binoutput (oBinstream &obs) const
{
  obs << char (RT_GLU_BIN);
}



const rt_GLY&
rt_GLY::operator= (const rt_GLY &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_GLY::Binoutput (oBinstream &obs) const
{
  obs << char (RT_GLY_BIN);
}



const rt_HIS&
rt_HIS::operator= (const rt_HIS &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_HIS::Binoutput (oBinstream &obs) const
{
  obs << char (RT_HIS_BIN);
}



const rt_ILE&
rt_ILE::operator= (const rt_ILE &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_ILE::Binoutput (oBinstream &obs) const
{
  obs << char (RT_ILE_BIN);
}



const rt_LEU&
rt_LEU::operator= (const rt_LEU &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_LEU::Binoutput (oBinstream &obs) const
{
  obs << char (RT_LEU_BIN);
}



const rt_LYS&
rt_LYS::operator= (const rt_LYS &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_LYS::Binoutput (oBinstream &obs) const
{
  obs << char (RT_LYS_BIN);
}



const rt_MET&
rt_MET::operator= (const rt_MET &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_MET::Binoutput (oBinstream &obs) const
{
  obs << char (RT_MET_BIN);
}



const rt_PHE&
rt_PHE::operator= (const rt_PHE &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_PHE::Binoutput (oBinstream &obs) const
{
  obs << char (RT_PHE_BIN);
}



const rt_PRO&
rt_PRO::operator= (const rt_PRO &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_PRO::Binoutput (oBinstream &obs) const
{
  obs << char (RT_PRO_BIN);
}



const rt_SER&
rt_SER::operator= (const rt_SER &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_SER::Binoutput (oBinstream &obs) const
{
  obs << char (RT_SER_BIN);
}



const rt_THR&
rt_THR::operator= (const rt_THR &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_THR::Binoutput (oBinstream &obs) const
{
  obs << char (RT_THR_BIN);
}



const rt_TRP&
rt_TRP::operator= (const rt_TRP &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_TRP::Binoutput (oBinstream &obs) const
{
  obs << char (RT_TRP_BIN);
}



const rt_TYR&
rt_TYR::operator= (const rt_TYR &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_TYR::Binoutput (oBinstream &obs) const
{
  obs << char (RT_TYR_BIN);
}



const rt_VAL&
rt_VAL::operator= (const rt_VAL &right)
{
  if (this != &right)
    rt_AminoAcid::operator= (right);
  return *this;
}



void
rt_VAL::Binoutput (oBinstream &obs) const
{
  obs << char (RT_VAL_BIN);
}



ostream&
operator<< (ostream &os, const t_Residue *restype)
{
  return os << *restype;
}
