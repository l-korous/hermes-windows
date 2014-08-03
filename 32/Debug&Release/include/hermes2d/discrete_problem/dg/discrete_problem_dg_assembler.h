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

#ifndef __H2D_DISCRETE_PROBLEM_DG_ASSEMBLER_H
#define __H2D_DISCRETE_PROBLEM_DG_ASSEMBLER_H

#include "hermes_common.h"
#include "forms.h"
#include "weakform/weakform.h"
#include "function/function.h"
#include "neighbor_search.h"
#include "refinement_selectors/selector.h"
#include "exceptions.h"
#include "mixins2d.h"
#include "multimesh_dg_neighbor_tree.h"
#include "discrete_problem/discrete_problem_selective_assembler.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// Discrete problem DG assembling class.
    ///
    /// This class provides methods for assembling DG forms (forms evaluated on internal edges) into external matrix / vector structures.
    ///
    template<typename Scalar>
    class HERMES_API DiscreteProblemDGAssembler
    {
    public:
      /// Constructor copying data from DiscreteProblemThreadAssembler.
      DiscreteProblemDGAssembler(DiscreteProblemThreadAssembler<Scalar>* threadAssembler, const std::vector<SpaceSharedPtr<Scalar> > spaces, std::vector<MeshSharedPtr>& meshes);

      /// Destructor.
      ~DiscreteProblemDGAssembler();

      /// Initialize assembling for a state.
      void init_assembling_one_state(Traverse::State* current_state_);
      /// Assemble DG forms.
      void assemble_one_state();
      /// Deinitialize assembling for a state.
      void deinit_assembling_one_state();

      static unsigned int dg_order;
    private:
      /// There is a matrix form set on DG_INNER_EDGE area or not.
      bool DG_matrix_forms_present;

      /// There is a vector form set on DG_INNER_EDGE area or not.
      bool DG_vector_forms_present;

      /// Initialize assembling for a neighbor.
      void init_assembling_one_neighbor();
      /// Assemble one DG neighbor.
      void assemble_one_neighbor(bool edge_processed, unsigned int neighbor_i, NeighborSearch<Scalar>** neighbor_searches);
      /// Deinitialize assembling for a neighbor.
      void deinit_assembling_one_neighbor();

      /// Initialize external functions for DG forms.
      DiscontinuousFunc<Scalar>** init_ext_fns(std::vector<MeshFunctionSharedPtr<Scalar> > ext,
        NeighborSearch<Scalar>** neighbor_searches, int order);

      /// Initialize neighbors.
      bool init_neighbors(NeighborSearch<Scalar>** neighbor_searches, Traverse::State* current_state);
      /// Deinitialize neighbors.
      void deinit_neighbors(NeighborSearch<Scalar>** neighbor_searches, Traverse::State* current_state);

      NeighborSearch<Scalar>*** neighbor_searches;
      unsigned int* num_neighbors;
      bool** processed;

      // Neighbor psss, refmaps.
      PrecalcShapesetAssembling ** npss;
      RefMap ** nrefmaps;

      PrecalcShapesetAssembling** pss;
      RefMap** refmaps;
      Solution<Scalar>** u_ext;
      AsmList<Scalar>* als;
      std::vector<Transformable *> fns;
      WeakFormSharedPtr<Scalar> wf;
      int spaces_size;
      bool nonlinear;
      DiscreteProblemSelectiveAssembler<Scalar>* selectiveAssembler;

      SparseMatrix<Scalar>* current_mat;
      Vector<Scalar>* current_rhs;

      Traverse::State* current_state;
      /// Current local matrix.
      Scalar local_stiffness_matrix[H2D_MAX_LOCAL_BASIS_SIZE * H2D_MAX_LOCAL_BASIS_SIZE * 4];

      const std::vector<SpaceSharedPtr<Scalar> > spaces;
      const std::vector<MeshSharedPtr>& meshes;

      template<typename T> friend class DiscreteProblem;
      template<typename T> friend class DiscreteProblemIntegrationOrderCalculator;

      /// Finds the correct NeighborSearch.
      static NeighborSearch<Scalar>* get_neighbor_search_ext(WeakFormSharedPtr<Scalar> wf, NeighborSearch<Scalar>** neighbor_searches, int index);

#ifdef DEBUG_DG_ASSEMBLING
      void debug();
#endif
    };
  }
}
#endif