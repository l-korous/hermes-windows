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

# ifndef __MESH2D_CPP_PARSER
# define __MESH2D_CPP_PARSER

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>
# include <cstdlib>
# include <cassert>
# include <map>

namespace Hermes
{
  namespace Hermes2D
  {
    /// \brief Class to stored 2d mesh parameters.
    /// .
    /// The MeshData class organizes all the necessary data structures required to store information in the input mesh file.
    /// All variables are stored internally as a mapping between strings and a list of strings. Symbolic expressions are not supported for variables.
    ///.
    /// The variables are stored in a vector of strings. This is true for single-valued variables, lists and list of lists.
    /// The contents of the variables are thus accessed differently depending on their contents.
    ///.
    class MeshData
    {
      /// Mesh Filename (private)
      std::string mesh_file_;

      /// Removes brackets, commas and other unessential details from the input file.
      /// Meaningful blank spaces are temporarily replaced with a ';'
      void strip(std::string &str);

      /// Restores ';' to blank spaces
      std::string restore(std::string &str);

    public:
      /// Map for storing variables in input mesh file
      std::map< std::string, std::vector< std::string > > vars_;

      /// Number of vertices
      int n_vert;
      /// Number of elements
      int n_el;
      /// Number of boundary edges
      int n_bdy;
      /// Number of curved edges (including NURBS curves)
      int n_curv;
      /// Number of elements with specified refinements
      int n_ref;

      /// x-coordinate of the vertices
      std::vector<double> x_vertex;
      /// y-coordinate of the vertices
      std::vector<double> y_vertex;

      /// Nodes with local node number 1
      std::vector<int> en1;
      /// Nodes with local node number 2
      std::vector<int> en2;
      /// Nodes with local node number 3
      std::vector<int> en3;
      /// Nodes with local node number 4. Only for quadrilateral elements. For triangular elements it is set to -1.
      std::vector<int> en4;

      /// Element markers -- single word strings
      std::vector<std::string> e_mtl;

      /// First node of a boundary edge
      std::vector<int> bdy_first;
      /// Second node of a boundary edge
      std::vector<int> bdy_second;
      /// Boundary name
      std::vector<std::string> bdy_type;

      /// First node of a curved edge
      std::vector<int> curv_first;
      /// Second node of a curved edge
      std::vector<int> curv_second;

      /// Third entry of a curve specification. Angle for a circular arc and degree for a NURBS curve.
      std::vector<double> curv_third;

      /// Name of the list of the control points and weights of a NURBS curve. Set to "none" for a circular arc
      std::vector<std::string> curv_inner_pts;
      /// Name of the list of knot vectors of a NURBS curve. Set to "none" for a circular arc
      std::vector<std::string> curv_knots;
      /// Nurbs Indicator. True if curve is modeled with NURBS. False if it is a circular arc.
      std::vector<bool> curv_nurbs;

      /// List of elements to be refined
      std::vector<int> ref_elt;
      /// List of element refinement type
      std::vector<int> ref_type;

      /// This function parses a given input mesh file line by line and extracts the necessary information into the MeshData class variables
      void parse_mesh(void);

      /// MeshData Constructor
      MeshData(const std::string &mesh_file);

      /// MeshData Copy Constructor
      MeshData(const MeshData &m);

      /// MeshData Assignment Operator
      MeshData& operator = (const MeshData &m);

      /// MeshData Destructor
      ~MeshData();
    };
  }
}
# endif