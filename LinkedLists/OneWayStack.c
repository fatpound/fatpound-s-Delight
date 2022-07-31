struct Node
{
	int n;
	struct Node *next;
};

struct Node *PUSH_1(struct Node *top, int value)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	
	yeni->n = value;
	yeni->next = NULL;
	
	if (!top)
	{
		top = yeni;
		return (top);
	}
	else
	{
		yeni->next = top;
		return (yeni);
	}
}

struct Node *POP_1(struct Node *top, int sayi)
{
	if (!top)
	{
		return (top);
	}
	else
	{
		struct Node *tmp = top;
		
		top = top->next;
		free(tmp);
		
		return (top);
	}
}
