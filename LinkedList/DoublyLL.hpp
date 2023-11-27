#pragma once

#include <iostream>

namespace fatpound::linkedlist
{
    template <typename T>
    class DoublyLL
    {
    public:
        DoublyLL() = default;
        ~DoublyLL() noexcept
        {
            if (list_ == nullptr)
            {
                return;
            }

            DoublyLL<T>::node* ex = list_;
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
        DoublyLL(DoublyLL&& src)
            :
            list_{ std::move(src.list_) },
            end_{ std::move(src.end_) },
            item_count_{ std::exchange(src.item_count_, 0ui64) }
        {

        }
        DoublyLL& operator = (const DoublyLL& src) = delete;
        DoublyLL& operator = (DoublyLL&& src)
        {
            list_ = std::move(src.list_);
            end_ = std::move(src.end_);
            item_count_ = std::exchange(src.item_count_, 0ui64);

            return *this;
        }


    public:
        void Add(T new_item)
        {
            node* new_part = new node(new_item);

            item_count_++;

            if (list_ == nullptr)
            {
                list_ = new_part;
                end_ = new_part;

                return;
            }

            end_->next = new_part;
            new_part->prev = end_;

            end_ = new_part;
        }
        void AddOrdered(T new_item)
        {
            node* new_part = new node(new_item);

            item_count_++;

            if (list_ == nullptr)
            {
                list_ = new_part;
                return;
            }

            if (new_item < list_->item)
            {
                new_part->next = list_;
                list_->prev = new_part;
                list_ = new_part;

                return;
            }

            node* temp = list_;

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
        void Reverse()
        {
            if (list_ == nullptr)
            {
                return;
            }

            node* temp = list_;

            while (temp->next != nullptr)
            {
                std::swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            list_ = temp;
        }
        void Print() const
        {
            node* temp = list_;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != nullptr);

            std::cout << '\n';
        }


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
        node* list_ = nullptr;
        node* end_  = nullptr;
        
        size_t item_count_ = 0;
    };
}