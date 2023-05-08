#pragma once

#include <iostream>

using namespace std;

template <typename T>
class DoublyCircularLinkedList
{
private:
    class DoublyCircularLL_node
    {
    private:


    protected:


    public:
        DoublyCircularLL_node* prev = NULL;
        DoublyCircularLL_node* next = NULL;
        T item;

        DoublyCircularLL_node();
        ~DoublyCircularLL_node();
        DoublyCircularLL_node(T new_item);
    };

    DoublyCircularLL_node* list = NULL;
    int item_count = 0;

    void connect(DoublyCircularLinkedList<T>& second);
    void connect_sorted(DoublyCircularLL_node* node);

    DoublyCircularLL_node* go_to_index(int index);


protected:


public:
    void add(T new_item);
    void add_sorted(T new_item);
    void combine(DoublyCircularLinkedList<T>& second);
    void combine_sorted(DoublyCircularLinkedList<T>& second);
    void reverse();
    void list_all();

    DoublyCircularLinkedList();
    ~DoublyCircularLinkedList();
};

template <typename T> DoublyCircularLinkedList<T>::DoublyCircularLL_node::DoublyCircularLL_node()
{

}
template <typename T> DoublyCircularLinkedList<T>::DoublyCircularLL_node::~DoublyCircularLL_node()
{

}
template <typename T> DoublyCircularLinkedList<T>::DoublyCircularLL_node::DoublyCircularLL_node(T new_item)
{
    this->item = new_item;
}

template <typename T> void DoublyCircularLinkedList<T>::connect(DoublyCircularLinkedList<T>& second)
{
    DoublyCircularLL_node* end = this->go_to_index(this->item_count - 1);

    second.list->prev = end;
    end->next = second.list;

    DoublyCircularLL_node* second_end = second.go_to_index(second.item_count - 1);

    this->list->prev = second_end;
    second_end->next = this->list;
}
template <typename T> void DoublyCircularLinkedList<T>::connect_sorted(DoublyCircularLinkedList<T>::DoublyCircularLL_node* node)
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

        DoublyCircularLinkedList<T>::DoublyCircularLL_node* end = this->go_to_index(this->item_count - 1);

        node->prev = end;
        end->next = node;

        this->list = node;

        return;
    }

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = this->list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = temp;

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
template <typename T> typename DoublyCircularLinkedList<T>::DoublyCircularLL_node* DoublyCircularLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T> DoublyCircularLinkedList<T>::DoublyCircularLinkedList()
{

}
template <typename T> DoublyCircularLinkedList<T>::~DoublyCircularLinkedList()
{

}

template <typename T> void DoublyCircularLinkedList<T>::add(T new_item)
{
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* new_part = new DoublyCircularLinkedList<T>::DoublyCircularLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        new_part->prev = new_part;
        new_part->next = new_part;

        this->list = new_part;

        return;
    }

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = this->list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* end = this->go_to_index(this->item_count - 2);

    end->next = new_part;
    new_part->prev = end;

    new_part->next = start;
    start->prev = new_part;
}
template <typename T> void DoublyCircularLinkedList<T>::add_sorted(T new_item)
{
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* new_part = new DoublyCircularLinkedList<T>::DoublyCircularLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
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

        DoublyCircularLinkedList<T>::DoublyCircularLL_node* end = this->go_to_index(this->item_count - 1);

        end->next = this->list;
        this->list->prev = end;

        return;
    }

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = this->list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = temp;

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
template <typename T> void DoublyCircularLinkedList<T>::combine(DoublyCircularLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    this->connect(second);
    this->item_count += second.item_count;
}
template <typename T> void DoublyCircularLinkedList<T>::combine_sorted(DoublyCircularLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = second.list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = temp;

    do
    {
        DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp2 = temp->next;

        this->connect_sorted(temp);
        temp = temp2;
    }
    while (temp != start);

    this->item_count += second.item_count;
}
template <typename T> void DoublyCircularLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = this->list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = this->list;

    while (temp->next != start)
    {
        swap(temp->prev, temp->next);
        temp = temp->prev;
    }

    swap(temp->prev, temp->next);
    this->list = temp;
}
template <typename T> void DoublyCircularLinkedList<T>::list_all()
{
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* temp = this->list;
    DoublyCircularLinkedList<T>::DoublyCircularLL_node* start = temp;

    do
    {
        cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != start);

    cout << '\n';
}