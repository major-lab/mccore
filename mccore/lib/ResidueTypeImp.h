//                              -*- Mode: C++ -*- 
// ResidueTypeImp.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Tue Mar  6 12:24:34 2001
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:04:16 2001
// Update Count     : 2
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


#ifndef _ResidueTypeImp_h_
#define _ResidueTypeImp_h_


#include "ResidueType.h"


class iBinstream;
class oBinstream;
class ostream;



/**
 * @short The residue type for general or unknown residues.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_Misc : public virtual t_Residue
{
  /**
   * The name of the residue.
   */
  char mName[4];
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_Misc () : t_Residue () { }

  /**
   * Initializes the objet with it's name and add it to the
   * @ref gMiscResidueString table.
   * @param name the name of the residue.
   */
  rt_Misc (const char *name);
  
  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_Misc (const rt_Misc &right);

  /**
   * Destructs the object.
   */
  virtual ~rt_Misc () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_Misc& operator= (const rt_Misc &right);

  /**
   * Converts the residue type to a string.
   * @return the contents of mName.
   */
  virtual operator const char* () const { return mName; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a misc type.
   * @return true.
   */
  virtual bool is_Misc () const { return true; }

  /**
   * Tests whether the type t is a rt_Misc or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_Misc* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general nucleic acid type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_NucleicAcid : public virtual t_Residue
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_NucleicAcid () : t_Residue () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_NucleicAcid (const rt_NucleicAcid &right) : t_Residue (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_NucleicAcid () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_NucleicAcid& operator= (const rt_NucleicAcid &right);

  /**
   * Converts the residue type to a string.
   * @return "Nucleic acid"
   */
  virtual operator const char* () const { return "Nucleic acid"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a NucleicAcid type.
   * @return true.
   */
  virtual bool is_NucleicAcid () const { return true; }

  /**
   * Tests whether the type t is a rt_NucleicAcid or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_NucleicAcid* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The general amino acid type.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_AminoAcid : public virtual t_Residue
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_AminoAcid () : t_Residue () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_AminoAcid (const rt_AminoAcid &right) : t_Residue (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_AminoAcid () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_AminoAcid& operator= (const rt_AminoAcid &right);

  /**
   * Converts the residue type to a string.
   * @return "Amino acid"
   */
  virtual operator const char* () const { return "Amino acid"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a AminoAcid type.
   * @return true.
   */
  virtual bool is_AminoAcid () const { return true; }

  /**
   * Tests whether the type t is a rt_AminoAcid or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_AminoAcid* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The phosphate residue type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_Phosphate : public virtual rt_NucleicAcid
{

public:
  
  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_Phosphate () : rt_NucleicAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_Phosphate (const rt_Phosphate &right) : rt_NucleicAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_Phosphate () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_Phosphate& operator= (const rt_Phosphate &right);

  /**
   * Converts the residue type to a string.
   * @return "Phosphate"
   */
  virtual operator const char* () const { return "Phosphate"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a Phosphate type.
   * @return true.
   */
  virtual bool is_Phosphate () const { return true; }

  /**
   * Tests whether the type t is a rt_Phosphate or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_Phosphate* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Classes of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_Purine : public virtual rt_NucleicAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_Purine () : rt_NucleicAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_Purine (const rt_Purine &right) : rt_NucleicAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_Purine () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_Purine& operator= (const rt_Purine &right);

  /**
   * Converts the residue type to a string.
   * @return "Purine"
   */
  virtual operator const char* () const { return "Purine"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a Purine type.
   * @return true.
   */
  virtual bool is_Purine () const { return true; }

  /**
   * Tests whether the type t is a rt_Purine or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_Purine* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The Pyrimidine residue type.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_Pyrimidine : public virtual rt_NucleicAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_Pyrimidine () : rt_NucleicAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_Pyrimidine (const rt_Pyrimidine &right) : rt_NucleicAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_Pyrimidine () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_Pyrimidine& operator= (const rt_Pyrimidine &right);

  /**
   * Converts the residue type to a string.
   * @return "Pyrimidine"
   */
  virtual operator const char* () const { return "Pyrimidine"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a Pyrimidine type.
   * @return true.
   */
  virtual bool is_Pyrimidine () const { return true; }

  /**
   * Tests whether the type t is a rt_Pyrimidine or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_Pyrimidine* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The DNA ribose class.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_DNA : public virtual rt_NucleicAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_DNA () : rt_NucleicAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_DNA (const rt_DNA &right) : rt_NucleicAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_DNA () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_DNA& operator= (const rt_DNA &right);

  /**
   * Converts the residue type to a string.
   * @return "DNA"
   */
  virtual operator const char* () const { return "DNA"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a DNA type.
   * @return true.
   */
  virtual bool is_DNA () const { return true; }

  /**
   * Tests whether the type t is a rt_DNA or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_DNA* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short The RNA ribose class.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_RNA : public virtual rt_NucleicAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_RNA () : rt_NucleicAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_RNA (const rt_RNA &right) : rt_NucleicAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_RNA () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_RNA& operator= (const rt_RNA &right);

  /**
   * Converts the residue type to a string.
   * @return "RNA"
   */
  virtual operator const char* () const { return "RNA"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a RNA type.
   * @return true.
   */
  virtual bool is_RNA () const { return true; }

  /**
   * Tests whether the type t is a rt_RNA or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_RNA* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_A : public virtual rt_Purine
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_A () : rt_Purine () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_A (const rt_A &right) : rt_Purine (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_A () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_A& operator= (const rt_A &right);

  /**
   * Converts the residue type to a string.
   * @return "A"
   */
  virtual operator const char* () const { return "A"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a A type.
   * @return true.
   */
  virtual bool is_A () const { return true; }

  /**
   * Tests whether the type t is a rt_A or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_A* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_C : public virtual rt_Pyrimidine
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_C () : rt_Pyrimidine () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_C (const rt_C &right) : rt_Pyrimidine (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_C () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_C& operator= (const rt_C &right);

  /**
   * Converts the residue type to a string.
   * @return "C"
   */
  virtual operator const char* () const { return "C"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a C type.
   * @return true.
   */
  virtual bool is_C () const { return true; }

  /**
   * Tests whether the type t is a rt_C or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_C* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_G : public virtual rt_Purine
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_G () : rt_Purine () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_G (const rt_G &right) : rt_Purine (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_G () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_G& operator= (const rt_G &right);

  /**
   * Converts the residue type to a string.
   * @return "G"
   */
  virtual operator const char* () const { return "G"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a G type.
   * @return true.
   */
  virtual bool is_G () const { return true; }

  /**
   * Tests whether the type t is a rt_G or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_G* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_U : public virtual rt_Pyrimidine
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_U () : rt_Pyrimidine () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_U (const rt_U &right) : rt_Pyrimidine (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_U () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_U& operator= (const rt_U &right);

  /**
   * Converts the residue type to a string.
   * @return "U"
   */
  virtual operator const char* () const { return "U"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a U type.
   * @return true.
   */
  virtual bool is_U () const { return true; }

  /**
   * Tests whether the type t is a rt_U or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_U* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_T : public virtual rt_Pyrimidine
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_T () : rt_Pyrimidine () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_T (const rt_T &right) : rt_Pyrimidine (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_T () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_T& operator= (const rt_T &right);

  /**
   * Converts the residue type to a string.
   * @return "T"
   */
  virtual operator const char* () const { return "T"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a T type.
   * @return true.
   */
  virtual bool is_T () const { return true; }

  /**
   * Tests whether the type t is a rt_T or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_T* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of RNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_rA : public virtual rt_A, public virtual rt_RNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_rA () : rt_A (), rt_RNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_rA (const rt_rA &right) : rt_A (right), rt_RNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_rA () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_rA& operator= (const rt_rA &right);

  /**
   * Converts the residue type to a string.
   * @return "rA"
   */
  virtual operator const char* () const { return "rA"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a rA type.
   * @return true.
   */
  virtual bool is_rA () const { return true; }

  /**
   * Tests whether the type t is a rt_rA or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_rA* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of RNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_rC : public virtual rt_C, public virtual rt_RNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_rC () : rt_C (), rt_RNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_rC (const rt_rC &right) : rt_C (right), rt_RNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_rC () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_rC& operator= (const rt_rC &right);

  /**
   * Converts the residue type to a string.
   * @return "rC"
   */
  virtual operator const char* () const { return "rC"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a rC type.
   * @return true.
   */
  virtual bool is_rC () const { return true; }

  /**
   * Tests whether the type t is a rt_rC or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_rC* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of RNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_rG : public virtual rt_G, public virtual rt_RNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_rG () : rt_G (), rt_RNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_rG (const rt_rG &right) : rt_G (right), rt_RNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_rG () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_rG& operator= (const rt_rG &right);

  /**
   * Converts the residue type to a string.
   * @return "rG"
   */
  virtual operator const char* () const { return "rG"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a rG type.
   * @return true.
   */
  virtual bool is_rG () const { return true; }

  /**
   * Tests whether the type t is a rt_rG or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_rG* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of RNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_rU : public virtual rt_U, public virtual rt_RNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_rU () : rt_U (), rt_RNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_rU (const rt_rU &right) : rt_U (right), rt_RNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_rU () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_rU& operator= (const rt_rU &right);

  /**
   * Converts the residue type to a string.
   * @return "rU"
   */
  virtual operator const char* () const { return "rU"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a rU type.
   * @return true.
   */
  virtual bool is_rU () const { return true; }

  /**
   * Tests whether the type t is a rt_rU or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_rU* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of DNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_dA : public virtual rt_A, public virtual rt_DNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_dA () : rt_A (), rt_DNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_dA (const rt_dA &right) : rt_A (right), rt_DNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_dA () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_dA& operator= (const rt_dA &right);

  /**
   * Converts the residue type to a string.
   * @return "dA"
   */
  virtual operator const char* () const { return "dA"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a dA type.
   * @return true.
   */
  virtual bool is_dA () const { return true; }

  /**
   * Tests whether the type t is a rt_dA or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_dA* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of DNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_dC : public virtual rt_C, public virtual rt_DNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_dC () : rt_C (), rt_DNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_dC (const rt_dC &right) : rt_C (right), rt_DNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_dC () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_dC& operator= (const rt_dC &right);

  /**
   * Converts the residue type to a string.
   * @return "dC"
   */
  virtual operator const char* () const { return "dC"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a dC type.
   * @return true.
   */
  virtual bool is_dC () const { return true; }

  /**
   * Tests whether the type t is a rt_dC or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_dC* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of DNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_dG : public virtual rt_G, public virtual rt_DNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_dG () : rt_G (), rt_DNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_dG (const rt_dG &right) : rt_G (right), rt_DNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_dG () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_dG& operator= (const rt_dG &right);

  /**
   * Converts the residue type to a string.
   * @return "dG"
   */
  virtual operator const char* () const { return "dG"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a dG type.
   * @return true.
   */
  virtual bool is_dG () const { return true; }

  /**
   * Tests whether the type t is a rt_dG or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_dG* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of DNA nitrogen bases.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class rt_dT : public virtual rt_T, public virtual rt_DNA
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_dT () : rt_T (), rt_DNA () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_dT (const rt_dT &right) : rt_T (right), rt_DNA (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_dT () { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_dT& operator= (const rt_dT &right);

  /**
   * Converts the residue type to a string.
   * @return "dT"
   */
  virtual operator const char* () const { return "dT"; }
  
  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a dT type.
   * @return true.
   */
  virtual bool is_dT () const { return true; }

  /**
   * Tests whether the type t is a rt_dT or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_dT* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of alanine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_ALA : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_ALA () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_ALA (const rt_ALA &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_ALA () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_ALA& operator= (const rt_ALA &right);

  /**
   * Converts the residue type to a string.
   * @return "ALA"
   */
  virtual operator const char* () const { return "ALA"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a alanine type.
   * @return true.
   */
  virtual bool is_ALA () const { return true; }

  /**
   * Tests whether the type t is a rt_ALA or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_ALA* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of arginine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_ARG : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_ARG () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_ARG (const rt_ARG &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_ARG () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_ARG& operator= (const rt_ARG &right);

  /**
   * Converts the residue type to a string.
   * @return "ARG"
   */
  virtual operator const char* () const { return "ARG"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a arginine type.
   * @return true.
   */
  virtual bool is_ARG () const { return true; }

  /**
   * Tests whether the type t is a rt_ARG or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_ARG* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of asparagine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_ASN : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_ASN () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_ASN (const rt_ASN &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_ASN () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_ASN& operator= (const rt_ASN &right);

  /**
   * Converts the residue type to a string.
   * @return "ASN"
   */
  virtual operator const char* () const { return "ASN"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a asparagine type.
   * @return true.
   */
  virtual bool is_ASN () const { return true; }

  /**
   * Tests whether the type t is a rt_ASN or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_ASN* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of asparticacid.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_ASP : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_ASP () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_ASP (const rt_ASP &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_ASP () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_ASP& operator= (const rt_ASP &right);

  /**
   * Converts the residue type to a string.
   * @return "ASP"
   */
  virtual operator const char* () const { return "ASP"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a asparticacid type.
   * @return true.
   */
  virtual bool is_ASP () const { return true; }

  /**
   * Tests whether the type t is a rt_ASP or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_ASP* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of cysteine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_CYS : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_CYS () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_CYS (const rt_CYS &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_CYS () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_CYS& operator= (const rt_CYS &right);

  /**
   * Converts the residue type to a string.
   * @return "CYS"
   */
  virtual operator const char* () const { return "CYS"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a cysteine type.
   * @return true.
   */
  virtual bool is_CYS () const { return true; }

  /**
   * Tests whether the type t is a rt_CYS or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_CYS* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of glutamine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_GLN : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_GLN () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_GLN (const rt_GLN &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_GLN () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_GLN& operator= (const rt_GLN &right);

  /**
   * Converts the residue type to a string.
   * @return "GLN"
   */
  virtual operator const char* () const { return "GLN"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a glutamine type.
   * @return true.
   */
  virtual bool is_GLN () const { return true; }

  /**
   * Tests whether the type t is a rt_GLN or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_GLN* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of glutamicacid.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_GLU : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_GLU () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_GLU (const rt_GLU &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_GLU () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_GLU& operator= (const rt_GLU &right);

  /**
   * Converts the residue type to a string.
   * @return "GLU"
   */
  virtual operator const char* () const { return "GLU"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a glutamicacid type.
   * @return true.
   */
  virtual bool is_GLU () const { return true; }

  /**
   * Tests whether the type t is a rt_GLU or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_GLU* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of glycine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_GLY : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_GLY () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_GLY (const rt_GLY &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_GLY () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_GLY& operator= (const rt_GLY &right);

  /**
   * Converts the residue type to a string.
   * @return "GLY"
   */
  virtual operator const char* () const { return "GLY"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a glycine type.
   * @return true.
   */
  virtual bool is_GLY () const { return true; }

  /**
   * Tests whether the type t is a rt_GLY or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_GLY* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of histidine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_HIS : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_HIS () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_HIS (const rt_HIS &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_HIS () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_HIS& operator= (const rt_HIS &right);

  /**
   * Converts the residue type to a string.
   * @return "HIS"
   */
  virtual operator const char* () const { return "HIS"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a histidine type.
   * @return true.
   */
  virtual bool is_HIS () const { return true; }

  /**
   * Tests whether the type t is a rt_HIS or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_HIS* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of isoleucine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_ILE : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_ILE () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_ILE (const rt_ILE &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_ILE () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_ILE& operator= (const rt_ILE &right);

  /**
   * Converts the residue type to a string.
   * @return "ILE"
   */
  virtual operator const char* () const { return "ILE"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a isoleucine type.
   * @return true.
   */
  virtual bool is_ILE () const { return true; }

  /**
   * Tests whether the type t is a rt_ILE or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_ILE* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of leucine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_LEU : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_LEU () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_LEU (const rt_LEU &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_LEU () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_LEU& operator= (const rt_LEU &right);

  /**
   * Converts the residue type to a string.
   * @return "LEU"
   */
  virtual operator const char* () const { return "LEU"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a leucine type.
   * @return true.
   */
  virtual bool is_LEU () const { return true; }

  /**
   * Tests whether the type t is a rt_LEU or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_LEU* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of lysine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_LYS : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_LYS () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_LYS (const rt_LYS &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_LYS () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_LYS& operator= (const rt_LYS &right);

  /**
   * Converts the residue type to a string.
   * @return "LYS"
   */
  virtual operator const char* () const { return "LYS"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a lysine type.
   * @return true.
   */
  virtual bool is_LYS () const { return true; }

  /**
   * Tests whether the type t is a rt_LYS or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_LYS* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of methionine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_MET : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_MET () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_MET (const rt_MET &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_MET () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_MET& operator= (const rt_MET &right);

  /**
   * Converts the residue type to a string.
   * @return "MET"
   */
  virtual operator const char* () const { return "MET"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a methionine type.
   * @return true.
   */
  virtual bool is_MET () const { return true; }

  /**
   * Tests whether the type t is a rt_MET or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_MET* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of phenylalanine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_PHE : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_PHE () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_PHE (const rt_PHE &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_PHE () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_PHE& operator= (const rt_PHE &right);

  /**
   * Converts the residue type to a string.
   * @return "PHE"
   */
  virtual operator const char* () const { return "PHE"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a phenylalanine type.
   * @return true.
   */
  virtual bool is_PHE () const { return true; }

  /**
   * Tests whether the type t is a rt_PHE or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_PHE* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of proline.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_PRO : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_PRO () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_PRO (const rt_PRO &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_PRO () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_PRO& operator= (const rt_PRO &right);

  /**
   * Converts the residue type to a string.
   * @return "PRO"
   */
  virtual operator const char* () const { return "PRO"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a proline type.
   * @return true.
   */
  virtual bool is_PRO () const { return true; }

  /**
   * Tests whether the type t is a rt_PRO or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_PRO* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of serine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_SER : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_SER () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_SER (const rt_SER &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_SER () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_SER& operator= (const rt_SER &right);

  /**
   * Converts the residue type to a string.
   * @return "SER"
   */
  virtual operator const char* () const { return "SER"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a serine type.
   * @return true.
   */
  virtual bool is_SER () const { return true; }

  /**
   * Tests whether the type t is a rt_SER or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_SER* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of threonine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_THR : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_THR () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_THR (const rt_THR &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_THR () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_THR& operator= (const rt_THR &right);

  /**
   * Converts the residue type to a string.
   * @return "THR"
   */
  virtual operator const char* () const { return "THR"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a threonine type.
   * @return true.
   */
  virtual bool is_THR () const { return true; }

  /**
   * Tests whether the type t is a rt_THR or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_THR* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of tryptophan.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_TRP : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_TRP () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_TRP (const rt_TRP &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_TRP () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_TRP& operator= (const rt_TRP &right);

  /**
   * Converts the residue type to a string.
   * @return "TRP"
   */
  virtual operator const char* () const { return "TRP"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a tryptophan type.
   * @return true.
   */
  virtual bool is_TRP () const { return true; }

  /**
   * Tests whether the type t is a rt_TRP or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_TRP* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of tyrosine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_TYR : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_TYR () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_TYR (const rt_TYR &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_TYR () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_TYR& operator= (const rt_TYR &right);

  /**
   * Converts the residue type to a string.
   * @return "TYR"
   */
  virtual operator const char* () const { return "TYR"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a tyrosine type.
   * @return true.
   */
  virtual bool is_TYR () const { return true; }

  /**
   * Tests whether the type t is a rt_TYR or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_TYR* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * @short Type of valine.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class rt_VAL : public rt_AminoAcid
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the objet.
   */
  rt_VAL () : rt_AminoAcid () { }

  /**
   * Initializes the objet with the right's content.
   * @param right the objet to copy.
   */
  rt_VAL (const rt_VAL &right) : rt_AminoAcid (right) { }

  /**
   * Destructs the object.
   */
  virtual ~rt_VAL () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the right's content to the object.
   * @param right the object to copy.
   * @return itself.
   */
  virtual const rt_VAL& operator= (const rt_VAL &right);

  /**
   * Converts the residue type to a string.
   * @return "VAL"
   */
  virtual operator const char* () const { return "VAL"; }

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Tells if the residue is a valine type.
   * @return true.
   */
  virtual bool is_VAL () const { return true; }

  /**
   * Tests whether the type t is a rt_VAL or derived class.
   * @param the type to test.
   * @return the truth value of the test.
   */
  virtual bool describe (const t_Residue *t) const
  { return dynamic_cast< const rt_VAL* >(t); }

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the type value in the binary stream.
   * @param obs the binary output stream.
   */
  virtual void Binoutput (oBinstream &obs) const;
};



/**
 * Displays the residue type to the output stream.
 * @param os the output stream.
 * @param restype the residue type.
 * @return the output stream used.
 */
ostream& operator<< (ostream &os, const t_Residue *restype);

#endif
