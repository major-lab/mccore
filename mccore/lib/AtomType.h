//                              -*- Mode: C++ -*- 
// AtomType.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Jan 23 15:01:16 2001
// Update Count     : 4
// Status           : Ok.
// 


#ifndef _AtomType_h_
#define _AtomType_h_


class t_Atom;
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
   * Converts the atom type to an Amber string representation.
   * @return "ATOM".
   */
  virtual const char* AmberRep () const { return "ATOM"; }
  
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
   * Tells if the atom is connected to the type in the residue.
   * @param type the second atom.
   * @param res the residue where the atoms are.
   * @return wheter the atom is connected to type in res.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const
  { return false; }

  /**
   * Gets the Van Der Waals radius value for the atom.
   * @return the Van Der Waals radius value.
   */
  virtual float GetVDWR () const { return 0; }

  /**
   * Gets the Amber epsilon value for the atom.
   * @return the Amber epsilon value.
   */
  virtual float get_epsilon () const { return 0; }

  /**
   * Gets the Amber charge value for the atom in the given residue type.
   * Throws a CFatalLibException when the chage is not defined.
   * @param res the residue type.
   * @exception CFatalLibException
   * @return the Amber charge.
   */
  virtual float get_charge (const t_Residue *res) const;

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



/**
 * @short The atom type for general or unknown atoms.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Misc : public virtual t_Atom
{
  /**
   * The stripped name of the atom.
   */
  char mSName[5];

  /**
   * The name of the atom.
   */
  char mName[5];

  /**
   * Initializes the objet.  It should never be used.
   */
  at_Misc () : t_Atom () { }
  
  /**
   * Gets the first alpha-numeric character of a the name.
   * @return the first alpha-numeric character.
   */
  char GetFirstAlpha () const;
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   * @param sn the stripped atom name.
   * @param n the name of the atom.
   */
  at_Misc (const char *sn, const char *n);

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Misc (const at_Misc &right);

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Misc () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Misc& operator= (const at_Misc &right);

  /**
   * Converts the atom type to a string.
   * @return the name of the atom.
   */
  virtual operator const char* () const { return mName; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return the name of the atom.
   */
  virtual const char* AmberRep () const { return mName; }
  
  /**
   * Tells if the atom is an unknown atom.
   * @return true.
   */
  virtual bool is_Misc () const { return true; }

  /**
   * Tells if the atom is a carbon by searching it's name.
   * @return if the atom is a carbon.
   */
  virtual bool is_Carbon () const { return GetFirstAlpha () == 'C'; }

  /**
   * Tells if the atom is an hydrogen by searching it's name.
   * @return if the atom is an hydrogen.
   */
  virtual bool is_Hydrogen () const { return GetFirstAlpha () == 'H'; }

  /**
   * Tells if the atom is a magnesium by searching it's name.
   * @return if the atom is a magnesium.
   */
  virtual bool is_Magnesium () const { return GetFirstAlpha () == 'M'; }

  /**
   * Tells if the atom is a nitrogen by searching it's name.
   * @return if the atom is a nitrogen.
   */
  virtual bool is_Nitrogen () const { return GetFirstAlpha () == 'N'; }

  /**
   * Tells if the atom is a phosphate by searching it's name.
   * @return if the atom is a phosphate.
   */
  virtual bool is_Phosphate () const { return GetFirstAlpha () == 'P'; }

  /**
   * Tells if the atom is an oxygen by searching it's name.
   * @return if the atom is an oxygen.
   */
  virtual bool is_Oxygen () const { return GetFirstAlpha () == 'O'; }

  /**
   * Tells if the atom is a sulfur by searching it's name.
   * @return if the atom is a sulfur.
   */
  virtual bool is_Sulfur () const { return GetFirstAlpha () == 'S'; }

  /**
   * Tells if the atom is a lonepair by searching it's name.
   * @return if the atom is a lonepair.
   */
  virtual bool is_LonePair () const { return GetFirstAlpha () == 'L'; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general atom type for nucleic acid.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_NucleicAcid : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NucleicAcid () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NucleicAcid (const at_NucleicAcid &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NucleicAcid () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NucleicAcid& operator= (const at_NucleicAcid &right);

  /**
   * Converts the atom type to a string.
   * @return "NucleicAcid".
   */
  virtual operator const char* () const { return "NucleicAcid"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NucleicAcid".
   */
  virtual const char* AmberRep () const { return "NucleicAcid"; }
  
  /**
   * Tells if the atom is a nucleic acid.
   * @return true.
   */
  virtual bool is_NucleicAcid () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general atom type for protein.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_AminoAcid : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_AminoAcid () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_AminoAcid (const at_AminoAcid &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_AminoAcid () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_AminoAcid& operator= (const at_AminoAcid &right);

  /**
   * Converts the atom type to a string.
   * @return "AminoAcid".
   */
  virtual operator const char* () const { return "AminoAcid"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "AminoAcid".
   */
  virtual const char* AmberRep () const { return "AminoAcid"; }

  /**
   * Tells if the atom is a protein.
   * @return true.
   */
  virtual bool is_AminoAcid () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general backbone atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Backbone : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Backbone () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Backbone (const at_Backbone &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Backbone () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Backbone& operator= (const at_Backbone &right);

  /**
   * Converts the atom type to a string.
   * @return "Backbone".
   */
  virtual operator const char* () const { return "Backbone"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "Backbone".
   */
  virtual const char* AmberRep () const { return "Backbone"; }

  /**
   * Tells if the atom is part of the backbone.
   * @return true.
   */
  virtual bool is_Backbone () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general side chain atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_SideChain : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_SideChain () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_SideChain (const at_SideChain &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_SideChain () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_SideChain& operator= (const at_SideChain &right);

  /**
   * Converts the atom type to a string.
   * @return "SideChain".
   */
  virtual operator const char* () const { return "SideChain"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "SideChain".
   */
  virtual const char* AmberRep () const { return "SideChain"; }

  /**
   * Tells if the atom is part of the side chain.
   * @return true.
   */
  virtual bool is_SideChain () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general carbon atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Carbon : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Carbon () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Carbon (const at_Carbon &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Carbon () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Carbon& operator= (const at_Carbon &right);

  /**
   * Converts the atom type to a string.
   * @return "Carbon".
   */
  virtual operator const char* () const { return "Carbon"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C".
   */
  virtual const char* AmberRep () const { return "C"; }

  /**
   * Tells if the atom is a carbon.
   * @return true.
   */
  virtual bool is_Carbon () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general hydrogen atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Hydrogen : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Hydrogen () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Hydrogen (const at_Hydrogen &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Hydrogen () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Hydrogen& operator= (const at_Hydrogen &right);

  /**
   * Converts the atom type to a string.
   * @return "Hydrogen".
   */
  virtual operator const char* () const { return "Hydrogen"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H".
   */
  virtual const char* AmberRep () const { return "H"; }

  /**
   * Tells if the atom is a hydrogen.
   * @return true.
   */
  virtual bool is_Hydrogen () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general nitrogen atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Nitrogen : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Nitrogen () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Nitrogen (const at_Nitrogen &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Nitrogen () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Nitrogen& operator= (const at_Nitrogen &right);

  /**
   * Converts the atom type to a string.
   * @return "Nitrogen".
   */
  virtual operator const char* () const { return "Nitrogen"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N".
   */
  virtual const char* AmberRep () const { return "N"; }

  /**
   * Tells if the atom is a nitrogen.
   * @return true.
   */
  virtual bool is_Nitrogen () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general phosphate atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Phosphate : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Phosphate () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Phosphate (const at_Phosphate &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Phosphate () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Phosphate& operator= (const at_Phosphate &right);

  /**
   * Converts the atom type to a string.
   * @return "Phosphate".
   */
  virtual operator const char* () const { return "Phosphate"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "P".
   */
  virtual const char* AmberRep () const { return "P"; }

  /**
   * Tells if the atom is a phosphate.
   * @return true.
   */
  virtual bool is_Phosphate () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general oxygen atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Oxygen : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Oxygen () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Oxygen (const at_Oxygen &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Oxygen () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Oxygen& operator= (const at_Oxygen &right);

  /**
   * Converts the atom type to a string.
   * @return "Oxygen".
   */
  virtual operator const char* () const { return "Oxygen"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O".
   */
  virtual const char* AmberRep () const { return "O"; }

  /**
   * Tells if the atom is an oxygen.
   * @return true.
   */
  virtual bool is_Oxygen () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general carbon atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_Sulfur : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Sulfur () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Sulfur (const at_Sulfur &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Sulfur () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Sulfur& operator= (const at_Sulfur &right);

  /**
   * Converts the atom type to a string.
   * @return "Sulfur".
   */
  virtual operator const char* () const { return "Sulfur"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "S".
   */
  virtual const char* AmberRep () const { return "S"; }

  /**
   * Tells if the atom is a carbon.
   * @return true.
   */
  virtual bool is_Sulfur () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general hydrogen atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_Magnesium : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Magnesium () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Magnesium (const at_Magnesium &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Magnesium () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Magnesium& operator= (const at_Magnesium &right);

  /**
   * Converts the atom type to a string.
   * @return "Magnesium".
   */
  virtual operator const char* () const { return "Magnesium"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "MG".
   */
  virtual const char* AmberRep () const { return "MG"; }

  /**
   * Tells if the atom is a magnesium.
   * @return true.
   */
  virtual bool is_Magnesium () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general lone pair atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_LonePair : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_LonePair () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_LonePair (const at_LonePair &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_LonePair () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_LonePair& operator= (const at_LonePair &right);

  /**
   * Converts the atom type to a string.
   * @return "LonePair".
   */
  virtual operator const char* () const { return "LonePair"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "LonePair".
   */
  virtual const char* AmberRep () const { return "LonePair"; }

  /**
   * Tells if the atom is a lone pair.
   * @return true.
   */
  virtual bool is_LonePair () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general pseudo atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_Pseudo : public virtual t_Atom
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_Pseudo () : t_Atom () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_Pseudo (const at_Pseudo &right) : t_Atom (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_Pseudo () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_Pseudo& operator= (const at_Pseudo &right);

  /**
   * Converts the atom type to a string.
   * @return "Pseudo".
   */
  virtual operator const char* () const { return "Pseudo"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "Pseudo".
   */
  virtual const char* AmberRep () const { return "Pseudo"; }

  /**
   * Tells if the atom is a pseudo atom.
   * @return true.
   */
  virtual bool is_Pseudo () const { return true; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C1p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C1p : public virtual at_NucleicAcid, 
	       public virtual at_Carbon, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C1p () : at_NucleicAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C1p (const at_C1p &right)
    : at_NucleicAcid (right),  at_Carbon (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C1p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C1p& operator= (const at_C1p &right);

  /**
   * Converts the atom type to a string.
   * @return "C1*".
   */
  virtual operator const char* () const { return "C1*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C1'".
   */
  virtual const char* AmberRep () const { return "C1'"; }

  /**
   * Tells if the atom is a C1p.
   * @return true.
   */
  virtual bool is_C1p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1094.
   */
  virtual float get_epsilon () const { return 0.1094; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C2p : public virtual at_NucleicAcid,
	       public virtual at_Carbon, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C2p () : at_NucleicAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C2p (const at_C2p &right)
    : at_NucleicAcid (right),  at_Carbon (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C2p& operator= (const at_C2p &right);

  /**
   * Converts the atom type to a string.
   * @return "C2*".
   */
  virtual operator const char* () const { return "C2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C2'".
   */
  virtual const char* AmberRep () const { return "C2'"; }

  /**
   * Tells if the atom is a C2p.
   * @return true.
   */
  virtual bool is_C2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C3p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C3p : public virtual at_NucleicAcid,
	       public virtual at_Carbon, 
	       public virtual at_Backbone
{
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C3p () : at_NucleicAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C3p (const at_C3p &right)
    : at_NucleicAcid (right),  at_Carbon (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C3p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C3p& operator= (const at_C3p &right);

  /**
   * Converts the atom type to a string.
   * @return "C3*".
   */
  virtual operator const char* () const { return "C3*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C3'".
   */
  virtual const char* AmberRep () const { return "C3'"; }

  /**
   * Tells if the atom is a C3p.
   * @return true.
   */
  virtual bool is_C3p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C4p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C4p : public virtual at_NucleicAcid,
	       public virtual at_Carbon, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C4p () : at_NucleicAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C4p (const at_C4p &right)
    : at_NucleicAcid (right), at_Carbon (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C4p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C4p& operator= (const at_C4p &right);

  /**
   * Converts the atom type to a string.
   * @return "C4*".
   */
  virtual operator const char* () const { return "C4*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C4'".
   */
  virtual const char* AmberRep () const { return "C4'"; }

  /**
   * Tells if the atom is a C4p.
   * @return true.
   */
  virtual bool is_C4p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C5p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C5p : public virtual at_NucleicAcid,
	       public virtual at_Carbon, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C5p () : at_NucleicAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C5p (const at_C5p &right)
    : at_NucleicAcid (right), at_Carbon (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C5p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C5p& operator= (const at_C5p &right);

  /**
   * Converts the atom type to a string.
   * @return "C5*".
   */
  virtual operator const char* () const { return "C5*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C5'".
   */
  virtual const char* AmberRep () const { return "C5'"; }

  /**
   * Tells if the atom is a C5p.
   * @return true.
   */
  virtual bool is_C5p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H1p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H1p : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H1p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H1p (const at_H1p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H1p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H1p& operator= (const at_H1p &right);

  /**
   * Converts the atom type to a string.
   * @return "H1*".
   */
  virtual operator const char* () const { return "H1*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H1'".
   */
  virtual const char* AmberRep () const { return "H1'"; }

  /**
   * Tells if the atom is a H1p.
   * @return true.
   */
  virtual bool is_H1p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.29.
   */
  virtual float GetVDWR () const { return 1.29; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H2p : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H2p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H2p (const at_H2p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H2p& operator= (const at_H2p &right);

  /**
   * Converts the atom type to a string.
   * @return "H2*".
   */
  virtual operator const char* () const { return "H2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H2'".
   */
  virtual const char* AmberRep () const { return "H2'"; }

  /**
   * Tells if the atom is a H2p.
   * @return true.
   */
  virtual bool is_H2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.36.
   */
  virtual float GetVDWR () const { return 1.36; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H3p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H3p : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H3p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H3p (const at_H3p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H3p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H3p& operator= (const at_H3p &right);

  /**
   * Converts the atom type to a string.
   * @return "H3*".
   */
  virtual operator const char* () const { return "H3*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H3'".
   */
  virtual const char* AmberRep () const { return "H3'"; }

  /**
   * Tells if the atom is a H3p.
   * @return true.
   */
  virtual bool is_H3p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H4p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H4p : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H4p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H4p (const at_H4p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H4p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H4p& operator= (const at_H4p &right);

  /**
   * Converts the atom type to a string.
   * @return "H4*".
   */
  virtual operator const char* () const { return "H4*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H4'".
   */
  virtual const char* AmberRep () const { return "H4'"; }

  /**
   * Tells if the atom is a H4p.
   * @return true.
   */
  virtual bool is_H4p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H5p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H5p : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H5p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H5p (const at_H5p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H5p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H5p& operator= (const at_H5p &right);

  /**
   * Converts the atom type to a string.
   * @return "H5*".
   */
  virtual operator const char* () const { return "H5*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H5'".
   */
  virtual const char* AmberRep () const { return "H5'"; }

  /**
   * Tells if the atom is a H5p.
   * @return true.
   */
  virtual bool is_H5p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O1P atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O1P : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O1P () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O1P (const at_O1P &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O1P () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O1P& operator= (const at_O1P &right);

  /**
   * Converts the atom type to a string.
   * @return "O1P".
   */
  virtual operator const char* () const { return "O1P"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O1P".
   */
  virtual const char* AmberRep () const { return "O1P"; }

  /**
   * Tells if the atom is a O1P.
   * @return true.
   */
  virtual bool is_O1P () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O2p : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O2p () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O2p (const at_O2p &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O2p& operator= (const at_O2p &right);

  /**
   * Converts the atom type to a string.
   * @return "O2*".
   */
  virtual operator const char* () const { return "O2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O2'".
   */
  virtual const char* AmberRep () const { return "O2'"; }

  /**
   * Tells if the atom is a O2p.
   * @return true.
   */
  virtual bool is_O2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O2P atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O2P : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O2P () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O2P (const at_O2P &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O2P () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O2P& operator= (const at_O2P &right);

  /**
   * Converts the atom type to a string.
   * @return "O2P".
   */
  virtual operator const char* () const { return "O2P"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O2P".
   */
  virtual const char* AmberRep () const { return "O2P"; }

  /**
   * Tells if the atom is a O2P.
   * @return true.
   */
  virtual bool is_O2P () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O3p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O3p : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O3p () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O3p (const at_O3p &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O3p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O3p& operator= (const at_O3p &right);

  /**
   * Converts the atom type to a string.
   * @return "O3*".
   */
  virtual operator const char* () const { return "O3*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O3'".
   */
  virtual const char* AmberRep () const { return "O3'"; }

  /**
   * Tells if the atom is a O3p.
   * @return true.
   */
  virtual bool is_O3p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O3P atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O3P : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O3P () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O3P (const at_O3P &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O3P () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O3P& operator= (const at_O3P &right);

  /**
   * Converts the atom type to a string.
   * @return "O3P".
   */
  virtual operator const char* () const { return "O3P"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O3P".
   */
  virtual const char* AmberRep () const { return "O3P"; }

  /**
   * Tells if the atom is a O3P.
   * @return true.
   */
  virtual bool is_O3P () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O4p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O4p : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O4p () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O4p (const at_O4p &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O4p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O4p& operator= (const at_O4p &right);

  /**
   * Converts the atom type to a string.
   * @return "O4*".
   */
  virtual operator const char* () const { return "O4*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O4'".
   */
  virtual const char* AmberRep () const { return "O4'"; }

  /**
   * Tells if the atom is a O4p.
   * @return true.
   */
  virtual bool is_O4p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.68.
   */
  virtual float GetVDWR () const { return 1.68; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O5p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O5p : public virtual at_NucleicAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O5p () : at_NucleicAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O5p (const at_O5p &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O5p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O5p& operator= (const at_O5p &right);

  /**
   * Converts the atom type to a string.
   * @return "O5*".
   */
  virtual operator const char* () const { return "O5*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O5'".
   */
  virtual const char* AmberRep () const { return "O5'"; }

  /**
   * Tells if the atom is a O5p.
   * @return true.
   */
  virtual bool is_O5p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The P atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_P : public virtual at_NucleicAcid,
	     public virtual at_Phosphate, 
	     public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_P () : at_NucleicAcid (), at_Phosphate (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_P (const at_P &right)
    : at_NucleicAcid (right), at_Phosphate (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_P () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_P& operator= (const at_P &right);

  /**
   * Converts the atom type to a string.
   * @return "P".
   */
  virtual operator const char* () const { return "P"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "P".
   */
  virtual const char* AmberRep () const { return "P"; }

  /**
   * Tells if the atom is a P.
   * @return true.
   */
  virtual bool is_P () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 2.10.
   */
  virtual float GetVDWR () const { return 2.10; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &out) const;
};



/**
 * @short The 1H2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H2p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H2p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H2p (const at_1H2p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H2p& operator= (const at_1H2p &right);

  /**
   * Converts the atom type to a string.
   * @return "1H2*".
   */
  virtual operator const char* () const { return "1H2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H2'1".
   */
  virtual const char* AmberRep () const { return "H2'1"; }

  /**
   * Tells if the atom is a 1H2p.
   * @return true.
   */
  virtual bool is_1H2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H5p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H5p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H5p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H5p (const at_1H5p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H5p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H5p& operator= (const at_1H5p &right);

  /**
   * Converts the atom type to a string.
   * @return "1H5*".
   */
  virtual operator const char* () const { return "1H5*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H5'1".
   */
  virtual const char* AmberRep () const { return "H5'1"; }

  /**
   * Tells if the atom is a 1H5p.
   * @return true.
   */
  virtual bool is_1H5p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H2p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H2p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H2p (const at_2H2p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H2p& operator= (const at_2H2p &right);

  /**
   * Converts the atom type to a string.
   * @return "2H2*".
   */
  virtual operator const char* () const { return "2H2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H2'2".
   */
  virtual const char* AmberRep () const { return "H2'2"; }

  /**
   * Tells if the atom is a 2H2p.
   * @return true.
   */
  virtual bool is_2H2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H5p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H5p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H5p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H5p (const at_2H5p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H5p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H5p& operator= (const at_2H5p &right);

  /**
   * Converts the atom type to a string.
   * @return "2H5*".
   */
  virtual operator const char* () const { return "2H5*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H5'2".
   */
  virtual const char* AmberRep () const { return "H5'2"; }

  /**
   * Tells if the atom is a 2H5p.
   * @return true.
   */
  virtual bool is_2H5p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HO2p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_HO2p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HO2p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HO2p (const at_HO2p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HO2p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HO2p& operator= (const at_HO2p &right);

  /**
   * Converts the atom type to a string.
   * @return "HO2*".
   */
  virtual operator const char* () const { return "HO2*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HO'2".
   */
  virtual const char* AmberRep () const { return "HO'2"; }

  /**
   * Tells if the atom is a HO2p.
   * @return true.
   */
  virtual bool is_HO2p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;  
};



/**
 * @short The HO3p atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_HO3p : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HO3p () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HO3p (const at_HO3p &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HO3p () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HO3p& operator= (const at_HO3p &right);

  /**
   * Converts the atom type to a string.
   * @return "HO3*".
   */
  virtual operator const char* () const { return "HO3*"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HO'3".
   */
  virtual const char* AmberRep () const { return "HO'3"; }

  /**
   * Tells if the atom is a HO3p.
   * @return true.
   */
  virtual bool is_HO3p () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C2 : public virtual at_NucleicAcid,
	      public virtual at_Carbon, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C2 () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C2 (const at_C2 &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C2& operator= (const at_C2 &right);

  /**
   * Converts the atom type to a string.
   * @return "C2".
   */
  virtual operator const char* () const { return "C2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C2".
   */
  virtual const char* AmberRep () const { return "C2"; }

  /**
   * Tells if the atom is a C2.
   * @return true.
   */
  virtual bool is_C2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0860.
   */
  virtual float get_epsilon () const { return 0.0860; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C4 : public virtual at_NucleicAcid,
	      public virtual at_Carbon, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C4 () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C4 (const at_C4 &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C4& operator= (const at_C4 &right);

  /**
   * Converts the atom type to a string.
   * @return "C4".
   */
  virtual operator const char* () const { return "C4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C4".
   */
  virtual const char* AmberRep () const { return "C4"; }

  /**
   * Tells if the atom is a C4.
   * @return true.
   */
  virtual bool is_C4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0860.
   */
  virtual float get_epsilon () const { return 0.0860; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C5 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C5 : public virtual at_NucleicAcid,
	      public virtual at_Carbon, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C5 () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C5 (const at_C5 &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C5 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C5& operator= (const at_C5 &right);

  /**
   * Converts the atom type to a string.
   * @return "C5".
   */
  virtual operator const char* () const { return "C5"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C5".
   */
  virtual const char* AmberRep () const { return "C5"; }

  /**
   * Tells if the atom is a C5.
   * @return true.
   */
  virtual bool is_C5 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0860.
   */
  virtual float get_epsilon () const { return 0.0860; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C5M atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C5M : public virtual at_NucleicAcid,
	       public virtual at_Carbon, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C5M () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C5M (const at_C5M &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C5M () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C5M& operator= (const at_C5M &right);

  /**
   * Converts the atom type to a string.
   * @return "C5M".
   */
  virtual operator const char* () const { return "C5M"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C7".
   */
  virtual const char* AmberRep () const { return "C7"; }

  /**
   * Tells if the atom is a C5M.
   * @return true.
   */
  virtual bool is_C5M () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C6 : public virtual at_NucleicAcid,
	      public virtual at_Carbon, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C6 () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C6 (const at_C6 &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C6& operator= (const at_C6 &right);

  /**
   * Converts the atom type to a string.
   * @return "C6".
   */
  virtual operator const char* () const { return "C6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C6".
   */
  virtual const char* AmberRep () const { return "C6"; }

  /**
   * Tells if the atom is a C6.
   * @return true.
   */
  virtual bool is_C6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0860.
   */
  virtual float get_epsilon () const { return 0.0860; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C8 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_C8 : public virtual at_NucleicAcid,
	      public virtual at_Carbon, 
	      public virtual at_SideChain
{

public:

    // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C8 () : at_NucleicAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C8 (const at_C8 &right)
    : at_NucleicAcid (right), at_Carbon (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C8 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C8& operator= (const at_C8 &right);

  /**
   * Converts the atom type to a string.
   * @return "C8".
   */
  virtual operator const char* () const { return "C8"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C8".
   */
  virtual const char* AmberRep () const { return "C8"; }

  /**
   * Tells if the atom is a C8.
   * @return true.
   */
  virtual bool is_C8 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.9080.
   */
  virtual float GetVDWR () const { return 1.9080; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0860.
   */
  virtual float get_epsilon () const { return 0.0860; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H1 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H1 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H1 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H1 (const at_H1 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H1& operator= (const at_H1 &right);

  /**
   * Converts the atom type to a string.
   * @return "H1".
   */
  virtual operator const char* () const { return "H1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H1".
   */
  virtual const char* AmberRep () const { return "H1"; }

  /**
   * Tells if the atom is a H1.
   * @return true.
   */
  virtual bool is_H1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H2 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H2 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H2 (const at_H2 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H2& operator= (const at_H2 &right);

  /**
   * Converts the atom type to a string.
   * @return "H2".
   */
  virtual operator const char* () const { return "H2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H2".
   */
  virtual const char* AmberRep () const { return "H2"; }

  /**
   * Tells if the atom is a H2.
   * @return true.
   */
  virtual bool is_H2 () const { return true; }

  /**
   * tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.3590.
   */
  virtual float GetVDWR () const { return 1.3590; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0150.
   */
  virtual float get_epsilon () const { return 0.0150; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H3 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H3 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H3 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H3 (const at_H3 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H3& operator= (const at_H3 &right);

  /**
   * Converts the atom type to a string.
   * @return "H3".
   */
  virtual operator const char* () const { return "H3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H3".
   */
  virtual const char* AmberRep () const { return "H3"; }

  /**
   * Tells if the atom is a H3.
   * @return true.
   */
  virtual bool is_H3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H5 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H5 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H5 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H5 (const at_H5 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H5 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H5& operator= (const at_H5 &right);

  /**
   * Converts the atom type to a string.
   * @return "H5".
   */
  virtual operator const char* () const { return "H5"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H5".
   */
  virtual const char* AmberRep () const { return "H5"; }

  /**
   * Tells if the atom is a H5.
   * @return true.
   */
  virtual bool is_H5 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.4590.
   */
  virtual float GetVDWR () const { return 1.4590; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0150.
   */
  virtual float get_epsilon () const { return 0.0150; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H6 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H6 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H6 (const at_H6 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H6& operator= (const at_H6 &right);

  /**
   * Converts the atom type to a string.
   * @return "H6".
   */
  virtual operator const char* () const { return "H6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H6".
   */
  virtual const char* AmberRep () const { return "H6"; }

  /**
   * Tells if the atom is a H6.
   * @return true.
   */
  virtual bool is_H6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.4090.
   */
  virtual float GetVDWR () const { return 1.4090; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0150.
   */
  virtual float get_epsilon () const { return 0.0150; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H7 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H7 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H7 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H7 (const at_H7 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H7 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H7& operator= (const at_H7 &right);

  /**
   * Converts the atom type to a string.
   * @return "H7".
   */
  virtual operator const char* () const { return "H7"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H7".
   */
  virtual const char* AmberRep () const { return "H7"; }

  /**
   * Tells if the atom is a H7.
   * @return true.
   */
  virtual bool is_H7 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H8 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H8 : public virtual at_NucleicAcid,
	      public virtual at_Hydrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H8 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H8 (const at_H8 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H8 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H8& operator= (const at_H8 &right);

  /**
   * Converts the atom type to a string.
   * @return "H8".
   */
  virtual operator const char* () const { return "H8"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H8".
   */
  virtual const char* AmberRep () const { return "H8"; }

  /**
   * Tells if the atom is a H8.
   * @return true.
   */
  virtual bool is_H8 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.3590.
   */
  virtual float GetVDWR () const { return 1.3590; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0150.
   */
  virtual float get_epsilon () const { return 0.0150; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N1 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N1 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N1 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N1 (const at_N1 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N1& operator= (const at_N1 &right);

  /**
   * Converts the atom type to a string.
   * @return "N1".
   */
  virtual operator const char* () const { return "N1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N1".
   */
  virtual const char* AmberRep () const { return "N1"; }

  /**
   * Tells if the atom is a N1.
   * @return true.
   */
  virtual bool is_N1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N2 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N2 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N2 (const at_N2 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N2& operator= (const at_N2 &right);

  /**
   * Converts the atom type to a string.
   * @return "N2".
   */
  virtual operator const char* () const { return "N2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N2".
   */
  virtual const char* AmberRep () const { return "N2"; }

  /**
   * Tells if the atom is a N2.
   * @return true.
   */
  virtual bool is_N2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &out) const;
};



/**
 * @short The N3 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N3 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N3 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N3 (const at_N3 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N3& operator= (const at_N3 &right);

  /**
   * Converts the atom type to a string.
   * @return "N3".
   */
  virtual operator const char* () const { return "N3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N3".
   */
  virtual const char* AmberRep () const { return "N3"; }

  /**
   * Tells if the atom is a N3.
   * @return true.
   */
  virtual bool is_N3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N4 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N4 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N4 (const at_N4 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N4& operator= (const at_N4 &right);

  /**
   * Converts the atom type to a string.
   * @return "N4".
   */
  virtual operator const char* () const { return "N4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N4".
   */
  virtual const char* AmberRep () const { return "N4"; }

  /**
   * Tells if the atom is a N4.
   * @return true.
   */
  virtual bool is_N4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &out) const;
};



/**
 * @short The N6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N6 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N6 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N6 (const at_N6 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N6& operator= (const at_N6 &right);

  /**
   * Converts the atom type to a string.
   * @return "N6".
   */
  virtual operator const char* () const { return "N6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N6".
   */
  virtual const char* AmberRep () const { return "N6"; }

  /**
   * Tells if the atom is a N6.
   * @return true.
   */
  virtual bool is_N6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N7 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N7 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N7 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N7 (const at_N7 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N7 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N7& operator= (const at_N7 &right);

  /**
   * Converts the atom type to a string.
   * @return "N7".
   */
  virtual operator const char* () const { return "N7"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N7".
   */
  virtual const char* AmberRep () const { return "N7"; }

  /**
   * Tells if the atom is a N7.
   * @return true.
   */
  virtual bool is_N7 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N9 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_N9 : public virtual at_NucleicAcid,
	      public virtual at_Nitrogen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N9 () : at_NucleicAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N9 (const at_N9 &right)
    : at_NucleicAcid (right), at_Nitrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N9 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N9& operator= (const at_N9 &right);

  /**
   * Converts the atom type to a string.
   * @return "N9".
   */
  virtual operator const char* () const { return "N9"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N9".
   */
  virtual const char* AmberRep () const { return "N9"; }

  /**
   * Tells if the atom is a N9.
   * @return true.
   */
  virtual bool is_N9 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.8240.
   */
  virtual float GetVDWR () const { return 1.8240; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.1700.
   */
  virtual float get_epsilon () const { return 0.1700; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O2 : public virtual at_NucleicAcid,
	      public virtual at_Oxygen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O2 () : at_NucleicAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O2 (const at_O2 &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O2& operator= (const at_O2 &right);

  /**
   * Converts the atom type to a string.
   * @return "O2".
   */
  virtual operator const char* () const { return "O2"; }

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O2".
   */
  virtual const char* AmberRep () const { return "O2"; }

  /**
   * Tells if the atom is a O2.
   * @return true.
   */
  virtual bool is_O2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.6612.
   */
  virtual float GetVDWR () const { return 1.6612; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.2100.
   */
  virtual float get_epsilon () const { return 0.2100; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O4 : public virtual at_NucleicAcid,
	      public virtual at_Oxygen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O4 () : at_NucleicAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O4 (const at_O4 &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O4& operator= (const at_O4 &right);

  /**
   * Converts the atom type to a string.
   * @return "O4".
   */
  virtual operator const char* () const { return "O4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O4".
   */
  virtual const char* AmberRep () const { return "O4"; }

  /**
   * Tells if the atom is a O4.
   * @return true.
   */
  virtual bool is_O4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.6612.
   */
  virtual float GetVDWR () const { return 1.6612; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.2100.
   */
  virtual float get_epsilon () const { return 0.2100; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &out) const;
};



/**
 * @short The O6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_O6 : public virtual at_NucleicAcid,
	      public virtual at_Oxygen, 
	      public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O6 () : at_NucleicAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O6 (const at_O6 &right)
    : at_NucleicAcid (right), at_Oxygen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O6& operator= (const at_O6 &right);

  /**
   * Converts the atom type to a string.
   * @return "O6".
   */
  virtual operator const char* () const { return "O6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O6".
   */
  virtual const char* AmberRep () const { return "O6"; }

  /**
   * Tells if the atom is a O6.
   * @return true.
   */
  virtual bool is_O6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.6612.
   */
  virtual float GetVDWR () const { return 1.6612; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.2100.
   */
  virtual float get_epsilon () const { return 0.2100; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H2 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H2 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H2 (const at_1H2 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H2& operator= (const at_1H2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1H2".
   */
  virtual operator const char* () const { return "1H2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H21".
   */
  virtual const char* AmberRep () const { return "H21"; }

  /**
   * Tells if the atom is a 1H2.
   * @return true.
   */
  virtual bool is_1H2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H4 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H4 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H4 (const at_1H4 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H4& operator= (const at_1H4 &right);

  /**
   * Converts the atom type to a string.
   * @return "1H4".
   */
  virtual operator const char* () const { return "1H4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H41".
   */
  virtual const char* AmberRep () const { return "H41"; }

  /**
   * Tells if the atom is a 1H4.
   * @return true.
   */
  virtual bool is_1H4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H5M atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H5M : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H5M () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H5M (const at_1H5M &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H5M () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H5M& operator= (const at_1H5M &right);

  /**
   * Converts the atom type to a string.
   * @return "1H5M".
   */
  virtual operator const char* () const { return "1H5M"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H71".
   */
  virtual const char* AmberRep () const { return "H71"; }

  /**
   * Tells if the atom is a 1H5M.
   * @return true.
   */
  virtual bool is_1H5M () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1H6 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H6 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H6 (const at_1H6 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H6& operator= (const at_1H6 &right);

  /**
   * Converts the atom type to a string.
   * @return "1H6".
   */
  virtual operator const char* () const { return "1H6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H61".
   */
  virtual const char* AmberRep () const { return "H61"; }

  /**
   * Tells if the atom is a 1H6.
   * @return true.
   */
  virtual bool is_1H6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H2 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H2 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H2 (const at_2H2 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H2& operator= (const at_2H2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2H2".
   */
  virtual operator const char* () const { return "2H2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H22".
   */
  virtual const char* AmberRep () const { return "H22"; }

  /**
   * Tells if the atom is a 2H2.
   * @return true.
   */
  virtual bool is_2H2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H4 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H4 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H4 (const at_2H4 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H4& operator= (const at_2H4 &right);

  /**
   * Converts the atom type to a string.
   * @return "2H4".
   */
  virtual operator const char* () const { return "2H4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H42".
   */
  virtual const char* AmberRep () const { return "H42"; }

  /**
   * Tells if the atom is a 2H4.
   * @return true.
   */
  virtual bool is_2H4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H5M atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H5M : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H5M () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H5M (const at_2H5M &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H5M () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H5M& operator= (const at_2H5M &right);

  /**
   * Converts the atom type to a string.
   * @return "2H5M".
   */
  virtual operator const char* () const { return "2H5M"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H72".
   */
  virtual const char* AmberRep () const { return "H72"; }

  /**
   * Tells if the atom is a 2H5M.
   * @return true.
   */
  virtual bool is_2H5M () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2H6 : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_SideChain
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H6 () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H6 (const at_2H6 &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H6& operator= (const at_2H6 &right);

  /**
   * Converts the atom type to a string.
   * @return "2H6".
   */
  virtual operator const char* () const { return "2H6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H62".
   */
  virtual const char* AmberRep () const { return "H62"; }

  /**
   * Tells if the atom is a 2H6.
   * @return true.
   */
  virtual bool is_2H6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6000.
   */
  virtual float GetVDWR () const { return 0.6000; }

  /**
   * Gets the Amber epsilon value.
   * @return 0.0157.
   */
  virtual float get_epsilon () const { return 0.0157; }

  /**
   * Gets the Amber atom charge value in residue r.
   * @param r the residue.
   * @return the charge value of the atom in the residue.
   */
  virtual float get_charge (const t_Residue *r) const;
  
  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3H5M atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_3H5M : public virtual at_NucleicAcid,
		public virtual at_Hydrogen, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3H5M () : at_NucleicAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3H5M (const at_3H5M &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3H5M () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3H5M& operator= (const at_3H5M &right);

  /**
   * Converts the atom type to a string.
   * @return "3H5M".
   */
  virtual operator const char* () const { return "3H5M"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H73".
   */
  virtual const char* AmberRep () const { return "H73"; }

  /**
   * Tells if the atom is a 3H5M.
   * @return true.
   */
  virtual bool is_3H5M () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.60.
   */
  virtual float GetVDWR () const { return 0.60; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The PSY atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_PSY : public virtual at_NucleicAcid,
	       public virtual at_Pseudo, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_PSY () : at_NucleicAcid (), at_Pseudo (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_PSY (const at_PSY &right)
    : at_NucleicAcid (right), at_Pseudo (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_PSY () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_PSY& operator= (const at_PSY &right);

  /**
   * Converts the atom type to a string.
   * @return "PSY".
   */
  virtual operator const char* () const { return "PSY"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "PSY".
   */
  virtual const char* AmberRep () const { return "PSY"; }

  /**
   * Tells if the atom is a PSY.
   * @return true.
   */
  virtual bool is_PSY () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The PSZ atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_PSZ : public virtual at_NucleicAcid,
	       public virtual at_Pseudo, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_PSZ () : at_NucleicAcid (), at_Pseudo (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_PSZ (const at_PSZ &right)
    : at_NucleicAcid (right), at_Pseudo (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_PSZ () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_PSZ& operator= (const at_PSZ &right);

  /**
   * Converts the atom type to a string.
   * @return "PSZ".
   */
  virtual operator const char* () const { return "PSZ"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "PSZ".
   */
  virtual const char* AmberRep () const { return "PSZ"; }

  /**
   * Tells if the atom is a PSZ.
   * @return true.
   */
  virtual bool is_PSZ () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The LP1 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_LP1 : public virtual at_NucleicAcid,
	       public virtual at_LonePair, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_LP1 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_LP1 (const at_LP1 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_LP1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_LP1& operator= (const at_LP1 &right);

  /**
   * Converts the atom type to a string.
   * @return "LP1".
   */
  virtual operator const char* () const { return "LP1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "LP1".
   */
  virtual const char* AmberRep () const { return "LP1"; }

  /**
   * Tells if the atom is a LP1.
   * @return true.
   */
  virtual bool is_LP1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The LP3 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_LP3 : public virtual at_NucleicAcid,
	       public virtual at_LonePair, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_LP3 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_LP3 (const at_LP3 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_LP3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_LP3& operator= (const at_LP3 &right);

  /**
   * Converts the atom type to a string.
   * @return "LP3".
   */
  virtual operator const char* () const { return "LP3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "LP3".
   */
  virtual const char* AmberRep () const { return "LP3"; }

  /**
   * Tells if the atom is a LP3.
   * @return true.
   */
  virtual bool is_LP3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The LP7 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_LP7 : public virtual at_NucleicAcid,
	       public virtual at_LonePair, 
	       public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_LP7 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_LP7 (const at_LP7 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_LP7 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_LP7& operator= (const at_LP7 &right);

  /**
   * Converts the atom type to a string.
   * @return "LP7".
   */
  virtual operator const char* () const { return "LP7"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "LP7".
   */
  virtual const char* AmberRep () const { return "LP7"; }

  /**
   * Tells if the atom is a LP7.
   * @return true.
   */
  virtual bool is_LP7 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1LP2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1LP2 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1LP2 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1LP2 (const at_1LP2 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1LP2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1LP2& operator= (const at_1LP2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1LP2".
   */
  virtual operator const char* () const { return "1LP2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "1LP2".
   */
  virtual const char* AmberRep () const { return "1LP2"; }

  /**
   * Tells if the atom is a 1LP2.
   * @return true.
   */
  virtual bool is_1LP2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1LP4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1LP4 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1LP4 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1LP4 (const at_1LP4 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1LP4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1LP4& operator= (const at_1LP4 &right);

  /**
   * Converts the atom type to a string.
   * @return "1LP4".
   */
  virtual operator const char* () const { return "1LP4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "1LP4".
   */
  virtual const char* AmberRep () const { return "1LP4"; }

  /**
   * Tells if the atom is a 1LP4.
   * @return true.
   */
  virtual bool is_1LP4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1LP6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_1LP6 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1LP6 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1LP6 (const at_1LP6 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1LP6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1LP6& operator= (const at_1LP6 &right);

  /**
   * Converts the atom type to a string.
   * @return "1LP6".
   */
  virtual operator const char* () const { return "1LP6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "1LP6".
   */
  virtual const char* AmberRep () const { return "1LP6"; }

  /**
   * Tells if the atom is a 1LP6.
   * @return true.
   */
  virtual bool is_1LP6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2LP2 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2LP2 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2LP2 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2LP2 (const at_2LP2 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2LP2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2LP2& operator= (const at_2LP2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2LP2".
   */
  virtual operator const char* () const { return "2LP2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "2LP2".
   */
  virtual const char* AmberRep () const { return "2LP2"; }

  /**
   * Tells if the atom is a 2LP2.
   * @return true.
   */
  virtual bool is_2LP2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2LP4 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2LP4 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2LP4 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2LP4 (const at_2LP4 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2LP4 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2LP4& operator= (const at_2LP4 &right);

  /**
   * Converts the atom type to a string.
   * @return "2LP4".
   */
  virtual operator const char* () const { return "2LP4"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "2LP4".
   */
  virtual const char* AmberRep () const { return "2LP4"; }

  /**
   * Tells if the atom is a 2LP4.
   * @return true.
   */
  virtual bool is_2LP4 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2LP6 atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_2LP6 : public virtual at_NucleicAcid,
		public virtual at_LonePair, 
		public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2LP6 () : at_NucleicAcid (), at_LonePair (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2LP6 (const at_2LP6 &right)
    : at_NucleicAcid (right), at_LonePair (right), at_SideChain (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2LP6 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2LP6& operator= (const at_2LP6 &right);

  /**
   * Converts the atom type to a string.
   * @return "2LP6".
   */
  virtual operator const char* () const { return "2LP6"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "2LP6".
   */
  virtual const char* AmberRep () const { return "2LP6"; }

  /**
   * Tells if the atom is a 2LP6.
   * @return true.
   */
  virtual bool is_2LP6 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.30.
   */
  virtual float GetVDWR () const { return 0.30; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H3T atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H3T : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H3T () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H3T (const at_H3T &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H3T () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H3T& operator= (const at_H3T &right);

  /**
   * Converts the atom type to a string.
   * @return "H3T".
   */
  virtual operator const char* () const { return "H3T"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H3T".
   */
  virtual const char* AmberRep () const { return "H3T"; }

  /**
   * Tells if the atom is a H3T.
   * @return true.
   */
  virtual bool is_H3T () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H5T atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_H5T : public virtual at_NucleicAcid,
	       public virtual at_Hydrogen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H5T () : at_NucleicAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H5T (const at_H5T &right)
    : at_NucleicAcid (right), at_Hydrogen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H5T () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H5T& operator= (const at_H5T &right);

  /**
   * Converts the atom type to a string.
   * @return "H5T".
   */
  virtual operator const char* () const { return "H5T"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H5T".
   */
  virtual const char* AmberRep () const { return "H5T"; }

  /**
   * Tells if the atom is a H5T.
   * @return true.
   */
  virtual bool is_H5T () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The C atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_C : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_C () : at_AminoAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_C (const at_C &right)
    : at_AminoAcid (right), at_Carbon (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_C () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_C& operator= (const at_C &right);

  /**
   * Converts the atom type to a string.
   * @return "C".
   */
  virtual operator const char* () const { return "C"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "C".
   */
  virtual const char* AmberRep () const { return "C"; }

  /**
   * Tells if the atom is a C.
   * @return true.
   */
  virtual bool is_C () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CA atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CA : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CA () : at_AminoAcid (), at_Carbon (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CA (const at_CA &right)
    : at_AminoAcid (right), at_Carbon (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CA () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CA& operator= (const at_CA &right);

  /**
   * Converts the atom type to a string.
   * @return "CA".
   */
  virtual operator const char* () const { return "CA"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CA".
   */
  virtual const char* AmberRep () const { return "CA"; }

  /**
   * Tells if the atom is a CA.
   * @return true.
   */
  virtual bool is_CA () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CB atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CB : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CB () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CB (const at_CB &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CB () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CB& operator= (const at_CB &right);

  /**
   * Converts the atom type to a string.
   * @return "CB".
   */
  virtual operator const char* () const { return "CB"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CB".
   */
  virtual const char* AmberRep () const { return "CB"; }

  /**
   * Tells if the atom is a CB.
   * @return true.
   */
  virtual bool is_CB () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CD atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CD : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CD () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CD (const at_CD &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CD () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CD& operator= (const at_CD &right);

  /**
   * Converts the atom type to a string.
   * @return "CD".
   */
  virtual operator const char* () const { return "CD"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CD".
   */
  virtual const char* AmberRep () const { return "CD"; }

  /**
   * Tells if the atom is a CD.
   * @return true.
   */
  virtual bool is_CD () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CD1 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CD1 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CD1 (const at_CD1 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CD1& operator= (const at_CD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "CD1".
   */
  virtual operator const char* () const { return "CD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CD1".
   */
  virtual const char* AmberRep () const { return "CD1"; }

  /**
   * Tells if the atom is a CD1.
   * @return true.
   */
  virtual bool is_CD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CD2 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CD2 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CD2 (const at_CD2 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CD2& operator= (const at_CD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "CD2".
   */
  virtual operator const char* () const { return "CD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CD2".
   */
  virtual const char* AmberRep () const { return "CD2"; }

  /**
   * Tells if the atom is a CD2.
   * @return true.
   */
  virtual bool is_CD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CE atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CE : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CE () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CE (const at_CE &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CE () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CE& operator= (const at_CE &right);

  /**
   * Converts the atom type to a string.
   * @return "CE".
   */
  virtual operator const char* () const { return "CE"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CE".
   */
  virtual const char* AmberRep () const { return "CD"; }

  /**
   * Tells if the atom is a CE.
   * @return true.
   */
  virtual bool is_CE () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CE1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CE1 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CE1 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CE1 (const at_CE1 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CE1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CE1& operator= (const at_CE1 &right);

  /**
   * Converts the atom type to a string.
   * @return "CE1".
   */
  virtual operator const char* () const { return "CE1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CE1".
   */
  virtual const char* AmberRep () const { return "CE1"; }

  /**
   * Tells if the atom is a CE1.
   * @return true.
   */
  virtual bool is_CE1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CE2 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CE2 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CE2 (const at_CE2 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CE2& operator= (const at_CE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "CE2".
   */
  virtual operator const char* () const { return "CE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CE2".
   */
  virtual const char* AmberRep () const { return "CE2"; }

  /**
   * Tells if the atom is a CE2.
   * @return true.
   */
  virtual bool is_CE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CE3 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CE3 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CE3 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CE3 (const at_CE3 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CE3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CE3& operator= (const at_CE3 &right);

  /**
   * Converts the atom type to a string.
   * @return "CE3".
   */
  virtual operator const char* () const { return "CE3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CE3".
   */
  virtual const char* AmberRep () const { return "CE3"; }

  /**
   * Tells if the atom is a CE3.
   * @return true.
   */
  virtual bool is_CE3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CG atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CG : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CG () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CG (const at_CG &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CG& operator= (const at_CG &right);

  /**
   * Converts the atom type to a string.
   * @return "CG".
   */
  virtual operator const char* () const { return "CG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CG".
   */
  virtual const char* AmberRep () const { return "CG"; }

  /**
   * Tells if the atom is a CG.
   * @return true.
   */
  virtual bool is_CG () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CG1 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CG1 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CG1 (const at_CG1 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CG1& operator= (const at_CG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "CG1".
   */
  virtual operator const char* () const { return "CG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CG1".
   */
  virtual const char* AmberRep () const { return "CG1"; }

  /**
   * Tells if the atom is a CG1.
   * @return true.
   */
  virtual bool is_CG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CG2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CG2 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CG2 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CG2 (const at_CG2 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CG2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CG2& operator= (const at_CG2 &right);

  /**
   * Converts the atom type to a string.
   * @return "CG2".
   */
  virtual operator const char* () const { return "CG2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CG2".
   */
  virtual const char* AmberRep () const { return "CG2"; }

  /**
   * Tells if the atom is a CG2.
   * @return true.
   */
  virtual bool is_CG2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CH2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CH2 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CH2 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CH2 (const at_CH2 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CH2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CH2& operator= (const at_CH2 &right);

  /**
   * Converts the atom type to a string.
   * @return "CH2".
   */
  virtual operator const char* () const { return "CH2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CH2".
   */
  virtual const char* AmberRep () const { return "CH2"; }

  /**
   * Tells if the atom is a CH2.
   * @return true.
   */
  virtual bool is_CH2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CZ atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CZ : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CZ () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CZ (const at_CZ &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CZ () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CZ& operator= (const at_CZ &right);

  /**
   * Converts the atom type to a string.
   * @return "CZ".
   */
  virtual operator const char* () const { return "CZ"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CZ".
   */
  virtual const char* AmberRep () const { return "CZ"; }

  /**
   * Tells if the atom is a CZ.
   * @return true.
   */
  virtual bool is_CZ () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CZ2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CZ2 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CZ2 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CZ2 (const at_CZ2 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CZ2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CZ2& operator= (const at_CZ2 &right);

  /**
   * Converts the atom type to a string.
   * @return "CZ2".
   */
  virtual operator const char* () const { return "CZ2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CZ2".
   */
  virtual const char* AmberRep () const { return "CZ2"; }

  /**
   * Tells if the atom is a CZ2.
   * @return true.
   */
  virtual bool is_CZ2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The CZ3 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_CZ3 : public virtual at_AminoAcid,
	      public virtual at_Carbon,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_CZ3 () : at_AminoAcid (), at_Carbon (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_CZ3 (const at_CZ3 &right)
    : at_AminoAcid (right), at_Carbon (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_CZ3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_CZ3& operator= (const at_CZ3 &right);

  /**
   * Converts the atom type to a string.
   * @return "CZ3".
   */
  virtual operator const char* () const { return "CZ3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "CZ3".
   */
  virtual const char* AmberRep () const { return "CZ3"; }

  /**
   * Tells if the atom is a CZ3.
   * @return true.
   */
  virtual bool is_CZ3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.91.
   */
  virtual float GetVDWR () const { return 1.91; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The H atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_H : public virtual at_AminoAcid,
	     public virtual at_Hydrogen,
	     public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_H () : at_AminoAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_H (const at_H &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_H () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_H& operator= (const at_H &right);

  /**
   * Converts the atom type to a string.
   * @return "H".
   */
  virtual operator const char* () const { return "H"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "H".
   */
  virtual const char* AmberRep () const { return "H"; }

  /**
   * Tells if the atom is a H.
   * @return true.
   */
  virtual bool is_H () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1H atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1H : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1H () : at_AminoAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1H (const at_1H &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1H () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1H& operator= (const at_1H &right);

  /**
   * Converts the atom type to a string.
   * @return "1H".
   */
  virtual operator const char* () const { return "1H"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "1H".
   */
  virtual const char* AmberRep () const { return "1H"; }

  /**
   * Tells if the atom is a 1H.
   * @return true.
   */
  virtual bool is_1H () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2H atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2H : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2H () : at_AminoAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2H (const at_2H &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2H () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2H& operator= (const at_2H &right);

  /**
   * Converts the atom type to a string.
   * @return "2H".
   */
  virtual operator const char* () const { return "2H"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "2H".
   */
  virtual const char* AmberRep () const { return "2H"; }

  /**
   * Tells if the atom is a 2H.
   * @return true.
   */
  virtual bool is_2H () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3H atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_3H : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3H () : at_AminoAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3H (const at_3H &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3H () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3H& operator= (const at_3H &right);

  /**
   * Converts the atom type to a string.
   * @return "3H".
   */
  virtual operator const char* () const { return "3H"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "3H".
   */
  virtual const char* AmberRep () const { return "3H"; }

  /**
   * Tells if the atom is a 3H.
   * @return true.
   */
  virtual bool is_3H () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HA atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HA : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HA () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HA (const at_HA &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HA () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HA& operator= (const at_HA &right);

  /**
   * Converts the atom type to a string.
   * @return "HA".
   */
  virtual operator const char* () const { return "HA"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HA".
   */
  virtual const char* AmberRep () const { return "HA"; }

  /**
   * Tells if the atom is a HA.
   * @return true.
   */
  virtual bool is_HA () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HA1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HA1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HA1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HA1 (const at_HA1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HA1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HA1& operator= (const at_HA1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HA1".
   */
  virtual operator const char* () const { return "HA1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HA".
   */
  virtual const char* AmberRep () const { return "HA"; }

  /**
   * Tells if the atom is a HA1.
   * @return true.
   */
  virtual bool is_HA1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HA2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HA2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HA2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HA2 (const at_HA2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HA2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HA2& operator= (const at_HA2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HA2".
   */
  virtual operator const char* () const { return "HA2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HA2".
   */
  virtual const char* AmberRep () const { return "HA2"; }

  /**
   * Tells if the atom is a HA2.
   * @return true.
   */
  virtual bool is_HA2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HB atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HB : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HB () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HB (const at_HB &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HB () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HB& operator= (const at_HB &right);

  /**
   * Converts the atom type to a string.
   * @return "HB".
   */
  virtual operator const char* () const { return "HB"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HB".
   */
  virtual const char* AmberRep () const { return "HB"; }

  /**
   * Tells if the atom is a HB.
   * @return true.
   */
  virtual bool is_HB () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HB1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HB1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HB1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HB1 (const at_HB1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HB1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HB1& operator= (const at_HB1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HB1".
   */
  virtual operator const char* () const { return "HB1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HB1".
   */
  virtual const char* AmberRep () const { return "HB1"; }

  /**
   * Tells if the atom is a HB1.
   * @return true.
   */
  virtual bool is_HB1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HB2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HB2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HB2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HB2 (const at_HB2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HB2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HB2& operator= (const at_HB2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HB2".
   */
  virtual operator const char* () const { return "HB2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HB2".
   */
  virtual const char* AmberRep () const { return "HB2"; }

  /**
   * Tells if the atom is a HB2.
   * @return true.
   */
  virtual bool is_HB2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HB3 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HB3 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HB3 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HB3 (const at_HB3 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HB3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HB3& operator= (const at_HB3 &right);

  /**
   * Converts the atom type to a string.
   * @return "HB3".
   */
  virtual operator const char* () const { return "HB3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HB3".
   */
  virtual const char* AmberRep () const { return "HB3"; }

  /**
   * Tells if the atom is a HB3.
   * @return true.
   */
  virtual bool is_HB3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HD1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HD1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HD1 (const at_HD1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HD1& operator= (const at_HD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HD1".
   */
  virtual operator const char* () const { return "HD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD1".
   */
  virtual const char* AmberRep () const { return "HD1"; }

  /**
   * Tells if the atom is a HD1.
   * @return true.
   */
  virtual bool is_HD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HD2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HD2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HD2 (const at_HD2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HD2& operator= (const at_HD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HD2".
   */
  virtual operator const char* () const { return "HD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD2".
   */
  virtual const char* AmberRep () const { return "HD2"; }

  /**
   * Tells if the atom is a HD2.
   * @return true.
   */
  virtual bool is_HD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HE atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HE : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HE () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HE (const at_HE &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HE () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HE& operator= (const at_HE &right);

  /**
   * Converts the atom type to a string.
   * @return "HE".
   */
  virtual operator const char* () const { return "HE"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE".
   */
  virtual const char* AmberRep () const { return "HE"; }

  /**
   * Tells if the atom is a HE.
   * @return true.
   */
  virtual bool is_HE () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HE1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HE1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HE1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HE1 (const at_HE1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HE1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HE1& operator= (const at_HE1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HE1".
   */
  virtual operator const char* () const { return "HE1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE1".
   */
  virtual const char* AmberRep () const { return "HE1"; }

  /**
   * Tells if the atom is a HE1.
   * @return true.
   */
  virtual bool is_HE1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HE2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HE2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HE2 (const at_HE2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HE2& operator= (const at_HE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HE2".
   */
  virtual operator const char* () const { return "HE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE2".
   */
  virtual const char* AmberRep () const { return "HE2"; }

  /**
   * Tells if the atom is a HE2.
   * @return true.
   */
  virtual bool is_HE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HE3 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HE3 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HE3 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HE3 (const at_HE3 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HE3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HE3& operator= (const at_HE3 &right);

  /**
   * Converts the atom type to a string.
   * @return "HE3".
   */
  virtual operator const char* () const { return "HE3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE3".
   */
  virtual const char* AmberRep () const { return "HE3"; }

  /**
   * Tells if the atom is a HE3.
   * @return true.
   */
  virtual bool is_HE3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HG atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HG : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HG () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HG (const at_HG &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HG& operator= (const at_HG &right);

  /**
   * Converts the atom type to a string.
   * @return "HG".
   */
  virtual operator const char* () const { return "HG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG".
   */
  virtual const char* AmberRep () const { return "HG"; }

  /**
   * Tells if the atom is a HG.
   * @return true.
   */
  virtual bool is_HG () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HG1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HG1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HG1 (const at_HG1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HG1& operator= (const at_HG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HG1".
   */
  virtual operator const char* () const { return "HG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG1".
   */
  virtual const char* AmberRep () const { return "HG1"; }

  /**
   * Tells if the atom is a HG1.
   * @return true.
   */
  virtual bool is_HG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.0.
   */
  virtual float GetVDWR () const { return 0.0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HG2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HG2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HG2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HG2 (const at_HG2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HG2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HG2& operator= (const at_HG2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HG2".
   */
  virtual operator const char* () const { return "HG2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG2".
   */
  virtual const char* AmberRep () const { return "HG2"; }

  /**
   * Tells if the atom is a HG2.
   * @return true.
   */
  virtual bool is_HG2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.39.
   */
  virtual float GetVDWR () const { return 1.39; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HH atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HH : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HH () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HH (const at_HH &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HH () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HH& operator= (const at_HH &right);

  /**
   * Converts the atom type to a string.
   * @return "HH".
   */
  virtual operator const char* () const { return "HH"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH".
   */
  virtual const char* AmberRep () const { return "HH"; }

  /**
   * Tells if the atom is a HH.
   * @return true.
   */
  virtual bool is_HH () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.0.
   */
  virtual float GetVDWR () const { return 0.0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HH2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HH2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HH2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HH2 (const at_HH2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HH2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HH2& operator= (const at_HH2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HH2".
   */
  virtual operator const char* () const { return "HH2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH2".
   */
  virtual const char* AmberRep () const { return "HH2"; }

  /**
   * Tells if the atom is a HH2.
   * @return true.
   */
  virtual bool is_HH2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.46.
   */
  virtual float GetVDWR () const { return 1.46; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HXT atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HXT : public virtual at_AminoAcid,
	       public virtual at_Hydrogen,
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HXT () : at_AminoAcid (), at_Hydrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HXT (const at_HXT &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HXT () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HXT& operator= (const at_HXT &right);

  /**
   * Converts the atom type to a string.
   * @return "HXT".
   */
  virtual operator const char* () const { return "HXT"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HXT".
   */
  virtual const char* AmberRep () const { return "HXT"; }

  /**
   * Tells if the atom is a HXT.
   * @return true.
   */
  virtual bool is_HXT () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HZ atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HZ : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HZ () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HZ (const at_HZ &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HZ () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HZ& operator= (const at_HZ &right);

  /**
   * Converts the atom type to a string.
   * @return "HZ".
   */
  virtual operator const char* () const { return "HZ"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HZ".
   */
  virtual const char* AmberRep () const { return "HZ"; }

  /**
   * Tells if the atom is a HZ.
   * @return true.
   */
  virtual bool is_HZ () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.46.
   */
  virtual float GetVDWR () const { return 1.46; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HZ1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HZ1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HZ1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HZ1 (const at_HZ1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HZ1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HZ1& operator= (const at_HZ1 &right);

  /**
   * Converts the atom type to a string.
   * @return "HZ1".
   */
  virtual operator const char* () const { return "HZ1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HZ1".
   */
  virtual const char* AmberRep () const { return "HZ1"; }

  /**
   * Tells if the atom is a HZ1.
   * @return true.
   */
  virtual bool is_HZ1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HZ2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HZ2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HZ2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HZ2 (const at_HZ2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HZ2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HZ2& operator= (const at_HZ2 &right);

  /**
   * Converts the atom type to a string.
   * @return "HZ2".
   */
  virtual operator const char* () const { return "HZ2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HZ2".
   */
  virtual const char* AmberRep () const { return "HZ2"; }

  /**
   * Tells if the atom is a HZ2.
   * @return true.
   */
  virtual bool is_HZ2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The HZ3 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_HZ3 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_HZ3 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_HZ3 (const at_HZ3 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_HZ3 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_HZ3& operator= (const at_HZ3 &right);

  /**
   * Converts the atom type to a string.
   * @return "HZ3".
   */
  virtual operator const char* () const { return "HZ3"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HZ3".
   */
  virtual const char* AmberRep () const { return "HZ3"; }

  /**
   * Tells if the atom is a HZ3.
   * @return true.
   */
  virtual bool is_HZ3 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The N atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_N : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_N () : at_AminoAcid (), at_Nitrogen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_N (const at_N &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_N () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_N& operator= (const at_N &right);

  /**
   * Converts the atom type to a string.
   * @return "N".
   */
  virtual operator const char* () const { return "N"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "N".
   */
  virtual const char* AmberRep () const { return "N"; }

  /**
   * Tells if the atom is a N.
   * @return true.
   */
  virtual bool is_N () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The ND1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_ND1 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_ND1 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_ND1 (const at_ND1 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_ND1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_ND1& operator= (const at_ND1 &right);

  /**
   * Converts the atom type to a string.
   * @return "ND1".
   */
  virtual operator const char* () const { return "ND1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "ND1".
   */
  virtual const char* AmberRep () const { return "ND1"; }

  /**
   * Tells if the atom is a ND1.
   * @return true.
   */
  virtual bool is_ND1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The ND2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_ND2 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_ND2 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_ND2 (const at_ND2 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_ND2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_ND2& operator= (const at_ND2 &right);

  /**
   * Converts the atom type to a string.
   * @return "ND2".
   */
  virtual operator const char* () const { return "ND2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "ND2".
   */
  virtual const char* AmberRep () const { return "ND2"; }

  /**
   * Tells if the atom is a ND2.
   * @return true.
   */
  virtual bool is_ND2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NE atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NE : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NE () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NE (const at_NE &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NE () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NE& operator= (const at_NE &right);

  /**
   * Converts the atom type to a string.
   * @return "NE".
   */
  virtual operator const char* () const { return "NE"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NE".
   */
  virtual const char* AmberRep () const { return "NE"; }

  /**
   * Tells if the atom is a NE.
   * @return true.
   */
  virtual bool is_NE () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NE1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NE1 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NE1 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NE1 (const at_NE1 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NE1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NE1& operator= (const at_NE1 &right);

  /**
   * Converts the atom type to a string.
   * @return "NE1".
   */
  virtual operator const char* () const { return "NE1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NE1".
   */
  virtual const char* AmberRep () const { return "NE1"; }

  /**
   * Tells if the atom is a NE1.
   * @return true.
   */
  virtual bool is_NE1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NE2 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NE2 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NE2 (const at_NE2 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NE2& operator= (const at_NE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "NE2".
   */
  virtual operator const char* () const { return "NE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NE2".
   */
  virtual const char* AmberRep () const { return "NE2"; }

  /**
   * Tells if the atom is a NE2.
   * @return true.
   */
  virtual bool is_NE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NH1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NH1 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NH1 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NH1 (const at_NH1 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NH1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NH1& operator= (const at_NH1 &right);

  /**
   * Converts the atom type to a string.
   * @return "NH1".
   */
  virtual operator const char* () const { return "NH1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NH1".
   */
  virtual const char* AmberRep () const { return "NH1"; }

  /**
   * Tells if the atom is a NH1.
   * @return true.
   */
  virtual bool is_NH1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NH2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NH2 : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NH2 () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NH2 (const at_NH2 &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NH2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NH2& operator= (const at_NH2 &right);

  /**
   * Converts the atom type to a string.
   * @return "NH2".
   */
  virtual operator const char* () const { return "NH2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NH2".
   */
  virtual const char* AmberRep () const { return "NH2"; }

  /**
   * Tells if the atom is a NH2.
   * @return true.
   */
  virtual bool is_NH2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The NZ atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_NZ : public virtual at_AminoAcid,
	      public virtual at_Nitrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_NZ () : at_AminoAcid (), at_Nitrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_NZ (const at_NZ &right)
    : at_AminoAcid (right), at_Nitrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_NZ () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_NZ& operator= (const at_NZ &right);

  /**
   * Converts the atom type to a string.
   * @return "NZ".
   */
  virtual operator const char* () const { return "NZ"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "NZ".
   */
  virtual const char* AmberRep () const { return "NZ"; }

  /**
   * Tells if the atom is a NZ.
   * @return true.
   */
  virtual bool is_NZ () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.82.
   */
  virtual float GetVDWR () const { return 1.82; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The O atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_O : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_O () : at_AminoAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_O (const at_O &right)
    : at_AminoAcid (right), at_Oxygen (right), at_Backbone (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_O () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_O& operator= (const at_O &right);

  /**
   * Converts the atom type to a string.
   * @return "O".
   */
  virtual operator const char* () const { return "O"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "O".
   */
  virtual const char* AmberRep () const { return "O"; }

  /**
   * Tells if the atom is a O.
   * @return true.
   */
  virtual bool is_O () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OD1 : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OD1 () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OD1 (const at_OD1 &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OD1& operator= (const at_OD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "OD1".
   */
  virtual operator const char* () const { return "OD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OD1".
   */
  virtual const char* AmberRep () const { return "OD1"; }

  /**
   * Tells if the atom is a OD1.
   * @return true.
   */
  virtual bool is_OD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OD2 : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OD2 () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OD2 (const at_OD2 &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OD2& operator= (const at_OD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "OD2".
   */
  virtual operator const char* () const { return "OD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OD2".
   */
  virtual const char* AmberRep () const { return "OD2"; }

  /**
   * Tells if the atom is a OD2.
   * @return true.
   */
  virtual bool is_OD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OE1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OE1 : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OE1 () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OE1 (const at_OE1 &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OE1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OE1& operator= (const at_OE1 &right);

  /**
   * Converts the atom type to a string.
   * @return "OE1".
   */
  virtual operator const char* () const { return "OE1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OE1".
   */
  virtual const char* AmberRep () const { return "OE1"; }

  /**
   * Tells if the atom is a OE1.
   * @return true.
   */
  virtual bool is_OE1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OE2 : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OE2 () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OE2 (const at_OE2 &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OE2& operator= (const at_OE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "OE2".
   */
  virtual operator const char* () const { return "OE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OE2".
   */
  virtual const char* AmberRep () const { return "OE2"; }

  /**
   * Tells if the atom is a OE2.
   * @return true.
   */
  virtual bool is_OE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OG atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OG : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OG () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OG (const at_OG &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OG& operator= (const at_OG &right);

  /**
   * Converts the atom type to a string.
   * @return "OG".
   */
  virtual operator const char* () const { return "OG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OG".
   */
  virtual const char* AmberRep () const { return "OG"; }

  /**
   * Tells if the atom is a OG.
   * @return true.
   */
  virtual bool is_OG () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OG1 : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OG1 () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OG1 (const at_OG1 &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OG1& operator= (const at_OG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "OG1".
   */
  virtual operator const char* () const { return "OG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OG1".
   */
  virtual const char* AmberRep () const { return "OG1"; }

  /**
   * Tells if the atom is a OG1.
   * @return true.
   */
  virtual bool is_OG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OH atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_OH : public virtual at_AminoAcid,
	      public virtual at_Oxygen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OH () : at_AminoAcid (), at_Oxygen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OH (const at_OH &right)
    : at_AminoAcid (right), at_Oxygen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OH () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OH& operator= (const at_OH &right);

  /**
   * Converts the atom type to a string.
   * @return "OH".
   */
  virtual operator const char* () const { return "OH"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OH".
   */
  virtual const char* AmberRep () const { return "OH"; }

  /**
   * Tells if the atom is a OH.
   * @return true.
   */
  virtual bool is_OH () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.72.
   */
  virtual float GetVDWR () const { return 1.72; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The OXT atom type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class at_OXT : public virtual at_AminoAcid,
	       public virtual at_Oxygen, 
	       public virtual at_Backbone
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_OXT () : at_AminoAcid (), at_Oxygen (), at_Backbone () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_OXT (const at_OXT &right)
    : at_AminoAcid (right), at_Oxygen (right), at_Backbone (right) { }
  
  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_OXT () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_OXT& operator= (const at_OXT &right);

  /**
   * Converts the atom type to a string.
   * @return "OXT".
   */
  virtual operator const char* () const { return "OXT"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "OXT".
   */
  virtual const char* AmberRep () const { return "OXT"; }

  /**
   * Tells if the atom is a OXT.
   * @return true.
   */
  virtual bool is_OXT () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.66.
   */
  virtual float GetVDWR () const { return 1.66; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The SD atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_SD : public virtual at_AminoAcid,
	      public virtual at_Sulfur,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_SD () : at_AminoAcid (), at_Sulfur (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_SD (const at_SD &right)
    : at_AminoAcid (right), at_Sulfur (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_SD () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_SD& operator= (const at_SD &right);

  /**
   * Converts the atom type to a string.
   * @return "SD".
   */
  virtual operator const char* () const { return "SD"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "SD".
   */
  virtual const char* AmberRep () const { return "SD"; }

  /**
   * Tells if the atom is a SD.
   * @return true.
   */
  virtual bool is_SD () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 2.0.
   */
  virtual float GetVDWR () const { return 2.0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The SG atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_SG : public virtual at_AminoAcid,
	      public virtual at_Sulfur,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_SG () : at_AminoAcid (), at_Sulfur (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_SG (const at_SG &right)
    : at_AminoAcid (right), at_Sulfur (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_SG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_SG& operator= (const at_SG &right);

  /**
   * Converts the atom type to a string.
   * @return "SG".
   */
  virtual operator const char* () const { return "SG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "SG".
   */
  virtual const char* AmberRep () const { return "SG"; }

  /**
   * Tells if the atom is a SG.
   * @return true.
   */
  virtual bool is_SG () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 2.0.
   */
  virtual float GetVDWR () const { return 2.0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HD1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HD1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HD1 (const at_1HD1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HD1& operator= (const at_1HD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HD1".
   */
  virtual operator const char* () const { return "1HD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD11".
   */
  virtual const char* AmberRep () const { return "HD11"; }

  /**
   * Tells if the atom is a 1HD1.
   * @return true.
   */
  virtual bool is_1HD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HD2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HD2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HD2 (const at_1HD2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HD2& operator= (const at_1HD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HD2".
   */
  virtual operator const char* () const { return "1HD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD21".
   */
  virtual const char* AmberRep () const { return "HD21"; }

  /**
   * Tells if the atom is a 1HD2.
   * @return true.
   */
  virtual bool is_1HD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HE2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HE2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HE2 (const at_1HE2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HE2& operator= (const at_1HE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HE2".
   */
  virtual operator const char* () const { return "1HE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE21".
   */
  virtual const char* AmberRep () const { return "HE21"; }

  /**
   * Tells if the atom is a 1HE2.
   * @return true.
   */
  virtual bool is_1HE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HG1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HG1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HG1 (const at_1HG1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HG1& operator= (const at_1HG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HG1".
   */
  virtual operator const char* () const { return "1HG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG11".
   */
  virtual const char* AmberRep () const { return "HG11"; }

  /**
   * Tells if the atom is a 1HG1.
   * @return true.
   */
  virtual bool is_1HG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HG2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HG2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HG2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HG2 (const at_1HG2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HG2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HG2& operator= (const at_1HG2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HG2".
   */
  virtual operator const char* () const { return "1HG2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG21".
   */
  virtual const char* AmberRep () const { return "HG21"; }

  /**
   * Tells if the atom is a 1HG2.
   * @return true.
   */
  virtual bool is_1HG2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HH1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HH1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HH1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HH1 (const at_1HH1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HH1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HH1& operator= (const at_1HH1 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HH1".
   */
  virtual operator const char* () const { return "1HH1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH11".
   */
  virtual const char* AmberRep () const { return "HH11"; }

  /**
   * Tells if the atom is a 1HH1.
   * @return true.
   */
  virtual bool is_1HH1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 1HH2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_1HH2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_1HH2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_1HH2 (const at_1HH2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_1HH2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_1HH2& operator= (const at_1HH2 &right);

  /**
   * Converts the atom type to a string.
   * @return "1HH2".
   */
  virtual operator const char* () const { return "1HH2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH21".
   */
  virtual const char* AmberRep () const { return "HH21"; }

  /**
   * Tells if the atom is a 1HH2.
   * @return true.
   */
  virtual bool is_1HH2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HD1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HD1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HD1 (const at_2HD1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HD1& operator= (const at_2HD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HD1".
   */
  virtual operator const char* () const { return "2HD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD12".
   */
  virtual const char* AmberRep () const { return "HD12"; }

  /**
   * Tells if the atom is a 2HD1.
   * @return true.
   */
  virtual bool is_2HD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HD2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HD2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HD2 (const at_2HD2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HD2& operator= (const at_2HD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HD2".
   */
  virtual operator const char* () const { return "2HD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD22".
   */
  virtual const char* AmberRep () const { return "HD22"; }

  /**
   * Tells if the atom is a 2HD2.
   * @return true.
   */
  virtual bool is_2HD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HE2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HE2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HE2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HE2 (const at_2HE2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HE2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HE2& operator= (const at_2HE2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HE2".
   */
  virtual operator const char* () const { return "2HE2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HE22".
   */
  virtual const char* AmberRep () const { return "HE22"; }

  /**
   * Tells if the atom is a 2HE2.
   * @return true.
   */
  virtual bool is_2HE2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HG1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HG1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HG1 (const at_2HG1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HG1& operator= (const at_2HG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HG1".
   */
  virtual operator const char* () const { return "2HG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG12".
   */
  virtual const char* AmberRep () const { return "HG12"; }

  /**
   * Tells if the atom is a 2HG1.
   * @return true.
   */
  virtual bool is_2HG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HG2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HG2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HG2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HG2 (const at_2HG2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HG2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HG2& operator= (const at_2HG2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HG2".
   */
  virtual operator const char* () const { return "2HG2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG22".
   */
  virtual const char* AmberRep () const { return "HG22"; }

  /**
   * Tells if the atom is a 2HG2.
   * @return true.
   */
  virtual bool is_2HG2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HH1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HH1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HH1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HH1 (const at_2HH1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HH1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HH1& operator= (const at_2HH1 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HH1".
   */
  virtual operator const char* () const { return "2HH1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH12".
   */
  virtual const char* AmberRep () const { return "HH12"; }

  /**
   * Tells if the atom is a 2HH1.
   * @return true.
   */
  virtual bool is_2HH1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 2HH2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_2HH2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_2HH2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_2HH2 (const at_2HH2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_2HH2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_2HH2& operator= (const at_2HH2 &right);

  /**
   * Converts the atom type to a string.
   * @return "2HH2".
   */
  virtual operator const char* () const { return "2HH2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HH22".
   */
  virtual const char* AmberRep () const { return "HH22"; }

  /**
   * Tells if the atom is a 2HH2.
   * @return true.
   */
  virtual bool is_2HH2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3HD1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_3HD1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3HD1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3HD1 (const at_3HD1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3HD1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3HD1& operator= (const at_3HD1 &right);

  /**
   * Converts the atom type to a string.
   * @return "3HD1".
   */
  virtual operator const char* () const { return "3HD1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD13".
   */
  virtual const char* AmberRep () const { return "HD13"; }

  /**
   * Tells if the atom is a 3HD1.
   * @return true.
   */
  virtual bool is_3HD1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 0.6.
   */
  virtual float GetVDWR () const { return 0.6; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3HD2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_3HD2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3HD2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3HD2 (const at_3HD2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3HD2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3HD2& operator= (const at_3HD2 &right);

  /**
   * Converts the atom type to a string.
   * @return "3HD2".
   */
  virtual operator const char* () const { return "3HD2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HD23".
   */
  virtual const char* AmberRep () const { return "HD23"; }

  /**
   * Tells if the atom is a 3HD2.
   * @return true.
   */
  virtual bool is_3HD2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3HG1 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_3HG1 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3HG1 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3HG1 (const at_3HG1 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3HG1 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3HG1& operator= (const at_3HG1 &right);

  /**
   * Converts the atom type to a string.
   * @return "3HG1".
   */
  virtual operator const char* () const { return "3HG1"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG13".
   */
  virtual const char* AmberRep () const { return "HG13"; }

  /**
   * Tells if the atom is a 3HG1.
   * @return true.
   */
  virtual bool is_3HG1 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The 3HG2 atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_3HG2 : public virtual at_AminoAcid,
	      public virtual at_Hydrogen,
	      public virtual at_SideChain
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_3HG2 () : at_AminoAcid (), at_Hydrogen (), at_SideChain () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_3HG2 (const at_3HG2 &right)
    : at_AminoAcid (right), at_Hydrogen (right), at_SideChain (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_3HG2 () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_3HG2& operator= (const at_3HG2 &right);

  /**
   * Converts the atom type to a string.
   * @return "3HG2".
   */
  virtual operator const char* () const { return "3HG2"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "HG23".
   */
  virtual const char* AmberRep () const { return "HG23"; }

  /**
   * Tells if the atom is a 3HG2.
   * @return true.
   */
  virtual bool is_3HG2 () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const;

  /**
   * Gets the Van Der Waals radius value.
   * @return 1.49.
   */
  virtual float GetVDWR () const { return 1.49; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The MG atom type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class at_MG : public virtual at_Magnesium
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  at_MG () : at_Magnesium () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the object to copy.
   */
  at_MG (const at_MG &right)
    : at_Magnesium (right) { }

  /**
   * Destructs the object.  Nothing to do.
   */
  ~at_MG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const at_MG& operator= (const at_MG &right);

  /**
   * Converts the atom type to a string.
   * @return "MG".
   */
  virtual operator const char* () const { return "MG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Converts the atom type to an Amber string representation.
   * @return "MG".
   */
  virtual const char* AmberRep () const { return "MG"; }

  /**
   * Tells if the atom is a MG.
   * @return true.
   */
  virtual bool is_MG () const { return true; }

  /**
   * Tells if the atom is connected to type in res.
   * @param type the second atom in the connection.
   * @param res the residue.
   * @return true if the 2 atoms are connected.
   */
  virtual bool is_connected (const t_Atom *type, const t_Residue *res) const
  { return false; }
  
  /**
   * Gets the Van Der Waals radius value.
   * @return 0.
   */
  virtual float GetVDWR () const { return 0; }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};

#endif
