//                              -*- Mode: C++ -*- 
// PairingPattern.cc
// Copyright © 2001, 2002, 2003 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Thu May 31 08:17:56 2001
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Jul 10 12:14:52 2003
// Update Count     : 37
// Status           : Unknown.
// 


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "PairingPattern.h"


namespace mccore {

  bool _verbose = false;

  // STATIC MEMBERS ------------------------------------------------------------

  list< PairingPattern* > PairingPattern::patterns;
  bool PairingPattern::isInit = false;


  // LIFECYCLE ------------------------------------------------------------


  PairingPattern::PairingPattern (void)
    : name (0), typeA (0), typeB (0), mSize (0)
  {}


  PairingPattern::PairingPattern (const PropertyType* id, const ResidueType* type_a, 
				  const ResidueType* type_b)
    : name (id), typeA (type_a), typeB (type_b), mSize (0)
  {}



  PairingPattern::PairingPattern (const PairingPattern &other)
    : name (other.name), typeA (other.typeA), typeB (other.typeB),
      ignored (other.ignored), directions (other.directions), 
      hbonds (other.hbonds), mSize (other.mSize)
  {}


  PairingPattern::~PairingPattern (void)
  {}


  // OPERATORS ------------------------------------------------------------


  const PairingPattern &PairingPattern::operator= (const PairingPattern &other)
  {
    if (this != &other) { 
      name = other.name;
      typeA = other.typeA;
      typeB = other.typeB;
      ignored = other.ignored;
      directions = other.directions;
      hbonds = other.hbonds;
      mSize = other.mSize;
    }
    return *this;
  }


  // ACCESS ---------------------------------------------------------------


  // METHODS --------------------------------------------------------------


  void 
  PairingPattern::addBond (char dir, const AtomType* donor, const AtomType* hydro,
			   const AtomType* acceptor, const AtomType* lonepair, 
			   bool ignore)
  {
    directions.push_back (dir);
    hbonds.push_back (HBond (donor, hydro, acceptor, lonepair));
    ignored.push_back (ignore);
    if (!ignore) mSize++;
  }


  const PropertyType*
  PairingPattern::evaluate (const Residue* ra, const Residue *rb, list< HBondFlow > &hbf) const
  {
    int j;
    list< HBondFlow >::reverse_iterator k;
  
    hbf.sort ();

    bool ab = true;
    bool ba = true;

    // One direction...

    if (_verbose) cout << "Testing " << *this << endl;

    if (ra->getType ()->is (typeA) && rb->getType ()->is (typeB))
      {
	for (j=0; j<(int)hbonds.size (); ++j) {
	  if (_verbose) cout << directions[j] << hbonds[j] << "   " << flush;
	  if (ignored[j]) {}
	  else {
	    bool found = false;
	    for (k=hbf.rbegin (); k!=hbf.rend (); ++k) {
	      if (k->hbond.getDonorResidue () == ra && directions[j] == '>') {
		if (hbonds[j] == k->hbond) { found = true; break; } 
	      } else if (k->hbond.getDonorResidue () == rb && directions[j] == '<') {
		if (hbonds[j] == k->hbond) { found = true; break; } 
	      }
	    }
	    if (!found) {
	      ab = false;
	      if (_verbose) cout << "ANot found " << endl;
	      break;
	    } else {
	      if (_verbose) {
		if (k->hbond.getDonorResidue () == rb) cout << '>' << flush;
		else cout << '<' << flush;
		cout << (HBond)k->hbond << " " << k->flow << endl;
	      }
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
	for (j=0; j<(int)hbonds.size (); ++j) {
	  if (_verbose) cout << directions[j] << hbonds[j] << "   " << flush;
	  if (ignored[j]) {}
	  else {
	    bool found = false;
	    for (k=hbf.rbegin (); k!=hbf.rend (); ++k) {
	     	     
	      if (k->hbond.getDonorResidue () == rb && directions[j] == '>') {
		if (hbonds[j] == k->hbond) { found = true; break; } 
	      } else if (k->hbond.getDonorResidue () == ra && directions[j] == '<') {
		if (hbonds[j] == k->hbond) { found = true; break; } 
	      }
	    }
	    if (!found) {
	      if (_verbose) cout << "BNot found " << endl;
	      ba = false;
	      break;
	    } else {
	      if (_verbose) {
		if (k->hbond.getDonorResidue () == rb) cout << '>' << flush;
		else cout << '<' << flush;
		cout << (HBond)k->hbond << " " << k->flow << endl;
	      }
	    }
	  }
	}
      }
    else
      {
	ba = false;
      }

    if (!ab && !ba) return 0;
    return name;
    
    return 0;
  }



//   void PairingPattern::amberOutput (ostream& out, CResId &id_a, CResId &id_b,
// 				    const ResidueType *ta, const ResidueType *tb)
//   {
//     int i;

//     out << " " << *name << " " << *typeA << " - " << *typeB << endl;

//     bool reverse = false;
//     if (ta->is (typeB) && tb->is (typeA)) reverse = true;
//     else if (!ta->is (typeA) || !tb->is (typeB)) {
//       CLibException e;
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
    PairingPattern *pat;
 
    pat = new PairingPattern (PropertyType::pI, ResidueType::rA, ResidueType::rA);
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    pat->addBond ('<', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pII, ResidueType::rA, ResidueType::rA);
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('<', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pIII, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pIV, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pV, ResidueType::rA, ResidueType::rA);     
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('<', AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pVI, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7, true); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pVII, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6); 
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO6, AtomType::a1LP6, true); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pVIII, ResidueType::rA, ResidueType::rG);   
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN1, AtomType::aLP1); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pIX, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pX, ResidueType::rA, ResidueType::rG);     
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXI, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXII, ResidueType::rU, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXIII, ResidueType::rU, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXIV, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXV, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXVI, ResidueType::rU, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXVII, ResidueType::rC, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXVIII, ResidueType::rC, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);  
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXIX, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3, true); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXX, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXI, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXII, ResidueType::rC, ResidueType::rG);   
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true); 
    pat->addBond ('<', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXIII, ResidueType::rA, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXIV, ResidueType::rA, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXV, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2, true); 
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXVI, ResidueType::rA, ResidueType::rC);   
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3); 
    pat->addBond ('<', AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1); 
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXVII, ResidueType::rG, ResidueType::rU);   
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4, true); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::pXXVIII, ResidueType::rG, ResidueType::rU);  
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aO6, AtomType::a2LP6); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2, true);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p35, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p36, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p37, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p38, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p39, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 40 is a 39 ;

    pat = new PairingPattern (PropertyType::p41, ResidueType::rA, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p68, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p69, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p70, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p71, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p72, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p73, ResidueType::rC, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 74 is a 73 ;

    pat = new PairingPattern (PropertyType::p75, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p76, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p77, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p78, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);
    //# 79 is a 78 ;

    pat = new PairingPattern (PropertyType::p80, ResidueType::rA, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p29, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p30, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p53, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p54, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p55, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p56, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN1, AtomType::aLP1);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p57, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p58, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p59, ResidueType::rG, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p60, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 61 is a 60 ;

    pat = new PairingPattern (PropertyType::p62, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p63, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p64, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p65, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p66, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p67, ResidueType::rA, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p42, ResidueType::rU, ResidueType::rA);    
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 43 is a 42 ;

    pat = new PairingPattern (PropertyType::p44, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p45, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p46, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p47, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p48, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 49 is a 48 ;

    pat = new PairingPattern (PropertyType::p50, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p51, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a1H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p52, ResidueType::rA, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN6, AtomType::a2H6, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);


    pat = new PairingPattern (PropertyType::p131, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p132, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p133, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p134, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);
    //# 135 is a 134 ; # 136 is a 134 ;

    pat = new PairingPattern (PropertyType::p137, ResidueType::rC, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p116, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p117, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 118 is a 117 ;

    pat = new PairingPattern (PropertyType::p119, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);
    //# 120 is a 119 ;

    pat = new PairingPattern (PropertyType::p121, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p122, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p123, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p124, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p125, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p126, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p127, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p128, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p129, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p130, ResidueType::rG, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p31, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p32, ResidueType::rC, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p100, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p101, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p102, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 103 is a 102 ;

    pat = new PairingPattern (PropertyType::p104, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p105, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p106, ResidueType::rU, ResidueType::rC);    
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p97, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p98, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a2H4, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p99, ResidueType::rC, ResidueType::rU);    
    pat->addBond ('>', AtomType::aN4, AtomType::a1H4, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p108, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 109 is a 108 ;

    pat = new PairingPattern (PropertyType::p110, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p111, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p112, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p113, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p114, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p115, ResidueType::rG, ResidueType::rG);    
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a2LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p33, ResidueType::rG, ResidueType::rG);  
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p34, ResidueType::rG, ResidueType::rG);
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aN7, AtomType::aLP7); 
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO6, AtomType::a1LP6);
    patterns.push_back (pat);
  
    pat = new PairingPattern (PropertyType::p83, ResidueType::rG, ResidueType::rU);  
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p84, ResidueType::rG, ResidueType::rU);  
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a1LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p85, ResidueType::rG, ResidueType::rU);
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p86, ResidueType::rG, ResidueType::rU);
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO2, AtomType::a2LP2); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p87, ResidueType::rG, ResidueType::rU);  
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO2, AtomType::a2LP2);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p88, ResidueType::rG, ResidueType::rU); 
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 89 is a 88 ;

    pat = new PairingPattern (PropertyType::p90, ResidueType::rG, ResidueType::rU); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p91, ResidueType::rG, ResidueType::rU); 
    pat->addBond ('>', AtomType::aN1, AtomType::aH1, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p92, ResidueType::rG, ResidueType::rU);  
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p93, ResidueType::rG, ResidueType::rU); 
    pat->addBond ('>', AtomType::aN2, AtomType::a1H2, AtomType::aO4, AtomType::a2LP4); 
    pat->addBond ('<', AtomType::aN3, AtomType::aH3, AtomType::aN3, AtomType::aLP3);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p94, ResidueType::rG, ResidueType::rU); 
    pat->addBond ('>', AtomType::aN2, AtomType::a2H2, AtomType::aO4, AtomType::a2LP4);
    patterns.push_back (pat);

    pat = new PairingPattern (PropertyType::p95, ResidueType::rU, ResidueType::rG);
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aN7, AtomType::aLP7);
    patterns.push_back (pat);
    //# 96 is a 95 ;

    pat = new PairingPattern (PropertyType::p81, ResidueType::rU, ResidueType::rU);
    pat->addBond ('>', AtomType::aN3, AtomType::aH3, AtomType::aO4, AtomType::a1LP4);
    patterns.push_back (pat);
    //# 82 is a 81 ;
  };


  ostream& 
  PairingPattern::output (ostream &os) const
  {
    os << name << ": " << flush;
    os << typeA << " " << typeB << endl;
    for (int i=0; i<hbonds.size (); ++i) {
      if (ignored[i]) os << "! ";
      else os << "  ";
      os << directions[i] << " ";
      os << hbonds[i] << endl;
    }
    return os;
  }

  ostream&
  operator<< (ostream &os, const PairingPattern &pat)
  {
    return pat.output (os);
  }

}
