//                              -*- Mode: C++ -*- 
// ResId.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Patrick Gendron
// Created On       : Mon Mar 10 14:45:21 2003
// Last Modified By : Philippe Thibault
// Last Modified On : Wed Jun 30 14:15:28 2004
// Update Count     : 31
// Status           : Unknown.
// 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>

#include "ResId.h"
#include "Binstream.h"
#include "Exception.h"



#ifndef HAVE_STRSEP
static char*
strsep (char **stringp, const char *delim)
{
  char *return_val = *stringp;
  char *to;

  if (*stringp == 0)
    return 0;

  to = strpbrk (*stringp, delim);

  if (to)
    *to++ = '\0';
  
  *stringp = to;

  return return_val;
}
#endif



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
	    FatalLibException exc ("Malformed residue id ");
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
	FatalLibException exc ("Malformed residue number in residue id ");
	exc << '\'' << chain << '\'' << token;
	if (strCopy && strlen (strCopy) > 0)
	  exc << '.' << strCopy;
	throw exc;
      }
    for (i = 0; i < strlen (token); ++i)
      if (!isdigit (token[i]))
	{
	  delete[] base;
	  FatalLibException exc ("Residue number is non numeric in residue id ");
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
	    FatalLibException exc ("Malformed insertion code in residue id ");
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
  
  
  Exception&
  operator<< (Exception &ex, const ResId& obj)
  {
    if (obj.getChainId () == ' ') ex << obj.getResNo ();
    else if (! isalpha (obj.getChainId ())) 
      ex << '\'' << obj.getChainId () << '\'' << obj.getResNo ();
    else ex << obj.getChainId () << obj.getResNo ();
    
    if (obj.getInsertionCode () != ' ') ex << '.' << obj.getInsertionCode ();
    
    return ex;
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
