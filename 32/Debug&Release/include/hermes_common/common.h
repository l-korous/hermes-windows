// This file is part of HermesCommon.
//
// Hermes2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D.  If not, see <http://www.gnu.org/licenses/>.

/*! \file common.h
\brief File containing common definitions, and basic global enums etc. for HermesCommon.
*/
#ifndef __HERMES_COMMON_COMMON_H
#define __HERMES_COMMON_COMMON_H

#include <complex>

#include <stdexcept>
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <initializer_list>
#include <time.h>
#include <float.h>
#include <climits>
#include <limits.h>
#include <errno.h>
#include <cmath>

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <map>
#include <cstdio>
#include <stdarg.h>
#include <sstream>
#ifdef _WINDOWS
#include <memory>
#else
#include <tr1/memory>
#endif
#include <algorithm>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <utility>

#include "config.h"

#ifdef WITH_TC_MALLOC
#include "tcmalloc.h"
#endif

#ifdef WITH_BSON
#define MONGO_HAVE_STDINT
#include "bson.h"
#endif

#ifdef WITH_MATIO
#include "matio.h"
#endif

#ifdef WITH_OPENMP
#include <omp.h>
#else
inline int omp_get_max_threads() { return 1; }
inline int omp_get_num_threads() { return 1; }
inline int omp_get_thread_num() { return 0; }
#endif

#ifdef WITH_PJLIB
#include "pjlib.h"
#endif

/// Int types handling.
#ifdef JU_WIN
typedef __int8           int8_t;
typedef __int16          int16_t;
typedef __int32          int32_t;
typedef __int64          int64_t;

typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <inttypes.h>
#endif

#ifdef _WINDOWS
#define finite _finite
#endif

typedef int int2[2];
typedef int int3[3];
typedef int int4[4];
typedef int int5[5];

typedef double double2[2];
typedef double double3[3];
typedef double double4[4];
typedef double double2x2[2][2];
typedef double double2x3[2][3];
typedef double double2x4[2][4];
typedef double double3x2[3][2];
typedef double double3x3[3][3];
typedef double double3x4[3][4];

typedef float float2[2];
typedef float float3[3];
typedef float float4[4];
typedef float float2x2[2][2];
typedef float float2x3[2][3];
typedef float float2x4[2][4];
typedef float float3x2[3][2];
typedef float float3x3[3][3];
typedef float float3x4[3][4];

template<typename Scalar>
class Scalar2
{
  Scalar val[2];

public:
  Scalar2(Scalar v1, Scalar v2)
  {
    val[0] = v1; val[1] = v2;
  }

  Scalar& operator[] (int idx)
  {
    assert(idx >= 0 && idx < 2);
    return val[idx];
  }
};

template<typename Scalar>
class Scalar3
{
  Scalar val[3];

public:
  Scalar3(Scalar v1, Scalar v2, Scalar v3)
  {
    val[0] = v1; val[1] = v2, val[2] = v3;
  }

  Scalar& operator[] (int idx)
  {
    assert(idx >= 0 && idx < 3);
    return val[idx];
  }
};

// Pi.
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

namespace Hermes
{
  const double HermesEpsilon = std::numeric_limits<double>::epsilon() * 10.;
  const double HermesSqrtEpsilon = std::sqrt(std::numeric_limits<double>::epsilon());

  inline int sqr(int x) { return x*x; }
  inline double sqr(double x) { return x*x; }
  inline double sqrt(double x) { return std::sqrt(x); }
  inline double sqr(std::complex<double> x)   { return std::norm(x); }
  inline double magn(double x) { return fabs(x); }
  inline double conj(double a) { return a; }
  inline double cos(double x) { return std::cos(x); }
  inline double sin(double x) { return std::sin(x); }
  inline double atan(double x) { return std::atan(x); }
  inline double atan2(double x, double y) { return std::atan2(x, y); }
  inline double abs(double x) { return std::abs(x); }
  inline double pow(double x, double y) { return std::pow(x, y); }
  inline double log(double x) { return std::log(x); }

  /* event codes */
#define HERMES_EC_ERROR 'E' ///< An event code: warnings. \internal
#define HERMES_EC_WARNING 'W' ///< An event code: warnings. \internal
#define HERMES_EC_INFO 'I' ///< An event code: info about results. \internal

  /// A size of a delimiter in a log file. \internal \ingroup g_logging
#define HERMES_LOG_FILE_DELIM_SIZE 80
#define BUF_SZ 2048

  /* function name */
  /** \def __CURRENT_FUNCTION
  *  \brief A platform-dependent string defining a current function. \internal */
#ifdef _WINDOWS
# ifdef __MINGW32__ //MinGW
#   define __CURRENT_FUNCTION __func__
# else //MSVC and other compilers
#   define __CURRENT_FUNCTION __FUNCTION__
# endif
#else //Linux and Mac
# define __CURRENT_FUNCTION __PRETTY_FUNCTION__
#endif

  // Represents "any" part of the boundary when deciding where (on which elements) to assemble the form at hand.
  const std::string HERMES_ANY = "-1234";
  // For internal use.
  const int HERMES_ANY_INT = -1234;

  namespace Exceptions
  {
    class NullException;
    class LengthException;
  }

  namespace Helpers
  {
    /// Check for nullptr.
    template<typename T>
    inline void check_for_null(T instance)
    {
      if (!instance)
        throw Hermes::Exceptions::NullException();
    }

    /// Check length of a vector.
    template<typename T>
    inline void check_length(const std::vector<T>& instance, const unsigned int length)
    {
      if (instance.size() != length)
        throw Hermes::Exceptions::LengthException(instance.size(), length);
    }

    /// Check length of a vector.
    template<typename T, typename U>
    inline void check_length(const std::vector<T>& instanceT, const std::vector<U>& instanceU)
    {
      if (instanceT.size() != instanceU.size())
        throw Hermes::Exceptions::LengthException();
    }

    /// Number printers.
    inline void fprint_num(FILE*f, double x, char* number_format)
    {
      fprintf(f, number_format, x);
    }

    inline void fprint_num(FILE*f, std::complex<double> x, char* number_format)
    {
      std::stringstream ss;
      ss << "(" << number_format << ", " << number_format << ")";
      fprintf(f, ss.str().c_str(), x.real(), x.imag());
    }

    template<typename Scalar>
    inline void fprint_coordinate_num(FILE*f, int i, int j, Scalar x, char* number_format)
    {
      fprintf(f, "%d %d ", i, j);
      fprint_num(f, x, number_format);
    }

    /// Type deductors.
    template<typename Scalar>
    struct TypeIsReal
    {
      static const bool value = false;
    };

    template<typename Scalar>
    struct TypeIsComplex
    {
      static const bool value = false;
    };

    template<>
    struct TypeIsReal < double >
    {
      static const bool value = true;
    };

    template<>
    struct TypeIsComplex < std::complex<double> >
    {
      static const bool value = true;
    };
  }

  namespace BLAS
  {
#ifdef WITH_BLAS
    // BLAS-related functions

    // Complex part.
#ifdef __cplusplus
    extern "C"
    {
#endif
      extern int zscal_(int *, std::complex<double> *, std::complex<double> *, int *);
      extern int zaxpy_(int *, std::complex<double> *, std::complex<double> *, int *, std::complex<double> *, int *);
      extern int zcopy_(int *, std::complex<double> *, int *, std::complex<double> *, int *);

      extern int dscal_(int *, double *, double *, int *);
      extern int daxpy_(int *, double *, double *, int *, double *, int *);
      extern int dcopy_(int *, double *, int *, double *, int *);

#ifdef __cplusplus
    }
#endif

    /// x <- alpha * x
    inline void blas_scal(int n, std::complex<double> alpha, std::complex<double> *x, int incx) { zscal_(&n, &alpha, x, &incx); }
    /// y <- alpha * x + y
    inline void blas_axpy(int n, std::complex<double> alpha, std::complex<double> *x, int incx, std::complex<double> *y, int incy) { zaxpy_(&n, &alpha, x, &incx, y, &incy); }
    /// y <- x
    inline void blas_copy(int n, std::complex<double> *x, int incx, std::complex<double> *y, int incy) { zcopy_(&n, x, &incx, y, &incx); }

    /// x <- alpha * x
    inline void blas_scal(int n, double alpha, double *x, int incx) { dscal_(&n, &alpha, x, &incx); }
    /// y <- alpha * x + y
    inline void blas_axpy(int n, double alpha, double *x, int incx, double *y, int incy) { daxpy_(&n, &alpha, x, &incx, y, &incy); }
    /// y <- x
    inline void blas_copy(int n, double *x, int incx, double *y, int incy) { dcopy_(&n, x, &incx, y, &incx); }

#endif
  }
}
#endif

/**

\mainpage

This manual documents the source code of hermes_common. It is intended for the developers of
the library. If you are only interested in using hermes_common together with hermesNd, please refer to the User's Manual.

The Hermes Common library encompasses the functionality shared by the code for any number of dimensions (1, 2, 3). The uppermost-level API is provided by the class
<a href="classHermes_1_1Api.html"><h1>Api</a></h1>

Hermes Common provides utility features, like
<ul>
<li><a href="namespaceHermes_1_1Mixins.html">Mixin classes</a>
<li>General representation of a 1,2,3-dimensional functions: <a href="classHermes_1_1Hermes1DFunction.html">Hermes 1D function</a>, <a href="classHermes_1_1Hermes2DFunction.html">Hermes 2D function</a>, <a href="classHermes_1_1Hermes3DFunction.html">Hermes 3D function</a>
<li><a href="classHermes_1_1vector.html">Own std::vector-based vector class</a>
<li><a href="classHermes_1_1ButcherTable.html">Butcher's tables</a>
<li><a href="classCallStack.html">Call stack printing</a>
<li><a href="classHermes_1_1Exceptions_1_1Exception.html">Exceptions - base class & general exceptions</a>.
</ul>

The library provides also stand-alone functionality, needed to solve problems shared by codes for all dimensions. The first big part is

<h3><a href="namespaceHermes_1_1Algebra.html">Linear algebra</a></h3>
<h4>Matrix structures</h4>
These structures correspond to the most widely used storage type for matrices - sparse matrices.
<img src="classHermes_1_1Algebra_1_1Matrix.png">
<center>
<a href="classHermes_1_1Algebra_1_1Matrix.html">Matrix structures</a>
</center>

<h4><a href="namespaceHermes_1_1Algebra_1_1DenseMatrixOperations.html">Dense matrix structures</a></h4>
These routines are here to support occasional needs to handle dense matrices, that are so small that storing them using sparse structures would be ineffective.
<br />
Vector structures
<img src="classHermes_1_1Algebra_1_1Vector.png">
<center>
<a href="classHermes_1_1Algebra_1_1Vector.html">Vector structures</a>
</center>

after one is able to store / load, and do other operations with linear algebraic structures, one would like to solve Ax = b:

<a href="namespaceHermes_1_1Solvers.html">
<h4>Linear matrix solvers</h4></a>
<img src="classHermes_1_1Solvers_1_1LinearMatrixSolver.png">
<center>
<a href="classHermes_1_1Solvers_1_1LinearMatrixSolver.html">Linear matrix solvers</a>
</center>
... possibly with

<a href="namespaceHermes_1_1Preconditioners.html"><h4>Preconditioners</a></h4>
<img src="classHermes_1_1Preconditioners_1_1Precond.png">
<center>
<a href="classHermes_1_1Preconditioners_1_1Precond.html">Preconditioners</a>
</center>
*/
