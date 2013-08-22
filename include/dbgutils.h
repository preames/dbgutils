/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __DBGUTILS_H
#define __DBGUTILS_H

// Make sure conflicting definitions of macros aren't being used and abort
// the build cleanly if found.
#include "dbgutils/macro-sanity.h"

// Includes functionality to trap into the debugger from
// a given statement in source code.
#include "dbgutils/trap.h"

// Routines for printing a stacktrace of the current thread
// and some special abort/exit routines to print stacktraces
// before termination.
#include "dbgutils/backtrace.h"


#ifdef __cplusplus
#include <exception>
namespace dbgutils {
  class error: public std::exception {
    virtual const char* what() const throw() {
      return "Unspecified dgbutils::error occurred";
    }
  };
}
#endif

// Special assertion macros (similar to cstdlib's assert.h) 
// with additional functionality like optionally continuing, 
// printing backtraces, or breaking into the debugger.
#include "dbgutils/assert.h"

// Macros to support a test driven style of development where
// parts of programs may be unimplemented or untested while
// other parts are the focus.  Using these macros ensures
// that unimplemented sections are self documenting and that
// execution of an unimplemented block fails loudly.
#include "dbgutils/partial.h"

// Define an unreachable construct used to indicate a particular
// line should be impossible to execute.  Used to assist compiler
// analysis and terminate execution forcefully to prevent cascading
// failures and corruption.
#include "dbgutils/unreachable.h"

// Handling for function precondition (ensures) and post conditions
// (ensures) being declared at the top of function (inside the body 
// brackets) and checking them at runtime.
#include "dbgutils/ensures-requires.h"

// Routines for dumping the contents of pretty much anything
// Currently C++ only
#include "dbgutils/dump.h"

#endif //__DBGUTILS_H
