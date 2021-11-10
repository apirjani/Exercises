CXX=g++
CXXFLAGS=-g -Wall -std=c++11
all: gridpaths sat_solver

gridpaths: gridpaths.cpp 
	$(CXX) $(CXXFLAGS) gridpaths.cpp -o gridpaths

sat_solver: sat_solver.cpp
	$(CXX) $(CXXFLAGS) sat_solver.cpp -o sat_solver

clean:
	rm gridpaths sat_solver
