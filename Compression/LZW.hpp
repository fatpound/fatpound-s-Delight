#pragma once

#include <vector>
#include <string>

namespace fatpound::compression
{
    class LZW
    {
    public:
        LZW() = delete;


    public:
        static void Compress(const std::string& input_filename);
        static void Decompress(const std::string& input_filename);
        

    protected:


    private:
        static void InitializeDictionary_(std::vector<std::pair<size_t, std::string>>& dictionary);
    };
}