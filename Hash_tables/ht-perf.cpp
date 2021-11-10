#include "ht.h"
#include "hash.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <map>

void ParseInputFile(char* inputFile, std::vector<std::string>& outVector);
void ParseParameters(char* argv[], int& probing, double& alpha, size_t& numberOfRepetitions);

enum ProbingStrategy { INVALID = 0, LINEAR = 1, QUADRATIC = 2};

typedef HashTable<
				std::string, int, 
				LinearProber, 
				std::hash<std::string>, 
				std::equal_to<std::string> > LinearProbeHashTable;

typedef HashTable<
				std::string, int, 
				QuadraticProber, 
				std::hash<std::string>, 
				std::equal_to<std::string> > QuadraticProbeHashTable;

typedef std::vector<std::string> StringVec;

template <typename HashTableType>
size_t doHashTest(HashTableType& ht, double alpha, size_t numberOfRepetitions, const StringVec& wordsFromFile)
{
		for(const auto& iter : wordsFromFile)
		{
			ht.insert({iter,1});
		}
		for(const auto& iter : wordsFromFile)
		{
			if(nullptr == ht.find(iter))
			{
				throw std::logic_error("Key should exist");
			}
		}
		return ht.totalProbes();
}

template <typename MapType>
void doMapTest(MapType& mt, size_t numberOfRepetitions, const StringVec& wordsFromFile)
{
		for(const auto& iter : wordsFromFile)
		{
			mt.insert({iter,1});
		}
		for(const auto& iter : wordsFromFile)
		{
			if(mt.end() == mt.find(iter))
			{
				throw std::logic_error("Key should exist");
			}
		}
}
int main(int argc, char* argv[])
{
	// Check the number of parameters is correct.
	if(argc < 5)
	{
		std::cerr << "Usage: ./counting [input] p alpha reps" << std::endl;
		return 1;
	}

	// Get parameters
	int probeStrategy = 1;
	size_t numberOfRepetitions = 0;
	double alpha = 0.5;
	ParseParameters(argv, probeStrategy, alpha, numberOfRepetitions);

	// Identify probing strategy
	ProbingStrategy probing = INVALID;
	if(probeStrategy == 1) probing = LINEAR;
	else if(probeStrategy == 2) probing = QUADRATIC;

	// Get the strings to insert to the hash table or map
	std::vector<std::string> wordsFromFile;
	ParseInputFile(argv[1], wordsFromFile);
	std::cout << "Testing on corpus of " << wordsFromFile.size() << " strings" << std::endl;

	size_t numProbes = 0;

	// Add code to start the timer (i.e. get a timestamp of the current clock time)
	//  and run the test numberOfRepetition times, saving the number of probes
	//  for the last reptition.

	clock_t start;
	start = clock();
	if(probing == LINEAR )
	{
		for (size_t i = 0; i < numberOfRepetitions; i++){
			LinearProbeHashTable ht(alpha);
			numProbes = doHashTest(ht, alpha, numberOfRepetitions, wordsFromFile);
		}

	}
	else if(probing == QUADRATIC ) 
	{
		for (size_t i = 0; i < numberOfRepetitions; i++){
			QuadraticProbeHashTable ht(alpha);
			numProbes = doHashTest(ht, alpha, numberOfRepetitions, wordsFromFile);
		}

	}
	else {
		throw std::logic_error("Invalid probing strategy");
	}

	// Add code to stop the timer (i.e. get a timestamp of the current clock time)
	// and calculate duration by subtracting.  Place your result in a variable
	// named 'duration'
	double duration = 0;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	// Output code to be run after all repetitions
	std::cout << "Average HashTable time: " << duration / numberOfRepetitions << std::endl;
	std::cout << "Total Probes: " << numProbes << std::endl;



	// Add code to start the timer (i.e. get a timestamp of the current clock time)
	//  and run the test numberOfRepetition times
	start = clock();

	for (size_t i = 0; i < numberOfRepetitions; i++){
		std::map<std::string, int> mt;
		doMapTest(mt, numberOfRepetitions, wordsFromFile);
	}


	// Add code to stop the timer (i.e. get a timestamp of the current clock time)
	// and calculate duration by subtracting.  Place your result in a variable
	// named 'duration'
	duration = 0; 
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Average std::map time: " << duration / numberOfRepetitions << std::endl;

	return 0;
}

void ParseParameters(char* argv[], int& probing, double& alpha, size_t& numberOfRepetitions)
{
	probing = std::atoi(argv[2]);
	alpha = std::atof(argv[3]);
	numberOfRepetitions = std::atoi(argv[4]);
}


void ParseInputFile(char* inputFile, std::vector<std::string>& outVector)
{
	std::ifstream inputStream{ inputFile };
	if(!inputStream.is_open())
	{
		std::cerr << "Could not open file " << inputFile << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string word{ "" };
	while(inputStream >> word)
	{
		std::string constructedWord{ "" };
		char letter{ ' ' };
		std::stringstream ss{ word };
		while(ss >> letter)
		{
			if(std::isalnum(letter))
			{
				constructedWord += std::tolower(letter);
			}
		}
		if(constructedWord != "")
		{
			outVector.push_back(constructedWord);
		}
	}
}
