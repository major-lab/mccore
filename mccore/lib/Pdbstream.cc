//                              -*- Mode: C++ -*- 
// Pdbstream.cc
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.19.12.2 $
// $Id: Pdbstream.cc,v 1.19.12.2 2003-12-05 19:59:12 larosem Exp $
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

#include <algorithm>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "AbstractResidue.h"
#include "AtomTypeImp.h"
#include "CAtom.h"
#include "McCore.h"
#include "Model.h"
#include "Pdbstream.h"
#include "ResidueTypeImp.h"



char*
iPdbstream::Strip (char * cp)
{
  char *top = cp;
  
  for (char *cpp = cp; *cpp; ++cpp)
    if(*cpp != ' ')
      *cp++ = *cpp;
  *cp = 0;
  return top;
}



t_Atom*
iPdbstream::GetAtomType (char *s, t_Residue *res_type)
{
  int i;
  char tmpstr[5];

  for (i = 0; i < 4; ++i)
    {
      s[i] = toupper (s[i]);
      if (s[i] == '\'')
	s[i] = '*';
    }
  strcpy (tmpstr, s);
  Strip (tmpstr);
  if (strcmp (tmpstr, "C1*") == 0)
    return a_C1p;
  if (strcmp (tmpstr, "C2*") == 0)
    return a_C2p;
  if (strcmp (tmpstr, "C3*") == 0)
    return a_C3p;
  if (strcmp (tmpstr, "C4*") == 0)
    return a_C4p;
  if (strcmp (tmpstr, "C5*") == 0)
    return a_C5p;
  if (strcmp (tmpstr, "H1*") == 0)
    return a_H1p;
  if (strcmp (tmpstr, "H2*") == 0)
    return a_H2p;
  if (strcmp (tmpstr, "H3*") == 0)
    return a_H3p;
  if (strcmp (tmpstr, "H4*") == 0)
    return a_H4p;
  if (strcmp (tmpstr, "H5*") == 0)
    return a_H5p;
  if (strcmp (tmpstr, "1H2*") == 0 || strcmp (tmpstr, "H2*1") == 0)
    return a_1H2p;
  if (strcmp (tmpstr, "1H5*") == 0 || strcmp (tmpstr, "H5*1") == 0)
    return a_1H5p;
  if (strcmp (tmpstr, "2H2*") == 0)
    return a_2H2p;
  if (strcmp (tmpstr, "2H5*") == 0 || strcmp (tmpstr, "H5**") == 0
      || strcmp (tmpstr, "H5*2") == 0)
    return a_2H5p;
  if (strcmp (tmpstr, "HO2*") == 0 || strcmp (tmpstr, "H2**") == 0
      || strcmp (tmpstr, "HO*2") == 0 || strcmp (tmpstr, "2HO*") == 0)
    return a_HO2p;
  if (strcmp (tmpstr, "HO3*") == 0 || strcmp (tmpstr, "HO*3") == 0)
    return a_HO3p;
  if (strcmp (tmpstr, "O1P") == 0)
    return a_O1P;
  if (strcmp (tmpstr, "O2*") == 0)
    return a_O2p;
  if (strcmp (tmpstr, "O2P") == 0)
    return a_O2P;
  if (strcmp (tmpstr, "O3*") == 0 || strcmp (tmpstr, "O3T") == 0)
    return a_O3p;
  if (strcmp (tmpstr, "O3P") == 0)
    return a_O3P;
  if (strcmp (tmpstr, "O4*") == 0)
    return a_O4p;
  if (strcmp (tmpstr, "O5*") == 0 || strcmp (tmpstr, "O5T") == 0)
    return a_O5p;
  if (strcmp (tmpstr, "OXT") == 0)
    return a_OXT;
  if (strcmp (tmpstr, "P") == 0)
    return a_P;
  if (strcmp (tmpstr, "C2") == 0)
    return a_C2;
  if (strcmp (tmpstr, "C4") == 0)
    return a_C4;
  if (strcmp (tmpstr, "C5") == 0)
    return a_C5;
  if (strcmp (tmpstr, "C5M") == 0 || strcmp (tmpstr, "C7") == 0
      || strcmp (tmpstr, "C5A") == 0)
    return a_C5M;
  if (strcmp (tmpstr, "C6") == 0)
    return a_C6;
  if (strcmp (tmpstr, "C8") == 0)
    return a_C8;
  if (strcmp (tmpstr, "H1") == 0)
    return a_H1;
  if (strcmp (tmpstr, "H2") == 0)
    return a_H2;
  if (strcmp (tmpstr, "H3") == 0)
    return a_H3;
  if (strcmp (tmpstr, "H5") == 0)
    return a_H5;
  if (strcmp (tmpstr, "H6") == 0)
    return a_H6;
  if (strcmp (tmpstr, "H7") == 0)
    return a_H7;
  if (strcmp (tmpstr, "H8") == 0)
    return a_H8;
  if (strcmp (tmpstr, "1H2") == 0 || strcmp (tmpstr, "H21") == 0)
    return a_1H2;
  if (strcmp (tmpstr, "1H4") == 0 || strcmp (tmpstr, "H41") == 0)
    return a_1H4;
  if (strcmp (tmpstr, "1H5M") == 0 || strcmp (tmpstr, "H71") == 0
      || strcmp (tmpstr, "1H5A") == 0)
    return a_1H5M;
  if (strcmp (tmpstr, "1H6") == 0 || strcmp (tmpstr, "H61") == 0)
    return a_1H6;
  if (strcmp (tmpstr, "2H2") == 0 || strcmp (tmpstr, "H22") == 0)
    return a_2H2;
  if (strcmp (tmpstr, "2H4") == 0 || strcmp (tmpstr, "H42") == 0)
    return a_2H4;
  if (strcmp (tmpstr, "2H5M") == 0 || strcmp (tmpstr, "H72") == 0
      || strcmp (tmpstr, "2H5A") == 0)
    return a_2H5M;
  if (strcmp (tmpstr, "2H6") == 0 || strcmp (tmpstr, "H62") == 0)
    return a_2H6;
  if (strcmp (tmpstr, "3H5M") == 0 || strcmp (tmpstr, "H73") == 0
      || strcmp (tmpstr, "3H5A") == 0)
    return a_3H5M;
  if (strcmp (tmpstr, "N1") == 0)
    return a_N1;
  if (strcmp (tmpstr, "N2") == 0)
    return a_N2;
  if (strcmp (tmpstr, "N3") == 0)
    return a_N3;
  if (strcmp (tmpstr, "N4") == 0)
    return a_N4;
  if (strcmp (tmpstr, "N6") == 0)
    return a_N6;
  if (strcmp (tmpstr, "N7") == 0)
    return a_N7;
  if (strcmp (tmpstr, "N9") == 0)
    return a_N9;
  if (strcmp (tmpstr, "O2") == 0)
    return a_O2;
  if (strcmp (tmpstr, "O4") == 0)
    return a_O4;
  if (strcmp (tmpstr, "O6") == 0)
    return a_O6;
  if (strcmp (tmpstr, "2LP6") == 0)
    return a_2LP6;
  if (strcmp (tmpstr, "1LP6") == 0)
    return a_1LP6;
  if (strcmp (tmpstr, "LP7") == 0)
    return a_LP7;
  if (strcmp (tmpstr, "LP3") == 0)
    return a_LP3;
  if (strcmp (tmpstr, "LP1") == 0)
    return a_LP1;
  if (strcmp (tmpstr, "2LP2") == 0)
    return a_2LP2;
  if (strcmp (tmpstr, "1LP2") == 0)
    return a_1LP2;
  if (strcmp (tmpstr, "2LP4") == 0)
    return a_2LP4;
  if (strcmp (tmpstr, "1LP4") == 0)
    return a_1LP4;
  if (strcmp (tmpstr, "PSY") == 0)
    return a_PSY;
  if (strcmp (tmpstr, "PSZ") == 0)
    return a_PSZ;
  if (strcmp (tmpstr, "H3T") == 0)
    return a_H3T;
  if (strcmp (tmpstr, "H5T") == 0)
    return a_H5T;
  if (strcmp (tmpstr, "C") == 0)
    return a_C;
  if (strcmp (tmpstr, "CA") == 0)
    return a_CA;
  if (strcmp (tmpstr, "CB") == 0)
    return a_CB;
  if (strcmp (tmpstr, "CD") == 0)
    return a_CD;
  if (strcmp (tmpstr, "CD1") == 0)
    return a_CD1;
  if (strcmp (tmpstr, "CD2") == 0)
    return a_CD2;
  if (strcmp (tmpstr, "CE") == 0)
    return a_CE;
  if (strcmp (tmpstr, "CE1") == 0)
    return a_CE1;
  if (strcmp (tmpstr, "CE2") == 0)
    return a_CE2;
  if (strcmp (tmpstr, "CE3") == 0)
    return a_CE3;
  if (strcmp (tmpstr, "CG") == 0)
    return a_CG;
  if (strcmp (tmpstr, "CG1") == 0)
    return a_CG1;
  if (strcmp (tmpstr, "CG2") == 0)
    return a_CG2;
  if (strcmp (tmpstr, "CH2") == 0)
    return a_CH2;
  if (strcmp (tmpstr, "CZ") == 0)
    return a_CZ;
  if (strcmp (tmpstr, "CZ2") == 0)
    return a_CZ2;
  if (strcmp (tmpstr, "CZ3") == 0)
    return a_CZ3;
  if (strcmp (tmpstr, "H") == 0)
    return a_H;
  if (strcmp (tmpstr, "1H") == 0 || strcmp (tmpstr, "HN1") == 0)
    return a_1H;
  if (strcmp (tmpstr, "2H") == 0 || strcmp (tmpstr, "HN2") == 0)
    return a_2H;
  if (strcmp (tmpstr, "3H") == 0 || strcmp (tmpstr, "HN3") == 0)
    return a_3H;
  if (strcmp (tmpstr, "HA") == 0)
    return a_HA;
  if (strcmp (tmpstr, "1HA") == 0)
    return a_HA1;
  if (strcmp (tmpstr, "2HA") == 0)
    return a_HA2;
  if (strcmp (tmpstr, "HB") == 0)
    return a_HB;
  if (strcmp (tmpstr, "1HB") == 0)
    return a_HB1;
  if (strcmp (tmpstr, "2HB") == 0)
    return a_HB2;
  if (strcmp (tmpstr, "3HB") == 0)
    return a_HB3;
  if (strcmp (tmpstr, "1HD") == 0 || strcmp (tmpstr, "HD1") == 0)
    return a_HD1;
  if (strcmp (tmpstr, "2HD") == 0 || strcmp (tmpstr, "HD2") == 0)
    return a_HD2;
  if (strcmp (tmpstr, "HE") == 0)
    return a_HE;
  if (strcmp (tmpstr, "1HE") == 0 || strcmp (tmpstr, "HE1") == 0)
    return a_HE1;
  if (strcmp (tmpstr, "2HE") == 0 || strcmp (tmpstr, "HE2") == 0)
    return a_HE2;
  if (strcmp (tmpstr, "3HE") == 0 || strcmp (tmpstr, "HE3") == 0)
    return a_HE3;
  if (strcmp (tmpstr, "HG") == 0)
    return a_HG;
  if (strcmp (tmpstr, "HG1") == 0 || strcmp (tmpstr, "1HG") == 0)
    return a_HG1;
  if (strcmp (tmpstr, "2HG") == 0)
    return a_HG2;
  if (strcmp (tmpstr, "HH") == 0)
    return a_HH;
  if (strcmp (tmpstr, "HH2") == 0)
    return a_HH2;
  if (strcmp (tmpstr, "HXT") == 0)
    return a_HXT;
  if (strcmp (tmpstr, "HZ") == 0)
    return a_HZ;
  if (strcmp (tmpstr, "1HZ") == 0)
    return a_HZ1;
  if (strcmp (tmpstr, "HZ2") == 0 || strcmp (tmpstr, "2HZ") == 0)
    return a_HZ2;
  if (strcmp (tmpstr, "HZ3") == 0 || strcmp (tmpstr, "3HZ") == 0)
    return a_HZ3;
  if (strcmp (tmpstr, "N") == 0)
    return a_N;
  if (strcmp (tmpstr, "ND1") == 0)
    return a_ND1;
  if (strcmp (tmpstr, "ND2") == 0)
    return a_ND2;
  if (strcmp (tmpstr, "NE") == 0)
    return a_NE;
  if (strcmp (tmpstr, "NE1") == 0)
    return a_NE1;
  if (strcmp (tmpstr, "NE2") == 0)
    return a_NE2;
  if (strcmp (tmpstr, "NH1") == 0)
    return a_NH1;
  if (strcmp (tmpstr, "NH2") == 0)
    return a_NH2;
  if (strcmp (tmpstr, "NZ") == 0)
    return a_NZ;
  if (strcmp (tmpstr, "O") == 0 && res_type->is_AminoAcid ())
    return a_O;
  if (strcmp (tmpstr, "OD1") == 0)
    return a_OD1;
  if (strcmp (tmpstr, "OD2") == 0)
    return a_OD2;
  if (strcmp (tmpstr, "OE1") == 0)
    return a_OE1;
  if (strcmp (tmpstr, "OE2") == 0)
    return a_OE2;
  if (strcmp (tmpstr, "OG") == 0)
    return a_OG;
  if (strcmp (tmpstr, "OG1") == 0)
    return a_OG1;
  if (strcmp (tmpstr, "OH") == 0)
    return a_OH;
  if (strcmp (tmpstr, "SD") == 0)
    return a_SD;
  if (strcmp (tmpstr, "SG") == 0)
    return a_SG;
  if (strcmp (tmpstr, "1HD1") == 0)
    return a_1HD1;
  if (strcmp (tmpstr, "1HD2") == 0)
    return a_1HD2;
  if (strcmp (tmpstr, "1HE2") == 0)
    return a_1HE2;
  if (strcmp (tmpstr, "1HG1") == 0)
    return a_1HG1;
  if (strcmp (tmpstr, "1HG2") == 0)
    return a_1HG2;
  if (strcmp (tmpstr, "1HH1") == 0)
    return a_1HH1;
  if (strcmp (tmpstr, "1HH2") == 0)
    return a_1HH2;
  if (strcmp (tmpstr, "2HD1") == 0)
    return a_2HD1;
  if (strcmp (tmpstr, "2HD2") == 0)
    return a_2HD2;
  if (strcmp (tmpstr, "2HE2") == 0)
    return a_2HE2;
  if (strcmp (tmpstr, "2HG1") == 0)
    return a_2HG1;
  if (strcmp (tmpstr, "2HG2") == 0)
    return a_2HG2;
  if (strcmp (tmpstr, "2HH1") == 0)
    return a_2HH1;
  if (strcmp (tmpstr, "2HH2") == 0)
    return a_2HH2;
  if (strcmp (tmpstr, "3HD1") == 0)
    return a_3HD1;
  if (strcmp (tmpstr, "3HD2") == 0)
    return a_3HD2;
  if (strcmp (tmpstr, "3HG1") == 0)
    return a_3HG1;
  if (strcmp (tmpstr, "3HG2") == 0)
    return a_3HG2;
  if (strcmp (tmpstr, "MG") == 0)
    return a_MG;
  if (strcmp (tmpstr, "PSAZ") == 0)
    return a_PSAZ;
  
  // This is an unknown type...
  map< const char *, t_Atom*, less_string >::iterator pos
    = gMiscAtomString.find (tmpstr);
  if (pos == gMiscAtomString.end ())
    return new at_Misc (tmpstr, s);
  else
    return pos->second;
}



t_Residue*
iPdbstream::GetResidueType (char *s)
{
  int l;
  char tmp[4];

  strcpy (tmp, s);
  Strip (s);
  l = strlen (s);

  if (l == 1)
    {
      switch (s[0])
	{
	case 'A':
	  return r_A;
	case 'C':
	  return r_C;
	case 'G':
	  return r_G;
	case 'U':
	  return r_U;
	case 'T':
	  return r_T;
	}
    }
  else if (l == 2)
    {
      if (strcmp (s, "RA") == 0 || strcmp (s, "DA") == 0)
	return r_A;
      if (strcmp (s, "RC") == 0 || strcmp (s, "DC") == 0)
	return r_C;
      if (strcmp (s, "RG") == 0 || strcmp (s, "DG") == 0)
	return r_G;
      if (strcmp (s, "RU") == 0)
	return r_U;
      if (strcmp (s, "DT") == 0)
	return r_T;
    }
  else if (l == 3)
    {
      if (strcmp (s, "ADE") == 0 || strcmp (s, "RA5") == 0
	  || strcmp (s, "RA3") == 0 || strcmp (s, "DA5") == 0
	  || strcmp (s, "DA3") == 0)
	return r_A;
      if (strcmp (s, "CYT") == 0 || strcmp (s, "RC5") == 0
	  || strcmp (s, "RC3") == 0 || strcmp (s, "DC5") == 0
	  || strcmp (s, "DC3") == 0)
	return r_C;
      if (strcmp (s, "GUA") == 0 || strcmp (s, "RG5") == 0
	  || strcmp (s, "RG3") == 0 || strcmp (s, "DG5") == 0
	  || strcmp (s, "DG3") == 0)
	return r_G;
      if (strcmp (s, "TYM") == 0 || strcmp (s, "DT5") == 0
	  || strcmp (s, "DT3") == 0)
	return r_T;
      if (strcmp (s, "URI") == 0 || strcmp (s, "RU5") == 0
	  || strcmp (s, "RU3") == 0 || strcmp (s, "URA") == 0)
	return r_U;
      if (strcmp (s, "PO4") == 0)
	return r_Phosphate;
      if (strcmp (s, "ALA") == 0)
	return r_ALA;
      if (strcmp (s, "ARG") == 0)
	return r_ARG;
      if (strcmp (s, "ASN") == 0)
	return r_ASN;
      if (strcmp (s, "ASP") == 0)
	return r_ASP;
      if (strcmp (s, "CYS") == 0)
	return r_CYS;
      if (strcmp (s, "GLN") == 0)
	return r_GLN;
      if (strcmp (s, "GLU") == 0)
	return r_GLU;
      if (strcmp (s, "GLY") == 0)
	return r_GLY;
      if (strcmp (s, "HIS") == 0)
	return r_HIS;
      if (strcmp (s, "ILE") == 0)
	return r_ILE;
      if (strcmp (s, "LEU") == 0)
	return r_LEU;
      if (strcmp (s, "LYS") == 0)
	return r_LYS;
      if (strcmp (s, "MET") == 0)
	return r_MET;
      if (strcmp (s, "PHE") == 0)
	return r_PHE;
      if (strcmp (s, "PRO") == 0)
	return r_PRO;
      if (strcmp (s, "SER") == 0)
	return r_SER;
      if (strcmp (s, "THR") == 0)
	return r_THR;
      if (strcmp (s, "TRP") == 0)
	return r_TRP;
      if (strcmp (s, "TYR") == 0)
	return r_TYR;
      if (strcmp (s, "VAL") == 0)
	return r_VAL;
    }

  // This is an unknown type...
  map< const char *, t_Residue*, less_string >::iterator i
    = gMiscResidueString.find (tmp);
  
  if (i == gMiscResidueString.end ())
    return new rt_Misc (tmp);
  else
    return i->second;
}



template< class T >
iPdbstream&
iPdbstream::operator>> (T& obj)
{
  *(istream*)this >> obj;
  return *this;
}



iPdbstream&
iPdbstream::getline (char *buf, unsigned int sz)
{
  int c;
  
  while (sz > 1 && (c = get ()) != EOF && c != '\n' && c != '\r')
    {
      *buf++ = c;
      --sz;
    }
  *buf = '\0';
  return *this;
}



size_t
iPdbstream::getline ()
{
  end_of_model = false;
  end_of_chain = false;
  getline (line, 256);
  if (strncmp (line, "TER   ", 6) == 0)
    end_of_chain = true;
  else if (strncmp (line, "ENDMDL", 6) == 0)
    end_of_model = true;
  else if (strncmp (line, "END   ", 6) == 0)
    end_of_pdb = true;
  return strlen (line);
}



const char*
iPdbstream::GetRecordType () const
{
  strncpy (buffer, line, 6);
  buffer[6] = '\0';
  return buffer;
}



t_Atom*
iPdbstream::GetAtomType () const
{
  strncpy (buffer, line + 12, 4);
  buffer[4] = '\0';
  return GetAtomType (buffer, current_res_type);
}



char
iPdbstream::GetAltLocId () const
{
  return line[16];
}



float
iPdbstream::GetX () const
{
  strncpy (buffer, line + 30, 8);
  buffer[8] = '\0';
  return atof (buffer);
}



float
iPdbstream::GetY () const
{
  strncpy (buffer, line + 38, 8);
  buffer[8] = '\0';
  return atof (buffer);
}



float
iPdbstream::GetZ () const
{
  strncpy (buffer, line + 46, 8);
  buffer[8] = '\0';
  return atof (buffer);
}



CAtom&
iPdbstream::getatom (CAtom &atom)
{
  char buf[5];
  
  strncpy (buf, line + 17, 3);
  buf[3] = '\0';
  current_res_type = GetResidueType (buf);
  strncpy (buf, line + 22, 4);
  buf[4] = '\0';
  current_res_id = CResId (atoi (buf), line[21], line[26]);

  atom.SetAll (GetX (), GetY (), GetZ (), GetAtomType (), GetAltLocId ());
  return atom;
}


  
void
iPdbstream::KeepAtom (const CAtom &atom)
{
  if (previous_atom)
    delete previous_atom;
  previous_atom = new CAtom (atom);
}



void
iPdbstream::DeleteAtom ()
{
  delete previous_atom;
  previous_atom = 0;
}



void
iPdbstream::NewRes ()
{
  if (eom ())
    previous_res_type = 0;
  else
    {
      previous_res_type = GetResType ();
      previous_res_id = GetResId ();
    }
}



void
iPdbstream::open ()
{
  previous_atom = 0;
  previous_res_type = 0;
  current_res_type = 0;
  end_of_chain = false;
  end_of_model = false;
  end_of_pdb = false;
}



void
oPdbstream::SetResId (const CResId &resid)
{
  resno = resid.GetResNo ();
  chainid = resid.GetChainId ();
  iCode = resid.getInsertionCode ();
}



void
oPdbstream::open ()
{
  mCurrentAtomNo = 1;
  delete atomset;
  atomset = new no_pse_lp_atom_set ();
  restype = 0;
  mModelNo = 1;
}



void
oPdbstream::putheader ()
{
  char str[81];
  char str2[81];
  
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "EXPDTA";
  setf (ios::right, ios::adjustfield);
  *this << "    " << "THEORETICAL MODEL" << endl;
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "AUTHOR";
  setf (ios::right, ios::adjustfield);
  gethostname (str, 80);
  *this << "    " << getenv ("LOGNAME") << '@' << str << endl;
  putremark (220, "");
  putremark (220, "EXPERIMENTAL DETAILS");
  putremark (220, "EXPERIMENT TYPE                : THEORETICAL MODELLING");
  putremark (220, "");
  strcpy (str, "CREATION DATE ");
  strcat (str, get_current_time (str2));
  putremark (220, str);
}



void
oPdbstream::putremark (unsigned int k, const char *rem)
{
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "REMARK";
  setf (ios::right, ios::adjustfield);
  *this << ' ' << setw (3) << k << ' ' << rem << endl;
}



void
oPdbstream::putatom (const CAtom &atom)
{
  if (atomset->operator() (atom))
    {
      setf (ios::left, ios::adjustfield);
//        if (restype->is_NucleicAcid () || restype->is_AminoAcid ())
      *this << setw (6) << "ATOM";
//        else
//  	*this << setw (6) << "HETATM";
      setf (ios::right, ios::adjustfield);
      setf (ios::fixed, ios::floatfield);
      precision (3);
      *this << setw (5) << mCurrentAtomNo
	    << ' '
	    << atom.GetType ()->getPDBRep ()
	    << atom.GetAltLocId ()
	    << restype->getPDBRep ()
	    << ' '
	    << chainid
	    << setw (4) << resno
	    << iCode
	    << "   "
	    << setw (8) << atom.GetX ()
	    << setw (8) << atom.GetY ()
	    << setw (8) << atom.GetZ ()
	    << "                          " << endl;
      atom.SetAtomSerNo (mCurrentAtomNo);
      ++mCurrentAtomNo;
    }
}



void
oPdbstream::putmodel (const Model &model)
{
  MODEL ();
  *this << model;
  ENDMDL ();
}



void
oPdbstream::putconect (const Model &model)
{
  Model::const_iterator cit1, cit2;
  
  for (cit2 = model.begin (), cit1 = cit2++;
       cit2 != model.end ();
       ++cit1, ++cit2)
    if (((CResId)*cit1).GetChainId () == ((CResId)*cit2).GetChainId ()
	&& ((CResId)*cit1).GetResNo () + 1 == ((CResId)*cit2).GetResNo ())
      {
	AbstractResidue::const_iterator a, b;
	
	a = find ((*cit1).begin (), (*cit1).end (), a_O3p);
	b = find ((*cit2).begin (), (*cit2).end (), a_P);
	if (a != (*cit1).end () && b != (*cit2).end ())
	  {
	    setf (ios::left, ios::adjustfield);
	    *this << setw (6) << "CONECT";
	    setf (ios::right, ios::adjustfield);
	    *this << setw (5) << (*a).GetAtomSerNo ()
		  << setw (5) << (*b).GetAtomSerNo () << endl;
	  }
      }
}	  



void
oPdbstream::MODEL ()
{
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "MODEL";
  setf (ios::right, ios::adjustfield);
  *this << "    "
	<< setw (4) << mModelNo << endl;
  ++mModelNo;
}



void
oPdbstream::TER ()
{
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "TER";
  setf (ios::right, ios::adjustfield);
  *this << setw (5) << mCurrentAtomNo
	<< "      "
	<< restype->getPDBRep ()
	<< ' '
	<< chainid
	<< setw (4) << resno
	<< ' ' << endl;
  ++mCurrentAtomNo;
}



void
oPdbstream::ENDMDL ()
{
  *this << setw (6) << "ENDMDL" << endl;
}



void
oPdbstream::END ()
{
  setf (ios::left, ios::adjustfield);
  *this << setw (6) << "END" << endl;
  setf (ios::right, ios::adjustfield);
}
