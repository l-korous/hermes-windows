##############################################################################
#
# CMake variable for use by Trilinos/Galeri clients. 
#
# Do not edit: This file was generated automatically by CMake.
#
##############################################################################


## ---------------------------------------------------------------------------
## Compilers used by Trilinos/Galeri build
## ---------------------------------------------------------------------------

SET(Galeri_CXX_COMPILER "cl")

SET(Galeri_C_COMPILER "cl")

SET(Galeri_FORTRAN_COMPILER "")


## ---------------------------------------------------------------------------
## Compiler flags used by Trilinos/Galeri build
## ---------------------------------------------------------------------------

## Set compiler flags, including those determined by build type
SET(Galeri_CXX_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")

SET(Galeri_C_FLAGS " /DWIN32 /D_WINDOWS /W3 /Zm1000 /D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1")

SET(Galeri_FORTRAN_FLAGS " ")

## Extra link flags (e.g., specification of fortran libraries)
SET(Galeri_EXTRA_LD_FLAGS "")

## This is the command-line entry used for setting rpaths. In a build
## with static libraries it will be empty. 
SET(Galeri_SHARED_LIB_RPATH_COMMAND "")
SET(Galeri_BUILD_SHARED_LIBS "OFF")

SET(Galeri_LINKER CMAKE_LINKER-NOTFOUND)
SET(Galeri_AR )

## ---------------------------------------------------------------------------
## Set library specifications and paths 
## ---------------------------------------------------------------------------

## List of package include dirs
SET(Galeri_INCLUDE_DIRS "d:/hpfem/hermes/dependencies/include")

## List of package library paths
SET(Galeri_LIBRARY_DIRS "d:/hpfem/hermes/dependencies/lib")

## List of package libraries
SET(Galeri_LIBRARIES "galeri;epetraext;triutils;epetra;teuchos")

## Specification of directories for TPL headers
SET(Galeri_TPL_INCLUDE_DIRS "")

## Specification of directories for TPL libraries
SET(Galeri_TPL_LIBRARY_DIRS "")

## List of required TPLs
SET(Galeri_TPL_LIBRARIES "lapack;blas")

## ---------------------------------------------------------------------------
## MPI specific variables
##   These variables are provided to make it easier to get the mpi libraries
##   and includes on systems that do not use the mpi wrappers for compiling
## ---------------------------------------------------------------------------

SET(Galeri_MPI_LIBRARIES "")
SET(Galeri_MPI_LIBRARY_DIRS "")
SET(Galeri_MPI_INCLUDE_DIRS "")
SET(Galeri_MPI_EXEC "")
SET(Galeri_MPI_EXEC_MAX_NUMPROCS "")
SET(Galeri_MPI_EXEC_NUMPROCS_FLAG "")

## ---------------------------------------------------------------------------
## Set useful general variables 
## ---------------------------------------------------------------------------

## The packages enabled for this project
SET(Galeri_PACKAGE_LIST "Galeri;EpetraExt;Triutils;Zoltan;Epetra;Teuchos")

## The TPLs enabled for this project
SET(Galeri_TPL_LIST "LAPACK;BLAS")

