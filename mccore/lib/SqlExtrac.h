
#ifndef _mccore_sqlExtrac_h_
#define _mccore_sqlExtrac_h_

#include <vector>
#include <sqlplus.hh>

using namespace std;

namespace mccore {
  
  class Atom;
  class ResidueFactoryMethod;
  class Residue;
  class Model;
  class Molecule;
  
  class sqlExtrac
  {
    
  private:

    const char *name;
    ResidueFactoryMethod *residueFM;
    Connection con;
    sqlExtrac() {}
    
  public:
    
    sqlExtrac (const char *name);
    virtual ~sqlExtrac ();
    
  private:
    
    Model* toExtrac (int num_Mod);

  public:

    Molecule* read ();
  };
}

#endif
