// AtomTypeStore.h
// Copyright © 2003-07, 2014 Laboratoire de Biologie Informatique et Theorique
//                     Universite de Montreal.
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


#ifndef _mccore_AtomTypeStore_h_
#define _mccore_AtomTypeStore_h_

#include <map>
#include <set>

#include "AtomType.h"

using namespace std;


namespace mccore
{
  class ResidueType;

  /**
   * @short Repository of atomtypes.
   */
  class AtomTypeStore
  {

    /**
     * The type repository
     */
    std::set< AtomType*, AtomType::less_deref > repository;
    std::map< std::string, const AtomType* > mapping;

  public:

    // LIFECYCLE ---------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomTypeStore ();

    /**
     * Destroys the object.
     */
    ~AtomTypeStore ();

    // METHODS -----------------------------------------------------------------

    /**
     * Gets the atomtype represented by the string if one exists.
     * @param key string key representing the atom type.
     * @return the matching atom type or a new one if none existed.
     */
    const AtomType* get (const string& key);

    void addMapping(const string& key, const AtomType* apType);

  private:

    // TYPES -------------------------------------------------------------------

    class Null : public virtual AtomType 
    {
    public:
      Null () {}
      Null (const string& ks) : AtomType (ks) {}

      virtual bool isNull () const { return true; }
      virtual bool describe (const AtomType* t) const
      {
        return dynamic_cast< const Null* > (t);
      }
    };

    /**
     * Public abstract class for unknown residues.
     */
    class Unknown : public virtual AtomType {
    public:      
      Unknown () {}
      Unknown (const string& ks) : AtomType (ks) {}
      
      virtual bool isUnknown () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Unknown* > (t);
      }
    };
    
    /**
     * Private abstract class for amino acid atoms.
     */
    class AminoAcid : public virtual AtomType {
    public:      
      AminoAcid () {}
      AminoAcid (const string& ks) : AtomType (ks) {}

      virtual bool isAminoAcid () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AminoAcid* > (t);
      }

    };
    
    /**
     * Private abstract class for nucleic acid atoms.
     */
    class NucleicAcid : public virtual AtomType {
    public:
      NucleicAcid () {}
      NucleicAcid (const string& ks) : AtomType (ks) {}

      virtual bool isNucleicAcid () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const NucleicAcid* > (t);
      }

    };

    /**
     * Private abstract class for backbone atoms.
     */
    class Backbone : public virtual AtomType {
    public:
      Backbone () {}
      Backbone (const string& ks) : AtomType (ks) {}

      virtual bool isBackbone () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Backbone* > (t);
      }


      
    };

    /**
     * Private abstract class for phosphate atoms.
     */
    class Phosphate : public virtual AtomType {
    public:
      Phosphate () {}
      Phosphate (const string& ks) : AtomType (ks) {}

      virtual bool isPhosphate () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Phosphate* > (t);
      }


      
    };
    
    /**
     * Private abstract class for sidechain atoms.
     */
    class SideChain : public virtual AtomType {
    public:
      SideChain () {}
      SideChain (const string& ks) : AtomType (ks) {}

      virtual bool isSideChain () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const SideChain* > (t);
      }


      
    };

    /**
     * Private abstract class for carbon atoms.
     */
    class Carbon : public virtual AtomType {
    public:
      Carbon () {}
      Carbon (const string& ks) : AtomType (ks) {}

      virtual bool isCarbon () const { return true; }
      virtual bool describe (const AtomType* t) const {
       return dynamic_cast< const Carbon* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.60, 0.60, 0.60);
      }
      
    };

    /**
     * Private abstract class for hydrogen atoms.
     */
    class Hydrogen : public virtual AtomType {
    public:
      Hydrogen () {}
      Hydrogen (const string& ks) : AtomType (ks) {}

      virtual bool isHydrogen () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Hydrogen* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (1.00, 1.00, 1.00);
      }
      
    };

    /**
     * Private abstract class for lonepair atoms.
     */
    class LonePair : public virtual AtomType {
    public:
      LonePair () {}
      LonePair (const string& ks) : AtomType (ks) {}

      virtual bool isLonePair () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const LonePair* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.00, 0.80, 0.00);
      }

      
    };

    /**
     * Private abstract class for magnesium atoms.
     */
    class Magnesium : public virtual AtomType {
    public:
      Magnesium () {}
      Magnesium (const string& ks) : AtomType (ks) {}

      virtual bool isMagnesium () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Magnesium* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.13, 0.54, 0.13);
      }
      
    };

    /**
     * Private abstract class for nitrogen atoms.
     */
    class Nitrogen : public virtual AtomType {
    public:
      Nitrogen () {}
      Nitrogen (const string& ks) : AtomType (ks) {}

      virtual bool isNitrogen () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Nitrogen* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.20, 0.15, 0.80);
      }
      
    };

    /**
     * Private abstract class for oxygen atoms.
     */
    class Oxygen : public virtual AtomType {
    public:
      Oxygen () {}
      Oxygen (const string& ks) : AtomType (ks) {}

      virtual bool isOxygen () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Oxygen* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.76, 0.00, 0.00);
      }

      
    };

    /**
     * Private abstract class for phosphorus atoms.
     */
    class Phosphorus : public virtual AtomType {
    public:
      Phosphorus () {}
      Phosphorus (const string& ks) : AtomType (ks) {}

      virtual bool isPhosphorus () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Phosphorus* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.82, 0.53, 0.00);
      }

      
    };

    /**
     * Private abstract class for pseudo atoms.
     */
    class Pseudo : public virtual AtomType {
    public:
      Pseudo () {}
      Pseudo (const string& ks) : AtomType (ks) {}

      virtual bool isPseudo () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Pseudo* > (t);
      }


      
    };

    /**
     * Private abstract class for sulfur atoms.
     */
    class Sulfur : public virtual AtomType {
    public:
      Sulfur () {}
      Sulfur (const string& ks) : AtomType (ks) {}

      virtual bool isSulfur () const { return true; }
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const Sulfur* > (t);
      }
      virtual Vector3D getColor () const {
	return Vector3D (0.80, 0.80, 0.00);
      }

      
    };

    /**
     * Global C1p atom type class.
     */
    class AC1p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC1p () {}
      AC1p (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC1p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }
      
      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }
      
      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C2p atom type class.
     */
    class AC2p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC2p () {}
      AC2p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC2p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;



      
    };

    /**
     * Global C3p atom type class.
     */
    class AC3p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC3p () {}
      AC3p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC3p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C4p atom type class.
     */
    class AC4p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC4p () {}
      AC4p (const string& ks) : AtomType (ks) {}
 
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC4p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C5p atom type class.
     */
    class AC5p : public virtual NucleicAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC5p () {}
      AC5p (const string& ks) : AtomType (ks) {}
 
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC5p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H1p atom type class.
     */
    class AH1p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH1p () {}
      AH1p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH1p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.2870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.2870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H2p atom type class.
     */
    class AH2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH2p () {}
      AH2p (const string& ks) : AtomType (ks) {}
  
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH2p* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H3p atom type class.
     */
    class AH3p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH3p () {}
      AH3p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH3p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H4p atom type class.
     */
    class AH4p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH4p () {}
      AH4p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH4p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H5p atom type class.
     */
    class AH5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH5p () {}
      AH5p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH5p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O1P atom type class.
     */
    class AO1P : public virtual NucleicAcid, public virtual Oxygen, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AO1P () {}
      AO1P (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO1P* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O2p atom type class.
     */
    class AO2p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO2p () {}
      AO2p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO2p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.7210.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.7210; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2104.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2104; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O2P atom type class.
     */
    class AO2P : public virtual NucleicAcid, public virtual Oxygen, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AO2P () {}
      AO2P (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO2P* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O3p atom type class.
     */
    class AO3p : public virtual NucleicAcid, public virtual Oxygen, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AO3p () {}
      AO3p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO3p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the returned value depends if the residue is a terminal.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the returned value depends if the residue is a terminal.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O3P atom type class.
     */
    class AO3P : public virtual NucleicAcid, public virtual Oxygen, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AO3P () {}
      AO3P (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO3P* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O4p atom type class.
     */
    class AO4p : public virtual NucleicAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO4p () {}
      AO4p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO4p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6837.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6837; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O5p atom type class.
     */
    class AO5p : public virtual NucleicAcid, public virtual Oxygen, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AO5p () {}
      AO5p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO5p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the returned value depends if the residue is a terminal.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the returned value depends if the residue is a terminal.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global P atom type class.
     */
    class AP : public virtual NucleicAcid, public virtual Phosphorus, public virtual Phosphate, public virtual Backbone
    { 
    public:
      AP () {}
      AP (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AP* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 2.1000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 2.1000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;



      
    };

    /**
     * Global 1H2p atom type class.
     */
    class A1H2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H2p () {}
      A1H2p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H2p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H5p atom type class.
     */
    class A1H5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H5p () {}
      A1H5p (const string& ks) : AtomType (ks) {}
 
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H5p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H2p atom type class.
     */
    class A2H2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H2p () {}
      A2H2p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H2p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H5p atom type class.
     */
    class A2H5p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H5p () {}
      A2H5p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H5p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HO2p atom type class.
     */
    class AHO2p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHO2p () {}
      AHO2p (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHO2p* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.  The value is not defined
       * in Amber.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber epsilon value for the atom.  The value is not defined
       * in Amber.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HO3p atom type class.
     */
    class AHO3p : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHO3p () {}
      AHO3p (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHO3p* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.  The value is not defined
       * in Amber.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber epsilon value for the atom.  The value is not defined
       * in Amber.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * The value is not defined in Amber.
       * @param res the residue type.
       * @return 0.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0; }


      
    };

    /**
     * Global C2 atom type class.
     */
    class AC2 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC2 () {}
      AC2 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C4 atom type class.
     */
    class AC4 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC4 () {}
      AC4 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC4* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C5 atom type class.
     */
    class AC5 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC5 () {}
      AC5 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC5* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C5M atom type class.
     */
    class AC5M : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC5M () {}
      AC5M (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC5M* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return -0.2269; }


      
    };

    /**
     * Global C6 atom type class.
     */
    class AC6 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC6 () {}
      AC6 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C8 atom type class.
     */
    class AC8 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      AC8 () {}
      AC8 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC8* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H1 atom type class.
     */
    class AH1 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH1 () {}
      AH1 (const string& ks) : AtomType (ks) {}

      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH1* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H2 atom type class.
     */
    class AH2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH2 () {}
      AH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3590.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3590; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H3 atom type class.
     */
    class AH3 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH3 () {}
      AH3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH3* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H5 atom type class.
     */
    class AH5 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH5 () {}
      AH5 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH5* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4590.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4590; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H6 atom type class.
     */
    class AH6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH6 () {}
      AH6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4090.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4090; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H7 atom type class.
     */
    class AH7 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH7 () {}
      AH7 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH7* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.0770; }


      
    };

    /**
     * Global H8 atom type class.
     */
    class AH8 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AH8 () {}
      AH8 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH8* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3590.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3590; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N1 atom type class.
     */
    class AN1 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN1 () {}
      AN1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN1* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N2 atom type class.
     */
    class AN2 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN2 () {}
      AN2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N3 atom type class.
     */
    class AN3 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN3 () {}
      AN3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN3* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N4 atom type class.
     */
    class AN4 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN4 () {}
      AN4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN4* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N6 atom type class.
     */
    class AN6 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN6 () {}
      AN6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N7 atom type class.
     */
    class AN7 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN7 () {}
      AN7 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN7* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N9 atom type class.
     */
    class AN9 : public virtual NucleicAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AN9 () {}
      AN9 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN9* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O2 atom type class.
     */
    class AO2 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO2 () {}
      AO2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O4 atom type class.
     */
    class AO4 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO4 () {}
      AO4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO4* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O6 atom type class.
     */
    class AO6 : public virtual NucleicAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AO6 () {}
      AO6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H2 atom type class.
     */
    class A1H2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H2 () {}
      A1H2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H4 atom type class.
     */
    class A1H4 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H4 () {}
      A1H4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H4* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H5M atom type class.
     */
    class A1H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H5M () {}
      A1H5M (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H5M* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H6 atom type class.
     */
    class A1H6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1H6 () {}
      A1H6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H2 atom type class.
     */
    class A2H2 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H2 () {}
      A2H2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H2* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H4 atom type class.
     */
    class A2H4 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H4 () {}
      A2H4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H4* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H5M atom type class.
     */
    class A2H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H5M () {}
      A2H5M (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H5M* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2H6 atom type class.
     */
    class A2H6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2H6 () {}
      A2H6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H6* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 3H5M atom type class.
     */
    class A3H5M : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3H5M () {}
      A3H5M (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3H5M* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    
    /**
     * Global PSX atom type class.
     */
    class APSX : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSX () {}
      APSX (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const APSX* > (t);
      }

      /**
       * Gets the Van Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return Pseudo::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return Pseudo::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return Pseudo::getAmberCharge (r); }


      
    };

    
    /**
     * Global PSY atom type class.
     */
    class APSY : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSY () {}
      APSY (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const APSY* > (t);
      }

      /**
       * Gets the Van Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return Pseudo::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return Pseudo::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return Pseudo::getAmberCharge (r); }


      
    };

    /**
     * Global PSZ atom type class.
     */
    class APSZ : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSZ () {}
      APSZ (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const APSZ* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return Pseudo::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return Pseudo::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Pseudo atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return Pseudo::getAmberCharge (r); }


      
    };


    /**
     * Global PSO atom type class.
     */
    class APSO : public virtual NucleicAcid, public virtual Pseudo, public virtual SideChain
    { 
    public:
      APSO () {}
      APSO (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const APSO* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return Pseudo::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return Pseudo::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Pseudo atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return Pseudo::getAmberCharge (r); }


      
    };

    /**
     * Global LP1 atom type class.
     */
    class ALP1 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP1 () {}
      ALP1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ALP1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global LP3 atom type class.
     */
    class ALP3 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP3 () {}
      ALP3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ALP3* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global LP7 atom type class.
     */
    class ALP7 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      ALP7 () {}
      ALP7 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ALP7* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 1LP2 atom type class.
     */
    class A1LP2 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP2 () {}
      A1LP2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1LP2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 1LP4 atom type class.
     */
    class A1LP4 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP4 () {}
      A1LP4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1LP4* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 1LP6 atom type class.
     */
    class A1LP6 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A1LP6 () {}
      A1LP6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1LP6* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 2LP2 atom type class.
     */
    class A2LP2 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP2 () {}
      A2LP2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2LP2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 2LP4 atom type class.
     */
    class A2LP4 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP4 () {}
      A2LP4 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2LP4* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global 2LP6 atom type class.
     */
    class A2LP6 : public virtual NucleicAcid, public virtual LonePair, public virtual SideChain
    { 
    public:
      A2LP6 () {}
      A2LP6 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2LP6* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return LonePair::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the LonePair atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return LonePair::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the LonePair atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return LonePair::getAmberCharge (r); }


      
    };

    /**
     * Global H3T atom type class.
     */
    class AH3T : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH3T () {}
      AH3T (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH3T* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H5T atom type class.
     */
    class AH5T : public virtual NucleicAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH5T () {}
      AH5T (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH5T* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global C atom type class.
     */
    class AC : public virtual AminoAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      AC () {}
      AC (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AC* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CA atom type class.
     */
    class ACA : public virtual AminoAcid, public virtual Carbon, public virtual Backbone
    { 
    public:
      ACA () {}
      ACA (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACA* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CB atom type class.
     */
    class ACB : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACB () {}
      ACB (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACB* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CD atom type class.
     */
    class ACD : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD () {}
      ACD (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACD* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the value depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CD1 atom type class.
     */
    class ACD1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD1 () {}
      ACD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the value depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CD2 atom type class.
     */
    class ACD2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACD2 () {}
      ACD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CE atom type class.
     */
    class ACE : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE () {}
      ACE (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACE* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CE1 atom type class.
     */
    class ACE1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE1 () {}
      ACE1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACE1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CE2 atom type class.
     */
    class ACE2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE2 () {}
      ACE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CE3 atom type class.
     */
    class ACE3 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACE3 () {}
      ACE3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACE3* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CG atom type class.
     */
    class ACG : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG () {}
      ACG (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACG* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the value depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CG1 atom type class.
     */
    class ACG1 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG1 () {}
      ACG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CG2 atom type class.
     */
    class ACG2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACG2 () {}
      ACG2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACG2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1094.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1094; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CH2 atom type class.
     */
    class ACH2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACH2 () {}
      ACH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACH2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CZ atom type class.
     */
    class ACZ : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ () {}
      ACZ (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACZ* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CZ2 atom type class.
     */
    class ACZ2 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ2 () {}
      ACZ2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACZ2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global CZ3 atom type class.
     */
    class ACZ3 : public virtual AminoAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACZ3 () {}
      ACZ3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ACZ3* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.9080.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.9080; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0860.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0860; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global H atom type class.
     */
    class AH : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AH () {}
      AH (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AH* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1H atom type class.
     */
    class A1H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A1H () {}
      A1H (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1H* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global 2H atom type class.
     */
    class A2H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A2H () {}
      A2H (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2H* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global 3H atom type class.
     */
    class A3H : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      A3H () {}
      A3H (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3H* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global HA atom type class.
     */
    class AHA : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA () {}
      AHA (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHA* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HA1 atom type class.
     */
    class AHA1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA1 () {}
      AHA1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHA1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HA2 atom type class.
     */
    class AHA2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHA2 () {}
      AHA2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHA2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.3870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.3870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HB atom type class.
     */
    class AHB : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB () {}
      AHB (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHB* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HB1 atom type class.
     */
    class AHB1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB1 () {}
      AHB1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHB1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HB2 atom type class.
     */
    class AHB2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB2 () {}
      AHB2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHB2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HB3 atom type class.
     */
    class AHB3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHB3 () {}
      AHB3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHB3* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HD1 atom type class.
     */
    class AHD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHD1 () {}
      AHD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HD2 atom type class.
     */
    class AHD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHD2 () {}
      AHD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HE atom type class.
     */
    class AHE : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE () {}
      AHE (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHE* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HE1 atom type class.
     */
    class AHE1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE1 () {}
      AHE1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHE1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HE2 atom type class.
     */
    class AHE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE2 () {}
      AHE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HE3 atom type class.
     */
    class AHE3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHE3 () {}
      AHE3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHE3* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HG atom type class.
     */
    class AHG : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG () {}
      AHG (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHG* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HG1 atom type class.
     */
    class AHG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG1 () {}
      AHG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HG2 atom type class.
     */
    class AHG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHG2 () {}
      AHG2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHG2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HH atom type class.
     */
    class AHH : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHH () {}
      AHH (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHH* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HH2 atom type class.
     */
    class AHH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHH2 () {}
      AHH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHH2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4590.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4590; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HXT atom type class.
     */
    class AHXT : public virtual AminoAcid, public virtual Hydrogen, public virtual Backbone
    { 
    public:
      AHXT () {}
      AHXT (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHXT* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global HZ atom type class.
     */
    class AHZ : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ () {}
      AHZ (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHZ* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4590.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4590; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0150.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0150; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HZ1 atom type class.
     */
    class AHZ1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ1 () {}
      AHZ1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHZ1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HZ2 atom type class.
     */
    class AHZ2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ2 () {}
      AHZ2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHZ2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global HZ3 atom type class.
     */
    class AHZ3 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      AHZ3 () {}
      AHZ3 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AHZ3* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getVDWR (const ResidueType *r) const;

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the result depends of the residue type.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const;

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global N atom type class.
     */
    class AN : public virtual AminoAcid, public virtual Nitrogen, public virtual Backbone
    { 
    public:
      AN () {}
      AN (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AN* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global ND1 atom type class.
     */
    class AND1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AND1 () {}
      AND1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AND1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global ND2 atom type class.
     */
    class AND2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      AND2 () {}
      AND2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AND2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NE atom type class.
     */
    class ANE : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE () {}
      ANE (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANE* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NE1 atom type class.
     */
    class ANE1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE1 () {}
      ANE1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANE1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NE2 atom type class.
     */
    class ANE2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANE2 () {}
      ANE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NH1 atom type class.
     */
    class ANH1 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANH1 () {}
      ANH1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANH1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NH2 atom type class.
     */
    class ANH2 : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANH2 () {}
      ANH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANH2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global NZ atom type class.
     */
    class ANZ : public virtual AminoAcid, public virtual Nitrogen, public virtual SideChain
    { 
    public:
      ANZ () {}
      ANZ (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ANZ* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.8240.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.8240; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.1700.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.1700; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global O atom type class.
     */
    class AO : public virtual AminoAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AO () {}
      AO (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AO* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OD1 atom type class.
     */
    class AOD1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOD1 () {}
      AOD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OD2 atom type class.
     */
    class AOD2 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOD2 () {}
      AOD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OE1 atom type class.
     */
    class AOE1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOE1 () {}
      AOE1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOE1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OE2 atom type class.
     */
    class AOE2 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOE2 () {}
      AOE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.6612.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.6612; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2100.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2100; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OG atom type class.
     */
    class AOG : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOG () {}
      AOG (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOG* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.7210.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.7210; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2104.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2104; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OG1 atom type class.
     */
    class AOG1 : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOG1 () {}
      AOG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.7210.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.7210; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2104.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2104; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OH atom type class.
     */
    class AOH : public virtual AminoAcid, public virtual Oxygen, public virtual SideChain
    { 
    public:
      AOH () {}
      AOH (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOH* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.7210.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.7210; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2104.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2104; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global OXT atom type class.
     */
    class AOXT : public virtual AminoAcid, public virtual Oxygen, public virtual Backbone
    { 
    public:
      AOXT () {}
      AOXT (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AOXT* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.7210.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.7210; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2104.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2104; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global SD atom type class.
     */
    class ASD : public virtual AminoAcid, public virtual Sulfur, public virtual SideChain
    { 
    public:
      ASD () {}
      ASD (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ASD* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 2.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 2.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2500.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2500; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global SG atom type class.
     */
    class ASG : public virtual AminoAcid, public virtual Sulfur, public virtual SideChain
    { 
    public:
      ASG () {}
      ASG (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const ASG* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 2.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 2.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.2500.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.2500; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HD1 atom type class.
     */
    class A1HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HD1 () {}
      A1HD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HD2 atom type class.
     */
    class A1HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HD2 () {}
      A1HD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HE2 atom type class.
     */
    class A1HE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HE2 () {}
      A1HE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HG1 atom type class.
     */
    class A1HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HG1 () {}
      A1HG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HG2 atom type class.
     */
    class A1HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HG2 () {}
      A1HG2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HG2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HH1 atom type class.
     */
    class A1HH1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HH1 () {}
      A1HH1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HH1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 1HH2 atom type class.
     */
    class A1HH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HH2 () {}
      A1HH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A1HH2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HD1 atom type class.
     */
    class A2HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HD1 () {}
      A2HD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HD2 atom type class.
     */
    class A2HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HD2 () {}
      A2HD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HE2 atom type class.
     */
    class A2HE2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HE2 () {}
      A2HE2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HE2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HG1 atom type class.
     */
    class A2HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HG1 () {}
      A2HG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HG2 atom type class.
     */
    class A2HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HG2 () {}
      A2HG2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HG2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HH1 atom type class.
     */
    class A2HH1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HH1 () {}
      A2HH1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HH1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 2HH2 atom type class.
     */
    class A2HH2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HH2 () {}
      A2HH2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A2HH2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.6000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.6000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 3HD1 atom type class.
     */
    class A3HD1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HD1 () {}
      A3HD1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3HD1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 3HD2 atom type class.
     */
    class A3HD2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HD2 () {}
      A3HD2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3HD2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 3HG1 atom type class.
     */
    class A3HG1 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HG1 () {}
      A3HG1 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3HG1* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global 3HG2 atom type class.
     */
    class A3HG2 : public virtual AminoAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A3HG2 () {}
      A3HG2 (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const A3HG2* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 1.4870.
       */
      virtual float getVDWR (const ResidueType *r) const { return 1.4870; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0157.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0157; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const;


      
    };

    /**
     * Global magnesium atom type class.
     */
    class AMG : public virtual Magnesium
    { 
    public:
      AMG () {}
      AMG (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const AMG* > (t);
      }

      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return 0.0000.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0.0000; }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0.00000; }


      
    };

    /**
     * Global amino acid pseudo atom type class.
     */
    class APSAZ : public virtual AminoAcid, public virtual Pseudo, public virtual Backbone
    { 
    public:
      APSAZ () {}
      APSAZ (const string& ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType* t) const {
	return dynamic_cast< const APSAZ* > (t);
      }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getVDWR (const ResidueType *r) const
      { return Pseudo::getVDWR (r); }

      /**
       * Gets the Amber epsilon value for the atom.
       * @param res the residue that contains the atom.
       * @return the Pseudo atom value.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const
      { return Pseudo::getAmberEpsilon (r); }

      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param res the residue type.
       * @return the Pseudo atom Amber charge.
       */
      virtual float getAmberCharge (const ResidueType *r) const
      { return Pseudo::getAmberCharge (r); }


      
    };

    // New atom types
    //

    /**
     * Global 1HN6 atom type class.
     */
    class A1HN6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HN6 () {}
      A1HN6 (const string &ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType *t) const { return dynamic_cast< const A1HN6* > (t); }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber epsilon value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param r the residue type.
       * @return 0.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0; }
      
    };

    /**
     * Global 2HN6 atom type class.
     */
    class A2HN6 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A2HN6 () {}
      A2HN6 (const string &ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType *t) const { return dynamic_cast< const A2HN6* > (t); }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber epsilon value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param r the residue type.
       * @return 0.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0; }
      
    };

    /**
     * Global CM1 atom type class.
     */
    class ACM1 : public virtual NucleicAcid, public virtual Carbon, public virtual SideChain
    { 
    public:
      ACM1 () {}
      ACM1 (const string &ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType *t) const { return dynamic_cast< const ACM1* > (t); }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber epsilon value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param r the residue type.
       * @return 0.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0; }
      
    };

     /**
      * Global 2HM1 atom type class.
      */
     class A2HM1 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
     { 
     public:
       A2HM1 () {}
       A2HM1 (const string &ks) : AtomType (ks) {}
    
       virtual bool describe (const AtomType *t) const { return dynamic_cast< const A2HM1* > (t); }
    
       /**
        * Gets the Van Der Waals radius value for the atom.
        * @param r the residue that contains the atom.
        * @return 0.
        */
       virtual float getVDWR (const ResidueType *r) const { return 0; }
    
       /**
        * Gets the Amber epsilon value for the atom.
        * @param r the residue that contains the atom.
        * @return 0.
        */
       virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
    
       /**
        * Gets the Amber charge value for the atom in the given residue type.
        * @param r the residue type.
        * @return 0.
        */
       virtual float getAmberCharge (const ResidueType *r) const { return 0; }
    
     };

    /**
     * Global 1HM1 atom type class.
     */
    class A1HM1 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
    { 
    public:
      A1HM1 () {}
      A1HM1 (const string &ks) : AtomType (ks) {}
      
      virtual bool describe (const AtomType *t) const { return dynamic_cast< const A1HM1* > (t); }
      
      /**
       * Gets the Van Der Waals radius value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getVDWR (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber epsilon value for the atom.
       * @param r the residue that contains the atom.
       * @return 0.
       */
      virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
      
      /**
       * Gets the Amber charge value for the atom in the given residue type.
       * @param r the residue type.
       * @return 0.
       */
      virtual float getAmberCharge (const ResidueType *r) const { return 0; }
      
    };

     /**
      * Global 3HM1 atom type class.
      */
     class A3HM1 : public virtual NucleicAcid, public virtual Hydrogen, public virtual SideChain
     { 
     public:
       A3HM1 () {}
       A3HM1 (const string &ks) : AtomType (ks) {}
    
       virtual bool describe (const AtomType *t) const { return dynamic_cast< const A3HM1* > (t); }
    
       /**
        * Gets the Van Der Waals radius value for the atom.
        * @param r the residue that contains the atom.
        * @return 0.
        */
       virtual float getVDWR (const ResidueType *r) const { return 0; }
    
       /**
        * Gets the Amber epsilon value for the atom.
        * @param r the residue that contains the atom.
        * @return 0.
        */
       virtual float getAmberEpsilon (const ResidueType *r) const { return 0; }
    
       /**
        * Gets the Amber charge value for the atom in the given residue type.
        * @param r the residue type.
        * @return 0.
        */
       virtual float getAmberCharge (const ResidueType *r) const { return 0; }
    
     };

  };  
}

#endif
