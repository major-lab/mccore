//                              -*- Mode: C++ -*- 
// ModelFactoryMethod.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Wed Jan  5 17:20:53 2005
// $Revision: 1.2 $
// $Id: ModelFactoryMethod.cc,v 1.2 2005-01-25 15:23:00 thibaup Exp $
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
#include "GraphModel.h"
#include "Model.h"
#include "ModelFactoryMethod.h"
#include "ResidueFactoryMethod.h"



namespace mccore
{

  ModelFactoryMethod::ModelFactoryMethod (const ResidueFactoryMethod *fm)
    : rFM (fm == 0 ? new ExtendedResidueFM () : fm->clone ())
  { }
  
  
  ModelFactoryMethod::ModelFactoryMethod (const ModelFactoryMethod &right)
    : rFM (right.rFM->clone ())
  { }

  
  ModelFactoryMethod::~ModelFactoryMethod ()
  {
    delete rFM;
  }


  const ResidueFactoryMethod* 
  ModelFactoryMethod::getResidueFactoryMethod () const
  {
    return this->rFM;
  }


  void 
  ModelFactoryMethod::setResidueFactoryMethod (const ResidueFactoryMethod* fm)
  {
    delete this->rFM;
    this->rFM = 0 == fm ? new ExtendedResidueFM () : fm->clone ();
  }

  
  AbstractModel* 
  ModelFM::createModel () const
  {
    return new Model (rFM->clone ());
  }


  AbstractModel* 
  GraphModelFM::createModel () const
  {
    return new GraphModel (rFM->clone ());
  }

}
