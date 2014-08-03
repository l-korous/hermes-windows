##############################################################################
#
# CMake variable for use by Trilinos/Komplex clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Komplex build
## ---------------------------------------------------------------------------

SET(Komplex_CXX_COMPILER "cl")

SET(Komplex_C_COMPILER "cl")

SET(Komplex_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Komplex build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Komplex_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Komplex_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Komplex_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Komplex_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Komplex_SHARED_LIB_RPATH_COMMAND "")
SET(Komplex_BUILD_SHARED_LIBS "OFF")

SET(Komplex_LINKER CMAKE_LINKER-NOTFOUND)
SET(Komplex_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Komplex_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Komplex_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Komplex_LIBRARIES "komplex;aztecoo;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(Komplex_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Komplex_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Komplex_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Komplex_MPI_LIBRARIES "")
SET(Komplex_MPI_LIBRARY_DIRS "")
SET(Komplex_MPI_INCLUDE_DIRS "")
SET(Komplex_MPI_EXEC "")
SET(Komplex_MPI_EXEC_MAX_NUMPROCS "")
SET(Komplex_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Komplex_PACKAGE_LIST "Komplex;AztecOO;Triutils;Epetra;Teuchos")

## The TPLs enabled for this project
SET(Komplex_TPL_LIST "LAPACK;BLAS")

