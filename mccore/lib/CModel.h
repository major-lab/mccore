//                              -*- Mode: C++ -*- 
// CModel.h
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Fri Oct  6 08:21:55 2000
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:51 2000
// Update Count     : 1
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

  // I/O  -----------------------------------------------------------------
};

//  ostream& operator<< (ostream &os, const CModel &obj);
//  istream& operator>> (istream &is, CModel &obj);

//  iBinstream& operator>> (iBinstream &ibs, CModel &obj);
//  oBinstream& operator<< (oBinstream &obs, const CModel &obj);

iPdbstream& operator>> (iPdbstream &ips, CModel &obj);
oPdbstream& operator<< (oPdbstream &ops, const CModel &obj);

#endif
