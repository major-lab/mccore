//                              -*- Mode: C++ -*- 
// Relation.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003
// $Revision: 1.39 $
// $Id: Relation.cc,v 1.39 2005-04-04 23:08:26 larosem Exp $
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

#include <cmath>
#include <iterator>
#include <limits>
#include <string>
#include <utility>

#include "Relation.h"

#include "Atom.h"
#include "AtomSet.h"
#include "AtomType.h"
#include "Exception.h"
#include "ExtendedResidue.h"
#include "MaximumFlowGraph.h"
#include "PairingPattern.h"
#include "PropertyType.h"
#include "ResidueType.h"
#include "Messagestream.h"



namespace mccore
{

  // STATIC MEMBERS -------------------------------------------------------

  const unsigned char Relation::adjacent_mask = 4;
  const unsigned char Relation::stacking_mask = 2;
  const unsigned char Relation::pairing_mask  = 1;
  
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_A;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_C;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_G;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_U;
  vector< pair< Vector3D, const PropertyType* > > Relation::faces_T;

  bool Relation::face_init = false;

  float Relation::adjacency_distance_cutoff_square = 4.00; // 2.0 Ang
  float Relation::stack_distance_cutoff_square = 20.25; // 4.5 Ang
  float Relation::stack_tilt_cutoff = 0.61; // 35 deg
  float Relation::stack_overlap_cutoff = 0.61; // 35 deg


  Relation::Relation ()
    : ref (0),
      res (0),
      refFace (PropertyType::pNull),
      resFace (PropertyType::pNull),
      type_asp (0),
      sum_flow (0)
  {
    
  }
  
  
  Relation::Relation (const Residue *rA, const Residue *rB)
    : ref (rA),
      res (rB),
      refFace (PropertyType::pNull),
      resFace (PropertyType::pNull),
      type_asp (0),
      sum_flow (0)
  {
    this->reset (rA, rB);  
  }

  
  Relation::Relation (const Relation &other)
    : ref (other.ref),
      res (other.res),
      tfo (other.tfo),
      po4_tfo (other.po4_tfo),
      refFace (other.refFace),
      resFace (other.resFace), 
      labels (other.labels),
      type_asp (other.type_asp),
      hbonds (other.hbonds),
      sum_flow (other.sum_flow)
  {

  }
    

  Relation& 
  Relation::operator= (const Relation &other)
  {
    if (this != &other)
    {
      this->ref = other.ref;
      this->res = other.res;
      this->tfo = other.tfo;
      this->po4_tfo = other.po4_tfo;
      this->refFace = other.refFace;
      this->resFace = other.resFace;
      this->type_asp = other.type_asp;
      this->labels = other.labels;
      this->hbonds = other.hbonds;
      this->sum_flow = other.sum_flow;
    }
    return *this;
  }

  
  // METHODS --------------------------------------------------------------


  bool
  Relation::is (const PropertyType* t) const
  {
    set< const PropertyType* >::const_iterator it;
    
    for (it = this->labels.begin (); it != this->labels.end (); ++it)
      if ((*it)->is (t))
	return true;
    return false;
  }

  bool
  Relation::has (const PropertyType* t) const
  {
    return labels.find (t) != labels.end ();
  }


  void
  Relation::reset (const Residue* org, const Residue* dest)
  {
    this->ref = org;
    this->res = dest;
    this->tfo = ref->getReferential ().invert () * res->getReferential ();
    this->po4_tfo.setIdentity ();
    this->refFace = this->resFace = PropertyType::pNull;
    this->labels.clear ();
    this->type_asp = 0;
    this->hbonds.clear ();
  }


  bool
  Relation::isAdjacent () const
  {
    return this->type_asp & Relation::adjacent_mask;
  }

  
  bool
  Relation::isStacking () const
  {
    return this->type_asp & Relation::stacking_mask;
  }

  
  bool
  Relation::isPairing () const
  {
    return this->type_asp & Relation::pairing_mask;
  }


  void
  Relation::reassignResiduePointers (const set< const Residue*, less_deref< Residue> > &resSet) throw (NoSuchElementException)
  {
    set< const Residue* >::iterator resIt;
    vector< HBondFlow >::iterator hbfIt;
    set< const Residue*, less_deref< Residue > > newSet;
    
    if (resSet.end () == (resIt = resSet.find (ref)))
    {
      throw NoSuchElementException ("Residue not found", __FILE__, __LINE__);
    }
    ref = *resIt;
    newSet.insert (ref);
    if (resSet.end () == (resIt = resSet.find (res)))
    {
      throw NoSuchElementException ("Residue not found", __FILE__, __LINE__);
    }
    res = *resIt;
    newSet.insert (res);
    
    for (hbfIt = hbonds.begin (); hbonds.end () != hbfIt; ++hbfIt)
    {
      hbfIt->hbond.reassignResiduePointers (newSet);
    }
  }

  
  bool
  Relation::annotate () 
  {
    this->areAdjacent ();
    this->areStacked ();
    this->arePaired ();

    //     TODO: fix areHBonded method
    //
    //     if (! is (PropertyType::pPairing))
    //       areHBonded ();

    return !this->empty ();
  }
  
  
  void
  Relation::areAdjacent ()
  {
    Residue::const_iterator up, down;
    const PropertyType * adj_type = PropertyType::pNull;
    
    if (this->ref->end () != (down = this->ref->find (AtomType::aO3p)) &&
	this->res->end () != (up = this->res->find (AtomType::aP)) &&
	down->squareDistance (*up) <= Relation::adjacency_distance_cutoff_square)
      adj_type = PropertyType::pAdjacent5p;
    else if (this->res->end () != (down = this->res->find (AtomType::aO3p)) &&
	     this->ref->end () != (up = this->ref->find (AtomType::aP)) &&
	     down->squareDistance (*up) <= Relation::adjacency_distance_cutoff_square)
      adj_type = PropertyType::pAdjacent3p;
    else if (this->ref->end () != (down = this->ref->find (AtomType::aC)) &&
	     this->res->end () != (up = this->res->find (AtomType::aN)) &&
	     down->squareDistance (*up) <= Relation::adjacency_distance_cutoff_square)
      adj_type = PropertyType::pAdjacent5p;
    else if (this->res->end () != (down = this->res->find (AtomType::aC)) &&
	     this->ref->end () != (up = this->ref->find (AtomType::aN)) &&
	     down->squareDistance (*up) <= Relation::adjacency_distance_cutoff_square)
      adj_type = PropertyType::pAdjacent3p;

    if (adj_type != PropertyType::pNull)
    {
      this->labels.insert (adj_type);
      this->type_asp |= Relation::adjacent_mask;
    }
    
    /*
      Compute relative transfo to place phosphate form ref base.
      Only in adjacent nucleic acids.
    */
    
    po4_tfo.setIdentity ();
    
    if (this->ref->getType ()->isNucleicAcid () &&
	this->res->getType ()->isNucleicAcid () &&
	adj_type->isAdjacent ())
      try
      {
	// fetch phosphate residue depending on adjacency direction
	ResId rid;
	Residue pRes (ResidueType::rPhosphate, rid);
	  
	pRes.setType (ResidueType::rPhosphate);

	if (adj_type->is (PropertyType::pAdjacent5p))
	{
	  pRes.insert (*this->ref->safeFind (AtomType::aO3p));
	  pRes.insert (*this->res->safeFind (AtomType::aP));
	  pRes.insert (*this->res->safeFind (AtomType::aO1P));
	  pRes.insert (*this->res->safeFind (AtomType::aO2P));
	  pRes.insert (*this->res->safeFind (AtomType::aO5p));
	}
	else if (adj_type->is (PropertyType::pAdjacent3p))
	{
	  pRes.insert (*this->res->safeFind (AtomType::aO3p));
	  pRes.insert (*this->ref->safeFind (AtomType::aP));
	  pRes.insert (*this->ref->safeFind (AtomType::aO1P));
	  pRes.insert (*this->ref->safeFind (AtomType::aO2P));
	  pRes.insert (*this->ref->safeFind (AtomType::aO5p));
	}
	else
	{
	  IntLibException ex ("", __FILE__, __LINE__);
	  ex << "adjacent type \"" << adj_type << "\" not handled";
	  throw ex;
	}

	pRes.finalize ();
	this->po4_tfo = this->ref->getReferential ().invert () * pRes.getReferential ();
      }
      catch (IntLibException& ex)
      {
	gOut (3) << "unable to compute phosphate transfo in adjacent relation: " << ex << endl;
	this->po4_tfo.setIdentity ();
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
    AtomSetSideChain as_sidechain;

    for (i = ref->begin (as_sidechain); i != ref->end (); ++i)
    {
      if (i->getType ()->isNitrogen () || i->getType ()->isOxygen ())
      {
	for (j = res->begin (as_sidechain); j != res->end (); ++j)
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
	      labels.insert (PropertyType::parseType (str));
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
    typedef MaximumFlowGraph< unsigned int, HBond > HBondFlowGraph;
    typedef map< Residue::const_iterator, unsigned int > AtomToInt;

    try
    {
      Residue::const_iterator i;
      Residue::const_iterator j;
      Residue::const_iterator k;
      Residue::const_iterator l;
      AtomToInt atomToInt;
      unsigned int node;
      HBondFlowGraph graph;
      vector< Residue::const_iterator > ref_at;
      vector< Residue::const_iterator > refn_at;
      vector< Residue::const_iterator > res_at;
      vector< Residue::const_iterator > resn_at;
      vector< Residue::const_iterator >::size_type x;
      vector< Residue::const_iterator >::size_type y;
      AtomSetAnd da (new AtomSetSideChain (), 
		     new AtomSetNot (new AtomSetOr (new AtomSetAtom (AtomType::a2H5M), 
						    new AtomSetAtom (AtomType::a3H5M))));
	
      node = 0;
      graph.insert (node++, 1); // Source
      graph.insert (node++, 1); // Sink

      for (i = ref->begin (da); i != ref->end (); ++i)
      {
	if ((i->getType ()->isCarbon ()
	     || i->getType ()->isNitrogen ()
	     || i->getType ()->isOxygen ()))
	{
	  for (j = ref->begin (da); j != ref->end (); ++j)
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
      
      for (i = res->begin (da); i != res->end (); ++i)
      {
	if ((i->getType ()->isCarbon ()
	     || i->getType ()->isNitrogen ()
	     || i->getType ()->isOxygen ()))
	{
	  for (j = res->begin (da); j != res->end (); ++j)
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
	
      for (x = 0; x < ref_at.size (); ++x)
      {
	i = ref_at[x];
	j = refn_at[x];
	for (y = 0; y < res_at.size (); ++y)
	{
	  k = res_at[y];
	  l = resn_at[y];
	      
	  if (i->getType ()->isHydrogen () && k->getType ()->isLonePair ())
	  {
	    HBond h (j->getType (), i->getType (), l->getType (), k->getType ());
		  
	    h.evalStatistically (ref, res);
	    if (h.getValue () > 0.01)
	    {
	      HBond fake (1);
	      pair< AtomToInt::iterator, bool > iIt = atomToInt.insert (make_pair (i, node));

	      if (iIt.second)
	      {
		graph.insert (node, 1);
		graph.internalConnect (0, node, fake, 0);
		++node;
	      }
	      pair< AtomToInt::iterator, bool > kIt = atomToInt.insert (make_pair (k, node));
	      if (kIt.second)
	      {
		graph.insert (node, 1);
		graph.internalConnect (node, 1, fake, 0);
		++node;
	      }
	      graph.internalConnect (iIt.first->second, kIt.first->second, h, 0);
	    }
	  }
	  else if (k->getType ()->isHydrogen () && i->getType ()->isLonePair ())
	  {
	    HBond h (l->getType (), k->getType (), j->getType (), i->getType ());
		  
	    h.evalStatistically (res, ref);
	    if (h.getValue () > 0.01)
	    {
	      HBond fake (1);
	      pair< AtomToInt::iterator, bool > kIt = atomToInt.insert (make_pair (k, node));
			
	      if (kIt.second)
	      {
		graph.insert (node, 1);
		graph.internalConnect (0, node, fake, 0);
		++node;
	      }
	      pair< AtomToInt::iterator, bool > iIt = atomToInt.insert (make_pair (i, node));
	      if (iIt.second)
	      {
		graph.insert (node, 1);
		graph.internalConnect (node, 1, fake, 0);
		++node;
	      }
	      graph.internalConnect (kIt.first->second, iIt.first->second, h, 0);
	    }
	  }
	}
      }

      gOut (5) << graph << endl;
	
      if (graph.size () >= 3)
      {
	HBondFlowGraph::size_type label;

	graph.preFlowPush (0, 1);
	    
	gOut (5) << graph << endl;

	for (label = 0; label < graph.edgeSize (); ++label)
	{
	  HBond &hbond = graph.internalGetEdge (label);

	  if (0 != hbond.getDonorType ())
	  {
	    float flow;

	    flow = graph.internalGetEdgeWeight (label);
	    sum_flow += flow;
	    hbonds.push_back (HBondFlow (hbond, flow));
	  }
	}

	gOut (4) << "Sum flow = " << sum_flow << endl;
	    
	if (sum_flow >= PAIRING_CUTOFF)
	{
	  this->type_asp |= Relation::pairing_mask;
	  addPairingLabels ();
	}

      }
      else
      {
	hbonds.clear ();
	gOut (4) << "MaximumFlowGraph.size () = " << graph.size () << endl;
      }
    }
    catch (IntLibException& ex)
    {
      gOut (3) << "An error occured during pairing annotation: " << ex << endl;
    }
  }


  void
  Relation::addPairingLabels ()
  {
    Vector3D pa;
    Vector3D pb;
    Vector3D pc;
    Vector3D pd;
    Vector3D pva;
    Vector3D pvb;
    list< HBondFlow > hbf (hbonds.begin (), hbonds.end ());
    vector< HBondFlow >::iterator hbIt;
    float rad;
    unsigned int size_hint;
    const PropertyType *pp;

    labels.insert (PropertyType::pPairing);
    if (sum_flow < TWO_BONDS_CUTOFF)
    {
      labels.insert (PropertyType::pOneHbond);
    }
		
    // Compute contact points and visual contact points
    for (hbIt = hbonds.begin (); hbonds.end () != hbIt; ++hbIt)
    {
      HBondFlow &fl = *hbIt;
		    
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
			
    pa = pa / sum_flow;
    pb = pb / sum_flow;
    pva = pva / sum_flow;
    pvb = pvb / sum_flow;
	      
    pc = *ref->safeFind (AtomType::aC1p); 
    pc = pc - *ref->safeFind (AtomType::aPSY);
    pc = pc + pa;
    pd = *res->safeFind (AtomType::aC1p); 
    pd = pd - *res->safeFind (AtomType::aPSY);
    pd = pd + pb;
	      
    // -- cis/trans orientation
    rad = fabs (pa.torsionAngle (pc, pb, pd));
    labels.insert (rad < M_PI / 2 ? PropertyType::pCis : PropertyType::pTrans);
	      
    // -- straight/reverse orientation
    labels.insert (Relation::_pyrimidine_ring_normal
		   (*this->ref, Relation::_pyrimidine_ring_center (*this->ref)).dot
		   (Relation::_pyrimidine_ring_normal
		    (*this->res, Relation::_pyrimidine_ring_center (*this->res))) > 0 ?
		   PropertyType::pStraight : PropertyType::pReverse);

    refFace = getFace (ref, pa);
    resFace = getFace (res, pb);
	      
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
    while (hbf.size () != size_hint)
    {
      hbf.pop_front ();
    }
    if (0 != (pp = translatePairing (ref, res, hbf, sum_flow, size_hint)))
    {
      labels.insert (pp);
    }

  }
  
  


  void
  Relation::areStacked_old ()
  {
    static const float STACK_DISTANCE_CUTOFF = 4.50f;
    static const float STACK_NORMAL_CUTOFF   = 0.61f; // 35 deg
    static const float STACK_OVERLAP_CUTOFF  = 0.61f; // 35 deg
    
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
    catch (IntLibException& ex)
    {
      gOut (3) << "An error occured during stacking annotation: " << ex << endl;
    }
    
  }


  Vector3D
  Relation::_pyrimidine_ring_center (const Residue& res)
  {
    return (*(res.safeFind (AtomType::aN1)) + *(res.safeFind (AtomType::aC2)) +
	    *(res.safeFind (AtomType::aN3)) + *(res.safeFind (AtomType::aC4)) +
	    *(res.safeFind (AtomType::aC5)) + *(res.safeFind (AtomType::aC6))) / 6.0;
  }


  Vector3D
  Relation::_imidazole_ring_center (const Residue& res)
  {
    return (*(res.safeFind (AtomType::aC4)) + *(res.safeFind (AtomType::aC5)) +
	    *(res.safeFind (AtomType::aN7)) + *(res.safeFind (AtomType::aC8)) +
	    *(res.safeFind (AtomType::aN9))) / 5.0;
  }

  
  Vector3D
  Relation::_pyrimidine_ring_normal (const Residue& res, const Vector3D& center)
  {
    Vector3D r1 = (((*(res.safeFind (AtomType::aN1)) - center) * 1) +
		   ((*(res.safeFind (AtomType::aC2)) - center) * 0.5) +
		   ((*(res.safeFind (AtomType::aN3)) - center) * -0.5) +
		   ((*(res.safeFind (AtomType::aC4)) - center) * -1) +
		   ((*(res.safeFind (AtomType::aC5)) - center) * -0.5) +
		   ((*(res.safeFind (AtomType::aC6)) - center) * 0.5));
    
    Vector3D r2 = (((*(res.safeFind (AtomType::aC2)) - center) * 0.8660254) +
		   ((*(res.safeFind (AtomType::aN3)) - center) * 0.8660254) +
		   ((*(res.safeFind (AtomType::aC5)) - center) * -0.8660254) +
		   ((*(res.safeFind (AtomType::aC6)) - center) * -0.8660254));

    if (res.getType ()->isPurine ())
      return -(r1.cross (r2).normalize ());

    return r1.cross (r2).normalize ();
  }

  
  Vector3D
  Relation::_imidazole_ring_normal (const Residue& res, const Vector3D& center)
  {
    Vector3D r1 = (((*(res.safeFind (AtomType::aC4)) - center) * 1) +
		   ((*(res.safeFind (AtomType::aC5)) - center) * 0.30901699) +
		   ((*(res.safeFind (AtomType::aN7)) - center) * -0.80901699) +
		   ((*(res.safeFind (AtomType::aC8)) - center) * -0.80901699) +
		   ((*(res.safeFind (AtomType::aN9)) - center) * 0.30901699));

    Vector3D r2 = (((*(res.safeFind (AtomType::aC5)) - center) * 0.95105652) +
		   ((*(res.safeFind (AtomType::aN7)) - center) * 0.58778525) +
		   ((*(res.safeFind (AtomType::aC8)) - center) * -0.58778525) +
		   ((*(res.safeFind (AtomType::aN9)) - center) * -0.95105652));

    return r1.cross (r2).normalize ();
  }
  
  
  const PropertyType*
  Relation::_ring_stacking (const Vector3D& centerA, const Vector3D& normalA,
			    const Vector3D& centerB, const Vector3D& normalB)
  {
    float theta1, theta2;

    /*
      00 (0) straight upward   (default)
      01 (1) straight downward
      10 (2) reverse  upward
      11 (3) reverse  downward
    */
    unsigned int annotation = 0; 
    
    // - check ring center distance
    
    if (centerA.squareDistance (centerB) > Relation::stack_distance_cutoff_square)
      return PropertyType::pNull;

    // - check ring normal angle (symetrical)    

    theta1 = acos (normalA.dot (normalB));

    if (theta1 > Relation::stack_tilt_cutoff)
    {
      if ((float)M_PI - theta1 < Relation::stack_tilt_cutoff)
	annotation = 2;
      else
	return PropertyType::pNull;
    }

    // - check ring overlap
    //   -> not symetrical, thus we say stack if any direction is satisfying.
    
    Vector3D vAB = (centerB - centerA).normalize ();
    theta1 = acos (normalA.dot (vAB));

    if (theta1 > Relation::stack_overlap_cutoff)
    {
      if ((float)M_PI - theta1 < Relation::stack_overlap_cutoff)
	annotation |= 1;
      else
      {
	// try from other base point of view
	theta2 = acos (normalB.dot (vAB));

	if (theta2 < Relation::stack_overlap_cutoff ||
	    (float)M_PI - theta2 < Relation::stack_overlap_cutoff)
	{
	  if (theta1 > M_PI_2)
	    annotation |= 1;
	}
	else
	  return PropertyType::pNull;
      }
    }

    this->type_asp |= Relation::stacking_mask;
    
    switch (annotation)
    {
    case 0:
      return PropertyType::pStraightUpward;
    case 1:
      return PropertyType::pStraightDownward;
    case 2:
      return PropertyType::pReverseUpward;
    case 3:
      return PropertyType::pReverseDownward;
    default:
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "invalid stacking annotation value " << annotation;
      throw ex;
    }

    return PropertyType::pNull;
  }
  
  
  void
  Relation::areStacked ()
  {
    try
    {
      Vector3D pyrCA, pyrCB, imidCA, imidCB, pyrNA, pyrNB, imidNA, imidNB;
      const PropertyType* stacking;
      unsigned char rtypes;

      /*
	Compute necessary geometry based on type family:

	00 (0) => Pur / Pur: imid / imid, imid / -pyr, -pyr / imid, -pyr / -pyr
	01 (1) => Pur / Pyr:              imid /  pyr,              -pyr /  pyr
	10 (2) => Pyr / Pur:                            pyr / imid,  pyr / -pyr
	11 (3) => Pyr / Pyr:                                         pyr /  pyr
      */
      
      pyrCA = Relation::_pyrimidine_ring_center (*this->ref);
      pyrNA = Relation::_pyrimidine_ring_normal (*this->ref, pyrCA);
      
      pyrCB = Relation::_pyrimidine_ring_center (*this->res);
      pyrNB = Relation::_pyrimidine_ring_normal (*this->res, pyrCB);
      
      if (this->ref->getType ()->isPurine ())
      {
	rtypes = 0;
	//pyrNA = -pyrNA;
	imidCA = Relation::_imidazole_ring_center (*this->ref);
	imidNA = Relation::_imidazole_ring_normal (*this->ref, imidCA);
      }
      else if (this->ref->getType ()->isPyrimidine ())
      {
	rtypes = 2;
      }
      else
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "Type \"" << this->ref->getType () << "\" not handled for residue"
	   << this->ref->getResId ();
	throw ex;
      }
      
      if (this->res->getType ()->isPurine ())
      {
	//pyrNB = -pyrNB;
	imidCB = Relation::_imidazole_ring_center (*this->res);
	imidNB = Relation::_imidazole_ring_normal (*this->res, imidCB);
      }
      else if (this->res->getType ()->isPyrimidine ())
      {
	rtypes |= 1;
      }
      else
      {
	IntLibException ex ("", __FILE__, __LINE__);
	ex << "Type \"" << this->res->getType () << "\" not handled for residue"
	   << this->res->getResId ();
	throw ex;
      }

      // pyrimidine / pyrimidine
      stacking = Relation::_ring_stacking (pyrCA, pyrNA, pyrCB, pyrNB);

      // imidazole / pyrimidine
      if (PropertyType::pNull == stacking && (1 == rtypes || 0 == rtypes))
	stacking = Relation::_ring_stacking (imidCA, imidNA, pyrCB, pyrNB);

      // pyrimidine / imidazole
      if (PropertyType::pNull == stacking && (2 == rtypes || 0 == rtypes))
	stacking = Relation::_ring_stacking (pyrCA, pyrNA, imidCB, imidNB);

      // imidazole / imidazole
      if (PropertyType::pNull == stacking && 0 == rtypes)
	stacking = Relation::_ring_stacking (imidCA, imidNA, imidCB, imidNB);

      if (PropertyType::pNull != stacking)
	labels.insert (stacking);
    }
    catch (IntLibException& ex)
    {
      gOut (3) << "An error occured during stacking annotation: " << ex << endl;
    }
  }
  

  //   Relation
  //   Relation::invert () const
  //   {
  //     Relation inv;
  //     inv.ref = res;
  //     inv.res = ref;
  //     inv.tfo = tfo.invert ();
  //     inv.po4_tfo = inv.tfo * po4_tfo;
  //     inv.refFace = resFace;
  //     inv.resFace = refFace;
  //     for (set< const PropertyType* >::const_iterator i=labels.begin (); i!=labels.end (); ++i) {
  //       if (*i == PropertyType::pDIR_5p) inv.labels.insert (PropertyType::pDIR_3p);
  //       else if (*i == PropertyType::pDIR_3p) inv.labels.insert (PropertyType::pDIR_5p);
  //       else inv.labels.insert (*i);
  //     }
  //     return inv;
  //   }
  

  Relation&
  Relation::invert ()
  {
    const Residue* rt;
    const PropertyType* pt;
    set< const PropertyType* > lt;
    set< const PropertyType* >::const_iterator it;

    // -- invert residues and faces
    rt = this->ref;
    this->ref = this->res;
    this->res = rt;
    pt = this->refFace;
    this->refFace = this->resFace;
    this->resFace = pt;

    // -- invert transfos
    this->tfo = this->tfo.invert ();
    this->po4_tfo = this->tfo * this->po4_tfo;

    // -- invert labels
    for (it = this->labels.begin (); it != this->labels.end (); ++it) 
      lt.insert (PropertyType::invert (*it));
    this->labels = lt;
    
    return *this;
  }


  // I/O -----------------------------------------------------------------------


  ostream&
  Relation::write (ostream &os) const
  {
    if (ref != 0 && res != 0)
    {
      os << "{" 
	 << ref->getResId () << ref->getType () << " -> " 
	 << res->getResId () << res->getType () << ": ";
      copy (labels.begin (), labels.end (), ostream_iterator< const PropertyType* > (os, " "));
      if (is (PropertyType::pPairing))
      {
	os << " " << refFace << "/" << resFace;
      }
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
  Relation::arePaired (const Residue *ra, const Residue *rb, const PropertyType *pta, const PropertyType *ptb)
  {
    Relation rel (ra, rb);

    rel.arePaired ();
    pta = rel.getRefFace ();
    ptb = rel.getResFace ();
    return rel.getLabels ();
  }

  
  set< const PropertyType* >
  Relation::areStacked (const Residue *ra, const Residue *rb)
  {
    Relation rel (ra, rb);

    rel.areStacked ();
    return rel.getLabels ();
  }
  

  set< const PropertyType* > 
  Relation::areStacked_old (const Residue* ra, const Residue *rb)
  {
    Relation rel (ra, rb);

    rel.areStacked_old ();
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
  Relation::getFace (const Residue *r, const Vector3D &p)
  {

    if (!Relation::face_init)
      Relation::init ();

    HomogeneousTransfo t;
    t = r->getReferential ();
    t = t.invert ();
    Vector3D pp = t * p;
    vector< pair< Vector3D, const PropertyType* > > *faces = 0;

    if (r->getType ()->isA ())
    {
      faces = &faces_A;
    }
    else if (r->getType ()->isC ())
    {
      faces = &faces_C;
    }
    else if (r->getType ()->isG ())
    {
      faces = &faces_G;
    }
    else if (r->getType ()->isU ())
    {
      faces = &faces_U;
    }
    else if (r->getType ()->isT ())
    {
      faces = &faces_T;
    }

    int face_index = 0;
    unsigned int x;
    float dist = numeric_limits< float >::max ();
    
    for (x = 0; x < faces->size (); ++x)
    {
      float tmp = pp.distance ((*faces)[x].first);
      if (tmp < dist)
      {
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
      ExtendedResidue C (ResidueType::rRC, ResId ('C', 1));
      ExtendedResidue G (ResidueType::rRG, ResId ('G', 1));
      ExtendedResidue U (ResidueType::rRU, ResId ('U', 1));
      ExtendedResidue T (ResidueType::rDT, ResId ('T', 1));

      A.setTheoretical ();
      ta = *A.safeFind (AtomType::aH8);	
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("C8")));
      ta = (*A.safeFind (AtomType::aH8) + *A.safeFind (AtomType::aLP7)) / 2;	
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*A.safeFind (AtomType::a2H6) + *A.safeFind (AtomType::aLP7)) / 2;
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *A.safeFind (AtomType::a2H6);
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*A.safeFind (AtomType::a1H6) + *A.safeFind (AtomType::a2H6)) / 2;
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *A.safeFind (AtomType::a1H6);
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*A.safeFind (AtomType::aLP1) + *A.safeFind (AtomType::a1H6)) / 2;
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*A.safeFind (AtomType::aLP1) + *A.safeFind (AtomType::aH2)) / 2;
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *A.safeFind (AtomType::aH2);
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = (*A.safeFind (AtomType::aH2) + *A.safeFind (AtomType::aLP3)) / 2;
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
      ta = *A.safeFind (AtomType::aLP3);
      Relation::faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

      C.setTheoretical ();
      ta = *C.safeFind (AtomType::aH6);
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*C.safeFind (AtomType::a1H4) + *C.safeFind (AtomType::aH5)) / 2;
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *C.safeFind (AtomType::a1H4);
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*C.safeFind (AtomType::a1H4) + *C.safeFind (AtomType::a2H4)) / 2;
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *C.safeFind (AtomType::a2H4);
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*C.safeFind (AtomType::a2H4) + *C.safeFind (AtomType::aLP3)) / 2;
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*C.safeFind (AtomType::aLP3) + *C.safeFind (AtomType::a2LP2)) / 2;
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *C.safeFind (AtomType::a2LP2);
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*C.safeFind (AtomType::a2LP2) + *C.safeFind (AtomType::a1LP2)) / 2;
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *C.safeFind (AtomType::a1LP2);
      Relation::faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

      G.setTheoretical ();
      ta = *G.safeFind (AtomType::aH8);
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("C8")));
      ta = (*G.safeFind (AtomType::aH8) + *G.safeFind (AtomType::aLP7)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*G.safeFind (AtomType::a1LP6) + *G.safeFind (AtomType::aLP7)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *G.safeFind (AtomType::a1LP6);
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*G.safeFind (AtomType::a1LP6) + *G.safeFind (AtomType::a2LP6)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *G.safeFind (AtomType::a2LP6);
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*G.safeFind (AtomType::a2LP6) + *G.safeFind (AtomType::aH1)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*G.safeFind (AtomType::aH1) + *G.safeFind (AtomType::a2H2)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *G.safeFind (AtomType::a2H2);
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*G.safeFind (AtomType::a2H2) + *G.safeFind (AtomType::a1H2)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *G.safeFind (AtomType::a1H2);
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Sw")));
      ta = (*G.safeFind (AtomType::a1H2) + *G.safeFind (AtomType::aLP3)) / 2;
      Relation::faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
      U.setTheoretical ();
      ta = *U.safeFind (AtomType::aH6);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*U.safeFind (AtomType::a1LP4) + *U.safeFind (AtomType::aH5)) / 2;
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *U.safeFind (AtomType::a1LP4);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*U.safeFind (AtomType::a1LP4) + *U.safeFind (AtomType::a2LP4)) / 2;
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *U.safeFind (AtomType::a2LP4);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*U.safeFind (AtomType::a2LP4) + *U.safeFind (AtomType::aH3)) / 2;
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *U.safeFind (AtomType::aH3);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*U.safeFind (AtomType::a2LP2) + *U.safeFind (AtomType::aH3)) / 2;
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = *U.safeFind (AtomType::a2LP2);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*U.safeFind (AtomType::a2LP2) + *U.safeFind (AtomType::a1LP2)) / 2;
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *U.safeFind (AtomType::a1LP2);
      Relation::faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
      T.setTheoretical ();
      ta = *T.safeFind (AtomType::aH6);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = (*T.safeFind (AtomType::a1LP4) + *T.safeFind (AtomType::aC5M)) / 2;
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
      ta = *T.safeFind (AtomType::a1LP4);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
      ta = (*T.safeFind (AtomType::a1LP4) + *T.safeFind (AtomType::a2LP4)) / 2;
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
      ta = *T.safeFind (AtomType::a2LP4);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
      ta = (*T.safeFind (AtomType::a2LP4) + *T.safeFind (AtomType::aH3)) / 2;
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = *T.safeFind (AtomType::aH3);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
      ta = (*T.safeFind (AtomType::a2LP2) + *T.safeFind (AtomType::aH3)) / 2;
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = *T.safeFind (AtomType::a2LP2);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
      ta = (*T.safeFind (AtomType::a2LP2) + *T.safeFind (AtomType::a1LP2)) / 2;
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
      ta = *T.safeFind (AtomType::a1LP2);
      Relation::faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
 
      Relation::face_init = true;
    }
    catch (IntLibException& ex)
    {
      FatalIntLibException fex ("", __FILE__, __LINE__);
      fex << "failed to initialize faces in relation: " << ex.what ();
      throw fex;
    }
    
  }


  const PropertyType* 
  Relation::translatePairing (const Residue *ra, const Residue *rb, list< HBondFlow > &hbf, float total_flow, unsigned int size_hint)
  {
    list< PairingPattern >::const_iterator i;
    const PropertyType *type;
    const PropertyType *best_type = 0;
    unsigned int best_size = 0;

    for (i = PairingPattern::patternList ().begin ();
	 i != PairingPattern::patternList().end ();
	 ++i)
    {
      if (size_hint >= (*i).size ()
	  && (type = (*i).evaluate (ra, rb, hbf)) != 0)
      {
	if ((*i).size () > best_size)
	{
	  best_size = (*i).size ();
	  best_type = type;
	}
      }
    }
    return best_type;
  }
  
}


namespace std
{
  
  ostream& operator<< (ostream &os, const mccore::Relation &r)
  {
    return r.write (os);
  }

  
  ostream& operator<< (ostream &os, const mccore::Relation *r)
  {
    return r->write (os);
  }
  
}
