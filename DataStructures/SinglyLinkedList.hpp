#pragma once

#include <iostream>

template <typename T>
class SinglyLinkedList
{
private:
    class node
    {
    private:


    protected:


    public:
        SinglyLinkedList<T>::node* next = nullptr;
        T item;

        node();
        ~node();
        node(T new_item);
    };

    SinglyLinkedList<T>::node* list = nullptr;
    int item_count = 0;

    void connect(SinglyLinkedList<T>& second);
    void connect_sorted(SinglyLinkedList<T>::node* node);

    SinglyLinkedList<T>::node* go_to_index(int index);


protected:


public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    void add(T new_item);
    void add_sorted(T new_item);
    void combine(SinglyLinkedList<T>& second);
    void combine_sorted(SinglyLinkedList<T>& second);
    void reverse();
    void list_all();
};

template <typename T> SinglyLinkedList<T>::node::node()
{

}
template <typename T> SinglyLinkedList<T>::node::~node()
{

}
template <typename T> SinglyLinkedList<T>::node::node(T new_item)
{
    this->item = new_item;
}

template <typename T> SinglyLinkedList<T>::SinglyLinkedList()
{

}
template <typename T> SinglyLinkedList<T>::~SinglyLinkedList()
{

}

template <typename T> void SinglyLinkedList<T>::connect(SinglyLinkedList<T>& second)
{
    SinglyLinkedList<T>::node* end = this->go_to_index(this->item_count - 1);
    end->next = second.list;
}
template <typename T> void SinglyLinkedList<T>::connect_sorted(SinglyLinkedList<T>::node* node)
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

    SinglyLinkedList<T>::node* temp = this->list;

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
template <typename T> typename SinglyLinkedList<T>::node* SinglyLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return nullptr;

    SinglyLinkedList<T>::node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T> void SinglyLinkedList<T>::add(T new_item)
{
    SinglyLinkedList<T>::node* new_part = new SinglyLinkedList<T>::node(new_item);
    this->item_count++;

    if (this->list == nullptr)
    {
        this->list = new_part;
        return;
    }

    SinglyLinkedList<T>::node* end = this->go_to_index(this->item_count - 2);
    end->next = new_part;
}
template <typename T> void SinglyLinkedList<T>::add_sorted(T new_item)
{
    SinglyLinkedList<T>::node* new_part = new SinglyLinkedList<T>::node(new_item);
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

    SinglyLinkedList<T>::node* temp = this->list;

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
template <typename T> void SinglyLinkedList<T>::combine(SinglyLinkedList<T>& second)
{
    if (this->list == nullptr || second.list == nullptr)
        return;

    this->connect(second);
    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::combine_sorted(SinglyLinkedList<T>& second)
{
    if (this->list == nullptr || second.list == nullptr)
        return;

    SinglyLinkedList<T>::node* temp = second.list;

    do
    {
        SinglyLinkedList<T>::node* temp2 = temp->next;

        this->connect_sorted(temp);
        temp = temp2;
    }
    while (temp != nullptr);

    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::reverse()
{
    if (this->list == nullptr)
        return;

    SinglyLinkedList<T>::node* t;
    SinglyLinkedList<T>::node* a = nullptr;
    SinglyLinkedList<T>::node* x;

    SinglyLinkedList<T>::node* temp = this->list;

    while (1)
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
template <typename T> void SinglyLinkedList<T>::list_all()
{
    if (this->list == nullptr)
        return;

    SinglyLinkedList<T>::node* temp = this->list;

    do
    {
        std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != nullptr);

    std::cout << '\n';
}