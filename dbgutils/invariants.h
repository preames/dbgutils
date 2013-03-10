/** 
Copyright (c) 2012, Philip Reames
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
