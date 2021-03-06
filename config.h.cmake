/* This file is part of mccore.
 *
 * mccore is a bioinformatics data structures and tools library for efficient
 * analysis and manipulation of RNA, DNA and protein 3D structures
 * Copyright (C) 2008,2009,2010,2011 Institut de recherche en immunologie et en cancérologie
 *
 * mccore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mccore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mccore.  If not, see <http://www.gnu.org/licenses/>.
 */   


#ifndef CONFIG_H
#define CONFIG_H

// package information
#define PACKAGE_NAME "${PACKAGE_NAME}"
#define PACKAGE_VERSION_STRING "${MCCORE_VERSION_STRING}"

// checks for functions
#cmakedefine HAVE_STRSEP 1
#cmakedefine HAVE_ISFDTYPE 1

// needed for actual version handling of Version.cc
#define VERSION_CPU "${CMAKE_SYSTEM_PROCESSOR}"
#define VERSION_OS "${CMAKE_SYSTEM_NAME}"

#endif /*CONFIG_H*/