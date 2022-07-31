struct Node
{
	int n;
	struct Node *prev;
	struct Node *next;
};

struct Node *PUSH_2(struct Node *top, int value)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	
	yeni->n = value;
	yeni->prev = NULL;
	
	if (!top)
	{
		yeni->next = NULL;
		
		return (top = yeni);
	}
	else
	{
		yeni->next = top;
		
		return (top->prev = yeni);
	}
}
