//                              -*- Mode: C++ -*- 
// CMessageQueue.h
// Copyright © 2000, 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Mon Jan 22 15:12:46 2001
// Update Count     : 2
// Status           : Ok.
// 


#ifndef _CMessageQueue_h_
#define _CMessageQueue_h_


#include <iostream.h>
#include <strstream.h>



/**
 * @short 
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
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CMessageQueue 
{
  ostream *mStream;
  int mVerbose;
  int mCurrentVerbose;
  ostrstream *mOst;
  char mBuf[262144];

public:

  // LIFECYCLE ------------------------------------------------------------

  CMessageQueue (ostream &nStream, int nVerbose) 
    : mStream (&nStream), mVerbose (nVerbose) { mOst = 0; }

  // OPERATORS ------------------------------------------------------------

  CMessageQueue& operator() (int nNewLevel)
  { mCurrentVerbose = nNewLevel; return *this; }

  template< class T >
  CMessageQueue& operator<< (const T &o)
  { return output (o); }

  // ACCESS ---------------------------------------------------------------

  void SetVerbose (int nVerbose) { mVerbose = nVerbose; }
  const char* GetStr ();
  void Record () { if (mOst) delete mOst;  mOst = new ostrstream; }
  void Stop () { if (mOst) delete mOst;  mOst = 0; }

  // METHODS --------------------------------------------------------------

  CMessageQueue& output (const char *s);

  template< class T >
  CMessageQueue& output (const T &o)
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << o;
	*mStream << o;
      }
    return *this;
  }
};

#endif
