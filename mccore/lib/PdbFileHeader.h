//                              -*- Mode: C++ -*- 
// PdbFileHeader.h
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 16:01:52 2003
// $Revision: 1.1 $
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


#ifndef _PdbFileHeader_h_
#define _PdbFileHeader_h_

#include <iostream>
#include <string>

using namespace std;

namespace mccore {

/**
 * @short Representation of a PDB file header in memory.
 * 
 * Representation of a PDB file header in memory.
 * <pre>
 *
 * HEADER 
 * COLUMNS        DATA TYPE       FIELD           DEFINITION
 * ----------------------------------------------------------------------------------
 *  1 -  6        Record name     "HEADER"    
 * 11 - 50        String(40)      classification  Classifies the molecule(s)
 * 51 - 59        Date            depDate         Deposition date.  This is the date
 *                                                the coordinates were received by
 *                                                the PDB    
 * 63 - 66        IDcode          idCode          This identifier is unique within PDB
 *
 * TITLE
 * COLUMNS        DATA TYPE       FIELD          DEFINITION
 * ----------------------------------------------------------------------------------
 * 1 -  6        Record name     "TITLE "	
 * 9 - 10        Continuation    continuation   Allows concatenation of multiple
 * records.	
 * 11 - 70        String          title          Title of the experiment.
 *
 * COMPND
 * COLUMNS        DATA TYPE         FIELD          DEFINITION
 * ----------------------------------------------------------------------------------
 * 1 -  6        Record name       "COMPND"
 * 9 - 10        Continuation      continuation   Allows concatenation of multiple
 *                                                records.
 * 11 - 70        Specification     compound       Description of the molecular
 *                list                             components.
 *
 * EXPDTA
 * COLUMNS       DATA TYPE      FIELD         DEFINITION
 * -------------------------------------------------------------------------------
 *  1 -  6       Record name    "EXPDTA"
 *  9 - 10       Continuation   continuation  Allows concatenation of multiple
 *                                            records.
 * 11 - 70       SList          technique     The experimental technique(s) with
 *                                            optional comment describing the
 *                                            sample or experiment.
 *
 *
 * REMARK 2
 * COLUMNS        DATA TYPE       FIELD               DEFINITION
 * --------------------------------------------------------------------------------
 *  1 -  6        Record name     "REMARK"
 * 10             LString(1)      "2"
 * 12 - 22        LString(11)     "RESOLUTION."
 * 23 - 27        Real(5.2)       resolution          Resolution.
 * 29 - 38        LString(10)     "ANGSTROMS."
 *
 * </pre>
 *
 * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>
 * @version $Id: PdbFileHeader.h,v 1.1 2003-04-03 21:55:55 gendrop Exp $
 *
 */
class PdbFileHeader
{
  /**
   * HEADER
   */
  string classification;
  string date;
  string pdbId;

  /**
   * TITLE
   */
  string title;

  /**
   * EXPDTA
   */
  string method;

  /**
   * REMARK 2
   */
  float resolution;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  PdbFileHeader () : resolution (0) { 
    setDate (); 
    pdbId = "0000"; 
    classification = "UNCLASSIFIED";
  }

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  PdbFileHeader (const PdbFileHeader &other);

  /**
   * Destroys the object.
   */
  ~PdbFileHeader () {}

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the other's content.
   * @param other the object to copy.
   * @return itself.
   */
  PdbFileHeader& operator= (const PdbFileHeader &other);

  // ACCESS ---------------------------------------------------------------

  const string& getClassification () const { return classification; }
  void setClassification (const string s) { classification = s; }
  
  const string& getDate () const { return date; }
  void setDate (const string s) { date = s; }

  /**
   * Set the date to today.
   */
  void setDate ();

  /**
   * Set the date to the given values.
   */
  void setDate (int day, int month, int year);

  const string& getPdbId () const { return pdbId; }
  void setPdbId (const string s) { pdbId = s; }
  
  const string& getTitle () const { return title; }
  void setTitle (const string s) { title = s; }
  
  const string& getMethod () const { return method; }
  void setMethod (const string s) { method = s; }
  
  float getResolution () const { return resolution; }
  void setResolution (float f) { resolution = f; }
    

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------

};
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const PdbFileHeader &h);


}

#endif
