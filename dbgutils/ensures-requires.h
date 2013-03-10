/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __DBGUTILS_ENSURES_REQUIRES_H__
#define __DBGUTILS_ENSURES_REQUIRES_H__

/// Define a precondition that is required by a given method
/// should only be used at the beginning of a method or function.
#define DBGUTILS_REQUIRES(exp) do { DBGUTILS_ASSERT(exp); } while(0)

/// ensures only available under C++0x
#ifdef __cplusplus

// TODO: Can we forward define this?  It would be really nice...
#include <functional>

#define __CLOSURE(exp) ( [&]() { return (exp); } )

// Define a helper class which runs a closure (passed as an boolean 
// function object) at destruction - i.e. function exit. 
namespace dbgutils {
  namespace __impl {
    struct __ensures_on_exit_t {
      std::function<bool(void)> m_func;
      explicit inline __ensures_on_exit_t(std::function<bool(void)> closure ) : m_func(closure) {}
      inline ~__ensures_on_exit_t() { DBGUTILS_ASSERT( m_func() ); }
    };
  }
}

#define __CONCAT2_IMPL(A, B) A ## B
#define __CONCAT2(A, B) __CONCAT2_IMPL(A,B)


/** Define a post condition that must be true on exit from a given method.
    The variables used in the expresion will be captured and the expression
    evaluated at scope (function) exit.  If the condition is not met, an 
    assertion violation will occur (likely terminating the program.)

    If you need to refer to the return value, you must declare a variable
    before the ensures clause and explicitly name it yourself.  There is
    no magic handling for the old values of variables either.  

    int rval;
    DBGUTILS_ENSURES( rval > 0 );

    WARNING: Do NOT declare inside an inner scope, you will not get the
    results you expect.
*/
//TODO: should capture the file, line, and function information for better reorting of errors.
#define DBGUTILS_ENSURES(exp) dbgutils::__impl::__ensures_on_exit_t __CONCAT2(__ensures__,__LINE__)( __CLOSURE(exp) )

#endif

#endif
