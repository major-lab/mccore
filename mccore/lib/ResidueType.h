//                              -*- Mode: C++ -*- 
// ResidueType.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Wed Mar  7 13:47:47 2001
// Update Count     : 3
// Status           : Ok.
// 


#ifndef _ResidueType_h_
#define _ResidueType_h_


class iBinstream;
class oBinstream;
class ostream;



/**
 * @short Basic residue type.
 *
 * The basic residue type defines a set of methods witch describes the
 * residue.  The base class always return false or 0 for these methods; the
 * derived classes defines the needed property method to return true.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class t_Residue
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  t_Residue () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  t_Residue (const t_Residue &right) { }

  /**
   * Destructs the object.
   */
  virtual ~t_Residue () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const t_Residue& operator= (const t_Residue &right) { return *this; }

  /**
   * Converts the residue type to a string.
   * @return "RES"
   */
  virtual operator const char* () const { return "RES"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is unknown.
   * @return false.
   */
  virtual bool is_Misc () const { return false; }

  /**
   * Tells if the residue is a nucleic acid.
   * @return false.
   */
  virtual bool is_NucleicAcid () const { return false; }

  /**
   * Tells if the residue is an amino acid.
   * @return false.
   */
  virtual bool is_AminoAcid () const { return false; }

  /**
   * Tells if the residue is a phosphate.
   * @return false.
   */
  virtual bool is_Phosphate () const { return false; }

  /**
   * Tells if the residue is a purine.
   * @return false.
   */
  virtual bool is_Purine () const { return false; }

  /**
   * Tells if the residue is a pyrimidine.
   * @return false.
   */
  virtual bool is_Pyrimidine () const { return false; }

  /**
   * Tells if the residue is a DNA.
   * @return false.
   */
  virtual bool is_DNA () const { return false; }

  /**
   * Tells if the residue is a RNA.
   * @return false.
   */
  virtual bool is_RNA () const { return false; }

  /**
   * Tells if the residue is an adenine.
   * @return false.
   */
  virtual bool is_A () const { return false; }

  /**
   * Tells if the residue is a cytosine.
   * @return false.
   */
  virtual bool is_C () const { return false; }

  /**
   * Tells if the residue is a guanine.
   * @return false.
   */
  virtual bool is_G () const { return false; }

  /**
   * Tells if the residue is a uracil.
   * @return false.
   */
  virtual bool is_U () const { return false; }

  /**
   * Tells if the residue is a thymine.
   * @return false.
   */
  virtual bool is_T () const { return false; }

  /**
   * Tells if the residue is a RNA adenine.
   * @return false
   */
  virtual bool is_rA () const { return false; }

  /**
   * Tells if the residue is a RNA cytosine.
   * @return false.
   */
  virtual bool is_rC () const { return false; }

  /**
   * Tells if the residue is a RNA guanine.
   * @return false
   */
  virtual bool is_rG () const { return false; }

  /**
   * Tells if the residue is a RNA uracil.
   * @return false.
   */
  virtual bool is_rU () const { return false; }

  /**
   * Tells if the residue is a DNA adenine.
   * @return false.
   */
  virtual bool is_dA () const { return false; }

  /**
   * Tells if the residue is a DNA cytosine.
   * @return false.
   */
  virtual bool is_dC () const { return false; }

  /**
   * Tells if the residue is a DNA guanine.
   * @return false.
   */
  virtual bool is_dG () const { return false; }

  /**
   * Tells if the residue is a DNA thymine.
   * @return false.
   */
  virtual bool is_dT () const { return false; }

  /**
   * Tells if the residue is an alanine.
   * @return false.
   */
  virtual bool is_ALA () const { return false; }

  /**
   * Tells if the residue is an arginine.
   * @return false.
   */
  virtual bool is_ARG () const { return false; }

  /**
   * Tells if the residue is an asparagine.
   * @return false.
   */
  virtual bool is_ASN () const { return false; }

  /**
   * Tells if the residue is an aspartic acid.
   * @return false.
   */
  virtual bool is_ASP () const { return false; }

  /**
   * Tells if the residue is a cysteine.
   * @return false.
   */
  virtual bool is_CYS () const { return false; }

  /**
   * Tells if the residue is a glutamine.
   * @return false.
   */
  virtual bool is_GLN () const { return false; }

  /**
   * Tells if the residue is a glutamic acid.
   * @return false.
   */
  virtual bool is_GLU () const { return false; }

  /**
   * Tells if the residue is a glycine.
   * @return false.
   */
  virtual bool is_GLY () const { return false; }

  /**
   * Tells if the residue is a histidine.
   * @return false.
   */
  virtual bool is_HIS () const { return false; }

  /**
   * Tells if the residue is an isoleucine.
   * @return false.
   */
  virtual bool is_ILE () const { return false; }

  /**
   * Tells if the residue is a leucine.
   * @return false.
   */
  virtual bool is_LEU () const { return false; }

  /**
   * Tells if the residue is a lysine.
   * @return false.
   */
  virtual bool is_LYS () const { return false; }

  /**
   * Tells if the residue is a methionine.
   * @return false.
   */
  virtual bool is_MET () const { return false; }

  /**
   * Tells if the residue is a phenylalanine.
   * @return false.
   */
  virtual bool is_PHE () const { return false; }

  /**
   * Tells if the residue is a proline.
   * @return false.
   */
  virtual bool is_PRO () const { return false; }

  /**
   * Tells if the residue is a serine.
   * @return false.
   */
  virtual bool is_SER () const { return false; }

  /**
   * Tells if the residue is a threonine.
   * @return false.
   */
  virtual bool is_THR () const { return false; }

  /**
   * Tells if the residue is a tryptophan.
   * @return false.
   */
  virtual bool is_TRP () const { return false; }

  /**
   * Tells if the residue is a tyrosine.
   * @return false.
   */
  virtual bool is_TYR () const { return false; }

  /**
   * Tells if the residue is a valine.
   * @return false.
   */
  virtual bool is_VAL () const { return false; }

  /**
   * Tests whether the current object is the same class or a derived class
   * of t.
   * @param t the other residue type.
   * @return the truth value.
   */
  virtual bool is (const t_Residue *t) const { return t->describe (this); }

  /**
   * Tests whether the type t is a t_Residue or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const t_Residue* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.  Each type must define a
   * unique integer value.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * Inputs the residue type.  The integer type is read and the type object is
 * assigned to the pointer.
 * @param ibs the input binary stream.
 * @param t the residue type pointer to fill.
 * @return the input binary stream used.
 */
iBinstream& operator>> (iBinstream &ibs, t_Residue *&t);



/**
 * Outputs the residue type through a binary stream.  The type is dumped as
 * an integer.
 * @param obs the binary output stream.
 * @param t the type to dump.
 * @return the output binary stream used.
 */
oBinstream& operator<< (oBinstream &obs, const t_Residue *t);

#endif
