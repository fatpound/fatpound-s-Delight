#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace linkedlist
    {
        template <typename T>
        class SinglyLL
        {
        private:
            class node
            {
            private:


            protected:


            public:
                SinglyLL<T>::node* next = nullptr;
                T item;

                node();
                ~node();
                node(T new_item);
            };

            SinglyLL<T>::node* list = nullptr;
            int item_count = 0;

            void connect(SinglyLL<T>& second);
            void connect_sorted(SinglyLL<T>::node* node);

            SinglyLL<T>::node* go_to_index(int index);


        protected:


        public:
            SinglyLL();
            ~SinglyLL();

            void add(T new_item);
            void add_sorted(T new_item);
            void combine(SinglyLL<T>& second);
            void combine_sorted(SinglyLL<T>& second);
            void reverse();
            void list_all();
        };

        template <typename T> SinglyLL<T>::node::node()
        {

        }
        template <typename T> SinglyLL<T>::node::~node()
        {

        }
        template <typename T> SinglyLL<T>::node::node(T new_item)
        {
            this->item = new_item;
        }

        template <typename T> SinglyLL<T>::SinglyLL()
        {

        }
        template <typename T> SinglyLL<T>::~SinglyLL()
        {

        }

        template <typename T> void SinglyLL<T>::connect(SinglyLL<T>& second)
        {
            SinglyLL<T>::node* end = this->go_to_index(this->item_count - 1);
            end->next = second.list;
        }
        template <typename T> void SinglyLL<T>::connect_sorted(SinglyLL<T>::node* node)
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

                return;
            }

            SinglyLL<T>::node* temp = this->list;

            while (temp->next != nullptr)
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
            node->next = nullptr;
        }
        template <typename T> typename SinglyLL<T>::node* SinglyLL<T>::go_to_index(int index)
        {
            if (index >= this->item_count)
                return nullptr;

            SinglyLL<T>::node* temp = this->list;

            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }

            return temp;
        }

        template <typename T> void SinglyLL<T>::add(T new_item)
        {
            SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                return;
            }

            SinglyLL<T>::node* end = this->go_to_index(this->item_count - 2);
            end->next = new_part;
        }
        template <typename T> void SinglyLL<T>::add_sorted(T new_item)
        {
            SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);
            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                return;
            }

            if (new_item < this->list->item)
            {
                new_part->next = this->list;
                this->list = new_part;

                return;
            }

            SinglyLL<T>::node* temp = this->list;

            while (temp->next != nullptr)
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
        }
        template <typename T> void SinglyLL<T>::combine(SinglyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->connect(second);
            this->item_count += second.item_count;
        }
        template <typename T> void SinglyLL<T>::combine_sorted(SinglyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            SinglyLL<T>::node* temp = second.list;

            do
            {
                SinglyLL<T>::node* temp2 = temp->next;

                this->connect_sorted(temp);
                temp = temp2;
            } while (temp != nullptr);

            this->item_count += second.item_count;
        }
        template <typename T> void SinglyLL<T>::reverse()
        {
            if (this->list == nullptr)
                return;

            SinglyLL<T>::node* t;
            SinglyLL<T>::node* a = nullptr;
            SinglyLL<T>::node* x;

            SinglyLL<T>::node* temp = this->list;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                temp = t->next;
                t->next = x;

                if (temp == nullptr)
                {
                    this->list = t;
                    return;
                }

                if (temp->next == nullptr)
                {
                    temp->next = t;
                    this->list = temp;

                    return;
                }
            }
        }
        template <typename T> void SinglyLL<T>::list_all()
        {
            if (this->list == nullptr)
                return;

            SinglyLL<T>::node* temp = this->list;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            } while (temp != nullptr);

            std::cout << '\n';
        }
    }
}