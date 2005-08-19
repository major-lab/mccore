//                              -*- Mode: C++ -*- 
// ResidueTypeStore.cc
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.23 $
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
    string strs, strl;

    ResidueType::rNull = *repository.insert (new Null ((strs = ""), (strl = "null"))).first;
    ResidueType::rUnknown = *repository.insert (new Unknown ((strs = "UNKNOWN"), (strl = "Unknown"))).first;
    
    /**
     * nucleic acids
     *
     * N:? generic nucleic acid type variety for ?
     * R:? RNA type variety for ?
     * D:? DNA type variety for ?
     * ? follows IUPAC
     */
    
    ResidueType::rA  = *repository.insert (new A  ((strs = "N:A"), (strl ="Adenine"))).first;
    ResidueType::rRA = *repository.insert (new RA ((strs = "R:A"), (strl ="RNA_Adenine"))).first;
    ResidueType::rDA = *repository.insert (new DA ((strs = "D:A"), (strl ="DNA_Adenine"))).first;
    ResidueType::rC  = *repository.insert (new C  ((strs = "N:C"), (strl ="Cytosine"))).first;
    ResidueType::rRC = *repository.insert (new RC ((strs = "R:C"), (strl ="RNA_Cytosine"))).first;
    ResidueType::rDC = *repository.insert (new DC ((strs = "D:C"), (strl ="DNA_Cytosine"))).first;
    ResidueType::rG  = *repository.insert (new G  ((strs = "N:G"), (strl ="Guanine"))).first;
    ResidueType::rRG = *repository.insert (new RG ((strs = "R:G"), (strl ="RNA_Guanine"))).first;
    ResidueType::rDG = *repository.insert (new DG ((strs = "D:G"), (strl ="DNA_Guanine"))).first;
    ResidueType::rT  = *repository.insert (new T  ((strs = "N:T"), (strl ="Thymine"))).first;
    ResidueType::rDT = *repository.insert (new DT ((strs = "D:T"), (strl ="DNA_Thymine"))).first;
    ResidueType::rU  = *repository.insert (new U  ((strs = "N:U"), (strl ="Uracil"))).first;
    ResidueType::rRU = *repository.insert (new RU ((strs = "R:U"), (strl ="RNA_Uracil"))).first;
    
    ResidueType::rK  = *repository.insert (new K  ((strs = "N:K"), (strl ="K"))).first;
    ResidueType::rRK = *repository.insert (new RK ((strs = "R:K"), (strl ="RNA_K"))).first;
    ResidueType::rDK = *repository.insert (new DK ((strs = "D:K"), (strl ="DNA_K"))).first;
    ResidueType::rM  = *repository.insert (new M  ((strs = "N:M"), (strl ="M"))).first;
    ResidueType::rRM = *repository.insert (new RM ((strs = "R:M"), (strl ="RNA_M"))).first;
    ResidueType::rDM = *repository.insert (new DM ((strs = "D:M"), (strl ="DNA_M"))).first;
    ResidueType::rS  = *repository.insert (new S  ((strs = "N:S"), (strl ="S"))).first;
    ResidueType::rRS = *repository.insert (new RS ((strs = "R:S"), (strl ="RNA_S"))).first;
    ResidueType::rDS = *repository.insert (new DS ((strs = "D:S"), (strl ="DNA_S"))).first;
    ResidueType::rW  = *repository.insert (new W  ((strs = "N:W"), (strl ="W"))).first;
    ResidueType::rRW = *repository.insert (new RW ((strs = "R:W"), (strl ="RNA_W"))).first;
    ResidueType::rDW = *repository.insert (new DW ((strs = "D:W"), (strl ="DNA_W"))).first;
    ResidueType::rPyrimidine  = *repository.insert (new Pyrimidine  ((strs = "N:Y"), (strl ="Pyrimidine"))).first;
    ResidueType::rRPyrimidine = *repository.insert (new RPyrimidine ((strs = "R:Y"), (strl ="RNA_Pyrimidine"))).first;
    ResidueType::rDPyrimidine = *repository.insert (new DPyrimidine ((strs = "D:Y"), (strl ="DNA_Pyrimidine"))).first;
    ResidueType::rPurine  = *repository.insert (new Purine  ((strs = "N:R"), (strl ="Purine"))).first;
    ResidueType::rRPurine = *repository.insert (new RPurine ((strs = "R:R"), (strl ="RNA_Purine"))).first;
    ResidueType::rDPurine = *repository.insert (new DPurine ((strs = "D:R"), (strl ="DNA_Purine"))).first;
    
    ResidueType::rB  = *repository.insert (new B  ((strs = "N:B"), (strl ="B"))).first;
    ResidueType::rRB = *repository.insert (new RB ((strs = "R:B"), (strl ="RNA_B"))).first;
    ResidueType::rDB = *repository.insert (new DB ((strs = "D:B"), (strl ="DNA_B"))).first;
    ResidueType::rD  = *repository.insert (new D  ((strs = "N:D"), (strl ="D"))).first;
    ResidueType::rRD = *repository.insert (new RD ((strs = "R:D"), (strl ="RNA_D"))).first;
    ResidueType::rDD = *repository.insert (new DD ((strs = "D:D"), (strl ="DNA_D"))).first;
    ResidueType::rH  = *repository.insert (new H  ((strs = "N:H"), (strl ="H"))).first;
    ResidueType::rRH = *repository.insert (new RH ((strs = "R:H"), (strl ="RNA_H"))).first;
    ResidueType::rDH = *repository.insert (new DH ((strs = "D:H"), (strl ="DNA_H"))).first;
    ResidueType::rV  = *repository.insert (new V  ((strs = "N:V"), (strl ="V"))).first;
    ResidueType::rRV = *repository.insert (new RV ((strs = "R:V"), (strl ="RNA_V"))).first;
    ResidueType::rDV = *repository.insert (new DV ((strs = "D:V"), (strl ="DNA_V"))).first;
    
    ResidueType::rNucleicAcid = *repository.insert (new NucleicAcid ((strs = "N:N"), (strl ="N"))).first;
    ResidueType::rRNA = *repository.insert (new RNA ((strs = "R:N"), (strl ="RNA_N"))).first;
    ResidueType::rDNA = *repository.insert (new DNA ((strs = "D:N"), (strl ="DNA_N"))).first;
    
    /**
     * specialized residue types
     */
    
    ResidueType::rPhosphate = *repository.insert (new Phosphate ((strs = "PO4"), (strl = "Phosphate"))).first;
    ResidueType::rRRibose   = *repository.insert (new RRibose   ((strs = "R:RIB"), (strl = "RNA_Ribose"))).first;
    ResidueType::rRRibose5  = *repository.insert (new RRibose5  ((strs = "R:RIB5"), (strl = "RNA_Ribose5"))).first;
    ResidueType::rRRibose3  = *repository.insert (new RRibose3  ((strs = "R:RIB3"), (strl = "RNA_Ribose3"))).first;
    ResidueType::rRRibose53 = *repository.insert (new RRibose53 ((strs = "R:RIB53"), (strl = "RNA_Ribose53"))).first;
    ResidueType::rDRibose   = *repository.insert (new DRibose   ((strs = "D:RIB"), (strl = "DNA_Ribose"))).first;
    ResidueType::rDRibose5  = *repository.insert (new DRibose5  ((strs = "D:RIB5"), (strl = "DNA_Ribose5"))).first;
    ResidueType::rDRibose3  = *repository.insert (new DRibose3  ((strs = "D:RIB3"), (strl = "DNA_Ribose3"))).first;
    ResidueType::rDRibose53 = *repository.insert (new DRibose53 ((strs = "D:RIB53"), (strl = "DNA_Ribose53"))).first;
    
    /**
     * amino acid (IUPAC 3-letter)
     */
    
    ResidueType::rALA = *repository.insert (new ALA ((strs = "ALA"), (strl = "Alanine"))).first;
    ResidueType::rARG = *repository.insert (new ARG ((strs = "ARG"), (strl = "Arginine"))).first;
    ResidueType::rASN = *repository.insert (new ASN ((strs = "ASN"), (strl = "Asparagine"))).first;
    ResidueType::rASP = *repository.insert (new ASP ((strs = "ASP"), (strl = "Aspartic_acid"))).first;
    ResidueType::rCYS = *repository.insert (new CYS ((strs = "CYS"), (strl = "Cysteine"))).first;
    ResidueType::rGLN = *repository.insert (new GLN ((strs = "GLN"), (strl = "Glutamine"))).first;
    ResidueType::rGLU = *repository.insert (new GLU ((strs = "GLU"), (strl = "Glutamic_acid"))).first;
    ResidueType::rGLY = *repository.insert (new GLY ((strs = "GLY"), (strl = "Glycine"))).first;
    ResidueType::rHIS = *repository.insert (new HIS ((strs = "HIS"), (strl = "Histidine"))).first;
    ResidueType::rILE = *repository.insert (new ILE ((strs = "ILE"), (strl = "Isoleucine"))).first;
    ResidueType::rLEU = *repository.insert (new LEU ((strs = "LEU"), (strl = "Leucine"))).first;
    ResidueType::rLYS = *repository.insert (new LYS ((strs = "LYS"), (strl = "Lysine"))).first;
    ResidueType::rMET = *repository.insert (new MET ((strs = "MET"), (strl = "Methionine"))).first;
    ResidueType::rPHE = *repository.insert (new PHE ((strs = "PHE"), (strl = "Phenylalanine"))).first;
    ResidueType::rPRO = *repository.insert (new PRO ((strs = "PRO"), (strl = "Proline"))).first;
    ResidueType::rSER = *repository.insert (new SER ((strs = "SER"), (strl = "Serine"))).first;
    ResidueType::rTHR = *repository.insert (new THR ((strs = "THR"), (strl = "Threonine"))).first;
    ResidueType::rTRP = *repository.insert (new TRP ((strs = "TRP"), (strl = "Tryptophane"))).first;
    ResidueType::rTYR = *repository.insert (new TYR ((strs = "TYR"), (strl = "Tyrosine"))).first;
    ResidueType::rVAL = *repository.insert (new VAL ((strs = "VAL"), (strl = "Valine"))).first;
    
    ResidueType::rASX = *repository.insert (new ASX ((strs = "ASX"), (strl = "ASX"))).first;
    ResidueType::rGLX = *repository.insert (new GLX ((strs = "GLX"), (strl = "GLX"))).first;
    ResidueType::rAminoAcid = *repository.insert (new AminoAcid ((strs = "XAA"), (strl = "XAA"))).first;
    
  }
  
    
  ResidueTypeStore::~ResidueTypeStore () 
  {
    set< const ResidueType*, ResidueType::less_deref >::iterator it;
    
    for (it = repository.begin (); it != repository.end (); ++it)
      {
	delete *it;
      }
    for (it = invalid_repository.begin (); it != invalid_repository.end (); ++it)
      {
	delete *it;
      }
  }
    
    
  const ResidueType* 
  ResidueTypeStore::get (const string& key) 
  {
    string key2 = key;
    string::iterator sit;

    for (sit = key2.begin (); sit != key2.end (); ++sit)
      *sit = toupper (*sit);

    const ResidueType* rtype = new Unknown (key2, key);    
    pair< set< const ResidueType*, ResidueType::less_deref >::iterator, bool > inserted =
      repository.insert (rtype);

    if (! inserted.second) // no unique insertion => key exists
    {
      delete rtype;
      rtype = *inserted.first;
    }

    return rtype;
  } 


  const ResidueType* 
  ResidueTypeStore::getInvalid (const ResidueType* irtype) 
  {
    const ResidueType* rtype = new Unknown (irtype->key, irtype->definition);    
    pair< set< const ResidueType*, ResidueType::less_deref >::iterator, bool > inserted = invalid_repository.insert (rtype);

    if (!inserted.second) // no unique insertion => key exists
    {
      delete rtype;
      rtype = *inserted.first;
    }

    return rtype;
  } 


}
