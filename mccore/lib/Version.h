//                              -*- Mode: C++ -*- 
// Version.h
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.2 $
// $Id: Version.h,v 1.2 2005-07-18 20:12:30 thibaup Exp $
// 


#ifndef _mccore_Version_h_
#define _mccore_Version_h_


#include <iostream>
#include <string>


using namespace std;


namespace mccore
{
  class iBinstream;
  class oBinstream;

  /**
   * @short Library version manipulation
   * 
   * @author Philippe Thibault <philippe.thibault@umontreal.ca>
   */
  class Version 
  {
    /**
     * Current version string "<major>.<minor>"
     */
    string current_version;

    /**
     * Current CPU architecture string.
     */
    string current_cpu;

    /**
     * Current vendor string.
     */
    string current_vendor;

    /**
     * Current operating system name string.
     */
    string current_os;

    /**
     * Current building date.
     */
    string current_date;
    
  public:

    /**
     * Library version string "<major>.<minor>"
     */
    static const string version;

    /**
     * Library CPU architecture string.
     */
    static const string cpu;

    /**
     * Library vendor string.
     */
    static const string vendor;

    /**
     * Library operating system name string.
     */
    static const string os;

    /**
     * Library building date.
     */
    static const string date;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Version ();

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

    /**
     * Writes the object to a binary stream.
     * @param obs The stream.
     * @return The written stream.
     */
    oBinstream& write (oBinstream& obs) const;

    /**
     * Reads the object from a binary stream.
     * @param ibs The stream.
     * @return The read stream.
     */
    iBinstream& read (iBinstream& ibs);

  };

  /**
   * Writes the object to a binary stream.
   * @param obs The stream.
   * @param obj The object to write.
   * @return The written stream.
   */
  oBinstream& operator<< (oBinstream &obs, const Version& obj);

  /**
   * Reads the object from a binary stream.
   * @param ibs The stream.
   * @param obj The object to read.
   * @return The read stream.
   */
  iBinstream& operator>> (iBinstream &ibs, Version& obj);
}

namespace std
{
  /**
   * Writes the object to a stream.
   * @param obs The stream.
   * @param obj The object to write.
   * @return The written stream.
   */
  ostream& operator<< (ostream &os, const mccore::Version& obj);
}

#endif
