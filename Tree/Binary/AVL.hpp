#pragma once

#include "BST.hpp"

namespace fatpound::tree
{
    template <std::totally_ordered T>
    class AVL : public BST<T>
    {
        using typename BST<T>::Node_;

    public:
        virtual void Insert(const T& new_item) override
        {
            [[maybe_unused]] Node_* new_node = BST<T>::Insert_(nullptr, this->root_, new_item);

            if (this->root_ == nullptr) [[unlikely]]
            {
                this->root_ = new_node;
            }
            else
            {
                Balance_();
            }

            this->node_count_++;
        }
        virtual void Delete(const T& old_item) override
        {
            Node_* node = BST<T>::Find_(this->root_, old_item);

            if (node == this->root_)
            {
                // inorder_successor
                Node_* iosuc = BST<T>::GetInorderSuccessor_(node);

                node->item = iosuc->item;

                Balance_(BST<T>::Delete_(iosuc));
            }
            else
            {
                Balance_(BST<T>::Delete_(node));
            }
        }


    protected:
        virtual void Balance_()
        {
            this->Balance_(this->last_added_);
        }
        virtual void Balance_(const Node_* const latest)
        {
            if (latest == nullptr)
            {
                return;
            }

            Node_* last = const_cast<Node_*>(latest); // Y

            while (last->parent != nullptr) // Going up
            {
                const int  left_val = BST<T>::GetDepth_(last->parent->left, 0);
                const int right_val = BST<T>::GetDepth_(last->parent->right, 0);

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
                    RotateLeft_(last->parent, last);
                }
                else if (balanceFactor < -1 && latest->item < last->item)
                {
                    RotateRight_(last->parent, last);
                }
                else if (balanceFactor > 1 && latest->item < last->item)
                {
                    RotateRight_(last, last->left);
                    RotateLeft_(last->parent->parent, last->parent);
                }
                else if (balanceFactor < -1 && latest->item > last->item)
                {
                    RotateLeft_(last, last->right);
                    RotateRight_(last->parent->parent, last->parent);
                }

                if (last->parent == nullptr)
                {
                    break;
                }

                last = last->parent;
            }
        }
        virtual void RotateLeft_(Node_* X, Node_* Y) final
        {
            Node_* parent_of_parent = X->parent;

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
        virtual void RotateRight_(Node_* X, Node_* Y) final
        {
            Node_* parent_of_parent = X->parent;

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