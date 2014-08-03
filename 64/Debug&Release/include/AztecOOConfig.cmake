##############################################################################
#
# CMake variable for use by Trilinos/AztecOO clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/AztecOO build
## ---------------------------------------------------------------------------

SET(AztecOO_CXX_COMPILER "cl")

SET(AztecOO_C_COMPILER "cl")

SET(AztecOO_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/AztecOO build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(AztecOO_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(AztecOO_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(AztecOO_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(AztecOO_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(AztecOO_SHARED_LIB_RPATH_COMMAND "")
SET(AztecOO_BUILD_SHARED_LIBS "OFF")

SET(AztecOO_LINKER CMAKE_LINKER-NOTFOUND)
SET(AztecOO_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(AztecOO_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(AztecOO_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(AztecOO_LIBRARIES "aztecoo;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(AztecOO_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(AztecOO_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(AztecOO_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(AztecOO_MPI_LIBRARIES "")
SET(AztecOO_MPI_LIBRARY_DIRS "")
SET(AztecOO_MPI_INCLUDE_DIRS "")
SET(AztecOO_MPI_EXEC "")
SET(AztecOO_MPI_EXEC_MAX_NUMPROCS "")
SET(AztecOO_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(AztecOO_PACKAGE_LIST "AztecOO;Triutils;Epetra;Teuchos")

## The TPLs enabled for this project
SET(AztecOO_TPL_LIST "LAPACK;BLAS")

