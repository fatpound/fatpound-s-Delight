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
        ~Huffman() noexcept;
        Huffman(const Huffman& src) = delete;
        Huffman(Huffman&& src) = delete;
        Huffman& operator = (const Huffman& src) = delete;
        Huffman& operator = (Huffman&& src) = delete;

        Huffman(const std::string& input);


    public:
        std::string GetDecompressed(const std::string& bin);

        void ListTreePreorder() const;


    protected:


    private:
        struct Node
        {
            Node* left_ = nullptr;
            Node* right_ = nullptr;

            std::string binary_value_;

            int64_t num_ = 0;

            char k_ = '\0';

            Node(Node* left, Node* right);
            Node(int64_t num, char k);
        };


    private:
        void SetBinaryValues_(Node* node, const std::string& str = "");
        void ListTreePreorder_(Node* node) const;
        void Delete_(Node* node);

        
    private:
        std::vector<std::string> results_binary_;
        std::vector<char> results_chars_;

        Node* root_ = nullptr;

        size_t node_count_ = 0u;

        size_t min_depth_ = std::numeric_limits<size_t>::max();
        size_t max_depth_ = 0u;
    };
}