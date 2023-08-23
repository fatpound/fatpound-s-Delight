#pragma once

#include "fatpound.hpp"

namespace fatpound::tree
{
    template <typename T, std::size_t C>
    class B // I will add a destructor to this
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

        std::size_t depth = 0;

        bool is_deleted = false;

        bool trash0 = false; // to avoid C4820
        bool trash1 = false;
        bool trash2 = false;
        bool trash3 = false;
        bool trash4 = false;
        bool trash5 = false;
        bool trash6 = false;

        /********************************/
        /*            Private           */
        /*           Functions          */
        /********************************/

        void private_clear();

        void private_insert  (B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time);
        void private_overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair);


    protected:
        

    public:
        ~B();

        void insert(T new_item);
        void list_levelorder() const;
    };
    
    template <typename T, std::size_t C> B<T, C>::node::node()
    {

    }
    template <typename T, std::size_t C> B<T, C>::node::node(std::vector<T>& new_items)
    {
        for (std::size_t i = 0; i < new_items.size(); i++)
            this->items.push_back(new std::pair<T, B<T, C>::node*>{new_items.at(i), nullptr});
    }
    template <typename T, std::size_t C> B<T, C>::node::node(std::vector<T>& new_items, B<T, C>::node* new_parent)
    {
        for (int i = 0; i < new_items.size(); i++)
        {
            std::pair<T, B<T, C>::node*> pair{new_items.at(i), nullptr};
            this->items.push_back(pair);
        }

        this->parent = new_parent;
    }
    template <typename T, std::size_t C> B<T, C>::node::node(B<T, C>::node* new_lesser)
    {
        this->lesser = new_lesser;
    }

    template <typename T, std::size_t C> B<T, C>::~B()
    {
        if (this->is_deleted == false)
        {
            this->private_clear();
            this->is_deleted = true;
        }
    }

    template <typename T, std::size_t C> void B<T, C>::private_clear()
    {
        if (this->root == nullptr)
            return;

        std::queue<B<T, C>::node*> Q;
        Q.push(this->root);

        for (std::int64_t i = 1; Q.size() > 0; i++)
        {
            B<T, C>::node* u = Q.front();
            Q.pop();

            if (u->lesser != nullptr)
                Q.push(u->lesser);

            for (std::size_t j = 0; j < u->items.size(); j++)
            {
                if (u->items.at(j)->second != nullptr)
                    Q.push(u->items.at(j)->second);
            }

            delete u;
        }

        this->root = nullptr;
    }
    template <typename T, std::size_t C> void B<T, C>::private_overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair)
    {
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec;

        temp_vec.push_back(pair);

        for (std::size_t i = 0; i < C * 2; i++)
            temp_vec.push_back(node->items.at(i));

        std::sort(temp_vec.begin(), temp_vec.end(), [](std::pair<T, B<T, C>::node*>* ref1, std::pair<T, B<T, C>::node*>* ref2) {return ref1->first < ref2->first; });

        std::size_t center = (C * 2 + 1) / 2;

        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_less;
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_more;

        for (std::size_t i = 0; i < center; i++)
            temp_vec_less.push_back(temp_vec.at(i));

        for (std::size_t i = center + 1; i <= C * 2; i++)
            temp_vec_more.push_back(temp_vec.at(i));

        node->items.clear();

        for (std::size_t i = 0; i < temp_vec_less.size(); i++)
            node->items.push_back(temp_vec_less.at(i));

        if (node == this->root)
        {
            node->parent = new B<T, C>::node(node);
            this->root = node->parent;
            this->depth++;
        }

        this->private_insert(node->parent, temp_vec.at(center), false);
        
        B<T, C>::node* new_node = new B<T, C>::node();
        new_node->parent = node->parent;

        for (std::size_t i = 0; i < temp_vec_more.size(); i++)
            new_node->items.push_back(temp_vec_more.at(i));

        new_node->lesser = temp_vec.at(center)->second;
        temp_vec.at(center)->second = new_node;
    }
    template <typename T, std::size_t C> void B<T, C>::private_insert  (B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time)
    {
        if (node == nullptr)
            return;

    label:

        if (node->items.size() == C * 2)
        {
            if (add_first_time)
            {
                std::size_t idx = 0;
                bool flag = false;

                for (std::size_t i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items.at(i)->first && node->items.at(i)->second != nullptr)
                    {
                        if (flag == false)
                            flag = true;

                        idx = i;
                    }
                }

                if (flag)
                    this->private_insert(node->items.at(idx)->second, pair, true);
                else
                    this->private_overflow(node, pair);
            }
            else
                this->private_overflow(node, pair);
        }
        else
        {
            if (node->items.size() != 0 && add_first_time)
            {
                if (pair->first < node->items.at(0)->first && node->lesser != nullptr)
                {
                    node = node->lesser;
                    goto label;
                }

                std::size_t index = 0;

                for (std::size_t i = 0; i < node->items.size(); i++)
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

    template <typename T, std::size_t C> void B<T, C>::list_levelorder() const
    {
        if (this->root == nullptr)
            return;

        std::queue<B<T, C>::node*> Q;
        Q.push(this->root);

        std::int64_t level = 1;

        for (std::int64_t i = 1; Q.size() > 0; i++)
        {
            B<T, C>::node* u = Q.front();
            Q.pop();

            if (ISPOWOF2(i))
            {
                std::cout << "Level " << level << " : ";
                level++;
            }

            if (u->lesser != nullptr)
                Q.push(u->lesser);
            
            for (std::size_t j = 0; j < u->items.size(); j++)
            {
                std::cout << u->items.at(j)->first << ' ';

                if (u->items.at(j)->second != nullptr)
                    Q.push(u->items.at(j)->second);
            }

            if (ISPOWOF2(i + 1))
                std::cout << '\n';
            else if (Q.size() != 0 && u != nullptr)
                std::cout << "- ";
            // else break;
        }

        std::cout << '\n';
    }
    template <typename T, std::size_t C> void B<T, C>::insert(T new_item)
    {
        std::vector<T> vec{new_item};

        if (this->root == nullptr)
        {
            this->root = new B<T, C>::node(vec);
            this->depth++;

            return;
        }
        
        this->private_insert(this->root, new  std::pair<T, B<T, C>::node*>{new_item, nullptr}, true);
    }
}
