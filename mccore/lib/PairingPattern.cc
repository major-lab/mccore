//                              -*- Mode: C++ -*- 
// PairingPattern.cc
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Thu May 31 08:17:56 2001
// $Revision: 1.7 $
// $Id: PairingPattern.cc,v 1.7 2004-09-15 22:37:59 larosem Exp $


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <algorithm>

#include "Messagestream.h"
#include "PairingPattern.h"
#include "stlio.h"



namespace mccore {

  list< PairingPattern > PairingPattern::patterns;
  bool PairingPattern::isInit = false;


  PairingPattern::PairingPattern ()
    : name (0), typeA (0), typeB (0), msize (0)
  { }


  PairingPattern::PairingPattern (const PropertyType* id, const ResidueType* type_a, const ResidueType* type_b)
    : name (id), typeA (type_a), typeB (type_b), msize (0)
  { }


  PairingPattern::PairingPattern (const PairingPattern &other)
    : name (other.name),
      typeA (other.typeA),
      typeB (other.typeB),
      descriptions (other.descriptions),
      msize (other.msize)
  { }


  PairingPattern::~PairingPattern ()
  { }


  const PairingPattern&
  PairingPattern::operator= (const PairingPattern &other)
  {
    if (this != &other)
      {
	name = other.name;
	typeA = other.typeA;
	typeB = other.typeB;
	descriptions = other.descriptions;
	msize = other.msize;
      }
    return *this;
  }


  void 
  PairingPattern::addBond (char dir, const AtomType* donor, const AtomType* hydro, const AtomType* acceptor, const AtomType* lonepair, bool ignore)
  {
    HBond hb (donor, hydro, acceptor, lonepair);
    
    descriptions.push_back (Description (ignore, dir, hb));
    if (! ignore)
      msize++;
  }


  const PropertyType*
  PairingPattern::evaluate (const Residue* ra, const Residue *rb, list< HBondFlow > &hbf) const
  {
    bool ab = true;
    bool ba = true;

    hbf.sort ();

    // One direction...

    gOut (3) << "Testing " << *this << endl;

    if (ra->getType ()->is (typeA) && rb->getType ()->is (typeB))
      {
	vector< Description >::const_iterator descIt;

	for (descIt = descriptions.begin (); descriptions.end () != descIt; ++descIt)
	  {
	    gOut (3) << descIt->direction << descIt->hbond << "   " << flush;
	    if (! descIt->ignored)
	      {
		list< HBondFlow >::reverse_iterator k;
		bool found = false;
		
		for (k = hbf.rbegin (); k != hbf.rend (); ++k)
		  {
		    if ((k->hbond.getDonorResidue () == ra
			 && '>' == descIt->direction
			 && descIt->hbond == k->hbond)
			|| (k->hbond.getDonorResidue () == rb
			    && '<' == descIt->direction
			    && descIt->hbond == k->hbond))
		      {
			found = true;
			break;
		      }
		  }
		if (! found)
		  {
		    ab = false;
		    gOut (3) << "ANot found " << endl;
		    break;
		  }
		else
		  {
		    if (k->hbond.getDonorResidue () == rb)
		      gOut (3) << '>';
		    else
		      gOut (3) << '<';
		    gOut (3) << (HBond) k->hbond << " " << k->flow << endl;
		  }
	      }
	  }
      }
    else
      {
	ab = false;
      }
  
    // The other direction
    if (rb->getType ()->is (typeA) && ra->getType ()->is (typeB))
      {
	vector< Description >::const_iterator descIt;

	for (descIt = descriptions.begin (); descriptions.end () != descIt; ++descIt)
	  {
	    gOut (0) << descIt->direction << descIt->hbond << "   ";
	    if (! descIt->ignored)
	      {
		list< HBondFlow >::reverse_iterator k;
		bool found = false;
		
		for (k = hbf.rbegin (); k != hbf.rend (); ++k)
		  {
		    if ((k->hbond.getDonorResidue () == rb
			 &&  '>' == descIt->direction
			 && descIt->hbond == k->hbond)
			|| (k->hbond.getDonorResidue () == ra
			    && '<' == descIt->direction))
		      {
			found = true;
			break;
		      }
		  }
		if (! found)
		  {
		    gOut (3) << "BNot found " << endl;
		    ba = false;
		    break;
		  }
		else
		  {
		    if (k->hbond.getDonorResidue () == rb)
		      gOut (3) << '>';
		    else
		      gOut (3) << '<';
		    gOut (3) << (HBond) k->hbond << " " << k->flow << endl;
		  }
	      }
	  }
      }
    else
      {
	ba = false;
      }

    return (!ab && !ba) ? 0 : name;
  }



//   void PairingPattern::amberOutput (ostream& out, CResId &id_a, CResId &id_b,
// 				    const ResidueType *ta, const ResidueType *tb)
//   {
//     int i;

//     out << " " << *name << " " << *typeA << " - " << *typeB << endl;

//     bool reverse = false;
//     if (ta->is (typeB) && tb->is (typeA)) reverse = true;
//     else if (!ta->is (typeA) || !tb->is (typeB)) {
//       LibException e;
//       throw e << "Pairing type " << *name
// 	      << " does not fit residue types " 
// 	      << *ta << ", " << *tb 
// 	      << " (" << *typeA << ", " << *typeB << " expected)";
//     } 

//     CResId new_id_a, new_id_b;

//     for (i=0; i<mSize; ++i) {
//       if (!ignored[i]) {
// 	if ((!reverse && directions[i] == '>') || 
// 	    (reverse && directions[i] == '<')) {
// 	  new_id_a = id_a;
// 	  new_id_b = id_b;
// 	} else {
// 	  new_id_a = id_b;
// 	  new_id_b = id_a;
// 	}

// 	out << " &rst iresid=1," << endl;
// 	out << "      iat(1)=" << new_id_a
// 	    << ", iat(2)=" << new_id_b << "," << endl;
// 	out << "      atnam(1)= '" << hbonds[i].getDonor ()->getAmberRep () << "', "
// 	    << "atnam(2)= '" << hbonds[i].getAcceptor ()->getAmberRep () << "'," << endl;
// 	out << "      r1= 1.0, r2= 1.5, r3= 3.0, r4= 5.0," << endl;
// 	out << "      rk2=0.0, rk3=32.0" << endl;
// 	out << " &end" << endl;
// 	out << " &rst iresid=1," << endl;
// 	out << "      iat(1)=" << new_id_a << ", iat(2)=" << new_id_a << ", iat(3)=" << new_id_b << "," << endl;
// 	out << "      atnam(1)= '" << hbonds[i].getDonor ()->getAmberRep () << "', "
// 	    << "atnam(2)= '" << hbonds[i].getHydro ()->getAmberRep () << "', "
// 	    << "atnam(3)= '" << hbonds[i].getAcceptor ()->getAmberRep () << "'," << endl;
// 	out << "      r1= 150, r2= 170, r3= 190, r4= 210," << endl;
// 	out << "      rk2=20.0, rk3=20.0" << endl;
// 	out << " &end" << endl;
      
//       }
//     }
//   }



  // STATIC FUNCTIONS -----------------------------------------------------

  void PairingPattern::init ()
  {
    PairingPattern pat;
 
    pat = PairingPattern (PropertyType::pI, ResidueType::rA, ResidueType::rA);
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    pat.addBond ('<', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pII, ResidueType::rA, ResidueType::rA);
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('<', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIII, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIV, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pV, ResidueType::rA, ResidueType::rA);     
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('<', AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVI, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7, true); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVII, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6); 
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6, true); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pVIII, ResidueType::rA, ResidueType::rG);   
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN1, AtomType::aLP1); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pIX, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pX, ResidueType::rA, ResidueType::rG);     
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXI, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXII, ResidueType::rU, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXIII, ResidueType::rU, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXIV, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXV, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVI, ResidueType::rU, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVII, ResidueType::rC, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXVIII, ResidueType::rC, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);  
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXIX, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3, true); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXX, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXI, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXII, ResidueType::rC, ResidueType::rG);   
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true); 
    pat.addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXIII, ResidueType::rA, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXIV, ResidueType::rA, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXV, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2, true); 
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVI, ResidueType::rA, ResidueType::rC);   
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat.addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1); 
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVII, ResidueType::rG, ResidueType::rU);   
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4, true); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::pXXVIII, ResidueType::rG, ResidueType::rU);  
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p35, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p36, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p37, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p38, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p39, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 40 is a 39 ;

    pat = PairingPattern (PropertyType::p41, ResidueType::rA, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p68, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p69, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p70, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p71, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p72, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p73, ResidueType::rC, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 74 is a 73 ;

    pat = PairingPattern (PropertyType::p75, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p76, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p77, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p78, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);
    //# 79 is a 78 ;

    pat = PairingPattern (PropertyType::p80, ResidueType::rA, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p29, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p30, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p53, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p54, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p55, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p56, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p57, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p58, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p59, ResidueType::rG, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p60, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 61 is a 60 ;

    pat = PairingPattern (PropertyType::p62, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p63, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p64, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p65, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p66, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p67, ResidueType::rA, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p42, ResidueType::rU, ResidueType::rA);    
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 43 is a 42 ;

    pat = PairingPattern (PropertyType::p44, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p45, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p46, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p47, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p48, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 49 is a 48 ;

    pat = PairingPattern (PropertyType::p50, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p51, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p52, ResidueType::rA, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);


    pat = PairingPattern (PropertyType::p131, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p132, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p133, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p134, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);
    //# 135 is a 134 ; # 136 is a 134 ;

    pat = PairingPattern (PropertyType::p137, ResidueType::rC, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p116, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p117, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 118 is a 117 ;

    pat = PairingPattern (PropertyType::p119, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 120 is a 119 ;

    pat = PairingPattern (PropertyType::p121, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p122, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p123, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p124, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p125, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p126, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p127, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p128, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p129, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p130, ResidueType::rG, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p31, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p32, ResidueType::rC, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p100, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p101, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p102, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 103 is a 102 ;

    pat = PairingPattern (PropertyType::p104, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p105, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p106, ResidueType::rU, ResidueType::rC);    
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p97, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p98, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p99, ResidueType::rC, ResidueType::rU);    
    pat.addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p108, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 109 is a 108 ;

    pat = PairingPattern (PropertyType::p110, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p111, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p112, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p113, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p114, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p115, ResidueType::rG, ResidueType::rG);    
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p33, ResidueType::rG, ResidueType::rG);  
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p34, ResidueType::rG, ResidueType::rG);
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);
  
    pat = PairingPattern (PropertyType::p83, ResidueType::rG, ResidueType::rU);  
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p84, ResidueType::rG, ResidueType::rU);  
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p85, ResidueType::rG, ResidueType::rU);
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p86, ResidueType::rG, ResidueType::rU);
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p87, ResidueType::rG, ResidueType::rU);  
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p88, ResidueType::rG, ResidueType::rU); 
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 89 is a 88 ;

    pat = PairingPattern (PropertyType::p90, ResidueType::rG, ResidueType::rU); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p91, ResidueType::rG, ResidueType::rU); 
    pat.addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p92, ResidueType::rG, ResidueType::rU);  
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p93, ResidueType::rG, ResidueType::rU); 
    pat.addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4); 
    pat.addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p94, ResidueType::rG, ResidueType::rU); 
    pat.addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = PairingPattern (PropertyType::p95, ResidueType::rU, ResidueType::rG);
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 96 is a 95 ;

    pat = PairingPattern (PropertyType::p81, ResidueType::rU, ResidueType::rU);
    pat.addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 82 is a 81 ;
  };


  ostream& 
  PairingPattern::output (ostream &os) const
  {
    os << name << ": " << typeA << " " << typeB << endl;
    for_each (descriptions.begin (), descriptions.end (), Print< const PairingPattern::Description > (os));
    return os;
  }

  
  ostream&
  operator<< (ostream &os, const PairingPattern &pat)
  {
    return pat.output (os);
  }

  
  ostream&
  operator<< (ostream &obs, const PairingPattern::Description &desc)
  {
    if (desc.ignored)
      obs << "! ";
    else
      obs << "  ";
    obs << desc.direction << " " << desc.hbond << endl;
  }

}
