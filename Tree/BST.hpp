#pragma once

#include <iostream>
#include <concepts>

namespace fatpound::tree
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        BST() = default;
        ~BST() noexcept
        {
            Delete(root_);
            root_ = nullptr;
            nodeCount_ = 0ui64;
        }
        BST(const BST<T>& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.Cloner(src.root_);
                nodeCount_ = src.nodeCount_;
            }
        }
        BST(BST<T>&& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.root_;
                nodeCount_ = src.nodeCount_;

                src.root_ = nullptr;
                src.nodeCount_ = 0ull;
            }
        }
        BST<T>& operator = (const BST<T>& src) noexcept
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete(root_);

                    root_ = nullptr;
                    nodeCount_ = 0ull;
                }

                root_ = src.Cloner(src.root_);
                nodeCount_ = src.nodeCount_;
            }

            return *this;
        }
        BST<T>& operator = (BST<T>&& src) noexcept
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete(root_);

                    root_ = nullptr;
                    nodeCount_ = 0ull;
                }

                root_ = src.root_;
                nodeCount_ = src.nodeCount_;

                src.root_ = nullptr;
                src.nodeCount_ = 0ull;
            }

            return *this;
        }


    public:
        int64_t GetTotalNodeCount() const
        {
            return nodeCount_;
        }

        bool Contains(T item)       const
        {
			return Find(root_, item) == nullptr
				? false
				: true
				;
        }

        void ListPreorder()         const
        {
            ListPreorder(root_);
            std::cout << '\n';
        }
        void ListPreorderReverse()  const
        {
            ListPreorderReverse(root_);
            std::cout << '\n';
        }
        void ListInorder()          const
        {
            ListInorder(root_);
            std::cout << '\n';
        }
        void ListInorderReverse()   const
        {
            ListInorderReverse(root_);
            std::cout << '\n';
        }
        void ListPostorder()        const
        {
            ListPostorder(root_);
            std::cout << '\n';
        }
        void ListPostorderReverse() const
        {
            ListPostorderReverse(root_);
            std::cout << '\n';
        }
        void ListLeaves()           const
        {
            ListLeaves(root_);
            std::cout << '\n';
        }
        void ListLeavesReverse()    const
        {
            ListLeavesReverse(root_);
            std::cout << '\n';
        }
        void ListLevelorder()       const
        {
            const int64_t height = GetDepth(root_, 0i64);

            for (int64_t i = 1; i <= height; i++)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        virtual void Insert(T new_item)
        {
            BST<T>::Node* new_root = Insert(nullptr, root_, new_item);

            if (root_ == nullptr)
            {
                root_ = new_root;
            }

            nodeCount_++;
        }
		virtual void Delete(T old_item)
		{
			// AVL and IPR should implement their own!!!!!!!
			BST<T>::Node* node = Find(root_, old_item);

			if (node != nullptr)
			{
				if (node->right != nullptr)
				{
					BST<T>::Node* leftmost = GetMin(node->right);

					if (leftmost != nullptr)
					{
						leftmost->left = node->left;
					}
					else
					{
						node->right->left = node->left;
					}
					
					if (node->parent != nullptr)
					{
						node->parent->right = node->right;
					}
					else
					{
						root_ = node->right;
					}
				}
				else
				{
					if (node->parent != nullptr)
					{
						node->parent->right = node->left;
					}
					else
					{
						root_ = node->left;
					}
				}

				delete node;
			}
		}
        void Mirror()
        {
            Mirror(root_);
        }


    protected:
        struct Node
        {
            Node* left   = nullptr;
            Node* right  = nullptr;
            Node* parent = nullptr;

            T item;

            Node(T new_item, Node* new_parent)
                :
                item(new_item),
                parent(new_parent)
            {

            }
        };


    protected:
        BST<T>::Node* Insert(BST<T>::Node* __restrict parent, BST<T>::Node* __restrict node, T new_item)
        {
            if (node == nullptr)
            {
                return new BST<T>::Node(new_item, parent);
            }

            if (new_item < node->item)
            {
                node->left = Insert(node, node->left, new_item);
            }
            else if (new_item > node->item)
            {
                node->right = Insert(node, node->right, new_item);
            }

            return node;
        }
        BST<T>::Node* Cloner(BST<T>::Node* node) const
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            BST<T>::Node* new_node = new BST<T>::Node(node->item, node->parent);

            new_node->left  = Cloner(node->left);
            new_node->right = Cloner(node->right);

            return new_node;
        }
        BST<T>::Node* Find(BST<T>::Node* node, T item) const
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->item == item)
            {
                return node;
            }

            BST<T>::Node* left_address = Find(node->left, item);

            if (left_address != nullptr)
            {
                return left_address;
            }

            BST<T>::Node* right_address = Find(node->right, item);

            if (right_address != nullptr)
            {
                return right_address;
            }
        }
		BST<T>::Node* GetMin(BST<T>::Node* node)
		{
			if (node == nullptr)
			{
				return nullptr;
			}

			while (node->left != nullptr)
			{
				node = node->left;
			}

			return node;
		}
		BST<T>::Node* GetMax(BST<T>::Node* node)
		{
			if (node == nullptr)
			{
				return nullptr;
			}

			while (node->right != nullptr)
			{
				node = node->right;
			}

			return node;
		}

        int64_t GetDepth(BST<T>::Node* node, int64_t depth) const
        {
            if (node == nullptr)
            {
                return depth;
            }

            const int64_t  left_val = GetDepth(node->left, depth + 1i64);
            const int64_t right_val = GetDepth(node->right, depth + 1i64);

            return std::max(left_val, right_val);
        }
        int64_t GetDepthLeft(BST<T>::Node* node, int64_t depth) const
        {
            return node ? GetDepthLeft(node->left, depth + 1i64) : depth;
        }
        int64_t GetDepthRight(BST<T>::Node* node, int64_t depth) const
        {
            return node ? GetDepthLeft(node->right, depth + 1i64) : depth;
        }
        int64_t GetNodeCount(BST<T>::Node* node) const
        {
            if (node == nullptr)
            {
                return 0i64;
            }

            const int64_t  left_val = GetNodeCount(node->left);
            const int64_t right_val = GetNodeCount(node->right);

            return 1i64 + left_val + right_val;
        }
        
        void Mirror(BST<T>::Node* node)
        {
            if (node != nullptr)
            {
                std::swap(node->left, node->right);

                Mirror(node->left);
                Mirror(node->right);
            }
        }

        void ListPreorder         (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorder(node->left);
                ListPreorder(node->right);
            }
        }
        void ListPreorderReverse  (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorderReverse(node->right);
                ListPreorderReverse(node->left);
            }
        }
        void ListInorder          (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                ListInorder(node->left);
                std::cout << node->item << ' ';
                ListInorder(node->right);
            }
        }
        void ListInorderReverse   (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                ListInorderReverse(node->right);
                std::cout << node->item << ' ';
                ListInorderReverse(node->left);
            }
        }
        void ListPostorder        (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                ListPostorder(node->left);
                ListPostorder(node->right);
                std::cout << node->item << ' ';
            }
        }
        void ListPostorderReverse (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                ListPostorderReverse(node->right);
                ListPostorderReverse(node->left);
                std::cout << node->item << ' ';
            }
        }
        void ListLeaves           (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    std::cout << node->item << ' ';
                    return;
                }

                ListLeaves(root_->left);
                ListLeaves(root_->right);
            }
        }
        void ListLeavesReverse    (const BST<T>::Node* node) const
        {
            if (node != nullptr)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    std::cout << node->item << ' ';
                    return;
                }

                ListLeavesReverse(root_->right);
                ListLeavesReverse(root_->left);
            }
        }
        void ListLevelorder       (const BST<T>::Node* node, int64_t level) const
        {
            if (node != nullptr)
            {
                if (level == 1)
                {
                    std::cout << node->item << ' ';
                }
                else if (level > 1)
                {
                    ListLevelorder(node->left,  level - 1);
                    ListLevelorder(node->right, level - 1);
                }
            }
            else if (level == 1)
            {
                std::cout << "x ";
            }
        }


    protected:
        Node* root_ = nullptr;

        size_t nodeCount_ = 0ui64;


    private:
        void Delete(BST<T>::Node* node) noexcept
        {
            if (node != nullptr)
            {
                Delete(node->left);
                Delete(node->right);

                delete node;
            }
        }
    };
}