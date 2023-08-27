#pragma once

#include "AVL.hpp"

namespace fatpound::tree
{
    template <typename T>
    class IPR : public AVL<T>
    {
    private:
        void balance();


    protected:


    public:
        void add(T new_item);


    };

    template <typename T> void IPR<T>::balance()
    {
        typename __super::node* last = __super::last_added; // Y

        while (last->parent != nullptr) // Going up
        {
            int na;
            int nb;
            int nc;

            bool a_location; // left => false, right => true

            if (last->parent->item < last->item)
            {
                na = __super::get_count_private(last->parent->left);
                a_location = false;
            }
            else
            {
                na = __super::get_count_private(last->parent->right);
                a_location = true;
            }

            if (a_location == false)
            {
                nb = __super::get_count_private(last->left);
                nc = __super::get_count_private(last->right);
            }
            else
            {
                nb = __super::get_count_private(last->right);
                nc = __super::get_count_private(last->left);
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
                this->rotate_left(last->parent, last);
            }
            else
            if (nc > na && a_location == true)
            {
                this->rotate_right(last->parent, last);
            }
            else
            if (nb > na && a_location == false)
            {
                this->rotate_right(last, last->left);
                this->rotate_left(last->parent->parent, last->parent);
            }
            else
            if (nb > na && a_location == true)
            {
                this->rotate_left(last, last->right);
                this->rotate_right(last->parent->parent, last->parent);
            }
            
            if (last->parent == nullptr)
                break;

            last = last->parent;
        }
    }
    template <typename T> void IPR<T>::add(T new_item)
    {
        typename __super::node* new_root = __super::add_private(nullptr, __super::root, new_item);

        if (__super::root == nullptr)
            __super::root = new_root;
        else
            this->balance();

        __super::node_count++;
    }
}
