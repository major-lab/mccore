//                              -*- Mode: C++ -*- 
// Exception.h
// Copyright © 1999, 2000-04 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Martin Larose
// Created On       : Fri Dec 10 16:27:35 1999
// $Revision: 1.10 $
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


#ifndef _mccore_Exception_h_
#define _mccore_Exception_h_

#include <iostream>
#include <exception>
#include <string>

#include <string.h>
#include <errno.h>

using namespace std;



namespace mccore
{
  
  /**
   * @short General class of exceptions.
   *
   * May be used as the base class for all exceptions in the helpers and
   * libraries.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Exception.h,v 1.10 2006-08-14 14:43:56 thibaup Exp $
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
    Exception (const string &message) : mMessage (message) { }

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
     * Concatenates the current message with a long long integer.  Be careful when
     * using this operator, the returned exception is a Exception type NOT a
     * derived type.
     * @param integer the long long integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (long long int integer);

    /**
     * Concatenates the current message with an unsigned long long integer.  Be
     * careful when using this operator, the returned exception is a Exception
     * type NOT a derived type.
     * @param integer the unsigned long long integer to concatenate.
     * @return itself.
     */
    Exception& operator<< (unsigned long long int integer);

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
    virtual ostream& output (ostream& os) const
    {
      return os << mMessage;
    }
    
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
    LibException (const string &theMessage) : Exception (theMessage) { }
  
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
    FatalLibException (const string &theMessage) : LibException (theMessage) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalLibException (const FatalLibException &right)
      : LibException (right)
    { }
  
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
    string mFile;

    /**
     * The line number.
     */
    int mLine;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    IntLibException () : Exception (), mLine (-1) { }

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    IntLibException (const string &theMessage, const string &file = "", int line = -1)
      : Exception (theMessage), mFile (file), mLine (line)
    { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    IntLibException (const IntLibException &right)
      : Exception (right), mFile (right.mFile), mLine (right.mLine)
    { }

    /**
     * Destroys the exception.
     */
    virtual ~IntLibException () throw () { }

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
    const string& getFileName () const { return mFile; }

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
    NoSuchAtomException () 
      : IntLibException ("NoSuchAtomException: ") 
    { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    NoSuchAtomException (const string &message)
      : IntLibException ("NoSuchAtomException: " + message) 
    { }

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = "").
     * @param line the line number where the exception occured (default = -1).
     */
    NoSuchAtomException (const string &message, const string &file = "", int line = -1)
      : IntLibException ("NoSuchAtomException: " + message, file, line)
    { }

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    NoSuchAtomException (const NoSuchAtomException &right)
      : IntLibException (right)
    { }

    /**
     * Destructs the exception.
     */
    virtual ~NoSuchAtomException () throw () 
    { }

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

  };

  /**
   * @short Specialized internal exceptions 
   *
   * Thrown when a file is not found for opening.
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class FileNotFoundException : public IntLibException
  {
    string syserr_msg;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exception.
     */
    FileNotFoundException () 
      : IntLibException ("FileNotFoundException: "),
	syserr_msg (strerror (errno))
    { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    FileNotFoundException (const string &message)
      : IntLibException ("FileNotFoundException: " + message),
	syserr_msg (strerror (errno))
    { }

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = "").
     * @param line the line number where the exception occured (default = -1).
     */
    FileNotFoundException (const string &message, const string &file = "", int line = -1)
      : IntLibException ("FileNotFoundException: " + message, file, line),
	syserr_msg (strerror (errno))
    { }

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    FileNotFoundException (const FileNotFoundException &right)
      : IntLibException (right),
	syserr_msg (right.syserr_msg)
    { }

    /**
     * Destructs the exception.
     */
    virtual ~FileNotFoundException () throw () 
    { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    FileNotFoundException& operator= (const FileNotFoundException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

    virtual ostream& output (ostream &os) const;

  };


  /**
   * Exception for invalid access requests.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: Exception.h,v 1.10 2006-08-14 14:43:56 thibaup Exp $
   */
  class NoSuchElementException : public IntLibException
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.  mMessage contains "".
     */
    NoSuchElementException () : IntLibException ("NoSuchElementException: ") { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    NoSuchElementException (const string &message)
      : IntLibException ("NoSuchElementException: " + message) { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    NoSuchElementException (const string &message, const string &file = "", int line = -1)
      : IntLibException ("NoSuchElementException: " + message, file, line) { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    NoSuchElementException (const NoSuchElementException &right)
      : IntLibException (right)
    { }

    /**
     * Destructs the exception.
     */
    virtual ~NoSuchElementException () throw () { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    NoSuchElementException& operator= (const NoSuchElementException &right);
  
    // ACCESS ---------------------------------------------------------------

    // I/O ------------------------------------------------------------------
    
  };


  /**
   * @short Specialized internal exceptions 
   *
   * To prevent null pointer dereferencing.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   */
  class NullPointerException : public IntLibException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exception.
     */
    NullPointerException () : IntLibException () { }

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    NullPointerException (const string &theMessage, const string &file = "", int line = -1)
      : IntLibException (theMessage, file, line)
    { }

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    NullPointerException (const NullPointerException &right)
      : IntLibException (right)
    { }

    /**
     * Destroys the exception.
     */
    virtual ~NullPointerException () throw () {  }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    NullPointerException& operator= (const NullPointerException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

  };


  /**
   * @short Specialized internal exceptions 
   *
   * To prevent array, or vector, out of bound referencing.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   */
  class ArrayIndexOutOfBoundsException : public IntLibException
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exception.
     */
    ArrayIndexOutOfBoundsException () : IntLibException ("ArrayIndexOutOfBoundsException: ") { }

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = 0).
     * @param line the line number where the exception occured (default = -1).
     */
    ArrayIndexOutOfBoundsException (const string &theMessage, const string &file = "", int line = -1)
      : IntLibException ("ArrayIndexOutOfBoundsException: " + theMessage, file, line)
    { }

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    ArrayIndexOutOfBoundsException (const ArrayIndexOutOfBoundsException &right)
      : IntLibException (right)
    { }

    /**
     * Destroys the exception.
     */
    virtual ~ArrayIndexOutOfBoundsException () throw () {  }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    ArrayIndexOutOfBoundsException& operator= (const ArrayIndexOutOfBoundsException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

  };


  /**
   * @short Specialized internal exceptions (yet another)
   *
   * Thrown to report any type mismatch (AtomType, ResidueType, PropertyType).
   *
   * @author Philippe Thibault <thibaup@iro.umontreal.ca>
   */
  class TypeException : public IntLibException
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exception.
     */
    TypeException () 
      : IntLibException ("TypeException: ") 
    { }

    /**
     * Initializes the exeption with a message.
     * @param message the message string.
     */
    TypeException (const string &message)
      : IntLibException ("TypeException: " + message) 
    { }

    /**
     * Initializes the exception with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = "").
     * @param line the line number where the exception occured (default = -1).
     */
    TypeException (const string &message, const string &file = "", int line = -1)
      : IntLibException ("TypeException: " + message, file, line)
    { }

    /**
     * Initializes the exception with the right's content.
     * @param right the exception to copy.
     */
    TypeException (const TypeException &right)
      : IntLibException (right)
    { }

    /**
     * Destructs the exception.
     */
    virtual ~TypeException () throw () 
    { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the exception with the right's content.
     * @param right the exception to copy.
     * @return itself.
     */
    TypeException& operator= (const TypeException &right);

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O ------------------------------------------------------------------

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
     * @param file the file name where the exception occured (default = "").
     * @param line the line number where the exception occured (default = -1.
     */
    FatalIntLibException (const string &theMessage, const string &file = "", int line = -1)
      : IntLibException (theMessage, file, line)
    { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalIntLibException (const IntLibException &right)
      : IntLibException (right)
    { }

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
     */
    SocketException (const string &theMessage) : Exception (theMessage) { }

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
    string mFile;

    /**
     * The line number.
     */
    int mLine;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the exeption.
     */
    FatalSocketException () : Exception (), mLine (-1) { }

    /**
     * Initializes the exeption with a message and where it was produced.
     * @param theMessage the information string.
     * @param file the file where the exception occured (default = "").
     * @param line the line number where the exception occured (default = -1).
     */
    FatalSocketException (const string &theMessage, const string &file = "", int line = -1)
      : Exception (theMessage), mFile (file), mLine (line)
    { }

    /**
     * Initializes the exeption with the right's content.
     * @param right the exception to copy.
     */
    FatalSocketException (const FatalSocketException &right)
      : Exception (right), mFile (right.mFile), mLine (right.mLine)
    { }

    /**
     * Destroys the exception.
     */
    virtual ~FatalSocketException () throw () { }

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
    const string& getFileName () const { return mFile; }

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
     */
    ConnectionException (const string &theMessage)
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
  

  /**
   * Outputs the exception to another exception stream.
   * @param exs the hosting exception stream.
   * @param ex the exception to output.
   * @return the used exception stream.
   */
  Exception& operator<< (Exception& exs, const Exception& ex);
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
