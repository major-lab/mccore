//                              -*- Mode: C++ -*- 
// Pdbstream.h
// Copyright � 1999, 2000-03 Laboratoire de Biologie Informatique et Th�orique.
//                           Universit� de Montr�al.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.14.4.1 $
// $Id: Pdbstream.h,v 1.14.4.1 2003-12-10 14:18:55 larosem Exp $
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


#ifndef _Pdbstream_h_
#define _Pdbstream_h_

#include <iostream>

#include "CResId.h"
#include "CAtom.h"

class Model;
class t_Residue;
class t_Atom;

using namespace std;



/**
 * @short Pdb file input stream.
 *
 * This stream is used to input residues from pdb files.  It reads raw
 * residues trying not to reject them.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class iPdbstream : public istream
{
  /**
   * The previously read atom.
   */
  CAtom* previous_atom;

  /**
   * The type of the previous residue.
   */
  t_Residue *previous_res_type;

  /**
   * The id of the previous residue.
   */
  CResId previous_res_id;

  /**
   * The type of the current residue.
   */
  t_Residue *current_res_type;

  /**
   * The id of the current residue.
   */
  CResId current_res_id;

  /**
   * Indicates whether the reader reached the end of a chain.
   */
  bool end_of_chain;
  
  /**
   * Indicates whether the reader reached the end of a model.
   */
  bool end_of_model;

  /**
   * Indicates whether the reader reached the end of the pdb file (END
   * record type).
   */
  bool end_of_pdb;

  /**
   * The input buffer that keeps the pdb line.
   */
  char line [256];

  /**
   * Temporary buffer.
   */
  mutable char buffer [256];

  /**
   * Strips the whitespaces around the strings.
   * @param cp the string to strip.
   * @return the stripped string.
   */
  static char* Strip (char *cp);

public:

  /**
   * Gets the residue type given it's string representation.
   * @param s the residue type representation.
   * @return the residue type.
   */
  static t_Residue* GetResidueType (char *s);

  /**
   * Gets the atom type given it's string representation.
   * @param s the atom type representation.
   * @param res_type the residue type.
   * @return the atom type.
   */
  static t_Atom* GetAtomType (char *s, t_Residue *res_type = 0);

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  iPdbstream ()
    : istream (cin.rdbuf ()),
      previous_atom (0),
      previous_res_type (0),
      current_res_type (0),
      end_of_chain (false),
      end_of_model (false),
      end_of_pdb (false)
  { }

  /**
   * Initializes the stream with a predefined stream buffer.
   * @param sb the stream buffer.
   */
  iPdbstream (streambuf* sb)
    : istream (sb),
      previous_atom (0),
      previous_res_type (0),
      current_res_type (0),
      end_of_chain (false),
      end_of_model (false),
      end_of_pdb (false)
  { }

  // OPERATORS -----------------------------------------------------

  /**
   * Casts the pdb stream to a istream.
   * @return the istream.
   */
  operator istream* () { return dynamic_cast<istream*>(this); }

  /**
   * Reads the pdb stream to an object.
   * @param obj the templated object.
   * @return itself.
   */
  template< class T >iPdbstream& operator>> (T& obj);

  // ACCESS ---------------------------------------------------------------

  /**
   * Tests whether the stream has reached the end of a chain.
   * @return the truth value.
   */
  bool eoc () const { return end_of_chain; }
  
  /**
   * Tests whether the stream has reached the end of a model.
   * @return the truth value.
   */
  bool eom () const { return end_of_model; }

  /**
   * Tests whether the stream has reached the end of the pdb.
   * @return the truth value.
   */
  bool eop () const { return end_of_pdb; }

  /**
   * Gets the value of the previous atom.
   * @return the atom previously read.
   */
  CAtom* GetAtom () const { return previous_atom; }

  /**
   * Gets the type of the previously read residue.
   * @return the residue type.
   */
  t_Residue* GetPrevResType () const { return previous_res_type; }

  /**
   * Gets the id of the previously read residue.
   * @return the residue id.
   */
  const CResId& GetPrevResId () const { return previous_res_id; }

  /**
   * Gets the residue type of the pdb atom record.
   * @return the residue type.
   */
  t_Residue* GetResType () const { return current_res_type; }

  /**
   * Gets the residue id of the pdb atom record.
   * @return the residue id.
   */
  CResId GetResId () const { return current_res_id; }

  // METHODS --------------------------------------------------------------

  /**
   * Gets a text line.  Same as the inherited one except that the endline
   * may be one of \n or \r.
   * @param buffer the buffer where the characters are copied.
   * @param sz the maximum reading number of characters.
   * @return the input stream.
   */
  iPdbstream& getline (char *buffer, unsigned int sz);

  /**
   * Reads the next line from the pdb stream and put it in the line buffer.
   * Triggers the end of model and end of pdb flags.
   * @return the number of character read.
   */
  size_t getline ();

  /**
   * Gets the record name of the pdb line.
   * @return the record name.
   */
  const char* GetRecordType () const;

  /**
   * Gets the atom type of the pdb atom record.
   * @return the atom type.
   */
  t_Atom* GetAtomType () const;

  /**
   * Gets the alternate location id of the pdb atom record.
   * @return the alternate location id.
   */
  char GetAltLocId () const;

  /**
   * Gets the x coordinate of the pdb atom record.
   * @return the x coordinate.
   */
  float GetX () const;

  /**
   * Gets the y coordinate of the pdb atom record.
   * @return the y coordinate.
   */
  float GetY () const;

  /**
   * Gets the z coordinate of the pdb atom record.
   * @return the z coordinate.
   */
  float GetZ () const;

  /**
   * Gets the atom coordinates and type.
   * @param atom the atom to fill.
   * @return the atom.
   */
  CAtom& getatom (CAtom &atom);

  /**
   * Keeps the atom for the next residue input.
   * @param atom the atom to keep.
   */
  void KeepAtom (const CAtom &atom);

  /**
   * Removes the atom from the previous atom slot.
   */
  void DeleteAtom ();

  /**
   * Places the current residue id and type to their respective previous
   * slots.
   */
  void NewRes ();

  /**
   * Opens the stream and initializes the slots.
   */
  void open ();

  /**
   * Closes the stream.
   */
  void close () { }

  // I/O ------------------------------------------------------------------
};



/**
 * @short Pdb file output stream.
 *
 * This stream is used to output residues to pdb files.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class oPdbstream : public ostream
{
  /**
   * Atom set filter function.
   */
  AtomSet *atomset;

  /**
   * The residue type of the saved residue.
   */
  const t_Residue *restype;

  /**
   * The residue number of the saved residue.
   */
  int resno;

  /**
   * The chain id of the saved residue.
   */
  char chainid;

  /**
   * The insertion code of the saved residue.
   */
  char iCode;

  /**
   * The atom serial number of the saved atom.
   */
  int mCurrentAtomNo;

  /**
   * The model number.
   */
  int mModelNo;
  
  /**
   * Line buffer.
   */
  char line[81];

public:

  // LIFECYCLE -----------------------------------------------------

  /**
   * Initializes the stream.
   */
  oPdbstream ()
    : ostream (cout.rdbuf ()),
      atomset (new no_pse_lp_atom_set ()),
      restype (0),
      mCurrentAtomNo (1),
      mModelNo (1)
  { }

  /**
   * Initializes the stream with a predefined stream buffer.
   * @param sb the stream buffer.
   */
  oPdbstream (streambuf* sb)
    : ostream (sb),
      atomset (new no_pse_lp_atom_set ()),
      restype (0),
      mCurrentAtomNo (1),
      mModelNo (1)
  { }

  /**
   * Destructs the stream.
   */
  virtual ~oPdbstream () { delete atomset; }

  // OPERATORS -----------------------------------------------------

  /**
   * Casts the pdb stream to a ostream.
   * @return the ostream.
   */
  operator ostream* () { return dynamic_cast<ostream*>(this); }

  /**
   * Writes a character to the pdb stream.
   * @param c the character to write.
   * @return itself.
   */
  oPdbstream& operator<< (char c)
  { *(ostream*)this << c; return *this; }

  /**
   * Writes a unsigned char to the pdb stream.
   * @param c the unsigned char to write.
   * @return itself.
   */
  oPdbstream& operator<< (unsigned char c) { return operator<< ((char)c); }

  /**
   * Writes a signed char to the pdb stream.
   * @param c the signed char to write.
   * @return itself.
   */
  oPdbstream& operator<< (signed char c) { return operator<< ((char)c); }

  /**
   * Writes a string to the pdb stream.
   * @param s the string to write.
   * @return itself.
   */
  oPdbstream& operator<< (const char *s)
  { *(ostream*)this << s; return *this; }

  /**
   * Writes an unsigned string to the pdb stream.
   * @param s the unsigned string to write.
   * @return itself.
   */
  oPdbstream& operator<< (const unsigned char *s)
  { return operator<< ((const char*)s); }

  /**
   * Writes a signed string to the pdb stream.
   * @param s the signed string to write.
   * @return itself.
   */
  oPdbstream& operator<< (const signed char *s)
  { return operator<< ((const char*)s); }

  /**
   * Writes an integer to the pdb stream.
   * @param n the integer to write.
   * @return itself.
   */
  oPdbstream& operator<< (int n)
  { *(ostream*)this << n; return *this; }

  /**
   * Writes an unsigned integer to the pdb stream.
   * @param n the unsigned integer to write.
   * @return itself.
   */
  oPdbstream& operator<< (unsigned int n)
  { *(ostream*)this << n; return *this; }

  /**
   * Writes a long integer to the pdb stream.
   * @param n the long integer to write.
   * @return itself.
   */
  oPdbstream& operator<< (long n)
  { *(ostream*)this << n; return *this; }

  /**
   * Writes an unsigned long integer to the pdb stream.
   * @param n the unsigned long integer to write.
   * @return itself.
   */
  oPdbstream& operator<<(unsigned long n)
  { *(ostream*)this << n; return *this; }

  /**
   * Writes a double real to the pdb stream.
   * @param n the double real to write.
   * @return itself.
   */
  oPdbstream& operator<< (double n)
  { *(ostream*)this << n; return *this; }

  /**
   * Writes a float to the pdb stream.
   * @param n the float to write.
   * @return itself.
   */
  oPdbstream& operator<< (float n) { return operator<< ((double)n); }

  /**
   * Writes a long double to the pdb stream.
   * @param n the long double to write.
   * @return itself.
   */
  oPdbstream& operator<< (long double n) { return operator<< ((double)n); }

  /**
   * Modifies the pdb stream.
   * @param func the ios manipulator function.
   * @return itself.
   */
  oPdbstream& operator<< (ios& (*func)(ios&))
  { (*func)(*(ostream*)this); return *this; }

  /**
   * Modifies the pdb stream.
   * @param func the ostream manipulator function.
   * @return itself.
   */
  oPdbstream& operator<< (ostream& (*func)(ostream&))
  { (*func)(*(ostream*)this); return *this; }


  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the atom set function.
   * @return the atom set function.
   */
  const AtomSet* GetAtomSet () const { return atomset; }

  /**
   * Sets the atom set function.
   * @param as the new atom set function.
   */
  void SetAtomSet (AtomSet *as) { delete atomset; atomset = as; }

  /**
   * Sets the residue type of the outputted atom.
   * @param type the residue type.
   */
  void SetResType (const t_Residue *type) { restype = type; }

  /**
   * Sets the residue id of the outputted atom.
   * @param resid the residue id.
   */
  void SetResId (const CResId &resid);

  // METHODS --------------------------------------------------------------

  /**
   * Opens a pdb stream.  Resets the slots.
   */
  void open ();

  /**
   * Closes a pdb stream.  It writes the END record.
   */
  virtual void close () { END (); }

  // I/O ------------------------------------------------------------------

  /**
   * Writes the header of the pdb file.  EXPDTA, AUTHOR, REMARKs 220 and
   * 225.
   */
  void putheader ();

  /**
   * Writes a REMARK record to the pdb stream.
   * @param k the remark number.
   * @param rem the remark string.
   */
  void putremark (unsigned int k, const char *rem);

  /**
   * Writes an ATOM record or a HETATM atom to the pdb stream.  The residue
   * type determines witch is used.
   * @param atom the atom to put.
   */
  void putatom (const CAtom &atom);

  /**
   * Writes a model to the pdb stream.  It writes the MODEL, the model and
   * the ENDMDL records.
   * @param model the model to output.
   */
  void putmodel (const Model &model);

  /**
   * Writes the CONECT records.
   * @param model the model to write the conect for.
   */
  void putconect (const Model &model);

  /**
   * Writes a MODEL record to the pdb stream.
   */
  void MODEL ();

  /**
   * Writes a TER record to the pdb stream.
   */
  void TER ();

  /**
   * Writes a ENDMDL record to the pdb stream.
   */
  void ENDMDL ();

  /**
   * Writes a END record to the pdb stream.
   */
  void END ();

};

#endif
