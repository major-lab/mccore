//                              -*- Mode: C++ -*- 
// CResidue.cc
// Copyright © 2000-02 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Philippe Thibault
// Last Modified On : Wed Mar 19 16:57:34 2003
// Update Count     : 35
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



void
CResidue::setIdeal ()
{
  erase (begin (), end ());
  
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
  }
  else {
    gOut (2) << "Oups, setIdeal erased the residue " << (const char*)*mType  
	     << " but the ideal confo is unknown.  Go get a coffee!" << endl;
  }

  Align ();
  init ();
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

	  insert_local (CAtom (Y.GetX (), Y.GetY (), Y.GetZ (), a_PSY));
	  insert_local (CAtom (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSZ));
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut (2) << "Residue " << *mType << "-" << resId
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

	  insert_local (CAtom (Z.GetX (), Z.GetY (), Z.GetZ (), a_PSAZ));
	}
      else
	{
	  // Create an invalid residue but keep it in misc residues.
	  gOut (2) << "Residue " << *mType << "-" << resId
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
	it->Transform (theAlign);
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
CResidue::insert_local (const CAtom &a)
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



void
CResidue::insert (const CAtom &a)
{
  ResMap::iterator i = mAtomIndex.find (a.GetType ());
  
  if (i == mAtomIndex.end ())
    {
      mAtomIndex[a.GetType ()] = size ();
      mAtomRef.push_back (a);
      mAtomRes.push_back (a);
      mAtomRes.reserve (size ());
      i = mAtomIndex.find (a.GetType ());  
    }
  else
    {
      mAtomRef[i->second] = a;
    }

  // Transform the atom to the origin
  CTransfo theAlign (mTfo);
  theAlign.Inverse ();
  mAtomRef[i->second].Transform (theAlign);

  if (isPlaced)
    {
      mAtomRes[i->second] = a;
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
	  CLibException exc ("Invalid residue type ");
	  
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


void
CResidue::AtomInit (const vector< CAtom >& newref)
{
  // should filter with no_pse_lp_atom_set ?
  mAtomRef = newref;
  init ();
}


void
CResidue::AtomInit (const vector< CAtom* >& newref)
{
  vector< CAtom* >::const_iterator ait;
  // should filter with no_pse_lp_atom_set ?
  mAtomRef.clear ();
  for (ait = newref.begin (); ait != newref.end (); ++ait)
    mAtomRef.push_back (**ait);
  init ();
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
  vector< CAtom >::const_iterator i;

  os << *mType << '(' << resId
     << ") type=" << *mType << ":" << endl;

  os << "REFERENTIAL atoms" << endl;
  for (i=mAtomRef.begin (); i!=mAtomRef.end (); ++i) {
    os << *i << endl;
  }
  os << (const CTransfo&)*this << endl;
  os << "PLACED atoms" << endl;
 for (cit = begin (); cit != end (); ++cit)
   os << *cit << endl;

  return os;
}



iBinstream&
operator>> (iBinstream &ibs, CResidue &res)
{
  return res.read (ibs);
}



oBinstream&
operator<< (oBinstream &obs, const CResidue &res)
{
  return res.write (obs);
}



iPdbstream&
operator>> (iPdbstream &ips, CResidue &res)
{
  return res.read (ips);
}



oPdbstream&
operator<< (oPdbstream &ops, const CResidue &res)
{
  return res.write (ops);
}



ostream&
operator<< (ostream &os, const CResidue &res)
{
  return res.write (os);
}
