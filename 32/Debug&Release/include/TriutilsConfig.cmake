##############################################################################
#
# CMake variable for use by Trilinos/Triutils clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Triutils build
## ---------------------------------------------------------------------------

SET(Triutils_CXX_COMPILER "cl")

SET(Triutils_C_COMPILER "cl")

SET(Triutils_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Triutils build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Triutils_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Triutils_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Triutils_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Triutils_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Triutils_SHARED_LIB_RPATH_COMMAND "")
SET(Triutils_BUILD_SHARED_LIBS "OFF")

SET(Triutils_LINKER CMAKE_LINKER-NOTFOUND)
SET(Triutils_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Triutils_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Triutils_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Triutils_LIBRARIES "triutils;epetra")

## Specification of directories for TPL headers
SET(Triutils_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Triutils_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Triutils_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Triutils_MPI_LIBRARIES "")
SET(Triutils_MPI_LIBRARY_DIRS "")
SET(Triutils_MPI_INCLUDE_DIRS "")
SET(Triutils_MPI_EXEC "")
SET(Triutils_MPI_EXEC_MAX_NUMPROCS "")
SET(Triutils_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Triutils_PACKAGE_LIST "Triutils;Epetra")

## The TPLs enabled for this project
SET(Triutils_TPL_LIST "LAPACK;BLAS")

