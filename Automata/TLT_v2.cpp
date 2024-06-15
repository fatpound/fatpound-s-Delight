#include "TLT_v2.hpp"

#include <iostream>
#include <deque>
#include <algorithm>

namespace rn = std::ranges;

using namespace std::literals::string_literals;

namespace fatpound::automata
{
    // TLT_v2

    TLT_v2::TLT_v2(const Vector<Pair<String, Vector<String>>>& trees)
    {
        trees_.reserve(trees.size());

        for (const auto& tree : trees)
        {
            trees_.push_back(new Node_(tree));
        }

        results_ = Generate_(""s, 0u, 0u);
    }
    TLT_v2::~TLT_v2() noexcept
    {
        std::deque<Node_*> nodes;

        for (auto& tree : trees_)
        {
            if (tree != nullptr)
            {
                nodes.push_back(tree);
            }
            else
            {
                continue;
            }

            while (nodes.size() > 0)
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
    }

    auto TLT_v2::GetWords() const noexcept -> Vector<Pair<String, bool>>
    {
        return results_;
    }

    auto TLT_v2::Generate_(String init_str, std::size_t index, std::size_t recursed_count) const -> Vector<Pair<String, bool>>
    {
        Vector<Pair<String, bool>> strings;

        for (const auto& node : trees_[index]->leaves_)
        {
            Vector<Pair<String, bool>> tempstrings;

            tempstrings.emplace_back(init_str, false);

            for (const auto& ch : node->item_)
            {
                Vector<Pair<String, bool>> newTempStrings;

                for (const auto& strPair : tempstrings)
                {
                    String& str = newTempStrings.emplace_back(strPair).first;
                    const std::size_t insertedindex = newTempStrings.size() - 1;

                    const auto it = std::find_if(trees_.cbegin() + index, trees_.cend(), [&](const auto& tree) -> bool { return ch == tree->item_[0]; });

                    if (it == trees_.cend())
                    {
                        str += ch;
                    }
                    else
                    {
                        const std::size_t tree_index = it - trees_.cbegin();
                        const std::size_t will_recurse = ((tree_index == index) ? 1 : 0);

                        if (recursed_count < recurse_limit_)
                        {
                            String tempstr = strPair.first;

                            if (tempstr == ""s)
                            {
                                continue;
                            }

                            const auto vec = Generate_(tempstr, tree_index, recursed_count + will_recurse);

                            for (const auto& pair : vec)
                            {
                                newTempStrings.emplace_back(pair);
                            }

                            newTempStrings.erase(newTempStrings.begin() + insertedindex);
                        }
                        else
                        {
                            str += ch;
                        }
                    }
                }

                tempstrings = std::move(newTempStrings);
            }

            for (const auto& strPair : tempstrings)
            {
                strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
            }
        }

        return strings;
    }

    bool TLT_v2::IsTerminal_(const String& str) const
    {
        for (const auto& tree : trees_)
        {
            if (rn::any_of(str, [&](const auto& ch) -> bool { return ch == (tree->item_[0]); }))
            {
                return false;
            }
        }

        return true;
    }


    // Node_

    TLT_v2::Node_::Node_(const Pair<String, Vector<String>>& tree)
        :
        item_(tree.first)
    {
        leaves_.reserve(tree.second.size());

        for (const auto& str : tree.second)
        {
            leaves_.push_back(new Node_(str));
        }
    }
    TLT_v2::Node_::Node_(const String& str)
        :
        item_(str)
    {

    }
}