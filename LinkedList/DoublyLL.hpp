#pragma once

#include <iostream>
#include <concepts>
#include <typeinfo>
#include <exception>
#include <stdexcept>

namespace fatpound::linkedlist
{
    template <std::totally_ordered T>
    class DoublyLL
    {
    public:
        DoublyLL() = default;
        virtual ~DoublyLL() noexcept
        {
            Delete_();
        }
        DoublyLL(const DoublyLL<T>& src) = delete;
        DoublyLL(DoublyLL<T>&& src) noexcept
            :
            list_(std::exchange(src.list_, nullptr)),
            end_(std::exchange(src.end_, nullptr)),
            item_count_(std::exchange(src.item_count_, 0u))
        {

        }
        DoublyLL<T>& operator = (const DoublyLL<T>& src) = delete;
        DoublyLL<T>& operator = (DoublyLL<T>&& src) noexcept
        {
            Delete_();

            if (this != std::addressof(src) && typeid(src) == typeid(*this) && src.list_ != nullptr)
            {
                list_ = std::exchange(src.list_, nullptr);
                end_ = std::exchange(src.end_, nullptr);

                item_count_ = std::exchange(src.item_count_, 0u);
            }

            return *this;
        }


    public:
        virtual bool Contains(T item) const
        {
            return Find_(item) == nullptr
                ? false
                : true
                ;
        }

        virtual void Add(T new_item)
        {
            Node* new_part = new Node(new_item);

            ++item_count_;

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
        virtual void AddOrdered(T new_item)
        {
            Node* new_part = new Node(new_item);

            ++item_count_;

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

            Node* temp = list_;

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
        virtual void Reverse()
        {
            if (list_ == nullptr)
            {
                return;
            }

            if (this->item_count_ < 2u)
            {
                return;
            }

            Node* temp = list_;

            while (temp->next != nullptr)
            {
                std::swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            list_ = temp;
        }
        virtual void Print() const
        {
            if (list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty DoublyLL!");
            }

            Node* temp = list_;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != nullptr);

            std::cout << '\n';
        }


    protected:
        struct Node
        {
            Node* prev = nullptr;
            Node* next = nullptr;

            T item;

            Node(T new_item)
                :
                item{ new_item }
            {}
        };


    protected:
        virtual DoublyLL<T>::Node* Find_(T item) const
        {
            if (item_count_ == 0u)
            {
                return nullptr;
            }

            if (item_count_ == 1u)
            {
                return list_->item == item
                    ? list_
                    : nullptr
                    ;
            }

            Node* temp = list_;

            for (size_t i = 0u; i < item_count_; ++i)
            {
                if (temp->item == item)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }

        virtual void Delete_()
        {
            if (list_ == nullptr)
            {
                return;
            }

            Node* ex = list_;
            Node* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != nullptr);

            list_ = nullptr;
            end_ = nullptr;

            item_count_ = 0u;
        }


    protected:
        Node* list_ = nullptr;
        Node* end_  = nullptr;
        
        size_t item_count_ = 0u;


    private:
    };
}