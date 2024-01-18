#pragma once

#pragma warning(disable:4820)

#include <vector>
#include <string>

namespace fatpound::compression
{
    class Huffman
    {
    public:
        Huffman() = delete;


    public:
        static void Compress(const std::string& input_filename);
        static void Decompress(const std::string& input_filename);


    protected:


    private:
        struct Node
        {
            Node* left_  = nullptr;
            Node* right_ = nullptr;

            int64_t ch_ = -1;
            int64_t num_ = 0;

            Node(Node* left, Node* right);
            Node(const int64_t& ch, const int64_t& num);
        };


    private:
        static std::vector<std::pair<unsigned char, std::string>> GenerateTreeResultPairs_(const std::string& tree_results);
        static std::string GenerateBinaryWords_(Node* node, const std::string& str);

        static bool DecompressToFile_(std::ofstream& output_file, const std::vector<std::pair<unsigned char, std::string>>& tree_results_pairs, std::string& final_str);

        static void DeleteTree_(Node* node);

        
    private:
    };
}