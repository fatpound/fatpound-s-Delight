#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace rn = std::ranges;

namespace fatpound::automata
{
    class TLTree
    {
    public:
        TLTree() = delete;
        ~TLTree() noexcept
        {
            std::deque<Node*> nodes;

            if (tree_ != nullptr)
            {
                nodes.push_back(tree_);
            }

            while (nodes.size() > 0u)
            {
                Node* node = nodes.back();

                nodes.pop_back();

                for (auto& leaf : node->leaves_)
                {
                    nodes.push_back(leaf);
                }

                delete node;
            }
        }
        TLTree(const TLTree& src) = delete;
        TLTree(TLTree&& src) = delete;
        TLTree& operator = (const TLTree& src) = delete;
        TLTree& operator = (TLTree&& src) = delete;

        TLTree(const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs)
            :
            cfgs_(cfgs),
            recurse_(cfgs_.size(), 0)
        {
            if (cfgs_.size() < 1)
            {
                throw std::runtime_error("There is no input!");
            }

            tree_ = new Node(cfgs_[0].first);

            for (const auto& leaf_str : cfgs_[0].second)
            {
                tree_->leaves_.push_back(new Node(leaf_str));
            }

            CreateTree(tree_);
        }


    public:
        std::vector<std::string> GetWords() const
        {
            return results_;
        }


    protected:


    private:
        struct Node
        {
            std::vector<Node*> leaves_;

            std::string item_;

            Node(const std::string& item)
                :
                item_(item)
            {

            }
        };


    private:
        bool IsTerminal(const std::string& word) const
        {
            return rn::all_of(word, [](const auto& ch) -> bool { return std::islower(ch); });
        }

        void CreateTree(Node* node)
        {
            results_.reserve(node->leaves_.size());

            for (auto& node : node->leaves_)
            {
                if (IsTerminal(node->item_))
                {
                    results_.push_back(node->item_);

                    continue;
                }

                CreateInnerTree(node);
            }
        }
        void CreateInnerTree(Node* node)
        {
            for (size_t i = 0u; i < node->item_.size(); ++i)
            {
                const auto& ch = node->item_[i];

                if (std::isupper(ch))
                {
                    const auto& cfg_it = rn::find_if(cfgs_, [&](const auto& pair) { return pair.first[0] == ch; });

                    std::string leftstr(node->item_.cbegin(), node->item_.cbegin() + i);
                    std::string rightstr(node->item_.cbegin() + i + 1, node->item_.cend());

                    const size_t index = cfg_it - cfgs_.cbegin();

                    node->leaves_.reserve(node->leaves_.size() + cfg_it->second.size());

                    for (const auto& cfgstr : cfg_it->second)
                    {
                        //std::string str = cfgstr;

                        bool recursed = false;

                        if (cfgstr.contains(ch))
                        {
                            if (recurse_[index] >= recurse_limit_)
                            {
                                //const auto [first, last] = rn::remove_if(str, [](const auto& ch) { return std::isupper(ch); });
                                //
                                //str.erase(first, last);

                                continue;
                            }

                            recursed = true;

                            ++recurse_[index];
                        }
                        
                        const std::string& newstr = leftstr + cfgstr + rightstr;

                        Node* newnode = new Node(newstr);

                        node->leaves_.push_back(newnode);

                        if ( ! IsTerminal(newstr) )
                        {
                            CreateInnerTree(newnode);
                        }
                        else
                        {
                            results_.push_back(newstr);
                        }

                        if (recursed)
                        {
                            --recurse_[index];
                        }
                    }
                }
            }
        }


    private:
        const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs_;
        std::vector<std::string> results_;
        std::vector<size_t> recurse_;

        Node* tree_ = nullptr;

        static constexpr const size_t recurse_limit_ = 1u;
    };
}
