//                              -*- Mode: C++ -*- 
// ResidueTypeStore.h
// Copyright © 2003, 2004 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.11 $
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


#ifndef _ResidueTypeStore_h_
#define _ResidueTypeStore_h_

#include <iostream>
#include <map>
#include <set>

#include <string>

#include "ResidueType.h"

using namespace std;

namespace mccore {

  /**
   * Repository of residue types.
   *
   * @author Patrick Gendron (<a href="mailto:gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: ResidueTypeStore.h,v 1.11 2004-10-04 22:16:05 larosem Exp $
   */
  class ResidueTypeStore
  {
    /**
     * @short less comparator for strings.
     */
    struct less_string
    {
      /**
       * Tests whether the first string is lexicographically less than the
       * second one.
       * @param s1 the first string.
       * @param s2 the second string.
       * @return the result of the test.
       */
      bool operator() (const char* s1, const char* s2) const
      { return strcmp (s1, s2) < 0; }
    };

    /**
     * Container for string to type associations.
     */
    map< const char*, ResidueType*, less_string > stringType;

    map< const char*, ResidueType*, less_string > invalidType;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    ResidueTypeStore ();

    /**
     * Destroys the object.  No deletion is done on the char* since it
     * is no known it is a string constant or an allocated string.
     * This is not too bad since types should live for as long as the
     * program runs.  (Note that we could use the C++ string class but
     * this increases compilation time by a factor 3).  NEWS: The get
     * function now uses the string found in the type as key to the
     * map and there are thus no more memory leaks.
     */
    ~ResidueTypeStore ();
    
    // METHODS --------------------------------------------------------------

    /**
     * Gets the residue type represented by the string if one exists.
     * @param key string key representing the atom type.
     * @return the matching residue type or a new one if none existed.
     */
    const ResidueType* get (const char* key);

    /**
     * Gets the invalidated residue type represented by the string if one exists.
     * @param key string key representing the invalidated residue type.
     * @return the matching invalidated residue type or a new one if none existed.
     */
    const ResidueType* getInvalid (const char* key);

  private:
    
    // TYPES -------------------------------------------------------------------

    /**
     * Public abstract class for nucleic acid residues.
     */
    class NucleicAcid : public virtual ResidueType {
    public:      
      NucleicAcid () {}
      NucleicAcid (const char* t, const char* lt) : ResidueType (t, lt) {}
      
      virtual bool isNucleicAcid () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const NucleicAcid* > (t);
      }
    };
    
    /**
     * Public abstract class for amino acid residues.
     */
    class AminoAcid : public virtual ResidueType {
    public:      
      AminoAcid () {}
      AminoAcid (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isAminoAcid () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const AminoAcid* > (t);
      }
    };
    
    /**
     *  Public abstract class for ribonucleic acid residues.
     */
    class RNA : public virtual ResidueType
    {
    public:
      RNA () { }
      RNA (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isRNA () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RNA* > (t); }
    };

    /**
     * Public abstract class for deoxyribonucleic acid residues.
     */
    class DNA : public virtual ResidueType
    {
    public:      
      DNA () {}
      DNA (const char* t, const char* lt) : ResidueType (t, lt) {}
      
      virtual bool isDNA () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DNA* > (t); }
    };

    /**
     *  Public abstract class for phosphate residue.
     */
    class Phosphate : public virtual ResidueType
    {
    public:
      Phosphate () { }
      Phosphate (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isPhosphate () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Phosphate* > (t); }
    };    

    /**
     *  Public abstract class for ribose residue.
     */
    class Ribose : public virtual ResidueType
    {
    public:
      Ribose () { }
      Ribose (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isRibose () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Ribose* > (t); }
    };

    /**
     *  Public abstract class for ribose residue with 5' phosphate' atoms.
     */
    class Ribose5 : public virtual Ribose
    {
    public:
      Ribose5 () { }
      Ribose5 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isRibose5 () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Ribose5* > (t); }
    };

    /**
     *  Public abstract class for ribose residue with 3' phosphate' atoms.
     */
    class Ribose3 : public virtual Ribose
    {
    public:
      Ribose3 () { }
      Ribose3 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isRibose3 () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Ribose3* > (t); }
    };

    /**
     *  Public abstract class for ribose residue with both 5' and 3' phosphates' atoms.
     */
    class Ribose53 : public virtual Ribose
    {
    public:
      Ribose53 () { }
      Ribose53 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isRibose53 () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Ribose53* > (t); }
    };


    /**
     *  Public abstract class for Amber residue representation.
     */
    class Amber : public virtual ResidueType
    {
    public:
      Amber () { }
      Amber (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isAmber () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const Amber* > (t); }
    };

    /**
     *  Public abstract class for DNA phosphate residue.
     */
    class DPhosphate : public virtual Phosphate, public virtual DNA
    {
    public:
      DPhosphate () { }
      DPhosphate (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DPhosphate* > (t); }
    };

    /**
     *  Public abstract class for RNA phosphate residue.
     */
    class RPhosphate : public virtual Phosphate, public virtual RNA
    {
    public:
      RPhosphate () { }
      RPhosphate (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RPhosphate* > (t); }
    };

    /**
     *  Public abstract class for DNA ribose residue.
     */
    class DRibose : public virtual Ribose, public virtual DNA
    {
    public:
      DRibose () { }
      DRibose (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DRibose* > (t); }
    };

    /**
     *  Public abstract class for DNA ribose residue with 5' phosphate' atoms.
     */
    class DRibose5 : public virtual Ribose5, public virtual DRibose
    {
    public:
      DRibose5 () { }
      DRibose5 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DRibose5* > (t); }
    };

    /**
     *  Public abstract class for DNA ribose residue with 3' phosphate' atoms.
     */
    class DRibose3 : public virtual Ribose3, public virtual DRibose
    {
    public:
      DRibose3 () { }
      DRibose3 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DRibose3* > (t); }
    };

    /**
     *  Public abstract class for DNA ribose residue with both 5' and 3' phosphates' atoms.
     */
    class DRibose53 : public virtual Ribose53, public virtual DRibose
    {
    public:
      DRibose53 () { }
      DRibose53 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DRibose53* > (t); }
    };

    /**
     *  Public abstract class for RNA ribose residue.
     */
    class RRibose : public virtual Ribose, public virtual RNA
    {
    public:
      RRibose () { }
      RRibose (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RRibose* > (t); }
    };
    
    /**
     *  Public abstract class for RNA ribose residue with 5' phosphate' atoms.
     */
    class RRibose5 : public virtual Ribose5, public virtual RRibose
    {
    public:
      RRibose5 () { }
      RRibose5 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RRibose5* > (t); }
    };

    /**
     *  Public abstract class for RNA ribose residue with 3' phosphate' atoms.
     */
    class RRibose3 : public virtual Ribose3, public virtual RRibose
    {
    public:
      RRibose3 () { }
      RRibose3 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RRibose3* > (t); }
    };

    /**
     *  Public abstract class for RNA ribose residue with both 5' and 3' phosphates' atoms.
     */
    class RRibose53 : public virtual Ribose53, public virtual RRibose
    {
    public:
      RRibose53 () { }
      RRibose53 (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RRibose53* > (t); }
    };
    
    /**
     *  Public abstract class for N residue (any).
     */
    class N : public virtual NucleicAcid
    {
    public:
      N () { }
      N (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isN () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const N* > (t); }
    };
    
    /**
     * Public abstract class for B residues (C || G || U || S || Y || K)
     */
    class B : public virtual N {
    public:      
      B () {}
      B (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const B* > (t);
      }
    };

    /**
     * Public abstract class for D residues (A || G || U || R || W || K)
     */
    class D : public virtual N {
    public:      
      D () {}
      D (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const D* > (t);
      }    
    };

    /**
     * Public abstract class for H residues (A || C || U || M || W || Y)
     */
    class H : public virtual N {
    public:      
      H () {}
      H (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const H* > (t);
      }    
    };

    /**
     * Public abstract class for V residues (A || C || G || M || R || S)
     */
    class V : public virtual N {
    public:      
      V () {}
      V (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const V* > (t);
      }
    };

    /**
     * Public abstract class for purine residues. (R = A || G)
     */
    class Purine : public virtual D, public virtual V {
    public:      
      Purine () {}
      Purine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isPurine () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const Purine* > (t);
      }
    };

    /**
     * Public abstract class for pyrimidine residues. (Y = C || U)
     */
    class Pyrimidine : public virtual B, public virtual H {
    public:      
      Pyrimidine () {}
      Pyrimidine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isPyrimidine () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const Pyrimidine* > (t);
      }
    };
    
    /**
     * Public abstract class for W residues. (A || U)
     */
    class W : public virtual D, public virtual H {
    public:      
      W () {}
      W (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const W* > (t);
      }
    };
    
    /**
     * Public abstract class for S residues. (C || G)
     */
    class S : public virtual B, public virtual V {
    public:      
      S () {}
      S (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const S* > (t);
      }      
   };

    /**
     * Public abstract class for M residues. (A || C)
     */
    class M : public virtual H, public virtual V {
    public:      
      M () {}
      M (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const M* > (t);
      }
    };
    
    /**
     * Public abstract class for K residues. (G || U)
     */
    class K : public virtual B, public virtual D {
    public:      
      K () {}
      K (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const K* > (t);
      }
    };

    /**
     * Public abstract class for A residues.
     */
    class A : public virtual Purine, public virtual W, public virtual M {
    public:      
      A () {}
      A (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isA () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const A* > (t);
      }
    };

    /**
     * Public abstract class for C residues.
     */
    class C : public virtual Pyrimidine, public virtual S, public virtual M {
    public:      
      C () {}
      C (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isC () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const C* > (t);
      }
    };

    /**
     * Public abstract class for G residues.
     */
    class G : public virtual Purine, public virtual S, public virtual K {
    public:      
      G () {}
      G (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isG () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const G* > (t);
      }
    };

    /**
     * Public abstract class for U residues.
     */
    class U : public virtual Pyrimidine, public virtual W, public virtual K {
    public:      
      U () {}
      U (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isU () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const U* > (t);
      }
    };

    /**
     * Public abstract class for T residues.
     */
    class T : public virtual Pyrimidine, public virtual W, public virtual K {
    public:      
      T () {}
      T (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isT () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const T* > (t);
      }
    };
    
    
    // -------------------------------------------------------------------------

    /**
     *  Public abstract class for RN residue (any RNA).
     */
    class RN : public virtual N, public virtual RNA
    {
    public:
      RN () { }
      RN (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const RN* > (t); }
    };
    
    /**
     * Public RB residue type class.
     */
    class RB : public virtual B, public virtual RN {
    public:
      RB () {}
      RB (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RB* > (t); 
      }
    };

    /**
     * Public RD residue type class.
     */
    class RD : public virtual D, public virtual RN {
    public:
      RD () {}
      RD (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RD* > (t); 
      }
    };

    /**
     * Public RH residue type class.
     */
    class RH : public virtual H, public virtual RN {
    public:
      RH () {}
      RH (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RH* > (t); 
      }
    };

    /**
     * Public RV residue type class.
     */
    class RV : public virtual V, public virtual RN {
    public:
      RV () {}
      RV (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RV* > (t); 
      }
    };

    /**
     * Public RNA Purine residue type class.
     */
    class RPurine : public virtual Purine, public virtual RD, public virtual RV {
    public:
      RPurine () {}
      RPurine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RPurine* > (t); 
      }
    };
    
    /**
     * Public RPyrimidine residue type class.
     */
    class RPyrimidine : public virtual Pyrimidine, public virtual RB, public virtual RH {
    public:
      RPyrimidine () {}
      RPyrimidine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RPyrimidine* > (t); 
      }
    };

    /**
     * Public RW residue type class.
     */
    class RW : public virtual W, public virtual RD, public virtual RH {
    public:
      RW () {}
      RW (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RW* > (t); 
      }
    };

    /**
     * Public RS residue type class.
     */
    class RS : public virtual S, public virtual RB, public virtual RV {
    public:
      RS () {}
      RS (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RS* > (t); 
      }
    };

    /**
     * Public RM residue type class.
     */
    class RM : public virtual M, public virtual RH, public virtual RV {
    public:
      RM () {}
      RM (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RM* > (t); 
      }
    };

    /**
     * Public RK residue type class.
     */
    class RK : public virtual K, public virtual RB, public virtual RD {
    public:
      RK () {}
      RK (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RK* > (t); 
      }
    };

    /**
     * Public A RNA residue type class.
     */
    class RA : public virtual A, public virtual RW, public virtual RM, public virtual RPurine {
    public:
      RA () {}
      RA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RA* > (t); 
      }
    };

    /**
     * Public Amber RA5 RNA residue type class.
     */
    class RRA5 : public virtual RA, public virtual Amber
    {
    public:
      RRA5 () {}
      RRA5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRA5* > (t); 
      }
    };

    /**
     * Public Amber RA3 RNA residue type class.
     */
    class RRA3 : public virtual RA, public virtual Amber
    {
    public:
      RRA3 () {}
      RRA3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRA3* > (t); 
      }
    };

    /**
     * Public C RNA residue type class.
     */
    class RC : public virtual C, public virtual RS, public virtual RM, public virtual RPyrimidine {
    public:
      RC () {}
      RC (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RC* > (t); 
      }
    };

    /**
     * Public Amber RC5 RNA residue type class.
     */
    class RRC5 : public virtual RC, public virtual Amber
    {
    public:
      RRC5 () {}
      RRC5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRC5* > (t); 
      }
    };

    /**
     * Public Amber RC3 RNA residue type class.
     */
    class RRC3 : public virtual RC, public virtual Amber
    {
    public:
      RRC3 () {}
      RRC3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRC3* > (t); 
      }
    };

    /**
     * Public G RNA residue type class.
     */
    class RG : public virtual G, public virtual RS, public virtual RK, public virtual RPurine {
    public:
      RG () {}
      RG (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RG* > (t); 
      }
    };

    /**
     * Public Amber RG5 RNA residue type class.
     */
    class RRG5 : public virtual RG, public virtual Amber
    {
    public:
      RRG5 () {}
      RRG5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRG5* > (t); 
      }
    };

    /**
     * Public Amber RG3 RNA residue type class.
     */
    class RRG3 : public virtual RG, public virtual Amber
    {
    public:
      RRG3 () {}
      RRG3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRG3* > (t); 
      }
    };

    /**
     * Public U RNA residue type class.
     */
    class RU : public virtual U, public virtual RW, public virtual RK, public virtual RPyrimidine  {
    public:
      RU () {}
      RU (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RU* > (t); 
      }
    };

    /**
     * Public Amber RU5 RNA residue type class.
     */
    class RRU5 : public virtual RU, public virtual Amber
    {
    public:
      RRU5 () {}
      RRU5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRU5* > (t); 
      }
    };

    /**
     * Public Amber RU3 RNA residue type class.
     */
    class RRU3 : public virtual RU, public virtual Amber
    {
    public:
      RRU3 () {}
      RRU3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RRU3* > (t); 
      }
    };

    /**
     *  Public abstract class for DN residue (any DNA).
     */
    class DN : public virtual N, public virtual DNA
    {
    public:
      DN () { }
      DN (const char* t, const char* lt) : ResidueType (t, lt) { }

      virtual bool isDN () const { return true; }
      virtual bool describe (const ResidueType* t) const
      { return dynamic_cast< const DN* > (t); }
    };
    
    /**
     * Public DB residue type class.
     */
    class DB : public virtual B, public virtual DN {
    public:
      DB () {}
      DB (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DB* > (t); 
      }
    };

    /**
     * Public DD residue type class.
     */
    class DD : public virtual D, public virtual DN {
    public:
      DD () {}
      DD (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DD* > (t); 
      }
    };

    /**
     * Public DH residue type class.
     */
    class DH : public virtual H, public virtual DN {
    public:
      DH () {}
      DH (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DH* > (t); 
      }
    };

    /**
     * Public DV residue type class.
     */
    class DV : public virtual V, public virtual DN {
    public:
      DV () {}
      DV (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DV* > (t); 
      }
    };


    /**
     * Public DNA Purine residue type class.
     */
    class DPurine : public virtual Purine, public virtual DD, public virtual DV {
    public:
      DPurine () {}
      DPurine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DPurine* > (t); 
      }
    };
    
    /**
     * Public DNA Pyrimidine residue type class.
     */
    class DPyrimidine : public virtual Pyrimidine, public virtual DB, public virtual DH {
    public:
      DPyrimidine () {}
      DPyrimidine (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DPyrimidine* > (t); 
      }
    };

    /**
     * Public DW residue type class.
     */
    class DW : public virtual W, public virtual DD, public virtual DH {
    public:
      DW () {}
      DW (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DW* > (t); 
      }
    };

    /**
     * Public DS residue type class.
     */
    class DS : public virtual S, public virtual DB, public virtual DV {
    public:
      DS () {}
      DS (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DS* > (t); 
      }
    };

    /**
     * Public DM residue type class.
     */
    class DM : public virtual M, public virtual DH, public virtual DV {
    public:
      DM () {}
      DM (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DM* > (t); 
      }
    };

    /**
     * Public DK residue type class.
     */
    class DK : public virtual K, public virtual DB, public virtual DD {
    public:
      DK () {}
      DK (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DK* > (t); 
      }
    };

    /**
     * Public A DNA residue type class.
     */
    class DA : public virtual A, public virtual DW, public virtual DM, public virtual DPurine {
    public:
      DA () {}
      DA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DA* > (t); 
      }
    };

    /**
     * Public Amber RU5 DNA residue type class.
     */
    class DDA5 : public virtual DA, public virtual Amber
    {
    public:
      DDA5 () {}
      DDA5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDA5* > (t); 
      }
    };

    /**
     * Public Amber RU3 DNA residue type class.
     */
    class DDA3 : public virtual DA, public virtual Amber
    {
    public:
      DDA3 () {}
      DDA3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDA3* > (t); 
      }
    };

    /**
     * Public C DNA residue type class.
     */
    class DC : public virtual C, public virtual DS, public virtual DM, public virtual DPyrimidine {
    public:
      DC () {}
      DC (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DC* > (t); 
      }
    };

    /**
     * Public Amber RU5 DNA residue type class.
     */
    class DDC5 : public virtual DC, public virtual Amber
    {
    public:
      DDC5 () {}
      DDC5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDC5* > (t); 
      }
    };

    /**
     * Public Amber RU3 DNA residue type class.
     */
    class DDC3 : public virtual DC, public virtual Amber
    {
    public:
      DDC3 () {}
      DDC3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDC3* > (t); 
      }
    };

    /**
     * Public G DNA residue type class.
     */
    class DG : public virtual G, public virtual DS, public virtual DK, public virtual DPurine {
    public:
      DG () {}
      DG (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DG* > (t); 
      }
    };

    /**
     * Public Amber RU5 DNA residue type class.
     */
    class DDG5 : public virtual DG, public virtual Amber
    {
    public:
      DDG5 () {}
      DDG5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDG5* > (t); 
      }
    };

    /**
     * Public Amber RU3 DNA residue type class.
     */
    class DDG3 : public virtual DG, public virtual Amber
    {
    public:
      DDG3 () {}
      DDG3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDG3* > (t); 
      }
    };

    /**
     * Public T DNA residue type class.
     */
    class DT : public virtual T, public virtual DW, public virtual DK, public virtual DPyrimidine {
    public:
      DT () {}
      DT (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DT* > (t); 
      }
    };

    /**
     * Public Amber RU5 DNA residue type class.
     */
    class DDT5 : public virtual DT, public virtual Amber
    {
    public:
      DDT5 () {}
      DDT5 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDT5* > (t); 
      }
    };

    /**
     * Public Amber RU3 DNA residue type class.
     */
    class DDT3 : public virtual DT, public virtual Amber
    {
    public:
      DDT3 () {}
      DDT3 (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DDT3* > (t); 
      }
    };

    /**
     * Public ALA residue type class.
     */
    class ALA : public virtual AminoAcid {
    public:
      ALA () {}
      ALA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const ALA* > (t); 
      }
    };

    /**
     * Public ARG residue type class.
     */
    class ARG : public virtual AminoAcid {
    public:
      ARG () {}
      ARG (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const ARG* > (t); 
      }
    };

    /**
     * Public ASN residue type class.
     */
    class ASN : public virtual AminoAcid {
    public:
      ASN () {}
      ASN (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const ASN* > (t); 
      }
    };

    /**
     * Public ASP residue type class.
     */
    class ASP : public virtual AminoAcid {
    public:
      ASP () {}
      ASP (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const ASP* > (t); 
      }
    };

    /**
     * Public CYS residue type class.
     */
    class CYS : public virtual AminoAcid {
    public:
      CYS () {}
      CYS (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const CYS* > (t); 
      }
    };

    /**
     * Public GLN residue type class.
     */
    class GLN : public virtual AminoAcid {
    public:
      GLN () {}
      GLN (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const GLN* > (t); 
      }
    };

    /**
     * Public GLU residue type class.
     */
    class GLU : public virtual AminoAcid {
    public:
      GLU () {}
      GLU (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const GLU* > (t); 
      }
    };

    /**
     * Public GLY residue type class.
     */
    class GLY : public virtual AminoAcid {
    public:
      GLY () {}
      GLY (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const GLY* > (t); 
      }
    };

    /**
     * Public HIS residue type class.
     */
    class HIS : public virtual AminoAcid {
    public:
      HIS () {}
      HIS (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const HIS* > (t); 
      }
    };

    /**
     * Public ILE residue type class.
     */
    class ILE : public virtual AminoAcid {
    public:
      ILE () {}
      ILE (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const ILE* > (t); 
      }
    };

    /**
     * Public LEU residue type class.
     */
    class LEU : public virtual AminoAcid {
    public:
      LEU () {}
      LEU (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const LEU* > (t); 
      }
    };

    /**
     * Public LYS residue type class.
     */
    class LYS : public virtual AminoAcid {
    public:
      LYS () {}
      LYS (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const LYS* > (t); 
      }
    };

    /**
     * Public MET residue type class.
     */
    class MET : public virtual AminoAcid {
    public:
      MET () {}
      MET (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const MET* > (t); 
      }
    };

    /**
     * Public PHE residue type class.
     */
    class PHE : public virtual AminoAcid {
    public:
      PHE () {}
      PHE (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const PHE* > (t); 
      }
    };

    /**
     * Public PRO residue type class.
     */
    class PRO : public virtual AminoAcid {
    public:
      PRO () {}
      PRO (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const PRO* > (t); 
      }
    };

    /**
     * Public SER residue type class.
     */
    class SER : public virtual AminoAcid {
    public:
      SER () {}
      SER (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const SER* > (t); 
      }
    };

    /**
     * Public THR residue type class.
     */
    class THR : public virtual AminoAcid {
    public:
      THR () {}
      THR (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const THR* > (t); 
      }
    };

    /**
     * Public TRP residue type class.
     */
    class TRP : public virtual AminoAcid {
    public:
      TRP () {}
      TRP (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const TRP* > (t); 
      }
    };

    /**
     * Public TYR residue type class.
     */
    class TYR : public virtual AminoAcid {
    public:
      TYR () {}
      TYR (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const TYR* > (t); 
      }
    };

    /**
     * Public VAL residue type class.
     */
    class VAL : public virtual AminoAcid {
    public:
      VAL () {}
      VAL (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const VAL* > (t); 
      }
    };

  };

}

#endif
