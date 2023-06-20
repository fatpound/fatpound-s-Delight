#pragma once

#include "fatpound.hpp"

#define ISPOWOF2(n) ( ! ((n) & ((n) - 1)))

namespace fatpound::tree
{
    template <typename T>
    class BST
    {
    private:


    protected:
        /********************************/
        /*           Protected          */
        /*            Classes           */
        /********************************/

        class node
        {
        private:


        protected:


        public:
            BST<T>::node* left   = nullptr;
            BST<T>::node* right  = nullptr;
            BST<T>::node* parent = nullptr;

            T item;

            node(T& new_item, BST<T>::node* parent);
        };

        /********************************/
        /*           Protected          */
        /*           Variables          */
        /********************************/

        BST<T>::node* root          = nullptr;
        BST<T>::node* last_inserted = nullptr;

        std::int64_t node_count = 0;

        /********************************/
        /*           Protected          */
        /*           Functions          */
        /********************************/

        BST<T>::node* insert_protected(BST<T>::node* parent, BST<T>::node* node, T& new_item);
        BST<T>::node* find_protected(BST<T>::node* root, T item) const;

        std::int64_t get_depth_protected(BST<T>::node* node, std::int64_t depth) const;
        std::int64_t get_count_protected(BST<T>::node* node) const;
        std::int64_t get_total_node_count_protected() const;

        void mirror_protected(BST<T>::node* node);

        void list_preorder_protected          (BST<T>::node* node) const;
        void list_preorder_reverse_protected  (BST<T>::node* node) const;
        void list_inorder_protected           (BST<T>::node* node) const;
        void list_inorder_reverse_protected   (BST<T>::node* node) const;
        void list_postorder_protected         (BST<T>::node* node) const;
        void list_postorder_reverse_protected (BST<T>::node* node) const;
        void list_leaves_protected            (BST<T>::node* node) const;
        void list_leaves_reverse_protected    (BST<T>::node* node) const;


    public:
        /********************************/
        /*            Public            */
        /*           Functions          */
        /********************************/

        ~BST();

        void insert(T new_item);
        void mirror();

        void list_levelorder()        const;
        void list_preorder()          const;
        void list_preorder_reverse()  const;
        void list_inorder()           const;
        void list_inorder_reverse()   const;
        void list_postorder()         const;
        void list_postorder_reverse() const;
        void list_leaves()            const;
        void list_leaves_reverse()    const;
    };

    /********************************/
    /*      Protected Functions     */
    /********************************/
    //
    //
    //   BST<T>::node*
    //
    //
    template <typename T> typename BST<T>::node* BST<T>::insert_protected(BST<T>::node* parent, BST<T>::node* node, T& new_item)
    {
        if (node == nullptr)
        {
            this->last_inserted = new BST<T>::node(new_item, parent);
            return this->last_inserted;
        }

        if (new_item < node->item)
            node->left  = this->insert_protected(node, node->left,  new_item);
        else if (new_item > node->item)
            node->right = this->insert_protected(node, node->right, new_item);

        return node;
    }
    //
    //   BST<T>::node* . . . const
    //
    template <typename T> typename BST<T>::node* BST<T>::find_protected(BST<T>::node* root, T item) const
    {
        if (root == nullptr)
            return nullptr;

        if (root->item == item)
            return root;

        BST<T>::node* left_insertress = find_protected(root->left, item);

        if (left_insertress != nullptr)
            return left_insertress;

        BST<T>::node* right_insertress = find_protected(root->right, item);

        if (right_insertress != nullptr)
            return right_insertress;
    }
    //
    // 
    //   std::int64_t
    //
    //
    /**/
    // 
    //   std::int64_t . . . const
    //
    template <typename T> std::int64_t BST<T>::get_depth_protected(BST<T>::node* node, std::int64_t depth) const
    {
        if (node == nullptr)
            return depth;

        const std::int64_t  left_val = this->get_depth_protected(node->left,  depth + 1);
        const std::int64_t right_val = this->get_depth_protected(node->right, depth + 1);

        return std::max(left_val, right_val);
    }
    template <typename T> std::int64_t BST<T>::get_count_protected(BST<T>::node* node) const
    {
        if (node == nullptr)
            return 0;

        const std::int64_t  left_val = this->get_count_protected(node->left);
        const std::int64_t right_val = this->get_count_protected(node->right);

        return 1 + left_val + right_val;
    }
    template <typename T> std::int64_t BST<T>::get_total_node_count_protected() const
    {
        return this->node_count;
    }
    //
    // 
    //   void
    //
    //
    template <typename T> void BST<T>::mirror_protected(BST<T>::node* node)
    {
        if (node == nullptr)
            return;

        std::swap(node->left, node->right);

        this->mirror_protected(node->left);
        this->mirror_protected(node->right);
    }
    //
    //   void . . . const
    //
    template <typename T> void BST<T>::list_preorder_protected          (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->item << ' ';
        this->list_preorder_protected(node->left);
        this->list_preorder_protected(node->right);
    }
    template <typename T> void BST<T>::list_preorder_reverse_protected  (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->item << ' ';
        this->list_preorder_reverse_protected(node->right);
        this->list_preorder_reverse_protected(node->left);
    }
    template <typename T> void BST<T>::list_inorder_protected           (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        this->list_inorder_protected(node->left);
        std::cout << node->item << ' ';
        this->list_inorder_protected(node->right);
    }
    template <typename T> void BST<T>::list_inorder_reverse_protected   (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        this->list_inorder_reverse_protected(node->right);
        std::cout << node->item << ' ';
        this->list_inorder_reverse_protected(node->left);
    }
    template <typename T> void BST<T>::list_postorder_protected         (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        this->list_postorder_protected(node->left);
        this->list_postorder_protected(node->right);
        std::cout << node->item << ' ';
    }
    template <typename T> void BST<T>::list_postorder_reverse_protected (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        this->list_postorder_reverse_protected(node->right);
        this->list_postorder_reverse_protected(node->left);
        std::cout << node->item << ' ';
    }
    template <typename T> void BST<T>::list_leaves_protected            (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            std::cout << node->item << ' ';
            return;
        }

        list_leaves_protected(root->left);
        list_leaves_protected(root->right);
    }
    template <typename T> void BST<T>::list_leaves_reverse_protected    (BST<T>::node* node) const
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            std::cout << node->item << ' ';
            return;
        }

        list_leaves_reverse_protected(root->right);
        list_leaves_reverse_protected(root->left);
    }
    
    /********************************/
    /*       Public Functions       */
    /********************************/
    //
    //
    //   constructor
    //   destructors
    //
    //
    template <typename T> BST<T>::node::node(T& new_item, BST<T>::node* new_parent)
    {
        this->item = new_item;
        this->parent = new_parent;
    }
    template <typename T> BST<T>::~BST()
    {

    }
    //
    // 
    //   void
    //
    //
    template <typename T> void BST<T>::insert(T new_item)
    {
        BST<T>::node* new_root = this->insert_protected(nullptr, this->root, new_item);

        if (this->root == nullptr)
            this->root = new_root;
        
        this->node_count++;
    }
    template <typename T> void BST<T>::mirror()
    {
        this->mirror_protected(this->root);
    }
    //
    //   void . . . const
    //
    template <typename T> void BST<T>::list_levelorder()        const
    {
        std::queue<BST<T>::node*> Q;

        if (this->root != nullptr)
            Q.push(this->root);

        std::int64_t level = 1;

        for (std::int64_t i = 1; Q.size() > 0; i++)
        {
            if (ISPOWOF2(i))
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

            if (ISPOWOF2(i + 1))
                std::cout << '\n';
            else if (Q.size() != 0)
                std::cout << ", ";
            // else break;
        }

        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_preorder()          const
    {
        this->list_preorder_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_preorder_reverse()  const
    {
        this->list_preorder_reverse_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_inorder()           const
    {
        this->list_inorder_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_inorder_reverse()   const
    {
        this->list_inorder_reverse_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_postorder()         const
    {
        this->list_postorder_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_postorder_reverse() const
    {
        this->list_postorder_reverse_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_leaves()            const
    {
        this->list_leaves_protected(this->root);
        std::cout << '\n';
    }
    template <typename T> void BST<T>::list_leaves_reverse()    const
    {
        this->list_leaves_reverse_protected(this->root);
        std::cout << '\n';
    }
}