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

#ifndef __H2D_OGPROJECTION_H
#define __H2D_OGPROJECTION_H

#include "../function/solution.h"
#include "../forms.h"
#include "../weakform/weakform.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// \brief Class for (global) orthogonal projecting. If the projection is not necessary (if a solution belongs to the space), then its solution vector is used.
    template<typename Scalar>
    class HERMES_API OGProjection : public Hermes::Mixins::Loggable
    {
    public:
      /// This method allows to specify your own OG-projection form.
      static void project_global(SpaceSharedPtr<Scalar> space,
        MatrixFormVol<Scalar>* custom_projection_jacobian,
        VectorFormVol<Scalar>* custom_projection_residual,
        Scalar* target_vec);

      /// Wrapper that delivers a Solution instead of a coefficient vector.
      static void project_global(SpaceSharedPtr<Scalar> space,
        MatrixFormVol<Scalar>* custom_projection_jacobian,
        VectorFormVol<Scalar>* custom_projection_residual,
        MeshFunctionSharedPtr<Scalar> target_sln);

      /// This method allows to specify your own multiple OG-projection forms.
      static void project_global(const std::vector<SpaceSharedPtr<Scalar> > spaces,
        const std::vector<MatrixFormVol<Scalar>*>& custom_projection_jacobian,
        const std::vector<VectorFormVol<Scalar>*>& custom_projection_residual,
        Scalar* target_vec);

      /// Wrapper that delivers a vector of Solutions instead of a coefficient vector.
      static void project_global(const std::vector<SpaceSharedPtr<Scalar> > spaces,
        const std::vector<MatrixFormVol<Scalar>*>& custom_projection_jacobian,
        const std::vector<VectorFormVol<Scalar>*>& custom_projection_residual,
        const std::vector<MeshFunctionSharedPtr<Scalar> >& target_slns);

      /**
      \fn  static void OGProjection::project_global(SpaceSharedPtr<Scalar> space,
      MeshFunction<Scalar>* source_meshfn, Scalar* target_vec,
      NormType proj_norm = HERMES_UNSET_NORM, double newton_tol = 1e-6, int newton_max_iter = 10);

      \brief The method checks source_meshfn if it is an instance of Solution, if so, it checks its sln_vector, and space_seq
      if they can be used directly.

      \param[in]  space         If non-null, the space.
      \param[in]  source_meshfn If non-null, source meshfn.
      \param[out]  target_vec    If non-null, target vector.
      \param matrix_solver           (optional) the matrix solver.
      \param proj_norm               (optional) the project normalise.
      \param newton_tol              (optional) the newton tolerance.
      \param newton_max_iter         (optional) the newton maximum iterator.
      */
      static void project_global(SpaceSharedPtr<Scalar> space, MeshFunctionSharedPtr<Scalar> source_meshfn,
        Scalar* target_vec, NormType proj_norm = HERMES_UNSET_NORM);

      static void project_global(SpaceSharedPtr<Scalar> space, MeshFunctionSharedPtr<Scalar> source_meshfn,
        Hermes::Algebra::Vector<Scalar>* target_vec, NormType proj_norm = HERMES_UNSET_NORM);

      /// Wrapper that delivers a Solution instead of coefficient vector.
      static void project_global(SpaceSharedPtr<Scalar> space,
        MeshFunctionSharedPtr<Scalar> source_sln, MeshFunctionSharedPtr<Scalar>  target_sln,
        NormType proj_norm = HERMES_UNSET_NORM);

      /// Wrapper for multiple source MeshFunctions that delivers coefficient vector.
      static void project_global(std::vector<SpaceSharedPtr<Scalar> > spaces, std::vector<MeshFunctionSharedPtr<Scalar> > source_meshfns,
        Scalar* target_vec, std::vector<NormType> proj_norms = std::vector<NormType>());

      static void project_global(std::vector<SpaceSharedPtr<Scalar> > spaces, std::vector<MeshFunctionSharedPtr<Scalar> > source_meshfns,
        Hermes::Algebra::Vector<Scalar>* target_vec, std::vector<NormType> proj_norms = std::vector<NormType>());

      static void project_global(std::vector<SpaceSharedPtr<Scalar> > spaces,
        std::vector<MeshFunctionSharedPtr<Scalar> > source_slns, std::vector<MeshFunctionSharedPtr<Scalar> > target_slns,
        std::vector<NormType> proj_norms = std::vector<NormType>(), bool delete_old_mesh = false);

    protected:
      /// Underlying function for global orthogonal projection.
      /// Not intended for the user. NOTE: the weak form here must be
      /// a special projection weak form, which is different from
      /// the weak form of the PDE. If you supply a weak form of the
      /// PDE, the PDE will just be solved.
      static void project_internal(SpaceSharedPtr<Scalar> space, WeakFormSharedPtr<Scalar> proj_wf, Scalar* target_vec);
    };
  }
}
#endif
