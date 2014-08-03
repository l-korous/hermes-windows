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

#ifndef __H2D_ORDER_H
#define __H2D_ORDER_H

#include "../global.h"
#include "../mesh/mesh.h"
namespace Hermes
{
  namespace Hermes2D
  {
    class HERMES_API EncodedOrder
    {
    public:
      EncodedOrder();
      EncodedOrder(int encoded_order);
      EncodedOrder(int horizontal_order, int vertical_order);
      int get_encoded_order(ElementMode2D mode) const;
      int get_horizontal_order() const;
      int get_vertical_order() const;

      /// Returns a (non-encoded, one-dimensional) order on an edge.
      int get_edge_order(ElementMode2D mode, int edge) const;
      
      /// Sets encoded_order in both dimensions.
      /// \param[in] encoded_order EncodedOrder to be set.
      void set_encoded_order(int encoded_order);

      /// Sets encoded_order in both dimensions.
      /// \param[in] encoded_order EncodedOrder encoded using H2D_MAKE_QUAD_ORDER.
      void set_quad_encoded_order(int encoded_order);
      
      void set_encoded_order(int horizontal_order, int vertical_order);
      void set_horizontal_order(int encoded_order);
      void set_vertical_order(int encoded_order);
      void change_encoded_order(int change);
      void change_encoded_order(int change_horizontal, int change_vertical);
      void change_horizontal_order(int change);
      void change_vertical_order(int change);

      /// Static method that return quad encoded_order with encoded_order_1d in both dimensions.
      static int get_quad_encoded_order(int encoded_order_1d);
      static int get_quad_encoded_order(int horizontal_order, int vertical_order);
      /// Returns appropriate edge encoded_order. The encoded_order coming is combined horizontal/vertical encoded_order.
      /// \param[in] encoded_order combined horizontal/vertical encoded_order.
      static int get_edge_encoded_order(ElementMode2D mode, int edge, int encoded_order);
    private:
      int horizontal_order, vertical_order;
    };
  }
}
#endif