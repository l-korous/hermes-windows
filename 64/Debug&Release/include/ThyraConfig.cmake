##############################################################################
#
# CMake variable for use by Trilinos/Thyra clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Thyra build
## ---------------------------------------------------------------------------

SET(Thyra_CXX_COMPILER "cl")

SET(Thyra_C_COMPILER "cl")

SET(Thyra_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Thyra build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Thyra_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Thyra_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Thyra_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Thyra_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Thyra_SHARED_LIB_RPATH_COMMAND "")
SET(Thyra_BUILD_SHARED_LIBS "OFF")

SET(Thyra_LINKER CMAKE_LINKER-NOTFOUND)
SET(Thyra_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Thyra_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Thyra_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Thyra_LIBRARIES "thyraepetraext;thyraepetra;thyra;epetraext;triutils;epetra;rtop;teuchos")

## Specification of directories for TPL headers
SET(Thyra_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Thyra_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Thyra_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Thyra_MPI_LIBRARIES "")
SET(Thyra_MPI_LIBRARY_DIRS "")
SET(Thyra_MPI_INCLUDE_DIRS "")
SET(Thyra_MPI_EXEC "")
SET(Thyra_MPI_EXEC_MAX_NUMPROCS "")
SET(Thyra_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Thyra_PACKAGE_LIST "Thyra;EpetraExt;Tpetra;Triutils;Zoltan;Epetra;Kokkos;RTOp;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(Thyra_TPL_LIST "LAPACK;BLAS")

