//                              -*- Mode: C++ -*- 
// Graph.cc
// Copyright © 2002 Laboratoire de Biologie Informatique et Théorique.
// Author           : Patrick Gendron
// Created On       : Mon Feb 18 16:07:09 2002
// Last Modified By : Patrick Gendron
// Last Modified On : Fri Jul 26 15:21:18 2002
// Update Count     : 6
// Status           : Unknown.
// 

#ifndef __Graph_cc_
#define __Graph_cc_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <iomanip.h>
#include <values.h>


// LIFECYCLE ------------------------------------------------------------


template< class Node, class Edge >
Graph< Node, Edge >::Graph (const Graph &other)
  : adjgraph (other)
{
  if (other.mNodes.size() > 0) 
    {
      mNodes = other.mNodes;  
      mNodeValues = other.mNodeValues;
      mEdges = other.mEdges;  
      mEdgeValues = other.mEdgeValues;
      mEdgeNodes = other.mEdgeNodes;
      mNodeMarks = other.mNodeMarks;
      mEdgeMarks = other.mEdgeMarks;
    }
}


template< class Node, class Edge >
Graph< Node, Edge >::~Graph ()
{
  mNodes.erase (mNodes.begin(), mNodes.end());
  mNodeValues.erase (mNodeValues.begin(), mNodeValues.end());
  mEdges.erase (mEdges.begin(), mEdges.end());
  mEdgeValues.erase (mEdgeValues.begin(), mEdgeValues.end());
  mEdgeNodes.erase (mEdgeNodes.begin(), mEdgeNodes.end());
  erase (begin(), end()); 
  mNodeMarks.clear ();
  mEdgeMarks.clear ();
}


// OPERATORS ------------------------------------------------------------


template< class Node, class Edge >
Graph< Node, Edge >& Graph< Node, Edge >::operator= (const Graph &other)
{
  if  (this != &other) { 
    if  (other.mNodes.size() > 0) 
      {
	adjgraph::operator= (other);
	mNodes = other.mNodes;  
	mNodeValues = other.mNodeValues;
	mEdges = other.mEdges;  
	mEdgeValues = other.mEdgeValues;
	mEdgeNodes = other.mEdgeNodes;
	mNodeMarks = other.mNodeMarks;
	mEdgeMarks = other.mEdgeMarks;
      }
  }
  return *this;
}


// Node related functions -----------------------------------------------


template< class Node, class Edge >
const Node &Graph< Node, Edge >::getNode (int index) const
{
  assert (index >= 0 && index < (int)mNodes.size());
  return mNodes[ index ]; 
}


template< class Node, class Edge >
Node &Graph< Node, Edge >::getNode (int index)
{
  assert (index >= 0 && index < (int)mNodes.size());
  return mNodes[ index ]; 
}

  
template< class Node, class Edge >
int Graph< Node, Edge >::getNodeValue (int index) const
{
  if  (index < 0 || index > (int)mNodeValues.size()) {
    return MAXINT;
  }
  return mNodeValues[ index ]; 
}



template< class Node, class Edge >
void Graph< Node, Edge >::setNodeValue (int index, int v)
{
  assert (index >= 0 && index < (int)mNodeValues.size());
  mNodeValues[ index ] = v;
}

 
template< class Node, class Edge >
int Graph< Node, Edge >::getNodeIndex (const Node &n) const
{
  vector< Node >::const_iterator i = ::find (mNodes.begin(), mNodes.end(), n);
  if  (i == mNodes.end()) return -1;
  return  (i - mNodes.begin());
}
 

// Edges related functions -----------------------------------------------

 
template< class Node, class Edge >
const Edge &Graph< Node, Edge >::getEdge (int index) const
{
  assert (index >= 0 && index < (int)mEdges.size());
  return mEdges[ index ]; 
}


template< class Node, class Edge >
Edge &Graph< Node, Edge >::getEdge (int index)
{
  assert (index >= 0 && index < (int)mEdges.size());
  return mEdges[ index ]; 
}


template< class Node, class Edge >
const Edge &Graph< Node, Edge >::getEdge (int a, int b) const
{
  adjgraph::const_iterator i = (*this).find (a);
  if  (i == end()) {
    cerr << "Index out of range " << __FILE__ << " " << __LINE__ << endl;
    exit (EXIT_FAILURE);
  }
  
  adjlist::const_iterator j = i->second.find (b);
  if  (j == i->second.end()) {
    cerr << "Index out of range" << __FILE__ << " " << __LINE__ << endl;
    exit (EXIT_FAILURE);
  }
  return mEdges[ j->second ];
}


template< class Node, class Edge >
Edge &Graph< Node, Edge >::getEdge (int a, int b)
{
  adjgraph::const_iterator i = (*this).find (a);
  if  (i == end()) {
    cerr << "Index out of range" << __FILE__ << " " << __LINE__ << endl;
    exit (EXIT_FAILURE);
  }

  adjlist::const_iterator j = i->second.find (b);
  if  (j == i->second.end()) {
    cerr << "Index out of range" << __FILE__ << " " << __LINE__ << endl;
    exit (EXIT_FAILURE);
  }
  return mEdges[ j->second ];
}


template< class Node, class Edge >
const pair< int, int > Graph< Node, Edge >::getNodes (const Edge &e) const
{
  vector< Edge >::const_iterator i = ::find (mEdges.begin(), mEdges.end(), e);
  if  (i == mEdges.end()) return make_pair (-1, -1);
  return mEdgeNodes[(i-mEdges.begin ())];
}

template< class Node, class Edge >
int Graph< Node, Edge >::getEdgeValue (int index) const
{
  if  (index < 0 || index > (int)mEdges.size()) {
    return MAXINT;
  }
  return mEdgeValues[ index ]; 
}


template< class Node, class Edge >
void Graph< Node, Edge >::setEdgeValue (int index, int v)
{
  assert (index >= 0 && index < (int)mEdgeValues.size ());
  mEdgeValues[ index ] = v; 
}


template< class Node, class Edge >
int Graph< Node, Edge >::getEdgeIndex (const Edge &e) const
{
  vector< Edge >::const_iterator i = ::find (mEdges.begin(), mEdges.end(), e);
  if  (i == mEdges.end()) return -1;
  return  (i - mEdges.begin());
}


template< class Node, class Edge >
int Graph< Node, Edge >::getEdgeIndex (int a, int b) const
{
  adjgraph::const_iterator i = (*this).find (a);
  if  (i == end()) return -1;
  adjlist::const_iterator j = i->second.find (b);
  if  (j == i->second.end()) return -1;
  return j->second;
}


// Check if there is a directed edge between a and b
// Returns false even if there is a directed edge between b and a
template< class Node, class Edge >
bool Graph< Node, Edge >::isConnected (int a, int b) const // a=origin, b=destination
{ 
  adjgraph::const_iterator i = (*this).find (a);
  if  (i == end()) return false;
  adjlist::const_iterator j = i->second.find (b);
  if  (j == i->second.end()) return false;
  return (mEdgeMarks[j->second]);
}


// Building methods ------------------------------------------------------


template< class Node, class Edge >
int Graph< Node, Edge >::addNode (const Node &n, const int v)
{
  // TODO : check redundancy
  unsigned int size = mNodes.size();
  mNodes.push_back (n);
  mNodeValues.push_back (v);
  mNodeMarks.push_back (true);
  adjlist tmp;
  (*this)[size] = tmp;
  return size;
}

template< class Node, class Edge >
int Graph< Node, Edge >::addEdgeById (int a, int b, const Edge &e, 
				      bool oriented, const int v)
{
  // TODO : Careful about redundancy...
  unsigned int size = mEdges.size();
  
  mEdges.push_back (e);
  mEdgeNodes.push_back (make_pair (a,b));
  mEdgeValues.push_back (v);
  mEdgeMarks.push_back (true);

  (*this)[ a ][ b ] = size;
  if  (!oriented) {
    (*this)[ b ][ a ] = size;
  }
  return size;
}
  
template< class Node, class Edge >
int Graph< Node, Edge >::addEdge (const Node &a, const Node &b, const Edge &e, 
				  bool oriented, const int v)
{
  int ida = getNodeIndex (a);
  int idb = getNodeIndex (b);
  return addEdgeById (ida, idb, e, oriented, v);
}
    

// Algorithms on the graph ----------------------------------------------


template< class Node, class Edge >
void
Graph< Node, Edge >::markNode (int index) 
{
  assert (index >= 0 && index < (int)mNodes.size());
  mNodeMarks[index] = true;
}


template< class Node, class Edge >
void
Graph< Node, Edge >::unmarkNode (int index)
{
  assert (index >= 0 && index < (int)mNodes.size());
  mNodeMarks[index] = false;
}



template< class Node, class Edge >
void
Graph< Node, Edge >::markEdge (int a, int b)
{
  mEdgeMarks[getEdgeIndex (a, b)] = true;
}


template< class Node, class Edge >
void
Graph< Node, Edge >::unmarkEdge (int a, int b)
{
  mEdgeMarks[getEdgeIndex (a, b)] = false;
}



template< class Node, class Edge >
vector< Path > Graph< Node, Edge >::shortest_path (int root) const
{
  int i;
  int n = 0;
  vector< Path > P (size ());             // path description  
  vector< int > C;                  // node set
  vector< int >::iterator k;
  
  // Initialize ---
  for  (i=0; i<(int)size (); i++) {
    if  (i == root) { 
      n++;
      P[ i ].setValue (0);
    } else if (mNodeMarks[i]==true) {
      n++;     
      C.push_back (i);
      if  (isConnected (root, i)) {
	P[ i ].setValue (getEdgeValue (getEdgeIndex (root, i)));
	P[ i ].push_back (root); 
	P[ i ].push_back (i);
      } else {
	P[ i ].setValue (MAXINT);
      }
    }
  }
  
//    cout << "P =  ("; for  (i=0; i<(int)size (); i++) { cout << P[ i ] << " "; } cout << ")" << endl;
//    cout << "C =  ("; for  (i=0; i<(int)C.size(); i++) { cout << C[ i ] << " "; } cout << ")" << endl;

  // Execute ---
  for  (i=0; i<n-2; i++) {
    vector< int >::iterator min_iter = C.begin();
    int min_value = P[ *min_iter ].getValue(); // in C
    int min_index;
    
    for  (k=C.begin(); k!=C.end(); k++) {
      if  (P[ *k ].getValue() < min_value) {
	min_value = P[ *k ].getValue();
	min_iter = k;
      } 
    }
    min_index = *min_iter;
    C.erase (min_iter);
    
    if  (min_value == MAXINT) break; // in case there is no better element...
    
    for (k=C.begin(); k!=C.end(); k++) {
      int old_val = P[ *k ].getValue();
      int new_val;
      if (isConnected (min_index, *k))
	new_val = min_value + getEdgeValue (getEdgeIndex (min_index, *k));
      else 
	new_val = MAXINT;
      if  (old_val > new_val) {
	P[ *k ] = P[ min_index ];
	P[ *k ].push_back (*k);
	P[ *k ].setValue (new_val);
      }
    }
  }
  return P;
}
  

template< class Node, class Edge >
Path Graph< Node, Edge >::shortest_path (int a, int b) const
{
  vector< Path > paths = shortest_path (a);
  vector< Path >::iterator i;
  
//    cout << "Shortest path between " << a << " and " << b << endl;
  
//    for (i=paths.begin (); i!=paths.end (); ++i) {
//      if (i->size ()) {
//        cout << *i << endl;;
//      }
//    }
  
  for (i=paths.begin (); i!=paths.end (); ++i) {
    if (i->size ()) {
      if (i->back () == b) {
	return *i;
      }
    }
  }
  return Path ();
}


template< class Node, class Edge >
vector< Edge > Graph< Node, Edge >::minimum_spanning_tree (void) const
{
  vector< int > nearest (size (), -1);
  vector< int > mindist (size (), MAXINT);
  vector< Edge > T;
  int i, j;

  for (i=1; i<(int)size (); ++i) {
    nearest[i] = 0;
    mindist[i] = getEdgeValue (getEdgeIndex (i, 0));
  }

  for (int x=0; x<(int)size ()-1; ++x) {
    int min = MAXINT;
    int k = -1;
    for (j=1; j<(int)size (); ++j) {
      if (mindist[j] >= 0 && mindist[j]<min) {
	min = mindist[j];
	k = j;
      }
    }

    // This is a test to see if we stay in the same connected component
    if (k!=-1) 
      {  
	T.push_back (getEdge (nearest[k], k));
	
	mindist[k] = -1;
	
	for (j=1; j<(int)size (); ++j) {
	  int val = getEdgeValue (getEdgeIndex (j, k));
	  if (val < mindist[j]) {
	    mindist[j] = val;
	    nearest[j] = k;
	  }
	}
      }
  }
  
  return T;
}



// Supposes that edge values are all 1.
template< class Node, class Edge >
vector< Path > 
Graph< Node, Edge >::cycle_base_vismara ()
{
  vector< Path > bag;
  vector< Path >::iterator p, q;
  int r, j, y, z;

  for (unsigned int i = 0; i < mEdges.size (); ++i) mEdgeValues [i] = 1;

  for (r=0; r<(int)size (); ++r) {
//      cout << "r = " << r << endl;
    for (j=r+1; j<(int)size (); ++j) mNodeMarks[j] = false;

    vector< int > Vr;
    vector< Path > sp = shortest_path (r);

    for (p=sp.begin (); p!=sp.end (); ++p) {
      if (p->size () != 0) {
	y = p->back ();
	vector< int > S;
	
//  	cout << " y = " << y << endl;

	for (q=sp.begin (); q!=sp.end (); ++q) {	  
	  if (q->size () != 0 && 
	      isConnected (y, q->back ())) {
	    z = q->back ();
	    
//  	    cout << " z = " << z << endl;

	    Path Prz = shortest_path (r,z);
	    int drz = Prz.getValue ();
	    Path Pry = shortest_path (r,y);
	    int dry = Pry.getValue ();
	    

//  	    cout << " Pry = " << Pry << endl;
//  	    cout << " Prz = " << Prz << endl;

	    if (drz + 1 == dry) {
	      S.push_back (z);
	    }
	    else if ((drz != dry + 1) &&
		     (z < y)) {
	      Path Pryp = Pry;
	      sort (Pryp.begin (), Pryp.end ());
	      Path Przp = Prz; 
	      sort (Przp.begin (), Przp.end ());
      
	      Path inter;
	      set_intersection (Pryp.begin (), Pryp.end (),
				Przp.begin (), Przp.end (),
				inserter (inter, inter.begin ()));

//  	      cout << "Intersection = " << inter << endl;
	      
	      if (inter.size () == 1 && inter.front () == r) {
		Path C = Pry;
		C.insert (C.end (), Prz.rbegin (), Prz.rend ());
		C.pop_back ();
		C.setValue (Prz.getValue () + Pry.getValue () + 1);
		bag.push_back (C);

//  		cout << "Adding " << C << endl;
	      }
	    }
	  }     
	}

//  	cout << " S = " << S.size () << endl;

	int m, n;
	for (m=0; m<(int)S.size (); ++m) {
	  for (n=m+1; n<(int)S.size (); ++n) {
	    Path Prm = shortest_path (r, S[m]);
	    Path Prmp = Prm;
	    sort (Prmp.begin (), Prmp.end ());
	    Path Prn = shortest_path (r, S[n]);
	    Path Prnp = Prn;
	    sort (Prnp.begin (), Prnp.end ());
	    
	    Path inter;
	    set_intersection (Prmp.begin (), Prmp.end (),
			      Prnp.begin (), Prnp.end (),
			      inserter (inter, inter.begin ()));
	    
//  	    cout << "m = " << S[m] << endl;
//  	    cout << "n = " << S[n] << endl;
//  	    cout << "Intersection = " << inter << endl;

	    if (inter.size () == 1 && inter.front () == r) {
	      Path C = Prm;
	      C.push_back (y);
	      C.insert (C.end (), Prn.rbegin (), Prn.rend ());
	      C.pop_back ();
	      C.setValue (Prm.getValue () + Prn.getValue () + 2);
	      bag.push_back (C);
//  	      cout << "Adding " << C << endl;
	    }	  
	  }	
	}
      }
    }
    for (j=r+1; j<(int)size (); ++j) mNodeMarks[j] = true;
  }
  

  // [...]
  // Missing step: list all cycles of each family...
  // [...]

  
//    cout << "sort cycles" << endl;
  sort (bag.begin (), bag.end ());

  {
    cout << endl;
    
    vector< Path >::iterator i;
    for (i=bag.begin (); i!=bag.end (); ++i) {
      cout << (*i) << " " << endl;
    }
  }

  vector< Path > newbag;
  vector< Path > tmpbag;
  int pi;

  for (j=0; j<(int)mEdgeMarks.size (); ++j) mEdgeMarks[j] = false;

  for (p=bag.begin (); p!=bag.end (); ++p) {
    {
      if (p!=bag.begin () && p->size () != (p-1)->size ()) {
	newbag.insert (newbag.end (), tmpbag.begin (), tmpbag.end ());
	for (q=tmpbag.begin (); q!=tmpbag.end (); ++q) {
	  for (pi=0; pi<(int)q->size (); ++pi) {
	    mEdgeMarks[getEdgeIndex ((*q)[pi], (*q)[(pi+1)%q->size ()])] = true;
	  }
	}
	tmpbag.clear ();
      }
      
//        cout << "Considering " << *p << " " << p->size () << endl;

//        cout << *this << endl;

      for (pi=0; pi<(int)p->size (); ++pi) {
//    	cout << " " << (*p)[pi] << " " 
//    	     << " " << (*p)[(pi+1)%p->size ()] << " " 
//    	     << mEdgeMarks[getEdgeIndex ((*p)[pi], (*p)[(pi+1)%p->size ()])] << endl;
	
	if (mEdgeMarks[getEdgeIndex ((*p)[pi], (*p)[(pi+1)%p->size ()])] == false) break;
      }
      if (pi!=(int)p->size ()) tmpbag.push_back (*p);      
    }
    
  }

  newbag.insert (newbag.end (), tmpbag.begin (), tmpbag.end ());

  for (j=0; j<(int)mEdgeMarks.size (); ++j) mEdgeMarks[j] = true;

  cout << "After Gaussian elimination" << endl;

  {
    cout << endl;
    
    vector< Path >::iterator i;
    for (i=newbag.begin (); i!=newbag.end (); ++i) {
      cout << (*i) << " " << endl;
    }
  }


  return newbag;
}



template< class Node, class Edge >
void
Graph< Node, Edge >::order_graph (int index, int depth)
{
  build_tree ();
  for (unsigned int i = 0; i < mNodeMarks.size (); ++i) mNodeMarks[i] = true;
  for (unsigned int i = 0; i < mEdgeMarks.size(); ++i) mEdgeMarks[i] = true;
}






template< class Node, class Edge >
vector< Path > 
Graph< Node, Edge >::cycle_base_horton ()
{
  vector< Path > bag;
  vector< Path >::iterator p;
  Path tmpPath;

  for (unsigned int i = 0; i < mEdges.size (); ++i) mEdgeValues [i] = 1;

  map< int, map< int, Path > > paths;
  for (int i=0; i<(int)size (); ++i) {
    for (int j=0; j<(int)size (); ++j) {
      paths[i][j] = 
	shortest_path (i, j);
    }
  }

  for (int i=0; i<(int)size (); ++i) {
    for (int j=0; j<(int)mEdges.size (); ++j) {

//        unmarkEdge (mEdgeNodes[j].first, mEdgeNodes[j].second);
//        unmarkEdge (mEdgeNodes[j].second, mEdgeNodes[j].first);

//        Path Pvx = shortest_path (i, mEdgeNodes[j].first);
//        Path Pvy = shortest_path (i, mEdgeNodes[j].second);

//        markEdge (mEdgeNodes[j].first, mEdgeNodes[j].second);
//        markEdge (mEdgeNodes[j].second, mEdgeNodes[j].first);

      Path Pvx = paths[i][mEdgeNodes[j].first];
      Path Pvy = paths[i][mEdgeNodes[j].second];

      // if P(v,x) ^ P(v,y) = {v}
      
      Path Pvxp = Pvx; 
      sort (Pvxp.begin (), Pvxp.end ());
      Path Pvyp = Pvy; 
      sort (Pvyp.begin (), Pvyp.end ());
      
      Path inter;
      set_intersection (Pvxp.begin (), Pvxp.end (),
			Pvyp.begin (), Pvyp.end (),
			inserter (inter, inter.begin ()));

//        cout << "Inter = " << inter << endl;

      if (inter.size () == 1 && inter.front () == i) 
	{
//  	  cout << "v=" << i << " {x,y}=" << " " << mEdgeNodes[j].first << ","
//  	       << mEdgeNodes[j].second << endl;
	  
//  	  cout << "Pvx " << Pvx << endl;
//  	  cout << "Pvy " << Pvy << endl;
	  
	  Path C = Pvx;
	  C.insert (C.end (), Pvy.rbegin (), Pvy.rend ());
	  C.pop_back ();
	  C.setValue (Pvx.getValue () + Pvy.getValue () + 1);

//  	  cout << "C = " << C << endl;
	  
	  for (p=bag.begin (); p!=bag.end (); ++p) {
	    //cout << *p << " == " << C << " " << (*p == C) << endl;
	    
	    // Redundancy test
	    if (*p == C) {
	      break;
	    }
	  }
	  if (p==bag.end ()) {
	    bag.push_back (C);
	  }
	}
      
    }
  }
  
  sort (bag.begin (), bag.end ());

  {
    cout << endl;
    
    vector< Path >::iterator i;
    for (i=bag.begin (); i!=bag.end (); ++i) {
      cout << (*i) << " " << endl;
    }
  }

  vector< Path > newbag;
  vector< Path > tmpbag;
  int j;

  for (j=0; j<(int)mEdgeMarks.size (); ++j) mEdgeMarks[j] = false;

  cout << "Gaussian elimination" << endl;

  newbag = gaussian_elimination (bag, false);

  {
    cout << endl;
    
    vector< Path >::iterator i;
    for (i=newbag.begin (); i!=newbag.end (); ++i) {
      cout << (*i) << " " << endl;
    }
  }

  return newbag;
}


template< class Node, class Edge >
vector< Path > 
Graph< Node, Edge >::gaussian_elimination (vector< Path > &bag, bool minimum_basis)
{
  if (bag.size () == 0) return bag;

  vector< bool* > matrix;
  vector< bool* >::iterator n;
  int i, j;
  vector< Path > newbag;
  vector< Path >::iterator p, q;

  vector< vector< Path >::iterator > marked;
  marked.clear ();

  for (p=bag.begin (); p!=bag.end (); ++p) {
    bool* row = new bool[mEdges.size ()];
    memset (row, false, mEdges.size () * sizeof (bool));

    // Let's see if *p is linearly independent to the content of newbag 
    cout << "Treating " << *p << endl;

    for (i=0; i<(int)p->size (); ++i) {
      row[getEdgeIndex ((*p)[i], (*p)[(i+1)%(int)p->size ()])] = true;
    }
 
    bool inserted = false;

    for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
      for (j=0; j<(int)mEdges.size (); ++j) { cout << row[j] << " "; } cout << "  ->  " << flush; for (j=0; j<(int)mEdges.size (); ++j) { cout << (*n)[j] << " "; } cout << endl;
      
      j=0;    
      while (j<(int)mEdges.size () && row[j] == false && (*n)[j] == false) ++j;
      if (j == (int)mEdges.size ()) continue;
      
      if (row[j] == true && (*n)[j] == false) {
	cout << "Marking " << *p << endl;
	marked.push_back (p);
	inserted = true;
	break;
      }
      
      if (row[j] == true && (*n)[j] == true) {
	// Reduce the current
	for (i=0; i<(int)mEdges.size (); ++i) {
	  row[i] = (row[i] + (*n)[i])%2;
	}
	continue;
      }
    }
    
    if (!inserted) {
      for (j=0; j<(int)mEdges.size (); ++j) {
	if (row[j] == true) break;
      }
      if (j!=(int)mEdges.size ()) {
	cout << "Marking " << *p << endl;
	marked.push_back (p);
      } else {
	cout << "Rejecting " << *p << endl;
      }
    }

    delete[] row;

    // Let's see if we should try to insert the marked...
    if (p+1==bag.end () || (p+1)->size () > p->size ()) {

      cout << "Inserting marked cycles" << endl;

      for (i=0; i<(int)marked.size (); ++i) {
	bool* row = new bool[mEdges.size ()];
	memset (row, false, mEdges.size () * sizeof (bool));

	for (j=0; j<(int)marked[i]->size (); ++j) {
	  row[getEdgeIndex ((*marked[i])[j], (*marked[i])[(j+1)%(int)p->size ()])] = true;
	}

	cout << "Treating " << *marked[i] << endl;	

	inserted = false;
	
	for (n=matrix.begin (), q=newbag.begin (); q!=newbag.end (); ++n, ++q) {
	  j=0;    
	  while (j<(int)mEdges.size () && row[j] == false && (*n)[j] == false) ++j;
	  if (j == (int)mEdges.size ()) continue;
	  
	  if (row[j] == true && (*n)[j] == false) {
	    cout << "Inserting " << *marked[i] << endl;
	    matrix.insert (n, row);
	    newbag.insert (q, *marked[i]);
	    inserted = true;
	    break;
	  }
	  
	  if (row[j] == true && (*n)[j] == true) {
	    // Reduce the current
	    for (int k=0; k<(int)mEdges.size (); ++k) {
	      row[k] = (row[k] + (*n)[k])%2;
	    }
	    continue;
	  }
	}
	
	if (!inserted) {
	  if (!minimum_basis) {
	    cout << "Accepting " << *marked[i] << endl;
	    matrix.push_back (row);
	    newbag.push_back (*marked[i]);
	  } else {	    
	    for (j=0; j<(int)mEdges.size (); ++j) {
	      if (row[j] == true) break;
	    }
	    if (j!=(int)mEdges.size ()) {
	      cout << "Accepting " << *marked[i] << endl;
	      matrix.push_back (row);
	      newbag.push_back (*marked[i]);
	    } else {
	      cout << "Rejecting " << *marked[i] << endl;
	    }
	  }	
	}
      }
      marked.clear ();

      cout << "Matrix -----------------------" << endl;
      for (i=0; i!=(int)matrix.size (); ++i) {
	for (j=0; j<(int)mEdges.size (); ++j)
	cout << matrix[i][j] << " " << flush;      
      cout << " : " << newbag[i] << flush;
      cout << endl;
      }
      cout << "------------------------------" << endl;
      
    }
  }
  return newbag;
}



template< class Node, class Edge >
vector< Path > 
Graph< Node, Edge >::cycle_base ()
{
  vector< Path > bag;
  Path tmpPath;
  vector< pair< float, pair< int, int > > > chords;

  for (unsigned int i = 0; i < mEdges.size (); ++i) mEdgeValues [i] = 1;

//    cout << "Building tree" << endl;
  build_tree();
  
//    cout << "Extract chords..." << endl;
  for(int b = 0; b < (int)size() - 1; ++b) {
    for(int a = b + 1; a < (int)size (); ++a) {
      if (getEdgeIndex (a, b) != -1 && mEdgeMarks[getEdgeIndex (a, b)] == false) {

	tmpPath = shortest_path (b, a);
  	chords.push_back (make_pair (tmpPath.getValue (),
  				     make_pair (a, b)));
      	cout << a << ", " << b << " = " << tmpPath << endl;
      }
    }
  }

//    cout << "sort chords" << endl;
  sort (chords.begin (), chords.end ());

//    cout << "Build cycles" << endl;
  for (unsigned int i = 0; i < chords.size (); ++i) {
    int a = chords[i].second.first;
    int b = chords[i].second.second;

    tmpPath = shortest_path (a, b);
//      tmpPath.push_back (a);
    tmpPath.setValue (tmpPath.getValue () + 1);

    cout << "ab = " << a << ", " << b << " -> ";
    cout << " " << tmpPath << endl;

    bag.push_back (tmpPath);
    markEdge (a, b);
    markEdge (b, a);
  }
//    cout << "done." << endl;

  sort (bag.begin (), bag.end ());
  
  return bag;
}

template< class Node, class Edge >
void 
Graph< Node, Edge >::build_tree (int index = -1, int depth = 0)
{
  if (index == -1) {
    for (unsigned int i = 0; i < mNodeMarks.size (); ++i) mNodeMarks[i] = false;
    for (unsigned int i = 0; i < mEdgeMarks.size(); ++i) mEdgeMarks[i] = false;
    mNodeMarks[0] = true;
    index = 0;
  }
  
  mNodeValues[index] = depth;
  
  for(int i = 0; i < (int)size (); ++i) {
    if (getEdgeIndex(index, i) != -1 && mNodeMarks[i] == false) {
      
      markEdge (index, i);
      markEdge (i, index);
      markNode (i);
      
      cout << "Marking node " << i << " edge " << index << " " << i << endl;

      build_tree (i, depth + 1);
    }
  }
}



// I/O  -----------------------------------------------------------------


template< class Node, class Edge >
ostream &Graph< Node, Edge >::output (ostream &out) const 
{
  if  (size() == 0) return out;
  unsigned int i, j;
  int id;
  
  for  (i=0; i<mNodes.size(); i++) {
    out << "Node[ " << i << " ]: " << mNodes[ i ] 
	<< " (value: " << mNodeValues[ i ] << ") " << mNodeMarks[i] << endl;
  }
  out << endl;
  for  (j=0; j<mEdges.size(); j++) {
    out << "Edge[ " << j << " ]: " << mEdges[ j ] 
	<< " (value: " << mEdgeValues[ j ] << ") " << mEdgeMarks[j] << endl; 
  }
  out << endl;
  
  out << "Matrix:" << endl;
  for (i=0 ; i<mNodes.size() ; i++) {
    for (j=0 ; j<mNodes.size() ; j++) {
      id = getEdgeIndex (i, j);
      if  (id != -1)
	out << setw (2) << id << " ";
      else
	out << " - ";
    }
    out << "\n";
  }

//    {
//      out << "Adjacency lists" << endl;
//      for (adjgraph::const_iterator i=begin (); i!=end (); ++i) {
//        out << i->first << " : " ;
//        for (adjlist::const_iterator j=i->second.begin (); 
//  	   j!=i->second.end (); ++j)
//  	out << j->first << " ";
//        out << endl;
//      }
//    }

  return out;
}

template< class Node, class Edge >
iBinstream& Graph< Node, Edge >::input (iBinstream& ibs)
{
  int i, j, size;
  
  ibs >> size;
  for (i=0; i<size; i++) {
    Node n;
    ibs >> n; mNodes.push_back (n);
    int val;
    ibs >> val; mNodeValues.push_back (val);
  }
  
  ibs >> size;
  for (i=0; i<size; i++) {
    Edge e;
    ibs >> e; mEdges.push_back(e);
    int val;
    ibs >> val; mEdgeValues.push_back(val);
  }
  
  int n1, n2;
  int e1;
  ibs >> size;
  for (i=0; i<size; i++) {
    ibs >> n1;
    int size2;
    ibs >> size2;
    for (j=0; j<size2; j++) {
      ibs >> n2 >> e1;
      (*this)[n1][n2] = e1;
    }
  }

  mNodeMarks.resize (mNodes.size (), true);
  mEdgeMarks.resize (mEdges.size (), true);
  
  return ibs;
}
  
template< class Node, class Edge >
oBinstream& Graph< Node, Edge >::output (oBinstream& obs) const
{  
  int i;
  adjlist::const_iterator u;
  adjgraph::const_iterator v;
  
  obs << mNodes.size();
  for (i=0; i<mNodes.size(); i++) {
    obs << mNodes[i];
    obs << mNodeValues[i];
  }
  obs << mEdges.size();
  for (i=0; i<mEdges.size(); i++) {
    obs << mEdges[i];
    obs << mEdgeValues[i];
  }
  
  obs << size();
  for (v=begin(); v!=end(); v++) {
    obs << v->first;
    obs << v->second.size();
    for (u=v->second.begin(); u!=v->second.end(); u++) {
      obs << u->first << u->second;
    }
  }
  
  return obs;
}


#endif
