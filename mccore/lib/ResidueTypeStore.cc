//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.16 $

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "ResidueTypeStore.h"

namespace mccore {

  // LIFECYCLE -----------------------------------------------------------------

  ResidueTypeStore::ResidueTypeStore () 
  {
    ResidueType *t;

    stringType[""] = ResidueType::rNull = new ResidueType ("", "");
    
    /** nucleic acids **/
    
    /*
      N:? generic nucleic acid type variety for ?
      R:? RNA type variety for ?
      D:? DNA type variety for ?
    */
    
    stringType["Adenine"] = t = ResidueType::rA = new A ("A", "ADE");
    stringType["N:A"] = t;
    stringType["A"] = t = ResidueType::rRA = new RA ("A", "R:A"); 
    stringType["ADE"] = t; 
    stringType["R:A"] = t;
    stringType["D:A"] = t = ResidueType::rDA = new DA ("A", "D:A");
    stringType["RA"] = new RRA ("RA", "R:RA");
    stringType["RA5"] = new RRA5 ("RA5", "R:RA5");
    stringType["RA3"] = new RRA3 ("RA3", "R:RA3");
    stringType["DA"] = new DDA ("DA", "D:DA");
    stringType["DA5"] = new DDA5 ("DA5", "D:DA5");
    stringType["DA3"] = new DDA3 ("DA3", "D:DA3");
    
    stringType["Cytosine"] = t = ResidueType::rC = new C ("C", "CYT");
    stringType["N:C"] = t;
    stringType["C"] = t = ResidueType::rRC = new RC ("C", "R:C");
    stringType["CYT"] = t; 
    stringType["R:C"] = t; 
    stringType["D:C"] = t = ResidueType::rDC = new DC ("C", "D:C");
    stringType["RC"] = new RRC ("RC", "R:RC");
    stringType["RC5"] = new RRC5 ("RC5", "R:RC5");
    stringType["RC3"] = new RRC3 ("RC3", "R:RC3");
    stringType["DC"] = new DDC ("DC", "D:DC");
    stringType["DC5"] = new DDC5 ("DC5", "D:DC5");
    stringType["DC3"] = new DDC3 ("DC3", "D:DC3");
    
    stringType["Guanine"] = t = ResidueType::rG = new G ("G", "GUA");
    stringType["N:G"] = t;
    stringType["G"] = t = ResidueType::rRG = new RG ("G", "R:G"); 
    stringType["GUA"] = t;
    stringType["R:G"] = t; 
    stringType["D:G"] = t = ResidueType::rDG = new DG ("G", "D:G");
    stringType["RG"] = new RRG ("RG", "R:RG");
    stringType["RG5"] = new RRG5 ("RG5", "R:RG5");
    stringType["RG3"] = new RRG3 ("RG3", "R:RG3");
    stringType["DG"] = new DDG ("DG", "D:DG");
    stringType["DG5"] = new DDG5 ("DG5", "D:DG5");
    stringType["DG3"] = new DDG3 ("DG3", "D:DG3");
    
    stringType["Uracyle"] = t = ResidueType::rU = new U ("U", "URA");
    stringType["N:U"] = t;
    stringType["U"] = t = ResidueType::rRU = new RU ("U", "R:U"); 
    stringType["R:U"] = t;
    stringType["URI"] = t; 
    stringType["URA"] = t; 
    stringType["RU"] = new RRU ("RU", "R:RC");
    stringType["RU5"] = new RRU5 ("RU5", "R:RU5");
    stringType["RU3"] = new RRU3 ("RU3", "R:RU3");
    
    stringType["Thymine"] = t = ResidueType::rT = new T ("T", "TYM");
    stringType["N:T"] = t;
    stringType["T"] = t = ResidueType::rDT = new DT ("T", "D:T"); 
    stringType["D:T"] = t;
    stringType["TYM"] = t; 
    stringType["DT"] = new DDT ("DT", "D:DT");
    stringType["DT5"] = new DDT5 ("DT5", "D:DT5");
    stringType["DT3"] = new DDT3 ("DT3", "D:DT3");
    
    stringType["(N:N)"] = ResidueType::rNucleicAcid = new N ("(N:N)", "(N:N)");
    stringType["(R:N)"] = ResidueType::rRNA = new RN ("(R:N)", "(R:N)");
    stringType["(D:N)"] = ResidueType::rDNA = new DN ("(D:N)", "(D:N)");

    stringType["(N:B)"] = ResidueType::rB = new B ("(B)", "(B)");
    stringType["(R:B)"] = ResidueType::rRB = new RB ("(R:B)", "(R:B)");
    stringType["(D:B)"] = ResidueType::rDB = new DB ("(D:B)", "(D:B)");
    stringType["(N:D)"] = ResidueType::rD = new D ("(D)", "(D)");
    stringType["(R:D)"] = ResidueType::rRD = new RD ("(R:D)", "(R:D)");
    stringType["(D:D)"] = ResidueType::rDD = new DD ("(D:D)", "(D:D)");
    stringType["(N:H)"] = ResidueType::rH = new H ("(H)", "(H)");
    stringType["(R:H)"] = ResidueType::rRH = new RH ("(R:H)", "(R:H)");
    stringType["(D:H)"] = ResidueType::rDH = new DH ("(D:H)", "(D:H)");
    stringType["(N:V)"] = ResidueType::rV = new V ("(V)", "(V)");
    stringType["(R:V)"] = ResidueType::rRV = new RV ("(R:V)", "(R:V)");
    stringType["(D:V)"] = ResidueType::rDV = new DV ("(D:V)", "(D:V)");

    stringType["(N:R)"] = ResidueType::rPurine = new Purine ("(R)", "(R)");
    stringType["(R:R)"] = ResidueType::rRPurine = new RPurine ("(R:R)", "(R:R)");
    stringType["(D:R)"] = ResidueType::rDPurine = new DPurine ("(D:R)", "(D:R)");
    stringType["(N:Y)"] = ResidueType::rPyrimidine = new Pyrimidine ("(Y)", "(Y)");
    stringType["(R:Y)"] = ResidueType::rRPyrimidine = new RPyrimidine ("(R:Y)", "(R:Y)");
    stringType["(D:Y)"] = ResidueType::rDPyrimidine = new DPyrimidine ("(D:Y)", "(D:Y)");
    stringType["(N:W)"] = ResidueType::rW = new W ("(W)", "(W)");
    stringType["(R:W)"] = ResidueType::rRW = new RW ("(R:W)", "(R:W)");
    stringType["(D:W)"] = ResidueType::rDW = new DW ("(D:W)", "(D:W)");
    stringType["(N:S)"] = ResidueType::rS = new S ("(S)", "(S)");
    stringType["(R:S)"] = ResidueType::rRS = new RS ("(R:S)", "(R:S)");
    stringType["(D:S)"] = ResidueType::rDS = new DS ("(D:S)", "(D:S)");
    stringType["(N:M)"] = ResidueType::rM = new M ("(M)", "(M)");
    stringType["(R:M)"] = ResidueType::rRM = new RM ("(R:M)", "(R:M)");
    stringType["(D:M)"] = ResidueType::rDM = new DM ("(D:M)", "(D:M)");
    stringType["(N:K)"] = ResidueType::rK = new K ("(K)", "(K)");
    stringType["(R:K)"] = ResidueType::rRK = new RK ("(R:K)", "(R:K)");
    stringType["(D:K)"] = ResidueType::rDK = new DK ("(D:K)", "(D:K)");

    /** specialized residue types **/
    
    stringType["(PO4)"]     = ResidueType::rPhosphate = new Phosphate ("(PO4)", "(PO4)");
    stringType["(R:RIB)"]   = ResidueType::rRRibose   = new RRibose   ("(R:RIB)", "(R:RIB)");
    stringType["(R:RIB5)"]  = ResidueType::rRRibose5  = new RRibose5  ("(R:RIB5)", "(R:RIB5)");
    stringType["(R:RIB3)"]  = ResidueType::rRRibose3  = new RRibose3  ("(R:RIB3)", "(R:RIB3)");
    stringType["(R:RIB53)"] = ResidueType::rRRibose53 = new RRibose53 ("(R:RIB53)", "(R:RIB53)");
    stringType["(D:RIB)"]   = ResidueType::rDRibose   = new DRibose   ("(D:RIB)", "(D:RIB)");
    stringType["(D:RIB5)"]  = ResidueType::rDRibose5  = new DRibose5  ("(D:RIB5)", "(D:RIB5)");
    stringType["(D:RIB3)"]  = ResidueType::rDRibose3  = new DRibose3  ("(D:RIB3)", "(D:RIB3)");
    stringType["(D:RIB53)"] = ResidueType::rDRibose53 = new DRibose53 ("(D:RIB53)", "(D:RIB53)");
    
    /** amino acid **/
    
    stringType["AminoAcid"] = ResidueType::rAminoAcid = new AminoAcid ("(AA)", "(AA)");
    stringType["ALA"] = ResidueType::rALA = new ALA ("A", "ALA");
    stringType["PA"] = ResidueType::rALA;
    stringType["ARG"] = ResidueType::rARG = new ARG ("R", "ARG");
    stringType["PR"] = ResidueType::rARG;
    stringType["ASN"] = ResidueType::rASN = new ASN ("N", "ASN");
    stringType["PN"] = ResidueType::rASN;
    stringType["ASP"] = ResidueType::rASP = new ASP ("D", "ASP");
    stringType["PD"] = ResidueType::rASP;
    stringType["CYS"] = ResidueType::rCYS = new CYS ("C", "CYS");
    stringType["PC"] = ResidueType::rCYS;
    stringType["GLN"] = ResidueType::rGLN = new GLN ("Q", "GLN");
    stringType["PQ"] = ResidueType::rGLN;
    stringType["GLU"] = ResidueType::rGLU = new GLU ("E", "GLU");
    stringType["PE"] = ResidueType::rGLU;
    stringType["GLY"] = ResidueType::rGLY = new GLY ("G", "GLY");
    stringType["PG"] = ResidueType::rGLY;
    stringType["HIS"] = ResidueType::rHIS = new HIS ("H", "HIS");
    stringType["PH"] = ResidueType::rHIS;
    stringType["ILE"] = ResidueType::rILE = new ILE ("I", "ILE");
    stringType["PI"] = ResidueType::rILE;
    stringType["LEU"] = ResidueType::rLEU = new LEU ("L", "LEU");
    stringType["PL"] = ResidueType::rLEU;
    stringType["LYS"] = ResidueType::rLYS = new LYS ("K", "LYS");
    stringType["PK"] = ResidueType::rLYS;
    stringType["MET"] = ResidueType::rMET = new MET ("M", "MET");
    stringType["PM"] = ResidueType::rMET;
    stringType["PHE"] = ResidueType::rPHE = new PHE ("F", "PHE");
    stringType["PF"] = ResidueType::rPHE;
    stringType["PRO"] = ResidueType::rPRO = new PRO ("P", "PRO");
    stringType["PP"] = ResidueType::rPRO;
    stringType["SER"] = ResidueType::rSER = new SER ("S", "SER");
    stringType["PS"] = ResidueType::rSER;
    stringType["THR"] = ResidueType::rTHR = new THR ("T", "THR");
    stringType["PT"] = ResidueType::rTHR;
    stringType["TRP"] = ResidueType::rTRP = new TRP ("W", "TRP");
    stringType["PW"] = ResidueType::rTRP;
    stringType["TYR"] = ResidueType::rTYR = new TYR ("Y", "TYR");
    stringType["PY"] = ResidueType::rTYR;
    stringType["VAL"] = ResidueType::rVAL = new VAL ("V", "VAL");	
    stringType["PV"] = ResidueType::rVAL;
  }


  ResidueTypeStore::~ResidueTypeStore () 
  {
    set< ResidueType* > bag;
    map< const char*, ResidueType*, less_string >::iterator i;
    set< ResidueType* >::iterator j;

    for (i=stringType.begin (); i!=stringType.end (); ++i) {
      bag.insert (i->second);
    }
    for (i=invalidType.begin (); i!=invalidType.end (); ++i) {
      bag.insert (i->second);
    }
    for (j=bag.begin (); j!=bag.end (); ++j) {
      delete *j;
    }
    bag.clear ();
  }
    
    // METHODS -----------------------------------------------------------------
    
  const ResidueType* 
  ResidueTypeStore::get (const char* key) 
  {
    char* key_copy = strdup (key);
    char* kp;

    for (kp = key_copy; 0 != *kp; ++kp)
      *kp = toupper (*kp);

    pair< map< const char*, ResidueType*, less_string >::iterator, bool > inserted =
      stringType.insert (make_pair (key_copy, ResidueType::rNull));

    if (inserted.second) // unique insertion => new atom type
      inserted.first->second = new ResidueType (inserted.first->first, inserted.first->first);
    else                 // key exists => delete key copy
      free (key_copy);

    return inserted.first->second;
  } 


  const ResidueType* 
  ResidueTypeStore::getInvalid (const char* key) 
  {
    char* key_copy = strdup (key);
    char* kp;

    for (kp = key_copy; 0 != *kp; ++kp)
      *kp = toupper (*kp);

    pair< map< const char*, ResidueType*, less_string >::iterator, bool > inserted =
      invalidType.insert (make_pair (key_copy, ResidueType::rNull));

    if (inserted.second) // unique insertion => new atom type
      inserted.first->second = new ResidueType (inserted.first->first, inserted.first->first);
    else                 // key exists => delete key copy
      delete[] key_copy;

    return inserted.first->second;
  } 


}
