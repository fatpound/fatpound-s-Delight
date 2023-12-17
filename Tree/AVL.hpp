#pragma once

#include "BST.hpp"

namespace fatpound::tree
{
    template <typename T>
    class AVL : public BST<T>
    {
    public:
		virtual void Insert(T new_item) override
		{
			typename AVL<T>::Node* new_root = BST<T>::Insert(nullptr, this->root_, new_item);

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


    protected:
		virtual void Balance(AVL<T>::Node* lastInserted)
		{
			typename AVL<T>::Node* last = lastInserted; // Y
        
			while (last->parent != nullptr) // Going up
			{
			    const int  left_val = BST<T>::GetDepth(last->parent->left,  0i64);
			    const int right_val = BST<T>::GetDepth(last->parent->right, 0i64);

			    const int balanceFactor = right_val - left_val;

			    /*
			    std::cout << "parent  : " << last->parent->item << '\n';
			    std::cout << "node    : " << last->item << '\n';
			    std::cout << "left    : " << left_val << '\n';
			    std::cout << "rite    : " << right_val << '\n';
			    std::cout << "Balance : " << balanceFactor << "\n\n";
			    */

			    if (balanceFactor >  1 && lastInserted->item > last->item)
			    {
			        RotateLeft(last->parent, last);
			    }
			    else if (balanceFactor < -1 && lastInserted->item < last->item)
			    {
			        RotateRight(last->parent, last);
			    }
			    else if (balanceFactor >  1 && lastInserted->item < last->item)
			    {
			        RotateRight(last, last->left);
			        RotateLeft(last->parent->parent, last->parent);
			    }
			    else if (balanceFactor < -1 && lastInserted->item > last->item)
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
		void RotateLeft(AVL<T>::Node* X, AVL<T>::Node* Y)
		{
			typename AVL<T>::Node* parent_of_parent = X->parent;

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
		void RotateRight(AVL<T>::Node* X, AVL<T>::Node* Y)
		{
			typename AVL<T>::Node* parent_of_parent = X->parent;

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