//                              -*- Mode: C++ -*- 
// Sequence.cc
// Copyright © 2003 Laboratoire de Biologie Informatique et Théorique
// Author           : Patrick Gendron
// Created On       : Fri Apr 25 10:12:06 2003


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <ctype.h>
#include <assert.h>

#include "Sequence.h"
#include "Fastastream.h"
#include "Binstream.h"
#include "Genbankstream.h"

namespace mccore {

int 
index_table (char type)
{
  switch (type) {
  case 'a':
  case 'A': return 0;
  case 'c':
  case 'C': return 1;
  case 'g':
  case 'G': return 2;
  case 'u':
  case 't':
  case 'T':
  case 'U': return 3;
  default: cerr << "Oups" << endl;
    exit (EXIT_FAILURE);
  }
  return -1;
}

char 
translation_table[4][4][4] = 
{ //A
  { //AA
    { 'K', //AAA 
      'N', //AAC 
      'K', //AAG 
      'N'  //AAU 
    },
    //AC
    { 'T', //ACA 
      'T', //ACC 
      'T', //ACG 
      'T'  //ACU 
    },
    //AG
    { 'R', //AGA 
      'S', //AGC 
      'R', //AGG 
      'S'  //AGU 
    },
    //AU
    { 'I', //AUA 
      'I', //AUC 
      'M', //AUG // START
      'I'  //AUU 
    }
  },
  //C
  { //CA
    { 'Q', //CAA 
      'H', //CAC 
      'Q', //CAG 
      'H'  //CAU 
    },
    //CC
    { 'P', //CCA 
      'P', //CCC 
      'P', //CCG 
      'P'  //CCU 
    },
    //CG
    { 'R', //CGA 
      'R', //CGC 
      'R', //CGG 
      'R'  //CGU 
    },
    //CU
    { 'L', //CUA 
      'L', //CUC 
      'L', //CUG 
      'L'  //CUU 
    }
  },
  //G
  { //GA
    { 'E', //GAA 
      'D', //GAC 
      'E', //GAG 
      'D'  //GAU 
    },
    //GC
    { 'A', //GCA 
      'A', //GCC 
      'A', //GCG 
      'A'  //GCU 
    },
    //GG
    { 'G', //GGA 
      'G', //GGC 
      'G', //GGG 
      'G'  //GGU 
    },
    //GU
    { 'V', //GUA 
      'V', //GUC 
      'V', //GUG 
      'V'  //GUU 
    }
  },
  //U
  { //UA
    { 'X', //UAA // STOP
      'Y', //UAC 
      'X', //UAG // STOP
      'Y'  //UAU 
    },
    //UC
    { 'S', //UCA 
      'S', //UCC 
      'S', //UCG 
      'S'  //UCU 
    },
    //UG
    { 'X', //UGA // STOP 
      'C', //UGC 
      'W', //UGG 
      'C'  //UGU 
    },
    //UU
    { 'L', //UUA 
      'F', //UUC 
      'L', //UUG 
      'F'  //UUU 
    }
  }
};


// LIFECYCLE ------------------------------------------------------------


Sequence::Sequence ()
  : vector< char > ()
{
  uniqueId = new char[1];
  uniqueId[0] = '\0';
  description = new char[1];
  description[0] = '\0';
}


Sequence::Sequence (const Sequence &other)
  : vector< char > (other), uniqueId (0), description (0)
{
  if (other.uniqueId)
    uniqueId = strdup (other.uniqueId);
  else {
      uniqueId = new char[1];
      uniqueId[0] = '\0';
  }
  if (other.description)
    description = strdup (other.description);
  else {
    description = new char[1];
    description[0] = '\0';
  }
}


Sequence::~Sequence ()
{
  if (uniqueId)
    delete[] uniqueId;

  if (description)
    delete[] description;
}

// OPERATORS ------------------------------------------------------------


Sequence& 
Sequence::operator= (const Sequence &other)
{
  if (this != &other) {
    vector< char >::operator= (other);
    
    if (uniqueId) { delete[] uniqueId; uniqueId = 0; }
    if (other.uniqueId)
      uniqueId = strdup (other.uniqueId);
    else {
      uniqueId = new char[1];
      uniqueId[0] = '\0';
    }
    
    if (description) { delete[] description; description = 0; }
    if (other.description)
      description = strdup (other.description); 
    else {
      description = new char[1];
      description[0] = '\0';
    }
  }

  return *this;
}

char 
Sequence::operator[] (unsigned int index) const
{
  assert (index < size ());
  return vector< char >::operator[] (index);
}


// CResId 
// Sequence::getResId (unsigned int index) const 
// {
//   assert (index<size ());
//   return CResId (index+1);
// }



// METHODS --------------------------------------------------------------


unsigned int 
Sequence::size () const
{
  return vector< char >::size ();
}


Sequence 
Sequence::translate (const Sequence::iterator &f, const Sequence::iterator &b)
{
  Sequence result;
  Sequence::iterator i;
  
  for (i=f; (i!=b && (i+1)!=b && (i+2)!=b && (i+3)!=b); i=i+3) {
    result.push_back (translation_table 
		      [index_table (*i)]
		      [index_table (*(i+1))]
		      [index_table (*(i+2))]);
  }
 
  return result;
}


Sequence 
Sequence::complement (const Sequence::iterator &f, const Sequence::iterator &b)
{
  Sequence result;
  Sequence::iterator i;
  
  for (i=f; i!=b; ++i) {
    if (*i == 'a' || *i == 'A')
      result.push_back ('T');
    else if (*i == 'c' || *i == 'C')
      result.push_back ('G');
    else if (*i == 'g' || *i == 'G')
      result.push_back ('C');
    else if (*i == 't' || *i == 'T')
      result.push_back ('A');
    else if (*i == 'u' || *i == 'U')
      result.push_back ('A');
  }
 
  return result;
}


// I/O  -----------------------------------------------------------------


iBinstream& 
Sequence::read (iBinstream &is)
{
  clear ();
  delete uniqueId;
  delete description;
  
  int size;
  char c;

  is >> &uniqueId;
  is >> &description;
  is >> size;
  for (int i=0; i<size; ++i) {
    is >> c;
    push_back (c);
  }

  return is;
}


oBinstream& 
Sequence::write (oBinstream &os) const
{
  os << uniqueId;
  os << description;
  os << size ();
  for (const_iterator i=begin (); i!=end (); ++i) {
    os << *i;
  }
  return os;
}

istream& 
Sequence::read (istream &is)
{
  clear ();

  char c;
  c = is.get ();
  while (!is.eof ()) {
    if (isgraph (c))
      push_back (c);
    c = is.get ();
  }
  return is;
}

ostream& 
Sequence::write (ostream &os) const
{
  const_iterator i;
  int j;

  os << "Unique Id   = " << uniqueId << endl;
  os << "Description = " << description << endl;

  for (i=begin (), j=0; i!=end (); ++i, ++j) {
    if (j!=0 && j%80 == 0) os << endl;
    os << *i;
  }
  return os;
}


iFastastream& 
Sequence::read (iFastastream &is)
{
  if (description) delete[] description;
  description = is.getDescription ();

  (vector< char >&)*this = is.getSequence ();

  return is;
}


oFastastream& 
Sequence::write (oFastastream &os) const
{
  if (description) os.putDescription (description);
  os.putSequence (*this);
  return os;
}


iGenbankstream& 
Sequence::read (iGenbankstream &is)
{
  if (description) delete[] description;
  description = is.getDescription ();

  (vector< char >&)*this = is.getSequence ();

  return is;
}


iBinstream& operator>> (iBinstream &ibs, Sequence &seq)
{
  return seq.read (ibs);
}


oBinstream& operator<< (oBinstream &obs, const Sequence &seq)
{
  return seq.write (obs);
}


istream& 
operator>> (istream &is, Sequence &seq)
{
  return seq.read (is);
}


ostream& 
operator<< (ostream &os, const Sequence &seq)
{
  return seq.write (os);
}


iFastastream& 
operator>> (iFastastream &is, Sequence &seq)
{
  return seq.read (is);
}


oFastastream& 
operator<< (oFastastream &os, const Sequence &seq)
{
  return seq.write (os);
}


iGenbankstream& 
operator>> (iGenbankstream &is, Sequence &seq)
{
  return seq.read (is);
}


}
