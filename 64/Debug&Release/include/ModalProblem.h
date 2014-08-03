//**************************************************************************
//
//                                 NOTICE
//
// This software is a result of the research described in the report
//
// " A comparison of algorithms for modal analysis in the absence 
//   of a sparse direct method", P. Arbenz, R. Lehoucq, and U. Hetmaniuk,
//  Sandia National Laboratories, Technical report SAND2003-1028J.
//
// It is based on the Epetra, AztecOO, and ML packages defined in the Trilinos
// framework ( http://software.sandia.gov/trilinos/ ).
//
// The distribution of this software follows also the rules defined in Trilinos.
// This notice shall be marked on any reproduction of this software, in whole or
// in part.
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// Code Authors: U. Hetmaniuk (ulhetma@sandia.gov), R. Lehoucq (rblehou@sandia.gov)
//
//**************************************************************************

#ifndef ANASAZI_MODAL_PROBLEM_H
#define ANASAZI_MODAL_PROBLEM_H

#include "Anasaziepetra_ModeLaplace_DLLExportMacro.h"

class Epetra_MultiVector;

class ANASAZIEPETRA_MODELAPLACE_LIB_DLL_EXPORT ModalProblem {

  public:

    virtual ~ModalProblem() { }

    virtual const Epetra_CrsMatrix* getStiffness() const = 0;
    virtual const Epetra_CrsMatrix* getMass()      const = 0;

    virtual int eigenCheck(const Epetra_MultiVector &Q, double *lambda,
                           double *normWeight, bool smallest = 0) const { 
      (void)Q;
      (void)lambda;
      (void)normWeight;
      (void)smallest;
      return 0; 
    };

    virtual void memoryInfo() const { };
    virtual void problemInfo() const { };

};

#endif
