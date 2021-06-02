#if 0
// ver 0.1
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE* head;

void insert_data(int data)
{
	NODE* temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = head;
	head = temp;
}

void display()
{
	NODE* temp;
	system("cls");
	printf("head");
	for (temp = head; temp; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("\n");
	getchar();
}

void init()
{
	head = 0;
}

int main()
{
	int i;
	init();
	display();
	for (i = 0; i < 7; i++)
	{
		insert_data(i + 1);
		display();
	}

	return 0;
}
#endif

#if 0
// ver 0.2
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE* head;

void insert_data(NODE* temp)
{
	temp->next = head;
	head = temp;
}

void display()
{
	NODE* temp;
	system("cls");
	printf("head");
	for (temp = head; temp; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("\n");
	getchar();
}

NODE nodes[7];
int node_count;

void init()
{
	head = 0;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;
	init();
	display();
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p);
		display();
	}

	return 0;
}
#endif

#if 0
// ver 0.3
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE head;

void insert_data(NODE* temp)
{
	temp->next = head.next;
	head.next = temp;
}

void display()
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head.next; temp; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("\n");
	getchar();
}

NODE nodes[7];
int node_count;

void init()
{
	head = { 0, 0 };
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;
	init();
	display();
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p);
		display();
	}

	return 0;
}
#endif


#if 0
// ver 0.4
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	int a;
	struct _node* next;
} NODE;

NODE head1;

void insert_data(NODE* temp, NODE *head)
{
	temp->next = head->next;
	head->next = temp;
}

void display(NODE *head)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("\n");
	getchar();
}

NODE nodes[7];
int node_count;

void init()
{
	head1.next = 0;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;
	
	NODE **q = &((NODE*)0)->next;
	init();
	display(&head1);
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head1);
		display(&head1);
	}

	return 0;
}
#endif

#if 0
// ver 0.5
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE head, tail;

void insert_data(NODE* temp, NODE* head)
{
	temp->next = head->next;
	head->next = temp;
}

void display(NODE* head, NODE *tail)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next;temp!=tail; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("->[tail]\n");
	getchar();
}

NODE nodes[7];
int node_count;

void init()
{
	head.next = &tail;
	tail.next = &tail;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;

	init();
	display(&head, &tail);
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head);
		display(&head, &tail);
	}

	return 0;
}
#endif

#if 0
// ver 0.6
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* head)
{
	temp->next = head->next;
	head->next = temp;
}

void display(NODE* head)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp != head; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("->[head]\n");
	getchar();
}

NODE nodes[7];
int node_count;

void init()
{
	head.next = &head;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;

	init();
	display(&head);
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head);
		display(&head);
	}

	return 0;
}
#endif

#if 0
// ver 0.7
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* head)
{
	temp->next = head->next;
	head->next = temp;
}

void display(NODE* head)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp != head; temp = temp->next)
		printf("->[%d]", temp->data);
	printf("->[head]\n");
	getchar();
}

void delete_node(NODE* temp, NODE* head)
{
	NODE* prev;
	for (prev = head; prev->next != head; prev = prev->next)
		if (prev->next == temp)
			break;
	if (prev->next == temp)
		prev->next = temp->next;
}

NODE* find_data(int data, NODE* head)
{
	NODE* temp;
	for (temp = head->next; temp != head; temp = temp->next)
		if (temp->data == data)
			return temp;
	return 0;
}

NODE nodes[7];
int node_count;

void init()
{
	head.next = &head;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;

	init();
	
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head);
	}

	p = find_data(5, &head);
	if( p )
		printf("%d\n", p->data);
	else
		printf("해당 노드는 없습니다.\n");

	display(&head);
	delete_node(p, &head);
	display(&head);

	return 0;
}
#endif

#if 0
// ver 0.7
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next, *prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* head)
{
	temp->next = head->next;
	head->next = temp;
	temp->prev = head;
	temp->next->prev = temp;
}

void display(NODE* head)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp != head; temp = temp->next)
		printf("<->[%d]", temp->data);
	printf("<->[head]\n");
	getchar();
}

void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

NODE* find_data(int data, NODE* head)
{
	NODE* temp;
	for (temp = head->next; temp != head; temp = temp->next)
		if (temp->data == data)
			return temp;
	return 0;
}

NODE nodes[7];
int node_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;

	init();

	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head);
	}

	p = find_data(5, &head);
	if (p)
		printf("%d\n", p->data);
	else
		printf("해당 노드는 없습니다.\n");

	display(&head);
	delete_node(p);
	display(&head);

	return 0;
}
#endif

#if 0
// ver 0.8
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next, * prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* prev, NODE* next)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}

void insert_front(NODE* temp, NODE* head)
{
	insert_data(temp, head, head->next);
}

void insert_back(NODE* temp, NODE* head)
{
	insert_data(temp, head->prev, head);
}

void display(NODE* head)
{
	NODE* temp;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp != head; temp = temp->next)
		printf("<->[%d]", temp->data);
	printf("<->[head]\n");
	getchar();
}

void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

NODE* find_data(int data, NODE* head)
{
	NODE* temp;
	for (temp = head->next; temp != head; temp = temp->next)
		if (temp->data == data)
			return temp;
	return 0;
}

NODE nodes[7];
int node_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	node_count = 0;
}

int main()
{
	int i;
	NODE* p;

	init();

	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		//insert_front(p, &head);
		insert_back(p, &head);
	}

	p = find_data(5, &head);
	if (p)
		printf("%d\n", p->data);
	else
		printf("해당 노드는 없습니다.\n");

	display(&head);
	delete_node(p);
	display(&head);

	return 0;
}
#endif

#if 0
// ver 0.9
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	void* data;
	struct _node* next, * prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* prev, NODE* next)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}

void insert_front(NODE* temp, NODE* head)
{
	insert_data(temp, head, head->next);
}

void insert_back(NODE* temp, NODE* head)
{
	insert_data(temp, head->prev, head);
}

void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

//--------------------------------------------------

typedef struct sawon
{
	int sid;
}SAWON;

void display(NODE* head)
{
	NODE* temp;
	SAWON* s;
	system("cls");
	printf("[head]");
	for (temp = head->next; temp != head; temp = temp->next)
	{
		s = (SAWON*)temp->data;
		printf("<->[%d]", s->sid);
	}
	printf("<->[head]\n");
	getchar();
}

SAWON* find_data(int data, NODE* head)
{
	NODE* temp;
	SAWON* s;
	for (temp = head->next; temp != head; temp = temp->next)
	{
		s = (SAWON*)temp->data;
		if (s->sid == data)
			return s;
	}
	return 0;
}

NODE nodes[1000];
int node_count;

SAWON sawons[1000];
int sawon_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	node_count = 0;
	sawon_count = 0;
}

int main()
{
	int i;
	NODE* p;
	SAWON* s;

	init();

	display(&head);
	for (i = 0; i < 7; i++)
	{
		p = &nodes[node_count++];
		s = &sawons[sawon_count++];
		s->sid = i + 1;
		p->data = s;
		insert_back(p, &head);
		display(&head);
	}
	return 0;
}
#endif

#if 0

#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	struct _node* next, * prev;
} NODE;

typedef struct
{
	int sid;
	int a;
	NODE list;
}SAWON;

int main()
{
	SAWON sawon;
	SAWON *s;
	NODE* temp = &sawon.list;
	NODE* t;
	t = &((SAWON*)0)->list;
	printf("%p\n", t);
}
#endif


#if 0
// ver 1.0
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	struct _node* next, * prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* prev, NODE* next)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}

void insert_front(NODE* temp, NODE* head)
{
	insert_data(temp, head, head->next);
}

void insert_back(NODE* temp, NODE* head)
{
	insert_data(temp, head->prev, head);
}

void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (unsigned long)&((type*)0)->member))

#define list_for_each(temp, head)     \
for(temp=(head)->next;temp!=(head);temp=temp->next)

//--------------------------------------------------

typedef struct sawon
{
	int sid;
	NODE list;
}SAWON;

void display(NODE* head)
{
	NODE* temp;
	SAWON* s;
	system("cls");
	printf("[head]");
	list_for_each(temp, head)
	{

		s = list_entry(temp, SAWON, list);
		printf("<->[%d]", s->sid);
	}
	printf("<->[head]\n");
	getchar();
}

SAWON* find_data(int data, NODE* head)
{
	NODE* temp;
	SAWON* s;
	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, list);
		if (s->sid == data)
			return s;
	}
	return 0;
}

SAWON sawons[1000];
int sawon_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	sawon_count = 0;
}

int main()
{
	int i;
	NODE* p;
	SAWON* s;

	init();

	display(&head);
	for (i = 0; i < 7; i++)
	{
		s = &sawons[sawon_count++];
		s->sid = i + 1;
		insert_back(&s->list, &head);
		display(&head);
	}
	return 0;
}
#endif


#if 1
// ver 1.0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node
{
	struct _node* next, * prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE* prev, NODE* next)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}

#define  INSERT_DATA(temp, p, n) \
do{                           \
	(temp)->next = (n);    \
	(p)->next = (temp);    \
	(temp)->prev = (p);    \
	(n)->prev = (temp);    \
}while(0)



void insert_front(NODE* temp, NODE* head)
{
	insert_data(temp, head, head->next);
}

void insert_back(NODE* temp, NODE* head)
{
	insert_data(temp, head->prev, head);
}

#define INSERT_BACK(temp, head)  \
	INSERT_DATA((temp), (head)->prev, (head))


void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (unsigned long)&((type*)0)->member))

#define list_for_each(temp, head)     \
for(temp=(head)->next;temp!=(head);temp=temp->next)

//--------------------------------------------------

typedef struct sawon
{
	int sid;
	NODE list;
}SAWON;

SAWON sawons[1000];
int sawon_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	sawon_count = 0;
}

SAWON* find_data(int data, NODE* head)
{
	NODE* temp;
	SAWON* s;
	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, list);
		if (s->sid == data)
			return s;
	}
	return 0;
}

int main()
{
	int i,j;
	//NODE* p;
	SAWON* s;
	clock_t start, end;

	init();
	start = clock();
	for (j = 0; j < 100000; j++)
	{
		sawon_count = 0;
		for (i = 0; i < 1000; i++)
		{
			s = &sawons[sawon_count++];
			s->sid = i + 1;
			//insert_back(&s->list, &head);
			//INSERT_BACK(&s->list, &head);
			//INSERT_DATA(&s->list, &head, head.next);
			insert_data(&s->list, &head, head.next);
		}
	}
	end = clock();
	printf("%lu\n", end - start);
	/*start = clock();
	for (j = 0; j < 10000; j++)
	{
		sawon_count = 0;

		for (i = 0; i < 1000; i++)
			s = find_data(i + 1, &head);
	}
	end = clock();
	printf("%lu\n", end - start);*/
	return 0;
}
#endif

#if 0
// ver 0.2
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next, *prev;
} NODE;

NODE head;

void insert_data(NODE* temp, NODE *head)
{
	temp->next = head->next;
	head->next = temp;
	temp->prev = head;
	temp->next->prev = temp;
}

NODE* find_data(int data, NODE* head)
{
	NODE* temp;
	for(temp=head->next; temp!=head; temp=temp->next)
	{
		if (temp->data == data)
			return temp;
	}
	return 0;
}

NODE nodes[1000];
int node_count;

void init()
{
	head.next = &head;
	head.prev = &head;
	node_count = 0;
}

int main()
{
	int i, j;
	NODE* p;
	clock_t start, end;

	init();

	for (i = 0; i < 1000; i++)
	{
		p = &nodes[node_count++];
		p->data = i + 1;
		insert_data(p, &head);
	}

	start = clock();
	for (j = 0; j < 10000; j++)
	{
		for (i = 0; i < 1000; i++)
			p = find_data(i + 1, &head);
	}
	end = clock();
	printf("%lu\n", end - start);
	return 0;
}
#endif