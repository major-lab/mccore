//                              -*- Mode: C++ -*- 
// Relation.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 14:47:53 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iterator>
#include <vector>

#include "Relation.h"
#include "Residue.h"
#include "PropertyType.h"
#include "UndirectedGraph.h"
#include "MaximumFlowGraph.h"
#include "ResidueTopology.h"
#include "HBond.h"
#include "ExtendedResidue.h"
#include "PairingPattern.h"

namespace mccore {


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
      refFace (0), resFace (0)
  {
  }
  
  
  Relation::Relation (const Residue *rA, const Residue *rB)
    : ref (rA), res (rB),
      refFace (0), resFace (0)
  {
    HomogeneousTransfo t;
    tfo = ref->getReferential (&t);
    tfo = tfo.invert ();
    tfo *= res->getReferential (&t);
  }

  
  Relation::Relation (const Relation &other)
    : ref (other.ref), res (other.res),
      tfo (other.tfo), refFace (other.refFace),
      resFace (other.resFace), labels (other.labels)
  {    
  }
    
  
  Relation::~Relation ()
  {
  }


  // OPERATORS ------------------------------------------------------------
  

  Relation& 
  Relation::operator= (const Relation &other)
  {
    if (this != &other) {
      ref = other.ref;
      res = other.res;
      tfo = other.tfo;
      refFace = other.refFace;
      resFace = other.resFace;
      labels = other.labels;
    }
    return *this;
  }
  

  // METHODS --------------------------------------------------------------


  bool
  Relation::annotate () 
  {
    const PropertyType *pta = 0;
    const PropertyType *ptb = 0;
    
    set< const PropertyType* > s;
    
    s = areAdjacent (ref, res);
    labels.insert (s.begin (), s.end ());
    s = areStacked (ref, res);
    labels.insert (s.begin (), s.end ());
    s = arePaired (ref, res, pta, ptb);
    labels.insert (s.begin (), s.end ());
    refFace = pta;
    resFace = ptb;

    return !empty ();
  }

  
  Relation
  Relation::invert () const
  {
    Relation inv;
    inv.ref = res;
    inv.res = ref;
    inv.tfo = tfo.invert ();
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
  Relation::output (ostream &os) const
  {
    if (ref!=0 && res!=0) {
      os << "{" 
	 << ref->getResId () << ref->getType () << " -> " 
	 << res->getResId () << res->getType () << ": ";
      copy (labels.begin (), labels.end (), ostream_iterator< const PropertyType* > (os, " "));
      if (is (PropertyType::pPairing))
	os << " " << resFace << "/" << refFace;
      os << "}";
    }	
    return os;
  }


  // STATIC METHODS ------------------------------------------------------------


  set< const PropertyType* > 
  Relation::areAdjacent (const Residue* ra, const Residue *rb)
  {
    static const float ADJACENCY_SQUARED_DISTANCE = 4.0;
    Residue::const_iterator up, down;
    
    set< const PropertyType* > s;
    
    if ((down = ra->find (AtomType::aO3p)) != ra->end ()
	&& (up = rb->find (AtomType::aP)) != rb->end () &&
	down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE) 
      {
	s.insert (PropertyType::pAdjacent);
	s.insert (PropertyType::pDIR_5p);
      } 
    else if ((down = rb->find (AtomType::aO3p)) != rb->end ()
	     && (up = ra->find (AtomType::aP)) != ra->end () &&
	     down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE) 
      {
	s.insert (PropertyType::pAdjacent);
	s.insert (PropertyType::pDIR_3p);
      } 
    else if ((down = ra->find (AtomType::aC)) != ra->end ()
	     && (up = rb->find (AtomType::aN)) != rb->end () &&
	     down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE) 
      {
	s.insert (PropertyType::pAdjacent);
	s.insert (PropertyType::pDIR_5p);
      } 
    else if ((down = rb->find (AtomType::aC)) != rb->end ()
	     && (up = ra->find (AtomType::aN)) != ra->end () &&
	     down->squareDistance (*up) <= ADJACENCY_SQUARED_DISTANCE) 
      {
	s.insert (PropertyType::pAdjacent);
	s.insert (PropertyType::pDIR_3p);
      } 
    return s;
  }


  set< const PropertyType* > 
  Relation::areStacked (const Residue* ra, const Residue *rb)
  {
    static const float STACK_DISTANCE_CUTOFF = 4.50f;
    static const float STACK_NORMAL_CUTOFF   = 0.61f; // 35 deg
    static const float STACK_OVERLAP_CUTOFF  = 0.61f; // 35 deg       

    set< const PropertyType* > ts;

    if (!(ra->getType ()->isNucleicAcid () && rb->getType ()->isNucleicAcid ()))
      return ts;
    
    Vector3D pyrCenterA;
    Vector3D pyrCenterB;
    Vector3D imidCenterA;
    Vector3D imidCenterB;
    Vector3D normalA, normalB;
    Vector3D centerV;
    
    float distance, theta1, theta2, tau1, tau2, tau3, tau4;
    float normal, overlap;
    
    // Stacking Pyr-Pyr 
    pyrCenterA = ((*(ra->find (AtomType::aN1))
		   + *(ra->find (AtomType::aC2))
		   + *(ra->find (AtomType::aN3))
		   + *(ra->find (AtomType::aC4))
		   + *(ra->find (AtomType::aC5))
		   + *(ra->find (AtomType::aC6))) / 6);
    pyrCenterB = ((*(rb->find (AtomType::aN1))
		   + *(rb->find (AtomType::aC2))
		   + *(rb->find (AtomType::aN3))
		   + *(rb->find (AtomType::aC4))
		   + *(rb->find (AtomType::aC5))
		   + *(rb->find (AtomType::aC6))) / 6);
    
    distance = pyrCenterA.distance (pyrCenterB);
    centerV = pyrCenterB - pyrCenterA;
    centerV = centerV.normalize ();
    normalA = pyrimidineNormal (ra);
    normalB = pyrimidineNormal (rb);
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
    
    if (ra->getType ()->isPurine () && rb->getType ()->isPurine ()
	|| ra->getType ()->isPyrimidine () && rb->getType ()->isPyrimidine ())
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
	&& overlap <=  STACK_OVERLAP_CUTOFF) {
      ts.insert (PropertyType::pStack);
      if (reverse) ts.insert (PropertyType::pReverse);
      return ts;
    }

    // Stacking imid-Pyr
    if (ra->getType ()->isPurine ()) {
      imidCenterA = ((*(ra->find (AtomType::aC4))
		      + *(ra->find (AtomType::aC5))
		      + *(ra->find (AtomType::aN7))
		      + *(ra->find (AtomType::aC8))
		      + *(ra->find (AtomType::aN9))) / 5);
      
      distance = imidCenterA.distance (pyrCenterB);
      centerV = pyrCenterB - imidCenterA;
      centerV = centerV.normalize ();
      normalA = imidazolNormal (ra);
      normalB = pyrimidineNormal (rb);
      theta1 = (float) acos (normalA.dot (normalB));   // this is symmetric
      theta2 = (float) acos (-normalA.dot (normalB));
      tau1 = (float) acos (normalA.dot (centerV));  // this ain't
      tau2 = (float) acos (-normalA.dot (centerV));
      tau3 = (float) acos (normalB.dot (centerV));
      tau4 = (float) acos (-normalB.dot (centerV));
      
      normal = min (theta1, theta2);
      overlap = min (min (tau1, tau2), min (tau3, tau4));
      
      if (distance <= STACK_DISTANCE_CUTOFF
	  && normal <= STACK_NORMAL_CUTOFF
	  && overlap <=  STACK_OVERLAP_CUTOFF) {
	ts.insert (PropertyType::parseType ("stack"));
	if (reverse) ts.insert (PropertyType::parseType ("reverse"));
	return ts;
      }	   	    
    }

    // Stacking Pyr-Imid
    if (rb->getType ()->isPurine ()) {
      imidCenterB = ((*(rb->find (AtomType::aC4))
		      + *(rb->find (AtomType::aC5))
		      + *(rb->find (AtomType::aN7))
		      + *(rb->find (AtomType::aC8))
		      + *(rb->find (AtomType::aN9))) / 5);
      
      distance = pyrCenterA.distance (imidCenterB);
      centerV = imidCenterB - pyrCenterA;
      centerV = centerV.normalize ();
      normalA = pyrimidineNormal (ra);
      normalB = imidazolNormal (rb);
      theta1 = (float) acos (normalA.dot (normalB));   // this is symmetric
      theta2 = (float) acos (-normalA.dot (normalB));
      tau1 = (float) acos (normalA.dot (centerV));  // this ain't
      tau2 = (float) acos (-normalA.dot (centerV));
      tau3 = (float) acos (normalB.dot (centerV));
      tau4 = (float) acos (-normalB.dot (centerV));
      
      normal = min (theta1, theta2);
      overlap = min (min (tau1, tau2), min (tau3, tau4));
      
      if (distance <= STACK_DISTANCE_CUTOFF
	  && normal <= STACK_NORMAL_CUTOFF
	  && overlap <=  STACK_OVERLAP_CUTOFF) {
	ts.insert (PropertyType::parseType ("stack"));
	if (reverse) ts.insert (PropertyType::parseType ("reverse"));
	return ts;
      }	   	    
    }
    
    // Stacking Imid-Imid
    if (ra->getType ()->isPurine () && rb->getType ()->isPurine ()) {
      distance = imidCenterA.distance (imidCenterB);
      centerV = imidCenterB - imidCenterA;
      centerV = centerV.normalize ();
      normalA = imidazolNormal (ra);
      normalB = imidazolNormal (rb);
      theta1 = (float) acos (normalA.dot (normalB));   // this is symmetric
      theta2 = (float) acos (-normalA.dot (normalB));
      tau1 = (float) acos (normalA.dot (centerV));  // this ain't
      tau2 = (float) acos (-normalA.dot (centerV));
      tau3 = (float) acos (normalB.dot (centerV));
      tau4 = (float) acos (-normalB.dot (centerV));
      
      normal = min (theta1, theta2);
      overlap = min (min (tau1, tau2), min (tau3, tau4));
      
      if (distance <= STACK_DISTANCE_CUTOFF
	  && normal <= STACK_NORMAL_CUTOFF
	  && overlap <=  STACK_OVERLAP_CUTOFF) {
	ts.insert (PropertyType::parseType ("stack"));
	if (reverse) ts.insert (PropertyType::parseType ("reverse"));
	return ts;
      }	   	    
    }	
    
    return ts;    
  }


  set< const PropertyType* > 
  Relation::arePaired (const Residue* ra, const Residue *rb, 
		       const PropertyType* &pta, const PropertyType* &ptb)
  {
    static const float PAIRING_CUTOFF = 0.8f;
    static const float TWO_BONDS_CUTOFF = 1.5f;
    static const float THREE_BONDS_CUTOFF = 2.1f;

    set< const PropertyType* > ts;

    if (!ra->getType ()->isNucleicAcid () && !rb->getType ()->isNucleicAcid ())
      return ts;
    
    Residue::const_iterator i, j, k, l;
    MaximumFlowGraph< int, HBond > graph;
    map< Residue::const_iterator, int > atomToInt; 

    int node = 0;
    graph.insert (node++); // Source
    graph.insert (node++); // Sink

    const UndirectedGraph< const AtomType* > *ga = ResidueTopology::get (ra->getType ());
    const UndirectedGraph< const AtomType* > *gb = ResidueTopology::get (rb->getType ());
    if (ga == 0 || gb == 0) return ts;
    
    vector< Residue::const_iterator > ra_at;
    vector< Residue::const_iterator > ran_at;
    vector< Residue::const_iterator > rb_at;
    vector< Residue::const_iterator > rbn_at;
    int x, y;

    AtomSet* as = new AtomSetOr (new AtomSetHydrogen (), new AtomSetLP ());
    as = new AtomSetAnd (new AtomSetSideChain (), as);

    for (i=ra->begin (as->clone ()); i!=ra->end (); ++i) {
      ra_at.push_back (i);
      ran_at.push_back (ra->find (ga->getNeighbors (i->getType ()).front ()));
    }

    for (k=rb->begin (as); k!=rb->end (); ++k) {
      rb_at.push_back (k);
      rbn_at.push_back (rb->find (gb->getNeighbors (k->getType ()).front ()));
    }
    
    for (x=0; x<(int)ra_at.size (); ++x) {
      i = ra_at[x];
      j = ran_at[x];
      for (y=0; y<(int)rb_at.size (); ++y) {
	k = rb_at[y];
	l = rbn_at[y];
	
	if (i->getType ()->isHydrogen () && k->getType ()->isLonePair ()) {
	  HBond h (j->getType (), i->getType (), l->getType (), k->getType ());
	  h.evalStatistically (*ra, *rb);
	  //h.eval (*ra, *rb);
	  if (h.getValue () > 0.01) {
	    if (atomToInt.find (i) == atomToInt.end ()) {
	      graph.insert (node);
	      graph.connect (0, node);
	      atomToInt[i] = node++;
	    }	   	   
	    if (atomToInt.find (k) == atomToInt.end ()) {
	      graph.insert (node);
	      graph.connect (node, 1);
	      atomToInt[k] = node++;
	    }
	    graph.connect (atomToInt[i], atomToInt[k], h, h.getValue ());
	  }
	} else if (k->getType ()->isHydrogen () && i->getType ()->isLonePair ()) {
	  HBond h (l->getType (), k->getType (), j->getType (), i->getType ());
	  h.evalStatistically (*rb, *ra);
	  //h.eval (*rb, *ra);
	  if (h.getValue () > 0.01) {
	    if (atomToInt.find (k) == atomToInt.end ()) {
	      graph.insert (node);
	      graph.connect (0, node);
	      atomToInt[k] = node++;
	    }
	    if (atomToInt.find (i) == atomToInt.end ()) {
	      graph.insert (node);
	      graph.connect (node, 1);
	      atomToInt[i] = node++;
	    }
	    graph.connect (atomToInt[k], atomToInt[i], h, h.getValue ());
	  }	
	} 
      }
    }


//     {
//       map< Residue::const_iterator, int >::iterator m, n;
//       for (m=atomToInt.begin (); m!=atomToInt.end (); ++m) {
// 	cout << m->second << " : " << *m->first << endl;
//       }
//     }
//     graph.output (cout);
    
    graph.preFlowPush (0, 1);
    
//     graph.output (cout);

    float sum_flow = 0;
    map< Residue::const_iterator, int >::iterator m, n;
    for (m=atomToInt.begin (); m!=atomToInt.end (); ++m) {
      for (n=atomToInt.begin (); n!=atomToInt.end (); ++n) {
	if (graph.areConnected (m->second, n->second)) {
	  sum_flow += graph.getFlow (m->second, n->second);
	}
      }
    }
    
//     cout << "Sum flow = " << sum_flow << endl;

    if (sum_flow >= PAIRING_CUTOFF) {
      ts.insert (PropertyType::pPairing);
      
      if (sum_flow < TWO_BONDS_CUTOFF)
	ts.insert (PropertyType::pOneHbond);

      
      // Compute contact points and visual contact points
      Vector3D pa;
      Vector3D pb;
      Vector3D pva;
      Vector3D pvb;
      
      list< HBondFlow > hbf;
      for (m=atomToInt.begin (); m!=atomToInt.end (); ++m) {
	for (n=atomToInt.begin (); n!=atomToInt.end (); ++n) {
	  if (graph.areConnected (m->second, n->second)) {
	    HBondFlow fl;
	    fl.hbond = graph.getEdge (m->second, n->second);
	    fl.flow = graph.getFlow (m->second, n->second);
	    hbf.push_back (fl);

	    if (fl.hbond.getDonorResidue () == ra) {
	      pa = pa + (fl.hbond.getHydrogen () * fl.flow);
	      pb = pb + (fl.hbond.getLonePair () * fl.flow);
	      pva = pva + (fl.hbond.getHydrogen () * fl.flow);
	      pvb = pvb + (fl.hbond.getAcceptor () * fl.flow);
	    } else {
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
      pc = *ra->find (AtomType::aC1p); 
      pc = pc - *ra->find (AtomType::aPSY);
      pc = pc + pa;
      pd = *rb->find (AtomType::aC1p); 
      pd = pd - *rb->find (AtomType::aPSY);
      pd = pd + pb;
      
      float rad = fabs (pa.torsionAngle (pc, pb, pd));
      PropertyType *iso = (rad<M_PI/2) ?
	PropertyType::parseType ("cis") :
	PropertyType::parseType ("trans");

      ts.insert (iso);

      pta = getFace (ra, pa);
      ptb = getFace (rb, pb);
      
      int size_hint;
      if (sum_flow >= PAIRING_CUTOFF && sum_flow < TWO_BONDS_CUTOFF) {
	size_hint = 1;
      } else if (sum_flow < THREE_BONDS_CUTOFF) {
	size_hint = 2;
      } else {
	size_hint = 3;
      }

      hbf.sort ();

      while (hbf.size () != size_hint) hbf.pop_front ();

      const PropertyType *pp = translatePairing (ra, rb, hbf, sum_flow, size_hint);

      if (pp) ts.insert (pp);
      
    }
    
    return ts;
  }  





  Vector3D 
  Relation::pyrimidineNormal (const Residue *res)
  {
    Vector3D radius1, radius2, center;
    Vector3D normal;
    
    center = ((*(res->find (AtomType::aN1))
	       + *(res->find (AtomType::aC2))
	       + *(res->find (AtomType::aN3))
	       + *(res->find (AtomType::aC4))
	       + *(res->find (AtomType::aC5))
	       + *(res->find (AtomType::aC6)))
	      / 6);
    radius1 = (((*(res->find (AtomType::aN1)) - center) * 1)
	       + ((*(res->find (AtomType::aC2)) - center) * 0.5)
	       + ((*(res->find (AtomType::aN3)) - center) * -0.5)
	       + ((*(res->find (AtomType::aC4)) - center) * -1)
	       + ((*(res->find (AtomType::aC5)) - center) * -0.5)
	       + ((*(res->find (AtomType::aC6)) - center) * 0.5));
    radius2 = (((*(res->find (AtomType::aC2)) - center) * 0.8660254)
	       + ((*(res->find (AtomType::aN3)) - center) * 0.8660254)
	       + ((*(res->find (AtomType::aC5)) - center) * -0.8660254)
	       + ((*(res->find (AtomType::aC6)) - center) * -0.8660254));
    
    normal = radius1.cross (radius2);
    return normal.normalize ();
  }



  Vector3D 
  Relation::imidazolNormal (const Residue *res)
  {
    Vector3D radius1, radius2, center;
    Vector3D normal;
    
    center = ((*(res->find (AtomType::aC4))
	       + *(res->find (AtomType::aC5))
	       + *(res->find (AtomType::aN7))
	       + *(res->find (AtomType::aC8))
	       + *(res->find (AtomType::aN9)))
	      / 5);
    
    radius1 = (((*(res->find (AtomType::aC4)) - center) * 1)
	       + ((*(res->find (AtomType::aC5)) - center) * 0.30901699)
	       + ((*(res->find (AtomType::aN7)) - center) * -0.80901699)
	       + ((*(res->find (AtomType::aC8)) - center) * -0.80901699)
	       + ((*(res->find (AtomType::aN9)) - center) * 0.30901699));
    
    radius2 = (((*(res->find (AtomType::aC5)) - center) * 0.95105652)
	       + ((*(res->find (AtomType::aN7)) - center) * 0.58778525)
	       + ((*(res->find (AtomType::aC8)) - center) * -0.58778525)
	       + ((*(res->find (AtomType::aN9)) - center) * -0.95105652));
    
    normal = radius1.cross (radius2);
    return normal.normalize ();
  }


  const PropertyType* 
  Relation::getFace (const Residue *r, const Vector3D& p)
  {
    if (!Relation::isInit) Relation::init ();

    HomogeneousTransfo tfo;
    tfo = r->getReferential (&tfo);
    tfo = tfo.invert ();
    Vector3D pp = tfo * p;

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
    Vector3D ta, tb;

    ExtendedResidue A (ResidueType::rRA, ResId ('A', 1));
    A.setIdeal ();
    A.setReferential (HomogeneousTransfo ());

    ta = *A.find (AtomType::aH8);	
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("C8")));
    ta = (*A.find (AtomType::aH8) + *A.find (AtomType::aLP7)) / 2;	
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = (*A.find (AtomType::a2H6) + *A.find (AtomType::aLP7)) / 2;
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = *A.find (AtomType::a2H6);
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
    ta = (*A.find (AtomType::a1H6) + *A.find (AtomType::a2H6)) / 2;
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
    ta = *A.find (AtomType::a1H6);
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
    ta = (*A.find (AtomType::aLP1) + *A.find (AtomType::a1H6)) / 2;
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = (*A.find (AtomType::aLP1) + *A.find (AtomType::aH2)) / 2;
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = *A.find (AtomType::aH2);
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
    ta = (*A.find (AtomType::aH2) + *A.find (AtomType::aLP3)) / 2;
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    ta = *A.find (AtomType::aLP3);
    faces_A.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

    ExtendedResidue C (ResidueType::rRC, ResId ('C', 1));
    C.setIdeal ();
    C.setReferential (HomogeneousTransfo ());

    ta = *C.find (AtomType::aH6);
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = (*C.find (AtomType::a1H4) + *C.find (AtomType::aH5)) / 2;
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = *C.find (AtomType::a1H4);
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
    ta = (*C.find (AtomType::a1H4) + *C.find (AtomType::a2H4)) / 2;
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
    ta = *C.find (AtomType::a2H4);
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
    ta = (*C.find (AtomType::a2H4) + *C.find (AtomType::aLP3)) / 2;
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = (*C.find (AtomType::aLP3) + *C.find (AtomType::a2LP2)) / 2;
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = *C.find (AtomType::a2LP2);
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = (*C.find (AtomType::a2LP2) + *C.find (AtomType::a1LP2)) / 2;
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
    ta = *C.find (AtomType::a1LP2);
    faces_C.push_back (make_pair (ta, PropertyType::parseType ("Ss")));

    ExtendedResidue G (ResidueType::rRG, ResId ('G', 1));
    G.setIdeal ();
    G.setReferential (HomogeneousTransfo ());

    ta = *G.find (AtomType::aH8);
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("C8")));
    ta = (*G.find (AtomType::aH8) + *G.find (AtomType::aLP7)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = (*G.find (AtomType::a1LP6) + *G.find (AtomType::aLP7)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = *G.find (AtomType::a1LP6);
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
    ta = (*G.find (AtomType::a1LP6) + *G.find (AtomType::a2LP6)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
    ta = *G.find (AtomType::a2LP6);
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
    ta = (*G.find (AtomType::a2LP6) + *G.find (AtomType::aH1)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = (*G.find (AtomType::aH1) + *G.find (AtomType::a2H2)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = *G.find (AtomType::a2H2);
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = (*G.find (AtomType::a2H2) + *G.find (AtomType::a1H2)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
    ta = *G.find (AtomType::a1H2);
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Sw")));
    ta = (*G.find (AtomType::a1H2) + *G.find (AtomType::aLP3)) / 2;
    faces_G.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
    ExtendedResidue U (ResidueType::rRU, ResId ('U', 1));
    U.setIdeal ();
    U.setReferential (HomogeneousTransfo ());
	
    ta = *U.find (AtomType::aH6);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = (*U.find (AtomType::a1LP4) + *U.find (AtomType::aH5)) / 2;
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = *U.find (AtomType::a1LP4);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
    ta = (*U.find (AtomType::a1LP4) + *U.find (AtomType::a2LP4)) / 2;
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
    ta = *U.find (AtomType::a2LP4);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
    ta = (*U.find (AtomType::a2LP4) + *U.find (AtomType::aH3)) / 2;
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = *U.find (AtomType::aH3);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = (*U.find (AtomType::a2LP2) + *U.find (AtomType::aH3)) / 2;
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = *U.find (AtomType::a2LP2);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = (*U.find (AtomType::a2LP2) + *U.find (AtomType::a1LP2)) / 2;
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
    ta = *U.find (AtomType::a1LP2);
    faces_U.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
    
    ExtendedResidue T (ResidueType::rDT, ResId ('T', 1));
    T.setIdeal ();
    T.setReferential (HomogeneousTransfo ());
    
    ta = *T.find (AtomType::aH6);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = (*T.find (AtomType::a1LP4) + *T.find (AtomType::aC5M)) / 2;
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hh")));
    ta = *T.find (AtomType::a1LP4);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Hw")));
    ta = (*T.find (AtomType::a1LP4) + *T.find (AtomType::a2LP4)) / 2;
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bh")));
    ta = *T.find (AtomType::a2LP4);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Wh")));
    ta = (*T.find (AtomType::a2LP4) + *T.find (AtomType::aH3)) / 2;
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = *T.find (AtomType::aH3);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ww")));
    ta = (*T.find (AtomType::a2LP2) + *T.find (AtomType::aH3)) / 2;
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = *T.find (AtomType::a2LP2);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ws")));
    ta = (*T.find (AtomType::a2LP2) + *T.find (AtomType::a1LP2)) / 2;
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Bs")));
    ta = *T.find (AtomType::a1LP2);
    faces_T.push_back (make_pair (ta, PropertyType::parseType ("Ss")));
 
    isInit = true;
  }



  const PropertyType* 
  Relation::translatePairing (const Residue* ra, const Residue *rb, 
			      list< HBondFlow > &hbf, 
			      float total_flow, int size_hint)
  {
    list< PairingPattern* >::iterator i;
    const PropertyType *type;
    const PropertyType *best_type = 0;
    int best_size = 0;

    for (i=PairingPattern::patternList().begin ();
	 i!=PairingPattern::patternList().end (); ++i) {
      if (size_hint >= (*i)->size () && 
	  (type = (*i)->evaluate (ra, rb, hbf)) != 0) {
	if ((*i)->size () > best_size) {
	  best_size = (*i)->size ();
	  best_type = type;
	}
      }
    }

    return best_type;
  }


  // NON-MEMBER FUNCTIONS ------------------------------------------------------

  ostream& operator<< (ostream &os, const Relation &r)
  {
    return r.output (os);
  }

  ostream& operator<< (ostream &os, const Relation *r)
  {
    return r->output (os);
  }
}
