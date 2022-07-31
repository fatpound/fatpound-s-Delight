struct Node
{
	int n;
	struct Node *next;
};

struct Node *AddCircularList_1(struct Node *list, int sayi)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	yeni->n = sayi;
	
	if (list == NULL)
	{
		yeni->next = yeni;
		
		return yeni;
	}
	else
	{
		struct Node *start = list;
		
		while (list->next != start)
		{
			list = list->next;
		}
		
		list->next = yeni;
		yeni->next = (list == start ? list : start);
		
		return start;
	}
}