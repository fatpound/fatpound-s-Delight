#include "TLTree_v2.hpp"

namespace fatpound::automata
{
    TLTree_v2::TLTree_v2(const std::vector<std::pair<std::string, std::vector<std::string>>>& trees)
    {
        trees_.reserve(trees.size());

        for (const auto& tree : trees)
        {
            trees_.push_back(new Node_(tree));
        }

        results_ = Generate_("", 0u, 0u);
    }
    TLTree_v2::~TLTree_v2() noexcept
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

    std::vector<std::pair<std::string, bool>> TLTree_v2::GetWords()
    {
        return results_;
    }

    std::vector<std::pair<std::string, bool>> TLTree_v2::Generate_(std::string init_str, std::size_t index, std::size_t recursed) const
    {
        std::vector<std::pair<std::string, bool>> strings;

        for (const auto& node : trees_[index]->leaves_)
        {
            std::vector<std::pair<std::string, bool>> tempstrings;

            tempstrings.emplace_back(init_str, false);

            for (const auto& ch : node->item_)
            {
                std::vector<std::pair<std::string, bool>> newTempStrings;

                for (const auto& strPair : tempstrings)
                {
                    std::string& str = newTempStrings.emplace_back(strPair).first;
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

                        if (recursed < recurse_limit_)
                        {
                            const std::size_t size = tempstrings.size();

                            bool deleted = false;

                            std::string tempstr = strPair.first;

                            if (tempstr == "")
                            {
                                continue;
                            }

                            const auto vec = Generate_(tempstr, tree_index, recursed + will_recurse);

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

    bool TLTree_v2::IsTerminal_(const std::string& str) const
    {
        for (const auto& tree : trees_)
        {
            if (std::any_of(str.cbegin(), str.cend(), [&](const auto& ch) -> bool { return ch == (tree->item_[0]); }))
            {
                return false;
            }
        }

        return true;
    }


    TLTree_v2::Node_::Node_(const std::pair<std::string, std::vector<std::string>>& tree)
        :
        item_(tree.first)
    {
        leaves_.reserve(tree.second.size());

        for (const auto& str : tree.second)
        {
            leaves_.push_back(new Node_(str));
        }
    }
    TLTree_v2::Node_::Node_(const std::string& str)
        :
        item_(str)
    {

    }
}