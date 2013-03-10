/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring> //strcmp

#ifndef NO_LIBUNWIND 
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#endif

#include "dbgutils.h"

using namespace dbgutils;


namespace {
  //an internal buffer used to try to avoid allocation
  // during backtracing.  We want to avoid allocation
  // so this can be called during init or after exit
  // from main with errors.  
  // Note: This isn't perfect, but
  // it's better than printf.  TODO.  
  char print_buffer[500];
}

extern "C" {
  void dbgutils_print_backtrace (void) {
#ifndef NO_LIBUNWIND 
    unw_cursor_t cursor; unw_context_t uc;
    unw_word_t ip, sp;
    int i;
    
    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    for(i = 0; unw_step(&cursor) > 0; i++) {
      //  while () {
      char buf[200];
    
      unw_get_proc_name(&cursor, buf, 200, NULL);
      unw_get_reg(&cursor, UNW_REG_IP, &ip);
      unw_get_reg(&cursor, UNW_REG_SP, &sp);
      snprintf(print_buffer, 500, 
               "%s, ip = %lx, sp = %lx\n", buf, (long) ip, (long) sp);
      print_buffer[499] = '\0';
      fprintf(stderr, "%s", print_buffer);
    }
    fprintf(stderr, "%s", "\n");
#else //NO_LIBUNWIND
    fprintf(stderr, "Backtrace unavailable on this platform due to lack of libundwind\n");
#endif
  }

  void dbgutils_exit_with_backtrace (int status) {
    print_backtrace();
    exit(status);
  }

  void dbgutils_abort_with_backtrace() {
    print_backtrace();
    abort();
  }
}
namespace dbgutils {
  void print_backtrace() { dbgutils_print_backtrace(); }
  void exit_with_backtrace(int status) { dbgutils_exit_with_backtrace(status); }
  void abort_with_backtrace() { dbgutils_abort_with_backtrace(); };
}

namespace {
  void print_assertion_failure_message(const char* exp, const char* file,
                                       unsigned line, const char* func) {
    snprintf(print_buffer, 500,
             "Assertion Failure at %s:%d in %s\n", file, line, func);
    print_buffer[499] = '\0';
    fprintf(stderr, "%s\n", print_buffer);

    snprintf(print_buffer, 500,
             "\tExpression: %s\n", exp);
    print_buffer[499] = '\0';
    fprintf(stderr, "%s\n", print_buffer);
  }
}

#include <cstdlib>
#include <map>
#include <string>
namespace {
  //IMPORTANT: DO NOT ALLOCATE
  // Note: The assertion functions can be called from places where
  // allocating memory via malloc would be _bad_.  (i.e. inside the
  // allocator, before init, after shutdown, etc..)  DO NOT EVER
  // allocate dynamic memory here.

  bool get_boolean_environment_variable(const char* name, 
                                        bool def = false) {
    const char* env_cstr = getenv(name);
    const char* def_cstr = def ? "true" : "false";
    const char* val = env_cstr ? env_cstr : def_cstr; 
    if( 0 == strcmp(val, "true") ) {
      return true;
    } else if ( 0 == strcmp(val, "false") ) {
      return false;
    } else {
      //unrestricted printf allocates
      puts("Unrecognized value for '");
      puts(name);
      puts("' environment variable.  ('true' or 'false' expected)\n");
      return def;
    }
  }

  bool should_print_backtrace_on_assert_failure() {
    return get_boolean_environment_variable("print_backtrace_on_assert_failure", true);
  }
  bool should_enter_debugger_on_assert_failure() {
    return get_boolean_environment_variable("enter_debugger_on_assert_failure", true);
  }
  bool should_abort_on_assert_failure() {
    return get_boolean_environment_variable("abort_on_assert_failure", true);
  }

}
//TODO: It would be nice to have a full release mode which
// prints no information and just exits.  (i.e. security)
void dbgutils_assert_fail(const char* exp, const char* file,
                          unsigned line, const char* func) {
  //defaults to aborting
  if( should_abort_on_assert_failure() ) {
    dbgutils_assert_abort_fail(exp, file, line, func);
  } else {
    dbgutils_assert_noabort_fail(exp, file, line, func);
  }
}
void dbgutils_assert_abort_fail(const char* exp, const char* file,
                                unsigned line, const char* func) {
  print_assertion_failure_message(exp, file, line, func);
  if( should_print_backtrace_on_assert_failure() ) //default: true
    print_backtrace();
  if( should_enter_debugger_on_assert_failure() ) //default: true
    ENTER_DEBUGGER();
  abort();
}
void dbgutils_assert_noabort_fail(const char* exp, const char* file,
                                  unsigned line, const char* func) {
  print_assertion_failure_message(exp, file, line, func);
  if( should_print_backtrace_on_assert_failure() ) //default: true
    print_backtrace();
  if( should_enter_debugger_on_assert_failure() ) //default: true
    ENTER_DEBUGGER();
}

namespace dbgutils {
  //TODO: some of these print codes aren't write
  void dump(char v) {
    printf("%c", v);
    fflush(stdout);
  }
  void dump(short v) {
    printf("%d", v);
    fflush(stdout);
  }
  void dump(int v) {
    printf("%d", v);
    fflush(stdout);
  }
  void dump(long v) {
    printf("%ld", v);
    fflush(stdout);
  }
  void dump(unsigned long v) {
    printf("%lu", v);
    fflush(stdout);
  }
  void dump(long long v) {
    printf("%lld", v);
    fflush(stdout);
  }
  void dump(float v) {
    printf("%f", v);
    fflush(stdout);
  }
  void dump(double v) {
    printf("%lf", v);
    fflush(stdout);
  }
  void dump(long double v) {
    printf("%Lf", v);
    fflush(stdout);
  }
  void dump(const char* s) {
    printf("%s", s);
    fflush(stdout);
  }
}
