#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace fatpound::automata
{
    class TLTree final
    {
    public:
        TLTree(const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs);

        TLTree() = delete;
        TLTree(const TLTree& src) = delete;
        TLTree& operator = (const TLTree& src) = delete;
        TLTree(TLTree&& src) = delete;
        TLTree& operator = (TLTree&& src) = delete;
        ~TLTree() noexcept;


    public:
        const std::vector<std::string>& GetWords() const;


    protected:


    private:
        struct Node_ final
        {
            std::vector<Node_*> leaves_;

            std::string item_;

            Node_(const std::string& item);
        };


    private:
        bool IsTerminal_(const std::string& word) const;

        void CreateTree_(Node_* node);
        void CreateInnerTree_(Node_* node);


    private:
        const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs_;
        std::vector<std::string> results_;
        std::vector<std::size_t> recurse_;

        Node_* tree_ = nullptr;

        static constexpr std::size_t recurse_limit_ = 1u;
    };
}