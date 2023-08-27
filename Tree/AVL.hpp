#pragma once

#include "BST.hpp"

namespace fatpound::tree
{
    template <typename T>
    class AVL : public BST<T>
    {
    private:
        void balance();


    protected:
        void  rotate_left(AVL<T>::node* X, AVL<T>::node* Y);
        void rotate_right(AVL<T>::node* X, AVL<T>::node* Y);


    public:
        void add(T new_item);


    };

    template <typename T> void AVL<T>::balance()
    {
        typename __super::node* last = __super::last_added; // Y
        
        while (last->parent != nullptr) // Going up
        {
            const int  left_val = __super::get_depth_private(last->parent->left,  0);
            const int right_val = __super::get_depth_private(last->parent->right, 0);

            const int balance_factor = right_val - left_val;

            /*
            std::cout << "parent  : " << last->parent->item << '\n';
            std::cout << "node    : " << last->item << '\n';
            std::cout << "left    : " << left_val << '\n';
            std::cout << "rite    : " << right_val << '\n';
            std::cout << "balance : " << balance_factor << "\n\n";
            */

            if (balance_factor >  1 && __super::last_added->item > last->item)
            {
                this->rotate_left(last->parent, last);
            }
            else
            if (balance_factor < -1 && __super::last_added->item < last->item)
            {
                this->rotate_right(last->parent, last);
            }
            else
            if (balance_factor >  1 && __super::last_added->item < last->item)
            {
                this->rotate_right(last, last->left);
                this->rotate_left(last->parent->parent, last->parent);
            }
            else
            if (balance_factor < -1 && __super::last_added->item > last->item)
            {
                this->rotate_left(last, last->right);
                this->rotate_right(last->parent->parent, last->parent);
            }

            if (last->parent == nullptr)
                break;

            last = last->parent;
        }
    }
    template <typename T> void AVL<T>::add(T new_item)
    {
        typename __super::node* new_root = __super::add_private(nullptr, __super::root, new_item);
        
        if (__super::root == nullptr)
            __super::root = new_root;
        else
            this->balance();

        __super::node_count++;
    }

    template <typename T> void AVL<T>::rotate_left (AVL<T>::node* X, AVL<T>::node* Y)
    {
        typename __super::node* parent_of_parent = X->parent;

        X->right = Y->left;

        if (X->right != nullptr)
            X->right->parent = X;
        
        Y->left  = X;

        X->parent = Y;
        Y->parent = parent_of_parent;

        if (parent_of_parent == nullptr)
            __super::root = Y;
        else
        {
            if (parent_of_parent->item < X->item)
            {
                parent_of_parent->right = Y;
            }
            else
            {
                parent_of_parent->left = Y;
            }
        }
    }
    template <typename T> void AVL<T>::rotate_right(AVL<T>::node* X, AVL<T>::node* Y)
    {
        typename __super::node* parent_of_parent = X->parent;

        X->left = Y->right;

        if (X->left != nullptr)
            X->left->parent = X;
        
        Y->right = X;

        X->parent = Y;
        Y->parent = parent_of_parent;

        if (parent_of_parent == nullptr)
            __super::root = Y;
        else
        {
            if (parent_of_parent->item < X->item)
            {
                parent_of_parent->right = Y;
            }
            else
            {
                parent_of_parent->left = Y;
            }
        }
    }
}
