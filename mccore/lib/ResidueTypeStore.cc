//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.21 $
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

#include <string>

#include "ResidueTypeStore.h"



namespace mccore
{

  ResidueTypeStore::ResidueTypeStore ()
  {
    ResidueType::rNull = *this->repository.insert (new Null (string (""), string ("null"))).first;
    ResidueType::rUnknown = *this->repository.insert (new Unknown (string ("UNKNOWN"), string ("Unknown"))).first;
    
    /**
     * nucleic acids
     *
     * N:? generic nucleic acid type variety for ?
     * R:? RNA type variety for ?
     * D:? DNA type variety for ?
     * ? follows IUPAC
     */
    
    ResidueType::rA  = *this->repository.insert (new A  (string ("N:A"), string("Adenine"))).first;
    ResidueType::rRA = *this->repository.insert (new RA (string ("R:A"), string("RNA_Adenine"))).first;
    ResidueType::rDA = *this->repository.insert (new DA (string ("D:A"), string("DNA_Adenine"))).first;
    ResidueType::rC  = *this->repository.insert (new C  (string ("N:C"), string("Cytosine"))).first;
    ResidueType::rRC = *this->repository.insert (new RC (string ("R:C"), string("RNA_Cytosine"))).first;
    ResidueType::rDC = *this->repository.insert (new DC (string ("D:C"), string("DNA_Cytosine"))).first;
    ResidueType::rG  = *this->repository.insert (new G  (string ("N:G"), string("Guanine"))).first;
    ResidueType::rRG = *this->repository.insert (new RG (string ("R:G"), string("RNA_Guanine"))).first;
    ResidueType::rDG = *this->repository.insert (new DG (string ("D:G"), string("DNA_Guanine"))).first;
    ResidueType::rT  = *this->repository.insert (new T  (string ("N:T"), string("Thymine"))).first;
    ResidueType::rDT = *this->repository.insert (new DT (string ("D:T"), string("DNA_Thymine"))).first;
    ResidueType::rU  = *this->repository.insert (new U  (string ("N:U"), string("Uracil"))).first;
    ResidueType::rRU = *this->repository.insert (new RU (string ("R:U"), string("RNA_Uracil"))).first;
    
    ResidueType::rK  = *this->repository.insert (new K  (string ("N:K"), string("K"))).first;
    ResidueType::rRK = *this->repository.insert (new RK (string ("R:K"), string("RNA_K"))).first;
    ResidueType::rDK = *this->repository.insert (new DK (string ("D:K"), string("DNA_K"))).first;
    ResidueType::rM  = *this->repository.insert (new M  (string ("N:M"), string("M"))).first;
    ResidueType::rRM = *this->repository.insert (new RM (string ("R:M"), string("RNA_M"))).first;
    ResidueType::rDM = *this->repository.insert (new DM (string ("D:M"), string("DNA_M"))).first;
    ResidueType::rS  = *this->repository.insert (new S  (string ("N:S"), string("S"))).first;
    ResidueType::rRS = *this->repository.insert (new RS (string ("R:S"), string("RNA_S"))).first;
    ResidueType::rDS = *this->repository.insert (new DS (string ("D:S"), string("DNA_S"))).first;
    ResidueType::rW  = *this->repository.insert (new W  (string ("N:W"), string("W"))).first;
    ResidueType::rRW = *this->repository.insert (new RW (string ("R:W"), string("RNA_W"))).first;
    ResidueType::rDW = *this->repository.insert (new DW (string ("D:W"), string("DNA_W"))).first;
    ResidueType::rPyrimidine  = *this->repository.insert (new Pyrimidine  (string ("N:Y"), string("Pyrimidine"))).first;
    ResidueType::rRPyrimidine = *this->repository.insert (new RPyrimidine (string ("R:Y"), string("RNA_Pyrimidine"))).first;
    ResidueType::rDPyrimidine = *this->repository.insert (new DPyrimidine (string ("D:Y"), string("DNA_Pyrimidine"))).first;
    ResidueType::rPurine  = *this->repository.insert (new Purine  (string ("N:R"), string("Purine"))).first;
    ResidueType::rRPurine = *this->repository.insert (new RPurine (string ("R:R"), string("RNA_Purine"))).first;
    ResidueType::rDPurine = *this->repository.insert (new DPurine (string ("D:R"), string("DNA_Purine"))).first;
    
    ResidueType::rB  = *this->repository.insert (new B  (string ("N:B"), string("B"))).first;
    ResidueType::rRB = *this->repository.insert (new RB (string ("R:B"), string("RNA_B"))).first;
    ResidueType::rDB = *this->repository.insert (new DB (string ("D:B"), string("DNA_B"))).first;
    ResidueType::rD  = *this->repository.insert (new D  (string ("N:D"), string("D"))).first;
    ResidueType::rRD = *this->repository.insert (new RD (string ("R:D"), string("RNA_D"))).first;
    ResidueType::rDD = *this->repository.insert (new DD (string ("D:D"), string("DNA_D"))).first;
    ResidueType::rH  = *this->repository.insert (new H  (string ("N:H"), string("H"))).first;
    ResidueType::rRH = *this->repository.insert (new RH (string ("R:H"), string("RNA_H"))).first;
    ResidueType::rDH = *this->repository.insert (new DH (string ("D:H"), string("DNA_H"))).first;
    ResidueType::rV  = *this->repository.insert (new V  (string ("N:V"), string("V"))).first;
    ResidueType::rRV = *this->repository.insert (new RV (string ("R:V"), string("RNA_V"))).first;
    ResidueType::rDV = *this->repository.insert (new DV (string ("D:V"), string("DNA_V"))).first;
    
    ResidueType::rNucleicAcid = *this->repository.insert (new NucleicAcid (string ("N:N"), string("N"))).first;
    ResidueType::rRNA = *this->repository.insert (new RNA (string ("R:N"), string("RNA_N"))).first;
    ResidueType::rDNA = *this->repository.insert (new DNA (string ("D:N"), string("DNA_N"))).first;
    
    /**
     * specialized residue types
     */
    
    ResidueType::rPhosphate = *this->repository.insert (new Phosphate (string ("PO4"), string ("Phosphate"))).first;
    ResidueType::rRRibose   = *this->repository.insert (new RRibose   (string ("R:RIB"), string ("RNA_Ribose"))).first;
    ResidueType::rRRibose5  = *this->repository.insert (new RRibose5  (string ("R:RIB5"), string ("RNA_Ribose5"))).first;
    ResidueType::rRRibose3  = *this->repository.insert (new RRibose3  (string ("R:RIB3"), string ("RNA_Ribose3"))).first;
    ResidueType::rRRibose53 = *this->repository.insert (new RRibose53 (string ("R:RIB53"), string ("RNA_Ribose53"))).first;
    ResidueType::rDRibose   = *this->repository.insert (new DRibose   (string ("D:RIB"), string ("DNA_Ribose"))).first;
    ResidueType::rDRibose5  = *this->repository.insert (new DRibose5  (string ("D:RIB5"), string ("DNA_Ribose5"))).first;
    ResidueType::rDRibose3  = *this->repository.insert (new DRibose3  (string ("D:RIB3"), string ("DNA_Ribose3"))).first;
    ResidueType::rDRibose53 = *this->repository.insert (new DRibose53 (string ("D:RIB53"), string ("DNA_Ribose53"))).first;
    
    /**
     * amino acid (IUPAC 3-letter)
     */
    
    ResidueType::rALA = *this->repository.insert (new ALA (string ("ALA"), string ("Alanine"))).first;
    ResidueType::rARG = *this->repository.insert (new ARG (string ("ARG"), string ("Arginine"))).first;
    ResidueType::rASN = *this->repository.insert (new ASN (string ("ASN"), string ("Asparagine"))).first;
    ResidueType::rASP = *this->repository.insert (new ASP (string ("ASP"), string ("Aspartic_acid"))).first;
    ResidueType::rCYS = *this->repository.insert (new CYS (string ("CYS"), string ("Cysteine"))).first;
    ResidueType::rGLN = *this->repository.insert (new GLN (string ("GLN"), string ("Glutamine"))).first;
    ResidueType::rGLU = *this->repository.insert (new GLU (string ("GLU"), string ("Glutamic_acid"))).first;
    ResidueType::rGLY = *this->repository.insert (new GLY (string ("GLY"), string ("Glycine"))).first;
    ResidueType::rHIS = *this->repository.insert (new HIS (string ("HIS"), string ("Histidine"))).first;
    ResidueType::rILE = *this->repository.insert (new ILE (string ("ILE"), string ("Isoleucine"))).first;
    ResidueType::rLEU = *this->repository.insert (new LEU (string ("LEU"), string ("Leucine"))).first;
    ResidueType::rLYS = *this->repository.insert (new LYS (string ("LYS"), string ("Lysine"))).first;
    ResidueType::rMET = *this->repository.insert (new MET (string ("MET"), string ("Methionine"))).first;
    ResidueType::rPHE = *this->repository.insert (new PHE (string ("PHE"), string ("Phenylalanine"))).first;
    ResidueType::rPRO = *this->repository.insert (new PRO (string ("PRO"), string ("Proline"))).first;
    ResidueType::rSER = *this->repository.insert (new SER (string ("SER"), string ("Serine"))).first;
    ResidueType::rTHR = *this->repository.insert (new THR (string ("THR"), string ("Threonine"))).first;
    ResidueType::rTRP = *this->repository.insert (new TRP (string ("TRP"), string ("Tryptophane"))).first;
    ResidueType::rTYR = *this->repository.insert (new TYR (string ("TYR"), string ("Tyrosine"))).first;
    ResidueType::rVAL = *this->repository.insert (new VAL (string ("VAL"), string ("Valine"))).first;
    
    ResidueType::rASX = *this->repository.insert (new ASX (string ("ASX"), string ("ASX"))).first;
    ResidueType::rGLX = *this->repository.insert (new GLX (string ("GLX"), string ("GLX"))).first;
    ResidueType::rAminoAcid = *this->repository.insert (new AminoAcid (string ("XAA"), string ("XAA"))).first;
    
  }
  
    
  ResidueTypeStore::~ResidueTypeStore () 
  {
    set< ResidueType*, ResidueType::less_deref >::iterator it;
    for (it = this->repository.begin (); it != this->repository.end (); ++it)
      delete *it;
    for (it = this->invalid_repository.begin (); it != this->invalid_repository.end (); ++it)
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
      this->repository.insert (rtype);

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
      this->invalid_repository.insert (rtype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete rtype;
      rtype = *inserted.first;
    }

    return rtype;
  } 


}
