#pragma once

#include "fatpound.hpp"

namespace fatpound::linkedlist
{
    template <typename T>
    class SinglyLL
    {
    private:
        /********************************/
        /*            Private           */
        /*            Structs           */
        /********************************/

        struct node
        {
            SinglyLL<T>::node* next = nullptr;
            T item;

            node(T new_item);
        };


        /********************************/
        /*            Private           */
        /*           Variables          */
        /********************************/

        SinglyLL<T>::node* list = nullptr;
        SinglyLL<T>::node* end  = nullptr;

        std::size_t item_count = 0;
        

    protected:


    public:
        ~SinglyLL();

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
    template <typename T> SinglyLL<T>::node::node(T new_item)
    {
        this->item = new_item;
    }
    template <typename T> SinglyLL<T>::~SinglyLL()
    {
        if (this->list == nullptr)
            return;

        SinglyLL<T>::node* ex = this->list;
        SinglyLL<T>::node* temp;

        do
        {
            temp = ex->next;
            delete ex;

            ex = temp;
        }
        while (ex != nullptr);
    }
    //
    // 
    //   void
    //
    //
    template <typename T> void SinglyLL<T>::add(T new_item)
    {
        SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list = new_part;
            this->end  = new_part;

            return;
        }

        this->end->next = new_part;
        this->end       = new_part;
    }
    template <typename T> void SinglyLL<T>::add_sorted(T new_item)
    {
        SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list = new_part;
            this->end  = new_part;

            return;
        }

        if (new_item < this->list->item)
        {
            new_part->next = this->list;
            this->list = new_part;

            return;
        }

        SinglyLL<T>::node* temp = this->list;

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
        this->end  = new_part;
    }
    template <typename T> void SinglyLL<T>::reverse()
    {
        if (this->list == nullptr)
            return;

        SinglyLL<T>::node* start_backup = this->list;

        SinglyLL<T>::node* t;
        SinglyLL<T>::node* a = nullptr;
        SinglyLL<T>::node* x;

        SinglyLL<T>::node* temp = this->list;

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
                this->list = t;
                return;
            }

            if (temp->next == nullptr)
            {
                temp->next = t;
                this->list = temp;

                return;
            }
        }

        this->end = start_backup;
    }
    template <typename T> void SinglyLL<T>::list_all() const
    {
        if (this->list == nullptr)
            return;

        SinglyLL<T>::node* temp = this->list;

        do
        {
            std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        }
        while (temp != nullptr);

        std::cout << '\n';
    }
}