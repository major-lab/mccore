//                              -*- Mode: C++ -*- 
// ResId.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:45:21 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Wed Jul 30 19:01:33 2003
// Update Count     : 30
// Status           : Unknown.
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "ResId.h"
#include "Binstream.h"
#include "CException.h"

namespace mccore {

ResId::ResId (const char *str)
  : chain (' '), no (-1), iCode (' ')
{
  char *strCopy = strdup (str);
  char *base = strCopy;
  char *token;
  unsigned int i;

  if (strCopy[0] == '\'')
    {
      if (strlen (strCopy) < 4 || strCopy[2] != '\'')
	{
 	  delete[] base;
	  CFatalLibException exc ("Malformed residue id ");
	  exc << strCopy;
	  throw exc;
	}
      chain = strCopy[1];
      strCopy += 3;
    }
  else if (isalpha (strCopy[0]))
    chain = *strCopy++;
  
  token = strsep (&strCopy, ".");

  if (strlen (token) < 1)
    {
      delete[] base;
      CFatalLibException exc ("Malformed residue number in residue id ");
      exc << '\'' << chain << '\'' << token;
      if (strCopy && strlen (strCopy) > 0)
	exc << '.' << strCopy;
      throw exc;
    }
  for (i = 0; i < strlen (token); ++i)
    if (!isdigit (token[i]))
      {
	delete[] base;
	CFatalLibException exc ("Residue number is non numeric in residue id ");
	exc << '\'' << chain << '\'' << token;
	if (strCopy && strlen (strCopy) > 0)
	  exc << '.' << strCopy;
	throw exc;
      }
  no = atoi (token);
  if (strCopy)
    {
      if (strlen (strCopy) != 1)
	{
	  delete[] base;
	  CFatalLibException exc ("Malformed insertion code in residue id ");
	  exc << '\'' << chain << '\'' << no << "." << strCopy;
	  throw exc;
	}
      iCode = strCopy[0];
    }
  delete[] base;
}
  

ResId&
ResId::operator= (const ResId &other)
{
  if (this != &other)
    {
      chain = other.chain;
      no = other.no;
      iCode = other.iCode;
    }
  return *this;
}


ostream&
operator<< (ostream &os, const ResId &obj)
{
  if (obj.getChainId () == ' ') os << obj.getResNo ();
  else if (! isalpha (obj.getChainId ())) 
    os << '\'' << obj.getChainId () << '\'' << obj.getResNo ();
  else os << obj.getChainId () << obj.getResNo ();

  if (obj.getInsertionCode () != ' ') os << '.' << obj.getInsertionCode ();

  return os;
}





iBinstream&
operator>> (iBinstream &ibs, ResId &obj)
{
  int resno;
  char chainid, ic;

  ibs >> resno >> chainid >> ic;
  obj.setResNo (resno);
  obj.setChainId (chainid);
  obj.setInsertionCode (ic);
  return ibs;
}



oBinstream&
operator<< (oBinstream &obs, const ResId &obj)
{
  return obs << obj.getResNo () << obj.getChainId ()
	     << obj.getInsertionCode ();
}

}
