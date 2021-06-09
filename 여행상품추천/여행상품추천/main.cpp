#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int M);
extern void befriend(int uid1, int uid2);
extern void add(int pid, int area, int price);
extern void reserve(int uid, int pid);
extern int  recommend(int uid);

#define INIT			100
#define BEFRIEND		200
#define ADD				300
#define RESERVE			400
#define RECOMMEND		500

static bool run()
{
    int L, N, M;
    bool okay = false;

    int pid, uid;
    int uid1, uid2;
    int area, price;

    int ans;
    int cmd, ret;

    scanf("%d", &L);

    for (int l = 0; l < L; ++l)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case INIT:
            scanf("%d %d", &N, &M);
            init(N, M);
            okay = true;
            break;
        case BEFRIEND:
            scanf("%d %d", &uid1, &uid2);
            befriend(uid1, uid2);
            break;
        case ADD:
            scanf("%d %d %d", &pid, &area, &price);
            add(pid, area, price);
            break;
        case RESERVE:
            scanf("%d %d", &uid, &pid);
            reserve(uid, pid);
            break;
        case RECOMMEND:
            scanf("%d %d", &uid, &ans);
            ret = recommend(uid);
            if (ret != ans)
                okay = false;
            break;
        }
    }

    return okay;
}

#include <time.h>
int main() {
    int TC, MARK;

    freopen("sample_input.txt", "r", stdin);

    setbuf(stdout, NULL);
    scanf("%d %d", &TC, &MARK);

	clock_t start, end;
	start = clock();
    for (int testcase = 1; testcase <= TC; ++testcase) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", testcase, score);
    }
	end = clock();
	printf("%lu\n", end - start);

    return 0;
}

#if 1

//-----------------------------------------------------------------------

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (unsigned long)&((type*)0)->member))

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

//--------------------------------------------------------------------------------------
#define MAX_USER 1000
#define MAX_PRODUCT 40000
#define MAX_AREA 10
#define MAX_FRIENDS 20
#define MAX_HASH 4096
//--------------------------------------------------------------------------------------

typedef struct heap
{
	void* data[MAX_PRODUCT];
	int h_count;
} HEAP;

#if 1
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
#endif

#if 1

#define swap(a, b)      \
do{                     \
	void* t;            \
	t = *(a);           \
	*(a) = *(b);        \
	*(b) = t;           \
}while(0)

#define up_heap(_heap, _cmp)             \
do{                                      \
	void** a = (_heap)->data;            \
	int n = (_heap)->h_count;            \
	int c, r;                            \
                                         \
	for (c = n - 1; c > 0; c = r)        \
	{                                    \
		r = (c - 1) / 2;                 \
		if ((_cmp)(a[r], a[c]) <= 0)     \
			break;                       \
		swap(&a[r], &a[c]);              \
	}                                    \
}while(0)



#define down_heap(_heap, _cmp)                             \
do{                                                        \
	int r, c;                                              \
	void** a = (_heap)->data;                              \
	int n = (_heap)->h_count;                              \
	swap(a, a + n - 1);                                    \
	for (r = 0; r * 2 + 1 < n - 1; r = c)                  \
	{                                                      \
		c = r * 2 + 1;                                     \
		if (c < n - 2 && (_cmp)(a[c], a[c + 1]) > 0)       \
			c++;                                           \
		if ((_cmp)(a[r], a[c]) <= 0)                       \
			break;                                         \
		swap(a + r, a + c);                                \
	}                                                      \
}while(0)


#define push(_heap, _data, _cmp)                      \
do{                                                   \
	(_heap)->data[(_heap)->h_count++] = _data;        \
	up_heap(_heap, _cmp);                              \
}while(0)

#define pop(_heap, _cmp)        \
do{                             \
	down_heap(_heap, _cmp);     \
	(_heap)->h_count--;         \
}while(0)
#endif


void* top(HEAP* heap)
{
	if (heap->h_count == 0)
		return 0;
	return heap->data[0];
}
//--------------------------------------------------------------------------------------

typedef struct
{
	int pid;
	int area;
	int price;
	int reserved;
	NODE hash_list;
} PRODUCT;

typedef struct
{
	int friends[MAX_FRIENDS];
	int friends_count;
	int area_count[MAX_AREA];
	int area_total_count[MAX_AREA];
} USER;

HEAP heap[MAX_AREA];

USER user_pool[MAX_USER];
PRODUCT product_pool[MAX_PRODUCT];

NODE product_hash_heads[MAX_HASH];

int product_pool_count;
int user_max_count;
int area_max_count;

void init(int N, int M)
{
	int i, j;

	product_pool_count = 0;
	user_max_count = N;
	area_max_count = M;

	for (i = 0; i < user_max_count; i++)
	{
		for (j = 0; j < area_max_count; j++)
		{
			user_pool[i].area_count[j] = 0;
			user_pool[i].area_total_count[j] = 0;
		}

		user_pool[i].friends_count = 0;
		for (j = 0; j < MAX_FRIENDS; j++)
			user_pool[i].friends[j] = 0;
	}

	for (i = 0; i < area_max_count; i++)
		heap[i].h_count = 0;
		
	for (i = 0; i < MAX_HASH; i++)
		INIT_LIST_HEAD(&product_hash_heads[i]);
}

void befriend(int uid1, int uid2)
{
	int i;

	user_pool[uid1-1].friends[user_pool[uid1-1].friends_count++] = uid2-1;
	user_pool[uid2-1].friends[user_pool[uid2-1].friends_count++] = uid1-1;

	for (i = 0; i < area_max_count; i++)
	{
		user_pool[uid1-1].area_total_count[i] += user_pool[uid2-1].area_count[i];
		user_pool[uid2-1].area_total_count[i] += user_pool[uid1-1].area_count[i];
	}
}

int my_product_compare(void* a, void* b)
{
	int ret = 0;
	PRODUCT* x = (PRODUCT*)a;
	PRODUCT* y = (PRODUCT*)b;

	if (x->price - y->price != 0)
	{
		ret = x->price - y->price;
	}
	else
		ret = x->pid - y->pid;

	return ret;
}

void add(int pid, int area, int price)
{
	PRODUCT* p;
	p = &product_pool[product_pool_count++];
	p->pid = pid;
	p->area = area-1;
	p->price = price;
	p->reserved = 0;
	list_add_tail(&p->hash_list, &product_hash_heads[pid%MAX_HASH]);

	push(&heap[area - 1], p, my_product_compare);
}

void reserve(int uid, int pid)
{
	int i;
	PRODUCT* p = 0;
	NODE* temp;

	list_for_each(temp, &product_hash_heads[pid%MAX_HASH])
	{
		p = list_entry(temp, PRODUCT, hash_list);
		if (p->pid == pid)
			break;
	}

	p->reserved = 1;

	user_pool[uid-1].area_count[p->area]++;
	user_pool[uid-1].area_total_count[p->area]++;

	for (i = 0; i < user_pool[uid-1].friends_count; i++) {
		user_pool[user_pool[uid-1].friends[i]].area_total_count[p->area]++;
	}
}


int recommend(int uid)
{
	int pid;
	int i, j, first=0;
	PRODUCT* p, *temp_node=0;
	NODE* temp;

	int temp_val = 0;

	for (i = 0; i < area_max_count; i++) 
	{
		while ( heap[i].h_count > 0 )
		{
			p = (PRODUCT*)top(&heap[i]);
			if (p->reserved)
				pop(&heap[i], my_product_compare);
			else
				break;
		}

		if (heap[i].h_count == 0)
			continue;

		if (first == 0)
		{
			temp_node = (PRODUCT*)top(&heap[i]);
			first = 1;
		}

		if (temp_val < user_pool[uid-1].area_total_count[i]) 
		{
			temp_node = (PRODUCT*)top(&heap[i]);
			temp_val = user_pool[uid-1].area_total_count[i];
		}
		else if(temp_val == user_pool[uid - 1].area_total_count[i])
		{
			p = (PRODUCT*)top(&heap[i]);
			if (p->price < temp_node->price)
			{
				temp_node = p;
			}
			else if (p->price == temp_node->price)
			{
				if( p->pid < temp_node->pid )
					temp_node = p;
			}
		}
	}

	return temp_node->pid;
}

#endif


