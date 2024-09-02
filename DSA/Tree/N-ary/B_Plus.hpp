#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ranges>

namespace fatpound::dsa::tree::n_ary
{
    template <std::totally_ordered T, std::size_t I, std::size_t S>
    class B_Plus final
    {
        using SizeType = std::size_t;
        
    public:
        explicit B_Plus() = default;
        explicit B_Plus(const B_Plus& src) = delete;
        explicit B_Plus(B_Plus&& src) = delete;

        auto operator = (const B_Plus& src) -> B_Plus& = delete;
        auto operator = (B_Plus&& src)      -> B_Plus& = delete;
        ~B_Plus() noexcept
        {
            Clear_();
        }


    public:
        auto Contains(const T& item) -> bool
        {
            if (root_ not_eq nullptr)
            {
                Node_* node = root_;

                while (node->lesser not_eq nullptr)
                {
                    std::size_t idx = 0u;

                    for (; idx < node->items.size(); ++idx)
                    {
                        if (node->items[idx]->first >= item)
                        {
                            break;
                        }
                    }

                    if (idx not_eq 0u)
                    {
                        --idx;
                    }

                    if (idx == 0u)
                    {
                        if ((node->items[idx]->first > item) or (node->items[idx]->second not_eq nullptr))
                        {
                            node = node->lesser;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        node = node->items[node->items[idx]->first > item ? (idx - 1u) : idx]->second;
                    }
                }

                for (std::size_t i = 0u; i < node->items.size(); ++i)
                {
                    if (node->items[i]->first > item)
                    {
                        break;
                    }

                    if (node->items[i]->first == item)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        void Insert(const T& new_item)
        {
            if (Contains(new_item))
            {
                return;
            }

            if (root_ == nullptr)
            {
                root_ = new Node_(new_item, nullptr, nullptr);
                root_->lesser = new Node_(new_item, nullptr, root_);

                return;
            }

            Insert_(root_, new_item);

            item_count_++;
        }
        void ListLevelorder() const
        {
            if (root_ == nullptr)
            {
                return;
            }

            const SizeType height = GetDepth_(root_);

            for (SizeType i = 1u; i <= height; ++i)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }


    protected:


    private:
        struct Node_ final
        {
            std::vector<std::pair<T, Node_*>*> items;

            Node_* lesser = nullptr;
            Node_* parent = nullptr;

            Node_() = default;

            Node_(std::vector<std::pair<T, Node_*>*>& new_items, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent),
                items(std::move(new_items))
            {

            }
            Node_(std::pair<T, Node_*>* new_pair, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new_pair);
            }
            Node_(const T& new_item, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new std::pair<T, Node_*>(new_item, nullptr));
            }
        };


    private:
        auto GetDepth_(Node_* node, std::size_t depth = 0u) const -> std::size_t
        {
            if (node == nullptr)
            {
                return depth;
            }

            return GetDepth_(node->lesser, depth + 1);
        }

        void Insert_(Node_* node, T new_item)
        {
            Insert_(node, new std::pair<T, Node_*>(new_item, nullptr), nullptr, false);
        }
        void Insert_(Node_* node, std::pair<T, Node_*>* new_pair, Node_* extend_node, bool extend, bool create = true)
        {
            if (node == nullptr)
            {
                return;
            }

            std::size_t index{};

            if (extend)
            {
                goto extension;
            }


        control:


            if (node->lesser == nullptr)
            {
                goto sequence;
            }

            if (new_pair->first <= node->items[0]->first)
            {
                node = node->lesser;
                goto control;
            }

            index = 0u;

            for (std::size_t i = 0u; i < node->items.size(); ++i)
            {
                if (new_pair->first > node->items[i]->first)
                {
                    index = i;
                }
            }

            if (node->items[index]->second == nullptr)
            {
                node->items[index]->second = new Node_(new_pair, nullptr, node);

                return;
            }
            
            
            node = node->items[index]->second;
            goto control;


        sequence:


            if (node->items.size() == S * 2u)
            {
                Overflow_(node, new_pair, nullptr, false);
            }
            else
            {
                node->items.push_back(new_pair);

                if (node->items.size() > 1u)
                {
                    std::ranges::sort(node->items, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });
                }
            }

            return;


        extension:


            if (node->items.size() == I * 2u)
            {
                if (create)
                {
                    Overflow_(node, new std::pair<T, Node_*>(new_pair->first, nullptr), extend_node, true);
                }
                else
                {
                    Overflow_(node, new_pair, extend_node, true);
                }
            }
            else
            {
                if (create)
                {
                    node->items.push_back(new std::pair<T, Node_*>(new_pair->first, extend_node));
                }
                else
                {
                    node->items.push_back(new_pair);
                    extend_node->lesser = new_pair->second;
                    new_pair->second = extend_node;
                }

                if (node->items.size() > 1u)
                {
                    std::ranges::sort(node->items, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });
                }
            }
        }
        void Overflow_(Node_* node, std::pair<T, Node_*>* new_pair, Node_* extend_node, bool extend)
        {
            const auto indexOrSetCount = (node->lesser == nullptr ? S : I);

            node->items.push_back(new_pair);
            new_pair->second = extend_node;

            std::ranges::sort(node->items, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });

            const auto center = (indexOrSetCount * 2u + 1u) / 2u;

            auto* const new_node = new Node_();

            new_node->items.reserve(indexOrSetCount * 2u);

            for (std::size_t i = center + 1u; i <= indexOrSetCount * 2u; ++i)
            {
                new_node->items.push_back(node->items[i]);
            }

            if (extend)
            {
                if (node == root_)
                {
                    auto* const new_parent = new Node_();

                    new_parent->lesser = root_;
                    root_->parent = new_parent;
                    root_ = new_parent;

                    root_->items.push_back(node->items[center]);
                    new_node->lesser = node->items[center]->second;
                    node->items[center]->second = new_node;
                }
                else
                {
                    new_pair->second = extend_node;
                    new_node->lesser = node->items[center]->second;
                    node->items[center]->second->parent = new_node;

                    Insert_(node->parent, node->items[center], new_node, true, false);
                }

                extend_node->parent = new_node;
                //new_pair->second = extend_node;
                new_node->parent = node->parent;

                for (std::size_t i = 0u; i < new_node->items.size(); ++i)
                {
                    if (new_node->items[i]->second not_eq nullptr)
                    {
                        new_node->items[i]->second->parent = new_node;
                    }
                }

                node->items.resize(center);
            }
            else
            {
                new_node->parent = node->parent;
                node->items.resize(center + 1u);

                Insert_(node->parent, node->items[center], new_node, true);
            }
        }
        void ListLevelorder_(const Node_* const node, std::size_t level) const
        {
            if (node not_eq nullptr)
            {
                if (level == 1u)
                {
                    for (std::size_t i = 0u; i < node->items.size(); ++i)
                    {
                        std::cout << node->items[i]->first << ' ';
                    }
                }
                else if (level > 1u)
                {
                    ListLevelorder_(node->lesser, level - 1u);

                    for (std::size_t i = 0u; i < node->items.size(); ++i)
                    {
                        ListLevelorder_(node->items[i]->second, level - 1u);

                        std::cout << '\t';
                    }
                }
            }
            else if (level == 1u)
            {
                std::cout << "x ";
            }

            std::cout << '\t';
        }

        void Clear_()
        {
            if (root_ == nullptr)
            {
                return;
            }

            std::queue<Node_*> queue;

            queue.push(root_);

            while (queue.size() > 0u)
            {
                auto* const node = queue.front();
                queue.pop();

                if (node->lesser not_eq nullptr)
                {
                    queue.push(node->lesser);
                }

                for (std::size_t i = 0u; i < node->items.size(); ++i)
                {
                    if (node->items[i]->second not_eq nullptr)
                    {
                        queue.push(node->items[i]->second);
                    }

                    delete node->items[i];
                }

                delete node;
            }

            root_ = nullptr;
        }


    private:
        Node_* root_ = nullptr;

        std::size_t item_count_ = 0u;
    };
}
