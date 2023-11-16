#pragma once

#include <iostream>

namespace fatpound::tree
{
    template <typename T>
    class BST
    {
    public:
        BST() = default;
        ~BST() noexcept
        {
            Delete(root);
            root = nullptr;
        }
        BST(const BST<T>& src) noexcept
        {
            if (src.root != nullptr)
            {
                root = src.Cloner(src.root);
                nodeCount = src.nodeCount;
            }
        }
        BST(BST<T>&& src) noexcept
        {
            if (src.root != nullptr)
            {
                root = src.root;
                nodeCount = src.nodeCount;

                src.root = nullptr;
                src.nodeCount = 0ull;
            }
        }
        BST& operator = (const BST<T>& src) noexcept
        {
            if (this != std::addressof(src) && src.root != nullptr)
            {
                if (root != nullptr)
                {
                    Delete(root);

                    root = nullptr;
                    // nodeCount = 0ull;
                }

                root = src.Cloner(src.root);
                nodeCount = src.nodeCount;
            }

            return *this;
        }
        BST& operator = (BST<T>&& src) noexcept
        {
            if (this != std::addressof(src) && src.root != nullptr)
            {
                if (root != nullptr)
                {
                    Delete(root);

                    root = nullptr;
                    // nodeCount = 0ull;
                }

                root = src.root;
                nodeCount = src.nodeCount;

                src.root = nullptr;
                src.nodeCount = 0ull;
            }

            return *this;
        }


    public:
        int64_t GetTotalNodeCount() const;

        void ListPreorder()         const
        {
            ListPreorder(root);
            std::cout << '\n';
        }
        void ListPreorderReverse()  const
        {
            ListPreorderReverse(root);
            std::cout << '\n';
        }
        void ListInorder()          const
        {
            ListInorder(root);
            std::cout << '\n';
        }
        void ListInorderReverse()   const
        {
            ListInorderReverse(root);
            std::cout << '\n';
        }
        void ListPostorder()        const
        {
            ListPostorder(root);
            std::cout << '\n';
        }
        void ListPostorderReverse() const
        {
            ListPostorderReverse(root);
            std::cout << '\n';
        }
        void ListLeaves()           const
        {
            ListLeaves(root);
            std::cout << '\n';
        }
        void ListLeavesReverse()    const
        {
            ListLeavesReverse(root);
            std::cout << '\n';
        }
        void ListLevelorder()       const;

        void Mirror()
        {
            Mirror(root);
        }
        void Insert(T new_item)
        {
            BST<T>::node* new_root = Insert(nullptr, root, new_item);

            if (root == nullptr)
            {
                root = new_root;
            }

            nodeCount++;
        }


    protected:
        struct node
        {
            node* left   = nullptr;
            node* right  = nullptr;
            node* parent = nullptr;

            T item;

            node(T new_item, node* new_parent)
            :
            item(new_item),
                parent(new_parent)
            {}
        };


    protected:
        BST<T>::node* Insert(BST<T>::node* __restrict parent, BST<T>::node* __restrict node, T new_item);
        BST<T>::node* Cloner(BST<T>::node* node) const;
        BST<T>::node* Find(BST<T>::node* root, T item) const;

        int64_t GetDepth(BST<T>::node* node, int64_t depth = 0) const;
        int64_t GetDepthLeft(BST<T>::node* node, int64_t depth = 0) const;
        int64_t GetDepthRight(BST<T>::node* node, int64_t depth = 0) const;
        int64_t GetNodeCount(BST<T>::node* node) const;
        
        void Mirror(BST<T>::node* node)
        {
            if (node != nullptr)
            {
                std::swap(node->left, node->right);

                Mirror(node->left);
                Mirror(node->right);
            }
        }

        void ListPreorder         (const BST<T>::node* node) const;
        void ListPreorderReverse  (const BST<T>::node* node) const;
        void ListInorder          (const BST<T>::node* node) const;
        void ListInorderReverse   (const BST<T>::node* node) const;
        void ListPostorder        (const BST<T>::node* node) const;
        void ListPostorderReverse (const BST<T>::node* node) const;
        void ListLeaves           (const BST<T>::node* node) const;
        void ListLeavesReverse    (const BST<T>::node* node) const;
        void ListLevelorder       (const BST<T>::node* node, int64_t level) const;


    protected:
        BST<T>::node* root = nullptr;

        size_t nodeCount = 0;


    private:
        void Delete(BST<T>::node* node) noexcept
        {
            if (node != nullptr)
            {
                Delete(node->left);
                Delete(node->right);

                delete node;
            }
        }
    };


    template <typename T> typename BST<T>::node* BST<T>::Insert(BST<T>::node* __restrict parent, BST<T>::node* __restrict node, T new_item)
    {
        if (node == nullptr)
        {
            return new BST<T>::node(new_item, parent);
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
    template <typename T> typename BST<T>::node* BST<T>::Cloner(BST<T>::node* node) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        BST<T>::node* new_node = new BST<T>::node(node->item, node->parent);

        new_node->left = Cloner(node->left);
        new_node->right = Cloner(node->right);

        return new_node;
    }
    template <typename T> typename BST<T>::node* BST<T>::Find(BST<T>::node* root, T item) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root->item == item)
        {
            return root;
        }

        BST<T>::node* left_address = Find(root->left, item);

        if (left_address != nullptr)
        {
            return left_address;
        }

        BST<T>::node* right_address = Find(root->right, item);

        if (right_address != nullptr)
        {
            return right_address;
        }
    }

    template <typename T> int64_t BST<T>::GetDepth(BST<T>::node* node, int64_t depth) const
    {
        if (node == nullptr)
        {
            return depth;
        }

        const int64_t  left_val = GetDepth(node->left,  depth + 1LL);
        const int64_t right_val = GetDepth(node->right, depth + 1LL);
        
        return std::max(left_val, right_val);
    }
    template <typename T> int64_t BST<T>::GetDepthLeft(BST<T>::node* node, int64_t depth) const
    {
        return node ? GetDepthLeft(node->left, depth + 1LL) : depth;
    }
    template <typename T> int64_t BST<T>::GetDepthRight(BST<T>::node* node, int64_t depth) const
    {
        return node ? GetDepthLeft(node->right, depth + 1LL) : depth;
    }
    template <typename T> int64_t BST<T>::GetNodeCount(BST<T>::node* node) const
    {
        if (node == nullptr)
        {
            return 0ll;
        }

        const int64_t  left_val = GetNodeCount(node->left);
        const int64_t right_val = GetNodeCount(node->right);

        return 1LL + left_val + right_val;
    }
    template <typename T> int64_t BST<T>::GetTotalNodeCount() const
    {
        return nodeCount;
    }

    template <typename T> void BST<T>::ListPreorder         (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            std::cout << node->item << ' ';
            ListPreorder(node->left);
            ListPreorder(node->right);
        }
    }
    template <typename T> void BST<T>::ListPreorderReverse  (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            std::cout << node->item << ' ';
            ListPreorderReverse(node->right);
            ListPreorderReverse(node->left);
        }
    }
    template <typename T> void BST<T>::ListInorder          (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            ListInorder(node->left);
            std::cout << node->item << ' ';
            ListInorder(node->right);
        }
    }
    template <typename T> void BST<T>::ListInorderReverse   (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            ListInorderReverse(node->right);
            std::cout << node->item << ' ';
            ListInorderReverse(node->left);
        }
    }
    template <typename T> void BST<T>::ListPostorder        (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            ListPostorder(node->left);
            ListPostorder(node->right);
            std::cout << node->item << ' ';
        }
    }
    template <typename T> void BST<T>::ListPostorderReverse (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            ListPostorderReverse(node->right);
            ListPostorderReverse(node->left);
            std::cout << node->item << ' ';
        }
    }
    template <typename T> void BST<T>::ListLeaves           (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << node->item << ' ';
                return;
            }

            ListLeaves(root->left);
            ListLeaves(root->right);
        }
    }
    template <typename T> void BST<T>::ListLeavesReverse    (const BST<T>::node* node) const
    {
        if (node != nullptr)
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << node->item << ' ';
                return;
            }

            ListLeavesReverse(root->right);
            ListLeavesReverse(root->left);
        }
    }
    template <typename T> void BST<T>::ListLevelorder       (const BST<T>::node* node, int64_t level) const
    {
        if (node != nullptr)
        {
            if (level == 1)
            {
                std::cout << node->item << ' ';
            }
            else if (level > 1)
            {
                ListLevelorder(node->left, level - 1);
                ListLevelorder(node->right, level - 1);
            }
        }
        else if (level == 1)
        {
            std::cout << "x ";
        }
    }

    template <typename T> void BST<T>::ListLevelorder() const
    {
        const int64_t height = GetDepth(root);

        for (int64_t i = 1; i <= height; i++)
        {
            std::cout << "Level " << i << " : ";

            ListLevelorder(root, i);

            std::cout << '\n';
        }

        std::cout << '\n';
    }
}