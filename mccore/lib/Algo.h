//                              -*- Mode: C++ -*- 
// Algo.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sebastien Lemieux
// Created On       : Wed Feb 14 15:33:58 2001
// Last Modified By : Sebastien Lemieux
// Last Modified On : Wed Feb 14 16:12:20 2001
// Update Count     : 31
// Status           : Unknown.
// 

#include <math.h>
#include <vector.h>
#include <pair.h>
#include <map.h>
#include <algorithm>
#include "CResidue.h"
#include "ResidueType.h"

class Algo {
private:

  template< class iterator >
  class ResidueRange {
    iterator mRes;
    float mMin;
    float mMax;
  public:
    ResidueRange (iterator nRes, float nMin, float nMax)
      : mRes (nRes), mMin (nMin), mMax (nMax) {}
    bool operator< (const ResidueRange &o) const { return mMin < o.mMin; }
    void Min (float nMin) { if (nMin < mMin) mMin = nMin; }
    void Max (float nMax) { if (nMax > mMax) mMax = nMax; }
    float Min () const { return mMin; }
    float Max () const { return mMax; }
    bool Overlap (const ResidueRange &o) const {
      if (mMin < o.mMin) {
	if (o.mMin <= mMax) return true;
	else return false;
      } else {
	if (mMin <= o.mMax) return true;
	else return false;
      }
    }
    iterator GetResidue () { return mRes; }
    void Output (ostream &out) {
      out << (CResId)(*mRes) << " : " << mMin << "-" << mMax << endl;
    }
  };
  
  template< class iterator >
  static
  void
  ExtractContact_OneDim (vector< ResidueRange< iterator > > &range, 
			 map< pair< iterator, iterator >, int > &contact,
			 float cutoff) {
    
    for (vector< ResidueRange< iterator > >::iterator i = range.begin (); i != range.end (); ++i) {
      for (vector< ResidueRange< iterator > >::iterator j = i; j != range.end (); ++j) if (i != j) {
	if ((j->Min () - cutoff) <= i->Max ()) {
	  int c;
	  if (i->GetResidue () < j->GetResidue ()) c = ++contact[make_pair (i->GetResidue (), j->GetResidue ())];
	  else c = ++contact[make_pair (j->GetResidue (), i->GetResidue ())];
	} else break;
      }
    }
  }


public:

  template< class iterator >
  static
  vector< pair< iterator, iterator > >
  ExtractContact_AABB (iterator begin, iterator end, float cutoff) {
    vector< pair< iterator, iterator > > result;

    vector< ResidueRange< iterator > > X_range;
    vector< ResidueRange< iterator > > Y_range;
    vector< ResidueRange< iterator > > Z_range;
    
    for (iterator i = begin; i != end; ++i) 
      if (i->GetType ()->is_NucleicAcid ()) {
	ResidueRange< iterator > tmp_X (i, FLT_MAX, -FLT_MAX);
	ResidueRange< iterator > tmp_Y (i, FLT_MAX, -FLT_MAX);
	ResidueRange< iterator > tmp_Z (i, FLT_MAX, -FLT_MAX);
	for (CResidue::iterator j = i->begin (); j != i->end (); ++j) {
	  tmp_X.Max (j->GetX ());
	  tmp_X.Min (j->GetX ());
	  tmp_Y.Max (j->GetY ());
	  tmp_Y.Min (j->GetY ());
	  tmp_Z.Max (j->GetZ ());
	  tmp_Z.Min (j->GetZ ());
	}
	X_range.push_back (tmp_X);
	Y_range.push_back (tmp_Y);
	Z_range.push_back (tmp_Z);
      }
    sort (X_range.begin (), X_range.end ());
    sort (Y_range.begin (), Y_range.end ());
    sort (Z_range.begin (), Z_range.end ());
    
    map< pair< iterator, iterator >, int > contact;
    
    ExtractContact_OneDim (X_range, contact, cutoff);
    ExtractContact_OneDim (Y_range, contact, cutoff);
    
    for (map< pair< iterator, iterator >, int >::iterator i = contact.begin ();
	 i != contact.end (); ++i) {
      map< pair< iterator, iterator >, int >::iterator tmp = i;  tmp++;
      if (i->second < 2) contact.erase (i);
      i = tmp;  i--;
    }
    
    ExtractContact_OneDim (Z_range, contact, cutoff);
    
    for (map< pair< iterator, iterator >, int >::iterator i = contact.begin ();
	 i != contact.end (); ++i)
      if (i->second == 3) result.push_back (i->first);
    
    return result;
  }
  

};
