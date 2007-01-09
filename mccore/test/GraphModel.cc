//                              -*- Mode: C++ -*- 
// GraphModel.cc
// Copyright © 2004-06 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Martin Larose
// Created On       : Wed Dec 29 00:44:53 2004
// $Revision: 1.5 $
// $Id: GraphModel.cc,v 1.5 2007-01-09 00:13:14 larosem Exp $
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

#include "AbstractModel.h"
#include "GraphModel.h"
#include "Messagestream.h"
#include "Pdbstream.h"
#include "Exception.h"
#include "stlio.h"

using namespace mccore;
using namespace std;



int
main (int argc, char *argv[])
{
  GraphModel model;
  GraphModel model2;
  
  try
    {
      izfPdbstream ifs;
    
      ifs.open ("1L8V.pdb.gz");

      if (! ifs)
	{
	  IntLibException ex ("failed to open \"1L8V.pdb.gz\"", __FILE__, __LINE__);
	  throw ex;
	}

      ifs >> model;
      ifs.close ();

      model.annotate ();
      gOut (0) << "Size: " << model.size ()
	       << " Edge size: " << model.edgeSize ()
	       << endl;
      gOut (0) << model << endl;
    }
  catch (Exception& ex)
    {
      gErr (0) << argv[0] << ": " << ex << endl;
      return EXIT_FAILURE;
    }

  AbstractModel &absModel = model;
  GraphModel model3 (absModel);

  model2 = absModel;
  model.clear ();

  gOut (0) << "copy constructor with AbstractModel&" << endl
	   << "Size: " << model3.size ()
	   << " Edge size: " << model3.edgeSize ()
	   << endl << model3 << endl;
  gOut (0) << "operator= with AbstractModel&" << endl
	   << "Size: " << model2.size ()
	   << " Edge size: " << model2.edgeSize ()
	   << endl << model2 << endl;

  gOut (0) << "copy constructor with GraphModel&" << endl;
  GraphModel model4 (model2);

  model2.clear ();
  gOut (0) << "Size: " << model4.size ()
	   << " Edge size: " << model4.edgeSize ()
	   << endl << model4 << endl;
  gOut (0) << "operator= with GraphModel&" << endl;
  model = model4;
  model4.clear ();
  gOut (0) << "Size: " << model.size ()
	   << " Edge size: " << model.edgeSize ()
	   << endl << model << endl;

  return EXIT_SUCCESS;
}
  
  
    
