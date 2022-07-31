struct Node
{
	int n;
	struct Node *prev;
	struct Node *next;
};

struct Node *ENQUEUE_2(struct Node *ilk, int value)
{
	struct Node *yeni = (struct Node*) malloc(sizeof(struct Node));
	
	yeni->n    = value;
	yeni->prev = NULL;
	yeni->next = NULL;
	
	if (!ilk)
	{
		return (yeni);
	}
	else
	{
		struct Node *gecici = ilk;
		struct Node *birprev = NULL;
		
		while (gecici->next)
		{
			birprev = gecici;
			gecici = gecici->next;
			gecici->prev = birprev;
		}
		
		gecici->next = yeni;
		yeni->prev = gecici;
		
		return (ilk);
	}
}