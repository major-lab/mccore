//                              -*- Mode: C++ -*- 
// CResidue.cc
// Copyright � 2000 Laboratoire de Biologie Informatique et Th�orique.
// Author           : S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Nov 14 17:22:54 2000
// Update Count     : 5
// Status           : Ok.
// 


#include <iostream.h>
#include <set.h>
#include <algo.h>
#include <string.h>
#include <stdarg.h>

#include "CResidue.h"

#include "McCore.h"

#include "AtomType.h"
#include "Binstream.h"
#include "CException.h"
#include "CMessageQueue.h"
#include "CPoint3D.h"
#include "Pdbstream.h"
#include "ResidueType.h"



int CResidue::count = 0;



residue_iterator::residue_iterator ()
  : mRes (0),
    mPos (0),
    mSet (new all_atom_set ()),
    mOption (new all_atom_set ())
{ }



residue_iterator::residue_iterator (CResidue *nRes, int nPos,
				    AtomSet *nSet, AtomSet *nOption)
  : mRes (nRes), mPos (nPos), mSet (nSet), mOption (nOption)
{
  size_type size = mRes->size ();

  if (! mSet)
    mSet = new all_atom_set ();
  if (! mOption)
    mOption = new all_atom_set ();
  while (mPos < size
	 && ! ((*mSet) (mRes->mAtomRef[mPos])
	       && (*mOption) (mRes->mAtomRef[mPos])))
    ++mPos;
}



residue_iterator::residue_iterator (const residue_iterator &right)
  : mRes (right.mRes),
    mPos (right.mPos),
    mSet (right.mSet->clone ()),
    mOption (right.mOption->clone ())
{ }



residue_iterator&
residue_iterator::operator= (const residue_iterator &right)
{
  if (this != &right)
    {
      mRes = right.mRes;
      mPos = right.mPos;
      delete mSet;
      mSet = right.mSet->clone ();
      delete mOption;
      mOption = right.mOption->clone ();
    }
  return *this;
}



residue_iterator&
residue_iterator::operator+= (difference_type k)
{
  size_type size = mRes->mAtomRef.size ();

  while (k > 0 && ++mPos < size)
    if (! (mSet->operator() (mRes->mAtomRef[mPos])
	   && mOption->operator() (mRes->mAtomRef[mPos])))
      --k;
  return *this;
}



residue_iterator::pointer
residue_iterator::operator-> () const
{
  return &(mRes->Place (mPos));
}



residue_iterator::reference
residue_iterator::operator* () const
{
  return mRes->Place (mPos);
}



residue_iterator&
residue_iterator::operator++ ()
{
  size_type size = mRes->mAtomRef.size ();

  if (mPos < size)
    while (++mPos < size
	   && ! (mSet->operator() (mRes->mAtomRef[mPos])
		 && mOption->operator() (mRes->mAtomRef[mPos])));
  return *this;
}



residue_iterator
residue_iterator::operator++ (int ign)
{
  residue_iterator ret = *this;
  size_type size = mRes->mAtomRef.size ();

  if (mPos < size)
    while (++mPos < size
	   && ! (mSet->operator() (mRes->mAtomRef[mPos])
		 && mOption->operator() (mRes->mAtomRef[mPos])));
  return ret;
}



residue_iterator
residue_iterator::operator+ (difference_type k) const
{
  return residue_iterator (*this) += k;
}



residue_iterator::difference_type
residue_iterator::operator- (const residue_iterator &i) const
{
  return difference_type (mPos - i.mPos);
}



const_residue_iterator::const_residue_iterator ()
  : mRes (0),
    mPos (0),
    mSet (new all_atom_set ()),
    mOption (new all_atom_set ())
{ }



const_residue_iterator::const_residue_iterator (const CResidue *nRes,
						int nPos,
						const AtomSet *nSet,
						const AtomSet *nOption)
  : mRes (nRes), mPos (nPos), mSet (nSet), mOption (nOption)
{
  size_type size = mRes->size ();

  if (! mSet)
    mSet = new all_atom_set ();
  if (! mOption)
    mOption = new all_atom_set ();
  while (mPos < size
	 && ! (mSet->operator() (mRes->mAtomRef[mPos])
	       && mOption->operator() (mRes->mAtomRef[mPos])))
    ++mPos;
}



const_residue_iterator::const_residue_iterator (const const_residue_iterator &right)
  : mRes (right.mRes),
    mPos (right.mPos),
    mSet (right.mSet->clone ()),
    mOption (right.mOption->clone ())
{ }



const_residue_iterator&
const_residue_iterator::operator= (const const_residue_iterator &right)
{
  if (this != &right)
    {
      mRes = right.mRes;
      mPos = right.mPos;
      delete mSet;
      mSet = right.mSet->clone ();
      delete mOption;
      mOption = right.mOption->clone ();
    }
  return *this;
}



const_residue_iterator&
const_residue_iterator::operator+= (difference_type k)
{
  size_type size = mRes->mAtomRef.size ();

  while (k > 0 && ++mPos < size)
    if (! (mSet->operator() (mRes->mAtomRef[mPos])
	   && mOption->operator() (mRes->mAtomRef[mPos])))
      --k;
  return *this;
}



const_residue_iterator::pointer
const_residue_iterator::operator-> () const
{
  return &(mRes->Place (mPos));
}



const_residue_iterator::reference
const_residue_iterator::operator* () const
{
  return mRes->Place (mPos);
}



const_residue_iterator&
const_residue_iterator::operator++ ()
{
  size_type size = mRes->mAtomRef.size ();

  if (mPos < size)
    while (++mPos < size
	   && ! (mSet->operator() (mRes->mAtomRef[mPos])
		 && mOption->operator() (mRes->mAtomRef[mPos])));
  return *this;
}



const_residue_iterator
const_residue_iterator::operator++ (int ign)
{
  const_residue_iterator ret = *this;
  size_type size = mRes->mAtomRef.size ();
  
  if (mPos < size)
    while (++mPos < size
	   && ! (mSet->operator() (mRes->mAtomRef[mPos])
		 && mOption->operator() (mRes->mAtomRef[mPos])));
  return ret;
}



const_residue_iterator
const_residue_iterator::operator+ (difference_type k) const
{
  return const_residue_iterator (*this) += k;
}



const_residue_iterator::difference_type
const_residue_iterator::operator- (const const_residue_iterator &i) const
{
  return difference_type (mPos - i.mPos);
}



CResidue::CResidue (t_Residue *type, const vector< CAtom > &vec,
		    const CResId &nId, t_Residue *readtype)
  : CResId (nId), mType (type), mReadType (readtype),
    mResName (0), mAtomRef (vec), mAtomResPos (vec.size (), -1)
{
  count++;
  const CAtom *pivot[3] = {0, 0, 0};
  vector< CAtom >::iterator it;
  vector< CAtom >::size_type i;
  
  for (it = mAtomRef.begin (), i = 0; it != mAtomRef.end (); ++it, ++i)
    {
      map< t_Atom*, int >::iterator pos = mAtomIndex.find (it->GetType ());
      
      if (pos != mAtomIndex.end ())
	gOut(2) << "CResidue: Duplicated atom ["
		<< *it->GetType () << "] in residue "
		<< nId << "." << endl;
      else
	mAtomIndex[it->GetType ()] = i;
    }

  if (! mType)
    return;
  
  // PSY and PSZ creation for nucleic acid.
  if (mType->is_Purine () || mType->is_Pyrimidine ())
    {
      const CPoint3D *p1 = 0, *p2 = 0, *p3 = 0;
      
      if ((mType->is_Purine ()
	   && (p1 = Ref (a_N9))
	   && (p2 = Ref (a_C8))
	   && (p3 = Ref (a_C4)))
	  || (mType->is_Pyrimidine ()
	      && (p1 = Ref (a_N1))
	      && (p2 = Ref (a_C6))
	      && (p3 = Ref (a_C2))))
	{
	  CPoint3D a = (*p2 - *p1).Normalize ();
	  CPoint3D b = (*p3 - *p1).Normalize ();
	  CPoint3D Y = *p1 + (a + b).Normalize ();
	  CPoint3D Z = *p1 + (b.Cross (a)).Normalize ();

	  Create (CAtom (Y.GetX (), Y.GetY (), Y.GetZ (), a_PSY));
	  Create (CAtom (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSZ));
	}
      else
	{
	  // Create an invalid residue.
	  gOut(1) << "Residue " << *type << "-" << nId
		  << " is missing one or more critical atoms. (1)<br>" 
		  << endl;
	  mReadType = type;
	  mType = 0;
	  return;
	}
    }
  
  // Set Pivot
  if (mType->is_Phosphate ())
    {
      pivot[0] = Ref (a_P);
      pivot[1] = Ref (a_O3p);
      pivot[2] = Ref (a_O5p);
    }
  else if (mType->is_NucleicAcid ())
    {
      pivot[0] = mType->is_Purine () ? Ref (a_N9) : Ref (a_N1);
      pivot[1] = Ref (a_PSY);
      pivot[2] = Ref (a_PSZ);
    }
  else if (mAtomRef.size () >= 3)
    {
      pivot[0] = &(mAtomRef[0]);
      pivot[1] = &(mAtomRef[1]);
      pivot[2] = &(mAtomRef[2]);
    }
  else
    return;

  // Fix res type
  // -- Si le type est d�j� sp�cialis�, il n'y a aucun changement.
  if (Ref (a_C1p))
    {
      if (Ref (a_O2p))
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
      AddHydrogens ();
      AddLP ();
    }
}



CResidue::CResidue (const CResidue& right)
  : CResId (right), mType (right.mType),
    mReadType (right.mReadType), mResName (0), mAtomRef (right.mAtomRef),
    mAtomResPos (right.mAtomResPos), mAtomIndex (right.mAtomIndex),
    mAtomRes (right.mAtomRes), mTfo (right.mTfo)    
{
  count++;
  if (right.mResName)
    {
      mResName = new char[strlen (right.mResName) + 1];
      strcpy (mResName, right.mResName);
    }
}



CResidue::~CResidue ()
{
  count--;
  if (mResName)
    delete[] mResName; 
}



const CResidue&
CResidue::operator= (const CResidue &right)
{
  if (&right != this)
    {
      CResId::operator= (right);
      mType = right.mType;
      mReadType = right.mReadType;
      if (mResName)
	{
	  delete[] mResName;
	  mResName = 0;
	}
      if (right.mResName)
	{
	  mResName = new char[strlen (right.mResName) + 1];
	  strcpy (mResName, right.mResName);
	}
      mAtomRef = right.mAtomRef;
      mAtomResPos = right.mAtomResPos;
      mAtomIndex = right.mAtomIndex;
      mAtomRes = right.mAtomRes;
      mTfo = right.mTfo;
    }
  return *this;
}



bool
CResidue::operator== (const CResidue &right) const
{
  return CResId::operator== (right) && mType == right.mType;
}



CAtom&
CResidue::operator[] (t_Atom *type)
{
  map< t_Atom*, int >::iterator i = mAtomIndex.find (type);
  
  if (i == mAtomIndex.end ())
    {
      mAtomRef.push_back (CAtom ());
      mAtomResPos.push_back (-1);
      mAtomIndex[type] = (int) mAtomResPos.size ();
      mAtomRes.push_back (CAtom ());
      i = mAtomIndex.find (type);
    }
  else
    Place (i->second);
  return mAtomRes[mAtomResPos[i->second]];
}



const CAtom&
CResidue::operator[] (t_Atom *type) const
{
  map< t_Atom*, int >::const_iterator cit = mAtomIndex.find (type);
  
  if (cit == mAtomIndex.end ())
    return mAtomRes[mAtomRes.size ()];
  else
    {
      Place (cit->second);
      return mAtomRes[mAtomResPos[cit->second]];
    }
}



CResidue::iterator
CResidue::find (t_Atom *k)
{
  map< t_Atom*, int >::iterator it = mAtomIndex.find (k);

  if (it == mAtomIndex.end ())
    return end ();
  else
    return iterator (this, it->second);
}



CResidue::const_iterator
CResidue::find (t_Atom *k) const
{
  map< t_Atom*, int >::const_iterator cit = mAtomIndex.find (k);

  if (cit == mAtomIndex.end ())
    return end ();
  else
    return const_iterator (this, cit->second);
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
    {
      mResName = new char[strlen (nName) + 1];
      strcpy (mResName, nName);
    }
}



void
CResidue::SetTransfo (const CTransfo &tfo)
{
  vector< int >::iterator i;
  
  mTfo = tfo; 
  mAtomRes.clear ();
  for (i = mAtomResPos.begin (); i != mAtomResPos.end (); ++i)
    *i = -1;
}



const char*
CResidue::GetResName () const
{
  return mResName == 0 ? *mType : mResName;
}



CAtom&
CResidue::Place (int pos) const
{
  int &new_pos = mAtomResPos[pos];

  if (new_pos == -1)
    {
      mAtomRes.push_back (mAtomRef[pos]);
      new_pos = mAtomRes.size () - 1;
      mAtomRes[new_pos].Transform (mTfo);
    }
  return mAtomRes[new_pos];
}



const CAtom*
CResidue::Ref (t_Atom *t) const
{
  map< t_Atom*, int >::const_iterator i = mAtomIndex.find (t);
  
  if (i != mAtomIndex.end ())
    return &(mAtomRef[i->second]);
  else
    return 0;
}



void
CResidue::Create (const CAtom &a)
{
  map< t_Atom*, int >::iterator i = mAtomIndex.find (a.GetType ());
  
  if (i == mAtomIndex.end ())
    {
      mAtomIndex[a.GetType ()] = mAtomRef.size ();
      mAtomRef.push_back (a);
      mAtomResPos.push_back (-1);
    }
  else
    {
      int pos;

      mAtomRef[i->second] = a;
      if ((pos = mAtomResPos[i->second]) != -1)
	{
	  mAtomRes[pos] = mAtomRef[i->second];
	  mAtomRes[pos].Transform (mTfo);
	}
    }
}



void
CResidue::erase (t_Atom *type)
{
  map< t_Atom*, int >::iterator i = mAtomIndex.find (type);

  if (i != mAtomIndex.end ())
    {
      vector< CAtom >::const_iterator cit;
      vector< CAtom >::size_type index;
      
      mAtomRef.erase (mAtomRef.begin () + i->second);
      mAtomIndex.clear ();
      mAtomResPos.clear ();
      for (cit = mAtomRef.begin (), index = 0;
	   cit != mAtomRef.end ();
	   ++cit, ++index)
	{
	  mAtomIndex[cit->GetType ()] = index;
	  mAtomResPos.push_back (-1);
	}
    }
}



void
CResidue::AddHydrogens ()
{
  // Add Hydrogens
  float C_H_dist = 1.08;
  float N_H_dist = 1.00;
  float tan60 = 1.7320508;
  CPoint3D x, y, z, up, a, b;

  if (mType->is_A ())
    {
      if (!(Ref (a_C2) && Ref (a_N1) && Ref (a_N3) && Ref (a_C8)
	    && Ref (a_N7) && Ref (a_N9) && Ref (a_C6) && Ref (a_C5)
	    && Ref (a_N6) && Ref (a_C4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms.<br>" 
		  << endl;
	  // Invalid residue
	  mReadType = mType;
	  mType = 0;
	  return;
	}
      
      // H2
      x = (*Ref (a_C2) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C2) - *Ref (a_N3)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H2 = *Ref (a_C2) + z * C_H_dist;
    
      // H8
      x = (*Ref (a_C8) - *Ref (a_N7)).Normalize ();
      y = (*Ref (a_C8) - *Ref (a_N9)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H8 = *Ref (a_C8) + z * C_H_dist;
      
      // 1H6 and 2H6
      x = (*Ref (a_C6) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C6) - *Ref (a_C5)).Normalize ();
      z = (*Ref (a_N6) - *Ref (a_C6)).Normalize ();  // axe N6-C6
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H61 = *Ref (a_N6) + a * N_H_dist;
      CPoint3D H62 = *Ref (a_N6) + b * N_H_dist;
      
      Create (CAtom (H2.GetX (), H2.GetY (), H2.GetZ (), a_H2));
      Create (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      Create (CAtom (H61.GetX (), H61.GetY (), H61.GetZ (), a_1H6));
      Create (CAtom (H62.GetX (), H62.GetY (), H62.GetZ (), a_2H6));
    } 
  else if (mType->is_G ())
    { 
      if (!(Ref (a_N1) && Ref (a_C2) && Ref (a_C6) && Ref (a_C8)
	    && Ref (a_N7) && Ref (a_N9) && Ref (a_N3) && Ref (a_N2)
	    && Ref (a_C4) && Ref (a_C5) && Ref (a_O6)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms.<br>" 
		  << endl;
	  // invalid residue
	  mReadType = mType;
	  mType = 0;
	  return;
	}

      // H1
      x = (*Ref (a_N1) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N1) - *Ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H1 = *Ref (a_N1) + z * N_H_dist;
      
      // H8
      x = (*Ref (a_C8) - *Ref (a_N7)).Normalize ();
      y = (*Ref (a_C8) - *Ref (a_N9)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H8 = *Ref (a_C8) + z * C_H_dist;
      
      // 1H2 and 2H2
      x = (*Ref (a_C2) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C2) - *Ref (a_N3)).Normalize ();
      z = (*Ref (a_N2) - *Ref (a_C2)).Normalize ();  // axe N2-C2
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H21 = *Ref (a_N2) + b * N_H_dist;
      CPoint3D H22 = *Ref (a_N2) + a * N_H_dist;
      
      Create (CAtom (H1.GetX (), H1.GetY (), H1.GetZ (), a_H1));
      Create (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      Create (CAtom (H21.GetX (), H21.GetY (), H21.GetZ (), a_1H2));
      Create (CAtom (H22.GetX (), H22.GetY (), H22.GetZ (), a_2H2));
    }
  else if (mType->is_C ())
    {
      if (!(Ref (a_C5) && Ref (a_C4) && Ref (a_C6) && Ref (a_N1)
	    && Ref (a_N3) && Ref (a_N4) && Ref (a_C6) && Ref (a_C5)
	    && Ref (a_C2) && Ref (a_O2)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms.<br>" 
		  << endl;
	  // invalid residue
	  mReadType = mType;
	  mType = 0;
	  return;
	}
      
      // H5
      x = (*Ref (a_C5) - *Ref (a_C4)).Normalize ();
      y = (*Ref (a_C5) - *Ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H5 = *Ref (a_C5) + z * C_H_dist;
      
      // H6
      x = (*Ref (a_C6) - *Ref (a_C5)).Normalize ();
      y = (*Ref (a_C6) - *Ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *Ref (a_C6) + z * C_H_dist;
      
      // 1H4 and 2H4
      x = (*Ref (a_C4) - *Ref (a_N3)).Normalize ();
      y = (*Ref (a_C4) - *Ref (a_C5)).Normalize ();
      z = (*Ref (a_N4) - *Ref (a_C4)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D H41 = *Ref (a_N4) + b * N_H_dist;
      CPoint3D H42 = *Ref (a_N4) + a * N_H_dist;
      
      Create (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      Create (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
      Create (CAtom (H41.GetX (), H41.GetY (), H41.GetZ (), a_1H4));
      Create (CAtom (H42.GetX (), H42.GetY (), H42.GetZ (), a_2H4));
    } 
  else if (mType->is_U ())
    {
      if (!(Ref (a_N3) && Ref (a_C2) && Ref (a_C4) && Ref (a_C5)
	    && Ref (a_C6) && Ref (a_N1) && Ref (a_O2) && Ref (a_O4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms.<br>" 
		  << endl;
	  // invalid residue
	  mReadType = mType;
	  mType = 0;
	  return;
	}
      
      // H3
      x = (*Ref (a_N3) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N3) - *Ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H3 = *Ref (a_N3) + z * N_H_dist;
      
      // H5
      x = (*Ref (a_C5) - *Ref (a_C4)).Normalize ();
      y = (*Ref (a_C5) - *Ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H5 = *Ref (a_C5) + z * C_H_dist;
      
      // H6
      x = (*Ref (a_C6) - *Ref (a_C5)).Normalize ();
      y = (*Ref (a_C6) - *Ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *Ref (a_C6) + z * C_H_dist;
      
      Create (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      Create (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      Create (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
    }
  else if (mType->is_T ())
    {
      if (!(Ref (a_N3) && Ref (a_C2) && Ref (a_C4) && Ref (a_C5)
	    && Ref (a_C6) && Ref (a_N1) && Ref (a_O2) && Ref (a_O4)))
	{
	  gOut(1) << "Residue " << *mType << "-" << *(CResId*)this
		  << " is missing one or more critical atoms.<br>" 
		  << endl;
	  // invalid residue
	  mReadType = mType;
	  mType = 0;
	  return;
	}
      
      // H3
      x = (*Ref (a_N3) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N3) - *Ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H3 = *Ref (a_N3) + z * N_H_dist;
      
      // H6
      x = (*Ref (a_C6) - *Ref (a_C5)).Normalize ();
      y = (*Ref (a_C6) - *Ref (a_N1)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D H6 = *Ref (a_C6) + z * C_H_dist;
      
      Create (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      Create (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
    }
  
  if (mType->is_NucleicAcid ())
    {
      const CPoint3D *r1, *r2, *r3, *r4;
      
      //  H1p
      r1 = Ref (a_C1p);
      r2 = Ref (a_C2p);
      r3 = (mType->is_Purine ()) ? Ref (a_N9) : Ref (a_N1);
      r4 = Ref (a_O4p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H1p = *r1 + (x + y + z).Normalize () * 1.09;
	  Create (CAtom (H1p.GetX (), H1p.GetY (), H1p.GetZ (), a_H1p));
	}
      
      //  H3p
      r1 = Ref (a_C3p);
      r2 = Ref (a_C2p);
      r3 = Ref (a_O3p);
      r4 = Ref (a_C4p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H3p = *r1 + (x + y + z).Normalize () * 1.09;
	  Create (CAtom (H3p.GetX (), H3p.GetY (), H3p.GetZ (), a_H3p));
	}
      
      //  H4p
      r1 = Ref (a_C4p);
      r2 = Ref (a_C3p);
      r3 = Ref (a_O4p);
      r4 = Ref (a_C5p);
      if (r1 && r2 && r3 && r4)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (*r1 - *r4).Normalize ();
	  
	  CPoint3D H4p = *r1 + (x + y + z).Normalize () * 1.09;
	  Create (CAtom (H4p.GetX (), H4p.GetY (), H4p.GetZ (), a_H4p));
	}
      
      
      //  1H5p  2H5p
      r1 = Ref (a_C5p);
      r2 = Ref (a_C4p);
      r3 = Ref (a_O5p);
      if (r1 && r2 && r3)
	{
	  x = (*r1 - *r2).Normalize ();
	  y = (*r1 - *r3).Normalize ();
	  z = (x + y).Normalize ();
	  up = x.Cross (y).Normalize ();
	  
	  CPoint3D H51p = *r1 + (up * 1.386 + z).Normalize () * 1.09;
	  CPoint3D H52p = *r1 + (-up * 1.386 + z).Normalize () * 1.09;
	  Create (CAtom (H51p.GetX (), H51p.GetY (), H51p.GetZ (), a_1H5p));
	  Create (CAtom (H52p.GetX (), H52p.GetY (), H52p.GetZ (), a_2H5p));
	}
      
      //  HO3p  // optionel
      
      if (mType->is_RNA ())
	{
	  //  H2p
	  r1 = Ref (a_C2p);
	  r2 = Ref (a_C1p);
	  r3 = Ref (a_C3p);
	  r4 = Ref (a_O2p);
	  if (r1 && r2 && r3 && r4)
	    {
	      x = (*r1 - *r2).Normalize ();
	      y = (*r1 - *r3).Normalize ();
	      z = (*r1 - *r4).Normalize ();
	      
	      CPoint3D H2p = *r1 + (x + y + z).Normalize () * 1.09;
	      Create (CAtom (H2p.GetX (), H2p.GetY (), H2p.GetZ (), a_H2p));
	    }
	  
	  // HO2p
	  r1 = Ref (a_O2p);
	  r2 = Ref (a_C2p);
	  r3 = Ref (a_C1p);
	  if (r1 && r2 && r3 && !Ref (a_HO2p))
	    {
	      x = (*r2 - *r3).Normalize ();
	      y = (*r1 - *r2).Normalize ();
	      z = x.Cross (y).Cross (y).Normalize ();
	      
	      CPoint3D HO2p = *r1 + (y * 0.354 - z).Normalize () * 1.03;
	      Create (CAtom (HO2p.GetX (), HO2p.GetY (), HO2p.GetZ (), a_HO2p));
	    }
	  
	  
	}
      else if (mType->is_DNA ())
	{
	  // 1H2p 2H2p
	  r1 = Ref (a_C2p);
	  r2 = Ref (a_C1p);
	  r3 = Ref (a_C3p);
	  if (r1 && r2 && r3)
	    {
	      x = (*r1 - *r2).Normalize ();
	      y = (*r1 - *r3).Normalize ();
	      z = (x + y).Normalize ();
	      up = x.Cross (y).Normalize ();
	      
	      CPoint3D H21p = *r1 + (up * 1.386 + z).Normalize () * 1.09;
	      CPoint3D H22p = *r1 + (-up * 1.386 + z).Normalize () * 1.09;
	      Create (CAtom (H21p.GetX (), H21p.GetY (), H21p.GetZ (), a_1H2p));
	      Create (CAtom (H22p.GetX (), H22p.GetY (), H22p.GetZ (), a_2H2p));
	    }
	}
    }
}



void
CResidue::AddLP ()
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
      x = (*Ref (a_N1) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N1) - *Ref (a_C6)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP1 = *Ref (a_N1) + z * N_LP_dist;
      
      // LP3
      x = (*Ref (a_N3) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N3) - *Ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *Ref (a_N3) + z * N_LP_dist;
      
      // LP7
      x = (*Ref (a_N7) - *Ref (a_C5)).Normalize ();
      y = (*Ref (a_N7) - *Ref (a_C8)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP7 = *Ref (a_N7) + z * N_LP_dist;
      
      Create (CAtom (LP1.GetX (), LP1.GetY (), LP1.GetZ (), a_LP1));
      Create (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      Create (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
    }
  else if (mType->is_G ())
    {
      // LP3
      x = (*Ref (a_N3) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N3) - *Ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *Ref (a_N3) + z * N_LP_dist;
      
      // LP7
      x = (*Ref (a_N7) - *Ref (a_C5)).Normalize ();
      y = (*Ref (a_N7) - *Ref (a_C8)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP7 = *Ref (a_N7) + z * N_LP_dist;
      
      // 1LP6 and 2LP6
      x = (*Ref (a_C6) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C6) - *Ref (a_C5)).Normalize ();
      z = (*Ref (a_O6) - *Ref (a_C6)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP61 = *Ref (a_O6) + b * O_LP_dist;
      CPoint3D LP62 = *Ref (a_O6) + a * O_LP_dist;
      
      Create (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      Create (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
      Create (CAtom (LP61.GetX (), LP61.GetY (), LP61.GetZ (), a_1LP6));
      Create (CAtom (LP62.GetX (), LP62.GetY (), LP62.GetZ (), a_2LP6));
    }
  else if (mType->is_C ())
    {
      // LP3
      x = (*Ref (a_N3) - *Ref (a_C2)).Normalize ();
      y = (*Ref (a_N3) - *Ref (a_C4)).Normalize ();
      z = (x + y).Normalize ();
      CPoint3D LP3 = *Ref (a_N3) + z * N_LP_dist;
      
      // 1LP2 and 2LP2
      x = (*Ref (a_C2) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C2) - *Ref (a_N3)).Normalize ();
      z = (*Ref (a_O2) - *Ref (a_C2)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP21 = *Ref (a_O2) + a * O_LP_dist;
      CPoint3D LP22 = *Ref (a_O2) + b * O_LP_dist;
      
      Create (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      Create (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      Create (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
    }
  else if (mType->is_U () || mType->is_T ())
    {
      // 1LP2 and 2LP2
      x = (*Ref (a_C2) - *Ref (a_N1)).Normalize ();
      y = (*Ref (a_C2) - *Ref (a_N3)).Normalize ();
      z = (*Ref (a_O2) - *Ref (a_C2)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP21 = *Ref (a_O2) + a * O_LP_dist;
      CPoint3D LP22 = *Ref (a_O2) + b * O_LP_dist;
      
      // 1LP2 and 2LP2
      x = (*Ref (a_C4) - *Ref (a_N3)).Normalize ();
      y = (*Ref (a_C4) - *Ref (a_C5)).Normalize ();
      z = (*Ref (a_O4) - *Ref (a_C4)).Normalize ();
      
      up = x.Cross (y).Normalize ();
      a = (z + up.Cross (z).Normalize () * tan60).Normalize ();
      b = (z + z.Cross (up).Normalize () * tan60).Normalize ();
      
      CPoint3D LP41 = *Ref (a_O4) + b * O_LP_dist;
      CPoint3D LP42 = *Ref (a_O4) + a * O_LP_dist;
      
      Create (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      Create (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
      Create (CAtom (LP41.GetX (), LP41.GetY (), LP41.GetZ (), a_1LP4));
      Create (CAtom (LP42.GetX (), LP42.GetY (), LP42.GetZ (), a_2LP4));
    }
}



CResidue
CResidue::Validate () const
{
  CResidue res (*this);
    
  if (mType != 0)
    {
      set< t_Atom* >::const_iterator optbegin, optend;
      set< t_Atom* > resset, diffset, allset;
      vector< CAtom >::iterator it;

      if (mType->is_DNA ())
	{
	  if (mType->is_dA ())
	    {
	      allset.insert (gdAOblAtomSet.begin (),  gdAOblAtomSet.end ());
	      optbegin = gdAOptAtomSet.begin ();
	      optend = gdAOptAtomSet.end ();
	    }
	  else if (mType->is_dC ())
	    {
	      allset.insert (gdCOblAtomSet.begin (), gdCOblAtomSet.end ());
	      optbegin = gdCOptAtomSet.begin ();
	      optend = gdCOptAtomSet.end ();
	    }
	  else if (mType->is_dG ())
	    {
	      allset.insert (gdGOblAtomSet.begin (), gdGOblAtomSet.end ());
	      optbegin = gdGOptAtomSet.begin ();
	      optend = gdGOptAtomSet.end ();
	    }
	  else if (mType->is_dT ())
	    {
	      allset.insert (gdTOblAtomSet.begin (), gdTOblAtomSet.end ());
	      optbegin = gdTOptAtomSet.begin ();
	      optend = gdTOptAtomSet.end ();
	    }
	}
      else if (mType->is_RNA ())
	{
	  if (mType->is_rA ())
	    {
	      allset.insert (grAOblAtomSet.begin (), grAOblAtomSet.end ());
	      optbegin = grAOptAtomSet.begin ();
	      optend = grAOptAtomSet.end ();
	    }
	  else if (mType->is_rC ())
	    {
	      allset.insert (grCOblAtomSet.begin (), grCOblAtomSet.end ());
	      optbegin = grCOptAtomSet.begin ();
	      optend = grCOptAtomSet.end ();
	    }
	  else if (mType->is_rG ())
	    {
	      allset.insert (grGOblAtomSet.begin (), grGOblAtomSet.end ());
	      optbegin = grGOptAtomSet.begin ();
	      optend = grGOptAtomSet.end ();
	    }
	  else if (mType->is_rU ())
	    {
	      allset.insert (grUOblAtomSet.begin (), grUOblAtomSet.end ());
	      optbegin = grUOptAtomSet.begin ();
	      optend = grUOptAtomSet.end ();
	    }
	}
      else
	{
	  res.mType = 0;
	  return res;
	}
      
      for (it = res.mAtomRef.begin (); it != res.mAtomRef.end (); ++it)
	resset.insert ((*it).GetType ());
      
      set_difference (allset.begin (), allset.end (),
		      resset.begin (), resset.end (),
		      inserter (diffset, diffset.begin ()));
      if (! diffset.empty ())
	{
	  res.mType = 0;
	  return res;
	}

      allset.insert (optbegin, optend);
      set_difference (resset.begin (), resset.end (),
		      allset.begin (), allset.end (),
		      inserter (diffset, diffset.begin ()));
      res.erase (diffset.begin (), diffset.end ());
      return res;
    }
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
CResidue::sort () const
{
  CResidue res (*this);
  vector< CAtom >::iterator it;
  vector< CAtom >::size_type index;

  ::sort (res.mAtomRef.begin (), res.mAtomRef.end ());
  res.mAtomIndex.clear ();
  res.mAtomResPos.clear ();
  for (it = res.mAtomRef.begin (), index = 0;
       it != res.mAtomRef.end ();
       ++it, ++index)
    {
      res.mAtomIndex[it->GetType ()] = index;
      res.mAtomResPos.push_back (-1);
    }
  return res;
}



CResidue
CResidue::select (t_Atom *at ...) const
{
  va_list ap;
  vector< CAtom > atom_vec;
  const CAtom *atom;

  atom = Ref (at);
  if (atom)
    atom_vec.push_back (*atom);
  
  va_start (ap, at);
  for (;;)
    {
      t_Atom* type = va_arg (ap, t_Atom*);
      if (type == 0)
	break;
      atom = Ref (type);
      if (atom)
	atom_vec.push_back (*atom);
    }
  return CResidue (mType, atom_vec, *(CResId*)this, mReadType);
}



CResidue&
CResidue::Transform (const CTransfo& tfo)
{
  vector< int >:: iterator i;
  
  mTfo = tfo * mTfo;
  mAtomRes.clear ();
  for (i = mAtomResPos.begin (); i != mAtomResPos.end (); ++i)
    *i = -1;
  return *this;
}



iBinstream&
operator>> (iBinstream& ibs, CResidue& res)
{
  CResId resid;
  t_Residue *type;
  t_Residue *readtype;
  vector< CAtom >::size_type i, nb;
  vector< CAtom > vec;

  ibs >> resid >> type >> readtype >> nb;
  for (i = 0; i < nb; i++)
    {
      vec.push_back (CAtom ());
      CAtom &aref = vec.back ();
      ibs >> aref;
    }
  res = CResidue (type, vec, resid, readtype);
  return ibs;
}



oBinstream&
operator<< (oBinstream& obs, const CResidue& res)
{
  vector< CResidue::const_iterator > atoms;
  vector< CResidue::const_iterator >::iterator ciit;
  CResidue::const_iterator cit;
  
  obs << (const CResId&)res << res.GetType ();
  
  for (cit = res.begin (new no_pse_lp_atom_set (), new no_hydrogen_opt ());
       cit != res.end ();
       ++cit)
    if (!(res.GetType ()->is_NucleicAcid ()))
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
      // Place le atom dans le r�sidu.
      vec.push_back (*ips.GetAtom ());
      ips.DeleteAtom ();
  }
  
  //  Boucle jusqu'� ce qu'on trouve un r�sidu complet.
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
	      // Peut-�tre le d�but d'un nouveau r�sidue???
	      if (atom.GetAltLocId () == ' ')
		{
		  if (! ips.GetPrevResType ()->is_Misc ())
		    {
		      // On rapporte l'"incident" seulement s'il s'agit d'un
		      // r�sidue "normal"!
		      gOut(2) << "Duplicate atoms <i>"
			      << ips.GetPrevResId () << ":"
			      << *(it->GetType ())
			      << "</i> in residue type <b>"
			      << *ips.GetPrevResType () << "</b><br>"
			      << endl;
		    }
		}
	      else
		atom.SetAltLocId ('_');  // On ignore l'atome
	    }
	  
	  // Place l'atom dans le r�sidu.
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

  if (type)
    ops.SetResType (type);
  else
    ops.SetResType (res.GetReadType ());
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