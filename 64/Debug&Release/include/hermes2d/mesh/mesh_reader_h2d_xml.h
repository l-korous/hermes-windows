// This file is part of Hermes2D
//
// Hermes2D is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D; if not, see <http://www.gnu.prg/licenses/>.

#ifndef _MESH_READER_H2D_XML_H_
#define _MESH_READER_H2D_XML_H_

#include "mesh_reader.h"

// This is here mainly because XSD uses its own error, therefore it has to be undefined here.
#ifdef error
#undef error
#endif

#include "mesh_h2d_xml.h"
#include "subdomains_h2d_xml.h"

// This is here mainly because XSD uses its own error, therefore it had to be undefined previously.
#ifndef error
#define error(...) hermes_exit_if(hermes_log_message_if(true, HERMES_BUILD_LOG_INFO(HERMES_EC_ERROR), __VA_ARGS__))
#endif

namespace Hermes
{
  namespace Hermes2D
  {
    /// Mesh reader from Hermes2D XML format
    ///
    /// Typical usage:
    /// MeshSharedPtr mesh;
    /// Hermes::Hermes2D::MeshReaderH2DXML mloader;
    /// try
    /// {
    ///&nbsp;mloader.load("mesh.xml", &mesh);
    /// }
    /// catch(Exceptions::MeshLoadFailureException& e)
    /// {
    ///&nbsp;e.print_msg();
    ///&nbsp;return -1;
    /// }
    ///
    /// The format specification is in hermes2d/xml_schemas/mesh_h2d_xml.xsd
    class HERMES_API MeshReaderH2DXML : public MeshReader, public Hermes::Hermes2D::Mixins::XMLParsing
    {
    public:
      MeshReaderH2DXML();
      virtual ~MeshReaderH2DXML();

      /// This method loads a single mesh from a file.
      virtual void load(const char *filename, MeshSharedPtr mesh);

      /// This method loads a single mesh from a XML structure.
      virtual void load(std::auto_ptr<XMLMesh::mesh> & parsed_xml_mesh, MeshSharedPtr mesh);

      /// This method saves a single mesh to a file.
      void save(const char *filename, MeshSharedPtr mesh);

      /// This method loads multiple meshes according to subdomains described in the meshfile.
      /// \param[in] meshes Meshes to be loaded, the number must correspond to the subdomains described in the file.
      ///&nbsp;         also the order is determined by the order in the file.
      void load(const char *filename, std::vector<MeshSharedPtr> meshes);

      /// This method loads multiple meshes according to subdomains described in the meshfile.
      /// \param[in] meshes Meshes to be loaded, the number must correspond to the subdomains described in the provided XML structure.
      ///&nbsp;         also the order is determined by the order in the file.
      void load(std::auto_ptr<XMLSubdomains::domain> & parsed_xml_domain, std::vector<MeshSharedPtr> meshes);

      /// This method saves multiple meshes according to subdomains in the vector meshes.
      void save(const char *filename, std::vector<MeshSharedPtr> meshes);

    protected:
      /// Internal method loading contents of parsed_xml_mesh into mesh.
      void load(std::auto_ptr<XMLMesh::mesh> & parsed_xml_mesh, MeshSharedPtr mesh, std::map<unsigned int, unsigned int>& vertex_is);

      /// Internal method loading contents of parsed_xml_domain's domain into mesh.
      void load(std::auto_ptr<XMLSubdomains::domain> & parsed_xml_domain, MeshSharedPtr mesh, std::map<int, int>& vertex_is, std::map<int, int>& element_is, std::map<int, int>& edge_is);

      /// Loads one general NURBS curve.
      /// \param[in] parsed_xml_entity Either XMLSubdomains::domain or XMLMesh::mesh.
      /// \param[in] skip_check Skip check that the edge exists, in case of subdomains.
      template<typename T>
      Nurbs* load_nurbs(MeshSharedPtr mesh, std::auto_ptr<T> & parsed_xml_entity, int id, Node** en, int p1, int p2, bool skip_check = false);

      /// Saves one circular arc.
      void save_arc(MeshSharedPtr mesh, int p1, int p2, Arc* curve, XMLMesh::curves_type & curves);

      /// Saves one general NURBS curve.
      void save_nurbs(MeshSharedPtr mesh, int p1, int p2, Nurbs* curve, XMLMesh::curves_type & curves);
    };
  }
}
#endif
