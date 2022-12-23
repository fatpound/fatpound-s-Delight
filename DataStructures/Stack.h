#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define STACK_LIMIT 50

typedef struct Stack
{
	int d[STACK_LIMIT];
	int index = -1;
}
STACK;

void Push(STACK* stack, int n)
{
	if (stack->index == STACK_LIMIT - 1)
	{
		return;
	}

	stack->d[++stack->index] = n;
}

int Pop(STACK* stack, int n)
{
	if (stack->index == 0)
	{
		return INT32_MIN;
	}

	int result = stack->d[stack->index];

	stack->d[stack->index--] = 0;

	return result;
}
