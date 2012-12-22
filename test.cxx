/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

  dbgutils::exit_with_backtrace(0);
}
