#pragma once

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
    class DoublyLL_node
    {
    private:


    protected:


    public:
        DoublyLL_node* prev = NULL;
        DoublyLL_node* next = NULL;
        T item;

        DoublyLL_node();
        ~DoublyLL_node();
        DoublyLL_node(T new_item);
    };

    DoublyLL_node* list = NULL;
    int item_count = 0;

    void connect(DoublyLinkedList<T>& second);
    void connect_sorted(DoublyLL_node* node);

    DoublyLL_node* go_to_index(int index);


protected:


public:
    void add(T new_item);
    void add_sorted(T new_item);
    void combine(DoublyLinkedList<T>& second);
    void combine_sorted(DoublyLinkedList<T>& second);
    void reverse();
    void list_all();

    DoublyLinkedList();
    ~DoublyLinkedList();
};

template <typename T> DoublyLinkedList<T>::DoublyLL_node::DoublyLL_node()
{

}
template <typename T> DoublyLinkedList<T>::DoublyLL_node::~DoublyLL_node()
{

}
template <typename T> DoublyLinkedList<T>::DoublyLL_node::DoublyLL_node(T new_item)
{
    this->item = new_item;
}

template <typename T> void DoublyLinkedList<T>::connect(DoublyLinkedList<T>& second)
{
    DoublyLL_node* end = this->go_to_index(this->item_count - 1);

    second.list->prev = end;
    end->next = second.list;
}
template <typename T> void DoublyLinkedList<T>::connect_sorted(DoublyLinkedList<T>::DoublyLL_node* node)
{
    if (this->list == NULL)
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

    DoublyLinkedList<T>::DoublyLL_node* temp = this->list;

    while (temp->next != NULL)
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
    node->next = NULL;
}
template <typename T> typename DoublyLinkedList<T>::DoublyLL_node* DoublyLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    DoublyLinkedList<T>::DoublyLL_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T> DoublyLinkedList<T>::DoublyLinkedList()
{

}
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList()
{

}

template <typename T> void DoublyLinkedList<T>::add(T new_item)
{
    DoublyLinkedList<T>::DoublyLL_node* new_part = new DoublyLinkedList<T>::DoublyLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;

        return;
    }

    DoublyLinkedList<T>::DoublyLL_node* end = this->go_to_index(this->item_count - 2);

    end->next = new_part;
    new_part->prev = end;
}
template <typename T> void DoublyLinkedList<T>::add_sorted(T new_item)
{
    DoublyLinkedList<T>::DoublyLL_node* new_part = new DoublyLinkedList<T>::DoublyLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
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

    DoublyLinkedList<T>::DoublyLL_node* temp = this->list;

    while (temp->next != NULL)
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
template <typename T> void DoublyLinkedList<T>::combine(DoublyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    this->connect(second);
    this->item_count += second.item_count;
}
template <typename T> void DoublyLinkedList<T>::combine_sorted(DoublyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    DoublyLinkedList<T>::DoublyLL_node* temp = second.list;

    do
    {
        DoublyLinkedList<T>::DoublyLL_node* temp2 = temp->next;

        this->connect_sorted(temp);
        temp = temp2;
    }
    while (temp != NULL);

    this->item_count += second.item_count;
}
template <typename T> void DoublyLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    DoublyLinkedList<T>::DoublyLL_node* temp = this->list;

    while (temp->next != NULL)
    {
        swap(temp->prev, temp->next);
        temp = temp->prev;
    }

    swap(temp->prev, temp->next);
    this->list = temp;
}
template <typename T> void DoublyLinkedList<T>::list_all()
{
    DoublyLinkedList<T>::DoublyLL_node* temp = this->list;

    do
    {
        cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != NULL);

    cout << '\n';
}