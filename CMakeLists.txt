## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010,2011 Université de Montréal
##

cmake_minimum_required (VERSION 2.6)

# ajouter les FindXXX.cmake supplémentaire
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project (MCCORE)

# information du package
set (PACKAGE_NAME "mccore")
set (PACKAGE_DESCRIPTION  "mccore is a bioinformatics data structures and tools library for efficient analysis and manipulation of RNA, DNA and protein 3D structures")

# version

#include(FindSubversion)
#if(Subversion_FOUND)
#  message(STATUS "Subversion found - Enabling version string with revision number")
#  Subversion_WC_INFO(${CMAKE_SOURCE_DIR} MCCORE)
#  set(MCCORE_SVN_REVISION ${MCCORE_WC_REVISION})
#else()
#  set (MCCORE_SVN_REVISION "")
#endif()


set (MCCORE_VERSION_MAJOR 2)
set (MCCORE_VERSION_MINOR 0)
set (MCCORE_VERSION_PATCH 0)
set (MCCORE_VERSION_STRING ${MCCORE_VERSION_MAJOR}.${MCCORE_VERSION_MINOR}.${MCCORE_VERSION_PATCH})

#if (MCCORE_SVN_REVISION)
#  set (MCCORE_VERSION_STRING ${MCCORE_VERSION_STRING}-r${MCCORE_SVN_REVISION})
#endif()

# nom complet avec version
set (MCCORE_COMPLETE_PACKAGE_NAME ${PACKAGE_NAME}-${MCCORE_VERSION_STRING})

############################################################
# Options de build                                         #
############################################################
option(STATIC_BUILD "Enable static build" OFF)
option(WITH-RNAML "Enable MySQL support" OFF)
option(WITH-MYSQL "Enable MySQL support" OFF)
option(HANDLE_GCC_VAR "Handle GCC environment variables" ON)
############################################################

############################################################
# Ajoute la gestion typique des variables d'environnement  #
############################################################ 

# note: Bug dans CMake, selon la doc les paths devraient être
# sépararés par des ":" et on doit plutôt les sépararés par des ";"
if (HANDLE_GCC_VAR)
  if (NOT $ENV{CPLUS_INCLUDE_PATH}  STREQUAL "")
    string (REPLACE ":" " " INCLUDES_CPP $ENV{CPLUS_INCLUDE_PATH})
    string (REPLACE "//" "/" INCLUDES_CPP ${INCLUDES_CPP})
    string(REGEX MATCHALL "[^ ]+" LIST_INCLUDES_CPP ${INCLUDES_CPP})
    set (CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${LIST_INCLUDES_CPP})
  endif ()

  if (NOT $ENV{LD_LIBRARY_PATH}  STREQUAL "")
    string (REPLACE ":" " " LIBRARIES $ENV{LD_LIBRARY_PATH})
    string (REPLACE "//" "/" LIBRARIES ${LIBRARIES})
    string(REGEX MATCHALL "[^ ]+" LIST_LIBRARIES ${LIBRARIES})
    set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${LIST_LIBRARIES})
  endif ()
endif()
#############################################################

# gestion du build static
if(STATIC_BUILD)
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
  set (BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set (CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
else()
  set (BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
endif()

# gestion du build 64 bits
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(LIB_SUFFIX "" CACHE INTERNAL "")
else()
  set(LIB_SUFFIX "64" CACHE INTERNAL "")
endif()

############################################################
# Définition utile plus loin                               #
############################################################

############################################################
# Dépendance  (fonctions, libs, etc)                       #
############################################################
include (CheckFunctionExists)
check_function_exists(strsep HAVE_STRSEP) 
check_function_exists(isfdtype HAVE_ISFDTYPE) 

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  set (EXT_LIBS ${EXT_LIBS} ${ZLIB_LIBRARIES})
endif()

if(WITH-MYSQL)
  # ajoute MySQL
  find_package(MySQLpp)
  if(MYSQLPP_FOUND)
    message(STATUS "Using MySQL++: YES") 
    include_directories(${MYSQLPP_INCLUDE_DIR})
    set (EXT_LIBS ${EXT_LIBS} ${MYSQLPP_LIBRARIES})
  else(MYSQLPP_FOUND)
    message(STATUS "Using MySQL++: NO")
  endif(MYSQLPP_FOUND)
endif()

############################################################

# convertis le fichier de configuration cmake en .h standard
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.cmake"
  "${PROJECT_BINARY_DIR}/config.h"
  )
  
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/config.h
                            PROPERTIES GENERATED TRUE
                            HEADER_FILE_ONLY TRUE)  

# ajoute le répertoire de build à la liste des "include_directories"
# pour que config.h puisse être trouvé
include_directories ("${PROJECT_BINARY_DIR}")

# ajoute le sous-répertoire de la librarie pour que le CMakeList.txt soit exécuter
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/lib")

# CPack 
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME ${PACKAGE_NAME})
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PACKAGE_DESCRIPTION})
set (CPACK_PACKAGE_VERSION ${MCCORE_VERSION_STRING})
set (CPACK_PACKAGE_VERSION_MAJOR ${MCCORE_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${MCCORE_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${MCCORE_VERSION_PATCH})
set (CPACK_PACKAGE_VENDOR "Laboratoire d'ingénierie des ARN")
set (CPACK_PACKAGE_CONTACT "Jonathan Roy <mctools@iric.ca>")
set (CPACK_PACKAGE_FILE_NAME ${MCCORE_COMPLETE_PACKAGE_NAME})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # The OS X PackageMaker doesn't seem to like files with no extension
else()
  set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
  #set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
endif()

# CPack spéficique à RPM
set (CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME}) 
set (CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
set (CPACK_RPM_PACKAGE_DESCRIPTION ${PACKAGE_DESCRIPTION}) 
set (CPACK_RPM_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION})
set (CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})
set (CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
set (CPACK_RPM_PACKAGE_GROUP "Applications/Science")
set (CPACK_RPM_PACKAGE_REQUIRES "") # "libc6 (>= 2.2.5), cmake (>= 2.6)"

# CPack spécifique à Debian (TODO au besoin)
#set (CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
#set (CPACK_DEBIAN_PACKAGE_DEPENDS "")
#set (CPACK_DEBIAN_PACKAGE_DESCRIPTION ${PACKAGE_DESCRIPTION)
#set (CPACK_DEBIAN_PACKAGE_SECTION "Applications/Science")

INCLUDE(CPack)

# TODO: ajouter des tests de base et possiblement l'exécution de tests unitaires

# enable dashboard scripting
#include (CTest)
