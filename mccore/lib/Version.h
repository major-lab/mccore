//                              -*- Mode: C++ -*- 
// Version.h
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.1 $
// $Id: Version.h,v 1.1 2005-05-20 15:28:46 thibaup Exp $
// 


#ifndef _mccore_Version_h_
#define _mccore_Version_h_


#include <iostream>
#include <string>


using namespace std;


namespace mccore
{
  /**
   * @short Library version
   * 
   * @author Philippe Thibault <philippe.thibault@umontreal.ca>
   */
  class Version 
  {

  public:

    /**
     * Version string "<major>.<minor>"
     */
    static const string version;

    /**
     * Machine architecture string.
     */
    static const string machine;

    /**
     * Kernel version string.
     */
    static const string kernel;

    /**
     * Operating system name string.
     */
    static const string osname;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Version () { }

    /**
     * Destructs the object.
     */
    ~Version () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to a stream.
     * @param os The stream.
     * @return The written stream.
     */
    ostream& write (ostream& os) const;

  };

}

namespace std
{
  ostream& operator<< (ostream &os, const mccore::Version& obj);
}

#endif
