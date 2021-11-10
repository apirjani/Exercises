#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
       
        vector<int> convertedString;
        unsigned long long word[5];

        for (int i = 0; i < 5; i++)
        {
            word[i] = 0;
        }
    
        for (unsigned int i = 0; i < k.size(); i++){ //convert string to base-36 string
            convertedString.push_back(letterDigitToNumber(k[i]));
        }

        process(word, convertedString); //fill in word array with unsigned long long's 
                                        //that represent each substr of 6

        HASH_INDEX_T hashVal = 0;
        for (int i = 0; i < 5; i++){ //get final hashvalue by calculating dot product of word and rvalues
            hashVal += (rValues[i] * word[i]);
        }

        return hashVal;

    }

    void process(unsigned long long* w, vector<int> & s) const
    {
        for (int i = 4; i >= 0; i--){ //iterate through w array

            vector<int> temp;

            if (s.empty()){ //if no more characters, leave w[i] as 0
                continue;
            }


            else if (s.size() < 6 && !s.empty()){ //case where substring has less than 6 chars

                int size = s.size();
                for (int i = s.size()-1; i >=0; i--){ //iterate through subtr backwards, push back on temp substr
                    temp.push_back(s[i]); 
                    s.pop_back();
                }

                for (int i = 0; i < 6 - size; i++){ //for the rest of the chars, push back 0
                    temp.push_back(0);
                }

                reverse(temp.begin(), temp.end()); //reverse 

            }

            else //case where subtring has at least 6 chars
            {
                int size = s.size();
                for (int i = size-1; i >= size - 6; i--){ //iterate through substr, push back on temp substr
                    temp.push_back(s[i]);
                    s.pop_back();
                }

                reverse(temp.begin(), temp.end()); //reverse
            }

            unsigned long long translation = temp[0]; //variable to store final product of ith element in word
            for (unsigned int i = 1; i < temp.size(); i++){ 
                translation = translation * 36 + temp[i];
            }

            w[i] = translation;
        
        }
    }

    
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {

        letter = tolower(letter); //make sure letter is lowercase
        if (letter >= 48 && letter <= 57){ //if digit from 0-9
            return letter-22;
        }

        else //if letter from a-z
        {
            return letter-97;
        }

    }

    // Add code to generate the random R values
    void generateRValues()
    {
        // Be sure to seed the random number generator
        srand(time(0));
        for (int i = 0; i < 5; i++)
        {
            rValues[i] = rand();
        }

    }

};

#endif
