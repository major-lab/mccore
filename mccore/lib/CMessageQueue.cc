//                              -*- Mode: C++ -*- 
// CMessageQueue.cc
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Aug 23 15:09:39 2001
// Update Count     : 5
// Status           : Unknown.
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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



void
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
}
