//                              -*- Mode: C++ -*- 
// ResId.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:45:21 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Mon Mar 10 16:50:27 2003
// Update Count     : 8
// Status           : Unknown.
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "ResId.h"
#include "Binstream.h"

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
// 	  gOut (2) << "Malformed residue id " << strCopy << endl;
	  delete[] base;
	  return;
	}
      chain = strCopy[1];
      strCopy += 3;
    }
  else if (isalpha (strCopy[0]))
    chain = *strCopy++;
  
  token = strsep (&strCopy, ".");

  if (strlen (token) > 4 || strlen (token) < 1)
    {
//       gOut (2) << "Malformed residue number in residue id "
// 	       << '\'' << chain << '\'' << token;
//       if (strlen (strCopy) > 0)
// 	gOut << '.' << strCopy;
//       gOut << endl;
      delete[] base;
      return;
    }
  for (i = 0; i < strlen (token); ++i)
    if (!isdigit (token[i]))
      {
// 	gOut (2) << "Malformed residue number in residue id "
// 		 << '\'' << chain << '\'' << token;
// 	if (strlen (strCopy) > 0)
// 	  gOut << '.' << strCopy;
// 	gOut << endl;
	delete[] base;
	return;
      }
  no = atoi (token);
  if (strCopy)
    {
      if (strlen (strCopy) != 1)
	{
// 	  gOut (2) << "Malformed insertion code in residue id "
// 		   << (const char*)*this << "." << strCopy << endl;
	  delete[] base;
	  return;
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
      no = other.no;
      chain = other.chain;
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
