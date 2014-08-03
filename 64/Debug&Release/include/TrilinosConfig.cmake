##############################################################################
#
# CMake variable for use by Trilinos clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos build
## ---------------------------------------------------------------------------

SET(Trilinos_CXX_COMPILER "cl")

SET(Trilinos_C_COMPILER "cl")

SET(Trilinos_Fortran_COMPILER "")

## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos build
## ---------------------------------------------------------------------------

SET(Trilinos_CXX_COMPILER_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Trilinos_C_COMPILER_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Trilinos_Fortran_COMPILER_FLAGS "-fPIC ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Trilinos_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Trilinos_SHARED_LIB_RPATH_COMMAND "")
SET(Trilinos_BUILD_SHARED_LIBS "OFF")

SET(Trilinos_LINKER CMAKE_LINKER-NOTFOUND)
SET(Trilinos_AR )


## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## The project version number
SET(Trilinos_VERSION "10.6.2")

## The project include file directories.
SET(Trilinos_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## The project library directories.
SET(Trilinos_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## The project libraries.
SET(Trilinos_LIBRARIES "locathyra;locaepetra;loca;noxthyra;noxepetra;nox;ModeLaplace;anasaziepetra;anasazi;stratimikos;stratimikosbelos;stratimikosaztecoo;stratimikosamesos;stratimikosml;stratimikosifpack;belosepetra;belos;ml;komplex;ifpack;amesos;galeri;aztecoo;thyraepetraext;thyraepetra;thyra;epetraext;triutils;epetra;rtop;teuchos")

## The project tpl include paths
SET(Trilinos_TPL_INCLUDE_DIRS "")

## The project tpl library paths
SET(Trilinos_TPL_LIBRARY_DIRS "")

## The project tpl libraries
SET(Trilinos_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Trilinos_MPI_LIBRARIES "")
SET(Trilinos_MPI_LIBRARY_DIRS "")
SET(Trilinos_MPI_INCLUDE_DIRS "")
SET(Trilinos_MPI_EXEC "")
SET(Trilinos_MPI_EXEC_MAX_NUMPROCS "")
SET(Trilinos_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Trilinos_PACKAGE_LIST "NOX;Anasazi;Stratimikos;Belos;ML;Komplex;Ifpack;Amesos;Galeri;AztecOO;Thyra;EpetraExt;Triutils;Epetra;RTOp;Teuchos")

## The TPLs enabled for this project
SET(Trilinos_TPL_LIST "LAPACK;BLAS")

FILE(GLOB PACKAGE_CONFIG_FILES "d:/hpfem/hermes/dependencies/include/*Config.cmake")
FOREACH(FILE ${PACKAGE_CONFIG_FILES})
  IF(NOT ${FILE} MATCHES "TrilinosConfig.cmake")
    INCLUDE(${FILE})
  ENDIF()
ENDFOREACH()
