//                              -*- Mode: C++ -*- 
// Pdbstream.h
// Copyright © 1999, 2000-03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.18 $
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


#ifndef _Pdbstream_h_
#define _Pdbstream_h_

#include <iostream>
#include <algorithm>
#include <string>

#include "PdbFileHeader.h"
#include "ResId.h"

using namespace std;

namespace mccore {

  class AtomType;
  class ResidueType;
  class Atom;
  class ResId;
  class Residue;
  class AtomSet;
  class Model;

  /**
   * @short Pdb file input stream.
   *
   * This stream is used to input residues from pdb files.  It reads raw
   * residues trying not to reject them.
   *
   * <pre>
   * ATOM FIELD
   * COLUMNS        DATA TYPE       FIELD         DEFINITION
   * ---------------------------------------------------------------------------------
   *  1 -  6        Record name     "ATOM  "
   *  7 - 11        Integer         serial        Atom serial number.
   * 13 - 16        Atom            name          Atom name.
   * 17             Character       altLoc        Alternate location indicator.
   * 18 - 20        Residue name    resName       Residue name.
   * 22             Character       chainID       Chain identifier.
   * 23 - 26        Integer         resSeq        Residue sequence number.
   * 27             AChar           iCode         Code for insertion of residues.
   * 31 - 38        Real(8.3)       x             Orthogonal coordinates for X in
   *                                              Angstroms.
   * 39 - 46        Real(8.3)       y             Orthogonal coordinates for Y in
   *                                              Angstroms.
   * 47 - 54        Real(8.3)       z             Orthogonal coordinates for Z in                                             Angstroms.
   * 55 - 60        Real(6.2)       occupancy     Occupancy.
   * 61 - 66        Real(6.2)       tempFactor    Temperature factor.
   * 73 - 76        LString(4)      segID         Segment identifier, left-justified.
   * 77 - 78        LString(2)      element       Element symbol, right-justified.
   * 79 - 80        LString(2)      charge        Charge on the atom.
   * </pre>
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   * @version $Id: Pdbstream.h,v 1.18 2003-07-11 20:28:20 gendrop Exp $
   */
  class iPdbstream : public istream
  {
    static const int LINELENGTH;

    /**
     * The PDB header (only the part that we read!).
     */
    PdbFileHeader header;
  
    /** 
     * The cached residue type.
     */
    const ResidueType *rtype;

    /**
     * The cached res id.
     */
    ResId *rid;

    /**
     * The cached atom
     */
    Atom *ratom;
  
    /**
     * Current model nb.
     */
    int modelNb;

    /**
     * Flag for end of model status.
     */
    bool eomFlag;

  public:

    // LIFECYCLE -----------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    iPdbstream ();

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    iPdbstream (streambuf* sb);

    /**
     * Destroys the object.
     */
    virtual ~iPdbstream ();

    // OPERATORS -----------------------------------------------------------------

    // ACCESS --------------------------------------------------------------------

    /**
     * Gets the header information.
     * @return the PDBFileHeader
     */
    const PdbFileHeader& getHeader ();

    /**
     * Gets the number of the model currently being read.
     */
    int getModelNb () { return modelNb; }

    // METHODS -------------------------------------------------------------------

    /**
     * Gets a text line.  Same as the inherited one except that the endline
     * may be one of \n or \r.
     * @param buffer the buffer where the characters are copied.
     * @param sz the maximum reading number of characters.
     * @return the input stream.
     */
    iPdbstream& getline (char*, unsigned int sz);

    /**
     * Opens the stream and initializes the slots.
     */
    void open ();

    /**
     * Closes the stream.
     */
    virtual void close ();
    
    /**
     * Indicates if the parser has reached an ENDMDL tag (end of model)
     */
    bool eom () { return (eomFlag || eof ()); }

    // PRIVATE METHODS ---------------------------------------------------------

  private:

    /**
     * Reads an atom from the stream and cache it.
     * @return the Atom or null if EOF was reached.
     */
    Atom* cacheAtom ();

    /**
     * Trims the whitespaces around the string.
     * @param cp the string to trim.
     * @return the stripped trim (actually a ptr on the original string with the end moved).
     */
    char* trim (char* cp);

    // I/O ---------------------------------------------------------------------

  public:

    /**
     * Reads an atom from the stream.
     * @param at the atom to read.
     * @return the Pdbstream.
     */
    iPdbstream& operator>> (Atom &at);
    
    /**
     * Reads a residue from the stream.
     * @param r the residue to read.
     * @return the Pdbstream.
     */
    iPdbstream& operator>> (Residue &r);

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
    static const int LINELENGTH;

    /**
     * The PDB header (only the part that we read!).
     */
    PdbFileHeader header;
    
    /**
     * Wether or not the header has been output yet.
     */
    bool headerdone;

    /**
     * Atom set filter function.
     */
    AtomSet *atomset;

    /**
     * The current residue type.
     */
    const ResidueType *rtype;

    /**
     * The current residue id.
     */
    ResId *rid;

    /**
     * The current model number.
     */
    int modelnb;

    /**
     * Atom counter.
     */
    int n;    

    /**
     * Nb of bytes written on the current line
     */
    
    
  public:

    // LIFECYCLE ---------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    oPdbstream ();

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    oPdbstream (streambuf* sb);

    
    /**
     * Destroys the stream.
     */
    virtual ~oPdbstream ();


    // OPERATORS ---------------------------------------------------------------

    /**
     * Casts the pdb stream to a ostream.
     * @return the ostream.
     */
    operator ostream* () { return dynamic_cast<ostream*>(this); }
    

    // ACCESS ------------------------------------------------------------------

    /**
     * Sets the atomset filter used for dumping residues.
     * @param s the atom set filter.
     */
    void setAtomSet (AtomSet *s) { atomset = s; }
    
    /**
     * Sets the residue type of all successive calls to write (atom).
     * @param t the residue type.
     */
    void setResidueType (const ResidueType *t) { rtype = t; }

    /**
     * Sets the residue id of all successive calls to write (atom).
     * @param r the ResId.
     */
    void setResId (const ResId &r) { 
      if (!rid) rid = new ResId (r); 
      else *rid = r;
    }    

    /**
     * Sets the header for the file.
     */
    void setHeader (const PdbFileHeader &h) { header = h; } 


    // METHODS -----------------------------------------------------------------
    
    /**
     * Opens a pdb stream.  Resets the slots.
     */
    void open ();
    
    /**
     * Closes a pdb stream.  It writes the END record.
     */
    virtual void close ();

    /**
     * Writes the current header to the stream.
     */
    void writeHeader ();

    /**
     * Writes a remark.
     * @param k the type of remark.
     * @param rem the remark.
     */
    void writeRemark (int k, const char* rem);

    /**
     * Writes a MODEL record to the pdb stream.
     */
    void startModel ();
    
    /**
     * Writes a ENDMDL record to the pdb stream.
     */
    void endModel ();

    /**
     * Writes a TER record to the pdb stream.
     */
    void ter ();

    /**
     * Writes a END record to the pdb stream.
     */
    void end ();

    /**
     * Write i whitespace to the stream
     */ 
    void pad (int i);

  protected:
    
    // I/O ---------------------------------------------------------------------

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

  public:

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

    /**
     * Writes an atom to the pdb stream.
     * @param at the atom to write.
     * @return itself.
     */
    oPdbstream& operator<< (const Atom& at);

    /**
     * Writes a residue to the pdb stream.
     * @param at the residue to write.
     * @return itself.
     */
    oPdbstream& operator<< (const Residue& r);

  };  
  
}

#endif
