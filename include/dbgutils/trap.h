/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/** @file Defines the ENTER_DEBUGGER(_IF) macro family and the supporting 
    implementation. */
#ifndef __DBGUTILS_TRAP_H_
#define __DBGUTILS_TRAP_H_


/** The ENTER_DEBUGGER() and ENTER_DEBUGGER_IF(cond) macro statements provide
    a means to trap into a debugger from a particular point in source code.  
    This is accomplished by generating some form of "debug trap" - exactly 
    how depends on the implementation.  This is compatible with most debuggers
    but if your debugger is poorly implemented, you may not be able to safely
    resume execution after trapping into the debugger.  

    The DBGUTILS_ENABLE_ENTER_DEBUGGER and DBGUTILS_DISABLE_ENTER_DEBUGGER 
    macros can be used to control whether ENTER_DEBUGGER(_IF) is enabled.  By
    default, the ENTER_DEBUGGER(_IF) macros are only enabled when built with 
    the _DEBUG macro set (to reflect common practice for C/C++ projects).

    Note: The behavior of these macros are only well defined when the program 
    is being run under a debugger.  When run outside a debugger, the behavior
    you'll see is implementation specific.  Typically, your program will 
    terminate, but whether destructors will run or not is implementation 
    defined.

    Note: If you need to debug a process that can not have a debugger attached
    check out the debugger_barrier() mechanism to give you time to connect an
    external debugger when requested.
*/

#if (defined DBGUTILS_ENABLE_ENTER_DEBUGGER) && (defined DBGUTILS_DISABLE_ENTER_DEBUGGER)
#error "You can't define both the force enable and the force disable flag"
#endif

// If we're in debug mode, and neither override macro is set, default
// to enabling the enter debugger routines
#if (defined DBGUTILS_DEBUG_MACRO_DEFINED) && (!defined DBGUTILS_DISABLE_ENTER_DEBUGGER) && (!defined DBGUTILS_ENABLE_ENTER_DEBUGGER)
#define DBGUTILS_ENABLE_ENTER_DEBUGGER
#endif


/// These are the utilities that you should actually be using.
#ifdef DBGUTILS_ENABLE_ENTER_DEBUGGER
#define ENTER_DEBUGGER() __debug_trap()
#define ENTER_DEBUGGER_IF(exp) if( exp ) { ENTER_DEBUGGER(); } else {}
#else 
#define ENTER_DEBUGGER() do {} while(0)
#define ENTER_DEBUGGER_IF(exp) do {} while(0)
#endif //_DEBUG



// ---------------------------------------------------------------------
// ----IMPLEMENTATION - MOST USERS SHOULD IGNORE -----------------------
// ---------------------------------------------------------------------

/** This section exposes the raw implementation of the various trap 
    mechanisms used internally by ENTER_DEBUGGER(_IF).  Most users 
    should not use these.  They're intended for folks who want to 
    customize their own handlers for specific purposes.

    WARNING: This is implementation details.  None of the macro names, 
    function names, or other details are gauranteed to be preserved in
    future versions.  Use at your own risk!
*/


/// First, if this architecture defines an trap instruction, define the
/// function style macro DBGUTILS_TRAP_TO_DEBUGGER() to be the inline
/// asm block that encodes that instruction.  A trap instruction is
/// the standard mechanism used by most debuggers.  On Linux, a trap
/// instruction typically generates a SIGTRAP which a debugger can
/// respond to.  If this macro is not defined, a different mechanism
/// (such as spinning in a debugger barrier) must be used instead.
/// Note: Since inline assembly is nicely compiler specific, we need both 
/// compiler and architecture guards here.  Joy.
#ifdef __GNUC__ //GAS assembler syntax
#if (defined __i386__) || (defined __x86_64__) //x86/x86-64 architecture
/// This is the appropriate interrupt code for much of the x86 family.  
/// I do not know which version this was introduced in, but I believe
/// it is pre 8086.  As a result, this should work on most any x86 machine.
#define DGBUTILS_TRAP_TO_DEBUGGER() asm volatile ("int3;")
#endif
// Note: If you work on one of this architectures, please contribute
// patches back!
// TODO: Other architectures to support:
// Itanium:  __IA64__
// ARM: __arm__ or __thumb__ (as appropriate)
// Note: These two are a bit deceptive since the same file can mix
// arm and thumb code.  How should that be handled?
#endif
//TODO: OTher compiler families it would be nice to support
// XCode: __APPLE__
// Microsoft: _MSC_VER (also gets Intel since it's compatible)

// If you expect there to be a debug trap instruction available
// uncomment the following
//#ifndef DGBUTILS_TRAP_TO_DEBUGGER
//#error "No debug trap instruct available"
//#endif

/// Another option is to use a OS specific function to raise a debug
/// trap.  This is slightly more dangerous since the semantics of the
/// functions vary substaintially between platforms.  I believe the
/// difference in behavior is mostly when run outside a debugger, but
/// none-the-less, the platform dependence is scary. For example, 
/// DebugBreak on Windows will act like a thrown exception outside of
/// a debugger.  raise(SIGTRAP) on Linux will usual terminate the 
/// program without allowing exception hanlders to run or object 
/// destruction to occur.  (Also, SIGTRAP is not defined by the C++
/// standard; I am unsure on exactly which platforms it's defined.)  
/// I strong suggest avoiding this if possible.
#if (defined __linux__) || (defined _WIN32) 
// We only know how to define these for two platforms
//TODO: does this work on Android?
#ifdef __cplusplus
extern "C"
#endif
void dbgutils_system_debug_trap_function();
#define DBGUTILS_SYSTEM_DEBUG_TRAP() dbgutils_system_debug_trap_function()
#endif



/// Spin in a tight loop until manually released by a user changing
/// a special variable using their debugger.  This is one of the
/// more effective ways to allow state inspection in a debugger
/// without support for debug trap instructions or when the program
/// can't normally be run in a debugger
#ifdef __cplusplus
extern "C" {
#endif
void dbgutils_debugger_barrier();
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
namespace dbgutils {
  void debugger_barrier();
}
#endif

/// This function abstracts away the details of whether a debug trap
/// instruction is available, the system trap routine is available, 
/// or if you must spin on barrier variable. In the worst case where
/// neither option is available, you may need to manually set a 
/// breakpoint on this function in your debugger.
#ifdef __cplusplus
extern "C" {
#endif
  __attribute__((noinline))
  void __debug_trap();
#ifdef __cplusplus
}
#endif
#define DBGUTILS_CALL_DEBUG_TRAP_FUNC() __debug_trap()

// One obvious question is why not simply use __builtin_trap() on
// GCC-like compilers?  __builtin_trap triggers a program crash, not
// a recoverable trap.  You can use it to enter the debugger once, but
// not resume execution again afterwards.

#endif //__DBGUTILS_TRAP_H_
