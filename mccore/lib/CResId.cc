//                              -*- Mode: C++ -*- 
// CResId.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:15:00 2000
// Update Count     : 1
// Status           : Ok.
// 


#include <iostream.h>

#include "CResId.h"
#include "Binstream.h"



const CResId&
CResId::operator= (const CResId &right)
{
  if (this != &right)
    {
      no = right.no;
      chain = right.chain;
    }
  return *this;
}



ostream&
operator<< (ostream &os, const CResId &obj)
{
  if (obj.GetChainId () != ' ')
    os << obj.GetChainId ();
  return os << obj.GetResNo ();
}



iBinstream&
operator>> (iBinstream &ibs, CResId &obj)
{
  int resno;
  char chainid;

  ibs >> resno >> chainid;
  obj.SetResNo (resno);
  obj.SetChainId (chainid);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const CResId &obj)
{
  return obs << obj.GetResNo () << obj.GetChainId ();
}
