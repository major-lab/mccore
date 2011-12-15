## This file is part of mccore.
##
## mccore is a bioinformatics data structures and tools library for efficient 
## analysis and manipulation of RNA, DNA and protein 3D structures
## Copyright (C) 2008,2009,2010,2011 Université de Montréal
##

include(FindSubversion)
Subversion_WC_INFO(${SOURCE_DIR} MCCORE)
#message(STATUS ${MCCORE_WC_INFO})
file(WRITE svnversion.h.cmake "#define SVNVERSION ${MCCORE_WC_REVISION}\n")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
      svnversion.h.cmake svnversion.h)
