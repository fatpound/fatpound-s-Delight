#pragma once

#include "fatpound.hpp"

namespace fatpound::tree
{
    template <typename T, std::size_t C>
    class B
    {
    private:
        class node
        {
        private:


        protected:


        public:
            std::vector<std::pair<T, B<T, C>::node*>*> items;

            B<T, C>::node* lesser = nullptr;
            B<T, C>::node* parent = nullptr;

            node();
            node(B<T, C>::node* new_lesser);
            node(std::pair<T, B<T, C>::node*>* new_item);
            node(std::pair<T, B<T, C>::node*>* new_item, B<T, C>::node* new_parent);
        };

        B<T, C>::node* root = nullptr;

        std::size_t depth = 0;

        void Insert(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time);
        void Overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair);


    protected:
        

    public:
        B() = default;
        ~B();
        B( const B<T,C>& src ) = delete;
        B& operator = ( const B<T,C>& src ) = delete;

        void Insert(T new_item);
        void ListLevelorder() const;
    };

    
    template <typename T, std::size_t C> B<T, C>::node::node()
    {

    }
    template <typename T, std::size_t C> B<T, C>::node::node(B<T, C>::node* new_lesser)
    {
        lesser = new_lesser;
    }
    template <typename T, std::size_t C> B<T, C>::node::node(std::pair<T, B<T, C>::node*>* new_item)
    {
        items.push_back(new_item);
    }
    template <typename T, std::size_t C> B<T, C>::node::node(std::pair<T, B<T, C>::node*>* new_item, B<T, C>::node* new_parent)
    {
        items.push_back(new_item);
        parent = new_parent;
    }

    template <typename T, std::size_t C> B<T, C>::~B()
    {
        if (root == nullptr)
            return;

        std::queue<B<T, C>::node*> Q;
        Q.push(root);

        while (Q.size() > 0)
        {
            B<T, C>::node* u = Q.front();
            Q.pop();

            if (u->lesser != nullptr)
                Q.push(u->lesser);

            for (std::size_t i = 0; i < u->items.size(); i++)
            {
                if (u->items[i]->second != nullptr)
                    Q.push(u->items[i]->second);

                delete u->items[i];
            }

            delete u;
        }

        root = nullptr;
    }

    template <typename T, std::size_t C> void B<T, C>::Overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair)
    {
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec;

        temp_vec.push_back(pair);

        for (std::size_t i = 0; i < C * 2; i++)
            temp_vec.push_back(node->items[i]);

        std::sort(temp_vec.begin(), temp_vec.end(), [](std::pair<T, B<T, C>::node*>* ref1, std::pair<T, B<T, C>::node*>* ref2) {return ref1->first < ref2->first; });

        std::size_t center = (C * 2 + 1) / 2;

        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_less;
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_more;

        for (std::size_t i = 0; i < center; i++)
            temp_vec_less.push_back(temp_vec[i]);

        for (std::size_t i = center + 1; i <= C * 2; i++)
            temp_vec_more.push_back(temp_vec[i]);

        node->items.clear();

        for (std::size_t i = 0; i < temp_vec_less.size(); i++)
            node->items.push_back(temp_vec_less[i]);

        if (node == root)
        {
            node->parent = new B<T, C>::node(node);
            root = node->parent;
            depth++;
        }

        Insert(node->parent, temp_vec[center], false);
        
        B<T, C>::node* new_node = new B<T, C>::node();
        new_node->parent = node->parent;

        for (std::size_t i = 0; i < temp_vec_more.size(); i++)
            new_node->items.push_back(temp_vec_more[i]);

        new_node->lesser = temp_vec[center]->second;
        temp_vec[center]->second = new_node;
    }
    template <typename T, std::size_t C> void B<T, C>::Insert  (B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time)
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
                    if (pair->first > node->items[i]->first && node->items[i]->second != nullptr)
                    {
                        if (flag == false)
                            flag = true;

                        idx = i;
                    }
                }

                if (flag)
                    Insert(node->items[idx]->second, pair, true);
                else
                    Overflow(node, pair);
            }
            else
                Overflow(node, pair);
        }
        else
        {
            if (node->items.size() != 0 && add_first_time)
            {
                if (pair->first < node->items[0]->first && node->lesser != nullptr)
                {
                    node = node->lesser;
                    goto label;
                }

                std::size_t index = 0;

                for (std::size_t i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items[i]->first)
                        index = i;
                }

                if (node->items[index]->second != nullptr)
                {
                    node = node->items[index]->second;
                    goto label;
                }
            }

            node->items.push_back(pair);

            if (node->items.size() > 1)
                std::sort(node->items.begin(), node->items.end(), [](std::pair<T, B<T, C>::node*>* ref1, std::pair<T, B<T, C>::node*>* ref2) {return ref1->first < ref2->first; });
        }
    }

    template <typename T, std::size_t C> void B<T, C>::ListLevelorder() const
    {
        if (root == nullptr)
            return;

        std::queue<B<T, C>::node*> Q;
        Q.push(root);

        std::int64_t level = 1;

        for (std::int64_t i = 1; Q.size() > 0; i++)
        {
            B<T, C>::node* u = Q.front();
            Q.pop();

            if (fatpound::math::IsPowerOf2(i))
            {
                std::cout << "Level " << level << " : ";
                level++;
            }

            if (u->lesser != nullptr)
            {
                Q.push(u->lesser);
            }
            
            for (std::size_t j = 0; j < u->items.size(); j++)
            {
                std::cout << u->items[j]->first << ' ';

                if (u->items[j]->second != nullptr)
                    Q.push(u->items[j]->second);
            }

            if (fatpound::math::IsPowerOf2(i))
                std::cout << "\n";
            else if (Q.size() != 0 && u != nullptr)
                std::cout << "- ";
            // else break;
        }

        std::cout << "\n";
    }
    template <typename T, std::size_t C> void B<T, C>::Insert(T new_item)
    {
        std::pair<T, B<T, C>::node*>* new_pair = new std::pair<T, B<T, C>::node*>{ new_item, nullptr };

        if (root == nullptr)
        {
            root = new B<T, C>::node(new_pair);
            depth++;

            return;
        }
        
        Insert(root, new_pair, true);
    }
}