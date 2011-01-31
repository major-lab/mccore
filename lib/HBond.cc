//                              -*- Mode: C++ -*- 
// HBond.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu Mar 20 18:05:28 2003
// $Revision: 1.17 $
// $Id: HBond.cc,v 1.17 2006-08-28 17:50:31 thibaup Exp $
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

#ifdef __APPLE_CC__
#define _GLIBCPP_USE_C99 1
#endif

#include <cmath>
#include <iomanip>

#include "Atom.h"
#include "AtomType.h"
#include "Binstream.h"
#include "HBond.h"
#include "Pdbstream.h"
#include "Residue.h"



namespace mccore
{
  // GLOBAL CONSTANT ---------------------------------------------------------

  const float TAN70        = 2.7474774;  // For CH3-like conformations
  const float C_H_DIST_CYC = 1.08;       // C-H distance for aromatic C

  // MEMBER CONSTANT ---------------------------------------------------------

  const int HBond::sNbGauss = 7;

  
  const float HBond::sProbH[7] = {
    1,
    0,
    0,
    0,
    0,
    0,
    0
  };

  
  const float HBond::sWeight[7] = {
    // Optimisé sur level1
    0.00752508,
    0.00989524,
    0.0259051,
    0.109535,
    0.120741,
    0.534611,
    0.191654
  };

  
  const float HBond::sMean[7][3] = {
    {0.100846, 2.45718, 2.25155},
    {8.78474, 1.13239, -0.0738701},
    {3.28653, 0.449332, 0.474348},
    {5.92268, -0.553811, 0.0362715},
    {5.06479, -0.443828, -0.424931},
    {6.52255, -0.165407, -0.0835928},
    {7.73618, -0.296942, -0.299877}
  };

  
  const float HBond::sCovarInv[7][3][3] = {
    {{2.80141, 1.04863, 0.88979},
     {1.04863, 2.37603, -0.59708},
     {0.88979, -0.59708, 2.58077}},
    {{0.173398, 0.292812, 0.0360642},
     {0.292812, 1.02071, 0.192637},
     {0.0360642, 0.192637, 1.75143}},
    {{8.89039, 4.47243, 4.42705},
     {4.47243, 3.16789, 2.61418},
     {4.42705, 2.61418, 3.14729}},
    {{3.1899, 0.842455, 0.862609},
     {0.842455, 0.753278, 0.317195},
     {0.862609, 0.317195, 0.839071}},
    {{11.7232, 13.8285, 11.7912},
     {13.8285, 20.5467, 11.29},
     {11.7912, 11.29, 18.2967}},
    {{0.907316, 0.522994, 0.614166},
     {0.522994, 3.27058, 0.547732},
     {0.614166, 0.547732, 3.37027}},
    {{2.18977, 0.416751, 0.437718},
     {0.416751, 1.10475, 0.0841468},
     {0.437718, 0.0841468, 1.06094}}
  };

  
  const float HBond::sCovarDet[7] = {
    0.096653,
    6.40514,
    0.157177,
    0.999763,
    0.00418066,
    0.126178,
    0.45749
  };


  HBond::HBond (float val)
    : donor (0), hydrogen (0), acceptor (0), lonepair (0),
      value (val), resD (0), resA (0)
  { }


  HBond::HBond (const AtomType *d, const AtomType *h, 
		const AtomType *a, const AtomType *l)
    : donor (d), hydrogen (h), acceptor (a), lonepair (l),
      value (0), resD (0), resA (0)
  { }
  
  
  HBond::HBond (const HBond &other)
    : donor (other.donor),
      hydrogen (other.hydrogen),
      acceptor (other.acceptor),
      lonepair (other.lonepair),
      value (other.value),
      resD (other.resD),
      resA (other.resA)
  { }


  const HBond&
  HBond::operator= (const HBond &other)
  {
    if (&other != this)
      {
	donor = other.donor;
	hydrogen = other.hydrogen;
	acceptor = other.acceptor;
	lonepair = other.lonepair;
	value = other.value;
	resD = other.resD;
	resA = other.resA;
      }
    return *this;
  }
  
  
  bool 
  HBond::operator== (const HBond &other) const
  {
    return (donor == other.donor && 
	    hydrogen == other.hydrogen &&
	    acceptor == other.acceptor && 
	    lonepair == other.lonepair);
  }


  const Atom& 
  HBond::getDonor () const throw (NullPointerException)
  {
    if (resD == 0)
      {
	throw NullPointerException ("Residue not set in HBond", __FILE__, __LINE__);
      }
    return *resD->safeFind (donor);
  }
  
  const Atom& 
  HBond::getDonor (const Residue &r) const
  {
    return *r.safeFind (donor);
  }
  
  
  const Atom&
  HBond::getHydrogen () const throw (NullPointerException)
  {
    if (resD == 0)
      {
	throw NullPointerException ("Residue not set in HBond", __FILE__, __LINE__);
      }
    return *resD->safeFind (hydrogen);
  }

  
  const Atom& 
  HBond::getHydrogen (const Residue &r) const
  {
    return *r.safeFind (hydrogen);
  }

  
  const Atom&
  HBond::getAcceptor () const throw (NullPointerException)
  {
    if (resA == 0)
      {
	throw NullPointerException ("Residue not set in HBond", __FILE__, __LINE__);
      }
    return *resA->safeFind (acceptor);
  }
  
  
  const Atom&
  HBond::getAcceptor (const Residue &r) const
  {
    return *r.safeFind (acceptor);
  }

  
  const Atom&
  HBond::getLonePair () const throw (NullPointerException)
  {
    if (resA == 0)
      {
	throw NullPointerException ("Residue not set in HBond", __FILE__, __LINE__);
      }
    return *resA->safeFind (lonepair);
  }

  
  const Atom&
  HBond::getLonePair (const Residue &r) const
  {
    return *r.safeFind (lonepair);
  }
  
  
  void
  HBond::reassignResiduePointers (const set< const Residue*, less_deref< Residue > > &resSet) throw (NoSuchElementException)
  {
    set< const Residue* >::iterator resIt;

    if (resSet.end () == (resIt = resSet.find (resA)))
    {
      NoSuchElementException ex ("", __FILE__, __LINE__);
      ex << "HBond's acceptor residue " << *resA << " not found in reassign target set.";
      throw ex;
    }
    resA = *resIt;
    if (resSet.end () == (resIt = resSet.find (resD)))
    {
      NoSuchElementException ex ("", __FILE__, __LINE__);
      ex << "HBond's donor residue " << *resD << " not found in reassign target set.";
      throw ex;
    }
    resD = *resIt;
  }

  
  float 
  HBond::eval (const Residue *ra, const Residue *rb) 
  {
    resD = ra;
    resA = rb;
    
    float hlp = getHydrogen ().distance (getLonePair ());
    return (hlp >= 0.1 && hlp < 1.65
	    ? (value = 1.0)
	    : (value = 0.0));
  }
  
  
  float 
  HBond::evalStatistically (const Residue *ra, const Residue *rb) 
  {
    float x[3];
    float p_x = 0;
    float p_h = 0;
    Atom at;
    
    resD = ra;
    resA = rb;
    
    // PreCheck on the donor/acceptor distance
    if (getDonor ().distance (getAcceptor ()) > 5)
      {
	return (value = 0);
      }
    
    if (donor == AtomType::aC5M)
      {
	Vector3D px, py, pz, up, pv;
      
	px = (getLonePair () - *ra->safeFind (AtomType::aC5)).normalize ();
	py = (getDonor () - *rb->safeFind (AtomType::aC5)).normalize ();
	up = px.cross (py).normalize ();
	pz = py.cross (up);
	pv = getDonor () + (py + pz * TAN70).normalize () * C_H_DIST_CYC;
      
	at = Atom (pv, hydrogen);
      }
//     else if (donor == AtomType::aO2p)
//       {
// 	Vector3D px;
// 	Vector3D py;
// 	Vector3D pz;
// 	Vector3D up;
// 	Vector3D pv;
// 	int side = 1;

// 	px = (getDonor () - *ra->safeFind (AtomType::aC2p)).normalize ();
// 	py = (*ra->safeFind (AtomType::aC2p) - getLonePair ()).normalize ();
// 	up = px.cross (py).normalize ();
// 	pz = py.cross (up);
// 	// if more than 90 deg, then invert the vector.
// 	if (1.5707963 < getDonor ().angle (getLonePair (), px + pz * Residue::TAN71))
// 	  {
// 	    side = -1;
// 	  }
// 	pv = getDonor () + (py + pz * side * Residue::TAN71).normalize () * Residue::O_H_DIST;
// 	at = Atom (pv, hydrogen);
//       }
    else
      {
	at = getHydrogen ();
      }
    x[0] = log (pow (at.distance (getLonePair ()), 3));       
    x[1] = atanh (cos (getDonor ().angle (at, getAcceptor ())));
    x[2] = atanh (cos (getAcceptor ().angle (getDonor (), getLonePair ())));
    
    for (int i=0; i<sNbGauss; ++i)
      {
	float diff[3];
	diff[0] = x[0] - sMean[i][0];
	diff[1] = x[1] - sMean[i][1];
	diff[2] = x[2] - sMean[i][2];
      
	float tmp = exp ((diff[0] * (diff[0] * sCovarInv[i][0][0] + 
				     diff[1] * sCovarInv[i][1][0] + 
				     diff[2] * sCovarInv[i][2][0]) + 
			  diff[1] * (diff[0] * sCovarInv[i][0][1] + 
				     diff[1] * sCovarInv[i][1][1] +
				     diff[2] * sCovarInv[i][2][1]) + 
			  diff[2] * (diff[0] * sCovarInv[i][0][2] +
				     diff[1] * sCovarInv[i][1][2] +
				     diff[2] * sCovarInv[i][2][2])) * -0.5);
	float prob;
	if (isnan (tmp) || fabs (sCovarDet[i]) < 0.0005) prob = 0;
	else prob = sWeight[i] * tmp / 
	  (pow (2 * M_PI, 1.5) * sqrt (sCovarDet[i]));
      
	p_x += prob;
	p_h += sProbH[i] * prob;
      }
    return (value = p_h / p_x);
  }
  
  
  ostream &
  HBond::output (ostream &os) const
  {
    if (resA != 0 && resD != 0)
      {
	os.precision (8);
	return os << resD->getResId () << " -> " 
		  << resA->getResId () << "  "
		  << donor << "-" << hydrogen << " -> " 
		  << acceptor << " (" << lonepair << ")"
		  << " [" << value << "]";
      }
    else
      {
	return os << donor << "-" << hydrogen << " -> " 
		  << acceptor << " (" << lonepair << ")";  
      }
  }


  iBinstream&
  HBond::read (iBinstream &is, const map< ResId, const Residue* > &resMap) throw (NoSuchElementException)
  {
    ResId id;
    map< ResId, const Residue* >::const_iterator rmIt;
    
    is >> donor >> hydrogen >> acceptor >> lonepair;
    is >> value;
    is >> id;
    if (resMap.end () == (rmIt = resMap.find (id)))
      {
	NoSuchElementException e ("cannot find residue id ", __FILE__, __LINE__);

	e << id;
	throw e;
      }
    else
      {
	resD = rmIt->second;
      }
    is >> id;
    if (resMap.end () == (rmIt = resMap.find (id)))
      {
	NoSuchElementException e ("cannot find residue id ", __FILE__, __LINE__);

	e << id;
	throw e;
      }
    else
      {
	resA = rmIt->second;
      }
    return is;
  }
    

  oBinstream&
  HBond::write (oBinstream &os) const
  {
    return os << donor << hydrogen << acceptor << lonepair
	      << value
	      << resD->getResId ()
	      << resA->getResId ();
  }
    
}



namespace std
{
  
  ostream&
  operator<< (ostream &os, const mccore::HBond &theBond)
  {
    return theBond.output (os);
  }
  
}
