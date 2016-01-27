//                              -*- Mode: C++ -*- 
// Sequence.h
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr 25 10:12:06 2003
// $Revision: 1.5 $
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


#ifndef _mccore_Sequence_h_
#define _mccore_Sequence_h_

#include <iostream>
#include <vector>

#include "ResId.h"

using namespace std;



namespace mccore 
{
  class iBinstream;
  class iFastastream;
  class oBinstream;
  class oFastastream;
  class iGenbankstream;


  
  /**
   * @short A sequence of residues in its simplest, fastest form.
   *
   * Well maybe not the smallest size since we are using a vector instead of
   * a table but, hey!, operations might be simpler!
   *
   * @author Patrick Gendron (<a href="gendrop.iro.umontreal.ca">gendrop.iro.umontreal.ca</a>)
   * @version $Id: Sequence.h,v 1.5 2005-01-03 23:06:18 larosem Exp $
   */
  class Sequence : public vector< char >
  {
    /**
     * The Id of the sequence.
     */
    char* uniqueId;

    /**
     * The description of the sequence.
     */
    char* description;
    
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Sequence ();

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    Sequence (const Sequence &other);

    /**
     * Clones the object.
     * @return a copy of itself.
     */
    virtual Sequence* clone () const {
      return new Sequence (*this);
    }
       
    /**
     * Destroys the object.
     */
    virtual ~Sequence ();

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual Sequence& operator= (const Sequence &other);

    // ACCESS ---------------------------------------------------------------

    /**
     * Produces the one character residue type at position i. 
     */
    virtual char operator[] (unsigned int index) const;
    
    /**
     * Produces the unique residue identifier for residue at position i.
     */
    virtual ResId getResId (unsigned int index) const;

    /**
     * Returns the uniqueId of this sequence.
     */
    const char* getUniqueIdentifier () const { return uniqueId; }
    
    /**
     * Returns the description of this sequence.
     */
    const char* getDescription () const { return description; }

    // METHODS --------------------------------------------------------------

    virtual unsigned int size () const;
    
    //    Sequence shuffle ();
    //    Sequence reverse ();

    /**
     * Translates the sequence contained between the two iterators f
     * (begin) and b (end) into a sequence of amino acids.
     * @param f an iterator on the first residue.
     * @param b an iterator after the last residue.
     * @return a protein sequence.
     */
    Sequence translate (const Sequence::iterator &f, const Sequence::iterator &b);
    //  Sequence sub ();
    
    Sequence complement (const Sequence::iterator &f, const Sequence::iterator &b);

    // I/O  -----------------------------------------------------------------

    iBinstream& read (iBinstream &ibs);
    oBinstream& write (oBinstream &obs) const;

    virtual istream& read (istream &is);
    virtual ostream& write (ostream &os) const;

    iFastastream& read (iFastastream &is);
    oFastastream& write (oFastastream &os) const;

    iGenbankstream& read (iGenbankstream &is);
  };
  
  /**
   * Reads a sequence from a fasta stream.
   * @param ips the input fasta stream.
   * @param seq the pointer to the new sequence.
   * @return the used input stream.
   */
  iFastastream& operator>> (iFastastream &is, Sequence &seq);
  
  /**
   * Outputs the sequence to the fasta stream.
   * @param obs the output stream.
   * @param seq the Sequence.
   * @return the output stream used.
   */
  oFastastream& operator<< (oFastastream &os, const Sequence &seq);
  
  /**
   * Reads a sequence from a genbank stream.
   * @param ips the input genbank stream.
   * @param seq the pointer to the new sequence.
   * @return the used input stream.
   */
  iGenbankstream& operator>> (iGenbankstream &is, Sequence &seq);
  
}



namespace std
{
  
  /**
   * Reads a sequence from a raw stream.
   * @param ips the input raw stream.
   * @param seq the pointer to the new sequence.
   * @return the used input stream.
   */
  istream& operator>> (istream &is, mccore::Sequence &seq);

  /**
   * Outputs the sequence to the raw stream.
   * @param obs the output stream.
   * @param seq the Sequence.
   * @return the output stream used.
   */
  ostream& operator<< (ostream &os, const mccore::Sequence &seq);
  
}

#endif
