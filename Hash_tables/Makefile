CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
DEFS=-DDEBUG


all: ht-test ht-perf str-hash-test pairless 

ht-test: ht-test.cpp ht.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# enable optimizations for performance tests with -O3
ht-perf: ht-perf.cpp ht.h
	$(CXX) -Wall -std=c++11 -O3 $(DEFS) $< -o $@

str-hash-test: str-hash-test.cpp hash.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# Add a target for pairless
pairless: pairless.cpp ht.h
	$(CXX) $(CXXFLAGS) $(DEFS) pairless.cpp ht.h -o pairless

clean:
	rm -f *~ *.o *.sol *.out ht-test ht-perf str-hash-test pairless 
