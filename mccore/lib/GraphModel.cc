//                              -*- Mode: C++ -*- 
// GraphModel.cc
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 19:34:11 2004
// $Revision: 1.1.2.3 $
// $Id: GraphModel.cc,v 1.1.2.3 2004-12-27 01:37:53 larosem Exp $
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

#include <set>
#include <vector>

#include "GraphModel.h"
#include "Relation.h"
#include "Residue.h"

using namespace std;



namespace mccore
{

  GraphModel::GraphModel (const GraphModel &right)
    : AbstractModel (right),
      annotated (right.annotated)
  {
    deepCopy (right);
  }
  

  GraphModel::~GraphModel ()
  {
    vector< Residue* >::iterator resIt;
    vector< Relation* >::iterator relIt;

    for (resIt = vertices.begin (); vertices.end () != resIt; ++resIt)
      {
	delete *resIt;
      }
    for (relIt = edges.begin (); edges.end () != relIt; ++relIt)
      {
	delete *relIt;
      }
  }


  void
  GraphModel::deepCopy (const GraphModel &right)
  {
    vector< Residue* >::const_iterator resIt;
    vector< Relation* >::const_iterator relIt;
    set< const Residue*, less_deref< Residue > > resSet;

    for (resIt = right.vertices.begin (); right.vertices.end () != resIt; ++resIt)
      {
	Residue *res = (*resIt)->clone ();
	
	graphsuper::insert (res, 0);
	resSet.insert (res);	
      }
    for (relIt = right.edges.begin (); right.edges.end () != relIt; ++relIt)
      {
	Relation *rel;

	rel = (*relIt)->clone ();
	rel->reassignResiduePointers (resSet);
	graphsuper::connect (const_cast< Residue* > (rel->getRef ()), const_cast < Residue* > (rel->getRes ()), rel, 0);
      }
  }
  
  
  GraphModel&
  GraphModel::operator= (const GraphModel &right)
  {
    if (this != &right)
      {
	AbstractModel::operator= (right);
	annotated = right.annotated;
	deepCopy (right);
      }
    return *this;
  }
    

  void
  GraphModel::sort ()
  {
  }
  
    
  void
  GraphModel::clear ()
  {
  }


  void
  GraphModel::annotate ()
  {
  }
    

  ostream&
  GraphModel::output (ostream &os) const
  {
    return os;
  }


  iPdbstream&
  GraphModel::input (iPdbstream &ips)
  {
    return ips;
  }
  

  oBinstream&
  GraphModel::output (oBinstream &obs) const
  {
    return obs;
  }
  
  
  iBinstream&
  GraphModel::input (iBinstream &ibs)
  {
    return ibs;
  }
  
}
