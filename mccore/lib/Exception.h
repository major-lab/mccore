//                              -*- Mode: C++ -*- 
// Exception.h
// Copyright © 1999, 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose
// Created On       : Fri Dec 10 16:27:35 1999
// $Revision: 1.4.2.2 $
// $Id: Exception.h,v 1.4.2.2 2004-12-23 15:51:49 larosem Exp $
//
// This file is part of mccore.
// 
// mccore is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// mccore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with mccore; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _Exception_h_
#define _Exception_h_


#include <iostream>
#include <exception>
#include <string>

using namespace std;



namespace mccore
{
  
  /**
   * @short General class of exceptions.
   *
   * May be used as the base class for all exceptions in the helpers and
   * libraries.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class Exception : public exception
  {
    /**
     * The information message about the exception.
     */
    string mMessage;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.  mMessage contains "".
     */
    Exception () { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    Exception (const char *message) : mMessage (message) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    Exception (const Exception &right) : mMessage (right.mMessage) { }

    /**
     * Destructs the exception.
     */
    virtual ~Exception () throw () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    Exception& operator= (const Exception &right);
  
    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the message.  Deprecated method, use the what () method instead.
     * @return the message string.
     * @deprecated Use the what method instead.
     */
    const char* GetMessage () const { return mMessage.c_str (); }

    /**
     * Gets the message.
     * @return the message string.
     */
    virtual const char* what () const throw () { return mMessage.c_str (); }

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

    /**
     * Concatenates the current message with a string.  Be careful when using
     * this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param message the string to concatenate.
     * @return itself.
     */
    Exception& operator<< (const char *message);

    /**
     * Concatenates the current message with a string.  Be careful when using
     * this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param message the string to concatenate.
     * @return itself.
     */
    Exception& operator<< (const string &message);

    /**
     * Concatenates the current message with an integer.  Be careful when using
     * this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param integer the integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (int integer);

    /**
     * Concatenates the current message with an unsigned integer.  Be careful
     * when using this operator, the returned exception is a Exception type
     * NOT a derived type.
     * @param integer the unsigned integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (unsigned int integer);

    /**
     * Concatenates the current message with a long integer.  Be careful when
     * using this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param integer the long integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (long int integer);

    /**
     * Concatenates the current message with an unsigned long integer.  Be
     * carefulwhen using this operator, the returned exception is a Exception
     * type NOT a derived type.
     * @param integer the unsigned long integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (unsigned long int integer);

    /**
     * Concatenates the current message with a float.  Be careful when using
     * this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param float_val the float to concatenate.
     * @return itself.
     */
    Exception& operator<< (float float_val);

    /**
     * Concatenates the current message with a character.  Be careful when
     * using this operator, the returned exception is a Exception type NOT a
     * derived type. 
     * @param theChar the character to concatenate.
     * @return itself.
     */
    Exception& operator<< (char theChar);
  
    /** 
     * Outputs the message to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream& os) const;
  };  


  /**
   * @short Interruption exception.
   *
   * This exception is used in the Status Manager to signal an interrupt
   * signal.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class InterruptException : public Exception
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    InterruptException () : Exception () { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    InterruptException (const InterruptException &right)
      : Exception (right) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    InterruptException& operator= (const InterruptException &right);

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
  class LibException : public Exception
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    LibException () : Exception () { }

    /**
     * Initializes the exeption with a message.
     * @param theMessage the information message.
     */
    LibException (const char *theMessage) : Exception (theMessage) { }
  
    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    LibException (const LibException &right) : Exception (right) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    LibException& operator= (const LibException &right);

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
  class FatalLibException : public LibException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    FatalLibException () : LibException () { }

    /**
     * Initializes the exeption with a message.
     * @param theMessage the information message.
     */
    FatalLibException (const char *theMessage) : LibException (theMessage) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalLibException (const FatalLibException &right)
      : LibException (right) { }
  
    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    FatalLibException& operator= (const FatalLibException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------
  };



  /**
   * @short Exceptions for internal errors.
   *
   * This exception class is specific for library exceptions.  This class is
   * reserved for internal errors.  It is not needed to terminate the
   * execution for this kind of exception.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class IntLibException : public Exception
  {
    
  protected:
    
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
    IntLibException ();

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    IntLibException (const char *theMessage,
		      const char *file = 0,
		      int line = -1);

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    IntLibException (const IntLibException &right);

    /**
     * Destructs the exception.
     */
    virtual ~IntLibException () throw () { delete[] mFile; }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    IntLibException& operator= (const IntLibException &right);

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the file name where the exception occured.
     * @return the file name.
     */
    const char* getFileName () const { return mFile; }

    /**
     * Gets the line number where the exception occured.
     * @return the line number.
     */
    int getLine () const { return mLine; }

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

    /**
     * Outputs the IntLibException and FatalIntLibException exception
     * messages.  Prints the filename, the line number, the message and a bug
     * notice.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
  };


  /**
   * @short Specialized internal exceptions 
   *
   * Thrown when a requested atom is not found within a residue.
   * It is not needed to terminate the execution for this kind of exception.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class NoSuchAtomException : public IntLibException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exception.
     */
    NoSuchAtomException ();

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    NoSuchAtomException (const char *theMessage,
			 const char *file = 0,
			 int line = -1);

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    NoSuchAtomException (const NoSuchAtomException &right);

    /**
     * Destructs the exception.
     */
    virtual ~NoSuchAtomException () throw () {  }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    NoSuchAtomException& operator= (const NoSuchAtomException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

    /**
     * Outputs the NoSuchAtomException exception
     * messages.  Prints the filename, the line number, the message and a bug
     * notice.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
  };


  /**
   * @short Fatal internal exceptions.
   *
   * This exception class is specific for library exceptions.  This class is
   * reserved for internal errors.  It is needed to terminate the execution
   * for this kind of exception.
   *
   * @author Martin Larose <larosem@iro.umontreal.ca>
   */
  class FatalIntLibException : public IntLibException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    FatalIntLibException () : IntLibException () { }

    /**
     * Initializes the exeption with a message and a file position.
     * @param theMessage the information string.
     * @param file the file name where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1.
     */
    FatalIntLibException (const char *theMessage,
			  const char *file = 0,
			  int line = -1)
      : IntLibException (theMessage, file, line) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalIntLibException (const IntLibException &right)
      : IntLibException (right) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    FatalIntLibException& operator= (const FatalIntLibException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------
  };

  /**
   * @short Exceptions produced by sockets.
   *
   * This exception class is specific for socket exceptions.  This class is
   * reserved for error caused by sockets manipulation.  It is not needed to
   * terminate the execution for this kind of exception.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class SocketException : public Exception
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    SocketException () : Exception () { } ;

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    SocketException (const char *theMessage) : Exception (theMessage) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    SocketException (const SocketException &right) : Exception (right) { }


    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    SocketException& operator= (const SocketException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------
  };



  /**
   * @short Fatal exceptions produced by sockets.
   *
   * This exception class is specific for socket exceptions.  This class is
   * reserved for error caused by socket manipulation.  It is needed to 
   * terminate the execution for this kind of exception.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class FatalSocketException : public Exception
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
    FatalSocketException ();

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    FatalSocketException (const char *theMessage,
			   const char *file = 0,
			   int line = -1);

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalSocketException (const FatalSocketException &right);

    /**
     * Destructs the exception.
     */
    ~FatalSocketException () throw () { delete[] mFile; }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    FatalSocketException& operator= (const FatalSocketException &right);

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the file name where the exception occured.
     * @return the file name.
     */
    const char* getFileName () const { return mFile; }

    /**
     * Gets the line number where the exception occured.
     * @return the line number.
     */
    int getLine () const { return mLine; }

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

    /**
     * Outputs the FatalSocketException exception
     * messages.  Prints the filename, the line number and the message.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
  };



  /**
   * @short Fatal exceptions produced by a connection to a socket.
   *
   * This exception class is specific for socket connection.  This class is
   * reserved for error caused by connections to sockets.  It is needed to 
   * terminate the execution for this kind of exception.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class ConnectionException : public SocketException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    ConnectionException () : SocketException () { }

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    ConnectionException (const char *theMessage)
      : SocketException (theMessage)
    { }
    

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    ConnectionException (const ConnectionException &right)
      : SocketException (right)
    { }

    /**
     * Destructs the exception.
     */
    virtual ~ConnectionException () throw () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    ConnectionException& operator= (const ConnectionException &right);

    // ACCESS ---------------------------------------------------------------

 

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------
  };
  
}

namespace std
{
   
  /**
   * Outputs the message to the stream.
   * @param os the output stream.
   * @param exc the exception to display.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const mccore::Exception &exc);
  

}
  
#endif
