//                              -*- Mode: C++ -*- 
// PdbFileHeader.h
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 16:01:52 2003
// $Revision: 1.9 $
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


#ifndef _mccore_PdbFileHeader_h_
#define _mccore_PdbFileHeader_h_

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <utility>


using namespace std;


namespace mccore
{
  class oPdbstream;
  class oBinstream;
  class iPdbstream;
  class iBinstream;

  /**
   * @short Representation of a PDB file header in memory.
   * 
   * Representation of a PDB file header in memory. The following records are handled:
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
   *                                              records.	
   * 11 - 70        String          title          Title of the experiment.
   *
   *
   * EXPDTA
   * COLUMNS       DATA TYPE      FIELD         DEFINITION
   * -------------------------------------------------------------------------------
   *  1 -  6       Record name    "EXPDTA"
   *  9 - 10       Continuation   continuation  Allows concatenation of multiple
   *                                            records.
   * 11 - 70       SList          technique     The experimental technique(s) with
   *                                            optional comment describing the
   *                                            sample or experiment. Each technique
   *                                            is separaated by semi-colon.
   *
   * AUTHOR
   * COLUMNS       DATA TYPE      FIELD         DEFINITION
   * ----------------------------------------------------------------------------------
   * 1 -  6       Record name    "AUTHOR"
   *
   * 9 - 10       Continuation   continuation   Allows concatenation of multiple
   *                                            records.
   *
   * 11 - 70       List          authorList     List of the author names, separated
   *                                            by commas.
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
   * COLUMNS      DATA TYPE       FIELD          DEFINITION
   * ---------------------------------------------------------------------------------
   * 1 -  6      Record name     "REMARK"
   *
   * 8 - 10      Integer         remarkNum      Remark number. It is not an error
   *                                            for remark n to exist in an entry
   *                                            when remark n-1 does not.
   *
   * 12 - 70      LString         empty          Left as white space in first line of
   *                                            each new remark.
   *
   * </pre>
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: PdbFileHeader.h,v 1.9 2006-11-15 19:44:50 larosem Exp $
   */
  class PdbFileHeader
  {
    /**
     * HEADER record: classification (40 characters limit).
     */
    string classification;

    /**
     * HEADER record: date (11 characters limit).
     */
    string date;

    /**
     * HEADER record: RCSB PDB code (4 characters limit).
     */
    string pdbId;

    /**
     * TITLE record (unlimited).
     */
    string title;

    /**
     * EXPDTA record: a list of "<name>,<comment>;" (unlimited).
     */
    map< string, string > methods;

    /**
     * AUTHOR record: a list of "<name>,"
     */
    list< string > authors;

    /**
     * Resolution value from a "REMARK 2" record.
     * Written only if [0,100[, else "NOT APPLICABLE" is written.
     * This is a partial handling of "REMARK 2", additional comment are ignored...
     */
    float resolution;

    /**
     * Remark lines. Written as "REMARK" remnum record.
     */
    list< pair< unsigned int, string > > remarks;
    
    /**
     * Unclassified remark lines (unlimited). Written as "REMARK 99" record.
     */
    list< string > unclassified;

  public:

    /**
     * Maximal length of any line
     */
    static const size_t linelength;

    /**
     * Official method name strings for EXPDTA record. 
     */
    static const string ElectronDiffraction;
    static const string FiberDiffraction;
    static const string FluorescenceTransfer;
    static const string NeutronDiffraction;
    static const string NMR;
    static const string TheoreticalModel;
    static const string XRayDiffraction;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     * @param reset if true then default content is assigned (default is true).
     */
    PdbFileHeader (bool reset = true);

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

    /**
     * Gets the classification string.
     * @return the fixed 40 columns classification string.
     */
    const string& getClassification () const 
    { 
      return classification; 
    }
    
    /**
     * Sets the classification string and resizes it to 40 columns.
     * @param s the new classification string.
     */
    void setClassification (const string &s);
  
    /**
     * Gets the date string.
     * @return the fixed 11 columns date string.
     */
    const string& getDate () const 
    { 
      return date; 
    }

    /**
     * Sets the date string to today.
     */
    void setDate ();

    /**
     * Sets the date string to a day.
     * @param day the day of the month, [1,31]
     * @param month the month of the year, [1,12]
     * @param year the year. 
     */
    void setDate (unsigned int day, unsigned int month, unsigned int year);

    /**
     * Sets the date string and resize it to 11 columns.
     * @param s the new date string.
     */
    void setDate (const string &s);

    /**
     * Gets the PDB code string.
     * @return the fixed 4 columns PDB code string.
     */
    const string& getPdbId () const 
    { 
      return pdbId; 
    }

    /**
     * Sets the PDB code string and resizes it to 4 columns.
     * @param s the new PDB code string.
     */
    void setPdbId (const string &s);

    /**
     * Gets the title text string.
     * @return the title text string.
     */
    const string& getTitle () const 
    { 
      return title; 
    }

    /**
     * Sets the title text string.
     * @param s the new title text string.
     */
    void setTitle (const string &s);


    /**
     * Gets the method list.
     * @return the name,comments mapping.
     */
    const map< string, string >& getMethods () const
    {
      return this->methods;
    }

    /**
     * Sets the method list.
     * @param mlist the new method list as a name,comments mapping.
     */
    void setMethods (const map< string, string >& mlist);

    /**
     * Gets the author list.
     * @return the author list.
     */
    const list< string >& getAuthors () const
    {
      return this->authors;
    }

    /**
     * Sets the author list.
     * @param alist the new author list.
     */
    void setAuthors (const list< string >& alist);

    /**
     * Gets the resolution value.
     * @return the resolution value.
     */
    float getResolution () const 
    { 
      return this->resolution; 
    }

    /**
     * Sets the resolution value.
     * @param f the new resolution value.
     */
    void setResolution (float f);

    /**
     * Gets the unclasified remark list.
     * @return the unclasified remark list.
     */
    const list< string >& getUnclassified () const
    {
      return this->unclassified;
    }

    /**
     * Sets the unclassified remark list.
     * @param ulist the new unclassified remark list.
     */
    void setUnclassified (const list< string >& ulist);
    
    /**
     * Gets the REMARK list.
     * @return the REMARK list.
     */
    list< pair< unsigned int, string > >& getRemarks () { return remarks; }

    /**
     * Gets the REMARK list.
     * @return the REMARK list.
     */
    const list< pair< unsigned int, string > >& getRemarks () const
    {
      return remarks;
    }

    /**
     * Sets the REMARK list.
     * @param remlist the new REMARK list.
     */
    void setRemarks (const list< pair< unsigned int, string > >& remlist);
    
    // METHODS --------------------------------------------------------------

    /**
     * Adds a new method entry with no comment.
     * @param n the method name.
     */ 
    void addMethod (const string& n);

    /**
     * Adds a new method entry with comments, or append a comment to
     * the already existing named method.
     * @param n the method name.
     * @param c the comment text.
     */
    void addMethod (const string& n, const string& c);

    /**
     * Adds a new author entry.
     * @param a the author name.
     */
    void addAuthor (const string& a);

    /**
     * Adds a new unclassified remark entry.
     * @param str the unclassified remark text.
     */
    void addUnclassified (const string &str);

    /**
     * Adds a new REMARK entry.
     * @param no the REMARK number.
     * @param str the REMARK text.
     */
    void addRemark (unsigned int no, const string &str);

    /**
     * Clears all content.
     * @param reset the reset to default flag: if true then default content is assigned.
     */
    void clear (bool reset = false);

    // I/O  -----------------------------------------------------------------

    /**
     * Writes content to an ouput stream. 
     * @param os the output stream.
     * @return the written stream.
     */
    ostream& write (ostream& os) const;

    /**
     * Writes content to a pdb stream. 
     * @param ops the output stream.
     * @return the written stream.
     */
    oPdbstream& write (oPdbstream& ops) const;

    /**
     * Writes content to a binary stream. 
     * @param ops the output stream.
     * @return the written stream.
     */
    oBinstream& write (oBinstream& obs) const;

    /**
     * Read and assign content from a pdb stream.
     * @param ips the input stream.
     * @return the read stream.
     */
    iPdbstream& read (iPdbstream& ips);

    /**
     * Read and assign content from a binary stream.
     * @param ips the input stream.
     * @return the read stream.
     */
    iBinstream& read (iBinstream& ibs);

  };

  /**
   * Outputs to a pdb stream. 
   * @param ops the output pdb stream.
   * @param obj the header records written.
   * @return the output pdb stream.
   */
  oPdbstream& operator<< (oPdbstream &ops, const PdbFileHeader& obj);

  /**
   * Outputs to a binary stream. 
   * @param ops the output binary stream.
   * @param obj the header records written.
   * @return the output binary stream.
   */
  oBinstream& operator<< (oBinstream &obs, const PdbFileHeader& obj);

  /**
   * Inputs from a pdb stream.
   * @param ips the input pdb stream.
   * @param obj the header records read
   * @return the input pdb stream.
   */
  iPdbstream& operator>> (iPdbstream& ips, PdbFileHeader& obj);

  /**
   * Inputs from a binary stream.
   * @param ips the input binary stream.
   * @param obj the header records read
   * @return the input binary stream.
   */
  iBinstream& operator>> (iBinstream& ibs, PdbFileHeader& obj);
}


namespace std
{
  
  /**
   * Outputs to a stream.
   * @param out the output stream.
   * @return the output stream used.
   */
  ostream &operator<< (ostream &out, const mccore::PdbFileHeader &h);

}

#endif
