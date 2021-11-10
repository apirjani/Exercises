#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include "heap.h"

/**
 * @brief Typedef of a vector of strings storing the uncompressed 
 * sequence of symbols (from an .aschex file)
 * 
 */
typedef std::vector<std::string> RawTextVector;
/**
 * @brief Used for the compressed sequence which is a string of 1s and 0s
 * 
 */
typedef std::string CompressedData;
/**
 * @brief Map of codes to keys/symbols ("100" => "006d")
 * 
 */
typedef std::map<std::string, std::string> CodeKeyMap;

class AsciiHexIO {
public:
    /**
     * @brief Reads a text file of ASCII strings representing the hex of
     *  of an UTF-16 coded file
     * 
     * @param filename path of the file to read
     * @return RawTextVector sequence of ASCII strings of the hex for each UTF-16 character
     */
    static RawTextVector read(const char* filename);
    /**
     * @brief Writes a text file of ASCII strings representing the hex of
     *  of an UTF-16 coded file
     * 
     * @param filename path of the file to write
     * @param text sequence of ASCII strings of the hex for each UTF-16 character
     */
    static void write(const char* filename, const RawTextVector&  text);

};

class AsciiHuffmanIo {
public:
    /**
     * @brief Writes a compressed file
     * 
     * @param filename name of file to create and write
     * @param inText string of the compressed sequence of 0s and 1s
     * @param code map of Huffman codes to their original symbols 
     *             (i.e. "100" => "006d")
     */
    static void writeCodedText(
        const char* filename, 
        const CompressedData& inText, 
        const CodeKeyMap& code);
    /**
     * @brief Reads a compressed file outputting its code/key map and 
     *        compressed data sequence
     * 
     * @param filename name of file to read
     * @param outText string of the compressed sequence of 0s and 1s
     * @param code map of Huffman codes to their original symbols 
     *        (i.e. "100" => "006d")
     */
    static void readCodedText(
        const char* filename, 
        CompressedData& outText, 
        CodeKeyMap& code);
};

class HuffmanCoder {
public:
    /**
     * @brief map to use for storing the frequencies of each symbol
     * 
     */
    typedef std::map<std::string, size_t> KeyFrequencyMap;
    /**
     * @brief map of symbol to code (used for compression)
     * 
     */
    typedef std::map<std::string, std::string> KeyCodeMap;
    /**
     * @brief Heap item/node struct
     * 
     */
    struct HeapItem {
        size_t total;
        std::set<std::string> keys;
        bool operator<(const HeapItem& rhs) const { return total < rhs.total; }
    };
    /**
     * @brief Compresses a RawTextVector and outputs the compressed sequence 
     *        along with the code/key mapping
     * 
     * @param [in] inText input sequence to be compressed (strings representing 
     *                    the hex of an UTF-16 character)
     * @param [out] outText compressed string of 1s and 0s
     * @param [out] codes code to key mapping
     */
    static void compress(
        const RawTextVector& inText, 
        CompressedData& outText, 
        CodeKeyMap& codes);

    /**
     * @brief Decompresses a compressed sequence (string of 1s and 0s) to the 
     * original sequence of symbols
     * 
     * @param [in] inText compressed string of 1s and 0s
     * @param [in] codes code to key mapping
     * @param [out] outText output sequence of strings representing the hex 
     *                      of UTF-16 characters
     */
    static void decompress(
        const CompressedData& inText, 
        const CodeKeyMap& codes, 
        RawTextVector& outText);

    /**
     * @brief Prints statistics and returns the compression ratio if all data 
     *        was stored at the bit/binary level
     * 
     * @param [in] inText input sequence to be compressed (strings 
     *                      representing the hex of an UTF-16 character)
     * @param [out] outText compressed string of 1s and 0s
     * @param [out] codes code to key mapping
     * @return double The ratio of compression if all data was stored at the 
     *                  bit/binary level
     */
    static double ratio(
        const RawTextVector& inText, 
        const CompressedData& outText, 
        const CodeKeyMap& codes);

};


#endif