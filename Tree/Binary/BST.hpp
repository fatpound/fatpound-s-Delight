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
        BST(const BST& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.Clone(src.root_);
                node_count_ = src.node_count_;
            }
        }
        BST& operator = (const BST& src) noexcept
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete(root_);

                    root_ = nullptr;
                    node_count_ = 0ull;
                }

                root_ = src.Clone(src.root_);
                node_count_ = src.node_count_;
            }

            return *this;
        }
        BST(BST&& src) noexcept
        {
            if (src.root_ != nullptr)
            {
                root_ = src.root_;
                node_count_ = src.node_count_;

                src.root_ = nullptr;
                src.node_count_ = 0ull;
            }
        }
        BST& operator = (BST&& src) noexcept
        {
            if (this != std::addressof(src) && src.root_ != nullptr)
            {
                if (root_ != nullptr)
                {
                    Delete(root_);

                    root_ = nullptr;
                    node_count_ = 0ull;
                }

                root_ = src.root_;
                node_count_ = src.node_count_;

                src.root_ = nullptr;
                src.node_count_ = 0ull;
            }

            return *this;
        }
        ~BST() noexcept
        {
            DeleteTree(root_);
            root_ = nullptr;
            node_count_ = 0u;
        }


    public:
        virtual std::int64_t GetTotalNodeCount() const final
        {
            return node_count_;
        }

        virtual bool Contains(T item)       const final
        {
            return Find(root_, item) == nullptr
                ? false
                : true
                ;
        }

        virtual void ListPreorder()         const final
        {
            ListPreorder(root_);
            std::cout << '\n';
        }
        virtual void ListPreorderReverse()  const final
        {
            ListPreorderReverse(root_);
            std::cout << '\n';
        }
        virtual void ListInorder()          const final
        {
            ListInorder(root_);
            std::cout << '\n';
        }
        virtual void ListInorderReverse()   const final
        {
            ListInorderReverse(root_);
            std::cout << '\n';
        }
        virtual void ListPostorder()        const final
        {
            ListPostorder(root_);
            std::cout << '\n';
        }
        virtual void ListPostorderReverse() const final
        {
            ListPostorderReverse(root_);
            std::cout << '\n';
        }
        virtual void ListLeaves()           const final
        {
            ListLeaves(root_);
            std::cout << '\n';
        }
        virtual void ListLeavesReverse()    const final
        {
            ListLeavesReverse(root_);
            std::cout << '\n';
        }
        virtual void ListLevelorder()       const final
        {
            const std::int64_t height = GetDepth(root_, 0);

            for (std::int64_t i = 1; i <= height; i++)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        virtual void Insert(T new_item) final
        {
            BST<T>::Node_* new_root = Insert(nullptr, root_, new_item);

            [[unlikely]] if (root_ == nullptr)
            {
                root_ = new_root;
            }

            ++node_count_;
        }
        virtual void Delete(T old_item) final
        {
            BST<T>::Node_* node = Find(root_, old_item);

            if (node != nullptr)
            {
                static_cast<void>(Delete(node));
            }
        }
        virtual void Mirror() final
        {
            Mirror(root_);
        }


    protected:
        struct Node_
        {
            Node_* left   = nullptr;
            Node_* right  = nullptr;
            Node_* parent = nullptr;

            T item;

            Node_(T new_item, Node_* new_parent)
                :
                item(new_item),
                parent(new_parent)
            {

            }
        };


    protected:
        virtual BST<T>::Node_* Insert(BST<T>::Node_* __restrict parent, BST<T>::Node_* __restrict node, T new_item) final
        {
            if (node == nullptr)
            {
                return new BST<T>::Node_(new_item, parent);
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
        virtual BST<T>::Node_* Clone(BST<T>::Node_* node) const final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            BST<T>::Node_* new_node = new BST<T>::Node_(node->item, node->parent);

            new_node->left  = Clone(node->left);
            new_node->right = Clone(node->right);

            return new_node;
        }
        virtual BST<T>::Node_* Find(BST<T>::Node_* node, T item) const final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->item == item)
            {
                return node;
            }

            BST<T>::Node_* left_address = Find(node->left, item);

            if (left_address != nullptr)
            {
                return left_address;
            }

            BST<T>::Node_* right_address = Find(node->right, item);

            if (right_address != nullptr)
            {
                return right_address;
            }
        }
        virtual BST<T>::Node_* Delete(BST<T>::Node_* node) final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            BST<T>::Node_* latest = nullptr;

            if (node->parent != nullptr)
            {
                if (node->right != nullptr)
                {
                    BST<T>::Node_* leftmost = GetMin(node->right);

                    if (leftmost != nullptr)
                    {
                        leftmost->left = node->left;

                        if (node->left != nullptr)
                        {
                            node->left->parent = leftmost;
                        }
                    }
                    else
                    {
                        node->right->left = node->left;

                        if (node->left != nullptr)
                        {
                            node->left->parent = node->right;
                        }
                    }

                    node->right->parent = node->parent;
                    latest = node->right;
                }
                else
                {
                    if (node->left != nullptr)
                    {
                        node->left->parent = node->parent;
                        latest = node->left;
                    }
                    else
                    {
                        latest = node->parent;
                    }
                }

                if (node->parent->item < node->item)
                {
                    node->parent->right = node->right;
                }
                else
                {
                    node->parent->left = node->right;
                }
            }
            else
            {
                root_ = node->right;
            }

            delete node;

            return latest;
        }

        virtual BST<T>::Node_* GetMin(BST<T>::Node_* node) final
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
        virtual BST<T>::Node_* GetMax(BST<T>::Node_* node) final
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
        virtual BST<T>::Node_* GetInorderSuccessor(BST<T>::Node_* node) final
        {
            if (node->right != nullptr)
            {
                return GetMin(node->right);
            }

            BST<T>::Node_* prnt = node->parent;

            while (prnt != nullptr && prnt->right == node)
            {
                node = prnt;
                prnt = prnt->parent;
            }

            return prnt;
        }

        virtual std::int64_t GetDepth(BST<T>::Node_* node, std::int64_t depth) const final
        {
            if (node == nullptr)
            {
                return depth;
            }

            const std::int64_t  left_val = GetDepth(node->left, depth + 1);
            const std::int64_t right_val = GetDepth(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        virtual std::int64_t GetDepthLeft(BST<T>::Node_* node, std::int64_t depth) const final
        {
            return node ? GetDepthLeft(node->left, depth + 1) : depth;
        }
        virtual std::int64_t GetDepthRight(BST<T>::Node_* node, std::int64_t depth) const final
        {
            return node ? GetDepthLeft(node->right, depth + 1) : depth;
        }
        virtual std::int64_t GetNodeCount(BST<T>::Node_* node) const final
        {
            if (node == nullptr)
            {
                return 0;
            }

            const std::int64_t  left_val = GetNodeCount(node->left);
            const std::int64_t right_val = GetNodeCount(node->right);

            return 1 + left_val + right_val;
        }
        
        virtual void Mirror(BST<T>::Node_* node) final
        {
            if (node != nullptr)
            {
                std::swap(node->left, node->right);

                Mirror(node->left);
                Mirror(node->right);
            }
        }

        virtual void ListPreorder         (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorder(node->left);
                ListPreorder(node->right);
            }
        }
        virtual void ListPreorderReverse  (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                std::cout << node->item << ' ';
                ListPreorderReverse(node->right);
                ListPreorderReverse(node->left);
            }
        }
        virtual void ListInorder          (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                ListInorder(node->left);
                std::cout << node->item << ' ';
                ListInorder(node->right);
            }
        }
        virtual void ListInorderReverse   (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                ListInorderReverse(node->right);
                std::cout << node->item << ' ';
                ListInorderReverse(node->left);
            }
        }
        virtual void ListPostorder        (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                ListPostorder(node->left);
                ListPostorder(node->right);
                std::cout << node->item << ' ';
            }
        }
        virtual void ListPostorderReverse (const BST<T>::Node_* node) const final
        {
            if (node != nullptr)
            {
                ListPostorderReverse(node->right);
                ListPostorderReverse(node->left);
                std::cout << node->item << ' ';
            }
        }
        virtual void ListLeaves           (const BST<T>::Node_* node) const final
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
        virtual void ListLeavesReverse    (const BST<T>::Node_* node) const final
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
        virtual void ListLevelorder       (const BST<T>::Node_* node, std::int64_t level) const final
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
        Node_* root_ = nullptr;

        std::size_t node_count_ = 0u;


    private:
        virtual void DeleteTree(BST<T>::Node_* root) final noexcept
        {
            if (root != nullptr)
            {
                DeleteTree(root->left);
                DeleteTree(root->right);

                delete root;
            }
        }
    };
}