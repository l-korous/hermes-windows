/// This file is part of Hermes2D.
///
/// Hermes2D is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 2 of the License, or
/// (at your option) any later version.
///
/// Hermes2D is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY;without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with Hermes2D. If not, see <http:///www.gnu.org/licenses/>.

#ifndef __H2D_DISCRETE_PROBLEM_HELPERS_H
#define __H2D_DISCRETE_PROBLEM_HELPERS_H

#include "hermes_common.h"
#include "weakform/weakform.h"

namespace Hermes
{
  namespace Hermes2D
  {
    namespace Mixins
    {
      template<typename Scalar>
      class HERMES_API DiscreteProblemRungeKutta
      {
      protected:
        /// Constructor for multiple components / equations.
        DiscreteProblemRungeKutta();

        /// Set the special handling of external functions of Runge-Kutta methods, including information how many spaces were there in the original problem.
        virtual void set_RK(int original_spaces_count, bool force_diagonal_blocks = nullptr, Table* block_weights = nullptr);

        /// Turn on Runge-Kutta specific handling of external functions.
        bool rungeKutta;

        /// Number of spaces in the original problem in a Runge-Kutta method.
        int RK_original_spaces_count;

        bool force_diagonal_blocks;

        Table* block_weights;

        // Return scaling coefficient.
        double block_scaling_coeff(MatrixForm<Scalar>* form) const;
        double block_scaling_coeff(MatrixFormDG<Scalar>* form) const;
      };

      template<typename Scalar>
      class HERMES_API DiscreteProblemWeakForm
      {
      public:
        WeakFormSharedPtr<Scalar> get_weak_formulation() const;

      protected:
        DiscreteProblemWeakForm(WeakFormSharedPtr<Scalar> wf = WeakFormSharedPtr<Scalar>(nullptr));

        virtual void set_weak_formulation(WeakFormSharedPtr<Scalar> wf);

        /// Weak formulation.
        WeakFormSharedPtr<Scalar> wf;
      };

      template<typename Scalar>
      class HERMES_API DiscreteProblemMatrixVector
      {
      protected:
        DiscreteProblemMatrixVector();

        virtual bool set_matrix(SparseMatrix<Scalar>* mat);
        virtual bool set_rhs(Vector<Scalar>* rhs);

        SparseMatrix<Scalar>* current_mat;
        Vector<Scalar>* current_rhs;
      };
    }

    /// \ingroup Helper methods inside {calc_order_*, assemble_*}
    /// Init geometry, jacobian * weights, return the number of integration points.
    HERMES_API unsigned char init_geometry_points_allocated(RefMap** reference_mapping, unsigned short reference_mapping_count, int order, GeomVol<double>& geometry, double* jacobian_x_weights);
    HERMES_API unsigned char init_geometry_points_allocated(RefMap* rep_reference_mapping, int order, GeomVol<double>& geometry, double* jacobian_x_weights);
    HERMES_API unsigned char init_surface_geometry_points_allocated(RefMap** reference_mapping, unsigned short reference_mapping_count, int& order, unsigned char isurf, int marker, GeomSurf<double>& geometry, double* jacobian_x_weights);
    HERMES_API unsigned char init_surface_geometry_points_allocated(RefMap* rep_reference_mapping, int& order, unsigned char isurf, int marker, GeomSurf<double>& geometry, double* jacobian_x_weights);
  }
}
#endif
