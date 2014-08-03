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

#ifndef __H2D_VECTOR_VIEW_H
#define __H2D_VECTOR_VIEW_H
#include "view.h"
#include "linearizer.h"

namespace Hermes
{
  namespace Hermes2D
  {
    namespace Views
    {
      // you can define NOGLUT to turn off all OpenGL stuff in Hermes2D
#ifndef NOGLUT

      /// \brief Visualizes a vector PDE solution.
      ///
      /// VectorView is a visualization window for all vector-valued PDE solutions.
      ///
      class HERMES_API VectorView : public View
      {
      public:

        VectorView(const char* title = "VectorView", WinGeom* wg = nullptr);
        VectorView(char* title, WinGeom* wg = nullptr);
        ~VectorView();

        void show(MeshFunctionSharedPtr<double> vsln);
        void show(MeshFunctionSharedPtr<double> xsln, MeshFunctionSharedPtr<double> ysln, int xitem = H2D_FN_VAL_0, int yitem = H2D_FN_VAL_0, MeshFunctionSharedPtr<double> xdisp = nullptr, MeshFunctionSharedPtr<double> ydisp = nullptr, double dmult = 1.0);

        inline void set_grid_type(bool hexa) { this->hexa = hexa; refresh(); };
        void set_mode(int mode);

        /// Returns the internal Linearizer for the purpose of parameter settings.
        Vectorizer* get_vectorizer();
        /// Sets the criterion to use for the linearization process.
        /// This criterion is used in ThreadLinearizerMultidimensional class instances (see threadLinearizerMultidimensional array).
        /// \param[in] criterion The instance of the criterion - see the class LinearizerCriterion for details (method split_decision() for the adaptive criterion, process_[triangle|quad] for the fixed one).
        void set_vectorizer_criterion(LinearizerCriterion criterion);

      protected:
        /// Linearizer class responsible for obtaining linearized data.
        Vectorizer* vec;

        double gx, gy, gs;
        /// false - quad grid, true - hexa grid
        bool hexa;
        /// 0 - magnitude is on the background, 1 - arrows are colored, 2 - no arrows, just magnitude on the background
        int mode;
        bool lines, pmode;
        /// for extending or shortening arrows
        double length_coef;
        /// draws edges
        void draw_edges_2d();

        void plot_arrow(double x, double y, double xval, double yval, double max, double min, double gs);

        virtual void on_display();
        virtual void on_mouse_move(int x, int y);
        virtual void on_key_down(unsigned char key, int x, int y);
        virtual const char* get_help_text() const;
      };
#else
      class HERMES_API VectorView : public View
      {
      public:
        VectorView(const char* title = "VectorView", WinGeom* wg = nullptr) {}
        VectorView(char* title, WinGeom* wg = nullptr) {}

        void show(MeshFunctionSharedPtr<double> vsln) { throw Hermes::Exceptions::Exception("GLUT disabled."); }
        void show(MeshFunctionSharedPtr<double> xsln, MeshFunctionSharedPtr<double> ysln, int xitem = H2D_FN_VAL_0, int yitem = H2D_FN_VAL_0, MeshFunctionSharedPtr<double> xdisp = nullptr, MeshFunctionSharedPtr<double> ydisp = nullptr, double dmult = 1.0) { throw Hermes::Exceptions::Exception("GLUT disabled."); }

        inline void set_grid_type(bool hexa) { throw Hermes::Exceptions::Exception("GLUT disabled."); }
        void set_mode(int mode) { throw Hermes::Exceptions::Exception("GLUT disabled."); }

        /// Returns the internal Linearizer for the purpose of parameter settings.
        Vectorizer* get_vectorizer() { throw Hermes::Exceptions::Exception("GLUT disabled."); return nullptr; }
        /// Sets the criterion to use for the linearization process.
        /// This criterion is used in ThreadLinearizerMultidimensional class instances (see threadLinearizerMultidimensional array).
        /// \param[in] criterion The instance of the criterion - see the class LinearizerCriterion for details (method split_decision() for the adaptive criterion, process_[triangle|quad] for the fixed one).
        void set_vectorizer_criterion(LinearizerCriterion criterion) { throw Hermes::Exceptions::Exception("GLUT disabled."); return nullptr; }
      };
#endif
    }
  }
}
#endif