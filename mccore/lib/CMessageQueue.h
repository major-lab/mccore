//                              -*- Mode: C++ -*- 
// CMessageQueue.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:02:55 2001
// Update Count     : 5
// Status           : Ok.
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


#ifndef _CMessageQueue_h_
#define _CMessageQueue_h_


#include <iostream.h>
#include <strstream.h>



/**
 * @short Console output facility.
 *
 * Version plus flexible de 'cout' pour gérer le niveau de verbose.
 * Un objet global est créé dans McCore (gOut) et est utilisé de la
 * façon suivante:  gOut(2) << "error!" << endl;
 * Indique une erreur de niveau 2.  Sémantique des niveaux:
 * <pre>
 *   0 : Doit être affiché à tout prix (silent).
 *   1 : Erreur importante pouvant compromettre l'intégrité des
 *       résultats à venir. (normal)
 *   2 : Avertissement de toute forme.  Erreur de sémantique
 *       potentielles. (debug)
 *   3 : Toute traces disponibles.  (verbose)
 * </pre>
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CMessageQueue 
{
  /**
   * The stream where the ouput is displayed.
   */
  ostream *mStream;

  /**
   * Verbose level of the message queue.
   */
  int mVerbose;

  /**
   * Verbose level of the last entered message.
   */
  int mCurrentVerbose;

  /**
   * String stream where the messages are kept for further display.
   */
  ostrstream *mOst;

  /**
   * Internal buffer.
   */
  char mBuf[262144];

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the message queue.
   * @param nStream the stream where the messages are displayed.
   * @param nVerbose the initial verbose level of the message queue.
   */
  CMessageQueue (ostream &nStream, int nVerbose) 
    : mStream (&nStream), mVerbose (nVerbose), mOst (0) { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Changes the verbose level of the future entered messages.
   * @param nNewLevel the level.
   * @return itself.
   */
  CMessageQueue& operator() (int nNewLevel)
  { mCurrentVerbose = nNewLevel; return *this; }

  /**
   * Outputs the messages.
   * @param o the object or type to display.
   * @return itself.
   */
  template< class T >
  CMessageQueue& operator<< (const T &o) { output (o); return *this; }

  /**
   * Modifies the CMessageQueue's stream.
   * @param func the ios manipulator function.
   * @return itself.
   */
  CMessageQueue& operator<< (ios& (*func)(ios&))
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << func;
	*mStream << func;
      }
    return *this;
  }

  /**
   * Modifies the CMessageQueue's stream.
   * @param func the ostream manipulator function.
   * @return itself.
   */
  CMessageQueue& operator<< (ostream& (*func)(ostream&))
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << func;
	*mStream << func;
      }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  /**
   * Sets the verbose level of the message queue.
   * @param nVerbose the new verbose level.
   */
  void SetVerbose (int nVerbose) { mVerbose = nVerbose; }

  /**
   * Gets the messages stored in the stream.
   * @return the message string.
   */
  const char* GetStr ();

  // METHODS --------------------------------------------------------------

  /**
   * Starts recording the messages in the message buffer.
   */
  void Record () { if (mOst) delete mOst;  mOst = new ostrstream; }

  /**
   * Stops recording the messages in the message buffer.
   */
  void Stop () { if (mOst) delete mOst;  mOst = 0; }

  // I/O ------------------------------------------------------------------
  
  /**
   * Outputs a character string to the message queue.
   * @param s the string to display.
   */
  void output (const char *s);

  /**
   * Outputs an object or a type to the message queue.
   * @param o the object to display.
   */
  template< class T >
  void output (const T &o)
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << o;
	*mStream << o;
      }
  }
};

#endif
