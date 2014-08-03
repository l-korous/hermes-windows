// This file is part of Hermes2D.
//
// Hermes2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef __H2D_FILTER_H
#define __H2D_FILTER_H

#include "solution.h"
#include <complex>

namespace Hermes
{
  namespace Hermes2D
  {
    struct UniData;

    /// Filter is a general postprocessing class, intended for visualization.
    /// The output of Filter is an arbitrary combination of up to three input functions,
    /// which usually are Solutions to PDEs, but can also be other Filters.
    ///
    /// (This class cannot be instantiated.)
    ///
    template<typename Scalar>
    class HERMES_API Filter : public MeshFunction < Scalar >
    {
    public:
      Filter();
      Filter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions);

      virtual ~Filter();

      virtual void reinit();

      inline SpaceType get_space_type() const { return space_type; };

      /// State querying helpers.
      inline std::string getClassName() const { return "Filter"; }

    protected:
      virtual void set_quad_2d(Quad2D* quad_2d);

      virtual void set_active_element(Element* e);

      virtual void free();

      virtual void push_transform(int son);

      virtual void pop_transform();

      virtual void init();

      std::vector<MeshFunctionSharedPtr<Scalar> > solutions;

      std::vector<uint64_t> solutions_sub_idx;

      bool unimesh;

      SpaceType space_type;

      UniData** unidata;

      void copy_base(Filter* flt);
    };

    /// SimpleFilter is a base class for predefined simple filters (MagFilter, DiffFilter...).
    /// The 'simplicity' lies in the fact that only one value per input function can be
    /// combined (e.g., not a value and a derivative). If this is not sufficient, a full-fledged
    /// filter must be derived from the Filter class (see VonMisesFilter). SimpleFilter is also
    /// intended for the user to be able to easily create custom filters only by supplying the
    /// combining function.
    ///
    /// The user specifies the combining function, the arguments ('sln1', 'sln2', 'sln3'), and
    /// optionally the 'item' for each argument, which can be any of H2D_FN_VAL_0, H2D_FN_DX_0, H2D_FN_DY_0
    /// etc.
    ///
    /// SimpleFilter is vector-valued, if at least one input function is vector-valued and
    /// both components are specified in 'item', e.g., item1 = H2D_FN_DX (which is H2D_FN_DX_0 | H2D_FN_DX_1).
    /// Otherwise it is Scalar-valued.
    ///
    template<typename Scalar>
    class HERMES_API SimpleFilter : public Filter < Scalar >
    {
    public:
      SimpleFilter();
      virtual ~SimpleFilter();

      SimpleFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions, std::vector<int> items = std::vector<int>());

      virtual Func<Scalar>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);

    protected:
      std::vector<int> items;

      virtual void filter_fn(int n, const std::vector<const Scalar*>& values, Scalar* result) = 0;

      void init_components();
      virtual void precalculate(unsigned short order, unsigned short mask);
    };

    /// ComplexFilter is used to transform complex solutions into its real parts.
    ///
    class HERMES_API ComplexFilter : public Filter < double >
    {
    public:
      ComplexFilter();
      ComplexFilter(MeshFunctionSharedPtr<std::complex<double> > solution, int item = H2D_FN_VAL_0);

      virtual ~ComplexFilter();
    protected:
      virtual Func<double>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);

      virtual void set_quad_2d(Quad2D* quad_2d);

      virtual void set_active_element(Element* e);

      virtual void push_transform(int son);

      virtual void pop_transform();

      virtual void free();

      MeshFunctionSharedPtr<std::complex<double> > sln_complex;

      int item;

      virtual void filter_fn(int n, const std::complex<double>* values, double* result) = 0;

      virtual void precalculate(unsigned short order, unsigned short mask);
    };

    /// DXDYFilter is a more advanced version of SimpleFilter. It allows combining derivatives
    /// of the inputs and also, unlike SimpleFilter, it defines derivatives of the filtered
    /// result. The user-supplied combining function has a different format: it takes and must
    /// return also the DX and DY values.
    ///
    template<typename Scalar>
    class HERMES_API DXDYFilter : public Filter < Scalar >
    {
    public:
      // one result (rslt), all inputs and result including derivatives
      DXDYFilter();

      DXDYFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions);

      virtual ~DXDYFilter();
    protected:
      void init(std::vector<MeshFunctionSharedPtr<Scalar> > solutions);

      virtual Func<Scalar>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);

      virtual void filter_fn(int n, double* x, double* y, const std::vector<const Scalar *>& values, const std::vector<const Scalar *>& dx, const std::vector<const Scalar *>& dy, Scalar* rslt, Scalar* rslt_dx, Scalar* rslt_dy) = 0;

      void init_components();

      virtual void precalculate(unsigned short order, unsigned short mask);
    };

    /// MagFilter takes two functions representing the components of a vector function and
    /// calculates the vector magnitude, sqrt(x^2 + y^2).
    /// \brief Calculates the magnitude of a vector function.
    template<typename Scalar>
    class HERMES_API MagFilter : public SimpleFilter < Scalar >
    {
    public:
      MagFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions, std::vector<int> items = std::vector<int>());

      /// for vector-valued sln1
      MagFilter(MeshFunctionSharedPtr<Scalar> sln1, int item1 = H2D_FN_VAL);
      virtual MeshFunction<Scalar>* clone() const;

      virtual ~MagFilter();
    protected:
      virtual void filter_fn(int n, const std::vector<const Scalar*>& values, Scalar* result);
    };

    /// TopValFilter takes functions and puts a threshold on their highest values.
    class HERMES_API TopValFilter : public SimpleFilter < double >
    {
    public:
      TopValFilter(std::vector<MeshFunctionSharedPtr<double> > solutions, std::vector<double> limits, std::vector<int> items = *(new std::vector<int>));

      /// for vector-valued sln1
      TopValFilter(MeshFunctionSharedPtr<double> sln, double limit, int item = H2D_FN_VAL_0);
      virtual MeshFunction<double>* clone() const;

      virtual ~TopValFilter();
    protected:
      virtual void filter_fn(int n, const std::vector<const double*>& values, double* result);
      std::vector<double> limits;
    };

    /// BottomValFilter takes functions and puts a threshold on their lowest values.
    class HERMES_API BottomValFilter : public SimpleFilter < double >
    {
    public:
      BottomValFilter(std::vector<MeshFunctionSharedPtr<double> > solutions, std::vector<double> limits, std::vector<int> items = *(new std::vector<int>));

      /// for vector-valued sln1
      BottomValFilter(MeshFunctionSharedPtr<double> sln, double limit, int item = H2D_FN_VAL_0);
      virtual MeshFunction<double>* clone() const;

      virtual ~BottomValFilter();
    protected:
      virtual void filter_fn(int n, const std::vector<const double*>& values, double* result);
      std::vector<double> limits;
    };

    /// ValFilter takes functions and puts a threshold on their lowest AND highest values.
    class HERMES_API ValFilter : public SimpleFilter < double >
    {
    public:
      ValFilter(std::vector<MeshFunctionSharedPtr<double> > solutions, std::vector<double> low_limits, std::vector<double> high_limits, std::vector<int> items = *(new std::vector<int>));

      /// for vector-valued sln1
      ValFilter(MeshFunctionSharedPtr<double> sln, double low_limit, double high_limit, int item = H2D_FN_VAL_0);
      virtual MeshFunction<double>* clone() const;

      virtual ~ValFilter();
    protected:
      virtual void filter_fn(int n, const std::vector<const double*>& values, double* result);
      std::vector<double> low_limits;
      std::vector<double> high_limits;
    };

    /// Calculates the difference of two functions.
    template<typename Scalar>
    class HERMES_API DiffFilter : public SimpleFilter < Scalar >
    {
    public:
      DiffFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions, std::vector<int> items = *(new std::vector<int>));
      virtual MeshFunction<Scalar>* clone() const;
      virtual ~DiffFilter();

    protected:
      virtual void filter_fn(int n, const std::vector<const Scalar*>& values, Scalar* result);
    };

    /// Calculates the sum of two functions.
    template<typename Scalar>
    class HERMES_API SumFilter : public SimpleFilter < Scalar >
    {
    public:
      SumFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions, std::vector<int> items = *(new std::vector<int>));
      virtual MeshFunction<Scalar>* clone() const;
      virtual ~SumFilter();

    protected:
      virtual void filter_fn(int n, const std::vector<const Scalar*>& values, Scalar* result);
    };

    /// Calculates the square of a function.
    template<typename Scalar>
    class HERMES_API SquareFilter : public SimpleFilter < Scalar >
    {
    public:
      SquareFilter(std::vector<MeshFunctionSharedPtr<Scalar> > solutions, std::vector<int> items = *(new std::vector<int>));
      virtual MeshFunction<Scalar>* clone() const;
      virtual ~SquareFilter();

    protected:
      virtual void filter_fn(int n, const std::vector<const Scalar*>& values, Scalar* result);
    };

    /// Calculates absolute value of a real solution.
    class HERMES_API AbsFilter : public SimpleFilter < double >
    {
    public:
      AbsFilter(std::vector<MeshFunctionSharedPtr<double> > solutions, std::vector<int> items = *(new std::vector<int>));
      AbsFilter(MeshFunctionSharedPtr<double> solution);
      virtual MeshFunction<double>* clone() const;
      virtual ~AbsFilter();

    protected:
      virtual void filter_fn(int n, const std::vector<const double*>& values, double* result);
    };

    /// Removes the imaginary part from a function.
    class HERMES_API RealFilter : public ComplexFilter
    {
    public:
      RealFilter();
      RealFilter(MeshFunctionSharedPtr<std::complex<double> > solution, int item = H2D_FN_VAL_0);
      virtual ~RealFilter();

      virtual MeshFunction<double>* clone() const;

    protected:
      virtual void filter_fn(int n, const std::complex<double>* values, double* result);
    };

    /// ImagFilter puts the imaginary part of the input function to the Real part of the
    /// output, allowing it to be visualized.
    class HERMES_API ImagFilter : public ComplexFilter
    {
    public:
      ImagFilter(MeshFunctionSharedPtr<std::complex<double> > solution, int item = H2D_FN_VAL_0);
      virtual ~ImagFilter();

      virtual MeshFunction<double>* clone() const;
    protected:
      virtual void filter_fn(int n, const std::complex<double>* values, double* result);
    };

    /// Computes the absolute value of a complex solution.
    class HERMES_API ComplexAbsFilter : public ComplexFilter
    {
    public:
      ComplexAbsFilter(MeshFunctionSharedPtr<std::complex<double> > solution, int item = H2D_FN_VAL_0);
      virtual ~ComplexAbsFilter();

      virtual MeshFunction<double>* clone() const;

    protected:
      virtual void filter_fn(int n, const std::complex<double>* values, double* result);
    };

    /// Computes the angle of a complex solution.
    class HERMES_API AngleFilter : public SimpleFilter < std::complex<double> >
    {
    public:
      AngleFilter(std::vector<MeshFunctionSharedPtr<std::complex<double> > > solutions, std::vector<int> items = *(new std::vector<int>));
      virtual ~AngleFilter();

    protected:
      virtual void filter_fn(int n, const std::vector<const std::complex<double>*>& values, double* result);
    };

    /// VonMisesFilter is a postprocessing filter for visualizing elastic stresses in a body.
    /// It calculates the stress tensor and applies the Von Mises equivalent stress formula
    /// to obtain the resulting stress measure.
    /// \brief Calculates the Von Mises stress.
    class HERMES_API VonMisesFilter : public Filter < double >
    {
    public: /// \todo cylindrical coordinates

      VonMisesFilter(std::vector<MeshFunctionSharedPtr<double> > solutions, double lambda, double mu,
        int cyl = 0, int item1 = H2D_FN_VAL, int item2 = H2D_FN_VAL);

      virtual Func<double>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);

      virtual MeshFunction<double>* clone() const;
      virtual ~VonMisesFilter();

    protected:
      double lambda, mu;

      int cyl, item1, item2;

      virtual void precalculate(unsigned short order, unsigned short mask);
    };

    /// Linearization filter for use in nonlinear problems. From one or two previous
    /// solution values it extrapolates an estimate of the new_ one.
    /// With adaptive time step: tau_frac = tau_new_ / tau_old
    template<typename Scalar>
    class HERMES_API LinearFilter : public Filter < Scalar >
    {
    public:
      LinearFilter(MeshFunctionSharedPtr<Scalar> old);

      LinearFilter(MeshFunctionSharedPtr<Scalar> older, MeshFunctionSharedPtr<Scalar> old, double tau_frac = 1);

      virtual Func<Scalar>* get_pt_value(double x, double y, bool use_MeshHashGrid = false, Element* e = nullptr);
      virtual MeshFunction<Scalar>* clone() const;
      virtual ~LinearFilter();

    protected:
      double tau_frac;

      virtual void precalculate(unsigned short order, unsigned short mask);

      void init_components();

      virtual void set_active_element(Element* e);
    };
  }
}
#endif
