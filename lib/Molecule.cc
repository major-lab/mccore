//                              -*- Mode: C++ -*- 
// Molecule.cc
// Copyright © 2003-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose
// Created On       : Mon Jul  7 15:59:35 2003
// $Revision: 1.19 $
// $Id: Molecule.cc,v 1.19 2006-11-15 19:44:37 larosem Exp $
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
#include <config.h>

#include "AbstractModel.h"
#include "Binstream.h"
#include "Molecule.h"
#include "Pdbstream.h"
#include "ModelFactoryMethod.h"
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
  
  
  Molecule::Molecule (const ModelFactoryMethod *fm)
    : modelFM (0 == fm ? new ModelFM () : fm->clone ())
  {

  }

  
  Molecule::Molecule (const Molecule &right)
    : header (right.header),
      properties (right.properties),
      modelFM (right.modelFM->clone ())
  {
    insert (right.begin (), right.end ());
  }
  
  
  Molecule::~Molecule ()
  {
    list< AbstractModel* >::iterator mit;
    
    for (mit = models.begin (); mit != models.end (); ++mit)
      {
	delete *mit;
      }
    delete modelFM;
  }
  
  
  Molecule&
  Molecule::operator= (const Molecule &right)
  {
    if (&right != this)
      {
	const_iterator it;

	clear ();
	delete modelFM;
	header = right.header;
	properties = right.properties;
	modelFM = right.modelFM->clone ();
	insert (right.begin (), right.end ());
      }
    return *this;
  }
  
  
  const string&
  Molecule::getProperty (const string &key) const
  {
    map< string, string >::const_iterator it;

    if (properties.end () == (it = properties.find (key)))
      {
	NoSuchElementException ex ("", __FILE__, __LINE__);
      
	ex << "property key \"" << key << "\" not found in molecule";
	throw ex;
      }
    return it->second;
  }
  
  
  void
  Molecule::setProperty (const string &key, const string &value)
  {
    properties[key] = value;
  }

  
  void
  Molecule::setModelFM (const ModelFactoryMethod *fm)
  {
    delete this->modelFM;
    this->modelFM = 0 == fm ? new ModelFM () : fm->clone ();
  }
  
  
  Molecule::iterator
  Molecule::insert (const AbstractModel& model)
  {
    AbstractModel *cloned;

    cloned = modelFM->createModel (model);

    return (iterator)models.insert (models.end (), cloned);
  }
  
    
  Molecule::iterator
  Molecule::insert (AbstractModel* model)
  {
    return (iterator)models.insert (models.end (), model);
  }
  
    
  Molecule::iterator
  Molecule::erase (iterator pos)
  {
    delete &*pos;
    return (iterator)models.erase (pos);
  }

  
  void
  Molecule::clear ()
  {
    list< AbstractModel* >::iterator mit;
    
    for (mit = models.begin (); mit != models.end (); ++mit)
      {
	delete *mit;
      }
    models.clear ();
    properties.clear ();
  }

  
  ostream&
  Molecule::write (ostream &os) const
  {
    map< string, string >::const_iterator pit;
    const_iterator mit;
    
    os << "MOLECULE:" << endl;
    os << header << endl;
    for (pit = properties.begin (); pit != properties.end (); ++pit)
      {
	os << "  " << pit->first.c_str () << " = " << pit->second.c_str ()
	   << endl;
      }
    for (mit = begin (); mit != end (); ++mit)
      {
	os << *mit << endl;
      }
    return os;
  }

  
  oPdbstream&
  Molecule::write (oPdbstream &ops) const
  {
    const_iterator mit;
    bool modelHeaders = size () > 1;

    ops.setHeader (header);
    for (mit = begin (); mit != end (); ++mit)
    {
      if (modelHeaders)
	ops.startModel ();
      ops << *mit;
      if (modelHeaders)
	ops.endModel ();
    }
    return ops;
  }


  iPdbstream&
  Molecule::read (iPdbstream& ips)
  {
    clear ();

    while (ips.good ())
      {
	AbstractModel* model;

	model = modelFM->createModel ();
	ips >> *model;
	if (model->empty ())
	  {
	    delete model;
	  }
	else
	  {
	    models.push_back (model);
	  }
      }
    setHeader (ips.getHeader ());
    return ips;
  }

  
  oBinstream&
  Molecule::write (oBinstream &obs) const
  {
    const_iterator mit;
    map< string, string >::const_iterator pit;

    // -- dump ModelFactoryMethod in first place
    obs << *modelFM;

    // -- dump models
    obs << (mccore::bin_ui64) size ();
    for (mit = begin (); mit != end (); ++mit)
      {
	obs << *mit;
      }
    
    // -- dump properties
    obs << (mccore::bin_ui64) properties.size ();
    for (pit = properties.begin (); pit != properties.end (); ++pit)
      {
	obs << pit->first.c_str () << pit->second.c_str ();
      }
    return obs;
  }


  iBinstream&
  Molecule::read (iBinstream &ibs)
  {
    mccore::bin_ui64 qty = 0;
    string kcs;
    string vcs;

    // -- reset object
    clear ();

    // -- read ModelFactoryMethod
    delete modelFM;
    modelFM = ModelFactoryMethod::read (ibs);

    // -- read models using restored factory method for object creation
    qty = 0;
    for (ibs >> qty; qty > 0; --qty)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

      models.push_back (modelFM->createModel ());
      ibs >> *models.back ();
    }

    // -- read properties
    qty = 0;
    for (ibs >> qty; qty > 0; --qty)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

      ibs >> kcs >> vcs;
      setProperty (kcs, vcs);
    }
    
    return ibs;
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



namespace std
{
  
  ostream&
  operator<< (ostream &os, const mccore::Molecule &obj)
  {
    return obj.write (os);
  }
    
}
