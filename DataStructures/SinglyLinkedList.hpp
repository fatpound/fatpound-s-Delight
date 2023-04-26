#pragma once

#include <iostream>

using namespace std;

template <typename T>
class SinglyLinkedList
{
private:
    class SinglyLinkedList_node
    {
    private:


    protected:


    public:
        SinglyLinkedList_node* next = NULL;
        T item;

        SinglyLinkedList_node();
        ~SinglyLinkedList_node();
        SinglyLinkedList_node(T new_item);
    };


    void connect_private(SinglyLinkedList<T>& second);
    void connect_sorted_private(SinglyLinkedList_node* node);
    int item_count = 0;
    bool is_circular = false;


protected:


public:
    SinglyLinkedList_node* list = NULL;

    SinglyLinkedList();
    ~SinglyLinkedList();
    SinglyLinkedList(bool set_circular);

    void add(T new_item);
    void add_sorted(T new_item);
    void combine(SinglyLinkedList<T>& second);
    void combine_sorted(SinglyLinkedList<T>& second);
    void reverse();
    void list_all();

    SinglyLinkedList_node* go_to_index(int index);
};

template <typename T> SinglyLinkedList<T>::SinglyLinkedList_node::SinglyLinkedList_node()
{

}
template <typename T> SinglyLinkedList<T>::SinglyLinkedList_node::~SinglyLinkedList_node()
{

}
template <typename T> SinglyLinkedList<T>::SinglyLinkedList_node::SinglyLinkedList_node(T new_item)
{
    this->item = new_item;
}

template <typename T> SinglyLinkedList<T>::SinglyLinkedList()
{
    
}
template <typename T> SinglyLinkedList<T>::~SinglyLinkedList()
{

}
template <typename T> SinglyLinkedList<T>::SinglyLinkedList(bool set_circular)
{
    this->is_circular = set_circular;
}

template <typename T> void SinglyLinkedList<T>::connect_private(SinglyLinkedList<T>& second)
{
    SinglyLinkedList_node* end = this->go_to_index(this->item_count - 1);

    end->next = second.list;

    if (this->is_circular)
    {
        SinglyLinkedList_node* second_end = second.go_to_index(second.item_count - 1);

        second_end->next = this->list;
    }
}
template <typename T> void SinglyLinkedList<T>::connect_sorted_private(SinglyLinkedList<T>::SinglyLinkedList_node* node)
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

        if (this->is_circular)
        {
            this->go_to_index(this->item_count - 1)->next = node;
        }

        return;
    }

    SinglyLinkedList<T>::SinglyLinkedList_node* temp = this->list;
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? temp : NULL;

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
    
    if (this->is_circular)
    {
        node->next = start;
    }
    else
        node->next = NULL;
}

template <typename T> void SinglyLinkedList<T>::add(T new_item)
{
    SinglyLinkedList<T>::SinglyLinkedList_node* new_part = new SinglyLinkedList_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;
        
        if (this->is_circular)
        {
            new_part->next = this->list;
        }

        return;
    }
    
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? this->list : NULL;
    SinglyLinkedList<T>::SinglyLinkedList_node* end = this->go_to_index(this->item_count - 2);

    end->next = new_part;

    if (this->is_circular)
    {
        new_part->next = this->list;
    }
}
template <typename T> void SinglyLinkedList<T>::add_sorted(T new_item)
{
    SinglyLinkedList<T>::SinglyLinkedList_node* new_part = new SinglyLinkedList_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;

        if (this->is_circular)
        {
            new_part->next = this->list;
        }

        return;
    }

    if (new_item < this->list->item)
    {
        new_part->next = this->list;
        this->list = new_part;

        if (this->is_circular)
        {
            SinglyLinkedList<T>::SinglyLinkedList_node* end = this->go_to_index(this->item_count - 1);

            end->next = new_part;
        }

        return;
    }

    SinglyLinkedList<T>::SinglyLinkedList_node* temp = this->list;
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? temp : NULL;

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
    
    if (this->is_circular)
    {
        new_part->next = start;
    }
}
template <typename T> void SinglyLinkedList<T>::combine(SinglyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    if (this->is_circular != second.is_circular)
        return;

    this->connect_private(second);
    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::combine_sorted(SinglyLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    if (this->is_circular != second.is_circular)
        return;

    SinglyLinkedList<T>::SinglyLinkedList_node* temp = second.list;
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? temp : NULL;

    do
    {
        SinglyLinkedList<T>::SinglyLinkedList_node* temp2 = temp->next;

        this->connect_sorted_private(temp);
        temp = temp2;
    }
    while (temp != start);

    this->item_count += second.item_count;
}
template <typename T> void SinglyLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    SinglyLinkedList<T>::SinglyLinkedList_node* t;
    SinglyLinkedList<T>::SinglyLinkedList_node* a = NULL;
    SinglyLinkedList<T>::SinglyLinkedList_node* x;
    
    SinglyLinkedList<T>::SinglyLinkedList_node* temp = this->list;
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? temp : NULL;

    while (1)
    {
        t = temp->next;
        temp->next = a;
        a = t;
        x = temp;

        temp = t->next;
        t->next = x;

        if (temp == start)
        {
            if (this->is_circular)
            {
                start->next = t;
            }

            this->list = t;

            return;
        }

        if (temp->next == start)
        {
            if (this->is_circular)
            {
                start->next = temp;
            }

            temp->next = t;
            this->list = temp;

            return;
        }
    }

    if (this->is_circular)
    {
        start->next = temp;
    }
}
template <typename T> void SinglyLinkedList<T>::list_all()
{
    if (this->list == NULL)
        return;

    SinglyLinkedList<T>::SinglyLinkedList_node* temp = this->list;
    SinglyLinkedList<T>::SinglyLinkedList_node* start = this->is_circular ? temp : NULL;
    
    do
    {
        cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != start);

    cout << '\n';
}

template <typename T> typename SinglyLinkedList<T>::SinglyLinkedList_node* SinglyLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    SinglyLinkedList<T>::SinglyLinkedList_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}