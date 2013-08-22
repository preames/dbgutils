/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __DBGUTILS_MACRO_SANITY_H_
#define __DBGUTILS_MACRO_SANITY_H_


#if (defined DEBUG) || (defined _DEBUG) || (defined __DEBUG) || (defined __DEBUG__)
#define DBGUTILS_DEBUG_MACRO_DEFINED
#endif

#if (defined NDEBUG) || (defined _NDEBUG) || (defined __NDEBUG) || (defined __NDEBUG__) || (defined NODEBUG) || (defined _NODEBUG) || (defined __NODEBUG) || (defined __NODEBUG__)
#define DBGUTILS_NODEBUG_MACRO_DEFINED
#endif

#if (defined DBGUTILS_DEBUG_MACRO_DEFINED) && (defined DBGUTILS_NODEBUG_MACRO_DEFINED)
#error "You have conflicting macros defined.  Building in both debug and not in debug mode at once is not possible and is entirely non-sensical.  Please correct your macro madness and retry a build (preferrably using a *clean* build)."
#endif

#endif //__DBGUTILS_MACRO_SANITY_H_

