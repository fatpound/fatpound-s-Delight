#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>

namespace fatpound::automata
{
    class TLTree_v2
    {
    public:
        TLTree_v2() = delete;

        TLTree_v2(const std::vector<std::pair<std::string, std::vector<std::string>>>& trees);

        TLTree_v2(const TLTree_v2& src) = delete;
        TLTree_v2(TLTree_v2&& src) = delete;
        TLTree_v2& operator = (const TLTree_v2& src) = delete;
        TLTree_v2& operator = (TLTree_v2&& src) = delete;
        ~TLTree_v2() noexcept;


    public:
        struct Node
        {
            std::vector<Node*> leaves_;

            std::string item_;

            Node(const std::pair<std::string, std::vector<std::string>>& tree);
            Node(const std::string& str);
        };


    public:
        std::vector<std::pair<std::string, bool>> GetWords();


    protected:


    private:
        std::vector<std::pair<std::string, bool>> Generate_(std::string init_str = "", size_t index = 0u, size_t recursed = 0u) const;

        bool IsTerminal_(const std::string& str) const;


    private:
        std::vector<std::pair<std::string, bool>> results_;

        std::vector<Node*> trees_;

        static constexpr const size_t recurse_limit_ = 1u;
    };
}