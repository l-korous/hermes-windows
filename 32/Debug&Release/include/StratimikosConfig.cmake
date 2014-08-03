##############################################################################
#
# CMake variable for use by Trilinos/Stratimikos clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Stratimikos build
## ---------------------------------------------------------------------------

SET(Stratimikos_CXX_COMPILER "cl")

SET(Stratimikos_C_COMPILER "cl")

SET(Stratimikos_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Stratimikos build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Stratimikos_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Stratimikos_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Stratimikos_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Stratimikos_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Stratimikos_SHARED_LIB_RPATH_COMMAND "")
SET(Stratimikos_BUILD_SHARED_LIBS "OFF")

SET(Stratimikos_LINKER CMAKE_LINKER-NOTFOUND)
SET(Stratimikos_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Stratimikos_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Stratimikos_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Stratimikos_LIBRARIES "stratimikos;stratimikosbelos;stratimikosaztecoo;stratimikosamesos;stratimikosml;stratimikosifpack;belosepetra;belos;ml;ifpack;amesos;galeri;aztecoo;thyraepetraext;thyraepetra;thyra;epetraext;triutils;epetra;rtop;teuchos")

## Specification of directories for TPL headers
SET(Stratimikos_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Stratimikos_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Stratimikos_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Stratimikos_MPI_LIBRARIES "")
SET(Stratimikos_MPI_LIBRARY_DIRS "")
SET(Stratimikos_MPI_INCLUDE_DIRS "")
SET(Stratimikos_MPI_EXEC "")
SET(Stratimikos_MPI_EXEC_MAX_NUMPROCS "")
SET(Stratimikos_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Stratimikos_PACKAGE_LIST "Stratimikos;Belos;ML;Ifpack;Amesos;Galeri;AztecOO;Isorropia;Thyra;EpetraExt;Tpetra;Triutils;Zoltan;Epetra;Kokkos;RTOp;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(Stratimikos_TPL_LIST "LAPACK;BLAS")

