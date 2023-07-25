#pragma once

#include "fatpound.hpp"

namespace fatpound::linkedlist
{
    template <typename T>
    class DoublyCircularLL
    {
    private:
        struct node
        {
            DoublyCircularLL<T>::node* prev = nullptr;
            DoublyCircularLL<T>::node* next = nullptr;
            T item;

            node(T new_item);
        };

        DoublyCircularLL<T>::node* list = nullptr;
        DoublyCircularLL<T>::node* end  = nullptr;

        std::size_t item_count = 0;


    protected:


    public:
        ~DoublyCircularLL();

        void add(T new_item);
        void add_sorted(T new_item);
        void reverse();
        void list_all() const;
    };


    /********************************/
    /*       Public Functions       */
    /********************************/
    //
    //
    //   constructor
    //   destructors
    //
    //
    template <typename T> DoublyCircularLL<T>::node::node(T new_item)
    {
        this->item = new_item;
    }
    template <typename T> DoublyCircularLL<T>::~DoublyCircularLL()
    {
        if (this->list == nullptr)
            return;

        DoublyCircularLL<T>::node* start = this->list;
        DoublyCircularLL<T>::node* ex    = this->list;
        DoublyCircularLL<T>::node* temp;

        do
        {
            temp = ex->next;
            delete ex;

            ex = temp;
        }
        while (ex != start);
    }
    //
    // 
    //   void
    //
    //
    template <typename T> void DoublyCircularLL<T>::add(T new_item)
    {
        DoublyCircularLL<T>::node* new_part = new DoublyCircularLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            new_part->next = new_part;
            new_part->prev = new_part;

            this->list = new_part;
            this->end  = new_part;

            return;
        }

        this->end->next = new_part;
        new_part->prev = this->end;
        new_part->next = this->list;
        this->list->prev = new_part;

        this->end = new_part;
    }
    template <typename T> void DoublyCircularLL<T>::add_sorted(T new_item)
    {
        DoublyCircularLL<T>::node* new_part = new DoublyCircularLL<T>::node(new_item);
        this->item_count++;

        if (this->list == nullptr)
        {
            new_part->prev = new_part;
            new_part->next = new_part;
            this->list = new_part;

            return;
        }

        if (new_item < this->list->item)
        {
            new_part->next = this->list;
            this->list->prev = new_part;
            this->list = new_part;

            DoublyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);

            end->next = this->list;
            this->list->prev = end;

            return;
        }

        DoublyCircularLL<T>::node* temp = this->list;
        DoublyCircularLL<T>::node* start = temp;

        while (temp->next != start)
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

        new_part->next = start;
        start->prev = new_part;
    }
    template <typename T> void DoublyCircularLL<T>::reverse()
    {
        if (this->list == nullptr)
            return;

        DoublyCircularLL<T>::node* temp = this->list;
        DoublyCircularLL<T>::node* start = this->list;

        while (temp->next != start)
        {
            swap(temp->prev, temp->next);
            temp = temp->prev;
        }

        std::swap(temp->prev, temp->next);
        this->list = temp;
    }
    template <typename T> void DoublyCircularLL<T>::list_all() const
    {
        DoublyCircularLL<T>::node* temp = this->list;
        DoublyCircularLL<T>::node* start = temp;

        do
        {
            std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        } while (temp != start);

        std::cout << '\n';
    }
}