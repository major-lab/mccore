//                              -*- Mode: C++ -*- 
// ResId.h
// Copyright © 2003-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:45:21 2003
// $Revision: 1.14 $
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


#ifndef _mccore_ResId_h_
#define _mccore_ResId_h_

#include <iostream>
#include <cstdlib>

using namespace std;



namespace mccore
{
  class Exception;
  class iBinstream;
  class oBinstream;


  /**
   * @short A residue Id.
   *
   * An identification structure for residues.  When using an input
   * string, the following format is recognized:
   *
   * "(?:'(.)'|([^0-9]))?([0-9]+)"
   *
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: ResId.h,v 1.14 2005-03-10 22:58:57 larosem Exp $
   */
  class ResId
  {
    /**
     * The residue chain id.
     */
    char chain;
  
    /**
     * The residue number.
     */
    int no;
  
    /**
     * The residue insertion code.
     */
    char iCode;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ResId (int n = -1) 
      : chain (' '), no (n), iCode (' ') {}

    /**
     * Initializes the object.
     */
    ResId (char c, int n, char i = ' ') 
      : chain (c), no (n), iCode (i) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    ResId (const ResId &other) 
      : chain (other.chain), no (other.no), iCode (other.iCode) {}

    /**
     * Initializes the structure with a text representation.
     * @param str the text representation.
     */
    ResId (const char *str);
  
    /**
     * Destroys the object.
     */
    virtual ~ResId () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    ResId& operator= (const ResId &other);

    /**
     * Indicates whether some other resid is "equal to" this one.
     * @param obj the reference object with which to compare.
     * @param true if this object is the same as the obj argument;
     * false otherwise.
     */
    bool operator== (const ResId &other) const
    {
      return (chain == other.chain
	      && no == other.no
	      && iCode == other.iCode);
    }
  
    /**
     * Tests the difference between ids.
     * @param other the object to test.
     * @return the truth value.
     */
    bool operator!= (const ResId &other) const 
    { return !operator== (other); }

    /**
     * Tests the partial order over ids.
     * @param other the object to test.
     * @return the truth value.
     */
    bool operator< (const ResId &other) const
    {
      return (chain < other.chain
	      || (chain == other.chain && no < other.no)
	      || (chain == other.chain
		  && no == other.no
		  && iCode < other.iCode));
    }

    /**
     * Calculate an id equal to this with its residue number incremented.
     * @param offset the increment.
     * @return the increment id.
     */
    ResId operator+ (int offset) const
    {
      return ResId (chain, no + offset, iCode);
    }

    /**
     * Calculate an id equal to this with its residue number decremented.
     * @param offset the decrement.
     * @return the increment id.
     */
    ResId operator- (int offset) const
    {
      return ResId (chain, no - offset, iCode);
    }


    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the residue number.
     * @return the residue number.
     */
    int getResNo () const { return no; }
  
    /**
     * Sets the residue number.
     * @param resno the new residue number.
     */
    void setResNo (int resno) { no = resno; }
  
    /**
     * Gets the chain id.
     * @return the chain id.
     */
    char getChainId () const { return chain; }
  
    /**
     * Sets the chain id.
     * @param chainid the new chain id.
     */
    void setChainId (char chainid) { chain = chainid; }
  
    /**
     * Gets the insertion code.
     * @return the insertion code.
     */
    char getInsertionCode () const { return iCode; }
  
    /**
     * Sets the insertion code.
     * @param ic the new insertion code.
     */
    void setInsertionCode (char ic) { iCode = ic; }

    // METHODS --------------------------------------------------------------

    /**
     * Test whether the given ResId is adjacent to this.
     * @param id the ResId.
     * @return true if the given ResId is adjacent to this.
     */
    bool areContiguous (const ResId &id) const
    {
      return (chain == id.chain && 1 == abs (no - id.no));
    }

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the ResId to the output stream.
     * @param os the output stream.
     * @return the output stream.
     */
    virtual ostream& write (ostream &os) const;
    
  };

  /**
   * Outputs the residue id to the exception stream.
   * @param os the exception stream.
   * @param obj the residue id.
   * @return the used exception stream.
   */
  Exception& operator<< (Exception& ex, const ResId &resid);
  
  /**
   * Inputs the residue id from the binary stream.
   * @param ibs the input binary stream.
   * @param obj the id to put data in.
   * @return the used input binary stream.
   */
  iBinstream& operator>> (iBinstream &ibs, ResId &obj);
    
  /**
   * Outputs the residue id to the binary stream.
   * @param obs the output binary stream.
   * @param obj the residue id.
   * @return the used output binary stream.
   */
  oBinstream& operator<< (oBinstream &obs, const ResId &obj);

}


namespace std
{
  
  /**
   * Outputs the residue id to the stream.
   * @param os the output stream.
   * @param obj the residue id.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::ResId &obj);
  
  /**
   * Outputs the residue id to the stream.
   * @param os the output stream.
   * @param obj the residue id.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::ResId *obj);
  
}  

#endif
