#include "TLTree.hpp"

namespace fatpound::automata
{
    TLTree::TLTree(const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs)
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
    TLTree::~TLTree() noexcept
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

    const std::vector<std::string>& TLTree::GetWords() const
    {
        return results_;
    }

    bool TLTree::IsTerminal_(const std::string& word) const
    {
        return std::ranges::all_of(word, [](const auto& ch) -> bool { return std::islower(ch); });
    }

    void TLTree::CreateTree_(Node_* node)
    {
        results_.reserve(node->leaves_.size());

        for (auto& node : node->leaves_)
        {
            if (IsTerminal_(node->item_))
            {
                results_.push_back(node->item_);

                continue;
            }

            CreateInnerTree_(node);
        }
    }
    void TLTree::CreateInnerTree_(Node_* node)
    {
        for (std::size_t i = 0u; i < node->item_.size(); ++i)
        {
            const auto& ch = node->item_[i];

            if (std::isupper(ch))
            {
                const auto& cfg_it = std::ranges::find_if(cfgs_, [&](const auto& pair) { return pair.first[0] == ch; });

                std::string leftstr(node->item_.cbegin(), node->item_.cbegin() + i);
                std::string rightstr(node->item_.cbegin() + i + 1, node->item_.cend());

                const std::size_t index = cfg_it - cfgs_.cbegin();

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

    TLTree::Node_::Node_(const std::string& item)
        :
        item_(item)
    {

    }
}