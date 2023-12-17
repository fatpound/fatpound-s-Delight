#pragma once

#include <iostream>
#include <vector>
#include <queue>

namespace fatpound::tree
{
    template <typename T, size_t I, size_t S>
    class B_Plus
    {
    public:
        B_Plus() = default;
        ~B_Plus() noexcept
        {
            if (root_ == nullptr)
            {
                return;
            }

            class Node;

            std::queue<Node*> Q;
            Q.push(root_);

            while (Q.size() > 0ui64)
            {
                Node* u = Q.front();
                Q.pop();

                if (u->lesser != nullptr)
                {
                    Q.push(u->lesser);
                }

                for (size_t i = 0ui64; i < u->items.size(); ++i)
                {
                    if (u->items[i]->second != nullptr)
                    {
                        Q.push(u->items[i]->second);
                    }

                    delete u->items[i];
                }

                delete u;
            }

            root_ = nullptr;
        }
        B_Plus(const B_Plus<T, I, S>& src) = delete;
        B_Plus(B_Plus<T, I, S>&& src) = delete;
        B_Plus<T, I, S>& operator = (const B_Plus<T, I, S>& src) = delete;
        B_Plus<T, I, S>& operator = (B_Plus<T, I, S>&& src) = delete;


    public:
		void Insert(const T& new_item)
		{
			if (root_ == nullptr)
			{
				root_ = new Node(new_item, nullptr, nullptr);
				root_->lesser = new Node(new_item, nullptr, root_);

				return;
			}

			Insert(root_, new_item);

			itemCount_++;
		}
		void ListLevelorder() const
		{
			const int64_t height = GetDepth(root_);

			for (int64_t i = 1i64; i <= height; ++i)
			{
				std::cout << "Level " << i << " : ";

				ListLevelorder(root_, i);

				std::cout << '\n';
			}

			std::cout << '\n';
		}


    protected:


    private:
        class Node
        {
        public:
            Node() = default;

            Node(std::vector<std::pair<T, Node*>*>& new_items, Node* new_lesser, Node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent),
                items( std::move(new_items) )
            {
                
            }
            Node(std::pair<T, Node*>* new_pair, Node* new_lesser, Node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new_pair);
            }
            Node(const T& new_item, Node* new_lesser, Node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new std::pair<T, Node*>(new_item, nullptr));
            }

        public:
            std::vector<std::pair<T, Node*>*> items;

            Node* lesser = nullptr;
            Node* parent = nullptr;

        protected:

        private:
        };


    private:
		int64_t GetDepth(Node* node, int64_t depth = 0i64) const
		{
			if (node == nullptr)
			{
				return depth;
			}

			return GetDepth(node->lesser, depth + 1i64);
		}

        void Insert(Node* node, T new_item)
        {
            Insert(node, new std::pair<T, Node*>(new_item, nullptr), nullptr, false);
        }
		void Insert(Node* node, std::pair<T, Node*>* new_pair, Node* extend_node, bool extend, bool create = true)
		{
			if (node == nullptr)
			{
				return;
			}

			if (extend)
			{
				goto extension;
			}

			size_t index;


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

			index = 0ui64;

			for (size_t i = 0ui64; i < node->items.size(); ++i)
			{
				if (new_pair->first > node->items[i]->first)
				{
					index = i;
				}
			}

			if (node->items[index]->second == nullptr)
			{
				node->items[index]->second = new Node(new_pair, nullptr, node);
				return;
			}
			else
			{
				node = node->items[index]->second;
				goto control;
			}


		sequence:


			if (node->items.size() == S * 2ui64)
			{
				Overflow(node, new_pair, nullptr, false);
			}
			else
			{
				node->items.push_back(new_pair);

				if (node->items.size() > 1ui64)
				{
					std::sort(
						node->items.begin(),
						node->items.end(),
						[](const auto p1, const auto p2)
						{
							return p1->first < p2->first;
						}
					);
				}
			}

			return;


		extension:


			if (node->items.size() == I * 2ui64)
			{
				if (create)
				{
					Overflow(node, new std::pair<T, Node*>(new_pair->first, nullptr), extend_node, true);
				}
				else
				{
					Overflow(node, new_pair, extend_node, true);
				}
			}
			else
			{
				if (create)
				{
					node->items.push_back(new std::pair<T, Node*>(new_pair->first, extend_node));
				}
				else
				{
					node->items.push_back(new_pair);
					extend_node->lesser = new_pair->second;
					new_pair->second = extend_node;
				}

				if (node->items.size() > 1ui64)
				{
					std::sort(
						node->items.begin(),
						node->items.end(),
						[](std::pair<T, Node*>* p1, std::pair<T, Node*>* p2)
						{
							return p1->first < p2->first;
						}
					);
				}
			}
		}
		void Overflow(Node* node, std::pair<T, Node*>* new_pair, Node* extend_node, bool extend)
		{
			const size_t a = (node->lesser == nullptr ? S : I);

			node->items.push_back(new_pair);
			new_pair->second = extend_node;

			std::sort(
				node->items.begin(),
				node->items.end(),
				[](const auto p1, const auto p2)
				{
					return p1->first < p2->first;
				}
			);

			size_t center = (a * 2ui64 + 1ui64) / 2ui64;

			Node* new_node = new Node();

			for (size_t i = center + 1ui64; i <= a * 2ui64; ++i)
			{
				new_node->items.push_back(node->items[i]);
			}

			if (extend)
			{
				if (node == root_)
				{
					Node* new_parent = new Node();

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

					Insert(node->parent, node->items[center], new_node, true, false);
				}

				extend_node->parent = new_node;
				//new_pair->second = extend_node;
				new_node->parent = node->parent;

				for (size_t i = 0ui64; i < new_node->items.size(); ++i)
				{
					if (new_node->items[i]->second != nullptr)
					{
						new_node->items[i]->second->parent = new_node;
					}
				}

				node->items.resize(center);
			}
			else
			{
				new_node->parent = node->parent;
				node->items.resize(center + 1ui64);
				Insert(node->parent, node->items[center], new_node, true);
			}
		}
		void ListLevelorder(const Node* node, int64_t level) const
		{
			if (node != nullptr)
			{
				if (level == 1ui64)
				{
					for (size_t i = 0ui64; i < node->items.size(); ++i)
					{
						std::cout << node->items[i]->first << ' ';
					}
				}
				else if (level > 1ui64)
				{
					ListLevelorder(node->lesser, level - 1ui64);

					for (size_t i = 0ui64; i < node->items.size(); ++i)
					{
						ListLevelorder(node->items[i]->second, level - 1ui64);
						std::cout << '\t';
					}
				}
			}
			else if (level == 1ui64)
			{
				std::cout << "x ";
			}
		}


    private:
        Node* root_ = nullptr;

        size_t itemCount_ = 0ui64;
    };
}