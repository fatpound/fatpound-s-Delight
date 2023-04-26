#pragma once

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
    class DoublyLinkedList_node
    {
    private:


    protected:


    public:
        DoublyLinkedList_node* prev = NULL;
        DoublyLinkedList_node* next = NULL;
        T item;

        DoublyLinkedList_node();
        ~DoublyLinkedList_node();
        DoublyLinkedList_node(T new_item);
    };


    void connect_private(DoublyLinkedList<T>& second);
    void connect_sorted_private(DoublyLinkedList_node* node);
    int item_count = 0;
    bool is_circular = false;


protected:


public:
    DoublyLinkedList_node* list = NULL;

    void add(T new_item);
    void add_sorted(T new_item);
    void combine(DoublyLinkedList<T>& second);
    void combine_sorted(DoublyLinkedList<T>& second);
    void reverse();
    void list_all();

    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(bool set_circular);

    DoublyLinkedList_node* go_to_index(int index);
};

template <typename T> DoublyLinkedList<T>::DoublyLinkedList_node::DoublyLinkedList_node()
{

}
template <typename T> DoublyLinkedList<T>::DoublyLinkedList_node::~DoublyLinkedList_node()
{

}
template <typename T> DoublyLinkedList<T>::DoublyLinkedList_node::DoublyLinkedList_node(T new_item)
{
    this->item = new_item;
}

template <typename T> void DoublyLinkedList<T>::connect_private(DoublyLinkedList<T>& second)
{
    DoublyLinkedList_node* end = this->go_to_index(this->item_count - 1);

    second.list->prev = end;
    end->next = second.list;

    if (this->is_circular)
    {
        DoublyLinkedList_node* second_end = second.go_to_index(second.item_count - 1);

        this->list->prev = second_end;
        second_end->next = this->list;
    }
}
template <typename T> void DoublyLinkedList<T>::connect_sorted_private(DoublyLinkedList<T>::DoublyLinkedList_node* node)
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

        if (this->is_circular)
        {
            DoublyLinkedList<T>::DoublyLinkedList_node* end = this->go_to_index(this->item_count - 1);

            node->prev = end;
            end->next = node;
        }

        this->list = node;

        return;
    }

    DoublyLinkedList<T>::DoublyLinkedList_node* temp = this->list;
    DoublyLinkedList<T>::DoublyLinkedList_node* start = this->is_circular ? temp : NULL;

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

    if (this->is_circular)
    {
        node->next = start;
        start->prev = node;
    }
    else
        node->next = NULL;
}

template <typename T> DoublyLinkedList<T>::DoublyLinkedList()
{

}
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList()
{

}
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(bool set_circular)
{
    this->is_circular = set_circular;
}

template <typename T> void DoublyLinkedList<T>::add(T new_item)
{
    DoublyLinkedList<T>::DoublyLinkedList_node* new_part = new DoublyLinkedList_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        if (this->is_circular)
        {
            new_part->prev = new_part;
            new_part->next = new_part;
        }

        this->list = new_part;

        return;
    }

    DoublyLinkedList<T>::DoublyLinkedList_node* start = this->is_circular ? this->list : NULL;
    DoublyLinkedList<T>::DoublyLinkedList_node* end = this->go_to_index(this->item_count - 2);

    end->next = new_part;
    new_part->prev = end;

    if (this->is_circular)
    {
        new_part->next = start;
        start->prev = new_part;
    }
}
template <typename T> void DoublyLinkedList<T>::add_sorted(T new_item)
{
    DoublyLinkedList<T>::DoublyLinkedList_node* new_part = new DoublyLinkedList_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        if (this->is_circular)
        {
            new_part->prev = new_part;
            new_part->next = new_part;
        }

        this->list = new_part;

        return;
    }

    if (new_item < this->list->item)
    {
        new_part->next = this->list;
        this->list->prev = new_part;
        this->list = new_part;

        if (this->is_circular)
        {
            DoublyLinkedList<T>::DoublyLinkedList_node* end = this->go_to_index(this->item_count - 1);

            end->next = this->list;
            this->list->prev = end;
        }
        
        return;
    }

    DoublyLinkedList<T>::DoublyLinkedList_node* temp = this->list;
    DoublyLinkedList<T>::DoublyLinkedList_node* start = this->is_circular ? temp : NULL;

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

    if (this->is_circular)
    {
        new_part->next = start;
        start->prev = new_part;
    }
}
template <typename T> void DoublyLinkedList<T>::combine(DoublyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    if (this->is_circular != second.is_circular)
        return;

    this->connect_private(second);
    this->item_count += second.item_count;
}
template <typename T> void DoublyLinkedList<T>::combine_sorted(DoublyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    if (this->is_circular != second.is_circular)
        return;

    DoublyLinkedList<T>::DoublyLinkedList_node* temp = second.list;
    DoublyLinkedList<T>::DoublyLinkedList_node* start = this->is_circular ? temp : NULL;

    do
    {
        DoublyLinkedList<T>::DoublyLinkedList_node* temp2 = temp->next;

        this->connect_sorted_private(temp);
        temp = temp2;
    }
    while (temp != start);

    this->item_count += second.item_count;
}
template <typename T> void DoublyLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    DoublyLinkedList<T>::DoublyLinkedList_node* temp = this->list;

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
    DoublyLinkedList<T>::DoublyLinkedList_node* temp = this->list;
    DoublyLinkedList<T>::DoublyLinkedList_node* start = this->is_circular ? temp : NULL;

    do
    {
        cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != start);

    cout << '\n';
}

template <typename T> typename DoublyLinkedList<T>::DoublyLinkedList_node* DoublyLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    DoublyLinkedList<T>::DoublyLinkedList_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}