//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.7 $

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

    stringType["Adenine"] = t = ResidueType::rA = new A ("A", "ADE"); 
    stringType["A"] = t = ResidueType::rRA = new RA ("A", "RA"); 
    stringType["ADE"] = t; 
    stringType["RA"] = t; 
    stringType["RA5"] = t; 
    stringType["RA3"] = t; 
    stringType["DA"] = t = ResidueType::rDA = new DA ("A", "DA");
    stringType["DA5"] = t; 
    stringType["DA3"] = t; 
    
    stringType["Cytosine"] = t = ResidueType::rC = new C ("C", "CYT");
    stringType["C"] = t = ResidueType::rRC = new RC ("C", "RC");
    stringType["CYT"] = t; 
    stringType["RC"] = t; 
    stringType["RC5"] = t; 
    stringType["RC3"] = t; 
    stringType["DC"] = t = ResidueType::rDC = new DC ("C", "DC");
    stringType["DC5"] = t; 
    stringType["DC3"] = t; 
    
    stringType["Guanine"] = t = ResidueType::rG = new G ("G", "GUA"); 
    stringType["G"] = t = ResidueType::rRG = new RG ("G", "RG"); 
    stringType["GUA"] = t;
    stringType["RG"] = t; 
    stringType["RG5"] = t; 
    stringType["RG3"] = t; 
    stringType["DG"] = t = ResidueType::rDG = new DG ("G", "DG");
    stringType["DG5"] = t; 
    stringType["DG3"] = t; 
    
    stringType["Uracyle"] = t = ResidueType::rU = new U ("U", "URA");
    stringType["U"] = t = ResidueType::rRU = new RU ("U", "RU"); 
    stringType["RU"] = t;
    stringType["URI"] = t; 
    stringType["URA"] = t; 
    stringType["RU5"] = t; 
    stringType["RU3"] = t; 
    
    stringType["Thymine"] = t = ResidueType::rT = new T ("T", "TYM"); 
    stringType["T"] = t = ResidueType::rDT = new DT ("T", "DT"); 
    stringType["DT"] = t;
    stringType["TYM"] = t; 
    stringType["DT5"] = t; 
    stringType["DT3"] = t; 
    
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

    stringType["N"] = ResidueType::rNucleicAcid = new NucleicAcid ("(N)", "(N)");
    stringType["RN"] = ResidueType::rNucleicAcid = new NucleicAcid ("(RN)", "(RN)");
    stringType["DN"] = ResidueType::rNucleicAcid = new NucleicAcid ("(DN)", "(DN)");
    stringType["W"] = ResidueType::rW = new W ("(W)", "(W)");
    stringType["RW"] = ResidueType::rRW = new RW ("(RW)", "(RW)");
    stringType["DW"] = ResidueType::rDW = new DW ("(DW)", "(DW)");
    stringType["S"] = ResidueType::rS = new S ("(S)", "(S)");
    stringType["RS"] = ResidueType::rRS = new RS ("(RS)", "(RS)");
    stringType["DS"] = ResidueType::rDS = new DS ("(DS)", "(DS)");
    stringType["M"] = ResidueType::rM = new M ("(M)", "(M)");
    stringType["RM"] = ResidueType::rRM = new RM ("(RM)", "(RM)");
    stringType["DM"] = ResidueType::rDM = new DM ("(DM)", "(DM)");
    stringType["K"] = ResidueType::rK = new K ("(K)", "(K)");
    stringType["RK"] = ResidueType::rRK = new RK ("(RK)", "(RK)");
    stringType["DK"] = ResidueType::rDK = new DK ("(DK)", "(DK)");
    stringType["B"] = ResidueType::rB = new B ("(B)", "(B)");
    stringType["RB"] = ResidueType::rRB = new RB ("(RB)", "(RB)");
    stringType["DB"] = ResidueType::rDB = new DB ("(DB)", "(DB)");
    stringType["D"] = ResidueType::rD = new D ("(D)", "(D)");
    stringType["RD"] = ResidueType::rRD = new RD ("(RD)", "(RD)");
    stringType["DD"] = ResidueType::rDD = new DD ("(DD)", "(DD)");
    stringType["H"] = ResidueType::rH = new H ("(H)", "(H)");
    stringType["RH"] = ResidueType::rRH = new RH ("(RH)", "(RH)");
    stringType["DH"] = ResidueType::rDH = new DH ("(DH)", "(DH)");
    stringType["V"] = ResidueType::rV = new V ("(V)", "(V)");
    stringType["RV"] = ResidueType::rRV = new RV ("(RV)", "(RV)");
    stringType["DV"] = ResidueType::rDV = new DV ("(DV)", "(DV)");
    
    stringType["RNA"] = ResidueType::rRNA = new RNA ("(RNA)", "(RNA)");
    stringType["DNA"] = ResidueType::rDNA = new DNA ("(DNA)", "(DNA)");
    stringType["PO4"] = ResidueType::rPhosphate = new Phosphate ("(PO4)", "(Phosphate)");
    stringType["RIB"] = ResidueType::rRibose = new Ribose ("(RIB)", "(Ribose)");
    stringType["R"] = ResidueType::rPurine = new Purine ("(R)", "(R)");
    stringType["RR"] = ResidueType::rRPurine = new RPurine ("(RR)", "(RR)");
    stringType["DR"] = ResidueType::rDPurine = new DPurine ("(DR)", "(DR)");
    stringType["Y"] = ResidueType::rPyrimidine = new Pyrimidine ("(Y)", "(Y)");
    stringType["RY"] = ResidueType::rRPyrimidine = new RPyrimidine ("(RY)", "(RY)");
    stringType["DY"] = ResidueType::rDPyrimidine = new DPyrimidine ("(DY)", "(DY)");


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
  ResidueTypeStore::get (const char* s) 
  {
    ResidueType* t = 0;
    char* str = new char[strlen (s) + 1];
    strcpy (str, s);
    for (char* i=str; *i; ++i) {
      *i = toupper (*i);
    }
    
    if (stringType.find (str) != stringType.end ()) {
      t = stringType[str];
    } else {
      t = new ResidueType (str, str);
      stringType[*t] = t;      
    }
    delete[] str;
    return t;
  } 


  const ResidueType* 
  ResidueTypeStore::getInvalid (const char* s) 
  {
    ResidueType* t = 0;
    char* str = new char[strlen (s) + 1];
    strcpy (str, s);
    for (char* i=str; *i; ++i) {
      *i = toupper (*i);
    }
    
    if (invalidType.find (str) != invalidType.end ()) {
      t = invalidType[str];
    } else {
      t = new ResidueType (str, str);
      invalidType[*t] = t;      
    }
    delete[] str;
    return t;
  } 


}
