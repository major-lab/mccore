//                              -*- Mode: C++ -*- 
// GraphModel.h
// Copyright © 2004-05 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 19:31:01 2004
// $Revision: 1.3 $
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
#include "Algo.h"
#include "Residue.h"
#include "OrientedGraph.h"



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
   * @version $Id: GraphModel.h,v 1.3 2005-01-05 01:45:04 larosem Exp $
   */
  class GraphModel : public AbstractModel, public OrientedGraph< Residue*, Relation*, int, int, less_deref< Residue > >
  {
    typedef OrientedGraph< Residue*, Relation*, int, int, less_deref< Residue > > graphsuper;
    
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
    GraphModel (const AbstractModel &right);

    /**
     * Clones the model.
     * @return a copy of the model.
     */
    virtual AbstractModel* clone () const
    {
      return new GraphModel ((const AbstractModel&) *this);
    }

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
    GraphModel& operator= (const AbstractModel &right);

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

    /**
     * Tells if the GraphModel was annotated.
     * @return the annotated flag.
     */
    bool isAnnotated () const { return annotated; }

    // METHODS -------------------------------------------------------------

  private:

    /**
     * Inserts a vertex in the graph.  Private, use the reference insert
     * method.
     * @param v the vertex to insert.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const Residue *&v) { return false; }

    /**
     * Inserts a vertex and its weight in the graph.  Private, use the
     * reference insert method.
     * @param v the vertex to insert.
     * @param w the vertex weight.
     * @return true if the element was inserted, false if already present.
     */
    virtual bool insert (const Residue *&v, const int &w) { return false; }

  public:
    
    /**
     * Inserts a residue at the end.  The annotated flag is turned to false.
     * @param res the residue to insert.
     * @return the position where the residue was inserted.
     */
    virtual iterator insert (const Residue &res)
    {
      return insert (res, 0);
    }
    
    /**
     * Inserts a residue at the end.  The annotated flag is turned to false.
     * @param res the residue to insert.
     * @param w the Residue weight.
     * @return the position where the residue was inserted.
     */
    virtual iterator insert (const Residue &res, int w)
    {
      annotated = false;
      graphsuper::insert (res.clone (), w);
      return end ();
    }
      
    /**
     * Erases a residue from the model.
     * @param pos the position to erase.
     * @return an iterator on the next residue.
     */ 
    virtual iterator erase (AbstractModel::iterator pos);

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
     * Sorts the model according to the Residue::operator<.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     */ 
    virtual void sort ();
    
    /**
     * Returns the number of residues present in the model.
     * @return a number of residues.
     */
    virtual size_type size () const
    {
      return graphsuper::size ();
    }

    /**
     * Tells if there is no residue in the model.
     * @return whether the model is empty.
     */
    virtual bool empty () const
    {
      return graphsuper::empty ();
    }

    /**
     * Removes all of the residues from the model.  
     */
    virtual void clear ();

    /**
     * Annotates the GraphModel.  It builds edges in the graph.
     */
    void annotate ();

    /**
     * Reannotates the GraphModel.
     */
    void reannotate ()
    {
      annotated = false;
      annotate ();
    }
    
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
