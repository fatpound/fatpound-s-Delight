struct Node
{
	int x;
	struct Node* next;
};

struct Node *ENQUEUE_1(struct Node *ilk, int sayi)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	
	yeni->x = sayi;
	yeni->next = NULL;
	
	if (!ilk)
	{
		ilk = yeni;
		return (ilk);
	}
	else
	{
		struct Node *temp = ilk;
		
		while (temp->next)
		{
			temp = temp->next;
		}
		
		temp->next = yeni;
		return (ilk);
	}
}

struct Node *DEQUEUE_1(struct Node *list, int sayi)
{
	if (!list)
	{
		return (list);
	}
	else
	{
		struct Node *tmp = list;
		
		list = list->next;
		free(tmp);
		
		return (list);
	}
}
