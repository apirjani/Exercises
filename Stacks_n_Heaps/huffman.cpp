#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include "huffman.h"
using namespace std;


RawTextVector AsciiHexIO::read(const char* filename)
{
    RawTextVector text;
    ifstream ifile(filename);
    if(ifile.fail()){
        throw std::invalid_argument("Bad input filename");
    }
    while(!ifile.fail()) {
        char c;
        string word;
        for(int i=0; i < 4; i++){
            ifile >> c;
            if(ifile.fail()){
                if(i > 0) {
                    throw std::runtime_error(
                        "Bad file format...did not find multiple of 4 hex characters");
                }
                else {
                    break; // normal exit
                }
            }
            else {
                word += c;
            }
        }
        if(word.size() == 4) {
            text.push_back(word);
        }
    }
    ifile.close();
    return text;
}


void AsciiHexIO::write(const char* filename, const RawTextVector&  text)
{
    const size_t NUM_WORDS_PER_LINE = 8;
    ofstream ofile(filename);
    if(ofile.fail()){
        throw std::runtime_error("Unable to open output file");
    }
    size_t i = 0;
    for( const auto & word : text ){
        ofile << word;
        if(i % NUM_WORDS_PER_LINE != NUM_WORDS_PER_LINE-1 ){
            ofile << " ";
        }
        else {
            ofile << endl;
        }
        i++;
    }
    ofile.close();
}


void AsciiHuffmanIo::writeCodedText(
    const char* filename, 
    const CompressedData& inText, 
    const CodeKeyMap& code)
{
    ofstream ofile(filename);
    ofile << code.size() << endl;
    // copy from map to vector so we can sort
    typedef pair<string,string> StrStrPair;
    vector< StrStrPair > codesToSort(code.begin(), code.end());
    std::sort(
        codesToSort.begin(), codesToSort.end(), 
        [] (const StrStrPair& s1, const StrStrPair& s2) -> bool
            { return (s1.first.size() < s2.first.size()) ||
                     (s1.first.size() == s2.first.size() && s1.first < s2.first); } );
    for(const auto& pair : codesToSort) {
        ofile << pair.first << " " << pair.second << endl;
    }
    ofile << inText << endl;
    ofile.close();
}

void AsciiHuffmanIo::readCodedText(
    const char* filename, 
    CompressedData& outText, 
    CodeKeyMap& code)
{
    // clear old contents of the output parameters that this function
    // should fill in
    code.clear();
    outText.clear();

    // Complete the code below
    ifstream ifile(filename);
    if(ifile.fail()){
        throw runtime_error("Cannot open file");
    }

    int codekey_pairs;
    string code_str, key_str;
    ifile >> codekey_pairs; //read in number of code key pairs
    //iterate through each code-key pair
    for (int i = 0; i < codekey_pairs; i++)
    {
        ifile >> code_str >> key_str; //first read in code then key
        code.insert(make_pair(code_str, key_str)); //insert the pair into the code map
    }

    ifile >> outText; //read in the compressed data

}


void HuffmanCoder::compress(
    const RawTextVector& inText, 
    CompressedData& outText, 
    CodeKeyMap& codes)
{
    // Clear old contents of the output parameters that this function should fill in
    codes.clear();
    outText.clear();
    KeyCodeMap keytocodes;
    KeyFrequencyMap frequencies;

    // Add your code here
    //store the frequency of each key in frequencies map
    for (unsigned int i = 0; i < inText.size(); i++)
    {
        //the first time you see a character, add one to counter
        int ctr = 1;
        if (frequencies.find(inText[i]) == frequencies.end()) //if character not seen before
        {
            //iterate through rest of text and count occurences of character
            for (unsigned int j = i+1; j < inText.size(); j++)
            {
                if (inText[j] == inText[i])
                {
                    ctr++;
                }
            }
            //make a pair with the character and the count of the occurrences
            frequencies.insert(make_pair(inText[i], ctr));
        }
    }

    Heap<HeapItem> heap(2);
    KeyFrequencyMap::iterator it;
    //push each heapitem into heap
    for (it = frequencies.begin(); it != frequencies.end(); ++it)
    {
        set<string> keys;
        HeapItem item;
        //for each symbol, create an item that contains its total occurrences
        item.total = it->second;
        (item.keys).insert(it->first);
        heap.push(item);
    }

    HeapItem first_node, second_node;
    //check if heap is empty before top and pop
    if (!heap.empty())
    {
        first_node = heap.top(); heap.pop();
    }

    while (!heap.empty())
    {
        second_node = heap.top(); heap.pop();
        set<string>::iterator it1;
        //iterate through keys in first node, prepend '0' to their codes
        for (it1 = (first_node.keys).begin(); it1 != (first_node.keys).end(); ++it1)
        {
            keytocodes[*it1] = '0' + keytocodes[*it1];
        }

        set<string>::iterator it2;
        //iterate through keys in second node, prepend '1' to their codes
        for (it2 = (second_node.keys).begin(); it2 != (second_node.keys).end(); ++it2)
        {
            keytocodes[*it2] = '1' + keytocodes[*it2];

        }

        HeapItem item;
        //create item that contains sum of two popped nodes totals
        item.total = first_node.total + second_node.total;
        set<string> union_set = first_node.keys;
        set<string>::iterator it3;
        //get the union of the keys of both nodes
        for (it3 = (second_node.keys).begin(); it3 != (second_node.keys).end(); ++it3)
        {
            if ((first_node.keys).find(*it3) == (first_node.keys).end())
            {
                union_set.insert(*it3);
            }
        }
        //set keys of new item to union of the two popped nodes
        item.keys = union_set;
        //push onto heap
        heap.push(item);
        first_node = heap.top(); heap.pop();
    }

    KeyCodeMap::iterator it4;
    //copy keytocodes map in reverse to get mapping from codes to keys in codes map
    for (it4 = keytocodes.begin(); it4 != keytocodes.end(); ++it4)
    {
        codes.insert(make_pair(it4->second, it4->first));
    }

    //replace every occurrence of a letter with its code
    for (unsigned int i = 0; i < inText.size(); i++)
    {
        outText += keytocodes[inText[i]];
    }

}


void HuffmanCoder::decompress(
    const CompressedData& inText, 
    const CodeKeyMap& codes, 
    RawTextVector& outText)
{
    // Clear old contents of the output parameter
    outText.clear();
    // Add your code here
    string inputCode;

    // create the decompressed text by reading one char at a time and, 
    // since Huffman codes are prefix codes, once the string matches 
    // a key in the code map, just substitute the word and start again
    for (unsigned int i = 0; i < inText.size(); i++) //iterate through compressed data intext
    {
        //concatenate to temporary string
        inputCode += inText[i];
        
        auto it = codes.find(inputCode); //check if the code exists in codes map
        if (it != codes.end())
        {
            //if it does, replace with key
            outText.push_back(it->second);
            //reset the temporary string
            inputCode = "";
        }
        
        
    }


}


double HuffmanCoder::ratio(const RawTextVector& inText, const CompressedData& outText, const CodeKeyMap& codes)
{
    // 2 bytes per entry
    double rawSize = 2 * inText.size(); 
    // each character in outText is a bit so convert to bytes
    double compressedSize = (outText.size() + 7) / 8; 
    for(const auto& pair : codes) {
        compressedSize += 2 + pair.first.size()+1; // 2 bytes for 16-bit val + string of 1,0 + null char
    }
    cout << "Original size (bytes): " << rawSize << endl;
 
    cout << "Compressed size (bytes): " << compressedSize << endl;
    double compressionRatio = rawSize / compressedSize;
    cout << "Compression ratio: " << setprecision(2) << fixed << compressionRatio << endl;
    return compressionRatio;
}
