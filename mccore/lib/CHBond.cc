//                        -*- Mode: C++ -*-
// CHBond.cc
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Patrick Gendron
// Last Modified On : Fri Mar  7 11:41:45 2003
// Update Count     : 57
// Status           : 
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
#include <math.h>

#include "AtomType.h"
#include "CAtom.h"
#include "CHBond.h"
#include "AbstractResidue.h"
#include "McCore.h"
#include "CResidue.h"
#include "fPdbstream.h"

HBond::HBond ()
  : donor (0), hydro (0), acceptor (0), lonepair (0)
{}


HBond::HBond (t_Atom *donor, t_Atom *hydro, t_Atom *acceptor, t_Atom *lonepair)
{
  this->donor = donor;
  this->hydro = hydro;
  this->acceptor = acceptor;
  this->lonepair = lonepair;
}


HBond::HBond (const HBond &other)
  : donor (other.donor), 
  hydro (other.hydro), 
  acceptor (other.acceptor), 
  lonepair (other.lonepair)
{}


const HBond& 
HBond::operator= (const HBond &other)
{
  if (&other != this)
    {
      donor = other.donor;
      hydro = other.hydro;
      acceptor = other.acceptor;
      lonepair = other.lonepair;
    }
  return *this;
}


bool 
HBond::operator== (const HBond &other) const
{
  return (donor == other.donor && 
	  hydro == other.hydro &&
	  acceptor == other.acceptor && 
	  lonepair == other.lonepair);
}



ostream&
operator<< (ostream &os, const HBond &theBond)
{
  os << *(theBond.donor) << "-"
     << *(theBond.hydro) << " -> "
     << *(theBond.acceptor) << " (" << *(theBond.lonepair) << ") " << flush;
  return os;
}



const int CHBond::sNbGauss = 7;

const float CHBond::sProbH[7] = {
  1,
  0,
  0,
  0,
  0,
  0,
  0
};

const float CHBond::sWeight[7] = {
  // Optimisé sur level1
  0.00752508,
  0.00989524,
  0.0259051,
  0.109535,
  0.120741,
  0.534611,
  0.191654
};

const float CHBond::sMean[7][3] = {
  {0.100846, 2.45718, 2.25155},
  {8.78474, 1.13239, -0.0738701},
  {3.28653, 0.449332, 0.474348},
  {5.92268, -0.553811, 0.0362715},
  {5.06479, -0.443828, -0.424931},
  {6.52255, -0.165407, -0.0835928},
  {7.73618, -0.296942, -0.299877}
};

const float CHBond::sCovarInv[7][3][3] = {
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

const float CHBond::sCovarDet[7] = {
  0.096653, 
  6.40514, 
  0.157177, 
  0.999763, 
  0.00418066, 
  0.126178, 
  0.45749
};


CHBond::CHBond ()
  : HBond ()
{
  mResidueA = 0;
  mResidueB = 0;
  cache_penality = -1;
}



CHBond::CHBond (const AbstractResidue *nResidueA, const AbstractResidue *nResidueB,
		t_Atom *nDonor, t_Atom *nHydro, 
		t_Atom *nAcceptor, t_Atom *nLonePair)
  : HBond (nDonor, nHydro, nAcceptor, nLonePair),
    mResidueA (nResidueA),
    mResidueB (nResidueB),
    cache_penality (-1)
{ }



CHBond::CHBond (const CHBond &other)
  : HBond (other),
    mResidueA (other.mResidueA),
    mResidueB (other.mResidueB),
    cache_penality (other.cache_penality)
{ }



const CHBond&
CHBond::operator= (const CHBond &other)
{
  if (&other != this)
    {
      HBond::operator= (other);
      mResidueA = other.mResidueA;
      mResidueB = other.mResidueB;
      cache_penality = other.cache_penality;
    }
  return *this;
}



CHBond::operator float () const
{
  if (cache_penality < 0)
    {
      float x[3];

      // Special treatment for CH3 and OH position of hydrogens.
      if (donor->is_C5M ()) {
 	CPoint3D px, py, pz, up, pv;
 	float tan70 = 2.7474774;
 	float C_H_dist = 1.08;

	px = ((*mResidueB)[lonepair] - (*mResidueA)[a_C5]).Normalize ();
	py = ((*mResidueA)[donor] - (*mResidueA)[a_C5]).Normalize ();
	up = px.Cross (py).Normalize ();
	pz = py.Cross (up);

	pv = (*mResidueA)[donor] + (py + pz * tan70).Normalize () * C_H_dist;
	CAtom at (pv.GetX (), pv.GetY (), pv.GetZ (), a_1H5M);
	//	mResidueA->insert (at);

	x[0] = log (pow (at | (*mResidueB)[lonepair], 3));
	x[1] = atanh (cos ((*mResidueA)[donor].Angle (at, (*mResidueB)[acceptor])));
	x[2] = atanh (cos ((*mResidueB)[acceptor].Angle ((*mResidueA)[donor], (*mResidueB)[lonepair])));      
      } else {
	x[0] = log (pow ((*mResidueA)[hydro] | (*mResidueB)[lonepair], 3));
	x[1] = atanh (cos ((*mResidueA)[donor].Angle ((*mResidueA)[hydro], (*mResidueB)[acceptor])));
	x[2] = atanh (cos ((*mResidueB)[acceptor].Angle ((*mResidueA)[donor], (*mResidueB)[lonepair])));
      }

      float p_x = 0;
      float p_h = 0;
      for (int i = 0; i < sNbGauss; ++i) {
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
	else prob = sWeight[i] * tmp / (pow (2 * M_PI, 1.5) * sqrt (sCovarDet[i]));
	
	p_x += prob;
	p_h += sProbH[i] * prob;
      }

      cache_penality = p_h / p_x;
    }

  return cache_penality;
}



void CHBond::SetHBond (const AbstractResidue *nResidueA, const AbstractResidue *nResidueB,
		       t_Atom *nDonor, t_Atom *nHydro,
		       t_Atom *nAcceptor, t_Atom *nLonePair)
{
  mResidueA = nResidueA;
  mResidueB = nResidueB;
  donor = nDonor;
  acceptor = nAcceptor;
  hydro = nHydro;
  lonepair = nLonePair;
  cache_penality = -1;
}


const CAtom &
CHBond::GetDonor (const AbstractResidue *r) const 
{ 
  return (r)?(*r)[donor]:(*mResidueA)[donor]; 
}

const CAtom &
CHBond::GetHydrogen (const AbstractResidue *r) const 
{ 
  return (r)?(*r)[hydro]:(*mResidueA)[hydro]; 
}

const CAtom &
CHBond::GetAcceptor (const AbstractResidue *r) const 
{ 
return (r)?(*r)[acceptor]:(*mResidueB)[acceptor]; 
}

const CAtom &
CHBond::GetLonePair (const AbstractResidue *r) const 
{ 
return (r)?(*r)[lonepair]:(*mResidueB)[lonepair]; 
}


float CHBond::Eval (float dist, float angle_h, float angle_l, bool decision)
{
  float x[3];
//    x[0] = log (pow (dist, 3));
//    x[1] = atanh (cos (angle_h));
//    x[2] = atanh (cos (angle_l));
  x[0] = dist;
  x[1] = angle_h;
  x[2] = angle_l;
  
  float p_x = 0;
  float p_h = 0;
  for (int i = 0; i < sNbGauss; ++i) {
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
    else prob = sWeight[i] * tmp / (pow (2 * M_PI, 1.5) * sqrt (sCovarDet[i]));
    
    p_x += prob;
    p_h += sProbH[i] * prob;
  }
  
  if (decision) return (p_h / p_x);
  else return (p_x);
}


void
CHBond::DumpAmberRestraint (ostream &os)
{
  os << " &rst iresid=1," << endl;
  os << "      iat(1)=" << ((const CResId&)*mResidueA).GetResNo ()
     << ", iat(2)=" << ((const CResId&)*mResidueB).GetResNo() << "," << endl;
  os << "      atnam(1)= '" << donor->getAmberRep () << "', "
     << "atnam(2)= '" << acceptor->getAmberRep () << "'," << endl;
  os << "      r1= 1.0, r2= 1.5, r3= 3.0, r4= 5.0," << endl;
  os << "      rk2=0.0, rk3=32.0" << endl;
  os << " &end" << endl;
  os << " &rst iresid=1," << endl;
  os << "      iat(1)=" << ((const CResId&)*mResidueA).GetResNo()
     << ", iat(2)=" << ((const CResId&)*mResidueA).GetResNo()
     << ", iat(3)=" << ((const CResId&)*mResidueB).GetResNo() << "," << endl;
  os << "      atnam(1)= '" << donor->getAmberRep () << "', "
     << "atnam(2)= '" << hydro->getAmberRep () << "', "
     << "atnam(3)= '" << acceptor->getAmberRep () << "'," << endl;
  os << "      r1= 150, r2= 170, r3= 190, r4= 210," << endl;
  os << "      rk2=20.0, rk3=20.0" << endl;
  os << " &end" << endl;
}



ostream&
operator<< (ostream &os, const CHBond &theBond)
{
  if (theBond.mResidueA && theBond.mResidueB)
    {
      os << (const CResId&)*theBond.mResidueA << " -> "
	 << (const CResId&)*theBond.mResidueB << "     "
	 << *(theBond.donor) << "-"
	 << *(theBond.hydro) << " -> "
	 << *(theBond.acceptor) << " (" << *(theBond.lonepair) << ")     "
	 << "[" << (float)theBond << "]" << flush;
    }
  else
    {
      cerr << "Error..." << endl;
      os << "baseA" << " -> "
	 << "baseB" << "     "
	 << *(theBond.donor) << "-"
	 << *(theBond.hydro) << " -> "
	 << *(theBond.acceptor) << "     "
	 << "[" << "???" << "]" << flush;
    }
  return os;
}

