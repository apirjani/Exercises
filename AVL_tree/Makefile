CXX=g++
CXXFLAGS=-g -Wall -std=c++11
all: internal-range-test bst-test

internal-range-test: internal-range-test.o internal-range.o 
	$(CXX) $(CXXFLAGS) internal-range-test.o internal-range.o -o internal-range-test

internal-range-test.o: internal-range-test.cpp internal-range.h
	$(CXX) $(CXXFLAGS) -c internal-range-test.cpp -o internal-range-test.o

internal-range.o: internal-range.cpp internal-range.h
	$(CXX) $(CXXFLAGS) -c internal-range.cpp -o internal-range.o

bst-test: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) bst-test.cpp -o bst-test


clean:
	rm -f *.o internal-range-test