//                              -*- Mode: C++ -*- 
// Molecule.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose
// Created On       : Mon Jul  7 15:59:35 2003
// $Revision: 1.7.2.2 $
// $Id: Molecule.cc,v 1.7.2.2 2004-12-25 02:42:19 larosem Exp $
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

#include "AbstractModel.h"
#include "Binstream.h"
#include "Exception.h"
#include "Model.h"
#include "Molecule.h"
#include "Pdbstream.h"
#include "ResidueFactoryMethod.h"



namespace mccore
{

  unsigned int
  Molecule::molecule_iterator::operator- (const Molecule::molecule_iterator &right) const
  {
    molecule_iterator it = *this;
    unsigned int dist = 0;

    while (it != right)
      {
	--it;
	++dist;
      }
    return dist;
  }


  unsigned int
  Molecule::molecule_const_iterator::operator- (const Molecule::molecule_const_iterator &right) const
  {
    molecule_const_iterator it = *this;
    unsigned int dist = 0;

    while (it != right)
      {
	--it;
	++dist;
      }
    return dist;
  }
  
  
  Molecule::Molecule (const ResidueFactoryMethod *fm)
    : residueFM (0 == fm ? new ExtendedResidueFM () : fm->clone ())
  {

  }

  
  Molecule::Molecule (const Molecule &right)
    : models (right.models),
      properties (right.properties),
      residueFM (right.residueFM->clone ())
  {
    // retrieve ownership
    list< AbstractModel* >::iterator it;
    for (it = this->models.begin (); it != this->models.end (); ++it)
      *it = (*it)->clone ();
  }
  
  
  Molecule::~Molecule ()
  {
    this->clear ();
    delete this->residueFM;
  }
  
  
  Molecule&
  Molecule::operator= (const Molecule &right)
  {
    if (&right != this)
    {
      list< AbstractModel* >::iterator it;

      // clear all
      this->clear ();
      delete this->residueFM;

      // copy 
      this->models = right.models;
      this->properties = right.properties;
      this->residueFM = right.residueFM->clone ();

      // retrieve ownership
      for (it = this->models.begin (); it != this->models.end (); ++it)
	*it = (*it)->clone ();
    }
    return *this;
  }
  
  
  const char*
  Molecule::getProperty (const char *key) const
  {
    map< string, string >::const_iterator it;
    string ks (key);

    if (this->properties.end () == (it = this->properties.find (ks)))
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "property key \"" << key << "\" not found in molecule";
      throw ex;
    }
    
    return it->second.c_str ();
  }
  
  
  void
  Molecule::setProperty (const string &key, const string &value)
  {
    pair< map< string, string >::iterator, bool > inserted = properties.insert (make_pair (key, value));

    if (! inserted.second)
      {
	inserted.first->second = value;
      }
  }

  
  void
  Molecule::setResidueFM (const ResidueFactoryMethod *fm)
  {
    delete this->residueFM;
    this->residueFM = 0 == fm ? new ExtendedResidueFM () : fm->clone ();
  }
  
  
  void
  Molecule::clear ()
  {
    list< AbstractModel* >::const_iterator mit;
    for (mit = this->models.begin (); mit != this->models.end (); ++mit)
      delete *mit;
    this->models.clear ();
    this->properties.clear ();
  }

  
  ostream&
  Molecule::write (ostream &os) const
  {
    map< string, string >::const_iterator pit;
    list< AbstractModel* >::const_iterator mit;
    
    os << "MOLECULE:" << endl;
    for (pit = this->properties.begin (); pit != this->properties.end (); ++pit)
      os << "  " << pit->first.c_str () << " = " << pit->second.c_str () << endl;
    for (mit = this->models.begin (); mit != this->models.end (); ++mit)
      os << **mit << endl;
    return os;
  }

  
  oPdbstream&
  Molecule::write (oPdbstream &ops) const
  {
    list< AbstractModel* >::const_iterator mit;
    bool modelHeaders = this->size () > 1;

    for (mit = this->models.begin (); mit != this->models.end (); ++mit)
    {
      if (modelHeaders)
	ops.startModel ();
      ops << **mit;
      if (modelHeaders)
	ops.endModel ();
    }
    
    return ops;
  }

  iPdbstream&
  Molecule::read (iPdbstream& ips)
  {
    this->clear ();

    while (!ips.eof ())
    {
      AbstractModel* model = new Model (this->residueFM);
      ips >> *model;
      if (!model->empty ())
	this->models.push_back (model);
      
//       this->models.push_back (new Model (this->residueFM));
//       ips >> *this->models.back ();
    }
    
    return ips;
  }

  oBinstream&
  Molecule::write (oBinstream &obs) const
  {
    list< AbstractModel* >::const_iterator mit;
    map< string, string >::const_iterator pit;

    obs << (unsigned int)this->models.size ();
    for (mit = this->models.begin (); mit != this->models.end (); ++mit)
      obs << **mit;

    obs << (unsigned int)this->properties.size ();
    for (pit = this->properties.begin (); pit != this->properties.end (); ++pit)
      obs << pit->first.c_str () << pit->second.c_str ();

    return obs;
  }


  iBinstream&
  Molecule::read (iBinstream &ibs)
  {
    unsigned int qty;
    char *kcs, *vcs;

    this->clear ();
    
    for (ibs >> qty; qty > 0; --qty)
    {
      this->models.push_back (new Model (this->residueFM));
      ibs >> *this->models.back ();
    }

    for (ibs >> qty; qty > 0; --qty)
    {
      ibs >> &kcs >> &vcs;
      this->setProperty (kcs, vcs);
      delete[] kcs;
      delete[] vcs;
    }

    return ibs;
  }

  
  ostream&
  operator<< (ostream &os, const Molecule &obj)
  {
    return obj.write (os);
  }
  
  
  oPdbstream&
  operator<< (oPdbstream &ops, const Molecule &obj)
  {
    return obj.write (ops);
  }

  
  iPdbstream&
  operator>> (iPdbstream &ips, Molecule &obj)
  {
    return obj.read (ips);
  }


  oBinstream&
  operator<< (oBinstream &obs, const Molecule &obj)
  {
    return obj.write (obs);
  }

  
  iBinstream&
  operator>> (iBinstream &ibs, Molecule &obj)
  {
    return obj.read (ibs);
  }
  

}
