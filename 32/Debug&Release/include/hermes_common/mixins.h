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
/*! \file mixins.h
\brief Mix-in classes for one functionality, for various classes to be derived from.
*/
#ifndef __HERMES_COMMON_MIXINS_H
#define __HERMES_COMMON_MIXINS_H

#include "common.h"
#include "exceptions.h"
#include "api.h"

namespace Hermes
{
  /** \defgroup g_mixins Mixins
  *  \brief Mixins are utility classes used for all kinds of other classes.
  *
  *  Mixin classes provide a single piece of functionality.
  *
  */

  /// \ingroup g_mixins
  /// \brief Namespace for mixin classes.
  /// These classes always serve one particular purpose that multiple classes of the entire Hermes library
  /// could use - logging, time measurement, ...
  namespace Mixins
  {
    /// \ingroup g_mixins
    /// Mixin that allows for asking about the instance state (ok / not ok).
    class HERMES_API StateQueryable
    {
    public:
      /// Ask if the instance is fine.
      virtual bool isOkay() const = 0;

      /// Get class name, for the purpose of messaging.
      virtual std::string getClassName() const = 0;

      /// Method to handle the state.
      void check() const;
    };

    /// \brief Class the output of which is loggable, i.e. that uses functionality of info(), warn()
    /// Contains the class Static with the following usage:
    /// Anywhere in your program you can write Hermes::Mixins::Loggable::Static::info("whatever you want to output").
    class HERMES_API Loggable
    {
    private:
      typedef void(*callbackFn)(const char*);

    public:
      Loggable(bool verbose_output = false, callbackFn verbose_callback = NULL, bool add_newline = true);

      void set_file_output_only(bool onOff);
      /// Sets the addition of a time stamp on each line in the log file. By default it is on.
      void set_timestamps(bool onOff);
      /// Sets the logFile being always erased before logging.
      void set_erase_on_beginning(bool onOff);
      void set_logFile_name(const char* filename);
      void set_logFile_name(std::string filename);
      static void set_static_logFile_name(const char* filename);
      static void set_static_logFile_name(std::string filename);

      void info(const char* msg, ...) const;
      void info_if(bool cond, const char* msg, ...) const;
      void warn(const char* msg, ...) const;
      void warn_if(bool cond, const char* msg, ...) const;
      void error(const char* msg, ...) const;
      void error_if(bool cond, const char* msg, ...) const;

      /// Sets the attribute verbose_output to the paramater option passed.
      /// \todo Use this in solvers etc.
      virtual void set_verbose_output(bool to_set);

      /// Returns the current value of verbose_output;
      bool get_verbose_output() const;

      /// Provides a callback for logging.
      /// \param[in] callback Function to be called for the messaging when verbose_output is set to yes.
      /// \todo Use this in solvers etc.
      virtual void set_verbose_callback(callbackFn callback);

      /// Returns the current value of verbose_callback;
      callbackFn get_verbose_callback() const;

      /// For static logging.
      class HERMES_API Static
      {
      public:
        static void info(const char* msg, ...);
        static void warn(const char* msg, ...);
        static void error(const char* msg, ...);
      };

      /// Logfile name.
      char* logFileName;
      static char* staticLogFileName;
    protected:

      /* file operations */
      void hermes_fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream) const;
      void hermes_fread(void* ptr, size_t size, size_t nitems, FILE* stream) const;

    private:
      /// Writes a fancy formatted text to a console. \internal \ingroup g_logging
      /** \param[in] code An event code, e.g., ::HERMES_EC_ERROR.
      *  \param[in] text A message. A C-style string.
      *  \return True if the message was written. False if it failed due to some reasone. */
      bool write_console(const char code, const char* text) const;

      /// Info about a log record. Used for output log function. \internal
      class HERMES_API HermesLogEventInfo
      {
      public:
        HermesLogEventInfo(const char code, const char* src_function, const char* src_file, const int src_line);
        /// An event code character. For defails see event characters, e.g., ::HERMES_EC_ERROR
        const char code;
        /// A name of a function/method at which the event was generated.
        const char* src_function;
        /// A source file at which the event was generated.
        const char* src_file;
        /// A line in the source file at which the event was generated.
        const int src_line;
      };

      HermesLogEventInfo* hermes_build_log_info(char event) const;

      static std::map<std::string, bool> logger_written;

      /// \brief Logs an event if the condition is true. \internal
      /** Used by all even logging macros. Since this function returns a copy of the parameter cond,
      *  it can be used to call a function hermes2d_exit_if() or a function(). Thanks to that, the macro
      *  behaves as a function rather than a block of code. Also, this allows a debugger to a particular
      *  code.
      *  \param[in] code Code of the message.
      *  \param[in] msg A message. */
      void hermes_log_message(const char code, const char* msg) const;

      /// Verbose output.
      /// Set to 'true' by default.
      bool verbose_output;

      /// Only output to file - not to console.
      bool file_output_only;

      /// Verbose callback.
      callbackFn verbose_callback;

      /// Print timestampts.
      bool print_timestamps;

      /// Erase the file on the beginning.
      bool erase_on_beginning;

      /// Internal.
      bool log_file_written;

      bool add_newline;
    };

    /// \brief Class using time measurement
    /// Can be used directly (is not abstract), so one can use e.g. this in a program:
    /// Mixins::TimeMeasurable time;
    /// time.tick();
    /// <-- do whatever you want to measure execution time of -->
    /// std::cout << "Whatever took " << time.last() << "seconds to execute.";
    class HERMES_API TimeMeasurable
    {
    public:
      /// Constructs internal structures and starts measuring.
      TimeMeasurable(const char *name = nullptr);

      /// Tick type. Used by the class Hermes::TimePeriod.
      enum TimerPeriodTickType
      {
        HERMES_ACCUMULATE, ///< Accumulate a period between ticks.
        HERMES_SKIP ///< Skip period between ticks, i.e., do not accumulate it.
      };

      /// Resets accumulated time.
      const TimeMeasurable& reset();
      /// Starts a new_ period and resets accumulated time.
      const TimeMeasurable& tick_reset();
      /// Starts/ends a new_ period.
      const TimeMeasurable& tick(TimeMeasurable::TimerPeriodTickType type = HERMES_ACCUMULATE);

      /// Returns a name of the time period if any.
      const std::string& name() const;

      /// Returns accumulated time (in seconds).
      double accumulated() const;

      /// Returns accumulated time in human readable form.
      std::string accumulated_str() const;

      /// Returns last measured period (in seconds).
      /** \return Returns the length of the last measured time period. -1 if period was skipped. */
      double last() const;

      /// Returns last measured period in human readable form.
      std::string last_str() const;

    private:
#ifdef _WINDOWS //Windows
      typedef uint64_t SysTime;
      /// Frequency of the performance timer. If zero, no hi-res timer is supported. (Win32 only)
      double frequency;
#else //Linux
      typedef timespec SysTime;
#endif
      /// Name of the timer (can be empty)
      const std::string period_name;
      /// Time of the last measured period.
      double last_period;
      /// Time when the timer was started/resumed (in platform-dependent units).
      SysTime last_time;
      /// Time accumulator (in seconds).
      double accum;

      /// Returns current time (in platform-dependent units).
      SysTime get_time() const;
      /// Calculates distance between times (in platform specific units) and returns it in seconds.
      double period_in_seconds(const SysTime& begin, const SysTime& end) const;
      /// Converts time from seconds to human readable form.
      std::string to_string(const double time) const;
    };

    /// \brief Class that allows overriding integration order in its discrete problems
    /// Internal
    class HERMES_API IntegrableWithGlobalOrder
    {
    public:
      IntegrableWithGlobalOrder();
      /// \todo Use this in solvers etc.
      virtual void set_global_integration_order(unsigned int order);
      bool global_integration_order_set;
      unsigned int global_integration_order;
    };

    /// \brief Class that allows overriding integration order in its discrete problems
    /// Internal
    class HERMES_API SettableComputationTime
    {
    public:
      SettableComputationTime();
      /// set time information for time-dependent problems.
      virtual void set_time(double time);
      virtual void set_time_step(double time_step);
      double time;
      double time_step;
    };

    /// \brief Class that allows for attaching any method to particular parts of its functionality.
    /// Internal
    class HERMES_API OutputAttachable
    {
    public:
      OutputAttachable();
      /// \return Whether or not should the processing continue.
      virtual bool on_initialization();
      /// \return Whether or not should the processing continue.
      virtual bool on_step_begin();
      /// \return Whether or not should the processing continue.
      virtual bool on_initial_step_end();
      /// \return Whether or not should the processing continue.
      virtual bool on_step_end();
      /// \return Whether or not should the processing continue.
      virtual bool on_finish();

      template<typename T>
      class Parameter
      {
      private:
        T* value;
        friend class OutputAttachable;
      };

      template<typename T>
      const T& get_parameter_value(const Parameter<T>& parameter);

      template<typename T>
      T& get_parameter_value(Parameter<T>& parameter);

    protected:
      template<typename T>
      void set_parameter_value(Parameter<T>& parameter, T* value);
    };
  }

  typedef Hermes::Mixins::OutputAttachable::Parameter<unsigned int> OutputParameterUnsignedInt;
  typedef Hermes::Mixins::OutputAttachable::Parameter<double> OutputParameterDouble;
  typedef Hermes::Mixins::OutputAttachable::Parameter<bool> OutputParameterBool;

  typedef Hermes::Mixins::OutputAttachable::Parameter<std::vector<unsigned int> > OutputParameterUnsignedIntVector;
  typedef Hermes::Mixins::OutputAttachable::Parameter<std::vector<double> > OutputParameterDoubleVector;
  typedef Hermes::Mixins::OutputAttachable::Parameter<std::vector<bool> > OutputParameterBoolVector;
}
#endif
