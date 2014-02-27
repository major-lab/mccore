//                              -*- Mode: C++ -*- 
// ExtendedResidue.cc
// Copyright © 2001-05 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Oct  9 15:58:22 2001
// $Revision: 1.34 $
// $Id: ExtendedResidue.cc,v 1.34 2006-05-15 17:56:21 thibaup Exp $
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


// cmake generated defines
#include <config.h>

#include "ExtendedResidue.h"

#include "AtomFactoryMethod.h"
#include "Exception.h"
#include "Messagestream.h"
#include "ResId.h"
#include "ResidueType.h"

#define DEBUG 1


namespace mccore
{
  // LIFECYCLE ---------------------------------------------------------------

  ExtendedResidue::ExtendedResidue (const ResidueType *t, const ResId &i, vector< Atom > &vec, const AtomFactoryMethod *fm)
      : Residue (t, i, vec, fm),
	placed (true)
  {
    vector< Atom* >::const_iterator cit;
    
    for (this->atomGlobal.begin (); cit != this->atomGlobal.end (); ++cit)
    {
      this->atomLocal.push_back (mpAtomFM->createAtom(*(*cit)));
    }
  }


  ExtendedResidue::ExtendedResidue (const ExtendedResidue& exres, const AtomFactoryMethod *fm)
    : Residue (exres, fm),
      referential (exres.referential),
      placed (exres.placed)
  {
    // global atoms are set in base class Residue.

    vector< Atom* >::iterator cit;

    this->atomLocal = exres.atomLocal;

    // harden atoms
    for (cit = this->atomLocal.begin (); cit != this->atomLocal.end (); ++cit)
    {
      *cit = mpAtomFM->createAtom(*(*cit));
    }
  }


  ExtendedResidue::ExtendedResidue (const Residue& res, const AtomFactoryMethod *fm)
    : Residue (res, fm)
  {
    const ExtendedResidue* vptr = dynamic_cast< const ExtendedResidue* > (&res);

    if (0 == vptr)
    {
      // -- default init for ExtendedResidue members

      vector< Atom* >::const_iterator cit;

      for (cit = this->atomGlobal.begin (); cit != this->atomGlobal.end (); ++cit)
	this->atomLocal.push_back (mpAtomFM->createAtom(*(*cit)));

      this->placed = true; // because referential is identity
    }
    else
      this->ExtendedResidue::_assign (*vptr);
  }


  ExtendedResidue::~ExtendedResidue ()
  {
    vector< Atom* >::iterator it;

    for (it = this->atomLocal.begin (); it != this->atomLocal.end (); ++it)
    {
      delete *it;
    }
  }

  // VIRTUAL ASSIGNATION --------------------------------------------------

  ExtendedResidue&
  ExtendedResidue::assignNV (const Residue& res)
  {
    if (this != &res)
    {
      const ExtendedResidue* vptr = dynamic_cast< const ExtendedResidue* > (&res);

      this->Residue::_assign (res);

      if (0 == vptr)
      {
	// -- fix local atoms with new globals, referential becomes identity

	vector< Atom* >::const_iterator cit;

	this->atomLocal.clear ();

	for (cit = this->atomGlobal.begin (); cit != this->atomGlobal.end (); ++cit)
	{
	  this->atomLocal.push_back (mpAtomFM->createAtom(*(*cit)));
	}

	this->referential.setIdentity ();
	this->placed = true;
      }
      else
	this->ExtendedResidue::_assign (*vptr);
    }
    return *this;
  }


  void 
  ExtendedResidue::_assign (const ExtendedResidue& exres)
  {
    vector< Atom* >::iterator it;
    vector< Atom* >::const_iterator cit;

    this->atomLocal.clear ();

    for (cit = exres.atomLocal.begin (); cit != exres.atomLocal.end (); ++cit)
    {
      this->atomLocal.push_back (mpAtomFM->createAtom(*(*cit)));
    }

    this->referential = exres.referential;
    this->placed = exres.placed;
  }

  // OPERATORS ------------------------------------------------------------
  
  ExtendedResidue& 
  ExtendedResidue::operator= (const ExtendedResidue& exres)
  {
    if (this != &exres)
    {
      this->Residue::_assign (exres);
      this->ExtendedResidue::_assign (exres);
    }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------
  
  // METHODS ---------------------------------------------------------------

  void
  ExtendedResidue::setReferential (const HomogeneousTransfo& m)
  {
    this->referential = m;
    this->placed = false;
  }


  void
  ExtendedResidue::transform (const HomogeneousTransfo& m)
  {
    this->referential = m * this->referential;
    this->placed = false;
  }

  
  void 
  ExtendedResidue::insert (const Atom &atom)
  {
    int pos = size ();
    pair< AtomMap::iterator, bool > inserted =
      atomIndex.insert (make_pair (atom.getType (), pos));

    if (inserted.second)
      {
	atomGlobal.push_back (mpAtomFM->createAtom(atom));
	atomLocal.push_back (mpAtomFM->createAtom(atom));
	rib_dirty_ref = true;
      }
    else
      {
    	delete atomGlobal[inserted.first->second];
    	delete atomLocal[inserted.first->second];
    	atomGlobal[inserted.first->second] = mpAtomFM->createAtom(atom);
    	atomLocal[inserted.first->second] = mpAtomFM->createAtom(atom);
      }

    atomLocal[inserted.first->second]->transform (referential.invert ());
  }


  ExtendedResidue::iterator 
  ExtendedResidue::erase (const iterator& rit)
  { 
    if (this->end () != rit)
    {
      vector< Atom* >::iterator avit;
      vector< Atom* >::const_iterator cavit;
      AtomMap::iterator next_position;
      const AtomType* atype = 0;
      size_type index = 0;

      // -- invalidate ribose pointers
      this->rib_dirty_ref = true;
      
      // -- get type for the following atom.
      iterator nrit = rit + 1;
      if (this->end () != nrit)
	atype = nrit.pos->first;
      
      // -- delete the indexed atom
      avit = this->atomGlobal.begin () + rit.pos->second;
      delete *avit;
      this->atomGlobal.erase (avit);
      avit = this->atomLocal.begin () + rit.pos->second;
      delete *avit;
      this->atomLocal.erase (avit);

      // -- recreate the atom index
      this->atomIndex.clear ();
      for (cavit = this->atomGlobal.begin (); cavit != this->atomGlobal.end (); ++cavit)
	this->atomIndex.insert (make_pair ((*cavit)->getType (), index++));

      if (atype)
      {
	// -- retrieve the appropriate iterator following the deletion point.
	if (this->atomIndex.end () == (next_position = this->atomIndex.find (atype)))
	{
	  FatalIntLibException ex ("", __FILE__, __LINE__);
	  ex << "failed to erase atom " << rit.pos->first << " from " << *this;
	  throw ex;
	}
	iterator next_rit (this, next_position, *rit.filter);
	return next_rit;
      }
    }
    return this->end ();  
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
    referential.setIdentity ();
    Residue::clear ();
  }

  
  void
  ExtendedResidue::finalize ()
  {
    unsigned int i;

    // set pseudo-atoms
    this->Residue::finalize ();

    // set referential
    this->referential = this->_compute_referential ();

    // set local atoms in referential's origin
    HomogeneousTransfo inv = this->referential.invert ();
    
    for (i = 0; i < atomLocal.size (); ++i)
    {
      *this->atomLocal[i] = *this->atomGlobal[i];
      this->atomLocal[i]->transform (inv);
    }

    this->placed = true;
  }


  Atom& 
  ExtendedResidue::_get (size_type pos) const 
  {
    _place ();
    return *atomGlobal[pos];
  }


  Atom*
  ExtendedResidue::_get_or_create (const AtomType *aType)
  {
    // ribose pointers to local container!
    
    size_type pos = this->size ();
    pair< AtomMap::iterator, bool > inserted =
      this->atomIndex.insert (make_pair (aType, pos));

    if (inserted.second)
      {
	this->atomLocal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	this->atomGlobal.push_back (new Atom (0.0, 0.0, 0.0, aType));
	this->rib_dirty_ref = true;
	return this->atomLocal[pos];
      }
    else
      {
	return this->atomLocal[inserted.first->second];
      }
  }

  
  void
  ExtendedResidue::_build_ribose_postprocess (const HomogeneousTransfo& referential,
					      bool build5p, bool build3p)
  {
    // place built ribose's atoms back in referential

    // TODO: place only ribose atoms...
    this->placed = false;
    this->_place (); // -> place all atoms :-(
    this->_add_ribose_hydrogens (true);
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
	  (*it)->transform (referential);
	}      
      placed = true;
    }
  }


  ostream&
  ExtendedResidue::display (ostream& os) const
  {
    return this->_display (os << "### ExtendedResidue status ###" << endl) << "### end ###" << endl;
  }


  ostream&
  ExtendedResidue::_display (ostream& os) const
  {
    vector< Atom* >::const_iterator ait;
 
    this->Residue::_display (os);
    os << endl
       << "# placed?: " << this->placed << endl
       << "# referential: " << endl << this->referential << endl
       << "# local atoms: " << this->atomLocal.size () << endl;

    for (ait = this->atomLocal.begin (); ait != atomLocal.end (); ++ait)
    {
      os << "\t";
      os.width (3);
      os.setf (ios::right);
      os << (ait - this->atomLocal.begin ()) << ": " << **ait << endl;
    }

    return os;
  }

}
