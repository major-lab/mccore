#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>
#include <errno.h>

#include "Atom.h"
#include "AtomType.h"
#include "Messagestream.h"
#include "Model.h"
#include "Molecule.h"
#include "ResId.h"
#include "Residue.h"
#include "ResidueFactoryMethod.h"
#include "ResidueType.h"
#include "SqlReader.h"
#include "SqlExtrac.h"

namespace mccore {

  sqlExtrac::sqlExtrac (const char *name)
  : name(name), con(use_exceptions)
  {
    
  }
  
  sqlExtrac::~sqlExtrac ()
  {
   
  }

  Molecule*
  sqlExtrac::read()
  {
    con.connect("database", "alpaga", "mccore", "mccoreweb");
    Molecule *molecule;
    molecule= new Molecule();
    int num_Mol=0;

    return molecule;
  }

  Model*
  sqlExtrac::toExtrac (int num_Mod)
  {
    Model *m;
    m = new Model ();

    return m;
  }
}
