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

#ifndef NOX_EPETRA_FINITEDIFFERENCECOLORINGWITHUPDATE_H
#define NOX_EPETRA_FINITEDIFFERENCECOLORINGWITHUPDATE_H

#include "Epetra_RowMatrix.h"    	            // base class
#include "NOX_Utils.H"          
#include "NOX_Epetra_FiniteDifference.H"    // base class

#include "NOX_Common.H"          // for <string>
#include "Teuchos_RCP.hpp"

#include "vector"                // for column indices from coloring
#include "list"                  //
#include "map"

// Forward Declarations
class Epetra_Comm;
class Epetra_Map;
class Epetra_MapColoring;
class Epetra_Import;
class Epetra_Vector;
class Epetra_IntVector;
class Epetra_CrsGraph;
class Epetra_CrsMatrix;

namespace NOX {

namespace Epetra {

/*! \brief Concrete implementation for creating an Epetra_RowMatrix Jacobian via finite 
differencing of the residual using coloring.  This method assumes the existence of a valid 
parallel coloring of the columns of the Jacobian (aka from Isorropia).

Unlike the class NOX::FiniteDifferenceColoring, this class allows for "update" colorings, for
use in situations where part of the Jacobian changes from iteration to iteration, but part 
does not.  The first time (or any time after the forceJacobianRecompute method is called) the 
method uses the complete coloring.  Afterwards, it uses the "update" coloring and only
changes the entries that can change.

WARNING: The "update" coloring assumes that rows AND columns corresponding to uncolored 
(aka color 0) nodes do not change from call to call.  If either the row or the column  
corresponding to a given node change then you must make sure it gets colored.


WARNING: Centered Difference Coloring is NOT supported as of yet.*/

class FiniteDifferenceColoringWithUpdate : public FiniteDifference {
 public:

  //! Constructor with no frills
  FiniteDifferenceColoringWithUpdate(
      Teuchos::ParameterList& printingParams,
      const Teuchos::RCP<Interface::Required>& i, 
      const NOX::Epetra::Vector& initialGuess, 
      const Teuchos::RCP<Epetra_MapColoring>& colorMap,
      double beta = 1.0e-6, double alpha = 1.0e-4);

  //! Constructor with graph
  FiniteDifferenceColoringWithUpdate(
      Teuchos::ParameterList& printingParams,
      const Teuchos::RCP<Interface::Required>& i, 
      const NOX::Epetra::Vector& initialGuess, 
      const Teuchos::RCP<Epetra_CrsGraph>& rawGraph,
      const Teuchos::RCP<Epetra_MapColoring>& colorMap,
      double beta = 1.0e-6, double alpha = 1.0e-4);
 
  //! Constructor with update map 
  FiniteDifferenceColoringWithUpdate(
      Teuchos::ParameterList& printingParams,
      const Teuchos::RCP<Interface::Required>& i, 
      const NOX::Epetra::Vector& initialGuess, 
      const Teuchos::RCP<Epetra_MapColoring>& colorMap,
      const Teuchos::RCP<Epetra_MapColoring>& updateColorMap,
      double beta = 1.0e-6, double alpha = 1.0e-4);


  //! Constructor with update map and graph
  FiniteDifferenceColoringWithUpdate(
      Teuchos::ParameterList& printingParams,
      const Teuchos::RCP<Interface::Required>& i, 
      const NOX::Epetra::Vector& initialGuess, 
      const Teuchos::RCP<Epetra_CrsGraph>& rawGraph,
      const Teuchos::RCP<Epetra_MapColoring>& colorMap,
      const Teuchos::RCP<Epetra_MapColoring>& updatecolorMap,
      double beta = 1.0e-6, double alpha = 1.0e-4);


  virtual void forceJacobianRecompute(){jacobianComputed=false;}

  //! Pure virtual destructor
  virtual ~FiniteDifferenceColoringWithUpdate();

  //! Computes (or updates) the Jacobian given the specified input vector, x. Returns true if computation was successful.
  virtual bool computeJacobian(const Epetra_Vector& x, Epetra_Operator& Jac);

  //! Computes (or updates) Jacobian given the specified input vector, x. Returns true if computation was successful.
  virtual bool computeJacobian(const Epetra_Vector& x);

  //! Disable/Enable the (low computational cost) probing diagnostics
  void SetProbingDiagnostics(bool activate){use_probing_diags=activate;}

protected:  
  bool differenceProbe(const Epetra_Vector& x, Epetra_CrsMatrix& Jac,const Epetra_MapColoring &colors);

  bool jacobianComputed;
  bool use_update;
  bool use_probing_diags;

  // These should be COLUMN colorings, ergo, no import should be needed
  Teuchos::RCP<Epetra_MapColoring> colorMap_;
  Teuchos::RCP<Epetra_MapColoring> updateColorMap_;

  

};
}  // namespace Epetra
}  // namespace NOX

#endif /* _EPETRA_FINITEDIFFERENCECOLORINGWITHUPDATE_H_ */
