/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/

#ifndef __DBGUTILS_UNREACHABLE_H
#define __DBGUTILS_UNREACHABLE_H

#ifndef __DBGUTILS_ASSERT_H
// For now, we use the implementation details of assert
#error "assert.h must be included before this header"
#endif

//TODO: debugger breakpoint insertion
//TODO: backtrace shown
//TODO: give the option of looping on abort

// TODO: introduce assertion throwing default versions for unimplemented and unreachable
// TODO: add a _MSG variant of each

#define DBGUTILS_UNREACHABLE() DBGUTILS_UNREACHABLE_FATAL()
#define DBGUTILS_UNREACHABLE_WARN() do { dbgutils_assert_noabort_fail("unimplemented reached", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);
#define DBGUTILS_UNREACHABLE_FATAL() do { dbgutils_assert_abort_fail("unimplemented reached", __FILE__, __LINE__, DBGUTILS_FUNCTION_MACRO); } while(0);

#endif //__DBGUTILS_PARTIAL_H
