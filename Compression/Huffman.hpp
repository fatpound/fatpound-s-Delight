#pragma once

#pragma warning(disable:4820)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

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
        void DeCompress(std::string& bin);
        void ListPreorder() const;
        void ListResults()  const;


    protected:


    private:
        struct node
        {
            node* left = nullptr;
            node* right = nullptr;

            std::string binary_val;

            int64_t num = 0;

            char k = '\0';

            node(int64_t new_num, char new_k)
                :
                num{ new_num },
                k{ new_k }
            {

            }
            node(node* sol, node* sag)
                :
                left{ sol },
                right{ sag },
                num{ sol->num + sag->num }
            {

            }
        };


    private:
        void Delete(node* node);
        void SetBinaryValues(node* node, const std::string& str = {});
        void ListPreorder(node* node) const;

        
    private:
        std::vector<std::string> results_binary;
        std::vector<char>        results_chars;

        node* root = nullptr;

        size_t node_count = 0ui64;
        size_t leaf_count = 0ui64;

        size_t min_depth = std::numeric_limits<size_t>::max();
        size_t max_depth = 0ui64;
    };
}