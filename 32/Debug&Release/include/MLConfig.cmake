##############################################################################
#
# CMake variable for use by Trilinos/ML clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/ML build
## ---------------------------------------------------------------------------

SET(ML_CXX_COMPILER "cl")

SET(ML_C_COMPILER "cl")

SET(ML_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/ML build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(ML_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(ML_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(ML_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(ML_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(ML_SHARED_LIB_RPATH_COMMAND "")
SET(ML_BUILD_SHARED_LIBS "OFF")

SET(ML_LINKER CMAKE_LINKER-NOTFOUND)
SET(ML_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(ML_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(ML_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(ML_LIBRARIES "ml;ifpack;amesos;galeri;aztecoo;epetraext;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(ML_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(ML_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(ML_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(ML_MPI_LIBRARIES "")
SET(ML_MPI_LIBRARY_DIRS "")
SET(ML_MPI_INCLUDE_DIRS "")
SET(ML_MPI_EXEC "")
SET(ML_MPI_EXEC_MAX_NUMPROCS "")
SET(ML_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(ML_PACKAGE_LIST "ML;Ifpack;Amesos;Galeri;AztecOO;Isorropia;EpetraExt;Tpetra;Triutils;Zoltan;Epetra;Kokkos;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(ML_TPL_LIST "LAPACK;BLAS")

