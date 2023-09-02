#pragma once

#include "fatpound.hpp"

namespace fatpound::tree
{
    template <typename T>
    class BST
    {
    protected:
        struct node
        {
            BST<T>::node* left   = nullptr;
            BST<T>::node* right  = nullptr;
            BST<T>::node* parent = nullptr;

            T item;

            node(T& new_item, BST<T>::node* parent);
        };

        BST<T>::node* root = nullptr;
        BST<T>::node* lastInserted = nullptr;

        std::size_t nodeCount = 0;


        BST<T>::node* Insert_Protected(BST<T>::node* parent, BST<T>::node* node, T& new_item);
        BST<T>::node* Find_Protected(BST<T>::node* root, T item) const;

        std::int64_t GetDepth_Protected(BST<T>::node* node, std::int64_t depth) const;
        std::int64_t GetNodeCount_Protected(BST<T>::node* node) const;
        

        void Mirror_Protected               (BST<T>::node* node);
        void ListPreorder_Protected         (BST<T>::node* node) const;
        void ListPreorderReverse_Protected  (BST<T>::node* node) const;
        void ListInorder_Protected          (BST<T>::node* node) const;
        void ListInorderReverse_Protected   (BST<T>::node* node) const;
        void ListPostorder_Protected        (BST<T>::node* node) const;
        void ListPostorderReverse_Protected (BST<T>::node* node) const;
        void ListLeaves_Protected           (BST<T>::node* node) const;
        void ListLeavesReverse_Protected    (BST<T>::node* node) const;


    private:
        void Erase(BST<T>::node* node);


    public:
        BST() = default;
        ~BST();
        BST(const BST<T>& src) = delete;
        BST& operator = (const BST<T>& src) = delete;

        std::int64_t GetTotalNodeCount() const;

        void Insert(T new_item);
        void Mirror();
        void ListLevelorder()       const;
        void ListPreorder()         const;
        void ListPreorderReverse()  const;
        void ListInorder()          const;
        void ListInorderReverse()   const;
        void ListPostorder()        const;
        void ListPostorderReverse() const;
        void ListLeaves()           const;
        void ListLeavesReverse()    const;
    };


    template <typename T> void BST<T>::Erase(BST<T>::node* node)
    {
        if (node == nullptr)
            return;

        Erase(node->left);
        Erase(node->right);

        delete node;
    }

    template <typename T> typename BST<T>::node* BST<T>::Insert_Protected(BST<T>::node* parent, BST<T>::node* node, T& new_item)
    {
        if (node == nullptr)
        {
            lastInserted = new BST<T>::node(new_item, parent);
            return lastInserted;
        }

        if (new_item < node->item)
            node->left  = Insert_Protected(node, node->left,  new_item);
        else if (new_item > node->item)
            node->right = Insert_Protected(node, node->right, new_item);

        return node;
    }
    template <typename T> typename BST<T>::node* BST<T>::Find_Protected(BST<T>::node* root, T item) const
    {
        if (root == nullptr)
            return nullptr;

        if (root->item == item)
            return root;

        BST<T>::node* left_address = Find_Protected(root->left, item);

        if (left_address != nullptr)
            return left_address;

        BST<T>::node* right_address = Find_Protected(root->right, item);

        if (right_address != nullptr)
            return right_address;
    }

    template <typename T> std::int64_t BST<T>::GetDepth_Protected(BST<T>::node* node, std::int64_t depth) const
    {
        if (node == nullptr)
            return depth;

        const std::int64_t  left_val = GetDepth_Protected(node->left,  depth + 1);
        const std::int64_t right_val = GetDepth_Protected(node->right, depth + 1);

        return std::max(left_val, right_val);
    }
    template <typename T> std::int64_t BST<T>::GetNodeCount_Protected(BST<T>::node* node) const
    {
        if (node == nullptr)
            return 0;

        const std::int64_t  left_val = GetNodeCount_Protected(node->left);
        const std::int64_t right_val = GetNodeCount_Protected(node->right);

        return 1 + left_val + right_val;
    }
    template <typename T> std::int64_t BST<T>::GetTotalNodeCount() const
    {
        return nodeCount;
    }

    template <typename T> void BST<T>::Mirror_Protected(BST<T>::node* node)
    {
        if (node == nullptr)
            return;

        std::swap(node->left, node->right);

        Mirror_Protected(node->left);
        Mirror_Protected(node->right);
    }
    template <typename T> void BST<T>::ListPreorder_Protected         (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->item << ' ';
        ListPreorder_Protected(node->left);
        ListPreorder_Protected(node->right);
    }
    template <typename T> void BST<T>::ListPreorderReverse_Protected  (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->item << ' ';
        ListPreorderReverse_Protected(node->right);
        ListPreorderReverse_Protected(node->left);
    }
    template <typename T> void BST<T>::ListInorder_Protected          (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        ListInorder_Protected(node->left);
        std::cout << node->item << ' ';
        ListInorder_Protected(node->right);
    }
    template <typename T> void BST<T>::ListInorderReverse_Protected   (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        ListInorderReverse_Protected(node->right);
        std::cout << node->item << ' ';
        ListInorderReverse_Protected(node->left);
    }
    template <typename T> void BST<T>::ListPostorder_Protected        (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        ListPostorder_Protected(node->left);
        ListPostorder_Protected(node->right);
        std::cout << node->item << ' ';
    }
    template <typename T> void BST<T>::ListPostorderReverse_Protected (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        ListPostorderReverse_Protected(node->right);
        ListPostorderReverse_Protected(node->left);
        std::cout << node->item << ' ';
    }
    template <typename T> void BST<T>::ListLeaves_Protected           (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            std::cout << node->item << ' ';
            return;
        }

        ListLeaves_Protected(root->left);
        ListLeaves_Protected(root->right);
    }
    template <typename T> void BST<T>::ListLeavesReverse_Protected    (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            std::cout << node->item << ' ';
            return;
        }

        ListLeavesReverse_Protected(root->right);
        ListLeavesReverse_Protected(root->left);
    }
    
    template <typename T> BST<T>::node::node(T& new_item, BST<T>::node* new_parent)
    {
        item = new_item;
        parent = new_parent;
    }
    template <typename T> BST<T>::~BST()
    {
        Erase(root);
    }

    template <typename T> void BST<T>::Insert(T new_item)
    {
        BST<T>::node* new_root = Insert_Protected(nullptr, root, new_item);

        if (root == nullptr)
            root = new_root;
        
        nodeCount++;
    }
    template <typename T> void BST<T>::Mirror()
    {
        Mirror_Protected(root);
    }
    template <typename T> void BST<T>::ListLevelorder()       const
    {
        std::queue<BST<T>::node*> Q;

        if (root != nullptr)
            Q.push(root);

        std::int64_t level = 1;

        for (std::int64_t i = 1; Q.size() > 0; i++)
        {
            if (fatpound::math::IsPowerOf2(i))
            {
                std::cout << "Seviye " << level << " : ";
                level++;
            }

            BST<T>::node* u = Q.front();
            Q.pop();

            if (u != nullptr)
            {
                Q.push(u->left);
                Q.push(u->right);

                std::cout << u->item;
            }
            else
                std::cout << "bos";

            if (fatpound::math::IsPowerOf2(i + 1))
                std::cout << '\n';
            else if (Q.size() != 0)
                std::cout << ", ";
            // else break;
        }

        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListPreorder()         const
    {
        ListPreorder_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListPreorderReverse()  const
    {
        ListPreorderReverse_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListInorder()          const
    {
        ListInorder_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListInorderReverse()   const
    {
        ListInorderReverse_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListPostorder()        const
    {
        ListPostorder_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListPostorderReverse() const
    {
        ListPostorderReverse_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListLeaves()           const
    {
        ListLeaves_Protected(root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::ListLeavesReverse()    const
    {
        ListLeavesReverse_Protected(root);
        std::cout << '\n';
    }
}