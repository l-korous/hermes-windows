##############################################################################
#
# CMake variable for use by Trilinos/Epetra clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Epetra build
## ---------------------------------------------------------------------------

SET(Epetra_CXX_COMPILER "cl")

SET(Epetra_C_COMPILER "cl")

SET(Epetra_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Epetra build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Epetra_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Epetra_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Epetra_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Epetra_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Epetra_SHARED_LIB_RPATH_COMMAND "")
SET(Epetra_BUILD_SHARED_LIBS "OFF")

SET(Epetra_LINKER CMAKE_LINKER-NOTFOUND)
SET(Epetra_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Epetra_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Epetra_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Epetra_LIBRARIES "epetra")

## Specification of directories for TPL headers
SET(Epetra_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Epetra_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Epetra_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Epetra_MPI_LIBRARIES "")
SET(Epetra_MPI_LIBRARY_DIRS "")
SET(Epetra_MPI_INCLUDE_DIRS "")
SET(Epetra_MPI_EXEC "")
SET(Epetra_MPI_EXEC_MAX_NUMPROCS "")
SET(Epetra_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Epetra_PACKAGE_LIST "Epetra")

## The TPLs enabled for this project
SET(Epetra_TPL_LIST "LAPACK;BLAS")

