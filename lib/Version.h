// Version.h
// Copyright © 2005, 2014 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
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
   * @short Library version  <major>.<minor>.<revision>
   */
  class Version 
  {
  protected:

    std::string package_name;

    short int major_no;

    short int minor_no;

    short int revision_no;

    string cpu;

    string vendor;

    string os;

    string timestamp;


    /**
     * Initialize the object specifying all parameters ( for subclasses )
     */
    Version (const std::string& astrPackageName,
             const std::string& astrPackageVersion,
             const std::string& astrCPU,
             const std::string& astrOS,
             const std::string& astrDate,
             const std::string& astrTime);

  public:

    // LIFECYCLE ------------------------------------------------------------

    Version ();

    Version (const Version& v);

    Version (const string& strv);

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
