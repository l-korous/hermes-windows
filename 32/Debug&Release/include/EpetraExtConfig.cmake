##############################################################################
#
# CMake variable for use by Trilinos/EpetraExt clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/EpetraExt build
## ---------------------------------------------------------------------------

SET(EpetraExt_CXX_COMPILER "cl")

SET(EpetraExt_C_COMPILER "cl")

SET(EpetraExt_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/EpetraExt build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(EpetraExt_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(EpetraExt_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(EpetraExt_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(EpetraExt_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(EpetraExt_SHARED_LIB_RPATH_COMMAND "")
SET(EpetraExt_BUILD_SHARED_LIBS "OFF")

SET(EpetraExt_LINKER CMAKE_LINKER-NOTFOUND)
SET(EpetraExt_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(EpetraExt_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(EpetraExt_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(EpetraExt_LIBRARIES "epetraext;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(EpetraExt_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(EpetraExt_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(EpetraExt_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(EpetraExt_MPI_LIBRARIES "")
SET(EpetraExt_MPI_LIBRARY_DIRS "")
SET(EpetraExt_MPI_INCLUDE_DIRS "")
SET(EpetraExt_MPI_EXEC "")
SET(EpetraExt_MPI_EXEC_MAX_NUMPROCS "")
SET(EpetraExt_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(EpetraExt_PACKAGE_LIST "EpetraExt;Triutils;Zoltan;Epetra;Teuchos")

## The TPLs enabled for this project
SET(EpetraExt_TPL_LIST "LAPACK;BLAS")

