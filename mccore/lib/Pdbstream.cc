//                              -*- Mode: C++ -*- 
// Pdbstream.cc
// Copyright © 1999, 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.49 $
// $Id: Pdbstream.cc,v 1.49 2004-12-09 19:55:52 thibaup Exp $
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
  
  const unsigned int iPdbstream::LINELENGTH = 80;
  const int oPdbstream::LINELENGTH = 80;


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
  

  iPdbstream::iPdbstream ()
    : istream (cin.rdbuf ()),
      rtype (0),
      rid (0),
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
      rtype (0),
      rid (0),
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
    if (rid) delete rid;
    if (ratom) delete ratom;
  }


  const PdbFileHeader&
  iPdbstream::getHeader () 
  { 
    if (!ratom)
      cacheAtom ();
    return header; 
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
    header = PdbFileHeader ();
    rtype = 0;
    if (rid)
      delete rid;
    rid = 0;
    if (ratom)
      delete ratom;
    ratom = 0;
    modelNb = 1;
    eomFlag = false;
    altloc = ' ';
  }


  void
  iPdbstream::close () 
  { 
    header = PdbFileHeader ();
    rtype = 0;
    if (rid)
      delete rid;
    rid = 0;
    if (ratom)
      delete ratom;
    ratom = 0;
    modelNb = 1;
    eomFlag = true;
  }


  Atom*
  iPdbstream::cacheAtom ()
  {    
    string line;

    // Cleanup any previous read:
    rtype = 0;
    if (rid)
      delete rid;
    rid = 0;
    if (ratom)
      delete ratom;
    ratom = 0;
    
    while (! eof ())
    {
      string tag;
      string field;
      string copy;
	
      while ((std::getline (*this, line), line.length ()) == 0 && ! eof ());
      if (0 == line.length () && eof ())
	break;

      if (LINELENGTH > line.length ())
	line.resize (LINELENGTH, ' ');
	
      tag = line.substr (0, 6);
      if ("HEADER" == tag)
      {
	header.setClassification (trim (copy = line.substr (10, 40)));
	header.setDate (trim (copy = line.substr (50, 9)));
	header.setPdbId (trim (copy = line.substr (62, 4)));
      }
      else if ("TITLE" == tag)
      {
	header.setTitle (header.getTitle () + " " + trim (copy = line.substr (10, 60)));
      }
      else if ("COMPND" == tag)
      {
      }
      else if ("EXPDTA" == tag)
      {
	header.setMethod (header.getMethod () + " " + trim (copy = line.substr (10, 60)));
      }
      else if ("REMARK" == tag
	       && '2' == line[9]
	       && 0 == line.compare (11, 11, "RESOLUTION.")
	       && 0 != line.compare (11, 27, "RESOLUTION. NOT APPLICABLE."))
      {
	header.setResolution (atof (trim (copy = line.substr (22, 5)).c_str ()));
      }
      else if ("MODEL" == tag)
      {
	// The eomFlag is reset to false o
      }
      else if ("ENDMDL" == tag)
      {
	modelNb++;
	eomFlag = true;
      }
      else if ("TER   " == tag)
      {
	    
      }
      else if ("END   " == tag)
      {
	eomFlag = true;
      }
      else if ("ATOM  " == tag || "HETATM" == tag)
      {
	if (' ' == this->altloc || ' ' == line[16] || line[16] == this->altloc)
	{
	  float x, y, z;
	  const AtomType *at;

	  this->altloc = line[16];
	      
	  x = atof (trim (copy = line.substr (30, 8)).c_str ());
	  y = atof (trim (copy = line.substr (38, 8)).c_str ());	    
	  z = atof (trim (copy = line.substr (46, 8)).c_str ());

	  // 	    at = atomTypeParseTable->parseType (trim (copy = line.substr (12, 4)));
	  copy = line.substr (12, 4);
	  trim (copy);
	  at = atomTypeParseTable->parseType (copy);
	      
	  rtype = residueTypeParseTable->parseType (trim (copy = line.substr (17, 3)));
	      
	  rid = new ResId (line[21],
			   atoi (trim (copy = line.substr (22, 4)).c_str ()),
			   line[26]);
	      
	  ratom = new Atom (x, y, z, at);
	    
	  break;
	}
	else
	  gOut (3) << "Warning: ignoring atom with alternate location \'"
		   << line[16] << "\' at line:" << endl
		   << '[' << line << ']' << endl;
      }
    }
      
    
    return ratom;
  }


  string&
  iPdbstream::trim (string &str)
  {
    string::size_type pos;

    pos = str.find_first_not_of (" ");
    if (0 != pos)
      str.erase (0, pos);
    
    pos = str.find_last_not_of (" ");
    if (string::npos != pos)
      str.erase (pos + 1, str.length () - pos);
    return str;
  }


  // I/O -----------------------------------------------------------------------

  void
  iPdbstream::read (Atom &at)
  {
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
    // Cache an atom if needed.
    if (!ratom)
      cacheAtom (); 
    // No atom was found, return.
    if (ratom)
      {
	ResId previd = *rid;
	const ResidueType* prevtype = rtype;

	eomFlag = false;
	
	r.clear ();
	r.setType (rtype);
	r.setResId (*rid);
	r.insert (*ratom);
	
	cacheAtom ();

	/*
	  Inserts read atom for this residue.
	  Stops inserting in any of those three cases:
	    1) Either an END or ENDMDL tag was read or EOF was reached (eom() result).
	    2) ResID for current cached atom is different from last read atom.
	    3) Residue type for current cached atom is different from last read atom.
	*/
	while (!eom () && *rid == previd && rtype == prevtype)
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
      header (),
      headerdone (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::parseType ("UNK")),
      rid (new ResId ()),
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
      header (),
      headerdone (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::parseType ("UNK")),
      rid (new ResId ()),
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
      header (),
      headerdone (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::parseType ("UNK")),
      rid (new ResId ()),
      modelnb (1),
      atomCounter (1),
      pdbType (Pdbstream::PDB),
      atomTypeParseTable (Pdbstream::pdbAtomTypeParseTable),
      residueTypeParseTable (Pdbstream::pdbResidueTypeParseTable)
  { }


  oPdbstream::~oPdbstream () 
  { 
    if (atomCounter != 1)
      close ();
    if (rid)
      delete rid;
    delete atomset; 
  }
  
  
  void
  oPdbstream::setAtomSet (const AtomSet& as)
  {
    delete this->atomset;
    atomset = as.clone ();
  }

  
  void
  oPdbstream::setPDBType (unsigned int type)
  {
    pdbType = type;
    if (Pdbstream::AMBER == type)
      {
	headerdone = true;
	atomTypeParseTable = Pdbstream::amberAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::amberResidueTypeParseTable;
      }
    else
      {
	headerdone = false;
	atomTypeParseTable = Pdbstream::pdbAtomTypeParseTable;
	residueTypeParseTable = Pdbstream::pdbResidueTypeParseTable;
      }	
  }
  

  void
  oPdbstream::open () 
  { 
    header = PdbFileHeader ();
    headerdone = false;
    rtype = 0;
    if (rid) delete rid;
    rid = new ResId ();
    modelnb = 1;
    atomCounter = 1;
  }
  

  void
  oPdbstream::close () 
  {
    end ();

    header = PdbFileHeader ();
    headerdone = false;
    rtype = 0;
    if (rid) delete rid;
    rid = new ResId ();
    modelnb = 1;
    atomCounter = 1;
  }


  void
  oPdbstream::writeHeader ()
  {
    headerdone = true;

    char line[81];

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "HEADER";
    *this << "    ";
    
    setf (ios::left, ios::adjustfield);
    *this << setw (40) << header.getClassification ().c_str();

    *this << setw (9) << header.getDate ().c_str();
    *this << "   ";
    *this << setw (4) << header.getPdbId ().c_str();
    pad (14);
    *this << endl;

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "EXPDTA";
    setf (ios::right, ios::adjustfield);
    *this << "    " << "THEORETICAL MODEL";
    pad (53);
    *this << endl;
    
    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "AUTHOR";
    setf (ios::right, ios::adjustfield);
    gethostname (line, 80);
    *this << "    " << getenv ("LOGNAME") << '@' << line << endl;
   
    if (header.getTitle () != "") {
      *this << setw (6) << "TITLE";
      *this << "    ";
      *this << setw (60) << header.getTitle ().c_str();
      pad (10);
      *this << endl;
    }

    sprintf (line, "FILE GENERATED WITH %s %s", PACKAGE, VERSION);
    writeRemark (10, line);
  }


  void
  oPdbstream::writeRemark (int k, const char* rem)
  {
    if (!headerdone) writeHeader ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "REMARK";
    *this << " ";
    setf (ios::right, ios::adjustfield);
    *this << setw (3) << k;
    *this << " ";
    setf (ios::left, ios::adjustfield);
    *this << setw (69) << rem;
    *this << endl;
  }


  void
  oPdbstream::startModel () 
  {
    if (!headerdone) writeHeader ();

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
    if (!headerdone) writeHeader ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "ENDMDL";
    pad (74);
    *this << endl;
  }


  void
  oPdbstream::ter () 
  {
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
	*this << rid->getChainId ();
	setf (ios::right, ios::adjustfield);
	*this << setw (4) << rid->getResNo ();
	*this << rid->getInsertionCode ();
	pad (53);
	*this << endl;
      }
  }


  void
  oPdbstream::putconect (const Model &model)
  {
    Model::const_iterator cit1, cit2;
    
    for (cit2 = model.begin (), cit1 = cit2++;
	 cit2 != model.end ();
	 ++cit1, ++cit2)
      if ((cit1->getResId ().getChainId () == cit2->getResId ().getChainId ())
	  && (cit1->getResId ().getResNo () + 1 == cit2->getResId ().getResNo ()))
	{
	  Residue::const_iterator a, b;
	  
	  a = cit1->find (AtomType::aO3p);
	  b = cit2->find (AtomType::aP);
	  if (a != (*cit1).end () && b != (*cit2).end ())
	    {
	      setf (ios::left, ios::adjustfield);
	      *this << setw (6) << "CONECT";
	      setf (ios::right, ios::adjustfield);
	      *this << setw (5) << (*a).getSerialNo ()
		    << setw (5) << (*b).getSerialNo () << endl;
	    }
	}
  }


  void
  oPdbstream::end () 
  {
    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "END";
    pad (74);
    *this << endl;
  }

  
  void
  oPdbstream::pad (int i) 
  {
    while (i-->0) {
      *this << ' ';
    }
  }


  void
  oPdbstream::write (const Atom& at)
  {
    string type;
    
    if (! headerdone)
      writeHeader ();

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

    *this << rid->getChainId ();

    setf (ios::right, ios::adjustfield);
    *this << setw (4) << rid->getResNo ();
    
    *this << rid->getInsertionCode ();

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

    at.setSerialNo (atomCounter);

    if (atomCounter > 99999)
      atomCounter = 1;
  }


  void
  oPdbstream::write (const Residue& r)
  {
    Residue::const_iterator it;
    
    if (!headerdone)
      writeHeader ();

    setResidueType (r.getType ());
    setResId (r.getResId ());
    
    for (it = r.begin (*atomset); it != r.end (); ++it)
      *this << *it << endl;
  }
}
