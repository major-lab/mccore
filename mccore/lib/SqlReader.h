
#ifndef _mccore_RnasqlReader_h_
#define _mccore_RnasqlReader_h_

#include <vector>
#include <sqlplus.hh>

using namespace std;

namespace mccore {
  
  class Atom;
  class ResidueFactoryMethod;
  class Residue;
  class Model;
  class Molecule;
  
  class RnasqlReader
  {
    
  private:

    const char *name;
    ResidueFactoryMethod *residueFM;
    Connection con;
    RnasqlReader() {}
    
  public:
    
    RnasqlReader (const char *name, ResidueFactoryMethod *fm = 0);
    virtual ~RnasqlReader ();
    
  private:
    
    //mccore::Atom* toMccoreAt (int num_At, int id_AtomType);
    //Residue* toMccoreRes (int num_Res, int id_ResidueType);
    Model* toMccoreMod (int num_Mod);
    //Molecule* toMccoreO (string sm);

  public:

    Molecule* read ();
  };
}

#endif
