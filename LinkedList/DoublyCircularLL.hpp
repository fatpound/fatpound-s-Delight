#pragma once

#include "DoublyLL.hpp"

namespace fatpound::linkedlist
{
    template <std::totally_ordered T>
    class DoublyCircularLL final : public DoublyLL<T>
    {
    public:
        DoublyCircularLL() = default;
        virtual ~DoublyCircularLL() noexcept override
        {
            Delete_();
        }
        DoublyCircularLL(const DoublyCircularLL& src) = delete;
        DoublyCircularLL(DoublyCircularLL&& src) noexcept
            :
            DoublyLL<T>(std::move(src))
        {
            
        }
        DoublyCircularLL<T>& operator = (const DoublyCircularLL& src) = delete;
        DoublyCircularLL<T>& operator = (DoublyCircularLL&& src) noexcept
        {
            Delete_();

            if (this != std::addressof(src) && typeid(src) == typeid(*this) && src.list_ != nullptr)
            {
                this->list_ = std::exchange(src.list_, nullptr);
                this->end_ = std::exchange(src.end_, nullptr);

                this->item_count_ = std::exchange(src.item_count_, 0u);

                return *this;
            }
        }


    public:
        void Add(T new_item) override
        {
            typename DoublyLL<T>::Node* new_part = new DoublyLL<T>::Node(new_item);

            ++(this->item_count_);

            if (this->list_ == nullptr)
            {
                new_part->next = new_part;
                new_part->prev = new_part;

                this->list_ = new_part;
                this->end_ = new_part;

                return;
            }

            this->end_->next = new_part;
            new_part->prev = this->end_;
            new_part->next = this->list_;
            this->list_->prev = new_part;

            this->end_ = new_part;
        }
        void AddOrdered(T new_item) override
        {
            typename DoublyLL<T>::Node* new_part = new DoublyLL<T>::Node(new_item);

            ++(this->item_count_);

            if (this->list_ == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                this->list_ = new_part;

                return;
            }

            if (new_item < this->list_->item)
            {
                new_part->next = this->list_;
                this->list_->prev = new_part;
                this->list_ = new_part;

                this->end_->next = this->list_;
                this->list_->prev = this->end_;

                return;
            }

            typename DoublyLL<T>::Node* temp = this->list_;
            typename DoublyLL<T>::Node* start = temp;

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
        void Reverse() override
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            if (this->item_count_ < 2u)
            {
                return;
            }

            typename DoublyLL<T>::Node* temp = this->list_;
            typename DoublyLL<T>::Node* start = this->list_;

            while (temp->next != start)
            {
                std::swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            this->list_ = temp;
        }
        void Print() const override
        {
            if (this->list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty DoublyCircularLL!");
            }

            typename DoublyLL<T>::Node* temp = this->list_;
            typename DoublyLL<T>::Node* start = temp;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != start);

            std::cout << '\n';
        }


    protected:
        void Delete_() override
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            typename DoublyLL<T>::Node* start = this->list_;
            typename DoublyLL<T>::Node* ex = this->list_;
            typename DoublyLL<T>::Node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != start);

            this->list_ = nullptr;
            this->end_ = nullptr;

            this->item_count_ = 0u;
        }


    private:
    };
}