//                              -*- Mode: C++ -*- 
// Relation.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <typeinfo>

#include <iterator>
#include <stdio.h>
#include <string>

#include "Exception.h"
#include "ExtendedResidue.h"
#include "HBond.h"
#include "PairingPattern.h"
#include "PropertyType.h"
#include "Relation.h"
#include "Residue.h"
#include "ResidueTopology.h"
#include "UndirectedGraph.h"
#include "stlio.h"



namespace mccore
{


  // STATIC MEMBERS -------------------------------------------------------

  
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_A;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_C;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_G;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_U;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_T;

  bool Relation::isInit = false;

  // LIFECYCLE ------------------------------------------------------------


  Relation::Relation ()
    : ref (0), res (0),
      refFace (0), resFace (0),
      sum_flow (0)
  { }
  
  
  Relation::Relation (const Residue *rA, const Residue *rB)
    : ref (rA), res (rB),
      refFace (0), resFace (0),
      sum_flow (0)
  {
    tfo = ref->getReferential ();
    tfo = tfo.invert ();
    tfo *= res->getReferential ();    
  }

  
  Relation::Relation (const Relation &other)
    : ref (other.ref), res (other.res),
      tfo (other.tfo), po4_tfo (other.po4_tfo),
      refFace (other.refFace), resFace (other.resFace), 
      labels (other.labels),
      hbonds (other.hbonds),
      sum_flow (other.sum_flow)
  { }
    

  Relation*
  Relation::clone () const
  {
    return new Relation (*this);
  }
  
  // OPERATORS ------------------------------------------------------------
  

  Relation& 
  Relation::operator= (const Relation &other)
  {
    if (this != &other)
      {
	ref = other.ref;
	res = other.res;
	tfo = other.tfo;
	po4_tfo = other.po4_tfo;
	refFace = other.refFace;
	resFace = other.resFace;
	labels = other.labels;
	hbonds = other.hbonds;
	sum_flow = other.sum_flow;
      }
    return *this;
  }
  

  // METHODS --------------------------------------------------------------


  bool
  Relation::annotate () 
  {
    areAdjacent ();
    areStacked ();
    arePaired ();

//     TODO: fix areHBonded method
//
//     if (! is (PropertyType::pPairing))
//       areHBonded ();
    
    if (!is (PropertyType::pAdjacent)
	&& (is (PropertyType::pPairing) || is (PropertyType::pStack)))
      {
	labels.insert (PropertyType::pDIR_ANY);
      }
    
    if (ref->getType ()->isNucleicAcid ()
	&& res->getType ()->isNucleicAcid ()
	&& is (PropertyType::pAdjacent))
      {
	// compute transfo from 5' base to phosphate
	vector< Atom > pVec;
	const Residue *r5, *r3;

	if (is (PropertyType::pDIR_5p))
	  {
	    r5 = ref;
	    r3 = res;
	  }
	else if (is (PropertyType::pDIR_3p))
	  {
	    r5 = res;
	    r3 = ref;
	  }
	else
	{
	  IntLibException ex ("adjacent relation should be either in direction 5' or 3'.");
	  throw ex;
	}

	try
	{
	  pVec.push_back (*r5->safeFind (AtomType::aO3p));
	  pVec.push_back (*r3->safeFind (AtomType::aP));
	  pVec.push_back (*r3->safeFind (AtomType::aO1P));
	  pVec.push_back (*r3->safeFind (AtomType::aO2P));
	  pVec.push_back (*r3->safeFind (AtomType::aO5p));

	  Residue pRes (ResidueType::rPhosphate, r5->getResId (), pVec);
	  pRes.finalize ();
	
	  po4_tfo = r5->getReferential ().invert () * pRes.getReferential ();
	  
	  if (r5 == res)
	    po4_tfo = tfo * po4_tfo;
	}
	catch (NoSuchAtomException& ex)
	{
	  gOut (3) << "unable to compute phosphate transfo: " << ex << endl;
	  po4_tfo.setIdentity ();
	}
	
      }
    else 
      {
	po4_tfo.setIdentity ();
      }
    
    return !empty ();
  }

  
  void
  Relation::areAdjacent ()
  {
    static const float ADJACENCY_SQUARED_DISTANCE = 4.0;
    Residue::const_iterator up, down;
    
    if (ref->end () != (down = ref->find (AtomType::aO3p))
	&& res->end () != (up = res->find (AtomType::aP))
	&& down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE)
    {
      labels.insert (PropertyType::pAdjacent);
      labels.insert (PropertyType::pDIR_5p);
    }
    else if (res->end () != (down = res->find (AtomType::aO3p))
	     && ref->end () != (up = ref->find (AtomType::aP))
	     && down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE)
    {
      labels.insert (PropertyType::pAdjacent);
      labels.insert (PropertyType::pDIR_3p);
    }
    else if (ref->end () != (down = ref->find (AtomType::aC))
	     && res->end () != (up = res->find (AtomType::aN))
	     && down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE)
    {
      labels.insert (PropertyType::pAdjacent);
      labels.insert (PropertyType::pDIR_5p);
    }
    else if (res->end () != (down = res->find (AtomType::aC))
	     && ref->end () != (up = ref->find (AtomType::aN))
	     && down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE)
    {
      labels.insert (PropertyType::pAdjacent);
      labels.insert (PropertyType::pDIR_3p);
    }
    
  }


  void
  Relation::areHBonded ()
  {
    Residue::const_iterator i;
    Residue::const_iterator j;
    Residue::const_iterator k;
    Residue::const_iterator l;
    vector< Residue::const_iterator > ref_at;
    vector< Residue::const_iterator > refn_at;
    vector< Residue::const_iterator > res_at;
    vector< Residue::const_iterator > resn_at;


    for (i = ref->begin (new AtomSetSideChain ()); i != ref->end (); ++i)
      {
	if (i->getType ()->isNitrogen () || i->getType ()->isOxygen ())
	  {
	    for (j = res->begin (new AtomSetSideChain ()); j != res->end (); ++j)
	      {
		if (j->getType ()->isNitrogen () || j->getType ()->isOxygen ())
		  {
		    if (i->distance (*j) > 1.7 && i->distance (*j) < 3.2)
		      {
			string str;
			
			labels.insert (PropertyType::parseType ("unclassified"));
			labels.insert (PropertyType::pPairing);
			str.append ((const char*) *(i->getType ()));
			str.append ("-");
			str.append ((const char*) *(j->getType ()));
			labels.insert (PropertyType::parseType (str.c_str ()));
		      }
		  }
	      }
	  }
      }
    

// TODO: This is experimental and is a tentative to identify as
// precisely as possible the presence of H-bonds on unindentified
// residues, between amino-nucleic acids, or when hydrogens are
// missing and their position is unknown (modified bases).
    
//     if (ref->getType ()->isNucleicAcid () && res->getType ()->isNucleicAcid ())
//       {
// 	AtomSet* hl = new AtomSetOr (new AtomSetHydrogen (), new AtomSetLP ());
// 	AtomSet* da = new AtomSetNot (hl->clone ());

// 	for (i=ref->begin (hl->clone ()); i!=ref->end (); ++i) {
// 	  for (j=ref->begin (da->clone ()); j!=ref->end (); ++j) {
// 	    if (i->distance (*j) < 1.7) {
// 	      ref_at.push_back (i);
// 	      refn_at.push_back (j);	  
// 	    }
// 	  }
// 	}
// 	for (i=res->begin (hl->clone ()); i!=res->end (); ++i) {
// 	  for (j=res->begin (da->clone ()); j!=res->end (); ++j) {
// 	    if (i->distance (*j) < 1.7) {
// 	      res_at.push_back (i);
// 	      resn_at.push_back (j);
// 	    }
// 	  }
// 	}    
	
// 	delete hl; 
// 	delete da;

	
// 	for (x=0; x<(int)ref_at.size (); ++x) {
// 	  i = ref_at[x];
// 	  j = refn_at[x];
// 	  for (y=0; y<(int)res_at.size (); ++y) {
// 	    k = res_at[y];
// 	    l = resn_at[y];
	    
// 	    if (i->getType ()->isHydrogen () && k->getType ()->isLonePair ()) {
// 	      HBond h (j->getType (), i->getType (), l->getType (), k->getType ());
// 	      h.eval (*ref, *res);
// 	      if (h.getValue () > 0.01) {
// // 		cout << h << endl;
// 	      }
// 	    } else if (k->getType ()->isHydrogen () && i->getType ()->isLonePair ()) {
// 	      HBond h (l->getType (), k->getType (), j->getType (), i->getType ());
// 	      h.eval (*res, *ref);
// 	      if (h.getValue () > 0.01) {
// // 		cout << h << endl;
// 	      }	
// 	    } 
// 	  }
// 	}
	      
//       }

//     if (ref->getType ()->isAminoAcid () && res->getType ()->isAminoAcid ())
//       {	
// 	for (i=ref->begin (); i!=ref->end (); ++i) {
// 	  if (i->getType ()->isNitrogen () 
// 	      || i->getType () == AtomType::aOG || i->getType () == AtomType::aOH) {
// 	    for (j=res->begin (); j!=res->end (); ++j) {
// 	      if (j->getType ()->isOxygen ()) {
		
// 		if (i->distance (*j) > 1.7 && i->distance (*j) < 3.5) {
// 		  bool reject = false;
// 		  if (i->getType () == AtomType::aN) {  // N donor
// 		    Vector3D u, v, w;
// 		    u = (*res->find (AtomType::aCA) - *i).normalize ();
// 		    w = (*j - *i).normalize ();
// 		    float theta = v.angle (u, w) * 180 / M_PI;
// 		    float theta_ideal = 115;
// 		    float theta_diff = fabs (theta - theta_ideal);
// 		    if (theta_diff > 40) reject = true;
// 		  }

// 		  if (j->getType () == AtomType::aO) { // O acceptor
// 		    Vector3D u, v, w;
// 		    u = (*ref->find (AtomType::aC) - *j).normalize ();
// 		    w = (*i - *j).normalize ();
// 		    float theta = v.angle (u, w) * 180 / M_PI;
// 		    float theta_ideal = 106;
// 		    float theta_diff = fabs (theta - theta_ideal);
// 		    if (theta_diff > 40) reject = true;
// 		  }		  
		  
// 		  if (!reject) {
// // 		    cout << *ref << " " << *res << " : " <<  *i << " -> " << *j << " \t " << i->distance (*j) << endl;
// 		    labels.insert (PropertyType::parseType ("amino-pair"));
// 		  }
// 		}
// 	      }
// 	    }
// 	  }
// 	}
	
// 	for (i=res->begin (); i!=res->end (); ++i) {
// 	  if (i->getType ()->isNitrogen () 
// 	      || i->getType () == AtomType::aOG || i->getType () == AtomType::aOH) {
// 	    for (j=ref->begin (); j!=ref->end (); ++j) {
// 	      if (j->getType ()->isOxygen ()) {
		
// 		if (i->distance (*j) > 1.7 && i->distance (*j) < 3.5) {
// 		   bool reject = false;

// 		  if (i->getType () == AtomType::aN) {  // N donor
// 		    Vector3D u, v, w;
// 		    u = (*res->find (AtomType::aCA) - *i).normalize ();
// 		    w = (*j - *i).normalize ();
// 		    float theta = v.angle (u, w) * 180 / M_PI;
// 		    float theta_ideal = 115;
// 		    float theta_diff = fabs (theta - theta_ideal);
// // 		    cout << theta << endl;
// // 		    cout << theta_diff << endl;
// 		    if (theta_diff > 40) reject = true;
// 		  }


// 		  if (j->getType () == AtomType::aO) { // O acceptor
// 		    Vector3D u, v, w;
// 		    u = (*ref->find (AtomType::aC) - *j).normalize ();
// 		    w = (*i - *j).normalize ();
// 		    float theta = v.angle (u, w) * 180 / M_PI;
// 		    float theta_ideal = 106;
// 		    float theta_diff = fabs (theta - theta_ideal);
// // 		    cout << theta << endl;
// // 		    cout << theta_diff << endl;
// 		    if (theta_diff > 40) reject = true;
// 		  }

// 		  if (!reject) {
// //  		    cout << *ref << " " << *res << " : " <<  *j << " <- " << *i << " \t " << i->distance (*j) << endl;		    
// 		    ts.insert (PropertyType::parseType ("amino-pair"));
// 		  }
// 		}
// 	      }
// 	    }
// 	  }
// 	}
//       }
  }
  

  void
  Relation::arePaired ()
  {
    static const float PAIRING_CUTOFF = 0.8f;
    static const float TWO_BONDS_CUTOFF = 1.5f;
    static const float THREE_BONDS_CUTOFF = 2.1f;

    //if (ref->getType ()->isNucleicAcid () && res->getType ()->isNucleicAcid ())
    try
    {
      Residue::const_iterator i, j, k, l;
      map< Residue::const_iterator, int > atomToInt; 
      int node = 0;
      MaximumFlowGraph< int, HBond > graph;
	
      graph.insert (node++); // Source
      graph.insert (node++); // Sink
	
      vector< Residue::const_iterator > ref_at;
      vector< Residue::const_iterator > refn_at;
      vector< Residue::const_iterator > res_at;
      vector< Residue::const_iterator > resn_at;
      int x, y;
	
      //     AtomSet* hl = new AtomSetOr (new AtomSetHydrogen (), new AtomSetLP ());
      //     hl = new AtomSetAnd (hl, new AtomSetNot (new AtomSetOr (new AtomSetAtom (AtomType::a2H5M), 
      // 							    new AtomSetAtom (AtomType::a3H5M))));
      //     AtomSet* da = new AtomSetNot (hl->clone ());

      //     for (i=ref->begin (hl->clone ()); i!=ref->end (); ++i) {
      //       for (j=ref->begin (da->clone ()); j!=ref->end (); ++j) {
      // 	if (i->distance (*j) < 1.7) {
      // 	  ref_at.push_back (i);
      // 	  refn_at.push_back (j);	  
      // 	}
      //       }
      //     }
      //     for (i=res->begin (hl->clone ()); i!=res->end (); ++i) {
      //       for (j=res->begin (da->clone ()); j!=res->end (); ++j) {
      // 	if (i->distance (*j) < 1.7) {
      // 	  res_at.push_back (i);
      // 	  resn_at.push_back (j);	  
      // 	}
      //       }
      //     }    
      //     delete da;
      //     delete hl;
    
      AtomSet* da = new AtomSetAnd (new AtomSetSideChain (), 
				    new AtomSetNot (new AtomSetOr (new AtomSetAtom (AtomType::a2H5M), 
								   new AtomSetAtom (AtomType::a3H5M))));
      for (i=ref->begin (da->clone ()); i!=ref->end (); ++i)
      {
	if ((i->getType ()->isCarbon ()
	     || i->getType ()->isNitrogen ()
	     || i->getType ()->isOxygen ()))
	{
	  for (j=ref->begin (da->clone ()); j!=ref->end (); ++j)
	  {
	    if ((j->getType ()->isHydrogen ()
		 || j->getType ()->isLonePair ())
		&& i->distance (*j) < 1.7)
	    {
	      ref_at.push_back (j);
	      refn_at.push_back (i);	  
	    }
	  }
	}
      }
        
      for (i=res->begin (da->clone ()); i!=res->end (); ++i)
      {
	if ((i->getType ()->isCarbon ()
	     || i->getType ()->isNitrogen ()
	     || i->getType ()->isOxygen ()))
	{
	  for (j=res->begin (da->clone ()); j!=res->end (); ++j)
	  {
	    if ((j->getType ()->isHydrogen ()
		 || j->getType ()->isLonePair ())
		&& i->distance (*j) < 1.7)
	    {
	      res_at.push_back (j);
	      resn_at.push_back (i);	  
	    }
	  }
	}
      }
      delete da;
	
      for (x = 0; x < (int) ref_at.size (); ++x)
      {
	i = ref_at[x];
	j = refn_at[x];
	for (y=0; y<(int)res_at.size (); ++y)
	{
	  k = res_at[y];
	  l = resn_at[y];
		
	  if (i->getType ()->isHydrogen ()
	      && k->getType ()->isLonePair ())
	  {
	    HBond h (j->getType (), i->getType (), l->getType (), k->getType ());
		    
	    h.evalStatistically (*ref, *res);
	    //h.eval (*ref, *res);
		    
	    if (h.getValue () > 0.01)
	    {
	      if (atomToInt.find (i) == atomToInt.end ())
	      {
		graph.insert (node);
		graph.connect (0, node);
		atomToInt[i] = node++;
	      }
	      if (atomToInt.find (k) == atomToInt.end ())
	      {
		graph.insert (node);
		graph.connect (node, 1);
		atomToInt[k] = node++;
	      }
	      graph.connect (atomToInt[i], atomToInt[k], h, h.getValue ());
	    }
	  }
	  else if (k->getType ()->isHydrogen ()
		   && i->getType ()->isLonePair ())
	  {
	    HBond h (l->getType (), k->getType (), j->getType (), i->getType ());
		    
	    h.evalStatistically (*res, *ref);
	    //h.eval (*res, *ref);
		    
	    if (h.getValue () > 0.01)
	    {
	      if (atomToInt.find (k) == atomToInt.end ())
	      {
		graph.insert (node);
		graph.connect (0, node);
		atomToInt[k] = node++;
	      }
	      if (atomToInt.find (i) == atomToInt.end ())
	      {
		graph.insert (node);
		graph.connect (node, 1);
		atomToInt[i] = node++;
	      }
	      graph.connect (atomToInt[k], atomToInt[i], h, h.getValue ());
	    }
	  }
	}
      }
	
      if (graph.size () >= 3)
      {
	//     graph.output (cout);
	    
	graph.preFlowPush (0, 1);
	    
	//     graph.output (cout);
	    
	map< Residue::const_iterator, int >::iterator m, n;
	for (m = atomToInt.begin (); m != atomToInt.end (); ++m)
	{
	  for (n = atomToInt.begin (); n != atomToInt.end (); ++n)
	  {
	    if (graph.areConnected (m->second, n->second))
	    {
	      float flow;

	      flow = graph.getFlow (m->second, n->second);
	      sum_flow += flow;
	      hbonds.push_back (HBondFlow (graph.getEdge (m->second, n->second), flow));
	    }
	  }
	}
	
	//     cout << "Sum flow = " << sum_flow << endl;
	    
	if (sum_flow >= PAIRING_CUTOFF)
	{
	  labels.insert (PropertyType::pPairing);
		
	  if (sum_flow < TWO_BONDS_CUTOFF)
	    labels.insert (PropertyType::pOneHbond);
		
		
	  // Compute contact points and visual contact points
	  Vector3D pa;
	  Vector3D pb;
	  Vector3D pva;
	  Vector3D pvb;
		
	  list< HBondFlow > hbf;
	  for (m=atomToInt.begin (); m!=atomToInt.end (); ++m)
	  {
	    for (n=atomToInt.begin (); n!=atomToInt.end (); ++n)
	    {
	      if (graph.areConnected (m->second, n->second))
	      {
		HBondFlow fl;
			    
		fl.hbond = graph.getEdge (m->second, n->second);
		fl.flow = graph.getFlow (m->second, n->second);
		hbf.push_back (fl);
			    
		if (fl.hbond.getDonorResidue () == ref)
		{
		  pa = pa + (fl.hbond.getHydrogen () * fl.flow);
		  pb = pb + (fl.hbond.getLonePair () * fl.flow);
		  pva = pva + (fl.hbond.getHydrogen () * fl.flow);
		  pvb = pvb + (fl.hbond.getAcceptor () * fl.flow);
		}
		else
		{
		  pa = pa + (fl.hbond.getLonePair () * fl.flow);
		  pb = pb + (fl.hbond.getHydrogen () * fl.flow);
		  pva = pva + (fl.hbond.getAcceptor () * fl.flow);
		  pvb = pvb + (fl.hbond.getHydrogen () * fl.flow);
		}
	      }
	    }
	  }
		
	  pa = pa / sum_flow;
	  pb = pb / sum_flow;
	  pva = pva / sum_flow;
	  pvb = pvb / sum_flow;
		
	  Vector3D pc, pd;
	  pc = *ref->safeFind (AtomType::aC1p); 
	  pc = pc - *ref->safeFind (AtomType::aPSY);
	  pc = pc + pa;
	  pd = *res->safeFind (AtomType::aC1p); 
	  pd = pd - *res->safeFind (AtomType::aPSY);
	  pd = pd + pb;
		
	  float rad = fabs (pa.torsionAngle (pc, pb, pd));
	  const PropertyType *iso = (rad < M_PI / 2
				     ? PropertyType::pCis
				     : PropertyType::pTrans);
		
	  labels.insert (iso);
		
	  refFace = getFace (ref, pa);
	  resFace= getFace (res, pb);
		
	  int size_hint;
	  if (sum_flow >= PAIRING_CUTOFF && sum_flow < TWO_BONDS_CUTOFF)
	  {
	    size_hint = 1;
	  }
	  else if (sum_flow < THREE_BONDS_CUTOFF)
	  {
	    size_hint = 2;
	  }
	  else
	  {
	    size_hint = 3;
	  }
		
	  hbf.sort ();
		
	  while ((int)hbf.size () != size_hint) hbf.pop_front ();
		
	  const PropertyType *pp = translatePairing (ref, res, hbf, sum_flow, size_hint);
	  if (pp)
	    labels.insert (pp);
	}
      }
      else
	hbonds.clear ();
    }
    catch (NoSuchAtomException& ex)
    {
      gOut (3) << "An error occured during pairing annotation: " << ex << endl;
    }
  }
    
  
  void
  Relation::areStacked ()
  {
    static const float STACK_DISTANCE_CUTOFF = 4.50f;
    static const float STACK_NORMAL_CUTOFF   = 0.61f; // 35 deg
    static const float STACK_OVERLAP_CUTOFF  = 0.61f; // 35 deg       
 
    
    //    if (ref->getType ()->isNucleicAcid () || res->getType ()->isNucleicAcid ())
    try
    {
      Vector3D pyrCenterA;
      Vector3D pyrCenterB;
      Vector3D imidCenterA;
      Vector3D imidCenterB;
      Vector3D normalA, normalB;
      Vector3D centerV;
      float distance, theta1, theta2, tau1, tau2, tau3, tau4;
      float normal, overlap;

      // Stacking Pyr-Pyr 
      pyrCenterA = ((*(ref->safeFind (AtomType::aN1))
		     + *(ref->safeFind (AtomType::aC2))
		     + *(ref->safeFind (AtomType::aN3))
		     + *(ref->safeFind (AtomType::aC4))
		     + *(ref->safeFind (AtomType::aC5))
		     + *(ref->safeFind (AtomType::aC6))) / 6);
      pyrCenterB = ((*(res->safeFind (AtomType::aN1))
		     + *(res->safeFind (AtomType::aC2))
		     + *(res->safeFind (AtomType::aN3))
		     + *(res->safeFind (AtomType::aC4))
		     + *(res->safeFind (AtomType::aC5))
		     + *(res->safeFind (AtomType::aC6))) / 6);
	
      distance = pyrCenterA.distance (pyrCenterB);
      centerV = pyrCenterB - pyrCenterA;
      centerV = centerV.normalize ();
      normalA = pyrimidineNormal (ref);
      normalB = pyrimidineNormal (res);
      theta1 = (float) acos (normalA.dot (normalB));   // this is symmetric
      theta2 = (float) acos (-normalA.dot (normalB));
      tau1 = (float) acos (normalA.dot (centerV));  // this ain't
      tau2 = (float) acos (-normalA.dot (centerV));
      tau3 = (float) acos (normalB.dot (centerV));
      tau4 = (float) acos (-normalB.dot (centerV));
	
      normal = min (theta1, theta2);
      overlap = min (min (tau1, tau2), min (tau3, tau4));
	
      // Check if the stack is reverse here since we need only pyr-pyr rings...
      float rev_angle = Vector3D (0, 0, 0).angle (normalA, normalB);
      bool reverse = false;
	
      if (ref->getType ()->isPurine () && res->getType ()->isPurine ()
	  || ref->getType ()->isPyrimidine () && res->getType ()->isPyrimidine ())
      {
	if (rev_angle > M_PI / 2)
	  reverse = true;
      }
      else if (rev_angle < M_PI / 2) 
      {
	reverse = true;
      }
	
      if (distance <= STACK_DISTANCE_CUTOFF
	  && normal <= STACK_NORMAL_CUTOFF
	  && overlap <=  STACK_OVERLAP_CUTOFF)
      {
	labels.insert (PropertyType::pStack);
	if (reverse)
	  labels.insert (PropertyType::pReverse);
	return;
      }
	
      // Stacking imid-Pyr
      if (ref->getType ()->isPurine ())
      {
	imidCenterA = ((*(ref->safeFind (AtomType::aC4))
			+ *(ref->safeFind (AtomType::aC5))
			+ *(ref->safeFind (AtomType::aN7))
			+ *(ref->safeFind (AtomType::aC8))
			+ *(ref->safeFind (AtomType::aN9))) / 5);
	    
	distance = imidCenterA.distance (pyrCenterB);
	centerV = pyrCenterB - imidCenterA;
	centerV = centerV.normalize ();
	normalA = imidazolNormal (ref);
	normalB = pyrimidineNormal (res);
	theta1 = (float) acos (normalA.dot (normalB)); // this is symmetric
	theta2 = (float) acos (-normalA.dot (normalB));
	tau1 = (float) acos (normalA.dot (centerV));  // this ain't
	tau2 = (float) acos (-normalA.dot (centerV));
	tau3 = (float) acos (normalB.dot (centerV));
	tau4 = (float) acos (-normalB.dot (centerV));
	    
	normal = min (theta1, theta2);
	overlap = min (min (tau1, tau2), min (tau3, tau4));
	    
	if (distance <= STACK_DISTANCE_CUTOFF
	    && normal <= STACK_NORMAL_CUTOFF
	    && overlap <=  STACK_OVERLAP_CUTOFF)
	{
	  labels.insert (PropertyType::pStack);
	  if (reverse)
	    labels.insert (PropertyType::pReverse);
	  return;
	}
      }
	
      // Stacking Pyr-Imid
      if (res->getType ()->isPurine ())
      {
	imidCenterB = ((*(res->safeFind (AtomType::aC4))
			+ *(res->safeFind (AtomType::aC5))
			+ *(res->safeFind (AtomType::aN7))
			+ *(res->safeFind (AtomType::aC8))
			+ *(res->safeFind (AtomType::aN9))) / 5);
	    
	distance = pyrCenterA.distance (imidCenterB);
	centerV = imidCenterB - pyrCenterA;
	centerV = centerV.normalize ();
	normalA = pyrimidineNormal (ref);
	normalB = imidazolNormal (res);
	theta1 = (float) acos (normalA.dot (normalB));  // this is symmetric
	theta2 = (float) acos (-normalA.dot (normalB));
	tau1 = (float) acos (normalA.dot (centerV));  // this ain't
	tau2 = (float) acos (-normalA.dot (centerV));
	tau3 = (float) acos (normalB.dot (centerV));
	tau4 = (float) acos (-normalB.dot (centerV));
	    
	normal = min (theta1, theta2);
	overlap = min (min (tau1, tau2), min (tau3, tau4));
	    
	if (distance <= STACK_DISTANCE_CUTOFF
	    && normal <= STACK_NORMAL_CUTOFF
	    && overlap <=  STACK_OVERLAP_CUTOFF)
	{
	  labels.insert (PropertyType::pStack);
	  if (reverse)
	    labels.insert (PropertyType::pReverse);
	  return;
	}
      }
	
      // Stacking Imid-Imid
      if (ref->getType ()->isPurine () && res->getType ()->isPurine ())
      {
	distance = imidCenterA.distance (imidCenterB);
	centerV = imidCenterB - imidCenterA;
	centerV = centerV.normalize ();
	normalA = imidazolNormal (ref);
	normalB = imidazolNormal (res);
	theta1 = (float) acos (normalA.dot (normalB)); // this is symmetric
	theta2 = (float) acos (-normalA.dot (normalB));
	tau1 = (float) acos (normalA.dot (centerV));  // this ain't
	tau2 = (float) acos (-normalA.dot (centerV));
	tau3 = (float) acos (normalB.dot (centerV));
	tau4 = (float) acos (-normalB.dot (centerV));
	    
	normal = min (theta1, theta2);
	overlap = min (min (tau1, tau2), min (tau3, tau4));
	    
	if (distance <= STACK_DISTANCE_CUTOFF
	    && normal <= STACK_NORMAL_CUTOFF
	    && overlap <=  STACK_OVERLAP_CUTOFF)
	{
	  labels.insert (PropertyType::pStack);
	  if (reverse)
	    labels.insert (PropertyType::pReverse);
	  return;
	}
      }
    }
    catch (NoSuchAtomException& ex)
    {
      gOut (3) << "An error occured during stacking annotation: " << ex << endl;
    }
    
  }


  Relation
  Relation::invert () const
  {
    Relation inv;
    inv.ref = res;
    inv.res = ref;
    inv.tfo = tfo.invert ();
    inv.po4_tfo = inv.tfo * po4_tfo;
    inv.refFace = resFace;
    inv.resFace = refFace;
    for (set< const PropertyType* >::const_iterator i=labels.begin (); i!=labels.end (); ++i) {
      if (*i == PropertyType::pDIR_5p) inv.labels.insert (PropertyType::pDIR_3p);
      else if (*i == PropertyType::pDIR_3p) inv.labels.insert (PropertyType::pDIR_5p);
      else inv.labels.insert (*i);
    }
    return inv;
  }


  // I/O -----------------------------------------------------------------------
  

  ostream&
  Relation::write (ostream &os) const
  {
    if (ref!=0 && res!=0) {
      os << "{" 
	 << ref->getResId () << ref->getType () << " -> " 
	 << res->getResId () << res->getType () << ": ";
      copy (labels.begin (), labels.end (), ostream_iterator< const PropertyType* > (os, " "));
      if (is (PropertyType::pPairing))
	os << " " << refFace << "/" << resFace;
      os << "}";
    }	
    return os;
  }


  // STATIC METHODS ------------------------------------------------------------


  set< const PropertyType* > 
  Relation::areAdjacent (const Residue* ra, const Residue *rb)
  {
    Relation rel (ra, rb);

    rel.areAdjacent ();
    return rel.getLabels ();
  }
  

  set< const PropertyType* > 
  Relation::arePaired (const Residue* ra, const Residue *rb, 
		       const PropertyType* &pta, const PropertyType* &ptb)
  {
    Relation rel (ra, rb);

    rel.arePaired ();
    pta = rel.getRefFace ();
    ptb = rel.getResFace ();
    return rel.getLabels ();
  }

  
  set< const PropertyType* > 
  Relation::areStacked (const Residue* ra, const Residue *rb)
  {
    Relation rel (ra, rb);

    rel.areStacked ();
    return rel.getLabels ();
  }

  
  set< const PropertyType* > 
  Relation::areHBonded (const Residue* ra, const Residue *rb)
  {
    Relation rel (ra, rb);

    rel.areHBonded ();
    return rel.getLabels ();
  }
    

  Vector3D 
  Relation::pyrimidineNormal (const Residue *res)
  {
    Vector3D radius1, radius2, center;
    Vector3D normal;
    
    center = ((*(res->safeFind (AtomType::aN1))
	       + *(res->safeFind (AtomType::aC2))
	       + *(res->safeFind (AtomType::aN3))
	       + *(res->safeFind (AtomType::aC4))
	       + *(res->safeFind (AtomType::aC5))
	       + *(res->safeFind (AtomType::aC6)))
	      / 6);
    radius1 = (((*(res->safeFind (AtomType::aN1)) - center) * 1)
	       + ((*(res->safeFind (AtomType::aC2)) - center) * 0.5)
	       + ((*(res->safeFind (AtomType::aN3)) - center) * -0.5)
	       + ((*(res->safeFind (AtomType::aC4)) - center) * -1)
	       + ((*(res->safeFind (AtomType::aC5)) - center) * -0.5)
	       + ((*(res->safeFind (AtomType::aC6)) - center) * 0.5));
    radius2 = (((*(res->safeFind (AtomType::aC2)) - center) * 0.8660254)
	       + ((*(res->safeFind (AtomType::aN3)) - center) * 0.8660254)
	       + ((*(res->safeFind (AtomType::aC5)) - center) * -0.8660254)
	       + ((*(res->safeFind (AtomType::aC6)) - center) * -0.8660254));
    
    normal = radius1.cross (radius2);
    return normal.normalize ();
  }



  Vector3D 
  Relation::imidazolNormal (const Residue *res)
  {
    Vector3D radius1, radius2, center;
    Vector3D normal;
    
    center = ((*(res->safeFind (AtomType::aC4))
	       + *(res->safeFind (AtomType::aC5))
	       + *(res->safeFind (AtomType::aN7))
	       + *(res->safeFind (AtomType::aC8))
	       + *(res->safeFind (AtomType::aN9)))
	      / 5);
    
    radius1 = (((*(res->safeFind (AtomType::aC4)) - center) * 1)
	       + ((*(res->safeFind (AtomType::aC5)) - center) * 0.30901699)
	       + ((*(res->safeFind (AtomType::aN7)) - center) * -0.80901699)
	       + ((*(res->safeFind (AtomType::aC8)) - center) * -0.80901699)
	       + ((*(res->safeFind (AtomType::aN9)) - center) * 0.30901699));
    
    radius2 = (((*(res->safeFind (AtomType::aC5)) - center) * 0.95105652)
	       + ((*(res->safeFind (AtomType::aN7)) - center) * 0.58778525)
	       + ((*(res->safeFind (AtomType::aC8)) - center) * -0.58778525)
	       + ((*(res->safeFind (AtomType::aN9)) - center) * -0.95105652));
    
    normal = radius1.cross (radius2);
    return normal.normalize ();
  }


  const PropertyType* 
  Relation::getFace (const Residue *r, const Vector3D& p)
  {
    if (!Relation::isInit) Relation::init ();

    HomogeneousTransfo t;
    t = r->getReferential ();
    t = t.invert ();
    Vector3D pp = t * p;

    vector< pair< Vector3D, const PropertyType* > > *faces = 0;

    if (r->getType ()->isA ()) faces = &faces_A;
    else if (r->getType ()->isC ()) faces = &faces_C;
    else if (r->getType ()->isG ()) faces = &faces_G;
    else if (r->getType ()->isU ()) faces = &faces_U;
    else if (r->getType ()->isT ()) faces = &faces_T;

    int face_index = 0;
    float dist = MAXFLOAT;
    for (unsigned int x=0; x<faces->size (); ++x) {
      float tmp = pp.distance ((*faces)[x].first);
      if (tmp < dist) {
	face_index = x;
	dist = tmp;
      }
    }

    return (*faces)[face_index].second;   
  }


  void 
  Relation::init () 
  {
    try
    {
      
      Vector3D ta, tb;

      ExtendedResidue A (ResidueType::rRA, ResId ('A', 1));
      A.setTheoretical ();

      ta = *A.safeFind (AtomType::aH8);	
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("C8")));
      ta = (*A.safeFind (AtomType::aH8) + *A.safeFind (AtomType::aLP7)) / 2;	
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*A.safeFind (AtomType::a2H6) + *A.safeFind (AtomType::aLP7)) / 2;
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *A.safeFind (AtomType::a2H6);
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*A.safeFind (AtomType::a1H6) + *A.safeFind (AtomType::a2H6)) / 2;
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *A.safeFind (AtomType::a1H6);
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*A.safeFind (AtomType::aLP1) + *A.safeFind (AtomType::a1H6)) / 2;
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*A.safeFind (AtomType::aLP1) + *A.safeFind (AtomType::aH2)) / 2;
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *A.safeFind (AtomType::aH2);
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = (*A.safeFind (AtomType::aH2) + *A.safeFind (AtomType::aLP3)) / 2;
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
      ta = *A.safeFind (AtomType::aLP3);
      faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

      ExtendedResidue C (ResidueType::rRC, ResId ('C', 1));
      C.setTheoretical ();

      ta = *C.safeFind (AtomType::aH6);
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*C.safeFind (AtomType::a1H4) + *C.safeFind (AtomType::aH5)) / 2;
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *C.safeFind (AtomType::a1H4);
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*C.safeFind (AtomType::a1H4) + *C.safeFind (AtomType::a2H4)) / 2;
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *C.safeFind (AtomType::a2H4);
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*C.safeFind (AtomType::a2H4) + *C.safeFind (AtomType::aLP3)) / 2;
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*C.safeFind (AtomType::aLP3) + *C.safeFind (AtomType::a2LP2)) / 2;
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *C.safeFind (AtomType::a2LP2);
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*C.safeFind (AtomType::a2LP2) + *C.safeFind (AtomType::a1LP2)) / 2;
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *C.safeFind (AtomType::a1LP2);
      faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

      ExtendedResidue G (ResidueType::rRG, ResId ('G', 1));
      G.setTheoretical ();

      ta = *G.safeFind (AtomType::aH8);
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("C8")));
      ta = (*G.safeFind (AtomType::aH8) + *G.safeFind (AtomType::aLP7)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*G.safeFind (AtomType::a1LP6) + *G.safeFind (AtomType::aLP7)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *G.safeFind (AtomType::a1LP6);
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*G.safeFind (AtomType::a1LP6) + *G.safeFind (AtomType::a2LP6)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *G.safeFind (AtomType::a2LP6);
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*G.safeFind (AtomType::a2LP6) + *G.safeFind (AtomType::aH1)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*G.safeFind (AtomType::aH1) + *G.safeFind (AtomType::a2H2)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *G.safeFind (AtomType::a2H2);
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*G.safeFind (AtomType::a2H2) + *G.safeFind (AtomType::a1H2)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *G.safeFind (AtomType::a1H2);
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Sw")));
      ta = (*G.safeFind (AtomType::a1H2) + *G.safeFind (AtomType::aLP3)) / 2;
      faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
      ExtendedResidue U (ResidueType::rRU, ResId ('U', 1));
      U.setTheoretical ();
	
      ta = *U.safeFind (AtomType::aH6);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*U.safeFind (AtomType::a1LP4) + *U.safeFind (AtomType::aH5)) / 2;
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *U.safeFind (AtomType::a1LP4);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*U.safeFind (AtomType::a1LP4) + *U.safeFind (AtomType::a2LP4)) / 2;
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *U.safeFind (AtomType::a2LP4);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*U.safeFind (AtomType::a2LP4) + *U.safeFind (AtomType::aH3)) / 2;
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *U.safeFind (AtomType::aH3);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*U.safeFind (AtomType::a2LP2) + *U.safeFind (AtomType::aH3)) / 2;
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = *U.safeFind (AtomType::a2LP2);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*U.safeFind (AtomType::a2LP2) + *U.safeFind (AtomType::a1LP2)) / 2;
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *U.safeFind (AtomType::a1LP2);
      faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
      ExtendedResidue T (ResidueType::rDT, ResId ('T', 1));
      T.setTheoretical ();
    
      ta = *T.safeFind (AtomType::aH6);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*T.safeFind (AtomType::a1LP4) + *T.safeFind (AtomType::aC5M)) / 2;
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *T.safeFind (AtomType::a1LP4);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*T.safeFind (AtomType::a1LP4) + *T.safeFind (AtomType::a2LP4)) / 2;
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *T.safeFind (AtomType::a2LP4);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*T.safeFind (AtomType::a2LP4) + *T.safeFind (AtomType::aH3)) / 2;
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *T.safeFind (AtomType::aH3);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*T.safeFind (AtomType::a2LP2) + *T.safeFind (AtomType::aH3)) / 2;
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = *T.safeFind (AtomType::a2LP2);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*T.safeFind (AtomType::a2LP2) + *T.safeFind (AtomType::a1LP2)) / 2;
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *T.safeFind (AtomType::a1LP2);
      faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
 
      isInit = true;
    }
    catch (NoSuchAtomException& ex)
    {
      FatalIntLibException fex ("", __FILE__, __LINE__);
      fex << "failed to initialize relation: " << ex.what ();
      throw fex;
    }
    
  }



  const PropertyType* 
  Relation::translatePairing (const Residue* ra, const Residue *rb, 
			      list< HBondFlow > &hbf, 
			      float total_flow, int size_hint)
  {
    list< PairingPattern >::iterator i;
    const PropertyType *type;
    const PropertyType *best_type = 0;
    int best_size = 0;

    for (i=PairingPattern::patternList().begin ();
	 i!=PairingPattern::patternList().end (); ++i) {
      if (size_hint >= (*i).size () && 
	  (type = (*i).evaluate (ra, rb, hbf)) != 0) {
	if ((*i).size () > best_size) {
	  best_size = (*i).size ();
	  best_type = type;
	}
      }
    }

    return best_type;
  }


  // NON-MEMBER FUNCTIONS ------------------------------------------------------

  ostream& operator<< (ostream &os, const Relation &r)
  {
    return r.write (os);
  }

  ostream& operator<< (ostream &os, const Relation *r)
  {
    return r->write (os);
  }
}
