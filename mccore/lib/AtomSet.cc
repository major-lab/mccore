//                              -*- Mode: C++ -*- 
// AtomSet.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Thu Mar 13 13:03:07 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Apr 10 21:33:12 2003
// Update Count     : 23
// Status           : Unknown.
// 



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "AtomSet.h"
#include "AtomType.h"
#include "Binstream.h"

namespace mccore {
  
  const int AtomSet::ATOMSET_ALL = 0;
  const int AtomSet::ATOMSET_NOT = 1;
  const int AtomSet::ATOMSET_AND = 2;
  const int AtomSet::ATOMSET_OR  = 3;
  const int AtomSet::ATOMSET_SIDECHAIN = 4;
  const int AtomSet::ATOMSET_BACKBONE = 5;
  const int AtomSet::ATOMSET_PSE = 6;
  const int AtomSet::ATOMSET_HYDROGEN = 7;
  const int AtomSet::ATOMSET_LP = 8;
  const int AtomSet::ATOMSET_ATOM = 9;
  
  ostream&
  operator<< (ostream &os, const AtomSet &as)
  {
    return as.output (os);
  }


  oBinstream&
  operator<< (oBinstream &obs, const AtomSet &as)
  {
    return as.output (obs);
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
    os << "all";
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
    os << "not (" << *op << ")";
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
    os << "(" << *op1 << " && " << *op2 << ")";
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
    os << "(" << *op1 << " || " << *op2 << ")";
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
    os << "sidechain";
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
    os << "backbone";
    return os;
  }

  
  oBinstream& 
  AtomSetBackbone::output (oBinstream &obs) const
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
    os << "pse";
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
    os << "lp";
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
    os << "hydrogen";
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

