//                              -*- Mode: C++ -*- 
// PairingPattern.cc
// Copyright � 2001-06 Laboratoire de Biologie Informatique et Th�orique.
//                     Universit� de Montr�al
// Author           : Patrick Gendron
// Created On       : Thu May 31 08:17:56 2001
// $Revision: 1.16 $
// $Id: PairingPattern.cc,v 1.16 2006-05-02 20:54:08 larosem Exp $
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

#include <algorithm>

#include "PairingPattern.h"

#include "AtomType.h"
#include "Messagestream.h"
#include "PropertyType.h"
#include "Residue.h"
#include "ResidueType.h"
#include "stlio.h"



namespace mccore
{

  list< PairingPattern > PairingPattern::patterns;
  bool PairingPattern::isInit = false;


  const PairingPattern&
  PairingPattern::operator= (const PairingPattern &other)
  {
    if (this != &other)
      {
	name = other.name;
	typeA = other.typeA;
	typeB = other.typeB;
	AtoB = other.AtoB;
	BtoA = other.BtoA;
	msize = other.msize;
	baseOrientation = other.baseOrientation;
      }
    return *this;
  }


  void 
  PairingPattern::addBond (vector< Description > &desc, const AtomType* donor, const AtomType* hydro, const AtomType* acceptor, const AtomType* lonepair, bool ignore)
  {
    HBond hb (donor, hydro, acceptor, lonepair);
    
    desc.push_back (Description (ignore, hb));
    if (! ignore)
      {
	msize++;
      }
  }


  bool
  PairingPattern::match (list< HBondFlow > &hbf, const vector< Description > &desc, const Residue *rA, char direction) const
  {
    bool matches = true;
    vector< Description >::const_iterator descIt;
    
    for (descIt = desc.begin (); desc.end () != descIt; ++descIt)
      {
	gOut (5) << direction << descIt->hbond << "   " << flush;
	if (! descIt->ignored)
	  {
	    list< HBondFlow >::reverse_iterator k;
	    bool found = false;
		
	    for (k = hbf.rbegin (); k != hbf.rend (); ++k)
	      {
		if (k->hbond.getDonorResidue () == rA
		    && descIt->hbond == k->hbond)
		  {
		    found = true;
		    gOut (5) << "found " << endl
			     << direction << k->hbond << " " << k->flow << endl;
		    break;
		  }
	      }
	    if (! found)
	      {
		matches = false;
		gOut (5) << "not found " << endl;
		break;
	      }
	  }
      }
    return matches;
  }
  

  const PropertyType*
  PairingPattern::evaluate (const Residue *ra, const Residue *rb, const PropertyType *bpori, list< HBondFlow > &hbf) const
  {
    const PropertyType *result = 0;
    
    if (! ra->getType ()->is (typeA))
      {
	swap (ra, rb);
      }
    gOut (5) << "Testing " << *this
	     << "  with " << *ra->getType () << " " << *rb->getType ()
	     << " " << *bpori << endl;
    if (ra->getType ()->is (typeA)
	&& rb->getType ()->is (typeB)
	&& bpori == baseOrientation)
      {
	bool res;

	hbf.sort ();
	res = match (hbf, AtoB, ra, '>');
	if (! res && typeA == typeB)
	  {
	    swap (ra, rb);
	    res = match (hbf, AtoB, ra, '>');
	  }
	if (res)
	  {
	    res = match (hbf, BtoA, rb, '<');
	  }
	if (res)
	  {
	    result = name;
	  }
	gOut (5) << (result ? (const char*) *result : "none") << endl;
      }
    return result;
  }


  void PairingPattern::init ()
  {
    PairingPattern pat;
 
    pat = PairingPattern (PropertyType::pXIX, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3, true); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXX, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pI, ResidueType::rA, ResidueType::rA, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    pat.addBond (pat.getBtoA (), AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pII, ResidueType::rA, ResidueType::rA, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getBtoA (), AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIII, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIV, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pV, ResidueType::rA, ResidueType::rA, PropertyType::pAntiparallel);     
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getBtoA (), AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVI, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7, true); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVII, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6); 
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6, true); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVIII, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aN1, AtomType::aLP1); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIX, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pX, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);     
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXI, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXII, ResidueType::rU, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXIII, ResidueType::rU, ResidueType::rU, PropertyType::pParallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXIV, ResidueType::rC, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true);
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXV, ResidueType::rC, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true); 
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVI, ResidueType::rU, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVII, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVIII, ResidueType::rC, ResidueType::rU, PropertyType::pAntiparallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);  
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXI, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXII, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);   
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true); 
    pat.addBond (pat.getBtoA (), AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXIII, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXIV, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXV, ResidueType::rA, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2, true); 
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVI, ResidueType::rA, ResidueType::rC, PropertyType::pParallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond (pat.getBtoA (), AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1); 
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVII, ResidueType::rG, ResidueType::rU, PropertyType::pParallel);   
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4, true); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVIII, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p29, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p30, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p31, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p32, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p33, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p34, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);
  
    pat = PairingPattern (PropertyType::p35, ResidueType::rA, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p36, ResidueType::rA, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p37, ResidueType::rA, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p38, ResidueType::rA, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p39, ResidueType::rA, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p40, ResidueType::rA, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p41, ResidueType::rA, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p42, ResidueType::rU, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p43, ResidueType::rU, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p44, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p45, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p46, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p47, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p48, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p49, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p50, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p51, ResidueType::rA, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p52, ResidueType::rA, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p53, ResidueType::rG, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p54, ResidueType::rG, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p55, ResidueType::rG, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p56, ResidueType::rG, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p57, ResidueType::rG, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p58, ResidueType::rG, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p59, ResidueType::rG, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p60, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p61, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p62, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p63, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p64, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p65, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p66, ResidueType::rA, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p67, ResidueType::rA, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p68, ResidueType::rC, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p69, ResidueType::rC, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p70, ResidueType::rC, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p71, ResidueType::rC, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p72, ResidueType::rC, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p73, ResidueType::rC, ResidueType::rA, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p74, ResidueType::rC, ResidueType::rA, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p75, ResidueType::rA, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p76, ResidueType::rA, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p77, ResidueType::rA, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p78, ResidueType::rA, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p79, ResidueType::rA, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p80, ResidueType::rA, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p81, ResidueType::rU, ResidueType::rU, PropertyType::pAntiparallel);
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    
    pat = PairingPattern (PropertyType::p82, ResidueType::rU, ResidueType::rU, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    
    pat = PairingPattern (PropertyType::p83, ResidueType::rG, ResidueType::rU, PropertyType::pParallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p84, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p85, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel);
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p86, ResidueType::rG, ResidueType::rU, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p87, ResidueType::rG, ResidueType::rU, PropertyType::pParallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p88, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p89, ResidueType::rG, ResidueType::rU, PropertyType::pParallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p90, ResidueType::rG, ResidueType::rU, PropertyType::pParallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p91, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p92, ResidueType::rG, ResidueType::rU, PropertyType::pParallel);  
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p93, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond (pat.getBtoA (), AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p94, ResidueType::rG, ResidueType::rU, PropertyType::pAntiparallel); 
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p95, ResidueType::rU, ResidueType::rG, PropertyType::pAntiparallel);
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    
    pat = PairingPattern (PropertyType::p96, ResidueType::rU, ResidueType::rG, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    
    pat = PairingPattern (PropertyType::p97, ResidueType::rC, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p98, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p99, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p100, ResidueType::rC, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p101, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p102, ResidueType::rC, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p103, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p104, ResidueType::rC, ResidueType::rU, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p105, ResidueType::rC, ResidueType::rU, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p106, ResidueType::rU, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p108, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p109, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p110, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p111, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p112, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p113, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p114, ResidueType::rG, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p115, ResidueType::rG, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p116, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p117, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p118, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p119, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p120, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p121, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p122, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p123, ResidueType::rC, ResidueType::rG, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p124, ResidueType::rC, ResidueType::rG, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p125, ResidueType::rG, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p126, ResidueType::rG, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p127, ResidueType::rG, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p128, ResidueType::rG, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p129, ResidueType::rG, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p130, ResidueType::rG, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p131, ResidueType::rC, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p132, ResidueType::rC, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p133, ResidueType::rC, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p134, ResidueType::rC, ResidueType::rC, PropertyType::pParallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p135, ResidueType::rC, ResidueType::rC, PropertyType::pAntiparallel);
    pat.addBond (pat.getAtoB (), AtomType::aC5, AtomType::aH5, AtomType::aN3, AtomType::aLP3); 
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p136, ResidueType::rC, ResidueType::rC, PropertyType::pParallel);
    pat.addBond (pat.getAtoB (), AtomType::aC5, AtomType::aH5, AtomType::aN3, AtomType::aLP3); 
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p137, ResidueType::rC, ResidueType::rC, PropertyType::pAntiparallel);    
    pat.addBond (pat.getAtoB (), AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

  };
  
  
  ostream& 
  PairingPattern::output (ostream &os) const
  {
    vector< Description >::const_iterator it;
    
    os << name << ": " << *typeA << " " << *typeB << " " << *baseOrientation
       << endl;
    for (it = AtoB.begin (); AtoB.end () != it; ++it)
      {
	os << (it->ignored ? "! > " : "  > ") << it->hbond << endl;
      }
    for (it = BtoA.begin (); BtoA.end () != it; ++it)
      {
	os << (it->ignored ? "! < " : "  < ") << it->hbond << endl;
      }
    return os;
  }
  
}



namespace std
{
  
  ostream&
  operator<< (ostream &os, const mccore::PairingPattern &pat)
  {
    return pat.output (os);
  }

}
