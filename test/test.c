/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#define _DEBUG
#include "dbgutils.h"

int main() {
  ENTER_DEBUGGER_IF( 0 );
  ENTER_DEBUGGER_IF( 1 );
  ENTER_DEBUGGER();

  dbgutils_debugger_barrier();

#ifdef DGBUTILS_TRAP_TO_DEBUGGER
  DGBUTILS_TRAP_TO_DEBUGGER();
#endif

#ifdef DBGUTILS_SYSTEM_DEBUG_TRAP
  DBGUTILS_SYSTEM_DEBUG_TRAP();
#endif

  DBGUTILS_CALL_DEBUG_TRAP_FUNC();

  DBGUTILS_ASSERT(1);
  DBGUTILS_ASSERT_ABORT(1);
  DBGUTILS_ASSERT_NOABORT(1);
  DBGUTILS_EXPECT(1);

  dbgutils_exit_with_backtrace(0);
}
