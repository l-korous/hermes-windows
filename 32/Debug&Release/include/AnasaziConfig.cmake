##############################################################################
#
# CMake variable for use by Trilinos/Anasazi clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Anasazi build
## ---------------------------------------------------------------------------

SET(Anasazi_CXX_COMPILER "cl")

SET(Anasazi_C_COMPILER "cl")

SET(Anasazi_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Anasazi build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Anasazi_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Anasazi_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Anasazi_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Anasazi_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Anasazi_SHARED_LIB_RPATH_COMMAND "")
SET(Anasazi_BUILD_SHARED_LIBS "OFF")

SET(Anasazi_LINKER CMAKE_LINKER-NOTFOUND)
SET(Anasazi_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Anasazi_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Anasazi_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Anasazi_LIBRARIES "ModeLaplace;anasaziepetra;anasazi;thyraepetraext;thyraepetra;thyra;epetraext;triutils;epetra;rtop;teuchos")

## Specification of directories for TPL headers
SET(Anasazi_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Anasazi_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Anasazi_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Anasazi_MPI_LIBRARIES "")
SET(Anasazi_MPI_LIBRARY_DIRS "")
SET(Anasazi_MPI_INCLUDE_DIRS "")
SET(Anasazi_MPI_EXEC "")
SET(Anasazi_MPI_EXEC_MAX_NUMPROCS "")
SET(Anasazi_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Anasazi_PACKAGE_LIST "Anasazi;Thyra;EpetraExt;Tpetra;Triutils;Zoltan;Epetra;Kokkos;RTOp;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(Anasazi_TPL_LIST "LAPACK;BLAS")

