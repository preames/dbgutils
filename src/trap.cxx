/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#include "dbgutils/trap.h"

using namespace dbgutils;

namespace dbgutils {
  void debugger_barrier() { dbgutils_debugger_barrier(); }
}


namespace dbgutils {
  volatile bool g_spin_in_trap = true;
}
void dbgutils_debugger_barrier() {
  using namespace dbgutils;
  //This may seem odd - The purpose of the code is to
  // spin forever (so that a debugger can attach), but to give
  // the debugger a means to continue.  If you want to continue
  // after debugging this issue, use your debugger to change
  // the variable g_spin_in_trap to false.  It will then exit the loop
  // and reset the flag so it spins next time.
  while(g_spin_in_trap) {}
  g_spin_in_trap = true;
}

#ifdef __linux__
#include <csignal> //raise. SIGTRAP
__attribute__((noinline))
void dbgutils_system_debug_trap_function() {
  // For reasons unknown, using raise(SIGTRAP)
  // may screw up your stack trace.  In particular,
  // on x86_64 Ubuntu it appears to skip right over the this 
  // entire function (and the function below it)
  raise(SIGTRAP);
}
#else
//prefer the raise(SIGTRAP) variant if we weirdly have both
#ifdef _WIN32
#include "Windows.h"
// The code below should work on Windows, but I haven't
// compiled or tested it to make sure.
#warning "Please confirm the following code works on Windows. It is untested."
void dbgutils_system_debug_trap_function() {
  DebugBreak();
}
#endif 
#endif
//There's supposidly a "Debugger();" function on Apple platforms, but I can't find any documentation of this.  Patches welcome.


__attribute__((noinline))
void __debug_trap()  {
#ifdef DGBUTILS_TRAP_TO_DEBUGGER
  //TODO: Consider whether it might be good to try to clear registers here
  // and possibly insert some noops on either side of the critical section.
  // If the debugger doesn't get things quite right, might be nice to have
  // some tolerance.  (Maybe a flush too?)
  DGBUTILS_TRAP_TO_DEBUGGER();
#else
# ifdef DBGUTILS_SYSTEM_DEBUG_TRAP
  DBGUTILS_SYSTEM_DEBUG_TRAP();
# else
#  ifndef DISABLE_SPIN_ON_TRAP
#   warning "Using a debugger_barrier (an infinite loop with an escape) is the only option for implementing ENTER_DEBUGGER(_IF).  You'll need to manually clear the gate variable to continue execution."
  fprintf(stderr, "debug trap triggered; waiting for debugger connection\n");
  debugger_barrier();
#  else
  // We don't have a means to automatically trap into the debugger,
  // and you've chosen not to spin waiting for a probe.  If you
  // want to actually be able to inspect the state, the only
  // remaining option is to set a breakpoint on this function.  
  // It is your responsibility to manually set that breakpoint.
#   warning "dbgutils could not establish an implementation for ENTER_DEBUGGER().  Unless you manually set a breakpoint on __debug_trap(), ENTER_DEBUGGER will be a noop."
#  endif
# endif
#endif

  //In general, we try to continue from a debug trap.  Some of
  // the instructions used don't always make this possible though.
}



