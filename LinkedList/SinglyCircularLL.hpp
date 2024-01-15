#pragma once

#include "SinglyLL.hpp"

namespace fatpound::linkedlist
{
    template <std::totally_ordered T>
    class SinglyCircularLL : public SinglyLL<T>
    {
    public:
        SinglyCircularLL() = default;
        virtual ~SinglyCircularLL() noexcept
        {
            if (this->list_ == nullptr)
            {
                return;
            }
            
            typename SinglyLL<T>::Node* start = this->list_;
            typename SinglyLL<T>::Node* ex = this->list_;
            typename SinglyLL<T>::Node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != start);

            this->list_ = nullptr;
            this->end_  = nullptr;

            this->item_count_ = static_cast<decltype(this->item_count_)>(0);
        }
        SinglyCircularLL(const SinglyCircularLL<T>& src) = delete;
        SinglyCircularLL(SinglyCircularLL<T>&& src) noexcept
            :
            SinglyLL<T>(std::move(src))
        {

        }
        SinglyCircularLL<T>& operator = (const SinglyCircularLL<T>& src) = delete;
        SinglyCircularLL<T>& operator = (SinglyCircularLL<T>&& src) noexcept
        {
            this->list_ = std::exchange(src.list_, nullptr);
            this->end_  = std::exchange(src.end_,  nullptr);

            this->item_count_ = std::exchange(src.item_count_, static_cast<decltype(this->item_count_)>(0));

            return *this;
        }


    public:
        virtual void Add(T new_item) override
        {
            typename SinglyLL<T>::Node* new_part = new SinglyLL<T>::Node(new_item);

            this->item_count_++;

            if (this->list_ == nullptr)
            {
                this->list_ = new_part;
                this->end_ = new_part;
                this->list_->next = this->list_;

                return;
            }

            this->end_->next = new_part;
            new_part->next = this->list_;

            this->end_ = new_part;
        }
        virtual void AddOrdered(T new_item) override
        {
            typename SinglyLL<T>::Node* new_part = new SinglyLL<T>::Node(new_item);

            this->item_count_++;

            if (this->list_ == nullptr)
            {
                this->list_ = new_part;
                new_part->next = this->list_;

                return;
            }

            if (new_item < this->list_->item)
            {
                new_part->next = this->list_;
                this->list_ = new_part;

                this->end_->next = new_part;

                return;
            }

            typename SinglyLL<T>::Node* temp = this->list_;
            typename SinglyLL<T>::Node* start = temp;

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
        virtual void Reverse() override
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            if (this->item_count_ < static_cast<decltype(this->item_count_)>(2))
            {
                return;
            }

            typename SinglyLL<T>::Node* start_backup = this->list_;

            typename SinglyLL<T>::Node* t;
            typename SinglyLL<T>::Node* a = nullptr;
            typename SinglyLL<T>::Node* x;

            typename SinglyLL<T>::Node* temp = this->list_;
            typename SinglyLL<T>::Node* start = temp;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                if (t->next) // C6011, I think its gone
                {
                    temp = t->next;
                    t->next = x;
                }

                if (temp == start)
                {
                    start->next = t;

                    this->list_ = t;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = t;
                    this->list_ = temp;

                    return;
                }
            }

            start->next = temp;

            this->end_ = start_backup;
        }
        virtual void Print() const override
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            typename SinglyLL<T>::Node* temp = this->list_;
            typename SinglyLL<T>::Node* start = temp;

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
    };
}