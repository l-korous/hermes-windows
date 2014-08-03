// This file is part of Hermes2D
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
/*! \file solver_picard.h
\brief Picard's method.
*/
#ifndef __H2D_SOLVER_PICARD_H_
#define __H2D_SOLVER_PICARD_H_

#include "solvers/picard_matrix_solver.h"
#include "solver.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// Class for the Picard's method.<br>
    /// For details about the optionally applied Anderson acceleration, the following website<br>
    /// http://www.hpfem.org/hermes/hermes-tutorial/doc/_build/html/src/hermes2d/B-nonlinear/01-picard.html
    /// will give an overview.<br>
    /// Typical usage:<br>
    /// // Initialize Picard's solver.<br>
    /// // Here wf is Hermes2D::WeakForm<std::complex<double> >, space is Hermes2D::Space<std::complex<double> ><br>
    /// Hermes::Hermes2D::PicardSolver<std::complex<double> > picard_solver(&wf, &space);<br>
    /// <br>
    /// // Here we have an initial guess for the Picard's method - let us say that we already have a previous time level solution<br>
    /// Solution<std::complex<double> > prevTimeLevelSolution;<br>
    /// <br>
    /// ..... // Here we fill prevTimeLevelSolution.<br>
    /// <br>
    /// // Solve the linear problem.<br>
    /// try<br>
    /// {<br>
    // Call solve with the initial guess.<br>
    ///&nbsp;
    ///&nbsp;picard_solver.solve(&prevTimeLevelSolution);<br>
    /// <br>
    // Get the solution vector from the solver.<br>
    ///&nbsp;
    ///&nbsp;std::complex<double> * sln_vector = picard_solver.get_sln_vector();<br>
    /// <br>
    // Translate the solution vector into the previously initialized Solution<std::complex<double> > using the static method vector_to_solution.<br>
    ///&nbsp;
    ///&nbsp;Hermes::Hermes2D::Solution<std::complex<double> >::vector_to_solution(sln_vector, &space, &sln);<br>
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
    template<typename Scalar>
    class HERMES_API PicardSolver :
      public Hermes::Hermes2D::Solver<Scalar>,
      public Hermes::Solvers::PicardMatrixSolver < Scalar >
    {
    public:
      PicardSolver();
      PicardSolver(DiscreteProblem<Scalar>* dp);
      PicardSolver(WeakFormSharedPtr<Scalar> wf, SpaceSharedPtr<Scalar> space);
      PicardSolver(WeakFormSharedPtr<Scalar> wf, std::vector<SpaceSharedPtr<Scalar> > spaces);
      virtual ~PicardSolver();

      // See the base class for details, the following serves only for avoiding C++ name-hiding.
      using Solver<Scalar>::solve;

      /// Basic solve method - in linear solvers it serves only as an initial guess for iterative solvers.
      /// \param[in] coeff_vec initiall guess.
      virtual void solve(Scalar* coeff_vec);

      /// Get sln vector.
      Scalar* get_sln_vector();

      /// DiscreteProblemWeakForm helper.
      virtual void set_spaces(std::vector<SpaceSharedPtr<Scalar> > spaces);

      /// See Hermes::Mixins::Loggable.
      virtual void set_verbose_output(bool to_set);

      /// DiscreteProblemWeakForm helper.
      virtual void set_weak_formulation(WeakFormSharedPtr<Scalar> wf);

      virtual void assemble_residual(bool store_previous_residual);
      virtual bool assemble_jacobian(bool store_previous_jacobian);
      virtual bool assemble(bool store_previous_jacobian, bool store_previous_residual);

      /// Initialization - called at the beginning of solving.
      virtual void init_solving(Scalar* coeff_vec);

      /// State querying helpers.
      virtual bool isOkay() const;
      inline std::string getClassName() const { return "PicardSolver"; }
    };
  }
}
#endif