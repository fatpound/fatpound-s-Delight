#pragma once

#include <iostream>

namespace fatpound::linkedlist
{
    template <typename T>
    class DoublyLL
    {
    public:
        DoublyLL() = default;
        ~DoublyLL()
        {
            if (list == nullptr)
            {
                return;
            }

            DoublyLL<T>::node* ex = list;
            DoublyLL<T>::node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != nullptr);
        }
        DoublyLL(const DoublyLL& src) = delete;
        DoublyLL(DoublyLL&& src) = delete;
        DoublyLL& operator = (const DoublyLL& src) = delete;
        DoublyLL& operator = (DoublyLL&& src) = delete;


    public:
        void Add(T new_item);
        void AddOrdered(T new_item);
        void Reverse();
        void Print() const;


    protected:


    private:
        struct node
        {
            node* prev = nullptr;
            node* next = nullptr;

            T item;

            node(T new_item)
                :
                item{ new_item }
            {}
        };


    private:
        node* list = nullptr;
        node* end  = nullptr;
        
        size_t item_count = 0;
    };


    template <typename T> void DoublyLL<T>::Add(T new_item)
    {
        DoublyLL<T>::node* new_part = new DoublyLL<T>::node(new_item);

        item_count++;

        if (list == nullptr)
        {
            list = new_part;
            end  = new_part;

            return;
        }

        end->next = new_part;
        new_part->prev  = end;

        end = new_part;
    }
    template <typename T> void DoublyLL<T>::AddOrdered(T new_item)
    {
        DoublyLL<T>::node* new_part = new DoublyLL<T>::node(new_item);

        item_count++;

        if (list == nullptr)
        {
            list = new_part;
            return;
        }

        if (new_item < list->item)
        {
            new_part->next = list;
            list->prev = new_part;
            list = new_part;

            return;
        }

        DoublyLL<T>::node* temp = list;

        while (temp->next != nullptr)
        {
            if (temp->item <= new_item && new_item <= temp->next->item)
            {
                new_part->next = temp->next;
                new_part->prev = temp;
                temp->next->prev = new_part;
                temp->next = new_part;

                return;
            }

            temp = temp->next;
        }

        temp->next = new_part;
        new_part->prev = temp;
    }
    template <typename T> void DoublyLL<T>::Reverse()
    {
        if (list == nullptr)
        {
            return;
        }

        DoublyLL<T>::node* temp = list;

        while (temp->next != nullptr)
        {
            swap(temp->prev, temp->next);
            temp = temp->prev;
        }

        std::swap(temp->prev, temp->next);
        list = temp;
    }
    template <typename T> void DoublyLL<T>::Print() const
    {
        DoublyLL<T>::node* temp = list;

        do
        {
            std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        }
        while (temp != nullptr);

        std::cout << '\n';
    }
}