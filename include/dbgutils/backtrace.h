/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
