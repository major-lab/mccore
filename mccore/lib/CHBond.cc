//                        -*- Mode: C++ -*-
// CHBond.cc
// Copyright © 1999, 2000, 2001 Laboratoire de Biologie Informatique et Théorique.
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
  // Optimisé sur 1ffk
//    0.00685586,
//    0.0276069,
//    0.0109897,
//    0.102683,
//    0.104988,
//    0.178908,
//    0.313868,
//    0.0682106,
//    0.185678
};

const float CHBond::sMean[7][3] = {
  {0.100846, 2.45718, 2.25155},
  {8.78474, 1.13239, -0.0738701},
  {3.28653, 0.449332, 0.474348},
  {5.92268, -0.553811, 0.0362715},
  {5.06479, -0.443828, -0.424931},
  {6.52255, -0.165407, -0.0835928},
  {7.73618, -0.296942, -0.299877}
//    {0.372106, 2.34613, 2.17351}, 
//    {4.10073, 0.265808, 0.263397}, 
//    {2.79089, 1.03484, 0.918478}, 
//    {5.94793, -0.394396, 0.000134236}, 
//    {5.22055, -0.50515, -0.461952}, 
//    {5.9725, -0.0679276, 0.143566}, 
//    {7.44753, -0.25692, -0.24096}, 
//    {6.24168, -0.230479, -0.19713}, 
//    {7.83215, -0.248146, -0.334584}
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
//    {{3.02239, 1.3715, 1.13844},
//     {1.3715, 2.3354, -0.228966},
//     {1.13844, -0.228966, 2.51175}},
//    {{6.1517, -0.809517, 0.463752},
//     {-0.809517, 4.8259, -2.345},
//     {0.463752, -2.345, 5.40297}},
//    {{10.5001, 2.10513, 1.97029},
//     {2.10513, 2.83424, 2.6967},
//     {1.97029, 2.6967, 3.31565}},
//    {{3.13307, 0.78012, 0.809492},
//     {0.78012, 0.710563, 0.261174},
//     {0.809492, 0.261174, 0.848647}},
//    {{10.2544, 12.3188, 10.1528},
//     {12.3188, 18.7488, 10.1583},
//     {10.1528, 10.1583, 15.9878}},
//    {{0.878105, 0.231733, 0.195747},
//     {0.231733, 4.15305, 2.72557},
//     {0.195747, 2.72557, 3.87254}},
//    {{1.68066, 0.55384, 0.68024},
//     {0.55384, 2.66366, -0.0308225},
//     {0.68024, -0.0308225, 2.97714}},
//    {{25.132, 17.608, 17.5469},
//     {17.608, 21.9551, 8.23878},
//     {17.5469, 8.23878, 22.1419}},
//    {{2.27699, 0.447363, 0.428156},
//     {0.447363, 0.875401, 0.0991827},
//     {0.428156, 0.0991827, 0.89259}}
};


const float CHBond::sCovarDet[7] = {
  0.096653, 
  6.40514, 
  0.157177, 
  0.999763, 
  0.00418066, 
  0.126178, 
  0.45749,
};



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
      float x[3];
      x[0] = log (pow ((*mResidueA)[mHydro] | (*mResidueB)[mLonePair], 3));
      x[1] = atanh (cos ((*mResidueA)[mDonor].Angle ((*mResidueA)[mHydro], (*mResidueB)[mAcceptor])));
      x[2] = atanh (cos ((*mResidueB)[mAcceptor].Angle ((*mResidueA)[mDonor], (*mResidueB)[mLonePair])));
      
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



void 
CHBond::SetHBond (const CResidue *nResidueA, const CResidue *nResidueB,
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


const CAtom &
CHBond::GetDonor (const CResidue *r) const 
{ 
  return (r)?(*r)[mDonor]:(*mResidueA)[mDonor]; 
}


const CAtom &
CHBond::GetHydrogen (const CResidue *r) const 
{ 
  return (r)?(*r)[mHydro]:(*mResidueA)[mHydro]; 
}


const CAtom &
CHBond::GetAcceptor (const CResidue *r) const 
{ 
  return (r)?(*r)[mAcceptor]:(*mResidueB)[mAcceptor]; 
}


const CAtom &
CHBond::GetLonePair (const CResidue *r) const 
{ 
return (r)?(*r)[mLonePair]:(*mResidueB)[mLonePair]; 
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
