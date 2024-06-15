#pragma once

#include <vector>
#include <string>

namespace fatpound::compression
{
    /// <summary>
    /// Unlike Huffman class, this one is not complete.
    /// </summary>
    class LZW final
    {
    public:
        LZW() = delete;


    public:
        static void Compress(const std::string& input_filename);
        static void Decompress(const std::string& input_filename);
        

    protected:


    private:
        static void InitializeDictionary_(std::vector<std::pair<std::size_t, std::string>>& dictionary);
    };
}