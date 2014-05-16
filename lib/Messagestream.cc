// Messagestream.cc
// Copyright © 2003-04, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal.
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

#include <config.h>

#include "Messagestream.h"

namespace mccore
{
  oMessagestream gOut (cout, 2);
  oMessagestream gErr (cerr, 2);

}
