//                              -*- Mode: C++ -*- 
// test/HomogeneousTransfo.cc
// Copyright © 2005 Laboratoire de Biologie Informatique et Théorique
//                  Université de Montréal.
// Author           : Philippe Thibault <thibaup@yoda.iro.umontreal.ca>
// Created On       : Tue Jan 11 13:24:06 2005
// $Revision: 1.1 $
// $Id: HomogeneousTransfo.cc,v 1.1 2005-01-11 19:51:22 thibaup Exp $
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <iostream>
#include <fstream>
#include <list>

#include "Binstream.h"
#include "Messagestream.h"
#include "HomogeneousTransfo.h"
#include "Exception.h"


using namespace std;
using namespace mccore;


int main (int argc, char** argv)
{
  try
  {
    list< HomogeneousTransfo > tfos;
    list< HomogeneousTransfo >::iterator it;
    HomogeneousTransfo I;

    Vector3D v1 (0.9, -999, 89.0076);
    Vector3D v2 (-0.0009, 79.987, -89);
    Vector3D v3 (2.789, -999, -9.7);
    Vector3D v4 (781.9, 9999.89, 5.45);
    Vector3D v5 (-23.9, -9, -89);

    Vector3D i (1.0, 0.0, 0.0), j (0.0, 1.0, 0.0), k (0.0, 0.0, 1.0);

    Vector3D u (0.5570860145311556,0.7427813527082074,0.3713906763541037);
    Vector3D v (-0.787070348709251,0.6148987099291023,-0.049191896794328185);
    Vector3D w (-0.26490647141300877,-0.26490647141300877,0.9271726499455307);
    

    tfos.push_back (I);
    tfos.back ().setIdentity ();
      
    tfos.push_back (I);
    tfos.back () = tfos.back ().rotate (v4, 3.5) * tfos.back ().translate (v1);

    tfos.push_back (HomogeneousTransfo::rotation (v4, 3.5) *
		    HomogeneousTransfo::translation (v2) *
		    HomogeneousTransfo::translation (v3));

    tfos.push_back (tfos.back ());
    tfos.back () = tfos.back ().invert ();

    tfos.push_back (tfos.back ());
    tfos.back () *= HomogeneousTransfo::rotation (v4, 3.5) *
      HomogeneousTransfo::translation (v2) *
      HomogeneousTransfo::translation (v3);

    tfos.push_back (HomogeneousTransfo::align (v3, v1, v4));
    tfos.push_back (HomogeneousTransfo::frame (u, v, w, v2));

    if (argc > 1)
    {
      // remake good files
      ozfBinstream obs ("HomogeneousTransfo.bin.gz");
      obs << (unsigned int)tfos.size ();
      for (it = tfos.begin (); it != tfos.end (); ++it)
	obs << *it;
      obs.close ();
      gOut (0) << "wrote HomogeneousTransfo.bin.gz" << endl;

      ofstream ofs ("HomogeneousTransfo.good");
      for (it = tfos.begin (); it != tfos.end (); ++it)
	ofs << "ok" << endl;
      ofs.close ();
      gOut (0) << "wrote HomogeneousTransfo.good" << endl;
    }
    else
    {
      izfBinstream ibs ("HomogeneousTransfo.bin.gz");
      if (ibs.fail ())
	throw Exception ("failed to open file \"HomogeneousTransfo.bin.gz\"");

      float d;
      unsigned int qty;
      list< HomogeneousTransfo > ref;
      list< HomogeneousTransfo >::iterator it1, it2;

      for (ibs >> qty; qty > 0; --qty)
      {
	ibs >> I;
	ref.push_back (I);
      }

      if (ref.size () != tfos.size ())
	throw Exception ("binary reference file corrupted");

      for (it1 = tfos.begin (), it2 = ref.begin (); it1 != tfos.end (); ++it1, ++it2)
	if ((d = it1->rmsd (*it2)) > 0.001)
	  cout << d << endl;
	else
	  cout << "ok" << endl;
    }
  


  }
  catch (Exception& ex)
  {
    gErr (0) << argv[0] << ": " << ex << endl;
    return EXIT_FAILURE;
  }
  return 0;
}
