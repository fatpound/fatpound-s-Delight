#pragma once

#include "fatpound.hpp"

namespace fatpound
{
#define ISPOWOF2(n) ( ! ((n) & ((n) - 1)))

    namespace tree
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
                BST<T>::node* parent = nullptr;
                BST<T>::node* left   = nullptr;
                BST<T>::node* right  = nullptr;

                T item;

                node(T& new_item, BST<T>::node* parent);
            };

            /********************************/
            /*           Protected          */
            /*           Variables          */
            /********************************/

            BST<T>::node* root       = nullptr;
            BST<T>::node* last_added = nullptr;

            std::int64_t node_count = 0;

            /********************************/
            /*           Protected          */
            /*           Functions          */
            /********************************/

            BST<T>::node* add_private(BST<T>::node* parent, BST<T>::node* node, T& new_item);
            BST<T>::node* find_private(BST<T>::node* root, T item) const;

            std::int64_t get_depth_private(BST<T>::node* node, std::int64_t depth) const;
            std::int64_t get_count_private(BST<T>::node* node) const;
            std::int64_t get_total_node_count_private() const;

            void mirror_private(BST<T>::node* node);

            void list_preorder_private(BST<T>::node* node)          const;
            void list_preorder_reverse_private(BST<T>::node* node)  const;
            void list_inorder_private(BST<T>::node* node)           const;
            void list_inorder_reverse_private(BST<T>::node* node)   const;
            void list_postorder_private(BST<T>::node* node)         const;
            void list_postorder_reverse_private(BST<T>::node* node) const;
            void list_leaves_private(BST<T>::node* node)            const;
            void list_leaves_reverse_private(BST<T>::node* node)    const;


        public:
            /********************************/
            /*            Public            */
            /*           Functions          */
            /********************************/

            ~BST();

            void add(T new_item);
            void mirror();
            void swap_left_right();

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
        template <typename T> typename BST<T>::node* BST<T>::add_private(BST<T>::node* parent, BST<T>::node* node, T& new_item)
        {
            if (node == nullptr)
            {
                this->last_added = new BST<T>::node(new_item, parent);
                return this->last_added;
            }

            if (new_item < node->item)
                node->left  = this->add_private(node, node->left,  new_item);
            else if (new_item > node->item)
                node->right = this->add_private(node, node->right, new_item);

            return node;
        }
        template <typename T> typename BST<T>::node* BST<T>::find_private(BST<T>::node* root, T item) const
        {
            if (root == nullptr)
                return nullptr;

            if (root->item == item)
                return root;

            BST<T>::node* left_address = find_private(root->left, item);

            if (left_address != nullptr)
                return left_address;

            BST<T>::node* right_address = find_private(root->right, item);

            if (right_address != nullptr)
                return right_address;
        }
        //
        // 
        //   int
        //
        //
        /**/
        // 
        //   std::int64_t ... const
        //
        template <typename T> std::int64_t BST<T>::get_depth_private(BST<T>::node* node, std::int64_t depth) const
        {
            if (node == nullptr)
                return depth;

            const std::int64_t  left_val = this->get_depth_private(node->left,  depth + 1);
            const std::int64_t right_val = this->get_depth_private(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        template <typename T> std::int64_t BST<T>::get_count_private(BST<T>::node* node) const
        {
            if (node == nullptr)
                return 0;

            const std::int64_t  left_val = this->get_count_private(node->left);
            const std::int64_t right_val = this->get_count_private(node->right);

            return 1 + left_val + right_val;
        }
        template <typename T> std::int64_t BST<T>::get_total_node_count_private() const
        {
            return this->node_count;
        }
        //
        // 
        //   void
        //
        //
        template <typename T> void BST<T>::mirror_private(BST<T>::node* node)
        {
            if (node == nullptr)
                return;

            std::swap(node->left, node->right);

            this->mirror_private(node->left);
            this->mirror_private(node->right);
        }
        //
        //   void ... const
        //
        template <typename T> void BST<T>::list_preorder_private          (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            std::cout << node->item << ' ';
            this->list_preorder_private(node->left);
            this->list_preorder_private(node->right);
        }
        template <typename T> void BST<T>::list_preorder_reverse_private  (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            std::cout << node->item << ' ';
            this->list_preorder_reverse_private(node->right);
            this->list_preorder_reverse_private(node->left);
        }
        template <typename T> void BST<T>::list_inorder_private           (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            this->list_inorder_private(node->left);
            std::cout << node->item << ' ';
            this->list_inorder_private(node->right);
        }
        template <typename T> void BST<T>::list_inorder_reverse_private   (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            this->list_inorder_reverse_private(node->right);
            std::cout << node->item << ' ';
            this->list_inorder_reverse_private(node->left);
        }
        template <typename T> void BST<T>::list_postorder_private         (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            this->list_postorder_private(node->left);
            this->list_postorder_private(node->right);
            std::cout << node->item << ' ';
        }
        template <typename T> void BST<T>::list_postorder_reverse_private (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            this->list_postorder_reverse_private(node->right);
            this->list_postorder_reverse_private(node->left);
            std::cout << node->item << ' ';
        }
        template <typename T> void BST<T>::list_leaves_private            (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << node->item << ' ';
                return;
            }

            list_leaves_private(root->left);
            list_leaves_private(root->right);
        }
        template <typename T> void BST<T>::list_leaves_reverse_private    (BST<T>::node* node) const
        {
            if (node == nullptr)
                return;

            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << node->item << ' ';
                return;
            }

            list_leaves_reverse_private(root->right);
            list_leaves_reverse_private(root->left);
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
        template <typename T> void BST<T>::add(T new_item)
        {
            BST<T>::node* new_root = this->add_private(nullptr, this->root, new_item);

            if (this->root == nullptr)
                this->root = new_root;
            
            this->node_count++;
        }
        template <typename T> void BST<T>::mirror()
        {
            this->mirror_private(this->root);
        }
        template <typename T> void BST<T>::swap_left_right()
        {
            std::swap(this->root->left, this->root->right);
        }
        //
        //   void ... const
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
            this->list_preorder_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_preorder_reverse()  const
        {
            this->list_preorder_reverse_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_inorder()           const
        {
            this->list_inorder_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_inorder_reverse()   const
        {
            this->list_inorder_reverse_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_postorder()         const
        {
            this->list_postorder_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_postorder_reverse() const
        {
            this->list_postorder_reverse_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_leaves()            const
        {
            this->list_leaves_private(this->root);
            std::cout << '\n';
        }
        template <typename T> void BST<T>::list_leaves_reverse()    const
        {
            this->list_leaves_reverse_private(this->root);
            std::cout << '\n';
        }
    }
}