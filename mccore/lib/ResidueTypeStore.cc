//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.19.2.1 $

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "ResidueTypeStore.h"

namespace mccore
{

  ResidueTypeStore::ResidueTypeStore ()
  {
    ResidueType::rNull = *repository.insert (new Null (string (""), string ("null"))).first;
    ResidueType::rUnknown = *repository.insert (new Unknown (string ("UNKNOWN"), string ("Unknown"))).first;
    
    /**
     * nucleic acids
     *
     * N:? generic nucleic acid type variety for ?
     * R:? RNA type variety for ?
     * D:? DNA type variety for ?
     * ? follows IUPAC
     */
    
    ResidueType::rA  = *repository.insert (new A  (string ("N:A"), string("Adenine"))).first;
    ResidueType::rRA = *repository.insert (new RA (string ("R:A"), string("RNA_Adenine"))).first;
    ResidueType::rDA = *repository.insert (new DA (string ("D:A"), string("DNA_Adenine"))).first;
    ResidueType::rC  = *repository.insert (new C  (string ("N:C"), string("Cytosine"))).first;
    ResidueType::rRC = *repository.insert (new RC (string ("R:C"), string("RNA_Cytosine"))).first;
    ResidueType::rDC = *repository.insert (new DC (string ("D:C"), string("DNA_Cytosine"))).first;
    ResidueType::rG  = *repository.insert (new G  (string ("N:G"), string("Guanine"))).first;
    ResidueType::rRG = *repository.insert (new RG (string ("R:G"), string("RNA_Guanine"))).first;
    ResidueType::rDG = *repository.insert (new DG (string ("D:G"), string("DNA_Guanine"))).first;
    ResidueType::rT  = *repository.insert (new T  (string ("N:T"), string("Thymine"))).first;
    ResidueType::rDT = *repository.insert (new DT (string ("D:T"), string("DNA_Thymine"))).first;
    ResidueType::rU  = *repository.insert (new U  (string ("N:U"), string("Uracil"))).first;
    ResidueType::rRU = *repository.insert (new RU (string ("R:U"), string("RNA_Uracil"))).first;
    
    ResidueType::rK  = *repository.insert (new K  (string ("N:K"), string("K"))).first;
    ResidueType::rRK = *repository.insert (new RK (string ("R:K"), string("RNA_K"))).first;
    ResidueType::rDK = *repository.insert (new DK (string ("D:K"), string("DNA_K"))).first;
    ResidueType::rM  = *repository.insert (new M  (string ("N:M"), string("M"))).first;
    ResidueType::rRM = *repository.insert (new RM (string ("R:M"), string("RNA_M"))).first;
    ResidueType::rDM = *repository.insert (new DM (string ("D:M"), string("DNA_M"))).first;
    ResidueType::rS  = *repository.insert (new S  (string ("N:S"), string("S"))).first;
    ResidueType::rRS = *repository.insert (new RS (string ("R:S"), string("RNA_S"))).first;
    ResidueType::rDS = *repository.insert (new DS (string ("D:S"), string("DNA_S"))).first;
    ResidueType::rW  = *repository.insert (new W  (string ("N:W"), string("W"))).first;
    ResidueType::rRW = *repository.insert (new RW (string ("R:W"), string("RNA_W"))).first;
    ResidueType::rDW = *repository.insert (new DW (string ("D:W"), string("DNA_W"))).first;
    ResidueType::rPyrimidine  = *repository.insert (new Pyrimidine  (string ("N:Y"), string("Pyrimidine"))).first;
    ResidueType::rRPyrimidine = *repository.insert (new RPyrimidine (string ("R:Y"), string("RNA_Pyrimidine"))).first;
    ResidueType::rDPyrimidine = *repository.insert (new DPyrimidine (string ("D:Y"), string("DNA_Pyrimidine"))).first;
    ResidueType::rPurine  = *repository.insert (new Purine  (string ("N:R"), string("Purine"))).first;
    ResidueType::rRPurine = *repository.insert (new RPurine (string ("R:R"), string("RNA_Purine"))).first;
    ResidueType::rDPurine = *repository.insert (new DPurine (string ("D:R"), string("DNA_Purine"))).first;
    
    ResidueType::rB  = *repository.insert (new B  (string ("N:B"), string("B"))).first;
    ResidueType::rRB = *repository.insert (new RB (string ("R:B"), string("RNA_B"))).first;
    ResidueType::rDB = *repository.insert (new DB (string ("D:B"), string("DNA_B"))).first;
    ResidueType::rD  = *repository.insert (new D  (string ("N:D"), string("D"))).first;
    ResidueType::rRD = *repository.insert (new RD (string ("R:D"), string("RNA_D"))).first;
    ResidueType::rDD = *repository.insert (new DD (string ("D:D"), string("DNA_D"))).first;
    ResidueType::rH  = *repository.insert (new H  (string ("N:H"), string("H"))).first;
    ResidueType::rRH = *repository.insert (new RH (string ("R:H"), string("RNA_H"))).first;
    ResidueType::rDH = *repository.insert (new DH (string ("D:H"), string("DNA_H"))).first;
    ResidueType::rV  = *repository.insert (new V  (string ("N:V"), string("V"))).first;
    ResidueType::rRV = *repository.insert (new RV (string ("R:V"), string("RNA_V"))).first;
    ResidueType::rDV = *repository.insert (new DV (string ("D:V"), string("DNA_V"))).first;
    
    ResidueType::rNucleicAcid = *repository.insert (new NucleicAcid (string ("N:N"), string("N"))).first;
    ResidueType::rRNA = *repository.insert (new RNA (string ("R:N"), string("RNA_N"))).first;
    ResidueType::rDNA = *repository.insert (new DNA (string ("D:N"), string("DNA_N"))).first;
    
    /**
     * specialized residue types
     */
    
    ResidueType::rPhosphate = *repository.insert (new Phosphate (string ("PO4"), string ("Phosphate"))).first;
    ResidueType::rRRibose   = *repository.insert (new RRibose   (string ("R:RIB"), string ("RNA_Ribose"))).first;
    ResidueType::rRRibose5  = *repository.insert (new RRibose5  (string ("R:RIB5"), string ("RNA_Ribose5"))).first;
    ResidueType::rRRibose3  = *repository.insert (new RRibose3  (string ("R:RIB3"), string ("RNA_Ribose3"))).first;
    ResidueType::rRRibose53 = *repository.insert (new RRibose53 (string ("R:RIB53"), string ("RNA_Ribose53"))).first;
    ResidueType::rDRibose   = *repository.insert (new DRibose   (string ("D:RIB"), string ("DNA_Ribose"))).first;
    ResidueType::rDRibose5  = *repository.insert (new DRibose5  (string ("D:RIB5"), string ("DNA_Ribose5"))).first;
    ResidueType::rDRibose3  = *repository.insert (new DRibose3  (string ("D:RIB3"), string ("DNA_Ribose3"))).first;
    ResidueType::rDRibose53 = *repository.insert (new DRibose53 (string ("D:RIB53"), string ("DNA_Ribose53"))).first;
    
    /**
     * amino acid (IUPAC 3-letter)
     */
    
    ResidueType::rALA = *repository.insert (new ALA (string ("ALA"), string ("Alanine"))).first;
    ResidueType::rARG = *repository.insert (new ARG (string ("ARG"), string ("Arginine"))).first;
    ResidueType::rASN = *repository.insert (new ASN (string ("ASN"), string ("Asparagine"))).first;
    ResidueType::rASP = *repository.insert (new ASP (string ("ASP"), string ("Aspartic_acid"))).first;
    ResidueType::rCYS = *repository.insert (new CYS (string ("CYS"), string ("Cysteine"))).first;
    ResidueType::rGLN = *repository.insert (new GLN (string ("GLN"), string ("Glutamine"))).first;
    ResidueType::rGLU = *repository.insert (new GLU (string ("GLU"), string ("Glutamic_acid"))).first;
    ResidueType::rGLY = *repository.insert (new GLY (string ("GLY"), string ("Glycine"))).first;
    ResidueType::rHIS = *repository.insert (new HIS (string ("HIS"), string ("Histidine"))).first;
    ResidueType::rILE = *repository.insert (new ILE (string ("ILE"), string ("Isoleucine"))).first;
    ResidueType::rLEU = *repository.insert (new LEU (string ("LEU"), string ("Leucine"))).first;
    ResidueType::rLYS = *repository.insert (new LYS (string ("LYS"), string ("Lysine"))).first;
    ResidueType::rMET = *repository.insert (new MET (string ("MET"), string ("Methionine"))).first;
    ResidueType::rPHE = *repository.insert (new PHE (string ("PHE"), string ("Phenylalanine"))).first;
    ResidueType::rPRO = *repository.insert (new PRO (string ("PRO"), string ("Proline"))).first;
    ResidueType::rSER = *repository.insert (new SER (string ("SER"), string ("Serine"))).first;
    ResidueType::rTHR = *repository.insert (new THR (string ("THR"), string ("Threonine"))).first;
    ResidueType::rTRP = *repository.insert (new TRP (string ("TRP"), string ("Tryptophane"))).first;
    ResidueType::rTYR = *repository.insert (new TYR (string ("TYR"), string ("Tyrosine"))).first;
    ResidueType::rVAL = *repository.insert (new VAL (string ("VAL"), string ("Valine"))).first;
    
    ResidueType::rASX = *repository.insert (new ASX (string ("ASX"), string ("ASX"))).first;
    ResidueType::rGLX = *repository.insert (new GLX (string ("GLX"), string ("GLX"))).first;
    ResidueType::rAminoAcid = *repository.insert (new AminoAcid (string ("XAA"), string ("XAA"))).first;
    
  }
  
    
  ResidueTypeStore::~ResidueTypeStore () 
  {
    set< ResidueType*, ResidueType::less_deref >::iterator it;
    for (it = repository.begin (); it != repository.end (); ++it)
      delete *it;
    for (it = invalid_repository.begin (); it != invalid_repository.end (); ++it)
      delete *it;
  }
    
    // METHODS -----------------------------------------------------------------
    
  const ResidueType* 
  ResidueTypeStore::get (const string& key) 
  {
    string key2 = key;
    string::iterator sit;

    for (sit = key2.begin (); sit != key2.end (); ++sit)
      *sit = toupper (*sit);

    ResidueType* rtype = new Unknown (key2, key);    
    pair< set< ResidueType*, ResidueType::less_deref >::iterator, bool > inserted =
      repository.insert (rtype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete rtype;
      rtype = *inserted.first;
    }

    return rtype;
  } 


  const ResidueType* 
  ResidueTypeStore::getInvalid (const ResidueType* irtype) 
  {
    ResidueType* rtype = new Unknown (irtype->key, irtype->definition);    
    pair< set< ResidueType*, ResidueType::less_deref >::iterator, bool > inserted =
      invalid_repository.insert (rtype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete rtype;
      rtype = *inserted.first;
    }

    return rtype;
  } 


}
