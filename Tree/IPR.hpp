#pragma once

#include "AVL.hpp"

namespace fatpound::tree
{
    template <typename T>
    class IPR : public AVL<T>
    {
    private:
        void Balance();


    protected:


    public:
        void Insert(T new_item);


    };

    template <typename T> void IPR<T>::Balance()
    {
        typename __super::node* last = __super::last_Inserted; // Y

        while (last->parent != nullptr) // Going up
        {
            int na;
            int nb;
            int nc;

            bool a_location; // false => left, true => right

            if (last->parent->item < last->item)
            {
                na = __super::GetNodeCount_Protected(last->parent->left);
                a_location = false;
            }
            else
            {
                na = __super::GetNodeCount_Protected(last->parent->right);
                a_location = true;
            }

            if (a_location == false)
            {
                nb = __super::GetNodeCount_Protected(last->left);
                nc = __super::GetNodeCount_Protected(last->right);
            }
            else
            {
                nb = __super::GetNodeCount_Protected(last->right);
                nc = __super::GetNodeCount_Protected(last->left);
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
                RotateLeft(last->parent, last);
            }
            else
            if (nc > na && a_location == true)
            {
                RotateRight(last->parent, last);
            }
            else
            if (nb > na && a_location == false)
            {
                RotateRight(last, last->left);
                RotateLeft(last->parent->parent, last->parent);
            }
            else
            if (nb > na && a_location == true)
            {
                RotateLeft(last, last->right);
                RotateRight(last->parent->parent, last->parent);
            }
            
            if (last->parent == nullptr)
                break;

            last = last->parent;
        }
    }
    template <typename T> void IPR<T>::Insert(T new_item)
    {
        typename __super::node* new_root = __super::Insert_Protected(nullptr, __super::root, new_item);

        if (__super::root == nullptr)
            __super::root = new_root;
        else
            this->Balance();

        __super::node_count++;
    }
}