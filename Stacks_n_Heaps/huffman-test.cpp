#include "huffman.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 4){
        cerr << "Usage [c|d] input-file output-file" << endl;
        return 1;
    }

    if(argv[1][0] == 'c') {
        cout << "Reading input ASCII hex file..." << endl;
        RawTextVector text = AsciiHexIO::read(argv[2]);
        cout << "Complete\n" << endl;

        CompressedData compressedText;
        CodeKeyMap codeMap;

        cout << "Compressing data..." << endl;
        HuffmanCoder::compress(text, compressedText, codeMap);
        cout << "Complete\n" << endl;

        HuffmanCoder::ratio(text, compressedText, codeMap);

        cout << "Saving compressed file..." << endl;
        AsciiHuffmanIo::writeCodedText(argv[3], compressedText, codeMap);
        cout << "Complete\n" << endl;
    }
    else if(argv[1][0] == 'd') {
        cout << "Reading compressed file..." << endl;
        CompressedData readCompressedText;
        CodeKeyMap readCodeMap;
        AsciiHuffmanIo::readCodedText(argv[2], readCompressedText, readCodeMap);
        cout << "Complete\n" << endl;
        
        cout << "decompressing..." << endl;
        RawTextVector decompressedText;
        HuffmanCoder::decompress(readCompressedText, readCodeMap, decompressedText);
        cout << "Complete\n" << endl;

        cout << "Writing decompressed contents to file..." << endl;
        AsciiHexIO::write(argv[3], decompressedText);    
        cout << "Complete\n" << endl;
    }
    else {
        cerr << "Invalid option...Exiting!" << endl;
        return 1;
    }

    return 0;
}