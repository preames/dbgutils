# Use these to compile a native version (for example x86_64) with
# libunwind support
LDFLAGS=-L/usr/local/lib -lunwind
CXXFLAGS= -O3 -fPIC -std=c++0x
CFLAGS = 

# Use these to compile a 32 bit version (on a 64 bit system without
# libunwind support)
#LDFLAGS=
#CXXFLAGS= -O3 -fPIC -std=c++0x -m32 -DNO_LIBUNWIND 
#CFLAGS = -m32

SOURCE_FILES= dbgutils.cxx trap.cxx

all:
	clang++ -shared $(CXXFLAGS) $(LDFLAGS) $(SOURCE_FILES) -o libdbgutils.so
	clang $(CFLAGS) test.c libdbgutils.so -o test-c.out #C usage
	clang++ $(CXXFLAGS) test.cxx libdbgutils.so -o test-cxx.out #C++ usage
	clang++ $(CXXFLAGS) er_test.cxx libdbgutils.so -o er_test-cxx.out #Ensures-Requires

test:
###	export LD_LIBRARY_PATH=./
	./test-c.out
	./test-cxx.out
	./er_test-cxx.out

clean:
	rm -f test-c.out test-cxx.out er_test-cxx.out libdbgutils.so
