## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010,2011 Université de Montréal
##

cmake_minimum_required (VERSION 2.6)

# ajoute le répertoire de build à la liste des "include_directories"
# pour que config.h puisse être trouvé
#include_directories ("${PROJECT_BINARY_DIR}")

# liste de tous les fichiers source
FILE(GLOB MCCORE_SOURCES_CC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  AbstractModel.cc 
  Atom.cc 
  AtomFactoryMethod.cc
  AtomSet.cc 
  AtomType.cc  
  AtomTypeStore.cc  
  Binstream.cc  
  Exception.cc  
  ExtendedResidue.cc  
  Fastastream.cc  
  Genbankstream.cc  
  GraphModel.cc  
  HBond.cc  
  HomogeneousTransfo.cc  
  Messagestream.cc  
  Model.cc  
  ModelFactoryMethod.cc  
  Molecule.cc  
  PairingPattern.cc  
  PdbFileHeader.cc  
  Pdbstream.cc  
  PropertyType.cc  
  PropertyTypeStore.cc  
  Relation.cc  
  ResId.cc  
  ResIdSet.cc  
  Residue.cc  
  ResidueFactoryMethod.cc  
  ResidueTopology.cc  
  ResidueType.cc  
  ResidueTypeStore.cc  
  Rmsd.cc  
  ServerSocket.cc  
  Sequence.cc  
  TypeRepresentationTables.cc  
  Vector3D.cc  
  Version.cc  
  sockstream.cc  
  zstream.cc)

# support RNAML
if(WITH-RNAML)
  set(MCCORE_SOURCES_CC ${MCCORE_SOURCES_CC} RnamlReader.cc  RnamlWriter.cc)
endif()

#support MySQL
if(WITH-MYSQL)
  set(MCCORE_SOURCES_CC ${MCCORE_SOURCES_CC} SqlReader.cc SqlExtrac.cc)
endif()

# ajoute la librarie
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library (mccore ${MCCORE_SOURCES_CC})
set_target_properties(mccore PROPERTIES VERSION ${MCCORE_VERSION_STRING})
target_link_libraries(mccore ${EXT_LIBS})

# ajoute le target d'installation
install (TARGETS mccore DESTINATION lib${LIB_SUFFIX})
install(DIRECTORY ./ DESTINATION include/${MCCORE_COMPLETE_PACKAGE_NAME} FILES_MATCHING PATTERN "*.h" PATTERN ".svn" EXCLUDE)

# wrap dans un install(CODE) pour que la commande soit exécuter à l'installation
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/include/${MCCORE_COMPLETE_PACKAGE_NAME} ${CMAKE_INSTALL_PREFIX}/include/${PACKAGE_NAME})")
                                                           
 
