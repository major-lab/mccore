//                              -*- Mode: C++ -*- 
// CException.h
// Copyright � 1999, 2000-01 Laboratoire de Biologie Informatique et Th�orique.
// Author           : Martin Larose
// Created On       : Fri Dec 10 16:27:35 1999
// Last Modified By : Martin Larose
// Last Modified On : Tue Jan 23 15:01:34 2001
// Update Count     : 10
// Status           : Unknown.
// 


#ifndef _CException_h_
#define _CException_h_


class ostream;



/**
 * @short General class of exceptions.
 *
 * May be used as the base class for all exceptions in the helpers and
 * libraries.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CException
{
  /**
   * The information message about the exception.
   */
  char *mMessage;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.  mMessage contains "".
   */
  CException ();

  /**
   * Initializes the exeption with a message.
   * @param message the message string.
   */
  CException (const char *message);

  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CException (const CException &right);

  /**
   * Destructs the exception.
   */
  ~CException () { delete[] mMessage; }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CException& operator= (const CException &right);
  
  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the message.
   * @return the message string.
   */
  const char* GetMessage () const { return mMessage; }

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------

  /**
   * Concatenates the current message with a string.  Be careful when using
   * this operator, the returned exception is a CException type NOT a
   * derived type.
   * @param message the string to concatenate.
   * @return itself.
   */
  CException& operator<< (const char *message);

  /**
   * Concatenates the current message with an integer.  Be careful when using
   * this operator, the returned exception is a CException type NOT a
   * derived type.
   * @param integer the integer to concatenate.
   * @return itself.
   */
  CException& operator<< (int integer);

  /**
   * Concatenates the current message with an unsigned integer.  Be careful
   * when using this operator, the returned exception is a CException type
   * NOT a derived type.
   * @param integer the unsigned integer to concatenate.
   * @return itself.
   */
  CException& operator<< (unsigned int integer);

  /**
   * Concatenates the current message with a float.  Be careful when using
   * this operator, the returned exception is a CException type NOT a
   * derived type.
   * @param float_val the float to concatenate.
   * @return itself.
   */
  CException& operator<< (float float_val);

  /**
   * Concatenates the current message with a character.  Be careful when
   * using this operator, the returned exception is a CException type NOT a
   * derived type. 
   * @param theChar the character to concatenate.
   * @return itself.
   */
  CException& operator<< (char theChar);
};  



/**
 * Outputs the message to the stream.
 * @param os the output stream.
 * @param exc the exception to display.
 * @return the used output stream.
 */
ostream& operator<< (ostream &os, const CException &exc);



/**
 * @short Interruption exception.
 *
 * This exception is used in the Status Manager to signal an interrupt
 * signal.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CInterruptException : public CException
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.
   */
  CInterruptException () : CException () { }

  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CInterruptException (const CInterruptException &right)
    : CException (right) { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CInterruptException& operator= (const CInterruptException &right);

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------
};



/**
 * @short Exceptions produced by users.
 *
 * This exception class is specific for library exceptions.  This class is
 * reserved for error caused by users.  It is not needed to terminate the
 * execution for this kind of exception.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CLibException : public CException
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.
   */
  CLibException () : CException () { }

  /**
   * Initializes the exeption with a message.
   * @param theMessage the information message.
   */
  CLibException (const char *theMessage) : CException (theMessage) { }
  
  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CLibException (const CLibException &right) : CException (right) { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CLibException& operator= (const CLibException &right);

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------
};



/**
 * @short Fatal exceptions produced by users.
 *
 * This exception class is specific for library exception.  This class is
 * reserved for error caused by users.  It is needed to terminate the
 * execution for this kind of exception.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CFatalLibException : public CLibException
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.
   */
  CFatalLibException () : CLibException () { }

  /**
   * Initializes the exeption with a message.
   * @param theMessage the information message.
   */
  CFatalLibException (const char *theMessage) : CLibException (theMessage) { }

  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CFatalLibException (const CFatalLibException &right)
    : CLibException (right) { }
  
  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CFatalLibException& operator= (const CFatalLibException &right);

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------
};



/**
 * @short Exceptions fo internal errors.
 *
 * This exception class is specific for library exceptions.  This class is
 * reserved for internal errors.  It is not needed to terminate the
 * execution for this kind of exception.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CIntLibException : public CException
{
  /**
   * The file name.
   */
  char *mFile;

  /**
   * The line number.
   */
  int mLine;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.
   */
  CIntLibException ();

  /**
   * Initializes the exeption with a message and where it was produced.
   * @param theMessage the information string.
   * @param file the file where the exception occured (default = 0).
   * @param line the line number where the exception occured (default = -1).
   */
  CIntLibException (const char *theMessage,
		    const char *file = 0,
		    int line = -1);

  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CIntLibException (const CIntLibException &right);

  /**
   * Destructs the exception.
   */
  ~CIntLibException () { delete[] mFile; }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CIntLibException& operator= (const CIntLibException &right);

  // ACCESS ---------------------------------------------------------------

  /**
   * Gets the file name where the exception occured.
   * @return the file name.
   */
  const char* GetFileName () const { return mFile; }

  /**
   * Gets the line number where the exception occured.
   * @return the line number.
   */
  int GetLine () const { return mLine; }

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------
};



/**
 * Outputs the CIntLibException and CFatalIntLibException exception
 * messages.  Prints the filename, the line number, the message and a bug
 * notice.
 * @param os the output stream.
 * @param exc the exception to display.
 * @return the used output stream.
 */
ostream& operator<< (ostream &os, const CIntLibException &exc);



/**
 * @short Fatal internal exceptions.
 *
 * This exception class is specific for library exceptions.  This class is
 * reserved for internal errors.  It is needed to terminate the execution
 * for this kind of exception.
 *
 * @author Martin Larose <larosem@iro.umontreal.ca>
 */
class CFatalIntLibException : public CIntLibException
{

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the exeption.
   */
  CFatalIntLibException () : CIntLibException () { }

  /**
   * Initializes the exeption with a message and a file position.
   * @param theMessage the information string.
   * @param file the file name where the exception occured (default = 0).
   * @param line the line number where the exception occured (default = -1.
   */
  CFatalIntLibException (const char *theMessage,
			 const char *file = 0,
			 int line = -1)
    : CIntLibException (theMessage, file, line) { }

  /**
   * Initializes the exeption with the right's content.
   * @param right the exception to copy.
   */
  CFatalIntLibException (const CIntLibException &right)
    : CIntLibException (right) { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the exception with the right's content.
   * @param right the exception to copy.
   * @return itself.
   */
  const CFatalIntLibException& operator= (const CFatalIntLibException &right);

  // ACCESS ---------------------------------------------------------------

  // METHODS --------------------------------------------------------------

  // I/O ------------------------------------------------------------------
};

#endif
