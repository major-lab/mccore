//                              -*- Mode: C++ -*- 
// CMessageQueue.cc
// Copyright © 2000 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:44 2000
// Update Count     : 1
// Status           : Unknown.
// 


#include <string.h>

#include "CMessageQueue.h"



const char*
CMessageQueue::GetStr ()
{
  if (mOst)
    {
      strncpy (mBuf, mOst->str (), mOst->pcount ());
      mBuf[mOst->pcount ()] = '\0';
      mOst->rdbuf ()->freeze (0);
      return mBuf;
    }
  else
    return "";
}



CMessageQueue&
CMessageQueue::output (const char *s)
{
  if (mCurrentVerbose <= mVerbose)
    {
      char *str = new char[strlen (s) + 256];
      const char *p1 = s;
      char *p2 = str;
      
      while (*p1)
	{
	  if (*p1 == '<')
	    {
	      if (strncmp (p1, "<b>", 3) == 0)
		{
		  *p2++ = '';
		  *p2++ = '[';
		  *p2++ = '0';
		  *p2++ = ';';
		  *p2++ = '1';
		  *p2++ = 'm';
		  p1 += 2;
		}
	      else if (strncmp (p1, "<i>", 3) == 0)
		{
		  *p2++ = '';
		  *p2++ = '[';
		  *p2++ = '0';
		  *p2++ = ';';
		  *p2++ = '4';
		  *p2++ = 'm';
		  p1 += 2;
		}
	      else if (strncmp (p1, "</b>", 4) == 0
		       || strncmp (p1, "</i>", 4) == 0)
		{
		  *p2++ = '';
		  *p2++ = '[';
		  *p2++ = '0';
		  *p2++ = 'm';
		  p1 += 3;
		}
	      else if (strncmp (p1, "<br>", 4) == 0)
		p1 += 3;
	      else
		*p2++ = *p1;
	    }
	  else
	    *p2++ = *p1;
	  p1++;
	}
      *p2 = *p1;
    
      if (mOst)
	*mOst << s;
      *mStream << str;
      delete[] str;
    }
  return *this;
}
