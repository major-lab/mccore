//                              -*- Mode: C++ -*- 
// Version.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.8 $
// $Id: Version.cc,v 1.8 2006-10-11 17:35:37 thibaup Exp $
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

// cmake generated defines
#include "config.h"

#include <sstream>

#include "Binstream.h"
#include "Messagestream.h"
#include "Version.h"

namespace mccore
{

  Version::Version ()
    : package_name (PACKAGE_NAME),
      major_no (-1),
      minor_no (-1),
      revision_no (-1),
      cpu (VERSION_CPU),
      os (VERSION_OS)
  {
    istringstream iss (PACKAGE_VERSION_STRING);
    char dot;

    iss >> this->major_no >> dot >> this->minor_no >> dot >> this->revision_no;

    this->timestamp = __DATE__;
    this->timestamp += " ";
    this->timestamp += __TIME__;
  }

  Version::Version (
	const std::string& astrPackageName,
	const std::string& astrPackageVersion,
	const std::string& astrCPU,
	const std::string& astrOS,
	const std::string& astrDate,
	const std::string& astrTime)
    : package_name (astrPackageName),
      major_no (-1),
      minor_no (-1),
      revision_no (-1),
      cpu (astrCPU),
      os (astrOS)
  {
    istringstream iss (astrPackageVersion);
    char dot;

    iss >> this->major_no >> dot >> this->minor_no >> dot >> this->revision_no;

    this->timestamp = astrDate;
    this->timestamp += " ";
    this->timestamp += astrTime;
  }

  Version::Version (const string& strv)
    : package_name (PACKAGE_NAME),
      major_no (-1),
      minor_no (-1),
      revision_no (-1),
      cpu (VERSION_CPU),
      os (VERSION_OS)
  {
    istringstream iss;
    char dot;

    iss.exceptions (ios::failbit | ios::badbit);

    try
    {
      iss.str (strv);
      iss >> this->major_no >> dot 
	  >> this->minor_no >> dot 
	  >> this->revision_no;
    }
    catch (ios::failure& ioex)
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "failed to initialize version to \"" << strv << "\": " << ioex.what ();
      throw ex;
    }
  }


  Version::Version (const Version& v)
    : package_name (v.package_name),
      major_no (v.major_no),
      minor_no (v.minor_no),
      revision_no (v.revision_no),
      cpu (v.cpu),
      os (v.os),
      timestamp (v.timestamp)
  {

  }


  Version&
  Version::operator= (const Version& v)
  {
    if (this != &v)
    {
      this->package_name = v.package_name;
      this->major_no = v.major_no;
      this->minor_no = v.minor_no;
      this->revision_no = v.revision_no;
      this->cpu = v.cpu;
      this->os = v.os;
      this->timestamp = v.timestamp;
    }
    return *this;
  }


  bool
  Version::operator== (const Version& v) const
  {
    return 
      this->package_name == v.package_name &&
      this->major_no == v.major_no &&
      this->minor_no == v.minor_no &&
      this->revision_no == v.revision_no &&
      this->cpu == v.cpu &&
      this->os == v.os &&
      this->timestamp == v.timestamp;
  }


  bool 
  Version::equals (const Version& v) const
  {
    return 
      this->major_no == v.major_no && 
      this->minor_no == v.minor_no && 
      this->revision_no == v.revision_no;
  }


  bool
  Version::compatibleWith (const Version& v) const
  {
    return this->major_no == v.major_no && this->minor_no == v.minor_no;
  }


  string
  Version::toString () const
  {
    ostringstream oss;
    oss << this->package_name << " "
	<< this->major_no << "." << this->minor_no << "." << this->revision_no << " "
	<< this->cpu << " "
	<< this->os << " "
	<< this->timestamp;
    return oss.str ();
  }


  string
  Version::version () const
  {
    ostringstream oss;
    oss << this->major_no << "." << this->minor_no << "." << this->revision_no;
    return oss.str ();
  }


  ostream&
  Version::write (ostream& os) const
  {
    return os << this->toString ();
  }


  oBinstream&
  Version::write (oBinstream& obs) const
  {
    return obs << this->major_no << this->minor_no << this->revision_no
	       << this->cpu
	       << this->os
	       << this->timestamp;
  }


  iBinstream& 
  Version::read (iBinstream& ibs)
  {
    Version saved = *this;

    this->cpu = this->os = this->timestamp = "unread";
    this->major_no = this->minor_no = this->revision_no = -1;
    ibs >> this->major_no >> this->minor_no >> this->revision_no
	>> this->cpu 
	>> this->os
	>> this->timestamp;

    if (*this != saved)
      gErr (4) << "Warning: reading data created from package version: " << endl
	       << "\t" << *this << endl
	       << "using package version: "
	       << "\t" << saved << endl;

    return ibs;
  }


  oBinstream& 
  operator<< (oBinstream &obs, const Version& obj)
  {
    return obj.write (obs);
  }


  iBinstream& 
  operator>> (iBinstream &ibs, Version& obj)
  {
    return obj.read (ibs);
  }
}

namespace std
{
  using namespace mccore;

  ostream&
  operator<< (ostream& os, const Version& obj)
  {
    return obj.write (os);
  }
}
