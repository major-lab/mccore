//                              -*- Mode: C++ -*-
// GraphModel.h
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Thu Dec  9 19:31:01 2004
// $Revision: 1.17 $
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

#include <iostream>

#include "AbstractModel.h"
#include "Algo.h"
#include "Exception.h"
#include "Path.h"
#include "Residue.h"
#include "Relation.h"
#include "OrientedGraph.h"

using namespace std;



namespace mccore
{
  class Molecule;
  class Relation;
  class ResidueFactoryMethod;
  class ResidueType;



  /**
   * The GraphModel class is a graph container for Residue pointers as
   * vertices and Relation pointers as edges.  It uses the AbstractModel
   * iterators.
   *
   * @author Martin Larose (<a href="larosem@iro.umontreal.ca">larosem@iro.umontreal.ca</a>)
   * @version $Id: GraphModel.h,v 1.17 2007-01-08 23:44:11 larosem Exp $
   */
  class GraphModel : public AbstractModel, public OrientedGraph< Residue*, Relation*, int, int, less_deref< Residue > >
  {

  protected:

    typedef OrientedGraph< Residue*, Relation*, int, int, less_deref< Residue > > graphsuper;

  public:

    typedef AbstractModel::iterator iterator;
    typedef AbstractModel::const_iterator const_iterator;
    typedef graphsuper::size_type size_type;
    typedef graphsuper::label label;
    typedef Residue* vertex;
    typedef Relation* edge;
    typedef int vertex_weight;
    typedef int edge_weight;

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
     * @param fm the residue factory methods that will instanciate new
     * residues (default is @ref ExtendedResidueFM).
     */
    GraphModel (const AbstractModel &right, const ResidueFactoryMethod *fm = 0);

    /**
     * Initializes the object with the right's content (deep copy).
     * @param right the object to copy.
     * @param fm the residue factory methods that will instanciate new
     * residues (default is @ref ExtendedResidueFM).
     */
    GraphModel (const GraphModel &right, const ResidueFactoryMethod *fm = 0);

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
    GraphModel& operator= (const AbstractModel &right);

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

    /**
     * Tells if the GraphModel was annotated.
     * @return the annotated flag.
     */
    bool isAnnotated () const { return annotated; }

    /**
     * Sets the annotated flag, use with care.
     * @param val the new annotated flag value.
     */
    void setAnnotated (bool val) { annotated = val; }

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
    virtual iterator insert (const Residue &res, int w);

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
     * Removes the amino acids from the model.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     * The edge order may change.
     */
    virtual void removeAminoAcid ();

    /**
     * Removes the nucleic acids from the model.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     * The edge order may change.
     */
    virtual void removeNucleicAcid ();

    /**
     * Removes every residue that is not an amino acid.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     * The edge order may change.
     */
    virtual void keepAminoAcid ();

    /**
     * Removes every residue that is not a nucleic acid.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     * The edge order may change.
     */
    virtual void keepNucleicAcid ();

    /**
     * Removes every residue that is not RNA.  If the GraphModel is already
     * annotated, it rearrange the adjacency graph.  The edge order may
     * change.
     */
    virtual void keepRNA ();

    /**
     * Removes every residue that is not DNA.  If the GraphModel is already
     * annotated, it rearrange the adjacency graph.  The edge order may
     * change.
     */
    virtual void keepDNA ();

  private:

    /**
     * Template function used by removeAminoAcid, removeNucleicAcid,
     * keepAminoAcid, keepNucleicAcid, keepRNA and keepDNA.  If the
     * GraphModel is already annotated, it rearrange the adjacency graph.
     * The edge order may change.
     */
    template < class V >
    void keepTemplate ()
    {
      if (! empty ())
	{
	  vector< Residue* > newv;
	  vector< int > newweights;
	  const graphsuper::size_type sz = size ();
	  graphsuper::size_type vIndex;
	  graphsuper::size_type *corresp;
	  vector< bool > marks;
	  EV2ELabel newEdgeMap;
	  EV2ELabel::iterator evIt;
	  vector< Relation* > newe;
	  vector< int > newew;

	  corresp = new graphsuper::size_type[vertices.size ()];
	  for (vIndex = 0; vIndex < sz; ++vIndex)
	    {
	      bool value = V ().operator () (vertices[vIndex]->getType ());

	      corresp[vIndex] = newv.size ();
	      marks.push_back (value);
	      if (value)
		{
		  newv.push_back (vertices[vIndex]);
		  newweights.push_back (vertexWeights[vIndex]);
		}
	    }
	  for (evIt = ev2elabel.begin (); ev2elabel.end () != evIt; ++evIt)
	    {
	      const EndVertices &endVertices = evIt->first;

	      if (marks[endVertices.getHeadLabel ()]
		  && marks[endVertices.getTailLabel ()])
		{
		  EndVertices ev (corresp[endVertices.getHeadLabel ()],
				  corresp[endVertices.getTailLabel ()]);

		  newEdgeMap.insert (make_pair (ev, newe.size ()));
		  newe.push_back (edges[evIt->second]);
		  newew.push_back (edgeWeights[evIt->second]);
		}
	      else
		{
		  delete edges[evIt->second];
		}
	    }
	  vertices = newv;
	  vertexWeights = newweights;
	  rebuildV2VLabel ();
	  edges = newe;
	  edgeWeights = newew;
	  ev2elabel = newEdgeMap;
	  delete[] corresp;
	}
    }

  public:

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
     * @param asbp Bit mask controlling annotation tasks: adjacency,
     *        stacking, pairing and pairing with backbone (default: all).
     */
    void annotate (unsigned char aspb = Relation::adjacent_mask|Relation::pairing_mask|Relation::stacking_mask|Relation::bhbond_mask);


    /**
     * Reannotates the GraphModel.
     * @param asbp Bit mask controlling annotation tasks: adjacency,
     *        stacking, pairing and pairing with backbone (default: all).
     */
    void reannotate (unsigned char aspb = Relation::adjacent_mask|Relation::pairing_mask|Relation::stacking_mask|Relation::bhbond_mask)
    {
      annotated = false;
      annotate (aspb);
    }

  private:

    /**
     * Fills the Molecule with the elements from this identified with the
     * Path vector.
     * @param molecule the molecule to fill.
     * @param cycles the collection of Paths describing the cycles.
     */
    void fillMoleculeWithCycles (Molecule &molecule, const vector< Path< GraphModel::label, GraphModel::size_type > > &cycles) const;

  public:

    /**
     * Finds a minimum cycle basis from this GraphModel.
     * @param molecule the container to fill with the cycles.
     */
    void minimumCycleBasis (Molecule &molecule) const;

    /**
     * Finds the union of minimum cycle bases from this GraphModel.
     * @param molecule the container to fill with the cycles.
     */
    void unionMinimumCycleBases (Molecule &molecule);


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

  /**
   * Reads the GraphModel from a binary input stream.
   * @param is the binary input stream.
   * @param model the GraphModel.
   * @return the consumed binary stream.
   */
  iBinstream& operator>> (iBinstream &is, GraphModel &model);

  /**
   * Writes the GraphModel to a binary output stream.
   * @param os the binary input stream.
   * @param model the GraphModel.
   * @return the consumed binary stream.
   */
  oBinstream& operator<< (oBinstream &os, const GraphModel &model);

}

#endif
