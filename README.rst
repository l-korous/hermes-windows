Information about this repository
---------------------------------

Structure
~~~~~~~~~

There are two repositories - for 32bit and 64bit - versions of both dependencies and hermes library.

Under both main repositories, there are directories - Debug, Release, and Debug&Release with the following meaning:

  1. Debug&Release - these files can be used for both Debug and Release builds (of the user programs) - include files and dynamic libraries
  2. Debug - only for Debug - static libraries & Debug versions of hermes
  3. Release - only for Release - static libraries & Release versions of hermes
  
These files are sufficient for building Hermes with the following settings in the CMake.vars::

  set(WITH_TC_MALLOC NO)
  set(WITH_BSON YES)        # Missing in the 64-bit build
  set(WITH_MATIO YES)
  set(WITH_UMFPACK YES)
  set(WITH_PARALUTION YES)
  set(WITH_MUMPS YES)
  set(WITH_TRILINOS YES)
  set(WITH_EXODUSII NO)
  set(WITH_OPENMP YES)
  set(WITH_MPI NO)
  set(WITH_PJLIB NO)
  set(WITH_H2D YES)
  set(H2D_WITH_GLUT YES)
  