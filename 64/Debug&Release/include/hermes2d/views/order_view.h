// This file is part of Hermes2D.
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

// $Id: view.h 1086 2008-10-21 09:05:44Z jakub $

#ifndef __H2D_ORDER_VIEW_H
#define __H2D_ORDER_VIEW_H
#include "view.h"

namespace Hermes
{
  namespace Hermes2D
  {
    namespace Views
    {
      // you can define NOGLUT to turn off all OpenGL stuff in Hermes2D
#ifndef NOGLUT
      /// Maximum viewable order.
      static const int H2DV_MAX_VIEWABLE_ORDER = 10;

      /// \brief Displays the polynomial degrees of elements.
      ///
      /// OrderView is a tool for displaying the polynomial degrees of the elements in a space.
      ///
      class HERMES_API OrderView : public View
      {
      public:

        OrderView(const char* title = "OrderView", WinGeom* wg = nullptr);
        // #ifndef _MSC_VER
        //  OrderView(const char* title = "OrderView", WinGeom* wg = nullptr);
        // #endif
        OrderView(char* title, WinGeom* wg = nullptr);

        template<typename Scalar>
        void show(SpaceSharedPtr<Scalar> space, bool show_edge_orders = false);
        void set_b_orders(bool set);
      protected:

        Orderizer ord;
        bool b_orders;

        int num_boxes, order_min;
        /// Pointers to order names. Pointers point inside OrderView::text_buffer.
        const char* box_names[H2DV_MAX_VIEWABLE_ORDER + 1];
        /// Text buffer which contains all order names.
        char text_buffer[H2DV_MAX_VIEWABLE_ORDER * 4];
        /// Order colors. Maximum order has to be accessible.
        float order_colors[H2DV_MAX_VIEWABLE_ORDER + 1][3];

        /// Initializes the palette from supplied vertices.
        void init_order_palette(double3* vert);

        virtual void on_display();
        virtual void on_key_down(unsigned char key, int x, int y);
        virtual void scale_dispatch();
        virtual int measure_scale_labels();
        virtual const char* get_help_text() const;
      };
#else
      class HERMES_API OrderView : public View
      {
      public:

        OrderView(const char* title = "OrderView", WinGeom* wg = nullptr) {}
        OrderView(char* title, WinGeom* wg = nullptr) {}

        template<typename Scalar>
        void show(SpaceSharedPtr<Scalar> space, bool show_edge_orders = true)  { throw Hermes::Exceptions::Exception("GLUT disabled."); }
        void set_b_orders(bool set)  { throw Hermes::Exceptions::Exception("GLUT disabled."); }
      };
#endif
    }
  }
}
#endif