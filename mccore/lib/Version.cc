//                              -*- Mode: C++ -*- 
// Version.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.4 $
// $Id: Version.cc,v 1.4 2005-08-30 13:16:47 thibaup Exp $
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <sstream>

#include "Binstream.h"
#include "Messagestream.h"
#include "Version.h"


namespace mccore
{

  Version::Version ()
    : major_version (-1),
      minor_version (-1),
      cpu (VERSION_CPU),
      vendor (VERSION_VENDOR),
      os (VERSION_OS)
  {
    istringstream iss (VERSION);
    char dot;

    iss >> this->major_version >> dot >> this->minor_version;
    this->timestamp = __DATE__;
    this->timestamp += " ";
    this->timestamp += __TIME__;
  }
  

  Version::Version (const Version& v)
    : major_version (v.major_version),
      minor_version (v.minor_version),
      cpu (v.cpu),
      vendor (v.vendor),
      os (v.os),
      timestamp (v.timestamp)
  {

  }


  Version&
  Version::operator= (const Version& v)
  {
    if (this != &v)
    {
      this->major_version = v.major_version;
      this->minor_version = v.minor_version;
      this->cpu = v.cpu;
      this->vendor = v.vendor;
      this->os = v.os;
      this->timestamp = v.timestamp;
    }
    return *this;
  }


  bool
  Version::operator== (const Version& v) const
  {
    return 
      this->major_version == v.major_version &&
      this->minor_version == v.minor_version &&
      this->cpu == v.cpu &&
      this->vendor == v.vendor &&
      this->os == v.os &&
      this->timestamp == v.timestamp;
  }


  string
  Version::toString () const
  {
    ostringstream oss;
    oss << PACKAGE << " " 
	<< this->major_version << "." << this->minor_version << " " 
	<< this->cpu << " "
	<< this->vendor << " "
	<< this->os << " "
	<< this->timestamp;
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
    return obs << this->major_version << this->minor_version
	       << this->cpu
	       << this->vendor
	       << this->os
	       << this->timestamp;
  }


  iBinstream& 
  Version::read (iBinstream& ibs)
  {
    Version saved = *this;

    this->cpu = this->vendor = this->os = this->timestamp = "unread";
    this->major_version = this->minor_version = -1;
    ibs >> this->major_version >> this->minor_version
	>> this->cpu 
	>> this->vendor 
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
