//                              -*- Mode: C++ -*- 
// CResidue.h
// Copyright © 2000-01 Laboratoire de Biologie Informatique et Théorique.
// Author           : Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : Thu Sep 28 16:59:32 2000
// Last Modified By : Martin Larose
// Last Modified On : Fri Feb  2 14:56:22 2001
// Update Count     : 11
// Status           : Ok.
// 


#ifndef _CResidue_h_
#define _CResidue_h_

#include <map.h>
#include <vector.h>

#include "CAtom.h"
#include "CResId.h"
#include "CTransfo.h"


class CResidue;
class t_Atom;
class t_Residue;
class oPdbstream;
class iBinstream;
class oBinstream;



/**
 * @short Residue implementation.
 *
 * The lazy residues contains an unsorted array of atoms (CAtoms).  The
 * atoms are positioned in a global referential space and are only placed in
 * local referential space when a residue iterator is dereferenced.  It is
 * necessary to manipulates residue iterator instead of atom pointers since
 * the atom address is unstable when it is placed.  Every methods that
 * modifies the contents of the atom array are functional, i.e. a new
 * residue is created, modified and returned.  This way existing iterators
 * over the residue are not dandling.
 *
 * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CResidue : public CResId
{
public:
  typedef vector< CAtom >::size_type size_type;
private:
  
  /**
   * The residue type.
   */
  t_Residue  *mType;

  /**
   * The name of the residue.
   */
  char* mResName;

  /**
   * The atom container in global referential.
   */
  vector< CAtom > mAtomRef;

  /**
   * The position container to mAtomRes.  If -1 is found then the atom has
   * not been transformed in local referential.
   */
  mutable vector< int > mAtomResPos;

  /**
   * The associative container between atom types and atom position in
   * mAtomRef, mAtomResPos.
   */
  map< t_Atom*, int > mAtomIndex;

  /**
   * The atom container in local referential.
   */
  mutable vector< CAtom > mAtomRes;

  /**
   * The tranfo for local referential.
   */
  CTransfo mTfo;

public:

  /**
   * The global counter over the number of residues.
   */
  static int count;

  /**
   * @short Iterator class over atoms in residues.
   *
   * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
   */
  class residue_iterator
  {
  public:
    typedef random_access_iterator_tag iterator_category;
    typedef CAtom value_type;
    typedef ptrdiff_t difference_type;
    typedef CAtom* pointer;
    typedef CAtom& reference;
    typedef size_t size_type;
  private:
    
    /**
     * The pointer over the residue.
     */
    CResidue *mRes;
    
    /**
     * The index of the atom global referencial container.
     */
    size_type mPos;
    
    /**
     * The unary function filter.
     */
    AtomSet *mSet;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the iterator.
     */
    residue_iterator ();
    
    /**
     * Initializes the iterator with a residue and position.
     * @param nRes the residue.
     * @param nPos the position over the atom global referential container.
     * @param nSet the atom set unary filter function.
     * @param nOption the atom set option unary filter function.
     */
    residue_iterator (CResidue *nRes, int nPos, AtomSet *nSet = 0);
    
    /**
     * Initializes the iterator with the right's contents.
     * @param right the iterator to copy.
     */
    residue_iterator (const residue_iterator &right);
    
    /**
     * Destructs the object.
     */
    ~residue_iterator () { delete mSet; }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the iterator with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    residue_iterator& operator= (const residue_iterator &right);
    
    /**
     * Advances and assigns the iterator of k positions.
     * @param k the number of positions to advance.
     * @return itself.
     */
    residue_iterator& operator+= (difference_type k);
    
    /**
     * Gets the atom pointed by the current mPos index.  Places the atom if
     * needed.
     * @return the atom pointer over local referential atom container.
     */
    pointer operator-> () const { return &(mRes->Place (mPos)); }
  
    /**
     * Dereferences the iterator.  Places the atom if needed.
     * @return the atom reference over local referential atom container.
     */
    reference operator* () const { return mRes->Place (mPos); }
  
    /**
     * Pre-advances the iterator to the next atom filtered by the unary
     * functions.
     * @return the iterator over the next atom.
     */
    residue_iterator& operator++ ();
    
    /**
     * Post-advances the iterator to the next atom filtered by the unary
     * functions.
     * @param ign ignored parameter.
     * @return the iterator over the current atom.
     */
    residue_iterator operator++ (int ign);
    
    /**
     * Adds the iterator to a distance type k.  The result may points to the
     * end of the residue.
     * @param k the distance type.
     * @return a new iterator pointing to itself + k.
     */
    residue_iterator operator+ (difference_type k) const;
    
    /**
     * Calculates the distance between 2 iterators.  Self and i must be
     * iterators from the same container.
     * @param i the iterator.
     * @return the difference type between 2 iterators.
     */
    difference_type operator- (const residue_iterator &i) const;
    
    /**
     * Tests whether the iterators are equal.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator== (const residue_iterator &right) const
    { return mPos == right.mPos; }
    
    /**
     * Tests whether the iterators are different.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator!= (const residue_iterator &right) const
    { return !(operator== (right)); }
    
    /**
     * Tests whether the current iterator is less than the right.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator< (const residue_iterator &right) const
    { return mPos < right.mPos; }
    
    // ACCESS ---------------------------------------------------------------
    
    /**
     * Casts the iterator to a residue.
     * @return the residue pointed by the iterator.
     */
    operator CResidue* () { return mRes; }
    
    // METHODS --------------------------------------------------------------
    
    // I/O  -----------------------------------------------------------------
  };
  
  /**
   * @short Const iterator class over atoms in residues.
   *
   * @author Sébastien Lemieux <lemieuxs@iro.umontreal.ca>
   */
  class const_residue_iterator
  {
  public:
    typedef random_access_iterator_tag iterator_category;
    typedef const CAtom value_type;
    typedef ptrdiff_t difference_type;
    typedef const CAtom* pointer;
    typedef const CAtom& reference;
    typedef size_t size_type;
  private:
    /**
     * The pointer over the residue.
     */
    const CResidue *mRes;
    
    /**
     * The index of the atom global referencial container.
     */
    size_type mPos;
    
    /**
     * The unary function filter.
     */
    const AtomSet *mSet;
    
  public:
    
    // LIFECYCLE ------------------------------------------------------------
    
    /**
     * Initializes the iterator.
     */
    const_residue_iterator ();
    
    /**
     * Initializes the iterator with a residue and position.
     * @param nRes the residue.
     * @param nPos the position over the atom global referential container.
     * @param nSet the atom set unary filter function.
     * @param nOption the atom set option unary filter function.
     */
    const_residue_iterator (const CResidue *nRes, int nPos,
			    const AtomSet *nSet = 0);
    
    /**
     * Initializes the const_iterator with the right's contents.
     * @param right the const_iterator to copy.
     */
    const_residue_iterator (const const_residue_iterator &right);
    
    /**
     * Destructs the object.
     */
    ~const_residue_iterator () { delete mSet; }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the const_iterator with the right's content.
     * @param right the object to copy.
     * @return itself.
     */
    const_residue_iterator& operator= (const const_residue_iterator &right);
    
    /**
     * Advances and assigns the const_iterator of k positions.
     * @param k the number of positions to advance.
     * @return itself.
     */
    const_residue_iterator& operator+= (difference_type k);
    
    /**
     * Gets the atom pointed by the current mPos index.  Places the atom if
     * needed.
     * @return the atom pointer over local referential atom container.
     */
    pointer operator-> () const { return &(mRes->Place (mPos)); }
    
    /**
     * Dereferences the iterator.  Places the atom if needed.
     * @return the atom reference over local referential atom container.
     */
    reference operator* () const { return mRes->Place (mPos); }
    
    /**
     * Pre-advances the iterator to the next atom filtered by the unary
     * functions.
     * @return the iterator over the next atom.
     */
    const_residue_iterator& operator++ ();
    
    /**
     * Post-advances the iterator to the next atom filtered by the unary
     * functions.
     * @param ign ignored parameter.
     * @return the iterator over the current atom.
     */
    const_residue_iterator operator++ (int ign);
    
    /**
     * Adds the const_iterator to a distance type k.  The result may points
     * to the end of the residue.
     * @param k the distance type.
     * @return a new iterator pointing to itself + k.
     */
    const_residue_iterator operator+ (difference_type k) const;
    
    /**
     * Calculates the distance between 2 const_iterators.  Self and i must
     * be const_iterators from the same container.
     * @param i the const_iterator.
     * @return the difference type between 2 const_iterators.
     */
    difference_type operator- (const const_residue_iterator &i) const;
    
    /**
     * Tests whether the iterators are equal.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator== (const const_residue_iterator &right) const
    { return mPos == right.mPos; }
    
    /**
     * Tests whether the iterators are different.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator!= (const const_residue_iterator &right) const
    { return !(operator== (right)); }
    
    /**
     * Tests whether the current iterator is less than the right.
     * @param right the right iterator.
     * @return the truth value.
     */
    bool operator< (const const_residue_iterator &right) const
    { return mPos < right.mPos; }
    
    // ACCESS ---------------------------------------------------------------
    
    /**
     * Casts the iterator to a residue.
     * @return the residue pointed by the iterator.
     */
    operator const CResidue* () const { return mRes; }
    
    // METHODS --------------------------------------------------------------
    
    // I/O  -----------------------------------------------------------------
  };
  
  friend residue_iterator;
  friend const_residue_iterator;
  typedef residue_iterator iterator;
  typedef const_residue_iterator const_iterator;

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the residue.  Increases the global count.
   */
  CResidue ()
    : CResId (), mType (0), mResName (0), mTfo ()
  {count++;} 

  /**
   * Initializes the residue with type, atom container and id.
   * @param type the residue type.
   * @param vec the atom container.
   * @param nId the residue id.
   */
  CResidue (t_Residue *type, const vector< CAtom > &vec, const CResId &nId);

  /**
   * Initializes the residue with the right's content.
   * @param right the object to copy.
   */
  CResidue (const CResidue &right);

  /**
   * Destructs the object.
   */
  ~CResidue ();

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the object with the right's content.
   * @param right the object to copy.
   * @return itself.
   */
  const CResidue& operator= (const CResidue &right);

  /**
   * Tests if the residues are equals.
   * @param right the right residue.
   * @return the truth value.
   */
  bool operator== (const CResidue &right) const;

  /**
   * Tests whether the residues are different.
   * @param right the right residue.
   * @return the truth value.
   */
  bool operator!= (const CResidue &right) const { return !operator== (right); }

  /**
   * Returns a reference to the atom associated with the type.  The returned
   * atom is not garanteed to stay valid.
   * @param type the atom type.
   * @return the reference to the atom in the local referential.
   */
  CAtom& operator[] (t_Atom *type) ;

  /**
   * Returns a const reference to the atom associated with the type.  The
   * returned atom is not garanteed to be valid.
   * @param type the atom type.
   * @return the reference to the atom in the local referential.
   */
  const CAtom& operator[] (t_Atom *type) const;

  // ACCESS ---------------------------------------------------------------

  /**
   * Casts the residue to a boolean.  Tests if the type is empty.
   * @return whether the type has been set.
   */
  operator bool () { return mType; }

  /**
   * Gets the size of the global referential atom container.
   * @return the size of the container.
   */
  size_type size () const { return mAtomRef.size (); }

  /**
   * Gets the iterator begin.
   * @return the iterator over the first element.
   */
  iterator begin (AtomSet *atomset = 0)
  { return iterator (this, 0, atomset); }

  /**
   * Gets the end iterator.
   * @return the iterator past the last element.
   */
  iterator end () { return iterator (this, size ()); }

  /**
   * Gets the begin const iterator.
   * @return the const_iterator over the first element.
   */
  const_iterator begin (AtomSet *atomset = 0) const
  { return const_iterator (this, 0, atomset); }

  /**
   * Gets the end const iterator.
   * @return the const_iterator past the last element.
   */
  const_iterator end () const { return const_iterator (this, size ()); }

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  iterator find (t_Atom *k);

  /**
   * Finds an element whose key is k.
   * @param k the atom type key.
   * @return the iterator to the element or end () if it is not found.
   */
  const_iterator find (t_Atom *k) const;

  /**
   * Gets the residue id.
   * @return the residue id.
   */
  const CResId& GetId () const { return *this; }

  /**
   * Sets the residue id.
   * @param resid the new residue id.
   */
  void SetResId (const CResId &resid) { CResId::operator= (resid); }

  /**
   * Gets the residue type.
   * @return the residue type.
   */
  t_Residue* GetType () const { return mType; }

  /**
   * Sets the residue type.
   * @param type the new residue type.
   */
  void SetType (t_Residue *type) { mType = type; }

 /**
   * Gets the transfo.
   * @return the transfo.
   */
  const CTransfo& GetTransfo () const { return mTfo; }

  /**
   * Sets the transfo.  Only the internal transfo is modified,
   * the atoms in local referential are erased.
   * @param tfo the new transfo.
   */
  void SetTransfo (const CTransfo &tfo);

  /**
   * Gets the residue name.
   * @return the residue name.
   */
  const char* GetResName () const;

  /**
   * Sets the residue name.
   * @param nName the new residue name.
   */
  void SetResName (const char* nName);

  // METHODS --------------------------------------------------------------

private:
  
  /**
   * Gets the atom at pos index if it is in local referential.  Transforms
   * it if it is not.
   * @param pos the index.
   * @return the atom in local referential.
   */
  CAtom& Place (int pos) const;

  /**
   * Gets the atom of type t in global referential.
   * @param t the atom type.
   * @return the atom or 0 if it is not found.
   */
  const CAtom* Ref (t_Atom *t) const;

  /**
   * Inserts an atom in the residue.  It crushes the existing atom if it
   * exists.  The index and the local referential containers are adjusted.
   * @param atom the atom to insert.
   */
  void Create (const CAtom &a);

  /**
   * Erases an atom from the residue, adjusting all containers and maps.
   * @param type the atom type to remove.
   */
  void erase (t_Atom *type);
  
  /**
   * Erases a range of atoms from the residue, adjusting all containers and
   * maps.
   * @param start the iterator of the first atom to erase.
   * @param finish the iterator of the last atom to erase.
   */
  template<class _InputIterator>
  void erase (const _InputIterator &start, const _InputIterator &finish)
  {
    vector< CAtom >::const_iterator cit;
    vector< CAtom >::size_type index;
    _InputIterator ciit;
    
    for (ciit = start; ciit != finish; ++ciit)
      {
	vector< CAtom >::iterator it = ::find (mAtomRef.begin (),
					       mAtomRef.end (), *ciit);
	
	if (it != mAtomRef.end ())
	  mAtomRef.erase (it);
      }
    mAtomIndex.clear ();
    mAtomResPos.clear ();
    for (cit = mAtomRef.begin (), index = 0;
	 cit != mAtomRef.end ();
	 ++cit, ++index)
      {
	mAtomIndex[cit->GetType ()] = index;
	mAtomResPos.push_back (-1);
      }
  }
  
  /**
   * Adds the hydrogens to the residue.
   * @return the new residue.
   */
  void AddHydrogens ();

  /**
   * Adds the lone pairs to the residue.
   */
  void AddLP ();

public:

  /**
   * Copies the atoms from the right residue.
   * @param right the residue to copy.
   */
  void AtomCopy (const CResidue &right);
  
  /**
   * Verifies wether all the obligatory atoms are in the residue and creates
   * a new residue where all atoms other than obligatory and optional are
   * removed.  If any test fails, the returned residue has no type.
   * @return the residue created.
   */
  CResidue Validate () const;

  /**
   * Creates a new residue where all the optional atoms are removed.
   * @return the residue created.
   */
  CResidue RemoveOptionals () const;

  /**
   * Creates a new residue where all the atoms are sorted.  The order is
   * based over atoms order @ref CAtom::operator<.
   * @return the new residue created.
   */
  CResidue sort () const;

  /**
   * Creates a new residue with the atoms specified in the variable argument
   * list.  The list must be terminated by a (char*) null pointer.
   * @param at the first atom type.
   * @return the new residue.
   */
  CResidue select (t_Atom *at ...) const;
  
  /**
   * Applies a tfo over each atoms.  Only the internal transfo is modified,
   * the atoms in local referential are erased.
   * @param theTfo the transfo to apply.
   * @return itself.
   */
  CResidue& Transform (const CTransfo &theTfo);

  /**
   * Aligns the residue.  Sets the transfo to the identity.
   */
  void Align ();

  // I/O  -----------------------------------------------------------------
};



/**
 * Outputs the residue to the stream.
 * @param os the output stream.
 * @param res the residue to display.
 * @return the used output stream.
 */
ostream& operator<< (ostream &os, const CResidue &res);



/**
 * Inputs a residue from an input binary stream.
 * @param ibs the input binary stream.
 * @param res the residue.
 * @return the used input binary stream.
 */
iBinstream& operator>> (iBinstream &ibs, CResidue &res);



/**
 * Outputs the residue to the binary stream.
 * @param obs the output binary stream.
 * @param res the residue.
 * @return the used output binary stream.
 */
oBinstream& operator<< (oBinstream &obs, const CResidue &res);



/**
 * Reads the residue from a pdb file.
 * @param ips the input pdb stream.
 * @param res the residue.
 * @return the used input pdb stream.
 */
iPdbstream& operator>> (iPdbstream &ips, CResidue &res);



/**
 * Writes the residue to a pdb format file.
 * @param ops the ouput pdb stream.
 * @param the residue to output.
 * @return the used output pdb stream.
 */
oPdbstream& operator<< (oPdbstream &ops, const CResidue &res);

#endif
