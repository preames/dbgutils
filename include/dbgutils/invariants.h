/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/
#ifndef __DBGUTILS_INVARIANTS_H_
#define __DBGUTILS_INVARIANTS_H_

#error "NOT IMPLEMENTED"



#include <vector>
#include <functional>

#include "assert.h"

/*

As a thought excerice, you could macro-ize much of this.  
I think you could reduce it to a DEFINE_INVARIANT(exp) - using lambda, inline member initializers, and _function_ based macro safety - and a SUPPORTS_INVARIANTS macro in each public function - which simply executes each in turn.

Not sure this is worth doing yet though.  
 */

class test {
  std::vector< std::function<bool(test*)> > m_inv_functions;

  bool my_test_invariant() { return true; }

  test() {
    m_inv_functions.push_back( [](test* self) { 
        bool b = self->my_test_invariant(); //separate the assignment for clear debugging errors
        return b; 
      } 
    );
  }

  void do_something() {
    for( auto f : m_inv_functions ) {
      DBGUTILS_ASSERT(  f(this) );
    }
#if 0
    on_scope_exit( [&]() {
        for( auto f : this->m_inv_functions ) {
          DBGUTILS_ASSERT(f(test));
        }
      });
#endif
  }
};
  
#endif //__DBGUTILS_INVARIANTS_H_
