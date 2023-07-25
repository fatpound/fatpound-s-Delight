#pragma once

#include "fatpound.hpp"

namespace fatpound::linkedlist
{
    template <typename T>
    class SinglyCircularLL
    {
    private:
        struct node
        {
            SinglyCircularLL<T>::node* next = nullptr;
            T item;

            node(T new_item);
        };

        /********************************/
        /*           Variables          */
        /********************************/

        SinglyCircularLL<T>::node* list = nullptr;
        SinglyCircularLL<T>::node* end  = nullptr;

        std::size_t item_count = 0;


    protected:


    public:
        ~SinglyCircularLL();

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
    template <typename T> SinglyCircularLL<T>::node::node(T new_item)
    {
        this->item = new_item;
    }
    template <typename T> SinglyCircularLL<T>::~SinglyCircularLL()
    {
        if (this->list == nullptr)
            return;

        SinglyCircularLL<T>::node* start = this->list;
        SinglyCircularLL<T>::node* ex    = this->list;
        SinglyCircularLL<T>::node* temp;

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
    template <typename T> void SinglyCircularLL<T>::add(T new_item)
    {
        SinglyCircularLL<T>::node* new_part = new SinglyCircularLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list       = new_part;
            this->end        = new_part;
            this->list->next = this->list;

            return;
        }

        this->end->next = new_part;
        new_part->next  = this->list;

        this->end = new_part;
    }
    template <typename T> void SinglyCircularLL<T>::add_sorted(T new_item)
    {
        SinglyCircularLL<T>::node* new_part = new SinglyCircularLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list = new_part;
            new_part->next = this->list;

            return;
        }

        if (new_item < this->list->item)
        {
            new_part->next = this->list;
            this->list = new_part;

            this->end->next = new_part;

            return;
        }

        SinglyCircularLL<T>::node* temp = this->list;
        SinglyCircularLL<T>::node* start = temp;

        while (temp->next != start)
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
        new_part->next = start;
    }
    template <typename T> void SinglyCircularLL<T>::reverse()
    {
        if (this->list == nullptr)
            return;

        // this should resolve the C6011 error but the compiler is still not smart enough for this ("t can be null")
        // why? because if the linked list does not have at least 2 elements in it, there should be a runtime error
        // at that time which will obviously display an error on the user's screen
        // so i am going to add an if (t != nullptr) check to the while loop.
        if (this->item_count < 2)
            return;

        SinglyCircularLL<T>::node* start_backup = this->list;

        SinglyCircularLL<T>::node* t;
        SinglyCircularLL<T>::node* a = nullptr;
        SinglyCircularLL<T>::node* x;

        SinglyCircularLL<T>::node* temp = this->list;
        SinglyCircularLL<T>::node* start = temp;

        while (true)
        {
            t = temp->next;
            temp->next = a;
            a = t;
            x = temp;

            if (t->next) // C6011
            {
                temp = t->next;
                t->next = x;
            }

            if (temp == start)
            {
                start->next = t;

                this->list = t;

                return;
            }

            if (temp->next == start)
            {
                start->next = temp;

                temp->next = t;
                this->list = temp;

                return;
            }
        }

        start->next = temp;

        this->end = start_backup;
    }
    template <typename T> void SinglyCircularLL<T>::list_all() const
    {
        if (this->list == nullptr)
            return;

        SinglyCircularLL<T>::node* temp  = this->list;
        SinglyCircularLL<T>::node* start = temp;

        do
        {
            std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        }
        while (temp != start);

        std::cout << '\n';
    }
}