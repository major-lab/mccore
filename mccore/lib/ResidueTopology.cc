//                              -*- Mode: C++ -*- 
// ResidueTopology.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Mar 21 15:30:27 2003
// Last Modified By : Philippe Thibault
// Last Modified On : Thu Dec  9 14:53:24 2004
// Update Count     : 33
// Status           : Unknown.
// 



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ResidueTopology.h"
#include "AtomType.h"
#include "ResidueType.h"
#include "ResidueTopology.h"

namespace mccore {

  map< const ResidueType*, UndirectedGraph< const AtomType* > >
  ResidueTopology::topologies;
  

  const UndirectedGraph< const AtomType* >* 
  ResidueTopology::get (const ResidueType* type) 
  {
    bool isKnown = true;
    if (topologies.find (type) == topologies.end ())
      isKnown = init (type);
    if (isKnown) return &topologies[type];
    else return 0;
  }


  bool
  ResidueTopology::init (const ResidueType* type) 
  {
    if (type == ResidueType::rRA)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::aH2p);
	g.insert(AtomType::aO2p);
	g.insert(AtomType::aHO2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aLP1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aH2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aN6);
	g.insert(AtomType::a1H6);
	g.insert(AtomType::a2H6);
	g.insert(AtomType::aN7);
	g.insert(AtomType::aLP7);
	g.insert(AtomType::aC8);
	g.insert(AtomType::aH8);
	g.insert(AtomType::aN9);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::aH2p);
	g.connect (AtomType::aC2p, AtomType::aO2p);
	g.connect (AtomType::aO2p, AtomType::aHO2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN9, AtomType::aC1p);
	
	// SIDECHAIN
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aH2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aN9);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aN7);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aN6);
	g.connect (AtomType::aN6, AtomType::a1H6);
	g.connect (AtomType::aN6, AtomType::a2H6);
	g.connect (AtomType::aN7, AtomType::aC8);
	g.connect (AtomType::aC8, AtomType::aN9);
	g.connect (AtomType::aC8, AtomType::aH8);
	
	g.connect (AtomType::aLP1, AtomType::aN1);
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::aLP7, AtomType::aN7);
	
	return true;
      }
    else if (type == ResidueType::rRC)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::aH2p);
	g.insert(AtomType::aO2p);
	g.insert(AtomType::aHO2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aO2);
	g.insert(AtomType::a1LP2);
	g.insert(AtomType::a2LP2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aN4);
	g.insert(AtomType::a1H4);
	g.insert(AtomType::a2H4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aH5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aH6);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::aH2p);
	g.connect (AtomType::aC2p, AtomType::aO2p);
	g.connect (AtomType::aO2p, AtomType::aHO2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN1, AtomType::aC1p);
	
	//SIDECHAIN	   
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aO2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aN4);
	g.connect (AtomType::aN4, AtomType::a1H4);
	g.connect (AtomType::aN4, AtomType::a2H4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC5, AtomType::aH5);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC6, AtomType::aH6);
	g.connect (AtomType::aC6, AtomType::aN1);
	
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::a1LP2, AtomType::aO2);
	g.connect (AtomType::a2LP2, AtomType::aO2);
	
	return true;
      }
    else if (type == ResidueType::rRG)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::aH2p);
	g.insert(AtomType::aO2p);
	g.insert(AtomType::aHO2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aH1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aN2);
	g.insert(AtomType::a1H2);
	g.insert(AtomType::a2H2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aO6);
	g.insert(AtomType::a1LP6);
	g.insert(AtomType::a2LP6);
	g.insert(AtomType::aN7);
	g.insert(AtomType::aLP7);
	g.insert(AtomType::aC8);
	g.insert(AtomType::aH8);
	g.insert(AtomType::aN9);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::aH2p);
	g.connect (AtomType::aC2p, AtomType::aO2p);
	g.connect (AtomType::aO2p, AtomType::aHO2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);

	g.connect (AtomType::aN9, AtomType::aC1p);
	
	// SIDECHAIN
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aN1, AtomType::aH1);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aN2);
	g.connect (AtomType::aN2, AtomType::a1H2);
	g.connect (AtomType::aN2, AtomType::a2H2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aN9);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aN7);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aO6);
	g.connect (AtomType::aN7, AtomType::aC8);
	g.connect (AtomType::aC8, AtomType::aN9);
	g.connect (AtomType::aC8, AtomType::aH8);
	
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::a1LP6, AtomType::aO6);
	g.connect (AtomType::a2LP6, AtomType::aO6);
	g.connect (AtomType::aLP7, AtomType::aN7);
	
	return true;
      }
    else if (type == ResidueType::rRU)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::aH2p);
	g.insert(AtomType::aO2p);
	g.insert(AtomType::aHO2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aO2);
	g.insert(AtomType::a1LP2);
	g.insert(AtomType::a2LP2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aH3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aO4);
	g.insert(AtomType::a1LP4);
	g.insert(AtomType::a2LP4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aH5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aH6);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::aH2p);
	g.connect (AtomType::aC2p, AtomType::aO2p);
	g.connect (AtomType::aO2p, AtomType::aHO2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);

	g.connect (AtomType::aN1, AtomType::aC1p);
	
	//SIDECHAIN	   
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aO2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aN3, AtomType::aH3);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aO4);	    
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aH5);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aH6);
	
	g.connect (AtomType::a1LP2, AtomType::aO2);
	g.connect (AtomType::a2LP2, AtomType::aO2);
	g.connect (AtomType::a1LP4, AtomType::aO4);
	g.connect (AtomType::a2LP4, AtomType::aO4);
	
	return true;
      }      
    else if (type == ResidueType::rDA)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::a1H2p);
	g.insert(AtomType::a2H2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aLP1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aH2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aN6);
	g.insert(AtomType::a1H6);
	g.insert(AtomType::a2H6);
	g.insert(AtomType::aN7);
	g.insert(AtomType::aLP7);
	g.insert(AtomType::aC8);
	g.insert(AtomType::aH8);
	g.insert(AtomType::aN9);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::a1H2p);
	g.connect (AtomType::aC2p, AtomType::a2H2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN9, AtomType::aC1p);
	
	// SIDECHAIN
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aH2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aN9);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aN7);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aN6);
	g.connect (AtomType::aN6, AtomType::a1H6);
	g.connect (AtomType::aN6, AtomType::a2H6);
	g.connect (AtomType::aN7, AtomType::aC8);
	g.connect (AtomType::aC8, AtomType::aN9);
	g.connect (AtomType::aC8, AtomType::aH8);
	
	g.connect (AtomType::aLP1, AtomType::aN1);
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::aLP7, AtomType::aN7);
	
	return true;
      }
    else if (type == ResidueType::rDC)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::a1H2p);
	g.insert(AtomType::a2H2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aO2);
	g.insert(AtomType::a1LP2);
	g.insert(AtomType::a2LP2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aN4);
	g.insert(AtomType::a1H4);
	g.insert(AtomType::a2H4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aH5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aH6);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::a1H2p);
	g.connect (AtomType::aC2p, AtomType::a2H2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN1, AtomType::aC1p);
	
	// SIDECHAIN
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aO2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aN4);
	g.connect (AtomType::aN4, AtomType::a1H4);
	g.connect (AtomType::aN4, AtomType::a2H4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC5, AtomType::aH5);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC6, AtomType::aH6);
	g.connect (AtomType::aC6, AtomType::aN1);
	
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::a1LP2, AtomType::aO2);
	g.connect (AtomType::a2LP2, AtomType::aO2);
	
	return true;
      }
    else if (type == ResidueType::rDG)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::a1H2p);
	g.insert(AtomType::a2H2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aH1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aN2);
	g.insert(AtomType::a1H2);
	g.insert(AtomType::a2H2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aLP3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aO6);
	g.insert(AtomType::a1LP6);
	g.insert(AtomType::a2LP6);
	g.insert(AtomType::aN7);
	g.insert(AtomType::aLP7);
	g.insert(AtomType::aC8);
	g.insert(AtomType::aH8);
	g.insert(AtomType::aN9);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::a1H2p);
	g.connect (AtomType::aC2p, AtomType::a2H2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN9, AtomType::aC1p);
	
	// SIDECHAIN
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aN1, AtomType::aH1);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aN2);
	g.connect (AtomType::aN2, AtomType::a1H2);
	g.connect (AtomType::aN2, AtomType::a2H2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aN9);
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aN7);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aO6);
	g.connect (AtomType::aN7, AtomType::aC8);
	g.connect (AtomType::aC8, AtomType::aN9);
	g.connect (AtomType::aC8, AtomType::aH8);
	
	g.connect (AtomType::aLP3, AtomType::aN3);
	g.connect (AtomType::a1LP6, AtomType::aO6);
	g.connect (AtomType::a2LP6, AtomType::aO6);
	g.connect (AtomType::aLP7, AtomType::aN7);
	
	return true;
      }
    else if (type == ResidueType::rDT)
      {
	UndirectedGraph< const AtomType* > &g = topologies[type];
	
	g.insert(AtomType::aC1p);
	g.insert(AtomType::aH1p);
	g.insert(AtomType::aC2p);
	g.insert(AtomType::a1H2p);
	g.insert(AtomType::a2H2p);
	g.insert(AtomType::aC3p);
	g.insert(AtomType::aH3p);
	g.insert(AtomType::aO3p);
	g.insert(AtomType::aHO3p);
	g.insert(AtomType::aC4p);
	g.insert(AtomType::aH4p);
	g.insert(AtomType::aC5p);
	g.insert(AtomType::a1H5p);
	g.insert(AtomType::a2H5p);
	g.insert(AtomType::aO5p);
	g.insert(AtomType::aO4p);

	g.insert(AtomType::aO1P);
	g.insert(AtomType::aO2P);
	g.insert(AtomType::aP);
	
	g.insert(AtomType::aN1);
	g.insert(AtomType::aC2);
	g.insert(AtomType::aO2);
	g.insert(AtomType::a1LP2);
	g.insert(AtomType::a2LP2);
	g.insert(AtomType::aN3);
	g.insert(AtomType::aH3);
	g.insert(AtomType::aC4);
	g.insert(AtomType::aO4);
	g.insert(AtomType::a1LP4);
	g.insert(AtomType::a2LP4);
	g.insert(AtomType::aC5);
	g.insert(AtomType::aC5M);
	g.insert(AtomType::a1H5M);
	g.insert(AtomType::a2H5M);
	g.insert(AtomType::a3H5M);
	g.insert(AtomType::aC6);
	g.insert(AtomType::aH6);
	
	// BACKBONE
	g.connect (AtomType::aC1p, AtomType::aC2p);
	g.connect (AtomType::aC1p, AtomType::aH1p);	    
	g.connect (AtomType::aC2p, AtomType::aC3p);
	g.connect (AtomType::aC2p, AtomType::a1H2p);
	g.connect (AtomType::aC2p, AtomType::a2H2p);
	g.connect (AtomType::aC3p, AtomType::aC4p);
	g.connect (AtomType::aC3p, AtomType::aH3p);
	g.connect (AtomType::aC3p, AtomType::aO3p);
	g.connect (AtomType::aO3p, AtomType::aHO3p);
	g.connect (AtomType::aC4p, AtomType::aO4p);
	g.connect (AtomType::aC4p, AtomType::aH4p);
	g.connect (AtomType::aC4p, AtomType::aC5p);	    
	g.connect (AtomType::aC5p, AtomType::aO5p);	    
	g.connect (AtomType::aC5p, AtomType::a1H5p);
	g.connect (AtomType::aC5p, AtomType::a2H5p);
	g.connect (AtomType::aO5p, AtomType::aP);
	g.connect (AtomType::aP, AtomType::aO1P);
	g.connect (AtomType::aP, AtomType::aO2P);
	g.connect (AtomType::aO4p, AtomType::aC1p);
	
	g.connect (AtomType::aN1, AtomType::aC1p);
	
	//SIDECHAIN	   
	g.connect (AtomType::aN1, AtomType::aC2);
	g.connect (AtomType::aC2, AtomType::aN3);
	g.connect (AtomType::aC2, AtomType::aO2);
	g.connect (AtomType::aN3, AtomType::aC4);
	g.connect (AtomType::aN3, AtomType::aH3);
	g.connect (AtomType::aC4, AtomType::aC5);
	g.connect (AtomType::aC4, AtomType::aO4);	    
	g.connect (AtomType::aC5, AtomType::aC6);
	g.connect (AtomType::aC5, AtomType::aC5M);
	g.connect (AtomType::aC5M, AtomType::a1H5M);
	g.connect (AtomType::aC5M, AtomType::a2H5M);
	g.connect (AtomType::aC5M, AtomType::a3H5M);
	g.connect (AtomType::aC6, AtomType::aN1);
	g.connect (AtomType::aC6, AtomType::aH6);
	
	g.connect (AtomType::a1LP2, AtomType::aO2);
	g.connect (AtomType::a2LP2, AtomType::aO2);
	g.connect (AtomType::a1LP4, AtomType::aO4);
	g.connect (AtomType::a2LP4, AtomType::aO4);
	
	return true;
      }      
    return false;
  }
  
  
  
  set< const AtomType* >
  ResidueTopology::getOblSet (const ResidueType* type)
  {
    static const AtomType* DAOblSet[24] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aC8,
	(const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN3,					    
	(const AtomType*)AtomType::aN6,  (const AtomType*)AtomType::aN7,
	(const AtomType*)AtomType::aN9,  (const AtomType*)AtomType::aO1P,
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,					    
	(const AtomType*)AtomType::aO4p, (const AtomType*)AtomType::aO5p,
	(const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSX,
	(const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ
      };
    
    static const AtomType* RAOblSet[25] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aC8,
	(const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN3,					    
	(const AtomType*)AtomType::aN6,  (const AtomType*)AtomType::aN7,
	(const AtomType*)AtomType::aN9,  (const AtomType*)AtomType::aO1P,
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO2p,					    
	(const AtomType*)AtomType::aO3p, (const AtomType*)AtomType::aO4p,
	(const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,
	(const AtomType*)AtomType::aPSX, (const AtomType*)AtomType::aPSY,
	(const AtomType*)AtomType::aPSZ
      };

    static const AtomType* DCOblSet[22] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,
	(const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN4,					    
	(const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,
	(const AtomType*)AtomType::aO4p, (const AtomType*)AtomType::aO5p,					    
	(const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSX,
	(const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ
      };

    static const AtomType* RCOblSet[23] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,
	(const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN4,					    
	(const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO2p,
	(const AtomType*)AtomType::aO3p, (const AtomType*)AtomType::aO4p,					    
	(const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,
	(const AtomType*)AtomType::aPSX, (const AtomType*)AtomType::aPSY,
	(const AtomType*)AtomType::aPSZ
      };

    static const AtomType* DGOblSet[25] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,  
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p, 
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p, 
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p, 
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aC8,  
	(const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN2,
	(const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN7,  
	(const AtomType*)AtomType::aN9,  (const AtomType*)AtomType::aO1P, 
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,
	(const AtomType*)AtomType::aO4p, (const AtomType*)AtomType::aO5p, 
	(const AtomType*)AtomType::aO6,  (const AtomType*)AtomType::aP,   
	(const AtomType*)AtomType::aPSX, (const AtomType*)AtomType::aPSY,
	(const AtomType*)AtomType::aPSZ
      };

    static const AtomType* RGOblSet[26] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aC8,
	(const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN2,					    
	(const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN7,
	(const AtomType*)AtomType::aN9,  (const AtomType*)AtomType::aO1P,
	(const AtomType*)AtomType::aO2p, (const AtomType*)AtomType::aO2P,					    
	(const AtomType*)AtomType::aO3p, (const AtomType*)AtomType::aO4p,
	(const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aO6,
	(const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSX,					    
	(const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ
      };

    static const AtomType* DTOblSet[23] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
	(const AtomType*)AtomType::aC5M, (const AtomType*)AtomType::aC6,
	(const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN3,					    
	(const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,
	(const AtomType*)AtomType::aO4,  (const AtomType*)AtomType::aO4p,					    
	(const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,
	(const AtomType*)AtomType::aPSX, (const AtomType*)AtomType::aPSY,
	(const AtomType*)AtomType::aPSZ
      };

    static const AtomType* RUOblSet[23] =
      {
	(const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,  
	(const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p, 
	(const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,
	(const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p, 
	(const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,  
	(const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aO1P,
	(const AtomType*)AtomType::aO2,  (const AtomType*)AtomType::aO2p, 
	(const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p, 
	(const AtomType*)AtomType::aO4,  (const AtomType*)AtomType::aO4p,
	(const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,   
	(const AtomType*)AtomType::aPSX, (const AtomType*)AtomType::aPSY,
	(const AtomType*)AtomType::aPSZ
      };

    static const AtomType* ALAOblSet[5]  = { (const AtomType*)AtomType::aN,  (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,  (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB};

    static const AtomType* ARGOblSet[11] = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD,   (const AtomType*)AtomType::aNE,
					     (const AtomType*)AtomType::aCZ,   (const AtomType*)AtomType::aNH1,
					     (const AtomType*)AtomType::aNH2 };

    static const AtomType* ASNOblSet[8]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,					    
					     (const AtomType*)AtomType::aOD1,  (const AtomType*)AtomType::aND2 };

    static const AtomType* ASPOblSet[8]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aOD1,  (const AtomType*)AtomType::aOD2 };

    static const AtomType* CYSOblSet[6]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aSG };

    static const AtomType* GLNOblSet[9]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD,   (const AtomType*)AtomType::aOE1,  
					     (const AtomType*)AtomType::aNE2 };

    static const AtomType* GLUOblSet[9]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD,   (const AtomType*)AtomType::aOE1,  
					     (const AtomType*)AtomType::aOE2 };

    static const AtomType* GLYOblSet[4]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA };

    static const AtomType* HISOblSet[10] = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     
					     (const AtomType*)AtomType::aND1,  (const AtomType*)AtomType::aCD2,
					     (const AtomType*)AtomType::aCE1,  (const AtomType*)AtomType::aNE2 };

    static const AtomType* ILEOblSet[8]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aCD1,
					     (const AtomType*)AtomType::aC,    (const AtomType*)AtomType::aO,
					     (const AtomType*)AtomType::aCA,   (const AtomType*)AtomType::aCB,
					     (const AtomType*)AtomType::aCG1,  (const AtomType*)AtomType::aCG2 };

    static const AtomType* LEUOblSet[8]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD1,  (const AtomType*)AtomType::aCD2 };

    static const AtomType* LYSOblSet[9]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD,   (const AtomType*)AtomType::aCE,   
					     (const AtomType*)AtomType::aNZ };

    static const AtomType* METOblSet[8]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aSD,   (const AtomType*)AtomType::aCE };

    static const AtomType* PHEOblSet[11] = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,					     
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,					     
					     (const AtomType*)AtomType::aCD1,  (const AtomType*)AtomType::aCD2,
					     (const AtomType*)AtomType::aCE1,  (const AtomType*)AtomType::aCE2,
					     (const AtomType*)AtomType::aCZ };

    static const AtomType* PROOblSet[7]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,					     
					     (const AtomType*)AtomType::aCD };

    static const AtomType* SEROblSet[6]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aOG };

    static const AtomType* THROblSet[7]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aOG1, 
					     (const AtomType*)AtomType::aCG2 };

    static const AtomType* TRPOblSet[14] = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD1,  (const AtomType*)AtomType::aCD2,  
					     (const AtomType*)AtomType::aNE1,  (const AtomType*)AtomType::aCE2,  
					     (const AtomType*)AtomType::aCE3,  (const AtomType*)AtomType::aCZ2,
					     (const AtomType*)AtomType::aCZ3,  (const AtomType*)AtomType::aCH2 };

    static const AtomType* TYROblSet[12] = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG,
					     (const AtomType*)AtomType::aCD1,  (const AtomType*)AtomType::aCD2,
					     (const AtomType*)AtomType::aCE1,  (const AtomType*)AtomType::aCE2,
					     (const AtomType*)AtomType::aCZ,   (const AtomType*)AtomType::aOH };

    static const AtomType* VALOblSet[7]  = { (const AtomType*)AtomType::aN,    (const AtomType*)AtomType::aC,    
					     (const AtomType*)AtomType::aO,    (const AtomType*)AtomType::aCA,   
					     (const AtomType*)AtomType::aCB,   (const AtomType*)AtomType::aCG1,
					     (const AtomType*)AtomType::aCG2 };

    if (type == ResidueType::rDA) { return set< const AtomType* > (DAOblSet, DAOblSet + sizeof(DAOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rRA) { return set< const AtomType* > (RAOblSet, RAOblSet + sizeof(RAOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rDC) { return set< const AtomType* > (DCOblSet, DCOblSet + sizeof(DCOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rRC) { return set< const AtomType* > (RCOblSet, RCOblSet + sizeof(RCOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rDG) { return set< const AtomType* > (DGOblSet, DGOblSet + sizeof(DGOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rRG) { return set< const AtomType* > (RGOblSet, RGOblSet + sizeof(RGOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rDT) { return set< const AtomType* > (DTOblSet, DTOblSet + sizeof(DTOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rRU) { return set< const AtomType* > (RUOblSet, RUOblSet + sizeof(RUOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rALA) { return set< const AtomType* > (ALAOblSet, ALAOblSet + sizeof(ALAOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rARG) { return set< const AtomType* > (ARGOblSet, ARGOblSet + sizeof(ARGOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rASN) { return set< const AtomType* > (ASNOblSet, ASNOblSet + sizeof(ASNOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rASP) { return set< const AtomType* > (ASPOblSet, ASPOblSet + sizeof(ASPOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rCYS) { return set< const AtomType* > (CYSOblSet, CYSOblSet + sizeof(CYSOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rGLN) { return set< const AtomType* > (GLNOblSet, GLNOblSet + sizeof(GLNOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rGLU) { return set< const AtomType* > (GLUOblSet, GLUOblSet + sizeof(GLUOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rGLY) { return set< const AtomType* > (GLYOblSet, GLYOblSet + sizeof(GLYOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rHIS) { return set< const AtomType* > (HISOblSet, HISOblSet + sizeof(HISOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rILE) { return set< const AtomType* > (ILEOblSet, ILEOblSet + sizeof(ILEOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rLEU) { return set< const AtomType* > (LEUOblSet, LEUOblSet + sizeof(LEUOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rLYS) { return set< const AtomType* > (LYSOblSet, LYSOblSet + sizeof(LYSOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rMET) { return set< const AtomType* > (METOblSet, METOblSet + sizeof(METOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rPHE) { return set< const AtomType* > (PHEOblSet, PHEOblSet + sizeof(PHEOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rPRO) { return set< const AtomType* > (PROOblSet, PROOblSet + sizeof(PROOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rSER) { return set< const AtomType* > (SEROblSet, SEROblSet + sizeof(SEROblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rTHR) { return set< const AtomType* > (THROblSet, THROblSet + sizeof(THROblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rTRP) { return set< const AtomType* > (TRPOblSet, TRPOblSet + sizeof(TRPOblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rTYR) { return set< const AtomType* > (TYROblSet, TYROblSet + sizeof(TYROblSet)/sizeof(const AtomType*)); }
    if (type == ResidueType::rVAL) { return set< const AtomType* > (VALOblSet, VALOblSet + sizeof(VALOblSet)/sizeof(const AtomType*)); }
    return set< const AtomType* > ();
  }

}
