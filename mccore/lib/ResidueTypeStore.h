//                              -*- Mode: C++ -*- 
// ResidueTypeStore.h
// Copyright � 2003 Laboratoire de Biologie Informatique et Th�orique
// Author           : Patrick Gendron
// Created On       : Wed Mar 12 10:40:10 2003
// $Revision: 1.2 $
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
   * @version $Id: ResidueTypeStore.h,v 1.2 2003-05-15 13:35:53 thibaup Exp $
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
     * @return the matching residue type or a new one if none existed.
     */
    ResidueType* get (const char* s);

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
     * Public abstract class for B residues (C || G || U || S || Y || K)
     */
    class B : public virtual NucleicAcid {
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
    class D : public virtual NucleicAcid {
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
    class H : public virtual NucleicAcid {
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
    class V : public virtual NucleicAcid {
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
    
    /**
     * Public abstract class for RNA residues.
     */
    class RNA : public virtual NucleicAcid {
    public:      
      RNA () {}
      RNA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isRNA () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RNA* > (t);
      }
    };
    
    /**
     * Public abstract class for DNA residues.
     */
    class DNA : public virtual NucleicAcid {
    public:      
      DNA () {}
      DNA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isDNA () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DNA* > (t);
      }
    };

    /**
     * Public abstract class for Phosphate residues.
     */
    class Phosphate : public virtual NucleicAcid {
    public:      
      Phosphate () {}
      Phosphate (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool isPhosphate () const { return true; }
      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const Phosphate* > (t);
      }
    };
    
    
    // -------------------------------------------------------------------------

    /**
     * Public RB residue type class.
     */
    class RB : public virtual B, public virtual RNA {
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
    class RD : public virtual D, public virtual RNA {
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
    class RH : public virtual H, public virtual RNA {
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
    class RV : public virtual V, public virtual RNA {
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
    class RPurine : public virtual Purine, public virtual RNA, public virtual RD, public virtual RV {
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
    class RPyrimidine : public virtual Pyrimidine, public virtual RNA, public virtual RB, public virtual RH {
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
    class RW : public virtual W, public virtual RNA, public virtual RD, public virtual RH {
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
    class RS : public virtual S, public virtual RNA, public virtual RB, public virtual RV {
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
    class RM : public virtual M, public virtual RNA, public virtual RH, public virtual RV {
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
    class RK : public virtual K, public virtual RNA, public virtual RB, public virtual RD {
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
    class RA : public virtual A, public virtual RNA, public virtual RW, public virtual RM, public virtual RPurine {
    public:
      RA () {}
      RA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RA* > (t); 
      }
    };

    /**
     * Public C RNA residue type class.
     */
    class RC : public virtual C, public virtual RNA, public virtual RS, public virtual RM, public virtual RPyrimidine {
    public:
      RC () {}
      RC (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RC* > (t); 
      }
    };

    /**
     * Public G RNA residue type class.
     */
    class RG : public virtual G, public virtual RNA, public virtual RS, public virtual RK, public virtual RPurine {
    public:
      RG () {}
      RG (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RG* > (t); 
      }
    };

    /**
     * Public U RNA residue type class.
     */
    class RU : public virtual U, public virtual RNA, public virtual RW, public virtual RK, public virtual RPyrimidine  {
    public:
      RU () {}
      RU (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const RU* > (t); 
      }
    };

    /**
     * Public DB residue type class.
     */
    class DB : public virtual B, public virtual DNA {
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
    class DD : public virtual D, public virtual DNA {
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
    class DH : public virtual H, public virtual DNA {
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
    class DV : public virtual V, public virtual DNA {
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
    class DPurine : public virtual Purine, public virtual DNA, public virtual DD, public virtual DV {
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
    class DPyrimidine : public virtual Pyrimidine, public virtual DNA, public virtual DB, public virtual DH {
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
    class DW : public virtual W, public virtual DNA, public virtual DD, public virtual DH {
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
    class DS : public virtual S, public virtual DNA, public virtual DB, public virtual DV {
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
    class DM : public virtual M, public virtual DNA, public virtual DH, public virtual DV {
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
    class DK : public virtual K, public virtual DNA, public virtual DB, public virtual DD {
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
    class DA : public virtual A, public virtual DNA, public virtual DW, public virtual DM, public virtual DPurine {
    public:
      DA () {}
      DA (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DA* > (t); 
      }
    };

    /**
     * Public C DNA residue type class.
     */
    class DC : public virtual C, public virtual DNA, public virtual DS, public virtual DM, public virtual DPyrimidine {
    public:
      DC () {}
      DC (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DC* > (t); 
      }
    };

    /**
     * Public G DNA residue type class.
     */
    class DG : public virtual G, public virtual DNA, public virtual DS, public virtual DK, public virtual DPurine {
    public:
      DG () {}
      DG (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DG* > (t); 
      }
    };

    /**
     * Public T DNA residue type class.
     */
    class DT : public virtual T, public virtual DNA, public virtual DW, public virtual DK, public virtual DPyrimidine {
    public:
      DT () {}
      DT (const char* t, const char* lt) : ResidueType (t, lt) {}

      virtual bool describe (const ResidueType* t) const {
	return dynamic_cast< const DT* > (t); 
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
