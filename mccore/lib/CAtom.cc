//                              -*- Mode: C++ -*- 
// CAtom.cc
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Jan 23 15:01:29 2001
// Update Count     : 43
// Status           : Ok.
// 


#include <iostream.h>
#include <string.h>

#include "CAtom.h"

#include "Binstream.h"
#include "CException.h"
#include "Pdbstream.h"



#define AS_AND          2
#define AS_ALL          3
#define AS_BASE         4
#define AS_BACKBONE     5
#define AS_PSE          6
#define AS_NO_HYDROGEN  7
#define AS_NO_PSE_LP    8
#define AS_NO_O2p       9



int CAtom::count = 0;



CAtom::CAtom ()
  : CPoint3D (), mType (0), altLocId (' '), mAtomSerNo (0)
{
  count++;
}



CAtom::CAtom (const CAtom &right)
  : CPoint3D (right), mType (right.mType), altLocId (right.altLocId),
    mAtomSerNo (right.mAtomSerNo)
{
  count++;
}



CAtom::CAtom (float x, float y, float z, t_Atom *type)
  : CPoint3D (x, y, z), mType (type), altLocId (' ')
{
  count++;
}



const CAtom&
CAtom::operator= (const CAtom &right)
{
  if (&right != this)  
    {
      CPoint3D::operator= (right);
      mType = right.mType;
      altLocId = right.altLocId;
      mAtomSerNo = right.mAtomSerNo;
    }
  return *this;
}



void
CAtom::SetAll (float x, float y, float z, t_Atom *type, char loc)
{
  SetXYZ (x, y, z);
  mType = type;
  altLocId = loc;
}



ostream&
operator<< (ostream &os, const CAtom& atom)
{
  return os << (const CPoint3D&) atom
	    << ' ' << *atom.GetType ()
	    << ' ' << atom.GetAltLocId ();
}



iBinstream&
operator>> (iBinstream &ibs, CAtom &atom)
{
  t_Atom *type;
  char altlocid;

  ibs >> (CPoint3D&)atom;
  ibs >> type >> altlocid;
  
  atom.SetType (type);
  atom.SetAltLocId (altlocid);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CAtom &atom)
{
  return obs << (const CPoint3D&) atom << atom.GetType ()
	     << atom.GetAltLocId ();
}



iPdbstream&
operator>> (iPdbstream &ips, CAtom &atom)
{
  while (true)
    {
      size_t len;

      len = ips.getline ();
      if (ips.eof () || ips.eop () || ips.eom () || ips.eoc ())
	return ips;
      if (strcmp (ips.GetRecordType (), "ATOM  ") == 0
	  || strcmp (ips.GetRecordType (), "HETATM") == 0)
	{
	  if (len < 54 || ips.GetAtomType () == 0)
	    continue;
	  ips.getatom (atom);
	  return ips;
	}
    }
}



oPdbstream&
operator<< (oPdbstream &ops, const CAtom &atom)
{
  if (atom.GetType ())    
    ops.putatom (atom);
  return ops;
}



iBinstream&
operator>> (iBinstream &ibs, AtomSet *&as)
{
  int val;

  ibs >> val;
  switch (val)
    {
    case AS_AND:
      {
	AtomSet *op1;
	AtomSet *op2;

	ibs >> op1;
	ibs >> op2;
	as = new atomset_and (op1, op2);
	break;
      }
    case AS_ALL:
      as = new all_atom_set ();
      break;
    case AS_BASE:
      as = new base_atom_set ();
      break;
    case AS_BACKBONE:
      as = new backbone_atom_set ();
      break;
    case AS_PSE:
      as = new pse_atom_set ();
      break;
    case AS_NO_HYDROGEN:
      as = new no_hydrogen_set ();
      break;
    case AS_NO_PSE_LP:
      as = new no_pse_lp_atom_set ();
      break;
    case AS_NO_O2p:
      as = new no_O2p_atom_set ();
      break;
    default:
      throw CFatalIntLibException ("Invalid atom set code.");
    }
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const AtomSet *as)
{
  as->BinOutput (obs);
  return obs;
}



atomset_and&
atomset_and::operator= (const atomset_and &right)
{
  if (this != &right)
    {
      AtomSet::operator= (right);
      delete op1;
      delete op2;
      op1 = right.op1->clone ();
      op2 = right.op2->clone ();
    }
  return *this;
}



atomset_and::operator const char* () const
{
  char str[256];
  
  sprintf (str,
	   "%s %s",
	   op1->operator const char* (),
	   op2->operator const char* ());
  return str;
}



void
atomset_and::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_AND << op1 << op2;
}



void
all_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_ALL;
}



void
base_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_BASE;
}



void
backbone_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_BACKBONE;
}



void
pse_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_PSE;
}



void
no_hydrogen_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_NO_HYDROGEN;
}



void
no_pse_lp_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_NO_PSE_LP;
}



void
no_O2p_atom_set::BinOutput (oBinstream &obs) const
{
  obs << (unsigned char) AS_NO_O2p;
}

