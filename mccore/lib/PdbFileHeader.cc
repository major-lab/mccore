//                              -*- Mode: C++ -*- 
// PdbFileHeader.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 18:45:58 2003
// $Revision: 1.3 $
// $Id: PdbFileHeader.cc,v 1.3 2003-12-23 14:57:49 larosem Exp $
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>

#include "PdbFileHeader.h"



namespace mccore {

  PdbFileHeader::PdbFileHeader (const PdbFileHeader &other) 
  {
    classification = other.classification;
    date = other.date;
    pdbId = other.pdbId;
    title = other.title;
    method = other.method;
    resolution = other.resolution;
  }


  PdbFileHeader&
  PdbFileHeader::operator= (const PdbFileHeader &other) 
  {
    if (this != &other) {
      classification = other.classification;
      date = other.date;
      pdbId = other.pdbId;
      title = other.title;
      method = other.method;
      resolution = other.resolution;
    }
    return *this;
  }

  void PdbFileHeader::setDate () 
  {
    time_t now = time (0);
    
    setDate (localtime (&now)->tm_mday,
	     localtime (&now)->tm_mon,
	     localtime (&now)->tm_year+1900);

  }

  void PdbFileHeader::setDate (int day, int month, int year) 
  {
    date = "";
    char t[5];
    sprintf (t, "%02d", day);
    date += string (t);
    date += "-";
    if (month==0) date += "JAN";
    if (month==1) date += "FEB";
    if (month==2) date += "MAR";
    if (month==3) date += "APR";
    if (month==4) date += "MAY";
    if (month==5) date += "JUN";
    if (month==6) date += "JUL";
    if (month==7) date += "AUG";
    if (month==8) date += "SEP";
    if (month==9) date += "OCT";
    if (month==10) date += "NOV";
    if (month==11) date += "DEC";
    date += "-";
    sprintf (t, "%04d", year);
    date += string (t+2);
  }


  ostream &
  operator<< (ostream &out, const PdbFileHeader &h)
  {
    out << "CLASS = " << h.getClassification () << "\n" 
	<< "PDB Id = " << h.getPdbId () <<  "\n"
	<< "DATE = " << h.getDate () <<  "\n"
	<< "TITLE = " << h.getTitle () << "\n"
      //	<< "COMPOUND = " << h.getCompound () << "\n"
	<< "METHOD = " << h.getMethod () << "\n"
	<< "RESOLUTION = " << h.getResolution ();
    return out;
  }

}
