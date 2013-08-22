/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#ifndef __DBGUTILS_DUMP_H
#define __DBGUTILS_DUMP_H

#ifdef __cplusplus
#include <type_traits>
#include <typeinfo>
#include <string>
#include <vector>
namespace dbgutils {

  /** The following routines define a fairly generic dump function
      which is intended for debug output.  This should work for classes,
      arrays, and primitive types.  

      Usage: 
      - dump( value ) where value is a primitive value, (fixed size) 
        array, class, or struct.
      - dump_array( arr, len ) where arr is a pointer to an array and
        len is the number of elements in the array

      Note: Enumerations and unions are currently not supported.  (You won't
      get a pretty error message either.  Behavior is undefined. TODO)

      Note: Do not use this for serialization.  The format is not guaranteed
      and is very likely to change.  

      Note: This section is one of the least mature out of all the components 
      of this mini-library.   Expect revisions in future versions.  (If anyone
      other than the other ever indicates interest.)
  */


  /* General scheme is to match the explicit versions first
     then the templated version.  The templated version trys to 
     find a special cased external dump function (arrays, std data
     structures, etc..), then a member function, and finally falls
     back to bit level (hex) display.. */

  //TODO: add unsigned versions
  void dump(char);
  void dump(short);
  void dump(int);
  void dump(long);
  void dump(unsigned long);
  void dump(long long);
  void dump(float);
  void dump(double);
  void dump(long double);
  void dump(const char* );


  /** This type trait indicates the presence of a member function 
      with the signature: (virtual) void __dump__() const.  (The 
      virtual is optional, but recommended.)  This mechanism can be
      used to provide dump functionality for arbitrary classes/structs.

      If such a member function is not available, a generic hex dump
      routine is used instead.
  */
  template<typename T>
  struct has_member_dump_function {
    //set to true if a void __dump__() function exists
    static const bool value = false;
  };

  /// A helper macro to define the type trait for a particular object type.
#define DBGUTIL_HAS_DUMP_MEMBER(type)           \
  namespace dbgutils {                          \
    template<>                                  \
    struct has_member_dump_function<type> {     \
      static const bool value = true;           \
    };                                          \
  }

  /* implementation detail -- dump_helper is used to dump an object.  
     It dispatches on the above type trait to either the member 
     function or generic hex dump. */
  template<typename T, 
    bool = has_member_dump_function<T>::value>
  struct dump_helper {
    void dump(const T& val);
  };

  template<typename T>
  struct dump_helper<T, true> {
    void dump(const T& val) {
      val.__dump__();
    }
  };
  template<typename T>
  struct dump_helper<T, false> {
    void dump(const T& val) {
      // This is really hacky - It ignores endianness, layout, etc..
      printf("{raw(%s) ", typeid(val).name());
      const char* raw = (const char*)&val;
      for(int i = 0; i < sizeof(val); i++) {
        //each 8 bit value is two hex values
        printf("%02X", raw[i]);
      }
      printf("}");
      fflush(stdout);
    }
  };


  //the trick is the odd parens
  // T is the base type of the array, not the array type!
  // I don't know why the extent works like this..
  template<typename T, int N = std::extent<T,0>::value >
    void dump_array(const T(& val)[N]);


  /** This the generic version.  It's only called if there isn't 
      already a better match (i.e. a more specific template or a 
      direct function overload).  We use dump_helper to (statically)
      dispatch to either a member function or a generic 
      "we give up" function.*/
  template<typename T>
  typename std::enable_if< !std::is_array<T>::value, void>::type
  dump(const T& val) {
    dump_helper<T>().dump(val);
  }

  template<typename T>
  typename std::enable_if< std::is_array<T>::value, void>::type
  dump(const T& val) {    
    static_assert( std::rank<T>::value == 1, "Multi-D arrays not yet supported" );
    dump_array(val);
  }

  template<typename T>
  void dump_array(const T* val, int N) {
    dump("{");
    for(int i = 0; i < N; i++) {
      if( i ) dump(",");
      dump(val[i]);
    }
    dump("}");
  }

  template<typename T, int N>
  void dump_array(const T(& val)[N]) {
    dump_array<T>(&val[0], N);
  }


  /** dump(val) speciailization for std::vector */
  template<typename TInner>
  void dump(const std::vector<TInner>& val) {
    dump("std::vector<");
    dump("unknown");//typeid().name()); gives nothing for std::vector<int> on int, or mangled names on the full thing
    dump(">{");
    for(int i = 0; i < val.size(); i++) {//for( auto item : val ) {
      if( i ) dump(",");
      dump(val[i]);
    }
    dump("}");
  }

  //TODO: array, bitset, deque, forward_list, list, map, queue, set, stack, unorder_map, unordered_set
  // Patches welcome.


  //The following is "seed of idea" stage.  DO NOT TRY TO USE THIS.
#if 0
  // the idea here is to fall back to the brute force dumper
  // (i.e. bit level) only if there is no dump symbol - can try to
  // do this using the weak symbol hack?
  #   pragma weak dumper
  template<typename T>
    void dumper() {}

  int foo() {
    dumper<int>();
    dumper<float>();
    return 0;
  }
#endif


}
#endif

#endif //__DBGUTILS_DUMP_H
