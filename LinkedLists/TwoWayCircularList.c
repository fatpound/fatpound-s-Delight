struct Node
{
	int n;
	struct Node *prev;
	struct Node *next;
};

struct Node *AddCircularList_2(struct Node *list, int value)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	yeni->n = value;
	
	if (list == NULL)
	{
		return (yeni->next = yeni->prev = yeni);
	}
	else
	{
		struct Node *start  = list;
		
		while (list->next != start)
		{
			list->next->prev = list;
			list = list->next;
		}
		
		list->next  = yeni;
		yeni->prev  = list;
		yeni->next  = start;
		start->prev = yeni;
		
		return (start);
	}
}