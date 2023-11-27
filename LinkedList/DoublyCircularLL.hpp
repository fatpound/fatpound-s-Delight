#pragma once

#include <iostream>

namespace fatpound::linkedlist
{
    template <typename T>
    class DoublyCircularLL
    {
    public:
        DoublyCircularLL() = default;
        ~DoublyCircularLL()
        {
            if (list_ == nullptr)
            {
                return;
            }

            node* start = list_;
            node* ex = list_;
            node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != start);
        }
        DoublyCircularLL(const DoublyCircularLL& src) = delete;
        DoublyCircularLL(DoublyCircularLL&& src)
            :
            list_{ std::move(src.list_) },
            end_{ std::move(src.end_) },
            item_count_{ std::exchange(src.item_count_, 0ui64) }
        {

        }
        DoublyCircularLL& operator = (const DoublyCircularLL& src) = delete;
        DoublyCircularLL& operator = (DoublyCircularLL&& src)
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
                new_part->next = new_part;
                new_part->prev = new_part;

                list_ = new_part;
                end_ = new_part;

                return;
            }

            end_->next = new_part;
            new_part->prev = end_;
            new_part->next = list_;
            list_->prev = new_part;

            end_ = new_part;
        }
        void AddOrdered(T new_item)
        {
            node* new_part = new node(new_item);
            item_count_++;

            if (list_ == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                list_ = new_part;

                return;
            }

            if (new_item < list_->item)
            {
                new_part->next = list_;
                list_->prev = new_part;
                list_ = new_part;

                end_->next = list_;
                list_->prev = end_;

                return;
            }

            node* temp = list_;
            node* start = temp;

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
        void Reverse()
        {
            if (list_ == nullptr)
            {
                return;
            }

            node* temp = list_;
            node* start = list_;

            while (temp->next != start)
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
            node* start = temp;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != start);

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
                item(new_item)
            {

            }
        };


    private:
        node* list_ = nullptr;
        node* end_  = nullptr;

        size_t item_count_ = 0ui64;
    };
}