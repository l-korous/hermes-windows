##############################################################################
#
# CMake variable for use by Trilinos/NOX clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/NOX build
## ---------------------------------------------------------------------------

SET(NOX_CXX_COMPILER "cl")

SET(NOX_C_COMPILER "cl")

SET(NOX_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/NOX build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(NOX_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(NOX_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(NOX_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(NOX_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(NOX_SHARED_LIB_RPATH_COMMAND "")
SET(NOX_BUILD_SHARED_LIBS "OFF")

SET(NOX_LINKER CMAKE_LINKER-NOTFOUND)
SET(NOX_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(NOX_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(NOX_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(NOX_LIBRARIES "locathyra;locaepetra;loca;noxthyra;noxepetra;nox;ModeLaplace;anasaziepetra;anasazi;stratimikos;stratimikosbelos;stratimikosaztecoo;stratimikosamesos;stratimikosml;stratimikosifpack;belosepetra;belos;ml;ifpack;amesos;galeri;aztecoo;thyraepetraext;thyraepetra;thyra;epetraext;triutils;epetra;rtop;teuchos")

## Specification of directories for TPL headers
SET(NOX_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(NOX_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(NOX_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(NOX_MPI_LIBRARIES "")
SET(NOX_MPI_LIBRARY_DIRS "")
SET(NOX_MPI_INCLUDE_DIRS "")
SET(NOX_MPI_EXEC "")
SET(NOX_MPI_EXEC_MAX_NUMPROCS "")
SET(NOX_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(NOX_PACKAGE_LIST "NOX;Anasazi;Stratimikos;Belos;ML;Ifpack;Amesos;Galeri;AztecOO;Isorropia;Thyra;EpetraExt;Tpetra;Triutils;Zoltan;Epetra;Kokkos;RTOp;ThreadPool;Teuchos")

## The TPLs enabled for this project
SET(NOX_TPL_LIST "LAPACK;BLAS")

