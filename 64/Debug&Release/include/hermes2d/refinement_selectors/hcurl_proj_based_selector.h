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

#ifndef __H2D_REFINEMENT_SELECTORS_HCURL_PROJ_BASED_SELECTOR_H
#define __H2D_REFINEMENT_SELECTORS_HCURL_PROJ_BASED_SELECTOR_H

#include "proj_based_selector.h"
#include "shapeset/shapeset_hc_all.h"
namespace Hermes
{
  namespace Hermes2D
  {
    namespace RefinementSelectors {
      /// A projection-based selector for Hcurl space. \ingroup g_selectors
      /** This class is designed to be used with the class HcurlAdapt.
      *  Since an initialization of the class may take a long time,
      *  it is suggested to create the instance outside the adaptivity
      *  loop. */
      template<typename Scalar>
      class HERMES_API HcurlProjBasedSelector : public ProjBasedSelector < Scalar > {
      public: //API
        /// Constructor.
        /** \param[in] cand_list A predefined list of candidates.
        *  \param[in] max_order A maximum order which considered. If ::H2DRS_DEFAULT_ORDER, a maximum order supported by the selector is used, see HcurlProjBasedSelector::H2DRS_MAX_HCURL_ORDER.
        *  \param[in] user_shapeset A shapeset. If nullptr, it will use internal instance of the class HcurlShapeset. */
        HcurlProjBasedSelector(CandList cand_list = H2D_HP_ANISO, int max_order = H2DRS_DEFAULT_ORDER, HcurlShapeset* user_shapeset = nullptr);

        /// Destructor.
        virtual ~HcurlProjBasedSelector();

      protected: //overloads
        /// A function expansion of a function f used by this selector.
        enum LocalFuncExpansion {
          H2D_HCFE_VALUE0 = 0, ///< A function expansion: f_0.
          H2D_HCFE_VALUE1 = 1, ///< A function expansion: f_1.
          H2D_HCFE_CURL = 2, ///< A function expansion: curl = df_1/dx - df_0/dy.
          H2D_HCFE_NUM = 3 ///< A total considered function expansion.
        };

        /// Array of arrays of precalculates. The first index is an index of a subdomain, the second index is an index of a function expansion (see enum LocalFuncExpansion).
        Scalar* precalc_rvals[H2D_MAX_ELEMENT_SONS][H2D_HCFE_NUM];

        /// A maximum used order in this Hcurl-space selector. \todo Replace the numerical constant after a symbolic constant is added to Hcurl shapeset which would declare the maximum supported order.
        static const int H2DRS_MAX_HCURL_ORDER;

        /// Sets OptimumSelector::current_max_order and OptimumSelector::current_min_order.
        /** The default order range is[1, ::H2DRS_MAX_HCURL_ORDER]. If curved, the upper boundary of the range becomes lower.
        *  Overriden function. For details, see OptimumSelector::set_current_order_range(). */
        virtual void get_current_order_range(Element* element, int& min_order, int& max_order);

        /// Returns an array of values of the reference solution at integration points.
        /**  Overriden function. For details, see ProjBasedSelector::precalc_ref_solution(). */
        virtual void precalc_ref_solution(int inx_son, MeshFunction<Scalar>* rsln, Element* element, int intr_gip_order, Scalar* rval[H2D_MAX_ELEMENT_SONS][MAX_NUMBER_FUNCTION_VALUES_FOR_SELECTORS]);

        /// Frees the data allocated in precalc_ref_solution.
        virtual void free_ref_solution_data(int inx_son, Scalar* rval[H2D_MAX_ELEMENT_SONS][MAX_NUMBER_FUNCTION_VALUES_FOR_SELECTORS]);

        /// Calculates values of shape function at GIP for all transformations.
        /**  Overriden function. For details, see ProjBasedSelector::precalc_shapes(). */
        virtual void precalc_shapes(const double3* gip_points, const int num_gip_points, const Trf* trfs, const int num_noni_trfs, const std::vector<typename OptimumSelector<Scalar>::ShapeInx>& shapes, const int max_shape_inx, typename ProjBasedSelector<Scalar>::TrfShape& svals, ElementMode2D mode);

        /// Calculates values of orthogonalized shape function at GIP for all transformations.
        /**  Overriden function. For details, see ProjBasedSelector::precalc_ortho_shapes(). */
        virtual void precalc_ortho_shapes(const double3* gip_points, const int num_gip_points, const Trf* trfs, const int num_noni_trfs, const std::vector<typename OptimumSelector<Scalar>::ShapeInx>& shapes, const int max_shape_inx, typename ProjBasedSelector<Scalar>::TrfShape& svals, ElementMode2D mode);

        /// Builds projection matrix using a given set of shapes.
        /**  Overriden function. For details, see ProjBasedSelector::build_projection_matrix(). */
        virtual double** build_projection_matrix(double3* gip_points, int num_gip_points, const int* shape_inx, const int num_shapes, ElementMode2D mode);

        /// Evaluates a value of the right-hande side in a subdomain.
        /**  Overriden function. For details, see ProjBasedSelector::evaluate_rhs_subdomain(). */
        virtual Scalar evaluate_rhs_subdomain(Element* sub_elem, const typename ProjBasedSelector<Scalar>::ElemGIP& sub_gip, int son, const typename ProjBasedSelector<Scalar>::ElemSubTrf& sub_trf, const typename ProjBasedSelector<Scalar>::ElemSubShapeFunc& sub_shape, Scalar* rval[H2D_MAX_ELEMENT_SONS][MAX_NUMBER_FUNCTION_VALUES_FOR_SELECTORS]);

        /// Evaluates an squared error of a projection of an element of a candidate onto subdomains.
        /**  Overriden function. For details, see ProjBasedSelector::evaluate_error_squared_subdomain(). */
        virtual double evaluate_error_squared_subdomain(Element* sub_elem, const typename ProjBasedSelector<Scalar>::ElemGIP& sub_gip, int son, const typename ProjBasedSelector<Scalar>::ElemSubTrf& sub_trf, const typename ProjBasedSelector<Scalar>::ElemProj& elem_proj, Scalar* rval[H2D_MAX_ELEMENT_SONS][MAX_NUMBER_FUNCTION_VALUES_FOR_SELECTORS]);

        friend class ProjBasedSelector < Scalar > ;
      };
    }
  }
}
#endif