// AtomFactoryMethod.h
// Copyright © 2014 Laboratoire d'ingenierie des ARN.
//                  Universite de Montreal.
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


#ifndef _mccore_AtomFactoryMethod_h_
#define _mccore_AtomFactoryMethod_h_


namespace mccore
{
  class Atom;
  class iBinstream;
  class oBinstream;

  /**
   * @short Abstract class for atom factory methods.
   *
   * This class is used in Residue to generate a given type of atom on input
   * methods.
   */
  class AtomFactoryMethod
  {

    public:
      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object.
       */
      AtomFactoryMethod () { }

      /**
       * Copies the object.
       */
      virtual AtomFactoryMethod* clone () const = 0;

      /**
      * Destroys the object.
      */
      virtual ~AtomFactoryMethod () { }

      // OPERATORS ------------------------------------------------------------

      // ACCESS ---------------------------------------------------------------

      // METHODS --------------------------------------------------------------

      /**
       * Creates the atom.
       * @return the newly created atom.
       */
      virtual Atom* createAtom () const = 0;

      /**
       * Creates an atom copy.
       * @param aAtom the atom to copy from.
       * @return the newly created atom copy.
       */
      virtual Atom* createAtom (const Atom& aAtom) const = 0;

      // I/O  -----------------------------------------------------------------

      /**
       * Creates a new object as read from the input binary stream. Throws a
       * @ref FatalIntLibException if read fails.
       * @param ibs the input binary stream
       * @return the newly created object.
       * @throws FatalIntLibException
       */
      static AtomFactoryMethod* read (iBinstream& ibs);

      /**
       * Writes the object to the output stream.
       * @param obs the output stream.
       * @return the written stream.
       */
      virtual oBinstream& write (oBinstream& obs) const = 0;
  };


  /**
   * @short AtomFactoryMethod implementation for Atom class.
   *
   * This is the atom factory method implementation for the Basic Atom
   * class.
   */
  class AtomFM : public AtomFactoryMethod
  {

    public:
      // LIFECYCLE ------------------------------------------------------------

      /**
       * Initializes the object.
       */
      AtomFM () { }

      /**
       * Clones the object.
       * @return the copy of the object.
       */
      virtual AtomFactoryMethod* clone () const { return new AtomFM (); }

      /**
       * Destroys the object.
       */
      virtual ~AtomFM () { }

      // OPERATORS ------------------------------------------------------------

      // ACCESS ---------------------------------------------------------------

      // METHODS --------------------------------------------------------------

      /**
       * Creates a new atom of Atom type.
       * @return the newly created empty atom.
       */
      virtual Atom* createAtom () const;

      /**
       * Creates an atom copy.
       * @param aAtom the atom to copy from.
       * @return the newly created atom copy.
       */
      virtual Atom* createAtom (const Atom& aAtom) const;

      // I/O  -----------------------------------------------------------------

      /**
       * Writes the object to the output stream.
       * @param obs the output stream.
       * @return the written stream.
       */
      virtual oBinstream& write (oBinstream& obs) const;

  };


  /**
  * Writes a @ref AtomFactoryMethod object to the output stream.
  * @param obs the output stream.
  * @param obj the @ref AtomFactoryMethod object to write
  * @return the written stream.
  */
  oBinstream& operator<< (oBinstream& obs, const AtomFactoryMethod& obj);

}

#endif
