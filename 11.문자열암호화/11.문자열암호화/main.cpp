#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

//-------------------------------------------------------------------------------
#if 1

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (char*)&((type*)0)->member))

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
			&pos->member != (head);					\
			pos = list_next_entry(pos, member))

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

typedef struct node
{
	struct node* next, * prev;
}NODE;

#define __list_add(temp, p, n)     \
do{                                \
    NODE *prev = (p);              \
    NODE *next = (n);              \
	(temp)->next = next;           \
	prev->next = (temp);           \
	(temp)->prev = prev;           \
	next->prev = (temp);           \
}while(0)

#define list_add(temp, head)    \
	__list_add((temp), (head), (head)->next)

#define list_add_tail(temp, head)    \
	__list_add((temp), (head)->prev, (head))


#define  __list_del(p, n)     \
do{                           \
	(n)->prev = (p);          \
	(p)->next = (n);          \
}while(0)

#define list_del(entry)       \
	__list_del((entry)->prev, (entry)->next)

#define INIT_LIST_HEAD(list)  \
do{                           \
	(list)->next = (list);    \
	(list)->prev = (list);    \
}while(0)

int list_empty(NODE* head)
{
	return head->next == head;
}

char* my_strcpy(char* dest, char* src)
{
	char* tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;
}

#define MAX_STR 50001
#define MAX_HASH 1024

typedef struct heap
{
	void* data[MAX_STR];
	int h_count;
} HEAP;

void swap(void** a, void** b)
{
	void* t;
	t = *a;
	*a = *b;
	*b = t;
}

void up_heap(HEAP* heap, int(*cmp)(void*, void*))
{
	void** a = heap->data;
	int n = heap->h_count;
	int c, r;

	for (c = n - 1; c > 0; c = r)
	{
		r = (c - 1) / 2;
		if (cmp(a[r], a[c]) <= 0)
			break;
		swap(&a[r], &a[c]);
	}
}

void down_heap(HEAP* heap, int(*cmp)(void*, void*))
{
	int r, c;
	void** a = heap->data;
	int n = heap->h_count;
	swap(a, a + n - 1);
	for (r = 0; r * 2 + 1 < n - 1; r = c)
	{
		c = r * 2 + 1;
		if (c < n - 2 && cmp(a[c], a[c + 1]) > 0)
			c++;
		if (cmp(a[r], a[c]) <= 0)
			break;
		swap(a + r, a + c);
	}
}

void push(HEAP* heap, void* data, int(*cmp)(void*, void*))
{
	heap->data[heap->h_count++] = data;
	up_heap(heap, cmp);
}

void pop(HEAP* heap, int(*cmp)(void*, void*))
{
	down_heap(heap, cmp);
	heap->h_count--;
}

void* top(HEAP* heap)
{
	if (heap->h_count == 0)
		return 0;
	return heap->data[0];
}
//-----------------------------------------------------------------------


typedef struct
{
	int id;
	int pos;
	NODE list;
} WORD;

char origin_string[MAX_STR];
char convert_string[MAX_STR];
int origin_len;

WORD word_pool[MAX_STR*3];
int word_count;

NODE heads[MAX_HASH];
HEAP heap;

int str_hash(char* str)
{
	int ret = 0;
	int i;

	for (i = 0; i < 3; i++)
		ret = (ret * 27) + str[i] - 'a' + 1;

	return ret;
}

void init(int N, char init_string[])
{
	int i;
	WORD* p;
	word_count = 0;
	my_strcpy(origin_string, init_string);
	my_strcpy(convert_string, init_string);
	origin_len = N;

	for (i = 0; i < MAX_HASH; i++)
		INIT_LIST_HEAD(&heads[i]);

	for (i = 0; i < N - 2; i++)
	{
		p = &word_pool[word_count++];
		p->id = str_hash(origin_string + i);
		p->pos = i;
		list_add_tail(&p->list, &heads[p->id % MAX_HASH]);
	}
}

int my_pos_compare(void* a, void* b)
{
	int ret = 0;
	WORD* x = (WORD*)a;
	WORD* y = (WORD*)b;

	ret = x->pos - y->pos;

	return ret;
}

WORD* find_word(int id)
{
	NODE* temp;
	WORD* wp = 0;

	list_for_each(temp, &heads[id % MAX_HASH])
	{
		wp = list_entry(temp, WORD, list);
		if (id == wp->id)
			break;
	}
	return wp;
}

void change_node(WORD* p)
{
	list_del(&p->list);
	list_add_tail(&p->list, &heads[p->id % MAX_HASH]);
}

int change(char string_A[], char string_B[])
{
	int change_count = 0; 
	int id;
	NODE* temp;
	WORD* p;
	int i, j, k;
	int prev;

	heap.h_count = 0;
	id = str_hash(string_A);
	
	list_for_each(temp, &heads[id % MAX_HASH])
	{
		p = list_entry(temp, WORD, list);
		if (id == p->id)
			push(&heap, p, my_pos_compare);
	}

	for (i = 0; top(&heap); i++)
	{
		p = (WORD*)top(&heap);
		if (p == 0)
			break;

		pop(&heap, my_pos_compare);

		if (i == 0)
			prev = p->pos;
		else if ( p->pos - prev < 3)
		{
			continue;
		}

		for (j = 0; j < 3; j++)
			convert_string[p->pos + j] = string_B[j];

		p->id = str_hash(string_B);
		change_node(p);

		prev = p->pos;

		for (j = 0; j < 5; j++)
		{
			char src[4] = { 0, };
			char dst[4] = { 0, };
			int src_id, dst_id;
			WORD* wp=0;

			if (j == 2)
				continue;

			if (p->pos+j-2 < 0)
				continue;

			if (p->pos + j >= origin_len)
				continue;

			for (k = 0; k < 3; k++)
			{
				src[k] = origin_string[p->pos + j - 2 + k ];
				dst[k] = convert_string[p->pos + j - 2 + k];
			}
			src_id = str_hash(src);
			dst_id = str_hash(dst);
			if (src_id == dst_id)
				continue;

			wp = find_word(src_id);
			wp->id = dst_id;
			change_node(wp);
		}
		
		change_count++;
	}
	return change_count;
}

void result(char ret[])
{
	my_strcpy(ret, convert_string);
}

int main()
{
	int ret;
	char ret_str[200];
	init(10, (char*)"baaabbbbbb");
	ret = change((char*)"baa", (char*)"aba");
	printf("ret=%d\n", ret);
	ret = change((char*)"aaa", (char*)"bba");
	printf("ret=%d\n", ret);
	ret = change((char*)"bbb", (char*)"abb");
	printf("ret=%d\n", ret);
	result(ret_str);
	printf("%s\n", ret_str);

	return 0;
}
#endif