//                              -*- Mode: C++ -*- 
// ModelFactoryMethod.h
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Wed Jan  5 17:12:54 2005
// $Revision: 1.1 $
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


#ifndef _mccore_ModelFactoryMethod_h_
#define _mccore_ModelFactoryMethod_h_



namespace mccore
{
  class AbstractModel;
  class ResidueFactoryMethod;


  
  /**
   * @short Abstract class for model factory methods.
   *
   * This class is used in Molecule to generate a given type of model on input
   * methods.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ModelFactoryMethod.h,v 1.1 2005-01-06 21:08:00 larosem Exp $
   */
  class ModelFactoryMethod
  {

  protected:
    
    /**
     * The Residue factory method to include in generated models.
     */
    ResidueFactoryMethod *rFM;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ModelFactoryMethod (const ResidueFactoryMethod *fm = 0);

    /**
     * Initializes the object with the right content.
     * @param right the object to copy.
     */
    ModelFactoryMethod (const ModelFactoryMethod &right);

    /**
     * Copies the object.
     */
    virtual ModelFactoryMethod* clone () const = 0;
  
    /**
     * Destroys the object.
     */
    virtual ~ModelFactoryMethod ();

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    // I/O  -----------------------------------------------------------------

    /**
     * Creates the model.
     * @return the newly created empty model.
     */
    virtual AbstractModel* createModel () const = 0;

  };
  

  /**
   * @short ModelFactoryMethod implementation for Model class.
   *
   * This is the model factory method implementation for the Model class.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ModelFactoryMethod.h,v 1.1 2005-01-06 21:08:00 larosem Exp $
   */
  class ModelFM : public ModelFactoryMethod
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ModelFM (const ResidueFactoryMethod *fm = 0) : ModelFactoryMethod (fm) { }

    /**
     * Initializes the object with the right content.
     * @param right the object to copy.
     */
    ModelFM (const ModelFM &right) : ModelFactoryMethod (right) { }
    
    /**
     * Clones the object.
     * @return the copy of the object.
     */
    virtual ModelFactoryMethod* clone () const { return new ModelFM (*this); }
  
    /**
     * Destroys the object.
     */
    virtual ~ModelFM () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Creates a new model of Model type.
     * @return the newly created empty model.
     */
    virtual AbstractModel* createModel () const;

    // I/O  -----------------------------------------------------------------

  };



  /**
   * @short ModelFactoryMethod implementation for GraphModel class.
   *
   * This is the model factory method implementation for the GraphModel class.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: ModelFactoryMethod.h,v 1.1 2005-01-06 21:08:00 larosem Exp $
   */
  class GraphModelFM : public ModelFactoryMethod
  {

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    GraphModelFM (const ResidueFactoryMethod *fm = 0);

    /**
     * Initializes the object with the right content.
     * @param right the object to copy.
     */
    GraphModelFM (const ModelFM &right) : ModelFactoryMethod (right) { }

    /**
     * Clones the object.
     * @return the copy of the object.
     */
    virtual ModelFactoryMethod* clone () const { return new GraphModelFM (*this); }
  
    /**
     * Destroys the object.
     */
    virtual ~GraphModelFM () { }

    // OPERATORS ------------------------------------------------------------

    // ACCESS ---------------------------------------------------------------

    // METHODS --------------------------------------------------------------

    /**
     * Creates a new model of Model type.
     * @return the newly created empty model.
     */
    virtual AbstractModel* createModel () const;

    // I/O  -----------------------------------------------------------------

  };
  
}

#endif
