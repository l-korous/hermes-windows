#ifndef __HERMES_CONFIG_H_
#define __HERMES_CONFIG_H_

/* #undef HERMES_STATIC_LIBS */

// OpenMP
#define NUM_THREADS 8
#define WITH_OPENMP

/* #undef HAVE_FMEMOPEN */
/* #undef HAVE_LOG2 */
/* #undef EXTREME_QUAD */

#define WITH_UMFPACK
#define WITH_PARALUTION
/* #undef WITH_MUMPS */
/* #undef WITH_SUPERLU */
/* #undef WITH_PETSC */
/* #undef WITH_MATIO */
/* #undef WITH_EXODUSII */
/* #undef WITH_MPI */

/* #undef WITH_TC_MALLOC */
/* #undef WITH_PJLIB */
/* #undef WITH_BSON */
/* #undef WITH_MATIO */
/* #undef MONGO_STATIC_BUILD */
/* #undef UMFPACK_LONG_INT */

// stacktrace
/* #undef WITH_WINDOWS_STACKWALKER */
/* #undef EXECINFO_FOUND */

// trilinos
/* #undef WITH_TRILINOS */
/* #undef HAVE_AMESOS */
/* #undef HAVE_AZTECOO */
/* #undef HAVE_TEUCHOS */
/* #undef HAVE_EPETRA */
/* #undef HAVE_IFPACK */
/* #undef HAVE_ML */
/* #undef HAVE_NOX */
/* #undef HAVE_KOMPLEX */

// GLUT
/* #undef NOGLUT */

// BFD
/* #undef HAVE_BFD */

#endif
