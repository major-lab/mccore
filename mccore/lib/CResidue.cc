//                              -*- Mode: C++ -*- 
// CResidue.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Fri Nov 16 13:30:56 2001
// Update Count     : 31
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

#include <iostream.h>
#include <set.h>
#include <algo.h>
#include <stdarg.h>

#include "AtomType.h"
#include "Binstream.h"
#include "CException.h"
#include "CPoint3D.h"
#include "CResidue.h"
#include "McCore.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "ResidueTypeImp.h"



CResidue::CResidue (t_Residue *type,
		    const vector< CAtom > &vec,
		    const CResId &nId)
  : AbstractResidue (nId, type),
    mAtomRef (vec),
    isPlaced (false),
    isIdentity (true)
{
  init ();
}



CResidue::CResidue (const CResidue& right)
  : AbstractResidue (right),
    mAtomRef (right.mAtomRef),
    mAtomRes (right.mAtomRes),
    isPlaced (right.isPlaced),
    isIdentity (right.isIdentity)
{
}



CResidue&
CResidue::operator= (const CResidue &right)
{
  if (&right != this)
    {
      AbstractResidue::operator= (right);
      mAtomRef = right.mAtomRef;
      mAtomRes = right.mAtomRes;
      isPlaced = right.isPlaced;
      isIdentity = right.isIdentity;
    }
  return *this;
}



AbstractResidue&
CResidue::operator= (const CTransfo &tfo)
{
  mTfo = tfo; 
  isPlaced = false;
  isIdentity = mTfo.isIdentity ();
  return *this;
}



CAtom&
CResidue::operator[] (t_Atom *type)
{
  ResMap::iterator i = mAtomIndex.find (type);
  
  if (i == mAtomIndex.end ())
    {
      mAtomRef.push_back (CAtom ());
      mAtomIndex[type] = size ();
      mAtomRes.push_back (CAtom ());
      i = mAtomIndex.find (type);
    }
  return place (i->second);
}



const CAtom&
CResidue::operator[] (const t_Atom *type) const
{
  ResMap::const_iterator cit = mAtomIndex.find (type);

  if (cit != mAtomIndex.end ())
    return res (cit->second);
  else
    return res (size ());
}



CResidue::iterator
CResidue::find (const t_Atom *k)
{
  ResMap::iterator it = mAtomIndex.find (k);

  if (it == mAtomIndex.end ())
    return end ();
  else
    return iterator (this, it);
}



CResidue::const_iterator
CResidue::find (const t_Atom *k) const
{
  ResMap::const_iterator cit = mAtomIndex.find (k);

  if (cit == mAtomIndex.end ())
    return end ();
  else
    return const_iterator (this, cit);
}



void
CResidue::init ()
{
  const CAtom *pivot[3] = {0, 0, 0};
  vector< CAtom >::iterator it = mAtomRef.begin ();
  size_type i = 0;

  mAtomIndex.clear ();
  mAtomRes.clear ();
  while (it != mAtomRef.end ())
    {
      t_Atom *type = it->GetType ();
      ResMap::iterator pos = mAtomIndex.find (type);

      if (pos != mAtomIndex.end ())
	{
	  gOut (2) << "CResidue: Duplicated atom [" << *type
		   << "] in residue " << resId << "." << endl;
	  it = mAtomRef.erase (it);
	}
      else
	{
	  mAtomIndex[type] = i++;
	  ++it;
	}
    }
  mAtomRes.reserve (size ());
  mAtomRes.resize (size ());

  if (! mType)
    return;
  
  // PSY and PSZ creation for nucleic acid.
  if (mType->is_Purine () || mType->is_Pyrimidine ())
    {
      const CPoint3D *p1 = 0, *p2 = 0, *p3 = 0;
      
      if ((mType->is_Purine ()
	   && (p1 = ref (a_N9))
	   && (p2 = ref (a_C8))
	   && (p3 = ref (a_C4)))
	  || (mType->is_Pyrimidine ()
	      && (p1 = ref (a_N1))
	      && (p2 = ref (a_C6))
	      && (p3 = ref (a_C2))))
	{
	  CPoint3D a = (*p2 - *p1).Normalize ();
	  CPoint3D b = (*p3 - *p1).Normalize ();
	  CPoint3D Y = *p1 + (a + b).Normalize ();
	  CPoint3D Z = *p1 + (b.Cross (a)).Normalize ();

	  insert (CAtom (Y.GetX (), Y.GetY (), Y.GetZ (), a_PSY));
	  insert (CAtom (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSZ));
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut (1) << "Residue " << *mType << "-" << resId
		   << " is missing one or more critical atoms." 
		   << endl;
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
    }
  else if (mType->is_AminoAcid ())
    {
      const CPoint3D *p1 = 0, *p2 = 0, *p3 = 0;
      
      if ((p1 = ref (a_CA)) && (p2 = ref (a_N)) && (p3 = ref (a_C)))
	{
	  CPoint3D a = (*p2 - *p1).Normalize ();
	  CPoint3D b = (*p3 - *p1).Normalize ();
	  CPoint3D Z = *p1 + b.Cross (a).Normalize ();

	  insert (CAtom (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSAZ));
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut (1) << "Residue " << *mType << "-" << resId
		   << " is missing one or more critical atoms." 
		   << endl;
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
    }
  
  // Set Pivot
  if (mType->is_Phosphate ())
    {
      pivot[0] = ref (a_P);
      pivot[1] = ref (a_O3p);
      pivot[2] = ref (a_O5p);
    }
  else if (mType->is_NucleicAcid ())
    {
      pivot[0] = mType->is_Purine () ? ref (a_N9) : ref (a_N1);
      pivot[1] = ref (a_PSY);
      pivot[2] = ref (a_PSZ);
    }
  else if (mType->is_AminoAcid ())
    {
      pivot[0] = ref (a_CA);
      pivot[1] = ref (a_N);
      pivot[2] = ref (a_PSAZ);
    }
  else if (size () >= 3)
    {
      pivot[0] = &(mAtomRef[0]);
      pivot[1] = &(mAtomRef[1]);
      pivot[2] = &(mAtomRef[2]);
    }
  else
    return;

  // Fix res type
  // -- Si le type est déjà spécialisé, il n'y a aucun changement.
  if (ref (a_C1p))
    {
      if (ref (a_O2p))
	{
	  // It is a RNA
	  if (mType == r_A)
	    mType = r_rA;
	  else if (mType == r_C)
	    mType = r_rC;
	  else if (mType == r_G)
	    mType = r_rG;
	  else if (mType == r_U)
	    mType = r_rU;
	}
      else
	{
	  // It is a DNA
	  if (mType == r_A)
	    mType = r_dA;
	  else if (mType == r_C)
	    mType = r_dC;
	  else if (mType == r_G)
	    mType = r_dG;
	  else if (mType == r_T)
	    mType = r_dT;
	}
    }
  
  if (pivot[0] && pivot[1] && pivot[2])
    {
      // Move to global origin referential
      
      mTfo.Align (pivot[0], pivot[1], pivot[2]);
      CTransfo theAlign (mTfo);
      theAlign.Inverse ();

      for (it = mAtomRef.begin (); it != mAtomRef.end (); ++it)
	it->Transform (theAlign);
    }
  
  if (mType->is_NucleicAcid ())
    {
      addHydrogens ();
      addLP ();
    }
  isIdentity = mTfo.isIdentity ();
}  



void
CResidue::placeIt () const
{
  vector< CAtom >::const_iterator refit;
  vector< CAtom >::iterator resit;
  
  for (refit = mAtomRef.begin (), resit = mAtomRes.begin ();
       refit != mAtomRef.end ();
       ++refit, ++resit)
    {
      *resit = *refit;
      resit->Transform (mTfo);
    }
  isPlaced = true;
}



const CAtom*
CResidue::ref (t_Atom *t) const
{
  ResMap::const_iterator i = mAtomIndex.find (t);

  return i == mAtomIndex.end () ? 0 : &(mAtomRef[i->second]);
}



const CAtom*
CResidue::res (t_Atom *t) const
{
  ResMap::const_iterator i = mAtomIndex.find (t);

  if (i == mAtomIndex.end ())
    return 0;
  else if (isIdentity)
    return &(mAtomRef[i->second]);
  else
    return &place (i->second);
}



void
CResidue::insert (const CAtom &a)
{
  ResMap::iterator i = mAtomIndex.find (a.GetType ());
  
  if (i == mAtomIndex.end ())
    {
      mAtomIndex[a.GetType ()] = size ();
      mAtomRef.push_back (a);
      mAtomRes.push_back (CAtom ());
      mAtomRes.reserve (size ());
      i = mAtomIndex.find (a.GetType ());
    }
  else
    mAtomRef[i->second] = a;
  if (isPlaced)
    {
      mAtomRes[i->second] = mAtomRef[i->second];
      mAtomRes[i->second].Transform (mTfo);
    }
}



CResidue::iterator
CResidue::erase (t_Atom *type)
{
  ResMap::iterator i = mAtomIndex.find (type);

  if (i != mAtomIndex.end ())
    {
      vector< CAtom >::const_iterator cit;
      const t_Atom *next;
      size_type index;
      
      mAtomRef.erase (mAtomRef.begin () + i->second);
      next = ++i == mAtomIndex.end () ? 0 : i->first;
      mAtomIndex.clear ();
      for (cit = mAtomRef.begin (), index = 0;
	   cit != mAtomRef.end ();
	   ++cit, ++index)
	mAtomIndex[cit->GetType ()] = index;
      mAtomRes.pop_back ();
      mAtomRes.reserve (index);
      isPlaced = false;
      return find (next);
    }
  else
    return end ();
}



void
CResidue::AtomCopy (const AbstractResidue &right)
{
  const CResidue *resp = dynamic_cast< const CResidue* > (&right);
  
  if (this != &right && resp)
    {
      const CResidue &res = *resp;
      
      if (mType != res.mType)
	{
	  CIntLibException exc ("Invalid residue type ", __FILE__,
				__LINE__);
	  exc << (const char*)*res.mType << ".";
	  throw exc;
	}
      
      ResMap::iterator i;
      ResMap::const_iterator j;
      
      // Since the atom ordering must be the same for the two
      // residues, we can do this:
      for (i = mAtomIndex.begin (), j = res.mAtomIndex.begin ();
	   i != mAtomIndex.end () && j != res.mAtomIndex.end ();
	   ++i, ++j)
	{
	  mAtomRef[i->second] = res.mAtomRef[j->second];
	  mAtomRes[i->second] = res.mAtomRes[j->second];
	}
      isPlaced = res.isPlaced;
      isIdentity = res.isIdentity;
      mTfo = res.mTfo;
    }
}



AbstractResidue*
CResidue::select (t_Atom *at ...) const
{
  va_list ap;
  vector< CAtom > atom_vec;
  const CAtom *atom;
  AbstractResidue *res;
  
  atom = ref (at);
  if (atom)
    atom_vec.push_back (*atom);
  
  va_start (ap, at);
  while (true)
    {
      t_Atom* type = va_arg (ap, t_Atom*);
      if (type == 0)
	break;
      atom = ref (type);
      if (atom)
	atom_vec.push_back (*atom);
    }
  res = new CResidue (mType, atom_vec, resId);
  return res;
}



CResidue&
CResidue::Transform (const CTransfo& tfo)
{
  mTfo = tfo * mTfo;
  isPlaced = false;
  isIdentity = mTfo.isIdentity ();
  return *this;
}



void
CResidue::Align ()
{
  mTfo.SetIdentity ();
  isPlaced = false;
  isIdentity = true;
}



iBinstream&
CResidue::read (iBinstream& ibs)
{
  vector< CAtom >::size_type nb;

  mAtomRef.clear ();
  ibs >> resId >> mType >> nb;
  for (; nb > 0; --nb)
    {
      mAtomRef.push_back (CAtom ());
      CAtom &aref = mAtomRef.back ();
      ibs >> aref;
    }
  init ();
  return ibs;
}



oBinstream&
CResidue::write (oBinstream& obs) const
{
  vector< const_iterator > atoms;
  vector< const_iterator >::iterator ciit;
  const_iterator cit;
  
  obs << resId << mType;
  
  for (cit = begin (new atomset_and (new no_pse_lp_atom_set (),
				     new no_hydrogen_set ()));
       cit != end ();
       ++cit)
    atoms.push_back (cit);
  
  obs << atoms.size ();
  
  for (ciit = atoms.begin (); ciit != atoms.end (); ++ciit)
    obs << **ciit;
  return obs;
}



iPdbstream&
CResidue::read (iPdbstream &ips)
{
  vector< CAtom > vec;
  vector< CAtom >::iterator it;

  if (ips.GetAtom ())
    {
      // Place le atom dans le résidu.
      vec.push_back (*ips.GetAtom ());
      ips.DeleteAtom ();
  }
  
  //  Boucle jusqu'à ce qu'on trouve un résidu complet.
  while (! (ips.eof () || ips.eop ()))
    {
      CAtom atom;
      
      ips >> atom;
      if (atom.GetType () && ips.GetResType ())
	{
	  // Found an atom.

	  if (ips.GetPrevResType () == 0)
	    // This is the first residue found in the model.
	    ips.NewRes ();
	  else if (ips.GetResType () != ips.GetPrevResType ()
		   || ips.GetResId () != ips.GetPrevResId ())
	    {
	      // The residue is complete.
	      ips.KeepAtom (atom);
	      break;
	    }
	  
	  for (it = vec.begin (); it != vec.end (); ++it)
	    if (it->GetType () == atom.GetType ())
	      break;
	  
	  if (it != vec.end ())
	    {
	      // Peut-être le début d'un nouveau résidue???
	      if (atom.GetAltLocId () == ' ')
		{
		  if (! ips.GetPrevResType ()->is_Misc ())
		    {
		      // On rapporte l'"incident" seulement s'il s'agit d'un
		      // résidue "normal"!
		      gOut(2) << "Duplicate atoms "
			      << ips.GetPrevResId () << ":"
			      << *(it->GetType ())
			      << " in residue type "
			      << *ips.GetPrevResType () << "."
			      << endl;
		    }
		}
	      else
		atom.SetAltLocId ('_');  // On ignore l'atome
	    }
	  
	  // Place l'atom dans le résidu.
	  if (atom.GetAltLocId () != '_') 
	    vec.push_back (atom);
	}
      if (ips.eom ())
	break;
    }
  
  if (! vec.empty ())
    {
      no_pse_lp_atom_set filter;

      mAtomRef.clear ();
      for (it = vec.begin (); it != vec.end (); ++it)
	if (filter (*it))
	  mAtomRef.push_back (*it);
      resId = ips.GetPrevResId ();
      mType = ips.GetPrevResType ();
      init ();
      ips.NewRes ();
    }
  return ips;
}
  


oPdbstream&
CResidue::write (oPdbstream &ops) const
{
  const_iterator cit;

  ops.SetResType (mType);
  ops.SetResId (resId);
  
  for (cit = begin (); cit != end (); ++cit)
    ops << *cit;
  return ops;
}



ostream&
CResidue::write (ostream &os) const
{
  const_iterator cit;
  
  os << *mType << '(' << resId
     << ") type=" << *mType << ":" << endl;
  for (cit = begin (); cit != end (); ++cit)
    os << *cit << endl;
  return os;
}
