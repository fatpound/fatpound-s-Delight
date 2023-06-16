#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace linkedlist
    {
        template <typename T>
        class DoublyCircularLL
        {
        private:
            class node
            {
            private:


            protected:


            public:
                DoublyCircularLL<T>::node* prev = nullptr;
                DoublyCircularLL<T>::node* next = nullptr;
                T item;

                node();
                ~node();
                node(T new_item);
            };

            DoublyCircularLL<T>::node* list = nullptr;
            int item_count = 0;

            void connect(DoublyCircularLL<T>& second);
            void connect_sorted(DoublyCircularLL<T>::node* node);

            DoublyCircularLL<T>::node* go_to_index(int index);


        protected:


        public:
            void add(T new_item);
            void add_sorted(T new_item);
            void combine(DoublyCircularLL<T>& second);
            void combine_sorted(DoublyCircularLL<T>& second);
            void reverse();
            void list_all();

            DoublyCircularLL();
            ~DoublyCircularLL();
        };

        template <typename T> DoublyCircularLL<T>::node::node()
        {

        }
        template <typename T> DoublyCircularLL<T>::node::~node()
        {

        }
        template <typename T> DoublyCircularLL<T>::node::node(T new_item)
        {
            this->item = new_item;
        }

        template <typename T> void DoublyCircularLL<T>::connect(DoublyCircularLL<T>& second)
        {
            DoublyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);

            second.list->prev = end;
            end->next = second.list;

            DoublyCircularLL<T>::node* second_end = second.go_to_index(second.item_count - 1);

            this->list->prev = second_end;
            second_end->next = this->list;
        }
        template <typename T> void DoublyCircularLL<T>::connect_sorted(DoublyCircularLL<T>::node* node)
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

                DoublyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);

                node->prev = end;
                end->next = node;

                this->list = node;

                return;
            }

            DoublyCircularLL<T>::node* temp = this->list;
            DoublyCircularLL<T>::node* start = temp;

            while (temp->next != start)
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

            node->next = start;
            start->prev = node;
        }
        template <typename T> typename DoublyCircularLL<T>::node* DoublyCircularLL<T>::go_to_index(int index)
        {
            if (index >= this->item_count)
                return nullptr;

            DoublyCircularLL<T>::node* temp = this->list;

            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }

            return temp;
        }

        template <typename T> DoublyCircularLL<T>::DoublyCircularLL()
        {

        }
        template <typename T> DoublyCircularLL<T>::~DoublyCircularLL()
        {

        }

        template <typename T> void DoublyCircularLL<T>::add(T new_item)
        {
            DoublyCircularLL<T>::node* new_part = new DoublyCircularLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;

                this->list = new_part;

                return;
            }

            DoublyCircularLL<T>::node* start = this->list;
            DoublyCircularLL<T>::node* end = this->go_to_index(this->item_count - 2);

            end->next = new_part;
            new_part->prev = end;

            new_part->next = start;
            start->prev = new_part;
        }
        template <typename T> void DoublyCircularLL<T>::add_sorted(T new_item)
        {
            DoublyCircularLL<T>::node* new_part = new DoublyCircularLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                this->list = new_part;

                return;
            }

            if (new_item < this->list->item)
            {
                new_part->next = this->list;
                this->list->prev = new_part;
                this->list = new_part;

                DoublyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);

                end->next = this->list;
                this->list->prev = end;

                return;
            }

            DoublyCircularLL<T>::node* temp = this->list;
            DoublyCircularLL<T>::node* start = temp;

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
        template <typename T> void DoublyCircularLL<T>::combine(DoublyCircularLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->connect(second);
            this->item_count += second.item_count;
        }
        template <typename T> void DoublyCircularLL<T>::combine_sorted(DoublyCircularLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            DoublyCircularLL<T>::node* temp = second.list;
            DoublyCircularLL<T>::node* start = temp;

            do
            {
                DoublyCircularLL<T>::node* temp2 = temp->next;

                this->connect_sorted(temp);
                temp = temp2;
            } while (temp != start);

            this->item_count += second.item_count;
        }
        template <typename T> void DoublyCircularLL<T>::reverse()
        {
            if (this->list == nullptr)
                return;

            DoublyCircularLL<T>::node* temp = this->list;
            DoublyCircularLL<T>::node* start = this->list;

            while (temp->next != start)
            {
                swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            this->list = temp;
        }
        template <typename T> void DoublyCircularLL<T>::list_all()
        {
            DoublyCircularLL<T>::node* temp = this->list;
            DoublyCircularLL<T>::node* start = temp;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            } while (temp != start);

            std::cout << '\n';
        }
    }
}