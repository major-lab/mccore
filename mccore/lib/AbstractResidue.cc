//                              -*- Mode: C++ -*- 
// AbstractResidue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct 12 18:21:12 2001
// Last Modified By : Patrick Gendron
// Last Modified On : Tue Feb  4 12:16:49 2003
// Update Count     : 16
// Status           : Unknown.
// 



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <set.h>
#include <algo.h>
#include <iterator.h>

#include "AbstractResidue.h"
#include "AtomType.h"
#include "Binstream.h"
#include "CAtom.h"
#include "McCore.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "ResidueTypeImp.h"



int AbstractResidue::count = 0;



AbstractResidue::ResidueIterator::ResidueIterator ()
  : res (0),
    filter (new all_atom_set ())
{
}
  


AbstractResidue::ResidueIterator::ResidueIterator (AbstractResidue *r,
						   ResMap::iterator p,
						   AtomSet *f)
  : res (r),
    pos (p),
    filter (f)
{
  ResMap::iterator last = res->mAtomIndex.end ();

  if (filter == 0)
    filter = new all_atom_set ();
  while (pos != last && ! (*filter) (res->ref (pos->second)))
    ++pos;
}
  


AbstractResidue::ResidueIterator::ResidueIterator (const ResidueIterator &right)
  : res (right.res),
    pos (right.pos),
    filter (right.filter->clone ())
{
}



AbstractResidue::ResidueIterator::~ResidueIterator ()
{
  delete filter;
}



AbstractResidue::ResidueIterator&
AbstractResidue::ResidueIterator::operator= (const ResidueIterator &right)
{
  if (this != &right)
    {
      res = right.res;
      pos = right.pos;
      delete filter;
      filter = right.filter->clone ();
    }
  return *this;
}



AbstractResidue::ResidueIterator&
AbstractResidue::ResidueIterator::operator+= (difference_type k)
{
  ResMap::iterator last = res->mAtomIndex.end ();

  while (k > 0 && pos != last)
    if (++pos != last && (*filter) (res->ref (pos->second)))
      --k;
  return *this;
}


  
AbstractResidue::iterator&
AbstractResidue::ResidueIterator::operator++ ()
{
  ResMap::iterator last = res->mAtomIndex.end ();

  while (pos != last)
    if (++pos == last || (*filter) (res->ref (pos->second)))
      break;
  return *this;
}



AbstractResidue::iterator
AbstractResidue::ResidueIterator::operator++ (int ign)
{
  ResidueIterator ret = *this;
  ResMap::iterator last = res->mAtomIndex.end ();

  while (pos != last)
    if (++pos == last || (*filter) (res->ref (pos->second)))
      break;
  return ret;
}



AbstractResidue::ResidueConstIterator::ResidueConstIterator ()
  : res (0),
    filter (new all_atom_set ())
{ }



AbstractResidue::ResidueConstIterator::ResidueConstIterator (const AbstractResidue *r,
							     ResMap::const_iterator p,
							     AtomSet *f)
  : res (r),
    pos (p),
    filter (f)
{
  ResMap::const_iterator last = res->mAtomIndex.end ();

  if (filter == 0)
    filter = new all_atom_set ();
  while (pos != last && ! (*filter) (res->ref (pos->second)))
    ++pos;
}



AbstractResidue::ResidueConstIterator::ResidueConstIterator (const AbstractResidue::const_iterator &right)
  : res (right.res),
    pos (right.pos),
    filter (right.filter->clone ())
{ }



AbstractResidue::ResidueConstIterator::ResidueConstIterator (const AbstractResidue::iterator &right)
  : res (right.res),
    pos (right.pos),
    filter (right.filter->clone ())
{ }



AbstractResidue::ResidueConstIterator::~ResidueConstIterator ()
{
  delete filter;
}



AbstractResidue::const_iterator&
AbstractResidue::ResidueConstIterator::operator= (const AbstractResidue::const_iterator &right)
{
  if (this != &right)
    {
      res = right.res;
      pos = right.pos;
      delete filter;
      filter = right.filter->clone ();
    }
  return *this;
}



AbstractResidue::const_iterator&
AbstractResidue::ResidueConstIterator::operator= (const AbstractResidue::iterator &right)
{
  res = right.res;
  pos = right.pos;
  delete filter;
  filter = right.filter->clone ();

  return *this;
}



AbstractResidue::const_iterator&
AbstractResidue::ResidueConstIterator::operator+= (difference_type k)
{
  ResMap::const_iterator last = res->mAtomIndex.end ();

  while (k > 0 && pos != last)
    if (++pos != last && (*filter) (res->ref (pos->second)))
      --k;
  return *this;
}



AbstractResidue::const_iterator&
AbstractResidue::ResidueConstIterator::operator++ ()
{
  ResMap::const_iterator last = res->mAtomIndex.end ();

  while (pos != last)
    if (++pos == last || (*filter) (res->ref (pos->second)))
      break;
  return *this;
}



AbstractResidue::const_iterator
AbstractResidue::ResidueConstIterator::operator++ (int ign)
{
  ResidueConstIterator ret = *this;
  ResMap::const_iterator last = res->mAtomIndex.end ();
  
  while (pos != last)
    if (++pos == last || (*filter) (res->ref (pos->second)))
      break;
  return ret;
}



AbstractResidue:: ~AbstractResidue ()
{
  --count;
}



AbstractResidue&
AbstractResidue::operator= (const AbstractResidue &right)
{
  if (this != &right)
    {
      resId = right.resId;
      mType = right.mType;
      mTfo = right.mTfo;
      mAtomIndex = right.mAtomIndex;
      }
  return *this;
}



void
AbstractResidue::addHydrogens ()
{
  float C_H_dist = 1.08;
  float N_H_dist = 1.00;
  float tan60 = 1.7320508;  // For NH2-like conformations
  float tan70 = 2.7474774;  // For CH3-like conformations
  float tan30 = 0.57735027;
  CPoint3D x, y, z, up, a, b;

  if (mType->is_A ())
    {
      if (!(ref (a_C2) && ref (a_N1) && ref (a_N3) && ref (a_C8)
	    && ref (a_N7) && ref (a_N9) && ref (a_C6) && ref (a_C5)
	    && ref (a_N6) && ref (a_C4)))
	{
	  gOut (2) << "Residue " << *mType << "-" << resId
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
      
      insert_local (CAtom (H2.GetX (), H2.GetY (), H2.GetZ (), a_H2));
      insert_local (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      insert_local (CAtom (H61.GetX (), H61.GetY (), H61.GetZ (), a_1H6));
      insert_local (CAtom (H62.GetX (), H62.GetY (), H62.GetZ (), a_2H6));
    } 
  else if (mType->is_G ())
    { 
      if (!(ref (a_N1) && ref (a_C2) && ref (a_C6) && ref (a_C8)
	    && ref (a_N7) && ref (a_N9) && ref (a_N3) && ref (a_N2)
	    && ref (a_C4) && ref (a_C5) && ref (a_O6)))
	{
	  gOut (2) << "Residue " << *mType << "-" << resId
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
      
      insert_local (CAtom (H1.GetX (), H1.GetY (), H1.GetZ (), a_H1));
      insert_local (CAtom (H8.GetX (), H8.GetY (), H8.GetZ (), a_H8));
      insert_local (CAtom (H21.GetX (), H21.GetY (), H21.GetZ (), a_1H2));
      insert_local (CAtom (H22.GetX (), H22.GetY (), H22.GetZ (), a_2H2));
    }
  else if (mType->is_C ())
    {
      if (!(ref (a_C5) && ref (a_C4) && ref (a_C6) && ref (a_N1)
	    && ref (a_N3) && ref (a_N4) && ref (a_C6) && ref (a_C5)
	    && ref (a_C2) && ref (a_O2)))
	{
	  gOut (2) << "Residue " << *mType << "-" << resId
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
      
      insert_local (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      insert_local (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
      insert_local (CAtom (H41.GetX (), H41.GetY (), H41.GetZ (), a_1H4));
      insert_local (CAtom (H42.GetX (), H42.GetY (), H42.GetZ (), a_2H4));
    } 
  else if (mType->is_U ())
    {
      if (!(ref (a_N3) && ref (a_C2) && ref (a_C4) && ref (a_C5)
	    && ref (a_C6) && ref (a_N1) && ref (a_O2) && ref (a_O4)))
	{
	  gOut (2) << "Residue " << *mType << "-" << resId
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
      
      insert_local (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      insert_local (CAtom (H5.GetX (), H5.GetY (), H5.GetZ (), a_H5));
      insert_local (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));
    }
  else if (mType->is_T ())
    {
      if (!(ref (a_N3) && ref (a_C2) && ref (a_C4) && ref (a_C5)
	    && ref (a_C6) && ref (a_N1) && ref (a_O2) && ref (a_O4)))
	{
	  gOut (2) << "Residue " << *mType << "-" << resId
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
      
      insert_local (CAtom (H3.GetX (), H3.GetY (), H3.GetZ (), a_H3));
      insert_local (CAtom (H6.GetX (), H6.GetY (), H6.GetZ (), a_H6));

      // 1H5M, 2H5M, 3H5M (arbitrarily placed)
      
      x = (*ref (a_C5M) - *ref (a_C5)).Normalize ();
      y = (*ref (a_C5) - *ref (a_C4)).Normalize ();
      up = x.Cross (y).Normalize ();
      z = x.Cross (up);
      
      CPoint3D H5M1 = *ref (a_C5M) + (x + z * tan70).Normalize () * C_H_dist;
      insert_local (CAtom (H5M1.GetX (), H5M1.GetY (), H5M1.GetZ (), a_1H5M));

      a = (up - z*tan30).Normalize ();
      CPoint3D H5M2 = *ref (a_C5M) + (x + a * tan70).Normalize () * C_H_dist;
      insert_local (CAtom (H5M2.GetX (), H5M2.GetY (), H5M2.GetZ (), a_2H5M));

      b = (-up - z*tan30).Normalize ();
      CPoint3D H5M3 = *ref (a_C5M) + (x + b * tan70).Normalize () * C_H_dist;
      insert_local (CAtom (H5M3.GetX (), H5M3.GetY (), H5M3.GetZ (), a_3H5M));
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
	  insert_local (CAtom (H1p.GetX (), H1p.GetY (), H1p.GetZ (), a_H1p));
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
	  insert_local (CAtom (H3p.GetX (), H3p.GetY (), H3p.GetZ (), a_H3p));
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
	  insert_local (CAtom (H4p.GetX (), H4p.GetY (), H4p.GetZ (), a_H4p));
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
	  insert_local (CAtom (H51p.GetX (), H51p.GetY (), H51p.GetZ (), a_1H5p));
	  insert_local (CAtom (H52p.GetX (), H52p.GetY (), H52p.GetZ (), a_2H5p));
	}
      
      //  HO3p  // optionel
      r1 = ref (a_O3p);
      r2 = ref (a_C3p);
      r3 = ref (a_C4p);
      if (r1 && r2 && r3/* && !ref (a_HO3p)*/)
	{
	  x = (*r2 - *r3).Normalize ();
	  y = (*r1 - *r2).Normalize ();
	  z = x.Cross (y).Cross (y).Normalize ();
	  
	  CPoint3D HO3p = *r1 + (y*0.354+z).Normalize () * 1.03;
	  insert_local (CAtom (HO3p.GetX (), HO3p.GetY (), HO3p.GetZ (), a_HO3p));
	}
	  

      
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
	      insert_local (CAtom (H2p.GetX (), H2p.GetY (), H2p.GetZ (), a_H2p));
	    }
	  
	  // HO2p (arbitrary position)
	  r1 = ref (a_O2p);
	  r2 = ref (a_C2p);
	  r3 = ref (a_C1p);
	  if (r1 && r2 && r3/* && !ref (a_HO2p)*/)
	    {
	      x = (*r2 - *r3).Normalize ();
	      y = (*r1 - *r2).Normalize ();
	      z = x.Cross (y).Cross (y).Normalize ();
	      
	      CPoint3D HO2p = *r1 + (y * 0.354 - z).Normalize () * 1.03;
	      insert_local (CAtom (HO2p.GetX (), HO2p.GetY (), HO2p.GetZ (), a_HO2p));
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
	      insert_local (CAtom (H21p.GetX (), H21p.GetY (), H21p.GetZ (), a_1H2p));
	      insert_local (CAtom (H22p.GetX (), H22p.GetY (), H22p.GetZ (), a_2H2p));
	    }
	}
    }
}



void
AbstractResidue::addLP ()
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
      
      insert_local (CAtom (LP1.GetX (), LP1.GetY (), LP1.GetZ (), a_LP1));
      insert_local (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert_local (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
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
      
      insert_local (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert_local (CAtom (LP7.GetX (), LP7.GetY (), LP7.GetZ (), a_LP7));
      insert_local (CAtom (LP61.GetX (), LP61.GetY (), LP61.GetZ (), a_1LP6));
      insert_local (CAtom (LP62.GetX (), LP62.GetY (), LP62.GetZ (), a_2LP6));
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
      
      insert_local (CAtom (LP3.GetX (), LP3.GetY (), LP3.GetZ (), a_LP3));
      insert_local (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      insert_local (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
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
      
      insert_local (CAtom (LP21.GetX (), LP21.GetY (), LP21.GetZ (), a_1LP2));
      insert_local (CAtom (LP22.GetX (), LP22.GetY (), LP22.GetZ (), a_2LP2));
      insert_local (CAtom (LP41.GetX (), LP41.GetY (), LP41.GetZ (), a_1LP4));
      insert_local (CAtom (LP42.GetX (), LP42.GetY (), LP42.GetZ (), a_2LP4));
    }
}



void
AbstractResidue::validate ()
{
  if (mType != 0)
    {
      set< t_Atom* >::const_iterator optbegin, optend, cit;
      set< t_Atom* > resset, diffset, allset;
      iterator it;
      
      if (mType->is_NucleicAcid ())
	{
	  removeOptionals ();
	  addHydrogens ();
	  addLP ();
	}

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
      else if (mType->is_AminoAcid ())
	{
	  if (mType->is_ALA ())
	    {
	      allset.insert (gALAOblAtomSet.begin (), gALAOblAtomSet.end ());
	      optbegin = gALAOptAtomSet.begin ();
	      optend = gALAOptAtomSet.end ();
	    }
	  else if (mType->is_ARG ())
	    {
	      allset.insert (gARGOblAtomSet.begin (), gARGOblAtomSet.end ());
	      optbegin = gARGOptAtomSet.begin ();
	      optend = gARGOptAtomSet.end ();
	    }
	  else if (mType->is_ASN ())
	    {
	      allset.insert (gASNOblAtomSet.begin (), gASNOblAtomSet.end ());
	      optbegin = gASNOptAtomSet.begin ();
	      optend = gASNOptAtomSet.end ();
	    }
	  else if (mType->is_ASP ())
	    {
	      allset.insert (gASPOblAtomSet.begin (), gASPOblAtomSet.end ());
	      optbegin = gASPOptAtomSet.begin ();
	      optend = gASPOptAtomSet.end ();
	    }
	  else if (mType->is_CYS ())
	    {
	      allset.insert (gCYSOblAtomSet.begin (), gCYSOblAtomSet.end ());
	      optbegin = gCYSOptAtomSet.begin ();
	      optend = gCYSOptAtomSet.end ();
	    }
	  else if (mType->is_GLN ())
	    {
	      allset.insert (gGLNOblAtomSet.begin (), gGLNOblAtomSet.end ());
	      optbegin = gGLNOptAtomSet.begin ();
	      optend = gGLNOptAtomSet.end ();
	    }
	  else if (mType->is_GLU ())
	    {
	      allset.insert (gGLUOblAtomSet.begin (), gGLUOblAtomSet.end ());
	      optbegin = gGLUOptAtomSet.begin ();
	      optend = gGLUOptAtomSet.end ();
	    }
	  else if (mType->is_GLY ())
	    {
	      allset.insert (gGLYOblAtomSet.begin (), gGLYOblAtomSet.end ());
	      optbegin = gGLYOptAtomSet.begin ();
	      optend = gGLYOptAtomSet.end ();
	    }
	  else if (mType->is_HIS ())
	    {
	      allset.insert (gHISOblAtomSet.begin (), gHISOblAtomSet.end ());
	      optbegin = gHISOptAtomSet.begin ();
	      optend = gHISOptAtomSet.end ();
	    }
	  else if (mType->is_ILE ())
	    {
	      allset.insert (gILEOblAtomSet.begin (), gILEOblAtomSet.end ());
	      optbegin = gILEOptAtomSet.begin ();
	      optend = gILEOptAtomSet.end ();
	    }
	  else if (mType->is_LEU ())
	    {
	      allset.insert (gLEUOblAtomSet.begin (), gLEUOblAtomSet.end ());
	      optbegin = gLEUOptAtomSet.begin ();
	      optend = gLEUOptAtomSet.end ();
	    }
	  else if (mType->is_LYS ())
	    {
	      allset.insert (gLYSOblAtomSet.begin (), gLYSOblAtomSet.end ());
	      optbegin = gLYSOptAtomSet.begin ();
	      optend = gLYSOptAtomSet.end ();
	    }
	  else if (mType->is_MET ())
	    {
	      allset.insert (gMETOblAtomSet.begin (), gMETOblAtomSet.end ());
	      optbegin = gMETOptAtomSet.begin ();
	      optend = gMETOptAtomSet.end ();
	    }
	  else if (mType->is_PHE ())
	    {
	      allset.insert (gPHEOblAtomSet.begin (), gPHEOblAtomSet.end ());
	      optbegin = gPHEOptAtomSet.begin ();
	      optend = gPHEOptAtomSet.end ();
	    }
	  else if (mType->is_PRO ())
	    {
	      allset.insert (gPROOblAtomSet.begin (), gPROOblAtomSet.end ());
	      optbegin = gPROOptAtomSet.begin ();
	      optend = gPROOptAtomSet.end ();
	    }
	  else if (mType->is_SER ())
	    {
	      allset.insert (gSEROblAtomSet.begin (), gSEROblAtomSet.end ());
	      optbegin = gSEROptAtomSet.begin ();
	      optend = gSEROptAtomSet.end ();
	    }
	  else if (mType->is_THR ())
	    {
	      allset.insert (gTHROblAtomSet.begin (), gTHROblAtomSet.end ());
	      optbegin = gTHROptAtomSet.begin ();
	      optend = gTHROptAtomSet.end ();
	    }
	  else if (mType->is_TRP ())
	    {
	      allset.insert (gTRPOblAtomSet.begin (), gTRPOblAtomSet.end ());
	      optbegin = gTRPOptAtomSet.begin ();
	      optend = gTRPOptAtomSet.end ();
	    }
	  else if (mType->is_TYR ())
	    {
	      allset.insert (gTYROblAtomSet.begin (), gTYROblAtomSet.end ());
	      optbegin = gTYROptAtomSet.begin ();
	      optend = gTYROptAtomSet.end ();
	    }
	  else if (mType->is_VAL ())
	    {
	      allset.insert (gVALOblAtomSet.begin (), gVALOblAtomSet.end ());
	      optbegin = gVALOptAtomSet.begin ();
	      optend = gVALOptAtomSet.end ();
	    }
	}
      else
	{
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);
	  
	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  gOut (3) << 'm';
	  return;
	}
      
      for (it = begin (); it != end (); ++it)
	resset.insert ((*it).GetType ());
      
      set_difference (allset.begin (), allset.end (),
		      resset.begin (), resset.end (),
		      inserter (diffset, diffset.begin ()));
      if (! diffset.empty ())
	{
	  map< const char *, t_Residue*, less_string >::iterator i
	    = gMiscResidueString.find ((const char*)*mType);

	  if (i == gMiscResidueString.end ())
	    mType = new rt_Misc ((const char*)*mType);
	  else
	    mType = i->second;
	  gOut (3) << 'i';
	}
      else
	{
	  allset.insert (optbegin, optend);
	  set_difference (resset.begin (), resset.end (),
			  allset.begin (), allset.end (),
			  inserter (diffset, diffset.begin ()));
	  for (cit = diffset.begin (); cit != diffset.end (); ++cit)
	    erase (*cit);
	  if (mType->is_AminoAcid ())
	    gOut (3) << 'a';
	  else
	    gOut (3) << 'n';
	}
    }
  else
    gOut (3) << 'i';
}



void
AbstractResidue::removeOptionals ()
{
  if (mType != 0)
    {
      set< t_Atom* >::const_iterator setbegin, setend;
      
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
	return;

      while (setbegin != setend)
	{
	  erase (*setbegin);
	  ++setbegin;
	}
    }
}



iBinstream&
operator>> (iBinstream &ibs, AbstractResidue &res)
{
  return res.read (ibs);
}



oBinstream&
operator<< (oBinstream &obs, const AbstractResidue &res)
{
  return res.write (obs);
}



iPdbstream&
operator>> (iPdbstream &ips, AbstractResidue &res)
{
  return res.read (ips);
}



oPdbstream&
operator<< (oPdbstream &ops, const AbstractResidue &res)
{
  return res.write (ops);
}



ostream&
operator<< (ostream &os, const AbstractResidue &res)
{
  return res.write (os);
}
