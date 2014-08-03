// *************************************************************************
//
//    PARALUTION   www.paralution.com
//
//    Copyright (C) 2012-2014 Dimitar Lukarski
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *************************************************************************



// PARALUTION version 0.7.0b 


#include "host_matrix_dense.hpp"
#include "host_matrix_ell.hpp"
#include "host_matrix_dia.hpp"
#include "host_matrix_hyb.hpp"
#include "host_matrix_coo.hpp"
#include "host_matrix_csr.hpp"
#include "host_conversion.hpp"
#include "../base_matrix.hpp"
#include "../base_vector.hpp"
#include "host_vector.hpp"
#include "../backend_manager.hpp"
#include "../../utils/log.hpp"
#include "../../utils/allocate_free.hpp"
#include "../matrix_formats_ind.hpp"

extern "C" {
#include "../../../thirdparty/matrix-market/mmio.h"
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_set_num_threads(num) ;
#endif

#ifdef SUPPORT_MKL
#include <mkl.h>
#include <mkl_spblas.h>
#endif


namespace paralution {

template <typename ValueType>
HostMatrixDENSE<ValueType>::HostMatrixDENSE() {

  // no default constructors
  LOG_INFO("no default constructor");
  FATAL_ERROR(__FILE__, __LINE__);

}

template <typename ValueType>
HostMatrixDENSE<ValueType>::HostMatrixDENSE(const Paralution_Backend_Descriptor local_backend) {

  LOG_DEBUG(this, "HostMatrixDENSE::HostMatrixDENSE()",
            "constructor with local_backend");

  this->mat_.val = NULL;
  this->set_backend(local_backend);

}

template <typename ValueType>
HostMatrixDENSE<ValueType>::~HostMatrixDENSE() {

  LOG_DEBUG(this, "HostMatrixDENSE::~HostMatrixDENSE()",
            "destructor");

  this->Clear();

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::info(void) const {

  LOG_INFO("HostMatrixDENSE<ValueType>");

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::Clear() {

  if (this->get_nnz() > 0) {

    free_host(&this->mat_.val);

    this->nrow_ = 0;
    this->ncol_ = 0;
    this->nnz_  = 0;

  }

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::AllocateDENSE(const int nrow, const int ncol) {

  assert( ncol  >= 0);
  assert( nrow  >= 0);

  if (this->get_nnz() > 0)
    this->Clear();

  if (nrow*ncol > 0) {

    allocate_host(nrow*ncol, &this->mat_.val);
    set_to_zero_host(nrow*ncol, mat_.val);   

    this->nrow_ = nrow;
    this->ncol_ = ncol;
    this->nnz_  = nrow*ncol;

  }

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::SetDataPtrDENSE(ValueType **val, const int nrow, const int ncol) {

  assert(*val != NULL);
  assert(nrow > 0);
  assert(ncol > 0);

  this->Clear();

  this->nrow_ = nrow;
  this->ncol_ = ncol;
  this->nnz_  = nrow*ncol;

  this->mat_.val = *val;

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::LeaveDataPtrDENSE(ValueType **val) {

  assert(this->get_nrow() > 0);
  assert(this->get_ncol() > 0);
  assert(this->get_nnz() > 0);

  *val = this->mat_.val;

  this->mat_.val = NULL;

  this->nrow_ = 0;
  this->ncol_ = 0;
  this->nnz_  = 0;

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::CopyFrom(const BaseMatrix<ValueType> &mat) {

  // copy only in the same format
  assert(this->get_mat_format() == mat.get_mat_format());

  if (const HostMatrixDENSE<ValueType> *cast_mat = dynamic_cast<const HostMatrixDENSE<ValueType>*> (&mat)) {
    
    this->AllocateDENSE(cast_mat->get_nrow(), cast_mat->get_ncol());

    assert((this->get_nnz()  == mat.get_nnz())  &&
	   (this->get_nrow() == mat.get_nrow()) &&
	   (this->get_ncol() == mat.get_ncol()) );    

    if (this->get_nnz() > 0) {

      _set_omp_backend_threads(this->local_backend_, this->get_nnz());  

      int nnz  = this->get_nnz();

#pragma omp parallel for      
      for (int j=0; j<nnz; ++j)
        this->mat_.val[j] = cast_mat->mat_.val[j];

    }

  } else {
    
    // Host matrix knows only host matrices
    // -> dispatching
    mat.CopyTo(this);
    
  }  

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::CopyTo(BaseMatrix<ValueType> *mat) const {

  mat->CopyFrom(*this);

}

template <typename ValueType>
bool HostMatrixDENSE<ValueType>::ConvertFrom(const BaseMatrix<ValueType> &mat) {

  this->Clear();

  // empty matrix is empty matrix
  if (mat.get_nnz() == 0)
    return true;

    if (const HostMatrixDENSE<ValueType> *cast_mat = dynamic_cast<const HostMatrixDENSE<ValueType>*> (&mat)) {

      this->CopyFrom(*cast_mat);
      return true;

  }


    if (const HostMatrixCSR<ValueType> *cast_mat = dynamic_cast<const HostMatrixCSR<ValueType>*> (&mat)) {

      this->Clear();

      csr_to_dense(this->local_backend_.OpenMP_threads,
                   cast_mat->get_nnz(), cast_mat->get_nrow(), cast_mat->get_ncol(),
                   cast_mat->mat_, &this->mat_);

      this->nrow_ = cast_mat->get_nrow();
      this->ncol_ = cast_mat->get_ncol();
      this->nnz_ = this->nrow_ * this->ncol_;

      return true;

  }

  return false;

}

#ifdef SUPPORT_MKL

template <>
void HostMatrixDENSE<double>::Apply(const BaseVector<double> &in, BaseVector<double> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_ncol());
  assert(out->get_size() == this->get_nrow());

  const HostVector<double> *cast_in = dynamic_cast<const HostVector<double>*> (&in) ; 
  HostVector<double> *cast_out      = dynamic_cast<      HostVector<double>*> (out) ; 

  assert(cast_in != NULL);
  assert(cast_out!= NULL);
 
  int nrow = this->get_nrow() ;
  int ncol = this->get_ncol();
  double alpha = double(1.0);
  double beta = double(0.0);

  cblas_dgemv(CblasRowMajor, CblasNoTrans, 
              nrow, ncol,
              alpha, this->mat_.val,
              nrow, 
              cast_in->vec_, 1, beta,
              cast_out->vec_, 1);

}

template <>
void HostMatrixDENSE<float>::Apply(const BaseVector<float> &in, BaseVector<float> *out) const {
  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_ncol());
  assert(out->get_size() == this->get_nrow());

  const HostVector<float> *cast_in = dynamic_cast<const HostVector<float>*> (&in) ; 
  HostVector<float> *cast_out      = dynamic_cast<      HostVector<float>*> (out) ; 

  assert(cast_in != NULL);
  assert(cast_out!= NULL);

  int nrow = this->get_nrow() ;
  int ncol = this->get_ncol();
  float alpha = float(1.0);
  float beta = float(0.0);

  cblas_sgemv(CblasRowMajor, CblasNoTrans, 
              nrow, ncol,
              alpha, this->mat_.val,
              nrow, 
              cast_in->vec_, 1, beta,
              cast_out->vec_, 1);


}

#else

template <typename ValueType>
void HostMatrixDENSE<ValueType>::Apply(const BaseVector<ValueType> &in, BaseVector<ValueType> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_ncol());
  assert(out->get_size() == this->get_nrow());

  const HostVector<ValueType> *cast_in = dynamic_cast<const HostVector<ValueType>*> (&in) ; 
  HostVector<ValueType> *cast_out      = dynamic_cast<      HostVector<ValueType>*> (out) ; 

  assert(cast_in != NULL);
  assert(cast_out!= NULL);

  _set_omp_backend_threads(this->local_backend_, this->get_nnz());  

#pragma omp parallel for
  for (int ai=0; ai<this->get_nrow(); ++ai) {
    cast_out->vec_[ai] = ValueType(0.0);
      for (int aj=0; aj<this->get_ncol(); ++aj) 
        cast_out->vec_[ai] += this->mat_.val[DENSE_IND(ai,aj,this->get_nrow(),this->get_ncol())] * cast_in->vec_[aj];
  }

}

#endif

#ifdef SUPPORT_MKL

template <>
void HostMatrixDENSE<double>::ApplyAdd(const BaseVector<double> &in, const double scalar,
                                       BaseVector<double> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_ncol());
  assert(out->get_size() == this->get_nrow());

  const HostVector<double> *cast_in = dynamic_cast<const HostVector<double>*> (&in) ; 
  HostVector<double> *cast_out      = dynamic_cast<      HostVector<double>*> (out) ; 

  assert(cast_in != NULL);
  assert(cast_out!= NULL);
 
  int nrow = this->get_nrow() ;
  int ncol = this->get_ncol();
  double beta = double(1.0);

  cblas_dgemv(CblasRowMajor, CblasNoTrans, 
              nrow, ncol,
              scalar, this->mat_.val,
              nrow, 
              cast_in->vec_, 1, beta,
              cast_out->vec_, 1);

}

template <>
void HostMatrixDENSE<float>::ApplyAdd(const BaseVector<float> &in, const float scalar,
                                      BaseVector<float> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_ncol());
  assert(out->get_size() == this->get_nrow());

  const HostVector<float> *cast_in = dynamic_cast<const HostVector<float>*> (&in) ; 
  HostVector<float> *cast_out      = dynamic_cast<      HostVector<float>*> (out) ; 

  assert(cast_in != NULL);
  assert(cast_out!= NULL);

  int nrow = this->get_nrow() ;
  int ncol = this->get_ncol();
  float beta = float(1.0);

  cblas_sgemv(CblasRowMajor, CblasNoTrans, 
              nrow, ncol,
              scalar, this->mat_.val,
              nrow, 
              cast_in->vec_, 1, beta,
              cast_out->vec_, 1);


}

#else

template <typename ValueType>
void HostMatrixDENSE<ValueType>::ApplyAdd(const BaseVector<ValueType> &in, const ValueType scalar,
                                        BaseVector<ValueType> *out) const {

  if (this->get_nnz() > 0) {

    assert(in.  get_size() >= 0);
    assert(out->get_size() >= 0);
    assert(in.  get_size() == this->get_ncol());
    assert(out->get_size() == this->get_nrow());
    
    const HostVector<ValueType> *cast_in = dynamic_cast<const HostVector<ValueType>*> (&in) ; 
    HostVector<ValueType> *cast_out      = dynamic_cast<      HostVector<ValueType>*> (out) ; 
    
    assert(cast_in != NULL);
    assert(cast_out!= NULL);

  _set_omp_backend_threads(this->local_backend_, this->get_nnz());  

#pragma omp parallel for
  for (int ai=0; ai<this->get_nrow(); ++ai) 
    for (int aj=0; aj<this->get_ncol(); ++aj) 
      cast_out->vec_[ai] += scalar * this->mat_.val[DENSE_IND(ai,aj,this->get_nrow(),this->get_ncol())] * cast_in->vec_[aj];

  }

}

#endif

template <typename ValueType>
void HostMatrixDENSE<ValueType>::Householder(const int idx, ValueType &beta, BaseVector<ValueType> *vec) {

  HostVector<ValueType> *cast_vec = dynamic_cast<HostVector<ValueType>*> (vec);
  assert(cast_vec != NULL);
  assert(cast_vec->get_size() >= this->get_nrow()-idx);

  int nrow = this->get_nrow();

  ValueType s  = 0.0;
  ValueType mu;

  for (int i=0; i<nrow-idx; ++i)
    cast_vec->vec_[i] = this->mat_.val[DENSE_IND(idx, i+idx, nrow, this->get_ncol())];

  ValueType y1 = cast_vec->vec_[0];

  for (int i=1; i<nrow-idx; ++i)
    s += cast_vec->vec_[i] * cast_vec->vec_[i];

  cast_vec->vec_[0] = 1.0;

  if (s == 0.0) {

    beta = 0.0;

  } else {

    mu = sqrt(y1 * y1 + s);

    if (y1 <= 0.0)
      cast_vec->vec_[0] = y1 - mu;
    else
      cast_vec->vec_[0] = -s / (y1 + mu);

    ValueType y0sq = cast_vec->vec_[0] * cast_vec->vec_[0];
    beta = 2 * y0sq / (s + y0sq);

    ValueType norm = cast_vec->vec_[0];
    for (int i=0; i<nrow-idx; ++i)
      cast_vec->vec_[i] /= norm;

  }

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::QRDecompose(void) {

  assert(this->get_nrow() > 0);
  assert(this->get_ncol() > 0);
  assert(this->get_nnz() > 0);

  int nrow = this->get_nrow();
  int ncol = this->get_ncol();

  int size = (nrow < ncol) ? nrow : ncol;
  ValueType beta;
  HostVector<ValueType> v(this->local_backend_);
  v.Allocate(nrow);

  for (int i=0; i<size; ++i) {

    this->Householder(i, beta, &v);

    if (beta != 0.0) {

      for (int aj=i; aj<ncol; ++aj) {
        ValueType sum = 0.0;
        for (int ai=i; ai<nrow; ++ai)
          sum += v.vec_[ai-i] * this->mat_.val[DENSE_IND(ai, aj, nrow, ncol)];
        sum *= beta;

        for (int ai=i; ai<nrow; ++ai)
          this->mat_.val[DENSE_IND(ai, aj, nrow, ncol)] -= sum * v.vec_[ai-i];

      }

      for (int k=i+1; k<nrow; ++k)
        this->mat_.val[DENSE_IND(k, i, nrow, ncol)] = v.vec_[k-i];

    }

  }

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::QRSolve(const BaseVector<ValueType> &in, BaseVector<ValueType> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_nrow());
  assert(out->get_size() == this->get_ncol());

  HostVector<ValueType> *cast_out = dynamic_cast<HostVector<ValueType>*>(out);

  assert(cast_out!= NULL);

  HostVector<ValueType> copy_in(this->local_backend_);
  copy_in.CopyFrom(in);

  int nrow = this->get_nrow();
  int ncol = this->get_ncol();
  int size = (nrow < ncol) ? nrow : ncol;

  ValueType *v = NULL;
  allocate_host(this->get_nrow(), &v);

  // Apply Q^T on copy_in
  v[0] = 1.0;
  for (int i=0; i<size; ++i) {

    ValueType sum = 1.0;
    for (int j=1; j<this->get_nrow()-i; ++j) {
      v[j] = this->mat_.val[DENSE_IND(j+i,i,this->get_nrow(), this->get_ncol())];
      sum += v[j] * v[j];
    }
    sum = ValueType(2.0) / sum;

    if (sum != 2.0) {

      ValueType sum2 = 0.0;
      for (int j=0; j<this->get_nrow()-i; ++j)
        sum2 += v[j] * copy_in.vec_[j+i];

      for (int j=0; j<this->get_nrow()-i; ++j)
        copy_in.vec_[j+i] -= sum * sum2 * v[j];

    }

  }

  free_host(&v);

  // Backsolve Rx = Q^T b
  for (int i=size-1; i>=0; --i) {

    ValueType sum = 0.0;
    for (int j=i+1; j<ncol; ++j)
      sum += this->mat_.val[DENSE_IND(i, j, this->get_nrow(), this->get_ncol())] * cast_out->vec_[j];

    cast_out->vec_[i] = (copy_in.vec_[i] - sum) / this->mat_.val[DENSE_IND(i, i, this->get_nrow(), this->get_ncol())];

  }

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::Invert(void) {

  assert(this->get_nrow() > 0);
  assert(this->get_ncol() > 0);
  assert(this->get_nnz() > 0);
  assert(this->get_nrow() == this->get_ncol());

  ValueType *val = NULL;
  allocate_host(this->get_nrow() * this->get_ncol(), &val);

  this->QRDecompose();

#pragma omp parallel for
  for (int i=0; i<this->get_nrow(); ++i) {

    HostVector<ValueType> sol(this->local_backend_);
    HostVector<ValueType> rhs(this->local_backend_);
    sol.Allocate(this->get_nrow());
    rhs.Allocate(this->get_nrow());

    rhs.vec_[i] = ValueType(1.0);

    this->QRSolve(rhs, &sol);

    for (int j=0; j<this->get_ncol(); ++j)
      val[DENSE_IND(j, i, this->get_nrow(), this->get_ncol())] = sol.vec_[j];

  }

  free_host(&this->mat_.val);
  this->mat_.val = val;

}

template <typename ValueType>
void HostMatrixDENSE<ValueType>::LUFactorize(void) {

  assert(this->get_nrow() > 0);
  assert(this->get_ncol() > 0);
  assert(this->get_nnz() > 0);
  assert(this->get_nrow() == this->get_ncol());

  int nrow = this->get_nrow();
  int ncol = this->get_ncol();

  for (int i=0; i<nrow-1; ++i)
    for (int j=i+1; j<nrow; ++j) {

      this->mat_.val[DENSE_IND(j, i, nrow, ncol)] /= this->mat_.val[DENSE_IND(i, i, nrow, ncol)];

      for (int k=i+1; k<ncol; ++k)
        this->mat_.val[DENSE_IND(j, k, nrow, ncol)] -= this->mat_.val[DENSE_IND(j, i, nrow, ncol)]
                                                     * this->mat_.val[DENSE_IND(i, k, nrow, ncol)];

    }

}

template <typename ValueType>
bool HostMatrixDENSE<ValueType>::LUSolve(const BaseVector<ValueType> &in, BaseVector<ValueType> *out) const {

  assert(in.  get_size() >= 0);
  assert(out->get_size() >= 0);
  assert(in.  get_size() == this->get_nrow());
  assert(out->get_size() == this->get_ncol());

  HostVector<ValueType> *cast_out = dynamic_cast<HostVector<ValueType>*>(out);
  const HostVector<ValueType> *cast_in = dynamic_cast<const HostVector<ValueType>*>(&in);

  assert(cast_out!= NULL);

  // fill solution vector
  for (int i=0; i<this->get_nrow(); ++i)
    cast_out->vec_[i] = cast_in->vec_[i];

  // forward sweeps
  for (int i=0; i<this->get_nrow()-1; ++i) {
    for (int j=i+1; j<this->get_nrow(); ++j)
      cast_out->vec_[j] -= cast_out->vec_[i] * this->mat_.val[DENSE_IND(j, i, this->get_nrow(), this->get_ncol())];
  }

  // backward sweeps
  for (int i=this->get_nrow()-1; i>=0; --i) {
    cast_out->vec_[i] /= this->mat_.val[DENSE_IND(i, i, this->get_nrow(), this->get_ncol())];
    for (int j=0; j<i; ++j)
      cast_out->vec_[j] -= cast_out->vec_[i] * this->mat_.val[DENSE_IND(j, i, this->get_nrow(), this->get_ncol())];
  }

  return true;

}


template class HostMatrixDENSE<double>;
template class HostMatrixDENSE<float>;

}

