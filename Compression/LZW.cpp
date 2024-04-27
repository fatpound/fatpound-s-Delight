#include "LZW.hpp"

#include "../File/FatFile.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::compression
{
    void LZW::Compress(const std::string& input_filename)
    {
        std::ifstream input_file(input_filename, std::ios::binary);

        if ( ! input_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened for [Compressing]!");
        }

        const auto name_ext = fatpound::file::GetNameAndExtension(input_filename);

        std::ofstream output_file(name_ext.first + "_compressed" + "." + name_ext.second, std::ios::binary);

        if ( ! output_file.is_open() )
        {
            throw std::runtime_error("Compressed file cannot be created!");
        }

        std::vector<std::pair<std::size_t, std::string>> dictionary;
        InitializeDictionary_(dictionary);

        std::string strp;

        int P = input_file.get();

        if ( ! input_file.eof() )
        {
            strp += static_cast<char>(P);

            const auto lambda = [&](const auto& pair) -> bool { return pair.second == strp; };

            std::size_t wordcode = 256u;

            int C = input_file.get();

            while ( ! input_file.eof() )
            {
                std::string strc;
                strc += static_cast<char>(C);

                std::string strpc;
                strpc = strp + strc;

                if (rn::find_if(dictionary, [&](const auto& pair) -> bool { return pair.second == strpc; }) != dictionary.cend())
                {
                    strp = strpc;
                }
                else
                {
                    dictionary.emplace_back(wordcode, strpc);

                    // std::cout << wordcode << '\t' << strpc << '\n';

                    output_file << (strp.length() == 1u ? static_cast<std::size_t>(strp[0]) : (rn::find_if(dictionary, lambda))->first) << ' ';

                    ++wordcode;

                    strp = strc;
                }

                C = input_file.get();
            }

            output_file << (strp.length() == 1u ? static_cast<std::size_t>(strp[0]) : (rn::find_if(dictionary, lambda))->first);
        }
    }
    void LZW::Decompress(const std::string& input_filename)
    {
        std::ifstream input_file(input_filename, std::ios::binary);

        if ( ! input_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened for [Decompressing]!");
        }

        const auto name_ext = fatpound::file::GetNameAndExtension(input_filename);

        std::ofstream output_file(name_ext.first + "_decompressed" + "." + name_ext.second, std::ios::binary);

        if ( ! output_file.is_open() )
        {
            throw std::runtime_error("Compressed file cannot be created!");
        }

        std::vector<std::pair<std::size_t, std::string>> dictionary;
        InitializeDictionary_(dictionary);

        if ( ! input_file.eof() )
        {
            int oldcode;
            input_file >> oldcode;

            std::string S;
            S += static_cast<char>(oldcode);

            output_file << S;

            std::size_t wordcode = 256u;

            while ( ! input_file.eof() )
            {
                int newcode;
                input_file >> newcode;

                const auto it = rn::find_if(dictionary, [&](const auto& pair) -> bool { return pair.first == newcode; });

                if (it == dictionary.cend())
                {
                    S += S[0];
                }
                else
                {
                    S = it->second;
                }

                output_file << S;

                std::string tempstr;
                tempstr += rn::find_if(dictionary, [&](const auto& pair) -> bool { return pair.first == oldcode; })->second;
                tempstr += S[0];

                dictionary.emplace_back(wordcode, tempstr);

                // std::cout << wordcode << '\t' << tempstr << '\n';

                oldcode = newcode;

                ++wordcode;
            }
        }
    }

    void LZW::InitializeDictionary_(std::vector<std::pair<std::size_t, std::string>>& dictionary)
    {
        std::string tempstr;
        
        for (std::size_t i = 'A'; i <= 'Z'; ++i)
        {
            tempstr = static_cast<char>(i);
            dictionary.emplace_back(i, tempstr);
        }

        for (std::size_t i = 'a'; i <= 'z'; ++i)
        {
            tempstr = static_cast<char>(i);
            dictionary.emplace_back(i, tempstr);
        }
    }
}