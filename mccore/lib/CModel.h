//                              -*- Mode: C++ -*- 
// CModel.h
// Copyright © 2000, 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Jan 22 15:13:41 2001
// Update Count     : 4
// Status           : Unknown.
// 


#ifndef _CModel_h_
#define _CModel_h_


#include <list.h>

#include "CResidue.h"


class iPdbstream;
class oPdbstream;
class iBinstream;
class oBinstream;



/**
 * @short Description
 * 
 * Long Description
 *
 * @author Martin Larose
 */
class CModel : public list< CResidue >
{
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  CModel () : list< CResidue > () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CModel (const CModel &right) : list< CResidue > (right) { }

  /**
   * Destructs the object.
   */
  ~CModel () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  CModel& operator= (const CModel &right);

  /**
   * Gets the model reference at nth position.
   * @param nth the position of the reference to get.
   * @return the nth reference.
   */
  reference operator[] (unsigned int nth);

  /**
   * Gets the model const_reference at nth position.
   * @param nth the position of the const_reference to get.
   * @return the nth const_reference.
   */
  const_reference operator[] (unsigned int nth) const;

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  /**
   * Creates a new model with validated residues.
   * @return the new model.
   */
  CModel Validate () const;

  /**
   * Creates a new model with all the optional atoms removed.
   * @return the new model.
   */
  CModel RemoveOptionals () const;

  /**
   * Creates a new model with atoms sorted in residues.
   * @return the new model.
   */
  CModel SortAtoms () const;

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  CResidue::iterator find (const char *str);

  /**
   * Finds an atom given it's text representation of the form residue:atom.
   * Returns a empty iterator if it is not found.
   * @param str the text representation.
   * @return the residue iterator over the atom.
   */
  CResidue::const_iterator find (const char *str) const;

  /**
   * Finds a residue given it's residue id.  Returns a CModel iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a CModel iterator.
   */
  CModel::iterator find (const CResId &id);

  /**
   * Finds a residue given it's residue id.  Returns a CModel iterator
   * pointing to the residue or the end of the container if the residue was
   * not found.
   * @param id the residue id.
   * @return a CModel iterator.
   */
  CModel::const_iterator find (const CResId &id) const;

  // I/O  -----------------------------------------------------------------
};



bool operator< (const CModel::iterator &left, const CModel::iterator &right);

iPdbstream& operator>> (iPdbstream &ips, CModel &obj);
oPdbstream& operator<< (oPdbstream &ops, const CModel &obj);

iBinstream& operator>> (iBinstream &ibs, CModel &obj);
oBinstream& operator<< (oBinstream &obs, const CModel &obj);

#endif
