//                              -*- Mode: C++ -*- 
// CResidue.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Sep 13 14:08:02 2001
// Update Count     : 26
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
#include <string.h>
#include <stdarg.h>

#include "CResidue.h"

#include "AtomType.h"
#include "Binstream.h"
#include "CException.h"
#include "Messagestream.h"
#include "CPoint3D.h"
#include "McCore.h"
#include "Pdbstream.h"
#include "ResidueTypeImp.h"



int CResidue::count = 0;



CResidue::residue_iterator::residue_iterator ()
  : mRes (0),
    mPos (),
    mSet (new all_atom_set ())
{ }



CResidue::residue_iterator::residue_iterator (CResidue *nRes,
					      CResidue::ResMap::iterator nPos,
					      AtomSet *nSet)
  : mRes (nRes), mPos (nPos), mSet (nSet)
{
  CResidue::ResMap::iterator last = mRes->mAtomIndex.end ();

  if (mSet == 0)
    mSet = new all_atom_set ();
  while (mPos != last && ! (*mSet) (mRes->ref (mPos->second)))
    ++mPos;
}



CResidue::residue_iterator::residue_iterator (const CResidue::iterator &right)
  : mRes (right.mRes),
    mPos (right.mPos),
    mSet (right.mSet->clone ())
{ }



CResidue::iterator&
CResidue::residue_iterator::operator= (const CResidue::iterator &right)
{
  if (this != &right)
    {
      mRes = right.mRes;
      mPos = right.mPos;
      delete mSet;
      mSet = right.mSet->clone ();
    }
  return *this;
}



CResidue::iterator&
CResidue::residue_iterator::operator+= (difference_type k)
{
  CResidue::ResMap::iterator last = mRes->mAtomIndex.end ();

  while (k > 0 && mPos != last)
    if (++mPos != last && (*mSet) (mRes->ref (mPos->second)))
      --k;
  return *this;
}



CResidue::iterator&
CResidue::residue_iterator::operator++ ()
{
  CResidue::ResMap::iterator last = mRes->mAtomIndex.end ();

  while (mPos != last)
    if (++mPos == last || (*mSet) (mRes->ref (mPos->second)))
      break;
  return *this;
}



CResidue::iterator
CResidue::residue_iterator::operator++ (int ign)
{
  residue_iterator ret = *this;
  CResidue::ResMap::iterator last = mRes->mAtomIndex.end ();

  while (mPos != last)
    if (++mPos == last || (*mSet) (mRes->ref (mPos->second)))
      break;
  return ret;
}



//  CResidue::iterator::difference_type
//  CResidue::residue_iterator::operator- (const CResidue::iterator &i) const
//  {
//    return difference_type (mPos - i.mPos);
//  }



CResidue::const_residue_iterator::const_residue_iterator ()
  : mRes (0),
    mPos (),
    mSet (new all_atom_set ())
{ }



CResidue::const_residue_iterator::const_residue_iterator (const CResidue *nRes,
							  CResidue::ResMap::const_iterator nPos,
							  AtomSet *nSet)
  : mRes (nRes), mPos (nPos), mSet (nSet)
{
  CResidue::ResMap::const_iterator last = mRes->mAtomIndex.end ();

  if (mSet == 0)
    mSet = new all_atom_set ();
  while (mPos != last && ! (*mSet) (mRes->ref (mPos->second)))
    ++mPos;
}



CResidue::const_residue_iterator::const_residue_iterator (const CResidue::const_iterator &right)
  : mRes (right.mRes),
    mPos (right.mPos),
    mSet (right.mSet->clone ())
{ }



CResidue::const_iterator&
CResidue::const_residue_iterator::operator= (const CResidue::const_iterator &right)
{
  if (this != &right)
    {
      mRes = right.mRes;
      mPos = right.mPos;
      delete mSet;
      mSet = right.mSet->clone ();
    }
  return *this;
}



CResidue::const_iterator&
CResidue::const_residue_iterator::operator+= (difference_type k)
{
  CResidue::ResMap::const_iterator last = mRes->mAtomIndex.end ();

  while (k > 0 && mPos != last)
    if (++mPos != last && (*mSet) (mRes->ref (mPos->second)))
      --k;
  return *this;
}



CResidue::const_iterator&
CResidue::const_residue_iterator::operator++ ()
{
  CResidue::ResMap::const_iterator last = mRes->mAtomIndex.end ();

  while (mPos != last)
    if (++mPos == last || (*mSet) (mRes->ref (mPos->second)))
      break;
  return *this;
}



CResidue::const_iterator
CResidue::const_residue_iterator::operator++ (int ign)
{
  const_residue_iterator ret = *this;
  CResidue::ResMap::const_iterator last = mRes->mAtomIndex.end ();
  
  while (mPos != last)
    if (++mPos == last || (*mSet) (mRes->ref (mPos->second)))
      break;
  return ret;
}



//  CResidue::const_iterator::difference_type
//  CResidue::const_residue_iterator::operator- (const CResidue::const_iterator &i) const
//  {
//    return difference_type (mPos - i.mPos);
//  }



CResidue::CResidue (t_Residue *type,
		    const vector< CAtom > &vec,
		    const CResId &nId)
  : CResId (nId),
    mType (type),
    mResName (0),
    isPlaced (false),
    isIdentity (true),
    mTfo ()
{
  count++;
  const CAtom *pivot[3] = {0, 0, 0};
  vector< CAtom >::const_iterator cit;
  size_type i;
  
  for (cit = vec.begin (), i = 0; cit != vec.end (); ++cit)
    {
      t_Atom *type = cit->GetType ();
      ResMap::iterator pos = mAtomIndex.find (type);
      
      if (pos != mAtomIndex.end ())
	gOut(2) << "CResidue: Duplicated atom [" << *type
		<< "] in residue " << nId << "." << endl;
      else
	{
	  mAtomIndex[type] = i++;
	  mAtomRef.push_back (*cit);
	}
    }

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
	  gOut(1) << "Residue " << *type << "-" << nId
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
	  gOut(1) << "Residue " << *type << "-" << nId
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
      
      vector< CAtom >::iterator it;

      for (it = mAtomRef.begin (); it != mAtomRef.end (); ++it)
	it->Transform (theAlign);
    }
  
  if (mType->is_NucleicAcid ())
    {
      addHydrogens ();
      addLP ();
    }

  isIdentity = mTfo.isIdentity ();

  mAtomRes.reserve (size ());
  mAtomRes.resize (size ());
}



CResidue::CResidue (const CResidue& right)
  : CResId (right),
    mType (right.mType),
    mResName (0),
    mAtomRef (right.mAtomRef),
    mAtomIndex (right.mAtomIndex),
    mAtomRes (right.mAtomRes),
    isPlaced (right.isPlaced),
    isIdentity (right.isIdentity),
    mTfo (right.mTfo)    
{
  count++;
  if (right.mResName)
    mResName = strdup (right.mResName);
}



CResidue::~CResidue ()
{
  count--;
  if (mResName)
    delete[] mResName; 
}



CResidue&
CResidue::operator= (const CResidue &right)
{
  if (&right != this)
    {
      CResId::operator= (right);
      mType = right.mType;
      if (mResName)
	{
	  delete[] mResName;
	  mResName = 0;
	}
      if (right.mResName)
	mResName = strdup (right.mResName);
      mAtomRef = right.mAtomRef;
      mAtomIndex = right.mAtomIndex;
      mAtomRes = right.mAtomRes;
      isPlaced = right.isPlaced;
      isIdentity = right.isIdentity;
      mTfo = right.mTfo;
    }
  return *this;
}



CResidue&
CResidue::operator= (const CTransfo &tfo)
{
  mTfo = tfo; 
  isPlaced = false;
  isIdentity = mTfo.isIdentity ();
  return *this;
}



bool
CResidue::operator== (const CResidue &right) const
{
  return CResId::operator== (right) && mType == right.mType;
}



CAtom&
CResidue::operator[] (const t_Atom *type)
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

  return res (cit->second);
}



CResidue::iterator
CResidue::find (const t_Atom *k)
{
  return iterator (this, mAtomIndex.find (k));
}



CResidue::const_iterator
CResidue::find (const t_Atom *k) const
{
  return const_iterator (this, mAtomIndex.find (k));
}



const char*
CResidue::GetResName () const
{
  return mResName == 0 ? *mType : mResName;
}



void
CResidue::SetResName (const char* nName)
{
  if (mResName)
    {
      delete[] mResName;
      mResName = 0;
    }
  if (nName)
    mResName = strdup (nName);
}



CAtom&
CResidue::placeIt (CResidue::size_type pos) const
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
  return mAtomRes[pos];
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
      mAtomRes.reserve (size ());
      mAtomRes.push_back (CAtom ());
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



void
CResidue::erase (t_Atom *type)
{
  ResMap::iterator i = mAtomIndex.find (type);

  if (i != mAtomIndex.end ())
    {
      vector< CAtom >::const_iterator cit;
      size_type index;
      
      mAtomRef.erase (mAtomRef.begin () + i->second);
      mAtomIndex.clear ();
      for (cit = mAtomRef.begin (), index = 0;
	   cit != mAtomRef.end ();
	   ++cit, ++index)
	mAtomIndex[cit->GetType ()] = index;
      mAtomRes.pop_back ();
      mAtomRes.reserve (index);
      isPlaced = false;
    }
}



void
CResidue::addHydrogens ()
{
  // Add Hydrogens
  float C_H_dist = 1.08;
  float N_H_dist = 1.00;
  float tan60 = 1.7320508;
  CPoint3D x, y, z, up, a, b;

  if (mType->is_A ())
    {
      if (!(ref (a_C2) && ref (a_N1) && ref (a_N3) && ref (a_C8)
	    && ref (a_N7) && ref (a_N9) && ref (a_C6) && ref (a_C5)
	    && ref (a_N6) && ref (a_C4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms." 
		  << endl;
	  // Invalid residue
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
      
      // H2
      x = (*ref (a_C2) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C2) - *ref (a_N3)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H2 = *ref (a_C2) + z * C_H_dist;
    
      // H8
      x = (*ref (a_C8) - *ref (a_N7)).Normalize ();
      y = (*ref (a_C8) - *ref (a_N9)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H8 = *ref (a_C8) + z * C_H_dist;
      
      // 1H6 and 2H6
      x = (*ref (a_C6) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C6) - *ref (a_C5)).Normalize ();
      z = (*ref (a_N6) - *ref (a_C6)).Normalize ();  // axe N6-C6
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H61 = *ref (a_N6) + a * N_H_dist;
      CPoint3D H62 = *ref (a_N6) + b * N_H_dist;
      
      insert (CAtom (H2.GetX (), H2.GetY (), H2.GetZ (), a_H2));
      insert (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      insert (CAtom (H61.GetX (), H61.GetY (), H61.GetZ (), a_1H6));
      insert (CAtom (H62.GetX (), H62.GetY (), H62.GetZ (), a_2H6));
    } 
  else if (mType->is_G ())
    { 
      if (!(ref (a_N1) && ref (a_C2) && ref (a_C6) && ref (a_C8)
	    && ref (a_N7) && ref (a_N9) && ref (a_N3) && ref (a_N2)
	    && ref (a_C4) && ref (a_C5) && ref (a_O6)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms." 
		  << endl;
	  // invalid residue
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}

      // H1
      x = (*ref (a_N1) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N1) - *ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H1 = *ref (a_N1) + z * N_H_dist;
      
      // H8
      x = (*ref (a_C8) - *ref (a_N7)).Normalize ();
      y = (*ref (a_C8) - *ref (a_N9)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H8 = *ref (a_C8) + z * C_H_dist;
      
      // 1H2 and 2H2
      x = (*ref (a_C2) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C2) - *ref (a_N3)).Normalize ();
      z = (*ref (a_N2) - *ref (a_C2)).Normalize ();  // axe N2-C2
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H21 = *ref (a_N2) + b * N_H_dist;
      CPoint3D H22 = *ref (a_N2) + a * N_H_dist;
      
      insert (CAtom (H1.GetX (), H1.GetY (), H1.GetZ (), a_H1));
      insert (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      insert (CAtom (H21.GetX (), H21.GetY (), H21.GetZ (), a_1H2));
      insert (CAtom (H22.GetX (), H22.GetY (), H22.GetZ (), a_2H2));
    }
  else if (mType->is_C ())
    {
      if (!(ref (a_C5) && ref (a_C4) && ref (a_C6) && ref (a_N1)
	    && ref (a_N3) && ref (a_N4) && ref (a_C6) && ref (a_C5)
	    && ref (a_C2) && ref (a_O2)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms." 
		  << endl;
	  // invalid residue
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
      
      // H5
      x = (*ref (a_C5) - *ref (a_C4)).Normalize ();
      y = (*ref (a_C5) - *ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H5 = *ref (a_C5) + z * C_H_dist;
      
      // H6
      x = (*ref (a_C6) - *ref (a_C5)).Normalize ();
      y = (*ref (a_C6) - *ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *ref (a_C6) + z * C_H_dist;
      
      // 1H4 and 2H4
      x = (*ref (a_C4) - *ref (a_N3)).Normalize ();
      y = (*ref (a_C4) - *ref (a_C5)).Normalize ();
      z = (*ref (a_N4) - *ref (a_C4)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H41 = *ref (a_N4) + b * N_H_dist;
      CPoint3D H42 = *ref (a_N4) + a * N_H_dist;
      
      insert (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      insert (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
      insert (CAtom (H41.GetX (), H41.GetY (), H41.GetZ (), a_1H4));
      insert (CAtom (H42.GetX (), H42.GetY (), H42.GetZ (), a_2H4));
    } 
  else if (mType->is_U ())
    {
      if (!(ref (a_N3) && ref (a_C2) && ref (a_C4) && ref (a_C5)
	    && ref (a_C6) && ref (a_N1) && ref (a_O2) && ref (a_O4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms." 
		  << endl;
	  // invalid residue
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
      
      // H3
      x = (*ref (a_N3) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N3) - *ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H3 = *ref (a_N3) + z * N_H_dist;
      
      // H5
      x = (*ref (a_C5) - *ref (a_C4)).Normalize ();
      y = (*ref (a_C5) - *ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H5 = *ref (a_C5) + z * C_H_dist;
      
      // H6
      x = (*ref (a_C6) - *ref (a_C5)).Normalize ();
      y = (*ref (a_C6) - *ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *ref (a_C6) + z * C_H_dist;
      
      insert (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      insert (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      insert (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
    }
  else if (mType->is_T ())
    {
      if (!(ref (a_N3) && ref (a_C2) && ref (a_C4) && ref (a_C5)
	    && ref (a_C6) && ref (a_N1) && ref (a_O2) && ref (a_O4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms." 
		  << endl;
	  // invalid residue
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  return;
	}
      
      // H3
      x = (*ref (a_N3) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N3) - *ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H3 = *ref (a_N3) + z * N_H_dist;
      
      // H6
      x = (*ref (a_C6) - *ref (a_C5)).Normalize ();
      y = (*ref (a_C6) - *ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *ref (a_C6) + z * C_H_dist;
      
      insert (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      insert (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
    }
  
  if (mType->is_NucleicAcid ())
    {
      const CPoint3D *r1, *r2, *r3, *r4;
      
      //  H1p
      r1 = ref (a_C1p);
      r2 = ref (a_C2p);
      r3 = (mType->is_Purine ()) ? ref (a_N9) : ref (a_N1);
      r4 = ref (a_O4p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H1p = *r1 + (x + y + z).Normalize () * 1.09;
	  insert (CAtom (H1p.GetX (), H1p.GetY (), H1p.GetZ (), a_H1p));
	}
      
      //  H3p
      r1 = ref (a_C3p);
      r2 = ref (a_C2p);
      r3 = ref (a_O3p);
      r4 = ref (a_C4p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H3p = *r1 + (x + y + z).Normalize () * 1.09;
	  insert (CAtom (H3p.GetX (), H3p.GetY (), H3p.GetZ (), a_H3p));
	}
      
      //  H4p
      r1 = ref (a_C4p);
      r2 = ref (a_C3p);
      r3 = ref (a_O4p);
      r4 = ref (a_C5p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H4p = *r1 + (x + y + z).Normalize () * 1.09;
	  insert (CAtom (H4p.GetX (), H4p.GetY (), H4p.GetZ (), a_H4p));
	}
      
      
      //  1H5p  2H5p
      r1 = ref (a_C5p);
      r2 = ref (a_C4p);
      r3 = ref (a_O5p);
      if (r1 && r2 && r3)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (x + y).Normalize ();
	  up = x.Cross (y).Normalize ();
	  
	  CPoint3D H51p = *r1 + (up * 1.386 + z).Normalize () * 1.09;
	  CPoint3D H52p = *r1 + (-up * 1.386 + z).Normalize () * 1.09;
	  insert (CAtom (H51p.GetX (), H51p.GetY (), H51p.GetZ (), a_1H5p));
	  insert (CAtom (H52p.GetX (), H52p.GetY (), H52p.GetZ (), a_2H5p));
	}
      
      //  HO3p  // optionel
      
      if (mType->is_RNA ())
	{
	  //  H2p
	  r1 = ref (a_C2p);
	  r2 = ref (a_C1p);
	  r3 = ref (a_C3p);
	  r4 = ref (a_O2p);
	  if (r1 && r2 && r3 && r4)
	    {
	      x = (*r1 - *r2).Normalize ();
	      y = (*r1 - *r3).Normalize ();
	      z = (*r1 - *r4).Normalize ();
	      
	      CPoint3D H2p = *r1 + (x + y + z).Normalize () * 1.09;
	      insert (CAtom (H2p.GetX (), H2p.GetY (), H2p.GetZ (), a_H2p));
	    }
	  
	  // HO2p
	  r1 = ref (a_O2p);
	  r2 = ref (a_C2p);
	  r3 = ref (a_C1p);
	  if (r1 && r2 && r3 && !ref (a_HO2p))
	    {
	      x = (*r2 - *r3).Normalize ();
	      y = (*r1 - *r2).Normalize ();
	      z = x.Cross (y).Cross (y).Normalize ();
	      
	      CPoint3D HO2p = *r1 + (y * 0.354 - z).Normalize () * 1.03;
	      insert (CAtom (HO2p.GetX (), HO2p.GetY (), HO2p.GetZ (), a_HO2p));
	    }
	  
	  
	}
      else if (mType->is_DNA ())
	{
	  // 1H2p 2H2p
	  r1 = ref (a_C2p);
	  r2 = ref (a_C1p);
	  r3 = ref (a_C3p);
	  if (r1 && r2 && r3)
	    {
	      x = (*r1 - *r2).Normalize ();
	      y = (*r1 - *r3).Normalize ();
	      z = (x + y).Normalize ();
	      up = x.Cross (y).Normalize ();
	      
	      CPoint3D H21p = *r1 + (up * 1.386 + z).Normalize () * 1.09;
	      CPoint3D H22p = *r1 + (-up * 1.386 + z).Normalize () * 1.09;
	      insert (CAtom (H21p.GetX (), H21p.GetY (), H21p.GetZ (), a_1H2p));
	      insert (CAtom (H22p.GetX (), H22p.GetY (), H22p.GetZ (), a_2H2p));
	    }
	}
    }
}



void
CResidue::addLP ()
{
  CPoint3D x, y, z, up, a, b;
  float tan60 = 1.7320508;
  float O_LP_dist = 1.00;
  float N_LP_dist = 1.00;

  if (!mType)
    return;

  // Add LP
  if (mType->is_A ())
    {
      // LP1
      x = (*ref (a_N1) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N1) - *ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP1 = *ref (a_N1) + z * N_LP_dist;
      
      // LP3
      x = (*ref (a_N3) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N3) - *ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *ref (a_N3) + z * N_LP_dist;
      
      // LP7
      x = (*ref (a_N7) - *ref (a_C5)).Normalize ();
      y = (*ref (a_N7) - *ref (a_C8)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP7 = *ref (a_N7) + z * N_LP_dist;
      
      insert (CAtom (LP1.GetX (), LP1.GetY (), LP1.GetZ (), a_LP1));
      insert (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
    }
  else if (mType->is_G ())
    {
      // LP3
      x = (*ref (a_N3) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N3) - *ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *ref (a_N3) + z * N_LP_dist;
      
      // LP7
      x = (*ref (a_N7) - *ref (a_C5)).Normalize ();
      y = (*ref (a_N7) - *ref (a_C8)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP7 = *ref (a_N7) + z * N_LP_dist;
      
      // 1LP6 and 2LP6
      x = (*ref (a_C6) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C6) - *ref (a_C5)).Normalize ();
      z = (*ref (a_O6) - *ref (a_C6)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP61 = *ref (a_O6) + b * O_LP_dist;
      CPoint3D LP62 = *ref (a_O6) + a * O_LP_dist;
      
      insert (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
      insert (CAtom (LP61.GetX (), LP61.GetY (), LP61.GetZ (), a_1LP6));
      insert (CAtom (LP62.GetX (), LP62.GetY (), LP62.GetZ (), a_2LP6));
    }
  else if (mType->is_C ())
    {
      // LP3
      x = (*ref (a_N3) - *ref (a_C2)).Normalize ();
      y = (*ref (a_N3) - *ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *ref (a_N3) + z * N_LP_dist;
      
      // 1LP2 and 2LP2
      x = (*ref (a_C2) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C2) - *ref (a_N3)).Normalize ();
      z = (*ref (a_O2) - *ref (a_C2)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP21 = *ref (a_O2) + a * O_LP_dist;
      CPoint3D LP22 = *ref (a_O2) + b * O_LP_dist;
      
      insert (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      insert (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
    }
  else if (mType->is_U () || mType->is_T ())
    {
      // 1LP2 and 2LP2
      x = (*ref (a_C2) - *ref (a_N1)).Normalize ();
      y = (*ref (a_C2) - *ref (a_N3)).Normalize ();
      z = (*ref (a_O2) - *ref (a_C2)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP21 = *ref (a_O2) + a * O_LP_dist;
      CPoint3D LP22 = *ref (a_O2) + b * O_LP_dist;
      
      // 1LP2 and 2LP2
      x = (*ref (a_C4) - *ref (a_N3)).Normalize ();
      y = (*ref (a_C4) - *ref (a_C5)).Normalize ();
      z = (*ref (a_O4) - *ref (a_C4)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP41 = *ref (a_O4) + b * O_LP_dist;
      CPoint3D LP42 = *ref (a_O4) + a * O_LP_dist;
      
      insert (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      insert (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
      insert (CAtom (LP41.GetX (), LP41.GetY (), LP41.GetZ (), a_1LP4));
      insert (CAtom (LP42.GetX (), LP42.GetY (), LP42.GetZ (), a_2LP4));
    }
}



void
CResidue::AtomCopy (const CResidue &right)
{
  if (this != &right)
    {
      if (mType != right.mType)
	{
	  CIntLibException exc ("Invalid residue type ", __FILE__,
				__LINE__);
	  exc << (const char*)*right.mType << ".";
	  throw exc;
	}

      ResMap::iterator i;
      ResMap::const_iterator j;

      // Since the atom ordering must be the same for the two
      // residues, we can do this:
      for (i=mAtomIndex.begin (), j=right.mAtomIndex.begin ();
	   i!=mAtomIndex.end () && j!=right.mAtomIndex.end (); ++i, ++j) {
	mAtomRef[i->second] = right.mAtomRef[j->second];
	mAtomRes[i->second] = right.mAtomRes[j->second];
      }
      isPlaced = right.isPlaced;
      isIdentity = right.isIdentity;
      mTfo = right.mTfo;
    }
}



CResidue
CResidue::Validate () const
{
  vector< CAtom >::const_iterator at_it;
  vector< CAtom > atoms;

  for (at_it = mAtomRef.begin (); at_it != mAtomRef.end (); ++at_it)
    if (::find (atoms.begin (), atoms.end (), *at_it) == atoms.end ())
      atoms.push_back (*at_it);

  CResidue res (mType, atoms, *this);
  res = mTfo;
  
  if (res.mType != 0)
    {
      set< t_Atom* >::const_iterator optbegin, optend;
      set< t_Atom* > resset, diffset, allset;
      vector< CAtom >::iterator it;

      if (res.mType->is_DNA ())
	{
	  if (res.mType->is_dA ())
	    {
	      allset.insert (gdAOblAtomSet.begin (),  gdAOblAtomSet.end ());
	      optbegin = gdAOptAtomSet.begin ();
	      optend = gdAOptAtomSet.end ();
	    }
	  else if (res.mType->is_dC ())
	    {
	      allset.insert (gdCOblAtomSet.begin (), gdCOblAtomSet.end ());
	      optbegin = gdCOptAtomSet.begin ();
	      optend = gdCOptAtomSet.end ();
	    }
	  else if (res.mType->is_dG ())
	    {
	      allset.insert (gdGOblAtomSet.begin (), gdGOblAtomSet.end ());
	      optbegin = gdGOptAtomSet.begin ();
	      optend = gdGOptAtomSet.end ();
	    }
	  else if (res.mType->is_dT ())
	    {
	      allset.insert (gdTOblAtomSet.begin (), gdTOblAtomSet.end ());
	      optbegin = gdTOptAtomSet.begin ();
	      optend = gdTOptAtomSet.end ();
	    }
	}
      else if (res.mType->is_RNA ())
	{
	  if (res.mType->is_rA ())
	    {
	      allset.insert (grAOblAtomSet.begin (), grAOblAtomSet.end ());
	      optbegin = grAOptAtomSet.begin ();
	      optend = grAOptAtomSet.end ();
	    }
	  else if (res.mType->is_rC ())
	    {
	      allset.insert (grCOblAtomSet.begin (), grCOblAtomSet.end ());
	      optbegin = grCOptAtomSet.begin ();
	      optend = grCOptAtomSet.end ();
	    }
	  else if (res.mType->is_rG ())
	    {
	      allset.insert (grGOblAtomSet.begin (), grGOblAtomSet.end ());
	      optbegin = grGOptAtomSet.begin ();
	      optend = grGOptAtomSet.end ();
	    }
	  else if (res.mType->is_rU ())
	    {
	      allset.insert (grUOblAtomSet.begin (), grUOblAtomSet.end ());
	      optbegin = grUOptAtomSet.begin ();
	      optend = grUOptAtomSet.end ();
	    }
	}
      else if (res.mType->is_AminoAcid ())
	{
	  if (res.mType->is_ALA ())
	    {
	      allset.insert (gALAOblAtomSet.begin (), gALAOblAtomSet.end ());
	      optbegin = gALAOptAtomSet.begin ();
	      optend = gALAOptAtomSet.end ();
	    }
	  else if (res.mType->is_ARG ())
	    {
	      allset.insert (gARGOblAtomSet.begin (), gARGOblAtomSet.end ());
	      optbegin = gARGOptAtomSet.begin ();
	      optend = gARGOptAtomSet.end ();
	    }
	  else if (res.mType->is_ASN ())
	    {
	      allset.insert (gASNOblAtomSet.begin (), gASNOblAtomSet.end ());
	      optbegin = gASNOptAtomSet.begin ();
	      optend = gASNOptAtomSet.end ();
	    }
	  else if (res.mType->is_ASP ())
	    {
	      allset.insert (gASPOblAtomSet.begin (), gASPOblAtomSet.end ());
	      optbegin = gASPOptAtomSet.begin ();
	      optend = gASPOptAtomSet.end ();
	    }
	  else if (res.mType->is_CYS ())
	    {
	      allset.insert (gCYSOblAtomSet.begin (), gCYSOblAtomSet.end ());
	      optbegin = gCYSOptAtomSet.begin ();
	      optend = gCYSOptAtomSet.end ();
	    }
	  else if (res.mType->is_GLN ())
	    {
	      allset.insert (gGLNOblAtomSet.begin (), gGLNOblAtomSet.end ());
	      optbegin = gGLNOptAtomSet.begin ();
	      optend = gGLNOptAtomSet.end ();
	    }
	  else if (res.mType->is_GLU ())
	    {
	      allset.insert (gGLUOblAtomSet.begin (), gGLUOblAtomSet.end ());
	      optbegin = gGLUOptAtomSet.begin ();
	      optend = gGLUOptAtomSet.end ();
	    }
	  else if (res.mType->is_GLY ())
	    {
	      allset.insert (gGLYOblAtomSet.begin (), gGLYOblAtomSet.end ());
	      optbegin = gGLYOptAtomSet.begin ();
	      optend = gGLYOptAtomSet.end ();
	    }
	  else if (res.mType->is_HIS ())
	    {
	      allset.insert (gHISOblAtomSet.begin (), gHISOblAtomSet.end ());
	      optbegin = gHISOptAtomSet.begin ();
	      optend = gHISOptAtomSet.end ();
	    }
	  else if (res.mType->is_ILE ())
	    {
	      allset.insert (gILEOblAtomSet.begin (), gILEOblAtomSet.end ());
	      optbegin = gILEOptAtomSet.begin ();
	      optend = gILEOptAtomSet.end ();
	    }
	  else if (res.mType->is_LEU ())
	    {
	      allset.insert (gLEUOblAtomSet.begin (), gLEUOblAtomSet.end ());
	      optbegin = gLEUOptAtomSet.begin ();
	      optend = gLEUOptAtomSet.end ();
	    }
	  else if (res.mType->is_LYS ())
	    {
	      allset.insert (gLYSOblAtomSet.begin (), gLYSOblAtomSet.end ());
	      optbegin = gLYSOptAtomSet.begin ();
	      optend = gLYSOptAtomSet.end ();
	    }
	  else if (res.mType->is_MET ())
	    {
	      allset.insert (gMETOblAtomSet.begin (), gMETOblAtomSet.end ());
	      optbegin = gMETOptAtomSet.begin ();
	      optend = gMETOptAtomSet.end ();
	    }
	  else if (res.mType->is_PHE ())
	    {
	      allset.insert (gPHEOblAtomSet.begin (), gPHEOblAtomSet.end ());
	      optbegin = gPHEOptAtomSet.begin ();
	      optend = gPHEOptAtomSet.end ();
	    }
	  else if (res.mType->is_PRO ())
	    {
	      allset.insert (gPROOblAtomSet.begin (), gPROOblAtomSet.end ());
	      optbegin = gPROOptAtomSet.begin ();
	      optend = gPROOptAtomSet.end ();
	    }
	  else if (res.mType->is_SER ())
	    {
	      allset.insert (gSEROblAtomSet.begin (), gSEROblAtomSet.end ());
	      optbegin = gSEROptAtomSet.begin ();
	      optend = gSEROptAtomSet.end ();
	    }
	  else if (res.mType->is_THR ())
	    {
	      allset.insert (gTHROblAtomSet.begin (), gTHROblAtomSet.end ());
	      optbegin = gTHROptAtomSet.begin ();
	      optend = gTHROptAtomSet.end ();
	    }
	  else if (res.mType->is_TRP ())
	    {
	      allset.insert (gTRPOblAtomSet.begin (), gTRPOblAtomSet.end ());
	      optbegin = gTRPOptAtomSet.begin ();
	      optend = gTRPOptAtomSet.end ();
	    }
	  else if (res.mType->is_TYR ())
	    {
	      allset.insert (gTYROblAtomSet.begin (), gTYROblAtomSet.end ());
	      optbegin = gTYROptAtomSet.begin ();
	      optend = gTYROptAtomSet.end ();
	    }
	  else if (res.mType->is_VAL ())
	    {
	      allset.insert (gVALOblAtomSet.begin (), gVALOblAtomSet.end ());
	      optbegin = gVALOptAtomSet.begin ();
	      optend = gVALOptAtomSet.end ();
	    }
	}
      else
	{
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*res.mType);
	  
	  if (i == gMiscResidueString.end ())
	    res.mType = new rt_Misc ((const char*)*res.mType);
	  else
	    res.mType = i->second;
	  return res;
	}

      
      for (it = res.mAtomRef.begin (); it != res.mAtomRef.end (); ++it)
	resset.insert ((*it).GetType ());
      
      set_difference (allset.begin (), allset.end (),
		      resset.begin (), resset.end (),
		      inserter (diffset, diffset.begin ()));
      if (! diffset.empty ())
	{
	  gOut (3) << 'i';
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*res.mType);
	  
	  if (i == gMiscResidueString.end ())
	    res.mType = new rt_Misc ((const char*)*res.mType);
	  else
	    res.mType = i->second;
	  return res;
	}

      allset.insert (optbegin, optend);
      set_difference (resset.begin (), resset.end (),
		      allset.begin (), allset.end (),
		      inserter (diffset, diffset.begin ()));
      res.erase (diffset.begin (), diffset.end ());

      if (res.mType->is_AminoAcid ())
	gOut (3) << 'p';
      else
	gOut (3) << '.';
      return res;
    }
  gOut (3) << 'i';
  return res;
}



CResidue
CResidue::RemoveOptionals () const
{
  if (mType != 0)
    {
      set< t_Atom* >::const_iterator setbegin, setend;
      vector< CAtom > atom_vec;
      
      if (mType->is_DNA ())
	{
	  if (mType->is_dA ())
	    {
	      setbegin = gdAOptAtomSet.begin ();
	      setend = gdAOptAtomSet.end ();
	    }
	  else if (mType->is_dC ())
	    {
	      setbegin = gdCOptAtomSet.begin ();
	      setend = gdCOptAtomSet.end ();
	    }
	  else if (mType->is_dG ())
	    {
	      setbegin = gdGOptAtomSet.begin ();
	      setend = gdGOptAtomSet.end ();
	    }
	  else if (mType->is_dT ())
	    {
	      setbegin = gdTOptAtomSet.begin ();
	      setend = gdTOptAtomSet.end ();
	    }
	}
      else if (mType->is_RNA ())
	{
	  if (mType->is_rA ())
	    {
	      setbegin = grAOptAtomSet.begin ();
	      setend = grAOptAtomSet.end ();
	    }
	  else if (mType->is_rC ())
	    {
	      setbegin = grCOptAtomSet.begin ();
	      setend = grCOptAtomSet.end ();
	    }
	  else if (mType->is_rG ())
	    {
	      setbegin = grGOptAtomSet.begin ();
	      setend = grGOptAtomSet.end ();
	    }
	  else if (mType->is_rU ())
	    {
	      setbegin = grUOptAtomSet.begin ();
	      setend = grUOptAtomSet.end ();
	    }
	}
      else if (mType->is_AminoAcid ())
	{
	  if (mType->is_ALA ())
	    {
	      setbegin = gALAOptAtomSet.begin ();
	      setend = gALAOptAtomSet.end ();
	    }
	  else if (mType->is_ARG ())
	    {
	      setbegin = gARGOptAtomSet.begin ();
	      setend = gARGOptAtomSet.end ();
	    }
	  else if (mType->is_ASN ())
	    {
	      setbegin = gASNOptAtomSet.begin ();
	      setend = gASNOptAtomSet.end ();
	    }
	  else if (mType->is_ASP ())
	    {
	      setbegin = gASPOptAtomSet.begin ();
	      setend = gASPOptAtomSet.end ();
	    }
	  else if (mType->is_CYS ())
	    {
	      setbegin = gCYSOptAtomSet.begin ();
	      setend = gCYSOptAtomSet.end ();
	    }
	  else if (mType->is_GLN ())
	    {
	      setbegin = gGLNOptAtomSet.begin ();
	      setend = gGLNOptAtomSet.end ();
	    }
	  else if (mType->is_GLU ())
	    {
	      setbegin = gGLUOptAtomSet.begin ();
	      setend = gGLUOptAtomSet.end ();
	    }
	  else if (mType->is_GLY ())
	    {
	      setbegin = gGLYOptAtomSet.begin ();
	      setend = gGLYOptAtomSet.end ();
	    }
	  else if (mType->is_HIS ())
	    {
	      setbegin = gHISOptAtomSet.begin ();
	      setend = gHISOptAtomSet.end ();
	    }
	  else if (mType->is_ILE ())
	    {
	      setbegin = gILEOptAtomSet.begin ();
	      setend = gILEOptAtomSet.end ();
	    }
	  else if (mType->is_LEU ())
	    {
	      setbegin = gLEUOptAtomSet.begin ();
	      setend = gLEUOptAtomSet.end ();
	    }
	  else if (mType->is_LYS ())
	    {
	      setbegin = gLYSOptAtomSet.begin ();
	      setend = gLYSOptAtomSet.end ();
	    }
	  else if (mType->is_MET ())
	    {
	      setbegin = gMETOptAtomSet.begin ();
	      setend = gMETOptAtomSet.end ();
	    }
	  else if (mType->is_PHE ())
	    {
	      setbegin = gPHEOptAtomSet.begin ();
	      setend = gPHEOptAtomSet.end ();
	    }
	  else if (mType->is_PRO ())
	    {
	      setbegin = gPROOptAtomSet.begin ();
	      setend = gPROOptAtomSet.end ();
	    }
	  else if (mType->is_SER ())
	    {
	      setbegin = gSEROptAtomSet.begin ();
	      setend = gSEROptAtomSet.end ();
	    }
	  else if (mType->is_THR ())
	    {
	      setbegin = gTHROptAtomSet.begin ();
	      setend = gTHROptAtomSet.end ();
	    }
	  else if (mType->is_TRP ())
	    {
	      setbegin = gTRPOptAtomSet.begin ();
	      setend = gTRPOptAtomSet.end ();
	    }
	  else if (mType->is_TYR ())
	    {
	      setbegin = gTYROptAtomSet.begin ();
	      setend = gTYROptAtomSet.end ();
	    }
	  else if (mType->is_VAL ())
	    {
	      setbegin = gVALOptAtomSet.begin ();
	      setend = gVALOptAtomSet.end ();
	    }
	}
      else
	return *this;

      CResidue res (*this);
      
      res.erase (setbegin, setend);
      return res;
    }
  else
    return *this;
}



CResidue
CResidue::select (t_Atom *at ...) const
{
  va_list ap;
  vector< CAtom > atom_vec;
  const CAtom *atom;

  atom = ref (at);
  if (atom)
    atom_vec.push_back (*atom);
  
  va_start (ap, at);
  for (;;)
    {
      t_Atom* type = va_arg (ap, t_Atom*);
      if (type == 0)
	break;
      atom = ref (type);
      if (atom)
	atom_vec.push_back (*atom);
    }
  return CResidue (mType, atom_vec, *(CResId*)this);
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
operator>> (iBinstream& ibs, CResidue& res)
{
  CResId resid;
  t_Residue *type;
  vector< CAtom >::size_type nb;
  vector< CAtom > vec;

  ibs >> resid >> type >> nb;
  for (; nb > 0; --nb)
    {
      vec.push_back (CAtom ());
      CAtom &aref = vec.back ();
      ibs >> aref;
    }
  res = CResidue (type, vec, resid);
  return ibs;
}



oBinstream&
operator<< (oBinstream& obs, const CResidue& res)
{
  vector< CResidue::const_iterator > atoms;
  vector< CResidue::const_iterator >::iterator ciit;
  CResidue::const_iterator cit;
  
  obs << (const CResId&)res << res.GetType ();
  
  for (cit = res.begin (new atomset_and (new no_pse_lp_atom_set (),
					 new no_hydrogen_set ()));
       cit != res.end ();
       ++cit)
    atoms.push_back (cit);
  
  obs << atoms.size ();
  
  for (ciit = atoms.begin (); ciit != atoms.end (); ++ciit)
    obs << **ciit;
  return obs;
}



iPdbstream&
operator>> (iPdbstream &ips, CResidue &newResidue)
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
  
  if (vec.size () != 0)
    {
      vector< CAtom > filteredVec;
      vector< CAtom >::iterator it;
      no_pse_lp_atom_set filter;

      for (it = vec.begin (); it != vec.end (); ++it)
	if (filter (*it))
	  filteredVec.push_back (*it);
      
      newResidue = CResidue (ips.GetPrevResType (), filteredVec,
			     ips.GetPrevResId ());
      ips.NewRes ();
    }
  return ips;
}
  


oPdbstream&
operator<< (oPdbstream &ops, const CResidue &res)
{
  CResidue::const_iterator cit;
  const t_Residue *type = res.GetType ();

  ops.SetResType (type);
  ops.SetResId (res);
  
  for (cit = res.begin (); cit != res.end (); ++cit)
    ops << *cit;
  return ops;
}



ostream&
operator<< (ostream &outStream, const CResidue &res)
{
  if (res.GetType () != 0)
    {
      CResidue::const_iterator cit;
      
      outStream << *res.GetType () << '(' << (const CResId&)res
		<< ") type=" << *res.GetType () << ":" << endl;
      for (cit = res.begin (); cit != res.end (); ++cit)
	outStream << *cit << endl;
    }
  return outStream;
}
