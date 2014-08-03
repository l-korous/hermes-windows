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

#ifndef __H2D_QUAD_H
#define __H2D_QUAD_H

#include "../global.h"
namespace Hermes
{
  namespace Hermes2D
  {
    /// Indices of values in the value returned by Quad2D::get_points().
    enum GIP2DIndices {
      /// X-axis coordinate.
      H2D_GIP2D_X = 0,
      /// Y-axis coordinate.
      H2D_GIP2D_Y = 1,
      /// A weight.
      H2D_GIP2D_W = 2
    };

    static unsigned short H2D_GIP1D_X = 0;
    static unsigned short H2D_GIP1D_W = 1;

    // Maximum integration order for global quadrature, for quadrilaterals.
#define g_max_quad 24
    // Maximum integration order for global quadrature, for triangles.
#define g_max_tri 20

    // Maximum number of integration points.
#define H2D_MAX_INTEGRATION_POINTS_COUNT_TRI 79
#define H2D_MAX_INTEGRATION_POINTS_COUNT_QUAD 169
#define H2D_MAX_INTEGRATION_POINTS_COUNT 169

    /// Quad1D is a base class for all 1D quadrature points.
    ///
    class HERMES_API Quad1D
    {
    public:

      inline double2* get_points(int order) const { return tables[order]; }
      inline unsigned char get_num_points(int order) const { return np[order]; };

      inline unsigned short get_max_order() const { return max_order; }
      inline double get_ref_vertex(int n) const { return ref_vert[n]; }

    protected:

      double2** tables;
      unsigned char* np;

      double ref_vert[H2D_NUM_MODES];
      unsigned short max_order;

      /// to prevent this class from being instantiated
      virtual void dummy_fn() = 0;
    };

    /// Quad2D is a base class for all 2D quadrature points on triangles and quads.
    ///

    class HERMES_API Quad2D
    {
    public:
      inline unsigned char get_num_points(int order, ElementMode2D mode)  const { assert(order < num_tables[mode]); return np[mode][order]; };
      inline double3* get_points(int order, ElementMode2D mode) const { assert(order < num_tables[mode]); return tables[mode][order]; }
      inline unsigned short get_edge_points(int edge, unsigned short order, ElementMode2D mode) { assert(order < num_tables[mode]);  return  max_order[mode] + 1 + (3 * (1 - mode) + 4 * mode)*order + edge; }

      inline unsigned short get_max_order(ElementMode2D mode) const { return max_order[mode]; }
      inline unsigned short get_safe_max_order(ElementMode2D mode) const { return safe_max_order[mode]; }
      inline unsigned short get_num_tables(ElementMode2D mode) const { return num_tables[mode]; }

      inline double2* get_ref_vertex(int n, ElementMode2D mode) { return &ref_vert[mode][n]; }

      virtual unsigned char get_id() = 0;
    protected:
      double3*** tables;
      unsigned char** np;

      unsigned short num_tables[2];
      unsigned short max_order[2], safe_max_order[2];
      unsigned short max_edge_order;

      double2 ref_vert[2][H2D_MAX_NUMBER_VERTICES];
    };
  }
}
#endif