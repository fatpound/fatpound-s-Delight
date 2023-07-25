#pragma once

#include "fatpound.hpp"

namespace fatpound::linkedlist
{
    template <typename T>
    class DoublyLL
    {
    private:
        struct node
        {
            DoublyLL<T>::node* prev = nullptr;
            DoublyLL<T>::node* next = nullptr;
            T item;

            node(T new_item);
        };

        /********************************/
        /*           Variables          */
        /********************************/

        DoublyLL<T>::node* list = nullptr;
        DoublyLL<T>::node* end  = nullptr;
        
        std::size_t item_count = 0;


    protected:


    public:
        ~DoublyLL();

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
    template <typename T> DoublyLL<T>::node::node(T new_item)
    {
        this->item = new_item;
    }
    template <typename T> DoublyLL<T>::~DoublyLL()
    {
        if (this->list == nullptr)
            return;

        DoublyLL<T>::node* ex = this->list;
        DoublyLL<T>::node* temp;

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
    template <typename T> void DoublyLL<T>::add(T new_item)
    {
        DoublyLL<T>::node* new_part = new DoublyLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list = new_part;
            this->end  = new_part;

            return;
        }

        this->end->next = new_part;
        new_part->prev  = this->end;

        this->end = new_part;
    }
    template <typename T> void DoublyLL<T>::add_sorted(T new_item)
    {
        DoublyLL<T>::node* new_part = new DoublyLL<T>::node(new_item);

        this->item_count++;

        if (this->list == nullptr)
        {
            this->list = new_part;
            return;
        }

        if (new_item < this->list->item)
        {
            new_part->next = this->list;
            this->list->prev = new_part;
            this->list = new_part;

            return;
        }

        DoublyLL<T>::node* temp = this->list;

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
    template <typename T> void DoublyLL<T>::reverse()
    {
        if (this->list == nullptr)
            return;

        DoublyLL<T>::node* temp = this->list;

        while (temp->next != nullptr)
        {
            swap(temp->prev, temp->next);
            temp = temp->prev;
        }

        std::swap(temp->prev, temp->next);
        this->list = temp;
    }
    template <typename T> void DoublyLL<T>::list_all() const
    {
        DoublyLL<T>::node* temp = this->list;

        do
        {
            std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            temp = temp->next;
        } while (temp != nullptr);

        std::cout << '\n';
    }
}