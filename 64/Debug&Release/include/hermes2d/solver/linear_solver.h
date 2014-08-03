// This file is part of HermesCommon
//
// Copyright (c) 2009 hp-FEM group at the University of Nevada, Reno (UNR).
// Email: hpfem-group@unr.edu, home page: http://www.hpfem.org/.
//
// Hermes2D is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 2 of the License,
// or (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
/*! \file nonlinear_solver.h
\brief General nonlinear solver functionality.
*/
#ifndef __H2D_LINEAR_SOLVER_H_
#define __H2D_LINEAR_SOLVER_H_

#include "solver.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// Class for solving linear problems.<br>
    /// Typical usage:<br>
    /// // Initialize linear solver.<br>
    /// // Here wf is Hermes2D::WeakForm<double>, space is Hermes2D::Space<double><br>
    /// Hermes::Hermes2D::LinearSolver<double> linear_solver(&wf, &space);<br>
    /// <br>
    /// // Solve the linear problem.<br>
    /// try<br>
    /// {<br>
    // Just call solve().<br>
    ///&nbsp;
    ///&nbsp;linear_solver.solve();<br>
    /// <br>
    // Get the solution vector from the solver.<br>
    ///&nbsp;
    ///&nbsp;double* sln_vector = linear_solver.get_sln_vector();<br>
    /// <br>
    // Translate the solution vector into the previously initialized Solution<double> using the static method vector_to_solution.<br>
    ///&nbsp;
    ///&nbsp;Hermes::Hermes2D::Solution<double>::vector_to_solution(sln_vector, &space, &sln);<br>
    /// }<br>
    /// // All kinds of Exceptions may happen (Linear algebraic solver, some bad parameters, some data not initialized...)<br>
    /// catch(Hermes::Exceptions::Exception& e)<br>
    /// {<br>
    ///&nbsp;e.print_msg();<br>
    ///&nbsp;return -1;<br>
    /// }<br>
    /// // For illustrative purposes, otherwise one can just catch std::exception directly, as Hermes::Exceptions::Exception derive from it.<br>
    /// catch(std::exception& e)<br>
    /// {<br>
    ///&nbsp;std::cout << e.what();<br>
    ///&nbsp;return -1;<br>
    /// }<br>
    template <typename Scalar>
    class LinearSolver : public Solver<Scalar>, public Hermes::Solvers::MatrixSolver < Scalar >
    {
    public:
      LinearSolver(bool force_use_direct_solver = false);
      LinearSolver(DiscreteProblem<Scalar>* dp, bool force_use_direct_solver = false);
      LinearSolver(WeakFormSharedPtr<Scalar> wf, SpaceSharedPtr<Scalar> space, bool force_use_direct_solver = false);
      LinearSolver(WeakFormSharedPtr<Scalar> wf, std::vector<SpaceSharedPtr<Scalar> > spaces, bool force_use_direct_solver = false);
      virtual ~LinearSolver();

      // See the base class for details, the following serves only for avoiding C++ name-hiding.
      using Solver<Scalar>::solve;

      /// Basic solve method - in linear solvers it serves only as an initial guess for iterative solvers.
      /// \param[in] coeff_vec initiall guess.
      virtual void solve(Scalar* coeff_vec);

      /// Get sln vector.
      Scalar* get_sln_vector();

      /// DiscreteProblemWeakForm helper.
      virtual void set_spaces(std::vector<SpaceSharedPtr<Scalar> > spaces);

      /// DiscreteProblemWeakForm helper.
      virtual void set_weak_formulation(WeakFormSharedPtr<Scalar> wf);

      /// See Hermes::Mixins::Loggable.
      virtual void set_verbose_output(bool to_set);

    protected:
      /// State querying helpers.
      virtual bool isOkay() const;
      inline std::string getClassName() const { return "LinearSolver"; }
    };
  }
}
#endif
