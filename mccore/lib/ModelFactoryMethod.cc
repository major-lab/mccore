//                              -*- Mode: C++ -*- 
// ModelFactoryMethod.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose
// Created On       : Wed Jan  5 17:20:53 2005
// $Revision: 1.3 $
// $Id: ModelFactoryMethod.cc,v 1.3 2005-01-26 19:57:58 thibaup Exp $
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
#include "Binstream.h"
#include "Exception.h"


#define _TAG_ModelFM      'M'
#define _TAG_GraphModelFM 'G'


namespace mccore
{

  ModelFactoryMethod::ModelFactoryMethod (const ResidueFactoryMethod *fm)
    : rFM (fm == 0 ? new ExtendedResidueFM () : fm->clone ())
  {
  }
  
  
  ModelFactoryMethod::ModelFactoryMethod (const ModelFactoryMethod &right)
    : rFM (right.rFM->clone ())
  { 
  }

  
  ModelFactoryMethod::~ModelFactoryMethod ()
  {
    delete rFM;
  }


  Residue* 
  ModelFactoryMethod::createResidue () const
  {
    return this->rFM->createResidue ();
  }


  ModelFactoryMethod*
  ModelFactoryMethod::read (iBinstream& ibs)
  {
    char tag = 0;
    ModelFactoryMethod* mfm = 0;

    ibs >> tag;

    switch (tag)
    {
    case _TAG_ModelFM:
      mfm = new ModelFM ();
      break;
    case _TAG_GraphModelFM:
      mfm = new GraphModelFM (); 
      break;
    default:
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown ModelFactoryMethod tag '" << tag << "' in binary stream.";
      throw ex;
    }

    mfm->_read (ibs);
    return mfm;
  }


  oBinstream& 
  ModelFactoryMethod::write (oBinstream& obs) const
  {
    return obs << *this->rFM;
  }
  
  
  iBinstream&
  ModelFactoryMethod::_read (iBinstream& ibs)
  {
    delete this->rFM;
    this->rFM = ResidueFactoryMethod::read (ibs);
    return ibs;
  }


  AbstractModel* 
  ModelFM::createModel () const
  {
    return new Model (this->rFM);
  }


  oBinstream& 
  ModelFM::write (oBinstream& obs) const
  {
    return this->ModelFactoryMethod::write (obs << (char)_TAG_ModelFM);
  }


  AbstractModel* 
  GraphModelFM::createModel () const
  {
    return new GraphModel (this->rFM);
  }


  oBinstream& 
  GraphModelFM::write (oBinstream& obs) const
  {
    return this->ModelFactoryMethod::write (obs << (char)_TAG_GraphModelFM);
  }


  oBinstream&
  operator<< (oBinstream& obs, const ModelFactoryMethod& obj)
  {
    return obj.write (obs);
  }

}
