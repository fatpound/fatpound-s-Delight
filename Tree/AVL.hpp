#pragma once

#include "BST.hpp"

namespace fatpound::tree
{
    template <std::totally_ordered T>
    class AVL : public BST<T>
    {
    public:
        virtual void Insert(T new_item) override
        {
            typename BST<T>::Node* new_root = BST<T>::Insert(nullptr, this->root_, new_item);

            if (this->root_ == nullptr)
            {
                this->root_ = new_root;
            }
            else
            {
                this->Balance(new_root);
            }

            this->nodeCount_++;
        }
        virtual void Delete(T old_item) override
        {
            typename BST<T>::Node* node = BST<T>::Find(this->root_, old_item);

            if (node == this->root_)
            {
                typename BST<T>::Node* iosuc = BST<T>::GetInorderSuccessor(node);
                node->item = iosuc->item;

                Balance(BST<T>::Delete(iosuc));
            }
            else
            {
                Balance(BST<T>::Delete(node));
            }
        }


    protected:
        virtual void Balance(BST<T>::Node* latest)
        {
            if (latest == nullptr)
            {
                return;
            }

            typename BST<T>::Node* last = latest; // Y
        
            while (last->parent != nullptr) // Going up
            {
                const int  left_val = BST<T>::GetDepth(last->parent->left,  0i64);
                const int right_val = BST<T>::GetDepth(last->parent->right, 0i64);

                const int balanceFactor = right_val - left_val;

                /*
                std::cout << "parent  : " << last->parent->item << '\n';
                std::cout << "node    : " << last->item << '\n';
                std::cout << "left    : " << left_val << '\n';
                std::cout << "right   : " << right_val << '\n';
                std::cout << "Balance : " << balanceFactor << "\n\n";
                */

                if (balanceFactor > 1 && latest->item > last->item)
                {
                    RotateLeft(last->parent, last);
                }
                else if (balanceFactor < -1 && latest->item < last->item)
                {
                    RotateRight(last->parent, last);
                }
                else if (balanceFactor > 1 && latest->item < last->item)
                {
                    RotateRight(last, last->left);
                    RotateLeft(last->parent->parent, last->parent);
                }
                else if (balanceFactor < -1 && latest->item > last->item)
                {
                    RotateLeft(last, last->right);
                    RotateRight(last->parent->parent, last->parent);
                }

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }
        void RotateLeft(BST<T>::Node* X, BST<T>::Node* Y)
        {
            typename BST<T>::Node* parent_of_parent = X->parent;

            X->right = Y->left;

            if (X->right != nullptr)
            {
                X->right->parent = X;
            }

            Y->left = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->root_ = Y;
            }
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
        void RotateRight(BST<T>::Node* X, BST<T>::Node* Y)
        {
            typename BST<T>::Node* parent_of_parent = X->parent;

            X->left = Y->right;

            if (X->left != nullptr)
            {
                X->left->parent = X;
            }

            Y->right = X;

            X->parent = Y;
            Y->parent = parent_of_parent;

            if (parent_of_parent == nullptr)
            {
                this->root_ = Y;
            }
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


    private:
    };
}