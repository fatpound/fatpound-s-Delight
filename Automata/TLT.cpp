#include "TLT.hpp"

#include <iostream>
#include <deque>
#include <algorithm>

namespace rn = std::ranges;

namespace fatpound::automata
{
    // TLT

    TLT::TLT(const Vector<Pair<String, Vector<String>>>& cfgs)
        :
        cfgs_(cfgs),
        recurse_(cfgs_.size(), 0)
    {
        if (cfgs_.size() < 1)
        {
            throw std::runtime_error("There is no input!");
        }

        tree_ = new Node_(cfgs_[0].first);

        for (const auto& leaf_str : cfgs_[0].second)
        {
            tree_->leaves_.push_back(new Node_(leaf_str));
        }

        CreateTree_(tree_);
    }
    TLT::~TLT() noexcept
    {
        std::deque<Node_*> nodes;

        if (tree_ != nullptr)
        {
            nodes.push_back(tree_);
        }

        while (nodes.size() > 0u)
        {
            Node_* node = nodes.back();

            nodes.pop_back();

            for (auto& leaf : node->leaves_)
            {
                nodes.push_back(leaf);
            }

            delete node;
        }
    }

    auto TLT::GetWords() const noexcept -> const Vector<String>&
    {
        return results_;
    }

    bool TLT::IsTerminal_(const String& word) noexcept
    {
        return rn::all_of(word, [](const auto& ch) -> bool { return std::islower(ch); });
    }

    void TLT::CreateTree_(Node_* node)
    {
        results_.reserve(node->leaves_.size());

        for (auto& leaf : node->leaves_)
        {
            if (TLT::IsTerminal_(leaf->item_))
            {
                results_.push_back(leaf->item_);

                continue;
            }

            CreateInnerTree_(leaf);
        }
    }
    void TLT::CreateInnerTree_(Node_* node)
    {
        for (std::size_t i = 0u; i < node->item_.size(); ++i)
        {
            const auto& ch = node->item_[i];

            if (std::isupper(ch))
            {
                const auto& cfg_it = rn::find_if(cfgs_, [&](const auto& pair) { return pair.first[0] == ch; });

                String leftstr(node->item_.cbegin(), node->item_.cbegin() + i);
                String rightstr(node->item_.cbegin() + i + 1, node->item_.cend());

                const std::size_t index = cfg_it - cfgs_.cbegin();

                node->leaves_.reserve(node->leaves_.size() + cfg_it->second.size());

                for (const auto& cfgstr : cfg_it->second)
                {
                    // String str = cfgstr;

                    bool recursed = false;

                    if (cfgstr.contains(ch))
                    {
                        if (recurse_[index] >= recurse_limit_)
                        {
                            // const auto [first, last] = rn::remove_if(str, [](const auto& ch) { return std::isupper(ch); });
                            // 
                            // str.erase(first, last);

                            continue;
                        }

                        recursed = true;

                        ++recurse_[index];
                    }

                    const String& newstr = leftstr + cfgstr + rightstr;

                    Node_* newnode = new Node_(newstr);

                    node->leaves_.push_back(newnode);

                    if (recursed || !IsTerminal_(newstr))
                    {
                        CreateInnerTree_(newnode);
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


    // Node_

    TLT::Node_::Node_(const String& item)
        :
        item_(item)
    {

    }
}