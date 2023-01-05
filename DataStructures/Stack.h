#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define STACK_LIMIT 5

typedef struct Stack
{
    int s[STACK_LIMIT];
    int index = -1;
}
STACK;

void Push(STACK* stack, int n)
{
    if (stack->index == STACK_LIMIT - 1)
        return;

    stack->s[++stack->index] = n;
}

int Pop(STACK* stack, int n)
{
    if (stack->index == 0)
        return INT32_MIN;

    int num = stack->s[stack->index];

    stack->s[stack->index--] = 0;

    return num;
}

void ListStack(STACK* stack)
{
	for (int i = stack->index; i >= 0; i--)
	{
		printf("%d\n", stack->s[i]);
	}

	printf("\n");
}
