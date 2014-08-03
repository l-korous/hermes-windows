// This file is part of Hermes2D.
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

#ifndef __H2D_EXACT_SOLUTION_H
#define __H2D_EXACT_SOLUTION_H

#include "solution.h"

namespace Hermes
{
  namespace Hermes2D
  {
    template<typename T> class Geom;

    /// \brief Represents an exact solution of a PDE.
    ///
    /// ExactSolution represents an arbitrary user-specified function defined on a domain (mesh),
    /// typically an exact solution to a PDE. This can be used to compare an approximate solution
    /// with an exact solution (see DiffFilter).
    template<typename Scalar>
    class HERMES_API ExactSolution : public Solution < Scalar >
    {
    public:
      ExactSolution(MeshSharedPtr mesh);
      virtual ~ExactSolution() {};

      /// Dimension of result - either 1 or 2.
      virtual unsigned int get_dimension() const = 0;

      virtual MeshFunction<Scalar>* clone() const;

      std::string getClassName() const;

      /// Saves the exact solution to an XML file.
      virtual void save(const char* filename) const;
#ifdef WITH_BSON
      virtual void save_bson(const char* filename) const;
#endif
      /// Function returning the integration order that
      /// should be used when integrating the function.
      virtual Hermes::Ord ord(double x, double y) const = 0;

    protected:
      /// For scaling of the solution.
      Scalar exact_multiplicator;
      template<typename T> friend class Solution;
    };

    /// These classes are abstract (pure virtual destructor).
    /// The user is supposed to subclass them (see e.g. NIST benchmarks).
    template<typename Scalar>
    class HERMES_API ExactSolutionScalar : public ExactSolution < Scalar >
    {
    public:
      ExactSolutionScalar(MeshSharedPtr mesh);
      virtual ~ExactSolutionScalar() {};

      /// For Scalar-valued solutions this returns 1.
      virtual unsigned int get_dimension() const;

      /// Function returning the value.
      virtual Scalar value(double x, double y) const = 0;

      /// Function returning the derivatives.
      virtual void derivatives(double x, double y, Scalar& dx, Scalar& dy) const = 0;

      /// Function returning the value and derivatives.
      Scalar exact_function(double x, double y, Scalar& dx, Scalar& dy) const {
        derivatives(x, y, dx, dy);
        return value(x, y);
      };
    };

    /// Serves for postprocessing of element-wise constant values (such as the error in adaptivity).
    /// The second template parameter ValueType must be a type castable to Scalar.
    template<typename Scalar, typename ValueType>
    class HERMES_API ExactSolutionConstantArray : public ExactSolutionScalar < Scalar >
    {
    public:
      /// Constructor.
      /// \param[in] valueArray Array of element-wise values, sorted according to the elements' ids.
      ExactSolutionConstantArray(MeshSharedPtr mesh, ValueType* valueArray, bool deleteArray = false);
      virtual ~ExactSolutionConstantArray();

      virtual MeshFunction<Scalar>* clone() const;

      /// Function returning the value.
      virtual Scalar value(double x, double y) const;
      virtual Ord ord(double x, double y) const;

      /// Function returning the derivatives.
      virtual void derivatives(double x, double y, Scalar& dx, Scalar& dy) const;

      inline std::string getClassName() const { return "ExactSolutionConstantArray"; }

      void setArray(ValueType* valueArray);

    protected:
      /// Array of the values.
      ValueType* valueArray;

      /// Delete the array.
      bool deleteArray;

      template<typename T> friend class Solution;
    };

    template<typename Scalar>
    class HERMES_API ExactSolutionVector : public ExactSolution < Scalar >
    {
    public:
      ExactSolutionVector(MeshSharedPtr mesh);
      virtual ~ExactSolutionVector() {};

      /// For vector-valued solutions this returns 2.
      virtual unsigned int get_dimension() const;

      /// Function returning the value.
      virtual Scalar2<Scalar> value(double x, double y) const = 0;

      /// Function returning the derivatives.
      virtual void derivatives(double x, double y, Scalar2<Scalar>& dx, Scalar2<Scalar>& dy) const = 0;

      /// Function returning the value and derivatives.
      virtual Scalar2<Scalar> exact_function(double x, double y, Scalar2<Scalar>& dx, Scalar2<Scalar>& dy) const {
        derivatives(x, y, dx, dy);
        return value(x, y);
      };
    };

    template<typename Scalar>
    class HERMES_API ConstantSolution : public ExactSolutionScalar < Scalar >
    {
    public:
      ConstantSolution(MeshSharedPtr mesh, Scalar constant);
      virtual ~ConstantSolution() {};

      virtual Scalar value(double x, double y) const;

      virtual void derivatives(double x, double y, Scalar& dx, Scalar& dy) const;

      virtual Ord ord(double x, double y) const;
      virtual MeshFunction<Scalar>* clone() const;

      /// Saves the exact solution to an XML file.
      void save(const char* filename) const;
#ifdef WITH_BSON
      void save_bson(const char* filename) const;
#endif

    protected:
      Scalar constant;
    };

    template<typename Scalar>
    class HERMES_API ZeroSolution : public ExactSolutionScalar < Scalar >
    {
    public:
      ZeroSolution(MeshSharedPtr mesh);
      virtual ~ZeroSolution() {};

      virtual Scalar value(double x, double y) const;

      virtual void derivatives(double x, double y, Scalar& dx, Scalar& dy) const;

      virtual Ord ord(double x, double y) const;
      virtual MeshFunction<Scalar>* clone() const;
    };

    template<typename Scalar>
    class HERMES_API ConstantSolutionVector : public ExactSolutionVector < Scalar >
    {
    public:
      ConstantSolutionVector(MeshSharedPtr mesh, Scalar constantX, Scalar constantY);
      virtual ~ConstantSolutionVector() {};

      virtual Scalar2<Scalar> value(double x, double y) const;

      virtual void derivatives(double x, double y, Scalar2<Scalar>& dx, Scalar2<Scalar>& dy) const;

      virtual Ord ord(double x, double y) const;
      virtual MeshFunction<Scalar>* clone() const;

      /// Saves the exact solution to an XML file.
      void save(const char* filename) const;
#ifdef WITH_BSON
      void save_bson(const char* filename) const;
#endif
    protected:
      Scalar constantX;
      Scalar constantY;
    };

    template<typename Scalar>
    class HERMES_API ZeroSolutionVector : public ExactSolutionVector < Scalar >
    {
    public:
      ZeroSolutionVector(MeshSharedPtr mesh);
      virtual ~ZeroSolutionVector() {};

      virtual Scalar2<Scalar> value(double x, double y) const;

      virtual void derivatives(double x, double y, Scalar2<Scalar>& dx, Scalar2<Scalar>& dy) const;

      virtual Ord ord(double x, double y) const;
      virtual MeshFunction<Scalar>* clone() const;
    };

    /// Eggshell function.
    class HERMES_API ExactSolutionEggShell : public ExactSolutionScalar < double >
    {
    public:
      /// \param[in] polynomialOrder The polynomial order used for the space where the solution of the
      /// internal Laplace equation is sought.
      ExactSolutionEggShell(MeshSharedPtr mesh, int polynomialOrder);
      virtual ~ExactSolutionEggShell() {};

      /// Function returning the value.
      virtual double value(double x, double y) const;

      /// Function returning the derivatives.
      virtual void derivatives(double x, double y, double& dx, double& dy) const;

      /// Function returning the integration order that
      /// should be used when integrating the function.
      virtual Hermes::Ord ord(double x, double y) const;

      MeshFunction<double>* clone() const;
    };

    /// Function operating on previous nonlinear solutions in assembling (u_ext)
    template<typename Scalar>
    class HERMES_API UExtFunction : public Function < Scalar >
    {
    public:
      /// \param[in] polynomialOrder The polynomial order used for the space where the solution of the
      /// internal Laplace equation is sought.
      UExtFunction();
      virtual ~UExtFunction() {};

      /// Function returning the value.
      virtual void value(int n, Func<Scalar>** ext, Func<Scalar>** u_ext, Func<Scalar>* result, Geom<double>* geometry) const = 0;
      virtual void ord(Func<Hermes::Ord>** ext, Func<Hermes::Ord>** u_ext, Func<Hermes::Ord>* result) const = 0;

      virtual Func<Scalar>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);
      void free(void);
      virtual void precalculate(unsigned short order, unsigned short mask);
    };

    template<typename Scalar>
    class HERMES_API UExtFunctionSharedPtr : public std::tr1::shared_ptr < UExtFunction<Scalar> >
    {
    public:
      UExtFunctionSharedPtr(UExtFunction<Scalar>* ptr = nullptr);

      UExtFunctionSharedPtr(const UExtFunctionSharedPtr<Scalar>& other);

      void operator=(const UExtFunctionSharedPtr<Scalar>& other);
    };
  }
}
#endif
