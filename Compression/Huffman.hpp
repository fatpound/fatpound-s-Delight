#pragma once

#pragma warning(disable:4820)

#include <vector>
#include <string>

namespace fatpound::compression
{
    class Huffman final
    {
    public:
        Huffman() = delete;


    public:
        static void Compress(const std::string& input_filename);
        static void Decompress(const std::string& input_filename);


    protected:


    private:
        struct Node_
        {
            Node_* left_  = nullptr;
            Node_* right_ = nullptr;

            std::int64_t ch_ = -1;
            std::int64_t num_ = 0;

            Node_(Node_* left, Node_* right);
            Node_(const std::int64_t& ch, const std::int64_t& num);
        };


    private:
        static std::vector<std::pair<unsigned char, std::string>> GenerateTreeResultPairs_(const std::string& tree_results);
        static std::string GenerateBinaryWords_(Node_* node, const std::string& str);

        static bool DecompressToFile_(std::ofstream& output_file, const std::vector<std::pair<unsigned char, std::string>>& tree_results_pairs, std::string& final_str);

        static void DeleteTree_(Node_* node);

        
    private:
    };
}