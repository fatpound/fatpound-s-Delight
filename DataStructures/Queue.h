#define QUEUE_LIMIT 5

typedef struct Queue
{
	int last = -1;
	int q[STACK_LIMIT];
}
QUEUE;

typedef struct CircularQueue
{
	int last  = -1;
	int first = -1;
	int count = 0;
	int q[STACK_LIMIT];
}
CIRCULAR_QUEUE;

void AddToQueue(QUEUE* queue, int n)
{
	if (queue->last == QUEUE_LIMIT)
		return;

	queue->q[++queue->last] = n;
}

int RemoveFromQueue(QUEUE* queue)
{
	if (queue->last == -1)
		return INT32_MIN;

	int num = queue->q[0];

	for (int i = 1; i <= queue->last; i++)
	{
		queue->q[i - 1] = queue->q[i];
	}

	// queue->q[queue->last] = 0;

	queue->last--;

	return num;
}

void ListQueue(QUEUE* queue)
{
	for (int i = 0; i <= queue->last; i++)
	{
		printf("%d ", queue->q[i]);
	}

	printf("\n");
}


void AddToCircularQueue(CIRCULAR_QUEUE* queue, int n)
{
	if (queue->count == QUEUE_LIMIT)
		return;

	queue->last++;
	queue->last %= QUEUE_LIMIT;
	queue->q[queue->last] = n;
	queue->count++;
}

int RemoveFromCircularQueue(CIRCULAR_QUEUE* queue)
{
	if (queue->count == 0)
		return INT32_MIN;

	queue->first++;
	queue->first %= QUEUE_LIMIT;

	int num = queue->q[queue->first];

	// queue->q[queue->first] = 0;

	queue->count--;

	return num;
}

void ListCircularQueue(CIRCULAR_QUEUE* queue)
{
	for (int i = 1; i <= queue->count; i++)
	{
		printf("%d ", queue->q[(queue->first + i) % QUEUE_LIMIT]);
	}

	printf("\n");
}
