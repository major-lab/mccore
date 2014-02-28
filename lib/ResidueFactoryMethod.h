//                              -*- Mode: C++ -*- 
// ResidueFactoryMethod.h
// Copyright © 2001-04 Laboratoire de Biologie Informatique et Théorique.
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct 12 14:31:19 2001
// $Revision: 1.7 $
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


#ifndef _mccore_ResidueFactoryMethod_h_
#define _mccore_ResidueFactoryMethod_h_



namespace mccore
{
  class Residue;
  class AtomFactoryMethod;
  class iBinstream;
  class oBinstream;

  /**
   * @short Abstract class for residue factory methods.
   *
   * This class is used in Model to generate a given type of residue on input
   * methods.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ResidueFactoryMethod.h,v 1.7 2005-02-25 16:48:14 thibaup Exp $
   */
  class ResidueFactoryMethod
  {
  protected:
	/**
	 * The Atom factory method to include in generated residues.
	 */
	AtomFactoryMethod* mpAtomFM;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ResidueFactoryMethod (const AtomFactoryMethod *fm = 0);

    /**
     * Initializes the object with the right content.
     * @param right the object to copy.
     */
    ResidueFactoryMethod (const ResidueFactoryMethod &right);

    /**
     * Copies the object.
     */
    virtual ResidueFactoryMethod* clone () const = 0;
  
    /**
     * Destroys the object.
     */
    virtual ~ResidueFactoryMethod ();

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Creates the residue.
     * @return the newly created empty residue.
     */
    virtual Residue* createResidue () const = 0;

    /**
     * Creates a residue copy.
     * @param res the residue to copy from.
     * @return the newly created residue copy.
     */
    virtual Residue* createResidue (const Residue& res) const = 0;

    // I/O  -----------------------------------------------------------------

    /**
     * Creates a new object as read from the input binary stream. Throws a
     * @ref FatalIntLibException if read fails.
     * @param ibs the input binary stream
     * @return the newly created object.
     * @throws FatalIntLibException
     */
    static ResidueFactoryMethod* read (iBinstream& ibs);

    /**
     * Writes the object to the output stream.
     * @param obs the output stream.
     * @return the written stream.
     */
    virtual oBinstream& write (oBinstream& obs) const = 0;

  };
  

  /**
   * @short ResidueFactoryMethod implementation for Residue class.
   *
   * This is the residue factory method implementation for the BasicResidue
   * class.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ResidueFactoryMethod.h,v 1.7 2005-02-25 16:48:14 thibaup Exp $
   */
  class ResidueFM : public ResidueFactoryMethod
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ResidueFM (const AtomFactoryMethod *fm = 0) : ResidueFactoryMethod(fm) { }

    /**
     * Clones the object.
     * @return the copy of the object.
     */
    virtual ResidueFactoryMethod* clone () const { return new ResidueFM (mpAtomFM); }
  
    /**
     * Destroys the object.
     */
    virtual ~ResidueFM () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Creates a new residue of Residue type.
     * @return the newly created empty residue.
     */
    virtual Residue* createResidue () const;

   /**
     * Creates a residue copy.
     * @param res the residue to copy from.
     * @return the newly created residue copy.
     */
    virtual Residue* createResidue (const Residue& res) const;

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to the output stream.
     * @param obs the output stream.
     * @return the written stream.
     */
    virtual oBinstream& write (oBinstream& obs) const;

  };



  /**
   * @short ResidueFactoryMethod implementation for ExtendedResidue class.
   *
   * This is the residue factory method implementation for the Residue class.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ResidueFactoryMethod.h,v 1.7 2005-02-25 16:48:14 thibaup Exp $
   */
  class ExtendedResidueFM : public ResidueFactoryMethod
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ExtendedResidueFM (const AtomFactoryMethod *fm = 0) : ResidueFactoryMethod(fm) { }

    /**
     * Clones the object.
     * @return the copy of the object.
     */
    virtual ResidueFactoryMethod* clone () const { return new ExtendedResidueFM (mpAtomFM); }
  
    /**
     * Destroys the object.
     */
    virtual ~ExtendedResidueFM () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Creates a new residue of Residue type.
     * @return the newly created empty residue.
     */
    virtual Residue* createResidue () const;

   /**
     * Creates a residue copy.
     * @param res the residue to copy from.
     * @return the newly created residue copy.
     */
    virtual Residue* createResidue (const Residue& res) const;

    // I/O  -----------------------------------------------------------------

    /**
     * Writes the object to the output stream.
     * @param obs the output stream.
     * @return the written stream.
     */
    virtual oBinstream& write (oBinstream& obs) const;

  };


  /**
   * Writes a @ref ResidueFactoryMethod object to the output stream.
   * @param obs the output stream.
   * @param obj the @ref ResidueFactoryMethod object to write
   * @return the written stream.
   */
  oBinstream& operator<< (oBinstream& obs, const ResidueFactoryMethod& obj);

}

#endif
