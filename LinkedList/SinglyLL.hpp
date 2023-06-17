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

                node(T new_item);
            };

            /********************************/
            /*           Variables          */
            /********************************/

            SinglyLL<T>::node* list = nullptr;
            SinglyLL<T>::node* end  = nullptr;

            std::int_fast64_t item_count = 0;
            
            /********************************/
            /*           Functions          */
            /********************************/

            void connect(SinglyLL<T>& second);
            void connect_sorted(SinglyLL<T>::node* node);
            

        protected:


        public:
            ~SinglyLL();

            void add(T new_item);
            void add_sorted(T new_item);
            void combine(SinglyLL<T>& second);
            void combine_sorted(SinglyLL<T>& second);
            void reverse();
            void list_all();
        };

        template <typename T> SinglyLL<T>::node::node(T new_item)
        {
            this->item = new_item;
        }

        template <typename T> SinglyLL<T>::~SinglyLL()
        {

        }

        /********************************/
        /*       Private Functions      */
        /********************************/
        //
        // Return type : void
        //
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

        /********************************/
        /*       Public Functions       */
        /********************************/
        //
        // Return type : void
        //
        template <typename T> void SinglyLL<T>::add(T new_item)
        {
            SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);

            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                this->end  = new_part;

                return;
            }

            this->end->next = new_part;
            this->end       = new_part;
        }
        template <typename T> void SinglyLL<T>::add_sorted(T new_item)
        {
            SinglyLL<T>::node* new_part = new SinglyLL<T>::node(new_item);

            this->item_count++;

            if (this->list == nullptr)
            {
                this->list = new_part;
                this->end  = new_part;

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
            this->end  = new_part;
        }
        template <typename T> void SinglyLL<T>::combine(SinglyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->connect(second);
            this->item_count += second.item_count;

            this->end = second.end;
        }
        template <typename T> void SinglyLL<T>::combine_sorted(SinglyLL<T>& second)
        {
            if (this->list == nullptr || second.list == nullptr)
                return;

            this->item_count += second.item_count;

            if (this->end->item < second.end->item)
                this->end = second.end;

            SinglyLL<T>::node* temp = second.list;

            do
            {
                SinglyLL<T>::node* temp2 = temp->next;

                this->connect_sorted(temp);
                temp = temp2;
            }
            while (temp != nullptr);
        }
        template <typename T> void SinglyLL<T>::reverse()
        {
            if (this->list == nullptr)
                return;

            SinglyLL<T>::node* start_backup = this->list;

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

            this->end = start_backup;
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
            }
            while (temp != nullptr);

            std::cout << '\n';
        }
    }
}
