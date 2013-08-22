/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/

#ifndef __DBGUTILS_PARTIAL_H
#define __DBGUTILS_PARTIAL_H

#ifndef __DBGUTILS_ASSERT_H
// For now, we use the implementation details of assert
#error "assert.h must be included before this header"
#endif

//TODO: debugger breakpoint insertion
//TODO: backtrace shown
//TODO: give the option of looping on abort

// TODO: introduce assertion throwing default versions for unimplemented and unreachable
// TODO: add a _MSG variant of each

// Three constructs: unimplemented (fatal or warn), untested (warn), unreachable (fatal) 

#ifdef __cplusplus
#include <exception>

namespace dbgutils {
  class unimplemented_error: public error {
    virtual const char* what() const throw() {
      return "Attempt to execute unimplement code";
    }
  };

  class untested_error: public error {
    virtual const char* what() const throw() {
      return "Attempt to implement untested code";
    }
  };
}
#endif

// The convention here is that the base version does something sane
// based on the global configuration.  The _FATAL, _WARN, _THROW 
// versions ignore the global settings and do exactly what was requested.

//TODO: differentiate c, vs c++ defaults
#define DBGUTILS_UNIMPLEMENTED() DBGUTILS_UNIMPLEMENTED_FATAL()
#define DBGUTILS_UNIMPLEMENTED_WARN() do { dbgutils_assert_noabort_fail("unimplemented reached", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);
#define DBGUTILS_UNIMPLEMENTED_FATAL() do { dbgutils_assert_abort_fail("unimplemented reached", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);


#define DBGUTILS_UNTESTED() DBGUTILS_UNTESTED_WARN()
#define DBGUTILS_UNTESTED_WARN() do { dbgutils_assert_noabort_fail("not yet tested", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);
#define DBGUTILS_UNTESTED_FATAL() do { dbgutils_assert_abort_fail("not yet tested", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);

#endif //__DBGUTILS_PARTIAL_H
