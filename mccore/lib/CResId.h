//                              -*- Mode: C++ -*- 
// CResId.h
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Dec  4 15:40:55 2000
// Update Count     : 3
// Status           : Ok.
// 


#ifndef _CResId_h_
#define _CResId_h_


class ostream;
class iBinstream;
class oBinstream;



/**
 * @short Identification structure for residues.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class CResId
{
  /**
   * The residue number.
   */
  int no;
  
  /**
   * The residue chain id.
   */
  char chain;
  
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the structure.
   * @param n the residue number (default = -1).
   * @param c the residue chain id (default = ' ').
   */
  CResId (int n = -1, char c = ' ') : no (n), chain (c) { }

  /**
   * Initializes the structure with a text representation.
   * @param str the text representation.
   */
  CResId (const char *str);
  
  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CResId (const CResId &right)
    : no (right.no), chain (right.chain) { }

  /**
   * Destructs the object.
   */
  ~CResId () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  const CResId& operator= (const CResId &right);
  
  /**
   * Tests the equality between ids.
   * @param right the object to test.
   * @return the truth value.
   */
  bool operator== (const CResId &right) const
  { return chain == right.chain && no == right.no; }
  
  /**
   * Tests the difference between ids.
   * @param right the object to test.
   * @return the truth value.
   */
  bool operator!= (const CResId &right) const { return !operator== (right); }
  
  /**
   * Tests the partial order over ids.
   * @param right the object to test.
   * @return the truth value.
   */
  bool operator< (const CResId &right) const
  { return chain < right.chain || (chain == right.chain && no < right.no); }
  
  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the residue number.
   * @return the residue number.
   */
  int GetResNo () const { return no; }

  /**
   * Sets the residue number.
   * @param resno the new residue number.
   */
  void SetResNo (int resno) { no = resno; }

  /**
   * Gets the chain id.
   * @return the chain id.
   */
  char GetChainId () const { return chain; }

  /**
   * Sets the chain id.
   * @param chainid the new chain id.
   */
  void SetChainId (char chainid) { chain = chainid; }
  
  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------
};



/**
 * Outputs the residue id to the stream.
 * @param os the output stream.
 * @param obj the residue id.
 * @return the used output stream.
 */
ostream& operator<< (ostream &os, const CResId &obj);



/**
 * Inputs the residue id from the binary stream.
 * @param ibs the input binary stream.
 * @param obj the id to put data in.
 * @return the used input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, CResId &obj);



/**
 * Outputs the residue id to the binary stream.
 * @param obs the output binary stream.
 * @param obj the residue id.
 * @return the used output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const CResId &obj);

#endif
