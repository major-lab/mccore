//                              -*- Mode: C++ -*- 
// ExtendedResidue.cc
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.28 $
// $Id: ExtendedResidue.cc,v 1.28 2005-01-27 19:11:56 larosem Exp $
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

#include "Exception.h"
#include "ExtendedResidue.h"
#include "Messagestream.h"
#include "ResId.h"
#include "ResidueType.h"



namespace mccore
{
  
  Atom& 
  ExtendedResidue::_get (size_type pos) const 
  {
    _place ();
    return *atomGlobal[pos];
  }


  ExtendedResidue::ExtendedResidue (const ExtendedResidue &other)
    : Residue (other),
      tfo (other.tfo),
      placed (other.placed)
  {
    vector< Atom* >::const_iterator cit;
    
    for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
      {
	atomLocal.push_back ((*cit)->clone ());
      }
  }


  ExtendedResidue::~ExtendedResidue ()
  {
    vector< Atom* >::iterator it;

    for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
      {
	delete *it;
      }
  }

  
  ExtendedResidue& 
  ExtendedResidue::operator= (const ExtendedResidue &other)
  {
    if (this != &other)
      {
	vector< Atom* >::iterator it;
	vector< Atom* >::const_iterator cit;

	Residue::operator= (other);
	for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
	  {
	    delete *it;
	  }
	atomLocal.clear ();
	for (cit = other.atomLocal.begin (); cit != other.atomLocal.end (); ++cit)
	  {
	    atomLocal.push_back ((*cit)->clone ());
	  }
	tfo = other.tfo;
	placed = other.placed;
      }
    return *this;
  }


  void
  ExtendedResidue::setReferential (const HomogeneousTransfo& m)
  {
    tfo = m;
    //       _displace ();
    placed = false;
  }
  
  
  void 
  ExtendedResidue::insert (const Atom &atom)
  {
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (atom.getType (), pos));

    if (inserted.second)
      {
	atomGlobal.push_back (atom.clone ());
	atomLocal.push_back (atom.clone ());
	rib_dirty_ref = true;
      }
    else
      {
	*atomGlobal[inserted.first->second] = atom;
	*atomLocal[inserted.first->second] = atom;
      }

    if (! tfo.isIdentity ())
      {
	atomLocal[inserted.first->second]->transform (tfo.invert ());
      }
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const iterator& rit)
  { 
    if (end () != rit)
    {
      vector< Atom* >::iterator avit;
      vector< Atom* >::const_iterator cavit;
      const AtomType* next = 0;
      size_type index = 0;
      iterator next_rit = rit + 1;

      // invalidate ribose pointers
      rib_dirty_ref = true;
      
      // get next atom type before deletion
      if (end () != next_rit)
	next = next_rit.pos->first;
      
      // delete atom
      avit = atomGlobal.begin () + rit.pos->second;
      delete *avit;
      atomGlobal.erase (avit);
      avit = atomLocal.begin () + rit.pos->second;
      delete *avit;
      atomLocal.erase (avit);

      // fix atom map
      atomIndex.clear ();
      for (cavit = atomGlobal.begin (); cavit != atomGlobal.end (); ++cavit, ++index)
	atomIndex.insert (make_pair ((*cavit)->getType (), index));

      if (next)
      {
	// fetch iterator to saved atom type and set its filter.
	next_rit = find (next);
	delete next_rit.filter;
	next_rit.filter = rit.filter->clone ();
	return next_rit;
      }
    }
    return end ();  
  }


  void 
  ExtendedResidue::clear ()
  {
    vector< Atom* >::iterator it;

    for (it = atomLocal.begin (); it != atomLocal.end (); ++it)
      {
	delete *it;
      }
    atomLocal.clear ();
    tfo.setIdentity ();
    Residue::clear ();
  }

  
  void
  ExtendedResidue::finalize ()
  {
    unsigned int i;

    // set pseudo-atoms
    Residue::finalize ();

    // set referential
    tfo = _compute_referential ();

    // set local atoms in referential's origin
    HomogeneousTransfo inv (tfo.invert ());
    
    for (i = 0; i < atomLocal.size (); ++i)
      {
	*atomLocal[i] = *atomGlobal[i];
	atomLocal[i]->transform (inv);
      }
  }

  
  void ExtendedResidue::atomCopy (const Residue& other) 
  {
    const ExtendedResidue *resp = dynamic_cast< const ExtendedResidue* > (&other);
    unsigned int i;

    if (this != &other && resp)
      {
	if (type != resp->getType ())
	  {
	    LibException exc ("Invalid residue type ");
	
	    exc << *resp->getType () << ".";
	    throw exc;
	  }
      
	for (i = 0; i < atomLocal.size (); ++i)
	  {
	    *atomLocal[i] = *resp->atomLocal[i];
	    *atomGlobal[i] = *resp->atomGlobal[i];
	  }

	placed = true;
	tfo = resp->tfo;      
      }
    else
      {
	if (this != &other)
	  {
	    if (type != other.getType ())
	      {
		LibException exc ("Invalid residue type ");
	  
		exc << *other.getType () << ".";
		throw exc;
	      }
	
	    tfo = other.getReferential ();
	    placed = true;

	    HomogeneousTransfo tfoi = tfo.invert ();
	    for (i = 0; i < atomLocal.size (); ++i)
	      {
		*atomGlobal[i] = *(other.atomGlobal[i]);
		*atomLocal[i] = *(other.atomGlobal[i]);
		atomLocal[i]->transform (tfoi);
	      }
	
	  } 
      }
  }


  Atom*
  ExtendedResidue::_get_or_create (const AtomType *aType)
  {
    // ribose pointers to local container!
    
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
      {
	atomLocal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	rib_dirty_ref = true;
	return atomGlobal[pos];
      }
    else
      {
	return atomGlobal[inserted.first->second];
      }
  }

  
  void
  ExtendedResidue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
					      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential

    // TODO: place only ribose atoms...
    placed = false;
    _place (); // -> place all atoms :(
    _add_ribose_hydrogens (true);
  }
  
  
  void
  ExtendedResidue::_place () const
  {
    if (false == placed)
    {
      vector< Atom* >::const_iterator cit;
      vector< Atom* >::iterator it;
    
      for (cit = atomLocal.begin (), it = atomGlobal.begin ();
	   cit != atomLocal.end ();
	   ++cit, ++it)
	{
	  **it = **cit;
	  (*it)->transform (tfo);
	}      
      placed = true;
    }
  }

  
//   void
//   ExtendedResidue::_displace () const
//   {
//     placed = false;
//     _place ();
//   }

}
