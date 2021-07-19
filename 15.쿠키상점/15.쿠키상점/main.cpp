#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_N				10
#define MAX_ORDER			20000

extern void init(void);
extern void addCookieCutter(int mID, int N, int mShapeList[]);
extern void orderCookie(int mShape, int daysLeft);
extern int  checkRemain(int mShape);
extern void newDay(void);

/////////////////////////////////////////////////////////////////////////

static int mIDList[MAX_ORDER];
static int mIDCnt;

void makeCookies(int mID)
{
	if (mIDCnt >= MAX_ORDER)
		return;

	mIDList[mIDCnt++] = mID;
}

/////////////////////////////////////////////////////////////////////////

#define INIT           		0
#define ADD_COOKIECUTTER    1
#define ORDER_COOKIE  		2
#define CHECK_REMAIN   		3
#define NEW_DAY         	4

static bool run()
{
	int mID;
	int N, mShapeList[MAX_N];
	int mShape, daysLeft;

	int Q;
	int cmd, ret = 0, ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int i = 0; i < Q; ++i)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			init();
			okay = true;
			break;
		case ADD_COOKIECUTTER:
			scanf("%d %d", &mID, &N);
			for (int j = 0; j < N; ++j)
				scanf("%d", &mShapeList[j]);
			if (okay)
				addCookieCutter(mID, N, mShapeList);
			break;
		case ORDER_COOKIE:
			scanf("%d %d", &mShape, &daysLeft);
			if (okay)
				orderCookie(mShape, daysLeft);
			break;
		case CHECK_REMAIN:
			scanf("%d", &mShape);
			if (okay)
				ret = checkRemain(mShape);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case NEW_DAY:
			mIDCnt = 0;
			if (okay)
				newDay();
			scanf("%d", &ans);
			if (mIDCnt != ans)
				okay = false;
			for (int k = 0; k < ans; ++k)
			{
				int mID_a;
				scanf("%d", &mID_a);
				if (mIDList[k] != mID_a)
					okay = false;
			}
			break;
		default:
			okay = false;
		}
	}

	return okay;
}

#include <time.h>
int main()
{
	clock_t start, end;
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	start = clock();
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	end = clock();
	printf("%lu\n", end - start);

	return 0;
}

//-----------------------------------------------------------------------

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

//--------------------------------------------------------------------------------------

typedef struct heap
{
	void* data[MAX_ORDER];
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

#define MAX_CALL 40000
#define MAX_COOKIE 1000 
#define MAX_ADD 100 
#define MAX_ORDER 20000
#define MAX_DAY 25000

extern void makeCookies(int mID);

typedef struct  
{
	int index;
    int day;
    int mShape;
    NODE list;
} Order;

typedef struct 
{
    int mShape[MAX_COOKIE+1];
    int mShapeList[10];
    int size;
}Cutter;

NODE days[MAX_DAY+5];
Order orders[MAX_ORDER + MAX_DAY * 2 + 5];
Cutter cutters[MAX_ADD+1];

int order_count;
int cutter_count;

HEAP heap[MAX_COOKIE+1];

int today;

void init(void)
{
	int i,j;
	cutter_count = 1;
	order_count = 0;
    today = 0;

    for( i = 0; i < MAX_DAY+5; i++) 
		INIT_LIST_HEAD(&days[i]);

    for (i = 0; i < MAX_COOKIE+1; i++) 
        heap[i].h_count=0;

	for (i = 0; i < MAX_ADD + 1; i++)
	{
		cutters[i].size = 0;
		for (j = 0; j < MAX_COOKIE + 1; j++)
			cutters[i].mShape[j] = 0;
		for (j = 0; j < 10; j++)
			cutters[i].mShapeList[j] = 0;
	}
}

void addCookieCutter(int mID, int N, int mShapeList[])
{
	int i;
    
    cutters[mID].size = 0;

    for ( i = 0; i < N; i++) 
	{
        cutters[mID].mShape[mShapeList[i]] = 1;
        cutters[mID].mShapeList[i] = mShapeList[i];
        cutters[mID].size++;
    }
    cutter_count++;
}

int my_compare(void* a, void* b)
{
	int ret = 0;
	Order* x = (Order*)a;
	Order* y = (Order*)b;

	if (x->day != y->day)
		return   x->day - y->day;
	else
		return x->index - y->index;
	
	return 0;
}

void orderCookie(int mShape, int daysLeft)
{
    int day = today + daysLeft;
    Order* ptr = &orders[order_count++];
	ptr->index = order_count-1;
    ptr->day = day;
    ptr->mShape = mShape;
	list_add_tail(&ptr->list, &days[day]);

    push(&heap[mShape],ptr,my_compare);
}

int checkRemain(int mShape)
{
    return heap[mShape].h_count;
}

void newDay(void)
{
	NODE* temp, *n;
	Order* ptr;
	int target = 0;
    today++;

    while ( !list_empty( &days[today]) ) 
	{ 
		temp = days[today].next;

		ptr = list_entry(temp, Order, list);

		int mShape = ptr->mShape;
		int max = -1;

		for (int cutter = 1; cutter < cutter_count; cutter++)
		{
			if (cutters[cutter].mShape[mShape] == 0)
				continue;

			int score = 0;
			for (int i = 0; i < cutters[cutter].size; i++)
			{
				if (heap[cutters[cutter].mShapeList[i]].h_count > 0)
					score++;
			}
			if (score > max)
			{
				max = score;
				target = cutter;
			}
		}


        for (int i = 0; i < cutters[target].size; i++) 
		{
			Order* p;
			if (heap[cutters[target].mShapeList[i]].h_count > 0)
			{
				p = (Order*)top(&heap[cutters[target].mShapeList[i]]);
				if (p)
					list_del(&p->list);
				pop(&heap[cutters[target].mShapeList[i]], my_compare);
			}
        }
		makeCookies(target);
    }
	
}

