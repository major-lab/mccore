//                              -*- Mode: C++ -*- 
// CGraph.h
// Copyright © 1999, 2000-01 Laboratoire de Biologie Informatique et Théorique.
//                           Université de Montréal.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:33:55 2001
// Update Count     : 4
// Status           : Ok.
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _CGraph_h_
#define _CGraph_h_


#include <iostream.h>
#include <values.h>
#include <vector.h>
#include <map.h>
#include <algo.h>


typedef int nodeid;
typedef int edgeid;
#define badid -1



/**
 * @short Class implementing the graph ADT with a adjacency lists
 * implementation and making it possible to treat
 * oriented/non-oriented/semi-oriented graphs.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
template< class Node >
class CPath : public vector< Node >
{
  int mValue;

public:

  // LIFECYCLE ------------------------------------------------------------

  CPath () : vector< Node > (), mValue (0) { }
  CPath (const CPath &other)
    : vector< Node > (other), mValue (other.mValue) { }
  ~CPath () { }

  // OPERATORS ------------------------------------------------------------

  const CPath& operator= (const CPath &right)
  {
    if (this != &right)
      {
	vector< Node >::operator= (right);
	mValue = right.mValue;
      }
    return *this;
  }
  
  bool operator< (const CPath &right) const
  {
    // used in sort (min_mean_path())
    return size () > right.size ();
  }

  // ACCESS ---------------------------------------------------------------

  void setValue (int value) { mValue = value; }
  int getValue () const { return mValue; }

  // METHODS --------------------------------------------------------------

  // I/O  -----------------------------------------------------------------
};



template< class Node >
ostream&
operator<< (ostream &out, const CPath< Node > &cpath) 
{
  CPath< Node >::const_iterator cit;
  
  out << "[ " << flush;
  for (cit = cpath.begin (); cit != cpath.end (); ++cit) 
    out << *cit << " ";
  return out << "] = " << cpath.getValue () << flush;
}



/**
 * @short Graph class.
 *
 * In it's present form, node ids are garantied to lie between 0 and size ()
 * - 1.  This should resist all modification to the implementation...
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
template< class Node, class Edge >
class CGraph 
{
public:

  typedef map< nodeid, edgeid, less< nodeid > > adjlist;    // Adjacency List
  typedef map< nodeid, adjlist ,less< nodeid > > adjgraph;  // Adjacency Graph  
  typedef vector< Node >::size_type size_type;
protected:

  struct __degree { short deg, in, out; };

  vector< Node > mNode;
  vector< bool > mNodeMark;
  vector< int >  mNodeValue;
  vector< __degree > mDegrees;

  vector< Edge > mEdge;
  vector< pair< nodeid, nodeid > > mEdgeNodes;
  vector< bool > mEdgeMark;
  vector< int >  mEdgeValue;
  
  adjgraph mAdj;

public:

  // EXCEPTION ------------------------------------------------------------

  class BadIndex { };

  // LIFECYCLE ------------------------------------------------------------

  CGraph () { }
  CGraph (const CGraph &right)
    : mNode (right.mNode), mNodeValue (right.mNodeValue),
      mNodeMark (right.mNodeMark), mEdge (right.mEdge),
      mEdgeValue (right.mEdgeValue), mEdgeMark (right.mEdgeMark),
      mEdgeNodes (right.mEdgeNodes), mDegrees (right.mDegrees),
      mAdj (right.mAdj)
  { }
  virtual ~CGraph () { }

  // OPERATORS ------------------------------------------------------------

  virtual const CGraph& operator= (const CGraph &right)
  {
    if (this != &right)
      { 
	mNode = right.mNode;
	mNodeValue = right.mNodeValue;
	mNodeMark = right.mNodeMark;
	mEdge = right.mEdge;
	mEdgeValue = right.mEdgeValue;
	mEdgeMark = right.mEdgeMark;
	mEdgeNodes = right.mEdgeNodes;
	mDegrees = right.mDegrees;
	mAdj = right.mAdj;
      }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  size_type size () const { return mNode.size (); }
  
  // Node related functions -----------------------------------------------

  const vector< Node >& getNodes () const { return mNode; }
  vector< Node >& getNodes () { return mNode; }

  const Node& getNode (nodeid index) const;
  Node& getNode (nodeid index);

  int getNodeValue (nodeid index) const;
  void setNodeValue (nodeid index, int v);

  void markNode (nodeid index) { mNodeMark[index] = true; }
  void unmarkNode (nodeid index) { mNodeMark[index] = false; }
  bool isMarkedNode (nodeid index) { return mNodeMark[index]; }

  short getDegree (nodeid index) const { return mDegrees[index].deg; }
  short getInDegree (nodeid index) const { return mDegrees[index].in; }
  short getOutDegree (nodeid index) const { return mDegrees[index].out; }

  nodeid getNodeIndex (const Node &n) const;

  // Edges related functions -----------------------------------------------

  const vector< Edge >& getEdges () const { return mEdge; }
  vector< Edge >& getEdges () { return mEdge; }
  const vector< pair< nodeid, nodeid > >& getEdgeNodes () const 
  { return mEdgeNodes; }

  const Edge& getEdge (edgeid index) const;
  Edge& getEdge (edgeid index);
  const Edge& getEdge (nodeid a, nodeid b) const;
  Edge& getEdge (nodeid a, nodeid b); // a=origin, b=destination

  const pair< nodeid, nodeid >& getNodes (const Edge &e) const;

  int getEdgeValue (nodeid a, nodeid b) const;
  int getEdgeValue (edgeid index) const;
  void setEdgeValue (nodeid a, nodeid b, int v);
  void setEdgeValue (edgeid index, int v);

  void markEdge (edgeid index) { mEdgeMark[index] = true; }
  void unmarkEdge (edgeid index) { mEdgeMark[index] = false; }
  bool isMarkedEdge (edgeid index) { return mEdgeMark[index]; }

  edgeid getEdgeIndex (const Edge &e) const;
  edgeid getEdgeIndex (nodeid a, nodeid b) const; // a=origin, b=destination

  // Check if there is a directed edge between a and b
  // Returns false even if there is a directed edge between b and a
  bool isConnected (nodeid a, nodeid b) const // a=origin, b=destination
  { 
    adjgraph::const_iterator i = mAdj.find (a);

    return (i != mAdj.end () && i->second.find (b) != i->second.end ());
  }

  // METHODS --------------------------------------------------------------

  size_type addNode (const Node &n, const int v = 0)
    {
      // TODO : check redundancy
      size_type size = mNode.size ();
      mDegrees.push_back (__degree ());
      mNode.push_back (n);
      mNodeMark.push_back (false);
      mNodeValue.push_back (v);
      return size;
    }

  edgeid addEdgeById (nodeid a, nodeid b, const Edge &e,
		      bool oriented = true, const int v = 0)
  {
    // TODO : Careful about redundancy...
    int size = mEdge.size ();

    mEdge.push_back (e);
    mEdgeNodes.push_back (make_pair (a,b));
    mEdgeMark.push_back (false);
    mEdgeValue.push_back (v);
    
    mAdj[a][b] = size;
    if (oriented)
      {
	mDegrees[b].in++;
	mDegrees[a].out++;
      }
    else
      {
	mDegrees[a].deg++;
	mDegrees[b].deg++;
	mAdj[b][a] = size;
      }
    return size;
  }
  
  edgeid addEdge (const Node &a, const Node &b, const Edge &e,
		  bool oriented = true, const int v = 0)
  {
    nodeid ida = getNodeIndex (a);
    nodeid idb = getNodeIndex (b);
    return addEdgeById (ida, idb, e, oriented, v);
  }

  vector< CPath< nodeid > > shortest_path (nodeid root) const
  {
    nodeid i, j;
    int n = size ();
    vector< CPath< nodeid > > P (n);    // path description
    vector< nodeid > C;                  // node set
    vector< nodeid >::iterator k;
    
    // Initialize ---
    for (i = 0; i < n; ++i)
      {
	if (i == root)
	  P[i].setValue (0);
	else
	  {
	    C.push_back (i);
	    if (isConnected (root, i))
	      {
		P[i].setValue (getEdgeValue (root, i));
		P[i].push_back (root);
		P[i].push_back (i);
	      }
	    else
	      P[i].setValue (MAXINT);
	  }
      }
    
    // Execute ---
    for (i = 0; i < n - 2; ++i)
      {
	vector< nodeid >::iterator min_iter = C.begin ();
	int min_value = P[*min_iter].getValue (); // in C
	int min_index;
	
	for (k = C.begin (); k != C.end (); ++k)
	  {
	    if ( P[*k].getValue () < min_value)
	      {
		min_value = P[*k].getValue ();
		min_iter = k;
	      } 
	  }
	min_index = *min_iter;
	C.erase (min_iter);
	
	if (min_value == MAXINT)
	  break; // in case there is no better element...
	
	for(k = C.begin (); k != C.end (); ++k)
	  {
	    int old_val = P[*k].getValue ();
	    int new_val;
	    if (isConnected (min_index, *k))
	      new_val = min_value + getEdgeValue (min_index, *k);
	    else 
	      new_val = MAXINT;
	    if (old_val > new_val)
	      {
		P[*k] = P[min_index];
		P[*k].push_back (*k);
		P[*k].setValue (new_val);
	      }
	  }
      }
    return P;
  }
  

  vector< CPath< nodeid > > minimum_mean_path () const
  {
    int i, j;
    vector< CPath< nodeid > > tree;
    vector< CPath< nodeid > > minTree;
    vector< CPath< nodeid > > finalTree;
    vector< CPath< nodeid > >::iterator k;
    int sum;
    int minValue = MAXINT;
      
    
    for (i = 0; i < size (); ++i)
      {
	tree.clear ();
	tree = shortest_path (i);
	sum = 0;
	for (j = 0; j < tree.size (); ++j)
	  {
	    if ( tree[j].getValue () == MAXINT)
	      {
		sum = MAXINT;
		break;
	      }
	    sum += tree[j].getValue ();
	  }

	if (sum < minValue)
	  {
	    minTree.clear ();
	    minTree = tree;
	    minValue = sum;
	  }
      }

      sort (minTree.begin (), minTree.end ());
      
      vector< bool > placed (size (), false);
      
      for (k = minTree.begin (); k != minTree.end (); ++k)
	{
	  if (k->size () > 1)
	    {
	      CPath< nodeid > tmpPath;
	      for (i = 1; i < k->size (); ++i)
		{
		  if (! placed[(*k)[i]])
		    {
		      if (i == 1 || placed[(*k)[i - 1]])
			{ 
			  tmpPath.push_back ((*k)[i - 1]);
			  tmpPath.push_back ((*k)[i]);
			}
		      else
			tmpPath.push_back ((*k)[i]);
		    }
		}
	      for (i = 1; i < k->size (); ++i)
		placed[(*k)[i]] = true;
	      if (tmpPath.size () > 0)
		finalTree.push_back (tmpPath);
	    }
	}
      return finalTree;
  }
  
  // I/O  -----------------------------------------------------------------

  friend ostream& operator<< (ostream &out, const CGraph< Node, Edge > &gr)
  {
    int i, j;
    edgeid id;

    if (gr.mNode.size () == 0)
      return out;
    for (i = 0; i < gr.mNode.size (); ++i)
      out << "Node[" << i << "]: " << gr.mNode[i]
	  << " (value: " << gr.mNodeValue[i] << ") "
	  << (gr.mNodeMark[i]?"mark":"") << endl;
    out << endl;
    for (j = 0; j < gr.mEdge.size (); ++j)
      out << "Edge[" << j << "]: " << gr.mEdge[j]
	  << " (value: " << gr.mEdgeValue[j] << ") "
	  << (gr.mEdgeMark[j]?"mark":"") << endl;
    out << endl;
    out << "Matrix:" << endl;
    for(i = 0; i < gr.mNode.size (); ++i)
      {
	for(j = 0; j < gr.mNode.size (); ++j)
	  {
	    id = gr.getEdgeIndex (i, j);
	    if (id != -1)
	      out.form ("%2d ", id);
	    else
	      out.form (" - ");
	  }
	out.form ("\n");
      }
    return out;
  }
};



template< class Node, class Edge >
const Node&
CGraph< Node, Edge >::getNode (nodeid index) const
{ 
  if (index < 0 || index > (int)mNode.size ())
    {
      cerr << "Bad Index in getNode (id): " << index << endl;
      throw BadIndex ();
    }
  return mNode[index];
}



template< class Node, class Edge >
Node&
CGraph< Node, Edge >::getNode (nodeid index)
{
  if (index < 0 || index > (int)mNode.size ())
    {
    cerr << "Bad Index in getNode (id): " << index << endl;
    throw BadIndex ();
  }
  return mNode[index];
}



template< class Node, class Edge >
int 
CGraph< Node, Edge >::getNodeValue (nodeid index) const
{
  if (index < 0 || index > (int)mNodeValue.size ())
    {
      cerr << "Bad Index in getNodeValue (id): " << index << endl;
      throw BadIndex ();
    }
  return mNodeValue[index];
}



template< class Node, class Edge >
void 
CGraph< Node, Edge >::setNodeValue (nodeid index, int v)
{
  if (index < 0 || index > (int)mNode.size ())
    {
      cerr << "Bad Index in setNodeValue (id): " << index << endl;
      throw BadIndex ();
    }
  mNodeValue[index] = v;
}



template< class Node, class Edge >
nodeid 
CGraph< Node, Edge >::getNodeIndex (const Node &n) const
{
  vector< Node >::const_iterator i = find (mNode.begin (), mNode.end (), n);
  if (i == mNode.end ())
    return badid;
  return i - mNode.begin ();
}



template< class Node, class Edge >
const Edge&
CGraph< Node, Edge >::getEdge (edgeid index) const
{
  if (index < 0 || index > (int)mEdge.size ())
    {
      cerr << "Bad Index in getEdge (b): " << index << endl;
      throw BadIndex ();
    }
  return mEdge[index];
}



template< class Node, class Edge >
Edge&
CGraph< Node, Edge >::getEdge (edgeid index)
{
  if (index < 0 || index > (int)mEdge.size ())
    {
      cerr << "Bad Index in getEdge (b): " << index << endl;
      throw BadIndex ();
    }
  return mEdge[index];
}



template< class Node, class Edge >
const Edge&
CGraph< Node, Edge >::getEdge (nodeid a, nodeid b) const
{
  adjgraph::const_iterator i = mAdj.find (a);
  adjlist::const_iterator j;
  
  if (i == mAdj.end ())
    throw BadIndex ();
  j = i->second.find (b);
  if (j == i->second.end ())
    throw BadIndex ();
  return mEdge[j->second];
}


// a=origin, b=destination
template< class Node, class Edge >
Edge&
CGraph< Node, Edge >::getEdge (nodeid a, nodeid b)
{
  adjgraph::const_iterator i = mAdj.find (a);
  adjlist::const_iterator j;
  
  if (i == mAdj.end ())
    throw BadIndex ();
  j = i->second.find (b);
  if (j == i->second.end ())
    throw BadIndex ();
  return mEdge[j->second];
}



template< class Node, class Edge >
const pair< nodeid, nodeid >&
CGraph< Node, Edge >::getNodes (const Edge &e) const
{
  vector< Edge >::const_iterator i = find (mEdge.begin (), mEdge.end (), e);
  if (i == mEdge.end ())
    return make_pair (badid, badid);
  return mEdgeNodes[i - mEdge.begin ()];
}



template< class Node, class Edge >
int 
CGraph< Node, Edge >::getEdgeValue (nodeid a, nodeid b) const
{
  adjgraph::const_iterator i = mAdj.find (a);
  adjlist::const_iterator j;
  
  if (i == mAdj.end ())
    throw BadIndex ();
  j = i->second.find (b);
  if (j == i->second.end ())
    throw BadIndex ();
  return mEdgeValue[j->second];
}



template< class Node, class Edge >
int 
CGraph< Node, Edge >::getEdgeValue (edgeid index) const
{
  if (index < 0 || index > (int)mEdge.size ())
    {
      cerr << "Bad Index in getEdgeValue (index): " << index << endl;
      throw BadIndex ();
    }
  return mEdgeValue[index]; 
}



template< class Node, class Edge >
void 
CGraph< Node, Edge >::setEdgeValue (nodeid a, nodeid b, int v)
{
  adjgraph::const_iterator i = mAdj.find (a);
  adjlist::const_iterator j;
  
  if (i == mAdj.end ())
    throw BadIndex ();
  j = i->second.find (b);
  if (j == i->second.end ())
    throw BadIndex ();
  mEdgeValue[j->second] = v;
}



template< class Node, class Edge >
void 
CGraph< Node, Edge >::setEdgeValue (edgeid index, int v)
{
  if (index < 0 || index > (int)mEdge.size ())
    {
      cerr << "Bad Index in setEdgeValue (b): " << index << endl;
      throw BadIndex ();
    }
  mEdgeValue[index] = v;
}



template< class Node, class Edge >
edgeid
CGraph< Node, Edge >::getEdgeIndex (const Edge &e) const
{
  vector< Edge >::const_iterator i = find (mEdge.begin (), mEdge.end (), e);
  if (i == mEdge.end ())
    return badid;
  return i - mEdge.begin ();
}



// a=origin, b=destination
template< class Node, class Edge >
edgeid
CGraph< Node, Edge >::getEdgeIndex (nodeid a, nodeid b) const
{
  adjgraph::const_iterator i = mAdj.find (a);
  adjlist::const_iterator j;

  if (i == mAdj.end ())
    return badid;
  j = i->second.find (b);
  if (j == i->second.end ())
    return badid;
  return j->second;
}

#endif
