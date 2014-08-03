// This file is part of Hermes2D.
//
// Hermes2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHout ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __H2D_VERTEX_BASED_INTERPOLATION_H
#define __H2D_VERTEX_BASED_INTERPOLATION_H

#include "function/solution.h"
#include "space/space.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// @ingroup projections
    /// \brief Class for vertex based interpolation.
    template<typename Scalar>
    class HERMES_API VertexBasedInterpolation
    {
    public:
      /// This method allows to specify your own OG-projection form.
      static void interpolate(SpaceSharedPtr<Scalar> src_space, Scalar* src_sln_vector, SpaceSharedPtr<Scalar> out_space, Scalar*& out_sln_vector, bool include_dirichlet = true);
    };

    /// @ingroup projections
    /// \brief Class for p-multigrid interpolation.
    template<typename Scalar>
    class HERMES_API pMultigridInterpolation
    {
    public:
      /// This method allows to specify your own OG-projection form.
      static void interpolate(SpaceSharedPtr<Scalar> src_space, Scalar* src_sln_vector, SpaceSharedPtr<Scalar> out_space, Scalar*& out_sln_vector, bool include_dirichlet = true);
    };
  }
}
#endif
