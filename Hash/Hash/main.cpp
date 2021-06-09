#if 0
#include <stdio.h>
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

#define INSERT_DATA(t,p,n)               \
do{                                      \
	(t)->next = (n);                     \
	(p)->next = (t);                     \
	(t)->prev = (p);                     \
	(n)->prev = (t);                     \
} while(0)

void insert_front(NODE* temp, NODE* head)
{
	insert_data(temp, head, head->next);
}

#define INSERT_FRONT(temp, head)     \
	INSERT_DATA((temp), (head), (head)->next)

void insert_back(NODE* temp, NODE* head)
{
	insert_data(temp, head->prev, head);
}

#define INSERT_BACK(temp, head)     \
	INSERT_DATA((temp), (head)->prev, (head))

void delete_node(NODE* temp)
{
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
}

#define  DELETE_NODE(temp)                \
do{                                       \
	(temp)->prev->next = (temp)->next;    \
	(temp)->next->prev = (temp)->prev;    \
}while(0)

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
	SAWON* s;
	int i,j;
	clock_t start, end;
	
	init();

	start = clock();
	for (i = 0; i < 100000; i++)
	{
		for (j = 0; j < 1000; j++)
		{
			s = &sawons[sawon_count++];
			s->sid = j + 1;
			//insert_front(&s->list, &head);
			INSERT_FRONT(&s->list, &head);
		}
	}
	end = clock();
	printf("%lu\n", end - start);

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// ver 0.1

typedef struct _node
{
	struct _node* next, * prev;
} NODE;

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

#define HASH_MAX 32

typedef struct sawon
{
	int sid;
	NODE hash_list;
	NODE list;
}SAWON;

SAWON sawons[1000];
int sawon_count;

NODE head;
NODE hash_heads[HASH_MAX];

void init()
{
	int i;
	head.next = &head;
	head.prev = &head;

	for (i = 0; i < HASH_MAX; i++)
	{
		hash_heads[i].next = &hash_heads[i];
		hash_heads[i].prev = &hash_heads[i];
	}
	sawon_count = 0;
}

SAWON* find_data(int data, NODE* head)
{
	NODE* temp;
	SAWON* s;
	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, hash_list);
		if (s->sid == data)
			return s;
	}
	return 0;
}

int main()
{
	SAWON* s;
	int i,j;
	int data;
	clock_t start, end;

	init();
	for (i = 0; i < 1000; i++)
	{
		s = &sawons[sawon_count++];
		s->sid = i + 1;
		insert_front(&s->list, &head);
		insert_front(&s->hash_list, &hash_heads[s->sid%HASH_MAX]);
	}

	start = clock();
	for (i = 0; i < 10000; i++)
	{
		for (j = 0; j < 1000; j++)
		{
			data = rand()%1000 + 1;
			s = find_data(data, &hash_heads[data % HASH_MAX]);
		}
	}
	end = clock();
	printf("%lu\n", end - start);

	return 0;
}
#endif

#if 1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// ver 0.2

typedef struct _node
{
	struct _node* next, * prev;
} NODE;

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

#define HASH_MAX 32

typedef struct sawon
{
	int sid;
	unsigned int name_id;
	char name[11];
	NODE hash_list;
	NODE list;
}SAWON;

SAWON sawons[1000];
int sawon_count;

NODE head;
NODE hash_heads[HASH_MAX];

void init()
{
	int i;
	head.next = &head;
	head.prev = &head;

	for (i = 0; i < HASH_MAX; i++)
	{
		hash_heads[i].next = &hash_heads[i];
		hash_heads[i].prev = &hash_heads[i];
	}
	sawon_count = 0;
}

SAWON* find_data(int data, NODE* head)
{
	NODE* temp;
	SAWON* s;
	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, hash_list);
		if (s->sid == data)
			return s;
	}
	return 0;
}

void my_strcpy(char* dst, char* src)
{
	while (*dst++ = *src++)
		;
}

int my_strcmp(const char* cs, const char* ct)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}

void make_name(char str[][30])
{
	int i,j,k, count=0;
	char name[30] = { 'h','e','l','l','o', };
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			for (k = 0; k < 26; k++)
			{
				name[5] = 'a' + i;
				name[6] = 'a' + j;
				name[7] = 'a' + k;
				printf("%s\n", name);
				my_strcpy(str[count], name);
				if (++count == 1000)
					return;
			}
		}
	}
}

unsigned int hash_name(char* name)
{
	int i;
	unsigned int hx = 0;
	for (i = 0; name[i]; i++)
	{
		hx = (hx << 1) + name[i];
	}
	return hx;
}

SAWON* find_name_list(char *name, NODE* head)
{
	NODE* temp;
	SAWON* s;
	unsigned int name_id;

	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, list);
		name_id = hash_name(name);
		if (s->name_id == name_id )
		{
			if( my_strcmp( s->name, name ) == 0 )
				return s;
		}
	}
	return 0;
}

SAWON* find_name_hash(char* name, NODE* head)
{
	NODE* temp;
	SAWON* s;
	
	list_for_each(temp, head)
	{
		s = list_entry(temp, SAWON, hash_list);
		if (s->name_id == hash_name(name))
		{
			if (my_strcmp(s->name, name) == 0)
				return s;
		}
	}
	return 0;
}


int main()
{
	SAWON* s;
	int i, j;
	int data;
	clock_t start, end;
	char name[1000][30];

	make_name(name);
	for (i = 0; i < 1000; i++)
		printf("%s\n", name[i]);

	init();
	for (i = 0; i < 1000; i++)
	{
		s = &sawons[sawon_count++];
		s->sid = i + 1;
		my_strcpy(s->name, name[i]);
		s->name_id = hash_name(name[i]);
		insert_front(&s->list, &head);
		insert_front(&s->hash_list, &hash_heads[s->name_id % HASH_MAX]);
	}

	start = clock();
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1; j++)
		{
			unsigned int index;
			index = hash_name(name[i]);
			s = find_name_list(name[rand() % 1000], &head);
			//s = find_name_hash(name[rand() % 1000], &hash_heads[index % HASH_MAX]);
		}
	}
	end = clock();
	printf("%lu\n", end - start);

	return 0;
}
#endif

