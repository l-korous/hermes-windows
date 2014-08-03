##############################################################################
#
# CMake variable for use by Trilinos/Amesos clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Amesos build
## ---------------------------------------------------------------------------

SET(Amesos_CXX_COMPILER "cl")

SET(Amesos_C_COMPILER "cl")

SET(Amesos_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Amesos build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Amesos_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Amesos_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Amesos_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Amesos_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Amesos_SHARED_LIB_RPATH_COMMAND "")
SET(Amesos_BUILD_SHARED_LIBS "OFF")

SET(Amesos_LINKER CMAKE_LINKER-NOTFOUND)
SET(Amesos_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Amesos_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Amesos_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Amesos_LIBRARIES "amesos;epetraext;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(Amesos_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Amesos_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Amesos_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Amesos_MPI_LIBRARIES "")
SET(Amesos_MPI_LIBRARY_DIRS "")
SET(Amesos_MPI_INCLUDE_DIRS "")
SET(Amesos_MPI_EXEC "")
SET(Amesos_MPI_EXEC_MAX_NUMPROCS "")
SET(Amesos_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Amesos_PACKAGE_LIST "Amesos;EpetraExt;Triutils;Zoltan;Epetra;Teuchos")

## The TPLs enabled for this project
SET(Amesos_TPL_LIST "LAPACK;BLAS")

