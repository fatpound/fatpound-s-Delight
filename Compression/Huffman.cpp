#include "Huffman.hpp"

#include <sstream>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::compression
{
    Huffman::~Huffman() noexcept
    {
        Delete_(root_);
    }

    Huffman::Huffman(const std::string& input)
    {
        if (input.length() == 0)
        {
            return;
        }

        std::vector<std::pair<int64_t, char>> pairs;

        for (const auto& ch : input)
        {
            int64_t index = -1;

            for (size_t i = 0u; i < pairs.size(); ++i)
            {
                if (pairs[i].second == ch)
                {
                    index = i;
                }
            }

            if (index == -1)
            {
                pairs.emplace_back(1, ch);
            }
            else
            {
                pairs[index].first++;
            }
        }

        rn::sort(pairs, [](const auto& a, const auto& b) -> bool { return a.first < b.first; });

        std::deque<Node*> deque;
        deque.resize(pairs.size());

        for (size_t i = 0; i < pairs.size(); ++i)
        {
            deque[i] = new Node(pairs[i].first, pairs[i].second);
        }

        const size_t first_size = deque.size();

        for (size_t i = 0u; i < first_size - 1u; ++i)
        {
            Node* const left = deque[0];
            Node* const right = deque[1];

            Node* newnode = new Node(left, right);

            deque.pop_front();
            deque.pop_front();

            size_t index = 0u;

            for (size_t j = 0u; j < deque.size(); ++j)
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

        root_ = deque[0];
        node_count_ = first_size * 2 - 1;

        SetBinaryValues_(root_);
    }


    std::string Huffman::GetDecompressed(const std::string& bin)
    {
        std::string decompressed;

        for (size_t i = 0u; i < bin.size(); ++i)
        {
            std::string temp = "";

            int64_t index = -1;

            for (size_t j = i; j < bin.size() && temp.size() <= max_depth_; ++j)
            {
                temp += bin[j];

                if (temp.size() < min_depth_)
                {
                    continue;
                }

                for (size_t k = 0; k < results_binary_.size(); ++k)
                {
                    if (temp == results_binary_[k])
                    {
                        index = k;

                        break;
                    }
                }

                if (index != -1)
                {
                    decompressed += results_chars_[index];

                    i += temp.size() - 1;

                    break;
                }
            }

            if (index == -1)
            {
                throw std::runtime_error("Incorrect Format!");
            }
        }

        std::ostringstream oss;

        oss << "Decompressed: " << decompressed << '\n';

        size_t size = bin.size();

        double numerator = static_cast<double>(size / 8);

        if (size % 8u != 0)
        {
            ++numerator;
        }

        const double denominator = static_cast<double>(decompressed.size());
        const double rate = numerator * 100 / denominator;

        oss << "Package count: " << numerator << '\n';
        oss << "Compression rate: %" << rate << " ~= " << numerator << '/' << denominator << '\n';

        return oss.str();
    }

    void Huffman::ListTreePreorder() const
    {
        std::cout << "Output : ";

        ListTreePreorder_(root_);

        std::cout << '\n';
    }

    void Huffman::SetBinaryValues_(Node* node, const std::string& str)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left_ == nullptr && node->right_ == nullptr)
        {
            results_chars_.push_back(node->k_);
            results_binary_.push_back(str);

            if (max_depth_ < str.size())
            {
                max_depth_ = str.size();
            }

            if (min_depth_ > str.size())
            {
                min_depth_ = str.size();
            }

            return;
        }

        SetBinaryValues_(node->left_,  str + "0");
        SetBinaryValues_(node->right_, str + "1");
    }
    void Huffman::ListTreePreorder_(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left_ == nullptr && node->right_ == nullptr)
        {
            std::cout << node->k_ << '*' << node->num_ << ' ';

            return;
        }

        std::cout << node->num_ << ' ';

        ListTreePreorder_(node->left_);
        ListTreePreorder_(node->right_);
    }
    void Huffman::Delete_(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        Delete_(node->left_);
        Delete_(node->right_);

        delete node;
    }


    Huffman::Node::Node(Node* left, Node* right)
        :
        left_(left),
        right_(right),
        num_(left->num_ + right->num_)
    {

    }
    Huffman::Node::Node(int64_t num, char k)
        :
        num_(num),
        k_(k)
    {

    }
}