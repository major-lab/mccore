//                              -*- Mode: C++ -*-
// ResidueFactoryMethod.cc
// Copyright � 2003-14 Laboratoire d'ingénierie des ARN.
//                     Université de Montréal.
// Author           : Marc-Frédérick Blanchet
// Created On       : Thu Feb 13 12:07:00 2014
// $Revision: 2.0 $
// $Id: AtomFactoryMethod.cc,v 2.0 2014-02-13 12:09:00 blanchmf Exp $
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

#include "Atom.h"
#include "Exception.h"
#include "Binstream.h"


#define _TAG_AtomFM         'A'

namespace mccore
{

	AtomFactoryMethod* AtomFactoryMethod::read (iBinstream& ibs)
	{
		AtomFactoryMethod* pFM = 0;
		char tag = 0;

		ibs >> tag;

		switch (tag)
		{
			case _TAG_AtomFM:
			{
				pFM = new AtomFM ();
				break;
			}
			default:
			{
				FatalIntLibException ex ("", __FILE__, __LINE__);
				ex << "Unknown AtomFactoryMethod tag '" << tag << "' in binary stream.";
				throw ex;
			}
		}
		return pFM;
	}

	Atom* AtomFM::createAtom() const
	{
		return new Atom ();
	}


	Atom* AtomFM::createAtom (const Atom& aAtom) const
	{
		return new Atom(aAtom);
	}


	oBinstream& AtomFM::write (oBinstream& obs) const
	{
		return obs << (char)_TAG_AtomFM;
	}


	oBinstream& operator<< (oBinstream& obs, const AtomFactoryMethod& obj)
	{
		return obj.write (obs);
	}

}
