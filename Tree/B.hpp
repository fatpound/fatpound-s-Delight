#pragma once

#include <iostream>
#include <vector>
#include <queue>

namespace fatpound::tree
{
    template <typename T, size_t C>
    class B
    {
    public:
        B() = default;
        ~B() noexcept
        {
            if (root_ == nullptr)
            {
                return;
            }

            class B<T, C>::node;

            std::queue<node*> Q;
            Q.push(root_);

            while (Q.size() > 0)
            {
                node* u = Q.front();
                Q.pop();

                if (u->lesser != nullptr)
                {
                    Q.push(u->lesser);
                }

                for (size_t i = 0; i < u->items.size(); i++)
                {
                    if (u->items[i]->second != nullptr)
                    {
                        Q.push(u->items[i]->second);
                    }

                    delete u->items[i];
                }

                delete u;
            }

            root_ = nullptr;
        }
        B(const B<T,C>& src) = delete;
        B(B<T,C>&& src) = delete;
        B<T, C>& operator = (const B<T,C>& src) = delete;
        B<T, C>& operator = (B<T,C>&& src) = delete;


    public:
        void Insert(const T& new_item);
        void ListLevelorder() const;
        

    protected:


    private:
        class node
        {
        public:
            node() = default;
            ~node() = default;
            node(const node& src) = delete;
            node(node&& src) = delete;
            node& operator = (const node& src) = delete;
            node& operator = (node&& src) = delete;

            node(B<T, C>::node* new_lesser)
                :
                lesser(new_lesser)
            {

            }
            node(std::pair<T, node*>* new_item, node* new_parent = nullptr)
                :
                parent(new_parent)
            {
                if (new_item != nullptr)
                {
                    items.push_back(new_item);
                }
            }

        public:
            std::vector<std::pair<T, node*>*> items;

            node* lesser = nullptr;
            node* parent = nullptr;

        protected:

        private:
        };


    private:
        void Insert(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time);
        void Overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair);


    private:
        node* root_ = nullptr;

        size_t depth_ = 0ui64;
    };


    template <typename T, size_t C> void B<T, C>::Insert(const T& new_item)
    {
        std::pair<T, B<T, C>::node*>* new_pair = new std::pair<T, B<T, C>::node*>{ new_item, nullptr };

        if (root_ == nullptr)
        {
            root_ = new B<T, C>::node(new_pair);
            depth_++;

            return;
        }
        
        Insert(root_, new_pair, true);
    }
    template <typename T, size_t C> void B<T, C>::Insert  (B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair, bool add_first_time)
    {
        if (node == nullptr)
        {
            return;
        }

    label:

        if (node->items.size() == C * 2)
        {
            if (add_first_time)
            {
                size_t idx = 0;
                bool flag = false;

                for (size_t i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items[i]->first && node->items[i]->second != nullptr)
                    {
                        if (flag == false)
                        {
                            flag = true;
                        }

                        idx = i;
                    }
                }

                if (flag)
                {
                    Insert(node->items[idx]->second, pair, true);
                }
                else
                {
                    Overflow(node, pair);
                }
            }
            else
            {
                Overflow(node, pair);
            }
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

                size_t index = 0;

                for (size_t i = 0; i < node->items.size(); i++)
                {
                    if (pair->first > node->items[i]->first)
                    {
                        index = i;
                    }
                }

                if (node->items[index]->second != nullptr)
                {
                    node = node->items[index]->second;
                    goto label;
                }
            }

            node->items.push_back(pair);

            if (node->items.size() > 1)
            {
                std::sort
                (
                    node->items.begin(),
                    node->items.end(),
                    [](std::pair<T, B<T, C>::node*>* p1, std::pair<T, B<T, C>::node*>* p2)
                    {
                        return p1->first < p2->first;
                    }
                );
            }
        }
    }
    template <typename T, size_t C> void B<T, C>::Overflow(B<T, C>::node* node, std::pair<T, B<T, C>::node*>* pair)
    {
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec;

        temp_vec.push_back(pair);

        for (size_t i = 0; i < C * 2; i++)
        {
            temp_vec.push_back(node->items[i]);
        }

        std::sort(
            temp_vec.begin(),
            temp_vec.end(),
            [] (std::pair<T, B<T, C>::node*>* p1, std::pair<T, B<T, C>::node*>* p2)
            {
                return p1->first < p2->first;
            }
        );

        size_t center = (C * 2 + 1) / 2;

        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_less;
        std::vector<std::pair<T, B<T, C>::node*>*> temp_vec_more;

        for (size_t i = 0; i < center; i++)
            temp_vec_less.push_back(temp_vec[i]);

        for (size_t i = center + 1; i <= C * 2; i++)
            temp_vec_more.push_back(temp_vec[i]);

        node->items.clear();

        for (size_t i = 0; i < temp_vec_less.size(); i++)
            node->items.push_back(temp_vec_less[i]);

        if (node == root_)
        {
            node->parent = new B<T, C>::node(node);
            root_ = node->parent;
            depth_++;
        }

        Insert(node->parent, temp_vec[center], false);
        
        B<T, C>::node* new_node = new B<T, C>::node();
        new_node->parent = node->parent;

        for (size_t i = 0; i < temp_vec_more.size(); i++)
            new_node->items.push_back(temp_vec_more[i]);

        new_node->lesser = temp_vec[center]->second;
        temp_vec[center]->second = new_node;
    }
    template <typename T, size_t C> void B<T, C>::ListLevelorder() const
    {
        if (root_ == nullptr)
            return;

        std::queue<B<T, C>::node*> Q;
        Q.push(root_);

        while (Q.size() > 0)
        {
            B<T, C>::node* u = Q.front();
            Q.pop();


            if (u->lesser != nullptr)
            {
                Q.push(u->lesser);
            }
            
            for (size_t i = 0; i < u->items.size(); i++)
            {
                std::cout << u->items[i]->first << ' ';

                if (u->items[i]->second != nullptr)
                {
                    Q.push(u->items[i]->second);
                }
            }

            std::cout << "\n";
        }

        std::cout << "\n";
    }
}