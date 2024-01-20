#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>

namespace fatpound::automata
{
    class CFGTree
    {
    public:
        CFGTree() = delete;
        ~CFGTree() noexcept;
        CFGTree(const CFGTree& src) = delete;
        CFGTree(CFGTree&& src) = delete;
        CFGTree& operator = (const CFGTree& src) = delete;
        CFGTree& operator = (CFGTree&& src) = delete;

        CFGTree(const std::vector<std::pair<std::string, std::vector<std::string>>>& trees);


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