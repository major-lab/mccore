//                              -*- Mode: C++ -*- 
// Pdbstream.cc
// Copyright © 1999, 2000-01, 03 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : 
// $Revision: 1.34 $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <iomanip>
#include <cctype>
#include <unistd.h>
#include <cstdio>

#include "Pdbstream.h"
#include "Atom.h"
#include "ResId.h"
#include "AtomType.h"
#include "ResidueType.h"
#include "Residue.h"
#include "Model.h"


namespace mccore {

  const int iPdbstream::LINELENGTH = 80;
  const int oPdbstream::LINELENGTH = 80;

  
  // LIFECYCLE -----------------------------------------------------------------

  iPdbstream::iPdbstream ()
    : istream (cin.rdbuf ()),
      rtype (0),
      rid (0),
      ratom (0),
      modelNb (1),
      eomFlag (false)
  {
  }
  
  
  iPdbstream::iPdbstream (streambuf* sb)
    : istream (sb),
      rtype (0),
      rid (0),
      ratom (0),
      modelNb (1),
      eomFlag (false)
  {
  }
  
  iPdbstream::~iPdbstream ()
  {
    if (rid) delete rid;
    if (ratom) delete ratom;
  }


  // OPERATORS -----------------------------------------------------------------

  // ACCESS --------------------------------------------------------------------


  const PdbFileHeader& iPdbstream::getHeader () 
  { 
    if (!ratom) cacheAtom ();
    return header; 
  }


  // METHODS -------------------------------------------------------------------
  

  iPdbstream&
  iPdbstream::getline (char *buffer, unsigned int sz)
  {
    int c;
    
    while (sz > 1 && (c = get ()) != EOF && c != '\n' && c != '\r')
      {
	*buffer++ = c;
	--sz;
      }
    *buffer = '\0';
    return *this;
  }
  

  void iPdbstream::open () 
  { 
    header = PdbFileHeader ();
    rtype = 0;
    if (rid) delete rid;
    rid = 0;
    if (ratom) delete ratom;
    ratom = 0;
    modelNb = 1;
    eomFlag = false;
  }


  void iPdbstream::close () 
  { 
    header = PdbFileHeader ();
    rtype = 0;
    if (rid) delete rid;
    rid = 0;
    if (ratom) delete ratom;
    ratom = 0;
    modelNb = 1;
    eomFlag = true;
  }


  Atom*
  iPdbstream::cacheAtom ()
  {    
    char line[LINELENGTH+2];
    char tag[7]; tag[6] = '\0';
    int length, taglength;
    char field[LINELENGTH];
    char* fieldp;

    // Cleanup any previous read:
    rtype = 0;
    if (rid) delete rid;
    rid = 0;
    if (ratom) delete ratom;
    ratom = 0;

    while ((getline (line, LINELENGTH+2)) > 0) {
      length = min ((int)strlen (line), LINELENGTH);
      taglength = min ((int)strlen (line), 6);
      strncpy (tag, line, 6);

      if (length<LINELENGTH) {
	int i;
	for (i=length; i<LINELENGTH; ++i) { line[i] = ' '; }
      }
      
      if (strcmp (tag, "HEADER") == 0) {
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+10, 40));
	header.setClassification (fieldp);
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+50, 9));
	header.setDate (fieldp);
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+62, 4));
	header.setPdbId (fieldp);
      } 

      if (strcmp (tag, "TITLE ") == 0) {
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+10, 60));
	header.setTitle (header.getTitle () + " " + string (fieldp));
      }

      if (strcmp (tag, "COMPND") == 0) {
      }

      if (strcmp (tag, "EXPDTA") == 0) {
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+10, 60));
	header.setMethod (header.getMethod () + " " + string (fieldp));

      }
      
      if (strcmp (tag, "REMARK") == 0 && 
	  line[9] == '2' &&
	  strncmp (line+11, "RESOLUTION.", 11) == 0 &&
	  !strncmp (line+11, "RESOLUTION. NOT APPLICABLE.", 27) == 0) {
	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+22, 5));
	header.setResolution (atof (fieldp));	
      }

      if (strcmp (tag, "MODEL ") == 0) {
	// The eomFlag is reset to false o
      }

      if (strcmp (tag, "ENDMDL") == 0) {
	modelNb++;
	eomFlag = true;
      }

      if (strcmp (tag, "TER   ") == 0) {
      }

      if (strcmp (tag, "END   ") == 0) {
	eomFlag = true;
      }

      if (strcmp (tag, "ATOM  ") == 0 || strcmp (tag, "HETATM") == 0) {
	float x, y, z;
	const AtomType *at;

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+30, 8));
	x = atof (field);

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+38, 8));
	y = atof (fieldp);

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+46, 8));
	z = atof (fieldp);

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+12, 4));
	at = AtomType::parseType (fieldp);

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+17, 3));
	rtype = ResidueType::parseType (fieldp);

	fieldp = trim (strncpy ((char*)memset (field, 0, LINELENGTH), line+22, 4));
	rid = new ResId (line[21], atoi (fieldp), line[26]);

	ratom = new Atom (x, y, z, at);

	return ratom;
      }
    }
    return ratom;
  }


  char* iPdbstream::trim (char* cp) 
  {
    char *a = cp;
    char *b = cp + strlen(cp)-1;
    
    while (b!=a && *b == ' ') b--;
    *(++b) = '\0';
    while (a!=b && *a == ' ') a++;
    return a;
  }


  // I/O -----------------------------------------------------------------------
  
  
  iPdbstream& 
  iPdbstream::operator>> (Atom &at)
  {
    // Cache an atom if needed.
    if (!ratom) cacheAtom (); 
    // No atom was found, return.
    if (!ratom) return *this;

    eomFlag = false;

    // Copy the return value.
    at = *ratom;
    
    // Cache another atom in order to detect endfiles.
    cacheAtom ();
    
    return *this;
  }
  

  iPdbstream& 
  iPdbstream::operator>> (Residue &r)
  {
    // Cache an atom if needed.
    if (!ratom) cacheAtom (); 
    // No atom was found, return.
    if (!ratom) return *this;
    
    eomFlag = false;
    
    ResId previd = *rid;

    r.clear ();
    r.setType (rtype);
    r.setResId (*rid);
    r.insert (*ratom);

    cacheAtom ();
    while (!eom () && (rid == 0 || *rid == previd)) {
      // Insert the atom.
      previd = *rid;
      r.insert (*ratom);      
      
      // Cache another atom in order to detect endfiles.
      cacheAtom ();
    }

    // Post reading processing
    if (r.size () > 0) {
      // Fix type.
      if (r.getType ()->isNucleicAcid ()) {
	if (r.contains (AtomType::aO2p)) {
	  if (r.getType () == ResidueType::rDA) r.setType (ResidueType::rRA);
	  else if (r.getType () == ResidueType::rDC) r.setType (ResidueType::rRC);
	  else if (r.getType () == ResidueType::rDG) r.setType (ResidueType::rRG);
	  else if (r.getType () == ResidueType::rDT) r.setType (ResidueType::rRU);
	} else {
	  if (r.getType () == ResidueType::rRA) r.setType (ResidueType::rDA);
	  else if (r.getType () == ResidueType::rRC) r.setType (ResidueType::rDC);
	  else if (r.getType () == ResidueType::rRG) r.setType (ResidueType::rDG);
	  else if (r.getType () == ResidueType::rRU) r.setType (ResidueType::rDT);
	}
      }

      // Finalize
      r.finalize ();
    }

    return *this;
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
      n (1)
  { 
  }
  

  oPdbstream::oPdbstream (streambuf* sb)
    : ostream (sb),
      header (),
      headerdone (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::parseType ("UNK")),
      rid (new ResId ()),
      modelnb (1),
      n (1)
  { 
  }

  oPdbstream::oPdbstream (ostream &os)
    : ostream (os.rdbuf ()),
      header (),
      headerdone (false),
      atomset (new AtomSetNot (new AtomSetOr (new AtomSetLP (), new AtomSetPSE ()))),
      rtype (ResidueType::parseType ("UNK")),
      rid (new ResId ()),
      modelnb (1),
      n (1)
  { 
  }

  oPdbstream::~oPdbstream () 
  { 
    if (n != 1) close ();

    if (rid) delete rid;
    delete atomset; 
  }
  
  
  // OPERATORS -----------------------------------------------------------------


  // ACCESS --------------------------------------------------------------------


  // METHODS -------------------------------------------------------------------


  void oPdbstream::open () 
  { 
    header = PdbFileHeader ();
    headerdone = false;
    rtype = 0;
    if (rid) delete rid;
    rid = new ResId ();
    modelnb = 1;
    n = 1;
  }
  
  void oPdbstream::close () 
  {
    end ();

    header = PdbFileHeader ();
    headerdone = false;
    rtype = 0;
    if (rid) delete rid;
    rid = new ResId ();
    modelnb = 1;
    n = 1;
  }

  void oPdbstream::writeHeader ()
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

  void oPdbstream::writeRemark (int k, const char* rem)
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

  void oPdbstream::startModel () 
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

  
  void oPdbstream::endModel () 
  {
    if (!headerdone) writeHeader ();

    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "ENDMDL";
    pad (74);
    *this << endl;
  }


  void oPdbstream::ter () 
  {
    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "TER";
    setf (ios::right, ios::adjustfield);
    *this << setw (5) << n++;
    *this << "      ";  // EMPTY SPACE.
    setf (ios::right, ios::adjustfield);
    *this << setw (3) << rtype->toPdbString ();
    *this << ' ';
    *this << rid->getChainId ();
    setf (ios::right, ios::adjustfield);
    *this << setw (4) << rid->getResNo ();
    *this << rid->getInsertionCode ();
    pad (53);
    *this << endl;
  }


  void oPdbstream::putconect (const Model &model)
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

  void oPdbstream::end () 
  {
    setf (ios::left, ios::adjustfield);
    *this << setw (6) << "END";
    pad (74);
    *this << endl;
  }

  
  void oPdbstream::pad (int i) 
  {
    while (i-->0) {
      *this << ' ';
    }
  }


  oPdbstream& 
  oPdbstream::operator<< (const Atom& at)
  {
    if (!headerdone) writeHeader ();

    setf (ios::left, ios::adjustfield);
    if (rtype->isUnknown ())
      *this << setw (6) << "HETATM";
    else
      *this << setw (6) << "ATOM";
    setf (ios::right, ios::adjustfield);
    *this << setw (5) << n++;

    *this << ' ';

    setf (ios::left, ios::adjustfield);
    if (isdigit (((const char*)*at.getType ())[0]) || strlen ((const char*)*at.getType ()) == 4)
      *this << setw (4) << *at.getType ();
    else 
      *this << ' ' << setw (3) << *at.getType ();
	
    *this << ' ';  // ALTLOC
    
    setf (ios::right, ios::adjustfield);
    *this << setw (3) << rtype->toPdbString ();

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

    *this << "  1.00  0.00";  // DUMMY VALUES

    pad (14);

    at.setSerialNo (n);

    if (n>99999) n=1;


    return *this;
  }


  oPdbstream& 
  oPdbstream::operator<< (const Residue& r)
  {
    if (!headerdone) writeHeader ();

    setResidueType (r.getType ());
    setResId (r.getResId ());
    
    for (Residue::const_iterator i=r.begin (atomset->clone ()); i!=r.end (); ++i) {
    //    for (Residue::const_iterator i=r.begin (); i!=r.end (); ++i) {
      *this << *i << endl;
    }

    return *this;
  }  
}
