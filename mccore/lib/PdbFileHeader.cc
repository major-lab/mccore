//                              -*- Mode: C++ -*- 
// PdbFileHeader.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 18:45:58 2003
// $Revision: 1.7 $
// $Id: PdbFileHeader.cc,v 1.7 2005-03-10 19:18:36 thibaup Exp $
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


#include <stdlib.h>
#include <time.h>
#include <sstream>

#include "Pdbstream.h"
#include "Binstream.h"
#include "Exception.h"
#include "Messagestream.h"
#include "PdbFileHeader.h"


namespace mccore
{
  const string PdbFileHeader::ElectronDiffraction = "ELECTRON DIFFRACTION";
  const string PdbFileHeader::FiberDiffraction = "FIBER DIFFRACTION";
  const string PdbFileHeader::FluorescenceTransfer = "FLUORESCENCE TRANSFER";
  const string PdbFileHeader::NeutronDiffraction = "NEUTRON DIFFRACTION";
  const string PdbFileHeader::NMR = "NMR";
  const string PdbFileHeader::TheoreticalModel = "THEORETICAL MODEL";
  const string PdbFileHeader::XRayDiffraction = "X-RAY DIFFRACTION";

  // LIFECYCLE ------------------------------------------------------------

  PdbFileHeader::PdbFileHeader (bool reset)
  {
    this->clear (reset);
  }


  PdbFileHeader::PdbFileHeader (const PdbFileHeader &other) 
    : classification (other.classification),
      date (other.date),
      pdbId (other.pdbId),
      title (other.title),
      methods (other.methods),
      authors (other.authors),
      resolution (other.resolution),
      unclassified (other.unclassified)
  {

  }

  // OPERATORS ------------------------------------------------------------

  PdbFileHeader&
  PdbFileHeader::operator= (const PdbFileHeader &other) 
  {
    if (this != &other) 
    {
      this->classification = other.classification;
      this->date = other.date;
      this->pdbId = other.pdbId;
      this->title = other.title;
      this->methods = other.methods;
      this->authors = other.authors;
      this->resolution = other.resolution;
      this->unclassified = other.unclassified;
    }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  void 
  PdbFileHeader::setClassification (const string &s) 
  { 
    this->classification = Pdbstream::trim (s);
    this->classification.resize (40, ' ');
  }


  void PdbFileHeader::setDate () 
  {
    time_t now = time (0);
    
    setDate (localtime (&now)->tm_mday,
	     localtime (&now)->tm_mon + 1,
	     localtime (&now)->tm_year+1900);
  }


  void 
  PdbFileHeader::setDate (unsigned int day, unsigned int month, unsigned int year) 
  {
    ostringstream oss;
    static const char* mnames[13] =  
      { "???", "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };

    // -- validation
    if (day > 31) day = 0;
    if (month > 12) month = 0;
    if (year > 9999) year = 0;

    oss.width (2);
    oss.fill ('0');
    oss << day << "-" << mnames[month]  << "-";
    oss.width (4);
    oss << year;
    this->date = oss.str ();
  }


  void 
  PdbFileHeader::setDate (const string &s) 
  { 
    this->date = Pdbstream::trim (s);
    this->date.resize (11, ' ');
  }


  void 
  PdbFileHeader::setPdbId (const string &s) 
  { 
    this->pdbId = Pdbstream::trim (s);
    this->pdbId.resize (4, ' ');
  }


  void 
  PdbFileHeader::setTitle (const string &s)
  { 
    this->title = s;
  }
   

  void
  PdbFileHeader::setMethods (const map< string, string >& mlist)
  {
//     map< string, string >::const_iterator it;

//     this->methods.clear ();
//     for (it = mlist.begin (); it != mlist.end (); ++it)
//       this->addMethod (it->first, it->second);

    this->methods = mlist;
  }


  void
  PdbFileHeader::setAuthors (const list< string >& alist)
  {
//     list< string >::const_iterator it;

//     this->authors.clear ();
//     for (it = alist.begin (); it != alist.end (); ++it)
//       this->addAuthor (*it);

    this->authors = alist;
  }


  void 
  PdbFileHeader::setResolution (float f)
  {
    this->resolution = f > 99.94 ? 99.94 : f;
  }


  void
  PdbFileHeader::setUnclassified (const list< string >& ulist)
  {
//     list< string >::const_iterator it;

//     this->unclassified.clear ();
//     for (it = ulist.begin (); it != ulist.end (); ++it)
//       this->addUnclassified (*it);

    this->unclassified = ulist;
  }

 
  // METHODS --------------------------------------------------------------

  void 
  PdbFileHeader::addMethod (const string& n)
  {
    string es;
    this->addMethod (n, es);
  }


  void 
  PdbFileHeader::addMethod (const string& n, const string& c)
  {
    pair< map< string, string >::iterator, bool > inserted = 
      this->methods.insert (make_pair (Pdbstream::trim (n), c));

    if (!inserted.second)
      inserted.first->second += ", " + c;
  }


  void 
  PdbFileHeader::addAuthor (const string& a)
  {
    //string cut = Pdbstream::trim (a);
//     if (!cut.empty ())
//       this->authors.push_back (cut);
    this->authors.push_back (a);
  }


  void PdbFileHeader::addUnclassified (const string& str)
  {
    //string cut = Pdbstream::trim (str);
//     if (!cut.empty ())
//       this->unclassified.push_back (cut);
    this->unclassified.push_back (str);
  }


  void 
  PdbFileHeader::clear (bool reset)
  {
    this->title.clear ();
    this->methods.clear ();
    this->authors.clear ();
    this->unclassified.clear ();
    this->resolution = -1.0;

    if (reset)
    {
      this->setClassification ("Unclassified");
      this->setDate ();
      this->setPdbId ("Void");
      
      string com = "File generated using ";
      com += PACKAGE;
      com += " ";
      com += VERSION;
      com += " by ";
      const char* cs = getenv ("USER");
      com += 0 == cs ? "anonymous" : cs;
      cs = getenv ("HOST");
      com += "@";
      com += 0 == cs ? "nohost" : cs;
      this->addUnclassified (com);
    }
    else
    {
      string es;
      this->setClassification (es);
      this->setDate (es);
      this->setPdbId (es);
    }
  }

  // I/O  -----------------------------------------------------------------

  ostream& 
  PdbFileHeader::write (ostream& os) const
  {
    map< string, string >::const_iterator psit;
    list< string >::const_iterator sit;

    os << "Classification: " << this->classification << endl
       << "PDB ID: " << this->pdbId <<  endl
       << "Date: " << this->date <<  endl
       << "Title: " << this->title << endl
       << "Methods:" << endl;

    for (psit = this->methods.begin (); psit != this->methods.end (); ++psit)
      os << "\t- " << psit->first << ", " << psit->second << endl; 
    
    os << "Authors: ";

    for (sit = this->authors.begin (); sit != this->authors.end (); ++sit)
      os << *sit << ", ";

    os << endl << "Resolution: " << this->resolution << endl
       << "Unclassified remarks:" << endl;

    for (sit = this->unclassified.begin (); sit != this->unclassified.end (); ++sit)
      os << "\t- " << *sit << endl;

    return os;
  }

  oPdbstream&
  PdbFileHeader::write (oPdbstream& ops) const
  {
    map< string, string >::const_iterator psit;
    list< string >::const_iterator sit;
    string es, rectext;

    // -- header
    if (!Pdbstream::trim (this->classification).empty ())
    {
      ops.setf (ios::left, ios::adjustfield);
      ops.width (10);
      //        10               40                  11         1         4       = 66
      ops << "HEADER" << this->classification << this->date << ' ' << this->pdbId;
      ops.width (Pdbstream::LINELENGTH - 66);
      ops << ' ' << endl;
    }

    // -- title
    if (!this->title.empty ())
      ops.writeRecord ("TITLE", this->title);

    // -- methods
    if (!this->methods.empty ())
    {
      rectext.clear ();
      psit = this->methods.begin ();

      while (true)
      {
	rectext += psit->first + (psit->second.empty () ? 
				  psit->second : 
				  (psit->second[0] == ' ' ? "," : ", ") + psit->second);

	if (this->methods.end () == ++psit)
	  break;

	rectext += "; ";
      }

      ops.writeRecord ("EXPDTA", rectext);
    }

    // -- authors
    if (!this->authors.empty ())
    {
      rectext.clear ();
      sit = this->authors.begin ();

      while (true)
      {
	rectext += *sit; 

	if (this->authors.end () == ++sit)
	  break;

	rectext += sit->empty () || (*sit)[0] == ' ' ? "," : ", ";
      }

      ops.writeRecord ("AUTHOR", rectext);
    }


    // -- resolution

    ostringstream rs;
    
    rs << "RESOLUTION.";

    if (this->resolution > 0.0)
    {
      rs.setf (ios::fixed);
      rs.width (5);
      rs.precision (2);
      rs << this->resolution << " Angstroms.";
    }
    else
      rs << " NOT APPLICABLE.";
    
    ops.writeRemark (rs.str (), 2);

		       
    // -- unclassified remarks
    
    for (sit = this->unclassified.begin (); sit != this->unclassified.end (); ++sit)
      ops.writeRemark (*sit, 99);

    return ops;
  }


  oBinstream&
  PdbFileHeader::write (oBinstream& obs) const
  {
    map< string, string >::const_iterator mit;
    list< string >::const_iterator lit;

    obs << this->classification << this->date << this->pdbId << this->title 
	<< this->resolution
	<< this->methods.size ();
    for (mit = this->methods.begin (); this->methods.end () != mit; ++mit)
      obs << mit->first << mit->second;
    obs << this->authors.size ();
    for (lit = this->authors.begin (); this->authors.end () != lit; ++lit)
      obs << *lit;
    obs << this->unclassified.size ();
    for (lit = this->unclassified.begin (); this->unclassified.end () != lit; ++lit)
      obs << *lit;
    return obs;
  }


  iPdbstream&
  PdbFileHeader::read (iPdbstream& ips)
  {
    string line, rectype, methodtext, authortext, remtext;
    int remid;
    list< pair< string, int > > remholder;
    list< pair< string, int > >::iterator it;
    istringstream iss;

    this->clear ();

    //while (getline (ips, line).good ())
    while (!ips.readLine (line).eof ())
    {
      if (ips.fail ())
      {
	IntLibException ex ("read failed", __FILE__, __LINE__);
	throw ex;
      }

      line.resize (Pdbstream::LINELENGTH, ' ');
      rectype = Pdbstream::trim (line.substr (0, 6));
      
      if (!rectype.empty ())
      {
	if ("HEADER" == rectype)
	{
	  this->setClassification (line.substr (10, 40));
	  this->setDate (line.substr (50, 11));
	  this->setPdbId (line.substr (62, 4));
	}
	else if ("OBSLTE" == rectype)
	{
	  gErr (4) << "skipped OBSLTE record in PDB header" << endl;
	}
	else if ("TITLE" == rectype)
	{
	  this->title += 
	    (this->title.empty () ? "" : "\n") + Pdbstream::trim (line.substr (10));
	}
	else if ("CAVEAT" == rectype)
	{
	  gErr (4) << "skipped CAVEAT record in PDB header" << endl;
	}
	else if ("COMPND" == rectype)
	{
	  gErr (4) << "skipped COMPND record in PDB header" << endl;
	}
	else if ("SOURCE" == rectype)
	{
	  gErr (4) << "skipped SOURCE record in PDB header" << endl;
	}
	else if ("KEYWDS" == rectype)
	{
	  gErr (4) << "skipped KEYWDS record in PDB header" << endl;
	}
	else if ("EXPDTA" == rectype)
	{
	  methodtext += 
	    (methodtext.empty () ? "" : "\n") + line.substr (10) + " ";
	}
	else if ("AUTHOR" == rectype)
	{
	  authortext += 
	    (authortext.empty () ? "" : "\n") + line.substr (10) + " ";
	}
	else if ("REVDAT" == rectype)
	{
	  gErr (4) << "skipped REVDAT record in PDB header" << endl;
	}
	else if ("SPRSDE" == rectype)
	{
	  gErr (4) << "skipped SPRSDE record in PDB header" << endl;
	}
	else if ("JRNL" == rectype)
	{
	  gErr (4) << "skipped JRNL record in PDB header" << endl;
	}
	else if ("REMARK" == rectype)
	{
	  string remline = Pdbstream::trim (line.substr (11));

	  if (remline.empty ()) // new remark
	  {
	    if (!remtext.empty ()) // save if not first remark read
	    {
	      remholder.push_back (make_pair (remtext, remid));
	      remtext.clear ();
	    }

	    iss.clear ();
	    iss.str (line.substr (7, 3));
	    iss >> remid;
	  }
	  else // concatenate remark line to current remark text (assumed same id)
	    remtext += (remtext.empty () ? "" : "\n") + remline;
	}
	else
	{
	  ips.unreadLine ();
	  break;
	}
      }
    }

    // -- add last remark (if any read)
    if (!remtext.empty ())
      remholder.push_back (make_pair (remtext, remid));


    // -- parse methods: NAME1, comments1; NAME2, comments2; ...

    string::size_type beg, com_beg, end;

    beg = 0;
    do
    {
      end = methodtext.find_first_of (';', beg);
      if ((com_beg = methodtext.find_first_of (',', beg)) < end)
	this->addMethod (methodtext.substr (beg, com_beg - beg),
			 methodtext.substr (com_beg + 1, end - com_beg - 1));
      else
	this->addMethod (methodtext.substr (beg, end - beg));
      beg = end + 1;
    }
    while (string::npos != end);


    // -- parse authors: comma separated list

    beg = 0;
    do
    {
      end = authortext.find_first_of (',', beg);
      this->addAuthor (Pdbstream::trim (authortext.substr (beg, end - beg)));
      beg = end + 1;
    }
    while (string::npos != end);


    // -- parse remarks by remid (record text starts at column 12)
    //    for now only #2 is handled

    for (it = remholder.begin (); it != remholder.end (); ++it)
      switch (it->second)
      {
      case 2: // resolution: 000000000111111111122222222223
	      //             123456789012345678901234567890 
	      // -> record:  REMARK   2 RESOLUTION.xx.xx Angstroms 
	      // -> string:             01234567890123456789
	      //                        00000000001111111111
	iss.clear ();
	iss.str (it->first.substr (11, 5));
	if ((iss >> this->resolution).fail ())
	  this->resolution = -1.0;
	break;

      default:
	this->addUnclassified (it->first);
	break;
      }
    
    return ips;
  }


  iBinstream&
  PdbFileHeader::read (iBinstream& ibs)
  {
    size_t qty;
    string s1, s2;
    
    this->clear ();
    ibs >> this->classification >> this->date >> this->pdbId >> this->title 
	>> this->resolution;
    for (ibs >> qty; ibs.good () && qty > 0; --qty) 
    {
      ibs >> s1 >> s2;
      this->methods.insert (make_pair (s1, s2));
    }
    for (ibs >> qty; ibs.good () && qty > 0; --qty)
    {
      ibs >> s1;
      this->authors.push_back (s1);
    }
    for (ibs >> qty; ibs.good () && qty > 0; --qty)
    {
      ibs >> s1;
      this->unclassified.push_back (s1);
    }
    return ibs;
  }


  oPdbstream& 
  operator<< (oPdbstream &ops, const PdbFileHeader& obj)
  {
    return obj.write (ops);
  }


  oBinstream& 
  operator<< (oBinstream &obs, const PdbFileHeader& obj)
  {
    return obj.write (obs);
  }


  iPdbstream& 
  operator>> (iPdbstream& ips, PdbFileHeader& obj)
  {
    return obj.read (ips);
  }


  iBinstream& 
  operator>> (iBinstream &ibs, PdbFileHeader& obj)
  {
    return obj.read (ibs);
  }
}


namespace std
{

  ostream &
  operator<< (ostream &out, const mccore::PdbFileHeader &h)
  {
    return h.write (out);
  }

}
