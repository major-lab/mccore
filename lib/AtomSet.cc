//                              -*- Mode: C++ -*- 
// AtomSet.cc
// Copyright � 2003-04 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al.
// Author           : Patrick Gendron
// Created On       : Thu Mar 13 13:03:07 2003
// $Revision: 1.7 $
// $Id: AtomSet.cc,v 1.7 2005-08-19 20:22:52 thibaup Exp $
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

#include <ctype.h>
#include <string.h>

#include "AtomSet.h"
#include "AtomType.h"
#include "Binstream.h"
#include "Exception.h"

namespace mccore {
  
  const int AtomSet::ATOMSET_ALL       =  0;
  const int AtomSet::ATOMSET_NOT       =  1;
  const int AtomSet::ATOMSET_AND       =  2;
  const int AtomSet::ATOMSET_OR        =  3;
  const int AtomSet::ATOMSET_SIDECHAIN =  4;
  const int AtomSet::ATOMSET_BACKBONE  =  5;
  const int AtomSet::ATOMSET_PHOSPHATE =  6;
  const int AtomSet::ATOMSET_PSE       =  7;
  const int AtomSet::ATOMSET_HYDROGEN  =  8;
  const int AtomSet::ATOMSET_LP        =  9;
  const int AtomSet::ATOMSET_ATOM      = 10;

  const char* AtomSetAll::representation       = "all";
  const char* AtomSetAnd::representation       = "and";
  const char* AtomSetNot::representation       = "not";
  const char* AtomSetOr::representation        = "or";
  const char* AtomSetBackbone::representation  = "backbone";
  const char* AtomSetHydrogen::representation  = "hydrogen";
  const char* AtomSetLP::representation        = "lp";
  const char* AtomSetPhosphate::representation = "phosphate";
  const char* AtomSetPSE::representation       = "pse";
  const char* AtomSetSideChain::representation = "sidechain";
  
  iBinstream& operator>> (iBinstream &ibs, AtomSet *&as)
  {
    int nb;
    AtomSet *op1;
    AtomSet *op2;
    

    ibs >> nb;

    switch (nb) {
    case AtomSet::ATOMSET_ALL:
      as = new AtomSetAll ();
      break;
    case AtomSet::ATOMSET_NOT:
      ibs >> op1;
      as = new AtomSetNot (op1);
      break;
    case AtomSet::ATOMSET_AND:
      ibs >> op1;
      ibs >> op2;
      as = new AtomSetAnd (op1, op2);
      break;
    case AtomSet::ATOMSET_OR:
      ibs >> op1;
      ibs >> op2;
      as = new AtomSetOr (op1, op2);
      break;      
    case AtomSet::ATOMSET_SIDECHAIN:
      as = new AtomSetSideChain ();
      break;
    case AtomSet::ATOMSET_BACKBONE:
      as = new AtomSetBackbone ();
      break;
    case AtomSet::ATOMSET_PHOSPHATE:
      as = new AtomSetPhosphate ();
      break;
    case AtomSet::ATOMSET_PSE:
      as = new AtomSetPSE ();
      break;
    case AtomSet::ATOMSET_HYDROGEN: 
      as = new AtomSetHydrogen ();
      break;
    case AtomSet::ATOMSET_LP:
      as = new AtomSetLP ();
      break;
    case AtomSet::ATOMSET_ATOM:
      const AtomType* t;
      ibs >> t;
      as = new AtomSetAtom (t);
      break;

    default:
      FatalIntLibException ex ("", __FILE__, __LINE__);
      ex << "corrupted AtomSet class tag #" << nb << " in binary data.";
      throw ex;
    }
    return ibs;
  }
  

  oBinstream&
  operator<< (oBinstream &obs, const AtomSet &as)
  {
    return as.output (obs);
  }


  AtomSet*
  AtomSet::create (const char* str)
  {
	  unsigned int i;
	  size_t sz = strlen(str);
	  char* lstr = reinterpret_cast<char*>(alloca(sz + 1));

    for (i = 0; i < sz; ++i)
      lstr[i] = tolower (str[i]);
    lstr[i] = '\0';
    
    if (0 == strcmp (lstr, AtomSetAll::representation))
      return new AtomSetAll ();
    else if (0 == strcmp (lstr, AtomSetBackbone::representation))
      return new AtomSetBackbone ();
    else if (0 == strcmp (lstr, AtomSetPhosphate::representation))
      return new AtomSetPhosphate ();
    else if (0 == strcmp (lstr, AtomSetSideChain::representation))
      return new AtomSetSideChain ();
    else if (0 == strcmp (lstr, AtomSetPSE::representation))
      return new AtomSetPSE ();
    else if (0 == strcmp (lstr, AtomSetLP::representation))
      return new AtomSetLP ();
    else if (0 == strcmp (lstr, AtomSetHydrogen::representation))
      return new AtomSetHydrogen ();
    else
    {
      IntLibException ex ("", __FILE__, __LINE__);
      ex << "Unknown AtomSet string representation \"" << lstr << "\"";
      throw ex;
    }
    
    return 0;
  }
  

  AtomSetAll&
  AtomSetAll::operator= (const AtomSetAll &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }


  ostream& 
  AtomSetAll::output (ostream &os) const
  {
    os << AtomSetAll::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetAll::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }


  AtomSetNot&
  AtomSetNot::operator= (const AtomSetNot &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
	delete op;
	op = other.op->clone ();
      }
    return *this;
  }

  ostream& 
  AtomSetNot::output (ostream &os) const
  {
    os << AtomSetNot::representation << " (" << *op << ")";
    return os;
  }

  
  oBinstream& 
  AtomSetNot::output (oBinstream &obs) const
  {
    obs << getSetNumber () << *op;
    return obs;
  }


  AtomSetAnd&
  AtomSetAnd::operator= (const AtomSetAnd &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
	delete op1;
	delete op2;
	op1 = other.op1->clone ();
	op2 = other.op2->clone ();
      }
    return *this;
  }

  ostream& 
  AtomSetAnd::output (ostream &os) const
  {
    os << "(" << *op1 << " "
       << AtomSetAnd::representation
       << " " << *op2 << ")";
    return os;
  }

  
  oBinstream& 
  AtomSetAnd::output (oBinstream &obs) const
  {
    obs << getSetNumber () << *op1 << *op2;
    return obs;
  }

  AtomSetOr&
  AtomSetOr::operator= (const AtomSetOr &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
	delete op1;
	delete op2;
	op1 = other.op1->clone ();
	op2 = other.op2->clone ();
      }
    return *this;
  }

  ostream& 
  AtomSetOr::output (ostream &os) const
  {
    os << "(" << *op1 << " "
       << AtomSetOr::representation
       << " " << *op2 << ")";
    return os;
  }

  
  oBinstream& 
  AtomSetOr::output (oBinstream &obs) const
  {
    obs << getSetNumber () << *op1 << *op2;
    return obs;
  }

  AtomSetSideChain&
  AtomSetSideChain::operator= (const AtomSetSideChain &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetSideChain::output (ostream &os) const
  {
    os << AtomSetSideChain::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetSideChain::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }

  AtomSetBackbone&
  AtomSetBackbone::operator= (const AtomSetBackbone &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetBackbone::output (ostream &os) const
  {
    os << AtomSetBackbone::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetBackbone::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }

  
  AtomSetPhosphate&
  AtomSetPhosphate::operator= (const AtomSetPhosphate &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetPhosphate::output (ostream &os) const
  {
    os << AtomSetPhosphate::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetPhosphate::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }

  
  AtomSetPSE&
  AtomSetPSE::operator= (const AtomSetPSE &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetPSE::output (ostream &os) const
  {
    os << AtomSetPSE::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetPSE::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }

  AtomSetLP&
  AtomSetLP::operator= (const AtomSetLP &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetLP::output (ostream &os) const
  {
    os << AtomSetLP::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetLP::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }


  AtomSetHydrogen&
  AtomSetHydrogen::operator= (const AtomSetHydrogen &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
      }
    return *this;
  }

  ostream& 
  AtomSetHydrogen::output (ostream &os) const
  {
    os << AtomSetHydrogen::representation;
    return os;
  }

  
  oBinstream& 
  AtomSetHydrogen::output (oBinstream &obs) const
  {
    obs << getSetNumber ();
    return obs;
  }


  AtomSetAtom&
  AtomSetAtom::operator= (const AtomSetAtom &other)
  {
    if (this != &other)
      {
	AtomSet::operator= (other);
	type = other.type;
      }
    return *this;
  }

  ostream& 
  AtomSetAtom::output (ostream &os) const
  {
    os << type;
    return os;
  }

  
  oBinstream& 
  AtomSetAtom::output (oBinstream &obs) const
  {
    obs << getSetNumber () << type;
    return obs;
  }

}



namespace std
{
  
  ostream&
  operator<< (ostream &os, const mccore::AtomSet &as)
  {
    return as.output (os);
  }

}  
