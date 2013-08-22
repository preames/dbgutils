/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#ifndef __DBGUTILS_BACKTRACE_H
#define __DBGUTILS_BACKTRACE_H

#ifdef __cplusplus
extern "C" {
#endif
  /** Print a backtrace (i.e. all of the stack frames invoked to reach
      the call site) to stderr. */
  void dbgutils_print_backtrace();
  /** Print a backtrace and then exit with the given status. */
  void dbgutils_exit_with_backtrace(int status) __attribute__ ((noreturn));
  /** Print a backtrace and then abort. */
  void dbgutils_abort_with_backtrace() __attribute__ ((noreturn));
#ifdef __cplusplus
} //end extern "C"
#endif

#ifdef __cplusplus
namespace dbgutils {
  void print_backtrace();
  void exit_with_backtrace(int status) __attribute__ ((noreturn));
  void abort_with_backtrace() __attribute__ ((noreturn));
}
#endif

#endif //__DBGUTILS_BACKTRACE_H
