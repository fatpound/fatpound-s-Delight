#pragma once

#include <iostream>

using namespace std;

template <typename T>
class SinglyLinkedList
{
private:
    class SinglyLL_node
    {
    private:


    protected:


    public:
        SinglyLL_node* next = NULL;
        T item;

        SinglyLL_node();
        ~SinglyLL_node();
        SinglyLL_node(T new_item);
    };

    SinglyLL_node* list = NULL;
    int item_count = 0;

    void connect(SinglyLinkedList<T>& second);
    void connect_sorted(SinglyLL_node* node);

    SinglyLL_node* go_to_index(int index);


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

template <typename T> SinglyLinkedList<T>::SinglyLL_node::SinglyLL_node()
{

}
template <typename T> SinglyLinkedList<T>::SinglyLL_node::~SinglyLL_node()
{

}
template <typename T> SinglyLinkedList<T>::SinglyLL_node::SinglyLL_node(T new_item)
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
    SinglyLL_node* end = this->go_to_index(this->item_count - 1);
    end->next = second.list;
}
template <typename T> void SinglyLinkedList<T>::connect_sorted(SinglyLinkedList<T>::SinglyLL_node* node)
{
    if (this->list == NULL)
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

    SinglyLinkedList<T>::SinglyLL_node* temp = this->list;

    while (temp->next != NULL)
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
    node->next = NULL;
}
template <typename T> typename SinglyLinkedList<T>::SinglyLL_node* SinglyLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    SinglyLinkedList<T>::SinglyLL_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T> void SinglyLinkedList<T>::add(T new_item)
{
    SinglyLinkedList<T>::SinglyLL_node* new_part = new SinglyLinkedList<T>::SinglyLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;
        return;
    }

    SinglyLinkedList<T>::SinglyLL_node* end = this->go_to_index(this->item_count - 2);
    end->next = new_part;
}
template <typename T> void SinglyLinkedList<T>::add_sorted(T new_item)
{
    SinglyLinkedList<T>::SinglyLL_node* new_part = new SinglyLinkedList<T>::SinglyLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
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

    SinglyLinkedList<T>::SinglyLL_node* temp = this->list;

    while (temp->next != NULL)
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
    if (this->list == NULL || second.list == NULL)
        return;

    this->connect(second);
    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::combine_sorted(SinglyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    SinglyLinkedList<T>::SinglyLL_node* temp = second.list;

    do
    {
        SinglyLinkedList<T>::SinglyLL_node* temp2 = temp->next;

        this->connect_sorted(temp);
        temp = temp2;
    }
    while (temp != NULL);

    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    SinglyLinkedList<T>::SinglyLL_node* t;
    SinglyLinkedList<T>::SinglyLL_node* a = NULL;
    SinglyLinkedList<T>::SinglyLL_node* x;

    SinglyLinkedList<T>::SinglyLL_node* temp = this->list;

    while (1)
    {
        t = temp->next;
        temp->next = a;
        a = t;
        x = temp;

        temp = t->next;
        t->next = x;

        if (temp == NULL)
        {
            this->list = t;
            return;
        }

        if (temp->next == NULL)
        {
            temp->next = t;
            this->list = temp;

            return;
        }
    }
}
template <typename T> void SinglyLinkedList<T>::list_all()
{
    if (this->list == NULL)
        return;

    SinglyLinkedList<T>::SinglyLL_node* temp = this->list;

    do
    {
        cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != NULL);

    cout << '\n';
}