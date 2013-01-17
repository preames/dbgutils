/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

//__STRING comes from GCC headers (I think - model after GNU assert.h)
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
