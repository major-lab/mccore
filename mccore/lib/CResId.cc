//                              -*- Mode: C++ -*- 
// CResId.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Martin Larose
// Created On       : Thu Sep 28 15:55:29 2000
// Last Modified By : Martin Larose
// Last Modified On : Tue Jan 23 15:01:51 2001
// Update Count     : 4
// Status           : Ok.
// 


#include <iostream.h>
#include <stdio.h>
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



CResId&
CResId::operator= (const CResId &right)
{
  if (this != &right)
    {
      no = right.no;
      chain = right.chain;
    }
  return *this;
}



CResId::operator const char* () const
{
  if (chain == ' ')
    sprintf (mRep, "%d", no);
  else
    sprintf (mRep, "%c%d", chain, no);
  return mRep;
}



ostream&
operator<< (ostream &os, const CResId &obj)
{
  return os << obj.operator const char* ();
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
