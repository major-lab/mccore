//                              -*- Mode: C++ -*- 
// Molecule.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Mon Jul  7 15:59:35 2003
// $Revision: 1.3 $
// $Id: Molecule.cc,v 1.3 2003-12-23 14:50:21 larosem Exp $
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

#include <string.h>

#include "Model.h"
#include "Molecule.h"
#include "Pdbstream.h"



namespace mccore {


  
  Molecule::Molecule (const Molecule &right)
  {
    Molecule::const_iterator mcit;
    map< const char*, char* >::const_iterator cit;
    
    for (mcit = right.begin (); right.end () != mcit; ++mcit)
      push_back ((*mcit)->clone ());
    for (cit = right.properties.begin (); right.properties.end () != cit; ++cit)
      properties[strdup (cit->first)] = strdup (cit->second);
  }
  
  
  
  Molecule::~Molecule ()
  {
    Molecule::iterator mit;
    map< const char*, char* >::iterator it;
    
    for (mit = begin (); end () != mit; ++mit)
      delete (*mit);
    for (it = properties.begin (); properties.end () != it; ++it)
      {
	delete it->first;
	delete it->second;
      }
  }
  
  
  
  Molecule&
  Molecule::operator= (const Molecule &right)
  {
    if (&right != this)
      {
	Molecule::iterator it;
	Molecule::const_iterator cit;
	map< const char*, char* >::iterator pit;
	map< const char*, char* >::const_iterator cpit;
	
	for (it = begin (); end () != it; ++it)
	  delete (*it);
	clear ();
	for (pit = properties.begin (); properties.end () != pit; ++pit)
	  {
	    delete pit->first;
	    delete pit->second;
	  }
	properties.clear ();
	for (cit = right.begin (); right.end () != cit; ++cit)
	  push_back ((*cit)->clone ());
	for (cpit = right.properties.begin (); right.properties.end () != cpit; ++cpit)
	  properties[strdup (cpit->first)] = strdup (cpit->second);
      }
    return *this;
  }
  
  
  
  const char*
  Molecule::getProperty (const char *key) const
  {
    map< const char*, char* >::const_iterator cit;
    
    return properties.end () != (cit = properties.find (key)) ? cit->second : 0;
  }
  
  
  
  void
  Molecule::setProperty (const char *key, const char *value)
  {
    map< const char*, char* >::iterator it;
    
    if (properties.end () != (it = properties.find (key)))
      {
	delete it->second;
	it->second = strdup (value);
      }
    else
      properties[strdup (key)] = strdup (value);
  }
  
  
  
  ostream&
  operator<< (ostream &obs, const Molecule &obj)
  {
    const map< const char*, char* > &properties = ((Molecule&) obj).getProperties ();
    map< const char*, char* >::const_iterator cit;
    list< Model* >::const_iterator cmit;
    
    obs << "MOLECULE: " << endl;
    for (cit = properties.begin (); properties.end () != cit; ++cit)
      obs << "  " << cit->first << " = " << cit->second << endl;
    for (cmit = obj.begin (); obj.end () != cmit; ++cmit)
      obs << **cmit << endl;
    return obs;
  }
  
  
  
  iPdbstream&
  operator>> (iPdbstream &ips, Molecule &obj)
  {
    Molecule::iterator it;
    map< const char*, char* > &properties = obj.getProperties ();
    map< const char*, char* >::iterator pit;
    
    for (it = obj.begin (); obj.end () != it; ++it)
      delete (*it);
    obj.clear ();
    for (pit = properties.begin (); properties.end () != pit; ++pit)
      {
	delete pit->first;
	delete pit->second;
      }
    properties.clear ();
    while (! ips.eof ())
      {
	Model *model;
	
	model = new Model ();
	ips >> *model;
	if (! model->empty ())
	  obj.push_back (model);
      }
    return ips;
  }
  
  
  
  oPdbstream&
  operator<< (oPdbstream &ops, const Molecule &obj)
  {
    Molecule::const_iterator cit;
    bool modelHeaders;
    
    modelHeaders = 1 < obj.size ();
    for (cit = obj.begin (); obj.end () != cit; ++cit)
      {
	if (modelHeaders)
	  ops.startModel ();
	ops << **cit;
	if (modelHeaders)
	  ops.endModel ();
      }
    return ops;
  }
}
