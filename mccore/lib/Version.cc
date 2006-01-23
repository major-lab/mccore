//                              -*- Mode: C++ -*- 
// Version.cc
// Copyright © 2005-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.5 $
// $Id: Version.cc,v 1.5 2006-01-23 23:05:54 larosem Exp $
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
    : version (VERSION),
      cpu (VERSION_CPU),
      vendor (VERSION_VENDOR),
      os (VERSION_OS),
      timestamp (((string) __DATE__) + " " + __TIME__)
  { }
  

  Version::Version (const Version& v)
    : version (v.version),
      cpu (v.cpu),
      vendor (v.vendor),
      os (v.os),
      timestamp (v.timestamp)
  { }


  Version&
  Version::operator= (const Version& v)
  {
    if (this != &v)
      {
	version = v.version;
	cpu = v.cpu;
	vendor = v.vendor;
	os = v.os;
	timestamp = v.timestamp;
      }
    return *this;
  }


  bool
  Version::operator== (const Version& v) const
  {
    return (version == v.version
	    && cpu == v.cpu
	    && vendor == v.vendor
	    && os == v.os
	    && timestamp == v.timestamp);
  }
  

  string
  Version::toString () const
  {
    return (((string) PACKAGE) + " " 
	    + version + " "
	    + cpu + " "
	    + vendor + " "
	    + os + " "
	    + timestamp);
  }


  ostream&
  Version::write (ostream& os) const
  {
    return os << toString ();
  }


  oBinstream&
  Version::write (oBinstream& obs) const
  {
    return obs << version
	       << cpu
	       << vendor
	       << os
	       << timestamp;
  }


  iBinstream& 
  Version::read (iBinstream& ibs)
  {
    Version saved = *this;

    version = cpu = vendor = os = timestamp = "unread";
    ibs >> version
	>> cpu 
	>> vendor 
	>> os
	>> timestamp;

    if (*this != saved)
      {
	gErr (4) << "Warning: reading data created from package version: " << endl
		 << "\t" << *this << endl
		 << "using package version: "
		 << "\t" << saved << endl;
      }
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
