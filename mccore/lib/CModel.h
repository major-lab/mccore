//                              -*- Mode: C++ -*- 
// CModel.h
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Dec  4 15:38:55 2000
// Update Count     : 3
// Status           : Unknown.
// 


#ifndef _CModel_h_
#define _CModel_h_


#include <vector.h>

#include "CResidue.h"


class iPdbstream;
class oPdbstream;



/**
 * @short Description
 * 
 * Long Description
 *
 * @author Martin Larose
 */
class CModel : public vector< CResidue >
{
public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.
   */
  CModel () : vector< CResidue > () { }

  /**
   * Initializes the object with the right's content.
   * @param right the object to copy.
   */
  CModel (const CModel &right) : vector< CResidue > (right) { }

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



iPdbstream& operator>> (iPdbstream &ips, CModel &obj);
oPdbstream& operator<< (oPdbstream &ops, const CModel &obj);

#endif
