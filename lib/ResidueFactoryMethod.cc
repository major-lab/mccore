//                              -*- Mode: C++ -*- 
// ResidueFactoryMethod.cc
// Copyright © 2003-04 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose
// Created On       : Thu Mar 20 16:21:52 2003
// $Revision: 1.5 $
// $Id: ResidueFactoryMethod.cc,v 1.5 2005-02-25 16:48:14 thibaup Exp $
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

#include "AtomFactoryMethod.h"
#include "ExtendedResidue.h"
#include "ResidueFactoryMethod.h"
#include "Residue.h"
#include "Exception.h"
#include "Binstream.h"


#define _TAG_ResidueFM         'R'
#define _TAG_ExtendedResidueFM 'E'


namespace mccore
{

  ResidueFactoryMethod::ResidueFactoryMethod (const AtomFactoryMethod *fm)
    : mpAtomFM (fm == 0 ? new AtomFM () : fm->clone ())
  {
  }


  ResidueFactoryMethod::ResidueFactoryMethod (const ResidueFactoryMethod &right)
    : mpAtomFM (right.mpAtomFM->clone ())
  {
  }

  ResidueFactoryMethod*
  ResidueFactoryMethod::read (iBinstream& ibs)
  {
    char tag = 0;

    ibs >> tag;

    switch (tag)
    {
    case _TAG_ResidueFM:
      return new ResidueFM ();
    case _TAG_ExtendedResidueFM:
      return new ExtendedResidueFM ();
    default:
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown ResidueFactoryMethod tag '" << tag << "' in binary stream.";
      throw ex;
    }
  }


  Residue* 
  ResidueFM::createResidue () const
  {
    return new Residue (mpAtomFM);
  }


  Residue* 
  ResidueFM::createResidue (const Residue& res) const
  {
    return new Residue (res, mpAtomFM);
  }


  oBinstream&
  ResidueFM::write (oBinstream& obs) const
  {
    return obs << (char)_TAG_ResidueFM;
  }


  Residue* 
  ExtendedResidueFM::createResidue () const
  {
    return new ExtendedResidue (mpAtomFM);
  }


  Residue* 
  ExtendedResidueFM::createResidue (const Residue& res) const
  {
    return new ExtendedResidue (res, mpAtomFM);
  }


  oBinstream&
  ExtendedResidueFM::write (oBinstream& obs) const
  {
    return obs << (char)_TAG_ExtendedResidueFM;
  }


  oBinstream&
  operator<< (oBinstream& obs, const ResidueFactoryMethod& obj)
  {
    return obj.write (obs);
  }

}
