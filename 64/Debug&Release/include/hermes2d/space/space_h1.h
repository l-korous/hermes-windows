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

#ifndef __H2D_SPACE_H1_H
#define __H2D_SPACE_H1_H

#include "../shapeset/shapeset_h1_all.h"
#include "space.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// H1Space represents a space of continuous Scalar functions over a domain (mesh).<br>
    /// Typical usage:<br>
    /// ...<br>
    /// Hermes::Hermes2D::EssentialBCs<double> bcs(&bc_essential1, &bc_essential2, ...);<br>
    /// <br>
    /// // Initialize space.<br>
    /// int globalPolynomialOrder = 4;<br>
    /// SpaceSharedPtr<double> space(&mesh, &bcs, globalPolynomialOrder);<br>
    template<typename Scalar>
    class HERMES_API H1Space : public Space < Scalar >
    {
    public:
      H1Space();
      H1Space(MeshSharedPtr mesh, EssentialBCs<Scalar>* boundary_conditions, int p_init = 1,
        Shapeset* shapeset = nullptr);

      H1Space(MeshSharedPtr mesh, int p_init = 1,
        Shapeset* shapeset = nullptr);

      virtual ~H1Space();

      virtual void set_shapeset(Shapeset* shapeset, bool clone = false);

      virtual Scalar* get_bc_projection(SurfPos* surf_pos, int order, EssentialBoundaryCondition<Scalar> *bc);

      /// Copy from Space instance 'space'
      virtual void copy(SpaceSharedPtr<Scalar> space, MeshSharedPtr new_mesh);

    protected:

      virtual SpaceType get_type() const { return HERMES_H1_SPACE; }

      /// Common code for the constructors.
      void init(Shapeset* shapeset, int p_init, bool assign_dofs_init = true);

      virtual void assign_vertex_dofs();
      virtual void assign_edge_dofs();
      virtual void assign_bubble_dofs();

      virtual void get_vertex_assembly_list(Element* e, int iv, AsmList<Scalar>* al) const;
      virtual void get_boundary_assembly_list_internal(Element* e, int ie, AsmList<Scalar>* al) const;

      inline void output_component(typename Space<Scalar>::BaseComponent*& current, typename Space<Scalar>::BaseComponent*& last, typename Space<Scalar>::BaseComponent* min,
        Node*& edge, typename Space<Scalar>::BaseComponent*& edge_dofs);

      typename Space<Scalar>::BaseComponent* merge_baselists(typename Space<Scalar>::BaseComponent* l1, int n1, typename Space<Scalar>::BaseComponent* l2, int n2,
        Node* edge, typename Space<Scalar>::BaseComponent*& edge_dofs, int& ncomponents);

      void update_constrained_nodes(Element* e, typename Space<Scalar>::EdgeInfo* ei0, typename Space<Scalar>::EdgeInfo* ei1, typename Space<Scalar>::EdgeInfo* ei2, typename Space<Scalar>::EdgeInfo* ei3);

      virtual void update_constraints();
    };
  }
}
#endif
