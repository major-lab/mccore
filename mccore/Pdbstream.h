//                              -*- Mode: C++ -*- 
// Pdbstream.h
// Copyright © 1999, 2000-06 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.40 $
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


#ifndef _mccore_Pdbstream_h_
#define _mccore_Pdbstream_h_

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

#include "PdbFileHeader.h"
#include "ResId.h"
#include "TypeRepresentationTables.h"
#include "sockstream.h"
#include "zstream.h"


using namespace std;


namespace mccore
{

  class Atom;
  class AtomSet;
  class AtomType;
  class Residue;
  class ResidueType;
  class Model;


  /**
   * Reads and writes models from and through streams in the Protein Data
   * Bank (PDB) format.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class Pdbstream
  {
  public:

    static const unsigned int LINELENGTH = 80;

    static const unsigned int PDB = 0;
    static const unsigned int AMBER = 1;

    /**
     * The atom type input parse table for Pdb streams.
     */
    static const PdbAtomTypeRepresentationTable *pdbAtomTypeParseTable;
    
    /**
     * The atom type input parse table for Amber streams.
     */
    static const AmberAtomTypeRepresentationTable *amberAtomTypeParseTable;
    
    /**
     * The residue type input parse table for Pdb streams.
     */
    static const PdbResidueTypeRepresentationTable *pdbResidueTypeParseTable;
    
    /**
     * The residue type input parse table for Amber streams.
     */
    static const AmberResidueTypeRepresentationTable *amberResidueTypeParseTable;

    /**
     * Initialises the representation tables.
     */
    static void init ();

    /**
     * Uses specific type table to parse type string.
     * @param str the sring representation to parse.
     * @param type the table type (0 for PDB, 1 for Amber, default is 0)
     */
    static const ResidueType* parseResidueType (const char* str, unsigned int type = 0);

    /**
     * Uses specific type table to get type string representation.
     * @param str the sring representation to parse.
     * @param type the table type (0 for PDB, 1 for Amber, default is 0)
     */
    static const char* stringifyResidueType (const ResidueType* rtype, unsigned int type = 0);

    /**
     * Uses specific type table to parse type string.
     * @param str the sring representation to parse.
     * @param type the table type (0 for PDB, 1 for Amber, default is 0)
     */
    static const AtomType* parseAtomType (const char* str, unsigned int type = 0);

    /**
     * Uses specific type table to get type string representation.
     * @param str the sring representation to parse.
     * @param type the table type (0 for PDB, 1 for Amber, default is 0)
     */
    static const char* stringifyAtomType (const AtomType* rtype, unsigned int type = 0);
    
    /**
     * Trims any leading or trailing whitespaces on a string. 
     * @param str the string to trim.
     * @return the trimmed string;
     */
    static string trim (const string &str);
  };

  
  /**
   * @short Pdb file input stream.
   *
   * This stream is used to input residues from pdb files.  It reads raw
   * residues trying not to reject them.
   *
   * <pre>
   * ATOM FIELD
   * COLUMNS        DATA TYPE       FIELD         DEFINITION
   * -----------------------------------------------------------------------
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
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class iPdbstream : public istream
  {

    /**
     * The PDB header (only the part that we read!).
     */
    PdbFileHeader header;
  
    /**
     * Whether or not the header has been input yet.
     */
    bool header_read;

    /**
     * Last read line.
     */
    string cached_line;

    /**
     * Flag raised to use last read line instead of reading a new one.
     */
    bool use_cached_line;

    /** 
     * The cached residue type.
     */
    const ResidueType *rtype;

    /**
     * The cached res id.
     */
    ResId rid;

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

    /**
     * The input type.  Possible values are: Pdbstream::PDB (default) and
     * Pdbstream::AMBER.
     */
    unsigned int pdbType;

    /**
     * The alternate location marker
     */
    char altloc;
    
    /**
     * The current parse table for atom types.
     */
    const TypeRepresentationTables< AtomType > *atomTypeParseTable;
    
    /**
     * The current parse table for residue types.
     */
    const TypeRepresentationTables< ResidueType > *residueTypeParseTable;
    
  public:

    // LIFECYCLE -----------------------------------------------------------

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

    // OPERATORS -----------------------------------------------------------

    // ACCESS --------------------------------------------------------------

    /**
     * Gets the header information.
     * @return the PDBFileHeader
     */
    const PdbFileHeader& getHeader () const { return header; }

    /**
     * Sets the header information.
     * @param h the new header.
     */
    void setHeader (const PdbFileHeader& h) { header = h; }

    /**
     * Gets the number of the model currently being read.
     */
    int getModelNb () { return modelNb; }

    /**
     * Sets the PDB type.
     * @param type the PDB type.
     */
    void setPDBType (unsigned int type);

    // METHODS -------------------------------------------------------------

    /**
     * Opens the stream and initializes the slots.
     */
    void open ();

    /**
     * Closes the stream.
     */
    virtual void close ();
    
    /**
     * Clears the stream's state.
     */
    void clear ();

    /**
     * Reads the next line from the stream.
     * @param line the string that will contains the read line.
     * @return itself.
     */
    iPdbstream& readLine (string& line);

    /**
     * Makes next call to readLine() returns the line read from the last call to readLine()
     * instead of reading a new line from the stream. 
     * It doesn't go beyond the last call to readLine().
     */
    void unreadLine ();

    /**
     * Indicates if the parser has reached an ENDMDL tag (end of model)
     */
    bool eom () { return (eomFlag || eof ()); }

    // PRIVATE METHODS -----------------------------------------------------

  private:

    /**
     * @internal
     * Reads an atom from the stream and cache it.
     * @return the Atom or null if EOF was reached.
     */
    Atom* cacheAtom ();

    /**
     * @internal
     * Reads the file header from the stream.
     */
    void _read_header ();

    // I/O -----------------------------------------------------------------

  public:

    /**
     * Reads an atom from the stream.
     * @param at the atom to read.
     */
    void read (Atom &at);
    
    /**
     * Reads a residue from the stream.
     * @return r the residue to read.
     */
    void read (Residue &r);

  };


  /**
   * @short Pdb file output stream.
   *
   * This stream is used to output residues to pdb files.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class oPdbstream : public ostream
  {

    /**
     * The PDB header (only the part that we read!).
     */
    PdbFileHeader header;
    
    /**
     * Whether or not the header has been output yet.
     */
    bool header_written;

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
    ResId rid;

    /**
     * The current model number.
     */
    int modelnb;

    /**
     * Atom counter.
     */
    int atomCounter;    

    /**
     * The output type.  Possible values are: AtomType::PDB (default) and
     * AtomType::AMBER.
     */
    unsigned int pdbType;    
    
    /**
     * The current parse table for atom types.
     */
    const TypeRepresentationTables< AtomType > *atomTypeParseTable;
    
    /**
     * The current parse table for residue types.
     */
    const TypeRepresentationTables< ResidueType > *residueTypeParseTable;
    
  public:

    // LIFECYCLE -----------------------------------------------------------

    /**
     * Initializes the stream.
     */
    oPdbstream ();

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    oPdbstream (streambuf* sb);

    oPdbstream (ostream &os);
    
    /**
     * Destroys the stream.
     */
    virtual ~oPdbstream ();


    // OPERATORS -----------------------------------------------------------

    /**
     * Casts the pdb stream to a ostream.
     * @return the ostream.
     */
    operator ostream* () { return dynamic_cast<ostream*>(this); }
    

    // ACCESS --------------------------------------------------------------

    /**
     * Gets the header information.
     * @return the PDBFileHeader
     */
    const PdbFileHeader& getHeader () const
    {
      return this->header;
    }

    /**
     * Sets the header information.
     * @param h the new header.
     */
    void setHeader (const PdbFileHeader& h)
    {
      this->header = h;
    }

    /**
     * Sets the atomset filter used for dumping residues.
     * @param as the atom set filter.
     */
    void setAtomSet (const AtomSet& as);
    
    /**
     * Sets the residue type of all successive calls to write (atom).
     * @param t the residue type.
     */
    void setResidueType (const ResidueType *t) { rtype = t; }

    /**
     * Sets the residue id of all successive calls to write (atom).
     * @param r the ResId.
     */
    void setResId (const ResId &r)
    {
      this->rid = r;
    }

    /**
     * Sets the PDB type.
     * @param type the PDB type.
     */
    void setPDBType (unsigned int type);

    // METHODS -------------------------------------------------------------
    
    /**
     * Opens a pdb stream.  Resets the slots.
     */
    void open ();
    
    /**
     * Closes a pdb stream.  It writes the END record.
     */
    virtual void close ();

    /**
     * Clears the stream's state.
     */
    void clear ();

    /**
     * Writes a standard multilined record, each text line
     * starting after the record type at column 11. Continuation number is added 
     * at columns 9 to 10.
     * @param name the record type
     * @param text the record text that will be wrapped in multiple lines
     * @param writable the writable line length, if smaller than @ref Pdbstream::LINELENGTH
     */
    void writeRecord (const string& name, 
		      const string& text, 
		      size_t writable = Pdbstream::LINELENGTH);

    /**
     * Writes a standard multilined remark.
     * @param remark the remark text that will be wrapped in multiple lines.
     * @param k the remark's ID number for further classification.
     * @param writable the writable line length, if smaller than @ref Pdbstream::LINELENGTH
     */
    void writeRemark (const string& remark, int k);

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

  protected:

    /**
     * @internal
     * Writes the header to the stream.
     */
    void _write_header ();

    /**
     * Writes a END record to the pdb stream.
     */
    void end ();

    /**
     * Write i whitespace to the stream
     */ 
    void pad (int i);

  public:
    
    // I/O -----------------------------------------------------------------

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
     * Writes an atom to the stream.
     * @param at the atom to write.
     */
    void write (const Atom &at);
    
    /**
     * Writes a residue to the pdb stream.
     * @param at the residue to write.
     */
    void write (const Residue &r);

  };


  /**
   * @short Input pdb file stream.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class ifPdbstream : public iPdbstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    ifPdbstream ()
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with a file name and optional mode and
     * protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::in).
     */
    ifPdbstream (const char *name, ios_base::openmode mode = ios_base::in)
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the file stream with a file name and optional mode and
     * protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
	this->setstate (ios::failbit);
      iPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      iPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };
  
  
  /**
   * @short Output pdb file stream.
   *
   * This stream can be used as a regular file stream (ofstream).  The output
   * is formatted for pdb files.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class ofPdbstream : public oPdbstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    ofPdbstream ()
      : oPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with a file name and an optional mode and
     * protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::out).
     */
    ofPdbstream (const char *name, ios_base::openmode mode = ios_base::out)
      : oPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with a file name and an optional mode and
     * protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::out | ios_base::trunc).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc)
    {
      if (! buf.open (name, mode | ios_base::out))
	this->setstate (ios::failbit);
      oPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      oPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };


  /**
   * @short Input pdb socket stream.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class isPdbstream : public iPdbstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    isPdbstream ()
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    isPdbstream (const char *host, unsigned int port)
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }
    
    /**
     * Initializes the stream with a socket descriptor.
     * @param id the socket descriptor.
     */
    isPdbstream (int desc)
      : iPdbstream (),
	buf (desc)
    {
      this->init (&buf);
      iPdbstream::open ();
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
	this->setstate (ios::failbit);
      iPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      iPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };
  
  
  /**
   * @short Output pdb socket stream.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class osPdbstream : public oPdbstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    osPdbstream ()
      : oPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    osPdbstream (const char *host, unsigned int port)
      : oPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }
    
    /**
     * Initializes the stream with a socket descriptor.
     * @param id the socket descriptor.
     */
    osPdbstream (int desc)
      : oPdbstream (),
	buf (desc)
    {
      this->init (&buf);
      oPdbstream::open ();
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
	this->setstate (ios::failbit);
      oPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      oPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };


  /**
   * @short Pdb socket stream.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class sPdbstream : public iPdbstream, public oPdbstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the stream.
     */
    sPdbstream ()
      : iPdbstream (),
	oPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    sPdbstream (const char *host, unsigned int port)
      : iPdbstream (),
	oPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }
    
    /**
     * Initializes the stream with a socket descriptor.
     * @param id the socket descriptor.
     */
    sPdbstream (int desc)
      : iPdbstream (),
	oPdbstream (),
	buf (desc)
    {
      this->init (&buf);
      iPdbstream::open ();
      oPdbstream::open ();
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Initializes the stream with host name and port number.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
	this->setstate (ios::failbit);
      iPdbstream::open ();
      oPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      oPdbstream::close ();
      iPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };


  /**
   * @short Compressed input pdb file stream.
   *
   * This stream can be used the same way as the ifPdbstream except that it
   * can read compressed files.
   *
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class izfPdbstream : public iPdbstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the objet.
     */
    izfPdbstream ()
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the objet with a file name and optional mode and
     * protection.  The zfstreambase is open with Z_BEST_SPEED compression
     * flag.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::in).
     */
    izfPdbstream (const char *name, ios_base::openmode mode = ios_base::in)
      : iPdbstream (),
	buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the file stream with a file name and optional mode and
     * protection.  The zfstreambase is open with Z_BEST_SPEED compression
     * flag.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
	this->setstate (ios::failbit);
      iPdbstream::open ();
    }
    
    /**
     * Closes the stream.
     */
    void close ()
    {
      iPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };
  
  
  /**
   * @short Output compressed pdb file stream.
   *
   * This stream can be used the same way as the ofPdbstream except that it
   * produces compressed pdb files.  The compression level is defaulted to
   * Z_BEST_SPEED but it can be modified on constructor and open operations.
   * Please do not use Z_NO_COMPRESSION (level 0): it produces a gzip header
   * and footer to the file (witch is often not desired).
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>.
   * @author Martin Larose (<a href="mailto:larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Pdbstream.h,v 1.40 2006-11-15 19:44:58 larosem Exp $
   */
  class ozfPdbstream : public oPdbstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;
    
  public:
    
    // LIFECYCLE -----------------------------------------------------
    
    /**
     * Initializes the pdb file stream.
     */
    ozfPdbstream ()
      : oPdbstream (),
	buf()
    {
      this->init (&buf);
    }
    
    /**
     * Initializes the pdb file stream with a file name and optional mode,
     * compression level and protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::out).
     * @param level the compression level (default = Z_BEST_SPEED).
     */
    ozfPdbstream (const char *name, ios_base::openmode mode = ios_base::out, int level = 1 /* Z_BEST_SPEED */)
      : oPdbstream (),
	buf()
    {
      this->init (&buf);
      this->open (name, mode, level);
    }
    
    // OPERATORS -----------------------------------------------------
    
    // ACCESS --------------------------------------------------------
    
    // METHODS -------------------------------------------------------
    
    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the pdb file stream with a file name and optional mode,
     * compression level and protection.
     * @param name the file name.
     * @param mode the ios mode (default = ios_base::out | ios_base::trunc).
     * @param level the compression level (default = Z_BEST_SPEED).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc, int level = 1 /* Z_BEST_SPEED */)
    {
      if (! buf.open (name, mode | ios_base::out, level))
	this->setstate (ios::failbit);
      oPdbstream::open ();
    }
    
    /**
     * Closes the compressed pdb file stream.
     */
    void close ()
    {
      oPdbstream::close ();
      if (! buf.close ())
	this->setstate (ios::failbit);
    }
    
    // I/O -----------------------------------------------------------
  };
}
  
#endif
