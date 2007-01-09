//                              -*- Mode: C++ -*- 
// PropertyTypeStore.h
// Copyright © 2003-07 Laboratoire de Biologie Informatique et Théorique
//                     Université de Montréal
// Author           : Patrick Gendron
// Created On       : Fri Apr  4 11:42:25 2003
// $Revision: 1.15 $
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


#ifndef _mccore_PropertyTypeStore_h_
#define _mccore_PropertyTypeStore_h_

#include <set>

#include "PropertyType.h"

using namespace std;



namespace mccore
{

  /**
   * @short Repository of property types.
   *
   *
   * @author Patrick Gendron (<a href="gendrop@iro.umontreal.ca">gendrop@iro.umontreal.ca</a>)
   * @version $Id: PropertyTypeStore.h,v 1.15 2007-01-09 01:07:10 larosem Exp $
   */
  class PropertyTypeStore
  {

    /**
     * The type repository
     */
    set< PropertyType*, PropertyType::less_deref > repository;
  
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    PropertyTypeStore ();
  
    /**
     * Destroys the object.  No deletion is done on the char* since it
     * is no known it is a string constant or an allocated string.
     * This is not too bad since types should live for as long as the
     * program runs.  (Note that we could use the C++ string class but
     * this increases compilation time by a factor 3).  NEWS: The get
     * function now uses the string found in the type as key to the
     * map and there are thus no more memory leaks.
     */
    ~PropertyTypeStore ();
  

    // METHODS --------------------------------------------------------------

    /**
     * Gets the property type represented by the string if one exists.
     * @param key string key representing the atom type.
     * @return the matching property type or a new one if none existed.
     */
    const PropertyType* get (const string& key);

  private:

    // TYPES -------------------------------------------------------------------

    class Null : public virtual PropertyType {
    public:      
      Null () {}
      Null (const string &ks) : PropertyType (ks) {}
      
      virtual bool isNull () const { return true; }
      virtual bool describe (const PropertyType* t) const {
	return dynamic_cast< const Null* > (t);
      }
    };
    
    /**
     * Public abstract class for unknown residues.
     */
    class Unknown : public virtual PropertyType {
    public:      
      Unknown () {}
      Unknown (const string &ks) : PropertyType (ks) {}
      
      virtual bool isUnknown () const { return true; }
      virtual bool describe (const PropertyType* t) const {
	return dynamic_cast< const Unknown* > (t);
      }
    };
    
    /**
     * Public class for theo.
     */
    class Theo : public virtual PropertyType {
    public:
      Theo () {}
      Theo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Theo* > (t); 
      }
    };
    
    /**
     * Public class for Hydrogen Bond.
     */
    class Hbond : public virtual PropertyType {
    public:
      Hbond () {}
      Hbond (const string &ks) : PropertyType (ks) { }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Hbond* > (t);
      }
    };

    
    /**
     * Public class for pairing.
     */
    class Pairing : public virtual Hbond {
    public:
      Pairing () {}
      Pairing (const string &ks) { key = ks; }
      
      virtual bool isPairing () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Pairing* > (t); 
      }
    };

    
    /**
     * Public class for backbone hydrogen bond.
     */
    class BHbond : public virtual Hbond {
    public:
      BHbond () {}
      BHbond (const string &ks) { key = ks; }
      
      virtual bool isBHbond () const { return true; }

      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const BHbond* > (t); 
      }
    };

    
    /**
     * Public class for cis.
     */
    class Cis : public virtual PropertyType {
    public:
      Cis () {}
      Cis (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Cis* > (t); 
      }
    };

    /**
     * Public class for trans.
     */
    class Trans : public virtual PropertyType {
    public:
      Trans () {}
      Trans (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Trans* > (t); 
      }
    };

    /**
     * Public class for straight.
     */
    class Straight : public virtual PropertyType {
    public:
      Straight () {}
      Straight (const string &ks) : PropertyType (ks) {}

      virtual bool isStraight () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Straight* > (t); 
      }
    };

    /**
     * Public class for reverse.
     */
    class Reverse : public virtual PropertyType {
    public:
      Reverse () {}
      Reverse (const string &ks) : PropertyType (ks) {}

      virtual bool isReverse () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Reverse* > (t); 
      }
    };

    /**
     * Public class for parallel.
     */
    class Parallel : public virtual Pairing, public virtual Straight {
    public:
      Parallel () {}
      Parallel (const string &ks) : PropertyType (ks) { }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Parallel* > (t); 
      }
    };

    /**
     * Public class for antiparallel.
     */
    class Antiparallel : public virtual Pairing, public virtual Reverse {
    public:
      Antiparallel () {}
      Antiparallel (const string &ks) : PropertyType (ks) {}
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Antiparallel* > (t); 
      }
    };

    /**
     * Public class for stacking.
     */
    class Stack : public virtual PropertyType {
    public:
      Stack () {}
      Stack (const string &ks) : PropertyType (ks) {}

      virtual bool isStack () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Stack* > (t); 
      }
    };


    /**
     * Public class for up stacking.
     */
    class Up : public virtual Stack {
    public:
      Up () {}
      Up (const string &ks) : PropertyType (ks) {}

      virtual bool isUp () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Up* > (t); 
      }
    };

    /**
     * Public class for down stacking.
     */
    class Down : public virtual Stack {
    public:
      Down () {}
      Down (const string &ks) : PropertyType (ks) {}

      virtual bool isDown () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Down* > (t); 
      }
    };

    /**
     * Public class for a straight upward stacking.
     */
    class Upward : public virtual Up, public virtual Straight {
    public:
      Upward () {}
      Upward (const string &ks) : PropertyType (ks) {}
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Upward* > (t); 
      }
    };

    /**
     * Public class for a straight downward stacking.
     */
    class Downward : public virtual Down, public virtual Straight {
    public:
      Downward () {}
      Downward (const string &ks) : PropertyType (ks) {}
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Downward* > (t); 
      }
    };

    /**
     * Public class for a reverse upward stacking.
     */
    class Inward : public virtual Up, public virtual Reverse {
    public:
      Inward () {}
      Inward (const string &ks) : PropertyType (ks) {}
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Inward* > (t); 
      }
    };

    /**
     * Public class for a reverse downward stacking.
     */
    class Outward : public virtual Down, public virtual Reverse {
    public:
      Outward () {}
      Outward (const string &ks) : PropertyType (ks) {}
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Outward* > (t); 
      }
    };
    
    /**
     * Public class for adjacent.
     */
    class Adjacent : public virtual PropertyType {
    public:
      Adjacent () {}
      Adjacent (const string &ks) : PropertyType (ks) {}

      virtual bool isAdjacent () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Adjacent* > (t); 
      }
    };

    /**
     * Public class for adjacent toward 5' direction.
     */
    class Adjacent5p : public virtual Adjacent {
    public:
      Adjacent5p () {}
      Adjacent5p (const string &ks) : PropertyType (ks) {}

      virtual bool isAdjacent5p () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Adjacent5p* > (t); 
      }
    };

    /**
     * Public class for adjacent toward 3' direction.
     */
    class Adjacent3p : public virtual Adjacent {
    public:
      Adjacent3p () {}
      Adjacent3p (const string &ks) : PropertyType (ks) {}

      virtual bool isAdjacent3p () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Adjacent3p* > (t); 
      }
    };

    /**
     * Public class for puckering modes.
     */
    class PuckeringMode : public virtual PropertyType {
    public:
      PuckeringMode () {}
      PuckeringMode (const string &ks) : PropertyType (ks) {}

      virtual bool isPuckeringMode () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const PuckeringMode* > (t); 
      }
    };

    
    /**
     * Public class for C1p_endo.
     */
    class C1p_endo : public virtual PuckeringMode {
    public:
      C1p_endo () {}
      C1p_endo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C1p_endo* > (t); 
      }
    };

    /**
     * Public class for C1p_exo.
     */
    class C1p_exo : public virtual PuckeringMode {
    public:
      C1p_exo () {}
      C1p_exo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C1p_exo* > (t); 
      }
    };

    /**
     * Public class for C2p_endo.
     */
    class C2p_endo : public virtual PuckeringMode {
    public:
      C2p_endo () {}
      C2p_endo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C2p_endo* > (t); 
      }
    };

    /**
     * Public class for C2p_exo.
     */
    class C2p_exo : public virtual PuckeringMode {
    public:
      C2p_exo () {}
      C2p_exo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C2p_exo* > (t); 
      }
    };

    /**
     * Public class for C3p_endo.
     */
    class C3p_endo : public virtual PuckeringMode {
    public:
      C3p_endo () {}
      C3p_endo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C3p_endo* > (t); 
      }
    };

    /**
     * Public class for C3p_exo.
     */
    class C3p_exo : public virtual PuckeringMode {
    public:
      C3p_exo () {}
      C3p_exo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C3p_exo* > (t); 
      }
    };

    /**
     * Public class for C4p_endo.
     */
    class C4p_endo : public virtual PuckeringMode {
    public:
      C4p_endo () {}
      C4p_endo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C4p_endo* > (t); 
      }
    };

    /**
     * Public class for C4p_exo.
     */
    class C4p_exo : public virtual PuckeringMode {
    public:
      C4p_exo () {}
      C4p_exo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const C4p_exo* > (t); 
      }
    };

    /**
     * Public class for O4p_endo.
     */
    class O4p_endo : public virtual PuckeringMode {
    public:
      O4p_endo () {}
      O4p_endo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const O4p_endo* > (t); 
      }
    };

    /**
     * Public class for O4p_exo.
     */
    class O4p_exo : public virtual PuckeringMode {
    public:
      O4p_exo () {}
      O4p_exo (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const O4p_exo* > (t); 
      }
    };

    /**
     * Public class for ribose relative orientation with base.
     */
    class RiboseOrientation : public virtual PropertyType {
    public:
      RiboseOrientation () {}
      RiboseOrientation (const string &ks) : PropertyType (ks) {}

      virtual bool isRiboseOrientation () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const RiboseOrientation* > (t); 
      }
    }; 
    
    /**
     * Public class for anti.
     */
    class Anti : public virtual RiboseOrientation {
    public:
      Anti () {}
      Anti (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Anti* > (t); 
      }
    };

    /**
     * Public class for syn.
     */
    class Syn : public virtual RiboseOrientation {
    public:
      Syn () {}
      Syn (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Syn* > (t); 
      }
    };

    /**
     * Public class for saenger.
     */
    class Saenger : public virtual Pairing {
    public:
      Saenger () {}
      Saenger (const string &ks) : PropertyType (ks) {}

      virtual bool isSaenger () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Saenger* > (t); 
      }
    };

    /**
     * Public class for wc.
     */
    class WC : public virtual Saenger {
    public:
      WC () {}
      WC (const string &ks) : PropertyType (ks) {}

      virtual bool isWC () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const WC* > (t); 
      }
    };

    /**
     * Public class for wobble.
     */
    class Wobble : public virtual Saenger {
    public:
      Wobble () {}
      Wobble (const string &ks) : PropertyType (ks) {}

      virtual bool isWobble () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Wobble* > (t); 
      }
    };

    /**
     * Public class for I.
     */
    class PI : public virtual Saenger {
    public:
      PI () {}
      PI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PI* > (t); 
      }
    };

    /**
     * Public class for II.
     */
    class PII : public virtual Saenger {
    public:
      PII () {}
      PII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PII* > (t); 
      }
    };

    /**
     * Public class for III.
     */
    class PIII : public virtual Saenger {
    public:
      PIII () {}
      PIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PIII* > (t); 
      }
    };

    /**
     * Public class for IV.
     */
    class PIV : public virtual Saenger {
    public:
      PIV () {}
      PIV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PIV* > (t); 
      }
    };

    /**
     * Public class for V.
     */
    class PV : public virtual Saenger {
    public:
      PV () {}
      PV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PV* > (t); 
      }
    };

    /**
     * Public class for VI.
     */
    class PVI : public virtual Saenger {
    public:
      PVI () {}
      PVI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PVI* > (t); 
      }
    };

    /**
     * Public class for VII.
     */
    class PVII : public virtual Saenger {
    public:
      PVII () {}
      PVII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PVII* > (t); 
      }
    };

    /**
     * Public class for VIII.
     */
    class PVIII : public virtual Saenger {
    public:
      PVIII () {}
      PVIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PVIII* > (t); 
      }
    };

    /**
     * Public class for IX.
     */
    class PIX : public virtual Saenger {
    public:
      PIX () {}
      PIX (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PIX* > (t); 
      }
    };

    /**
     * Public class for X.
     */
    class PX : public virtual Saenger {
    public:
      PX () {}
      PX (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PX* > (t); 
      }
    };

    /**
     * Public class for XI.
     */
    class PXI : public virtual Saenger {
    public:
      PXI () {}
      PXI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXI* > (t); 
      }
    };

    /**
     * Public class for XII.
     */
    class PXII : public virtual Saenger {
    public:
      PXII () {}
      PXII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXII* > (t); 
      }
    };

    /**
     * Public class for XIII.
     */
    class PXIII : public virtual Saenger {
    public:
      PXIII () {}
      PXIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXIII* > (t); 
      }
    };

    /**
     * Public class for XIV.
     */
    class PXIV : public virtual Saenger {
    public:
      PXIV () {}
      PXIV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXIV* > (t); 
      }
    };

    /**
     * Public class for XV.
     */
    class PXV : public virtual Saenger {
    public:
      PXV () {}
      PXV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXV* > (t); 
      }
    };

    /**
     * Public class for XVI.
     */
    class PXVI : public virtual Saenger {
    public:
      PXVI () {}
      PXVI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXVI* > (t); 
      }
    };

    /**
     * Public class for XVII.
     */
    class PXVII : public virtual Saenger {
    public:
      PXVII () {}
      PXVII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXVII* > (t); 
      }
    };

    /**
     * Public class for XVIII.
     */
    class PXVIII : public virtual Saenger {
    public:
      PXVIII () {}
      PXVIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXVIII* > (t); 
      }
    };

    /**
     * Public class for XIX.
     */
    class PXIX : public virtual WC {
    public:
      PXIX () {}
      PXIX (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXIX* > (t); 
      }
    };

    /**
     * Public class for XX.
     */
    class PXX : public virtual WC {
    public:
      PXX () {}
      PXX (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXX* > (t); 
      }
    };

    /**
     * Public class for XXI.
     */
    class PXXI : public virtual Saenger {
    public:
      PXXI () {}
      PXXI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXI* > (t); 
      }
    };

    /**
     * Public class for XXII.
     */
    class PXXII : public virtual Saenger {
    public:
      PXXII () {}
      PXXII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXII* > (t); 
      }
    };

    /**
     * Public class for XXIII.
     */
    class PXXIII : public virtual Saenger {
    public:
      PXXIII () {}
      PXXIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXIII* > (t); 
      }
    };

    /**
     * Public class for XXIV.
     */
    class PXXIV : public virtual Saenger {
    public:
      PXXIV () {}
      PXXIV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXIV* > (t); 
      }
    };

    /**
     * Public class for XXV.
     */
    class PXXV : public virtual Saenger {
    public:
      PXXV () {}
      PXXV (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXV* > (t); 
      }
    };

    /**
     * Public class for XXVI.
     */
    class PXXVI : public virtual Saenger {
    public:
      PXXVI () {}
      PXXVI (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXVI* > (t); 
      }
    };

    /**
     * Public class for XXVII.
     */
    class PXXVII : public virtual Saenger {
    public:
      PXXVII () {}
      PXXVII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXVII* > (t); 
      }
    };

    /**
     * Public class for XXVIII.
     */
    class PXXVIII : public virtual Wobble {
    public:
      PXXVIII () {}
      PXXVIII (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PXXVIII* > (t); 
      }
    };

    /**
     * Public class for OneHbond.
     */
    class OneHbond : public virtual Pairing {
    public:
      OneHbond () {}
      OneHbond (const string &ks) : PropertyType (ks) {}

      virtual bool isOneHbond () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const OneHbond* > (t); 
      }
    };

    /**
     * Public class for 29.
     */
    class P29 : public virtual OneHbond {
    public:
      P29 () {}
      P29 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P29* > (t); 
      }
    };

    /**
     * Public class for 30.
     */
    class P30 : public virtual OneHbond {
    public:
      P30 () {}
      P30 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P30* > (t); 
      }
    };

    /**
     * Public class for 31.
     */
    class P31 : public virtual OneHbond {
    public:
      P31 () {}
      P31 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P31* > (t); 
      }
    };

    /**
     * Public class for 32.
     */
    class P32 : public virtual OneHbond {
    public:
      P32 () {}
      P32 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P32* > (t); 
      }
    };

    /**
     * Public class for 33.
     */
    class P33 : public virtual OneHbond {
    public:
      P33 () {}
      P33 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P33* > (t); 
      }
    };

    /**
     * Public class for 34.
     */
    class P34 : public virtual OneHbond {
    public:
      P34 () {}
      P34 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P34* > (t); 
      }
    };

    /**
     * Public class for 35.
     */
    class P35 : public virtual OneHbond {
    public:
      P35 () {}
      P35 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P35* > (t); 
      }
    };

    /**
     * Public class for 36.
     */
    class P36 : public virtual OneHbond {
    public:
      P36 () {}
      P36 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P36* > (t); 
      }
    };

    /**
     * Public class for 37.
     */
    class P37 : public virtual OneHbond {
    public:
      P37 () {}
      P37 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P37* > (t); 
      }
    };

    /**
     * Public class for 38.
     */
    class P38 : public virtual OneHbond {
    public:
      P38 () {}
      P38 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P38* > (t); 
      }
    };

    /**
     * Public class for 39.
     */
    class P39 : public virtual OneHbond {
    public:
      P39 () {}
      P39 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P39* > (t); 
      }
    };

    /**
     * Public class for 40.
     */
    class P40 : public virtual OneHbond {
    public:
      P40 () {}
      P40 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P40* > (t); 
      }
    };

    /**
     * Public class for 41.
     */
    class P41 : public virtual OneHbond {
    public:
      P41 () {}
      P41 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P41* > (t); 
      }
    };

    /**
     * Public class for 42.
     */
    class P42 : public virtual OneHbond {
    public:
      P42 () {}
      P42 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P42* > (t); 
      }
    };

    /**
     * Public class for 43.
     */
    class P43 : public virtual OneHbond {
    public:
      P43 () {}
      P43 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P43* > (t); 
      }
    };

    /**
     * Public class for 44.
     */
    class P44 : public virtual OneHbond {
    public:
      P44 () {}
      P44 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P44* > (t); 
      }
    };

    /**
     * Public class for 45.
     */
    class P45 : public virtual OneHbond {
    public:
      P45 () {}
      P45 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P45* > (t); 
      }
    };

    /**
     * Public class for 46.
     */
    class P46 : public virtual OneHbond {
    public:
      P46 () {}
      P46 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P46* > (t); 
      }
    };

    /**
     * Public class for 47.
     */
    class P47 : public virtual OneHbond {
    public:
      P47 () {}
      P47 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P47* > (t); 
      }
    };

    /**
     * Public class for 48.
     */
    class P48 : public virtual OneHbond {
    public:
      P48 () {}
      P48 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P48* > (t); 
      }
    };

    /**
     * Public class for 49.
     */
    class P49 : public virtual OneHbond {
    public:
      P49 () {}
      P49 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P49* > (t); 
      }
    };

    /**
     * Public class for 50.
     */
    class P50 : public virtual OneHbond {
    public:
      P50 () {}
      P50 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P50* > (t); 
      }
    };

    /**
     * Public class for 51.
     */
    class P51 : public virtual OneHbond {
    public:
      P51 () {}
      P51 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P51* > (t); 
      }
    };

    /**
     * Public class for 52.
     */
    class P52 : public virtual OneHbond {
    public:
      P52 () {}
      P52 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P52* > (t); 
      }
    };

    /**
     * Public class for 53.
     */
    class P53 : public virtual OneHbond {
    public:
      P53 () {}
      P53 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P53* > (t); 
      }
    };

    /**
     * Public class for 54.
     */
    class P54 : public virtual OneHbond {
    public:
      P54 () {}
      P54 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P54* > (t); 
      }
    };

    /**
     * Public class for 55.
     */
    class P55 : public virtual OneHbond {
    public:
      P55 () {}
      P55 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P55* > (t); 
      }
    };

    /**
     * Public class for 56.
     */
    class P56 : public virtual OneHbond {
    public:
      P56 () {}
      P56 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P56* > (t); 
      }
    };

    /**
     * Public class for 57.
     */
    class P57 : public virtual OneHbond {
    public:
      P57 () {}
      P57 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P57* > (t); 
      }
    };

    /**
     * Public class for 58.
     */
    class P58 : public virtual OneHbond {
    public:
      P58 () {}
      P58 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P58* > (t); 
      }
    };

    /**
     * Public class for 59.
     */
    class P59 : public virtual OneHbond {
    public:
      P59 () {}
      P59 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P59* > (t); 
      }
    };

    /**
     * Public class for 60.
     */
    class P60 : public virtual OneHbond {
    public:
      P60 () {}
      P60 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P60* > (t); 
      }
    };

    /**
     * Public class for 61.
     */
    class P61 : public virtual OneHbond {
    public:
      P61 () {}
      P61 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P61* > (t); 
      }
    };

    /**
     * Public class for 62.
     */
    class P62 : public virtual OneHbond {
    public:
      P62 () {}
      P62 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P62* > (t); 
      }
    };

    /**
     * Public class for 63.
     */
    class P63 : public virtual OneHbond {
    public:
      P63 () {}
      P63 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P63* > (t); 
      }
    };

    /**
     * Public class for 64.
     */
    class P64 : public virtual OneHbond {
    public:
      P64 () {}
      P64 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P64* > (t); 
      }
    };

    /**
     * Public class for 65.
     */
    class P65 : public virtual OneHbond {
    public:
      P65 () {}
      P65 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P65* > (t); 
      }
    };

    /**
     * Public class for 66.
     */
    class P66 : public virtual OneHbond {
    public:
      P66 () {}
      P66 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P66* > (t); 
      }
    };

    /**
     * Public class for 67.
     */
    class P67 : public virtual OneHbond {
    public:
      P67 () {}
      P67 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P67* > (t); 
      }
    };

    /**
     * Public class for 68.
     */
    class P68 : public virtual OneHbond {
    public:
      P68 () {}
      P68 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P68* > (t); 
      }
    };

    /**
     * Public class for 69.
     */
    class P69 : public virtual OneHbond {
    public:
      P69 () {}
      P69 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P69* > (t); 
      }
    };

    /**
     * Public class for 70.
     */
    class P70 : public virtual OneHbond {
    public:
      P70 () {}
      P70 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P70* > (t); 
      }
    };

    /**
     * Public class for 71.
     */
    class P71 : public virtual OneHbond {
    public:
      P71 () {}
      P71 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P71* > (t); 
      }
    };

    /**
     * Public class for 72.
     */
    class P72 : public virtual OneHbond {
    public:
      P72 () {}
      P72 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P72* > (t); 
      }
    };

    /**
     * Public class for 73.
     */
    class P73 : public virtual OneHbond {
    public:
      P73 () {}
      P73 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P73* > (t); 
      }
    };

    /**
     * Public class for 74.
     */
    class P74 : public virtual OneHbond {
    public:
      P74 () {}
      P74 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P74* > (t); 
      }
    };

    /**
     * Public class for 75.
     */
    class P75 : public virtual OneHbond {
    public:
      P75 () {}
      P75 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P75* > (t); 
      }
    };

    /**
     * Public class for 76.
     */
    class P76 : public virtual OneHbond {
    public:
      P76 () {}
      P76 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P76* > (t); 
      }
    };

    /**
     * Public class for 77.
     */
    class P77 : public virtual OneHbond {
    public:
      P77 () {}
      P77 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P77* > (t); 
      }
    };

    /**
     * Public class for 78.
     */
    class P78 : public virtual OneHbond {
    public:
      P78 () {}
      P78 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P78* > (t); 
      }
    };

    /**
     * Public class for 79.
     */
    class P79 : public virtual OneHbond {
    public:
      P79 () {}
      P79 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P79* > (t); 
      }
    };

    /**
     * Public class for 80.
     */
    class P80 : public virtual OneHbond {
    public:
      P80 () {}
      P80 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P80* > (t); 
      }
    };

    /**
     * Public class for 81.
     */
    class P81 : public virtual OneHbond {
    public:
      P81 () {}
      P81 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P81* > (t); 
      }
    };

    /**
     * Public class for 82.
     */
    class P82 : public virtual OneHbond {
    public:
      P82 () {}
      P82 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P82* > (t); 
      }
    };

    /**
     * Public class for 83.
     */
    class P83 : public virtual OneHbond {
    public:
      P83 () {}
      P83 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P83* > (t); 
      }
    };

    /**
     * Public class for 84.
     */
    class P84 : public virtual OneHbond {
    public:
      P84 () {}
      P84 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P84* > (t); 
      }
    };

    /**
     * Public class for 85.
     */
    class P85 : public virtual OneHbond {
    public:
      P85 () {}
      P85 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P85* > (t); 
      }
    };

    /**
     * Public class for 86.
     */
    class P86 : public virtual OneHbond {
    public:
      P86 () {}
      P86 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P86* > (t); 
      }
    };

    /**
     * Public class for 87.
     */
    class P87 : public virtual OneHbond {
    public:
      P87 () {}
      P87 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P87* > (t); 
      }
    };

    /**
     * Public class for 88.
     */
    class P88 : public virtual OneHbond {
    public:
      P88 () {}
      P88 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P88* > (t); 
      }
    };

    /**
     * Public class for 89.
     */
    class P89 : public virtual OneHbond {
    public:
      P89 () {}
      P89 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P89* > (t); 
      }
    };

    /**
     * Public class for 90.
     */
    class P90 : public virtual OneHbond {
    public:
      P90 () {}
      P90 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P90* > (t); 
      }
    };

    /**
     * Public class for 91.
     */
    class P91 : public virtual OneHbond {
    public:
      P91 () {}
      P91 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P91* > (t); 
      }
    };

    /**
     * Public class for 92.
     */
    class P92 : public virtual OneHbond {
    public:
      P92 () {}
      P92 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P92* > (t); 
      }
    };

    /**
     * Public class for 93.
     */
    class P93 : public virtual OneHbond {
    public:
      P93 () {}
      P93 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P93* > (t); 
      }
    };

    /**
     * Public class for 94.
     */
    class P94 : public virtual OneHbond {
    public:
      P94 () {}
      P94 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P94* > (t); 
      }
    };

    /**
     * Public class for 95.
     */
    class P95 : public virtual OneHbond {
    public:
      P95 () {}
      P95 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P95* > (t); 
      }
    };

    /**
     * Public class for 96.
     */
    class P96 : public virtual OneHbond {
    public:
      P96 () {}
      P96 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P96* > (t); 
      }
    };

    /**
     * Public class for 97.
     */
    class P97 : public virtual OneHbond {
    public:
      P97 () {}
      P97 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P97* > (t); 
      }
    };

    /**
     * Public class for 98.
     */
    class P98 : public virtual OneHbond {
    public:
      P98 () {}
      P98 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P98* > (t); 
      }
    };

    /**
     * Public class for 99.
     */
    class P99 : public virtual OneHbond {
    public:
      P99 () {}
      P99 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P99* > (t); 
      }
    };

    /**
     * Public class for 100.
     */
    class P100 : public virtual OneHbond {
    public:
      P100 () {}
      P100 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P100* > (t); 
      }
    };

    /**
     * Public class for 101.
     */
    class P101 : public virtual OneHbond {
    public:
      P101 () {}
      P101 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P101* > (t); 
      }
    };

    /**
     * Public class for 102.
     */
    class P102 : public virtual OneHbond {
    public:
      P102 () {}
      P102 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P102* > (t); 
      }
    };

    /**
     * Public class for 103.
     */
    class P103 : public virtual OneHbond {
    public:
      P103 () {}
      P103 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P103* > (t); 
      }
    };

    /**
     * Public class for 104.
     */
    class P104 : public virtual OneHbond {
    public:
      P104 () {}
      P104 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P104* > (t); 
      }
    };

    /**
     * Public class for 105.
     */
    class P105 : public virtual OneHbond {
    public:
      P105 () {}
      P105 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P105* > (t); 
      }
    };

    /**
     * Public class for 106.
     */
    class P106 : public virtual OneHbond {
    public:
      P106 () {}
      P106 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P106* > (t); 
      }
    };

    /**
     * Public class for 108.
     */
    class P108 : public virtual OneHbond {
    public:
      P108 () {}
      P108 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P108* > (t); 
      }
    };

    /**
     * Public class for 109.
     */
    class P109 : public virtual OneHbond {
    public:
      P109 () {}
      P109 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P109* > (t); 
      }
    };

    /**
     * Public class for 110.
     */
    class P110 : public virtual OneHbond {
    public:
      P110 () {}
      P110 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P110* > (t); 
      }
    };

    /**
     * Public class for 111.
     */
    class P111 : public virtual OneHbond {
    public:
      P111 () {}
      P111 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P111* > (t); 
      }
    };

    /**
     * Public class for 112.
     */
    class P112 : public virtual OneHbond {
    public:
      P112 () {}
      P112 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P112* > (t); 
      }
    };

    /**
     * Public class for 113.
     */
    class P113 : public virtual OneHbond {
    public:
      P113 () {}
      P113 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P113* > (t); 
      }
    };

    /**
     * Public class for 114.
     */
    class P114 : public virtual OneHbond {
    public:
      P114 () {}
      P114 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P114* > (t); 
      }
    };

    /**
     * Public class for 115.
     */
    class P115 : public virtual OneHbond {
    public:
      P115 () {}
      P115 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P115* > (t); 
      }
    };

    /**
     * Public class for 116.
     */
    class P116 : public virtual OneHbond {
    public:
      P116 () {}
      P116 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P116* > (t); 
      }
    };

    /**
     * Public class for 117.
     */
    class P117 : public virtual OneHbond {
    public:
      P117 () {}
      P117 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P117* > (t); 
      }
    };

    /**
     * Public class for 118.
     */
    class P118 : public virtual OneHbond {
    public:
      P118 () {}
      P118 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P118* > (t); 
      }
    };

    /**
     * Public class for 119.
     */
    class P119 : public virtual OneHbond {
    public:
      P119 () {}
      P119 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P119* > (t); 
      }
    };

    /**
     * Public class for 120.
     */
    class P120 : public virtual OneHbond {
    public:
      P120 () {}
      P120 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P120* > (t); 
      }
    };

    /**
     * Public class for 121.
     */
    class P121 : public virtual OneHbond {
    public:
      P121 () {}
      P121 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P121* > (t); 
      }
    };

    /**
     * Public class for 122.
     */
    class P122 : public virtual OneHbond {
    public:
      P122 () {}
      P122 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P122* > (t); 
      }
    };

    /**
     * Public class for 123.
     */
    class P123 : public virtual OneHbond {
    public:
      P123 () {}
      P123 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P123* > (t); 
      }
    };

    /**
     * Public class for 124.
     */
    class P124 : public virtual OneHbond {
    public:
      P124 () {}
      P124 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P124* > (t); 
      }
    };

    /**
     * Public class for 125.
     */
    class P125 : public virtual OneHbond {
    public:
      P125 () {}
      P125 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P125* > (t); 
      }
    };

    /**
     * Public class for 126.
     */
    class P126 : public virtual OneHbond {
    public:
      P126 () {}
      P126 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P126* > (t); 
      }
    };

    /**
     * Public class for 127.
     */
    class P127 : public virtual OneHbond {
    public:
      P127 () {}
      P127 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P127* > (t); 
      }
    };

    /**
     * Public class for 128.
     */
    class P128 : public virtual OneHbond {
    public:
      P128 () {}
      P128 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P128* > (t); 
      }
    };

    /**
     * Public class for 129.
     */
    class P129 : public virtual OneHbond {
    public:
      P129 () {}
      P129 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P129* > (t); 
      }
    };

    /**
     * Public class for 130.
     */
    class P130 : public virtual OneHbond {
    public:
      P130 () {}
      P130 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P130* > (t); 
      }
    };

    /**
     * Public class for 131.
     */
    class P131 : public virtual OneHbond {
    public:
      P131 () {}
      P131 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P131* > (t); 
      }
    };

    /**
     * Public class for 132.
     */
    class P132 : public virtual OneHbond {
    public:
      P132 () {}
      P132 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P132* > (t); 
      }
    };

    /**
     * Public class for 133.
     */
    class P133 : public virtual OneHbond {
    public:
      P133 () {}
      P133 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P133* > (t); 
      }
    };

    /**
     * Public class for 134.
     */
    class P134 : public virtual OneHbond {
    public:
      P134 () {}
      P134 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P134* > (t); 
      }
    };

    /**
     * Public class for 135.
     */
    class P135 : public virtual OneHbond {
    public:
      P135 () {}
      P135 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P135* > (t); 
      }
    };

    /**
     * Public class for 136.
     */
    class P136 : public virtual OneHbond {
    public:
      P136 () {}
      P136 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P136* > (t); 
      }
    };

    /**
     * Public class for 137.
     */
    class P137 : public virtual OneHbond {
    public:
      P137 () {}
      P137 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const P137* > (t); 
      }
    };

    /**
     * Public class for Face.
     */
    class Face : public virtual PropertyType {
    public:
      Face () {}
      Face (const string &ks) : PropertyType (ks) {}

      virtual bool isFace () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const Face* > (t); 
      }
    };
    
    /**
     * Public class for W.
     */
    class PW : public virtual Face {
    public:
      PW () {}
      PW (const string &ks) : PropertyType (ks) {}

      virtual bool isW () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const PW* > (t); 
      }
    };

    /**
     * Public class for S.
     */
    class PS : public virtual Face {
    public:
      PS () {}
      PS (const string &ks) : PropertyType (ks) {}

      virtual bool isS () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const PS* > (t); 
      }
    };

    /**
     * Public class for H.
     */
    class PH : public virtual Face {
    public:
      PH () {}
      PH (const string &ks) : PropertyType (ks) {}

      virtual bool isH () const
      {
	return true;
      }
      
      virtual bool describe (const PropertyType *t) const
      {
	return dynamic_cast< const PH* > (t); 
      }
    };

    /**
     * Public class for Ws.
     */
    class PWs : public PW {
    public:
      PWs () {}
      PWs (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PWs* > (t); 
      }
    };

    /**
     * Public class for Ww.
     */
    class PWw : public PW {
    public:
      PWw () {}
      PWw (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PWw* > (t); 
      }
    };

    /**
     * Public class for Wh.
     */
    class PWh : public PW {
    public:
      PWh () {}
      PWh (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PWh* > (t); 
      }
    };

    /**
     * Public class for Sw.
     */
    class PSw : public PS {
    public:
      PSw () {}
      PSw (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PSw* > (t); 
      }
    };

    /**
     * Public class for Ss.
     */
    class PSs : public PS {
    public:
      PSs () {}
      PSs (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PSs* > (t); 
      }
    };

    /**
     * Public class for Hw.
     */
    class PHw : public PH {
    public:
      PHw () {}
      PHw (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PHw* > (t); 
      }
    };

    /**
     * Public class for Hh.
     */
    class PHh : public PH {
    public:
      PHh () {}
      PHh (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PHh* > (t); 
      }
    };

    /**
     * Public class for C8.
     */
    class PC8 : public PH {
    public:
      PC8 () {}
      PC8 (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PC8* > (t); 
      }
    };

    /**
     * Public class for Bs.
     */
    class PBs : public Face {
    public:
      PBs () {}
      PBs (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PBs* > (t); 
      }
    };

    /**
     * Public class for Bh.
     */
    class PBh : public Face {
    public:
      PBh () {}
      PBh (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PBh* > (t); 
      }
    };

    /**
     * Public class for Phosphate.
     */
    class PPhosphate : public Face {
    public:
      PPhosphate () {}
      PPhosphate (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PPhosphate* > (t); 
      }
    };

    /**
     * Public class for Ribose.
     */
    class PRibose : public Face {
    public:
      PRibose () {}
      PRibose (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const PRibose* > (t); 
      }
    };

    /**
     * Public class for Furanose.
     */
    class Furanose : public virtual PropertyType {
    public:
      Furanose () {}
      Furanose (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Furanose* > (t); 
      }
    };

    /**
     * Public class for Alpha anomer.
     */
    class Alpha : public Furanose {
    public:
      Alpha () {}
      Alpha (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Alpha* > (t); 
      }
    };

    /**
     * Public class for Beta anomer.
     */
    class Beta : public Furanose {
    public:
      Beta () {}
      Beta (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Beta* > (t); 
      }
    };

    /**
     * Public class for L enantiomer.
     */
    class L : public Furanose {
    public:
      L () {}
      L (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const L* > (t); 
      }
    };

    /**
     * Public class for D enantiomer.
     */
    class D : public Furanose {
    public:
      D () {}
      D (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const D* > (t); 
      }
    };

    /**
     * Public class for Lyxo aldose.
     */
    class Lyxofuranoside : public virtual Furanose {
    public:
      Lyxofuranoside () {}
      Lyxofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Lyxofuranoside* > (t);
      }
    };

    /**
     * Public class for Ribo aldose.
     */
    class Ribofuranoside : public virtual Furanose {
    public:
      Ribofuranoside () {}
      Ribofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Ribofuranoside* > (t);
      }
    };

    /**
     * Public class for Arabino aldose.
     */
    class Arabinofuranoside : public virtual Furanose {
    public:
      Arabinofuranoside () {}
      Arabinofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Arabinofuranoside* > (t);
      }
    };

    /**
     * Public class for Xylo aldose.
     */
    class Xylofuranoside : public virtual Furanose {
    public:
      Xylofuranoside () {}
      Xylofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Xylofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-L-Lyxofuranoside.
     */
    class Alpha_L_Lyxofuranoside : public virtual Alpha, public virtual L, public virtual Lyxofuranoside {
    public:
      Alpha_L_Lyxofuranoside () {}
      Alpha_L_Lyxofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_L_Lyxofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-L-Lyxo.
     */
    class Beta_L_Lyxofuranoside : public virtual Beta, public virtual L, public virtual Lyxofuranoside {
    public:
      Beta_L_Lyxofuranoside () {}
      Beta_L_Lyxofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_L_Lyxofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-D-Lyxo.
     */
    class Alpha_D_Lyxofuranoside : public virtual Alpha, public virtual D, public virtual Lyxofuranoside {
    public:
      Alpha_D_Lyxofuranoside () {}
      Alpha_D_Lyxofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_D_Lyxofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-D-Lyxo.
     */
    class Beta_D_Lyxofuranoside : public virtual Beta, public virtual D, public virtual Lyxofuranoside {
    public:
      Beta_D_Lyxofuranoside () {}
      Beta_D_Lyxofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_D_Lyxofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-L-Ribo.
     */
    class Alpha_L_Ribofuranoside : public virtual Alpha, public virtual L, public virtual Ribofuranoside {
    public:
      Alpha_L_Ribofuranoside () {}
      Alpha_L_Ribofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_L_Ribofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-L-Ribo.
     */
    class Beta_L_Ribofuranoside : public virtual Beta, public virtual L, public virtual Ribofuranoside {
    public:
      Beta_L_Ribofuranoside () {}
      Beta_L_Ribofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_L_Ribofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-D-Ribo.
     */
    class Alpha_D_Ribofuranoside : public virtual Alpha, public virtual D, public virtual Ribofuranoside {
    public:
      Alpha_D_Ribofuranoside () {}
      Alpha_D_Ribofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_D_Ribofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-D-Ribo.
     */
    class Beta_D_Ribofuranoside : public virtual Beta, public virtual D, public virtual Ribofuranoside {
    public:
      Beta_D_Ribofuranoside () {}
      Beta_D_Ribofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_D_Ribofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-L-Arabino.
     */
    class Alpha_L_Arabinofuranoside : public virtual Alpha, public virtual L, public virtual Arabinofuranoside {
    public:
      Alpha_L_Arabinofuranoside () {}
      Alpha_L_Arabinofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_L_Arabinofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-L-Arabino.
     */
    class Beta_L_Arabinofuranoside : public virtual Beta, public virtual L, public virtual Arabinofuranoside {
    public:
      Beta_L_Arabinofuranoside () {}
      Beta_L_Arabinofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_L_Arabinofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-D-Arabino.
     */
    class Alpha_D_Arabinofuranoside : public virtual Alpha, public virtual D, public virtual Arabinofuranoside {
    public:
      Alpha_D_Arabinofuranoside () {}
      Alpha_D_Arabinofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_D_Arabinofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-D-Arabino.
     */
    class Beta_D_Arabinofuranoside : public virtual Beta, public virtual D, public virtual Arabinofuranoside {
    public:
      Beta_D_Arabinofuranoside () {}
      Beta_D_Arabinofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_D_Arabinofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-L-Xylo.
     */
    class Alpha_L_Xylofuranoside : public virtual Alpha, public virtual L, public virtual Xylofuranoside {
    public:
      Alpha_L_Xylofuranoside () {}
      Alpha_L_Xylofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_L_Xylofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-L-Xylo.
     */
    class Beta_L_Xylofuranoside : public virtual Beta, public virtual L, public virtual Xylofuranoside {
    public:
      Beta_L_Xylofuranoside () {}
      Beta_L_Xylofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_L_Xylofuranoside* > (t);
      }
    };

    /**
     * Public class for Alpha-D-Xylo.
     */
    class Alpha_D_Xylofuranoside : public virtual Alpha, public virtual D, public virtual Xylofuranoside {
    public:
      Alpha_D_Xylofuranoside () {}
      Alpha_D_Xylofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Alpha_D_Xylofuranoside* > (t);
      }
    };

    /**
     * Public class for Beta-D-Xylo.
     */
    class Beta_D_Xylofuranoside : public virtual Beta, public virtual D, public virtual Xylofuranoside {
    public:
      Beta_D_Xylofuranoside () {}
      Beta_D_Xylofuranoside (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
        return dynamic_cast< const Beta_D_Xylofuranoside* > (t);
      }
    };

    /**
     * Public class for type_A.
     */
    class Type_A : public virtual PropertyType {
    public:
      Type_A () {}
      Type_A (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Type_A* > (t); 
      }
    };

    /**
     * Public class for type_B.
     */
    class Type_B : public virtual PropertyType {
    public:
      Type_B () {}
      Type_B (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Type_B* > (t); 
      }
    };
    
    /**
     * Public class for helix.
     */
    class Helix : public virtual Stack {
    public:
      Helix () {}
      Helix (const string &ks) : PropertyType (ks) {}
      virtual bool describe (const PropertyType *t) const {
	return dynamic_cast< const Helix* > (t); 
      }
    };
    
  };

}

#endif
