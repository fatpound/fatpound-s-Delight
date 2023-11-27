#pragma once

#include <iostream>

namespace fatpound::linkedlist
{
    template <typename T>
    class SinglyCircularLL
    {
    public:
        SinglyCircularLL() = default;
        ~SinglyCircularLL() noexcept
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
        SinglyCircularLL(const SinglyCircularLL& src) = delete;
        SinglyCircularLL(SinglyCircularLL&& src)
            :
            list_{ std::move(src.list_) },
            end_{ std::move(src.end_) },
            item_count_{ std::exchange(src.item_count_, 0ui64) }
        {

        }
        SinglyCircularLL& operator = (const SinglyCircularLL& src) = delete;
        SinglyCircularLL& operator = (SinglyCircularLL&& src)
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
                list_->next = list_;

                return;
            }

            end_->next = new_part;
            new_part->next = list_;

            end_ = new_part;
        }
        void AddOrdered(T new_item)
        {
            node* new_part = new node(new_item);

            item_count_++;

            if (list_ == nullptr)
            {
                list_ = new_part;
                new_part->next = list_;

                return;
            }

            if (new_item < list_->item)
            {
                new_part->next = list_;
                list_ = new_part;

                end_->next = new_part;

                return;
            }

            node* temp = list_;
            node* start = temp;

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
        void Reverse()
        {
            if (list_ == nullptr)
            {
                return;
            }

            // this should resolve the C6011 error but the compiler is still not smart enough for this ("t can be null")
            // why? because if the linked list does not have at least 2 elements in it, there should be a runtime error
            // at that time which will obviously display an error on the user's screen
            // so i am going to add an if (t != nullptr) check to the while loop.
            if (item_count_ < 2)
            {
                return;
            }

            node* start_backup = list_;

            node* t;
            node* a = nullptr;
            node* x;

            node* temp = list_;
            node* start = temp;

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

                    list_ = t;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = t;
                    list_ = temp;

                    return;
                }
            }

            start->next = temp;

            end_ = start_backup;
        }
        void Print() const
        {
            if (list_ == nullptr)
            {
                return;
            }

            node* temp = list_;
            node* start = temp;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != start);

            std::cout << '\n';
        }


    protected:


    private:
        struct node
        {
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