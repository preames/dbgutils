/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#ifndef __DBGUTILS_ENSURES_REQUIRES_H__
#define __DBGUTILS_ENSURES_REQUIRES_H__

/// Define a precondition that is required by a given method
/// should only be used at the beginning of a method or function.
#define DBGUTILS_REQUIRES(exp) if( !(exp) ) { dbgutils_requires_fail(__DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } else {}

/// ensures only available under C++0x
#ifdef __cplusplus

void dbgutils_ensures_fail(const char* exp, const char* file,
                           unsigned line, const char* func);
void dbgutils_requires_fail(const char* exp, const char* file,
                             unsigned line, const char* func);

// TODO: Can we forward define this?  It would be really nice...
#include <functional>

#define __CAPTURE(exp) ( [&]() -> bool { return (exp); } )

// Define a helper class which runs a closure (passed as an boolean 
// function object) at destruction - i.e. function exit. 
namespace dbgutils {
  namespace __impl {
    struct __ensures_on_exit_t {
      // The callable function which captures the condition to check on 
      // scope exit.  
      std::function<bool(void)> m_func;
      /// Metadata about the declaration site
      const char* m_exp;
      const char* m_file;
      const unsigned m_line;
      const char* m_funcname;

      explicit inline __ensures_on_exit_t(std::function<bool(void)> closure,
                                          const char* exp, const char* file,
                                          unsigned line, const char* func )
        : m_func(closure), m_exp(exp), m_file(file),
          m_line(line), m_funcname(func) {}
      inline ~__ensures_on_exit_t() {
        //TODO: should really capture the line and location
        // of the original expression.  Asserting on the result
        // here isn't the easiest thing to backtrace to the
        // ensures clause - and then from there to the branch 
        // which actually failed.
        if( !m_func() ) {
          dbgutils_ensures_fail(m_exp, m_file, m_line, m_funcname);
        } 
      }
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
#define DBGUTILS_ENSURES(exp) dbgutils::__impl::__ensures_on_exit_t __CONCAT2(__ensures__,__LINE__)( __CAPTURE(exp), __DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO )

#endif

#endif
