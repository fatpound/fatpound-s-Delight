#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace linkedlist
    {
        template <typename T>
        class SinglyCircularLL
        {
        private:
            class node
            {
            private:


            protected:


            public:
                SinglyCircularLL<T>::node* next = nullptr;
                T item;

                node();
                ~node();
                node(T new_item);
            };

            SinglyCircularLL<T>::node* list = nullptr;
            int item_count = 0;

            void connect(SinglyCircularLL<T>& second);
            void connect_sorted(SinglyCircularLL<T>::node* node);

            SinglyCircularLL<T>::node* go_to_index(int index);


        protected:


        public:
            SinglyCircularLL();
            ~SinglyCircularLL();

            void add(T new_item);
            void add_sorted(T new_item);
            void combine(SinglyCircularLL<T>& second);
            void combine_sorted(SinglyCircularLL<T>& second);
            void reverse();
            void list_all();
        };

        template <typename T> SinglyCircularLL<T>::node::node()
        {

        }
        template <typename T> SinglyCircularLL<T>::node::~node()
        {

        }
        template <typename T> SinglyCircularLL<T>::node::node(T new_item)
        {
            this->item = new_item;
        }

        template <typename T> SinglyCircularLL<T>::SinglyCircularLL()
        {

        }
        template <typename T> SinglyCircularLL<T>::~SinglyCircularLL()
        {

        }

        template <typename T> void SinglyCircularLL<T>::connect(SinglyCircularLL<T>& second)
        {
            SinglyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);
            end->next = second.list;

            SinglyCircularLL<T>::node* second_end = second.go_to_index(second.item_count - 1);
            second_end->next = this->list;
        }
        template <typename T> void SinglyCircularLL<T>::connect_sorted(SinglyCircularLL<T>::node* node)
        {
            if (this->list == nullptr)
            {
                this->list = node;
                return;
            }

            if (node->item < this->list->item)
            {
                node->next = this->list;
                this->list = node;

                SinglyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);
                end->next = node;

                return;
            }

            SinglyCircularLL<T>::node* temp = this->list;
            SinglyCircularLL<T>::node* start = temp;

            while (temp->next != start)
            {
                if (temp->item <= node->item && node->item <= temp->next->item)
                {
                    node->next = temp->next;
                    temp->next = node;

                    return;
                }

                temp = temp->next;
            }

            temp->next = node;
            node->next = start;
        }
        template <typename T> typename SinglyCircularLL<T>::node* SinglyCircularLL<T>::go_to_index(int index)
        {
            if (index >= this->item_count)
                return nullptr;

            SinglyCircularLL<T>::node* temp = this->list;

            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }

            return temp;
        }

        template <typename T> void SinglyCircularLL<T>::add(T new_item)
        {
            SinglyCircularLL<T>::node* new_part = new SinglyCircularLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                new_part->next = this->list;

                return;
            }

            SinglyCircularLL<T>::node* end = this->go_to_index(this->item_count - 2);
            end->next = new_part;
            new_part->next = this->list;
        }
        template <typename T> void SinglyCircularLL<T>::add_sorted(T new_item)
        {
            SinglyCircularLL<T>::node* new_part = new SinglyCircularLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                new_part->next = this->list;

                return;
            }

            if (new_item < this->list->item)
            {
                new_part->next = this->list;
                this->list = new_part;

                SinglyCircularLL<T>::node* end = this->go_to_index(this->item_count - 1);
                end->next = new_part;

                return;
            }

            SinglyCircularLL<T>::node* temp = this->list;
            SinglyCircularLL<T>::node* start = temp;

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
        template <typename T> void SinglyCircularLL<T>::combine(SinglyCircularLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->connect(second);
            this->item_count += second.item_count;
        }
        template <typename T> void SinglyCircularLL<T>::combine_sorted(SinglyCircularLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            SinglyCircularLL<T>::node* temp = second.list;
            SinglyCircularLL<T>::node* start = temp;

            do
            {
                SinglyCircularLL<T>::node* temp2 = temp->next;

                this->connect_sorted(temp);
                temp = temp2;
            } while (temp != start);

            this->item_count += second.item_count;
        }
        template <typename T> void SinglyCircularLL<T>::reverse()
        {
            if (this->list == nullptr)
                return;

            SinglyCircularLL<T>::node* t;
            SinglyCircularLL<T>::node* a = nullptr;
            SinglyCircularLL<T>::node* x;

            SinglyCircularLL<T>::node* temp = this->list;
            SinglyCircularLL<T>::node* start = temp;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                temp = t->next;
                t->next = x;

                if (temp == start)
                {
                    start->next = t;

                    this->list = t;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = t;
                    this->list = temp;

                    return;
                }
            }

            start->next = temp;
        }
        template <typename T> void SinglyCircularLL<T>::list_all()
        {
            if (this->list == nullptr)
                return;

            SinglyCircularLL<T>::node* temp = this->list;
            SinglyCircularLL<T>::node* start = temp;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            } while (temp != start);

            std::cout << '\n';
        }
    }
}