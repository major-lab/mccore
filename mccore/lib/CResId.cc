//                              -*- Mode: C++ -*- 
// CResId.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Mon Dec  4 15:40:53 2000
// Update Count     : 2
// Status           : Ok.
// 


#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>

#include "CResId.h"
#include "Binstream.h"



CResId::CResId (const char *str)
{
  if (isalpha (str[0]))
    chain = *str++;
  else
    chain = ' ';
  no = atoi (str);
}



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
