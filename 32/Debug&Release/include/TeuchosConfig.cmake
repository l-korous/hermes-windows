##############################################################################
#
# CMake variable for use by Trilinos/Teuchos clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Teuchos build
## ---------------------------------------------------------------------------

SET(Teuchos_CXX_COMPILER "cl")

SET(Teuchos_C_COMPILER "cl")

SET(Teuchos_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Teuchos build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Teuchos_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Teuchos_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Teuchos_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Teuchos_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Teuchos_SHARED_LIB_RPATH_COMMAND "")
SET(Teuchos_BUILD_SHARED_LIBS "OFF")

SET(Teuchos_LINKER CMAKE_LINKER-NOTFOUND)
SET(Teuchos_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Teuchos_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Teuchos_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Teuchos_LIBRARIES "teuchos")

## Specification of directories for TPL headers
SET(Teuchos_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Teuchos_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Teuchos_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Teuchos_MPI_LIBRARIES "")
SET(Teuchos_MPI_LIBRARY_DIRS "")
SET(Teuchos_MPI_INCLUDE_DIRS "")
SET(Teuchos_MPI_EXEC "")
SET(Teuchos_MPI_EXEC_MAX_NUMPROCS "")
SET(Teuchos_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Teuchos_PACKAGE_LIST "Teuchos")

## The TPLs enabled for this project
SET(Teuchos_TPL_LIST "LAPACK;BLAS")

