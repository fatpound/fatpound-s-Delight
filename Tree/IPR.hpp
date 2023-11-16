#pragma once

#include "AVL.hpp"

namespace fatpound::tree
{
    template <typename T>
    class IPR : public AVL<T>
    {
    public:
        void Insert(T new_item);
    

    protected:


    private:
        void Balance(IPR<T>::node* lastInserted);
    };


    template <typename T> void IPR<T>::Balance(IPR<T>::node* lastInserted)
    {
        typename IPR<T>::node* last = lastInserted; // Y

        while (last->parent != nullptr) // Going up
        {
            int na;
            int nb;
            int nc;

            bool a_location; // false => left, true => right

            if (last->parent->item < last->item)
            {
                na = BST<T>::GetNodeCount(last->parent->left);
                a_location = false;
            }
            else
            {
                na = BST<T>::GetNodeCount(last->parent->right);
                a_location = true;
            }

            if (a_location == false)
            {
                nb = BST<T>::GetNodeCount(last->left);
                nc = BST<T>::GetNodeCount(last->right);
            }
            else
            {
                nb = BST<T>::GetNodeCount(last->right);
                nc = BST<T>::GetNodeCount(last->left);
            }

            /*
            std::cout << "parent  : " << last->parent->item << '\n';
            std::cout << "node    : " << last->item << '\n';
            std::cout << "na      : " << na << '\n';
            std::cout << "nb      : " << nb << '\n';
            std::cout << "nc      : " << nc << '\n' << '\n';
            */
            
            if (nc > na && a_location == false)
            {
                AVL<T>::RotateLeft(last->parent, last);
            }
            else if (nc > na && a_location == true)
            {
                AVL<T>::RotateRight(last->parent, last);
            }
            else if (nb > na && a_location == false)
            {
                AVL<T>::RotateRight(last, last->left);
                AVL<T>::RotateLeft(last->parent->parent, last->parent);
            }
            else if (nb > na && a_location == true)
            {
                AVL<T>::RotateLeft(last, last->right);
                AVL<T>::RotateRight(last->parent->parent, last->parent);
            }
            
            if (last->parent == nullptr)
            {
                break;
            }

            last = last->parent;
        }
    }
    template <typename T> void IPR<T>::Insert(T new_item)
    {
        typename BST<T>::node* new_root = BST<T>::Insert(nullptr, this->root, new_item);

        if (this->root == nullptr)
        {
            this->root = new_root;
        }
        else
        {
            this->Balance(new_root);
        }

        this->nodeCount++;
    }
}