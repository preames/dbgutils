/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/

#ifndef __DBGUTILS_ASSERT_H
#define __DBGUTILS_ASSERT_H
//TODO: add noreturn attributes to exit, abort, assert_abort

//TODO: debugger breakpoint insertion
//TODO: backtrace shown
//TODO: give the option of looping on abort
/** These assertion functions will trigger if the condition given does not
    hold.  All with print an error message.  The _ABORT variant will 
    terminate the program.  The EXPECT and _NOABORT will return to normal
    execution.  The plain ASSERT variant defaults to aborting, but this 
    behavior can be controlled by the environment variable "".
    Note: The plain ASSERT form should not be used where checking an
    environmental variable is not legal.  (For example during global object
    construction or destruction, inside a memory allocator, etc..) */

#ifdef __cplusplus
namespace dbgutils {
  class assertion_error: public error {
    // TODO: fill out
    virtual const char* what() const throw() {
      return "Assertion failure";
    }
  };
}
#endif

//TODO: add branch hints here
#define __DBGUTILS_STRING(exp) #exp
#define DBGUTILS_ASSERT(exp) if(!(exp)) { dbgutils_assert_fail(__DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } else {}
#define DBGUTILS_ASSERT_ABORT(exp) if(!(exp)) { dbgutils_assert_abort_fail(__DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } else {}
#define DBGUTILS_ASSERT_NOABORT(exp) if(!(exp)) { dbgutils_assert_noabort_fail(__DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } else {}
#define DBGUTILS_EXPECT(exp) if(!(exp)) { dbgutils_assert_noabort_fail(__DBGUTILS_STRING(exp), __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } else {}

#ifdef __cplusplus
extern "C" {
#endif
  void dbgutils_assert_fail(const char* exp, const char* file,
                            unsigned line, const char* func);
  void dbgutils_assert_abort_fail(const char* exp, const char* file,
                                  unsigned line, const char* func);
  void dbgutils_assert_noabort_fail(const char* exp, const char* file,
                                    unsigned line, const char* func);


  // If this library is being used inside a malloc
  // implementation, nasty things can happen if our stack
  // walker or assert functions directly or indirectly call
  // malloc.  If this is your use case, make sure you call
  // this routine with a non-zero value before any possible
  // call to the other functions/macros in this library.
  // Note: This does a best effort, but the library should
  // ALWAYS abort cleanly if a reentry situation does 
  // happen.  If you find an exception, please file a bug.
  int dbgutils_config_avoid_malloc(int value);

#ifdef __cplusplus
} //end extern "C"
#endif

//The idea for the following was taken from GNU libc cassert.h
//TODO: need GNU check here
#ifdef __cplusplus
# define DBGUTILS_FUNCTION_MACRO __PRETTY_FUNCTION__
#else
# if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#  define DBGUTILS_FUNCTION_MACRO 	__func__
# else
#  define DBGUTILS_FUNCTION_MACRO "n/a"
# endif
#endif



#endif //__DBGUTILS_ASSERT_H
