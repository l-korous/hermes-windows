##############################################################################
#
# CMake variable for use by Trilinos/RTOp clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/RTOp build
## ---------------------------------------------------------------------------

SET(RTOp_CXX_COMPILER "cl")

SET(RTOp_C_COMPILER "cl")

SET(RTOp_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/RTOp build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(RTOp_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(RTOp_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(RTOp_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(RTOp_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(RTOp_SHARED_LIB_RPATH_COMMAND "")
SET(RTOp_BUILD_SHARED_LIBS "OFF")

SET(RTOp_LINKER CMAKE_LINKER-NOTFOUND)
SET(RTOp_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(RTOp_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(RTOp_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(RTOp_LIBRARIES "rtop;teuchos")

## Specification of directories for TPL headers
SET(RTOp_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(RTOp_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(RTOp_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(RTOp_MPI_LIBRARIES "")
SET(RTOp_MPI_LIBRARY_DIRS "")
SET(RTOp_MPI_INCLUDE_DIRS "")
SET(RTOp_MPI_EXEC "")
SET(RTOp_MPI_EXEC_MAX_NUMPROCS "")
SET(RTOp_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(RTOp_PACKAGE_LIST "RTOp;Teuchos")

## The TPLs enabled for this project
SET(RTOp_TPL_LIST "LAPACK;BLAS")

