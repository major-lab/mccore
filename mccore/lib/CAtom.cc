//                              -*- Mode: C++ -*- 
// CAtom.cc
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : 
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:25 2000
// Update Count     : 40
// Status           : Ok.
// 


#include <iostream.h>
#include <string.h>

#include "CAtom.h"

#include "Binstream.h"
#include "Pdbstream.h"



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
  return os << (const CPoint3D&) atom << *atom.GetType ()
	    << ' ' << atom.GetAltLocId () << flush;
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
