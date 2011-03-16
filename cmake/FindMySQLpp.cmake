## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010,2011 Université de Montréal
##

find_path(MYSQLPP_INCLUDE_DIR mysql++/mysql++.h)
find_library(MYSQLPP_LIBRARIES NAMES mysqlpp)

if(MYSQLPP_INCLUDE_DIR AND MYSQLPP_LIBRARIES)
  set(MYSQLPP_FOUND TRUE)
endif()

if(MYSQLPP_FOUND)
  if (NOT MySQLpp_FIND_QUIETLY)
    message(STATUS "Found mysql++ includes:	${MYSQLPP_INCLUDE_DIR}/mysql++/mysql++.h")
    message(STATUS "Found mysql++ library: ${MYSQLPP_LIBRARIES}")
  endif ()
else()
  if (MySQLpp_FIND_REQUIRED)
    message(FATAL_ERROR "Could NOT find mysql++ development files")
  endif ()
endif()
