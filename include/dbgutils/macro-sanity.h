/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

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

