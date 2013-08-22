/** 
Copyright (c) 2013, Philip Reames
All rights reserved.

This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.  You can also find the appropriate version of that file by searching the history of this project at https://github.com/preames/dbgutils/.

*/

#define _DEBUG
#include "dbgutils.h"


using namespace dbgutils;

void valid(int a) {
  DBGUTILS_REQUIRES(a > 10);
  DBGUTILS_ENSURES(a < 10);

  a = 0;
}
void bad_pre(int a) {
  DBGUTILS_REQUIRES(a < 10);
}
void bad_post(int a) {
  DBGUTILS_ENSURES(a >= 100);
  a = 20;
}

int main() {
  valid(20);
  bad_pre(20);
  bad_post(2000);
}
