#pragma once

#include <iostream>

namespace fatpound::linkedlist
{
    template <typename T>
    class SinglyLL
    {
    public:
        SinglyLL() = default;
        ~SinglyLL()
        {
            if (list_ == nullptr)
            {
                return;
            }

            node* ex = list_;
            node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != nullptr);
        }
        SinglyLL(const SinglyLL& src) = delete;
        SinglyLL(SinglyLL&& src) = delete;
        SinglyLL& operator = (const SinglyLL& src) = delete;
        SinglyLL& operator = (SinglyLL&& src) = delete;


    public:
        void Add(T new_item);
        void AddOrdered(T new_item);
        void Reverse();
        void Print() const;


    protected:


    private:
        struct node
        {
            node* next = nullptr;
            T item;

            node(T new_item)
                :
                item{ new_item }
            {}
        };


    private:
        node* list_ = nullptr;
        node* end_ = nullptr;

        size_t item_count_ = 0;
    };


    template <typename T> void SinglyLL<T>::Add(T new_item)
    {
        node* new_part = new node(new_item);

        item_count_++;

        if (list_ == nullptr)
        {
            list_ = new_part;
            end_  = new_part;

            return;
        }

        end_->next = new_part;
        end_       = new_part;
    }
    template <typename T> void SinglyLL<T>::AddOrdered(T new_item)
    {
        node* new_part = new node(new_item);

        item_count_++;

        if (list_ == nullptr)
        {
            list_ = new_part;
            end_  = new_part;

            return;
        }

        if (new_item < list_->item)
        {
            new_part->next = list_;
            list_ = new_part;

            return;
        }

        node* temp = list_;

        while (temp->next != nullptr)
        {
            if (temp->item <= new_item && new_item <= temp->next->item)
            {
                new_part->next = temp->next;
                temp->next = new_part;

                return;
            }

            temp = temp->next;
        }

        temp->next = new_part;
        end_  = new_part;
    }
    template <typename T> void SinglyLL<T>::Reverse()
    {
        if (list_ == nullptr)
        {
            return;
        }

        node* start_backup = list_;

        node* t;
        node* a = nullptr;
        node* x;

        node* temp = list_;

        while (true)
        {
            t = temp->next;
            temp->next = a;
            a = t;
            x = temp;

            temp = t->next;
            t->next = x;

            if (temp == nullptr)
            {
                list_ = t;
                return;
            }

            if (temp->next == nullptr)
            {
                temp->next = t;
                list_ = temp;

                return;
            }
        }

        end_ = start_backup;
    }
    template <typename T> void SinglyLL<T>::Print() const
    {
        if (list_ == nullptr)
        {
            return;
        }

        node* temp = list_;

        do
        {
            std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        }
        while (temp != nullptr);

        std::cout << '\n';
    }
}