#pragma once

#include "fatpound.hpp"

namespace fatpound::tree
{
    template <typename T, std::uint64_t C>
    class B
    {
    private:
        /********************************/
        /*            Private           */
        /*            Classes           */
        /********************************/

        class node
        {
        private:


        protected:


        public:
            std::vector<std::pair<T, B<T, C>::node*>*> items;

            B<T, C>::node* lesser = nullptr;
            B<T, C>::node* parent = nullptr;

            node();
            node(std::vector<T>& new_items);
            node(std::vector<T>& new_items, B<T, C>::node* new_parent);
            node(B<T, C>::node* new_lesser);
        };

        /********************************/
        /*            Private           */
        /*           Variables          */
        /********************************/

        B<T, C>::node* root = nullptr;

        std::uint64_t capacity_order = C;

        /********************************/
        /*            Private           */
        /*           Functions          */
        /********************************/

        void private_insert  (B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time);
        void private_overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair);


    protected:


    public:
        void insert(T new_item);
    };
    
    template <typename T, std::uint64_t C> B<T, C>::node::node()
    {

    }
    template <typename T, std::uint64_t C> B<T, C>::node::node(std::vector<T>& new_items)
    {
        for (int i = 0; i < new_items.size(); i++)
            this->items.push_back(new std::pair<T, B<T, C>::node*>{new_items.at(i), nullptr});
    }
    template <typename T, std::uint64_t C> B<T, C>::node::node(std::vector<T>& new_items, B<T, C>::node* new_parent)
    {
        for (int i = 0; i < new_items.size(); i++)
        {
            std::pair<T, B<T, C>::node*> pair{new_items.at(i), nullptr};
            this->items.push_back(pair);
        }

        this->parent = new_parent;
    }
    template <typename T, std::uint64_t C> B<T, C>::node::node(B<T, C>::node* new_lesser)
    {
        this->lesser = new_lesser;
    }

    template <typename T, std::uint64_t C> void B<T, C>::private_overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair)
    {
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec;

        temp_vec.push_back(pair);

        for (int i = 0; i < this->capacity_order * 2; i++)
            temp_vec.push_back(node->items.at(i));

        std::sort(temp_vec.begin(), temp_vec.end(), [](std::pair<T, B<T, C>::node*>* ref1, std::pair<T, B<T, C>::node*>* ref2) {return ref1->first < ref2->first; });

        int center = (this->capacity_order * 2 + 1) / 2;

        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_less;
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_more;

        for (int i = 0; i < center; i++)
            temp_vec_less.push_back(temp_vec.at(i));

        for (int i = center + 1; i <= this->capacity_order * 2; i++)
            temp_vec_more.push_back(temp_vec.at(i));

        node->items.clear();

        for (int i = 0; i < temp_vec_less.size(); i++)
            node->items.push_back(temp_vec_less.at(i));

        if (node == this->root)
        {
            node->parent = new B<T, C>::node(node);
            this->root = node->parent;
        }

        this->private_insert(node->parent, temp_vec.at(center), false);
        
        B<T, C>::node* new_node = new B<T, C>::node();
        new_node->parent = node->parent;

        for (int i = 0; i < temp_vec_more.size(); i++)
            new_node->items.push_back(temp_vec_more.at(i));

        new_node->lesser = temp_vec.at(center)->second;
        temp_vec.at(center)->second = new_node;
    }
    template <typename T, std::uint64_t C> void B<T, C>::private_insert(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time)
    {
        if (node == nullptr)
            return;

    label:

        if (node->items.size() == this->capacity_order * 2)
        {
            if (add_first_time)
            {
                int idx = -1;

                for (int i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items.at(i)->first && node->items.at(i)->second != nullptr)
                        idx = i;
                }

                if (idx != -1)
                    this->private_insert(node->items.at(idx)->second, pair, true);
                else
                    this->private_overflow(node, pair);
            }
            else
                this->private_overflow(node, pair);
        }
        else
        {
            int index = 0;

            if (node->items.size() != 0 && add_first_time)
            {
                if (pair->first < node->items.at(0)->first && node->lesser != nullptr)
                {
                    node = node->lesser;
                    goto label;
                }

                for (int i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items.at(i)->first)
                        index = i;
                }

                if (node->items.at(index)->second != nullptr)
                {
                    node = node->items.at(index)->second;
                    goto label;
                }
            }

            node->items.push_back(pair);

            if (node->items.size() > 1)
                std::sort(node->items.begin(), node->items.end(), [](std::pair<T, B<T, C>::node*>* ref1, std::pair<T, B<T, C>::node*>* ref2) {return ref1->first < ref2->first; });
        }
    }
    template <typename T, std::uint64_t C> void B<T, C>::insert(T new_item)
    {
        std::vector<T> vec{new_item};

        if (this->root == nullptr)
        {
            this->root = new B<T, C>::node(vec);
            return;
        }
        
        this->private_insert(this->root, new  std::pair<T, B<T, C>::node*>{new_item, nullptr}, true);
    }
}
