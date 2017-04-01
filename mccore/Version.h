//                              -*- Mode: C++ -*- 
// Version.h
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.7 $
// $Id: Version.h,v 1.7 2006-10-11 17:35:37 thibaup Exp $
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
  protected:
	/**
	 * Name of the package being versioned
	 */
	std::string package_name;

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
    

    // LIFECYCLE

    /**
     * Initialize the object specifying all parameters ( for subclasses )
     */
    Version (
		const std::string& astrPackageName,
		const std::string& astrPackageVersion,
		const std::string& astrCPU,
		const std::string& astrOS,
		const std::string& astrDate,
		const std::string& astrTime);

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    Version ();

    Version (const Version& v);

    Version (const string& strv);

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

    bool equals (const Version& v) const;

    bool compatibleWith (const Version& v) const;

    string toString () const;

    string version () const;

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
