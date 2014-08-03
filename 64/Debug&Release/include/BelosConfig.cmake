##############################################################################
#
# CMake variable for use by Trilinos/Belos clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Belos build
## ---------------------------------------------------------------------------

SET(Belos_CXX_COMPILER "cl")

SET(Belos_C_COMPILER "cl")

SET(Belos_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Belos build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Belos_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Belos_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Belos_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Belos_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Belos_SHARED_LIB_RPATH_COMMAND "")
SET(Belos_BUILD_SHARED_LIBS "OFF")

SET(Belos_LINKER CMAKE_LINKER-NOTFOUND)
SET(Belos_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Belos_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Belos_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Belos_LIBRARIES "belosepetra;belos;epetra;teuchos")

## Specification of directories for TPL headers
SET(Belos_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Belos_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Belos_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Belos_MPI_LIBRARIES "")
SET(Belos_MPI_LIBRARY_DIRS "")
SET(Belos_MPI_INCLUDE_DIRS "")
SET(Belos_MPI_EXEC "")
SET(Belos_MPI_EXEC_MAX_NUMPROCS "")
SET(Belos_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Belos_PACKAGE_LIST "Belos;Tpetra;Epetra;Kokkos;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(Belos_TPL_LIST "LAPACK;BLAS")

