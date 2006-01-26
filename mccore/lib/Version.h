//                              -*- Mode: C++ -*- 
// Version.h
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.5 $
// $Id: Version.h,v 1.5 2006-01-26 21:19:55 thibaup Exp $
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
   * @short Library version manipulation <major>.<minor>.<revision>
   * 
   * @author Philippe Thibault <philippe.thibault@umontreal.ca>
   */
  class Version 
  {
    /**
     * Major version number: <major>.<minor>.<revision>
     */
    short int major_no;

    /**
     * Minor version number: <major>.<minor>.<revision>
     */
    short int minor_no;

    /**
     * Revision version number: <major>.<minor>.<revision>
     */
    short int revision_no;

    /**
     * CPU architecture string.
     */
    string cpu;

    /**
     * Vendor string.
     */
    string vendor;

    /**
     * Operating system name string.
     */
    string os;

    /**
     * Building timestamp.
     */
    string timestamp;
    
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Version ();

    Version (const Version& v);

    /**
     * Destructs the object.
     */
    ~Version () { }

    // OPERATORS ------------------------------------------------------------

    Version& operator= (const Version& v);

    bool operator== (const Version& v) const;

    bool operator!= (const Version& v) const
    {
      return !this->operator== (v);
    }

    // ACCESS ---------------------------------------------------------------

    int getMajor () const
    {
      return this->major_no;
    }

    int getMinor () const
    {
      return this->minor_no;
    }

    int getRevision () const
    {
      return this->revision_no;
    }

    // METHODS --------------------------------------------------------------

    string toString () const;

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
