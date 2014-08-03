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

#ifndef __H2D_POSTPROCESSING_H
#define __H2D_POSTPROCESSING_H

#include "../forms.h"
#include "../function/mesh_function.h"
#include "../space/space.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// \brief Solution (mesh function) Postprocessing capabilities.
    namespace PostProcessing
    {
      template<typename Scalar>
      class HERMES_API Limiter
        : public Hermes::Mixins::TimeMeasurable,
        public Hermes::Mixins::Loggable,
        public Hermes::Hermes2D::Mixins::Parallel,
        public Hermes::Mixins::StateQueryable
      {
      public:
        Limiter(SpaceSharedPtr<Scalar> space, Scalar* solution_vector);
        Limiter(std::vector<SpaceSharedPtr<Scalar> > spaces, Scalar* solution_vector);
        virtual ~Limiter();

        /// Get the zero-th solution.
        MeshFunctionSharedPtr<Scalar> get_solution();
        /// Get all solutions.
        void get_solutions(std::vector<MeshFunctionSharedPtr<Scalar> > solutions);
        /// Get changed element ids.
        std::vector<int> get_changed_element_ids() const;

        /// Helpers for state querying.
        virtual bool isOkay() const;
        inline std::string getClassName() const { return "Limiter"; }

        /// Set the solution vector.
        void set_solution_vector(Scalar* sln);

        /// Get the solution vector.
        Scalar* get_solution_vector();

      protected:
        int component_count;
        std::vector<SpaceSharedPtr<Scalar> > spaces;
        Scalar* solution_vector;
        std::vector<MeshFunctionSharedPtr<Scalar> > limited_solutions;
        std::vector<int> changed_element_ids;

        virtual void process() = 0;

      private:
        void init(Scalar* solution_vector_);
      };

      class HERMES_API VertexBasedLimiter
        : public Limiter < double >
      {
      public:
        VertexBasedLimiter(SpaceSharedPtr<double> space, double* solution_vector, int maximum_polynomial_order);
        VertexBasedLimiter(std::vector<SpaceSharedPtr<double> > spaces, double* solution_vector, int maximum_polynomial_order);
        virtual ~VertexBasedLimiter();
        std::vector<std::pair<int, double> > get_correction_factors() const;
        void print_detailed_info(bool print_details = true);
        int maximum_polynomial_order;
        void set_p_coarsening_only();
        static bool wider_bounds_on_boundary;

      private:
        bool p_coarsening_only;

        void init(int maximum_polynomial_order);

        void process();

        void prepare_min_max_vertex_values(bool quadratic);

        /// Get mean value of the mixed derivative (mixed_derivative_index) on element e, of the "component" - component
        /// of the solution.
        double get_centroid_value_multiplied(Element* e, int component, int mixed_derivative_index);

        double get_edge_midpoint_value_multiplied(Element* e, int component, int mixed_derivative_index, int edge);

        void impose_linear_correction_factor(Element* e, int component);

        /// Return if there was a need to limit the second derivatives.
        bool impose_quadratic_correction_factor(Element* e, int component);

        double*** vertex_min_values;
        double*** vertex_max_values;
        void allocate_vertex_values();
        void deallocate_vertex_values();

        int mixed_derivatives_count;
        std::vector<std::pair<int, double> > correction_factors;
        bool print_details;
      };

      /// Integral calculator
      /// Abstract base class
      template<typename Scalar>
      class HERMES_API IntegralCalculator :
        public Hermes::Hermes2D::Mixins::Parallel,
        public Hermes::Mixins::Loggable
      {
      public:
        /// \param[in] source_functions The functions forming the integral expression.
        /// \param[in] number_of_integrals Number of results (expressions) evaluated. The method integral will get the array result allocated according to this parameter.
        ///
        IntegralCalculator(MeshFunctionSharedPtr<Scalar> source_function, int number_of_integrals);
        IntegralCalculator(std::vector<MeshFunctionSharedPtr<Scalar> > source_functions, int number_of_integrals);

        /// Main method returning the value(s).
        /// \return The values (more values at once for saving time with initialization etc.)
        virtual Scalar* calculate(std::vector<std::string> markers) = 0;

        /// Main method returning the value(s).
        /// One marker overload.
        virtual Scalar* calculate(std::string marker);

        /// The integration order calculation.
        virtual void order(Func<Hermes::Ord> **fns, Hermes::Ord* result) = 0;

      protected:
        std::vector<MeshFunctionSharedPtr<Scalar> > source_functions;
        int number_of_integrals;

        void add_results(Scalar* results_local, Scalar* results);
      };

      /// Volumetric integral calculator
      template<typename Scalar>
      class HERMES_API VolumetricIntegralCalculator : public IntegralCalculator < Scalar >
      {
      public:
        VolumetricIntegralCalculator(MeshFunctionSharedPtr<Scalar> source_function, int number_of_integrals);
        VolumetricIntegralCalculator(std::vector<MeshFunctionSharedPtr<Scalar> > source_functions, int number_of_integrals);

        /// The integral description.
        /// \param[in] n - number of integration points.
        /// \param[in] result - preallocated (see number_of_integrals in the constructor) and zeroed array for the results.
        virtual void integral(int n, double* wt, Func<Scalar> **fns, GeomVol<double> *e, Scalar* result) = 0;

        /// Main method returning the value.
        /// Not designed to be overriden.
        Scalar* calculate(std::vector<std::string> markers);
        using IntegralCalculator<Scalar>::calculate;
      };

      /// Surface integral calculator
      template<typename Scalar>
      class HERMES_API SurfaceIntegralCalculator : public IntegralCalculator < Scalar >
      {
      public:
        SurfaceIntegralCalculator(MeshFunctionSharedPtr<Scalar> source_function, int number_of_integrals);
        SurfaceIntegralCalculator(std::vector<MeshFunctionSharedPtr<Scalar> > source_functions, int number_of_integrals);

        /// The integral description.
        /// \param[in] n - number of integration points.
        /// \param[in] result - preallocated (see number_of_integrals in the constructor) and zeroed array for the results.
        virtual void integral(int n, double* wt, Func<Scalar> **fns, GeomSurf<double> *e, Scalar* result) = 0;

        /// Main method returning the value.
        /// Not designed to be overriden.
        Scalar* calculate(std::vector<std::string> markers);
        using IntegralCalculator<Scalar>::calculate;
      };
    }
  }
}

#endif
