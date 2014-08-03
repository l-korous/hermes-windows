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


#ifndef PARALUTION_GPU_MATRIX_DENSE_HPP_
#define PARALUTION_GPU_MATRIX_DENSE_HPP_

#include "../base_matrix.hpp"
#include "../base_vector.hpp"
#include "../matrix_formats.hpp"

namespace paralution {

template <typename ValueType>
class GPUAcceleratorMatrixDENSE : public GPUAcceleratorMatrix<ValueType> {
  
public:

  GPUAcceleratorMatrixDENSE();
  GPUAcceleratorMatrixDENSE(const Paralution_Backend_Descriptor local_backend);
  virtual ~GPUAcceleratorMatrixDENSE();

  virtual void info(void) const;
  virtual unsigned int get_mat_format(void) const{ return DENSE; }

  virtual void Clear(void);
  virtual void AllocateDENSE(const int nrow, const int ncol);

  virtual bool ConvertFrom(const BaseMatrix<ValueType> &mat);

  virtual void CopyFrom(const BaseMatrix<ValueType> &mat);
  virtual void CopyFromAsync(const BaseMatrix<ValueType> &mat);
  virtual void CopyTo(BaseMatrix<ValueType> *mat) const;
  virtual void CopyToAsync(BaseMatrix<ValueType> *mat) const;

  virtual void CopyFromHost(const HostMatrix<ValueType> &src);
  virtual void CopyFromHostAsync(const HostMatrix<ValueType> &src);
  virtual void CopyToHost(HostMatrix<ValueType> *dst) const;
  virtual void CopyToHostAsync(HostMatrix<ValueType> *dst) const;

  virtual void Apply(const BaseVector<ValueType> &in, BaseVector<ValueType> *out) const; 
  virtual void ApplyAdd(const BaseVector<ValueType> &in, const ValueType scalar,
                        BaseVector<ValueType> *out) const; 
  
private:
  
  MatrixDENSE<ValueType> mat_;

  friend class BaseVector<ValueType>;  
  friend class AcceleratorVector<ValueType>;  
  friend class GPUAcceleratorVector<ValueType>;  

};


}

#endif // PARALUTION_GPU_MATRIX_DENSE_HPP_

