// $Id$ 
// $Source$ 

//@HEADER
// ************************************************************************
// 
//            NOX: An Object-Oriented Nonlinear Solver Package
//                 Copyright (2002) Sandia Corporation
// 
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Roger Pawlowski (rppawlo@sandia.gov) or 
// Eric Phipps (etphipp@sandia.gov), Sandia National Laboratories.
// ************************************************************************
//  CVS Information
//  $Source$
//  $Author$
//  $Date$
//  $Revision$
// ************************************************************************
//@HEADER

#ifndef NOX_LINESEARCH_USERLIMITING_H
#define NOX_LINESEARCH_USERLIMITING_H

#include "NOX_LineSearch_Generic.H" // base class

#include "NOX_LineSearch_Utils_Printing.H"  // class data member
#include "NOX_LineSearch_Utils_Counters.H"  // class data member
#include "Teuchos_RCP.hpp"          // class data member

// Forward Declarations
namespace NOX {
  namespace MeritFunction {
    class Generic;
  }
}

namespace NOX {
namespace LineSearch {

/*!
  \brief A line search that limits the step size based limiting the change/update of specific entries in the solution vector.

  \author Roger Pawlowski
*/

class UserLimiting : public Generic {

public:
  
  //! Constructor
  UserLimiting(const Teuchos::RCP<NOX::GlobalData>& gd,
	       Teuchos::ParameterList& params);

  // derived
  bool reset(const Teuchos::RCP<NOX::GlobalData>& gd,
	     Teuchos::ParameterList& params);
  
  // derived
  bool compute(NOX::Abstract::Group& newgrp, double& step, 
	       const NOX::Abstract::Vector& dir,
	       const NOX::Solver::Generic& s);

  Teuchos::RCP<const Teuchos::ParameterList> getValidParameters();
  
private:

  void printOpeningRemarks() const;

private:

  Teuchos::RCP<NOX::Abstract::Vector> userLimits_;
  Teuchos::RCP<NOX::Abstract::Vector> invLimits_;
  Teuchos::RCP<NOX::Abstract::Vector> scaledUpdate_;
  double lowerStepBound_;
  double upperStepBound_;

  Teuchos::ParameterList* paramsPtr_;
  Teuchos::RCP<Teuchos::ParameterList> validParams_;
  bool useCounter_;
  Teuchos::RCP<NOX::GlobalData> globalDataPtr_;
  NOX::LineSearch::Utils::Printing print_;
  NOX::LineSearch::Utils::Counters counter_;

};
} // namespace LineSearch
} // namespace NOX
#endif
