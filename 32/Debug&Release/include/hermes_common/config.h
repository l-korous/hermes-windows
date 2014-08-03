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
#define WITH_MUMPS
/* #undef WITH_SUPERLU */
/* #undef WITH_PETSC */
#define WITH_MATIO
/* #undef WITH_EXODUSII */
/* #undef WITH_MPI */

/* #undef WITH_TC_MALLOC */
/* #undef WITH_PJLIB */
#define WITH_BSON
#define WITH_MATIO
/* #undef MONGO_STATIC_BUILD */
/* #undef UMFPACK_LONG_INT */

// stacktrace
/* #undef WITH_WINDOWS_STACKWALKER */
/* #undef EXECINFO_FOUND */

// trilinos
#define WITH_TRILINOS
#define HAVE_AMESOS
#define HAVE_AZTECOO
#define HAVE_TEUCHOS
#define HAVE_EPETRA
#define HAVE_IFPACK
#define HAVE_ML
#define HAVE_NOX
#define HAVE_KOMPLEX

// GLUT
/* #undef NOGLUT */

// BFD
/* #undef HAVE_BFD */

#endif
