##############################################################################
#
# CMake variable for use by Trilinos/Ifpack clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Ifpack build
## ---------------------------------------------------------------------------

SET(Ifpack_CXX_COMPILER "cl")

SET(Ifpack_C_COMPILER "cl")

SET(Ifpack_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Ifpack build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Ifpack_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Ifpack_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Ifpack_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Ifpack_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Ifpack_SHARED_LIB_RPATH_COMMAND "")
SET(Ifpack_BUILD_SHARED_LIBS "OFF")

SET(Ifpack_LINKER CMAKE_LINKER-NOTFOUND)
SET(Ifpack_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Ifpack_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Ifpack_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Ifpack_LIBRARIES "ifpack;amesos;aztecoo;epetraext;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(Ifpack_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Ifpack_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Ifpack_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Ifpack_MPI_LIBRARIES "")
SET(Ifpack_MPI_LIBRARY_DIRS "")
SET(Ifpack_MPI_INCLUDE_DIRS "")
SET(Ifpack_MPI_EXEC "")
SET(Ifpack_MPI_EXEC_MAX_NUMPROCS "")
SET(Ifpack_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Ifpack_PACKAGE_LIST "Ifpack;Amesos;AztecOO;EpetraExt;Triutils;Zoltan;Epetra;Teuchos")

## The TPLs enabled for this project
SET(Ifpack_TPL_LIST "LAPACK;BLAS")

