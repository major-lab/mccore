## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010,2011 Institut de recherche en immunologie et en cancérologie
##
## mccore is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## mccore is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with mccore  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.6)

# ajouter les FindXXX.cmake supplémentaire
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project (MCCORE)

# information du package
set (PACKAGE_NAME "mccore")
set (PACKAGE_DESCRIPTION  "mccore is a bioinformatics data structures and tools library for efficient analysis and manipulation of RNA, DNA and protein 3D structures")

# version
set (MCCORE_VERSION_MAJOR 2)
set (MCCORE_VERSION_MINOR 0)
set (MCCORE_VERSION_PATCH 0)
set (MCCORE_VERSION_STRING ${MCCORE_VERSION_MAJOR}.${MCCORE_VERSION_MINOR}.${MCCORE_VERSION_PATCH})

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

if(WITH-MYSQL)
  # ajoute MySQL
  find_package(MySQLpp)
  if(MYSQLPP_FOUND)
    message(STATUS "Using MySQL++: YES") 
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
set (CPACK_PACKAGE_CONTACT "Jonathan Roy <TO_BE_DECIDED@kekchose.com>")
set (CPACK_PACKAGE_FILE_NAME ${MCCORE_COMPLETE_PACKAGE_NAME})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # The OS X PackageMaker doesn't seem to like files with no extension
else()
  set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
  set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
endif()

# CPack spéficique à RPM
set (CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME}) # comportement par défaut(mais je préfère être explicite 
set (CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
set (CPACK_RPM_PACKAGE_DESCRIPTION ${PACKAGE_DESCRIPTION}) # TODO: donnez une version plus complète et pas seulement le sommaire
set (CPACK_RPM_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION})
set (CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})
set (CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
set (CPACK_RPM_PACKAGE_GROUP "Applications/Science")

# // TODO: je ne connais pas les versions "minimales" pour laquelle ça fonctionnerait alors je m'abstiens de forcer une contrainte pour l'instant
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