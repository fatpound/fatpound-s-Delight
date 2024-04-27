#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>

namespace fatpound::automata
{
    class TLTree_v2 final
    {
    public:
        TLTree_v2(const std::vector<std::pair<std::string, std::vector<std::string>>>& trees);

        TLTree_v2() = delete;
        TLTree_v2(const TLTree_v2& src) = delete;
        TLTree_v2& operator = (const TLTree_v2& src) = delete;
        TLTree_v2(TLTree_v2&& src) = delete;
        TLTree_v2& operator = (TLTree_v2&& src) = delete;
        ~TLTree_v2() noexcept;


    public:
        std::vector<std::pair<std::string, bool>> GetWords();


    protected:


    private:
        struct Node_ final
        {
            std::vector<Node_*> leaves_;

            std::string item_;

            Node_(const std::pair<std::string, std::vector<std::string>>& tree);
            Node_(const std::string& str);
        };


    private:
        std::vector<std::pair<std::string, bool>> Generate_(std::string init_str = "", std::size_t index = 0u, std::size_t recursed = 0u) const;

        bool IsTerminal_(const std::string& str) const;


    private:
        std::vector<std::pair<std::string, bool>> results_;

        std::vector<Node_*> trees_;

        static constexpr const std::size_t recurse_limit_ = 1u;
    };
}