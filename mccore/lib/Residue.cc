//                              -*- Mode: C++ -*- 
// Residue.cc
// Copyright © 2001-03 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// Last Modified By : Philippe Thibault
// Last Modified On : Wed Mar 19 16:58:16 2003
// Update Count     : 9
// Status           : Unknown.
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
#include <list.h>
#include <algo.h>
#include <string.h>
#include <stdarg.h>

#include "AtomType.h"
#include "Binstream.h"
#include "CException.h"
#include "CPoint3D.h"
#include "McCore.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "Residue.h"
#include "ResidueTypeImp.h"



Residue::Residue (t_Residue *type,
		  vector< CAtom > &vec,
		  const CResId &nId)
  : AbstractResidue (nId, type),
    isPlaced (false),
    isIdentity (true)
{
  vector< CAtom >::iterator it;

  for (it = vec.begin (); it != vec.end (); ++it)
    mAtomRef.push_back (it->clone ());
  init ();
}



Residue::Residue (const Residue& right)
  : AbstractResidue (right),
    isPlaced (right.isPlaced),
    isIdentity (right.isIdentity)
{
  vector< CAtom* >::const_iterator cit;
  
  for (cit = right.mAtomRef.begin (); cit != right.mAtomRef.end (); ++cit)
    mAtomRef.push_back ((*cit)->clone ());
  for (cit = right.mAtomRes.begin (); cit != right.mAtomRes.end (); ++cit)
    mAtomRes.push_back ((*cit)->clone ());
}



Residue::~Residue ()
{
  vector< CAtom* >::iterator it;

  for (it = mAtomRef.begin (); it != mAtomRef.end (); ++it)
    delete *it;
  for (it = mAtomRes.begin (); it != mAtomRes.end (); ++it)
    delete *it;
}



void
Residue::setIdeal ()
{
  mAtomIndex.clear ();
  mAtomRef.clear ();
  mAtomRes.clear ();
  
  if (mType->is_rA ()) {
    insert (CAtom (0.213, 0.660, 1.287, a_N9));
    insert (CAtom (0.250, 2.016, 1.509, a_C4));
    insert (CAtom (0.016, 2.995, 0.619, a_N3));
    insert (CAtom (0.142, 4.189, 1.194, a_C2));
    insert (CAtom (0.451, 4.493, 2.459, a_N1));
    insert (CAtom (0.681, 3.485, 3.329, a_C6));
    insert (CAtom (0.990, 3.787, 4.592, a_N6));
    insert (CAtom (0.579, 2.170, 2.844, a_C5));
    insert (CAtom (0.747, 0.934, 3.454, a_N7));
    insert (CAtom (0.520, 0.074, 2.491, a_C8));
    insert (CAtom (0.000, 0.000, 0.000, a_C1p));
  } else if (mType->is_rC ()) {
    insert (CAtom (0.212, 0.668, 1.294, a_N1)); 
    insert (CAtom (0.193, -0.043, 2.462, a_C6));
    insert (CAtom (0.374, 2.055, 1.315, a_C2)); 
    insert (CAtom (0.388, 2.673, 0.240, a_O2)); 
    insert (CAtom (0.511, 2.687, 2.504, a_N3)); 
    insert (CAtom (0.491, 1.984, 3.638, a_C4)); 
    insert (CAtom (0.631, 2.649, 4.788, a_N4)); 
    insert (CAtom (0.328, 0.569, 3.645, a_C5)); 
    insert (CAtom (0.000, 0.000, 0.000, a_C1p));
  } else if (mType->is_rG ()) {
    insert (CAtom (0.214, 0.659, 1.283, a_N9)); 
    insert (CAtom (0.254, 2.014, 1.509, a_C4)); 
    insert (CAtom (0.034, 2.979, 0.591, a_N3)); 
    insert (CAtom (0.142, 4.190, 1.110, a_C2)); 
    insert (CAtom (-0.047, 5.269, 0.336, a_N2)); 
    insert (CAtom (0.444, 4.437, 2.427, a_N1)); 
    insert (CAtom (0.676, 3.459, 3.389, a_C6)); 
    insert (CAtom (0.941, 3.789, 4.552, a_O6)); 
    insert (CAtom (0.562, 2.154, 2.846, a_C5)); 
    insert (CAtom (0.712, 0.912, 3.448, a_N7)); 
    insert (CAtom (0.498, 0.057, 2.485, a_C8)); 
    insert (CAtom (0.000, 0.000, 0.000, a_C1p));
  } else if (mType->is_rU ()) {
    insert (CAtom (0.212, 0.676, 1.281, a_N1)); 
    insert (CAtom (0.195, -0.023, 2.466, a_C6));
    insert (CAtom (0.370, 2.048, 1.265, a_C2)); 
    insert (CAtom (0.390, 2.698, 0.235, a_O2)); 
    insert (CAtom (0.505, 2.629, 2.502, a_N3)); 
    insert (CAtom (0.497, 1.990, 3.725, a_C4)); 
    insert (CAtom (0.629, 2.653, 4.755, a_O4)); 
    insert (CAtom (0.329, 0.571, 3.657, a_C5)); 
    insert (CAtom (0.000, 0.000, 0.000, a_C1p));
  } else if (mType->is_Phosphate ()) {
      insert (CAtom ( 99.755, 106.228, 6.380, a_O3p));
      insert (CAtom (100.821, 105.050, 6.479, a_P));
      insert (CAtom (100.856, 104.272, 5.224, a_O1P));
      insert (CAtom (100.658, 104.316, 7.746, a_O2P));
      insert (CAtom (102.198, 105.850, 6.595, a_O5p));
  } else {
    gOut (2) << "Oups, setIdeal erased the residue " << (const char*)*mType
	     << "but the ideal confo is unknown.  Go get a coffee!" << endl;
  }
 
  Align ();
  init ();
}


Residue&
Residue::operator= (const Residue &right)
{
  vector< CAtom* >::const_iterator cit;
  vector< CAtom* >::iterator it;
  
  if (&right != this)
    {
      AbstractResidue::operator= (right);
      for (it = mAtomRef.begin (); it != mAtomRef.end (); ++it)
	delete *it;
      mAtomRef.clear ();
      for (cit = right.mAtomRef.begin (); cit != right.mAtomRef.end (); ++cit)
	mAtomRef.push_back ((*cit)->clone ());
      for (it = mAtomRes.begin (); it != mAtomRes.end (); ++it)
	delete *it;
      mAtomRes.clear ();
      for (cit = right.mAtomRes.begin (); cit != right.mAtomRes.end (); ++cit)
	mAtomRes.push_back ((*cit)->clone ());
      isPlaced = right.isPlaced;
      isIdentity = right.isIdentity;
    }
  return *this;
}



AbstractResidue&
Residue::operator= (const CTransfo &tfo)
{
  mTfo = tfo; 
  isPlaced = false;
  isIdentity = mTfo.isIdentity ();
  return *this;
}



CAtom&
Residue::operator[] (t_Atom *type)
{
  ResMap::iterator i = mAtomIndex.find (type);
  
  if (i == mAtomIndex.end ())
    {
      CAtom *clonedAtom;

      // keep this line until there is an AtomFM.
      clonedAtom = mAtomRef.empty () ? new CAtom () : mAtomRef[0]->clone ();
      clonedAtom->SetType (type);
      mAtomRef.push_back (clonedAtom->clone ());
      mAtomIndex[type] = size ();
      mAtomRes.push_back (clonedAtom);
      i = mAtomIndex.find (type);
    }
  return place (i->second);
}



const CAtom&
Residue::operator[] (const t_Atom *type) const
{
  ResMap::const_iterator cit = mAtomIndex.find (type);

  if (cit != mAtomIndex.end ())
    return res (cit->second);
  else
    return res (size ());
}



Residue::iterator
Residue::find (const t_Atom *k)
{
  ResMap::iterator it = mAtomIndex.find (k);

  if (it == mAtomIndex.end ())
    return end ();
  else
    return iterator (this, it);
}



Residue::const_iterator
Residue::find (const t_Atom *k) const
{
  ResMap::const_iterator cit = mAtomIndex.find (k);

  if (cit == mAtomIndex.end ())
    return end ();
  else
    return const_iterator (this, cit);
}



void
Residue::init ()
{
  const CAtom *pivot[3] = {0, 0, 0};
  vector< CAtom* >::iterator it;
  size_type i = 0;
  CAtom *clonedAtom;

  mAtomIndex.clear ();
  for (it = mAtomRes.begin (); it != mAtomRes.end (); ++it)
    delete *it;
  mAtomRes.clear ();
  it = mAtomRef.begin ();
  while (it != mAtomRef.end ())
    {
      t_Atom *type = (*it)->GetType ();
      ResMap::iterator pos = mAtomIndex.find (type);
      
      if (pos != mAtomIndex.end ())
	{
	  gOut(2) << "Residue: Duplicated atom [" << *mType
		  << "] in residue " << resId << "." << endl;
	  delete *it;
	  it = mAtomRef.erase (it);
	}
      else
	{
	  mAtomIndex[type] = i++;
	  mAtomRes.push_back ((*it)->clone ());
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
	   && (p1 = clonedAtom = ref (a_N9)->clone ())
	   && (p2 = ref (a_C8))
	   && (p3 = ref (a_C4)))
	  || (mType->is_Pyrimidine ()
	      && (p1 = clonedAtom = ref (a_N1)->clone ())
	      && (p2 = ref (a_C6))
	      && (p3 = ref (a_C2))))
	{
	  CPoint3D a = (*p2 - *p1).Normalize ();
	  CPoint3D b = (*p3 - *p1).Normalize ();
	  CPoint3D Y = *p1 + (a + b).Normalize ();
	  CPoint3D Z = *p1 + (b.Cross (a)).Normalize ();

	  clonedAtom->SetAll (Y.GetX (), Y.GetY (), Y.GetZ (), a_PSY);
	  insert_local (*clonedAtom);
	  clonedAtom->SetAll (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSZ);
	  insert_local (*clonedAtom);
	  delete clonedAtom;
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut(1) << "Residue " << *mType << "-" << resId
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
      
      if ((p1 = ref (a_CA))
	  && (p2 = ref (a_N))
	  && (p3 = ref (a_C)))
	{
	  clonedAtom = ref (a_CA)->clone ();
	  CPoint3D a = (*p2 - *p1).Normalize ();
	  CPoint3D b = (*p3 - *p1).Normalize ();
	  CPoint3D Z = *p1 + b.Cross (a).Normalize ();

	  clonedAtom->SetAll (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSAZ);
	  insert_local (*clonedAtom);
	  delete clonedAtom;
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut(1) << "Residue " << *mType << "-" << resId
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
      pivot[0] = mAtomRef[0];
      pivot[1] = mAtomRef[1];
      pivot[2] = mAtomRef[2];
    }
  else
    return;

  // Fix res type
  // -- Si le type est déjà spécialisé, il n'y a aucun changement.
  if (ref (a_C2p))
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
	(*it)->Transform (theAlign);
    }
  
  isIdentity = mTfo.isIdentity ();

//   if (mAtomRes.capacity () > mAtomRes.size ())
//     {
//       cerr << "resizing atomres: " << mAtomRes.capacity () << " -> "
// 	   << mAtomRes.size () << endl;
//       mAtomRes.resize (mAtomRes.size ());
//     }
}



void
Residue::placeIt () const
{
  vector< CAtom* >::const_iterator refit;
  vector< CAtom* >::iterator resit;
  
  for (refit = mAtomRef.begin (), resit = mAtomRes.begin ();
       refit != mAtomRef.end ();
       ++refit, ++resit)
    {
      **resit = **refit;
      (*resit)->Transform (mTfo);
    }
  isPlaced = true;
}



const CAtom*
Residue::ref (t_Atom *t) const
{
  ResMap::const_iterator i = mAtomIndex.find (t);

  return i == mAtomIndex.end () ? 0 : mAtomRef[i->second];
}



const CAtom*
Residue::res (t_Atom *t) const
{
  ResMap::const_iterator i = mAtomIndex.find (t);

  if (i == mAtomIndex.end ())
    return 0;
  else if (isIdentity)
    return mAtomRef[i->second];
  else
    return &place (i->second);
}



void
Residue::insert_local (const CAtom &a)
{
  ResMap::iterator i = mAtomIndex.find (a.GetType ());
  
  if (i == mAtomIndex.end ())
    {
      mAtomIndex[a.GetType ()] = size ();
      mAtomRef.push_back (a.clone ());
      mAtomRes.push_back (a.clone ());
      mAtomRef.reserve (size ());
      mAtomRes.reserve (size ());
      i = mAtomIndex.find (a.GetType ());
    }
  else
    *mAtomRef[i->second] = a;
  if (isPlaced)
    {
      *mAtomRes[i->second] = *mAtomRef[i->second];
      mAtomRes[i->second]->Transform (mTfo);
    }
}


void
Residue::insert (const CAtom &a)
{
  ResMap::iterator i = mAtomIndex.find (a.GetType ());
  
  if (i == mAtomIndex.end ())
    {
      mAtomIndex[a.GetType ()] = size ();
      mAtomRef.push_back (a.clone ());
      mAtomRes.push_back (a.clone ());
      mAtomRef.reserve (size ());
      mAtomRes.reserve (size ());
      i = mAtomIndex.find (a.GetType ());  
    }
  else
    {
      *mAtomRef[i->second] = a;
    }

  // Transform the atom to the origin
  CTransfo theAlign (mTfo);
  theAlign.Inverse ();
  (*mAtomRef[i->second]).Transform (theAlign);

  if (isPlaced)
    {
      *mAtomRes[i->second] = a;
    }
}


Residue::iterator
Residue::erase (t_Atom *type)
{
  ResMap::iterator i = mAtomIndex.find (type);

  if (i != mAtomIndex.end ())
    {
      vector< CAtom* >::const_iterator cit;
      const t_Atom *next;
      size_type index;

      delete mAtomRef[i->second];
      mAtomRef.erase (mAtomRef.begin () + i->second);
      next = ++i == mAtomIndex.end () ? 0 : i->first;
      mAtomIndex.clear ();
      for (cit = mAtomRef.begin (), index = 0;
	   cit != mAtomRef.end ();
	   ++cit, ++index)
	mAtomIndex[(*cit)->GetType ()] = index;
      delete mAtomRes.back ();
      mAtomRes.pop_back ();
      mAtomRes.reserve (index);
      isPlaced = false;
      return find (next);
    }
  else
    return end ();
}



void
Residue::AtomCopy (const AbstractResidue &right)
{
  const Residue *resp = dynamic_cast< const Residue* > (&right);
  
  if (this != &right && resp)
    {
      const Residue &res = *resp;
      
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
	  *mAtomRef[i->second] = *res.mAtomRef[j->second];
	  *mAtomRes[i->second] = *res.mAtomRes[j->second];
	}
      isPlaced = res.isPlaced;
      isIdentity = res.isIdentity;
      mTfo = res.mTfo;
    }
}


void
Residue::AtomInit (const vector< CAtom >& newref)
{
  vector< CAtom >::const_iterator ait;
  // should filter with no_pse_lp_atom_set ?
  mAtomRef.clear ();
  for (ait = newref.begin (); ait != newref.end (); ++ait)
    mAtomRef.push_back (ait->clone ());
  init ();
}


void
Residue::AtomInit (const vector< CAtom* >& newref)
{
  // should filter with no_pse_lp_atom_set ?
  mAtomRef = newref;
  init ();
}


AbstractResidue*
Residue::select (t_Atom *at ...) const
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
  res = new Residue (mType, atom_vec, resId);
  return res;
}



AbstractResidue&
Residue::Transform (const CTransfo& tfo)
{
  mTfo = tfo * mTfo;
  isPlaced = false;
  isIdentity = mTfo.isIdentity ();
  return *this;
}



void
Residue::Align ()
{
  mTfo.SetIdentity ();
  isPlaced = false;
  isIdentity = true;
}



iBinstream&
Residue::read (iBinstream &ibs)
{
  vector< CAtom* >::size_type nb;
  vector< CAtom* > vec;

  mAtomRef.clear ();
  ibs >> resId >> mType >> nb;
  for (; nb > 0; --nb)
    {
      CAtom *atom = new CAtom ();

      ibs >> *atom;
      mAtomRef.push_back (atom);
    }
  init ();
  return ibs;
}



oBinstream&
Residue::write (oBinstream &obs) const
{
  list< Residue::const_iterator > atoms;
  list< Residue::const_iterator >::iterator ciit;
  Residue::const_iterator cit;
  
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
Residue::read (iPdbstream &ips)
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
	  mAtomRef.push_back (it->clone ());

//       if (mAtomRef.capacity () > mAtomRef.size ())
// 	{
// 	  cerr << "resizing atomref: " << mAtomRef.capacity () << " -> "
// 	       << mAtomRef.size () << endl;
// 	  mAtomRef.resize (mAtomRef.size ());
// 	}
      
      resId = ips.GetPrevResId ();
      mType = ips.GetPrevResType ();

      init ();
      ips.NewRes ();
    }
  return ips;
}



oPdbstream&
Residue::write (oPdbstream &ops) const
{
  const_iterator cit;

  ops.SetResType (mType);
  ops.SetResId (resId);
  for (cit = begin (); cit != end (); ++cit)
    ops << *cit;
  return ops;
}



ostream&
Residue::write (ostream &os) const
{
  const_iterator cit;

  os << *mType << '(' << resId
     << ") type=" << *mType << ":" << endl;
  for (cit = begin (); cit != end (); ++cit)
    os << *cit << endl;
  return os;
}



iBinstream&
operator>> (iBinstream &ibs, Residue &res)
{
  return res.read (ibs);
}



oBinstream&
operator<< (oBinstream &obs, const Residue &res)
{
  return res.write (obs);
}



iPdbstream&
operator>> (iPdbstream &ips, Residue &res)
{
  return res.read (ips);
}



oPdbstream&
operator<< (oPdbstream &ops, const Residue &res)
{
  return res.write (ops);
}



ostream&
operator<< (ostream &os, const Residue &res)
{
  return res.write (os);
}
