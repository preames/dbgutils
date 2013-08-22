/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
