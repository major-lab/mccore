//                              -*- Mode: C++ -*- 
// AtomType.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Patrick Gendron
// Last Modified On : Wed Sep 12 11:55:26 2001
// Update Count     : 11
// Status           : Ok.
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _AtomType_h_
#define _AtomType_h_


class CResidue;
class t_Residue;
class iBinstream;
class oBinstream;



/**
 * @short Base atom type.
 *
 * The base atom type defines a set of methods witch describes the atom.
 * The base class always return false or 0 for these methods; the derived
 * classes defines the needed property method to return true.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class t_Atom
{

public:
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.  Nothing to do.
   */
  t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  t_Atom (const t_Atom &right) { }

  /**
   * Destructs the objet.  Nothing to do.
   */
  virtual ~t_Atom () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const t_Atom& operator= (const t_Atom &right) { return *this; }

  /**
   * Converts the atom type to a string.
   * @return "ATOM".
   */
  virtual operator const char* () const { return "ATOM"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an PDB string representation.
   * @return the PDB string representation of the atom.
   */
  virtual const char* getPDBRep () const = 0;
  
  /**
   * Converts the atom type to an Amber string representation.
   * @return the Amber string representation of the atom.
   */
  virtual const char* getAmberRep () const = 0;
  
  /**
   * Tells if the atom is unknown.
   * @return if the atom is unknown.
   */
  virtual bool is_Misc () const { return false; }

  /**
   * Tells if the atom is part of a nucleic acid.
   * @return if the atom is part of a nucleic acid.
   */
  virtual bool is_NucleicAcid () const { return false; }

  /**
   * Tells if the atom is part of a protein.
   * @return if the atom is part of a protein.
   */
  virtual bool is_AminoAcid () const { return false; }

  /**
   * Tells if the atom is part of the backbone.
   * @return if the atom is part of the backbone.
   */
  virtual bool is_Backbone () const { return false; }

  /**
   * Tells if the atom is part of the sidechain.
   * @return if the atom is part of the sidechain.
   */
  virtual bool is_SideChain () const { return false; }
  /**
   * Tells if the atom is a carbon.
   * @return if the atom is a carbon.
   */
  virtual bool is_Carbon () const { return false; }
  
  /**
   * Tells if the atom is a hydrogen.
   * @return if the atom is a hydrogen.
   */
  virtual bool is_Hydrogen () const { return false; }

  /**
   * Tells if the atom is a nitrogen.
   * @return if the atom is a nitrogen.
   */
  virtual bool is_Nitrogen () const { return false; }

  /**
   * Tells if the atom is a phosphate.
   * @return if the atom is a phosphate.
   */
  virtual bool is_Phosphate () const { return false; }

  /**
   * Tells if the atom is an oxygen.
   * @return if the atom is an oxygen.
   */
  virtual bool is_Oxygen () const { return false; }

  /**
   * Tells if the atom is a sulfur.
   * @return if the atom is a sulfur.
   */
  virtual bool is_Sulfur () const { return false; }

  /**
   * Tells if the atom is a magnesium.
   * @return if the atom is a magnesium.
   */
  virtual bool is_Magnesium () const { return false; }

  /**
   * Tells if the atom is a lonepair.
   * @return if the atom is a lonepair.
   */
  virtual bool is_LonePair () const { return false; }

  /**
   * Tells if the atom is a pseudo.
   * @return if the atom is a pseudo.
   */
  virtual bool is_Pseudo () const { return false; }
  
  /**
   * Tells if the atom is a C1p.
   * @return if the atom is a C1p.
   */
  virtual bool is_C1p () const { return false; }
  
  /**
   * Tells if the atom is a C2p.
   * @return if the atom is a C2p.
   */
  virtual bool is_C2p () const { return false; }
  
  /**
   * Tells if the atom is a C3p.
   * @return if the atom is a C3p.
   */
  virtual bool is_C3p () const { return false; }
  
  /**
   * Tells if the atom is a C4p.
   * @return if the atom is a C4p.
   */
  virtual bool is_C4p () const { return false; }
  
  /**
   * Tells if the atom is a C5p.
   * @return if the atom is a C5p.
   */
  virtual bool is_C5p () const { return false; }
  
  /**
   * Tells if the atom is a H1p.
   * @return if the atom is a H1p.
   */
  virtual bool is_H1p () const { return false; }
  
  /**
   * Tells if the atom is a H2p.
   * @return if the atom is a H2p.
   */
  virtual bool is_H2p () const { return false; }
  
  /**
   * Tells if the atom is a H3p.
   * @return if the atom is a H3p.
   */
  virtual bool is_H3p () const { return false; }
  
  /**
   * Tells if the atom is a H4p.
   * @return if the atom is a H4p.
   */
  virtual bool is_H4p () const { return false; }
  
  /**
   * Tells if the atom is a H5p.
   * @return if the atom is a H5p.
   */
  virtual bool is_H5p () const { return false; }
  
  /**
   * Tells if the atom is a O1P.
   * @return if the atom is a O1P.
   */
  virtual bool is_O1P () const { return false; }
  
  /**
   * Tells if the atom is a O2p.
   * @return if the atom is a O2p.
   */
  virtual bool is_O2p () const { return false; }
  
  /**
   * Tells if the atom is a O2P.
   * @return if the atom is a O2P.
   */
  virtual bool is_O2P () const { return false; }
  
  /**
   * Tells if the atom is a O3p.
   * @return if the atom is a O3p.
   */
  virtual bool is_O3p () const { return false; }
  
  /**
   * Tells if the atom is a O3P.
   * @return if the atom is a O3P.
   */
  virtual bool is_O3P () const { return false; }
  
  /**
   * Tells if the atom is a O4p.
   * @return if the atom is a O4p.
   */
  virtual bool is_O4p () const { return false; }
  
  /**
   * Tells if the atom is a O5p.
   * @return if the atom is a O5p.
   */
  virtual bool is_O5p () const { return false; }
  
  /**
   * Tells if the atom is a P.
   * @return if the atom is a P.
   */
  virtual bool is_P () const { return false; }
  
  /**
   * Tells if the atom is a 1H2p.
   * @return if the atom is a 1H2p.
   */
  virtual bool is_1H2p () const { return false; }
  
  /**
   * Tells if the atom is a 1H5p.
   * @return if the atom is a 1H5p.
   */
  virtual bool is_1H5p () const { return false; }
  
  /**
   * Tells if the atom is a 2H2p.
   * @return if the atom is a 2H2p.
   */
  virtual bool is_2H2p () const { return false; }
  
  /**
   * Tells if the atom is a 2H5p.
   * @return if the atom is a 2H5p.
   */
  virtual bool is_2H5p () const { return false; }
  
  /**
   * Tells if the atom is a HO2p.
   * @return if the atom is a HO2p.
   */
  virtual bool is_HO2p () const { return false; }
  
  /**
   * Tells if the atom is a HO3p.
   * @return if the atom is a HO3p.
   */
  virtual bool is_HO3p () const { return false; }
  
  /**
   * Tells if the atom is a C2.
   * @return if the atom is a C2.
   */
  virtual bool is_C2 () const { return false; }
  
  /**
   * Tells if the atom is a C4.
   * @return if the atom is a C4.
   */
  virtual bool is_C4 () const { return false; }
  
  /**
   * Tells if the atom is a C5.
   * @return if the atom is a C5.
   */
  virtual bool is_C5 () const { return false; }
  
  /**
   * Tells if the atom is a C5M.
   * @return if the atom is a C5M.
   */
  virtual bool is_C5M () const { return false; }
  
  /**
   * Tells if the atom is a C6.
   * @return if the atom is a C6.
   */
  virtual bool is_C6 () const { return false; }
  
  /**
   * Tells if the atom is a C8.
   * @return if the atom is a C8.
   */
  virtual bool is_C8 () const { return false; }
  
  /**
   * Tells if the atom is a H1.
   * @return if the atom is a H1.
   */
  virtual bool is_H1 () const { return false; }
  
  /**
   * Tells if the atom is a H2.
   * @return if the atom is a H2.
   */
  virtual bool is_H2 () const { return false; }
  
  /**
   * Tells if the atom is a H3.
   * @return if the atom is a H3.
   */
  virtual bool is_H3 () const { return false; }
  
  /**
   * Tells if the atom is a H5.
   * @return if the atom is a H5.
   */
  virtual bool is_H5 () const { return false; }
  
  /**
   * Tells if the atom is a H6.
   * @return if the atom is a H6.
   */
  virtual bool is_H6 () const { return false; }
  
  /**
   * Tells if the atom is a H7.
   * @return if the atom is a H7.
   */
  virtual bool is_H7 () const { return false; }
  
  /**
   * Tells if the atom is a H8.
   * @return if the atom is a H8.
   */
  virtual bool is_H8 () const { return false; }
  
  /**
   * Tells if the atom is a N1.
   * @return if the atom is a N1.
   */
  virtual bool is_N1 () const { return false; }
  
  /**
   * Tells if the atom is a N2.
   * @return if the atom is a N2.
   */
  virtual bool is_N2 () const { return false; }
  
  /**
   * Tells if the atom is a N3.
   * @return if the atom is a N3.
   */
  virtual bool is_N3 () const { return false; }
  
  /**
   * Tells if the atom is a N4.
   * @return if the atom is a N4.
   */
  virtual bool is_N4 () const { return false; }
  
  /**
   * Tells if the atom is a N6.
   * @return if the atom is a N6.
   */
  virtual bool is_N6 () const { return false; }
  
  /**
   * Tells if the atom is a N7.
   * @return if the atom is a N7.
   */
  virtual bool is_N7 () const { return false; }
  
  /**
   * Tells if the atom is a N9.
   * @return if the atom is a N9.
   */
  virtual bool is_N9 () const { return false; }
  
  /**
   * Tells if the atom is a O2.
   * @return if the atom is a O2.
   */
  virtual bool is_O2 () const { return false; }
  
  /**
   * Tells if the atom is a O4.
   * @return if the atom is a O4.
   */
  virtual bool is_O4 () const { return false; }
  
  /**
   * Tells if the atom is a O6.
   * @return if the atom is a O6.
   */
  virtual bool is_O6 () const { return false; }
  
  /**
   * Tells if the atom is a 1H2.
   * @return if the atom is a 1H2.
   */
  virtual bool is_1H2 () const { return false; }
  
  /**
   * Tells if the atom is a 1H4.
   * @return if the atom is a 1H4.
   */
  virtual bool is_1H4 () const { return false; }
  
  /**
   * Tells if the atom is a 1H5M.
   * @return if the atom is a 1H5M.
   */
  virtual bool is_1H5M () const { return false; }
  
  /**
   * Tells if the atom is a 1H6.
   * @return if the atom is a 1H6.
   */
  virtual bool is_1H6 () const { return false; }
  
  /**
   * Tells if the atom is a 2H2.
   * @return if the atom is a 2H2.
   */
  virtual bool is_2H2 () const { return false; }
  
  /**
   * Tells if the atom is a 2H4.
   * @return if the atom is a 2H4.
   */
  virtual bool is_2H4 () const { return false; }
  
  /**
   * Tells if the atom is a 2H5M.
   * @return if the atom is a 2H5M.
   */
  virtual bool is_2H5M () const { return false; }
  
  /**
   * Tells if the atom is a 2H6.
   * @return if the atom is a 2H6.
   */
  virtual bool is_2H6 () const { return false; }
  
  /**
   * Tells if the atom is a 3H5M.
   * @return if the atom is a 3H5M.
   */
  virtual bool is_3H5M () const { return false; }
  
  /**
   * Tells if the atom is a PSY.
   * @return if the atom is a PSY.
   */
  virtual bool is_PSY () const { return false; }
  
  /**
   * Tells if the atom is a PSZ.
   * @return if the atom is a PSZ.
   */
  virtual bool is_PSZ () const { return false; }
  
  /**
   * Tells if the atom is a 2LP6.
   * @return if the atom is a 2LP6.
   */
  virtual bool is_2LP6 () const { return false; }
  
  /**
   * Tells if the atom is a 1LP6.
   * @return if the atom is a 1LP6.
   */
  virtual bool is_1LP6 () const { return false; }
  
  /**
   * Tells if the atom is a LP7.
   * @return if the atom is a LP7.
   */
  virtual bool is_LP7 () const { return false; }
  
  /**
   * Tells if the atom is a LP3.
   * @return if the atom is a LP3.
   */
  virtual bool is_LP3 () const { return false; }
  
  /**
   * Tells if the atom is a LP1.
   * @return if the atom is a LP1.
   */
  virtual bool is_LP1 () const { return false; }
  
  /**
   * Tells if the atom is a 2LP2.
   * @return if the atom is a 2LP2.
   */
  virtual bool is_2LP2 () const { return false; }
  
  /**
   * Tells if the atom is a 1LP2.
   * @return if the atom is a 1LP2.
   */
  virtual bool is_1LP2 () const { return false; }
  
  /**
   * Tells if the atom is a 2LP4.
   * @return if the atom is a 2LP4.
   */
  virtual bool is_2LP4 () const { return false; }
  
  /**
   * Tells if the atom is a 1LP4.
   * @return if the atom is a 1LP4.
   */
  virtual bool is_1LP4 () const { return false; }
  
  /**
   * Tells if the atom is a H3T.
   * @return if the atom is a H3T.
   */
  virtual bool is_H3T () const { return false; }
  
  /**
   * Tells if the atom is a H5T.
   * @return if the atom is a H5T.
   */
  virtual bool is_H5T () const { return false; }
  
  /**
   * Tells if the atom is a C.
   * @return if the atom is a C.
   */
  virtual bool is_C () const { return false; }
  
  /**
   * Tells if the atom is a CA.
   * @return if the atom is a CA.
   */
  virtual bool is_CA () const { return false; }
  
  /**
   * Tells if the atom is a CB.
   * @return if the atom is a CB.
   */
  virtual bool is_CB () const { return false; }
  
  /**
   * Tells if the atom is a CD.
   * @return if the atom is a CD.
   */
  virtual bool is_CD () const { return false; }
  
  /**
   * Tells if the atom is a CD1.
   * @return if the atom is a CD1.
   */
  virtual bool is_CD1 () const { return false; }
  
  /**
   * Tells if the atom is a CD2.
   * @return if the atom is a CD2.
   */
  virtual bool is_CD2 () const { return false; }
  
  /**
   * Tells if the atom is a CE.
   * @return if the atom is a CE.
   */
  virtual bool is_CE () const { return false; }
  
  /**
   * Tells if the atom is a CE1.
   * @return if the atom is a CE1.
   */
  virtual bool is_CE1 () const { return false; }
  
  /**
   * Tells if the atom is a CE2.
   * @return if the atom is a CE2.
   */
  virtual bool is_CE2 () const { return false; }
  
  /**
   * Tells if the atom is a CE3.
   * @return if the atom is a CE3.
   */
  virtual bool is_CE3 () const { return false; }
  
  /**
   * Tells if the atom is a CG.
   * @return if the atom is a CG.
   */
  virtual bool is_CG () const { return false; }
  
  /**
   * Tells if the atom is a CG1.
   * @return if the atom is a CG1.
   */
  virtual bool is_CG1 () const { return false; }
  
  /**
   * Tells if the atom is a CG2.
   * @return if the atom is a CG2.
   */
  virtual bool is_CG2 () const { return false; }
  
  /**
   * Tells if the atom is a CH2.
   * @return if the atom is a CH2.
   */
  virtual bool is_CH2 () const { return false; }
  
  /**
   * Tells if the atom is a CZ.
   * @return if the atom is a CZ.
   */
  virtual bool is_CZ () const { return false; }
  
  /**
   * Tells if the atom is a CZ2.
   * @return if the atom is a CZ2.
   */
  virtual bool is_CZ2 () const { return false; }
  
  /**
   * Tells if the atom is a CZ3.
   * @return if the atom is a CZ3.
   */
  virtual bool is_CZ3 () const { return false; }
  
  /**
   * Tells if the atom is a H.
   * @return if the atom is a H.
   */
  virtual bool is_H () const { return false; }
  
  /**
   * Tells if the atom is a HA.
   * @return if the atom is a HA.
   */
  virtual bool is_HA () const { return false; }
  
  /**
   * Tells if the atom is a HA1.
   * @return if the atom is a HA1.
   */
  virtual bool is_HA1 () const { return false; }
  
  /**
   * Tells if the atom is a HA2.
   * @return if the atom is a HA2.
   */
  virtual bool is_HA2 () const { return false; }
  
  /**
   * Tells if the atom is a HB.
   * @return if the atom is a HB.
   */
  virtual bool is_HB () const { return false; }
  
  /**
   * Tells if the atom is a HB1.
   * @return if the atom is a HB1.
   */
  virtual bool is_HB1 () const { return false; }

  /**
   * Tells if the atom is a HB2.
   * @return if the atom is a HB2.
   */
  virtual bool is_HB2 () const { return false; }

  /**
   * Tells if the atom is a HB3.
   * @return if the atom is a HB3.
   */
  virtual bool is_HB3 () const { return false; }

  /**
   * Tells if the atom is a HD1.
   * @return if the atom is a HD1.
   */
  virtual bool is_HD1 () const { return false; }

  /**
   * Tells if the atom is a HD2.
   * @return if the atom is a HD2.
   */
  virtual bool is_HD2 () const { return false; }

  /**
   * Tells if the atom is a HD3.
   * @return if the atom is a HD3.
   */
  virtual bool is_HD3 () const { return false; }

  /**
   * Tells if the atom is a HE.
   * @return if the atom is a HE.
   */
  virtual bool is_HE () const { return false; }

  /**
   * Tells if the atom is a HE1.
   * @return if the atom is a HE1.
   */
  virtual bool is_HE1 () const { return false; }

  /**
   * Tells if the atom is a HE2.
   * @return if the atom is a HE2.
   */
  virtual bool is_HE2 () const { return false; }

  /**
   * Tells if the atom is a HE3.
   * @return if the atom is a HE3.
   */
  virtual bool is_HE3 () const { return false; }

  /**
   * Tells if the atom is a HG.
   * @return if the atom is a HG.
   */
  virtual bool is_HG () const { return false; }

  /**
   * Tells if the atom is a HG1.
   * @return if the atom is a HG1.
   */
  virtual bool is_HG1 () const { return false; }

  /**
   * Tells if the atom is a HG2.
   * @return if the atom is a HG2.
   */
  virtual bool is_HG2 () const { return false; }

  /**
   * Tells if the atom is a HG3.
   * @return if the atom is a HG3.
   */
  virtual bool is_HG3 () const { return false; }

  /**
   * Tells if the atom is a HH.
   * @return if the atom is a HH.
   */
  virtual bool is_HH () const { return false; }

  /**
   * Tells if the atom is a HH2.
   * @return if the atom is a HH2.
   */
  virtual bool is_HH2 () const { return false; }

  /**
   * Tells if the atom is a HXT.
   * @return if the atom is a HXT.
   */
  virtual bool is_HXT () const { return false; }

  /**
   * Tells if the atom is a HZ.
   * @return if the atom is a HZ.
   */
  virtual bool is_HZ () const { return false; }

  /**
   * Tells if the atom is a HZ1.
   * @return if the atom is a HZ1.
   */
  virtual bool is_HZ1 () const { return false; }

  /**
   * Tells if the atom is a HZ2.
   * @return if the atom is a HZ2.
   */
  virtual bool is_HZ2 () const { return false; }

  /**
   * Tells if the atom is a HZ3.
   * @return if the atom is a HZ3.
   */
  virtual bool is_HZ3 () const { return false; }

  /**
   * Tells if the atom is a N.
   * @return if the atom is a N.
   */
  virtual bool is_N () const { return false; }

  /**
   * Tells if the atom is a ND1.
   * @return if the atom is a ND1.
   */
  virtual bool is_ND1 () const { return false; }

  /**
   * Tells if the atom is a ND2.
   * @return if the atom is a ND2.
   */
  virtual bool is_ND2 () const { return false; }

  /**
   * Tells if the atom is a NE.
   * @return if the atom is a NE.
   */
  virtual bool is_NE () const { return false; }

  /**
   * Tells if the atom is a NE1.
   * @return if the atom is a NE1.
   */
  virtual bool is_NE1 () const { return false; }

  /**
   * Tells if the atom is a NE2.
   * @return if the atom is a NE2.
   */
  virtual bool is_NE2 () const { return false; }

  /**
   * Tells if the atom is a NH1.
   * @return if the atom is a NH1.
   */
  virtual bool is_NH1 () const { return false; }

  /**
   * Tells if the atom is a NH2.
   * @return if the atom is a NH2.
   */
  virtual bool is_NH2 () const { return false; }

  /**
   * Tells if the atom is a NZ.
   * @return if the atom is a NZ.
   */
  virtual bool is_NZ () const { return false; }

  /**
   * Tells if the atom is a O.
   * @return if the atom is a O.
   */
  virtual bool is_O () const { return false; }

  /**
   * Tells if the atom is a OD1.
   * @return if the atom is a OD1.
   */
  virtual bool is_OD1 () const { return false; }

  /**
   * Tells if the atom is a OD2.
   * @return if the atom is a OD2.
   */
  virtual bool is_OD2 () const { return false; }

  /**
   * Tells if the atom is a OE1.
   * @return if the atom is a OE1.
   */
  virtual bool is_OE1 () const { return false; }

  /**
   * Tells if the atom is a OE2.
   * @return if the atom is a OE2.
   */
  virtual bool is_OE2 () const { return false; }

  /**
   * Tells if the atom is a OG.
   * @return if the atom is a OG.
   */
  virtual bool is_OG () const { return false; }

  /**
   * Tells if the atom is a OG1.
   * @return if the atom is a OG1.
   */
  virtual bool is_OG1 () const { return false; }

  /**
   * Tells if the atom is a OH.
   * @return if the atom is a OH.
   */
  virtual bool is_OH () const { return false; }

  /**
   * Tells if the atom is a OXT.
   * @return if the atom is a OXT.
   */
  virtual bool is_OXT () const { return false; }
  
  /**
   * Tells if the atom is a SD.
   * @return if the atom is a SD.
   */
  virtual bool is_SD () const { return false; }

  /**
   * Tells if the atom is a SG.
   * @return if the atom is a SG.
   */
  virtual bool is_SG () const { return false; }

  /**
   * Tells if the atom is a 1H.
   * @return false.
   */
  virtual bool is_1H () const { return false; }

  /**
   * Tells if the atom is a 2H.
   * @return false.
   */
  virtual bool is_2H () const { return false; }

  /**
   * Tells if the atom is a 3H.
   * @return false.
   */
  virtual bool is_3H () const { return false; }

  /**
   * Tells if the atom is a 1HD1.
   * @return if the atom is a 1HD1.
   */
  virtual bool is_1HD1 () const { return false; }

  /**
   * Tells if the atom is a 1HD2.
   * @return if the atom is a 1HD2.
   */
  virtual bool is_1HD2 () const { return false; }

  /**
   * Tells if the atom is a 1HE2.
   * @return if the atom is a 1HE2.
   */
  virtual bool is_1HE2 () const { return false; }

  /**
   * Tells if the atom is a 1HG1.
   * @return if the atom is a 1HG1.
   */
  virtual bool is_1HG1 () const { return false; }

  /**
   * Tells if the atom is a 1HG2.
   * @return if the atom is a 1HG2.
   */
  virtual bool is_1HG2 () const { return false; }

  /**
   * Tells if the atom is a 1HH1.
   * @return if the atom is a 1HH1.
   */
  virtual bool is_1HH1 () const { return false; }

  /**
   * Tells if the atom is a 1HH2.
   * @return if the atom is a 1HH2.
   */
  virtual bool is_1HH2 () const { return false; }

  /**
   * Tells if the atom is a 2HD1.
   * @return if the atom is a 2HD1.
   */
  virtual bool is_2HD1 () const { return false; }

  /**
   * Tells if the atom is a 2HD2.
   * @return if the atom is a 2HD2.
   */
  virtual bool is_2HD2 () const { return false; }

  /**
   * Tells if the atom is a 2HE2.
   * @return if the atom is a 2HE2.
   */
  virtual bool is_2HE2 () const { return false; }

  /**
   * Tells if the atom is a 2HG1.
   * @return if the atom is a 2HG1.
   */
  virtual bool is_2HG1 () const { return false; }

  /**
   * Tells if the atom is a 2HG2.
   * @return if the atom is a 2HG2.
   */
  virtual bool is_2HG2 () const { return false; }

  /**
   * Tells if the atom is a 2HH1.
   * @return if the atom is a 2HH1.
   */
  virtual bool is_2HH1 () const { return false; }

  /**
   * Tells if the atom is a 2HH2.
   * @return if the atom is a 2HH2.
   */
  virtual bool is_2HH2 () const { return false; }

  /**
   * Tells if the atom is a 3HD1.
   * @return if the atom is a 3HD1.
   */
  virtual bool is_3HD1 () const { return false; }

  /**
   * Tells if the atom is a 3HD2.
   * @return if the atom is a 3HD2.
   */
  virtual bool is_3HD2 () const { return false; }

  /**
   * Tells if the atom is a 3HG1.
   * @return if the atom is a 3HG1.
   */
  virtual bool is_3HG1 () const { return false; }

  /**
   * Tells if the atom is a 3HG2.
   * @return if the atom is a 3HG2.
   */
  virtual bool is_3HG2 () const { return false; }

  /**
   * Tells if the atom is a MG.
   * @return if the atom is a MG.
   */
  virtual bool is_MG () const { return false; }

  /**
   * Tells if the atom is a PSAZ.
   * @return if the atom is a PSAZ.
   */
  virtual bool is_PSAZ () const { return false; }

  /**
   * Tells if the atom is connected to the type in the residue.
   * @param type the second atom.
   * @param res the residue where the atoms are.
   * @return wheter the atom is connected to type in res.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const
  { return false; }

  /**
   * Gets the Van Der Waals radius value for the atom.
   * @param res the residue that contains the atom.
   * @return the Van Der Waals radius value.
   */
  virtual float getVDWR (const CResidue *res) const = 0;

  /**
   * Gets the Amber epsilon value for the atom.
   * @param res the residue that contains the atom.
   * @return the Amber epsilon value.
   */
  virtual float getAmberEpsilon (const CResidue *res) const = 0;

  /**
   * Gets the Amber charge value for the atom in the given residue type.
   * @param res the residue type.
   * @return the Amber charge.
   */
  virtual float getAmberCharge (const CResidue *res) const = 0;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.  Each type must define a
   * unique integer value.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * Inputs the atom type.  The integer type is read and the type object is
 * assigned to the pointer.
 * @param ibs the input binary stream.
 * @param t the atom type pointer to fill.
 * @return the input binary stream used.
 */
iBinstream& operator>> (iBinstream &in, t_Atom *&t);



/**
 * Outputs the atom type through a binary stream.  The type is dumped as an
 * integer.
 * @param obs the binary output stream.
 * @param t the type to dump.
 * @return the output binary stream used.
 */
oBinstream& operator<< (oBinstream &out, const t_Atom *t);

#endif
