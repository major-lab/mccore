//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright � 2003-04 Laboratoire de Biologie Informatique et Th�orique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.14 $

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
    stringType["RA5"] = t; 
    stringType["RA3"] = t; 
    stringType["D:A"] = t = ResidueType::rDA = new DA ("A", "D:A");
    stringType["DA5"] = t; 
    stringType["DA3"] = t; 
    
    stringType["Cytosine"] = t = ResidueType::rC = new C ("C", "CYT");
    stringType["N:C"] = t;
    stringType["C"] = t = ResidueType::rRC = new RC ("C", "R:C");
    stringType["CYT"] = t; 
    stringType["R:C"] = t; 
    stringType["RC5"] = t; 
    stringType["RC3"] = t; 
    stringType["D:C"] = t = ResidueType::rDC = new DC ("C", "D:C");
    stringType["DC5"] = t; 
    stringType["DC3"] = t; 
    
    stringType["Guanine"] = t = ResidueType::rG = new G ("G", "GUA");
    stringType["N:G"] = t;
    stringType["G"] = t = ResidueType::rRG = new RG ("G", "R:G"); 
    stringType["GUA"] = t;
    stringType["R:G"] = t; 
    stringType["RG5"] = t; 
    stringType["RG3"] = t; 
    stringType["D:G"] = t = ResidueType::rDG = new DG ("G", "D:G");
    stringType["DG5"] = t; 
    stringType["DG3"] = t; 
    
    stringType["Uracyle"] = t = ResidueType::rU = new U ("U", "URA");
    stringType["N:U"] = t;
    stringType["U"] = t = ResidueType::rRU = new RU ("U", "R:U"); 
    stringType["R:U"] = t;
    stringType["URI"] = t; 
    stringType["URA"] = t; 
    stringType["RU5"] = t; 
    stringType["RU3"] = t; 
    
    stringType["Thymine"] = t = ResidueType::rT = new T ("T", "TYM");
    stringType["N:T"] = t;
    stringType["T"] = t = ResidueType::rDT = new DT ("T", "D:T"); 
    stringType["D:T"] = t;
    stringType["TYM"] = t; 
    stringType["DT5"] = t; 
    stringType["DT3"] = t; 
    
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
    
    stringType["(PO4)"] = ResidueType::rPhosphate = new Phosphate ("(PO4)", "(PO4)");
    stringType["(R:RIB)"] = ResidueType::rRRibose = new DRibose ("(R:RIB)", "(R:RIB)");
    stringType["(D:RIB)"] = ResidueType::rDRibose = new RRibose ("(D:RIB)", "(D:RIB)");

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
