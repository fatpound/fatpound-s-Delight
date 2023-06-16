#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace linkedlist
    {
        template <typename T>
        class DoublyLL
        {
        private:
            class node
            {
            private:


            protected:


            public:
                DoublyLL<T>::node* prev = nullptr;
                DoublyLL<T>::node* next = nullptr;
                T item;

                node();
                ~node();
                node(T new_item);
            };

            DoublyLL<T>::node* list = nullptr;
            int item_count = 0;

            void connect(DoublyLL<T>& second);
            void connect_sorted(DoublyLL<T>::node* node);

            DoublyLL<T>::node* go_to_index(int index);


        protected:


        public:
            void add(T new_item);
            void add_sorted(T new_item);
            void combine(DoublyLL<T>& second);
            void combine_sorted(DoublyLL<T>& second);
            void reverse();
            void list_all();

            DoublyLL();
            ~DoublyLL();
        };

        template <typename T> DoublyLL<T>::node::node()
        {

        }
        template <typename T> DoublyLL<T>::node::~node()
        {

        }
        template <typename T> DoublyLL<T>::node::node(T new_item)
        {
            this->item = new_item;
        }

        template <typename T> void DoublyLL<T>::connect(DoublyLL<T>& second)
        {
            DoublyLL<T>::node* end = this->go_to_index(this->item_count - 1);

            second.list->prev = end;
            end->next = second.list;
        }
        template <typename T> void DoublyLL<T>::connect_sorted(DoublyLL<T>::node* node)
        {
            if (this->list == nullptr)
            {
                this->list = node;
                return;
            }

            if (node->item < this->list->item)
            {
                node->next = this->list;
                this->list->prev = node;
                this->list = node;

                return;
            }

            DoublyLL<T>::node* temp = this->list;

            while (temp->next != nullptr)
            {
                if (temp->item <= node->item && node->item <= temp->next->item)
                {
                    node->next = temp->next;
                    node->prev = temp;
                    temp->next->prev = node;
                    temp->next = node;

                    return;
                }

                temp = temp->next;
            }

            temp->next = node;
            node->prev = temp;
            node->next = nullptr;
        }
        template <typename T> typename DoublyLL<T>::node* DoublyLL<T>::go_to_index(int index)
        {
            if (index >= this->item_count)
                return nullptr;

            DoublyLL<T>::node* temp = this->list;

            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }

            return temp;
        }

        template <typename T> DoublyLL<T>::DoublyLL()
        {

        }
        template <typename T> DoublyLL<T>::~DoublyLL()
        {

        }

        template <typename T> void DoublyLL<T>::add(T new_item)
        {
            DoublyLL<T>::node* new_part = new DoublyLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;

                return;
            }

            DoublyLL<T>::node* end = this->go_to_index(this->item_count - 2);

            end->next = new_part;
            new_part->prev = end;
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
        template <typename T> void DoublyLL<T>::combine(DoublyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->connect(second);
            this->item_count += second.item_count;
        }
        template <typename T> void DoublyLL<T>::combine_sorted(DoublyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            DoublyLL<T>::node* temp = second.list;

            do
            {
                DoublyLL<T>::node* temp2 = temp->next;

                this->connect_sorted(temp);
                temp = temp2;
            } while (temp != nullptr);

            this->item_count += second.item_count;
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
        template <typename T> void DoublyLL<T>::list_all()
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
}