//                        -*- Mode: C++ -*-
// CHBond.cc
// Copyright © 1999, 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:39 2000
// Update Count     : 26
// Status           : 


#include <iostream.h>
#include <math.h>

#include "CHBond.h"

#include "AtomType.h"
#include "CResidue.h"
#include "McCore.h"



/**
 * Calculates the modified gaussian probability distribution function.
 * Gives 1 when m<=0 and 0.5 when m = v.
 * @param m the x - mean.
 * @param v the standard deviation.
 * @return the probability.
 */

float
eval_SCORE (float m, float v)
{
  float t;
  
  if (m <= 0)
    return 1;
  t = m / (v * (sqrt (-1 / log (0.5))));
  t *= t;
  return exp (-t);
}



CHBond::CHBond ()
{
  mResidueA = 0;
  mResidueB = 0;
  mDonor = 0;
  mAcceptor = 0;
  mHydro = 0;
  mLonePair = 0;
  cache_penality = -1;
}



CHBond::CHBond (const CHBond &right)
  : mResidueA (right.mResidueA),
    mResidueB (right.mResidueB),
    mDonor (right.mDonor),
    mAcceptor (right.mAcceptor),
    mHydro (right.mHydro),
    mLonePair (right.mLonePair),
    cache_penality (right.cache_penality)
{ }



CHBond::CHBond (const CResidue *nResidueA, const CResidue *nResidueB,
		t_Atom *nDonor, t_Atom *nHydro, 
		t_Atom *nAcceptor, t_Atom *nLonePair)
  : mResidueA (nResidueA),
    mResidueB (nResidueB),
    mDonor (nDonor),
    mAcceptor (nAcceptor),
    mHydro (nHydro),
    mLonePair (nLonePair),
    cache_penality (-1)
{ }



const CHBond&
CHBond::operator= (const CHBond &right)
{
  if (&right != this)
    {
      mResidueA = right.mResidueA;
      mResidueB = right.mResidueB;
      mDonor = right.mDonor;
      mAcceptor = right.mAcceptor;
      mHydro = right.mHydro;
      mLonePair = right.mLonePair;
      cache_penality = right.cache_penality;
    }
  return *this;
}



CHBond::operator float () const
{
  if (cache_penality < 0)
    {
      float current_angle;
      float theta_term;
      cache_penality = 1;
      
      // Angle Acceptor-Donor-Hydrogen
      current_angle = RadToDegree ((*mResidueA)[mDonor].Angle ((*mResidueA)[mHydro], (*mResidueB)[mAcceptor]));
      theta_term = eval_SCORE (current_angle - hbond_angleH_ideal, hbond_angleH_var);
      cache_penality *= theta_term;
      
      // Angle Donor-Acceptor-LonePair

      current_angle = RadToDegree ((*mResidueB)[mAcceptor].Angle ((*mResidueA)[mDonor], (*mResidueB)[mLonePair]));
      theta_term = eval_SCORE (current_angle - hbond_angleL_ideal, hbond_angleL_var);
      cache_penality *= theta_term;
      
      // Distance Donor-Acceptor
      float current_dist = (*mResidueA)[mDonor] | (*mResidueB)[mAcceptor];
      float dist_term = eval_SCORE (current_dist - hbond_dist_ideal, hbond_dist_var);
      cache_penality *= dist_term;
    }
  return cache_penality;
}



void CHBond::SetHBond (const CResidue *nResidueA, const CResidue *nResidueB,
		       t_Atom *nDonor, t_Atom *nHydro,
		       t_Atom *nAcceptor, t_Atom *nLonePair)
{
  mResidueA = nResidueA;
  mResidueB = nResidueB;
  mDonor = nDonor;
  mAcceptor = nAcceptor;
  mHydro = nHydro;
  mLonePair = nLonePair;
  cache_penality = -1;
}



void
CHBond::DumpAmberRestraint (ostream &os)
{
  os << " &rst iresid=1," << endl;
//   os << "      iat(1)=" << mResidueA->GetResNo()
// 	    << ", iat(2)=" << mResidueB->GetResNo() << "," << endl;
//   os << "      atnam(1)= '" << AmberNameString[ mDonor ] << "', "
// 	    << "atnam(2)= '" << AmberNameString[ mAcceptor ] << "'," << endl;
//   os << "      r1= 1.0, r2= 1.5, r3= 3.0, r4= 5.0," << endl;
//   os << "      rk2=0.0, rk3=32.0" << endl;
//   os << " &end" << endl;
//   os << " &rst iresid=1," << endl;
//   os << "      iat(1)=" << mResidueA->GetResNo()
// 	    << ", iat(2)=" << mResidueA->GetResNo()
// 	    << ", iat(3)=" << mResidueB->GetResNo() << "," << endl;
//   os << "      atnam(1)= '" << AmberNameString[ mDonor ] << "', "
// 	    << "atnam(2)= '" << AmberNameString[ mHydro ] << "', "
// 	    << "atnam(3)= '" << AmberNameString[ mAcceptor ] << "'," << endl;
//   os << "      r1= 150, r2= 170, r3= 190, r4= 210," << endl;
//   os << "      rk2=20.0, rk3=20.0" << endl;
  os << " &end" << endl;
}



ostream&
operator<< (ostream &os, const CHBond &theBond)
{
  if (theBond.mResidueA && theBond.mResidueB)
    {
      os << (const CResId)*theBond.mResidueA << " -> "
	 << (const CResId)*theBond.mResidueB << "     "
	 << *(theBond.mDonor) << "-"
	 << *(theBond.mHydro) << " -> "
	 << *(theBond.mAcceptor) << "     "
	 << "[" << (float)theBond << "]" << flush;
    }
  else
    {
      cerr << "Error..." << endl;
      os << "baseA" << " -> "
	 << "baseB" << "     "
	 << *(theBond.mDonor) << "-"
	 << *(theBond.mHydro) << " -> "
	 << *(theBond.mAcceptor) << "     "
	 << "[" << "???" << "]" << flush;
    }
  return os;
}
