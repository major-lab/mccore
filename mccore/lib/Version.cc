//                              -*- Mode: C++ -*- 
// Version.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <philippe.thibault@umontreal.ca>
// Created On       : Wed May 11 10:07:28 2005
// $Revision: 1.1 $
// $Id: Version.cc,v 1.1 2005-05-20 15:28:46 thibaup Exp $
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "Version.h"


namespace mccore
{

  const string Version::version (VERSION);
  const string Version::machine (MACHINE);
  const string Version::kernel (KERNEL);
  const string Version::osname (OSNAME);

  ostream&
  Version::write (ostream& os) const
  {
    return os << PACKAGE << " " 
	      << Version::version << " " 
	      << Version::machine << " "
	      << Version::kernel << " "
	      << Version::osname << " "
	      << __DATE__;
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
