//                              -*- Mode: C++ -*- 
// Model.cc
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Oct 10 15:34:08 2001
// $Revision: 1.16 $
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

#include <list>

#include "Model.h"

#include "Binstream.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"
#include "Pdbstream.h"


namespace mccore {


  bool less_deref (Residue *x, Residue *y)
  {
    return *x < *y;
  }

  
  // LIFECYCLE -----------------------------------------------------------------

  
  Model::Model (ResidueFactoryMethod *fm)
  {
    residueFM = (fm == 0) ? new ExtendedResidueFM () : fm;
  }


  
  Model::Model (const Model &right)
  {
    const_iterator cit;
    
    residueFM = right.residueFM->clone ();
    for (cit = right.begin (); cit != right.end (); ++cit)
      insert (*cit);
  }



  Model::~Model ()
  {
    delete residueFM;
    clear ();
  }


  // OPERATORS -----------------------------------------------------------------


  Model&
  Model::operator= (const Model &right)
  {
    if (this != &right)
      {
	iterator it;
	const_iterator cit;

	delete residueFM;
	residueFM = right.residueFM->clone ();
	for (it = begin (); it != end (); ++it)
	  delete &*it;
	clear ();

	for (cit = right.begin (); cit != right.end (); ++cit)
	  insert (*cit);
      }
    return *this;
  }



  Residue&
  Model::operator[] (size_type nth)
  {
    if (nth > size ())
      return *end ();
    else
      {
	iterator it;
      
	for (it = begin (); nth > 0; --nth, ++it);
	return *it;
      }
  }



  const Residue&
  Model::operator[] (size_type nth) const
  {
    if (nth > size ())
      return *end ();
    else
      {
	const_iterator cit;
      
	for (cit = begin (); nth > 0; --nth, ++cit);
	return *cit;
      }
  }


  // ACCESS --------------------------------------------------------------------


  void
  Model::setResidueFM (ResidueFactoryMethod *fm)
  {
    delete residueFM;
    residueFM = fm;
  }


  // METHODS -------------------------------------------------------------------


//   Residue::iterator
//   Model::find (const char *str)
//   {
//     char *s = strdup (str);
//     char *p = s;
//     char *argum;
//     vector< char* > tok;
//     Model::iterator mit;
//     Residue::iterator it;
  
//     argum = strsep (&p, ":");
//     while (argum)
//       {
// 	if (strlen (argum) > 0) 
// 	  tok.push_back (argum);
// 	argum = strsep (&p, ":");
//       }

//     if (tok.size () != 2
// 	|| (mit = find (CResId (tok[0]))) == end ()
// 	|| (it = mit->find (iPdbstream::GetAtomType (tok[1]))) == mit->end ())
//       it = Residue::iterator ();
//     delete[] s;
//     return it;
//   }



//   Residue::const_iterator
//   Model::find (const char *str) const
//   {
//     char *s = strdup (str);
//     char *p = s;
//     char *argum;
//     vector< char* > tok;
//     Model::const_iterator mit;
//     Residue::const_iterator it;
  
//     argum = strsep (&p, ":");
//     while (argum)
//       {
// 	if (strlen (argum) > 0) 
// 	  tok.push_back (argum);
// 	argum = strsep (&p, ":");
//       }

//     if (tok.size () != 2
// 	|| (mit = find (CResId (tok[0]))) == end ()
// 	|| (it = mit->find (iPdbstream::GetAtomType (tok[1]))) == mit->end ())
//       it = Residue::const_iterator ();
//     delete[] s;
//     return it;
//   }



  Model::iterator
  Model::find (const ResId &id)
  {
    iterator it;

    for (it = begin (); it != end (); ++it)
      if (id == it->getResId ())
	break;
    return it;
  }


  Model::const_iterator
  Model::find (const ResId &id) const
  {
    const_iterator it;

    for (it = begin (); it != end (); ++it)
      if (id == it->getResId ())
	break;
    return it;
  }


  void
  Model::sort ()
  {
    residues.sort (less_deref);
  }

  
  Model::size_type
  Model::size () const
  {
    return residues.size ();
  }


  bool
  Model::empty () const
  {
    return residues.empty ();
  }


  void 
  Model::clear()
  {
    iterator it;

    for (it = begin (); it != end (); ++it)
      delete &*it;
    residues.clear ();    
  }


  void
  Model::validate ()
  {
    iterator it = begin ();

    while (it != end ())
      {
	it->validate ();
	if (it->getType ()->isNucleicAcid ()
	    || it->getType ()->isAminoAcid ())
	  ++it;
	else
	  {
	    delete &*it;
	    it = erase (it);
	  }
      }
  }



  void
  Model::removeOptionals ()
  {
    iterator it;

    for (it = begin (); it != end (); ++it)
      it->removeOptionals ();
  }



  void
  Model::removeAminoAcid ()
  {
    iterator modelIt = begin ();

    while (modelIt != end ())
      {
	if (modelIt->getType ()->isAminoAcid ())
	  {
	    delete &*modelIt;
	    modelIt = erase (modelIt);
	  }
	else
	  ++modelIt;
      }
  }



  void
  Model::removeNucleicAcid ()
  {
    iterator modelIt;

    for (modelIt = begin (); modelIt != end ();)
      {
	if (modelIt->getType ()->isNucleicAcid ())
	  {
	    delete &*modelIt;
	    modelIt = erase (modelIt);
	  }
	else
	  ++modelIt;
      }
  }



  void
  Model::keepAminoAcid ()
  {
    iterator modelIt;

    for (modelIt = begin (); modelIt != end ();)
      {
	if (modelIt->getType ()->isAminoAcid ())
	  ++modelIt;
	else
	  {
	    delete &*modelIt;
	    modelIt = erase (modelIt);
	  }
      }
  }



  void
  Model::keepNucleicAcid ()
  {
    iterator modelIt;

    for (modelIt = begin (); modelIt != end ();)
      {
	if (modelIt->getType ()->isNucleicAcid ())
	  ++modelIt;
	else
	  {
	    delete &*modelIt;
	    modelIt = erase (modelIt);
	  }
      }
  }



//   void 
//   Model::removeClashes ()
//   {
//     iterator i, j;
//     vector< pair< iterator, iterator > > possibleContacts;
//     vector< pair< iterator, iterator > >::iterator m;

//     possibleContacts = 
//       Algo::ExtractContact_AABB (begin (), end (), 2.0);

//     Residue::iterator k, l;

//     set< iterator > toremove;
//     set< iterator >::iterator t;

//     for (m=possibleContacts.begin (); m!=possibleContacts.end (); ++m)
//       {
// 	i = m->first;
// 	j = m->second;

// 	if (*(i->begin ()) | *(j->end ()) < 3.0) {
// 	  bool clash = false;
// 	  for (k=i->begin (new atomset_and (new no_pse_lp_atom_set (),
// 					    new no_hydrogen_set ())); 
// 	       k!=i->end (); ++k) {
// 	    for (l=j->begin (new atomset_and (new no_pse_lp_atom_set (),
// 					      new no_hydrogen_set ())); 
// 		 l!=j->end (); ++l) {
// 	      if ((*k | *l) < 0.8) {
// 		clash=true;
// 		break;
// 	      }
// 	    }
// 	    if (clash) break;
// 	  }
// 	  if (clash) {
// 	    gOut (3) << "Rejecting " << (CResId&)*j
// 		     << " because of clashes with " << (CResId&)*i << endl;
// 	    toremove.insert (j);
// 	  }
// 	}
//       }

//     for (t=toremove.begin (); t!=toremove.end (); ++t) {    
//       delete &**t;
//       erase (*t);
//     }  
//   }


  // I/O -----------------------------------------------------------------------


  ostream& 
  Model::output (ostream &os) const
  {
    const_iterator cit;
    
    os << "MODEL :" << flush;
    for (cit = begin (); cit != end (); ++cit)
      os << cit->getResId ()  << " ";
    return os;
  }
  
  
  
  oPdbstream& 
  Model::output (oPdbstream &ops) const
  {
    const_iterator cit;
    char chainId;

    cit = begin ();
    chainId = cit->getResId ().getChainId ();
    for (; cit != end (); ++cit)
      {
	if (cit->getResId ().getChainId () != chainId)
	  {
	    ops.ter ();
	    chainId = cit->getResId ().getChainId ();
	  }
	ops << *cit;
      }
    ops.ter ();
    return ops;
  }
  
  
  iPdbstream& 
  Model::input (iPdbstream &ips)
  {
    clear ();
    int currNb = ips.getModelNb ();
    
    while (! (ips.eof ()) && currNb == ips.getModelNb () )
      {
	Residue *res = getResidueFM ()->createResidue ();
	
	ips >> *res;
	
 	if (res->size () != 0) {
	  // Optimized insertion that bypasses the copy: 
 	  residues.push_back (res); 
	} else
	  delete res;
      }    
    return ips;
  }


  oBinstream& 
  Model::output (oBinstream &obs) const
  {
    const_iterator cit;
    
    obs << size ();
    for (cit = begin (); cit != end (); ++cit)
      obs << *cit;
    return obs;
  }


  iBinstream& 
  Model::input (iBinstream &ibs)
  {
    clear ();
    
    Model::size_type sz;
    
    ibs >> sz;
    for (; sz > 0; --sz)
      {
	Residue *res = getResidueFM ()->createResidue ();
	
	ibs >> *res;
	// Optimized insertion that bypasses the copy: 
	residues.push_back (res); 
      }
    return ibs;
  }
  

  // ITERATORS -------------------------------------------------------------------


  unsigned int
  Model::model_iterator::operator- (const Model::model_iterator &right) const
  {
    model_iterator it = *this;
    unsigned int dist = 0;

    while (it != right)
      {
	--it;
	++dist;
      }
    return dist;
  }


  unsigned int
  Model::model_const_iterator::operator- (const Model::model_const_iterator &right) const
  {
    model_const_iterator it = *this;
    unsigned int dist = 0;

    while (it != right)
      {
	--it;
	++dist;
      }
    return dist;
  }


  // NON-MEMBER FUNCTIONS ------------------------------------------------------

  ostream&
  operator<< (ostream &os, const Model &obj)
  {
    return obj.output (os);
  }


 
  iPdbstream&
  operator>> (iPdbstream &ips, Model &obj)
  {
    return obj.input (ips);
  }



  oPdbstream&
  operator<< (oPdbstream &ops, const Model &obj)
  {
    return obj.output (ops);
  }



  iBinstream&
  operator>> (iBinstream &ibs, Model &obj)
  {
    return obj.input (ibs);
  }



  oBinstream&
  operator<< (oBinstream &obs, const Model &obj)
  {
    return obj.output (obs);
  }



  bool
  operator< (const Model::iterator &left, const Model::iterator &right)
  {
    return *left < *right;
  }



  bool
  operator< (const Model::const_iterator &left, const Model::const_iterator &right)
  {
    return *left < *right;
  }

}
