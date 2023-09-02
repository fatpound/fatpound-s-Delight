#pragma once

#include "BST.hpp"

namespace fatpound::tree
{
    template <typename T>
    class AVL : public BST<T>
    {
    private:
        void Balance();


    protected:
        void RotateLeft (AVL<T>::node* X, AVL<T>::node* Y);
        void RotateRight(AVL<T>::node* X, AVL<T>::node* Y);


    public:
        void Insert(T new_item);


    };

    template <typename T> void AVL<T>::Balance()
    {
        typename __super::node* last = __super::lastInserted; // Y
        
        while (last->parent != nullptr) // Going up
        {
            const int  left_val = __super::GetDepth_Protected(last->parent->left,  0);
            const int right_val = __super::GetDepth_Protected(last->parent->right, 0);

            const int balanceFactor = right_val - left_val;

            /*
            std::cout << "parent  : " << last->parent->item << '\n';
            std::cout << "node    : " << last->item << '\n';
            std::cout << "left    : " << left_val << '\n';
            std::cout << "rite    : " << right_val << '\n';
            std::cout << "Balance : " << balanceFactor << "\n\n";
            */

            if (balanceFactor >  1 && __super::lastInserted->item > last->item)
            {
                RotateLeft(last->parent, last);
            }
            else
            if (balanceFactor < -1 && __super::lastInserted->item < last->item)
            {
                RotateRight(last->parent, last);
            }
            else
            if (balanceFactor >  1 && __super::lastInserted->item < last->item)
            {
                RotateRight(last, last->left);
                RotateLeft(last->parent->parent, last->parent);
            }
            else
            if (balanceFactor < -1 && __super::lastInserted->item > last->item)
            {
                RotateLeft(last, last->right);
                RotateRight(last->parent->parent, last->parent);
            }

            if (last->parent == nullptr)
                break;

            last = last->parent;
        }
    }
    template <typename T> void AVL<T>::Insert(T new_item)
    {
        typename __super::node* new_root = __super::Insert_Protected(nullptr, __super::root, new_item);
        
        if (__super::root == nullptr)
            __super::root = new_root;
        else
            this->Balance();

        __super::node_count++;
    }

    template <typename T> void AVL<T>::RotateLeft (AVL<T>::node* X, AVL<T>::node* Y)
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
    template <typename T> void AVL<T>::RotateRight(AVL<T>::node* X, AVL<T>::node* Y)
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