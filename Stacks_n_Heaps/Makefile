CXX := g++
CXXFLAGS := -g -Wall --std=c++11

VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: huffman-test rem_dup laundry 

huffman-test: huffman-test.o huffman.o 
	$(CXX) $(CXXFLAGS) $^ -o huffman-test

huffman.o: huffman.cpp huffman.h heap.h  
	$(CXX) $(CXXFLAGS) -c $< -o $@
huffman-test.o: huffman-test.cpp huffman.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

rem_dup: rem_dup.cpp rem_dup_lib.o
	$(CXX) $(CXXFLAGS) $^ -o $@
rem_dup_lib.o: rem_dup_lib.cpp rem_dup_lib.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

laundry: laundry.o
	$(CXX) $(CXXFLAGS) $^ -o $@

laundry.o: laundry.cpp stack.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o huffman-test rem_dup laundry *.huf *.dec

.PHONY: clean 