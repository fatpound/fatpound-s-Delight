#include "Huffman.hpp"

#include "../../File/File.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <bitset>
#include <stdexcept>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::dsa::compression
{
    void Huffman::Compress(const std::string& input_filename)
    {
        std::ifstream input_file(input_filename, std::ios::binary);

        if ( ! input_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened for [Compressing]!");
        }

        input_file.seekg(0, std::ios::end);
        const std::size_t file_size = input_file.tellg();

        if (file_size < 1u)
        {
            throw std::runtime_error("Input file is empty for [Compressing]!");
        }

        // input_file.clear();
        input_file.seekg(0, std::ios::beg);

        const auto& name_ext = fatpound::file::GetNameAndExtension(input_filename);

        std::ofstream output_file(name_ext.first + "_compressed" + "." + name_ext.second, std::ios::binary);

        if ( ! output_file.is_open() )
        {
            throw std::runtime_error("Compressed file cannot be created!");
        }

        std::vector<std::pair<unsigned char, std::size_t>> pairs;
        pairs.reserve(256);

        for (std::size_t i = 0u; i < 256u; ++i)
        {
            pairs.emplace_back(static_cast<unsigned char>(i), 0u);
        }

        int ch = input_file.get();

        while ( ! input_file.eof() )
        {
            pairs[ch].second++;

            ch = input_file.get();
        }

        pairs.erase(rn::remove_if(pairs, [](const auto& pair) -> bool { return pair.second == 0u; }).begin(), pairs.end());
        rn::sort(pairs, [](const auto& pair1, const auto& pair2) -> bool { return pair1.second < pair2.second; });

        std::deque<Node_*> deque;
        deque.resize(pairs.size());

        for (std::size_t i = 0u; i < pairs.size(); ++i)
        {
            deque[i] = new Node_(static_cast<std::int64_t>(pairs[i].first), pairs[i].second);
        }

        const std::size_t first_size = deque.size();

        // Generating Huffman Tree

        for (std::size_t i = 0u; i < first_size - 1u; ++i)
        {
            Node_* const left  = deque[0];
            Node_* const right = deque[1];

            Node_* const newnode = new Node_(left, right);

            deque.pop_front();
            deque.pop_front();

            std::size_t index = 0u;

            for (std::size_t j = 0u; j < deque.size(); ++j)
            {
                if (newnode->num_ > deque[index]->num_)
                {
                    index = j + 1u;
                }
                else
                {
                    break;
                }
            }
            
            deque.insert(deque.begin() + index, newnode);
        }

        // const std::size_t node_count = first_size * 2 - 1; // unused

        auto tree_results = GenerateBinaryWords_(deque[0], "");
        DeleteTree_(deque[0]);

        const std::size_t tree_result_len = tree_results.length();

        output_file << tree_result_len << ' ';

        auto tree_results_pairs = GenerateTreeResultPairs_(tree_results);

        output_file << tree_results << ' ';

        // rn::sort(tree_results_pairs, [](const auto& pair1, const auto& pair2) -> bool { return pair1.first < pair2.first; });

        std::size_t bit_mod = 0u;

        for (const auto& pair : pairs)
        {
            bit_mod += rn::find_if(tree_results_pairs, [&](const auto& pair1) -> bool { return pair1.first == pair.first; })->second.length() * pair.second;
        }

        bit_mod %= 8u;

        output_file << bit_mod << ' ';

        input_file.clear();
        input_file.seekg(std::ios::beg);

        std::string final_str;

        const auto lambda = [&](const auto& pair) -> bool { return pair.first == ch; };

        ch = input_file.get();

        while ( ! input_file.eof() )
        {
            final_str += rn::find_if(tree_results_pairs, lambda)->second;

            if (final_str.length() >= 8u)
            {
                const std::string temp_str(final_str.cbegin(), final_str.cbegin() + 8u);

                final_str.erase(final_str.cbegin(), final_str.cbegin() + 8u);

                output_file.put(std::stoi(temp_str, nullptr, 2));
            }

            ch = input_file.get();
        }

        while (final_str.length() >= 8u)
        {
            const std::string temp_str(final_str.cbegin(), final_str.cbegin() + 8u);

            final_str.erase(final_str.cbegin(), final_str.cbegin() + 8u);

            output_file.put(std::stoi(temp_str, nullptr, 2));
        }
        
        if (bit_mod != 0u)
        {
            final_str += std::string(8u - bit_mod, '0');

            output_file.put(std::stoi(final_str, nullptr, 2));
        }
    }
    void Huffman::Decompress(const std::string& input_filename)
    {
        std::ifstream input_file(input_filename, std::ios::binary);

        if ( ! input_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened for [Decompressing]!");
        }

        input_file.seekg(0, std::ios::end);

        if (input_file.tellg() < 1u)
        {
            throw std::runtime_error("Input file is empty for [Compressing]!");
        }

        // input_file.clear();
        input_file.seekg(0, std::ios::beg);

        const auto& name_ext = fatpound::file::GetNameAndExtension(input_filename);

        std::ofstream output_file(name_ext.first + "_decompressed" + "." + name_ext.second, std::ios::binary);

        if (!output_file.is_open())
        {
            throw std::runtime_error("Compressed file cannot be created!");
        }

        int byte_count;
        input_file >> byte_count;
        
        if (byte_count == -1 || input_file.get() != ' ')
        {
            throw std::runtime_error("Unknown compression format for [Decompressing]!");
        }

        std::string tree_str(byte_count, ' ');

        input_file.read(tree_str.data(), byte_count);
        auto tree_results_pairs = GenerateTreeResultPairs_(tree_str);

        int bit_mod;
        input_file >> bit_mod;

        if (bit_mod == -1 || input_file.get() != ' ')
        {
            throw std::runtime_error("Unknown compression format for [Decompressing]!");
        }

        unsigned int ch;
        ch = input_file.get();

        std::string final_str;

        while ( ! input_file.eof() )
        {
            std::bitset<8> bitset(ch);

            final_str += bitset.to_string();

            if (final_str.length() > 32u)
            {
                if ( ! DecompressToFile_(output_file, tree_results_pairs, final_str) )
                {
                    throw std::runtime_error("Unknown compression format for [Decompressing]!");
                }
            }

            ch = input_file.get();
        }
        
        if (bit_mod != 0u)
        {
            final_str.erase(final_str.cend() - (8u - bit_mod), final_str.cend());
        }

        while (final_str.length() > 0)
        {
            if ( ! DecompressToFile_(output_file, tree_results_pairs, final_str) )
            {
                throw std::runtime_error("Unknown compression format for [Decompressing]!");
            }
        }
    }

    
    std::vector<std::pair<unsigned char, std::string>> Huffman::GenerateTreeResultPairs_(const std::string& tree_results)
    {
        std::vector<std::pair<unsigned char, std::string>> tree_results_pairs;

        for (std::size_t i = 0u; i < tree_results.length(); ++i)
        {
            std::string tempstr;

            unsigned char ch = static_cast<unsigned char>(tree_results[i]);

            tempstr += ch;

            std::size_t j = i + 1u;

            ch = tree_results[j];

            while (j < tree_results.length() && std::isdigit(ch))
            {
                tempstr += ch;

                ++j;

                ch = tree_results[j];
            }

            i = j;

            tree_results_pairs.emplace_back(tempstr[0], std::string(tempstr.cbegin() + 1u, tempstr.cend()));
        }

        return tree_results_pairs;
    }

    std::string Huffman::GenerateBinaryWords_(Node_* node, const std::string& str)
    {
        if (node == nullptr)
        {
            return str;
        }

        if (node->ch_ != -1)
        {
            std::string s;
            s += static_cast<unsigned char>(node->ch_);

            return s + str;
        }

        return GenerateBinaryWords_(node->left_, str + "0") + "-" + GenerateBinaryWords_(node->right_, str + "1");
    }

    bool Huffman::DecompressToFile_(std::ofstream& output_file, const std::vector<std::pair<unsigned char, std::string>>& tree_results_pairs, std::string& final_str)
    {
        if (final_str.length() == 0u)
        {
            return true;
        }

        bool found = false;
        
        std::size_t max = final_str.length() >= 16u ? 16u : final_str.length();
        
        for (std::size_t i = 1u; i <= max; ++i)
        {
            std::string str(final_str.cbegin(), final_str.cbegin() + i);

            const auto it = rn::find_if(tree_results_pairs, [&](const auto& pair) -> bool { return pair.second == str; });

            if (it != tree_results_pairs.cend())
            {
                found = true;

                output_file << it->first;

                final_str = std::string(final_str.cbegin() + i, final_str.cend());

                break;
            }
        }

        return found;
    }

    void Huffman::DeleteTree_(Node_* node)
    {
        if (node == nullptr)
        {
            return;
        }

        DeleteTree_(node->left_);
        DeleteTree_(node->right_);

        delete node;
    }


    Huffman::Node_::Node_(Node_* left, Node_* right)
        :
        left_(left),
        right_(right),
        num_(left->num_ + right->num_)
    {

    }
    Huffman::Node_::Node_(const std::int64_t& ch, const std::int64_t& num)
        :
        ch_(ch),
        num_(num)
    {

    }
}