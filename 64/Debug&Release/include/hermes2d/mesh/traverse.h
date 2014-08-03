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

#ifndef __H2D_TRAVERSE_H
#define __H2D_TRAVERSE_H

#include "hermes_common.h"
#include "mesh.h"

namespace Hermes
{
  namespace Hermes2D
  {
    /// \brief Determines the position on an element surface (edge in 2D and Face in 3D).
    /// \details Used for the retrieval of boundary condition values.
    /// \details Same in H2D and H3D.
    ///
    struct SurfPos
    {
      /// surface marker (surface = edge in 2D and face in 3D)
      int marker;
      /// local element surface number
      int surf_num;

      /// for internal use
      Element *base;

      /// H2D only: edge endpoint vertex id numbers
      int v1, v2;
      /// H2D only: position between v1 and v2 in the range[0..1]
      double t;
      /// H2D only: for internal use
      double lo, hi;
    };

    class Mesh;
    class Transformable;
    struct Rect;

    struct UniData
    {
      Element* e;
      uint64_t idx;
    };

    static const uint64_t ONE = (uint64_t)1 << 63;

    struct Rect
    {
      uint64_t l, b, r, t;
    };

    /// Traverse is a multi-mesh traversal utility class. Given N meshes sharing the
    /// same base mesh it walks through all (pseudo-)elements of the union of all
    /// the N meshes.
    ///
    class HERMES_API Traverse : public Hermes::Mixins::Loggable
    {
    public:
      Traverse(int spaces_size);
      class State
      {
      public:
        Element** e;
        uint64_t* sub_idx;
        bool bnd[H2D_MAX_NUMBER_EDGES];
        bool isBnd;
        unsigned char isurf;
        Element* rep;
        unsigned short rep_i;
        ~State();
        unsigned short num;
        static State* clone(const State * other);
      private:
        State();
        //void operator=(const State * other);
        void push_transform(unsigned char son, unsigned char i, bool is_triangle = false);
        bool is_triangle();
        uint64_t get_transform(unsigned char i);
        bool visited;
        Rect  cr;
        Rect* er;
        friend class Traverse;
        template<typename Scalar> friend class DiscreteProblem;
        template<typename T> friend class DiscreteProblemDGAssembler;
        template<typename T> friend class DiscreteProblemThreadAssembler;
      };

      /// Returns all states on the passed meshes.
      /// \param[in] meshes Meshes.
      /// \param[out] num Number of states.
      /// \return The states.
      State** get_states(std::vector<MeshSharedPtr> meshes, unsigned int& states_count);
      State** get_states(MeshSharedPtr* meshes, unsigned short meshes_count, unsigned int& states_count);

      /// Returns all states on the passed meshes.
      /// Overload for mesh functions.
      template<typename Scalar>
      State** get_states(std::vector<MeshFunctionSharedPtr<Scalar> > mesh_functions, unsigned int& states_count);

    private:
      /// Used by get_states.
      void begin(int n);
      /// Used by get_states.
      void finish();
      /// Used by get_states.
      void init_transforms(State* s, unsigned char i);

#pragma region union-mesh
      static UniData** construct_union_mesh(unsigned char n, MeshSharedPtr* meshes, MeshSharedPtr unimesh);
      void union_recurrent(Rect* cr, Element** e, Rect* er, uint64_t* idx, Element* uni);
      uint64_t init_idx(Rect* cr, Rect* er);

      UniData** unidata;
      int udsize;
#pragma endregion

      /// Internal.
      unsigned short num;
      /// Internal.
      State* stack;
      /// Internal.
      int top, size;

      /// Internal.
      State* push_state(int* top_by_ref = nullptr);
      /// Internal.
      void set_boundary_info(State* s);
      /// Internal.
      void free_state(State* state);
      /// Internal.
      unsigned char spaces_size;

      MeshSharedPtr unimesh;
      template<typename T> friend class Adapt;
      template<typename T> friend class KellyTypeAdapt;
      template<typename T> friend class DiscreteProblem;
      template<typename T> friend class DiscreteProblemDGAssembler;
      template<typename T> friend class DiscreteProblemIntegrationOrderCalculator;
      template<typename T> friend class Filter;
      template<typename T> friend class SimpleFilter;
      friend class Views::Orderizer;
    };
  }
}
#endif