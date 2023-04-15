#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct SinglyLinkedList
{
	int n;
	struct SinglyLinkedList *next;
}
SINGLY_LINKED_LIST;

typedef struct DoublyLinkedList
{
	struct DoublyLinkedList *prev;
	int n;
	struct DoublyLinkedList *next;
}
DOUBLY_LINKED_LIST;

#define ALLOCATE_SINGLY (SINGLY_LINKED_LIST*) malloc(sizeof(SINGLY_LINKED_LIST))
#define ALLOCATE_DOUBLY (DOUBLY_LINKED_LIST*) malloc(sizeof(DOUBLY_LINKED_LIST))

/* SINGLY */

SINGLY_LINKED_LIST* AddToSinglyLL(SINGLY_LINKED_LIST* list, int num)
{
	SINGLY_LINKED_LIST* new_list = ALLOCATE_SINGLY;
	new_list->n = num;
	new_list->next = NULL;

	if (list == NULL)
	{
		return new_list;
	}

	SINGLY_LINKED_LIST* start = list;

	while (list->next != NULL)
	{
		list = list->next;
	}

	list->next = new_list;

	return start;
}

SINGLY_LINKED_LIST* AddToSinglyLL_Sorted(SINGLY_LINKED_LIST* list, int num)
{
	SINGLY_LINKED_LIST* new_list = ALLOCATE_SINGLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->next = NULL;

		return new_list;
	}

	if (num < list->n)
	{
		new_list->next = list;

		return new_list;
	}

	SINGLY_LINKED_LIST* start = list;

	while (list->next != NULL)
	{
		if (list->n <= num && num <= list->next->n)
		{
			new_list->next = list->next;
			list->next = new_list;

			return start;
		}

		list = list->next;
	}

	list->next = new_list;
	new_list->next = NULL;

	return start;
}

SINGLY_LINKED_LIST* AddToSinglyCircularLL(SINGLY_LINKED_LIST* list, int num)
{
	SINGLY_LINKED_LIST* new_list = ALLOCATE_SINGLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->next = new_list;
		return new_list;
	}

	SINGLY_LINKED_LIST* start = list;

	while (list->next != start)
	{
		list = list->next;
	}

	list->next = new_list;
	new_list->next = start;

	return start;
}

SINGLY_LINKED_LIST* AddToSinglyCircularLL_Sorted(SINGLY_LINKED_LIST* list, int num)
{
	SINGLY_LINKED_LIST* new_list = ALLOCATE_SINGLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->next = new_list;
		return new_list;
	}

	SINGLY_LINKED_LIST* start = list;

	if (num < list->n)
	{
		new_list->next = list;

		while (list->next != start)
		{
			list = list->next;
		}

		list->next = new_list;

		return new_list;
	}

	while (list->next != start)
	{
		if (list->n <= num && num <= list->next->n)
		{
			new_list->next = list->next;
			list->next = new_list;

			return start;
		}

		list = list->next;
	}

	list->next = new_list;
	new_list->next = start;

	return start;
}


SINGLY_LINKED_LIST* ReverseSinglyLL(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* t;
	SINGLY_LINKED_LIST* a = NULL;
	SINGLY_LINKED_LIST* x;

	while (1)
	{
		t = list->next;
		list->next = a;
		a = t;
		x = list;

		list = t->next;
		t->next = x;

		if (list == NULL)
		{
			return t;
		}
		
		if (list->next == NULL)
		{
			list->next = t;
			return temp;
		}
	}

	return list;
}

SINGLY_LINKED_LIST* ReverseSinglyCircularLL(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* start = list;

	SINGLY_LINKED_LIST* t;
	SINGLY_LINKED_LIST* a = start;
	SINGLY_LINKED_LIST* x;

	while (1)
	{
		t = list->next;
		list->next = a;
		a = t;
		x = list;

		list = t->next;
		t->next = x;

		if (list == start)
		{
			start->next = t;
			return t;
		}
		
		if (list->next == start)
		{
			start->next = temp;
			temp->next = t;
			return temp;
		}
	}

	start->next = list;
	return list;
}


SINGLY_LINKED_LIST* CombineSinglyLL(SINGLY_LINKED_LIST* list1, SINGLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToSinglyLL(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

SINGLY_LINKED_LIST* CombineSinglyLL_Sorted(SINGLY_LINKED_LIST* list1, SINGLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToSinglyLL_Sorted(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

SINGLY_LINKED_LIST* CombineSinglyCircularLL(SINGLY_LINKED_LIST* list1, SINGLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToSinglyCircularLL(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

SINGLY_LINKED_LIST* CombineSinglyCircularLL_Sorted(SINGLY_LINKED_LIST* list1, SINGLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToSinglyCircularLL_Sorted(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}


SINGLY_LINKED_LIST* ConvertToSinglyLL(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToSinglyLL(new_list, list->n);

		list = list->next;
	}

	new_list = AddToSinglyLL(new_list, list->n);

	return new_list;
}

SINGLY_LINKED_LIST* ConvertToSinglyLL_Sorted(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToSinglyLL_Sorted(new_list, list->n);

		list = list->next;
	}

	new_list = AddToSinglyLL_Sorted(new_list, list->n);

	return new_list;
}

SINGLY_LINKED_LIST* ConvertToSinglyCircularLL(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToSinglyCircularLL(new_list, list->n);

		list = list->next;
	}

	new_list = AddToSinglyCircularLL(new_list, list->n);

	return new_list;
}

SINGLY_LINKED_LIST* ConvertToSinglyCircularLL_Sorted(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	SINGLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToSinglyCircularLL_Sorted(new_list, list->n);

		list = list->next;
	}

	new_list = AddToSinglyCircularLL_Sorted(new_list, list->n);

	return new_list;
}


SINGLY_LINKED_LIST* GoToIndex_SinglyLL(SINGLY_LINKED_LIST* list, int index)
{
	if (list == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < index; i++)
	{
		if (list->next == NULL)
		{
			return NULL;
		}

		list = list->next;
	}

	return list;
}

/* DOUBLY */

DOUBLY_LINKED_LIST* AddToDoublyLL(DOUBLY_LINKED_LIST* list, int num)
{
	DOUBLY_LINKED_LIST* new_list = ALLOCATE_DOUBLY;
	new_list->n = num;
	new_list->next = NULL;

	if (list == NULL)
	{
		new_list->prev = NULL;
		return new_list;
	}

	DOUBLY_LINKED_LIST* start = list;

	while (list->next != NULL)
	{
		list = list->next;
	}

	list->next = new_list;
	new_list->prev = list;

	return start;
}

DOUBLY_LINKED_LIST* AddToDoublyLL_Sorted(DOUBLY_LINKED_LIST* list, int num)
{
	DOUBLY_LINKED_LIST* new_list = ALLOCATE_DOUBLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->prev = NULL;
		new_list->next = NULL;

		return new_list;
	}

	if (num < list->n)
	{
		list->prev = new_list;
		new_list->prev = NULL;
		new_list->next = list;

		return new_list;
	}

	DOUBLY_LINKED_LIST* start = list;

	while (list->next != NULL)
	{
		if (list->n <= num && num <= list->next->n)
		{
			list->next->prev = new_list;
			new_list->next = list->next;
			new_list->prev = list;
			list->next = new_list;

			return start;
		}

		list = list->next;
	}

	list->next = new_list;
	new_list->prev = list;
	new_list->next = NULL;

	return start;
}

DOUBLY_LINKED_LIST* AddToDoublyCircularLL(DOUBLY_LINKED_LIST* list, int num)
{
	DOUBLY_LINKED_LIST* new_list = ALLOCATE_DOUBLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->prev = new_list;
		new_list->next = new_list;
		return new_list;
	}

	DOUBLY_LINKED_LIST* start = list;

	while (list->next != start)
	{
		list = list->next;
	}

	list->next = new_list;
	new_list->prev = list;
	new_list->next = start;
	start->prev = new_list;

	return start;
}

DOUBLY_LINKED_LIST* AddToDoublyCircularLL_Sorted(DOUBLY_LINKED_LIST* list, int num)
{
	DOUBLY_LINKED_LIST* new_list = ALLOCATE_DOUBLY;
	new_list->n = num;

	if (list == NULL)
	{
		new_list->prev = new_list;
		new_list->next = new_list;
		return new_list;
	}

	DOUBLY_LINKED_LIST* start = list;

	if (num < list->n)
	{
		new_list->next = list;
		list->prev = new_list;

		while (list->next != start)
		{
			list = list->next;
		}

		list->next = new_list;
		new_list->prev = list;

		return new_list;
	}

	while (list->next != start)
	{
		if (list->n <= num && num <= list->next->n)
		{
			new_list->prev = list;
			new_list->next = list->next;
			list->next->prev = new_list;
			list->next = new_list;

			return start;
		}

		list = list->next;
	}

	list->next = new_list;
	new_list->prev = list;
	new_list->next = start;
	start->prev = new_list;

	return start;
}


DOUBLY_LINKED_LIST* ReverseDoublyLL(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	while (list->next != NULL)
	{
		swap(list->prev, list->next);

		list = list->prev;
	}

	swap(list->prev, list->next);
	return list;
}

DOUBLY_LINKED_LIST* ReverseDoublyCircularLL(DOUBLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	DOUBLY_LINKED_LIST* start = list;

	while (list->next != start)
	{
		swap(list->prev, list->next);

		list = list->prev;
	}

	swap(list->prev, list->next);
	return list;
}


DOUBLY_LINKED_LIST* CombineDoublyLL(DOUBLY_LINKED_LIST* list1, DOUBLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToDoublyLL(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

DOUBLY_LINKED_LIST* CombineDoublyLL_Sorted(DOUBLY_LINKED_LIST* list1, DOUBLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToDoublyLL_Sorted(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

DOUBLY_LINKED_LIST* CombineDoublyCircularLL(DOUBLY_LINKED_LIST* list1, DOUBLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToDoublyCircularLL(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}

DOUBLY_LINKED_LIST* CombineDoublyCircularLL_Sorted(DOUBLY_LINKED_LIST* list1, DOUBLY_LINKED_LIST* list2)
{
	if (list1 == NULL || list2 == NULL)
	{
		return NULL;
	}

	do
	{
		list1 = AddToDoublyCircularLL_Sorted(list1, list2->n);
		list2 = list2->next;
	}
	while (list2 != NULL);

	return list1;
}


DOUBLY_LINKED_LIST* ConvertToDoublyLL(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	DOUBLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToDoublyLL(new_list, list->n);

		list = list->next;
	}

	new_list = AddToDoublyLL(new_list, list->n);

	return new_list;
}

DOUBLY_LINKED_LIST* ConvertToDoublyLL_Sorted(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	DOUBLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToDoublyLL_Sorted(new_list, list->n);

		list = list->next;
	}

	new_list = AddToDoublyLL_Sorted(new_list, list->n);

	return new_list;
}

DOUBLY_LINKED_LIST* ConvertToDoublyCircularLL(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	DOUBLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToDoublyCircularLL(new_list, list->n);

		list = list->next;
	}

	new_list = AddToDoublyCircularLL(new_list, list->n);

	return new_list;
}

DOUBLY_LINKED_LIST* ConvertToDoublyCircularLL_Sorted(SINGLY_LINKED_LIST* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	DOUBLY_LINKED_LIST* new_list = NULL;

	while (list->next != NULL)
	{
		new_list = AddToDoublyCircularLL_Sorted(new_list, list->n);

		list = list->next;
	}

	new_list = AddToDoublyCircularLL_Sorted(new_list, list->n);

	return new_list;
}


DOUBLY_LINKED_LIST* GoToIndex_DoublyLL(DOUBLY_LINKED_LIST* list, int index)
{
	if (list == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < index; i++)
	{
		if (list->next == NULL)
		{
			return NULL;
		}

		list = list->next;
	}

	return list;
}
