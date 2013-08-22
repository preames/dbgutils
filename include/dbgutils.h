/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

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
