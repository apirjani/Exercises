#include <iostream>
#include <fstream>
#include <cstdio>
#include "ht.h"
using namespace std;


int main(int argc, char* argv[])
{
    // Check the number of parameters is correct.
	if(argc < 3)
	{
		std::cerr << "Usage: ./missing [input] target" << std::endl;
		return 1;
	}

    int target = atoi(argv[2]);
    int pairlessCount = 0;
    
    ifstream ifile(argv[1]);
    if(ifile.fail()){
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }

    HashTable<int, int, QuadraticProber, std::hash<int>, std::equal_to<int> > ht;
    int buff;
    while (ifile >> buff){
        if (ht.find(target-buff) != nullptr) //if we find pair of buff
        {
            if ((ht.find(target-buff))->second > 1){ //if more than one exist, decrement count
                (ht.find(target-buff))->second--;
            }
            else{ //otherwise remove it
                ht.remove(target-buff);
            }
            pairlessCount--; //decrement pairless count
        }

        else //if we don't find pair of buff (yet)
        {
            if (ht.find(buff) == nullptr) //if buff isn't in hashtable
            {
                ht.insert({buff, 1}); //add it with count of 1
            }

            else //if it is in hashtable
            {
                (ht.find(buff))->second++; //increment its count
            }
            pairlessCount++; //increment pairless count
        }
    }



    std::cout << "Unmatched items: " << pairlessCount << std::endl;

    ifile.close();

    return 0;
}