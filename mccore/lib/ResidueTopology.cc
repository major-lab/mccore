//                              -*- Mode: C++ -*- 
// ResidueTopology.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Fri Mar 21 15:30:27 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Fri Mar 21 16:29:15 2003
// Update Count     : 13
// Status           : Unknown.
// 



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ResidueTopology.h"
#include "AtomType.h"
#include "ResidueType.h"


namespace mccore {

  set< const AtomType* >
  ResidueTopology::getOblSet (const ResidueType* type)
  {
    static const AtomType* DAOblSet[23] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
					    (const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
					    (const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
					    (const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
					    (const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aC8,
					    (const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN3,					    
					    (const AtomType*)AtomType::aN6,  (const AtomType*)AtomType::aN7,
					    (const AtomType*)AtomType::aN9,  (const AtomType*)AtomType::aO1P,
					    (const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,					    
					    (const AtomType*)AtomType::aO4p, (const AtomType*)AtomType::aO5p,
					    (const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSY,
					    (const AtomType*)AtomType::aPSZ };
    
    static const AtomType* RAOblSet[24] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
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
					    (const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ };

    static const AtomType* DCOblSet[21] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
					    (const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
					    (const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
					    (const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
					    (const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,
					    (const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN4,					    
					    (const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
					    (const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,
					    (const AtomType*)AtomType::aO4p, (const AtomType*)AtomType::aO5p,					    
					    (const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSY,
					    (const AtomType*)AtomType::aPSZ };

    static const AtomType* RCOblSet[22] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
					    (const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
					    (const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,
					    (const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
					    (const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,
					    (const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aN4,					    
					    (const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
					    (const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO2p,
					    (const AtomType*)AtomType::aO3p, (const AtomType*)AtomType::aO4p,					    
					    (const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,
					    (const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ };

    static const AtomType* DGOblSet[24] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,  
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
					    (const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ };

    static const AtomType* RGOblSet[25] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
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
					    (const AtomType*)AtomType::aP,   (const AtomType*)AtomType::aPSY,					    
					    (const AtomType*)AtomType::aPSZ };

    static const AtomType* DTOblSet[22] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,
					    (const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p,
					    (const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,					    
					    (const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p,
					    (const AtomType*)AtomType::aC5M, (const AtomType*)AtomType::aC6,
					    (const AtomType*)AtomType::aN1,  (const AtomType*)AtomType::aN3,					    
					    (const AtomType*)AtomType::aO1P, (const AtomType*)AtomType::aO2,
					    (const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p,
					    (const AtomType*)AtomType::aO4,  (const AtomType*)AtomType::aO4p,					    
					    (const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,
					    (const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ };

    static const AtomType* RUOblSet[22] = { (const AtomType*)AtomType::aC1p, (const AtomType*)AtomType::aC2,  
					    (const AtomType*)AtomType::aC2p, (const AtomType*)AtomType::aC3p, 
					    (const AtomType*)AtomType::aC4,  (const AtomType*)AtomType::aC4p,
					    (const AtomType*)AtomType::aC5,  (const AtomType*)AtomType::aC5p, 
					    (const AtomType*)AtomType::aC6,  (const AtomType*)AtomType::aN1,  
					    (const AtomType*)AtomType::aN3,  (const AtomType*)AtomType::aO1P,
					    (const AtomType*)AtomType::aO2,  (const AtomType*)AtomType::aO2p, 
					    (const AtomType*)AtomType::aO2P, (const AtomType*)AtomType::aO3p, 
					    (const AtomType*)AtomType::aO4,  (const AtomType*)AtomType::aO4p,
					    (const AtomType*)AtomType::aO5p, (const AtomType*)AtomType::aP,   
					    (const AtomType*)AtomType::aPSY, (const AtomType*)AtomType::aPSZ };

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
