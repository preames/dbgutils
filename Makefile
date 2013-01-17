# wherever you have libunwind installed
LDFLAGS=-L/usr/local/lib -lunwind
CXXFLAGS= -O3 -fPIC -std=c++0x

SOURCE_FILES= dbgutils.cxx trap.cxx

all:
	clang++ -shared $(CXXFLAGS) $(LDFLAGS) $(SOURCE_FILES) -o libdbgutils.so
	clang test.c libdbgutils.so -o test-c.out #C usage
	clang++ $(CXXFLAGS) test.cxx libdbgutils.so -o test-cxx.out #C++ usage

test:
	./test-c.out
	./test-cxx.out

clean:
	rm -f test-c.out test-cxx.out libdbgutils.so
