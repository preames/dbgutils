/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/

#define _DEBUG
#include "dbgutils.h"

using namespace dbgutils;

struct dump_me {
  int i;
  float f;
  void __dump__() const {
    printf("dump_me.__dump__ called\n");
    fflush(stdout);
  }
};

DBGUTIL_HAS_DUMP_MEMBER(dump_me);

int main() {
  dump( (char)5 );
  dump( (short)5 );
  dump( (int)5 );
  dump( (long)5 );
  dump( (long long)5 );
  dump( 5.0f );
  dump( 5.0 ); //double, default
  dump( 5.0L ); //long double
  dump( 5 );
  dump( "--" );

  int a[2];
  a[0] = 1;
  a[1] = 2;
  dump_array(a, 2);
  dump_array(a);
  dump(a);

  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  dump(v);

  dump_me o;
  dump(o);

  ENTER_DEBUGGER_IF(false);
  ENTER_DEBUGGER_IF(true);
  ENTER_DEBUGGER();

  dbgutils_debugger_barrier();
  dbgutils::debugger_barrier();

#ifdef DGBUTILS_TRAP_TO_DEBUGGER
  DGBUTILS_TRAP_TO_DEBUGGER();
#endif

#ifdef DBGUTILS_SYSTEM_DEBUG_TRAP
  DBGUTILS_SYSTEM_DEBUG_TRAP();
#endif

  DBGUTILS_CALL_DEBUG_TRAP_FUNC();


  DBGUTILS_ASSERT(true);
  DBGUTILS_ASSERT_ABORT(true);
  DBGUTILS_ASSERT_NOABORT(true);
  DBGUTILS_EXPECT(true);


  dbgutils::exit_with_backtrace(0);
}
