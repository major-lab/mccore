//                              -*- Mode: C++ -*- 
// Pdbstream.cc
// Copyright © 1999, 2000-05 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.52 $
// $Id: Pdbstream.cc,v 1.52 2005-02-18 20:29:44 thibaup Exp $
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

#include <ctype.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

#include "Atom.h"
#include "AtomType.h"
#include "Model.h"
#include "Pdbstream.h"
#include "Messagestream.h"
#include "Exception.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueType.h"



namespace mccore
{

  const PdbAtomTypeRepresentationTable *Pdbstream::pdbAtomTypeParseTable = 0;
  const AmberAtomTypeRepresentationTable *Pdbstream::amberAtomTypeParseTable = 0;
  const PdbResidueTypeRepresentationTable *Pdbstream::pdbResidueTypeParseTable = 0;
  const AmberResidueTypeRepresentationTable *Pdbstream::amberResidueTypeParseTable = 0;
  

  void
  Pdbstream::init ()
  {
    if (0 == Pdbstream::pdbAtomTypeParseTable)
      {
	Pdbstream::pdbAtomTypeParseTable = new PdbAtomTypeRepresentationTable ();
	Pdbstream::amberAtomTypeParseTable = new AmberAtomTypeRepresentationTable ();
	Pdbstream::pdbResidueTypeParseTable = new PdbResidueTypeRepresentationTable ();
	Pdbstream::amberResidueTypeParseTable = new AmberResidueTypeRepresentationTable ();
      }
  }    

  
  const ResidueType*
  Pdbstream::parseResidueType (const char* str, unsigned int type)
  {
    string key (str);

    Pdbstream::init ();
    if (Pdbstream::PDB == type)
      return Pdbstream::pdbResidueTypeParseTable->parseType (key);
    else if (Pdbstream::AMBER == type)
      return Pdbstream::amberResidueTypeParseTable->parseType (key);
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown table type " << type << " in Pdbstream::parseResidueType.";
      throw ex;
    }
    return 0;
  }

  
  const char*
  Pdbstream::stringifyResidueType (const ResidueType* rtype, unsigned int type)
  {
    Pdbstream::init ();
    if (Pdbstream::PDB == type)
      return Pdbstream::pdbResidueTypeParseTable->toString (rtype);
    else if (Pdbstream::AMBER == type)
      return Pdbstream::amberResidueTypeParseTable->toString (rtype);
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown table type " << type << " in Pdbstream::stringifyResidueType.";
      throw ex;
    }
    return 0;
  }


  const AtomType*
  Pdbstream::parseAtomType (const char* str, unsigned int type)
  {
    Pdbstream::init ();
    string key (str);
    if (Pdbstream::PDB == type)
      return Pdbstream::pdbAtomTypeParseTable->parseType (key);
    else if (Pdbstream::AMBER == type)
      return Pdbstream::amberAtomTypeParseTable->parseType (key);
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown table type " << type << " in Pdbstream::parseAtomType.";
      throw ex;
    }
    return 0;
  }

  
  const char*
  Pdbstream::stringifyAtomType (const AtomType* rtype, unsigned int type)
  {
    Pdbstream::init ();
    if (Pdbstream::PDB == type)
      return Pdbstream::pdbAtomTypeParseTable->toString (rtype);
    else if (Pdbstream::AMBER == type)
      return Pdbstream::amberAtomTypeParseTable->toString (rtype);
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown table type " << type << " in Pdbstream::stringifyAtomType.";
      throw ex;
    }
    return 0;
  }
  

  string
  Pdbstream::trim (const string& str)
  {
    string::size_type b = str.find_first_not_of (" \t\n\r\f");
    string::size_type e = str.find_last_not_of (" \t\n\r\f");

    if (string::npos == b && string::npos == e)
    {
      string es;
      return es;
    }
    
    return str.substr (string::npos == b ? 0 : b, 
		       string::npos == e ? e : e - b + 1);
  }

  iPdbstream::iPdbstream ()
    : istream (cin.rdbuf ()),
      header_read (false),
      use_cached_line (false),
      rtype (ResidueType::rNull),
      ratom (0),
      modelNb (1),
      eomFlag (false),
      pdbType (Pdbstream::PDB),
      altloc (' ')
  {
    Pdbstream::init ();
    atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
    residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
  }
  
  
  iPdbstream::iPdbstream (streambuf* sb)
    : istream (sb),
      header_read (false),
      use_cached_line (false),
      rtype (ResidueType::rNull),
      ratom (0),
      modelNb (1),
      eomFlag (false),
      pdbType (Pdbstream::PDB),
      altloc (' ')
  {
    Pdbstream::init ();
    atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
    residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
  }
  
  iPdbstream::~iPdbstream ()
  {
    if (ratom) delete ratom;
  }

  
  void
  iPdbstream::setPDBType (unsigned int type)
  {
    pdbType = type;
    if (Pdbstream::AMBER == type)
      {
	atomTypeParseTable = Pdbstream::amberAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::amberResidueTypeParseTable;
      }
    else
      {
	atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
      }	
  }
  

  void
  iPdbstream::open () 
  { 

  }


  void
  iPdbstream::close () 
  { 
    this->header.clear ();
    this->use_cached_line = false;
    this->eomFlag = true;
    if (ratom) delete ratom;
  }


  void
  iPdbstream::clear ()
  {
    this->istream::clear ();
    this->header_read = false;
    this->use_cached_line = false;
    this->rtype = ResidueType::rNull;
    ResId id;
    this->rid = id;
    if (this->ratom) delete this->ratom;
    this->ratom = 0;
    this->modelNb = 1;
    this->eomFlag = false;
    this->altloc = ' ';
  }


  iPdbstream&
  iPdbstream::readLine (string& line)
  {
    if (this->use_cached_line)
      this->use_cached_line = false;
    else
      std::getline (*this, this->cached_line);

    line = this->cached_line;
    return *this;
  }


  void
  iPdbstream::unreadLine ()
  {
    this->use_cached_line = true;
  }


  Atom*
  iPdbstream::cacheAtom ()
  {    
    string rectype, line;

    // Cleanup any previous read:
    rtype = ResidueType::rNull;
    ResId id;
    this->rid = id;
    if (ratom) delete ratom;
    ratom = 0;
    
    //while (!std::getline (*this, line).eof ())
    while (!this->readLine (line).eof ())
    {
      if (this->fail ())
      {
	IntLibException ex ("read failed", __FILE__, __LINE__);
	throw ex;
      }

      line.resize (Pdbstream::LINELENGTH, ' ');
      rectype = Pdbstream::trim (line.substr (0, 6));

      if ("MODEL" == rectype)
      {	// The eomFlag is reset to false 
      }
      else if ("ENDMDL" == rectype)
      {
	modelNb++;
	eomFlag = true;
      }
      else if ("TER" == rectype)
      {
      }
      else if ("END" == rectype)
      {
	eomFlag = true;
      }
      else if ("ATOM" == rectype || "HETATM" == rectype)
      {
	// ignore this atom if we are in a second alternate location.
	if (' ' == this->altloc || ' ' == line[16] || line[16] == this->altloc)
	{
	  int resno = 0;
	  float x = 0.0, y = 0.0, z = 0.0;
	  const AtomType *at;

	  this->altloc = line[16];

	  // -- coordinates
	  istringstream 
	    x_iss (line.substr (30, 8)), 
	    y_iss (line.substr (38, 8)), 
	    z_iss (line.substr (46, 8));
	  

	  if (!((x_iss >> x).fail () || 
		(y_iss >> y).fail () || 
		(z_iss >> z).fail ()))
	  {
	    // -- types
	    at = atomTypeParseTable->parseType (Pdbstream::trim (line.substr (12, 4)));
	    rtype = residueTypeParseTable->parseType (Pdbstream::trim (line.substr (17, 3)));

	    // -- ResID
	    istringstream resno_iss (line.substr (22, 4));

	    if (!(resno_iss >> resno).fail ())
	    {
	      // -- create the atom and break the reading loop.
	      ResId id (line[21], resno, line[26]);
	      this->rid = id;
	      ratom = new Atom (x, y, z, at);	    
	      break;
	    }
	  }

	  gErr (1) << "Warning: ignored corrupted ATOM record {" << line << "}." << endl;
	}
	else
	  gErr (3) << "Warning: ignored ATOM record with second alternate location {" 
		   << line << "}." << endl;
      }
    }
      
    return ratom;
  }


  void
  iPdbstream::_read_header ()
  {
    if (false == this->header_read)
    {
      this->header_read = true;
      *this >> this->header;
    }
  }


  // I/O -----------------------------------------------------------------------

  void
  iPdbstream::read (Atom &at)
  {
    this->_read_header ();

    // Cache an atom if needed.
    if (!ratom)
      cacheAtom (); 
    // No atom was found, return.
    if (ratom)
      {
	eomFlag = false;
	
	// Copy the return value.
	at = *ratom;
	
	// Cache another atom in order to detect endfiles.
	cacheAtom ();
      }
  }

  
  
  void
  iPdbstream::read (Residue &r)
  {
    this->_read_header ();

    // Cache an atom if needed.
    if (!ratom)
      cacheAtom (); 
    // No atom was found, return.
    if (ratom)
      {
	ResId previd = this->rid;
	const ResidueType* prevtype = rtype;

	eomFlag = false;
	
	r.clear ();
	r.setType (rtype);
	r.setResId (rid);
	r.insert (*ratom);
	
	cacheAtom ();

	/*
	  Inserts read atom for this residue.
	  Stops inserting in any of those three cases:
	    1) Either an END or ENDMDL tag was read or EOF was reached (eom() result).
	    2) ResID for current cached atom is different from last read atom.
	    3) Residue type for current cached atom is different from last read atom.
	*/
	while (!eom () && this->rid == previd && rtype == prevtype)
	  {
	    // Insert the atom.
	    r.insert (*ratom);      
	    
	    // Cache another atom in order to detect endfiles.
	    cacheAtom ();
	  }
	
	// Post reading processing
	if (r.size () > 0)
	  {
	    // Fix type:  The type is converted to DNA only if it
	    // contains a deoxyribose
	    if (r.getType ()->isNucleicAcid () && ! r.contains (AtomType::aO2p) &&
		r.contains (AtomType::aC2p))
	      {
		if (r.getType () == ResidueType::rRA)
		  r.setType (ResidueType::rDA);
		else if (r.getType () == ResidueType::rRC)
		  r.setType (ResidueType::rDC);
		else if (r.getType () == ResidueType::rRG)
		  r.setType (ResidueType::rDG);
		else if (r.getType () == ResidueType::rRU)
		  r.setType (ResidueType::rDT);
	      }

	    // Finalize
	    r.finalize ();
	  }
      }
    
    gOut (6) << "> Read residue " << r << endl;
  }
  

  // LIFECYCLE -----------------------------------------------------------------

  oPdbstream::oPdbstream ()
    : ostream (cout.rdbuf ()),
      header_written (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::rNull),
      modelnb (1),
      atomCounter (1),
      pdbType (Pdbstream::PDB)
  {
    Pdbstream::init ();
    atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
    residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
  }
  


  oPdbstream::oPdbstream (streambuf* sb)
    : ostream (sb),
      header_written (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::rNull),
      modelnb (1),
      atomCounter (1),
      pdbType (Pdbstream::PDB)
  {
    Pdbstream::init ();
    atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
    residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
  }


  oPdbstream::oPdbstream (ostream &os)
    : ostream (os.rdbuf ()),
      header_written (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::rNull),
      modelnb (1),
      atomCounter (1),
      pdbType (Pdbstream::PDB)
  {
    Pdbstream::init ();
    atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
    residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
  }


  oPdbstream::~oPdbstream () 
  { 
    if (atomCounter != 1)
      close ();
    delete atomset; 
  }
  
  
  void
  oPdbstream::setAtomSet (const AtomSet& as)
  {
    delete this->atomset;
    this->atomset = as.clone ();
  }

  
  void
  oPdbstream::setPDBType (unsigned int type)
  {
    pdbType = type;
    if (Pdbstream::AMBER == type)
      {
	atomTypeParseTable = Pdbstream::amberAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::amberResidueTypeParseTable;
      }
    else
      {
	atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
      }	
  }
  

  void
  oPdbstream::open () 
  { 

  }
  

  void
  oPdbstream::close () 
  {
    this->end ();
    this->header.clear ();
  }


  void
  oPdbstream::clear () 
  {
    this->ostream::clear ();
    this->header_written = false;
    this->rtype = ResidueType::rNull;
    ResId id;
    this->rid = id;
    this->modelnb = 1;
    this->atomCounter = 1;
  }


  void
  oPdbstream::_write_header ()
  {
    if (false == this->header_written)
    {
      this->header_written = true;
      *this << this->header;
    }
  }


  void
  oPdbstream::writeRecord (const string& name, const string& text)
  {
    this->_write_header ();

    string line;
    string::size_type recbeg, reclen, linelen, linebeg, lineend, textlen;
    int continuation = 0;

    // -- preformat record

    string rectype = Pdbstream::trim (name);
    rectype.resize (8, ' ');


    // -- write multiline record keeping original line wrapping when possible

    linebeg = recbeg = 0;
    textlen = text.size ();
    reclen = Pdbstream::LINELENGTH - 10;

    do // wrap using given newlines
    {
      lineend = text.find_first_of ("\n\r\f", linebeg);
      line = text.substr (linebeg, lineend - linebeg);
      recbeg = 0;
      linelen = line.size ();
      
      do // wrap into LINELENGTH columns
      {
	*this << rectype;

	if (++continuation > 1)
	{
	  // continuation for line 2 and onward: 
	  // space is added at column 11 before line text
	  this->setf (ios::right, ios::adjustfield);
	  this->width (2);
	  *this << continuation;
	  if (line[recbeg] != ' ') 
	    *this << ' ';
	  reclen = Pdbstream::LINELENGTH - 11;
	}
	else
	  *this << "  ";

	this->setf (ios::left, ios::adjustfield);
	this->width (reclen);
	*this << line.substr (recbeg, reclen) << endl;
	recbeg += reclen;
      }
      while (recbeg < linelen);

      linebeg = lineend + 1;
    }
    while (string::npos != lineend && linebeg < textlen);

  }


  void
  oPdbstream::writeRemark (const string& text, int k)
  {
    this->_write_header ();

    string line;
    string::size_type recbeg, reclen, linelen, linebeg, lineend, textlen;
    ostringstream rectype_oss;

    rectype_oss << "REMARK ";
    rectype_oss.setf (ios::right, ios::adjustfield);
    rectype_oss.width (3);
    rectype_oss << (k > 999 ? 999 : k) << ' ';

    reclen = Pdbstream::LINELENGTH - rectype_oss.str ().size ();
    
    // -- first remark line is blank

    *this << rectype_oss.str ();
    this->width (reclen);
    *this << ' ' << endl;


    // -- write multiline remark keeping original line wrapping when possible
    
    linebeg = recbeg = 0;
    textlen = text.size ();

    do // wrap using given newlines
    {
      lineend = text.find_first_of ("\n\r\f", linebeg);
      line = text.substr (linebeg, lineend - linebeg);
      recbeg = 0;
      linelen = line.size ();
      
      do // wrap into LINELENGTH columns
      {
	*this << rectype_oss.str ();
	this->setf (ios::left, ios::adjustfield);
	this->width (reclen);
	*this << line.substr (recbeg, reclen) << endl;
	recbeg += reclen;
      }
      while (recbeg < linelen);

      linebeg = lineend + 1;
    }
    while (string::npos != lineend && linebeg < textlen);
  }




  void
  oPdbstream::startModel () 
  {
    this->_write_header ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "MODEL";
    setf (ios::right, ios::adjustfield);
    *this << setw (8) << modelnb++;
    setf (ios::right, ios::adjustfield);
    pad (66);
    *this << endl;
  }

  
  void
  oPdbstream::endModel () 
  {
    this->_write_header ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "ENDMDL";
    pad (74);
    *this << endl;
  }


  void
  oPdbstream::ter () 
  {
    this->_write_header ();

    if (Pdbstream::PDB == pdbType)
      {
	setf (ios::left, ios::adjustfield);
	*this << setw (6) << "TER";
	setf (ios::right, ios::adjustfield);
	*this << setw (5) << atomCounter++;
	*this << "      ";  // EMPTY SPACE.
	setf (ios::right, ios::adjustfield);
	*this << setw (3) << residueTypeParseTable->toString (rtype);
	*this << ' ';
	*this << this->rid.getChainId ();
	setf (ios::right, ios::adjustfield);
	*this << setw (4) << this->rid.getResNo ();
	*this << this->rid.getInsertionCode ();
	pad (53);
	*this << endl;
      }
  }


  void
  oPdbstream::end () 
  {
    this->_write_header ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "END";
    pad (74);
    *this << endl;
  }

  
  void
  oPdbstream::pad (int i) 
  {
    this->fill (' ');
    this->width (i);
    *this << ' ';
  }


  void
  oPdbstream::write (const Atom& at)
  {
    this->_write_header ();

    string type;

    setf (ios::left, ios::adjustfield);
    if (rtype->isUnknown ())
      *this << setw (6) << "HETATM";
    else
      *this << setw (6) << "ATOM";
    setf (ios::right, ios::adjustfield);
    *this << setw (5) << atomCounter++;

    *this << ' ';

    setf (ios::left, ios::adjustfield);
    
    type = atomTypeParseTable->toString (at.getType ());
    if (isdigit (type[0]) || 4 == type.size ())
      *this << setw (4);
    else 
      *this << ' ' << setw (3);
    *this << type << ' ';  // ALTLOC
    
    setf (ios::right, ios::adjustfield);
    *this << setw (3) << residueTypeParseTable->toString (rtype);

    *this << ' ';

    *this << this->rid.getChainId ();

    setf (ios::right, ios::adjustfield);
    *this << setw (4) << this->rid.getResNo ();
    
    *this << this->rid.getInsertionCode ();

    *this << "   ";  // EMPTY SPACE!

    setf (ios::right, ios::adjustfield);
    setf (ios::fixed, ios::floatfield);
    precision (3);
    *this << setw (8) << at.getX ();
    *this << setw (8) << at.getY ();
    *this << setw (8) << at.getZ ();

    if (Pdbstream::PDB == pdbType)
      {
	*this << "  1.00  0.00";  // DUMMY VALUES
	pad (14);
      }
    else
      pad (26);

    if (atomCounter > 99999)
      atomCounter = 1;
  }


  void
  oPdbstream::write (const Residue& r)
  {
    this->_write_header ();

    Residue::const_iterator it;

    setResidueType (r.getType ());
    setResId (r.getResId ());

    for (it = r.begin (*atomset); it != r.end (); ++it)
      {
	*this << *it << endl;
      }
  }
  
}
