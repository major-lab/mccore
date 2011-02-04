## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010 Institut de recherche en immunologie et en cancérologie
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
