//                              -*- Mode: C++ -*- 
// RiboseBuilder.cc
// Author           : Philippe Thibault
// Created On       : Mon Sep 29 14:58:39 2003
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


#include "ResidueFactoryMethod.h"
#include "ExtendedResidue.h"
#include "CException.h"

#include "RiboseBuilder.h"


namespace mccore
{

  HomogeneousTransfo RiboseBuilder::rz90 (cos (M_PI_2),-sin (M_PI_2), 0, 0,
					  sin (M_PI_2), cos (M_PI_2), 0, 0,
					  0,            0,            1, 0,
					  0,            0,            0, 1);
  
  const char RiboseBuilder::QFCT_PTP = 'p';
  const char RiboseBuilder::QFCT_BOND = 'b';
  
  RiboseBuilder::_Ribose::_Ribose ()
  {
    C1p.setType (AtomType::aC1p);
    C2p.setType (AtomType::aC2p);
    C3p.setType (AtomType::aC3p);
    C4p.setType (AtomType::aC4p);
    C5p.setType (AtomType::aC5p);
    O2p.setType (AtomType::aO2p);
    O3p.setType (AtomType::aO3p);
    O4p.setType (AtomType::aO4p);
    O5p.setType (AtomType::aO5p);
    P5p.setType (AtomType::aP);
    P3p.setType (AtomType::aP);
  }


  RiboseBuilder::_Ribose::_Ribose (const RiboseBuilder::_Ribose& right)
  {
    C1p = right.C1p;
    C2p = right.C2p;
    C3p = right.C3p;
    C4p = right.C4p;
    C5p = right.C5p;
    O2p = right.O2p;
    O3p = right.O3p;
    O4p = right.O4p;
    O5p = right.O5p;
    P5p = right.P5p;
    P3p = right.P3p;
  }


  RiboseBuilder::_Ribose::~_Ribose ()
  {

  }


  RiboseBuilder::_Ribose&
  RiboseBuilder::_Ribose::operator= (const RiboseBuilder::_Ribose& right)
  {
    if (this != &right)
      {
	C1p = right.C1p;
	C2p = right.C2p;
	C3p = right.C3p;
	C4p = right.C4p;
	C5p = right.C5p;
	O2p = right.O2p;
	O3p = right.O3p;
	O4p = right.O4p;
	O5p = right.O5p;
	P5p = right.P5p;
	P3p = right.P3p;
      }
    return *this;
  }


  void
  RiboseBuilder::_Ribose::reset ()
  {
    C1p.set (0.0, 0.0, 0.0);
    C2p.set (0.0, 0.0, 0.0);
    C3p.set (0.0, 0.0, 0.0);
    C4p.set (0.0, 0.0, 0.0);
    C5p.set (0.0, 0.0, 0.0);
    O2p.set (0.0, 0.0, 0.0);
    O3p.set (0.0, 0.0, 0.0);
    O4p.set (0.0, 0.0, 0.0);
    O5p.set (0.0, 0.0, 0.0);
    P5p.set (0.0, 0.0, 0.0);
    P3p.set (0.0, 0.0, 0.0);
  }


  void
  RiboseBuilder::_Ribose::transform (const HomogeneousTransfo& tfo)
  {
    C1p.transform (tfo);
    C2p.transform (tfo);
    C3p.transform (tfo);
    C4p.transform (tfo);
    C5p.transform (tfo);
    O2p.transform (tfo);
    O3p.transform (tfo);
    O4p.transform (tfo);
    O5p.transform (tfo);
    P5p.transform (tfo);
    P3p.transform (tfo);
  }


  RiboseBuilder::RiboseBuilder (char quality)
    : rho (0),
      chi (0),
      gamma (0),
      beta (0),
      epsilon (0),
      built_count (0)
  {
    if (quality == QFCT_PTP)
      qfct = new _PointToPointQFct (this);
    else if (quality == QFCT_BOND)
      qfct = new _BondQFct (this);
    else
      throw CIntLibException ("unkown quality functor id \'") << quality << "\'.";
  }


  RiboseBuilder::RiboseBuilder (const RiboseBuilder &right)
    : check_O5p (check_O5p),
      check_O3p (check_O3p),
      rho (right.rho),
      chi (right.chi),
      gamma (right.gamma),
      beta (right.beta),
      epsilon (right.epsilon),
      built_count (right.built_count)
  {
    ribose = right.ribose;
    qfct = right.qfct->clone ();
    alignment = right.alignment;
  }


  RiboseBuilder::~RiboseBuilder ()
  {
    delete qfct;
  }


  RiboseBuilder&
  RiboseBuilder::operator= (const RiboseBuilder &right)
  {
    ribose = right.ribose;
    delete qfct;
    qfct = right.qfct->clone ();
    check_O5p = check_O5p;
    check_O3p = check_O3p;
    alignment = right.alignment;
    rho = right.rho;
    chi = right.chi;
    gamma = right.gamma;
    beta = right.beta;
    epsilon = right.epsilon;
    built_count = right.built_count;
    return *this;
  }


  int
  RiboseBuilder::status () const
  {
    if (check_O5p && check_O3p)
      return 0;

    if (check_O5p)
      return 1;

    return -1;
  }


  void
  RiboseBuilder::buildFuranose ()
  {
    // 0.6577118824501829 rad = 37.684115 deg
    // 2.5132741228718345 rad = 144 deg

    float nu0 = 0.6981317007977318 * cos (rho + 3*2.5132741228718345);
    float nu1 = 0.6981317007977318 * cos (rho + 4*2.5132741228718345);

    // building transfo 
    // uses idealized geometries as defined by
    // G.Parkinson et al., ACTA CRYST.D (1996) v. 52, 57-64.

    // 1.0746515803304686  rad = 61.573  deg
    // 0.45770037903074895 rad = 26.2243 deg
    // 1.062835701294467   rad = 60.8960 deg
    // 1.024618226663547   rad = 58.7063 deg
  
    float sin_chi = sin (chi);
    float sin_chi_c2p = sin (chi + 1.0746515803304686);
    float sin_nu1_o2p = sin (nu1  + 0.45770037903074895);
    float sin_nu1_c3p = sin (nu1  - 1.062835701294467);
    float sin_nu0_c4p = sin (nu0  + 1.024618226663547);

    float cos_chi = cos (chi);
    float cos_chi_c2p = cos (chi + 1.0746515803304686);
    float cos_nu1_o2p = cos (nu1  + 0.45770037903074895);
    float cos_nu1_c3p = cos (nu1  - 1.062835701294467);
    float cos_nu0_c4p = cos (nu0  + 1.024618226663547);
  
    // C1' from Nt (N1 or N9)
    HomogeneousTransfo tfo
      (1,0,0,1.465,
       0,1,0,0,
       0,0,1,0);
      
    ribose.C1p.transform (tfo);

    // O4' from C1'
    tfo.set
      (0.3189593092980698,
       0,
       -0.9477684100095858,
       1.916965341275365,
	 
       -0.9477684100095858*sin_chi,cos_chi,
       -0.3189593092980698*sin_chi,
       -1.342987836983583*sin_chi,
	 
       0.9477684100095858*cos_chi,
       sin_chi,
       0.3189593092980698*cos_chi,
       1.342987836983583*cos_chi);
      
    ribose.O4p.transform (tfo);
      
    // C2' from C1'
    tfo.set
      (0.37505965617503256,
       0,
       0.9270006765422916,
       2.038466214291625,
	 
       0.9270006765422916*sin_chi_c2p,
       cos_chi_c2p,
       -0.37505965617503256*sin_chi_c2p,
       1.4173840344331636*sin_chi_c2p,
	 
       -0.9270006765422916*cos_chi_c2p,
       sin_chi_c2p,
       0.37505965617503256*cos_chi_c2p,
       -1.4173840344331636*cos_chi_c2p);
      
    ribose.C2p.transform (tfo);
      
    // O2' from C2'
    tfo.set
      (0.37505965617503256,
       0.9270006765422916*sin_nu1_o2p,
       0.9270006765422916*cos_nu1_o2p,
       2.2177447299432904 + 1.0391677584039087*cos_nu1_o2p - 0.6646594850808231*sin_nu1_o2p,
	
       0.9270006765422916*sin_chi_c2p,
       cos_chi_c2p*cos_nu1_o2p - 0.37505965617503256*sin_chi_c2p*sin_nu1_o2p,
       -0.37505965617503256*cos_nu1_o2p*sin_chi_c2p - cos_chi_c2p*sin_nu1_o2p,
       cos_chi_c2p*(-0.717*cos_nu1_o2p - 1.121*sin_nu1_o2p) + sin_chi_c2p*(1.860490357820379 - 0.4204418745722115*cos_nu1_o2p + 0.26891777347749835*sin_nu1_o2p),
	
       -0.9270006765422916*cos_chi_c2p,cos_nu1_o2p*sin_chi_c2p + 0.37505965617503256*cos_chi_c2p*sin_nu1_o2p,
       0.37505965617503256*cos_chi_c2p*cos_nu1_o2p - sin_chi_c2p*sin_nu1_o2p,
       sin_chi_c2p*(-0.717*cos_nu1_o2p - 1.121*sin_nu1_o2p) + cos_chi_c2p*(-1.860490357820379 + 0.4204418745722115*cos_nu1_o2p - 0.26891777347749835*sin_nu1_o2p));
      
    ribose.O2p.transform (tfo);
      
    // C3' from C2'
    tfo.set
      (0.07442844670182767 + 0.9085646439620313*cos_nu1_c3p,
       0.9270006765422916*sin_nu1_c3p,
       -0.3676005332037575 + 0.18395798991077703*cos_nu1_c3p,
       2.1518207386185084 + 1.3837439527541735*cos_nu1_c3p,

       (0.18395798991077703 - 0.3676005332037575*cos_nu1_c3p)*sin_chi_c2p - 0.9801121692283693*cos_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*cos_nu1_c3p - 0.37505965617503256*sin_chi_c2p*sin_nu1_c3p,
       (-0.9085646439620313 - 0.07442844670182767*cos_nu1_c3p)*sin_chi_c2p - 0.1984442887322796*cos_chi_c2p*sin_nu1_c3p,
       (1.697552053067277 - 0.5598556120693227*cos_nu1_c3p)*sin_chi_c2p - 1.4927108337348063*cos_chi_c2p*sin_nu1_c3p,
	
       cos_chi_c2p*(-0.18395798991077703 + 0.3676005332037575*cos_nu1_c3p) - 0.9801121692283693*sin_chi_c2p*sin_nu1_c3p,
       cos_nu1_c3p*sin_chi_c2p + 0.37505965617503256*cos_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*(0.9085646439620313 + 0.07442844670182767*cos_nu1_c3p) - 0.1984442887322796*sin_chi_c2p*sin_nu1_c3p,
       cos_chi_c2p*(-1.697552053067277 + 0.5598556120693227*cos_nu1_c3p) - 1.4927108337348063*sin_chi_c2p*sin_nu1_c3p);
      
    ribose.C3p.transform (tfo);
      
    // C4' from O4'
    tfo.set
      (0.10751967079428061 + 0.8922960413273637*cos_nu0_c4p,
       -0.9477684100095858*sin_nu0_c4p,
       0.3002907946977251 - 0.3194882370974149*cos_nu0_c4p,
       2.0730839032686603 + 1.2956138520073321*cos_nu0_c4p,

       (-0.3194882370974149 + 0.3002907946977251*cos_nu0_c4p)*sin_chi + 0.941470544812038*cos_chi*sin_nu0_c4p,
       cos_chi*cos_nu0_c4p - 0.3189593092980698*sin_chi*sin_nu0_c4p,
       (-0.8922960413273637 - 0.10751967079428061*cos_nu0_c4p)*sin_chi - 0.3370952584230821*cos_chi*sin_nu0_c4p,
       (-1.8068847572490294 + 0.43602223390109685*cos_nu0_c4p)*sin_chi + 1.3670152310670791*cos_chi*sin_nu0_c4p,

       cos_chi*(0.3194882370974149 - 0.3002907946977251*cos_nu0_c4p) + 0.941470544812038*sin_chi*sin_nu0_c4p,
       cos_nu0_c4p*sin_chi + 0.3189593092980698*cos_chi*sin_nu0_c4p,
       cos_chi*(0.8922960413273637 + 0.10751967079428061*cos_nu0_c4p) - 0.3370952584230821*sin_chi*sin_nu0_c4p,
       cos_chi*(1.8068847572490294 - 0.43602223390109685*cos_nu0_c4p) + 1.3670152310670791*sin_chi*sin_nu0_c4p);
      
    ribose.C4p.transform (tfo);
  }


  void
  RiboseBuilder::build5p ()
  {
    float cos_gamma = cos (gamma);
    float cos_beta = cos (beta);
    float sin_gamma = sin (gamma);
    float sin_beta = sin (beta);
  
    // C5' => align first for 5' branch
    HomogeneousTransfo branch5p
      (HomogeneousTransfo::align (ribose.C4p, ribose.C3p, ribose.O4p));
  
    HomogeneousTransfo tfo (0.4983470223041225,
			    -0.783262352599052,
			    -0.3716857979014169,
			    1.1827261524245685,
			    
			    0.,
			    0.4287143941490142,
			    -0.9034400745204099,
			    -0.6473587351650114,
			    
			    0.8669776498622179,
			    0.4502266709674608,
			    0.21364854174307712,
			    -0.6798422731608658);

    ribose.C5p.transform (branch5p * tfo);
	
    // O5' from C5' => align first for 5' branch
    tfo.set
      (0.4983470223041225*cos_gamma - 0.3716857979014169*sin_gamma,
       -0.26019509810650415 - 0.3505781564521977*cos_gamma - 0.47004642453183026*sin_gamma,
       0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma,
       1.5574070936979345 + 0.5048325452911646*cos_gamma + 0.6768668513258356*sin_gamma,
	 
       -0.9034400745204099*sin_gamma,
       0.14241637361367576 - 0.8521346728303227*cos_gamma,
       -0.40436815932672815 - 0.3001174230360551*cos_gamma,
       -0.8524383131687046 + 1.2270739288756647*cos_gamma,
	 
       0.8669776498622179*cos_gamma + 0.21364854174307712*sin_gamma,
       0.14956262411160473 + 0.20151566811507393*cos_gamma - 0.8177429105175843*sin_gamma,
       -0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma,
       -0.8952124518815765 - 0.2901825620857065*cos_gamma + 1.1775497911453214*sin_gamma);

    ribose.O5p.transform (branch5p * tfo);
      
    // P5' from O5' => align first for 5' branch
    tfo.set
      (cos_beta*(0.4983470223041225*cos_gamma - 0.3716857979014169*sin_gamma) + sin_beta*(0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma),
       -0.26019509810650415 - 0.3505781564521977*cos_gamma - 0.47004642453183026*sin_gamma,
       cos_beta*(0.7387817160165432 - 0.1234718128974842*cos_gamma - 0.16554791881575529*sin_gamma) + sin_beta*(-0.4983470223041225*cos_gamma + 0.3716857979014169*sin_gamma),
       1.7704808595373507 + cos_gamma*(0.7919209976098692 + 0.680941371276353*sin_beta) + cos_beta*(-1.0094713367650046 + 0.1687118851431224*cos_gamma + 0.22620467626984803*sin_gamma) + (1.0617878683749513 - 0.5078714742524961*sin_beta)*sin_gamma,
	 
       -0.9034400745204099*sin_gamma*cos_beta + sin_beta*(-0.40436815932672815 - 0.3001174230360551*cos_gamma),
       0.14241637361367576 - 0.8521346728303227*cos_gamma,
       cos_beta*(-0.40436815932672815 - 0.3001174230360551*cos_gamma) + 0.9034400745204099*sin_beta*sin_gamma,
       -0.9690630815209436 + 1.9248870124564157*cos_gamma + cos_beta*(0.5525286529040414 + 0.4100804468364657*cos_gamma) - 1.2344605178246881*sin_beta*sin_gamma,
	 
       sin_beta*(-0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma) + cos_beta*(0.8669776498622179*cos_gamma + 0.21364854174307712*sin_gamma),
       0.14956262411160473 + 0.20151566811507393*cos_gamma - 0.8177429105175843*sin_gamma,
       cos_beta*(-0.42465877680708897 + 0.07097277571772671*cos_gamma - 0.2880048222840108*sin_gamma) + sin_beta*(-0.8669776498622179*cos_gamma - 0.21364854174307712*sin_gamma),
       -1.0176892847665697 + cos_gamma*(-0.45520374270514047 + 1.1846382607717347*sin_beta) + cos_beta*(0.5802537526292064 - 0.09697720074070179*cos_gamma + 0.3935297891688724*sin_gamma) + (1.847199460568171 + 0.2919293674377406*sin_beta)*sin_gamma);

    ribose.P5p.transform (branch5p * tfo);
  }


  void
  RiboseBuilder::build3p ()
  {
    float cos_epsilon = cos (epsilon);
    float sin_epsilon = sin (epsilon);
  
    // O3' => align first for 3' branch
    HomogeneousTransfo branch3p
      (HomogeneousTransfo::align (ribose.C3p, ribose.C4p, ribose.C2p));
  
    HomogeneousTransfo tfo (0.5043859675317346,
			    -0.8016153916448716,
			    -0.3209479079774709,
			    1.1471116254438114,
	 
			    0.,
			    0.3716919156133742,
			    -0.9283561384876282,
			    -0.5318911312427386,
	 
			    0.8634783122679318,
			    0.46824980912510733,
			    0.18747618648037562,
			    -0.6700654768580286);

    ribose.O3p.transform (branch3p * tfo);
      
    // P3' from O3' => align first for 3' branch
    tfo.set
      (0.5043859675317346*cos_epsilon - 0.3209479079774709*sin_epsilon,
       -0.8016153916448716,
       -0.3209479079774709*cos_epsilon - 0.5043859675317346*sin_epsilon,
       1.8035544696617967 + 0.4385432214604163*cos_epsilon + 0.6891929860353622*sin_epsilon,
	 
       -0.9283561384876282*sin_epsilon,
       0.3716919156133742,
       -0.9283561384876282*cos_epsilon,
       -0.8362696409385307 + 1.2685058276294952*cos_epsilon,
	 
       0.8634783122679318*cos_epsilon + 0.18747618648037562*sin_epsilon,
       0.46824980912510733,
       0.18747618648037562*cos_epsilon - 0.8634783122679318*sin_epsilon,
       -1.053515245550579 - 0.25616746120678524*cos_epsilon + 1.179856765882902*sin_epsilon);

    ribose.P3p.transform (branch3p * tfo);
  }


  void
  RiboseBuilder::fillResidue (Residue& res) const
  {
    _Ribose rib (ribose);
    rib.transform (alignment);
  
    res.insert (rib.C1p);
    res.insert (rib.C2p);
    res.insert (rib.C3p);
    res.insert (rib.C4p);
    res.insert (rib.C5p);
    res.insert (rib.O2p);
    res.insert (rib.O4p);

    if (!check_O3p)
      res.insert (rib.O3p);


    if (!check_O5p)
      {
	res.insert (rib.O5p);
	res.insert (rib.P5p);
      }

  }


  Residue*
  RiboseBuilder::createPhosphate5p (ResidueFactoryMethod* fm) const
  {
    Vector3D p5p, o5p, u, v;
    Vector3D rib_p5p (ribose.P5p), rib_o5p (ribose.O5p);
    HomogeneousTransfo trans, rot;
    Residue::const_iterator p5p_it, o5p_it;
  
    Residue* po4 = fm ? fm->createResidue () : new ExtendedResidue ();

    rib_p5p.transform (alignment);
    rib_o5p.transform (alignment);
  
    po4->setType (ResidueType::rPhosphate);
    po4->setIdeal ();

    p5p_it = po4->find (AtomType::aP);
    o5p_it = po4->find (AtomType::aO5p);

    p5p = *p5p_it;
  
    trans = trans.translate (rib_p5p - p5p);

    p5p = *p5p_it;
    o5p = *o5p_it;

    u = o5p - p5p;
    v = rib_o5p - p5p;
  
    rot = rot.rotate (u.cross (v), p5p.angle (o5p, rib_o5p));

    po4->transform (rot * trans);

    return po4;
  }

}
