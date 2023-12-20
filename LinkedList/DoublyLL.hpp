#pragma once

#include <iostream>
#include <concepts>

namespace fatpound::linkedlist
{
    template <std::totally_ordered T>
    class DoublyLL
    {
    public:
        DoublyLL() = default;
        virtual ~DoublyLL() noexcept
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
			end_  = nullptr;

			item_count_ = static_cast<decltype(item_count_)>(0);
        }
        DoublyLL(const DoublyLL<T>& src) = delete;
        DoublyLL(DoublyLL<T>&& src) noexcept
            :
            list_(std::exchange(src.list_, nullptr)),
            end_(std::exchange(src.end_, nullptr)),
            item_count_(std::exchange(src.item_count_, static_cast<decltype(item_count_)>(0)))
        {

        }
        DoublyLL<T>& operator = (const DoublyLL<T>& src) = delete;
        DoublyLL<T>& operator = (DoublyLL<T>&& src) noexcept
        {

			list_ = std::exchange(src.list_, nullptr);
			end_  = std::exchange(src.end_,  nullptr);

            item_count_ = std::exchange(src.item_count_, static_cast<decltype(item_count_)>(0));

            return *this;
        }


    public:
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
        Node* list_ = nullptr;
        Node* end_  = nullptr;
        
        size_t item_count_ = static_cast<size_t>(0);
    };
}