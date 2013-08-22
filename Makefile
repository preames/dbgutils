# Use these to compile a native version (for example x86_64) with
# libunwind support
LDFLAGS=-L/usr/local/lib -lunwind
CXXFLAGS= -O3 -fPIC -std=c++0x -I./include/
CFLAGS = -I./include/
CXX=clang++
CC=clang

# headers should be installed to
# $(hdr_install_root)/dbgutils/

# Use these to compile a 32 bit version (on a 64 bit system without
# libunwind support)
#LDFLAGS=
#CXXFLAGS= -O3 -fPIC -std=c++0x -m32 -DNO_LIBUNWIND 
#CFLAGS = -m32

SOURCE_FILES= src/dbgutils.cxx src/trap.cxx

all:
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(SOURCE_FILES) -o libdbgutils.so
	$(CC)  $(CFLAGS) test/test.c libdbgutils.so -o test-c.out #C usage
	$(CXX) $(CXXFLAGS) test/test.cxx libdbgutils.so -o test-cxx.out #C++ usage
	$(CXX) $(CXXFLAGS) test/er_test.cxx libdbgutils.so -o er_test-cxx.out #Ensures-Requires

test:
###	export LD_LIBRARY_PATH=./
	./test-c.out
	./test-cxx.out
	./er_test-cxx.out

clean:
	rm -f test-c.out test-cxx.out er_test-cxx.out libdbgutils.so
