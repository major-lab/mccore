//                              -*- Mode: C++ -*- 
// GraphModel.h
// Copyright © 2004 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 19:31:01 2004
// $Revision: 1.1.2.5 $
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


#ifndef _mccore_GraphModel_h_
#define _mccore_GraphModel_h_

#include "AbstractModel.h"
#include "Residue.h"
#include "UndirectedGraph.h"



namespace mccore
{
  class Relation;
  class ResidueFactoryMethod;


  
  /**
   * The GraphModel class is a graph container for Residue pointers as
   * vertices and Relation pointers as edges.  It uses the AbstractModel
   * iterators.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: GraphModel.h,v 1.1.2.5 2004-12-27 01:37:55 larosem Exp $
   */
  class GraphModel : public AbstractModel, public UndirectedGraph < Residue*, Relation*, float, float, less_deref< Residue > >
  {
    typedef UndirectedGraph< Residue*, Relation*, float, float, less_deref< Residue > > graphsuper;
    
  public:

    typedef AbstractModel::iterator iterator;
    typedef AbstractModel::const_iterator const_iterator;
    typedef graphsuper::size_type size_type;
    typedef graphsuper::label label;

  protected:
    
    typedef graphsuper::V2VLabel V2VLabel;
    typedef graphsuper::EV2ELabel EV2ELabel;
    typedef graphsuper::EndVertices EndVertices;

  private:

    /**
     * Annotation flag.
     */
    bool annotated;
    
  public:
    
    /**
     * Initializes the object.
     * @param fm the residue factory methods that will instanciate new
     * residues (default is @ref ExtendedResidueFM).
     */
    GraphModel (const ResidueFactoryMethod *fm = 0)
      : AbstractModel (fm), annotated (false) { }

    /**
     * Initializes the object with the right's content (deep copy).
     * @param right the object to copy.
     */
    GraphModel (const GraphModel &right);

    /**
     * Clones the model.
     * @return a copy of the model.
     */
    virtual AbstractModel* clone () const { return new GraphModel (*this); }

    /**
     * Destroys the object.
     */
    virtual ~GraphModel ();

  private:

    /**
     * Clones and re-assigns the residues and relations into the graph.
     * @param right the GraphModel to clone.
     */
    void deepCopy (const GraphModel &right);

    // OPERATORS ------------------------------------------------------------

  public:
    
    /**
     * Assigns the object with the right's content (deep copy).
     * @param right the object to copy.
     * @return itself.
     */
    GraphModel& operator= (const GraphModel &right);

    /**
     * Gets the model reference at nth position.
     * @param nth the position of the reference to get.
     * @return the nth reference.
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual Residue& operator[] (size_type nth) throw (ArrayIndexOutOfBoundsException)
    {
      try
	{
	  return *internalGetVertex (nth);
	}
      catch (NoSuchElementException &e)
	{
	  throw ArrayIndexOutOfBoundsException ("", __FILE__, __LINE__);
	}
    }

    /**
     * Gets the model const_reference at nth position.
     * @param nth the position of the const_reference to get.
     * @return the nth const_reference.
     * @exception ArrayIndexOutOfBoundsException
     */
    virtual const Residue& operator[] (size_type nth) const throw (ArrayIndexOutOfBoundsException)
    {
      try
	{
	  return *internalGetVertex (nth);
	}
      catch (NoSuchElementException &e)
	{
	  throw ArrayIndexOutOfBoundsException ("", __FILE__, __LINE__);
	}
    }

    // ACCESS ---------------------------------------------------------------

    /**
     * Gets the iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual iterator begin () { return iterator (vertices.begin ()); }

    /**
     * Gets the iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual iterator end () { return iterator (vertices.end ()); }

    /**
     * Gets the const iterator pointing to the beginning of the model.
     * @return the iterator.
     */
    virtual const_iterator begin () const
    { return const_iterator (vertices.begin ()); }

    /**
     * Gets the const iterator pointing to the end of the model.
     * @return the iterator.
     */
    virtual const_iterator end () const
    { return const_iterator (vertices.end()); }


    // METHODS -------------------------------------------------------------

    /**
     * Inserts a residue at the end.
     * @param res the residue to insert.
     * @return the position where the residue was inserted.
     */
    virtual iterator insert (const Residue &res);

    /**
     * Inserts the residue range before pos.
     * @param pos the iterator where the residue will be placed.
     * @param f the first iterator in the range.
     * @param l the last iterator in the range.
     */
    template <class InputIterator>
    void insert (InputIterator f, InputIterator l)
    {
      graphsuper::insertRange (f, l);
    }

    /**
     * Erases a residue from the model.
     * @param pos the position to erase.
     * @return an iterator on the next residue.
     */ 
    virtual iterator erase (iterator pos) 
    {
      return iterator (graphsuper::erase (&*pos));
    }

    /**
     * Finds a residue given it's residue id.  Returns an iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     */
    iterator find (const ResId &id)
    {
      return AbstractModel::find (id);
    }

    /**
     * Finds a residue given it's residue id.  Returns a AbstractModel iterator
     * pointing to the residue or the end of the container if the residue was
     * not found.
     * @param id the residue id.
     * @return a AbstractModel iterator.
     */
    const_iterator find (const ResId &id) const
    {
      return AbstractModel::find (id);
    }
    
    /**
     * Sorts the model according to the Residue::operator<
     */ 
    virtual void sort ();
    
    /**
     * Returns the number of residues present in the model.
     * @return a number of residues.
     */
    virtual size_type size () const
    {
      return UndirectedGraph< Residue*, Relation*, float, float, less_deref < Residue > >::size ();
    }

    /**
     * Tells if there is no residue in the model.
     * @return whether the model is empty.
     */
    virtual bool empty () const
    {
      return UndirectedGraph< Residue*, Relation*, float, float, less_deref < Residue > >::empty ();
    }

    /**
     * Removes all of the residues from the model.  
     */
    virtual void clear ();

    /**
     * Annotates the GraphModel.  It builds edge in the graph.
     */
    void annotate ();
    
    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the model to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Reads the model from a pdb input stream.
     * @param ips the pdb data stream.
     * @return the consumed pdb stream.
     */
    virtual iPdbstream& input (iPdbstream &ips);
  
    /**
     * Writes the model to a binary output stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;

    /**
     * Reads the model from a binary input stream.
     * @param obs the binary data stream.
     * @return the consumed binary stream.
     */
    virtual iBinstream& input (iBinstream &ibs);

  };
}
    
#endif
