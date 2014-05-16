// Binstream.h
// Copyright © 1999, 2000-04, 2014 Laboratoire de Biologie Informatique et Theorique.
//                           Universite de Montreal.
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


#ifndef _mccore_Binstream_h_
#define _mccore_Binstream_h_

#include <config.h>

#include <iostream>
#include <fstream>
#include <string>
#include <zlib.h>

#if defined (__FreeBSD__)
#include <sys/param.h>
#else
#include <netinet/in.h>
#endif

#include "Exception.h"
#include "sockstream.h"
#include "zstream.h"


// masks to split 64b in two 32b parts
#define BS_LS32BM (4294967295ULL)
#define BS_MS32BM (18446744069414584320ULL)

// extrema value for 16b integers
#define BS_UMAX16 (255)
#define BS_MAX16 (127)
#define BS_MIN16 (-128)

// extrema value for 32b integers
#define BS_UMAX32 (4294967295ULL)
#define BS_MAX32 (214748363LL)
#define BS_MIN32 (-214748364LL)


using namespace std;


namespace mccore
{

  typedef short bin_i16;
  typedef unsigned short bin_ui16;

  typedef int bin_i32;
  typedef unsigned int bin_ui32;

  typedef long long bin_i64;
  typedef unsigned long long bin_ui64;

  /**
   * @short Input binary stream for database and cache input.
   *
   * I/O binary stream.  These classes are defined to provide binary
   * read and write on basic types with the operators << and >> and to
   * give the opportunity to create ways to save user defined objets in
   * binary format.  Basic types uses read and write methods from
   * istream and ostream.  Each new class that needs to be saved in
   * binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   *
   * Type sizes:
   *
   * 16b: char, unsigned char, signed char, short, unsigned short.
   * 32b: int, unsigned, float.
   * 64b: long, unsigned long, long long, unsigned long long, double.
   *
   * char types are read from 16b data for compatibility with Java.
   * long types are read from 64b data for compatibility between 32b and 64b architectures. 
   */
  class iBinstream : public istream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.  Nothing to be done.
     */
    iBinstream () : istream (0) { }

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    iBinstream (streambuf *sb) : istream (sb) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Inputs character from binary stream.
     * Value is read from 16b data.
     * @param c the character to input.
     * @return itself.
     */
    iBinstream& operator>> (char& c);

    /**
     * Inputs unsigned character from binary stream.
     * Value is read from 16b data.
     * @param c the character to input.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char& c);

    /**
     * Inputs signed character from binary stream.
     * Value is read from 16b data.
     * @param c the character to input.
     * @return itself.
     */
    iBinstream& operator>> (signed char& c);

    /**
     * Inputs short integer from binary stream.
     * Value is read from 16b data.
     * @param s the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (short& s);

    /**
     * Inputs unsigned short integer from binary stream.
     * Value is read from 16b data.
     * @param s the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned short& s);

    /**
     * Inputs integer from binary stream.
     * Value is read from 32b data.
     * @param i the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (int& i);

    /**
     * Inputs unsigned integer from binary stream.
     * Value is read from 32b data.
     * @param i the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned int& i);

    /**
     * Inputs long integer from binary stream.
     * Value is read from 64b data.
     * @param li the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (long& li);

    /**
     * Inputs unsigned long integer from binary stream.
     * Value is read from 64b data.
     * @param li the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned long& li);

    /**
     * Inputs long long integer from binary stream.
     * Value is read from 64b data.
     * @param lli the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (long long& lli);

    /**
     * Inputs unsigned long long integer from binary stream.
     * Value is read from 64b data.
     * @param lli the integer to read.
     * @return itself.
     */
    iBinstream& operator>> (unsigned long long& lli);

    /**
     * Inputs float from binary stream.
     * Value is read from 32b data.
     * @param f the float to read.
     * @return itself.
     */
    iBinstream& operator>> (float& f);

    /**
     * Inputs double from binary stream.
     * Value is read from 64b data.
     * @param d the double to read.
     * @return itself.
     */
    iBinstream& operator>> (double& d);

    /**
     * Inputs booleans from the binary stream.
     * @param b the boolean to read.
     * @return itself.
     */
    iBinstream& operator>> (bool& b);

    /**
     * Inputs unknown size strings from the binary stream.  This operator read
     * an integer from the stream representing the string size, allocate a
     * space to read in the string.
     * @param str the string address where the new string will placed.
     * @return itself.
     */
    iBinstream& operator>> (char** cstr);

    /**
     * Inputs unknown size strings from the binary stream.  This operator read
     * an integer from the stream representing the string size, allocate a
     * space to read in the string.
     * @param str the string address where the new string will placed.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char** cstr);

    /**
     * Inputs unknown size strings from the binary stream.  This operator read
     * an integer from the stream representing the string size, allocate a
     * space to read in the string.
     * @param str the string address where the new string will placed.
     * @return itself.
     */
    iBinstream& operator>> (signed char** cstr);

    /**
     * Inputs known size strings from the binary stream.  To use with care,
     * the size of the input must be less than the size of the character
     * string given as parameter.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (char* cstr);

    /**
     * Inputs known size strings from the binary stream.  To use with care,
     * the size of the input must be less than the size of the character
     * string given as parameter.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (unsigned char* cstr);

    /**
     * Inputs known size strings from the binary stream.  To use with care,
     * the size of the input must be less than the size of the character
     * string given as parameter.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (signed char* cstr);

    /**
     * Inputs a strings from the binary stream.
     * @param str the string to put the characters in.
     * @return itself.
     */
    iBinstream& operator>> (string& str);

    /**
     * Inputs ios manipulation functions.
     * @param f is the ios manip fuction.
     * @return itself.
     */
    iBinstream& operator>> (ios& (*f)(ios&));

    /**
     * Inputs istream manipulation functions.
     * @param f is the istream manip function.
     * @return itself.
     */
    iBinstream& operator>> (istream& (*f)(istream&));

  protected:

    /**
     * @internal
     * Inputs 16b integer data. Throws an exception if the parameter isn't 16b.
     * @param data the variable to contain the 16b value read.
     * @exception FatalIntLibException
     */
    template< class t16 >
    iBinstream& read16 (t16& data) throw (FatalIntLibException)
    {
      if (sizeof (data) != 2)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to read 16 bits data in " 
           << sizeof (data) * 8 << " bits variable.";
         throw ex;
      }

      uint16_t data16;

      this->read ((char*)&data16, 2);
      data = ntohs (data16);

      return *this;
    }

    /**
     * @internal
     * Inputs 32b integer data. Throws an exception if the parameter isn't 32b.
     * @param data the variable to contain the 32b value read.
     * @exception FatalIntLibException
     */
    template< class t32 >
    iBinstream& read32 (t32& data) throw (FatalIntLibException)
    {
      if (sizeof (data) != 4)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to read 32 bits data in " 
           << sizeof (data) * 8 << " bits variable.";
        throw ex;
      }

      uint32_t data32;

      this->read ((char*)&data32, 4);
      data = ntohl (data32);

      return *this;
    }

    /**
     * @internal
     * Inputs 64b integer data. Throws an exception if the parameter isn't 64b.
     * @param data the variable to contain the 64b value read.
     * @exception FatalIntLibException
     */
    template< class t64 >
    iBinstream& read64 (t64& data) throw (FatalIntLibException)
    {
      if (sizeof (data) != 8)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to read 64 bits data in a " 
           << sizeof (data) * 8 << " bits variable.";
        throw ex;
      }

      uint32_t data32;
      mccore::bin_ui64 data64;

      // -- most significant 32 bits
      this->read ((char*)&data32, 4);
      data64 = (mccore::bin_ui64)ntohl (data32) << 32;

      // -- least significant 32 bits
      this->read ((char*)&data32, 4);

      // -- merge
      data = data64 | (mccore::bin_ui64)ntohl (data32);

      return *this;
    }

  public:

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Opens the stream.
     */
    void open () { }

    /**
     * Closes the stream.
     */
    virtual void close () { }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Output binary stream for database and cache output.
   *
   * I/O binary stream basically used for the MCSYM database and cache.  These
   * classes are defined to provide binary read and write on basic types with
   * the operators << and >> and to give the opportunity to create ways to
   * save user defined objets in binary format.  Basic types uses read and
   * write methods from istream and ostream.  Each new class that needs to be
   * saved in binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   *
   * Type sizes:
   *
   * 16b: char, unsigned char, signed char, short, unsigned short.
   * 32b: int, unsigned, float.
   * 64b: long, unsigned long, long long, unsigned long long, double.
   *
   * char types are written as 16b data for compatibility with Java.
   * long types are written as 64b data for compatibility between 32b and 64b architectures. 
   */
  class oBinstream : public ostream
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.  Nothing to be done.
     */
    oBinstream () : ostream (0) { }

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    oBinstream (streambuf *sb) : ostream (sb) { }

    // OPERATORS ------------------------------------------------------------

    /**
     * Outputs character to binary stream.
     * Value is written as 16b data.
     * @param c the character to output.
     * @return itself.
     */
    oBinstream& operator<< (char c);

    /**
     * Outputs unsigned character to binary stream.
     * Value is written as 16b data.
     * @param c the character to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned char c);

    /**
     * Outputs signed character to binary stream.
     * Value is written as 16b data.
     * @param c the character to output.
     * @return itself.
     */
    oBinstream& operator<< (signed char c);

    /**
     * Outputs short integer to binary stream.
     * Value is written as 16b data.
     * @param s the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (short s);

    /**
     * Outputs unsigned short integer to binary stream.
     * Value is written as 16b data.
     * @param s the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned short s);

    /**
     * Outputs integer to binary stream.
     * Value is written as 32b data.
     * @param i the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (int i);

    /**
     * Outputs unsigned integer to binary stream.
     * Value is written as 32b data.
     * @param i the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned int i);

    /**
     * Outputs long integer to binary stream.
     * Value is written as 64b data.
     * @param li the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (long li);

    /**
     * Outputs unsigned long integer to binary stream.
     * Value is written as 64b data.
     * @param li the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned long li);

    /**
     * Outputs long long integer to binary stream.
     * Value is written as 64b data.
     * @param lli the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (long long lli);

    /**
     * Outputs unsigned long long integer to binary stream.
     * Value is written as 64b data.
     * @param lli the integer to output.
     * @return itself.
     */
    oBinstream& operator<< (unsigned long long lli);

    /**
     * Outputs float to binary stream.
     * Value is written as 32b data.
     * @param f the float to output.
     * @return itself.
     */
    oBinstream& operator<< (float f);

    /**
     * Outputs double to binary stream.
     * Value is written as 64b data.
     * @param d the double to output.
     * @return itself.
     */
    oBinstream& operator<< (double d);

    /**
     * Outputs strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const char* cstr);

    /**
     * Outputs strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const unsigned char* cstr);

    /**
     * Outputs strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const signed char* cstr);

    /**
     * Outputs strings.
     * @param str the string to output.
     * @return itself.
     */
    oBinstream& operator<< (const string& str);

    /**
     * Outputs boolean value to binary stream.
     * @param b the boolean value to write.
     * @return itself.
     */
    oBinstream& operator<< (bool b);

    /**
     * Manipulates ios output.
     * @param func is the ios manip fuction.
     * @return itself.
     */
    oBinstream& operator<< (ios& (*func)(ios&));

    /**
     * Manipulates ostream output.
     * @param func is the ostream manip function.
     * @return itself.
     */
    oBinstream& operator<< (ostream& (*func)(ostream&));

  protected:

    /**
     * @internal
     * Outputs 16b integer data. Throws an exception if the parameter isn't 16b.
     * @param data the 16b value to write.
     * @exception FatalIntLibException
     */
    template< class t16 >
    oBinstream& write16 (t16 data) throw (FatalIntLibException)
    {
      if (sizeof (data) != 2)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to write 16 bits data from " 
           << sizeof (data) * 8 << " bits variable.";
        throw ex;
      }

      uint16_t data16 = htons (data);
      this->write ((char*)&data16, 2);
      return *this;
    }

    /**
     * @internal
     * Outputs 32b integer data. Throws an exception if the parameter isn't 32b.
     * @param data the 32b value to write.
     * @exception FatalIntLibException
     */
    template< class t32 >
    oBinstream& write32 (t32 data) throw (FatalIntLibException)
    {
      if (sizeof (data) != 4)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to write 32 bits data from " 
           << sizeof (data) * 8 << " bits variable.";
        throw ex;
      }

      uint32_t data32 = htonl (data);
      this->write ((char*)&data32, 4);
      return *this;
    }

    /**
     * @internal
     * Outputs 64b integer data. Throws an exception if the parameter isn't 64b.
     * @param data the 64b value to write.
     * @exception FatalIntLibException
     */
    template< class t64 >
    oBinstream& write64 (t64 data)
    {
      if (sizeof (data) != 8)
      {
        FatalIntLibException ex ("", __FILE__, __LINE__);
        ex << "trying to write 64 bits data from " 
           << sizeof (data) * 8 << " bits variable.";
        throw ex;
      }

      uint32_t data32 = htonl (((data & BS_MS32BM) >> 32) & BS_LS32BM);
      this->write ((char*)&data32, 4); // most significant 32 bits
      data32 = htonl (data & BS_LS32BM); 
      this->write ((char*)&data32, 4); // least significant 32 bits
      return *this;
    }

  public:

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Opens the stream.
     */
    void open () { }

    /**
     * Closes the stream.
     */
    virtual void close () { }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short General binary stream for database and cache I/O.
   *
   * I/O binary stream basically used for the MCSYM database and cache.  These
   * classes are defined to provide binary read and write on basic types with
   * the operators << and >> and to give the opportunity to create ways to
   * save user defined objets in binary format.  Basic types uses read and
   * write methods from istream and ostream.  Each new class that needs to be
   * saved in binary format must define operators << and >> on iBinstream and
   * oBinstream in their class implementation.
   *
   * Binary streams saves the types according to the big endianness
   * which is the standard on network protocols.  Types are converted
   * from little endianness to big on read and write on system that uses
   * this encoding.
   */
  class Binstream : public iBinstream, public oBinstream
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    Binstream () : iBinstream (), oBinstream () { }

    /**
     * Initializes the stream with a predefined stream buffer.
     * @param sb the stream buffer.
     */
    Binstream (streambuf *sb) : iBinstream (sb), oBinstream (sb) { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Opens the stream.
     */
    void open () { }

    /**
     * Closes the stream.
     */
    virtual void close () { }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Input binary file streams.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   */
  class ifBinstream : public iBinstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the objet.
     */
    ifBinstream () : iBinstream (), buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    ifBinstream (const char *name, ios_base::openmode mode = ios_base::in)
    : iBinstream (),
      buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode))
        this->setstate (ios::failbit);
      iBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      iBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Output binary file stream.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   */
  class ofBinstream : public oBinstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    ofBinstream () : oBinstream (), buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out).
     */
    ofBinstream (const char *name, ios_base::openmode mode = ios_base::out)
    : oBinstream (),
      buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name and optional mode and protection.
     * @param name the path and file name to open.
     * @param mode the open mode (default = ios_base::out).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc)
    {
      if (! buf.open (name, mode | ios_base::out))
        this->setstate (ios::failbit);
      oBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      oBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short General binary file stream.
   *
   * Implementation of binary file streams, based on fstreambase and
   * Binstream.  These streams are used for binary dumps in files.  The
   * general layout is based on fstream while I/O operators comes from
   * Binstream.
   */
  class fBinstream : public Binstream
  {
    /**
     * The stream buffer.
     */
    mutable filebuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    fBinstream ()
    : Binstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in | ios_base::out).
     */
    fBinstream (const char *name, ios_base::openmode mode = ios_base::in | ios_base::out)
    : Binstream (),
      buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    filebuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in | ios_base::out).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in | ios_base::out)
    {
      if (! buf.open (name, mode))
        this->setstate (ios::failbit);
      Binstream::open ();
    }

    /**
     * Closes the stream.
     */
    virtual void close ()
    {
      Binstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Compressed input binary stream.
   *
   * I/O general classes using the GNU zip compression system.  These streams
   * adds the compression on the normal binary streams.  The input stream can
   * read an uncompressed file.  When creating a output stream the programmer
   * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
   * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
   * of compression level 0 is not recommended: the data is not compressed but
   * a gzip dependent header an footer is added to the file.  It is preferable
   * to use the fBinstream classes for uncompressed output binary streams.
   * For further details see @ref iBinstream and @ref zfstreambase.  Note that
   * the compression level is not used in input streams.
   */
  class izfBinstream : public iBinstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    izfBinstream () : iBinstream (), buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    izfBinstream(const char *name, ios_base::openmode mode = ios_base::in)
    : iBinstream (),
      buf ()
    {
      this->init (&buf);
      this->open (name, mode);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::in).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::in)
    {
      if (! buf.open (name, mode | ios_base::in))
        this->setstate (ios::failbit);
      iBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      iBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Compressed output binary stream.
   *
   * I/O general classes using the GNU zip compression system.  These streams
   * adds the compression on the normal binary streams.  The input stream can
   * read an uncompressed file.  When creating a output stream the programmer
   * can specify a compression level from 0 (Z_NO_COMPRESSION) to 9
   * (Z_BEST_COMPRESSION), the default is level 1 (Z_BEST_SPEED).  The usage
   * of compression level 0 is not recommended: the data is not compressed but
   * a gzip dependent header an footer is added to the file.  It is preferable
   * to use the fBinstream classes for uncompressed output binary streams.
   * For further details see @ref oBinstream and @ref zfstreambase.
   */
  class ozfBinstream : public oBinstream
  {
    /**
     * The compressed stream buffer.
     */
    mutable zstreambuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    ozfBinstream ()
    : oBinstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out).
     * @param level the compression level for output.
     */
    ozfBinstream (const char *name, ios_base::openmode mode = ios_base::out, int level = Z_BEST_SPEED)
    : oBinstream (),
      buf()
    {
      this->init (&buf);
      this->open (name, mode, level);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    zstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with file name and parameters.
     * @param name the path and file name to open.
     * @param mode the open mode (default ios_base::out | ios_base::trunc).
     * @param level the compression level for output (default Z_BEST_SPEED).
     */
    void open (const char *name, ios_base::openmode mode = ios_base::out | ios_base::trunc, int level = Z_BEST_SPEED)
    {
      if (! buf.open (name, mode | ios_base::out, level))
        this->setstate (ios::failbit);
      oBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      oBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Input binary socket streams.
   *
   * Implementation of binary socket streams.  These streams are used for
   * binary dumps in sockets.  The general layout is based on fstream while
   * I/O operators comes from Binstream.
   */
  class isBinstream : public iBinstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the objet.
     */
    isBinstream ()
    : iBinstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes a socket stream from an existing (opened) socket id
     * @param s a socket created by accept(2) or socket(2)
     */
    isBinstream (int s)
    : iBinstream (),
      buf (s)
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    isBinstream (const char *host, unsigned int port)
    : iBinstream (),
      buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
        this->setstate (ios::failbit);
      iBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      iBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short Output binary file stream.
   *
   * Implementation of binary socket streams These streams are used for
   * binary dumps in sockets.  The general layout is based on fstream while
   * I/O operators comes from Binstream.
   */
  class osBinstream : public oBinstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    osBinstream ()
    : oBinstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes a socket stream from an existing (opened) socket id
     * @param s a socket created by accept(2) or socket(2)
     */
    osBinstream (int s)
    : oBinstream (),
      buf (s)
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    osBinstream (const char *host, unsigned int port)
    : oBinstream (),
      buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
        this->setstate (ios::failbit);
      oBinstream::open ();
    }

    /**
     * Closes the stream.
     */
    void close ()
    {
      oBinstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };


  /**
   * @short General binary socket stream.
   *
   * Implementation of binary socket streams.  These streams are used for
   * binary dumps in sockets.  The general layout is based on fstream while
   * I/O operators comes from Binstream.
   */
  class sBinstream : public Binstream
  {
    /**
     * The stream buffer.
     */
    mutable sockstreambuf buf;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the stream.
     */
    sBinstream ()
    : Binstream (),
      buf ()
    {
      this->init (&buf);
    }

    /**
     * Initializes a socket stream from an existing (opened) socket id
     * @param s a socket created by accept(2) or socket(2)
     */
    sBinstream (int s)
    : Binstream (),
      buf (s)
    {
      this->init (&buf);
    }

    /**
     * Initializes the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    sBinstream (const char *host, unsigned int port)
      : Binstream (),
        buf ()
    {
      this->init (&buf);
      this->open (host, port);
    }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Gets the file buffer.
     * @return the file buffer.
     */
    sockstreambuf* rdbuf () const { return &buf; }

    /**
     * Tells if the buf is open.
     * @return whether buf is open.
     */
    bool is_open () const { return buf.is_open (); }

    /**
     * Opens the stream with host name and port.
     * @param host the host name.
     * @param port the port number.
     */
    void open (const char *host, unsigned int port)
    {
      if (! buf.open (host, port))
        this->setstate (ios::failbit);
      Binstream::open ();
    }

    /**
     * Closes the stream.
     */
    virtual void close ()
    {
      Binstream::close ();
      if (! buf.close ())
        this->setstate (ios::failbit);
    }

    // I/O ------------------------------------------------------------------
  };
}

#endif
