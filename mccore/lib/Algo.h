//                              -*- Mode: C++ -*- 
// Algo.h
// Copyright © 2001 Laboratoire de Biologie Informatique et Théorique.
//                  Université de Montréal.
// Author           : Sebastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : Wed Feb 14 15:33:58 2001
// Last Modified By : Martin Larose
// Last Modified On : Tue Aug 14 12:33:17 2001
// Update Count     : 43
// Status           : Unknown.
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


#include <math.h>
#include <vector.h>
#include <pair.h>
#include <map.h>
#include <algo.h>
#include "CResidue.h"
#include "ResidueType.h"
#include "CAtom.h"

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
  static void ExtractContact_OneDim (vector< ResidueRange< iterator > > &range, 
				     map< pair< iterator, iterator >, int > &contact,
				     float cutoff)
  {
    vector< ResidueRange< iterator > >::iterator i;
    
    for (i = range.begin (); i != range.end (); ++i)
      {
	vector< ResidueRange< iterator > >::iterator j;
	
	for (j = i; j != range.end (); ++j)
	  if (i != j)
	    {
	      if (j->Min () - cutoff <= i->Max ())
		{
		  if (i->GetResidue () < j->GetResidue ())
		    ++contact[make_pair (i->GetResidue (), j->GetResidue ())];
		  else
		    ++contact[make_pair (j->GetResidue (), i->GetResidue ())];
		}
	      else
		break;
	    }
      }
  }


public:

  template< class iterator >
  static vector< pair< iterator, iterator > > ExtractContact_AABB (iterator begin, iterator end, float cutoff) 
  {
    vector< pair< iterator, iterator > > result;
    vector< ResidueRange< iterator > > X_range;
    vector< ResidueRange< iterator > > Y_range;
    vector< ResidueRange< iterator > > Z_range;
    iterator i;

    for (i = begin; i != end; ++i) 
      if (i->GetType ()->is_NucleicAcid ())
	{
	  CResidue::iterator j;
	  ResidueRange< iterator > tmp_X (i, HUGE, -HUGE);
	  ResidueRange< iterator > tmp_Y (i, HUGE, -HUGE);
	  ResidueRange< iterator > tmp_Z (i, HUGE, -HUGE);
	  
	  for (j = i->begin (); j != i->end (); ++j)
	    {
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
    std::sort (X_range.begin (), X_range.end ());
    std::sort (Y_range.begin (), Y_range.end ());
    std::sort (Z_range.begin (), Z_range.end ());
    
    map< pair< iterator, iterator >, int > contact;
    
    ExtractContact_OneDim (X_range, contact, cutoff);
    ExtractContact_OneDim (Y_range, contact, cutoff);

    map< pair< iterator, iterator >, int >::iterator cont_i;
    for (cont_i = contact.begin (); cont_i != contact.end (); ++cont_i)
      {
	map< pair< iterator, iterator >, int >::iterator tmp = cont_i;

	tmp++;
	if (cont_i->second < 2)
	  contact.erase (cont_i);
	// For an unknown reason, when the map is empty, 
	// cont_i-- does not points to contact.begin (), so this test is added:
	if (contact.size () == 0)
	  break;
	cont_i = tmp;
	cont_i--;
      }
    
    ExtractContact_OneDim (Z_range, contact, cutoff);
    
    for (cont_i = contact.begin (); cont_i != contact.end (); ++cont_i)
      if (cont_i->second == 3)
	result.push_back (cont_i->first);
    return result;
  }
};
