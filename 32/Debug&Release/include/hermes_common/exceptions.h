// This file is part of HermesCommon
//
// Copyright (c) 2009 hp-FEM group at the University of Nevada, Reno (UNR).
// Email: hpfem-group@unr.edu, home page: http://www.hpfem.org/.
//
// Hermes2D is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 2 of the License,
// or (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
/*! \file exceptions.h
\brief File containing definition of exceptions classes
*/
#ifndef __HERMES_COMMON_EXCEPTIONS_H_
#define __HERMES_COMMON_EXCEPTIONS_H_

#include "common.h"
#include "util/compat.h"

#ifndef _DEBUG
#undef assert
#define assert(x)
#endif

namespace Hermes
{
  namespace Exceptions
  {
    /// \brief Exception interface
    /// Basically a std::exception, but with a constructor with string and with print_msg method.
    /// Usage:
    /// try
    /// {
    ///&nbsp;...
    ///&nbsp;throw Hermes::Exceptions::Exception("this is an exception message");
    /// }
    /// catch(Hermes::Exceptions::Exception& e)
    /// {
    ///&nbsp;e.print_msg();
    /// }
    class HERMES_API Exception : public std::exception
    {
    public:
      /// \brief Init exception with default message.
      Exception();
      Exception(const Exception& e);
      /// Init exception with message.
      /// \param[in] msg message
      Exception(const char * msg, ...);
      /// \brief print error message to stderr
      void print_msg() const;
      /// \brief get pointer to error message
      virtual const char * what() const throw();
      std::string info() const;
      /// \return name of function where exception was created.
      const char * get_func_name() const;
      virtual ~Exception() throw() {};

    protected:
      std::stringstream message;
      /// To be compatible with what().
      char message_char[10000];
    };

    /// \brief IO exception.
    /// Internal.
    /// Exception occurs when something fails to be written to / read from the disk.
    class HERMES_API IOException : public Exception
    {
    public:
      /// Read or Write.
      enum ReadWrite
      {
        Read,
        Write
      };
      /// Constructor
      /// \param[in] readWrite obvious.
      /// \param[in] filename obvious.
      IOException(ReadWrite readWrite, const char* filename);
      IOException(ReadWrite readWrite, std::string filename);

      virtual ~IOException() throw() {};
      IOException(const IOException & e);
    private:
      ReadWrite readWrite;
      std::string filename;
    };

    /// \brief Null parameter exception.
    /// Internal.
    /// Exception occurs when some parameter is Null or empty and it shouldn't be.
    class HERMES_API NullException : public Exception
    {
    public:
      /// Constructor - simple.
      NullException();
      /// Constructor
      /// \param[in] paramnIdx index of null parameter.
      NullException(unsigned int param_idx);
      /// Null item is passed in vector or array.
      /// \param[in] paramnIdx index of parameter.
      /// \param[in] elementIdx index of null item in array parameter.
      NullException(unsigned int param_idx, unsigned int item_idx);
      /// \return index of null parameter.
      unsigned int get_param_idx() const;
      /// \return index of null item in array parameter. Returns -1 if bad parrameter is not array with null item.
      unsigned int get_item_idx() const;
      virtual ~NullException() throw() {};
      NullException(const NullException & e);
    private:
      unsigned int param_idx, item_idx;
    };

    /// \brief Parameter length parameter exception.
    /// Internal.
    /// Exception occurs when some parameter has wrong length.
    class HERMES_API LengthException : public Exception
    {
    public:
      /// Two parameters do not have equal length.
      LengthException();
      /// A parameter has wrong length - simple case.
      /// \param[in] wrong actual length of parameter.
      /// \param[in] right right length of parameter.
      LengthException(unsigned int wrong, unsigned int right);
      /// One parameter has wrong length.
      /// \param[in] paramnIdx index wrong parameter.
      /// \param[in] wrong actual length of parameter.
      /// \param[in] right right length of parameter.
      LengthException(unsigned int param_idx, unsigned int wrong, unsigned int right);
      /// Two parameters should have same length and they dont have.
      /// \param[in] fstParamnIdx index first parameter.
      /// \param[in] sndParamnIdx index second parameter.
      /// \param[in] first actual length of first parameter.
      /// \param[in] second actual length of second parameter.
      LengthException(unsigned int fst_param_idx, unsigned int snd_param_idx, unsigned int first, unsigned int second);
      /// \return index of first wrong parameter.
      unsigned int get_first_param_idx() const;
      /// \return index of second wrong parameter. Returns -1 when only one parameter is wrong.
      unsigned int get_second_param_idx() const;
      /// \return length of first parameter.
      unsigned int get_first_length() const;
      /// \return expected length of first parameter.
      unsigned int get_expected_length() const;
      virtual ~LengthException() throw() {};
      LengthException(const LengthException & e);
    private:
      unsigned int fst_param_idx, snd_param_idx, wrong, right;
    };

    /// \brief Linear solver failed.
    class HERMES_API LinearMatrixSolverException : public Exception
    {
    public:
      /// \brief Linear solver failed from unknown reason.
      LinearMatrixSolverException();
      /// Linear solver failed from spevific reason.
      /// \param[in] reason specification of solver fail.
      LinearMatrixSolverException(const char * reason, ...);
      virtual ~LinearMatrixSolverException() throw() {};
      LinearMatrixSolverException(const LinearMatrixSolverException & e);
    };

    /// \brief Numeric value is out of allowed range
    class HERMES_API ValueException : public Exception
    {
    public:
      /// Value is greather or lower than allowed.
      /// \param[in] name name of variable
      /// \param[in] value value of variable
      /// \param[in] allowed allowed value (maximum or minimum)
      ValueException(const char * name, double value, double allowed);
      /// Value is out of range.
      /// \param[in] name name of variable.
      /// \param[in] value value of variable.
      /// \param[in] min minimum allowed value.
      /// \param[in] max minimum allowed value.
      ValueException(const char * name, double value, double min, double max);
      /// String value is not supported.
      ValueException(const char * name, std::string passed);
      /// \return bad value of variable.
      double get_value() const;
      /// return allowed value of variable.
      double get_allowed() const;
      virtual ~ValueException() throw() {};
      ValueException(const ValueException & e);
    private:
      double value, allowed;
    };

    /// \brief Method is not overriden and should be.
    class HERMES_API MethodNotOverridenException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      MethodNotOverridenException(const char * msg, ...);
      virtual  ~MethodNotOverridenException() throw() {};
      MethodNotOverridenException(const MethodNotOverridenException & e);
    };

    /// \brief Method is not overriden and should be.
    class HERMES_API MethodNotImplementedException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      MethodNotImplementedException(const char * msg, ...);
      virtual ~MethodNotImplementedException() throw() {};
      MethodNotImplementedException(const MethodNotImplementedException & e);
    };

    /// \brief Mesh failed to load.
    /// Thrown by Hermes2D::MeshReaderH2DXML, MeshReaderH2D
    class HERMES_API MeshLoadFailureException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      MeshLoadFailureException(const char * msg, ...);
      ~MeshLoadFailureException() throw() {};
      MeshLoadFailureException(const MeshLoadFailureException & e);
    };

    /// \brief Space failed to load.
    class HERMES_API SpaceLoadFailureException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      SpaceLoadFailureException(const char * msg, ...);
      virtual ~SpaceLoadFailureException() throw() {};
      SpaceLoadFailureException(const SpaceLoadFailureException & e);
    };

    /// \brief Solution failed to save.
    class HERMES_API SolutionSaveFailureException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      SolutionSaveFailureException(const char * msg, ...);
      virtual ~SolutionSaveFailureException() throw() {};
      SolutionSaveFailureException(const SolutionSaveFailureException & e);
    };

    /// \brief Solution failed to load.
    class HERMES_API SolutionLoadFailureException : public Exception
    {
    public:
      /// Constructor
      /// \param[in] name Name of the function.
      SolutionLoadFailureException(const char * msg, ...);
      virtual ~SolutionLoadFailureException() throw() {};
      SolutionLoadFailureException(const SolutionLoadFailureException & e);
    };
  }
}
#endif