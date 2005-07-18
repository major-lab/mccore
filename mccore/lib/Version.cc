//                              -*- Mode: C++ -*- 
// Version.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.3 $
// $Id: Version.cc,v 1.3 2005-07-18 20:12:30 thibaup Exp $
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "Binstream.h"
#include "Messagestream.h"
#include "Version.h"


namespace mccore
{
  const string Version::version (VERSION);
  const string Version::cpu (VERSION_CPU);
  const string Version::vendor (VERSION_VENDOR);
  const string Version::os (VERSION_OS);
  const string Version::date (__DATE__);


  Version::Version ()
    : current_version (Version::version),
      current_cpu (Version::cpu),
      current_vendor (Version::vendor),
      current_os (Version::os),
      current_date (Version::date)
  {

  }


  ostream&
  Version::write (ostream& os) const
  {
    return os << PACKAGE << " " 
	      << this->current_version << " " 
	      << this->current_cpu << " "
	      << this->current_vendor << " "
	      << this->current_os << " "
	      << this->current_date;
  }


  oBinstream&
  Version::write (oBinstream& obs) const
  {
    return obs << this->current_version
	       << this->current_cpu
	       << this->current_vendor
	       << this->current_os
	       << this->current_date;
  }


  iBinstream& 
  Version::read (iBinstream& ibs)
  {
    this->current_version = this->current_cpu = this->current_vendor = this->current_os = this->current_date = "unread";
    ibs >> this->current_version 
	>> this->current_cpu 
	>> this->current_vendor 
	>> this->current_os
	>> this->current_date;

    if (Version::version != this->current_version)
      gErr (4) << "Warning: reading data created from " << PACKAGE 
	       << " version " << this->current_version
	       << " using " << PACKAGE << " version " << Version::version << endl;

    if (Version::cpu != this->current_cpu)
      gErr (4) << "Warning: reading data created from " << PACKAGE 
	       << " built on cpu type \"" << this->current_cpu
	       << "\" using " << PACKAGE << " built on cpu type \"" 
	       << Version::cpu << "\"" << endl;

    if (Version::vendor != this->current_vendor)
      gErr (4) << "Warning: reading data created from " << PACKAGE 
	       << " built on cpu vendor \"" << this->current_vendor
	       << "\" using " << PACKAGE << " built on cpu vendor \"" 
	       << Version::vendor << "\"" << endl;

    if (Version::os != this->current_os)
      gErr (4) << "Warning: reading data created from " << PACKAGE 
	       << " built on os type \"" << this->current_os
	       << "\" using " << PACKAGE << " built on os type \"" 
	       << Version::os << "\"" << endl;

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
